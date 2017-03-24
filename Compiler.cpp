#include "Compiler.h"
#include "StaticData.h"
#include <random>
#include <chrono>

using namespace std;
using namespace Utils::System;
using namespace Utils::Bitwise;

#pragma region Base

#pragma region Parse_Functions
/*void CompileBase::fixFunctionJumps()
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
	*//*

	//should check if all labels and jumps are set before clearing
	JumpLocations.clear();
	LabelLocations.clear();
	SignedJumpLocationInc = UnsignedJumpLocationInc = 0;
	
}*/
void CompileBase::ParseGeneral(const OpcodeKind OK)
{
	switch (OK)
	{
		case OK_Null:		return;
		case OK_Nop:		AddPadding(DATA->getUShort(0)); return;
		case OK_Add:		DoesOpcodeHaveRoom(1); AddOpcode(Add); return;
		case OK_Sub:		DoesOpcodeHaveRoom(1); AddOpcode(Sub); return;
		case OK_Mult:		DoesOpcodeHaveRoom(1); AddOpcode(Mult); return;
		case OK_Div:		DoesOpcodeHaveRoom(1); AddOpcode(Div); return;
		case OK_Mod:		DoesOpcodeHaveRoom(1); AddOpcode(Mod); return;
		case OK_Not:		DoesOpcodeHaveRoom(1); AddOpcode(Not); return;
		case OK_Neg:		DoesOpcodeHaveRoom(1); AddOpcode(Neg); return;
		case OK_CmpEq:		DoesOpcodeHaveRoom(1); AddOpcode(CmpEq); return;
		case OK_CmpNe:		DoesOpcodeHaveRoom(1); AddOpcode(CmpNe); return;
		case OK_CmpGt:		DoesOpcodeHaveRoom(1); AddOpcode(CmpGt); return;
		case OK_CmpGe:		DoesOpcodeHaveRoom(1); AddOpcode(CmpGe); return;
		case OK_CmpLt:		DoesOpcodeHaveRoom(1); AddOpcode(CmpLt); return;
		case OK_CmpLe:		DoesOpcodeHaveRoom(1); AddOpcode(CmpLe); return;
		case OK_FAdd:		DoesOpcodeHaveRoom(1); AddOpcode(fAdd); return;
		case OK_FSub:		DoesOpcodeHaveRoom(1); AddOpcode(fSub); return;
		case OK_FMult:		DoesOpcodeHaveRoom(1); AddOpcode(fMult); return;
		case OK_FDiv:		DoesOpcodeHaveRoom(1); AddOpcode(fDiv); return;
		case OK_FMod:		DoesOpcodeHaveRoom(1); AddOpcode(fMod); return;
		case OK_FNeg:		DoesOpcodeHaveRoom(1); AddOpcode(fNeg); return;
		case OK_FCmpEq:		DoesOpcodeHaveRoom(1); AddOpcode(fCmpEq); return;
		case OK_FCmpNe:		DoesOpcodeHaveRoom(1); AddOpcode(fCmpNe); return;
		case OK_FCmpGt:		DoesOpcodeHaveRoom(1); AddOpcode(fCmpGt); return;
		case OK_FCmpGe:		DoesOpcodeHaveRoom(1); AddOpcode(fCmpGe); return;
		case OK_FCmpLt:		DoesOpcodeHaveRoom(1); AddOpcode(fCmpLt); return;
		case OK_FCmpLe:		DoesOpcodeHaveRoom(1); AddOpcode(fCmpLe); return;
		case OK_VAdd:		DoesOpcodeHaveRoom(1); AddOpcode(vAdd); return;
		case OK_VSub:		DoesOpcodeHaveRoom(1); AddOpcode(vSub); return;
		case OK_VMult:		DoesOpcodeHaveRoom(1); AddOpcode(vMult); return;
		case OK_VDiv:		DoesOpcodeHaveRoom(1); AddOpcode(vDiv); return;
		case OK_VNeg:		DoesOpcodeHaveRoom(1); AddOpcode(vNeg); return;
		case OK_And:		DoesOpcodeHaveRoom(1); AddOpcode(And); return;
		case OK_Or:			DoesOpcodeHaveRoom(1); AddOpcode(Or); return;
		case OK_Xor:		DoesOpcodeHaveRoom(1); AddOpcode(Xor); return;
		case OK_FtoI:		DoesOpcodeHaveRoom(1); AddOpcode(FtoI); return;
		case OK_ItoF:		DoesOpcodeHaveRoom(1); AddOpcode(ItoF); return;
		case OK_FtoV:		DoesOpcodeHaveRoom(1); AddOpcode(FtoV); return;
		case OK_PushInt:	PushInt(); return;//gta4 needs to override
		case OK_PushBytes:	PushBytes(); return;//gta4 needs to override
		case OK_PushFloat:	PushFloat(); return;//gta4 needs to override
		case OK_Dup:		DoesOpcodeHaveRoom(1); AddOpcode(Dup); return;
		case OK_Drop:		DoesOpcodeHaveRoom(1); AddOpcode(Drop); return;
		case OK_Native:		CallNative(DATA->getNative()->getHash(), DATA->getNative()->getParamCount(), DATA->getNative()->getReturnCount()); return;//callnative def| gta5 1 byte param/return, 2 byte call loc | rdr 2 byte call loc | gta4: 1 byte param, 1 byte return, 4 byte hash
		case OK_Return:		Return(); return;//rdr needs to override
		case OK_PGet:		DoesOpcodeHaveRoom(1); AddOpcode(pGet); return;
		case OK_PSet:		DoesOpcodeHaveRoom(1); AddOpcode(pSet); return;
		case OK_PeekSet:	DoesOpcodeHaveRoom(1); AddOpcode(pPeekSet); return;
		case OK_ToStack:	DoesOpcodeHaveRoom(1); AddOpcode(ToStack); return;
		case OK_FromStack:	DoesOpcodeHaveRoom(1); AddOpcode(FromStack); return;

		case OK_GetArrayP:	GetArrayP(); return;
		case OK_GetArray:	GetArray(); return;
		case OK_SetArray:	SetArray(); return;
		case OK_GetFrameP:	GetFrameP(); return;
		case OK_GetFrame:	GetFrame(); return;
		case OK_SetFrame:	SetFrame(); return;
		case OK_GetStaticP:	GetStaticP(); return;
		case OK_GetStaticPRaw:	GetStaticPRaw(); return;
		case OK_GetStatic:	GetStatic(); return;
		case OK_GetStaticRaw:	GetStaticRaw(); return;
		case OK_SetStatic:	SetStatic(); return;
		case OK_SetStaticRaw:	SetStaticRaw(); return;
		case OK_GetGlobalP:	GetGlobalP(); return;
		case OK_GetGlobal:	GetGlobal(); return;
		case OK_SetGlobal:	SetGlobal(); return;
		case OK_AddImm:		AddImm(); return;
		case OK_MultImm:	MultImm(); return;
		case OK_FAddImm:	FAddImm(); return;
		case OK_FMultImm:	FMultImm(); return;
		case OK_GetImmPStack:	GetImmPStack(); return;
		case OK_GetImmP:	GetImmP(); return;
		case OK_GetImm:		GetImm(); return;
		case OK_SetImm:		SetImm(); return;


		case OK_Call:		Call();  return;//call def| gta4: 4 byte loc | gta5: 3 byte loc | rdr: 2 byte loc (loc or'ed)
		case OK_Jump:		AddJump(JumpInstructionType::Jump, DATA->getString()); return;//gta 4 needs to override
		case OK_JumpFalse:	AddJump(JumpInstructionType::JumpFalse, DATA->getString()); return;//gta 4 needs to override
		case OK_JumpEQ:		AddJump(JumpInstructionType::JumpEQ, DATA->getString()); return;//gta 4 needs to override
		case OK_JumpNE:		AddJump(JumpInstructionType::JumpNE, DATA->getString()); return;//gta 4 needs to override
		case OK_JumpGT:		AddJump(JumpInstructionType::JumpGT, DATA->getString()); return;//gta 4 needs to override
		case OK_JumpGE:		AddJump(JumpInstructionType::JumpGE, DATA->getString()); return;//gta 4 needs to override
		case OK_JumpLT:		AddJump(JumpInstructionType::JumpLT, DATA->getString()); return;//gta 4 needs to override
		case OK_JumpLE:		AddJump(JumpInstructionType::JumpLE, DATA->getString()); return;//gta 4 needs to override
		case OK_Switch:		Switch(); return;
		case OK_PushString:	PushString(); return;//gta5 needs to override
		case OK_StrCopy:	StrCopy(); return;//gta4 needs to overrideul
		case OK_ItoS:		ItoS(); return;//gta4 needs to override
		case OK_StrAdd:		StrAdd(); return;//gta4 needs to override
		case OK_StrAddI:	StrAddI(); return;//gta4 needs to override
		case OK_MemCpy:		DoesOpcodeHaveRoom(1); AddOpcode(MemCopy); return;
		case OK_PCall:		pCall(); return;//gta4 needs to override as error
		case OK_Label:		AddLabel(DATA->getString()); return;
		case OK_LabelLoc:	AddJump(JumpInstructionType::LabelLoc, DATA->getString()); return;
		case OK_FuncLoc:	AddFuncLoc(DATA->getFunctionData()); return;
		case OK_ShiftLeft:	Shift_Left(); return;
		case OK_ShiftRight:	Shift_Right(); return;
		case OK_GetHash:	GetHash(); return;//gta5 needs to override
		case OK_GoToStack:	GoToStack(); return;
		case OK_JumpTable:	AddJumpTable(); return;
		case OK_PushNullPtr: DoesOpcodeHaveRoom(1); AddOpcode(Push_0);
		//default: assert(false && "Invalid General Opcode");
	}
}
void CompileBase::CheckLabels()
{
	for (JumpData Label : JumpLocations)
	{
		if (!Label.isSet)
		{
			Throw("Label " + Label.Label + " is not set");
		}
			
	}
}
void CompileBase::BuildTables()
{
	for (FunctionCount = 0; FunctionCount < HLData->getFunctionCount(); FunctionCount++)
	{
		if (HLData->getFunctionFromIndex(FunctionCount)->IsUsed())
		{
			AddFunction(HLData->getFunctionFromIndex(FunctionCount), DisableFunctionNames);
			for (InstructionCount = 0; InstructionCount < HLData->getFunctionFromIndex(FunctionCount)->getInstructionCount(); InstructionCount++)
			{
				ParseGeneral(HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)->getKind());
				CheckSignedJumps();
				CheckUnsignedJumps();
			}
			CheckLabels();
			fixFunctionJumps();
		}
	}
	fixFunctionCalls();
}
#pragma endregion

