#include "FunctionOpcode.h"
#include <cassert>
#include <sstream>

struct SwitchCaseIns
{
	int value;
	string loc;
	SwitchCaseIns* next;
};

void Opcode::setULong(uint64_t value)
{
	*(uint64_t*)storage = value;
}

void Opcode::setString(string str)
{
	char* temp = new char[str.length() + 1];
	memcpy(temp, str.c_str(), str.length() + 1);
	*(char**)storage = temp;
}

void Opcode::setInt(int value, int offset)
{
	assert(offset >= 0 && offset <= 8 && "int offset must be between 0 and 8");
	*(int*)(storage + offset) = value;
}

void Opcode::setFloat(float value, int offset)
{
	assert(offset >= 0 && offset <= 8 && "float offset must be between 0 and 8");
	*(float*)(storage + offset) = value;
}

void Opcode::setShort(int16_t value, int offset)
{
	assert(offset >= 0 && offset <= 10 && "short offset must be between 0 and 10");
	*(int16_t*)(storage + offset) = value;
}

void Opcode::setUShort(uint16_t value, int offset)
{
	assert(offset >= 0 && offset <= 10 && "ushort offset must be between 0 and 10");
	*(uint16_t*)(storage + offset) = value;
}

Opcode::~Opcode()
{
#ifdef _DEBUG
	if(_comment)
	{
		delete[] _comment;
	}
#endif
	switch(opcodeKind)
	{
	case OK_Call:
	case OK_PushString:
	case OK_Jump:
	case OK_JumpTrue:
	case OK_JumpFalse:
	case OK_JumpEQ:
	case OK_JumpNE:
	case OK_JumpGT:
	case OK_JumpGE:
	case OK_JumpLT:
	case OK_JumpLE:
	case OK_Label:
		delete[] * (char**)storage;
		break;
	case OK_Switch:
	{
		SwitchCaseIns** sCasePtr = (SwitchCaseIns**)storage;
		if(sCasePtr)
		{
			SwitchCaseIns *sCase = *sCasePtr;
			while(sCase)
			{
				SwitchCaseIns* tmp = sCase;
				sCase = sCase->next;
				delete tmp;
			}
		}

		break;
	}
	default:
		break;
	}
}

void Opcode::setComment(string comment)
{
#ifdef _DEBUG
	if(_comment)
	{
		delete[] _comment;
	}
	_comment = new char[comment.length() + 1];
	memcpy(_comment, comment.c_str(), comment.length() + 1);
#endif
}

string Opcode::getComment() const
{
#ifdef _DEBUG
	if(_comment)
	{
		return string(_comment);
	}
#endif
	return "";
}

bool Opcode::hasComment() const
{
#ifdef _DEBUG
	return _comment;
#else
	return false;
#endif
}
string Opcode::getString() const
{
	switch(opcodeKind)
	{
	case OK_Call:
	case OK_PushString:
	case OK_Jump:
	case OK_JumpTrue:
	case OK_JumpFalse:
	case OK_JumpEQ:
	case OK_JumpNE:
	case OK_JumpGT:
	case OK_JumpGE:
	case OK_JumpLT:
	case OK_JumpLE:
	case OK_Label:
	case OK_LabelLoc:
		return string(*(char**)storage);
	default:
		assert(false && "Get String called on a non string opcode");
	}
	return "";
}

int Opcode::getInt(int offset) const
{
	assert(offset >= 0 && offset <= 8 && "int offset must be between 0 and 8");
	return *(int*)(storage + offset);
}

float Opcode::getFloat(int offset) const
{
	assert(offset >= 0 && offset <= 8 && "float offset must be between 0 and 8");
	return *(float*)(storage + offset);
}

int16_t Opcode::getShort(int offset) const
{
	assert(offset >= 0 && offset <= 10 && "short offset must be between 0 and 10");
	return *(int16_t*)(storage + offset);
}

uint16_t Opcode::getUShort(int offset) const
{
	assert(offset >= 0 && offset <= 10 && "short offset must be between 0 and 10");
	return *(uint16_t*)(storage + offset);
}

uint64_t Opcode::getULong() const
{
	return *(uint64_t*)storage;
}

