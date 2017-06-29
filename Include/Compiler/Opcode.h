#pragma once
#include <llvm/ADT/StringRef.h>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include "Utils/Utils.h"

enum OpcodeKind{
	OK_Null,
	OK_Nop,
	OK_Add,
	OK_Sub,
	OK_Mult,
	OK_Div,
	OK_Mod,
	OK_Not,
	OK_Neg,
	OK_CmpEq,
	OK_CmpNe,
	OK_CmpGt,
	OK_CmpGe,
	OK_CmpLt,
	OK_CmpLe,
	OK_FAdd,
	OK_FSub,
	OK_FMult,
	OK_FDiv,
	OK_FMod,
	OK_FNeg,
	OK_FCmpEq,
	OK_FCmpNe,
	OK_FCmpGt,
	OK_FCmpGe,
	OK_FCmpLt,
	OK_FCmpLe,
	OK_VAdd,
	OK_VSub,
	OK_VMult,
	OK_VDiv,
	OK_VNeg,
	OK_And,
	OK_Or,
	OK_Xor,
	OK_FtoI,
	OK_ItoF,
	OK_FtoV,
	OK_PushInt,
	OK_PushBytes,
	OK_PushFloat,
	OK_Dup,
	OK_Drop,
	OK_Native,
	OK_Return,
	OK_PGet,
	OK_PSet,
	OK_PeekSet,
	OK_ToStack,
	OK_FromStack,
	OK_GetArrayP,
	OK_GetArray,
	OK_SetArray,
	OK_GetFrameP,
	OK_GetFrame,
	OK_SetFrame,
	OK_GetStaticP,
	OK_GetStatic,
	OK_SetStatic,
	OK_GetStaticPRaw,
	OK_GetStaticRaw,
	OK_SetStaticRaw,
	OK_GetGlobalP,
	OK_GetGlobal,
	OK_SetGlobal,
	OK_AddImm,
	OK_MultImm,
	OK_FAddImm,//simplify optimising
	OK_FMultImm,//simplify optimising
	OK_GetImmPStack,
	OK_GetImmP,
	OK_GetImm,
	OK_SetImm,
	OK_Call,
	OK_Jump,
	OK_JumpFalse,
	OK_JumpEQ,
	OK_JumpNE,
	OK_JumpGT,
	OK_JumpGE,
	OK_JumpLT,
	OK_JumpLE,
	OK_Switch,
	OK_PushString,
	OK_StrCopy,
	OK_ItoS,
	OK_StrAdd,
	OK_StrAddI,
	OK_MemCpy,
	OK_PCall,
	OK_Label,
	OK_LabelLoc,
	OK_FuncLoc,
	OK_ShiftLeft,
	OK_ShiftRight,
	OK_GetHash,
	OK_GoToStack,
	OK_JumpTable,
	OK_PushNullPtr
};

#pragma region Forward Declarations
class FunctionData;
class StaticData;
#pragma endregion

#pragma region OpcodeCustomStorage
struct StringStorage
{
private:
	char* pointer;
	size_t length;
public:
	std::string toString()const
	{
		return std::string(pointer, length);
	}
	/*llvm::StringRef toStringRef()const
	{
	return llvm::StringRef(pointer, length);
	}*/
	StringStorage(const std::string& str)
	{
		length = str.length();
		pointer = new char[length + 1];
		memcpy(pointer, str.c_str(), length + 1);
	}
	StringStorage(llvm::StringRef stringRef)
	{
		length = stringRef.size();
		pointer = new char[length + 1];
		memcpy(pointer, stringRef.data(), length + 1);
	}
	const char *data() const
	{
		return pointer;
	}
	size_t size()const
	{
		return length;
	}
	~StringStorage()
	{
		delete[] pointer;
	}
	friend std::ostream& operator << (std::ostream& stream, const StringStorage& string) {
		stream.write(string.pointer, string.size());
		return stream;
	}
};

struct SwitchCaseStorage
{
private:
	int _caseVal;
	std::string _jumpLoc;
	SwitchCaseStorage* _next;
public:
	SwitchCaseStorage(int caseVal, const std::string& jumpLoc) : _caseVal(caseVal), _jumpLoc(jumpLoc), _next(NULL) {}
	~SwitchCaseStorage()
	{
		if (_next)
			delete _next;
	}