#pragma region Data_Functions
void CompileBase::AddLabel(const string& label)
{
	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end())
	{
		LabelLocations.insert({ label,{ CodePageData->getTotalSize(), true } });
	}
	else if (!it->second.isSet)
	{
		it->second.isSet = true;
		it->second.LabelLocation = CodePageData->getTotalSize();
		for (uint32_t i = 0; i < it->second.JumpIndexes.size(); i++)
		{
			//Fix jump forwards that are in range. Out of range jumps should have already been fixed.

			if (!JumpLocations[it->second.JumpIndexes[i]].isSet)
			{
				if (JumpLocations[it->second.JumpIndexes[i]].InstructionType != JumpInstructionType::LabelLoc)
				{
					const int32_t offset = it->second.LabelLocation - JumpLocations[it->second.JumpIndexes[i]].JumpLocation - 2;

					if (JumpLocations[it->second.JumpIndexes[i]].InstructionType == JumpInstructionType::Switch && (offset < 0 || offset > 65535))
						Utils::System::Throw("Switch label \"" + label + "\" out of jump range");
					else if (offset < -32768 || offset > 32767)
						Utils::System::Throw("Jump label \"" + label + "\" out of jump range");

					ChangeInt16InCodePage(offset, JumpLocations[it->second.JumpIndexes[i]].JumpLocation);

					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
				else
				{
					if (it->second.LabelLocation >= 0x1000000)
						Utils::System::Throw("Get label loc \"" + label + "\" out of jump range");

					ChangeInt24InCodePage(it->second.LabelLocation, JumpLocations[it->second.JumpIndexes[i]].JumpLocation);
					*(CodePageData->getPositionAddress(JumpLocations[it->second.JumpIndexes[i]].JumpLocation - 1)) = BaseOpcodes->PushI24;
					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
			}
		}
	}
	else
		Utils::System::Throw("Cannot add label. Label \"" + label + "\" already exists.");
}
void CompileBase::AddJump(const JumpInstructionType type, const string& label)
{
	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end() || !it->second.isSet)
	{
		//jump forward
		switch (type)
		{
			case JumpInstructionType::Jump:			DoesOpcodeHaveRoom(3); AddOpcode(Jump); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(3); AddOpcode(JumpFalse); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpNE); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(3); AddOpcode(JumpEQ); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLE); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLT); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGE); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGT); AddJumpLoc(type, label); break;
			case JumpInstructionType::LabelLoc:		DoesOpcodeHaveRoom(4); AddOpcode(PushI24); AddJumpLoc(type, label); break;
			default: assert(false && "Invalid JumpInstructionType"); break;
		}
	}
	else
	{
		//jump backward
		int32_t offset = it->second.LabelLocation - CodePageData->getTotalSize() - 3;//estimate
		assert(offset < 0);

		if (offset >= -32768 + 3 + 2)//3 for opcode size, 2 for possible DoesOpcodeHaveRoom padding
		{
			switch (type)
			{

				case JumpInstructionType::Jump:			DoesOpcodeHaveRoom(3); AddOpcode(Jump); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(3); AddOpcode(JumpFalse); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpNE); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(3); AddOpcode(JumpEQ); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLE); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLT); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGE); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGT); AddInt16(it->second.LabelLocation - CodePageData->getTotalSize() - 2); break;
				case JumpInstructionType::LabelLoc:		PushInt(it->second.LabelLocation); break;
				default: assert(false && "Invalid JumpInstructionType"); break;
			}
		}
		else
		{
			PushInt(it->second.LabelLocation);
			GoToStack();
		}
	}
	
}
CompileBase::JumpLabelData CompileBase::AddSwitchJump(const JumpInstructionType type, const string& label)
{
	if (type != JumpInstructionType::Switch)
		assert(false && "Invalid JumpInstructionType");

	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end() || !it->second.isSet)
	{
		//jump forward
		AddJumpLoc(type, label);
		return{ {0,type,label,false},{0,0,{}} };
	}
	else
	{
		//jump backward
		assert(it->second.LabelLocation - CodePageData->getTotalSize() - 2 >= 0);

		AddInt16(0);

		//have to add a jump forward to jump backward
		return{ { CodePageData->getTotalSize() - 2, type, label, false}, it->second };
	}

}

void CompileBase::CheckSignedJumps()
{
	if (!FindNextSignedJumpLocation())
		return;

	int32_t offset = (CodePageData->getTotalSize() + 3) - JumpLocations[SignedJumpLocationInc].JumpLocation - 2;
	if (offset > 31135)//to make this easier im going on the assumption that the max size of an opcode is 1532 (nothing can be added that is 1632) 100 bytes of leeway
	{
		//jump to jump code

		DoesOpcodeHaveRoom(3);
		AddOpcode(Jump);
		uint32_t JumpOverOffset = CodePageData->getTotalSize();
		AddInt16(0);

		//need to update jumps of same label that are out of bounds to jumps that are already added. instead of adding another jump to jump.

		offset = CodePageData->getTotalSize() - JumpLocations[SignedJumpLocationInc].JumpLocation - 2;

		do
		{
			if (offset > 32767)
				Throw("Jump label \"" + JumpLocations[SignedJumpLocationInc].Label + "\" out of jump range on jump to jump " + to_string(offset));

			ChangeInt16InCodePage(offset, JumpLocations[SignedJumpLocationInc].JumpLocation);

			JumpLocations[SignedJumpLocationInc].isSet = true;
			cout << "fixed label " + JumpLocations[SignedJumpLocationInc].Label << " at index " << SignedJumpLocationInc << endl;

			DoesOpcodeHaveRoom(3);
			AddOpcode(Jump);
			AddJumpLoc(JumpInstructionType::Jump, JumpLocations[SignedJumpLocationInc].Label);

			if (!FindNextSignedJumpLocation())
				return;

			offset = CodePageData->getTotalSize() - JumpLocations[SignedJumpLocationInc].JumpLocation - 2;
		} while (offset > 30000);


		//set jump over jump
		ChangeInt16InCodePage(CodePageData->getTotalSize() - JumpOverOffset - 2, JumpOverOffset);
	}

}
void CompileBase::CheckUnsignedJumps()
{
	if (!FindNextUnsignedJumpLocation())
		return;

	int32_t offset = (CodePageData->getTotalSize() + 3) - JumpLocations[UnsignedJumpLocationInc].JumpLocation - 2;
	if (offset > 63903)//to make this easier im going on the assumption that the max size of an opcode is 1532 (nothing can be added that is 1632) 10 bytes of leeway
	{
		//jump to jump code

		DoesOpcodeHaveRoom(3);
		AddOpcode(Jump);
		uint32_t JumpOverOffset = CodePageData->getTotalSize();
		AddInt16(0);

		//need to update jumps of same label that are out of bounds to jumps that are already added. instead of adding another jump to jump.

		offset = CodePageData->getTotalSize() - JumpLocations[UnsignedJumpLocationInc].JumpLocation - 2;

		do
		{
			if (offset > 65535)
				Throw("Jump label \"" + JumpLocations[UnsignedJumpLocationInc].Label + "\" out of jump range on jump to jump " + to_string(offset));

			ChangeInt16InCodePage(offset, JumpLocations[UnsignedJumpLocationInc].JumpLocation);
			JumpLocations[UnsignedJumpLocationInc].isSet = true;
			cout << "fixed label " + JumpLocations[UnsignedJumpLocationInc].Label << " at index " << UnsignedJumpLocationInc << endl;

			DoesOpcodeHaveRoom(3);
			AddOpcode(Jump);
			AddJumpLoc(JumpInstructionType::Jump, JumpLocations[UnsignedJumpLocationInc].Label);

			if (!FindNextUnsignedJumpLocation())
				return;

			offset = CodePageData->getTotalSize() - JumpLocations[UnsignedJumpLocationInc].JumpLocation - 2;
		} while (offset > 63903);


		//set jump over jump
		ChangeInt16InCodePage((CodePageData->getTotalSize() - JumpOverOffset - 2), JumpOverOffset);
	}

}

#pragma endregion

