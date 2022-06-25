#include <iostream>
#include <string>
#include "Utils/rapidxml/rapidxml.hpp"
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
using namespace rapidxml;

namespace SCCL
{
	void WriteAsmFile(const string& outDir)
	{
		string Out = outDir + scriptData->getASMFileName();
		FILE* file = nullptr;
		if (Utils::IO::CreateFileWithDir(Out.data(), file))
		{
			//this needs tidying up and when ready removing the first statics method
			string staticData = scriptData->getStaticsAsString();
			fwrite(staticData.data(), 1, staticData.size(), file);

			for (uint32_t i = 0, max = scriptData->getFunctionCount(); i < max; i++)
			{
				auto func = scriptData->getFunctionFromIndex(i);
				if (func->IsUsed())
				{
					if (!func->isProcessed())
						Throw("Function Prototype Implementation missing on referenced function: " + func->getName());

					string fStr = func->toString();
					fwrite(fStr.c_str(), 1, fStr.size(), file);
				}
			}
			fclose(file);
		}

	}

	void WriteScriptFile(const string& outDir)
	{
		for (uint32_t i = 0, max = scriptData->getFunctionCount(); i < max; i++)
		{
			const FunctionData* func = scriptData->getFunctionFromIndex(i);
			if (func->IsUsed())
			{
				if (!func->isProcessed())
					Throw("Function Prototype Implementation missing on referenced function: " + func->getName());
			}
		}
		switch (scriptData->getBuildType())
		{
			case BT_GTAIV_TLAD:
			case BT_GTAIV_TBOGT:
			case BT_GTAIV:
			{
				switch (scriptData->getBuildPlatform())
				{
					case P_XBOX:
					case P_PSX:
					case P_PC:
					{
						CompileGTAIV c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
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
				switch (scriptData->getBuildPlatform())
				{
					case P_XBOX:
					case P_PSX:
					{
						CompileRDR c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
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
				switch (scriptData->getBuildPlatform())
				{
					case P_XBOX:
					case P_PSX:
					{
						CompileGTAV c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
						if (Option_ObfuscationLevel > obf_none)
						{
							c.setEncryptStrings();
						}
						c.Compile(outDir);
					}
					break;
					case P_PC:
					{
						CompileGTAVPC c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
						if (Option_ObfuscationLevel > obf_none)
						{
							c.setEncryptStrings();
						}
						c.Compile(outDir);
					}
					break;
					default:
						Throw("GTA V only supported on Xbox360, PS3, and PC");
				}
			}
            case BT_RDR2:
            {
                switch (scriptData->getBuildPlatform())
                {
                case P_XBOX:
                case P_PSX:
                {
                    CompileRDR2Console c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
                    if (Option_ObfuscationLevel > obf_none)
                    {
                        c.setEncryptStrings();
                    }
                    c.Compile(outDir);
                }
                break;
                case P_PC:
                {
                    CompileRDR2PC c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
                    if (Option_ObfuscationLevel > obf_none)
                    {
                        c.setEncryptStrings();
                    }
                    c.Compile(outDir);
                }
                break;
                default:
                    Throw("Red Dead Redemption 2 only supported on Console and PC");
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

	void PrintVersion()
	{
		cout << "Version: " << VERSION << endl;
	}

	int ProcessFiles(ClangTool &Tool)
	{
		bool ProcessingFailed = true;
		if (SourcePaths.size() > 0)
		{
			//TODO: this is temporary. script name should be set from the file that the main function is in

			string outDir = Option_OutputDirectory.size() ? Option_OutputDirectory : Utils::IO::GetDir(SourcePaths[0]);

			string scriptName = (Option_OutputFileName != "" ? Option_OutputFileName : GetBaseNameFromDir(SourcePaths[0]));
			scriptData.reset(new Script(scriptName, Option_BuildType, Option_Platform, Option_Singleton, Option_EntryFunctionPadding, Option_OptimizationLevel));

			stackWidth = scriptData->getStackWidth();
			ProcessingFailed = Tool.run(newFrontendActionFactory<ASTFrontendAction>().get());


			/// ClangTool::run accepts a FrontendActionFactory, which is then used to
			/// create new objects implementing the FrontendAction interface. Here we use
			/// the helper newFrontendActionFactory to create a default factory that will
			/// return a new MyFrontendAction object every time.
			/// To further customize this, we could create our own factory class.
			if (!ProcessingFailed)
			{
				//ProcessingSuccess
				if (Option_HostVarSize)
				{
					scriptData->resgisterReservedStaticBlock(Option_HostVarIndex, Option_HostVarSize);
				}
				if (Option_PlayerVarSize)
				{
					scriptData->resgisterReservedStaticBlock(Option_PlayerVarIndex, Option_PlayerVarSize);
				}
				scriptData->finaliseEntryFunction();

				if (Option_AsmOnly || Option_EmitAsm)
				{
					WriteAsmFile(outDir);
				}
				if (!Option_AsmOnly)
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

	void ParseVCXPROJFile(llvm::cl::list<string>& SourcePaths)
	{
		if (Option_VCXPROJ.size())
		{
			SourcePaths.empty();

			vector<uint8_t> VCXPROJFileText;
			string dir = Utils::IO::GetDir(Option_VCXPROJ);
			Utils::IO::LoadData(Option_VCXPROJ.c_str(), VCXPROJFileText);
			VCXPROJFileText.push_back(0);

			xml_document<> VCXPROJFile;

			size_t xmlStartOffset = 0;
			for (; xmlStartOffset < VCXPROJFileText.size(); xmlStartOffset++)
			{
				if (VCXPROJFileText[xmlStartOffset] == '<')
					break;
			}


			VCXPROJFile.parse<0>((char*)VCXPROJFileText.data() + xmlStartOffset);// 0 = default parse flags

			bool mainFound = false;

			vector<char*> SavedSourcePaths;

			if (xml_node<>* baseNode = VCXPROJFile.first_node("Project"))
			{
				for (xml_node<> *currentNode = baseNode->first_node("ItemGroup"); currentNode; currentNode = currentNode->next_sibling("ItemGroup"))
				{
					//if it has an attribute we dont want it
					if (currentNode->first_attribute())
						continue;
			
					if (xml_node<> *customBuildNode = currentNode->first_node("CustomBuild"))
					{
						if (xml_attribute<> *mainFileName = customBuildNode->first_attribute("Include"))
						{
							SourcePaths.push_back(dir + mainFileName->value());
							mainFound = true;
						}
					}
					else
					{
						for (xml_node<> *clCompileNode = currentNode->first_node("ClCompile"); clCompileNode; clCompileNode = clCompileNode->next_sibling("ClCompile"))
						{
							if (xml_attribute<> *sourceIncludeFileName = clCompileNode->first_attribute("Include"))
							{
								SavedSourcePaths.push_back(sourceIncludeFileName->value());
							}
						}
					}
				}
			}

			if (mainFound)
			{
				//this fixes potential case of a ItemGroup of type ClCompile is before the ItemGroup of type CustomBuild (main file)
				for (char* path : SavedSourcePaths)
				{
					SourcePaths.push_back(dir + path);
				}
			}
			else
				Throw("Could not parse " + Option_VCXPROJ);

		}
	}

	void ParseCommandLine(int argc, const char **argv, const char* Overview, unique_ptr<CompilationDatabase>& Compilations)
	{
        string err = "Error loading from command line";
        Compilations = FixedCompilationDatabase::loadFromCommandLine(argc, argv, err);

		ParseCommandLineOptions(argc, argv, Overview);

		//file is visual studio project
		if (Option_VCXPROJ.size())
		{
			ParseVCXPROJFile(SourcePaths);
		}

		if (!Compilations)
		{
			string ErrorMessage;
			if (!BuildPath.empty())
				Compilations = CompilationDatabase::autoDetectFromDirectory(BuildPath, ErrorMessage);
			else
				Compilations = CompilationDatabase::autoDetectFromSource(SourcePaths[0], ErrorMessage);
			if (!Compilations)
			{
				llvm::errs() << "Error while trying to load a compilation database:\n" << ErrorMessage << "Running without flags.\n";
				Compilations.reset(new FixedCompilationDatabase(".", std::vector<std::string>()));
			}
		}
        auto AdjustingCompilations = std::make_unique<clang::tooling::ArgumentsAdjustingCompilations> (std::move(Compilations));

		AdjustingCompilations->appendArgumentsAdjuster(getInsertArgumentAdjuster(ArgsBefore, ArgumentInsertPosition::BEGIN));
		AdjustingCompilations->appendArgumentsAdjuster(getInsertArgumentAdjuster(ArgsAfter, ArgumentInsertPosition::END));
		Compilations = std::move(AdjustingCompilations);
	}
}

int main(int argc, const char **argv)
{
	llvm::errs() << "Starting SC-CL " << VERSION << " running Clang 14.0.5\n";

	SCCL::globalDirectory = Utils::IO::GetDir(string(argv[0]));

    llvm::cl::VersionPrinterTy versionPrinter = [&] (llvm::raw_ostream& os) -> void
    {
        SCCL::PrintVersion();
    };
    
	SetVersionPrinter(versionPrinter);
	unique_ptr<CompilationDatabase> Compilations;
    
	SCCL::ParseCommandLine(argc, argv, " SC-CL\n", Compilations);

	ClangTool Tool(*Compilations, SCCL::SourcePaths);
	return SCCL::ProcessFiles(Tool);
}
