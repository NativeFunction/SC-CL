#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "common.c"
#include "funcs.c"
#include "inc.h"

static void test()
{
	1+1*3;
	mani("");
}
void main(int* data, int size)
{
	__push(5);
	__neg();
	float klm = acos(6.0f);
	short *t, *s;
	while((*t++ = *s++)) ;
	mani("");
	JumpOver30000();
	SwitchJumpOver65535();
	test();
	hello();
}
