//------------------------------------------------------------------------------
// Tooling sample. Demonstrates:
//
// * How to write a simple source tool using libTooling.
// * How to use RecursiveASTVisitor to find interesting AST nodes.
// * How to use the Rewriter API to rewrite the source code.
//
// Eli Bendersky (eliben@gmail.com)
// This code is in the public domain
//------------------------------------------------------------------------------
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <map>
#include <cmath>
#include "Utils.h"

using namespace Utils;
using namespace Utils::System;
using namespace Utils::DataConversion;
using namespace clang;
//using namespace clang::driver;
using namespace clang::tooling;
using namespace std;
static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

static Rewriter rewriter;

map<string, int> locals;
map<string, int> globals;
map<string, int> statics;


struct local_scope
{
	vector<map<string, int>> scope_locals;
	int scope_level = 0;
	int local_count = 2;//reserved for retn addr and stack base pointer
	void reset()//call this on function decl
	{
		scope_level = 0;
		scope_locals.clear();
		local_count = 2;
	}
	void add_level()
	{
		scope_locals.push_back(map<string, int>());
		scope_level++;
	}
	void remove_level()
	{
		if (scope_level > 0)
		{
			scope_level--;
			scope_locals.pop_back();
		}
	}
	bool find(string key, int* outIndex)
	{
		for (int i = scope_level; i >= 0; i--)
		{
			map<string, int>& locals = scope_locals[i];
			if (locals.find(key) != locals.end())
			{
				*outIndex = locals[key];
				return true;
			}
		}
		return false;
	}
	int add_decl(string key)
	{
		map<string, int>& locals = scope_locals[scope_level];
		//if(locals.find(key) != locals.end())
		//{
		//	//ast should catch this error when you have a redecl in the same scope
		//}
		locals[key] = local_count;
		return local_count++;//incriment local count
	}

};

map<const FunctionDecl*, int> localCounts;
static int globalInc = 0;
static int staticInc = 0;
static int localInc = 2;


// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.

uint32_t getSizeOfType(const Type* type);
uint64_t getSizeOfQualType(const QualType *type) {
	int mult = 1;
	if ((*type)->isArrayType()) {
		const ArrayType *arr = (*type)->getAsArrayTypeUnsafe();
		if (isa<ConstantArrayType>(arr)) {
			const ConstantArrayType *cArrType = cast<const ConstantArrayType>(arr);
			mult = cArrType->getSize().getSExtValue();
		}

	}

	const Type *canonical = type->getCanonicalType().getTypePtr();
	if (canonical->getBaseElementTypeUnsafe()->isCharType() && mult >= 4) {
		return 1 * mult + ((mult % 4 != 0) ? 1 : 0);
	}
	else if (canonical->isArrayType())
		return getSizeOfType(canonical->getArrayElementTypeNoTypeQual())*mult + (mult > 1 ? 4 : 0);
	else
		return getSizeOfType(canonical)*mult + (mult > 1 ? 4 : 0);
}

uint32_t getSizeOfCXXDecl(const CXXRecordDecl *classDecl, bool incVTableDef = false, bool incOwnVTable = false, const CXXRecordDecl *stopAt = NULL, bool *bFound = NULL) {
	incOwnVTable = true;
	if (classDecl == stopAt)
		return 0;

	uint64_t offset = 0;
	bool printedVTP = false;
	bool didAlloc = false;

	if (bFound == NULL) {
		didAlloc = true;
		bFound = new bool;
	}

	for (auto VBI : classDecl->bases()) {

		const CXXBaseSpecifier baseSpec = VBI;
		const CXXRecordDecl *baseDecl = baseSpec.getType()->getAsCXXRecordDecl();

		if (stopAt != NULL)
			if (baseDecl->getDeclName() == stopAt->getDeclName()) {
				*bFound = true;
				return offset;
			}


		offset += getSizeOfCXXDecl(baseDecl, incVTableDef, true, stopAt, bFound);
		if (*bFound)
			return offset;
	}


	printedVTP = false;
	if (incOwnVTable) {
		for (CXXMethodDecl *VFI : classDecl->methods()) {
			if (VFI->isVirtualAsWritten() && VFI->isFirstDecl()) {
				if (!printedVTP) {
					offset += 4;
					printedVTP = true;
				}
				if (incVTableDef)
					offset += 4;
				else
					break;
			}
		}
	}

	if (classDecl->isUnion()) {

		for (const FieldDecl *CS : classDecl->fields()) {
			if (CS->Decl::isFirstDecl() == false)
				continue;




			const  QualType type = CS->getType();
			int temp = getSizeOfQualType(&type);
			temp = max(temp, 4);

			if (temp > (int)offset)
				offset = temp;

		}
	}
	else {
		for (const FieldDecl *CS : classDecl->fields()) {
			if (CS->Decl::isFirstDecl() == false)
				continue;




			const  QualType type = CS->getType();
			int temp = getSizeOfQualType(&type);
			offset += max(temp, 4);
		}
	}

	return offset;
}
uint32_t getSizeOfVTable(const CXXRecordDecl *classDecl) {
	uint32_t size = 0;
	for (CXXMethodDecl *VFI : classDecl->methods()) {
		if (VFI->isVirtual()) {
			size++;
		}
	}
	return size;
}

uint32_t getSizeFromBytes(uint64_t bytes) {
	uint32_t size = (bytes / 4) + ((bytes % 4) ? 1 : 0);
	return size;
}

uint32_t getNumVirtMethods(const CXXRecordDecl *classDecl) {
	int numVirt = 0;
	for (CXXMethodDecl *VFI : classDecl->methods())
		if (VFI->isVirtual())
			numVirt++;

	return numVirt;
}
uint32_t getSizeOfType(const Type* type) {

	if (type->isCharType()) {
		return 1;
	}
	else if (isa<ConstantArrayType>(type)) {
		const ConstantArrayType *arrType = cast<const ConstantArrayType>(type);

		return getSizeOfType(type->getArrayElementTypeNoTypeQual())*(arrType->getSize()).getSExtValue();
	}
	else if (type->isRecordType() && type->getAsCXXRecordDecl()) {
		CXXRecordDecl *recordDecl = type->getAsCXXRecordDecl();
		return getSizeOfCXXDecl(recordDecl, true, false);
	}
	else if (type->isStructureType()) {
		const RecordType *record = type->getAsStructureType();

		if (RecordDecl *rd = record->getDecl()) {

			uint32_t size = 0;
			for (const auto *CS : rd->fields()) {
				const  QualType type = CS->getType();
				int temp = getSizeOfQualType(&type);

				size += max(temp, 4);
			}
			//cout << "struct: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

			return size;
		}

	}
	else if (type->isUnionType())
	{
		const RecordType *record = type->getAsUnionType();

		if (RecordDecl *rd = record->getDecl()) {

			uint32_t size = 0;
			for (const auto *CS : rd->fields()) {
				const  QualType type = CS->getType();
				int temp = getSizeOfQualType(&type);

				uint32_t sz = max(temp, 4);
				if (sz > size)
					size = sz;
			}
			//cout << "union: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

			return size;
		}

	}
	else if (type->isIntegerType() || type->isBooleanType() || type->isCharType() || type->isFloatingType() || type->isPointerType()) {
		return 4;
	}
	else if (type->isVoidType()) {
		return 0;
	}
	else {
		return 0;
	}
	return 0;
}


