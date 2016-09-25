#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <string>
#include <fstream>
#include "Utils.h"
#include "Constants.h"
#include "Crypto/aes256.h"
#include <algorithm>
#include "zlib.h"

using namespace std;
using namespace Utils::System;
using namespace Utils::Bitwise;
using namespace Constants;

namespace Utils{

    namespace BlockParsing
    {
        int CountOffNextBlockSize(int size, int blockSize)
        {
            return blockSize - (size % blockSize);
        }
        int NextBlockSize(int size, int blockSize)
        {
            int sizeLeft = CountOffNextBlockSize(size, blockSize);
            if (sizeLeft == 0)
                return size;
            return size + sizeLeft;
        }
        vector<char> GiveDataBlock(vector<char> data, int blockSize)
        {
            int sizeLeft = 0x10 - (data.size() % 0x10);
            if (sizeLeft == 0)
                return data;

            vector<char> newData(data.size() + sizeLeft);
            memcpy(&newData,&data,data.size());

            return newData;
        }
        vector<char> GiveDataBlock(char* data, int blockSize)
        {
            return GiveDataBlock(data + '\0', blockSize);
        }
        vector<char> GiveDataBlock(int size, int blockSize)
        {
            vector<char> temp(size);
            return GiveDataBlock(temp , blockSize);
        }

    }

    namespace IO
    {
        DLX LoadData(const char* loc) {
            ifstream is(loc, std::ios::in|std::ios::binary|std::ios::ate);
            DLX File;

            if (is.is_open()) {
                is.seekg(0, is.end);
                size_t datasize = is.tellg();
                is.seekg(0, is.beg);

                File.data = new char [datasize];
                File.length = datasize;
                is.read((char*)File.data, datasize);
                is.close();
            }
            else
                Throw("Input File Could Not Be Opened");

            return File;
        }

    }

    namespace System
    {
        void Throw(string str)
        {
            cout << "Exception: " << str << "\r\nPress ENTER to exit...\r\n" << flush;
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
            exit(0);
        }
        void Pause(string str)
        {
            if(str != "")
                cout << str << "\n";
            cout << "Press ENTER to continue..." << flush;
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
    }

    namespace Math
    {
        int64_t CeilDivInt(uint32_t a, uint32_t b)
        {
            if(a == 0 || b == 0)
                return 0;
            return 1 + ((a - 1) / b);
        }
    }

    namespace RSC85Parsing
    {
        uint32_t GetHeaderFormatFromFlag(uint32_t val)
        {
            uint8_t flags = val >> 24;
            switch(flags)
            {
                ///header is at a multiple of 4096 (in rockstar scripts that is always the last 4096)
                case RSC85_Flags_ReadBuffer4096:
                    return 4096;
                ///header is at a multiple of 65536 (in rockstar scripts that is always 0 because any other 65536 would yield the same result)
                case RSC85_Flags_ReadBuffer65536:
                    return 0;
                ///header is at a multiple of 16384 (in rockstar scripts that is always the last 16384)
                case RSC85_Flags_ReadBuffer16384:
                    return 16384;
                ///header is at a multiple of 8192 (in rockstar scripts that is always the last 8192)
                case RSC85_Flags_ReadBuffer8192:
                    return 8192;
            }
            return 0xFFFFFFFF;
        }
        uint32_t GetFlagFromReadbuffer(uint32_t buffer)
        {
            switch(buffer)
            {
                case 4096:
                    return RSC85_Flags_ReadBuffer4096_32;
                case 65536:
                    return RSC85_Flags_ReadBuffer65536_32;
                case 16384:
                    return RSC85_Flags_ReadBuffer16384_32;
                case 8192:
                    return RSC85_Flags_ReadBuffer8192_32;

            }
            return 0xFFFFFFFF;
        }

    }

    namespace DataConversion
    {
        char* IntToHex(uint32_t val)
        {
            const char hex_str[]= "0123456789ABCDEF";
            uint8_t* bin = (uint8_t*)&val;

            char str[9];

            for (uint32_t i = 0; i < 4; i++)
            {
                str[i * 2 + 0] = hex_str[(bin[i] >> 4) & 0x0F];
                str[i * 2 + 1] = hex_str[(bin[i]) & 0x0F];
            }
            str[8] = '\0';
            return str;
        }

        vector<NamedUint32> ReorderUint32Vector_SmallToBig(vector<uint32_t> vec, vector<const char*> name)
        {
            vector<NamedUint32> ret;
            ret.reserve(vec.size() + name.size());


            for(uint32_t i = 0; vec.size() != 0; i++)
            {
                uint32_t index = -(vec.begin() - min_element(vec.begin(), vec.end()));
                if(index > vec.size())
                    Throw("ReorderUint32Vector Out Of Bounds");

                ret.push_back({name[index],vec[index]});
                vec.erase(vec.begin() + index);
                name.erase(name.begin() + index);

            }

            return ret;
        }

