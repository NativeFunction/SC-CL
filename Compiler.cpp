#include "Compiler.h"

using namespace std;
using namespace Utils::System;
using namespace Utils::Bitwise;

#pragma region Base

#pragma region Parse_Functions
void CompileBase::fixFunctionJumps()
{
	/* 
	jump back is set on jump
	jump forward is set on label def


	for (auto jumpInfo : JumpLocations)
	{
		auto it = LabelLocations.find(jumpInfo.Label);
		if (it == LabelLocations.end())
		{
			
			Throw("Jump of type " + to_string((int)jumpInfo.InstructionType) + " to label \"" + jumpInfo.Label + "\" was not found");
		}
		switch (jumpInfo.InstructionType)
		{
			case JumpInstructionType::Jump:
			case JumpInstructionType::JumpFalse:
			case JumpInstructionType::JumpEQ:
			case JumpInstructionType::JumpNE:
			case JumpInstructionType::JumpGT:
			case JumpInstructionType::JumpGE:
			case JumpInstructionType::JumpLT:
			case JumpInstructionType::JumpLE:
			case JumpInstructionType::Switch:
			{
				int32_t offset = it->second - jumpInfo.JumpLocation - 2;
				if (offset < -32768 || offset > 32767)
				{
					Throw("Jump label \"" + jumpInfo.Label + "\" out of jump range");
				}
				*(int16_t*)(CodePageData.data() + jumpInfo.JumpLocation) = SwapEndian((int16_t)offset);
				break;
			}
			case JumpInstructionType::LabelLoc:
			{
				uint32_t pos = it->second;
				if ( pos >= 0x1000000)
				{
					Throw("Get label loc \"" + jumpInfo.Label + "\" out of jump range");
				}
			
				*(uint32_t*)(CodePageData.data() - 1 + jumpInfo.JumpLocation) = SwapEndian(pos) | BaseOpcodes->PushI24;
				break;
			}
		}
	}
	*/
	//JumpLocations.clear();
	LabelLocations.clear();
	
}
void CompileBase::ParseGeneral(const OpcodeKind OK)
{
	switch (OK)
	{
		case OK_Nop:		break;
		case OK_Add:		AddOpcode(Add); break;
		case OK_Sub:		AddOpcode(Sub); break;
		case OK_Mult:		AddOpcode(Mult); break;
		case OK_Div:		AddOpcode(Div); break;
		case OK_Mod:		AddOpcode(Mod); break;
		case OK_Not:		AddOpcode(Not); break;
		case OK_Neg:		AddOpcode(Neg); break;
		case OK_CmpEq:		AddOpcode(CmpEq); break;
		case OK_CmpNe:		AddOpcode(CmpNe); break;
		case OK_CmpGt:		AddOpcode(CmpGt); break;
		case OK_CmpGe:		AddOpcode(CmpGe); break;
		case OK_CmpLt:		AddOpcode(CmpLt); break;
		case OK_CmpLe:		AddOpcode(CmpLe); break;
		case OK_FAdd:		AddOpcode(fAdd); break;
		case OK_FSub:		AddOpcode(fSub); break;
		case OK_FMult:		AddOpcode(fMult); break;
		case OK_FDiv:		AddOpcode(fDiv); break;
		case OK_FMod:		AddOpcode(fMod); break;
		case OK_FNeg:		AddOpcode(fNeg); break;
		case OK_FCmpEq:		AddOpcode(fCmpEq); break;
		case OK_FCmpNe:		AddOpcode(fCmpNe); break;
		case OK_FCmpGt:		AddOpcode(fCmpGt); break;
		case OK_FCmpGe:		AddOpcode(fCmpGe); break;
		case OK_FCmpLt:		AddOpcode(fCmpLt); break;
		case OK_FCmpLe:		AddOpcode(fCmpLe); break;
		case OK_VAdd:		AddOpcode(vAdd); break;
		case OK_VSub:		AddOpcode(vSub); break;
		case OK_VMult:		AddOpcode(vMult); break;
		case OK_VDiv:		AddOpcode(vDiv); break;
		case OK_VNeg:		AddOpcode(vNeg); break;
		case OK_And:		AddOpcode(And); break;
		case OK_Or:			AddOpcode(Or); break;
		case OK_Xor:		AddOpcode(Xor); break;
		case OK_FtoI:		AddOpcode(FtoI); break;
		case OK_ItoF:		AddOpcode(ItoF); break;
		case OK_FtoV:		AddOpcode(FtoV); break;
		case OK_PushInt:	PushInt(); break;//gta4 needs to override
		case OK_PushBytes:	PushBytes(); break;//gta4 needs to override
		case OK_PushFloat:	PushFloat(); break;//gta4 needs to override
		case OK_Dup:		AddOpcode(Dup); break;
		case OK_Drop:		AddOpcode(Drop); break;
		case OK_Native:		CallNative(); break;//callnative def| gta5 1 byte param/return, 2 byte call loc | rdr 2 byte call loc | gta4: 1 byte param, 1 byte return, 4 byte hash
		case OK_Return:		Return(); break;//rdr needs to override
		case OK_PGet:		AddOpcode(pGet); break;
		case OK_PSet:		AddOpcode(pSet); break;
		case OK_PeekSet:	AddOpcode(pPeekSet); break;
		case OK_ToStack:	AddOpcode(ToStack); break;
		case OK_FromStack:	AddOpcode(FromStack); break;

		case OK_GetArrayP:	GetArrayP(); break;
		case OK_GetArray:	GetArray(); break;
		case OK_SetArray:	SetArray(); break;
		case OK_GetFrameP:	GetFrameP(); break;
		case OK_GetFrame:	GetFrame(); break;
		case OK_SetFrame:	SetFrame(); break;
		case OK_GetStaticP:	GetStaticP(); break;
		case OK_GetStatic:	GetStatic(); break;
		case OK_SetStatic:	SetStatic(); break;
		case OK_GetGlobalP:	GetGlobalP(); break;
		case OK_GetGlobal:	GetGlobal(); break;
		case OK_SetGlobal:	SetGlobal(); break;
		case OK_AddImm:		AddImm(); break;
		case OK_MultImm:	MultImm(); break;
		case OK_FAddImm:	FAddImm(); break;
		case OK_FMultImm:	FMultImm(); break;
		case OK_GetImmP:	GetImmP(); break;
		case OK_GetImm:		GetImm(); break;
		case OK_SetImm:		SetImm(); break;


		case OK_Call:		Call();  break;//call def| gta4: 4 byte loc | gta5: 3 byte loc | rdr: 2 byte loc (loc or'ed)
		case OK_Jump:		AddJump(JumpInstructionType::Jump, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpFalse:	AddJump(JumpInstructionType::JumpFalse, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpEQ:		AddJump(JumpInstructionType::JumpEQ, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpNE:		AddJump(JumpInstructionType::JumpNE, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpGT:		AddJump(JumpInstructionType::JumpGT, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpGE:		AddJump(JumpInstructionType::JumpGE, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpLT:		AddJump(JumpInstructionType::JumpLT, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpLE:		AddJump(JumpInstructionType::JumpLE, DATA->getString()); break;//gta 4 needs to override
		case OK_Switch:		Switch(); break;
		case OK_PushString:	PushString(); break;//gta5 needs to override
		case OK_StrCopy:	StrCopy(); break;//gta4 needs to override
		case OK_ItoS:		ItoS(); break;//gta4 needs to override
		case OK_StrAdd:		StrAdd(); break;//gta4 needs to override
		case OK_StrAddI:	StrAddI(); break;//gta4 needs to override
		case OK_MemCpy:		AddOpcode(MemCopy); break;
		case OK_PCall:		pCall(); break;//gta4 needs to override as error
		case OK_Label:		AddLabel(DATA->getString()); break;
		case OK_LabelLoc:	AddJump(JumpInstructionType::LabelLoc, DATA->getString()); break;
		case OK_FuncLoc:	AddFuncLoc(DATA->getString()); break;
		case OK_ShiftLeft:	CallNative(JoaatConst("shift_left"), 2, 1); break;
		case OK_ShiftRight:	CallNative(JoaatConst("shift_right"), 2, 1); break;
		case OK_GetHash:	GetHash(); break;//gta5 needs to override
	}
	CheckJumps();
}
void CompileBase::BuildTables()
{
	for (FunctionCount = 0; FunctionCount < HLData->getFunctionCount(); FunctionCount++)
	{
		if (HLData->getFunctionFromIndex(FunctionCount)->IsUsed())
		{
			AddFunction(HLData->getFunctionFromIndex(FunctionCount)->getName().substr(1), HLData->getFunctionFromIndex(FunctionCount)->getParamCount(), HLData->getFunctionFromIndex(FunctionCount)->getStackSize());
			for (InstructionCount = 0; InstructionCount < HLData->getFunctionFromIndex(FunctionCount)->getInstructionCount(); InstructionCount++)
			{
				ParseGeneral(HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)->getKind());
			}
			fixFunctionJumps();
		}
	}
	fixFunctionCalls();
}
#pragma endregion

#pragma region Data_Functions
void CompileBase::AddLabel(const string label)
{
	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end())
	{
		LabelLocations.insert({ label,{ CodePageData.size(), true } });
	}
	else if (!it->second.isSet)
	{
		it->second.isSet = true;
		it->second.LabelLocation = CodePageData.size();
		for (uint32_t i = 0; i < it->second.JumpIndexes.size(); i++)
		{
			//Fix jump forwards that are in range. Out of range jumps should have already been fixed.

			if (!JumpLocations[it->second.JumpIndexes[i]].isSet)
			{
				if (JumpLocations[it->second.JumpIndexes[i]].InstructionType != JumpInstructionType::LabelLoc)
				{
					const int32_t offset = it->second.LabelLocation - JumpLocations[it->second.JumpIndexes[i]].JumpLocation - 2;

					if (offset < -32768 || offset > 32767)
						Utils::System::Throw("Jump label \"" + label + "\" out of jump range");

					*(int16_t*)(CodePageData.data() + JumpLocations[it->second.JumpIndexes[i]].JumpLocation) = SwapEndian((int16_t)offset);
					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
				else
				{
					if (it->second.LabelLocation >= 0x1000000)
						Utils::System::Throw("Get label loc \"" + label + "\" out of jump range");

					*(uint32_t*)(CodePageData.data() - 1 + JumpLocations[it->second.JumpIndexes[i]].JumpLocation) = SwapEndian(it->second.LabelLocation) | BaseOpcodes->PushI24;
					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
			}
		}
	}
	else
		Utils::System::Throw("Cannot add label. Label \"" + label + "\" already exists.");
}
void CompileBase::AddJump(const JumpInstructionType type, const string label)
{
	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end() || !it->second.isSet)
	{
		//jump forward
		switch (type)
		{
			case JumpInstructionType::Jump:			DoesOpcodeHaveRoom(3); AddOpcode(Jump); AddJumpLoc(type, label); return;
			case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(3); AddOpcode(JumpFalse); AddJumpLoc(type, label); return;
			case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpNE); AddJumpLoc(type, label); return;
			case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(3); AddOpcode(JumpEQ); AddJumpLoc(type, label); return;
			case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLE); AddJumpLoc(type, label); return;
			case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLT); AddJumpLoc(type, label); return;
			case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGE); AddJumpLoc(type, label); return;
			case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGT); AddJumpLoc(type, label); return;
			case JumpInstructionType::Switch:		AddJumpLoc(type, label); return;
			case JumpInstructionType::LabelLoc:	DoesOpcodeHaveRoom(4); AddOpcode(PushI24); AddJumpLoc(type, label); return;
			default: assert(false && "Invalid JumpInstructionType"); return;
		}
	}
	else
	{
		//jump backward
		int32_t offset = it->second.LabelLocation - BuildBuffer.size() - 3;
		if (offset >= -32768 || offset <= 32767)
		{
			switch (type)
			{
				case JumpInstructionType::Jump:			DoesOpcodeHaveRoom(3); AddOpcode(Jump); AddInt16(offset); return;
				case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(3); AddOpcode(JumpFalse); AddInt16(offset); return;
				case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpNE); AddInt16(offset); return;
				case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(3); AddOpcode(JumpEQ); AddInt16(offset); return;
				case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLE); AddInt16(offset); return;
				case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLT); AddInt16(offset); return;
				case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGE); AddInt16(offset); return;
				case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGT); AddInt16(offset); return;
				case JumpInstructionType::Switch:		AddInt16(it->second.LabelLocation - BuildBuffer.size() - 2); return;
				case JumpInstructionType::LabelLoc:	PushInt(it->second.LabelLocation); return;
				default: assert(false && "Invalid JumpInstructionType"); return;
			}
		}
		else
		{
			Throw("unimplemented long jump func call");
			//long jump func call
		}
		
	}
	
}
void CompileBase::CheckJumps()
{
	if (!UpdateJumpLocationsToFar())
		return;

	int32_t offset = (CodePageData.size() + 3) - JumpLocations[JumpLocationsToFarInc].JumpLocation - 2;
	if (offset > 30000)//to make this easier im going on the assumption that the max size of an opcode is 1532 (nothing can be added that is 2767)
	{
		//jump to jump code

		DoesOpcodeHaveRoom(3);
		AddOpcode(Jump);
		uint32_t JumpOverOffset = CodePageData.size();
		AddInt16(0);

		//need to update jumps of same label that are out of bounds to jumps that are already added. instead of adding another jump to jump.

		offset = CodePageData.size() - JumpLocations[JumpLocationsToFarInc].JumpLocation - 2;

		do
		{
			if (offset > 32767)
				Throw("Jump label \"" + JumpLocations[JumpLocationsToFarInc].Label + "\" out of jump range on jump to jump " + to_string(offset));

			*(int16_t*)(CodePageData.data() + JumpLocations[JumpLocationsToFarInc].JumpLocation) = SwapEndian((int16_t)offset);
			JumpLocations[JumpLocationsToFarInc].isSet = true;
			cout << "fixed label " + JumpLocations[JumpLocationsToFarInc].Label << " at index " << JumpLocationsToFarInc << endl;

			DoesOpcodeHaveRoom(3);
			AddOpcode(Jump);
			AddJumpLoc(JumpInstructionType::Jump, JumpLocations[JumpLocationsToFarInc].Label);

			if (!UpdateJumpLocationsToFar())
				return;

			offset = CodePageData.size() - JumpLocations[JumpLocationsToFarInc].JumpLocation - 2;
		} while (offset > 30000);


		//set jump over jump
		*(int16_t*)(CodePageData.data() + JumpOverOffset) = SwapEndian((int16_t)(CodePageData.size() - JumpOverOffset - 2));
	}

}
#pragma endregion

