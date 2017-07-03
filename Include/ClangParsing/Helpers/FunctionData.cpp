#include <cassert>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_map>
#include <iterator>

#include "ClangParsing/GlobalDecls.h"
#include "ClangParsing/Helpers/FunctionData.h"
#include "ClangParsing/Helpers/Script.h"


using namespace std;

bool FunctionData::tryPop2Ints(int & i1, int & i2)
{
	int size = Instructions.size();
	if (size >= 2)
	{
		auto last = Instructions.back();
		if (last->getKind() == OK_PushInt){
			auto prev = Instructions[size - 2];
			switch (prev->getKind()){
				case OK_PushInt:
					i1 = prev->getInt();
					delete prev;
					i2 = last->getInt();
					delete prev;
					Instructions.pop_back();
					Instructions.pop_back();
					return true;
				case OK_GetFrame:
				{
					if (size >= 4){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_SetFrame && prev2->getUShort(0) == prev->getUShort(0)){
							auto prev3 = Instructions[size - 4];
							if (prev3->getKind() == OK_PushInt){
								i2 = last->getInt();
								delete last;
								i1 = prev3->getInt();
								delete prev;
								Instructions.pop_back();
								Instructions.pop_back();
								return true;
							}
						}
					}
				}
				break;
				case OK_GetStatic:
				{
					if (size >= 4){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_SetStatic && prev->getStaticData()->isEqual(*(prev2->getStaticData()))){
							auto prev3 = Instructions[size - 4];
							if (prev3->getKind() == OK_PushInt){
								i2 = last->getInt();
								delete last;
								i1 = prev3->getInt();
								delete prev;
								Instructions.pop_back();
								Instructions.pop_back();
								return true;
							}
						}
					}
				}
				break;
				case OK_GetStaticRaw:
				{
					if (size >= 4){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_SetStaticRaw && prev2->getUShort(0) == prev->getUShort(0)){
							auto prev3 = Instructions[size - 4];
							if (prev3->getKind() == OK_PushInt){
								i2 = last->getInt();
								delete last;
								i1 = prev3->getInt();
								delete prev;
								Instructions.pop_back();
								Instructions.pop_back();
								return true;
							}
						}
					}
				}
				break;
				case OK_GetGlobal:
				{
					if (size >= 4){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_SetGlobal && prev2->getInt() == prev->getInt()){
							auto prev3 = Instructions[size - 4];
							if (prev3->getKind() == OK_PushInt){
								i2 = last->getInt();
								delete last;
								i1 = prev3->getInt();
								delete prev;
								Instructions.pop_back();
								Instructions.pop_back();
								return true;
							}
						}
					}
				}
				break;
				default:
					return false;
			}
		}
	}
	return false;

}

bool FunctionData::tryPopInt(int& result)
{
	int size = Instructions.size();
	if (size)
	{
		auto last = Instructions.back();
		switch (last->getKind()){
			case OK_PushInt:
				result = last->getInt();
				delete last;
				Instructions.pop_back();
				return true;
			case OK_GetFrame:
			{
				if (size > 3){
					auto prev = Instructions[size - 2];
					if (prev->getKind() == OK_SetFrame && prev->getUShort(0) == last->getUShort(0)){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_PushInt){
							result = prev2->getInt();
							delete last;
							Instructions.pop_back();
							return true;
						}
					}
				}
			}
			break;
			case OK_GetStatic:
			{
				if (size > 3){
					auto prev = Instructions[size - 2];
					if (prev->getKind() == OK_SetStatic && last->getStaticData()->getStatic() == prev->getStaticData()->getStatic() && last->getStaticData()->getImmIndex() == prev->getStaticData()->getImmIndex()){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_PushInt){
							result = prev2->getInt();
							delete last;
							Instructions.pop_back();
							return true;
						}
					}
				}
			}
			break;
			case OK_GetStaticRaw:
			{
				if (size > 3){
					auto prev = Instructions[size - 2];
					if (prev->getKind() == OK_SetStaticRaw && prev->getUShort(0) == last->getUShort(0)){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_PushInt){
							result = prev2->getInt();
							delete last;
							Instructions.pop_back();
							return true;
						}
					}
				}
			}
			break;
			case OK_GetGlobal:
			{
				if (size > 3){
					auto prev = Instructions[size - 2];
					if (prev->getKind() == OK_SetGlobal && prev->getInt() == last->getInt()){
						auto prev2 = Instructions[size - 3];
						if (prev2->getKind() == OK_PushInt){
							result = prev2->getInt();
							delete last;
							Instructions.pop_back();
							return true;
						}
					}
				}
			}
			break;
			default:
				return false;
		}
	}
	return false;
}

bool FunctionData::tryPop2Floats(float & f1, float & f2)
{
	int size = Instructions.size();
	if (size > 1)
	{
		Opcode *last = Instructions[size - 1];
		Opcode *prev = Instructions[size - 2];
		if (last->getKind() == OK_PushFloat && prev->getKind() == OK_PushFloat)
		{
			f1 = prev->getFloat();
			f2 = last->getFloat();
			delete prev;
			delete last;
			Instructions.pop_back();
			Instructions.pop_back();
			return true;
		}
	}
	return false;
}

FunctionData::~FunctionData()
{
	for (size_t i = 0; i < Instructions.size();i++)
	{
		delete Instructions[i];
	}
}

void FunctionData::pushComment(const string& comment)
{
#ifdef _DEBUG
	if (Instructions.size()){//instruction stack can be empty in the rare case you're dropping the first instruction of a function
		Instructions.back()->setComment(comment);
	}
#endif
}
void FunctionData::pushCommentNewLine(const string& comment)
{
	#ifdef _DEBUG
	Instructions.push_back(new Opcode(OK_Null));
	Instructions.back()->setComment(comment);
	#endif
}

void FunctionData::addOpIsNotZero()
{
	if (getOptLevel() > OptimisationLevel::OL_None){
		assert(Instructions.size() && "Cannot add IsNotZero on an empty instruction stack");
		Opcode *last = Instructions.back();
		switch (last->getKind())
		{
			case OK_PushInt:
			case OK_PushFloat://kind of weird including this, but this is how it would be ran
				last->setInt(last->getInt() != 0);
				break;
			case OK_CmpEq:
			case OK_CmpNe:
			case OK_CmpGt:
			case OK_CmpGe:
			case OK_CmpLt:
			case OK_CmpLe:
			case OK_FCmpEq:
			case OK_FCmpNe:
			case OK_FCmpGt:
			case OK_FCmpGe:
			case OK_FCmpLt:
			case OK_FCmpLe:
			case OK_Not:
				//dont need to worry about these cases
				break;
			default:
				addOpPushInt(0);
				addOpCmpNe();
				break;
		}
	}
	else{
		addOpPushInt(0);
		addOpCmpNe();
	}
}

