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
#include <stack>
#include <set>
#include <windows.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/tokenizer.hpp>
#include "Utils.h"
#include "RSC.h"
#include "Constants.h"
#include "PikIO.h"

//typedef boost::iterator_range<string::const_iterator> string_view;

using namespace std;
using namespace Utils;
using namespace Utils::Bitwise;
using namespace Utils::System;
using namespace Utils::DataConversion;
using namespace Utils::Hashing;
using namespace Constants;

//{ RSC

bool RSC::OpenScript(void* xIn, size_t* length )
{
    PikIO io;
    io.Init((uint8_t*)xIn, *length, PikIO::Endianess::Big);

//{ Check Compression
uint32_t CompressHead = io.PeekDynamic<uint32_t>();
if(CompressHead == 0x85435352)//.CSR (RSC85)
{
    RSC_Type = 85;
    Header_XSC = XSCHeader();
    if(io.PeekDynamic<uint32_t>(4) == 2)//index 4 = resource // 2 = script resource
    {
        int32_t DecompressedSize = RSC85Parsing::GetSizeFromFlag(io.PeekDynamic<int32_t>(12));//index 12 = xcompress decompile size
        Header_XSC.Flag = io.PeekDynamic<int32_t>(12);

        //cout << "Flags: " << bitset<12>(io.PeekDynamic<int32_t>(12) >> 20) << endl;
        //cout << "Size: " << DecompressedSize << endl;

        if(!Crypt::AES_Decrypt(io.BaseStream + 16, io.Length - 16))
            Throw("Decryption Failed");

        const uint32_t CompressedHeaderStart = 16;//16 = csr header -> CompressedHeader
        const uint32_t CompressedDataStart = CompressedHeaderStart + 8;//8 = compression header -> CompressedDataStart

        uint32_t CompressedSize = io.PeekDynamic<uint32_t>(CompressedHeaderStart + 4);

        if(CompressedSize != io.Length - CompressedDataStart)
            Throw("Invalid Compression Size");

        uint8_t * DecompressedData = new uint8_t[DecompressedSize];


        Compression::xCompress Compression;
        Compression.xCompressInit();

        Compression.Decompress(io.BaseStream + CompressedDataStart,CompressedSize, DecompressedData, DecompressedSize);

        io.BaseStream = DecompressedData;
        io.Position = 0;
        io.Length = DecompressedSize;

//        FILE* file2 = fopen("outnewdecomp.xsc", "wb");
//        fwrite(DecompressedData, 1, DecompressedSize , file2);
//        fclose(file2);
//        cout << "File Written\n";
    }
    else
    {
        Throw("Invalid Resource Type");
    }
}
else if(CompressHead == 0x53435202)//(SCR2)
{
    RSC_Type = 2;
    Header_SCO = SCOHeader();

    Header_SCO.SCR = io.ReadInt32();
    Header_SCO.GlobalsSignature = io.ReadInt32();
    Header_SCO.CompressedSize = io.ReadInt32();
    Header_SCO.unk12 = io.ReadInt32();//-3 encrypted
    Header_SCO.CodeLength = io.ReadInt32();
    Header_SCO.StaticsCount = io.ReadInt32();
    Header_SCO.GlobalsCount = io.ReadInt32();
    Header_SCO.ParameterCount = io.ReadInt32();
    Header_SCO.NativesCount = io.ReadInt32();
    Header_SCO.unk36 = io.ReadInt32();
    Header_SCO.unk40 = io.ReadInt32();
    Header_SCO.unk44 = io.ReadInt32();

    uint8_t * CurrentPos = io.BaseStream + io.Position;

    if(!Crypt::AES_Decrypt(CurrentPos, Header_SCO.CompressedSize))
        Throw("Decryption Failed");

    uint32_t DecompressedSize = Header_SCO.CodeLength + (Header_SCO.StaticsCount * 4) + (Header_SCO.NativesCount * 4);

    uint8_t * DecompressedData = new uint8_t[DecompressedSize];

    Compression::ZLIB_Decompress(CurrentPos,Header_SCO.CompressedSize,DecompressedData,DecompressedSize);

    io.BaseStream = DecompressedData;
    io.Position = 0;
    io.Length = DecompressedSize;

    uint64_t CodePageCount = Math::CeilDivInt(Header_SCO.CodeLength, 16384);
    if(CodePageCount > 100)
        Throw("Too Many Code Pages");


    Header_SCO.CodePages.resize(CodePageCount);
    for (uint32_t i = 0; i < CodePageCount; i++)
    {
        uint32_t CurrentPageSize = 16384;
        if(i == CodePageCount - 1)
            CurrentPageSize = Header_SCO.CodeLength % 16384;

        Header_SCO.CodePages[i].resize(CurrentPageSize);
        memcpy(Header_SCO.CodePages[i].data(),DecompressedData + (i * 16384), CurrentPageSize);
    }


    io.Position = Header_SCO.CodeLength;
    Header_SCO.Natives.resize(Header_SCO.NativesCount);

    if(io.Position + Header_SCO.NativesCount > io.Length - Header_SCO.StaticsCount)
        Throw("Get Natives Out Of Bounds");

    for (int i = 0; i < Header_SCO.NativesCount; i++)
        Header_SCO.Natives[i] = io.ReadUInt32();

    Header_SCO.Statics.resize(Header_SCO.StaticsCount);

    if(io.Position + Header_SCO.StaticsCount > io.Length)
        Throw("Get Statics Out Of Bounds");

    for (int i = 0; i < Header_SCO.StaticsCount; i++)
        Header_SCO.Statics[i] = io.ReadUInt32();

//    FILE* file2 = fopen("outnewdecomp.sco", "wb");
//    fwrite(DecompressedData, 1, DecompressedSize , file2);
//    fclose(file2);
//    cout << "File Written\n";



    return true;

}
else
{
    RSC_Type = 85;
    Header_XSC = XSCHeader();
}
//}

//{ Read XSCHeader

    if(CompressHead == 0x85435352)
    {
        uint32_t HeaderLocation = RSC85Parsing::GetHeaderFormatFromFlag(Header_XSC.Flag);
        switch(HeaderLocation)
        {
            case 0:
                io.Position = 0;
            break;
            case 0xFFFFFFFF:
                Throw("Unknown Header Flag Format");
            break;
            default:
                if(io.Length >= HeaderLocation)
                    io.Position = io.Length - HeaderLocation;
                else Throw("Header Location Out Of Bounds");
            break;
        }

    }
    else
    {
        io.Position = 0;
        if(io.PeekDynamic<uint32_t>() != 0xA8D74300)
        {
            io.Position = io.Length - 4096;
            for(uint32_t pos = 0; pos < 4; pos++)
            {
                if(io.PeekDynamic<uint32_t>() == 0xA8D74300)
                    break;
                else
                {
                    io.Position -= 4096;
                    if(io.Position < 0)
                        Throw("Header Search Failed");
                }
            }
        }
    }

    if(io.PeekDynamic<uint32_t>() != 0xA8D74300)
    {
        cout << "Header Not Found\n";
        return false;
    }

    uint32_t HeaderLoc = io.Position;
//    cout << "Header Location: " << io.Position << endl;
//    cout << "Header Location Page: " << ((float)(io.Length)) / 8192 << endl;
//    cout << "Header Location Rem: " << io.Length - (io.Position)<< endl;

    Header_XSC.PgBase = io.ReadInt32();
    Header_XSC.Unk1 = io.ReadInt32() & 0xFFFFFF;
    Header_XSC.CodeBlocksListOffset = io.ReadInt32() & 0xFFFFFF;
    Header_XSC.CodeLength = io.ReadInt32();
    Header_XSC.ParameterCount = io.ReadInt32();
    Header_XSC.StaticsCount = io.ReadInt32();
    Header_XSC.StaticsOffset = io.ReadInt32() & 0xFFFFFF;
    Header_XSC.GlobalsSignature = io.ReadInt32();
    Header_XSC.NativesCount = io.ReadInt32();
    Header_XSC.NativesOffset = io.ReadInt32() & 0xFFFFFF;



    Header_XSC.CodePagePointers.resize((Header_XSC.CodeLength + (1 << 14) - 1 >> 14));
    Header_XSC.CodePages.resize(Header_XSC.CodePagePointers.size());
    Header_XSC.Natives.resize(Header_XSC.NativesCount);



    for (uint32_t i = 0; i < Header_XSC.CodePagePointers.size(); i++)
    {
        io.Position = Header_XSC.CodeBlocksListOffset + (i * 4);
        Header_XSC.CodePagePointers[i] = io.ReadInt32() & 0xFFFFFF;

        io.Position = Header_XSC.CodePagePointers[i];
        int thisPageLen = PageParsing::GetPageLenAtPage(Header_XSC.CodePagePointers.size(), Header_XSC.CodeLength, i, XboxPageSize);
        Header_XSC.CodePages[i] = io.ReadBytes(thisPageLen);
    }


    io.Position = Header_XSC.NativesOffset;
    Header_XSC.Natives.resize(Header_XSC.NativesCount);
    for (int i = 0; i < Header_XSC.NativesCount; i++)
        Header_XSC.Natives[i] = io.ReadUInt32();

    io.Position = Header_XSC.StaticsOffset;
    Header_XSC.Statics.resize(Header_XSC.StaticsCount);
    for (int i = 0; i < Header_XSC.StaticsCount; i++)
        Header_XSC.Statics[i] = io.ReadUInt32();


//        cout << "Header.PgBase: " << Header_XSC.PgBase << "\n";//0
//        cout << "Header.CodeLength: " << Header_XSC.CodeLength << "\n";//16
//        cout << "Header.ParameterCount: " << Header_XSC.ParameterCount << "\n";//20
//        cout << "Header.StaticsCount: " << Header_XSC.StaticsCount << "\n";//24
//        cout << "Header.StaticsOffset: " << Header_XSC.StaticsOffset << "\n";//28
//        cout << "Header.GlobalsSignature: " << Header_XSC.GlobalsSignature << "\n";//32
//        cout << "Header.NativesCount: " << Header_XSC.NativesCount << "\n";//36


//        vector<uint32_t> pointers = {
//        HeaderLoc,
//        Header_XSC.CodeBlocksListOffset,
//        Header_XSC.CodePagePointers[0],
//        Header_XSC.CodePagePointers[Header_XSC.CodePagePointers.size() - 1],
//        Header_XSC.Unk1,
//        Header_XSC.NativesOffset,
//        Header_XSC.StaticsOffset
//        };
//        vector<const char*> names = {
//        "Header Location: ",
//        "Header.CodeBlocksListOffset: ",
//        "Header.FirstCodeBlockOffest: ",
//        "Header.LastCodeBlockOffest: ",
//        "Header.Unk1: ",
//        "Header.NativesOffset: ",
//        "Header.StaticsOffset: "
//        };
//
//        vector<NamedUint32> sorted = ReorderUint32Vector_SmallToBig(pointers,names);
//
//        for(uint32_t i = 0; i < sorted.size(); i++)
//        {
//            cout << sorted[i].str << sorted[i].val << '\n';
//        }



//}

return true;
}

void RSC::GetCode(string OutPath, uint32_t flags, DecompileType DecompType)
{
    //cout << OutPath << endl << endl;

//{ alloc vars

    //---------init string building types--------------------
    stringstream toRetHeader;
    stringstream toRet;

    stringstream DecompileStringsOut;
    set<string> DecompileStrings;

    stringstream DecompileNativesOut;
    set<uint32_t> DecompileNatives;

    //-----------init floating point precision----------------
    toRetHeader.precision(7);
    toRet.precision(7);

    //{------------init vars----------------------
    struct PCI
    {
        bool Ignored = false;
        bool IsLabelFunction = false;
        int64_t LabelNum;
    };

    vector<int8_t> _codePages;
    set<uint32_t> CustomNativeNames;
    map<int64_t, PCI> PCInformation;
    FILE* file;

    uint32_t FunctionCount = 0, LabelCount = 0, UnusedFunctionNum = 0;

    //}

    //{------------load natives----------------------
    map<uint32_t, boost::tokenizer<boost::char_separator<char>>::iterator> NativeMap;

    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    boost::filesystem::path nativespath = buffer;
    string outnatives = nativespath.parent_path().string();
    std::ifstream NativeFile(outnatives + "\\natives.txt");
    string content( (std::istreambuf_iterator<char>(NativeFile) ),(std::istreambuf_iterator<char>()));
    NativeFile.close();
    if(content == "")
    {
        Throw("Could Not Load natives.txt");
    }

    boost::char_separator<char> sep(":\n");
    boost::tokenizer<boost::char_separator<char>> tokens(content, sep);
    for (boost::tokenizer<boost::char_separator<char>>::iterator tokeni = tokens.begin(); tokeni != tokens.end(); tokeni++)
    {
        uint32_t token1 = stoul(*tokeni);
        tokeni++;
        NativeMap.insert({token1,tokeni});

    }


//}


    vector<vector<uint8_t>> *CodePagesPtr;
    uint32_t *CodeLengthPtr;
    vector<uint32_t> *NativesPtr;
    uint32_t *NativesCountPtr;
    vector<int32_t> *StaticsPtr;
    uint32_t *StaticsCountPtr;
    uint32_t *ParameterCountPtr;


    if(RSC_Type == 2)
    {
        CodePagesPtr = &Header_SCO.CodePages;
        CodeLengthPtr = &Header_SCO.CodeLength;
        NativesPtr = &Header_SCO.Natives;
        NativesCountPtr = &Header_SCO.NativesCount;
        StaticsPtr = &Header_SCO.Statics;
        StaticsCountPtr = &Header_SCO.StaticsCount;
        ParameterCountPtr = &Header_SCO.ParameterCount;
    }
    else//rsc 85 default
    {
        CodePagesPtr = &Header_XSC.CodePages;
        CodeLengthPtr = &Header_XSC.CodeLength;
        NativesPtr = &Header_XSC.Natives;
        NativesCountPtr = &Header_XSC.NativesCount;
        StaticsPtr = &Header_XSC.Statics;
        StaticsCountPtr = &Header_XSC.StaticsCount;
        ParameterCountPtr = &Header_XSC.ParameterCount;
    }

    vector<vector<uint8_t>> &CodePagesRef = *CodePagesPtr;
    uint32_t &CodeLengthRef = *CodeLengthPtr;
    vector<uint32_t> &NativesRef = *NativesPtr;
    uint32_t &NativesCountRef = *NativesCountPtr;
    vector<int32_t> &StaticsRef = *StaticsPtr;
    uint32_t &StaticsCountRef = *StaticsCountPtr;
    uint32_t &ParameterCountRef = *ParameterCountPtr;



    uint32_t len = 0;
    for(uint32_t i = 0; i < CodePagesRef.size(); i++)
    {
        _codePages.resize( len + CodePagesRef[i].size() );
        memcpy(_codePages.data() + len, CodePagesRef[i].data(), CodePagesRef[i].size());
        len += CodePagesRef[i].size();
    }


    int8_t* codepages = _codePages.data();
    uint32_t Position = 0;
//}

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
        uint32_t in = SwapEndian(*(uint32_t*)(codepages + Position));

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
            int switchCase = SwapEndian(ReadInt32());

            uint8_t val1 = ReadByte();
            uint8_t val2 = ReadByte();
            int16_t jumpLoc = val2 | (val1 << 8);

            int64_t fullJumpLoc = jumpLoc + Position;

            if(!(fullJumpLoc <= CodeLengthRef && fullJumpLoc >= 0))
            {
                Throw("Switch Jump Pos Out Of Bounds");
            }

            if (PCInformation.count(fullJumpLoc) == 0)
            {
                PCI ins;
                ins.LabelNum = LabelCount;
                LabelCount++;

                PCInformation.insert({fullJumpLoc, ins});
            }
        }


    };
    auto SaveCallOffset = [&](auto op)
    {
        uint8_t val1 = ReadByte();
        uint8_t val2 = ReadByte();

        int32_t callOffset = CallParsing::GetCallOffset(val2 | (val1 << 8), op);

        if(!(callOffset <= CodeLengthRef && callOffset >= 0))
        {
            cout << "Position: " << Position << '\n';
            cout << "Offset: " << callOffset << " > " << CodeLengthRef << '\n';
            Throw("Call Pos Out Of Bounds");
        }


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


        uint8_t val1 = ReadByte();
        uint8_t val2 = ReadByte();

        int16_t val = val2 | (val1 << 8);

        int64_t fullVal = val + Position;

        bool IsJumpValid = true;

        if(!(fullVal <= CodeLengthRef && fullVal >= 0))
        {
            Throw("Jump Pos Out Of Bounds");
        }


        for(uint32_t i = Position; i < _codePages.size(); i++)
        {
            if(*(uint8_t*)(codepages + i) == OP_Nop)
            {
                if(i + 1 == fullVal)
                {
                    IsJumpValid = false;
                    break;
                }
                else continue;
            }
            else
                break;
        }


        if (PCInformation.count(fullVal) == 0)
        {
            PCI ins;

            if(!IsJumpValid)
                ins.Ignored = true;
            else
            {
                ins.LabelNum = LabelCount;
                LabelCount++;
            }
            PCInformation.insert({fullVal, ins});
        }
    };
    auto WriteLine = [&](auto str)
    {
        toRet << str << "\r\n";
    };
    auto FixString = [&](char * str, uint32_t len, char* tofix)
    {
        uint32_t addval = 0;
        for(uint32_t i = 0; i < len; i++)
        {
            char currentchar = str[i];
            switch(currentchar)
            {
                case '\n':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = 'n';
                    break;
                case '\r':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = 'r';
                    break;
                case '"':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = '"';
                    break;
                case '\\':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = '\\';
                    break;
                default:
                    tofix[i + addval] = currentchar;
                    break;
            }

        }
    };

//}

if(OutPath.find('.') == string::npos)//decompile directory put extention
{
    if(DecompType == DecompileType::DecompileStrings)
        OutPath += ".txt";
    else if(RSC_Type == 85)
        OutPath += ".xsa";
    else if(RSC_Type == 2)
        OutPath += ".sca";
    else Throw("Undefined Output Type");
}

