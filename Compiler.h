#pragma once
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "Utils.h"
#include "FunctionOpcode.h"
#include "OpcodeConsts.h"
#include "ConstExpr.h"
#include "Script.h"

using namespace Utils::System;
using namespace Utils::Bitwise;
using namespace Utils::Hashing;

#pragma warning( disable : 4201 )//unnamed struct extention
typedef union OpCodes {
	const uint8_t A[164];
	struct {
		const uint8_t
			Nop
			, Add
			, Sub
			, Mult
			, Div
			, Mod
			, Not
			, Neg
			, CmpEq
			, CmpNe
			, CmpGt
			, CmpGe
			, CmpLt
			, CmpLe
			, fAdd
			, fSub
			, fMult
			, fDiv
			, fMod
			, fNeg
			, fCmpEq
			, fCmpNe
			, fCmpGt
			, fCmpGe
			, fCmpLt
			, fCmpLe
			, vAdd
			, vSub
			, vMult
			, vDiv
			, vNeg
			, And
			, Or
			, Xor
			, ItoF
			, FtoI
			, FtoV
			, PushB
			, PushB2
			, PushB3
			, Push
			, PushF
			, Dup
			, Drop
			, CallNative
			, Function
			, Return
			, pGet
			, pSet
			, pPeekSet
			, ToStack
			, FromStack
			, GetArrayP1
			, GetArray1
			, SetArray1
			, GetFrameP1
			, GetFrame1
			, SetFrame1
			, GetStaticP1
			, GetStatic1
			, SetStatic1
			, Add1
			, Mult1
			, GetImm1
			, SetImm1
			, PushS
			, Add2
			, Mult2
			, GetImm2
			, SetImm2
			, GetArrayP2
			, GetArray2
			, SetArray2
			, GetFrameP2
			, GetFrame2
			, SetFrame2
			, GetStaticP2
			, GetStatic2
			, SetStatic2
			, GetGlobalP2
			, GetGlobal2
			, SetGlobal2
			, Jump
			, JumpFalse
			, JumpNE
			, JumpEQ
			, JumpLE
			, JumpLT
			, JumpGE
			, JumpGT
			, Call
			, GetGlobalP3
			, GetGlobal3
			, SetGlobal3
			, PushI24
			, Switch
			, PushString
			, StrCopy
			, ItoS
			, StrAdd
			, StrAddi
			, MemCopy
			, Catch
			, Throw
			, pCall
			, Push_Neg1
			, Push_0
			, Push_1
			, Push_2
			, Push_3
			, Push_4
			, Push_5
			, Push_6
			, Push_7
			, PushF_Neg1
			, PushF_0
			, PushF_1
			, PushF_2
			, PushF_3
			, PushF_4
			, PushF_5
			, PushF_6
			, PushF_7

			///Extra GTAV Opcodes
			, GetHash
			, GetImmP2
			, GetImmP
			, GetImmP1

			///Extra RDR Opcodes
			, Call2
			, Call2h1
			, Call2h2
			, Call2h3
			, Call2h4
			, Call2h5
			, Call2h6
			, Call2h7
			, Call2h8
			, Call2h9
			, Call2hA
			, Call2hB
			, Call2hC
			, Call2hD
			, Call2hE
			, Call2hF
			, PushArrayP
			, ReturnP0R0
			, ReturnP0R1
			, ReturnP0R2
			, ReturnP0R3
			, ReturnP1R0
			, ReturnP1R1
			, ReturnP1R2
			, ReturnP1R3
			, ReturnP2R0
			, ReturnP2R1
			, ReturnP2R2
			, ReturnP2R3
			, ReturnP3R0
			, ReturnP3R1
			, ReturnP3R2
			, ReturnP3R3

			///RDR and GTAIV Opcodes
			, PushStringNull

			///GTAIV Extra Opcodes
			, JumpTrue
			, GetFrameP0
			, GetFrameP3
			, GetFrameP4
			, GetFrameP5
			, GetFrameP6
			, GetFrameP7
			, GetFrameP
			, GetGlobalP
			, GetStaticP
			, GetArrayP
			, GetXProtect//PC
			, SetXProtect//PC
			, RefXProtect//PC
			, Exit

			;
	};
} OpCodes;

