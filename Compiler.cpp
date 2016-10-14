#include "Compiler.h"


#pragma region Base
void CompileBase::ParseGeneral(const OpcodeKind OK)
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
}
void CompileBase::AddJump(const JumpInstructionType type, const string label)
{
	switch (type)
	{
		case JumpInstructionType::Jump:		DoesOpcodeHaveRoom(3); AddOpcode(Jump); AddJumpLoc(type, label); break;
		case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(3); AddOpcode(JumpFalse); AddJumpLoc(type, label); break;
		case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpNE); AddJumpLoc(type, label); break;
		case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(3); AddOpcode(JumpEQ); AddJumpLoc(type, label); break;
		case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLE); AddJumpLoc(type, label); break;
		case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLT); AddJumpLoc(type, label); break;
		case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGE); AddJumpLoc(type, label); break;
		case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGT); AddJumpLoc(type, label); break;
		case JumpInstructionType::Switch:		AddJumpLoc(type, label); break;
		case JumpInstructionType::LabelLoc:	DoesOpcodeHaveRoom(4); AddOpcode(PushI24); AddJumpLoc(type, label); break;
		default: assert(false && "Invalid JumpInstructionType");
	}
}

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

#pragma region RDR

void CompileRDR::CallNative(const uint32_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	// rdr 2 byte call loc based on index
	DoesOpcodeHaveRoom(3);

	AddOpcode(CallNative);
	if (hash == -1)
	{
		if(DATA->getNative()->getReturnCount() > 1)
			Throw("Native Calls Can Only Have One Return");

		const uint32_t index = NativeHashMap.size();
		if (index >= 1024)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
		AddInt16(SetNewIndex(index, DATA->getNative()->getParamCount(), DATA->getNative()->getReturnCount() == 1));
	}
	else
	{
		if (returnCount > 1)
			Throw("Native Calls Can Only Have One Return");

		const uint32_t index = NativeHashMap.size();
		if (index >= 1024)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
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
	DoesOpcodeHaveRoom(3);
	CallLocations.push_back({ CodePageData.size(), CallInstructionType::Call, DATA->getString()});
	AddInt24(0);
}
void CompileRDR::GetImm()
{
	const uint32_t value = DATA->getInt() * 4;
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
		PushInt(value);
		AddOpcode(Add);
		AddOpcode(pGet);
	}
}
void CompileRDR::SetImm()
{
	const uint32_t value = DATA->getInt() * 4;
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
		PushInt(value);
		AddOpcode(Add);
		AddOpcode(pSet);
	}
}

#pragma endregion

#pragma region GTAV
const uint32_t CompileGTAV::AddStringToStringPage(const string str)
{
	const uint32_t len = str.length();
	const uint32_t pos = StringPageData.size();

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

void CompileGTAV::CallNative(const uint32_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	// gta5 1 byte param/return, 2 byte call loc

	DoesOpcodeHaveRoom(4);

	AddOpcode(CallNative);
	if (hash == -1)
	{
		if (DATA->getNative()->getReturnCount() > 3)
			Throw("Native Calls Can Only Have Three Returns");

		const uint32_t index = NativeHashMap.size();
		if (index > 0xFFFF)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
		AddInt8( (DATA->getNative()->getParamCount() << 2) | (DATA->getNative()->getReturnCount() & 0x3));
		AddInt16(index);
	}
	else
	{
		if (returnCount > 3)
			Throw("Native Calls Can Only Have Three Returns");

		const uint32_t index = NativeHashMap.size();
		if (index > 0xFFFF)
			Throw("Native Call Index out of bounds");

		AddNative(hash);
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
void CompileGTAV::GetImm()
{
	const uint32_t value = DATA->getInt();
	if (value <= 0xFF)
	{
		DoesOpcodeHaveRoom(2);
		AddOpcode(GetImm1);
		AddInt8(value);
	}
	else if (value <= 0xFFFF)
	{
		DoesOpcodeHaveRoom(3);
		AddOpcode(GetImm2);
		AddInt16(value);
	}
	else
	{
		PushInt(value * 4);
		AddOpcode(Add);
		AddOpcode(pGet);
	}
}
void CompileGTAV::SetImm()
{
	const uint32_t value = DATA->getInt();
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
		PushInt(value * 4);
		AddOpcode(Add);
		AddOpcode(pSet);
	}
}

#pragma endregion
