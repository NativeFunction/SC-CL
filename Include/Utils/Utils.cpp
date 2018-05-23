#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>
#include "Utils/Utils.h"
#include <windows.h>
#include "ConsoleColor.h"
#include <experimental\filesystem>

using namespace std;
using namespace Utils::System;
using namespace Utils::Bitwise;

namespace Utils {

	namespace IO
	{
		void LoadData(const char* path, vector<uint8_t>& out) {
			ifstream is(path, std::ios::in | std::ios::binary | std::ios::ate);

			if (is.is_open()) {
				is.seekg(0, is.end);
				size_t datasize = is.tellg();
				is.seekg(0, is.beg);

				out.resize(datasize, 0);
				is.read((char*)out.data(), datasize);
				is.close();
			}
			else
				Throw("Input File Could Not Be Opened");

		}
		bool CheckFopenFile(const char* path, FILE* file)
		{
			if (file == NULL)
			{
				System::Throw("Could Not Open File: " + string(path));
				return false;
			}
			return true;
		}
		bool CreateFileWithDir(const char* filePath, FILE*& file)
		{
			string dir = GetDir(filePath);
			bool exists = std::experimental::filesystem::exists(std::experimental::filesystem::v1::path(dir)) ?
			true : 
			std::experimental::filesystem::create_directories(std::experimental::filesystem::v1::path(dir));
			
			file = fopen(filePath, "wb");
            exists = file != NULL && exists;

			if(!exists)
				System::Throw("Could Not create File: " + string(filePath));

			return exists;
		}

	}

	namespace System
	{
		void Test(bool Condition, const std::string& str)
		{
			if (!Condition)
			{
				cout << brightred << "error: " << white << str << flush;
				assert(false);
				exit(EXIT_FAILURE);
			}
		}

		void Throw(const std::string& str)
		{
			cout << brightred << "error: " << white << str << "\r\nPress ENTER to exit..." << flush;
			cin.clear();
			cin.ignore(STREAMSIZE_MAX, '\n');
			exit(EXIT_FAILURE);
		}

		void Warn(const std::string& str)
		{
			cout << brightyellow << "Warning: " << white << str << endl;
		}
		void Pause(const std::string& str)
		{
			if (str != "")
				cout << str << "\n";
			cout << "Press ENTER to continue..." << flush;
			cin.clear();
			cin.ignore(STREAMSIZE_MAX, '\n');
		}
	}

	namespace DataConversion
	{

		vector<NamedUint32> ReorderUint32Vector(vector<uint32_t> vec, vector<const char*> name, bool isSmallToBig)
		{
			vector<NamedUint32> ret;
			ret.reserve(vec.size() + name.size());


			for (uint32_t i = 0; vec.size() != 0; i++)
			{
				uint32_t index = -(vec.begin() - (isSmallToBig ? min_element(vec.begin(), vec.end()) : max_element(vec.begin(), vec.end())));
				if (index > vec.size())
					Throw("ReorderUint32Vector Out Of Bounds");

				ret.push_back({ name[index],vec[index] });
				vec.erase(vec.begin() + index);
				name.erase(name.begin() + index);

			}

			return ret;
		}

		void ArrayReverse(vector<uint8_t> InArr, vector<uint8_t>& OutArr)
		{
			uint32_t InSize = InArr.size(), InSizeLoop = InSize - 1, i = 0;

			if (OutArr.size() != InSize)
				OutArr.resize(InSize);

			for (; i < InSize; i++, InSizeLoop--)
				OutArr[i] = InArr[InSizeLoop];
		}

}

