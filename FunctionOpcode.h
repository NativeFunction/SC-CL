#pragma once
#include <llvm/ADT/StringRef.h>
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

enum OpcodeKind{
	OK_Null,
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
	OK_GetHash,
	OK_JumpTable //Gets compiled as a PushString(V)/PushArrayP(RDR)
	//do these really need including
	//OK_Catch
	//OK_Throw
};

class FunctionData;

struct StringStorage
{
private:
	char* pointer;
	size_t length;
public:
	std::string toString()const
	{
		return std::string(pointer, length);
	}
	/*llvm::StringRef toStringRef()const
	{
	return llvm::StringRef(pointer, length);
	}*/
	StringStorage(std::string str)
	{
		length = str.length();
		pointer = new char[length + 1];
		memcpy(pointer, str.c_str(), length + 1);
	}
	StringStorage(llvm::StringRef stringRef)
	{
		length = stringRef.size();
		pointer = new char[length + 1];
		memcpy(pointer, stringRef.data(), length + 1);
	}
	const char *data() const
	{
		return pointer;
	}
	size_t size()const
	{
		return length;
	}
	~StringStorage()
	{
		delete[] pointer;
	}
	friend std::ostream& operator << (std::ostream& stream, const StringStorage& string) {
		stream.write(string.pointer, string.size());
		return stream;
	}
};

struct SwitchCaseStorage
{
private:
	int _caseVal;
	std::string _jumpLoc;
	SwitchCaseStorage* _next;
public:
	SwitchCaseStorage(int caseVal, std::string jumpLoc) : _caseVal(caseVal), _jumpLoc(jumpLoc), _next(NULL) {}
	~SwitchCaseStorage()
	{
		if (_next)
			delete _next;
	}

	std::string getCaseLocation()const { return _jumpLoc; }
	int getCaseValue()const { return _caseVal; }
	bool hasNextCase()const { return _next; }
	const SwitchCaseStorage *getNextCase()const { return _next; }
	void setNextCase(SwitchCaseStorage* next)
	{
		assert(!_next && "Already a next case defined");
		_next = next;
	}
	void setNextCase(int caseVal, std::string jumpLoc)
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
	StringStorage* _defaultJumpLoc;//to be set at the end of the switch
public:
	SwitchStorage(): _count(0), _first(NULL), _last(NULL), _defaultJumpLoc(NULL){}
	~SwitchStorage()
	{
		if (_first)
		{
			delete _first;
		}
		if (_defaultJumpLoc)
		{
			delete _defaultJumpLoc;
		}
	}

	void addCase(int caseVal, std::string caseLoc)
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
	void setDefaultJumpLoc(std::string defCase)
	{
		assert(!_defaultJumpLoc && "Default jump case alread specified");
		_defaultJumpLoc = new StringStorage(defCase);
	}
	void setDefaultJumpLoc(llvm::StringRef defCase)
	{
		assert(!_defaultJumpLoc && "Default jump case alread specified");
		_defaultJumpLoc = new StringStorage(defCase);
	}
	bool hasDefaultJumpLoc()const{ return _defaultJumpLoc; }//only would occur when you have a switch statement with > 255 cases
	const StringStorage* getDefaultJumpLoc()const{ return _defaultJumpLoc; }

};

struct NativeStorage
{
private:
	uint64_t _hash;
	StringStorage *_name;
	uint8_t _pCount, _rCount;
public:
	NativeStorage(std::string name, uint64_t hash, uint8_t pCount, uint8_t rCount) :
		_hash(hash),
		_name(new StringStorage(name)),
		_pCount(pCount),
		_rCount(rCount)
	{
	}
	NativeStorage(std::string name, uint8_t pCount, uint8_t rCount) :
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
	std::string getName()const { if (hasName())return _name->toString(); return std::string(); }
	uint64_t getHash()const { return _hash; }
	uint8_t getParamCount()const { return _pCount; }
	uint8_t getReturnCount()const { return _rCount; }
};

