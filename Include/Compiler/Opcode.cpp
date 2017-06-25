#include "Compiler/Opcode.h"
#include "ClangParsing/Helpers/StaticData.h"
#include "ClangParsing/Helpers/FunctionData.h"

using namespace std;

Opcode::~Opcode()
{
#ifdef _DEBUG
	if (_comment)
	{
		delete _comment;
	}
#endif
	switch (opcodeKind)
	{
		case OK_PushString:
		case OK_Jump:
		case OK_JumpFalse:
		case OK_JumpEQ:
		case OK_JumpNE:
		case OK_JumpGT:
		case OK_JumpGE:
		case OK_JumpLT:
		case OK_JumpLE:
		case OK_Label:
		case OK_LabelLoc:
			delete storage.string;
			break;
		case OK_Native:
			delete storage.native;
			break;
		case OK_Switch:
			delete storage.switchCase;
			break;
		case OK_JumpTable:
			delete storage.jTable;
			break;
		default:
			break;
	}
}

int Opcode::getSizeEstimate() const
{
	bool isRDR = false;
	switch (getKind())
	{
		case OK_Null:
			return 0;
		case OK_Nop:
			return getUShort(0);
		case OK_Add:
		case OK_Sub:
		case OK_Mult:
		case OK_Div:
		case OK_Mod:
		case OK_Not:
		case OK_Neg:
		case OK_CmpEq:
		case OK_CmpNe:
		case OK_CmpGt:
		case OK_CmpGe:
		case OK_CmpLt:
		case OK_CmpLe:
		case OK_FAdd:
		case OK_FSub:
		case OK_FMult:
		case OK_FDiv:
		case OK_FMod:
		case OK_FNeg:
		case OK_FCmpEq:
		case OK_FCmpNe:
		case OK_FCmpGt:
		case OK_FCmpGe:
		case OK_FCmpLt:
		case OK_FCmpLe:
		case OK_VAdd:
		case OK_VSub:
		case OK_VMult:
		case OK_VDiv:
		case OK_VNeg:
		case OK_And:
		case OK_Or:
		case OK_Xor:
		case OK_ItoF:
		case OK_FtoI:
		case OK_FtoV:
		case OK_Dup:
		case OK_Drop:
		case OK_PGet:
		case OK_PSet:
		case OK_PeekSet:
		case OK_FromStack:
		case OK_ToStack:
		case OK_MemCpy:
		case OK_PCall:
		case OK_GetImmPStack:
		case OK_PushNullPtr:
			return 1;
		case OK_PushInt:
		{
			int value = getInt();
			if (value >= -1 && value <= 7){
				return 1;//Push_Val
			}
			if (value > 0 && value < 256){
				return 2;//PushB Val
			}
			if (value >= -32768 && value <= 32767){
				return 3;//PushS Val
			}
			if (value > 0 && value < 0x1000000){
				return 4;//PushI24 Val
			}
		}
		return 5;//Push Val

		case OK_PushBytes:
			switch (getByte(0))
			{
				case 0:
					assert(false && "Empty PushBytes opcode");
					return 0;
				case 1:
					assert(false && "PushBytes opcode called with 1 byte, should never happen as it should be wrapped in PushInt");
					return 2;
				case 2:
					return 3;
				case 3:
					return 4;
			}
			assert(false && "Too many bytes in PushBytes opcode");
			return 0;

		case OK_PushFloat:
			switch ((uint32_t)getInt())
			{
				case 0xbf800000:
				case 0x80000000://neg 0
				case 0x00000000://pos 0
				case 0x3f800000:
				case 0x40000000:
				case 0x40400000:
				case 0x40800000:
				case 0x40A00000:
				case 0x40C00000:
				case 0x40E00000:
					return 1;//PushF_Val
			}
			return 5;//PushF Val
		case OK_ShiftLeft:
		case OK_ShiftRight:
		case OK_Native:
		case OK_Call:
			return 4;
		case OK_Return:
		case OK_Jump:
		case OK_JumpFalse:
		case OK_JumpEQ:
		case OK_JumpNE:
		case OK_JumpGT:
		case OK_JumpGE:
		case OK_JumpLT:
		case OK_JumpLE:
			return 3;
		case OK_PushString:
			if (isRDR)
			{
				return 3 + getString().length();//PushString <len> <string> <nullTerminator>
			}
			else
			{
				return 4;//just a guess as it depends where it is placed in string table
			}
		case OK_StrCopy:
		case OK_ItoS:
		case OK_StrAdd:
		case OK_StrAddI:
			return 2;
		case OK_GetArrayP:
		case OK_GetArray:
		case OK_SetArray:
		case OK_GetStaticP:
		case OK_GetStaticPRaw:
		case OK_GetStatic:
		case OK_GetStaticRaw:
		case OK_SetStatic:
		case OK_SetStaticRaw:
		case OK_GetFrameP:
		case OK_GetFrame:
		case OK_SetFrame:
		case OK_GetImmP:
		case OK_GetImm:
		case OK_SetImm:
			return getUShort(0) > 0xFF ? 3 : 2;
		case OK_GetGlobalP:
		case OK_GetGlobal:
		case OK_SetGlobal:
			return (uint32_t)getInt() > 0xFFFF ? 4 : 3;
		case OK_Label:
			return 0;//labels dont take up storage
		case OK_LabelLoc:
		case OK_FuncLoc:
			return 4;//Just PushInt24
		case OK_AddImm:
		{
			int value = getInt();
			if (value > 0 && value < 256){
				return 2;//Add1 Val
			}
			if (value >= -32768 && value < 32768){
				return 3;//Add2 Val
			}
			if (value > 0 && value < 0x1000000)
			{
				return 5;//PushI24 Val, Add
			}
		}
		return 6;//Push Val, Add
		case OK_MultImm:
		{
			int value = getInt();
			if (value > 0 && value < 256){
				return 2;//Mult1 Val
			}
			if (value >= -32768 && value < 32768){
				return 3;//Mult2 Val
			}
			if (value > 0 && value < 0x1000000)
			{
				return 5;//PushI24 Val, Mult
			}
		}
		return 6;//Push Val, Mult
		case OK_FAddImm:
			switch ((uint32_t)getInt())
			{
				case 0x80000000://neg 0
				case 0x00000000://pos 0
					return 0;//can be skipped
				case 0xc0e00000:
				case 0xc0c00000:
				case 0xc0a00000:
				case 0xc0800000:
				case 0xc0400000:
				case 0xc0000000:
				case 0xbf800000:
				case 0x3f800000:
				case 0x40000000:
				case 0x40400000:
				case 0x40800000:
				case 0x40A00000:
				case 0x40C00000:
				case 0x40E00000:
					return 2;//PushF_Val, FAdd/FSub
			}
			return 6;//PushF Val, FAdd/FSub
		case OK_FMultImm:
			switch ((uint32_t)getInt())
			{
				case 0xbf800000:
					return 1;//FNeg
				case 0x3f800000:
					return 0;//this should never come up(just skip it)
				case 0x80000000://neg 0
				case 0x00000000://pos 0 - this should never come up
				case 0x40000000:
				case 0x40400000:
				case 0x40800000:
				case 0x40A00000:
				case 0x40C00000:
				case 0x40E00000:
					return 2;//PushF_Val, FMult
			}
			return 6;//PushF Val, FMult		
		case OK_Switch:
		{
			return 2 + storage.switchCase->getCount() * 6 + (storage.switchCase->hasDefaultJumpLoc() ? 3 : 0);
		}
		case OK_GetHash:
			if (isRDR)
			{
				return 4;//CallNative
			}
			else
			{
				return 1;//GetHash opcode
			}
		case OK_JumpTable:
		{
			if (isRDR)
			{
				return 5 + storage.jTable->getByteSize();
			}
			else{
				return 4;//just a guess as it depends where it is placed in string table
			}
		}
		case OK_GoToStack:
			if (isRDR)return 6;
			else return 8;
	}
	//assert(false);//trying to figure out which path isnt returning a value
	return 0;
}