class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
public:
	MyASTVisitor(Rewriter &R, ASTContext *context, string filename) : TheRewriter(R), context(context), outfile(filename) {}

	//    bool VisitStmt(Stmt *s) {
	//        // Only care about compound statements.
	//
	//
	//        return true;
	//    }
	//


	bool handleParmVarDecl(ParmVarDecl *D) {
		if (isa<ParmVarDecl>(D)) {
			ParmVarDecl *decl = cast<ParmVarDecl>(D);
			if (isa<VarDecl>(decl)) {
				VarDecl *var = cast<VarDecl>(decl);
				auto size = context->getTypeInfoDataSizeInChars(var->getType()).first.getQuantity();
				uint32_t oldLocalInc = localInc;
				locals.insert(make_pair(var->getName().str(), localInc));
				if (var->isCXXInstanceMember())
					localInc += getSizeFromBytes(getSizeOfCXXDecl(var->getType()->getAsCXXRecordDecl(), true, false));
				else
					localInc += getSizeFromBytes(size);
				const Expr *initializer = var->getAnyInitializer();
				if (initializer) {
					if (isa<CXXConstructExpr>(initializer)) {

						out << pFrame(oldLocalInc) << " //" << var->getNameAsString() << endl;
						parseExpression(initializer);
					}
					else {
						parseExpression(initializer);
						out << frameSet(oldLocalInc) << "  //" << var->getName().str() << endl;
					}
				}

			}
		}
		return true;
	}


	string frameSet(int index) {
		if ((index & 0xFF) == index) {
			return "SetFrame1 " + to_string(index);
		}
		else if ((index & 0xFFFF) == index) {
			return "SetFrame2 " + to_string(index);
		}
		else {
			assert(!"Frame Index out of range");
		}
	}
	string frameGet(int index) {
		if ((index & 0xFF) == index) {
			return "GetFrame1 " + to_string(index);
		}
		else if ((index & 0xFFFF) == index) {
			return "GetFrame2 " + to_string(index);
		}
		else {
			assert(!"Frame Index out of range");
		}
	}
	string pFrame(const int index) {
		if ((index & 0xFF) == index)
			return "GetFrameP1 " + to_string(index);
		else if ((index & 0xFFFF) == index)
			return "GetFrameP2 " + to_string(index);
		else
			return "Index too large";

	}
	string GetImm(int size)
	{
		int aSize = size * 4;
		if ((size & 0xFF) == size)
			return "Add1 " + to_string(aSize) + "\r\npGet";
		else if ((size & 0xFFFF) == size)
			return "Add2 " + to_string(aSize) + "\r\npGet";
		else
			return iPush(aSize) + "\r\nAdd\r\npGet";
	}
	string SetImm(int size)
	{
		int aSize = size * 4;
		if ((size & 0xFF) == size)
			return "Add1 " + to_string(aSize) + "\r\npSet";
		else if ((size & 0xFFFF) == size)
			return "Add2 " + to_string(aSize) + "\r\npSet";
		else
			return iPush(aSize) + "\r\nAdd\r\npSet";
	}
	string iPush(int64_t val) {
		if (val < -1)
			return "Push " + to_string(val);
		else if (val >= -1 && val <= 7)
			return "Push_" + to_string(val);
		else if ((val & 0xFF) == val)
			return "PushB " + to_string(val);
		else if ((val & 0xFFFF) == val)
			return "PushS " + to_string(val);
		else if ((val & 0xFFFFFF) == val)
			return "PushI24 " + to_string(val);
		else
		{
			return "Push " + to_string(val);
		}

	}


	string dumpName(const NamedDecl *ND) {
		if (isa<CXXMethodDecl>(ND)) {
			const CXXMethodDecl *method = cast<const CXXMethodDecl>(ND);
			const CXXRecordDecl *record = method->getParent();
			return "@" + record->getNameAsString() + "::" + method->getNameAsString();
		}
		if (ND->getDeclName()) {

			return ND->getNameAsString();
		}
		return "";
	}


	void printDeclWithKey(string key, bool isAddr, bool isLtoRValue, int size = 1) {
		int index = -1;

		if (size > 1 && isLtoRValue) {
			out << "Push " << size << "//size" << endl;
			isAddr = true;
		}


		if (locals.find(key) != locals.end()) {
			index = locals[key];
			if (isLtoRValue && !isAddr) {
				out << frameGet(index) << " //" << key << endl;
			}
			else if (isAddr)
				out << pFrame(index) << " //&" << key << endl;
			else {
				out << frameSet(index) << " //" << key << endl;

			}


		}
		else if (globals.find(key) != globals.end()) {
			index = globals[key];
			if (isLtoRValue && !isAddr)
				out << "GetGlobal3 ";
			else if (isAddr)
				out << "GetGlobalP3 ";
			else
				out << "SetGlobal3 ";
			out << index << "  //" << key << endl;
		}
		else if (statics.find(key) != statics.end()) {
			index = statics[key];
			if (isLtoRValue && !isAddr)
				out << "GetStatic2 ";
			else if (isAddr)
				out << "GetStaticP2 ";
			else
				out << "SetStatic2 ";
			out << index << "  //" << key << endl;
		}
		else
		{
			out << "//DeclRefExpr, nothing else, so func it" << endl;
			out << "Push GetLoc(\"" << key << "\")" << endl;
			//out << key << endl;
			//out << "DeclRefExpr not implemented" << endl;
		}
		// out << "DeclRefExpr not implemented" << endl;

		if (size > 1 && isLtoRValue) {
			out << "ToStack" << endl;
		}

	}

	bool parseStatement(Stmt *s, uint64_t breakLoc = -1, uint64_t continueLoc = -1) {
		if (isa<CompoundStmt>(s)) {
			CompoundStmt *cSt = cast<CompoundStmt>(s);
			//            cSt->dump();
			for (auto *CS : cSt->body()) {
				if (isa<Stmt>(*CS))
					parseStatement(cast<Stmt>(CS), breakLoc, continueLoc);
				else if (isa<Expr>(CS))
					parseExpression(cast<const Expr>(CS));
			}
		}
		else if (isa<DeclStmt>(s)) {
			DeclStmt *decl = cast<DeclStmt>(s);
			handleDecl(decl);
		}
		else if (isa<IfStmt>(s)) {
			IfStmt *IfStatement = cast<IfStmt>(s);
			Expr *conditional = IfStatement->getCond();
			Stmt *Then = IfStatement->getThen();
			Stmt *Else = IfStatement->getElse();

			string IfLocEnd =
				to_string(Then->getLocEnd().getRawEncoding());

			parseExpression(conditional, false, true);
			out << "JumpFalse @" << (Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd) << endl;

			parseStatement(Then, breakLoc, continueLoc);


			out << "Jump @" << IfLocEnd << "//ifstmt jmp" << endl;

			if (Else) {
				out << endl << ":" << Else->getLocStart().getRawEncoding() << "//ifstmt else lbl" << endl;
				parseStatement(Else, breakLoc, continueLoc);
				out << "//" << Else->getLocStart().getRawEncoding() << " " << Else->getLocEnd().getRawEncoding() << endl;
			}
			if (Then)
			{
				out << "//" << Then->getLocStart().getRawEncoding() << " " << Then->getLocEnd().getRawEncoding() << endl;
			}

			out << endl << ":" << IfLocEnd << "//ifend lbl" << endl;


		}
		else if (isa<WhileStmt>(s)) {
			WhileStmt *whileStmt = cast<WhileStmt>(s);
			Expr *conditional = whileStmt->getCond();

			Stmt *body = whileStmt->getBody();

			out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;
			parseExpression(conditional, false, true);
			out << "JumpFalse @" << whileStmt->getLocEnd().getRawEncoding() << endl;
			parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding());
			out << "Jump @" << conditional->getLocStart().getRawEncoding() << endl;
			out << endl << ":" << whileStmt->getLocEnd().getRawEncoding() << endl;
		}
		else if (isa<ForStmt>(s)) {
			ForStmt *forStmt = cast<ForStmt>(s);
			Stmt *decl = forStmt->getInit();
			Expr *conditional = forStmt->getCond();
			Expr *increment = forStmt->getInc();
			Stmt *body = forStmt->getBody();
			if (decl) {
				if (isa<DeclStmt>(decl)) {
					handleDecl(cast<DeclStmt>(decl));
				}
			}

			if (conditional) {
				out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;

				parseExpression(conditional, false, true);
				if (increment)
					out << "JumpFalse @" << body->getLocEnd().getRawEncoding() << endl;
				else
					out << "JumpFalse @" << body->getLocEnd().getRawEncoding() << endl;
			}

			parseStatement(
				body,
				forStmt->getLocEnd().getRawEncoding(),
				increment->getLocStart().getRawEncoding());

			if (increment)
				out << endl << ":" << increment->getLocStart().getRawEncoding() << "//forstmt inc lbl" << endl;

			if (increment)
				parseExpression(increment);

			if (conditional)
				out << "Jump @" << conditional->getLocStart().getRawEncoding() << "//forstmt cond jmp" << endl;
			else
				out << "Jump @" << body->getLocStart().getRawEncoding() << "//forstmt jmp" << endl;


			out << endl << ":" << body->getLocEnd().getRawEncoding() << "//forend lbl" << endl;


		}
		else if (isa<UnaryOperator>(s)) {
			parseExpression(cast<const Expr>(s));
		}
		else if (isa<DoStmt>(s)) {
			DoStmt *doStmt = cast<DoStmt>(s);
			Expr *conditional = doStmt->getCond();

			Stmt *body = doStmt->getBody();


			out << endl << ":" << body->getLocStart().getRawEncoding() << endl;

			parseStatement(body, conditional->getLocEnd().getRawEncoding(), body->getLocStart().getRawEncoding());




			out << endl << ":" << conditional->getLocStart().getRawEncoding() << "" << endl;
			parseExpression(conditional, false, true);
			out << "not //Invert Result" << endl;
			out << "JumpFalse @" << body->getLocStart().getRawEncoding() << endl;
			out << endl << ":" << conditional->getLocEnd().getRawEncoding() << "" << endl;

		}
		else if (isa<ReturnStmt>(s)) {
			const ReturnStmt *ret = cast<const ReturnStmt>(s);
			const Expr* retVal = ret->getRetValue();
			if (retVal)
				parseExpression(retVal, false, true);
			int size = 0;
			if (ret->getRetValue()) {
				QualType type = ret->getRetValue()->getType();
				size = context->getTypeInfoDataSizeInChars(type).first.getQuantity();
			}

			int32_t paramSize = 0;
			for (uint32_t i = 0; i < currFunction->getNumParams(); i++) {
				paramSize += getSizeFromBytes(getSizeOfType(currFunction->getParamDecl(i)->getType().getTypePtr()));
			}
			out << "Return " << paramSize + (isa<CXXMethodDecl>(currFunction) ? 1 : 0) << " " << getSizeFromBytes(size) << endl;
		}
		else if (isa<Expr>(s)) {
			parseExpression(cast<const Expr>(s));
		}
		else if (isa<BreakStmt>(s)) {
			out << "Jump @" << breakLoc << "//brkstmt jmp" << endl;
		}
		else if (isa<NullStmt>(s)) {
			// out << "nop " << breakLoc << endl;
		}
		else if (isa<ContinueStmt>(s)) {
			out << "Jump @" << continueLoc << "//contstmt jmp" << endl;
		}
		else if (isa<DefaultStmt>(s)) {
			//            DefaultStmt *stmt = cast<DefaultStmt>(s);
			//            parseStatement(stmt->getSubStmt(), breakLoc);
		}
		else if (isa<CaseStmt>(s)) {
			CaseStmt *caseS = cast<CaseStmt>(s);

			Expr *LHS = caseS->getLHS();
			if (isa<CastExpr>(LHS)) {
				LHS = cast<CastExpr>(LHS)->getSubExpr();
			}
			string labelName = ":" + to_string(caseS->getLocEnd().getRawEncoding());
			if (isa<IntegerLiteral>(LHS)) {
				//IntegerLiteral *literal = cast<IntegerLiteral>(LHS);

				if (FindBuffer.find(labelName) == FindBuffer.end())
				{
					FindBuffer.insert(labelName);
					out << labelName << endl;
				}

			}
			else if (isa<FloatingLiteral>(LHS)) {
				//FloatingLiteral *literal = cast<FloatingLiteral>(LHS);
				if (FindBuffer.find(labelName) == FindBuffer.end())
				{
					FindBuffer.insert(labelName);
					out << labelName << endl;
				}
			}

			if (caseS->getRHS())
				parseExpression(caseS->getRHS());

			if (caseS->getSubStmt())
				parseStatement(caseS->getSubStmt(), breakLoc);
		}
		else if (isa<SwitchStmt>(s)) {
			SwitchStmt *switchStmt = cast<SwitchStmt>(s);
			out << "//Switch Conditional" << endl;
			FindBuffer.clear();
			parseExpression(switchStmt->getCond());
			out << "Switch ";

			//Build case switch list first
			SwitchCase *switchCaseList = switchStmt->getSwitchCaseList();
			while (switchCaseList != NULL)
			{
				if (isa<CaseStmt>(switchCaseList))
				{
					CaseStmt *caseS = cast<CaseStmt>(switchCaseList);
					Expr *LHS = caseS->getLHS();
					if (isa<CastExpr>(LHS)) {
						LHS = cast<CastExpr>(LHS)->getSubExpr();
					}
					if (isa<IntegerLiteral>(LHS)) {
						IntegerLiteral *literal = cast<IntegerLiteral>(LHS);
						out << "[" << literal->getValue().getSExtValue() << " @" << caseS->getLocEnd().getRawEncoding() << "]";
					}
					else if (isa<FloatingLiteral>(LHS)) {
						FloatingLiteral *literal = cast<FloatingLiteral>(LHS);
						out << "[" << literal->getValue().convertToFloat() << " @" << caseS->getLocEnd().getRawEncoding() << "]";
					}
					else Throw("Unsupported case statement \"" + string(LHS->getStmtClassName()) + "\"", rewriter, LHS->getExprLoc());

				}
				else if (isa<DefaultStmt>(switchCaseList))
				{
					//We don't handle the default case here..
				}
				else
					llvm::errs() << "Unexpected Statement: " << switchCaseList->getStmtClassName();

				bool isStmt = isa<DefaultStmt>(switchCaseList);
				switchCaseList = switchCaseList->getNextSwitchCase();
				if (switchCaseList == NULL)
					out << endl;
				else
					if (!isStmt)
						out << ":";
			}
			//Get default case
			SwitchCase *switchCaseDefaultSearcher = switchStmt->getSwitchCaseList();

			bool hasDefault = false;
			while (switchCaseDefaultSearcher != NULL) {
				if (isa<DefaultStmt>(switchCaseDefaultSearcher)) {
					DefaultStmt *stmt = cast<DefaultStmt>(switchCaseDefaultSearcher);
					parseStatement(stmt->getSubStmt(), breakLoc, continueLoc);
					out << "Jump @" << switchStmt->getLocEnd().getRawEncoding() << endl;
					hasDefault = true;
					break;
				}
				switchCaseDefaultSearcher = switchCaseDefaultSearcher->getNextSwitchCase();
			}

			if (!hasDefault)
			{
				out << "Jump @" << switchStmt->getLocEnd().getRawEncoding() << endl;
			}

			//parse all
			parseStatement(switchStmt->getBody(), switchStmt->getLocEnd().getRawEncoding(), continueLoc);
			out << "//SwitchEnd" << endl << endl;
			out << ":" << switchStmt->getLocEnd().getRawEncoding() << endl;
			FindBuffer.clear();
		}
		else if (isa<GotoStmt>(s))
		{
			GotoStmt *gotoStmt = cast<GotoStmt>(s);
			out << "Jump @" << gotoStmt->getLabel()->getNameAsString() << endl;
		}
		else if (isa<LabelStmt>(s))
		{
			LabelStmt *labelStmt = cast<LabelStmt>(s);
			out << ":" << labelStmt->getName() << endl;
		}
		else if (isa<GCCAsmStmt>(s))
		{
			GCCAsmStmt *asmstmt = cast<GCCAsmStmt>(s);
			out << asmstmt->getAsmString()->getString().str() << endl;
		}
		else
			Throw("Undefined statement \"" + string(s->getStmtClassName()) + "\"", rewriter, s->getLocStart());

			return true;
	}

	bool handleDecl(DeclStmt* decl) {
		for (DeclStmt::decl_iterator I = decl->decl_begin(), E = decl->decl_end(); I != E; ++I) {
			if (isa<VarDecl>(*I)) {
				VarDecl *var = cast<VarDecl>(*I);

				//out << +var->getStorageClass() << endl;
				if (var->getStorageClass() == SC_Static) {
					uint32_t oldStaticInc = 0;

					map<string, int>::iterator StaticFind = statics.find(dumpName(cast<NamedDecl>(*I)));
					if (StaticFind == statics.end()) {

						QualType type = var->getType();
						auto size = getSizeOfQualType(&type);
						// auto size  = context->getTypeInfoDataSizeInChars(varDecl->getType()).first.getQuantity();

						oldStaticInc = staticInc;

						statics.insert(make_pair(dumpName(cast<NamedDecl>(*I)), staticInc));
						staticInc += getSizeFromBytes(size);


					}
					else
						oldStaticInc = distance(statics.begin(), StaticFind);

					const Expr *initializer = var->getAnyInitializer();

					if (initializer) {
						if (isa<CXXConstructExpr>(initializer)) {
							out << "GetStaticP2 " << oldStaticInc << " //" << var->getName().str() << endl;
							parseExpression(initializer, true, false, true, var);
						}

						parseExpression(initializer, false, true);
						out << "SetStatic2 " << oldStaticInc << "  //" << var->getName().str() << endl;
					}

				}
				else
				{
					auto size = context->getTypeInfoDataSizeInChars(var->getType()).first.getQuantity();
					uint32_t oldLocalInc = localInc;
					locals.insert(make_pair(var->getName().str(), localInc));

					const ArrayType *arr = NULL;
					if ((arr = var->getType()->getAsArrayTypeUnsafe()) && arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl()) {
						if (isa<ConstantArrayType>(arr)) {
							const ConstantArrayType *cArrType = cast<const ConstantArrayType>(arr);
							size = getSizeOfCXXDecl(arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), true, false) * cArrType->getSize().getSExtValue();
							localInc += getSizeFromBytes(size);
						}
						else {
							out << "Unsupported decl" << endl;
						}

					}
					else if (var->getType()->getAsCXXRecordDecl()) {
						size = getSizeOfCXXDecl(var->getType()->getAsCXXRecordDecl(), true, false);
						localInc += getSizeFromBytes(size);
					}
					else
						localInc += getSizeFromBytes(size);

					const Expr *initializer = var->getAnyInitializer();
					if (initializer) {
						if (isa<CXXConstructExpr>(initializer)) {
							if (isa<ConstantArrayType>(var->getType())) {
								const ConstantArrayType *arr = cast<ConstantArrayType>(var->getType());
								static int vTableInitInc = 0;

								out << "Push 0" << endl;
								out << ":vTableConditional_" << vTableInitInc << endl;
								//for(int i=0; i<arr->getSize().getSExtValue(); i++) {
								out << "dup //index" << endl;
								out << "Push " << arr->getSize().getZExtValue() << endl;
								out << "cmplt" << endl;
								out << "JumpFalse @vTableEnd_" << vTableInitInc << endl;

								out << "dup #index" << endl;
								out << pFrame(oldLocalInc) << " //" << var->getNameAsString() << endl;
								out << "ArrayGetP " << getSizeFromBytes(getSizeOfCXXDecl(arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), true, true)) << "//index Array" << endl;
								parseExpression(initializer, true, false, true, var);
								out << "Push 1" << endl;
								out << "add" << endl;
								out << "Jump @vTableConditional_" << vTableInitInc << endl;
								out << ":vTableEnd_" << vTableInitInc << endl << endl;
								//}
								vTableInitInc++;
								return true;
							}
							out << pFrame(oldLocalInc) << " //" << var->getNameAsString() << endl;
							parseExpression(initializer, true, false, true, var);
							return true;
						}

						parseExpression(initializer, false, true);
						if (size > 4) {
							out << "Push " << size / 4 << " //Type Size" << endl;
							out << pFrame(oldLocalInc) << " //&" << var->getNameAsString() << endl;
							out << "FromStack" << endl;
						}
						else {
							out << frameSet(oldLocalInc) << "  //" << var->getName().str() << endl;
						}
					}

				}


			}
		}
		return true;
	}


	bool checkIntrinsic(const CallExpr *call) {
		std::string funcName = parseCast(cast<const CastExpr>(call->getCallee()));
		const Expr * const*argArray = call->getArgs();
		int argCount = call->getNumArgs();

		if (funcName == "@__strcopy" || funcName == "@__stradd" || funcName == "@__straddi" || funcName == "@__itos") {
			if (argCount != 3)
				out << "!!Invalid " << funcName << " parameters!" << endl;
			else
			{
				parseExpression(argArray[1]);
				parseExpression(argArray[0]);

				out << funcName << " ";
				if (isa<IntegerLiteral>(argArray[2])) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(argArray[2]);
					out << literal->getValue().getSExtValue() << endl;
				}
				else if (isa<CastExpr>(argArray[2])) {
					out << parseCast(cast<const CastExpr>(argArray[2])) << endl;
				}
				else
				{
					llvm::errs() << "Expected Literal String Max Length";
					return false;
				}
			}
			return true;
		}
		else if (funcName == "@__pop")
		{
			//	out << call->getExprLoc().
			if (argCount == 1)
			{
				if (isa<IntegerLiteral>(argArray[0]))
				{
					const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
					int intValue = intVal->getValue().getSExtValue();
					for (int i = 0; i < intValue; i++)
						out << "Pop" << endl;
				}
				else
					out << "!!Invalid " << funcName.substr(3) << " Parameters!";
			}
			else
				out << "Pop" << endl;
			return true;
		}
		else if (funcName == "@__pcall")
		{
			if (argCount < 1)
				out << "!!Invalid PCall Parameters" << endl;
			else
			{
				if (argCount > 1)
					for (int i = 1; i < argCount; i++)
						parseExpression(argArray[i], false, true);
				parseExpression(argArray[0], false, true);
				out << "//PCall Drops must be handled by user!" << endl;
				out << "pCall" << endl;
			}

			return true;
		}
		else if (funcName == "@__add" || funcName == "@__sub" || funcName == "@__mult" || funcName == "@__div")
		{
			if (argCount == 1)
			{
				out << "//" << funcName << endl;
				if (isa<IntegerLiteral>(argArray[0]))
				{
					const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
					long longVal = intVal->getValue().getSExtValue();

					if (funcName == "@__add" || funcName == "@__mult")
					{
						out << funcName.substr(3);
						out << ((longVal & 0xFF) == longVal ? "1 " : "2 ");
						out << longVal;
					}
					else if (funcName == "@__sub" || funcName == "@__div")
					{
						out << "Push " << longVal << endl;
						out << funcName.substr(3);
					}
				}
				else if (isa<Expr>(argArray[0]))
				{
					parseExpression(argArray[0]);
					out << funcName.substr(3);
				}
				else
				{
					out << "!!Invalid " << funcName.substr(1) << " Parameters!" << endl;
					return true;
				}
			}
			out << endl;
			return true;
		}
		else if (funcName == "@__getframe" || funcName == "@__getframep" || funcName == "@__setframe")
		{
			if (argCount == 1)
			{

				if (isa<IntegerLiteral>(argArray[0]))
				{
					out << funcName.substr(3);
					const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
					long intValue = intVal->getValue().getSExtValue();
					out << ((intValue & 0xFF) == intValue ? "1 " : "2 ");
					out << intValue << endl;
				}
				else if (isa<CastExpr>(argArray[0]))
				{

					const CastExpr* castExpr = cast<CastExpr>(argArray[0]);
					if (isa<DeclRefExpr>(castExpr->getSubExpr()))
					{
						const DeclRefExpr* declRef = cast<DeclRefExpr>(castExpr->getSubExpr());
						if (isa<VarDecl>(declRef->getDecl()))
						{

							const VarDecl* varDecl = cast<VarDecl>(declRef->getDecl());
							std::string name = varDecl->getName();
							if (locals.find(name) != locals.end())
							{
								int index = locals[name];
								out << funcName.substr(3);
								out << (((index & 0xFF) == index) ? "1 " : "2 ");
								out << index << " //" << name << endl;
							}
							else
								Throw("Could not find variable " + name + ".", rewriter, argArray[0]->getExprLoc());
						}
						else
							Throw("Invalid " + funcName.substr(3) + " Parameters.", rewriter, argArray[0]->getExprLoc());
					}
					else
						Throw("Invalid " + funcName.substr(3) + " Parameters.", rewriter, argArray[0]->getExprLoc());
				}
				else
					Throw("Invalid " + funcName.substr(3) + " Parameters.", rewriter, argArray[0]->getExprLoc());
			}
			else
			{
				Throw("Invalid " + funcName.substr(3) + " Parameters.", rewriter, argArray[0]->getExprLoc());
			}
			return true;
		}
		else if (funcName == "@__getglobal" || funcName == "@__getglobalp" || funcName == "@__getglobal")
		{
			if (funcName == "@__getglobal" || funcName == "@__getglobalp")
			{
				if (argCount == 1)
				{
					if (isa<IntegerLiteral>(argArray[0]))
					{
						const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
						int intValue = intVal->getValue().getSExtValue();

						out << funcName.substr(3);
						out << ((intValue & 0xFF) == intValue) ? "2 " : "3 ";
						out << intValue << endl;
					}
					else
						Throw("Expected Integer Literal.", rewriter, argArray[0]->getExprLoc());
				}
				else
					Throw("Invalid " + funcName.substr(3) + " Parameters.", rewriter, call->getExprLoc());
			}
			else if (funcName == "@__setglobal")
			{
				if (argCount == 2)
				{
					if (isa<IntegerLiteral>(argArray[0]))
					{
						parseExpression(argArray[1], false, true);
						const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
						int intValue = intVal->getValue().getSExtValue();

						out << funcName.substr(3);
						out << ((intValue & 0xFF) == intValue ? "2 " : "2 ");
						out << intValue << endl;
					}
					else
						Throw("Expected Integer Literal.", rewriter, argArray[0]->getExprLoc());
				}
				else if (argCount == 1) //allow for just SetGlobal, stack value expected
				{
					if (isa<IntegerLiteral>(argArray[0]))
					{
						const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
						int intValue = intVal->getValue().getSExtValue();

						out << funcName.substr(3);
						out << ((intValue & 0xFF) == intValue ? "2 " : "2 ");
						out << intValue << endl;
					}
					else
						Throw("Expected Integer Literal.", rewriter, argArray[0]->getExprLoc());
				}
				else
					Throw("Invalid " + funcName.substr(3) + " Parameters.", rewriter, call->getExprLoc());
			}
			return true;
		}

		return false;
	}

	string parseCast(const CastExpr *castExpr) {
		switch (castExpr->getCastKind()) {
		case clang::CK_LValueToRValue:
			break;
		case clang::CK_IntegralCast:
		{
			const Expr *e = castExpr->getSubExpr();
			if (isa<IntegerLiteral>(e)) {
				const IntegerLiteral *literal = cast<const IntegerLiteral>(e);
				return to_string(literal->getValue().getSExtValue());
			}
			else if (isa<FloatingLiteral>(e)) {
				const FloatingLiteral *literal = cast<const FloatingLiteral>(e);
				if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
					return to_string(literal->getValue().convertToFloat());
				else
					return to_string(literal->getValue().convertToDouble());
			}
			else {
				out << "unhandled cast (IK)" << endl;
			}
		}
		case clang::CK_FunctionToPointerDecay:
		{
			if (isa<DeclRefExpr>(castExpr->getSubExpr())) {
				const DeclRefExpr *declRef = cast<const DeclRefExpr>(castExpr->getSubExpr());
				if (isa<FunctionDecl>(declRef->getDecl())) {
					const FunctionDecl *decl = cast<const FunctionDecl>(declRef->getDecl());
					return getNameForFunc(decl);
				}
				else {
					out << "Unimplemented cast" << endl;
				}

			}
			else {
				out << "Unimplemented cast" << endl;
			}
		}
		break;
		default:
			out << "unimplemented cast" << endl;
		}
		return "";
	}

	string getNameForFunc(const FunctionDecl *decl) {
		if (isa<CXXMethodDecl>(decl)) {
			const CXXMethodDecl *methodDecl = cast<const CXXMethodDecl>(decl);
			const CXXRecordDecl *record = methodDecl->getParent();
			return "@" + record->getNameAsString() + "::" + methodDecl->getNameAsString();
		}
		else {
			return "@" + decl->getNameAsString();
		}
	}


	const DeclRefExpr *getDeclRefExpr(const Expr *e) {
		if (isa<DeclRefExpr>(e)) {
			return cast<const DeclRefExpr>(e);
		}
		else {
			for (auto *CS : e->clang::Stmt::children()) {
				if (isa<Expr>(CS)) {
					return getDeclRefExpr(cast<const Expr>(CS));
				}
			}
		}
		return NULL;
	}


	int parseExpression(const Expr *e, bool isAddr = false, bool isLtoRValue = false, bool printVTable = true, const NamedDecl *lastDecl = NULL) {
		if (isa<IntegerLiteral>(e)) {
			const IntegerLiteral *literal = cast<const IntegerLiteral>(e);
			out << iPush(literal->getValue().getSExtValue()) << endl;
		}
		else if (isa<FloatingLiteral>(e)) {
			const FloatingLiteral *literal = cast<const FloatingLiteral>(e);
			if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
				out << "PushF " << (double)literal->getValue().convertToFloat() << endl;
			else
				out << "PushF " << literal->getValue().convertToDouble() << endl;
			//Throw("My Error", rewriter, e);
		}
		else if (isa<CompoundLiteralExpr>(e)) {
			const CompoundLiteralExpr *cLit = cast<const CompoundLiteralExpr>(e);
			if (isa<InitListExpr>(cLit->getInitializer())) {
				const InitListExpr *init = cast<const InitListExpr>(cLit->getInitializer());
				for (unsigned int i = 0; i<init->getNumInits(); i++) {
					parseExpression(init->getInit(i));
				}
				// if(!printVTable)
				//     out << "iPush " << init->getNumInits() << " // numInitializers" << endl;
			}
			else {
				parseExpression(cLit->getInitializer());
				//                out << "Unimplemented CompoundLiteralExpr" << endl;
			}
		}
		else if (isa<StringLiteral>(e)) {
			const StringLiteral *literal = cast<const StringLiteral>(e);
			if (literal->getString().str().length() > 0)
				out << "PushString \"" << literal->getString().str() << "\"" << endl;
			else
				out << "PushString \"\"" << endl;
		}
		else if (isa<CallExpr>(e)) {
			const CallExpr *call = cast<const CallExpr>(e);
			if (checkIntrinsic(call))
				return 1;

			const Expr * const*argArray = call->getArgs();
			for (uint32_t i = 0; i < call->getNumArgs(); i++) {
				parseExpression(argArray[i], false, true);
			}

			if (isa<CastExpr>(call->getCallee()))
			{
				if (isa<PointerType>(call->getCallee()->getType()) && !call->getDirectCallee())
				{
					parseExpression(call->getCallee());
					out << "PCall" << endl;
				}
				else
				{
					if (!call->getDirectCallee()->isDefined() && call->getDirectCallee()->getStorageClass() != StorageClass::SC_Extern)
					{
						//could turn this into a native
						out << "//!Undefined Function" << endl;

						return 1;
					}
					else
					{
						if (((call->getDirectCallee()->isDefined() || call->getDirectCallee()->hasPrototype()) || call->getDirectCallee()->getNumParams() == 0) && call->getDirectCallee()->getStorageClass() != clang::StorageClass::SC_Extern)
							out << "Call " << parseCast(cast<const CastExpr>(call->getCallee())) << " //NumArgs: " << call->getNumArgs() << " " << endl;
						else {

							const QualType type = call->getDirectCallee()->getReturnType();
							out << "CallNative " << (parseCast(cast<const CastExpr>(call->getCallee())).c_str() + 1) << " " << call->getNumArgs() << " " << getSizeFromBytes(getSizeOfQualType(&type)) << endl;
						}
					}
				}
			}
			else if (isa<MemberExpr>(call->getCallee())) {
				const MemberExpr *expr = cast<const MemberExpr>(call->getCallee());
				if (isa<CXXMethodDecl>(expr->getMemberDecl())) {
					const CXXMethodDecl *method = cast<const CXXMethodDecl>(expr->getMemberDecl());
					if (method->isVirtualAsWritten()) {
						const CXXRecordDecl *classDecl = method->getParent();


						int offset = 0;
						printVirtualCall(classDecl, method, expr->getBase());
					}
					else {

						parseExpression(expr->getBase(), true);
						out << "call " << getNameForFunc(method) << " //NumArgs: " << call->getNumArgs() + 1 << " " << endl;
					}
				}
				else {
					out << "Unhandled Call Member Expression" << endl;
				}
			}
			else
				out << "Unimplemented call" << endl;


			if (call->getType()->isVoidType() == false) {
				if (!isLtoRValue) {
					out << "drop//Function Result unused" << endl;
					call->dump();
				}
			}

		}
		else if (isa<CastExpr>(e)) {
			const CastExpr *icast = cast<const CastExpr>(e);
			//out << icast->getCastKindName() << endl;
			switch (icast->getCastKind()) {
			case clang::CK_IntegralToFloating:
			{
				if (isa<IntegerLiteral>(icast->getSubExpr())) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(icast->getSubExpr());
					out << "PushF " << literal->getValue().getSExtValue() << ".0" << endl;
					return true;
				}
				else {
					parseExpression(icast->getSubExpr(), false, true);
					out << "itof" << endl;
					return true;
				}
			}
			case clang::CK_FloatingCast:
			case clang::CK_IntegralCast:
				parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
				break;
			case clang::CK_ArrayToPointerDecay:
				parseExpression(icast->getSubExpr(), true, false);
				break;
			case clang::CK_LValueToRValue:
			{
				parseExpression(icast->getSubExpr(), isAddr, true, printVTable);
				//const Expr *subE = icast->getSubExpr();

				//handleRValueDeclRef(subE);
				break;
			}
			case clang::CK_UncheckedDerivedToBase:
			{
				if (isa<DeclRefExpr>(icast->getSubExpr())) {
					const DeclRefExpr *declRef = cast<const DeclRefExpr>(icast->getSubExpr());
					CXXRecordDecl *base = declRef->getType()->getAsCXXRecordDecl();
					int offset = getSizeOfCXXDecl(base, false, false, icast->getType()->getAsCXXRecordDecl());
					if (offset != 0) {
						out << endl << iPush(offset / 4) << " //Base+" << offset << endl;
						parseExpression(declRef, true);
						out << "GetArrayP2 1  " << " //Cast : " << base->getDeclName().getAsString() << " to " << icast->getType()->getAsCXXRecordDecl()->getDeclName().getAsString() << endl;
					}
					else {
						parseExpression(icast->getSubExpr());
					}
				}
				else if (isa<CXXThisExpr>(icast->getSubExpr())) {
					const CXXThisExpr *expr = cast<const CXXThisExpr>(icast->getSubExpr());
					const PointerType *pointer = cast<const PointerType>(expr->getType());
					const PointerType *castPointer = cast<const PointerType>(icast->getType());

					CXXRecordDecl *base = pointer->getPointeeType()->getAsCXXRecordDecl();
					int offset = getSizeOfCXXDecl(base, false, false, castPointer->getPointeeCXXRecordDecl());
					if (offset != 0) {
						out << endl << iPush(offset / 4) << " //Base+" << offset << endl;
						parseExpression(expr, true);
						if (icast->getType()->getAsCXXRecordDecl())
							out << "GetArrayP2 1  " << " //Cast : " << base->getDeclName().getAsString() << " to " << icast->getType()->getAsCXXRecordDecl()->getDeclName().getAsString() << endl;
						else
							out << "GetArrayP2 1  " << " //Cast : " << base->getDeclName().getAsString() << " to " << icast->getType()->getPointeeCXXRecordDecl()->getDeclName().getAsString() << endl;
					}
					else {
						parseExpression(icast->getSubExpr());
					}
				}
				else {
					out << "unsupported cast" << endl;
				}


				break;

			}
			case clang::CK_DerivedToBase:
			{
				parseExpression(icast->getSubExpr());
				break;
			}
			case clang::CK_PointerToIntegral:
			{

				parseExpression(icast->getSubExpr(), false, true);
				break;
			}
			case clang::CK_IntegralToPointer:
			{
				//Fixed support for:
				//char* test = GET_STRING_PTR();
				//and other pointers
				parseExpression(icast->getSubExpr(), false, true);
				break;
			}
			case clang::CK_FloatingToIntegral:
			{

				parseExpression(icast->getSubExpr());
				out << "ftoi" << endl;
				break;
			}
			case clang::CK_NoOp:
			{
				parseExpression(icast->getSubExpr());
				break;
			}
			case clang::CK_FunctionToPointerDecay:
			{
				parseExpression(icast->getSubExpr());
				break;
			}
			case clang::CK_BitCast:
			{
				parseExpression(icast->getSubExpr());
				break;
			}
			case clang::CK_IntegralToBoolean:
			{
				parseExpression(icast->getSubExpr());
				break;
			}
			case clang::CK_FloatingComplexToReal:
			{
				parseExpression(icast->getSubExpr());
				break;
			}
			default:
				out << "Unhandled cast (CK) of type " << icast->getCastKindName() << endl;

			}
		}
		else if (isa<DeclRefExpr>(e)) {
			const DeclRefExpr *declref = cast<const DeclRefExpr>(e);

			if (isa<EnumConstantDecl>(declref->getDecl())) {
				const EnumConstantDecl *enumDecl = cast<const EnumConstantDecl>(declref->getDecl());
				int val = enumDecl->getInitVal().getSExtValue();
				out << iPush(val) << endl;
				return 1;
			}

			string key = declref->getNameInfo().getAsString();
			printDeclWithKey(key, isAddr, isLtoRValue, getSizeFromBytes(getSizeOfType(declref->getType().getTypePtr())));

			return true;
		}
		else if (isa<ArraySubscriptExpr>(e)) {
			return parseArraySubscriptExpr(e, isAddr, isLtoRValue);
		}
		else if (isa<ParenExpr>(e)) {
			const ParenExpr *parenExpr = cast<const ParenExpr>(e);
			parseExpression(parenExpr->getSubExpr(), isAddr, isLtoRValue);
		}
		else if (isa<UnaryOperator>(e)) {
			const UnaryOperator *op = cast<const UnaryOperator>(e);

			Expr *subE = op->getSubExpr();
			if (op->getOpcode() == UO_Minus) {
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					out << iPush(-(literal->getValue().getSExtValue())) << endl;
				}
				else if (isa<FloatingLiteral>(subE)) {
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);

					out << "PushF ";
					if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
						out << to_string(-1.0f*literal->getValue().convertToFloat());
					else
						out << to_string(-1.0*literal->getValue().convertToDouble());
					out << endl;
					// out << "fPush " << (double)-(literal->getValue().convertToDouble()) << endl;
				}
				return false;
			}
			else if (op->getOpcode() == UO_LNot) {
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					out << iPush(literal->getValue().getSExtValue()) << endl;

				}
				else if (isa<FloatingLiteral>(subE))
				{
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);
					out << "PushF " << literal->getValue().convertToDouble() << endl;

				}
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);

				}
				else
				{
					out << "unimplmented UO_Not" << endl;
				}
				out << "not" << endl;
				return true;

			}
			else if (op->getOpcode() == UO_AddrOf) {
				if (isa<ArraySubscriptExpr>(subE)) {
					parseArraySubscriptExpr(subE, true);
				}
				else if (isa<DeclRefExpr>(subE)) {
					parseExpression(subE, true, false);
				}
				else {
					parseExpression(subE, true, false);
				}
				return  true;

			}
			else if (op->getOpcode() == UO_Deref) {
				if (isa<ArraySubscriptExpr>(subE)) {
					parseArraySubscriptExpr(subE, false);
				}
				else if (isa<DeclRefExpr>(subE)) {
					parseExpression(subE, false, false);
				}
				else {
					parseExpression(subE, false, true);
				}
				if (isLtoRValue)
					out << "pGet" << endl;
				else
					out << "pSet" << endl;
				return true;
			}




			if (op->isPrefix()) {

				if (op->isIncrementOp()) {
					parseExpression(subE, false, true);
					out << "Push 1" << endl;
					out << "add" << endl;
					if (isLtoRValue)
						out << "dup" << endl;
					parseExpression(subE);
					return 1;
				}
				else if (op->isDecrementOp()) {
					parseExpression(subE, false, true);
					out << "Push 1" << endl;
					out << "sub" << endl;
					if (isLtoRValue)
						out << "dup" << endl;
					parseExpression(subE);
					return 1;
				}
			}
			else if (op->isPostfix()) {
				if (op->isIncrementOp()) {
					parseExpression(subE, false, true);
					if (isLtoRValue)
						out << "dup" << endl;
					out << "Push 1" << endl;
					out << "add" << endl;
					parseExpression(subE, false, false);
					return 1;
				}
				else if (op->isDecrementOp()) {
					parseExpression(subE, false, true);

					out << "Push 1" << endl;
					if (isLtoRValue)
						out << "dup" << endl;
					out << "sub" << endl;
					parseExpression(subE, false, false);
					return 1;
				}
			}
		}
		else if (isa<CXXThisExpr>(e)) {
			out << "GetFrame1 0 //\"this\"" << endl;
		}
		else if (isa<CXXConstructExpr>(e)) {
			const CXXConstructExpr *expr = cast<const CXXConstructExpr>(e);
			if (printVTable) {


				//out << "\n//VTableInit " << endl;
				//out << "call "
				if (expr->getType()->isArrayType()) {
					out << "dup" << endl;
					out << "call @" << expr->getType()->getAsArrayTypeUnsafe()->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl()->getNameAsString() << "::VTableInit" << endl;//printVTableInit(expr->getType()->getAsArrayTypeUnsafe()->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), lastDecl);
				}
				else {
					out << "dup" << endl;

					out << "call " << expr->getBestDynamicClassType()->getNameAsString() << "::VTableInit" << endl;//printVTableInit(expr->getBestDynamicClassType(), lastDecl);
				}
				//  out << " //End_VtableInit\n" << endl;
			}
			if (expr->getConstructor()->hasBody())
				out << "call " << getNameForFunc(expr->getConstructor()) << " // ctor" << endl;

		}
		else if (isa<BinaryOperator>(e)) {
			const BinaryOperator *bOp = cast<const BinaryOperator>(e);

			if (bOp->getOpcode() == BO_Assign) {

				parseExpression(bOp->getRHS(), isAddr, true, true);
				if (bOp->getRHS()->getType()->isStructureOrClassType()) {
					int size = getSizeOfType(bOp->getRHS()->getType().getTypePtr());
					out << "Push " << size << " //size " << endl;
					parseExpression(bOp->getLHS(), true);

					out << "FromStack" << endl;
				}
				else {
					parseExpression(bOp->getLHS());
				}

				return true;
			}

			switch (bOp->getOpcode()) {
			case BO_SubAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);//fixed with this line
				if (bOp->getLHS()->getType()->isFloatingType())
					out << "f";

				out << "Sub" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_AddAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				if (bOp->getLHS()->getType()->isFloatingType())
					out << "f";

				out << "Add" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_DivAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				if (bOp->getLHS()->getType()->isFloatingType())
					out << "f";
				out << "Div" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_MulAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				if (bOp->getLHS()->getType()->isFloatingType())
					out << "f";
				out << "Mult" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_OrAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				out << "Or" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_AndAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				out << "And" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_RemAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				if (bOp->getLHS()->getType()->isFloatingType())
					out << "f";
				out << "Mod" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_XorAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				out << "Xor" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_ShlAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				out << "CallNative shift_left 2 1" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			case BO_ShrAssign:
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);
				out << "CallNative shift_right 2 1" << endl;
				parseExpression(bOp->getLHS(), false, false);
				break;
			default:
			{
				parseExpression(bOp->getLHS(), false, true);
				parseExpression(bOp->getRHS(), false, true);


				if (bOp->getLHS()->getType()->isFloatingType()) {
					switch (bOp->getOpcode()) {
					case BO_EQ:
						out << "fCmpEQ" << endl;
						break;
					case BO_Mul:
						out << "fMult" << endl;
						break;
					case BO_Div:
						out << "fDiv" << endl;
						break;
					case BO_Rem:
						out << "FMod" << endl;
						break;
					case BO_Sub:
						out << "fSub" << endl;
						break;
					case BO_LT:
						out << "fCmpLT" << endl;
						break;
					case BO_GT:
						out << "fCmpGT" << endl;
						break;
					case BO_GE:
						out << "fCmpGE" << endl;
						break;
					case BO_LE:
						out << "fCmpLE" << endl;
						break;
					case BO_NE:
						out << "fCmpNE" << endl;
						break;
					case BO_LAnd:
					case BO_And:
						out << "And" << endl;
						break;
					case BO_Xor:
						out << "Xor" << endl;
						break;
					case BO_Add:
						out << "fAdd" << endl;
						break;
					case BO_LOr:
					case BO_Or:
						out << "Or " << endl;
						break;
					case BO_Shl:
						out << "CallNative shift_left 2 1";
						break;
					case BO_Shr:
						out << "CallNative shift_right 2 1";
						break;

					default:
						out << "unimplemented2 " << bOp->getOpcode() << endl;
					}

				}
				else {
					switch (bOp->getOpcode()) {
					case BO_EQ:
						out << "CmpEQ" << endl;
						break;
					case BO_Mul:
						out << "Mult" << endl;
						break;
					case BO_Div:
						out << "Div" << endl;
						break;
					case BO_Rem:
						out << "Mod" << endl;
						break;
					case BO_Sub:
						out << "Sub" << endl;
						break;
					case BO_LT:
						out << "CmpLT" << endl;
						break;
					case BO_GT:
						out << "CmpGT" << endl;
						break;
					case BO_GE:
						out << "CmpGE" << endl;
						break;
					case BO_LE:
						out << "CmpLE" << endl;
						break;
					case BO_NE:
						out << "CmpNE" << endl;
						break;
					case BO_LAnd:
					case BO_And:
						out << "And" << endl;
						break;
					case BO_Xor:
						out << "Xor" << endl;
						break;
					case BO_Add:
						out << "Add" << endl;
						break;
					case BO_LOr:
					case BO_Or:
						out << "Or" << endl;
						break;
					case BO_Shl:
						out << "CallNative shift_left 2 1" << endl;
						break;
					case BO_Shr:
						out << "CallNative shift_right 2 1" << endl;
						break;
					default:
						out << "unimplemented2 " << bOp->getOpcode() << endl;
					}
				}



				if (!isLtoRValue) {

					Warn("Unused operator \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());
					out << "Drop" << endl;
				}


			}

			}
		}
		else if (isa<MemberExpr>(e)) {
			const MemberExpr *E = cast<const MemberExpr>(e);
			Expr *BaseExpr = E->getBase();


			if (E->isArrow()) {
				parseExpression(BaseExpr, false);

			}
			else
				parseExpression(BaseExpr, true);




			int offset = 0;
			NamedDecl *ND = E->getMemberDecl();


			const CXXRecordDecl *classDecl = NULL;
			if (isa<PointerType>(BaseExpr->getType().getTypePtr())) {
				const PointerType *pointer = cast<const PointerType>(BaseExpr->getType().getTypePtr());
				classDecl = pointer->getPointeeType()->getAsCXXRecordDecl();
			}
			if (classDecl) //BaseExpr->getType()->getAsCXXRecordDecl() != NULL || isa<CXXThisExpr>(BaseExpr)) {
			{
				offset = getCXXOffsetOfNamedDecl(classDecl, ND);
			}
			else
			{
				if (auto *Field = dyn_cast<FieldDecl>(ND)) {
					const RecordDecl *record = Field->getParent();
					if (record->isUnion())
						offset = 0;
					else {
						for (const auto *CS : record->fields()) {
							if (CS == Field)
								break;

							const  QualType type = CS->getType();
							int temp = getSizeOfQualType(&type);
							offset += max(temp, 4);
						}
					}
				}
			}

			int size = getSizeFromBytes(offset);

			out << "Push " << size * 4 << " // ." << ND->getName().str() << "\r\nAdd\r\n";


			if (isLtoRValue)
				out << "pGet\r\n";
			else if (isAddr)
			{
				return 1;
			}
			else
				out << "pSet\r\n";

			return 1;
		}
		else if (isa<InitListExpr>(e))
		{
			//{ 1, 3, 7 }; support
			const InitListExpr *I = cast<const InitListExpr>(e);
			for (unsigned int i = 0; i < I->getNumInits(); i++)
				parseExpression(I->getInit(i), false, true);
		}
		else if (isa<ImplicitValueInitExpr>(e))
		{
			const ImplicitValueInitExpr *im = cast<const ImplicitValueInitExpr>(e);
			QualType qt = im->getType();
			uint32_t size = getSizeFromBytes(getSizeOfQualType(&qt));
			for (uint32_t i = 0; i < size; i++)
				out << "Push_0" << endl;
		}
		else if (isa<UnaryExprOrTypeTraitExpr>(e))
		{

			const UnaryExprOrTypeTraitExpr *ueTrait = cast<const UnaryExprOrTypeTraitExpr>(e);
			//out << ueTrait->getKind() << endl;
			switch (ueTrait->getKind())
			{
			case UnaryExprOrTypeTrait::UETT_SizeOf:
			{
				int size = 0;

				if (ueTrait->isArgumentType())
					size = getSizeOfType(ueTrait->getArgumentType().getTypePtr());
				else
					size = context->getTypeInfoDataSizeInChars(ueTrait->getArgumentExpr()->getType()).first.getQuantity();

				//Pause("SIZE: " + to_string(size) + "\r\n");
				if (isLtoRValue)
					out << "Push " << size << endl;

			}
			break;
			default:
				out << "!!Unsupported UnaryExprOrTypeTrait" << endl;
				break;
			}
		}
		else if (isa<ConditionalOperator>(e))
		{
			if (!isLtoRValue)
				Throw("Invalid Use Of Operator", rewriter, e->getExprLoc());
			const ConditionalOperator *cond = cast<const ConditionalOperator>(e);

			parseExpression(cond->getCond(), false, true);
			out << "JumpFalse @" << cond->getRHS()->getLocStart().getRawEncoding() << endl;
			parseExpression(cond->getLHS(), false, true);
			out << "Jump @" << cond->getLHS()->getLocEnd().getRawEncoding() << endl;

			out << ":" << cond->getRHS()->getLocStart().getRawEncoding() << endl;
			parseExpression(cond->getRHS(), false, true);
			out << ":" << cond->getLHS()->getLocEnd().getRawEncoding() << endl;
		}
		else if (isa<ImaginaryLiteral>(e))
		{
			Warn("Imaginary literals aren't supported", rewriter, e->getExprLoc());
			const ImaginaryLiteral *literal = cast<ImaginaryLiteral>(e);
			const Expr* item = literal->getSubExpr();

			out << "imaginary_literal_push" << endl;

		}
		else {
			out << "unimplemented3 " << endl;

		}
		return -1;
	}

	uint32_t getCXXOffsetOfNamedDecl(const CXXRecordDecl *classDecl, const NamedDecl *ND, const CXXRecordDecl *prevDecl = NULL) {
		bool found = false;
		bool foundVirt = false;
		int offset = 0;

		for (auto VBI : classDecl->bases()) {

			const CXXBaseSpecifier baseSpec = VBI;
			const CXXRecordDecl *baseDecl = baseSpec.getType()->getAsCXXRecordDecl();


			offset += getCXXOffsetOfNamedDecl(baseDecl, ND, classDecl);
			//            for(CXXMethodDecl *VFI : baseDecl->methods()) {
			//                if(VFI->isVirtual()) {
			//                    offset+=4;
			//                    break;
			//                }
			//            }
			//            for(const FieldDecl *CS : baseDecl->fields()) {
			//                
			//                if(CS->Decl::isFirstDecl() == false)
			//                    continue;
			//                if(CS == ND) {
			//                    found = true;
			//                }
			//                
			//                const  QualType type = CS->getType();
			//                int temp = getSizeOfQualType(&type);
			//                offset += max(temp, 4);
			//            }
		}

		for (CXXMethodDecl *VFI : classDecl->methods()) {
			if (VFI->isVirtualAsWritten()) {
				offset += 4;
				break;
			}
		}
		if (classDecl->isUnion()) {
			return 0;

		}
		else {
			for (const FieldDecl *CS : classDecl->fields()) {
				if (CS->Decl::isFirstDecl() == false)
					continue;
				if (CS == ND) {
					found = true;

					break;
				}



				const  QualType type = CS->getType();
				int temp = getSizeOfQualType(&type);
				offset += max(temp, 4);
			}
		}
		return offset;

	}


	bool parseArraySubscriptExpr(const Expr *e, bool addrOf, bool LValueToRValue = false) {
		const ArraySubscriptExpr *arr = cast<const ArraySubscriptExpr>(e);
		const Expr *base = arr->getBase();
		const Expr *index = arr->getIdx();


		parseExpression(index, false, true);
		parseExpression(base, true);
		const DeclRefExpr *declRef = getDeclRefExpr(base);
		const Type *type = base->getType().getTypePtr();//declRef->getType().getTypePtr()->getArrayElementTypeNoTypeQual();
		if (type == NULL) {
			type = declRef->getType().getTypePtr();
		}
		if (declRef) {
			declRef->getType();
		}
		if (type->isPointerType())
			type = type->getPointeeType().getTypePtr();

		if (LValueToRValue)
			out << "GetArray2 " << getSizeFromBytes(getSizeOfType(type)) << endl;
		else if (addrOf)
			out << "GetArrayP2 " << getSizeFromBytes(getSizeOfType(type)) << endl;
		else
			out << "SetArray2 " << getSizeFromBytes(getSizeOfType(type)) << endl;

		return true;
	}

	bool VisitFunctionDecl(FunctionDecl *f) {
		// Only function definitions (with bodies), not declarations.
		int funcNum = 0;
		if (f->hasBody()) {
			if (isa<CXXConstructorDecl>(f))
				return true;

			Stmt *FuncBody = f->getBody();

			int32_t paramSize = 0;
			for (uint32_t i = 0; i<f->getNumParams(); i++)
			{
				paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
			}


			out << endl << "//Loc: " << f->getBody()->getLocStart().getRawEncoding() << endl;

			string name = dumpName(cast<NamedDecl>(f));

			out << ":" << name << endl;

			if (name == "main")
			{
				QualType type = f->getReturnType();
				MainRets = Utils::Math::DivInt(getSizeOfQualType(&type), 4);
			}



			out << "Function " << to_string(paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0)) << " ";

			int32_t FunctionStackCountLocation = out.tellp();

			//write stack count buffer as 5 spaces because max stack size of function is 65536
			out << "     ";


			out << "\r\n//" + getNameForFunc(f) + "\r\n";

			currFunction = f;
			locals.clear();
			if (isa<CXXMethodDecl>(f))
				localInc = 1;
			else
				localInc = 0;

			for (uint32_t i = 0; i<f->getNumParams(); i++) {
				handleParmVarDecl(f->getParamDecl(i));
			}
			localInc += 2;
			parseStatement(FuncBody);

			if (f->getReturnType().getTypePtr()->isVoidType()) {
				int32_t paramSize = 0;
				for (uint32_t i = 0; i < f->getNumParams(); i++) {
					paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
				}

				out << "Return " << paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0) << " 0\r\n";
			}
			else if (f->hasImplicitReturnZero())
			{
				int32_t paramSize = 0;
				for (uint32_t i = 0; i < f->getNumParams(); i++) {
					paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
				}
				out << "Push_0\r\n";
				out << "Return " << paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0) << " 1\r\n";
			}

			//Throw(f->getNameAsString() + ": not all control paths return a value", rewriter, f->getLocEnd());

			uint32_t FunctionStackCount = localInc - isa<CXXMethodDecl>(f);
			string FunctionStackCountStr = to_string(FunctionStackCount);

			if (FunctionStackCount > 65536)
				Throw("Function \"" + f->getNameAsString() + "\" has a stack size of " + FunctionStackCountStr + " when the max is 65536", rewriter, f->getLocStart());
			else
			{
				out.seekp(FunctionStackCountLocation);
				out << FunctionStackCountStr;
				out.seekp(0, ios::end);
			}
			//out << dumpName(cast<NamedDecl>(f)) << endl;

			//outfile << out.str();
			//out.str(string(""));
			//out.clear();

		}

		return true;
	}


	uint32_t printVirtualCall(const CXXRecordDecl *classDecl, const CXXMethodDecl *method, Expr *baseExpr, const CXXRecordDecl *superDecl = NULL) {
		int offset = 0;


		if (superDecl == NULL)
			superDecl = classDecl;

		int vtableInc = 0;
		for (auto VBI : classDecl->bases()) {


			const CXXBaseSpecifier baseSpec = VBI;
			const CXXRecordDecl *baseDecl = baseSpec.getType()->getAsCXXRecordDecl();
			vtableInc += printVirtualCall(baseDecl, method, baseExpr, superDecl);
		}

		int func = 0;
		for (CXXMethodDecl *VFI : classDecl->methods()) {

			if (VFI->isVirtual()) {

				const CXXMethodDecl *VFII = VFI->getCorrespondingMethodInClass(superDecl);
				if (VFI->getName() == method->getName()) { //getLocStart(VFI) != getLocStart(VFII)) {

														   //out << "push " << func << endl;
					parseExpression(baseExpr);
					out << endl << "dup" << endl << GetImm(getSizeFromBytes(getSizeOfCXXDecl(superDecl, false, true, classDecl)) + vtableInc) << " //" << classDecl->getDeclName().getAsString() << "::VTablePtr[" << getSizeFromBytes(getSizeOfCXXDecl(superDecl, false, true, classDecl)) + vtableInc << "]" << endl;
					out << GetImm(func) << " //VTable[" << func << "] //" << getNameForFunc(method) << endl;
					out << "pcall" << " //(*)(" << getNameForFunc(method) << "());" << endl;


				}
				func++;
				// }

			}

		}
		return getSizeOfVTable(classDecl);


	}

	uint32_t printVTableInit(const CXXRecordDecl *classDecl, const NamedDecl *classLoc) {
		int offset = 0;


		//string key = classLoc->getDeclName().getAsString();
		int vtableInc = 0;
		for (auto VBI : classDecl->bases()) {


			const CXXBaseSpecifier baseSpec = VBI;
			const CXXRecordDecl *baseDecl = baseSpec.getType()->getAsCXXRecordDecl();
			//vtableInc += printVTableInit(baseDecl, classLoc);
			bool foundVirt = false;
			int func = 0;
			for (CXXMethodDecl *VFI : baseDecl->methods()) {

				if (VFI->isVirtual()) {
					if (!foundVirt) {



						//                        out << "StaticGet 0 //\"this\"" << endl;
						uint32_t size = getSizeFromBytes(getSizeOfCXXDecl(classDecl, false, false));
						uint32_t sizeBase = getSizeFromBytes(getSizeOfCXXDecl(classDecl, false, true, baseDecl));
						out << endl << "//SetVTablePtr" << endl;
						out << "getFrame1 0" << endl;
						out << "GetImmp " << size + vtableInc << " //" << baseDecl->getDeclName().getAsString() << "::VTableStart" << endl;
						out << "getFrame1 0" << endl;
						out << SetImm(sizeBase) << " //" << baseDecl->getDeclName().getAsString() << "::VTablePtr" << endl;
						foundVirt = true;
						out << endl << "//SetVTableFunctionPtrs" << endl;
					}





					const CXXMethodDecl *VFII = VFI->getCorrespondingMethodInClass(classDecl);

					if (VFI != VFII) { //getLocStart(VFI) != getLocStart(VFII)) {
						const Stmt *body = VFII->FunctionDecl::getBody();

						out << "PushFunction " << getNameForFunc(VFII) << " // &" << VFII->getDeclName().getAsString() << endl;
						out << "getFrame1 0" << endl;
						out << SetImm(getSizeFromBytes(getSizeOfCXXDecl(classDecl, false, false)) + vtableInc + func++) << endl;


					}
					else {
						out << "PushFunction " << getNameForFunc(VFII) << " // " << VFII->getDeclName().getAsString() << endl;
						out << "getFrame1 0" << endl;
						out << SetImm(getSizeFromBytes(getSizeOfCXXDecl(classDecl, false, false)) + vtableInc + func++) << endl;

					}
				}

			}
			if (foundVirt)
				out << "//EndVTableFunctionPtrs" << endl;



			vtableInc += getSizeOfVTable(baseDecl);
		}


		return 0;
	}



	uint64_t getLocStart(const CXXMethodDecl *VFFI) {
		Stmt *body = VFFI->getBody();
		if (body == NULL) {
			body = VFFI->getTemplateInstantiationPattern()->getBody();
		}
		return body->getLocStart().getRawEncoding();
	}
	bool VisitCXXRecordDecl(CXXRecordDecl *d) {

		//if(!d->hasBody())
		//   return false;
		//constructors
		for (auto *CS : d->ctors()) {
			if (!CS->hasBody())
				continue;
			localInc = 1;
			locals.clear();
			locals.insert(make_pair(d->getDeclName().getAsString(), 0));

			out << endl << endl;
			out << ":" << getLocStart(CS) << endl << ":" << CS->getDeclName().getAsString() << endl << "Function " << CS->getNumParams() + 1 << "//" << getNameForFunc(CS) << endl;
			currFunction = CS;

			for (auto *PI : CS->params()) {
				handleParmVarDecl(PI);
			}
			localInc = (3 + CS->getNumParams());
			for (auto *IS : CS->inits()) {

				if (IS->getMember()) {

					parseExpression(IS->getInit());
					out << "GetFrame1 0 //\"this\"" << endl;
					out << SetImm(getSizeFromBytes(getCXXOffsetOfNamedDecl(d, IS->getMember()))) << " //" << IS->getMember()->getDeclName().getAsString() << endl;
				}
				else {
					if (isa<CXXConstructExpr>(IS->getInit())) {
						const CXXConstructExpr *constructor = cast<const CXXConstructExpr>(IS->getInit());
						for (auto *ARG : constructor->arguments()) {
							parseExpression(ARG);
						}
						out << "GetFrame1 0 //\"this\"" << endl;
					}
					parseExpression(IS->getInit(), false, false, false);
				}
			}


			parseStatement(CS->getBody());

			int32_t paramSize = 0;
			for (uint32_t i = 0; i < currFunction->getNumParams(); i++) {
				paramSize += getSizeFromBytes(getSizeOfType(currFunction->getParamDecl(i)->getType().getTypePtr()));
			}
			out << "Return " << paramSize + (isa<CXXMethodDecl>(currFunction)) << " 0" << endl;

			out << "#FuncEnd L " << localInc - isa<CXXMethodDecl>(CS) << endl << endl;

			if (d->isPolymorphic()) {
				out << endl << endl;
				out << "Function 1 1 @" << d->getNameAsString() << "::VTableInit" << endl;
				printVTableInit(d, NULL);
				out << "Return 1 0" << endl;
				out << "//Var Count 2" << endl;

			}
		}
		return true;
	}

