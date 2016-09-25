#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <map>
#include <streambuf>
#include <conio.h>
#include <cstdlib>
#include <climits>
#include <limits>
#include <set>
#include <boost/algorithm/string/classification.hpp>
#include <boost/tokenizer.hpp>
#include "Utils.h"
#include "XSC.h"
#include "Constants.h"
#include "PikIO.h"

//typedef boost::iterator_range<string::const_iterator> string_view;

using namespace std;
using namespace Constants;

//{ XSCHeader
void XSCHeader::XSCHeaderClear()
{
    Statics.clear();
}
void XSCHeader::SetupNewStatics(int staticsCount)
{
    Statics.clear();
    Statics.resize(StaticsCount);
}
void XSCHeader::AddStatic(int x)
{
    Statics.push_back(x);
}
void XSCHeader::AddStatic(float x)
{
    Statics.push_back(Utils::FloatToInt(x));
}
void XSCHeader::SetStatics(vector<int> collection)
{
    Statics.clear();
    Statics = collection;
}
float XSCHeader::GetStaticAsFloat(int index)
{
    return Utils::IntToFloat(Statics[index]);
}
int XSCHeader::GetStaticAsInt(int index)
{
    return Statics[index];
}
//}

//{ XSC

void XSC::OpenScript(void* xIn, size_t* length )
{
    PikIO io;
    io.Init(xIn, *length, PikIO::Endianess::Big);
    Header = XSCHeader();

//{ Read Header
    Header.PgBase = io.ReadInt32();
    if(Header.PgBase == 0x52534337)//rsc7
    {
        void* temp = new char [*length - 16];
        memcpy(temp,xIn + 16, *length - 16);
        *length -= 16;
        memcpy(xIn,temp, *length);
        io.Init(xIn, *length, PikIO::Endianess::Big);
        Header.PgBase = io.ReadInt32();
    }

    Header.Unk1 = io.ReadInt32();
    Header.CodeBlocksListOffset = io.ReadInt32() & 0xFFFFFF;
    Header.Unk2 = io.ReadInt32();

    Header.CodeLength = io.ReadInt32();
    Header.ParameterCount = io.ReadInt32();
    Header.StaticsCount = io.ReadInt32();
    Header.GlobalsSize = io.ReadInt32();
    Header.NativesCount = io.ReadInt32();
    Header.StaticsOffset = io.ReadInt32() & 0xFFFFFF;
    Header.GlobalsPtr = io.ReadInt32() & 0xFFFFFF;
    Header.NativesOffset = io.ReadInt32() & 0xFFFFFF;
    Header.Unk3 = io.ReadInt32();
    Header.Unk4 = io.ReadInt32();
    Header.NameHash = io.ReadUInt32();
    Header.Unk5 = io.ReadInt32();
    Header.ScriptNameOffset = io.ReadInt32() & 0xFFFFFF;
    Header.StringsOffset = io.ReadInt32() & 0xFFFFFF;
    Header.StringsSize = io.ReadInt32();
    Header.Unk6 = io.ReadInt32();

    Header.CodePagePointers.resize((Header.CodeLength + (1 << 14) - 1 >> 14));
    Header.StringPagePointers.resize((Header.StringsSize + (1 << 14) - 1 >> 14));

    Header.CodePages.resize(Header.CodePagePointers.size());
    Header.StringPages.resize(Header.StringPagePointers.size());
    Header.Natives.resize(Header.NativesCount);


    for (uint32_t i = 0; i < Header.CodePagePointers.size(); i++)
    {
        io.Position = Header.CodeBlocksListOffset + (i * 4);
        Header.CodePagePointers[i] = io.ReadInt32() & 0xFFFFFF;

        io.Position = Header.CodePagePointers[i];
        int thisPageLen = Utils::GetPageLenAtPage(Header.CodePagePointers.size(), Header.CodeLength, i, Constants::XboxPageSize);
        Header.CodePages[i] = io.ReadBytes(thisPageLen);
    }


    io.Position = Header.StringsOffset;
    for (uint32_t i = 0; i < Header.StringPagePointers.size(); i++)
    {
        io.Position = Header.StringsOffset + (i * 4);
        Header.StringPagePointers[i] = io.ReadInt32() & 0xFFFFFF;

        io.Position = Header.StringPagePointers[i];
        int thisPageLen = Utils::GetPageLenAtPage(Header.StringPagePointers.size(), Header.StringsSize, i, Constants::XboxPageSize);
        Header.StringPages[i] = io.ReadBytesAsStr(thisPageLen);
        //printf("%X", Header.StringPages[i][0]);
    }

    io.Position = Header.NativesOffset;
    for (int i = 0; i < Header.NativesCount; i++)
        Header.Natives[i] = io.ReadUInt32();

    io.Position = Header.StaticsOffset;
    for (int i = 0; i < Header.StaticsCount; i++)
        Header.AddStatic(io.ReadInt32());

    io.Position = Header.ScriptNameOffset;
    Header.ScriptName = (char*)io.BaseLoc();
    io.Position += strlen(Header.ScriptName) + 1;
//}
}
void XSC::Write(FILE* file,char* path, Constants::Platform platform, PikIO::Endianess endian, bool rsc7 = true)
{
    int32_t placeHolderOffsets[6];
    PikIO dataWriter;
    dataWriter.InitWriter(PikIO::Endianess::Big);
    //0: Code blocks ptrs
    //1: unkPtrs
    //2: natives ptr
    //3: script name
    //4: statics
    //5: string block ptrs

//{ Delegates
    auto GetSpaceLeft = [&](auto size)
    {
        int sl = size - ((int)dataWriter.BaseWrite.size() % size);
        if (sl == 0)
            sl = size;
        return (uint32_t)sl;
    };
    auto FillPage = [&]()
    {
        vector<int8_t> buffer (GetSpaceLeft(platform == Constants::Platform::Xbox ? 16384 : 8192));
        dataWriter.WriteBytes(buffer);
    };
    auto FillFile = [&]()
    {
        vector<int8_t> buffer (GetSpaceLeft(platform == Constants::Platform::Xbox ? 8192 : 4096));
        dataWriter.WriteBytes(buffer);
    };
    auto Pad = [&]()
    {
        int pad = 16 - (int)dataWriter.BaseWrite.size() % 16;
        if (pad == 0 || pad == 16)
            return;
        vector<int8_t> buffer (pad);
        dataWriter.WriteBytes(buffer);
    };
    auto ForcePad = [&]()
    {
        int pad = 16 - (int)dataWriter.BaseWrite.size() % 16;
        if (pad == 0 || pad == 16)
            pad = 16;
        vector<int8_t> buffer (pad);
        dataWriter.WriteBytes(buffer);
    };
//}

//{ Write Header
    int32_t headerLocation = 0;
    Header.StaticsCount = Header.Statics.size();
    Header.NameHash = Utils::Joaat(Header.ScriptName);
    Header.Unk5 = 1; //typically 1

    dataWriter.Write(Header.PgBase);
    dataWriter.Write(0); //Unk1 ptr
    dataWriter.Write(0); //codeBlocksListOffsetPtr
    dataWriter.Write(Header.Unk2);
    dataWriter.Write(Header.CodeLength);
    dataWriter.Write(Header.ParameterCount);
    dataWriter.Write(Header.StaticsCount);
    dataWriter.Write(Header.GlobalsSize);
    dataWriter.Write(Header.NativesCount);
    dataWriter.Write(0); //Statics offset
    dataWriter.Write(0); //Globals ptr, stay 0
    dataWriter.Write(0); //native offset
    dataWriter.Write(Header.Unk3);
    dataWriter.Write(Header.Unk4);
    dataWriter.Write(Header.NameHash);
    dataWriter.Write(Header.Unk5);
    dataWriter.Write(0); //script name offset
    dataWriter.Write(0); //strings offset
    dataWriter.Write(Header.StringsSize);
    dataWriter.Write(Header.Unk6);
//}

//{ Write Pages
    //Write Code Pages
    Header.CodePagePointers.clear();
    Header.CodePagePointers.resize(Header.CodePages.size());
    for (uint32_t i = 0; i < Header.CodePages.size(); i++)
    {
        Pad();
        if (GetSpaceLeft(16384) < Header.CodePages[i].size())
            FillPage();

        Header.CodePagePointers[i] = dataWriter.BaseWrite.size();
        dataWriter.WriteBytes(Header.CodePages[i]);

    }

    //Write String Pages
    Header.StringPagePointers.clear();
    Header.StringPagePointers.resize(Header.StringPages.size());
    for (uint32_t i = 0; i < Header.StringPages.size(); i++)
    {
        Pad();
        if (GetSpaceLeft(16384) < Header.StringPages[i].size())
            FillPage();

        Header.StringPagePointers[i] = dataWriter.BaseWrite.size();
        dataWriter.WriteChars(Header.StringPages[i]);

    }

    //Write natives
    if (Header.Natives.size() > 0)
    {
        Pad();
        if (GetSpaceLeft(16384) < Header.Natives.size() * 4)
            FillPage();

        placeHolderOffsets[2] = dataWriter.BaseWrite.size();

        for(uint32_t i = 0; i < Header.Natives.size(); i++)
            dataWriter.Write(Header.Natives[i]);

    }
    else
        placeHolderOffsets[2] = 0;

    //Write statics
    if (Header.Statics.size() > 0)
    {
        Pad();
        if (GetSpaceLeft(16384) < Header.Statics.size() * 4)
            FillPage();

        placeHolderOffsets[4] = dataWriter.BaseWrite.size();

        for(uint32_t i = 0; i < Header.Statics.size(); i++)
            dataWriter.Write(Header.Statics[i]);

    }
    else
        placeHolderOffsets[4] = 0;
//}

//{ Write Misc & Pointers
    //Write script name
    Pad();
    if (GetSpaceLeft(16384) < strlen(Header.ScriptName) + 1)
        FillPage();
    placeHolderOffsets[3] = dataWriter.BaseWrite.size();
    dataWriter.Write(Header.ScriptName);

    //Write code page pointers
    Pad();
    if (GetSpaceLeft(16384) < Header.CodePages.size() * 4)
        FillPage();
    placeHolderOffsets[0] = dataWriter.BaseWrite.size();
    for (uint32_t i = 0; i < Header.CodePages.size(); i++)
        dataWriter.Write(0);

    //Write string page pointers
    Pad();
    if (GetSpaceLeft(16384) < Header.StringPages.size() * 4)
        FillPage();
    placeHolderOffsets[5] = dataWriter.BaseWrite.size();
    for (uint32_t i = 0; i < Header.StringPages.size(); i++)
        dataWriter.Write(0);

    //write unk1
    Pad();
    vector<int8_t> _unkPTRData(16);
    _unkPTRData[4] = 1;
    if (GetSpaceLeft(16384) < _unkPTRData.size())
        FillPage();
    placeHolderOffsets[1] = dataWriter.BaseWrite.size();
    dataWriter.WriteBytes(_unkPTRData);
    FillFile();
//}

//{ Fix header and other pointers
    dataWriter.WriteAtIndex(Utils::GetPointerInt(placeHolderOffsets[0]),headerLocation + 8); //code block ptrs offset
    dataWriter.WriteAtIndex(Utils::GetPointerInt(placeHolderOffsets[4]), headerLocation + 36); //statics offset
    dataWriter.WriteAtIndex(Utils::GetPointerInt(placeHolderOffsets[3]), headerLocation + 64); //script name offset
    dataWriter.WriteAtIndex(Utils::GetPointerInt(placeHolderOffsets[2]), headerLocation + 44); //natives offset
    dataWriter.WriteAtIndex(Utils::GetPointerInt(placeHolderOffsets[1]), headerLocation + 4); //UnkPtr1
    dataWriter.WriteAtIndex(Utils::GetPointerInt(placeHolderOffsets[5]), headerLocation + 68); //string block ptrs offset

    for (uint32_t i = 0; i < Header.CodePagePointers.size(); i++)
        dataWriter.WriteAtIndex(Utils::GetPointerInt(Header.CodePagePointers[i]),  placeHolderOffsets[0] + (i * 4));
    for (uint32_t i = 0; i < Header.StringPagePointers.size(); i++)
        dataWriter.WriteAtIndex(Utils::GetPointerInt(Header.StringPagePointers[i]), placeHolderOffsets[5] + (i * 4));
//}

file = fopen(path, "wb");

//{ Write File
    if (rsc7)
    {
        int32_t flag = Utils::GetFlagFromSize(dataWriter.BaseWrite.size(), platform == Constants::Platform::Xbox ? 8192 : 4096);
        switch(endian)
        {
            case PikIO::Endianess::Big:
                if(!IS_BIG_ENDIAN)
                    flag = Utils::SwapEndian(flag);
            break;
            case PikIO::Endianess::Little:
                if(!IS_BIG_ENDIAN)
                    break;
                else
                    flag = Utils::SwapEndian(flag);
            break;
            case PikIO::Endianess::SystemDefault:
                break;
        }

        vector<int8_t> rsc7 = {0x52, 0x53, 0x43, 0x37, 0x00, 0x00, 0x00, 0x09,static_cast<int8_t>(flag & 0xFF),static_cast<int8_t>(flag >> 8),static_cast<int8_t>(flag >> 16),static_cast<int8_t>(flag >> 24),(int8_t)0x90, 0x00, 0x00, 0x00};

        fwrite(rsc7.data(), 1, rsc7.size(), file);

    }

    fwrite(dataWriter.BaseWrite.data(), 1, dataWriter.BaseWrite.size(), file);
    fclose(file);


//}

}

//{ Compile Global vars
    enum JumpType{
        Jump,
        Call,
        Switch,
        pCall
    };
    enum ParamTypes : uint8_t{
        None,
        Static,
        Frame,
        Native,
        Global
    };
    enum PushTypes : uint8_t{
        Push_None,
        Push_Enum,
        Push_Loc,
        Push_Hash
    };

    struct CharStrType{
        char* str;
        uint32_t len;
        PushTypes type;
    };
    struct SavedJumps{
        JumpType JumpType;
        uint32_t TablePos;
        uint32_t LineStartPos;
        uint32_t LineNum;
        string Label;
    };
    struct CharStr{
        char* str;
        uint32_t len;
    };
    struct StrIndex{
        uint32_t index;
        uint32_t len;
    };


    uint32_t line = 1;
    uint32_t LineStart = 0;
    uint32_t lstring_size;
    uint32_t string_size;
    uint32_t CharNum = 0;
    const char* cmpdata;
    map<string,uint32_t>* gLabelLocations;
    map<string,uint32_t>* gEnums;
    map<string,uint16_t>* gFrameNames;
    map<string,uint16_t>* gStaticNames;
    map<string,uint32_t>* gNativeNames;
    map<string,uint32_t>* gGlobalNames;
    vector<uint8_t>* gtable;
    vector<SavedJumps>* gJumps;
