#pragma once
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "Utils.h"
#include "FunctionOpcode.h"
#include "OpcodeConsts.h"
#include "ConstExpr.h"

using namespace Utils::System;


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
private:
	enum class JumpType
	{
		  Jump
		, JumpFalse
		, JumpNE
		, JumpEQ
		, JumpLE
		, JumpLT
		, JumpGE
		, JumpGT
		, Switch
	};
	typedef struct JumpData
	{
		uint32_t JumpLocation;
		string Label;
	};

protected:
	vector<uint8_t> CodePageData;
	map<string, uint32_t> LabelLocations;//label ,data index
	vector<JumpData> JumpLocations;
	OpCodes* BaseOpcodes;
	vector<FunctionData*> HLData;
	uint32_t FunctionCount;
	uint32_t InstructionCount;

public:
	#define DATA HLData[FunctionCount]->Instructions[InstructionCount]
	#define AddOpcode(op) AddByte(BaseOpcodes->##op);

	CompileBase(OpCodes& Op, vector<FunctionData*> data, uint32_t FC, uint32_t IC)
	{
		BaseOpcodes = &Op;
		HLData = data;
		FunctionCount = FC;
		InstructionCount = IC;
	}

	inline void AddByte(uint8_t b)
	{
		CodePageData.push_back(b);
	}
	inline void AddShort(int s)
	{
		CodePageData.resize(CodePageData.size() + 2);
		*(short*)(CodePageData.data() + CodePageData.size() - 2) = s;
	}
	inline void AddTriByte(int t)
	{
		CodePageData.resize(CodePageData.size() + 3);
		memcpy(CodePageData.data() + CodePageData.size() - 3, (char*)&t + 1, 3);
	}
	inline void AddInt(int i)
	{
		CodePageData.resize(CodePageData.size() + 4);
		*(int*)(CodePageData.data() + CodePageData.size() - 4) = i;
	}
	inline void AddLabel(string label)
	{
		if (CodePageData.size() == 0)//label indexing optimising
			AddOpcode(Nop);

		if (LabelLocations[label] == 0)
			LabelLocations.insert({ label, CodePageData.size() });
		else
			Throw("Label \"" + label + "\" already exists");
	}
	inline uint32_t GetLabel(string label)
	{
		if (LabelLocations[label] != 0)
			return LabelLocations[label];
		else
			Throw("Label \"" + label + "\" not found");
		return 0;
	}
	virtual inline void AddJump(JumpType type, string label)//gta 4 needs to override 
	{
		switch (type)
		{
			case JumpType::Jump:		AddOpcode(Jump); AddShort(0); break;
			case JumpType::JumpFalse:	AddOpcode(JumpFalse); AddShort(0); break;
			case JumpType::JumpNE:		AddOpcode(JumpNE); AddShort(0); break;
			case JumpType::JumpEQ:		AddOpcode(JumpEQ); AddShort(0); break;
			case JumpType::JumpLE:		AddOpcode(JumpLE); AddShort(0); break;
			case JumpType::JumpLT:		AddOpcode(JumpLT); AddShort(0); break;
			case JumpType::JumpGE:		AddOpcode(JumpGE); AddShort(0); break;
			case JumpType::JumpGT:		AddOpcode(JumpGT); AddShort(0); break;
			case JumpType::Switch:		AddShort(0); break;
			default: assert(false && "Invalid Type");
				
		}
		JumpLocations.push_back({CodePageData.size(), label});
	}
		

	virtual void PushInt();
	virtual void PushBytes();
	virtual void PushFloat();
	virtual void PushString();
	virtual void CallNative();
	virtual void Return();
	virtual void StrCopy();
	virtual void ItoS();
	virtual void StrAdd();
	virtual void StrAddI();
	virtual void MemCopy();
	virtual inline void pCall(){ AddOpcode(pCall); }
	virtual void GetHash();
	virtual void Call();

	void Switch()
	{
		AddOpcode(Switch);
		//AddByte(DATA->getByte());

		SwitchCaseStorage* sCase = DATA->storage.switchCase;
		uint32_t CaseCount = CodePageData.size();
		AddByte(0);

		assert(sCase && "Empty Switch Statement");
		uint32_t i = 0;
		while (sCase->hasNextCase())
		{
			sCase = sCase->getNextCase();
			AddInt(sCase->getCase());
			AddJump(JumpType::Switch, sCase->getLoc());
			i++;
		}
		CodePageData[CaseCount] = i;
	}

	void ParseGeneral(OpcodeKind OK);
		
};