        void ArrayReverse(vector<uint8_t> InArr, vector<uint8_t>& OutArr)
        {
            uint32_t InSize = InArr.size(), InSizeLoop = InSize - 1, i = 0;

            if(OutArr.size() != InSize)
                OutArr.resize(InSize);

            for(; i < InSize; i++, InSizeLoop--)
                OutArr[i] = InArr[InSizeLoop];
        }
    }

    namespace PageParsing
    {
        int GetPageLenAtPage(int pgCount, int totalLen, int pg, int maxPageSize)
        {
            return (pg == pgCount - 0x1) ? (totalLen % maxPageSize) : maxPageSize;
        }
    }

    namespace OpcodeParsing
    {
        uint32_t GetOpCodeLengthDefault(Constants::OpCode opCode)
        {
            //Lengths include the opCode byte
            switch (opCode)
            {
                case OP_Nop:
                case OP_Add:
                case OP_Sub:
                case OP_Mult:
                case OP_Div:
                case OP_Mod:
                case OP_Not:
                case OP_Neg:
                case OP_CmpEQ:
                case OP_CmpNE:
                case OP_CmpGT:
                case OP_CmpGE:
                case OP_CmpLT:
                case OP_CmpLE:
                case OP_fAdd:
                case OP_fSub:
                case OP_fMult:
                case OP_fDiv:
                case OP_fMod:
                case OP_fNeg:
                case OP_fCmpEQ:
                case OP_fCmpNE:
                case OP_fCmpGT:
                case OP_fCmpGE:
                case OP_fCmpLT:
                case OP_fCmpLE:
                case OP_vAdd:
                case OP_vSub:
                case OP_vMult:
                case OP_vDiv:
                case OP_vNeg:
                case OP_And:
                case OP_Or:
                case OP_Xor:
                case OP_ItoF:
                case OP_FtoI:
                case OP_FtoV:
                case OP_Dup:
                case OP_Drop:
                case OP_pGet:
                case OP_pSet:
                case OP_pPeekSet:
                case OP_ToStack:
                case OP_FromStack:
                case OP_PushStringNull:
                case OP_MemCopy:
                case OP_Catch:
                case OP_Throw:
                case OP_pCall:
                case OP_Push_Neg1:
                case OP_Push_0:
                case OP_Push_1:
                case OP_Push_2:
                case OP_Push_3:
                case OP_Push_4:
                case OP_Push_5:
                case OP_Push_6:
                case OP_Push_7:
                case OP_PushF_Neg1:
                case OP_PushF_0:
                case OP_PushF_1:
                case OP_PushF_2:
                case OP_PushF_3:
                case OP_PushF_4:
                case OP_PushF_5:
                case OP_PushF_6:
                case OP_PushF_7:
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

                    return 1;
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
                case OP_PushString:
                    return 2;
                case OP_Switch:
                    return 2;

                case OP_PushB2:
                case OP_Return:
                case OP_PushS:
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
                case OP_Jump:
                case OP_JumpFalse:
                case OP_JumpEQ:
                case OP_JumpNE:
                case OP_JumpGE:
                case OP_JumpGT:
                case OP_JumpLE:
                case OP_JumpLT:
                case OP_CallNative:
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
                    return 3;
                case OP_PushB3:
                case OP_GetGlobalP3:
                case OP_GetGlobal3:
                case OP_SetGlobal3:
                case OP_PushI24:
                    return 4;

                case OP_Push:
                case OP_PushF:
                case OP_PushArrayP:
                    return 5;
                case OP_Function:
                    return 5;
                default:
                    cout << "Unknown OpCode: " << (int32_t)opCode << "\r\n";
                    Throw( "Unknown OpCode" );
            }
        }
        uint32_t GetOpCodeLength(Constants::OpCode opCode, vector<uint8_t> &code, uint32_t PC)
        {
            //Lengths include the opCode byte
            uint32_t len = GetOpCodeLengthDefault(opCode);
            switch (opCode)
            {
                case OP_Switch:
                    return len + (code[PC + 1] * 6);
                case OP_Function:
                    return len + code[PC + 4];
                case OP_PushString:
                    return len + code[PC + 1];
                case OP_PushArrayP:
                    return len + *(uint32_t*)(code.data() + 1);
                default:
                    return len;
            }

        return len;
        }
    }

    namespace NativeParsing
    {

