#pragma once
#include <string>
#include "Compiler/Opcode.h"
#include <vector>
#include "Compiler/BuildTarget.h"
#include "Utils/Utils.h"

class Script;
class FunctionData;
class StaticData : public std::enable_shared_from_this<StaticData>
{
private:
	size_t _size;
	int _index = -1;//-1 means unused
	std::vector<uint8_t> _initialisation;
	std::vector<Opcode*> _dynamicInitialisation;
	std::vector<StaticData*> _referenceStatics;
	std::vector<FunctionData*> _referencedFunctions;
	std::string _name;
	bool _isDynamic = false;
	bool _isPrototype = false;

	void cleanUpDynamic()
	{
		for (auto opcode : _dynamicInitialisation)
		{
			delete opcode;
		}
	}
	void addReferencedStatic(StaticData* staticData)
	{
		auto iter = std::find(_referenceStatics.begin(), _referenceStatics.end(), staticData);
		if (iter == _referenceStatics.end())
		{
			_referenceStatics.push_back(staticData);
		}
	}
	void addReferencedFunction(FunctionData* functionData)
	{
		auto iter = std::find(_referencedFunctions.begin(), _referencedFunctions.end(), functionData);
		if (iter == _referencedFunctions.end())
		{
			_referencedFunctions.push_back(functionData);
		}
	}

public:
	StaticData(std::string name, size_t size): _size(size), _name(std::move(name))
	{
		assert(size > 0 && "Size must be positive");
	}
	~StaticData()
	{
		cleanUpDynamic();
	}

	size_t getSize()const
	{
		return _size;
	}
	const std::string& getName()const{ return _name; }

	bool isUsed() const
	{
		return _index > -1;
	}
	uint16_t getIndex()const
	{
		assert(isUsed() && "cannot get index of unused static");
		return _index;
	}
	bool isPrototype()const
	{
		return _isPrototype;
	}
	bool isDynamic()const
	{
		return _isDynamic;
	}
	void setUsed(Script& scriptBase);
	void setUsedStaticInd(Script* scriptBase);
	
	void setPrototype(bool value)
	{
		_isPrototype = value;
	}
	void setDynamic()
	{
		_isDynamic = true;
	}
	size_t getStackInitSize(uint8_t stackWidth)const
	{
		return (_initialisation.size() + stackWidth - 1) / stackWidth;
	}

	void padInitTable(uint8_t stackWidth)
	{
		if (_initialisation.size() % stackWidth)
		{
			_initialisation.resize(_initialisation.size() + stackWidth - (_initialisation.size() % stackWidth));//pad the initialisation table up to a multiple of stack width
		}
	}
	void pushInit32(int32_t value, Endian endian)
	{
		size_t curSize = _initialisation.size();
		_initialisation.resize(curSize + 4);
		if (endian == END_BIG)
			value = Utils::Bitwise::SwapEndian(value);
		*(int32_t*)&_initialisation[curSize] = value;
	}
	void pushInit16(int16_t value, Endian endian)
	{
		size_t curSize = _initialisation.size();
		_initialisation.resize(curSize + 2);
		if (endian == END_BIG)
			value = Utils::Bitwise::SwapEndian(value);
		*(int16_t*)&_initialisation[curSize] = value;
	}
	void pushInit8(int8_t value)
	{
		size_t curSize = _initialisation.size();
		_initialisation.resize(curSize + 1);
		*(int8_t*)&_initialisation[curSize] = value;
	}
	void pushStringInit(const std::string& str, size_t strActSize)
	{
		size_t curSize = _initialisation.size();
		_initialisation.resize(curSize + strActSize);
		memcpy(&_initialisation[curSize], str.data(), min(str.size(), strActSize));
		if (str.size() >= strActSize)
		{
			_initialisation.back() = '\0';
		}
	}
	void pushNullInit(size_t count, uint8_t stackWidth)
	{
		_initialisation.resize(_initialisation.size() + count * stackWidth);
	}
	void fillCapacity(uint8_t stackWidth)
	{
		assert(_initialisation.size() <= (getSize() * stackWidth) && "table exceeded value");
		_initialisation.resize(getSize() * stackWidth, 0);
	}
	void addOpPushNullPtr(){
		_dynamicInitialisation.push_back(new Opcode(OK_PushNullPtr));
	}
	void addOpAddBitField(int bitIndex, int bitCount)
	{
		assert(bitIndex + bitCount >= 1 && bitIndex + bitCount <= 32 && "bitindex + bitCount must be between 1 and 32");
		assert(_dynamicInitialisation.size() >= 2 && "cannot add bitset to empty instruction stack");

		_dynamicInitialisation.push_back(Opcode::makeIntOpcode(OK_PushInt, Utils::Bitwise::revbitmask(bitCount)));
		_dynamicInitialisation.push_back(new Opcode(OK_And));
		_dynamicInitialisation.push_back(Opcode::makeIntOpcode(OK_PushInt, 0));
		_dynamicInitialisation.push_back(new Opcode(OK_ShiftLeft));
		_dynamicInitialisation.push_back(new Opcode(OK_Or));
	}
	void addOpPushInt(int value)
	{
		Opcode* op = new Opcode(OK_PushInt);
		op->setInt(value);
		_dynamicInitialisation.push_back(op);
	}
	void addOpPushFloat(float value)
	{
		Opcode* op = new Opcode(OK_PushFloat);
		op->setFloat(value);
		_dynamicInitialisation.push_back(op);
	}
	void addOpSetThisStatic(Script& scriptBase);//will only ever called on this static data so no point passing params
	void addOpSetThisStaticMult(Script & scriptBase, int32_t value, int32_t count);
	void addOpDynamicNullThisStatic(Script& scriptBase);
	void addOpGetStaticP(StaticData* staticData)
	{
		addReferencedStatic(staticData);
		Opcode * op = new Opcode(OK_GetStaticP);
		op->storage.staticData = new OpStaticStorage(staticData);
		_dynamicInitialisation.push_back(op);
	}
	void addOpGetImmP(uint16_t imm)
	{
		if (_dynamicInitialisation.size() && _dynamicInitialisation.back()->getKind() == OK_GetStaticP)
		{
			auto data = _dynamicInitialisation.back()->storage.staticData;
			data->setImmIndex(data->getImmIndex() + imm);
		}
		else{
			Opcode * op = new Opcode(OK_GetImmP);
			op->setUShort(imm, 0);
			_dynamicInitialisation.push_back(op);
		}
	}
	void addOpAddImm(int imm)
	{
		Opcode * op = new Opcode(OK_AddImm);
		op->setInt(imm);
		_dynamicInitialisation.push_back(op);
	}
	void addOpMultImm(int imm)
	{
		Opcode * op = new Opcode(OK_MultImm);
		op->setInt(imm);
		_dynamicInitialisation.push_back(op);
	}
	void addOpPushString(std::string string)
	{
		Opcode * op = new Opcode(OK_PushString);
		op->setString(string);
		_dynamicInitialisation.push_back(op);
	}
	void addOpFuncLoc(FunctionData *functionData);

	void addOpFSub(){ _dynamicInitialisation.push_back(new Opcode(OK_FSub)); }
	void addOpSub(){ _dynamicInitialisation.push_back(new Opcode(OK_Sub)); }
	void addOpAdd(){ _dynamicInitialisation.push_back(new Opcode(OK_Add)); }
	void addOpDiv(){ _dynamicInitialisation.push_back(new Opcode(OK_Div)); }

	const std::string getStringOutput(Endian endian, uint8_t stackWidth)const;
};

