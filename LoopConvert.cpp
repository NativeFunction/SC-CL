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
#include <unordered_map>
#include <cmath>
#include "Utils.h"

#undef ReplaceText//(commdlg.h) fix for the retard at microsoft who thought having a define as ReplaceText was a good idea
#define MultValue(pTypePtr) (pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4)
#define STATIC_DEBUG 0

//using namespace clang::driver;

using namespace Utils;
using namespace Utils::System;
using namespace Utils::DataConversion;
using namespace Utils::Hashing;
using namespace clang;
using namespace clang::tooling;
using namespace std;
static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

static Rewriter rewriter;

map<string, int> globals;
map<string, int> statics;
struct FData
{
	uint32_t hash;
	string name;
	bool isused;
	streampos FuncDataPos;
};
vector<FData> functions;
struct InlineData { uint32_t hash; string name; };
vector<InlineData> InlineItems;

bool isFunctionInInline(string fName)
{
	uint32_t hash = Utils::Hashing::Joaat((char*)fName.c_str());
	for (InlineData data : InlineItems)
	{
		if (data.hash == hash)
		{
			if (data.name == fName)
				return true;
		}
	}
	return false;
}
bool addFunctionInline(string fName)
{
	if (isFunctionInInline(fName))
		return false;
	InlineItems.push_back({ Utils::Hashing::Joaat((char*)fName.c_str()) , fName });
	return true;
}
void removeFunctionInline(string fName)
{
	assert(InlineItems.back().name == fName);
	InlineItems.pop_back();

}

map<const FunctionDecl*, int> localCounts;
static int globalInc = 0;
static int staticInc = 0;


struct local_scope
{
	vector<vector<string>> scopeLocals;
	uint32_t maxIndex = 0;
	int scopeLevel = 0;
	void reset()//call this on function decl
	{
		scopeLevel = 0;
		scopeLocals.clear();
		scopeLocals.push_back(vector<string>());
		maxIndex = 0;
	}
	void addLevel()
	{
		scopeLocals.push_back(vector<string>());
		scopeLevel++;
	}
	void removeLevel()
	{
		if (scopeLevel > 0)
		{
			scopeLevel--;
			scopeLocals.pop_back();
		}
	}
	bool find(string key, int* outIndex)
	{
		for (int i = scopeLevel; i >= 0; i--)
		{
			vector<string>& locals = scopeLocals[i];
			for (int j = 0, max = locals.size(); j < max; j++) {
				if (locals[j] == key)
				{
					int count = j;
					for (int k = 0; k < i; k++)
					{
						count += scopeLocals[k].size();
					}
					*outIndex = count;
					return true;
				}
			}
		}
		return false;
	}
	uint32_t getCurrentSize()
	{
		uint32_t cursize = 0;
		for (int i = 0; i <= scopeLevel; i++)
		{
			cursize += scopeLocals[i].size();
		}
		return cursize;
	}
	int addDecl(string key, int size)//size being number of 4 byte variables it takes up
	{
		assert(size > 0);
		int prevSize = getCurrentSize();
		scopeLocals[scopeLevel].push_back(key);
		for (int i = 1; i < size; i++)
		{
			scopeLocals[scopeLevel].push_back("");//use a null string for padding
		}

		uint32_t cursize = prevSize + size;
		if (cursize > maxIndex)
		{
			maxIndex = cursize;
		}
		return prevSize;
	}

}LocalVariables;
// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.

//Constexpr in visual studio is not fully implemented. When they are put in the hashing namespace in utils it errors.
#pragma region constexpr_helpers
constexpr char ToLowerConst(const char c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; }
constexpr uint32_t sumSHL(uint32_t h, uint32_t shift) { return h + (h << shift); }
constexpr uint32_t sumSHR(uint32_t h, uint32_t shift) { return h + (h >> shift); }
constexpr uint32_t xorSHR(uint32_t h, uint32_t shift) { return h ^ (h >> shift); }
constexpr uint32_t hashFinishImpl(uint32_t h) { return sumSHL(xorSHR(sumSHL(h, 3), 11), 15); }
constexpr uint32_t hashStepImpl(uint32_t h, uint32_t c) { return xorSHR(sumSHL(h + c, 10), 6); }
constexpr uint32_t casedHashImpl(const char * cstr, uint32_t h) { return (*cstr != 0) ? casedHashImpl(cstr + 1, hashStepImpl(h, *cstr)) : hashFinishImpl(h); }
constexpr uint32_t hashImpl(const char * cstr, uint32_t h) { return (*cstr != 0) ? hashImpl(cstr + 1, hashStepImpl(h, ToLowerConst(*cstr))) : hashFinishImpl(h); }
#pragma endregion

