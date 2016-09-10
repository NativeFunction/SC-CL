#pragma once
#include "types.h"
#include "constants.h"

#define __intrinsic __attribute__((__intrinsic__))

#define __intrinsic_advanced_user true
#if __intrinsic_advanced_user == false
#define __asm_unsafe __attribute__((deprecated("This asm function is extremely unsafe. It should only be used if you know what you are doing.")))
#else
#define __asm_unsafe 
#endif
#undef __intrinsic_advanced_user

#define offsetof(st, m) ((uint)&(((st *)0)->m))
#define count(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#pragma region String
//{ String
extern __intrinsic void memcpy(void* dest, const void* src, size_t len);
extern __intrinsic void strcpy(char* dest, char* src, const byte len);
extern __intrinsic void stradd(char* dest, char* src, const byte len);
extern __intrinsic void straddi(char* dest, int value, const byte len);
extern __intrinsic void itos(char* dest, int value, const byte len);
//}
#pragma endregion

#pragma region Misc_Opcodes
//{ Misc_Opcodes
extern __intrinsic __asm_unsafe void pcall(void* funcAddr, ...);//params with types like floats must be implicitly set (1.0f)
//}
#pragma endregion

#pragma region Stack_Operations
//{ Stack_Operations
extern __intrinsic any stacktop();
extern __intrinsic __asm_unsafe void pop(const uint count);
extern __intrinsic __asm_unsafe void popMult(const uint count);
extern __intrinsic __asm_unsafe void pushFloat(float floatValue);
extern __intrinsic __asm_unsafe void pushInt(int intValue);
extern __intrinsic __asm_unsafe void dupStackTop();
//}
#pragma endregion

#pragma region Math/Conversions
//{ Math/Conversions
extern __intrinsic __asm_unsafe int add(int value);
extern __intrinsic __asm_unsafe int sub(int value);
extern __intrinsic __asm_unsafe int div(int value);
extern __intrinsic __asm_unsafe int mult(int value);
extern __intrinsic int creal(int _Complex complexInteger);
extern __intrinsic int cimag(int _Complex complexInteger);
extern __intrinsic float crealf(float _Complex complexFloat);
extern __intrinsic float cimagf(float _Complex complexFloat);
extern __intrinsic int _Complex cconj(int _Complex complexInteger);
extern __intrinsic float _Complex cconjf(float _Complex complexFloat);
extern __intrinsic float reinterpretIntToFloat(int intValue);
extern __intrinsic int reinterpretFloatToInt(float floatValue);
extern __intrinsic vector3 tovector3(float value);
//}
#pragma endregion

#pragma region Variables
//{ Variables
extern __intrinsic __asm_unsafe void setframe(int index);
extern __intrinsic int getframe(int index);
extern __intrinsic int getframep(int index);
extern __intrinsic void setglobal(int index, int value);
extern __intrinsic int getglobal(int index);
extern __intrinsic int getglobalp(int index);
//}
#pragma endregion

#undef __asm_unsafe
#undef __intrinsic