#pragma once

#define __CreateSizedArray(name, size, type)\
struct\
{\
	int size;\
	type items[size];\
} name; name.size = size

#define __ArrayToSizedArray(arr, sizedarr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	__memcopy(sizedarr.items, arr, sizeof(arr));

#define __SizedArrayToArray(sizedarr, arr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	__memcopy(arr, sizedarr.items, sizeof(sizedarr.items));
	

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef int* sizedarray;
typedef _Bool bool;

typedef union vector3
{
	struct { float x, y, z; };
	float v[3];
} vector3, *vector3p;

typedef union quaternion
{
	struct { float x, y, z, w; };
	float v[4];
} quaternion, *quaternionp;

typedef union any
{
	bool Bool;
	int Int;
	float Float;
	char* CharP;
	int* IntP;
	float* FloatP;
	short* ShortP;
	vector3* Vector3P;
	quaternion* QuaternionP;
	
} any, *anyp;
