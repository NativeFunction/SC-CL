#include "Script.h"
#include "Utils.h"

FunctionData * Script::createFunction(string name, int paramCount, bool makeCurrent)
{
	uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
	for (int i = 0, max = getFunctionCount(); i<max; i++)
	{
		FunctionData *func = functions[i];
		if (hash == func->getHash() && name == func->getName())
		{
			assert(!func->isProcessed() && "Function has already been processed");
			if (makeCurrent)
			{
				currentFunc = func;
			}
			return func;
		}
	}
	FunctionData *newFunc = new FunctionData(name, paramCount);
	functions.push_back(newFunc);
	if (makeCurrent)
	{
		currentFunc = newFunc;
	}
	return newFunc;
}

const FunctionData * Script::getFunctionFromName(string name) const
{
	uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
	for (int i = 0, max = getFunctionCount(); i<max;i++)
	{
		const FunctionData *func = getFunctionFromIndex(i);
		if (hash == func->getHash() && name == func->getName())
			return functions[i];
	}
	assert(false && "Function doesnt exist");
	return NULL;
}

bool Script::addUsedFuncToCurrent(string name)
{
	assert(getCurrentFunction() && "Current func undefined");
	uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
	for (int i = 0, max = getFunctionCount(); i<max; i++)
	{
		FunctionData *func = functions[i];
		if (hash == func->getHash() && name == func->getName())
		{
			getCurrentFunction()->addUsedFunc(func);
			return true;
		}
	}
	assert(false && "Function doesnt exist");
	return false;
}

bool Script::addUsedFuncToEntry(string name)
{
	uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
	for (int i = 0, max = getFunctionCount(); i<max; i++)
	{
		FunctionData *func = functions[i];
		if (hash == func->getHash() && name == func->getName())
		{
			entryFunction.addUsedFunc(func);
			return true;
		}
	}
	assert(false && "Function doesnt exist");
	return false;
}

bool Script::isFunctionInInlineStack(string name) const
{
	uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
	for (int i = 0, max = getInlineCount(); i<max; i++)
	{
		if (hash == inlineStack[i].hash && name == inlineStack[i].name)
			return true;
	}
	return false;
}

bool Script::isFunctionInInlineStack(const FunctionData * fData) const
{
	assert(fData && "Null FunctionData pointer");
	for (int i = 0, max = getInlineCount(); i < max;i++)
	{
		if (fData->getHash() == inlineStack[i].hash && fData->getName() == inlineStack[i].name)
			return true;
	}
	return false;
}

bool Script::addFunctionInline(string name, string returnLoc)
{
	if (isFunctionInInlineStack(name))
		return false;
	inlineStack.push_back({ Utils::Hashing::Joaat(name.c_str()) , name, getInlineJumpLabelAppend() + "_" + returnLoc });
	return true;
}

bool Script::addFunctionInline(const FunctionData * fData, string returnLoc)
{
	if (isFunctionInInlineStack(fData))
		return false;
	inlineStack.push_back({ fData->getHash() , fData->getName(), getInlineJumpLabelAppend() + "_" + returnLoc });
	return true;
}
void Script::removeFunctionInline(string name)
{
	assert(inlineStack.size() && "Empty Inline stack");
	assert(inlineStack.back().name == name && "Function isnt at top of Inline Stack");
	inlineStack.pop_back();
}

void Script::removeFunctionInline(const FunctionData *fData)
{
	assert(inlineStack.size() && "Empty Inline stack");
	assert(inlineStack.back().name == fData->getName() && "Function isnt at top of Inline Stack");
	inlineStack.pop_back();
}

int Script::addStaticDecl(string name, int size)
{
	assert(size > 0 && "Static size must be at least 1");
	int index = staticCount;
	staticIndexes[name] = index;
	for (int i = 0; i < size; i++)
	{
		staticTable.push_back(0);//set it to 0 for time being
	}
	index += size;
	return index;
}

int Script::getStaticIndex(string name) const
{
	auto it = staticIndexes.find(name);
	if (it != staticIndexes.end())
	{
		return it->second;
	}
	assert(false && "Static index doesnt exist");
	return -1;
}

void Script::setStaticInit(int index, int val, int offset)
{
	assert(index >= 0 && index + offset < staticTable.size() && "Invalid static index");
	staticTable[index + offset] = val;
}
