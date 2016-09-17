#pragma once

//calculation range is -2,147,483,648 to 2,147,483,647
//any value above or below that will be automatically cast to a signed int
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef _Bool bool;

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
	

