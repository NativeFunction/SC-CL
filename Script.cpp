#include "Script.h"
#include "Utils.h"

Script::Script() : entryFunction(new FunctionData("@__builtin__entryPoint", 0)), indirectGoTo(new FunctionData("@__buiiltin__indirectGoTo", 1)), currentFunc(NULL)
{
	functions.push_back(entryFunction);
	functions.push_back(indirectGoTo);
	entryFunction->setBuiltIn();
	indirectGoTo->addOpGetFrame(0);
	indirectGoTo->addOpSetFrame(1);
	indirectGoTo->addOpReturn(1, 0);
	indirectGoTo->setStackSize(3);
	indirectGoTo->setProcessed();
	indirectGoTo->setBuiltIn();
}

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
			entryFunction->addUsedFunc(func);
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

string Script::getStaticsAsString()
{
	string data;
	data.reserve(36 * staticTable.size() + 28);
	data += "SetStaticsCount " + to_string(staticTable.size()) + "\r\n";
	for (uint32_t i = 0, it = 0; i < staticTable.size(); i++)
	{
		if (staticTable[i] != 0)
		{
			if (it < staticTableShortIndexes.size() && staticTableShortIndexes[it] == i)
			{
				it++;
				data += "SetDefaultStatic " + to_string(i) + " " + to_string(Utils::Bitwise::Flip2BytesIn4(staticTable[i])) + "\r\n";
			}
			else
				data += "SetDefaultStatic " + to_string(i) + " " + to_string(Utils::Bitwise::SwapEndian(staticTable[i])) + "\r\n";
		}
			
	}
	data.shrink_to_fit();
	return data;
}