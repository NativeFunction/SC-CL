#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "PikIO.h"
#include "Utils.h"
#include <stdint.h>
#include <string>
using namespace std;

//{ Constructor

void PikIO::Init()
{
    Endian = Endianess::SystemDefault;
    NullTerminatorMaxLength = 512;
    Position = 0;
}
void PikIO::Init(void* xIn, size_t Len)
{
    BaseStream = xIn;
    Endian = Endianess::SystemDefault;
    NullTerminatorMaxLength = 512;
    Length = Len;
    Position = 0;
}
void PikIO::Init(void* xIn, size_t Len, Endianess endian)
{
    BaseStream = xIn;
    Endian = endian;
    NullTerminatorMaxLength = 512;
    Length = Len;
    Position = 0;
}
void PikIO::Init(void* xIn, size_t Len, Endianess endian, int32_t nullTerminatorMaxLength)
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
int8_t PikIO::ReadByte()
{
    int8_t ret = *(int8_t*)BaseLoc();
    Position += 1;
    return ret;
}
vector<int8_t> PikIO::ReadBytes(int32_t len)
{
    if(Position + len > Length)
        Utils::Throw( "Invalid Data Length" );

    vector<int8_t> ret((int8_t*)BaseLoc(), (int8_t*)((int8_t*)BaseLoc() + len));
    Position += len;
    return ret;
}
vector<char> PikIO::ReadBytesAsStr(int32_t len)
{
    if(Position + len > Length)
        Utils::Throw( "Invalid Data Length" );

    vector<char> ret((char*)BaseLoc(), (char*)((int8_t*)BaseLoc() + len));
    Position += len;
    return ret;
}

int16_t PikIO::ReadInt16()
{
    int16_t ret = ToInt16((int8_t*)BaseStream, Position, Length, Endian);
    Position += 2;
    return ret;

}
int32_t PikIO::ReadInt32()
{
    int32_t ret = ToInt32((int8_t*)BaseStream, Position, Length, Endian);
    Position += 4;
    return ret;
}
int64_t PikIO::ReadInt64()
{
    int64_t ret = ToInt64((int8_t*)BaseStream, Position, Length, Endian);
    Position += 8;
    return ret;
}
uint16_t PikIO::ReadUInt16()
{
    uint16_t ret = ToUInt16((int8_t*)BaseStream, Position, Length, Endian);
    Position += 2;
    return ret;
}
uint32_t PikIO::ReadUInt32()
{
    uint32_t ret = ToUInt32((int8_t*)BaseStream, Position, Length, Endian);
    Position += 4;
    return ret;
}
uint64_t PikIO::ReadUInt64()
{
    uint64_t ret = ToUInt64((int8_t*)BaseStream, Position, Length, Endian);
    Position += 8;
    return ret;
}
char* PikIO::ReadString()
{
    int32_t len = strlen((char*)BaseLoc());
    vector<int8_t> bytes = ReadBytes(len);
    char* ret = new char [len + 1];
    strcpy(ret,string(bytes.begin(),bytes.end()).c_str());
    return ret;
}
//}
//{ Writer
void PikIO::WriteByte(int8_t b)
{
    BaseWrite.push_back(b);
}
void PikIO::WriteBytes(vector<int8_t> b)
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
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
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
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
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
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
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
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
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
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
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
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
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
        Utils::Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));
}
void PikIO::WriteAtIndex(int32_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Utils::Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));

}
void PikIO::WriteAtIndex(int64_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Utils::Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
   memcpy(BaseWrite.data() + pos,&val,sizeof(val));
}
void PikIO::WriteAtIndex(uint16_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Utils::Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));

}
void PikIO::WriteAtIndex(uint32_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Utils::Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
    memcpy(BaseWrite.data() + pos,&val,sizeof(val));

}
void PikIO::WriteAtIndex(uint64_t val, int32_t pos)
{
    if(pos + sizeof(val) > BaseWrite.size())
        Utils::Throw( "Position Out Of Bounds" );

    switch(Endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                val = Utils::SwapEndian(val);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                val = Utils::SwapEndian(val);
        break;
        case Endianess::SystemDefault:
            break;
    }
   memcpy(BaseWrite.data() + pos,&val,sizeof(val));
}


//}
//{ Extras
int16_t PikIO::ToInt16(int8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	int16_t Store = *(int16_t*)(data + startIndex);
    if(startIndex + 2 > length)
        Utils::Throw( "Invalid Data Length" );
    switch (endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::SystemDefault:
            break;
        default:
            Utils::Throw("ToInt16 Unknown Error");
    }
    return Store;

}
int32_t PikIO::ToInt32(int8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	int32_t Store = *(int32_t*)(data + startIndex);
    if(startIndex + 4 > length)
        Utils::Throw( "Invalid Data Length" );
    switch (endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::SystemDefault:
            break;
        default:
            Utils::Throw("ToInt32 Unknown Error");
    }
    return Store;

}
int64_t PikIO::ToInt64(int8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	int64_t Store = *(int64_t*)(data + startIndex);
    if(startIndex + 8 > length)
        Utils::Throw( "Invalid Data Length" );
    switch (endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::SystemDefault:
            break;
        default:
            Utils::Throw("ToInt64 Unknown Error");
    }
    return Store;

}
uint16_t PikIO::ToUInt16(int8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	uint16_t Store = *(uint16_t*)(data + startIndex);
    if(startIndex + 2 > length)
        Utils::Throw( "Invalid Data Length" );
    switch (endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::SystemDefault:
            break;
        default:
            Utils::Throw("ToInt16 Unknown Error");
    }
    return Store;

}
uint32_t PikIO::ToUInt32(int8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	uint32_t Store = *(uint32_t*)(data + startIndex);
    if(startIndex + 4 > length)
        Utils::Throw( "Invalid Data Length" );
    switch (endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::SystemDefault:
            break;
        default:
            Utils::Throw("ToInt32 Unknown Error");
    }
    return Store;

}
uint64_t PikIO::ToUInt64(int8_t* data, int32_t startIndex, int32_t length, Endianess endian)
{
	uint64_t Store = *(uint64_t*)(data + startIndex);
    if(startIndex + 8 > length)
        Utils::Throw( "Invalid Data Length" );
    switch (endian)
    {
        case Endianess::Big:
            if(!IS_BIG_ENDIAN)
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::Little:
            if(!IS_BIG_ENDIAN)
                break;
            else
                Store = Utils::SwapEndian(Store);
        break;
        case Endianess::SystemDefault:
            break;
        default:
            Utils::Throw("ToInt64 Unknown Error");
    }
    return Store;

}
vector<int8_t> PikIO::SwapBytes (vector<int8_t> data)
{
    int Size = data.size();
    vector<int8_t> ret(Size);
    for(int i = 0; i < Size; i++)
    {
        ret[i] = data[i - Size];
    }
    return ret;
}
//}


