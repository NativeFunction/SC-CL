#include "Compiler.h"


void CompileBase::PushInt()
	{
		int value = DATA->getInt();

		if (value >= -1 && value <= 7) {
			switch (value)
			{
				case -1: AddByte(BaseOpcodes->Push_Neg1); break;
				case 0: AddByte(BaseOpcodes->Push_0); break;
				case 1: AddByte(BaseOpcodes->Push_1); break;
				case 2: AddByte(BaseOpcodes->Push_2); break;
				case 3: AddByte(BaseOpcodes->Push_3); break;
				case 4: AddByte(BaseOpcodes->Push_4); break;
				case 5: AddByte(BaseOpcodes->Push_5); break;
				case 6: AddByte(BaseOpcodes->Push_6); break;
				case 7: AddByte(BaseOpcodes->Push_7); break;
				default: assert(false && "Invalid Push Opcode");
			}
		}
		else if (value > 0 && value < 256)
		{
			AddByte(BaseOpcodes->PushB);
			AddByte(value);
		}
		else if (value >= -32768 && value <= 32767)
		{
			AddByte(BaseOpcodes->PushS);
			AddShort(value);
		}
		else if (value > 0 && value < 16777216)
		{
			AddByte(BaseOpcodes->PushI24);
			AddTriByte(value);
		}
		else
		{
			AddByte(BaseOpcodes->Push);
			AddInt(value);
		}


	}

void CompileBase::ParseGeneral(OpcodeKind OK)
{
	switch (OK)
	{
		case OK_Nop:		AddOpcode(Nop); break;
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
		case OK_Native:		CallNative(); break;//callnative def| gta5 2 byte call loc, 1 byte param/return | rdr 2 byte call loc | gta4: 1 byte param, 1 byte return, 4 byte hash
		case OK_Return:		Return(); break;//rdr needs to override
		case OK_PGet:		AddOpcode(pGet); break;
		case OK_PSet:		AddOpcode(pSet); break;
		case OK_PeekSet:	AddOpcode(pPeekSet); break;
		case OK_ToStack:	AddOpcode(ToStack); break;
		case OK_FromStack:	AddOpcode(FromStack); break;

		case OK_GetArrayP:	break;
		case OK_GetArray:	break;
		case OK_SetArray:	break;
		case OK_GetFrameP:	break;
		case OK_GetFrame:	break;
		case OK_SetFrame:	break;
		case OK_GetStaticP:	break;
		case OK_GetStatic:	break;
		case OK_SetStatic:	break;
		case OK_GetGlobalP:	break;
		case OK_GetGlobal:	break;
		case OK_SetGlobal:	break;
		case OK_AddImm:	break;
		case OK_MultImm:	break;
		case OK_FAddImm:	break;
		case OK_FMultImm:	break;
		case OK_GetImmP:	break;
		case OK_GetImm:	break;
		case OK_SetImm:	break;


		case OK_Call:		Call();  break;//call def| gta4: 4 byte loc | gta5: 3 byte loc | rdr: 2 byte loc (loc or'ed)
		case OK_Jump:		AddJump(JumpType::Jump, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpFalse:	AddJump(JumpType::JumpFalse, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpEQ:		AddJump(JumpType::JumpEQ, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpNE:		AddJump(JumpType::JumpNE, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpGT:		AddJump(JumpType::JumpGT, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpGE:		AddJump(JumpType::JumpGE, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpLT:		AddJump(JumpType::JumpLT, DATA->getString()); break;//gta 4 needs to override
		case OK_JumpLE:		AddJump(JumpType::JumpLE, DATA->getString()); break;//gta 4 needs to override

		case OK_Switch:		break;

		case OK_PushString:	PushString(); break;//gta5 needs to override
		case OK_StrCopy:	StrCopy(); break;//gta4 needs to override
		case OK_ItoS:		ItoS(); break;//gta4 needs to override
		case OK_StrAdd:		StrAdd(); break;//gta4 needs to override
		case OK_StrAddI:	StrAddI(); break;//gta4 needs to override
		case OK_MemCpy:		MemCopy(); break;//gta4 needs to override
		case OK_PCall:		pCall(); break;//gta4 needs to override as error
		case OK_Label:		AddLabel(DATA->getString()); break;
		case OK_LabelLoc:	AddOpcode(Push); AddInt(GetLabel(DATA->getString())); break;
		case OK_ShiftLeft:	AddOpcode(CallNative); AddInt(JoaatConst("shift_left")); AddByte(2); AddByte(1); break;
		case OK_ShiftRight:	AddOpcode(CallNative); AddInt(JoaatConst("shift_right")); AddByte(2); AddByte(1); break;
		case OK_GetHash:	GetHash(); break;//gta5 needs to override
	}
}

