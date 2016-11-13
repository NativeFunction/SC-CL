#pragma once
#include "FunctionData.h"
#include <cassert>
#include <string>
#include <vector>

#include <unordered_map>
#include "Utils.h"
#include "OpcodeConsts.h"
#include "ConstExpr.h"
#include "Script.h"

class CompileGTAPC
{

public:
	CompileGTAPC(const Script& data)
	{
		BaseOpcodes = &GTAVOpcodes;
		HLData = &data;

		ReadBufferSize = 16384;//TODO: Find pc read buffer
		FunctionCount = 0;
		InstructionCount = 0;
	}
	~CompileGTAPC(){}

	void Compile(std::string outDirectory)
	{
		BuildTables();
		XSCWrite((outDirectory + HLData->getBuildFileName()).data());
	}
protected:
	const OpCodes GTAVOpcodes = { VO_Nop, VO_Add, VO_Sub, VO_Mult, VO_Div, VO_Mod, VO_Not, VO_Neg, VO_CmpEq, VO_CmpNe, VO_CmpGt, VO_CmpGe, VO_CmpLt, VO_CmpLe, VO_fAdd, VO_fSub, VO_fMult, VO_fDiv, VO_fMod, VO_fNeg, VO_fCmpEq, VO_fCmpNe, VO_fCmpGt, VO_fCmpGe, VO_fCmpLt, VO_fCmpLe, VO_vAdd, VO_vSub, VO_vMult, VO_vDiv, VO_vNeg, VO_And, VO_Or, VO_Xor, VO_ItoF, VO_FtoI, VO_FtoV, VO_PushB, VO_PushB2, VO_PushB3, VO_Push, VO_PushF, VO_Dup, VO_Drop, VO_CallNative, VO_Function, VO_Return, VO_pGet, VO_pSet, VO_pPeekSet, VO_ToStack, VO_FromStack, VO_GetArrayP1, VO_GetArray1, VO_SetArray1, VO_GetFrameP1, VO_GetFrame1, VO_SetFrame1, VO_GetStaticP1, VO_GetStatic1, VO_SetStatic1, VO_Add1, VO_Mult1, VO_GetImm1, VO_SetImm1, VO_PushS, VO_Add2, VO_Mult2, VO_GetImm2, VO_SetImm2, VO_GetArrayP2, VO_GetArray2, VO_SetArray2, VO_GetFrameP2, VO_GetFrame2, VO_SetFrame2, VO_GetStaticP2, VO_GetStatic2, VO_SetStatic2, VO_GetGlobalP2, VO_GetGlobal2, VO_SetGlobal2, VO_Jump, VO_JumpFalse, VO_JumpNE, VO_JumpEQ, VO_JumpLE, VO_JumpLT, VO_JumpGE, VO_JumpGT, VO_Call, VO_GetGlobalp3, VO_GetGlobal3, VO_SetGlobal3, VO_PushI24, VO_Switch, VO_PushString, VO_StrCopy, VO_ItoS, VO_StrAdd, VO_StrAddi, VO_Memcopy, VO_Catch, VO_Throw, VO_pCall, VO_Push_Neg1, VO_Push_0, VO_Push_1, VO_Push_2, VO_Push_3, VO_Push_4, VO_Push_5, VO_Push_6, VO_Push_7, VO_PushF_Neg1, VO_PushF_0, VO_PushF_1, VO_PushF_2, VO_PushF_3, VO_PushF_4, VO_PushF_5, VO_PushF_6, VO_PushF_7, VO_GetImmP, VO_GetImmP1, VO_GetImmP2, VO_GetHash };
#pragma region Type_Defines
	enum class JumpInstructionType
	{
		Jump,
		JumpFalse,
		JumpEQ,
		JumpNE,
		JumpGT,
		JumpGE,
		JumpLT,
		JumpLE,
		Switch,
		LabelLoc
	};
	enum class CallInstructionType
	{
		Call,
		FuncLoc
	};
	typedef struct
	{
		const uint32_t JumpLocation;
		const JumpInstructionType InstructionType;
		const std::string Label;
		bool isSet;
	} JumpData;
	typedef struct
	{
		uint32_t LabelLocation;
		bool isSet;
		std::vector<uint32_t> JumpIndexes;
	} LabelData;
	typedef struct
	{
		JumpData JumpInfo;
		LabelData LabelInfo;
	} JumpLabelData;
	typedef struct
	{
		const uint32_t CallLocation;
		const CallInstructionType InstructionType;
		const FunctionData* Function;
	} CallData;
	typedef struct
	{
		int32_t CodeBlocks, Unk1, Statics, Natives, StringBlocks, ScriptName;
		std::vector<uint32_t> CodePagePointers;
		std::vector<uint32_t> StringPagePointers;
	} PHO;//placeHolderOffsets
	typedef struct
	{
		uint32_t tableOffset;
		std::string labelName;
	} JumpTableData;//these can be set at the end of compiling a function
#pragma endregion

#pragma region Parsed_Data_Vars
	std::vector<uint8_t> CodePageData;//opcode data
	std::unordered_map<std::string, LabelData> LabelLocations;//label ,data index
	std::vector<JumpData> JumpLocations;//JumpLocations to fill after building the CodePageData for a function
	uint32_t SignedJumpLocationInc = 0, UnsignedJumpLocationInc = 0;
	std::unordered_map<const FunctionData*, uint32_t> FuncLocations;//call, data index
	std::vector<CallData> CallLocations;//CallLocations to fill after building the CodePageData
	std::unordered_map<uint64_t, uint32_t> NativeHashMap;//hash, index  (native hash map has index start of 1) (hash map list for NativesList to limit find recursion)
	std::vector<JumpTableData> jumpTableLocs;
	std::vector<uint8_t> StringPageData;
	std::unordered_map<std::string, uint32_t> StringPageDataIndexing;
	uint32_t StringPageCount = 0;
#pragma endregion

#pragma region Parse_Data_Vars
	uint32_t ReadBufferSize = 0;
	const OpCodes* BaseOpcodes;//dynamic opcode list
	const Script* HLData;//data to parse(High Level Data)
	uint32_t FunctionCount = 0;
	uint32_t InstructionCount = 0;
#pragma endregion

#pragma region Write_Data_Vars