#pragma region Opcode_Functions
void CompileBase::PushInt(const int32_t Literal)
{
	if (Literal >= -1 && Literal <= 7) {
		DoesOpcodeHaveRoom(1);
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
		case 0xbf800000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_Neg1); break;
		case 0x80000000://neg 0
		case 0x00000000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_0); break;
		case 0x3f800000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_1); break;
		case 0x40000000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_2); break;
		case 0x40400000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_3); break;
		case 0x40800000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_4); break;
		case 0x40A00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_5); break;
		case 0x40C00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_6); break;
		case 0x40E00000:DoesOpcodeHaveRoom(1);  AddOpcode(PushF_7); break;
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
#define AddOpcodeStatic(op, errorstr)\
assert(DATA->getStaticData()->getStatic()->isUsed() && "unused static referenced, this shouldn't happen");\
const uint32_t value = DATA->getStaticData()->getStatic()->getIndex() + DATA->getStaticData()->getImmIndex();\
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
	AddInt16(value);\
}\
else if (value <= 0xFFFFFF)\
{\
	DoesOpcodeHaveRoom(4);\
	AddInt8(BaseOpcodes->##op##3);\
	AddInt24(value);\
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
	AddOpcodeStatic(GetStaticP, "GetStaticP index too high");
}
void CompileBase::GetStaticPRaw()
{
	AddOpcodeB_1or2(GetStaticP, "GetStaticP index too high");
}
void CompileBase::GetStatic()
{
	AddOpcodeStatic(GetStatic, "GetStatic index too high");
}
void CompileBase::GetStaticRaw()
{
	AddOpcodeB_1or2(GetStatic, "GetStatic index too high");
}
void CompileBase::SetStatic()
{
	AddOpcodeStatic(SetStatic, "SetStatic index too high");
}
void CompileBase::SetStaticRaw()
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
void CompileBase::AddFuncLoc(const FunctionData* function)
{
	DoesOpcodeHaveRoom(4);
	AddOpcode(PushI24);
	CallLocations.push_back({ CodePageData->getTotalSize(), CallInstructionType::FuncLoc, function });
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
		vector<CompileBase::JumpLabelData> CasesToBeFixed;
		const SwitchCaseStorage* sCase = switchStore->getFirstCase();

		AddInt32(sCase->getCaseValue());
		CompileBase::JumpLabelData JumpLabelData = AddSwitchJump(JumpInstructionType::Switch, sCase->getCaseLocation());
		if (JumpLabelData.JumpInfo.JumpLocation)
			CasesToBeFixed.push_back(JumpLabelData);

		while (sCase->hasNextCase())
		{
			sCase = sCase->getNextCase();
			AddInt32(sCase->getCaseValue());
			CompileBase::JumpLabelData JumpLabelData = AddSwitchJump(JumpInstructionType::Switch, sCase->getCaseLocation());
			if (JumpLabelData.JumpInfo.JumpLocation)
				CasesToBeFixed.push_back(JumpLabelData);
		}
		//start jump table to fix jumps
		if (CasesToBeFixed.size() > 0)
		{
			uint32_t JumpOverOffset;
			if (switchStore->hasDefaultJumpLoc())
			{
				AddJump(JumpInstructionType::Jump, switchStore->getDefaultJumpLoc()->toString());
			}
			else{
				DoesOpcodeHaveRoom(3);
				AddOpcode(Jump);
				JumpOverOffset = CodePageData->getTotalSize();
				AddInt16(0);
			}
			

			//need to update jumps of same label that are out of bounds to jumps that are already added. instead of adding another jump to jump.

			int32_t offset = 0;

			for (uint32_t i = 0; i < CasesToBeFixed.size(); i++)
			{
				offset = CodePageData->getTotalSize() - CasesToBeFixed[i].JumpInfo.JumpLocation - 2;
				if (offset > 65535)
					Throw("Jump label \"" + CasesToBeFixed[i].JumpInfo.Label + "\" out of jump range on jump to jump " + to_string(offset));

				ChangeInt16InCodePage(offset, CasesToBeFixed[i].JumpInfo.JumpLocation);

				cout << "fixed switch jump " + CasesToBeFixed[i].JumpInfo.Label << endl;


				offset = CasesToBeFixed[i].LabelInfo.LabelLocation - CodePageData->getTotalSize() - 3;
				if (offset >= -32768)
				{
					DoesOpcodeHaveRoom(3);
					AddOpcode(Jump);
					AddInt16(offset);
				}
				else
				{
					PushInt(CasesToBeFixed[i].LabelInfo.LabelLocation);
					GoToStack();
				}
			}


			//set jump over jump
			if (!switchStore->hasDefaultJumpLoc())
				ChangeInt16InCodePage(CodePageData->getTotalSize() - JumpOverOffset - 2, JumpOverOffset);
		}
		else if (switchStore->hasDefaultJumpLoc()){
			AddJump(JumpInstructionType::Jump, switchStore->getDefaultJumpLoc()->toString());
		}
	}
	else if (switchStore->hasDefaultJumpLoc())
	{
		AddJump(JumpInstructionType::Jump, switchStore->getDefaultJumpLoc()->toString());
	}
	
}
void CompileBase::AddImm(const int32_t Literal)
{
	if (Literal > 0 && Literal < 256)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(Add1);
		DoesOpcodeHaveRoom(1);
		AddInt8(Literal);
	}
	else if (Literal >= -32768 && Literal < 32768)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(Add2);
		DoesOpcodeHaveRoom(1);
		AddInt16(Literal);
	}
	else if (Literal > 0 && Literal < 0x1000000)
	{
		DoesOpcodeHaveRoom(4);
		AddOpcode(PushI24);
		AddInt24(Literal);
		DoesOpcodeHaveRoom(1);
		AddOpcode(Add);
	}
	else
	{
		DoesOpcodeHaveRoom(5);
		AddOpcode(Push);
		AddInt32(Literal);
		DoesOpcodeHaveRoom(1);
		AddOpcode(Add);
	}

}
void CompileBase::MultImm(const int32_t Literal)
{
	if (Literal > 0 && Literal < 256)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(Mult1);
		DoesOpcodeHaveRoom(1);
		AddInt8(Literal);
	}
	else if (Literal >= -32768 && Literal < 32768)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(Mult2);
		DoesOpcodeHaveRoom(1);
		AddInt16(Literal);
	}
	else if (Literal > 0 && Literal < 0x1000000)
	{
		DoesOpcodeHaveRoom(4);
		AddOpcode(PushI24);
		AddInt24(Literal);
		DoesOpcodeHaveRoom(1);
		AddOpcode(Mult);
	}
	else
	{
		DoesOpcodeHaveRoom(5);
		AddOpcode(Push);
		AddInt32(Literal);
		DoesOpcodeHaveRoom(1);
		AddOpcode(Mult);
	}

}
void CompileBase::FAddImm()
{
	switch (DATA->getInt())
	{
		case 0xc0e00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_7); DoesOpcodeHaveRoom(1); AddOpcode(fSub); break;
		case 0xc0c00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_6); DoesOpcodeHaveRoom(1); AddOpcode(fSub); break;
		case 0xc0a00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_5); DoesOpcodeHaveRoom(1); AddOpcode(fSub); break;
		case 0xc0800000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_4); DoesOpcodeHaveRoom(1); AddOpcode(fSub); break;
		case 0xc0400000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_3); DoesOpcodeHaveRoom(1); AddOpcode(fSub); break;
		case 0xc0000000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_2); DoesOpcodeHaveRoom(1); AddOpcode(fSub); break;
		case 0xbf800000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_1); DoesOpcodeHaveRoom(1); AddOpcode(fSub); break;
		case 0x80000000: //neg 0
		case 0x00000000: break;
		case 0x3f800000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_1); DoesOpcodeHaveRoom(1); AddOpcode(fAdd); break;
		case 0x40000000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_2); DoesOpcodeHaveRoom(1); AddOpcode(fAdd); break;
		case 0x40400000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_3); DoesOpcodeHaveRoom(1); AddOpcode(fAdd); break;
		case 0x40800000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_4); DoesOpcodeHaveRoom(1); AddOpcode(fAdd); break;
		case 0x40A00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_5); DoesOpcodeHaveRoom(1); AddOpcode(fAdd); break;
		case 0x40C00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_6); DoesOpcodeHaveRoom(1); AddOpcode(fAdd); break;
		case 0x40E00000: DoesOpcodeHaveRoom(1); AddOpcode(PushF_7); DoesOpcodeHaveRoom(1); AddOpcode(fAdd); break;
		default: DoesOpcodeHaveRoom(5); AddOpcode(PushF); AddFloat(DATA->getFloat()); DoesOpcodeHaveRoom(1);  AddOpcode(fAdd); break;
	}

}
void CompileBase::FMultImm()
{
	PushFloat();
	DoesOpcodeHaveRoom(1);
	AddOpcode(fMult);
}
#pragma endregion

#pragma region Write_Functions
void CompileBase::WriteCodePagesNoPadding()
{
	SavedOffsets.CodePagePointers.resize(CodePageData->getPageCount());
	for (uint32_t i = 0; i < CodePageData->getPageCount() - 1; i++)
	{	
		SavedOffsets.CodePagePointers[i] = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + 16384);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - 16384, CodePageData->getPageAddress(i), 16384);
	}
	const uint32_t LastCodePageSize = CodePageData->getLastPageSize();
	SavedOffsets.CodePagePointers[CodePageData->getPageCount() - 1] = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + LastCodePageSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - LastCodePageSize, CodePageData->getPageAddress(CodePageData->getPageCount() - 1), LastCodePageSize);
};
void CompileBase::Write16384CodePages()
{
	SavedOffsets.CodePagePointers.resize(CodePageData->getPageCount());
	for (uint32_t i = 0; i < CodePageData->getPageCount() - 1; i++)
	{

		if (GetSpaceLeft(16384) < 16384)
		{
			if(i)
				FillPageNops();
			else
				FillPageDynamic(16384);
		}

		SavedOffsets.CodePagePointers[i] = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + 16384);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - 16384, CodePageData->getPageAddress(i), 16384);

		PadNops();
	}
}
void CompileBase::WriteFinalCodePage()
{
	const uint32_t LastCodePageSize = CodePageData->getTotalSize() % 16384;
	SavedOffsets.CodePagePointers[CodePageData->getPageCount() - 1] = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + LastCodePageSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - LastCodePageSize, CodePageData->getPageAddress(CodePageData->getPageCount() - 1), LastCodePageSize);
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
	const size_t staticByteSize = HLData->getStaticCount() * 4;

	SavedOffsets.Statics = BuildBuffer.size();

	BuildBuffer.resize(BuildBuffer.size() + staticByteSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - staticByteSize, HLData->getNewStaticData(), staticByteSize);
}
void CompileBase::WriteStatics()
{

	if (HLData->getStaticCount() > 0)
	{
		const size_t staticByteSize = HLData->getStaticCount() * 4;

		if (GetSpaceLeft(16384) < staticByteSize)
			FillPageDynamic(16384);

		SavedOffsets.Statics = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + staticByteSize);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - staticByteSize, HLData->getNewStaticData(), staticByteSize);

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

#pragma region GTAIV