//}

//{ Compile Private Functions
	void UnkOpcodeError(){
		cout << "Error on line " << line << "\r\n";
		cout << "Opcode " << ((uint8_t*)cmpdata)[CharNum + 2] << "\r\n";
        Utils::Throw("Unknown Opcode");
	}
    char* GetLineG(){
		uint32_t i;
        for(i = LineStart; i < lstring_size; i++)
        {
            if(cmpdata[i] == '\r' || cmpdata[i] == '\n' )
            {
                uint32_t len = i - LineStart;
                char* buffer = new char [len + 1];
                memcpy(buffer, cmpdata + LineStart,  len );
                buffer[len] = '\0';
                return buffer;
            }

        }
		char* buffer = new char [i];
        memcpy(buffer, cmpdata + LineStart, i - LineStart );
        buffer[i - 1] = '\0';
        return buffer;
    }
    char* GetLineGAtPos(uint32_t start){
		uint32_t i;
        for(i = start; i < lstring_size; i++)
        {
            if(cmpdata[i] == '\r' || cmpdata[i] == '\n' )
            {
                uint32_t len = i - start;
                char* buffer = new char [len + 1];
                memcpy(buffer, cmpdata + start,  len );
                buffer[len] = '\0';
                return buffer;
            }

        }
		char* buffer = new char [i];
        memcpy(buffer, cmpdata + start, i - start );
        buffer[i - 1] = '\0';
        return buffer;
    }
    void ChkRem (const char* chars = nullptr, const uint32_t len = 0, const bool isparam = false){
        //pushb 28
        CharNum++;
        if(CharNum + len > string_size)
        {
            cout << "Error on line " << line << "\r\n";
            Utils::Throw("Index Out Of Bounds");
        }
        else if(len != 0)
        {
            for(uint32_t i = 0; i < len; i++)
            {
                if(tolower(cmpdata[CharNum + i]) != chars[i])
                {
                    UnkOpcodeError();
                }
            }
            CharNum+=len;
        }

        if(isparam)
        {
            if(cmpdata[CharNum] == ' ')
                return;
            else
            {
                cout << "Error on line " << line << "\r\n";
                cout << "Code: " << 0 << "\r\n";
                cout << "Line: " << GetLineG() << "\r\n";
                Utils::Throw("Invalid Parameter");
            }
        }
        else if(CharNum >= string_size)
            return;

        switch(cmpdata[CharNum])
        {
            case '\r':
            case '\n':
            case ' ':
            case '/':
            return;
            default:
                UnkOpcodeError();
            break;
        }
    }
    bool ChkRemBool (const char* chars = nullptr, const uint32_t len = 0){
        if(CharNum + len > string_size)
        {
            cout << "Error on line " << line << "\r\n";
            Utils::Throw("Index Out Of Bounds");
        }
        else if(len != 0)
        {
            for(uint32_t i = 0; i < len; i++)
            {
                if(tolower(cmpdata[CharNum + i]) != chars[i])
                    return false;
            }
            CharNum+=len;
            return true;
        }
        return false;
    }
    string GetParamAsLabel(bool islabel){
		if(!islabel)
        {
            if(CharNum < lstring_size)
            {
                if(cmpdata[CharNum] == '@')
                {
                    CharNum++;
                }
                else
                {
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Invalid Jump Format");
                }
            }
        }
        uint32_t Starti = CharNum;
        while(CharNum < lstring_size)
        {
            switch(cmpdata[CharNum])
            {
                case '/':
                    if(CharNum + 1 < lstring_size)
                    {
                        if(cmpdata[CharNum + 1] == '/')
                            goto endfindlabel;
                    }
                break;
                case '\r':
                case '\n':
                case ' ':
                case ']':
                goto endfindlabel;

            }
			CharNum++;
        }
        endfindlabel:
		uint32_t len = CharNum - Starti;
        char* buffer = new char [len + 1];
        memcpy(buffer, cmpdata + Starti, len);
        buffer[len] = '\0';
        return string(buffer);
    }
    string GetParamString(){
        CharNum++;
        if(CharNum < lstring_size)
        {
            if(cmpdata[CharNum] == '"')
            {
                CharNum++;
            }
            else
            {
                cout << "Error on line " << line << "\r\n";
                cout << "Code: " << 0 << "\r\n";
                cout << "Line: " << GetLineG() << "\r\n";
                Utils::Throw("Invalid String Format");
            }
        }
        vector<char> buffer;
        buffer.reserve(64);
        while(CharNum < lstring_size)
        {
            switch(cmpdata[CharNum])
            {
                case '\\':
                    CharNum++;
                    if(CharNum < lstring_size)
                    {
                        switch(cmpdata[CharNum])
                        {
                            case 'n':
                                buffer.push_back('\n');
                                break;
                            case 'r':
                                buffer.push_back('\r');
                                break;
                            case '\\':
                            case '"':
                            default:
                                buffer.push_back(cmpdata[CharNum]);
                                break;
                        }
                    }
                    else
                    {
                        cout << "Error on line " << line << "\r\n";
                        cout << "Code: " << 0 << "\r\n";
                        cout << "Line: " << GetLineG() << "\r\n";
                        Utils::Throw("Character Literal Out Of Bounds");
                    }
                    break;
                case '\r':
                case '\n':
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Invalid String Format");
                break;
                case '"':
                    goto endfindstring;
                default:
                    buffer.push_back(cmpdata[CharNum]);
                break;

            }
			CharNum++;
        }
        endfindstring:
        return string(buffer.data(),buffer.size());
    }
    string GetParams(){
		CharNum++;
		uint32_t Starti = CharNum;
        while(CharNum < lstring_size)
        {
            if(cmpdata[CharNum] == '/')
            {
                if(CharNum + 1 < lstring_size)
                {
                    if(cmpdata[CharNum + 1] == '/')
                        break;
                }
            }
            else if(cmpdata[CharNum] == '\r' || cmpdata[CharNum] == '\n' || cmpdata[CharNum] == ' ')
                break;

			CharNum++;
        }
		uint32_t len = CharNum - Starti;
        char* buffer = new char [len + 1];
        memcpy(buffer, cmpdata + Starti, len);
        buffer[len] = '\0';
        return string(buffer);
    }
    CharStr GetParami(){
		CharNum++;
		uint32_t Starti = CharNum;
        while(CharNum < lstring_size)
        {
            if(cmpdata[CharNum] == '/')
            {
                if(CharNum + 1 < lstring_size)
                {
                    if(cmpdata[CharNum + 1] == '/')
                        break;
                }
            }
            else if(cmpdata[CharNum] == '\r' || cmpdata[CharNum] == '\n' || cmpdata[CharNum] == ' ')
                break;

			CharNum++;
        }
		uint32_t len = CharNum - Starti;
        char* buffer = new char [len + 1];
        memcpy(buffer, cmpdata + Starti, len);
        buffer[len] = '\0';
        return {buffer, len};
    }
    CharStrType GetParamiWithEnums(){

        bool istype = false;
        PushTypes type = PushTypes::Push_None;

		CharNum++;

        if(lstring_size > CharNum + 7)
        {
            if(tolower(cmpdata[CharNum]) == 'g' && tolower(cmpdata[CharNum + 1]) == 'e' && tolower(cmpdata[CharNum + 2]) == 't')
            {
                CharNum += 3;
                switch(tolower(cmpdata[CharNum]))
                {
                    case 'e'://getenum
                        if(ChkRemBool("enum(\"", 6))
                        {
                            istype = true;
                            type = PushTypes::Push_Enum;
                            break;
                        }
                        else
                        {
                            cout << "Error on line " << line << "\r\n";
                            cout << "Code: " << 0 << "\r\n";
                            cout << "Line: " << GetLineG() << "\r\n";
                            Utils::Throw("Invalid GetEnum Format");
                        }
                    break;
                    case 'l'://getloc
                        if(ChkRemBool("loc(\"", 5))
                         {
                            istype = true;
                            type = PushTypes::Push_Loc;
                            break;
                        }
                        else
                        {
                            cout << "Error on line " << line << "\r\n";
                            cout << "Code: " << 0 << "\r\n";
                            cout << "Line: " << GetLineG() << "\r\n";
                            Utils::Throw("Invalid GetLoc Format");
                        }
                    break;
                    case 'h'://gethash
                        if(ChkRemBool("hash(\"", 6))
                        {
                            istype = true;
                            type = PushTypes::Push_Hash;
                            break;
                        }
                        else
                        {
                            cout << "Error on line " << line << "\r\n";
                            cout << "Code: " << 0 << "\r\n";
                            cout << "Line: " << GetLineG() << "\r\n";
                            Utils::Throw("Invalid GetHash Format");
                        }
                    break;
                }
            }
        }

        uint32_t Starti = CharNum;

        if(istype == false)
        {
            while(CharNum < lstring_size)
            {
                switch(cmpdata[CharNum])
                {
                    case '/':
                        if(CharNum + 1 < lstring_size)
                        {
                            if(cmpdata[CharNum + 1] == '/')
                                goto BreakLoop;
                        }
                    break;
                    case '\r':
                    case '\n':
                    case ' ':
                    goto BreakLoop;

                }
                CharNum++;
            }
        }
        else
        {
            while(CharNum < lstring_size)
            {
                switch(cmpdata[CharNum])
                {
                    case '"':
                    goto BreakLoop;
                    case '\r':
                    case '\n':
                    case ' ':
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Invalid GetHash/GetEnum/GetLoc String Format");
                    break;

                }
                CharNum++;
            }
        }

        BreakLoop:

		uint32_t len = CharNum - Starti;
        char* buffer = new char [len + 1];
        memcpy(buffer, cmpdata + Starti, len);
        buffer[len] = '\0';

        if(istype == true)
        {
            if(lstring_size > CharNum + 2)
            {
                if(!(cmpdata[CharNum] == '"' && cmpdata[CharNum + 1] == ')'))
                {
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Invalid GetHash/GetEnum/GetLoc String Format");
                }
                else CharNum += 2;
            }
            else
            {
                cout << "Error on line " << line << "\r\n";
                Utils::Throw("Index Out Of Bounds");
            }

        }
        //cout << buffer << endl;

        return {buffer, len, type};
    }
    template<typename T> bool FindStaticParams(char* str,ParamTypes type, T* out){
        switch(type)
        {
            case ParamTypes::Frame:
            {
                map<string,uint16_t>::iterator iter = (*gFrameNames).find(string(str));
                if (iter != (*gFrameNames).cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Could Not Find Frame Name");
                }
            }
            break;
            case ParamTypes::Static:
            {
                map<string,uint16_t>::iterator iter = (*gStaticNames).find(string(str));
                if (iter != (*gStaticNames).cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Could Not Find Static Name");
                }
            }
            break;
            case ParamTypes::Native:
            {
                map<string,uint32_t>::iterator iter = (*gNativeNames).find(string(str));
                if (iter != (*gNativeNames).cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Could Not Find Native Name");
                }
            }
            break;
            case ParamTypes::Global:
            {
                map<string,uint32_t>::iterator iter = (*gGlobalNames).find(string(str));
                if (iter != (*gGlobalNames).cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Could Not Find Global Name");
                }
            }
            break;


            default: return false;
        }

        return false;
    }
    template<typename T> T GetParamAsInt(ParamTypes type = ParamTypes::None){
        CharStr str = GetParami();
        char *endp;

        unsigned long int value = strtoul(str.str, &endp, 0);
        if(value > numeric_limits<T>::max())
        {
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Utils::Throw("Opcode Data Out Of Bounds");
        }

        if (endp == str.str) {
            T ret;
            if(FindStaticParams<T>(str.str, type, &ret))
                return ret;

            //failed
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Utils::Throw("String To Int Failed");
        }
        else if (*endp != 0) {
            T retc;
            if(FindStaticParams<T>(str.str, type, &retc))
                return retc;

            //invalid char
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            cout << "Index: " << endp - str.str << "\r\n";
            Utils::Throw("String To Int Failed");
        }
        else {
            return (T)value;
        }
        return (T)0;
    }
    uint32_t GetParamAsInt32WithType(uint32_t OpcodeSize){
        CharStrType str = GetParamiWithEnums();
        char *endp;

        switch(str.type)
        {
            case PushTypes::Push_None:
                {
                unsigned long int value = strtoul(str.str, &endp, 0);

                if (endp == str.str) {
                    //failed
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("String To Int Failed");
                }
                else if (*endp != 0) {
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << "Index: " << endp - str.str << "\r\n";
                    Utils::Throw("String To Int Failed");
                }
                else {
                    return (uint32_t)value;
                }
                }
            break;
            case PushTypes::Push_Enum:
                {
                    map<string,uint32_t>::iterator iter = (*gEnums).find(string(str.str));
                    if (iter != (*gEnums).cend()){
                        return iter->second;
                    }
                    else{
                        cout << "Error on line " << line << "\r\n";
                        cout << "Code: " << 0 << "\r\n";
                        cout << "Line: " << GetLineG() << "\r\n";
                        Utils::Throw("Could Not Find Enum");
                    }
                }
            break;
            case PushTypes::Push_Loc:
                (*(gJumps)).push_back({JumpType::pCall, (*(gtable)).size() + OpcodeSize,LineStart,line,str.str});
                return 0x7FFFFFFF;
            break;
            case PushTypes::Push_Hash:
                return Utils::Joaat(str.str);
            break;
        }

        return 0;
    }
    float GetParamAsFloat(){
        CharStr str = GetParami();
        char* endp;

        if(str.str[0] == 0)
        {
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Utils::Throw("Param Not Found");
        }
        float value;
        if(str.len > 2)
        {
            if(str.str[0] == '0' && tolower(str.str[1]) == 'x')
            {
                uint32_t tmp = strtoul(str.str, &endp, 0);
                value = *(float*)&tmp;
            }
            else value = strtof(str.str, &endp);
        }
        else value = strtof(str.str, &endp);

        if (endp == str.str) {
            //failed
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Utils::Throw("String To Float Failed");
        }
        else if (*endp != 0) {
            //invalid char
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            cout << "Index: " << endp - str.str << "\r\n";
            Utils::Throw("String To Float Failed");
        }
        else {
            return value;
        }
        return 0;
    }
    uint32_t GetParamAsHash(){
        CharStr str = GetParami();
        char* endp;
        if(str.str[0] == 0)
        {
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Utils::Throw("Param Not Found");
        }

        uint32_t value;
        if(str.len > 1 && str.str[0] == '_')
        {
            //custom native
            uint32_t ret;
            if(FindStaticParams<uint32_t>(str.str, ParamTypes::Native, &ret))
                return ret;

        }
        else if(str.len > 7)
        {

            if(tolower(str.str[0]) == 'u' && tolower(str.str[1]) == 'n' && tolower(str.str[2]) == 'k' && str.str[3] == '_' && str.str[4] == '0' && tolower(str.str[5]) == 'x')
            {
                value = strtoul(str.str + 6, &endp, 16);
                if (endp == str.str) {
                    //failed
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Utils::Throw("Unk Hash Parse Failed");
                }
                else if (*endp != 0) {
                    //invalid char
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << "Index: " << endp - str.str << "\r\n";
                    Utils::Throw("Unk Hash Parse Failed");
                }
                else
                    return value;

            }
        }


        return Utils::Joaat(str.str);
    }
    uint32_t GetParamAsIorF(){
        CharStr str = GetParami();
        char* endp;

        if(str.str[0] == 0)
        {
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Utils::Throw("Param Not Found");
        }

        uint32_t value;
        if(tolower(str.str[str.len - 1]) == 'f' || strchr(str.str, '.') != nullptr)
        {
            str.str[str.len - 1] = '\0';
            float tmp = strtof(str.str, &endp);
            value = *(uint32_t*)&tmp;
        }
        else
            value = strtoul(str.str, &endp, 0);

        if (endp == str.str) {
            //failed
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Utils::Throw("String To Int or Float Failed");
        }
        else if (*endp != 0) {
            //invalid char
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            cout << "Index: " << endp - str.str << "\r\n";
            Utils::Throw("String To Int or Float Failed");
        }
        else {
            return value;
        }
        return 0;
    }
    void GetSwitchParams(){

        //switch [1337 @MyLabel]:[1338 @NextLabel]
        vector<uint8_t> TempTable;
        uint32_t ssize = (*gtable).size();

        TempTable.push_back(OpCode::Switch);
        TempTable.push_back(0);//len = index 0

        uint32_t SwitchCount = 0;
        bool switchended;
		CharNum++;
		uint32_t Starti = CharNum;

        while(CharNum < lstring_size)
        {
            switch(cmpdata[CharNum])
            {
                case '[':
                    {
                    //get case value
                    SwitchCount++;
                    uint32_t value = GetParamAsInt32WithType(TempTable.size());

                    TempTable.push_back(*(((uint8_t*)&value) + 3));
                    TempTable.push_back(*(((uint8_t*)&value) + 2));
                    TempTable.push_back(*(((uint8_t*)&value) + 1));
                    TempTable.push_back(*(uint8_t*)&value);
                    }
                    break;
                case '@':
                    //get label value
                    (*gJumps).push_back({JumpType::Switch, ssize + TempTable.size(),LineStart, line, GetParamAsLabel(false)});
                    TempTable.push_back(OpCode::Nop);
                    TempTable.push_back(OpCode::Nop);
                    continue;
                case ']':
                    //end switch case
                    if(CharNum + 1 < lstring_size)
                    {
                        if(cmpdata[CharNum + 1] == ':')
                        {
                            //continue switch cases
                            CharNum++;
                            break;
                        }
                        else
                        {
                            switchended = true;
                            if(SwitchCount > 255)
                            {
                                cout << "Error on line " << line << "\r\n";
                                cout << "Code: " << 0 << "\r\n";
                                cout << "Line: " << GetLineG() << "\r\n";
                                cout << "Count: " << SwitchCount << "\r\n";
                                Utils::Throw("Switch Count Too Large");
                            }
                            TempTable[1] = (uint8_t)SwitchCount;
                        }
                    }
                    break;
                case '/':
                    if(CharNum + 1 < lstring_size)
                    {
                        if(cmpdata[CharNum + 1] == '/')
                        {
                            if(switchended)
                            {

                                uint32_t amount = (ssize + (SwitchCount * 6)) % 16384;
                                if(amount < ssize % 16384)
                                {
                                    //code page has been passed
                                    if(amount == 0)
                                    {
                                        (*gtable).resize(ssize + TempTable.size());
                                        memcpy((*gtable).data() + ssize, TempTable.data(), TempTable.size());
                                        return;
                                    }

                                    uint32_t rem = (16384 - (ssize % 16384));
                                    for(uint32_t i = 0; i < rem; i++)
                                    {
                                        (*gtable).push_back(OpCode::Nop);
                                    }

                                }

                                (*gtable).resize(ssize + TempTable.size());
                                memcpy((*gtable).data() + ssize, TempTable.data(), TempTable.size());
                                return;
                            }
                            else
                            {
                                cout << "Error on line " << line << "\r\n";
                                cout << "Code: " << 0 << "\r\n";
                                cout << "Line: " << GetLineG() << "\r\n";
                                Utils::Throw("Invalid Switch Format");
                            }
                        }
                    }
                break;
                case '\r':
                case '\n':
                    if(switchended)
                    {

                        uint32_t amount = (ssize + (SwitchCount * 6)) % 16384;
                        if(amount < ssize % 16384)
                        {
                            //code page has been passed
                            if(amount == 0)
                            {
                                (*gtable).resize(ssize + TempTable.size());
                                memcpy((*gtable).data() + ssize, TempTable.data(), TempTable.size());
                                return;
                            }

                            uint32_t rem = (16384 - (ssize % 16384));
                            for(uint32_t i = 0; i < rem; i++)
                            {
                                (*gtable).push_back(OpCode::Nop);
                            }

                        }

                        (*gtable).resize(ssize + TempTable.size());
                        memcpy((*gtable).data() + ssize, TempTable.data(), TempTable.size());
                        return;
                    }
                    else
                    {
                        cout << "Error on line " << line << "\r\n";
                        cout << "Code: " << 0 << "\r\n";
                        cout << "Line: " << GetLineG() << "\r\n";
                        Utils::Throw("Invalid Switch Format");
                    }
                break;


            }
			CharNum++;
        }

        cout << "Error on line " << line << "\r\n";
        cout << "Code: " << 0 << "\r\n";
        cout << "Line: " << GetLineG() << "\r\n";
        Utils::Throw("Invalid Switch Format");
    }
    bool GetLabelLoc(uint32_t * out,string& str, uint32_t pos){
        map<string,uint32_t>::iterator iter = (*gLabelLocations).find(str);
        if (iter != (*gLabelLocations).cend()){
            *out = iter->second;
            return true;
        }
        else{
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineGAtPos(pos) << "\r\n";
            Utils::Throw("Could Not Find Label");
        }
        return false;
    }

