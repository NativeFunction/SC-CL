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
	short *t, *s;
	while((*t++ = *s++)) ;
	mani("");
	JumpOver30000();
	SwitchJumpOver65535();
	test();
	hello();
}