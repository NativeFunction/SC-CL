#pragma once
#include "Compiler/Opcode.h"
#include "ClangParsing/Helpers/StaticData.h"
#include "Utils\ConstExpr.h"

#define SimpleOpCheck(Op, OpName) if (getOptLevel() > OptimisationLevel::OL_None){ \
	int i1, i2; \
	if (tryPop2Ints(i1, i2)) \
	{ \
		addOpPushInt((i1) Op (i2)); \
	} \
	else { \
		Instructions.push_back(new Opcode(OK_##OpName)); \
	} \
} else { \
	Instructions.push_back(new Opcode(OK_##OpName)); \
}
#define SimpleFloatOpCheck(Op, OpName) if (getOptLevel() > OptimisationLevel::OL_None){ \
	float f1, f2; \
	if (tryPop2Floats(f1, f2)) \
	{ \
		addOpPushFloat((f1) Op (f2)); \
	} \
	else { \
		Instructions.push_back(new Opcode(OK_##OpName)); \
	} \
} else { \
	Instructions.push_back(new Opcode(OK_##OpName)); \
}

class Script;

class FunctionData
{
	
	std::string name;
	uint32_t hash;
	uint8_t pcount;
	uint8_t rcount;
	uint16_t stackSize = 2;
	struct{
		bool used : 1;
		bool processed : 1;
		bool isBuiltin : 1;
		bool allowUnsafe : 1;
		bool dontObf : 1;
	}bitSet = { false, false, false, false, false };
	std::vector<Opcode *> Instructions;
	std::vector<FunctionData *> usedFuncs;
	std::vector<StaticData*> _usedStatics;
	OptimisationLevel _optLevel = OptimisationLevel::OL_None;

	bool tryPop2Ints(int& i1, int& i2);
	bool tryPopInt(int& result);
	bool tryPop2Floats(float& f1, float& f2);
	void optimisePushBytes();
	void jumpThreading();
	void insertDrop(size_t index);
	void makeDrop(size_t index);
public:
	
	FunctionData(std::string name, uint8_t pcount, uint8_t rcount) : name(name), hash(Utils::Hashing::JoaatCased((char*)name.c_str())), pcount(pcount), rcount(rcount)
	{
	}
	~FunctionData();
	void pushComment(const std::string& comment);
	void pushCommentNewLine(const std::string& comment);
	void AddSimpleOp(OpcodeKind operation);
	bool endsWithReturn() const{ return Instructions.size() && Instructions.back()->getKind() == OK_Return; }//this will get confused by if else having a return, but it will just return false when there actually is a return so no harm
	bool endsWithInlineReturn(const std::string& position) const;
	void RemoveLast(){ Instructions.pop_back(); }
	uint8_t getParamCount()const { return pcount; }
	uint8_t getReturnCount()const{ return rcount; }
	uint16_t getStackSize()const { return stackSize; }
	void setStackSize(uint16_t newSize){
		stackSize = newSize;
	}
	uint32_t getHash()const{ return hash; }
	const std::string& getName()const{ return name; }
	void setUsed(Script& scriptBase);
	bool IsUsed()const{ return bitSet.used; }
	friend std::ostream& operator << (std::ostream& stream, const FunctionData& fdata);
	std::string toString() const;
	void addSwitchCase(int caseVal, const std::string& jumpLoc);
	void setSwitchDefaultCaseLoc(const std::string& jumpLoc);
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
	bool isProcessed()const{ return bitSet.processed; }
	void setProcessed()
	{
		bitSet.processed = true;
		optimisePushBytes();
		jumpThreading();
	}
	bool isBuiltIn()const{ return bitSet.isBuiltin; }
	void setBuiltIn(){ bitSet.isBuiltin = true; }

	bool getDontObfuscate()const{ return bitSet.dontObf; }
	void setDontObfuscate(){ bitSet.dontObf = true; }

	OptimisationLevel getOptLevel()const{ return _optLevel; }
	void setOptLevel(OptimisationLevel optLevel){ _optLevel = optLevel; }

	void codeLayoutRandomisation(const Script& scriptData, uint32_t maxBlockSize = 10, uint32_t minBlockSize = 2, bool keepEndReturn = true, bool makeJumpTable = false);

	void setUnsafe(){ bitSet.allowUnsafe = true; }
	bool isUnsafe()const{ return bitSet.allowUnsafe; }
	void moveInto(std::vector<Opcode*>& source);
#pragma region CreateOpcodes
	void addOpNop(uint16_t nopCount)
	{
		assert(nopCount > 0 && nopCount <= 4096 && "Nop Count out of range");
		Instructions.push_back(Opcode::makeUShortOpcode(OK_Nop, nopCount));
	}
#pragma region MathOpcodes
	void addOpAdd();
	void addOpSub();
	void addOpMult();
	void addOpDiv(bool *isZeroDivDetected);
	void addOpDiv() { addOpDiv(nullptr); }
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
	void addOpFDiv(bool *isZeroDivDetected);
	void addOpFDiv() { addOpFDiv(nullptr); }
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
	void addOpPushInt(int immediate)
	{
		Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, immediate));
	}
	void addOpPushFloat(float immediate)
	{
		Instructions.push_back(Opcode::makeFloatOpcode(OK_PushFloat, immediate));
	}
	void addOpShiftLeft(){ SimpleOpCheck(<< , ShiftLeft); }
	void addOpShiftLeft(uint8_t shiftCount)
	{
		assert(shiftCount >= 0 && shiftCount <= 31 && "shiftCount must be between 0 and 31");
		if (getOptLevel() >= OptimisationLevel::OL_Trivial)
			if (!shiftCount)
				return;

		addOpPushInt(shiftCount);
		Instructions.push_back(new Opcode(OK_ShiftLeft));
	}
	void addOpShiftRight(){ SimpleOpCheck(>> , ShiftRight); }
	void addOpShiftRight(uint8_t shiftCount)
	{
		assert(shiftCount >= 0 && shiftCount <= 31 && "shiftCount must be between 0 and 31");
		if (getOptLevel() >= OptimisationLevel::OL_Trivial)
			if (!shiftCount)
				return;

		addOpPushInt(shiftCount);
		Instructions.push_back(new Opcode(OK_ShiftRight));
	}
	/*
	stack setup
	-------------------
	0: value to set (true/false)
	1: pointer to var
	-------------------
	NOTE: this function should be in its own scope
	*/
	void addOpSetBitStack(uint8_t bitIndex, size_t storageIndex)
	{
		TEST(bitIndex >= 0 && bitIndex <= 31, "bitindex must be between 0 and 31");
		TEST(Instructions.size(), "cannot add bitset to empty instruction stack");

		
		addOpSetFrame(storageIndex);
		pushComment("__bitset_set_temp_ptr");
		
		addOpPushInt(0);
		Instructions.push_back(new Opcode(OK_CmpNe));
		
		addOpNeg();
		addOpGetFrame(storageIndex);
		pushComment("__bitset_set_temp_ptr");
		Instructions.push_back(new Opcode(OK_PGet));
		Instructions.push_back(new Opcode(OK_Xor));
		Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
		Instructions.push_back(new Opcode(OK_And));
		addOpGetFrame(storageIndex);
		pushComment("__bitset_set_temp_ptr");
		Instructions.push_back(new Opcode(OK_PGet));
		Instructions.push_back(new Opcode(OK_Xor));
		addOpGetFrame(storageIndex);
		pushComment("__bitset_set_temp_ptr");
		Instructions.push_back(new Opcode(OK_PSet));

	}
	/*
	stack setup
	-------------------
	1: var value
	-------------------
	*/
	void addOpGetBitField(uint32_t bitIndex, uint32_t bitCount, BuildType BT, Platform P)
	{
		TEST(bitIndex + bitCount >= 1 && bitIndex + bitCount <= 32, "bitindex + bitCount must be between 1 and 32");
		TEST(Instructions.size(), "cannot add bitset to empty instruction stack");
		
		if (BT == BT_GTAIV_TLAD || BT == BT_GTAIV_TBOGT || BT == BT_GTAIV || BT == BT_GTAV)
		{
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, bitIndex));
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, Utils::Bitwise::bitCountToIntEnd(bitIndex, bitCount)));
			
			if (P == P_PC)
			{
				if (BT == BT_GTAV)
				{
					addOpNative(0x53158863FCC0893A, 3, 1);
				}
				else //GTAIV
				{
					addOpNative(0x58AE7C1D, 3, 1);
				}
			}
			else
			{
				addOpNative(JoaatConst("get_bits_in_range"), 3, 1);
			}
		}
		else
		{
			uint32_t rangeEnd = Utils::Bitwise::bitCountToIntEnd(bitIndex, bitCount);
			if ((int32_t)bitIndex > (int32_t)rangeEnd || bitIndex > 31 || rangeEnd > 31)
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 0));
			else
			{
				addOpShiftRight(bitIndex);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, (uint32_t)((1 << (rangeEnd - bitIndex + 1)) - 1)));
				Instructions.push_back(new Opcode(OK_And));
			}
		}
	}
	/*
	stack setup
	-------------------
	0: value to set (true/false)
	1: pointer to var
	-------------------
	NOTE: this function should be in its own scope
	*/
	void addOpSetBitField(int bitIndex, int bitCount, size_t storageIndex[2], BuildType BT, Platform P)
	{
		TEST(bitCount < 32, "set_bits_in_range is only valid for 31 bits");
		TEST(bitIndex + bitCount >= 1 && bitIndex + bitCount <= 32 , "bitindex + bitCount must be between 1 and 31");
		TEST(Instructions.size() >= 2, "cannot add bitset to empty instruction stack");

		addOpSetFrame(storageIndex[0]);//ptr
		pushComment("__bitset_set_temp_ptr");
		addOpSetFrame(storageIndex[1]);//value

		if (BT == BT_GTAIV_TLAD || BT == BT_GTAIV_TBOGT || BT == BT_GTAIV || BT == BT_GTAV)
		{
			addOpGetFrame(storageIndex[0]);
			pushComment("__bitset_set_temp_ptr");
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, bitIndex));
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, Utils::Bitwise::bitCountToIntEnd(bitIndex, bitCount)));
			addOpGetFrame(storageIndex[1]);
			pushComment("__bitset_set_temp_val");

			if (P == P_PC)
			{
				if (BT == BT_GTAV)
				{
					addOpNative(0x8EF07E15701D61ED, 4, 0);
				}
				else //GTAIV
				{
					addOpNative(0x14DD5F87, 4, 0);
				}
			}
			else
			{
				addOpNative(JoaatConst("set_bits_in_range"), 4, 0);
			}
		}
		else
		{
			static uint32_t bitfield_set_compatibility_counter = 0;
			std::string bitfield_set_compatibility_label = "__bitfield_set_compatibility" + std::to_string(bitfield_set_compatibility_counter);
			uint32_t rangeEnd = Utils::Bitwise::bitCountToIntEnd(bitIndex, bitCount);

			addOpGetFrame(storageIndex[1]);
			pushComment("__bitset_set_temp_val");
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 0));
			Instructions.push_back(new Opcode(OK_CmpGe));
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, ((int32_t)bitIndex <= (int32_t)rangeEnd && bitIndex <= 31 && rangeEnd <= 31)));
			Instructions.push_back(new Opcode(OK_And));
			addOpJumpFalse(bitfield_set_compatibility_label);
			addOpGetFrame(storageIndex[1]);
			pushComment("__bitset_set_temp_val");
			addOpShiftLeft(bitIndex);
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, (uint32_t)~(((1 << (rangeEnd - bitIndex + 1)) - 1) << bitIndex)));
			addOpGetFrame(storageIndex[0]);
			pushComment("__bitset_set_temp_ptr");
			Instructions.push_back(new Opcode(OK_PGet));
			Instructions.push_back(new Opcode(OK_And));
			Instructions.push_back(new Opcode(OK_Or));
			addOpGetFrame(storageIndex[0]);
			pushComment("__bitset_set_temp_ptr");
			Instructions.push_back(new Opcode(OK_PSet));
			addOpLabel(bitfield_set_compatibility_label);
			bitfield_set_compatibility_counter++;

		}

	}
	/*
	stack setup
	-------------------
	0: bitfield value
	1: value to be added by or
	-------------------
	*/
	void addOpAddBitField(int bitIndex, int bitCount)
	{
		TEST(bitIndex + bitCount >= 1 && bitIndex + bitCount <= 32, "bitindex + bitCount must be between 1 and 32");
		TEST(Instructions.size() >= 2, "cannot add bitset to empty instruction stack");

		Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, Utils::Bitwise::revbitmask(bitCount)));
		Instructions.push_back(new Opcode(OK_And));
		addOpShiftLeft(bitIndex);
		Instructions.push_back(new Opcode(OK_Or));

	}
	void addOpIsBitSet(uint8_t bitIndex)
	{
		TEST(bitIndex >= 0 && bitIndex <= 31, "bitindex must be between 0 and 31");
		int temp;
		if (tryPopInt(temp))
		{
			addOpPushInt((temp & (1 << bitIndex)) != 0);
		}
		else
		{
			Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
			Instructions.push_back(new Opcode(OK_And));
			addOpIsNotZero();
		}
	}
	void addOpBitSet(uint8_t bitIndex)
	{
		TEST(bitIndex >= 0 && bitIndex <= 31, "bitindex must be between 0 and 31");
		TEST(Instructions.size(), "cannot add bitset to empty instruction stack");
		Opcode* back = Instructions.back();
		switch(back->getKind())
		{
			case OK_GetFrameP:
				back->setKind(OK_GetFrame);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpOr();
				Instructions.push_back(Opcode::makeUShortOpcode(OK_SetFrame, back->getUShort(0)));
				break;
			case OK_GetStaticPRaw:
				back->setKind(OK_GetStaticRaw);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpOr();
				Instructions.push_back(Opcode::makeUShortOpcode(OK_SetStaticRaw, back->getUShort(0)));
				break;
			case OK_GetStaticP:
				back->setKind(OK_GetStatic);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpOr();
				Instructions.push_back(Opcode::makeStaticOpcode(OK_SetStatic, new OpStaticStorage(*back->getStaticData())));
				break;
			case OK_GetGlobalP:
				back->setKind(OK_GetGlobal);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpOr();
				Instructions.push_back(Opcode::makeIntOpcode(OK_SetGlobal, back->getInt()));
				break;
			default:
				Instructions.push_back(new Opcode(OK_Dup));
				Instructions.push_back(new Opcode(OK_PGet));
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				Instructions.push_back(new Opcode(OK_Or));
				Instructions.push_back(new Opcode(OK_PeekSet));
				Instructions.push_back(new Opcode(OK_Drop));
				break;
		}
	}
	void addOpBitReset(uint8_t bitIndex)
	{
		TEST(bitIndex >= 0 && bitIndex <= 31, "bitindex must be between 0 and 31");
		TEST(Instructions.size(), "cannot add bitreset to empty instruction stack");
		Opcode* back = Instructions.back();
		switch (back->getKind())
		{
			case OK_GetFrameP:
				back->setKind(OK_GetFrame);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, ~(int)(1 << bitIndex)));
				addOpAnd();
				Instructions.push_back(Opcode::makeUShortOpcode(OK_SetFrame, back->getUShort(0)));
				break;
			case OK_GetStaticPRaw:
				back->setKind(OK_GetStaticRaw);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, ~(int)(1 << bitIndex)));
				addOpAnd();
				Instructions.push_back(Opcode::makeUShortOpcode(OK_SetStaticRaw, back->getUShort(0)));
				break;
			case OK_GetStaticP:
				back->setKind(OK_GetStatic);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, ~(int)(1 << bitIndex)));
				addOpAnd();
				Instructions.push_back(Opcode::makeStaticOpcode(OK_SetStatic, new OpStaticStorage(*back->getStaticData())));
				break;
			case OK_GetGlobalP:
				back->setKind(OK_GetGlobal);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, ~(int)(1 << bitIndex)));
				addOpAnd();
				Instructions.push_back(Opcode::makeIntOpcode(OK_SetGlobal, back->getInt()));
				break;
			default:
				Instructions.push_back(new Opcode(OK_Dup));
				Instructions.push_back(new Opcode(OK_PGet));
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, ~(int)(1 << bitIndex)));
				Instructions.push_back(new Opcode(OK_And));
				Instructions.push_back(new Opcode(OK_PeekSet));
				Instructions.push_back(new Opcode(OK_Drop));
				break;
		}
	}
	void addOpBitFlip(uint8_t bitIndex)
	{
		TEST(bitIndex >= 0 && bitIndex <= 31, "bitindex must be between 0 and 31");
		TEST(Instructions.size(), "cannot add bitflip to empty instruction stack");
		Opcode* back = Instructions.back();
		switch (back->getKind())
		{
			case OK_GetFrameP:
				back->setKind(OK_GetFrame);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpXor();
				Instructions.push_back(Opcode::makeUShortOpcode(OK_SetFrame, back->getUShort(0)));
				break;
			case OK_GetStaticPRaw:
				back->setKind(OK_GetStaticRaw);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpXor();
				Instructions.push_back(Opcode::makeUShortOpcode(OK_SetStaticRaw, back->getUShort(0)));
				break;
			case OK_GetStaticP:
				back->setKind(OK_GetStatic);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpXor();
				Instructions.push_back(Opcode::makeStaticOpcode(OK_SetStatic, new OpStaticStorage(*back->getStaticData())));
				break;
			case OK_GetGlobalP:
				back->setKind(OK_GetGlobal);
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				addOpXor();
				Instructions.push_back(Opcode::makeIntOpcode(OK_SetGlobal, back->getInt()));
				break;
			default:
				Instructions.push_back(new Opcode(OK_Dup));
				Instructions.push_back(new Opcode(OK_PGet));
				Instructions.push_back(Opcode::makeIntOpcode(OK_PushInt, 1 << bitIndex));
				Instructions.push_back(new Opcode(OK_Xor));
				Instructions.push_back(new Opcode(OK_PeekSet));
				Instructions.push_back(new Opcode(OK_Drop));
				break;
		}
	}
	void addOpIsNotZero();
	void addOpGetConv(const Script& scriptData, int size, bool isSigned);
	void addOpSetConv(const Script& scriptData, int size);