public:
	int32_t MainRets = -1;
	set<std::string> FindBuffer;
	Rewriter &TheRewriter;
	ASTContext *context;
	stringstream out;
	string outfile;
	const FunctionDecl *currFunction;
};

class GlobalsVisitor : public RecursiveASTVisitor<GlobalsVisitor> {
public:
	GlobalsVisitor(Rewriter &R, ASTContext *context) : TheRewriter(R), context(context) {}

	int32_t ParseLiteral(const Expr *e, bool isAddr = false, bool isLtoRValue = false, bool printVTable = true, const NamedDecl *lastDecl = NULL)
	{
		if (isa<IntegerLiteral>(e)) {
			const IntegerLiteral *literal = cast<const IntegerLiteral>(e);
			InitializationStack.push({ (int32_t)literal->getValue().getSExtValue(), FBWT_INT });
		}
		else if (isa<FloatingLiteral>(e)) {
			const FloatingLiteral *literal = cast<const FloatingLiteral>(e);

			float fltliteral;

			if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
				fltliteral = literal->getValue().convertToFloat();
			else
				fltliteral = (float)literal->getValue().convertToDouble();

			InitializationStack.push({ *(int32_t*)&fltliteral, FBWT_FLOAT });
		}
		else if (isa<CompoundLiteralExpr>(e)) {
			const CompoundLiteralExpr *cLit = cast<const CompoundLiteralExpr>(e);
			if (isa<InitListExpr>(cLit->getInitializer())) {
				const InitListExpr *init = cast<const InitListExpr>(cLit->getInitializer());
				for (unsigned int i = 0; i<init->getNumInits(); i++) {
					ParseLiteral(init->getInit(i));
				}
				// if(!printVTable)
				//     out << "iPush " << init->getNumInits() << " // numInitializers" << endl;
			}
			else {
				ParseLiteral(cLit->getInitializer());
				//                out << "Unimplemented CompoundLiteralExpr" << endl;
			}
		}
		else if (isa<StringLiteral>(e)) {
			//first param is string size

			const StringLiteral *literal = cast<const StringLiteral>(e);
			if (literal->getString().str().length() > 0)
			{
				InitializationStack.push({ 0, FBWT_ARRAY });

				int32_t StrIntSize = (literal->getString().str().length() + 4 - 1) & ~3;
				int32_t StrRem = StrIntSize - literal->getString().str().length();

				int32_t LoopSize = StrIntSize / 4;

				for (int32_t i = 0; i < LoopSize; i++)
				{
					if (i < LoopSize - 1)
						ArrayOut.push_back(Utils::Bitwise::SwapEndian(*(int32_t*)(literal->getString().str().c_str() + (i * 4))));
					else
					{
						int32_t buffer = 0;
						memcpy(&buffer, literal->getString().str().substr(StrIntSize - 4, StrRem).c_str(), 4 - StrRem);
						ArrayOut.push_back(Utils::Bitwise::SwapEndian(buffer));
						if (StrRem == 4)//if str size is equal to a mult of 4 we need to add a null terminator
							ArrayOut.push_back(0);
					}

				}
			}
			return true;

		}
		else if (isa<ImplicitCastExpr>(e))
		{
			const ImplicitCastExpr *icast = cast<const ImplicitCastExpr>(e);

			switch (icast->getCastKind())
			{
			case CK_ArrayToPointerDecay://char* x = "hello"; is unsupported
				if (isa<StringLiteral>(icast->getSubExpr()))
				{
					Throw("Static initialization of a char* is forbidden", rewriter, icast->getSubExpr()->getExprLoc());
				}
				else
					Throw("Unimplemented CK_ArrayToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()));
				break;

			case CK_IntegralCast://int x = 5.0;
			case CK_FloatingCast://float x = 6.9;
				ParseLiteral(icast->getSubExpr(), isAddr, isLtoRValue);
				break;
			case CK_IntegralToFloating://float x = 5;
				if (isa<IntegerLiteral>(icast->getSubExpr())) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(icast->getSubExpr());
					float fltliteral = literal->getValue().getSExtValue();
					InitializationStack.push({ FloatToInt(fltliteral), FBWT_FLOAT });
				}
				else
				{
					ParseLiteral(icast->getSubExpr(), false, true);
					InitializationStack.push({ FloatToInt((float)IS_Pop().bytes), FBWT_FLOAT });
				}
				break;
			case CK_FloatingToIntegral:
				if (isa<FloatingLiteral>(icast->getSubExpr())) {
					const FloatingLiteral *literal = cast<const FloatingLiteral>(icast->getSubExpr());
					float fltliteral;
					if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
						fltliteral = literal->getValue().convertToFloat();
					else
						fltliteral = (float)literal->getValue().convertToDouble();
					InitializationStack.push({ (int32_t)IntToFloat(fltliteral), FBWT_INT });
				}
				else
				{
					ParseLiteral(icast->getSubExpr(), false, true);
					InitializationStack.push({ (int32_t)IntToFloat(IS_Pop().bytes), FBWT_INT });
				}
				break;

			case CK_FunctionToPointerDecay://int (*ggg)(int, float) = test; // test is a function

				if (isa<DeclRefExpr>(icast->getSubExpr())) {
					const DeclRefExpr *declRef = cast<const DeclRefExpr>(icast->getSubExpr());
					if (isa<FunctionDecl>(declRef->getDecl())) {
						const FunctionDecl *decl = cast<const FunctionDecl>(declRef->getDecl());

						if (isa<CXXMethodDecl>(decl)) {
							const CXXMethodDecl *methodDecl = cast<const CXXMethodDecl>(decl);
							const CXXRecordDecl *record = methodDecl->getParent();

							InitializationStack.push({ 0, FBWT_FUNCTION_PTR });

							string funcname = "GetLoc(\"" + record->getNameAsString() + "::" + methodDecl->getNameAsString() + "\")";
							int64_t length = Utils::Math::CeilDivInt(funcname.length(), 4);

							ArrayOut.resize(funcname.length() % 4 == 0 ? length + 1 : length, 0);
							memcpy(ArrayOut.data(), funcname.c_str(), funcname.length());
						}
						else
						{

							InitializationStack.push({ 0, FBWT_FUNCTION_PTR });


							string funcname = "GetLoc(\"" + decl->getNameAsString() + "\")";
							int64_t length = Utils::Math::CeilDivInt(funcname.length(), 4);

							ArrayOut.resize(funcname.length() % 4 == 0 ? length + 1 : length, 0);
							memcpy(ArrayOut.data(), funcname.c_str(), funcname.length());
						}

					}
					else Throw("Unimplemented CK_FunctionToPointerDecay DeclRefExpr for " + string(declRef->getStmtClassName()));

				}
				else Throw("Unimplemented CK_FunctionToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()));

				break;

			default:
				Throw("Unimplemented ImplicitCastExpr of type " + string(icast->getCastKindName()));

			}


		}
		else if (isa<CastExpr>(e)) {
			const CastExpr *icast = cast<const CastExpr>(e);
			switch (icast->getCastKind()) {
			case clang::CK_IntegralToFloating:
			{
				if (isa<IntegerLiteral>(icast->getSubExpr())) {

					const IntegerLiteral *literal = cast<const IntegerLiteral>(icast->getSubExpr());
					InitializationStack.push({ FloatToInt((float)literal->getValue().getSExtValue()), FBWT_FLOAT });
					return true;
				}
				else {
					Throw("Unable to cast a non literal on initialization of a static var");
				}
			}
			case clang::CK_FloatingCast:
			case clang::CK_IntegralCast:
				ParseLiteral(icast->getSubExpr(), isAddr, isLtoRValue);
				break;
			case clang::CK_ArrayToPointerDecay:

				ParseLiteral(icast->getSubExpr(), true, false);
				break;
			case clang::CK_LValueToRValue:
			{
				ParseLiteral(icast->getSubExpr(), isAddr, true, printVTable);
				//const Expr *subE = icast->getSubExpr();

				//handleRValueDeclRef(subE);
				break;
			}
			case clang::CK_DerivedToBase:
			{
				ParseLiteral(icast->getSubExpr());
				break;
			}
			case clang::CK_PointerToIntegral:
			{
				ParseLiteral(icast->getSubExpr());
				break;
			}
			case clang::CK_FloatingToIntegral:
			{
				ParseLiteral(icast->getSubExpr());
				InitializationStack.push({ (int32_t)IntToFloat(IS_Pop().bytes), FBWT_INT });
				break;
			}
			case clang::CK_NoOp:
			{
				ParseLiteral(icast->getSubExpr());
				break;
			}
			case clang::CK_BitCast:
			{
				ParseLiteral(icast->getSubExpr());
				break;
			}
			default:
				Throw("Cast " + string(icast->getCastKindName()) + " is unimplemented for a static define");

			}
		}
		else if (isa<DeclRefExpr>(e)) {
			//const DeclRefExpr *declref = cast<const DeclRefExpr>(e);
			//
			//if (isa<EnumConstantDecl>(declref->getDecl())) {
			//	const EnumConstantDecl *enumDecl = cast<const EnumConstantDecl>(declref->getDecl());
			//	int val = enumDecl->getInitVal().getSExtValue();
			//	out << iPush(val) << endl;
			//	return 1;
			//}
			//
			//string key = declref->getNameInfo().getAsString();
			//printDeclWithKey(key, isAddr, isLtoRValue, getSizeFromBytes(getSizeOfType(declref->getType().getTypePtr())));
			Throw("DeclRefExpr");
			//int k;
			//int x = &k;
			return true;
		}
		else if (isa<ArraySubscriptExpr>(e)) {
			Throw("parseArraySubscriptExpr");
			//return parseArraySubscriptExpr(e, isAddr, isLtoRValue);
		}
		else if (isa<ParenExpr>(e)) {
			const ParenExpr *parenExpr = cast<const ParenExpr>(e);
			ParseLiteral(parenExpr->getSubExpr(), isAddr, isLtoRValue);
		}
		else if (isa<UnaryOperator>(e)) {
			const UnaryOperator *op = cast<const UnaryOperator>(e);

			Expr *subE = op->getSubExpr();
			if (op->getOpcode() == UO_Minus) {
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					InitializationStack.push({ (int32_t)-literal->getValue().getSExtValue(), FBWT_INT });
				}
				else if (isa<FloatingLiteral>(subE)) {
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);
					float fltliteral;
					if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
						fltliteral = literal->getValue().convertToFloat();
					else
						fltliteral = (float)literal->getValue().convertToDouble();
					InitializationStack.push({ FloatToInt(-1.0f*fltliteral), FBWT_FLOAT });
				}
				else Throw("UO_Minus not caught");
				return false;
			}
			else if (op->getOpcode() == UO_LNot) {
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					InitializationStack.push({ !literal->getValue().getSExtValue(), FBWT_INT });

				}
				else if (isa<FloatingLiteral>(subE)) {
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);
					float fltliteral;
					if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
						fltliteral = literal->getValue().convertToFloat();
					else
						fltliteral = (float)literal->getValue().convertToDouble();
					InitializationStack.push({ FloatToInt(!fltliteral), FBWT_FLOAT });

				}
				else if (isa<Expr>(subE)) {
					ParseLiteral(subE, isAddr, isLtoRValue);

				}
				else {
					Throw("unimplmented UO_Not");
				}
				return true;

			}
			else if (op->getOpcode() == UO_AddrOf) {
				if (isa<ArraySubscriptExpr>(subE)) {
					//parseArraySubscriptExpr(subE, true);
					Throw("parseArraySubscriptExpr");
				}
				else if (isa<DeclRefExpr>(subE)) {
					Throw("DeclRefExpr");
					//parseExpression(subE, true, false);
				}
				else {
					ParseLiteral(subE, true, false);
				}
				return  true;

			}


		}
		else if (isa<BinaryOperator>(e)) {
			const BinaryOperator *bOp = cast<const BinaryOperator>(e);

			if (bOp->getOpcode() == BO_Assign) {

				//parseExpression(bOp->getRHS(), isAddr, true, false);
				//if (bOp->getRHS()->getType()->isStructureOrClassType()) {
				//	int size = getSizeFromBytes(getSizeOfType(bOp->getRHS()->getType().getTypePtr()));
				//	out << "Push " << size << " //size " << endl;
				//	parseExpression(bOp->getLHS(), true);
				//
				//	out << "ArrayFromStack" << endl;
				//}
				//else {
				//	parseExpression(bOp->getLHS());
				//}
				//
				//
				Pause("BO_Assign");
				return true;
			}

			ParseLiteral(bOp->getLHS(), false, true);
			ParseLiteral(bOp->getRHS(), false, true);


			if (bOp->getLHS()->getType()->isFloatingType()) {
#define IS_PushF(op)\
				float stk1 = IntToFloat(IS_Pop().bytes);\
				float stk2 = IntToFloat(IS_Pop().bytes);\
				InitializationStack.push({ stk2 op stk1, FBWT_FLOAT });
#define IS_PushFc(op)\
				float stk1 = IntToFloat(IS_Pop().bytes);\
				float stk2 = IntToFloat(IS_Pop().bytes);\
				InitializationStack.push({ FloatToInt(stk2 op stk1), FBWT_FLOAT });
#define IS_PushFi(op)\
				int32_t stk1 = IS_Pop().bytes;\
				int32_t stk2 = IS_Pop().bytes;\
				InitializationStack.push({ stk2 op stk1, FBWT_FLOAT });

				switch (bOp->getOpcode()) {
				case BO_EQ: { IS_PushF(== ); } break;
				case BO_Mul: { IS_PushFc(*); } break;
				case BO_Div: { IS_PushFc(/ ); } break;
				case BO_Rem:
				{
					float stk1 = IntToFloat(IS_Pop().bytes);
					float stk2 = IntToFloat(IS_Pop().bytes);
					InitializationStack.push({ FloatToInt(fmod(stk2, stk1)), FBWT_FLOAT });
				}
				break;
				case BO_Sub: { IS_PushFc(-); } break;
				case BO_Add: { IS_PushFc(+); } break;
				case BO_LT: { IS_PushF(<); } break;
				case BO_GT: { IS_PushF(>); } break;
				case BO_GE: { IS_PushF(>= ); } break;
				case BO_LE: { IS_PushF(<= ); } break;
				case BO_NE: { IS_PushF(!= ); } break;
				case BO_LAnd: { IS_PushF(&&); } break;
				case BO_And: { IS_PushFi(&); } break;
				case BO_Xor: { IS_PushFi(^); } break;
				case BO_LOr: { IS_PushF(|| ); } break;
				case BO_Or: { IS_PushFi(| ); } break;
				case BO_Shl: { IS_PushFi(<< ); } break;
				case BO_Shr: { IS_PushFi(>> ); } break;

				default:
					Throw("flt operator " + to_string(bOp->getOpcode()) + " is unimplemented for a static define");
				}

			}
			else {
#define IS_PushI(op)\
				int32_t stk1 = IS_Pop().bytes;\
				int32_t stk2 = IS_Pop().bytes;\
				InitializationStack.push({ stk2 op stk1, FBWT_INT });

				switch (bOp->getOpcode()) {
				case BO_EQ: { IS_PushI(== ); } break;
				case BO_Mul: { IS_PushI(*); } break;
				case BO_Div: { IS_PushI(/ ); } break;
				case BO_Rem: { IS_PushI(%); } break;
				case BO_Sub: { IS_PushI(-); } break;
				case BO_LT: { IS_PushI(<); } break;
				case BO_GT: { IS_PushI(>); } break;
				case BO_GE: { IS_PushI(>= ); } break;
				case BO_LE: { IS_PushI(<= ); } break;
				case BO_NE: { IS_PushI(!= ); } break;
				case BO_LAnd: { IS_PushI(&&); } break;
				case BO_And: { IS_PushI(&); } break;
				case BO_Xor: { IS_PushI(^); } break;
				case BO_Add: { IS_PushI(+); } break;
				case BO_LOr: { IS_PushI(|| ); } break;
				case BO_Or: { IS_PushI(| ); } break;
				case BO_Shl: { IS_PushI(<< ); } break;
				case BO_Shr: { IS_PushI(>> ); } break;
				default:
					Throw("operator " + to_string(bOp->getOpcode()) + " is unimplemented for a static define");
				}
			}

		}
		else if (isa<InitListExpr>(e))
		{
			InitializationStack.push({ 0, FBWT_ARRAY });
			const InitListExpr *init = cast<const InitListExpr>(e);
			for (unsigned int i = 0; i<init->getNumInits(); i++) {
				ParseLiteral(init->getInit(i));
				ArrayOut.push_back(IS_Pop().bytes);

			}
			if (InitializationStack.top().type != FBWT_ARRAY)
				Throw("Stack error on InitListExpr literal");
		}
		else if (isa<CharacterLiteral>(e))
		{
			const CharacterLiteral *charliteral = cast<const CharacterLiteral>(e);

			InitializationStack.push({ (int32_t)charliteral->getValue(), FBWT_INT });
		}
		else {

			Throw("Class " + string(e->getStmtClassName()) + " is unimplemented for a static define");

		}
		return -1;
	}

	bool VisitDecl(Decl *D) {
		if (isa<VarDecl>(D)) {
			VarDecl *varDecl = cast<VarDecl>(D);
			if (varDecl->hasGlobalStorage()) {
				if (statics.find(dumpName(cast<NamedDecl>(D))) == statics.end()) {

					//QualType type = varDecl->getType();
					//auto size = getSizeOfQualType(&type);
					auto size = context->getTypeInfoDataSizeInChars(varDecl->getType()).first.getQuantity();

					uint32_t oldStaticInc = staticInc;
					statics.insert(make_pair(dumpName(cast<NamedDecl>(D)), staticInc));
					staticInc += getSizeFromBytes(size);

					const Expr *initializer = varDecl->getAnyInitializer();

					if (initializer) {
						if (isa<CXXConstructExpr>(initializer)) {
							//out << "GetStaticP2 " << oldStaticInc << " //" << varDecl->getName().str() << endl;
							ParseLiteral(initializer, true, false, true, varDecl);
						}

						ParseLiteral(initializer, false, true);
						//out << "SetStatic2 " << oldStaticInc << "  //" << varDecl->getName().str() << endl;

						uint32_t sizeb4 = 0;
						if (!InitializationStack.empty())
						{
							sizeb4 = InitializationStack.size();

							switch (InitializationStack.top().type)
							{
							case FBWT_ARRAY:
								if (varDecl->getType()->isArrayType())
								{
									if (varDecl->getType()->getArrayElementTypeNoTypeQual()->isBuiltinType())
									{
										const BuiltinType *bt = cast<const BuiltinType>(varDecl->getType()->getArrayElementTypeNoTypeQual());

										int32_t buffer = 0, b = 0, stvi = 0;

										switch (bt->getKind())
										{
											default://int, float, ect
											for (uint32_t i = 0; i < ArrayOut.size(); i++)
												DefaultStaticValues.insert({ oldStaticInc + i, to_string(ArrayOut[i]) });
											break;
											case clang::BuiltinType::Kind::SChar://var decl is char ksjsk[] = {'d','b','n','p','k'};
											case clang::BuiltinType::Kind::UChar:
												for (int32_t i = 0; i < ArrayOut.size(); i++, b++)
												{
													if (b >= 4)
													{
														DefaultStaticValues.insert({ oldStaticInc + stvi++, to_string(Utils::Bitwise::SwapEndian(buffer)) });
														b = buffer = 0;
													}
													
													((uint8_t*)(&buffer))[b] = ArrayOut[i] % 256;
												}
												if (b != 0)
													DefaultStaticValues.insert({ oldStaticInc + stvi, to_string(Utils::Bitwise::SwapEndian(buffer)) });

											break;
											case clang::BuiltinType::Kind::UShort:
											case clang::BuiltinType::Kind::Short:
												for (int32_t i = 0; i < ArrayOut.size(); i++, b++)
												{
													if (b >= 2)
													{
														DefaultStaticValues.insert({ oldStaticInc + stvi++, to_string(buffer) });
														b = buffer = 0;
													}
													
													((uint16_t*)(&buffer))[!b] = ArrayOut[i] % 65536;
												}
												if (b != 0)
													DefaultStaticValues.insert({ oldStaticInc + stvi, to_string(buffer) });

											break;

										}
									}
									else 
										Throw("Unimplemented non builtin type for static array initialization", rewriter, varDecl->getLocStart());

								}
								else
									Throw("Static var array " +
										varDecl->getType().getAsString() +
										"  was parsed as an array but declared as different",
										rewriter,
										varDecl->getLocStart()
									);



								//if (ArrayOut.size() != 0)
								//{
								//	staticInc += ArrayOut.size() - 1;
								//}
								ArrayOut.clear();
								InitializationStack.pop();
								break;
							case FBWT_FUNCTION_PTR:
								DefaultStaticValues.insert({ oldStaticInc, std::string((char*)ArrayOut.data()) });
								ArrayOut.clear();
								InitializationStack.pop();
								break;
							default://FBWT_INT

								if (varDecl->getType()->isBuiltinType())
								{
									const BuiltinType *bt = cast<const BuiltinType>(varDecl->getType());

									switch (bt->getKind())
									{
										default://int, float, ect
											DefaultStaticValues.insert({ oldStaticInc, to_string(IS_Pop().bytes) });
										break;
										case clang::BuiltinType::Kind::SChar:
										case clang::BuiltinType::Kind::UChar:
											DefaultStaticValues.insert({ oldStaticInc, to_string(Utils::Bitwise::SwapEndian(IS_Pop().bytes % 256)) });
										break;
										case clang::BuiltinType::Kind::UShort:
										case clang::BuiltinType::Kind::Short:
											DefaultStaticValues.insert({ oldStaticInc, to_string(Utils::Bitwise::Flip2BytesIn4(IS_Pop().bytes % 65536)) });
										break;

									}
								}
								else
									Throw("Unimplemented non builtin type for static initialization", rewriter, varDecl->getLocStart());

								//cout << "stack size: " << sizeb4 << endl
								//<< "value: " << DefaultStaticValues[oldStaticInc] << endl;
								break;
							}

						}
						else Throw("stack empty");

						//cout << "init Name: " << varDecl->getName().str() << " class: " << initializer->getStmtClassName() << '\n';
						//Pause();


					}
					else
					{
						//cout << "!init Name: " << varDecl->getName().str() << '\n';
						//Pause();
					}

				}
				else
					Throw("Var " + dumpName(cast<NamedDecl>(D)) + " is already defined");
			}
		}
		return true;
	}


	string dumpName(const NamedDecl *ND) {
		if (ND->getDeclName()) {

			return ND->getNameAsString();
		}
		return "";
	}

	vector<int32_t> ArrayOut;
	map<uint32_t, string> DefaultStaticValues;//index, value

	enum FBWT_Types : uint8_t
	{
		FBWT_INT,
		FBWT_FLOAT,
		FBWT_ARRAY,
		FBWT_FUNCTION_PTR
	};
	typedef struct {
		int32_t bytes;
		FBWT_Types type;
	} FBWT;
	stack<FBWT> InitializationStack;
	FBWT IS_Pop()
	{
		if (!InitializationStack.empty())
		{
			FBWT ret = InitializationStack.top();
			InitializationStack.pop();
			return ret;
		}
		else Throw("InitializationStack Empty");
	}