void FunctionData::addOpGetConv(const Script& scriptData, int size, bool isSigned)
{
	assert(size == 1 || size == 2);
	if (!(size == 1 || size == 2))
		return;

	const uint32_t extSW = size == 1 ? 0xFF000000 : size == 2 ? 0xFFFF0000 : 0;
	const string type = size == 1 ? "Char Type" : size == 2 ? "Short Type" : "";
	static uint32_t ExtSignWordLabelCounter = 0;

	if (scriptData.getBuildPlatform() != P_PC)
	{
		const uint32_t shiftSize = size == 1 ? 24 : size == 2 ? 16 : 0;
		addOpShiftRight(shiftSize);
	}
	else
	{
		const uint32_t andSize = size == 1 ? 0xFF : size == 2 ? 0xFFFF : 0;
		addOpPushInt(andSize);
		addOpAnd();//this only clears the right 2 bytes. if issues arise with the remaining 4 bytes that is why.
	}
	
	pushComment(type);
	if (isSigned)
	{
		addOpDup();
		addOpPushInt(size == 1 ? 127 : size == 2 ? 32767 : 0);
		addOpJumpLE("__ExtSignWord--noSign--" + to_string(ExtSignWordLabelCounter));
		addOpPushInt(extSW);
		addOpOr();
		pushComment("ExtSignWord");
		addOpLabel("__ExtSignWord--noSign--" + to_string(ExtSignWordLabelCounter++));
	}

}
void FunctionData::addOpSetConv(const Script& scriptData, int size)
{
	assert(size == 1 || size == 2);
	if (!(size == 1 || size == 2))
		return;

	const uint32_t shiftSize = size == 1 ? 24 : size == 2 ? 16 : 0;
	const string type = size == 1 ? "Char Type" : size == 2 ? "Short Type" : "";

	assert(Instructions.size() && "Cannot add convert a type on an empty instruction stack");
	Opcode *last = Instructions.back();
	if (getOptLevel() > OptimisationLevel::OL_None && last->getKind() == OK_PushInt)
	{
		if(scriptData.getBuildPlatform() != P_PC)
			last->setInt(last->getInt() << shiftSize);

	}
	else
	{
		if (scriptData.getBuildPlatform() != P_PC)
			addOpShiftLeft(shiftSize);

		pushComment(type);
	}



}
void FunctionData::AddSimpleOp(OpcodeKind operation)
{
	switch(operation)
	{
		//special handling cases
	case OK_Add:
		addOpAdd();
		break;
	case OK_Sub:
		addOpSub();
		break;
	case OK_Mult:
		addOpMult();
		break;
	case OK_Div:
		addOpDiv();
		break;
	case OK_Not:
		addOpNot();
		break;
	case OK_Neg:
		addOpNeg();
		break;
	case OK_FAdd:
		addOpFAdd();
		break;
	case OK_FSub:
		addOpFSub();
		break;
	case OK_FMult:
		addOpFMult();
		break;
	case OK_FDiv:
		addOpFDiv();
		break;
	case OK_FNeg:
		addOpFNeg();
		break;
	case OK_Drop:
		addOpDrop();
		break;
	case OK_PGet:
		addOpPGet();
		break;
	case OK_PSet:
		addOpPSet();
		break;
	case OK_Mod:
	case OK_CmpEq:
	case OK_CmpNe:
	case OK_CmpGt:
	case OK_CmpGe:
	case OK_CmpLt:
	case OK_CmpLe:
	case OK_FMod:
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
	case OK_ShiftLeft:
	case OK_ShiftRight:
	case OK_Dup:
	case OK_PeekSet:
	case OK_ToStack:
	case OK_FromStack:
	case OK_MemCpy:
	case OK_PCall:
		Instructions.push_back(new Opcode(operation));
		break;
	default:
		assert(false && "Not a simple operation passed");
	}
}
bool FunctionData::endsWithInlineReturn(const string& position) const
{
	return Instructions.size() && Instructions.back()->getKind() == OK_Jump && Instructions.back()->getString() == position;
}

void FunctionData::setUsed(Script& scriptBase)
{
	if (!bitSet.used)
	{
		bitSet.used = true;
		for(auto fdata : usedFuncs)
		{
			fdata->setUsed(scriptBase);
		}
		for(auto sdata: _usedStatics)
		{
			sdata->setUsed(scriptBase);
		}
	}
	
}

string FunctionData::toString() const
{
	stringstream stream;
	stream << "\r\n:" << name << "//>\r\nFunction " << (int)pcount << " " << (int)stackSize << "\r\n";
	for(size_t i = 0; i < Instructions.size(); i++)
	{
		if (Instructions[i]->getKind() == OK_Null)
		{
			if (Instructions[i]->hasComment())
			{
				stream << "//" + Instructions[i]->getComment() << "\r\n";
			}
		}
		else
		{
			stream << *Instructions[i] << "\r\n";
		}
	}
	stream << "//<\r\n";
	return stream.str();
}

void FunctionData::addSwitchCase(int caseVal, const string& jumpLoc)
{
	assert(Instructions.size() && "Instruction stack empty, cant add switch case");
	Opcode *end = Instructions.back();
	assert(end->getKind() == OK_Switch && "AddSwitchCase must be called on switches");
	if (end->storage.switchCase->getCount() < 255)
	{
		end->storage.switchCase->addCase(caseVal, jumpLoc);
	}
	else
	{
		assert(false && "Switch case too large");
	}
}

void FunctionData::setSwitchDefaultCaseLoc(const string& jumpLoc)
{
	assert(Instructions.size() && "Instruction stack empty, cant add switch case");
	Opcode *end = Instructions.back();
	assert(end->getKind() == OK_Switch && "AddSwitchCase must be called on switches");
	end->storage.switchCase->setDefaultJumpLoc(jumpLoc);
}

void FunctionData::addUsedFunc(FunctionData * func)
{
	if(find(usedFuncs.begin(), usedFuncs.end(), func) == usedFuncs.end())
	{
		usedFuncs.push_back(func);
	}
}

void FunctionData::addUsedStatic(StaticData * staticData)
{
	if (find(_usedStatics.begin(), _usedStatics.end(), staticData) == _usedStatics.end())
	{
		_usedStatics.push_back(staticData);
	}
}

int FunctionData::getSizeEstimate(int incDecl) const
{
	int size = 0;
	if (incDecl) size += 5;//fDecl
	for(int i = 0, _max = Instructions.size(); i < _max;i++)
	{
		size += Instructions[i]->getSizeEstimate();
	}
	return size;
}

