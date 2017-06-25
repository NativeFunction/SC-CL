#pragma once
#include "Utils/ClangUtils.h"
#include "clang/Lex/PreProcessor.h"
#include "stdint.h"
#include "ClangParsing/GlobalDecls.h"

namespace SCCL
{
	class ASTVisitorLocal : public clang::RecursiveASTVisitor<ASTVisitorLocal>
	{
	public:
		ASTVisitorLocal(clang::Rewriter &R, const clang::ASTContext& context, Script& scriptData) : TheRewriter(R), context(context), scriptData(scriptData) {}

		#pragma region Misc_Functions
		void ComplexToBoolean(bool floating);

		#pragma endregion

		#pragma region Name_Resolution
		std::string dumpName(const clang::NamedDecl *ND);
		std::string getNameForFunc(const clang::FunctionDecl *decl);
		#pragma endregion

		#pragma region Parsing
		std::string parseCast(const clang::CastExpr *castExpr);
		#pragma endregion

		#pragma region Decl_Handling
		void printDeclWithKey(const std::string& key, bool isAddr, bool isLtoRValue, bool isAssign, const clang::DeclRefExpr* declref);
		bool handleParmVarDecl(clang::ParmVarDecl *D);
		bool handleDecl(clang::DeclStmt* decl);
		#pragma endregion

		#pragma region Parse/Visit_Functions
		void parseCallProto(const clang::CallExpr* call, bool& isVariadic, size_t& NumParams);

		bool isPushString(const clang::Expr* e);
		bool EvaluateAsString(const clang::Expr* cExpr, std::string& outStr);

		bool checkIntrinsic(const clang::CallExpr* call);

		bool findAnyLabel(const clang::Stmt* stmt);
		void parseJumpFalse(const clang::Expr* conditional, const std::string& jumpFalseLoc);

		void parseCondition(const clang::Expr* conditional, const std::string& trueLoc, const std::string& falseLoc);
		void parseCondition2(const clang::Expr* conditional, const std::string& trueLoc, const std::string& falseLoc);
		void parseJumpTrue(const clang::Expr* conditional, const std::string& jumpTrueLoc);
		bool parseStatement(clang::Stmt *s, const std::string& breakLoc, const std::string& continueLoc);

		/// <summary>
		/// Parses the expression.
		/// </summary>
		/// <param name="e">The e.</param>
		/// <param name="isAddr">if set to <c>true</c> [is addr].</param>
		/// <param name="isLtoRValue">if set to <c>true</c> [is lto r value].</param>
		/// <param name="printVTable">if set to <c>true</c> [print v table].</param>
		/// <param name="isAssign">if set to <c>true</c> [is assign].</param>
		/// <returns></returns>
		int parseExpression(const clang::Expr *e, bool isAddr = false, bool isLtoRValue = false, bool printVTable = true, bool isAssign = false, bool isArrToPtrDecay = false);

		bool parseArraySubscriptExpr(const clang::Expr *e, bool addrOf, bool LValueToRValue = false, bool isArrToPtrDecay = false);

		bool VisitFunctionDecl(clang::FunctionDecl *f);
		#pragma endregion

	public:
		clang::Rewriter &TheRewriter;
		const clang::ASTContext &context;

		const clang::FunctionDecl *currFunction;
		Script& scriptData;
	};
}