//{ First Loop
    while (Position < _codePages.size())
    {
        OpCode cop = (OpCode)ReadByte();

        if (cop < 0 || (uint8_t)cop > 155)
        {
            cout << "Invalid OpCode (PC: " << Position - 1 << " Op: " << cop << ")\r\n";
            Throw( "Invalid OpCode" );
        }

//        cout << Position - 1 << '\n';
//        cout << _opNames[cop] << " " << cop << '\n';
//        Pause();

        switch (cop)
        {
            case OP_Nop:
                //is last jump pointing to itself for code page jump
            break;
            case OP_PushB:
            case OP_GetArrayP1:
            case OP_GetArray1:
            case OP_SetArray1:
            case OP_GetFrameP1:
            case OP_GetFrame1:
            case OP_SetFrame1:
            case OP_GetStaticP1:
            case OP_GetStatic1:
            case OP_SetStatic1:
            case OP_Add1:
            case OP_Mult1:
            case OP_GetImm1:
            case OP_SetImm1:
            case OP_StrCopy:
            case OP_ItoS:
            case OP_StrAdd:
            case OP_StrAddI:
                AdvPos(1);
                break;
            case OP_PushS:
            case OP_PushB2:
            case OP_Return:
            case OP_Add2:
            case OP_Mult2:
            case OP_GetImm2:
            case OP_SetImm2:
            case OP_GetArrayP2:
            case OP_GetArray2:
            case OP_SetArray2:
            case OP_GetFrameP2:
            case OP_GetFrame2:
            case OP_SetFrame2:
            case OP_GetStaticP2:
            case OP_GetStatic2:
            case OP_SetStatic2:
            case OP_GetGlobalP2:
            case OP_GetGlobal2:
            case OP_SetGlobal2:
                AdvPos(2);
                break;
            case OP_CallNative:
                if (DecompType == DecompileType::OutputNativeHashes)
                {
                    uint16_t NativeData = ReadUInt16();

                    int32_t nativeIndex = NativeParsing::GetIndex(NativeData);
                    //int32_t nativeParamCount = NativeParsing::GetArgCountFromIndex(&NativeData);
                    //bool nativehasRets = NativeParsing::FunctionHasReturn(&NativeData);

                    if(DecompileNatives.find(NativesRef[nativeIndex]) == DecompileNatives.end())
                    {
                        DecompileNatives.insert(NativesRef[nativeIndex]);
                        DecompileNativesOut << NativesRef[nativeIndex] << "\r\n";
                    }
                }
                else
                    AdvPos(2);
                break;
            case OP_PushI24:
            case OP_PushB3:
            case OP_GetGlobalP3:
            case OP_GetGlobal3:
            case OP_SetGlobal3:
                AdvPos(3);
                break;
            case OP_Push:
            case OP_PushF:
                AdvPos(4);
                break;
            case OP_Function:
                AdvPos(3);
                AdvPos(ReadByte());
                break;
            case OP_PushString:
                if (DecompType == DecompileType::DecompileStrings)
                {
                    if(DecompileStrings.find((char*)(codepages + Position)) == DecompileStrings.end())
                    {

                        DecompileStrings.insert((char*)(codepages + Position));
                        DecompileStringsOut << DataConversion::IntToHex(SwapEndian(Hashing::Joaat((char*)(codepages + Position)))) << ':' << (char*)(codepages + Position) << "\r\n";
                    }

                }
                AdvPos(ReadByte());
                break;
            case OP_PushArrayP:
                AdvPos(SwapEndian(ReadInt32()));
                break;
            case OP_Switch:
                SaveSwitchOffsets();
                break;
            case OP_Jump:
            case OP_JumpFalse:
            case OP_JumpEQ:
            case OP_JumpNE:
            case OP_JumpGE:
            case OP_JumpGT:
            case OP_JumpLE:
            case OP_JumpLT:
                SaveJumpOffset();
                break;
            case OP_Call2:
            case OP_Call2h1:
            case OP_Call2h2:
            case OP_Call2h3:
            case OP_Call2h4:
            case OP_Call2h5:
            case OP_Call2h6:
            case OP_Call2h7:
            case OP_Call2h8:
            case OP_Call2h9:
            case OP_Call2hA:
            case OP_Call2hB:
            case OP_Call2hC:
            case OP_Call2hD:
            case OP_Call2hE:
            case OP_Call2hF:
                SaveCallOffset(cop);
                break;

            default:
                break;

        }
    }
//}

if (DecompType == DecompileType::DecompileStrings)
{
    string dir = OutPath.substr(0, OutPath.find_last_of('\\') + 1);
    if(dir != "")
        boost::filesystem::create_directories(dir);

    file = fopen(OutPath.c_str(), "wb");
    if (file != NULL)
    {
        DecompileStringsOut.seekg(0, ios::end);
        fwrite(DecompileStringsOut.str().c_str(), 1, DecompileStringsOut.tellg(), file);
        fclose(file);
    }
    else Throw("Output File Could Not Be Opened");
    return;
}
else if (DecompType == DecompileType::OutputNativeHashes)
{
    file = fopen("NativeHashes.txt", "ab");
    DecompileNativesOut.seekg(0, ios::end);
    fwrite(DecompileNativesOut.str().c_str(), 1, DecompileNativesOut.tellg(), file);
    fclose(file);
    return;
}

if(ParameterCountRef > 0)
{
    toRetHeader << "SetParamCount " << ParameterCountRef << "\r\n";
    if(RSC_Type == 2)
    {
        if(Header_SCO.GlobalsCount == 0)
            toRetHeader << "\r\n";
    }
    else toRetHeader << "\r\n";
}

if(RSC_Type == 2)
{
    if(Header_SCO.GlobalsCount > 0)
    {
        toRetHeader << "RegisterGlobals " << Header_SCO.GlobalsCount << "\r\n\r\n";
    }
}

if (StaticsRef.size() > 0)
{
    toRetHeader << "//> Default Static Information\r\nSetStaticsCount " << StaticsRef.size() << "\r\n";

    bool hadAnyNonZeroStatics = false;
    //bool scriptHasParameters = Header_XSC.ParameterCount > 0;

    if (ParameterCountRef > 0)
    {
        uint32_t i = StaticsRef.size() - ParameterCountRef, index = 0;
        if(i < 0)
            Throw("Script has Too Many Parameters and Not Enough Statics");

        for (; index < ParameterCountRef;i++,index++)
            toRetHeader << "SetStaticName " << i << " ScriptParameter" << index << "\r\n";
        toRetHeader << "\r\n";
    }

    for (uint32_t i = 0; i < StaticsRef.size(); i++)
        if (StaticsRef[i] != 0)
        {
            hadAnyNonZeroStatics = true;
            toRetHeader << "SetDefaultStatic " << i << " " << StaticsRef[i] << "\r\n";
        }
    toRetHeader << "//<\r\n\r\n";
}

//{ Main Loop
    bool WasLastLineALabel = false, UsesCustomNativeNames = false, WasLastLabelANopLabel = false;
    Position = 0;
    while (Position < _codePages.size())
    {

        uint32_t beforeOpCodePC = Position;
        OpCode cop = (OpCode)ReadByte();

        if (cop < 0 || (uint8_t)cop > 155)
        {
            cout << "Invalid OpCode " << cop << "\r\n";
            //FILE* file = fopen("C:\\Users\\Rocko\\Desktop\\out.txt", "wb");
            //toRet.seekg(0, ios::end);
            //fwrite(toRet.str().c_str(), 1, toRet.tellg(), file);
            //fclose(file);
            Throw( "Invalid OpCode" );
        }


        if (PCInformation.find(beforeOpCodePC) != PCInformation.end())
        {
            if(PCInformation[beforeOpCodePC].IsLabelFunction)
            {
                toRet << "//<\r\n" << "\r\n:Function_" << PCInformation[beforeOpCodePC].LabelNum << "//>\r\n";
                WasLastLineALabel = true;
            }
            else if(!PCInformation[beforeOpCodePC].Ignored)
            {
                toRet << "\r\n:Label_" << PCInformation[beforeOpCodePC].LabelNum << "\r\n";
                WasLastLineALabel = true;
            }
            else WasLastLineALabel = false;
        }
        else WasLastLineALabel = false;

        if(WasLastLineALabel && cop == OP_Nop)
        {
            WasLastLabelANopLabel = true;
        }

        if (HasFlag(DecompileFlag::ShowPC))
            toRet << "[PC -> " << Position - 1 << "] ";

        switch (cop)
        {
            case OP_Nop:
                break;//disable nop display
            case OP_PushB:
            case OP_GetArrayP1:
            case OP_GetArray1:
            case OP_SetArray1:
            case OP_GetFrameP1:
            case OP_GetFrame1:
            case OP_SetFrame1:
            case OP_Add1:
            case OP_Mult1:
            case OP_GetImm1:
            case OP_SetImm1:
            case OP_StrCopy:
            case OP_ItoS:
            case OP_StrAdd:
            case OP_StrAddI:
                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte()) << "\r\n";
                break;
            case OP_GetStaticP1:
            case OP_GetStatic1:
            case OP_SetStatic1:
                if (ParameterCountRef > 0)
                {
                    uint8_t tryParseByte = ReadByte();
                    if (tryParseByte >= StaticsRef.size() - ParameterCountRef)
                        toRet << _opNames[(uint8_t)cop] << " ScriptParameter" << to_string(tryParseByte - (StaticsRef.size() - ParameterCountRef)) << "\r\n";
                    else
                        toRet << _opNames[(uint8_t)cop] << " " << to_string(tryParseByte) << "\r\n";
                }
                else
                    toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte()) << "\r\n";
                break;
            case OP_PushS:
                toRet << _opNames[(uint8_t)cop] << " " << SwapEndian(ReadInt16()) << "\r\n";
                break;
            case OP_Add2:
            case OP_Mult2:
            case OP_GetImm2:
            case OP_SetImm2:
            case OP_GetArrayP2:
            case OP_GetArray2:
            case OP_SetArray2:
            case OP_GetFrameP2:
            case OP_GetFrame2:
            case OP_SetFrame2:
            case OP_GetGlobalP2:
            case OP_GetGlobal2:
            case OP_SetGlobal2:
                toRet << _opNames[(uint8_t)cop] << " " << SwapEndian(ReadUInt16()) << "\r\n";
                break;
            case OP_GetStaticP2:
            case OP_GetStatic2:
            case OP_SetStatic2:
                if (ParameterCountRef > 0)
                {
                    uint32_t tryParseUShort = SwapEndian(ReadUInt16());
                    if (tryParseUShort >= StaticsRef.size() - ParameterCountRef)
                        toRet << _opNames[(uint8_t)cop] << " ScriptParameter" << to_string(tryParseUShort - (StaticsRef.size() - ParameterCountRef)) << "\r\n";
                    else
                        toRet << _opNames[(uint8_t)cop] << " " << to_string(tryParseUShort) << "\r\n";
                }
                else
                    toRet << _opNames[(uint8_t)cop] << " " << SwapEndian(ReadUInt16()) << "\r\n";
                break;
            case OP_PushB2:
            case OP_Return:
                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte());
                toRet << " " << to_string(ReadByte()) << "\r\n";
                break;
            case OP_ReturnP0R0:
            case OP_ReturnP0R1:
            case OP_ReturnP0R2:
            case OP_ReturnP0R3:
            case OP_ReturnP1R0:
            case OP_ReturnP1R1:
            case OP_ReturnP1R2:
            case OP_ReturnP1R3:
            case OP_ReturnP2R0:
            case OP_ReturnP2R1:
            case OP_ReturnP2R2:
            case OP_ReturnP2R3:
            case OP_ReturnP3R0:
            case OP_ReturnP3R1:
            case OP_ReturnP3R2:
            case OP_ReturnP3R3:
            {
                uint32_t base = cop - 122;
                toRet << "Return " << base / 4  << " "<< base % 4 << "\r\n";
            }
                break;
            case OP_PushB3:
                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte());
                toRet << " " << to_string(ReadByte()) << " ";
                toRet << to_string(ReadByte()) << "\r\n";
                break;
            case OP_CallNative:
            {
                uint16_t NativeData = ReadUInt16();

                int32_t nativeIndex = NativeParsing::GetIndex(NativeData);
                int32_t nativeParamCount = NativeParsing::GetArgCountFromIndex(&NativeData);
                bool nativehasRets = NativeParsing::FunctionHasReturn(&NativeData);

                toRet << _opNames[(uint8_t)cop] << " ";

                if(NativeMap.find(NativesRef[nativeIndex]) != NativeMap.end())
                {
                    string NativeName = *NativeMap.find(NativesRef[nativeIndex])->second;
                    if(NativeName.at(0) == '_')
                    {
                        uint32_t NativeVal = SwapEndian(NativesRef[nativeIndex]);
                        char * NativeHash = IntToHex(NativeVal);

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

                        toRet << NativeName << " " << nativeParamCount << " " << nativehasRets << "//0x" << NativeHash;
                    }
                    else
                        toRet << NativeName << " " << nativeParamCount << " " << nativehasRets;
                }
                else
                {
                    toRet << "unk_0x" << IntToHex(SwapEndian((uint32_t)NativesRef[nativeIndex])) << " " << nativeParamCount << " " << nativehasRets;
                }

                if (HasFlag(DecompileFlag::ShowNativeInfo))
                    toRet << "//NI: " << nativeIndex << "\r\n";
                else
                    toRet << "\r\n";
            }
            break;
            case OP_GetGlobalP3:
            case OP_GetGlobal3:
            case OP_SetGlobal3:
            case OP_PushI24:
                toRet << _opNames[(uint8_t)cop] << " " << ReadInt24() << "\r\n";
                break;
            case OP_Push:
                toRet << _opNames[(uint8_t)cop] << " " << (int32_t)SwapEndian(ReadInt32()) << "\r\n";
                break;
            case OP_PushF:
                toRet << _opNames[(uint8_t)cop] << " " << SwapEndian(ReadSingle()) << "\r\n";
                break;
            case OP_Function:
            {
                if(!WasLastLineALabel)
                {
                    if(!WasLastLabelANopLabel)
                    {
                        if(UnusedFunctionNum == 0)
                            toRet << ":MainFunction//>\r\n";
                        else
                            toRet << "//<\r\n\r\n:UnusedFunction_" << UnusedFunctionNum << "//> PCall Location: " << Position - 1 << "\r\n";
                        UnusedFunctionNum++;
                    }
                }

                toRet << _opNames[(uint8_t)cop] << " " << to_string(ReadByte()) << " ";
                toRet << SwapEndian(ReadInt16()) << "\r\n";
                AdvPos(ReadByte());
                break;
            }
            case OP_Switch:
            {

                uint8_t switchCaseCount = ReadByte();

                toRet << _opNames[(uint8_t)cop];
                for (uint32_t i = 0; i < switchCaseCount; i++)
                {

                    int32_t switchCase = SwapEndian(ReadInt32());

                    uint16_t switchVal = SwapEndian(ReadInt16());
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
            case OP_Jump:
            case OP_JumpFalse:
            case OP_JumpEQ:
            case OP_JumpNE:
            case OP_JumpGT:
            case OP_JumpGE:
            case OP_JumpLT:
            case OP_JumpLE:
            {
                int16_t jumpLoc = SwapEndian(ReadInt16());
                int32_t fullJumpLoc = (int32_t)(jumpLoc + Position);
                string flag = HasFlag(DecompileFlag::ShowJumpPosition) ? "//JPC: " + to_string(fullJumpLoc) : "";

                if(PCInformation[fullJumpLoc].IsLabelFunction)
                    toRet << _opNames[(uint8_t)cop] << " @Function_" << PCInformation[fullJumpLoc].LabelNum << flag << "\r\n";
                else if(!PCInformation[fullJumpLoc].Ignored)
                    toRet << _opNames[(uint8_t)cop] << " @Label_" << PCInformation[fullJumpLoc].LabelNum << flag << "\r\n";
            }
            break;
            case OP_Call2:
            case OP_Call2h1:
            case OP_Call2h2:
            case OP_Call2h3:
            case OP_Call2h4:
            case OP_Call2h5:
            case OP_Call2h6:
            case OP_Call2h7:
            case OP_Call2h8:
            case OP_Call2h9:
            case OP_Call2hA:
            case OP_Call2hB:
            case OP_Call2hC:
            case OP_Call2hD:
            case OP_Call2hE:
            case OP_Call2hF:
            {
                uint8_t val1 = ReadByte();
                uint8_t val2 = ReadByte();
                int32_t callOffset = CallParsing::GetCallOffset(val2 | (val1 << 8), cop);

                string flag = HasFlag(DecompileFlag::ShowCallPosition) ? "//CPC: " + to_string(callOffset) : "";
                toRet << "Call @Function_" << PCInformation[callOffset].LabelNum << flag << "\r\n";
            }
            break;
            case OP_PushStringNull:
                toRet << "PushString \"\"" << "\r\n";
            break;
            case OP_PushString:
            {
                uint8_t len = ReadByte();
                char* StringFixed = new char[len*2];
                FixString((char*)(codepages + Position), len, StringFixed);

                toRet << "PushString " << "\"" << StringFixed << "\"\r\n";
                AdvPos(len);
            }
            break;
            case OP_PushArrayP:
            {
                int32_t len = SwapEndian(ReadInt32());

                toRet << "PushArrayP";

                if(len % 4 != 0)
                {
                    for(uint32_t i = 0; i < len; i++)
                    {
                        toRet << ' ' << ReadByte();
                    }
                }
                else
                {
                    uint32_t size = len / 4;
                    for(uint32_t i = 0; i < size; i++)
                    {
                        toRet << ' ' << (int32_t)SwapEndian(ReadInt32());
                    }

                }
                toRet << "\r\n";
            }
            break;
            case OP_Push_0:
            case OP_Push_1:
            case OP_Push_2:
            case OP_Push_3:
            case OP_Push_4:
            case OP_Push_5:
            case OP_Push_6:
            case OP_Push_7:
                toRet << _opNames[(uint8_t)cop] << "\r\n";
                break;
            default:
                toRet << _opNames[(uint8_t)cop] << "\r\n";
                break;


        }


    }

///fix for rockstar jumping to the end of a script like a bellend
if (PCInformation.find(Position) != PCInformation.end())
{
    if(!PCInformation[Position].Ignored)
        toRet << "\r\n:Label_" << PCInformation[Position].LabelNum << "\r\n";
}

//}

//{ Write File

    string dir = OutPath.substr(0, OutPath.find_last_of('\\') + 1);
    if(dir != "")
        boost::filesystem::create_directories(dir);

    file = fopen(OutPath.c_str(), "wb");
    if (file != NULL)
    {
        if(UsesCustomNativeNames)
        {
            toRetHeader << "//<\r\n";
            toRetHeader << "\r\n";
        }
        toRetHeader.seekg(0, ios::end);
        fwrite(toRetHeader.str().c_str(), 1, toRetHeader.tellg(), file);

        toRet << "//<";
        toRet.seekg(0, ios::end);
        fwrite(toRet.str().c_str(), 1, toRet.tellg(), file);

        fclose(file);
    }
    else Throw("Output File Could Not Be Opened");
//}

}

