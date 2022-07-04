#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"

#include "funcs.c"

const int j = 40000;

struct MenuToggles
{
	//unsigned int start;
	unsigned Invulnerability : 1;
	unsigned InfiniteDeadeye : 8;
	unsigned FlyMod : 1;
	unsigned BlazingGuns : 1;
	unsigned InfiniteHorseStamina : 1;
	unsigned ExplosiveWeapons : 1;
	unsigned endi : 19;

	unsigned startnbs : 1;
	//unsigned int end;
} MenuToggles = { 1, 2, 4, 0, 5, 10, j };


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
	//do init str/uni bitfield
	//do init str/uni bitfield gbl
	//do str/uni bitfield gbl
	int t = 0b00000001111101000001001111010010;
	
	
	MenuToggles.startnbs = true;
	MenuToggles.endi = 138371;
	MenuToggles.Invulnerability = true;
	MenuToggles.Invulnerability = false;
	MenuToggles.InfiniteDeadeye = 239;
	MenuToggles.ExplosiveWeapons = true;
	MenuToggles.InfiniteDeadeye = 200;
	
	
	int iArrTest[13] = {0};
	iArrTest[12] = 1338;
	iArrTest[11] = 1339;
	
	short sArrTest[13] = {0};
	sArrTest[12] = 1340;
	sArrTest[11] = 1341;
	
	char cArrTest[13] = {0};
	sArrTest[12] = 1342;
	sArrTest[11] = 1343;
	
	memset(intArrTest, 0, 13 * 4);
	
	int* iPtr = 0x03000000C13F8000;
	iPtr[7] = 5;
	short* sPtr = 0x03000000C13F8000;
	sPtr[7] = 5;
	char* cPtr = 0x03000000C13F8000;
	cPtr[7] = 5;
	
	iPtr++;
	sPtr++;
	cPtr++;
	
	int diff = iPtr - sPtr;
	
	
	
	
	ShortTesting();
	
	mani("hello");
	
	JumpOver30000();
	
	SwitchJumpOver65535()
	
	int hello = 1337;
	while(true)
	{
		
		PrintSubtitle("hello world");
		WAIT(0);
	}
	
}




