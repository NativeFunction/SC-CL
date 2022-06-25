#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <ctime>
#include "OpcodeConsts.h"
#include "Utils/ConstExpr.h"
#include "ClangParsing/GlobalDecls.h"
#include "ClangParsing/Helpers/FunctionData.h"
#include "ClangParsing/Helpers/Script.h"
#include "Utils/Utils.h"
#include "ClangParsing/CommandLineOptions.h"
#include "BuildTarget.h"

#pragma region Collections
class PageCollection{
protected:
	std::vector<std::vector<uint8_t>> Pages;
	std::vector<uint8_t>* lastPage;
public:
	bool DoesPageRequirePadding = true;

	PageCollection(){
		std::vector<uint8_t> newPage;
		newPage.reserve(0x4000);
		Pages.push_back(std::move(newPage));
		lastPage = &Pages.back();
	}
	void AddNewPage(uint8_t nopVal){
		lastPage->resize(0x4000, nopVal);//fill last page with nops
		std::vector<uint8_t> newPage;
		newPage.reserve(0x4000);
		Pages.push_back(std::move(newPage));
		lastPage = &Pages.back();
	}
	uint32_t getPageCount()const{ return (uint32_t)Pages.size(); }

	uint32_t getPageCountIgnoreEmpty()const {
		return (uint32_t)(lastPage->size() ? Pages.size() : Pages.size() - 1);
	}

	uint32_t getTotalSize()const {
		return (uint32_t)((Pages.size() - 1) << 14) + getLastPageSize();
	}
	uint32_t getPageSize(int PageIndex)const
	{
		return (uint32_t)Pages[PageIndex].size();
	}
	uint32_t getLastPageSize()const{
		return (uint32_t)lastPage->size();
	}
	uint32_t getLastPageSizeIgnoreEmpty()const{
		if (lastPage->size()){
			return (uint32_t)lastPage->size();
		}
		if (getPageCount() > 1){
			return 0x4000;
		}
		else{
			return 0;
		}
	}
	uint8_t* getPositionAddress(size_t position){
		assert(position < getTotalSize() && "Code position out of range");

		if (DoesPageRequirePadding)
		{
			assert(position >> 14 < Pages.size() && "Code position out of page range");
			return  Pages[position >> 14].data() + (position & 0x3FFF);
		}
		else
			return Pages[0].data() + position;

	}
	uint8_t* getPageAddress(size_t pageIndex){
		assert(pageIndex < getPageCount() && "Page index out of range");
		return Pages[pageIndex].data();
	}
	//Ensures there is enough space in the current code page for a specific opcode
	//Returns true if a new page needed to be created to fit the desired amount of bytes
	bool reserveBytes(size_t byteCount, uint8_t nopVal){
		if (DoesPageRequirePadding && lastPage->size() + byteCount >= 0x4000){
			AddNewPage(nopVal);
			return true;
		}
		return false;
	}
	void AddPadding(const uint32_t paddingCount, uint8_t nopVal){
		lastPage->resize(lastPage->size() + paddingCount, nopVal);
	}
};

class CodePageCollection : public PageCollection{
public:
	CodePageCollection(){}

	void AddInt8(const uint8_t value){
		lastPage->push_back(value);
	}
	void changeInt8(const uint8_t newValue, const size_t position){
		*getPositionAddress(position) = newValue;
	}
	virtual void AddInt16(const int16_t value) = 0;
	virtual void ChangeInt16(const int16_t newValue, const size_t position) = 0;

	virtual void AddInt24(const uint32_t value) = 0;
	virtual void ChangeInt24(const uint32_t newValue, const size_t position) = 0;

	virtual void AddInt32(const uint32_t value) = 0;
	virtual void ChangeInt32(const uint32_t newValue, const size_t position) = 0;

	virtual void AddFloat(const float value) = 0;

