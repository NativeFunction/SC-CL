/*H**********************************************************************
* FILENAME :	common.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Common functions to be used with all targets and platforms of SC-CL.
*
* NOTES :
*		This file is part of SC-CL's include library.
*
* LICENSE :
*
*		Copyright 2016 SC-CL
*
*		Redistribution and use in source and binary forms, with or without
*		modification, are permitted provided that the following conditions are met:
*
*		* Redistributions of source code must retain the above copyright
*		notice, this list of conditions and the following disclaimer.
*
*		* Redistributions in binary form must reproduce the above copyright
*		notice, this list of conditions and the following disclaimer in the
*		documentation and/or other materials provided with the distribution.
*
*		* Neither SC-CL nor its contributors may be used to endorse or promote products
*		derived from this software without specific prior written permission.
*
*		* Redistribution of this software in source or binary forms shall be free
*		of all charges or fees to the recipient of this software.
*
*		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*		ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*		WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*		DISCLAIMED. IN NO EVENT SHALL SC-CL BE LIABLE FOR ANY
*		DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*		(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* AUTHORS :
*		Rocko Tompkins
*		Nathan James
*H*/
#pragma once
#include "types.h"

/// <summary>Swaps the endian of a int or short.</summary>
/// <param name="x">The value to be swapped.</param>
/// <returns></returns>
#define SwapEndian(x) _Generic((x),\
short int: SwapEndian16(x), unsigned short int: SwapEndian16(x),\
default: SwapEndian32(x))

/// <summary>Safely divides a and b to avoid division by zero.</summary>
/// <param name="a">The left side value.</param>
/// <param name="b">The right side value.</param>
/// <returns>The divided value.</returns>
#define SafeDiv(x, y) _Generic((x),\
float: DivFloat(x, y), double: DivFloat(x, y),\
default: DivInt(x, y))

/// <summary>Swaps the endian of a int to a constant value.</summary>
/// <param name="value">The value to be swapped.</param>
/// <returns></returns>
#define SwapEndian32Const(value)  ((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >>  8) | (((value) & 0x0000ff00) <<  8) | (((value) & 0x000000ff) << 24))

/// <summary>Converts degrees to radians.</summary>
/// <param name="degrees">The value to be converted.</param>
/// <returns>The value converted to radians.</returns>
#define DegreesToRadians(degrees) (degrees * (PI / 180.0f))

/// <summary>Converts radians to degrees.</summary>
/// <param name="radians">The value to be converted.</param>
/// <returns>The value converted to degrees.</returns>
#define RadiansToDegrees(radians) (radians * (180.0f / PI))

#if TARGET == TARGET_RDR
#define ftos(flt, precision) _float_to_string(flt, 3, precision)
#else
#define ftos(flt, precision) 
#endif

/// <summary>Prints the specified string to the subtitle buffer.</summary>
/// <param name="str">The string to be printed.</param>
/// <param name="ms">The milliseconds that the string should be printed for.</param>
/// <returns></returns>
void print(const char* str, int ms);

/// <summary>Concatinates two strings into one using a global char buffer.</summary>
/// <param name="str1">The first string to be added to the buffer.</param>
/// <param name="str2">The second string to be added to the buffer.</param>
/// <returns>The pointer to the global char buffer.</returns>
const char* strcatGlobal(const char* str1, const char* str2);

/// <summary>Copies str into the global char buffer then concatinates it with the string representation of i.</summary>
/// <param name="str">The string to be added to the buffer.</param>
/// <param name="i">The int to be converted and added to the buffer.</param>
/// <returns>The pointer to the global char buffer.</returns>
const char* straddiGlobal(const char* str, int i);

/// <summary>Copies the string representation of i into the global char buffer.</summary>
/// <param name="i">The int to be converted and copied to the buffer.</param>
/// <returns>The pointer to the global char buffer.</returns>
const char* itosGlobal(int i);

/// <summary>Prints the string as an exception for 10 seconds then exits the script.</summary>
/// <param name="str">The string to be printed.</param>
/// <returns></returns>
void Throw(const char* str);

/// <summary>Prints the string as an warning for 5 seconds.</summary>
/// <param name="str">The string to be printed.</param>
/// <returns></returns>
void Warn(const char* str);

/// <summary>Prints the string as an error for 5 seconds.</summary>
/// <param name="str">The string to be printed.</param>
/// <returns></returns>
void Error(const char* str);