#pragma endregion 

	void addOpDup(){ Instructions.push_back(new Opcode(OK_Dup)); }
	void addOpDrop();
	void addOpNative(const std::string& name, uint8_t pCount, uint8_t rCount)
	{
		Instructions.push_back(Opcode::makeNativeOpcode(new NativeStorage(name, pCount, rCount)));
	}
	void addOpNative(uint64_t hash, uint8_t pCount, uint8_t rCount)
	{
		Instructions.push_back(Opcode::makeNativeOpcode(new NativeStorage(hash, pCount, rCount)));
	}
	void addOpNative(const std::string& name, uint64_t hash, uint8_t pCount, uint8_t rCount)
	{
		Instructions.push_back(Opcode::makeNativeOpcode(new NativeStorage(name, hash, pCount, rCount)));
	}
	void addOpReturn()
	{
		Instructions.push_back(Opcode::make2ByteOpcode(OK_Return, pcount, rcount));
	}
	void addOpReturn(uint8_t stackSize, uint8_t returnCount)
	{
		Instructions.push_back(Opcode::make2ByteOpcode(OK_Return, stackSize, returnCount));
	}
	void addOpPGet();
	void addOpPSet();
	void addOpPeekSet(){ Instructions.push_back(new Opcode(OK_PeekSet)); }
	void addOpToStack(){ Instructions.push_back(new Opcode(OK_ToStack)); }
	void addOpFromStack(){ Instructions.push_back(new Opcode(OK_FromStack)); }
	void addOpGetArrayP(uint16_t itemSize)
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_GetArrayP, itemSize));
	}
	void addOpGetArray(uint16_t itemSize)
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_GetArray, itemSize));
	}
	void addOpSetArray(uint16_t itemSize)
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_SetArray, itemSize));
	}
	void addOpGetFrameP(uint16_t index)
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_GetFrameP, index));
	}
	void addOpGetFrame(uint16_t index);
	void addOpSetFrame(uint16_t index)
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_SetFrame, index));
	}
	void addOpGetStaticP(StaticData* staticData)
	{
		Instructions.push_back(Opcode::makeStaticOpcode(OK_GetStaticP, new OpStaticStorage(staticData)));
	}
	void addOpGetStaticPRaw(uint16_t index)
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_GetStaticPRaw, index));
	}
	void addOpGetStatic(StaticData* staticData)
	{
		Instructions.push_back(Opcode::makeStaticOpcode(OK_GetStatic, new OpStaticStorage(staticData)));
	}
	void addOpGetStaticRaw(uint16_t index);
	void addOpSetStatic(StaticData* staticData)
	{
		Instructions.push_back(Opcode::makeStaticOpcode(OK_SetStatic, new OpStaticStorage(staticData)));
	}
	void addOpSetStaticRaw(uint16_t index)
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_SetStaticRaw, index));
	}
	void addOpGetGlobalP(int index)
	{
		Instructions.push_back(Opcode::makeIntOpcode(OK_GetGlobalP, index));
	}
	void addOpGetGlobal(int index);
	void addOpSetGlobal(int index)
	{
		Instructions.push_back(Opcode::makeIntOpcode(OK_SetGlobal, index));
	}
	void addOpAddImm(int immediate);
	void addOpMultImm(int immediate);
	void addOpFAddImm(float immediate);
	void addOpFMultImm(float immediate);
	void addOpGetImmPStack(){ Instructions.push_back(new Opcode(OK_GetImmPStack)); }
	void addOpGetImmP(uint16_t index);
	void addOpGetImm(uint16_t index);
	void addOpSetImm(uint16_t index);

	void addOpCall(FunctionData* callee)
	{
		addUsedFunc(callee);
		Instructions.push_back(Opcode::makeFunctionOpcode(OK_Call, callee));
	}