constexpr uint32_t JoaatCasedConst(const char * cstr) { return casedHashImpl(cstr, 0); }
constexpr uint32_t JoaatConst(const char * cstr) { return hashImpl(cstr, 0); }


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
uint32_t getLiteralSizeOfType(const Type* type) {

	if (isa<ConstantArrayType>(type)) {
		const ConstantArrayType *arrType = cast<const ConstantArrayType>(type);
		return getSizeOfType(type->getArrayElementTypeNoTypeQual()) * (arrType->getSize()).getSExtValue();
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
				const Type* type = CS->getType().getTypePtr();

				size += getSizeOfType(type);
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
				const Type* type = CS->getType().getTypePtr();

				uint32_t sz = getSizeOfType(type);
				if (sz > size)
					size = sz;
			}
			//cout << "union: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

			return size;
		}

	}
	else if (type->isAnyComplexType())
		return 8;
	else if (type->isCharType())
		return 1;
	else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
		return 2;
	else if (type->isIntegerType() || type->isBooleanType() || type->isRealFloatingType() || type->isPointerType())
		return 4;
	else if (type->isVoidType())
		return 0;

	return 0;
}
uint32_t getSizeOfType(const Type* type) {

	if (isa<ConstantArrayType>(type)) {
		const ConstantArrayType *arrType = cast<const ConstantArrayType>(type);
		return ((getSizeOfType(type->getArrayElementTypeNoTypeQual()) * (arrType->getSize()).getSExtValue()) + 4 - 1) & ~3;
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
				const Type* type = CS->getType().getTypePtr();

				size += (getSizeOfType(type) + 4 - 1) & ~3;
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
				const Type* type = CS->getType().getTypePtr();

				uint32_t sz = (getSizeOfType(type) + 4 - 1) & ~3;
				if (sz > size)
					size = sz;
			}
			//cout << "union: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

			return size;
		}

	}
	else if (type->isCharType())
		return 1;
	else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
		return 2;
	else if (type->isIntegerType() || type->isBooleanType() || type->isFloatingType() || type->isPointerType())
		return 4;
	else if (type->isVoidType())
		return 0;

	return 0;
}
bool CheckExprForSizeOf(const Expr* expr, int *outSize)
{
	if (isa<UnaryExprOrTypeTraitExpr>(expr))
	{
		const UnaryExprOrTypeTraitExpr *ueTrait = cast<UnaryExprOrTypeTraitExpr>(expr);
		if (ueTrait->getKind() == UETT_SizeOf)
		{
			if (ueTrait->isArgumentType())
				*outSize = getSizeOfType(ueTrait->getArgumentType().getTypePtr());
			else//size = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
				*outSize = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
			return true;
		}
	}
	return false;
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

	//handleParamVarDecl
	bool handleParmVarDecl(ParmVarDecl *D) {
		if (isa<ParmVarDecl>(D)) {
			ParmVarDecl *decl = cast<ParmVarDecl>(D);
			if (isa<VarDecl>(decl)) {

				VarDecl *var = cast<VarDecl>(decl);
				auto size = context->getTypeInfoDataSizeInChars(var->getType()).first.getQuantity();
				uint32_t curIndex = LocalVariables.getCurrentSize();

				int actsize = var->isCXXInstanceMember() ?
					getSizeFromBytes(getSizeOfCXXDecl(var->getType()->getAsCXXRecordDecl(), true, false))
					: getSizeFromBytes(size);

				const Expr *initializer = var->getAnyInitializer();

				if (initializer) {
					if (isa<CXXConstructExpr>(initializer)) {

						out << pFrame(curIndex) << " //" << var->getNameAsString() << endl;
						parseExpression(initializer);
					}
					else
					{
						parseExpression(initializer);
						out << frameSet(curIndex) << "  //" << var->getName().str() << endl;
					}
				}
				LocalVariables.addDecl(var->getName().str(), actsize);
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
		return add(size * 4) + "\r\npGet";
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
		return add(size * 4) + "\r\npSet";
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
		else if (val > -32768 && val < 32767)
			return "PushS " + to_string(val);
		else if ((val & 0xFFFFFF) == val)
			return "PushI24 " + to_string(val);
		else
		{
			return "Push " + to_string(val);
		}
	}
	string fPush(double value)
	{
		if (value == -1.0)
			return "PushF_-1";
		if (value == 0.0 || value == -0.0)//double has -ive 0 and +ive 0
			return "PushF_0";
		if (value == 1.0)
			return "PushF_1";
		if (value == 2.0)
			return "PushF_2";
		if (value == 3.0)
			return "PushF_3";
		if (value == 4.0)
			return "PushF_4";
		if (value == 5.0)
			return "PushF_5";
		if (value == 6.0)
			return "PushF_6";
		if (value == 7.0)
			return "PushF_7";
		return "PushF " + to_string(value);
	}
	string fPush(llvm::APFloat value)
	{
		if (&value.getSemantics() == &llvm::APFloat::IEEEsingle)
			return fPush((double)value.convertToFloat());
		else
			return fPush(value.convertToDouble());
	}
	string mult(int value)
	{
		if (value < -32768 || value > 32767)
			return iPush(value) + "\r\nMult";
		else if (value > 0xFF || value < 0)
			return "Mult2 " + to_string(value);
		else
			return "Mult1 " + to_string(value);
	}
	string add(int value)
	{
		if (value == 0)
			return "";
		if (value < -32768 || value > 32767)
			return iPush(value) + "\r\nAdd";
		else if (value > 0xFF || value < 0)
			return "Add2 " + to_string(value);
		else
			return "Add1 " + to_string(value);
	}
	string sub(int value)
	{
		if (value < -32767 || value > 32768)
			return iPush(value) + "\r\nSub";
		else
			return "Add2 " + to_string(-value);
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

	void parseJumpFalseCondition(Expr *condition, bool invert = false)
	{
		while (isa<BinaryOperator>(condition))
		{
			BinaryOperator* bCond = cast<BinaryOperator>(condition);
			if (bCond->getOpcode() == BO_Comma)
			{
				parseExpression(bCond->getLHS());
				condition = bCond->getRHS();
				continue;
			}
			break;
		}
		if (isa<BinaryOperator>(condition))
		{
			BinaryOperator* bCond = cast<BinaryOperator>(condition);
			if (bCond->getLHS()->getType()->isIntegerType() && bCond->getRHS()->getType()->isIntegerType())
			{
				switch (bCond->getOpcode())
				{
					case BO_EQ:
					case BO_NE:
					case BO_GT:
					case BO_GE:
					case BO_LT:
					case BO_LE:
					parseExpression(bCond->getLHS(), false, true);
					parseExpression(bCond->getRHS(), false, true);
					if (invert) {
						switch (bCond->getOpcode())
						{
							case BO_EQ:
							out << "JumpEQ @";
							return;
							case BO_NE:
							out << "JumpNE @";
							return;
							case BO_GT:
							out << "JumpGT @";
							return;
							case BO_GE:
							out << "JumpGE @";
							return;
							case BO_LT:
							out << "JumpLT @";
							return;
							case BO_LE:
							out << "JumpLE @";
							return;
							default:
							assert(false);//this shouldnt happen
						}
					}
					else
					{
						switch (bCond->getOpcode())
						{
							case BO_EQ:
							out << "JumpNE @";
							return;
							case BO_NE:
							out << "JumpEQ @";
							return;
							case BO_GT:
							out << "JumpLE @";
							return;
							case BO_GE:
							out << "JumpLT @";
							return;
							case BO_LT:
							out << "JumpGE @";
							return;
							case BO_LE:
							out << "JumpGT @";
							return;
							default:
							assert(false);//this shouldnt happen
						}
					}
					break;
					default:
					break;
				}
			}
		}
		parseExpression(condition, false, true);
		if (invert)
		{
			out << "not //Invert the result\r\n";
		}
		out << "JumpFalse @";
	}

	void printDeclWithKey(string key, bool isAddr, bool isLtoRValue, int size = 1) {
		int index = -1;

		if (size > 1 && isLtoRValue) {
			out << iPush(size) << "//Type Size" << endl;
			isAddr = true;
		}

		if (LocalVariables.find(key, &index))
		{
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
			string name = "@" + key;
			uint32_t hash = Utils::Hashing::Joaat((char*)name.c_str());
			uint32_t i = 0;
			for (; i < functions.size(); i++)
			{
				if (functions[i].hash == hash)
				{
					if (functions[i].name == name)
					{
						functions[i].isused = true;
						break;
					}
				}
			}

			if (i >= functions.size())
				Throw("Function pointer \"" + key + "\" not found");

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

	bool parseStatement(Stmt *s, uint64_t breakLoc = -1, uint64_t continueLoc = -1, uint64_t returnLoc = -1) {
		if (isa<CompoundStmt>(s)) {
			CompoundStmt *cSt = cast<CompoundStmt>(s);
			//            cSt->dump();
			for (auto *CS : cSt->body()) {
				if (isa<Stmt>(*CS))
					parseStatement(cast<Stmt>(CS), breakLoc, continueLoc, returnLoc);
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

			string IfLocEnd = to_string(Then->getLocEnd().getRawEncoding());

			Expr::EvalResult eResult;
			bool bValue = false, ignoreCondition = false;
			if (conditional->EvaluateAsRValue(eResult, *context) && eResult.Val.isInt())
			{
				bValue = eResult.Val.getInt().getBoolValue();
				if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
					Warn("if condition always evaluates to " + (bValue ? string("true") : string("false")), rewriter, conditional->getSourceRange());
				ignoreCondition = !eResult.HasSideEffects;
			}
			if (ignoreCondition)
			{
				if (bValue)
				{
					LocalVariables.addLevel();
					parseStatement(Then, breakLoc, continueLoc, returnLoc);
					LocalVariables.removeLevel();
					if (Else)//still parse the else code just incase there are goto labels in there
					{
						out << "Jump @" << IfLocEnd << "//ifstmt jmp" << endl;
						LocalVariables.addLevel();
						parseStatement(Else, breakLoc, continueLoc, returnLoc);
						LocalVariables.removeLevel();
						out << endl << ":" << IfLocEnd << "//ifend lbl" << endl;
					}
				}
				else
				{
					//still parse the then code just incase there are goto labels in there
					out << "Jump @" << (Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd) << endl;
					LocalVariables.addLevel();
					parseStatement(Then, breakLoc, continueLoc, returnLoc);
					LocalVariables.removeLevel();
					if (Else)
					{
						out << "Jump @" << IfLocEnd << "//ifstmt jmp" << endl;
						out << endl << ":" << Else->getLocStart().getRawEncoding() << "//ifstmt else lbl" << endl;
						LocalVariables.addLevel();
						parseStatement(Else, breakLoc, continueLoc, returnLoc);
						LocalVariables.removeLevel();
					}
					out << endl << ":" << IfLocEnd << "//ifend lbl" << endl;
				}
			}
			else
			{
				parseJumpFalseCondition(conditional);
				out << (Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd) << endl;
				LocalVariables.addLevel();
				parseStatement(Then, breakLoc, continueLoc, returnLoc);
				LocalVariables.removeLevel();

				out << "Jump @" << IfLocEnd << "//ifstmt jmp" << endl;

				if (Else) {
					out << endl << ":" << Else->getLocStart().getRawEncoding() << "//ifstmt else lbl" << endl;
					LocalVariables.addLevel();
					parseStatement(Else, breakLoc, continueLoc, returnLoc);
					LocalVariables.removeLevel();
					out << "//" << Else->getLocStart().getRawEncoding() << " " << Else->getLocEnd().getRawEncoding() << endl;
				}
				if (Then)
				{
					out << "//" << Then->getLocStart().getRawEncoding() << " " << Then->getLocEnd().getRawEncoding() << endl;
				}

				out << endl << ":" << IfLocEnd << "//ifend lbl" << endl;
			}
		}
		else if (isa<WhileStmt>(s)) {
			WhileStmt *whileStmt = cast<WhileStmt>(s);
			Expr *conditional = whileStmt->getCond();

			Stmt *body = whileStmt->getBody();
			LocalVariables.addLevel();

			Expr::EvalResult eResult;
			bool bValue = false, ignoreCondition = false;
			if (conditional->EvaluateAsRValue(eResult, *context) && eResult.Val.isInt())
			{
				bValue = eResult.Val.getInt().getBoolValue();
				if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
					Warn("While condition always evaluates to " + (bValue ? string("true") : string("false")), rewriter, conditional->getSourceRange());
				ignoreCondition = !eResult.HasSideEffects;
			}
			if (ignoreCondition)
			{
				if (bValue)
				{
					out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;
					parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding(), returnLoc);

					out << "Jump @" << conditional->getLocStart().getRawEncoding() << endl;
					out << endl << ":" << whileStmt->getLocEnd().getRawEncoding() << endl;
				}
				else
				{
					out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;
					out << "Jump @" << whileStmt->getLocEnd().getRawEncoding() << endl;

					parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding(), returnLoc);

					out << "Jump @" << conditional->getLocStart().getRawEncoding() << endl;
					out << endl << ":" << whileStmt->getLocEnd().getRawEncoding() << endl;
				}

			}
			else {

				out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;
				parseJumpFalseCondition(conditional);
				out << whileStmt->getLocEnd().getRawEncoding() << endl;

				parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding(), returnLoc);

				out << "Jump @" << conditional->getLocStart().getRawEncoding() << endl;
				out << endl << ":" << whileStmt->getLocEnd().getRawEncoding() << endl;
			}
			LocalVariables.removeLevel();
		}
		else if (isa<ForStmt>(s)) {
			ForStmt *forStmt = cast<ForStmt>(s);
			Stmt *decl = forStmt->getInit();
			Expr *conditional = forStmt->getCond();
			Expr *increment = forStmt->getInc();
			Stmt *body = forStmt->getBody();
			LocalVariables.addLevel();
			if (decl) {
				parseStatement(decl, -1, -1, returnLoc);
			}

			if (conditional) {
				out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;

				parseJumpFalseCondition(conditional);
				out << body->getLocEnd().getRawEncoding() << endl;
			}
			else
			{
				out << endl << ":" << body->getLocStart().getRawEncoding() << endl;
			}

			parseStatement(
				body,
				forStmt->getLocEnd().getRawEncoding(),
				increment ? increment->getLocStart().getRawEncoding() : conditional ? conditional->getLocStart().getRawEncoding() : body->getLocStart().getRawEncoding(),
				returnLoc);

			if (increment)
				out << endl << ":" << increment->getLocStart().getRawEncoding() << "//forstmt inc lbl" << endl;

			if (increment)
				parseExpression(increment);

			if (conditional)
				out << "Jump @" << conditional->getLocStart().getRawEncoding() << "//forstmt cond jmp" << endl;
			else
				out << "Jump @" << body->getLocStart().getRawEncoding() << "//forstmt jmp" << endl;


			out << endl << ":" << body->getLocEnd().getRawEncoding() << "//forend lbl" << endl;
			LocalVariables.removeLevel();


		}
		else if (isa<UnaryOperator>(s)) {
			parseExpression(cast<const Expr>(s));
		}
		else if (isa<DoStmt>(s)) {
			DoStmt *doStmt = cast<DoStmt>(s);
			Expr *conditional = doStmt->getCond();

			Stmt *body = doStmt->getBody();
			LocalVariables.addLevel();

			out << endl << ":" << body->getLocStart().getRawEncoding() << endl;

			parseStatement(body, conditional->getLocEnd().getRawEncoding(), body->getLocEnd().getRawEncoding(), returnLoc);



			out << endl << ":" << body->getLocEnd().getRawEncoding() << "" << endl;
			Expr::EvalResult eResult;
			bool bValue = false, ignoreCondition = false;
			if (conditional->EvaluateAsRValue(eResult, *context) && eResult.Val.isInt())
			{
				bValue = eResult.Val.getInt().getBoolValue();
				if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
					Warn("do While condition always evaluates to " + (bValue ? string("true") : string("false")), rewriter, conditional->getSourceRange());
				ignoreCondition = !eResult.HasSideEffects;
			}
			if (ignoreCondition)
			{
				if (bValue)
				{
					out << "Jump @" << body->getLocStart().getRawEncoding() << endl;
				}
				//no need for else, just jump right out

			}
			else
			{
				parseJumpFalseCondition(conditional, true);
				out << body->getLocStart().getRawEncoding() << endl;
			}

			out << endl << ":" << conditional->getLocEnd().getRawEncoding() << "" << endl;
			LocalVariables.removeLevel();

		}
		else if (isa<ReturnStmt>(s)) {
			const ReturnStmt *ret = cast<const ReturnStmt>(s);
			const Expr* retVal = ret->getRetValue();
			if (retVal)
				parseExpression(retVal, false, true);
			if (returnLoc == -1)
			{
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
			else
			{
				out << "Jump @" << returnLoc << endl;
			}

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
			DefaultStmt *caseD = cast<DefaultStmt>(s);
			string labelName = ":" + to_string(caseD->getLocEnd().getRawEncoding());
			if (FindBuffer.find(labelName) == FindBuffer.end())
			{
				FindBuffer.insert(labelName);
				out << labelName << endl;
			}
			LocalVariables.addLevel();

			if (caseD->getSubStmt())
				parseStatement(caseD->getSubStmt(), breakLoc, continueLoc, returnLoc);
			LocalVariables.removeLevel();
		}
		else if (isa<CaseStmt>(s)) {
			CaseStmt *caseS = cast<CaseStmt>(s);

			string labelName = ":" + to_string(caseS->getLocEnd().getRawEncoding());
			if (FindBuffer.find(labelName) == FindBuffer.end())
			{
				FindBuffer.insert(labelName);
				out << labelName << endl;
			}
			LocalVariables.addLevel();
			if (caseS->getRHS())
				parseExpression(caseS->getRHS());

			if (caseS->getSubStmt())
				parseStatement(caseS->getSubStmt(), breakLoc, continueLoc, returnLoc);
			LocalVariables.removeLevel();
		}
		else if (isa<SwitchStmt>(s)) {
			SwitchStmt *switchStmt = cast<SwitchStmt>(s);
			out << "//Switch Conditional" << endl;
			FindBuffer.clear();
			parseExpression(switchStmt->getCond(), false, true);
			out << "Switch ";

			//Build case switch list first
			SwitchCase *switchCaseList = switchStmt->getSwitchCaseList();
			DefaultStmt *defaultCase = NULL;
			stack<string> caseLabels;
			while (switchCaseList != NULL)
			{
				if (isa<CaseStmt>(switchCaseList))
				{
					CaseStmt *caseS = cast<CaseStmt>(switchCaseList);
					Expr::EvalResult result;
					if (caseS->getLHS()->EvaluateAsRValue(result, *context)) {
						if (result.Val.isInt())
						{
							int val;
							if (CheckExprForSizeOf(caseS->getLHS()->IgnoreParens(), &val))
								caseLabels.push("[" + to_string(val) + " @" + to_string(caseS->getLocEnd().getRawEncoding()) + "]");
							else
								caseLabels.push("[" + to_string(result.Val.getInt().getSExtValue()) + " @" + to_string(caseS->getLocEnd().getRawEncoding()) + "]");
						}
						else if (result.Val.isFloat())
						{
							caseLabels.push("[" + to_string(result.Val.getFloat().convertToFloat()) + " @" + to_string(caseS->getLocEnd().getRawEncoding()) + "]");
						}
						else Throw("Unsupported case statement \"" + string(caseS->getLHS()->getStmtClassName()) + "\"", rewriter, caseS->getLHS()->getSourceRange());
					}
					else Throw("Unsupported case statement \"" + string(caseS->getLHS()->getStmtClassName()) + "\"", rewriter, caseS->getLHS()->getSourceRange());

				}
				else if (isa<DefaultStmt>(switchCaseList))
				{
					if (defaultCase) {
						Throw("Multiple default statements found in switch", rewriter, defaultCase->getLocStart(), switchCaseList->getLocEnd());
					}
					defaultCase = cast<DefaultStmt>(switchCaseList);
				}
				else
					llvm::errs() << "Unexpected Statement: " << switchCaseList->getStmtClassName();
				switchCaseList = switchCaseList->getNextSwitchCase();
			}
			while (caseLabels.size() > 1)
			{
				out << caseLabels.top() << ":";
				caseLabels.pop();
			}
			out << caseLabels.top() << endl;

			if (defaultCase)
			{
				out << "Jump @" << defaultCase->getLocEnd().getRawEncoding() << endl;
			}
			else
			{
				out << "Jump @" << switchStmt->getLocEnd().getRawEncoding() << endl;
			}

			//parse all
			parseStatement(switchStmt->getBody(), switchStmt->getLocEnd().getRawEncoding(), continueLoc, returnLoc);
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
			if (InlineItems.size())
			{
				Warn("Using a __asm__ statement in an inlined function may lead to undesireable effects\r\nConsider marking the function as __attribute__((__noinline__))", rewriter, asmstmt->getSourceRange());
			}
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
				if (var->getStorageClass() != SC_Static)//static vars are initialized in the globals visitor
				{
					auto size = getSizeOfType(var->getType().getTypePtr());

					uint32_t curIndex = LocalVariables.getCurrentSize();

					const ArrayType *arr = NULL;
					if ((arr = var->getType()->getAsArrayTypeUnsafe()) && arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl()) {
						if (isa<ConstantArrayType>(arr)) {
							const ConstantArrayType *cArrType = cast<const ConstantArrayType>(arr);
							size = getSizeOfCXXDecl(arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), true, false) * cArrType->getSize().getSExtValue();
						}
						else {
							Throw("Unsupported decl of " + string(var->getDeclKindName()), rewriter, var->getLocStart());
						}

					}
					else if (var->getType()->getAsCXXRecordDecl()) {
						size = getSizeOfCXXDecl(var->getType()->getAsCXXRecordDecl(), true, false);
					}

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
								out << "JumpGE @vTableEnd_" << vTableInitInc << endl;

								out << "dup #index" << endl;
								out << pFrame(curIndex) << " //" << var->getNameAsString() << endl;
								out << "ArrayGetP " << getSizeFromBytes(getSizeOfCXXDecl(arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), true, true)) << "//index Array" << endl;
								parseExpression(initializer, true, false, true, var);
								out << "Add1 1" << endl;
								out << "Jump @vTableConditional_" << vTableInitInc << endl;
								out << ":vTableEnd_" << vTableInitInc << endl << endl;
								//}
								vTableInitInc++;
								return true;
							}
							out << pFrame(curIndex) << " //" << var->getNameAsString() << endl;
							parseExpression(initializer, true, false, true, var);
							return true;
						}

						parseExpression(initializer, false, true);
						if (size > 4) {
							out << iPush(getSizeFromBytes(size)) << " //Type Size" << endl;
							out << pFrame(curIndex) << " //&" << var->getNameAsString() << endl;
							out << "FromStack" << endl;
						}
						else {
							out << frameSet(curIndex) << "  //" << var->getName().str() << endl;
						}
					}
					LocalVariables.addDecl(var->getName().str(), getSizeFromBytes(size));
				}


			}
		}
		return true;
	}

	bool checkIntrinsic(const CallExpr *call) {
		const FunctionDecl* callee = call->getDirectCallee();

		if (callee == NULL || !callee->hasAttr<IntrinsicFuncAttr>())
			return false;

		if (callee->getStorageClass() != SC_Extern)
			Throw("Intrinsic functions must be declared with the 'extern' keyword", rewriter, callee->getLocation());

		string funcName = dumpName(cast<NamedDecl>(callee));

		const Expr * const*argArray = call->getArgs();
		int argCount = call->getNumArgs();

		#define ChkHashCol(str) if(strcmp(funcName.c_str(), str) != 0) return false;

		switch (JoaatCased(const_cast<char*>(funcName.c_str())))
		{
			case JoaatCasedConst("strncpy"):
			{
				ChkHashCol("strncpy");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					parseExpression(argArray[0], false, true);

					out << "StrCopy ";
					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
							out << iValue << endl;
							return true;
						}
						else
						{
							Throw("Integer constant for string max length argument in strcpy must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
							return false;
						}
					}
					else
					{
						Throw("Expected integer constant for string max length argument in strcpy", rewriter, argArray[2]->getSourceRange());
						return false;
					}
				}
				else
				{
					Throw("strcpy must have signature \"extern __intrinsic void strcpy(char* dst, char* src, const byte len);\"", rewriter, callee->getSourceRange());
					return false;
				}
			}
			break;
			case JoaatCasedConst("stradd"):
			{
				ChkHashCol("stradd");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					parseExpression(argArray[0], false, true);

					out << "StrAdd ";
					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
							out << iValue << endl;
							return true;
						}
						else
						{
							Throw("Integer constant for string max length argument in stradd must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
							return false;
						}
					}
					else
					{
						Throw("Expected integer constant for string max length argument in stradd", rewriter, argArray[2]->getSourceRange());
						return false;
					}
				}
				else
				{
					Throw("stradd must have signature \"extern __intrinsic void stradd(char* dst, char* append, const byte len);\"", rewriter, callee->getSourceRange());
					return false;
				}
			}
			break;
			case JoaatCasedConst("straddi"):
			{
				ChkHashCol("straddi");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					parseExpression(argArray[0], false, true);

					out << "StrAddi ";
					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
							out << iValue << endl;
							return true;
						}
						else
						{
							Throw("Integer constant for string max length argument in straddi must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
							return false;
						}
					}
					else
					{
						Throw("Expected integer constant for string max length argument in straddi", rewriter, argArray[2]->getSourceRange());
						return false;
					}
				}
				else
				{
					Throw("straddi must have signature \"extern __intrinsic void straddi(char* dst, int append, const byte len);\"", rewriter, callee->getSourceRange());
					return false;
				}
			}
			break;
			case JoaatCasedConst("itos"):
			{
				ChkHashCol("itos");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					parseExpression(argArray[0], false, true);

					out << "ItoS ";
					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
							out << iValue << endl;
							return true;
						}
						else
						{
							Throw("Integer constant for string max length argument in itos must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
							return false;
						}
					}
					else
					{
						Throw("Expected integer constant for string max length argument in itos", rewriter, argArray[2]->getSourceRange());
						return false;
					}
				}
				else
				{
					Throw("itos must have signature \"extern __intrinsic void itos(char* dst, int value, const byte len);\"", rewriter, callee->getSourceRange());
					return false;
				}
			}
			break;
			case JoaatCasedConst("pop"):
			{
				ChkHashCol("pop");
				if (argCount == 0 && callee->getReturnType()->isVoidType())
				{
					out << "Drop\r\n";
					return true;
				}
				Throw("pop must have signature \"extern __intrinsic void pop();\"", rewriter, callee->getSourceRange());
			}
			break;
			case JoaatCasedConst("popMult"):
			{
				ChkHashCol("popMult");
				//	out << call->getExprLoc().
				if (argCount == 1 && callee->getReturnType()->isVoidType())
				{
					llvm::APSInt result;
					if (argArray[0]->getType()->isIntegerType())
					{
						if (argArray[0]->EvaluateAsInt(result, *context))
						{
							int intValue = result.getSExtValue();
							if (intValue <= 0)
							{
								Throw("Expected positive integer constant for pop amount argument in popMult, got " + to_string(intValue), rewriter, argArray[0]->getSourceRange());
								return false;
							}
							for (int i = 0; i < intValue; i++)
								out << "Drop\r\n";
							return true;;
						}
						Throw("Expected positive integer constant for pop amount argument in popMult", rewriter, argArray[0]->getSourceRange());
						return false;
					}
				}
				Throw("popMult must have signature \"extern __intrinsic void popMult(const int amount);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("pcall"):
			{
				ChkHashCol("pcall");
				if (argCount >= 1 && !callee->getReturnType()->isVoidType())
				{
					if (argCount > 1)
						for (int i = 1; i < argCount; i++)
							parseExpression(argArray[i], false, true);

					parseExpression(argArray[0], false, true);

					Warn("PCall unused returns must be dropped handled by user!", rewriter, call->getSourceRange());
					out << "pCall" << endl;
					return true;
				}
				Throw("pCall must have signature \"extern __intrinsic void pcall(void* funcAddr, ... args);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("add"):
			{
				ChkHashCol("add");
				if(argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if(argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if(iResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << add(iResult) << "\r\n";
						}
					}
					else
					{
						parseExpression(argArray[0]);
						out << "Add\r\n";
					}
					return true;
				}
				Throw("add must have signature \"extern __intrinsic int add(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("sub"):
			{
				ChkHashCol("sub");
				if(argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if(argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if(iResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << sub(iResult) << "\r\n";
						}
					}
					else
					{
						parseExpression(argArray[0]);
						out << "Sub\r\n";
					}
					return true;
				}
				Throw("sub must have signature \"extern __intrinsic int sub(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("mult"):
			{
				ChkHashCol("mult");
				if(argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if(argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if(iResult == 0)
						{
							out << "Drop\r\nPush_0\r\n";//replace top of stack with 0
						}
						else if(iResult == 1)
						{
							//do nothing here
						}
						else if(iResult == -1)
						{
							//negate
							out << "Neg\r\n";
						}
						else
						{
							out << mult(iResult) << "\r\n";
						}

					}
					else
					{
						parseExpression(argArray[0]);
						out << "Mult\r\n";
					}
					return true;
				}
				Throw("mult must have signature \"extern __intrinsic int mult(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("div"):
			{
				ChkHashCol("div");
				if(argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if(argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if(iResult == 0)
						{
							Warn("Zero division error detected", rewriter, argArray[0]->getSourceRange());//just warn the user of the undefined behaviour
						}
						else if(iResult == 1)
						{
							//do nothing here
						}
						else if(iResult == -1)
						{
							//negate
							out << "Neg\r\n";
						}
						else
						{
							out << iPush(iResult) << "\r\nDiv\r\n";
						}

					}
					else
					{
						parseExpression(argArray[0]);
						out << "Div\r\n";
					}
					return true;
				}
				Throw("div must have signature \"extern __intrinsic int div(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("getframe"):
			ChkHashCol("getframe");
			goto FrameReuse;
			case JoaatCasedConst("getframep"):
			ChkHashCol("getframep");
			goto FrameReuse;
			case JoaatCasedConst("setframe"):
			{
				ChkHashCol("setframe");

			FrameReuse:;

				if (argCount == 1)
				{

					if (isa<IntegerLiteral>(argArray[0]))
					{
						out << funcName;
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
								int index;
								if (LocalVariables.find(name, &index))
								{
									out << funcName;
									out << ((index & 0xFF) == index ? "1 " : "2 ");
									out << index << " //" << name << endl;
								}
								else
									Throw("Could not find variable " + name + ".", rewriter, argArray[0]->getExprLoc());
							}
							else
								Throw("Invalid " + funcName + " Parameters.", rewriter, argArray[0]->getExprLoc());
						}
						else
							Throw("Invalid " + funcName + " Parameters.", rewriter, argArray[0]->getExprLoc());
					}
					else
						Throw("Invalid " + funcName + " Parameters.", rewriter, argArray[0]->getExprLoc());
				}
				else
				{
					Throw("Invalid " + funcName + " Parameters.", rewriter, argArray[0]->getExprLoc());
				}
				return true;
			}
			break;
			case JoaatCasedConst("getglobal"):
			{
				ChkHashCol("getglobal");
				if (argCount == 1)
				{
					if (isa<IntegerLiteral>(argArray[0]))
					{
						const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
						int intValue = intVal->getValue().getSExtValue();

						out << "getglobal"
							<< ((intValue & 0xFFFF) == intValue ? "2 " : "3 ")
							<< intValue << endl;
						return true;
					}
					else
						Throw("Expected Integer Literal.", rewriter, argArray[0]->getExprLoc());
				}
				else
					Throw("Invalid " + funcName + " Parameters.", rewriter, call->getExprLoc());
			}
			break;
			case JoaatCasedConst("setglobal"):
			{
				ChkHashCol("setglobal");
				if (argCount == 2)
				{
					if (isa<IntegerLiteral>(argArray[0]))
					{
						parseExpression(argArray[1], false, true);
						const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
						int intValue = intVal->getValue().getSExtValue();

						out << "setglobal";
						out << ((intValue & 0xFFFF) == intValue ? "2 " : "3 ");
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

						out << "setglobal";
						out << ((intValue & 0xFFFF) == intValue ? "2 " : "3 ");
						out << intValue << endl;
					}
					else
						Throw("Expected Integer Literal.", rewriter, argArray[0]->getExprLoc());
				}
				else
					Throw("Invalid " + funcName + " Parameters.", rewriter, call->getExprLoc());
			}
			break;
			case JoaatCasedConst("getglobalp"):
			{
				ChkHashCol("getglobalp");
				if (argCount == 1)
				{
					if (isa<IntegerLiteral>(argArray[0]))
					{
						const IntegerLiteral* intVal = cast<IntegerLiteral>(argArray[0]);
						int intValue = intVal->getValue().getSExtValue();

						out << "getglobalp"
							<< ((intValue & 0xFFFF) == intValue ? "2 " : "3 ")
							<< intValue << endl;
						return true;
					}
					else
						Throw("Expected Integer Literal.", rewriter, argArray[0]->getExprLoc());
				}
				else
					Throw("Invalid " + funcName + " Parameters.", rewriter, call->getExprLoc());
			}
			break;
			case JoaatCasedConst("stacktop"):
			{

				ChkHashCol("stacktop");
				if (argCount != 0 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) != 1)
				{
					Throw("stacktop must have signature \"extern __intrinsic int stacktop();\"", rewriter, callee->getSourceRange());
				}
				return true;
			}
			break;
			case JoaatCasedConst("memcpy"):
			{
				ChkHashCol("memcpy");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
				{
					//to stack
					//size
					parseExpression(argArray[2], false, true);
					//src
					parseExpression(argArray[1], true, true);
					out << "ToStack" << endl;


					//from stack
					//size
					parseExpression(argArray[2], false, true);
					//dest
					parseExpression(argArray[0], true, true);
					out << "FromStack" << endl;
				}
				else
					Throw("memcpy must have signature \"extern __intrinsic void memcpy(void* dst, void* src, int len);\"", rewriter, callee->getSourceRange());
				return true;
			}
			break;
			case JoaatCasedConst("creal"):
			{
				ChkHashCol("creal");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isComplexType())
				{
					parseExpression(argArray[0], false, true);
					out << "drop //drop the Imag Part\r\n";
					return true;
				}
				Throw("creal must have signature \"extern __intrinsic int creal(int _Complex complexInteger);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("cimag"):
			{
				ChkHashCol("cimag");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isComplexIntegerType())
				{
					parseExpression(argArray[0], false, true);
					LocalVariables.addLevel();
					int index = LocalVariables.addDecl("imag_part", 1);
					out << frameSet(index) << " //Store Imag Part\r\ndrop\r\n" << frameGet(index) << " //Retrieve Imag Part\r\n";
					LocalVariables.removeLevel();
					return true;
				}
				Throw("cimag must have signature \"extern __intrinsic int cimag(int _Complex complexInteger);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("crealf"):
			{
				ChkHashCol("crealf");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isComplexType())
				{
					parseExpression(argArray[0], false, true);

					out << "drop //drop the Imag Part\r\n";
					return true;
				}
				Throw("crealf must have signature \"extern __intrinsic float crealf(float _Complex complexFloat);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("cimagf"):
			{
				ChkHashCol("cimagf");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isComplexType())
				{
					parseExpression(argArray[0], false, true);
					LocalVariables.addLevel();
					int index = LocalVariables.addDecl("imag_part", 1);
					out << frameSet(index) << " //Store Imag Part\r\ndrop\r\n" << frameGet(index) << " //Retrieve Imag Part\r\n";
					LocalVariables.removeLevel();
					return true;
				}
				Throw("cimagf must have signature \"extern __intrinsic float cimagf(float _Complex complexFloat);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("cconj"):
			{
				ChkHashCol("cconj");
				if (argCount == 1 && callee->getReturnType()->isComplexIntegerType() && argArray[0]->getType()->isComplexIntegerType())
				{
					parseExpression(argArray[0], false, true);
					out << "Neg //Negate the Imag Part\r\n";
					return true;
				}
				Throw("cconj must have signature \"extern __intrinsic int _Complex cconj(int _Complex complexInteger);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("cconjf"):
			{
				ChkHashCol("cconjf");
				if (argCount == 1 && callee->getReturnType()->isComplexType() && argArray[0]->getType()->isComplexType())
				{
					parseExpression(argArray[0], false, true);
					out << "Neg //Negate the Imag Part\r\n";
					return true;
				}
				Throw("cconjf must have signature \"extern __intrinsic float _Complex cconj(float _Complex complexFloat);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("reinterpretIntToFloat"):
			{
				ChkHashCol("reinterpretIntToFloat");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isIntegerType())
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("reinterpretIntToFloat must have signature \"extern __intrinsic float reinterpretIntToFloat(int intValue);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("reinterpretFloatToInt"):
			{
				ChkHashCol("reinterpretFloatToInt");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("reinterpretFloatToInt must have signature \"extern __intrinsic int reinterpretFloatToInt(float floatValue);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("pushFloat"):;
			{
				ChkHashCol("pushFloat");
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("pushFloat must have signature \"extern __intrinsic void pushFloat(float floatValue);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("pushInt"):
			{
				ChkHashCol("pushInt");

				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("pushInt must have signature \"extern __intrinsic void pushInt(int intValue);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("pushStruct"):
			{
				ChkHashCol("pushStruct");
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isVoidPointerType())
				{
					if (isa<CastExpr>(argArray[0]))
					{
						const CastExpr *castee = cast<CastExpr>(argArray[0]);
						if (castee->getCastKind() == CK_BitCast)
						{
							int size = getSizeFromBytes(getSizeOfType(castee->getSubExpr()->getType()->getPointeeType().getTypePtr()));
							if (size > 1)
							{
								out << iPush(size) << "//Struct Size\r\n";
							}
							parseExpression(argArray[0], true, true);
							if (size > 1)
							{
								out << "ToStack\r\n";
							}
							else
							{
								out << "pGet\r\n";
							}
							return true;
						}
					}
					Throw("Couldnt extract type information from the argument in pushStruct", rewriter, argArray[0]->getSourceRange());
					return false;
				}
				Throw("pushStruct must have signature \"extern __intrinsic void pushStruct(void *Struct);\"", rewriter, callee->getSourceRange());
				return false;;
			}
			break;
			case JoaatCasedConst("popStruct"):
			{
				ChkHashCol("popStruct");

				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isVoidPointerType())
				{
					if (isa<CastExpr>(argArray[0]))
					{
						const CastExpr *castee = cast<CastExpr>(argArray[0]);
						if (castee->getCastKind() == CK_BitCast)
						{
							int size = getSizeFromBytes(getSizeOfType(castee->getSubExpr()->getType()->getPointeeType().getTypePtr()));
							if (size > 1)
							{
								out << iPush(size) << "//Struct Size\r\n";
							}
							parseExpression(argArray[0], true, true);
							if (size > 1)
							{
								out << "FromStack\r\n";
							}
							else
							{
								out << "pSet\r\n";
							}
							return true;
						}
					}
					Throw("Couldnt extract type information from the argument in popStruct", rewriter, argArray[0]->getSourceRange());
					return false;
				}
				Throw("popStruct must have signature \"extern __intrinsic void popStruct(void *Struct);\"", rewriter, callee->getSourceRange());
				return false;;
			}
			break;
			case JoaatCasedConst("dupStackTop"):
			{
				ChkHashCol("dupStackTop");

				if (argCount == 0 && callee->getReturnType()->isVoidType())
				{
					out << "dup //dupStackTop\r\n";
					return true;
				}
				Throw("dupStackTop must have signature \"extern __intrinsic void dupStackTop();\"", rewriter, callee->getSourceRange());
			}
			break;
			case JoaatCasedConst("toVector3"):
			{
				ChkHashCol("toVector3");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					out << "FToV\r\n";
					return true;
				}
				Throw("tovector3 must have signature \"extern __intrinsic vector3 tovector3(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("makeVector3"):
			{
				ChkHashCol("makeVector3");

				if (argCount == 3 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && argArray[0]->getType()->isRealFloatingType() && argArray[1]->getType()->isRealFloatingType() && argArray[2]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					parseExpression(argArray[2], false, true);
					return true;
				}
				Throw("makeVector3 must have signature \"extern __intrinsic vector3 makeVector3(float x, float y, float z)\"", rewriter, callee->getSourceRange());
				return false;
			}
			case JoaatCasedConst("vector3Add"):
			{
				ChkHashCol("vector3Add");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					out << "vAdd\r\n";
					return true;
				}
				Throw("vector3Add must have signature \"extern __intrinsic vector3 vector3Add(vector3 left, vector3 right)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vector3Sub"):
			{
				ChkHashCol("vector3Sub");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					out << "vSub\r\n";
					return true;
				}
				Throw("vector3Sub must have signature \"extern __intrinsic vector3 vector3Sub(vector3 left, vector3 right)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vector3Mult"):
			{
				ChkHashCol("vector3Mult");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					out << "vMult\r\n";
					return true;
				}
				Throw("vector3Mult must have signature \"extern __intrinsic vector3 vector3Mult(vector3 left, vector3 right)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vector3Div"):
			{
				ChkHashCol("vector3Div");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					out << "vDiv\r\n";
					return true;
				}
				Throw("vector3Div must have signature \"extern __intrinsic vector3 vector3Div(vector3 left, vector3 right)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vector3Neg"):
			{
				ChkHashCol("vector3Neg");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					out << "vNeg\r\n";
					return true;
				}
				Throw("vector3Neg must have signature \"extern __intrinsic vector3 vector3Neg(vector3 vector)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("fadd"):
			{
				ChkHashCol("fadd");
				if(argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if(argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if(dResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << fPush(dResult) << "\r\nfAdd\r\n";
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fAdd\r\n";
					}
					return true;
				}
				Throw("fadd must have signature \"extern __intrinsic float fadd(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("fsub"):
			{
				ChkHashCol("fsub");
				if(argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if(argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if(dResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << fPush(dResult) << "\r\nfSub\r\n";
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fSub\r\n";
					}
					return true;
				}
				Throw("fsub must have signature \"extern __intrinsic float fsub(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("fmult"):
			{
				ChkHashCol("fmult");
				if(argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if(argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if(dResult == 0)
						{
							out << "Drop\r\nPushF_0\r\n";
						}
						else if(dResult == 1)
						{
							//do nothing here
						}
						else if(dResult == -1)
						{
							//negate
							out << "fNeg\r\n";
						}
						else
						{
							out << fPush(dResult) << "\r\nfMult\r\n";
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fMult\r\n";
					}
					return true;
				}
				Throw("fmult must have signature \"extern __intrinsic float fmult(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("fdiv"):
			{
				ChkHashCol("fdiv");
				if(argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if(argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if(dResult == 0)
						{
							Warn("Zero division error detected", rewriter, argArray[0]->getSourceRange());//just warn the user of the undefined behaviour
						}
						else if(dResult == 1)
						{
							//do nothing here
						}
						else if(dResult == -1)
						{
							//negate
							out << "fNeg\r\n";
						}
						else
						{
							out << fPush(dResult) << "\r\nfDiv\r\n";
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fDiv\r\n";
					}
					return true;
				}
				Throw("fdiv must have signature \"extern __intrinsic float fdiv(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			default:
			Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
		}

		#undef ChkHashCol

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
		Expr::EvalResult result;
		if (e->EvaluateAsRValue(result, *context))
		{
			if (!result.HasSideEffects)
			{
				if (result.Val.isInt())
				{
					int val;
					if (CheckExprForSizeOf(e->IgnoreParens(), &val))
						out << iPush(val) << endl;
					else
						out << iPush(result.Val.getInt().getSExtValue()) << endl;
					return -1;
				}
				else if (result.Val.isFloat())
				{
					out << fPush(result.Val.getFloat()) << endl;
					return -1;
				}
				else if (result.Val.isComplexFloat())
				{
					out << fPush(result.Val.getComplexFloatReal()) << endl;
					out << fPush(result.Val.getComplexFloatImag()) << endl;
					return -1;
				}
				else if (result.Val.isComplexInt())
				{
					out << iPush(result.Val.getComplexIntReal().getSExtValue()) << endl;
					out << iPush(result.Val.getComplexIntImag().getSExtValue()) << endl;
					return -1;
				}
			}
		}
		if (isa<IntegerLiteral>(e)) {
			out << iPush(cast<const IntegerLiteral>(e)->getValue().getSExtValue()) << endl;
		}
		else if (isa<FloatingLiteral>(e)) {
			out << fPush(cast<const FloatingLiteral>(e)->getValue()) << endl;
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
			const Expr* callee = call->getCallee();

			if (isa<MemberExpr>(callee))
			{
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
			else if (isa<CastExpr>(callee))
			{
				const Expr * const*argArray = call->getArgs();
				std::string funcName = parseCast(cast<const CastExpr>(call->getCallee()));
				for (uint32_t i = 0; i < call->getNumArgs(); i++)
					parseExpression(argArray[i], false, true);
				if (call->getDirectCallee() && call->getDirectCallee()->hasAttr<NativeFuncAttr>())
				{
					if (call->getDirectCallee()->getStorageClass() != SC_Extern)
					{
						Throw("Natives should be defined with the 'extern' keyword", rewriter, call->getDirectCallee()->getLocation());
					}
					const QualType type = call->getDirectCallee()->getReturnType();
					out << "CallNative " << (parseCast(cast<const CastExpr>(callee)).c_str() + 1) << " " << call->getNumArgs() << " " << getSizeFromBytes(getSizeOfQualType(&type)) << endl;
				}
				else if (call->getDirectCallee() && !call->getDirectCallee()->isDefined() && call->getDirectCallee()->getStorageClass() != StorageClass::SC_Extern)
					Throw("Function \"" + call->getDirectCallee()->getNameAsString() + "\" Not Defined", rewriter, call->getExprLoc());
				else if (isa<PointerType>(callee->getType()) && !call->getDirectCallee())
				{
					parseExpression(call->getCallee());
					out << "PCall\r\n";
				}
				else
				{
					bool inlined = false;
					if (const FunctionDecl * cDecl = call->getDirectCallee())
					{
						string name = dumpName(cast<NamedDecl>(cDecl));
						string curName = dumpName(cast<NamedDecl>(currFunction));
						if (cDecl->hasBody() && !isFunctionInInline(name) && curName != name)
						{
							Stmt *body = cDecl->getBody();
							Stmt *subBody = body;
							bool isEmpty = false;
							if (isa<CompoundStmt>(body))
							{
								if (cast<CompoundStmt>(body)->size() == 0)
								{
									isEmpty = true;
								}
								else if (cast<CompoundStmt>(body)->size() == 1)
								{
									subBody = cast<CompoundStmt>(body)->body_front();
								}
							}
							if (isEmpty)
							{
								inlined = true;
								for (uint32_t i = 0; i < cDecl->getNumParams(); i++)
								{
									for (int32_t paramSize = getSizeFromBytes(getSizeOfType(cDecl->getParamDecl(i)->getType().getTypePtr())); paramSize--;)
									{
										out << "Drop\r\n";
									}
								}
							}
							else
							{
								bool noInline = cDecl->hasAttr<NoInlineAttr>();
								bool isRet = isa<ReturnStmt>(subBody);
								bool isExpr = isa<Expr>(subBody);
								bool inlineSpec = cDecl->isInlineSpecified();
								if (!noInline && (isRet || isExpr || inlineSpec)) //inline it
								{
									inlined = true;
									if (!addFunctionInline(name))
									{
										assert(false);
									}
									LocalVariables.addLevel();
									int Index = LocalVariables.getCurrentSize();
									int32_t paramSize = 0;
									for (uint32_t i = 0; i < cDecl->getNumParams(); i++)
									{
										paramSize += getSizeFromBytes(getSizeOfType(cDecl->getParamDecl(i)->getType().getTypePtr()));
										handleParmVarDecl((ParmVarDecl*)(cDecl->getParamDecl(i)));
									}
									if (paramSize == 1)
									{
										out << frameSet(Index) << endl;
									}
									else if (paramSize > 1)
									{
										out << iPush(paramSize) << endl << pFrame(Index) << "\r\nFromStack\r\n";
									}
									if (isRet) {
										if (Expr* retval = cast<ReturnStmt>(subBody)->getRetValue())
											parseExpression(retval, false, true);
									}
									else if (isExpr)
									{
										parseExpression(cast<Expr>(subBody));
									}
									else
									{
										parseStatement(body, -1, -1, e->getLocEnd().getRawEncoding());
										out << ":" << e->getLocEnd().getRawEncoding() << endl;
									}
									LocalVariables.removeLevel();
									removeFunctionInline(name);

								}
							}

						}
					}
					if (!inlined)
					{
						string name = parseCast(cast<const CastExpr>(callee));
						uint32_t hash = Utils::Hashing::Joaat((char*)name.c_str());
						uint32_t i = 0;
						for (; i < functions.size(); i++)
							if (functions[i].hash == hash)
							{
								if (functions[i].name == name)
								{
									functions[i].isused = true;
									break;
								}
							}
						if (i >= functions.size())
							Throw("Function \"" + name + "\" not found", rewriter, call->getExprLoc());

						out << "Call " << name << " //NumArgs: " << call->getNumArgs() << " " << endl;
					}

				}

				if (call->getType()->isVoidType() == false) {
					if (!isLtoRValue) {
						out << "Drop//Function Result unused" << endl;
						int size = getSizeFromBytes(getSizeOfType(call->getType().getTypePtr()));
						for (int i = 1; i<size; i++)
							out << "Drop" << endl;
					}
				}
			}
			else
				Throw("Unexpected Expression for Callee!", rewriter, callee->getExprLoc());
			return 1;

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
					if (!isLtoRValue)
					{
						for (int i = getSizeFromBytes(getSizeOfType(icast->getSubExpr()->getType().getTypePtr())); i--;)
						{
							out << "drop //unused result\r\n";
						}
					}
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
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					break;
				}
				case clang::CK_BitCast:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					break;
				}
				case clang::CK_IntegralToBoolean:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					break;
				}
				case clang::CK_FloatingToBoolean:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					out << fPush(0.0f) << "\r\nfCmpNe\r\n";
					break;
				}
				case clang::CK_FloatingComplexToReal:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					out << "Drop\r\n";
					break;
				}
				case clang::CK_IntegralComplexToReal:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					out << "Drop\r\n";
					break;
				}
				case clang::CK_NullToPointer:
				{
					parseExpression(icast->getSubExpr());
					break;
				}
				case clang::CK_FloatingRealToComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					out << "PushF_0\r\n"; //Push 0.0f for imag part
					break;
				}
				case clang::CK_IntegralRealToComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					out << "Push_0\r\n"; //Push 0 for imag part
					break;
				}
				case clang::CK_FloatingComplexToIntegralComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					LocalVariables.addLevel();
					int index = LocalVariables.addDecl("imagPart", 1);
					out << frameSet(index) << "\r\nFtoI\r\n" << frameGet(index) << "\r\nFtoI\r\n";
					LocalVariables.removeLevel();
					break;
				}
				case clang::CK_IntegralComplexToFloatingComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					LocalVariables.addLevel();
					int index = LocalVariables.addDecl("imagPart", 1);
					out << frameSet(index) << "\r\ItoF\r\n" << frameGet(index) << "\r\ItoF\r\n";
					LocalVariables.removeLevel();
					break;
				}
				case clang::CK_FloatingComplexCast:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					break;
				}
				case clang::CK_IntegralComplexCast:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					break;
				}
				case clang::CK_FloatingComplexToBoolean:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					LocalVariables.addLevel();
					int index = LocalVariables.addDecl("imagPart", 1);
					out << frameSet(index) << "\r\PushF_0\r\nfCmpEq\r\n" << frameGet(index) << "r\PushF_0\r\nfCmpEq\r\nAnd\r\n";
					LocalVariables.removeLevel();
					break;
				}
				case clang::CK_IntegralComplexToBoolean:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					LocalVariables.addLevel();
					int index = LocalVariables.addDecl("imagPart", 1);
					out << frameSet(index) << "\r\Push_0\r\nCmpEq\r\n" << frameGet(index) << "r\Push_0\r\nCmpEq\r\nAnd\r\n";
					LocalVariables.removeLevel();
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
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nfNeg\r\n" << frameGet(index) << "\r\nfNeg\r\n";
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nNeg\r\n" << frameGet(index) << "\r\nNeg\r\n";
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isRealFloatingType())
					{
						out << "fNeg\r\n";
					}
					else
					{
						out << "Neg\r\n";
					}

				}
				else
				{
					out << "unimplmented UO_MINUS" << endl;
				}
				return false;
			}
			else if (op->getOpcode() == UO_LNot) {
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					out << iPush(!literal->getValue().getSExtValue()) << endl;

				}
				else if (isa<FloatingLiteral>(subE))
				{
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);
					out << fPush(!literal->getValue().convertToDouble()) << endl;

				}
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nPushF_0\r\nfCmpEq\r\n" << frameGet(index) << "\r\nPushF_0\r\nfCmpEq\r\nAnd\r\n";
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nnot\r\n" << frameGet(index) << "\r\nnot\r\nAnd\r\n";
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isFloatingType())
					{
						out << "PushF_0\r\nfCmpEq\r\n";
					}
					else
					{
						out << "not\r\n";
					}

				}
				else
				{
					out << "unimplmented UO_LNot" << endl;
				}

				return true;
			}
			else if (op->getOpcode() == UO_Not)
			{
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					out << iPush(~literal->getValue().getSExtValue()) << endl;

				}
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					//Not operator for complex numbers is the conjugate
					if (subE->getType()->isComplexIntegerType())
					{
						out << "Neg\r\n";
					}
					else if (subE->getType()->isComplexType())
					{
						out << "fNeg\r\n";
					}
					else
					{
						out << "Add1 1\r\nNeg\r\n";
					}
				}
				else
				{
					out << "unimplmented UO_Not" << endl;
				}
				return true;
			}
			else if (op->getOpcode() == UO_AddrOf) {
				if (isa<ArraySubscriptExpr>(subE)) {
					parseArraySubscriptExpr(subE, true);
				}
				else if (isa<DeclRefExpr>(subE)) {
					parseExpression(subE, true, false);
					if (!isLtoRValue) {
						out << "Drop //unused result\r\n";
					}
				}
				else {
					parseExpression(subE, true, false);
					if (!isLtoRValue) {
						out << "Drop //unused result\r\n";
					}
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
				if (!isAddr)
				{
					if (isLtoRValue)
						out << "pGet" << endl;
					else
						out << "pSet" << endl;
				}

				return true;
			}
			else if (op->getOpcode() == UO_Real)
			{
				if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (subE->getType()->isAnyComplexType())
					{
						out << "Drop\r\n";
					}
					else
					{
						Throw("__real operator used on non complex data type");
					}
				}
				else
				{
					out << "unimplmented UO_Real" << endl;
				}
			}
			else if (op->getOpcode() == UO_Imag)
			{
				if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (subE->getType()->isAnyComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nDrop\r\n" << frameGet(index) << endl;
					}
					else
					{
						Throw("__imag operator used on non complex data type");
					}
				}
				else
				{
					out << "unimplmented UO_Real" << endl;
				}
			}


			string pMult = "";
			if ((op->isPrefix() || op->isPostfix()) && isa<PointerType>(subE->getType()))
			{
				const Type* pTypePtr = subE->getType().getTypePtr()->getPointeeType().getTypePtr();
				int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
				int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;
				pMult = "\r\n" + mult(pSize) + "\r\n";
			}

			if (op->isPrefix()) {

				if (op->isIncrementOp()) {
					parseExpression(subE, false, true);
					out << "Push 1" << pMult << endl;
					out << "Add" << endl;
					if (isLtoRValue)
						out << "Dup" << endl;
					parseExpression(subE);
					return 1;
				}
				else if (op->isDecrementOp()) {
					parseExpression(subE, false, true);
					out << "Push 1" << pMult << endl;
					out << "Sub" << endl;
					if (isLtoRValue)
						out << "Dup" << endl;
					parseExpression(subE);
					return 1;
				}
			}
			else if (op->isPostfix()) {
				if (op->isIncrementOp()) {
					parseExpression(subE, false, true);
					if (isLtoRValue)
						out << "Dup" << endl;
					out << "Push 1" << pMult << endl;
					out << "Add" << endl;
					parseExpression(subE, false, false);
					return 1;
				}
				else if (op->isDecrementOp()) {
					parseExpression(subE, false, true);

					out << "Push 1" << pMult << endl;
					if (isLtoRValue)
						out << "Dup" << endl;
					out << "Sub" << endl;
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
				int bSize = getSizeFromBytes(getSizeOfType(bOp->getRHS()->getType().getTypePtr()));
				if (bSize > 1)
				{
					out << iPush(bSize) << endl;
					parseExpression(bOp->getLHS(), true);
					out << "FromStack\r\n";
					if (isLtoRValue)
					{
						parseExpression(bOp->getLHS(), false, true);
					}
				}
				else {
					if (isLtoRValue)
					{
						out << "dup //duplicate value for set\r\n";
					}
					parseExpression(bOp->getLHS());
				}

				return true;
			}
			if (bOp->getOpcode() == BO_Comma)
			{
				parseExpression(bOp->getLHS());
				parseExpression(bOp->getRHS(), false, true);
				return true;
			}
			if (bOp->getOpcode() == BO_LAnd)
			{
				parseExpression(bOp->getLHS(), false, true);
				out << "dup\r\nJumpFalse @" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				parseExpression(bOp->getRHS(), false, true);
				out << "and\r\n\r\n:" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				return true;
			}
			if (bOp->getOpcode() == BO_LOr)
			{
				parseExpression(bOp->getLHS(), false, true);
				out << "dup\r\nnot\r\nJumpFalse @" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				parseExpression(bOp->getRHS(), false, true);
				out << "or\r\n\r\n:" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				return true;
			}


			if (bOp->getLHS()->getType()->isAnyComplexType() || bOp->getRHS()->getType()->isAnyComplexType())
			{
				if (currFunction)
				{
					parseExpression(bOp->getLHS(), isAddr, true, true);
					if (!bOp->getLHS()->getType()->isAnyComplexType())
					{
						if (bOp->getLHS()->getType()->isFloatingType())
						{
							out << "PushF_0\r\n";
						}
						else
						{
							out << "Push_0\r\n";
						}
					}
					parseExpression(bOp->getRHS(), isAddr, true, true);
					if (!bOp->getRHS()->getType()->isAnyComplexType())
					{
						if (bOp->getRHS()->getType()->isFloatingType())
						{
							out << "PushF_0\r\n";
						}
						else
						{
							out << "Push_0\r\n";
						}
					}
					bool isFlt = bOp->getLHS()->getType()->isFloatingType();
					string isFloat = isFlt ? "f" : "";
					if (!isFlt)
					{
						if (bOp->getRHS()->getType()->isFloatingType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("imagPart", 1);
							out << frameSet(index) << "\r\nFtoI\r\n" << frameGet(index) << "\r\nFtoI\r\n";
							LocalVariables.removeLevel();
						}
					}
					else
					{
						if (!bOp->getRHS()->getType()->isFloatingType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("imagPart", 1);
							out << frameSet(index) << "\r\nItoF\r\n" << frameGet(index) << "\r\nItoF\r\n";
							LocalVariables.removeLevel();
						}
					}
					LocalVariables.addLevel();
					int startindex = LocalVariables.addDecl("complex", 4);
					out << "Push_4\r\n" << pFrame(startindex) << "\r\nFromStack\r\n";

					switch (bOp->getOpcode())
					{
						case BO_Add:
						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Add //Calc Real Part\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Add //Calc Imag Part\r\n";
						break;
						case BO_AddAssign:
						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Add //Calc Real Part\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Add //Calc Imag Part\r\n";
						out << "Push_2 //Type Size\r\n";
						parseExpression(bOp->getLHS(), true);
						out << "FromStack\r\n";
						case BO_Sub:
						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Sub //Calc Real Part\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Sub //Calc Imag Part\r\n";
						break;
						case BO_SubAssign:
						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Sub //Calc Real Part\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Sub //Calc Imag Part\r\n";
						out << "Push_2 //Type Size\r\n";
						parseExpression(bOp->getLHS(), true);
						out << "FromStack\r\n";
						break;
						case BO_Mul:
						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Sub //Calc Real Part\r\n";

						out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Add //Calc Imag Part\r\n";
						break;
						case BO_MulAssign:
						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Sub //Calc Real Part\r\n";

						out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Add //Calc Imag Part\r\n";
						out << "Push_2 //Type Size\r\n";
						parseExpression(bOp->getLHS(), true);
						out << "FromStack\r\n";
						break;
						case BO_Div:
						LocalVariables.addDecl("divide", 1);
						out << frameGet(startindex + 2) << "\r\nDup\r\n" << isFloat << "Mul\r\n";
						out << frameGet(startindex + 3) << "\r\nDup\r\n" << isFloat << "Mul\r\n";
						out << isFloat << "Add //Calc Comp Denominator\r\n" << frameSet(startindex + 4) << endl;

						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Add //Calc Real Part\r\n";
						out << frameGet(startindex + 4) << endl << isFloat << "Div\r\n";

						out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Sub //Calc Imag Part\r\n";
						out << frameGet(startindex + 4) << endl << isFloat << "Div\r\n";
						break;
						case BO_DivAssign:
						LocalVariables.addDecl("divide", 1);
						out << frameGet(startindex + 2) << "\r\nDup\r\n" << isFloat << "Mul\r\n";
						out << frameGet(startindex + 3) << "\r\nDup\r\n" << isFloat << "Mul\r\n";
						out << isFloat << "Add //Calc Comp Denominator\r\n" << frameSet(startindex + 4) << endl;

						out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Add //Calc Real Part\r\n";
						out << frameGet(startindex + 4) << endl << isFloat << "Div\r\n";

						out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
						out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
						out << isFloat << "Sub //Calc Imag Part\r\n";
						out << frameGet(startindex + 4) << endl << isFloat << "Div\r\n";
						out << "Push_2 //Type Size\r\n";
						parseExpression(bOp->getLHS(), true);
						out << "FromStack\r\n";
						break;

						case BO_LAnd:
						if (!isFlt)
						{
							out << frameGet(startindex) << "\r\nPush_0\r\nCmpNe\r\n" << frameGet(startindex + 1) << "\r\nPush_0\r\nCmpNe\r\nOr\r\n";
							out << frameGet(startindex + 2) << "\r\nPush_0\r\nCmpNe\r\n" << frameGet(startindex + 3) << "\r\nPush_0\r\nCmpNe\r\nOr\r\n";
						}
						else
						{
							out << frameGet(startindex) << "\r\nPushF_0\r\nfCmpNe\r\n" << frameGet(startindex + 1) << "\r\nPushF_0\r\nfCmpNe\r\nOr\r\n";
							out << frameGet(startindex + 2) << "\r\nPushF_0\r\nfCmpNe\r\n" << frameGet(startindex + 3) << "\r\nPushF_0\r\nfCmpNe\r\nOr\r\n";
						}
						out << "And\r\n";
						break;
						case BO_LOr:
						if (!isFlt)
						{
							out << frameGet(startindex) << "\r\nPush_0\r\nCmpNe\r\n" << frameGet(startindex + 1) << "\r\nPush_0\r\nCmpNe\r\nOr\r\n";
							out << frameGet(startindex + 2) << "\r\nPush_0\r\nCmpNe\r\n" << frameGet(startindex + 3) << "\r\nPush_0\r\nCmpNe\r\nOr\r\n";
						}
						else
						{
							out << frameGet(startindex) << "\r\nPushF_0\r\nfCmpNe\r\n" << frameGet(startindex + 1) << "\r\nPushF_0\r\nfCmpNe\r\nOr\r\n";
							out << frameGet(startindex + 2) << "\r\nPushF_0\r\nfCmpNe\r\n" << frameGet(startindex + 3) << "\r\nPushF_0\r\nfCmpNe\r\nOr\r\n";
						}
						out << "Or\r\n";
						break;
						default:
						Throw("Unsupported binary operator \"" + bOp->getOpcodeStr().str() + "\" for Complex data type", rewriter, bOp->getOperatorLoc());
					}
					LocalVariables.removeLevel();
					return true;
				}
				else
				{
					Throw("Complex binary operations can only be done in functions");
				}

			}


			#define OpAssign(op, isfloat)\
			parseExpression(bOp->getLHS(), true, false);\
			out << "dup\r\npGet\r\n";\
			parseExpression(bOp->getRHS(), false, true);\
			if (isa<PointerType>(bOp->getLHS()->getType()))\
			{\
				const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();\
				out << mult(getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr)) + "\r\n";\
			}\
			if (bOp->getLHS()->getType()->isFloatingType() && isfloat)\
				out << "f" << op << "\r\npPeekSet\r\nDrop\r\n";\
			else\
			{\
				out << op << "\r\npPeekSet\r\nDrop\r\n";\
			}

			switch (bOp->getOpcode()) {

				case BO_SubAssign:
				{
					parseExpression(bOp->getLHS(), true, false);
					out << "dup\r\npGet\r\n";
					llvm::APSInt intRes;
					if (bOp->getRHS()->EvaluateAsInt(intRes, *context))
					{
						int64_t val = intRes.getSExtValue();
						if (isa<PointerType>(bOp->getLHS()->getType()))
						{
							const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
							out << sub(val * getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr)) << "\r\npPeekSet\r\nDrop\r\n";
						}
						else
						{
							out << sub(val) << "\r\npPeekSet\r\nDrop\r\n";
						}
					}
					else
					{
						parseExpression(bOp->getRHS(), false, true);
						if (isa<PointerType>(bOp->getLHS()->getType()))
						{
							const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
							out << mult(getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr)) + "\r\n";
						}
						if (bOp->getLHS()->getType()->isFloatingType())
							out << "fsub" << "\r\npPeekSet\r\nDrop\r\n";
						else
						{
							out << "Sub" << "\r\npPeekSet\r\nDrop\r\n";
						}
					}
				}
				break;
				case BO_AddAssign:
				{
					parseExpression(bOp->getLHS(), true, false);
					out << "dup\r\npGet\r\n";
					llvm::APSInt intRes;
					if (bOp->getRHS()->EvaluateAsInt(intRes, *context))
					{
						int64_t val = intRes.getSExtValue();
						if (isa<PointerType>(bOp->getLHS()->getType()))
						{
							const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
							out << add(val * getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr)) << "\r\npPeekSet\r\nDrop\r\n";
						}
						else
						{
							out << add(val) << "\r\npPeekSet\r\nDrop\r\n";
						}
					}
					else
					{
						parseExpression(bOp->getRHS(), false, true);
						if (isa<PointerType>(bOp->getLHS()->getType()))
						{
							const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
							out << mult(getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr)) + "\r\n";
						}
						if (bOp->getLHS()->getType()->isFloatingType())
							out << "fadd" << "\r\npPeekSet\r\nDrop\r\n";
						else
						{
							out << "Add" << "\r\npPeekSet\r\nDrop\r\n";
						}
					}
				}
				break;
				case BO_DivAssign:  OpAssign("Div", true); break;
				case BO_MulAssign:  OpAssign("Mult", true); break;
				case BO_OrAssign:  OpAssign("Or", false); break;
				case BO_AndAssign:  OpAssign("And", false); break;
				case BO_RemAssign:  OpAssign("Mod", true); break;
				case BO_XorAssign:  OpAssign("Xor", false); break;
				case BO_ShlAssign:  OpAssign("CallNative shift_left 2 1", false); break;
				case BO_ShrAssign:  OpAssign("CallNative shift_right 2 1", false); break;
				default:
				{
					parseExpression(bOp->getLHS(), false, true);
					if (isa<PointerType>(bOp->getLHS()->getType()))
					{
						const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
						int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
						int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;
						out << mult(pSize) + "\r\n";
					}
					parseExpression(bOp->getRHS(), false, true);
					if (bOp->getLHS()->getType()->isFloatingType()) {
						switch (bOp->getOpcode()) {
							case BO_EQ: out << "fCmpEQ\r\n"; break;
							case BO_Mul: out << "fMult\r\n"; break;
							case BO_Div: out << "fDiv\r\n"; break;
							case BO_Rem: out << "fMod\r\n"; break;
							case BO_Sub: out << "fSub\r\n"; break;
							case BO_LT: out << "fCmpLT\r\n"; break;
							case BO_GT: out << "fCmpGT\r\n"; break;
							case BO_GE: out << "fCmpGE\r\n"; break;
							case BO_LE: out << "fCmpLE\r\n"; break;
							case BO_NE: out << "fCmpNE\r\n"; break;
							case BO_LAnd:
							case BO_And: out << "And\r\n"; break;
							case BO_Xor: out << "Xor\r\n"; break;
							case BO_Add: out << "fAdd\r\n"; break;
							case BO_LOr:
							case BO_Or: out << "Or\r\n"; break;
							case BO_Shl: out << "CallNative shift_left 2 1\r\n"; break;
							case BO_Shr: out << "CallNative shift_right 2 1\r\n"; break;
							default:
							Throw("Unimplemented binary floating op " + bOp->getOpcodeStr().str(), rewriter, bOp->getExprLoc());
						}

					}
					else {
						switch (bOp->getOpcode()) {
							case BO_EQ: out << "CmpEQ\r\n"; break;
							case BO_Mul: out << "Mult\r\n"; break;
							case BO_Div: out << "Div\r\n"; break;
							case BO_Rem: out << "Mod\r\n"; break;
							case BO_Sub: out << "Sub\r\n"; break;
							case BO_LT: out << "CmpLT\r\n"; break;
							case BO_GT: out << "CmpGT\r\n"; break;
							case BO_GE: out << "CmpGE\r\n"; break;
							case BO_LE: out << "CmpLE\r\n"; break;
							case BO_NE: out << "CmpNE\r\n"; break;
							case BO_LAnd:
							case BO_And: out << "And\r\n"; break;
							case BO_Xor: out << "Xor\r\n"; break;
							case BO_Add: out << "Add\r\n"; break;
							case BO_LOr:
							case BO_Or: out << "Or\r\n"; break;
							case BO_Shl: out << "CallNative shift_left 2 1\r\n"; break;
							case BO_Shr: out << "CallNative shift_right 2 1\r\n"; break;
							default:
							Throw("Unimplemented binary op " + bOp->getOpcodeStr().str(), rewriter, bOp->getExprLoc());
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

			if (size > 0) {
				out << add(size * 4) << " // ." << ND->getName().str() << "\r\n";
			}
			else
			{
				out << "// ." << ND->getName().str() << "\r\n";
			}


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
					else//size = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
						size = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
					//size = context->getTypeInfoDataSizeInChars(ueTrait->getArgumentExpr()->getType()).first.getQuantity();



					//Pause("SIZE: " + to_string(size) + "\r\n");
					if (isLtoRValue)
						out << "Push " << size << endl;

				}
				break;
				case UnaryExprOrTypeTrait::UETT_JenkinsHash:
				{
					if (const Expr* arg = ueTrait->getArgumentExpr()->IgnoreParens())
					{
						if (isa<StringLiteral>(arg))
						{
							string str = cast<StringLiteral>(arg)->getString().str();
							out << iPush((int)Utils::Hashing::Joaat((char*)str.c_str())) << " //Joaat(\"" << str << "\")\r\n";
							break;
						}
						Throw("Jenkins Method called with unsupported arg type, please use a StringLiteral argument", rewriter, arg->getLocStart());
						break;
					}
				}
				Throw("Jenkins Method called without any argument, please use a StringLiteral argument", rewriter, ueTrait->getLocStart());
				break;
				default:
				Throw("Unsupported UnaryExprOrTypeTrait Type:" + to_string(ueTrait->getKind()), rewriter, ueTrait->getLocStart());
				break;
			}
		}
		else if (isa<ConditionalOperator>(e))
		{
			if (!isLtoRValue)
				Throw("Invalid Use Of Operator", rewriter, e->getExprLoc());
			const ConditionalOperator *cond = cast<const ConditionalOperator>(e);

			parseJumpFalseCondition(cond->getCond());
			out << cond->getRHS()->getLocStart().getRawEncoding() << endl;
			parseExpression(cond->getLHS(), false, true);
			out << "Jump @" << cond->getLHS()->getLocEnd().getRawEncoding() << endl;

			out << ":" << cond->getRHS()->getLocStart().getRawEncoding() << endl;
			parseExpression(cond->getRHS(), false, true);
			out << ":" << cond->getLHS()->getLocEnd().getRawEncoding() << endl;
		}
		else if (isa<ImaginaryLiteral>(e))
		{
			Warn("Imaginary literals aren't supported", rewriter, e->getExprLoc());
			/*const ImaginaryLiteral *literal = cast<ImaginaryLiteral>(e);
			const Expr* item = literal->getSubExpr();
			if (isa<FloatingLiteral>(item))
			{
			Warn("Temp");
			}
			else if (isa<IntegerLiteral>(item))
			{
			Warn("Temp");
			}
			out << "imaginary_literal_push" << endl;*/

		}
		else if (isa<GenericSelectionExpr>(e))
		{
			const GenericSelectionExpr *gse = cast<GenericSelectionExpr>(e);
			parseExpression(gse->getResultExpr(), isAddr, isLtoRValue);
		}
		else if (isa<BinaryConditionalOperator>(e))
		{
			const BinaryConditionalOperator *bco = cast<BinaryConditionalOperator>(e);

			//out << "COND:" << endl;
			parseExpression(bco->getCond(), false, true);
			out << "dup\r\n";
			out << "JumpFalse @" << bco->getFalseExpr()->getExprLoc().getRawEncoding() << endl;

			//out << "//TRUE: " << endl;
			//parseExpression(bco->getTrueExpr(), false, true);
			out << "Jump @" << bco->getLocStart().getRawEncoding() << endl;

			//out << "//FALSE: " << endl;
			out << ":" << bco->getFalseExpr()->getExprLoc().getRawEncoding() << endl;
			out << "drop\r\n";
			parseExpression(bco->getFalseExpr(), false, true);
			out << ":" << bco->getLocStart().getRawEncoding() << endl;
		}
		else if (isa<OpaqueValueExpr>(e))
		{
			const OpaqueValueExpr *ov = cast<OpaqueValueExpr>(e);
			parseExpression(ov->getSourceExpr(), isAddr, isLtoRValue);
		}
		else
			Throw("Unimplemented expression " + string(e->getStmtClassName()), rewriter, e->getExprLoc());

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


		if (!addrOf && !LValueToRValue)
		{
			//1 byte indexing
			if (type->isCharType())
			{
				//mod for narrowing conversion
				out << "PushS 256\r\nMod\r\nPushB 24\r\nCallNative shift_left 2 1\r\n";
				parseExpression(base, true);
				parseExpression(index, false, true);
				out << mult(getSizeOfType(type)) << "\r\nAdd\r\npGet\r\nPushI24 0xFFFFFF\r\nand\r\nor\r\n";
			}
			//2 byte indexing
			else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
			{
				//mod for narrowing conversion
				out << "Pushi24 65536\r\nMod\r\nPushB 16\r\nCallNative shift_left 2 1\r\n";
				parseExpression(base, true);
				parseExpression(index, false, true);
				out << mult(getSizeOfType(type)) << "\r\nAdd\r\npGet\r\nPushI24 0xFFFF\r\nand\r\nor\r\n";
			}
		}


		parseExpression(base, true);
		parseExpression(index, false, true);


		if (LValueToRValue && !addrOf)
		{
			out << mult(getSizeOfType(type)) << "\r\nAdd\r\npGet//GetArray2\r\n";

			//1 byte indexing
			if (type->isCharType())
				out << "PushB 24\r\nCallNative shift_right 2 1\r\n";
			//2 byte indexing
			else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
				out << "PushB 16\r\nCallNative shift_right 2 1\r\n";

		}
		else if (addrOf)
		{
			int size = getSizeOfType(type);
			if (type->isArrayType())
				size = getSizeFromBytes(size) * 4;

			out << mult(size) << "\r\nAdd//GetArrayP2\r\n";
		}
		else
		{
			out << mult(getSizeOfType(type)) << "\r\nAdd\r\npSet//SetArray2\r\n";
		}


		return true;
	}

	bool VisitFunctionDecl(FunctionDecl *f) {
		// Only function definitions (with bodies), not declarations.
		int funcNum = 0;
		if (f->hasBody()) {
			out.seekg(0, ios::end);
			functions.push_back({ Utils::Hashing::Joaat((char*)getNameForFunc(f).c_str()), getNameForFunc(f), false, out.tellg() });

			if (isa<CXXConstructorDecl>(f))
				return true;

			Stmt *FuncBody = f->getBody();

			int32_t paramSize = 0;
			for (uint32_t i = 0; i<f->getNumParams(); i++)
				paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));


			out << endl << "//Loc: " << f->getBody()->getLocStart().getRawEncoding() << endl;
			string name = dumpName(cast<NamedDecl>(f));
			out << ":" << name << endl;

			if (f->isMain())
			{
				functions.back().isused = true;
				QualType type = f->getReturnType();
				MainRets = Utils::Math::DivInt(getSizeOfQualType(&type), 4);
			}

			out << "Function " << to_string(paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0)) << " ";

			int32_t FunctionStackCountLocation = out.tellp();

			//write stack count buffer as 5 spaces because max stack size of function is 65536
			out << "     ";


			out << "\r\n//" + getNameForFunc(f) + "\r\n";

			currFunction = f;
			LocalVariables.reset();
			if (isa<CXXMethodDecl>(f))
				LocalVariables.addDecl("", 1);

			for (uint32_t i = 0; i<f->getNumParams(); i++)
				handleParmVarDecl(f->getParamDecl(i));

			LocalVariables.addDecl("", 2);//base pointer and return address
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
			//uint32_t FunctionStackCount = LocalVariables.maxIndex - (isa<CXXMethodDecl>(f) ? 1 : 0) - paramSize;
			uint32_t FunctionStackCount = LocalVariables.maxIndex;
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

			LocalVariables.reset();
			LocalVariables.addDecl(d->getDeclName().getAsString(), 1);

			out << endl << endl;
			out << ":" << getLocStart(CS) << endl << ":" << CS->getDeclName().getAsString() << endl << "Function " << CS->getNumParams() + 1 << "//" << getNameForFunc(CS) << endl;
			currFunction = CS;

			for (auto *PI : CS->params()) {
				handleParmVarDecl(PI);
			}

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

			out << "#FuncEnd L " << LocalVariables.getCurrentSize() - (isa<CXXMethodDecl>(CS) ? 1 : 0) << endl << endl;
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

				string strlit = literal->getString().str();
				e->getType().getTypePtr();

				int32_t strsize = getLiteralSizeOfType(e->getType().getTypePtr());

				//int32_t StrIntSize = (literal->getString().str().length() + 4 - 1) & ~3;
				//int32_t StrRem = StrIntSize - literal->getString().str().length();
				//
				//int32_t LoopSize = StrIntSize / 4;


				int32_t buffer = 0;
				int32_t i = 0, b = 0;
				for (; i < strsize; i++, b++)
				{
					if (b >= 4)
					{
						DefaultStaticValues.insert({ oldStaticInc++, to_string(Utils::Bitwise::SwapEndian(buffer)) });
						b = 0;
						buffer = 0;
					}
					if (i >= strlit.length())
						((uint8_t*)&buffer)[b] = 0;//add padding
					else
						((uint8_t*)&buffer)[b] = strlit[i];



				}
				if (b != 0)
					DefaultStaticValues.insert({ oldStaticInc++, to_string(Utils::Bitwise::SwapEndian(buffer)) });

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
					Throw("Unimplemented CK_ArrayToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()), rewriter, icast->getSubExpr()->getExprLoc());
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
					InitializationStack.push({ (int32_t)fltliteral, FBWT_INT });
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

						InitializationStack.push({ 0, FBWT_ARRAY });

						string name = "@" + decl->getNameAsString();
						uint32_t hash = Utils::Hashing::Joaat((char*)name.c_str());
						uint32_t i = 0;
						for (; i < functions.size(); i++)
						{
							if (functions[i].hash == hash)
							{
								if (functions[i].name == name)
								{
									functions[i].isused = true;
									break;
								}
							}
						}

						if (i >= functions.size())
							Throw("Static function pointer \"" + decl->getNameAsString() + "\" not found");

						string funcname = "GetLoc(\"" + decl->getNameAsString() + "\")";
						DefaultStaticValues.insert({ oldStaticInc++, funcname });

					}
					else Throw("Unimplemented CK_FunctionToPointerDecay DeclRefExpr for " + string(declRef->getStmtClassName()));

				}
				else Throw("Unimplemented CK_FunctionToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()));

				break;
				case CK_LValueToRValue://const int h = 5; int k = h;

				if (isa<DeclRefExpr>(icast->getSubExpr())) {
					const DeclRefExpr *declRef = cast<const DeclRefExpr>(icast->getSubExpr());
					map<string, int>::iterator it = statics.find(declRef->getDecl()->getName());

					if (it != statics.end())
					{
						map<uint32_t, string>::iterator dsit = DefaultStaticValues.find(it->second);
						if (dsit != DefaultStaticValues.end())
						{
							char *endp;
							int32_t value = strtol(dsit->second.c_str(), &endp, 10);

							if (endp == dsit->second.c_str() || *endp != 0)
								Throw("Unable to convert a const default static value to value", rewriter, declRef->getExprLoc());

							if (declRef->getDecl()->getType()->isFloatingType())
								InitializationStack.push({ value, FBWT_FLOAT });
							else
								InitializationStack.push({ value, FBWT_INT });
						}
						else Throw("Const value index " + string(declRef->getDecl()->getName()) + " was not found", rewriter, declRef->getExprLoc());
					}
					else Throw("Const value " + string(declRef->getDecl()->getName()) + " was not found", rewriter, declRef->getExprLoc());
				}
				else Throw("Unimplemented CK_LValueToRValue for " + string(icast->getSubExpr()->getStmtClassName()));

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
				case clang::CK_FloatingToIntegral:
				{
					if (isa<FloatingLiteral>(icast->getSubExpr())) {
						const FloatingLiteral *literal = cast<const FloatingLiteral>(icast->getSubExpr());
						float fltliteral;
						if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle)
							fltliteral = literal->getValue().convertToFloat();
						else
							fltliteral = (float)literal->getValue().convertToDouble();
						InitializationStack.push({ (int32_t)fltliteral, FBWT_INT });
					}
					else
					{
						ParseLiteral(icast->getSubExpr(), false, true);
						InitializationStack.push({ (int32_t)IntToFloat(IS_Pop().bytes), FBWT_INT });
					}
					break;
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
			Throw("DeclRefExpr", rewriter, e->getExprLoc());
			//int k;
			//int x = &k;
			return true;
		}
		else if (isa<ArraySubscriptExpr>(e)) {
			Throw("parseArraySubscriptExpr", rewriter, e->getExprLoc());
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
				else Throw("UO_Minus not caught", rewriter, op->getOperatorLoc());
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
					Throw("unimplmented UO_Not", rewriter, op->getOperatorLoc());
				}
				return true;

			}
			else if (op->getOpcode() == UO_AddrOf) {
				if (isa<ArraySubscriptExpr>(subE)) {
					//parseArraySubscriptExpr(subE, true);
					Throw("parseArraySubscriptExpr", rewriter, subE->getExprLoc());
				}
				else if (isa<DeclRefExpr>(subE)) {
					Throw("DeclRefExpr", rewriter, subE->getExprLoc());
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


			IS_Exch();
			bool islvaluefloat = InitializationStack.top().type == FBWT_FLOAT;
			IS_Exch();


			if (bOp->getLHS()->getType()->isFloatingType() || islvaluefloat) {
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
					Throw("flt operator " + to_string(bOp->getOpcode()) + " is unimplemented for a static define", rewriter, bOp->getOperatorLoc());
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
					Throw("operator " + to_string(bOp->getOpcode()) + " is unimplemented for a static define", rewriter, bOp->getOperatorLoc());
				}
			}

		}
		else if (isa<ImplicitValueInitExpr>(e))
		{
			const ImplicitValueInitExpr *ivie = cast<const ImplicitValueInitExpr>(e);

			const Type* type = ivie->getType().getTypePtr();
			uint32_t size = getSizeFromBytes(getSizeOfType(type));
			InitializationStack.push({ 0, FBWT_ARRAY });

			for (uint32_t i = 0; i < size; i++)
				DefaultStaticValues.insert({ oldStaticInc++, "0" });

		}
		else if (isa<InitListExpr>(e))//kill on myself
		{

			const InitListExpr *init = cast<const InitListExpr>(e);

			const Type* type = init->getType().getTypePtr();
			int32_t size = getSizeOfType(type);

			int32_t itemType = 0;

			//int32_t oldArrayOutSize = ArrayOut.size();
			if (!InitializationStack.empty())
			{
				if (InitializationStack.top().type != FBWT_INIT_LIST)
					InitializationStack.push({ 0, FBWT_INIT_LIST });
			}
			else
				InitializationStack.push({ 0, FBWT_INIT_LIST });

			if (isa<ConstantArrayType>(type))//will fuck up with array of array of array
				type = type->getArrayElementTypeNoTypeQual();
			else if (type->isStructureType())
			{
				const RecordType *record = type->getAsStructureType();
				type = record;

				if (RecordDecl *rd = record->getDecl()) {

					for (const auto *CS : rd->fields()) {
						const QualType qtype = CS->getType();

						const Type* type = qtype.getTypePtr();

						if (isa<ConstantArrayType>(type))
							type = type->getArrayElementTypeNoTypeQual();

						#if STATIC_DEBUG == 1
						cout << "\trecord type size: " << getSizeOfQualType(&qtype) << " is char: " << type->isCharType() << endl;
						#endif
						//size += max(temp, 4);
					}
					//cout << "struct: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';
				}

			}

			#if STATIC_DEBUG == 1
			cout << "init size: " << size << "\tType size: " << getSizeFromBytes(size) << "\tClass: " << type->getTypeClassName() << "\tis char: " << type->isCharType() << endl;
			#endif

			vector<uint8_t> initdata;
			for (unsigned int i = 0; i < init->getNumInits(); i++) {
				const Expr* expr = init->getInit(i);

				#if STATIC_DEBUG == 1
				if (isa<BuiltinType>(expr->getType().getTypePtr()))
				{
					const BuiltinType *bt = cast<const BuiltinType>(expr->getType().getTypePtr());
					cout << "BT:" << bt->getKind() << endl;
					if (init->getType().getTypePtr()->isStructureType())
						cout << "\tarr size:" << getSizeOfType(init->getType().getTypePtr()->getAsStructureType()->getDecl()->field_begin()->getType().getTypePtr()) << endl;
					else
						cout << "\tarr size:" << getSizeOfType(init->getType().getTypePtr()) << endl;


				}
				#endif

				ParseLiteral(expr);

				if (InitializationStack.top().type != FBWT_ARRAY)
				{

					#if STATIC_DEBUG == 1
					cout << "istype: " << InitializationStack.top().type << endl;
					#endif

					const Type* type = init->getType().getTypePtr();
					const Type* exprtype = expr->getType().getTypePtr();
					size_t size = 0;

					if (type->isStructureType())
					{
						if (RecordDecl *rd = type->getAsStructureType()->getDecl()) {

							int j = 0;
							for (const auto *CS : rd->fields())
							{
								if (j++ == i)
								{
									type = CS->getType().getTypePtr();
									if (isa<ConstantArrayType>(type))
										type = type->getArrayElementTypeNoTypeQual();
									break;
								}

							}
						}

					}

					size = getSizeOfType(type);
					#if STATIC_DEBUG == 1
					cout << "size: " << size << endl;
					#endif

					if (exprtype->isCharType())
					{
						if (size == 1)
						{
							DefaultStaticValues.insert({ oldStaticInc++, to_string((IS_Pop().bytes % 256) << 24) });
							size--;
						}
						else
						{
							#if STATIC_DEBUG == 1
							cout << "pushing 1\n";
							#endif
							initdata.push_back(IS_Pop().bytes % 256);
						}
					}
					else if (exprtype->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || exprtype->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
					{
						if (size == 2)
						{
							DefaultStaticValues.insert({ oldStaticInc++, to_string((IS_Pop().bytes % 65536) << 16) });
							size -= 2;
						}
						else
						{
							#if STATIC_DEBUG == 1
							cout << "pushing 2\n";
							#endif
							initdata.resize(initdata.size() + 2);
							int16_t data = IS_Pop().bytes % 65536;
							memcpy(initdata.data() + initdata.size() - 2, &data, 2);
						}
					}
					else if (InitializationStack.top().type != FBWT_INIT_LIST)
					{
						if (size == 4)
						{
							DefaultStaticValues.insert({ oldStaticInc++, to_string(IS_Pop().bytes) });
							size -= 4;
						}
						else
						{
							#if STATIC_DEBUG == 1
							cout << "pushing 4\n";
							#endif
							initdata.resize(initdata.size() + 4);
							int32_t data = IS_Pop().bytes;
							memcpy(initdata.data() + initdata.size() - 4, &data, 4);
						}
					}

					//add padding at end of init list expression
					if (i == init->getNumInits() - 1 && !isa<InitListExpr>(expr))
					{
						#if STATIC_DEBUG == 1
						cout << "push size: " << size << endl;
						cout << "pushing 0 ints times " << (size - initdata.size()) / 4 << endl;
						#endif
						while (initdata.size() < size)
						{
							initdata.push_back(0);
						}
					}
				}
				//else is array which is already padded and good to go
				else
				{
					IS_Pop();
					if (InitializationStack.top().type != FBWT_INIT_LIST)
						Throw("Stack error on InitListExpr literal");
				}

			}

			//read data into statics
			for (int i = 0; i < initdata.size(); i += 4)
			{
				if (i + 4 > initdata.size())
				{
					int32_t buffer = 0;
					for (int j = 0; j < initdata.size() - i; j++)
						((uint8_t*)&buffer)[j] = initdata[i + j];

					//swapping bytes
					if (type->isCharType())
						buffer = Utils::Bitwise::SwapEndian(buffer);
					else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
						buffer = Utils::Bitwise::Flip2BytesIn4(buffer);

					#if STATIC_DEBUG == 1
					cout << "read b: " << buffer << "\n";
					#endif
					DefaultStaticValues.insert({ oldStaticInc++, to_string(buffer) });
				}
				else
				{
					int32_t value = *(uint32_t*)(initdata.data() + i);

					//swapping bytes
					if (type->isCharType())
						value = Utils::Bitwise::SwapEndian(value);
					else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
						value = Utils::Bitwise::Flip2BytesIn4(value);

					#if STATIC_DEBUG == 1
					cout << "read: " << to_string(value) << "\n";
					#endif
					DefaultStaticValues.insert({ oldStaticInc++, to_string(value) });
				}
			}

			//if (oldArrayOutSize + itemSize < ArrayOut.size())
			//	Throw("ArrayOut Overflow!!!");
			//
			//if (oldArrayOutSize + itemSize > ArrayOut.size())
			//{
			//	int count = ArrayOut.size() - (oldArrayOutSize + itemSize);
			//
			//	for(int i = 0; i < count; i++)
			//		ArrayOut.push_back(0);
			//
			//}

			if (InitializationStack.empty() || InitializationStack.top().type != FBWT_INIT_LIST)
				Throw("Stack error on InitListExpr literal");
		}
		else if (isa<CharacterLiteral>(e))
		{
			const CharacterLiteral *charliteral = cast<const CharacterLiteral>(e);
			InitializationStack.push({ (int32_t)charliteral->getValue(), FBWT_CHAR });
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

					auto size = getSizeOfType(varDecl->getType().getTypePtr());
					//auto size = context->getTypeInfoDataSizeInChars(varDecl->getType()).first.getQuantity();

					oldStaticInc = staticInc;
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

						if (oldStaticInc > staticInc)//undefined length arrays
							staticInc = oldStaticInc;

						uint32_t sizeb4 = 0;
						if (!InitializationStack.empty())
						{
							sizeb4 = InitializationStack.size();

							switch (InitializationStack.top().type)
							{
								case FBWT_ARRAY:
								case FBWT_INIT_LIST:

								//if (ArrayOut.size() != 0)
								//{
								//	staticInc += ArrayOut.size() - 1;
								//}
								InitializationStack.pop();
								if (!InitializationStack.empty())
									Warn("InitializationStack not empty after array type" + to_string(InitializationStack.top().type));
								break;
								default://FBWT_INT

								if (varDecl->getType()->isCharType())
									DefaultStaticValues.insert({ oldStaticInc, to_string(Utils::Bitwise::SwapEndian(IS_Pop().bytes % 256)) });
								else if (varDecl->getType()->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || varDecl->getType()->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
									DefaultStaticValues.insert({ oldStaticInc, to_string(Utils::Bitwise::Flip2BytesIn4(IS_Pop().bytes % 65536)) });
								else
									DefaultStaticValues.insert({ oldStaticInc, to_string(IS_Pop().bytes) });


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

					if (oldStaticInc > staticInc)
						Warn("Static Overflow Old:" + to_string(oldStaticInc) + " New:" + to_string(staticInc));


				}
				else
					Throw("Var " + dumpName(cast<NamedDecl>(D)) + " is already defined", rewriter, D->getLocStart());
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

	//enum AOWT_Types : uint8_t
	//{
	//	AOWT_4BYTE,
	//	AOWT_2BYTE,
	//	AOWT_1BYTE,
	//	AOWT_STR_LITERAL
	//};
	//typedef struct {
	//	AOWT_Types type;
	//	vector<int32_t> out;
	//} AOWT;
	//vector<int32_t> ArrayOut;

	uint32_t oldStaticInc = 0;
	map<uint32_t, string> DefaultStaticValues;//index, value

	enum FBWT_Types : uint8_t
	{
		FBWT_INT,
		FBWT_CHAR,
		FBWT_FLOAT,
		FBWT_ARRAY,
		FBWT_INIT_LIST
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
	void IS_Clear()
	{
		while (!InitializationStack.empty())
		{
			InitializationStack.pop();
		}
	}
	void IS_Exch()
	{
		if (InitializationStack.size() >= 2)
		{
			FBWT val1 = IS_Pop();
			FBWT val2 = IS_Pop();
			InitializationStack.push(val1);
			InitializationStack.push(val2);
		}
		else Throw("InitializationStack not big enough to exch");
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
				localCounts.insert(make_pair(currentFunction, LocalVariables.getCurrentSize() - currentFunction->getNumParams() - (isa<CXXMethodDecl>(currentFunction) ? 1 : 0)));
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
		{
			localCounts.insert(make_pair(currentFunction, LocalVariables.getCurrentSize()));
		}
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
		for (map<uint32_t, string>::iterator iterator = GlobalsVisitor.DefaultStaticValues.begin(); iterator != GlobalsVisitor.DefaultStaticValues.end(); iterator++)
			header << "SetDefaultStatic " << iterator->first << " " << iterator->second << "\r\n";

		//this is not to be used by the high level compiler statics will still be indexed by integers for performance
		for (map<string, int>::iterator iterator = statics.begin(); iterator != statics.end(); iterator++)
			header << "SetStaticName " << iterator->second << " " << iterator->first << "\r\n";

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

			string outstr = Visitor.out.str();
			for (uint32_t i = 0; i < functions.size(); i++)
			{
				if (functions[i].isused)
					fwrite(outstr.c_str() + functions[i].FuncDataPos, 1, i == functions.size() - 1 ? outstr.size() - functions[i].FuncDataPos : functions[i + 1].FuncDataPos - functions[i].FuncDataPos, file);
			}

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