//}

void XSC::CompileXSC(string& data, int pgBase, char* scriptName, bool ignoreNops, uint32_t paramcount)
{
    Header.ScriptName = scriptName;
    Header.PgBase = pgBase;
    Header.Unk2 = 0x11CD39A2;
    Header.ParameterCount = paramcount;

    vector<uint8_t> table;
    uint32_t SavedTableSize = 0;
    vector<StrIndex> StringTablePtrs;
    vector<uint8_t> stringtable;

    vector<SavedJumps> Jumps;
    map<string, uint32_t> LabelLocations;
    map<string, uint32_t> enums;
    map<string, uint16_t> FrameNames;
    map<string, uint16_t> StaticNames;
    map<string, uint32_t> NativeNames;
    map<string, uint32_t> GlobalNames;
    gLabelLocations = &LabelLocations;
    gEnums = &enums;
    gFrameNames = &FrameNames;
    gStaticNames = &StaticNames;
    gNativeNames = &NativeNames;
    gGlobalNames = &GlobalNames;
    gtable = &table;
    gJumps = &Jumps;
    vector<uint32_t> natives;
    bool lastLineWasLabel = false, alreadySetStaticsCount = false;

    LineStart = 0;
    line = 1;
    lstring_size = data.length();
    string_size = data.length() - 1;
    CharNum = 0;
    cmpdata = data.data();

    //{ delegates
	//push might have to swap endian
    auto PushInt16 = [&](auto var)
    {
        uint8_t* ptr = (uint8_t*)&var;
        table.push_back(*(ptr + 1));
        table.push_back(*(ptr));
    };
	auto PushInt24 = [&](auto var)
    {
		if(var > 16777215)
			var = 16777215;
        uint8_t* ptr = (uint8_t*)&var;
        table.push_back(*(ptr + 2));
        table.push_back(*(ptr + 1));
        table.push_back(*ptr);
    };
    auto PushInt32 = [&](auto var)
    {
        uint8_t* ptr = (uint8_t*)&var;
        table.push_back(*(ptr + 3));
        table.push_back(*(ptr + 2));
        table.push_back(*(ptr + 1));
        table.push_back(*ptr);
    };
    auto GetLine = [&]()
    {
		uint32_t i;
        for(i = LineStart; i < lstring_size; i++)
        {
            if(data[i] == '\r' || data[i] == '\n' )
                return data.substr(LineStart, i - LineStart);
        }
		return data.substr(LineStart, i - LineStart - 1);
    };
    auto GetParam = [&]()
    {
		CharNum++;
		uint32_t Starti = CharNum;
        while(CharNum < lstring_size)
        {
            if(data[CharNum] == '\r' || data[CharNum] == '\n' || data[CharNum] == ' ')
                return data.substr(Starti, CharNum - Starti);
			CharNum++;
        }
		return data.substr(Starti, CharNum - Starti - 1);
    };
    auto Fix16384 = [&](auto OpcodeLen)
    {
        uint32_t amount = (table.size() + OpcodeLen) % 16384;
		if(amount < table.size() % 16384)
        {
            //code page has been passed
            if(amount == 0)
                return;

            uint32_t rem = (16384 - (table.size() % 16384));
            table.resize(table.size() + rem);

//            old code
//            for(uint32_t i = 0; i < rem; i++)
//            {
//                table.push_back(OpCode::Nop);
//            }

        }
    };
    //}

    while (CharNum < lstring_size)
    {
        switch(tolower(data[CharNum]))
        {
            case 'p'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'u':
                        if(CharNum + 3 > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum + 1]) == 's' && tolower(data[CharNum + 2]) == 'h'))
                        {
                            UnkOpcodeError();
                        }
                        CharNum += 3;
                        switch(tolower(data[CharNum]))
                        {
                            case 's':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Utils::Throw("Param Not Found");
                                        break;
                                    case ' '://pushs
                                        //parse param
                                        {
                                            int16_t value = GetParamAsInt<int16_t>();

                                            if(value >= -1 && value <= 7)
                                            {
                                                table.push_back(value + 110);
                                            }
                                            else if(value >= 8 && value <= 255)
                                            {
                                                Fix16384(PushB_L);
                                                table.push_back(OpCode::PushB);
                                                table.push_back((uint8_t)value);
                                            }
                                            else
                                            {
                                                Fix16384(PushS_L);
                                                table.push_back(OpCode::PushS);
                                                PushInt16(value);
                                            }
                                        }
										break;
                                    case 't'://pushstring will have to check ring
                                        {
                                        ChkRem("ring", 4, true);
                                        //parse param

                                        string tempstr = GetParamString();
                                        uint32_t len = tempstr.length();
                                        uint32_t strpos = 0;
                                        uint32_t pos = stringtable.size();

                                        //if string is in table
                                        for(uint32_t i = 0; i < StringTablePtrs.size(); i++)
                                        {
                                            char* str = (char*)(stringtable.data() + StringTablePtrs[i].index);
                                            if(StringTablePtrs[i].len == len)
                                            {
                                                if(strcmp(str, tempstr.c_str()) == 0)
                                                {
                                                    //match
                                                    strpos = StringTablePtrs[i].index;
                                                    goto StringAlreadyExists;
                                                }
                                            }
                                        }

                                        //else check size

                                        if((pos + len + 1) % 16384 < pos % 16384)
                                        {
                                            //cout << "HIT!!!\n";
                                            stringtable.resize(16384 - (pos % 16384) + pos);
                                        }

                                        //add string to table
                                        {
                                        strpos = stringtable.size();

                                        StringTablePtrs.push_back({strpos, len});
                                        stringtable.resize(strpos + len + 1);
                                        //cout << stringtable.size() << endl;

                                        memcpy(stringtable.data() + strpos, tempstr.c_str(),len + 1);
                                        //cin.ignore();
                                        }
                                        StringAlreadyExists:

                                        if(strpos < 7)
                                        {
                                           table.push_back(strpos + 110);
                                        }
                                        else if(strpos < 256)
                                        {
                                            Fix16384(PushB_L);
                                            table.push_back(OpCode::PushB);
                                            table.push_back((uint8_t)strpos);
                                        }
                                        else if(strpos < 32768)
                                        {
                                            Fix16384(PushS_L);
                                            table.push_back(OpCode::PushS);
                                            PushInt16((int16_t)strpos);
                                        }
                                        else if(strpos < 16777216)
                                        {
                                            Fix16384(PushI24_L);
                                            table.push_back(OpCode::PushI24);
                                            PushInt24(strpos);
                                        }
                                        else
                                        {
                                            Fix16384(Push_L);
                                            table.push_back(OpCode::Push);
                                            PushInt32(strpos);
                                        }

                                        table.push_back(OpCode::PushString);
                                        }
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                            break;
                            case '_':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '-'://push_-1 will have to check 1
                                        ChkRem("1", 1);
										//append code
										table.push_back(OpCode::Push_Neg1);
                                        break;
                                    case 'n'://push_neg1 will have to check eg1
                                        ChkRem("eg1", 3);
                                        //append code
										table.push_back(OpCode::Push_Neg1);
                                        break;
                                    case '0'://push_0
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_0);
                                        break;
                                    case '1'://push_1
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_1);
                                        break;
                                    case '2'://push_2
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_2);
                                        break;
                                    case '3'://push_3
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_3);
                                        break;
                                    case '4'://push_4
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_4);
                                        break;
                                    case '5'://push_5
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_5);
                                        break;
                                    case '6'://push_6
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_6);
                                        break;
                                    case '7'://push_7
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::Push_7);
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;

                                }
                            break;
                            case '\r':
                            case '\n':
                                cout << "Error on line " << line << "\r\n";
                                cout << "Code: " << 0 << "\r\n";
                                cout << "Line: " << GetLineG() << "\r\n";
                                Utils::Throw("Param Not Found");
                                break;
                            case ' '://push
                                {
                                    int32_t value = GetParamAsInt32WithType(1);

                                    //getenum
                                    //getloc
                                    //gethash

                                    if(value >= -1 && value <= 7)
                                    {
                                        table.push_back(value + 110);
                                    }
                                    else if(value < -1)//push getloc rets 0//might change
                                    {
                                        if(value >= -32768)
                                        {
                                            Fix16384(PushS_L);
                                            table.push_back(OpCode::PushS);
                                            PushInt16((int16_t)value);
                                        }
                                        else
                                        {
                                            Fix16384(Push_L);
                                            table.push_back(OpCode::Push);
                                            PushInt32(value);
                                        }
                                    }
                                    else if(value < 256)
                                    {
                                        Fix16384(PushB_L);
                                        table.push_back(OpCode::PushB);
                                        table.push_back((uint8_t)value);
                                    }
                                    else if(value < 32768)
                                    {
                                        Fix16384(PushS_L);
                                        table.push_back(OpCode::PushS);
                                        PushInt16((int16_t)value);
                                    }
                                    else if(value < 16777216)
                                    {
                                        Fix16384(PushI24_L);
                                        table.push_back(OpCode::PushI24);
                                        PushInt24(value);
                                    }
                                    else
                                    {
                                        Fix16384(Push_L);
                                        table.push_back(OpCode::Push);
                                        PushInt32(value);
                                    }

                                    break;
                                }
                                break;
                            case 'b':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Utils::Throw("Param Not Found");
                                        break;
                                    case ' '://pushb
                                        //parse param
                                        {
                                            uint8_t value = GetParamAsInt<uint8_t>();

                                            if(value <= 7)
                                            {
                                                table.push_back(value + 110);
                                            }
                                            else
                                            {
                                                Fix16384(PushB_L);
                                                table.push_back(OpCode::PushB);
                                                table.push_back(value);
                                            }
                                        }
                                        break;
                                    case '2'://pushb2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(PushB2_L);
                                        table.push_back(OpCode::PushB2);
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        break;
                                    case '3'://pushb3
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(PushB3_L);
                                        table.push_back(OpCode::PushB3);
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                                break;
                            case 'f':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Utils::Throw("Param Not Found");
                                        break;
                                    case ' '://pushf
                                    {
                                        //parse param

                                        float value = GetParamAsFloat();

                                        switch(*(uint32_t*)&value)
                                        {
                                            case 3212836864:
                                                table.push_back(OpCode::PushF_Neg1);
                                            goto EndPushFloat;
                                            case 0:
                                                table.push_back(OpCode::PushF_0);
                                            goto EndPushFloat;
                                            case 1065353216:
                                                table.push_back(OpCode::PushF_1);
                                            goto EndPushFloat;
                                            case 1073741824:
                                                table.push_back(OpCode::PushF_2);
                                            goto EndPushFloat;
                                            case 1077936128:
                                                table.push_back(OpCode::PushF_3);
                                            goto EndPushFloat;
                                            case 1082130432:
                                                table.push_back(OpCode::PushF_4);
                                            goto EndPushFloat;
                                            case 1084227584:
                                                table.push_back(OpCode::PushF_5);
                                            goto EndPushFloat;
                                            case 1086324736:
                                                table.push_back(OpCode::PushF_6);
                                            goto EndPushFloat;
                                            case 1088421888:
                                                table.push_back(OpCode::PushF_7);
                                            goto EndPushFloat;
                                        }

                                        Fix16384(PushF_L);
                                        table.push_back(OpCode::PushF);
                                        PushInt32(value);
                                        EndPushFloat:
                                        break;

                                    }
                                        break;
                                    case '_':
                                        CharNum++;
                                        if(CharNum > string_size)
                                        {
                                            cout << "Error on line " << line << "\r\n";
                                            Utils::Throw("Index Out Of Bounds");
                                        }
                                        switch(tolower(data[CharNum]))
                                        {
                                            case '-'://pushf_-1 will have to check 1
                                                ChkRem("1", 1);
                                                //append code
												table.push_back(OpCode::PushF_Neg1);
                                                break;
                                            case 'n'://pushf_neg1 will have to check eg1
                                                ChkRem("eg1", 3);
                                                //append code
												table.push_back(OpCode::PushF_Neg1);
                                                break;
                                            case '0'://pushf_0
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_0);
                                                break;
                                            case '1'://pushf_1
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_1);
                                                break;
                                            case '2'://pushf_2
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_2);
                                                break;
                                            case '3'://pushf_3
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_3);
                                                break;
                                            case '4'://pushf_4
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_4);
                                                break;
                                            case '5'://pushf_5
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_5);
                                                break;
                                            case '6'://pushf_6
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_6);
                                                break;
                                            case '7'://pushf_7
                                                ChkRem();
                                                //append code
												table.push_back(OpCode::PushF_7);
                                                break;
                                            default:
                                                UnkOpcodeError();
                                            break;

                                        }
                                    break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }

                                break;
                            case 'i'://pushi24 will need to check 24
                                ChkRem("24", 2, true);
                                //parse param
                                {
                                    uint32_t value = GetParamAsInt<uint32_t>();

                                    if(value <= 7)
                                    {
                                        table.push_back(value + 110);
                                    }
                                    else if(value < 256)
                                    {
                                        Fix16384(PushB_L);
                                        table.push_back(OpCode::PushB);
                                        table.push_back((uint8_t)value);
                                    }
                                    else if (value < 32768)
                                    {
                                        Fix16384(PushS_L);
                                        table.push_back(OpCode::PushS);
                                        PushInt16(value);
                                    }
                                    else
                                    {
                                        Fix16384(PushI24_L);
                                        table.push_back(OpCode::PushI24);
                                        PushInt24(value);
                                    }
                                }
                                break;
                            default:
                                UnkOpcodeError();

                        }
                        break;
                    case 'c'://pcall will need to check all
                        ChkRem("all", 3);
                        //append code
						table.push_back(OpCode::pCall);
                        break;
                    case 'g'://pget will need to check et
                        ChkRem("et", 2);
                        //append code
						table.push_back(OpCode::pGet);
                        break;
                    case 'p'://ppeekset will need to check eekset
                        ChkRem("eekset", 6);
                        //append code
						table.push_back(OpCode::pPeekSet);
                        break;
                    case 's'://pset will need to check et
                        ChkRem("et", 2);
                        //append code
						table.push_back(OpCode::pSet);
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case 'c'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'a':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'l':
                                CharNum+=2;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                if(tolower(data[CharNum - 1]) != 'l')
                                {
                                    UnkOpcodeError();
                                }

                                switch(tolower(data[CharNum]))
                                {
                                    case 'n'://callnative will have to check ative
                                    {
                                        ChkRem("ative", 5, true);
                                        //parse param
                                        Fix16384(CallNative_L);
                                        uint32_t Hash = GetParamAsHash();
                                        uint16_t index = 0;
                                        std::vector<uint32_t>::iterator loc = find(natives.begin(), natives.end(), Hash);
                                        if (loc == natives.end())
                                        {
                                            index = natives.size();
                                            natives.push_back(Hash);
                                        }
                                        else index = loc - natives.begin();

                                        table.push_back(OpCode::CallNative);
                                        uint8_t b1 = GetParamAsInt<uint8_t>();
                                        uint8_t b2 = GetParamAsInt<uint8_t>();
                                        table.push_back(((b1 << 2) | (b2 & 0x3)));
                                        PushInt16(index);
                                    }
                                    break;
                                    case ' '://call
                                        //parse param
                                        Fix16384(Call_L);
                                        table.push_back(OpCode::Call);
                                        CharNum++;
                                        Jumps.push_back({JumpType::Call, table.size(),LineStart,line,GetParamAsLabel(false)});
                                        table.push_back(OpCode::Nop);
                                        table.push_back(OpCode::Nop);
                                        table.push_back(OpCode::Nop);
                                        break;
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Utils::Throw("Param Not Found");
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                            break;
                            case 't'://catch will have to check ch
                                ChkRem("ch", 2);
                                //append code
								table.push_back(OpCode::Catch);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'm':
                        CharNum+=2;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum - 1]) != 'p')
                        {
                            UnkOpcodeError();
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'e'://cmpeq will have to check q
                                ChkRem("q", 1);
                                //append code
								table.push_back(OpCode::CmpEQ);
                                break;
                            case 'n'://cmpne will have to check e
                                ChkRem("e", 1);
                                //append code
								table.push_back(OpCode::CmpNE);
                                break;
                            case 'g':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://cmpge
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::CmpGE);
                                        break;
                                    case 't'://cmpgt
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::CmpGT);
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }

                                break;
                            case 'l':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://cmple
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::CmpLE);
                                        break;
                                    case 't'://cmplt
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::CmpLT);
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }

                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                    break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case '/'://{
                if(CharNum + 1 > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                if(tolower(data[CharNum + 1]) == '/')
                {
                    CharNum++;
                    while(CharNum < string_size)
                    {
                        if(data[CharNum] == '\n')
                        {
                            lastLineWasLabel = false;
                            line++;
                            CharNum ++;
                            LineStart = CharNum;
                            SavedTableSize = table.size();
                            break;
                        }
                        CharNum++;
                    }
                }

                //}
                break;
            case 'g'://{
                CharNum+=3;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                if(!(tolower(data[CharNum - 2]) == 'e' && tolower(data[CharNum - 1]) == 't'))
                {
                    UnkOpcodeError();
                }
                switch(tolower(data[CharNum]))
                {
                    case 'a':
                        CharNum+=5;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum - 4]) == 'r' && tolower(data[CharNum - 3]) == 'r' && tolower(data[CharNum - 2]) == 'a' && tolower(data[CharNum - 1]) == 'y'))
                        {
                            UnkOpcodeError();
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case '1'://getarray1
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetArray1_L);
								table.push_back(OpCode::GetArray1);
								table.push_back(GetParamAsInt<uint8_t>());
                                break;
                            case '2'://getarray2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetArray2_L);
								table.push_back(OpCode::GetArray2);
								PushInt16(GetParamAsInt<uint16_t>());
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '1'://getarrayp1
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetArrayP1_L);
										table.push_back(OpCode::GetArrayP1);
										table.push_back(GetParamAsInt<uint8_t>());
                                        break;
                                    case '2'://getarrayp2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetArrayP2_L);
										table.push_back(OpCode::GetArrayP2);
										PushInt16(GetParamAsInt<uint16_t>());
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'f':
                        CharNum+=5;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum - 4]) == 'r' && tolower(data[CharNum - 3]) == 'a' && tolower(data[CharNum - 2]) == 'm' && tolower(data[CharNum - 1]) == 'e'))
                        {
                            UnkOpcodeError();
                        }

                        switch(tolower(data[CharNum]))
                        {
                            case '1'://getframe1
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetFrame1_L);
								table.push_back(OpCode::GetFrame1);
								table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Frame));
                                break;
                            case '2'://getframe2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetFrame2_L);
								table.push_back(OpCode::GetFrame2);
								PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Frame));
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '1'://getframep1
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetFrameP1_L);
										table.push_back(OpCode::GetFrameP1);
										table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Frame));
                                        break;
                                    case '2'://getframep2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetFrameP2_L);
										table.push_back(OpCode::GetFrameP2);
										PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Frame));
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'g':
                        CharNum+=6;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum - 5]) == 'l' && tolower(data[CharNum - 4]) == 'o' && tolower(data[CharNum - 3]) == 'b' && tolower(data[CharNum - 2]) == 'a' && tolower(data[CharNum - 1]) == 'l'))
                        {
                            UnkOpcodeError();
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case '2'://getglobal2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetGlobal2_L);
								table.push_back(OpCode::GetGlobal2);
								PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Global));
                                break;
                            case '3'://getglobal3
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetGlobal3_L);
								table.push_back(OpCode::GetGlobal3);
                                PushInt24(GetParamAsInt<uint32_t>(ParamTypes::Global));
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '2'://getglobalp2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetGlobalP2_L);
										table.push_back(OpCode::GetGlobalP2);
										PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Global));
                                        break;
                                    case '3'://getglobalp3
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetGlobalP3_L);
										table.push_back(OpCode::GetGlobalP3);
										PushInt24(GetParamAsInt<uint32_t>(ParamTypes::Global));
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                        case 'h'://gethash will need to check ash
                        ChkRem("ash", 3);
                        //append code
						table.push_back(OpCode::GetHash);
                        break;
                        case 'i':
                        CharNum+=3;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum - 2]) == 'm' && tolower(data[CharNum - 1]) == 'm'))
                        {
                            UnkOpcodeError();
                        }

                        switch(tolower(data[CharNum]))
                        {
                            case '1'://getimm1
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetImm1_L);
								table.push_back(OpCode::GetImm1);
								table.push_back(GetParamAsInt<uint8_t>());
                                break;
                            case '2'://getimm2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetImm2_L);
								table.push_back(OpCode::GetImm2);
								PushInt16(GetParamAsInt<uint16_t>());
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    goto getimmp;
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '\n':
                                    case ' '://getimmp
                                    case '\r':
                                        getimmp:
                                        //append code
										table.push_back(OpCode::GetImmP);
                                        break;
                                    case '/':
                                    if(CharNum + 1 < string_size)
                                    {
                                        if(data[CharNum + 1] == '/')
                                        {
                                            table.push_back(OpCode::GetImmP);
                                            continue;
                                        }
                                    }
                                    break;
                                    case '1'://getimmp1
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetImmP1_L);
										table.push_back(OpCode::GetImmP1);
										table.push_back(GetParamAsInt<uint8_t>());
                                        break;
                                    case '2'://getimmp2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetImmP2_L);
										table.push_back(OpCode::GetImmP2);
										PushInt16(GetParamAsInt<uint16_t>());
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                        case 's':
                        CharNum+=6;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum - 5]) == 't' && tolower(data[CharNum - 4]) == 'a' && tolower(data[CharNum - 3]) == 't' && tolower(data[CharNum - 2]) == 'i' && tolower(data[CharNum - 1]) == 'c'))
                        {
                            UnkOpcodeError();
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case '1'://getstatic1
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetStatic1_L);
								table.push_back(OpCode::GetStatic1);
								table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Static));
                                break;
                            case '2'://getstatic2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetStatic2_L);
								table.push_back(OpCode::GetStatic2);
								PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Static));
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '1'://getstaticp1
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetStaticP1_L);
										table.push_back(OpCode::GetStaticP1);
										table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Static));
                                        break;
                                    case '2'://getstaticp2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetStaticP2_L);
										table.push_back(OpCode::GetStaticP2);
										PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Static));
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case '\n': line++; CharNum++; LineStart = CharNum; SavedTableSize = table.size(); lastLineWasLabel = false; break;
            case ':':{
                if(lastLineWasLabel)
                    table.push_back(OpCode::Nop);
                CharNum++;
                string labelName = GetParamAsLabel(true);

                if (LabelLocations.count(labelName) == 0)
                        LabelLocations.insert({labelName, table.size()});
                else
                {
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLine() << "\r\n";
                    cout << "Label: " << labelName << "\r\n";

                    Utils::Throw("Label already exists");
                }
                lastLineWasLabel = true;
                }
                break;
            case 's'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'e':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum]) == 't')
                        {
                            CharNum++;
                            if(CharNum > string_size)
                            {
                                cout << "Error on line " << line << "\r\n";
                                Utils::Throw("Index Out Of Bounds");
                            }
                            switch(tolower(data[CharNum]))
                            {
                                case 'a':
                                    CharNum+=5;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Utils::Throw("Index Out Of Bounds");
                                    }
                                    if(!(tolower(data[CharNum - 4]) == 'r' && tolower(data[CharNum - 3]) == 'r' && tolower(data[CharNum - 2]) == 'a' && tolower(data[CharNum - 1]) == 'y'))
                                    {
                                        UnkOpcodeError();
                                    }
                                    switch(tolower(data[CharNum]))
                                    {
                                        case '1'://setarray1
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetArray1_L);
											table.push_back(OpCode::SetArray1);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case '2'://setarray2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetArray2_L);
											table.push_back(OpCode::SetArray2);
											PushInt16(GetParamAsInt<uint16_t>());
                                            break;
                                        default:
                                            UnkOpcodeError();
                                        break;
                                    }
                                    break;
                                case 'f':
                                    CharNum+=5;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Utils::Throw("Index Out Of Bounds");
                                    }
                                    if(!(tolower(data[CharNum - 4]) == 'r' && tolower(data[CharNum - 3]) == 'a' && tolower(data[CharNum - 2]) == 'm' && tolower(data[CharNum - 1]) == 'e'))
                                    {
                                        UnkOpcodeError();
                                    }
                                    switch(tolower(data[CharNum]))
                                    {
                                        case '1'://setframe1
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetFrame1_L);
											table.push_back(OpCode::SetFrame1);
											table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Frame));
                                            break;
                                        case '2'://setframe2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetFrame2_L);
											table.push_back(OpCode::SetFrame2);
											PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Frame));
                                            break;
                                        case 'n'://setframename will need to check ame
                                            {
                                            ChkRem("ame",3,true);
                                            //parse param
                                            uint16_t value = GetParamAsInt<uint16_t>();
                                            string str = GetParams();

                                            if (FrameNames.find(str) == FrameNames.end())
                                                FrameNames.insert({str, value});
                                            }
                                            break;
                                        default:
                                            UnkOpcodeError();
                                        break;
                                    }
                                    break;
                                case 'g':
                                    CharNum+=6;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Utils::Throw("Index Out Of Bounds");
                                    }
                                    if(!(tolower(data[CharNum - 5]) == 'l' && tolower(data[CharNum - 4]) == 'o' && tolower(data[CharNum - 3]) == 'b' && tolower(data[CharNum - 2]) == 'a' && tolower(data[CharNum - 1]) == 'l'))
                                    {
                                        UnkOpcodeError();
                                    }
                                    switch(tolower(data[CharNum]))
                                    {
                                        case '2'://setglobal2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetGlobal2_L);
											table.push_back(OpCode::SetGlobal2);
											PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Global));
                                            break;
                                        case '3'://setglobal3
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetGlobal3_L);
											table.push_back(OpCode::SetGlobal3);
											PushInt24(GetParamAsInt<uint32_t>(ParamTypes::Global));
                                            break;
                                        case 'n'://setglobalname wiil need check ame
                                            {
                                            ChkRem("ame",3,true);
                                            //parse param
                                            uint32_t value = GetParamAsInt<uint32_t>();
                                            string str = GetParams();

                                            if(!(value >= 0 && value <= 16777215))
                                            {
                                                cout << "Error on line " << line << "\r\n";
                                                cout << "Code: " << 0 << "\r\n";
                                                cout << "Line: " << GetLineG() << "\r\n";
                                                cout << "Index: " << value << "\r\n";
                                                Utils::Throw("Global Index Out Of Bounds");
                                            }

                                             if (GlobalNames.count(str) == 0)
                                                GlobalNames.insert({str, value});
                                            }

                                            break;
                                        case 's'://setglobalsversion will need to check version
                                            ChkRem("version",7,true);
                                            //parse param
                                            Header.Unk2 = GetParamAsInt<uint32_t>();
                                            break;
                                        default:
                                            UnkOpcodeError();
                                        break;
                                    }
                                    break;
                                    case 'i':
                                    CharNum+=3;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Utils::Throw("Index Out Of Bounds");
                                    }
                                    if(!(tolower(data[CharNum - 2]) == 'm' && tolower(data[CharNum - 1]) == 'm'))
                                    {
                                        UnkOpcodeError();
                                    }

                                    switch(tolower(data[CharNum]))
                                    {
                                        case '1'://setimm1
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetImm1_L);
											table.push_back(OpCode::SetImm1);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case '2'://setimm2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetImm2_L);
											table.push_back(OpCode::SetImm2);
											PushInt16(GetParamAsInt<uint16_t>());
                                            break;
                                        default:
                                            UnkOpcodeError();
                                        break;
                                    }
                                    break;
                                    case 's':
                                    CharNum+=6;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Utils::Throw("Index Out Of Bounds");
                                    }
                                    if(!(tolower(data[CharNum - 5]) == 't' && tolower(data[CharNum - 4]) == 'a' && tolower(data[CharNum - 3]) == 't' && tolower(data[CharNum - 2]) == 'i' && tolower(data[CharNum - 1]) == 'c'))
                                    {
                                        UnkOpcodeError();
                                    }
                                    switch(tolower(data[CharNum]))
                                    {
                                        case '1'://setstatic1

                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetStatic1_L);
											table.push_back(OpCode::SetStatic1);
											table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Static));
                                            break;
                                        case '2'://setstatic2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetStatic2_L);
											table.push_back(OpCode::SetStatic2);
											PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Static));
                                            break;
                                        case 'n'://setstaticname will need to check ame
                                            {
                                            ChkRem("ame",3,true);
                                            //parse param
                                            uint32_t value = GetParamAsInt<uint16_t>();
                                            string str = GetParams();

                                             if (StaticNames.count(str) == 0)
                                                StaticNames.insert({str, value});
                                            }
                                            break;
                                        case 's'://setstaticscount will need to check count
                                            ChkRem("count",5,true);
                                            //parse param
                                            if(!alreadySetStaticsCount)
                                            {
                                                alreadySetStaticsCount = true;
                                                Header.Statics.resize(GetParamAsInt<uint16_t>());
                                            }
                                            else
                                            {
                                                cout << "Error on line " << line << "\r\n";
                                                cout << "Code: " << 0 << "\r\n";
                                                cout << "Line: " << GetLineG() << "\r\n";
                                                Utils::Throw("Statics Count Already Set");
                                            }
                                            break;
                                        default:
                                            UnkOpcodeError();
                                        break;
                                    }
                                    break;
                                    case 'd'://setdefaultstatic will need to check efaultstatic
                                        {
                                            ChkRem("efaultstatic",12,true);
                                            //parse param

                                            uint32_t staticIndex = GetParamAsInt<uint32_t>();
                                            uint32_t staticValue = GetParamAsIorF();


                                            if(staticIndex < Header.Statics.size())
                                                Header.Statics[staticIndex] = staticValue;
                                            else
                                            {
                                                cout << "Error on line " << line << "\r\n";
                                                cout << "Code: " << 0 << "\r\n";
                                                cout << "Line: " << GetLineG() << "\r\n";
                                                Utils::Throw("Static Index Out Of Bounds");
                                            }
                                        }
                                        break;
                                    case 'e'://setenum will need to check num
                                        {
                                            ChkRem("num",3,true);
                                            //parse param
                                            string str = GetParams();
                                            uint32_t value = GetParamAsIorF();
                                             if (enums.count(str) == 0)
                                                enums.insert({str, value});
                                        }
                                        break;
                                    case 'n'://setnativename will need to check ativename
                                        {
                                        ChkRem("ativename",9,true);
                                        //parse param
                                        uint32_t value = GetParamAsInt<uint32_t>();
                                        string str = GetParams();

                                        if(str[0] != '_')
                                        {
                                            cout << "Error on line " << line << "\r\n";
                                            cout << "Code: " << 0 << "\r\n";
                                            cout << "Line: " << GetLineG() << "\r\n";
                                            Utils::Throw("Custom Native Names Must Start With _");
                                        }
                                        else if (NativeNames.count(str) == 0)
                                            NativeNames.insert({str, value});

                                        }
                                        break;
                                    case 'p'://setpagebase will need to check agebase
                                        ChkRem("agebase",7,true);
                                        //parse param
                                        Header.PgBase = GetParamAsInt<uint32_t>();
                                        break;
                                default:
                                    UnkOpcodeError();
                                break;
                            }
                        }
                        else
                        {
                            UnkOpcodeError();
                        }
                    break;
                    case 't':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum]) == 'r')
                        {
                            CharNum++;
                            if(CharNum > string_size)
                            {
                                cout << "Error on line " << line << "\r\n";
                                Utils::Throw("Index Out Of Bounds");
                            }
                            switch(tolower(data[CharNum]))
                            {
                                case 'a':
                                    CharNum+=3;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Utils::Throw("Index Out Of Bounds");
                                    }
                                    switch(tolower(data[CharNum]))
                                    {
                                        case 'i'://straddi
                                            ChkRem(nullptr,0,true);

                                            //parse param
                                            Fix16384(StrAddI_L);
											table.push_back(OpCode::StrAddI);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case ' '://stradd
                                            //parse param
                                            Fix16384(StrAdd_L);
											table.push_back(OpCode::StrAdd);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case '\r':
                                        case '\n':
                                            cout << "Error on line " << line << "\r\n";
                                            cout << "Code: " << 0 << "\r\n";
                                            cout << "Line: " << GetLineG() << "\r\n";
                                            Utils::Throw("Param Not Found");
                                            break;
                                        default:
                                            UnkOpcodeError();
                                        break;

                                    }
                                    break;
                                case 'c'://strcopy will need to check opy
                                    ChkRem("opy",3,true);
                                    //parse param
                                    Fix16384(StrCopy_L);
									table.push_back(OpCode::StrCopy);
									table.push_back(GetParamAsInt<uint8_t>());
                                    break;
                                default:
                                    UnkOpcodeError();
                                break;
                            }

                        }
                        else
                        {
                            UnkOpcodeError();
                        }
                    break;
                    case 'u'://sub will need to check b
                        ChkRem("b",1,false);

                        //append code
						table.push_back(OpCode::Sub);
                        break;
                    case 'w'://switch will need to check itch
						ChkRem("itch",4,true);
                        //parse param
                        GetSwitchParams();
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }


            //}
                break;
            case 'j'://{
                CharNum+=4;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                if(!(tolower(data[CharNum - 3]) == 'u' && tolower(data[CharNum - 2]) == 'm' && tolower(data[CharNum - 1]) == 'p'))
                {
                    UnkOpcodeError();
                }
                switch(tolower(data[CharNum]))
                {
                    case '\r':
                    case '\n':
                        cout << "Error on line " << line << "\r\n";
                        cout << "Code: " << 0 << "\r\n";
                        cout << "Line: " << GetLineG() << "\r\n";
                        Utils::Throw("Param Not Found");
                        break;
                    case ' '://jump
                        //parse param
                        Fix16384(Jump_L);
                        table.push_back(OpCode::Jump);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OpCode::Nop);
                        table.push_back(OpCode::Nop);
                        break;
                    case 'e'://jumpeq will need to check q
                        ChkRem("q",1,true);
                        //parse param
                        Fix16384(JumpEQ_L);
                        table.push_back(OpCode::JumpEQ);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OpCode::Nop);
                        table.push_back(OpCode::Nop);
                        break;
                    case 'f'://jumpfalse will need to check alse
						ChkRem("alse",4,true);
                        //parse param
                        Fix16384(JumpFalse_L);
                        table.push_back(OpCode::JumpFalse);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OpCode::Nop);
                        table.push_back(OpCode::Nop);
                        break;
                    case 'g':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'e'://jumpge
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpGE_L);
                                table.push_back(OpCode::JumpGE);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OpCode::Nop);
                                table.push_back(OpCode::Nop);
                            break;
                            case 't'://jumpgt
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpGT_L);
                                table.push_back(OpCode::JumpGT);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OpCode::Nop);
                                table.push_back(OpCode::Nop);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'l':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'e'://jumple
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpLE_L);
                                table.push_back(OpCode::JumpLE);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OpCode::Nop);
                                table.push_back(OpCode::Nop);
                                break;
                            case 't'://jumplt
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpLT_L);
                                table.push_back(OpCode::JumpLT);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OpCode::Nop);
                                table.push_back(OpCode::Nop);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'n'://jumpne will need to check e
                        ChkRem("e",1,true);
                        //parse param
                        Fix16384(JumpNE_L);
                        table.push_back(OpCode::JumpNE);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OpCode::Nop);
                        table.push_back(OpCode::Nop);
                        break;
                    case 't'://jumptrue will need to check rue
                        ChkRem("rue",3,true);
                        //parse param
                        table.push_back(OpCode::Push_1);
                        Fix16384(JumpEQ_L);
                        table.push_back(OpCode::JumpEQ);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OpCode::Nop);
                        table.push_back(OpCode::Nop);
                        break;
                    default:
                            UnkOpcodeError();
                        break;

                }
                //}
                break;
            case 'r'://{
                //return will need to check eturn
				ChkRem("eturn",5,true);
                //parse param
                Fix16384(Return_L);
				table.push_back(OpCode::Return);
				table.push_back(GetParamAsInt<uint8_t>());
				table.push_back(GetParamAsInt<uint8_t>());
            //}
                break;
            case 'n'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'e'://neg will need to check g
                        ChkRem("g",1,false);
                        //append code
						table.push_back(OpCode::Neg);
                        break;
                    case 'o':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'p'://nop
                                ChkRem();
                                //append code
                                if(!ignoreNops)
								table.push_back(OpCode::Nop);
                                break;
                            case 't'://not
                                ChkRem();
                                //append code
								table.push_back(OpCode::Not);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
                //}
                break;
            case 'f'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'r'://fromstack will need to check omstack
						ChkRem("omstack",7,false);
                        //append code
						table.push_back(OpCode::FromStack);
                        break;
                    case 't':
                        CharNum+=2;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum - 1]) != 'o')
                        {
                            UnkOpcodeError();
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'i'://ftoi
                                ChkRem();
                                //append code
								table.push_back(OpCode::FToI);
                                break;
                            case 'v'://ftov
                                ChkRem();
                                //append code
								table.push_back(OpCode::FToV);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'u'://function will need to check nction
						ChkRem("nction",6,true);
                        //parse param
                        Fix16384(5);
                        table.push_back(OpCode::Function);
                        table.push_back(GetParamAsInt<uint8_t>());
                        PushInt16(GetParamAsInt<uint16_t>());
                        table.push_back(0);//function name

                        FrameNames.clear();

                        break;
                    case 'a'://fadd will need to check dd
                        ChkRem("dd",2,false);
                        //append code
						table.push_back(OpCode::fAdd);
                        break;
                    case 'c':
                        CharNum+=3;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum - 3]) == 'c' && tolower(data[CharNum - 2]) == 'm' && tolower(data[CharNum - 1]) == 'p'))
                        {
                            UnkOpcodeError();
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'e'://fcmpeq will need to check q
                                ChkRem("q",1,false);
                                //append code
								table.push_back(OpCode::fCmpEQ);
                                break;
                            case 'g':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://fcmpge
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::fCmpGE);
                                        break;
                                    case 't'://fcmpgt
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::fCmpGT);
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }

                                break;
                            case 'l':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Utils::Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://fcmple
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::fCmpLE);
                                        break;
                                    case 't'://fcmplt
                                        ChkRem();
                                        //append code
										table.push_back(OpCode::fCmpLT);
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }

                                break;
                            case 'n'://fcmpne will need to check e
                                ChkRem("e",1,false);
                                //append code
								table.push_back(OpCode::fCmpNE);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'd'://fdiv will need to check iv
                        ChkRem("iv",2,false);
                        //append code
						table.push_back(OpCode::fDiv);
                        break;
                    case 'm':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'o'://fmod will need to check d
                                ChkRem("d",1,false);
                                //append code
								table.push_back(OpCode::fMod);
                                break;
                            case 'u'://fmult will need to check lt
                                ChkRem("lt",2,false);
                                //append code
								table.push_back(OpCode::fMult);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'n'://fneg will need to check eg
                        ChkRem("eg",2,false);
                        //append code
						table.push_back(OpCode::fNeg);
                        break;
                    case 's'://fsub will need to check ub
                        ChkRem("ub",2,false);
                        //append code
						table.push_back(OpCode::fSub);
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case 'a'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'd':
                        CharNum+=2;
                        if(CharNum > string_size)
                        {
                            if(CharNum - 1 <= string_size)
                            {
                                if(tolower(data[CharNum - 1]) == 'd')
                                {
                                    goto add;
                                }
                            }
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum - 1]) == 'd')
                        {
                            switch(tolower(data[CharNum]))
                            {
                                case '1'://add1
                                    ChkRem(nullptr,0,true);
                                    //parse param
                                    Fix16384(Add1_L);
									table.push_back(OpCode::Add1);
									table.push_back(GetParamAsInt<uint8_t>());
                                    break;
                                case '2'://add2
                                    ChkRem(nullptr,0,true);
                                    //parse param
                                    Fix16384(Add2_L);
									table.push_back(OpCode::Add2);
									PushInt16(GetParamAsInt<uint16_t>());
                                    break;
                                case '\n':
                                case ' ':
                                case '\r'://add
                                    add:
                                    //append code
									table.push_back(OpCode::Add);
                                    break;
                                case '/':
                                    if(CharNum + 1 < string_size)
                                    {
                                        if(data[CharNum + 1] == '/')
                                        {
                                            table.push_back(OpCode::Add);
                                            continue;
                                        }
                                    }
                                    break;
                                default:
                                    UnkOpcodeError();
                                    break;
                            }
                        }
                        else
                        {
                            UnkOpcodeError();
                        }
                        break;
                    case 'n'://and will need to check d
                        ChkRem("d",1,false);
                        //append code
						table.push_back(OpCode::And);
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case 'd'://{
                 CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'i'://div will need to check v
                        ChkRem("v",1,false);
                        //append code
						table.push_back(OpCode::Div);
                        break;
                    case 'r'://drop will need to check op
                        ChkRem("op",2,false);
                        //append code
						table.push_back(OpCode::Drop);
                        break;
                    case 'u'://dup will need to check p
                        ChkRem("p",1,false);
                        //append code
						table.push_back(OpCode::Dup);
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
                //}
                break;
            case 'o'://{
                //or will need to check r
                ChkRem("r",1,false);
                //append code
				table.push_back(OpCode::Or);
            //}
                break;
            case 't'://{
                 CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'h'://throw will need to check row
                        ChkRem("row",3,false);
                        //append code
						table.push_back(OpCode::Throw);
                        break;
                    case 'o'://tostack will need to check stack
						ChkRem("stack",5,false);
                        //append code
						table.push_back(OpCode::ToStack);
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case 'i'://{
                CharNum+= 3;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                if(!(tolower(data[CharNum - 2]) == 't' && tolower(data[CharNum - 1]) == 'o'))
                {
                    UnkOpcodeError();
                }
                switch(tolower(data[CharNum]))
                {
                    case 'f'://itof
                        ChkRem();
                        //append code
						table.push_back(OpCode::IToF);
                        break;
                    case 's'://itos
                        ChkRem(nullptr,0,true);
                        //parse param
                        Fix16384(IToS_L);
						table.push_back(OpCode::IToS);
						table.push_back(GetParamAsInt<uint8_t>());
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case 'm'://{
                CharNum++;

                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'e'://memcopy will need to check mcopy
                        ChkRem("mcopy",5,false);

                        //append code
						table.push_back(OpCode::MemCopy);
                        break;
                    case 'o'://mod will need to check d
                        ChkRem("d",1,false);
                        //append code
						table.push_back(OpCode::Mod);
                        break;
                    case 'u':
                        CharNum+=2;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Utils::Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum - 1]) == 'l' && tolower(data[CharNum]) == 't'))
                        {
                            UnkOpcodeError();
                        }
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            goto mult;
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case '1'://mult1
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(Mult1_L);
								table.push_back(OpCode::Mult1);
								table.push_back(GetParamAsInt<uint8_t>());
                                break;
                            case '2'://mult2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(Mult2_L);
								table.push_back(OpCode::Mult2);
								PushInt16(GetParamAsInt<uint16_t>());
                                break;
                            case '\n':

                            case ' ':
                            case '\r'://mult
                                mult:
                                //append code
								table.push_back(OpCode::Mult);
                                break;
                            default:
                                UnkOpcodeError();
                                break;

                        }
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case 'v'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Utils::Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'a'://vadd will need to check dd
                        ChkRem("dd",2,false);
                        //append code
						table.push_back(OpCode::vAdd);
                        break;
                    case 'd'://vdiv will need to check iv
                        ChkRem("iv",2,false);
                        //append code
						table.push_back(OpCode::vDiv);
                        break;
                    case 'm'://vmult will need to check ult
                        ChkRem("ult",3,false);
                        //append code
						table.push_back(OpCode::vMult);
                        break;
                    case 'n'://vneg will need to check eg
                        ChkRem("eg",2,false);
                        //append code
						table.push_back(OpCode::vNeg);
                        break;
                    case 's'://vsub will need to check ub
                        ChkRem("ub",2,false);
                        //append code
						table.push_back(OpCode::vSub);
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case 'x'://{
                //xor will need to check or
                ChkRem("or",2,false);
                //append code
                table.push_back(OpCode::Xor);
            //}
                break;
            default:
                CharNum++;
                break;

        }
        /*
        if(table.size() % 16384 < SavedTableSize % 16384)
        {
            //code page has been passed
            if(table.size() % 16384 == 0)
                continue;
            uint32_t rem = (16384 - (SavedTableSize % 16384));
            table.resize(table.size() + rem);
            memcpy(table.data() + SavedTableSize + rem, table.data() + SavedTableSize, table.size() - SavedTableSize);
            memset(table.data() + SavedTableSize, 0, rem);
        }
        */
    }



    //Fix labels
    uint32_t out;
    for(uint32_t ji = 0; ji < Jumps.size(); ji++)
    {
        if(GetLabelLoc(&out,Jumps[ji].Label,Jumps[ji].LineStartPos))
        {
            if(Jumps[ji].JumpType == JumpType::pCall)
            {
                uint32_t value = out;

                table[Jumps[ji].TablePos] = *(((uint8_t*)&value) + 3);
                table[Jumps[ji].TablePos + 1] = *(((uint8_t*)&value) + 2);
                table[Jumps[ji].TablePos + 2] = *(((uint8_t*)&value) + 1);
                table[Jumps[ji].TablePos + 3] = *(((uint8_t*)&value));
            }
            else if(Jumps[ji].JumpType == JumpType::Call)
            {
                uint32_t value = out;//add check for label out of bounds
                //cout << value << endl;
                if(value > 16777215)
                {
                    cout << "Error on line " << Jumps[ji].LineNum << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineGAtPos(Jumps[ji].LineStartPos) << "\r\n";
                    cout << "Pos: " << value << "\r\n";
                    Utils::Throw("Call is out of bounds");
                }
                table[Jumps[ji].TablePos] = *(((uint8_t*)&value) + 2);
                table[Jumps[ji].TablePos + 1] = *(((uint8_t*)&value) + 1);
                table[Jumps[ji].TablePos + 2] = *(((uint8_t*)&value));
            }
            else
            {
                int32_t value = out - Jumps[ji].TablePos - 2;//add check for label out of bounds
                //cout << value << endl;
                if(value < SHRT_MIN || value > SHRT_MAX)
                {
                    //cout << out << endl;
                    //cout << Jumps[ji].TablePos << endl;
                    cout << "Error on line " << Jumps[ji].LineNum << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineGAtPos(Jumps[ji].LineStartPos) << "\r\n";
                    cout << "Pos: " << value << "\r\n";
                    cout << "Label: " << Jumps[ji].Label << "\r\n";
                    Utils::Throw("Label is out of bounds");
                }
                uint16_t shortval = (uint16_t)value;
                table[Jumps[ji].TablePos] = *(((uint8_t*)&shortval) + 1);
                table[Jumps[ji].TablePos + 1] = *((uint8_t*)&shortval);

            }

        }
    }



    //{ add code to code pages
    uint32_t tablesize = table.size();

    //cout << (tablesize + 16384 - 1) / 16384 << endl;
    //cout << tablesize << endl;

    if(tablesize > 16384)
    {
        Header.CodePages.resize((tablesize + 16384 - 1) / 16384);
    }
    else Header.CodePages.resize(1);

    uint32_t pagesize = Header.CodePages.size();

    for(uint32_t i = 0; i < pagesize; i++)
    {
        if(i * 16384 + 16384 < tablesize)
        {
            Header.CodePages[i].resize(16384);
            memcpy(Header.CodePages[i].data(),table.data() + i * 16384, 16384);

        }
        else
        {
            uint32_t rem = tablesize - i * 16384;
            Header.CodePages[i].resize(rem);
            memcpy(Header.CodePages[i].data(),table.data() + i * 16384, rem);
            break;
        }
    }
    //}
    //{ add string to string pages
    tablesize = stringtable.size();

    if(tablesize > 16384)
    {
        Header.StringPages.resize((tablesize + 16384 - 1) / 16384);
    }
    else Header.StringPages.resize(1);

    pagesize = Header.StringPages.size();
    for(uint32_t i = 0; i < pagesize; i++)
    {
        if(i * 16384 + 16384 < tablesize)
        {
            Header.StringPages[i].resize(16384);
            memcpy(Header.StringPages[i].data(),stringtable.data() + i * 16384, 16384);

        }
        else
        {
            uint32_t rem = tablesize - i * 16384;
            Header.StringPages[i].resize(rem);
            memcpy(Header.StringPages[i].data(),stringtable.data() + i * 16384, rem);
            break;
        }
    }
    //}

    Header.Natives = natives;

    Header.CodeLength = table.size();
    Header.StringsSize = stringtable.size();
    Header.NativesCount = natives.size();

}

