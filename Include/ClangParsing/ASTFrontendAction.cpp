#include "ClangParsing\ASTFrontendAction.h"
#include "Version\Version.h"
#include "ClangParsing\ASTConsumer.h"

using namespace std;
using namespace clang;

void SCCL::ASTFrontendAction::AddDefines(Preprocessor &PP)
{
	string preDefines = PP.getPredefines();

	int major = 0, minor = 0, revision = 0, patchlevel = 0;
	sscanf(VERSION, "%d.%d.%d.%d", &major, &minor, &revision, &patchlevel);
	preDefines += "\n#define __SCCL_major__ " + to_string(major);
	preDefines += "\n#define __SCCL_minor__ " + to_string(minor);
	preDefines += "\n#define __SCCL_revision__ " + to_string(revision);
	preDefines += "\n#define __SCCL_patchlevel__ " + to_string(patchlevel);

	preDefines +=
		"\n#define __SCCL__ 1"

		"\n#define ENDIAN_BIG 0"
		"\n#define ENDIAN_LITTLE 1"

		"\n#define PLATFORM_X360 0"
		"\n#define PLATFORM_PS3 1"
		"\n#define PLATFORM_PC 2"

		"\n#define TARGET_GTAIV 0"
		"\n#define TARGET_GTAV 1"
		"\n#define TARGET_RDR 2"

		"\n#define FILETYPE_XSC 0"
		"\n#define FILETYPE_YSC 1"
		"\n#define FILETYPE_CSC 2"
		"\n#define FILETYPE_SCO 3"

		"\n#define SUBTARGET_TBOGT 0"
		"\n#define SUBTARGET_TLAD 1";

	switch (scriptData->getBuildPlatform())
	{
		case P_XBOX:
			preDefines +=
				"\n#define PLATFORM PLATFORM_X360"
				"\n#define ENDIAN ENDIAN_BIG";
			break;
		case P_PSX:
			preDefines +=
				"\n#define PLATFORM PLATFORM_PS3"
				"\n#define ENDIAN ENDIAN_BIG";
			break;
		case P_PC:
			preDefines +=
				"\n#define PLATFORM PLATFORM_PC"
				"\n#define ENDIAN ENDIAN_LITTLE";
			break;
	}
	switch (scriptData->getBuildType())
	{
		case BT_GTAIV_TLAD:
			preDefines +=
				"\n#define SUBTARGET SUBTARGET_TLAD"
				"\n#define TARGET TARGET_GTAIV"
				"\n#define FILETYPE FILETYPE_SCO"
				"\n#define PTRWIDTH 32";
			break;
		case BT_GTAIV_TBOGT:
			preDefines +=
				"\n#define SUBTARGET SUBTARGET_TBOGT";
		case BT_GTAIV:
			preDefines +=
				"\n#define TARGET TARGET_GTAIV"
				"\n#define FILETYPE FILETYPE_SCO"
				"\n#define PTRWIDTH 32";
			break;
		case BT_RDR_XSC:
			preDefines +=
				"\n#define TARGET TARGET_RDR"
				"\n#define PTRWIDTH 32"
				"\n#define FILETYPE FILETYPE_" + scriptData->getPlatformAbvUpper() + string("SC");
			break;
		case BT_RDR_SCO:
			preDefines +=
				"\n#define TARGET TARGET_RDR"
				"\n#define PTRWIDTH 32"
				"\n#define FILETYPE FILETYPE_SCO";
			break;
		case BT_GTAV:
			preDefines +=
				"\n#define TARGET TARGET_GTAV"
				"\n#define FILETYPE FILETYPE_" + scriptData->getPlatformAbvUpper() + string("SC");
			if (scriptData->getBuildPlatform() == P_PC)
				preDefines += "\n#define PTRWIDTH 64";
			else
				preDefines += "\n#define PTRWIDTH 32";

			break;

        case BT_RDR2:
            preDefines +=
                "\n#define TARGET TARGET_RDR2"
                "\n#define FILETYPE FILETYPE_" + scriptData->getPlatformAbvUpper() + string("SC");
            preDefines += "\n#define PTRWIDTH 64";

            break;
	}
	preDefines += "\n#undef _MSC_VER";
	
	PP.setPredefines(preDefines.data());
}

void SCCL::ASTFrontendAction::ModifyClangWarnings(DiagnosticsEngine& DE)
{
	#define DisableClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Ignored, SourceLocation());
	#define ElevateClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Error, SourceLocation());

	DisableClangWarning("main-return-type");
	DisableClangWarning("incompatible-library-redeclaration");
	DisableClangWarning("microsoft-enum-value");//this allows enums to be in hex without : unsigned int tag
	ElevateClangWarning("return-type");
	ElevateClangWarning("dangling-else");

	#undef DisableClangWarning
	#undef ElevateClangWarning
}

std::unique_ptr<ASTConsumer> SCCL::ASTFrontendAction::CreateASTConsumer(CompilerInstance &CI, StringRef file)
{
	llvm::errs() << "Compiling: " << file << "\n";

	diagnostics = &CI.getDiagnostics();
	CI.getLangOpts().Freestanding = true;

	TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
	rewriter = &TheRewriter;


	//const SourceManager &SM = TheRewriter.getSourceMgr();
	//string fileName(string(SM.getFileEntryForID(SM.getMainFileID())->getName()));

	//is CompilerInstance constant? if so these can be done once instead of being applied every file
	ModifyClangWarnings(*diagnostics);
	AddDefines(CI.getPreprocessor());
	

	return std::make_unique<SCCL::ASTConsumer>(TheRewriter, CI.getASTContext(), *scriptData);
}