        int32_t GetArgCountFromIndex(uint16_t* Indblock)
        {
            return (((uint8_t*)Indblock)[0] & 0x3e) >> 1;
        }
        int32_t GetIndex(uint16_t val)
        {
            return (((val & 0xFF) << 2) & 0x300) | ((val >> 8) & 0xFF);
        }
        bool FunctionHasReturn(uint16_t* data)
        {
            return (((uint8_t*)data)[0] & 1) == 1 ? true : false;
        }
        uint16_t SetNewIndex(uint16_t index, int parameterCount, bool ret)
        {
            return SwapEndian((uint16_t)(((index & 0xFF00) >> 2) | ((index & 0xFF) << 8) | (ret ? 1 : 0) | (parameterCount << 1)));
        }



    }

    namespace Hashing
    {
        uint32_t Joaat(char* key)
        {
            unsigned int hash, i;
            for (hash = i = 0;; i++)
            {
                if(key[i] == '\0')
                    break;
                hash += tolower(key[i]);
                hash += (hash << 10);
                hash ^= (hash >> 6);
            }
            hash += (hash << 3);
            hash ^= (hash >> 11);
            hash += (hash << 15);
            return hash;
        }
    }

    namespace Compression
    {

        void xCompress::xCompressInit()
        {
            if(!HasxCompressLoaded)
            {
                xCompressDLL = LoadLibrary("xcompress32.dll");

                if(xCompressDLL != NULL)
                {
                    LoadFunction<XMemCreateDecompressionContext_CALL>(&XMemCreateDecompressionContext, "XMemCreateDecompressionContext");
                    LoadFunction<XMemDestroyDecompressionContext_CALL>(&XMemDestroyDecompressionContext, "XMemDestroyDecompressionContext");
                    LoadFunction<XMemDecompress_CALL>(&XMemDecompress, "XMemDecompress");
                    LoadFunction<XMemDecompressStream_CALL>(&XMemDecompressStream, "XMemDecompressStream");
                    LoadFunction<XMemCreateCompressionContext_CALL>(&XMemCreateCompressionContext, "XMemCreateCompressionContext");
                    LoadFunction<XMemDestroyCompressionContext_CALL>(&XMemDestroyCompressionContext, "XMemDestroyCompressionContext");
                    LoadFunction<XMemResetCompressionContext_CALL>(&XMemResetCompressionContext, "XMemResetCompressionContext");
                    LoadFunction<XMemCompress_CALL>(&XMemCompress, "XMemCompress");
                    LoadFunction<XMemCompressStream_CALL>(&XMemCompressStream, "XMemCompressStream");
                    HasxCompressLoaded = true;
                }
                else
                    Throw("xCompress Not Found");


            }
        }

        int32_t xCompress::Decompress(uint8_t* compressedData,int32_t compressedLen, uint8_t* decompressedData, int32_t decompressedLen)
        {

            // Setup our decompression context
            int32_t DecompressionContext = 0;
            int32_t hr = XMemCreateDecompressionContext(XMEMCODEC_TYPE::XMEMCODEC_LZX, 0, 0, DecompressionContext);

            try
            {
                hr = XMemDecompress(DecompressionContext, decompressedData, decompressedLen, compressedData, compressedLen);
            }
            catch(exception ex)
            {
                XMemResetDecompressionContext(DecompressionContext);
                XMemDestroyDecompressionContext(DecompressionContext);
                return -1;
            }


            XMemResetDecompressionContext(DecompressionContext);
            XMemDestroyDecompressionContext(DecompressionContext);

            // Return our hr
            return hr;
        }

        int32_t xCompress::Compress(uint8_t* Data,int32_t DataLen, uint8_t* CompressedData, int32_t * OutCompressedLen)
        {

            // Setup our decompression context
            int32_t CompressionContext = 0;

            int32_t hr = XMemCreateCompressionContext(XMEMCODEC_TYPE::XMEMCODEC_LZX, 0, 0, CompressionContext);
            int32_t CompressedLen = DataLen;

            try
            {
                hr = XMemCompress(CompressionContext, CompressedData, CompressedLen, Data, DataLen);
            }
            catch(exception ex)
            {
                XMemResetCompressionContext(CompressionContext);
                XMemDestroyCompressionContext(CompressionContext);
                return -1;
            }

            XMemResetCompressionContext(CompressionContext);
            XMemDestroyCompressionContext(CompressionContext);

            *OutCompressedLen = CompressedLen;

            // Return our hr
            return hr;
        }

