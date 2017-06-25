#include "ClangParsing/ASTConsumer.h"

using namespace clang;

bool SCCL::ASTConsumer::HandleTopLevelDecl(DeclGroupRef DR)
{
	for (Decl* decl : DR)
	{
		// Traverse the declaration using our AST visitor.
		GlobalVisitor.TraverseDecl(decl);
	}

	for (Decl* decl : DR)
	{
		// Traverse the declaration using our AST visitor.
		LocalVisitor.TraverseDecl(decl);
	}

	return true;
}