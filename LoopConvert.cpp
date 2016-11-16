#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <map>
#include <cmath>
#include "ClangUtils.h"
#include "Utils.h"
#include "FunctionData.h"
#include "clang/Lex/PreProcessor.h"
#include "ConstExpr.h"
#include "Script.h"
#include "Compiler.h"
std::string globalDirectory;

#pragma region Global_Defines
#undef ReplaceText//(commdlg.h)
#define MultValue(pTypePtr) (pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth)
#define STATIC_PADDING_DEBUG 0
#define AddInstruction(opName, ...) scriptData.getCurrentFunction()->addOp##opName(__VA_ARGS__)
#ifdef _DEBUG
#define AddInstructionComment(opName, comment, ...) {scriptData.getCurrentFunction()->addOp##opName(__VA_ARGS__); scriptData.getCurrentFunction()->pushComment(comment);}
#else
#define AddInstructionComment(opName, comment, ...) AddInstruction(opName, __VA_ARGS__)
#endif
#define AddFloatingOpCheck(isFlt, opEnum, opEnumFlt) scriptData.getCurrentFunction()->AddSimpleOp((isFlt) ? opEnumFlt : opEnum)
#define AddInstructionCondition(cond, opNameTrue, opNameFalse, ...) {if (cond) scriptData.getCurrentFunction()->addOp##opNameTrue(__VA_ARGS__); else scriptData.getCurrentFunction()->addOp##opNameFalse(__VA_ARGS__);}
#define AddInstructionConditionally(cond, opName, ...) {if (cond) scriptData.getCurrentFunction()->addOp##opName(__VA_ARGS__);}
#ifdef _DEBUG
#define AddInstructionConditionallyComment(cond, opName, comment, ...) {if (cond) {scriptData.getCurrentFunction()->addOp##opName(__VA_ARGS__); scriptData.getCurrentFunction()->pushComment(comment);}}
#else
#define AddInstructionConditionallyComment(cond, opName, comment, ...) AddInstructionConditionally(cond, opName, __VA_ARGS__)
#endif
#define AddJumpInlineCheck(jumpType, loc) scriptData.getCurrentFunction()->addOp##jumpType(to_string(loc) + scriptData.getInlineJumpLabelAppend())
#define AddJumpInlineCheckStr(jumpType, loc) scriptData.getCurrentFunction()->addOp##jumpType((loc) + scriptData.getInlineJumpLabelAppend())
#define AddJumpInlineCheckComment(jumpType, comment, loc) {scriptData.getCurrentFunction()->addOp##jumpType(to_string(loc) + scriptData.getInlineJumpLabelAppend()); scriptData.getCurrentFunction()->pushComment(comment);}
#define AddJumpInlineCheckStrComment(jumpType, comment, loc) {scriptData.getCurrentFunction()->addOp##jumpType((loc) + scriptData.getInlineJumpLabelAppend()); scriptData.getCurrentFunction()->pushComment(comment);}
#define AddJumpInlineCheckConditionally(cond, jumpType, loc) {if (cond) scriptData.getCurrentFunction()->addOp##jumpType(to_string(loc) + scriptData.getInlineJumpLabelAppend());}
#define AddJumpInlineCheckConditionallyStr(cond, jumpType, loc) {if (cond) scriptData.getCurrentFunction()->addOp##jumpType((loc) + scriptData.getInlineJumpLabelAppend());}
#ifdef _DEBUG
#define AddJumpInlineCheckConditionallyComment(cond, jumpType, comment, loc){if (cond) {scriptData.getCurrentFunction()->addOp##jumpType(to_string(loc) + scriptData.getInlineJumpLabelAppend()); scriptData.getCurrentFunction()->pushComment(comment);}}
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
using namespace llvm;

#pragma region Global_Misc_Clang_Decls
static cl::OptionCategory OptCategory("Options", "Option Category");
static cl::opt<Platform> PlatformOption(
	"platform", cl::desc("Choose Target Platform:"),
	cl::Required,
	cl::ValueRequired,
	cl::cat(OptCategory),
	cl::values(
	clEnumValN(Platform::P_XBOX, "XBOX", "Target Xbox (32 bit, big endian)"),
	clEnumValN(Platform::P_PS3, "PS3", "Target PS3 (32 bit, big endian)"),
	clEnumValN(Platform::P_PC, "PC", "Target PC (64 bit, little endian)"),
	clEnumValEnd
));
static cl::opt<BuildType> BuildTypeOption(
	"build_type", cl::desc("Choose Build Type:"),
	cl::Required,
	cl::ValueRequired,
	cl::cat(OptCategory),
	cl::values(
	//clEnumValN(BuildType::BT_GTAIV, "XBOX", "Grand Theft Auto IV (sco output)"),
	clEnumValN(BuildType::BT_GTAV, "GTAV", "Grand Theft Auto V (#sc output)"),
	clEnumValN(BuildType::BT_RDR_SCO, "RDR_SCO", "Red Dead Redemption (sco output)"),
	clEnumValN(BuildType::BT_RDR_XSC, "RDR_XSC", "Red Dead Redemption (#sc output)"),
	clEnumValEnd
));
static cl::opt<bool> SingletonOption(
	"singleton", cl::desc("Limits script to one instance on runtime"),
	cl::cat(OptCategory)
);
//void codeLayoutRandomisation(int maxBlockSize = 10, int minBlockSize = 2, bool keepEndReturn = true, bool makeJumpTable = false);
static cl::list<int> ObfuscateOption(
	"obfuscate", cl::desc("Options: int maxBlockSize, int minBlockSize, bool keepEndReturn, bool makeJumpTable"),
	cl::ValueRequired,
	cl::cat(OptCategory),
	cl::multi_val(4)
);
static cl::opt<int> PCVerisonOption(
	"pc_version", cl::desc("Sets the pc version for use in the native translation table"),
	cl::ValueRequired,
	cl::cat(OptCategory)
);

//static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
//static cl::extrahelp ProgramHelp("\nTemp text...\n");

static Rewriter rewriter;
#pragma endregion

#pragma region Global_Var_and_Scope_Decls
unique_ptr<Script> scriptData = nullptr;
uint32_t CurrentFileId = 0;
typedef struct NamedIndex
{
	uint32_t index;
	string name;
} NamedIndex;
map<uint32_t, NamedIndex> statics;///static decl end loc, StaticData
static int globalInc = 0;
static uint32_t staticInc = 0;

