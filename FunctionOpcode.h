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
	OK_PushBytes,
	OK_PushFloat,
	OK_Dup,
	OK_Drop,
	OK_Native,
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
	OK_MultImm,
	OK_FAddImm,//simplify optimising
	OK_FMultImm,//simplify optimising
	OK_GetImmP,
	OK_GetImm,
	OK_SetImm,
	OK_Call,
	OK_Jump,
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
	OK_LabelLoc,
	OK_ShiftLeft,
	OK_ShiftRight
	//do these really need including
	//OK_Catch
	//OK_Throw
};

class FunctionData;

class Opcode
{
	friend class FunctionData;
	OpcodeKind opcodeKind;
	char storage[sizeof(void*)] = {0,0,0,0};
#ifdef _DEBUG
	char *_comment = NULL;
#endif
	Opcode(OpcodeKind kind) : opcodeKind(kind){ }
	void setString(string str);
	void setInt(int value);
	void setFloat(float value);
	void setShort(int16_t value, int offset);
	void setUShort(uint16_t value, int offset);
	void setByte(uint8_t value, int offset);
public:
	~Opcode();
	OpcodeKind GetKind() const{ return opcodeKind; }
	void setComment(string comment);
	string getComment() const;
	bool hasComment() const;
	string getString() const;
	int getInt() const;
	float getFloat() const;
	int16_t getShort(int offset) const;
	uint16_t getUShort(int offset) const;
	uint8_t getByte(int offset) const;
	int getSizeEstimate() const;
	

	string toString() const;
	friend std::ostream& operator << (std::ostream& stream, const Opcode& opcode) {
		stream << opcode.toString();
		return stream;
	}
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
	void pushComment(string comment);
	void AddSimpleOp(OpcodeKind operation);
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
	void addSwitchCase(int caseVal, string jumpLoc);
	void addUsedFunc(FunctionData *func);

#pragma region CreateOpcodes
	void addOpNop(){ Instructions.push_back(new Opcode(OK_Nop)); }
#pragma region MathOpcodes
	void addOpAdd();
	void addOpSub();
	void addOpMult();
	void addOpDiv(bool *isZeroDivDetected = nullptr);
	void addOpMod(){ Instructions.push_back(new Opcode(OK_Mod)); }
	void addOpNot();
	void addOpNeg();
	void addOpCmpEq(){ Instructions.push_back(new Opcode(OK_CmpEq)); }
	void addOpCmpNe(){ Instructions.push_back(new Opcode(OK_CmpNe)); }
	void addOpCmpGt(){ Instructions.push_back(new Opcode(OK_CmpGt)); }
	void addOpCmpGe(){ Instructions.push_back(new Opcode(OK_CmpGe)); }
	void addOpCmpLt(){ Instructions.push_back(new Opcode(OK_CmpLt)); }
	void addOpCmpLe(){ Instructions.push_back(new Opcode(OK_CmpLe)); }
	void addOpFAdd();
	void addOpFSub();
	void addOpFMult();
	void addOpFDiv(bool *isZeroDivDetected = nullptr);
	void addOpFMod(){ Instructions.push_back(new Opcode(OK_FMod)); }
	void addOpFNeg();
	void addOpFCmpEq(){ Instructions.push_back(new Opcode(OK_FCmpEq)); }
	void addOpFCmpNe(){ Instructions.push_back(new Opcode(OK_FCmpNe)); }
	void addOpFCmpGt(){ Instructions.push_back(new Opcode(OK_FCmpGt)); }
	void addOpFCmpGe(){ Instructions.push_back(new Opcode(OK_FCmpGe)); }
	void addOpFCmpLt(){ Instructions.push_back(new Opcode(OK_FCmpLt)); }
	void addOpFCmpLe(){ Instructions.push_back(new Opcode(OK_FCmpLe)); }
	void addOpVAdd(){ Instructions.push_back(new Opcode(OK_VAdd)); }
	void addOpVSub(){ Instructions.push_back(new Opcode(OK_VSub)); }
	void addOpVMult(){ Instructions.push_back(new Opcode(OK_VMult)); }
	void addOpVDiv(){ Instructions.push_back(new Opcode(OK_VDiv)); }
	void addOpVNeg(){ Instructions.push_back(new Opcode(OK_VNeg)); }
	void addOpAnd(){ Instructions.push_back(new Opcode(OK_And)); }
	void addOpOr(){ Instructions.push_back(new Opcode(OK_Or)); }
	void addOpXor(){ Instructions.push_back(new Opcode(OK_Xor)); }
	void addOpItoF(){ Instructions.push_back(new Opcode(OK_ItoF)); }
	void addOpFtoI(){ Instructions.push_back(new Opcode(OK_FtoI)); }
	void addOpFtoV(){ Instructions.push_back(new Opcode(OK_FtoV)); }
	void addOpPushInt(int immediate);
	void addOpPushFloat(float immediate)
	{
		Opcode* op = new Opcode(OK_PushFloat);
		op->setFloat(immediate);
		Instructions.push_back(op);
	}
	void addOpShiftLeft(){ Instructions.push_back(new Opcode(OK_ShiftLeft)); }
	void addOpShiftLeft(uint8_t shiftCount)
	{
		assert(shiftCount >= 0 && shiftCount <= 31 && "shiftCount must be between 0 and 31");
		addOpPushInt(shiftCount);
		Instructions.push_back(new Opcode(OK_ShiftLeft));
	}
	void addOpShiftRight(){ Instructions.push_back(new Opcode(OK_ShiftRight)); }
	void addOpShiftRight(uint8_t shiftCount)
	{
		assert(shiftCount >= 0 && shiftCount <= 31 && "shiftCount must be between 0 and 31");
		addOpPushInt(shiftCount);
		Instructions.push_back(new Opcode(OK_ShiftRight));
	}
	void addOpIsBitSet(uint8_t bitIndex)
	{
		//treat it as 2 instructions to simplify compiling
		assert(bitIndex >= 0 && bitIndex <= 31 && "bitindex must be between 0 and 31");
		Opcode* op = new Opcode(OK_PushInt);
		op->setInt((int)(1 << bitIndex));
		Instructions.push_back(op);
		Instructions.push_back(new Opcode(OK_And));
	}
#pragma endregion 


