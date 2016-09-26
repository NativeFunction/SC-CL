#pragma once
#include <string>
#include <vector>
#include "Utils.h"
using namespace std;
enum OpcodeKind{
	OK_Nop,
	OK_Add,
	OK_Sub,
	OK_Mult,
	OK_Div,
	OK_Mod,
	OK_Not,
	OK_Neg,
	OK_CmpEq,
	OK_CmpNe,
	OK_CmpGt,
	OK_CmpGe,
	OK_CmpLt,
	OK_CmpLe,
	OK_FAdd,
	OK_FSub,
	OK_FMult,
	OK_FDiv,
	OK_FMod,
	OK_FNeg,
	OK_FCmpEq,
	OK_FCmpNe,
	OK_FCmpGt,
	OK_FCmpGe,
	OK_FCmpLt,
	OK_FCmpLe,
	OK_VAdd,
	OK_VSub,
	OK_VMult,
	OK_VDiv,
	OK_VNeg,
	OK_And,
	OK_Or,
	OK_Xor,
	OK_FtoI,
	OK_ItoF,
	OK_FtoV,
	OK_PushInt,
	OK_PushFloat,
	OK_Dup,
	OK_Drop,
	OK_Native,
	//OK_Func,
	OK_Return,
	OK_PGet,
	OK_PSet,
	OK_PeekSet,
	OK_ToStack,
	OK_FromStack,
	OK_GetArrayP,
	OK_GetArray,
	OK_SetArray,
	OK_GetFrameP,
	OK_GetFrame,
	OK_SetFrame,
	OK_GetStaticP,
	OK_GetStatic,
	OK_SetStatic,
	OK_GetGlobalP,
	OK_GetGlobal,
	OK_SetGlobal,
	OK_AddImm,
	//OK_SubImm,//sees if operand can be made into adding a negative number
	
	OK_MultImm,
	OK_GetImmP,
	OK_GetImm,
	OK_SetImm,
	OK_Call,
	OK_Jump,
	OK_JumpTrue,//evaluates as not -> jumpfalse
	OK_JumpFalse,
	OK_JumpEQ,
	OK_JumpNE,
	OK_JumpGT,
	OK_JumpGE,
	OK_JumpLT,
	OK_JumpLE,
	OK_Switch,
	OK_PushString,
	OK_StrCopy,
	OK_ItoS,
	OK_StrAdd,
	OK_StrAddI,
	OK_MemCpy,
	OK_PCall,
	OK_Label, 
	OK_LabelLoc
	//do these really need including
	//OK_Catch
	//OK_Throw
};

