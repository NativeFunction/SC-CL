#pragma once

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"
#include "Utils.h"


using namespace std;


namespace Utils {
	namespace System
	{
		void Throw(string str, clang::Rewriter writer, clang::SourceLocation location);
		void Throw(string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end);
		void Throw(string str, clang::Rewriter writer, clang::SourceRange range);
		void Warn(string str, clang::Rewriter writer, clang::SourceLocation location);
		void Warn(string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end);
		void Warn(string str, clang::Rewriter writer, clang::SourceRange range);
	}
	namespace ClangUtils
	{
		uint32_t GetLineFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		uint32_t GetColumnFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		string GetFileFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		string GetLineStringFromLocation(clang::Rewriter writer, clang::SourceLocation location);
	}
}
