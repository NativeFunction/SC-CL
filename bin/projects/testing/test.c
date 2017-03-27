#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"

void print(const char* str, int ms)
{
	CLEAR_PRINTS();
	PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, ms, true);
}


int func(int var)
{
	print("Hello World", var);
	return 1000;
}


void main(){
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	
	int(*funcCall)(int) = func;
	
	funcCall(3000);
	
}
	
