#pragma once

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
int SetBit(int value, uint index);
int ClearBit(int value, uint index);
int ToggleBit(int value, uint index);
int SetBitInline(int value, uint index, bool bit);
int ModNegitive(int value1, int value2);
float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);
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
int* Sub64P(const int* x, int y);
int* Add64P(const int* x, int y);
int* Push64P(int x[2]);