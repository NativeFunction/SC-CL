#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "Constants.h"
#include <stdint.h>
#include <vector>
#include "windows.h"

using namespace std;


namespace Utils{

    struct DLX{
        void * data;
        size_t length;
    };


    namespace Hashing
    {
        unsigned int Joaat(char* key);
    }
    namespace DataConversion
    {
        inline uint32_t FloatToUInt(float x){return *(uint32_t*)&x;}
        inline int32_t FloatToInt(float x){return *(int32_t*)&x;}
        inline float UIntToFloat(uint32_t x){return *(float*)&x;}
        inline float IntToFloat(int32_t x){return *(float*)&x;}
        char* IntToHex(uint32_t val);
        inline int32_t IntToPointerInt(int32_t x){return 0x50000000 | x;}
        struct NamedUint32
        {
            const char* str;
            uint32_t val;
        };
        vector<NamedUint32> ReorderUint32Vector_SmallToBig(vector<uint32_t> vec, vector<const char*> name);
        void ArrayReverse(vector<uint8_t> InArr, vector<uint8_t>& OutArr);
    }
    namespace Bitwise
    {
        inline int16_t SwapEndian(int16_t x){return __builtin_bswap16((uint16_t)x);}
        inline int32_t SwapEndian(int32_t x){return __builtin_bswap32((uint32_t)x);}
        inline float SwapEndian(float x){return Utils::DataConversion::UIntToFloat(__builtin_bswap32(Utils::DataConversion::FloatToUInt(x)));}
        inline int64_t SwapEndian(int64_t x){return __builtin_bswap64((uint64_t)x);}
        inline uint16_t SwapEndian(uint16_t x){return __builtin_bswap16(x);}
        inline uint32_t SwapEndian(uint32_t x){return __builtin_bswap32(x);}
        inline uint64_t SwapEndian(uint64_t x){return __builtin_bswap64(x);}
    }
    namespace IO
    {
        DLX LoadData(const char* loc);
    }
    namespace System
    {
        void Pause(string str = "");
        void Throw(string str);
    }
    namespace Math
    {
        int64_t CeilDivInt(uint32_t a, uint32_t b);
    }
    namespace RSC85Parsing
    {
        uint32_t GetHeaderFormatFromFlag(uint32_t val);
        uint32_t GetFlagFromReadbuffer(uint32_t buffer);

        inline uint32_t GetFullFlagWithSize(uint32_t size, uint32_t flag)
        {
            return flag | (size >> 12 & 0xFF) | (size >> 12 & 0xFF00) | (size >> 12 & 0xFF0000);
        }
        inline uint32_t GetSizeFromFlag(uint32_t val)
        {
            return val << 12;
        }
    }
    namespace BlockParsing
    {
        int CountOffNextBlockSize(int size, int blockSize);
        int NextBlockSize(int size, int blockSize);
        vector<char> GiveDataBlock(vector<char> data, int blockSize);
        vector<char> GiveDataBlock(char* data, int blockSize);
        vector<char> GiveDataBlock(int size, int blockSize);
    }
    namespace PageParsing
    {
        int GetPageLenAtPage(int pgCount, int totalLen, int pg, int maxPageSize);
    }
    namespace OpcodeParsing
    {
        uint32_t GetOpCodeLengthDefault(Constants::OpCode opCode);
        uint32_t GetOpCodeLength(Constants::OpCode opCode, vector<uint8_t> &code, uint32_t PC);
    }
    namespace CallParsing
    {
        inline uint8_t GetNewCallOpCode(uint32_t needOffset)
        {
            if(needOffset >= 1048576)
                return 255;
            return 82 + (needOffset >> 16);
        }
        inline uint16_t GetNewCallOffset(uint32_t needOffset)
        {
            return needOffset - (((needOffset >> 16)) << 16);
        }
        inline int32_t GetCallOffset(int32_t readOffset, int32_t opCode)
        {
            return readOffset | ((opCode - 82) << 16);
        }

    }
    namespace NativeParsing
    {
        int32_t GetArgCountFromIndex(uint16_t* Indblock);
        int32_t GetIndex(uint16_t val);
        bool FunctionHasReturn(uint16_t* data);
        uint16_t SetNewIndex(uint16_t index, int parameterCount, bool ret);
    }
    namespace Compression
    {
        class xCompress
        {
        public:

            enum XMEMCODEC_TYPE
            {
                XMEMCODEC_DEFAULT = 0,
                XMEMCODEC_LZX = 1
            };
            struct XMEMCODEC_PARAMETERS_LZX
            {
                int Flags;
                int WindowSize;
                int CompressionPartitionSize;
            };

            const int32_t XMEMCOMPRESS_STREAM = 0x00000001;
            bool HasxCompressLoaded = false;
            HINSTANCE xCompressDLL;

