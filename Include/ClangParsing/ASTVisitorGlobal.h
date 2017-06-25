#pragma once
#include "Utils/ClangUtils.h"
#include "clang/Lex/PreProcessor.h"
#include "stdint.h"
#include "ClangParsing/GlobalDecls.h"

namespace SCCL
{
	class ASTVisitorGlobal : public clang::RecursiveASTVisitor<ASTVisitorGlobal>
	{
	public:
		ASTVisitorGlobal(clang::Rewriter &R, const clang::ASTContext &context, Script& scriptData) : TheRewriter(R), context(context), scriptData(scriptData)
		{

		}

		/// <summary>Gets the name of a function</summary>
		/// <param name="decl">Function to get name</param>
		/// <returns>The function name</returns>
		std::string getNameForFunc(const clang::FunctionDecl *decl);

		void addStaticPadding(size_t count);

		void addStatic(int32_t value);

		int32_t ParseLiteral(const clang::Expr *e, bool isAddr = false, bool isLtoRValue = false);

		bool VisitDecl(clang::Decl *D);

		std::string dumpName(const clang::NamedDecl *ND);

		inline void resetIntIndex();



	private:
		clang::VarDecl* globalVarDecl;
		uint32_t intIndex = 0;
		clang::Type* savedType = nullptr;
		bool isCurrentExprEvaluable = true;
		bool doesCurrentValueNeedSet = false;

		clang::Rewriter &TheRewriter;
		const clang::ASTContext &context;
		Script& scriptData;
	};
}