uint8_t stackWidth = 4;

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
	if (canonical->getBaseElementTypeUnsafe()->isCharType() && mult >= stackWidth) {
		return 1 * mult + ((mult % stackWidth != 0) ? 1 : 0);
	}
	else if (canonical->isArrayType())
		return getSizeOfType(canonical->getArrayElementTypeNoTypeQual())*mult + (mult > 1 ? stackWidth : 0);
	else
		return getSizeOfType(canonical)*mult + (mult > 1 ? stackWidth : 0);
}
uint32_t getSizeFromBytes(uint64_t bytes) {
	uint32_t size = (bytes / stackWidth) + ((bytes % stackWidth) ? 1 : 0);
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
		return 2 * stackWidth;
	else if (type->isCharType())
		return 1;
	else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
		return 2;
	else if (type->isIntegerType() || type->isBooleanType() || type->isRealFloatingType() || type->isPointerType())
		return stackWidth;
	else if (type->isVoidType())
		return 0;

	return 0;
}
uint32_t getSizeOfType(const Type* type) {

	if (isa<ConstantArrayType>(type)) {
		const ConstantArrayType *arrType = cast<const ConstantArrayType>(type);
		return ((getSizeOfType(type->getArrayElementTypeNoTypeQual()) * (arrType->getSize()).getSExtValue()) + stackWidth - 1) & ~(stackWidth-1);
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

				size += (getSizeOfType(type) + stackWidth - 1) & ~(stackWidth-1);
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

				uint32_t sz = (getSizeOfType(type) + stackWidth - 1) & ~(stackWidth-1);
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
		return stackWidth;
	else if (type->isVoidType())
		return 0;
	else if (type->isAnyComplexType())
		return 2 * stackWidth;

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
					offset += stackWidth;
					printedVTP = true;
				}
				if (incVTableDef)
					offset += stackWidth;
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
			temp = max(temp, stackWidth);

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
			offset += max(temp, stackWidth);
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
	MyASTVisitor(Rewriter &R, ASTContext *context, Script& scriptData) : TheRewriter(R), context(context), scriptData(scriptData) {}

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
			return record->getNameAsString() + "::" + method->getNameAsString();
		}
		if (ND->getDeclName()) {

			return ND->getNameAsString();
		}
		return "";
	}
	string getNameForFunc(const FunctionDecl *decl) {

		string FileId = "";
		if (decl->getStorageClass() == SC_Static)
		{
			assert(CurrentFileId && "File id 0 reserved for extern");
			char buf[9] = {};
			FileId += string(itoa(CurrentFileId - 1, buf, 36)) += "~";
			//this works without collision going on the notion that no one can add "~" to a function name
		}

		if (isa<CXXMethodDecl>(decl)) {
			const CXXMethodDecl *methodDecl = cast<const CXXMethodDecl>(decl);
			const CXXRecordDecl *record = methodDecl->getParent();
			return FileId + record->getNameAsString() + "::" + methodDecl->getNameAsString();
		}
		else {
			return FileId + decl->getNameAsString();
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
		const VarDecl *varDecl = dyn_cast<VarDecl>(declref->getDecl());
		size_t size = getSizeOfType(type);
		bool isStackCpy = size > stackWidth && isLtoRValue && !isAddr;//if greater then 4 bytes then a to stack is in order

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
				
				if (size > stackWidth)//fromStack
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
		else if (varDecl && varDecl->hasAttr<GlobalVariableAttr>()) {
			index = varDecl->getAttr<GlobalVariableAttr>()->getIndex();
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
				
				if (size > stackWidth)//fromStack
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
		else if (auto sData = scriptData.findStatic(declref->getDecl()->getLocEnd().getRawEncoding())) {

			scriptData.getCurrentFunction()->addUsedStatic(sData);
			if (isLtoRValue && !isAddr)
			{
				AddInstructionComment(GetStatic, key, sData);
				if (size == 1 || size == 2)
				{
					AddInstruction(GetConv, size, declref->getType()->isSignedIntegerType());
				}
			}
			else if (isAddr)
			{
				AddInstructionComment(GetStaticP, key, sData);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				

				if (size > stackWidth)//fromStack
				{
					AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
					AddInstructionComment(GetStaticP, "&" + key, sData);
					AddInstruction(FromStack);
				}
				else
				{
					if (size == 1 || size == 2)
					{
						AddInstruction(SetConv, size);
					}
					AddInstructionComment(SetStatic, key, sData);
				}
			}
		}
		else
		{
			if (isAddr || isLtoRValue)
			{
				if (auto funcDecl = dyn_cast_or_null<FunctionDecl>(declref->getDecl()))
				{
					if (auto func = scriptData.getFunctionFromName(getNameForFunc(funcDecl)))
					{
						AddInstructionComment(FuncLoc, "DeclRefExpr, nothing else, so func it", func);
					}
					else
						Throw("Function pointer \"" + key + "\" not found");
				}
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
						
						if (size > stackWidth) {
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
	bool isPushString(const Expr* e)
	{
		const CastExpr *cast;
		if ((cast = dyn_cast<CastExpr>(e)) && cast->getCastKind() == CK_ArrayToPointerDecay)
		{
			return isa<StringLiteral>(cast->getSubExpr());
		}
		return false;
	}

	bool checkIntrinsic(const CallExpr *call) {
		const FunctionDecl* callee = call->getDirectCallee();

		if (callee == NULL || !callee->hasAttr<IntrinsicFuncAttr>())
			return false;

		if (callee->getStorageClass() != SC_Extern)
			Throw("Intrinsic functions must be declared with the 'extern' keyword", rewriter, callee->getLocation());

		string funcName = dumpName(cast<NamedDecl>(callee));

		if (callee->getAttr<IntrinsicFuncAttr>()->getIsUnsafe() && !scriptData.isUnsafeContext())
			Warn("Unsafe Intrinsic \"" + funcName + "\" used in an unsafe context. This could lead to crashes", rewriter, call->getSourceRange());

		

		const Expr * const*argArray = call->getArgs();
		int argCount = call->getNumArgs();

		#define ChkHashCol(str) if(strcmp(funcName.c_str(), str) != 0) goto _IntrinsicNotFound;

		switch (JoaatCased(const_cast<char*>(funcName.c_str())))
		{
			case JoaatCasedConst("nop"):
			{
				ChkHashCol("nop");
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					
					if (argArray[0]->EvaluateAsInt(result, *context) && result.getSExtValue() > 0 && result.getSExtValue() <= 4096)
					{
						AddInstruction(Nop, result.getSExtValue());
					}
					else
					{
						Throw("nopCount argument must be a constant integer between 1 and 4096", rewriter, argArray[0]->getSourceRange());
					}
					
					return true;
				}
				else
				{
					Throw("nop must have signature \"extern __intrinsic void nop(const int nopCount);\"", rewriter, callee->getSourceRange());
				}
			}
			break;
			case JoaatCasedConst("strcpy"):
			{
				ChkHashCol("strcpy");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					if (isPushString(argArray[0]))
					{
						Throw("strcpy called with string literal as destination index", rewriter, argArray[0]->getSourceRange());
					}
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
							Throw("Integer constant for string max length argument in strcpy must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
					}
					else
						Throw("Expected integer constant for string max length argument in strcpy", rewriter, argArray[2]->getSourceRange());
				}
				else
					Throw("strcpy must have signature \"extern __intrinsic void strcpy(char* dst, char* src, const byte len);\"", rewriter, callee->getSourceRange());
				
				return false;
			}
			break;
			case JoaatCasedConst("stradd"):
			{
				ChkHashCol("stradd");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					if (isPushString(argArray[0]))
					{
						Throw("stradd called with string literal as destination index", rewriter, argArray[0]->getSourceRange());
					}
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
							Throw("Integer constant for string max length argument in stradd must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
					}
					else
						Throw("Expected integer constant for string max length argument in stradd", rewriter, argArray[2]->getSourceRange());
				}
				else
					Throw("stradd must have signature \"extern __intrinsic void stradd(char* dst, char* append, const byte len);\"", rewriter, callee->getSourceRange());
				
				return false;
			}
			break;
			case JoaatCasedConst("straddi"):
			{
				ChkHashCol("straddi");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					if (isPushString(argArray[0]))
					{
						Throw("straddi called with string literal as destination index", rewriter, argArray[0]->getSourceRange());
					}
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
							Throw("Integer constant for string max length argument in straddi must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
					}
					else
						Throw("Expected integer constant for string max length argument in straddi", rewriter, argArray[2]->getSourceRange());
				}
				else
					Throw("straddi must have signature \"extern __intrinsic void straddi(char* dst, int append, const byte len);\"", rewriter, callee->getSourceRange());
				
				return false;
			}
			break;
			case JoaatCasedConst("itos"):
			{
				ChkHashCol("itos");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
				{
					parseExpression(argArray[1], false, true);
					if (isPushString(argArray[0]))
					{
						Throw("itos called with string literal as destination index", rewriter, argArray[0]->getSourceRange());
					}
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
							Throw("Integer constant for string max length argument in itos must be between 1 and 255, got " + to_string(iValue), rewriter, argArray[2]->getSourceRange());
					}
					else
						Throw("Expected integer constant for string max length argument in itos", rewriter, argArray[2]->getSourceRange());
				}
				else
					Throw("itos must have signature \"extern __intrinsic void itos(char* dst, int value, const byte len);\"", rewriter, callee->getSourceRange());
				
				return false;
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
			case JoaatCasedConst("stackAdd"):
			{
				ChkHashCol("stackAdd");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(Add);//let FunctionOpcode optimise this
					return true;
				}
				Throw("stackAdd must have signature \"extern __intrinsic int stackAdd(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackSub"):
			{
				ChkHashCol("stackSub");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(Sub);//let FunctionOpcode optimise this
					return true;
				}
				Throw("stackSub must have signature \"extern __intrinsic int stackSub(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackMult"):
			{
				ChkHashCol("stackMult");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isIntegerType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(Mult);//let FunctionOpcode optimise this
				}
				Throw("stackMult must have signature \"extern __intrinsic int stackMult(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackDiv"):
			{
				ChkHashCol("stackDiv");
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
				Throw("stackDiv must have signature \"extern __intrinsic int stackDiv(int value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackNeg"):
			{
				ChkHashCol("stackNeg");
				if (argCount == 0 && callee->getReturnType()->isIntegerType())
				{
					AddInstruction(Neg);
					return true;
				}
				Throw("stackNeg must have signature \"extern __intrinsic int stackNeg();\"", rewriter, callee->getSourceRange());
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
					if (argArray[2]->EvaluateAsInt(apCount, *context) && (iCount = apCount.getSExtValue(), iCount > 0) && iCount & ~(stackWidth-1))
					{
						int itemCount = iCount / stackWidth;
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
						static uint32_t loopLblCount = -1;
						loopLblCount++;

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
					llvm::APSInt sResult, vResult;
					if (argArray[2]->EvaluateAsInt(sResult, *context) && sResult.getSExtValue() % 4 == 0 && argArray[1]->EvaluateAsInt(vResult, *context))
					{
						if (sResult.getSExtValue() < 0)
						{
							Throw("memset size must be positive", rewriter, callee->getSourceRange());
						}
						LocalVariables.addLevel();
						int destIndex = LocalVariables.addDecl("__memset-loop-dest", 1);
						uint8_t byteVal = vResult.getSExtValue();
						int pushVal = byteVal | byteVal << 8 | byteVal << 16 | byteVal << 24;
						int count = sResult.getSExtValue() / 4;
						parseExpression(argArray[0], true, true);//dest
						AddInstruction(SetFrame, destIndex);

						for (int i = 0; i < count;i++)
						{
							AddInstruction(PushInt, pushVal);
							AddInstruction(GetFrame, destIndex);
							AddInstruction(AddImm, i << 2);
							AddInstruction(PSet);
						}
						
						LocalVariables.removeLevel();
					}
					else
					{


						static uint32_t loopLblCount = -1;
						loopLblCount++;
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
						AddInstruction(Label, "__memset-loopend-" + to_string(loopLblCount));
						AddInstruction(Drop);
						LocalVariables.removeLevel();
					}

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
			break;
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
			break;
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
			break;
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
			case JoaatCasedConst("fMod"):
			{
				ChkHashCol("fMod");
				if (argCount == 2 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType() && argArray[1]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					AddInstruction(FMod);
				}
			}
			case JoaatCasedConst("stackFAdd"):
			{
				ChkHashCol("stackFAdd");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(FAdd);//FunctionOpcode will optimise
					return true;
				}
				Throw("stackFAdd must have signature \"extern __intrinsic float stackFAdd(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackFSub"):
			{
				ChkHashCol("stackFSub");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(FSub);//FunctionOpcode will optimise
					return true;
				}
				Throw("stackFSub must have signature \"extern __intrinsic float stackFSub(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackFMult"):
			{
				ChkHashCol("stackFMult");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(FMult);//FunctionOpcode will optimise
					return true;
				}
				Throw("stackFMult must have signature \"extern __intrinsic float stackFMult(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackFDiv"):
			{
				ChkHashCol("stackFDiv");
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
				Throw("stackFDiv must have signature \"extern __intrinsic float stackFDiv(float value);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackFNeg"):
			{
				ChkHashCol("stackFNeg");
				if (argCount == 0 && callee->getReturnType()->isRealFloatingType())
				{
					AddInstruction(FNeg);
					return true;
				}
				Throw("stackFNeg must have signature \"extern __intrinsic float stackFNeg();\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackVAdd"):
			{
				ChkHashCol("stackVAdd");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(VAdd);
					return true;
				}
				Throw("stackVAdd must have signature \"extern __intrinsic vector3 stackVAdd(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackVSub"):
			{
				ChkHashCol("stackVSub");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(VSub);
					return true;
				}
				Throw("stackVSub must have signature \"extern __intrinsic vector3 stackVSub(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackVMult"):
			{
				ChkHashCol("stackVMult");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(VMult);
					return true;
				}
				Throw("stackVMult must have signature \"extern __intrinsic vector3 stackVMult(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackVDiv"):
			{
				ChkHashCol("stackVDiv");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(VDiv);
					return true;
				}
				Throw("stackVDiv must have signature \"extern __intrinsic vector3 stackVDiv(vector3 value)\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("stackVNeg"):
			{
				ChkHashCol("stackVNeg");

				if (argCount == 0 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3)
				{
					AddInstruction(VNeg);
					return true;
				}
				Throw("stackVNeg must have signature \"extern __intrinsic vector3 stackVNeg()\"", rewriter, callee->getSourceRange());
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
					parseExpression(argArray[0], false, true);
					AddInstruction(GetHash);
					return true;
				}
				Throw("getHashKey must have signature \"extern __intrinsic int getHashKey(char *string);\"", rewriter, callee->getSourceRange());
				return false;
			}
			break;
			case JoaatCasedConst("bit_test"):
			{
				ChkHashCol("bit_test");
				if (argCount == 2 && callee->getReturnType()->isBooleanType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[1]->EvaluateAsInt(result, *context))
					{
						auto iResult = result.getSExtValue();
						if (iResult < 32 && iResult >= 0)
						{
							parseExpression(argArray[0], false, true);
							AddInstruction(IsBitSet, (uint8_t)iResult);
							return true;
						}
					}
					Throw("bitIndex argument for bit_test must be a compile time constant integer between 0 and 31", rewriter, argArray[1]->getSourceRange());
				}
				Throw("bit_test must have signature \"extern __intrinsic bool bit_test(int value, const byte bitIndex);\"", rewriter, callee->getSourceRange());
			}
			case JoaatCasedConst("bit_set"):
			{
				ChkHashCol("bit_set");
				if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[1]->EvaluateAsInt(result, *context))
					{
						auto iResult = result.getSExtValue();
						if (iResult < 32 && iResult >= 0)
						{
							parseExpression(argArray[0], false, true);
							AddInstruction(BitSet, (uint8_t)iResult);
							return true;
						}
					}
					Throw("bitIndex argument for bit_set must be a compile time constant integer between 0 and 31", rewriter, argArray[1]->getSourceRange());
				}
				Throw("bit_set must have signature \"extern __intrinsic bool bit_set(int* address, const byte bitIndex);\"", rewriter, callee->getSourceRange());
			}
			case JoaatCasedConst("bit_reset"):
			{
				ChkHashCol("bit_reset");
				if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[1]->EvaluateAsInt(result, *context))
					{
						auto iResult = result.getSExtValue();
						if (iResult < 32 && iResult >= 0)
						{
							parseExpression(argArray[0], false, true);
							AddInstruction(BitReset, (uint8_t)iResult);
							return true;
						}
					}
					Throw("bitIndex argument for bit_reset must be a compile time constant integer between 0 and 31", rewriter, argArray[1]->getSourceRange());
				}
				Throw("bit_reset must have signature \"extern __intrinsic bool bit_reset(int* address, const byte bitIndex);\"", rewriter, callee->getSourceRange());
			}
			case JoaatCasedConst("bit_flip"):
			{
				ChkHashCol("bit_flip");
				if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
				{
					llvm::APSInt result;
					if (argArray[1]->EvaluateAsInt(result, *context))
					{
						auto iResult = result.getSExtValue();
						if (iResult < 32 && iResult >= 0)
						{
							parseExpression(argArray[0], false, true);
							AddInstruction(BitFlip, (uint8_t)iResult);
							return true;
						}
					}
					Throw("bitIndex argument for bit_flip must be a compile time constant integer between 0 and 31", rewriter, argArray[1]->getSourceRange());
				}
				Throw("bit_flip must have signature \"extern __intrinsic bool bit_flip(int* address, const byte bitIndex);\"", rewriter, callee->getSourceRange());
			}
			default:
		_IntrinsicNotFound:
			Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
		}

		#undef ChkHashCol

		return false;
	}

	bool findAnyLabel(const Stmt* stmt)
	{
		for (auto it = stmt->child_begin(); it!=stmt->child_end();++it)
		{
			if (isa<LabelStmt>(*it))
				return true;
			return findAnyLabel(*it);
		}
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
			if (Else && isa<CompoundStmt>(Else) && cast<CompoundStmt>(Else)->size() == 0)
			{
				Else = NULL;
			}

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
					if (Else && !findAnyLabel(Else))
					{
						Else = NULL;// if there are no labels in the else just mark it as null as the code will never be executed
					}
					bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
					if (Else)
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
					if (findAnyLabel(Then))
					{
						if (Else)
						{
							AddJumpInlineCheckStr(Jump, to_string(Else->getLocStart().getRawEncoding()));
							LocalVariables.addLevel();
							parseStatement(Then, breakLoc, continueLoc);
							LocalVariables.removeLevel();


							bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
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
						else
						{
							AddJumpInlineCheckStr(Jump, IfLocEnd);
							LocalVariables.addLevel();
							parseStatement(Then, breakLoc, continueLoc);
							LocalVariables.removeLevel();
							AddJumpInlineCheckStr(Label, IfLocEnd);

						}
					}
					else
					{
						//ignore the then case
						if (Else)
						{
							LocalVariables.addLevel();
							parseStatement(Else, breakLoc, continueLoc);
							LocalVariables.removeLevel();
						}
					}
				}
			}
			else
			{
				parseExpression(conditional, false, true);
				AddJumpInlineCheckStr(JumpFalse, Else ? to_string(Else->getLocStart().getRawEncoding()) : IfLocEnd);
				LocalVariables.addLevel();
				parseStatement(Then, breakLoc, continueLoc);
				LocalVariables.removeLevel();
				bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
				AddJumpInlineCheckConditionallyStr(!ifEndRet && Else, Jump, IfLocEnd);//if the last instruction is a return, no point adding a jump

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

			if (!scriptData.getInlineCount())
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
				AddInstruction(Return);
			}
			else
			{
				AddInstructionComment(Jump, "Inline return", scriptData.getInlineJumpLabelAppend());
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
			AddInstruction(Label, to_string(caseD->getLocStart().getRawEncoding()) + scriptData.getInlineJumpLabelAppend());
			LocalVariables.addLevel();

			if (caseD->getSubStmt())
				parseStatement(caseD->getSubStmt(), breakLoc, continueLoc);
			LocalVariables.removeLevel();
		}
		else if (isa<CaseStmt>(s)) {
			CaseStmt *caseS = cast<CaseStmt>(s);
			AddInstruction(Label, to_string(caseS->getLocStart().getRawEncoding()) + scriptData.getInlineJumpLabelAppend());

			LocalVariables.addLevel();
			if (caseS->getRHS())
				parseExpression(caseS->getRHS());

			if (caseS->getSubStmt())
				parseStatement(caseS->getSubStmt(), breakLoc, continueLoc);
			LocalVariables.removeLevel();
		}
		else if (isa<SwitchStmt>(s)) {
			SwitchStmt *switchStmt = cast<SwitchStmt>(s);
			parseExpression(switchStmt->getCond(), false, true);

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
								caseLabels.push({ val, to_string(caseS->getLocStart().getRawEncoding()) + scriptData.getInlineJumpLabelAppend() });
							}
							else
							{
								caseLabels.push({ (int)result.Val.getInt().getSExtValue(), to_string(caseS->getLocStart().getRawEncoding()) + scriptData.getInlineJumpLabelAppend() });
							}
						}
						else if (result.Val.isFloat())
						{
							float f = result.Val.getFloat().convertToFloat();
							caseLabels.push({ *(int*)&f, to_string(caseS->getLocStart().getRawEncoding()) });
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
			int sSize = caseLabels.size();
			if (!sSize)
			{
				Warn("Switch statement contains no cases", rewriter, switchStmt->getSourceRange());
				AddInstruction(Switch);
			}
			else if (sSize > 255)
			{
				//multiple switch statements needed
				LocalVariables.addLevel();
				int index = LocalVariables.addDecl("Switch Temp", 1);
				AddInstruction(Dup);
				AddInstructionComment(SetFrame, "Switch temporary variable",index);
				AddInstruction(Switch);
				int i = 0;
				while (caseLabels.size())
				{
					if (i++ == 255)
					{
						i = 1;
						AddInstructionComment(GetFrame, "Switch temporary variable", index);
						AddInstruction(Switch);
					}
					scriptData.getCurrentFunction()->addSwitchCase(caseLabels.top().val, caseLabels.top().loc);
					caseLabels.pop();
				}
				LocalVariables.removeLevel();
			}
			else
			{
				AddInstruction(Switch);
				while (caseLabels.size())
				{
					scriptData.getCurrentFunction()->addSwitchCase(caseLabels.top().val, caseLabels.top().loc);
					caseLabels.pop();
				}
			}
			

			if (defaultCase)
			{
				scriptData.getCurrentFunction()->setSwitchDefaultCaseLoc(to_string(defaultCase->getLocStart().getRawEncoding()) + scriptData.getInlineJumpLabelAppend());
			}
			else
			{
				scriptData.getCurrentFunction()->setSwitchDefaultCaseLoc(to_string(switchStmt->getLocEnd().getRawEncoding()) + scriptData.getInlineJumpLabelAppend());
			}

			//parse all
			parseStatement(switchStmt->getBody(), switchStmt->getLocEnd().getRawEncoding(), continueLoc);
			AddJumpInlineCheck(Label, switchStmt->getLocEnd().getRawEncoding());
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
			if (scriptData.getInlineCount())
			{
				Warn("Using a __asm__ statement in an inlined function may lead to undesireable effects\r\nConsider marking the function as __attribute__((__noinline__))", rewriter, asmstmt->getSourceRange());
			}
		}
		else if (isa<IndirectGotoStmt>(s))
		{
			auto indirectGoto = cast<IndirectGotoStmt>(s);
			parseExpression(indirectGoto->getTarget(), false, true);
			AddInstruction(GoToStack);
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
		if (!isAddr && e->EvaluateAsRValue(result, *context) && !result.HasSideEffects)
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
					AddInstruction(PushInt, getSizeFromBytes(getSizeOfType(e->getType().getTypePtr())));
					AddInstructionComment(PushString, "string array", str);
					AddInstruction(ToStack);
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
						AddInstructionComment(Call, "(memExpr) NumArgs: " + to_string(call->getNumArgs() + 1), scriptData.getFunctionFromName(getNameForFunc(method)));
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
				{
					parseExpression(argArray[i], false, true);
					const Type* type = argArray[i]->getType().getTypePtr();
					if (type->isCharType() || type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
					{
						AddInstruction(SetConv, getSizeOfType(type));
					}
				}


				if (call->getDirectCallee() && call->getDirectCallee()->hasAttr<NativeFuncAttr>())
				{
					NativeFuncAttr *attr = call->getDirectCallee()->getAttr<NativeFuncAttr>();

					if (call->getDirectCallee()->getStorageClass() != SC_Extern)
					{
						Throw("Natives should be defined with the 'extern' keyword", rewriter, call->getDirectCallee()->getLocation());
					}
					const QualType type = call->getDirectCallee()->getReturnType();
					int pCount = 0;
					for (unsigned i = 0; i < call->getDirectCallee()->getNumParams();i++)
					{
						pCount += getSizeFromBytes(getSizeOfType(call->getDirectCallee()->getParamDecl(i)->getType().getTypePtr()));
					}
					if (attr->getX64HiDwordHash() || attr->getHash())
					{
						//clang attribute arguments cannot be 64bits wide, so using 2 32 bit args can manually joining them is the nicest way to support pc
						//when using 32 bit(xbox/ps3) the hi dword would be 0 so can be neglected
						AddInstruction(Native, call->getDirectCallee()->getNameAsString(), ((uint64_t)attr->getX64HiDwordHash() << 32) | attr->getHash(), pCount, getSizeFromBytes(getSizeOfType(type.getTypePtr())));
					}
					else
					{
						AddInstruction(Native, call->getDirectCallee()->getNameAsString(), pCount, getSizeFromBytes(getSizeOfType(type.getTypePtr())));
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
						string name = getNameForFunc(cDecl);
						string curName = dumpName(cast<NamedDecl>(currFunction));
						if (cDecl->hasBody() && !scriptData.isFunctionInInlineStack(name) && curName != name)
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
										if (!scriptData.addFunctionInline(name, to_string(e->getLocEnd().getRawEncoding())))
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
											AddInstructionComment(SetFrame, "Inline Argument Setting",Index);
										}
										else if (paramSize > 1)
										{
											AddInstruction(PushInt, paramSize);
											AddInstruction(GetFrameP, Index);
											AddInstructionComment(FromStack, "Inline Argument Setting");
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
											if (scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()))
											{
												scriptData.getCurrentFunction()->RemoveLast();
												//remove the last jump, but keep the label, just incase other places in the function have returns
											}
											AddInstructionComment(Label, "Inline return location",scriptData.getInlineJumpLabelAppend());
										}
										LocalVariables.removeLevel();
										scriptData.removeFunctionInline(name);

									}
								}
							}
						}
					}
					if (!inlined)
					{
						string name = getNameForFunc(call->getDirectCallee());
						if (auto func = scriptData.getFunctionFromName(name))
						{
							AddInstructionComment(Call, "NumArgs: " + to_string(call->getNumArgs()), func);
						}
						else
							Throw("Function \"" + name + "\" not found", rewriter, call->getExprLoc());
						
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
							AddInstructionComment(PushInt, "Base+" + to_string(offset), offset / stackWidth);
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
							AddInstructionComment(PushInt, "Base+" + to_string(offset), offset / stackWidth);
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
						LocalVariables.addLevel();
						int index = LocalVariables.addDecl("DerefSavedVar", 1);
						AddInstruction(SetConv, size);

						parseExpression(subE, subE->getType().getTypePtr()->isArrayType(), true);
						AddInstruction(Dup);
						AddInstructionComment(SetFrame, "DerefSavedVar", index);

						AddInstruction(PGet);
						AddInstruction(PushInt, size == 1 ? 0xFFFFFF : 0xFFFF);
						AddInstruction(And);
						AddInstruction(Or);

						AddInstructionComment(GetFrame, "DerefSavedVar", index);
						LocalVariables.removeLevel();
						goto DerefPtrOnStack;
					}
				}
				
				if (isa<ArraySubscriptExpr>(subE))
					parseArraySubscriptExpr(subE, false, isArrToPtrDecay);
				else if (isa<DeclRefExpr>(subE))
					parseExpression(subE, false, false);
				else
					parseExpression(subE, false, true);

				DerefPtrOnStack:


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
				int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
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
					AddInstruction(Call, scriptData.getFunctionFromName(expr->getType()->getAsArrayTypeUnsafe()->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl()->getNameAsString() + "::VTableInit"));
				}
				else {
					AddInstruction(Dup);
					AddInstruction(Call, scriptData.getFunctionFromName(expr->getBestDynamicClassType()->getNameAsString() + "::VTableInit"));
				}
				//  out << " //End_VtableInit\n" << endl;
			}
			if (expr->getConstructor()->hasBody())
			{
				AddInstructionComment(Call, "ctor", scriptData.getFunctionFromName(getNameForFunc(expr->getConstructor())));
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
				case BO_RemAssign:  OpAssign(OK_Mod); break;
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
								int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
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
								int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
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
								int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
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

			int typeSize = getSizeFromBytes(getSizeOfType(E->getType().getTypePtr()));
			if ((isLtoRValue || !isAddr) && typeSize > 1)
			{
				AddInstructionComment(PushInt, "Type Size", typeSize);
			}


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
							offset += max(temp, stackWidth);
						}
					}
				}
			}

			AddInstructionComment(GetImmP, "." + ND->getName().str(), getSizeFromBytes(offset));
			if (isLtoRValue)
			{
				AddInstructionCondition(typeSize > 1, ToStack, PGet);
			}
			else if (isAddr)
			{
				return 1;
			}
			else
			{
				AddInstructionCondition(typeSize > 1, FromStack, PSet);
			}

			return 1;
		}
		else if (isa<InitListExpr>(e))
		{
			//{ 1, 3, 7 }; support
			if (isLtoRValue)
			{
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
								i += stackWidth;
							}
						}
						return 1;
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
							int curSize = getSizeFromBytes(i * 2) * stackWidth;
							while (curSize < size)
							{
								AddInstruction(PushInt, 0);
								curSize += stackWidth;
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
					curSize += stackWidth * getSizeFromBytes(getSizeOfType(init->getType().getTypePtr()));
					parseExpression(init, false, true);
				}
				while (curSize < size)
				{
					AddInstruction(PushInt, 0);
					curSize += stackWidth;
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
			if (isLtoRValue)
			{
				auto addrOf = cast<AddrLabelExpr>(e);
				AddJumpInlineCheckStr(LabelLoc, addrOf->getLabel()->getNameAsString());
			}
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
				size = getSizeFromBytes(size) * stackWidth;
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

			//if (f->getStorageClass() == SC_Static)


			int32_t paramSize = 0;
			for (uint32_t i = 0; i < f->getNumParams(); i++)
				paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));
			if (isa<CXXMethodDecl>(f))
				paramSize++;
			

			FunctionData* func = scriptData.createFunction(getNameForFunc(f), paramSize, getSizeFromBytes(getSizeOfType(f->getReturnType().getTypePtr())), true);
			auto identifier = f->getIdentifier();
			if (identifier && identifier->isStr("main"))//cant use f->isMain as its now freestanding exe
			{
				scriptData.setMainFunction(func);
			}
			if (f->hasAttr<UnsafeFuncAttr>())
			{
				func->setUnsafe();
			}

			currFunction = f;
			LocalVariables.reset();
			if (isa<CXXMethodDecl>(f))
				LocalVariables.addDecl("", 1);

			for (uint32_t i = 0; i<f->getNumParams(); i++)
				handleParmVarDecl(f->getParamDecl(i));

			LocalVariables.addDecl("", 2);//base pointer and return address
			parseStatement(FuncBody);

			if (f->getReturnType().getTypePtr()->isVoidType() && !func->endsWithReturn()) {
					AddInstruction(Return);
			}
			else if (f->hasImplicitReturnZero() && !func->endsWithReturn())
			{
				AddInstruction(PushInt, 0);
				AddInstruction(Return);
			}

			//Throw(f->getNameAsString() + ": not all control paths return a value", rewriter, f->getLocEnd());
			//uint32_t FunctionStackCount = LocalVariables.maxIndex - (isa<CXXMethodDecl>(f) ? 1 : 0) - paramSize;

			if (LocalVariables.maxIndex > 65536)
				Throw("Function \"" + f->getNameAsString() + "\" has a stack size of " + to_string(LocalVariables.maxIndex) + " when the max is 65536", rewriter, f->getLocStart());
			else
			{
				func->setStackSize(LocalVariables.maxIndex);
			}
			func->setProcessed();

			if(ObfuscateOption.size() == 4)
				func->codeLayoutRandomisation(ObfuscateOption[0], ObfuscateOption[1], static_cast<bool>(ObfuscateOption[2]), static_cast<bool>(ObfuscateOption[3]));
			
			scriptData.clearCurrentFunction();
		}
		else
		{
			if (f->hasAttrs())
			{
				if (f->hasAttr<NativeFuncAttr>() || f->hasAttr<IntrinsicFuncAttr>())
				{
					return false;
				}
				AttrVec vec = f->getAttrs();
				for(uint32_t i = 0; i < vec.size(); i++)
					cout << vec[i]->getSpelling() << endl;
			}
			int32_t paramSize = 0;
			for (uint32_t i = 0; i < f->getNumParams(); i++)
				paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));

			scriptData.createFunction(getNameForFunc(f), paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0), getSizeFromBytes(getSizeOfType(f->getReturnType().getTypePtr())), false, true);


			cout << "added prototype: " << f->getNameAsString() << endl;
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
			//                    offset+=stackWidth;
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
			//                offset += max(temp, stackWidth);
			//            }
		}

		for (CXXMethodDecl *VFI : classDecl->methods()) {
			if (VFI->isVirtualAsWritten()) {
				offset += stackWidth;
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
				offset += max(temp, stackWidth);
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
			uint32_t paramSize = 1;//class
			for (uint32_t i = 0; i < CS->getNumParams();i++)
			{
				paramSize += getSizeFromBytes(getSizeOfType(CS->getParamDecl(i)->getType().getTypePtr()));
			}
			auto ctor = scriptData.createFunction(CS->getDeclName().getAsString(), paramSize, getSizeFromBytes(getSizeOfType(CS->getReturnType().getTypePtr())), true);
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

			if (!scriptData.getCurrentFunction()->endsWithReturn())
			{
				AddInstruction(Return);
			}
			ctor->setProcessed();

			scriptData.clearCurrentFunction();

			out << "#FuncEnd L " << LocalVariables.getCurrentSize() - (isa<CXXMethodDecl>(CS) ? 1 : 0) << endl << endl;
			if (d->isPolymorphic()) {
				out << endl << endl;
				out << "Function 1 1 " << d->getNameAsString() << "::VTableInit" << endl;
				printVTableInit(d, NULL);
				out << "Return 1 0" << endl;
				out << "//Var Count 2" << endl;

			}
		}
		return true;
	}
	#pragma endregion