void FunctionData::codeLayoutRandomisation(const Script& scriptData, uint32_t maxBlockSize, uint32_t minBlockSize, bool keepEndReturn, bool makeJumpTable)
{
	if (getDontObfuscate()){
		return;
	}
	int maxSize = Instructions.size();
	if (!maxSize)
		return;//sanity check
	if (isBuiltIn())
		return;
	int randMod = 1 + maxBlockSize - minBlockSize;
	assert(maxBlockSize > minBlockSize && "max block size must be greater than min block size");
	assert(minBlockSize >= 0 && "min block size must be positive");
	if (getSizeEstimate(0) > 30000)
	{
		return;//jumps may be screwed messed up if past 32768 size limit
	}
	auto randomEngine = default_random_engine(chrono::system_clock::now().time_since_epoch().count());
	vector<vector<Opcode*>> InstructionBuilder;
	int labelCounter = 0;
	
	Opcode* first = Instructions[0];
	bool isFirstNop = first->getKind() == OK_Nop;
	if (makeJumpTable)
	{
		int pcFrameIndex = 0;
		if (scriptData.getBuildType() == BT_GTAV && scriptData.getBuildPlatform() == P_PC)
		{
			pcFrameIndex = getStackSize();
			stackSize++;
		}
		int xorValue = randomEngine();
		
		vector<string> jumpTableLocations;
		vector<size_t> jumpTableRandomisation;
		auto JumpTable = new JumpTableStorage();
		JumpTable->setXORValue(xorValue);
		vector<Opcode*> jTableBlock;
		jTableBlock.push_back(Opcode::makeStringOpcode(OK_Label, "__builtin__jumpTable"));
		if (pcFrameIndex)
		{
			jTableBlock.push_back(Opcode::makeUShortOpcode(OK_SetFrame, pcFrameIndex));
		}
		jTableBlock.push_back(Opcode::makeJumpTableOpcode(JumpTable));
		if (pcFrameIndex)
		{
			jTableBlock.push_back(Opcode::makeUShortOpcode(OK_GetFrame, pcFrameIndex));
			//jTableBlock.push_back(new Opcode(OK_GetImmPStack));
			jTableBlock.push_back(new Opcode(OK_Add));
		}
		else{
			jTableBlock.push_back(new Opcode(OK_Add));
		}
		jTableBlock.push_back(new Opcode(OK_PGet));
		if (xorValue){
			jTableBlock.push_back(Opcode::makeIntOpcode(OK_PushInt, xorValue));
			jTableBlock.push_back(new Opcode(OK_Xor));
		}
		jTableBlock.push_back(new Opcode(OK_GoToStack));
		InstructionBuilder.push_back(jTableBlock);

		for (int i = (isFirstNop ? 1 : 0); i < maxSize;)
		{
			vector<Opcode*> block;
			block.push_back(Opcode::makeStringOpcode(OK_Label, "__builtin__controlFlowObsJumpTable_" + to_string(labelCounter++)));
			int bSize = (randomEngine() % randMod) + minBlockSize;
			for (int j = 0; j < bSize;j++)
			{
				if (i + j >= maxSize)
					break;
				if (Instructions[i+j]->getKind() == OK_Jump)
				{
					bSize = j + 1;
					break;
				}
			}
			if (i + bSize >= maxSize)
			{
				if (i + bSize > maxSize)
				{
					bSize = maxSize - i;
				}
				block.resize(bSize + 1);
				memcpy(&block[1], &Instructions[i], bSize * sizeof(Opcode*));
			}
			else
			{
				block.reserve(bSize + 2);
				block.resize(bSize + 1);
				if (bSize)
					memcpy(&block[1], &Instructions[i], bSize * sizeof(Opcode*));
				if (block[bSize]->getKind() != OK_Jump)
				{
					jumpTableLocations.push_back("__builtin__controlFlowObsJumpTable_" + to_string(labelCounter));
				}
				else
				{
					jumpTableLocations.push_back(block[bSize]->getString());//replace the jump with a jump table jump to add confusion
					block.pop_back();
				}
				jumpTableRandomisation.push_back(jumpTableRandomisation.size());
			}
			InstructionBuilder.push_back(block);
			i += bSize;
			shuffle(jumpTableRandomisation.begin(), jumpTableRandomisation.end(), randomEngine);
		}
		for (unsigned i = 0; i < jumpTableRandomisation.size();i++)
		{
			bool found = false;
			for (unsigned j = 0; j < jumpTableRandomisation.size();j++)
			{
				if (jumpTableRandomisation[i] == j)
				{
					found = true;
					JumpTable->addJumpLoc(jumpTableLocations[j]);
					//if (pcFrameIndex){
					//	InstructionBuilder[j + 1].push_back(Opcode::makeIntOpcode(OK_PushInt, i));
					//}
					//else{
						InstructionBuilder[j + 1].push_back(Opcode::makeIntOpcode(OK_PushInt, i * 4));
					//}
					InstructionBuilder[j+1].push_back(Opcode::makeStringOpcode(OK_Jump, "__builtin__jumpTable"));
					break;
				}
			}
			assert(found && "Not Found Correct Index");
		}
		Instructions.clear();
		if (isFirstNop)Instructions.push_back(first);
		//if (pcFrameIndex){
		//	addOpPushInt(JumpTable->getItemCount());
		//}
		//else{
			addOpPushInt(JumpTable->getItemCount() * 4);
		//}
		addOpJump("__builtin__jumpTable");

		JumpTable->addJumpLoc((string)"__builtin__controlFlowObsJumpTable_0");
		vector<size_t> randomiseIndexes;
		for (size_t i = 0; i < InstructionBuilder.size(); i++)
		{
			randomiseIndexes.push_back(i);
		}
		shuffle(randomiseIndexes.begin(), (keepEndReturn ? randomiseIndexes.end() - 1 : randomiseIndexes.end()), randomEngine);
		for (uint32_t i = 0; i < randomiseIndexes.size(); i++)
		{
			if (randomiseIndexes[i] == 0)
			{
				if (Instructions.back()->getKind() == OK_Jump)
				{
					Instructions.back()->setKind(OK_LabelLoc);	
					Instructions.push_back(new Opcode(OK_GoToStack));
				}
				
			}
			size_t size = InstructionBuilder[randomiseIndexes[i]].size();
			size_t iSize = Instructions.size();
			Instructions.resize(iSize + size);
			memcpy(&Instructions[iSize], &InstructionBuilder[randomiseIndexes[i]][0], size * sizeof(Opcode*));
		}
	}
	else
	{
		for (int i = (isFirstNop ? 1 : 0); i < maxSize;)
		{
			vector<Opcode*> block;
			block.push_back(Opcode::makeStringOpcode(OK_Label, "__builtin__controlFlowObs_" + to_string(labelCounter++)));
			int bSize = (randomEngine() % randMod) + minBlockSize;
			if (i + bSize >= maxSize)
			{
				if (i + bSize > maxSize)
				{
					bSize = maxSize - i;
				}
				block.resize(bSize + 1);
				memcpy(&block[1], &Instructions[i], bSize * sizeof(Opcode*));
			}
			else
			{
				block.reserve(bSize + 2);
				block.resize(bSize + 1);
				if (bSize)
					memcpy(&block[1], &Instructions[i], bSize * sizeof(Opcode*));
				if (block[bSize]->getKind() != OK_Jump)
				{
					block.push_back(Opcode::makeStringOpcode(OK_Jump, "__builtin__controlFlowObs_" + to_string(labelCounter)));
				}
			}
			InstructionBuilder.push_back(block);
			i += bSize;
		}
		Instructions.clear();
		if (isFirstNop)Instructions.push_back(first);
		vector<size_t> randomiseIndexes;
		for (size_t i = 0; i < InstructionBuilder.size(); i++)
		{
			randomiseIndexes.push_back(i);
		}
		shuffle(randomiseIndexes.begin(), (keepEndReturn ? randomiseIndexes.end() - 1 : randomiseIndexes.end()), randomEngine);
		if (randomiseIndexes[0] > 0)
		{
			Instructions.push_back(Opcode::makeStringOpcode(OK_Jump, "__builtin__controlFlowObs_0"));
		}
		else
		{
			InstructionBuilder[0][0]->makeNull();
		}
		for (uint32_t i = 0; i < randomiseIndexes.size(); i++)
		{
			if (i > 0)
			{
				if (randomiseIndexes[i] == randomiseIndexes[i - 1] + 1)
				{
					delete Instructions.back();
					Instructions.pop_back();
				}
			}
			size_t size = InstructionBuilder[randomiseIndexes[i]].size();
			size_t iSize = Instructions.size();
			Instructions.resize(iSize + size);
			memcpy(&Instructions[iSize], &InstructionBuilder[randomiseIndexes[i]][0], size * sizeof(Opcode*));
		}
	}
}

void FunctionData::optimisePushBytes()
{
	size_t size = Instructions.size(), _max = size - 1, max2 = size - 2;
	for (size_t i = 0; i < _max;i++)
	{
		Opcode* op = Instructions[i], *next, *next2;
		if (op->getKind() == OK_PushInt)
		{
			int val = op->getInt(), nextVal, next2Val;
			if (val >= 0 && val <= 0xFF)
			{
				if ((next = Instructions[i + 1], next->getKind()) == OK_PushInt && (nextVal = next->getInt(), nextVal >= 0 && nextVal <= 0xFF))
				{
					if (i < max2 && (next2 = Instructions[i + 2], next2->getKind() == OK_PushInt) && (next2Val = next2->getInt(), next2Val >= 0 && next2Val <= 0xFF))
					{
						//PushBytes3
						op->setKind(OK_PushBytes);
						op->setByte(3, 0);
						op->setByte(val, 1);
						op->setByte(nextVal, 2);
						op->setByte(next2Val, 3);
						//nop the next 2 opcodes as they have been handled
						next->makeNull();
						next2->makeNull();
						//skip the next 2 in Instructions in the next iteration
						i += 2;
					}
					else
					{
						//PushBytes2
						op->setKind(OK_PushBytes);
						op->setByte(2, 0);
						op->setByte(val, 1);
						op->setByte(nextVal, 2);
						//nop the next opcode as it has been handled
						next->makeNull();
						//skip the next instruction
						i++;
					}
				}
			}
		}
	}
}