#pragma region Data_Functions
void CompileGTAIV::AddLabel(const string& label)
{
	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end())
	{
		LabelLocations.insert({ label,{ CodePageData->getTotalSize(), true } });
	}
	else if (!it->second.isSet)
	{
		it->second.isSet = true;
		it->second.LabelLocation = CodePageData->getTotalSize();
		for (uint32_t i = 0; i < it->second.JumpIndexes.size(); i++)
		{
			//Fix jump forwards that are in range. Out of range jumps should have already been fixed.

			if (!JumpLocations[it->second.JumpIndexes[i]].isSet)
			{
				if (JumpLocations[it->second.JumpIndexes[i]].InstructionType != JumpInstructionType::LabelLoc)
				{
					ChangeInt32InCodePage(it->second.LabelLocation, JumpLocations[it->second.JumpIndexes[i]].JumpLocation);
					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
				else
				{
					ChangeInt32InCodePage(it->second.LabelLocation, JumpLocations[it->second.JumpIndexes[i]].JumpLocation);
					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
			}
		}
	}
	else
		Utils::System::Throw("Cannot add label. Label \"" + label + "\" already exists.");
}
void CompileGTAIV::AddJump(const JumpInstructionType type, const string& label)
{
	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end() || !it->second.isSet)
	{
		//jump forward
		switch (type)
		{
			case JumpInstructionType::Jump:			DoesOpcodeHaveRoom(5); AddOpcode(Jump); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(5); AddOpcode(JumpFalse); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(6); AddOpcode(CmpNe); AddOpcode(JumpTrue); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(6); AddOpcode(CmpEq); AddOpcode(JumpTrue); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(6); AddOpcode(CmpLe); AddOpcode(JumpTrue); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(6); AddOpcode(CmpLt); AddOpcode(JumpTrue); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(6); AddOpcode(CmpGe); AddOpcode(JumpTrue); AddJumpLoc(type, label); break;
			case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(6); AddOpcode(CmpGt); AddOpcode(JumpTrue); AddJumpLoc(type, label); break;
			case JumpInstructionType::LabelLoc:		DoesOpcodeHaveRoom(5); AddOpcode(Push); AddJumpLoc(type, label); break;
			default: assert(false && "Invalid JumpInstructionType"); break;
		}
	}
	else
	{
		//jump backward
		switch (type)
		{
			case JumpInstructionType::Jump:			DoesOpcodeHaveRoom(5); AddOpcode(Jump); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(5); AddOpcode(JumpFalse); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(6); AddOpcode(CmpNe); AddOpcode(JumpTrue); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(6); AddOpcode(CmpEq); AddOpcode(JumpTrue); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(6); AddOpcode(CmpLe); AddOpcode(JumpTrue); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(6); AddOpcode(CmpLt); AddOpcode(JumpTrue); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(6); AddOpcode(CmpGe); AddOpcode(JumpTrue); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(6); AddOpcode(CmpGt); AddOpcode(JumpTrue); AddInt32(it->second.LabelLocation); break;
			case JumpInstructionType::LabelLoc:		PushInt(it->second.LabelLocation); break;
			default: assert(false && "Invalid JumpInstructionType"); break;
		}
	}

}
CompileBase::JumpLabelData CompileGTAIV::AddSwitchJump(const JumpInstructionType type, const string& label)
{
	if (type != JumpInstructionType::Switch)
		assert(false && "Invalid JumpInstructionType");

	auto it = LabelLocations.find(label);
	if (it == LabelLocations.end() || !it->second.isSet)
	{
		//jump forward
		AddJumpLoc(type, label);
		return{ { 0,type,label,false },{ 0,0,{} } };
	}
	else
	{
		//jump backward
		assert(it->second.LabelLocation - CodePageData->getTotalSize() - 4 >= 0);

		AddInt32(0);

		//have to add a jump forward to jump backward
		return{ { CodePageData->getTotalSize() - 4, type, label, false }, it->second };
	}

}
#pragma endregion

#pragma region Opcode_Functions
void CompileGTAIV::PushInt(const int32_t Literal)
{
	if (Literal >= -16 && Literal <= 159) {
		DoesOpcodeHaveRoom(1);
		AddInt8(BaseOpcodes->Push_0 + Literal);
	}
	else if (Literal >= -32768 && Literal <= 32767)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(PushS);
		AddInt16(Literal);
	}
	else
	{
		DoesOpcodeHaveRoom(5);
		AddOpcode(Push);
		AddInt32(Literal);
	}


}
void CompileGTAIV::PushFloat(const float Literal)
{
	DoesOpcodeHaveRoom(5);
	AddOpcode(PushF);
	AddFloat(Literal);
}
void CompileGTAIV::PushBytes()
{
	switch (DATA->getByte(0))
	{
		case 0: assert(false && "Empty PushBytes opcode"); break;
		case 1: PushInt(DATA->getByte(1)); break;
		case 2: PushInt(DATA->getByte(1)); PushInt(DATA->getByte(2)); break;
		case 3: PushInt(DATA->getByte(1)); PushInt(DATA->getByte(2)); PushInt(DATA->getByte(3)); break;
		default:
		assert(false && "Too many bytes in PushBytes opcode");
	}
}
void CompileGTAIV::GetArrayP()
{
	DoesOpcodeHaveRoom(1);
	AddOpcode(GetArrayP);
}
void CompileGTAIV::GetArray()
{
	GetArrayP();
	AddOpcode(pGet);
}
void CompileGTAIV::SetArray()
{
	GetArrayP();
	AddOpcode(pSet);
}
void CompileGTAIV::GetFrameP()
{
	const uint32_t value = DATA->getInt();
	if (value >= 0 && value <= 7)
	{
		switch (value)
		{
			case 0: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP0); break;
			case 1: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP1); break;
			case 2: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP2); break;
			case 3: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP3); break;
			case 4: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP4); break;
			case 5: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP5); break;
			case 6: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP6); break;
			case 7: DoesOpcodeHaveRoom(1); AddOpcode(GetFrameP7); break;
			default: assert(false && "Invalid FrameP Opcode");
		}
	}
	else
	{
		PushInt(DATA->getInt());
		DoesOpcodeHaveRoom(1);
		AddOpcode(GetFrameP);
	}
	
}
void CompileGTAIV::GetFrame()
{
	GetFrameP();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pGet);
}
void CompileGTAIV::SetFrame()
{
	GetFrameP();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pSet);
}
void CompileGTAIV::GetStaticP()
{
	assert(DATA->getStaticData()->getStatic()->isUsed() && "unused static referenced, this shouldn't happen");
	const uint32_t value = DATA->getStaticData()->getStatic()->getIndex() + DATA->getStaticData()->getImmIndex();
	PushInt(value);
	DoesOpcodeHaveRoom(1);
	AddOpcode(GetStaticP);
}
void CompileGTAIV::GetStaticPRaw()
{
	PushInt(DATA->getInt());
	DoesOpcodeHaveRoom(1);
	AddOpcode(GetStaticP);
}
void CompileGTAIV::GetStatic()
{
	GetStaticP();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pGet);
}
void CompileGTAIV::GetStaticRaw()
{
	GetStaticPRaw();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pGet);
}
void CompileGTAIV::SetStatic()
{
	GetStaticP();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pSet);
}
void CompileGTAIV::SetStaticRaw()
{
	GetStaticPRaw();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pSet);
}
void CompileGTAIV::GetGlobalP()
{
	PushInt(DATA->getInt());
	DoesOpcodeHaveRoom(1);
	AddOpcode(GetGlobalP);
}
void CompileGTAIV::GetGlobal()
{
	GetGlobalP();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pGet);
}
void CompileGTAIV::SetGlobal()
{
	GetGlobalP();
	DoesOpcodeHaveRoom(1);
	AddOpcode(pSet);
}


void CompileGTAIV::pCall()
{
	DoesOpcodeHaveRoom(15);
	AddOpcode(PushString);
	AddInt8(0);//length
	AddInt8(0);//null termination needed?
	PushInt(5);
	AddOpcode(Add);
	AddOpcode(pSet);
	AddOpcode(Call);
	AddInt32(0xCDCDCDCD);
}
void CompileGTAIV::AddImm(const int32_t Literal)
{
	PushInt(Literal);
	DoesOpcodeHaveRoom(1);
	AddOpcode(Add);
}
void CompileGTAIV::MultImm(const int32_t Literal)
{
	PushInt(Literal);
	DoesOpcodeHaveRoom(1);
	AddOpcode(Mult);
}
void CompileGTAIV::FAddImm()
{
	PushFloat();
	DoesOpcodeHaveRoom(1);
	AddOpcode(fAdd);
}
void CompileGTAIV::FMultImm()
{
	PushFloat();
	DoesOpcodeHaveRoom(1);
	AddOpcode(fMult);
}
void CompileGTAIV::CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	// gta5 1 byte param/return, 2 byte call loc


	DoesOpcodeHaveRoom(7);

	AddOpcode(CallNative);

	if (paramCount > 255)
		Utils::System::Throw("Native Calls Can Only Have Up To 255 Params");
	else
		AddInt8(paramCount);
	
	if (returnCount > 255)
		Utils::System::Throw("Native Calls Can Only Have Up To 255 Returns");
	else
		AddInt8(returnCount);

	AddInt32(hash);
}

void CompileGTAIV::Call()
{
	// gta4: 4 byte loc
	DoesOpcodeHaveRoom(5);
	AddOpcode(Call);
	CallLocations.push_back({ CodePageData->getTotalSize(), CallInstructionType::Call, DATA->getFunctionData() });
	AddInt32(0);
}
void CompileGTAIV::GetImmPStack()
{
	PushInt(4);
	DoesOpcodeHaveRoom(1);
	AddOpcode(Mult);
	DoesOpcodeHaveRoom(1);
	AddOpcode(Add);
}
void CompileGTAIV::GetImm()
{
	const uint32_t value = (uint32_t)DATA->getInt() * 4;
	AddImm(value);
	DoesOpcodeHaveRoom(1);
	AddOpcode(pGet);
}
void CompileGTAIV::SetImm()
{
	const uint32_t value = (uint32_t)DATA->getInt() * 4;
	AddImm(value);
	DoesOpcodeHaveRoom(1);
	AddOpcode(pSet);
}
void CompileGTAIV::GoToStack()
{
	DoesOpcodeHaveRoom(4);
	AddOpcode(Function);
	AddInt8(0);
	AddInt16(2);
	DoesOpcodeHaveRoom(3);
	AddOpcode(Return);
	AddInt16(0);
}
void CompileGTAIV::AddJumpTable()
{
	auto jumpTable = DATA->getJumpTable();
	const uint32_t len = jumpTable->getByteSize();
	if (len < 256)//push string
	{
		DoesOpcodeHaveRoom(2 + len);//PushString - Size - length
		AddOpcode(PushString);
		AddInt8(len);
		for (unsigned i = 0; i < jumpTable->getItemCount(); i++)
		{
			jumpTableLocs.push_back({ CodePageData->getTotalSize(), jumpTable->getJumpLocAsString(i), jumpTable->getXORValue() });
			AddInt32(0);//place holder
		}
	}
	else
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(PushString);
		AddInt8(0);
		AddInt8(0);

		DoesOpcodeHaveRoom(5);
		AddOpcode(Jump);
		AddInt32(len);
		for (unsigned i = 0; i < jumpTable->getItemCount(); i++)
		{
			jumpTableLocs.push_back({ CodePageData->getTotalSize(), jumpTable->getJumpLocAsString(i), jumpTable->getXORValue() });
			AddInt32(0);//place holder
		}

		PushInt(len + 1 + 5);
		DoesOpcodeHaveRoom(1);
		AddOpcode(Add);
	}
}
#pragma endregion

