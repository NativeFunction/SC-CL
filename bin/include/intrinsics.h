#pragma once
#include "types.h"
#include "constants.h"

#define __intrinsic __attribute((intrinsic(false)))
#define __unsafeIntrinsic __attribute((intrinsic(true)))

#define offsetof(st, m) ((uint)&(((st *)0)->m))
#define countof(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define stacksizeof(x) ((sizeof(x) + 3) >> 2)

#pragma region String //{
extern __intrinsic void memset(void* dest, byte value, size_t len);
extern __intrinsic void memcpy(void* dest, const void* src, size_t len);
extern __intrinsic void strcpy(char* dest, const char* src, const byte destBufferLen);
extern __intrinsic void stradd(char* dest, const char* src, const byte destBufferLen);
extern __intrinsic void straddi(char* dest, int value, const byte destBufferLen);
extern __intrinsic void itos(char* dest, int value, const byte destBufferLen);
extern __intrinsic int getHashKey(const char *string);

#pragma endregion //}

#pragma region Misc_Opcodes //{
extern __unsafeIntrinsic void pcall(void* funcAddr, ...);//params with types like floats must be implicitly set (1.0f)
extern __intrinsic void nop(const int count);
#pragma endregion //}

#pragma region Stack_Operations //{
extern __unsafeIntrinsic any stacktop();
extern __unsafeIntrinsic void pop();
extern __unsafeIntrinsic void popMult(const uint count);
extern __unsafeIntrinsic void pushFloat(float floatValue);
extern __unsafeIntrinsic void pushInt(int intValue);
extern __unsafeIntrinsic void pushVector3(vector3 vec3Value);
extern __unsafeIntrinsic void dupStackTop();
extern __unsafeIntrinsic void pushStruct(void* structure);
extern __unsafeIntrinsic void popStruct(void* structure);
extern __unsafeIntrinsic void rev(const int numItems);
extern __unsafeIntrinsic void exchange(const int structStackSize);
extern __unsafeIntrinsic int popInt();
extern __unsafeIntrinsic float popFloat();
extern __unsafeIntrinsic vector3 popVector3();
#pragma endregion //}

#pragma region Math/Conversions //{
extern __intrinsic float reinterpretIntToFloat(int intValue);
extern __intrinsic int reinterpretFloatToInt(float floatValue);
extern __intrinsic vector3 toVector3(float value);
extern __intrinsic vector3 makeVector3(float x, float y, float z);
extern __intrinsic vector3 vector3Add(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Sub(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Mult(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Div(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Neg(vector3 vector);
extern __intrinsic float fMod(float divend, float divisor);
extern __intrinsic bool bit_test(int value, const byte bitIndex);
extern __intrinsic void bit_set(int* address, const byte bitIndex);
extern __intrinsic void bit_reset(int* address, const byte bitIndex);
extern __intrinsic void bit_flip(int* address, const byte bitIndex);
#pragma endregion //}

#pragma region Unsafe_Math //{
// These perform the operation on the item(or vector) on top of the stack
// This can lead to dangerous behaviour if you arent sure what is currently on the stack
extern __unsafeIntrinsic int stackAdd(int value);
extern __unsafeIntrinsic int stackSub(int value);
extern __unsafeIntrinsic int stackMult(int value);
extern __unsafeIntrinsic int stackDiv(int value);
extern __unsafeIntrinsic int stackNeg();
extern __unsafeIntrinsic float stackFAdd(float value);
extern __unsafeIntrinsic float stackFSub(float value);
extern __unsafeIntrinsic float stackFMult(float value);
extern __unsafeIntrinsic float stackFDiv(float value);
extern __unsafeIntrinsic float stackFNeg();
extern __unsafeIntrinsic vector3 stackVAdd(vector3 value);
extern __unsafeIntrinsic vector3 stackVSub(vector3 value);
extern __unsafeIntrinsic vector3 stackVMult(vector3 value);
extern __unsafeIntrinsic vector3 stackVDiv(vector3 value);
extern __unsafeIntrinsic vector3 stackVNeg();
#pragma endregion //}

#pragma region Variables //{
extern __unsafeIntrinsic void setframe(const uint index);
extern __intrinsic int getframe(const uint index);
extern __intrinsic int getframep(const uint index);
extern __intrinsic void setglobal(const uint index, int value);
extern __intrinsic int getglobal(const uint index);
extern __intrinsic int getglobalp(const uint index);
#pragma endregion //}

#undef __asm_unsafe
#undef __intrinsic