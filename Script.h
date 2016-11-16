#pragma once
#include "FunctionData.h"
#include "StaticData.h"
#include "BuildTarget.h"
#include <memory>
#include <vector>
#include <map>
class Script
{
	FunctionData *entryFunction;
	FunctionData *mainFunction;
	std::vector<std::unique_ptr<FunctionData>> functions;
	std::vector<std::unique_ptr<StaticData>> statics;
	std::map<unsigned, StaticData*> Statics;
	std::vector<StaticData*> finalStatics;
	size_t newStaticCount = 0;
	FunctionData *currentFunc;
	StaticData *currentStatic = NULL;
	std::vector<int32_t> staticTable;
	std::vector<uint8_t> newStaticTable;
	std::vector<uint32_t> staticTableShortIndexes;//endian for printing has to be swapped. however for shorts we have to Flip2BytesIn4
	struct InlineData { uint32_t hash; std::string name; std::string inlineLblAppend; bool unsafe; };
	std::vector<InlineData> inlineStack;
	int staticCount = 0;
	BuildType _bType;
	Platform _platform;
	Endian _endian;
	uint8_t _stackWidth;
	std::string _scriptName;
	std::unique_ptr<StaticData> scriptParams;
	bool _isSingleton = false,
		EntryFunctionPadding = false;
public:
	Script(std::string scriptName, BuildType buildType, Platform platform);

	FunctionData *getEntryFunction() const{ return entryFunction; }
	FunctionData *getCurrentFunction()const{ return currentFunc; }
	FunctionData *createFunction(std::string name, int paramCount, int returnCount, bool makeCurrent = false, bool isPrototype = false);
	void clearCurrentFunction(){ currentFunc = NULL; }
	FunctionData *getFunctionFromName(const std::string &name);
	const FunctionData *getFunctionFromName(const std::string &name)const;
	unsigned getFunctionCount() const{ return functions.size(); }
	const FunctionData *getFunctionFromIndex(unsigned index)const{ assert(index < getFunctionCount() && index >= 0 && "Function index out of range"); return functions[index].get(); }

	unsigned getInlineCount() const{ return inlineStack.size(); }

	std::string getInlineJumpLabelAppend() const
	{
		if (inlineStack.size())
		{
			return inlineStack.back().inlineLblAppend;
		}
		return "";
	}

	void setMainFunction(FunctionData* mainFunc){ 
		assert(mainFunc->getName() == "main" && "trying to set function not called main to mainFunction"); 
		assert(!mainFunction && "Trying to set main function twice");
		mainFunction = mainFunc; 
		if (mainFunction->getParamCount())
		{
			assert(!scriptParams && "script params already set");
			scriptParams = std::make_unique<StaticData>("__builtin_ScriptParameters", mainFunction->getParamCount());
			scriptParams->fillCapacity(getStackWidth());
		}
	}

	unsigned getParameterCount()const
	{
		return scriptParams ? scriptParams->getSize() : 0;
	}

	void setSingleton(bool makeSingleton = true){ _isSingleton = makeSingleton; }
	bool isSingleton()const{ return _isSingleton; }

	void setEntryFunctionPadding(bool Entry_Function_Padding = true) { EntryFunctionPadding = Entry_Function_Padding; }
	bool doesEntryFunctionHavePadding()const { return EntryFunctionPadding; }

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
	const uint8_t* getNewStaticData() const
	{
		return newStaticTable.data();
	}
	std::string getStaticsAsString();
	std::string getNewStaticsAsString()
	{
		std::string out = "SetStaticsCount " + std::to_string(newStaticCount);
		for (auto sdata:finalStatics)
		{
			out += sdata->getStringOutput(getEndian(), getStackWidth());
		}
		return std::move(out);
	}

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

	size_t getStaticCount()const
	{
		return newStaticCount;
	}
	void incStaticCount(StaticData* staticData)
	{
		assert(staticData);
		assert(staticData->getSize() && "incAmount must be positive");
		newStaticCount += staticData->getSize();
		finalStatics.push_back(staticData);
	}
	void addStaticNewDecl(unsigned sourceLoc, const std::string& name, int size)
	{
		statics.push_back(std::make_unique<StaticData>(name, size));
		currentStatic = statics.back().get();
		Statics.insert({ sourceLoc, currentStatic });
	}
	StaticData* getCurrentStatic()const{ return currentStatic; }
	std::vector<uint8_t>& getStaticTable(){ return newStaticTable; }
	
	uint8_t getStackWidth()const 
	{
		return _stackWidth;
	}
	Endian getEndian()const
	{
		return _endian;
	}
	StaticData* findStatic(unsigned sourceLoc)
	{
		auto it = Statics.find(sourceLoc);
		if (it != Statics.end())
		{
			return it->second;
		}
		return NULL;
	}

	~Script()
	{
	}
};