	void AddString(const std::string str, bool incNullTerminator = true){
		auto curSize = lastPage->size();
		auto strSize = str.size() + (incNullTerminator ? 1 : 0);
		lastPage->resize(curSize + strSize);
		memcpy(lastPage->data() + curSize, str.data(), strSize);
	}

};
class CodePageCollectionBig : public CodePageCollection{
public:
	void AddInt16(const int16_t value)override{
		lastPage->resize(lastPage->size() + 2, 0);
		*((int16_t*)(lastPage->data() + lastPage->size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
	void ChangeInt16(const int16_t newValue, const size_t position)override{
		*(int16_t*)getPositionAddress(position) = Utils::Bitwise::SwapEndian(newValue);
	}

	void AddInt24(const uint32_t value)override{
		lastPage->resize(lastPage->size() + 3, 0);
		*((uint32_t*)(lastPage->data() + lastPage->size()) - 1) |= Utils::Bitwise::SwapEndian(value & 0xFFFFFF);
	}
	void ChangeInt24(const uint32_t newValue, const size_t position)override{
		*(uint32_t*)(getPositionAddress(position) - 1) |= Utils::Bitwise::SwapEndian(newValue & 0xFFFFFF);
	}

	void AddInt32(const uint32_t value)override{
		lastPage->resize(lastPage->size() + 4, 0);
		*((uint32_t*)(lastPage->data() + lastPage->size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
	void ChangeInt32(const uint32_t newValue, const size_t position)override{
		*(uint32_t*)getPositionAddress(position) = Utils::Bitwise::SwapEndian(newValue);
	}

	void AddFloat(const float value)override{
		lastPage->resize(lastPage->size() + 4, 0);
		*((float*)(lastPage->data() + lastPage->size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
};
class CodePageCollectionLit : public CodePageCollection{
public:
	void AddInt16(const int16_t value)override{
		lastPage->resize(lastPage->size() + 2, 0);
		*((int16_t*)(lastPage->data() + lastPage->size()) - 1) = value;
	}
	void ChangeInt16(const int16_t newValue, const size_t position)override{
		*(int16_t*)getPositionAddress(position) = newValue;
	}

	void AddInt24(const uint32_t value)override{
		lastPage->resize(lastPage->size() + 3, 0);
		*((uint32_t*)(lastPage->data() + lastPage->size()) - 1) |= (value & 0xFFFFFF) << 8;
	}
	void ChangeInt24(const uint32_t newValue, const size_t position)override{
		*(uint32_t*)(getPositionAddress(position) - 1) |= (newValue & 0xFFFFFF) << 8;
	}

	void AddInt32(const uint32_t value)override{
		lastPage->resize(lastPage->size() + 4, 0);
		*((uint32_t*)(lastPage->data() + lastPage->size()) - 1) = value;
	}
	void ChangeInt32(const uint32_t newValue, const size_t position)override{
		*(uint32_t*)getPositionAddress(position) = newValue;
	}
	void AddFloat(const float value)override{
		lastPage->resize(lastPage->size() + 4, 0);
		*((float*)(lastPage->data() + lastPage->size()) - 1) = value;
	}
};

class StringPageCollection : public PageCollection{
private:
	std::unordered_map<std::string, size_t> stringLocationMap;
public:
	StringPageCollection(){}
	size_t AddString(const std::string& value){
		auto it = stringLocationMap.find(value);
		if (it != stringLocationMap.end()){
			return it->second;
		}
		else{
			auto strSize = value.size() + 1;
			reserveBytes(strSize, 0);
			auto index = getTotalSize();
			auto curSize = lastPage->size();
			lastPage->resize(curSize + strSize);
			memcpy(lastPage->data() + curSize, value.data(), strSize);
			stringLocationMap[value] = index;
			return index;
		}
	}
	virtual void ChangeInt32(const uint32_t newValue, const size_t position) = 0;
	uint32_t AddJumpTable(const uint32_t itemCount){
		//lastPage->resize(lastPage->size() + 3 & ~3, 0);
		reserveBytes(itemCount * 4, 0);
		size_t pageStartIndex = lastPage->size();
		auto tableIndex = getTotalSize();
		lastPage->resize(pageStartIndex + itemCount * 4, 0);
		return tableIndex;
	}
	void padAlign(const uint32_t alignment){
		lastPage->resize((lastPage->size() + alignment - 1) & ~(alignment - 1), 0);
	}
};
class StringPageCollectionBig : public StringPageCollection{
public:
	void ChangeInt32(const uint32_t newValue, const size_t position)override{
		*(uint32_t*)getPositionAddress(position) = Utils::Bitwise::SwapEndian(newValue);
	}
};
class StringPageCollectionLit : public StringPageCollection{
public:
	void ChangeInt32(const uint32_t newValue, const size_t position)override{
		*(uint32_t*)getPositionAddress(position) = newValue;
	}
};
#pragma endregion

class CompileBase
{
protected:

	#pragma region Type_Defines
	enum class JumpInstructionType
	{
		Jump, 
		JumpFalse,
		JumpEQ,
		JumpNE,
		JumpGT,
		JumpGE,
		JumpLT,
		JumpLE,
		Switch,
		LabelLoc
	};
	enum class CallInstructionType
	{
		Call,
		FuncLoc
	};
	typedef struct 
	{
		const uint32_t JumpLocation;
		const JumpInstructionType InstructionType;
		const std::string Label;
		bool isSet;
	} JumpData;
	typedef struct
	{
		uint32_t LabelLocation;
		bool isSet;
		std::vector<uint32_t> JumpIndexes;
	} LabelData;
	typedef struct
	{
		JumpData JumpInfo;
		LabelData LabelInfo;
	} JumpLabelData;
	typedef struct
	{
		const uint32_t CallLocation;
		const CallInstructionType InstructionType;
		const FunctionData* Function;
	} CallData;
	typedef struct 
	{
		int32_t CodeBlocks, Unk1, Statics, Natives, StringBlocks, ScriptName, Unk8, Unk9, Unk10;
		std::vector<uint32_t> CodePagePointers;
		std::vector<uint32_t> StringPagePointers;
	} PHO;//placeHolderOffsets
	typedef struct
	{
		uint32_t tableOffset;
		std::string labelName;
		uint32_t xorVal;
	} JumpTableData;//these can be set at the end of compiling a function
	

	/*
	typedef uint32_t relPtr;
	typedef struct
	{
		uint32_t HeaderID;//OBJ\0 = 0x4F424A00
		uint16_t BuildPlatform;
		uint16_t BuildTarget;
		uint32_t UnixTimeOfCompile;

		relPtr CallLabelTable;
		relPtr StaticNameRefTable;
		relPtr FunctonLocTable;
		relPtr StaticNameTable;
		relPtr CodeTable;
		relPtr StaticsTable;
		relPtr StringTable;
	} ObjectFileHeader;

	typedef struct
	{
		std::string FunctionName;
		uint32_t CallOffsetsCount;
		uint32_t CallOffsets[];
	} CallLabelEntry;
	typedef struct
	{
		std::string StaticName;
		uint32_t StaticOffsetsCount;
		uint32_t StaticOffsets[];
	} StaticNameRefTableEntry;
	typedef struct
	{
		std::string FunctionName;
		uint32_t FunctionOffset;
		uint32_t FunctionParamCount;
		uint32_t FunctionReturnCount;
	} FunctionLocEntry;
	typedef struct
	{
		std::string StaticName;
		uint32_t StaticIndex;
	} StaticNameTableEntry;
	typedef struct
	{
		uint16_t CodeTableSize;
		uint8_t CodeTable[];
	} CodeTableEntry;
	typedef struct
	{
		uint16_t StringTableSize;
		uint8_t StringTable[];
	} StringTableEntry;

	void WriteObjectFile(const char* Path, Platform BuildPlatform, BuildType BuildType, vector<CallLabelEntry>& CallLableTable,
						 vector<StaticNameRefTableEntry>& StaticNameRefTable, vector<FunctionLocEntry>& FunctonLocTable, 
						 vector<StaticNameTableEntry>& StaticNameTable, std::unique_ptr<StringPageCollection> StringPageData = nullptr)
	{
		
		ObjectFileHeader Header =
		{
			'OBJ\0',
			BuildPlatform,
			BuildType,
			std::time(0),
		};


		FILE* file = fopen(Path, "wb");
		if (Utils::IO::CheckFopenFile(Path, file))
		{
			fwrite(&Header, 1, sizeof(ObjectFileHeader), file);
			Header.CallLabelTable = (uint32_t)ftell(file);
			fwrite(CallLableTable.data(), 1, CallLableTable.size(), file);
			Header.StaticNameRefTable = (uint32_t)ftell(file);
			fwrite(StaticNameRefTable.data(), 1, StaticNameRefTable.size(), file);
			Header.FunctonLocTable = (uint32_t)ftell(file);
			fwrite(FunctonLocTable.data(), 1, FunctonLocTable.size(), file);
			Header.StaticNameTable = (uint32_t)ftell(file);
			fwrite(StaticNameTable.data(), 1, StaticNameTable.size(), file);
			Header.CodeTable = (uint32_t)ftell(file);
			vector<uint8_t> Buffer(16386);
			for (uint32_t i = 0; i < CodePageData->getPageCount(); i++)
			{
				const size_t PageSize = CodePageData->getPageSize(i);
				assert(PageSize <= 0xFFFF && "CodePage size greater then size of ushort");
				*(uint16_t*)Buffer.data() = PageSize;
				memcpy(Buffer.data() + 2, CodePageData->getPageAddress(i), PageSize);
				fwrite(Buffer.data(), 1, PageSize, file);
			}

			Header.StaticsTable = (uint32_t)ftell(file);
			fwrite(HLData->getNewStaticData(), 1, HLData->getStaticCount() * 4, file);
			
			if (BuildType == BT_GTAV)
			{
				assert(StringPageData && "Invalid String Page Pointer");
				Header.StringTable = (uint32_t)ftell(file);
				for (uint32_t i = 0; i < StringPageData->getPageCount(); i++)
				{
					const size_t PageSize = StringPageData->getPageSize(i);
					assert(PageSize <= 0xFFFF && "StringPage size greater then size of ushort");
					*(uint16_t*)Buffer.data() = PageSize;
					memcpy(Buffer.data() + 2, StringPageData->getPageAddress(i), PageSize);
					fwrite(Buffer.data(), 1, PageSize, file);
				}
			}
			
			fseek(file, 0, SEEK_SET);
			fwrite(&Header, 1, sizeof(ObjectFileHeader), file);

			fclose(file);
		}

	}
	*/
	
	#pragma endregion

	#pragma region Parsed_Data_Vars
	std::unique_ptr<CodePageCollection> CodePageData;//opcode data
	std::unordered_map<std::string, LabelData> LabelLocations;//label ,data index
	std::vector<JumpData> JumpLocations;//JumpLocations to fill after building the CodePageData for a function
	uint32_t SignedJumpLocationInc = 0, UnsignedJumpLocationInc = 0;
	std::unordered_map<const FunctionData*, uint32_t> FuncLocations;//call, data index
	std::vector<CallData> CallLocations;//CallLocations to fill after building the CodePageData
	std::unordered_map<uint32_t, uint32_t> NativeHashMap;//hash, index  (native hash map has index start of 1) (hash map list for NativesList to limit find recursion)
	std::vector<JumpTableData> jumpTableLocs;

	#pragma endregion

	#pragma region Parse_Data_Vars
	OpCodes* BaseOpcodes;//dynamic opcode list
	const Script* HLData;//data to parse(High Level Data)
	const uint32_t ReadBufferSize = 0;
	uint32_t FunctionCount = 0;
	uint32_t InstructionCount = 0;
	const bool DisableFunctionNames = false;
	#pragma endregion

	#pragma region Write_Data_Vars
	
	PHO SavedOffsets = {};
	int32_t headerLocation = 0;
	uint32_t headerFlag = 0;
	std::vector<uint8_t> BuildBuffer;
	uint8_t FilePadding = 0;
	#pragma endregion


	#define DATA HLData->getFunctionFromIndex(FunctionCount)->getInstruction(InstructionCount)
	#define AddOpcode(op) AddInt8(BaseOpcodes->op);

	CompileBase(OpCodes& Op, const Script& data, const uint32_t Function_Count, const uint32_t Instruction_Count, bool Disable_Function_Names) :
		BaseOpcodes(&Op), 
		HLData(&data), 
		ReadBufferSize(data.getBuildPlatform() == Platform::P_PSX ? 8192 : 16384),
		FunctionCount(Function_Count),
		InstructionCount(Instruction_Count),
		DisableFunctionNames(Disable_Function_Names)
	{
		//Set Endian
		const int BT = HLData->getBuildType();
		if ((HLData->getBuildPlatform() == Platform::P_PC && BT == BT_GTAV) || BT == BT_RDR2 || (BT == BT_GTAIV || BT == BT_GTAIV_TLAD || BT == BT_GTAIV_TBOGT))
		{
			CodePageData = std::make_unique<CodePageCollectionLit>();
			AddInt32toBuff = &CompileBase::AddInt32toBuffL;
			ChangeInt32inBuff = &CompileBase::ChangeInt32inBuffL;
			AddInt64toBuff = &CompileBase::AddInt64toBuffL;
			ChangeInt64inBuff = &CompileBase::ChangeInt64inBuffL;
		}
		else
		{
			CodePageData = std::make_unique<CodePageCollectionBig>();
			AddInt32toBuff = &CompileBase::AddInt32toBuffB;
			ChangeInt32inBuff = &CompileBase::ChangeInt32inBuffB;
			AddInt64toBuff = &CompileBase::AddInt64toBuffB;
			ChangeInt64inBuff = &CompileBase::ChangeInt64inBuffB;
		}
	}
	virtual ~CompileBase() {};

	virtual void Compile(const std::string& outDirectory) = 0;

	#pragma region Data_Functions
	void AddString(const std::string& str)//Override: GTAV
	{
		CodePageData->AddString(str);
	}
	void AddPadding(const uint32_t paddingCount)
	{
		CodePageData->AddPadding(paddingCount, BaseOpcodes->Nop);
	}

    void ReserveBytes(const uint32_t paddingCount)
    {
        CodePageData->reserveBytes(paddingCount, BaseOpcodes->Nop);
    }
	void AddInt8(const uint8_t value){
		CodePageData->AddInt8(value);
	}
	void AddInt16(const int16_t value){
		CodePageData->AddInt16(value);
	}
	void AddInt24(const uint32_t value){
		CodePageData->AddInt24(value);
	}
	void AddInt32(const uint32_t value){
		CodePageData->AddInt32(value);
	}
	void AddFloat(const float value){
		CodePageData->AddFloat(value);
	}
	void ChangeInt16InCodePage(const int16_t value, const size_t index){
		CodePageData->ChangeInt16(value, index);
	}
	void ChangeInt24InCodePage(const uint32_t value, const size_t index){
		CodePageData->ChangeInt24(value, index);
	}
	void ChangeInt32InCodePage(const uint32_t value, const size_t index){
		CodePageData->ChangeInt32(value, index);
	}
	virtual void AddLabel(const std::string& label);
	void AddFuncLabel(const FunctionData* function)
	{
		if (FuncLocations.find(function) == FuncLocations.end())
			FuncLocations.insert({ function, CodePageData->getTotalSize() });
		else
			Utils::System::Throw("Cannot add function. function \"" + function->getName() + "\" already exists.");
	}
	virtual void AddJumpLoc(const JumpInstructionType it, const std::string& label)
	{
		// this should only be called on jump forward
		JumpLocations.push_back({ (uint32_t)CodePageData->getTotalSize(), it, label, false });
		LabelLocations[label].JumpIndexes.push_back(JumpLocations.size() - 1);
		switch (it)
		{
			case JumpInstructionType::Switch:
			case JumpInstructionType::Jump:
			case JumpInstructionType::JumpFalse:
			case JumpInstructionType::JumpEQ:
			case JumpInstructionType::JumpNE:
			case JumpInstructionType::JumpGT:
			case JumpInstructionType::JumpGE:
			case JumpInstructionType::JumpLT:
			case JumpInstructionType::JumpLE:		AddInt16(0); break;
			case JumpInstructionType::LabelLoc:		AddInt24(0); break;
			default: assert(false && "Invalid Type");
		}
	}
	virtual void AddJump(const JumpInstructionType type, const std::string& label);//Override: GTAIV
	virtual JumpLabelData AddSwitchJump(const JumpInstructionType type, const std::string& label);
	uint32_t AddNative(const uint32_t hash)
	{
		std::unordered_map<uint32_t, uint32_t>::iterator findRes = NativeHashMap.find(hash);
		const uint32_t size = NativeHashMap.size();
		if (findRes != NativeHashMap.end())
			return findRes->second;
		else
			NativeHashMap.insert({ hash, size });
		return size;
	}
	void DoesOpcodeHaveRoom(const size_t OpcodeLen)
	{
		if (CodePageData->reserveBytes(OpcodeLen, BaseOpcodes->Nop))
		{
			CheckSignedJumps();
			CheckUnsignedJumps();
		}
	}
	virtual void CheckSignedJumps();
	virtual void CheckUnsignedJumps();
	bool FindNextSignedJumpLocation()
	{
		for (; SignedJumpLocationInc < JumpLocations.size() && (JumpLocations[SignedJumpLocationInc].isSet || JumpLocations[SignedJumpLocationInc].InstructionType == JumpInstructionType::LabelLoc || JumpLocations[SignedJumpLocationInc].InstructionType == JumpInstructionType::Switch);  SignedJumpLocationInc++);

		return SignedJumpLocationInc < JumpLocations.size();
	}
	bool FindNextUnsignedJumpLocation()
	{
		for (; UnsignedJumpLocationInc < JumpLocations.size() && (JumpLocations[UnsignedJumpLocationInc].isSet || JumpLocations[UnsignedJumpLocationInc].InstructionType != JumpInstructionType::Switch); UnsignedJumpLocationInc++);

		return UnsignedJumpLocationInc < JumpLocations.size();
	}

	#pragma endregion

	#pragma region Opcode_Functions
	virtual void AddFunction(const FunctionData* function, bool disableFunctionName)
	{
		if (disableFunctionName || function->isBuiltIn())
		{
			DoesOpcodeHaveRoom(5);
			AddFuncLabel(function);
			AddOpcode(Function);
			AddInt8(function->getParamCount());
			AddInt16(function->getStackSize());
			AddInt8(0);//unused function name
		}
		else		
		{
			const std::string& name = function->getName();
			DoesOpcodeHaveRoom(5 + name.size());
			AddFuncLabel(function);
			AddOpcode(Function);
			AddInt8(function->getParamCount());
			AddInt16(function->getStackSize());
			AddInt8(function->getName().size());
			CodePageData->AddString(name, false);
		}
	}
	virtual void PushInt(const int32_t Literal);//Override: GTAIV
	void PushInt(){ PushInt(DATA->getInt()); }
	virtual void PushBytes();//Override: GTAIV
	virtual void PushFloat(const float Literal);//Override: GTAIV
	void PushFloat(){ PushFloat(DATA->getFloat()); }
	virtual void PushString();//Override: GTAV
	virtual void CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount) = 0;
	virtual void Return() { DoesOpcodeHaveRoom(3); AddOpcode(Return); AddInt8(DATA->getByte(0)); AddInt8(DATA->getByte(1)); };//Override: RDR
	virtual void GetArrayP();//Override: GTAIV
	virtual void GetArray();//Override: GTAIV
	virtual void SetArray();//Override: GTAIV
	virtual void GetFrameP();//Override: GTAIV
	virtual void GetFrame();//Override: GTAIV
	virtual void SetFrame();//Override: GTAIV
	virtual void GetStaticP();//Override: GTAIV
	virtual void GetStaticPRaw();//Override: GTAIV
	virtual void GetStatic();//Override: GTAIV
	virtual void GetStaticRaw();//Override: GTAIV
	virtual void SetStatic();//Override: GTAIV
	virtual void SetStaticRaw();//Override: GTAIV
	virtual void GetGlobalP();//Override: GTAIV
	virtual void GetGlobal();//Override: GTAIV
	virtual void SetGlobal();//Override: GTAIV
	virtual void StrCopy() { DoesOpcodeHaveRoom(2); AddOpcode(StrCopy); AddInt8(DATA->getByte(0)); };//Override: GTAIV
	virtual void ItoS() { DoesOpcodeHaveRoom(2); AddOpcode(ItoS); AddInt8(DATA->getByte(0)); };;//Override: GTAIV
	virtual void StrAdd() { DoesOpcodeHaveRoom(2); AddOpcode(StrAdd); AddInt8(DATA->getByte(0)); };;//Override: GTAIV
	virtual void StrAddI() { DoesOpcodeHaveRoom(2); AddOpcode(StrAddi); AddInt8(DATA->getByte(0)); };;//Override: GTAIV
	virtual void pCall() { AddOpcode(pCall); };//Override: GTAIV
	virtual void GetHash() = 0;
	virtual void Call() = 0;
	virtual void AddFuncLoc(const FunctionData* function);
	virtual void Switch();//for gta4 switches override AddJump
	virtual void AddImm(const int32_t Literal);//Override: GTAIV
	void AddImm(){ AddImm(DATA->getInt()); }
	virtual void MultImm(const int32_t Literal);//Override: GTAIV
	void MultImm(){ MultImm(DATA->getInt()); }
	virtual void FAddImm();
	virtual void FMultImm();
	virtual void GetImmPStack() = 0;
	virtual void GetImmP() { AddImm((uint32_t)DATA->getUShort(0) * 4); };//Override: GTAV
	virtual void GetImm() = 0;
	virtual void SetImm() = 0;
	virtual void GoToStack() = 0;
	virtual void AddJumpTable() = 0;
	virtual void Shift_Left() { CallNative(JoaatConst("shift_left"), 2, 1); }//Override: GTAVPC, GTAIVPC
	virtual void Shift_Right() { CallNative(JoaatConst("shift_right"), 2, 1); }//Override: GTAVPC, GTAIVPC
	
	#pragma endregion

	#pragma region Write_Functions

	void ClearWriteVars()
	{
		SavedOffsets = {};
		headerLocation = 0;
		headerFlag = 0;
		BuildBuffer.clear();
	}
	void (CompileBase::*AddInt32toBuff)(int32_t value);
	#define AddInt32toBuff (this->*AddInt32toBuff)
	void AddInt32toBuffB(int32_t value)
	{
		BuildBuffer.resize(BuildBuffer.size() + 4, 0);
		*((int32_t*)(BuildBuffer.data() + BuildBuffer.size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
	void AddInt32toBuffL(int32_t value)
	{
		BuildBuffer.resize(BuildBuffer.size() + 4, 0);
		*((int32_t*)(BuildBuffer.data() + BuildBuffer.size()) - 1) = value;
	}
	void (CompileBase::*ChangeInt32inBuff)(int32_t value, uint32_t index);
	#define ChangeInt32inBuff (this->*ChangeInt32inBuff)
	void ChangeInt32inBuffB(int32_t value, uint32_t index)
	{
		*(int32_t*)(BuildBuffer.data() + index) = Utils::Bitwise::SwapEndian(value);
	}
	void ChangeInt32inBuffL(int32_t value, uint32_t index)
	{
		*(int32_t*)(BuildBuffer.data() + index) = value;
	}
	void (CompileBase::*AddInt64toBuff)(int64_t value);
	#define AddInt64toBuff (this->*CompileBase::AddInt64toBuff)
	void AddInt64toBuffL(int64_t value)
	{
		BuildBuffer.resize(BuildBuffer.size() + 8, 0);
		*((int64_t*)(BuildBuffer.data() + BuildBuffer.size()) - 1) = value;
	}
	void AddInt64toBuffB(int64_t value)
	{
		BuildBuffer.resize(BuildBuffer.size() + 8, 0);
		*((int64_t*)(BuildBuffer.data() + BuildBuffer.size()) - 1) = Utils::Bitwise::SwapEndian(value);
	}
	void (CompileBase::*ChangeInt64inBuff)(int64_t value, uint32_t index);
	#define ChangeInt64inBuff (this->*ChangeInt64inBuff)
	void ChangeInt64inBuffL(int64_t value, uint32_t index)
	{
		*(int64_t*)(BuildBuffer.data() + index) = value;
	}
	void ChangeInt64inBuffB(int64_t value, uint32_t index)
	{
		*(int64_t*)(BuildBuffer.data() + index) = Utils::Bitwise::SwapEndian(value);
	}

	uint32_t GetSpaceLeft(uint32_t size)
	{
		const uint32_t rem = size - (BuildBuffer.size() % size);
		return rem == 0 ? size : rem;
	}
	void FillPageNops()
	{
		BuildBuffer.resize(BuildBuffer.size() + GetSpaceLeft(16384), 0);
	}
	void FillPageDynamic(uint32_t amount)
	{
		BuildBuffer.resize(BuildBuffer.size() + GetSpaceLeft(amount), FilePadding);
	}
	void PadNops()
	{
		const int32_t pad = 16 - BuildBuffer.size() % 16;
		if (pad == 0 || pad == 16)
			return;
		else if (pad > 16384)
			Utils::System::Throw("Pad Over 16364");

		BuildBuffer.resize(BuildBuffer.size() + pad, 0);
	}
	int32_t GetPadExpectedAmount(int32_t val)
	{
		const int32_t pad = 16 - val % 16;
		return pad == 0 || pad == 16 ? val : pad + val;
	}
	void Pad()
	{
		const int32_t pad = 16 - BuildBuffer.size() % 16;
		if (pad == 0 || pad == 16)
			return;
		else if (pad > 16384)
			Utils::System::Throw("Pad Over 16364");

		BuildBuffer.resize(BuildBuffer.size() + pad, FilePadding);
	}
	void ForcePad()
	{
		const int32_t pad = 16 - BuildBuffer.size() % 16;
		if (pad == 0 || pad == 16)
		{
			BuildBuffer.resize(BuildBuffer.size() + 16, FilePadding);
			return;
		}
		else if (pad > 16384)
			Utils::System::Throw("ForcePad Over 16364");
		else 
			BuildBuffer.resize(BuildBuffer.size() + pad, FilePadding);
	}
	int32_t IntToPointerInt(int32_t x) { return 0x50000000 | x; }
	

	void WriteCodePagesNoPadding();
	void Write16384CodePages();
	void WriteFinalCodePage();
	void WriteNativesNoPadding();
	virtual void WriteNatives();
	virtual void WriteStaticsNoPadding();
	virtual void WriteStatics();
	virtual void WriteHeader() = 0;
	virtual void WritePointers() = 0;

	#pragma endregion
	
	#pragma region Parse_Functions
	void CheckLabels();
	virtual void BuildTables();
	virtual void fixFunctionJumps() = 0;
	virtual void fixFunctionCalls() = 0;
	void ParseGeneral(const OpcodeKind OK);
	#pragma endregion

	#pragma region Object File Functions



	#pragma endregion
};

class CompileGTAIV : public CompileBase
{
public:
	CompileGTAIV(const Script& data, bool Disable_Function_Names) : CompileBase(GTAIVOpcodes, data, 0, 0, Disable_Function_Names) 
	{ 
		CodePageData->DoesPageRequirePadding = false; 
	}

	void Compile(const std::string& outDirectory) override
	{
		BuildTables();
		switch (HLData->getBuildType())
		{
			case BT_GTAIV_TLAD:
			case BT_GTAIV_TBOGT:
			case BT_GTAIV:
                
                switch (SCCL::Option_GTAIVSCRFlag)
                {
                    case GTAIVSCRFlags::SCRF_Standard:
                        SCOWrite((outDirectory + HLData->getBuildFileName()).data(), SCRFlags::Standard);
                        break;
                    case GTAIVSCRFlags::SCRF_Encrypted:
                        SCOWrite((outDirectory + HLData->getBuildFileName()).data(), SCRFlags::Encrypted);
                        break;
                    case GTAIVSCRFlags::SCRF_CompressedEncrypted:
                        SCOWrite((outDirectory + HLData->getBuildFileName()).data(), SCRFlags::CompressedEncrypted);
                        break;
                }
			
			break;
			default:
				TEST(false, "Incompatible build type for GTAIV");
			break;
		}
	}
private:
	//visual studio plz... designated initializers were added in 1999 get with the times
	OpCodes GTAIVOpcodes = { IVO_Nop, IVO_Add, IVO_Sub, IVO_Mult, IVO_Div, IVO_Mod, IVO_Not, IVO_Neg, IVO_CmpEq, IVO_CmpNe, IVO_CmpGt, IVO_CmpGe, IVO_CmpLt, IVO_CmpLe, IVO_fAdd, IVO_fSub, IVO_fMult, IVO_fDiv, IVO_fMod, IVO_fNeg, IVO_fCmpEq, IVO_fCmpNe, IVO_fCmpGt, IVO_fCmpGe, IVO_fCmpLt, IVO_fCmpLe, IVO_vAdd, IVO_vSub, IVO_vMult, IVO_vDiv, IVO_vNeg, IVO_And, IVO_Or, IVO_Xor, IVO_ItoF, IVO_FtoI, IVO_FtoV, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Push, IVO_PushF, IVO_Dup, IVO_Drop, IVO_CallNative, IVO_Function, IVO_Return, IVO_pGet, IVO_pSet, IVO_pPeekSet, IVO_ToStack, IVO_FromStack, IVO_Nop, IVO_Nop, IVO_Nop, IVO_GetFrameP1, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_PushS, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_GetFrameP2, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Jump, IVO_JumpFalse, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Call, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Switch, IVO_PushString, IVO_StrCopy, IVO_ItoS, IVO_StrAdd, IVO_StrAddi, IVO_MemCopy, IVO_Catch, IVO_Throw, IVO_Nop, IVO_Push_Neg1, IVO_Push_0, IVO_Push_1, IVO_Push_2, IVO_Push_3, IVO_Push_4, IVO_Push_5, IVO_Push_6, IVO_Push_7, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_Nop, IVO_PushStringNull, IVO_JumpTrue, IVO_GetFrameP0, IVO_GetFrameP3, IVO_GetFrameP4, IVO_GetFrameP5, IVO_GetFrameP6, IVO_GetFrameP7, IVO_GetFrameP, IVO_GetGlobalP, IVO_GetStaticP, IVO_GetArrayP, IVO_GetXProtect, IVO_SetXProtect, IVO_RefXProtect, IVO_Exit };

	#pragma region Type_Defines
	enum class SCRFlags
	{
		  Standard = 0x5343520D
		, Encrypted = 0x7363720E
		, CompressedEncrypted = 0x5363720E
	};
	enum class SignatureTypes
	{
		GTAIV = 0x0044207E
		, TLAD = 0x3FA5FA2D
		, TBOGT = 0x4AA44B39
	};
	#pragma endregion

	#pragma region Data_Functions
	virtual void AddLabel(const std::string& label) override;
	virtual void AddJumpLoc(const JumpInstructionType it, const std::string& label) override
	{
		// this should only be called on jump forward
		JumpLocations.push_back({ (uint32_t)CodePageData->getTotalSize(), it, label, false });
		LabelLocations[label].JumpIndexes.push_back(JumpLocations.size() - 1);
		switch (it)
		{
			case JumpInstructionType::Switch:
			case JumpInstructionType::Jump:
			case JumpInstructionType::JumpFalse:
			case JumpInstructionType::JumpEQ:
			case JumpInstructionType::JumpNE:
			case JumpInstructionType::JumpGT:
			case JumpInstructionType::JumpGE:
			case JumpInstructionType::JumpLT:
			case JumpInstructionType::JumpLE:
			case JumpInstructionType::LabelLoc:		AddInt32(0); break;
			default: assert(false && "Invalid Type");
		}
	}
	virtual void AddJump(const JumpInstructionType type, const std::string& label) override;
	virtual JumpLabelData AddSwitchJump(const JumpInstructionType type, const std::string& label) override;
	#pragma endregion
	
	#pragma region Opcode_Functions
	virtual void AddFunction(const FunctionData* function, bool disableFunctionName) override
	{
		DoesOpcodeHaveRoom(4);
		AddFuncLabel(function);
		AddOpcode(Function);
		AddInt8(function->getParamCount());
		AddInt16(function->getStackSize());
	}
	virtual void PushInt(const int32_t Literal) override;
	void PushInt() { PushInt(DATA->getInt()); }
	virtual void PushBytes() override;
	virtual void PushFloat(const float Literal) override;
	void PushFloat() { PushFloat(DATA->getFloat()); }
	virtual void CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount) override;
	virtual void GetArrayP() override;
	virtual void GetArray() override;
	virtual void SetArray() override;
	virtual void GetFrameP() override;
	virtual void GetFrame() override;
	virtual void SetFrame() override;
	virtual void GetStaticP() override;
	virtual void GetStaticPRaw() override;
	virtual void GetStatic() override;
	virtual void GetStaticRaw() override;
	virtual void SetStatic() override;
	virtual void SetStaticRaw() override;
	virtual void GetGlobalP() override;
	virtual void GetGlobal() override;
	virtual void SetGlobal() override;
	virtual void AddFuncLoc(const FunctionData* function) override;

	//Do these opcodes use code buffer???
	//virtual void StrCopy() override { DoesOpcodeHaveRoom(2); AddOpcode(StrCopy); AddInt8(DATA->getByte(0)); };//Override: GTAIV
	//virtual void ItoS() override { DoesOpcodeHaveRoom(2); AddOpcode(ItoS); AddInt8(DATA->getByte(0)); };//Override: GTAIV
	//virtual void StrAdd() override { DoesOpcodeHaveRoom(2); AddOpcode(StrAdd); AddInt8(DATA->getByte(0)); };//Override: GTAIV
	//virtual void StrAddI() override { DoesOpcodeHaveRoom(2); AddOpcode(StrAddi); AddInt8(DATA->getByte(0)); };//Override: GTAIV
	virtual void pCall() override;
	virtual void AddImm(const int32_t Literal) override;
	virtual void MultImm(const int32_t Literal) override;
	virtual void FAddImm() override;
	virtual void FMultImm() override;

	
	void GetHash() override { CallNative(HLData->getBuildPlatform() == P_PC ? 0x68FF7165 : JoaatConst("get_hash_key"), 1, 1); };
	void Shift_Left() override { CallNative(HLData->getBuildPlatform() == P_PC ? 0x102A0A6C : JoaatConst("shift_left"), 2, 1); };
	void Shift_Right() override { CallNative(HLData->getBuildPlatform() == P_PC ? 0x64DD173C : JoaatConst("shift_right"), 2, 1); };

	void Call() override;
	void GetImmPStack() override;
	void GetImm() override;
	void SetImm() override;
	void GoToStack() override;
	void AddJumpTable() override;
	#pragma endregion

	#pragma region Parse_Functions
	virtual void BuildTables() override;
	void fixFunctionCalls() override;
	void fixFunctionJumps() override;
	#pragma endregion

	#pragma region Write_Functions
	SignatureTypes GetSignature();
	virtual void WriteStaticsNoPadding() override;
	virtual void WriteHeader() override {};
	virtual void WritePointers() override {};
	void SCOWrite(const char* path, SCRFlags flag);
	#pragma endregion
	
};

class CompileRDR : public CompileBase
{
public:
	CompileRDR(const Script& data, bool Disable_Function_Names) : CompileBase(RDROpcodes, data, 0, 0, Disable_Function_Names) 
	{ 
		//do rdr sco files require padding?
		if(HLData->getBuildType() == BT_RDR_SCO)
			CodePageData->DoesPageRequirePadding = false;
	}

	void Compile(const std::string& outDirectory) override
	{
		BuildTables();
		switch (HLData->getBuildType())
		{
			case BT_RDR_SCO:
				SCOWrite((outDirectory + HLData->getBuildFileName()).data(), true);
				break;
			case BT_RDR_XSC:
				XSCWrite((outDirectory + HLData->getBuildFileName()).data(), true);
				break;
			default:
				TEST(false, "Incompatible build type for RDR");
				break;
		}
	}
private:
	//visual studio plz... designated initializers were added in 1999 get with the times
	OpCodes RDROpcodes = { RO_Nop, RO_Add, RO_Sub, RO_Mult, RO_Div, RO_Mod, RO_Not, RO_Neg, RO_CmpEq, RO_CmpNe, RO_CmpGt, RO_CmpGe, RO_CmpLt, RO_CmpLe, RO_fAdd, RO_fSub, RO_fMult, RO_fDiv, RO_fMod, RO_fNeg, RO_fCmpEq, RO_fCmpNe, RO_fCmpGt, RO_fCmpGe, RO_fCmpLt, RO_fCmpLe, RO_vAdd, RO_vSub, RO_vMult, RO_vDiv, RO_vNeg, RO_And, RO_Or, RO_Xor, RO_ItoF, RO_FtoI, RO_FtoV, RO_PushB, RO_PushB2, RO_PushB3, RO_Push, RO_PushF, RO_Dup, RO_Drop, RO_CallNative, RO_Function, RO_Return, RO_pGet, RO_pSet, RO_pPeekSet, RO_ToStack, RO_FromStack, RO_GetArrayP1, RO_GetArray1, RO_SetArray1, RO_GetFrameP1, RO_GetFrame1, RO_SetFrame1, RO_GetStaticP1, RO_GetStatic1, RO_SetStatic1, RO_Add1, RO_Mult1, RO_GetImm1, RO_SetImm1, RO_PushS, RO_Add2, RO_Mult2, RO_GetImm2, RO_SetImm2, RO_GetArrayP2, RO_GetArray2, RO_SetArray2, RO_GetFrameP2, RO_GetFrame2, RO_SetFrame2, RO_GetStaticP2, RO_GetStatic2, RO_SetStatic2, RO_GetGlobalP2, RO_GetGlobal2, RO_SetGlobal2, RO_Jump, RO_JumpFalse, RO_JumpNE, RO_JumpEQ, RO_JumpLE, RO_JumpLT, RO_JumpGE, RO_JumpGT, RO_Nop, RO_GetGlobalP3, RO_GetGlobal3, RO_SetGlobal3, RO_PushI24, RO_Switch, RO_PushString, RO_StrCopy, RO_ItoS, RO_StrAdd, RO_StrAddi, RO_MemCopy, RO_Catch, RO_Throw, RO_pCall, RO_Push_Neg1, RO_Push_0, RO_Push_1, RO_Push_2, RO_Push_3, RO_Push_4, RO_Push_5, RO_Push_6, RO_Push_7, RO_PushF_Neg1, RO_PushF_0, RO_PushF_1, RO_PushF_2, RO_PushF_3, RO_PushF_4, RO_PushF_5, RO_PushF_6, RO_PushF_7, RO_Nop, RO_Nop, RO_Nop, RO_Nop, RO_Call2, RO_Call2h1, RO_Call2h2, RO_Call2h3, RO_Call2h4, RO_Call2h5, RO_Call2h6, RO_Call2h7, RO_Call2h8, RO_Call2h9, RO_Call2hA, RO_Call2hB, RO_Call2hC, RO_Call2hD, RO_Call2hE, RO_Call2hF, RO_PushArrayP, RO_ReturnP0R0, RO_ReturnP0R1, RO_ReturnP0R2, RO_ReturnP0R3, RO_ReturnP1R0, RO_ReturnP1R1, RO_ReturnP1R2, RO_ReturnP1R3, RO_ReturnP2R0, RO_ReturnP2R1, RO_ReturnP2R2, RO_ReturnP2R3, RO_ReturnP3R0, RO_ReturnP3R1, RO_ReturnP3R2, RO_ReturnP3R3, RO_PushStringNull };
	
	#pragma region Type_Defines
	typedef union
	{
		uint32_t Flag[2];
		struct
		{
			DWORD VPage2 : 8;
			DWORD VPage1 : 6;
			DWORD VPage0 : 2;
			DWORD PPage2 : 8;
			DWORD PPage1 : 4;
			DWORD PPage0 : 3;
			DWORD bResource : 1;//true


			DWORD TotalVSize : 14; // TotalVSize (size = TotalVSize * 4096)
			DWORD TotalPSize : 14; // TotalPSize (size = TotalPSize * 4096)
			DWORD ObjectStartPage : 3; // resource starts at the 1st page with size = (0x1000 << ObjectStartPage)
			DWORD bUseExtSize : 1; //true
		};
		
	} RSCFlag;
	#pragma endregion

	#pragma region CallParsing
	uint8_t GetNewCallOpCode(const uint32_t needOffset) const { 
		return needOffset >= 1048576 ? 255 : 82 + (needOffset >> 16); 
	}
	uint16_t GetNewCallOffset(const uint32_t needOffset) const { 
		return needOffset - (((needOffset >> 16)) << 16); 
	}
	int32_t GetCallOffset(const int32_t readOffset, const int32_t opCode) const {
		return readOffset | ((opCode - 82) << 16); 
	}
	#pragma endregion
	#pragma region NativeParsing
	int32_t GetArgCountFromIndex(const uint16_t* Indblock) const {
		return (((uint8_t*)Indblock)[0] & 0x3e) >> 1; 
	}
	int32_t GetIndex(const uint16_t val) const {
		return (((val & 0xFF) << 2) & 0x300) | ((val >> 8) & 0xFF);
	}
	bool FunctionHasReturn(const uint16_t* data) const { 
		return (((uint8_t*)data)[0] & 1) == 1 ? true : false; 
	}
	uint16_t SetNewIndex(const uint16_t index, const int parameterCount, const bool ret) const { 
		return Utils::Bitwise::SwapEndian((uint16_t)(((index & 0xFF00) >> 2) | ((index & 0xFF) << 8) | (ret ? 1 : 0) | (parameterCount << 1)));
	}
	#pragma endregion
	#pragma region RSC85Parsing
	std::vector<size_t> GetPageSizes(uint32_t& size);
	size_t GetHeaderPageIndex(const std::vector<size_t>& DataSizePages);
	uint32_t ObjectStartPageSizeToFlag(size_t value)
	{
		//4096 = 1 << 12;
		//2048 = 1 << 11
		//The -12 should be platform dependent, if the PageShift is different on PS3 then it might be 11
		DWORD r = 0;
		_BitScanReverse(&r, value);
		return r - 12;
	}
	#pragma endregion
	
	#pragma region Opcode_Functions
	void CallNative(const uint64_t hash, const uint8_t paramCount,const uint8_t returnCount) override;
	void Return() override;
	void GetHash() override { CallNative(JoaatConst("string_to_hash"), 1, 1); };
	void Call() override;
	void GetImmPStack() override;
	void GetImm() override;
	void SetImm() override;	
	void GoToStack() override;
	void AddJumpTable() override;
	#pragma endregion
	
	#pragma region Parse_Functions
	void fixFunctionCalls() override;
	void fixFunctionJumps() override;
	#pragma endregion

	#pragma region Write_Functions
	void CheckPad4096(uint32_t& value);
	void WriteHeader() override;
	void WritePointers() override;
	void XSCWrite(const char* path, bool CompressAndEncrypt = true);
	void SCOWrite(const char* path, bool CompressAndEncrypt = true);
	#pragma endregion

};

class CompileGTAV : public CompileBase
{
	friend class CompileGTAVPC;
public:
	CompileGTAV(const Script& data, bool Disable_Function_Names) : CompileBase(GTAVOpcodes, data, 0, 0, Disable_Function_Names) {
		if (data.getBuildPlatform() == P_PC){
			StringPageData = std::make_unique<StringPageCollectionLit>();
		}
		else{
			StringPageData = std::make_unique<StringPageCollectionBig>();
		}
	}

	virtual void Compile(const std::string& outDirectory) override
	{
		BuildTablesCheckEnc();
		switch (HLData->getBuildType())
		{
			case BT_GTAV:
			XSCWrite((outDirectory + HLData->getBuildFileName()).data(), !SCCL::Option_NoRSC7);
			break;
			default:
				TEST(false, "Incompatible build type for GTAV");
			break;
		}
	}

private:
	OpCodes GTAVOpcodes = { VO_Nop, VO_Add, VO_Sub, VO_Mult, VO_Div, VO_Mod, VO_Not, VO_Neg, VO_CmpEq, VO_CmpNe, VO_CmpGt, VO_CmpGe, VO_CmpLt, VO_CmpLe, VO_fAdd, VO_fSub, VO_fMult, VO_fDiv, VO_fMod, VO_fNeg, VO_fCmpEq, VO_fCmpNe, VO_fCmpGt, VO_fCmpGe, VO_fCmpLt, VO_fCmpLe, VO_vAdd, VO_vSub, VO_vMult, VO_vDiv, VO_vNeg, VO_And, VO_Or, VO_Xor, VO_ItoF, VO_FtoI, VO_FtoV, VO_PushB, VO_PushB2, VO_PushB3, VO_Push, VO_PushF, VO_Dup, VO_Drop, VO_CallNative, VO_Function, VO_Return, VO_pGet, VO_pSet, VO_pPeekSet, VO_ToStack, VO_FromStack, VO_GetArrayP1, VO_GetArray1, VO_SetArray1, VO_GetFrameP1, VO_GetFrame1, VO_SetFrame1, VO_GetStaticP1, VO_GetStatic1, VO_SetStatic1, VO_Add1, VO_Mult1, VO_GetImm1, VO_SetImm1, VO_PushS, VO_Add2, VO_Mult2, VO_GetImm2, VO_SetImm2, VO_GetArrayP2, VO_GetArray2, VO_SetArray2, VO_GetFrameP2, VO_GetFrame2, VO_SetFrame2, VO_GetStaticP2, VO_GetStatic2, VO_SetStatic2, VO_GetGlobalP2, VO_GetGlobal2, VO_SetGlobal2, VO_Jump, VO_JumpFalse, VO_JumpNE, VO_JumpEQ, VO_JumpLE, VO_JumpLT, VO_JumpGE, VO_JumpGT, VO_Call, VO_GetGlobalp3, VO_GetGlobal3, VO_SetGlobal3, VO_PushI24, VO_Switch, VO_PushString, VO_StrCopy, VO_ItoS, VO_StrAdd, VO_StrAddi, VO_Memcopy, VO_Catch, VO_Throw, VO_pCall, VO_Push_Neg1, VO_Push_0, VO_Push_1, VO_Push_2, VO_Push_3, VO_Push_4, VO_Push_5, VO_Push_6, VO_Push_7, VO_PushF_Neg1, VO_PushF_0, VO_PushF_1, VO_PushF_2, VO_PushF_3, VO_PushF_4, VO_PushF_5, VO_PushF_6, VO_PushF_7, VO_GetImmP, VO_GetImmP1, VO_GetImmP2, VO_GetHash };

protected:
    std::unique_ptr<StringPageCollection> StringPageData;
private:

	#pragma region Type_Defines
	enum class ResourceType : uint8_t
	{
		XenonTextDict = 7,
		WinTextDict = 8,
		ScriptContainer = 9,
		Particles_0 = 27,
		Bounds = 32,
		Particles_1 = 36,
		XenonModel = 109,
		WinModel = 110,
		WinModelFlag = 112
	};
	#pragma endregion

protected:
	#pragma region Parse_Functions
	int32_t GetSizeFromFlag(uint32_t flag, int32_t baseSize);
	int32_t GetSizeFromSystemFlag(uint32_t flag);
	int32_t GetSizeFromGraphicsFlag(uint32_t flag);
	uint32_t GetFlagFromSize(int32_t size);
	void fixFunctionCalls() override;
	void fixFunctionJumps() override;
	#pragma endregion

	#pragma region Opcode_Functions
	void CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount) override;
	void GetHash() override { DoesOpcodeHaveRoom(1); AddOpcode(GetHash); };
	void Call() override;
	void PushString() override;
	void GetImmPStack() override;
	void GetImmP() override;
	void GetImm() override;
	void SetImm() override;
	void GoToStack() override;
	void AddJumpTable() override;
	#pragma endregion

	#pragma region Write_Functions
	void WriteHeader() override;
	void WritePointers() override;
	void Write16384StringPages();
	void WriteFinalStringPage();
	virtual void XSCWrite(const char* path, bool CompressAndEncrypt = true);
	#pragma endregion

	#pragma region StringEnc
	bool isStringEncrypted = false;
	virtual void addDecryptionFunction(__int64 xorValue, size_t entryCallLoc);

	void BuildTablesCheckEnc();
public:
	void setEncryptStrings(bool bValue = true) { isStringEncrypted = true; }
	#pragma endregion
};

class CompileGTAVPC : public CompileGTAV
{
    //old, new
    std::unordered_map<uint64_t, uint64_t> NativeTranslationMap;
    const std::string NativeMapFileName = "GTAVNativesTranslationPC.csv";

public:
	
	CompileGTAVPC(const Script& data, bool Disable_Function_Names) : 
        CompileGTAV(data, Disable_Function_Names)
	{

        if (!Utils::IO::LoadCSVMap(Utils::IO::GetDir(Utils::IO::GetExecutablePath()) + NativeMapFileName, true, 16, NativeTranslationMap, true))
        {
            Utils::System::Throw("Could not load native map " + NativeMapFileName);
        }
	}

	void Compile(const std::string& outDirectory) override
	{
		BuildTablesCheckEnc();
		YSCWrite((outDirectory + HLData->getBuildFileName()).data(), !SCCL::Option_NoRSC7);
	}
protected:

	#pragma region Parsed_Data_Vars
	std::unordered_map<uint64_t, uint32_t> NativeHashMap;//hash, index  (native hash map has index start of 1) (hash map list for NativesList to limit find recursion)
	#pragma endregion

	#pragma region Data_Functions
	uint32_t AddNative(const uint64_t hash)
	{
		std::unordered_map<uint64_t, uint32_t>::iterator findRes = NativeHashMap.find(hash);
		const uint32_t size = NativeHashMap.size();
		if (findRes != NativeHashMap.end())
			return findRes->second;
		else
			NativeHashMap.insert({ hash, size });
		return size;
	}

	#pragma endregion

	#pragma region Opcode_Functions
	void CallNative(const uint64_t hash, const uint8_t paramCount, const uint8_t returnCount) override;

	void Shift_Left() override { CallNative(0xEDD95A39E5544DE8, 2, 1); }
	void Shift_Right() override { CallNative(0x97EF1E5BCE9DC075, 2, 1); }
	#pragma endregion

	#pragma region Write_Functions
	void WriteHeader() override;
	void WritePointers() override;
	void WriteNatives() override;
	void WriteStatics() override;
	void YSCWrite(const char* path, bool AddRsc7Header = false);
	#pragma endregion

    #pragma region StringEnc
	virtual void addDecryptionFunction(__int64 xorValue, size_t entryCallLoc)override;
    #pragma endregion

};

class CompileRDR2Console : public CompileGTAVPC
{

public:

    CompileRDR2Console(const Script& data, bool Disable_Function_Names) :
        CompileGTAVPC(data, Disable_Function_Names)
    {
        memset(BaseOpcodes, R2O_Nop, BASE_OPCODE_SIZE);

        BaseOpcodes->Nop = R2O_Nop;
        BaseOpcodes->Add = R2O_Add;
        BaseOpcodes->Sub = R2O_Sub;
        BaseOpcodes->Mult = R2O_Mult;
        BaseOpcodes->Div = R2O_Div;
        BaseOpcodes->Mod = R2O_Mod;
        BaseOpcodes->Not = R2O_Not;
        BaseOpcodes->Neg = R2O_Neg;
        BaseOpcodes->CmpEq = R2O_CmpEQ;
        BaseOpcodes->CmpNe = R2O_CmpNE;
        BaseOpcodes->CmpGt = R2O_CmpGT;
        BaseOpcodes->CmpGe = R2O_CmpGE;
        BaseOpcodes->CmpLt = R2O_CmpLT;
        BaseOpcodes->CmpLe = R2O_CmpLE;
        BaseOpcodes->fAdd = R2O_fAdd;
        BaseOpcodes->fSub = R2O_fSub;
        BaseOpcodes->fMult = R2O_fMult;
        BaseOpcodes->fDiv = R2O_fDiv;
        BaseOpcodes->fMod = R2O_fMod;
        BaseOpcodes->fNeg = R2O_fNeg;
        BaseOpcodes->fCmpEq = R2O_fCmpEQ;
        BaseOpcodes->fCmpNe = R2O_fCmpNE;
        BaseOpcodes->fCmpGt = R2O_fCmpGT;
        BaseOpcodes->fCmpGe = R2O_fCmpGE;
        BaseOpcodes->fCmpLt = R2O_fCmpLT;
        BaseOpcodes->fCmpLe = R2O_fCmpLE;
        BaseOpcodes->vAdd = R2O_vAdd;
        BaseOpcodes->vSub = R2O_vSub;
        BaseOpcodes->vMult = R2O_vMult;
        BaseOpcodes->vDiv = R2O_vDiv;
        BaseOpcodes->vNeg = R2O_vNeg;
        BaseOpcodes->And = R2O_And;
        BaseOpcodes->Or = R2O_Or;
        BaseOpcodes->Xor = R2O_Xor;
        BaseOpcodes->ItoF = R2O_ItoF;
        BaseOpcodes->FtoI = R2O_FtoI;
        BaseOpcodes->FtoV = R2O_FtoV;
        BaseOpcodes->PushB = R2O_PushB;
        BaseOpcodes->PushB2 = R2O_PushB2;
        BaseOpcodes->PushB3 = R2O_PushB3;
        BaseOpcodes->Push = R2O_Push;
        BaseOpcodes->PushF = R2O_PushF;
        BaseOpcodes->Dup = R2O_Dup;
        BaseOpcodes->Drop = R2O_Drop;
        BaseOpcodes->CallNative = R2O_CallNative;
        BaseOpcodes->Function = R2O_Function;
        BaseOpcodes->Return = R2O_Return;
        BaseOpcodes->pGet = R2O_pGet;
        BaseOpcodes->pSet = R2O_pSet;
        BaseOpcodes->pPeekSet = R2O_pPeekSet;
        BaseOpcodes->ToStack = R2O_ToStack;
        BaseOpcodes->FromStack = R2O_FromStack;
        BaseOpcodes->GetArrayP1 = R2O_GetArrayP1;
        BaseOpcodes->GetArray1 = R2O_GetArray1;
        BaseOpcodes->SetArray1 = R2O_SetArray1;
        BaseOpcodes->GetFrameP1 = R2O_GetLocalP1;
        BaseOpcodes->GetFrame1 = R2O_GetLocal1;
        BaseOpcodes->SetFrame1 = R2O_SetLocal1;
        BaseOpcodes->GetStaticP1 = R2O_GetStaticP1;
        BaseOpcodes->GetStatic1 = R2O_GetStatic1;
        BaseOpcodes->SetStatic1 = R2O_SetStatic1;
        BaseOpcodes->Add1 = R2O_AddImm1;
        BaseOpcodes->Mult1 = R2O_MultImm1;
        BaseOpcodes->GetImm1 = R2O_GetImm1;
        BaseOpcodes->SetImm1 = R2O_SetImm1;
        BaseOpcodes->PushS = R2O_PushS;
        BaseOpcodes->Add2 = R2O_AddImm2;
        BaseOpcodes->Mult2 = R2O_MultImm2;
        BaseOpcodes->GetImm2 = R2O_GetImm2;
        BaseOpcodes->SetImm2 = R2O_SetImm2;
        BaseOpcodes->GetArrayP2 = R2O_GetArrayP2;
        BaseOpcodes->GetArray2 = R2O_GetArray2;
        BaseOpcodes->SetArray2 = R2O_SetArray2;
        BaseOpcodes->GetFrameP2 = R2O_GetLocalP2;
        BaseOpcodes->GetFrame2 = R2O_GetLocal2;
        BaseOpcodes->SetFrame2 = R2O_SetLocal2;
        BaseOpcodes->GetStaticP2 = R2O_GetStaticP2;
        BaseOpcodes->GetStatic2 = R2O_GetStatic2;
        BaseOpcodes->SetStatic2 = R2O_SetStatic2;
        BaseOpcodes->GetGlobalP2 = R2O_GetGlobalP2;
        BaseOpcodes->GetGlobal2 = R2O_GetGlobal2;
        BaseOpcodes->SetGlobal2 = R2O_SetGlobal2;
        BaseOpcodes->Jump = R2O_Jump;
        BaseOpcodes->JumpFalse = R2O_JumpFalse;
        BaseOpcodes->JumpNE = R2O_JumpNE;
        BaseOpcodes->JumpEQ = R2O_JumpEQ;
        BaseOpcodes->JumpLE = R2O_JumpLE;
        BaseOpcodes->JumpLT = R2O_JumpLT;
        BaseOpcodes->JumpGE = R2O_JumpGE;
        BaseOpcodes->JumpGT = R2O_JumpGT;
        BaseOpcodes->Call = R2O_Call;
        BaseOpcodes->GetGlobalP3 = R2O_GetGlobalP3;
        BaseOpcodes->GetGlobal3 = R2O_GetGlobal3;
        BaseOpcodes->SetGlobal3 = R2O_SetGlobal3;
        BaseOpcodes->PushI24 = R2O_PushI24;
        BaseOpcodes->Switch = R2O_Switch;
        BaseOpcodes->PushString = R2O_PushStringS;
        BaseOpcodes->StrCopy = R2O_StrCopy;
        BaseOpcodes->ItoS = R2O_ItoS;
        BaseOpcodes->StrAdd = R2O_StrAdd;
        BaseOpcodes->StrAddi = R2O_StrAddi;
        BaseOpcodes->MemCopy = R2O_MemCopy;
        BaseOpcodes->Catch = R2O_Catch;
        BaseOpcodes->Throw = R2O_Throw;
        BaseOpcodes->pCall = R2O_pCall;
        BaseOpcodes->Push_Neg1 = R2O_Push_Neg1;
        BaseOpcodes->Push_0 = R2O_Push_0;
        BaseOpcodes->Push_1 = R2O_Push_1;
        BaseOpcodes->Push_2 = R2O_Push_2;
        BaseOpcodes->Push_3 = R2O_Push_3;
        BaseOpcodes->Push_4 = R2O_Push_4;
        BaseOpcodes->Push_5 = R2O_Push_5;
        BaseOpcodes->Push_6 = R2O_Push_6;
        BaseOpcodes->Push_7 = R2O_Push_7;
        BaseOpcodes->PushF_Neg1 = R2O_PushF_Neg1;
        BaseOpcodes->PushF_0 = R2O_PushF_0;
        BaseOpcodes->PushF_1 = R2O_PushF_1;
        BaseOpcodes->PushF_2 = R2O_PushF_2;
        BaseOpcodes->PushF_3 = R2O_PushF_3;
        BaseOpcodes->PushF_4 = R2O_PushF_4;
        BaseOpcodes->PushF_5 = R2O_PushF_5;
        BaseOpcodes->PushF_6 = R2O_PushF_6;
        BaseOpcodes->PushF_7 = R2O_PushF_7;

        //Extra GTAV Opcodes
        BaseOpcodes->GetImmP = R2O_GetImmPs;
        BaseOpcodes->GetImmP1 = R2O_GetImmP1;
        BaseOpcodes->GetImmP2 = R2O_GetImmP2;
        BaseOpcodes->GetHash = R2O_GetHash;

        //RDR2 Extra Opcodes
        BaseOpcodes->GetLocalS = R2O_GetLocalS;
        BaseOpcodes->SetLocalS = R2O_SetLocalS;
        BaseOpcodes->SetLocalSR = R2O_SetLocalSR;
        BaseOpcodes->GetStaticS = R2O_GetStaticS;
        BaseOpcodes->SetStaticS = R2O_SetStaticS;
        BaseOpcodes->SetStaticSR = R2O_SetStaticSR;
        BaseOpcodes->pGetS = R2O_pGetS;
        BaseOpcodes->pSetS = R2O_pSetS;
        BaseOpcodes->pSetSR = R2O_pSetSR;
        BaseOpcodes->GetGlobalS = R2O_GetGlobalS;
        BaseOpcodes->SetGlobalS = R2O_SetGlobalS;
        BaseOpcodes->SetGlobalSR = R2O_SetGlobalSR;

        BaseOpcodes->GetStaticP3 = R2O_GetStaticP3;
        BaseOpcodes->GetStatic3 = R2O_GetStatic3;
        BaseOpcodes->SetStatic3 = R2O_SetStatic3;

    }

    void Compile(const std::string& outDirectory) override
    {
        BuildTablesCheckEnc();
        YSCWrite((outDirectory + HLData->getBuildFileName()).data(), !SCCL::Option_NoRSC7);
    }
protected:

#pragma region Opcode_Functions
    void Switch() override;
#pragma endregion

#pragma region Write_Functions
    void WriteHeader() override;
    void WritePointers() override;
    void WriteNatives() override;
    void YSCWrite(const char* path, bool AddRsc8Header = false);
#pragma endregion


};

class CompileRDR2PC : public CompileRDR2Console
{
    const std::string OpcodeMapFileName = "RDR2OpcodeTranslationPC.csv";

public:

    CompileRDR2PC(const Script& data, bool Disable_Function_Names);

    void Compile(const std::string& outDirectory) override
    {
        BuildTablesCheckEnc();
        YSCWrite((outDirectory + HLData->getBuildFileName()).data(), !SCCL::Option_NoRSC7);
    }
private:

#pragma region Write_Functions
    void WriteNatives() override;
#pragma endregion


};