#pragma region Opcode_Functions
void CompileBase::PushInt(const int32_t Literal)
{
	if (Literal >= -1 && Literal <= 7) {
		switch (Literal)
		{
			case -1:AddOpcode(Push_Neg1); break;
			case 0: AddOpcode(Push_0); break;
			case 1: AddOpcode(Push_1); break;
			case 2: AddOpcode(Push_2); break;
			case 3: AddOpcode(Push_3); break;
			case 4: AddOpcode(Push_4); break;
			case 5: AddOpcode(Push_5); break;
			case 6: AddOpcode(Push_6); break;
			case 7: AddOpcode(Push_7); break;
			default: assert(false && "Invalid Push Opcode");
		}
	}
	else if (Literal > 0 && Literal < 256)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(PushB);
		AddInt8(Literal);
	}
	else if (Literal >= -32768 && Literal <= 32767)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(PushS);
		AddInt16(Literal);
	}
	else if (Literal > 0 && Literal < 16777216)
	{
		DoesOpcodeHaveRoom(4);
		AddOpcode(PushI24);
		AddInt24(Literal);
	}
	else
	{
		DoesOpcodeHaveRoom(5);
		AddOpcode(Push);
		AddInt32(Literal);
	}


}
void CompileBase::PushFloat(const float Literal)
{
	switch (Utils::DataConversion::FloatToInt(Literal))
	{
		case 0xbf800000: AddOpcode(PushF_Neg1); break;
		case 0x80000000://neg 0
		case 0x00000000: AddOpcode(PushF_0); break;
		case 0x3f800000: AddOpcode(PushF_1); break;
		case 0x40000000: AddOpcode(PushF_2); break;
		case 0x40400000: AddOpcode(PushF_3); break;
		case 0x40800000: AddOpcode(PushF_4); break;
		case 0x40A00000: AddOpcode(PushF_5); break;
		case 0x40C00000: AddOpcode(PushF_6); break;
		case 0x40E00000: AddOpcode(PushF_7); break;
		default: DoesOpcodeHaveRoom(5); AddOpcode(PushF); AddFloat(Literal);
	}
}
void CompileBase::PushBytes()
{
	switch (DATA->getByte(0))
	{
		case 0: assert(false && "Empty PushBytes opcode"); break;
		case 1: DoesOpcodeHaveRoom(2); AddOpcode(PushB); AddInt8(DATA->getByte(1)); break;
		case 2: DoesOpcodeHaveRoom(3); AddOpcode(PushB2); AddInt8(DATA->getByte(1)); AddInt8(DATA->getByte(2)); break;
		case 3: DoesOpcodeHaveRoom(4); AddOpcode(PushB3); AddInt8(DATA->getByte(1)); AddInt8(DATA->getByte(2)); AddInt8(DATA->getByte(3)); break;
		default:
			assert(false && "Too many bytes in PushBytes opcode");
	}
}