public:
	Rewriter &TheRewriter;
	ASTContext *context;
	stringstream out;//temp until CXX stuff sorted/removed

	const FunctionDecl *currFunction;
	Script& scriptData;
};

#pragma region GlobalsVisitor
class GlobalsVisitor : public RecursiveASTVisitor<GlobalsVisitor> {
public:
	GlobalsVisitor(Rewriter &R, ASTContext *context, Script& scriptData) : TheRewriter(R), context(context), scriptData(scriptData) {}

	string getNameForFunc(const FunctionDecl *decl) {

		string FileId = "";
		if (decl->getStorageClass() == SC_Static)
		{
			assert(CurrentFileId && "File id 0 reserved for extern");
			char buf[9] = {};
			FileId += string(itoa(CurrentFileId - 1, buf, 36)) += "~";
			//this works without collision going on the notion that no one can add "~" to a function name
			
		}

		if (isa<CXXMethodDecl>(decl)) {
			const CXXMethodDecl *methodDecl = cast<const CXXMethodDecl>(decl);
			const CXXRecordDecl *record = methodDecl->getParent();
			return FileId + record->getNameAsString() + "::" + methodDecl->getNameAsString();
		}
		else {
			return FileId + decl->getNameAsString();
		}
	}
	int32_t ParseLiteral(const Expr *e, bool isAddr = false, bool isLtoRValue = false)
	{
		Expr::EvalResult result;

		if (isa<ImplicitValueInitExpr>(e))
		{
			const ImplicitValueInitExpr *ivie = cast<const ImplicitValueInitExpr>(e);

			const Type* type = ivie->getType().getTypePtr();
			uint32_t size = getSizeFromBytes(getSizeOfType(type));

			scriptData.addStaticInit(0, size);
			scriptData.getCurrentStatic()->pushNullInit(size, scriptData.getStackWidth());
			return true;
		}
		else if (e->EvaluateAsRValue(result, *context))
		{
			if (!isLtoRValue)
			{
				Warn("Static value was dropped");
				return -1;
			}
			if (result.Val.isInt())
			{
				
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
						scriptData.addStaticInit();

					scriptData.modifyLastInitStaticByte(resValue, intIndex);

					if (++intIndex >= stackWidth)
						intIndex = 0;

					scriptData.getCurrentStatic()->pushInit8(resValue);
				}
				else if (type->isSpecificBuiltinType(BuiltinType::Kind::Short) || type->isSpecificBuiltinType(BuiltinType::Kind::UShort))
				{
					if (intIndex == 0)
						scriptData.addStaticInit();

					scriptData.modifyLastInitStaticShort(resValue, intIndex);

					intIndex += 2;
					if (intIndex >= stackWidth)
						intIndex = 0;
					scriptData.getCurrentStatic()->pushInit16(resValue, scriptData.getEndian());
				}
				else if (isCurrentExprEvaluable)
				{
					scriptData.addStaticInit((int32_t)resValue);//remove later
					scriptData.getCurrentStatic()->pushInit32(resValue, scriptData.getEndian());
					scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				}
				else
				{
					scriptData.getCurrentStatic()->addOpPushInt(resValue);
				}

				return true;
			}
			else if (result.Val.isFloat())
			{
				if (isCurrentExprEvaluable)
				{
					scriptData.addStaticInit(FloatToInt((float)extractAPFloat(result.Val.getFloat())));
					scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getFloat())), scriptData.getEndian());
				}
				else
				{
					scriptData.getCurrentStatic()->addOpPushFloat((float)extractAPFloat(result.Val.getFloat()));
				}
				return true;
			}
			else if (result.Val.isComplexFloat())
			{
				//can this be unevaluable?
				scriptData.addStaticInit(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatReal())));
				scriptData.addStaticInit(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatImag())));

				scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatReal())), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatImag())), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				return true;
			}
			else if (result.Val.isComplexInt())
			{
				//can this be unevaluable?
				scriptData.addStaticInit(result.Val.getComplexIntReal().getSExtValue());
				scriptData.addStaticInit(result.Val.getComplexIntImag().getSExtValue());


				scriptData.getCurrentStatic()->pushInit32(result.Val.getComplexIntReal().getSExtValue(), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				scriptData.getCurrentStatic()->pushInit32(result.Val.getComplexIntImag().getSExtValue(), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				return true;
			}
		}

		if (isa<StringLiteral>(e)) {
			const StringLiteral *literal = cast<const StringLiteral>(e);
			if (literal->getString().str().length() > 0)
			{
				scriptData.getCurrentStatic()->pushStringInit(literal->getString().str(), scriptData.getStackWidth() * getSizeFromBytes(getLiteralSizeOfType(e->getType().getTypePtr())));
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				string strlit = literal->getString().str();
				e->getType().getTypePtr();

				int32_t strsize = getLiteralSizeOfType(e->getType().getTypePtr());

				int32_t buffer = 0;
				int32_t i = 0, b = 0;
				for (; i < strsize; i++, b++)
				{
					if (b >= stackWidth)
					{
						scriptData.addStaticInitBig(buffer);
						b = 0;
						buffer = 0;

						if (i >= (int32_t)strlit.length())
						{
							scriptData.addStaticInit(0, Utils::Math::CeilDivInt(strsize - i, stackWidth));
							break;
						}
					}
					if (i >= (int32_t)strlit.length())
						((uint8_t*)&buffer)[b] = 0;//add padding
					else
						((uint8_t*)&buffer)[b] = strlit[i];

				}
				if (b != 0)
					scriptData.addStaticInitBig(buffer);

			}

			return true;
		}
		else if (isa<InitListExpr>(e))
		{
			const InitListExpr *I = cast<const InitListExpr>(e);
			uint32_t size = getSizeFromBytes(getSizeOfType(I->getType().getTypePtr()));
			uint32_t SavedStaticInc = scriptData.getStaticSize();
			size_t curSize = scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth());
			resetIntIndex();
			for (uint32_t i = 0; i < I->getNumInits(); i++)
			{
				isCurrentExprEvaluable = true;
				doesCurrentValueNeedSet = false;
				ParseLiteral(I->getInit(i), false, true);
				if (doesCurrentValueNeedSet)
				{
					scriptData.addStaticInit();//needs removing
					scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
				}
			}
			scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());

			resetIntIndex();
			isCurrentExprEvaluable = true;
			doesCurrentValueNeedSet = false;

			if (scriptData.getStaticSize() - SavedStaticInc < size)
			{
				//cout << "init list size is less adding " << size - (oldStaticInc - SavedStaticInc) << " size: " << size << endl;

				scriptData.addStaticInit(0, size - (scriptData.getStaticSize() - SavedStaticInc));
			}
			if (scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth()) - curSize < size)
			{
				scriptData.getCurrentStatic()->pushNullInit(size -(scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth()) - curSize), scriptData.getStackWidth());
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
					StaticData* staticData = scriptData.findStatic(DRE->getDecl()->getLocEnd().getRawEncoding());
					assert(staticData && "Static Not Found");
					scriptData.getCurrentStatic()->addOpGetStaticP(staticData);
					scriptData.getCurrentStatic()->setDynamic();
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
					scriptData.getCurrentStatic()->addOpPushString(literal->getString().str());
					scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
					scriptData.getCurrentStatic()->setDynamic();
					scriptData.addStaticInit();//prevents errors with old methods
				}
				else if (isa<DeclRefExpr>(icast->getSubExpr()))//int vstack[10] = {1,2,3,4,5,6,7,8,9,10}, *vstack_ptr = vstack;
				{
					const DeclRefExpr *DRE = cast<const DeclRefExpr>(icast->getSubExpr());
					doesCurrentValueNeedSet = true;

					//we can index because the name has to be declared in clang to use the declare, we will let clang handle errors
					StaticData* staticData = scriptData.findStatic(DRE->getDecl()->getLocEnd().getRawEncoding());
					assert(staticData && "Static Not Found");
					scriptData.getCurrentStatic()->addOpGetStaticP(staticData);
					scriptData.getCurrentStatic()->setDynamic();
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
						
						auto function = scriptData.getFunctionFromName(getNameForFunc(decl));
						if (!function)
							Throw("Static function pointer \"" + decl->getNameAsString() + "\" not found");

						scriptData.addStaticInit();
						//New Handling
						scriptData.getCurrentStatic()->addOpFuncLoc(function);
						scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
						scriptData.getCurrentStatic()->setDynamic();

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
					int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
					int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;
					auto cur = scriptData.getCurrentStatic();
					cur->setDynamic();
					if (bOp->getLHS()->getType()->isFloatingType())
						cur->addOpFSub();
					else
						cur->addOpSub();


					if (pSize > 1)
					{
						cur->addOpPushInt(pSize);
						cur->addOpDiv();
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
					int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
					int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

					if (pSize > 1)
						scriptData.getCurrentStatic()->addOpMultImm(pSize);
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
					int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
					int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

					if (pSize > 1)
						scriptData.getCurrentStatic()->addOpMultImm(pSize);
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
				case BO_Sub: scriptData.getCurrentStatic()->addOpSub();  break;
				case BO_Add: scriptData.getCurrentStatic()->addOpAdd(); break;
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
					auto cur = scriptData.getCurrentStatic();
					cur->setDynamic();
					if (!inc)
					{
						cur->addOpGetStaticP(scriptData.findStatic(declRef->getDecl()->getLocEnd().getRawEncoding()));
					}

					if (!ssize)
					{
						uint32_t elementSize = stackWidth;
						if (type->isArrayType())
							elementSize = getSizeOfType(base->getType()->getArrayElementTypeNoTypeQual());

						cur->addOpAddImm(iResult.getSExtValue() * elementSize);
					}
					else
					{
						cur->addOpAddImm(ssize * iResult.getSExtValue());
					}

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
		else if (isa<MemberExpr>(e))
		{
			if (!isAddr)
			{
				Throw("Can only get address of members for static defines", rewriter, e->getExprLoc());
			}
			auto cur = scriptData.getCurrentStatic();
			doesCurrentValueNeedSet = true;
			const MemberExpr *E = cast<const MemberExpr>(e);
			Expr *BaseExpr = E->getBase();


			if (E->isArrow()) {
				ParseLiteral(BaseExpr, false, true);
			}
			else
				ParseLiteral(BaseExpr, true);


			int offset = 0;
			NamedDecl *ND = E->getMemberDecl();



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
						offset += max(temp, stackWidth);
					}
				}
			}
			cur->addOpGetImmP(getSizeFromBytes(offset));
			cur->setDynamic();
			return 1;
		}
		else if (isa<DeclRefExpr>(e))
		{
			auto declRef = cast<DeclRefExpr>(e);
			if (isAddr)
			{
				if (auto varDecl = dyn_cast_or_null<VarDecl>(declRef->getFoundDecl()))
				{
					scriptData.getCurrentStatic()->addOpGetStaticP(scriptData.findStatic(varDecl->getLocEnd().getRawEncoding()));
					scriptData.getCurrentStatic()->setDynamic();
					return 1;
				}else
				{
					Throw("DeclRefExpr error", rewriter, e->getSourceRange());
				}
			}
			else
			{
				Throw("DeclRefExpr error", rewriter, e->getSourceRange());
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
				//globalVarDecl->getStorageClass() == SC_Static
				if (globalVarDecl->hasAttr<GlobalVariableAttr>())
				{
					if (globalVarDecl->getStorageClass() == SC_None)
					{
						if (globalVarDecl->hasInit())
						{
							Throw("Global variables cannot be initialised", rewriter, D->getSourceRange());
						}
					}
					else
					{
						Throw("Global variables cannot have a storage class associated with them", rewriter, globalVarDecl->getSourceRange());
					}
					
				}
				else
				{
					uint32_t staticLoc = globalVarDecl->getLocEnd().getRawEncoding();// +dumpName(cast<NamedDecl>(D));

					if (statics.find(staticLoc) == statics.end()) {

						auto size = getSizeOfType(globalVarDecl->getType().getTypePtr());
						scriptData.addStaticNewDecl(staticLoc, dumpName(cast<NamedDecl>(D)), getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())));
						resetIntIndex();
						savedType = nullptr;

						isCurrentExprEvaluable = true;
						doesCurrentValueNeedSet = false;

						statics.insert({ staticLoc, {staticInc, dumpName(cast<NamedDecl>(D))} });

						scriptData.addStaticDecl(getSizeFromBytes(size));
						staticInc += getSizeFromBytes(size);

						const Expr *initializer = globalVarDecl->getAnyInitializer();


						if (initializer) {

							ParseLiteral(initializer, false, true);

							if (scriptData.getStaticSize() > staticInc)//undefined length arrays (should check if it is an undefined length array)
								staticInc = scriptData.getStaticSize();

							if (doesCurrentValueNeedSet)
							{
								scriptData.addStaticInit();
								scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
							}
							scriptData.getCurrentStatic()->fillCapacity(scriptData.getStackWidth());
						}
						else
						{
							scriptData.fillStaticCapacity();
							scriptData.getCurrentStatic()->fillCapacity(scriptData.getStackWidth());
						}


						if (scriptData.getStaticSize() > staticInc)
							Warn("Static Overflow Old:" + to_string(scriptData.getStaticSize()) + " New:" + to_string(staticInc));

						if (scriptData.getStaticSize() != scriptData.getStaticCapacity())
							Throw("not all values in static decl were initialized");

					}
					else
						Throw("Var " + dumpName(cast<NamedDecl>(D)) + " is already defined", rewriter, D->getLocStart());
				}
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

	inline void resetIntIndex()
	{
		if (intIndex != 0)
			intIndex = 0;
	}

	VarDecl* globalVarDecl;
	uint32_t intIndex = 0;
	Type* savedType = nullptr;
	bool isCurrentExprEvaluable = true;
	bool doesCurrentValueNeedSet = false;

