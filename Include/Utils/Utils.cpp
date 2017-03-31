#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <fstream>
#include <algorithm>
#include "Utils/Utils.h"


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

		void ZLIB_Decompress(uint8_t* in, uint32_t inSize, uint8_t* out, uint32_t& outSize)
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

			outSize = infstream.next_out - out;


		}
		void ZLIB_Compress(uint8_t* in, uint32_t inSize, uint8_t* out, uint32_t& outSize)
		{
			z_stream defstream;
			defstream.zalloc = Z_NULL;
			defstream.zfree = Z_NULL;
			defstream.opaque = Z_NULL;
			defstream.data_type = Z_BINARY;
			// setup "a" as the input and "b" as the compressed output

			defstream.next_in = in; // input char array
			defstream.avail_in = inSize; // size of input
			defstream.next_out = out; // output char array
			defstream.avail_out = outSize; // size of output

			
			int32_t res = deflateInit(&defstream, Z_BEST_COMPRESSION);
			if (res != Z_OK)
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				//cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB DeflateInit Failed");
			}

			res = deflate(&defstream, Z_FINISH);
			if (!(res == Z_STREAM_END || res == Z_OK))
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				//cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB deflate Failed ");
			}
			

			res = deflateEnd(&defstream);
			if (res != Z_OK)
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				//cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB deflateEnd Failed");
			}

			outSize = defstream.next_out - out;
		}
		void ZLIB_CompressChecksum(uint8_t* in, uint32_t inSize, uint8_t* out, uint32_t& outSize)
		{
			z_stream defstream;
			defstream.zalloc = Z_NULL;
			defstream.zfree = Z_NULL;
			defstream.opaque = Z_NULL;
			defstream.data_type = Z_BINARY;
			// setup "a" as the input and "b" as the compressed output

			defstream.next_in = in; // input char array
			defstream.avail_in = inSize; // size of input
			defstream.next_out = out; // output char array
			defstream.avail_out = outSize; // size of output

			//deflateSetDictionary(&defstream, )

			int32_t res = deflateInit(&defstream, Z_BEST_COMPRESSION);
			if (res != Z_OK)
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				//cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB DeflateInit Failed");
			}

			res = deflate(&defstream, Z_FINISH);
			if (!(res == Z_STREAM_END || res == Z_OK))
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				//cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB deflate Failed ");
			}

			res = deflateEnd(&defstream);
			if (res != Z_OK)
			{
				cout << "Error Code: " << ZLIB_ErrorCodeToStr(res) << '\n';
				//cout << "Error: " << zError(res) << '\n';
				Throw("ZLIB deflateEnd Failed");
			}

			outSize = defstream.next_out - out;

			if (*(uint32_t*)(out + outSize - 4) != _byteswap_ulong(defstream.adler))
			{
				*(uint32_t*)(out + outSize) = _byteswap_ulong(defstream.adler);
				outSize += 4;
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