#pragma region Parse_Functions
void CompileGTAIV::fixFunctionCalls()
{
	for (auto CallInfo : CallLocations)
	{
		auto it = FuncLocations.find(CallInfo.Function);
		if (it == FuncLocations.end())
		{
			Utils::System::Throw("Function \"" + CallInfo.Function->getName() + "\" not found");
		}
		uint32_t pos = it->second;
		switch (CallInfo.InstructionType)
		{
			case CallInstructionType::FuncLoc:
			case CallInstructionType::Call:
			ChangeInt32InCodePage(pos, CallInfo.CallLocation);
			break;
			default: assert(false && "Invalid Call Instruction"); break;
		}
	}
}
void CompileGTAIV::fixFunctionJumps()
{
	for (auto jTableItem : jumpTableLocs)
	{
		auto it = LabelLocations.find(jTableItem.labelName);
		if (it == LabelLocations.end())
		{
			Throw("Jump table label '" + jTableItem.labelName + "' not found");
		}
		ChangeInt32InCodePage(it->second.LabelLocation ^ jTableItem.xorVal, jTableItem.tableOffset);
	}
	jumpTableLocs.clear();
	JumpLocations.clear();
	LabelLocations.clear();
	SignedJumpLocationInc = UnsignedJumpLocationInc = 0;
}
void CompileGTAIV::BuildTables()
{
	for (FunctionCount = 0; FunctionCount < HLData->getFunctionCount(); FunctionCount++)
	{
		if (HLData->getFunctionFromIndex(FunctionCount)->IsUsed())
		{
			AddFunction(HLData->getFunctionFromIndex(FunctionCount), DisableFunctionNames);
			for (InstructionCount = 0; InstructionCount < HLData->getFunctionFromIndex(FunctionCount)->getInstructionCount(); InstructionCount++)
			{
				ParseGeneral(HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)->getKind());
			}
			CheckLabels();
			fixFunctionJumps();
		}
	}
	fixFunctionCalls();
}

#pragma endregion

#pragma region Write_Functions
void CompileGTAIV::WriteStaticsNoPadding()
{
	const size_t staticByteSize = HLData->getStaticCount() * 4;
	SavedOffsets.Statics = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + staticByteSize);
	for (uint32_t i = 0; i < staticByteSize; i += 4)
	{
		*(int32_t*)(BuildBuffer.data() + BuildBuffer.size() - staticByteSize + i) = Utils::Bitwise::SwapEndian(*(int32_t*)(HLData->getNewStaticData() + i));
	}
}

CompileGTAIV::SignatureTypes CompileGTAIV::GetSignature()
{
	switch (HLData->getBuildType())
	{
		case BT_GTAIV_TLAD:
		return SignatureTypes::TLAD;
		break;
		case BT_GTAIV_TBOGT:
		return SignatureTypes::TBOGT;
		break;
		default:
		case BT_GTAIV:
		return SignatureTypes::GTAIV;
		break;
	}
}
void CompileGTAIV::SCOWrite(const char* path, CompileGTAIV::SCRFlags EncryptionCompressionLevel)
{
	const uint8_t GTAIVEncryptionKey[32] = { 0x1A,0xB5,0x6F,0xED,0x7E,0xC3,0xFF,0x01,0x22,0x7B,0x69,0x15,0x33,0x97,0x5D,0xCE,0x47,0xD7,0x69,0x65,0x3F,0xF7,0x75,0x42,0x6A,0x96,0xCD,0x6D,0x53,0x07,0x56,0x5D };

	FilePadding = 0x00;
	ClearWriteVars();

	enum HeaderIndexes
	{
		CodeSize = 1,
		StaticsCount = 2,
		GlobalsCount = 3,
	};

	const uint32_t HeaderSize = 24;
	const vector<uint32_t> SCR_Header = {
		Utils::Bitwise::SwapEndian((uint32_t)EncryptionCompressionLevel)//SCR.
		, CodePageData->getTotalSize()//code size
		, HLData->getStaticCount()//statics count
		, 0u//Globals Alloc Count
		, Utils::Bitwise::SwapEndian(0u)//Script Flags
		, Utils::Bitwise::SwapEndian((uint32_t)GetSignature())//Signature
	};
	
	WriteCodePagesNoPadding();
	WriteStaticsNoPadding();
	//Globals should be written here if we decide to use them

	#pragma region Write_File

	switch (EncryptionCompressionLevel)
	{
		case SCRFlags::CompressedEncrypted:{
			uint32_t CompressedSize = BuildBuffer.size();
			vector<uint8_t> CompressedData(CompressedSize * 2, 0);
			Utils::Compression::ZLIB_CompressChecksum(BuildBuffer.data(), BuildBuffer.size(), CompressedData.data(), CompressedSize);

			if (CompressedSize <= 0)
				Utils::System::Throw("SCO Compressed Size Invalid");

			if (!Utils::Crypt::AES_Encrypt(CompressedData.data(), CompressedSize, GTAIVEncryptionKey))
				Utils::System::Throw("SCO Encryption Failed");

			FILE* file = fopen(path, "wb");
			if (Utils::IO::CheckFopenFile(path, file))
			{
				std::fwrite(SCR_Header.data(), 1, HeaderSize, file);//header
				std::fwrite(&CompressedSize, 1, 4, file);//compressed size
				std::fwrite(CompressedData.data(), 1, CompressedSize, file);//opcode data
				std::fclose(file);
			}
		}
		break;
		case SCRFlags::Encrypted:{
			if (SCR_Header[CodeSize] > 0)
			{
				if (!Utils::Crypt::AES_Encrypt(BuildBuffer.data(), SCR_Header[CodeSize], GTAIVEncryptionKey))
					Utils::System::Throw("SCO Code Page Encryption Failed");
			}
			if (SCR_Header[StaticsCount] > 0)
			{
				if (!Utils::Crypt::AES_Encrypt(BuildBuffer.data() + SCR_Header[CodeSize], SCR_Header[StaticsCount] * 4, GTAIVEncryptionKey))
					Utils::System::Throw("SCO Statics Page Encryption Failed");
			}
			if (SCR_Header[GlobalsCount] > 0)
			{
				if (!Utils::Crypt::AES_Encrypt(BuildBuffer.data() + SCR_Header[CodeSize] + SCR_Header[StaticsCount] * 4, SCR_Header[GlobalsCount] * 4, GTAIVEncryptionKey))
					Utils::System::Throw("SCO Globals Page Encryption Failed");
			}
		}
		//intentional no break
		case SCRFlags::Standard:{
			FILE* file = fopen(path, "wb");
			if (Utils::IO::CheckFopenFile(path, file))
			{
				std::fwrite(SCR_Header.data(), 1, HeaderSize, file);//header
				std::fwrite(BuildBuffer.data(), 1, BuildBuffer.size(), file);
				std::fclose(file);
			}
		}
		break;
	}

	#pragma endregion

}

#pragma endregion


#pragma endregion

#pragma region RDR

#pragma region Parse_Functions
void CompileRDR::fixFunctionCalls()
{
	for (auto CallInfo : CallLocations)
	{
		auto it = FuncLocations.find(CallInfo.Function);
		if (it == FuncLocations.end())
		{
			Throw("Function \"" + CallInfo.Function->getName() + "\" not found");
		}
		uint32_t pos = it->second;
		if (pos >= 0x1000000)
			Throw("Function \"" + CallInfo.Function->getName() + "\" out of call range");
		
		switch (CallInfo.InstructionType)
		{
			case CallInstructionType::FuncLoc:
				ChangeInt24InCodePage(pos, CallInfo.CallLocation);
				*(CodePageData->getPositionAddress(CallInfo.CallLocation) - 1) = BaseOpcodes->PushI24;
			break;
			case CallInstructionType::Call:
				if (pos > 1048575)
				{
					ChangeInt24InCodePage(pos, CallInfo.CallLocation);
					*(CodePageData->getPositionAddress(CallInfo.CallLocation) - 1) = BaseOpcodes->PushI24;
					*(CodePageData->getPositionAddress(CallInfo.CallLocation) + 4) = RDROpcodes.pCall;
				}
				else
				{
					*(CodePageData->getPositionAddress(CallInfo.CallLocation)) = GetNewCallOpCode(pos);//any out of range errors already been caught
					ChangeInt16InCodePage(GetNewCallOffset((uint16_t)pos), CallInfo.CallLocation + 1);
				}
			break;
			default: assert(false && "Invalid Call Instruction"); break;
		}
	}
}
void CompileRDR::fixFunctionJumps()
{
	for (auto jTableItem : jumpTableLocs)
	{
		auto it = LabelLocations.find(jTableItem.labelName);
		if (it == LabelLocations.end())
		{
			Throw("Jump table label '" + jTableItem.labelName + "' not found");
		}
		ChangeInt32InCodePage(it->second.LabelLocation ^ jTableItem.xorVal, jTableItem.tableOffset);
	}
	jumpTableLocs.clear();
	JumpLocations.clear();
	LabelLocations.clear();
	SignedJumpLocationInc = UnsignedJumpLocationInc = 0;
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
void CompileRDR::CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	// rdr 2 byte call loc based on index
	//PLS Check RDR native has 10 bits index, 5 bits pCount, 1 bit rCount
	DoesOpcodeHaveRoom(3);

	AddOpcode(CallNative);
	if (returnCount > 1)
		Throw("Native Calls Can Only Have One Return");
	if (paramCount > 31)
		Utils::System::Throw("Native Calls Can Only Have Up To Thirty One Params");

	const uint32_t index = AddNative(hash);
	if (index >= 1024)
		Throw("Native Call Index out of bounds");

	AddInt16(SetNewIndex(index, paramCount, returnCount == 1));
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
	auto func = DATA->getFunctionData();
	auto it = FuncLocations.find(func);
	if (it == FuncLocations.end())
	{
		DoesOpcodeHaveRoom(4);//4 because pcall can be separate
		CallLocations.push_back({ CodePageData->getTotalSize(), CallInstructionType::Call, func });
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
			AddInt16(GetNewCallOffset((uint16_t)it->second));
		}
	}

	
}
void CompileRDR::GetImmPStack()
{
	DoesOpcodeHaveRoom(2);
	AddOpcode(Mult1);
	AddInt8(4);
	DoesOpcodeHaveRoom(1);
	AddOpcode(Add);
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
		DoesOpcodeHaveRoom(1);
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
		DoesOpcodeHaveRoom(1);
		AddOpcode(pSet);
	}
}
void CompileRDR::GoToStack()
{
	DoesOpcodeHaveRoom(5);
	AddOpcode(Function);
	AddInt8(0);
	AddInt16(2);
	AddInt8(0);
	DoesOpcodeHaveRoom(1);
	AddOpcode(ReturnP0R0);
}
void CompileRDR::AddJumpTable()
{
	auto jumpTable = DATA->getJumpTable();
	const uint32_t len = jumpTable->getByteSize();
	if (len < 256)//push string
	{
		DoesOpcodeHaveRoom(2 + len);//PushString - Size - length
		AddOpcode(PushString);
		AddInt8(len);
		for (unsigned i = 0; i < jumpTable->getItemCount();i++)
		{
			jumpTableLocs.push_back({ CodePageData->getTotalSize(), jumpTable->getJumpLocAsString(i), jumpTable->getXORValue() });
			AddInt32(0);//place holder
		}
	}
	else
	{
		DoesOpcodeHaveRoom(5 + len);
		AddOpcode(PushArrayP);
		AddInt32(len);
		for (unsigned i = 0; i < jumpTable->getItemCount(); i++)
		{
			jumpTableLocs.push_back({ CodePageData->getTotalSize(), jumpTable->getJumpLocAsString(i), jumpTable->getXORValue() });
			AddInt32(0);//place holder
		}
		AddImm(4);//Skip past the size of the array
	}
}
#pragma endregion