private:
	Rewriter &TheRewriter;
	ASTContext *context;
	Script& scriptData;
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
	MyASTConsumer(Rewriter &R, ASTContext *context, Script& scriptData) : Visitor(R, context, scriptData), GlobalsVisitor(R, context, scriptData), scriptData(scriptData) {}

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
	}

private:
	MyASTVisitor Visitor;
	GlobalsVisitor GlobalsVisitor;
	Script &scriptData;
};
#pragma endregion

#pragma region CreateASTConsumer
class MyFrontendAction : public ASTFrontendAction {
public:
	MyFrontendAction()
	{
		CurrentFileId++;
	}
	~MyFrontendAction()
	{ 
		cout << "class ended\n";

		//this should not be needed anymore
		if (diagnostics->getClient()->getNumErrors())
			exit(EXIT_FAILURE);
	}
	void EndSourceFileAction() override {

		cout << "file ended\n";
		
	}
	
	void AddDefines(Preprocessor &PP)
	{
		string preDefines = PP.getPredefines();
		switch (scriptData->getBuildType())
		{
			case BT_GTAIV://it would be cool to support gta 4 at some point but its not a priority
				preDefines += "\n#define __GTAIV__";
				preDefines += "\n#define __SCO__";
				break;
			case BT_RDR_XSC:
				preDefines += "\n#define __RDR__"; 
				preDefines += "\n#define __" + scriptData->getPlatformAbvUpper() + string("SC__");
				break;
			case BT_RDR_SCO:
				preDefines += "\n#define __RDR__";
				preDefines += "\n#define __SCO__";
				break;
			case BT_GTAV:
				preDefines += "\n#define __GTAV__";
				preDefines += "\n#define __" + scriptData->getPlatformAbvUpper() + string("SC__");
				break;
		}

		PP.setPredefines(preDefines.data());
	}
	void ModifyClangWarnings(DiagnosticsEngine& DE)
	{
		#define DisableClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Ignored, SourceLocation());
		#define ElevateClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Error, SourceLocation());
		
		DisableClangWarning("main-return-type");
		DisableClangWarning("incompatible-library-redeclaration");
		ElevateClangWarning("return-type");
		ElevateClangWarning("dangling-else");
		
		#undef DisableClangWarning
		#undef ElevateClangWarning
	}
	
	
	std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override {
		llvm::errs() << "Compiling: " << file << "\n";

		diagnostics = &CI.getDiagnostics();
		CI.getLangOpts().Freestanding = true;

		TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
		rewriter = TheRewriter;

		//const SourceManager &SM = TheRewriter.getSourceMgr();
		//string fileName(string(SM.getFileEntryForID(SM.getMainFileID())->getName()));

		//is CompilerInstance constant? if so these can be done once instead of being applied every file
		ModifyClangWarnings(*diagnostics);
		AddDefines(CI.getPreprocessor());

		return llvm::make_unique<MyASTConsumer>(TheRewriter, &CI.getASTContext(), *scriptData);
	}

private:
	DiagnosticsEngine* diagnostics = NULL;
	Rewriter TheRewriter;
	string outDir;
};
#pragma endregion