class Opcode
{
	OpcodeKind opcodeKind;
	char storage[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
#ifdef _DEBUG
	char *_comment = NULL;
#endif
	Opcode(OpcodeKind kind) : opcodeKind(kind){ }
	void setULong(uint64_t value);//can only really be at offset 0
	void setString(string str);
	void setInt(int value, int offset);
	void setFloat(float value, int offset);
	void setShort(int16_t value, int offset);
	void setUShort(uint16_t value, int offset);
public:
	~Opcode();
	OpcodeKind GetKind(){ return opcodeKind; }
	static Opcode *AddSimpleOp(OpcodeKind operation)
	{
		switch(operation)
		{
			case OK_Nop:
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
			case OK_FtoI:
			case OK_ItoF:
			case OK_FtoV:
			case OK_Dup:
			case OK_Drop:
			case OK_PGet:
			case OK_PSet:
			case OK_PeekSet:
			case OK_ToStack:
			case OK_FromStack:
			case OK_MemCpy:
			case OK_PCall:
				return new Opcode(operation);
			default:
				assert(false && "Not a simple operation passed");
		}
		return new Opcode(OK_Nop);
	}
#ifdef _DEBUG
	void setComment(string comment);
	string getComment() const;
	bool hasComment() const;
#endif
	string getString() const;
	int getInt(int offset) const;
	float getFloat(int offset) const;
	int16_t getShort(int offset) const;
	uint16_t getUShort(int offset) const;
	uint64_t getULong() const;
	

	string toString() const;
	friend std::ostream& operator << (std::ostream& stream, const Opcode& opcode) {
		stream << opcode.toString();
		return stream;
	}
	void addSwitchCase(int caseVal, string jumpLoc);

#pragma region CreateOpcodes
	static Opcode *Nop(){ return new Opcode(OK_Nop);}
	#pragma region MathOpcodes
	static Opcode *Add(){ return new Opcode(OK_Add);}
	static Opcode *Sub(){ return new Opcode(OK_Sub);}
	static Opcode *Mult(){ return new Opcode(OK_Mult);}
	static Opcode *Div(){ return new Opcode(OK_Div); }
	static Opcode *Mod(){ return new Opcode(OK_Mod); }
	static Opcode *Not(){ return new Opcode(OK_Not); }
	static Opcode *Neg(){ return new Opcode(OK_Neg); }
	static Opcode *CmpEq(){ return new Opcode(OK_CmpEq);}
	static Opcode *CmpNe(){ return new Opcode(OK_CmpNe); }
	static Opcode *CmpGt(){ return new Opcode(OK_CmpGt); }
	static Opcode *CmpGe(){ return new Opcode(OK_CmpGe); }
	static Opcode *CmpLt(){ return new Opcode(OK_CmpLt); }
	static Opcode *CmpLe(){ return new Opcode(OK_CmpLe); }
	static Opcode *FAdd(){ return new Opcode(OK_FAdd); }
	static Opcode *FSub(){ return new Opcode(OK_FSub); }
	static Opcode *FMult(){ return new Opcode(OK_FMult); }
	static Opcode *FDiv(){ return new Opcode(OK_FDiv); }
	static Opcode *FMod(){ return new Opcode(OK_FMod); }
	static Opcode *FNeg(){ return new Opcode(OK_FNeg); }
	static Opcode *FCmpEq(){ return new Opcode(OK_FCmpEq); }
	static Opcode *FCmpNe(){ return new Opcode(OK_FCmpNe); }
	static Opcode *FCmpGt(){ return new Opcode(OK_FCmpGt); }
	static Opcode *FCmpGe(){ return new Opcode(OK_FCmpGe); }
	static Opcode *FCmpLt(){ return new Opcode(OK_FCmpLt); }
	static Opcode *FCmpLe(){ return new Opcode(OK_FCmpLe); }
	static Opcode *VAdd(){ return new Opcode(OK_VAdd); }
	static Opcode *VSub(){ return new Opcode(OK_VSub); }
	static Opcode *VMult(){ return new Opcode(OK_VMult); }
	static Opcode *VDiv(){ return new Opcode(OK_VDiv); }
	static Opcode *VNeg(){ return new Opcode(OK_VNeg); }
	static Opcode *And(){ return new Opcode(OK_And); }
	static Opcode *Or(){ return new Opcode(OK_Or); }
	static Opcode *Xor(){ return new Opcode(OK_Xor); }
	static Opcode *ItoF(){ return new Opcode(OK_ItoF); }
	static Opcode *FtoI(){ return new Opcode(OK_FtoI); }
	static Opcode *FtoV(){ return new Opcode(OK_FtoV); }
	static Opcode *PushInt(int immediate)
	{
		Opcode* op = new Opcode(OK_PushInt);
		op->setInt(immediate, 0);
		return op;
	}
	static Opcode *PushFloat(float immediate)
	{
		Opcode* op = new Opcode(OK_PushFloat);
		op->setFloat(immediate, 0);
		return op;
	}
#pragma endregion 


	static Opcode *Dup(){ return new Opcode(OK_Dup); }
	static Opcode *Drop(){ return new Opcode(OK_Drop); }
	static Opcode *Native(string name, uint16_t pCount, uint16_t rCount)
	{
		Opcode* op = new Opcode(OK_Native);
		if (!strnicmp(name.c_str(), "unk_0x", 6))
		{
			op->setULong(strtoull(name.c_str() + 6, NULL, 16));
		}else
		{
			op->setULong(Utils::Hashing::Joaat((char*)name.c_str()));
		}
		op->setUShort(pCount, 8);
		op->setUShort(rCount, 10);
		return op;
	}
	static Opcode *Native(uint64_t hash, uint16_t pCount, uint16_t rCount)
	{
		Opcode* op = new Opcode(OK_Native);
		op->setULong(hash);
		op->setUShort(pCount, 8);
		op->setUShort(rCount, 10);
		return op;
	}
/*	static Opcode *Function(string name, uint16_t pCount, uint16_t frameSize)
	{
		Opcode* op = new Opcode(OK_Func);;
		op->setString(name, 0);
		op->setUShort(pCount, 4);
		op->setUShort(frameSize, 6);
		return op;
	}*/
	static Opcode *Return(uint16_t pCount, uint16_t rCount)
	{
		Opcode* op = new Opcode(OK_Return);
		op->setUShort(pCount, 0);
		op->setUShort(rCount, 2);
		return op;
	}
	static Opcode *PGet(){ return new Opcode(OK_PGet); }
	static Opcode *PSet(){ return new Opcode(OK_PSet); }
	static Opcode *PeekSet(){ return new Opcode(OK_PeekSet); }
	static Opcode *ToStack(){ return new Opcode(OK_ToStack); }
	static Opcode *FromStack(){ return new Opcode(OK_FromStack); }
	static Opcode *GetArrayP(uint16_t itemSize)
	{
		Opcode* op = new Opcode(OK_GetArrayP);
		op->setUShort(itemSize, 0);
		return op;
	}
	static Opcode *GetArray(uint16_t itemSize)
	{
		Opcode* op = new Opcode(OK_GetArray);
		op->setUShort(itemSize, 0);
		return op;
	}
	static Opcode *SetArray(uint16_t itemSize)
	{
		Opcode* op = new Opcode(OK_SetArray);
		op->setUShort(itemSize, 0);
		return op;
	}
	static Opcode *GetFrameP(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetFrameP);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *GetFrame(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetFrame);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *SetFrame(uint16_t index)
	{
		Opcode* op = new Opcode(OK_SetFrame);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *GetStaticP(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetStaticP);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *GetStatic(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetStatic);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *SetStatic(uint16_t index)
	{
		Opcode* op = new Opcode(OK_SetStatic);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *GetGlobalP(int index)
	{
		Opcode* op = new Opcode(OK_GetGlobalP);
		op->setInt(index, 0);
		return op;
	}
	static Opcode *GetGlobal(int index)
	{
		Opcode* op = new Opcode(OK_GetGlobal);
		op->setInt(index, 0);
		return op;
	}
	static Opcode *SetGlobal(int index)
	{
		Opcode* op = new Opcode(OK_SetGlobal);
		op->setInt(index, 0);
		return op;
	}
	static Opcode *AddImm(int immediate)
	{
		Opcode* op = new Opcode(OK_AddImm);
		op->setInt(immediate, 0);
		return op;
	}
/*	static Opcode *SubImm(int immediate)
	{
		Opcode* op = new Opcode(OK_SubImm);
		op->setInt(immediate, 0);
		return op;
	}*/
	static Opcode *MultImm(int immediate)
	{
		Opcode* op = new Opcode(OK_MultImm);
		op->setInt(immediate, 0);
		return op;
	}
	
	static Opcode *GetImmP(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetImmP);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *GetImm(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetImm);
		op->setUShort(index, 0);
		return op;
	}
	static Opcode *SetImm(uint16_t index)
	{
		Opcode* op = new Opcode(OK_SetImm);
		op->setUShort(index, 0);
		return op;
	}

	static Opcode *Call(string fName)
	{
		Opcode* op = new Opcode(OK_Call);
		op->setString(fName);
		return op;
	}
#pragma region Jumps
	static Opcode *Jump(string loc)
	{
		Opcode* op = new Opcode(OK_Jump);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpTrue(string loc)
	{
		Opcode* op = new Opcode(OK_JumpTrue);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpFalse(string loc)
	{
		Opcode* op = new Opcode(OK_JumpFalse);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpEQ(string loc)
	{
		Opcode* op = new Opcode(OK_JumpEQ);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpNE(string loc)
	{
		Opcode* op = new Opcode(OK_JumpNE);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpGT(string loc)
	{
		Opcode* op = new Opcode(OK_JumpGT);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpGE(string loc)
	{
		Opcode* op = new Opcode(OK_JumpGE);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpLT(string loc)
	{
		Opcode* op = new Opcode(OK_JumpLT);
		op->setString(loc);
		return op;
	}
	static Opcode *JumpLE(string loc)
	{
		Opcode* op = new Opcode(OK_JumpLE);
		op->setString(loc);
		return op;
	}
	static Opcode *Jump(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_Jump);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpTrue(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpTrue);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpFalse(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpFalse);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpEQ(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpEQ);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpNE(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpNE);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpGT(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpGT);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpGE(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpGE);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpLT(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpLT);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *JumpLE(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_JumpLE);
		op->setString(to_string(rawEncoding));
		return op;
	}
#pragma endregion
	static Opcode *Switch(){ return new Opcode(OK_Switch); }//handle adding the cases later
	static Opcode *PushString(string str)
	{
		Opcode* op = new Opcode(OK_PushString);
		op->setString(str);
		return op;
	}
	static Opcode *StrCopy(uint16_t size)
	{
		Opcode* op = new Opcode(OK_StrCopy);
		op->setUShort(size, 0);
		return op;
	}
	static Opcode *ItoS(uint16_t size)
	{
		Opcode* op = new Opcode(OK_ItoS);
		op->setUShort(size, 0);
		return op;
	}
	static Opcode *StrAdd(uint16_t size)
	{
		Opcode* op = new Opcode(OK_StrAdd);
		op->setUShort(size, 0);
		return op;
	}
	static Opcode *StrAddI(uint16_t size)
	{
		Opcode* op = new Opcode(OK_StrAddI);
		op->setUShort(size, 0);
		return op;
	}
	static Opcode *MemCopy(){ return new Opcode(OK_MemCpy); }
	static Opcode *PCall(){ return new Opcode(OK_PCall); }
	static Opcode *Label(string loc)
	{
		Opcode* op = new Opcode(OK_Label);
		op->setString(loc);
		return op;
	}
	static Opcode *Label(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_Label);
		op->setString(to_string(rawEncoding));
		return op;
	}
	static Opcode *LabelLoc(string loc)
	{
		Opcode* op = new Opcode(OK_LabelLoc);
		op->setString(loc);
		return op;
	}
	static Opcode *LabelLoc(unsigned int rawEncoding)
	{
		Opcode* op = new Opcode(OK_LabelLoc);
		op->setString(to_string(rawEncoding));
		return op;
	}
#pragma endregion
};

class FunctionData
{
private:
	vector<Opcode *> Instructions;
	string name;
	uint32_t hash;
	uint16_t pcount;
	uint16_t stackSize = 2;
	bool used = false;
	vector<FunctionData *> usedFuncs;

public:
	FunctionData(string name, int pcount) : name(name), hash(Utils::Hashing::JoaatCased((char*)name.c_str())), pcount(pcount)
	{
	}
	~FunctionData();
	void AddOpcode(Opcode *op);
#ifdef _DEBUG
	void AddOpcodeWithComment(Opcode *op, string comment);
#endif
	bool endsWithReturn() const{ return Instructions.size() && Instructions.back()->GetKind() == OK_Return; }//this will get confused by if else having a return, but it will just return false when there actually is a return so no harm
	bool endsWithInlineReturn(unsigned position) const;
	void RemoveLast(){ Instructions.pop_back(); }
	uint16_t getPCount()const { return pcount; }
	uint16_t getStackSize()const { return stackSize; }
	void setPCount(uint16_t newSize){
		pcount = newSize;
	}
	void setStackSize(uint16_t newSize){
		stackSize = newSize;
	}
	uint32_t Hash()const{ return hash; }
	string Name()const{ return name; }
	void setUsed();
	bool IsUsed()const{ return used; }
	friend std::ostream& operator << (std::ostream& stream, const FunctionData& fdata);
	string toString() const;
	void addSwitchCase(int caseVal, string jumpLoc)const;
	void addUsedFunc(FunctionData *func);
};
