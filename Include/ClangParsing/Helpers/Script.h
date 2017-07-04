#pragma once
#include "ClangParsing/Helpers/FunctionData.h"
#include "ClangParsing/Helpers/StaticData.h"
#include "Compiler/BuildTarget.h"
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include "Utils/Utils.h"

struct StaticsIgnoreBlock{
	size_t startIndex;
	size_t size;
};
class Script
{
	
	FunctionData *entryFunction;
	FunctionData *mainFunction;
	std::vector<std::unique_ptr<FunctionData>> functions;

	std::unordered_multimap<uint32_t, std::shared_ptr<StaticData>> staticMapExtern;//Joaat of Name, StaticData
	std::unordered_multimap<uint32_t, std::shared_ptr<StaticData>> staticMapStatic;//Joaat of Name, StaticData

	std::unordered_multimap<unsigned,std::shared_ptr<StaticData>> staticLocals;

	std::vector<std::shared_ptr<StaticData>> UsedStatics;
	size_t newStaticCount = 0;
	FunctionData *currentFunc = NULL;
	StaticData *currentStatic = NULL;

	std::vector<uint8_t> staticTable;//used static data

	struct InlineData { uint32_t hash; std::string name; std::string inlineLblAppend; bool unsafe; };
	std::vector<InlineData> inlineStack;
	int staticCount = 0;
	BuildType _bType;
	Platform _platform;
	Endian _endian;
	uint8_t _stackWidth;
	std::string _scriptName;
	std::shared_ptr<StaticData> scriptParams;
	const bool _isSingleton = false;
	const bool EntryFunctionPadding = false;
	const OptimisationLevel _optLevel = OptimisationLevel::OL_None;
	std::vector<StaticsIgnoreBlock> IgnoredBlocks;
	bool isStaticsLocked = false;
public:
	Script(std::string scriptName, BuildType buildType, Platform platform, bool isSingleton, bool isEntryFunctionPadding, OptimisationLevel optLevel);
	
	~Script()
	{
	}

	FunctionData *getEntryFunction() const{ return entryFunction; }
	FunctionData *getCurrentFunction()const{ return currentFunc; }
	FunctionData *createFunction(std::string name, int paramCount, int returnCount, bool makeCurrent = false, bool isPrototype = false);
	void clearCurrentFunction(){ currentFunc = NULL; }
	FunctionData *getFunctionFromName(const std::string &name);
	const FunctionData *getFunctionFromName(const std::string &name)const;
	unsigned getFunctionCount() const{ return functions.size(); }
	const FunctionData *getFunctionFromIndex(unsigned index)const{ assert(index < getFunctionCount() && index >= 0 && "Function index out of range"); return functions[index].get(); }

	unsigned getInlineCount() const{ return inlineStack.size(); }
	void resgisterReservedStaticBlock(size_t startIndex, size_t dataCount){
		if (!isStaticsLocked)
			IgnoredBlocks.push_back({ startIndex, dataCount });
	}
	void lockReservedStaticBlock(){
		if (!isStaticsLocked)
			std::sort(IgnoredBlocks.begin(), IgnoredBlocks.end(), [](StaticsIgnoreBlock& a, StaticsIgnoreBlock&b){return a.startIndex > b.startIndex; });
			isStaticsLocked = true;
	}
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

	bool isSingleton()const{ return _isSingleton; }
	
	bool doesEntryFunctionHavePadding()const { return EntryFunctionPadding; }

	OptimisationLevel getOptLevel()const{ return _optLevel; }

	void initializeEntryFunction();
	void finaliseEntryFunction();

	bool isFunctionInInlineStack(std::string name) const;
	bool isFunctionInInlineStack(const FunctionData *fData) const;

	bool addFunctionInline(std::string name, std::string returnLoc);
	bool addFunctionInline(const FunctionData *fData, std::string returnLoc);

	void removeFunctionInline(std::string name);
	void removeFunctionInline(const FunctionData *fData);

	bool isUnsafeContext()const;
	void resetStaticStatics()
	{
		staticMapStatic.clear();
	}
	void updateStaticStatics()
	{
		for (auto item : staticMapStatic)
			item.second->setUsedStaticInd(this);
	}
	const uint8_t* getNewStaticData() const
	{
		return staticTable.data();
	}
	std::string getStaticsAsString()
	{
		std::string out = "//> Default Static Information\r\nSetStaticsCount " + std::to_string(newStaticCount);
		for (auto sdata : UsedStatics)
		{
			out += sdata->getStringOutput(getEndian(), getStackWidth());
		}
		out += "\r\n//<\r\n";
		return out;
	}

	std::string getScriptName()const{ return _scriptName; }
	BuildType getBuildType()const{ return _bType; }
	Platform getBuildPlatform()const{ return _platform; }
	int getBuildPlatformSize() const { return _platform == Platform::P_PC ? 8 : 4; }

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

	size_t allocateStatic(size_t sizeOf){
		while (IgnoredBlocks.size()){
			auto& block = IgnoredBlocks.back();
			if (newStaticCount + sizeOf >= block.startIndex){
				newStaticCount = block.startIndex + block.size;
				getStaticTable().resize(newStaticCount * 8);
				IgnoredBlocks.pop_back();
				continue;
			}
			break;
		}
		return newStaticCount;
	}

	size_t getStaticCount()const
	{
		return newStaticCount;
	}
	void incStaticCount(std::shared_ptr<StaticData> staticData)
	{
		//assert(staticData);
		assert(staticData->getSize() && "incAmount must be positive");
		newStaticCount += staticData->getSize();

		UsedStatics.push_back(staticData);
	}
	void addStaticNewDecl(const std::string& name, int size, bool isStaticStorage, bool isPrototype = false)
	{
		uint32_t NameHash = Utils::Hashing::JoaatCased(name);
		if (isStaticStorage)
			currentStatic = staticMapStatic.insert({ NameHash , std::make_shared<StaticData>(name, size) })->second.get();
		else
		{
			currentStatic = staticMapExtern.insert({ NameHash , std::make_shared<StaticData>(name, size) })->second.get();
			currentStatic->setPrototype(isPrototype);
		}
	}
	void addStaticLocalNewDecl(const std::string& name, int size, unsigned sourceLoc){
		currentStatic = staticLocals.insert({ sourceLoc, std::make_shared<StaticData>(name, size) })->second.get();
	}
	StaticData* findLocalStatic(unsigned sourceLoc){
		auto it = staticLocals.find(sourceLoc);
		if (it != staticLocals.end()){
			return it->second.get();
		}
		return nullptr;
	}
	void setCurrentStatic(StaticData* staticData) { currentStatic = staticData; }
	StaticData* getCurrentStatic()const{ return currentStatic; }
	std::vector<uint8_t>& getStaticTable(){ return staticTable; }
	
	uint8_t getStackWidth()const 
	{
		return _stackWidth;
	}
	Endian getEndian()const
	{
		return _endian;
	}
	StaticData* findStatic(const std::string& name)
	{
		uint32_t NameHash = Utils::Hashing::JoaatCased(name);
		auto range = staticMapExtern.equal_range(NameHash);
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second.get()->getName() == name)
				return it->second.get();
		}
		range = staticMapStatic.equal_range(NameHash);
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second.get()->getName() == name)
				return it->second.get();
		}

		return NULL;
	}
};
