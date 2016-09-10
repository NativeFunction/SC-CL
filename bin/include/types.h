#pragma once

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
	int* IntP;
	float* FloatP;
	short* ShortP;
	vector3* Vector3P;
	quaternion* QuaternionP;
	
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
	