void FunctionData::jumpThreading()
{
	if (getOptLevel() <= OptimisationLevel::OL_Trivial)
		return;
	for (int count = 0; count < (getOptLevel() > OptimisationLevel::OL_Normal ? 4 : 1); count++){//looping it takes more compile time so only on O3 but it will be able to produce more optimised code
		unordered_map<string, vector<size_t>> JumpLocs;
		unordered_map<string, vector<SwitchCaseStorage*>> switchCaseLocs;
		unordered_map<string, vector<SwitchStorage*>> switchDefaultLocs;
		unordered_map<string, vector<pair<JumpTableStorage*, size_t>>> jumpTableLocs;
		vector<pair<string, size_t>> LabelLocs;
		vector<pair<string, string>> JumpReplace;
		vector<string> JumpReturns;
		size_t instructionCount = Instructions.size();
		for (size_t i = 0; i < instructionCount; i++){
			auto opcode = Instructions[i];
			switch (opcode->getKind()){
				case OK_Jump:
				{
					bool nulled = false;
					for (size_t j = i + 1; j < instructionCount; j++){
						switch (Instructions[j]->getKind()){
							case OK_Null:
								continue;
							case OK_Label:
								if (opcode->getString() == Instructions[j]->getString()){
									opcode->makeNull();
									nulled = true;
									break;
								}
								continue;
							default:
								break;
						}
						break;
					}
					if (nulled){
						break;
					}
					else{
						JumpLocs[opcode->getString()].push_back(i);
					}
				}
				case OK_Return:
					//Remove any code after a unconditional jump/return until a label is reached, the code will never get executed
					for (i++; i < instructionCount; i++){
						auto next = Instructions[i];
						if (next->getKind() != OK_Label){
							next->makeNull();
						}
						else{
							i--;
							break;
						}
					}
					break;
				case OK_JumpFalse:
					//JumpLocs[opcode->getString()].push_back(i);
					{
						bool nulled = false;
						for (size_t j = i + 1; j < instructionCount; j++){
							switch (Instructions[j]->getKind()){
								case OK_Null:
									continue;
								case OK_Label:
									if (opcode->getString() == Instructions[j]->getString()){
										opcode->makeNull();
										makeDrop(i);
										instructionCount = Instructions.size();
										nulled = true;
										break;
									}
									continue;
								default:
									break;
							}
							break;
						}
						if (!nulled){
							JumpLocs[opcode->getString()].push_back(i);
						}
					}
					break;
				case OK_JumpEQ:
				case OK_JumpNE:
				case OK_JumpGT:
				case OK_JumpGE:
				case OK_JumpLT:
				case OK_JumpLE:
				{
					bool nulled = false;
					for (size_t j = i + 1; j < instructionCount; j++){
						switch (Instructions[j]->getKind()){
							case OK_Null:
								continue;
							case OK_Label:
								if (opcode->getString() == Instructions[j]->getString()){
									opcode->makeNull();
									makeDrop(i);
									makeDrop(i - 1);
									instructionCount = Instructions.size();
									nulled = true;
									break;
								}
								continue;
							default:
								break;
						}
						break;
					}
					if (!nulled){
						JumpLocs[opcode->getString()].push_back(i);
					}
				}
					break;
				case OK_LabelLoc:
					JumpLocs[opcode->getString()].push_back(i);
					break;
				case OK_Switch:
				{
					auto switchStorage = opcode->storage.switchCase;
					for (auto switchCase = switchStorage->getFirstCase(); switchCase; switchCase = switchCase->getNextCase()){
						switchCaseLocs[switchCase->getCaseLocation()].push_back(switchCase);
					}
					if (switchStorage->hasDefaultJumpLoc()){
						bool nulled = false;
						for (size_t j = i + 1; j < instructionCount; j++){
							switch (Instructions[j]->getKind()){
								case OK_Null:
									continue;
								case OK_Label:
									if (Instructions[j]->getString() == switchStorage->getDefaultJumpLoc()->toString()){
										switchStorage->clearDefaultJumpLoc();
										nulled = true;
										break;
									}
									continue;
								default:
									break;
							}
							break;
						}
						if (!nulled){
							switchDefaultLocs[switchStorage->getDefaultJumpLoc()->toString()].push_back(switchStorage);
							for (i++; i < instructionCount; i++){
								auto next = Instructions[i];
								if (next->getKind() != OK_Label){
									next->makeNull();
								}
								else{
									i--;
									break;
								}
							}
						}
					}
					break;
				}
				case OK_JumpTable:
				{
					auto jumpTable = opcode->storage.jTable;
					for (size_t i = 0; i < jumpTable->getItemCount(); i++){
						jumpTableLocs[jumpTable->getJumpLocAsString(i)].push_back(make_pair(jumpTable, i));
					}
				}
				case OK_Label:
				{
					const string orig = opcode->getString();
					LabelLocs.push_back(make_pair(orig, i));
					for (i++; i < instructionCount; i++){
						auto next = Instructions[i];
						if (next->getKind() == OK_Null)//ignore nops
							continue;
						if (next->getKind() == OK_Jump){

							const string repl = next->getString();
							if (orig != repl){//would only be the same in an infinite loop
								JumpReplace.push_back(make_pair(orig, repl));
							}
						}
						else if (next->getKind() == OK_Return){
							JumpReturns.push_back(orig);
						}
						i--;
						break;
					}
					break;
				}
				default:
					break;
			}
		}
		for (auto it = JumpReplace.begin(); it != JumpReplace.end(); it++){
			{
				auto locs = JumpLocs.find(it->first);
				if (locs != JumpLocs.end()){
					for (auto index : locs->second){
						Instructions[index]->setString(it->second);
					}
					auto &src = locs->second;
					auto &dst = JumpLocs[it->second];
					std::move(src.begin(), src.end(), std::back_inserter(dst));
					JumpLocs.erase(it->first);
				}
			}
			{
				auto locs = switchCaseLocs.find(it->first);
				if (locs != switchCaseLocs.end()){
					for (auto switchCase : locs->second){
						switchCase->setCaseLocation(it->second);
					}
					auto &src = locs->second;
					auto &dst = switchCaseLocs[it->second];
					std::move(src.begin(), src.end(), std::back_inserter(dst));
					switchCaseLocs.erase(it->first);
				}
			}
			{
				auto locs = switchDefaultLocs.find(it->first);
				if (locs != switchDefaultLocs.end()){
					for (auto switchStore : locs->second){
						switchStore->overWriteDefaultJumpLoc(it->second);
					}
					auto &src = locs->second;
					auto &dst = switchDefaultLocs[it->second];
					std::move(src.begin(), src.end(), std::back_inserter(dst));
					switchDefaultLocs.erase(it->first);
				}
			}
			{
				auto locs = jumpTableLocs.find(it->first);
				if (locs != jumpTableLocs.end()){
					for (auto jTable : locs->second){
						jTable.first->setJumpLoc(jTable.second, it->second);
					}
					auto &src = locs->second;
					auto &dst = jumpTableLocs[it->second];
					std::move(src.begin(), src.end(), std::back_inserter(dst));
					jumpTableLocs.erase(it->first);
				}
				
			}
		}
		for (auto it = LabelLocs.begin(); it != LabelLocs.end(); it++){
			if (JumpLocs.find(it->first) == JumpLocs.end() &&
				switchCaseLocs.find(it->first) == switchCaseLocs.end() &&
				switchDefaultLocs.find(it->first) == switchDefaultLocs.end() &&
				jumpTableLocs.find(it->first) == jumpTableLocs.end()){
				Instructions[it->second]->makeNull();
			}
		}
		for (auto item : JumpReturns){
			auto locs = JumpLocs.find(item);
			if (locs != JumpLocs.end()){
				for (auto index : locs->second){
					if (Instructions[index]->getKind() == OK_Jump){
						Instructions[index]->makeNull();
						Instructions[index]->setKind(OK_Return);
						Instructions[index]->setByte(pcount, 0);
						Instructions[index]->setByte(rcount, 1);
					}
				}
			}
		}
	}
	for (size_t i = 1, instructionCount = Instructions.size(); i < instructionCount; i++){
		auto ins = Instructions[i];
		switch (ins->getKind()){
			case OK_JumpFalse:
			{
				auto prev = Instructions[i - 1];
				for (i++; i < instructionCount; i++){
					auto jumpIns = Instructions[i];
					if (jumpIns->getKind() == OK_Null)
						continue;
					if (jumpIns->getKind() == OK_Jump){
						for (i++; i < instructionCount; i++){
							if (Instructions[i]->getKind() == OK_Null)
								continue;
							if (Instructions[i]->getKind() == OK_Label){
								if (Instructions[i]->getString() == ins->getString()){
									ins->makeNull();
									if (prev->getKind() == OK_Not){
										prev->makeNull();
									}
									else{
										ins->setKind(OK_Not);
									}
									jumpIns->setKind(OK_JumpFalse);
									break;
								}
							}
							i--;
							break;
						}
					}
					else{
						i--;
					}
					break;

				}
			}
			break;
			case OK_JumpEQ:
			case OK_JumpNE:
			case OK_JumpGE:
			case OK_JumpGT:
			case OK_JumpLE:
			case OK_JumpLT:
			{
				for (i++; i < instructionCount; i++){
					auto jumpIns = Instructions[i];
					if (jumpIns->getKind() == OK_Null)
						continue;
					if (jumpIns->getKind() == OK_Jump){
						for (i++; i < instructionCount; i++){
							if (Instructions[i]->getKind() == OK_Null)
								continue;
							if (Instructions[i]->getKind() == OK_Label){
								if (Instructions[i]->getString() == ins->getString()){
									switch (ins->getKind()){
										case OK_JumpEQ: ins->setKind(OK_JumpNE); break;
										case OK_JumpNE: ins->setKind(OK_JumpEQ); break;
										case OK_JumpGE: ins->setKind(OK_JumpLT); break;
										case OK_JumpGT: ins->setKind(OK_JumpLE); break;
										case OK_JumpLE: ins->setKind(OK_JumpGT); break;
										case OK_JumpLT: ins->setKind(OK_JumpGE); break;
										default: assert(false);
									}
									ins->setString(jumpIns->getString());
									jumpIns->makeNull();
									break;
								}
							}
							i--;
							break;
						}
					}
					else{
						i--;
					}
					break;

				}
			}
			break;
		default:
			break;

		}
	}
}
void FunctionData::insertDrop(size_t index){
	if (Instructions[index]->getKind() == OK_Null){
		Instructions[index]->setKind(OK_Drop);
	}
	else{
		Instructions.insert(Instructions.begin() + index, new Opcode(OK_Drop));
	}
}
void FunctionData::makeDrop(size_t index)
{
	start:
	switch (Instructions[index]->getKind())
	{
		case OK_Null:
			index--;
			goto start;
		case OK_PushInt:
		case OK_PushFloat:
		case OK_PushString:
		case OK_GetFrameP:
		case OK_GetFrame:
		case OK_GetStaticP:
		case OK_GetStatic:
		case OK_GetGlobalP:
		case OK_GetGlobal:
		case OK_Dup:
		case OK_LabelLoc:
			Instructions[index]->makeNull();
			break;
		case OK_FtoV:
			//this case would only ever come up if you have
			// toVector3(1.0f); and dont use the result, in which case it would recursively get cancelled down 
			Instructions.back()->setKind(OK_Dup);//replace fToV(dup2) with dup
			break;
		case OK_AddImm:
		case OK_MultImm:
		case OK_PGet:
		case OK_ItoF:
		case OK_FtoI:
		case OK_GetArrayP:
		case OK_GetArray:
		case OK_GetImmP:
		case OK_GetImm:
		case OK_Neg:
		case OK_FNeg:
		case OK_Not:
			//replace instructions that just replace item at top of the stack with a drop
			Instructions[index]->makeNull();
			makeDrop(index - 1);
			break;
		case OK_ShiftLeft:
		case OK_ShiftRight:
		case OK_Add:
		case OK_Sub:
		case OK_Mult:
		case OK_Div:
		case OK_Mod:
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
		case OK_FCmpEq:
		case OK_FCmpNe:
		case OK_FCmpGt:
		case OK_FCmpGe:
		case OK_FCmpLt:
		case OK_FCmpLe:
		case OK_And:
		case OK_Or:
		case OK_Xor:
			Instructions[index]->makeNull();
			makeDrop(index - 1);
			makeDrop(index - 2);
			break;
		case OK_ToStack:
		{
			auto& ptr = Instructions[index - 1];
			switch (ptr->getKind()){
				case OK_GetFrame:
				case OK_GetFrameP:
				case OK_GetStatic:
				case OK_GetStaticP:
				case OK_GetStaticRaw:
				case OK_GetStaticPRaw:
				case OK_GetGlobal:
				case OK_GetGlobalP:
				{
					auto& typeSize = Instructions[index - 2];
					if (typeSize->getKind() == OK_PushInt){
						if (typeSize->getInt() > 2){
							typeSize->setInt(typeSize->getInt() - 1);
						}
						else if (typeSize->getInt() == 2){
							
							typeSize->makeNull();
							switch (ptr->getKind()){
								case OK_GetFrameP:
									ptr->setKind(OK_GetFrame);
									break;
								case OK_GetStaticP:
									ptr->setKind(OK_GetStatic);
									break;
								case OK_GetStaticPRaw:
									ptr->setKind(OK_GetStaticRaw);
									break;
								case OK_GetGlobalP:
									ptr->setKind(OK_GetGlobal);
									break;
								default:
									typeSize->setKind(OK_PGet);
									break;
							}
							swap(typeSize, ptr);
							Instructions[index]->makeNull();
						}
						else{
							insertDrop(index + 1);
						}
					}
					else{
						insertDrop(index + 1);
					}
				}
				break;
				default:
					insertDrop(index + 1);
					break;

			}
		}
		break;
		default:
			insertDrop(index + 1);
			break;
	}
}