#pragma region Write_Functions
void CompileRDR::WriteHeader()
{
	headerLocation = BuildBuffer.size();
	AddInt32toBuff(0xA8D74300);//Page Base
	AddInt32toBuff(0); //Page Map ptr
	AddInt32toBuff(0); //codeBlocksListOffsetPtr
	AddInt32toBuff(CodePageData->getTotalSize());//code length
	AddInt32toBuff(HLData->getParameterCount());//script ParameterCount (this needs to be implemented)
	AddInt32toBuff(HLData->getStaticCount());//statics count
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

	uint64_t padcount = Utils::Math::CeilDivInt(CodePageData->getPageCount() * 4, 16);
	for (uint64_t i = 0; i < padcount; i++)
		ForcePad();

	//Write code page pointers
	if (GetSpaceLeft(16384) < CodePageData->getPageCount() * 4)
		FillPageDynamic(16384);

	SavedOffsets.CodeBlocks = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + CodePageData->getPageCount() * 4, 0);


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

	#pragma region Write_Pages_and_header

	const uint32_t CodePagePtrsSize = CodePageData->getPageCount() * 4;

	uint32_t TotalData = GetPadExpectedAmount(NativeHashMap.size() * 4) +
		GetPadExpectedAmount(HLData->getStaticCount() * 4) +
		GetPadExpectedAmount(16 + CodePagePtrsSize) + //unk1 4 but set as 16 (padded) to avoid miscalculating the pad size
		GetPadExpectedAmount(40) + //header
		GetPadExpectedAmount(CodePagePtrsSize);//code page pointers

	uint32_t LastCodePageSize = GetPadExpectedAmount(CodePageData->getTotalSize() % 16384);//code page pointers * padding for unk1

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
		vector<uint8_t> CompressedData;
		uint32_t CompressedLen = 0;

		switch (HLData->getBuildPlatform())
		{
			case Platform::P_XBOX:
			{
				Utils::Compression::xCompress Compression;
				Compression.xCompressInit();

				CompressedData.resize(BuildBuffer.size() + 8);
				CompressedLen = 0;

				Compression.Compress((uint8_t*)BuildBuffer.data(), BuildBuffer.size(), CompressedData.data() + 8, (int32_t*)&CompressedLen);

				if (CompressedLen > 0)
				{
					*(uint32_t*)CompressedData.data() = SwapEndian(0x0FF512F1);//LZX Signature?
					*(uint32_t*)(CompressedData.data() + 4) = SwapEndian(CompressedLen);
					CompressedLen += 8;
				}
				else Throw("Compression Failed");

				CompressedData.resize(CompressedLen);
			}
			break;
			case Platform::P_PS3:
			{
				CompressedData.resize(BuildBuffer.size(), 0);
				CompressedLen = BuildBuffer.size();
				Utils::Compression::ZLIB_Compress(BuildBuffer.data(), BuildBuffer.size(), CompressedData.data(), CompressedLen);
				
				if (CompressedLen == 0)
					Throw("CSC Compressed Size Invalid");

				CompressedData.resize(CompressedLen);
			}
			break;
			case Platform::P_PC:
			default:
			Throw("Invalid Build Platform for compression");
		}


		const uint8_t RDREncryptionKey[32] = { 0xB7, 0x62, 0xDF, 0xB6, 0xE2, 0xB2, 0xC6, 0xDE, 0xAF, 0x72, 0x2A, 0x32, 0xD2, 0xFB, 0x6F, 0x0C, 0x98, 0xA3, 0x21, 0x74, 0x62, 0xC9, 0xC4, 0xED, 0xAD, 0xAA, 0x2E, 0xD0, 0xDD, 0xF9, 0x2F, 0x10 };

		if (!Utils::Crypt::AES_Encrypt(CompressedData.data(), CompressedLen, RDREncryptionKey))
			Throw("Encryption Failed");

		const vector<uint32_t> CSR_Header =
		{
			SwapEndian(HLData->getBuildPlatform() == Platform::P_XBOX ? 0x85435352u : 0x86435352u),//.CSR
			SwapEndian(0x00000002u),//Resource Type Script
			SwapEndian(0x80000000u),//unk int max val (flags1)
			SwapEndian(GetFullFlagWithSize(BuildBuffer.size(), headerFlag))//size (flags2)
		};

		FILE* file = fopen(path, "wb");
		if (file != NULL)
		{
			fwrite(CSR_Header.data(), 1, 16, file);//encrypted data
			fwrite(CompressedData.data(), 1, CompressedLen, file);//encrypted data
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

		const uint8_t RDREncryptionKey[32] = { 0xB7, 0x62, 0xDF, 0xB6, 0xE2, 0xB2, 0xC6, 0xDE, 0xAF, 0x72, 0x2A, 0x32, 0xD2, 0xFB, 0x6F, 0x0C, 0x98, 0xA3, 0x21, 0x74, 0x62, 0xC9, 0xC4, 0xED, 0xAD, 0xAA, 0x2E, 0xD0, 0xDD, 0xF9, 0x2F, 0x10 };

		if (CompressedSize = 0)
			Utils::System::Throw("SCO Compressed Size Invalid");
		else if (!Utils::Crypt::AES_Encrypt(CompressedData.data(), CompressedSize, RDREncryptionKey))
			Utils::System::Throw("SCO Encryption Failed");

		const vector<uint32_t> SCR_Header = //size: 12
		{ 
		  Utils::Bitwise::SwapEndian(0x53435202u)//SCR.
		, Utils::Bitwise::SwapEndian(0x349D018Au)//GlobalsSignature
		, Utils::Bitwise::SwapEndian(CompressedSize)
		, Utils::Bitwise::SwapEndian(-3u)//-3 is_crypt?
		, Utils::Bitwise::SwapEndian(BuildBuffer.size())
		, Utils::Bitwise::SwapEndian(HLData->getStaticCount())
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
inline int32_t CompileGTAV::GetSizeFromFlag(uint32_t flag, int32_t baseSize)
{
	baseSize <<= (int32_t)(flag & 0xf);
	int size = (int32_t)((((flag >> 17) & 0x7f) + (((flag >> 11) & 0x3f) << 1) + (((flag >> 7) & 0xf) << 2) + (((flag >> 5) & 0x3) << 3) + (((flag >> 4) & 0x1) << 4)) * baseSize);
	for (int32_t i = 0; i < 4; ++i)
		size += (((flag >> (24 + i)) & 1) == 1) ? (baseSize >> (1 + i)) : 0;
	return size;
}
inline int32_t CompileGTAV::GetSizeFromSystemFlag(uint32_t flag)
{
	if (HLData->getBuildPlatform() == Platform::P_PS3)
		return GetSizeFromFlag(flag, 0x1000);
	else // XBOX 360 / PC
		return GetSizeFromFlag(flag, 0x2000);
}
inline int32_t CompileGTAV::GetSizeFromGraphicsFlag(uint32_t flag)
{
	if (HLData->getBuildPlatform() == Platform::P_PS3)
		return GetSizeFromFlag(flag, 0x1580);
	else // XBOX 360 / PC
		return GetSizeFromFlag(flag, 0x2000);
}
uint32_t CompileGTAV::GetFlagFromSize(int32_t size)
{
	for (int i = 0; i < 0x7FFFFFFF; i++)
	{
		if (GetSizeFromSystemFlag(i) == size)
			return i;
	}
	assert(false && "GetFlagFromSize: Size Not Found");
	return 0;
}
void CompileGTAV::fixFunctionCalls()
{
	for (auto CallInfo : CallLocations)
	{
		auto it = FuncLocations.find(CallInfo.Function);
		if (it == FuncLocations.end())
		{
			Utils::System::Throw("Function \"" + CallInfo.Function->getName() + "\" not found");
		}
		uint32_t pos = it->second;
		if (pos >= 0x1000000)
		{
			Utils::System::Throw("Function \"" + CallInfo.Function->getName() + "\" out of call range");//realistically this is never going to happen
		}
		switch (CallInfo.InstructionType)
		{
			case CallInstructionType::FuncLoc:
			ChangeInt24InCodePage(pos, CallInfo.CallLocation);
			*(CodePageData->getPositionAddress(CallInfo.CallLocation) - 1) = BaseOpcodes->PushI24;
			break;
			case CallInstructionType::Call:
			ChangeInt24InCodePage(pos, CallInfo.CallLocation);
			*(CodePageData->getPositionAddress(CallInfo.CallLocation) - 1) = BaseOpcodes->Call;
			break;
			default: assert(false && "Invalid Call Instruction"); break;
		}
	}
}
void CompileGTAV::fixFunctionJumps()
{
	for (auto jTableItem : jumpTableLocs)
	{
		auto it = LabelLocations.find(jTableItem.labelName);
		if (it == LabelLocations.end())
		{
			Throw("Jump table label '" + jTableItem.labelName + "' not found");
		}
		StringPageData->ChangeInt32(it->second.LabelLocation ^ jTableItem.xorVal, jTableItem.tableOffset);
	}
	jumpTableLocs.clear();
	JumpLocations.clear();
	LabelLocations.clear();
	SignedJumpLocationInc = UnsignedJumpLocationInc = 0;
}
#pragma endregion

#pragma region Opcode_Functions
void CompileGTAV::CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	// gta5 1 byte param/return, 2 byte call loc

	DoesOpcodeHaveRoom(4);

	AddOpcode(CallNative);
		if (returnCount > 3)
			Utils::System::Throw("Native Calls Can Only Have Up To Three Returns");
		if (paramCount > 63)
			Utils::System::Throw("Native Calls Can Only Have Up To Sixty Three Params");

		const uint32_t index = AddNative(hash);
		if (index >= 0xFFFF)
			Utils::System::Throw("Native Call Index out of bounds");

		AddInt8((paramCount << 2) | (returnCount & 0x3));
		AddInt16(index);
}
void CompileGTAV::Call()
{
	// gta5: 3 byte loc
	DoesOpcodeHaveRoom(4);
	AddOpcode(Call);
	CallLocations.push_back({ CodePageData->getTotalSize(), CallInstructionType::Call, DATA->getFunctionData() });
	AddInt24(0);
}
void CompileGTAV::PushString()
{
	PushInt(StringPageData->AddString(DATA->getString()));
	DoesOpcodeHaveRoom(1);
	AddOpcode(PushString);
}
void CompileGTAV::GetImmPStack()
{
	DoesOpcodeHaveRoom(1);
	AddOpcode(GetImmP);
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
void CompileGTAV::GoToStack()
{
	DoesOpcodeHaveRoom(5);
	AddOpcode(Function);
	AddInt8(0);
	AddInt16(2);
	AddInt8(0);
	DoesOpcodeHaveRoom(3);
	AddOpcode(Return);
	AddInt16(0);//cba adding byte 0 twice
}
void CompileGTAV::AddJumpTable()
{
	auto jumpTable = DATA->getJumpTable();
	auto pos = StringPageData->AddJumpTable(jumpTable->getItemCount());
	PushInt(pos);
	DoesOpcodeHaveRoom(1);
	AddOpcode(PushString);
	for (unsigned i = 0; i < jumpTable->getItemCount();i++)
	{
		jumpTableLocs.push_back({ pos, jumpTable->getJumpLocAsString(i), jumpTable->getXORValue() });
		pos += 4;
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
	AddInt32toBuff(CodePageData->getTotalSize());//code length
	AddInt32toBuff(HLData->getParameterCount());//script ParameterCount (this needs to be implemented)
	AddInt32toBuff(HLData->getStaticCount());//statics count
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
	AddInt32toBuff(StringPageData->getTotalSize());
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
	if (GetSpaceLeft(16384) < CodePageData->getPageCount() * 4)
		FillPageDynamic(16384);

	SavedOffsets.CodeBlocks = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + CodePageData->getPageCount() * 4, 0);
	Pad();

	//Write string page pointers
	
	if (StringPageData->getPageCountIgnoreEmpty())
	{
		if (GetSpaceLeft(16384) < StringPageData->getPageCountIgnoreEmpty() * 4)
			FillPageDynamic(16384);

		SavedOffsets.StringBlocks = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + StringPageData->getPageCountIgnoreEmpty() * 4, 0);
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
	if (StringPageData->getPageCountIgnoreEmpty())
	{
		SavedOffsets.StringPagePointers.resize(StringPageData->getPageCountIgnoreEmpty());
		for (uint32_t i = 0; i < StringPageData->getPageCountIgnoreEmpty() - 1; i++)
		{
			if (GetSpaceLeft(16384) < 16384)
				FillPageDynamic(16384);

			SavedOffsets.StringPagePointers[i] = BuildBuffer.size();

			BuildBuffer.resize(BuildBuffer.size() + 16384);
			memcpy(BuildBuffer.data() + BuildBuffer.size() - 16384, StringPageData->getPageAddress(i), 16384);

			Pad();
		}
	}
}
void CompileGTAV::WriteFinalStringPage()
{
	if (StringPageData->getPageCountIgnoreEmpty())
	{
		auto size = StringPageData->getLastPageSizeIgnoreEmpty();
		if (GetSpaceLeft(16384) < size){
			FillPageDynamic(16384);
		}
		SavedOffsets.StringPagePointers[StringPageData->getPageCountIgnoreEmpty() - 1] = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + StringPageData->getLastPageSizeIgnoreEmpty());
		memcpy(BuildBuffer.data() + BuildBuffer.size() - StringPageData->getLastPageSizeIgnoreEmpty(), StringPageData->getPageAddress(StringPageData->getPageCountIgnoreEmpty()-1), StringPageData->getLastPageSizeIgnoreEmpty());
		Pad();
	}
}
void CompileGTAV::XSCWrite(const char* path, bool AddRsc7Header)
{
	FilePadding = 0;
	ClearWriteVars();

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
		const vector<uint32_t> rsc7 =
		{
			Utils::Bitwise::SwapEndian(0x52534337u),//magic
			Utils::Bitwise::SwapEndian((uint32_t)ResourceType::ScriptContainer),//resourceType
			Utils::Bitwise::SwapEndian(GetFlagFromSize(BuildBuffer.size())),//systemFlag
			Utils::Bitwise::SwapEndian(0x90000000u)//graphicsFlag
		};

		fwrite(rsc7.data(), 1, 16, file);
	}

	fwrite(BuildBuffer.data(), 1, BuildBuffer.size(), file);
	fclose(file);
	#pragma endregion

}
#pragma endregion