	PHO SavedOffsets = {};
	int32_t headerLocation = 0;
	uint32_t headerFlag = 0;
	uint32_t CodePageCount = 0;
	std::vector<uint8_t> BuildBuffer;
	uint8_t FilePadding = 0;
#pragma endregion


#define DATA HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)
#define AddOpcode(op) AddInt8(BaseOpcodes->##op);

#pragma region Data_Functions
	inline void AddPadding(const uint16_t value)
	{
		CodePageData.resize(CodePageData.size() + value);
	}
	inline void AddInt8(const uint8_t b)
	{
		CodePageData.push_back(b);
	}
	inline void AddInt16(const int16_t value)
	{
		CodePageData.resize(CodePageData.size() + 2, 0);
		*((int16_t*)(CodePageData.data() + CodePageData.size()) - 1) = value;
	}
	inline void AddInt24(const uint32_t value)
	{
		CodePageData.resize(CodePageData.size() + 3, 0);
		*((uint32_t*)(CodePageData.data() + CodePageData.size()) - 1) |= (value & 0xFFFFFF) << 8;
	}
	inline void AddInt32(const int32_t value)
	{
		CodePageData.resize(CodePageData.size() + 4, 0);
		*((int32_t*)(CodePageData.data() + CodePageData.size()) - 1) = value;
	}
	inline void AddFloat(const float value)
	{
		CodePageData.resize(CodePageData.size() + 4, 0);
		*((float*)(CodePageData.data() + CodePageData.size()) - 1) = value;
	}
	inline void AddString(const std::string str)//Override: GTAV
	{
		CodePageData.resize(CodePageData.size() + str.size() + 1);
		memcpy(CodePageData.data() + CodePageData.size() - str.size() - 1, str.data(), str.size() + 1);
	}
	void AddLabel(const std::string label);
	inline void AddFuncLabel(const FunctionData* function)
	{
		if (FuncLocations.find(function) == FuncLocations.end())
			FuncLocations.insert({ function, CodePageData.size() });
		else
			Utils::System::Throw("Cannot add function. function \"" + function->getName() + "\" already exists.");
	}
	inline void AddJumpLoc(const JumpInstructionType it, const std::string label)
	{
		// this should only be called on jump forward
		JumpLocations.push_back({ CodePageData.size(), it, label, false });
		LabelLocations[label].JumpIndexes.push_back(JumpLocations.size() - 1);
		switch (it)
		{
			case JumpInstructionType::Switch:
			case JumpInstructionType::Jump:
			case JumpInstructionType::JumpFalse:
			case JumpInstructionType::JumpEQ:
			case JumpInstructionType::JumpNE:
			case JumpInstructionType::JumpGT:
			case JumpInstructionType::JumpGE:
			case JumpInstructionType::JumpLT:
			case JumpInstructionType::JumpLE:		AddInt16(0); break;
			case JumpInstructionType::LabelLoc:		AddInt24(0); break;
			default: assert(false && "Invalid Type");
		}
	}
	void AddJump(const JumpInstructionType type, const std::string label);
	JumpLabelData AddSwitchJump(const JumpInstructionType type, const std::string label);
	inline uint32_t AddNative(const uint64_t hash)
	{
		std::unordered_map<uint64_t, uint32_t>::iterator findRes = NativeHashMap.find(hash);
		const uint32_t size = NativeHashMap.size();
		if (findRes != NativeHashMap.end())
			return findRes->second;
		else
			NativeHashMap.insert({ hash, size });
		return size;
	}
	inline uint32_t GetNativeIndex(const uint32_t hash)
	{
		std::unordered_map<uint64_t, uint32_t>::iterator it = NativeHashMap.find(hash);
		if (it != NativeHashMap.end())
			return it->second;
		else
			Utils::System::Throw("Native with hash \"" + std::to_string(hash) + "\" does not exist");
		return 0;
	}
	inline void DoesOpcodeHaveRoom(const size_t OpcodeLen)
	{
		size_t size = CodePageData.size();
		uint32_t amount = (size + OpcodeLen) % 16384;
		if (amount < size % 16384 && amount != 0)
		{
			CodePageData.resize(size + (16384 - (size % 16384)));
			CheckSignedJumps();
			CheckUnsignedJumps();
		}
	}
	void CheckSignedJumps();
	void CheckUnsignedJumps();
	inline bool FindNextSignedJumpLocation()
	{
		for (; SignedJumpLocationInc < JumpLocations.size() && (JumpLocations[SignedJumpLocationInc].isSet || JumpLocations[SignedJumpLocationInc].InstructionType == JumpInstructionType::LabelLoc || JumpLocations[SignedJumpLocationInc].InstructionType == JumpInstructionType::Switch); SignedJumpLocationInc++);

		return SignedJumpLocationInc < JumpLocations.size();
	}
	inline bool FindNextUnsignedJumpLocation()
	{
		for (; UnsignedJumpLocationInc < JumpLocations.size() && (JumpLocations[UnsignedJumpLocationInc].isSet || JumpLocations[UnsignedJumpLocationInc].InstructionType != JumpInstructionType::Switch); UnsignedJumpLocationInc++);

		return UnsignedJumpLocationInc < JumpLocations.size();
	}
#pragma endregion

#pragma region Opcode_Functions
	void AddFunction(const FunctionData* function)
	{
#if _DEBUG
		std::string name = function->getName();
		DoesOpcodeHaveRoom(5 + name.size());
		AddFuncLabel(function);
		AddOpcode(Function);
		AddInt8(function->getParamCount());
		AddInt16(function->getStackSize());
		AddInt8(name.size());
		CodePageData.resize(CodePageData.size() + name.size());
		memcpy(CodePageData.data() + CodePageData.size() - name.size(), name.data(), name.size());
#else
		DoesOpcodeHaveRoom(5);
		AddFuncLabel(function);
		AddOpcode(Function);
		AddInt8(function->getParamCount());
		AddInt16(function->getStackSize());
		AddInt8(0);//unused function name
#endif
	}
	void PushInt(const int32_t Literal);
	void PushInt(){ PushInt(DATA->getInt()); }
	void PushBytes();
	void PushFloat(const float Literal);
	void PushFloat(){ PushFloat(DATA->getFloat()); }
	void PushString();//Override: GTAV
	void CallNative(const uint64_t hash = -1, const uint8_t paramCount = -1, const uint8_t returnCount = -1);
	void Return() { DoesOpcodeHaveRoom(3); AddOpcode(Return); AddInt8(DATA->getByte(0)); AddInt8(DATA->getByte(1)); };
	void GetArrayP();
	void GetArray();
	void SetArray();
	void GetFrameP();
	void GetFrame();
	void SetFrame();
	void GetStaticP();
	void GetStatic();
	void SetStatic();
	void GetGlobalP();
	void GetGlobal();
	void SetGlobal();
	void StrCopy() { DoesOpcodeHaveRoom(2); AddOpcode(StrCopy); AddInt8(DATA->getByte(0)); };
	void ItoS() { DoesOpcodeHaveRoom(2); AddOpcode(ItoS); AddInt8(DATA->getByte(0)); };
	void StrAdd() { DoesOpcodeHaveRoom(2); AddOpcode(StrAdd); AddInt8(DATA->getByte(0)); };
	void StrAddI() { DoesOpcodeHaveRoom(2); AddOpcode(StrAddi); AddInt8(DATA->getByte(0)); };
	void pCall() { AddOpcode(pCall); };
	void GetHash() { AddOpcode(GetHash); };
	void Call();
	void AddFuncLoc(const FunctionData* function);
	void Switch();
	void AddImm(const int32_t Literal);
	void AddImm(){ AddImm(DATA->getInt()); }
	void MultImm(const int32_t Literal);//Override: GTAIV
	void MultImm(){ MultImm(DATA->getInt()); }
	void FAddImm();
	void FMultImm(){ PushFloat(); AddOpcode(fMult); }
	void GetImmP();
	void GetImm();
	void SetImm();
	void GoToStack();
	void AddJumpTable();
#pragma endregion

#pragma region Write_Functions