struct JumpTableStorage
{
private:
	std::vector<StringStorage*> jumpLocs;
public:
	JumpTableStorage(){}
	uint32_t getByteSize()const{ return jumpLocs.size() << 2; }
	uint32_t getItemCount()const{ return jumpLocs.size(); }
	void addJumpLoc(std::string jumpLoc){ jumpLocs.push_back(new StringStorage(jumpLoc)); }
	void addJumpLoc(llvm::StringRef jumpLoc){ jumpLocs.push_back(new StringStorage(jumpLoc)); }
	void addJumpLoc(StringStorage* jumpLoc){ jumpLocs.push_back(jumpLoc); }
	const StringStorage* getJumpLoc(unsigned index)
	{
		assert(index >= 0 && index < jumpLocs.size() && "Index out of range for jump table");
		return jumpLocs[index];
	}
	std::string getJumpLocAsString(unsigned index)
	{
		assert(index >= 0 && index < jumpLocs.size() && "Index out of range for jump table");
		return jumpLocs[index]->toString();
	}
	~JumpTableStorage()
	{
		for(auto item : jumpLocs)
		{
			delete item;
		}
	}
};

class Opcode
{
	friend class FunctionData;
	OpcodeKind opcodeKind;
#ifdef _DEBUG
	StringStorage *_comment = NULL;
#endif
	Opcode(OpcodeKind kind) : opcodeKind(kind){ }
	void setString(std::string str);
	void setInt(int value);
	void setFloat(float value);
	void setShort(int16_t value, int offset);
	void setUShort(uint16_t value, int offset);
	void setByte(uint8_t value, int offset);
	void setKind(OpcodeKind newKind){ opcodeKind = newKind; }
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
		JumpTableStorage *jTable;
	}storage = { 0,0,0,0 };
public:

	~Opcode();
	OpcodeKind getKind() const{ return opcodeKind; }
	void setComment(std::string comment);
	std::string getComment() const;
	bool hasComment() const;
	std::string getString() const;
	int getInt() const;
	float getFloat() const;
	int16_t getShort(int offset) const;
	uint16_t getUShort(int offset) const;
	uint8_t getByte(int offset) const;
	int getSizeEstimate() const;
	std::string toString() const;

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
	bool tryPopInt(int& result);
	bool tryPop2Floats(float& f1, float& f2);
	std::string name;
	uint32_t hash;
	uint8_t pcount;
	uint8_t rcount;
	uint16_t stackSize = 2;
	bool used = false;
	bool _processed = false;
	bool _isBuiltIn = false;
	std::vector<Opcode *> Instructions;
	std::vector<FunctionData *> usedFuncs;
	bool allowUnsafe = false;
public:
	
	FunctionData(std::string name, uint8_t pcount, uint8_t rcount) : name(name), hash(Utils::Hashing::JoaatCased((char*)name.c_str())), pcount(pcount), rcount(rcount)
	{
	}
	~FunctionData();
	void pushComment(std::string comment);
	void AddSimpleOp(OpcodeKind operation);
	bool endsWithReturn() const{ return Instructions.size() && Instructions.back()->getKind() == OK_Return; }//this will get confused by if else having a return, but it will just return false when there actually is a return so no harm
	bool endsWithInlineReturn(std::string position) const;
	void RemoveLast(){ Instructions.pop_back(); }
	uint8_t getParamCount()const { return pcount; }
	uint8_t getReturnCount()const{ return rcount; }
	uint16_t getStackSize()const { return stackSize; }
	void setStackSize(uint16_t newSize){
		stackSize = newSize;
	}
	uint32_t getHash()const{ return hash; }
	std::string getName()const{ return name; }
	void setUsed();
	bool IsUsed()const{ return used; }
	friend std::ostream& operator << (std::ostream& stream, const FunctionData& fdata);
	std::string toString() const;
	void addSwitchCase(int caseVal, std::string jumpLoc);
	void setSwitchDefaultCaseLoc(std::string jumpLoc);
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
	void setProcessed()
	{
		_processed = true;
		optimisePushBytes();
	}
	bool isBuiltIn()const{ return _isBuiltIn; }
	void setBuiltIn(){ _isBuiltIn = true; }

	void codeLayoutRandomisation(int maxBlockSize = 10, int minBlockSize = 2, bool keepEndReturn = true);

	void setUnsafe(){ allowUnsafe = true; }
	bool isUnsafe()const{ return allowUnsafe; }
	void optimisePushBytes();