#pragma region StringEnc
void CompileGTAV::BuildTablesCheckEnc()
{
	if (isStringEncrypted){
		auto randomEngine = default_random_engine(chrono::system_clock::now().time_since_epoch().count());
		__int64 stringTableXOR = ((__int64)randomEngine() << 32) | randomEngine();
		StringPageData->AddPadding(8);
		FunctionCount = 0;
		InstructionCount = 0;
		AddFunction(HLData->getFunctionFromIndex(FunctionCount), DisableFunctionNames);
		if (HLData->getFunctionFromIndex(FunctionCount)->getInstruction(0)->getKind() == OK_Nop){
			ParseGeneral(HLData->getFunctionFromIndex(FunctionCount)->getInstruction(0)->getKind());
			InstructionCount = 1;

		}
		CodePageData->reserveBytes(4);
		AddOpcode(Call);
		size_t entryCallLoc = CodePageData->getTotalSize();
		AddInt24(0);
		for (; InstructionCount < HLData->getFunctionFromIndex(FunctionCount)->getInstructionCount(); InstructionCount++)
		{
			ParseGeneral(HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)->getKind());
			CheckSignedJumps();
			CheckUnsignedJumps();
		}
		CheckLabels();
		fixFunctionJumps();

		for (FunctionCount = 1; FunctionCount < HLData->getFunctionCount(); FunctionCount++)
		{
			if (HLData->getFunctionFromIndex(FunctionCount)->IsUsed())
			{
				AddFunction(HLData->getFunctionFromIndex(FunctionCount), DisableFunctionNames);
				for (InstructionCount = 0; InstructionCount < HLData->getFunctionFromIndex(FunctionCount)->getInstructionCount(); InstructionCount++)
				{
					ParseGeneral(HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)->getKind());
					CheckSignedJumps();
					CheckUnsignedJumps();
				}
				CheckLabels();
				fixFunctionJumps();
			}
		}
		fixFunctionCalls();
		StringPageData->padAlign(8);
		addDecryptionFunction(stringTableXOR, entryCallLoc);

		for (size_t i = 0; i < StringPageData->getPageCount(); i++){
			size_t pageSize = (i == StringPageData->getPageCount() - 1) ? StringPageData->getLastPageSize() : 0x4000;
			__int64* ptr = (__int64*)StringPageData->getPageAddress(i);
			__int64* end = (__int64*)(StringPageData->getPageAddress(i) + pageSize);
			while (ptr < end){
				*ptr++ ^= stringTableXOR;
			}
		}
	}
	else{
		BuildTables();
	}
}
void CompileGTAV::addDecryptionFunction(__int64 xorValue, size_t entryCallLoc)
{
	CodePageData->reserveBytes(5);
	ChangeInt24InCodePage(CodePageData->getTotalSize(), entryCallLoc);
	AddOpcode(Function);
	AddInt8(0);
	AddInt16(7);
	AddInt8(0);//unused function name

	PushInt(0);

	CodePageData->reserveBytes(1);
	AddOpcode(PushString);

	CodePageData->reserveBytes(1);
	AddOpcode(pGet);

	CodePageData->reserveBytes(1);
	AddOpcode(Not);

	AddJump(CompileBase::JumpInstructionType::JumpFalse, "__decrypted_not_done");

	CodePageData->reserveBytes(3);
	AddOpcode(Return);
	AddInt16(0);

	AddLabel("__decrypted_not_done");

	PushInt(StringPageData->getTotalSize());

	CodePageData->reserveBytes(1);
	AddOpcode(Dup);
	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(2);

	AddImm(16383);
	PushInt(16384);

	CodePageData->reserveBytes(1);
	AddOpcode(Div);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(3);

	PushInt(0);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(4);

	AddLabel("__decryptedForBody");

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(4);

	MultImm(16384);
	CodePageData->reserveBytes(1);
	AddOpcode(PushString);

	CodePageData->reserveBytes(1);
	AddOpcode(Dup);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(4);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(3);

	AddImm(-1);
	AddJump(CompileBase::JumpInstructionType::JumpNE, "__decryptedCondFalse");

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(2);

	PushInt(16383);

	CodePageData->reserveBytes(1);
	AddOpcode(And);
	AddJump(CompileBase::JumpInstructionType::Jump, "__decryptedCondEnd");

	AddLabel("__decryptedCondFalse");
	PushInt(16384);
	AddLabel("__decryptedCondEnd");

	CodePageData->reserveBytes(1);
	AddOpcode(Add);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(6);

	AddLabel("__decryptedWhileBody");

	//decrypt lower 32 bits
	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(1);
	AddOpcode(pGet);

	PushInt(xorValue & 0xFFFFFFFF);
	CodePageData->reserveBytes(1);
	AddOpcode(Xor);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(1);
	AddOpcode(pSet);
	//decrypt higher 32 bits
	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(2);
	AddOpcode(GetImm1);
	AddInt8(1);

	PushInt(xorValue >> 32);
	CodePageData->reserveBytes(1);
	AddOpcode(Xor);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(2);
	AddOpcode(SetImm1);
	AddInt8(1);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);
	CodePageData->reserveBytes(2);
	AddOpcode(GetImmP1);
	AddInt8(2);

	CodePageData->reserveBytes(1);
	AddOpcode(Dup);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(6);

	AddJump(CompileBase::JumpInstructionType::JumpLT, "__decryptedWhileBody");

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(4);
	AddImm(1);
	CodePageData->reserveBytes(1);
	AddOpcode(Dup);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(4);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(3);

	AddJump(CompileBase::JumpInstructionType::JumpLT, "__decryptedForBody");

	CodePageData->reserveBytes(3);
	AddOpcode(Return);
	AddInt16(0);

	CheckSignedJumps();
	CheckUnsignedJumps();
	CheckLabels();
	fixFunctionJumps();
}
#pragma endregion

