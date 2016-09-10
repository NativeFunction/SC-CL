#pragma once
#include "types.h"

#define __intrinsic __attribute__((__intrinsic__))
#define __asm_unsafe __attribute__((deprecated("This asm function is extremely unsafe. It should only be used if you know what you are doing.")))

#define offsetof(st, m) ((uint)&(((st *)0)->m))

extern __intrinsic void strcpy(char* dest, char* src, const byte len);
extern __intrinsic void stradd(char* dest, char* src, const byte len);
extern __intrinsic void straddi(char* dest, int value, const byte len);
extern __intrinsic void itos(char* dest, int value, const byte len);
extern __intrinsic vector3 tovector3(float value);
extern __intrinsic any stacktop();
extern __intrinsic __asm_unsafe void pop(const uint count);
extern __intrinsic __asm_unsafe void popMult(const uint count);

#undef __asm_unsafe
#undef __intrinsic