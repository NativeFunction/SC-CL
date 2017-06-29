#pragma once
#include "Utils/ClangUtils.h"
#include "clang/Lex/Preprocessor.h"
#include "stdint.h"
#include "ClangParsing/GlobalDecls.h"

namespace SCCL
{
	class ASTFrontendAction : public clang::ASTFrontendAction
	{
	public:

		ASTFrontendAction()
		{
			CurrentFileId++;
		}

		~ASTFrontendAction()
		{
			scriptData->updateStaticStatics();
			scriptData->resetStaticStatics();

			//this should not be needed anymore
			if (diagnostics->getClient()->getNumErrors())
				exit(EXIT_FAILURE);
		}

		std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, StringRef file) override;

	private:
		clang::DiagnosticsEngine* diagnostics = NULL;
		clang::Rewriter TheRewriter;
		std::string outDir;

		void AddDefines(clang::Preprocessor &PP);
		void ModifyClangWarnings(clang::DiagnosticsEngine& DE);

	};
}