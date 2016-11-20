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
	float klh;
	
	__switch(0, "testLBL1", 1, "testLBL2", 2, "testLBL3");
	
	testLBL1:
	klh = acos(1.0f);
	testLBL2:
	klh = acos(2.0f);
	testLBL3:
	klh = acos(3.0f);
	short *t, *s;
	while((*t++ = *s++)) ;
	mani("");
	JumpOver30000();
	SwitchJumpOver65535();
	test();
	hello();
}
