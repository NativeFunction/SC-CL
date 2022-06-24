#include "natives.h"
#include "types.h"
#include "constants.h"
#include "common.h"
#include "Utils.h"
#include "Memory.h"

#define ImageBase 0x7FF654150000
#define GetImageBaseRem(x) ((x) - ImageBase)
int* GetVehicleMetaAddress(VehicleHash Hash)
{
	const char* DisplayName = GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Hash);

	if (ARE_STRINGS_EQUAL(DisplayName, "CARNOTFOUND"))
		return nullptr;
	else
		return Sub64P((int*)DisplayName, VMI_DisplayName, 0);
}
int* GetExecutableAddress()
{
	#if PLATFORM == PLATFORM_PC
		#define ExeBaseToStringDist 31273176
		return Sub64P((int*)_GET_ONLINE_VERSION(), ExeBaseToStringDist, 0);
		#undef ExeBaseToStringDist
	#elif PLATFORM == PLATFORM_XBOX
		return (int*)0x82000000;
	#elif PLATFORM == PLATFORM_PS3
		return (int*)0x00010000;
	#endif
}