#pragma region Jumps
	void addOpJump(const std::string& loc)
	{
		if (getOptLevel() > OptimisationLevel::OL_Trivial && Instructions.size()){
			//this optimisation will make control flow look weird if there was code straight after the jump
			//but that code would never get executed so the end result would be the same.
			//Its main use is for things like in a loop
			/*
			for (int i = 0;I<5;i++){
				if (!check(i)){
					continue;
				}
				doSomething(i);
			}			
			the condition will look like

			---GetFrame i
			---Call @Check
			---JumpFalse @ContinueJump

			instead of

			---GetFrame i
			---Call @Check
			---Not
			---JumpFalse @CondOK
			---Jump &ContinueJump

			:CondOk
			*/
			auto last = Instructions.back();
			switch (last->getKind()){
				case OK_JumpFalse:
					Instructions.pop_back();
					addOpJumpTrue(loc);
					delete last;
					break;
				case OK_JumpEQ:
					last->setKind(OK_JumpNE);
					last->setString(loc);
					break;
				case OK_JumpNE:
					last->setKind(OK_JumpEQ);
					last->setString(loc);
					break;
				case OK_JumpGT:
					last->setKind(OK_JumpLE);
					last->setString(loc);
					break;
				case OK_JumpGE:
					last->setKind(OK_JumpLT);
					last->setString(loc);
					break;
				case OK_JumpLT:
					last->setKind(OK_JumpGE);
					last->setString(loc);
					break;
				case OK_JumpLE:
					last->setKind(OK_JumpGT);
					last->setString(loc);
					break;
				default:
					Instructions.push_back(Opcode::makeStringOpcode(OK_Jump, loc));
					break;
			}
		}
		else{
			Instructions.push_back(Opcode::makeStringOpcode(OK_Jump, loc));
		}
	}
	void addOpJumpTrue(const std::string& loc)
	{
		addOpNot();
		addOpJumpFalse(loc);
	}
	void addOpJumpFalse(const std::string& loc);
	void addOpJumpEQ(const std::string& loc)
	{
		assert(Instructions.size() && "cannot add jumpEQ to empty instruction stack");
		auto back = Instructions.back();
		if (getOptLevel() > OptimisationLevel::OL_None && back->getKind() == OK_PushInt && back->getInt() == 0)
		{
			back->setKind(OK_JumpFalse);
			back->setString(loc);
		}
		else
		{
			Instructions.push_back(Opcode::makeStringOpcode(OK_JumpEQ, loc));
		}
		
	}
	void addOpJumpNE(const std::string& loc)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_JumpNE, loc));
	}
	void addOpJumpGT(const std::string& loc)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_JumpGT, loc));
	}
	void addOpJumpGE(const std::string& loc)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_JumpGE, loc));
	}
	void addOpJumpLT(const std::string& loc)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_JumpLT, loc));
	}
	void addOpJumpLE(const std::string& loc)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_JumpLE, loc));
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
		Instructions.push_back(Opcode::makeSwitchOpcode(new SwitchStorage()));
	}
	void addOpPushString(const std::string& str)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_PushString, str));
	}
	void addOpStrCopy(uint8_t size)
	{
		Instructions.push_back(Opcode::makeByteOpcode(OK_StrCopy, size));
	}
	void addOpItoS(uint8_t size)
	{
		Instructions.push_back(Opcode::makeByteOpcode(OK_ItoS, size));
	}
	void addOpStrAdd(uint8_t size)
	{
		Instructions.push_back(Opcode::makeByteOpcode(OK_StrAdd, size));
	}
	void addOpStrAddI(uint8_t size)
	{
		Instructions.push_back(Opcode::makeByteOpcode(OK_StrAddI, size));
	}
	void addOpMemCopy(){ Instructions.push_back(new Opcode(OK_MemCpy)); }
	void addOpPCall()
	{
		if (getOptLevel() > OptimisationLevel::OL_None && Instructions.back()->getKind() == OK_FuncLoc){
			Instructions.back()->setKind(OK_Call);
		}
		else{
			Instructions.push_back(new Opcode(OK_PCall));
		}
	}
	void addOpLabel(const std::string& loc)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_Label, loc));
	}
	void addOpLabel(unsigned int rawEncoding){ addOpLabel(std::to_string(rawEncoding)); }
	void addOpLabelLoc(const std::string& loc)
	{
		Instructions.push_back(Opcode::makeStringOpcode(OK_LabelLoc, loc));
	}
	void addOpFuncLoc(FunctionData* function)
	{
		addUsedFunc(function);
		Instructions.push_back(Opcode::makeFunctionOpcode(OK_FuncLoc, function));
	}
	void addOpLabelLoc(unsigned int rawEncoding){ addOpLabelLoc(std::to_string(rawEncoding)); }
	void addOpGetHash();
	void addOpJumpTable()
	{
		Instructions.push_back(Opcode::makeJumpTableOpcode(new JumpTableStorage()));
	}
	void addJumpTableLoc(const std::string& jumpLoc)
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

		if (getOptLevel() > OptimisationLevel::OL_None && Instructions.back()->getKind() == OK_LabelLoc)
		{
			Instructions.back()->setKind(OK_Jump);
		}
		else
		{
			Instructions.push_back(new Opcode(OK_GoToStack));
		}

	}
	void addOpPushNullPtr(){ Instructions.push_back(new Opcode(OK_PushNullPtr)); }

	void addOpPushConstArrayPtr(const Script& base, const std::vector<int>& values);
	void addOpPushConstArrayPtr(const Script& base, const std::vector<float>& values);

#pragma endregion
};

#undef SimpleOpCheck
#undef SimpleFloatOpCheck