void RSC::GetHighLevelCode(string OutPath, uint32_t flags)
{

//{ alloc vars

    //---------init string building types--------------------
    stringstream toRetHeader;
    stringstream toRet;

    //-----------init floating point precision----------------
    toRetHeader.precision(7);
    toRet.precision(7);

    //{------------init vars----------------------
    struct PCI
    {
        bool Ignored = false;
        bool IsLabelFunction = false;
        bool IsLabelCase = false;
        bool StatementEnd = false;
        int64_t LabelNum;
        int32_t StatementEndCount = 0;
        vector<int32_t> SwitchStatementCase;

    };

    stack<string> codestack;
    vector<int8_t> _codePages;
    set<uint32_t> CustomNativeNames;
    map<int64_t, PCI> PCInformation;
    map<uint32_t, uint16_t> FunctionRets;//pc location of func , ret count
    FILE* file;

    uint32_t FunctionCount = 0, LabelCount = 0, UnusedFunctionNum = 0, TabCount = 0;
    int32_t LastFunctionPc = -1;
    uint8_t CurrentFuncParamCount = 0;
    bool WasReturnHit = false;

    //}

    //{------------load natives----------------------
    map<uint32_t, boost::tokenizer<boost::char_separator<char>>::iterator> NativeMap;

    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    boost::filesystem::path nativespath = buffer;
    string outnatives = nativespath.parent_path().string();
    std::ifstream NativeFile(outnatives + "\\natives.txt");
    string content( (std::istreambuf_iterator<char>(NativeFile) ),(std::istreambuf_iterator<char>()));
    NativeFile.close();
    if(content == "")
    {
        Throw("Could Not Load natives.txt");
    }

    boost::char_separator<char> sep(":\n");
    boost::tokenizer<boost::char_separator<char>> tokens(content, sep);
    for (boost::tokenizer<boost::char_separator<char>>::iterator tokeni = tokens.begin(); tokeni != tokens.end(); tokeni++)
    {
        uint32_t token1 = stoul(*tokeni);
        tokeni++;
        NativeMap.insert({token1,tokeni});

    }


//}

    //{ ------------load script types----------------------
    vector<vector<uint8_t>> *CodePagesPtr;
    uint32_t *CodeLengthPtr;
    vector<uint32_t> *NativesPtr;
    uint32_t *NativesCountPtr;
    vector<int32_t> *StaticsPtr;
    uint32_t *StaticsCountPtr;
    uint32_t *ParameterCountPtr;

    if(RSC_Type == 2)
    {
        CodePagesPtr = &Header_SCO.CodePages;
        CodeLengthPtr = &Header_SCO.CodeLength;
        NativesPtr = &Header_SCO.Natives;
        NativesCountPtr = &Header_SCO.NativesCount;
        StaticsPtr = &Header_SCO.Statics;
        StaticsCountPtr = &Header_SCO.StaticsCount;
        ParameterCountPtr = &Header_SCO.ParameterCount;
    }
    else//rsc 85 default
    {
        CodePagesPtr = &Header_XSC.CodePages;
        CodeLengthPtr = &Header_XSC.CodeLength;
        NativesPtr = &Header_XSC.Natives;
        NativesCountPtr = &Header_XSC.NativesCount;
        StaticsPtr = &Header_XSC.Statics;
        StaticsCountPtr = &Header_XSC.StaticsCount;
        ParameterCountPtr = &Header_XSC.ParameterCount;
    }

    vector<vector<uint8_t>> &CodePagesRef = *CodePagesPtr;
    uint32_t &CodeLengthRef = *CodeLengthPtr;
    vector<uint32_t> &NativesRef = *NativesPtr;
    uint32_t &NativesCountRef = *NativesCountPtr;
    vector<int32_t> &StaticsRef = *StaticsPtr;
    uint32_t &StaticsCountRef = *StaticsCountPtr;
    uint32_t &ParameterCountRef = *ParameterCountPtr;
//}

    //{------------load codepages into one array----------------------
    uint32_t len = 0;
    for(uint32_t i = 0; i < CodePagesRef.size(); i++)
    {
        _codePages.resize( len + CodePagesRef[i].size() );
        memcpy(_codePages.data() + len, CodePagesRef[i].data(), CodePagesRef[i].size());
        len += CodePagesRef[i].size();
    }
    int8_t* codepages = _codePages.data();
    uint32_t Position = 0;
    //}


//}

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
    auto ReadByte = [&]() -> uint8_t
    {
        uint8_t ret = *(uint8_t*)(codepages + Position);
        Position++;
        return ret;
    };
    auto ReadInt16 = [&]() -> int16_t
    {
        int16_t ret = SwapEndian(*(int16_t*)(codepages + Position));
        Position+=2;
        return ret;
    };
    auto ReadUInt16 = [&]() -> uint16_t
    {
        uint16_t ret = SwapEndian(*(uint16_t*)(codepages + Position));
        Position+=2;
        return ret;
    };
    auto ReadInt24 = [&]() -> uint32_t
    {
        uint32_t in = SwapEndian(*(uint32_t*)(codepages + Position));

        //printf("%x2\n", in);
        Position += 3;
        return in >> 8;
    };
    auto GetInt24 = [&](auto val) -> uint32_t
    {
        return val >> 8;
    };
    auto ReadInt32 = [&]() -> int32_t
    {
        uint32_t ret = SwapEndian(*(uint32_t*)(codepages + Position));
        Position+=4;
        return ret;
    };
    auto ReadSingle = [&]() -> float
    {
        float ret = SwapEndian(*(float*)(codepages + Position));
        Position+=4;
        return ret;
    };

    auto GetTab = [&]() -> string
    {
        string ret(TabCount, '\t');
        return ret;
    };


    auto Clear = [&]()
    {
        while (!codestack.empty() )
        {
            codestack.pop();
        }
    };
    auto ClearAndPrint = [&]()
    {
        if(!codestack.empty())
        {
            toRet << GetTab() <<  "//Warning items were left on the stack";
            while (!codestack.empty())
            {
                toRet << " " << codestack.top();
                codestack.pop();
            }
            toRet << "\r\n";
        }
    };

    auto PopFixed = [&]() -> string
    {
        string ret = codestack.top();
        codestack.pop();
        return ret;
    };
    auto Pop = [&]() -> string
    {
        if(!codestack.empty())
            return PopFixed();
        return "UnkStack";
    };
    auto Dup = [&](auto count)
    {
        count++;
        toRet << GetTab() << "int StackVar = " << Pop() << ";\r\n";
        for(uint32_t i = 0; i < (uint32_t)count; i++)
            codestack.push("StackVar");
    };
    auto Peek = [&]() -> string
    {
        if(!codestack.empty())
            return codestack.top();
        return "UnkStack";
    };

    auto StackRev = [&](auto count)
    {
        string buffer[(uint32_t)count];

        for(int i = 0; i < count; i++)
            buffer[i] = Pop();
        for (int i = 0; i < count; i++)
            codestack.push(buffer[i]);

    };



    auto PushUInt = [&](auto val)
    {
        codestack.push(to_string((uint32_t)val));
    };
    auto PushGlobal = [&](auto str, auto val)
    {
        codestack.push(str + to_string((uint32_t)val) + ']');
    };

    auto PushF = [&](auto val)
    {
        codestack.push(to_string((float)val) + 'f');
    };

    auto PushOperandUInt = [&](auto operand, auto val)
    {
        codestack.push('(' + Pop() + (string)operand + to_string((uint32_t)val) + ')');
    };
    auto PushOperand = [&](auto operand)
    {
        codestack.push( '(' + Pop() + (string)operand + Pop() + ')');
    };
    auto PushPreOperand = [&](auto operand)
    {
        codestack.push((string)operand + '(' + Pop() + ')');
    };

    auto PushVOperand = [&](auto operand)
    {
        string stack6 = Pop();
        string stack5 = Pop();
        string stack4 = Pop();
        string stack3 = Pop();
        string stack2 = Pop();
        string stack1 = Pop();

        codestack.push(stack1 + (const char*)operand + stack4);
        codestack.push(stack2 + (const char*)operand + stack5);
        codestack.push(stack3 + (const char*)operand + stack6);
    };
    auto PushVPreOperand = [&](auto operand)
    {
        string stack3 = Pop();
        string stack2 = Pop();
        string stack1 = Pop();

        codestack.push((const char*)operand + stack1);
        codestack.push((const char*)operand + stack2);
        codestack.push((const char*)operand + stack3);
    };
    auto PushArray = [&](auto val, auto typestr)
    {
        string arrptr = Pop();
        //if(*arrptr.c_str() != '&')
        //    cout << "Warning Arrptr is not a ptr\n";

        uint32_t structsize = val;
        if(structsize == 1)
            codestack.push(typestr + arrptr + ")[" + Pop() + ']');
        else
            codestack.push(typestr + arrptr + ")[" + Pop() + "][0]");
    };
    auto PrintArray = [&](auto val)
    {
        string arrptr = Pop();
        if(*arrptr.c_str() != '&')
            cout << "Warning Arrptr is not a ptr\n";

        uint32_t structsize = val;
        if(structsize == 1)
            toRet << GetTab() << '(' << arrptr << ")[" << Pop() << "] = " << Pop() << ";\r\n";
        else
            toRet << GetTab() << '(' << arrptr << ")[" << Pop() << "][0] = " << Pop() << ";\r\n";
    };

    auto PushVar = [&](auto VarIndex, auto prefix)
    {
        if(VarIndex < CurrentFuncParamCount)
            codestack.push(string(prefix) + "Param_" + to_string(VarIndex));
        else if(VarIndex < CurrentFuncParamCount + 2)
            codestack.push(string(prefix) + "VmVar[" + to_string(VarIndex - CurrentFuncParamCount) + "]");
        else
            codestack.push(string(prefix) + "Var[" + to_string(VarIndex - CurrentFuncParamCount - 2) + "]");// - 2 for vm vars
    };
    auto PrintVar = [&](auto VarIndex)
    {
        if(VarIndex < CurrentFuncParamCount)
            toRet << GetTab() << "Param_" << +VarIndex;
        else if(VarIndex < CurrentFuncParamCount + 2)
            toRet << GetTab() << "VmVar[" << VarIndex - CurrentFuncParamCount << ']';
        else
            toRet << GetTab() << "Var[" << VarIndex - CurrentFuncParamCount - 2 << ']';// - 2 for vm vars

        toRet << " = " << Pop() << ";\r\n";
    };

    auto PrintRet = [&](auto PopCount, auto RetCount)
    {
        toRet << GetTab() << "return";
        if(RetCount > 0)
        {
            StackRev(RetCount);
            for(uint32_t i = 0; i < RetCount; i++)
            {
                if(i == 0)
                    toRet << " " << Pop();
                else
                    toRet << ", " << Pop();
            }
        }
        toRet << ";\r\n";
    };

    auto PrintCall = [&](auto Name, auto ParamCount)
    {
        toRet << GetTab() << Name << '(';

        if(ParamCount > 1)
            StackRev(ParamCount);

        for(uint32_t i = 0; i < ParamCount; i++)
        {
            if(i == 0)
                toRet << Pop();
            else
                toRet << ", " << Pop();
        }
        toRet << ");\r\n";
    };
    auto PushCall = [&](auto Name, auto ParamCount)
    {
        string ret =  string(Name) + '(';

        if(ParamCount > 1)
            StackRev(ParamCount);

        for(uint32_t i = 0; i < ParamCount; i++)
        {
            if(i == 0)
               ret += Pop();
            else
                ret += ", " + Pop();
        }
        ret += ')';
        codestack.push(ret);
    };
    auto PushCallArray = [&](auto Name, auto ParamCount, auto RetCount)
    {
        string ret =  Name + '(';

        if(ParamCount > 1)
            StackRev(ParamCount);

        for(uint32_t i = 0; i < ParamCount; i++)
        {
            if(i == 0)
               ret += Pop();
            else
                ret += ", " + Pop();
        }
        ret += ");\r\n";
        toRet << GetTab() << "int RetArray[" << RetCount << "] = " << ret;

        for(uint32_t i = 0; i < RetCount; i++)
        {
            codestack.push("RetArray[" + to_string(i) + "]");
        }

    };

    auto PrintIfOperand = [&](auto Operand)
    {
        toRet << GetTab() << "if(" << Pop() << Operand << Pop() << ")\r\n" << GetTab() << "{\r\n";

        int16_t jumpLoc = ReadInt16();
        int32_t fullJumpLoc = (int32_t)(jumpLoc + Position);

        map<int64_t, PCI>::iterator pos = PCInformation.find(fullJumpLoc);
        if (pos != PCInformation.end())
            pos->second.StatementEndCount++;

        TabCount++;
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
            int switchCase = SwapEndian(ReadInt32());

            uint8_t val1 = ReadByte();
            uint8_t val2 = ReadByte();
            int16_t jumpLoc = val2 | (val1 << 8);

            int64_t fullJumpLoc = jumpLoc + Position;

            if(!(fullJumpLoc <= CodeLengthRef && fullJumpLoc >= 0))
            {
                Throw("Switch Jump Pos Out Of Bounds");
            }

            if (PCInformation.count(fullJumpLoc) == 0)
            {
                PCI ins;
                ins.LabelNum = LabelCount;
                LabelCount++;

                PCInformation.insert({fullJumpLoc, ins});
            }
        }


    };
    auto FindFuncOffsetFromCall = [&](auto offset) -> int32_t
    {
        for(uint32_t i = offset; i < CodeLengthRef; i++)
        {

            switch(codepages[i])
            {
                case OP_Nop: continue;
                case OP_Jump: i+=2; continue;
                case OP_Function: return i;
                default: return -1;

            }
        }
        return -1;
    };

    auto SaveCallOffset = [&](auto op)
    {
        uint8_t val1 = ReadByte();
        uint8_t val2 = ReadByte();

        int32_t callOffset = CallParsing::GetCallOffset(val2 | (val1 << 8), op);

        //parse calloffset to func offset then if og calloff valid modify

        if(!(callOffset <= CodeLengthRef && callOffset >= 0))
        {
            cout << "Position: " << Position << '\n';
            cout << "Offset: " << callOffset << " > " << CodeLengthRef << '\n';
            Throw("Call Pos Out Of Bounds");
        }



        int32_t NewCallOffset = FindFuncOffsetFromCall(callOffset);
        //cout << "callpc: " << NewCallOffset << endl;

        if(!(NewCallOffset <= CodeLengthRef && NewCallOffset >= 0))
        {
            cout << "Position: " << Position << '\n';
            cout << "Offset: " << NewCallOffset << " > " << CodeLengthRef << '\n';
            Throw("NewCall Pos Out Of Bounds");
        }


        map<int64_t, PCI>::iterator pos = PCInformation.find(NewCallOffset);
        if (pos == PCInformation.end())
        {
            PCI ins;
            ins.IsLabelFunction = true;

            ins.LabelNum = FunctionCount;
            FunctionCount++;

            PCInformation.insert({NewCallOffset, ins});
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
        uint8_t val1 = ReadByte();
        uint8_t val2 = ReadByte();
        int16_t val = val2 | (val1 << 8);

        int64_t fullVal = val + Position;

        bool IsJumpValid = true;

        if(!(fullVal <= CodeLengthRef && fullVal >= 0))
        {
            Throw("Jump Pos Out Of Bounds");
        }

        for(uint32_t i = Position; i < _codePages.size(); i++)
        {
            if(*(uint8_t*)(codepages + i) == OP_Nop)
            {
                if(i + 1 == fullVal)
                {
                    IsJumpValid = false;
                    break;
                }
                else continue;
            }
            else
                break;
        }

        map<int64_t, PCI>::iterator pos = PCInformation.find(fullVal);
        if (pos == PCInformation.end())
        {
            PCI ins;

            if(!IsJumpValid)
                ins.Ignored = true;
            else
            {
                ins.LabelNum = LabelCount;
                LabelCount++;
            }
            PCInformation.insert({fullVal, ins});
        }

    };
    auto SaveJumpOffsetParam = [&]()
    {


        uint8_t val1 = ReadByte();
        uint8_t val2 = ReadByte();

        int16_t val = val2 | (val1 << 8);

        int64_t fullVal = val + Position;

        bool IsJumpValid = true;

        if(!(fullVal <= CodeLengthRef && fullVal >= 0))
        {
            Throw("Jump Pos Out Of Bounds");
        }


        for(uint32_t i = Position; i < _codePages.size(); i++)
        {
            if(*(uint8_t*)(codepages + i) == OP_Nop)
            {
                if(i + 1 == fullVal)
                {
                    IsJumpValid = false;
                    break;
                }
                else continue;
            }
            else
                break;
        }


        map<int64_t, PCI>::iterator pos = PCInformation.find(fullVal);
        if (pos == PCInformation.end())
        {
            PCI ins;

            if(!IsJumpValid)
                ins.Ignored = true;
            else
            {
                ins.StatementEnd = true;
                ins.LabelNum = LabelCount;
                LabelCount++;
            }
            PCInformation.insert({fullVal, ins});
        }
        else
        {
            if(!pos->second.StatementEnd)
            {
                pos->second.StatementEnd = true;
            }
        }
    };

    auto WriteLine = [&](auto str)
    {
        toRet << str << "\r\n";
    };
    auto FixString = [&](char * str, uint32_t len, char* tofix)
    {
        uint32_t addval = 0;
        for(uint32_t i = 0; i < len; i++)
        {
            char currentchar = str[i];
            switch(currentchar)
            {
                case '\n':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = 'n';
                    break;
                case '\r':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = 'r';
                    break;
                case '"':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = '"';
                    break;
                case '\\':
                    tofix[i + addval] = '\\';
                    addval++;
                    tofix[i + addval] = '\\';
                    break;
                default:
                    tofix[i + addval] = currentchar;
                    break;
            }

        }
    };

//}

//{ First Loop
    while (Position < _codePages.size())
    {
        OpCode cop = (OpCode)ReadByte();

        if (cop < 0 || (uint8_t)cop > 155)
        {
            cout << "Invalid OpCode (PC: " << Position - 1 << " Op: " << cop << ")\r\n";
            Throw( "Invalid OpCode" );
        }

//        cout << Position - 1 << '\n';
//        cout << _opNames[cop] << " " << cop << '\n';
//        Pause();

        switch (cop)
        {
            case OP_Nop:
                //is last jump pointing to itself for code page jump
            break;
            case OP_PushB:
            case OP_GetArrayP1:
            case OP_GetArray1:
            case OP_SetArray1:
            case OP_GetFrameP1:
            case OP_GetFrame1:
            case OP_SetFrame1:
            case OP_GetStaticP1:
            case OP_GetStatic1:
            case OP_SetStatic1:
            case OP_Add1:
            case OP_Mult1:
            case OP_GetImm1:
            case OP_SetImm1:
            case OP_StrCopy:
            case OP_ItoS:
            case OP_StrAdd:
            case OP_StrAddI:
                AdvPos(1);
                break;
            case OP_PushS:
            case OP_PushB2:
            case OP_Add2:
            case OP_Mult2:
            case OP_GetImm2:
            case OP_SetImm2:
            case OP_GetArrayP2:
            case OP_GetArray2:
            case OP_SetArray2:
            case OP_GetFrameP2:
            case OP_GetFrame2:
            case OP_SetFrame2:
            case OP_GetStaticP2:
            case OP_GetStatic2:
            case OP_SetStatic2:
            case OP_GetGlobalP2:
            case OP_GetGlobal2:
            case OP_SetGlobal2:
                AdvPos(2);
                break;
            case OP_CallNative:
                AdvPos(2);
                break;
            case OP_PushI24:
            case OP_PushB3:
            case OP_GetGlobalP3:
            case OP_GetGlobal3:
            case OP_SetGlobal3:
                AdvPos(3);
                break;
            case OP_Push:
            case OP_PushF:
                AdvPos(4);
                break;
            case OP_Function:
                if(!WasReturnHit)
                {
                    if(LastFunctionPc != -1)
                    {
                        FunctionRets.insert({LastFunctionPc, 0xFFFF});
                        cout << "Warning: Function at location " << LastFunctionPc << " did not have a return\n";
                    }
                }
                LastFunctionPc = Position - 1;
                WasReturnHit = false;

                AdvPos(3);
                AdvPos(ReadByte());
                break;
            case OP_PushString:
                AdvPos(ReadByte());
                break;
            case OP_PushArrayP:
                AdvPos(ReadInt32());
                break;
            case OP_Switch:
                SaveSwitchOffsets();
                break;
            case OP_Jump:
                SaveJumpOffset();
                break;
            case OP_JumpFalse:
            case OP_JumpEQ:
            case OP_JumpNE:
            case OP_JumpGE:
            case OP_JumpGT:
            case OP_JumpLE:
            case OP_JumpLT:
                SaveJumpOffsetParam();
                break;
            case OP_Call2:
            case OP_Call2h1:
            case OP_Call2h2:
            case OP_Call2h3:
            case OP_Call2h4:
            case OP_Call2h5:
            case OP_Call2h6:
            case OP_Call2h7:
            case OP_Call2h8:
            case OP_Call2h9:
            case OP_Call2hA:
            case OP_Call2hB:
            case OP_Call2hC:
            case OP_Call2hD:
            case OP_Call2hE:
            case OP_Call2hF:
                SaveCallOffset(cop);
                break;
            case OP_Return:
                if(!WasReturnHit)
                {
                    AdvPos(1);
                    uint8_t k = ReadByte();

//                    cout << "retcount: " << k << endl;
//                    cout << "functionpc: " << LastFunctionPc << endl;
//                    Pause();

                    FunctionRets.insert({LastFunctionPc, k});
                    WasReturnHit = true;
                }
                else
                    AdvPos(2);
            break;
            case OP_ReturnP0R0:
            case OP_ReturnP0R1:
            case OP_ReturnP0R2:
            case OP_ReturnP0R3:
            case OP_ReturnP1R0:
            case OP_ReturnP1R1:
            case OP_ReturnP1R2:
            case OP_ReturnP1R3:
            case OP_ReturnP2R0:
            case OP_ReturnP2R1:
            case OP_ReturnP2R2:
            case OP_ReturnP2R3:
            case OP_ReturnP3R0:
            case OP_ReturnP3R1:
            case OP_ReturnP3R2:
            case OP_ReturnP3R3:
            {
                if(!WasReturnHit)
                {
                    uint32_t base = cop - 122;
//                    cout << "retcount: " << base % 4 << endl;
//                    cout << "functionpc: " << LastFunctionPc << endl;
//                    Pause();
                    FunctionRets.insert({LastFunctionPc, base % 4});
                    WasReturnHit = true;
                }
            }
            break;

            default:
                break;

        }
    }
//}


if(ParameterCountRef > 0)
{
    toRetHeader << "const int MainParamCount = " << ParameterCountRef << ";\r\n";
    if(RSC_Type == 2)
    {
        if(Header_SCO.GlobalsCount == 0)
            toRetHeader << "\r\n";
    }
    else toRetHeader << "\r\n";
}

if(RSC_Type == 2)
{
    if(Header_SCO.GlobalsCount > 0)
    {
        toRetHeader << "const int RegisterGlobals = " << Header_SCO.GlobalsCount << ";\r\n\r\n";
    }
}

if (StaticsRef.size() > 0)
{
    toRetHeader << "//{ Default Static Information\r\nint Static[" << StaticsRef.size() << "];\r\n";

    bool hadAnyNonZeroStatics = false;
    //bool scriptHasParameters = Header_XSC.ParameterCount > 0;

    if (ParameterCountRef > 0)
    {
        uint32_t i = StaticsRef.size() - ParameterCountRef, index = 0;
        if(i < 0)
            Throw("Script has Too Many Parameters and Not Enough Statics");

        for (; index < ParameterCountRef;i++,index++)
            toRetHeader << "Static[" << i << "] = ScriptParameter" << index << ";\r\n";
        toRetHeader << "\r\n";
    }

    for (uint32_t i = 0; i < StaticsRef.size(); i++)
    {
        if (StaticsRef[i] != 0)
        {
            hadAnyNonZeroStatics = true;
            toRetHeader << "Static[" << i << "] = " << StaticsRef[i] << ";\r\n";
        }
    }

    toRetHeader << "//}\r\n\r\n";
}

//{ Main Loop

    bool WasLastLineALabel = false, UsesCustomNativeNames = false, WasLastLabelANopLabel = false;
    Position = 0;

    while (Position < _codePages.size())
    {
        uint32_t beforeOpCodePC = Position;
        OpCode cop = (OpCode)ReadByte();

        if (cop < 0 || (uint8_t)cop > 155)
        {
            cout << "Invalid OpCode " << cop << "\r\n";
            //FILE* file = fopen("C:\\Users\\Rocko\\Desktop\\out.txt", "wb");
            //toRet.seekg(0, ios::end);
            //fwrite(toRet.str().c_str(), 1, toRet.tellg(), file);
            //fclose(file);
            Throw( "Invalid OpCode" );
        }

        if (PCInformation.find(beforeOpCodePC) != PCInformation.end())
        {
            if(PCInformation[beforeOpCodePC].IsLabelFunction)
            {
                WasLastLineALabel = true;
            }
            else if(PCInformation[beforeOpCodePC].StatementEnd)
            {
                for(uint32_t i = 0; i < PCInformation[beforeOpCodePC].StatementEndCount; i++)
                {
                    TabCount--;
                    toRet << GetTab() << "}\r\n";
                }
                WasLastLineALabel = true;
            }
            else if(PCInformation[beforeOpCodePC].IsLabelCase)
            {
                for(uint32_t i = 0; i < PCInformation[beforeOpCodePC].SwitchStatementCase.size(); i++)
                    toRet << GetTab() << "case " << PCInformation[beforeOpCodePC].SwitchStatementCase[i] << ":\r\n";
                TabCount++;
                WasLastLineALabel = true;
            }
            else if(!PCInformation[beforeOpCodePC].Ignored)
            {
                    toRet << "\r\n" << GetTab() << "Label_" << PCInformation[beforeOpCodePC].LabelNum << ":;\r\n";

                WasLastLineALabel = true;
            }
            else WasLastLineALabel = false;
        }
        else WasLastLineALabel = false;

        if(WasLastLineALabel && cop == OP_Nop)
        {
            WasLastLabelANopLabel = true;
        }

        switch (cop)
        {
            case OP_Nop: break;//disable nop display
            case OP_fAdd:
            case OP_Add: PushOperand(" + "); break;
            case OP_fSub:
            case OP_Sub: PushOperand(" - "); break;
            case OP_fMult:
            case OP_Mult: PushOperand(" * "); break;
            case OP_fDiv:
            case OP_Div: PushOperand(" / "); break;
            case OP_fMod:
            case OP_Mod: PushOperand(" % "); break;
            case OP_Not: PushPreOperand("!"); break;
            case OP_fNeg:
            case OP_Neg: PushPreOperand("~"); break;
            case OP_fCmpEQ:
            case OP_CmpEQ: PushOperand(" == "); break;
            case OP_fCmpNE:
            case OP_CmpNE: PushOperand(" != "); break;
            case OP_fCmpGT:
            case OP_CmpGT: PushOperand(" > "); break;
            case OP_fCmpGE:
            case OP_CmpGE: PushOperand(" >= "); break;
            case OP_fCmpLT:
            case OP_CmpLT: PushOperand(" < "); break;
            case OP_fCmpLE:
            case OP_CmpLE: PushOperand(" <= "); break;
            case OP_vAdd: PushVOperand(" + "); break;
            case OP_vSub: PushVOperand(" - "); break;
            case OP_vMult: PushVOperand(" * "); break;
            case OP_vDiv: PushVOperand(" / "); break;
            case OP_vNeg: PushVPreOperand(" ~"); break;
            case OP_And: PushOperand(" & "); break;
            case OP_Or: PushOperand(" | "); break;
            case OP_Xor: PushOperand(" ^ "); break;
            case OP_ItoF: PushPreOperand("(int)"); break;
            case OP_FtoI: PushPreOperand("(float)"); break;
            case OP_FtoV: Dup(2); break;
            case OP_PushB: PushUInt(ReadByte()); break;
            case OP_PushB2: PushUInt(ReadByte()); PushUInt(ReadByte()); break;
            case OP_PushB3: PushUInt(ReadByte()); PushUInt(ReadByte()); PushUInt(ReadByte()); break;
            case OP_Push: PushUInt(ReadInt32()); break;
            case OP_PushF: PushF(ReadSingle()); break;
            case OP_Dup: Dup(1); break;
            case OP_Drop: toRet << GetTab() << "Pop(" << Pop() << ");\r\n"; break;
            case OP_CallNative:{
                uint16_t NativeData = SwapEndian(ReadUInt16());

                int32_t nativeIndex = NativeParsing::GetIndex(NativeData);
                int32_t nativeParamCount = NativeParsing::GetArgCountFromIndex(&NativeData);
                bool nativehasRets = NativeParsing::FunctionHasReturn(&NativeData);

                if(NativeMap.find(NativesRef[nativeIndex]) != NativeMap.end())
                {
                    string NativeName = *NativeMap.find(NativesRef[nativeIndex])->second;
                    if(NativeName.at(0) == '_')
                    {
                        uint32_t NativeVal = SwapEndian(NativesRef[nativeIndex]);
                        char * NativeHash = IntToHex(NativeVal);

                        if (CustomNativeNames.find(NativeVal) == CustomNativeNames.end())
                        {
                            if(CustomNativeNames.size() == 0)
                            {
                                toRetHeader << "//{ Custom Native Names\r\n";
                                UsesCustomNativeNames = true;
                            }
                            CustomNativeNames.insert(NativeVal);
                            toRetHeader << "#define " << NativeName << " unk_0x" << NativeHash << "\r\n";
                            //cout << NativeName << endl;
                        }

                        if(!nativehasRets)
                            PrintCall(NativeName, nativeParamCount);
                        else
                            PushCall(NativeName, nativeParamCount);
                    }
                    else
                    {
                        if(!nativehasRets)
                            PrintCall(NativeName, nativeParamCount);
                        else
                            PushCall(NativeName, nativeParamCount);
                    }
                }
                else
                {

                    string Name = string("unk_0x") + IntToHex(SwapEndian((uint32_t)NativesRef[nativeIndex]));
                    if(!nativehasRets)
                        PrintCall(Name, nativeParamCount);
                    else
                        PushCall(Name, nativeParamCount);
                }

            }
                break;
            case OP_Function:{
                TabCount = 0;

                CurrentFuncParamCount = ReadByte();
                uint16_t StackCount = ReadUInt16();
                bool unusedfunc = false;

                if(!WasLastLineALabel)
                {
                    if(!WasLastLabelANopLabel)
                    {
                        if(UnusedFunctionNum == 0)
                        {
                            toRet << "void Main(";
                            UnusedFunctionNum++;
                            goto initmainvars;
                        }
                        else
                            unusedfunc = true;
                    }
                }

                //print items left on stack
                toRet << "}\r\n";
                ClearAndPrint();
                toRet << "\r\n";

                switch(FunctionRets[beforeOpCodePC])
                {
                    case 0: toRet << "void "; break;
                    case 1: toRet << "int "; break;
                    default: toRet << "int[" << FunctionRets[beforeOpCodePC] << "] "; break;

                }
                if(unusedfunc)
                {
                    toRet << "UnusedFunction_" << UnusedFunctionNum << '(';// PCall Location: " << Position - 1 << "\r\n";
                    UnusedFunctionNum++;
                }
                else
                    toRet << "Function_" << PCInformation[beforeOpCodePC].LabelNum << '(';

                initmainvars:;
                for(uint32_t i = 0; i < CurrentFuncParamCount; i++)
                {
                    if(i == 0)
                        toRet << "int Param_0";
                    else
                        toRet << ", int Param_" << i;
                }
                toRet << ")\r\n{\r\n";

                int32_t VarCount = StackCount - CurrentFuncParamCount;
                if(VarCount < 0)
                    Throw("Not Enough Stack Allocated to Function_" + to_string(PCInformation[beforeOpCodePC].LabelNum));

                TabCount++;

                toRet << GetTab() << "int VmVar[2];//These vars are allocated to the vm\r\n";

                if(VarCount - 2 > 0)
                    toRet << GetTab() << "int Var[" << VarCount - 2 << "];\r\n";

                toRet << "\r\n";


                AdvPos(ReadByte());
            }
                break;
            case OP_Return:{
                uint32_t PopCount = ReadByte();
                uint32_t RetCount = ReadByte();
                PrintRet(PopCount, RetCount);
            }
                break;
            case OP_pGet: PushPreOperand("*"); break;
            case OP_pSet: toRet << GetTab() << '*' << Pop(); toRet << " = " << Pop() << ";\r\n"; break;
            case OP_pPeekSet: Dup(1); StackRev(3); toRet << GetTab() << '*' << Pop(); toRet << " = " << Pop() << ";\r\n"; break;
            case OP_ToStack:{
                string ptr = Pop();
                string stackitemcount = Pop();

                char *endp;
                unsigned long int loopcount = strtoul(stackitemcount.c_str(), &endp, 10);

                if (endp == stackitemcount.c_str())
                {
                    Clear();
                    toRet << GetTab() << "//Undefined ToStack Count Resulted in UnkStack\r\n";
                }
                else if (*endp != 0)
                {
                    Clear();
                    toRet << GetTab() << "//Undefined ToStack Count Resulted in UnkStack\r\n";
                }
                else
                {
                    for(uint32_t i = 0; i < loopcount; i++)
                    {
                        codestack.push(ptr + '[' + to_string(i) + ']');
                    }
                }


            }
                break;
            case OP_FromStack:{
                string ptr = Pop();
                string stackitemcount = Pop();

                char *endp;
                unsigned long int loopcount = strtoul(stackitemcount.c_str(), &endp, 10);

                if (endp == stackitemcount.c_str())
                {
                    Clear();
                    toRet << GetTab() << "memcpy(" << ptr << ", StackPtr, " << stackitemcount << ");\r\n";
                    toRet << GetTab() << "//Undefined FromStack Count Resulted in UnkStack\r\n";
                }
                else if (*endp != 0)
                {
                    Clear();
                    toRet << GetTab() << "memcpy(" << ptr << ", StackPtr, " << stackitemcount << ");\r\n";
                    toRet << GetTab() << "//Undefined FromStack Count Resulted in UnkStack\r\n";
                }
                else
                {
                    if(loopcount > 0)
                    {
                        StackRev(loopcount);
                        toRet << GetTab() << "int StackVar[] = {" << Pop();
                        loopcount--;
                        for(uint32_t i = 0; i < loopcount; i++)
                        {
                            toRet << ", " << Pop();
                        }
                        toRet << "};\r\n";
                    }
                    else toRet << GetTab() << "int StackVar[] = {};\r\n";
                    toRet << GetTab() << "memcpy(" << ptr << ", StackVar, " << loopcount * 4 + 4 << ");\r\n";
                }


            }
                break;
            case OP_GetArrayP1: PushArray(ReadByte(), "&("); break;
            case OP_GetArray1: PushArray(ReadByte(), "("); break;
            case OP_SetArray1: PrintArray(ReadByte()); break;
            case OP_GetFrameP1: PushVar(ReadByte(), "&"); break;
            case OP_GetFrame1: PushVar(ReadByte(), ""); break;
            case OP_SetFrame1: PrintVar(ReadByte()); break;
            case OP_GetStaticP1: PushGlobal("&Static[", ReadByte()); break;
            case OP_GetStatic1: PushGlobal("Static[", ReadByte()); break;
            case OP_SetStatic1: toRet << GetTab() << "Static[" << +ReadByte() << "] = " << Pop() << ";\r\n"; break;
            case OP_Add1: PushOperandUInt(" + ", ReadByte()); break;
            case OP_GetImm1: codestack.push("*(" + Pop() + " + " + to_string(ReadByte()) + ')'); break;
            case OP_SetImm1: toRet << GetTab() << "*(" << Pop(); toRet << " + " << +ReadByte() << ") = " << Pop() << ";\r\n"; break;
            case OP_Mult1: PushOperandUInt(" * ", ReadByte()); break;
            case OP_PushS: codestack.push(to_string(ReadInt16())); break;
            case OP_Add2: PushOperandUInt(" + ", ReadUInt16()); break;
            case OP_GetImm2: codestack.push("*(" + Pop() + " + " + to_string(ReadUInt16()) + ')'); break;
            case OP_SetImm2: toRet << GetTab() << "*(" << Pop(); toRet << " + " << ReadUInt16() << ") = " << Pop() << ";\r\n"; break;
            case OP_Mult2: PushOperandUInt(" * ", ReadUInt16()); break;
            case OP_GetArrayP2: PushArray(ReadUInt16(), "&("); break;
            case OP_GetArray2: PushArray(ReadUInt16(), "("); break;
            case OP_SetArray2: PrintArray(ReadUInt16()); break;
            case OP_GetFrameP2: PushVar(ReadUInt16(), "&"); break;
            case OP_GetFrame2: PushVar(ReadUInt16(), ""); break;
            case OP_SetFrame2: PrintVar(ReadUInt16()); break;
            case OP_GetStaticP2: PushGlobal("&Static[", ReadUInt16()); break;
            case OP_GetStatic2: PushGlobal("Static[" , ReadUInt16()); break;
            case OP_SetStatic2: toRet << GetTab() << "Static[" << ReadUInt16() << "] = " << Pop() << ";\r\n"; break;
            case OP_GetGlobalP2: PushGlobal("&Global[", ReadUInt16()); break;
            case OP_GetGlobal2: PushGlobal("Global[", ReadUInt16()); break;
            case OP_SetGlobal2: toRet << GetTab() << "Global[" << ReadUInt16() << "] = " << Pop() << ";\r\n"; break;
            case OP_Call2:
            case OP_Call2h1:
            case OP_Call2h2:
            case OP_Call2h3:
            case OP_Call2h4:
            case OP_Call2h5:
            case OP_Call2h6:
            case OP_Call2h7:
            case OP_Call2h8:
            case OP_Call2h9:
            case OP_Call2hA:
            case OP_Call2hB:
            case OP_Call2hC:
            case OP_Call2hD:
            case OP_Call2hE:
            case OP_Call2hF:{
                uint8_t val1 = ReadByte();
                uint8_t val2 = ReadByte();
                int32_t callOffset = CallParsing::GetCallOffset(val2 | (val1 << 8), cop);

                if(!(callOffset <= CodeLengthRef && callOffset >= 0))
                {
                    cout << "Position: " << Position << '\n';
                    cout << "Offset: " << callOffset << " > " << CodeLengthRef << '\n';
                    Throw("Call Pos Out Of Bounds");
                }

                int32_t NewCallOffset = FindFuncOffsetFromCall(callOffset);

                if(!(NewCallOffset <= CodeLengthRef && NewCallOffset >= 0))
                {
                    cout << "Position: " << Position << '\n';
                    cout << "Offset: " << NewCallOffset << " > " << CodeLengthRef << '\n';
                    Throw("NewCall Pos Out Of Bounds");
                }
//                cout << FunctionRets[NewCallOffset] << "\r\n";
//                Pause();

                if(FunctionRets[NewCallOffset] == 0)
                    PrintCall("Function_" + to_string(PCInformation[NewCallOffset].LabelNum), (codepages + NewCallOffset)[1]);
                else if(FunctionRets[NewCallOffset] == 1)
                    PushCall("Function_" + to_string(PCInformation[NewCallOffset].LabelNum), (codepages + NewCallOffset)[1]);
                else
                    PushCallArray("Function_" + to_string(PCInformation[NewCallOffset].LabelNum), (codepages + NewCallOffset)[1], FunctionRets[NewCallOffset]);


            }
                break;
            case OP_Jump:{
                int16_t jumpLoc = ReadInt16();
                int32_t fullJumpLoc = (int32_t)(jumpLoc + Position);

                if(PCInformation[fullJumpLoc].StatementEnd && PCInformation[fullJumpLoc].IsLabelCase)
                {
                    TabCount--;
                    toRet << GetTab() << "break;\r\n";
                }
                else if(!(PCInformation[fullJumpLoc].Ignored || PCInformation[fullJumpLoc].IsLabelFunction))
                        toRet << GetTab() << "goto " << "Label_" << PCInformation[fullJumpLoc].LabelNum << ";\r\n";
            }
                break;
            case OP_JumpFalse:{
                toRet << GetTab() << "if(" << Pop() << ")\r\n" << GetTab() << "{\r\n";

                int16_t jumpLoc = ReadInt16();
                int32_t fullJumpLoc = (int32_t)(jumpLoc + Position);

                map<int64_t, PCI>::iterator pos = PCInformation.find(fullJumpLoc);
                if (pos != PCInformation.end())
                    pos->second.StatementEndCount++;

                TabCount++;
            }
                break;
            case OP_JumpNE: PrintIfOperand(" == "); break;
            case OP_JumpEQ: PrintIfOperand(" != "); break;
            case OP_JumpLE: PrintIfOperand(" > "); break;
            case OP_JumpLT: PrintIfOperand(" >= "); break;
            case OP_JumpGE: PrintIfOperand(" < "); break;
            case OP_JumpGT: PrintIfOperand(" <= "); break;
            case OP_GetGlobalP3: PushGlobal("&Global[", ReadInt24()); break;
            case OP_GetGlobal3: PushGlobal("Global[", ReadInt24()); break;
            case OP_SetGlobal3: toRet << GetTab() << "Global[" << ReadInt24() << "] = " << Pop() << ";\r\n"; break;
            case OP_PushI24: PushUInt(ReadInt24()); break;
            case OP_Switch:{
                uint8_t switchCaseCount = ReadByte();

                toRet << GetTab() << "switch(" << Pop() << ")\r\n" << GetTab() << "{\r\n";
                TabCount++;
                for (uint32_t i = 0; i < switchCaseCount; i++)
                {
                    int32_t switchCase = ReadInt32();

                    uint16_t switchVal = ReadInt16();
                    int64_t fullSwitchVal = Position + switchVal;


                    //toRet << GetTab() << "case " << switchCase << ":\r\n" << GetTab();
                    //test for break label if found then jump to label and copy pasta code until break jump


                    map<int64_t, PCI>::iterator pos = PCInformation.find(fullSwitchVal);
                    if (pos != PCInformation.end())
                    {
                        pos->second.IsLabelCase = true;
                        pos->second.SwitchStatementCase.push_back(switchCase);
                    }

                }

                //get default case
                if(*(uint8_t*)(codepages + Position) == OP_Jump)
                {
                    //ok valid end
                    Position++;
                    int16_t jumpLoc = ReadInt16();
                    int32_t fullJumpLoc = (int32_t)(jumpLoc + Position);

                    map<int64_t, PCI>::iterator pos = PCInformation.find(fullJumpLoc);
                    if (pos != PCInformation.end())
                    {
                        //this will bug if switch end is the same as nested switch end
                        //might fix

                        //possible default case are
                        //none -> default jump = end
                        //default break -> default jump goes to default then end
                        //default -> regular default case

                        pos->second.StatementEnd = true;
                        pos->second.IsLabelCase = true;
                        pos->second.StatementEndCount++;
                    }

                }
                else
                    Throw("Switch End Not specified");//must be undefined default case

            }
                break;
            case OP_PushString:{
                uint8_t len = ReadByte();
                char* StringFixed = new char[len*2];
                FixString((char*)(codepages + Position), len, StringFixed);
                codestack.push('"' + string(StringFixed) + '"');
                AdvPos(len);
                delete[] StringFixed;
            }
                break;
            case OP_PushArrayP:{
                int32_t len = ReadInt32();
                if(len % 4 != 0)
                {
                    toRet << GetTab() << "unsigned char InlineArray[" << len << "] = {";
                    for(uint32_t i = 0; i < len; i++)
                    {
                        if(i == 0)
                            toRet << ReadByte();
                        else
                            toRet << ', ' << ReadByte();
                    }
                }
                else
                {
                    uint32_t size = len / 4;
                    toRet << GetTab() << "int InlineArray[" << size << "] = {";
                    for(uint32_t i = 0; i < size; i++)
                    {
                        if(i == 0)
                            toRet << ReadInt32();
                        else
                            toRet << ", " << ReadInt32();
                    }

                }
                toRet << "};" << "\r\n";
                codestack.push("InlineArray");

            }
                break;
            case OP_PushStringNull: codestack.push("\"\""); break;
            case OP_StrCopy: toRet << GetTab() << Pop(); toRet << " = " << Pop() << ";//" << +ReadByte() << "\r\n"; break;
            case OP_ItoS: toRet << GetTab() << Pop(); toRet << " = itos(" << Pop() << ");//" << +ReadByte() << "\r\n"; break;
            case OP_StrAdd: toRet << GetTab() << Pop(); toRet <<" += " << Pop() << ";//" << +ReadByte() << "\r\n"; break;
            case OP_StrAddI: toRet << GetTab() << Pop(); toRet << " += itos(" << Pop() << ");//" << +ReadByte() << "\r\n"; break;
            case OP_MemCopy:{

                string ptr = Pop();
                string stackdatasize = Pop();
                string stackitemcount = Pop();

                char *endp;
                unsigned long int loopcount = strtoul(stackitemcount.c_str(), &endp, 10);

                if (endp == stackitemcount.c_str())
                {
                    Clear();
                    toRet << GetTab() << "memcpy(" << ptr << ", StackPtr, " << stackitemcount << ");\r\n";
                    toRet << GetTab() << "//Undefined MemCopy Count Resulted in UnkStack\r\n";
                }
                else if (*endp != 0)
                {
                    Clear();
                    toRet << GetTab() << "memcpy(" << ptr << ", StackPtr, " << stackitemcount << ");\r\n";
                    toRet << GetTab() << "//Undefined MemCopy Count Resulted in UnkStack\r\n";
                }
                else
                {
                    if(loopcount > 0)
                    {
                        StackRev(loopcount);
                        toRet << GetTab() <<  "int StackVar[] = {" << Pop();
                        loopcount--;
                        for(uint32_t i = 0; i < loopcount; i++)
                        {
                            toRet << ", " << Pop();
                        }
                        toRet << "};\r\n";
                    }
                    else toRet << GetTab() << "int StackVar[] = {};\r\n";
                    toRet << GetTab() << "memcpy(" << ptr << ", StackVar, " << loopcount * 4 << ");\r\n";
                }
            }
                break;
            case OP_Catch: break;
            case OP_Throw: break;
            case OP_pCall:{
                string callloc = Peek();

                char *endp;

                unsigned long int value = strtoul(callloc.c_str(), &endp, 0);

                if (endp == callloc.c_str() || *endp != 0) {
                    unkpcall:
                    toRet << GetTab() << "CallPos(" << Pop() << ");\r\n";
                    toRet << GetTab() << "Due to a unparsable pCall the stack has to be cleared\r\n";
                    ClearAndPrint();
                    toRet << "\r\n";
                }
                else {
                    //function loc might be parcelable

                    int32_t NewCallOffset = FindFuncOffsetFromCall(value);

                    if(!(NewCallOffset <= CodeLengthRef && NewCallOffset >= 0))
                        goto unkpcall;

                    Pop();//get rid of function loc on stack

//                    cout << FunctionRets[NewCallOffset] << "\r\n";
//                    Pause();

                    if(FunctionRets[NewCallOffset] == 0)
                        PrintCall("Function_" + to_string(PCInformation[NewCallOffset].LabelNum), (codepages + NewCallOffset)[1]);
                    else if(FunctionRets[NewCallOffset] == 1)
                        PushCall("Function_" + to_string(PCInformation[NewCallOffset].LabelNum), (codepages + NewCallOffset)[1]);
                    else
                        PushCallArray("Function_" + to_string(PCInformation[NewCallOffset].LabelNum), (codepages + NewCallOffset)[1], FunctionRets[NewCallOffset]);


                }
            }
                break;
            case OP_ReturnP0R0:
            case OP_ReturnP0R1:
            case OP_ReturnP0R2:
            case OP_ReturnP0R3:
            case OP_ReturnP1R0:
            case OP_ReturnP1R1:
            case OP_ReturnP1R2:
            case OP_ReturnP1R3:
            case OP_ReturnP2R0:
            case OP_ReturnP2R1:
            case OP_ReturnP2R2:
            case OP_ReturnP2R3:
            case OP_ReturnP3R0:
            case OP_ReturnP3R1:
            case OP_ReturnP3R2:
            case OP_ReturnP3R3:{
                uint32_t base = cop - 122;
                PrintRet(base / 4, base % 4);
            }
                break;
            case OP_Push_Neg1: codestack.push("-1"); break;
            case OP_Push_0: codestack.push("0"); break;
            case OP_Push_1: codestack.push("1"); break;
            case OP_Push_2: codestack.push("2"); break;
            case OP_Push_3: codestack.push("3"); break;
            case OP_Push_4: codestack.push("4"); break;
            case OP_Push_5: codestack.push("5"); break;
            case OP_Push_6: codestack.push("6"); break;
            case OP_Push_7: codestack.push("7"); break;
            case OP_PushF_Neg1: codestack.push("-1f"); break;
            case OP_PushF_0: codestack.push("0f"); break;
            case OP_PushF_1: codestack.push("1f"); break;
            case OP_PushF_2: codestack.push("2f"); break;
            case OP_PushF_3: codestack.push("3f"); break;
            case OP_PushF_4: codestack.push("4f"); break;
            case OP_PushF_5: codestack.push("5f"); break;
            case OP_PushF_6: codestack.push("6f"); break;
            case OP_PushF_7: codestack.push("7f"); break;
            default:
                toRet << "//UNK" << _opNames[(uint8_t)cop] << "\r\n";
                break;
        }
    }

///fix for rockstar jumping to the end of a script like a bellend
if (PCInformation.find(Position) != PCInformation.end())
{
    if(!PCInformation[Position].Ignored)
        toRet << "\r\n:Label_" << PCInformation[Position].LabelNum << "\r\n";
}

//}

//{ Write File

    string dir = OutPath.substr(0, OutPath.find_last_of('\\') + 1);
    if(dir != "")
        boost::filesystem::create_directories(dir);

    file = fopen(OutPath.c_str(), "wb");
    if (file != NULL)
    {
        if(UsesCustomNativeNames)
        {
            toRetHeader << "//<\r\n";
            toRetHeader << "\r\n";
        }
        toRetHeader.seekg(0, ios::end);
        fwrite(toRetHeader.str().c_str(), 1, toRetHeader.tellg(), file);

        toRet << "}\r\n";
        ClearAndPrint();
        toRet << "\r\n";

        toRet.seekg(0, ios::end);
        fwrite(toRet.str().c_str(), 1, toRet.tellg(), file);

        fclose(file);
    }
    else Throw("Output File Could Not Be Opened");
//}

}