class CompileRDR : CompileBase
{
	//visual studio plz... designated initializers were added in 1999 get with the times
	OpCodes RDROpcodes = { RO_Nop, RO_Add, RO_Sub, RO_Mult, RO_Div, RO_Mod, RO_Not, RO_Neg, RO_CmpEq, RO_CmpNe, RO_CmpGt, RO_CmpGe, RO_CmpLt, RO_CmpLe, RO_fAdd, RO_fSub, RO_fMult, RO_fDiv, RO_fMod, RO_fNeg, RO_fCmpEq, RO_fCmpNe, RO_fCmpGt, RO_fCmpGe, RO_fCmpLt, RO_fCmpLe, RO_vAdd, RO_vSub, RO_vMult, RO_vDiv, RO_vNeg, RO_And, RO_Or, RO_Xor, RO_ItoF, RO_FtoI, RO_FtoV, RO_PushB, RO_PushB2, RO_PushB3, RO_Push, RO_PushF, RO_Dup, RO_Drop, RO_CallNative, RO_Function, RO_Return, RO_pGet, RO_pSet, RO_pPeekSet, RO_ToStack, RO_FromStack, RO_GetArrayP1, RO_GetArray1, RO_SetArray1, RO_GetFrameP1, RO_GetFrame1, RO_SetFrame1, RO_GetStaticP1, RO_GetStatic1, RO_SetStatic1, RO_Add1, RO_Mult1, RO_GetImm1, RO_SetImm1, RO_PushS, RO_Add2, RO_Mult2, RO_GetImm2, RO_SetImm2, RO_GetArrayP2, RO_GetArray2, RO_SetArray2, RO_GetFrameP2, RO_GetFrame2, RO_SetFrame2, RO_GetStaticP2, RO_GetStatic2, RO_SetStatic2, RO_GetGlobalP2, RO_GetGlobal2, RO_SetGlobal2, RO_Jump, RO_JumpFalse, RO_JumpNE, RO_JumpEQ, RO_JumpLE, RO_JumpLT, RO_JumpGE, RO_JumpGT, RO_Nop, RO_GetGlobalP3, RO_GetGlobal3, RO_SetGlobal3, RO_PushI24, RO_Switch, RO_PushString, RO_StrCopy, RO_ItoS, RO_StrAdd, RO_StrAddi, RO_MemCopy, RO_Catch, RO_Throw, RO_pCall, RO_Push_Neg1, RO_Push_0, RO_Push_1, RO_Push_2, RO_Push_3, RO_Push_4, RO_Push_5, RO_Push_6, RO_Push_7, RO_PushF_Neg1, RO_PushF_0, RO_PushF_1, RO_PushF_2, RO_PushF_3, RO_PushF_4, RO_PushF_5, RO_PushF_6, RO_PushF_7, RO_Nop, RO_Nop, RO_Nop, RO_Nop, RO_Call2, RO_Call2h1, RO_Call2h2, RO_Call2h3, RO_Call2h4, RO_Call2h5, RO_Call2h6, RO_Call2h7, RO_Call2h8, RO_Call2h9, RO_Call2hA, RO_Call2hB, RO_Call2hC, RO_Call2hD, RO_Call2hE, RO_Call2hF, RO_PushArrayP, RO_ReturnP0R0, RO_ReturnP0R1, RO_ReturnP0R2, RO_ReturnP0R3, RO_ReturnP1R0, RO_ReturnP1R1, RO_ReturnP1R2, RO_ReturnP1R3, RO_ReturnP2R0, RO_ReturnP2R1, RO_ReturnP2R2, RO_ReturnP2R3, RO_ReturnP3R0, RO_ReturnP3R1, RO_ReturnP3R2, RO_ReturnP3R3, RO_PushStringNull };
		
	CompileRDR(vector<FunctionData*> data) : CompileBase(RDROpcodes, data, 0, 0)
	{
	}

	void Call() override
	{
		AddOpcode(Push);
	}

};

class CompileGTAV : CompileBase
{
	OpCodes GTAVOpcodes = { VO_Nop, VO_Add, VO_Sub, VO_Mult, VO_Div, VO_Mod, VO_Not, VO_Neg, VO_CmpEq, VO_CmpNe, VO_CmpGt, VO_CmpGe, VO_CmpLt, VO_CmpLe, VO_fAdd, VO_fSub, VO_fMult, VO_fDiv, VO_fMod, VO_fNeg, VO_fCmpEq, VO_fCmpNe, VO_fCmpGt, VO_fCmpGe, VO_fCmpLt, VO_fCmpLe, VO_vAdd, VO_vSub, VO_vMult, VO_vDiv, VO_vNeg, VO_And, VO_Or, VO_Xor, VO_ItoF, VO_FtoI, VO_FtoV, VO_PushB, VO_PushB2, VO_PushB3, VO_Push, VO_PushF, VO_Dup, VO_Drop, VO_CallNative, VO_Function, VO_Return, VO_pGet, VO_pSet, VO_pPeekSet, VO_ToStack, VO_FromStack, VO_GetArrayP1, VO_GetArray1, VO_SetArray1, VO_GetFrameP1, VO_GetFrame1, VO_SetFrame1, VO_GetStaticP1, VO_GetStatic1, VO_SetStatic1, VO_Add1, VO_Mult1, VO_GetImm1, VO_SetImm1, VO_PushS, VO_Add2, VO_Mult2, VO_GetImm2, VO_SetImm2, VO_GetArrayP2, VO_GetArray2, VO_SetArray2, VO_GetFrameP2, VO_GetFrame2, VO_SetFrame2, VO_GetStaticP2, VO_GetStatic2, VO_SetStatic2, VO_GetGlobalP2, VO_GetGlobal2, VO_SetGlobal2, VO_Jump, VO_JumpFalse, VO_JumpNE, VO_JumpEQ, VO_JumpLE, VO_JumpLT, VO_JumpGE, VO_JumpGT, VO_Call, VO_GetGlobalp3, VO_GetGlobal3, VO_SetGlobal3, VO_PushI24, VO_Switch, VO_PushString, VO_StrCopy, VO_ItoS, VO_StrAdd, VO_StrAddi, VO_Memcopy, VO_Catch, VO_Throw, VO_pCall, VO_Push_Neg1, VO_Push_0, VO_Push_1, VO_Push_2, VO_Push_3, VO_Push_4, VO_Push_5, VO_Push_6, VO_Push_7, VO_PushF_Neg1, VO_PushF_0, VO_PushF_1, VO_PushF_2, VO_PushF_3, VO_PushF_4, VO_PushF_5, VO_PushF_6, VO_PushF_7, VO_GetImmP, VO_GetImmP1, VO_GetImmP2, VO_GetHash };


	CompileGTAV(vector<FunctionData*> data) : CompileBase(GTAVOpcodes, data, 0, 0)
	{
			
	}
};