string Opcode::toString() const
{
#define Check12Op(opcode){uint16_t value = getUShort(0);current = (value > 0xFF ? #opcode "2 " :  #opcode "1 ") + to_string(value); }
#define Check23Op(opcode){int value = getInt();assert(value >= 0 && "value cannot be negative"); current = (value > 0xFFFF ? #opcode "3 " :  #opcode "2 ") + to_string(value); }
#define CheckStatic(opcode){auto data = getStaticData(); assert(data->getStatic()->isUsed() && "static is unused"); uint16_t value = data->getStatic()->getIndex() + data->getImmIndex(); current = (value > 0xFF ? #opcode "2 " :  #opcode "1 ") + to_string(value); }
#define CheckStaticRaw(opcode){uint16_t value = getUShort(0); current = (value > 0xFF ? #opcode "2 " :  #opcode "1 ") + to_string(value); }
#define PrintJump(cond){current = "Jump"#cond " @" + getString();}
	string current;
	switch (getKind())
	{
		case OK_Null: break;
		case OK_Nop: current = "Nop"; for (int i = getUShort(0); --i;){ current += "\r\nNop"; } break;
		case OK_Add: current = "Add"; break;
		case OK_Sub: current = "Sub"; break;
		case OK_Mult: current = "Mult"; break;
		case OK_Div: current = "Div"; break;
		case OK_Mod: current = "Mod"; break;
		case OK_Not: current = "Not"; break;
		case OK_Neg: current = "Neg"; break;
		case OK_CmpEq: current = "CmpEq"; break;
		case OK_CmpNe: current = "CmpNe"; break;
		case OK_CmpGt: current = "CmpGt"; break;
		case OK_CmpGe: current = "CmpGe"; break;
		case OK_CmpLt: current = "CmpLt"; break;
		case OK_CmpLe: current = "CmpLe"; break;
		case OK_FAdd: current = "FAdd"; break;
		case OK_FSub: current = "FSub"; break;
		case OK_FMult: current = "FMult"; break;
		case OK_FDiv: current = "FDiv"; break;
		case OK_FMod: current = "FMod"; break;
		case OK_FNeg: current = "FNeg"; break;
		case OK_FCmpEq: current = "FCmpEq"; break;
		case OK_FCmpNe: current = "FCmpNe"; break;
		case OK_FCmpGt: current = "FCmpGt"; break;
		case OK_FCmpGe: current = "FCmpGe"; break;
		case OK_FCmpLt: current = "FCmpLt"; break;
		case OK_FCmpLe: current = "FCmpLe"; break;
		case OK_VAdd: current = "VAdd"; break;
		case OK_VSub: current = "VSub"; break;
		case OK_VMult: current = "VMult"; break;
		case OK_VDiv: current = "VDiv"; break;
		case OK_VNeg: current = "VNeg"; break;
		case OK_And: current = "And"; break;
		case OK_Or: current = "Or"; break;
		case OK_Xor: current = "Xor"; break;
		case OK_ItoF: current = "ItoF"; break;
		case OK_FtoI: current = "FtoI"; break;
		case OK_FtoV: current = "FtoV"; break;
		case OK_ShiftLeft: current = "CallNative shift_left 2 1"; break;
		case OK_ShiftRight: current = "CallNative shift_right 2 1"; break;
		case OK_GetHash: current = "CallNative get_hash_key 1 1"; break;
		case OK_PushInt:
		{
			int value = getInt();
			if (value >= -1 && value <= 7){
				current = "Push_" + to_string(value);
			}
			else if (value > 0 && value < 256){
				current = "PushB " + to_string(value);
			}
			else if (value >= -32768 && value <= 32767){
				current = "PushS " + to_string(value);
			}
			else if (value > 0 && value < 0x1000000){
				current = "PushI24 " + to_string(value);
			}
			else{
				current = "Push " + to_string(value);
			}
			break;
		}
		case OK_PushBytes:
		{
			switch (getByte(0))
			{
				case 0:
					assert(false && "Empty PushBytes opcode");
				case 1:
					assert(false && "PushBytes opcode called with 1 byte, should never happen as it should be wrapped in PushInt");
					current = "PushB " + to_string(getByte(1));
					break;
				case 2:
					current = "PushB2 " + to_string(getByte(1)) + " " + to_string(getByte(2));
					break;
				case 3:
					current = "PushB3 " + to_string(getByte(1)) + " " + to_string(getByte(2)) + " " + to_string(getByte(3));
					break;
				default:
					assert(false && "Too many bytes in PushBytes opcode");
			}
		}
		break;
		case OK_PushFloat:
		{
			switch ((uint32_t)getInt())
			{
				case 0xbf800000:
					current = "PushF_-1"; break;
				case 0x80000000://neg 0
				case 0x00000000://pos 0
					current = "PushF_0"; break;
				case 0x3f800000:
					current = "PushF_1"; break;
				case 0x40000000:
					current = "PushF_2"; break;
				case 0x40400000:
					current = "PushF_3"; break;
				case 0x40800000:
					current = "PushF_4"; break;
				case 0x40A00000:
					current = "PushF_5"; break;
				case 0x40C00000:
					current = "PushF_6"; break;
				case 0x40E00000:
					current = "PushF_7"; break;
				default:
					current = "PushF " + to_string(getFloat());
					break;
			}
			break;
		}
		case OK_Dup: current = "Dup"; break;
		case OK_Drop: current = "Drop"; break;
		case OK_Native:
		{
			char buff[17];
			sprintf(buff, "%llX", storage.native->getHash());
			
			if (storage.native->hasName())
			{
				current = "CallNative " + storage.native->getName() + " " + to_string(storage.native->getParamCount()) + " " + to_string(storage.native->getReturnCount()) + " //0x" + string(buff);
			}
			else{
				current = "CallNative _0x" + string(buff) + " " + to_string(storage.native->getParamCount()) + " " + to_string(storage.native->getReturnCount());
			}
			break;
		}
		case OK_Return:
			current = "Return " + to_string(getByte(0)) + " " + to_string(getByte(1));
			break;
		case OK_PGet: current = "pGet"; break;
		case OK_PSet: current = "pSet"; break;
		case OK_PeekSet: current = "pPeekSet"; break;
		case OK_ToStack: current = "ToStack"; break;
		case OK_FromStack: current = "FromStack"; break;
		case OK_GetArrayP:Check12Op(GetArrayP); break;
		case OK_GetArray:Check12Op(GetArray); break;
		case OK_SetArray:Check12Op(SetArray); break;
		case OK_GetFrameP:Check12Op(GetFrameP); break;
		case OK_GetFrame:Check12Op(GetFrame); break;
		case OK_SetFrame:Check12Op(SetFrame); break;
		case OK_GetStaticP:CheckStatic(GetStaticP); break;
		case OK_GetStaticPRaw:CheckStaticRaw(GetStaticP); break;
		case OK_GetStatic:CheckStatic(GetStatic); break;
		case OK_GetStaticRaw:CheckStaticRaw(GetStatic); break;
		case OK_SetStatic:CheckStatic(SetStatic); break;
		case OK_SetStaticRaw:CheckStaticRaw(SetStatic); break;
		case OK_GetImmPStack:current = "GetImmP"; break;
		case OK_GetImmP:Check12Op(GetImmP); break;
		case OK_GetImm:Check12Op(GetImm); break;
		case OK_SetImm:Check12Op(SetImm); break;
		case OK_GetGlobalP:Check23Op(GetGlobalP); break;
		case OK_GetGlobal:Check23Op(GetGlobal); break;
		case OK_SetGlobal:Check23Op(SetGlobal); break;
		case OK_AddImm:
		{
			int value = getInt();
			if (value > 0 && value < 256){
				current = "Add1 " + to_string(value);
			}
			else if (value >= -32768 && value < 32768){
				current = "Add2 " + to_string(value);
			}
			else if (value > 0 && value < 0x1000000)
			{
				current = "PushI24 " + to_string(value) + "\r\nAdd";
			}
			else{
				current = "Push " + to_string(value) + "\r\nAdd";
			}
			break;
		}
		case OK_MultImm:
		{
			int value = getInt();
			if (value > 0 && value < 256){
				current = "Mult1 " + to_string(value);
			}
			else if (value >= -32768 && value < 32768){
				current = "Mult2 " + to_string(value);
			}
			else if (value > 0 && value < 0x1000000)
			{
				current = "PushI24 " + to_string(value) + "\r\nMult";
			}
			else{
				current = "Push " + to_string(value) + "\r\nMult";
			}
			break;
		}
		case OK_FAddImm:
		{
			switch ((uint32_t)getInt())
			{
				case 0xc0e00000:
					current = "PushF_7\r\nFSub"; break;
				case 0xc0c00000:
					current = "PushF_6\r\nFSub"; break;
				case 0xc0a00000:
					current = "PushF_5\r\nFSub"; break;
				case 0xc0800000:
					current = "PushF_4\r\nFSub"; break;
				case 0xc0400000:
					current = "PushF_3\r\nFSub"; break;
				case 0xc0000000:
					current = "PushF_2\r\nFSub"; break;
				case 0xbf800000:
					current = "PushF_1\r\nFSub"; break;
				case 0x80000000://neg 0
				case 0x00000000://pos 0
					current = "";//dont parse anything for these, though they should never come up
				case 0x3f800000:
					current = "PushF_1\r\nFAdd"; break;
				case 0x40000000:
					current = "PushF_2\r\nFAdd"; break;
				case 0x40400000:
					current = "PushF_3\r\nFAdd"; break;
				case 0x40800000:
					current = "PushF_4\r\nFAdd"; break;
				case 0x40A00000:
					current = "PushF_5\r\nFAdd"; break;
				case 0x40C00000:
					current = "PushF_6\r\nFAdd"; break;
				case 0x40E00000:
					current = "PuashF_7\r\nFAdd"; break;
				default:
					float fValue = getFloat();
					if (fValue >= 0)
					{
						current = "PushF " + to_string(fValue) + "\r\nFAdd";
					}
					else
					{
						current = "PushF " + to_string(-fValue) + "\r\nFSub";
					}
					break;
			}
			break;
		}
		case OK_FMultImm:
		{
			switch ((uint32_t)getInt())
			{
				case 0xbf800000:
					current = "FNeg"; break;//this should never come up
				case 0x80000000://neg 0
				case 0x00000000://pos 0
					current = "PushF_0\r\nFMult"; break;//this should never come up
				case 0x3f800000:
					current = ""; break;//this should never come up
				case 0x40000000:
					current = "PushF_2\r\nFMult"; break;
				case 0x40400000:
					current = "PushF_3\r\nFMult"; break;
				case 0x40800000:
					current = "PushF_4\r\nFMult"; break;
				case 0x40A00000:
					current = "PushF_5\r\nFMult"; break;
				case 0x40C00000:
					current = "PushF_6\r\nFMult"; break;
				case 0x40E00000:
					current = "PushF_7\r\nFMult"; break;
				default:
					current = "PushF " + to_string(getFloat()) + "\r\nFMult";
					break;
			}
			break;
		}
		case OK_Call:current = "Call @" + getFunctionData()->getName(); break;
		case OK_Jump: current = "Jump @" + getString(); break;
		case OK_JumpFalse: PrintJump(False); break;
		case OK_JumpEQ: PrintJump(EQ); break;
		case OK_JumpNE: PrintJump(NE); break;
		case OK_JumpGT: PrintJump(GT); break;
		case OK_JumpGE: PrintJump(GE); break;
		case OK_JumpLT: PrintJump(LT); break;
		case OK_JumpLE: PrintJump(LE); break;
		case OK_Switch:{
			const SwitchStorage* switchStorage = getSwitch();
			if (switchStorage->getCount())
			{
				const SwitchCaseStorage* sCase = switchStorage->getFirstCase();
				current = "Switch [" + to_string(sCase->getCaseValue()) + " @" + sCase->getCaseLocation() + "]";
				while (sCase->hasNextCase())
				{
					sCase = sCase->getNextCase();
					current += ":[" + to_string(sCase->getCaseValue()) + " @" + sCase->getCaseLocation() + "]";
				}
			}
			else
			{
				current = "Switch //Empty Switch";
			}
			if (switchStorage->hasDefaultJumpLoc())
			{
				current += "\r\nJump @" + switchStorage->getDefaultJumpLoc()->toString();
			}
			break;
		}
		case OK_PushString:
			current = "PushString \"" + getString() + "\""; break;
		case OK_StrCopy:
			current = "StrCopy " + to_string(getByte(0)); break;
		case OK_ItoS:
			current = "ItoS " + to_string(getByte(0)); break;
		case OK_StrAdd:
			current = "StrAdd " + to_string(getByte(0)); break;
		case OK_StrAddI:
			current = "StrAddI " + to_string(getByte(0)); break;
		case OK_MemCpy: current = "MemCpy"; break;
		case OK_PCall: current = "PCall"; break;
		case OK_Label: current = "\r\n:" + getString(); break; //make labels have a line break
		case OK_LabelLoc: current = "Push GetLoc(\"" + getString() + "\")"; break;
		case OK_FuncLoc: current = "Push GetFuncLoc(\"" + getFunctionData()->getName() + "\")"; break;
		case OK_JumpTable:{
			current = "PushLabelLocArrayPtr {\r\n";
			if (storage.jTable->getItemCount() == 0)
			{
				current += "}"; break;
			}
			current += "\"" + storage.jTable->getJumpLocAsString(0) + "\"";
			for (unsigned i = 1; i < storage.jTable->getItemCount(); i++)
			{
				current += ", \r\n\"" + storage.jTable->getJumpLocAsString(i) + "\"";
			}
			current += "\r\n}";
			break;
		}
		case OK_GoToStack:
			current = "Function 0 2\r\nReturn 0 0"; break;
		case OK_PushNullPtr:
			current = "Push_0"; break;
	}
#ifdef _DEBUG
	if (hasComment())
	{
		current += " //" + getComment();
	}
#endif
	return current;
#undef Check12Op
#undef Check23Op
#undef CheckStatic
#undef CheckStaticRaw
#undef PrintJump
}

void Opcode::makeNull()
{
	switch (opcodeKind)
	{
		case OK_PushString:
		case OK_Jump:
		case OK_JumpFalse:
		case OK_JumpEQ:
		case OK_JumpNE:
		case OK_JumpGT:
		case OK_JumpGE:
		case OK_JumpLT:
		case OK_JumpLE:
		case OK_Label:
		case OK_LabelLoc:
			delete storage.string;
			break;
		case OK_Native:
			delete storage.native;
			break;
		case OK_Switch:
			delete storage.switchCase;
			break;
		case OK_JumpTable:
			delete storage.jTable;
			break;
		case OK_GetStaticP:
		case OK_GetStatic:
		case OK_SetStatic:
			delete storage.staticData;
			break;
		default:
			break;
	}
	storage.i32 = 0;
	opcodeKind = OK_Null;
}
