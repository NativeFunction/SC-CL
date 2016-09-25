#ifndef PIKIO_H_INCLUDED
#define PIKIO_H_INCLUDED

#include <stdint.h>
#include "Utils.h"

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)
using namespace std;
using namespace Utils;
using namespace Utils::System;
using namespace Utils::Bitwise;

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
    uint8_t* BaseStream;
    vector<uint8_t> BaseWrite;
    int64_t Position = 0;
    size_t Length;
    int32_t NullTerminatorMaxLength;

    //helpers
    inline uint8_t* BaseLoc(){return (BaseStream + Position);}

    //constructor
    void Init();
    void Init(uint8_t* xIn, size_t Len);
    void Init(uint8_t* xIn, size_t Len, Endianess endian);
    void Init(uint8_t* xIn, size_t Len, Endianess endian, int32_t nullTerminatorMaxLength);
    void InitWriter(Endianess endian);

    //reader
    uint8_t ReadByte();
    vector<uint8_t> ReadBytes(int32_t len);
    vector<char> ReadBytesAsStr(int32_t len);

    template<typename T>
    T ReadDynamic()
    {
        T ret = ToDynamic<T>(BaseStream, Position, Length, Endian);
        Position += sizeof(T);
        return ret;
    }
    template<typename T>
    T PeekDynamic(uint32_t count = 0)
    {
        return ToDynamic<T>(BaseStream, Position + count, Length, Endian);
    }

    int16_t ReadInt16();
    int32_t ReadInt32();
    int64_t ReadInt64();
    uint16_t ReadUInt16();
    uint32_t ReadUInt32();
    uint64_t ReadUInt64();
    char* ReadString();

    //writer
    void WriteByte(uint8_t b);
    void WriteBytes(vector<uint8_t> b);
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
    template<typename T>
    T ToDynamic(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian)
    {
        T Store = *(T*)(data + startIndex);
        if(startIndex + sizeof(T) > length)
            Throw( "Invalid Data Length" );
        switch (endian)
        {
            case Endianess::Big:
                if(!IS_BIG_ENDIAN)
                    Store = SwapEndian(Store);
            break;
            case Endianess::Little:
                if(!IS_BIG_ENDIAN)
                    break;
                else
                    Store = SwapEndian(Store);
            break;
            case Endianess::SystemDefault:
                break;
            default:
                Throw("ToInt16 Unknown Error");
        }
        return Store;

    }

    int16_t ToInt16(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    int32_t ToInt32(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    int64_t ToInt64(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    uint16_t ToUInt16(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    uint32_t ToUInt32(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    uint64_t ToUInt64(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian);
    vector<uint8_t> SwapBytes(vector<uint8_t> data);

};


#endif // PIKIO_H_INCLUDED
