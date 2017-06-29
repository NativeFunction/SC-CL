/*H**********************************************************************
* FILENAME :	intrinsics.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Intrinsic functions to be used with all targets and platforms of SC-CL.
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
#include "types.h"
#include "constants.h"

//Fix for intellisense nonsense
#ifndef _MSC_VER
/// <summary>Defines a function as an intrinsic for use in the compiler.</summary>
#define __intrinsic __attribute((intrinsic(false)))

/// <summary>Defines a function as an unsafe intrinsic for use in the compiler.</summary>
#define __unsafeIntrinsic __attribute((intrinsic(true)))

#else

/// <summary>Computes the Jenkins one-at-a-time hash at compile time.</summary>
/// <param name="str">String to be hashed.</param>
/// <returns>The Jenkins one-at-a-time hash key of the string.</returns>
#define hashof(str) 0

/// <summary>Computes the Jenkins one-at-a-time hash at compile time.</summary>
/// <param name="str">String to be hashed.</param>
/// <returns>The Jenkins one-at-a-time hash key of the string.</returns>
#define joaat(str) 0

/// <summary>Defines a function as an intrinsic for use in the compiler.</summary>
#define __intrinsic

/// <summary>Defines a function as an unsafe intrinsic for use in the compiler.</summary>
#define __unsafeIntrinsic

#pragma warning( disable : 4391 )
#pragma warning( disable : 4392 )
#pragma warning( disable : 4244 )
#endif

/// <summary>This macro with functional form returns the offset value in bytes of member in the data structure or union type type.</summary>
/// <param name="type">A type in which member is a valid member designator.</param>
/// <param name="member">A member of type.</param>
/// <returns>A value of type unsigned int with the offset value of member in type.</returns>
#define offsetof(type, member) ((uint)&(((type *)0)->member))

/// <summary>Computes the number of elements in a statically-allocated array</summary>
/// <param name="x">The name of an array.</param>
/// <returns>The number of elements in the array, expressed as a unsigned int.</returns>
#define countof(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

/// <summary>Computes the stack size of a type.</summary>
/// <param name="x">The name of the type.</param>
/// <returns>The stack size of the type, expressed as a unsigned int.</returns>
#define stacksizeof(x) ((sizeof(x) + 3) >> 2)

#pragma region String //{
/// <summary>Sets the first num bytes of the block of memory pointed by ptr to the specified value.</summary>
/// <param name="ptr">Pointer to the block of memory to fill.</param>
/// <param name="value">Value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion of this value.</param>
/// <param name="len">Number of bytes to be set.</param>
/// <returns></returns>
extern __intrinsic void memset(void* ptr, byte value, unsigned int len);

/// <summary>Copies the values of len bytes from the location pointed to by source directly to the memory block pointed to by destination.</summary>
/// <param name="dest">Pointer to the destination array where the content is to be copied.</param>
/// <param name="src">Pointer to the source of data to be copied.</param>
/// <param name="len">Number of bytes to copy.</param>
/// <returns></returns>
extern __intrinsic void memcpy(void* dest, const void* src, unsigned int len);

/// <summary>Copies the string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point).</summary>
/// <param name="dest">Pointer to the destination array where the content is to be copied.</param>
/// <param name="src">String to be copied.</param>
/// <param name="destBufferLen">The length of the dest buffer.<para>This value must be an integer literal in the range of 1 - 255.</para></param>
/// <returns></returns>
extern __intrinsic void strcpy(char* dest, const char* src, const byte destBufferLen);

/// <summary>
/// Appends a copy of the source string to the destination string. 
/// <para>The terminating null character in destination is overwritten by the first character of source,</para>
/// <para>and a null-character is included at the end of the new string formed by the concatenation of both in destination.</para>
/// </summary>
/// <param name="dest">Pointer to the destination array, which should contain a string, and be large enough to contain the concatenated resulting string.</param>
/// <param name="src">String to be appended. This should not overlap destination.</param>
/// <param name="destBufferLen">The length of the dest buffer.<para>This value must be an integer literal in the range of 1 - 255.</para></param>
/// <returns></returns>
extern __intrinsic void stradd(char* dest, const char* src, const byte destBufferLen);

/// <summary>
/// Appends a integer to the destination string. 
/// <para>The terminating null character in destination is overwritten by the first character of the integer conversion,</para>
/// <para>and a null-character is included at the end of the new string formed by the concatenation of both in destination.</para>
/// </summary>
/// <param name="dest">Pointer to the destination array, which should contain a string, and be large enough to contain the concatenated resulting string.</param>
/// <param name="value">Integer to be appended.</param>
/// <param name="destBufferLen">The length of the dest buffer.<para>This value must be an integer literal in the range of 1 - 255.</para></param>
/// <returns></returns>
extern __intrinsic void straddi(char* dest, int value, const byte destBufferLen);

/// <summary>Converts a integer to a string.</summary>
/// <param name="dest">Pointer to the destination array where the content is to be copied.</param>
/// <param name="value">Integer to be copied.</param>
/// <param name="destBufferLen">The length of the dest buffer.<para>This value must be an integer literal in the range of 1 - 255.</para></param>
/// <returns></returns>
extern __intrinsic void itos(char* dest, int value, const byte destBufferLen);

/// <summary>Copies the null-terminated byte string pointed to by src, including the null terminator, to the character array whose first element is pointed to by dest.</summary>
/// <param name="dest">Pointer to the character array to write to.</param>
/// <param name="src">Pointer to the null-terminated byte string to copy from.</param>
/// <returns></returns>
extern __intrinsic void strcpy_s(char* dest, const char* src);

/// <summary>Appends a copy of the null-terminated byte string pointed to by src to the end of the null-terminated byte string pointed to by dest.</summary>
/// <param name="dest">Pointer to the null-terminated byte string to append to.</param>
/// <param name="src">Pointer to the null-terminated byte string to copy from.</param>
/// <returns></returns>
extern __intrinsic void stradd_s(char* dest, const char* src);

/// <summary>Appends a copy of the null-terminated byte string converted from value to the end of the null-terminated byte string pointed to by dest.</summary>
/// <param name="dest">Pointer to the null-terminated byte string to append to.</param>
/// <param name="value">Value to be converted to a null-terminated byte string then appended.</param>
/// <returns></returns>
extern __intrinsic void straddi_s(char* dest, int value);

/// <summary>Copies the null-terminated byte string converted from value, including the null terminator, to the character array whose first element is pointed to by dest.</summary>
/// <param name="dest">Pointer to the character array to write to.</param>
/// <param name="value">Value to be converted to a null-terminated byte string then copied.</param>
/// <returns></returns>
extern __intrinsic void itos_s(char* dest, int value);

/// <summary>Computes the Jenkins one-at-a-time hash.</summary>
/// <param name="str">String to be hashed.</param>
/// <returns>The Jenkins one-at-a-time hash key of the string.</returns>
extern __intrinsic int getHashKey(const char* str);

#pragma endregion //}

#pragma region Misc_Opcodes //{
/// <summary>Gets a variable's index by its name.</summary>
/// <param name="varName">The variable name to be found.<para>This value must be an string literal.</para></param>
/// <returns>The var index.</returns>
extern __intrinsic const uint __varIndex(const char* varName);

#pragma endregion //}

#pragma region Math/Conversions //{
/// <summary>Reinterprets a int to a float without type conversion.</summary>
/// <param name="intValue">The integer value to be converted.</param>
/// <returns>The integer data now representing an float.</returns>
extern __intrinsic float reinterpretIntToFloat(int intValue);

/// <summary>Reinterprets a float to a int without type conversion.</summary>
/// <param name="floatValue">The floating-point value to be converted.</param>
/// <returns>The floating-point data now representing an int</returns>
extern __intrinsic int reinterpretFloatToInt(float floatValue);

/// <summary>Creates a vector3 with all values initialized as the floating-point value.</summary>
/// <param name="value">The floating-point value to be set.</param>
/// <returns>A vector3 with all values set as the floating-point value</returns>
extern __intrinsic vector3 toVector3(float value);

/// <summary>Adds each value of the left vector3 to each value the right vector3.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The addition result of the two vector3s.</returns>
extern __intrinsic vector3 vector3Add(vector3 left, vector3 right);

/// <summary>Substacts each value of the left vector3 from each value the right vector3.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The subtraction result of the two vector3s.</returns>
extern __intrinsic vector3 vector3Sub(vector3 left, vector3 right);

/// <summary>Multiplies each value of the left vector3 by each value the right vector3.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The multiplication result of the two vector3s.</returns>
extern __intrinsic vector3 vector3Mult(vector3 left, vector3 right);

/// <summary>Divides each value of the left vector3 by each value the right vector3.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The division result of the two vector3s.</returns>
extern __intrinsic vector3 vector3Div(vector3 left, vector3 right);

/// <summary>Negates each value of the vector3.</summary>
/// <param name="vector">The vector to be negated.</param>
/// <returns>The negation result of the vector3.</returns>
extern __intrinsic vector3 vector3Neg(vector3 vector);

/// <summary>Calculates the dot product of two vector3s.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The dot product of the two vector3s.</returns>
extern __intrinsic float vector3Dot(vector3 left, vector3 right);

/// <summary>Flattens the height value of the vector3 to 0.</summary>
/// <param name="vector">The vector to be flattened.</param>
/// <returns>The flatten result of the vector3.</returns>
extern __intrinsic vector3 vector3Flatten(vector3 vector);

/// <summary>Creates a vector2 with all values initialized as the floating-point value.</summary>
/// <param name="value">The floating-point value to be set.</param>
/// <returns>A vector2 with all values set as the floating-point value</returns>
extern __intrinsic vector2 toVector2(float value);

/// <summary>Adds each value of the left vector2 to each value the right vector2.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The addition result of the two vector2s.</returns>
extern __intrinsic vector2 vector2Add(vector2 left, vector2 right);

/// <summary>Substacts each value of the left vector2 from each value the right vector3.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The subtraction result of the two vector2s.</returns>
extern __intrinsic vector2 vector2Sub(vector2 left, vector2 right);

/// <summary>Multiplies each value of the left vector2 by each value the right vector3.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The multiplication result of the two vector2s.</returns>
extern __intrinsic vector2 vector2Mult(vector2 left, vector2 right);

/// <summary>Divides each value of the left vector2 by each value the right vector3.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The division result of the two vector2s.</returns>
extern __intrinsic vector2 vector2Div(vector2 left, vector2 right);

/// <summary>Negates each value of the vector2.</summary>
/// <param name="vector">The vector to be negated.</param>
/// <returns>The negation result of the vector2.</returns>
extern __intrinsic vector2 vector2Neg(vector2 vector);

/// <summary>Calculates the dot product of two vector2s.</summary>
/// <param name="left">The left side of the operation.</param>
/// <param name="right">The right side of the operation.</param>
/// <returns>The dot product of the two vector2s.</returns>
extern __intrinsic float vector2Dot(vector2 left, vector2 right);

/// <summary>Converts a vector2 to a vector3 with z initialized as 0.</summary>
/// <param name="vector">The vector2 to be converted.</param>
/// <returns>The vector2 as a vector3 with z initialized as 0.</returns>
extern __intrinsic vector3 vector2ToVector3(vector2 vector);

/// <summary>Converts a vector3 to a vector2 with z truncated.</summary>
/// <param name="vector">The vector3 to be converted.</param>
/// <returns>The vector3 as a vector2 with z truncated.</returns>
extern __intrinsic vector2 vector3ToVector2(vector3 vector);

/// <summary>Returns the floating-point remainder of numer/denom</summary>
/// <param name="numer">The Value of the quotient numerator.</param>
/// <param name="denom">The Value of the quotient denominator.<para>If denom is zero, the function may either return zero or cause a domain error</para></param>
/// <returns>The remainder of dividing the arguments.</returns>
extern __intrinsic float fMod(float numer, float denom);

/// <summary>Tests if the bit at a index of a value is set.</summary>
/// <param name="value">The value of the integer to be tested.</param>
/// <param name="bitIndex">The bit index to be tested.<para>This value must be an integer literal.</para></param>
/// <returns>The if the bit is set.</returns>
extern __intrinsic bool bit_test(int value, const byte bitIndex);

/// <summary>Sets the bit at a index at the address of a value.</summary>
/// <param name="address">The address of the value.</param>
/// <param name="bitIndex">The bit index to be set.<para>This value must be an integer literal.</para></param>
/// <returns></returns>
extern __intrinsic void bit_set(int* address, const byte bitIndex);

/// <summary>Resets the bit at a index at the address of a value.</summary>
/// <param name="address">The address of the value.</param>
/// <param name="bitIndex">The bit index to be reset.<para>This value must be an integer literal.</para></param>
/// <returns></returns>
extern __intrinsic void bit_reset(int* address, const byte bitIndex);

/// <summary>Flips the bit at a index at the address of a value.</summary>
/// <param name="address">The address of the value.</param>
/// <param name="bitIndex">The bit index to be flipped.<para>This value must be an integer literal.</para></param>
/// <returns></returns>
extern __intrinsic void bit_flip(int* address, const byte bitIndex);
#pragma endregion //}

#pragma region Variables //{
/// <summary>Sets a static variable at a specific index.</summary>
/// <param name="index">The index of the static to set.<para>This value must be an integer literal.</para></param>
/// <param name="value">The value to set the static.</param>
/// <returns></returns>
extern __intrinsic void setStaticAtIndex(const uint index, int value);

/// <summary>Gets a static variable at a specific index.</summary>
/// <param name="index">The index of the static to get.<para>This value must be an integer literal.</para></param>
/// <returns>The static value.</returns>
extern __intrinsic int getStaticAtIndex(const uint index);

/// <summary>Gets the pointer to a static variable at a specific index.</summary>
/// <param name="index">The index of the static to get.<para>This value must be an integer literal.</para></param>
/// <returns>The pointer to the static.</returns>
extern __intrinsic void* getStaticPtrAtIndex(const uint index);

/// <summary>Sets a global variable at a specific index.</summary>
/// <param name="index">The index of the global to set.<para>This value must be an integer literal.</para></param>
/// <param name="value">The value to set the global.</param>
/// <returns></returns>
extern __intrinsic void setGlobalAtIndex(const uint index, int value);

/// <summary>Gets a global variable at a specific index.</summary>
/// <param name="index">The index of the global to get.<para>This value must be an integer literal.</para></param>
/// <returns>The global value.</returns>
extern __intrinsic int getGlobalAtIndex(const uint index);

/// <summary>Gets the pointer to a global variable at a specific index.</summary>
/// <param name="index">The index of the global to get.<para>This value must be an integer literal.</para></param>
/// <returns>The pointer to the global.</returns>
extern __intrinsic void* getGlobalPtrAtIndex(const uint index);

/// <summary>Gets the pointer to a variable at a specific index in a array.</summary>
/// <param name="array">The pointer to the array.</param>
/// <param name="index">The index of the array item.</param>
/// <param name="arrayItemSize">The array item size.<para>This value must be an integer literal.</para></param>
/// <returns>The pointer to the array item.</returns>
extern __intrinsic void* getPtrFromArrayIndex(const void* array, int index, const int arrayItemSize);

/// <summary>Gets the pointer at a immediate index of a pointer.</summary>
/// <param name="pointer">The starting pointer.</param>
/// <param name="immIndex">The immediate index.<para>This value must be an integer literal.</para></param>
/// <returns>The pointer + immIndex * 4.</returns>
extern __intrinsic void* getPtrImmIndex(const void* pointer, const int immIndex);
#pragma endregion //}

#if PTRWIDTH == 64
#pragma region YSC_Specific //{
extern __intrinsic void setLoDWord(void* addr, int value);
extern __intrinsic void setHiDWord(void* addr, int value);
extern __intrinsic int getLoDWord(void* addr);
extern __intrinsic int getHiDWord(void* addr);
#pragma endregion //}
#endif

#if TARGET == TARGET_GTAV
extern __intrinsic unsigned char getByte(void* addr);
extern __intrinsic void setByte(void* addr, unsigned char value);
#endif

#pragma region Custom_ASM //{
/*************************************************************************
*	These perform the operation on the item(or vector) on top of the stack
*	This can lead to dangerous behaviour if you aren't sure what is currently on the stack
*************************************************************************/

