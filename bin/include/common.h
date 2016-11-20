#pragma once
#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"

void print(char* str, int ms);
char* strcat(char* str1, char* str2);
char* straddiGlobal(char* str1, int i);
char* itosGlobal(int i);
void Throw(char* str);
void Warn(char* str);
int SwapEndian32(int value);
short SwapEndian16(short value);
int CeilDivInt(uint a, uint b);
int DivInt(int a, int b);
char* IntToHex(int val);
int HexToInt(char *hex);
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
float StringToFloat(char* str);