void WriteAsmFile(string outDir)
{
	string Out = outDir  + scriptData->getASMFileName();
	FILE* file = fopen(Out.data(), "wb");
	if (file != NULL)
	{
		string StaticData = scriptData->getStaticsAsString();

		StaticData.reserve(StaticData.size() + 45 * statics.size());
		for (auto item : statics)
			StaticData += "SetStaticName " + to_string(item.second.index) + " " + to_string(item.first) + "//" + item.second.name + "\r\n";

		fwrite(StaticData.data(), 1, StaticData.size(), file);
		StaticData.clear();
		//this needs tidying up and when ready removing the first statics method
		string staticData2 = "/*\r\n" + scriptData->getNewStaticsAsString() + "\r\n*/\r\n";
		fwrite(staticData2.data(), 1, staticData2.size(), file);

		for (uint32_t i = 0, max = scriptData->getFunctionCount(); i <max; i++)
		{
			auto func = scriptData->getFunctionFromIndex(i);
			if (func->IsUsed())
			{
				assert(func->isProcessed() && "Function Prototype Implementation missing on referenced function");
				string fStr = func->toString();
				fwrite(fStr.c_str(), 1, fStr.size(), file);
			}
		}
		fclose(file);
	}
	else Throw("Output File \"" + Out + "\" Could Not Be Opened");

}

