#pragma once
#include "FunctionOpcode.h"
#include <vector>
#include <map>
class Script
{
	FunctionData entryFunction;
	vector<FunctionData *> functions;
	FunctionData *currentFunc;
	map<string, int> staticIndexes;
	vector<int> staticTable;
	struct InlineData { uint32_t hash; string name; string inlineLblAppend; };
	vector<InlineData> inlineStack;
	int staticCount = 0;
public:
	Script() : entryFunction("@EntryPoint", 0), currentFunc(NULL){}
	FunctionData *getEntryFunction() { return &entryFunction; }
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

	int addStaticDecl(string name, int size = 1);
	int getStaticIndex(string name) const;
	void setStaticInit(string name, int val, int offset = 0){ setStaticInit(getStaticIndex(name), val, offset); }
	void setStaticInit(int index, int val, int offset = 0);

	~Script()
	{
		for(auto fData : functions)
		{
			delete fData;
		}
	}
};