void RSC::XSCWrite(char* path, Platform platform, PikIO::Endianess endian, bool rsc85 = true)
{

    struct PHO//placeHolderOffsets
    {
        int32_t CodeBlocks, Unk1, Statics, Natives;
    };
    PHO SavedOffsets;
    PikIO dataWriter;
    int32_t headerLocation = 0;

    dataWriter.InitWriter(PikIO::Endianess::Big);
    //0: Code blocks ptrs
    //1: unk1 Ptr
    //4: statics
    //2: natives ptr

//{ Delegates
    auto GetSpaceLeft = [&](auto size)
    {
        int32_t sl = size - ((int32_t)dataWriter.BaseWrite.size() % size);
        if (sl == 0)
            sl = size;
        return (uint32_t)sl;
    };
    auto FillPageNops = [&]()
    {
        vector<uint8_t> buffer (GetSpaceLeft(16384));
        dataWriter.WriteBytes(buffer);
    };
    auto FillPageDynamic = [&](auto amount)
    {
        vector<uint8_t> buffer (GetSpaceLeft(amount));
        memset(buffer.data(),0xCD,buffer.size());
        dataWriter.WriteBytes(buffer);
    };
    auto PadNops = [&]()
    {
        int32_t pad = 16 - (int32_t)dataWriter.BaseWrite.size() % 16;
        if (pad == 0 || pad == 16)
            return;

        if(pad > 16384)
            Throw("Pad Over 16364");

        vector<uint8_t> buffer (pad);
        dataWriter.WriteBytes(buffer);
    };
    auto GetPadExpectedAmount = [&](auto val)
    {
        int32_t pad = 16 - (int32_t)val % 16;
        if (pad == 0 || pad == 16)
            return (uint32_t)val;
        return (uint32_t)(pad + val);
    };
    auto Pad = [&]()
    {
        int32_t pad = 16 - (int32_t)dataWriter.BaseWrite.size() % 16;
        if (pad == 0 || pad == 16)
            return;

        if(pad > 16384)
            Throw("Pad Over 16364");

        vector<uint8_t> buffer (pad);
        memset(buffer.data(),0xCD,buffer.size());
        dataWriter.WriteBytes(buffer);
    };
    auto ForcePad = [&]()
    {
        int32_t pad = 16 - (int32_t)dataWriter.BaseWrite.size() % 16;
        if (pad == 0 || pad == 16)
            pad = 16;

         if(pad > 16384)
            Throw("ForcePad Over 16364");

        vector<uint8_t> buffer (pad);
        memset(buffer.data(),0xCD,buffer.size());
        dataWriter.WriteBytes(buffer);
    };
    auto Write16384CodePages = [&]()
    {
        Header_XSC.CodePagePointers.clear();
        Header_XSC.CodePagePointers.resize(Header_XSC.CodePages.size());
        for (uint32_t i = 0; i < Header_XSC.CodePages.size() - 1; i++)
        {

            if (GetSpaceLeft(16384) < Header_XSC.CodePages[i].size())
                FillPageNops();

            Header_XSC.CodePagePointers[i] = dataWriter.BaseWrite.size();
            dataWriter.WriteBytes(Header_XSC.CodePages[i]);

            PadNops();

        }

    };
    auto WriteFinalCodePage = [&]()
    {
        Header_XSC.CodePagePointers[Header_XSC.CodePages.size() - 1] = dataWriter.BaseWrite.size();
        dataWriter.WriteBytes(Header_XSC.CodePages[Header_XSC.CodePages.size() - 1]);
        Pad();
    };
    auto WriteNatives = [&]()
    {
        if (Header_XSC.Natives.size() > 0)
        {

            if (GetSpaceLeft(16384) < Header_XSC.Natives.size() * 4)
                FillPageDynamic(16384);

            SavedOffsets.Natives = dataWriter.BaseWrite.size();

            for(uint32_t i = 0; i < Header_XSC.Natives.size(); i++)
                dataWriter.Write(Header_XSC.Natives[i]);
            Pad();
        }
        else
        {
            if (GetSpaceLeft(16384) < 16)
                FillPageDynamic(16384);
            SavedOffsets.Natives = dataWriter.BaseWrite.size();
            ForcePad();
        }

    };
    auto WriteStatics = [&]()
    {
        if (Header_XSC.Statics.size() > 0)
        {

            if (GetSpaceLeft(16384) < Header_XSC.Statics.size() * 4)
                FillPageDynamic(16384);

            SavedOffsets.Statics = dataWriter.BaseWrite.size();

            for(uint32_t i = 0; i < Header_XSC.Statics.size(); i++)
                dataWriter.Write(Header_XSC.Statics[i]);
            Pad();

        }
        else
        {
            if (GetSpaceLeft(16384) < 16)
                FillPageDynamic(16384);
            SavedOffsets.Statics = dataWriter.BaseWrite.size();
            ForcePad();

        }

    };
    auto WriteHeader = [&]()
    {
        headerLocation = dataWriter.BaseWrite.size();
        Header_XSC.StaticsCount = Header_XSC.Statics.size();
        dataWriter.Write(Header_XSC.PgBase);
        dataWriter.Write(0); //Unk1 ptr
        dataWriter.Write(0); //codeBlocksListOffsetPtr
        dataWriter.Write(Header_XSC.CodeLength);
        dataWriter.Write(Header_XSC.ParameterCount);
        dataWriter.Write(Header_XSC.StaticsCount);
        dataWriter.Write(0); //Statics offset
        dataWriter.Write(Header_XSC.GlobalsSignature);
        dataWriter.Write(Header_XSC.NativesCount);
        dataWriter.Write(0); //native offset
        Pad();
    };
    auto WritePointers = [&]()
    {
        //write unk1

        vector<uint8_t> _unkPTRData(4);

        if (GetSpaceLeft(16384) < _unkPTRData.size())
            FillPageDynamic(16384);

        SavedOffsets.Unk1 = dataWriter.BaseWrite.size();
        dataWriter.WriteBytes(_unkPTRData);
        Pad();

        uint64_t padcount = Math::CeilDivInt(Header_XSC.CodePages.size() * 4, 16);
        for(uint64_t i = 0; i < padcount; i++)
            ForcePad();

        //Write code page pointers
        if (GetSpaceLeft(16384) < Header_XSC.CodePages.size() * 4)
            FillPageDynamic(16384);
        SavedOffsets.CodeBlocks = dataWriter.BaseWrite.size();
        for (uint32_t i = 0; i < Header_XSC.CodePages.size(); i++)
            dataWriter.Write(0);

        Pad();
    };
    auto WriteNormal = [&](auto datasize,auto bufferflag)
    {
        if(datasize < bufferflag)
        {
            Header_XSC.Flag = RSC85Parsing::GetFlagFromReadbuffer(bufferflag);
            if(Header_XSC.Flag == 0xFFFFFFFF)
                Throw("Invalid Read Buffer");
            Write16384CodePages();
            WriteFinalCodePage();
            FillPageDynamic(bufferflag);
            WriteHeader();
            WriteNatives();
            WriteStatics();
            WritePointers();
            FillPageDynamic(bufferflag);
            return true;
        }
        return false;
    };
    auto WriteSmall = [&](auto datasize,auto bufferflag)
    {
        if(datasize < bufferflag)
        {
            Header_XSC.Flag = RSC85Parsing::GetFlagFromReadbuffer(bufferflag);

//            cout << "Datasize: " << datasize << '\n';
//            cout << "Bufferflag: " << bufferflag << '\n';
//            cout << "Flag: " << hex << Header_XSC.Flag << '\n';
//
            if(Header_XSC.Flag == 0xFFFFFFFF)
                Throw("Invalid Read Buffer");
            Write16384CodePages();
            WriteHeader();
            WriteFinalCodePage();
            WriteNatives();
            WriteStatics();
            WritePointers();
            FillPageDynamic(bufferflag);
            return true;
        }
        return false;
    };

//}

//{ Write Pages and header

    const uint32_t CodePagePtrsSize = Header_XSC.CodePages.size() * 4;

    uint32_t TotalData = GetPadExpectedAmount(Header_XSC.Natives.size() * 4) +
    GetPadExpectedAmount(Header_XSC.Statics.size() * 4) +
    GetPadExpectedAmount(16 + CodePagePtrsSize) + //unk1 4 but set as 16 (padded) to avoid miscalculating the pad size
    GetPadExpectedAmount(40) + //header
    GetPadExpectedAmount(CodePagePtrsSize);//code page pointers

    uint32_t LastCodePageSize = GetPadExpectedAmount(Header_XSC.CodePages[Header_XSC.CodePages.size() - 1].size());//code page pointers * padding for unk1

//    cout << "Natives: " << GetPadExpectedAmount(Header_XSC.Natives.size() * 4) << '\n';
//    cout << "Statics: " << GetPadExpectedAmount(Header_XSC.Statics.size() * 4) << '\n';
//    cout << "Unk1: " << GetPadExpectedAmount(16 + CodePagePtrsSize) << '\n';
//    cout << "Header: " << GetPadExpectedAmount(40) << '\n';
//    cout << "Codepage Ptrs: " << GetPadExpectedAmount(CodePagePtrsSize) << '\n';
//    cout << "Last Codepage: " << GetPadExpectedAmount(Header_XSC.CodePages[Header_XSC.CodePages.size() - 1].size()) << '\n';


    //if(LastCodePageSize +  TotalData > 16384) then write normal but maybe place somethings under last code page if possible
    //else include last code page in header

    if(LastCodePageSize + TotalData > 16384)
    {
        if     (WriteNormal(TotalData,4096));
        else if(WriteNormal(TotalData,8192));
        else if(WriteNormal(TotalData,16384));
        else
        {
            Header_XSC.Flag = RSC85_Flags_ReadBuffer65536_32;
            WriteHeader();
            WriteNatives();
            WriteStatics();
            WritePointers();
            FillPageDynamic(65536);
            Write16384CodePages();
            WriteFinalCodePage();
            FillPageDynamic(65536);
        }

    }
    else
    {
        TotalData += LastCodePageSize;
        if     (WriteSmall(TotalData,4096));
        else if(WriteSmall(TotalData,8192));
        else if(WriteSmall(TotalData,16384));
        else
            Throw("Total Data is Less Then and Greater Then 16384. Impossible.");
    }

//}

//{ Fix header and other pointers
    dataWriter.WriteAtIndex(DataConversion::IntToPointerInt(SavedOffsets.Unk1), headerLocation + 4); //UnkPtr1
    dataWriter.WriteAtIndex(DataConversion::IntToPointerInt(SavedOffsets.CodeBlocks),headerLocation + 8); //code block ptrs offset
    dataWriter.WriteAtIndex(DataConversion::IntToPointerInt(SavedOffsets.Statics), headerLocation + 24); //statics offset
    dataWriter.WriteAtIndex(DataConversion::IntToPointerInt(SavedOffsets.Natives), headerLocation + 36); //natives offset

    for (uint32_t i = 0; i < Header_XSC.CodePagePointers.size(); i++)
        dataWriter.WriteAtIndex(DataConversion::IntToPointerInt(Header_XSC.CodePagePointers[i]),  SavedOffsets.CodeBlocks + (i * 4));
//}

//{ Write File
    if (rsc85)
    {

        // compressing and encrypting

            Compression::xCompress Compression;
            Compression.xCompressInit();

            uint8_t * CompressedData = new uint8_t[dataWriter.BaseWrite.size() + 8];
            int32_t CompressedLen = 0;

            Compression.Compress((uint8_t*)dataWriter.BaseWrite.data(), dataWriter.BaseWrite.size(), CompressedData + 8, &CompressedLen);

            if(CompressedLen > 0)
            {
                *(uint32_t*)CompressedData = SwapEndian(0x0FF512F1);//LZX Signature?
                *(uint32_t*)(CompressedData + 4) = SwapEndian(CompressedLen);
                CompressedLen += 8;
            }
            else Throw("Compression Failed");

            if(!Crypt::AES_Encrypt(CompressedData, CompressedLen))
                Throw("Encryption Failed");


            uint32_t * CSR_Header = new uint32_t[4];
            CSR_Header[0] = SwapEndian(0x85435352);//.CSR
            CSR_Header[1] = SwapEndian(0x00000002);//Resource Type Script
            CSR_Header[2] = SwapEndian(0x80000000);//unk int max val (flags1)
            CSR_Header[3] = SwapEndian(RSC85Parsing::GetFullFlagWithSize(dataWriter.BaseWrite.size(), Header_XSC.Flag));//size (flags2)

            FILE* file = fopen(path, "wb");
            if(file != NULL)
            {
                fwrite(CSR_Header, 1, 16, file);//encrypted data
                fwrite(CompressedData, 1, CompressedLen, file);//encrypted data
                fclose(file);
            }
            else
                Throw("Could Not Open Output File");

            delete[] CSR_Header;
            delete[] CompressedData;
    }
    else
    {
        FILE* file = fopen(path, "wb");

        if(file != NULL)
        {
            fwrite(dataWriter.BaseWrite.data(), 1, dataWriter.BaseWrite.size(), file);
            fclose(file);
        }
        else
            Throw("Could Not Open Output File");
    }

//}

}

