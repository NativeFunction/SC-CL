#pragma once
#include "FunctionOpcode.h"
#include <vector>
#include <map>
class Script
{
	FunctionData *entryFunction;
	FunctionData *indirectGoTo;
	vector<FunctionData *> functions;
	FunctionData *currentFunc;
	vector<int32_t> staticTable;
	vector<uint32_t> staticTableShortIndexes;//endian for printing has to be swapped. however for shorts we have to Flip2BytesIn4
	struct InlineData { uint32_t hash; string name; string inlineLblAppend; };
	vector<InlineData> inlineStack;
	int staticCount = 0;
public:
	Script();
	FunctionData *getEntryFunction() const{ return entryFunction; }
	FunctionData *getCurrentFunction()const{ return currentFunc; }
	FunctionData *createFunction(string name, int paramCount, bool makeCurrent = false);
	void clearCurrentFunction(){ currentFunc = NULL; }
	const FunctionData *getFunctionFromName(string name)const;
	unsigned getFunctionCount() const{ return functions.size(); }
	const FunctionData *getFunctionFromIndex(unsigned index)const{ assert(index < getFunctionCount() && index >= 0 && "Function index out of range"); return functions[index]; }

	unsigned getInlineCount() const{ return inlineStack.size(); }

	string getInlineJumpLabelAppend() const
	{
		if (inlineStack.size())
		{
			return inlineStack.back().inlineLblAppend;
		}
		return "";
	}

	bool addUsedFuncToCurrent(string name);
	bool addUsedFuncToEntry(string name);

	bool isFunctionInInlineStack(string name) const;
	bool isFunctionInInlineStack(const FunctionData *fData) const;

	bool addFunctionInline(string name, string returnLoc);
	bool addFunctionInline(const FunctionData *fData, string returnLoc);

	void removeFunctionInline(string name);
	void removeFunctionInline(const FunctionData *fData);

	void addStaticDecl(const uint32_t size = 1) 
	{ 
		staticTable.reserve(staticTable.size() + size); 
	}
	uint32_t addStaticInit(const int32_t val = 0)
	{
		staticTable.push_back(Utils::Bitwise::SwapEndian(val));
		return staticTable.size() - 1;
	}
	uint32_t addStaticInitBig(const int32_t val = 0)
	{
		staticTable.push_back(val);
		return staticTable.size() - 1;
	}
	uint32_t addStaticInit(const int32_t val, const size_t size)
	{
		staticTable.resize(staticTable.size() + size, val);
		return staticTable.size() - 1;
	}
	void modifyLastInitStaticByte(const uint8_t byte, const uint8_t index)
	{
		assert((index < 4 && index >= 0) && "modifyLastInitStaticByte index out of bounds");
		*((uint8_t*)&staticTable.back() + index) = byte;
	}
	void modifyLastInitStaticShort(const uint16_t byte, const uint8_t index)
	{
		if(staticTableShortIndexes.empty() || staticTableShortIndexes.back() != staticTable.size() - 1)
			staticTableShortIndexes.push_back(staticTable.size() - 1);

		assert((index == 0 || index == 2) && "modifyLastInitStaticShort index out of bounds");
		*(uint16_t*)((uint8_t*)&staticTable.back() + index) = byte;
	}
	uint32_t getStaticSize() const
	{
		return staticTable.size();
	}
	uint32_t getStaticCapacity() const
	{
		return staticTable.capacity();
	}
	void fillStaticCapacity()
	{
		staticTable.resize(staticTable.capacity());
	}
	uint32_t getStaticRemainder() const
	{
		return staticTable.capacity() - staticTable.size();
	}
	const int32_t* getStaticData() const
	{
		return staticTable.data();
	}
	string getStaticsAsString();
	
	~Script()
	{
		for(auto fData : functions)
		{
			delete fData;
		}
	}
};

enum Platform
{
	P_XBOX,
	P_PS3,
	P_PC
};

