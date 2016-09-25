#ifndef PIKIO_H_INCLUDED
#define PIKIO_H_INCLUDED

#include <stdint.h>
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)
using namespace std;

class PikIO
{
public:
    enum StringTerminationType : bool
    {
        ByteLengthPrefix,
        NullTerminated
    };
    enum Endianess : char
    {
        Little,
        Big,
        SystemDefault
    };

    Endianess Endian;
    void* BaseStream;
    vector<int8_t> BaseWrite;
    int64_t Position = 0;
    size_t Length;
    int32_t NullTerminatorMaxLength;

    //helpers
    inline uint8_t* BaseLoc(){return ((uint8_t*)BaseStream + Position);}

    //constructor
    void Init();
    void Init(void* xIn, size_t Len);
    void Init(void* xIn, size_t Len, Endianess endian);
    void Init(void* xIn, size_t Len, Endianess endian, int32_t nullTerminatorMaxLength);
    void InitWriter(Endianess endian);

    //reader
    int8_t ReadByte();
    vector<int8_t> ReadBytes(int32_t len);
    vector<char> ReadBytesAsStr(int32_t len);
    int16_t ReadInt16();
    int32_t ReadInt32();
    int64_t ReadInt64();
    uint16_t ReadUInt16();
    uint32_t ReadUInt32();
    uint64_t ReadUInt64();
    char* ReadString();

    //writer
    void WriteByte(int8_t b);
    void WriteBytes(vector<int8_t> b);
    void WriteChars(vector<char> b);
    void Write(int16_t val);
    void Write(int32_t val);
    void Write(int64_t val);
    void Write(uint16_t val);
    void Write(uint32_t val);
    void Write(uint64_t val);
    void Write(char* val);
    void WriteAtIndex(int16_t val, int32_t pos);
    void WriteAtIndex(int32_t val, int32_t pos);
    void WriteAtIndex(int64_t val, int32_t pos);
    void WriteAtIndex(uint16_t val, int32_t pos);
    void WriteAtIndex(uint32_t val, int32_t pos);
    void WriteAtIndex(uint64_t val, int32_t pos);



    //extras
    int16_t ToInt16(int8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    int32_t ToInt32(int8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    int64_t ToInt64(int8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    uint16_t ToUInt16(int8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    uint32_t ToUInt32(int8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    uint64_t ToUInt64(int8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    vector<int8_t> SwapBytes(vector<int8_t> data);

};


#endif // PIKIO_H_INCLUDED
