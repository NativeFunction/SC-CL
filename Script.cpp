#include "Script.h"
#include "Utils.h"

Script::Script(string scriptName, BuildType buildType, Platform platform) : entryFunction(new FunctionData("@__builtin__entryPoint", 0, 0)), indirectGoTo(new FunctionData("@__buiiltin__indirectGoTo", 1, 0)), currentFunc(NULL), _scriptName(scriptName), _bType(buildType), _platform(platform)
{
	functions.push_back(entryFunction);
	functions.push_back(indirectGoTo);
	entryFunction->setBuiltIn();
	indirectGoTo->addOpGetFrame(0);
	indirectGoTo->addOpSetFrame(1);
	indirectGoTo->addOpReturn();
	indirectGoTo->setStackSize(3);
	indirectGoTo->setProcessed();
	indirectGoTo->setBuiltIn();
}

FunctionData * Script::createFunction(string name, int paramCount, int returnCount, bool makeCurrent)
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
	FunctionData *newFunc = new FunctionData(name, paramCount, returnCount);
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

void Script::finaliseEntryFunction()
{
	if (mainFunction)
	{
		entryFunction->addOpCall("main");
		for (int i = 0; i < mainFunction->getReturnCount(); i++)
		{
			entryFunction->addOpDrop();
			entryFunction->pushComment("dropping main returns");
		}
		entryFunction->addOpReturn();
		entryFunction->addUsedFunc(mainFunction);
		entryFunction->setProcessed();
		entryFunction->setUsed();
	}
	else
	{
		Utils::System::Throw("Main Function not found");
	}
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
	inlineStack.push_back({ Utils::Hashing::Joaat(name.c_str()) , name, getInlineJumpLabelAppend() + "_" + returnLoc, getFunctionFromName(name)->isUnsafe() });
	return true;
}

bool Script::addFunctionInline(const FunctionData * fData, string returnLoc)
{
	if (isFunctionInInlineStack(fData))
		return false;
	inlineStack.push_back({ fData->getHash() , fData->getName(), getInlineJumpLabelAppend() + "_" + returnLoc, fData->isUnsafe() });
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

bool Script::isUnsafeContext() const
{
	if (inlineStack.size())
	{
		return inlineStack.back().unsafe;
	}
	return currentFunc->isUnsafe();
}

string Script::getStaticsAsString()
{
	string data;
	data.reserve(73 * staticTable.size() + 28);
	data += "//> Default Static Information\r\nSetStaticsCount " + to_string(staticTable.size()) + "\r\n";
	for (uint32_t i = 0, it = 0; i < staticTable.size(); i++)
	{
		if (staticTable[i] != 0)
		{
			if (it < staticTableShortIndexes.size() && staticTableShortIndexes[it] == i)
			{
				it++;
				int32_t shortData = Utils::Bitwise::Flip2BytesIn4(staticTable[i]);
				int16_t* shortDataP = (int16_t*)&shortData;
				*shortDataP = Utils::Bitwise::SwapEndian(*shortDataP);
				shortDataP++;
				*shortDataP = Utils::Bitwise::SwapEndian(*shortDataP);
				data += "SetDefaultStatic " + to_string(i) + " " + to_string(shortData) + "\r\n";
			}
			else
				data += "SetDefaultStatic " + to_string(i) + " " + to_string(Utils::Bitwise::SwapEndian(staticTable[i])) + "\r\n";
		}
	}
	data += "//<\r\n";
	data.shrink_to_fit();
	return data;
}

string Script::getPlatformAbv() const
{
	switch (getBuildPlatform())
	{
		case P_XBOX: return "x";
		case P_PS3: return "c";
		case P_PC: return getBuildType() == BT_GTAIV ? "w" : "y";
	}
	Utils::System::Throw("No platform selected");
	return 0;
}
string Script::getPlatformAbvUpper() const
{
	switch (getBuildPlatform())
	{
		case P_XBOX: return "X";
		case P_PS3: return "C";
		case P_PC: return getBuildType() == BT_GTAIV ? "W" : "Y";
	}
	Utils::System::Throw("No platform selected");
	return 0;
}
string Script::getBuildTypeExt() const
{
	switch (getBuildType())
	{
		case BT_GTAIV: return "sca";//it would be cool to support gta 4 at some point but its not a priority
		case BT_RDR_XSC: return getPlatformAbv() + "sa";
		case BT_RDR_SCO: return "sca2";
		case BT_GTAV: return getPlatformAbv() + "sa2";
	}
	return "asm";
}

string Script::getCompiledOutputExt() const
{
	switch (getBuildType())
	{
		case BT_RDR_SCO:
		case BT_GTAIV: return "sco";
		case BT_GTAV:
		case BT_RDR_XSC: return getPlatformAbv() + "sc";
	}
	return "xsc";
}

