#include "CompilePC.h"

using namespace std;
using namespace Utils::System;

template <typename INT>
constexpr INT rol(INT val, uint32_t rot) {
	rot &= (sizeof(INT)*CHAR_BIT - 1);
	return (val << (rot & (sizeof(INT)*CHAR_BIT - 1))) | (val >> (sizeof(INT)*CHAR_BIT - (rot & (sizeof(INT)*CHAR_BIT - 1))));
}

template <typename INT>
constexpr INT ror(INT val, uint32_t rot) {
	return (val >> (rot & (sizeof(INT)*CHAR_BIT - 1))) | (val << (sizeof(INT)*CHAR_BIT - (rot & (sizeof(INT)*CHAR_BIT - 1))));
}

void CompileGTAPC::AddLabel(const std::string label)
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

					if (JumpLocations[it->second.JumpIndexes[i]].InstructionType == JumpInstructionType::Switch && (offset < 0 || offset > 65535))
						Utils::System::Throw("Switch label \"" + label + "\" out of jump range");
					else if (offset < -32768 || offset > 32767)
						Utils::System::Throw("Jump label \"" + label + "\" out of jump range");

					*(int16_t*)(CodePageData.data() + JumpLocations[it->second.JumpIndexes[i]].JumpLocation) = (int16_t)offset;
					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
				else
				{
					if (it->second.LabelLocation >= 0x1000000)
						Utils::System::Throw("Get label loc \"" + label + "\" out of jump range");

					*(uint32_t*)(CodePageData.data() - 1 + JumpLocations[it->second.JumpIndexes[i]].JumpLocation) = it->second.LabelLocation << 8 | BaseOpcodes->PushI24;
					JumpLocations[it->second.JumpIndexes[i]].isSet = true;
				}
			}
		}
	}
	else
		Utils::System::Throw("Cannot add label. Label \"" + label + "\" already exists.");
}

void CompileGTAPC::AddJump(const JumpInstructionType type, const std::string label)
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
		int32_t offset = it->second.LabelLocation - CodePageData.size() - 3;//estimate
		assert(offset < 0);

		if (offset >= -32768 + 3 + 2)//3 for opcode size, 2 for possible DoesOpcodeHaveRoom padding
		{
			switch (type)
			{

				case JumpInstructionType::Jump:			DoesOpcodeHaveRoom(3); AddOpcode(Jump); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
				case JumpInstructionType::JumpFalse:	DoesOpcodeHaveRoom(3); AddOpcode(JumpFalse); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
				case JumpInstructionType::JumpNE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpNE); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
				case JumpInstructionType::JumpEQ:		DoesOpcodeHaveRoom(3); AddOpcode(JumpEQ); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
				case JumpInstructionType::JumpLE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLE); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
				case JumpInstructionType::JumpLT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpLT); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
				case JumpInstructionType::JumpGE:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGE); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
				case JumpInstructionType::JumpGT:		DoesOpcodeHaveRoom(3); AddOpcode(JumpGT); AddInt16(it->second.LabelLocation - CodePageData.size() - 2); break;
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

CompileGTAPC::JumpLabelData CompileGTAPC::AddSwitchJump(const JumpInstructionType type, const std::string label)
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
		assert(it->second.LabelLocation - CodePageData.size() - 2 >= 0);

		AddInt16(0);

		//have to add a jump forward to jump backward
		return{ { BuildBuffer.size() - 2, type, label, false }, it->second };
	}

}