/// <summary>Pops multiple items off the stack.</summary>
/// <param name="count">The amount of items to pop off.<para>This value must be an integer literal.</para></param>
/// <returns></returns>
extern __unsafeIntrinsic void __popMult(const uint count);

/// <summary>Pushes a vector3 on the stack.</summary>
/// <param name="value">The vector3 to be pushed.</param>
/// <returns></returns>
extern __unsafeIntrinsic void __pushV(vector3 value);

/// <summary>Pushes a struct on the stack.</summary>
/// <param name="structure">The struct to be pushed.</param>
/// <returns></returns>
extern __unsafeIntrinsic void __pushStruct(void* structure);

/// <summary>Pops a struct off the stack.</summary>
/// <param name="structure">The struct to be poped.</param>
/// <returns></returns>
extern __unsafeIntrinsic void __popStruct(void* structure);

/// <summary>Reverses items on the stack.</summary>
/// <param name="numItems">The amount of items to be reversed.<para>This value must be an integer literal.</para></param>
/// <returns></returns>
extern __unsafeIntrinsic void __rev(const int numItems);

/// <summary>Exchanges two same sized structs on the stack.</summary>
/// <param name="structStackSize">The size of the struct.</param>
/// <returns></returns>
extern __unsafeIntrinsic void __exch(const int structStackSize);

