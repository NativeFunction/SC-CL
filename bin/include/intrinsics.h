#pragma once
#include "types.h"
#include "constants.h"

#define __intrinsic __attribute((intrinsic(false)))

#define __intrinsic_advanced_user true
#if __intrinsic_advanced_user == false
#define __asm_unsafe __attribute__((deprecated("This asm function is extremely unsafe. It should only be used if you know what you are doing.")))
#else
#define __asm_unsafe 
#endif
#undef __intrinsic_advanced_user

#define offsetof(st, m) ((uint)&(((st *)0)->m))
#define countof(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define stacksizeof(x) ((sizeof(x) + 3) >> 2)
#define BITTEST(integer, index) ((integer & (1 << index)) != 0)
#define BITSET(integer, index) (integer | (1 << index))
#define BITCLEAR(integer, index) (integer & ~(1 << index))

#pragma region String //{
extern __intrinsic void memset(void* dest, byte value, size_t len);
extern __intrinsic void memcpy(void* dest, void* src, size_t len);
extern __intrinsic void strcpy(char* dest, char* src, const byte destBufferLen);
extern __intrinsic void stradd(char* dest, char* src, const byte destBufferLen);
extern __intrinsic void straddi(char* dest, int value, const byte destBufferLen);
extern __intrinsic void itos(char* dest, int value, const byte destBufferLen);
extern __intrinsic int getHashKey(char *string);
#pragma endregion //}

#pragma region Misc_Opcodes //{
extern __intrinsic __asm_unsafe void pcall(void* funcAddr, ...);//params with types like floats must be implicitly set (1.0f)
#pragma endregion //}

#pragma region Stack_Operations //{
extern __intrinsic __asm_unsafe any stacktop();
extern __intrinsic __asm_unsafe void pop();
extern __intrinsic __asm_unsafe void popMult(const uint count);
extern __intrinsic __asm_unsafe void pushFloat(float floatValue);
extern __intrinsic __asm_unsafe void pushInt(int intValue);
extern __intrinsic __asm_unsafe void pushVector3(vector3 vec3Value);
extern __intrinsic __asm_unsafe void dupStackTop();
extern __intrinsic __asm_unsafe void pushStruct(void* structure);
extern __intrinsic __asm_unsafe void popStruct(void* structure);
extern __intrinsic __asm_unsafe void rev(const int numItems);
extern __intrinsic __asm_unsafe void exchange(const int structStackSize);
extern __intrinsic __asm_unsafe int popInt();
extern __intrinsic __asm_unsafe float popFloat();
extern __intrinsic __asm_unsafe vector3 popVector3();
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
#pragma endregion //}

#pragma region Unsafe_Math //{
// These perform the operation on the item(or vector) on top of the stack
// This can lead to dangerous behaviour if you arent sure what is currently on the stack
extern __intrinsic __asm_unsafe int stackAdd(int value);
extern __intrinsic __asm_unsafe int stackSub(int value);
extern __intrinsic __asm_unsafe int stackMult(int value);
extern __intrinsic __asm_unsafe int stackDiv(int value);
extern __intrinsic __asm_unsafe int stackNeg();
extern __intrinsic __asm_unsafe float stackFAdd(float value);
extern __intrinsic __asm_unsafe float stackFSub(float value);
extern __intrinsic __asm_unsafe float stackFMult(float value);
extern __intrinsic __asm_unsafe float stackFDiv(float value);
extern __intrinsic __asm_unsafe float stackFNeg();
extern __intrinsic __asm_unsafe vector3 stackVAdd(vector3 value);
extern __intrinsic __asm_unsafe vector3 stackVSub(vector3 value);
extern __intrinsic __asm_unsafe vector3 stackVMult(vector3 value);
extern __intrinsic __asm_unsafe vector3 stackVDiv(vector3 value);
extern __intrinsic __asm_unsafe vector3 stackVNeg();
#pragma endregion //}

#pragma region Variables //{
extern __intrinsic __asm_unsafe void setframe(const uint index);
extern __intrinsic int getframe(const uint index);
extern __intrinsic int getframep(const uint index);
extern __intrinsic void setglobal(const uint index, int value);
extern __intrinsic int getglobal(const uint index);
extern __intrinsic int getglobalp(const uint index);
#pragma endregion //}

#undef __asm_unsafe
#undef __intrinsic