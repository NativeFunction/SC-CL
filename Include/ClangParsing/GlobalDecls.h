#pragma once
#include "stdint.h"
#include <vector>
#include "Utils/ClangUtils.h"
#include "ClangParsing/Helpers/Script.h"

namespace SCCL
{
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
	#ifdef _DEBUG
	#define AddComment(comment) scriptData.getCurrentFunction()->pushCommentNewLine(comment)
	#else
	#define AddComment(comment)
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

	typedef struct BitfieldData
	{
		size_t width = 0, offset = 0;
		BitfieldData()
		{
		}
		BitfieldData(std::initializer_list<size_t> l)
		{
			assert(l.size() <= 2 && "bitfield size too large");
			width = *l.begin();
			offset = *((char*)l.begin() + 4);
		}
	} BitfieldData;

	extern std::string globalDirectory;
	extern std::unique_ptr<Script> scriptData;
	extern uint32_t CurrentFileId;
	extern uint8_t stackWidth;
	extern clang::Rewriter* rewriter;
    extern clang::PrintingPolicy printingPolicy;

	typedef struct QueuedBF
	{
		const BitfieldData Data;
		const clang::Expr* Expr;
	} QueuedBF;

	class local_scope
	{
		std::vector<std::pair<std::pair<std::unordered_map<std::string, uint32_t>, uint32_t>, std::unordered_map<std::string, StaticData*>>> newScope;
		uint32_t maxIndex = 0;
		int scopeLevel = 0;
	public:
		void reset()//call this on function decl
		{
			scopeLevel = 0;
			newScope.clear();
			newScope.emplace_back();
			maxIndex = 0;
		}
		void addLevel()
		{
			newScope.emplace_back();
			scopeLevel++;
			newScope[scopeLevel].first.second = newScope[scopeLevel - 1].first.second;
		}
		void removeLevel()
		{
			if (scopeLevel > 0)
			{
				scopeLevel--;
				newScope.pop_back();
			}
		}
		bool find(const std::string& key, uint32_t& outIndex)
		{
			for (int i = scopeLevel; i >= 0; i--)
			{
				auto& Level = newScope[i];
				auto& frameVars = Level.first.first;
				auto& staticVars = Level.second;
				auto it = frameVars.find(key);
				if (it != frameVars.end())
				{
					outIndex = it->second;
					return true;
				}
				if (staticVars.find(key) != staticVars.end())
				{
					return false;//a static with this name has been found in the current level,
				}
			}
			return false;
		}
		bool findNewStatic(const std::string& key, StaticData*& outPtr)
		{
			for (int i = scopeLevel; i >= 0; i--)
			{
				auto& Level = newScope[i];
				auto& frameVars = Level.first.first;
				auto& staticVars = Level.second;
				auto it = staticVars.find(key);
				if (it != staticVars.end())
				{
					outPtr = it->second;
					return true;
				}
				if (frameVars.find(key) != frameVars.end())
				{
					return false;
				}

			}
			return false;
		}

		uint32_t getCurrentSize()const
		{
			return newScope[scopeLevel].first.second;
		}
		uint32_t getMaxIndex()const
		{
			return maxIndex;
		}

		size_t addDecl(const std::string& key, uint32_t size)
		{
			assert(size > 0 && "size can't be 0");
			auto lvlSize = newScope[scopeLevel].first.second;

			newScope[scopeLevel].first.first.insert({ key, lvlSize });
			newScope[scopeLevel].first.second += size;

			if (newScope[scopeLevel].first.second > maxIndex)
			{
				maxIndex = newScope[scopeLevel].first.second;
			}
			return lvlSize;
		}

		StaticData* addLocalStaticDecl(const clang::VarDecl* decl)
		{
			auto var = scriptData->findLocalStatic(decl->getLocation().getRawEncoding());
			if (var)
			{
				newScope[scopeLevel].second.insert({ var->getName(), var });
			}
			return var;
		}

	};

	extern local_scope LocalVariables;

	#pragma region Global_Size_Functions
	namespace size
	{

	}
	uint32_t checkBitFieldWidth(const clang::FieldDecl* bitField);
	uint32_t getSizeFromBytes(uint64_t bytes);
	uint32_t getLiteralSizeOfType(const clang::Type* type);
	uint32_t getSizeOfType(const clang::Type* type);
	bool CheckExprForSizeOf(const clang::Expr* expr, int *outSize);
	inline bool doesInt64FitIntoInt32(int64_t value)
	{
		return (int32_t)value != value;
	}

	#pragma endregion

	namespace conversion
	{

	}
	inline double extractAPFloat(llvm::APFloat value)
	{
		return &value.getSemantics() == &llvm::APFloat::IEEEsingle() ? (double)value.convertToFloat() : value.convertToDouble();
	}

	#pragma region Global_Local/Static_Functions
	const clang::DeclRefExpr *getDeclRefExpr(const clang::Expr *e);
	#pragma endregion

}

