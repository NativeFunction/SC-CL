#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <map>
#include <cmath>
#include "Utils.h"
#include "FunctionOpcode.h"
#include "clang/Lex/PreProcessor.h"

#pragma region Global_Defines
#undef ReplaceText//(commdlg.h)
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
#ifdef _DEBUG
#define AddInstructionConditionallyComment(cond, opName, comment, ...) {if (cond) {CurrentFunction->addOp##opName(__VA_ARGS__); CurrentFunction->pushComment(comment);}}
#else
#define AddInstructionConditionallyComment(cond, opName, comment, ...) AddInstructionConditionally(cond, opName, __VA_ARGS__)
#endif
#define AddJumpInlineCheck(jumpType, loc) CurrentFunction->addOp##jumpType(to_string(loc) + getInlineJumpLabelAppend())
#define AddJumpInlineCheckStr(jumpType, loc) CurrentFunction->addOp##jumpType((loc) + getInlineJumpLabelAppend())
#define AddJumpInlineCheckComment(jumpType, comment, loc) {CurrentFunction->addOp##jumpType(to_string(loc) + getInlineJumpLabelAppend()); CurrentFunction->pushComment(comment);}
#define AddJumpInlineCheckStrComment(jumpType, comment, loc) {CurrentFunction->addOp##jumpType((loc) + getInlineJumpLabelAppend()); CurrentFunction->pushComment(comment);}
#define AddJumpInlineCheckConditionally(cond, jumpType, loc) {if (cond) CurrentFunction->addOp##jumpType(to_string(loc) + getInlineJumpLabelAppend());}
#define AddJumpInlineCheckConditionallyStr(cond, jumpType, loc) {if (cond) CurrentFunction->addOp##jumpType((loc) + getInlineJumpLabelAppend());}
#ifdef _DEBUG
#define AddJumpInlineCheckConditionallyComment(cond, jumpType, comment, loc){if (cond) {CurrentFunction->addOp##jumpType(to_string(loc) + getInlineJumpLabelAppend()); CurrentFunction->pushComment(comment);}}
#else
#define AddJumpInlineCheckConditionallyComment(cond, jumpType, comment, loc) AddJumpInlineCheckConditionally(cond, jumpType, loc)
#endif
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

vector<FunctionData*> functionsNew;
FunctionData* CurrentFunction;
FunctionData Entryfunction("@EntryPoint", 0);
struct InlineData { uint32_t hash; string name; string inlineLblAppend; };
vector<InlineData> InlineItems;
#pragma endregion

