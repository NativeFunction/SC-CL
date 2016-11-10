#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <fstream>
#include <algorithm>
#include "Utils.h"


using namespace std;
using namespace Utils::System;
using namespace Utils::Bitwise;



namespace Utils {

	namespace IO
	{
		DLX LoadData(const char* loc) {
			ifstream is(loc, std::ios::in | std::ios::binary | std::ios::ate);
			DLX File;

			if (is.is_open()) {
				is.seekg(0, is.end);
				size_t datasize = is.tellg();
				is.seekg(0, is.beg);

				File.data = new char[datasize];
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
			cout << brightred << "Exception: " << white << str << "\r\nPress ENTER to exit..." << flush;
			cin.clear();
			cin.ignore(STREAMSIZE_MAX, '\n');
			exit(EXIT_FAILURE);
		}
		void Warn(string str)
		{
			cout << brightyellow << "Warning: " << white << str << endl;
		}
		void Pause(string str)
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
		string IntToHex(uint32_t val)
		{
			const char hex_str[] = "0123456789ABCDEF";
			uint8_t* bin = (uint8_t*)&val;

			string str("\0", 9);

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


			for (uint32_t i = 0; vec.size() != 0; i++)
			{
				uint32_t index = -(vec.begin() - min_element(vec.begin(), vec.end()));
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
		uint32_t Joaat(string key)
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
		uint32_t JoaatCased(string key)
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
	}

	namespace Compression
	{

		void xCompress::xCompressInit()
		{
			if (!HasxCompressLoaded)
			{
				xCompressDLL = LoadLibrary("xcompress32.dll");

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
			if (res != Z_OK)
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB InflateInit Failed");
			}
			res = inflate(&infstream, Z_NO_FLUSH);
			if (!(res == Z_STREAM_END || res == Z_OK))
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB Inflate Failed");
			}
			res = inflateEnd(&infstream);
			if (res != Z_OK)
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
			if (res != Z_OK)
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB DeflateInit Failed");
			}

			res = deflate(&defstream, Z_FINISH);
			if (!(res == Z_STREAM_END || res == Z_OK))
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB deflate Failed ");
			}

			res = deflateEnd(&defstream);
			if (res != Z_OK)
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB deflateEnd Failed");
			}

			outSize = defstream.next_out - out;

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