void WriteScriptFile(string outDir)
{
	switch (scriptData->getBuildType())
	{
		case BT_RDR_XSC:
		case BT_RDR_SCO:
		{
			switch (scriptData->getBuildPlatform())
			{
				case P_XBOX:
				case P_PS3:
				{
					CompileRDR c(*scriptData);
					c.Compile(outDir);
				}
				break;
				default:
				Throw("Red dead redemption only supported on Xbox360 and PS3");
			}
		}
		break;
		case BT_GTAV:
		{
			switch (scriptData->getBuildPlatform())
			{
				case P_XBOX:
				case P_PS3:
				{
					CompileGTAV c(*scriptData);
					c.Compile(outDir);
				}
				break;
				case P_PC:
				{
					CompileGTAVPC c(*scriptData, to_string(PCVerisonOption));
					c.Compile(outDir);
				}
				break;
				default:
				Throw("GTA V only supported on Xbox360 and PS3");
			}
		}
		break;
		default:
		Throw("Unsupported Build Platform");
	}
}

string GetBaseNameFromDir(string &Dir)
{
	const size_t BaseStartPos = Dir.find_last_of("/\\") + 1;
	const size_t BaseExtPos = Dir.find_last_of('.');
	if (BaseExtPos == Dir.npos)
		return "Script";
	else if (BaseStartPos == Dir.npos)
		return Dir.substr(BaseStartPos, BaseExtPos);
	return Dir.substr(BaseStartPos, BaseExtPos - BaseStartPos);
}
string GetDir(const string &Dir)
{
	const size_t BaseExtPos = Dir.find_last_of("/\\") + 1;
	return BaseExtPos == Dir.npos ? "" : Dir.substr(0, BaseExtPos);
}