void FunctionData::moveInto(std::vector<Opcode*>& source)
{
	if (source.size() > 0)
	{
		size_t curSize = Instructions.size();
		Instructions.resize(Instructions.size() + source.size());
		memcpy(&Instructions[curSize], source.data(), source.size() * sizeof(Opcode*));
		source.clear();
	}
}

void FunctionData::addOpAdd()
{
	assert(Instructions.size() && "Instruction stack empty, cant add Add Instruction");
	int result;
	if (getOptLevel() > OptimisationLevel::OL_None && tryPopInt(result))
	{
		if (result != 0)
		{
			addOpAddImm(result);
		}
	}
	else
	{
		Instructions.push_back(new Opcode(OK_Add));
	}
}

void FunctionData::addOpSub()
{
	assert(Instructions.size() && "Instruction stack empty, cant add Sub Instruction");
	int result;
	if (getOptLevel() > OptimisationLevel::OL_None && tryPopInt(result))
	{
		if (result != 0)
		{
			addOpAddImm(-result);
		}
	}
	else
	{
		Instructions.push_back(new Opcode(OK_Sub));
	}
}

void FunctionData::addOpMult()
{
	assert(Instructions.size() && "Instruction stack empty, cant add Mult Instruction");
	int result;
	if (getOptLevel() > OptimisationLevel::OL_None && tryPopInt(result))
	{
		if (result == 0)
		{
			addOpDrop();
			addOpPushInt(0);
		}
		else if (result != 1)
		{
			addOpMultImm(result);
		}
	}
	else
	{
		Instructions.push_back(new Opcode(OK_Mult));
	}
}

void FunctionData::addOpDiv(bool *isZeroDivDetected)
{

	assert(Instructions.size() && "Instruction stack empty, cant add Div Instruction");
	if (isZeroDivDetected)
	{
		*isZeroDivDetected = false;
	}
	int result;
	if (getOptLevel() > OptimisationLevel::OL_None && tryPopInt(result))
	{
		if (result == 0)
		{
			if (isZeroDivDetected)
			{
				*isZeroDivDetected = true;
			}
			//game treats division by zero as just putting 0 on top of stack
			addOpDrop();
			addOpPushInt(0);
		}
		else if (result == -1){
			addOpNeg();
		}
		else if (result != 1)
		{
			int r2;
			if (tryPopInt(r2)){
				addOpPushInt(r2 / result);
			}
			else if (Instructions.back()->getKind() == OK_MultImm && Instructions.back()->getInt() % result == 0){
				Instructions.back()->setInt(Instructions.back()->getInt() / result);
			}
			else{
				addOpPushInt(result);
				Instructions.push_back(new Opcode(OK_Div));
			}
			
		}
	}
	else
	{
		Instructions.push_back(new Opcode(OK_Div));
	}
}

void FunctionData::addOpNot()
{
	assert(Instructions.size() && "Instruction stack empty, cant add Not Instruction");
	if (getOptLevel() > OptimisationLevel::OL_None){
		Opcode* back = Instructions.back();
		switch (back->getKind())
		{
			case OK_CmpEq:
				back->setKind(OK_CmpNe);
				return;
			case OK_CmpNe:
				back->setKind(OK_CmpEq);
				return;
			case OK_CmpGe:
				back->setKind(OK_CmpLt);
				return;
			case OK_CmpGt:
				back->setKind(OK_CmpLe);
				return;
			case OK_CmpLe:
				back->setKind(OK_CmpGt);
				return;
			case OK_CmpLt:
				back->setKind(OK_CmpGe);
				return;
			case OK_FCmpEq:
				back->setKind(OK_FCmpNe);
				return;
			case OK_FCmpNe:
				back->setKind(OK_FCmpEq);
				return;
			case OK_FCmpGe:
				back->setKind(OK_FCmpLt);
				return;
			case OK_FCmpGt:
				back->setKind(OK_FCmpLe);
				return;
			case OK_FCmpLe:
				back->setKind(OK_FCmpGt);
				return;
			case OK_FCmpLt:
				back->setKind(OK_FCmpGe);
				return;
			case OK_Not:
				delete Instructions.back();
				Instructions.pop_back();
				addOpIsNotZero();
				return;
			default:
			{
				int result;
				if (tryPopInt(result)){
					addOpPushInt(result == 0);
				}
				else{
					Instructions.push_back(new Opcode(OK_Not));
				}
				return;
			}

		}
	}
	else{
		Instructions.push_back(new Opcode(OK_Not));
	}
}

