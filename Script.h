#pragma once
#include "FunctionData.h"
#include <vector>

enum Platform
{
	P_XBOX,
	P_PS3,
	P_PC
};

enum BuildType
{
	BT_GTAIV,
	BT_RDR_XSC,
	BT_RDR_SCO,
	BT_GTAV
};


class Script
{
	FunctionData *entryFunction;
	FunctionData *mainFunction;
	std::vector<FunctionData *> functions;
	FunctionData *currentFunc;
	std::vector<int32_t> staticTable;
	std::vector<uint32_t> staticTableShortIndexes;//endian for printing has to be swapped. however for shorts we have to Flip2BytesIn4
	struct InlineData { uint32_t hash; std::string name; std::string inlineLblAppend; bool unsafe; };
	std::vector<InlineData> inlineStack;
	int staticCount = 0;
	BuildType _bType;
	Platform _platform;
	std::string _scriptName;
public:
	Script(std::string scriptName, BuildType buildType, Platform platform);
	FunctionData *getEntryFunction() const{ return entryFunction; }
	FunctionData *getCurrentFunction()const{ return currentFunc; }
	FunctionData *createFunction(std::string name, int paramCount, int returnCount, bool makeCurrent = false);
	void clearCurrentFunction(){ currentFunc = NULL; }
	const FunctionData *getFunctionFromName(std::string name)const;
	unsigned getFunctionCount() const{ return functions.size(); }
	const FunctionData *getFunctionFromIndex(unsigned index)const{ assert(index < getFunctionCount() && index >= 0 && "Function index out of range"); return functions[index]; }

	unsigned getInlineCount() const{ return inlineStack.size(); }

	std::string getInlineJumpLabelAppend() const
	{
		if (inlineStack.size())
		{
			return inlineStack.back().inlineLblAppend;
		}
		return "";
	}

	void setMainFunction(FunctionData* mainFunc){ assert(mainFunc->getName() == "@main" && "trying to set function not called main to mainFunction"); mainFunction = mainFunc; }

	bool addUsedFuncToCurrent(std::string name);
	bool addUsedFuncToEntry(std::string name);
	void finaliseEntryFunction();

	bool isFunctionInInlineStack(std::string name) const;
	bool isFunctionInInlineStack(const FunctionData *fData) const;

	bool addFunctionInline(std::string name, std::string returnLoc);
	bool addFunctionInline(const FunctionData *fData, std::string returnLoc);

	void removeFunctionInline(std::string name);
	void removeFunctionInline(const FunctionData *fData);

	bool isUnsafeContext()const;

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
		*(uint16_t*)((uint8_t*)&staticTable.back() + index) = Utils::Bitwise::SwapEndian(byte);
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
	std::string getStaticsAsString();

	std::string getScriptName()const{ return _scriptName; }
	BuildType getBuildType()const{ return _bType; }
	Platform getBuildPlatform()const{ return _platform; }

	std::string getPlatformAbv()const;

	std::string getPlatformAbvUpper()const;

	std::string getBuildTypeExt()const;

	std::string getCompiledOutputExt()const;

	std::string getBuildFileName()const{
		return getScriptName() + "." + getCompiledOutputExt();
	}

	std::string getASMFileName()const{
		return getScriptName() + "." + getBuildTypeExt();
	}
	
	~Script()
	{
		for(auto fData : functions)
		{
			delete fData;
		}
	}
};
