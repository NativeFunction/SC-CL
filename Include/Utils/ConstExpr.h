#pragma once
#include <stdint.h>

typedef union 
{
	float fvalue;
	uint32_t uivalue;
	int32_t ivalue;
}IntAndFloat;

#pragma region Constexpr_Helpers
#pragma warning( disable : 4307 )//integral constant overflow
constexpr char ToLowerConst(const char c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; }
constexpr uint32_t sumSHL(uint32_t h, uint32_t shift) { return h + (h << shift); }
constexpr uint32_t sumSHR(uint32_t h, uint32_t shift) { return h + (h >> shift); }
constexpr uint32_t xorSHR(uint32_t h, uint32_t shift) { return h ^ (h >> shift); }
constexpr uint32_t hashFinishImpl(uint32_t h) { return sumSHL(xorSHR(sumSHL(h, 3), 11), 15); }
constexpr uint32_t hashStepImpl(uint32_t h, uint32_t c) { return xorSHR(sumSHL(h + c, 10), 6); }
constexpr uint32_t casedHashImpl(const char * cstr, uint32_t h) { return (*cstr != 0) ? casedHashImpl(cstr + 1, hashStepImpl(h, *cstr)) : hashFinishImpl(h); }
constexpr uint32_t hashImpl(const char * cstr, uint32_t h) { return (*cstr != 0) ? hashImpl(cstr + 1, hashStepImpl(h, ToLowerConst(*cstr))) : hashFinishImpl(h); }
constexpr uint32_t FloatToIntImpl(const IntAndFloat value) { return value.uivalue; }
#pragma endregion

#pragma region Global_Constexpr_Functions
constexpr uint32_t JoaatCasedConst(const char * cstr) { return casedHashImpl(cstr, 0); }
constexpr uint32_t JoaatConst(const char * cstr) { return hashImpl(cstr, 0); }
constexpr uint32_t FloatConst(const float value) { return FloatToIntImpl({value}); }


#pragma endregion