void FunctionData::addOpNeg()
{
	assert(Instructions.size() && "Instruction stack empty, cant add Neg Instruction");
	if (getOptLevel() > OptimisationLevel::OL_None){
		Opcode *back = Instructions.back();
		if (back->getKind() == OK_PushInt || back->getKind() == OK_MultImm)//treat pushInt and MultImm as the same
		{
			back->setInt(-back->getInt());
		}
		else
		{
			Instructions.push_back(new Opcode(OK_Neg));
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_Neg));
	}
}

void FunctionData::addOpFAdd()
{
	assert(Instructions.size() && "Instruction stack empty, cant add FAdd Instruction");
	if (getOptLevel() > OptimisationLevel::OL_None){
		Opcode *back = Instructions.back();
		if (back->getKind() == OK_PushFloat)
		{
			float imm = back->getFloat();
			delete back;
			Instructions.pop_back();
			addOpFAddImm(imm);
		}
		else
		{
			Instructions.push_back(new Opcode(OK_FAdd));
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_FAdd));
	}
}

void FunctionData::addOpFSub()
{
	assert(Instructions.size() && "Instruction stack empty, cant add FSub Instruction");
	if (getOptLevel() > OptimisationLevel::OL_None){
		Opcode *back = Instructions.back();
		if (back->getKind() == OK_PushFloat)
		{
			float imm = back->getFloat();
			delete back;
			Instructions.pop_back();
			addOpFAddImm(-imm);
		}
		else
		{
			Instructions.push_back(new Opcode(OK_FSub));
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_FSub));
	}
}

void FunctionData::addOpFMult()
{
	assert(Instructions.size() && "Instruction stack empty, cant add FMult Instruction");
	if (getOptLevel() > OptimisationLevel::OL_None){
		Opcode *back = Instructions.back();
		if (back->getKind() == OK_PushFloat)
		{
			float imm = back->getFloat();
			delete back;
			Instructions.pop_back();
			addOpFMultImm(imm);
		}
		else
		{
			Instructions.push_back(new Opcode(OK_FMult));
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_FMult));
	}
}

void FunctionData::addOpFDiv(bool * isZeroDivDetected)
{
	assert(Instructions.size() && "Instruction stack empty, cant add FDiv Instruction");
	if (isZeroDivDetected)
	{
		*isZeroDivDetected = false;
	}
	if (getOptLevel() > OptimisationLevel::OL_None){
		Opcode *back = Instructions.back();
		if (back->getKind() == OK_PushFloat)
		{
			float imm = back->getFloat();
			if (imm == 0.0f)
			{
				Instructions.push_back(new Opcode(OK_FDiv));//still parse the instruction as FDiv, but warn user
				if (isZeroDivDetected)
				{
					*isZeroDivDetected = true;
				}
			}
			else
			{
				delete back;
				Instructions.pop_back();
				addOpFMultImm(1.0f / imm);
			}
		}
		else
		{
			Instructions.push_back(new Opcode(OK_FDiv));
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_FDiv));
	}
}

void FunctionData::addOpFNeg()
{
	assert(Instructions.size() && "Instruction stack empty, cant add FNeg Instruction");
	if (getOptLevel() > OptimisationLevel::OL_None){
		Opcode *back = Instructions.back();
		if (back->getKind() == OK_PushFloat || back->getKind() == OK_FMultImm)//treat pushFloat and FMultImm as the same
		{
			back->setFloat(-back->getFloat());
		}
		else
		{
			Instructions.push_back(new Opcode(OK_FNeg));
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_FNeg));
	}
}

void FunctionData::addOpItoF()
{
	assert(Instructions.size() && "Cannot add ItoF to empty instruction stack");
	if (getOptLevel() > OptimisationLevel::OL_None && Instructions.back()->getKind() == OK_PushInt)
	{
		Opcode *last = Instructions.back();
		last->setKind(OK_PushFloat);
		last->setFloat((float)last->getInt());
	}
	else{
		Instructions.push_back(new Opcode(OK_ItoF));
	}
}

void FunctionData::addOpFtoI()
{
	assert(Instructions.size() && "Cannot add ItoF to empty instruction stack");
	if (getOptLevel() > OptimisationLevel::OL_None && Instructions.back()->getKind() == OK_PushFloat)
	{
		Opcode *last = Instructions.back();
		last->setKind(OK_PushInt);
		last->setInt((int)last->getInt());
	}
	else{
		Instructions.push_back(new Opcode(OK_FtoI));
	}
}

void FunctionData::addOpDrop()
{
	if (getOptLevel() > OptimisationLevel::OL_None)
	{
		switch (Instructions.back()->getKind())
		{
			case OK_PushInt:
			case OK_PushFloat:
			case OK_PushString:
			case OK_GetFrameP:
			case OK_GetFrame:
			case OK_GetStaticP:
			case OK_GetStatic:
			case OK_GetGlobalP:
			case OK_GetGlobal:
			case OK_Dup:
			case OK_LabelLoc:
				//delete instrucions that just push a value to the stack
				delete Instructions.back();
				Instructions.pop_back();
				break;
			case OK_FtoV:
				//this case would only ever come up if you have
				// toVector3(1.0f); and dont use the result, in which case it would recursively get cancelled down 
				Instructions.back()->setKind(OK_Dup);//replace fToV(dup2) with dup
				break;
			case OK_AddImm:
			case OK_MultImm:
			case OK_PGet:
			case OK_ItoF:
			case OK_FtoI:
			case OK_GetArrayP:
			case OK_GetArray:
			case OK_GetImmP:
			case OK_GetImm:
			case OK_Neg:
			case OK_FNeg:
			case OK_Not:
				//replace instructions that just replace item at top of the stack with a drop
				delete Instructions.back();
				Instructions.pop_back();
				addOpDrop();
				break;
			case OK_ShiftLeft:
			case OK_ShiftRight:
			case OK_Add:
			case OK_Sub:
			case OK_Mult:
			case OK_Div:
			case OK_Mod:
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
			case OK_FCmpEq:
			case OK_FCmpNe:
			case OK_FCmpGt:
			case OK_FCmpGe:
			case OK_FCmpLt:
			case OK_FCmpLe:
			case OK_And:
			case OK_Or:
			case OK_Xor:
				delete Instructions.back();
				Instructions.pop_back();
				addOpDrop();
				addOpDrop();
				break;
			case OK_ToStack:
			{
				auto& ptr = Instructions.at(Instructions.size() - 2);
				switch (ptr->getKind()){
					case OK_GetFrame:
					case OK_GetFrameP:
					case OK_GetStatic:
					case OK_GetStaticP:
					case OK_GetStaticRaw:
					case OK_GetStaticPRaw:
					case OK_GetGlobal:
					case OK_GetGlobalP:
					{
						auto& typeSize = Instructions.at(Instructions.size() - 3);
						if (typeSize->getKind() == OK_PushInt){
							if (typeSize->getInt() > 2){
								typeSize->setInt(typeSize->getInt() - 1);
							}
							else if (typeSize->getInt() == 2){
								//remove toStack
								delete typeSize;
								typeSize = ptr;
								delete Instructions.back();//toStack
								Instructions.pop_back();
								Instructions.pop_back();
								addOpPGet();
							}
							else{
								Instructions.push_back(new Opcode(OK_Drop));
							}
						}
						else{
							Instructions.push_back(new Opcode(OK_Drop));
						}
					}
					break;
					default:
						Instructions.push_back(new Opcode(OK_Drop));
						break;

				}
			}
			break;
			default:
				Instructions.push_back(new Opcode(OK_Drop));
				break;
		}
	}
	else
	{
		Instructions.push_back(new Opcode(OK_Drop));
	}
}