void CompileGTAPC::CheckSignedJumps()
{
	if (!FindNextSignedJumpLocation())
		return;

	int32_t offset = (CodePageData.size() + 3) - JumpLocations[SignedJumpLocationInc].JumpLocation - 2;
	if (offset > 31135)//to make this easier im going on the assumption that the max size of an opcode is 1532 (nothing can be added that is 1632) 100 bytes of leeway
	{
		//jump to jump code

		DoesOpcodeHaveRoom(3);
		AddOpcode(Jump);
		uint32_t JumpOverOffset = CodePageData.size();
		AddInt16(0);

		//need to update jumps of same label that are out of bounds to jumps that are already added. instead of adding another jump to jump.

		offset = CodePageData.size() - JumpLocations[SignedJumpLocationInc].JumpLocation - 2;

		do
		{
			if (offset > 32767)
				Throw("Jump label \"" + JumpLocations[SignedJumpLocationInc].Label + "\" out of jump range on jump to jump " + to_string(offset));

			*(int16_t*)(CodePageData.data() + JumpLocations[SignedJumpLocationInc].JumpLocation) = (int16_t)offset;
			JumpLocations[SignedJumpLocationInc].isSet = true;
			cout << "fixed label " + JumpLocations[SignedJumpLocationInc].Label << " at index " << SignedJumpLocationInc << endl;

			DoesOpcodeHaveRoom(3);
			AddOpcode(Jump);
			AddJumpLoc(JumpInstructionType::Jump, JumpLocations[SignedJumpLocationInc].Label);

			if (!FindNextSignedJumpLocation())
				return;

			offset = CodePageData.size() - JumpLocations[SignedJumpLocationInc].JumpLocation - 2;
		} while (offset > 30000);


		//set jump over jump
		*(int16_t*)(CodePageData.data() + JumpOverOffset) = (int16_t)(CodePageData.size() - JumpOverOffset - 2);
	}
}

void CompileGTAPC::CheckUnsignedJumps()
{
	if (!FindNextUnsignedJumpLocation())
		return;

	int32_t offset = (CodePageData.size() + 3) - JumpLocations[UnsignedJumpLocationInc].JumpLocation - 2;
	if (offset > 63903)//to make this easier im going on the assumption that the max size of an opcode is 1532 (nothing can be added that is 1632) 10 bytes of leeway
	{
		//jump to jump code

		DoesOpcodeHaveRoom(3);
		AddOpcode(Jump);
		uint32_t JumpOverOffset = CodePageData.size();
		AddInt16(0);

		//need to update jumps of same label that are out of bounds to jumps that are already added. instead of adding another jump to jump.

		offset = CodePageData.size() - JumpLocations[UnsignedJumpLocationInc].JumpLocation - 2;

		do
		{
			if (offset > 65535)
				Throw("Jump label \"" + JumpLocations[UnsignedJumpLocationInc].Label + "\" out of jump range on jump to jump " + to_string(offset));

			*(int16_t*)(CodePageData.data() + JumpLocations[UnsignedJumpLocationInc].JumpLocation) = (int16_t)offset;
			JumpLocations[UnsignedJumpLocationInc].isSet = true;
			cout << "fixed label " + JumpLocations[UnsignedJumpLocationInc].Label << " at index " << UnsignedJumpLocationInc << endl;

			DoesOpcodeHaveRoom(3);
			AddOpcode(Jump);
			AddJumpLoc(JumpInstructionType::Jump, JumpLocations[UnsignedJumpLocationInc].Label);

			if (!FindNextUnsignedJumpLocation())
				return;

			offset = CodePageData.size() - JumpLocations[UnsignedJumpLocationInc].JumpLocation - 2;
		} while (offset > 63903);


		//set jump over jump
		*(int16_t*)(CodePageData.data() + JumpOverOffset) = (int16_t)(CodePageData.size() - JumpOverOffset - 2);
	}
}

void CompileGTAPC::PushInt(const int32_t Literal)
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

void CompileGTAPC::PushBytes()
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

void CompileGTAPC::PushFloat(const float Literal)
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

void CompileGTAPC::PushString()
{
	PushInt(AddStringToStringPage(DATA->getString()));
	AddOpcode(PushString);
}

