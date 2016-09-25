#ifndef XSC_H_INCLUDED
#define XSC_H_INCLUDED
#include <vector>
#include "Constants.h"
#include "PikIO.h"
#include "Utils.h"
using namespace std;

class XSCHeader{
public:
    uint32_t PgBase;//0
    uint32_t Unk1;//UNK PTR //4
    uint32_t CodeBlocksListOffset;//8
    uint32_t Unk2;//12
    uint32_t CodeLength;//16

    uint32_t ParameterCount;//20
    uint32_t StaticsCount;//24
    uint32_t GlobalsSize;//28
    uint32_t NativesCount;//32
    uint32_t StaticsOffset;//36
    uint32_t GlobalsPtr;//40
    uint32_t NativesOffset;//44
    uint32_t Unk3;//48
    uint32_t Unk4;//52
    uint32_t NameHash;//56

    uint32_t Unk5;//60 (typically 1)
    uint32_t ScriptNameOffset;//64
    uint32_t StringsOffset;//68
    uint32_t StringsSize;//72

    uint32_t Unk6;//76

    char* ScriptName;
    vector<int> CodePagePointers;
    vector<int> StringPagePointers;
    vector<unsigned int> Natives;
    vector<int> Statics;
    vector<vector<int8_t>> CodePages;
    vector<vector<char>> StringPages;



    void XSCHeaderClear();
    void SetupNewStatics(int staticsCount);
    void AddStatic(int x);
    void AddStatic(float x);
    void SetStatics(vector<int> collection);
    float GetStaticAsFloat(int index);
    int GetStaticAsInt(int index);
};

class XSC
{
public:

    XSCHeader Header;

    void OpenScript(void* xIn, size_t* length );
    void Write(FILE* file, char* path, Constants::Platform platform, PikIO::Endianess endian, bool rsc7);
    void CompileXSC(string& data, int pgBase, char* scriptName, bool ignoreNops, uint32_t paramcount);
    void GetCode(const char* OutPath, uint32_t flags);
};

#endif // XSC_H_INCLUDED