    //{ Callback Pointer Allocation

            ///public static extern int XMemCreateDecompressionContext(XMEMCODEC_TYPE CodecType,int pCodecParams,int Flags, ref int pContext);
            typedef int32_t (CALLBACK* XMemCreateDecompressionContext_CALL)(XMEMCODEC_TYPE CodecType, int32_t pCodecParams, int32_t Flags, int32_t &pContext);
            XMemCreateDecompressionContext_CALL XMemCreateDecompressionContext;

            ///public static extern void XMemDestroyDecompressionContext(int Context);
            typedef void (CALLBACK* XMemDestroyDecompressionContext_CALL)(int32_t Context);
            XMemDestroyDecompressionContext_CALL XMemDestroyDecompressionContext;

            ///public static extern int XMemResetDecompressionContext(int Context);
            typedef int32_t (CALLBACK* XMemResetDecompressionContext_CALL)(int32_t Context);
            XMemResetDecompressionContext_CALL XMemResetDecompressionContext;

            ///public static extern int XMemDecompress(int Context, byte[] pDestination, ref int pDestSize, byte[] pSource, int pSrcSize);
            typedef int32_t (CALLBACK* XMemDecompress_CALL)(int32_t Context, uint8_t* pDestination, int32_t &pDestSize, uint8_t* pSource, int32_t pSrcSize);
            XMemDecompress_CALL XMemDecompress;

            ///public static extern int XMemDecompressStream(int Context, byte[] pDestination, ref int pDestSize, byte[] pSource, ref int pSrcSize);
            typedef int32_t (CALLBACK* XMemDecompressStream_CALL)(int32_t Context, uint8_t* pDestination, int32_t &pDestSize, uint8_t* pSource, int32_t &pSrcSize);
            XMemDecompressStream_CALL XMemDecompressStream;

            ///public static extern int XMemCreateCompressionContext(XMEMCODEC_TYPE CodecType, int pCodecParams, int Flags, ref int pContext);
            typedef int32_t (CALLBACK* XMemCreateCompressionContext_CALL)(XMEMCODEC_TYPE CodecType, int32_t pCodecParams, int32_t Flags, int32_t &pContext);
            XMemCreateCompressionContext_CALL XMemCreateCompressionContext;

            ///public static extern void XMemDestroyCompressionContext(int Context);
            typedef void (CALLBACK*XMemDestroyCompressionContext_CALL)(int32_t Context);
            XMemDestroyCompressionContext_CALL XMemDestroyCompressionContext;

            ///public static extern int XMemResetCompressionContext(int Context);
            typedef int32_t (CALLBACK* XMemResetCompressionContext_CALL)(int32_t Context);
            XMemResetCompressionContext_CALL XMemResetCompressionContext;

            ///public static extern int XMemCompress(int Context, byte[] pDestination, ref int pDestSize, byte[] pSource, int pSrcSize);
            typedef int32_t (CALLBACK* XMemCompress_CALL)(int32_t Context, uint8_t* pDestination, int32_t &pDestSize, uint8_t* pSource, int32_t pSrcSize);
            XMemCompress_CALL XMemCompress;

            ///public static extern int XMemCompressStream(int Context, byte[] pDestination, ref int pDestSize, byte[] pSource, ref int pSrcSize);
            typedef int32_t (CALLBACK* XMemCompressStream_CALL)(int32_t Context, uint8_t* pDestination, int &pDestSize, uint8_t* pSource, int32_t &pSrcSize);
            XMemCompressStream_CALL XMemCompressStream;

    //}
    //{ Template Functions
            template<typename T>
            void LoadFunction(T* ptr, string str)
            {
                *ptr = (T)GetProcAddress(xCompressDLL, str.c_str());
                if (!*ptr)
                {
                    // handle the error
                    FreeLibrary(xCompressDLL);
                    cout << "Function: " << str;
                    Utils::System::Throw("xCompress Function Not Found");
                }
            }
    //}

            void xCompressInit();
            int32_t Decompress(uint8_t* compressedData,int32_t compressedLen, uint8_t* decompressedData, int32_t decompressedLen);
            int32_t Compress(uint8_t* Data,int32_t DataLen, uint8_t* CompressedData, int32_t * OutCompressedLen);

        };

        void ZLIB_Decompress(uint8_t* in, uint32_t inSize, uint8_t* out, uint32_t outSize);
        void ZLIB_Compress(uint8_t* in, uint32_t inSize, uint8_t* out, uint32_t& outSize);
        string ZLIB_ErrorCodeToStr(int32_t errorcode);
    }

    namespace Crypt
    {
         bool AES_Decrypt(uint8_t * data, size_t length);
         bool AES_Encrypt(uint8_t * data, size_t length);
    }

}

#endif // UTILS_H_INCLUDED