#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <map>
#include <cmath>
#include "Utils.h"
#include "FunctionOpcode.h"

#pragma region Global_Defines
#undef ReplaceText//(commdlg.h) fix for the retard at microsoft who thought having a define as ReplaceText was a good idea
#define MultValue(pTypePtr) (pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4)
#define STATIC_PADDING_DEBUG 0
#define AddInstruction(opName, ...) CurrentFunction->addOp##opName(__VA_ARGS__)
#ifdef _DEBUG
#define AddInstructionComment(opName, comment, ...) {CurrentFunction->addOp##opName(__VA_ARGS__); CurrentFunction->pushComment(comment);}
#else
#define AddInstructionComment(opName, comment, ...) CurrentFunction->addOp##opName(__VA_ARGS__)
#endif
#define AddFloatingOpCheck(isFlt, opEnum, opEnumFlt) CurrentFunction->AddSimpleOp((isFlt) ? opEnumFlt : opEnum)
#define AddInstructionCondition(cond, opNameTrue, opNameFalse, ...) {if (cond) CurrentFunction->addOp##opNameTrue(__VA_ARGS__); else CurrentFunction->addOp##opNameFalse(__VA_ARGS__);}
#define AddInstructionConditionally(cond, opName, ...) {if (cond) CurrentFunction->addOp##opName(__VA_ARGS__);}
#pragma endregion

using namespace Utils;
using namespace Utils::System;
using namespace Utils::DataConversion;
using namespace Utils::Hashing;
using namespace clang;
using namespace clang::tooling;
using namespace std;

#pragma region Global_Misc_Clang_Decls
static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");
static Rewriter rewriter;
#pragma endregion

#pragma region Global_Function_Data_Decls
struct FData
{
	uint32_t hash;
	string name;
	bool isused;
	streampos FuncDataPos;
};
vector<FData> functions;

vector<FunctionData*> functionsNew;
FunctionData* CurrentFunction;
FunctionData Entryfunction("@EntryPoint", 0);
vector<FunctionData*> staticReferences;
struct InlineData { uint32_t hash; string name; };
vector<InlineData> InlineItems;
#pragma endregion

#pragma region Global_Var_and_Scope_Decls
map<string, int> globals;
map<string, int> statics;
map<const FunctionDecl*, int> localCounts;
static int globalInc = 0;
static uint32_t staticInc = 0;

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
#pragma endregion

//Constexpr in visual studio is not fully implemented. When they are put in the hashing namespace in utils it errors.
#pragma region Constexpr_Helpers
#pragma warning( disable : 4307 )
constexpr char ToLowerConst(const char c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; }
constexpr uint32_t sumSHL(uint32_t h, uint32_t shift) { return h + (h << shift); }
constexpr uint32_t sumSHR(uint32_t h, uint32_t shift) { return h + (h >> shift); }
constexpr uint32_t xorSHR(uint32_t h, uint32_t shift) { return h ^ (h >> shift); }
constexpr uint32_t hashFinishImpl(uint32_t h) { return sumSHL(xorSHR(sumSHL(h, 3), 11), 15); }
constexpr uint32_t hashStepImpl(uint32_t h, uint32_t c) { return xorSHR(sumSHL(h + c, 10), 6); }
constexpr uint32_t casedHashImpl(const char * cstr, uint32_t h) { return (*cstr != 0) ? casedHashImpl(cstr + 1, hashStepImpl(h, *cstr)) : hashFinishImpl(h); }
constexpr uint32_t hashImpl(const char * cstr, uint32_t h) { return (*cstr != 0) ? hashImpl(cstr + 1, hashStepImpl(h, ToLowerConst(*cstr))) : hashFinishImpl(h); }
#pragma endregion

#pragma region Global_Constexpr_Functions
constexpr uint32_t JoaatCasedConst(const char * cstr) { return casedHashImpl(cstr, 0); }
constexpr uint32_t JoaatConst(const char * cstr) { return hashImpl(cstr, 0); }
#pragma endregion

#pragma region Global_Inline_Function_Functions
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
#pragma endregion