	void addOpDup(){ Instructions.push_back(new Opcode(OK_Dup)); }
	void addOpDrop();
	void addOpNative(string name, uint8_t pCount, uint8_t rCount);
	void addOpNative(uint64_t hash, uint8_t pCount, uint8_t rCount);
	void addOpNative(string name, uint64_t hash, uint8_t pCount, uint8_t rCount);
	void addOpReturn(uint8_t pCount, uint8_t rCount)
	{
		Opcode* op = new Opcode(OK_Return);
		op->setByte(pCount, 0);
		op->setByte(rCount, 1);
		Instructions.push_back(op);
	}
	void addOpPGet();
	void addOpPSet();
	void addOpPeekSet(){ Instructions.push_back(new Opcode(OK_PeekSet)); }
	void addOpToStack(){ Instructions.push_back(new Opcode(OK_ToStack)); }
	void addOpFromStack(){ Instructions.push_back(new Opcode(OK_FromStack)); }
	void addOpGetArrayP(uint16_t itemSize)
	{
		Opcode* op = new Opcode(OK_GetArrayP);
		op->setUShort(itemSize, 0);
		Instructions.push_back(op);
	}
	void addOpGetArray(uint16_t itemSize)
	{
		Opcode* op = new Opcode(OK_GetArray);
		op->setUShort(itemSize, 0);
		Instructions.push_back(op);
	}
	void addOpSetArray(uint16_t itemSize)
	{
		Opcode* op = new Opcode(OK_SetArray);
		op->setUShort(itemSize, 0);
		Instructions.push_back(op);
	}
	void addOpGetFrameP(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetFrameP);
		op->setUShort(index, 0);
		Instructions.push_back(op);
	}
	void addOpGetFrame(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetFrame);
		op->setUShort(index, 0);
		Instructions.push_back(op);
	}
	void addOpSetFrame(uint16_t index)
	{
		Opcode* op = new Opcode(OK_SetFrame);
		op->setUShort(index, 0);
		Instructions.push_back(op);
	}
	void addOpGetStaticP(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetStaticP);
		op->setUShort(index, 0);
		Instructions.push_back(op);
	}
	void addOpGetStatic(uint16_t index)
	{
		Opcode* op = new Opcode(OK_GetStatic);
		op->setUShort(index, 0);
		Instructions.push_back(op);
	}
	void addOpSetStatic(uint16_t index)
	{
		Opcode* op = new Opcode(OK_SetStatic);
		op->setUShort(index, 0);
		Instructions.push_back(op);
	}
	void addOpGetGlobalP(int index)
	{
		Opcode* op = new Opcode(OK_GetGlobalP);
		op->setInt(index);
		Instructions.push_back(op);
	}
	void addOpGetGlobal(int index)
	{
		Opcode* op = new Opcode(OK_GetGlobal);
		op->setInt(index);
		Instructions.push_back(op);
	}
	void addOpSetGlobal(int index)
	{
		Opcode* op = new Opcode(OK_SetGlobal);
		op->setInt(index);
		Instructions.push_back(op);
	}
	void addOpAddImm(int immediate);
	void addOpMultImm(int immediate);
	void addOpFAddImm(float immediate);
	void addOpFMultImm(float immediate);
	void addOpGetImmP(uint16_t index);
	void addOpGetImm(uint16_t index);
	void addOpSetImm(uint16_t index);

	void addOpCall(string fName)
	{
		Opcode* op = new Opcode(OK_Call);
		op->setString(fName);
		Instructions.push_back(op);
	}