#pragma endregion

#pragma region GTAVPC

#pragma region Opcode_Functions
void CompileGTAVPC::addDecryptionFunction(__int64 xorValue, size_t entryCallLoc)
{
	CodePageData->reserveBytes(5);
	ChangeInt24InCodePage(CodePageData->getTotalSize(), entryCallLoc);
	AddOpcode(Function);
	AddInt8(0);
	AddInt16(7);
	AddInt8(0);//unused function name

	PushInt(0);

	CodePageData->reserveBytes(1);
	AddOpcode(PushString);

	CodePageData->reserveBytes(1);
	AddOpcode(pGet);

	CodePageData->reserveBytes(1);
	AddOpcode(Not);

	AddJump(CompileBase::JumpInstructionType::JumpFalse, "__decrypted_not_done");

	CodePageData->reserveBytes(3);
	AddOpcode(Return);
	AddInt16(0);

	AddLabel("__decrypted_not_done");

	PushInt(StringPageData->getTotalSize());

	CodePageData->reserveBytes(1);
	AddOpcode(Dup);
	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(2);

	AddImm(16383);
	PushInt(16384);

	CodePageData->reserveBytes(1);
	AddOpcode(Div);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(3);

	PushInt(0);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(4);

	AddLabel("__decryptedForBody");

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(4);

	MultImm(16384);
	CodePageData->reserveBytes(1);
	AddOpcode(PushString);

	CodePageData->reserveBytes(1);
	AddOpcode(Dup);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(4);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(3);

	AddImm(-1);
	AddJump(CompileBase::JumpInstructionType::JumpNE, "__decryptedCondFalse");

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(2);

	PushInt(16383);

	CodePageData->reserveBytes(1);
	AddOpcode(And);
	AddJump(CompileBase::JumpInstructionType::Jump, "__decryptedCondEnd");

	AddLabel("__decryptedCondFalse");
	PushInt(16384);
	AddLabel("__decryptedCondEnd");

	CodePageData->reserveBytes(1);
	AddOpcode(Add);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(6);

	AddLabel("__decryptedWhileBody");

	//decrypt lower 32 bits
	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(1);
	AddOpcode(pGet);

	PushInt(xorValue & 0xFFFFFFFF);
	CodePageData->reserveBytes(1);
	AddOpcode(Xor);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(1);
	AddOpcode(pSet);
	//decrypt higher 32 bits
	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);
	AddImm(4);

	CodePageData->reserveBytes(1);
	AddOpcode(pGet);

	PushInt(xorValue >> 32);
	CodePageData->reserveBytes(1);
	AddOpcode(Xor);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);
	AddImm(4);

	CodePageData->reserveBytes(1);
	AddOpcode(pSet);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(5);
	CodePageData->reserveBytes(2);
	AddOpcode(GetImmP1);
	AddInt8(1);

	CodePageData->reserveBytes(1);
	AddOpcode(Dup);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(5);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(6);

	AddJump(CompileBase::JumpInstructionType::JumpLT, "__decryptedWhileBody");

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(4);
	AddImm(1);
	CodePageData->reserveBytes(1);
	AddOpcode(Dup);

	CodePageData->reserveBytes(2);
	AddOpcode(SetFrame1);
	AddInt8(4);

	CodePageData->reserveBytes(2);
	AddOpcode(GetFrame1);
	AddInt8(3);

	AddJump(CompileBase::JumpInstructionType::JumpLT, "__decryptedForBody");

	CodePageData->reserveBytes(3);
	AddOpcode(Return);
	AddInt16(0);

	CheckSignedJumps();
	CheckUnsignedJumps();
	CheckLabels();
	fixFunctionJumps();
}
void CompileGTAVPC::CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	DoesOpcodeHaveRoom(4);

	AddOpcode(CallNative);
	if (returnCount > 3)
		Utils::System::Throw("Native Calls Can Only Have Three Returns");
	if (paramCount > 63)
		Utils::System::Throw("Native Calls Can Only Have Up To Sixty Three Params");

	const uint32_t index = AddNative(hash);
	if (index >= 0xFFFF)
		Utils::System::Throw("Native Call Index out of bounds");

	AddInt8((paramCount << 2) | (returnCount & 0x3));
	AddInt16(Utils::Bitwise::SwapEndian((uint16_t)index));
}
#pragma endregion

#pragma region Write_Functions
void CompileGTAVPC::WriteHeader()
{
	headerLocation = BuildBuffer.size();
	
	AddInt64toBuff(0x1405A9E0D);//page base
	AddInt64toBuff(0); //Unk1 ptr
	AddInt64toBuff(0); //codeBlocksListOffsetPtr
	AddInt32toBuff(0xB0AC45A4);//unk2
	AddInt32toBuff(CodePageData->getTotalSize());//code length
	AddInt32toBuff(HLData->getParameterCount());//script ParameterCount (this needs to be implemented)
	AddInt32toBuff(HLData->getStaticCount());//statics count
	AddInt32toBuff(0);//GlobalsSize
	AddInt32toBuff(NativeHashMap.size());//natives count
	AddInt64toBuff(0); //Statics offset
	AddInt64toBuff(0); //Globals ptr, stay 0
	AddInt64toBuff(0); //native offset
	AddInt64toBuff(0);//Unk3
	AddInt64toBuff(0);//Unk4
	AddInt32toBuff(Utils::Hashing::Joaat(HLData->getScriptName()));
	AddInt32toBuff(1);//Unk5 typically 1
	AddInt64toBuff(0); //script name offset
	AddInt64toBuff(0); //strings offset
	AddInt32toBuff(StringPageData->getTotalSize());
	AddInt32toBuff(0);//Unk6
	AddInt64toBuff(0);//unk7

	 //no need to pad as its divisible by 16
}
void CompileGTAVPC::WritePointers()
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
	if (GetSpaceLeft(16384) < CodePageData->getPageCount() * 4)
		FillPageDynamic(16384);

	SavedOffsets.CodeBlocks = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + CodePageData->getPageCount() * 8, 0);
	Pad();

	//Write string page pointers

	if (StringPageData->getPageCountIgnoreEmpty())
	{
		if (GetSpaceLeft(16384) < StringPageData->getPageCountIgnoreEmpty() * 8)
			FillPageDynamic(16384);

		SavedOffsets.StringBlocks = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + StringPageData->getPageCountIgnoreEmpty() * 8, 0);
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
	BuildBuffer.resize(BuildBuffer.size() + 24);
	*(BuildBuffer.data() + BuildBuffer.size() - 24 + 8) = 1;

	FillPageDynamic(16384 / 2);
}
void CompileGTAVPC::WriteNatives()
{
	if (NativeHashMap.size() > 0)
	{
		const size_t nativeByteSize = NativeHashMap.size() * 8;

		if (GetSpaceLeft(16384) < nativeByteSize)
			FillPageDynamic(16384);

		SavedOffsets.Natives = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + nativeByteSize);
		for (unordered_map<uint64_t, uint32_t>::iterator it = NativeHashMap.begin(); it != NativeHashMap.end(); it++)
		{
			*(uint64_t*)(BuildBuffer.data() + SavedOffsets.Natives + it->second * 8) = _rotr64(nativeTranslation.Translate(it->first), it->second + CodePageData->getTotalSize());
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
void CompileGTAVPC::WriteStatics()
{

	if (HLData->getStaticCount() > 0)
	{
		const size_t staticByteSize = HLData->getStaticCount() * 8;

		if (GetSpaceLeft(16384) < staticByteSize)
			FillPageDynamic(16384);

		SavedOffsets.Statics = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + staticByteSize);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - staticByteSize, HLData->getNewStaticData(), staticByteSize);

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
void CompileGTAVPC::YSCWrite(const char* path, bool AddRsc7Header)
{
	FilePadding = 0;
	ClearWriteVars();

	WriteHeader();
	Write16384CodePages();
	WriteFinalCodePage();
	Write16384StringPages();
	WriteFinalStringPage();
	WriteNatives();
	WriteStatics();
	WritePointers();

	#pragma region Fix_header_and_other_pointers
	ChangeInt64inBuff(IntToPointerInt(SavedOffsets.Unk1), headerLocation + 8);
	ChangeInt64inBuff(IntToPointerInt(SavedOffsets.CodeBlocks), headerLocation + 16);
	ChangeInt64inBuff(IntToPointerInt(SavedOffsets.Statics), headerLocation + 48);
	ChangeInt64inBuff(IntToPointerInt(SavedOffsets.Natives), headerLocation + 64);
	ChangeInt64inBuff(IntToPointerInt(SavedOffsets.ScriptName), headerLocation + 96);
	ChangeInt64inBuff(IntToPointerInt(SavedOffsets.StringBlocks), headerLocation + 104);

	for (uint32_t i = 0; i < SavedOffsets.CodePagePointers.size(); i++)
		ChangeInt64inBuff(IntToPointerInt(SavedOffsets.CodePagePointers[i]), SavedOffsets.CodeBlocks + (i * 8));
	for (uint32_t i = 0; i < SavedOffsets.StringPagePointers.size(); i++)
		ChangeInt64inBuff(IntToPointerInt(SavedOffsets.StringPagePointers[i]), SavedOffsets.StringBlocks + (i * 8));
	#pragma endregion

	FILE* file = fopen(path, "wb");

	#pragma region Write_File
	if (AddRsc7Header)
	{
		const vector<uint32_t> rsc7 =
		{
			Utils::Bitwise::SwapEndian(0x52534337u),//magic
			Utils::Bitwise::SwapEndian((uint32_t)ResourceType::ScriptContainer),//resourceType
			Utils::Bitwise::SwapEndian(GetFlagFromSize(BuildBuffer.size())),//systemFlag
			Utils::Bitwise::SwapEndian(0x90000000u)//graphicsFlag
		};

		fwrite(rsc7.data(), 1, 16, file);
	}

	fwrite(BuildBuffer.data(), 1, BuildBuffer.size(), file);
	fclose(file);
	#pragma endregion

}
#pragma endregion

#pragma endregion