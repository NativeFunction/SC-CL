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

/// <summary>Gets the byte at an address in big endian.</summary>
/// <param name="addr">The address of the value you want to get.</param>
/// <returns>The the byte at an address in big endian.</returns>
extern __intrinsic unsigned char getByte(void* addr);

/// <summary>Sets the byte at an address.</summary>
/// <param name="addr">The address of the value you want to set.</param>
/// <param name="value">The value you want to set.</param>
extern __intrinsic void setByte(void* addr, unsigned char value);
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
/// <summary>Sets the lower 32 bits of a value.</summary>
/// <param name="addr">The address of the value you want to set.</param>
/// <param name="value">The value to set.</param>
extern __intrinsic void setLoDWord(void* addr, int value);
/// <summary>Sets the higher 32 bits of a value.</summary>
/// <param name="addr">The address of the value you want to set.</param>
/// <param name="value">The value to set.</param>
extern __intrinsic void setHiDWord(void* addr, int value);
/// <summary>Gets the lower 32 bits of a value.</summary>
/// <param name="addr">The address of the value you want to get.</param>
/// <returns>The the lower 32 bits of the value.</returns>
extern __intrinsic int getLoDWord(void* addr);
/// <summary>Gets the higher 32 bits of a value.</summary>
/// <param name="addr">The address of the value you want to get.</param>
/// <returns>The the higher 32 bits of the value.</returns>
extern __intrinsic int getHiDWord(void* addr);
#pragma endregion //}
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
/// <param name="structStackSize">The size of the struct.<para>This value must be an integer literal.</para></param>
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
/// <param name="count">The amount of nops to add.<para>This value must be an integer literal.</para></param>
/// <returns></returns>
extern __intrinsic void __nop(const uint count);
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) + Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __add();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) - Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __sub();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) * Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __mult();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) / Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __div();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) % Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __mod();
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Performs {!Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __not();
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Performs {-Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __neg();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) == Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpEq();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) != Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpNe();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) > Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpGt();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) >= Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpGe();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) &#60; Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpLt();
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) &#60;= Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpLe();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) + Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __addF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) - Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __subF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) * Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __multF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) / Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __divF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) % Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __modF();
/// <summary>
/// Pops one item off the stack.  (float)
/// <para>Performs {-Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __negF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) == Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpEqF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) != Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpNeF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) > Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpGtF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) >= Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpGeF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) &#60; Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpLtF();
/// <summary>
/// Pops two items off the stack. (float, float)
/// <para>Performs {(Stack.Top - 1) &#60;= Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __cmpLeF();
/// <summary>
/// Pops six items off the stack. (float, float, float, float, float, float)
/// <para>Performs {(Stack.Top - 5) + (Stack.Top - 2)} as a float.</para>
/// <para>Performs {(Stack.Top - 4) + (Stack.Top - 1)} as a float.</para>
/// <para>Performs {(Stack.Top - 3) + Stack.Top} as a float.</para>
/// <para>Pushes three items on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __addV();
/// <summary>
/// Pops six items off the stack. (float, float, float, float, float, float)
/// <para>Performs {(Stack.Top - 5) - (Stack.Top - 2)} as a float.</para>
/// <para>Performs {(Stack.Top - 4) - (Stack.Top - 1)} as a float.</para>
/// <para>Performs {(Stack.Top - 3) - Stack.Top} as a float.</para>
/// <para>Pushes three items on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __subV();
/// <summary>
/// Pops six items off the stack. (float, float, float, float, float, float)
/// <para>Performs {(Stack.Top - 5) * (Stack.Top - 2)} as a float.</para>
/// <para>Performs {(Stack.Top - 4) * (Stack.Top - 1)} as a float.</para>
/// <para>Performs {(Stack.Top - 3) * Stack.Top} as a float.</para>
/// <para>Pushes three items on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __multV();
/// <summary>
/// Pops six items off the stack. (float, float, float, float, float, float)
/// <para>Performs {(Stack.Top - 5) / (Stack.Top - 2)} as a float.</para>
/// <para>Performs {(Stack.Top - 4) / (Stack.Top - 1)} as a float.</para>
/// <para>Performs {(Stack.Top - 3) / Stack.Top} as a float.</para>
/// <para>Pushes three items on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __divV();
/// <summary>
/// Pops three items off the stack. (float, float, float)
/// <para>Performs {-(Stack.Top - 2)} as a float.</para>
/// <para>Performs {-(Stack.Top - 1)} as a float.</para>
/// <para>Performs {-Stack.Top} as a float.</para>
/// <para>Pushes three items on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __negV();
/// <summary>
/// Pops two item off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) & Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __and();
/// <summary>
/// Pops two item off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) | Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __or();
/// <summary>
/// Pops two item off the stack. (signed int32, signed int32)
/// <para>Performs {(Stack.Top - 1) ^ Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __xor();
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Performs {(float)Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __iToF();
/// <summary>
/// Pops one item off the stack. (float)
/// <para>Performs {(int)Stack.Top} as a float.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __fToI();
/// <summary>
/// Pops one item off the stack. (float)
/// <para>Pushes three items of value Stack.Top on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __fToV();
/// <summary>Pushes two signed int32 values to the stack.</summary>
/// <param name="value0">The first value to push to the stack.<para>This value must be an integer literal.</para></param>
/// <param name="value1">The second value to push to the stack.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __push2(const int value0, const int value1);
/// <summary>Pushes three signed int32 values to the stack.</summary>
/// <param name="value0">The first value to push to the stack.<para>This value must be an integer literal.</para></param>
/// <param name="value1">The second value to push to the stack.<para>This value must be an integer literal.</para></param>
/// <param name="value2">The third value to push to the stack.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __push3(const int value0, const int value1, const int value2);
/// <summary>Pushes one signed int32 value to the stack.</summary>
/// <param name="value">The value to push to the stack.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __push(const int value);
/// <summary>Pushes one float value to the stack.</summary>
/// <param name="value">The value to push to the stack.<para>This value must be an floating-point literal.</para></param>
extern __unsafeIntrinsic void __pushF(const float value);
/// <summary>Pushes a duplicate of Stack.Top to the stack.</summary>
extern __unsafeIntrinsic void __dup();
/// <summary>Pops one item off the stack and discards it.</summary>
extern __unsafeIntrinsic void __drop();
/// <summary>
/// Pops the amount of items off the stack that the function takes.
/// <para>Calls a native function.</para>
/// </summary>
/// <param name="nativeHash">The hash relating to the native.<para>This value must be an integer literal.</para></param>
/// <param name="paramCount">The param count of the native.<para>This value must be an integer literal.</para></param>
/// <param name="returnCount">The return count of the native.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __callNative(const uint nativeHash, const uint paramCount, const uint returnCount);
/// <summary>
/// Pops the amount of items off the stack that the function takes.
/// <para>Calls a native function.</para>
/// </summary>
/// <param name="nativeHash64Part1">The upper 32 bits of the hash relating to the native.<para>This value must be an integer literal.</para></param>
/// <param name="nativeHash64Part2">The lower 32 bits of the hash relating to the native.<para>This value must be an integer literal.</para></param>
/// <param name="paramCount">The param count of the native.<para>This value must be an integer literal.</para></param>
/// <param name="returnCount">The return count of the native.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __callNativePc(const uint nativeHash64Part1, const uint nativeHash64Part2, const uint paramCount, const uint returnCount);
/// <summary>Returns a function.</summary>
/// <param name="paramCount">The param count of the function.<para>This value must be an integer literal.</para></param>
/// <param name="returnCount">The return count of the function.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __return(const uint paramCount, const uint returnCount);
/// <summary>
/// Pops one item off the stack. (void*)
/// <para>Performs {*Stack.Top} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __pGet();
/// <summary>
/// Pops two items off the stack. (signed int32, void*)
/// <para>Performs {*Stack.Top = (Stack.Top - 1)} as a signed int32.</para>
/// </summary>
extern __unsafeIntrinsic void __pSet();
/// <summary>
/// Pops two items off the stack. (void*, signed int32)
/// <para>Performs {*(Stack.Top - 1) = Stack.Top} as a signed int32.</para>
/// <para>Pushes Stack.Top on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __pPeekSet();
/// <summary>
/// Pops two items off the stack. (signed int32, void*)
/// <para>Pushes items at the pointer Stack.Top for (Stack.Top - 1) on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __toStack();
/// <summary>
/// Pops two items off the stack. (signed int32, void*)
/// <para>Pops off items from the stack for (Stack.Top - 1) into the pointer Stack.Top.</para>
/// </summary>
extern __unsafeIntrinsic void __fromStack();
/// <summary>
/// Pops two items off the stack. (signed int32, void*)
/// <para>Performs {&Stack.Top[(Stack.Top - 1)]}.</para>>
/// </summary>
/// <param name="arraySize">The array item stack size.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getArrayP(const uint arraySize);
/// <summary>
/// Pops two items off the stack. (signed int32, void*)
/// <para>Performs {Stack.Top[(Stack.Top - 1)]}.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
/// <param name="arraySize">The array item stack size.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getArray(const uint arraySize);
/// <summary>
/// Pops two items off the stack. (signed int32, void*)
/// <para>Performs {&Stack.Top[(Stack.Top - 1)] = (Stack.Top - 2)}.</para>
/// </summary>
/// <param name="arraySize">The array item stack size.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __setArray(const uint arraySize);
/// <summary>
/// Gets a local functon frame pointer by an index.
/// <para>Pushes the frame pointer on the stack.</para>
/// </summary>
/// <param name="frameIndex">The index to get the frame at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getFrameP(const uint frameIndex);
/// <summary>
/// Gets a local functon frame pointer by it's name.
/// <para>Pushes the frame pointer on the stack.</para>
/// </summary>
/// <param name="frameName">The name of the local function frame.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __getNamedFrameP(const char* frameName);
/// <summary>
/// Gets a local functon frame by an index.
/// <para>Pushes the frame on the stack.</para>
/// </summary>
/// <param name="frameIndex">The index to get the frame at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getFrame(const uint frameIndex);
/// <summary>
/// Gets a local functon frame by it's name.
/// <para>Pushes the frame on the stack.</para>
/// </summary>
/// <param name="frameName">The name of the local function frame.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __getNamedFrame(const char* frameName);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Sets a local functon frame by an index.</para>
/// </summary>
/// <param name="frameIndex">The index to set the frame at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __setFrame(const uint frameIndex);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Sets a local functon frame by it's name.</para>
/// </summary>
/// <param name="frameName">The name of the local function frame.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __setNamedFrame(const char* frameName);
/// <summary>
/// Gets a static var pointer by an index.
/// <para>Pushes the static var pointer on the stack.</para>
/// </summary>
/// <param name="staticIndex">The index to get the static at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getStaticP(const uint staticIndex);
/// <summary>
/// Gets a static var pointer by it's name.
/// <para>Pushes the static var pointer on the stack.</para>
/// </summary>
/// <param name="StaticName">The name of the static var.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __getNamedStaticP(const char* StaticName);
/// <summary>
/// Gets a static var by an index.
/// <para>Pushes the static var on the stack.</para>
/// </summary>
/// <param name="staticIndex">The index to get the static at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getStatic(const uint staticIndex);
/// <summary>
/// Gets a static var by it's name.
/// <para>Pushes the static var on the stack.</para>
/// </summary>
/// <param name="StaticName">The name of the static var.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __getNamedStatic(const char* StaticName);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Sets a static var by an index.</para>
/// </summary>
/// <param name="staticIndex">The index to set the static at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __setStatic(const uint staticIndex);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Sets a static var by it's name.</para>
/// </summary>
/// <param name="StaticName">The name of the static var.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __setNamedStatic(const char* StaticName);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Performs {Stack.Top + value} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
/// <param name="value">Right hand side of the math operation.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __addImm(const uint value);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Performs {Stack.Top * value} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
/// <param name="value">Right hand side of the math operation.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __multImm(const uint value);
/// <summary>
/// Pops one item off the stack. (void*)
/// <para>Performs {Stack.Top + immediate * 4} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
/// <param name="immediate">The immediate value of a pointer.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getImmP(const uint immediate);
/// <summary>
/// Pops one item off the stack. (void*)
/// <para>Performs {*(Stack.Top + immediate * 4)} as a signed int32.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
/// <param name="immediate">The immediate value of a pointer.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getImm(const uint immediate);
/// <summary>
/// Pops one item off the stack. (signed int32, void*)
/// <para>Performs {*(Stack.Top + immediate * 4) = (Stack.Top - 1)} as a signed int32.</para>
/// </summary>
/// <param name="immediate">The immediate value of a pointer.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __setImm(const uint immediate);
/// <summary>
/// Gets a global var pointer by an index.
/// <para>Pushes the global var pointer on the stack.</para>
/// </summary>
/// <param name="globalIndex">The index to get the global at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getGlobalP(const uint globalIndex);
/// <summary>
/// Gets a global var by an index.
/// <para>Pushes the global var on the stack.</para>
/// </summary>
/// <param name="globalIndex">The index to get the global at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __getGlobal(const uint globalIndex);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Sets a global var by an index.</para>
/// </summary>
/// <param name="globalIndex">The index to set the global at.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __setGlobal(const uint globalIndex);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Switchs on Stack.Top to the case.</para>
/// <para>This function must have a label for every case.</para>
/// </summary>
/// <param name="Case">The case of the switch.<para>This value must be an integer literal.</para></param>
/// <param name="label">The label of the switch to jump to if Stack.Top == Case.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __switch(const int Case, const char* label, ...);
/// <summary>
/// Performs {goto label;}.
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jump(const char* label);
/// <summary>
/// Pops one item off the stack. (signed int32)
/// <para>Performs {if(Stack.Top) goto label;}.</para>
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jumpFalse(const char* label);
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {if((Stack.Top - 1) != Stack.Top) goto label;}.</para>
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jumpNE(const char* label);
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {if((Stack.Top - 1) == Stack.Top) goto label;}.</para>
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jumpEQ(const char* label);
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {if((Stack.Top - 1) &#60;= Stack.Top) goto label;}.</para>
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jumpLE(const char* label);
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {if((Stack.Top - 1) &#60; Stack.Top) goto label;}.</para>
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jumpLT(const char* label);
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {if((Stack.Top - 1) >= Stack.Top) goto label;}.</para>
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jumpGE(const char* label);
/// <summary>
/// Pops two items off the stack. (signed int32, signed int32)
/// <para>Performs {if((Stack.Top - 1) > Stack.Top) goto label;}.</para>
/// </summary>
/// <param name="label">The label to jump to.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __jumpGT(const char* label);
/// <summary>
/// Pops the amount of items off the stack that the function takes.
/// <para>Calls a function.</para>
/// </summary>
/// <param name="functionName">The name of the function to call.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __call(const char* functionName);
/// <summary>Pushes one char* to the stack.</summary>
/// <param name="value">The string that will be referenced by the pointer.<para>This value must be an string literal.</para></param>
extern __unsafeIntrinsic void __pushString(const char* value);
/// <summary>
/// Pops one item off the stack. (char*)
/// <para>Performs {joaat(Stack.Top);}.</para>
/// <para>Pushes one item on the stack.</para>
/// </summary>
extern __unsafeIntrinsic void __getHash();
/// <summary>
/// Pops two items off the stack. (char*, char*)
/// <para>Copies (Stack.Top - 1) into Stack.Top for strLen bytes or until a 0 was hit in (Stack.Top - 1).</para>
/// </summary>
/// <param name="strLen">The length of the string destination buffer.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __strCopy(const uint strLen);
/// <summary>
/// Pops two items off the stack. (signed int32, char*)
/// <para>Copies the string representation of (Stack.Top - 1) into Stack.Top for strLen bytes or until a 0 was hit in (Stack.Top - 1).</para>
/// </summary>
/// <param name="strLen">The length of the string destination buffer.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __iToS(const uint strLen);
/// <summary>
/// Pops two items off the stack. (char*, char*)
/// <para>Appends (Stack.Top - 1) into Stack.Top for strLen bytes or until a 0 was hit in (Stack.Top - 1).</para>
/// </summary>
/// <param name="strLen">The length of the string destination buffer.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __strAdd(const uint strLen);
/// <summary>
/// Pops two items off the stack. (signed int32, char*)
/// <para>appends the string representation of (Stack.Top - 1) into Stack.Top for strLen bytes or until a 0 was hit in (Stack.Top - 1).</para>
/// </summary>
/// <param name="strLen">The length of the string destination buffer.<para>This value must be an integer literal.</para></param>
extern __unsafeIntrinsic void __strAddI(const uint strLen);
/// <summary>
/// Pops three items off the stack. (signed int32, signed int32, void*)
/// <para>Pops off items from the stack for {(Stack.Top - 2) * (Stack.Top - 1) / 4} into the pointer Stack.Top.</para>
/// </summary>
extern __unsafeIntrinsic void __memCopy();
/// <summary>
/// Pops one item off the stack. (void*) then pops the amount of items off the stack that the function takes.
/// <para>Calls the function at the pointer Stack.Top.</para>
/// </summary>
extern __unsafeIntrinsic void __pCall();
#pragma endregion //}

#undef __intrinsic
#undef __unsafeIntrinsic

/// <summary>Creates a array with the first item as the size.</summary>
/// <param name="type">The type of array to create.</param>
/// <param name="name">The name of the array to create.</param>
/// <param name="sizein">The size of the array to create.</param>
#define CreateSizedArray(type, name, sizein, ...)\
struct SizedArray\
{\
	unsigned int size;\
	type items[sizein];\
} name = {.size = sizein, .items = {__VA_ARGS__}}

/// <summary>Gets the size of the sized array.</summary>
/// <param name="sizedarr">The pointer to the sized array.</param>
#define GetSizedArraySize(sizedarr) (*(unsigned int*)sizedarr)

/// <summary>Gets an item of the sized array.</summary>
/// <param name="sizedarr">The pointer to the sized array.</param>
/// <param name="type">The type of the sized array.</param>
/// <param name="index">The index of the sized array item.</param>
#define GetSizedArrayItem(sizedarr, type, index) (*(type*)((int*)sizedarr + 1 + index))

/// <summary>Converts an array to a sized array.</summary>
/// <param name="arr">The pointer to the array.</param>
/// <param name="sizedarr">The pointer to the sized array.</param>
#define ArrayToSizedArray(arr, sizedarr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	memcpy(sizedarr.items, arr, countof(arr));

/// <summary>Converts an sized array to a array.</summary>
/// <param name="sizedarr">The pointer to the sized array.</param>
/// <param name="arr">The pointer to the array.</param>
#define SizedArrayToArray(sizedarr, arr)\
if(sizeof(arr) == sizeof(sizedarr.items))\
	memcpy(arr, sizedarr.items, countof(sizedarr.items));