#pragma region AddOpcodeB_1or2
#define AddOpcodeB_1or2(op, errorstr)\
const uint32_t value = DATA->getInt();\
if (value <= 0xFF)\
{\
	DoesOpcodeHaveRoom(2);\
	AddInt8(BaseOpcodes->##op##1);\
	AddInt8(value);\
}\
else if (value <= 0xFFFF)\
{\
	DoesOpcodeHaveRoom(3);\
	AddInt8(BaseOpcodes->##op##2);\
	AddInt16(value);\
}\
else{\
assert(false && errorstr);\
}
#pragma endregion
#pragma region AddOpcodeB_2or3
#define AddOpcodeB_2or3(op, errorstr)\
const uint32_t value = DATA->getInt();\
if (value <= 0xFFFF)\
{\
	DoesOpcodeHaveRoom(3);\
	AddInt8(BaseOpcodes->##op##2);\
	AddInt8(value);\
}\
else if (value <= 0xFFFFFF)\
{\
	DoesOpcodeHaveRoom(4);\
	AddInt8(BaseOpcodes->##op##3);\
	AddInt16(value);\
}\
else{\
assert(false && errorstr);\
}
#pragma endregion

void CompileBase::GetArrayP()
{
	AddOpcodeB_1or2(GetArrayP, "GetArrayP index too high");
}
void CompileBase::GetArray()
{
	AddOpcodeB_1or2(GetArray, "GetArray index too high");
}
void CompileBase::SetArray()
{
	AddOpcodeB_1or2(SetArray, "SetArray index too high");
}
void CompileBase::GetFrameP()
{
	AddOpcodeB_1or2(GetFrameP, "GetFrameP index too high");
}
void CompileBase::GetFrame()
{
	AddOpcodeB_1or2(GetFrame, "GetFrame index too high");
}
void CompileBase::SetFrame()
{
	AddOpcodeB_1or2(SetFrame, "SetFrame index too high");
}
void CompileBase::GetStaticP()
{
	AddOpcodeB_1or2(GetStaticP, "GetStaticP index too high");
}
void CompileBase::GetStatic()
{
	AddOpcodeB_1or2(GetStatic, "GetStatic index too high");
}
void CompileBase::SetStatic()
{
	AddOpcodeB_1or2(SetStatic, "SetStatic index too high");
}
void CompileBase::GetGlobalP()
{
	AddOpcodeB_2or3(GetGlobalP, "GetGlobalP index too high");
}
void CompileBase::GetGlobal()
{
	AddOpcodeB_2or3(GetGlobal, "GetGlobal index too high");
}
void CompileBase::SetGlobal()
{
	AddOpcodeB_2or3(SetGlobal, "SetGlobal index too high");
}


void CompileBase::PushString()
{
	DoesOpcodeHaveRoom(DATA->getString().size() + 3);//opcode, len, null terminator
	AddOpcode(PushString);
	AddInt8(DATA->getString().size() + 1);//str size + null terminator
	AddString(DATA->getString());
}
void CompileBase::AddFuncLoc(const string funcName)
{
	DoesOpcodeHaveRoom(4);
	AddOpcode(PushI24);
	CallLocations.push_back({ CodePageData.size(), CallInstructionType::FuncLoc, funcName });
	AddInt24(0);
}
void CompileBase::Switch(){

	const SwitchStorage* switchStore = DATA->getSwitch();
	const uint32_t caseCount = switchStore->getCount();
	DoesOpcodeHaveRoom(caseCount * 6 + 2);//opcode, case count

	AddOpcode(Switch);
	AddInt8(caseCount);

	if (caseCount)
	{
		const SwitchCaseStorage* sCase = switchStore->getFirstCase();
		AddInt32(sCase->getCaseValue());
		AddJump(JumpInstructionType::Switch, sCase->getCaseLocation());
		while (sCase->hasNextCase())
		{
			sCase = sCase->getNextCase();
			AddInt32(sCase->getCaseValue());
			AddJump(JumpInstructionType::Switch, sCase->getCaseLocation());
		}
	}
	
}
void CompileBase::AddImm(const int32_t Literal)
{
	if (Literal > 0 && Literal < 256)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(Add1);
		AddInt8(Literal);
	}
	else if (Literal >= -32768 && Literal < 32768)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(Add2);
		AddInt16(Literal);
	}
	else if (Literal > 0 && Literal < 0x1000000)
	{
		DoesOpcodeHaveRoom(4);
		AddOpcode(PushI24);
		AddInt24(Literal);
		AddOpcode(Add);
	}
	else
	{
		DoesOpcodeHaveRoom(5);
		AddOpcode(Push);
		AddInt32(Literal);
		AddOpcode(Add);
	}

}
void CompileBase::MultImm(const int32_t Literal)
{
	if (Literal > 0 && Literal < 256)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(Mult1);
		AddInt8(Literal);
	}
	else if (Literal >= -32768 && Literal < 32768)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(Mult2);
		AddInt16(Literal);
	}
	else if (Literal > 0 && Literal < 0x1000000)
	{
		DoesOpcodeHaveRoom(4);
		AddOpcode(PushI24);
		AddInt24(Literal);
		AddOpcode(Mult);
	}
	else
	{
		DoesOpcodeHaveRoom(5);
		AddOpcode(Push);
		AddInt32(Literal);
		AddOpcode(Mult);
	}

}
void CompileBase::FAddImm()
{
	switch(DATA->getInt())
	{
		case 0xc0e00000: AddOpcode(PushF_7); AddOpcode(fSub); break;
		case 0xc0c00000: AddOpcode(PushF_6); AddOpcode(fSub); break;
		case 0xc0a00000: AddOpcode(PushF_5); AddOpcode(fSub); break;
		case 0xc0800000: AddOpcode(PushF_4); AddOpcode(fSub); break;
		case 0xc0400000: AddOpcode(PushF_3); AddOpcode(fSub); break;
		case 0xc0000000: AddOpcode(PushF_2); AddOpcode(fSub); break;
		case 0xbf800000: AddOpcode(PushF_1); AddOpcode(fSub); break;
		case 0x80000000: //neg 0
		case 0x00000000: break;
		case 0x3f800000: AddOpcode(PushF_1); AddOpcode(fAdd); break;
		case 0x40000000: AddOpcode(PushF_2); AddOpcode(fAdd); break;
		case 0x40400000: AddOpcode(PushF_3); AddOpcode(fAdd); break;
		case 0x40800000: AddOpcode(PushF_4); AddOpcode(fAdd); break;
		case 0x40A00000: AddOpcode(PushF_5); AddOpcode(fAdd); break;
		case 0x40C00000: AddOpcode(PushF_6); AddOpcode(fAdd); break;
		case 0x40E00000: AddOpcode(PushF_7); AddOpcode(fAdd); break;
	default: DoesOpcodeHaveRoom(5); AddOpcode(PushF); AddFloat(DATA->getFloat()); AddOpcode(fAdd); break;
	}
	
}
void CompileBase::FMultImm()
{
	PushFloat();
	AddOpcode(fMult);
}
#pragma endregion

