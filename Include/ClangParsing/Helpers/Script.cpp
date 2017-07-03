#include "ClangParsing/Helpers/Script.h"
#include "Utils/Utils.h"
#include "Utils/ConstExpr.h"

using namespace std;

Script::Script(string scriptName, BuildType buildType, Platform platform, bool isSingleton, bool isEntryFunctionPadding, OptimisationLevel optLevel) :
	 mainFunction(NULL), currentFunc(NULL), _bType(buildType), _platform(platform), _scriptName(scriptName), scriptParams(), _isSingleton(isSingleton), EntryFunctionPadding(isEntryFunctionPadding), _optLevel(optLevel)
{
	auto entry = std::make_unique<FunctionData>("__builtin__entryPoint", 0, 0);
	entryFunction = entry.get();
	entryFunction->setBuiltIn();

	initializeEntryFunction();

	functions.push_back(std::move(entry));
	_endian = (buildType == BT_GTAV && platform == P_PC) ? END_LITTLE : END_BIG;
	_stackWidth = (buildType == BT_GTAV && platform == P_PC) ? 8 : 4;
}

FunctionData * Script::createFunction(string name, int paramCount, int returnCount, bool makeCurrent, bool isPrototype)
{
	uint32_t hash = Utils::Hashing::JoaatCased(name.c_str());
	for (int i = 0, max = getFunctionCount(); i<max; i++)
	{
		FunctionData *func = functions[i].get();
		if (hash == func->getHash() && name == func->getName())
		{
			if (isPrototype)
			{
				//assert(!func->isProcessed() && "Function has already been processed");
				//if (func->isProcessed())
					//Utils::System::Warn("Function \"" + name + "\" has already been processed");
			}
			if (makeCurrent)
			{
				currentFunc = func;
			}
			return func;
		}
	}
	functions.push_back(std::make_unique<FunctionData>(name, paramCount, returnCount));
	functions.back()->setOptLevel(getOptLevel());
	if (makeCurrent)
	{
		currentFunc = functions.back().get();
	}
	return functions.back().get();
}

FunctionData * Script::getFunctionFromName(const string& name)
{
	uint32_t hash = Utils::Hashing::JoaatCased(name);
	for (int i = 0, max = getFunctionCount(); i < max;i++)
	{
		const FunctionData *func = getFunctionFromIndex(i);
		if (hash == func->getHash() && name == func->getName())
			return functions[i].get();
	}
	
	Utils::System::Warn("Function \"" + name + "\" does not exist");
	assert(false && "Function doesnt exist");
	return NULL;
}

const FunctionData * Script::getFunctionFromName(const string& name) const
{
	uint32_t hash = Utils::Hashing::JoaatCased(name);
	for (int i = 0, max = getFunctionCount(); i < max; i++)
	{
		const FunctionData *func = getFunctionFromIndex(i);
		if (hash == func->getHash() && name == func->getName())
			return functions[i].get();
	}
	Utils::System::Warn("Function \"" + name + "\" does not exist");
	assert(false && "Function doesnt exist");
	return NULL;
}
void Script::initializeEntryFunction()
{
	if (doesEntryFunctionHavePadding())
	{
		/* Size: 9
		Nop//Push_0
		Nop//CallNative wait 1 0
		Nop
		Nop
		Nop
		Nop//Push_0
		Nop//JumpFalse @-4
		Nop
		Nop
		*/

		entryFunction->addOpNop(9);
	}
	if (isSingleton())
	{
		switch (getBuildType())
		{
			case BT_GTAV:
			entryFunction->addOpNative("get_hash_of_this_script_name", (getBuildPlatform() == P_PC ? 0x8A1C8B1738FFE87E : JoaatConst("get_hash_of_this_script_name")), 0, 1);
			entryFunction->addOpNative("_get_number_of_instances_of_streamed_script", (getBuildPlatform() == P_PC ? 0x2C83A9DA6BFFC4F9 : 0x029D3841), 1, 1);
			entryFunction->addOpPushInt(1);
			entryFunction->addOpJumpGT("__builtin__singleton__");
			break;
			case BT_GTAIV_TLAD:
			case BT_GTAIV_TBOGT:
			case BT_GTAIV:
			entryFunction->addOpPushString(getScriptName());//no native for getting the name of a script at runtime
			entryFunction->addOpNative("get_number_of_instances_of_streamed_script", (getBuildPlatform() == P_PC ? 0x5A1C52C7 : JoaatConst("get_number_of_instances_of_streamed_script")), 1, 1);// iv native takes a string
			entryFunction->addOpPushInt(1);
			entryFunction->addOpJumpGT("__builtin__singleton__");
			Utils::System::Warn("Singleton scripts for GTA IV only work when you dont change the name of the output sco file");
			break;
			default:
			Utils::System::Warn("Singleton scripts are only supported on GTA IV and GTA V");
			break;
		}
	}
}
void Script::finaliseEntryFunction()
{
	lockReservedStaticBlock();
	if (mainFunction)
	{
		entryFunction->addUsedFunc(mainFunction);
		if (scriptParams)
		{
			if (getBuildType() == BT_RDR_XSC || getBuildType() == BT_RDR_SCO)
			{
				scriptParams->setUsed(*this);
				entryFunction->setUsed(*this);
			}
			else
			{
				entryFunction->setUsed(*this);
				scriptParams->setUsed(*this);
			}
			if (scriptParams->getSize() > 1)
			{
				entryFunction->addOpPushInt(scriptParams->getSize());
				entryFunction->addOpGetStaticP(scriptParams.get());
				entryFunction->addOpToStack();
			}
			else if (scriptParams->getSize())
			{
				entryFunction->addOpGetStatic(scriptParams.get());
			}
		}
		else
		{
			entryFunction->setUsed(*this);
		}
		entryFunction->addOpCall(mainFunction);
		for (int i = 0; i < mainFunction->getReturnCount(); i++)
		{
			entryFunction->addOpDrop();
			entryFunction->pushComment("dropping main returns");
		}
		if (isSingleton())
		{
			entryFunction->addOpLabel("__builtin__singleton__");
		}
		entryFunction->addOpReturn();
		entryFunction->setProcessed();
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
string Script::getPlatformAbv() const
{
	const int BT = getBuildType();
	switch (getBuildPlatform())
	{
		case P_X360: return "x";
		case P_PS3: return "c";
		case P_PC: return (BT == BT_GTAIV || BT == BT_GTAIV_TLAD || BT == BT_GTAIV_TBOGT) ? "w" : "y";
	}
	Utils::System::Throw("No platform selected");
	return 0;
}
string Script::getPlatformAbvUpper() const
{
	const int BT = getBuildType();
	switch (getBuildPlatform())
	{
		case P_X360: return "X";
		case P_PS3: return "C";
		case P_PC: return (BT == BT_GTAIV || BT == BT_GTAIV_TLAD || BT == BT_GTAIV_TBOGT) ? "W" : "Y";
	}
	Utils::System::Throw("No platform selected");
	return 0;
}
string Script::getBuildTypeExt() const
{
	switch (getBuildType())
	{
		case BT_GTAIV_TLAD:
		case BT_GTAIV_TBOGT:
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
		case BT_GTAIV_TLAD:
		case BT_GTAIV_TBOGT:
		case BT_GTAIV: return "sco";
		case BT_GTAV:
		case BT_RDR_XSC: return getPlatformAbv() + "sc";
	}
	return "xsc";
}

