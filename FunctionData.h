#pragma once
#include "Opcode.h"
#include "StaticData.h"


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

class Script;

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
	std::vector<StaticData*> _usedStatics;
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
	void setUsed(Script& scriptBase);
	bool IsUsed()const{ return used; }
	friend std::ostream& operator << (std::ostream& stream, const FunctionData& fdata);
	std::string toString() const;
	void addSwitchCase(int caseVal, std::string jumpLoc);
	void setSwitchDefaultCaseLoc(std::string jumpLoc);
	void addUsedFunc(FunctionData *func);
	void addUsedStatic(StaticData *staticData);
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

	void codeLayoutRandomisation(int maxBlockSize = 10, int minBlockSize = 2, bool keepEndReturn = true, bool makeJumpTable = false);

	void setUnsafe(){ allowUnsafe = true; }
	bool isUnsafe()const{ return allowUnsafe; }
	void optimisePushBytes();
	void moveInto(std::vector<Opcode*>& source);
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
	void addOpGetStaticP(StaticData* staticData)
	{
		Opcode* op = new Opcode(OK_GetStaticP);
		op->storage.staticData = staticData;
		Instructions.push_back(op);
	}
	void addOpGetStatic(StaticData* staticData)
	{
		Opcode* op = new Opcode(OK_GetStatic);
		op->storage.staticData = staticData;
		Instructions.push_back(op);
	}
	void addOpSetStatic(StaticData* staticData)
	{
		Opcode* op = new Opcode(OK_SetStatic);
		op->storage.staticData = staticData;
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

	void addOpCall(FunctionData* callee)
	{
		addUsedFunc(callee);
		Opcode* op = new Opcode(OK_Call);
		op->storage.functionData = callee;
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
	void addOpFuncLoc(FunctionData* function)
	{
		addUsedFunc(function);
		Opcode* op = new Opcode(OK_FuncLoc);
		op->storage.functionData = function;
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
	void addOpGoToStack()
	{
		assert(Instructions.size() && "Cannot add a GoToStack when instruction stack is empty");
#ifdef USE_OPTIMISATIONS
		if (Instructions.back()->getKind() == OK_LabelLoc)
		{
			Instructions.back()->setKind(OK_Jump);
		}
		else
#endif
		{
			Instructions.push_back(new Opcode(OK_GoToStack));
		}

	}

#pragma endregion
};

#undef SimpleOpCheck