#pragma region Write_Functions
void CompileBase::WriteCodePagesNoPadding()
{
	for (uint32_t i = 0; i < CodePageCount - 1; i++)
	{	
		SavedOffsets.CodePagePointers[i] = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + 16384);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - 16384, CodePageData.data() + i * 16384, 16384);
	}
	const uint32_t LastCodePageSize = CodePageData.size() % 16384;
	SavedOffsets.CodePagePointers[CodePageCount - 1] = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + LastCodePageSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - LastCodePageSize, CodePageData.data() + CodePageData.size() - LastCodePageSize, LastCodePageSize);
};
void CompileBase::Write16384CodePages()
{
	SavedOffsets.CodePagePointers.resize(CodePageCount);
	for (uint32_t i = 0; i < CodePageCount - 1; i++)
	{

		if (GetSpaceLeft(16384) < 16384)
			FillPageNops();

		SavedOffsets.CodePagePointers[i] = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + 16384);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - 16384, CodePageData.data() + i * 16384, 16384);

		PadNops();
	}
}
void CompileBase::WriteFinalCodePage()
{
	const uint32_t LastCodePageSize = CodePageData.size() % 16384;
	SavedOffsets.CodePagePointers[CodePageCount - 1] = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + LastCodePageSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - LastCodePageSize, CodePageData.data() + CodePageData.size() - LastCodePageSize, LastCodePageSize);
	Pad();
}
void CompileBase::WriteNativesNoPadding()
{
	const size_t nativeByteSize = NativeHashMap.size() * 4;
	SavedOffsets.Natives = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + nativeByteSize);
	for (unordered_map<uint32_t, uint32_t>::iterator it = NativeHashMap.begin(); it != NativeHashMap.end(); it++)
	{
		*(uint32_t*)(BuildBuffer.data() + SavedOffsets.Natives + it->second * 4) = Utils::Bitwise::SwapEndian(it->first);
	}
}
void CompileBase::WriteNatives()
{
	if (NativeHashMap.size() > 0)
	{
		const size_t nativeByteSize = NativeHashMap.size() * 4;

		if (GetSpaceLeft(16384) < nativeByteSize)
			FillPageDynamic(16384);

		SavedOffsets.Natives = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + nativeByteSize);
		for (unordered_map<uint32_t, uint32_t>::iterator it = NativeHashMap.begin(); it != NativeHashMap.end(); it++)
		{
			*(uint32_t*)(BuildBuffer.data() + SavedOffsets.Natives + it->second * 4) = Utils::Bitwise::SwapEndian(it->first);
		}

		Pad();
	}
	else
	{
		if (GetSpaceLeft(16384) < 16)
			FillPageDynamic(16384);
		SavedOffsets.Natives = BuildBuffer.size();
		ForcePad();
	}

}
void CompileBase::WriteStaticsNoPadding()
{
	const size_t staticByteSize = HLData->getStaticSize() * 4;

	SavedOffsets.Statics = BuildBuffer.size();

	BuildBuffer.resize(BuildBuffer.size() + staticByteSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - staticByteSize, HLData->getStaticData(), staticByteSize);
}
void CompileBase::WriteStatics()
{

	if (HLData->getStaticSize() > 0)
	{
		const size_t staticByteSize = HLData->getStaticSize() * 4;

		if (GetSpaceLeft(16384) < staticByteSize)
			FillPageDynamic(16384);

		SavedOffsets.Statics = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + staticByteSize);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - staticByteSize, HLData->getStaticData(), staticByteSize);

		Pad();

	}
	else
	{
		if (GetSpaceLeft(16384) < 16)
			FillPageDynamic(16384);
		SavedOffsets.Statics = BuildBuffer.size();
		ForcePad();

	}

}
#pragma endregion