	namespace Hashing
	{
		uint32_t Joaat(const char* key)
		{
			uint32_t hash, i;
			for (hash = i = 0; key[i]; ++i)
			{
				hash += tolower(key[i]);
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		}
		uint32_t Joaat(const string& key)
		{
			uint32_t hash, i;
			for (hash = i = 0; i < key.size(); ++i)
			{
				hash += tolower(key[i]);
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		}
		uint32_t JoaatCased(const char* key)
		{
			uint32_t hash, i;
			for (hash = i = 0; key[i]; ++i)
			{
				hash += key[i];
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		}
		uint32_t JoaatCased(const string& key)
		{
			uint32_t hash, i;
			for (hash = i = 0; i < key.size(); ++i)
			{
				hash += key[i];
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		}
	}

	namespace Bitwise
	{
		uint32_t Flip2BytesIn4(uint32_t value)
		{
			short* ptr = (short*)&value;
			short ret[2] = { ptr[1], ptr[0] };
			return *(uint32_t*)ret;
		}
		/**
		Copys bits from source num at start 0 into varToSet at index rangeStart until rangeEnd.
		Notes:-----------------------------------------------
		Total range can't be larger then 31 bits
		rangeStart can be from 0 - 31
		rangeEnd can be from 0 - 31
		rangeStart must be less then or equal to rangeEnd
		sign bit on sourceNum cannot be set
		*/
		int32_t __fastcall set_bits_in_range(uint32_t *varToSet, uint32_t rangeStart, uint32_t rangeEnd, int32_t sourceNum)
		{
			int32_t result = 0;
			if (sourceNum >= 0 && (int32_t)rangeStart <= (int32_t)rangeEnd && rangeStart <= 31 && rangeEnd <= 31)
			{
				result = (sourceNum << rangeStart) | *varToSet & (uint32_t)~(((1 << (rangeEnd - rangeStart + 1)) - 1) << rangeStart);
				*varToSet = result;
			}
			return result;
		}
		int32_t __fastcall get_bits_in_range(int32_t value, uint32_t rangeStart, uint32_t rangeEnd)
		{
			int32_t result;
			if ((int32_t)rangeStart > (int32_t)rangeEnd || rangeStart > 31 || rangeEnd > 31)
				result = 0;
			else
				result = (value >> rangeStart) & (uint32_t)((1 << (rangeEnd - rangeStart + 1)) - 1);
			return result;
		}
		uint32_t revbitmask(uint32_t index)
		{
			if (!(index % 32))
				return -1;
			return ~(-1 << index);
		}
		uint32_t bitCountToIntEnd(uint32_t rangeStart, uint32_t count)
		{
			assert(count && "count cannot be 0");
			assert(count < 32 && "count too large");
			uint32_t endIndex = rangeStart + count;
			if (count == 1)
				return rangeStart;
			else if (endIndex >= 32)
				return 31;
			else
				return endIndex - 1;
		}

	}

	namespace Compression
	{

		void xCompress::xCompressInit()
		{
			if (!HasxCompressLoaded)
			{
				xCompressDLL = LoadLibraryA("xcompress32.dll");

				if (xCompressDLL != NULL)
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

		int32_t xCompress::Decompress(uint8_t* compressedData, int32_t compressedLen, uint8_t* decompressedData, int32_t decompressedLen)
		{

			// Setup our decompression context
			int32_t DecompressionContext = 0;
			int32_t hr = XMemCreateDecompressionContext(XMEMCODEC_TYPE::XMEMCODEC_LZX, 0, 0, DecompressionContext);

			try
			{
				hr = XMemDecompress(DecompressionContext, decompressedData, decompressedLen, compressedData, compressedLen);
			}
			catch (exception ex)
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

		int32_t xCompress::Compress(uint8_t* Data, int32_t DataLen, uint8_t* CompressedData, int32_t * OutCompressedLen)
		{

			// Setup our decompression context
			int32_t CompressionContext = 0;

			int32_t hr = XMemCreateCompressionContext(XMEMCODEC_TYPE::XMEMCODEC_LZX, 0, 0, CompressionContext);
			int32_t CompressedLen = DataLen;

			try
			{
				hr = XMemCompress(CompressionContext, CompressedData, CompressedLen, Data, DataLen);
			}
			catch (exception ex)
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


        #define CHUNK 16384

		void ZLIB_Decompress(const std::vector<uint8_t>& in, std::vector<uint8_t> &out)
		{
            int ec;
            unsigned have;
            z_stream strm;
            unsigned char inbuf[CHUNK];
            unsigned char outbuf[CHUNK];
            uint32_t inIndex = 0;
            uint32_t inIndexOld = 0;

            out.clear();

            /* allocate inflate state */
            strm.zalloc = Z_NULL;
            strm.zfree = Z_NULL;
            strm.opaque = Z_NULL;
            strm.avail_in = 0;
            strm.next_in = Z_NULL;
            ec = inflateInit(&strm);
            if (ec != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                //cout << "Error: " << zError(ec) << '\n';
                Throw("ZLIB InflateInit Failed");
            }

            /* decompress until deflate stream ends or end of file */
            do
            {
                inIndexOld = inIndex;
                inIndex += CHUNK;
                if (inIndex > in.size())
                    inIndex = in.size();

                uint32_t size = inIndex - inIndexOld;
                if (size == 0)
                    break;
                memcpy(inbuf, in.data() + inIndexOld, size);

                strm.avail_in = size;
                strm.next_in = inbuf;

                /* run inflate() on input until output buffer not full */
                do
                {
                    strm.avail_out = CHUNK;
                    strm.next_out = outbuf;
                    ec = inflate(&strm, Z_NO_FLUSH);

                    /* state not clobbered */
                    if (ec == Z_STREAM_ERROR)
                    {
                        cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                        // cout << "Error: " << zError(ec) << '\n';
                        Throw("ZLIB deflate Failed ");
                    }

                    switch (ec)
                    {
                        case Z_NEED_DICT:
                            ec = Z_DATA_ERROR;     /* and fall through */
                        case Z_DATA_ERROR:
                        case Z_MEM_ERROR:
                            (void)inflateEnd(&strm);
                            cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                            // cout << "Error: " << zError(ec) << '\n';
                            Throw("ZLIB deflate Failed ");
                    }

                    have = CHUNK - strm.avail_out;
                    out.insert(out.end(), outbuf, outbuf + have);

                } while (strm.avail_out == 0);



                /* done when inflate() says it's done */
            } while (ec != Z_STREAM_END);

            /* clean up and return */
            ec = inflateEnd(&strm);
            if (ec != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                //cout << "Error: " << zError(ec) << '\n';
                Throw("ZLIB InflateEnd Failed");
            }
		}

        void ZLIB_Compress(const std::vector<uint8_t>& in, std::vector<uint8_t> &out)
        {
            int32_t ec, flush;
            uint32_t have;
            z_stream strm;
            uint8_t inbuf[CHUNK];
            uint8_t outbuf[CHUNK];
            uint32_t inIndex = 0;
            uint32_t inIndexOld = 0;

            out.clear();

            /* allocate deflate state */
            strm.zalloc = Z_NULL;
            strm.zfree = Z_NULL;
            strm.opaque = Z_NULL;
            ec = deflateInit(&strm, Z_BEST_COMPRESSION);
            if (ec != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                // cout << "Error: " << zError(ec) << '\n';
                Throw("ZLIB DeflateInit Failed");
            }

            /* compress until end of file */
            do
            {
                inIndexOld = inIndex;
                inIndex += CHUNK;
                if (inIndex > in.size())
                {
                    inIndex = in.size();
                    flush = Z_FINISH;
                }
                else
                    flush = Z_NO_FLUSH;

                uint32_t size = inIndex - inIndexOld;
                memcpy(inbuf, in.data() + inIndexOld, size);

                strm.avail_in = size;
                strm.next_in = inbuf;

                /* run deflate() on input until output buffer not full, finish
                compression if all of source has been read in */
                do
                {
                    strm.avail_out = CHUNK;
                    strm.next_out = outbuf;
                    ec = deflate(&strm, flush);    /* no bad return value */

                    /* state not clobbered */
                    if (ec == Z_STREAM_ERROR)
                    {
                        cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                        // cout << "Error: " << zError(ec) << '\n';
                        Throw("ZLIB deflate Failed ");
                    }

                    have = CHUNK - strm.avail_out;

                    out.insert(out.end(), outbuf, outbuf + have);

                } while (strm.avail_out == 0);
                assert(strm.avail_in == 0);     /* all input will be used */

                                                /* done when last data in file processed */
            } while (flush != Z_FINISH);
            
            /* stream will be complete */
            if (ec != Z_STREAM_END)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                // cout << "Error: " << zError(ec) << '\n';
                Throw("ZLIB deflate Failed ");
            }

            /* clean up and return */
            ec = deflateEnd(&strm);
            if (ec != Z_OK)
            {
                cout << "Error Code: " << ZLIB_ErrorCodeToStr(ec) << '\n';
                //cout << "Error: " << zError(ec) << '\n';
                Throw("ZLIB InflateEnd Failed");
            }
        }

		string ZLIB_ErrorCodeToStr(int32_t errorcode)
		{
			switch (errorcode)
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
			return "UNK_ERR" + to_string(errorcode);
		}

        #undef CHUNK

	}

	namespace Crypt
	{
		bool AES_Decrypt(uint8_t * data, size_t length, const uint8_t key[32])
		{
			if (length == 0)
				return false;

			uint32_t inputCount = length & -16;
			if (inputCount > 0)
			{

				aes256_context ctx;
				aes256_init(&ctx, const_cast<uint8_t*>(key));

				for (uint32_t i = 0; i < inputCount; i += 16)
				{
					for (uint32_t b = 0; b < 16; b++)
						aes256_decrypt_ecb(&ctx, data + i);
				}

				aes256_done(&ctx);
				return true;
			}
			return false;
		}
		bool AES_Encrypt(uint8_t * data, size_t length, const uint8_t key[32])
		{
			if (length == 0)
				return false;

			uint32_t inputCount = length & -16;
			if (inputCount > 0)
			{

				aes256_context ctx;
				aes256_init(&ctx, const_cast<uint8_t*>(key));

				for (uint32_t i = 0; i < inputCount; i += 16)
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