void RSC::SCOWrite(char* path, Platform platform, PikIO::Endianess endian, bool rsc2 = true)
{
    PikIO dataWriter;
    dataWriter.InitWriter(PikIO::Endianess::Big);

//{ Delegates
    auto GetSpaceLeft = [&](auto size)
    {
        int32_t sl = size - ((int32_t)dataWriter.BaseWrite.size() % size);
        if (sl == 0)
            sl = size;
        return (uint32_t)sl;
    };
    auto FillPageNops = [&]()
    {
        vector<uint8_t> buffer (GetSpaceLeft(16384));
        dataWriter.WriteBytes(buffer);
    };
    auto WriteCodePages = [&]()
    {
        for (uint32_t i = 0; i < Header_SCO.CodePages.size(); i++)
        {
            if (GetSpaceLeft(16384) < Header_SCO.CodePages[i].size())
                FillPageNops();

            dataWriter.WriteBytes(Header_SCO.CodePages[i]);
        }

    };
    auto WriteNatives = [&]()
    {
        if (Header_SCO.Natives.size() > 0)
        {
            for(uint32_t i = 0; i < Header_SCO.Natives.size(); i++)
                dataWriter.Write(Header_SCO.Natives[i]);
        }
    };
    auto WriteStatics = [&]()
    {
        if (Header_SCO.Statics.size() > 0)
        {
            for(uint32_t i = 0; i < Header_SCO.Statics.size(); i++)
                dataWriter.Write(Header_SCO.Statics[i]);
        }
    };

//}

WriteCodePages();
WriteNatives();
WriteStatics();

//{ Write File
    if (rsc2)
    {

        uint32_t CompressedSize = dataWriter.BaseWrite.size();

        uint8_t * CompressedData = new uint8_t[dataWriter.BaseWrite.size()];

        Compression::ZLIB_Compress(dataWriter.BaseWrite.data(),dataWriter.BaseWrite.size(),CompressedData,CompressedSize);
        //fix length of compressed data

        if(CompressedSize != 0)
            Header_SCO.CompressedSize = CompressedSize;
        else Throw("SCO Compressed Size Invalid");

         if(!Crypt::AES_Encrypt(CompressedData, CompressedSize))
            Throw("Decryption Failed");

            uint32_t * SCR_Header = new uint32_t[12];
            SCR_Header[0] = SwapEndian(0x53435202);//SCR.
            SCR_Header[1] = SwapEndian(Header_SCO.GlobalsSignature);
            SCR_Header[2] = SwapEndian(Header_SCO.CompressedSize);
            SCR_Header[3] = SwapEndian(Header_SCO.unk12);//-3 is_crypt?
            SCR_Header[4] = SwapEndian(Header_SCO.CodeLength);
            SCR_Header[5] = SwapEndian(Header_SCO.StaticsCount);
            SCR_Header[6] = SwapEndian(Header_SCO.GlobalsCount);
            SCR_Header[7] = SwapEndian(Header_SCO.ParameterCount);
            SCR_Header[8] = SwapEndian(Header_SCO.NativesCount);
            SCR_Header[9] = SwapEndian(Header_SCO.unk36);
            SCR_Header[10] = SwapEndian(Header_SCO.unk40);
            SCR_Header[11] = SwapEndian(Header_SCO.unk44);


            FILE* file = fopen(path, "wb");
            if(file != NULL)
            {
                fwrite(SCR_Header, 1, 48, file);//encrypted data
                fwrite(CompressedData, 1, CompressedSize, file);//encrypted data
                fclose(file);
            }
            else
                Throw("Could Not Open Output File");
    }
    else
    {
        FILE* file = fopen(path, "wb");

        if(file != NULL)
        {
            fwrite(dataWriter.BaseWrite.data(), 1, dataWriter.BaseWrite.size(), file);
            fclose(file);
        }
        else
            Throw("Could Not Open Output File");
    }

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
    void UnkOpcodeError(){
		cout << "Error on line " << line << "\r\n";
		cout << "Line: " << GetLineG() << "\r\n";
        Throw("Unknown Opcode");
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
            Throw("Index Out Of Bounds");
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
                Throw("Invalid Parameter");
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
            Throw("Index Out Of Bounds");
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
                    Throw("Invalid Jump Format");
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
                Throw("Invalid String Format");
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
                            case '0':
                                buffer.push_back('\0');
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
                        Throw("Character Literal Out Of Bounds");
                    }
                    break;
                case '\r':
                case '\n':
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    Throw("Invalid String Format");
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
                            Throw("Invalid GetEnum Format");
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
                            Throw("Invalid GetLoc Format");
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
                            Throw("Invalid GetHash Format");
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
                    Throw("Invalid GetHash/GetEnum/GetLoc String Format");
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
                    Throw("Invalid GetHash/GetEnum/GetLoc String Format");
                }
                else CharNum += 2;
            }
            else
            {
                cout << "Error on line " << line << "\r\n";
                Throw("Index Out Of Bounds");
            }

        }