#pragma region CreateOpcodes
	void addOpNop(uint16_t nopCount)
	{
		assert(nopCount > 0 && nopCount <= 4096 && "Nop Count out of range");
		Opcode* op = new Opcode(OK_Nop);
		op->setUShort(nopCount, 0);
		Instructions.push_back(op);
	}
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
		assert(bitIndex >= 0 && bitIndex <= 31 && "bitindex must be between 0 and 31");
		int temp;
		if (tryPopInt(temp))
		{
			addOpPushInt((temp & (1 << bitIndex)) != 0);
		}
		else
		{
			Opcode* op = new Opcode(OK_PushInt);
			op->setInt((int)(1 << bitIndex));
			Instructions.push_back(op);
			Instructions.push_back(new Opcode(OK_And));
			addOpIsNotZero();
		}
	}
	void addOpBitSet(uint8_t bitIndex)
	{
		assert(bitIndex >= 0 && bitIndex <= 31 && "bitindex must be between 0 and 31");
		Instructions.push_back(new Opcode(OK_Dup));
		Instructions.push_back(new Opcode(OK_PGet));
		Opcode* op = new Opcode(OK_PushInt);
		op->setInt((int)(1 << bitIndex));
		Instructions.push_back(op);
		Instructions.push_back(new Opcode(OK_Or));
		Instructions.push_back(new Opcode(OK_PeekSet));
		Instructions.push_back(new Opcode(OK_Drop));
	}
	void addOpBitReset(uint8_t bitIndex)
	{
		assert(bitIndex >= 0 && bitIndex <= 31 && "bitindex must be between 0 and 31");
		Instructions.push_back(new Opcode(OK_Dup));
		Instructions.push_back(new Opcode(OK_PGet));
		Opcode* op = new Opcode(OK_PushInt);
		op->setInt(~((int)(1 << bitIndex)));
		Instructions.push_back(op);
		Instructions.push_back(new Opcode(OK_And));
		Instructions.push_back(new Opcode(OK_PeekSet));
		Instructions.push_back(new Opcode(OK_Drop));
	}
	void addOpBitFlip(uint8_t bitIndex)
	{
		assert(bitIndex >= 0 && bitIndex <= 31 && "bitindex must be between 0 and 31");
		Instructions.push_back(new Opcode(OK_Dup));
		Instructions.push_back(new Opcode(OK_PGet));
		Opcode* op = new Opcode(OK_PushInt);
		op->setInt((int)(1 << bitIndex));
		Instructions.push_back(op);
		Instructions.push_back(new Opcode(OK_Xor));
		Instructions.push_back(new Opcode(OK_PeekSet));
		Instructions.push_back(new Opcode(OK_Drop));
	}
	void addOpIsNotZero();
	void addOpGetConv(int size, bool isSigned);
	void addOpSetConv(int size);
#pragma endregion 

	void addOpDup(){ Instructions.push_back(new Opcode(OK_Dup)); }
	void addOpDrop();
	void addOpNative(std::string name, uint8_t pCount, uint8_t rCount);
	void addOpNative(uint64_t hash, uint8_t pCount, uint8_t rCount);
	void addOpNative(std::string name, uint64_t hash, uint8_t pCount, uint8_t rCount);
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
	void addOpGetFrame(uint16_t index);
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
	void addOpGetStatic(uint16_t index);
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
	void addOpGetGlobal(int index);
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

	void addOpCall(std::string fName)
	{
		Opcode* op = new Opcode(OK_Call);
		op->setString(fName);
		Instructions.push_back(op);
	}
