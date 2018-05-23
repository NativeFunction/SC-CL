#pragma once
#include "Utils/ClangUtils.h"
#include "ClangParsing/Helpers/Script.h"
#include "stdint.h"

namespace SCCL
{
	extern llvm::cl::OptionCategory ClangOptions;
	extern llvm::cl::OptionCategory CompilerOptions;

	extern llvm::cl::opt<bool> Help;
	extern llvm::cl::opt<std::string> BuildPath;
	extern llvm::cl::list<std::string> SourcePaths;
	extern llvm::cl::list<std::string> ArgsAfter;
	extern llvm::cl::list<std::string> ArgsBefore;

	extern llvm::cl::opt<Platform> Option_Platform;
	extern llvm::cl::opt<BuildType> Option_BuildType;
	extern llvm::cl::opt<std::string> Option_OutputFileName;

	typedef enum ObfLevel
	{
		obf_none,
		obf_string, //just xor string table
		obf_low, //low: int maxBlockSize = 50, int minBlockSize = 30, bool keepEndReturn = true, bool makeJumpTable = false
		obf_default, //default: int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = false
		obf_high, //high: int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = true
		obf_veryhigh, //very high: int maxBlockSize = 15, int minBlockSize = 5, bool keepEndReturn = false, bool makeJumpTable = true
		obf_max, //max: int maxBlockSize = 5, int minBlockSize = 1, bool keepEndReturn = false, bool makeJumpTable = true
	} ObfLevel;

	extern llvm::cl::opt<ObfLevel> Option_ObfuscationLevel;

	extern llvm::cl::opt<uint32_t> Option_PCVerison;

	extern llvm::cl::opt <uint32_t> Option_HostVarIndex;
	extern llvm::cl::opt <uint32_t> Option_HostVarSize;
	extern llvm::cl::opt <uint32_t> Option_PlayerVarIndex;
	extern llvm::cl::opt <uint32_t> Option_PlayerVarSize;
	extern llvm::cl::opt<OptimisationLevel> Option_OptimizationLevel;
    extern llvm::cl::opt<GTAIVSCRFlags> Option_GTAIVSCRFlag;

	extern llvm::cl::opt<bool> Option_EmitAsm;
	extern llvm::cl::opt<bool> Option_AsmOnly;
	extern llvm::cl::opt<bool> Option_NoRSC7;

	extern llvm::cl::opt<std::string> Option_OutputDirectory;

	extern llvm::cl::opt<std::string> Option_VCXPROJ;

	#pragma region Bool_Group
	//Grouping is for multi bool set support ex: -snb
	extern llvm::cl::opt<bool> Option_Singleton;
	extern llvm::cl::opt<bool> Option_DisableFunctionNames;
	extern llvm::cl::opt<bool> Option_EntryFunctionPadding;
	#pragma endregion

	//extern llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
	//extern llvm::cl::extrahelp ProgramHelp("\nTemp text...\n");

}