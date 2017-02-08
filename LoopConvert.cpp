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

#pragma region Global_Defines
#undef ReplaceText//(commdlg.h)
#define MultValue(pTypePtr) (pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth)
#define GetInsPtr(opName) &FunctionData::addOp##opName
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

#pragma region Global_Decls
string globalDirectory;
const string Version = "0.0.0";
#pragma endregion

#pragma region Global_Misc_Clang_Decls
static cl::OptionCategory ClangOptions("Clang Options");
static cl::OptionCategory CompilerOptions("Compiler Options");

static cl::opt<bool> Help("h", cl::desc("Alias for -help"), cl::Hidden);
static cl::opt<std::string> BuildPath("p", cl::desc("Build path"), cl::Optional, cl::cat(ClangOptions));
static cl::list<std::string> SourcePaths(cl::Positional, cl::desc("<source0> [... <sourceN>]"), cl::cat(ClangOptions));
static cl::list<std::string> ArgsAfter("extra-arg", cl::desc("Additional argument to append to the compiler command line"), cl::cat(ClangOptions));
static cl::list<std::string> ArgsBefore("extra-arg-before", cl::desc("Additional argument to prepend to the compiler command line"), cl::cat(ClangOptions));


static cl::opt<Platform> Option_Platform(
	"platform", cl::desc("Choose target platform:"),
	cl::Required,
	cl::ValueRequired,
	cl::cat(CompilerOptions),
	cl::values(
	clEnumValN(Platform::P_XBOX, "XBOX", "Target Xbox (32 bit, big endian)"),
	clEnumValN(Platform::P_PS3, "PS3", "Target PS3 (32 bit, big endian)"),
	clEnumValN(Platform::P_PC, "PC", "Target PC (64 bit, little endian)"),
	clEnumValEnd
));
static cl::opt<BuildType> Option_BuildType(
	"build_type", cl::desc("Choose build type:"),
	cl::Required,
	cl::ValueRequired,
	cl::cat(CompilerOptions),
	cl::values(
	//clEnumValN(BuildType::BT_GTAIV, "XBOX", "Grand Theft Auto IV (sco output)"),
	clEnumValN(BuildType::BT_GTAV, "GTAV", "Grand Theft Auto V (#sc output)"),
	clEnumValN(BuildType::BT_RDR_SCO, "RDR_SCO", "Red Dead Redemption (sco output)"),
	clEnumValN(BuildType::BT_RDR_XSC, "RDR_XSC", "Red Dead Redemption (#sc output)"),
	clEnumValEnd
));

static cl::opt<std::string> Option_OutputFileName(
	"name", cl::desc("File name of output script, defaults to input file name"),
	cl::ValueRequired,
	cl::cat(CompilerOptions));

typedef enum ObfLevel { 
	obf_none,
	obf_low = 1, //low: int maxBlockSize = 50, int minBlockSize = 30, bool keepEndReturn = true, bool makeJumpTable = false
	obf_default = 2, //default: int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = false
	obf_high = 3, //high: int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = true
	obf_veryhigh = 4, //very high: int maxBlockSize = 15, int minBlockSize = 5, bool keepEndReturn = false, bool makeJumpTable = true
	obf_max = 5, //max: int maxBlockSize = 5, int minBlockSize = 1, bool keepEndReturn = false, bool makeJumpTable = true
} ObfLevel;

static cl::opt<ObfLevel> Option_ObfuscationLevel(
	cl::desc("Choose obfuscation level:"),
	cl::cat(CompilerOptions),
	cl::values(
	clEnumValN(obf_low, "F1", "Enable low obfuscations"),
	clEnumValN(obf_default, "F2", "Enable default obfuscations"),
	clEnumValN(obf_high, "F3", "Enable high obfuscations"),
	clEnumValN(obf_veryhigh, "F4", "Enable very high obfuscations"),
	clEnumValN(obf_max, "F5", "Enable max obfuscations"),
	clEnumValEnd
));

static cl::opt<uint32_t> Option_PCVerison(
	"pc_version", cl::desc("Sets the pc version for use in the native translation table"),
	cl::ValueRequired,
	cl::cat(CompilerOptions)
);
static cl::opt<OptimisationLevel> Option_OptimizationLevel(
	cl::desc("Choose optimization level:"),
	cl::cat(CompilerOptions),
	cl::values(
	clEnumValN(OptimisationLevel::OL_None, "g","No optimizations, enable debugging"),
	clEnumValN(OptimisationLevel::OL_Trivial, "O1", "Enable trivial optimizations"),
	clEnumValN(OptimisationLevel::OL_Normal, "O2", "Enable default optimizations"),
	clEnumValN(OptimisationLevel::OL_Full, "O3", "Enable expensive optimizations"),
	clEnumValEnd
));

#pragma region Bool_Group
//Grouping is for multi bool set support ex: -snb
static cl::opt<bool> Option_Singleton(
	"s", cl::desc("Limits script to one instance on runtime (GTAV)"),
	cl::Grouping,
	cl::cat(CompilerOptions)
);
static cl::opt<bool> Option_DisableFunctionNames(
	"n", cl::desc("Disable function names in script output, Enabled when optimisations are turned on"),
	cl::Grouping,
	cl::cat(CompilerOptions)
);
static cl::opt<bool> Option_EntryFunctionPadding(//TODO: if selected set static initializers in code
	"b", cl::desc("Adds buffer to the entry function to allow script injection"),
	cl::Hidden,
	cl::Grouping,
	cl::cat(CompilerOptions)
);
#pragma endregion

//static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
//static cl::extrahelp ProgramHelp("\nTemp text...\n");

static Rewriter rewriter;
#pragma endregion

