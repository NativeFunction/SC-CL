#ifndef RSC_H_INCLUDED
#define RSC_H_INCLUDED
#include <vector>
#include "Constants.h"
#include "PikIO.h"
#include "Utils.h"
using namespace std;

class XSCHeader
{
public:
    uint32_t Flag;

    uint32_t PgBase = 0;//0
    uint32_t Unk1;//UNK PTR to last block? //4
    uint32_t CodeBlocksListOffset;//8
    uint32_t CodeLength;//16
    uint32_t ParameterCount;//20
    uint32_t StaticsCount;//24
    uint32_t StaticsOffset;//28
    uint32_t GlobalsSignature;//32
    uint32_t NativesCount;//36
    uint32_t NativesOffset;//40

    vector<uint32_t> CodePagePointers;
    vector<uint32_t> Natives;
    vector<int32_t> Statics;
    vector<vector<uint8_t>> CodePages;
};
class SCOHeader
{
public:

    uint32_t SCR;//0
    uint32_t GlobalsSignature;//4
    uint32_t CompressedSize;//8
    int32_t unk12;//12 is_crypt?
    uint32_t CodeLength;//16
    uint32_t StaticsCount;//20
    uint32_t GlobalsCount;
    uint32_t ParameterCount;
    uint32_t NativesCount;//32
    uint32_t unk36;//36
    uint32_t unk40;//40
    uint32_t unk44;//44

    vector<uint32_t> Natives;
    vector<int32_t> Statics;
    vector<vector<uint8_t>> CodePages;
};

class RSC
{
    string _opNames[156]{"Nop", "Add", "Sub", "Mult", "Div", "Mod", "Not", "Neg", "CmpEq", "CmpNe", "CmpGt", "CmpGe", "CmpLt",
    "CmpLe", "fAdd", "fSub", "fMult", "fDiv", "fMod", "fNeg", "fCmpEq", "fCmpNe", "fCmpGt", "fCmpGe", "fCmpLt", "fCmpLe", "vAdd",
    "vSub", "vMult", "vDiv", "vNeg", "And", "Or", "Xor", "ItoF", "FtoI", "FtoV", "PushB", "PushB2", "PushB3", "Push", "PushF",
    "Dup", "Drop", "CallNative", "Function", "Return", "pGet", "pSet", "pPeekSet", "ToStack", "FromStack", "GetArrayP1", "GetArray1",
    "SetArray1", "GetFrameP1", "GetFrame1", "SetFrame1", "GetStaticP1", "GetStatic1", "SetStatic1", "Add1", "GetImm1", "SetImm1",
    "Mult1", "PushS", "Add2", "GetImm2", "SetImm2", "Mult2", "GetArrayP2", "GetArray2", "SetArray2", "GetFrameP2", "GetFrame2",
    "SetFrame2", "GetStaticP2", "GetStatic2", "SetStatic2", "GetGlobalP2", "GetGlobal2", "SetGlobal2", "call", "call", "call",
    "call", "call", "call", "call", "call", "call", "call", "call", "call", "call", "call", "call", "call", "Jump", "JumpFalse",
    "JumpNE", "JumpEQ", "JumpLE", "JumpLT", "JumpGE", "JumpGT", "GetGlobalP3", "GetGlobal3", "SetGlobal3", "PushI24", "Switch",
    "PushString", "PushArrayP", "PushString", "StrCopy", "IToS", "StrAdd", "StrAddi", "MemCopy", "Catch", "Throw", "pCall",
    "return", "return", "return", "return", "return", "return", "return", "return", "return", "return", "return", "return",
    "return", "return", "return", "return", "Push_-1", "Push_0", "Push_1", "Push_2", "Push_3", "Push_4", "Push_5", "Push_6",
    "Push_7", "PushF_-1", "PushF_0", "PushF_1", "PushF_2", "PushF_3", "PushF_4", "PushF_5", "PushF_6", "PushF_7"};


public:

    uint8_t RSC_Type = 0;

    SCOHeader Header_SCO;
    XSCHeader Header_XSC;

    bool OpenScript(void* xIn, size_t* length );
    void XSCWrite(char* path, Constants::Platform platform, PikIO::Endianess endian, bool rsc85);
    void SCOWrite(char* path, Constants::Platform platform, PikIO::Endianess endian, bool rsc2);
    void Compile(string& data, int pgBase, char* scriptName, bool ignoreNops, bool issco = false);
    void GetCode(string OutPath, uint32_t flags, Constants::DecompileType type = Constants::DecompileType::Type_None);
    void GetHighLevelCode(string OutPath, uint32_t flags);
};



#endif // RSC_H_INCLUDED
