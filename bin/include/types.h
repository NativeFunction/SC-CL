/*H**********************************************************************
* FILENAME :	types.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Types to be used with all targets and platforms of SC-CL.
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

#ifndef _MSC_VER
#define global(index) __attribute((scriptglobal(index)))
#define noinline __attribute((noinline))
#define unsafe __attribute((unsafe))
#else
#define _Generic(x) 0
#define global(index)
#define noinline
#define unsafe
#endif

#if PLATFORM == PLATFORM_PC
#define int long long
#define float double
#endif

//calculation range is -2,147,483,648 to 2,147,483,647
//any value above or below that will be automatically cast to a signed int
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;

//Fix for intellisense nonsense
#ifndef _MSC_VER
typedef _Bool bool;
#else
typedef int bool;
#endif

typedef int Player;
typedef int Entity;
typedef Entity Ped;
typedef Entity Vehicle;
typedef Entity Object;
typedef uint Hash;
typedef int Cam;
typedef int FireId;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
typedef int DecisionMaker;
typedef int ScriptAny;
typedef int UnkInt;
typedef int Actor;
typedef int Controller;
typedef int Layout;
typedef int Iterator;
typedef int IterationSet;
typedef int GUIWindow;
typedef float Time;

typedef struct NetworkHandle
{
	int data[13];
} NetworkHandle;

typedef union vector2
{
	struct { float x, y; };
	struct { float width, height; };
	struct { float w, h; };
	float v[2];
} Point, Size, vector2;

//GTA Coord Type = Y Depth
//RDR Coord Type = Z Depth
typedef union vector3
{
	struct { float x, y, z; };
	float v[3];
} vector3;

typedef union quaternion
{
	struct { float x, y, z, w; };
	float v[4];
} quaternion;

//Colour struct where values range from 0 - 255
typedef union RGBA
{
	struct
	{
		union{int red; int r;};
		union{int green; int g;};
		union{int blue; int b;};
		union{int opacity; int alpha; int a;};
	};
	int col[4];
} RGBA;

//Colour struct where values range from 0 - 255
typedef union RGB
{
	struct
	{
		union{int red; int r;};
		union{int green; int g;};
		union{int blue; int b;};
	};
	int col[3];
} RGB;

//Colour struct where values range from 0.0 - 1.0
typedef union FloatRGBA
{
	struct
	{
		union{float red; float r;};
		union{float green; float g;};
		union{float blue; float b;};
		union{float opacity; float alpha; float a;};
	};
	float col[4];
} FloatRGBA;

//Colour struct where values range from 0.0 - 1.0
typedef union FloatRGB
{
	struct
	{
		union{float red; float r;};
		union{float green; float g;};
		union{float blue; float b;};
	};
	float col[3];
} FloatRGB;

typedef enum DataType
{
	DT_None,
	DT_UInt,
	DT_UIntP,
	DT_Int,
	DT_IntP,
	DT_Float,
	DT_FloatP,
	DT_Bool,
	DT_BoolP,
	DT_Char,
	DT_CharP,
	DT_Short,
	DT_ShortP,
	DT_UShort,
	DT_UShortP,
	DT_Vector3,
	DT_Vector3P,
	DT_Vector2,
	DT_Vector2P,
	DT_Quaternion,
	DT_QuaternionP,
	DT_FunctionP
} DataType;

typedef union flint
{
	int Int;
	float Float;
} flint;

typedef union any
{
	int Int;
	float Float;
	bool Bool;
	char* CharP;
	byte* ByteP;
	int* IntP;
	float* FloatP;
	short* ShortP;
	vector3* Vector3P;
	quaternion* QuaternionP;
	byte ByteArray[4];
	char CharArray[4];
	short ShortArray[2];
} any;

//poor mans constructors

#define Any(x) (any) {x}
#define RGBA(R,G,B,A) (RGBA){R,G,B,A}
#define FloatRGBA(R,G,B,A) (FloatRGBA){R,G,B,A}
#define Point(x, y) (Point){x, y}
#define Size(w, h) (Size){w, h}
#define Vector2(x, y) (vector2){x, y}
#define Vector3(x,y,z) (vector3){x,y,z}

typedef void* SizedArray;