/// <summary>Gets the top item on the stack as a int.</summary>
/// <returns>The top item on the stack as a int.</returns>
extern __unsafeIntrinsic int __popI();

/// <summary>Gets the top item on the stack as a float.</summary>
/// <returns>The top item on the stack as a float.</returns>
extern __unsafeIntrinsic float __popF();

/// <summary>Gets the top 3 items on the stack as a vector3.</summary>
/// <returns>The top 3 items on the stack as a vector3.</returns>
extern __unsafeIntrinsic vector3 __popV();

/// <summary>Pushes an amount of items from the specified pointer to the stack.</summary>
/// <param name="address">The pointer to draw from.</param>
/// <param name="count">The amount of items to push to the stack.</param>
/// <returns></returns>
extern __unsafeIntrinsic void __ptrToStack(const void* address, int count);

/// <summary>Pops an amount of items from the stack to the specified pointer.</summary>
/// <param name="address">The pointer to place the items.</param>
/// <param name="count">The amount of items to pop from the stack.</param>
/// <returns></returns>
extern __unsafeIntrinsic void __ptrFromStack(const void* address, int count);
#pragma endregion //}

#pragma region ASM //{
/*************************************************************************
*	These perform an operation on the item(or vector) on top of the stack
*	This can lead to dangerous behaviour if you aren't sure what is currently on the stack
*************************************************************************/

/// <summary>
///		Adds specified amount of nops to the script in the interval [0,4096].
///		<para>Note: GTAIV nops exit the script.</para>
/// </summary>
/// <param name="count">The amount of nops to add.</param>
/// <returns></returns>
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

#undef __intrinsic
#undef __unsafeIntrinsic

#define CreateSizedArray(type, name, sizein, ...)\
struct SizedArray\
{\
	unsigned int size;\
	type items[sizein];\
} name = {.size = sizein, .items = {__VA_ARGS__}}

#define GetSizedArraySize(sizedarr) (*(unsigned int*)sizedarr)
#define GetSizedArrayItem(sizedarr, type, index) (*(type*)((int*)sizedarr + 1 + index))


#define ArrayToSizedArray(arr, sizedarr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	memcpy(sizedarr.items, arr, countof(arr));

#define SizedArrayToArray(sizedarr, arr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	memcpy(arr, sizedarr.items, countof(sizedarr.items));

