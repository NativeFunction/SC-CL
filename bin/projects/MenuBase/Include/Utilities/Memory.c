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
	const char* DisplayName = get_display_name_from_vehicle_model(Hash);

	if (are_strings_equal(DisplayName, "CARNOTFOUND"))
		return nullptr;
	else
		return Sub64P((int*)DisplayName, VMI_DisplayName, 0);
}
int* GetExecutableAddress()
{
	#if PLATFORM == PLATFORM_PC
		#define ExeBaseToStringDist 31273176
		return Sub64P((int*)_get_online_version(), ExeBaseToStringDist, 0);
		#undef ExeBaseToStringDist
	#elif PLATFORM == PLATFORM_XBOX
		return (int*)0x82000000;
	#elif PLATFORM == PLATFORM_PS3
		return (int*)0x00010000;
	#endif
}