#pragma region Global_Size_Functions
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
uint32_t getSizeFromBytes(uint64_t bytes) {
	uint32_t size = (bytes / 4) + ((bytes % 4) ? 1 : 0);
	return size;
}
uint32_t getLiteralSizeOfType(const Type* type) {

	if (isa<ConstantArrayType>(type)) {
		const ConstantArrayType *arrType = cast<const ConstantArrayType>(type);
		return getSizeOfType(type->getArrayElementTypeNoTypeQual()) * (arrType->getSize()).getSExtValue();
	}
	//else if (type->isRecordType() && type->getAsCXXRecordDecl()) {
	//	CXXRecordDecl *recordDecl = type->getAsCXXRecordDecl();
	//	return getSizeOfCXXDecl(recordDecl, true, false);
	//}
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
	//else if (type->isRecordType() && type->getAsCXXRecordDecl()) {
	//	CXXRecordDecl *recordDecl = type->getAsCXXRecordDecl();
	//	return getSizeOfCXXDecl(recordDecl, true, false);
	//}
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
	else if (type->isIntegerType() || type->isBooleanType() || type->isRealFloatingType() || type->isPointerType())
		return 4;
	else if (type->isVoidType())
		return 0;
	else if (type->isAnyComplexType())
		return 8;

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
inline bool doesInt64FitIntoInt32(int64_t value)
{
	return (int32_t)value != value;
}
#pragma endregion

#pragma region Global_CXX_Functions
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
uint32_t getNumVirtMethods(const CXXRecordDecl *classDecl) {
	int numVirt = 0;
	for (CXXMethodDecl *VFI : classDecl->methods())
		if (VFI->isVirtual())
			numVirt++;

	return numVirt;
}
#pragma endregion


#pragma region Global_Opcode_Functions
#pragma region Opcodes_Push
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
double extractAPFloat(llvm::APFloat value)
{
	return &value.getSemantics() == &llvm::APFloat::IEEEsingle ? (double)value.convertToFloat() : value.convertToDouble();
}
#pragma endregion
#pragma region Opcodes_Math
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
string div(int value)
{
	return iPush(value) + "\r\nDiv";
}
#pragma endregion
#pragma region Opcodes_Var
string frameSet(int index) {
	if ((index & 0xFF) == index) {
		return "SetFrame1 " + to_string(index);
	}
	else if ((index & 0xFFFF) == index) {
		return "SetFrame2 " + to_string(index);
	}
	else
		Throw("SetFrame Index \"" + to_string(index) + "\" is out of range 0 - 65535");
	return "null";
}
string frameGet(int index) {
	if ((index & 0xFF) == index) {
		return "GetFrame1 " + to_string(index);
	}
	else if ((index & 0xFFFF) == index) {
		return "GetFrame2 " + to_string(index);
	}
	else
		Throw("GetFrame Index \"" + to_string(index) + "\" is out of range 0 - 65535");
	return "null";
}
string pFrame(const int index) {
	if ((index & 0xFF) == index)
		return "GetFrameP1 " + to_string(index);
	else if ((index & 0xFFFF) == index)
		return "GetFrameP2 " + to_string(index);
	else
		Throw("GetFrameP Index \"" + to_string(index) + "\" is out of range 0 - 65535");
	return "null";
}
string setGlobal(int index) {
	if ((index & 0xFFFF) == index)
		return "SetGlobal2 " + to_string(index);
	else if ((index & 0xFFFFFF) == index)
		return "SetGlobal3 " + to_string(index);
	else
		Throw("SetGlobal Index \"" + to_string(index) + "\" is out of range 0 - 16777215");
	return "null";
}
string getGlobal(int index) {
	if ((index & 0xFFFF) == index)
		return "GetGlobal2 " + to_string(index);
	else if ((index & 0xFFFFFF) == index)
		return "GetGlobal3 " + to_string(index);
	else
		Throw("GetGlobal Index \"" + to_string(index) + "\" is out of range 0 - 16777215");
	return "null";
}
string getGlobalp(const int index) {
	if ((index & 0xFFFF) == index)
		return "GetGlobalP2 " + to_string(index);
	else if ((index & 0xFFFFFF) == index)
		return "GetGlobalP3 " + to_string(index);
	else
		Throw("GetGlobalP Index \"" + to_string(index) + "\" is out of range 0 - 16777215");
	return "null";
}
string setStatic(int index) {
	if ((index & 0xFF) == index)
		return "SetStatic1 " + to_string(index);
	else if ((index & 0xFFFF) == index)
		return "SetStatic2 " + to_string(index);
	else
		Throw("SetStatic Index \"" + to_string(index) + "\" is out of range 0 - 65535");
	return "null";
}
string getStatic(int index) {
	if ((index & 0xFF) == index)
		return "GetStatic1 " + to_string(index);
	else if ((index & 0xFFFF) == index)
		return "GetStatic2 " + to_string(index);
	else
		Throw("GetStatic Index \"" + to_string(index) + "\" is out of range 0 - 65535");
	return "null";
}
string getStaticp(const int index) {
	if ((index & 0xFF) == index)
		return "GetStaticP1 " + to_string(index);
	else if ((index & 0xFFFF) == index)
		return "GetStaticP2 " + to_string(index);
	else
		Throw("GetStaticP Index \"" + to_string(index) + "\" is out of range 0 - 65535");
	return "null";
}
#pragma endregion
#pragma region Opcodes_Immediate
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
#pragma endregion
#pragma endregion


class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
public:
	MyASTVisitor(Rewriter &R, ASTContext *context, string filename) : TheRewriter(R), context(context), outfile(filename) {}

	#pragma region Misc_Functions
	void ComplexToBoolean(bool floating)
	{
		LocalVariables.addLevel();
		int index = LocalVariables.addDecl("imagPart", 1);
		if (floating) {
			out << frameSet(index) << "\r\nPushF_0\r\nfCmpNe\r\n" << frameGet(index) << "\r\nPushF_0\r\nfCmpNe\r\nOr\r\n";
			AddInstruction(SetFrame, index);
			AddInstruction(PushFloat, 0.0f);
			AddInstruction(FCmpEq);
			AddInstruction(GetFrame, index);
			AddInstruction(PushFloat, 0.0f);
			AddInstruction(FCmpEq);
			AddInstruction(Or);
		}
		else
		{
			out << frameSet(index) << "\r\nPush_0\r\nCmpNe\r\n" << frameGet(index) << "\r\nPush_0\r\nCmpNe\r\nOr\r\n";
			AddInstruction(SetFrame, index);
			AddInstruction(PushInt, 0);
			AddInstruction(CmpEq);
			AddInstruction(GetFrame, index);
			AddInstruction(PushInt, 0);
			AddInstruction(CmpEq);
			AddInstruction(Or);
		}
		LocalVariables.removeLevel();
	}
	#pragma endregion

	#pragma region Name_Resolution
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
	#pragma endregion

	#pragma region Parsing
	void parseJumpFalseCondition(Expr *condition, string location, bool invert = false)
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
							out << "JumpEQ @" << location << endl;
							AddInstruction(JumpEQ, location);
							return;
							case BO_NE:
							out << "JumpNE @" << location << endl;
							AddInstruction(JumpNE, location);
							return;
							case BO_GT:
							out << "JumpGT @" << location << endl;
							AddInstruction(JumpGT, location);
							return;
							case BO_GE:
							out << "JumpGE @" << location << endl;
							AddInstruction(JumpGE, location);
							return;
							case BO_LT:
							out << "JumpLT @" << location << endl;
							AddInstruction(JumpLT, location);
							return;
							case BO_LE:
							out << "JumpLE @" << location << endl;
							AddInstruction(JumpLE, location);
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
							out << "JumpNE @" << location << endl;
							AddInstruction(JumpNE, location);
							return;
							case BO_NE:
							out << "JumpEQ @" << location << endl;
							AddInstruction(JumpEQ, location);
							return;
							case BO_GT:
							out << "JumpLE @" << location << endl;
							AddInstruction(JumpLE, location);
							return;
							case BO_GE:
							out << "JumpLT @" << location << endl;
							AddInstruction(JumpLT, location);
							return;
							case BO_LT:
							out << "JumpGE @" << location << endl;
							AddInstruction(JumpGE, location);
							return;
							case BO_LE:
							out << "JumpGT @" << location << endl;
							AddInstruction(JumpGT, location);
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
			out << "JumpFalse @" << location << endl;
			AddInstruction(JumpTrue, location);
		}
		else
		{
			out << "JumpFalse @" << location << endl;
			AddInstruction(JumpFalse, location);
		}


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
					Throw("Unhandled Integral Cast", rewriter, castExpr->getSourceRange());
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
						Throw("Unimplemented Cast", rewriter, castExpr->getSourceRange());
					}

				}
				else {
					Throw("Unimplemented Cast", rewriter, castExpr->getSourceRange());
				}
			}
			break;
			default:
			Throw("Unimplemented Cast", rewriter, castExpr->getSourceRange());
		}
		return "";
	}
	#pragma endregion

	#pragma region Decl_Handling
	//handleParamVarDecl
	void printDeclWithKey(string key, bool isAddr, bool isLtoRValue, bool isAssign, const DeclRefExpr* declref) {
		int index = -1;
		const Type* type = declref->getType().getTypePtr();
		size_t size = getSizeOfType(type);
		bool isStackCpy = size > 4 && isLtoRValue && !isAddr;//if greater then 4 bytes then a to stack is in order

		if (isStackCpy) {
			out << iPush(getSizeFromBytes(size)) << "//Type Size" << endl;
			AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
			isAddr = true;
		}

		if (LocalVariables.find(key, &index))
		{
			if (isLtoRValue && !isAddr)
			{

				out << frameGet(index) << " //(pdecl)" << key << endl;
				AddInstructionComment(GetFrame, "(pdecl)" + key,index);
				if (size == 1)//char
				{
					out << "PushB 24\r\nCallNative shift_right 2 1//char type\r\n";
					AddInstruction(PushInt, 24);
					AddInstructionComment(ShiftRight, "char type");
				}
				else if (size == 2)//short
				{
					out << "PushB 16\r\nCallNative shift_right 2 1//short type\r\n";
					AddInstruction(PushInt, 16);
					AddInstructionComment(ShiftRight, "short type");
				}
			}
			else if (isAddr)
			{
				out << pFrame(index) << " //(pdecl)&" << key << endl;
				AddInstructionComment(GetFrameP, "(pdecl)&" + key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				if (size == 1)//char
				{
					out << "PushS 256\r\nMod\r\nPushB 24\r\nCallNative shift_left 2 1//char type\r\n";
					AddInstruction(PushInt, 255);
					AddInstruction(And);
					AddInstruction(PushInt, 24);
					AddInstructionComment(ShiftLeft, "char type");

				}
				else if (size == 2)//short
				{
					out << "Pushi24 65536\r\nMod\r\nPushB 16\r\nCallNative shift_left 2 1//short type\r\n";
					AddInstruction(PushInt, 65536);
					AddInstruction(Mod);
					AddInstruction(PushInt, 16);
					AddInstructionComment(ShiftLeft, "short type");
				}
				if (size > 4)//fromStack
				{
					int bSize = getSizeFromBytes(size);
					out << iPush(bSize) << " //Type Size\r\n";
					out << pFrame(index) << " //(pdecl)&" << key << endl;
					out << "FromStack\r\n";
					AddInstructionComment(PushInt, "Type Size", bSize);
					AddInstructionComment(GetFrameP, "(pdecl)&" + key, index);
					AddInstruction(FromStack);
				}
				else
				{
					out << frameSet(index) << " //(pdecl)" << key << endl;
					AddInstructionComment(SetFrame, "(pdecl)" + key, index);
				}
				
			}
			else
			{
				out << "//Var " << key << " was dropped because there were no vaild paths.\r\n";
			}
		}
		else if (globals.find(key) != globals.end()) {
			index = globals[key];
			if (isLtoRValue && !isAddr)
			{
				out << getGlobal(index) << " //Global_" << key << endl;
				AddInstructionComment(GetGlobal, "Global_" + key, index);
				if (size == 1)//char
				{
					out << "PushB 24\r\nCallNative shift_right 2 1//char type\r\n";
					AddInstruction(PushInt, 24);
					AddInstructionComment(ShiftRight, "char type");
				}
				else if (size == 2)//short
				{
					out << "PushB 16\r\nCallNative shift_right 2 1//short type\r\n";
					AddInstruction(PushInt, 16);
					AddInstructionComment(ShiftRight, "short type");
				}
			}
			else if (isAddr)
			{
				out << getGlobalp(index) << "  //Global_" << key << endl;
				AddInstructionComment(GetGlobalP,"Global_" + key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				if (size == 1)//char
				{
					out << "PushS 256\r\nMod\r\nPushB 24\r\nCallNative shift_left 2 1//char type\r\n";
					AddInstruction(PushInt, 255);
					AddInstruction(And);
					AddInstruction(PushInt, 24);
					AddInstructionComment(ShiftLeft, "char type");

				}
				else if (size == 2)//short
				{
					out << "Pushi24 65536\r\nMod\r\nPushB 16\r\nCallNative shift_left 2 1//short type\r\n";
					AddInstruction(PushInt, 65536);
					AddInstruction(Mod);
					AddInstruction(PushInt, 16);
					AddInstructionComment(ShiftLeft, "short type");
				}
				if(size > 4)//fromStack
				{
					int bSize = getSizeFromBytes(size);
					out << iPush(bSize) << " //Type Size\r\n";
					out << getGlobalp(index) << " //&Global_" << key << endl;
					out << "FromStack\r\n";
					AddInstructionComment(PushInt, "Type Size", bSize);
					AddInstructionComment(GetGlobalP, "&Global_" + key, index);
					AddInstruction(FromStack);
				}
				else
				{
					out << setGlobal(index) << " //" << key << endl;
					AddInstructionComment(SetGlobal, key, index);
				}
			}
			else
			{
				out << "//Global Var " << key << " was dropped because there were no vaild paths.\r\n";
			}
		}
		else if (statics.find(key) != statics.end()) {
			index = statics[key];
			if (isLtoRValue && !isAddr)
			{
				out << getStatic(index) << " //" << key << endl;
				AddInstructionComment(GetStatic, key, index);
				if (size == 1)//char
				{
					out << "PushB 24\r\nCallNative shift_right 2 1//char type\r\n";
					AddInstruction(PushInt, 24);
					AddInstructionComment(ShiftRight, "char type");
				}
				else if (size == 2)//short
				{
					out << "PushB 16\r\nCallNative shift_right 2 1//short type\r\n";
					AddInstruction(PushInt, 16);
					AddInstructionComment(ShiftRight, "short type");
				}
			}
			else if (isAddr)
			{
				out << getStaticp(index) << " //" << key << endl;
				AddInstructionComment(GetStaticP, key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				if (size == 1)//char
				{
					out << "PushS 256\r\nMod\r\nPushB 24\r\nCallNative shift_left 2 1//char type\r\n";
					AddInstruction(PushInt, 255);
					AddInstruction(And);
					AddInstruction(PushInt, 24);
					AddInstructionComment(ShiftLeft, "char type");

				}
				else if (size == 2)//short
				{
					out << "Pushi24 65536\r\nMod\r\nPushB 16\r\nCallNative shift_left 2 1//short type\r\n";
					AddInstruction(PushInt, 65536);
					AddInstruction(Mod);
					AddInstruction(PushInt, 16);
					AddInstructionComment(ShiftLeft, "short type");
				}

				if(size > 4)//fromStack
				{
					int bSize = getSizeFromBytes(size);
					out << iPush(bSize) << " //Type Size\r\n";
					out << getStaticp(index) << " //&" << key << endl;
					out << "FromStack\r\n";
					AddInstructionComment(PushInt, "Type Size", bSize);
					AddInstructionComment(GetStaticP, "&" + key, index);
					AddInstruction(FromStack);
				}
				else
				{
					out << setStatic(index) << "  //" << key << endl;
					AddInstructionComment(SetStatic, key, index);
				}
			}
			else
			{
				out << "//Static Var " << key << " was dropped because there were no vaild paths.\r\n";
			}
		}
		else
		{
			string name = "@" + key;
			uint32_t hash = Utils::Hashing::JoaatCased((char*)name.c_str());
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
			for (uint32_t j = 0; j < functionsNew.size(); j++)
			{
				if (functionsNew[j]->Hash() == hash)
				{
					if (functionsNew[j]->Name() == name)
					{
						CurrentFunction->addUsedFunc(functionsNew[j]);
						break;
					}
				}
			}

			if (i >= functions.size())
				Throw("Function pointer \"" + key + "\" not found");

			out << "//DeclRefExpr, nothing else, so func it" << endl;
			out << "Push GetLoc(\"" << key << "\")" << endl;
			AddInstructionComment(LabelLoc, "DeclRefExpr, nothing else, so func it", key);
			//out << key << endl;
			//out << "DeclRefExpr not implemented" << endl;
		}

		if (isStackCpy) {//if greater then 4 bytes then a to stack is in order
			out << "ToStack" << endl;
			AddInstruction(ToStack);

		}

	}
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
						AddInstructionComment(GetFrameP, var->getNameAsString(), curIndex);
						parseExpression(initializer);
					}
					else
					{
						parseExpression(initializer);
						out << frameSet(curIndex) << "  //(parm)" << var->getName().str() << endl;
						AddInstructionComment(SetFrame, "(parm)" + var->getName().str(), curIndex);
					}
				}
				LocalVariables.addDecl(var->getName().str(), actsize);
			}
		}
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
						//if (isa<CXXConstructExpr>(initializer)) {
						//	if (isa<ConstantArrayType>(var->getType())) {
						//		const ConstantArrayType *arr = cast<ConstantArrayType>(var->getType());
						//		static int vTableInitInc = 0;
						//
						//		out << "Push 0" << endl;
						//		out << ":vTableConditional_" << vTableInitInc << endl;
						//		//for(int i=0; i<arr->getSize().getSExtValue(); i++) {
						//		out << "dup //index" << endl;
						//		out << "Push " << arr->getSize().getZExtValue() << endl;
						//		out << "JumpGE @vTableEnd_" << vTableInitInc << endl;
						//
						//		out << "dup #index" << endl;
						//		out << pFrame(curIndex) << " //" << var->getNameAsString() << endl;
						//		out << "ArrayGetP " << getSizeFromBytes(getSizeOfCXXDecl(arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), true, true)) << "//index Array" << endl;
						//		parseExpression(initializer, true, false, true, var);
						//		out << "Add1 1" << endl;
						//		out << "Jump @vTableConditional_" << vTableInitInc << endl;
						//		out << ":vTableEnd_" << vTableInitInc << endl << endl;
						//		//}
						//		vTableInitInc++;
						//		return true;
						//	}
						//	out << pFrame(curIndex) << " //" << var->getNameAsString() << endl;
						//	parseExpression(initializer, true, false, true, var);
						//	return true;
						//}

						parseExpression(initializer, false, true);
						if (size > 4) {
							out << iPush(getSizeFromBytes(size)) << " //Type Size" << endl;
							out << pFrame(curIndex) << " //&" << var->getNameAsString() << endl;
							out << "FromStack" << endl;
							AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
							AddInstructionComment(GetFrameP, "&" + var->getNameAsString(), curIndex);
							AddInstruction(FromStack);
						}
						else {
							out << frameSet(curIndex) << "  //" << var->getName().str() << endl;
							AddInstructionComment(SetFrame, var->getName().str(), curIndex);
						}
					}
					LocalVariables.addDecl(var->getName().str(), getSizeFromBytes(size));
				}

			}
		}
		return true;
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
	#pragma endregion

	#pragma region Parse/Visit_Functions
	bool checkIntrinsic(const CallExpr *call) {
		const FunctionDecl* callee = call->getDirectCallee();

		if (callee == NULL || !callee->hasAttr<IntrinsicFuncAttr>())
			return false;

		if (callee->getStorageClass() != SC_Extern)
			Throw("Intrinsic functions must be declared with the 'extern' keyword", rewriter, callee->getLocation());

		string funcName = dumpName(cast<NamedDecl>(callee));

		const Expr * const*argArray = call->getArgs();
		int argCount = call->getNumArgs();

		#define ChkHashCol(str) if(strcmp(funcName.c_str(), str) != 0) goto _IntrinsicNotFound;

		switch (JoaatCased(const_cast<char*>(funcName.c_str())))
		{
			case JoaatCasedConst("strcpy"):
			{
				ChkHashCol("strcpy");
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
							AddInstruction(StrCopy, iValue);
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
							AddInstruction(StrAdd, iValue);
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
							AddInstruction(StrAddI, iValue);
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
							AddInstruction(ItoS, iValue);
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
					AddInstruction(Drop);
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
							{
								out << "Drop\r\n";
								AddInstruction(Drop);
							}
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
				if (argCount >= 1 && callee->getReturnType()->isVoidType())
				{
					if (argCount > 1)
						for (int i = 1; i < argCount; i++)
							parseExpression(argArray[i], false, true);

					parseExpression(argArray[0], false, true);

					Warn("PCall unused returns must be dropped handled by user!", rewriter, call->getSourceRange());
					out << "pCall" << endl;
					AddInstruction(PCall);
					return true;
				}
				Throw("pCall must have signature \"extern __intrinsic void pcall(void* funcAddr, ... args);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("add"):
			{
				ChkHashCol("add");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if (iResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << add(iResult) << "\r\n";
							AddInstruction(AddImm, iResult);
						}
					}
					else
					{
						parseExpression(argArray[0]);
						out << "Add\r\n";
						AddInstruction(Add);
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
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if (iResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << sub(iResult) << "\r\n";
							AddInstruction(AddImm, -iResult);
						}
					}
					else
					{
						parseExpression(argArray[0]);
						out << "Sub\r\n";
						AddInstruction(Sub);
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
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if (iResult == 0)
						{
							out << "Drop\r\nPush_0\r\n";//replace top of stack with 0
							AddInstruction(Drop);
							AddInstruction(PushInt, 0);
						}
						else if (iResult == 1)
						{
							//do nothing here
						}
						else if (iResult == -1)
						{
							//negate
							out << "Neg\r\n";
							AddInstruction(Neg);
						}
						else
						{
							out << mult(iResult) << "\r\n";
							AddInstruction(MultImm, iResult);
						}
					}
					else
					{
						parseExpression(argArray[0]);
						out << "Mult\r\n";
						AddInstruction(Mult);
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
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t iResult = result.getSExtValue();
						if (iResult == 0)
						{
							Warn("Zero division error detected", rewriter, argArray[0]->getSourceRange());//just warn the user of the undefined behaviour
						}
						else if (iResult == 1)
						{
							//do nothing here
						}
						else if (iResult == -1)
						{
							//negate
							out << "Neg\r\n";
							AddInstruction(Neg);
						}
						else
						{
							out << iPush(iResult) << "\r\nDiv\r\n";
							AddInstruction(PushInt, iResult);
							AddInstruction(Div);
						}

					}
					else
					{
						parseExpression(argArray[0]);
						out << "Div\r\n";
						AddInstruction(Div);
					}
					return true;
				}
				Throw("div must have signature \"extern __intrinsic int div(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("neg"):
			{
				ChkHashCol("neg");
				if (argCount == 0 && callee->getReturnType()->isIntegerType())
				{
					out << "Neg\r\n";
					AddInstruction(Neg);
					return true;
				}
				Throw("neg must have signature \"extern __intrinsic int neg();\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("getframe"):
			ChkHashCol("getframe");
			if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
			{
				llvm::APSInt result;
				if (argArray[0]->EvaluateAsInt(result, *context))
				{
					out << frameGet(result.getSExtValue()) << endl;
					AddInstruction(GetFrame, result.getSExtValue());
					return true;
				}
				else
				{
					Throw("Argument got getframe must be a constant integer", rewriter, argArray[0]->getSourceRange());
				}
			}
			else {
				Throw("getframe must have signature \"extern __intrinsic int getframe(const int index);\"", rewriter, callee->getSourceRange());
			}
			break;
			case JoaatCasedConst("getframep"):
			ChkHashCol("getframep");
			if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
			{
				llvm::APSInt result;
				if (argArray[0]->EvaluateAsInt(result, *context))
				{
					out << pFrame(result.getSExtValue()) << endl;
					AddInstruction(GetFrameP, result.getSExtValue());
					return true;
				}
				else
				{
					Throw("Argument got getframep must be a constant integer", rewriter, argArray[0]->getSourceRange());
				}
			}
			else {
				Throw("getframep must have signature \"extern __intrinsic int getframep(int index);\"", rewriter, callee->getSourceRange());
			}
			break;
			case JoaatCasedConst("setframe"):
			ChkHashCol("setframe");

			if (argCount == 1 && callee->getReturnType()->isVoidType())
			{
				llvm::APSInt result;
				if (argArray[0]->EvaluateAsInt(result, *context))
				{
					out << frameSet(result.getSExtValue()) << endl;
					AddInstruction(SetFrame, result.getSExtValue());
					return true;
				}
				else
				{
					Throw("Argument got setframe must be a constant integer", rewriter, argArray[0]->getSourceRange());
				}
			}
			else if (argCount == 2 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
			{
				llvm::APSInt result;
				if (argArray[0]->EvaluateAsInt(result, *context))
				{
					parseExpression(argArray[1], false, true);
					out << frameSet(result.getSExtValue()) << endl;
					AddInstruction(SetFrame, result.getSExtValue());
					return true;
				}
				else
				{
					Throw("Argument got setframe must be a constant integer", rewriter, argArray[0]->getSourceRange());
				}
			}
			else {
				Throw("setframe must have signature \"extern __intrinsic void setframe(int index, ... optinalArgToSetTo);\"", rewriter, callee->getSourceRange());
			}
			break;
			case JoaatCasedConst("getglobal"):
			{
				ChkHashCol("getglobal");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						out << getGlobal(result.getSExtValue()) << endl;
						AddInstruction(GetGlobal, result.getSExtValue());
						return true;
					}
					else
					{
						Throw("Argument got getglobal must be a constant integer", rewriter, argArray[0]->getSourceRange());
					}
				}
				else {
					Throw("getglobal must have signature \"extern __intrinsic int getglobal(const int index);\"", rewriter, callee->getSourceRange());
				}
			}
			break;
			case JoaatCasedConst("setglobal"):
			{
				ChkHashCol("setglobal");
				if (argCount == 1 && callee->getReturnType()->isVoidType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						out << setGlobal(result.getSExtValue()) << endl;
						AddInstruction(SetGlobal, result.getSExtValue());
						return true;
					}
					else
					{
						Throw("Argument got setframe must be a constant integer", rewriter, argArray[0]->getSourceRange());
					}
				}
				else if (argCount == 2 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						parseExpression(argArray[1], false, true);
						out << setGlobal(result.getSExtValue()) << endl;
						AddInstruction(SetGlobal, result.getSExtValue());
						return true;
					}
					else
					{
						Throw("Argument got setglobal must be a constant integer", rewriter, argArray[0]->getSourceRange());
					}
				}
				else {
					Throw("setglobal must have signature \"extern __intrinsic void setglobal(int index, ... optinalArgToSetTo);\"", rewriter, callee->getSourceRange());
				}
			}
			break;
			case JoaatCasedConst("getglobalp"):
			{
				ChkHashCol("getglobalp");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						out << getGlobalp(result.getSExtValue()) << endl;
						AddInstruction(GetGlobalP, result.getSExtValue());
						return true;
					}
					else
					{
						Throw("Argument got getglobal must be a constant integer", rewriter, argArray[0]->getSourceRange());
					}
				}
				else {
					Throw("getglobal must have signature \"extern __intrinsic int getglobal(const int index);\"", rewriter, callee->getSourceRange());
				}
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

					uint32_t loopLblCount = __COUNTER__;

					LocalVariables.addLevel();

					int destIndex = LocalVariables.addDecl("__memcpy-loop-dest", 1);
					int srcIndex = LocalVariables.addDecl("__memcpy-loop-src", 1);
					int sizeIndex = LocalVariables.addDecl("__memcpy-loop-size", 1);

					parseExpression(argArray[0], true, true);//dest
					out << frameSet(destIndex) << endl;
					AddInstruction(SetFrame, destIndex);

					parseExpression(argArray[1], true, true);//src
					out << frameSet(srcIndex) << endl;
					AddInstruction(SetFrame, srcIndex);
					parseExpression(argArray[2], false, true);//size
					out << frameSet(sizeIndex) << endl
						<< iPush(0) << endl//inc ini

						<< ":__memcpy-loop-" << loopLblCount << endl
						<< "Dup\r\n"
						<< frameGet(sizeIndex) << endl
						<< "JumpGE @__memcpy-loopend-" << loopLblCount << endl

						<< frameGet(srcIndex) << endl
						<< "pGet\r\nPushB 24\r\nCallNative shift_left 2 1\r\n"
						<< frameGet(destIndex) << endl
						<< "pGet\r\nPushI24 0xFFFFFF\r\nAnd\r\nOr\r\n"
						<< frameGet(destIndex) << endl
						<< "pSet\r\n"

						<< frameGet(destIndex) << endl
						<< "Add1 1\r\n"
						<< frameSet(destIndex) << endl
						<< frameGet(srcIndex) << endl
						<< "Add1 1\r\n"
						<< frameSet(srcIndex) << endl

						<< "Add1 1\r\n"//inc add
						<< "Jump @__memcpy-loop-" << loopLblCount << endl
						<< ":__memcpy-loopend-" << loopLblCount << endl
						<< "Drop\r\n";

					AddInstruction(SetFrame, sizeIndex);
					AddInstruction(PushInt, 0);
					AddInstruction(Label, "__memcpy-loop-" + to_string(loopLblCount));
					AddInstruction(Dup);
					AddInstruction(JumpGE, "__memcpy-loopend-" + to_string(loopLblCount));

					AddInstruction(GetFrame, srcIndex);
					AddInstruction(PGet);
					AddInstruction(PushInt, 24);
					AddInstruction(ShiftLeft);
					AddInstruction(GetFrame, destIndex);
					AddInstruction(PGet);
					AddInstruction(PushInt, 0xFFFFFF);
					AddInstruction(And);
					AddInstruction(Or);
					AddInstruction(GetFrame, destIndex);
					AddInstruction(PSet);

					AddInstruction(GetFrame, destIndex);
					AddInstruction(AddImm, 1);
					AddInstruction(SetFrame, destIndex);
					AddInstruction(GetFrame, srcIndex);
					AddInstruction(AddImm, 1);
					AddInstruction(SetFrame, srcIndex);

					AddInstruction(AddImm, 1);
					AddInstruction(Jump, "__memcpy-loop-" + to_string(loopLblCount));
					AddInstruction(Label, "__memcpy-loopend-" + to_string(loopLblCount));
					AddInstruction(Drop);
					LocalVariables.removeLevel();

				}
				else
					Throw("memcpy must have signature \"extern __intrinsic void memcpy(void* dst, void* src, int len);\"", rewriter, callee->getSourceRange());
				return true;
			}
			break;
			case JoaatCasedConst("memset"):
			{
				ChkHashCol("memset");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isCharType() && argArray[2]->getType()->isIntegerType())
				{
					uint32_t loopLblCount = __COUNTER__;

					LocalVariables.addLevel();

					int destIndex = LocalVariables.addDecl("__memset-loop-dest", 1);
					int valIndex = LocalVariables.addDecl("__memset-loop-val", 1);
					int sizeIndex = LocalVariables.addDecl("__memset-loop-size", 1);

					parseExpression(argArray[0], true, true);//dest
					out << frameSet(destIndex) << endl;
					AddInstruction(SetFrame, destIndex);

					parseExpression(argArray[1], false, true);//value
					out << "PushB 24\r\nCallNative shift_left 2 1\r\n";
					AddInstruction(PushInt, 24);
					AddInstruction(ShiftLeft);
					out << frameSet(valIndex) << endl;
					AddInstruction(SetFrame, valIndex);
					parseExpression(argArray[2], false, true);//size
					out << frameSet(sizeIndex) << endl
						<< iPush(0) << endl//inc
						<< ":__memset-loop-" << loopLblCount << endl
						<< "Dup" << endl
						<< frameGet(sizeIndex) << endl
						<< "JumpGE @__memset-loopend-" << loopLblCount << endl

						<< frameGet(valIndex) << endl
						<< frameGet(destIndex) << endl
						<< "pGet\r\nPushI24 0xFFFFFF\r\nAnd\r\nOr\r\n"
						<< frameGet(destIndex) << endl
						<< "pSet\r\n"

						<< frameGet(destIndex) << endl
						<< "Add1 1\r\n"
						<< frameSet(destIndex) << endl
						<< "Add1 1\r\n"//add 1 to inc
						<< "Jump @__memset-loop-" << loopLblCount << endl
						<< ":__memset-loopend-" << loopLblCount << endl
						<< "Drop\r\n";

					AddInstruction(SetFrame, sizeIndex);
					AddInstruction(PushInt, 0);
					AddInstruction(Label, "__memset-loop-" + to_string(loopLblCount));
					AddInstruction(Dup);
					AddInstruction(GetFrame, sizeIndex);
					AddInstruction(JumpGE, "__memset-loopend-" + to_string(loopLblCount));

					AddInstruction(GetFrame, valIndex);
					AddInstruction(GetFrame, destIndex);
					AddInstruction(PGet);
					AddInstruction(PushInt, 0xFFFFFF);
					AddInstruction(And);
					AddInstruction(Or);
					AddInstruction(GetFrame, destIndex);
					AddInstruction(PSet);
					AddInstruction(GetFrame, destIndex);
					AddInstruction(AddImm, 1);
					AddInstruction(SetFrame, destIndex);
					AddInstruction(AddImm, 1);
					AddInstruction(Jump, "__memset-loop-" + to_string(loopLblCount));
					AddInstruction(Label, "memset-loopend-" + to_string(loopLblCount));
					AddInstruction(Drop);
					LocalVariables.removeLevel();

				}
				else
					Throw("memset must have signature \"extern __intrinsic void memset(void* dst, byte src, size_t len);\"", rewriter, callee->getSourceRange());
				return true;
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
			case JoaatCasedConst("pushVector3"):
			{
				ChkHashCol("pushVector3");

				if (argCount == 1 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("pushVector3 must have signature \"extern __intrinsic void pushVector3(vector3 vec3Value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			case JoaatCasedConst("popFloat"):;
			{
				ChkHashCol("popFloat");
				if (argCount == 0 && callee->getReturnType()->isRealFloatingType())
				{
					return true;
				}
				Throw("popFloat must have signature \"extern __intrinsic float pushFloat();\"", rewriter, callee->getSourceRange());
				return false;
			}
			case JoaatCasedConst("popInt"):;
			{
				ChkHashCol("popInt");
				if (argCount == 0 && callee->getReturnType()->isIntegerType())
				{
					return true;
				}
				Throw("popInt must have signature \"extern __intrinsic int pushInt();\"", rewriter, callee->getSourceRange());
				return false;
			}
			case JoaatCasedConst("popVector3"):
			{
				ChkHashCol("popVector3");

				if (argCount == 0 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3)
				{
					return true;
				}
				Throw("popVector3 must have signature \"extern __intrinsic vector3 popVector3();\"", rewriter, callee->getSourceRange());
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
								AddInstructionComment(PushInt, "StructSize", size);
							}
							parseExpression(argArray[0], true, true);
							if (size > 1)
							{
								out << "ToStack\r\n";
								AddInstruction(ToStack);
							}
							else
							{
								out << "pGet\r\n";
								AddInstruction(PGet);
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
								AddInstructionComment(PushInt, "StructSize", size);
							}
							parseExpression(argArray[0], true, true);
							if (size > 1)
							{
								out << "FromStack\r\n";
								AddInstruction(FromStack);
							}
							else
							{
								out << "pSet\r\n";
								AddInstruction(PSet);
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
					AddInstruction(Dup);
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
					AddInstruction(FtoV);
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
			break;
			case JoaatCasedConst("vector3Add"):
			{
				ChkHashCol("vector3Add");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					out << "vAdd\r\n";
					AddInstruction(VAdd);
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
					AddInstruction(VSub);
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
					AddInstruction(VMult);
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
					AddInstruction(VDiv);
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
					AddInstruction(VNeg);
					return true;
				}
				Throw("vector3Neg must have signature \"extern __intrinsic vector3 vector3Neg(vector3 vector)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("fadd"):
			{
				ChkHashCol("fadd");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if (argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if (dResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << fPush(dResult) << "\r\nfAdd\r\n";
							AddInstruction(PushFloat, dResult);
							AddInstruction(FAdd);
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fAdd\r\n";
						AddInstruction(FAdd);
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
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if (argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if (dResult == 0)
						{
							//do nothing here
						}
						else
						{
							out << fPush(dResult) << "\r\nfSub\r\n";
							AddInstruction(PushFloat, dResult);
							AddInstruction(FSub);
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fSub\r\n";
						AddInstruction(FSub);
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
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if (argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if (dResult == 0)
						{
							out << "Drop\r\nPushF_0\r\n";
							AddInstruction(Drop);
							AddInstruction(PushFloat, 0);
						}
						else if (dResult == 1)
						{
							//do nothing here
						}
						else if (dResult == -1)
						{
							//negate
							out << "fNeg\r\n";
							AddInstruction(FNeg);
						}
						else
						{
							out << fPush(dResult) << "\r\nfMult\r\n";
							AddInstruction(PushFloat, dResult);
							AddInstruction(FMult);
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fMult\r\n";
						AddInstruction(FMult);
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
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					Expr::EvalResult result;
					if (argArray[0]->EvaluateAsRValue(result, *context) && !result.HasSideEffects && result.Val.isFloat())
					{
						double dResult = &result.Val.getFloat().getSemantics() == &llvm::APFloat::IEEEsingle ? (double)result.Val.getFloat().convertToFloat() : result.Val.getFloat().convertToDouble();
						if (dResult == 0)
						{
							Warn("Zero division error detected", rewriter, argArray[0]->getSourceRange());//just warn the user of the undefined behaviour
						}
						else if (dResult == 1)
						{
							//do nothing here
						}
						else if (dResult == -1)
						{
							//negate
							out << "fNeg\r\n";
							AddInstruction(FNeg);
						}
						else
						{
							out << fPush(1.0f / dResult) << "\r\nfMult\r\n";//convert the / into a multiply and its reciprocal as fmult is faster than fdiv
							AddInstruction(PushFloat, 1.0f / dResult);
							AddInstruction(FMult);
						}
					}
					else
					{
						parseExpression(argArray[0], false, true);
						out << "fDiv\r\n";
						AddInstruction(FDiv);
					}
					return true;
				}
				Throw("fdiv must have signature \"extern __intrinsic float fdiv(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("fneg"):
			{
				ChkHashCol("fneg");
				if (argCount == 0 && callee->getReturnType()->isRealFloatingType())
				{
					out << "fNeg\r\n";
					AddInstruction(FNeg);
					return true;
				}
				Throw("fneg must have signature \"extern __intrinsic float fneg();\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vadd"):
			{
				ChkHashCol("vadd");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					out << "vAdd\r\n";
					AddInstruction(VAdd);
					return true;
				}
				Throw("vadd must have signature \"extern __intrinsic vector3 vadd(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vsub"):
			{
				ChkHashCol("vsub");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					out << "vSub\r\n";
					AddInstruction(VSub);
					return true;
				}
				Throw("vsub must have signature \"extern __intrinsic vector3 vsub(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vmult"):
			{
				ChkHashCol("vmult");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					out << "vMult\r\n";
					AddInstruction(VMult);
					return true;
				}
				Throw("vmult must have signature \"extern __intrinsic vector3 vmult(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vdiv"):
			{
				ChkHashCol("vdiv");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					out << "vDiv\r\n";
					AddInstruction(VDiv);
					return true;
				}
				Throw("vdiv must have signature \"extern __intrinsic vector3 vdiv(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("vneg"):
			{
				ChkHashCol("vneg");

				if (argCount == 0 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3)
				{
					out << "vNeg\r\n";
					AddInstruction(VNeg);
					return true;
				}
				Throw("vneg must have signature \"extern __intrinsic vector3 vneg()\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("rev"):
			{
				ChkHashCol("rev");

				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						int64_t value = result.getSExtValue();
						if (value >= 2)
						{
							LocalVariables.addLevel();
							int startDeclIndex = LocalVariables.addDecl("__rev-container-var-decl", value);

							//FromStack into it
							out << iPush(value) << endl;
							out << pFrame(startDeclIndex) << endl;
							out << "FromStack" << endl;
							AddInstruction(PushInt, value);
							AddInstruction(GetFrameP, startDeclIndex);
							AddInstruction(FromStack);

							//Put them back on stack in reverse
							for (int i = startDeclIndex + value - 1; i >= startDeclIndex; i--)
							{
								out << frameGet(i) << endl;
								AddInstruction(GetFrame, i);
							}

							LocalVariables.removeLevel();
						}
						else
							Warn("Reverse called with " + to_string(value) + " exchange num.  Expected >= 2", rewriter, argArray[0]->getSourceRange());
					}
					else
					{
						Throw("Reverse count must be called with a compile time constant", rewriter, argArray[0]->getSourceRange());
						return false;
					}
					return true;
				}
				Throw("rev must have signature \"extern __intrinsic void rev(const int numItems);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("exchange"):
			{
				ChkHashCol("exchange");

				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						const Expr* expr = argArray[0]->IgnoreParens()->IgnoreCasts();
						if (isa<UnaryExprOrTypeTraitExpr>(expr) && cast<UnaryExprOrTypeTraitExpr>(expr)->getKind() == UETT_SizeOf)
						{
							Warn("Exchange called with a sizeof operation, did you mean to use stacksizeof", rewriter, argArray[0]->getSourceRange());
						}
						int64_t value = result.getSExtValue();
						if (value > 0)
						{
							LocalVariables.addLevel();
							int firstItemIndex = LocalVariables.addDecl("__exchangeItem1", value);
							int secondItemIndex = LocalVariables.addDecl("__exchangeItem2", value);

							if (value > 1)
							{
								//FromStack into it
								out << iPush(value) << endl;
								out << pFrame(firstItemIndex) << endl;
								out << "FromStack" << endl;
								out << iPush(value) << endl;
								out << pFrame(secondItemIndex) << endl;
								out << "FromStack" << endl;

								//Put them back on stack in reverse
								out << iPush(value) << endl;
								out << pFrame(firstItemIndex) << endl;
								out << "ToStack" << endl;
								out << iPush(value) << endl;
								out << pFrame(secondItemIndex) << endl;
								out << "ToStack" << endl;

								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, firstItemIndex);
								AddInstruction(FromStack);
								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, secondItemIndex);
								AddInstruction(FromStack);

								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, firstItemIndex);
								AddInstruction(ToStack);
								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, secondItemIndex);
								AddInstruction(ToStack);

							}
							else
							{
								out << frameSet(firstItemIndex) << endl << frameSet(secondItemIndex) << endl
									<< frameGet(firstItemIndex) << endl << frameGet(secondItemIndex) << endl;
								AddInstruction(SetFrame, firstItemIndex);
								AddInstruction(SetFrame, secondItemIndex);
								AddInstruction(GetFrame, firstItemIndex);
								AddInstruction(GetFrame, secondItemIndex);


							}


							LocalVariables.removeLevel();
						}
						else
							Warn("Exchange called with " + to_string(value) + " item size num.  Expected a positive value", rewriter, argArray[0]->getSourceRange());
					}
					else
					{
						Throw("Exchange structSize must be called with a compile time constant", rewriter, argArray[0]->getSourceRange());
						return false;
					}
					return true;
				}
				Throw("exchange must have signature \"extern __intrinsic void exchange(const int structStackSize);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			default:
		_IntrinsicNotFound:
			Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
		}

		#undef ChkHashCol

		return false;
	}

	bool parseStatement(Stmt *s, uint64_t breakLoc = -1, uint64_t continueLoc = -1, uint64_t returnLoc = -1) {
		if (isa<CompoundStmt>(s)) {
			CompoundStmt *cSt = cast<CompoundStmt>(s);
			LocalVariables.addLevel();
			for (auto *CS : cSt->body()) {
				parseStatement(cast<Stmt>(CS), breakLoc, continueLoc, returnLoc);
			}
			LocalVariables.removeLevel();
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
					bool ifEndRet = CurrentFunction->endsWithReturn() || CurrentFunction->endsWithInlineReturn(returnLoc);
					if (Else)//still parse the else code just incase there are goto labeils in there
					{
						if (!ifEndRet)
						{
							out << "Jump @" << IfLocEnd << "//ifstmt jmp" << endl;
							AddInstruction(Jump, IfLocEnd);
						}
						LocalVariables.addLevel();
						parseStatement(Else, breakLoc, continueLoc, returnLoc);
						LocalVariables.removeLevel();
						if (!ifEndRet)
						{
							out << endl << ":" << IfLocEnd << "//ifend lbl" << endl;
							AddInstruction(Label, IfLocEnd);
						}

					}
				}
				else
				{
					//still parse the then code just incase there are goto labels in there
					out << "Jump @" << (Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd) << endl;
					AddInstruction(Jump, Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd);
					LocalVariables.addLevel();
					parseStatement(Then, breakLoc, continueLoc, returnLoc);
					LocalVariables.removeLevel();
					bool ifEndRet = CurrentFunction->endsWithReturn() || CurrentFunction->endsWithInlineReturn(returnLoc);
					if (Else)
					{
						if (!ifEndRet)
						{
							out << "Jump @" << IfLocEnd << "//ifstmt jmp" << endl;
							AddInstruction(Jump, IfLocEnd);
						}

						out << endl << ":" << Else->getLocStart().getRawEncoding() << "//ifstmt else lbl" << endl;
						AddInstruction(Label, Else->getLocStart().getRawEncoding());
						LocalVariables.addLevel();
						parseStatement(Else, breakLoc, continueLoc, returnLoc);
						LocalVariables.removeLevel();
					}
					if (!ifEndRet || !Else)
					{
						out << endl << ":" << IfLocEnd << "//ifend lbl" << endl;
						AddInstruction(Label, IfLocEnd);
					}
				}
			}
			else
			{
				parseJumpFalseCondition(conditional, Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd);
				LocalVariables.addLevel();
				parseStatement(Then, breakLoc, continueLoc, returnLoc);
				LocalVariables.removeLevel();
				bool ifEndRet = CurrentFunction->endsWithReturn() || CurrentFunction->endsWithInlineReturn(returnLoc);
				if (!ifEndRet)//if the last instruction is a return, no point adding a jump
				{
					out << "Jump @" << IfLocEnd << "//ifstmt jmp" << endl;
					AddInstruction(Jump, IfLocEnd);
				}

				if (Else) {
					out << endl << ":" << Else->getLocStart().getRawEncoding() << "//ifstmt else lbl" << endl;
					AddInstruction(Label, Else->getLocStart().getRawEncoding());
					LocalVariables.addLevel();
					parseStatement(Else, breakLoc, continueLoc, returnLoc);
					LocalVariables.removeLevel();
					out << "//" << Else->getLocStart().getRawEncoding() << " " << Else->getLocEnd().getRawEncoding() << endl;
				}
				if (Then)
				{
					out << "//" << Then->getLocStart().getRawEncoding() << " " << Then->getLocEnd().getRawEncoding() << endl;
				}

				if (!ifEndRet || !Else)
				{
					out << endl << ":" << IfLocEnd << "//ifend lbl" << endl;
					AddInstruction(Label, IfLocEnd);
				}

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
					AddInstruction(Label, conditional->getLocStart().getRawEncoding());
					parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding(), returnLoc);

					out << "Jump @" << conditional->getLocStart().getRawEncoding() << endl;
					out << endl << ":" << whileStmt->getLocEnd().getRawEncoding() << endl;
					AddInstruction(Jump, conditional->getLocStart().getRawEncoding());
					AddInstruction(Label, whileStmt->getLocEnd().getRawEncoding());
				}
				else
				{
					out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;
					out << "Jump @" << whileStmt->getLocEnd().getRawEncoding() << endl;

					AddInstruction(Label, conditional->getLocStart().getRawEncoding());
					AddInstruction(Jump, whileStmt->getLocEnd().getRawEncoding());

					parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding(), returnLoc);

					out << "Jump @" << conditional->getLocStart().getRawEncoding() << endl;
					out << endl << ":" << whileStmt->getLocEnd().getRawEncoding() << endl;

					AddInstruction(Jump, conditional->getLocStart().getRawEncoding());
					AddInstruction(Label, whileStmt->getLocEnd().getRawEncoding());
				}

			}
			else {

				out << endl << ":" << conditional->getLocStart().getRawEncoding() << endl;
				AddInstruction(Label, conditional->getLocStart().getRawEncoding());
				parseJumpFalseCondition(conditional, to_string(whileStmt->getLocEnd().getRawEncoding()));
				out << endl;

				parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding(), returnLoc);

				out << "Jump @" << conditional->getLocStart().getRawEncoding() << endl;
				out << endl << ":" << whileStmt->getLocEnd().getRawEncoding() << endl;

				AddInstruction(Jump, conditional->getLocStart().getRawEncoding());
				AddInstruction(Label, whileStmt->getLocEnd().getRawEncoding());
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
				AddInstruction(Label, conditional->getLocStart().getRawEncoding());

				parseJumpFalseCondition(conditional, to_string(body->getLocEnd().getRawEncoding()));
				out << endl;
			}
			else
			{
				out << endl << ":" << body->getLocStart().getRawEncoding() << endl;
				AddInstruction(Label, body->getLocStart().getRawEncoding());
			}

			parseStatement(
				body,
				forStmt->getLocEnd().getRawEncoding(),
				increment ? increment->getLocStart().getRawEncoding() : conditional ? conditional->getLocStart().getRawEncoding() : body->getLocStart().getRawEncoding(),
				returnLoc);

			if (increment)
			{
				out << endl << ":" << increment->getLocStart().getRawEncoding() << "//forstmt inc lbl" << endl;
				AddInstruction(Label, increment->getLocStart().getRawEncoding());
			}

			if (increment)
				parseExpression(increment);

			if (conditional)
			{
				out << "Jump @" << conditional->getLocStart().getRawEncoding() << "//forstmt cond jmp" << endl;
				AddInstruction(Jump, conditional->getLocStart().getRawEncoding());
			}
			else
			{
				out << "Jump @" << body->getLocStart().getRawEncoding() << "//forstmt jmp" << endl;
				AddInstruction(Jump, body->getLocStart().getRawEncoding());
			}


			out << endl << ":" << body->getLocEnd().getRawEncoding() << "//forend lbl" << endl;
			AddInstruction(Label, body->getLocEnd().getRawEncoding());
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
			AddInstruction(Label, body->getLocStart().getRawEncoding());
			parseStatement(body, conditional->getLocEnd().getRawEncoding(), body->getLocEnd().getRawEncoding(), returnLoc);



			out << endl << ":" << body->getLocEnd().getRawEncoding() << "" << endl;
			AddInstruction(Label, body->getLocEnd().getRawEncoding());

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
					AddInstruction(Jump, body->getLocStart().getRawEncoding());
				}
				//no need for else, just jump right out

			}
			else
			{
				parseJumpFalseCondition(conditional, to_string(body->getLocStart().getRawEncoding()), true);
				out << endl;
			}

			out << endl << ":" << conditional->getLocEnd().getRawEncoding() << "" << endl;
			AddInstruction(Label, conditional->getLocEnd().getRawEncoding());
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
				AddInstruction(Return, paramSize + (isa<CXXMethodDecl>(currFunction) ? 1 : 0), getSizeFromBytes(size));
			}
			else
			{
				out << "Jump @" << returnLoc << endl;
				AddInstruction(Jump, to_string(returnLoc));
			}

		}
		else if (isa<Expr>(s)) {
			parseExpression(cast<const Expr>(s));
		}
		else if (isa<BreakStmt>(s)) {
			out << "Jump @" << breakLoc << "//brkstmt jmp" << endl;
			AddInstruction(Jump, to_string(breakLoc));
		}
		else if (isa<NullStmt>(s)) {
			// out << "nop " << breakLoc << endl;
		}
		else if (isa<ContinueStmt>(s)) {
			out << "Jump @" << continueLoc << "//contstmt jmp" << endl;
			AddInstruction(Jump, to_string(continueLoc));
		}
		else if (isa<DefaultStmt>(s)) {
			DefaultStmt *caseD = cast<DefaultStmt>(s);
			string labelName = ":" + to_string(caseD->getLocEnd().getRawEncoding());
			if (FindBuffer.find(labelName) == FindBuffer.end())
			{
				FindBuffer.insert(labelName);
				out << labelName << endl;
				AddInstruction(Label, labelName.substr(1));
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
				AddInstruction(Label, labelName.substr(1));
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
			AddInstruction(Switch);

			//Build case switch list first
			SwitchCase *switchCaseList = switchStmt->getSwitchCaseList();
			DefaultStmt *defaultCase = NULL;
			stack<string> caseLabels;
			struct switchCase { int val; string loc; };
			stack<switchCase> caseLabelsNew;
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
							{
								caseLabels.push("[" + to_string(val) + " @" + to_string(caseS->getLocEnd().getRawEncoding()) + "]");
								caseLabelsNew.push({ val, to_string(caseS->getLocEnd().getRawEncoding()) });
							}
							else
							{
								caseLabels.push("[" + to_string(result.Val.getInt().getSExtValue()) + " @" + to_string(caseS->getLocEnd().getRawEncoding()) + "]");
								caseLabelsNew.push({ (int)result.Val.getInt().getSExtValue(), to_string(caseS->getLocEnd().getRawEncoding()) });
							}
						}
						else if (result.Val.isFloat())
						{
							caseLabels.push("[" + to_string(result.Val.getFloat().convertToFloat()) + " @" + to_string(caseS->getLocEnd().getRawEncoding()) + "]");
							float f = result.Val.getFloat().convertToFloat();
							caseLabelsNew.push({ *(int*)&f, to_string(caseS->getLocEnd().getRawEncoding()) });
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
			if(!caseLabelsNew.size())
			{
				Throw("Switch statement contains no cases", rewriter, switchStmt->getSourceRange());
			}
			while (caseLabels.size() > 1)
			{
				out << caseLabels.top() << ":";

				caseLabels.pop();
			}
			out << caseLabels.top() << endl;
			while (caseLabelsNew.size())
			{
				CurrentFunction->addSwitchCase(caseLabelsNew.top().val, caseLabelsNew.top().loc);
				caseLabelsNew.pop();
			}

			if (defaultCase)
			{
				out << "Jump @" << defaultCase->getLocEnd().getRawEncoding() << endl;
				AddInstruction(Jump, defaultCase->getLocEnd().getRawEncoding());
			}
			else
			{
				out << "Jump @" << switchStmt->getLocEnd().getRawEncoding() << endl;
				AddInstruction(Jump, switchStmt->getLocEnd().getRawEncoding());
			}

			//parse all
			parseStatement(switchStmt->getBody(), switchStmt->getLocEnd().getRawEncoding(), continueLoc, returnLoc);
			out << "//SwitchEnd" << endl << endl;
			out << ":" << switchStmt->getLocEnd().getRawEncoding() << endl;
			AddInstruction(Label, switchStmt->getLocEnd().getRawEncoding());
			FindBuffer.clear();
		}
		else if (isa<GotoStmt>(s))
		{
			GotoStmt *gotoStmt = cast<GotoStmt>(s);
			out << "Jump @" << gotoStmt->getLabel()->getNameAsString() << endl;
			AddInstruction(Jump, gotoStmt->getLabel()->getNameAsString());
		}
		else if (isa<LabelStmt>(s))
		{
			LabelStmt *labelStmt = cast<LabelStmt>(s);
			out << ":" << labelStmt->getName() << endl;
			AddInstruction(Label, string(labelStmt->getName()));
			parseStatement(labelStmt->getSubStmt(), breakLoc, continueLoc, returnLoc);
		}
		else if (isa<GCCAsmStmt>(s))
		{
			GCCAsmStmt *asmstmt = cast<GCCAsmStmt>(s);
			Throw("Coding in assembley isnt supported", rewriter, s->getSourceRange());//throw an error as the new method of compiling wont support this
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

	/// <summary>
	/// Parses the expression.
	/// </summary>
	/// <param name="e">The e.</param>
	/// <param name="isAddr">if set to <c>true</c> [is addr].</param>
	/// <param name="isLtoRValue">if set to <c>true</c> [is lto r value].</param>
	/// <param name="printVTable">if set to <c>true</c> [print v table].</param>
	/// <param name="isAssign">if set to <c>true</c> [is assign].</param>
	/// <returns></returns>
	int parseExpression(const Expr *e, bool isAddr = false, bool isLtoRValue = false, bool printVTable = true, bool isAssign = false, bool isArrToPtrDecay= false ) {
		Expr::EvalResult result;
		if(e->EvaluateAsRValue(result, *context) && !result.HasSideEffects)
		{
			if(result.Val.isInt())
			{
				if(!isLtoRValue)
					return -1;
				int val;
				if(CheckExprForSizeOf(e->IgnoreParens(), &val))
				{
					out << iPush(val) << endl;
					AddInstruction(PushInt, val);
				}
				else
				{
					int64_t resValue = result.Val.getInt().getSExtValue();

					if(doesInt64FitIntoInt32(resValue))
					{
						string value = to_string(resValue);
						Warn("Integer overflow. Value: " + value + " is out of bounds of (-2,147,483,648 to 2,147,483,647). Changed value to " + to_string((int32_t)resValue), rewriter, e->getExprLoc(), e->getExprLoc().getLocWithOffset(value.length() - 1));

					}
					out << iPush((int32_t)resValue) << endl;
					AddInstruction(PushInt, (int32_t)resValue);
				}
				return -1;
			}
			else if(result.Val.isFloat())
			{
				if(!isLtoRValue)
					return -1;
				out << fPush(result.Val.getFloat()) << endl;
				AddInstruction(PushFloat, extractAPFloat(result.Val.getFloat()));
				return -1;
			}
			else if(result.Val.isComplexFloat())
			{
				if(!isLtoRValue)
					return -1;
				out << fPush(result.Val.getComplexFloatReal()) << endl;
				out << fPush(result.Val.getComplexFloatImag()) << endl;
				AddInstruction(PushFloat, extractAPFloat(result.Val.getComplexFloatReal()));
				AddInstruction(PushFloat, extractAPFloat(result.Val.getComplexFloatImag()));
				return -1;
			}
			else if(result.Val.isComplexInt())
			{
				if(!isLtoRValue)
					return -1;
				out << iPush(result.Val.getComplexIntReal().getSExtValue()) << endl;
				out << iPush(result.Val.getComplexIntImag().getSExtValue()) << endl;
				AddInstruction(PushInt, result.Val.getComplexIntReal().getSExtValue());
				AddInstruction(PushInt, result.Val.getComplexIntImag().getSExtValue());
				return -1;
			}
		}
		/*if (isa<IntegerLiteral>(e)) {
			out << iPush(cast<const IntegerLiteral>(e)->getValue().getSExtValue()) << endl;
			AddInstruction(PushInt, cast<const IntegerLiteral>(e)->getValue().getSExtValue());
		}
		else if (isa<FloatingLiteral>(e)) {
			out << fPush(cast<const FloatingLiteral>(e)->getValue()) << endl;
			AddInstruction(PushFloat, extractAPFloat(cast<const FloatingLiteral>(e)->getValue()));
		}*/
		if (isa<CompoundLiteralExpr>(e)) {
			const CompoundLiteralExpr *cLit = cast<const CompoundLiteralExpr>(e);
			parseExpression(cLit->getInitializer(), isAddr, isLtoRValue);
			if (isArrToPtrDecay && isLtoRValue)
			{
				int size = getSizeFromBytes(getSizeOfType(e->getType().getTypePtr()));
				int index = LocalVariables.addDecl("", size);
				if (size > 1)
				{
					out << iPush(size) << " //Type Size\r\n" << pFrame(index) << "\r\nFromStack\r\n" << pFrame(index) << " //compound literal ptr decay\r\n";
					AddInstructionComment(PushInt, "Type Size", size);
					AddInstruction(GetFrameP, index);
					AddInstruction(FromStack);
					AddInstructionComment(GetFrameP, "compound literal ptr decay", index);
				}
				else
				{
					out << frameSet(index) << "\r\n" << pFrame(index) << " //compound literal ptr decay\r\n";
					AddInstruction(SetFrame, index);
					AddInstructionComment(GetFrameP, "compound literal ptr decay", index);
				}
			}
		}
		else if (isa<StringLiteral>(e)) {
			string str = cast<const StringLiteral>(e)->getString().str();
			if (isLtoRValue)
			{
				if (isArrToPtrDecay)
				{
					out << "PushString \"" << str << "\"";
					AddInstruction(PushString, str);
				}
				else
				{
					int size = getSizeOfType(e->getType().getTypePtr());
					int litSize = str.size();
					const char *ptr = str.c_str();
					for (int i = 0; i < size; i += 4)
					{
						uint32_t res = 0;
						for (int j = 0; j < 4; j++)
						{
							if (i + j < litSize){
								res |= ptr[i + j] << ((3 - j) << 3);
							}
						}
						out << iPush((int32_t)res) << endl;
						AddInstruction(PushInt, (int32_t)res);
					}
				}
			}
			
			
		}
		else if (isa<CallExpr>(e)) {
			const CallExpr *call = cast<const CallExpr>(e);
			if (checkIntrinsic(call))
				return 1;
			const Expr* callee = call->getCallee();
			if (isAddr)
			{
				Throw("cannot take the address of an rvalue of type '" + QualType::getAsString(call->getCallReturnType(*context).split()) + "'", rewriter, call->getSourceRange());
			}
			LocalVariables.addLevel();
			if (isa<MemberExpr>(callee))
			{
				const MemberExpr *expr = cast<const MemberExpr>(call->getCallee());
				if (isa<CXXMethodDecl>(expr->getMemberDecl())) {
					const CXXMethodDecl *method = cast<const CXXMethodDecl>(expr->getMemberDecl());
					if (method->isVirtualAsWritten()) {
						const CXXRecordDecl *classDecl = method->getParent();


						//int offset = 0;
						printVirtualCall(classDecl, method, expr->getBase());
					}
					else {

						parseExpression(expr->getBase(), true);
						out << "call " << getNameForFunc(method) << " //NumArgs: " << call->getNumArgs() + 1 << " " << endl;
						AddInstruction(Call, getNameForFunc(method).substr(1));
					}
				}
				else {
					Throw("Unhandled Call Member Expression", rewriter, e->getSourceRange());
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
					NativeFuncAttr *attr = call->getDirectCallee()->getAttr<NativeFuncAttr>();

					if (call->getDirectCallee()->getStorageClass() != SC_Extern)
					{
						Throw("Natives should be defined with the 'extern' keyword", rewriter, call->getDirectCallee()->getLocation());
					}
					const QualType type = call->getDirectCallee()->getReturnType();
					out << "CallNative " << (parseCast(cast<const CastExpr>(callee)).c_str() + 1) << " " << call->getNumArgs() << " " << getSizeFromBytes(getSizeOfQualType(&type)) << endl;
					if (attr->getX64HiDwordHash() || attr->getHash())
					{
						//clang attribute arguments cannot be 64bits wide, so using 2 32 bit args can manually joining them is the nicest way to support pc
						//when using 32 bit(xbox/ps3) the hi dword would be 0 so can be neglected
						AddInstruction(Native, parseCast(cast<const CastExpr>(callee)).substr(1), ((uint64_t)attr->getX64HiDwordHash() << 32) | attr->getHash(), call->getNumArgs(), getSizeFromBytes(getSizeOfType(type.getTypePtr())));
					}
					else
					{
						AddInstruction(Native, parseCast(cast<const CastExpr>(callee)).substr(1), call->getNumArgs(), getSizeFromBytes(getSizeOfType(type.getTypePtr())));
					}

				}
				//else if (call->getDirectCallee() && !call->getDirectCallee()->isDefined() && call->getDirectCallee()->getStorageClass() != StorageClass::SC_Extern)
				//	Throw("Function \"" + call->getDirectCallee()->getNameAsString() + "\" Not Defined", rewriter, call->getExprLoc());
				else if (isa<PointerType>(callee->getType()) && !call->getDirectCallee())
				{
					parseExpression(call->getCallee(), false, true);
					out << "PCall\r\n";
					AddInstruction(PCall);
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
							CompoundStmt *body = cast<CompoundStmt>(cDecl->getBody());
							Stmt *subBody = body;
							bool isEmpty = false;
							if (!cDecl->hasAttr<NoInlineAttr>())
							{
								if (body->size() == 0)
								{
									isEmpty = true;
								}
								else if (body->size() == 1)
								{
									subBody = body->body_front();
								}
								if (isEmpty)
								{
									inlined = true;
									for (uint32_t i = 0; i < cDecl->getNumParams(); i++)
									{
										for (int32_t paramSize = getSizeFromBytes(getSizeOfType(cDecl->getParamDecl(i)->getType().getTypePtr())); paramSize--;)
										{
											out << "Drop\r\n";
											AddInstruction(Drop);
										}
									}
								}
								else
								{
									bool isRet = isa<ReturnStmt>(subBody);
									bool isExpr = isa<Expr>(subBody);
									bool inlineSpec = cDecl->isInlineSpecified();
									if (isRet || isExpr || inlineSpec) //inline it
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
											AddInstruction(SetFrame, Index);
										}
										else if (paramSize > 1)
										{
											out << iPush(paramSize) << endl << pFrame(Index) << "\r\nFromStack\r\n";
											AddInstruction(PushInt, paramSize);
											AddInstruction(GetFrameP, Index);
											AddInstruction(FromStack);
										}
										if (isRet) {
											parseExpression(cast<ReturnStmt>(subBody)->getRetValue(), false, true);
										}
										else if (isExpr)
										{
											parseExpression(cast<Expr>(subBody));
										}
										else
										{
											parseStatement(body, -1, -1, e->getLocEnd().getRawEncoding());
											if (CurrentFunction->endsWithInlineReturn(e->getLocEnd().getRawEncoding()))
											{
												CurrentFunction->RemoveLast();
												//remove the last jump, but keep the label, just incase other places in the function have returns
											}
											out << ":" << e->getLocEnd().getRawEncoding() << endl;
											AddInstruction(Label, e->getLocEnd().getRawEncoding());
										}
										LocalVariables.removeLevel();
										removeFunctionInline(name);

									}
								}
							}
						}
					}
					if (!inlined)
					{
						string name = parseCast(cast<const CastExpr>(callee));
						uint32_t hash = Utils::Hashing::JoaatCased((char*)name.c_str());
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
						for (uint32_t j = 0; j < functionsNew.size(); j++)
							if (functionsNew[j]->Hash() == hash)
							{
								if (functionsNew[j]->Name() == name)
								{
									CurrentFunction->addUsedFunc(functionsNew[j]);
									break;
								}
							}
						if (i >= functions.size())
							Throw("Function \"" + name + "\" not found", rewriter, call->getExprLoc());

						out << "Call " << name << " //NumArgs: " << call->getNumArgs() << " " << endl;
						AddInstructionComment(Call, "NumArgs: " + to_string(call->getNumArgs()), name.substr(1));
					}

				}

				if (call->getType()->isVoidType() == false) {
					if (!isLtoRValue) {
						out << "Drop//Function Result unused" << endl;
						AddInstructionComment(Drop, "Function Result Unused");
						int size = getSizeFromBytes(getSizeOfType(call->getType().getTypePtr()));
						for (int i = 1; i < size; i++)
						{
							out << "Drop" << endl;
							AddInstruction(Drop);
						}
					}
				}
			}
			else
				Throw("Unexpected Expression for Callee!", rewriter, callee->getExprLoc());
				LocalVariables.removeLevel();
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
						if (isLtoRValue)
						{
							out << "PushF " << literal->getValue().getSExtValue() << ".0" << endl;
							AddInstruction(PushFloat, (float)(int)(literal->getValue().getSExtValue()));
						}
						return true;
					}
					else {
						parseExpression(icast->getSubExpr(), false, true);
						out << (isLtoRValue ? "itof\r\n" : "drop\r\n");
						if (isLtoRValue)
							AddInstruction(ItoF);
						else
							AddInstruction(Drop);
						return true;
					}
				}
				case clang::CK_FloatingCast:
				case clang::CK_IntegralCast:
				parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
				break;
				case clang::CK_ArrayToPointerDecay:

						parseExpression(icast->getSubExpr(), isAddr, isLtoRValue, printVTable, isAssign, true);
				
				break;
				case clang::CK_LValueToRValue:
				{
					parseExpression(icast->getSubExpr(), isAddr, true, printVTable);
					if (!isLtoRValue)
					{
						for (int i = getSizeFromBytes(getSizeOfType(icast->getSubExpr()->getType().getTypePtr())); i--;)
						{
							out << "drop //unused result (CK_LValueToRValue)\r\n";
							AddInstructionComment(Drop, "unused result (CK_LValueToRValue)");
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
							AddInstructionComment(PushInt, "Base+" + to_string(offset), offset / 4);
							parseExpression(declRef, true);
							out << "GetArrayP2 1  " << " //Cast : " << base->getDeclName().getAsString() << " to " << icast->getType()->getAsCXXRecordDecl()->getDeclName().getAsString() << endl;
							AddInstructionComment(GetArrayP, "Cast : " + base->getDeclName().getAsString() + " to " + icast->getType()->getAsCXXRecordDecl()->getDeclName().getAsString(), 1);
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
							AddInstructionComment(PushInt, "Base+" + to_string(offset), offset / 4);
							parseExpression(expr, true);
							AddInstruction(GetArrayP, 1);
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
						Throw("Unsupported Cast", rewriter, icast->getSourceRange());
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
					if (!isLtoRValue)
					{
						out << "drop //unused result\r\n";
						AddInstructionComment(Drop, "unused result");
					}
					break;
				}
				case clang::CK_IntegralToPointer:
				{
					//Fixed support for:
					//char* test = GET_STRING_PTR();
					//and other pointers
					parseExpression(icast->getSubExpr(), false, true);
					if (!isLtoRValue)
					{
						out << "drop //unused result\r\n";
						AddInstructionComment(Drop, "unused result");
					}
					break;
				}
				case clang::CK_FloatingToIntegral:
				{

					parseExpression(icast->getSubExpr(), false, true);
					out << (isLtoRValue ? "ftoi\r\n" : "drop\r\n");
					if (isLtoRValue)
						AddInstruction(FtoI);
					else
						AddInstruction(Drop);
					break;
				}
				case clang::CK_NoOp:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
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
					if (isLtoRValue) {
						out << fPush(0.0f) << "\r\nfCmpNe\r\n";
						AddInstruction(PushFloat, 0);
						AddInstruction(FCmpNe);
					}
					break;
				}
				case clang::CK_FloatingComplexToReal:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (!isLtoRValue) {
						out << "Drop\r\n";//if its not l2r value both will be dropped in parse expression
						AddInstruction(Drop);
					}
					break;
				}
				case clang::CK_IntegralComplexToReal:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (!isLtoRValue) {
						out << "Drop\r\n";//if its not l2r value both will be dropped in parse expression
						AddInstruction(Drop);
					}
					break;
				}
				case clang::CK_NullToPointer:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					break;
				}
				case clang::CK_FloatingRealToComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (isLtoRValue) {
						out << "PushF_0\r\n"; //Push 0.0f for imag part
						AddInstruction(PushFloat, 0);
					}
					break;
				}
				case clang::CK_IntegralRealToComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (isLtoRValue) {
						out << "Push_0\r\n"; //Push 0 for imag part
						AddInstruction(PushInt, 0);
					}
					break;
				}
				case clang::CK_FloatingComplexToIntegralComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (isLtoRValue) {
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nFtoI\r\n" << frameGet(index) << "\r\nFtoI\r\n";
						AddInstruction(SetFrame, index);
						AddInstruction(FtoI);
						AddInstruction(GetFrame, index);
						AddInstruction(FtoI);
						LocalVariables.removeLevel();
					}
					break;
				}
				case clang::CK_IntegralComplexToFloatingComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (isLtoRValue) {
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nItoF\r\n" << frameGet(index) << "\r\nItoF\r\n";
						AddInstruction(SetFrame, index);
						AddInstruction(ItoF);
						AddInstruction(GetFrame, index);
						AddInstruction(ItoF);
						LocalVariables.removeLevel();
					}
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
					if (isLtoRValue)ComplexToBoolean(true);
					break;
				}
				case clang::CK_IntegralComplexToBoolean:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (isLtoRValue)ComplexToBoolean(false);
					break;
				}
				case clang::CK_ToUnion:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);//clang does check to make sure this is valid	
					break;
				}
				default:
				Throw("Unhandled cast (CK) of type " + string(icast->getCastKindName()), rewriter, e->getSourceRange());

			}
		}
		else if (isa<DeclRefExpr>(e)) {
			const DeclRefExpr *declref = cast<const DeclRefExpr>(e);

			if (isa<EnumConstantDecl>(declref->getDecl())) {
				const EnumConstantDecl *enumDecl = cast<const EnumConstantDecl>(declref->getDecl());
				int val = enumDecl->getInitVal().getSExtValue();
				out << iPush(val) << endl;
				AddInstruction(PushInt, val);
				return 1;
			}

			string key = declref->getNameInfo().getAsString();

			if (declref->getDecl()->getType().getTypePtr()->isArrayType())
			{
				printDeclWithKey(key, true, isLtoRValue, isAssign, declref);
			}
			else
				printDeclWithKey(key, isAddr, isLtoRValue, isAssign, declref);

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
					AddInstruction(PushInt, -literal->getValue().getSExtValue());
				}
				else if (isa<FloatingLiteral>(subE)) {
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);

					out << fPush(extractAPFloat(literal->getValue()) * -1.0) << endl;
					AddInstruction(PushFloat, -1.0f * extractAPFloat(literal->getValue()));
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
						AddInstruction(SetFrame, index);
						AddInstruction(FNeg);
						AddInstruction(GetFrame, index);
						AddInstruction(FNeg);
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nNeg\r\n" << frameGet(index) << "\r\nNeg\r\n";
						AddInstruction(SetFrame, index);
						AddInstruction(Neg);
						AddInstruction(GetFrame, index);
						AddInstruction(Neg);
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isRealFloatingType())
					{
						out << "fNeg\r\n";
						AddInstruction(FNeg);
					}
					else
					{
						out << "Neg\r\n";
						AddInstruction(Neg);
					}

				}
				else
				{
					Throw("unimplmented UO_MINUS", rewriter, e->getSourceRange());
				}
				return false;
			}
			else if (op->getOpcode() == UO_LNot) {
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					out << iPush(!literal->getValue().getSExtValue()) << endl;
					AddInstruction(PushInt, !literal->getValue().getSExtValue());

				}
				else if (isa<FloatingLiteral>(subE))
				{
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);
					out << fPush(!extractAPFloat(literal->getValue())) << endl;
					AddInstruction(PushFloat, !extractAPFloat(literal->getValue()));

				}
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nPushF_0\r\nfCmpEq\r\n" << frameGet(index) << "\r\nPushF_0\r\nfCmpEq\r\nAnd\r\n";
						AddInstruction(SetFrame, index);
						AddInstruction(PushFloat, 0);
						AddInstruction(FCmpEq);
						AddInstruction(GetFrame, index);
						AddInstruction(PushFloat, 0);
						AddInstruction(FCmpEq);
						AddInstruction(And);
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
						out << frameSet(index) << "\r\nnot\r\n" << frameGet(index) << "\r\nnot\r\nAnd\r\n";
						AddInstruction(SetFrame, index);
						AddInstruction(Not);
						AddInstruction(GetFrame, index);
						AddInstruction(Not);
						AddInstruction(And);
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isFloatingType())
					{
						out << "PushF_0\r\nfCmpEq\r\n";
						AddInstruction(PushFloat, 0);
						AddInstruction(FCmpEq);
					}
					else
					{
						out << "not\r\n";
						AddInstruction(Not);
					}

				}
				else
				{
					Throw("unimplmented UO_LNot", rewriter, e->getSourceRange());
				}

				return true;
			}
			else if (op->getOpcode() == UO_Not)
			{
				if (isa<IntegerLiteral>(subE)) {
					const IntegerLiteral *literal = cast<const IntegerLiteral>(subE);
					out << iPush(~(int)literal->getValue().getSExtValue()) << endl;
					AddInstruction(PushInt, ~(int)literal->getValue().getSExtValue());

				}
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					//Not operator for complex numbers is the conjugate
					if (subE->getType()->isComplexIntegerType())
					{
						out << "Neg\r\n";
						AddInstruction(Neg);
					}
					else if (subE->getType()->isComplexType())
					{
						out << "fNeg\r\n";
						AddInstruction(FNeg);
					}
					else
					{
						out << "Add1 1\r\nNeg\r\n";
						AddInstruction(AddImm, 1);
						AddInstruction(Neg);
					}
				}
				else
				{
					Throw("unimplmented UO_Not", rewriter, e->getSourceRange());
				}
				return true;
			}
			else if (op->getOpcode() == UO_AddrOf) {
				if (isa<ArraySubscriptExpr>(subE)) {
					parseArraySubscriptExpr(subE, true);
				}
				else if (isa<DeclRefExpr>(subE)) {
					parseExpression(subE, true, false);
					if (!isLtoRValue && !isAddr) {
						out << "Drop //unused result (UO_AddrOf - DeclRefExpr)\r\n";
						AddInstructionComment(Drop, "unused result (UO_AddrOf - DeclRefExpr)");
					}
				}
				else {
					parseExpression(subE, true, false);
					if (!isLtoRValue) {
						out << "Drop //unused result (UO_AddrOf - else)\r\n";
						AddInstructionComment(Drop, "unused result (UO_AddrOf - else)");
					}
				}
				return  true;

			}
			else if (op->getOpcode() == UO_Deref) {
				if (isa<ArraySubscriptExpr>(subE)) {
					out << "//deref ArraySubscriptExpr" << endl;
					parseArraySubscriptExpr(subE, false);
				}
				else if (isa<DeclRefExpr>(subE)) {
					out << "//deref DeclRefExpr" << endl;
					parseExpression(subE, false, false);
				}
				else {
					parseExpression(subE, false, true);
				}
				if (!isAddr)
				{
					if (isLtoRValue)
					{
						out << "pGet" << endl;
						AddInstruction(PGet);
					}
					else
					{
						out << "pSet" << endl;
						AddInstruction(PSet);
					}
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
						if (isLtoRValue)
						{
							out << "Drop\r\n";
							AddInstruction(Drop);
						}
					}
					else
					{
						Throw("__real operator used on non complex data type");
					}
				}
				else
				{
					Throw("unimplmented UO_Real", rewriter, e->getSourceRange());
				}
				return true;
			}
			else if (op->getOpcode() == UO_Imag)
			{
				if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (subE->getType()->isAnyComplexType())
					{
						if (isLtoRValue)
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("imagPart", 1);
							out << frameSet(index) << "\r\nDrop\r\n" << frameGet(index) << endl;
							AddInstruction(SetFrame, index);
							AddInstruction(Drop);
							AddInstruction(GetFrame, index);
							LocalVariables.removeLevel();
						}
					}
					else
					{
						Throw("__imag operator used on non complex data type");
					}
				}
				else
				{
					Throw("unimplmented UO_Imag", rewriter, e->getSourceRange());
				}
				return true;
			}

			int pMult = 1;
			if ((op->isPrefix() || op->isPostfix()) && isa<PointerType>(subE->getType()))
			{
				const Type* pTypePtr = subE->getType().getTypePtr()->getPointeeType().getTypePtr();
				int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
				pMult = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;
			}

			if (op->isPrefix()) {

				if (op->isIncrementOp()) {
					parseExpression(subE, false, true);

					if (subE->getType()->isRealFloatingType())
					{
						out << "PushF_1\r\nfAdd\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FAdd);
					}
					else if(subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << "PushF_1\r\nfAdd\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FAdd);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if(subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << add(pMult) << endl;
						AddInstruction(AddImm, pMult);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
					{
						Throw("Incriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
					}
					else
					{
						out << add(pMult) << endl;
						AddInstruction(AddImm, pMult);
					}
					if(isLtoRValue)
					{
						if(subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
							out << frameSet(index + 1) << "\r\ndup\r\n" << frameSet(index) << endl << frameGet(index + 1) << endl << frameGet(index) << endl << frameGet(index + 1) << endl;
							AddInstruction(SetFrame, index + 1);//store imag
							AddInstruction(Dup);//dup real
							AddInstruction(SetFrame, index);//store real
							AddInstruction(GetFrame, index + 1);//restore imag
							AddInstruction(GetFrame, index);//push real
							AddInstruction(GetFrame, index + 1);//push imag
							LocalVariables.removeLevel();
						}
						else
						{
							out << "Dup" << endl;
							AddInstruction(Dup);
						}
					}
					parseExpression(subE, false, false, true, true);
					return 1;
				}
				else if (op->isDecrementOp()) {
					parseExpression(subE, false, true);

					if(subE->getType()->isRealFloatingType())
					{
						out << "PushF_1\r\nfSub\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FSub);
					}
					else if(subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << "PushF_1\r\nfSub\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FSub);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if(subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << sub(pMult) << endl;
						AddInstruction(AddImm, -pMult);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if(getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
					{
						Throw("Decriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
					}
					else
					{
						out << sub(pMult) << endl;
						AddInstruction(AddImm, -pMult);
					}
					if(isLtoRValue)
					{
						if(subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
							out << frameSet(index + 1) << "\r\ndup\r\n" << frameSet(index) << endl << frameGet(index + 1) << endl << frameGet(index) << endl << frameGet(index + 1) << endl;
							AddInstruction(SetFrame, index + 1);//store imag
							AddInstruction(Dup);//dup real
							AddInstruction(SetFrame, index);//store real
							AddInstruction(GetFrame, index + 1);//restore imag
							AddInstruction(GetFrame, index);//push real
							AddInstruction(GetFrame, index + 1);//push imag
							LocalVariables.removeLevel();
						}
						else
						{
							out << "Dup" << endl;
							AddInstruction(Dup);
						}
					}
					parseExpression(subE, false, false, true, true);
					return 1;
				}
			}
			else if (op->isPostfix()) {
				if (op->isIncrementOp()) {
					parseExpression(subE, false, true);
					if(isLtoRValue)
					{
						if(subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
							out << frameSet(index + 1) << "\r\ndup\r\n" << frameSet(index) << endl << frameGet(index + 1) << endl << frameGet(index) << endl << frameGet(index + 1) << endl;
							AddInstruction(SetFrame, index + 1);//store imag
							AddInstruction(Dup);//dup real
							AddInstruction(SetFrame, index);//store real
							AddInstruction(GetFrame, index + 1);//restore imag
							AddInstruction(GetFrame, index);//push real
							AddInstruction(GetFrame, index + 1);//push imag
							LocalVariables.removeLevel();
						}
						else
						{
							out << "Dup" << endl;
							AddInstruction(Dup);
						}
					}
					if(subE->getType()->isRealFloatingType())
					{
						out << "PushF_1\r\nfAdd\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FAdd);
					}
					else if(subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << "PushF_1\r\nfAdd\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FAdd);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if(subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << add(pMult) << endl;
						AddInstruction(AddImm, pMult);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if(getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
					{
						Throw("Incriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
					}
					else
					{
						out << add(pMult) << endl;
						AddInstruction(AddImm, pMult);
					}

					parseExpression(subE, false, false, true, true);
					return 1;
				}
				else if (op->isDecrementOp()) {
					parseExpression(subE, false, true);
					if(isLtoRValue)
					{
						if(subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
							out << frameSet(index + 1) << "\r\ndup\r\n" << frameSet(index) << endl << frameGet(index + 1) << endl << frameGet(index) << endl << frameGet(index + 1) << endl;
							AddInstruction(SetFrame, index + 1);//store imag
							AddInstruction(Dup);//dup real
							AddInstruction(SetFrame, index);//store real
							AddInstruction(GetFrame, index + 1);//restore imag
							AddInstruction(GetFrame, index);//push real
							AddInstruction(GetFrame, index + 1);//push imag
							LocalVariables.removeLevel();
						}
						else
						{
							out << "Dup" << endl;
							AddInstruction(Dup);
						}
					}

					if(subE->getType()->isRealFloatingType())
					{
						out << "PushF_1\r\nfSub\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FSub);
					}
					else if(subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << "PushF_1\r\nfSub\r\n";
						AddInstruction(PushFloat, 1.0);
						AddInstruction(FSub);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if(subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						out << frameSet(index) << endl;
						AddInstruction(SetFrame, index);
						out << sub(pMult) << endl;
						AddInstruction(AddImm, -pMult);
						out << frameGet(index) << endl;
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if(getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
					{
						Throw("Decriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
					}
					else
					{
						out << sub(pMult) << endl;
						AddInstruction(AddImm, -pMult);
					}
					parseExpression(subE, false, false, true, true);
					return 1;
				}
			}
		}
		else if (isa<CXXThisExpr>(e)) {
			out << "GetFrame1 0 //\"this\"" << endl;
			AddInstruction(GetFrame, 0);
		}
		else if (isa<CXXConstructExpr>(e)) {
			const CXXConstructExpr *expr = cast<const CXXConstructExpr>(e);
			if (printVTable) {


				//out << "\n//VTableInit " << endl;
				//out << "call "
				if (expr->getType()->isArrayType()) {
					out << "dup" << endl;
					out << "call @" << expr->getType()->getAsArrayTypeUnsafe()->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl()->getNameAsString() << "::VTableInit" << endl;//printVTableInit(expr->getType()->getAsArrayTypeUnsafe()->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), lastDecl);
					AddInstruction(Dup);
					AddInstruction(Call, expr->getType()->getAsArrayTypeUnsafe()->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl()->getNameAsString() + "::VTableInit");
				}
				else {
					out << "dup" << endl;
					AddInstruction(Dup);
					out << "call " << expr->getBestDynamicClassType()->getNameAsString() << "::VTableInit" << endl;//printVTableInit(expr->getBestDynamicClassType(), lastDecl);
					AddInstruction(Call, expr->getBestDynamicClassType()->getNameAsString().substr(1) + "::VTableInit");
				}
				//  out << " //End_VtableInit\n" << endl;
			}
			if (expr->getConstructor()->hasBody())
			{
				out << "call " << getNameForFunc(expr->getConstructor()) << " // ctor" << endl;
				AddInstruction(Call, getNameForFunc(expr->getConstructor()).substr(1));
			}
		}
		else if (isa<BinaryOperator>(e)) {
			const BinaryOperator *bOp = cast<const BinaryOperator>(e);
			BinaryOperatorKind op = bOp->getOpcode();

			if (bOp->getOpcode() == BO_Assign) {

				parseExpression(bOp->getRHS(), isAddr, true, true);
				int bSize = getSizeFromBytes(getSizeOfType(bOp->getRHS()->getType().getTypePtr()));
				if (bSize > 1)
				{
					out << iPush(bSize) << endl;
					AddInstruction(PushInt, bSize);
					parseExpression(bOp->getLHS(), true, false, true, true);
					out << "FromStack\r\n";
					AddInstruction(FromStack);
					if (isLtoRValue)
					{
						parseExpression(bOp->getLHS(), false, true, true, true);
					}
				}
				else {
					if (isLtoRValue)
					{
						out << "dup //duplicate value for set\r\n";
						AddInstruction(Dup);
					}
					parseExpression(bOp->getLHS(), false, false, true, true);
				}

				return true;
			}
			if (bOp->getOpcode() == BO_Comma)
			{
				parseExpression(bOp->getLHS());
				parseExpression(bOp->getRHS(), isAddr, isLtoRValue);
				return true;
			}
			if (bOp->getOpcode() == BO_LAnd)
			{
				parseExpression(bOp->getLHS(), false, true);
				if (bOp->getLHS()->getType()->isAnyComplexType())
				{
					ComplexToBoolean(bOp->getLHS()->getType()->isComplexType());
				}
				out << "dup\r\nJumpFalse @" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				AddInstruction(Dup);
				AddInstruction(JumpFalse, bOp->getRHS()->getLocEnd().getRawEncoding());
				parseExpression(bOp->getRHS(), false, true);
				if (bOp->getRHS()->getType()->isAnyComplexType())
				{
					ComplexToBoolean(bOp->getRHS()->getType()->isComplexType());
				}
				out << "and\r\n\r\n:" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				AddInstruction(And);
				AddInstruction(Label, bOp->getRHS()->getLocEnd().getRawEncoding());
				if (!isLtoRValue)
				{
					out << "drop //unused value\r\n";
					AddInstructionComment(Drop, "unused value");
				}
				return true;
			}
			if (bOp->getOpcode() == BO_LOr)
			{
				parseExpression(bOp->getLHS(), false, true);
				if (bOp->getLHS()->getType()->isAnyComplexType())
				{
					ComplexToBoolean(bOp->getLHS()->getType()->isComplexType());
				}
				out << "dup\r\nnot\r\nJumpFalse @" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				AddInstruction(Dup);
				AddInstruction(JumpTrue, bOp->getRHS()->getLocEnd().getRawEncoding());
				parseExpression(bOp->getRHS(), false, true);
				if (bOp->getRHS()->getType()->isAnyComplexType())
				{
					ComplexToBoolean(bOp->getRHS()->getType()->isComplexType());
				}
				out << "or\r\n\r\n:" << bOp->getRHS()->getLocEnd().getRawEncoding() << "\r\n";
				AddInstruction(Or);
				AddInstruction(Label, bOp->getRHS()->getLocEnd().getRawEncoding());
				if (!isLtoRValue)
				{
					out << "drop //unused value\r\n";
					AddInstructionComment(Drop, "unused value");
				}
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
							AddInstruction(PushFloat, 0);
						}
						else
						{
							out << "Push_0\r\n";
							AddInstruction(PushInt, 0);
						}
					}
					parseExpression(bOp->getRHS(), isAddr, true, true);
					if (!bOp->getRHS()->getType()->isAnyComplexType())
					{
						if (bOp->getRHS()->getType()->isFloatingType())
						{
							out << "PushF_0\r\n";
							AddInstruction(PushFloat, 0);
						}
						else
						{
							out << "Push_0\r\n";
							AddInstruction(PushInt, 0);
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
							AddInstruction(SetFrame, index);
							AddInstruction(ItoF);
							AddInstruction(GetFrame, index);
							AddInstruction(ItoF);
							LocalVariables.removeLevel();
						}
					}
					LocalVariables.addLevel();
					int startindex = LocalVariables.addDecl("complex", 4);
					out << "Push_4\r\n" << pFrame(startindex) << "\r\nFromStack\r\n";
					AddInstruction(PushInt, 4);
					AddInstruction(GetFrameP, startindex);
					AddInstruction(FromStack);
					switch (bOp->getOpcode())
					{
						case BO_Add:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}
							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Add //Calc Real Part\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Add //Calc Imag Part\r\n";
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt)
								AddInstruction(FAdd);
							else
								AddInstruction(Add);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt)
								AddInstruction(FAdd);
							else
								AddInstruction(Add);

						}
						break;
						case BO_AddAssign:
						{
							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Add //Calc Real Part\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Add //Calc Imag Part\r\n";
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt)
								AddInstruction(FAdd);
							else
								AddInstruction(Add);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt)
								AddInstruction(FAdd);
							else
								AddInstruction(Add);

							out << "Push_2 //Type Size\r\n";
							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							out << "FromStack\r\n";
							AddInstruction(FromStack);

						}
						goto CheckAssignL2R;

						case BO_Sub:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}
							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Sub //Calc Real Part\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Sub //Calc Imag Part\r\n";
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt)
								AddInstruction(FSub);
							else
								AddInstruction(Sub);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt)
								AddInstruction(FSub);
							else
								AddInstruction(Sub);
						}
						break;
						case BO_SubAssign:
						{
							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Sub //Calc Real Part\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Sub //Calc Imag Part\r\n";
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt)
								AddInstruction(FSub);
							else
								AddInstruction(Sub);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt)
								AddInstruction(FSub);
							else
								AddInstruction(Sub);

							out << "Push_2 //Type Size\r\n";
							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							out << "FromStack\r\n";
							AddInstruction(FromStack);
						}
						goto CheckAssignL2R;

						case BO_Mul:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}
							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mult\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mult\r\n";
							out << isFloat << "Sub //Calc Real Part\r\n";

							out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mult\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mult\r\n";
							out << isFloat << "Add //Calc Imag Part\r\n";

							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt)
								AddInstruction(FMult);
							else
								AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FSub);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Sub);
							}
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt)
								AddInstruction(FMult);
							else
								AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FAdd);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Add);
							}
						}
						break;
						case BO_MulAssign:
						{
							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mult\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mult\r\n";
							out << isFloat << "Sub //Calc Real Part\r\n";

							out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mult\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mult\r\n";
							out << isFloat << "Add //Calc Imag Part\r\n";

							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt)
								AddInstruction(FMult);
							else
								AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FSub);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Sub);
							}
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt)
								AddInstruction(FMult);
							else
								AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FAdd);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Add);
							}

							out << "Push_2 //Type Size\r\n";
							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							out << "FromStack\r\n";
							AddInstruction(FromStack);
						}
						goto CheckAssignL2R;

						case BO_Div:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}
							int divide = LocalVariables.addDecl("divide", 1);
							out << frameGet(startindex + 2) << "\r\nDup\r\n" << isFloat << "Mult\r\n";
							out << frameGet(startindex + 3) << "\r\nDup\r\n" << isFloat << "Mult\r\n";
							out << isFloat << "Add //Calc Comp Denominator\r\n" << frameSet(divide) << endl;

							AddInstruction(GetFrame, startindex + 2);
							AddInstruction(Dup);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 3);
							AddInstruction(Dup);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							if (isFlt) AddInstruction(FAdd);
							else AddInstruction(Add);
							AddInstruction(SetFrame, divide);

							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mult\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mult\r\n";
							out << isFloat << "Add //Calc Real Part\r\n";
							out << frameGet(divide) << endl << isFloat << "Div\r\n";

							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FAdd);
								AddInstruction(GetFrame, divide);
								AddInstruction(FDiv);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Add);
								AddInstruction(GetFrame, divide);
								AddInstruction(Div);
							}
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
							out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
							out << isFloat << "Sub //Calc Imag Part\r\n";
							out << frameGet(startindex + 4) << endl << isFloat << "Div\r\n";

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FSub);
								AddInstruction(GetFrame, divide);
								AddInstruction(FDiv);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Sub);
								AddInstruction(GetFrame, divide);
								AddInstruction(Div);
							}

						}
						break;
						case BO_DivAssign:
						{
							int divide = LocalVariables.addDecl("divide", 1);
							out << frameGet(startindex + 2) << "\r\nDup\r\n" << isFloat << "Mult\r\n";
							out << frameGet(startindex + 3) << "\r\nDup\r\n" << isFloat << "Mult\r\n";
							out << isFloat << "Add //Calc Comp Denominator\r\n" << frameSet(divide) << endl;

							AddInstruction(GetFrame, startindex + 2);
							AddInstruction(Dup);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 3);
							AddInstruction(Dup);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							if (isFlt) AddInstruction(FAdd);
							else AddInstruction(Add);
							AddInstruction(SetFrame, divide);

							out << frameGet(startindex) << endl << frameGet(startindex + 2) << endl << isFloat << "Mult\r\n";
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 3) << endl << isFloat << "Mult\r\n";
							out << isFloat << "Add //Calc Real Part\r\n";
							out << frameGet(divide) << endl << isFloat << "Div\r\n";

							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FAdd);
								AddInstruction(GetFrame, divide);
								AddInstruction(FDiv);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Add);
								AddInstruction(GetFrame, divide);
								AddInstruction(Div);
							}
							out << frameGet(startindex + 1) << endl << frameGet(startindex + 2) << endl << isFloat << "Mul\r\n";
							out << frameGet(startindex) << endl << frameGet(startindex + 3) << endl << isFloat << "Mul\r\n";
							out << isFloat << "Sub //Calc Imag Part\r\n";
							out << frameGet(startindex + 4) << endl << isFloat << "Div\r\n";

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							if (isFlt) AddInstruction(FMult);
							else AddInstruction(Mult);
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);
							if (isFlt) {
								AddInstruction(FMult);
								AddInstruction(FSub);
								AddInstruction(GetFrame, divide);
								AddInstruction(FDiv);
							}
							else {
								AddInstruction(Mult);
								AddInstruction(Sub);
								AddInstruction(GetFrame, divide);
								AddInstruction(Div);
							}

							out << "Push_2 //Type Size\r\n";
							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							out << "FromStack\r\n";
							AddInstruction(FromStack);
						}
						goto CheckAssignL2R;
						default:
						Throw("Unsupported binary operator \"" + bOp->getOpcodeStr().str() + "\" for Complex data type", rewriter, bOp->getOperatorLoc());
						break;
					CheckAssignL2R:
						if (isLtoRValue)
						{
							out << "Push_2 //Type Size\r\n";
							parseExpression(bOp->getLHS(), true);
							out << "ToStack\r\n";
						}
						break;
					}
					LocalVariables.removeLevel();
					return true;
				}
				else
				{
					Throw("Complex binary operations can only be done in functions");
				}

			}


			auto OpAssign = [&](string opStr, bool canValueBeFloat, OpcodeKind opcode, OpcodeKind floatVar = (OpcodeKind)-1)
			{
				bool pointerSet = true;
				if (isa<DeclRefExpr>(bOp->getLHS()))
				{
					const DeclRefExpr *dRef = cast<DeclRefExpr>(bOp->getLHS());
					if (isa<VarDecl>(dRef->getFoundDecl()))
					{
						pointerSet = false;
						parseExpression(bOp->getLHS(), false, true);
					}
				}
				if (pointerSet)
				{
					parseExpression(bOp->getLHS(), true, false);
					out << "dup\r\npGet\r\n";
					AddInstruction(Dup);
					AddInstruction(PGet);
				}
				llvm::APSInt intRes;
				if (bOp->getRHS()->EvaluateAsInt(intRes, *context))
				{
					int64_t val = intRes.getSExtValue();
					if (isa<PointerType>(bOp->getLHS()->getType()))
					{
						const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
						out << iPush(val * getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr)) << endl;
						AddInstruction(PushInt, val * getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr));
						if (bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat)
							out << "f";
						if (pointerSet)
						{
							out << opStr << "\r\npPeekSet\r\n" << (isLtoRValue ? "pGet" : "Drop") << "\r\n";
							AddFloatingOpCheck(bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat, opcode, floatVar);
							AddInstruction(PeekSet);
							AddInstructionCondition(isLtoRValue, PGet, Drop);
						}
						else
						{
							out << opStr << "\r\n";
							AddFloatingOpCheck(bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat, opcode, floatVar);
							if (isLtoRValue)
							{
								AddInstruction(Dup);
								out << "dup\r\n";
							}
							parseExpression(bOp->getLHS(), false, false, false, true);
						}
					}
					else
					{
						out << iPush(val) << endl;
						AddInstruction(PushInt, val);
						if (bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat)
							out << "f";
						if (pointerSet)
						{
							out << opStr << "\r\npPeekSet\r\n" << (isLtoRValue ? "pGet" : "Drop") << "\r\n";
							AddFloatingOpCheck(bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat, opcode, floatVar);
							AddInstruction(PeekSet);
							AddInstructionCondition(isLtoRValue, PGet, Drop);
						}
						else
						{
							out << opStr << "\r\n";
							AddFloatingOpCheck(bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat, opcode, floatVar);
							if (isLtoRValue)
							{
								out << "dup\r\n";
								AddInstruction(Dup);
							}
							parseExpression(bOp->getLHS(), false, false, false, true);
						}
					}
				}
				else
				{
					parseExpression(bOp->getRHS(), false, true);
					if (isa<PointerType>(bOp->getLHS()->getType()))
					{
						const Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
						out << mult(getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr)) + "\r\n";
						AddInstruction(MultImm, getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr));
					}

					if (bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat)
						out << "f";

					if (pointerSet)
					{
						out << opStr << "\r\npPeekSet\r\n" << (isLtoRValue ? "pGet" : "Drop") << "\r\n";
						AddFloatingOpCheck(bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat, opcode, floatVar);
						AddInstruction(PeekSet);
						AddInstructionCondition(isLtoRValue, PGet, Drop);
					}
					else
					{
						out << opStr << "\r\n";
						AddFloatingOpCheck(bOp->getLHS()->getType()->isFloatingType() && canValueBeFloat, opcode, floatVar);
						if (isLtoRValue)
						{
							out << "dup\r\n";
							AddInstruction(Dup);
						}
						parseExpression(bOp->getLHS(), false, false, false, true);
					}
				}

			};

			switch (op) {
				case BO_SubAssign: OpAssign("Sub", true, OK_Sub, OK_FSub); break;
				case BO_AddAssign: OpAssign("Add", true, OK_Add, OK_FAdd); break;
				case BO_DivAssign:  OpAssign("Div", true, OK_Div, OK_FDiv); break;
				case BO_MulAssign:  OpAssign("Mult", true, OK_Mult, OK_FMult); break;
				case BO_OrAssign:  OpAssign("Or", false, OK_Or); break;
				case BO_AndAssign:  OpAssign("And", false, OK_And); break;
				case BO_RemAssign:  OpAssign("Mod", true, OK_Mod, OK_FMod); break;
				case BO_XorAssign:  OpAssign("Xor", false, OK_Xor); break;
				case BO_ShlAssign:	OpAssign("CallNative shift_left 2 1", false, OK_ShiftLeft); break;
				case BO_ShrAssign: OpAssign("CallNative shift_right 2 1", false, OK_ShiftRight); break;
				default:
				{

					//c allows same type pointer to pointer subtraction to obtain the logical difference. 
					if (isa<PointerType>(bOp->getLHS()->getType()) && isa<PointerType>(bOp->getRHS()->getType()))
					{
						parseExpression(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
						parseExpression(bOp->getRHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);

						if (op == BO_Sub)
						{
							const Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
							int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
							int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

							if (bOp->getLHS()->getType()->isFloatingType())
								out << "fSub\r\n";
							else
								out << "Sub\r\n";
							AddInstructionCondition(bOp->getLHS()->getType()->isFloatingType(), FSub, Sub);

							if (pSize > 1)
							{
								out << div(pSize) << "\r\n";
								AddInstruction(PushInt, pSize);
								AddInstruction(Div);
							}


							if (!isLtoRValue) {
								Warn("Unused operator \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());
								out << "Drop" << endl;
								AddInstruction(Drop);
							}
							return -1;
						}
					}
					else if (isa<PointerType>(bOp->getLHS()->getType()))
					{
						//we need to parse left as an addr if its an array else its a pointer val
						parseExpression(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
						parseExpression(bOp->getRHS(), false, true);

						if (op == BO_Add || op == BO_Sub)
						{
							const Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
							int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
							int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

							if (pSize > 1)
								out << mult(pSize) << endl;
							AddInstructionConditionally(pSize > 1, MultImm, pSize);
						}
					}
					else if (isa<PointerType>(bOp->getRHS()->getType()))
					{
						//we need to parse right as an addr if its an array else its a pointer val
						parseExpression(bOp->getLHS(), false, true);

						if (op == BO_Add || op == BO_Sub)
						{
							const Type* pTypePtr = bOp->getRHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
							int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
							int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

							if (pSize > 1)
								out << mult(pSize) << endl;
							AddInstructionConditionally(pSize > 1, MultImm, pSize);
						}

						parseExpression(bOp->getRHS(), bOp->getRHS()->getType().getTypePtr()->isArrayType(), true);
					}
					else
					{
						//no pointer operations
						parseExpression(bOp->getLHS(), false, true);
						parseExpression(bOp->getRHS(), false, true);
					}

					if (bOp->getLHS()->getType()->isFloatingType()) {
						switch (op) {
							case BO_EQ: out << "fCmpEQ\r\n"; AddInstruction(FCmpEq); break;
							case BO_Mul: out << "fMult\r\n"; AddInstruction(FMult); break;
							case BO_Div: out << "fDiv\r\n"; AddInstruction(FDiv); break;
							case BO_Rem: out << "fMod\r\n"; AddInstruction(FMod); break;
							case BO_Sub: out << "fSub\r\n"; AddInstruction(FSub); break;
							case BO_LT: out << "fCmpLT\r\n"; AddInstruction(FCmpLt); break;
							case BO_GT: out << "fCmpGT\r\n"; AddInstruction(FCmpGt); break;
							case BO_GE: out << "fCmpGE\r\n"; AddInstruction(FCmpGe); break;
							case BO_LE: out << "fCmpLE\r\n"; AddInstruction(FCmpLe); break;
							case BO_NE: out << "fCmpNE\r\n"; AddInstruction(FCmpNe); break;
							case BO_LAnd: out << "And\r\n"; AddInstruction(And); break;//needs changing
							case BO_Add: out << "fAdd\r\n"; AddInstruction(FAdd); break;
							case BO_LOr: out << "Or\r\n"; AddInstruction(Or); break;//needs changing

							default:
							Throw("Unimplemented binary floating op " + bOp->getOpcodeStr().str(), rewriter, bOp->getExprLoc());
						}
					}
					else {
						switch (op) {
							case BO_EQ: out << "CmpEQ\r\n"; AddInstruction(CmpEq); break;
							case BO_Mul: out << "Mult\r\n"; AddInstruction(Mult); break;
							case BO_Div: out << "Div\r\n"; AddInstruction(Div); break;
							case BO_Rem: out << "Mod\r\n"; AddInstruction(Mod); break;
							case BO_Sub: out << "Sub\r\n"; AddInstruction(Sub); break;
							case BO_LT: out << "CmpLT\r\n"; AddInstruction(CmpLt); break;
							case BO_GT: out << "CmpGT\r\n"; AddInstruction(CmpGt); break;
							case BO_GE: out << "CmpGE\r\n"; AddInstruction(CmpGe); break;
							case BO_LE: out << "CmpLE\r\n"; AddInstruction(CmpLe); break;
							case BO_NE: out << "CmpNE\r\n"; AddInstruction(CmpNe); break;
							case BO_LAnd://needs changing
							case BO_And: out << "And\r\n"; AddInstruction(And); break;
							case BO_Xor: out << "Xor\r\n"; AddInstruction(Xor); break;
							case BO_Add: out << "Add\r\n"; AddInstruction(Add); break;
							case BO_LOr://needs changing
							case BO_Or: out << "Or\r\n"; AddInstruction(Or); break;
							case BO_Shl: out << "CallNative shift_left 2 1\r\n"; AddInstruction(ShiftLeft); break;
							case BO_Shr: out << "CallNative shift_right 2 1\r\n"; AddInstruction(ShiftRight); break;
							default:
							Throw("Unimplemented binary op " + bOp->getOpcodeStr().str(), rewriter, bOp->getExprLoc());
						}
					}

					if (!isLtoRValue) {

						Warn("Unused operator \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());
						out << "Drop" << endl;
						AddInstruction(Drop);
					}
				}

			}
		}
		else if (isa<MemberExpr>(e)) {
			const MemberExpr *E = cast<const MemberExpr>(e);
			Expr *BaseExpr = E->getBase();


			if (E->isArrow()) {
				parseExpression(BaseExpr, false, true);
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
				AddInstructionComment(AddImm, "." + ND->getName().str(), size * 4);
			}
			else
			{
				out << "// ." << ND->getName().str() << "\r\n";
			}


			if (isLtoRValue)
			{
				out << "pGet\r\n";
				AddInstruction(PGet);
			}
			else if (isAddr)
			{
				return 1;
			}
			else
			{
				out << "pSet\r\n";
				AddInstruction(PSet);
			}

			return 1;
		}
		else if (isa<InitListExpr>(e))
		{
			//{ 1, 3, 7 }; support
			const InitListExpr *I = cast<const InitListExpr>(e);
			if (I->getType()->isArrayType())
			{
				switch (getSizeOfType(I->getType()->getArrayElementTypeNoTypeQual()))
				{
				case 1:
				{
					int initCount = I->getNumInits();
					int i;
					for(i = 0; i < initCount; i += 4)
					{
						llvm::APSInt res;
						int evaluated[4];
						const Expr* inits[4];
						bool allconst = true;
						bool succ[4];
						for(int j = 0; j < 4; j++)
						{
							if(i + j < initCount)
							{
								inits[j] = I->getInit(i + j);
								if((succ[j] = inits[j]->EvaluateAsInt(res, *context)))
								{
									evaluated[j] = res.getSExtValue() & 0xFF;
								}
								else
								{
									allconst = false;
								}
							}
							else
							{
								succ[j] = true;
								evaluated[j] = 0;
							}

						}
						if(allconst)
						{
							int val = (evaluated[0] << 24) | (evaluated[1] << 16) | (evaluated[2] << 8) | (evaluated[3]);
							out << iPush(val) << endl;
							AddInstruction(PushInt, val);
						}
						else
						{
							if(succ[0])
							{
								out << iPush(evaluated[0] << 24) << endl;
								AddInstruction(PushInt, evaluated[0] << 24);

							}
							else
							{
								parseExpression(I->getInit(i), false, true);
								out << "PushB 255\r\nAnd\r\nPushB 24\r\nCallNative shift_left 2 1\r\n";
								AddInstruction(PushInt, 24);
								AddInstruction(ShiftLeft);
								AddInstruction(PushInt, 255);
								AddInstruction(And);
							}
							for(int j = 1; j < 4; j++)
							{
								if(i + j >= initCount)
									break;
								if(succ[j])
								{
									out << iPush(evaluated[j] << ((3 - j) << 3)) << "\r\nOr\r\n";
									AddInstruction(PushInt, evaluated[j] << ((3-j) << 3));
									AddInstruction(Or);
								}
								else
								{
									parseExpression(I->getInit(i + j), false, true);
									out << "PushB 255\r\nAnd\r\nPushB " << ((3 - j) << 3) << "\r\nCallNative shift_left 2 1\r\nOr\r\n";
									AddInstruction(PushInt, 255);
									AddInstruction(And);
									if(j != 3)
									{
										AddInstruction(PushInt, (3 - j) << 3);
										AddInstruction(ShiftLeft);
									}
									AddInstruction(Or);
								}

							}
						}
					}
					int size = getSizeOfType(I->getType().getTypePtr());
					while (i < size)
					{
						out << iPush(0) << endl;
						AddInstruction(PushInt, 0);
						i += 4;
					}
				}
					return 1;
				case 2:
				{
					int initCount = I->getNumInits();
					int i;
					for(i = 0; i < initCount; i += 2)
					{
						llvm::APSInt res;
						int evaluated[2];
						const Expr* inits[2];
						bool allconst = true;
						bool succ[2];
						for(int j = 0; j < 2; j++)
						{
							if(i + j < initCount)
							{
								inits[j] = I->getInit(i + j);
								if((succ[j] = inits[j]->EvaluateAsInt(res, *context)))
								{
									evaluated[j] = res.getSExtValue() & 0xFFFF;
								}
								else
								{
									allconst = false;
								}
							}
							else
							{
								succ[j] = true;
								evaluated[j] = 0;
							}

						}
						if(allconst)
						{
							int val = (evaluated[0] << 16) | (evaluated[1]);
							out << iPush(val) << endl;
							AddInstruction(PushInt, val);
						}
						else
						{
							if(succ[0])
							{
								out << iPush(evaluated[0] << 16) << endl;
								AddInstruction(PushInt, evaluated[0] << 16);

							}
							else
							{
								parseExpression(I->getInit(i), false, true);
								out << "PushI24 65535\r\nAnd\r\nPushB 16\r\nCallNative shift_left 2 1\r\n";
								AddInstruction(PushInt, 65535);
								AddInstruction(And);
								AddInstruction(PushInt, 16);
								AddInstruction(ShiftLeft);
							}
							if(i + 1 < initCount)
							{
								if(succ[1])
								{
									out << iPush(evaluated[1]) << "\r\nOr\r\n";
									AddInstruction(PushInt, evaluated[1]);
									AddInstruction(Or);
								}
								else
								{
									parseExpression(I->getInit(i + 1), false, true);
									out << "PushI24 65535\r\nAnd\r\nOr\r\n";
									AddInstruction(PushInt, 65535);
									AddInstruction(And);
									AddInstruction(Or);
								}
							}
						}
					}
					int size = getSizeOfType(I->getType().getTypePtr());
					int curSize = getSizeFromBytes(i * 2) * 4;
					while(curSize < size)
					{
						out << iPush(0) << endl;
						AddInstruction(PushInt, 0);
						curSize += 4;
					}
				}
				return 1;
				}
			}
			int size = getSizeOfType(I->getType().getTypePtr());
			int curSize = 0;
			for (unsigned int i = 0; i < I->getNumInits(); i++)
			{
				const Expr *init = I->getInit(i);
				curSize += 4 * getSizeFromBytes(getSizeOfType(init->getType().getTypePtr()));
				parseExpression(init, false, true);
			}
			while (curSize < size)
			{
				out << iPush(0) << endl;
				AddInstruction(PushInt, 0);
				curSize += 4;
			}
				
		}
		else if (isa<ImplicitValueInitExpr>(e))
		{
			const ImplicitValueInitExpr *im = cast<const ImplicitValueInitExpr>(e);
			uint32_t size = getSizeFromBytes(getSizeOfType(im->getType().getTypePtr()));
			for (uint32_t i = 0; i < size; i++)
			{
				out << "Push_0" << endl;
				AddInstruction(PushInt, 0);
			}
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
					AddInstructionConditionally(isLtoRValue, PushInt, size);

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
							AddInstructionComment(PushInt, "Joaat(\"" + str + "\")", Utils::Hashing::Joaat((char*)str.c_str()));
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

			parseJumpFalseCondition(cond->getCond(), to_string(cond->getRHS()->getLocStart().getRawEncoding()));
			out << endl;
			parseExpression(cond->getLHS(), false, true);
			out << "Jump @" << cond->getLHS()->getLocEnd().getRawEncoding() << endl;
			AddInstruction(Jump, cond->getLHS()->getLocEnd().getRawEncoding());

			out << ":" << cond->getRHS()->getLocStart().getRawEncoding() << endl;
			AddInstruction(Label, cond->getRHS()->getLocStart().getRawEncoding());
			parseExpression(cond->getRHS(), false, true);
			out << ":" << cond->getLHS()->getLocEnd().getRawEncoding() << endl;
			AddInstruction(Label, cond->getLHS()->getLocEnd().getRawEncoding());
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

	bool parseArraySubscriptExpr(const Expr *e, bool addrOf, bool LValueToRValue = false) {
		const ArraySubscriptExpr *arr = cast<const ArraySubscriptExpr>(e);
		const Expr *base = arr->getBase();
		const Expr *index = arr->getIdx();

		llvm::APSInt evalIndex;
		bool isCst = index->EvaluateAsInt(evalIndex, *context);

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
				AddInstruction(PushInt, 256);
				AddInstruction(Mod);
				AddInstruction(PushInt, 24);
				AddInstruction(ShiftLeft);
				parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);
				if (isCst)
				{
					int iRes = evalIndex.getSExtValue();
					if(iRes != 0)
					{
						out << add(iRes) << endl;
						AddInstruction(AddImm, iRes);
					}
				}
				else
				{
					parseExpression(index, false, true);
					out << "Add\r\n";
					AddInstruction(Add);
				}
				out << "pGet\r\nPushI24 0xFFFFFF\r\nand\r\nor\r\n";
				AddInstruction(PGet);
				AddInstruction(PushInt, 0xFFFFFF);
				AddInstruction(And);
				AddInstruction(Or);
			}
			//2 byte indexing
			else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
			{
				//mod for narrowing conversion
				out << "Pushi24 65536\r\nMod\r\nPushB 16\r\nCallNative shift_left 2 1\r\n";
				AddInstruction(PushInt, 65536);
				AddInstruction(Mod);
				AddInstruction(PushInt, 16);
				AddInstruction(ShiftLeft);
				parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);
				if(isCst)
				{
					int iRes = evalIndex.getSExtValue();
					if(iRes != 0)
					{
						out << add(iRes*2) << endl;
						AddInstruction(AddImm, iRes*2);
					}
				}
				else
				{
					parseExpression(index, false, true);
					out << mult(2) << "\r\nAdd\r\n";
					AddInstruction(MultImm, 2);
					AddInstruction(Add);
				}
				out << "pGet\r\nPushI24 0xFFFF\r\nand\r\nor\r\n";
				AddInstruction(PGet);
				AddInstruction(PushInt, 0xFFFF);
				AddInstruction(And);
				AddInstruction(Or);
			}
		}


		parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);


		if (LValueToRValue && !addrOf)
		{
			if(isCst)
			{
				int iRes = evalIndex.getSExtValue();
				if(iRes != 0)
				{
					out << add(iRes * getSizeOfType(type)) << endl;
					AddInstruction(AddImm, iRes * getSizeOfType(type));
				}
			}
			else
			{
				parseExpression(index, false, true);
				int size = getSizeOfType(type);
				if (size > 1)
				{
					out << mult(size) << endl;
					AddInstruction(MultImm, size);
				}
				out << "Add\r\n";
				AddInstruction(Add);
			}
			out << "pGet//GetArray2\r\n";
			AddInstruction(PGet);
			//1 byte indexing
			if (type->isCharType())
			{
				out << "PushB 24\r\nCallNative shift_right 2 1\r\n";
				AddInstruction(PushInt, 24);
				AddInstruction(ShiftRight);
			}
			//2 byte indexing
			else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
			{
				out << "PushB 16\r\nCallNative shift_right 2 1\r\n";
				AddInstruction(PushInt, 16);
				AddInstruction(ShiftRight);
				if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short))
				{
					out << iPush(1 << 15) << "\r\nAnd\r\nJumpFalse @" << arr->getLocEnd().getRawEncoding()
						<< "\r\n" << iPush(0xFFFF0000) << "\r\nOr //ExtSignWord\r\n\r\n:" << arr->getLocEnd().getRawEncoding() << endl;
					AddInstruction(IsBitSet, 15);
					AddInstruction(JumpFalse, arr->getLocEnd().getRawEncoding());
					AddInstruction(PushInt, 0xFFFF0000);
					AddInstructionComment(Or, "ExtSignWord");
					AddInstruction(Label, arr->getLocEnd().getRawEncoding());
				}
			}

		}
		else if (addrOf)
		{
			int size = getSizeOfType(type);
			if (type->isArrayType())
				size = getSizeFromBytes(size) * 4;
			if(isCst)
			{
				int iRes = evalIndex.getSExtValue();
				if(iRes != 0)
				{
					out << add(iRes * size) << endl;
					AddInstruction(AddImm, iRes * size);
				}
			}
			else
			{
				parseExpression(index, false, true);
				if(size > 1)
				{
					out << mult(size) << endl;
					AddInstruction(MultImm, size);
				}
				out << "Add//GetArrayP2\r\n";
				AddInstruction(Add);
			}
		}
		else
		{
			if(isCst)
			{
				int iRes = evalIndex.getSExtValue();
				if(iRes != 0)
				{
					out << add(iRes * getSizeOfType(type)) << endl;
					AddInstruction(AddImm, iRes * getSizeOfType(type));
				}
			}
			else
			{
				parseExpression(index, false, true);
				int size = getSizeOfType(type);
				if(size > 1)
				{
					out << mult(size) << endl;
					AddInstruction(MultImm, size);
				}
				out << "Add\r\n";
				AddInstruction(Add);
			}
			out << "pSet//SetArray2\r\n";
			AddInstructionComment(PSet, "SetArray2");
		}


		return true;
	}

	bool VisitFunctionDecl(FunctionDecl *f) {
		// Only function definitions (with bodies), not declarations.
		//int funcNum = 0;
		if (f->hasBody()) {
			if (f->hasAttr<NativeFuncAttr>())
			{
				Throw("Native function attribute cannot be used on functions which have a body declared", rewriter, f->getAttr<NativeFuncAttr>()->getRange());
			}
			else if (f->hasAttr<IntrinsicFuncAttr>())
			{
				Throw("Intrinsic function attribute cannot be used on functions which have a body declared", rewriter, f->getAttr<IntrinsicFuncAttr>()->getRange());
			}
			out.seekg(0, ios::end);
			string name2 = f->getNameAsString();
			{
				uint32_t hash = Utils::Hashing::JoaatCased((char*)getNameForFunc(f).c_str());
				size_t i;
				for (i = 0; i < functions.size(); i++)
				{
					if (functions[i].hash == hash)
					{
						if (functions[i].name == getNameForFunc(f))
						{
							bool used = functions[i].isused;
							functions.erase(functions.begin() + i);
							functions.push_back({ Utils::Hashing::JoaatCased((char*)getNameForFunc(f).c_str()) , getNameForFunc(f), used, out.tellg() });
							break;
						}
					}
				}
				if (i == functions.size())
				{
					functions.push_back({ Utils::Hashing::JoaatCased((char*)getNameForFunc(f).c_str()) , getNameForFunc(f), false, out.tellg() });
				}
			}



			if (isa<CXXConstructorDecl>(f))
				return true;

			Stmt *FuncBody = f->getBody();

			int32_t paramSize = 0;
			for (uint32_t i = 0; i<f->getNumParams(); i++)
				paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
			{
				uint32_t hash = Utils::Hashing::JoaatCased((char*)getNameForFunc(f).c_str());
				size_t i;
				for(i = 0; i < functionsNew.size(); i++)
				{
					if(functionsNew[i]->Hash() == hash)
					{
						if(functionsNew[i]->Name() == getNameForFunc(f))
						{
							CurrentFunction = functionsNew[i];
							break;
						}
					}
				}
				if(i == functionsNew.size())
				{
					functionsNew.push_back(new FunctionData(getNameForFunc(f), (paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0))));
					CurrentFunction = functionsNew.back();
				}
			}
			out << endl << "//Loc: " << f->getBody()->getLocStart().getRawEncoding() << endl;
			string name = dumpName(cast<NamedDecl>(f));
			out << ":" << name << endl;//no need for addinstruction, FunctionData handles this

			if (f->isMain())
			{
				functions.back().isused = true;
				Entryfunction.addUsedFunc(CurrentFunction);
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
				if (!CurrentFunction->endsWithReturn())
					AddInstruction(Return, paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0), 0);
			}
			else if (f->hasImplicitReturnZero())
			{
				int32_t paramSize = 0;
				for (uint32_t i = 0; i < f->getNumParams(); i++) {
					paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
				}
				out << "Push_0\r\n";
				out << "Return " << paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0) << " 1\r\n";
				AddInstruction(PushInt, 0);
				AddInstruction(Return, paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0), 1);
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
				functionsNew.back()->setStackSize(FunctionStackCount);
			}
			//out << dumpName(cast<NamedDecl>(f)) << endl;

			//outfile << out.str();
			//out.str(string(""));
			//out.clear();
			CurrentFunction = NULL;
		}
		else
		{
			string name = f->getNameAsString();
			if (f->getStorageClass() == SC_None)
			{
				//prototype detected, add it to the functions list(s), 
				out.seekg(0, ios::end);
				functions.push_back({ Utils::Hashing::JoaatCased((char*)getNameForFunc(f).c_str()), getNameForFunc(f), false, out.tellg() });

				int32_t paramSize = 0;
				for (uint32_t i = 0; i<f->getNumParams(); i++)
					paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
				functionsNew.push_back(new FunctionData(getNameForFunc(f), (paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0))));
			}
		}

		return true;
	}
	#pragma endregion

	#pragma region CXX_Functions
	uint32_t getCXXOffsetOfNamedDecl(const CXXRecordDecl *classDecl, const NamedDecl *ND, const CXXRecordDecl *prevDecl = NULL) {
		bool found = false;
		//bool foundVirt = false;
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

	uint32_t printVirtualCall(const CXXRecordDecl *classDecl, const CXXMethodDecl *method, Expr *baseExpr, const CXXRecordDecl *superDecl = NULL) {
		//int offset = 0;


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

				//const CXXMethodDecl *VFII = VFI->getCorrespondingMethodInClass(superDecl);
				if (VFI->getName() == method->getName()) { //getLocStart(VFI) != getLocStart(VFII)) {

														   //out << "push " << func << endl;
					parseExpression(baseExpr);
					out << endl << "dup" << endl << GetImm(getSizeFromBytes(getSizeOfCXXDecl(superDecl, false, true, classDecl)) + vtableInc) << " //" << classDecl->getDeclName().getAsString() << "::VTablePtr[" << getSizeFromBytes(getSizeOfCXXDecl(superDecl, false, true, classDecl)) + vtableInc << "]" << endl;
					out << GetImm(func) << " //VTable[" << func << "] //" << getNameForFunc(method) << endl;
					out << "pcall" << " //(*)(" << getNameForFunc(method) << "());" << endl;
					AddInstruction(Dup);
					AddInstruction(GetImm, getSizeFromBytes(getSizeOfCXXDecl(superDecl, false, true, classDecl)) + vtableInc);
					AddInstruction(GetImm, func);
					AddInstruction(PCall);


				}
				func++;
				// }

			}

		}
		return getSizeOfVTable(classDecl);


	}

	uint32_t printVTableInit(const CXXRecordDecl *classDecl, const NamedDecl *classLoc) {
		//int offset = 0;


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
						AddInstruction(GetFrame, 0);
						AddInstruction(GetImmP, size + vtableInc);
						AddInstruction(GetFrame, 0);
						AddInstruction(SetImm, sizeBase);

					}





					const CXXMethodDecl *VFII = VFI->getCorrespondingMethodInClass(classDecl);

					if (VFI != VFII) { //getLocStart(VFI) != getLocStart(VFII)) {
									   //const Stmt *body = VFII->FunctionDecl::getBody();

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
	#pragma endregion

public:
	int32_t MainRets = -1;
	set<std::string> FindBuffer;
	Rewriter &TheRewriter;
	ASTContext *context;

	stringstream out;
	string outfile;
	const FunctionDecl *currFunction;
};

