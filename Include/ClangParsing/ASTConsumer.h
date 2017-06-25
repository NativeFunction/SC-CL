#pragma once
#include "Utils/ClangUtils.h"
#include "clang/Lex/PreProcessor.h"
#include "stdint.h"
#include "ClangParsing/GlobalDecls.h"
#include "ClangParsing/ASTVisitorGlobal.h"
#include "ClangParsing/ASTVisitorLocal.h"

namespace SCCL
{
	class ASTConsumer : public clang::ASTConsumer
	{
	public:
		ASTConsumer(clang::Rewriter &R, const clang::ASTContext &context, Script& scriptData) : LocalVisitor(R, context, scriptData), GlobalVisitor(R, context, scriptData)
		{

		}

		// Override the method that gets called for each parsed top-level
		// declaration.
		bool HandleTopLevelDecl(clang::DeclGroupRef DR) override;

	private:
		ASTVisitorLocal LocalVisitor;
		ASTVisitorGlobal GlobalVisitor;
	};
}