private:
	Rewriter &TheRewriter;
	ASTContext *context;
};

class LocalsVisitor : public RecursiveASTVisitor<GlobalsVisitor> {
public:
	LocalsVisitor(Rewriter &R, ASTContext *context) : TheRewriter(R), context(context) { currentFunction = NULL; }

	//    bool VisitStmt(Stmt *s) {
	//        // Only care about compound statements.
	//
	//
	//        return true;
	//    }
	//




	bool VisitDecl(Decl *D) {

		if (isa<FunctionDecl>(D)) {
			const FunctionDecl *func = cast<const FunctionDecl>(D);
			if (currentFunction) {
				localCounts.insert(make_pair(currentFunction, localInc - currentFunction->getNumParams() - (isa<CXXMethodDecl>(currentFunction) ? 1 : 0)));
			}
		}
		return true;
	}



	string dumpName(const NamedDecl *ND) {
		if (ND->getDeclName()) {

			return ND->getNameAsString();
		}
		return "";
	}

	bool TraverseDecl(Decl *D) {
		RecursiveASTVisitor::TraverseDecl(D);
		if (currentFunction)
			localCounts.insert(make_pair(currentFunction, localInc));
		return true;
	}



private:
	Rewriter &TheRewriter;
	ASTContext *context;
	const FunctionDecl *currentFunction;

};

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
class MyASTConsumer : public ASTConsumer {
public:
	MyASTConsumer(Rewriter &R, ASTContext *context, string filename) : Visitor(R, context, filename), GlobalsVisitor(R, context) {}