#pragma region Global_Var_and_Scope_Decls
map<string, int> globals;
map<string, int> statics;
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
string getInlineJumpLabelAppend()
{
	if (InlineItems.size())
	{
		return InlineItems.back().inlineLblAppend;
	}
	return "";
}
bool isInInline() { return InlineItems.size(); }
bool isFunctionInInline(string fName)
{
	uint32_t hash = Utils::Hashing::Joaat(fName.c_str());
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
bool addFunctionInline(string fName, string returnLoc)
{
	if (isFunctionInInline(fName))
		return false;
	InlineItems.push_back({ Utils::Hashing::Joaat(fName.c_str()) , fName, getInlineJumpLabelAppend() + "_" + returnLoc });
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
				if (CS->isBitField())
				{
					Throw("Bit fileds aren't yet supported", rewriter, CS->getSourceRange());
				}
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
	if (isa<UnaryExprOrTypeTraitExpr>(expr->IgnoreParens()->IgnoreCasts()))
	{
		const UnaryExprOrTypeTraitExpr *ueTrait = cast<UnaryExprOrTypeTraitExpr>(expr->IgnoreParens()->IgnoreCasts());
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

double extractAPFloat(llvm::APFloat value)
{
	return &value.getSemantics() == &llvm::APFloat::IEEEsingle ? (double)value.convertToFloat() : value.convertToDouble();
}
#pragma endregion
#pragma endregion

#pragma region Global_Local/Static_Functions
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

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
public:
	MyASTVisitor(Rewriter &R, ASTContext *context, string filename) : TheRewriter(R), context(context), outfile(filename) {}

	#pragma region Misc_Functions
	void ComplexToBoolean(bool floating)
	{
		LocalVariables.addLevel();
		int index = LocalVariables.addDecl("imagPart", 1);
		if (floating) {
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
				if (isa<DeclRefExpr>(castExpr->getSubExpr()->IgnoreParens()->IgnoreCasts())) {
					const DeclRefExpr *declRef = cast<const DeclRefExpr>(castExpr->getSubExpr()->IgnoreParens()->IgnoreCasts());
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
			AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
			isAddr = true;
		}

		if (LocalVariables.find(key, &index))
		{
			if (isLtoRValue && !isAddr)
			{
				AddInstructionComment(GetFrame, "(pdecl)" + key, index);
				if (size == 1 || size == 2)
				{
					AddInstruction(GetConv, size, declref->getType()->isSignedIntegerType());
				}
			}
			else if (isAddr)
			{
				AddInstructionComment(GetFrameP, "(pdecl)&" + key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				
				if (size > 4)//fromStack
				{
					AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
					AddInstructionComment(GetFrameP, "(pdecl)&" + key, index);
					AddInstruction(FromStack);
				}
				else
				{
					if (size == 1 || size == 2)
					{
						AddInstruction(SetConv, size);
					}
					AddInstructionComment(SetFrame, "(pdecl)" + key, index);
				}

			}
		}
		else if (globals.find(key) != globals.end()) {
			index = globals[key];
			if (isLtoRValue && !isAddr)
			{
				AddInstructionComment(GetGlobal, "Global_" + key, index);
				if (size == 1 || size == 2)
				{
					AddInstruction(GetConv, size, declref->getType()->isSignedIntegerType());
				}
			}
			else if (isAddr)
			{
				AddInstructionComment(GetGlobalP, "Global_" + key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				
				if (size > 4)//fromStack
				{
					AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
					AddInstructionComment(GetGlobalP, "&Global_" + key, index);
					AddInstruction(FromStack);
				}
				else
				{
					if (size == 1 || size == 2)
					{
						AddInstruction(SetConv, size);
					}
					AddInstructionComment(SetGlobal, key, index);
				}
			}
		}
		else if (statics.find(key) != statics.end()) {
			index = statics[key];
			if (isLtoRValue && !isAddr)
			{
				AddInstructionComment(GetStatic, key, index);
				if (size == 1 || size == 2)
				{
					AddInstruction(GetConv, size, declref->getType()->isSignedIntegerType());
				}
			}
			else if (isAddr)
			{
				AddInstructionComment(GetStaticP, key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				

				if (size > 4)//fromStack
				{
					AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
					AddInstructionComment(GetStaticP, "&" + key, index);
					AddInstruction(FromStack);
				}
				else
				{
					if (size == 1 || size == 2)
					{
						AddInstruction(SetConv, size);
					}
					AddInstructionComment(SetStatic, key, index);
				}
			}
		}
		else
		{
			if (isAddr || isLtoRValue)
			{
				string name = "@" + key;
				uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
				uint32_t i = 0;
				for (i = 0; i < functionsNew.size(); i++)
				{
					if (functionsNew[i]->Hash() == hash)
					{
						if (functionsNew[i]->Name() == name)
						{
							CurrentFunction->addUsedFunc(functionsNew[i]);
							break;
						}
					}
				}

				if (i >= functionsNew.size())
					Throw("Function pointer \"" + key + "\" not found");

				AddInstructionComment(LabelLoc, "DeclRefExpr, nothing else, so func it", key);

			}
		}
		AddInstructionConditionally(isStackCpy, ToStack);
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
						AddInstructionComment(GetFrameP, var->getNameAsString(), curIndex);
						parseExpression(initializer);
					}
					else
					{
						parseExpression(initializer);
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
							AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
							AddInstructionComment(GetFrameP, "&" + var->getNameAsString(), curIndex);
							AddInstruction(FromStack);
						}
						else {
							if (size == 1 || size == 2)
							{
								AddInstruction(SetConv, size);
							}
							AddInstructionComment(SetFrame, "(init)" + var->getName().str(), curIndex);
						}
					}
					LocalVariables.addDecl(var->getName().str(), getSizeFromBytes(size));
				}

			}
		}
		return true;
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

					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
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

					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
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

					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
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

					llvm::APSInt result;
					if (argArray[2]->EvaluateAsInt(result, *context))
					{
						int iValue = result.getSExtValue();
						if (iValue > 0 && iValue < 256)
						{
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
					parseExpression(argArray[0], false, true);
					AddInstruction(Add);//let FunctionOpcode optimise this
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
					parseExpression(argArray[0], false, true);
					AddInstruction(Sub);//let FunctionOpcode optimise this
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
					parseExpression(argArray[0], false, true);
					AddInstruction(Mult);//let FunctionOpcode optimise this
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
					parseExpression(argArray[0], false, true);
					bool zeroDiv;
					AddInstruction(Div, &zeroDiv);
					if (zeroDiv) {
						Warn("Zero division error detected", rewriter, argArray[0]->getSourceRange());//just warn the user of the undefined behaviour)
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
					AddInstruction(Neg);
					return true;
				}
				Throw("neg must have signature \"extern __intrinsic int neg();\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("getframe"):
			{
				ChkHashCol("getframe");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						AddInstruction(GetFrame, result.getSExtValue());
						return true;
					}
					else
					{
						Throw("Argument got getframe must be a constant integer", rewriter, argArray[0]->getSourceRange());
					}
				}
				else
				{
					Throw("getframe must have signature \"extern __intrinsic int getframe(const int index);\"", rewriter, callee->getSourceRange());
				}
			}
			break;
			case JoaatCasedConst("getframep"):
			{
				ChkHashCol("getframep");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
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
			}
			break;
			case JoaatCasedConst("setframe"):
			{
				ChkHashCol("setframe");

				if (argCount == 1 && callee->getReturnType()->isVoidType())
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
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
						AddInstruction(SetFrame, result.getSExtValue());
						return true;
					}
					else
					{
						Throw("Argument got setframe must be a constant integer", rewriter, argArray[0]->getSourceRange());
					}
				}
				else
				{
					Throw("setframe must have signature \"extern __intrinsic void setframe(int index, ... optinalArgToSetTo);\"", rewriter, callee->getSourceRange());
				}
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
					llvm::APSInt apCount;
					int iCount;
					if (argArray[2]->EvaluateAsInt(apCount, *context) && (iCount = apCount.getSExtValue(), iCount > 0) && iCount & ~3)
					{
						int itemCount = iCount / 4;
						if (itemCount == 1)
						{
							parseExpression(argArray[1], true, true);
							AddInstruction(PGet);
							parseExpression(argArray[0], true, true);
							AddInstruction(PSet);
						}
						else {
							AddInstruction(PushInt, itemCount);
							parseExpression(argArray[1], true, true);
							AddInstruction(ToStack);
							AddInstruction(PushInt, itemCount);
							parseExpression(argArray[0], true, true);
							AddInstruction(FromStack);
						}
					}
					else
					{
						uint32_t loopLblCount = __COUNTER__;

						LocalVariables.addLevel();

						int destIndex = LocalVariables.addDecl("__memcpy-loop-dest", 1);
						int srcIndex = LocalVariables.addDecl("__memcpy-loop-src", 1);
						int sizeIndex = LocalVariables.addDecl("__memcpy-loop-size", 1);

						parseExpression(argArray[0], true, true);//dest
						AddInstruction(SetFrame, destIndex);

						parseExpression(argArray[1], true, true);//src
						AddInstruction(SetFrame, srcIndex);
						parseExpression(argArray[2], false, true);//size


						AddInstruction(SetFrame, sizeIndex);
						AddInstruction(PushInt, 0);
						AddInstruction(Label, "__memcpy-loop-" + to_string(loopLblCount));
						AddInstruction(Dup);
						AddInstruction(GetFrame, sizeIndex);
						AddInstruction(JumpGE, "__memcpy-loopend-" + to_string(loopLblCount));

						AddInstruction(GetFrame, srcIndex);
						AddInstruction(PGet);
						AddInstruction(ShiftLeft, 24);
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
					AddInstruction(SetFrame, destIndex);

					parseExpression(argArray[1], false, true);//value
					AddInstruction(ShiftLeft, 24);
					AddInstruction(SetFrame, valIndex);
					parseExpression(argArray[2], false, true);//size

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
			case JoaatCasedConst("popFloat"):
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
							AddInstructionConditionallyComment(size > 1, PushInt, "Struct Size", size);
							parseExpression(argArray[0], true, true);
							AddInstructionCondition(size > 1, ToStack, PGet);
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
							AddInstructionConditionallyComment(size > 1, PushInt, "Struct Size", size);
							parseExpression(argArray[0], true, true);
							AddInstructionCondition(size > 1, FromStack, PSet);
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
					parseExpression(argArray[0], false, true);
					AddInstruction(FAdd);//FunctionOpcode will optimise
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
					parseExpression(argArray[0], false, true);
					AddInstruction(FSub);//FunctionOpcode will optimise
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
					parseExpression(argArray[0], false, true);
					AddInstruction(FMult);//FunctionOpcode will optimise
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
					parseExpression(argArray[0], false, true);
					bool zeroDiv;
					AddInstruction(FDiv, &zeroDiv);//FunctionOpcode will optimise
					if (zeroDiv)
					{
						Warn("Zero division error detected", rewriter, argArray[0]->getSourceRange());//just warn the user of the undefined behaviour
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
							AddInstruction(PushInt, value);
							AddInstruction(GetFrameP, startDeclIndex);
							AddInstruction(FromStack);

							//Put them back on stack in reverse
							for (int i = startDeclIndex + value - 1; i >= startDeclIndex; i--)
							{
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
								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, firstItemIndex);
								AddInstruction(FromStack);
								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, secondItemIndex);
								AddInstruction(FromStack);

								//Put them back on stack in reverse
								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, firstItemIndex);
								AddInstruction(ToStack);
								AddInstruction(PushInt, value);
								AddInstruction(GetFrameP, secondItemIndex);
								AddInstruction(ToStack);

							}
							else
							{
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
			case JoaatCasedConst("getHashKey"):
			{
				ChkHashCol("getHashKey");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isCharType())
				{
					if (isa<StringLiteral>(argArray[0]->IgnoreParens()->IgnoreCasts()))
					{
						string str = cast<StringLiteral>(argArray[0]->IgnoreParens()->IgnoreCasts())->getString().str();
						AddInstructionComment(PushInt, "getHashKey(\"" + str + "\")", Utils::Hashing::Joaat(str.c_str()));
					}
					else
					{
						parseExpression(argArray[0], false, true);
						AddInstruction(GetHash);
					}
					return true;
				}
				Throw("getHashKey must have signature \"extern __intrinsic int getHashKey(char *string);\"", rewriter, callee->getSourceRange());
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

	bool parseStatement(Stmt *s, uint64_t breakLoc = -1, uint64_t continueLoc = -1) {
		if (isa<CompoundStmt>(s)) {
			CompoundStmt *cSt = cast<CompoundStmt>(s);
			LocalVariables.addLevel();
			for (auto *CS : cSt->body()) {
				parseStatement(cast<Stmt>(CS), breakLoc, continueLoc);
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
					parseStatement(Then, breakLoc, continueLoc);
					LocalVariables.removeLevel();
					bool ifEndRet = CurrentFunction->endsWithReturn() || (isInInline() && CurrentFunction->endsWithInlineReturn(getInlineJumpLabelAppend()));
					if (Else)//still parse the else code just incase there are goto labeils in there
					{

						AddJumpInlineCheckConditionallyStr(!ifEndRet, Jump, IfLocEnd);
						LocalVariables.addLevel();
						parseStatement(Else, breakLoc, continueLoc);
						LocalVariables.removeLevel();
						AddJumpInlineCheckConditionallyStr(!ifEndRet, Label, IfLocEnd);

					}
				}
				else
				{
					//still parse the then code just incase there are goto labels in there
					AddJumpInlineCheckStr(Jump, Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd);
					LocalVariables.addLevel();
					parseStatement(Then, breakLoc, continueLoc);
					LocalVariables.removeLevel();
					bool ifEndRet = CurrentFunction->endsWithReturn() || (isInInline() && CurrentFunction->endsWithInlineReturn(getInlineJumpLabelAppend()));
					if (Else)
					{
						AddJumpInlineCheckConditionallyStr(!ifEndRet, Jump, IfLocEnd);

						AddJumpInlineCheck(Label, Else->getLocStart().getRawEncoding());
						LocalVariables.addLevel();
						parseStatement(Else, breakLoc, continueLoc);
						LocalVariables.removeLevel();
					}
					AddJumpInlineCheckConditionallyStr(!ifEndRet || !Else, Label, IfLocEnd);
				}
			}
			else
			{
				parseExpression(conditional, false, true);
				AddJumpInlineCheckStr(JumpFalse, Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd);
				LocalVariables.addLevel();
				parseStatement(Then, breakLoc, continueLoc);
				LocalVariables.removeLevel();
				bool ifEndRet = CurrentFunction->endsWithReturn() || (isInInline() && CurrentFunction->endsWithInlineReturn(getInlineJumpLabelAppend()));
				AddJumpInlineCheckConditionallyStr(!ifEndRet, Jump, IfLocEnd);//if the last instruction is a return, no point adding a jump

				if (Else) {
					AddJumpInlineCheck(Label, Else->getLocStart().getRawEncoding());
					LocalVariables.addLevel();
					parseStatement(Else, breakLoc, continueLoc);
					LocalVariables.removeLevel();
				}

				AddJumpInlineCheckConditionallyStr(!ifEndRet || !Else, Label, IfLocEnd);

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
					AddJumpInlineCheck(Label, conditional->getLocStart().getRawEncoding());
					parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding());

					AddJumpInlineCheck(Jump, conditional->getLocStart().getRawEncoding());
					AddJumpInlineCheck(Label, whileStmt->getLocEnd().getRawEncoding());
				}
				else
				{

					AddJumpInlineCheck(Label, conditional->getLocStart().getRawEncoding());
					AddJumpInlineCheck(Jump, whileStmt->getLocEnd().getRawEncoding());

					parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding());

					AddJumpInlineCheck(Jump, conditional->getLocStart().getRawEncoding());
					AddJumpInlineCheck(Label, whileStmt->getLocEnd().getRawEncoding());
				}

			}
			else {
				AddJumpInlineCheck(Label, conditional->getLocStart().getRawEncoding());
				parseExpression(conditional, false, true);

				AddJumpInlineCheck(JumpFalse, whileStmt->getLocEnd().getRawEncoding());

				parseStatement(body, whileStmt->getLocEnd().getRawEncoding(), conditional->getLocStart().getRawEncoding());

				AddJumpInlineCheck(Jump, conditional->getLocStart().getRawEncoding());
				AddJumpInlineCheck(Label, whileStmt->getLocEnd().getRawEncoding());
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
				parseStatement(decl, -1, -1);
			}

			if (conditional) {
				AddJumpInlineCheck(Label, conditional->getLocStart().getRawEncoding());

				parseExpression(conditional, false, true);
				AddJumpInlineCheck(JumpFalse, body->getLocEnd().getRawEncoding());
			}
			else
			{
				AddJumpInlineCheck(Label, body->getLocStart().getRawEncoding());
			}

			parseStatement(
				body,
				forStmt->getLocEnd().getRawEncoding(),
				increment ? increment->getLocStart().getRawEncoding() : conditional ? conditional->getLocStart().getRawEncoding() : body->getLocStart().getRawEncoding());

			if (increment)
			{
				AddJumpInlineCheckComment(Label, "forstmt inc lbl", increment->getLocStart().getRawEncoding());
			}

			if (increment)
				parseExpression(increment);

			if (conditional)
			{
				AddJumpInlineCheckComment(Jump, "forstmt cond jmp", conditional->getLocStart().getRawEncoding());
			}
			else
			{
				AddJumpInlineCheckComment(Jump, "forstmt jmp", body->getLocStart().getRawEncoding());
			}

			AddJumpInlineCheckComment(Label, "forend lbl", body->getLocEnd().getRawEncoding());
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

			AddJumpInlineCheck(Label, body->getLocStart().getRawEncoding());
			parseStatement(body, conditional->getLocEnd().getRawEncoding(), body->getLocEnd().getRawEncoding());

			AddJumpInlineCheck(Label, body->getLocEnd().getRawEncoding());

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
				AddJumpInlineCheckConditionally(bValue, Jump, body->getLocStart().getRawEncoding());
				//no need for else, just jump right out
			}
			else
			{
				parseExpression(conditional, false, true);
				AddJumpInlineCheck(JumpTrue, body->getLocStart().getRawEncoding());
			}

			AddJumpInlineCheck(Label, conditional->getLocEnd().getRawEncoding());
			LocalVariables.removeLevel();

		}
		else if (isa<ReturnStmt>(s)) {
			const ReturnStmt *ret = cast<const ReturnStmt>(s);
			const Expr* retVal = ret->getRetValue();
			if (retVal)
				parseExpression(retVal, false, true);
			if (!isInInline())
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
				AddInstruction(Return, paramSize + (isa<CXXMethodDecl>(currFunction) ? 1 : 0), getSizeFromBytes(size));
			}
			else
			{
				AddInstructionComment(Jump, "Inline return", getInlineJumpLabelAppend());
			}

		}
		else if (isa<Expr>(s)) {
			parseExpression(cast<const Expr>(s));
		}
		else if (isa<BreakStmt>(s)) {
			AddJumpInlineCheckStrComment(Jump, "brkstmt jmp", to_string(breakLoc));
		}
		else if (isa<NullStmt>(s)) {
		}
		else if (isa<ContinueStmt>(s)) {
			AddJumpInlineCheckStrComment(Jump, "contstmt jmp", to_string(continueLoc));
		}
		else if (isa<DefaultStmt>(s)) {
			DefaultStmt *caseD = cast<DefaultStmt>(s);
			string labelName = to_string(caseD->getLocEnd().getRawEncoding()) + getInlineJumpLabelAppend();
			if (FindBuffer.find(labelName) == FindBuffer.end())
			{
				FindBuffer.insert(labelName);
				AddInstruction(Label, labelName);
			}
			LocalVariables.addLevel();

			if (caseD->getSubStmt())
				parseStatement(caseD->getSubStmt(), breakLoc, continueLoc);
			LocalVariables.removeLevel();
		}
		else if (isa<CaseStmt>(s)) {
			CaseStmt *caseS = cast<CaseStmt>(s);

			string labelName = to_string(caseS->getLocEnd().getRawEncoding()) + getInlineJumpLabelAppend();
			if (FindBuffer.find(labelName) == FindBuffer.end())
			{
				FindBuffer.insert(labelName);
				AddInstruction(Label, labelName);
			}
			LocalVariables.addLevel();
			if (caseS->getRHS())
				parseExpression(caseS->getRHS());

			if (caseS->getSubStmt())
				parseStatement(caseS->getSubStmt(), breakLoc, continueLoc);
			LocalVariables.removeLevel();
		}
		else if (isa<SwitchStmt>(s)) {
			SwitchStmt *switchStmt = cast<SwitchStmt>(s);
			FindBuffer.clear();
			parseExpression(switchStmt->getCond(), false, true);
			AddInstruction(Switch);

			//Build case switch list first
			SwitchCase *switchCaseList = switchStmt->getSwitchCaseList();
			DefaultStmt *defaultCase = NULL;
			struct switchCase { int val; string loc; };
			stack<switchCase> caseLabels;
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
								caseLabels.push({ val, to_string(caseS->getLocEnd().getRawEncoding()) + getInlineJumpLabelAppend() });
							}
							else
							{
								caseLabels.push({ (int)result.Val.getInt().getSExtValue(), to_string(caseS->getLocEnd().getRawEncoding()) + getInlineJumpLabelAppend() });
							}
						}
						else if (result.Val.isFloat())
						{
							float f = result.Val.getFloat().convertToFloat();
							caseLabels.push({ *(int*)&f, to_string(caseS->getLocEnd().getRawEncoding()) });
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
			if (!caseLabels.size())
			{
				Throw("Switch statement contains no cases", rewriter, switchStmt->getSourceRange());
			}
			while (caseLabels.size())
			{
				CurrentFunction->addSwitchCase(caseLabels.top().val, caseLabels.top().loc);
				caseLabels.pop();
			}

			if (defaultCase)
			{
				AddJumpInlineCheckComment(Jump, "Switch Default Jump", defaultCase->getLocEnd().getRawEncoding());
			}
			else
			{
				AddJumpInlineCheckComment(Jump, "Switch End Jump", switchStmt->getLocEnd().getRawEncoding());
			}

			//parse all
			parseStatement(switchStmt->getBody(), switchStmt->getLocEnd().getRawEncoding(), continueLoc);
			AddJumpInlineCheck(Label, switchStmt->getLocEnd().getRawEncoding());
			FindBuffer.clear();
		}
		else if (isa<GotoStmt>(s))
		{
			GotoStmt *gotoStmt = cast<GotoStmt>(s);
			AddJumpInlineCheckStr(Jump, gotoStmt->getLabel()->getNameAsString());
		}
		else if (isa<LabelStmt>(s))
		{
			LabelStmt *labelStmt = cast<LabelStmt>(s);
			AddJumpInlineCheckStr(Label, string(labelStmt->getName()));
			parseStatement(labelStmt->getSubStmt(), breakLoc, continueLoc);
		}
		else if (isa<GCCAsmStmt>(s))
		{
			GCCAsmStmt *asmstmt = cast<GCCAsmStmt>(s);
			Throw("Coding in assembley isnt supported", rewriter, s->getSourceRange());//throw an error as the new method of compiling wont support this
			if (InlineItems.size())
			{
				Warn("Using a __asm__ statement in an inlined function may lead to undesireable effects\r\nConsider marking the function as __attribute__((__noinline__))", rewriter, asmstmt->getSourceRange());
			}
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
	int parseExpression(const Expr *e, bool isAddr = false, bool isLtoRValue = false, bool printVTable = true, bool isAssign = false, bool isArrToPtrDecay = false) {
		Expr::EvalResult result;
		if (e->EvaluateAsRValue(result, *context) && !result.HasSideEffects)
		{
			if (result.Val.isInt())
			{
				if (!isLtoRValue)
					return -1;
				int val;
				if (CheckExprForSizeOf(e->IgnoreParens(), &val))
				{
					AddInstruction(PushInt, val);
				}
				else
				{
					
					int64_t resValue = result.Val.getInt().getSExtValue();

					if (doesInt64FitIntoInt32(resValue))
					{
						string value = to_string(resValue);
						Warn("Integer overflow. Value: " + value + " is out of bounds of (-2,147,483,648 to 2,147,483,647). Changed value to " + to_string((int32_t)resValue), rewriter, e->getExprLoc(), e->getExprLoc().getLocWithOffset(value.length() - 1));
					}

					if (e->getType()->isBooleanType() && (int32_t)resValue == -1)
						resValue = 1;

					AddInstruction(PushInt, (int32_t)resValue);
				}
				return -1;
			}
			else if (result.Val.isFloat())
			{
				if (!isLtoRValue)
					return -1;
				AddInstruction(PushFloat, extractAPFloat(result.Val.getFloat()));
				return -1;
			}
			else if (result.Val.isComplexFloat())
			{
				if (!isLtoRValue)
					return -1;
				AddInstruction(PushFloat, extractAPFloat(result.Val.getComplexFloatReal()));
				AddInstruction(PushFloat, extractAPFloat(result.Val.getComplexFloatImag()));
				return -1;
			}
			else if (result.Val.isComplexInt())
			{
				if (!isLtoRValue)
					return -1;
				AddInstruction(PushInt, result.Val.getComplexIntReal().getSExtValue());
				AddInstruction(PushInt, result.Val.getComplexIntImag().getSExtValue());
				return -1;
			}
		}
		if (isa<CompoundLiteralExpr>(e)) {
			const CompoundLiteralExpr *cLit = cast<const CompoundLiteralExpr>(e);
			parseExpression(cLit->getInitializer(), isAddr, isLtoRValue);
			if (isArrToPtrDecay && isLtoRValue)
			{
				int size = getSizeFromBytes(getSizeOfType(e->getType().getTypePtr()));
				int index = LocalVariables.addDecl("", size);
				if (size > 1)
				{
					AddInstructionComment(PushInt, "Type Size", size);
					AddInstruction(GetFrameP, index);
					AddInstruction(FromStack);
					AddInstructionComment(GetFrameP, "compound literal ptr decay", index);
				}
				else
				{
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
							if (i + j < litSize) {
								res |= ptr[i + j] << ((3 - j) << 3);
							}
						}
						AddInstruction(PushInt, (int32_t)res);
					}
				}
			}


		}
		else if (isa<CallExpr>(e)) {
			const CallExpr *call = cast<const CallExpr>(e);
			if (checkIntrinsic(call))
			{
				if (call->getType()->isVoidType() == false) {
					if (!isLtoRValue) {
						AddInstructionComment(Drop, "Function Result Unused");
						int size = getSizeFromBytes(getSizeOfType(call->getType().getTypePtr()));
						for (int i = 1; i < size; i++)
						{
							AddInstruction(Drop);
						}
					}
				}
				return 1;
			}
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
						AddInstructionComment(Call, "NumArgs: " + to_string(call->getNumArgs() + 1), getNameForFunc(method).substr(1));
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
										if (!addFunctionInline(name, to_string(e->getLocEnd().getRawEncoding())))
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
											AddInstruction(SetFrame, Index);
										}
										else if (paramSize > 1)
										{
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
											parseStatement(body, -1, -1);
											if (CurrentFunction->endsWithInlineReturn(getInlineJumpLabelAppend()))
											{
												CurrentFunction->RemoveLast();
												//remove the last jump, but keep the label, just incase other places in the function have returns
											}
											AddInstruction(Label, getInlineJumpLabelAppend());
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
						uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
						uint32_t i = 0;
						for (; i < functionsNew.size(); i++)
							if (functionsNew[i]->Hash() == hash)
							{
								if (functionsNew[i]->Name() == name)
								{
									CurrentFunction->addUsedFunc(functionsNew[i]);
									break;
								}
							}
						if (i >= functionsNew.size())
							Throw("Function \"" + name + "\" not found", rewriter, call->getExprLoc());

						AddInstructionComment(Call, "NumArgs: " + to_string(call->getNumArgs()), name.substr(1));
					}

				}

				if (call->getType()->isVoidType() == false) {
					if (!isLtoRValue) {
						AddInstructionComment(Drop, "Function Result Unused");
						int size = getSizeFromBytes(getSizeOfType(call->getType().getTypePtr()));
						for (int i = 1; i < size; i++)
						{
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
			switch (icast->getCastKind()) {
				case clang::CK_IntegralToFloating:
				{
					if (isa<IntegerLiteral>(icast->getSubExpr())) 
					{
						const IntegerLiteral *literal = cast<const IntegerLiteral>(icast->getSubExpr());

						AddInstructionConditionally(isLtoRValue, PushFloat, (float)(int)(literal->getValue().getSExtValue()));
						return true;
					}
					else 
					{
						parseExpression(icast->getSubExpr(), false, isLtoRValue);
						AddInstructionConditionally(isLtoRValue, ItoF);
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
							AddInstructionComment(PushInt, "Base+" + to_string(offset), offset / 4);
							parseExpression(declRef, true);
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
							AddInstructionComment(PushInt, "Base+" + to_string(offset), offset / 4);
							parseExpression(expr, true);
							AddInstruction(GetArrayP, 1);
							if (icast->getType()->getAsCXXRecordDecl())
								out << "GetArrayP2 1  " << " //Cast : " << base->getDeclName().getAsString() << " to " << icast->getType()->getAsCXXRecordDecl()->getDeclName().getAsString() << endl;
							else
								out << "GetArrayP2 1  " << " //Cast : " << base->getDeclName().getAsString() << " to " << icast->getType()->getPointeeCXXRecordDecl()->getDeclName().getAsString() << endl;
							AddInstructionComment(GetArrayP, base->getDeclName().getAsString() + "to" +
								(icast->getType()->getAsCXXRecordDecl() ? icast->getType()->getAsCXXRecordDecl()->getDeclName().getAsString() :
												  icast->getType()->getPointeeCXXRecordDecl()->getDeclName().getAsString()), 1);
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

					parseExpression(icast->getSubExpr(), false, isLtoRValue);
					break;
				}
				case clang::CK_IntegralToPointer:
				{
					//Fixed support for:
					//char* test = GET_STRING_PTR();
					//and other pointers
					parseExpression(icast->getSubExpr(), false, isLtoRValue);
					break;
				}
				case clang::CK_FloatingToIntegral:
				{

					parseExpression(icast->getSubExpr(), false, isLtoRValue);
					AddInstructionConditionally(isLtoRValue, FtoI);
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
					if (isLtoRValue) 
					{
						if (!icast->getSubExpr()->isEvaluatable(*context, Expr::SE_NoSideEffects))
						{
							AddInstruction(IsNotZero);
						}
					}
					break;
				}
				case clang::CK_FloatingToBoolean:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (isLtoRValue) {
						AddInstruction(PushFloat, 0);
						AddInstruction(FCmpNe);
					}
					break;
				}
				case clang::CK_FloatingComplexToReal:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					AddInstructionConditionally(!isLtoRValue, Drop);
					break;
				}
				case clang::CK_IntegralComplexToReal:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					AddInstructionConditionally(!isLtoRValue, Drop);
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
					AddInstructionConditionally(isLtoRValue, PushFloat, 0.0);
					break;
				}
				case clang::CK_IntegralRealToComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					AddInstructionConditionally(isLtoRValue, PushInt, 0);
					break;
				}
				case clang::CK_FloatingComplexToIntegralComplex:
				{
					parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					if (isLtoRValue) {
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("imagPart", 1);
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
				AddInstructionConditionally(isLtoRValue, PushInt, enumDecl->getInitVal().getSExtValue());
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
			return parseArraySubscriptExpr(e, isAddr, isLtoRValue, isArrToPtrDecay);
		}
		else if (isa<ParenExpr>(e)) {
			const ParenExpr *parenExpr = cast<const ParenExpr>(e);
			parseExpression(parenExpr->getSubExpr(), isAddr, isLtoRValue);
		}
		else if (isa<UnaryOperator>(e)) {
			const UnaryOperator *op = cast<const UnaryOperator>(e);

			Expr *subE = op->getSubExpr();
			if (op->getOpcode() == UO_Minus) {
				if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (isLtoRValue)
					{
						if (subE->getType()->isComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("imagPart", 1);
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
							AddInstruction(SetFrame, index);
							AddInstruction(Neg);
							AddInstruction(GetFrame, index);
							AddInstruction(Neg);
							LocalVariables.removeLevel();
						}
						else if (subE->getType()->isRealFloatingType())
						{
							AddInstruction(FNeg);
						}
						else
						{
							AddInstruction(Neg);
						}
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
					AddInstructionConditionally(isLtoRValue, PushInt, !literal->getValue().getSExtValue());
				}
				else if (isa<FloatingLiteral>(subE))
				{
					const FloatingLiteral *literal = cast<const FloatingLiteral>(subE);
					AddInstructionConditionally(isLtoRValue, PushFloat, !extractAPFloat(literal->getValue()));
				}
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					if (isLtoRValue)
					{
						if (subE->getType()->isComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("imagPart", 1);
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
							AddInstruction(SetFrame, index);
							AddInstruction(Not);
							AddInstruction(GetFrame, index);
							AddInstruction(Not);
							AddInstruction(And);
							LocalVariables.removeLevel();
						}
						else if (subE->getType()->isFloatingType())
						{
							AddInstruction(PushFloat, 0);
							AddInstruction(FCmpEq);
						}
						else
						{
							AddInstruction(Not);
						}
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
					AddInstructionConditionally(isLtoRValue, PushInt, ~(int)literal->getValue().getSExtValue());
					
				}
				else if (isa<Expr>(subE))
				{
					parseExpression(subE, isAddr, isLtoRValue);
					//Not operator for complex numbers is the conjugate
					if (isLtoRValue)
					{
						if (subE->getType()->isComplexIntegerType())
						{
							AddInstruction(Neg);
						}
						else if (subE->getType()->isComplexType())
						{
							AddInstruction(FNeg);
						}
						else
						{
							AddInstruction(AddImm, 1);
							AddInstruction(Neg);
						}
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
						AddInstructionComment(Drop, "unused result (UO_AddrOf - DeclRefExpr)");
					}
				}
				else {
					parseExpression(subE, true, false);
					if (!isLtoRValue) {
						AddInstructionComment(Drop, "unused result (UO_AddrOf - else)");
					}
				}
				return  true;

			}
			else if (op->getOpcode() == UO_Deref) {
				const Type* type = e->getType().getTypePtr();
				int size = getSizeOfType(type);
				int bSize = getSizeFromBytes(size);

				if (!isAddr && !isArrToPtrDecay)
				{
					if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
					{
						AddInstructionComment(PushInt, "Type Size", bSize);
					}
					else if ((size == 1 || size == 2) && isAssign)
					{
						AddInstruction(SetConv, size);

						parseExpression(subE, subE->getType().getTypePtr()->isArrayType(), true);

						AddInstruction(PGet);
						AddInstruction(PushInt, size == 1 ? 0xFFFFFF : 0xFFFF);
						AddInstruction(And);
						AddInstruction(Or);
					}

				}
				if (isa<ArraySubscriptExpr>(subE))
				{
					parseArraySubscriptExpr(subE, false, isArrToPtrDecay);
				}
				else if (isa<DeclRefExpr>(subE))
				{
					parseExpression(subE, false, false);
				}
				else
				{
					parseExpression(subE, false, true);
				}
				if (!isAddr && !isArrToPtrDecay)
				{
					if (isLtoRValue)
					{
						if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
						{
							AddInstruction(ToStack);
						}
						else
						{
							if (bSize > 1 && type->isArrayType())
								return true;

							AddInstruction(PGet);
							if (size == 1 || size == 2)
							{
								AddInstruction(GetConv, size, e->getType()->isSignedIntegerType());
							}
						}
					}
					else
					{
						if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
						{
							AddInstruction(FromStack);
						}
						else
						{
							AddInstruction(PSet);
						}
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

					if (subE->getType()->isBooleanType())
					{
						AddInstruction(PushInt, 1);//bool inc operation can only be 1
					}
					else
					{
						parseExpression(subE, false, true);

						if (subE->getType()->isRealFloatingType())
						{
							AddInstruction(FAddImm, 1.0);
						}
						else if (subE->getType()->isComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complexTemp", 1);
							AddInstruction(SetFrame, index);
							AddInstruction(FAddImm, 1.0);
							AddInstruction(GetFrame, index);
							LocalVariables.removeLevel();
						}
						else if (subE->getType()->isComplexIntegerType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complexTemp", 1);
							AddInstruction(SetFrame, index);
							AddInstruction(AddImm, 1);
							AddInstruction(GetFrame, index);
							LocalVariables.removeLevel();
						}
						else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
						{
							Throw("Incriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
						}
						else
						{
							AddInstruction(AddImm, pMult);
						}

					}
					if (isLtoRValue)
					{
						if (subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
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
							AddInstruction(Dup);
						}
					}
					parseExpression(subE, false, false, true, true);
					return 1;
				}
				else if (op->isDecrementOp()) {

					parseExpression(subE, false, true);

					if (subE->getType()->isRealFloatingType())
					{
						AddInstruction(FAddImm, -1.0);
					}
					else if (subE->getType()->isBooleanType())
					{
						AddInstruction(AddImm, -pMult);
						AddInstruction(IsNotZero);//bool dec operation can be 1 or 0
					}
					else if (subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						AddInstruction(SetFrame, index);
						AddInstruction(FAddImm, -1.0);
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						AddInstruction(SetFrame, index);
						AddInstruction(AddImm, -1);
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
					{
						Throw("Decriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
					}
					else
					{
						AddInstruction(AddImm, -pMult);
					}
					if (isLtoRValue)
					{
						if (subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
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
							AddInstruction(Dup);//ret value
						}
					}
					parseExpression(subE, false, false, true, true);
					return 1;
				}
			}
			else if (op->isPostfix()) {
				if (op->isIncrementOp()) {

					if (!subE->getType()->isBooleanType())
						parseExpression(subE, false, true);

					if (isLtoRValue)
					{
						if (subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
							AddInstruction(SetFrame, index + 1);//store imag
							AddInstruction(Dup);//dup real
							AddInstruction(SetFrame, index);//store real
							AddInstruction(GetFrame, index + 1);//restore imag
							AddInstruction(GetFrame, index);//push real
							AddInstruction(GetFrame, index + 1);//push imag
							LocalVariables.removeLevel();
						}
						else if (subE->getType()->isBooleanType())
						{
							parseExpression(subE, false, true);
						}
						else
						{
							AddInstruction(Dup);
						}
					}

					if (subE->getType()->isRealFloatingType())
					{
						AddInstruction(FAddImm, 1.0);
					}
					else if (subE->getType()->isBooleanType())
					{
						AddInstruction(PushInt, 1);//bool inc operation can only be 1
					}
					else if (subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						AddInstruction(SetFrame, index);
						AddInstruction(FAddImm, 1.0);
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						AddInstruction(SetFrame, index);
						AddInstruction(AddImm, 1);
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
					{
						Throw("Incriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
					}
					else
					{
						AddInstruction(AddImm, pMult);
					}

					parseExpression(subE, false, false, true, true);
					return 1;
				}
				else if (op->isDecrementOp()) {
					parseExpression(subE, false, true);

					if (isLtoRValue)
					{
						if (subE->getType()->isAnyComplexType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("complex", 2);
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
							AddInstruction(Dup);
						}
					}

					if (subE->getType()->isRealFloatingType())
					{
						AddInstruction(FAddImm, -1.0);
					}
					else if (subE->getType()->isBooleanType())
					{
						AddInstruction(AddImm, -pMult);
						AddInstruction(IsNotZero);//bool dec operation can be 1 or 0
					}
					else if (subE->getType()->isComplexType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						AddInstruction(SetFrame, index);
						AddInstruction(FAddImm, -1.0);
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if (subE->getType()->isComplexIntegerType())
					{
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("complexTemp", 1);
						AddInstruction(SetFrame, index);
						AddInstruction(AddImm, -1);
						AddInstruction(GetFrame, index);
						LocalVariables.removeLevel();
					}
					else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
					{
						Throw("Decriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split()) + "'", rewriter, subE->getSourceRange());
					}
					else
					{
						AddInstruction(AddImm, -pMult);
					}

					parseExpression(subE, false, false, true, true);
					return 1;
				}
			}
		}
		else if (isa<CXXThisExpr>(e)) {
			out << "GetFrame1 0 //\"this\"" << endl;
			AddInstructionComment(GetFrame, "\"this\"", 0);
			if (!isLtoRValue)
			{
				AddInstructionComment(Drop, "Unused This Expr");
			}
		}
		else if (isa<CXXConstructExpr>(e)) {
			const CXXConstructExpr *expr = cast<const CXXConstructExpr>(e);
			if (printVTable) {


				//out << "\n//VTableInit " << endl;
				//out << "call "
				if (expr->getType()->isArrayType()) {
					AddInstruction(Dup);
					AddInstruction(Call, expr->getType()->getAsArrayTypeUnsafe()->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl()->getNameAsString() + "::VTableInit");
				}
				else {
					AddInstruction(Dup);
					AddInstruction(Call, expr->getBestDynamicClassType()->getNameAsString().substr(1) + "::VTableInit");
				}
				//  out << " //End_VtableInit\n" << endl;
			}
			if (expr->getConstructor()->hasBody())
			{
				AddInstructionComment(Call, "ctor", getNameForFunc(expr->getConstructor()).substr(1));
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
					AddInstruction(PushInt, bSize);
					parseExpression(bOp->getLHS(), true, false, true, true);
					AddInstruction(FromStack);
					if (isLtoRValue)
					{
						parseExpression(bOp->getLHS(), false, true, true, false);
					}
				}
				else {
					if (isLtoRValue)
					{
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
				if (isLtoRValue)
				{
					parseExpression(bOp->getLHS(), false, true);
					if (bOp->getLHS()->getType()->isAnyComplexType())
					{
						ComplexToBoolean(bOp->getLHS()->getType()->isComplexType());
					}
					else if (bOp->getLHS()->getType()->isRealFloatingType())
					{
						AddInstruction(PushFloat, 0.0);
						AddInstruction(FCmpNe);
					}
					AddInstruction(Dup);
					AddJumpInlineCheck(JumpFalse, bOp->getRHS()->getLocEnd().getRawEncoding());
					AddInstruction(Drop);
					AddInstruction(PushInt, 1);
					parseExpression(bOp->getRHS(), false, true);
					if (bOp->getRHS()->getType()->isAnyComplexType())
					{
						ComplexToBoolean(bOp->getRHS()->getType()->isComplexType());
					}
					else if (bOp->getLHS()->getType()->isRealFloatingType())
					{
						AddInstruction(PushFloat, 0.0);
						AddInstruction(FCmpNe);
					}
					AddInstruction(And);
					AddJumpInlineCheck(Label, bOp->getRHS()->getLocEnd().getRawEncoding());
				}
				else
				{
					//parse LHS and RHS as not LtoR so the results get dropped, but any function calls etc still happen
					parseExpression(bOp->getLHS());
					parseExpression(bOp->getRHS());
				}
				return true;
			}
			if (bOp->getOpcode() == BO_LOr)
			{
				if (isLtoRValue)
				{


					parseExpression(bOp->getLHS(), false, true);
					if (bOp->getLHS()->getType()->isAnyComplexType())
					{
						ComplexToBoolean(bOp->getLHS()->getType()->isComplexType());
					}
					else if (bOp->getLHS()->getType()->isRealFloatingType())
					{
						AddInstruction(PushFloat, 0.0);
						AddInstruction(FCmpNe);
					}
					AddInstruction(Dup);
					AddJumpInlineCheck(JumpTrue, bOp->getRHS()->getLocEnd().getRawEncoding());
					parseExpression(bOp->getRHS(), false, true);
					if (bOp->getRHS()->getType()->isAnyComplexType())
					{
						ComplexToBoolean(bOp->getRHS()->getType()->isComplexType());
					}
					else if (bOp->getLHS()->getType()->isRealFloatingType())
					{
						AddInstruction(PushFloat, 0.0);
						AddInstruction(FCmpNe);
					}
					AddInstruction(Or);
					AddJumpInlineCheck(Label, bOp->getRHS()->getLocEnd().getRawEncoding());
				}
				else
				{
					//parse LHS and RHS as not LtoR so the results get dropped, but any function calls etc still happen
					parseExpression(bOp->getLHS());
					parseExpression(bOp->getRHS());
				}
				return true;
			}

			if (bOp->getLHS()->getType()->isAnyComplexType() || bOp->getRHS()->getType()->isAnyComplexType())
			{
				if (!isLtoRValue)
				{
					switch (bOp->getOpcode())
					{
						case BO_AddAssign:
						case BO_AndAssign:
						case BO_DivAssign:
						case BO_MulAssign:
						case BO_OrAssign:
						case BO_RemAssign:
						case BO_ShlAssign:
						case BO_ShrAssign:
						case BO_SubAssign:
						case BO_XorAssign:
						break;//these are ok if not LtoR, BO_Assign has already been handled
						default:
						parseExpression(bOp->getLHS());
						parseExpression(bOp->getRHS());
						Warn("Unused operator \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());
						return true;
					}
				}
				if (currFunction)
				{
					parseExpression(bOp->getLHS(), isAddr, true, true);
					if (!bOp->getLHS()->getType()->isAnyComplexType())
					{
						if (bOp->getLHS()->getType()->isFloatingType())
						{
							AddInstruction(PushFloat, 0);
						}
						else
						{
							AddInstruction(PushInt, 0);
						}
					}
					parseExpression(bOp->getRHS(), isAddr, true, true);
					if (!bOp->getRHS()->getType()->isAnyComplexType())
					{
						if (bOp->getRHS()->getType()->isFloatingType())
						{
							AddInstruction(PushFloat, 0);
						}
						else
						{
							AddInstruction(PushInt, 0);
						}
					}
					bool isFlt = bOp->getLHS()->getType()->isFloatingType();
					if (!isFlt)
					{
						if (bOp->getRHS()->getType()->isFloatingType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("imagPart", 1);
							AddInstruction(SetFrame, index);
							AddInstruction(FtoI);
							AddInstruction(GetFrame, index);
							AddInstruction(FtoI);
							LocalVariables.removeLevel();
						}
					}
					else
					{
						if (!bOp->getRHS()->getType()->isFloatingType())
						{
							LocalVariables.addLevel();
							int index = LocalVariables.addDecl("imagPart", 1);
							AddInstruction(SetFrame, index);
							AddInstruction(ItoF);
							AddInstruction(GetFrame, index);
							AddInstruction(ItoF);
							LocalVariables.removeLevel();
						}
					}
					LocalVariables.addLevel();
					int startindex = LocalVariables.addDecl("complex", 4);
					AddInstruction(PushInt, 4);
					AddInstruction(GetFrameP, startindex);
					AddInstruction(FromStack);
					#define AddIns() AddInstructionCondition(isFlt, FAdd, Add)
					#define SubIns() AddInstructionCondition(isFlt, FSub, Sub)
					#define MultIns() AddInstructionCondition(isFlt, FMult, Mult)
					#define DivIns() AddInstructionCondition(isFlt, FDiv, Div)
					switch (bOp->getOpcode())
					{
						case BO_Add:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							AddIns();
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							AddIns();

						}
						break;
						case BO_AddAssign:
						{
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							AddIns();
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							AddIns();

							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							AddInstruction(FromStack);

						}
						goto CheckAssignL2R;

						case BO_Sub:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}

							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							SubIns();
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							SubIns();
						}
						break;
						case BO_SubAssign:
						{
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							SubIns();
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							SubIns();

							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							AddInstruction(FromStack);
						}
						goto CheckAssignL2R;

						case BO_Mul:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							MultIns();
							SubIns();
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);
							MultIns();

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();
							AddIns();
						}
						break;
						case BO_MulAssign:
						{
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							MultIns();
							SubIns();
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);
							MultIns();

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();
							AddIns();

							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							AddInstruction(FromStack);
						}
						goto CheckAssignL2R;

						case BO_Div:
						{
							if (!isLtoRValue) {
								break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
							}
							int divide = LocalVariables.addDecl("divide", 1);

							AddInstruction(GetFrame, startindex + 2);
							AddInstruction(Dup);
							MultIns();

							AddInstruction(GetFrame, startindex + 3);
							AddInstruction(Dup);
							MultIns();

							AddIns();
							AddInstruction(SetFrame, divide);

							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							MultIns();
							AddIns();
							AddInstruction(GetFrame, divide);
							DivIns();

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);

							MultIns();
							SubIns();
							AddInstruction(GetFrame, divide);
							DivIns();
						}
						break;
						case BO_DivAssign:
						{
							int divide = LocalVariables.addDecl("divide", 1);
							AddInstruction(GetFrame, startindex + 2);
							AddInstruction(Dup);
							MultIns();

							AddInstruction(GetFrame, startindex + 3);
							AddInstruction(Dup);
							MultIns();

							AddIns();
							AddInstruction(SetFrame, divide);

							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();
							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 3);
							MultIns();
							AddIns();
							AddInstruction(GetFrame, divide);
							DivIns();

							AddInstruction(GetFrame, startindex + 1);
							AddInstruction(GetFrame, startindex + 2);
							MultIns();
							AddInstruction(GetFrame, startindex);
							AddInstruction(GetFrame, startindex + 3);

							MultIns();
							SubIns();
							AddInstruction(GetFrame, divide);
							DivIns();

							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							AddInstruction(FromStack);
						}
						goto CheckAssignL2R;
						default:
						Throw("Unsupported binary operator \"" + bOp->getOpcodeStr().str() + "\" for Complex data type", rewriter, bOp->getOperatorLoc());
						break;
					CheckAssignL2R:
						if (isLtoRValue)
						{
							AddInstruction(PushInt, 2);
							parseExpression(bOp->getLHS(), true);
							AddInstruction(ToStack);
						}
						break;
					}
					#undef AddIns
					#undef SubIns
					#undef MultIns
					#undef DivIns
					LocalVariables.removeLevel();
					return true;
				}
				else
				{
					Throw("Complex binary operations can only be done in functions");
				}

			}


			auto OpAssign = [&](OpcodeKind opcode, OpcodeKind floatVar = (OpcodeKind)-1)
			{
				if (bOp->getType()->isRealFloatingType() && floatVar == (OpcodeKind)-1)
				{
					Throw("Unsuppored binary operation '" + bOp->getOpcodeStr().str() + "' on floating point data type.", rewriter, bOp->getSourceRange());
				}
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
						AddInstruction(PushInt, val * getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr));
						if (pointerSet)
						{
							AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
							AddInstruction(PeekSet);
							AddInstructionCondition(isLtoRValue, PGet, Drop);
						}
						else
						{
							AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
							if (isLtoRValue)
							{
								AddInstruction(Dup);
							}
							parseExpression(bOp->getLHS(), false, false, false, true);
						}
					}
					else
					{
						AddInstruction(PushInt, val);
						if (pointerSet)
						{
							AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
							AddInstruction(PeekSet);
							AddInstructionCondition(isLtoRValue, PGet, Drop);
						}
						else
						{
							AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
							if (bOp->getLHS()->getType()->isBooleanType())
								AddInstruction(IsNotZero);
							if (isLtoRValue)
							{
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
						AddInstruction(MultImm, getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr));
					}

					if (pointerSet)
					{
						AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
						AddInstruction(PeekSet);
						AddInstructionCondition(isLtoRValue, PGet, Drop);
					}
					else
					{
						AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
						if (bOp->getLHS()->getType()->isBooleanType())
							AddInstruction(IsNotZero);
						if (isLtoRValue)
						{
							AddInstruction(Dup);
						}
						parseExpression(bOp->getLHS(), false, false, false, true);
					}
				}

			};

			switch (op) {
				case BO_SubAssign: OpAssign(OK_Sub, OK_FSub); break;
				case BO_AddAssign: OpAssign(OK_Add, OK_FAdd); break;
				case BO_DivAssign:  OpAssign(OK_Div, OK_FDiv); break;
				case BO_MulAssign:  OpAssign(OK_Mult, OK_FMult); break;
				case BO_OrAssign:  OpAssign(OK_Or); break;
				case BO_AndAssign:  OpAssign(OK_And); break;
				case BO_RemAssign:  OpAssign(OK_Mod, OK_FMod); break;
				case BO_XorAssign:  OpAssign(OK_Xor); break;
				case BO_ShlAssign:	OpAssign(OK_ShiftLeft); break;
				case BO_ShrAssign: OpAssign(OK_ShiftRight); break;
				default:
				{
					if (isLtoRValue)
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

								AddInstructionCondition(bOp->getLHS()->getType()->isFloatingType(), FSub, Sub);

								if (pSize > 1)
								{
									AddInstruction(PushInt, pSize);
									AddInstruction(Div);
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
								case BO_EQ: AddInstruction(FCmpEq); break;
								case BO_Mul: AddInstruction(FMult); break;
								case BO_Div:
								{
									bool isZeroDiv;
									AddInstruction(FDiv, &isZeroDiv);
									if (isZeroDiv)
									{
										Warn("Zero division error detected", rewriter, bOp->getRHS()->getSourceRange());//just warn the user of the undefined behaviour
									}
								}
								break;
								case BO_Rem: AddInstruction(FMod); break;
								case BO_Sub:  AddInstruction(FSub); break;
								case BO_LT: AddInstruction(FCmpLt); break;
								case BO_GT: AddInstruction(FCmpGt); break;
								case BO_GE: AddInstruction(FCmpGe); break;
								case BO_LE: AddInstruction(FCmpLe); break;
								case BO_NE: AddInstruction(FCmpNe); break;
								case BO_Add: AddInstruction(FAdd); break;

								default:
								Throw("Unimplemented binary floating op " + bOp->getOpcodeStr().str(), rewriter, bOp->getExprLoc());
							}
						}
						else {
							switch (op) {
								case BO_EQ: AddInstruction(CmpEq); break;
								case BO_Mul: AddInstruction(Mult); break;
								case BO_Div:
								{
									bool isZeroDiv;
									AddInstruction(Div, &isZeroDiv);
									if (isZeroDiv)
									{
										Warn("Zero division error detected", rewriter, bOp->getRHS()->getSourceRange());//just warn the user of the undefined behaviour
									}
								} break;
								case BO_Rem: AddInstruction(Mod); break;
								case BO_Sub: AddInstruction(Sub); break;
								case BO_LT: AddInstruction(CmpLt); break;
								case BO_GT: AddInstruction(CmpGt); break;
								case BO_GE: AddInstruction(CmpGe); break;
								case BO_LE: AddInstruction(CmpLe); break;
								case BO_NE: AddInstruction(CmpNe); break;
								case BO_And: AddInstruction(And); break;
								case BO_Xor: AddInstruction(Xor); break;
								case BO_Add: AddInstruction(Add); break;
								case BO_Or: AddInstruction(Or); break;
								case BO_Shl: AddInstruction(ShiftLeft); break;
								case BO_Shr: AddInstruction(ShiftRight); break;
								default:
								Throw("Unimplemented binary op " + bOp->getOpcodeStr().str(), rewriter, bOp->getExprLoc());
							}
						}
					}
					else
					{
						parseExpression(bOp->getLHS());
						parseExpression(bOp->getRHS());
						Warn("Unused operator \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());
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
				AddInstructionComment(AddImm, "." + ND->getName().str(), size * 4);
			}
			if (isLtoRValue)
			{
				AddInstruction(PGet);
			}
			else if (isAddr)
			{
				return 1;
			}
			else
			{
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
						for (i = 0; i < initCount; i += 4)
						{
							llvm::APSInt res;
							int evaluated[4];
							const Expr* inits[4];
							bool allconst = true;
							bool succ[4];
							for (int j = 0; j < 4; j++)
							{
								if (i + j < initCount)
								{
									inits[j] = I->getInit(i + j);
									if ((succ[j] = inits[j]->EvaluateAsInt(res, *context)))
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
							if (allconst)
							{
								int val = (evaluated[0] << 24) | (evaluated[1] << 16) | (evaluated[2] << 8) | (evaluated[3]);
								AddInstruction(PushInt, val);
							}
							else
							{
								if (succ[0])
								{
									AddInstruction(PushInt, evaluated[0] << 24);

								}
								else
								{
									parseExpression(I->getInit(i), false, true);
									AddInstruction(PushInt, 255);
									AddInstruction(And);
									AddInstruction(ShiftLeft, 24);

								}
								for (int j = 1; j < 4; j++)
								{
									if (i + j >= initCount)
										break;
									if (succ[j])
									{
										AddInstruction(PushInt, evaluated[j] << ((3 - j) << 3));
										AddInstruction(Or);
									}
									else
									{
										parseExpression(I->getInit(i + j), false, true);
										AddInstruction(PushInt, 255);
										AddInstruction(And);
										AddInstructionConditionally(j != 3, ShiftLeft, (3 - j) << 3);
										AddInstruction(Or);
									}

								}
							}
						}
						int size = getSizeOfType(I->getType().getTypePtr());
						while (i < size)
						{
							AddInstruction(PushInt, 0);
							i += 4;
						}
					}
					goto L2RCheck;
					case 2:
					{
						int initCount = I->getNumInits();
						int i;
						for (i = 0; i < initCount; i += 2)
						{
							llvm::APSInt res;
							int evaluated[2];
							const Expr* inits[2];
							bool allconst = true;
							bool succ[2];
							for (int j = 0; j < 2; j++)
							{
								if (i + j < initCount)
								{
									inits[j] = I->getInit(i + j);
									if ((succ[j] = inits[j]->EvaluateAsInt(res, *context)))
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
							if (allconst)
							{
								int val = (evaluated[0] << 16) | (evaluated[1]);
								AddInstruction(PushInt, val);
							}
							else
							{
								if (succ[0])
								{
									AddInstruction(PushInt, evaluated[0] << 16);

								}
								else
								{
									parseExpression(I->getInit(i), false, true);
									AddInstruction(PushInt, 65535);
									AddInstruction(And);
									AddInstruction(ShiftLeft, 16);
								}
								if (i + 1 < initCount)
								{
									if (succ[1])
									{
										AddInstruction(PushInt, evaluated[1]);
										AddInstruction(Or);
									}
									else
									{
										parseExpression(I->getInit(i + 1), false, true);
										AddInstruction(PushInt, 65535);
										AddInstruction(And);
										AddInstruction(Or);
									}
								}
							}
						}
						int size = getSizeOfType(I->getType().getTypePtr());
						int curSize = getSizeFromBytes(i * 2) * 4;
						while (curSize < size)
						{
							AddInstruction(PushInt, 0);
							curSize += 4;
						}
					}
					goto L2RCheck;
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
				AddInstruction(PushInt, 0);
				curSize += 4;
			}
		L2RCheck:
			if (!isLtoRValue)
			{
				int bSize = getSizeFromBytes(getSizeOfType(I->getType().getTypePtr()));
				while(bSize--)
				{
					AddInstructionComment(Drop, "Unused InitListExpr");
				}
			}
			return 1;
		}
		else if (isa<ImplicitValueInitExpr>(e))
		{
			const ImplicitValueInitExpr *im = cast<const ImplicitValueInitExpr>(e);
			uint32_t size = getSizeFromBytes(getSizeOfType(im->getType().getTypePtr()));
			for (uint32_t i = 0; i < size; i++)
			{
				AddInstruction(PushInt, 0);
			}
			if (!isLtoRValue)
			{
				for (uint32_t i = 0; i < size; i++)
				{
					AddInstructionComment(Drop, "Unused ImplicitValueInitExpr");
				}
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
							AddInstructionComment(PushInt, "Joaat(\"" + str + "\")", Utils::Hashing::Joaat(str.c_str()));
							if(!isLtoRValue)
							{
								AddInstructionComment(Drop, "unused jenkins hash");
							}
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
			const ConditionalOperator *cond = cast<const ConditionalOperator>(e);

			parseExpression(cond->getCond(), false, true);
			AddJumpInlineCheck(JumpFalse, cond->getRHS()->getLocStart().getRawEncoding());
			parseExpression(cond->getLHS(), isAddr, isLtoRValue);
			AddJumpInlineCheck(Jump, cond->getLHS()->getLocEnd().getRawEncoding());

			AddJumpInlineCheck(Label, cond->getRHS()->getLocStart().getRawEncoding());
			parseExpression(cond->getRHS(), isAddr, isLtoRValue);
			AddJumpInlineCheck(Label, cond->getLHS()->getLocEnd().getRawEncoding());
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
			AddInstruction(Dup);
			AddJumpInlineCheck(JumpFalse, bco->getFalseExpr()->getExprLoc().getRawEncoding());
			if (!isLtoRValue)
			{
				AddInstruction(Drop);//drop the value if not LtoR
			}
			AddJumpInlineCheck(Jump, bco->getLocStart().getRawEncoding());

			AddJumpInlineCheck(Label, bco->getFalseExpr()->getExprLoc().getRawEncoding());
			AddInstruction(Drop);
			parseExpression(bco->getFalseExpr(), false, isLtoRValue);//LtoR should handle the drop
			AddJumpInlineCheck(Label, bco->getLocStart().getRawEncoding());
		}
		else if (isa<OpaqueValueExpr>(e))
		{
			const OpaqueValueExpr *ov = cast<OpaqueValueExpr>(e);
			parseExpression(ov->getSourceExpr(), isAddr, isLtoRValue);
		}
		else if (isa<AddrLabelExpr>(e))
		{
			Throw("Address of Label Expressions are not supported", rewriter, e->getSourceRange());
		}
		else
			Throw("Unimplemented expression " + string(e->getStmtClassName()), rewriter, e->getExprLoc());

		return -1;
	}

	bool parseArraySubscriptExpr(const Expr *e, bool addrOf, bool LValueToRValue = false, bool isArrToPtrDecay = false) {
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


		if (!addrOf && !LValueToRValue && !isArrToPtrDecay)
		{
			//1 byte indexing
			if (type->isCharType())
			{
				//mod for narrowing conversion
				AddInstruction(SetConv, 1);
				parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);

				if (isCst)
				{
					int iRes = evalIndex.getSExtValue();
					if (iRes != 0)
					{
						AddInstruction(AddImm, iRes);
					}
				}
				else
				{
					parseExpression(index, false, true);
					AddInstruction(Add);
				}

				AddInstruction(PGet);
				AddInstruction(PushInt, 0xFFFFFF);
				AddInstruction(And);
				AddInstruction(Or);
			}
			//2 byte indexing
			else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
			{
				//mod for narrowing conversion
				
				AddInstruction(SetConv, 2);
				parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);
				if (isCst)
				{
					int iRes = evalIndex.getSExtValue();
					if (iRes != 0)
					{
						AddInstruction(AddImm, iRes * 2);
					}
				}
				else
				{
					parseExpression(index, false, true);
					AddInstruction(MultImm, 2);
					AddInstruction(Add);
				}
				AddInstruction(PGet);
				AddInstruction(PushInt, 0xFFFF);
				AddInstruction(And);
				AddInstruction(Or);
			}
		}
		else if (LValueToRValue && !addrOf && !isArrToPtrDecay)
		{
			int bSize = getSizeFromBytes(getSizeOfType(type));
			if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
			{
				AddInstructionComment(PushInt, "Type Size", bSize);
			}
		}

		parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);


		if (LValueToRValue && !addrOf && !isArrToPtrDecay)
		{
			if (isCst)
			{
				int iRes = evalIndex.getSExtValue();
				if (iRes != 0)
				{
					AddInstruction(AddImm, iRes * getSizeOfType(type));
				}
			}
			else
			{
				parseExpression(index, false, true);
				int size = getSizeOfType(type);
				if (size > 1)
				{
					AddInstruction(MultImm, size);
				}
				AddInstruction(Add);
			}
			if (getSizeFromBytes(getSizeOfType(type)) > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
			{
				AddInstructionComment(ToStack, "GetArray2");
			}
			else
			{
				AddInstruction(PGet);
				//1 byte indexing
				if (type->isCharType())
				{
					AddInstruction(GetConv, 1, e->getType()->isSignedIntegerType());
				}
				//2 byte indexing
				else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
				{
					AddInstruction(GetConv, 2, e->getType()->isSignedIntegerType());
				}

			}

		}
		else if (addrOf || isArrToPtrDecay)
		{
			int size = getSizeOfType(type);
			if (type->isArrayType())
				size = getSizeFromBytes(size) * 4;
			if (isCst)
			{
				int iRes = evalIndex.getSExtValue();
				if (iRes != 0)
				{
					AddInstruction(AddImm, iRes * size);
				}
			}
			else
			{
				parseExpression(index, false, true);
				AddInstructionConditionally(size > 1, MultImm, size);
				AddInstructionComment(Add, "GetArrayP2");
			}
		}
		else
		{
			if (isCst)
			{
				int iRes = evalIndex.getSExtValue();
				if (iRes != 0)
				{
					AddInstruction(AddImm, iRes * getSizeOfType(type));
				}
			}
			else
			{
				parseExpression(index, false, true);
				int size = getSizeOfType(type);
				AddInstructionConditionally(size > 1, MultImm, size);
				AddInstruction(Add);
			}
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


			if (isa<CXXConstructorDecl>(f))
				return true;

			Stmt *FuncBody = f->getBody();

			int32_t paramSize = 0;
			for (uint32_t i = 0; i<f->getNumParams(); i++)
				paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
			{
				uint32_t hash = Utils::Hashing::JoaatCased(getNameForFunc(f).c_str());
				size_t i;
				for (i = 0; i < functionsNew.size(); i++)
				{
					if (functionsNew[i]->Hash() == hash)
					{
						if (functionsNew[i]->Name() == getNameForFunc(f))
						{
							CurrentFunction = functionsNew[i];
							break;
						}
					}
				}
				if (i == functionsNew.size())
				{
					functionsNew.push_back(new FunctionData(getNameForFunc(f), (paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0))));
					CurrentFunction = functionsNew.back();
				}
			}
			string name = dumpName(cast<NamedDecl>(f));

			if (f->isMain())
			{
				Entryfunction.addUsedFunc(CurrentFunction);
				QualType type = f->getReturnType();
				MainRets = Utils::Math::DivInt(getSizeOfType(type.getTypePtr()), 4);
			}

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
				if (!CurrentFunction->endsWithReturn())
					AddInstruction(Return, paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0), 0);
			}
			else if (f->hasImplicitReturnZero() && !CurrentFunction->endsWithReturn())
			{
				int32_t paramSize = 0;
				for (uint32_t i = 0; i < f->getNumParams(); i++) {
					paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
				}
				AddInstruction(PushInt, 0);
				AddInstruction(Return, paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0), 1);
			}

			//Throw(f->getNameAsString() + ": not all control paths return a value", rewriter, f->getLocEnd());
			//uint32_t FunctionStackCount = LocalVariables.maxIndex - (isa<CXXMethodDecl>(f) ? 1 : 0) - paramSize;

			if (LocalVariables.maxIndex > 65536)
				Throw("Function \"" + f->getNameAsString() + "\" has a stack size of " + to_string(LocalVariables.maxIndex) + " when the max is 65536", rewriter, f->getLocStart());
			else
			{
				functionsNew.back()->setStackSize(LocalVariables.maxIndex);
			}
			CurrentFunction = NULL;
		}
		else
		{
			string name = f->getNameAsString();
			if (f->getStorageClass() == SC_None)
			{
				//prototype detected, add it to the functions list(s), 

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
					AddInstruction(Dup);
					AddInstructionComment(GetImm, classDecl->getDeclName().getAsString() + "::VTablePtr[" + to_string(getSizeFromBytes(getSizeOfCXXDecl(superDecl, false, true, classDecl)) + vtableInc) + "]", (getSizeFromBytes(getSizeOfCXXDecl(superDecl, false, true, classDecl)) + vtableInc));
					AddInstructionComment(GetImm, "VTable[" + to_string(func) + "] //" + getNameForFunc(method), func);
					AddInstructionComment(PCall, "(*)(" + getNameForFunc(method) + "());)");


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
			//int func = 0;
			for (CXXMethodDecl *VFI : baseDecl->methods()) {

				if (VFI->isVirtual()) {
					if (!foundVirt) {



						//                        out << "StaticGet 0 //\"this\"" << endl;
						uint32_t size = getSizeFromBytes(getSizeOfCXXDecl(classDecl, false, false));
						uint32_t sizeBase = getSizeFromBytes(getSizeOfCXXDecl(classDecl, false, true, baseDecl));

						foundVirt = true;

						AddInstruction(GetFrame, 0);
						AddInstructionComment(GetImmP, baseDecl->getDeclName().getAsString() + "::VTableStart", size + vtableInc);
						AddInstruction(GetFrame, 0);
						AddInstructionComment(SetImm, baseDecl->getDeclName().getAsString() + "::VTablePtr", sizeBase);

					}





					//const CXXMethodDecl *VFII = VFI->getCorrespondingMethodInClass(classDecl);
					/*
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
					*/
				}

			}
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
			FunctionData* ctor = new FunctionData("@" + CS->getDeclName().getAsString(), CS->getNumParams() + 1);
			functionsNew.push_back(ctor);
			CurrentFunction = ctor;
			currFunction = CS;

			for (auto *PI : CS->params()) {
				handleParmVarDecl(PI);
			}

			for (auto *IS : CS->inits()) {

				if (IS->getMember()) {

					parseExpression(IS->getInit());
					AddInstructionComment(GetFrame, "this", 0);
					AddInstructionComment(SetImm, IS->getMember()->getDeclName().getAsString(), getSizeFromBytes(getCXXOffsetOfNamedDecl(d, IS->getMember())))
				}
				else {
					if (isa<CXXConstructExpr>(IS->getInit())) {
						const CXXConstructExpr *constructor = cast<const CXXConstructExpr>(IS->getInit());
						for (auto *ARG : constructor->arguments()) {
							parseExpression(ARG);
						}
						AddInstructionComment(GetFrame, "this", 0);
					}
					parseExpression(IS->getInit(), false, false, false);
				}
			}


			parseStatement(CS->getBody());

			int32_t paramSize = 0;
			for (uint32_t i = 0; i < currFunction->getNumParams(); i++) {
				paramSize += getSizeFromBytes(getSizeOfType(currFunction->getParamDecl(i)->getType().getTypePtr()));
			}
			if (!CurrentFunction->endsWithReturn())
			{
				AddInstruction(Return, paramSize + (isa<CXXMethodDecl>(currFunction)), 0);
			}

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
				else if (type != savedType)//if type change with out identifier// --------- NEED TO TEST TYPE CHANGE TO SAME TYPE WITHOUT IDENTIFIER FOR BUGS ---------
				{
					resetIntIndex();
					isCurrentExprEvaluable = true;
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
				else if (isCurrentExprEvaluable)
					DefaultStaticValues.insert({ oldStaticInc++, to_string((int32_t)resValue) });
				else
					Entryfunction.addOpPushInt((int32_t)resValue);

				return true;
			}
			else if (result.Val.isFloat())
			{
				if (!isLtoRValue)
					return -1;
				if (isCurrentExprEvaluable)
					DefaultStaticValues.insert({ oldStaticInc++, to_string(FloatToInt((float)extractAPFloat(result.Val.getFloat()))) });
				else
					Entryfunction.addOpPushFloat((float)extractAPFloat(result.Val.getFloat()));
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
			{
				isCurrentExprEvaluable = true;
				doesCurrentValueNeedSet = false;
				ParseLiteral(I->getInit(i), false, true);
				if (doesCurrentValueNeedSet)
					Entryfunction.addOpSetStatic(oldStaticInc++);
			}

			resetIntIndex();
			isCurrentExprEvaluable = true;
			doesCurrentValueNeedSet = false;

			if (oldStaticInc - SavedStaticInc < size)
			{
				//cout << "init list size is less adding " << size - (oldStaticInc - SavedStaticInc) << " size: " << size << endl;

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
		else if (isa<UnaryOperator>(e)) {
			isCurrentExprEvaluable = false;
			const UnaryOperator *op = cast<const UnaryOperator>(e);
			Expr *subE = op->getSubExpr();

			if (op->getOpcode() == UO_AddrOf) {
				if (isa<DeclRefExpr>(subE)) {
					const DeclRefExpr *DRE = cast<const DeclRefExpr>(subE);
					doesCurrentValueNeedSet = true;

					//we can index because the name has to be declared in clang to use the declare, we will let clang handle errors
					Entryfunction.addOpGetStaticP(statics[DRE->getDecl()->getNameAsString()]);
				}
				else
				{
					ParseLiteral(subE, true, false);
				}
				return true;

			}
		}
		else if (isa<ImplicitCastExpr>(e))
		{
			const ImplicitCastExpr *icast = cast<const ImplicitCastExpr>(e);

			switch (icast->getCastKind())
			{
				case CK_ArrayToPointerDecay:
				isCurrentExprEvaluable = false;
				if (isa<StringLiteral>(icast->getSubExpr()))//char* x = "hello";
				{
					const StringLiteral *literal = cast<const StringLiteral>(icast->getSubExpr());
					Entryfunction.addOpPushString(literal->getString().str());
					Entryfunction.addOpSetStatic(oldStaticInc++);
				}
				else if (isa<DeclRefExpr>(icast->getSubExpr()))//int vstack[10] = {1,2,3,4,5,6,7,8,9,10}, *vstack_ptr = vstack;
				{
					const DeclRefExpr *DRE = cast<const DeclRefExpr>(icast->getSubExpr());
					doesCurrentValueNeedSet = true;

					//we can index because the name has to be declared in clang to use the declare, we will let clang handle errors
					Entryfunction.addOpGetStaticP(statics[DRE->getDecl()->getNameAsString()]);
				}
				else// need to test byte* t = {1,2,3};
					Throw("Unimplemented CK_ArrayToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()), rewriter, icast->getSubExpr()->getExprLoc());
				break;

				case CK_FunctionToPointerDecay://int (*ggg)(int, float) = test; // test is a function
				isCurrentExprEvaluable = false;
				if (isa<DeclRefExpr>(icast->getSubExpr())) {
					const DeclRefExpr *declRef = cast<const DeclRefExpr>(icast->getSubExpr());
					if (isa<FunctionDecl>(declRef->getDecl())) {
						const FunctionDecl *decl = cast<const FunctionDecl>(declRef->getDecl());

						string name = "@" + decl->getNameAsString();
						uint32_t hash = Utils::Hashing::JoaatCased(const_cast<char*>(name.c_str()));
						uint32_t i = 0;
						for (; i < functionsNew.size(); i++)
						{
							if (functionsNew[i]->Hash() == hash && functionsNew[i]->Name() == name)
							{
								Entryfunction.addUsedFunc(functionsNew[i]);
								break;
							}
						}

						if (i >= functionsNew.size())
							Throw("Static function pointer \"" + decl->getNameAsString() + "\" not found");

						string funcname = "GetLoc(\"" + decl->getNameAsString() + "\")";
						DefaultStaticValues.insert({ oldStaticInc++, funcname });

					}
					else Throw("Unimplemented CK_FunctionToPointerDecay DeclRefExpr for " + string(declRef->getStmtClassName()));

				}
				else
					Throw("Unimplemented CK_FunctionToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()));
				break;

				case clang::CK_PointerToIntegral://int ptoitest = &addrptrtest;
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;
				case clang::CK_IntegralToPointer://*vstack_ptr = &vstack[9] - &vstack[0];
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

				case clang::CK_BitCast://short* testok = &addrptrtest;//(addrptrtest is an int)
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

				default:
				Throw("Unimplemented ImplicitCastExpr of type " + string(icast->getCastKindName()));
			}


		}
		else if (isa<CastExpr>(e)) {
			
			const CastExpr *icast = cast<const CastExpr>(e);
			switch (icast->getCastKind()) {

				case clang::CK_ArrayToPointerDecay:
				isCurrentExprEvaluable = false;
				ParseLiteral(icast->getSubExpr(), true, false);
				break;

				//case clang::CK_DerivedToBase:
				//	ParseLiteral(icast->getSubExpr());
				//break;

				case clang::CK_PointerToIntegral://int ptoitest = (int)&addrptrtest;
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;
				case clang::CK_IntegralToPointer://*vstack_ptr = (int*)(&vstack[9] - &vstack[0]);
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

				case clang::CK_BitCast://short* testok = (short*)&addrptrtest;//(addrptrtest is an int)
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

				default:
				Throw("Cast " + string(icast->getCastKindName()) + " is unimplemented for a static define");

			}
		}
		else if (isa<BinaryOperator>(e)) {
			isCurrentExprEvaluable = false;
			const BinaryOperator *bOp = cast<const BinaryOperator>(e);
			BinaryOperatorKind op = bOp->getOpcode();
			

			//c allows same type pointer to pointer subtraction to obtain the logical difference. 
			if (isa<PointerType>(bOp->getLHS()->getType()) && isa<PointerType>(bOp->getRHS()->getType()))
			{
				ParseLiteral(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
				ParseLiteral(bOp->getRHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);

				if (op == BO_Sub)
				{
					const Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
					int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
					int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

					if (bOp->getLHS()->getType()->isFloatingType())
						Entryfunction.addOpFSub();
					else
						Entryfunction.addOpSub();

					if (pSize > 1)
					{
						Entryfunction.addOpPushInt(pSize);
						Entryfunction.addOpDiv();
					}

					return -1;
				}
				else
					Throw("Pointer to pointer operation not subtraction \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());
			}
			else if (isa<PointerType>(bOp->getLHS()->getType()))
			{
				//we need to parse left as an addr if its an array else its a pointer val
				ParseLiteral(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
				ParseLiteral(bOp->getRHS(), false, true);

				if (op == BO_Add || op == BO_Sub)
				{
					const Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
					int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
					int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

					if (pSize > 1)
						Entryfunction.addOpMultImm(pSize);
				}
				else
					Throw("Pointer to literal operation not addition or subtraction \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());

			}
			else if (isa<PointerType>(bOp->getRHS()->getType()))
			{
				//we need to parse right as an addr if its an array else its a pointer val
				ParseLiteral(bOp->getLHS(), false, true);

				if (op == BO_Add || op == BO_Sub)
				{
					const Type* pTypePtr = bOp->getRHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
					int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : 4;
					int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

					if (pSize > 1)
						Entryfunction.addOpMultImm(pSize);
				}
				else
					Throw("Pointer to literal operation not addition or subtraction \"" + bOp->getOpcodeStr().str() + "\"", rewriter, bOp->getOperatorLoc());

				ParseLiteral(bOp->getRHS(), bOp->getRHS()->getType().getTypePtr()->isArrayType(), true);
			}
			else
			{
				//no pointer operations
				Throw("Expected pointer operation for static BinaryOperator", rewriter, e->getExprLoc());
				//parseExpression(bOp->getLHS(), false, true);
				//parseExpression(bOp->getRHS(), false, true);
			}

			switch (op)
			{
				case BO_Sub: Entryfunction.addOpSub(); break;
				case BO_Add: Entryfunction.addOpAdd(); break;
				default:
				Throw("Unimplemented binary op " + bOp->getOpcodeStr().str(), rewriter, bOp->getExprLoc());
			}

		}
		else if (isa<ParenExpr>(e)) {
			const ParenExpr *parenExpr = cast<const ParenExpr>(e);
			ParseLiteral(parenExpr->getSubExpr(), isAddr, isLtoRValue);
		}
		else if (isa<ArraySubscriptExpr>(e)) {
			Expr* sexpr = const_cast<Expr*>(e);
			uint32_t inc = 0, ssize = 0;
			while (isa<ArraySubscriptExpr>(sexpr))
			{
				const ArraySubscriptExpr* arr = cast<ArraySubscriptExpr>(sexpr);
				const Expr *index = arr->getIdx();
				const Expr *base = arr->getBase();

				if (isa<ImplicitCastExpr>(base))
					base = cast<ImplicitCastExpr>(base)->getSubExpr();
				else if(isa<ParenExpr>(base))
					base = cast<ParenExpr>(base)->getSubExpr();
				else
					Throw("Unimplemented static array base resolution of " + string(base->getStmtClassName()), rewriter, e->getSourceRange());



				const DeclRefExpr *declRef = getDeclRefExpr(base);
				Type* type = const_cast<Type*>(base->getType().getTypePtr());

				if (type == NULL)
					type = const_cast<Type*>(declRef->getType().getTypePtr());
				if (type->isPointerType())
					type = const_cast<Type*>(type->getPointeeType().getTypePtr());

				llvm::APSInt iResult;
				if (index->EvaluateAsInt(iResult, *context))
				{
					doesCurrentValueNeedSet = true;

					if (!inc)
						Entryfunction.addOpGetStaticP(statics[declRef->getDecl()->getNameAsString()]);

					if (!ssize)
					{
						uint32_t elementSize = 4;
						if (type->isArrayType())
							elementSize = getSizeOfType(base->getType()->getArrayElementTypeNoTypeQual());

						Entryfunction.addOpAddImm(iResult.getSExtValue() * elementSize);
					}
					else
						Entryfunction.addOpAddImm(ssize * iResult.getSExtValue());

					ssize = getSizeOfType(type);
				}
				else
					Throw("Expected integer literal for static array pointer initialisation", rewriter, e->getSourceRange());

				inc++;
				sexpr = const_cast<Expr*>(base);
				while (isa<ParenExpr>(sexpr))
					sexpr = const_cast<Expr*>(cast<const ParenExpr>(sexpr)->getSubExpr());


			}

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
					isCurrentExprEvaluable = true;
					doesCurrentValueNeedSet = false;
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

						if (doesCurrentValueNeedSet)
							Entryfunction.addOpSetStatic(oldStaticInc++);

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
	bool isCurrentExprEvaluable = true;
	bool doesCurrentValueNeedSet = false;

	map<uint32_t, string> DefaultStaticValues;//index, value

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
		Entryfunction.setUsed();//build up function usage tree


		stringstream header;

		header << "SetStaticsCount " << staticInc << "\r\n";
		for (map<uint32_t, string>::iterator iterator = GlobalsVisitor.DefaultStaticValues.begin(); iterator != GlobalsVisitor.DefaultStaticValues.end(); iterator++)
			header << "SetDefaultStatic " << iterator->first << " " << iterator->second << "\r\n";

		//this is not to be used by the high level compiler statics will still be indexed by integers for performance
		for (map<string, int>::iterator iterator = statics.begin(); iterator != statics.end(); iterator++)
			header << "SetStaticName " << iterator->second << " " << iterator->first << "\r\n";


		if (Visitor.MainRets != -1)
		{
			Entryfunction.addOpCall("main");
			for (int i = 0; i < Visitor.MainRets; i++)
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
			string eStr = Entryfunction.toString();
			fwrite(eStr.c_str(), 1, eStr.size(), file);
			for (uint32_t i = 0; i <functionsNew.size(); i++)
			{
				if (functionsNew[i]->IsUsed())
				{
					string fStr = functionsNew[i]->toString();
					fwrite(fStr.c_str(), 1, fStr.size(), file);
				}
			}
			fclose(file);
		}
		else Throw("Output File Could Not Be Opened");

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
enum BuildType
{
	BT_GTAIV,
	BT_RDR_XSC,
	BT_RDR_SCO,
	BT_GTAV
};
enum Platform
{
	P_XBOX,
	P_PS3,
	P_PC
};
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


	string GetPlatformAbv()
	{
		switch (Plat)
		{
			case P_XBOX: return "x";
			case P_PS3: return "c";
			case P_PC: return "w";
		}
		Throw("No platform selected");
		return 0;
	}
	string GetBuildTypeExt()
	{
		switch (bType)
		{
			case BT_GTAIV: return "sca";//it would be cool to support gta 4 at some point but its not a priority
			case BT_RDR_XSC: return GetPlatformAbv() + "sa";
			case BT_RDR_SCO: return "sca2";
			case BT_GTAV: return GetPlatformAbv() + "sa2";
		}
		return "asm";
	}

	void AddDefines(Preprocessor &PP)
	{
		#define AddClangDefine(str) PP.appendDefMacroDirective(PP.getIdentifierInfo(str), PP.AllocateMacroInfo(SourceLocation()));
		switch(bType)
		{
			case BT_GTAIV://it would be cool to support gta 4 at some point but its not a priority
				AddClangDefine("__GTAIV__");
				AddClangDefine("__SCO__");
				break;
			case BT_RDR_XSC:
				AddClangDefine("__RDR__");
				AddClangDefine(string("__").append(1, toupper(*GetPlatformAbv().c_str())) + "SC__");
				break;
			case BT_RDR_SCO:
				AddClangDefine("__RDR__");
				AddClangDefine("__SCO__");
				break;
			case BT_GTAV:
				AddClangDefine("__GTAV__");
				AddClangDefine(string("__").append(1, toupper(*GetPlatformAbv().c_str())) + "SC__");
				break;
		}
		#undef AddClangMacro
	}
	void ModifyClangWarnings(DiagnosticsEngine& DE)
	{
		#define DisableClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Ignored, SourceLocation());
		#define EvevateClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Error, SourceLocation());
		
		DisableClangWarning("main-return-type");
		DisableClangWarning("incompatible-library-redeclaration");
		EvevateClangWarning("return-type");
		EvevateClangWarning("dangling-else");
		
		#undef DisableClangWarning
		#undef EvevateClangWarning
	}
	
	
	std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override {

		ModifyClangWarnings(CI.getDiagnostics());
		AddDefines(CI.getPreprocessor());
		llvm::errs() << "Compiling: " << file << "\n";
		TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
		rewriter = TheRewriter;
		SourceManager &SM = TheRewriter.getSourceMgr();
		string fileName(string(SM.getFileEntryForID(SM.getMainFileID())->getName()));
		fileName.erase(fileName.find_last_of(".c"));

		return llvm::make_unique<MyASTConsumer>(TheRewriter, &CI.getASTContext(), &CI.getDiagnostics(), fileName + GetBuildTypeExt());
	}

private:
	Rewriter TheRewriter;
	BuildType bType = BT_RDR_XSC;
	Platform Plat = P_XBOX;
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
