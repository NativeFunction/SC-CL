#pragma once

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/ADT/STLExtras.h"
#include "clang/Tooling/ArgumentsAdjusters.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"
#include "Utils/Utils.h"

class ArgumentsAdjustingCompilations : public clang::tooling::CompilationDatabase {
public:
	ArgumentsAdjustingCompilations(
		std::unique_ptr<CompilationDatabase> Compilations)
		: Compilations(std::move(Compilations)) {}

	void appendArgumentsAdjuster(clang::tooling::ArgumentsAdjuster Adjuster) {
		Adjusters.push_back(Adjuster);
	}

	std::vector<clang::tooling::CompileCommand>
		getCompileCommands(StringRef FilePath) const override {
		return adjustCommands(Compilations->getCompileCommands(FilePath));
	}

	std::vector<std::string> getAllFiles() const override {
		return Compilations->getAllFiles();
	}

	std::vector<clang::tooling::CompileCommand> getAllCompileCommands() const override {
		return adjustCommands(Compilations->getAllCompileCommands());
	}

private:
	std::unique_ptr<CompilationDatabase> Compilations;
	std::vector<clang::tooling::ArgumentsAdjuster> Adjusters;

	std::vector<clang::tooling::CompileCommand>
		adjustCommands(std::vector<clang::tooling::CompileCommand> Commands) const {
		for (clang::tooling::CompileCommand &Command : Commands)
			for (const auto &Adjuster : Adjusters)
				Command.CommandLine = Adjuster(Command.CommandLine, Command.Filename);
		return Commands;
	}
};

namespace Utils {
	namespace System
	{
		void Throw(std::string str, clang::Rewriter writer, clang::SourceLocation location);
		void Throw(std::string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end);
		void Throw(std::string str, clang::Rewriter writer, clang::SourceRange range);
		void Warn(std::string str, clang::Rewriter writer, clang::SourceLocation location);
		void Warn(std::string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end);
		void Warn(std::string str, clang::Rewriter writer, clang::SourceRange range);
	}
	namespace ClangUtils
	{
		uint32_t GetLineFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		uint32_t GetColumnFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		std::string GetFileFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		std::string GetLineStringFromLocation(clang::Rewriter writer, clang::SourceLocation location);
	}
}