void FunctionData::addOpPGet()
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		assert(Instructions.size() && "Cannot add PGet to empty instruction stack");
		Opcode* op = Instructions.back();
		switch (op->getKind())
		{
			case OK_GetArrayP:
				Instructions.back()->setKind(OK_GetArray);
				return;
			case OK_GetFrameP:
				Instructions.back()->setKind(OK_GetFrame);
				return;
			case OK_GetGlobalP:
				Instructions.back()->setKind(OK_GetGlobal);
				return;
			case OK_GetStaticP:
				Instructions.back()->setKind(OK_GetStatic);
				return;
			case OK_GetStaticPRaw:
				Instructions.back()->setKind(OK_GetStaticRaw);
				return;
			case OK_GetImmP:
				Instructions.back()->setKind(OK_GetImm);
				return;
			default:
				Instructions.push_back(new Opcode(OK_PGet));
				return;
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_PGet));
	}
}

void FunctionData::addOpPSet()
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		assert(Instructions.size() && "Cannot add PSet to empty instruction stack");
		switch (Instructions.back()->getKind())
		{
			case OK_GetArrayP:
				Instructions.back()->setKind(OK_SetArray);
				return;
			case OK_GetFrameP:
				Instructions.back()->setKind(OK_SetFrame);
				return;
			case OK_GetGlobalP:
				Instructions.back()->setKind(OK_SetGlobal);
				return;
			case OK_GetStaticP:
				Instructions.back()->setKind(OK_SetStatic);
				return;
			case OK_GetStaticPRaw:
				Instructions.back()->setKind(OK_SetStaticRaw);
				return;
			case OK_GetImmP:
				Instructions.back()->setKind(OK_SetImm);
				return;
			default:
				Instructions.push_back(new Opcode(OK_PSet));
				return;
		}
	}
	else{
		Instructions.push_back(new Opcode(OK_PSet));
	}
}

void FunctionData::addOpGetFrame(uint16_t index)
{
	if (getOptLevel() > OptimisationLevel::OL_Normal){
		if (Instructions.size())
		{
			Opcode *back = Instructions.back();
			if (back->getKind() == OK_GetFrame && back->getUShort(0) == index - 1)
			{
				back->setKind(OK_PushInt);
				back->setInt(2);
				addOpGetFrameP(index - 1);
				addOpToStack();
				return;
			}
			else if (back->getKind() == OK_ToStack)
			{
				size_t size = Instructions.size();
				assert(size > 2 && "To Stack called with invalid args");
				Opcode* ptrOp = Instructions[size - 2], *sizeOp = Instructions[size - 3];
				if (ptrOp->getKind() == OK_GetFrameP && sizeOp->getKind() == OK_PushInt)
				{
					if (index - ptrOp->getUShort(0) == sizeOp->getInt())
					{
						sizeOp->setInt(sizeOp->getInt() + 1);
						return;
					}
				}
			}
		/*	else if (back->getKind() == OK_SetFrame && back->getUShort(0) == index){
				Instructions.pop_back();
				addOpDup();
				Instructions.push_back(back);
				return;
			}*/
		}
	}
	Instructions.push_back(Opcode::makeUShortOpcode(OK_GetFrame, index));

}

void FunctionData::addOpGetStaticRaw(uint16_t index)
{
	if (getOptLevel() > OptimisationLevel::OL_Normal){
		if (Instructions.size())
		{
			Opcode *back = Instructions.back();
			if (back->getKind() == OK_GetStaticRaw && back->getUShort(0) == index - 1)
			{
				back->setKind(OK_PushInt);
				back->setInt(2);
				addOpGetFrameP(index - 1);
				addOpToStack();
				return;
			}
			else if (back->getKind() == OK_ToStack)
			{
				size_t size = Instructions.size();
				assert(size > 2 && "To Stack called with invalid args");
				Opcode* ptrOp = Instructions[size - 2], *sizeOp = Instructions[size - 3];
				if (ptrOp->getKind() == OK_GetStaticPRaw && sizeOp->getKind() == OK_PushInt)
				{
					if (index - ptrOp->getUShort(0) == sizeOp->getInt())
					{
						sizeOp->setInt(sizeOp->getInt() + 1);
						return;
					}
				}
			}
		}
	}

	Instructions.push_back(Opcode::makeUShortOpcode(OK_GetStaticRaw, index));
}

void FunctionData::addOpGetGlobal(int index)
{
	if (getOptLevel() > OptimisationLevel::OL_Normal){
		if (Instructions.size())
		{
			Opcode *back = Instructions.back();
			if (back->getKind() == OK_GetGlobal && back->getInt() == index - 1)
			{
				back->setKind(OK_PushInt);
				back->setInt(2);
				addOpGetGlobalP(index - 1);
				addOpToStack();
				return;
			}
			else if (back->getKind() == OK_ToStack)
			{
				size_t size = Instructions.size();
				assert(size > 2 && "To Stack called with invalid args");
				Opcode* ptrOp = Instructions[size - 2], *sizeOp = Instructions[size - 3];
				if (ptrOp->getKind() == OK_GetGlobalP && sizeOp->getKind() == OK_PushInt)
				{
					if (index - ptrOp->getInt() == sizeOp->getInt())
					{
						sizeOp->setInt(sizeOp->getInt() + 1);
						return;
					}
				}
			}
		}
	}
	Instructions.push_back(Opcode::makeIntOpcode(OK_GetGlobal, index));
}

void FunctionData::addOpAddImm(int immediate)
{
start:
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		assert(Instructions.size() && "Cannot add AddImm to empty instruction stack");
		Opcode *last = Instructions.back();
		if (immediate == 0)
		{
			return;
		}
		switch (last->getKind())
		{
			case OK_AddImm:
			{
				int val = last->getInt() + immediate;
				delete last;
				Instructions.pop_back();
				immediate = val;
				goto start;
			}
			case OK_GetFrameP:
			case OK_GetStaticPRaw:
			case OK_GetImmP:
			{
				if (immediate % SCCL::stackWidth == 0)
				{
					int newImmIndex = (int)last->getUShort(0) + immediate / SCCL::stackWidth;
					if (newImmIndex < 0xFFFF)
					{
						last->setUShort(newImmIndex, 0);
						return;
					}
				}
			}
			goto setAsAddImm;
			case OK_GetGlobalP:
			{
				if (immediate % SCCL::stackWidth == 0)
				{
					int newImmIndex = last->getInt() + immediate / SCCL::stackWidth;
					if (newImmIndex < 0xFFFFFF)
					{
						last->setInt(newImmIndex);
						return;
					}
				}
			}
			goto setAsAddImm;
			case OK_GetStaticP:
			{
				if (immediate % SCCL::stackWidth == 0)
				{
					int newImmIndex = (int)last->getStaticData()->getImmIndex() + immediate / SCCL::stackWidth;
					if (newImmIndex < 0xFFFF)
					{
						last->storage.staticData->setImmIndex(newImmIndex);
						return;
					}
				}
			}
			goto setAsAddImm;
			default:
			{
				int result;
				if (tryPopInt(result)){
					addOpPushInt(result + immediate);
					return;
				}
			setAsAddImm:
				Instructions.push_back(Opcode::makeIntOpcode(OK_AddImm, immediate));
			}

		}

	}
	else{
		Instructions.push_back(Opcode::makeIntOpcode(OK_AddImm, immediate));
	}
}

void FunctionData::addOpMultImm(int immediate)
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		assert(Instructions.size() && "Cannot add MultImm to empty instruction stack");
		Opcode *last = Instructions.back();
		int result;
		if (tryPopInt(result))
		{
			addOpPushInt(result * immediate);
		}
		else if (last->getKind() == OK_MultImm)
		{
			int val = last->getInt() * immediate;
			delete last;
			Instructions.pop_back();
			addOpMultImm(val);
		}
		else if (immediate == -1)
		{
			addOpNeg();
		}
		else if (immediate == 0)
		{
			addOpDrop();
			addOpPushInt(0);
		}
		else if (immediate != 1)
		{
			Instructions.push_back(Opcode::makeIntOpcode(OK_MultImm, immediate));
		}
	}
	else{
		Instructions.push_back(Opcode::makeIntOpcode(OK_MultImm, immediate));
	}
}