	// Override the method that gets called for each parsed top-level
	// declaration.
	bool HandleTopLevelDecl(DeclGroupRef DR) override {
		for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
			// Traverse the declaration using our AST visitor.
			GlobalsVisitor.TraverseDecl(*b);
			//            (*b)->dump();
		}

		for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
			// Traverse the declaration using our AST visitor.
			Visitor.TraverseDecl(*b);
			//(*b)->dump();
		}

		return true;
	}
	~MyASTConsumer() {
		stringstream header;

		header << "SetStaticsCount " << staticInc << "\r\n";
		for (map<uint32_t, string>::iterator iterator = GlobalsVisitor.DefaultStaticValues.begin(); iterator != GlobalsVisitor.DefaultStaticValues.end(); iterator++) {
			header << "SetDefaultStatic " << iterator->first << " " << iterator->second << "\r\n";

		}

		if (Visitor.MainRets != -1)
		{
			header << "\r\nFunction 0 2\r\nCall @main\r\n";
			for (int32_t i = 0; i < Visitor.MainRets; i++)
			{
				header << "Drop\r\n";
			}
			header << "Return 0 0\r\n";
		}
		else
			Throw("Function \"main\" was not found");

		FILE* file = fopen(Visitor.outfile.c_str(), "wb");
		if (file != NULL)
		{

			header.seekg(0, ios::end);
			fwrite(header.str().c_str(), 1, header.tellg(), file);

			Visitor.out.seekg(0, ios::end);
			fwrite(Visitor.out.str().c_str(), 1, Visitor.out.tellg(), file);

			fclose(file);
		}
		else Throw("Output File Could Not Be Opened");

	}

