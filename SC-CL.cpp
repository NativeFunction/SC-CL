#include <iostream>
#include <string>
#include "Utils/ClangUtils.h"
#include "Utils/Utils.h"
#include "Compiler/Compiler.h"
#include "Version/Version.h"
#include "ClangParsing/CommandLineOptions.h"
#include "ClangParsing/GlobalDecls.h"
#include "ClangParsing/ASTFrontendAction.h"

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm::cl;
using namespace Utils::System;

void WriteAsmFile(const string& outDir)
{
	string Out = outDir + SCCL::scriptData->getASMFileName();
	FILE* file = fopen(Out.data(), "wb");
	if (file != NULL)
	{
		//this needs tidying up and when ready removing the first statics method
		string staticData = SCCL::scriptData->getStaticsAsString();
		fwrite(staticData.data(), 1, staticData.size(), file);

		for (uint32_t i = 0, max = SCCL::scriptData->getFunctionCount(); i <max; i++)
		{
			auto func = SCCL::scriptData->getFunctionFromIndex(i);
			if (func->IsUsed())
			{
				if (!func->isProcessed())
					Throw("Function Prototype Implementation missing on referenced function: " + func->getName());
				assert(func->isProcessed() && "Function Prototype Implementation missing on referenced function");
				string fStr = func->toString();
				fwrite(fStr.c_str(), 1, fStr.size(), file);
			}
		}
		fclose(file);
	}
	else Throw("Output File \"" + Out + "\" Could Not Be Opened");

}

void WriteScriptFile(const string& outDir)
{
	switch (SCCL::scriptData->getBuildType())
	{
		case BT_GTAIV_TLAD:
		case BT_GTAIV_TBOGT:
		case BT_GTAIV:
		{
			switch (SCCL::scriptData->getBuildPlatform())
			{
				case P_X360:
				case P_PS3:
				case P_PC:
				{
					CompileGTAIV c(*SCCL::scriptData, SCCL::Option_DisableFunctionNames || SCCL::Option_OptimizationLevel > OptimisationLevel::OL_None);
					c.Compile(outDir);
				}
				break;
				default:
					Throw("Grand Theft Auto IV is only supported on Xbox360, PS3 and PC");
			}
		}
		break;
		case BT_RDR_XSC:
		case BT_RDR_SCO:
		{
			switch (SCCL::scriptData->getBuildPlatform())
			{
				case P_X360:
				case P_PS3:
				{
					CompileRDR c(*SCCL::scriptData, SCCL::Option_DisableFunctionNames || SCCL::Option_OptimizationLevel > OptimisationLevel::OL_None);
					c.Compile(outDir);
				}
				break;
				default:
					Throw("Red Dead Redemption is only supported on Xbox360 and PS3");
			}
		}
		break;
		case BT_GTAV:
		{
			switch (SCCL::scriptData->getBuildPlatform())
			{
				case P_X360:
				case P_PS3:
				{
					CompileGTAV c(*SCCL::scriptData, SCCL::Option_DisableFunctionNames || SCCL::Option_OptimizationLevel > OptimisationLevel::OL_None);
					if (SCCL::Option_ObfuscationLevel > SCCL::obf_none)
					{
						c.setEncryptStrings();
					}
					c.Compile(outDir);
				}
				break;
				case P_PC:
				{
					CompileGTAVPC c(*SCCL::scriptData, SCCL::Option_PCVerison, SCCL::Option_DisableFunctionNames || SCCL::Option_OptimizationLevel > OptimisationLevel::OL_None);
					if (SCCL::Option_ObfuscationLevel > SCCL::obf_none)
					{
						c.setEncryptStrings();
					}
					c.Compile(outDir);
				}
				break;
				default:
					Throw("GTA V only supported on Xbox360 and PS3");
			}
		}
		break;
		default:
			Throw("Unsupported Build Platform");
	}
}

string GetBaseNameFromDir(const string &Dir)
{
	const size_t BaseStartPos = Dir.find_last_of("/\\") + 1;
	const size_t BaseExtPos = Dir.find_last_of('.');
	if (BaseExtPos == Dir.npos)
		return "Script";
	else if (BaseStartPos == Dir.npos)
		return Dir.substr(BaseStartPos, BaseExtPos);
	return Dir.substr(BaseStartPos, BaseExtPos - BaseStartPos);
}