#pragma region Jumps
	void addOpJump(std::string loc)
	{
		Opcode* op = new Opcode(OK_Jump);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpTrue(std::string loc)
	{
		addOpNot();
		addOpJumpFalse(loc);
	}
	void addOpJumpFalse(std::string loc);
	void addOpJumpEQ(std::string loc)
	{
		Opcode* op = new Opcode(OK_JumpEQ);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpNE(std::string loc)
	{
		Opcode* op = new Opcode(OK_JumpNE);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpGT(std::string loc)
	{
		Opcode* op = new Opcode(OK_JumpGT);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpGE(std::string loc)
	{
		Opcode* op = new Opcode(OK_JumpGE);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpLT(std::string loc)
	{
		Opcode* op = new Opcode(OK_JumpLT);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJumpLE(std::string loc)
	{
		Opcode* op = new Opcode(OK_JumpLE);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpJump(unsigned int rawEncoding){ addOpJump(std::to_string(rawEncoding)); }
	void addOpJumpTrue(unsigned int rawEncoding){ addOpJumpTrue(std::to_string(rawEncoding)); }
	void addOpJumpFalse(unsigned int rawEncoding){ addOpJumpFalse(std::to_string(rawEncoding)); }
	void addOpJumpEQ(unsigned int rawEncoding){ addOpJumpEQ(std::to_string(rawEncoding)); }
	void addOpJumpNE(unsigned int rawEncoding){ addOpJumpNE(std::to_string(rawEncoding)); }
	void addOpJumpGT(unsigned int rawEncoding){ addOpJumpGT(std::to_string(rawEncoding)); }
	void addOpJumpGE(unsigned int rawEncoding){ addOpJumpGE(std::to_string(rawEncoding)); }
	void addOpJumpLT(unsigned int rawEncoding){ addOpJumpLT(std::to_string(rawEncoding)); }
	void addOpJumpLE(unsigned int rawEncoding){ addOpJumpLE(std::to_string(rawEncoding)); }
#pragma endregion
	
	void addOpSwitch()
	{
		Opcode* op = new Opcode(OK_Switch);
		op->storage.switchCase = new SwitchStorage();
		Instructions.push_back(op);
	}
	void addOpPushString(std::string str)
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
	void addOpLabel(std::string loc)
	{
		Opcode* op = new Opcode(OK_Label);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpLabel(unsigned int rawEncoding){ addOpLabel(std::to_string(rawEncoding)); }
	void addOpLabelLoc(std::string loc)
	{
		Opcode* op = new Opcode(OK_LabelLoc);
		op->setString(loc);
		Instructions.push_back(op);
	}
	void addOpFuncLoc(std::string funcName)
	{
		Opcode* op = new Opcode(OK_FuncLoc);
		op->setString(funcName);
		Instructions.push_back(op);
	}
	void addOpLabelLoc(unsigned int rawEncoding){ addOpLabelLoc(std::to_string(rawEncoding)); }
	void addOpGetHash();
	void addOpJumpTable()
	{
		Opcode* op = new Opcode(OK_JumpTable);
		op->storage.jTable = new JumpTableStorage();
		Instructions.push_back(op);
	}
	void addJumpTableLoc(std::string jumpLoc)
	{
		assert(Instructions.size() && Instructions.back()->getKind() == OK_JumpTable && "Cannot add a jump table case when last instruction isnt a jump table");
		Instructions.back()->storage.jTable->addJumpLoc(jumpLoc);
	}
	void addJumpTableLoc(llvm::StringRef jumpLoc)
	{
		assert(Instructions.size() && Instructions.back()->getKind() == OK_JumpTable && "Cannot add a jump table case when last instruction isnt a jump table");
		Instructions.back()->storage.jTable->addJumpLoc(jumpLoc);
	}

#pragma endregion
};

#undef SimpleOpCheck