string Opcode::toString() const
{
#define Check12Op(opcode){uint16_t value = getUShort(0);current = (value > 0xFF ? #opcode "2 " :  #opcode "1 ") + to_string(value); }
#define Check23Op(opcode){int value = getInt(0);assert(value < 0 && "value cannot be negative"); current = (value > 0xFFFF ? #opcode "3 " :  #opcode "2 ") + to_string(value); }
#define PrintJump(cond){current = "Jump"#cond " @" + getString();}
	string current;
	switch(opcodeKind)
	{
	case OK_Nop: current = "Nop"; break;
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
	case OK_PushInt:
	{
		int value = getInt(0);
		if(value >= -1 && value <= 7){
			current = "Push_" + to_string(value);
		}
		else if(value > 0 && value < 256){
			current = "PushB " + to_string(value);
		}
		else if(value >= -32768 && value <= 32767){
			current = "PushS " + to_string(value);
		}
		else if(value > 0 && value < 0x1000000){
			current = "PushI24 " + to_string(value);
		}
		else{
			current = "Push " + to_string(value);
		}
		break;
	}
	case OK_PushFloat:
	{
		float value = getFloat(0);
		if(value == -1.0){
			current = "PushF_-1";
		}
		else if(value == 0.0){
			current = "PushF_0";
		}
		else if(value == 1.0){
			current = "PushF_1";
		}
		else if(value == 2.0){
			current = "PushF_2";
		}
		else if(value == 3.0){
			current = "PushF_3";
		}
		else if(value == 4.0){
			current = "PushF_4";
		}
		else if(value == 5.0){
			current = "PushF_5";
		}
		else if(value == 6.0){
			current = "PushF_6";
		}
		else if(value == 7.0){
			current = "PushF_7";
		}
		else{
			current = "PushF " + to_string(value);
		}
		break;
	}
	case OK_Dup: current = "Dup"; break;
	case OK_Drop: current = "Drop"; break;
	case OK_Native:
	{
		char buff[17];
		sprintf(buff, "%llX", getULong());
		current = "CallNative 0x" + string(buff) + " " + to_string(getUShort(8)) + " " + to_string(getUShort(10));
		break;
	}
/*	case OK_Func:
		current = ":" + getString() + "\r\nFunction " + to_string(getUShort(4)) + " " + to_string(getUShort(6));
		break;*/
	case OK_Return:
		current = "Return " + to_string(getUShort(0)) + " " + to_string(getUShort(2));
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
	case OK_GetStaticP:Check12Op(GetStaticP); break;
	case OK_GetStatic:Check12Op(GetStatic); break;
	case OK_SetStatic:Check12Op(SetStatic); break;
	case OK_GetImmP:Check12Op(GetImmP); break;
	case OK_GetImm:Check12Op(GetImm); break;
	case OK_SetImm:Check12Op(SetImm); break;
	case OK_GetGlobalP:Check23Op(GetGlobalP); break;
	case OK_GetGlobal:Check23Op(GetGlobal); break;
	case OK_SetGlobal:Check23Op(SetGlobal); break;
	case OK_AddImm:
	{
		int value = getInt(0);
		if(value > 0 && value < 256){
			current = "Add1 " + to_string(value);
		}
		else if(value >= -32768 && value < 32768){
			current = "Add2 " + to_string(value);
		}
		else if(value > 0 && value < 0x1000000)
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
		int value = getInt(0);
		if(value > 0 && value < 256){
			current = "Mult1 " + to_string(value);
		}
		else if(value >= -32768 && value < 32768){
			current = "Mult2 " + to_string(value);
		}
		else if(value > 0 && value < 0x1000000)
		{
			current = "PushI24 " + to_string(value) + "\r\nMult";
		}
		else{
			current = "Push " + to_string(value) + "\r\nMult";
		}
		break;
	}
	case OK_Call:current = "Call @" + getString(); break;
	case OK_Jump: current = "Jump @" + getString(); break;
	case OK_JumpTrue: current = "Not\r\nJumpFalse @" + getString(); break;
	case OK_JumpFalse: PrintJump(False); break;
	case OK_JumpEQ: PrintJump(EQ); break;
	case OK_JumpNE: PrintJump(NE); break;
	case OK_JumpGT: PrintJump(GT); break;
	case OK_JumpGE: PrintJump(GE); break;
	case OK_JumpLT: PrintJump(LT); break;
	case OK_JumpLE: PrintJump(LE); break;
	case OK_Switch:{
		SwitchCaseIns** sCasePtr = (SwitchCaseIns**)storage;
		assert(sCasePtr && "Empty Switch Statement");
		SwitchCaseIns* sCase = *sCasePtr;
		current = "Switch [" + to_string(sCase->value) + " @" + sCase->loc + "]";
		sCase = sCase->next;
		while(sCase)
		{
			current += ":[" + to_string(sCase->value) + " @" + sCase->loc + "]";
			sCase = sCase->next;
		}
		break;
	}
	case OK_PushString:
		current = "PushString \"" + getString() + "\""; break;
	case OK_StrCopy:
		current = "StrCopy " + to_string(getUShort(0)); break;
	case OK_ItoS:
		current = "ItoS " + to_string(getUShort(0)); break;
	case OK_StrAdd:
		current = "StrAdd " + to_string(getUShort(0)); break;
	case OK_StrAddI:
		current = "StrAddI " + to_string(getUShort(0)); break;
	case OK_MemCpy: current = "MemCpy"; break;
	case OK_PCall: current = "PCall"; break;
	case OK_Label: current = "\r\n:" + getString(); break; //make labels have a line break
	case OK_LabelLoc: current = "GetLoc(\"" + getString() + "\")"; break;
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
#undef PrintJump
}

void Opcode::addSwitchCase(int caseVal, string jumpLoc)
{
	assert(opcodeKind == OK_Switch && "AddSwitchCase must be called on switches");
	SwitchCaseIns** curCasePtr = (SwitchCaseIns**)&storage;
	int count = 0;
	while(*curCasePtr)
	{
		assert(caseVal != (*curCasePtr)->value && "Duplicate switch case found");
		curCasePtr = &(*curCasePtr)->next;
		count++;
	}
	assert(count < 256 && "Too many switch cases in statement");
	SwitchCaseIns* newCase = new SwitchCaseIns();
	newCase->loc = jumpLoc;
	newCase->value = caseVal;
	newCase->next = NULL;
	*curCasePtr = newCase;
}

FunctionData::~FunctionData()
{
	for (size_t i = 0; i < Instructions.size();i++)
	{
		delete Instructions[i];
	}
}

void FunctionData::AddOpcode(Opcode * op)
{
	Instructions.push_back(op);
}

void FunctionData::AddOpcodeWithComment(Opcode * op, string comment)
{
#ifdef _DEBUG
	op->setComment(comment);
#endif
	Instructions.push_back(op);
}
bool FunctionData::endsWithInlineReturn(unsigned position) const
{
	return Instructions.size() && Instructions.back()->GetKind() == OK_Jump && Instructions.back()->getString() == to_string(position);
}

void FunctionData::setUsed()
{
	if (!used)
	{
		used = true;
		for(auto fdata : usedFuncs)
		{
			fdata->setUsed();
		}
	}
	
}

string FunctionData::toString() const
{
	stringstream stream;
	stream << "\r\n:" << name.substr(1) << "\r\nFunction " << pcount << " " << stackSize << endl;
	for(size_t i = 0; i < Instructions.size(); i++)
	{
		stream << *Instructions[i] << endl;
	}
	stream << endl;
	return stream.str();
}

void FunctionData::addSwitchCase(int caseVal, string jumpLoc) const
{
	assert(Instructions.size() && "Instruction stakck empty, cant add switch case");
	Instructions.back()->addSwitchCase(caseVal, jumpLoc);
}

void FunctionData::addUsedFunc(FunctionData * func)
{
	if(find(usedFuncs.begin(), usedFuncs.end(), func) == usedFuncs.end())
	{
		usedFuncs.push_back(func);
	}
}

ostream & operator<<(ostream & stream, const FunctionData & fdata)
{
	stream << "\r\n:" << fdata.name.substr(1) << "\r\nFunction " << fdata.pcount << " " << fdata.stackSize << endl;
	for(size_t i = 0; i < fdata.Instructions.size(); i++)
	{
		stream << *fdata.Instructions[i] << endl;
	}
	stream << endl;
	return stream;
}