void XSC::GetCode(const char * OutPath, uint32_t flags)
{

    stringstream toRetHeader;
    stringstream toRet;

    toRetHeader.precision(8);
    toRet.precision(8);

    vector<int8_t> _codePages;
    vector<char> _stringPages;


    map<uint32_t, uint32_t> ogStrPtrToModifyed;


    vector<bool> pcsToIgnore(Header.CodeLength);
    set<uint32_t> CustomNativeNames;


    bool hadModifiedPushStringOpCode = false, ignoreThisPC = false;

    uint32_t FunctionCount = 0, LabelCount = 0, UnusedFunctionNum = 0;
    int32_t lastPushValue = 0, lastPushPC = 0;
    Constants::OpCode lastPushOpCode = Constants::OpCode::Nop;

    string _opNames[127]{"Nop", "Add", "Sub", "Mult", "Div", "Mod", "Not", "Neg", "CmpEQ", "CmpNE", "CmpGT", "CmpGE", "CmpLT", "CmpLE", "fAdd", "fSub", "fMult", "fDiv", "fMod", "fNeg", "FCmpEQ", "FCmpNE", "FCmpGT", "FCmpGE", "FCmpLT", "FCmpLE", "vAdd", "vSub", "vMult", "vDiv", "vNeg", "And", "Or", "Xor", "IToF", "FToI", "FToV", "PushB", "PushB2", "PushB3", "Push", "PushF", "Dup", "Drop", "CallNative", "Function", "Return", "pGet", "pSet", "pPeekSet", "ToStack", "FromStack", "GetArrayP1", "GetArray1", "SetArray1", "GetFrameP1", "GetFrame1", "SetFrame1", "GetStaticP1", "GetStatic1", "SetStatic1", "Add1", "Mult1", "GetImmP", "GetImmP1", "GetImm1", "SetImm1", "PushS", "Add2", "Mult2", "GetImmP2", "GetImm2", "SetImm2", "GetArrayP2", "GetArray2", "SetArray2", "GetFrameP2", "GetFrame2", "SetFrame2", "GetStaticP2", "GetStatic2", "SetStatic2", "GetGlobalP2", "GetGlobal2", "SetGlobal2", "Jump", "JumpFalse", "JumpNE", "JumpEQ", "JumpLE", "JumpLT", "JumpGE", "JumpGT", "Call", "GetGlobalP3", "GetGlobal3", "SetGlobal3", "PushI24", "Switch", "PushString", "GetHash", "StrCopy", "IToS", "StrAdd", "StrAddI", "MemCopy", "Catch", "Throw", "pCall", "Push_-1", "Push_0", "Push_1", "Push_2", "Push_3", "Push_4", "Push_5", "Push_6", "Push_7", "PushF_-1", "PushF_0", "PushF_1", "PushF_2", "PushF_3", "PushF_4", "PushF_5", "PushF_6", "PushF_7"};

    struct PCI
    {
        bool Ignored = false;
        bool IsLabelFunction = false;
        int64_t LabelNum;
    };
    map<int64_t, PCI> PCInformation;
    struct PINS
    {
        Constants::OpCode Op;
        uint8_t byteval[4];
    };
    map<int64_t, PINS> pushInserts;
    map<uint32_t, boost::tokenizer<boost::char_separator<char>>::iterator> NativeMap;

    std::ifstream NativeFile("natives.txt");
    string content( (std::istreambuf_iterator<char>(NativeFile) ),(std::istreambuf_iterator<char>()));
    NativeFile.close();
    boost::char_separator<char> sep(":\n");
    boost::tokenizer<boost::char_separator<char>> tokens(content, sep);
    for (boost::tokenizer<boost::char_separator<char>>::iterator tokeni = tokens.begin(); tokeni != tokens.end(); tokeni++)
    {
        uint32_t token1 = stoul(*tokeni);
        tokeni++;
        NativeMap.insert({token1,tokeni});

    }

    uint32_t len = 0;
    for(uint32_t i = 0; i < Header.CodePages.size(); i++)
    {
        _codePages.resize( len + Header.CodePages[i].size() );
        memcpy(_codePages.data() + len, Header.CodePages[i].data(), Header.CodePages[i].size());
        len += Header.CodePages[i].size();
    }
    len = 0;
    for(uint32_t i = 0; i < Header.StringPages.size(); i++)
    {
        _stringPages.resize( len + Header.StringPages[i].size());
        memcpy(_stringPages.data() + len, Header.StringPages[i].data(), Header.StringPages[i].size());
        len += Header.StringPages[i].size();
    }

    //detection for newlines and carriage returns
    uint32_t AppendedChars = 0;
    for(uint32_t i = 0; i < _stringPages.size(); i++)
    {
        switch(_stringPages[i])
        {

            case '\n':
                _stringPages[i] = 'n';
                _stringPages.insert(_stringPages.begin() + i,'\\');
                i++;
                AppendedChars++;
            break;
            case '\r':
                _stringPages[i] = 'r';
                _stringPages.insert(_stringPages.begin() + i,'\\');
                i++;
                AppendedChars++;
            break;
            case '"':
                _stringPages.insert(_stringPages.begin() + i,'\\');
                i++;
                AppendedChars++;
            break;
            case '\\':
                _stringPages.insert(_stringPages.begin() + i,'\\');
                i++;
                AppendedChars++;
            break;
            case '\0':
                ogStrPtrToModifyed.insert({i - AppendedChars + 1,i + 1});
            break;


        }

    }

    int8_t* codepages = _codePages.data();
    int32_t Position = 0;


//{ Delegates

    auto HasFlag = [&](auto bitflag)
    {
        bitset<8> bf = bitflag;
        bitset<8> f = flags;
        for(uint32_t i = 0; i < 8; i++)
        {
            if(bf.test(i))
            {
                if(f.test(i))
                    return true;
                break;
            }
        }
        return false;
    };
    auto WriteByte = [&](auto b)
    {
        *(uint8_t*)(codepages + Position) = b;
        Position++;
    };
    auto ReadByte = [&]()
    {
        uint8_t ret = *(uint8_t*)(codepages + Position);
        Position++;
        return ret;
    };
    auto ReadInt16 = [&]()
    {
        int16_t ret = *(int16_t*)(codepages + Position);
        Position+=2;
        return ret;
    };
    auto ReadUInt16 = [&]()
    {
        uint16_t ret = *(uint16_t*)(codepages + Position);
        Position+=2;
        return ret;
    };
    auto ReadInt24 = [&]()
    {
        uint32_t in = Utils::SwapEndian(*(uint32_t*)(codepages + Position));

        //printf("%x2\n", in);
        Position += 3;
        return in >> 8;
    };
    auto GetInt24 = [&](auto val)
    {
        return val >> 8;
    };
    auto ReadInt32 = [&]()
    {
        uint32_t ret = *(uint32_t*)(codepages + Position);
        Position+=4;
        return ret;
    };
    auto ReadSingle = [&]()
    {
        float ret = *(float*)(codepages + Position);
        Position+=4;
        return ret;
    };

    auto ReadStringAtPos = [&](auto pos)
    {
        if((uint32_t)pos > _stringPages.size())
        {
            cout << "String Index (" << pos << ") is Out Of Bounds By " << pos - _stringPages.size() << "\r\n";
            Utils::Throw( "Index Out Of Bounds" );
        }
        else if(pos == 0)
            return _stringPages.data();

        map<uint32_t,uint32_t>::iterator i = ogStrPtrToModifyed.find(pos);
        if(i != ogStrPtrToModifyed.end())
        {
            char* ret = (char*)(_stringPages.data() + i->second);
            return ret;
        }
        else
        {
            cout << "Invalid String Index " << pos << "\r\n";
            Utils::Throw( "Invalid String Index" );
        }
        return _stringPages.data();
    };
    auto AdvPos = [&](auto pos)
    {
        Position += pos;
    };
    auto SaveSwitchOffsets = [&]()
    {
        uint8_t caseCount = ReadByte();
        for (int i = 0; i < caseCount; i++)
        {
            //swap or not to swap?
            int switchCase = Utils::SwapEndian(ReadInt32());

            int16_t jumpLoc = Utils::SwapEndian(ReadInt16());
            int64_t fullJumpLoc = jumpLoc + Position;

            if (PCInformation.count(fullJumpLoc) == 0)
            {
                PCI ins;
                ins.LabelNum = LabelCount;
                LabelCount++;

                PCInformation.insert({fullJumpLoc, ins});
            }
        }


    };
    auto SaveCallOffset = [&]()
    {
        int64_t callOffset = ReadInt24();
        map<int64_t, PCI>::iterator pos = PCInformation.find(callOffset);
        if (pos == PCInformation.end())
        {
            PCI ins;
            ins.IsLabelFunction = true;

            ins.LabelNum = FunctionCount;
            FunctionCount++;

            PCInformation.insert({callOffset, ins});
        }
        else
        {

            if(!pos->second.IsLabelFunction)
            {
                pos->second.IsLabelFunction = true;

                //note: this creates a skipped label. if needed loop through rest of map with pos->second.LabelNum = pos->second.LabelNum - 1
                pos->second.LabelNum = FunctionCount;
                FunctionCount++;

            }
        }

    };

    auto SaveJumpOffset = [&]()
    {
        int16_t val = Utils::SwapEndian(ReadInt16());
        int64_t fullVal = val + Position;

        if (PCInformation.count(fullVal) == 0)
        {
            PCI ins;
            ins.LabelNum = LabelCount;
            LabelCount++;
            PCInformation.insert({fullVal, ins});
        }
    };
    auto WriteLine = [&](auto str)
    {
        toRet << str << "\r\n";
    };
//}

//{ First Loop
    while (Position < _codePages.size())
    {
        Constants::OpCode cop = (Constants::OpCode)ReadByte();
        if (cop < 0 || (int8_t)cop > 126)
        {
            cout << "Invalid OpCode (PC: " << Position - 1 << " Op: " << cop << ")\r\n";
            Utils::Throw( "Invalid OpCode" );
        }


        //cout << _opNames[cop] << "\r\n";
        switch (cop)
        {
            case Constants::OpCode::PushB:
                lastPushPC = Position - 1;
                lastPushOpCode = cop;
                AdvPos(1);
                break;
            case Constants::OpCode::GetArrayP1:
            case Constants::OpCode::GetArray1:
            case Constants::OpCode::SetArray1:
            case Constants::OpCode::GetFrameP1:
            case Constants::OpCode::GetFrame1:
            case Constants::OpCode::SetFrame1:
            case Constants::OpCode::GetStaticP1:
            case Constants::OpCode::GetStatic1:
            case Constants::OpCode::SetStatic1:
            case Constants::OpCode::Add1:
            case Constants::OpCode::Mult1:
            case Constants::OpCode::GetImmP1:
            case Constants::OpCode::GetImm1:
            case Constants::OpCode::SetImm1:
            case Constants::OpCode::StrCopy:
            case Constants::OpCode::IToS:
            case Constants::OpCode::StrAdd:
            case Constants::OpCode::StrAddI:
                AdvPos(1);
                break;
            case Constants::OpCode::PushS:
                lastPushPC = Position - 1;
                lastPushOpCode = cop;
                AdvPos(2);
                break;
            case Constants::OpCode::PushB2:
                lastPushPC = Position - 1;
                lastPushOpCode = cop;
                AdvPos(2);
                break;
            case Constants::OpCode::Return:
            case Constants::OpCode::Add2:
            case Constants::OpCode::Mult2:
            case Constants::OpCode::GetImmP2:
            case Constants::OpCode::GetImm2:
            case Constants::OpCode::SetImm2:
            case Constants::OpCode::GetArrayP2:
            case Constants::OpCode::GetArray2:
            case Constants::OpCode::SetArray2:
            case Constants::OpCode::GetFrameP2:
            case Constants::OpCode::GetFrame2:
            case Constants::OpCode::SetFrame2:
            case Constants::OpCode::GetStaticP2:
            case Constants::OpCode::GetStatic2:
            case Constants::OpCode::SetStatic2:
            case Constants::OpCode::GetGlobalP2:
            case Constants::OpCode::GetGlobal2:
            case Constants::OpCode::SetGlobal2:
                AdvPos(2);
                break;
            case Constants::OpCode::PushI24:
                lastPushPC = Position - 1;
                lastPushOpCode = cop;
                AdvPos(3);
                break;
            case Constants::OpCode::PushB3:
                lastPushPC = Position - 1;
                lastPushOpCode = cop;
                AdvPos(3);
                break;
            case Constants::OpCode::CallNative:
            case Constants::OpCode::GetGlobalP3:
            case Constants::OpCode::GetGlobal3:
            case Constants::OpCode::SetGlobal3:

                AdvPos(3);
                break;
            case Constants::OpCode::Push:
                lastPushPC = Position - 1;
                lastPushOpCode = cop;
                AdvPos(4);
                break;
            case Constants::OpCode::PushF:
                AdvPos(4);
                break;
            case Constants::OpCode::Function:
                AdvPos(3);
                AdvPos(ReadByte());
                break;
            case Constants::OpCode::Switch:
                SaveSwitchOffsets();
                break;
            case Constants::OpCode::Jump:
            case Constants::OpCode::JumpFalse:
            case Constants::OpCode::JumpEQ:
            case Constants::OpCode::JumpNE:
            case Constants::OpCode::JumpGE:
            case Constants::OpCode::JumpGT:
            case Constants::OpCode::JumpLE:
            case Constants::OpCode::JumpLT:
                SaveJumpOffset();

                break;
            case Constants::OpCode::Call:
                SaveCallOffset();

                break;
            case Constants::OpCode::PushString:
                if (lastPushOpCode == Constants::OpCode::PushB2)
                {
                    hadModifiedPushStringOpCode = true;
                    int64_t tempOff = Position;
                    Position = lastPushPC;
                    WriteByte((int8_t)Constants::OpCode::PushB);
                    Position++;

                    int8_t secondByteVal = ReadByte();
                    Position--;
                    pcsToIgnore[Position] = true;
                    WriteByte((int8_t)Constants::OpCode::Nop);
                    if (pushInserts.count(Position) == 0)
                    {
                        PINS obj;
                        obj.Op = Constants::OpCode::PushB;
                        obj.byteval[0] = secondByteVal;
                        pushInserts.insert({Position, obj});
                    }
                    Position = tempOff;
                }
                else if (lastPushOpCode == Constants::OpCode::PushB3)
                {
                    hadModifiedPushStringOpCode = true;
                    long tempOff = Position;
                    Position = lastPushPC;
                    WriteByte((int8_t)Constants::OpCode::PushB2);
                    Position += 2;

                    int8_t thirdByteVal = ReadByte();
                    Position--;
                    pcsToIgnore[Position] = true;
                    WriteByte((int8_t)Constants::OpCode::Nop);
                    if (pushInserts.count(Position) == 0)
                    {
                        PINS obj;
                        obj.Op = Constants::OpCode::PushB;
                        obj.byteval[0] = thirdByteVal;
                        pushInserts.insert({Position, obj});
                    }
                    Position = tempOff;
                }
                else
                {
                    pcsToIgnore[lastPushPC] = true;

                }
                break;
            case Constants::OpCode::Push_0:
            case Constants::OpCode::Push_1:
            case Constants::OpCode::Push_2:
            case Constants::OpCode::Push_3:
            case Constants::OpCode::Push_4:
            case Constants::OpCode::Push_5:
            case Constants::OpCode::Push_6:
            case Constants::OpCode::Push_7:
                lastPushOpCode = cop;
                lastPushPC = Position - 1;
                break;
            default:
                break;

        }
    }
//}

    if (hadModifiedPushStringOpCode)
    {
        toRetHeader << "//This script MAY not compile correctly due to a modified PushString opcode\r\n";
        toRetHeader << "//Given to it by the decompiler to try and fix the script.\r\n\r\n";
    }
    if (Header.Statics.size() > 0)
    {
        toRetHeader << "//> Default Static Information\r\nSetStaticsCount " << Header.Statics.size() << "\r\n";

        bool hadAnyNonZeroStatics = false;
        //bool scriptHasParameters = Header.ParameterCount > 0;

        if (Header.ParameterCount > 0)
        {
            for (int i =0; i < Header.ParameterCount;i++)
                toRetHeader << "SetStaticName " << i << " ScriptParameter" << i << "\r\n";
            toRetHeader << "\r\n";
        }

        for (uint32_t i = 0; i < Header.Statics.size(); i++)
            if (Header.Statics[i] != 0)
            {
                hadAnyNonZeroStatics = true;
                toRetHeader << "SetDefaultStatic " << i << " " << Header.Statics[i] << "\r\n";
            }
        toRetHeader << "//<\r\n\r\n";
    }

//{ Main Loop
    bool WasLastLineALabel = false, UsesCustomNativeNames = false, WasLastLabelANopLabel = false;
    Position = 0;
    while (Position < _codePages.size())
    {

        int l = Position;

        long beforeOpCodePC = Position;

        Constants::OpCode cop = (Constants::OpCode)ReadByte();

        if (cop < 0 || (uint8_t)cop > 126)
        {
            cout << "Invalid OpCode " << cop << "\r\n";
            //FILE* file = fopen("C:\\Users\\Rocko\\Desktop\\out.txt", "wb");
            //toRet.seekg(0, ios::end);
            //fwrite(toRet.str().c_str(), 1, toRet.tellg(), file);
            //fclose(file);
            Utils::Throw( "Invalid OpCode" );
        }


        if (PCInformation.count(beforeOpCodePC) > 0)
        {
            if(PCInformation[beforeOpCodePC].IsLabelFunction)
                toRet << "//<\r\n" << "\r\n:Function_" << PCInformation[beforeOpCodePC].LabelNum << "//>\r\n";
            else toRet << "\r\n:Label_" << PCInformation[beforeOpCodePC].LabelNum << "\r\n";
            WasLastLineALabel = true;
        }
        else WasLastLineALabel = false;

        if(WasLastLineALabel && cop == Constants::OpCode::Nop)
        {
            WasLastLabelANopLabel = true;
        }

        if (HasFlag(Constants::DecompileFlag::ShowPC))
            toRet << "[PC -> " << Position - 1 << "] ";

        if (pushInserts.count(beforeOpCodePC) > 0)
        {

            PINS _insertData = pushInserts[beforeOpCodePC];
            int8_t dataZero = (int8_t)_insertData.Op;
            Constants::OpCode dataZeroOpCode = (Constants::OpCode)dataZero;

            switch (dataZeroOpCode)
            {
                //dafuk
                case Constants::OpCode::PushB:
                    lastPushValue = (uint8_t)_insertData.byteval[0];
                    break;
                case Constants::OpCode::PushB2:
                    lastPushValue = (uint8_t)_insertData.byteval[1];
                    break;
                case Constants::OpCode::PushB3:
                    lastPushValue = (uint8_t)_insertData.byteval[2];
                    break;
                case Constants::OpCode::Push:
                    lastPushValue = *(int32_t*)&_insertData.byteval;

                    break;
                case Constants::OpCode::PushS:
                    lastPushValue = *(int16_t*)&_insertData.byteval;

                    break;
                case Constants::OpCode::PushI24:
                    lastPushValue = GetInt24(*(uint32_t*)&_insertData.byteval);

                    break;
                default:
                    break;
            }

        }

        switch (cop)
        {
            case Constants::OpCode::PushB:
                lastPushValue = ReadByte();
                if(!pcsToIgnore[Position - 2])
                toRet << _opNames[(uint8_t)cop] << " " <<  lastPushValue << "\r\n";
                break;
            case Constants::OpCode::GetArrayP1:
            case Constants::OpCode::GetArray1:
            case Constants::OpCode::SetArray1:
            case Constants::OpCode::GetFrameP1:
            case Constants::OpCode::GetFrame1:
            case Constants::OpCode::SetFrame1:
                lastPushValue = ReadByte();
                toRet << _opNames[(uint8_t)cop] << " " <<  lastPushValue << "\r\n";
                break;
            case Constants::OpCode::GetStaticP1:
            case Constants::OpCode::GetStatic1:
            case Constants::OpCode::SetStatic1:
                if (Header.ParameterCount > 0)
                {
                    uint8_t tryParseByte = ReadByte();
                    if (tryParseByte < Header.ParameterCount)
                        toRet << _opNames[(uint8_t)cop] << " ScriptParameter" << to_string(tryParseByte) << "\r\n";
                    else
                        toRet << _opNames[(uint8_t)cop] << " " << to_string(tryParseByte) << "\r\n";
                }
                else
                    toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte()) << "\r\n";
                break;
            case Constants::OpCode::Add1:
            case Constants::OpCode::Mult1:
            case Constants::OpCode::GetImmP1:
            case Constants::OpCode::GetImm1:
            case Constants::OpCode::SetImm1:
            case Constants::OpCode::StrCopy:
            case Constants::OpCode::IToS:
            case Constants::OpCode::StrAdd:
            case Constants::OpCode::StrAddI:
                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte()) << "\r\n";
                break;

            case Constants::OpCode::PushS:
                lastPushValue = Utils::SwapEndian(ReadInt16());
                if(!pcsToIgnore[Position - 3])
                toRet << _opNames[(uint8_t)cop] << " " << lastPushValue << "\r\n";
                break;
            case Constants::OpCode::Add2:
            case Constants::OpCode::Mult2:
            case Constants::OpCode::GetImmP2:
            case Constants::OpCode::GetImm2:
            case Constants::OpCode::SetImm2:
            case Constants::OpCode::GetArrayP2:
            case Constants::OpCode::GetArray2:
            case Constants::OpCode::SetArray2:
            case Constants::OpCode::GetFrameP2:
            case Constants::OpCode::GetFrame2:
            case Constants::OpCode::SetFrame2:
			case Constants::OpCode::GetGlobalP2:
            case Constants::OpCode::GetGlobal2:
            case Constants::OpCode::SetGlobal2:
				toRet << _opNames[(uint8_t)cop] << " " << Utils::SwapEndian(ReadInt16()) << "\r\n";
			break;
            case Constants::OpCode::GetStaticP2:
            case Constants::OpCode::GetStatic2:
            case Constants::OpCode::SetStatic2:
                if (Header.ParameterCount > 0)
                {
                    uint32_t tryParseUShort = Utils::SwapEndian(ReadUInt16());
                    if (tryParseUShort < Header.ParameterCount)
                        toRet << _opNames[(uint8_t)cop] << "  ScriptParameter" << to_string(tryParseUShort) << "\r\n";
                    else
                        toRet << _opNames[(uint8_t)cop] << " " << to_string(tryParseUShort) << "\r\n";
                }
                else
                    toRet << _opNames[(uint8_t)cop] << " " << Utils::SwapEndian(ReadUInt16()) << "\r\n";
                break;
            case Constants::OpCode::PushB2:
            case Constants::OpCode::Return:
                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte());
                toRet << " " << to_string(ReadByte()) << "\r\n";
                break;
            case Constants::OpCode::PushB3:
                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte());
                toRet << " " << to_string(ReadByte()) << " ";
                toRet << to_string(ReadByte()) << "\r\n";
                break;
            case Constants::OpCode::CallNative:
            {
                uint8_t nativeFlagHolder = ReadByte();
                int16_t nativeIndex = Utils::SwapEndian(ReadInt16());
                int nativeParamCount = nativeFlagHolder >> 2;
                int nativeRetCount = nativeFlagHolder & 3;

                toRet << _opNames[(uint8_t)cop] << " ";

                if(NativeMap.count(Header.Natives[nativeIndex]) > 0)
                {
                    string NativeName = *NativeMap.find(Header.Natives[nativeIndex])->second;
                    if(NativeName.at(0) == '_')
                    {
                        uint32_t NativeVal = Utils::SwapEndian(Header.Natives[nativeIndex]);
                        char * NativeHash = Utils::IntToHex(NativeVal);

                        if (CustomNativeNames.find(NativeVal) == CustomNativeNames.end())
                        {
                            if(CustomNativeNames.size() == 0)
                            {
                                toRetHeader << "//> Custom Native Names\r\n";
                                UsesCustomNativeNames = true;
                            }
                            CustomNativeNames.insert(NativeVal);
                            toRetHeader << "SetNativeName 0x" << NativeHash << " " << NativeName << "\r\n";
                            //cout << NativeName << endl;
                        }

                        toRet << NativeName << " " << nativeParamCount << " " << nativeRetCount << "//0x" << NativeHash;
                    }
                    else
                        toRet << NativeName << " " << nativeParamCount << " " << nativeRetCount;
                }
                else
                {
                    toRet << "unk_0x" << Utils::IntToHex(Utils::SwapEndian((uint32_t)Header.Natives[nativeIndex])) << " " << nativeParamCount << " " << nativeRetCount;
                }

                if (HasFlag(Constants::DecompileFlag::ShowNativeInfo))
                    toRet << "//NI: " << nativeIndex << "\r\n";
                else
                    toRet << "\r\n";
            }
            break;
            case Constants::OpCode::GetGlobalP3:
            case Constants::OpCode::GetGlobal3:
            case Constants::OpCode::SetGlobal3:
                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadInt24()) << "\r\n";
                break;
            case Constants::OpCode::PushI24:
                lastPushValue = ReadInt24();
                if(!pcsToIgnore[Position - 4])
                toRet << _opNames[(uint8_t)cop] << " " << lastPushValue << "\r\n";
                break;
            case Constants::OpCode::Push:
                lastPushValue = Utils::SwapEndian(ReadInt32());
                if(!pcsToIgnore[Position - 5])
                toRet << _opNames[(uint8_t)cop] << " " << lastPushValue << "\r\n";
                break;
            case Constants::OpCode::PushF:
            {
                float tmp = ReadSingle();
                toRet << _opNames[(uint8_t)cop] << " " << Utils::SwapEndian(&tmp) << "\r\n";
                break;
            }
            case Constants::OpCode::Function:
            {
                if(!WasLastLineALabel)
                {
                    if(!WasLastLabelANopLabel)
                    {
                        if(UnusedFunctionNum == 0)
                            toRet << ":MainFunction//>\r\n";
                        else
                            toRet << "//<\r\n\r\n:UnusedFunction_" << UnusedFunctionNum << "//>\r\n";
                        UnusedFunctionNum++;

                    }
                }

                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte()) << " ";
                toRet << Utils::SwapEndian(ReadInt16()) << "\r\n";
                AdvPos(ReadByte());
                break;
            }
            case Constants::OpCode::Switch:
            {

                uint8_t switchCaseCount = ReadByte();

                toRet << _opNames[(uint8_t)cop];
                for (uint32_t i = 0; i < switchCaseCount; i++)
                {

                    int32_t switchCase = Utils::SwapEndian(ReadInt32());

                    uint16_t switchVal = Utils::SwapEndian(ReadInt16());
                    int64_t fullSwitchVal = Position + switchVal;
                    //cout << switchCase << "\r\n";

                    if(i == 0)
                        toRet << " [";
                    else
                        toRet << ":[";
                    toRet << switchCase << " @Label_" << PCInformation[fullSwitchVal].LabelNum << "]";
                }
                toRet << "\r\n";
            }
            break;
            case Constants::OpCode::Jump:
            case Constants::OpCode::JumpFalse:
            case Constants::OpCode::JumpEQ:
            case Constants::OpCode::JumpNE:
            case Constants::OpCode::JumpGT:
            case Constants::OpCode::JumpGE:
            case Constants::OpCode::JumpLT:
            case Constants::OpCode::JumpLE:
            {
                int16_t jumpLoc = Utils::SwapEndian(ReadInt16());
                int32_t fullJumpLoc = (int32_t)(jumpLoc + Position);
                string flag = HasFlag(Constants::DecompileFlag::ShowJumpPosition) ? "//JPC: " + to_string(fullJumpLoc) : "";

                if(PCInformation[fullJumpLoc].IsLabelFunction)
                    toRet << _opNames[(uint8_t)cop] << " @Function_" << PCInformation[fullJumpLoc].LabelNum << flag << "\r\n";
                else
                    toRet << _opNames[(uint8_t)cop] << " @Label_" << PCInformation[fullJumpLoc].LabelNum << flag << "\r\n";


            }
            break;
            case Constants::OpCode::Call:
            {
                int callOffset = ReadInt24();
                string flag = HasFlag(Constants::DecompileFlag::ShowCallPosition) ? "//CPC: " + to_string(callOffset) : "";
                toRet << _opNames[(uint8_t)cop] << " @Function_" << PCInformation[callOffset].LabelNum << flag << "\r\n";
            }
            break;
            case Constants::OpCode::PushString:
                if (lastPushValue < 0)
                {
                    toRet << "PushString ###DECOMPILE_ERROR###//Unk PushString Val Of " << lastPushValue << "\r\n";
                    break;
                }
                else {
                    string flag = HasFlag(Constants::DecompileFlag::ShowStringsPC) ? "//SI: " + to_string(lastPushValue) : "";
                    //cout << (char*)ReadStringAtPos(lastPushValue)<< " " << lastPushValue << "\r\n";
                    toRet << _opNames[(uint8_t)cop] << " \"" << (char*)ReadStringAtPos(lastPushValue) << "\"" << flag << "\r\n";
                    break;
                }
            break;
            case Constants::OpCode::Push_0:
            case Constants::OpCode::Push_1:
            case Constants::OpCode::Push_2:
            case Constants::OpCode::Push_3:
            case Constants::OpCode::Push_4:
            case Constants::OpCode::Push_5:
            case Constants::OpCode::Push_6:
            case Constants::OpCode::Push_7:

                lastPushValue = (uint8_t)cop - 110;
                if(!pcsToIgnore[Position - 1])
                toRet << _opNames[(uint8_t)cop] << "\r\n";
                break;
            default:
                if(!pcsToIgnore[Position - 1])
                toRet << _opNames[(uint8_t)cop] << "\r\n";
                break;


        }
//}
         //cout << _opNames[cop] <<  " " << Position - l  << "\r\n";

    }

    FILE* file = fopen(OutPath, "wb");

    if(UsesCustomNativeNames)
        toRetHeader << "//<\r\n";
    toRetHeader << "\r\n";
    toRetHeader.seekg(0, ios::end);
    fwrite(toRetHeader.str().c_str(), 1, toRetHeader.tellg(), file);

    toRet << "//<";
    toRet.seekg(0, ios::end);
    fwrite(toRet.str().c_str(), 1, toRet.tellg(), file);

    fclose(file);
}

//}