#pragma endregion

#pragma region RDR

#pragma region Parse_Functions
void CompileRDR::fixFunctionCalls()
{
	for (auto CallInfo : CallLocations)
	{
		auto it = FuncLocations.find(CallInfo.FuncName);
		if (it == FuncLocations.end())
		{
			Throw("Function \"" + CallInfo.FuncName + "\" not found");
		}
		uint32_t pos = it->second;
		if (pos >= 0x1000000)
			Throw("Function \"" + CallInfo.FuncName + "\" out of call range");
		
		switch (CallInfo.InstructionType)
		{
			case CallInstructionType::FuncLoc:
				*(int32_t*)(CodePageData.data() - 1 + CallInfo.CallLocation) = SwapEndian(pos) | BaseOpcodes->PushI24;
			break;
			case CallInstructionType::Call:
				if (pos > 1048575)
				{
					*(int32_t*)(CodePageData.data() + CallInfo.CallLocation) = SwapEndian(pos) | BaseOpcodes->PushI24;
					*(CodePageData.data() + CallInfo.CallLocation + 4) = RDROpcodes.pCall;
				}
				else
				{
					*(CodePageData.data() + CallInfo.CallLocation) = GetNewCallOpCode(pos);//any out of range errors already been caught
					*(uint16_t*)(CodePageData.data() + CallInfo.CallLocation + 1) = SwapEndian(GetNewCallOffset((uint16_t)pos));
				}
			break;
			default: assert(false && "Invalid Call Instruction"); break;
		}
	}
}
#pragma endregion

#pragma region RSC85Parsing
uint32_t CompileRDR::GetHeaderFormatFromFlag(uint32_t val)
{
	uint8_t flags = val >> 24;
	switch (flags)
	{
		///header is at a multiple of 4096 (in rockstar scripts that is always the last 4096)
		case (int)Rsc85Flags::F4096:
		return 4096;
		///header is at a multiple of 65536 (in rockstar scripts that is always 0 because any other 65536 would yield the same result)
		case (int)Rsc85Flags::F65536:
		return 0;
		///header is at a multiple of 16384 (in rockstar scripts that is always the last 16384)
		case (int)Rsc85Flags::F16384:
		return 16384;
		///header is at a multiple of 8192 (in rockstar scripts that is always the last 8192)
		case (int)Rsc85Flags::F8192:
		return 8192;
	}
	return 0xFFFFFFFF;
}
uint32_t CompileRDR::GetFlagFromReadbuffer(uint32_t buffer)
{
	switch (buffer)
	{
		case 4096:
		return (int)Rsc85Flags::Fi4096;
		case 65536:
		return (int)Rsc85Flags::Fi65536;
		case 16384:
		return (int)Rsc85Flags::Fi16384;
		case 8192:
		return (int)Rsc85Flags::Fi8192;

	}
	return 0xFFFFFFFF;
}
#pragma endregion

#pragma region Opcode_Functions
void CompileRDR::CallNative(const uint32_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	// rdr 2 byte call loc based on index
	DoesOpcodeHaveRoom(3);

	AddOpcode(CallNative);
	if (hash == -1)
	{
		if(DATA->getNative()->getReturnCount() > 1)
			Throw("Native Calls Can Only Have One Return");

		const uint32_t index = AddNative(DATA->getNative()->getHash());
		if (index >= 1024)
			Throw("Native Call Index out of bounds");

		AddInt16(SetNewIndex(index, DATA->getNative()->getParamCount(), DATA->getNative()->getReturnCount() == 1));
	}
	else
	{
		if (returnCount > 1)
			Throw("Native Calls Can Only Have One Return");

		const uint32_t index = AddNative(hash);
		if (index >= 1024)
			Throw("Native Call Index out of bounds");

		AddInt16(SetNewIndex(index, paramCount, returnCount == 1));
	}
}
void CompileRDR::Return()
{
	const uint8_t popParams = DATA->getByte(0);
	const uint8_t returns = DATA->getByte(1);

	if (popParams <= 3 && returns <= 3)
		AddInt8(RDROpcodes.ReturnP0R0 + (popParams * 4) + returns);
	else
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(Return);
		AddInt8(popParams);
		AddInt8(returns);
	}
}
void CompileRDR::Call()
{
	// rdr: 2 byte loc (loc or'ed)
	auto it = FuncLocations.find(DATA->getString());
	if (it == FuncLocations.end())
	{
		DoesOpcodeHaveRoom(4);//4 because pcall can be separate
		CallLocations.push_back({ CodePageData.size(), CallInstructionType::Call, DATA->getString() });
		AddInt24(0);//call, int16 loc / pushi24, int16 loc part
		AddInt16(0);//int16 loc part 2, pcall
	}
	else
	{
		if (it->second > 1048575)
		{
			PushInt(it->second);
			AddOpcode(pCall);
		}
		else
		{
			DoesOpcodeHaveRoom(3);
			AddInt8(GetNewCallOpCode(it->second));
			AddInt16(SwapEndian(GetNewCallOffset((uint16_t)it->second)));
		}
	}

	
}
void CompileRDR::GetImm()
{
	const uint32_t value = (uint32_t)DATA->getUShort(0) * 4;
	if (value <= 0xFF)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(GetImm1);
		AddInt8(value);
	}
	else if(value <= 0xFFFF)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(GetImm2);
		AddInt16(value);
	}
	else
	{
		AddImm(value);
		AddOpcode(pGet);
	}
}
void CompileRDR::SetImm()
{
	const uint32_t value = (uint32_t)DATA->getUShort(0) * 4;
	if (value <= 0xFF)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(SetImm1);
		AddInt8(value);
	}
	else if (value <= 0xFFFF)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(SetImm2);
		AddInt16(value);
	}
	else
	{
		AddImm(value);
		AddOpcode(pSet);
	}
}
#pragma endregion

