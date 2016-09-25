#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "PikIO.h"
#include "Utils.h"
#include <stdint.h>
#include <string>

using namespace std;
using namespace Utils::Bitwise;
using namespace Utils::System;

//{ Constructor

void PikIO::Init()
{
    Endian = Endianess::SystemDefault;
    NullTerminatorMaxLength = 512;
    Position = 0;
}
void PikIO::Init(uint8_t* xIn, size_t Len)
{
    BaseStream = xIn;
    Endian = Endianess::SystemDefault;
    NullTerminatorMaxLength = 512;
    Length = Len;
    Position = 0;
}
void PikIO::Init(uint8_t* xIn, size_t Len, Endianess endian)
{
    BaseStream = xIn;
    Endian = endian;
    NullTerminatorMaxLength = 512;
    Length = Len;
    Position = 0;
}
void PikIO::Init(uint8_t* xIn, size_t Len, Endianess endian, int32_t nullTerminatorMaxLength)
{
    BaseStream = xIn;
    Endian = endian;
    NullTerminatorMaxLength = NullTerminatorMaxLength;
    Length = Len;
    Position = 0;
}
void PikIO::InitWriter(Endianess endian)
{
    Endian = endian;
    Position = 0;
}
//}
//{ Reader
uint8_t PikIO::ReadByte()
{
    uint8_t ret = *(uint8_t*)BaseLoc();
    Position += 1;
    return ret;
}
vector<uint8_t> PikIO::ReadBytes(int32_t len)
{
    if(Position + len > Length)
        Throw( "Invalid Data Length (ReadBytes)" );

    vector<uint8_t> ret((uint8_t*)BaseLoc(), (uint8_t*)((uint8_t*)BaseLoc() + len));
    Position += len;
    return ret;
}
vector<char> PikIO::ReadBytesAsStr(int32_t len)
{
    if(Position + len > Length)
        Throw( "Invalid Data Length (ReadBytesAsStr)" );

    vector<char> ret((char*)BaseLoc(), (char*)((int8_t*)BaseLoc() + len));
    Position += len;
    return ret;
}


int16_t PikIO::ReadInt16()
{
    int16_t ret = ToInt16(BaseStream, Position, Length, Endian);
    Position += 2;
    return ret;

}
int32_t PikIO::ReadInt32()
{
    int32_t ret = ToInt32(BaseStream, Position, Length, Endian);
    Position += 4;
    return ret;
}
int64_t PikIO::ReadInt64()
{
    int64_t ret = ToInt64(BaseStream, Position, Length, Endian);
    Position += 8;
    return ret;
}
uint16_t PikIO::ReadUInt16()
{
    uint16_t ret = ToUInt16(BaseStream, Position, Length, Endian);
    Position += 2;
    return ret;
}
uint32_t PikIO::ReadUInt32()
{
    uint32_t ret = ToUInt32(BaseStream, Position, Length, Endian);
    Position += 4;
    return ret;
}
uint64_t PikIO::ReadUInt64()
{
    uint64_t ret = ToUInt64(BaseStream, Position, Length, Endian);
    Position += 8;
    return ret;
}
char* PikIO::ReadString()
{
    int32_t len = strlen((char*)BaseLoc());
    vector<uint8_t> bytes = ReadBytes(len);
    char* ret = new char [len + 1];
    strcpy(ret,string(bytes.begin(),bytes.end()).c_str());
    return ret;
}
//}
//{ Writer
void PikIO::WriteByte(uint8_t b)
{
    BaseWrite.push_back(b);
}
void PikIO::WriteBytes(vector<uint8_t> b)
{
    BaseWrite.insert(BaseWrite.end(), b.begin(), b.end());
}
void PikIO::WriteChars(vector<char> b)
{
    BaseWrite.insert(BaseWrite.end(), b.begin(), b.end());
}

