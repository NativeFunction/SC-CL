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

	

}