void CompileGTAPC::CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount)
{
	DoesOpcodeHaveRoom(4);

	AddOpcode(CallNative);
	if (hash == -1)
	{
		if (DATA->getNative()->getReturnCount() > 3)
			Throw("Native Calls Can Only Have Three Returns");

		const uint32_t index = AddNative(DATA->getNative()->getHash());
		if (index >= 0xFFFF)
			Throw("Native Call Index out of bounds");

		AddInt8((DATA->getNative()->getParamCount() << 2) | (DATA->getNative()->getReturnCount() & 0x3));
		AddInt16(Utils::Bitwise::SwapEndian((uint16_t)index));
	}
	else
	{
		if (returnCount > 3)
			Utils::System::Throw("Native Calls Can Only Have Three Returns");

		const uint32_t index = AddNative(hash);
		if (index >= 0xFFFF)
			Utils::System::Throw("Native Call Index out of bounds");

		AddInt8((paramCount << 2) | (returnCount & 0x3));
		AddInt16(Utils::Bitwise::SwapEndian((uint16_t)index));
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
assert(DATA->getStaticData()->isUsed() && "unused static referenced, this shouldn't happen");\
const uint32_t value = DATA->getStaticData()->getIndex();\
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

void CompileGTAPC::GetArrayP()
{
	AddOpcodeB_1or2(GetArrayP, "GetArrayP index too high");
}
void CompileGTAPC::GetArray()
{
	AddOpcodeB_1or2(GetArray, "GetArray index too high");
}
void CompileGTAPC::SetArray()
{
	AddOpcodeB_1or2(SetArray, "SetArray index too high");
}
void CompileGTAPC::GetFrameP()
{
	AddOpcodeB_1or2(GetFrameP, "GetFrameP index too high");
}
void CompileGTAPC::GetFrame()
{
	AddOpcodeB_1or2(GetFrame, "GetFrame index too high");
}
void CompileGTAPC::SetFrame()
{
	AddOpcodeB_1or2(SetFrame, "SetFrame index too high");
}
void CompileGTAPC::GetStaticP()
{
	AddOpcodeStatic(GetStaticP, "GetStaticP index too high");
}
void CompileGTAPC::GetStatic()
{
	AddOpcodeStatic(GetStatic, "GetStatic index too high");
}
void CompileGTAPC::SetStatic()
{
	AddOpcodeStatic(SetStatic, "SetStatic index too high");
}
void CompileGTAPC::GetGlobalP()
{
	AddOpcodeB_2or3(GetGlobalP, "GetGlobalP index too high");
}
void CompileGTAPC::GetGlobal()
{
	AddOpcodeB_2or3(GetGlobal, "GetGlobal index too high");
}
void CompileGTAPC::SetGlobal()
{
	AddOpcodeB_2or3(SetGlobal, "SetGlobal index too high");
}

void CompileGTAPC::GetImmP()
{
	AddOpcodeB_1or2(GetImmP, "GetImmP index too high");
}

void CompileGTAPC::GetImm()
{
	AddOpcodeB_1or2(GetImm, "GetImm index too high");
}

void CompileGTAPC::SetImm()
{
	AddOpcodeB_1or2(SetImm, "SetImm index too high");
}

void CompileGTAPC::GoToStack()
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

void CompileGTAPC::AddJumpTable()
{
	auto jumpTable = DATA->getJumpTable();
	const uint32_t len = jumpTable->getByteSize() + 1;
	uint32_t pos = StringPageData.size();

	if ((pos + len) % 16384 < pos % 16384)
	{
		StringPageData.resize(16384 - (pos % 16384) + pos);
		pos = StringPageData.size();
	}
	PushInt(pos);
	AddOpcode(PushString);
	StringPageData.resize(pos + len, 0);
	for (unsigned i = 0; i < jumpTable->getItemCount(); i++)
	{
		jumpTableLocs.push_back({ pos, jumpTable->getJumpLocAsString(i) });
		pos += 4;
	}
}

void CompileGTAPC::Call()
{
	DoesOpcodeHaveRoom(4);
	AddOpcode(Call);
	CallLocations.push_back({ CodePageData.size(), CallInstructionType::Call, DATA->getFunctionData() });
	AddInt24(0);
}

void CompileGTAPC::AddFuncLoc(const FunctionData * function)
{
	DoesOpcodeHaveRoom(4);
	AddOpcode(PushI24);
	CallLocations.push_back({ CodePageData.size(), CallInstructionType::FuncLoc, function });
	AddInt24(0);
}

void CompileGTAPC::Switch()
{
	const SwitchStorage* switchStore = DATA->getSwitch();
	const uint32_t caseCount = switchStore->getCount();
	DoesOpcodeHaveRoom(caseCount * 6 + 2);//opcode, case count

	AddOpcode(Switch);
	AddInt8(caseCount);

	if (caseCount)
	{
		vector<JumpLabelData> CasesToBeFixed;
		const SwitchCaseStorage* sCase = switchStore->getFirstCase();

		AddInt32(sCase->getCaseValue());
		JumpLabelData jumpLabelData = AddSwitchJump(JumpInstructionType::Switch, sCase->getCaseLocation());
		if (jumpLabelData.JumpInfo.JumpLocation)
			CasesToBeFixed.push_back(jumpLabelData);

		while (sCase->hasNextCase())
		{
			sCase = sCase->getNextCase();
			AddInt32(sCase->getCaseValue());
			JumpLabelData jumpLabelData = AddSwitchJump(JumpInstructionType::Switch, sCase->getCaseLocation());
			if (jumpLabelData.JumpInfo.JumpLocation)
				CasesToBeFixed.push_back(jumpLabelData);
		}
		//start jump table to fix jumps
		if (CasesToBeFixed.size() > 0)
		{

			DoesOpcodeHaveRoom(3);
			AddOpcode(Jump);
			uint32_t JumpOverOffset = CodePageData.size();
			AddInt16(0);

			//need to update jumps of same label that are out of bounds to jumps that are already added. instead of adding another jump to jump.

			int32_t offset = 0;

			for (uint32_t i = 0; i < CasesToBeFixed.size(); i++)
			{
				offset = CodePageData.size() - CasesToBeFixed[i].JumpInfo.JumpLocation - 2;
				if (offset > 65535)
					Throw("Jump label \"" + CasesToBeFixed[i].JumpInfo.Label + "\" out of jump range on jump to jump " + to_string(offset));

				*(int16_t*)(CodePageData.data() + CasesToBeFixed[i].JumpInfo.JumpLocation) = (int16_t)offset;

				cout << "fixed switch jump " + CasesToBeFixed[i].JumpInfo.Label << endl;


				offset = CasesToBeFixed[i].LabelInfo.LabelLocation - CodePageData.size() - 2;
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
			*(int16_t*)(CodePageData.data() + JumpOverOffset) = (int16_t)(CodePageData.size() - JumpOverOffset - 2);
		}
	}
	if (switchStore->hasDefaultJumpLoc())
	{
		AddJump(JumpInstructionType::Jump, switchStore->getDefaultJumpLoc()->toString());
	}

}

void CompileGTAPC::AddImm(const int32_t Literal)
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

void CompileGTAPC::MultImm(const int32_t Literal)
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

void CompileGTAPC::FAddImm()
{
	switch (DATA->getInt())
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

void CompileGTAPC::BuildTables()
{
	for (FunctionCount = 0; FunctionCount < HLData->getFunctionCount(); FunctionCount++)
	{
		if (HLData->getFunctionFromIndex(FunctionCount)->IsUsed())
		{
			AddFunction(HLData->getFunctionFromIndex(FunctionCount));
			for (InstructionCount = 0; InstructionCount < HLData->getFunctionFromIndex(FunctionCount)->getInstructionCount(); InstructionCount++)
			{
				ParseGeneral(HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)->getKind());
				CheckSignedJumps();
				CheckUnsignedJumps();
			}
			fixFunctionJumps();
		}
	}
	fixFunctionCalls();
}

void CompileGTAPC::fixFunctionJumps()
{
	for (auto jTableItem : jumpTableLocs)
	{
		auto it = LabelLocations.find(jTableItem.labelName);
		if (it == LabelLocations.end())
		{
			Throw("Jump table label '" + jTableItem.labelName + "' not found");
		}
		*(uint32_t*)(StringPageData.data() + jTableItem.tableOffset) = it->second.LabelLocation;
	}
	jumpTableLocs.clear();
	JumpLocations.clear();
	LabelLocations.clear();
	SignedJumpLocationInc = UnsignedJumpLocationInc = 0;
}

void CompileGTAPC::fixFunctionCalls()
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
		{
			Throw("Function \"" + CallInfo.Function->getName() + "\" out of call range");//realistally this is never going to happen
		}
		switch (CallInfo.InstructionType)
		{
			case CallInstructionType::FuncLoc:
				*(int*)(CodePageData.data() - 1 + CallInfo.CallLocation) = pos << 8 | BaseOpcodes->PushI24;
				break;
			case CallInstructionType::Call:
				*(int*)(CodePageData.data() - 1 + CallInfo.CallLocation) = pos << 8 | BaseOpcodes->Call;
				break;
			default: assert(false && "Invalid Call Instruction"); break;
		}
	}
}

void CompileGTAPC::ParseGeneral(const OpcodeKind OK)
{
	switch (OK)
	{
		case OK_Null:		return;
		case OK_Nop:		AddPadding(DATA->getUShort(0)); return;
		case OK_Add:		AddOpcode(Add); return;
		case OK_Sub:		AddOpcode(Sub); return;
		case OK_Mult:		AddOpcode(Mult); return;
		case OK_Div:		AddOpcode(Div); return;
		case OK_Mod:		AddOpcode(Mod); return;
		case OK_Not:		AddOpcode(Not); return;
		case OK_Neg:		AddOpcode(Neg); return;
		case OK_CmpEq:		AddOpcode(CmpEq); return;
		case OK_CmpNe:		AddOpcode(CmpNe); return;
		case OK_CmpGt:		AddOpcode(CmpGt); return;
		case OK_CmpGe:		AddOpcode(CmpGe); return;
		case OK_CmpLt:		AddOpcode(CmpLt); return;
		case OK_CmpLe:		AddOpcode(CmpLe); return;
		case OK_FAdd:		AddOpcode(fAdd); return;
		case OK_FSub:		AddOpcode(fSub); return;
		case OK_FMult:		AddOpcode(fMult); return;
		case OK_FDiv:		AddOpcode(fDiv); return;
		case OK_FMod:		AddOpcode(fMod); return;
		case OK_FNeg:		AddOpcode(fNeg); return;
		case OK_FCmpEq:		AddOpcode(fCmpEq); return;
		case OK_FCmpNe:		AddOpcode(fCmpNe); return;
		case OK_FCmpGt:		AddOpcode(fCmpGt); return;
		case OK_FCmpGe:		AddOpcode(fCmpGe); return;
		case OK_FCmpLt:		AddOpcode(fCmpLt); return;
		case OK_FCmpLe:		AddOpcode(fCmpLe); return;
		case OK_VAdd:		AddOpcode(vAdd); return;
		case OK_VSub:		AddOpcode(vSub); return;
		case OK_VMult:		AddOpcode(vMult); return;
		case OK_VDiv:		AddOpcode(vDiv); return;
		case OK_VNeg:		AddOpcode(vNeg); return;
		case OK_And:		AddOpcode(And); return;
		case OK_Or:			AddOpcode(Or); return;
		case OK_Xor:		AddOpcode(Xor); return;
		case OK_FtoI:		AddOpcode(FtoI); return;
		case OK_ItoF:		AddOpcode(ItoF); return;
		case OK_FtoV:		AddOpcode(FtoV); return;
		case OK_PushInt:	PushInt(); return;//gta4 needs to override
		case OK_PushBytes:	PushBytes(); return;//gta4 needs to override
		case OK_PushFloat:	PushFloat(); return;//gta4 needs to override
		case OK_Dup:		AddOpcode(Dup); return;
		case OK_Drop:		AddOpcode(Drop); return;
		case OK_Native:		CallNative(); return;//callnative def| gta5 1 byte param/return, 2 byte call loc | rdr 2 byte call loc | gta4: 1 byte param, 1 byte return, 4 byte hash
		case OK_Return:		Return(); return;//rdr needs to override
		case OK_PGet:		AddOpcode(pGet); return;
		case OK_PSet:		AddOpcode(pSet); return;
		case OK_PeekSet:	AddOpcode(pPeekSet); return;
		case OK_ToStack:	AddOpcode(ToStack); return;
		case OK_FromStack:	AddOpcode(FromStack); return;

		case OK_GetArrayP:	GetArrayP(); return;
		case OK_GetArray:	GetArray(); return;
		case OK_SetArray:	SetArray(); return;
		case OK_GetFrameP:	GetFrameP(); return;
		case OK_GetFrame:	GetFrame(); return;
		case OK_SetFrame:	SetFrame(); return;
		case OK_GetStaticP:	GetStaticP(); return;
		case OK_GetStatic:	GetStatic(); return;
		case OK_SetStatic:	SetStatic(); return;
		case OK_GetGlobalP:	GetGlobalP(); return;
		case OK_GetGlobal:	GetGlobal(); return;
		case OK_SetGlobal:	SetGlobal(); return;
		case OK_AddImm:		AddImm(); return;
		case OK_MultImm:	MultImm(); return;
		case OK_FAddImm:	FAddImm(); return;
		case OK_FMultImm:	FMultImm(); return;
		case OK_GetImmP:	GetImmP(); return;
		case OK_GetImm:		GetImm(); return;
		case OK_SetImm:		SetImm(); return;


		case OK_Call:		Call();  return;
		case OK_Jump:		AddJump(JumpInstructionType::Jump, DATA->getString()); return;
		case OK_JumpFalse:	AddJump(JumpInstructionType::JumpFalse, DATA->getString()); return;
		case OK_JumpEQ:		AddJump(JumpInstructionType::JumpEQ, DATA->getString()); return;
		case OK_JumpNE:		AddJump(JumpInstructionType::JumpNE, DATA->getString()); return;
		case OK_JumpGT:		AddJump(JumpInstructionType::JumpGT, DATA->getString()); return;
		case OK_JumpGE:		AddJump(JumpInstructionType::JumpGE, DATA->getString()); return;
		case OK_JumpLT:		AddJump(JumpInstructionType::JumpLT, DATA->getString()); return;
		case OK_JumpLE:		AddJump(JumpInstructionType::JumpLE, DATA->getString()); return;
		case OK_Switch:		Switch(); return;
		case OK_PushString:	PushString(); return;
		case OK_StrCopy:	StrCopy(); return;
		case OK_ItoS:		ItoS(); return;
		case OK_StrAdd:		StrAdd(); return;
		case OK_StrAddI:	StrAddI(); return;
		case OK_MemCpy:		AddOpcode(MemCopy); return;
		case OK_PCall:		pCall(); return;
		case OK_Label:		AddLabel(DATA->getString()); return;
		case OK_LabelLoc:	AddJump(JumpInstructionType::LabelLoc, DATA->getString()); return;
		case OK_FuncLoc:	AddFuncLoc(DATA->getFunctionData()); return;
		case OK_ShiftLeft:	CallNative(0xEDD95A39E5544DE8, 2, 1); return;
		case OK_ShiftRight:	CallNative(0x97EF1E5BCE9DC075, 2, 1); return;
		case OK_GetHash:	GetHash(); return;
		case OK_GoToStack:	GoToStack(); return;
		case OK_JumpTable:	AddJumpTable(); return;
		default: assert(false && "Invalid General Opcode");
	}
}

inline int32_t CompileGTAPC::GetSizeFromFlag(uint32_t flag, int32_t baseSize)
{
	baseSize <<= (int32_t)(flag & 0xf);
	int size = (int32_t)((((flag >> 17) & 0x7f) + (((flag >> 11) & 0x3f) << 1) + (((flag >> 7) & 0xf) << 2) + (((flag >> 5) & 0x3) << 3) + (((flag >> 4) & 0x1) << 4)) * baseSize);
	for (int32_t i = 0; i < 4; ++i)
		size += (((flag >> (24 + i)) & 1) == 1) ? (baseSize >> (1 + i)) : 0;
	return size;
}
inline int32_t CompileGTAPC::GetSizeFromSystemFlag(uint32_t flag)
{
	if (HLData->getBuildPlatform() == Platform::P_PS3)
		return GetSizeFromFlag(flag, 0x1000);
	else // XBOX 360 / PC
		return GetSizeFromFlag(flag, 0x2000);
}
inline int32_t CompileGTAPC::GetSizeFromGraphicsFlag(uint32_t flag)
{
	if (HLData->getBuildPlatform() == Platform::P_PS3)
		return GetSizeFromFlag(flag, 0x1580);
	else // XBOX 360 / PC
		return GetSizeFromFlag(flag, 0x2000);
}
uint32_t CompileGTAPC::GetFlagFromSize(int32_t size)
{
	for (int i = 0; i < 0x7FFFFFFF; i++)
	{
		if (GetSizeFromSystemFlag(i) == size)
			return i;
	}
	assert(false && "GetFlagFromSize: Size Not Found");
	return 0;
}
const uint32_t CompileGTAPC::AddStringToStringPage(const string str)
{
	//if string is in table
	auto it = StringPageDataIndexing.find(str);
	if (it != StringPageDataIndexing.end())
	{
		return it->second;
	}

	const uint32_t len = str.length();
	uint32_t pos = StringPageData.size();

	if ((pos + len + 1) % 16384 < pos % 16384)
	{
		StringPageData.resize(16384 - (pos % 16384) + pos);
		pos = StringPageData.size();
	}

	StringPageDataIndexing[str] = pos;
	StringPageData.resize(pos + len + 1);
	memcpy(StringPageData.data() + pos, str.data(), len + 1);
	return pos;
}

void CompileGTAPC::WriteHeader()
{
	headerLocation = BuildBuffer.size();

	AddInt64toBuff(0x1405A9E0D);//page base
	AddInt64toBuff(0); //Unk1 ptr
	AddInt64toBuff(0); //codeBlocksListOffsetPtr
	AddInt32toBuff(0xB0AC45A4);//unk2
	AddInt32toBuff(CodePageData.size());//code length
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
	AddInt32toBuff(StringPageData.size());
	AddInt32toBuff(0);//Unk6
	AddInt64toBuff(0);//unk7

	//no need to pad as its divisible by 16
}

void CompileGTAPC::WritePointers()
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
	BuildBuffer.resize(BuildBuffer.size() + CodePageCount * 8, 0);
	Pad();

	//Write string page pointers

	if (StringPageCount)
	{
		if (GetSpaceLeft(16384) < StringPageCount * 8)
			FillPageDynamic(16384);

		SavedOffsets.StringBlocks = BuildBuffer.size();
		BuildBuffer.resize(BuildBuffer.size() + StringPageCount * 8, 0);
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

void CompileGTAPC::Write16384StringPages()
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

void CompileGTAPC::WriteFinalStringPage()
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

void CompileGTAPC::XSCWrite(const char* path, bool AddRsc7Header)
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

void CompileGTAPC::WriteCodePagesNoPadding()
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
}

void CompileGTAPC::Write16384CodePages()
{
	SavedOffsets.CodePagePointers.resize(CodePageCount);
	for (uint32_t i = 0; i < CodePageCount - 1; i++)
	{

		if (GetSpaceLeft(16384) < 16384)
		{
			if (i)
				FillPageNops();
			else
				FillPageDynamic(16384);
		}

		SavedOffsets.CodePagePointers[i] = BuildBuffer.size();

		BuildBuffer.resize(BuildBuffer.size() + 16384);
		memcpy(BuildBuffer.data() + BuildBuffer.size() - 16384, CodePageData.data() + i * 16384, 16384);

		PadNops();
	}
}

void CompileGTAPC::WriteFinalCodePage()
{
	const uint32_t LastCodePageSize = CodePageData.size() % 16384;
	SavedOffsets.CodePagePointers[CodePageCount - 1] = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + LastCodePageSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - LastCodePageSize, CodePageData.data() + CodePageData.size() - LastCodePageSize, LastCodePageSize);
	Pad();
}
void CompileGTAPC::WriteNativesNoPadding()
{
	const size_t nativeByteSize = NativeHashMap.size() * 8;
	SavedOffsets.Natives = BuildBuffer.size();
	BuildBuffer.resize(BuildBuffer.size() + nativeByteSize);
	for (unordered_map<uint64_t, uint32_t>::iterator it = NativeHashMap.begin(); it != NativeHashMap.end(); it++)
	{
		*(uint64_t*)(BuildBuffer.data() + SavedOffsets.Natives + it->second * 8) = ror(it->first, it->second + CodePageData.size());
	}
}
void CompileGTAPC::WriteNatives()
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
			*(uint64_t*)(BuildBuffer.data() + SavedOffsets.Natives + it->second * 8) = ror(it->first, it->second + CodePageData.size());
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
void CompileGTAPC::WriteStaticsNoPadding()
{
	const size_t staticByteSize = HLData->getStaticCount() * 8;

	SavedOffsets.Statics = BuildBuffer.size();

	BuildBuffer.resize(BuildBuffer.size() + staticByteSize);
	memcpy(BuildBuffer.data() + BuildBuffer.size() - staticByteSize, HLData->getNewStaticData(), staticByteSize);
}
void CompileGTAPC::WriteStatics()
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