int main(int argc, const char **argv) {
	
	globalDirectory = GetDir(string(argv[0]));

	CommonOptionsParser op(argc, argv, OptCategory, " XSC-CL\n");
	ClangTool Tool(op.getCompilations(), op.getSourcePathList());
	bool ProcessingFailed = true;


	/// ClangTool::run accepts a FrontendActionFactory, which is then used to
	/// create new objects implementing the FrontendAction interface. Here we use
	/// the helper newFrontendActionFactory to create a default factory that will
	/// return a new MyFrontendAction object every time.
	/// To further customize this, we could create our own factory class.
	
	if (op.getSourcePathList().size() > 0)
	{
		//this is temporary. script name should be set from the file that the main function is in
		
		string outDir = GetDir(op.getSourcePathList()[0]);
		string scriptName = GetBaseNameFromDir(op.getSourcePathList()[0]);
		scriptData.reset(new Script(scriptName, BuildTypeOption, PlatformOption));

		if(SingletonOption)
			scriptData->setSingleton();
		
		stackWidth = scriptData->getStackWidth();

		cout << "Starting Clang 3.8.1\r\n";
		ProcessingFailed = Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
		if (!ProcessingFailed)
		{
			//ProcessingSuccess
			scriptData->finaliseEntryFunction();
			
			WriteAsmFile(outDir);
			WriteScriptFile(outDir);

		}
		else
		{
			//ProcessingFailed
		}
	}

	return (int)ProcessingFailed;
}