	std::string getCaseLocation()const { return _jumpLoc; }
	void setCaseLocation(const std::string& newCaseLoc){ _jumpLoc = newCaseLoc; }
	int getCaseValue()const { return _caseVal; }
	bool hasNextCase()const { return _next; }
	SwitchCaseStorage *getNextCase(){ return _next; }
	const SwitchCaseStorage *getNextCase()const { return _next; }
	void setNextCase(SwitchCaseStorage* next)
	{
		assert(!_next && "Already a next case defined");
		_next = next;
	}
	void setNextCase(int caseVal, const std::string& jumpLoc)
	{
		assert(!_next && "Already a next case defined");
		_next = new SwitchCaseStorage(caseVal, jumpLoc);
	}
};

struct SwitchStorage
{
private:
	uint32_t _count;
	SwitchCaseStorage *_first, *_last;//keep track of last for faster access
	StringStorage* _defaultJumpLoc;//to be set at the end of the switch
public:
	SwitchStorage() : _count(0), _first(NULL), _last(NULL), _defaultJumpLoc(NULL){}
	~SwitchStorage()
	{
		if (_first)
		{
			delete _first;
		}
		if (_defaultJumpLoc)
		{
			delete _defaultJumpLoc;
		}
	}

	void addCase(int caseVal, const std::string& caseLoc)
	{
		_count++;
		assert(_count < 256 && "Error switch has too many cases");
		if (!_first)
		{
			_first = new SwitchCaseStorage(caseVal, caseLoc);
			_last = _first;
		}
		else
		{
			SwitchCaseStorage* next = new SwitchCaseStorage(caseVal, caseLoc);
			_last->setNextCase(next);
			_last = next;
		}
	}
	const SwitchCaseStorage* getFirstCase() const { return _first; }
	SwitchCaseStorage* getFirstCase(){ return _first; }
	uint32_t getCount() const{ return _count; }
	void setDefaultJumpLoc(const std::string& defCase)
	{
		assert(!_defaultJumpLoc && "Default jump case already specified");
		_defaultJumpLoc = new StringStorage(defCase);
	}
	void overWriteDefaultJumpLoc(const std::string& newDefCase){
		assert(_defaultJumpLoc && "Default jump case not already specified");
		delete _defaultJumpLoc;
		_defaultJumpLoc = new StringStorage(newDefCase);
	}
	void setDefaultJumpLoc(llvm::StringRef defCase)
	{
		assert(!_defaultJumpLoc && "Default jump case already specified");
		_defaultJumpLoc = new StringStorage(defCase);
	}
	bool hasDefaultJumpLoc()const{ return _defaultJumpLoc; }//only would occur when you have a switch statement with > 255 cases
	const StringStorage* getDefaultJumpLoc()const{ return _defaultJumpLoc; }
	void clearDefaultJumpLoc(){
		if (_defaultJumpLoc){
			delete _defaultJumpLoc;
			_defaultJumpLoc = NULL;
		}
	}

};

struct NativeStorage
{
private:
	uint64_t _hash;
	StringStorage *_name;
	uint8_t _pCount, _rCount;
public:
	NativeStorage(const std::string& name, uint64_t hash, uint8_t pCount, uint8_t rCount) :
		_hash(hash),
		_name(new StringStorage(name)),
		_pCount(pCount),
		_rCount(rCount)
	{
	}
	NativeStorage(const std::string& name, uint8_t pCount, uint8_t rCount) :
		_hash((!strnicmp(name.c_str(), "unk_0x", 6) ? strtoull(name.c_str() + 6, NULL, 16) : Utils::Hashing::Joaat(name.c_str()))),
		_name(new StringStorage(name)),
		_pCount(pCount),
		_rCount(rCount)
	{
	}
	NativeStorage(uint64_t hash, uint8_t pCount, uint8_t rCount) :
		_hash(hash),
		_name(NULL),
		_pCount(pCount),
		_rCount(rCount)
	{
	}
	~NativeStorage()
	{
		if (_name)
			delete _name;
	}
	bool hasName()const { return _name; }
	std::string getName()const { if (hasName())return _name->toString(); return std::string(); }
	uint64_t getHash()const { return _hash; }
	uint8_t getParamCount()const { return _pCount; }
	uint8_t getReturnCount()const { return _rCount; }
};