#pragma region Write_Functions
void CompileRDR::WriteHeader()
{
	headerLocation = BuildBuffer.size();
	AddInt32toBuff(0xA8D74300);//Page Base
	AddInt32toBuff(0); //Unk1 ptr
	AddInt32toBuff(0); //codeBlocksListOffsetPtr
	AddInt32toBuff(CodePageData.size());//code length
	AddInt32toBuff(0);//script ParameterCount (this needs to be implemented)
	AddInt32toBuff(HLData->getStaticSize());//statics count
	AddInt32toBuff(0); //Statics offset
	AddInt32toBuff(0x349D018A);//GlobalsSignature
	AddInt32toBuff(NativeHashMap.size());//natives count
	AddInt32toBuff(0); //natives offset
	Pad();
}
void CompileRDR::WritePointers()
{
	//write unk1

	if (GetSpaceLeft(16384) < 4)
		FillPageDynamic(16384);

	SavedOffsets.Unk1 = BuildBuffer.size();
	AddInt32toBuff(0);//unkPTRData
	Pad();

	uint64_t padcount = Utils::Math::CeilDivInt(CodePageCount * 4, 16);
	for (uint64_t i = 0; i < padcount; i++)
		ForcePad();

	//Write code page pointers
	if (GetSpaceLeft(16384) < CodePageCount * 4)
		FillPageDynamic(16384);

	SavedOffsets.CodeBlocks = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + CodePageCount * 4, 0);


	Pad();
}
bool CompileRDR::WriteNormal(uint32_t datasize, uint32_t bufferflag)
{
	if (datasize < bufferflag)
	{
		headerFlag = GetFlagFromReadbuffer(bufferflag);
		if (headerFlag == 0xFFFFFFFF)
			Throw("Invalid Read Buffer");
		Write16384CodePages();
		WriteFinalCodePage();
		FillPageDynamic(bufferflag);
		WriteHeader();
		WriteNatives();
		WriteStatics();
		WritePointers();
		FillPageDynamic(bufferflag);
		return true;
	}
	return false;
}
bool CompileRDR::WriteSmall(uint32_t datasize, uint32_t bufferflag)
{
	if (datasize < bufferflag)
	{
		headerFlag = GetFlagFromReadbuffer(bufferflag);
		if (headerFlag == 0xFFFFFFFF)
			Throw("Invalid Read Buffer");
		Write16384CodePages();
		WriteHeader();
		WriteFinalCodePage();
		WriteNatives();
		WriteStatics();
		WritePointers();
		FillPageDynamic(bufferflag);
		return true;
	}
	return false;
};
void CompileRDR::XSCWrite(const char* path, bool CompressAndEncrypt)
{
	FilePadding = 0xCD;
	ClearWriteVars();
	CodePageCount = Utils::Math::CeilDivInt(CodePageData.size(), 16384);

	#pragma region Write_Pages_and_header

	const uint32_t CodePagePtrsSize = CodePageCount * 4;

	uint32_t TotalData = GetPadExpectedAmount(NativeHashMap.size() * 4) +
		GetPadExpectedAmount(HLData->getStaticSize() * 4) +
		GetPadExpectedAmount(16 + CodePagePtrsSize) + //unk1 4 but set as 16 (padded) to avoid miscalculating the pad size
		GetPadExpectedAmount(40) + //header
		GetPadExpectedAmount(CodePagePtrsSize);//code page pointers

	uint32_t LastCodePageSize = GetPadExpectedAmount(CodePageData.size() % 16384);//code page pointers * padding for unk1

	//cout << "Natives: " << GetPadExpectedAmount(NativeHashMap.size() * 4) << '\n';
	//cout << "Statics: " << GetPadExpectedAmount(HLData->getStaticSize() * 4) << '\n';
	//cout << "Unk1: " << GetPadExpectedAmount(16 + CodePagePtrsSize) << '\n';
	//cout << "Header: " << GetPadExpectedAmount(40) << '\n';
	//cout << "Codepage Ptrs: " << GetPadExpectedAmount(CodePagePtrsSize) << '\n';
	//cout << "Last Codepage: " << GetPadExpectedAmount(LastCodePageSize) << '\n';
	//cout << "Total: "  << LastCodePageSize + TotalData << "\n";
	//if(LastCodePageSize +  TotalData > 16384) then write normal but maybe place somethings under last code page if possible
	//else include last code page in header

	if (LastCodePageSize + TotalData > 16384)
	{
		if (WriteNormal(TotalData, 4096));
		else if (WriteNormal(TotalData, 8192));
		else if (WriteNormal(TotalData, 16384));
		else
		{
			headerFlag = (int)Rsc85Flags::Fi65536;
			WriteHeader();
			WriteNatives();
			WriteStatics();
			WritePointers();
			FillPageDynamic(65536);
			Write16384CodePages();
			WriteFinalCodePage();
			FillPageDynamic(65536);
		}

	}
	else
	{
		TotalData += LastCodePageSize;
		if (WriteSmall(TotalData, 4096));
		else if (WriteSmall(TotalData, 8192));
		else if (WriteSmall(TotalData, 16384));
		else
			Throw("Total Data is Less Then and Greater Then 16384. Impossible.");
	}

	#pragma endregion

	#pragma region Fix_header_and_other_pointers
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.Unk1), headerLocation + 4);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.CodeBlocks), headerLocation + 8);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.Statics), headerLocation + 24);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.Natives), headerLocation + 36);

	for (uint32_t i = 0; i < SavedOffsets.CodePagePointers.size(); i++)
		ChangeInt32inBuff(IntToPointerInt(SavedOffsets.CodePagePointers[i]), SavedOffsets.CodeBlocks + (i * 4));
	#pragma endregion

	#pragma region Write_File
	if (CompressAndEncrypt)
	{

		// compressing and encrypting

		Utils::Compression::xCompress Compression;
		Compression.xCompressInit();

		vector<uint8_t> Compressed(BuildBuffer.size() + 8);
		uint8_t* CompressedData = Compressed.data();
		int32_t CompressedLen = 0;

		Compression.Compress((uint8_t*)BuildBuffer.data(), BuildBuffer.size(), CompressedData + 8, &CompressedLen);

		if (CompressedLen > 0)
		{
			*(uint32_t*)CompressedData = SwapEndian(0x0FF512F1);//LZX Signature?
			*(uint32_t*)(CompressedData + 4) = SwapEndian(CompressedLen);
			CompressedLen += 8;
		}
		else Throw("Compression Failed");

		if (!Utils::Crypt::AES_Encrypt(CompressedData, CompressedLen))
			Throw("Encryption Failed");


		vector<uint32_t> CSR_Header(4);
		CSR_Header[0] = SwapEndian(0x85435352);//.CSR
		CSR_Header[1] = SwapEndian(0x00000002);//Resource Type Script
		CSR_Header[2] = SwapEndian(0x80000000);//unk int max val (flags1)
		CSR_Header[3] = SwapEndian(GetFullFlagWithSize(BuildBuffer.size(), headerFlag));//size (flags2)

		FILE* file = fopen(path, "wb");
		if (file != NULL)
		{
			fwrite(CSR_Header.data(), 1, 16, file);//encrypted data
			fwrite(CompressedData, 1, CompressedLen, file);//encrypted data
			fclose(file);
		}
		else
			Throw("Could Not Open Output File");

	}
	else
	{
		FILE* file = fopen(path, "wb");

		if (file != NULL)
		{
			fwrite(BuildBuffer.data(), 1, BuildBuffer.size(), file);
			fclose(file);
		}
		else
			Throw("Could Not Open Output File");
	}

	#pragma endregion

}
void CompileRDR::SCOWrite(const char* path, bool CompressAndEncrypt)
{
	FilePadding = 0xCD;
	ClearWriteVars();
	CodePageCount = Utils::Math::CeilDivInt(CodePageData.size(), 16384);

	WriteCodePagesNoPadding();
	WriteNativesNoPadding();
	WriteStaticsNoPadding();

	#pragma region Write_File
	if (CompressAndEncrypt)
	{

		uint32_t CompressedSize = BuildBuffer.size();

		vector<uint8_t> CompressedData(BuildBuffer.size(), 0);

		Utils::Compression::ZLIB_Compress(BuildBuffer.data(), BuildBuffer.size(), CompressedData.data(), CompressedSize);
		//fix length of compressed data

		if (CompressedSize = 0)
			Utils::System::Throw("SCO Compressed Size Invalid");
		else if (!Utils::Crypt::AES_Encrypt(CompressedData.data(), CompressedSize))
			Utils::System::Throw("SCO Encryption Failed");

		vector<uint32_t> SCR_Header = //size: 12
		{ 
		  Utils::Bitwise::SwapEndian(0x53435202u)//SCR.
		, Utils::Bitwise::SwapEndian(0x349D018Au)//GlobalsSignature
		, Utils::Bitwise::SwapEndian(CompressedSize)
		, Utils::Bitwise::SwapEndian(-3u)//-3 is_crypt?
		, Utils::Bitwise::SwapEndian(BuildBuffer.size())
		, Utils::Bitwise::SwapEndian(HLData->getStaticSize())
		, Utils::Bitwise::SwapEndian(0u)//GlobalsCount
		, Utils::Bitwise::SwapEndian(0u)//ParameterCount
		, Utils::Bitwise::SwapEndian(NativeHashMap.size())
		, Utils::Bitwise::SwapEndian(0u)//unk36
		, Utils::Bitwise::SwapEndian(0u)//unk40
		, Utils::Bitwise::SwapEndian(0u)//unk44
		};

		FILE* file = fopen(path, "wb");
		if (file != NULL)
		{
			fwrite(SCR_Header.data(), 1, 48, file);//encrypted data
			fwrite(CompressedData.data(), 1, CompressedSize, file);//encrypted data
			fclose(file);
		}
		else
			Utils::System::Throw("Could Not Open Output File");
	}
	else
	{
		FILE* file = fopen(path, "wb");

		if (file != NULL)
		{
			fwrite(BuildBuffer.data(), 1, BuildBuffer.size(), file);
			fclose(file);
		}
		else
			Utils::System::Throw("Could Not Open Output File");
	}

	#pragma endregion

}