private:
	MyASTVisitor Visitor;
	GlobalsVisitor GlobalsVisitor;

};



// For each source file provided to the tool, a new FrontendAction is created.
class MyFrontendAction : public ASTFrontendAction {
public:
	MyFrontendAction() {}
	void EndSourceFileAction() override {
		//emit source

		//SourceManager &SM = TheRewriter.getSourceMgr();
		//llvm::errs() << "** EndSourceFileAction for: " << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

		// Now emit the rewritten buffer.
		//TheRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
	}

	std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override {

		llvm::errs() << "Compiling: " << file << "\n";
		TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
		rewriter = TheRewriter;
		SourceManager &SM = TheRewriter.getSourceMgr();
		string fileName(string(SM.getFileEntryForID(SM.getMainFileID())->getName()));
		fileName.erase(fileName.find_last_of(".c"));

		return llvm::make_unique<MyASTConsumer>(TheRewriter, &CI.getASTContext(), fileName + "asm");
	}

private:
	Rewriter TheRewriter;
};

int main(int argc, const char **argv) {
	cout << "Starting Clang 3.8.1\r\n";

	CommonOptionsParser op(argc, argv, ToolingSampleCategory);
	ClangTool Tool(op.getCompilations(), op.getSourcePathList());

	// ClangTool::run accepts a FrontendActionFactory, which is then used to
	// create new objects implementing the FrontendAction interface. Here we use
	// the helper newFrontendActionFactory to create a default factory that will
	// return a new MyFrontendAction object every time.
	// To further customize this, we could create our own factory class.
	return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}