#pragma region Global_Var_and_Scope_Decls
unique_ptr<Script> scriptData = nullptr;
uint32_t CurrentFileId = 0;
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
	bool find(const string& key, uint32_t* outIndex)
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
	int addDecl(const string& key, int size)//size being number of 4 byte variables it takes up
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

			const Type* type = CS->getType().getTypePtr();
			int temp = getSizeOfType(type);
			temp = max(temp, stackWidth);

			if (temp > (int)offset)
				offset = temp;

		}
	}
	else {
		for (const FieldDecl *CS : classDecl->fields()) {
			if (CS->Decl::isFirstDecl() == false)
				continue;
			const Type* type = CS->getType().getTypePtr();
			int temp = getSizeOfType(type);
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
	void printDeclWithKey(const string& key, bool isAddr, bool isLtoRValue, bool isAssign, const DeclRefExpr* declref) {
		uint32_t index = -1;
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
				AddInstructionComment(GetFrame, key, index);
				if (size == 1 || size == 2)
				{
					AddInstruction(GetConv, scriptData, size, declref->getType()->isSignedIntegerType());
				}
			}
			else if (isAddr)
			{
				AddInstructionComment(GetFrameP, key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				
				if (size > stackWidth)//fromStack
				{
					AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
					AddInstructionComment(GetFrameP, key, index);
					AddInstruction(FromStack);
				}
				else
				{
					if (size == 1 || size == 2)
					{
						AddInstruction(SetConv, scriptData, size);
					}
					AddInstructionComment(SetFrame, key, index);
				}

			}
		}
		else if (varDecl && varDecl->hasAttr<GlobalVariableAttr>()) {
			index = varDecl->getAttr<GlobalVariableAttr>()->getIndex();
			if (isLtoRValue && !isAddr)
			{
				AddInstructionComment(GetGlobal, key, index);
				if (size == 1 || size == 2)
				{
					AddInstruction(GetConv, scriptData, size, declref->getType()->isSignedIntegerType());
				}
			}
			else if (isAddr)
			{
				AddInstructionComment(GetGlobalP, key, index);
			}
			else if (isAssign)
			{
				//this for single var setting (and or) for data preservation is not needed
				
				if (size > stackWidth)//fromStack
				{
					AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
					AddInstructionComment(GetGlobalP, key, index);
					AddInstruction(FromStack);
				}
				else
				{
					if (size == 1 || size == 2)
					{
						AddInstruction(SetConv, scriptData, size);
					}
					AddInstructionComment(SetGlobal, key, index);
				}
			}
		}
		else if (auto sData = scriptData.findStatic(dumpName(cast<NamedDecl>(declref->getDecl())))) {

			scriptData.getCurrentFunction()->addUsedStatic(sData);
			if (isLtoRValue && !isAddr)
			{
				AddInstructionComment(GetStatic, key, sData);
				if (size == 1 || size == 2)
				{
					AddInstruction(GetConv, scriptData, size, declref->getType()->isSignedIntegerType());
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
					AddInstructionComment(GetStaticP, key, sData);
					AddInstruction(FromStack);
				}
				else
				{
					if (size == 1 || size == 2)
					{
						AddInstruction(SetConv, scriptData, size);
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
						AddInstructionComment(FuncLoc, string("DeclRefExpr, nothing else, so func it ") + string(type->getTypeClassName()) + " " + to_string(size), func);
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
				auto size = getSizeOfType(decl->getType().getTypePtr());
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
							AddInstructionComment(PushInt, "Type Size (init decl)", getSizeFromBytes(size));
							AddInstructionComment(GetFrameP, "&" + var->getNameAsString(), curIndex);
							AddInstruction(FromStack);
						}
						else {
							if (size == 1 || size == 2)
							{
								AddInstruction(SetConv, scriptData, size);
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
	bool EvaluateAsString(const Expr* cExpr, string& outStr)
	{
		Expr* expr = (Expr*)cExpr;
		while (isa<ImplicitCastExpr>(expr)) {
			const ImplicitCastExpr *icast = cast<const ImplicitCastExpr>(expr);
			expr = (Expr*)icast->getSubExpr();
		}
		if (isa<StringLiteral>(expr))
		{
			outStr = cast<const StringLiteral>(expr)->getString().str();
			return true;
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
		bool ret = false;

		
		#define ChkHashCol(str) if(strcmp(funcName.c_str(), str) != 0) goto _IntrinsicNotFound;
		#define BadIntrin else Throw("Intrinsic not correctly defined", rewriter, callee->getSourceRange());
		#define EvalFailed else Throw("Value must be a integer literal", rewriter, call->getSourceRange());
		#define EvalFailedFlt else Throw("Value must be a floating literal", rewriter, call->getSourceRange());
		#define EvalFailedStr else Throw("Value must be a string literal", rewriter, call->getSourceRange());
		#define BadIntrinArgC else Throw("Bad arg count", rewriter, call->getSourceRange());


		auto AddAsmIntrinsic = [&](const char* str, void(FunctionData::*func)(void)) -> void
		{
			if (strcmp(funcName.c_str(), str) != 0)
				Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
			if (argCount == 0 && callee->getReturnType()->isVoidType()) {
				(scriptData.getCurrentFunction()->*func)();
				ret = true;
				return;
			} BadIntrin
		};
		auto AddAsmIntrinsic8 = [&](const char* str, void(FunctionData::*func)(uint8_t)) -> void
		{
			if (strcmp(funcName.c_str(), str) != 0)
				Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
			if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType()) {
				APSInt apCount;
				if (argArray[0]->EvaluateAsInt(apCount, *context)) {
					(scriptData.getCurrentFunction()->*func)(apCount.getSExtValue());
					ret = true;
					return;
				} EvalFailed
			} BadIntrin
		};
		auto AddAsmIntrinsic16 = [&](const char* str, void(FunctionData::*func)(uint16_t)) -> void
		{
			if (strcmp(funcName.c_str(), str) != 0)
				Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
			if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType()) {
				APSInt apCount;
				if (argArray[0]->EvaluateAsInt(apCount, *context)) {
					(scriptData.getCurrentFunction()->*func)(apCount.getSExtValue());
					ret = true;
					return;
				} EvalFailed
			} BadIntrin
		};
		auto AddAsmIntrinsicLocal = [&](const char* str, void(FunctionData::*func)(uint16_t)) -> void
		{
			if (strcmp(funcName.c_str(), str) != 0)
				Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
			if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType())
			{
				string str;
				if (EvaluateAsString(argArray[0], str))
				{
					uint32_t index = 0;
					if (LocalVariables.find(str, &index))
					{
						(scriptData.getCurrentFunction()->*func)(index);
						scriptData.getCurrentFunction()->pushComment("(ASM Named Local) " + str);
						ret = true;
						return;
					}
					else
						Throw("varName \"" + str + "\" not found", rewriter, call->getSourceRange());
				} EvalFailedStr
			} BadIntrin
		};
		auto AddAsmIntrinsicStatic = [&](const char* str, void(FunctionData::*func)(StaticData*)) -> void
		{
			if (strcmp(funcName.c_str(), str) != 0)
				Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
			if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType())
			{
				string str;
				if (EvaluateAsString(argArray[0], str))
				{
					StaticData* data = scriptData.findStatic(str);
					if (data)
					{
						(scriptData.getCurrentFunction()->*func)(data);
						scriptData.getCurrentFunction()->pushComment("(ASM Named Static) " + str);
						ret = true;
						return;
					}
					else
						Throw("varName \"" + str + "\" not found", rewriter, call->getSourceRange());
				} EvalFailedStr
			} BadIntrin
		};
		auto AddAsmIntrinsic32 = [&](const char* str, void(FunctionData::*func)(int)) -> void
		{
			if (strcmp(funcName.c_str(), str) != 0)
				Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
			if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType()) {
				APSInt apCount;
				if (argArray[0]->EvaluateAsInt(apCount, *context)) {
					(scriptData.getCurrentFunction()->*func)(apCount.getSExtValue());
					ret = true;
					return;
				} EvalFailed
			} BadIntrin
		};
		auto AddAsmIntrinsicJump = [&](const char* str, void(FunctionData::*func)(const string&)) -> void
		{
			if (strcmp(funcName.c_str(), str) != 0)
				Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());

			if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType()) {
				string str;
				if (EvaluateAsString(argArray[0], str))
				{
					(scriptData.getCurrentFunction()->*func)(str + scriptData.getInlineJumpLabelAppend());
					ret = true;
					return;
				} EvalFailedStr
			} BadIntrin
		};


		switch (JoaatCased(const_cast<char*>(funcName.c_str())))
		{
			#pragma region String

			//isAddr is false on memory functions because we dont want to force addressof
			case JoaatCasedConst("memcpy"):{
				ChkHashCol("memcpy");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
				{
					llvm::APSInt apCount;
					int iCount;
					if (argArray[2]->EvaluateAsInt(apCount, *context) && (iCount = apCount.getSExtValue(), iCount > 0) && iCount % stackWidth == 0)
					{
						int itemCount = iCount / stackWidth;
						if (itemCount == 1)
						{
							
							parseExpression(argArray[1], false, true);
							AddInstruction(PGet);
							parseExpression(argArray[0], false, true);
							AddInstruction(PSet);
						}
						else {
							AddInstruction(PushInt, itemCount);
							parseExpression(argArray[1], false, true);
							AddInstruction(ToStack);
							AddInstruction(PushInt, itemCount);
							parseExpression(argArray[0], false, true);
							AddInstruction(FromStack);
						}
					}
					else
					{
						//TODO: fix for pc
						static uint32_t loopLblCount = -1;
						loopLblCount++;

						LocalVariables.addLevel();

						int destIndex = LocalVariables.addDecl("__memcpy-loop-dest", 1);
						int srcIndex = LocalVariables.addDecl("__memcpy-loop-src", 1);
						int sizeIndex = LocalVariables.addDecl("__memcpy-loop-size", 1);

						parseExpression(argArray[0], false, true);//dest
						AddInstruction(SetFrame, destIndex);

						parseExpression(argArray[1], false, true);//src
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
			} break;
			case JoaatCasedConst("memset"):{
				ChkHashCol("memset");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isCharType() && argArray[2]->getType()->isIntegerType())
				{
					static uint32_t loopLblCount = -1;
					loopLblCount++;

					llvm::APSInt sResult, vResult;
					if (argArray[2]->EvaluateAsInt(sResult, *context) && sResult.getSExtValue() % scriptData.getBuildPlatformSize() == 0 && argArray[1]->EvaluateAsInt(vResult, *context))
					{
						if (sResult.getSExtValue() <= 0)
							Throw("memset size must greater then 0", rewriter, callee->getSourceRange());
						if ((uint32_t)vResult.getExtValue() > 255)
							Throw("memset value must be a byte", rewriter, callee->getSourceRange());
						
						LocalVariables.addLevel();
						int destIndex = LocalVariables.addDecl("__memset-loop-dest", 1);
						int incIndex = LocalVariables.addDecl("__memset-loop-inc", 1);

						parseExpression(argArray[0], false, true);//dest
						AddInstruction(SetFrame, destIndex);
						AddInstruction(PushInt, 0);
						AddInstruction(SetFrame, incIndex);

						AddInstruction(Label, "__memset-loop-" + to_string(loopLblCount));
						AddInstruction(GetFrame, incIndex);
						AddInstruction(PushInt, sResult.getExtValue());
						AddInstruction(JumpGE, "__memset-loopend-" + to_string(loopLblCount));

						AddInstruction(PushInt, (uint8_t)vResult.getSExtValue());//value to set
						AddInstruction(GetFrame, destIndex);
						AddInstruction(GetFrame, incIndex);
						AddInstruction(Add);
						AddInstruction(PSet);

						AddInstruction(GetFrame, incIndex);
						AddInstruction(AddImm, scriptData.getBuildPlatformSize());
						AddInstruction(SetFrame, incIndex);
						AddInstruction(Jump, "__memset-loop-" + to_string(loopLblCount));
						AddInstruction(Label, "__memset-loopend-" + to_string(loopLblCount));
						LocalVariables.removeLevel();
					}
					else
					{

						//TODO: fix for pc
						
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
			} break;
			case JoaatCasedConst("strcpy"):{
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
						uint8_t iValue = result.getSExtValue();
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
			} break;
			case JoaatCasedConst("stradd"):{
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
						uint8_t iValue = result.getSExtValue();
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
			} break;
			case JoaatCasedConst("straddi"):{
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
						uint8_t iValue = result.getSExtValue();
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
			} break;
			case JoaatCasedConst("itos"):{
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
						uint8_t iValue = result.getSExtValue();
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
			} break;
			case JoaatCasedConst("getHashKey"): {
				ChkHashCol("getHashKey");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isCharType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(GetHash);
					return true;
				}
				Throw("getHashKey must have signature \"extern __intrinsic int getHashKey(char *string);\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			#pragma endregion
			#pragma region Misc_Opcodes
			case JoaatCasedConst("__varIndex"): {
				ChkHashCol("__varIndex");

				if (argCount == 1 && callee->getReturnType()->isIntegerType())
				{
					string str;
					if (EvaluateAsString(argArray[0], str))
					{
						uint32_t index = 0;
						StaticData* sData = NULL;
						if (LocalVariables.find(str, &index))
						{
							AddInstruction(PushInt, index);
							return true;
						}
						else if((sData = scriptData.findStatic(str)))
						{
							AddInstruction(PushInt, sData->getIndex());
							return true;
						}
						else
							Throw("__varIndex varName not found", rewriter, callee->getSourceRange());
					} EvalFailedStr
				}
				else Throw("__varIndex must have signature \"extern __unsafeIntrinsic const uint __varIndex(const char* varName);\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("__getReturnAddress"): {
				ChkHashCol("__getReturnAddress");

				if (argCount == 0 && callee->getReturnType()->isIntegerType()){
					AddInstruction(GetFrame, scriptData.getCurrentFunction()->getParamCount());
					return true;
				}
				else{
					Throw("__getReturnAddress must have signature \"extern __unsafeIntrinsic int __getReturnAddress();\"", rewriter, callee->getSourceRange());
				}
			} break;
			case JoaatCasedConst("__addressOFReturnAddress"): {
				ChkHashCol("__addressOFReturnAddress");

				if (argCount == 0 && callee->getReturnType()->isPointerType() && callee->getReturnType()->getPointeeType()->isIntegerType()){
					AddInstruction(GetFrameP, scriptData.getCurrentFunction()->getParamCount());
					return true;
				}
				else{
					Throw("__addressOFReturnAddress must have signature \"extern __unsafeIntrinsic int* __addressOFReturnAddress();\"", rewriter, callee->getSourceRange());
				}
			} break;
			#pragma endregion
			#pragma region Math/Conversions
			case JoaatCasedConst("reinterpretIntToFloat"): {
				ChkHashCol("reinterpretIntToFloat");
				if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isIntegerType())
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("reinterpretIntToFloat must have signature \"extern __intrinsic float reinterpretIntToFloat(int intValue);\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("reinterpretFloatToInt"): {
				ChkHashCol("reinterpretFloatToInt");
				if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("reinterpretFloatToInt must have signature \"extern __intrinsic int reinterpretFloatToInt(float floatValue);\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("toVector3"): {
				ChkHashCol("toVector3");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(FtoV);
					return true;
				}
				Throw("tovector3 must have signature \"extern __intrinsic vector3 tovector3(float value);\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector3Add"): {
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
			} break;
			case JoaatCasedConst("vector3Sub"): {
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
			} break;
			case JoaatCasedConst("vector3Mult"): {
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
			} break;
			case JoaatCasedConst("vector3Div"): {
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
			} break;
			case JoaatCasedConst("vector3Neg"): {
				ChkHashCol("vector3Neg");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					AddInstruction(VNeg);
					return true;
				}
				Throw("vector3Neg must have signature \"extern __intrinsic vector3 vector3Neg(vector3 vector)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector3Dot"): {
				ChkHashCol("vector3Dot");

				if (argCount == 2 && callee->getReturnType()->isRealFloatingType() && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
				{

					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					AddInstruction(VMult);
					AddInstruction(FAdd);
					AddInstruction(FAdd);
					return true;
				}
				Throw("vector3Dot must have signature \"extern __intrinsic float vector3Dot(vector3 left, vector3 right)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("toVector2"): {
				ChkHashCol("toVector2");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && argArray[0]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(Dup);
					return true;
				}
				Throw("tovector2 must have signature \"extern __intrinsic vector2 tovector2(float value);\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector2Add"): {
				ChkHashCol("vector2Add");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
				{

					parseExpression(argArray[0], false, true);
					AddInstruction(PushFloat, 0.0f);
					parseExpression(argArray[1], false, true);
					AddInstruction(PushFloat, 0.0f);
					AddInstruction(VAdd);
					AddInstruction(Drop);
					return true;
				}
				Throw("vector2Add must have signature \"extern __intrinsic vector2 vector2Add(vector2 left, vector2 right)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector2Sub"): {
				ChkHashCol("vector2Sub");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
				{
					parseExpression(argArray[0], false, true);
					AddInstruction(PushFloat, 0.0f);
					parseExpression(argArray[1], false, true);
					AddInstruction(PushFloat, 0.0f);
					AddInstruction(VSub);
					AddInstruction(Drop);
					return true;
				}
				Throw("vector2Sub must have signature \"extern __intrinsic vector2 vector2Sub(vector2 left, vector2 right)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector2Mult"): {
				ChkHashCol("vector2Mult");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
				{

					parseExpression(argArray[0], false, true);
					AddInstruction(PushFloat, 0.0f);
					parseExpression(argArray[1], false, true);
					AddInstruction(PushFloat, 0.0f);
					AddInstruction(VMult);
					AddInstruction(Drop);
					return true;
				}
				Throw("vector2Mult must have signature \"extern __intrinsic vector2 vector3Mult(vector2 left, vector2 right)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector2Div"): {
				ChkHashCol("vector2Div");

				if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
				{

					parseExpression(argArray[0], false, true);
					AddInstruction(PushFloat, 0.0f);
					parseExpression(argArray[1], false, true);
					AddInstruction(PushFloat, 0.0f);
					AddInstruction(VDiv);
					AddInstruction(Drop);
					return true;
				}
				Throw("vector2Div must have signature \"extern __intrinsic vector2 vector2Div(vector2 left, vector2 right)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector2Neg"): {
				ChkHashCol("vector2Neg");

				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2)
				{

					parseExpression(argArray[0], false, true);
					AddInstruction(PushFloat, 0.0f);
					AddInstruction(VNeg);
					AddInstruction(Drop);
					return true;
				}
				Throw("vector2Neg must have signature \"extern __intrinsic vector2 vector2Neg(vector2 vector)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("vector2Dot"): {
				ChkHashCol("vector2Dot");

				if (argCount == 2 && callee->getReturnType()->isRealFloatingType() && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
				{

					parseExpression(argArray[0], false, true);
					AddInstruction(PushFloat, 0.0f);
					parseExpression(argArray[1], false, true);
					AddInstruction(PushFloat, 0.0f);
					AddInstruction(VMult);
					AddInstruction(Drop);
					AddInstruction(FAdd);
					return true;
				}
				Throw("vector2Dot must have signature \"extern __intrinsic float vector2Dot(vector2 left, vector2 right)\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("fMod"): {
				ChkHashCol("fMod");
				if (argCount == 2 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType() && argArray[1]->getType()->isRealFloatingType())
				{
					parseExpression(argArray[0], false, true);
					parseExpression(argArray[1], false, true);
					AddInstruction(FMod);
					return true;
				}
			} break;
			case JoaatCasedConst("bit_test"): {
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
			} break;
			case JoaatCasedConst("bit_set"): {
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
			} break;
			case JoaatCasedConst("bit_reset"): {
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
			} break;
			case JoaatCasedConst("bit_flip"): {
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
			} break;
			case JoaatCasedConst("vector3ToVector2"): {
					ChkHashCol("vector3ToVector2");

					if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
					{

						parseExpression(argArray[0], false, true);
						AddInstruction(Drop);
						return true;
					}
					Throw("vector3ToVector2 must have signature \"extern __intrinsic vector2 vector3ToVector2(vector3 vector)\"", rewriter, callee->getSourceRange());
					return false;
				} break;
			case JoaatCasedConst("vector2ToVector3"): {
					ChkHashCol("vector2ToVector3");

					if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2)
					{

						parseExpression(argArray[0], false, true);
						AddInstruction(PushFloat, 0.0f);
						return true;
					}
					Throw("vector2ToVector3 must have signature \"extern __intrinsic vector3 vector2ToVector3(vector2 vector)\"", rewriter, callee->getSourceRange());
					return false;
				} break;
				case JoaatCasedConst("vector3Flatten"): {
						ChkHashCol("vector3Flatten");

						if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
						{
							parseExpression(argArray[0], false, true);
							AddInstruction(Drop);
							AddInstruction(PushFloat, 0.0f);
							return true;
						}
						Throw("vector3Flatten must have signature \"extern __intrinsic vector3 vector3Flatten(vector3 vector)\"", rewriter, callee->getSourceRange());
						return false;
					} break;
			#pragma endregion
			#pragma region Variables 
			case JoaatCasedConst("setStaticAtIndex"): {
				ChkHashCol("setStaticAtIndex");
				if (argCount == 2 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						parseExpression(argArray[1], false, true);
						AddInstruction(SetStaticRaw, result.getSExtValue());
						return true;
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("getStaticAtIndex"): {
				ChkHashCol("getStaticAtIndex");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						AddInstruction(GetStaticRaw, result.getSExtValue());
						return true;
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("getStaticPtrAtIndex"): {
				ChkHashCol("getStaticPtrAtIndex");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						AddInstruction(GetStaticPRaw, result.getSExtValue());
						return true;
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("setGlobalAtIndex"): {
				ChkHashCol("setGlobalAtIndex");
				if (argCount == 2 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						parseExpression(argArray[1], false, true);
						AddInstruction(SetGlobal, result.getSExtValue());
						return true;
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("getGlobalAtIndex"):{
				ChkHashCol("getGlobalAtIndex");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						AddInstruction(GetGlobal, result.getSExtValue());
						return true;
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("getGlobalPtrAtIndex"):{
				ChkHashCol("getGlobalPtrAtIndex");
				if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
				{
					llvm::APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context))
					{
						AddInstruction(GetGlobalP, result.getSExtValue());
						return true;
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("getPtrFromArrayIndex"):{
				ChkHashCol("getPtrFromArrayIndex");
				if (argCount == 3 && callee->getReturnType()->isPointerType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
				{
					llvm::APSInt itemSize;
					if (argArray[2]->EvaluateAsInt(itemSize, *context))
					{
						if (itemSize.getSExtValue() < 1 || itemSize.getSExtValue() > 0xFFFF)
							Throw("getPtrFromArrayIndex item size expected a value between 1 and 65535, got'" + to_string(itemSize.getSExtValue()) + "'", rewriter, argArray[2]->getSourceRange());
						
						llvm::APSInt index;
						if (Option_OptimizationLevel > OptimisationLevel::OL_Trivial && argArray[1]->EvaluateAsInt(index ,*context))
						{
							parseExpression(argArray[0], false, true);
							AddInstruction(GetImmP, 1 + itemSize.getSExtValue() * index.getSExtValue());
						}
						else
						{
							//get_arrayp
							parseExpression(argArray[1], false, true);
							parseExpression(argArray[0], false, true);
							AddInstruction(GetArrayP, itemSize.getSExtValue());
							return true;
						}
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("getPtrImmIndex"):{
				ChkHashCol("getPtrImmIndex");
				if (argCount == 2 && callee->getReturnType()->isPointerType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType())
				{
					APSInt index;
					if (argArray[1]->EvaluateAsInt(index, *context) && index.getSExtValue() >= 0 && index.getSExtValue() <= 0xFFFF)
					{
						parseExpression(argArray[0], false, true);
						AddInstructionComment(GetImmP, "imm_" + to_string(index.getSExtValue()), index.getSExtValue());
						return true;
					}
					else{
						parseExpression(argArray[0], false, true);
						parseExpression(argArray[1], false, true);
						AddInstruction(GetImmPStack);
						return true;
					}
				} BadIntrin
			} break;
			#pragma endregion
			#pragma region Custom_ASM
			case JoaatCasedConst("__popMult"): {
				ChkHashCol("__popMult");
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
			} break;
			case JoaatCasedConst("__pushV"): {
				ChkHashCol("__pushV");

				if (argCount == 1 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
				{
					parseExpression(argArray[0], false, true);
					return true;
				}
				Throw("pushVector3 must have signature \"extern __intrinsic void pushVector3(vector3 vec3Value);\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("__pushStruct"): {
				ChkHashCol("__pushStruct");
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isVoidPointerType())
				{
					if (isa<CastExpr>(argArray[0]))
					{
						const CastExpr *castee = cast<CastExpr>(argArray[0]);
						if (castee->getCastKind() == CK_BitCast)
						{
							int size = getSizeFromBytes(getSizeOfType(castee->getSubExpr()->getType()->getPointeeType().getTypePtr()));
							AddInstructionConditionallyComment(size > 1, PushInt, "Struct Size", size);
							parseExpression(argArray[0], false, true);
							AddInstructionCondition(size > 1, ToStack, PGet);
							return true;
						}
					}
					Throw("Couldnt extract type information from the argument in pushStruct", rewriter, argArray[0]->getSourceRange());
					return false;
				}
				Throw("pushStruct must have signature \"extern __intrinsic void pushStruct(void *Struct);\"", rewriter, callee->getSourceRange());
				return false;;
			} break;
			case JoaatCasedConst("__popStruct"): {
				ChkHashCol("__popStruct");

				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isVoidPointerType())
				{
					if (isa<CastExpr>(argArray[0]))
					{
						const CastExpr *castee = cast<CastExpr>(argArray[0]);
						if (castee->getCastKind() == CK_BitCast)
						{
							int size = getSizeFromBytes(getSizeOfType(castee->getSubExpr()->getType()->getPointeeType().getTypePtr()));
							AddInstructionConditionallyComment(size > 1, PushInt, "Struct Size", size);
							parseExpression(argArray[0], false, true);
							AddInstructionCondition(size > 1, FromStack, PSet);
							return true;
						}
					}
					Throw("Couldnt extract type information from the argument in popStruct", rewriter, argArray[0]->getSourceRange());
					return false;
				}
				Throw("popStruct must have signature \"extern __intrinsic void popStruct(void *Struct);\"", rewriter, callee->getSourceRange());
				return false;;
			} break;
			case JoaatCasedConst("__rev"): {
				ChkHashCol("__rev");

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
			} break;
			case JoaatCasedConst("__exch"): {
				ChkHashCol("__exch");

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
			} break;
			case JoaatCasedConst("__popI"): {
				ChkHashCol("__popI");
				if (argCount == 0 && callee->getReturnType()->isIntegerType())
				{
					return true;
				}
				Throw("popInt must have signature \"extern __intrinsic int pushInt();\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("__popF"): {
				ChkHashCol("__popF");
				if (argCount == 0 && callee->getReturnType()->isRealFloatingType())
				{
					return true;
				}
				Throw("popFloat must have signature \"extern __intrinsic float pushFloat();\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			case JoaatCasedConst("__popV"): {
				ChkHashCol("__popV");

				if (argCount == 0 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3)
				{
					return true;
				}
				Throw("popVector3 must have signature \"extern __intrinsic vector3 popVector3();\"", rewriter, callee->getSourceRange());
				return false;
			} break;
			#pragma endregion
			#pragma region ASM 
			case JoaatCasedConst("__nop"): {
				ChkHashCol("__nop");
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType()){
					APSInt result;
					if (argArray[0]->EvaluateAsInt(result, *context) && result.getSExtValue() > 0 && result.getSExtValue() <= 4096)
					{
						AddInstruction(Nop, result.getSExtValue());
						return true;
					}
					else
						Throw("nopCount argument must be a constant integer between 1 and 4096", rewriter, argArray[0]->getSourceRange());
				} BadIntrin
			} break;
			case JoaatCasedConst("__add"):			AddAsmIntrinsic("__add", GetInsPtr(Add)); break;
			case JoaatCasedConst("__sub"):			AddAsmIntrinsic("__sub", GetInsPtr(Sub)); break;
			case JoaatCasedConst("__mult"):			AddAsmIntrinsic("__mult", GetInsPtr(Mult)); break;
			case JoaatCasedConst("__div"):			AddAsmIntrinsic("__div", GetInsPtr(Div)); break;
			case JoaatCasedConst("__mod"):			AddAsmIntrinsic("__mod", GetInsPtr(Mod)); break;
			case JoaatCasedConst("__not"):			AddAsmIntrinsic("__not", GetInsPtr(Not)); break;
			case JoaatCasedConst("__neg"):			AddAsmIntrinsic("__neg", GetInsPtr(Neg)); break;
			case JoaatCasedConst("__cmpEq"):		AddAsmIntrinsic("__cmpEq", GetInsPtr(CmpEq)); break;
			case JoaatCasedConst("__cmpNe"):		AddAsmIntrinsic("__cmpNe", GetInsPtr(CmpNe)); break;
			case JoaatCasedConst("__cmpGt"):		AddAsmIntrinsic("__cmpGt", GetInsPtr(CmpGt)); break;
			case JoaatCasedConst("__cmpGe"):		AddAsmIntrinsic("__cmpGe", GetInsPtr(CmpGe)); break;
			case JoaatCasedConst("__cmpLt"):		AddAsmIntrinsic("__cmpLt", GetInsPtr(CmpLt)); break;
			case JoaatCasedConst("__cmpLe"):		AddAsmIntrinsic("__cmpLe", GetInsPtr(CmpLe)); break;
			case JoaatCasedConst("__addF"):			AddAsmIntrinsic("__addF", GetInsPtr(FAdd)); break;
			case JoaatCasedConst("__subF"):			AddAsmIntrinsic("__subF", GetInsPtr(FSub)); break;
			case JoaatCasedConst("__multF"):		AddAsmIntrinsic("__multF", GetInsPtr(FMult)); break;
			case JoaatCasedConst("__divF"):			AddAsmIntrinsic("__divF", GetInsPtr(FDiv)); break;
			case JoaatCasedConst("__modF"):			AddAsmIntrinsic("__modF", GetInsPtr(FMod)); break;
			case JoaatCasedConst("__negF"):			AddAsmIntrinsic("__negF", GetInsPtr(FNeg)); break;
			case JoaatCasedConst("__cmpEqF"):		AddAsmIntrinsic("__cmpEqF", GetInsPtr(FCmpEq)); break;
			case JoaatCasedConst("__cmpNeF"):		AddAsmIntrinsic("__cmpNeF", GetInsPtr(FCmpNe)); break;
			case JoaatCasedConst("__cmpGtF"):		AddAsmIntrinsic("__cmpGtF", GetInsPtr(FCmpGt)); break;
			case JoaatCasedConst("__cmpGeF"):		AddAsmIntrinsic("__cmpGeF", GetInsPtr(FCmpGe)); break;
			case JoaatCasedConst("__cmpLtF"):		AddAsmIntrinsic("__cmpLtF", GetInsPtr(FCmpLt)); break;
			case JoaatCasedConst("__cmpLeF"):		AddAsmIntrinsic("__cmpLeF", GetInsPtr(FCmpLe)); break;
			case JoaatCasedConst("__addV"):			AddAsmIntrinsic("__addV", GetInsPtr(VAdd)); break;
			case JoaatCasedConst("__subV"):			AddAsmIntrinsic("__subV", GetInsPtr(VSub)); break;
			case JoaatCasedConst("__multV"):		AddAsmIntrinsic("__multV", GetInsPtr(VMult)); break;
			case JoaatCasedConst("__divV"):			AddAsmIntrinsic("__divV", GetInsPtr(VDiv)); break;
			case JoaatCasedConst("__negV"):			AddAsmIntrinsic("__negV", GetInsPtr(VNeg)); break;
			case JoaatCasedConst("__and"):			AddAsmIntrinsic("__and", GetInsPtr(And)); break;
			case JoaatCasedConst("__or"):			AddAsmIntrinsic("__or", GetInsPtr(Or)); break;
			case JoaatCasedConst("__xor"):			AddAsmIntrinsic("__xor", GetInsPtr(Xor)); break;
			case JoaatCasedConst("__iToF"):			AddAsmIntrinsic("__iToF", GetInsPtr(ItoF)); break;
			case JoaatCasedConst("__fToI"):			AddAsmIntrinsic("__fToI", GetInsPtr(FtoI)); break;
			case JoaatCasedConst("__fToV"):			AddAsmIntrinsic("__fToV", GetInsPtr(FtoV)); break;
			case JoaatCasedConst("__push2"): {
				ChkHashCol("__push2");
				if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType()) {
					APSInt apCount;
					if (argArray[0]->EvaluateAsInt(apCount, *context)) {
						AddInstruction(PushInt, apCount.getSExtValue());
						if (argArray[1]->EvaluateAsInt(apCount, *context)) {
							AddInstruction(PushInt, apCount.getSExtValue());
							return true;
						} EvalFailed
					} EvalFailed
				}  BadIntrin
			} break;
			case JoaatCasedConst("__push3"): {
				ChkHashCol("__push3");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType()) {
					APSInt apCount;
					if (argArray[0]->EvaluateAsInt(apCount, *context)) {
						AddInstruction(PushInt, apCount.getSExtValue());
						if (argArray[1]->EvaluateAsInt(apCount, *context)) {
							AddInstruction(PushInt, apCount.getSExtValue());
							if (argArray[2]->EvaluateAsInt(apCount, *context)) {
								AddInstruction(PushInt, apCount.getSExtValue());
								return true;
							} EvalFailed
						} EvalFailed
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("__push"):			AddAsmIntrinsic32("__push", GetInsPtr(PushInt)); break;
			case JoaatCasedConst("__pushF"): {
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isRealFloatingType()) {
					Expr::EvalResult ER;
					if (argArray[0]->EvaluateAsRValue(ER, *context)) {
						AddInstruction(PushFloat, ER.Val.getFloat().convertToFloat());
						return true;
					} EvalFailed
				} BadIntrin
			} break;
			case JoaatCasedConst("__dup"):			AddAsmIntrinsic("__dup", GetInsPtr(Dup)); break;
			case JoaatCasedConst("__drop"):			AddAsmIntrinsic("__drop", GetInsPtr(Drop)); break;
			case JoaatCasedConst("__callNative"): {
				//TODO: add hash translation to pc
				ChkHashCol("__callNative");
				if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType()) {
					APSInt apCount, apCount1, apCount2;
					if (argArray[0]->EvaluateAsInt(apCount, *context)) {
						if (argArray[1]->EvaluateAsInt(apCount1, *context)) {
							if (argArray[2]->EvaluateAsInt(apCount2, *context)) {
								AddInstruction(Native, apCount.getSExtValue() & 0xFFFFFFFF, apCount1.getSExtValue(), apCount2.getSExtValue());
								return true;
							} EvalFailed
						} EvalFailed
					} EvalFailed
				}  BadIntrin
			} break;
			case JoaatCasedConst("__callNativePc"): {
				ChkHashCol("__callNativePc");
				if (argCount == 4 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType() && argArray[3]->getType()->isIntegerType()) {
					APSInt apCount, apCount1, apCount2, apCount3;
					if (argArray[0]->EvaluateAsInt(apCount, *context)) {
						if (argArray[1]->EvaluateAsInt(apCount1, *context)) {
							if (argArray[2]->EvaluateAsInt(apCount2, *context)) {
								if (argArray[3]->EvaluateAsInt(apCount2, *context)) {
									AddInstruction(Native, (apCount.getSExtValue() << 32) | apCount1.getSExtValue(), apCount2.getSExtValue(), apCount3.getSExtValue());
									return true;
								} EvalFailed
							} EvalFailed
						} EvalFailed
					} EvalFailed
				}  BadIntrin
			} break;
			case JoaatCasedConst("__return"): {
				ChkHashCol("__return");
				if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType()) {
					APSInt apCount, apCount1;
					if (argArray[0]->EvaluateAsInt(apCount, *context) && apCount.getSExtValue() <= 255) {
						if (argArray[1]->EvaluateAsInt(apCount1, *context) && apCount.getSExtValue() <= 255) {
							AddInstruction(Return, apCount.getSExtValue(), apCount1.getSExtValue());
							return true;
						} EvalFailed
					} EvalFailed
				}  BadIntrin
			} break;
			case JoaatCasedConst("__pGet"):			AddAsmIntrinsic("__pGet", GetInsPtr(PGet)); break;
			case JoaatCasedConst("__pSet"):			AddAsmIntrinsic("__pSet", GetInsPtr(PSet)); break;
			case JoaatCasedConst("__pPeekSet"):		AddAsmIntrinsic("__pPeekSet", GetInsPtr(PeekSet)); break;
			case JoaatCasedConst("__toStack"):		AddAsmIntrinsic("__toStack", GetInsPtr(ToStack)); break;
			case JoaatCasedConst("__fromStack"):	AddAsmIntrinsic("__fromStack", GetInsPtr(FromStack)); break;
			case JoaatCasedConst("__getArrayP"):	AddAsmIntrinsic16("__getArrayP", GetInsPtr(GetArrayP)); break;
			case JoaatCasedConst("__getArray"):		AddAsmIntrinsic16("__getArray", GetInsPtr(GetArray)); break;
			case JoaatCasedConst("__setArray"):		AddAsmIntrinsic16("__setArray", GetInsPtr(SetArray)); break;
			case JoaatCasedConst("__getFrameP"):	AddAsmIntrinsic16("__getFrameP", GetInsPtr(GetFrameP)); break;
			case JoaatCasedConst("__getNamedFrameP"):AddAsmIntrinsicLocal("__getNamedFrameP", GetInsPtr(GetFrameP)); break;
			case JoaatCasedConst("__getFrame"):		AddAsmIntrinsic16("__getFrame", GetInsPtr(GetFrame)); break;
			case JoaatCasedConst("__getNamedFrame"):AddAsmIntrinsicLocal("__getNamedFrame", GetInsPtr(GetFrame)); break;
			case JoaatCasedConst("__setFrame"):		AddAsmIntrinsic16("__setFrame", GetInsPtr(SetFrame)); break;
			case JoaatCasedConst("__setNamedFrame"):AddAsmIntrinsicLocal("__setNamedFrame", GetInsPtr(SetFrame)); break;
			case JoaatCasedConst("__getStaticP"):	AddAsmIntrinsic16("__getStaticP", GetInsPtr(GetStaticPRaw)); break;
			case JoaatCasedConst("__getNamedStaticP"):AddAsmIntrinsicStatic("__getNamedStaticP", GetInsPtr(GetStaticP)); break;
			case JoaatCasedConst("__getStatic"):	AddAsmIntrinsic16("__getStatic", GetInsPtr(GetStaticRaw)); break;
			case JoaatCasedConst("__getNamedStatic"):AddAsmIntrinsicStatic("__getNamedStatic", GetInsPtr(GetStatic)); break;
			case JoaatCasedConst("__setStatic"):	AddAsmIntrinsic16("__setStatic", GetInsPtr(SetStaticRaw)); break;
			case JoaatCasedConst("__setNamedStatic"):AddAsmIntrinsicStatic("__setNamedStatic", GetInsPtr(SetStatic)); break;
			case JoaatCasedConst("__addImm"):		AddAsmIntrinsic32("__addImm", GetInsPtr(AddImm)); break;
			case JoaatCasedConst("__multImm"):		AddAsmIntrinsic32("__multImm", GetInsPtr(MultImm)); break;
			case JoaatCasedConst("__getImmP"):		AddAsmIntrinsic16("__getImmP", GetInsPtr(GetImmP)); break;
			case JoaatCasedConst("__getImm"):		AddAsmIntrinsic16("__getImm", GetInsPtr(GetImm)); break;
			case JoaatCasedConst("__setImm"):		AddAsmIntrinsic16("__setImm", GetInsPtr(SetImm)); break;
			case JoaatCasedConst("__getGlobalP"):	AddAsmIntrinsic32("__getGlobalP", GetInsPtr(GetGlobalP)); break;
			case JoaatCasedConst("__getGlobal"):	AddAsmIntrinsic32("__getGlobal", GetInsPtr(GetGlobal)); break;
			case JoaatCasedConst("__setGlobal"):	AddAsmIntrinsic32("__setGlobal", GetInsPtr(SetGlobal)); break;
			case JoaatCasedConst("__switch"):{
				ChkHashCol("__switch");
				if (argCount >= 2 && callee->getReturnType()->isVoidType())
				{
					if (argCount >= 2 && argCount % 2 == 0)
					{
						APSInt apCount;
						string str;
						bool isSwitchOver255 = argCount >= 255 * 2;
						int SwitchCount = 1, tempSwitchIndex = 0;
						if (isSwitchOver255)
						{
							LocalVariables.addLevel();
							tempSwitchIndex = LocalVariables.addDecl("Switch Temp", 1);
							AddInstruction(Dup);
							AddInstructionComment(SetFrame, "Switch temporary variable", tempSwitchIndex);
							AddInstruction(Switch);
						}
						else
						{
							AddInstruction(Switch);
						}
						
						for (int i = 0; i < argCount; i+=2)
						{
							if (i >= (255 * 2) * SwitchCount)
							{
								AddInstructionComment(GetFrame, "Switch temporary variable", tempSwitchIndex);
								AddInstruction(Switch);
								SwitchCount++;
							}
							if (argArray[i]->EvaluateAsInt(apCount, *context)) {
								if (EvaluateAsString(argArray[i + 1], str))
								{
									scriptData.getCurrentFunction()->addSwitchCase(apCount.getSExtValue(), str + scriptData.getInlineJumpLabelAppend());

								} EvalFailedStr
							} EvalFailed
						}
						if(isSwitchOver255)
							LocalVariables.removeLevel();
						return true;
					} BadIntrinArgC
				} BadIntrin
			} break;
			case JoaatCasedConst("__jump"):			AddAsmIntrinsicJump("__jump", GetInsPtr(Jump)); break;
			case JoaatCasedConst("__jumpFalse"):	AddAsmIntrinsicJump("__jumpFalse", GetInsPtr(JumpFalse)); break;
			case JoaatCasedConst("__jumpNE"):		AddAsmIntrinsicJump("__jumpNE", GetInsPtr(JumpNE)); break;
			case JoaatCasedConst("__jumpEQ"):		AddAsmIntrinsicJump("__jumpEQ", GetInsPtr(JumpEQ)); break;
			case JoaatCasedConst("__jumpLE"):		AddAsmIntrinsicJump("__jumpLE", GetInsPtr(JumpLE)); break;
			case JoaatCasedConst("__jumpLT"):		AddAsmIntrinsicJump("__jumpLT", GetInsPtr(JumpLT)); break;
			case JoaatCasedConst("__jumpGE"):		AddAsmIntrinsicJump("__jumpGE", GetInsPtr(JumpGE)); break;
			case JoaatCasedConst("__jumpGT"):		AddAsmIntrinsicJump("__jumpGT", GetInsPtr(JumpGT)); break;
			case JoaatCasedConst("__call"): {
				ChkHashCol("__call");
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType()) {
					string str;
					if (EvaluateAsString(argArray[0], str))
					{
						if (FunctionData* func = scriptData.getFunctionFromName(str))//TODO:  check if this works with static functions
						{
							AddInstruction(Call, func);
							return true;
						}
						else
							Throw("__call: Function \"" + str + "\" not found", rewriter, call->getExprLoc());
						return true;
					} EvalFailedStr
				} BadIntrin
			} break;
			case JoaatCasedConst("__pushString"): {
				ChkHashCol("__pushString");
				if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType()) {
					string str;
					if (EvaluateAsString(argArray[0], str))
					{
						AddInstruction(PushString, str);
						return true;
					} EvalFailedStr
				} BadIntrin
			} break;
			case JoaatCasedConst("__getHash"):		AddAsmIntrinsic("__getHash", GetInsPtr(GetHash)); break;
			case JoaatCasedConst("__strCopy"):		AddAsmIntrinsic8("__strCopy", GetInsPtr(StrCopy)); break;
			case JoaatCasedConst("__iToS"):			AddAsmIntrinsic8("__iToS", GetInsPtr(ItoS)); break;
			case JoaatCasedConst("__strAdd"):		AddAsmIntrinsic8("__strAdd", GetInsPtr(StrAdd)); break;
			case JoaatCasedConst("__strAddI"):		AddAsmIntrinsic8("__strAddI", GetInsPtr(StrAddI)); break;
			case JoaatCasedConst("__memCopy"):		AddAsmIntrinsic("__memCopy", GetInsPtr(MemCopy)); break;
			case JoaatCasedConst("__pCall"):		AddAsmIntrinsic("__pCall", GetInsPtr(PCall)); break;


			#pragma endregion 

			default:
		_IntrinsicNotFound:
			Throw("No intrinsic function found named " + funcName, rewriter, callee->getLocation());
		}

		#undef ChkHashCol
		#undef BadIntrin
		#undef EvalFailed
		#undef EvalFailedStr
		#undef BadIntrinArgC
		return ret;
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
	void parseJumpFalse(const Expr* conditional, const string& jumpFalseLoc){
		const BinaryOperator* binaryOp;
		if ((binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens())) && binaryOp->getOpcode() == BO_LAnd){
				parseJumpFalse(binaryOp->getLHS(), jumpFalseLoc);
				parseJumpFalse(binaryOp->getRHS(), jumpFalseLoc);
		}
		else{
			parseExpression(conditional, false, true);
			AddJumpInlineCheckStr(JumpFalse, jumpFalseLoc);
		}
	}

	void parseCondition(const Expr* conditional, const string& trueLoc, const string& falseLoc){
		const BinaryOperator* binaryOp;
		if (binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens()))
		{
			switch (binaryOp->getOpcode()){
				case BO_LAnd:
					parseJumpFalse(binaryOp->getLHS(), falseLoc);
					//parseJumpFalse(binaryOp->getRHS(), falseLoc);
					parseCondition(binaryOp->getRHS(), trueLoc, falseLoc);
					break;
				case BO_LOr:
					parseJumpTrue(binaryOp->getLHS(), trueLoc);
					parseCondition(binaryOp->getRHS(), trueLoc, falseLoc);
					break;
				case BO_Comma:
					parseExpression(binaryOp->getLHS());
					parseCondition(binaryOp->getRHS(), trueLoc, falseLoc);
					break;
				default:
					parseExpression(conditional, false, true);
					AddJumpInlineCheckStr(JumpFalse, falseLoc);
					break;

			}
		}
		else{
			parseExpression(conditional, false, true);
			AddJumpInlineCheckStr(JumpFalse, falseLoc);
		}
	}
	void parseCondition2(const Expr* conditional, const string& trueLoc, const string& falseLoc){
		const BinaryOperator* binaryOp;
		if (binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens()))
		{
			switch (binaryOp->getOpcode()){
				case BO_LAnd:
					parseJumpFalse(binaryOp->getLHS(), falseLoc);
					parseCondition2(binaryOp->getRHS(), trueLoc, falseLoc);
					break;
				case BO_LOr:
					parseJumpTrue(binaryOp->getLHS(), trueLoc);
					parseCondition2(binaryOp->getRHS(), trueLoc, falseLoc);
					break;
				case BO_Comma:
					parseExpression(binaryOp->getLHS());
					parseCondition2(binaryOp->getRHS(), trueLoc, falseLoc);
					break;
				default:
					parseExpression(conditional, false, true);
					AddJumpInlineCheckStr(JumpTrue, trueLoc);
					break;

			}
		}
		else{
			parseExpression(conditional, false, true);
			AddJumpInlineCheckStr(JumpTrue, trueLoc);
		}
	}
	void parseJumpTrue(const Expr* conditional, const string& jumpTrueLoc){
		const BinaryOperator* binaryOp;
		if ((binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens())) && binaryOp->getOpcode() == BO_LOr){
			parseJumpTrue(binaryOp->getLHS(), jumpTrueLoc);
			parseJumpTrue(binaryOp->getRHS(), jumpTrueLoc);
		}
		else{
			parseExpression(conditional, false, true);
			AddJumpInlineCheckStr(JumpTrue, jumpTrueLoc);
		}
	}
	bool parseStatement(Stmt *s, const string& breakLoc, const string& continueLoc) {
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
			static int ifCounter = 0;
			const string currentCounter = to_string(ifCounter++);//prevents issues with nested if statements
			IfStmt *IfStatement = cast<IfStmt>(s);
			Expr *conditional = IfStatement->getCond();
			Stmt *Then = IfStatement->getThen();
			Stmt *Else = IfStatement->getElse();
			bool rev = false;
			if (Else && (isa<NullStmt>(Else) || (isa<CompoundStmt>(Else) && cast<CompoundStmt>(Else)->size() == 0)))
			{
				Else = NULL;
			}
			if (isa<NullStmt>(Then) || (isa <CompoundStmt>(Then) && cast<CompoundStmt>(Then)->size() == 0)){
				if (Else){
					rev = true;
					Then = Else;
					Else = NULL;
				}
				else{
					if (conditional->HasSideEffects(*context, true)){
						parseExpression(conditional);//parse then drop
					}
					return true;
				}
			}
			string IfLocEnd = "__if_end_" + currentCounter;

			Expr::EvalResult eResult;
			bool bValue = false, ignoreCondition = false;
			if (conditional->EvaluateAsRValue(eResult, *context) && eResult.Val.isInt())
			{
				bValue = eResult.Val.getInt().getBoolValue();
				if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
					Warn("if condition always evaluates to " + (bValue ? string("true") : string("false")), rewriter, conditional->getSourceRange());
				ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !conditional->HasSideEffects(*context, true);
			}
			if (ignoreCondition)
			{
				if (bValue ^ rev)
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
							AddJumpInlineCheckStr(Jump, "__if_else_" + currentCounter);
							LocalVariables.addLevel();
							parseStatement(Then, breakLoc, continueLoc);
							LocalVariables.removeLevel();


							bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
							if (Else)
							{
								AddJumpInlineCheckConditionallyStr(!ifEndRet, Jump, IfLocEnd);

								AddJumpInlineCheckStr(Label, "__if_else_" + currentCounter);
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
				if (rev){
					parseCondition2(conditional, IfLocEnd, "__if_else_" + currentCounter);
					AddJumpInlineCheckStr(Label, "__if_else_" + currentCounter);
				}
				else{
					parseCondition(conditional, "__if_then_" + currentCounter, Else ? "__if_else_" + currentCounter : IfLocEnd);
					AddJumpInlineCheckStr(Label, "__if_then_" + currentCounter);
				}
				LocalVariables.addLevel();
				parseStatement(Then, breakLoc, continueLoc);
				LocalVariables.removeLevel();
				bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
				AddJumpInlineCheckConditionallyStr(!ifEndRet && Else, Jump, IfLocEnd);//if the last instruction is a return, no point adding a jump

				if (Else) {
					AddJumpInlineCheckStr(Label, "__if_else_" + currentCounter);
					LocalVariables.addLevel();
					parseStatement(Else, breakLoc, continueLoc);
					LocalVariables.removeLevel();
				}

				AddJumpInlineCheckConditionallyStr(!ifEndRet || !Else, Label, IfLocEnd);

			}
		}
		else if (isa<WhileStmt>(s)) {
			static int whileCounter = 0;
			const string currentCounter = to_string(whileCounter++);
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
				ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !conditional->HasSideEffects(*context, true);
			}
			if (ignoreCondition)
			{
				if (bValue)
				{
					AddJumpInlineCheckStr(Label, "__while_body_" + currentCounter);

					parseStatement(body, "__while_end_" + currentCounter, "__while_body_" + currentCounter);

					AddJumpInlineCheckStr(Jump, "__while_body_" + currentCounter);
					AddJumpInlineCheckStr(Label, "__while_end_" + currentCounter);
				}
				else
				{
					AddJumpInlineCheckStr(Label, "__while_body_" + currentCounter);
					AddJumpInlineCheckStr(Jump, "__while_end_" + currentCounter);

					parseStatement(body, "__while_end_" + currentCounter, "__while_body_" + currentCounter);

					AddJumpInlineCheckStr(Label, "__while_end_" + currentCounter);
				}

			}
			else {
				parseCondition(conditional, "__while_body_" + currentCounter, "__while_end_" + currentCounter);
				AddJumpInlineCheckStr(Label, "__while_body_" + currentCounter);

				parseStatement(body, "__while_end_" + currentCounter, "__while_cond_" + currentCounter);

				AddJumpInlineCheckStr(Label, "__while_cond_" + currentCounter);

				parseCondition2(conditional, "__while_body_" + currentCounter, "__while_end_" + currentCounter);

				AddJumpInlineCheckStr(Label, "__while_end_" + currentCounter);
			}
			LocalVariables.removeLevel();
		}
		else if (isa<ForStmt>(s)) {
			static int forCounter = 0;
			const string currentCounter = to_string(forCounter++);
			ForStmt *forStmt = cast<ForStmt>(s);
			Stmt *decl = forStmt->getInit();
			Expr *conditional = forStmt->getCond();
			Expr *increment = forStmt->getInc();
			Stmt *body = forStmt->getBody();
			LocalVariables.addLevel();
			if (decl) {
				parseStatement(decl, "", "");
			}

			if (conditional) {
				parseCondition(conditional, "__for_body_" + currentCounter, "__for_end_" + currentCounter);
			}
			AddJumpInlineCheckStr(Label, "__for_body_" + currentCounter);

			parseStatement(
				body,
				"__for_end_" + currentCounter,
				(increment || conditional ? "__for_continue_" :"__for_body_") + currentCounter);

			if (increment || conditional){
				AddJumpInlineCheckStr(Label, "__for_continue_" + currentCounter);
			}

			if (increment)
				parseExpression(increment);

			if (conditional)
			{
				parseCondition2(conditional, "__for_body_" + currentCounter, "__for_end_" + currentCounter);
			}
			else
			{
				AddJumpInlineCheckStr(Jump, "__for_body_" + currentCounter);
			}

			AddJumpInlineCheckStr(Label, "__for_end_" + currentCounter);
			LocalVariables.removeLevel();


		}
		else if (isa<UnaryOperator>(s)) {
			parseExpression(cast<const Expr>(s));
		}
		else if (isa<DoStmt>(s)) {
			static int doCounter = 0;
			const string  currentCounter = to_string(doCounter++);
			DoStmt *doStmt = cast<DoStmt>(s);
			Expr *conditional = doStmt->getCond();

			Stmt *body = doStmt->getBody();
			LocalVariables.addLevel();

			AddJumpInlineCheckStr(Label, "__do_body_" + currentCounter);
			parseStatement(body, "__do_end_" + currentCounter, "__do_cond_" + currentCounter);

			AddJumpInlineCheckStr(Label, "__do_cond_" + currentCounter);

			Expr::EvalResult eResult;
			bool bValue = false, ignoreCondition = false;
			if (conditional->EvaluateAsRValue(eResult, *context) && eResult.Val.isInt())
			{
				bValue = eResult.Val.getInt().getBoolValue();
				if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
					Warn("do While condition always evaluates to " + (bValue ? string("true") : string("false")), rewriter, conditional->getSourceRange());
				ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !conditional->HasSideEffects(*context, true);
			}
			if (ignoreCondition)
			{
				AddJumpInlineCheckConditionallyStr(bValue, Jump, "__do_body_" + currentCounter);
				//no need for else, just jump right out
			}
			else
			{
				parseCondition2(conditional, "__do_body_" + currentCounter, "__do_end_" + currentCounter);
			}

			AddJumpInlineCheckStr(Label, "__do_end_" + currentCounter);
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
			AddJumpInlineCheckStrComment(Jump, "brkstmt jmp", breakLoc);
		}
		else if (isa<NullStmt>(s)) {
		}
		else if (isa<ContinueStmt>(s)) {
			AddJumpInlineCheckStrComment(Jump, "contstmt jmp", continueLoc);
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
			parseStatement(switchStmt->getBody(), to_string(switchStmt->getLocEnd().getRawEncoding()), continueLoc);
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
					AddInstructionComment(PushInt, "Type Size (compound decl)", size);
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
						AddInstruction(SetConv, scriptData, getSizeOfType(type));
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
					if (Option_OptimizationLevel > OptimisationLevel::OL_None){
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
												AddInstructionComment(SetFrame, "Inline Argument Setting", Index);
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
												parseStatement(body, "", "");
												if (scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()))
												{
													scriptData.getCurrentFunction()->RemoveLast();
													//remove the last jump, but keep the label, just incase other places in the function have returns
												}
												AddInstructionComment(Label, "Inline return location", scriptData.getInlineJumpLabelAppend());
											}
											LocalVariables.removeLevel();
											scriptData.removeFunctionInline(name);

										}
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
				case clang::CK_PointerToBoolean:
				{
					parseExpression(icast->getSubExpr(), false, isLtoRValue);
					AddInstructionConditionally(isLtoRValue, IsNotZero);
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
					if (isLtoRValue){
						AddInstruction(PushNullPtr);
					}
					else{
						parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
					}
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
						AddInstructionComment(PushInt, "Type Size (Deref)", bSize);
					}
					else if ((size == 1 || size == 2) && isAssign)
					{
						LocalVariables.addLevel();

						if (scriptData.getBuildPlatform() == P_PC)
						{
							int index = LocalVariables.addDecl("DerefSavedVar", 1);
							int buffer = LocalVariables.addDecl("64BitTempStorage", 2);

							AddInstruction(SetConv, scriptData, size);

							AddInstruction(PushInt, 0);
							AddInstructionComment(SetFrame, "64BitTempStorage[0]", buffer);
							AddInstruction(PushInt, 0);
							AddInstructionComment(SetFrame, "64BitTempStorage[1]", buffer + 1);

							

							parseExpression(subE, subE->getType().getTypePtr()->isArrayType(), true);
							AddInstruction(Dup);
							AddInstructionComment(SetFrame, "DerefSavedVar", index);
							

							AddInstruction(PGet);
							AddInstruction(PushInt, size == 1 ? 0xFFFFFF : 0xFFFF0000);
							AddInstruction(And);
							AddInstruction(Or);
							AddInstructionComment(SetFrame, "64BitTempStorage[0]", buffer);

							AddInstructionComment(GetFrame, "DerefSavedVar", index);
							AddInstruction(AddImm, 4);
							AddInstruction(PGet);
							AddInstructionComment(GetFrameP, "64BitTempStorage[0]", buffer);
							AddInstruction(AddImm, 4);
							AddInstruction(PSet);

							AddInstructionComment(GetFrame, "64BitTempStorage[0]", buffer);
							AddInstructionComment(GetFrame, "DerefSavedVar", index);
						}
						else
						{
							int index = LocalVariables.addDecl("DerefSavedVar", 1);
							AddInstruction(SetConv, scriptData, size);

							parseExpression(subE, subE->getType().getTypePtr()->isArrayType(), true);
							AddInstruction(Dup);
							AddInstructionComment(SetFrame, "DerefSavedVar", index);

							AddInstruction(PGet);
							AddInstruction(PushInt, size == 1 ? 0xFFFFFF : 0xFFFF);
							AddInstruction(And);
							AddInstruction(Or);

							AddInstructionComment(GetFrame, "DerefSavedVar", index);
						}
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
								AddInstruction(GetConv, scriptData, size, e->getType()->isSignedIntegerType());
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
					AddInstruction(Drop);
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
			const Type* type = E->getType().getTypePtr();
			
			int typeSize = getSizeFromBytes(getSizeOfType(type));

			if ((isLtoRValue || !isAddr) && typeSize > 1 && !isArrToPtrDecay)
			{
				AddInstructionComment(PushInt, "Type Size (member expr) " + 
									  to_string(isLtoRValue) + " " + 
									  to_string(isAddr) + " " + 
									  to_string(isArrToPtrDecay) + " " + 
									  to_string(isAssign), typeSize);
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
						for (const FieldDecl *CS : record->fields()) {
							if (CS == Field)
								break;

							const Type* type = CS->getType().getTypePtr();
							int temp = getSizeOfType(type);
							offset += max(temp, stackWidth);
						}
					}
				}
			}

			AddInstructionComment(GetImmP, "." + ND->getName().str(), getSizeFromBytes(offset));
			if (isArrToPtrDecay)
			{
				return 1;
			}
			else if (isLtoRValue)
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
			static int condCounter = 0;
			const string currentCounter = to_string(condCounter++);
			const ConditionalOperator *cond = cast<const ConditionalOperator>(e);
			auto condition = cond->getCond();
			Expr::EvalResult eResult;
			bool bValue = false, ignoreCondition = false;
			if (condition->EvaluateAsRValue(eResult, *context) && eResult.Val.isInt())
			{
				bValue = eResult.Val.getInt().getBoolValue();
				if (!isa<IntegerLiteral>(condition->IgnoreParenCasts()))
					Warn("Conditional operator always evaluates to " + (bValue ? string("true") : string("false")), rewriter, condition->getSourceRange());
				ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !condition->HasSideEffects(*context, true);
			}
			if (ignoreCondition){
				parseExpression(bValue ? cond->getLHS() : cond->getRHS(), isAddr, isLtoRValue);
			}
			else{
				parseCondition(condition, "__cond_true_" + currentCounter, "__cond_false_" + currentCounter);
				AddJumpInlineCheckStr(Label, "__cond_true_" + currentCounter);

				parseExpression(cond->getLHS(), isAddr, isLtoRValue);
				AddJumpInlineCheckStr(Jump, "__cond_end_" + currentCounter);

				AddJumpInlineCheckStr(Label, "__cond_false_" + currentCounter);
				parseExpression(cond->getRHS(), isAddr, isLtoRValue);
				AddJumpInlineCheckStr(Label, "__cond_end_" + currentCounter);
			}
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
			static int binCondCounter = 0;
			const string currentCounter = to_string(binCondCounter++);
			const BinaryConditionalOperator *bco = cast<BinaryConditionalOperator>(e);

			//out << "COND:" << endl;
			parseExpression(bco->getCond(), false, true);
			AddInstruction(Dup);
			AddJumpInlineCheckStr(JumpFalse, "__bin_false_" + currentCounter);
			if (!isLtoRValue)
			{
				AddInstruction(Drop);//drop the value if not LtoR
			}
			AddJumpInlineCheckStr(Jump, "__bin_end_" + currentCounter);

			AddJumpInlineCheckStr(Label, "__bin_false_" + currentCounter);
			AddInstruction(Drop);
			parseExpression(bco->getFalseExpr(), false, isLtoRValue);//LtoR should handle the drop
			AddJumpInlineCheckStr(Label, "__bin_end_" + currentCounter);
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
				AddInstruction(SetConv, scriptData, 1);
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
				
				AddInstruction(SetConv, scriptData, 2);
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
				AddInstructionComment(PushInt, "Type Size (array)", bSize);
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
					int size = getSizeOfType(type);
					if (size % scriptData.getStackWidth() == 0){
						int multVal = size / scriptData.getStackWidth();
						int addval = iRes * multVal;
						if (addval > 0 && addval <= 0xFFFF){
							AddInstruction(GetImmP, addval);
						}
						else{
							AddInstruction(PushInt, addval);
							AddInstruction(GetImmPStack);
						}
					}
					else{
						AddInstruction(AddImm, iRes * size);
					}
				}
			}
			else
			{
				parseExpression(index, false, true);
				int size = getSizeOfType(type);
				if (size % scriptData.getStackWidth() == 0){
					AddInstructionConditionally(size > 1, MultImm, size / scriptData.getStackWidth())
					AddInstructionConditionally(size > 1, GetImmPStack);
				}
				else{
					AddInstructionConditionally(size > 1, MultImm, size);
					AddInstruction(Add);
				}
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
					AddInstruction(GetConv, scriptData, 1, e->getType()->isSignedIntegerType());
				}
				//2 byte indexing
				else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
				{
					AddInstruction(GetConv, scriptData, 2, e->getType()->isSignedIntegerType());
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
					if (size % scriptData.getStackWidth() == 0){
						int multVal = size / scriptData.getStackWidth();
						int addval = iRes * multVal;
						if (addval > 0 && addval <= 0xFFFF){
							AddInstruction(GetImmP, addval);
						}
						else{
							AddInstruction(PushInt, addval);
							AddInstruction(GetImmPStack);
						}
					}
					else{
						AddInstruction(AddImm, iRes * size);
					}
				}
			}
			else
			{
				parseExpression(index, false, true);
				int size = getSizeOfType(type);
				if (size % scriptData.getStackWidth() == 0){
					AddInstructionConditionally(size > 1, MultImm, size / scriptData.getStackWidth())
					AddInstructionConditionally(size > 1, GetImmPStack);
				}
				else{
					AddInstructionConditionally(size > 1, MultImm, size);
					AddInstruction(Add);
				}
			}
		}
		else
		{
			if (isCst)
			{
				int iRes = evalIndex.getSExtValue();
				if (iRes != 0)
				{
					int size = getSizeOfType(type);
					if (size % scriptData.getStackWidth() == 0){
						int multVal = size / scriptData.getStackWidth();
						int addval = iRes * multVal;
						if (addval > 0 && addval <= 0xFFFF){
							AddInstruction(GetImmP, addval);
						}
						else{
							AddInstruction(PushInt, addval);
							AddInstruction(GetImmPStack);
						}
					}
					else{
						AddInstruction(AddImm, iRes * size);
					}
					
				}
			}
			else
			{
				parseExpression(index, false, true);
				int size = getSizeOfType(type);
				if (size % scriptData.getStackWidth() == 0){
					AddInstructionConditionally(size > 1, MultImm, size / scriptData.getStackWidth())
					AddInstructionConditionally(size > 1, GetImmPStack);
				}
				else{
					AddInstructionConditionally(size > 1, MultImm, size);
					AddInstruction(Add);
				}
				
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
			parseStatement(FuncBody, "", "");

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

			//	F1, //low: int maxBlockSize = 50, int minBlockSize = 30, bool keepEndReturn = true, bool makeJumpTable = false
			//	F2, //default: int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = false
			//	F3, //high:  int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = true
			//	F4, //very high: int maxBlockSize = 15, int minBlockSize = 5, bool keepEndReturn = false, bool makeJumpTable = true
			//  F5, //max: int maxBlockSize = 5, int minBlockSize = 1, bool keepEndReturn = false, bool makeJumpTable = true

			switch (Option_ObfuscationLevel)
			{
				case obf_none: break;
				case obf_low: func->codeLayoutRandomisation(scriptData, 50, 30, true, false); break;
				case obf_default: func->codeLayoutRandomisation(scriptData, 30, 15, false, false); break;
				case obf_high:func->codeLayoutRandomisation(scriptData, 30, 15, false, true); break;
				case obf_veryhigh: func->codeLayoutRandomisation(scriptData, 15, 5, false, true); break;
				case obf_max: func->codeLayoutRandomisation(scriptData, 5, 1, false, true); break;
				default: Throw("Unknown Obfuscation Level: " + Option_ObfuscationLevel);
			}
				
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

				//tests attributes
				//AttrVec vec = f->getAttrs();
				//for(uint32_t i = 0; i < vec.size(); i++)
				//	cout << vec[i]->getSpelling() << endl;
			}
			int32_t paramSize = 0;
			for (uint32_t i = 0; i < f->getNumParams(); i++)
				paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));

			
			scriptData.createFunction(getNameForFunc(f), paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0), getSizeFromBytes(getSizeOfType(f->getReturnType().getTypePtr())), false, true);


			//cout << "added prototype: " << f->getNameAsString() << endl;
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
			//                const Type* type = CS->getType().getTypePtr();
			//				  int temp = getSizeOfType(type);
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
				const Type* type = CS->getType().getTypePtr();
				int temp = getSizeOfType(type);
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


			parseStatement(CS->getBody(), "", "");

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

			if (Option_EntryFunctionPadding)
			{
				isCurrentExprEvaluable = false;
				scriptData.getCurrentStatic()->addOpSetThisStaticMult(scriptData, 0, size);
				scriptData.getCurrentStatic()->setDynamic();
			}
			else
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
					//if (intIndex == 0)
					//	scriptData.addStaticInit();
					//
					//scriptData.modifyLastInitStaticByte(resValue, intIndex);

					if (++intIndex >= stackWidth)
						intIndex = 0;

					//TODO:  if (!isCurrentExprEvaluable)
					scriptData.getCurrentStatic()->pushInit8(resValue);
				}
				else if (type->isSpecificBuiltinType(BuiltinType::Kind::Short) || type->isSpecificBuiltinType(BuiltinType::Kind::UShort))
				{
					//if (intIndex == 0)
					//	scriptData.addStaticInit();
					//
					//scriptData.modifyLastInitStaticShort(resValue, intIndex);

					intIndex += 2;
					if (intIndex >= stackWidth)
						intIndex = 0;

					//TODO:  if (!isCurrentExprEvaluable)
					scriptData.getCurrentStatic()->pushInit16(resValue, scriptData.getEndian());
				}
				else if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
				{
					isCurrentExprEvaluable = false;
					doesCurrentValueNeedSet = true;
					scriptData.getCurrentStatic()->addOpPushInt(resValue);
					scriptData.getCurrentStatic()->setDynamic();
				}
				else
				{

					scriptData.getCurrentStatic()->pushInit32(resValue, scriptData.getEndian());
					scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				}

				return true;
			}
			else if (result.Val.isFloat())
			{
				if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
				{
					isCurrentExprEvaluable = false;
					doesCurrentValueNeedSet = true;
					scriptData.getCurrentStatic()->addOpPushFloat((float)extractAPFloat(result.Val.getFloat()));
					scriptData.getCurrentStatic()->setDynamic();
				}
				else
				{
					scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getFloat())), scriptData.getEndian());
				}
				return true;
			}
			else if (result.Val.isComplexFloat())
			{
				if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
				{
					isCurrentExprEvaluable = false;
					doesCurrentValueNeedSet = true;
					scriptData.getCurrentStatic()->addOpPushFloat((float)extractAPFloat(result.Val.getComplexFloatReal()));
					scriptData.getCurrentStatic()->addOpPushFloat((float)extractAPFloat(result.Val.getComplexFloatImag()));
					scriptData.getCurrentStatic()->setDynamic();
				}
				else
				{
					scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatReal())), scriptData.getEndian());
					scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
					scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatImag())), scriptData.getEndian());
					scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				}
				return true;
			}
			else if (result.Val.isComplexInt())
			{
				if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
				{
					isCurrentExprEvaluable = false;
					doesCurrentValueNeedSet = true;
					scriptData.getCurrentStatic()->addOpPushInt(result.Val.getComplexIntReal().getSExtValue());
					scriptData.getCurrentStatic()->addOpPushInt(result.Val.getComplexIntImag().getSExtValue());
					scriptData.getCurrentStatic()->setDynamic();
				}
				else
				{
					scriptData.getCurrentStatic()->pushInit32(result.Val.getComplexIntReal().getSExtValue(), scriptData.getEndian());
					scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
					scriptData.getCurrentStatic()->pushInit32(result.Val.getComplexIntImag().getSExtValue(), scriptData.getEndian());
					scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());

				}
				return true;
			}
		}

		if (isa<StringLiteral>(e)) {
			const StringLiteral *literal = cast<const StringLiteral>(e);
			if (literal->getString().str().length() > 0)
			{
				if (Option_EntryFunctionPadding)
				{
					isCurrentExprEvaluable = false;
					scriptData.getCurrentStatic()->addOpPushString(literal->getString().str());
					scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
					scriptData.getCurrentStatic()->setDynamic();
				}
				else
				{
					scriptData.getCurrentStatic()->pushStringInit(literal->getString().str(), scriptData.getStackWidth() * getSizeFromBytes(getLiteralSizeOfType(e->getType().getTypePtr())));
					scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				}
				
				//string strlit = literal->getString().str();
				//e->getType().getTypePtr();
				//
				//int32_t strsize = getLiteralSizeOfType(e->getType().getTypePtr());
				//
				//int32_t buffer = 0;
				//int32_t i = 0, b = 0;
				//for (; i < strsize; i++, b++)
				//{
				//	if (b >= stackWidth)
				//	{
				//		scriptData.addStaticInitBig(buffer);
				//		b = 0;
				//		buffer = 0;
				//
				//		if (i >= (int32_t)strlit.length())
				//		{
				//			scriptData.addStaticInit(0, Utils::Math::CeilDivInt(strsize - i, stackWidth));
				//			break;
				//		}
				//	}
				//	if (i >= (int32_t)strlit.length())
				//		((uint8_t*)&buffer)[b] = 0;//add padding
				//	else
				//		((uint8_t*)&buffer)[b] = strlit[i];
				//
				//}
				//if (b != 0)
				//	scriptData.addStaticInitBig(buffer);

			}

			return true;
		}
		else if (isa<InitListExpr>(e))
		{
			const InitListExpr *I = cast<const InitListExpr>(e);
			uint32_t size = getSizeFromBytes(getSizeOfType(I->getType().getTypePtr()));
			size_t curSize = scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth());
			resetIntIndex();
			for (uint32_t i = 0; i < I->getNumInits(); i++)
			{
				isCurrentExprEvaluable = true;
				doesCurrentValueNeedSet = false;
				ParseLiteral(I->getInit(i), false, true);
				if (doesCurrentValueNeedSet)
				{
					scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
				}
			}
			scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());

			resetIntIndex();
			isCurrentExprEvaluable = true;
			doesCurrentValueNeedSet = false;

			if (scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth()) - curSize < size)
			{
				int count = size - (scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth()) - curSize);
				if (Option_EntryFunctionPadding)
				{
					isCurrentExprEvaluable = false;
					scriptData.getCurrentStatic()->addOpSetThisStaticMult(scriptData, 0, count);
					scriptData.getCurrentStatic()->setDynamic();
				}
				else
					scriptData.getCurrentStatic()->pushNullInit(count, scriptData.getStackWidth());
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
					if (auto fDecl = dyn_cast_or_null<FunctionDecl>(DRE->getDecl()))
					{
						auto function = scriptData.getFunctionFromName(getNameForFunc(fDecl));
						if (!function)
							Throw("Static function pointer \"" + fDecl->getNameAsString() + "\" not found");

						scriptData.getCurrentStatic()->addOpFuncLoc(function);
						scriptData.getCurrentStatic()->setDynamic();
					}
					else{
						//we can index because the name has to be declared in clang to use the declare, we will let clang handle errors
						StaticData* staticData = scriptData.findStatic(dumpName(cast<NamedDecl>(DRE->getDecl())));
						assert(staticData && "Static Not Found");
						scriptData.getCurrentStatic()->addOpGetStaticP(staticData);
						scriptData.getCurrentStatic()->setDynamic();
					}
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
				}
				else if (isa<DeclRefExpr>(icast->getSubExpr()))//int vstack[10] = {1,2,3,4,5,6,7,8,9,10}, *vstack_ptr = vstack;
				{
					const DeclRefExpr *DRE = cast<const DeclRefExpr>(icast->getSubExpr());
					doesCurrentValueNeedSet = true;

					//we can index because the name has to be declared in clang to use the declare, we will let clang handle errors
					StaticData* staticData = scriptData.findStatic(dumpName(cast<NamedDecl>(DRE->getDecl())));
					assert(staticData && "Static Not Found");
					scriptData.getCurrentStatic()->addOpGetStaticP(staticData);
					scriptData.getCurrentStatic()->setDynamic();
				}
				else// need to test byte* t = {1,2,3};
					Throw("Unimplemented CK_ArrayToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()), rewriter, icast->getSubExpr()->getSourceRange());
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

						scriptData.getCurrentStatic()->addOpFuncLoc(function);
						scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
						scriptData.getCurrentStatic()->setDynamic();

					}
					else Throw("Unimplemented CK_FunctionToPointerDecay DeclRefExpr for " + string(declRef->getStmtClassName()));

				}
				else
					Throw("Unimplemented CK_FunctionToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()), rewriter, icast->getSubExpr()->getSourceRange());
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
				case clang::CK_NullToPointer://char* HeaderText = nullptr,
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

				default:
				Throw("Unimplemented ImplicitCastExpr of type " + string(icast->getCastKindName()), rewriter, icast->getSourceRange());
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

					//TODO: double check this code
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
						cur->addOpGetStaticP(scriptData.findStatic(dumpName(cast<NamedDecl>(declRef->getDecl()))));
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
					for (const FieldDecl *CS : record->fields()) {
						if (CS == Field)
							break;

						const Type* type = CS->getType().getTypePtr();
						int temp = getSizeOfType(type);
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
					scriptData.getCurrentStatic()->addOpGetStaticP(scriptData.findStatic(dumpName(cast<NamedDecl>(varDecl))));
					scriptData.getCurrentStatic()->setDynamic();
					return 1;
				}
				else
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
					//TODO: this will have to catch exturning vars
					if (scriptData.findStatic(dumpName(cast<NamedDecl>(D))) == NULL)
					{
						string varName = dumpName(cast<NamedDecl>(D));
						uint32_t size = getSizeOfType(globalVarDecl->getType().getTypePtr());
						const Expr *initializer = globalVarDecl->getAnyInitializer();


						switch (globalVarDecl->getStorageClass())
						{
							case SC_None:
							scriptData.addStaticNewDecl(varName, getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())), false);
							break;
							case SC_Extern:
							if (initializer)
								scriptData.addStaticNewDecl(varName, getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())), false);
							else
								return true;//this is prototyped
							break;
							case SC_Static:
							scriptData.addStaticNewDecl(varName, getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())), !globalVarDecl->isStaticLocal());
							break;
							default:
							Throw("Unhandled Storage Class", rewriter, globalVarDecl->getSourceRange());
						}

						resetIntIndex();
						savedType = nullptr;

						isCurrentExprEvaluable = true;
						doesCurrentValueNeedSet = false;

						staticInc += getSizeFromBytes(size);

						if (initializer) {

							ParseLiteral(initializer, false, true);

							//if (scriptData.getStaticSize() > staticInc)//undefined length arrays (should check if it is an undefined length array)
							//	staticInc = scriptData.getStaticSize();

							if (doesCurrentValueNeedSet)
							{
								scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
							}
							scriptData.getCurrentStatic()->fillCapacity(scriptData.getStackWidth());
						}
						else
						{
							if (Option_EntryFunctionPadding){
								scriptData.getCurrentStatic()->addOpDynamicNullThisStatic(scriptData);
							}
							scriptData.getCurrentStatic()->fillCapacity(scriptData.getStackWidth());
						}


						//if (scriptData.getStaticSize() > staticInc)
						//	Warn("Static Overflow Old:" + to_string(scriptData.getStaticSize()) + " New:" + to_string(staticInc));
						//
						//if (scriptData.getStaticSize() != scriptData.getStaticCapacity())
						//	Throw("not all values in static decl were initialized");

					}
					else
					{
						if (globalVarDecl->getStorageClass() != SC_Extern)
							Throw("Var " + dumpName(cast<NamedDecl>(D)) + " is already defined", rewriter, D->getLocStart());
					}
						
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
		scriptData->updateStaticStatics();
		scriptData->resetStaticStatics();

		//this should not be needed anymore
		if (diagnostics->getClient()->getNumErrors())
			exit(EXIT_FAILURE);
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
		preDefines += "\n#undef _MSC_VER";
		PP.setPredefines(preDefines.data());
	}
	void ModifyClangWarnings(DiagnosticsEngine& DE)
	{
		#define DisableClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Ignored, SourceLocation());
		#define ElevateClangWarning(str) DE.setSeverityForGroup(diag::Flavor::WarningOrError, str, diag::Severity::Error, SourceLocation());
		
		DisableClangWarning("main-return-type");
		DisableClangWarning("incompatible-library-redeclaration");
		DisableClangWarning("microsoft-enum-value");//this allows enums to be in hex without : unsigned int tag
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


void WriteAsmFile(const string& outDir)
{
	string Out = outDir  + scriptData->getASMFileName();
	FILE* file = fopen(Out.data(), "wb");
	if (file != NULL)
	{
		//this needs tidying up and when ready removing the first statics method
		string staticData = scriptData->getStaticsAsString();
		fwrite(staticData.data(), 1, staticData.size(), file);

		for (uint32_t i = 0, max = scriptData->getFunctionCount(); i <max; i++)
		{
			auto func = scriptData->getFunctionFromIndex(i);
			if (func->IsUsed())
			{
				if (!func->isProcessed())
					Throw("Function Prototype Implementation missing on referenced function: " + func->getName());
				assert(func->isProcessed() && "Function Prototype Implementation missing on referenced function");
				string fStr = func->toString();
				fwrite(fStr.c_str(), 1, fStr.size(), file);
			}
		}
		fclose(file);
	}
	else Throw("Output File \"" + Out + "\" Could Not Be Opened");

}

void WriteScriptFile(const string& outDir)
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
					CompileRDR c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
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
					CompileGTAV c(*scriptData, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
					c.Compile(outDir);
				}
				break;
				case P_PC:
				{
					CompileGTAVPC c(*scriptData, Option_PCVerison, Option_DisableFunctionNames || Option_OptimizationLevel > OptimisationLevel::OL_None);
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

string GetBaseNameFromDir(const string &Dir)
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
void PrintVersion()
{
	cout << "Version: " << Version << endl;
}

int ProcessFiles(ClangTool &Tool)
{
	bool ProcessingFailed = true;
	if (SourcePaths.size() > 0)
	{
		//this is temporary. script name should be set from the file that the main function is in

		string outDir = GetDir(SourcePaths[0]);
		string scriptName = (Option_OutputFileName != "" ? Option_OutputFileName : GetBaseNameFromDir(SourcePaths[0]));
		scriptData.reset(new Script(scriptName, Option_BuildType, Option_Platform, Option_Singleton, Option_EntryFunctionPadding, Option_OptimizationLevel));

		stackWidth = scriptData->getStackWidth();
		ProcessingFailed = Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
		/// ClangTool::run accepts a FrontendActionFactory, which is then used to
		/// create new objects implementing the FrontendAction interface. Here we use
		/// the helper newFrontendActionFactory to create a default factory that will
		/// return a new MyFrontendAction object every time.
		/// To further customize this, we could create our own factory class.
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
void ParseCommandLine(int argc, const char **argv, const char* Overview, unique_ptr<CompilationDatabase>& Compilations)
{
	Compilations.reset(FixedCompilationDatabase::loadFromCommandLine(argc, argv));
	cl::ParseCommandLineOptions(argc, argv, Overview);

	if (!Compilations) {
		string ErrorMessage;
		if (!BuildPath.empty())
			Compilations = CompilationDatabase::autoDetectFromDirectory(BuildPath, ErrorMessage);
		else
			Compilations = CompilationDatabase::autoDetectFromSource(SourcePaths[0], ErrorMessage);
		if (!Compilations) {
			llvm::errs() << "Error while trying to load a compilation database:\n" << ErrorMessage << "Running without flags.\n";
			Compilations.reset(new FixedCompilationDatabase(".", std::vector<std::string>()));
		}
	}
	auto AdjustingCompilations = llvm::make_unique<ArgumentsAdjustingCompilations>(std::move(Compilations));

	AdjustingCompilations->appendArgumentsAdjuster(getInsertArgumentAdjuster(ArgsBefore, ArgumentInsertPosition::BEGIN));
	AdjustingCompilations->appendArgumentsAdjuster(getInsertArgumentAdjuster(ArgsAfter, ArgumentInsertPosition::END));
	Compilations = std::move(AdjustingCompilations);
}
int main(int argc, const char **argv)
{
	cout << "Starting Clang 3.8.1\n";

	globalDirectory = GetDir(string(argv[0]));
	cl::SetVersionPrinter(PrintVersion);
	unique_ptr<CompilationDatabase> Compilations;
	ParseCommandLine(argc, argv, " XSC-CL\n", Compilations);

	ClangTool Tool(*Compilations, SourcePaths);
	return ProcessFiles(Tool);
}
