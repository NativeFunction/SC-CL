/*H**********************************************************************
* FILENAME :	common.c					START DATE :	10 Sept 16
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
#include "types.h"
#include "constants.h"
#include "natives.h"
#include "intrinsics.h"

#define GlobalCharBufferD "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"

char* GlobalCharBuffer = GlobalCharBufferD;//256

void print(const char* str, int ms)
{
	#if TARGET == TARGET_GTAV
	BEGIN_TEXT_COMMAND_PRINT("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str);
	END_TEXT_COMMAND_PRINT(ms, 1);
	#elif TARGET == TARGET_RDR
	_CLEAR_PRINTS();
	_PRINT_SUBTITLE(str, ms != 0 ? (float)ms / 1000.0f : 0, true, 2, 1, 0, 0, 0);
	#elif TARGET == TARGET_GTAIV
	CLEAR_PRINTS();
	PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, ms, true);
	#endif
}

const char* IntToHex(int val, bool isLowercase)
{
	char* hex_str;
	if(isLowercase)
		hex_str = "0123456789ABCDEF";
	else
		hex_str = "0123456789abcdef";

	byte* bin = (byte*)&val;

	char* str = "         ";

	for (int i = 0; i < 4; i++)
	{
		str[i * 2] = hex_str[(bin[i] >> 4) & 0x0F];
		str[i * 2 + 1] = hex_str[(bin[i]) & 0x0F];
	}
	str[8] = 0;
	return str;
}

int HexToInt(const char *hex)
{
	uint result = 0;

	while (*hex)
	{
		if (*hex > 47 && *hex < 58)
			result += (*hex - 48);
		else if (*hex > 64 && *hex < 71)
			result += (*hex - 55);
		else if (*hex > 96 && *hex < 103)
			result += (*hex - 87);

		if (*++hex)
			result <<= 4;
	}

	return result;
}

int IntToBase(int n, int b)
{
	int rslt = 0, digitPos = 1;
	while (n)
	{
		rslt += (n%b)*digitPos;
		n /= b;
		digitPos *= 10;
	}
	return rslt;
}

const char* strcatGlobal(const char* str1, const char* str2)
{
	//this takes advantage of strings being global
	//this returns a static pointer so if you want to use the function again without losing the return you have to strcpy it


	strcpy((char*)GlobalCharBuffer, str1, 255);
	stradd((char*)GlobalCharBuffer, str2, 255);
	return (char*)GlobalCharBuffer;
}

const char* straddiGlobal(const char* str, int i)
{
	//this takes advantage of strings being global
	//this returns a static pointer so if you want to use the function again without losing the return you have to strcpy it

	strcpy((char*)GlobalCharBuffer, str, 255);
	straddi((char*)GlobalCharBuffer, i, 255);
	return (char*)GlobalCharBuffer;
}

const char* itosGlobal(int i)
{
	//this takes advantage of strings being global
	//this returns a static pointer so if you want to use the function again without losing the return you have to strcpy it

	itos((char*)GlobalCharBuffer, i, 64);
	return (char*)GlobalCharBuffer;
}

void Throw(const char* str)
{
	char Buffer[256];
	#if TARGET == TARGET_RDR
	strcpy(Buffer, "<red>Exception</red>: ", 255);
	#else
	strcpy(Buffer, "~r~Exception~s~: ", 255);
	#endif

	stradd(Buffer, str, 255);
	print(Buffer, 10000);
	WAIT(10000);

	#if TARGET == TARGET_GTAV
	TERMINATE_THIS_THREAD();
	#else
	TERMINATE_THIS_SCRIPT();
	#endif
}

void Warn(const char* str)
{
	char Buffer[256];
	#if TARGET == TARGET_RDR
	strcpy(Buffer, "<yellow>Warning</yellow>: ", 255);
	#else
	strcpy(Buffer, "~y~Warning~s~: ", 255);
	#endif

	stradd(Buffer, str, 255);
	print(Buffer, 5000);
}

void Error(const char* str)
{
	char Buffer[256];
	#if TARGET == TARGET_RDR
	strcpy(Buffer, "<red>Error</red>: ", 255);
	#else
	strcpy(Buffer, "~r~Error~s~: ", 255);
	#endif

	stradd(Buffer, str, 255);
	print(Buffer, 5000);
}

int SwapEndian32(int value)
{
	return ((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >> 8) | (((value) & 0x0000ff00) << 8) | (((value) & 0x000000ff) << 24));
}

short SwapEndian16(short value)
{
	return (((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >> 8);
}

int CeilDivInt(uint a, uint b)
{
	return a == 0 || b == 0 ? 0 : 1 + ((a - 1) / b);
}

int DivInt(int a, int b)
{
	return a == 0 || b == 0 ? 0 : a / b;
}

float DivFloat(float a, float b)
{
	return a == 0.0f || b == 0.0f ? 0.0f : a / b;
}

void SetBitAtIndex(int* valuePtr, uint bitIndex, bool bitValue)
{
	*valuePtr = *valuePtr ^ ((-bitValue ^ *valuePtr) & (1 << (bitIndex % 32)));
}


int ModNegitive(int a, int b)
{
	int ret = a % b;
	return ret < 0 ? ret + b : ret;
}

quaternion EulerToQuaternion(vector3 euler)
{
	float cosYawOver2 = COS(euler.x * 0.5),
		  sinYawOver2 = SIN(euler.x * 0.5),

		  cosPitchOver2 = COS(euler.y * 0.5),
		  sinPitchOver2 = SIN(euler.y * 0.5),
	      
		  cosRollOver2 = COS(euler.z * 0.5),
		  sinRollOver2 = SIN(euler.z * 0.5);

	quaternion out =
	{
		(cosYawOver2 * cosPitchOver2 * cosRollOver2) + (sinYawOver2 * sinPitchOver2 * sinRollOver2),
		(cosYawOver2 * cosPitchOver2 * sinRollOver2) - (sinYawOver2 * sinPitchOver2 * cosRollOver2),
		(cosYawOver2 * sinPitchOver2 * cosRollOver2) + (sinYawOver2 * cosPitchOver2 * sinRollOver2),
		(sinYawOver2 * cosPitchOver2 * cosRollOver2) - (cosYawOver2 * sinPitchOver2 * sinRollOver2)
	};
	return out;
}

vector3 RotationLookAtPoint(vector3 pos, vector3 endPos)
{
	vector3 out =
	{
		ATAN2(pos.y, pos.z),
		ATAN2(pos.x * COS(endPos.x), pos.z),
		ATAN2(COS(endPos.x), SIN(endPos.x) * SIN(pos.y))
	};
	return out;
}

#if TARGET == TARGET_RDR
#ifdef _MSC_VER
#define aCOS(number) acosMSC(number)
float acosMSC(float number)
#else
float aCOS(float number)
#endif
{
	//this works fine for floats as negitive ints and floats both have msb set
	if (reinterpretFloatToInt(number) < 0)
	{
		number = -number;
		return
			-(((((((
			-0.0187293f * number)
			+ 0.0742610f)
			* number)
			- 0.2121144f)
			* number)
			+ 1.5707288f)
			* SQRT(1.0 - number))
			+ PI;
	}

	return
		((((((
		-0.0187293f * number)
		+ 0.0742610f)
		* number)
		- 0.2121144f)
		* number)
		+ 1.5707288f)
		* SQRT(1.0 - number);

}
#ifdef _MSC_VER
#define aSIN(number) asinMSC(number)
float asinMSC(float number)
#else
float aSIN(float number)
#endif
{
	//this works fine for floats as negitive ints and floats both have msb set
	if (reinterpretFloatToInt(number) < 0)
	{
		number = -number;
		return
			(((((((
			-0.0187293f * number)
			+ 0.0742610f)
			* number)
			- 0.2121144f)
			* number)
			+ 1.5707288f)
			* SQRT(1.0 - number))
			- 1.57079632;
	}
	return
		-(((((((
		-0.0187293f * number)
		+ 0.0742610f)
		* number)
		- 0.2121144f)
		* number)
		+ 1.5707288f)
		* SQRT(1.0 - number))
		+ 1.57079632;
}
#endif

float StringToFloat(const char* str)
{
	float rez = 0, fact = 1;
	bool point_seen = false;
	str -= 3;
	int d = 0, read_char = *str & 0xFF;

	if (read_char == '-')
	{
		fact = -1;
		read_char = *++str & 0xFF;
	}

	while (read_char)
	{
		if (read_char == '.')
		{
			point_seen = true;
			read_char = *++str & 0xFF;
			continue;
		}

		d = read_char - '0';

		if (d >= 0 && d <= 9)
		{
			if (point_seen)
				fact /= 10;
			rez = rez * 10.0f + (float)d;
		}
		read_char = *++str & 0xFF;
	}
	return rez * fact;
}

//TODO: add these as intrinsics
bool CmpLtU(int a, int b)
{
	if (a >= 0 && b >= 0)
		return a < b;
	else
	{
		if (a == b)
			return false;

		int ltb = ~a & b;

		ltb |= ltb >> 1;
		ltb |= ltb >> 2;
		ltb |= ltb >> 4;
		ltb |= ltb >> 8;
		ltb |= ltb >> 16;
		return ((a & ~b) & ~ltb) == 0;
	}
}

bool CmpGtU(int a, int b)
{
	if (a >= 0 && b >= 0)
		return a > b;
	else
	{
		int ltb = ~a & b;

		ltb |= ltb >> 1;
		ltb |= ltb >> 2;
		ltb |= ltb >> 4;
		ltb |= ltb >> 8;
		ltb |= ltb >> 16;

		return ((a & ~b) & ~ltb) != 0;
	}
}

int Diff64P(int* x, int* y)
{
	int out[2];
	out[0] = (int)x - (int)y;
	#if PTRWIDTH == 64
	*(int*)((char*)out + 4) = *(int*)((char*)&x + 4) - *(int*)((char*)&y + 4);
	if (CmpGtU(out[0], (int)x))
		out[1]--;
	#endif
	return out[0];

}

int* Sub64P(int* x, int yLeft, int yRight)
{
	int out[2];
	out[0] = (int)x - yLeft;
	#if PTRWIDTH == 64
	*(int*)((char*)out + 4) = *(int*)((char*)&x + 4) - yRight;
	if (CmpGtU(out[0], (int)x))
		out[1]--;
	#endif
	return (int*)out[0];
}

int* Add64P(int* x, int yLeft, int yRight)
{
	int out[2];
	out[0] = (int)x + yLeft;
	#if PTRWIDTH == 64
	*(int*)((char*)out + 4) = *(int*)((char*)&x + 4) + yRight;
	//if (CmpLtU(out[0], (int)x))
		//out[1]++;
	#endif
	return (int*)out[0];
}

int* Push64P(int LeftMost, int RightMost)
{
	#if PTRWIDTH == 64
	int out[2];
	out[0] = LeftMost;
	*(int*)((char*)out + 4) = RightMost;
	return (int*)out[0];
	#else
	return (int*)LeftMost;
	#endif
}
