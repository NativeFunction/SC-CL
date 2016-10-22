#pragma once

#define __global(index) __attribute((scriptglobal(index)))
#define __noinline __attribute((noinline))

//calculation range is -2,147,483,648 to 2,147,483,647
//any value above or below that will be automatically cast to a signed int
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef _Bool bool;

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


typedef struct vector2
{
	float X, Y;
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

typedef struct RGBA
{//Colour struct where values range from 0 - 255
	int Red, Green, Blue, Alpha;
} RGBA;

typedef struct RGB
{//Colour struct where values range from 0 - 255
	int Red, Green, Blue;
} RGB;

typedef struct FloatRGBA
{
	float Red, Green, Blue, Alpha;//Colour struct where values range from 0.0 - 1.0
} FloatRGBA;

typedef struct FloatRGB
{
	float Red, Green, Blue;//Colour struct where values range from 0.0 - 1.0
} FloatRGB;

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
#define RGBA(R,G,B,A) (RGBA){R,G,B,A}
#define FloatRGBA(R,G,B,A) (FloatRGBA){R,G,B,A}
#define Point(x, y) (Point){x, y}
#define Size(w, h) (Size){w, h}
#define vector2(x, y) (vector2){x, y}
#define vector3(x,y,z) (vector3){x,y,z}


typedef void* sizedarrayp;

#include "intrinsics.h"

#define CreateSizedArray(name, sizein)\
struct\
{\
	int size;\
	any items[sizein];\
} name = {.size = sizein};

#define ArrayToSizedArray(arr, sizedarr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	memcpy(sizedarr.items, arr, countof(arr));

#define SizedArrayToArray(sizedarr, arr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	memcpy(arr, sizedarr.items, countof(sizedarr.items));
	

