#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"

void PrintSubtitle(char* str)
{
	char* test = _GET_STRING_FROM_VECTOR(Vector3(1,2,3));
	
	_UILOG_SET_CACHED_OBJECTIVE(VAR_STRING(0, "STRING_LITERAL", str));
	_UILOG_PRINT_CACHED_OBJECTIVE();
	_UILOG_CLEAR_HAS_DISPLAYED_CACHED_OBJECTIVE();
	_UILOG_CLEAR_CACHED_OBJECTIVE();
}

void main()
{
	int hello = 1337;
	while(true)
	{
		
		PrintSubtitle("hello world");
		WAIT(0);
	}
	
}