/// <summary>Swaps the endian of a int.</summary>
/// <param name="value">The value to be swapped.</param>
/// <returns></returns>
int SwapEndian32(int value);

/// <summary>Swaps the endian of a short.</summary>
/// <param name="value">The value to be swapped.</param>
/// <returns></returns>
short SwapEndian16(short value);

/// <summary>Divides a and b then rounds up.</summary>
/// <param name="a">The left side value.</param>
/// <param name="b">The right side value.</param>
/// <returns>The ceiled value.</returns>
int CeilDivInt(uint a, uint b);

/// <summary>Safely divides a and b to avoid division by zero.</summary>
/// <param name="a">The left side value.</param>
/// <param name="b">The right side value.</param>
/// <returns>The divided value.</returns>
int DivInt(int a, int b);

/// <summary>Safely divides a and b to avoid division by zero.</summary>
/// <param name="a">The left side value.</param>
/// <param name="b">The right side value.</param>
/// <returns>The divided value.</returns>
float DivFloat(float a, float b);

/// <summary>Converts a string representing a float to a float.</summary>
/// <param name="str">The string to convert.</param>
/// <returns>The converted float value.</returns>
float StringToFloat(const char* str);

/// <summary>Converts a number to a hex string and stores it in a global char buffer.</summary>
/// <param name="val">The value to convert.</param>
/// <param name="isLowercase">If to convert the hex result to lower case.</param>
/// <returns>A pointer to the global char buffer.</returns>
const char* IntToHex(int val, bool isLowercase);

/// <summary>Converts a hex string to decimal.</summary>
/// <param name="hex">Hex string to convert.</param>
/// <returns>The decimal result.</returns>
int HexToInt(const char* hex);

/// <summary>Converts a base 10 integer to a specified base.</summary>
/// <param name="n">The base 10 integer.</param>
/// <param name="b">The base to convert to.</param>
/// <returns>The decimal representation of the new base.</returns>
int IntToBase(int n, int b);

/// <summary>Sets a bit at the bitIndex of a pointer to the specified value of bitValue.</summary>
/// <param name="valuePtr">The pointer to the value that will be changed.</param>
/// <param name="bitIndex">The bit index of the bit relative to the pointer.</param>
/// <param name="bitValue">The bit value to be set at the index.</param>
/// <returns></returns>
void SetBitAtIndex(int* valuePtr, uint bitIndex, bool bitValue);

/// <summary>Preforms a modulo operation an a negative number.</summary>
/// <param name="a">The left side value.</param>
/// <param name="b">The right side value.</param>
/// <returns>The modulo result.</returns>
int ModNegitive(int a, int b);

/// <summary>Converts a euler angle to a quaternion.</summary>
/// <param name="euler">The euler angle to be converted.</param>
/// <returns>The quaternion result.</returns>
quaternion EulerToQuaternion(vector3 euler);

/// <summary>Applys slow rotation to a look position eventualy converting it to endPos.</summary>
/// <param name="pos">The current look position.</param>
/// <param name="pos">The end look position.</param>
/// <returns>The updated look position.</returns>
vector3 RotationLookAtPoint(vector3 pos, vector3 endPos);

#if TARGET == TARGET_RDR
#ifdef _MSC_VER
/// <summary>Returns the principal value of the arc cosine of x, expressed in radians.</summary>
/// <param name="x">
///		Value whose arc cosine is computed, in the interval [-1,+1].
///		If the argument is out of this interval, a domain error occurs.
/// </param>
/// <returns>Principal arc cosine of x, in the interval [0,pi] radians.</returns>
#define acos(x) acosMSC(x)
float acosMSC(float number) {};
#else
float acos(float number);
#endif
#ifdef _MSC_VER
/// <summary>Returns the principal value of the arc sine of x, expressed in radians.</summary>
/// <param name="x">
///		Value whose arc sine is computed, in the interval [-1,+1].
///		If the argument is out of this interval, a domain error occurs.
/// </param>
/// <returns>Principal arc sine of x, in the interval [-pi/2,+pi/2] radians.</returns>
#define asin(number) asinMSC(number)
float asinMSC(float number) {};
#else
float asin(float number);
#endif
#endif

bool CmpLtU(int a, int b);
bool CmpGtU(int a, int b);
int Diff64P(int* x, int* y);
int* Sub64P(int* x, int yLeft, int yRight);
int* Add64P(int* x, int yLeft, int yRight);
int* Push64P(int LeftMost, int RightMost);