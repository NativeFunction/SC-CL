#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <stdint.h>
#include <vector>
#include "windows.h"


#ifdef _MSC_VER
#define __builtin_bswap16 _byteswap_ushort
#define __builtin_bswap32 _byteswap_ulong
#define __builtin_bswap64 _byteswap_uint64
#endif

#define STREAMSIZE_MAX 9223372036854775807

using namespace std;


namespace Utils {

	struct DLX {
		void * data;
		size_t length;
	};


	namespace Hashing
	{
		uint32_t Joaat(char* key);
		uint32_t JoaatCased(char* key);
	}
	namespace DataConversion
	{
		inline uint32_t FloatToUInt(float x) { return *(uint32_t*)&x; }
		inline int32_t FloatToInt(float x) { return *(int32_t*)&x; }
		inline float UIntToFloat(uint32_t x) { return *(float*)&x; }
		inline float IntToFloat(int32_t x) { return *(float*)&x; }
		char* IntToHex(uint32_t val);
		inline int32_t IntToPointerInt(int32_t x) { return 0x50000000 | x; }
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
		inline int16_t SwapEndian(int16_t x) { return __builtin_bswap16((uint16_t)x); }
		inline int32_t SwapEndian(int32_t x) { return __builtin_bswap32((uint32_t)x); }
		inline float SwapEndian(float x) { return Utils::DataConversion::UIntToFloat(__builtin_bswap32(Utils::DataConversion::FloatToUInt(x))); }
		inline int64_t SwapEndian(int64_t x) { return __builtin_bswap64((uint64_t)x); }
		inline uint16_t SwapEndian(uint16_t x) { return __builtin_bswap16(x); }
		inline uint32_t SwapEndian(uint32_t x) { return __builtin_bswap32(x); }
		inline uint64_t SwapEndian(uint64_t x) { return __builtin_bswap64(x); }
		uint32_t Flip2BytesIn4(uint32_t value);
	}
	namespace IO
	{
		DLX LoadData(const char* loc);
	}
	namespace System
	{
		void Pause(string str = "");
		void Throw(string str);
		void Throw(string str, int line, int col);
		void Throw(string str, clang::Rewriter writer, clang::SourceLocation location);
		void Throw(string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end);
		void Throw(string str, clang::Rewriter writer, clang::SourceRange range);
		void Warn(string str);
		void Warn(string str, clang::Rewriter writer, clang::SourceLocation location);
		void Warn(string str, clang::Rewriter writer, clang::SourceLocation start, clang::SourceLocation end);
		void Warn(string str, clang::Rewriter writer, clang::SourceRange range);
	}
	namespace Math
	{
		inline int64_t CeilDivInt(uint32_t a, uint32_t b) { return a == 0 || b == 0 ? 0 : 1 + ((a - 1) / b); }
		inline int32_t DivInt(uint32_t a, uint32_t b) { return a == 0 || b == 0 ? 0 : a / b; }
	}
	namespace ClangUtils
	{
		uint32_t GetLineFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		uint32_t GetColumnFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		string GetFileFromLocation(clang::Rewriter writer, clang::SourceLocation location);
		string GetLineStringFromLocation(clang::Rewriter writer, clang::SourceLocation location);
	}
}

#endif // UTILS_H_INCLUDED