//        cout << buffer << endl;
//        Pause();

        return {buffer, len, type};
    }
    template<typename T> bool FindStaticParams(char* str,ParamTypes type, T* out){
        switch(type)
        {
            case ParamTypes::Frame:
            {
                map<string,uint16_t>::iterator iter = gFrameNames->find(string(str));
                if (iter != gFrameNames->cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << "Name: " << string(str) << "\r\n";
                    Throw("Could Not Find Frame Name");
                }
            }
            break;
            case ParamTypes::Static:
            {
                map<string,uint16_t>::iterator iter = gStaticNames->find(string(str));
                if (iter != gStaticNames->cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << "Name: " << string(str) << "\r\n";
                    Throw("Could Not Find Static Name");
                }
            }
            break;
            case ParamTypes::Native:
            {
                map<string,uint32_t>::iterator iter = gNativeNames->find(string(str));
                if (iter != gNativeNames->cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << "Name: " << string(str) << "\r\n";
                    Throw("Could Not Find Native Name");
                }
            }
            break;
            case ParamTypes::Global:
            {
                map<string,uint32_t>::iterator iter = gGlobalNames->find(string(str));
                if (iter != gGlobalNames->cend()){
                    *out = iter->second;
                    return true;
                }
                else{
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << "Name: " << string(str) << "\r\n";
                    Throw("Could Not Find Global Name");
                }
            }
            break;


            default: return false;
        }

        return false;
    }
    template<typename T> T GetParamAsInt(ParamTypes type = ParamTypes::None){

        CharStr str = GetParami();
        //cout << "<" << str.str << ">\r\n";

        char *endp;

        unsigned long int value = strtoul(str.str, &endp, 0);

        if(value > numeric_limits<T>::max())
        {
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            cout << "Value " << value << " is greater then " << numeric_limits<T>::max() << "\r\n";
            Throw("Opcode Data Out Of Bounds");
        }

        if (endp == str.str) {
            T ret;
            if(FindStaticParams<T>(str.str, type, &ret))
                return ret;

            //failed
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Throw("String To Int Failed");
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
            Throw("String To Int Failed");
        }
        else {
            return (T)value;
        }
        return (T)0;
    }
    bool GetParamAsInt32WithType(int32_t &out , bool errors, uint32_t OpcodeSize){
        CharStrType str = GetParamiWithEnums();
        char *endp;

        switch(str.type)
        {
            case PushTypes::Push_None:
                {
                    unsigned long int value = strtoul(str.str, &endp, 0);

                    if (endp == str.str) {
                        //failed
                        if(errors)
                        {
                            cout << "Error on line " << line << "\r\n";
                            cout << "Code: " << 0 << "\r\n";
                            cout << "Line: " << GetLineG() << "\r\n";
                            Throw("String To Int Failed");
                        }
                        return false;
                    }
                    else if (*endp != 0) {
                        if(errors)
                        {
                            cout << "Error on line " << line << "\r\n";
                            cout << "Code: " << 0 << "\r\n";
                            cout << "Line: " << GetLineG() << "\r\n";
                            cout << "Index: " << endp - str.str << "\r\n";
                            Throw("String To Int Failed");
                        }
                        return false;
                    }
                    else {
                        out = value;
                        return true;
                    }
                }
            break;
            case PushTypes::Push_Enum:
                {
                    map<string,uint32_t>::iterator iter = gEnums->find(string(str.str));
                    if (iter != gEnums->cend()){
                        out = iter->second;
                        return true;
                    }
                    else{
                            cout << "Error on line " << line << "\r\n";
                            cout << "Code: " << 0 << "\r\n";
                            cout << "Line: " << GetLineG() << "\r\n";
                            cout << "Enum: " << str.str << "\r\n";
                            Throw("Could Not Find Enum");
                        return false;
                    }
                }
            break;
            case PushTypes::Push_Loc:
                gJumps->push_back({JumpType::pCall, gtable->size() + OpcodeSize,LineStart,line,str.str});
                out = 0x7FFFFFFF;
                return true;
            break;
            case PushTypes::Push_Hash:
                out = Joaat(str.str);
                return true;
            break;
        }

        return false;
    }
    vector<uint32_t> GetParamAsVector(){
        vector<uint32_t> ret;
		uint32_t inc = CharNum;

        while(inc < lstring_size)
        {
            switch(cmpdata[inc])
            {
                case '/':
                    if(inc + 1 < lstring_size)
                    {
                        if(cmpdata[inc + 1] == '/')
                            return ret;
                    }
                //if / is not // then / must be part of a param so no break;
                case ' '://continue
                {

                    for(uint32_t i = inc; inc < lstring_size && cmpdata[i] != ' ' && cmpdata[i] != '\r' && cmpdata[i] != '\n'; i++);

                    int32_t value = 0;
                    uint32_t savedCharNum = CharNum;

                    if(GetParamAsInt32WithType(value, false, PushArrayP_L + (ret.size() * 4)))
                    {
                        inc = CharNum - 1;
                        ret.push_back(SwapEndian(value));
                    }
                    else
                    {
                        CharNum = savedCharNum;
                        return ret;
                    }
                }
                break;
                case '\r':
                case '\n'://end
                return ret;
                default:
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << cmpdata[inc] << '\n';
                    Throw("PushArrayP Invalid Data");
                break;
            }

			inc++;
        }
        return ret;
    }
    float GetParamAsFloat(){
        CharStr str = GetParami();
        char* endp;

        if(str.str[0] == 0)
        {
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Throw("Param Not Found");
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
            Throw("String To Float Failed");
        }
        else if (*endp != 0) {
            //invalid char
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            cout << "Index: " << endp - str.str << "\r\n";
            Throw("String To Float Failed");
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
            Throw("Param Not Found");
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
                    Throw("Unk Hash Parse Failed");
                }
                else if (*endp != 0) {
                    //invalid char
                    cout << "Error on line " << line << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineG() << "\r\n";
                    cout << "Index: " << endp - str.str << "\r\n";
                    Throw("Unk Hash Parse Failed");
                }
                else
                    return value;

            }
        }


        return Joaat(str.str);
    }
    uint32_t GetParamAsIorF(){
        CharStr str = GetParami();
        char* endp;

        if(str.str[0] == 0)
        {
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            Throw("Param Not Found");
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
            Throw("String To Int or Float Failed");
        }
        else if (*endp != 0) {
            //invalid char
            cout << "Error on line " << line << "\r\n";
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineG() << "\r\n";
            cout << "Index: " << endp - str.str << "\r\n";
            Throw("String To Int or Float Failed");
        }
        else {
            return value;
        }
        return 0;
    }
    void GetSwitchParams(){

        //switch [1337 @MyLabel]:[1338 @NextLabel]
        vector<uint8_t> TempTable;
        uint32_t ssize = gtable->size();

        TempTable.push_back(OP_Switch);
        TempTable.push_back(0);//len = index 0

        uint32_t SwitchCount = 0;
        bool switchended = false,IsSwitchContinuing = true, HasCaseBeenPlaced = false;
		CharNum++;
		uint32_t Starti = CharNum;

        while(CharNum < lstring_size)
        {
            switch(cmpdata[CharNum])
            {
                case '[':
                    {
                    //get case value
                    if(IsSwitchContinuing)
                    {
                        SwitchCount++;
                        int32_t value = 0;
                        GetParamAsInt32WithType(value, true, TempTable.size());

                        TempTable.push_back(*(((uint8_t*)&value) + 3));
                        TempTable.push_back(*(((uint8_t*)&value) + 2));
                        TempTable.push_back(*(((uint8_t*)&value) + 1));
                        TempTable.push_back(*(uint8_t*)&value);
                        IsSwitchContinuing = false;
                        HasCaseBeenPlaced = true;
                    }
                    else
                    {
                        cout << "Error on line " << line << "\r\n";
                        cout << "Code: " << 0 << "\r\n";
                        cout << "Line: " << GetLineG() << "\r\n";
                        Throw("Invalid Switch Format");
                    }

                    }
                    break;
                case '@':
                    //get label value
                    if(HasCaseBeenPlaced)
                    {
                        gJumps->push_back({JumpType::Switch, ssize + TempTable.size(),LineStart, line, GetParamAsLabel(false)});
                        TempTable.push_back(OP_Nop);
                        TempTable.push_back(OP_Nop);
                        HasCaseBeenPlaced = false;
                    }
                    else
                    {
                        cout << "Error on line " << line << "\r\n";
                        cout << "Code: " << 0 << "\r\n";
                        cout << "Line: " << GetLineG() << "\r\n";
                        Throw("Invalid Switch Format");
                    }
                    continue;
                case ']':
                    //end switch case
                    if(CharNum + 1 < lstring_size)
                    {
                        if(cmpdata[CharNum + 1] == ':')
                        {
                            //continue switch cases
                            CharNum++;
                            IsSwitchContinuing = true;
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
                                Throw("Switch Count Too Large");
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
                                        gtable->resize(ssize + TempTable.size());
                                        memcpy(gtable->data() + ssize, TempTable.data(), TempTable.size());
                                        return;
                                    }

                                    uint32_t rem = (16384 - (ssize % 16384));
                                    for(uint32_t i = 0; i < rem; i++)
                                    {
                                        gtable->push_back(OP_Nop);
                                    }

                                }

                                gtable->resize(ssize + TempTable.size());
                                memcpy(gtable->data() + ssize, TempTable.data(), TempTable.size());
                                return;
                            }
                            else
                            {
                                cout << "Error on line " << line << "\r\n";
                                cout << "Code: " << 0 << "\r\n";
                                cout << "Line: " << GetLineG() << "\r\n";
                                Throw("Invalid Switch Format");
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
                                gtable->resize(ssize + TempTable.size());
                                memcpy(gtable->data() + ssize, TempTable.data(), TempTable.size());
                                return;
                            }

                            uint32_t rem = (16384 - (ssize % 16384));
                            for(uint32_t i = 0; i < rem; i++)
                            {
                                gtable->push_back(OP_Nop);
                            }

                        }

                        gtable->resize(ssize + TempTable.size());
                        memcpy(gtable->data() + ssize, TempTable.data(), TempTable.size());
                        return;
                    }
                    else
                    {
                        cout << "Error on line " << line << "\r\n";
                        cout << "Code: " << 0 << "\r\n";
                        cout << "Line: " << GetLineG() << "\r\n";
                        Throw("Invalid Switch Format");
                    }
                break;


            }
			CharNum++;
        }

        cout << "Error on line " << line << "\r\n";
        cout << "Code: " << 0 << "\r\n";
        cout << "Line: " << GetLineG() << "\r\n";
        Throw("Invalid Switch Format");
    }
    bool GetLabelLoc(uint32_t * out,string& str, uint32_t pos){
        map<string,uint32_t>::iterator iter = gLabelLocations->find(str);
        if (iter != gLabelLocations->cend()){
            *out = iter->second;
            return true;
        }
        else{
            cout << "Error on line " << line << "\r\n";//wrong line
            cout << "Code: " << 0 << "\r\n";
            cout << "Line: " << GetLineGAtPos(pos) << "\r\n";
            cout << "Label: " << str << "\r\n";
            Throw("Could Not Find Label");
        }
        return false;
    }