class CompileBase
{
protected:

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
		const string Label;
	}JumpData;
	typedef struct
	{
		const uint32_t CallLocation;
		const CallInstructionType InstructionType;
		const string FuncName;
	}CallData;
	#pragma endregion

	#pragma region Parsed_Data_Vars
	vector<uint8_t> CodePageData;//opcode data
	unordered_map<string, uint32_t> LabelLocations;//label ,data index
	vector<JumpData> JumpLocations;//JumpLocations to fill after building the CodePageData for a function
	unordered_map<string, uint32_t> FuncLocations;//call, data index
	vector<CallData> CallLocations;//CallLocations to fill after building the CodePageData
	unordered_map<uint32_t, uint32_t> NativeHashMap;//hash, index  (native hash map has index start of 1) (hash map list for NativesList to limit find recursion)
	#pragma endregion

	#pragma region Parse_Data_Vars
	const OpCodes* BaseOpcodes;//dynamic opcode list
	const Script* HLData;//data to parse(High Level Data)
	uint32_t FunctionCount = 0;
	uint32_t InstructionCount = 0;
	Platform tPlatform;
	#pragma endregion

	#define DATA HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)
	#define AddOpcode(op) AddInt8(BaseOpcodes->##op);

	CompileBase(const OpCodes& Op, const Script& data, const uint32_t Function_Count, const uint32_t Instruction_Count, Platform tPlat)
	{
		BaseOpcodes = &Op;
		HLData = &data;
		FunctionCount = Function_Count;
		InstructionCount = Instruction_Count;
		tPlatform = tPlat;
	}

	#pragma region Data_Functions
	inline void AddInt8(const uint8_t b)
	{
		CodePageData.push_back(b);
	}
	inline void AddInt16(const int16_t value)
	{
		CodePageData.resize(CodePageData.size() + 2, 0);
		*((int16_t*)(CodePageData.data() + CodePageData.size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
	inline void AddInt24(const uint32_t value)
	{
		CodePageData.resize(CodePageData.size() + 3, 0);
		*((uint32_t*)(CodePageData.data() + CodePageData.size()) - 1) |= Utils::Bitwise::SwapEndian(value & 0xFFFFFF);
	}
	inline void AddInt32(const int32_t value)
	{
		CodePageData.resize(CodePageData.size() + 4, 0);
		*((int32_t*)(CodePageData.data() + CodePageData.size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
	inline void AddFloat(const float value)
	{
		CodePageData.resize(CodePageData.size() + 4, 0);
		*((float*)(CodePageData.data() + CodePageData.size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
	inline void AddString(const string str)//Override: GTAV
	{
		CodePageData.resize(CodePageData.size() + str.size() + 1);
		memcpy(CodePageData.data() + CodePageData.size() - str.size() - 1, str.data(), str.size() + 1);
	}
	inline void AddLabel(const string label)
	{
		if (LabelLocations.find(label) == LabelLocations.end())
			LabelLocations.insert({ label, CodePageData.size() });
		else
			Throw("Cannot add label. Label \"" + label + "\" already exists.");
	}
	inline void AddFuncLabel(const string label)
	{
		if (FuncLocations.find(label) == FuncLocations.end())
			FuncLocations.insert({ label, CodePageData.size() });
		else
			Throw("Cannot add function. function \"" + label + "\" already exists.");
	}
	inline void AddJumpLoc(const JumpInstructionType it, const string label)
	{
		JumpLocations.push_back({ CodePageData.size(), it, label });
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
	virtual void AddJump(const JumpInstructionType type, const string label);//Override: GTAIV
	inline uint32_t AddNative(const uint32_t hash)
	{
		unordered_map<uint32_t, uint32_t>::iterator findRes = NativeHashMap.find(hash);
		const uint32_t size = NativeHashMap.size();
		if (findRes != NativeHashMap.end())
			return findRes->second;
		else
			NativeHashMap.insert({ hash, size });
		return size;
	}
	inline uint32_t GetNativeIndex(const uint32_t hash)
	{
		unordered_map<uint32_t, uint32_t>::iterator it = NativeHashMap.find(hash);
		if (it != NativeHashMap.end())
			return it->second;
		else
			Throw("Native with hash \""+to_string(hash)+"\" does not exist");
		return 0;
	}
	inline void DoesOpcodeHaveRoom(const size_t OpcodeLen)
	{
		size_t size = CodePageData.size();
		uint32_t amount = (size + OpcodeLen) % 16384;
		if (amount < size % 16384 && amount != 0)
			CodePageData.resize(size + (16384 - (size % 16384)));
	}
	#pragma endregion

	#pragma region Opcode_Functions
	virtual void AddFunction(string name, uint8_t paramCount, uint16_t stackSize)
	{
#if _DEBUG
		DoesOpcodeHaveRoom(5 + name.size());
		AddFuncLabel(name);
		AddOpcode(Function);
		AddInt8(paramCount);
		AddInt16(stackSize);
		AddInt8(name.size());
		CodePageData.resize(CodePageData.size() + name.size());
		memcpy(CodePageData.data() + CodePageData.size() - name.size(), name.data(), name.size());
#else
		DoesOpcodeHaveRoom(5);
		AddFuncLabel(name);
		AddOpcode(Function);
		AddInt8(paramCount);
		AddInt16(stackSize);
		AddInt8(0);//unused function name
#endif
	}
	virtual void PushInt(const int32_t Literal);//Override: GTAIV
	void PushInt(){ PushInt(DATA->getInt()); }
	virtual void PushBytes();//Override: GTAIV
	virtual void PushFloat(const float Literal);//Override: GTAIV
	void PushFloat(){ PushFloat(DATA->getFloat()); }
	virtual void PushString();//Override: GTAV
	virtual void CallNative(const uint32_t hash = -1, const uint8_t paramCount = -1, const uint8_t returnCount = -1) { assert(false && "CallNative has to be overridden"); };//Override: ALL
	virtual void Return() { DoesOpcodeHaveRoom(3); AddOpcode(Return); AddInt8(DATA->getByte(0)); AddInt8(DATA->getByte(1)); };//Override: RDR
	virtual void GetArrayP();//Override: GTAIV
	virtual void GetArray();//Override: GTAIV
	virtual void SetArray();//Override: GTAIV
	virtual void GetFrameP();//Override: GTAIV
	virtual void GetFrame();//Override: GTAIV
	virtual void SetFrame();//Override: GTAIV
	virtual void GetStaticP();//Override: GTAIV
	virtual void GetStatic();//Override: GTAIV
	virtual void SetStatic();//Override: GTAIV
	virtual void GetGlobalP();//Override: GTAIV
	virtual void GetGlobal();//Override: GTAIV
	virtual void SetGlobal();//Override: GTAIV
	virtual void StrCopy() { DoesOpcodeHaveRoom(2); AddOpcode(StrCopy); AddInt8(DATA->getByte(0)); };//Override: GTAIV
	virtual void ItoS() { DoesOpcodeHaveRoom(2); AddOpcode(ItoS); AddInt8(DATA->getByte(0)); };;//Override: GTAIV
	virtual void StrAdd() { DoesOpcodeHaveRoom(2); AddOpcode(StrAdd); AddInt8(DATA->getByte(0)); };;//Override: GTAIV
	virtual void StrAddI() { DoesOpcodeHaveRoom(2); AddOpcode(StrAddi); AddInt8(DATA->getByte(0)); };;//Override: GTAIV
	virtual void pCall() { AddOpcode(pCall); };//Override: GTAIV
	virtual void GetHash() { assert(false && "GetHash has to be overridden"); };//Override: ALL
	virtual void Call() { assert(false && "Call has to be overridden"); };//Override: ALL
	virtual void AddFuncLoc(const string funcName);
	void Switch();//for gta4 switches override AddJump
	virtual void AddImm(const int32_t Literal);//Override: GTAIV
	void AddImm(){ AddImm(DATA->getInt()); }
	virtual void MultImm(const int32_t Literal);//Override: GTAIV
	void MultImm(){ MultImm(DATA->getInt()); }
	void FAddImm();
	void FMultImm();
	virtual void GetImmP() { MultImm(4); AddOpcode(Add); };//Override: GTAV
	virtual void GetImm() { assert(false && "GetImm has to be overridden"); };//Override: ALL
	virtual void SetImm() { assert(false && "SetImm has to be overridden"); };//Override: ALL
	#pragma endregion

	#pragma region Write_Functions

	#pragma endregion

	#pragma region Parse_Functions
	void BuildTables();
	virtual void fixFunctionJumps();
	virtual void fixFunctionCalls() = 0;
	void ParseGeneral(const OpcodeKind OK);
	#pragma endregion
};

class CompileRDR : CompileBase
{
public:
	CompileRDR(Script& data, Platform tPlatform) : CompileBase(RDROpcodes, data, 0, 0, tPlatform) { }

	void CompileXSC(string fileName)
	{
		BuildTables();
		XSCWrite(fileName.c_str(), P_XBOX, false);
	}
private:
	//visual studio plz... designated initializers were added in 1999 get with the times
	const OpCodes RDROpcodes = { RO_Nop, RO_Add, RO_Sub, RO_Mult, RO_Div, RO_Mod, RO_Not, RO_Neg, RO_CmpEq, RO_CmpNe, RO_CmpGt, RO_CmpGe, RO_CmpLt, RO_CmpLe, RO_fAdd, RO_fSub, RO_fMult, RO_fDiv, RO_fMod, RO_fNeg, RO_fCmpEq, RO_fCmpNe, RO_fCmpGt, RO_fCmpGe, RO_fCmpLt, RO_fCmpLe, RO_vAdd, RO_vSub, RO_vMult, RO_vDiv, RO_vNeg, RO_And, RO_Or, RO_Xor, RO_ItoF, RO_FtoI, RO_FtoV, RO_PushB, RO_PushB2, RO_PushB3, RO_Push, RO_PushF, RO_Dup, RO_Drop, RO_CallNative, RO_Function, RO_Return, RO_pGet, RO_pSet, RO_pPeekSet, RO_ToStack, RO_FromStack, RO_GetArrayP1, RO_GetArray1, RO_SetArray1, RO_GetFrameP1, RO_GetFrame1, RO_SetFrame1, RO_GetStaticP1, RO_GetStatic1, RO_SetStatic1, RO_Add1, RO_Mult1, RO_GetImm1, RO_SetImm1, RO_PushS, RO_Add2, RO_Mult2, RO_GetImm2, RO_SetImm2, RO_GetArrayP2, RO_GetArray2, RO_SetArray2, RO_GetFrameP2, RO_GetFrame2, RO_SetFrame2, RO_GetStaticP2, RO_GetStatic2, RO_SetStatic2, RO_GetGlobalP2, RO_GetGlobal2, RO_SetGlobal2, RO_Jump, RO_JumpFalse, RO_JumpNE, RO_JumpEQ, RO_JumpLE, RO_JumpLT, RO_JumpGE, RO_JumpGT, RO_Nop, RO_GetGlobalP3, RO_GetGlobal3, RO_SetGlobal3, RO_PushI24, RO_Switch, RO_PushString, RO_StrCopy, RO_ItoS, RO_StrAdd, RO_StrAddi, RO_MemCopy, RO_Catch, RO_Throw, RO_pCall, RO_Push_Neg1, RO_Push_0, RO_Push_1, RO_Push_2, RO_Push_3, RO_Push_4, RO_Push_5, RO_Push_6, RO_Push_7, RO_PushF_Neg1, RO_PushF_0, RO_PushF_1, RO_PushF_2, RO_PushF_3, RO_PushF_4, RO_PushF_5, RO_PushF_6, RO_PushF_7, RO_Nop, RO_Nop, RO_Nop, RO_Nop, RO_Call2, RO_Call2h1, RO_Call2h2, RO_Call2h3, RO_Call2h4, RO_Call2h5, RO_Call2h6, RO_Call2h7, RO_Call2h8, RO_Call2h9, RO_Call2hA, RO_Call2hB, RO_Call2hC, RO_Call2hD, RO_Call2hE, RO_Call2hF, RO_PushArrayP, RO_ReturnP0R0, RO_ReturnP0R1, RO_ReturnP0R2, RO_ReturnP0R3, RO_ReturnP1R0, RO_ReturnP1R1, RO_ReturnP1R2, RO_ReturnP1R3, RO_ReturnP2R0, RO_ReturnP2R1, RO_ReturnP2R2, RO_ReturnP2R3, RO_ReturnP3R0, RO_ReturnP3R1, RO_ReturnP3R2, RO_ReturnP3R3, RO_PushStringNull };
	
	#pragma region Type_Defines
	enum class Rsc85Flags
	{
		F4096 = 0x80
		, F65536 = 0xC0
		, F16384 = 0xA0
		, F8192 = 0x90
		, Fi4096 = (int32_t)0x80000000
		, Fi65536 = (int32_t)0xC0000000
		, Fi16384 = (int32_t)0xA0000000
		, Fi8192 = (int32_t)0x90000000
	};
	#pragma endregion

	#pragma region CallParsing
	inline const uint8_t GetNewCallOpCode(const uint32_t needOffset) const { 
		return needOffset >= 1048576 ? 255 : 82 + (needOffset >> 16); 
	}
	inline const uint16_t GetNewCallOffset(const uint32_t needOffset) const { 
		return needOffset - (((needOffset >> 16)) << 16); 
	}
	inline const int32_t GetCallOffset(const int32_t readOffset, const int32_t opCode) const {
		return readOffset | ((opCode - 82) << 16); 
	}
	#pragma endregion
	#pragma region NativeParsing
	inline const int32_t GetArgCountFromIndex(const uint16_t* Indblock) const {
		return (((uint8_t*)Indblock)[0] & 0x3e) >> 1; 
	}
	inline const int32_t GetIndex(const uint16_t val) const {
		return (((val & 0xFF) << 2) & 0x300) | ((val >> 8) & 0xFF);
	}
	inline const bool FunctionHasReturn(const uint16_t* data) const { 
		return (((uint8_t*)data)[0] & 1) == 1 ? true : false; 
	}
	inline const uint16_t SetNewIndex(const uint16_t index, const int parameterCount, const bool ret) const { 
		return SwapEndian((uint16_t)(((index & 0xFF00) >> 2) | ((index & 0xFF) << 8) | (ret ? 1 : 0) | (parameterCount << 1)));
	}
	#pragma endregion
	#pragma region RSC85Parsing
	uint32_t GetHeaderFormatFromFlag(uint32_t val);
	uint32_t GetFlagFromReadbuffer(uint32_t buffer);
	const uint32_t GetFullFlagWithSize(const uint32_t size, const uint32_t flag)
	{
		return flag | (size >> 12 & 0xFF) | (size >> 12 & 0xFF00) | (size >> 12 & 0xFF0000);
	}
	int32_t IntToPointerInt(int32_t x) { return 0x50000000 | x; }
	#pragma endregion
	
	#pragma region Opcode_Functions
	void CallNative(const uint32_t hash, const uint8_t paramCount,const uint8_t returnCount) override;
	void Return() override;
	void GetHash() override { CallNative(JoaatConst("string_to_hash"), 1, 1); };
	void Call() override;
	void GetImm() override;
	void SetImm() override;	
	#pragma endregion
	
	#pragma region Parse_Functions
	void fixFunctionCalls() override;
	#pragma endregion

	#pragma region Write_Functions
	void XSCWrite(const char* path, Platform platform, bool CompressAndEncrypt = true);
	#pragma endregion

};

class CompileGTAV : CompileBase
{
public:
	CompileGTAV(Script& data, Platform tPlatform) : CompileBase(GTAVOpcodes, data, 0, 0, tPlatform) { }
private:
	const OpCodes GTAVOpcodes = { VO_Nop, VO_Add, VO_Sub, VO_Mult, VO_Div, VO_Mod, VO_Not, VO_Neg, VO_CmpEq, VO_CmpNe, VO_CmpGt, VO_CmpGe, VO_CmpLt, VO_CmpLe, VO_fAdd, VO_fSub, VO_fMult, VO_fDiv, VO_fMod, VO_fNeg, VO_fCmpEq, VO_fCmpNe, VO_fCmpGt, VO_fCmpGe, VO_fCmpLt, VO_fCmpLe, VO_vAdd, VO_vSub, VO_vMult, VO_vDiv, VO_vNeg, VO_And, VO_Or, VO_Xor, VO_ItoF, VO_FtoI, VO_FtoV, VO_PushB, VO_PushB2, VO_PushB3, VO_Push, VO_PushF, VO_Dup, VO_Drop, VO_CallNative, VO_Function, VO_Return, VO_pGet, VO_pSet, VO_pPeekSet, VO_ToStack, VO_FromStack, VO_GetArrayP1, VO_GetArray1, VO_SetArray1, VO_GetFrameP1, VO_GetFrame1, VO_SetFrame1, VO_GetStaticP1, VO_GetStatic1, VO_SetStatic1, VO_Add1, VO_Mult1, VO_GetImm1, VO_SetImm1, VO_PushS, VO_Add2, VO_Mult2, VO_GetImm2, VO_SetImm2, VO_GetArrayP2, VO_GetArray2, VO_SetArray2, VO_GetFrameP2, VO_GetFrame2, VO_SetFrame2, VO_GetStaticP2, VO_GetStatic2, VO_SetStatic2, VO_GetGlobalP2, VO_GetGlobal2, VO_SetGlobal2, VO_Jump, VO_JumpFalse, VO_JumpNE, VO_JumpEQ, VO_JumpLE, VO_JumpLT, VO_JumpGE, VO_JumpGT, VO_Call, VO_GetGlobalp3, VO_GetGlobal3, VO_SetGlobal3, VO_PushI24, VO_Switch, VO_PushString, VO_StrCopy, VO_ItoS, VO_StrAdd, VO_StrAddi, VO_Memcopy, VO_Catch, VO_Throw, VO_pCall, VO_Push_Neg1, VO_Push_0, VO_Push_1, VO_Push_2, VO_Push_3, VO_Push_4, VO_Push_5, VO_Push_6, VO_Push_7, VO_PushF_Neg1, VO_PushF_0, VO_PushF_1, VO_PushF_2, VO_PushF_3, VO_PushF_4, VO_PushF_5, VO_PushF_6, VO_PushF_7, VO_GetImmP, VO_GetImmP1, VO_GetImmP2, VO_GetHash };

	#pragma region Type_Defines
	struct StrIndex {
		uint32_t index;
		const uint32_t len;
	};
	#pragma endregion

	#pragma region Parsed_Data_Vars
	vector<uint8_t> StringPageData;
	vector<StrIndex> StringPageDataIndexing;
	#pragma endregion

	#pragma region Parse_Functions
	const uint32_t AddStringToStringPage(const string str);
	void fixFunctionCalls() override;
	#pragma endregion

	#pragma region Opcode_Functions
	void CallNative(const uint32_t hash, const uint8_t paramCount, const uint8_t returnCount) override;
	void GetHash() override { AddOpcode(GetHash); };
	void Call() override;
	void PushString() override;
	void GetImmP() override { AddOpcode(GetImmP); };
	void GetImm() override;
	void SetImm() override;
	#pragma endregion
};