#pragma endregion

#pragma endregion

#pragma region GTAV

#pragma region Parse_Functions
const uint32_t CompileGTAV::AddStringToStringPage(const string str)
{
	//if string is in table
	auto it = StringPageDataIndexing.find(str);
	if (it != StringPageDataIndexing.end())
	{
		return it->second;
	}

	const uint32_t len = str.length();
	const uint32_t pos = StringPageData.size();

	if ((pos + len + 1) % 16384 < pos % 16384)
		StringPageData.resize(16384 - (pos % 16384) + pos);

	StringPageDataIndexing[str] = StringPageData.size();
	StringPageData.resize(pos + len + 1);
	memcpy(StringPageData.data() + pos, str.data(), len + 1);
	return pos;
}
void CompileGTAV::fixFunctionCalls()
{
	for (auto CallInfo : CallLocations)
	{
		auto it = FuncLocations.find(CallInfo.FuncName);
		if (it == FuncLocations.end())
		{
			Utils::System::Throw("Function \"" + CallInfo.FuncName + "\" not found");
		}
		uint32_t pos = it->second;
		if (pos >= 0x1000000)
		{
			Utils::System::Throw("Function \"" + CallInfo.FuncName + "\" out of call range");//realistally this is never going to happen
		}
		switch (CallInfo.InstructionType)
		{
			case CallInstructionType::FuncLoc:
			*(int*)(CodePageData.data() - 1 + CallInfo.CallLocation) = Utils::Bitwise::SwapEndian(pos) | BaseOpcodes->PushI24;
			break;
			case CallInstructionType::Call:
			*(int*)(CodePageData.data() - 1 + CallInfo.CallLocation) = Utils::Bitwise::SwapEndian(pos) | BaseOpcodes->Call;
			break;
			default: assert(false && "Invalid Call Instruction"); break;
		}
	}
}
#pragma endregion

#pragma region Opcode_Functions
void CompileGTAV::CallNative(const uint32_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	// gta5 1 byte param/return, 2 byte call loc

	DoesOpcodeHaveRoom(4);

	AddOpcode(CallNative);
	if (hash == -1)
	{
		if (DATA->getNative()->getReturnCount() > 3)
			Utils::System::Throw("Native Calls Can Only Have Three Returns");

		const uint32_t index = AddNative(DATA->getNative()->getHash());
		if (index >= 0xFFFF)
			Utils::System::Throw("Native Call Index out of bounds");

		AddInt8( (DATA->getNative()->getParamCount() << 2) | (DATA->getNative()->getReturnCount() & 0x3));
		AddInt16(index);
	}
	else
	{
		if (returnCount > 3)
			Utils::System::Throw("Native Calls Can Only Have Three Returns");

		const uint32_t index = AddNative(hash);
		if (index >= 0xFFFF)
			Utils::System::Throw("Native Call Index out of bounds");

		AddInt8((paramCount << 2) | (returnCount & 0x3));
		AddInt16(index);
	}
}
void CompileGTAV::Call()
{
	// gta5: 3 byte loc
	DoesOpcodeHaveRoom(4);
	AddOpcode(Call);
	CallLocations.push_back({ CodePageData.size(), CallInstructionType::Call, DATA->getString() });
	AddInt24(0);
}
void CompileGTAV::PushString()
{
	PushInt(AddStringToStringPage(DATA->getString()));
	AddOpcode(PushString);
}
void CompileGTAV::GetImmP()
{
	const uint16_t value = DATA->getUShort(0);
	if (value <= 0xFF)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(GetImmP1);
		AddInt8(value);
	}
	else
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(GetImmP2);
		AddInt16(value);
	}
}
void CompileGTAV::GetImm()
{
	const uint16_t value = DATA->getUShort(0);
	if (value <= 0xFF)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(GetImm1);
		AddInt8(value);
	}
	else
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(GetImm2);
		AddInt16(value);
	}
}
void CompileGTAV::SetImm()
{
	const uint16_t value = DATA->getUShort(0);
	if (value <= 0xFF)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(SetImm1);
		AddInt8(value);
	}
	else
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(SetImm2);
		AddInt16(value);
	}
}
#pragma endregion

