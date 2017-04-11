#pragma once
#include "types.h"

#define SwapEndian(x) _Generic((x),\
short int: SwapEndian16(x), unsigned short int: SwapEndian16(x),\
default: SwapEndian32(x))

#define SwapEndian32Const(value)  ((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >>  8) | (((value) & 0x0000ff00) <<  8) | (((value) & 0x000000ff) << 24))
#define DegreesToRadians(degrees) (degrees * (PI / 180.0f))
#define RadiansToDegrees(radians) (radians * (180.0f / PI))


void print(const char* str, int ms);
const char* strcatGlobal(const char* str1, const char* str2);
const char* straddiGlobal(const char* str1, int i);
const char* itosGlobal(int i);
void Throw(const char* str);
void Warn(const char* str);
int SwapEndian32(int value);
short SwapEndian16(short value);
int CeilDivInt(uint a, uint b);
int DivInt(int a, int b);
float DivFloat(float a, float b);
const char* IntToHex(int val);
int HexToInt(const char* hex);
void SetBitAtIndex(int* value, uint index, bool bit);
int ModNegitive(int value1, int value2);
quaternion EulerToQuaternion(vector3 euler);
vector3 RotationLookAtPoint(vector3 pos, vector3 endpos);
#ifndef __GTAV__
#ifdef _MSC_VER
#define acos(number) acosMSC(number)
float acosMSC(float number);
#else
float acos(float number);
#endif
#ifdef _MSC_VER
#define asin(number) asinMSC(number)
float asinMSC(float number);
#else
float asin(float number);
#endif
#endif
float StringToFloat(const char* str);
bool CmpLtU(int a, int b);
bool CmpGtU(int a, int b);
int Diff64P(int* x, int* y);
int* Sub64P(int* x, int yLeft, int yRight);
int* Add64P(int* x, int yLeft, int yRight);
int* Push64P(int LeftMost, int RightMost);