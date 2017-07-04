#include "ClangParsing/Helpers/StaticData.h"
#include "ClangParsing/Helpers/Script.h"
#include "ClangParsing/Helpers/FunctionData.h"

using namespace std;
void StaticData::setUsedStaticInd(Script* scriptBase)
{
	if (!isUsed())
	{
		_index = scriptBase->getStaticCount();

		scriptBase->incStaticCount(shared_from_this());
		if (_isDynamic)
		{
			auto entry = scriptBase->getEntryFunction();
			entry->moveInto(_dynamicInitialisation);
		}
		//still copy the initialisation table incase of a struct which has members with static initialisers
		assert(_initialisation.size() <= getSize() * scriptBase->getStackWidth() && "static initialisation table too large");
		auto &table = scriptBase->getStaticTable();
		size_t curSize = table.size();
		table.resize(table.size() + getSize() * scriptBase->getStackWidth(), 0);
		memcpy(&table[curSize], _initialisation.data(), min(_initialisation.size(), getSize() * scriptBase->getStackWidth()));
	}
}

void StaticData::setUsed(Script & scriptBase)
{
	if (isPrototype())
		Utils::System::Throw("Implentation of " + getName() + " not found");

	if (!isUsed())
	{
		_index = scriptBase.allocateStatic(getSize());
		scriptBase.incStaticCount(shared_from_this());
		if (_isDynamic)
		{
			auto entry = scriptBase.getEntryFunction();
			entry->moveInto(_dynamicInitialisation);
		}
		//still copy the initialisation table incase of a struct which has members with static initialisers
		assert(_initialisation.size() <= getSize() * scriptBase.getStackWidth() && "static initialisation table too large");
		auto &table = scriptBase.getStaticTable();
		size_t curSize = table.size();
		table.resize(table.size() + getSize() * scriptBase.getStackWidth(), 0);
		memcpy(&table[curSize], _initialisation.data(), min(_initialisation.size(), getSize() * scriptBase.getStackWidth()));

		for (auto sdata : _referenceStatics)
		{
			sdata->setUsed(scriptBase);
		}
		for (auto fdata : _referencedFunctions)
		{
			fdata->setUsed(scriptBase);
		}
	}
}

void StaticData::addOpSetThisStatic(Script & scriptBase)
{

	assert(!(_initialisation.size() % scriptBase.getStackWidth()) && "invalid initialisation size");

	_dynamicInitialisation.push_back(Opcode::makeStaticOpcode(OK_SetStatic, new OpStaticStorage(this, _initialisation.size() / scriptBase.getStackWidth())));
	_initialisation.resize(_initialisation.size() + scriptBase.getStackWidth());
}

void StaticData::addOpSetThisStaticMult(Script & scriptBase, int32_t value, int32_t count)
{
	assert(!(_initialisation.size() % scriptBase.getStackWidth()) && "invalid initialisation size");

	while(count > 0)
	{
		uint32_t currentCount = count > 50 ? 50 : count;

		for (uint32_t i = 0; i < currentCount; i++)
		{
			_dynamicInitialisation.push_back(Opcode::makeIntOpcode(OK_PushInt, value));
		}
		

		_dynamicInitialisation.push_back(Opcode::makeIntOpcode(OK_PushInt, currentCount));
		_dynamicInitialisation.push_back(Opcode::makeStaticOpcode(OK_GetStaticP, new OpStaticStorage(this, _initialisation.size() / scriptBase.getStackWidth())));
		_dynamicInitialisation.push_back(new Opcode(OK_FromStack));
		_initialisation.resize(_initialisation.size() + scriptBase.getStackWidth() * currentCount);

		count -= 50;
	}
	
}

void StaticData::addOpDynamicNullThisStatic(Script & scriptBase)
{
	assert(!(_initialisation.size() % scriptBase.getStackWidth()) && "invalid initialisation size");
	int count = getSize() - (_initialisation.size() / scriptBase.getStackWidth());
	if (count == 1){
		_dynamicInitialisation.push_back(new Opcode(OK_PushNullPtr));
		_dynamicInitialisation.push_back(Opcode::makeStaticOpcode(OK_SetStatic, new OpStaticStorage(this, _initialisation.size() / scriptBase.getStackWidth())));
		_initialisation.resize(_initialisation.size() + scriptBase.getStackWidth());
	}
	else{
		while (count > 0)
		{
			uint32_t currentCount = count > 50 ? 50 : count;

			for (uint32_t i = 0; i < currentCount; i++)
			{
				_dynamicInitialisation.push_back(new Opcode(OK_PushNullPtr));
			}
			_dynamicInitialisation.push_back(Opcode::makeIntOpcode(OK_PushInt, currentCount));
			_dynamicInitialisation.push_back(Opcode::makeStaticOpcode(OK_GetStaticP, new OpStaticStorage(this, _initialisation.size() / scriptBase.getStackWidth())));
			_dynamicInitialisation.push_back(new Opcode(OK_FromStack));
			_initialisation.resize(_initialisation.size() + scriptBase.getStackWidth() * currentCount);

			count -= 50;
		}
	}
	setDynamic();
}

void StaticData::addOpFuncLoc(FunctionData * functionData)
{
	addReferencedFunction(functionData);
	Opcode *op = new Opcode(OK_FuncLoc);
	op->storage.functionData = functionData;
	_dynamicInitialisation.push_back(op);
}

const string StaticData::getStringOutput(Endian endian, uint8_t stackWidth)const
{
	assert(isUsed() && "Cant Display Unused Static Info");
	string output = "\r\nSetStaticName " + to_string(_index) + " " + getName();

	//add this error to compiler 
	if (isPrototype())
		Utils::System::Throw("Implentation of " + getName() + " not found for asm output");

	for (size_t i = 0; i <getSize();i++)
	{
		if (stackWidth == 4)
		{
			int val = *(int*)(_initialisation.data() + 4 * i);
			if (endian == END_BIG)
				val = Utils::Bitwise::SwapEndian(val);
			if (val != 0)
			{
				output += "\r\nSetDefaultStatic " + to_string(_index + i) + " " + to_string(val);
			}
		}
		else if (stackWidth == 8)
		{
			int64_t val = *(int64_t*)(_initialisation.data() + 8 * i);
			if (endian == END_BIG)
				val = Utils::Bitwise::SwapEndian(val);
			if (val != 0)
			{
				output += "\r\nSetDefaultStatic " + to_string(_index + i) + " " + to_string(val);
			}
		}
		else
		{
			assert(false && "This shouldnt happen, invalid stack width");
		}
	}
	return output;
}