#pragma region GlobalsVisitor
class GlobalsVisitor : public RecursiveASTVisitor<GlobalsVisitor> {
public:
	GlobalsVisitor(Rewriter &R, ASTContext *context) : TheRewriter(R), context(context) {}

	int32_t ParseLiteral(const Expr *e, bool isAddr = false, bool isLtoRValue = false)
	{
		Expr::EvalResult result;

		if (isa<ImplicitValueInitExpr>(e))
		{
			const ImplicitValueInitExpr *ivie = cast<const ImplicitValueInitExpr>(e);

			const Type* type = ivie->getType().getTypePtr();
			uint32_t size = getSizeFromBytes(getSizeOfType(type));

			#if STATIC_PADDING_DEBUG == 0
			oldStaticInc += size;
			#else
			for (uint32_t i = 0; i < size; i++)
				DefaultStaticValues.insert({ oldStaticInc++, "0" });
			#endif
			return true;
		}
		else if (e->EvaluateAsRValue(result, *context))
		{

			if (result.Val.isInt())
			{
				if (!isLtoRValue)
					return -1;

				int64_t resValue = result.Val.getInt().getSExtValue();

				if (doesInt64FitIntoInt32(resValue))
				{
					string value = to_string(resValue);
					Warn("Integer overflow. Value: " + value + " is out of bounds of (-2,147,483,648 to 2,147,483,647). Changed value to " + to_string((int32_t)resValue), rewriter, e->getExprLoc(), e->getExprLoc().getLocWithOffset(value.length() - 1));
				}
				const Type* typeE = e->getType().getTypePtr();
				const Type* type = typeE;//globalVarDecl->getType().getTypePtr();

				if (savedType == nullptr)
					savedType = const_cast<Type*>(type);
				else if (type != savedType)
				{
					resetIntIndex();
					savedType = const_cast<Type*>(type);
				}

				if (type->isCharType())
				{
					if (intIndex == 0)
						DefaultStaticValues.insert({ oldStaticInc, "0x00000000" });

					char buffer[10] = { '0' };
					itoa(static_cast<char>(resValue), buffer + 1, 16);

					assert(intIndex < 4 && intIndex >= 0);
					uint32_t len = strlen(buffer + 1);
					assert(len > 0 && len <= 2);
					memcpy(const_cast<void*>(static_cast<const void*>(DefaultStaticValues[oldStaticInc].data() + 2 + intIndex * 2)), buffer + len - 1, 2);

					if (++intIndex >= 4)
					{
						intIndex = 0;
						oldStaticInc++;
					}
				}
				else if (type->isSpecificBuiltinType(BuiltinType::Kind::Short) || type->isSpecificBuiltinType(BuiltinType::Kind::UShort))
				{
					if (intIndex == 0)
						DefaultStaticValues.insert({ oldStaticInc, "0x00000000" });

					char buffer[12] = { '0','0','0' };
					itoa(static_cast<short>(resValue), buffer + 3, 16);
					assert(intIndex < 4 && intIndex >= 0);
					uint32_t len = strlen(buffer + 3);
					assert(len > 0 && len <= 4);
					memcpy(const_cast<void*>(static_cast<const void*>(DefaultStaticValues[oldStaticInc].data() + 2 + intIndex * 2)), buffer + len - 1, 4);

					intIndex += 2;
					if (intIndex >= 4)
					{
						intIndex = 0;
						oldStaticInc++;
					}
				}
				else
					DefaultStaticValues.insert({ oldStaticInc++, to_string((int32_t)resValue) });



				return true;
			}
			else if (result.Val.isFloat())
			{
				if (!isLtoRValue)
					return -1;
				DefaultStaticValues.insert({ oldStaticInc++, to_string(FloatToInt((float)extractAPFloat(result.Val.getFloat()))) });
				return true;
			}
			else if (result.Val.isComplexFloat())
			{
				if (!isLtoRValue)
					return -1;
				DefaultStaticValues.insert({ oldStaticInc++, to_string(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatReal()))) });
				DefaultStaticValues.insert({ oldStaticInc++, to_string(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatImag()))) });
				return true;
			}
			else if (result.Val.isComplexInt())
			{
				if (!isLtoRValue)
					return -1;
				DefaultStaticValues.insert({ oldStaticInc++, to_string(result.Val.getComplexIntReal().getSExtValue()) });
				DefaultStaticValues.insert({ oldStaticInc++, to_string(result.Val.getComplexIntImag().getSExtValue()) });
				return true;
			}
		}

		if (isa<StringLiteral>(e)) {
			const StringLiteral *literal = cast<const StringLiteral>(e);
			if (literal->getString().str().length() > 0)
			{
				string strlit = literal->getString().str();
				e->getType().getTypePtr();

				int32_t strsize = getLiteralSizeOfType(e->getType().getTypePtr());

				int32_t buffer = 0;
				int32_t i = 0, b = 0;
				for (; i < strsize; i++, b++)
				{
					if (b >= 4)
					{
						DefaultStaticValues.insert({ oldStaticInc++, to_string(Utils::Bitwise::SwapEndian(buffer)) });
						b = 0;
						buffer = 0;

#if STATIC_PADDING_DEBUG == 0
						if (i >= (int32_t)strlit.length())
						{
							oldStaticInc += Utils::Math::CeilDivInt(strsize - i, 4);
							break;
						}
#endif
					}
					if (i >= (int32_t)strlit.length())
						((uint8_t*)&buffer)[b] = 0;//add padding
					else
						((uint8_t*)&buffer)[b] = strlit[i];

				}
				if (b != 0)
					DefaultStaticValues.insert({ oldStaticInc++, to_string(Utils::Bitwise::SwapEndian(buffer)) });

			}

			return true;
		}
		else if (isa<InitListExpr>(e))
		{
			const InitListExpr *I = cast<const InitListExpr>(e);
			uint32_t size = getSizeFromBytes(getSizeOfType(I->getType().getTypePtr()));
			uint32_t SavedStaticInc = oldStaticInc;

			resetIntIndex();

			for (uint32_t i = 0; i < I->getNumInits(); i++)
				ParseLiteral(I->getInit(i), false, true);

			resetIntIndex();

			if (oldStaticInc - SavedStaticInc < size)
			{
				cout << "init list size is less adding " << size - (oldStaticInc - SavedStaticInc) << " size: " << size << endl;

				#if STATIC_PADDING_DEBUG == 0
				oldStaticInc += size - (oldStaticInc - SavedStaticInc);
				#else
				uint32_t temp = size - (oldStaticInc - SavedStaticInc);
				for (uint32_t i = 0; i < temp; i++)
					DefaultStaticValues.insert({ oldStaticInc++, "0ie added " + to_string(temp) });
				#endif
			}
			return true;
		}
		else if (isa<ImplicitCastExpr>(e))
		{
			const ImplicitCastExpr *icast = cast<const ImplicitCastExpr>(e);

			switch (icast->getCastKind())
			{
				case CK_ArrayToPointerDecay://char* x = "hello";
				if (isa<StringLiteral>(icast->getSubExpr()))
				{
					const StringLiteral *literal = cast<const StringLiteral>(icast->getSubExpr());
					Entryfunction.addOpPushString(literal->getString().str());
					Entryfunction.addOpSetStatic(oldStaticInc);
					if (literal->getString().str().length() > 0)
						RuntimeStatics << "PushString \"" << literal->getString().str() << "\"\r\n";
					else
						RuntimeStatics << "PushString \"\"\r\n";

					RuntimeStatics << setStatic(oldStaticInc++) << endl;
					
				}
				else if (isa<DeclRefExpr>(icast->getSubExpr()))//int vstack[10] = {1,2,3,4,5,6,7,8,9,10}, *vstack_ptr = vstack;
				{
					const DeclRefExpr *DRE = cast<const DeclRefExpr>(icast->getSubExpr());

					//we can index because the name has to be declared in clang to use the declare
					//we will let clang handle errors
					Entryfunction.addOpGetStaticP(statics[DRE->getDecl()->getNameAsString()]);
					Entryfunction.addOpSetStatic(oldStaticInc);
					RuntimeStatics
						<< getStaticp(statics[DRE->getDecl()->getNameAsString()]) << endl
						<< setStatic(oldStaticInc++) << endl;
				}
				else// need to test byte* t = {1,2,3};
					Throw("Unimplemented CK_ArrayToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()), rewriter, icast->getSubExpr()->getExprLoc());
				break;

				case CK_FunctionToPointerDecay://int (*ggg)(int, float) = test; // test is a function
				if (isa<DeclRefExpr>(icast->getSubExpr())) {
					const DeclRefExpr *declRef = cast<const DeclRefExpr>(icast->getSubExpr());
					if (isa<FunctionDecl>(declRef->getDecl())) {
						const FunctionDecl *decl = cast<const FunctionDecl>(declRef->getDecl());

						string name = "@" + decl->getNameAsString();
						uint32_t hash = Utils::Hashing::JoaatCased(const_cast<char*>(name.c_str()));
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
						for (uint32_t j = 0; j < functionsNew.size(); j++)
						{
							if (functionsNew[j]->Hash() == hash)
							{
								if (functionsNew[j]->Name() == name)
								{
									Entryfunction.addUsedFunc(functionsNew[i]);
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
				else
					Throw("Unimplemented CK_FunctionToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()));
				break;

				default:
				Throw("Unimplemented ImplicitCastExpr of type " + string(icast->getCastKindName()));
			}


		}

		//need to add full pointer init support for 
		//ex:  int vstack[10] = {1,2,3,4,5,6,7,8,9,10};
		//int* vstack_ptr = vstack + 4; //or
		//int* vstack_ptr2 = &vstack[1]; //ect
		//this will require these function below and more for parseing unevaluable expressions

		else if (isa<UnaryOperator>(e)) {
			const UnaryOperator *op = cast<const UnaryOperator>(e);

			Expr *subE = op->getSubExpr();
			if (op->getOpcode() == UO_AddrOf) {
				if (isa<ArraySubscriptExpr>(subE)) {
					const ArraySubscriptExpr* arr = cast<ArraySubscriptExpr>(subE);
					const Expr* base = arr->getBase();
					const Type* type = base->getType().getTypePtr();
					if(isa<ImplicitCastExpr>(base) && cast<ImplicitCastExpr>(base)->getCastKind() == CK_ArrayToPointerDecay)
					{
						base = cast<ImplicitCastExpr>(base)->getSubExpr();
						if(isa<DeclRefExpr>(base))
						{
							const DeclRefExpr* DRE = cast<DeclRefExpr>(base);
							llvm::APSInt iResult;
							if(arr->getIdx()->EvaluateAsInt(iResult, *context))
							{
								int size = getSizeOfType(type);
								if(type->isArrayType())
									size = getSizeFromBytes(size) * 4;
								Entryfunction.addOpGetStaticP(statics[DRE->getDecl()->getNameAsString()]);
								Entryfunction.addOpAddImm(size * iResult.getSExtValue());
								Entryfunction.addOpSetStatic(oldStaticInc);
								RuntimeStatics
									<< getStaticp(statics[DRE->getDecl()->getNameAsString()]) << endl << add(size * iResult.getSExtValue()) << endl
									<< setStatic(oldStaticInc++) << endl;

							}
							else
							{
								Throw("Expected integer literal for static array pointer initialisation", rewriter, op->getSourceRange());
							}
						}
						else
						{
							Throw("Expected static declaration for static array pointer initialisation", rewriter, op->getSourceRange());
						}
					}
					else
					{
						Throw("Expected static declaration for static array pointer initialisation", rewriter, op->getSourceRange());
					}
					

				}
				else if (isa<DeclRefExpr>(subE)) {
					const DeclRefExpr *DRE = cast<const DeclRefExpr>(subE);

					//we can index because the name has to be declared in clang to use the declare
					//we will let clang handle errors
					Entryfunction.addOpGetStaticP(statics[DRE->getDecl()->getNameAsString()]);
					Entryfunction.addOpSetStatic(oldStaticInc);
					RuntimeStatics
						<< getStaticp(statics[DRE->getDecl()->getNameAsString()]) << endl
						<< setStatic(oldStaticInc++) << endl;
				}
				else {
					ParseLiteral(subE, true, false);
				}
				return  true;

			}


		}
		else if (isa<CompoundLiteralExpr>(e)) {
			Throw("COL", rewriter, e->getExprLoc());
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
		else if (isa<CastExpr>(e)) {
			Throw("CE", rewriter, e->getExprLoc());
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
					ParseLiteral(icast->getSubExpr(), isAddr, true);
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
				case clang::CK_PointerToBoolean:
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
			Throw("ASE", rewriter, e->getExprLoc());
			Throw("parseArraySubscriptExpr", rewriter, e->getExprLoc());
			//return parseArraySubscriptExpr(e, isAddr, isLtoRValue);
		}
		else if (isa<ParenExpr>(e)) {
			Throw("PE", rewriter, e->getExprLoc());
			const ParenExpr *parenExpr = cast<const ParenExpr>(e);
			ParseLiteral(parenExpr->getSubExpr(), isAddr, isLtoRValue);
		}
		else if (isa<BinaryOperator>(e)) {
			Throw("BO", rewriter, e->getExprLoc());
			const BinaryOperator *bOp = cast<const BinaryOperator>(e);
			ParseLiteral(bOp->getLHS(), false, true);
			ParseLiteral(bOp->getRHS(), false, true);
		}

		else
			Throw("Class " + string(e->getStmtClassName()) + " is unimplemented for a static define");
		return -1;
	}

	bool VisitDecl(Decl *D) {
		if (isa<VarDecl>(D)) {
			globalVarDecl = cast<VarDecl>(D);
			if (globalVarDecl->hasGlobalStorage()) {
				if (statics.find(dumpName(cast<NamedDecl>(D))) == statics.end()) {

					auto size = getSizeOfType(globalVarDecl->getType().getTypePtr());

					resetIntIndex();
					savedType = nullptr;
					oldStaticInc = staticInc;
					statics.insert(make_pair(dumpName(cast<NamedDecl>(D)), staticInc));
					staticInc += getSizeFromBytes(size);

					const Expr *initializer = globalVarDecl->getAnyInitializer();


					if (initializer) {
						//if (isa<CXXConstructExpr>(initializer)) {
						//	//out << "GetStaticP2 " << oldStaticInc << " //" << varDecl->getName().str() << endl;
						//	ParseLiteral(initializer, true, false, true, varDecl);
						//}

						ParseLiteral(initializer, false, true);


						if (oldStaticInc > staticInc)//undefined length arrays (should check if it is an undefined length array)
							staticInc = oldStaticInc;



						//if (varDecl->getType()->isCharType())
						//	DefaultStaticValues.insert({ oldStaticInc, to_string(Utils::Bitwise::SwapEndian(IS_Pop().bytes % 256)) });
						//else if (varDecl->getType()->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || varDecl->getType()->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
						//	DefaultStaticValues.insert({ oldStaticInc, to_string(Utils::Bitwise::Flip2BytesIn4(IS_Pop().bytes % 65536)) });
						//else
						//	DefaultStaticValues.insert({ oldStaticInc, to_string(IS_Pop().bytes) });


						//cout << "init Name: " << varDecl->getName().str() << " class: " << initializer->getStmtClassName() << '\n';
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
	void resetIntIndex()
	{
		if (intIndex != 0)
		{
			intIndex = 0;
			oldStaticInc++;
		}
	}


	VarDecl* globalVarDecl;
	uint32_t oldStaticInc = 0;
	uint32_t intIndex = 0;
	Type* savedType = nullptr;

	stringstream RuntimeStatics;
	map<uint32_t, string> DefaultStaticValues;//index, value

	#pragma region InitializationStack
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
		else
			Throw("InitializationStack Empty");
		return{ 0, FBWT_INT };
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
	#pragma endregion

private:
	Rewriter &TheRewriter;
	ASTContext *context;
};
#pragma endregion

#pragma region LocalsVisitor
class LocalsVisitor : public RecursiveASTVisitor<GlobalsVisitor> {
public:
	LocalsVisitor(Rewriter &R, ASTContext *context) : TheRewriter(R), context(context) { currentFunction = NULL; }

	bool VisitDecl(Decl *D) {

		if (isa<FunctionDecl>(D)) {
			//const FunctionDecl *func = cast<const FunctionDecl>(D);
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
#pragma endregion

#pragma region HandleASTConsumer
class MyASTConsumer : public ASTConsumer {
public:
	MyASTConsumer(Rewriter &R, ASTContext *context, DiagnosticsEngine *diagnostics, string filename) : Visitor(R, context, filename), GlobalsVisitor(R, context), diagnostics(diagnostics) {}

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

		if (diagnostics->getClient()->getNumErrors())
		{
			for (uint32_t i = 0; i < functionsNew.size(); i++)
			{
				delete functionsNew[i];
			}
			return;
		}
		Entryfunction.setUsed();


		stringstream header, main;

		header << "SetStaticsCount " << staticInc << "\r\n";
		for (map<uint32_t, string>::iterator iterator = GlobalsVisitor.DefaultStaticValues.begin(); iterator != GlobalsVisitor.DefaultStaticValues.end(); iterator++)
			header << "SetDefaultStatic " << iterator->first << " " << iterator->second << "\r\n";

		//this is not to be used by the high level compiler statics will still be indexed by integers for performance
		for (map<string, int>::iterator iterator = statics.begin(); iterator != statics.end(); iterator++)
			header << "SetStaticName " << iterator->second << " " << iterator->first << "\r\n";


		if (Visitor.MainRets != -1)
		{
			main << "\r\nFunction 0 2\r\nCall @main\r\n";
			for (int32_t i = 0; i < Visitor.MainRets; i++)
			{
				main << "Drop\r\n";
			}
			main << "Return 0 0\r\n";
			Entryfunction.addOpCall("main");
			for (int i = 0; i < Visitor.MainRets;i++)
			{
				Entryfunction.addOpDrop();
			}
			Entryfunction.addOpReturn(0, 0);
		}
		else
			Throw("Function \"main\" was not found");

		FILE* file = fopen(Visitor.outfile.c_str(), "wb");
		if (file != NULL)
		{

			header.seekg(0, ios::end);
			fwrite(header.str().c_str(), 1, header.tellg(), file);
			GlobalsVisitor.RuntimeStatics.seekg(0, ios::end);
			fwrite(GlobalsVisitor.RuntimeStatics.str().c_str(), 1, GlobalsVisitor.RuntimeStatics.tellg(), file);
			main.seekg(0, ios::end);
			fwrite(main.str().c_str(), 1, main.tellg(), file);

			string outstr = Visitor.out.str();
			for (uint32_t i = 0; i < functions.size(); i++)
			{
				if (functions[i].isused)
					fwrite(outstr.c_str() + functions[i].FuncDataPos, 1, i == functions.size() - 1 ? outstr.size() - functions[i].FuncDataPos : functions[i + 1].FuncDataPos - functions[i].FuncDataPos, file);
			}

			fclose(file);
		}
		else Throw("Output File Could Not Be Opened");

		FILE* ftemp = fopen((Visitor.outfile + "2").c_str(), "wb");
		if (ftemp != NULL)
		{
			header.seekg(0, ios::end);
			fwrite(header.str().c_str(), 1, header.tellg(), ftemp);
			string eStr = Entryfunction.toString();
			fwrite(eStr.c_str(), 1, eStr.size(), ftemp);
			for (uint32_t i = 0; i <functionsNew.size(); i++)
			{
				if (functionsNew[i]->IsUsed())
				{
					string fStr = functionsNew[i]->toString();
					fwrite(fStr.c_str(), 1, fStr.size(), ftemp);
				}
			}
			fclose(ftemp);
		}

		for (uint32_t i = 0; i < functionsNew.size(); i++)
		{
			delete functionsNew[i];
		}

	}

private:
	MyASTVisitor Visitor;
	GlobalsVisitor GlobalsVisitor;
	DiagnosticsEngine *diagnostics;
};
#pragma endregion

#pragma region CreateASTConsumer
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

		return llvm::make_unique<MyASTConsumer>(TheRewriter, &CI.getASTContext(), &CI.getDiagnostics(), fileName + "asm");
	}

private:
	Rewriter TheRewriter;
};
#pragma endregion

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