	void ClearWriteVars()
	{
		SavedOffsets = {};
		headerLocation = 0;
		headerFlag = 0;
		CodePageCount = 0;
		BuildBuffer.clear();
	}
	void AddInt32toBuff(int32_t value)
	{
		BuildBuffer.resize(BuildBuffer.size() + 4, 0);
		*((int32_t*)(BuildBuffer.data() + BuildBuffer.size()) - 1) = value;
	}
	void AddInt64toBuff(int64_t value)
	{
		BuildBuffer.resize(BuildBuffer.size() + 8, 0);
		*((int32_t*)(BuildBuffer.data() + BuildBuffer.size()) - 1) = value;
	}
	void ChangeInt32inBuff(int32_t value, uint32_t index)
	{
		*(int32_t*)(BuildBuffer.data() + index) = value;
	}
	void ChangeInt64inBuff(int64_t value, uint32_t index)
	{
		*(int64_t*)(BuildBuffer.data() + index) = value;
	}
	uint32_t GetSpaceLeft(uint32_t size)const 
	{
		const uint32_t rem = size - (BuildBuffer.size() % size);
		return rem == 0 ? size : rem;
	}
	void FillPageNops()
	{
		BuildBuffer.resize(BuildBuffer.size() + GetSpaceLeft(16384), 0);
	}
	void FillPageDynamic(uint32_t amount)
	{
		BuildBuffer.resize(BuildBuffer.size() + GetSpaceLeft(amount), FilePadding);
	}
	void PadNops()
	{
		const int32_t pad = 16 - BuildBuffer.size() % 16;
		if (pad == 0 || pad == 16)
			return;
		else if (pad > 16384)
			Utils::System::Throw("Pad Over 16364");

		BuildBuffer.resize(BuildBuffer.size() + pad, 0);
	}
	int32_t GetPadExpectedAmount(int32_t val)
	{
		const int32_t pad = 16 - val % 16;
		return pad == 0 || pad == 16 ? val : pad + val;
	}
	void Pad()
	{
		const int32_t pad = 16 - BuildBuffer.size() % 16;
		if (pad == 0 || pad == 16)
			return;
		else if (pad > 16384)
			Utils::System::Throw("Pad Over 16364");

		BuildBuffer.resize(BuildBuffer.size() + pad, FilePadding);
	}
	void ForcePad()
	{
		const int32_t pad = 16 - BuildBuffer.size() % 16;
		if (pad == 0 || pad == 16)
		{
			BuildBuffer.resize(BuildBuffer.size() + 16, FilePadding);
			return;
		}
		else if (pad > 16384)
			Utils::System::Throw("ForcePad Over 16364");
		else
			BuildBuffer.resize(BuildBuffer.size() + pad, FilePadding);
	}
	int32_t IntToPointerInt(int32_t x) { return 0x50000000 | x; }