struct JumpTableStorage
{
private:
	std::vector<std::unique_ptr<StringStorage>> jumpLocs;
	uint32_t _XORvalue = 0;
public:
	JumpTableStorage(){}
	uint32_t getByteSize()const{ return jumpLocs.size() << 2; }
	uint32_t getItemCount()const{ return jumpLocs.size(); }
	void addJumpLoc(const std::string& jumpLoc){ jumpLocs.push_back(std::make_unique<StringStorage>(jumpLoc)); }
	void addJumpLoc(llvm::StringRef jumpLoc){ jumpLocs.push_back(std::make_unique<StringStorage>(jumpLoc)); }
	const StringStorage* getJumpLoc(unsigned index) const
	{
		assert(index >= 0 && index < jumpLocs.size() && "Index out of range for jump table");
		return jumpLocs[index].get();
	}
	std::string getJumpLocAsString(unsigned index) const
	{
		assert(index >= 0 && index < jumpLocs.size() && "Index out of range for jump table");
		return jumpLocs[index]->toString();
	}
	void setJumpLoc(unsigned index, const std::string& newJumpLoc){
		jumpLocs[index] = std::make_unique<StringStorage>(newJumpLoc);
	}
	void setXORValue(uint32_t val){ _XORvalue = val; }
	uint32_t getXORValue()const{ return _XORvalue; }
};

struct OpStaticStorage
{
private:
	const StaticData* _staticData;
	uint16_t _immIndex;
public:
	OpStaticStorage(const StaticData* staticData, const uint16_t immIndex = 0):_staticData(staticData), _immIndex(immIndex)
	{
	}
	const StaticData* getStatic()const{ return _staticData; }
	uint16_t getImmIndex()const{ return _immIndex; }
	void setImmIndex(uint16_t newValue){ _immIndex = newValue; }
	bool isEqual(const OpStaticStorage& other)const{
		return _staticData == other._staticData && _immIndex == other._immIndex;
	}
};
#pragma endregion