#pragma region Jumps
	void addOpJump(string loc)
	{
		Opcode* op = new Opcode(OK_Jump);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpTrue(string loc)
	{
		addOpNot();
		addOpJumpFalse(loc);
	}
	void addOpJumpFalse(string loc);
	void addOpJumpEQ(string loc)
	{
		Opcode* op = new Opcode(OK_JumpEQ);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpNE(string loc)
	{
		Opcode* op = new Opcode(OK_JumpNE);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpGT(string loc)
	{
		Opcode* op = new Opcode(OK_JumpGT);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpGE(string loc)
	{
		Opcode* op = new Opcode(OK_JumpGE);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpLT(string loc)
	{
		Opcode* op = new Opcode(OK_JumpLT);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpLE(string loc)
	{
		Opcode* op = new Opcode(OK_JumpLE);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJump(unsigned int rawEncoding){ addOpJump(to_string(rawEncoding)); }
	void addOpJumpTrue(unsigned int rawEncoding){ addOpJumpTrue(to_string(rawEncoding)); }
	void addOpJumpFalse(unsigned int rawEncoding){ addOpJumpFalse(to_string(rawEncoding)); }
	void addOpJumpEQ(unsigned int rawEncoding){ addOpJumpEQ(to_string(rawEncoding)); }
	void addOpJumpNE(unsigned int rawEncoding){ addOpJumpNE(to_string(rawEncoding)); }
	void addOpJumpGT(unsigned int rawEncoding){ addOpJumpGT(to_string(rawEncoding)); }
	void addOpJumpGE(unsigned int rawEncoding){ addOpJumpGE(to_string(rawEncoding)); }
	void addOpJumpLT(unsigned int rawEncoding){ addOpJumpLT(to_string(rawEncoding)); }
	void addOpJumpLE(unsigned int rawEncoding){ addOpJumpLE(to_string(rawEncoding)); }
#pragma endregion
	void addOpSwitch(){ Instructions.push_back(new Opcode(OK_Switch)); }//handle adding the cases later
	void addOpPushString(string str)
	{
		Opcode* op = new Opcode(OK_PushString);
		op->setString(str);
		Instructions.push_back(op);
	}
	void addOpStrCopy(uint8_t size)
	{
		Opcode* op = new Opcode(OK_StrCopy);
		op->setByte(size, 0);
		Instructions.push_back(op);
	}
	void addOpItoS(uint8_t size)
	{
		Opcode* op = new Opcode(OK_ItoS);
		op->setByte(size, 0);
		Instructions.push_back(op);
	}
	void addOpStrAdd(uint8_t size)
	{
		Opcode* op = new Opcode(OK_StrAdd);
		op->setByte(size, 0);
		Instructions.push_back(op);
	}
	void addOpStrAddI(uint8_t size)
	{
		Opcode* op = new Opcode(OK_StrAddI);
		op->setByte(size, 0);
		Instructions.push_back(op);
	}
	void addOpMemCopy(){ Instructions.push_back(new Opcode(OK_MemCpy)); }
	void addOpPCall(){ Instructions.push_back(new Opcode(OK_PCall)); }
	void addOpLabel(string loc)
	{
		Opcode* op = new Opcode(OK_Label);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpLabel(unsigned int rawEncoding){ addOpLabel(to_string(rawEncoding)); }
	void addOpLabelLoc(string loc)
	{
		Opcode* op = new Opcode(OK_LabelLoc);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpLabelLoc(unsigned int rawEncoding){ addOpLabelLoc(to_string(rawEncoding)); }

#pragma endregion
};