void PikIO::Write(int16_t val)
{
    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    BaseWrite.push_back(val & 0xFF);
    BaseWrite.push_back(val >> 8);
}
void PikIO::Write(int32_t val)
{
    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    BaseWrite.push_back(val & 0xFF);
    BaseWrite.push_back(val >> 8);
    BaseWrite.push_back(val >> 16);
    BaseWrite.push_back(val >> 24);

}
void PikIO::Write(int64_t val)
{
    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    BaseWrite.push_back(val & 0xFF);
    BaseWrite.push_back(val >> 8);
    BaseWrite.push_back(val >> 16);
    BaseWrite.push_back(val >> 24);
    BaseWrite.push_back(val >> 32);
    BaseWrite.push_back(val >> 40);
    BaseWrite.push_back(val >> 48);
    BaseWrite.push_back(val >> 56);

}
void PikIO::Write(uint16_t val)
{
    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    BaseWrite.push_back(val & 0xFF);
    BaseWrite.push_back(val >> 8);

}
void PikIO::Write(uint32_t val)
{
    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    BaseWrite.push_back(val & 0xFF);
    BaseWrite.push_back(val >> 8);
    BaseWrite.push_back(val >> 16);
    BaseWrite.push_back(val >> 24);

}
void PikIO::Write(uint64_t val)
{
    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    BaseWrite.push_back(val & 0xFF);
    BaseWrite.push_back(val >> 8);
    BaseWrite.push_back(val >> 16);
    BaseWrite.push_back(val >> 24);
    BaseWrite.push_back(val >> 32);
    BaseWrite.push_back(val >> 40);
    BaseWrite.push_back(val >> 48);
    BaseWrite.push_back(val >> 56);
}
void PikIO::Write(char* val)
{
    int32_t len = strlen(val);
    for(int i = 0; i < len; i++)
    {
        BaseWrite.push_back(((int8_t*)val)[i]);
    }
    BaseWrite.push_back(0);
}

void PikIO::WriteAtIndex(int16_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));
}
void PikIO::WriteAtIndex(int32_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));

}
void PikIO::WriteAtIndex(int64_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
   memcpy(BaseWrite.data() + pos,&val,sizeof(val));
}
void PikIO::WriteAtIndex(uint16_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));

}
void PikIO::WriteAtIndex(uint32_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));

}
void PikIO::WriteAtIndex(uint64_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
   memcpy(BaseWrite.data() + pos,&val,sizeof(val));
}


//}
//{ Extras
int16_t PikIO::ToInt16(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	int16_t Store = *(int16_t*)(data + startIndex);
    if(startIndex + 2 > length)
        Throw( "Invalid Data Length (ToInt16)" );
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
int32_t PikIO::ToInt32(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	int32_t Store = *(int32_t*)(data + startIndex);
    if(startIndex + 4 > length)
    {

        cout << Position << '\n';
        Throw( "Invalid Data Length (ToInt32)" );
    }

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
            Throw("ToInt32 Unknown Error");
    }
    return Store;

}
int64_t PikIO::ToInt64(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	int64_t Store = *(int64_t*)(data + startIndex);
    if(startIndex + 8 > length)
        Throw( "Invalid Data Length (ToInt64)" );
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
            Throw("ToInt64 Unknown Error");
    }
    return Store;

}
uint16_t PikIO::ToUInt16(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	uint16_t Store = *(uint16_t*)(data + startIndex);
    if(startIndex + 2 > length)
        Throw( "Invalid Data Length (ToUInt16)" );
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
uint32_t PikIO::ToUInt32(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	uint32_t Store = *(uint32_t*)(data + startIndex);
    if(startIndex + 4 > length)
    {
        cout << "Trying to get data from " << startIndex << " when length is " << length << '\n';
        Throw( "Invalid Data Length (ToUInt32)" );
    }


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
            Throw("ToInt32 Unknown Error");
    }
    return Store;

}
uint64_t PikIO::ToUInt64(uint8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	uint64_t Store = *(uint64_t*)(data + startIndex);
    if(startIndex + 8 > length)
        Throw( "Invalid Data Length (ToUInt64)" );
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
            Throw("ToInt64 Unknown Error");
    }
    return Store;

}
vector<uint8_t> PikIO::SwapBytes (vector<uint8_t> data)
{
    int Size = data.size();
    vector<uint8_t> ret(Size);
    for(int i = 0; i < Size; i++)
    {
        ret[i] = data[i - Size];
    }
    return ret;
}
//}


