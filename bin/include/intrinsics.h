#pragma once
#include "types.h"
#include "constants.h"

//Fix for intellisense nonsense
#ifndef _MSC_VER
#define __intrinsic __attribute((intrinsic(false)))
#define __unsafeIntrinsic __attribute((intrinsic(true)))
#else
#define __intrinsic
#define __unsafeIntrinsic
#pragma warning( disable : 4391 )
#pragma warning( disable : 4392 )
#pragma warning( disable : 4244 )
#endif


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
extern __intrinsic int getHashKey(const char* str);

#pragma endregion //}

#pragma region Misc_Opcodes //{
extern __intrinsic const uint __varIndex(const char* varName);///Gets a var's index by name
#pragma endregion //}

#pragma region Math/Conversions //{
extern __intrinsic float reinterpretIntToFloat(int intValue);
extern __intrinsic int reinterpretFloatToInt(float floatValue);
extern __intrinsic vector3 toVector3(float value);
extern __intrinsic vector3 vector3Add(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Sub(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Mult(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Div(vector3 left, vector3 right);
extern __intrinsic vector3 vector3Neg(vector3 vector);
extern __intrinsic vector2 toVector2(float value);
extern __intrinsic vector2 vector2Add(vector2 left, vector2 right);
extern __intrinsic vector2 vector2Sub(vector2 left, vector2 right);
extern __intrinsic vector2 vector2Mult(vector2 left, vector2 right);
extern __intrinsic vector2 vector2Div(vector2 left, vector2 right);
extern __intrinsic vector2 vector2Neg(vector2 vector);
extern __intrinsic float fMod(float divend, float divisor);
extern __intrinsic bool bit_test(int value, const byte bitIndex);
extern __intrinsic void bit_set(int* address, const byte bitIndex);
extern __intrinsic void bit_reset(int* address, const byte bitIndex);
extern __intrinsic void bit_flip(int* address, const byte bitIndex);
#pragma endregion //}

//this will be deleted
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
extern __intrinsic void setGlobalAtIndex(const uint index, int value);
extern __intrinsic int getGlobalAtIndex(const uint index);
extern __intrinsic void* getGlobalPtrAtIndex(const uint index);
extern __intrinsic void* getPtrFromArrayIndex(const void* array, int index, const int arrayItemSize);
extern __intrinsic void* getPtrImmIndex(const void* pointer, const int immIndex);
#pragma endregion //}

#pragma region Custom_ASM //{
extern __unsafeIntrinsic void __popMult(const uint count);///Pops multiple items off the stack
extern __unsafeIntrinsic void __pushV(vector3 value);///Pushes a vector3 on the stack
extern __unsafeIntrinsic void __pushStruct(void* structure);///Pushes a struct on the stack
extern __unsafeIntrinsic void __popStruct(void* structure);///Pops a struct off the stack
extern __unsafeIntrinsic void __rev(const int numItems);///Reverses items on stack
extern __unsafeIntrinsic void __exch(const int structStackSize);///Exchanges a struct on the stack
extern __unsafeIntrinsic int __popI();///Gets top int on stack 
extern __unsafeIntrinsic float __popF();///Gets top float on stack 
extern __unsafeIntrinsic vector3 __popV();///Gets top vector3 on stack 
#pragma endregion //}

#pragma region ASM //{
extern __intrinsic       void __nop(const uint count);
extern __unsafeIntrinsic void __add();
extern __unsafeIntrinsic void __sub();
extern __unsafeIntrinsic void __mult();
extern __unsafeIntrinsic void __div();
extern __unsafeIntrinsic void __mod();
extern __unsafeIntrinsic void __not();
extern __unsafeIntrinsic void __neg();
extern __unsafeIntrinsic void __cmpEq();
extern __unsafeIntrinsic void __cmpNe();
extern __unsafeIntrinsic void __cmpGt();
extern __unsafeIntrinsic void __cmpGe();
extern __unsafeIntrinsic void __cmpLt();
extern __unsafeIntrinsic void __cmpLe();
extern __unsafeIntrinsic void __addF();
extern __unsafeIntrinsic void __subF();
extern __unsafeIntrinsic void __multF();
extern __unsafeIntrinsic void __divF();
extern __unsafeIntrinsic void __modF();
extern __unsafeIntrinsic void __negF();
extern __unsafeIntrinsic void __cmpEqF();
extern __unsafeIntrinsic void __cmpNeF();
extern __unsafeIntrinsic void __cmpGtF();
extern __unsafeIntrinsic void __cmpGeF();
extern __unsafeIntrinsic void __cmpLtF();
extern __unsafeIntrinsic void __cmpLeF();
extern __unsafeIntrinsic void __addV();
extern __unsafeIntrinsic void __subV();
extern __unsafeIntrinsic void __multV();
extern __unsafeIntrinsic void __divV();
extern __unsafeIntrinsic void __negV();
extern __unsafeIntrinsic void __and();
extern __unsafeIntrinsic void __or();
extern __unsafeIntrinsic void __xor();
extern __unsafeIntrinsic void __iToF();
extern __unsafeIntrinsic void __fToI();
extern __unsafeIntrinsic void __fToV();
extern __unsafeIntrinsic void __push2(const uint value0, const uint value1);
extern __unsafeIntrinsic void __push3(const uint value0, const uint value1, const uint value2);
extern __unsafeIntrinsic void __push(const int value);
extern __unsafeIntrinsic void __pushF(const float value);
extern __unsafeIntrinsic void __dup();
extern __unsafeIntrinsic void __drop();
extern __unsafeIntrinsic void __callNative(const uint nativeHash, const uint paramCount, const uint returnCount);
extern __unsafeIntrinsic void __callNativePc(const uint nativeHash64Part1, const uint nativeHash64Part2, const uint paramCount, const uint returnCount);
extern __unsafeIntrinsic void __return(const uint paramCount, const uint returnCount);
extern __unsafeIntrinsic void __pGet();
extern __unsafeIntrinsic void __pSet();
extern __unsafeIntrinsic void __pPeekSet();
extern __unsafeIntrinsic void __toStack();
extern __unsafeIntrinsic void __fromStack();
extern __unsafeIntrinsic void __getArrayP(const uint arraySize);
extern __unsafeIntrinsic void __getArray(const uint arraySize);
extern __unsafeIntrinsic void __setArray(const uint arraySize);
extern __unsafeIntrinsic void __getFrameP(const uint frameIndex);
extern __unsafeIntrinsic void __getNamedFrameP(const char* frameName);
extern __unsafeIntrinsic void __getFrame(const uint frameIndex);
extern __unsafeIntrinsic void __getNamedFrame(const char* frameName);
extern __unsafeIntrinsic void __setFrame(const uint frameIndex);
extern __unsafeIntrinsic void __setNamedFrame(const char* frameName);
extern __unsafeIntrinsic void __getStaticP(const uint staticIndex);
extern __unsafeIntrinsic void __getNamedStaticP(const char* StaticName);
extern __unsafeIntrinsic void __getStatic(const uint staticIndex);
extern __unsafeIntrinsic void __getNamedStatic(const char* StaticName);
extern __unsafeIntrinsic void __setStatic(const uint staticIndex);
extern __unsafeIntrinsic void __setNamedStatic(const char* StaticName);
extern __unsafeIntrinsic void __addImm(const uint value);
extern __unsafeIntrinsic void __multImm(const uint value);
extern __unsafeIntrinsic void __getImmP(const uint immediate);
extern __unsafeIntrinsic void __getImm(const uint immediate);
extern __unsafeIntrinsic void __setImm(const uint immediate);
extern __unsafeIntrinsic void __getGlobalP(const uint globalIndex);
extern __unsafeIntrinsic void __getGlobal(const uint globalIndex);
extern __unsafeIntrinsic void __setGlobal(const uint globalIndex);
extern __unsafeIntrinsic void __switch(const int Case, const char* label, ...);
extern __unsafeIntrinsic void __jump(const char* label);
extern __unsafeIntrinsic void __jumpFalse(const char* label);
extern __unsafeIntrinsic void __jumpNE(const char* label);
extern __unsafeIntrinsic void __jumpEQ(const char* label);
extern __unsafeIntrinsic void __jumpLE(const char* label);
extern __unsafeIntrinsic void __jumpLT(const char* label);
extern __unsafeIntrinsic void __jumpGE(const char* label);
extern __unsafeIntrinsic void __jumpGT(const char* label);
extern __unsafeIntrinsic void __call(const char* functionName);
extern __unsafeIntrinsic void __pushString(const char* value);
extern __unsafeIntrinsic void __getHash();
extern __unsafeIntrinsic void __strCopy(const uint strLen);
extern __unsafeIntrinsic void __iToS(const uint strLen);
extern __unsafeIntrinsic void __strAdd(const uint strLen);
extern __unsafeIntrinsic void __strAddI(const uint strLen);
extern __unsafeIntrinsic void __memCopy();
extern __unsafeIntrinsic void __pCall();
#pragma endregion //}

#undef __asm_unsafe
#undef __intrinsic