//}

void RSC::Compile(string& data, int pgBase, char* scriptName, bool ignoreNops, bool issco)
{
    vector<vector<uint8_t>>* CodePagesPTR;
    vector<int32_t>* StaticsPTR;
    uint32_t* GlobalsSignaturePTR;
    vector<uint32_t>* nativesPTR;
    uint32_t* ParameterCountPTR;


    if(issco)
    {
        CodePagesPTR = &Header_SCO.CodePages;
        StaticsPTR = &Header_SCO.Statics;
        Header_SCO.GlobalsSignature = 0x349D018A;
        GlobalsSignaturePTR = &Header_SCO.GlobalsSignature;
        nativesPTR = &Header_SCO.Natives;
        ParameterCountPTR = &(Header_SCO.ParameterCount = 0);
        Header_SCO.unk12 = -3;
        Header_SCO.unk36 = 0;
        Header_SCO.unk40 = 0;
        Header_SCO.unk44 = 0;
        Header_SCO.GlobalsCount = 0;//make editable in source


    }
    else
    {
        CodePagesPTR = &Header_XSC.CodePages;
        StaticsPTR = &Header_XSC.Statics;
        Header_XSC.GlobalsSignature = 0x349D018A;
        GlobalsSignaturePTR = &Header_XSC.GlobalsSignature;
        nativesPTR = &Header_XSC.Natives;
        ParameterCountPTR = &(Header_XSC.ParameterCount = 0);
        Header_XSC.PgBase = pgBase;
    }

    vector<vector<uint8_t>>& CodePages = *CodePagesPTR;
    vector<int32_t>& Statics = *StaticsPTR;
    uint32_t& GlobalsSignature = *GlobalsSignaturePTR;
    vector<uint32_t>& natives = *nativesPTR;
    uint32_t& ParameterCount = *ParameterCountPTR;


    vector<uint8_t> table;
    uint32_t SavedTableSize = 0;

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
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'u':
                        if(CharNum + 3 > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
                        }
                        if(!(tolower(data[CharNum + 1]) == 's' && tolower(data[CharNum + 2]) == 'h'))
                        {
                            UnkOpcodeError();
                        }
                        CharNum += 3;
                        switch(tolower(data[CharNum]))
                        {
                            case 's'://{
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Throw("Param Not Found");
                                        break;
                                    case ' '://pushs
                                        //parse param
                                        {
                                            CharStr str = GetParami();
                                            char *endp;
                                            int32_t value = strtol(str.str, &endp, 0);
                                            if(!(value <= 32767 || value >= -32768))
                                            {
                                                cout << "Error on line " << line << "\r\n";
                                                cout << "Code: " << 0 << "\r\n";
                                                cout << "Line: " << GetLineG() << "\r\n";
                                                Throw("Opcode Data Out Of Bounds");
                                            }

                                            if(value >= -1 && value <= 7)
                                            {
                                                table.push_back(value + 139);
                                            }
                                            else if(value >= 8 && value <= 255)
                                            {
                                                Fix16384(PushB_L);
                                                table.push_back(OP_PushB);
                                                table.push_back((uint8_t)value);
                                            }
                                            else
                                            {
                                                Fix16384(PushS_L);
                                                table.push_back(OP_PushS);
                                                PushInt16(value);
                                            }
                                        }
										break;
                                    case 't'://pushstring will have to check ring
                                        {
                                            ChkRem("ring", 4, true);
                                            //parse param

                                            string tempstr = GetParamString();

                                            const char * ctempstr = tempstr.c_str();
                                            if(tempstr == "")
                                            {
                                                table.push_back(OP_PushStringNull);
                                                break;
                                            }
                                            uint32_t len = tempstr.length() + 1;
                                            if(len > 254)
                                            {
                                                cout << "Error on line " << line << "\r\n";
                                                cout << "Code: " << 0 << "\r\n";
                                                cout << "Line: " << GetLineG() << "\r\n";
                                                Throw("String Length Can Not Be Over 254");
                                            }

                                            Fix16384(len + PushString_L);
                                            table.push_back(OP_PushString);
                                            table.push_back((uint8_t)len);
                                            uint32_t savedsize = table.size();
                                            table.resize(savedsize + len);
                                            memcpy(table.data() + savedsize, tempstr.c_str(), len);



                                        }
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
                            //}
                                break;
                            case '_'://{
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '-'://push_-1 will have to check 1
                                        ChkRem("1", 1);
										//append code
										table.push_back(OP_Push_Neg1);
                                        break;
                                    case 'n'://push_neg1 will have to check eg1
                                        ChkRem("eg1", 3);
                                        //append code
										table.push_back(OP_Push_Neg1);
                                        break;
                                    case '0'://push_0
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_0);
                                        break;
                                    case '1'://push_1
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_1);
                                        break;
                                    case '2'://push_2
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_2);
                                        break;
                                    case '3'://push_3
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_3);
                                        break;
                                    case '4'://push_4
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_4);
                                        break;
                                    case '5'://push_5
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_5);
                                        break;
                                    case '6'://push_6
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_6);
                                        break;
                                    case '7'://push_7
                                        ChkRem();
                                        //append code
										table.push_back(OP_Push_7);
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;

                                }
                            //}
                                break;
                            case '\r':
                            case '\n'://{
                                cout << "Error on line " << line << "\r\n";
                                cout << "Code: " << 0 << "\r\n";
                                cout << "Line: " << GetLineG() << "\r\n";
                                Throw("Param Not Found");
                            //}
                                break;
                            case ' '://push
                                {
                                    int32_t value = 0;
                                    GetParamAsInt32WithType(value, true, 1);

                                    //getenum
                                    //getloc
                                    //gethash

                                    if(value >= -1 && value <= 7)
                                    {
                                        table.push_back(value + 139);
                                    }
                                    else if(value < -1)//push getloc rets 0//might change
                                    {
                                        if(value >= -32768)
                                        {
                                            Fix16384(PushS_L);
                                            table.push_back(OP_PushS);
                                            PushInt16((int16_t)value);
                                        }
                                        else
                                        {
                                            Fix16384(Push_L);
                                            table.push_back(OP_Push);
                                            PushInt32(value);
                                        }
                                    }
                                    else if(value < 256)
                                    {
                                        Fix16384(PushB_L);
                                        table.push_back(OP_PushB);
                                        table.push_back((uint8_t)value);
                                    }
                                    else if(value < 32768)
                                    {
                                        Fix16384(PushS_L);
                                        table.push_back(OP_PushS);
                                        PushInt16((int16_t)value);
                                    }
                                    else if(value < 16777216)
                                    {
                                        Fix16384(PushI24_L);
                                        table.push_back(OP_PushI24);
                                        PushInt24(value);
                                    }
                                    else
                                    {
                                        Fix16384(Push_L);
                                        table.push_back(OP_Push);
                                        PushInt32(value);
                                    }

                                    break;
                                }
                                break;
                            case 'b'://{
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Throw("Param Not Found");
                                        break;
                                    case ' '://pushb
                                        //parse param
                                        {
                                            uint8_t value = GetParamAsInt<uint8_t>();

                                            if(value <= 7)
                                            {
                                                table.push_back(value + 139);
                                            }
                                            else
                                            {
                                                Fix16384(PushB_L);
                                                table.push_back(OP_PushB);
                                                table.push_back(value);
                                            }
                                        }
                                        break;
                                    case '2'://pushb2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(PushB2_L);
                                        table.push_back(OP_PushB2);
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        break;
                                    case '3'://pushb3
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(PushB3_L);
                                        table.push_back(OP_PushB3);
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        table.push_back(GetParamAsInt<uint8_t>());
                                        table.push_back(GetParamAsInt<uint8_t>());
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
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Throw("Param Not Found");
                                        break;
                                    case ' '://pushf
                                    {
                                        //parse param

                                        float value = GetParamAsFloat();

                                        switch(*(uint32_t*)&value)
                                        {
                                            case 3212836864:
                                                table.push_back(OP_PushF_Neg1);
                                            goto EndPushFloat;
                                            case 0:
                                                table.push_back(OP_PushF_0);
                                            goto EndPushFloat;
                                            case 1065353216:
                                                table.push_back(OP_PushF_1);
                                            goto EndPushFloat;
                                            case 1073741824:
                                                table.push_back(OP_PushF_2);
                                            goto EndPushFloat;
                                            case 1077936128:
                                                table.push_back(OP_PushF_3);
                                            goto EndPushFloat;
                                            case 1082130432:
                                                table.push_back(OP_PushF_4);
                                            goto EndPushFloat;
                                            case 1084227584:
                                                table.push_back(OP_PushF_5);
                                            goto EndPushFloat;
                                            case 1086324736:
                                                table.push_back(OP_PushF_6);
                                            goto EndPushFloat;
                                            case 1088421888:
                                                table.push_back(OP_PushF_7);
                                            goto EndPushFloat;
                                        }

                                        Fix16384(PushF_L);
                                        table.push_back(OP_PushF);
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
                                            Throw("Index Out Of Bounds");
                                        }
                                        switch(tolower(data[CharNum]))
                                        {
                                            case '-'://pushf_-1 will have to check 1
                                                ChkRem("1", 1);
                                                //append code
												table.push_back(OP_PushF_Neg1);
                                                break;
                                            case 'n'://pushf_neg1 will have to check eg1
                                                ChkRem("eg1", 3);
                                                //append code
												table.push_back(OP_PushF_Neg1);
                                                break;
                                            case '0'://pushf_0
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_0);
                                                break;
                                            case '1'://pushf_1
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_1);
                                                break;
                                            case '2'://pushf_2
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_2);
                                                break;
                                            case '3'://pushf_3
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_3);
                                                break;
                                            case '4'://pushf_4
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_4);
                                                break;
                                            case '5'://pushf_5
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_5);
                                                break;
                                            case '6'://pushf_6
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_6);
                                                break;
                                            case '7'://pushf_7
                                                ChkRem();
                                                //append code
												table.push_back(OP_PushF_7);
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
                            case 'i':// pushi24 will need to check 24
                            {
                                ChkRem("24", 2, true);
                                //parse param
                                    uint32_t value = GetParamAsInt<uint32_t>();

                                    if(value <= 7)
                                    {
                                        table.push_back(value + 139);
                                    }
                                    else if(value < 256)
                                    {
                                        Fix16384(PushB_L);
                                        table.push_back(OP_PushB);
                                        table.push_back((uint8_t)value);
                                    }
                                    else if (value < 32768)
                                    {
                                        Fix16384(PushS_L);
                                        table.push_back(OP_PushS);
                                        PushInt16(value);
                                    }
                                    else
                                    {
                                        Fix16384(PushI24_L);
                                        table.push_back(OP_PushI24);
                                        PushInt24(value);
                                    }
                                }
                                break;
                            case 'a':// pusharrayp will need to check rrayp
                            {
                                ChkRem("rrayp", 5, true);
                                vector<uint32_t> value = GetParamAsVector();
                                uint32_t ValueSizeBytes = value.size() * 4;

                                Fix16384(ValueSizeBytes + PushArrayP_L);

                                table.push_back(OP_PushArrayP);
                                PushInt32(ValueSizeBytes);//reverse?

                                uint32_t tablesize = table.size();
                                table.resize(tablesize + ValueSizeBytes);
                                memcpy(table.data() + tablesize, value.data(), ValueSizeBytes);

                            }
                                break;
                            default:
                                UnkOpcodeError();

                        }
                        break;
                    case 'c'://pcall will need to check all
                        ChkRem("all", 3);
                        //append code
						table.push_back(OP_pCall);
                        break;
                    case 'g'://pget will need to check et
                        ChkRem("et", 2);
                        //append code
						table.push_back(OP_pGet);
                        break;
                    case 'p'://ppeekset will need to check eekset
                        ChkRem("eekset", 6);
                        //append code
						table.push_back(OP_pPeekSet);
                        break;
                    case 's'://pset will need to check et
                        ChkRem("et", 2);
                        //append code
						table.push_back(OP_pSet);
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
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'a':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'l'://{
                                CharNum+=2;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
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
                                        uint32_t Hash = GetParamAsHash();//should sooner or later check if the native is valid
                                        uint16_t index = 0;
                                        std::vector<uint32_t>::iterator loc = find(natives.begin(), natives.end(), Hash);
                                        if (loc == natives.end())
                                        {
                                            index = natives.size();
                                            natives.push_back(Hash);
                                        }
                                        else index = loc - natives.begin();

                                        table.push_back(OP_CallNative);

                                        uint8_t parameterCount = GetParamAsInt<uint8_t>();
                                        uint8_t ret = GetParamAsInt<uint8_t>();
                                        if(ret > 1)
                                        {
                                            cout << "Error on line " << line << "\r\n";
                                            cout << "Code: " << 0 << "\r\n";
                                            cout << "Line: " << GetLineG() << "\r\n";
                                            Throw("Native Calls Can Only Have One Return");
                                        }
                                        PushInt16(NativeParsing::SetNewIndex(index, parameterCount, ret == 1));
                                    }
                                    break;
                                    case ' '://call
                                        //parse param
                                        Fix16384(Call_L);
                                        CharNum++;
                                        Jumps.push_back({JumpType::Call, table.size(),LineStart,line,GetParamAsLabel(false)});
                                        table.push_back(OP_Nop);//call op

                                        table.push_back(OP_Nop);
                                        table.push_back(OP_Nop);
                                        break;
                                    case '\r':
                                    case '\n':
                                        cout << "Error on line " << line << "\r\n";
                                        cout << "Code: " << 0 << "\r\n";
                                        cout << "Line: " << GetLineG() << "\r\n";
                                        Throw("Param Not Found");
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }
							//}
								break;
                            case 't'://{ catch will have to check ch
                                ChkRem("ch", 2);
                                //append code
								table.push_back(OP_Catch);
							//}
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
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_CmpEQ);
                                break;
                            case 'n'://cmpne will have to check e
                                ChkRem("e", 1);
                                //append code
								table.push_back(OP_CmpNE);
                                break;
                            case 'g':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://cmpge
                                        ChkRem();
                                        //append code
										table.push_back(OP_CmpGE);
                                        break;
                                    case 't'://cmpgt
                                        ChkRem();
                                        //append code
										table.push_back(OP_CmpGT);
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
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://cmple
                                        ChkRem();
                                        //append code
										table.push_back(OP_CmpLE);
                                        break;
                                    case 't'://cmplt
                                        ChkRem();
                                        //append code
										table.push_back(OP_CmpLT);
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
                    Throw("Index Out Of Bounds");
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
                //{ check rem et
                CharNum+=3;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Throw("Index Out Of Bounds");
                }
                if(!(tolower(data[CharNum - 2]) == 'e' && tolower(data[CharNum - 1]) == 't'))
                {
                    UnkOpcodeError();
                }
                //}
                switch(tolower(data[CharNum]))
                {
                    case 'a'://{
                        CharNum+=5;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_GetArray1);
								table.push_back(GetParamAsInt<uint8_t>());
                                break;
                            case '2'://getarray2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetArray2_L);
								table.push_back(OP_GetArray2);
								PushInt16(GetParamAsInt<uint16_t>());
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '1'://getarrayp1
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetArrayP1_L);
										table.push_back(OP_GetArrayP1);
										table.push_back(GetParamAsInt<uint8_t>());
                                        break;
                                    case '2'://getarrayp2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetArrayP2_L);
										table.push_back(OP_GetArrayP2);
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
                        //}
                        break;
                    case 'f'://{
                        CharNum+=5;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_GetFrame1);
								table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Frame));
                                break;
                            case '2'://getframe2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetFrame2_L);
								table.push_back(OP_GetFrame2);
								PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Frame));
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '1'://getframep1
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetFrameP1_L);
										table.push_back(OP_GetFrameP1);
										table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Frame));
                                        break;
                                    case '2'://getframep2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetFrameP2_L);
										table.push_back(OP_GetFrameP2);
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
                        //}
                        break;
                    case 'g'://{
                        CharNum+=6;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_GetGlobal2);
								PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Global));
                                break;
                            case '3'://getglobal3
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetGlobal3_L);
								table.push_back(OP_GetGlobal3);
                                PushInt24(GetParamAsInt<uint32_t>(ParamTypes::Global));
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '2'://getglobalp2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetGlobalP2_L);
										table.push_back(OP_GetGlobalP2);
										PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Global));
                                        break;
                                    case '3'://getglobalp3
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetGlobalP3_L);
										table.push_back(OP_GetGlobalP3);
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
                        //}
                        break;
                    case 'i'://{
                        CharNum+=3;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_GetImm1);
								table.push_back(GetParamAsInt<uint8_t>());
                                break;
                            case '2'://getimm2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetImm2_L);
								table.push_back(OP_GetImm2);
								PushInt16(GetParamAsInt<uint16_t>());
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        //}
                        break;
                    case 's'://{
                        CharNum+=6;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_GetStatic1);
								table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Static));
                                break;
                            case '2'://getstatic2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(GetStatic2_L);
								table.push_back(OP_GetStatic2);
								PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Static));
                                break;
                            case 'p':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case '1'://getstaticp1
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetStaticP1_L);
										table.push_back(OP_GetStaticP1);
										table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Static));
                                        break;
                                    case '2'://getstaticp2
                                        ChkRem(nullptr,0,true);
                                        //parse param
                                        Fix16384(GetStaticP2_L);
										table.push_back(OP_GetStaticP2);
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
                        //}
                        break;
                    default:
                        UnkOpcodeError();
                    break;
                }
            //}
                break;
            case '\n': line++; CharNum++; LineStart = CharNum; SavedTableSize = table.size(); lastLineWasLabel = false;
				break;
            case ':':{
                if(lastLineWasLabel)
                    table.push_back(OP_Nop);
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

                    Throw("Label already exists");
                }
                lastLineWasLabel = true;
                }
                break;
            case 's'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'e':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum]) == 't')
                        {
                            CharNum++;
                            if(CharNum > string_size)
                            {
                                cout << "Error on line " << line << "\r\n";
                                Throw("Index Out Of Bounds");
                            }
                            switch(tolower(data[CharNum]))
                            {
                                case 'a':
                                    CharNum+=5;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Throw("Index Out Of Bounds");
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
											table.push_back(OP_SetArray1);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case '2'://setarray2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetArray2_L);
											table.push_back(OP_SetArray2);
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
                                        Throw("Index Out Of Bounds");
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
											table.push_back(OP_SetFrame1);
											table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Frame));
                                            break;
                                        case '2'://setframe2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetFrame2_L);
											table.push_back(OP_SetFrame2);
											PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Frame));
                                            break;
                                        case 'n'://setframename will need to check ame
                                        {
											ChkRem("ame",3,true);
											//parse param
											uint16_t value = GetParamAsInt<uint16_t>();
											string str = GetParams();
											
											map<string,uint16_t>::iterator fni = FrameNames.find(str);
											if (fni == FrameNames.end())
												FrameNames.insert({str, value});
											else//update frame name on redeclaration
												fni->second = value;
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
                                        Throw("Index Out Of Bounds");
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
											table.push_back(OP_SetGlobal2);
											PushInt16(GetParamAsInt<uint16_t>(ParamTypes::Global));
                                            break;
                                        case '3'://setglobal3
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetGlobal3_L);
											table.push_back(OP_SetGlobal3);
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
                                                Throw("Global Index Out Of Bounds");
                                            }

                                             if (GlobalNames.count(str) == 0)
                                                GlobalNames.insert({str, value});
                                            }

                                            break;
                                        case 's'://setglobalsversion will need to check version
                                            ChkRem("version",7,true);
                                            //parse param
                                            GlobalsSignature = GetParamAsInt<uint32_t>();
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
                                        Throw("Index Out Of Bounds");
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
											table.push_back(OP_SetImm1);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case '2'://setimm2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetImm2_L);
											table.push_back(OP_SetImm2);
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
                                        Throw("Index Out Of Bounds");
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
											table.push_back(OP_SetStatic1);
											table.push_back(GetParamAsInt<uint8_t>(ParamTypes::Static));
                                            break;
                                        case '2'://setstatic2
                                            ChkRem(nullptr,0,true);
                                            //parse param
                                            Fix16384(SetStatic2_L);
											table.push_back(OP_SetStatic2);
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
                                                Statics.resize(GetParamAsInt<uint16_t>());
                                            }
                                            else
                                            {
                                                cout << "Error on line " << line << "\r\n";
                                                cout << "Code: " << 0 << "\r\n";
                                                cout << "Line: " << GetLineG() << "\r\n";
                                                Throw("Statics Count Already Set");
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


                                            if(staticIndex < Statics.size())
                                                Statics[staticIndex] = staticValue;
                                            else
                                            {
                                                cout << "Error on line " << line << "\r\n";
                                                cout << "Code: " << 0 << "\r\n";
                                                cout << "Line: " << GetLineG() << "\r\n";
                                                Throw("Static Index Out Of Bounds");
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
                                            Throw("Custom Native Names Must Start With _");
                                        }
                                        else if (NativeNames.count(str) == 0)
                                            NativeNames.insert({str, value});

                                        }
                                        break;
                                    case 'p'://setparamcount will need to check aramcount
                                            ChkRem("aramcount",9,true);
                                            //parse param
                                            ParameterCount = GetParamAsInt<uint32_t>();

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
                            Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum]) == 'r')
                        {
                            CharNum++;
                            if(CharNum > string_size)
                            {
                                cout << "Error on line " << line << "\r\n";
                                Throw("Index Out Of Bounds");
                            }
                            switch(tolower(data[CharNum]))
                            {
                                case 'a':
                                    CharNum+=3;
                                    if(CharNum > string_size)
                                    {
                                        cout << "Error on line " << line << "\r\n";
                                        Throw("Index Out Of Bounds");
                                    }
                                    switch(tolower(data[CharNum]))
                                    {
                                        case 'i'://straddi
                                            ChkRem(nullptr,0,true);

                                            //parse param
                                            Fix16384(StrAddI_L);
											table.push_back(OP_StrAddI);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case ' '://stradd
                                            //parse param
                                            Fix16384(StrAdd_L);
											table.push_back(OP_StrAdd);
											table.push_back(GetParamAsInt<uint8_t>());
                                            break;
                                        case '\r':
                                        case '\n':
                                            cout << "Error on line " << line << "\r\n";
                                            cout << "Code: " << 0 << "\r\n";
                                            cout << "Line: " << GetLineG() << "\r\n";
                                            Throw("Param Not Found");
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
									table.push_back(OP_StrCopy);
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
						table.push_back(OP_Sub);
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
                    Throw("Index Out Of Bounds");
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
                        Throw("Param Not Found");
                        break;
                    case ' '://jump
                        //parse param
                        Fix16384(Jump_L);
                        table.push_back(OP_Jump);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OP_Nop);
                        table.push_back(OP_Nop);
                        break;
                    case 'e'://jumpeq will need to check q
                        ChkRem("q",1,true);
                        //parse param
                        Fix16384(JumpEQ_L);
                        table.push_back(OP_JumpEQ);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OP_Nop);
                        table.push_back(OP_Nop);
                        break;
                    case 'f'://jumpfalse will need to check alse
						ChkRem("alse",4,true);
                        //parse param
                        Fix16384(JumpFalse_L);
                        table.push_back(OP_JumpFalse);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OP_Nop);
                        table.push_back(OP_Nop);
                        break;
                    case 'g':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'e'://jumpge
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpGE_L);
                                table.push_back(OP_JumpGE);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OP_Nop);
                                table.push_back(OP_Nop);
                            break;
                            case 't'://jumpgt
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpGT_L);
                                table.push_back(OP_JumpGT);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OP_Nop);
                                table.push_back(OP_Nop);
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
                            Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'e'://jumple
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpLE_L);
                                table.push_back(OP_JumpLE);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OP_Nop);
                                table.push_back(OP_Nop);
                                break;
                            case 't'://jumplt
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(JumpLT_L);
                                table.push_back(OP_JumpLT);
                                CharNum++;
                                Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                                table.push_back(OP_Nop);
                                table.push_back(OP_Nop);
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
                        table.push_back(OP_JumpNE);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OP_Nop);
                        table.push_back(OP_Nop);
                        break;
                    case 't'://jumptrue will need to check rue
                        ChkRem("rue",3,true);
                        //parse param
                        table.push_back(OP_Push_1);
                        Fix16384(JumpEQ_L);
                        table.push_back(OP_JumpEQ);
                        CharNum++;
                        Jumps.push_back({JumpType::Jump, table.size(),LineStart,line,GetParamAsLabel(false)});
                        table.push_back(OP_Nop);
                        table.push_back(OP_Nop);
                        break;
                    default:
                            UnkOpcodeError();
                        break;

                }
                //}
                break;
            case 'r':
                CharNum+=2;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Throw("Index Out Of Bounds");
                }
                if(tolower(data[CharNum - 1]) != 'e')
                {
                    UnkOpcodeError();
                }
                switch(tolower(data[CharNum]))
                {
                    case 't'://return will need to check urn
                    {
                        ChkRem("urn",3,true);
                        //parse param

                        uint8_t popParams = GetParamAsInt<uint8_t>();
                        uint8_t returns = GetParamAsInt<uint8_t>();

                        if(popParams <= 3 && returns <= 3)
                            table.push_back(OP_ReturnP0R0 + (popParams * 4) + returns);
                        else
                        {
                            Fix16384(Return_L);
                            table.push_back(OP_Return);
                            table.push_back(popParams);
                            table.push_back(returns);
                        }
                    }
                    break;
                    case 'g'://registerglobals will need to check isterglobals
                    ChkRem("isterglobals",12,true);
                    if(issco)
                    {
                        Header_SCO.GlobalsCount = GetParamAsInt<uint32_t>();
                    }
                    break;
                }
                break;
            case 'n'://{
                CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'e'://neg will need to check g
                        ChkRem("g",1,false);
                        //append code
						table.push_back(OP_Neg);
                        break;
                    case 'o':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'p'://nop
                                ChkRem();
                                //append code
                                if(!ignoreNops)
								table.push_back(OP_Nop);
                                break;
                            case 't'://not
                                ChkRem();
                                //append code
								table.push_back(OP_Not);
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
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'r'://fromstack will need to check omstack
						ChkRem("omstack",7,false);
                        //append code
						table.push_back(OP_FromStack);
                        break;
                    case 't':
                        CharNum+=2;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_FtoI);
                                break;
                            case 'v'://ftov
                                ChkRem();
                                //append code
								table.push_back(OP_FtoV);
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
                        table.push_back(OP_Function);
                        table.push_back(GetParamAsInt<uint8_t>());
                        PushInt16(GetParamAsInt<uint16_t>());
                        table.push_back(0);//function name

                        FrameNames.clear();

                        break;
                    case 'a'://fadd will need to check dd
                        ChkRem("dd",2,false);
                        //append code
						table.push_back(OP_fAdd);
                        break;
                    case 'c':
                        CharNum+=3;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_fCmpEQ);
                                break;
                            case 'g':
                                CharNum++;
                                if(CharNum > string_size)
                                {
                                    cout << "Error on line " << line << "\r\n";
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://fcmpge
                                        ChkRem();
                                        //append code
										table.push_back(OP_fCmpGE);
                                        break;
                                    case 't'://fcmpgt
                                        ChkRem();
                                        //append code
										table.push_back(OP_fCmpGT);
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
                                    Throw("Index Out Of Bounds");
                                }
                                switch(tolower(data[CharNum]))
                                {
                                    case 'e'://fcmple
                                        ChkRem();
                                        //append code
										table.push_back(OP_fCmpLE);
                                        break;
                                    case 't'://fcmplt
                                        ChkRem();
                                        //append code
										table.push_back(OP_fCmpLT);
                                        break;
                                    default:
                                        UnkOpcodeError();
                                    break;
                                }

                                break;
                            case 'n'://fcmpne will need to check e
                                ChkRem("e",1,false);
                                //append code
								table.push_back(OP_fCmpNE);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'd'://fdiv will need to check iv
                        ChkRem("iv",2,false);
                        //append code
						table.push_back(OP_fDiv);
                        break;
                    case 'm':
                        CharNum++;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
                        }
                        switch(tolower(data[CharNum]))
                        {
                            case 'o'://fmod will need to check d
                                ChkRem("d",1,false);
                                //append code
								table.push_back(OP_fMod);
                                break;
                            case 'u'://fmult will need to check lt
                                ChkRem("lt",2,false);
                                //append code
								table.push_back(OP_fMult);
                                break;
                            default:
                                UnkOpcodeError();
                            break;
                        }
                        break;
                    case 'n'://fneg will need to check eg
                        ChkRem("eg",2,false);
                        //append code
						table.push_back(OP_fNeg);
                        break;
                    case 's'://fsub will need to check ub
                        ChkRem("ub",2,false);
                        //append code
						table.push_back(OP_fSub);
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
                    Throw("Index Out Of Bounds");
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
                            Throw("Index Out Of Bounds");
                        }
                        if(tolower(data[CharNum - 1]) == 'd')
                        {
                            switch(tolower(data[CharNum]))
                            {
                                case '1'://add1
                                    ChkRem(nullptr,0,true);
                                    //parse param
                                    Fix16384(Add1_L);
									table.push_back(OP_Add1);
									table.push_back(GetParamAsInt<uint8_t>());
                                    break;
                                case '2'://add2
                                    ChkRem(nullptr,0,true);
                                    //parse param
                                    Fix16384(Add2_L);
									table.push_back(OP_Add2);
									PushInt16(GetParamAsInt<uint16_t>());
                                    break;
                                case '\n':
                                case ' ':
                                case '\r'://add
                                    add:
                                    //append code
									table.push_back(OP_Add);
                                    break;
                                case '/':
                                    if(CharNum + 1 < string_size)
                                    {
                                        if(data[CharNum + 1] == '/')
                                        {
                                            table.push_back(OP_Add);
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
						table.push_back(OP_And);
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
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'i'://div will need to check v
                        ChkRem("v",1,false);
                        //append code
						table.push_back(OP_Div);
                        break;
                    case 'r'://drop will need to check op
                        ChkRem("op",2,false);
                        //append code
						table.push_back(OP_Drop);
                        break;
                    case 'u'://dup will need to check p
                        ChkRem("p",1,false);
                        //append code
						table.push_back(OP_Dup);
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
				table.push_back(OP_Or);
            //}
                break;
            case 't'://{
                 CharNum++;
                if(CharNum > string_size)
                {
                    cout << "Error on line " << line << "\r\n";
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'h'://throw will need to check row
                        ChkRem("row",3,false);
                        //append code
						table.push_back(OP_Throw);
                        break;
                    case 'o'://tostack will need to check stack
						ChkRem("stack",5,false);
                        //append code
						table.push_back(OP_ToStack);
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
                    Throw("Index Out Of Bounds");
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
						table.push_back(OP_ItoF);
                        break;
                    case 's'://itos
                        ChkRem(nullptr,0,true);
                        //parse param
                        Fix16384(ItoS_L);
						table.push_back(OP_ItoS);
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
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'e'://memcopy will need to check mcopy
                        ChkRem("mcopy",5,false);

                        //append code
						table.push_back(OP_MemCopy);
                        break;
                    case 'o'://mod will need to check d
                        ChkRem("d",1,false);
                        //append code
						table.push_back(OP_Mod);
                        break;
                    case 'u':
                        CharNum+=2;
                        if(CharNum > string_size)
                        {
                            cout << "Error on line " << line << "\r\n";
                            Throw("Index Out Of Bounds");
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
								table.push_back(OP_Mult1);
								table.push_back(GetParamAsInt<uint8_t>());
                                break;
                            case '2'://mult2
                                ChkRem(nullptr,0,true);
                                //parse param
                                Fix16384(Mult2_L);
								table.push_back(OP_Mult2);
								PushInt16(GetParamAsInt<uint16_t>());
                                break;
                            case '\n':

                            case ' ':
                            case '\r'://mult
                                mult:
                                //append code
								table.push_back(OP_Mult);
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
                    Throw("Index Out Of Bounds");
                }
                switch(tolower(data[CharNum]))
                {
                    case 'a'://vadd will need to check dd
                        ChkRem("dd",2,false);
                        //append code
						table.push_back(OP_vAdd);
                        break;
                    case 'd'://vdiv will need to check iv
                        ChkRem("iv",2,false);
                        //append code
						table.push_back(OP_vDiv);
                        break;
                    case 'm'://vmult will need to check ult
                        ChkRem("ult",3,false);
                        //append code
						table.push_back(OP_vMult);
                        break;
                    case 'n'://vneg will need to check eg
                        ChkRem("eg",2,false);
                        //append code
						table.push_back(OP_vNeg);
                        break;
                    case 's'://vsub will need to check ub
                        ChkRem("ub",2,false);
                        //append code
						table.push_back(OP_vSub);
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
                table.push_back(OP_Xor);
            //}
                break;
            default:
                CharNum++;
                break;

        }
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
                if(value >= 1048576)
                {
                    cout << "Error on line " << Jumps[ji].LineNum << "\r\n";
                    cout << "Code: " << 0 << "\r\n";
                    cout << "Line: " << GetLineGAtPos(Jumps[ji].LineStartPos) << "\r\n";
                    cout << "Pos: " << value << "\r\n";
                    Throw("Call is out of bounds");
                }

                table[Jumps[ji].TablePos] = CallParsing::GetNewCallOpCode(value);
                int16_t offset = CallParsing::GetNewCallOffset(value);
                table[Jumps[ji].TablePos + 1] = *(((uint8_t*)&offset) + 1);
                table[Jumps[ji].TablePos + 2] = *(uint8_t*)&offset;

            }
            else //jump
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
                    Throw("Label is out of bounds");
                }
                uint16_t shortval = (uint16_t)value;
                table[Jumps[ji].TablePos] = *(((uint8_t*)&shortval) + 1);
                table[Jumps[ji].TablePos + 1] = *((uint8_t*)&shortval);

//                uint8_t val1 = ReadByte();
//                uint8_t val2 = ReadByte();
//
//                int16_t val = val2 | (val1 << 8);
//
//                int64_t fullVal = val + Position;

            }

        }
    }

    //{ add code to code pages
    uint32_t tablesize = table.size();

    //cout << (tablesize + 16384 - 1) / 16384 << endl;
    //cout << tablesize << endl;

    if(tablesize > 16384)
    {
        CodePages.resize((tablesize + 16384 - 1) / 16384);
    }
    else CodePages.resize(1);

    uint32_t pagesize = CodePages.size();

    for(uint32_t i = 0; i < pagesize; i++)
    {
        if(i * 16384 + 16384 < tablesize)
        {
            CodePages[i].resize(16384);
            memcpy(CodePages[i].data(),table.data() + i * 16384, 16384);

        }
        else
        {
            uint32_t rem = tablesize - i * 16384;
            CodePages[i].resize(rem);
            memcpy(CodePages[i].data(),table.data() + i * 16384, rem);
            break;
        }
    }
    //}


    if(issco)
    {
        Header_SCO.NativesCount = natives.size();
        Header_SCO.CodeLength = table.size();
        Header_SCO.StaticsCount = Statics.size();
    }
    else
    {
        Header_XSC.NativesCount = natives.size();
        Header_XSC.CodeLength = table.size();
        Header_XSC.StaticsCount = Statics.size();
    }

}



//}