	void WriteCodePagesNoPadding();
	void Write16384CodePages();
	void WriteFinalCodePage();
	void WriteNativesNoPadding();
	void WriteNatives();
	void WriteStaticsNoPadding();
	void WriteStatics();

#pragma endregion

#pragma region Parse_Functions
	void BuildTables();
	void fixFunctionJumps();
	void fixFunctionCalls();
	void ParseGeneral(const OpcodeKind OK);
	int32_t GetSizeFromFlag(uint32_t flag, int32_t baseSize);
	int32_t GetSizeFromSystemFlag(uint32_t flag);
	int32_t GetSizeFromGraphicsFlag(uint32_t flag);
	uint32_t GetFlagFromSize(int32_t size);
	const uint32_t AddStringToStringPage(const std::string str);
#pragma endregion

#pragma region Type_Defines
	enum class ResourceType : uint8_t
	{
		XenonTextDict = 7,
		WinTextDict = 8,
		ScriptContainer = 9,
		Particles_0 = 27,
		Bounds = 32,
		Particles_1 = 36,
		XenonModel = 109,
		WinModel = 110,
		WinModelFlag = 112
	};
#pragma endregion

#pragma region Write_Functions
	void WriteHeader();
	void WritePointers();
	void Write16384StringPages();
	void WriteFinalStringPage();
	void XSCWrite(const char* path, bool AddRsc7Header = false);
#pragma endregion

};