void FunctionData::addOpFAddImm(float immediate)
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		assert(Instructions.size() && "Cannot add FAddImm to empty instruction stack");
		Opcode *last = Instructions.back();
		if (last->getKind() == OK_PushFloat)
		{
			last->setFloat(last->getFloat() + immediate);
		}
		else if (last->getKind() == OK_FAddImm)
		{
			float val = immediate + last->getFloat();
			delete last;
			Instructions.pop_back();
			addOpFAddImm(val);
		}
		else if (immediate == 0.0f)
		{
			//do nothing
		}
		else
		{
			Instructions.push_back(Opcode::makeFloatOpcode(OK_FAddImm, immediate));
		}
	}
	else{
		Instructions.push_back(Opcode::makeFloatOpcode(OK_FAddImm, immediate));
	}

}

void FunctionData::addOpFMultImm(float immediate)
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		assert(Instructions.size() && "Cannot add FMultImm to empty instruction stack");
		Opcode *last = Instructions.back();
		if (last->getKind() == OK_PushFloat)
		{
			last->setFloat(last->getFloat() * immediate);
		}
		else if (last->getKind() == OK_FMultImm)
		{
			float val = immediate * last->getFloat();
			delete last;
			Instructions.pop_back();
			addOpFMultImm(val);
		}
		else if (immediate == 0.0f)
		{
			addOpDrop();
			addOpPushFloat(0.0f);
		}
		else if (immediate == -1.0f)
		{
			addOpFNeg();
		}
		else if (immediate == 1.0f)
		{
			//do nothing
		}
		else if (immediate == 2.0f){
			addOpDup();
			addOpFAdd();
		}
		else
		{
			Instructions.push_back(Opcode::makeFloatOpcode(OK_FMultImm, immediate));
		}
	}
	else{
		Instructions.push_back(Opcode::makeFloatOpcode(OK_FMultImm, immediate));
	}
}

void FunctionData::addOpGetImmP(uint16_t index)
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		assert(Instructions.size() && "Cannot add GetImmP to empty instruction stack");
		if (index != 0){
			switch (Instructions.back()->getKind())
			{
				case OK_GetFrameP:
				case OK_GetGlobalP:
				case OK_GetImmP:
				case OK_GetStaticPRaw:
					Instructions.back()->setUShort(Instructions.back()->getUShort(0) + index, 0);
					break;
				case OK_GetStaticP:
				{
					auto data = Instructions.back()->storage.staticData;
					data->setImmIndex(data->getImmIndex() + index);
				}
				break;
				default:
					Instructions.push_back(Opcode::makeUShortOpcode(OK_GetImmP, index));
					break;
			}
		}
	}
	else{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_GetImmP, index));
	}
}

void FunctionData::addOpGetImm(uint16_t index)
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		if (index != 0){
			assert(Instructions.size() && "Cannot add GetImm to empty instruction stack");
			switch (Instructions.back()->getKind())
			{
				case OK_GetFrameP:
				case OK_GetGlobalP:
				case OK_GetImmP:
				case OK_GetStaticPRaw:
					Instructions.back()->setUShort(Instructions.back()->getUShort(0) + index, 0);
					addOpPGet();//pget will turn these
					return;
				case OK_GetStaticP:
				{
					auto data = Instructions.back()->storage.staticData;
					data->setImmIndex(data->getImmIndex() + index);
					addOpPGet();
				}
				return;
				default:
					break;
			}
			Instructions.push_back(Opcode::makeUShortOpcode(OK_GetImm, index));
		}
		else{
			addOpPGet();
		}
	}
	else
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_GetImm, index));
	}
}

void FunctionData::addOpSetImm(uint16_t index)
{
	if (getOptLevel() > OptimisationLevel::OL_Trivial){
		if (index != 0){
			assert(Instructions.size() && "Cannot add GetImm to empty instruction stack");
			switch (Instructions.back()->getKind())
			{
				case OK_GetFrameP:
				case OK_GetGlobalP:
				case OK_GetImmP:
				case OK_GetStaticPRaw:
					Instructions.back()->setUShort(Instructions.back()->getUShort(0) + index, 0);
					addOpPSet();//pset will turn these
					return;
				case OK_GetStaticP:
				{
					auto data = Instructions.back()->storage.staticData;
					data->setImmIndex(data->getImmIndex() + index);
					addOpPSet();
				}
				return;
				default:
					break;
			}
			Instructions.push_back(Opcode::makeUShortOpcode(OK_SetImm, index));
		}
		else{
			addOpPSet();
		}
	}
	else
	{
		Instructions.push_back(Opcode::makeUShortOpcode(OK_SetImm, index));
	}
}

void FunctionData::addOpJumpFalse(const string& loc)
{
	if (getOptLevel() > OptimisationLevel::OL_None){
		assert(Instructions.size() && "Instruction stack empty, cant add JumpFalse Instruction");
		Opcode *op = Instructions.back();
		switch (op->getKind())
		{
			case OK_CmpEq:
				op->setKind(OK_JumpNE);
				op->setString(loc);
				break;
			case OK_CmpNe:
				assert(Instructions.size() - 1);
			{
					Opcode* back2 = Instructions[Instructions.size() - 2];
					if (back2->getKind() == OK_PushInt && back2->getInt() == 0)
					{
						back2->setKind(OK_JumpFalse);
						back2->setString(loc);
						delete op;
						Instructions.pop_back();
					}
					else
					{
						op->setKind(OK_JumpEQ);
						op->setString(loc);
					}
			}
				
				break;
			case OK_CmpGt:
				op->setKind(OK_JumpLE);
				op->setString(loc);
				break;
			case OK_CmpGe:
				op->setKind(OK_JumpLT);
				op->setString(loc);
				break;
			case OK_CmpLt:
				op->setKind(OK_JumpGE);
				op->setString(loc);
				break;
			case OK_CmpLe:
				op->setKind(OK_JumpGT);
				op->setString(loc);
				break;
			case OK_PushInt:
				if (op->getInt())
				{
					delete op;//JumpFalse on something not zero never gets executed
					Instructions.pop_back();
				}
				else
				{
					//JumpFalse on zero always branches
					op->setKind(OK_Jump);
					op->setString(loc);
				}
				break;
			default:
				Instructions.push_back(Opcode::makeStringOpcode(OK_JumpFalse, loc));
				break;
		}
	}
	else{
		Instructions.push_back(Opcode::makeStringOpcode(OK_JumpFalse, loc));
	}
}

void FunctionData::addOpGetHash()
{
	assert(Instructions.size() && "Cannot add OpGetHash to empty instruction stack");
	auto back = Instructions.back();
	if (getOptLevel() > OptimisationLevel::OL_None && back->getKind() == OK_PushString)
	{
		const string& str = back->getString();
		delete back->storage.string;
		back->setInt(Utils::Hashing::Joaat(str));
		back->setKind(OK_PushInt);
		pushComment("GetHash(\"" + str + "\")");
	}
	else
	{
		Instructions.push_back(new Opcode(OK_GetHash));
	}
}

void FunctionData::addOpPushConstArrayPtr(const Script& base, const std::vector<int>& values)
{
	string strValue;
	strValue.resize(values.size() * base.getStackWidth());
	for (size_t i = 0; i < values.size(); i++){
		*(float*)(&strValue.data()[i * base.getStackWidth()]) = (base.getEndian() == Endian::END_BIG ? Utils::Bitwise::SwapEndian(values[i]) : values[i]);
	}
	addOpPushString(strValue);
}

void FunctionData::addOpPushConstArrayPtr(const Script& base, const std::vector<float>& values)
{
	string strValue;
	strValue.resize(values.size() * base.getStackWidth());
	for (size_t i = 0; i < values.size(); i++){
		*(float*)(&strValue.data()[i * base.getStackWidth()]) = (base.getEndian() == Endian::END_BIG ? Utils::Bitwise::SwapEndian(values[i]) : values[i]);
	}
	addOpPushString(strValue);
}

ostream & operator<<(ostream & stream, const FunctionData & fdata)
{
	stream << "\r\n:" << fdata.name << "//>\r\nFunction " << (int)fdata.pcount << " " << (int)fdata.stackSize << "\r\n";
	for(size_t i = 0; i < fdata.Instructions.size(); i++)
	{
		if (fdata.Instructions[i]->getKind() == OK_Null)
		{
			if (fdata.Instructions[i]->hasComment())
			{
				stream << "//" + fdata.Instructions[i]->getComment() << "\r\n";
			}
		}
		else
		{
			stream << *fdata.Instructions[i] << "\r\n";
		}
	}
	stream << "//<\r\n";
	return stream;
}