#pragma region Write_Functions
void CompileGTAV::WriteHeader()
{
	headerLocation = BuildBuffer.size();

	AddInt32toBuff(0xB43A4500);//page base
	AddInt32toBuff(0); //Unk1 ptr
	AddInt32toBuff(0); //codeBlocksListOffsetPtr
	AddInt32toBuff(0x11CD39A2);//unk2
	AddInt32toBuff(CodePageData.size());//code length
	AddInt32toBuff(0);//script ParameterCount (this needs to be implemented)
	AddInt32toBuff(HLData->getStaticSize());//statics count
	AddInt32toBuff(0);//GlobalsSize
	AddInt32toBuff(NativeHashMap.size());//natives count
	AddInt32toBuff(0); //Statics offset
	AddInt32toBuff(0); //Globals ptr, stay 0
	AddInt32toBuff(0); //native offset
	AddInt32toBuff(0);//Unk3
	AddInt32toBuff(0);//Unk4
	AddInt32toBuff(Utils::Hashing::Joaat(HLData->getScriptName()));
	AddInt32toBuff(1);//Unk5 typically 1
	AddInt32toBuff(0); //script name offset
	AddInt32toBuff(0); //strings offset
	AddInt32toBuff(StringPageData.size());
	AddInt32toBuff(0);//Unk6

	//no need to pad as its divisible by 16
}
void CompileGTAV::WritePointers()
{
	//Write script name
	const uint32_t StringSize = HLData->getScriptName().size() + 1;
	if (GetSpaceLeft(16384) < StringSize)
		FillPageDynamic(16384);

	SavedOffsets.ScriptName = BuildBuffer.size();

	BuildBuffer.resize(BuildBuffer.size() + StringSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - StringSize, HLData->getScriptName().data(), StringSize);
	Pad();

	//Write code page pointers
	if (GetSpaceLeft(16384) < CodePageCount * 4)
		FillPageDynamic(16384);

	SavedOffsets.CodeBlocks = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + CodePageCount * 4, 0);
	Pad();

	//Write string page pointers
	
	if (StringPageCount)
	{
		if (GetSpaceLeft(16384) < StringPageCount * 4)
			FillPageDynamic(16384);

		SavedOffsets.StringBlocks = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + StringPageCount * 4, 0);
		Pad();
	}
	else
	{
		if (GetSpaceLeft(16384) < 16)
			FillPageDynamic(16384);
		SavedOffsets.StringBlocks = BuildBuffer.size();
		ForcePad();
	}

	//write unk1
	if (GetSpaceLeft(16384) < 16)
		FillPageDynamic(16384);
	SavedOffsets.Unk1 = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + 16);
	*(BuildBuffer.data() + BuildBuffer.size() - 16 + 4) = 1;

	FillPageDynamic(16384 / 2);
}
void CompileGTAV::Write16384StringPages()
{
	if (StringPageCount)
	{
		SavedOffsets.StringPagePointers.resize(StringPageCount);
		for (uint32_t i = 0; i < StringPageCount - 1; i++)
		{
			if (GetSpaceLeft(16384) < 16384)
				FillPageDynamic(16384);

			SavedOffsets.StringPagePointers[i] = BuildBuffer.size();

			BuildBuffer.resize(BuildBuffer.size() + 16384);
			memcpy(BuildBuffer.data() + BuildBuffer.size() - 16384, StringPageData.data() + i * 16384, 16384);

			Pad();
		}
	}
}
void CompileGTAV::WriteFinalStringPage()
{
	if (StringPageCount)
	{
		const uint32_t LastStringPageSize = StringPageData.size() % 16384;
		SavedOffsets.StringPagePointers[StringPageCount - 1] = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + LastStringPageSize);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - LastStringPageSize, StringPageData.data() + StringPageData.size() - LastStringPageSize, LastStringPageSize);
		Pad();
	}
}
void CompileGTAV::XSCWrite(const char* path, bool AddRsc7Header)
{
	FilePadding = 0;
	ClearWriteVars();
	CodePageCount = Utils::Math::CeilDivInt(CodePageData.size(), 16384);
	StringPageCount = Utils::Math::CeilDivInt(StringPageData.size(), 16384);

	WriteHeader();
	Write16384CodePages();
	WriteFinalCodePage();
	Write16384StringPages();
	WriteFinalStringPage();
	WriteNatives();
	WriteStatics();
	WritePointers();

	#pragma region Fix_header_and_other_pointers
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.Unk1), headerLocation + 4);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.CodeBlocks), headerLocation + 8);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.Statics), headerLocation + 36);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.Natives), headerLocation + 44);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.ScriptName), headerLocation + 64);
	ChangeInt32inBuff(IntToPointerInt(SavedOffsets.StringBlocks), headerLocation + 68);

	for (uint32_t i = 0; i < SavedOffsets.CodePagePointers.size(); i++)
		ChangeInt32inBuff(IntToPointerInt(SavedOffsets.CodePagePointers[i]), SavedOffsets.CodeBlocks + (i * 4));
	for (uint32_t i = 0; i < SavedOffsets.StringPagePointers.size(); i++)
		ChangeInt32inBuff(IntToPointerInt(SavedOffsets.StringPagePointers[i]), SavedOffsets.StringBlocks + (i * 4));
	#pragma endregion

	FILE* file = fopen(path, "wb");

	#pragma region Write_File
	if (AddRsc7Header)
	{
		vector<uint32_t> rsc7 =
		{
			Utils::Bitwise::SwapEndian(0x52534337u),
			Utils::Bitwise::SwapEndian(0x00000009u),
			Utils::Bitwise::SwapEndian(0u),//GetFlagFromSize(BuildBuffer.size(), 16384 / 2)
			Utils::Bitwise::SwapEndian(0x90000000u)
		};

		fwrite(rsc7.data(), 1, 16, file);
	}

	fwrite(BuildBuffer.data(), 1, BuildBuffer.size(), file);
	fclose(file);
	#pragma endregion

}
#pragma endregion

#pragma endregion