#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "Constants.h"
#include <stdint.h>
#include <vector>

using namespace std;


namespace Utils{
    struct DLX{
        void * data;
        size_t length;
    };

    int GetSizeFromFlag(int flag, int baseSize);
    int GetFlagFromSize(int size, int baseSize);
    int CountOffNextBlockSize(int size, int blockSize);
    int NextBlockSize(int size, int blockSize);
    vector<char> GiveDataBlock(vector<char> data, int blockSize);
    vector<char> GiveDataBlock(char* data, int blockSize);
    vector<char> GiveDataBlock(int size, int blockSize);
    int GetPointerInt(int x);
    unsigned int Joaat(char* key);
    int GetPageLenAtPage(int pgCount, int totalLen, int pg, int maxPageSize);
    int GetOpCodeLength(Constants::OpCode opCode, vector<char> code, int PC);

    inline int16_t SwapEndian(int16_t x){return _byteswap_ushort(x);}
    inline int32_t SwapEndian(int32_t x){return _byteswap_ulong(x);}
    inline int64_t SwapEndian(int64_t x){return _byteswap_uint64(x);}
    inline uint16_t SwapEndian(uint16_t x){return _byteswap_ushort(x);}
    inline uint32_t SwapEndian(uint32_t x){return _byteswap_ulong(x);}
    inline uint64_t SwapEndian(uint64_t x){return _byteswap_uint64(x);}
    float SwapEndian(float* x);
    vector<char> Swap(vector<char> data);
    char* IntToHex(uint32_t val);
    DLX LoadData(char* loc);
    void Pause();
    void Throw(string str);
    int GetOpCodeLengthDefault(Constants::OpCode opCode);

    inline int FloatToInt(float x){return *(int*)&x;}
    inline float IntToFloat(int x){return *(float*)&x;}
    inline int IntFromUInt(unsigned int x){return *(int*)&x;}
    inline unsigned int UIntFromInt(int x){return *(unsigned int*)&x;}
}

#endif // UTILS_H_INCLUDED