string GetDir(const string &Dir)
{
	const size_t BaseExtPos = Dir.find_last_of("/\\") + 1;
	return BaseExtPos == Dir.npos ? "" : Dir.substr(0, BaseExtPos);
}

void PrintVersion()
{
	cout << "Version: " << VERSION << endl;
}

int ProcessFiles(ClangTool &Tool)
{
	bool ProcessingFailed = true;
	if (SCCL::SourcePaths.size() > 0)
	{
		//TODO: this is temporary. script name should be set from the file that the main function is in
		//TODO: find or make a command for an out directory

		string outDir = GetDir(SCCL::SourcePaths[0]);
		string scriptName = (SCCL::Option_OutputFileName != "" ? SCCL::Option_OutputFileName : GetBaseNameFromDir(SCCL::SourcePaths[0]));
		SCCL::scriptData.reset(new Script(scriptName, SCCL::Option_BuildType, SCCL::Option_Platform, SCCL::Option_Singleton, SCCL::Option_EntryFunctionPadding, SCCL::Option_OptimizationLevel));

		SCCL::stackWidth = SCCL::scriptData->getStackWidth();
		ProcessingFailed = Tool.run(newFrontendActionFactory<SCCL::ASTFrontendAction>().get());
		
		/// ClangTool::run accepts a FrontendActionFactory, which is then used to
		/// create new objects implementing the FrontendAction interface. Here we use
		/// the helper newFrontendActionFactory to create a default factory that will
		/// return a new MyFrontendAction object every time.
		/// To further customize this, we could create our own factory class.
		if (!ProcessingFailed)
		{
			//ProcessingSuccess
			if (SCCL::Option_HostVarSize)
			{
				SCCL::scriptData->resgisterReservedStaticBlock(SCCL::Option_HostVarIndex, SCCL::Option_HostVarSize);
			}
			if (SCCL::Option_PlayerVarSize)
			{
				SCCL::scriptData->resgisterReservedStaticBlock(SCCL::Option_PlayerVarIndex, SCCL::Option_PlayerVarSize);
			}
			SCCL::scriptData->finaliseEntryFunction();

			if (SCCL::Option_AsmOnly || SCCL::Option_EmitAsm)
			{
				WriteAsmFile(outDir);
			}
			if (!SCCL::Option_AsmOnly)
			{
				WriteScriptFile(outDir);
			}

		}
		else
		{
			//ProcessingFailed
		}
	}
	return (int)ProcessingFailed;
}

void ParseCommandLine(int argc, const char **argv, const char* Overview, unique_ptr<CompilationDatabase>& Compilations)
{
	Compilations.reset(FixedCompilationDatabase::loadFromCommandLine(argc, argv));
	ParseCommandLineOptions(argc, argv, Overview);

	if (!Compilations)
	{
		string ErrorMessage;
		if (!SCCL::BuildPath.empty())
			Compilations = CompilationDatabase::autoDetectFromDirectory(SCCL::BuildPath, ErrorMessage);
		else
			Compilations = CompilationDatabase::autoDetectFromSource(SCCL::SourcePaths[0], ErrorMessage);
		if (!Compilations)
		{
			llvm::errs() << "Error while trying to load a compilation database:\n" << ErrorMessage << "Running without flags.\n";
			Compilations.reset(new FixedCompilationDatabase(".", std::vector<std::string>()));
		}
	}
	auto AdjustingCompilations = llvm::make_unique<ArgumentsAdjustingCompilations>(std::move(Compilations));

	AdjustingCompilations->appendArgumentsAdjuster(getInsertArgumentAdjuster(SCCL::ArgsBefore, ArgumentInsertPosition::BEGIN));
	AdjustingCompilations->appendArgumentsAdjuster(getInsertArgumentAdjuster(SCCL::ArgsAfter, ArgumentInsertPosition::END));
	Compilations = std::move(AdjustingCompilations);
}

int main(int argc, const char **argv)
{
	llvm::errs() << "Starting SC-CL " << VERSION << " running Clang 3.8.1\n";

	SCCL::globalDirectory = GetDir(string(argv[0]));
	SetVersionPrinter(PrintVersion);
	unique_ptr<CompilationDatabase> Compilations;
	ParseCommandLine(argc, argv, " SC-CL\n", Compilations);

	ClangTool Tool(*Compilations, SCCL::SourcePaths);
	return ProcessFiles(Tool);
}