class Opcode
{
	friend class FunctionData;
	friend class StaticData;
	OpcodeKind opcodeKind;
#ifdef _DEBUG
	StringStorage *_comment = NULL;
#endif
	Opcode(OpcodeKind kind) : opcodeKind(kind){ storage.ptr = nullptr; }
	Opcode(OpcodeKind kind, void* pointer) :opcodeKind(kind){ storage.ptr = pointer; }
	Opcode(OpcodeKind kind, int storageVal) : opcodeKind(kind){ storage.i32 = storageVal; }
	Opcode(OpcodeKind kind, float storageVal) : opcodeKind(kind){ storage.f32 = storageVal; }
	Opcode(OpcodeKind kind, uint16_t storageVal) : opcodeKind(kind){ storage.u16[0] = storageVal; storage.u16[1] = 0; }
	Opcode(OpcodeKind kind, int16_t storageVal) : opcodeKind(kind){ storage.i16[0] = storageVal; storage.i16[1] = 0;}
	Opcode(OpcodeKind kind, uint8_t storageVal) : opcodeKind(kind){ storage.u8[0] = storageVal; storage.u8[1] = storage.u8[2] = storage.u8[3] = 0; }
	Opcode(OpcodeKind kind, uint8_t storageVal1, uint8_t storageVal2) : opcodeKind(kind){
		storage.u8[0] = storageVal1; storage.u8[1] = storageVal2; storage.u8[2] = storage.u8[3] = 0;
	}
	void setString(const std::string& str)
	{
		if (storage.string)
			delete storage.string;
		storage.string = new StringStorage(str);
	}
	void setInt(int value)
	{
		storage.i32 = value;
	}
	void setFloat(float value)
	{
		storage.f32 = value;
	}
	void setShort(int16_t value, uint32_t offset)
	{
		assert(offset < (sizeof(void*) / 2) && "short offset must be between 0 and 2");
		storage.i16[offset] = value;
	}
	void setUShort(uint16_t value, uint32_t offset)
	{
		assert(offset < (sizeof(void*) / 2) && "short offset must be between 0 and 2");
		storage.u16[offset] = value;
	}
	void setByte(uint8_t value, uint32_t offset)
	{
		assert(offset < (sizeof(void*)) && "byte offset must be between 0 and 4");
		storage.u8[offset] = value;
	}
	void setKind(OpcodeKind newKind){ opcodeKind = newKind; }
	union
	{
		void* ptr;
		char u8[sizeof(void*)];
		uint16_t u16[sizeof(void*) / 2];
		int16_t i16[sizeof(void*) / 2];
		int32_t i32;
		uint32_t u32;
		float f32;
		SwitchStorage *switchCase;
		NativeStorage *native;
		StringStorage *string;
		JumpTableStorage *jTable;
		OpStaticStorage* staticData;
		FunctionData* functionData;
	}storage;
public:
	static Opcode* makeIntOpcode(OpcodeKind ok, int value)
	{
		return new Opcode(ok, value);
	}
	static Opcode* makeFloatOpcode(OpcodeKind ok, float value)
	{
		return new Opcode(ok, value);
	}
	static Opcode* makeUShortOpcode(OpcodeKind ok, uint16_t value)
	{
		return new Opcode(ok, value);
	}
	static Opcode* makeShortOpcode(OpcodeKind ok, int16_t value)
	{
		return new Opcode(ok, value);
	}
	static Opcode* makeStaticOpcode(OpcodeKind ok, OpStaticStorage* staticData)
	{
		return new Opcode(ok, staticData);
	}
	static Opcode* makeStringOpcode(OpcodeKind ok, const std::string& str)
	{
		return new Opcode(ok, new StringStorage(str));
	}
	static Opcode* makeByteOpcode(OpcodeKind ok, uint8_t value)
	{
		return new Opcode(ok, value);
	}
	static Opcode* make2ByteOpcode(OpcodeKind ok, uint8_t value1, uint8_t value2)
	{
		return new Opcode(ok, value1, value2);
	}
	static Opcode* makeFunctionOpcode(OpcodeKind ok, FunctionData* function)
	{
		return new Opcode(ok, function);
	}
	static Opcode* makeJumpTableOpcode(JumpTableStorage* jTable)
	{
		return new Opcode(OK_JumpTable, jTable);
	}
	static Opcode* makeSwitchOpcode(SwitchStorage* switchStorage)
	{
		return new Opcode(OK_Switch, switchStorage);
	}
	static Opcode* makeNativeOpcode(NativeStorage* nativeStorage)
	{
		return new Opcode(OK_Native, nativeStorage);
	}
	~Opcode();
	OpcodeKind getKind() const{ return opcodeKind; }
	void setComment(const std::string& comment)
	{
#ifdef _DEBUG
		if (_comment)
		{
			auto nComment = new StringStorage(_comment->toString() + " - " + comment);
			delete _comment;
			_comment = nComment;
		}
		else
		{
			_comment = new StringStorage(comment);
		}
#endif
	}
	std::string getComment() const
	{
#ifdef _DEBUG
		if (_comment)
		{
			return _comment->toString();
		}
#endif
		return "";
	}
	bool hasComment() const
	{
#ifdef _DEBUG
		return _comment;
#else
		return false;
#endif
	}
	std::string getString() const
	{
		assert((getKind() == OK_PushString ||
			getKind() == OK_Jump ||
			getKind() == OK_JumpFalse ||
			getKind() == OK_JumpEQ ||
			getKind() == OK_JumpNE ||
			getKind() == OK_JumpGT ||
			getKind() == OK_JumpGE ||
			getKind() == OK_JumpLT ||
			getKind() == OK_JumpLE ||
			getKind() == OK_Label ||
			getKind() == OK_LabelLoc ||
			getKind() == OK_FuncLoc) && "getString called on a non string opcode");
		return storage.string->toString();
	}
	int getInt() const
	{
		return storage.i32;
	}
	float getFloat() const
	{
		return storage.f32;
	}
	int16_t getShort(uint32_t offset) const
	{
		assert(offset < (sizeof(void*) / 2) && "short offset must be between 0 and 2");
		return storage.i16[offset];
	}
	uint16_t getUShort(uint32_t offset) const
	{
		assert(offset < (sizeof(void*) / 2) && "ushort offset must be between 0 and 2");
		return storage.u16[offset];
	}
	uint8_t getByte(uint32_t offset) const
	{
		assert(offset < (sizeof(void*)) && "byte offset must be between 0 and 4");
		return storage.u8[offset];
	}
	int getSizeEstimate() const;
	std::string toString() const;
	void makeNull();

	const SwitchStorage *getSwitch() const
	{
		assert(getKind() == OK_Switch && "getSwitch not called on Switch Opcode");
		return storage.switchCase;
	}
	const NativeStorage *getNative() const
	{
		assert(getKind() == OK_Native && "getNative not called on Native Opcode");
		return storage.native;
	}
	const JumpTableStorage *getJumpTable() const
	{
		assert(getKind() == OK_JumpTable && "getNative not called on JumpTable Opcode");
		return storage.jTable;
	}
	const OpStaticStorage* getStaticData()const
	{
		assert((getKind() == OK_GetStaticP || getKind() == OK_GetStatic || getKind() == OK_SetStatic) && "getStaticData not called on static opcode");
		return storage.staticData;
	}
	const FunctionData* getFunctionData()const
	{
		assert((getKind() == OK_FuncLoc || getKind() == OK_Call) && "getFunctionData not called on function location opcode");
		return storage.functionData;
	}

	friend std::ostream& operator << (std::ostream& stream, const Opcode& opcode) {
		stream << opcode.toString();
		return stream;
	}
};
