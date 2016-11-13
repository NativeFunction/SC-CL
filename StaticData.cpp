#include "StaticData.h"
#include "Script.h"
#include "FunctionData.h"

using namespace std;
void StaticData::setUsed(Script & scriptBase)
{
	if (!isUsed())
	{
		_index = scriptBase.getStaticCount();
		scriptBase.incStaticCount(this);
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
	if (_initialisation.size())
	{
		assert(!(_initialisation.size() % scriptBase.getStackWidth()) && "invalid initialisation size");
		Opcode * op = new Opcode(OK_GetStaticP);
		op->storage.staticData = this;
		_dynamicInitialisation.push_back(op);
		op = new Opcode(OK_SetImm);
		op->setUShort(_initialisation.size() / scriptBase.getStackWidth(), 0);
		_dynamicInitialisation.push_back(op);
	}
	else
	{
		Opcode * op = new Opcode(OK_SetStatic);
		op->storage.staticData = this;
		_dynamicInitialisation.push_back(op);
	}
	_initialisation.resize(_initialisation.size() + scriptBase.getStackWidth());
}

void StaticData::addOpFuncLoc(FunctionData * functionData)
{
	addReferencedFunction(functionData);
	Opcode *op = new Opcode(OK_FuncLoc);
	op->setString(functionData->getName().substr(1));
	_dynamicInitialisation.push_back(op);
}

const string StaticData::getStringOutput(Endian endian, uint8_t stackWidth)const
{
	assert(isUsed() && "Cant Display Unused Static Info");
	string output = "\r\nSetStaticName " + to_string(_index) + " " + getName();
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
	return std::move(output);
}
