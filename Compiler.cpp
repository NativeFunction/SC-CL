#include "Compiler.h"


#pragma region Base
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
		case OK_Native:		CallNative(); break;//callnative def| gta5 1 byte param/return, 2 byte call loc | rdr 2 byte call loc | gta4: 1 byte param, 1 byte return, 4 byte hash
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
		case OK_LabelLoc:	AddOpcode(Push); AddInt32(GetLabel(DATA->getString())); break;
		case OK_ShiftLeft:	CallNative(JoaatConst("shift_left"), 2, 1); break;
		case OK_ShiftRight:	CallNative(JoaatConst("shift_left"), 2, 1); break;
		case OK_GetHash:	GetHash(); break;//gta5 needs to override
	}
}


void CompileBase::PushInt(bool isLiteral, int32_t Literal)
{
	int32_t value = isLiteral ? Literal : DATA->getInt();

	if (value >= -1 && value <= 7) {
		switch (value)
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
	else if (value > 0 && value < 256)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(PushB);
		AddInt8(value);
	}
	else if (value >= -32768 && value <= 32767)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(PushS);
		AddInt16(value);
	}
	else if (value > 0 && value < 16777216)
	{
		DoesOpcodeHaveRoom(4);
		AddOpcode(PushI24);
		AddInt24(value);
	}
	else
	{
		DoesOpcodeHaveRoom(5);
		AddOpcode(Push);
		AddInt32(value);
	}


}
void CompileBase::PushFloat()
{
	switch (DATA->getInt())
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
		default: DoesOpcodeHaveRoom(5); AddOpcode(PushF); AddFloat(DATA->getFloat());
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
void CompileBase::PushString()
{
	DoesOpcodeHaveRoom(DATA->getString().size() + 3);//opcode, len, null terminator
	AddOpcode(PushString);
	AddInt8(DATA->getString().size() + 1);//str size + null terminator
	AddString(DATA->getString());
}
void CompileBase::Switch(){


	//DoesOpcodeHaveRoom(DATA->getString().size() + 2);//opcode, case count
	AddOpcode(Switch);

	SwitchCaseStorage* sCase = DATA->storage.switchCase;

	uint32_t CaseCount = CodePageData.size();
	AddInt8(0);

	assert(sCase && "Empty Switch Statement");
	uint32_t i = 0;
	while (sCase->hasNextCase())
	{
		sCase = sCase->getNextCase();
		AddInt32(sCase->getCase());
		AddJump(JumpType::Switch, sCase->getLoc());//for gta4 switches override this
		i++;
	}
	CodePageData[CaseCount] = i;
}
#pragma endregion

#pragma region RDR

void CompileRDR::CallNative(uint32_t hash, uint8_t paramCount, uint8_t returnCount)
{
	// rdr 2 byte call loc based on index
	DoesOpcodeHaveRoom(3);

	AddOpcode(CallNative);
	if (hash == -1)
	{
		if(DATA->storage.native->getReturnCount() > 1)
			Throw("Native Calls Can Only Have One Return");

		uint32_t index = NativeHashMap.size();
		if (index >= 1024)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
		AddInt16(SetNewIndex(index, DATA->storage.native->getParamCount(), DATA->storage.native->getReturnCount() == 1));
	}
	else
	{
		if (returnCount > 1)
			Throw("Native Calls Can Only Have One Return");

		uint32_t index = NativeHashMap.size();
		if (index >= 1024)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
		AddInt16(SetNewIndex(index, paramCount, returnCount == 1));
	}
}

#pragma endregion

#pragma region GTAV
uint32_t CompileGTAV::AddStringToStringPage(string str)
{
	uint32_t len = str.length();
	uint32_t pos = StringPageData.size();

	//if string is in table
	for (uint32_t i = 0; i < StringPageDataIndexing.size(); i++)
	{
		if (StringPageDataIndexing[i].len == len && strcmp((char*)(StringPageData.data() + StringPageDataIndexing[i].index), str.c_str()) == 0)
			return StringPageDataIndexing[i].index;
	}

	if ((pos + len + 1) % 16384 < pos % 16384)
		StringPageData.resize(16384 - (pos % 16384) + pos);

	StringPageDataIndexing.push_back({ StringPageData.size(), len });
	StringPageData.resize(pos + len + 1);
	memcpy(StringPageData.data() + pos, str.data(), len + 1);
	return pos;
}

void CompileGTAV::CallNative(uint32_t hash, uint8_t paramCount, uint8_t returnCount)
{
	// gta5 1 byte param/return, 2 byte call loc

	DoesOpcodeHaveRoom(4);

	AddOpcode(CallNative);
	if (hash == -1)
	{
		if (DATA->storage.native->getReturnCount() > 3)
			Throw("Native Calls Can Only Have Three Returns");

		uint32_t index = NativeHashMap.size();
		if (index > 0xFFFF)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
		AddInt8( (DATA->storage.native->getParamCount() << 2) | (DATA->storage.native->getReturnCount() & 0x3));
		AddInt16(index);
	}
	else
	{
		if (returnCount > 3)
			Throw("Native Calls Can Only Have Three Returns");

		uint32_t index = NativeHashMap.size();
		if (index > 0xFFFF)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
		AddInt8((paramCount << 2) | (returnCount & 0x3));
		AddInt16(index);
	}
}
void CompileGTAV::PushString()
{
	PushInt(true, AddStringToStringPage(DATA->getString()));
	AddOpcode(PushString);
}


#pragma endregion
