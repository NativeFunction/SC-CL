#pragma once

#ifndef _MSC_VER
#define global(index) __attribute((scriptglobal(index)))
#define noinline __attribute((noinline))
#define unsafe __attribute((unsafe))
#else
#define global(index) 
#define noinline 
#define unsafe 
#endif

#ifdef __YSC__
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

typedef union vector2
{
	struct { float x, y; };
	struct { float width, height; };
	struct { float w, h; };
	float v[2];
} Point, Size, vector2;

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

typedef union RGBA
{//Colour struct where values range from 0 - 255
	struct
	{
		union{int red; int r;};
		union{int green; int g;};
		union{int blue; int b;};
		union{int opacity; int alpha; int a;};
	};
	int col[4];
} RGBA;

typedef union RGB
{//Colour struct where values range from 0 - 255
	struct
	{
		union{int red; int r;};
		union{int green; int g;};
		union{int blue; int b;};
	};
	int col[3];
} RGB;

typedef union FloatRGBA
{//Colour struct where values range from 0.0 - 1.0
	struct
	{
		union{float red; float r;};
		union{float green; float g;};
		union{float blue; float b;};
		union{float opacity; float alpha; float a;};
	};
	float col[4];
} FloatRGBA;

typedef union FloatRGB
{//Colour struct where values range from 0.0 - 1.0
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


typedef void* sizedarrayp;