        void ZLIB_Decompress(uint8_t* in, uint32_t inSize, uint8_t* out, uint32_t outSize)
        {
            z_stream infstream;
            infstream.zalloc = Z_NULL;
            infstream.zfree = Z_NULL;
            infstream.opaque = Z_NULL;
            // setup "b" as the input and "c" as the compressed output
            infstream.avail_in = inSize; // size of input
            infstream.next_in = in; // input char array
            infstream.avail_out = outSize; // size of output
            infstream.next_out = out; // output char array

            int32_t res;

            res = inflateInit(&infstream);
            if(res != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
                cout << "Error: " << zError(res) << '\n';
                Throw("ZLIB InflateInit Failed");
            }
            res = inflate(&infstream, Z_NO_FLUSH);
            if(!(res == Z_STREAM_END || res == Z_OK))
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
                cout << "Error: " << zError(res) << '\n';
                Throw("ZLIB Inflate Failed");
            }
            res = inflateEnd(&infstream);
            if(res != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
                cout << "Error: " << zError(res) << '\n';
                Throw("ZLIB InflateEnd Failed");
            }


        }
        void ZLIB_Compress(uint8_t* in, uint32_t inSize, uint8_t* out, uint32_t& outSize)
        {
            z_stream defstream;
            defstream.zalloc = Z_NULL;
            defstream.zfree = Z_NULL;
            defstream.opaque = Z_NULL;
            // setup "a" as the input and "b" as the compressed output
            defstream.avail_in = inSize; // size of input
            defstream.next_in = in; // input char array
            defstream.avail_out = outSize; // size of output
            defstream.next_out = out; // output char array

            int32_t res;

            res = deflateInit(&defstream, Z_BEST_COMPRESSION);
            if(res != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
                cout << "Error: " << zError(res) << '\n';
                Throw("ZLIB DeflateInit Failed");
            }

            res = deflate(&defstream, Z_FINISH);
            if(!(res == Z_STREAM_END || res == Z_OK))
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
                cout << "Error: " << zError(res) << '\n';
                Throw("ZLIB deflate Failed ");
            }

            res = deflateEnd(&defstream);
            if(res != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
                cout << "Error: " << zError(res) << '\n';
                Throw("ZLIB deflateEnd Failed");
            }

            outSize = defstream.next_out - out;

        }
        string ZLIB_ErrorCodeToStr(int32_t errorcode)
        {
            switch(errorcode)
            {
                case Z_OK: return "Z_OK";
                case Z_STREAM_END: return "Z_STREAM_END";
                case Z_NEED_DICT: return "Z_NEED_DICT";
                case Z_ERRNO: return "Z_ERRNO";
                case Z_STREAM_ERROR: return "Z_STREAM_ERROR";
                case Z_DATA_ERROR: return "Z_DATA_ERROR";
                case Z_MEM_ERROR: return "Z_MEM_ERROR";
                case Z_BUF_ERROR: return "Z_BUF_ERROR";
                case Z_VERSION_ERROR: return "Z_VERSION_ERROR";
            }
            return "UNK_ERR";
        }




    }

    namespace Crypt
    {
        bool AES_Decrypt(uint8_t * data, size_t length)
        {
            if (length == 0)
                return false;

            uint32_t inputCount = length & -16;
            if (inputCount > 0)
            {

                aes256_context ctx;
                uint8_t key[32] = { 0xB7, 0x62, 0xDF, 0xB6, 0xE2, 0xB2, 0xC6, 0xDE, 0xAF, 0x72, 0x2A, 0x32, 0xD2, 0xFB, 0x6F, 0x0C, 0x98, 0xA3, 0x21, 0x74, 0x62, 0xC9, 0xC4, 0xED, 0xAD, 0xAA, 0x2E, 0xD0, 0xDD, 0xF9, 0x2F, 0x10 };
                aes256_init(&ctx, key);

                for(uint32_t i = 0; i < inputCount; i += 16)
                {
                    for (uint32_t b = 0; b < 16; b++)
                        aes256_decrypt_ecb(&ctx, data + i);
                }

                aes256_done(&ctx);
                return true;
            }
            return false;
        }
        bool AES_Encrypt(uint8_t * data, size_t length)
        {
            if (length == 0)
                return false;

            uint32_t inputCount = length & -16;
            if (inputCount > 0)
            {

                aes256_context ctx;
                uint8_t key[32] = { 0xB7, 0x62, 0xDF, 0xB6, 0xE2, 0xB2, 0xC6, 0xDE, 0xAF, 0x72, 0x2A, 0x32, 0xD2, 0xFB, 0x6F, 0x0C, 0x98, 0xA3, 0x21, 0x74, 0x62, 0xC9, 0xC4, 0xED, 0xAD, 0xAA, 0x2E, 0xD0, 0xDD, 0xF9, 0x2F, 0x10 };
                aes256_init(&ctx, key);

                for(uint32_t i = 0; i < inputCount; i += 16)
                {
                    for (uint32_t b = 0; b < 16; b++)
                        aes256_encrypt_ecb(&ctx, data + i);

                }

                aes256_done(&ctx);
                return true;
            }
            return false;
        }

    }

}
