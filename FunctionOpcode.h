#pragma once
#include <string>
#include <vector>
#include <cassert>
#include "Utils.h"

#define USE_OPTIMISATIONS

#ifdef USE_OPTIMISATIONS
#define SimpleOpCheck(Op, OpName) int i1, i2; \
if (tryPop2Ints(i1, i2)) \
{ \
	addOpPushInt(i1 ##Op i2); \
} \
else \
{ \
	Instructions.push_back(new Opcode(OK_##OpName)); \
}
#define SimpleFloatOpCheck(Op, OpName) float f1, f2; \
if (tryPop2Floats(f1, f2)) \
{ \
	addOpPushFloat(f1 ##Op f2); \
} \
else \
{ \
	Instructions.push_back(new Opcode(OK_##OpName)); \
}
#else
#define SimpleOpCheck(Op, OpName) Instructions.push_back(new Opcode(OK_##OpName))
#define SimpleFloatOpCheck(Op, OpName) Instructions.push_back(new Opcode(OK_##OpName))
#endif


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
	OK_FuncLoc,
	OK_ShiftLeft,
	OK_ShiftRight,
	OK_GetHash
	//do these really need including
	//OK_Catch
	//OK_Throw
};

class FunctionData;


struct SwitchCaseStorage
{
private:
	int _caseVal;
	string _jumpLoc;
	SwitchCaseStorage* _next;
public:
	SwitchCaseStorage(int caseVal, string jumpLoc) : _caseVal(caseVal), _jumpLoc(jumpLoc), _next(NULL) {}
	~SwitchCaseStorage()
	{
		if (_next)
			delete _next;
	}
	string getCaseLocation()const { return _jumpLoc; }
	int getCaseValue()const { return _caseVal; }
	bool hasNextCase()const { return _next; }
	const SwitchCaseStorage *getNextCase()const { return _next; }
	void setNextCase(SwitchCaseStorage* next)
	{
		assert(!_next && "Already a next case defined");
		_next = next;
	}
	void setNextCase(int caseVal, string jumpLoc)
	{
		assert(!_next && "Already a next case defined");
		_next = new SwitchCaseStorage(caseVal, jumpLoc);
	}
};
struct SwitchStorage
{
private:
	uint32_t _count;
	SwitchCaseStorage *_first, *_last;//keep track of last for faster access
public:
	SwitchStorage(): _count(0), _first(NULL), _last(NULL){}
	~SwitchStorage()
	{
		if (_first)
		{
			delete _first;
		}
	}

	void addCase(int caseVal, string caseLoc)
	{
		_count++;
		assert(_count < 256 && "Error switch has too many cases");
		if (!_first)
		{
			_first = new SwitchCaseStorage(caseVal, caseLoc);
			_last = _first;
		}else
		{
			SwitchCaseStorage* next = new SwitchCaseStorage(caseVal, caseLoc);
			_last->setNextCase(next);
			_last = next;
		}
	}
	const SwitchCaseStorage* getFirstCase() const { return _first; }
	uint32_t getCount() const{ return _count; }

};
struct StringStorage
{
private:
	char* pointer;
	int length;
public:
	string toString()const
	{
		return string(pointer, length);
	}
	StringStorage(string str)
	{
		length = str.length();
		pointer = new char[length + 1];
		memcpy(pointer, str.c_str(), length + 1);
	}
	~StringStorage()
	{
		delete[] pointer;
	}
};
struct NativeStorage
{
private:
	uint64_t _hash;
	StringStorage *_name;
	uint8_t _pCount, _rCount;
public:
	NativeStorage(string name, uint64_t hash, uint8_t pCount, uint8_t rCount) :
		_hash(hash),
		_name(new StringStorage(name)),
		_pCount(pCount),
		_rCount(rCount)
	{
	}
	NativeStorage(string name, uint8_t pCount, uint8_t rCount) :
		_hash((!strnicmp(name.c_str(), "unk_0x", 6) ? strtoull(name.c_str() + 6, NULL, 16) : Utils::Hashing::Joaat(name.c_str()))),
		_name(new StringStorage(name)),
		_pCount(pCount),
		_rCount(rCount)
	{
	}
	NativeStorage(uint64_t hash, uint8_t pCount, uint8_t rCount) :
		_hash(hash),
		_name(NULL),
		_pCount(pCount),
		_rCount(rCount)
	{
	}
	~NativeStorage()
	{
		if (_name)
			delete _name;
	}
	bool hasName()const { return _name; }
	string getName()const { if (hasName())return _name->toString(); return string(); }
	uint64_t getHash()const { return _hash; }
	uint8_t getParamCount()const { return _pCount; }
	uint8_t getReturnCount()const { return _rCount; }
};


class Opcode
{
	friend class FunctionData;
	OpcodeKind opcodeKind;
#ifdef _DEBUG
	StringStorage *_comment = NULL;
#endif
	Opcode(OpcodeKind kind) : opcodeKind(kind){ }
	void setString(string str);
	void setInt(int value);
	void setFloat(float value);
	void setShort(int16_t value, int offset);
	void setUShort(uint16_t value, int offset);
	void setByte(uint8_t value, int offset);
	void setKind(OpcodeKind newKind){ opcodeKind = newKind; }
	void setPBytesCount(uint8_t count)
	{
		assert(opcodeKind == OK_PushBytes && "setPBytesCount can only be called on PushBytes");
		assert(count == 2 || count == 3 && "setPBytes must be called with 2 or 3 count");
		setByte(count, 0);
	}
	union
	{
		char u8[sizeof(void*)];
		uint16_t u16[sizeof(void*) / 2];
		int16_t i16[sizeof(void*) / 2];
		int32_t i32;
		uint32_t u32;
		float f32;
		SwitchStorage *switchCase;
		NativeStorage *native;
		StringStorage *string;
	}storage = { 0,0,0,0 };
public:

	~Opcode();
	OpcodeKind getKind() const{ return opcodeKind; }
	void setComment(string comment);
	string getComment() const;
	bool hasComment() const;
	string getString() const;
	int getInt() const;
	float getFloat() const;
	int16_t getShort(int offset) const;
	uint16_t getUShort(int offset) const;
	uint8_t getByte(int offset) const;
	uint8_t getPBytesCount() const
	{
		assert(opcodeKind == OK_PushBytes && "getPBytesCount can only be called on PushBytes");
		return getByte(0);
	}
	int getSizeEstimate() const;
	string toString() const;

	const SwitchStorage *getSwitch() const
	{
		assert(getKind() == OK_Switch && "getSwitch not called on Switch Opcode");
		return storage.switchCase;
	}
	const NativeStorage *getNative() const
	{
		assert(getKind() == OK_Native && "getNative not called on Switch Opcode");
		return storage.native;
	}

	friend std::ostream& operator << (std::ostream& stream, const Opcode& opcode) {
		stream << opcode.toString();
		return stream;
	}
};

class FunctionData
{
	bool tryPop2Ints(int& i1, int& i2);
	bool tryPop2Floats(float& f1, float& f2);
	string name;
	uint32_t hash;
	uint8_t pcount;
	uint8_t rcount;
	uint16_t stackSize = 2;
	bool used = false;
	bool _processed = false;
	bool _isBuiltIn = false;
	vector<Opcode *> Instructions;
	vector<FunctionData *> usedFuncs;
public:
	
	FunctionData(string name, uint8_t pcount, uint8_t rcount) : name(name), hash(Utils::Hashing::JoaatCased((char*)name.c_str())), pcount(pcount), rcount(rcount)
	{
	}
	~FunctionData();
	void pushComment(string comment);
	void AddSimpleOp(OpcodeKind operation);
	bool endsWithReturn() const{ return Instructions.size() && Instructions.back()->getKind() == OK_Return; }//this will get confused by if else having a return, but it will just return false when there actually is a return so no harm
	bool endsWithInlineReturn(string position) const;
	void RemoveLast(){ Instructions.pop_back(); }
	uint8_t getParamCount()const { return pcount; }
	uint8_t getReturnCount()const{ return rcount; }
	uint16_t getStackSize()const { return stackSize; }
	void setStackSize(uint16_t newSize){
		stackSize = newSize;
	}
	uint32_t getHash()const{ return hash; }
	string getName()const{ return name; }
	void setUsed();
	bool IsUsed()const{ return used; }
	friend std::ostream& operator << (std::ostream& stream, const FunctionData& fdata);
	string toString() const;
	void addSwitchCase(int caseVal, string jumpLoc);
	void addUsedFunc(FunctionData *func);
	int getSizeEstimate(int incDecl) const;//only to be used when seeing if a function should be inlined
	const Opcode *getInstruction(size_t index)const{
		assert(index < Instructions.size() && "Instruction out of range");
		return Instructions[index];
	}
	size_t getInstructionCount() const{
		return Instructions.size();
	}
	bool isProcessed()const{ return _processed; }
	void setProcessed(){ _processed = true; }
	bool isBuiltIn()const{ return _isBuiltIn; }
	void setBuiltIn(){ _isBuiltIn = true; }

	void controlFlowConfusion();

#pragma region CreateOpcodes
	void addOpNop(){ Instructions.push_back(new Opcode(OK_Nop)); }
#pragma region MathOpcodes
	void addOpAdd();
	void addOpSub();
	void addOpMult();
	void addOpDiv(bool *isZeroDivDetected = nullptr);
	void addOpMod(){ SimpleOpCheck(%, Mod); }
	void addOpNot();
	void addOpNeg();
	void addOpCmpEq(){ SimpleOpCheck(==, CmpEq); }
	void addOpCmpNe(){ SimpleOpCheck(!= , CmpNe); }
	void addOpCmpGt(){ SimpleOpCheck(> , CmpGt); }
	void addOpCmpGe(){ SimpleOpCheck(>= , CmpGe); }
	void addOpCmpLt(){ SimpleOpCheck(< , CmpLt); }
	void addOpCmpLe(){ SimpleOpCheck(<= , CmpLe); }
	void addOpFAdd();
	void addOpFSub();
	void addOpFMult();
	void addOpFDiv(bool *isZeroDivDetected = nullptr);
	void addOpFMod(){ Instructions.push_back(new Opcode(OK_FMod)); }
	void addOpFNeg();
	void addOpFCmpEq(){ SimpleFloatOpCheck(== , FCmpEq); }
	void addOpFCmpNe(){ SimpleFloatOpCheck(!= , FCmpNe); }
	void addOpFCmpGt(){ SimpleFloatOpCheck(> , FCmpGt); }
	void addOpFCmpGe(){ SimpleFloatOpCheck(>= , FCmpGe); }
	void addOpFCmpLt(){ SimpleFloatOpCheck(< , FCmpLt); }
	void addOpFCmpLe(){ SimpleFloatOpCheck(<= , FCmpLe); }
	void addOpVAdd(){ Instructions.push_back(new Opcode(OK_VAdd)); }
	void addOpVSub(){ Instructions.push_back(new Opcode(OK_VSub)); }
	void addOpVMult(){ Instructions.push_back(new Opcode(OK_VMult)); }
	void addOpVDiv(){ Instructions.push_back(new Opcode(OK_VDiv)); }
	void addOpVNeg(){ Instructions.push_back(new Opcode(OK_VNeg)); }
	void addOpAnd(){ SimpleOpCheck(& , And); }
	void addOpOr(){ SimpleOpCheck(|, Or); }
	void addOpXor(){ SimpleOpCheck(^ , Xor); }
	void addOpItoF();
	void addOpFtoI();
	void addOpFtoV(){ Instructions.push_back(new Opcode(OK_FtoV)); }
	void addOpPushInt(int immediate);
	void addOpPushFloat(float immediate)
	{
		Opcode* op = new Opcode(OK_PushFloat);
		op->setFloat(immediate);
		Instructions.push_back(op);
	}
	void addOpShiftLeft(){ SimpleOpCheck(<< , ShiftLeft); }
	void addOpShiftLeft(uint8_t shiftCount)
	{
		assert(shiftCount >= 0 && shiftCount <= 31 && "shiftCount must be between 0 and 31");
		addOpPushInt(shiftCount);
		Instructions.push_back(new Opcode(OK_ShiftLeft));
	}
	void addOpShiftRight(){ SimpleOpCheck(>> , ShiftRight); }
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
	void addOpIsNotZero();
	void addOpGetConv(int size, bool isSigned);
	void addOpSetConv(int size);
#pragma endregion 

	void addOpDup(){ Instructions.push_back(new Opcode(OK_Dup)); }
	void addOpDrop();
	void addOpNative(string name, uint8_t pCount, uint8_t rCount);
	void addOpNative(uint64_t hash, uint8_t pCount, uint8_t rCount);
	void addOpNative(string name, uint64_t hash, uint8_t pCount, uint8_t rCount);
	void addOpReturn()
	{
		Opcode* op = new Opcode(OK_Return);
		op->setByte(pcount, 0);
		op->setByte(rcount, 1);
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
	
	void addOpSwitch()
	{
		Opcode* op = new Opcode(OK_Switch);
		op->storage.switchCase = new SwitchStorage();
		Instructions.push_back(op);
	}
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
	void addOpFuncLoc(string funcName)
	{
		Opcode* op = new Opcode(OK_FuncLoc);
		op->setString(funcName);
		Instructions.push_back(op);
	}
	void addOpLabelLoc(unsigned int rawEncoding){ addOpLabelLoc(to_string(rawEncoding)); }
	void addOpGetHash();

#pragma endregion
};

#undef SimpleOpCheck