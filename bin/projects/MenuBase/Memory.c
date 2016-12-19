#include "natives.h"
#include "types.h"
#include "constants.h"
#include "common.h"
#include "Memory.h"

#define ImageBase 0x7FF654150000
#define GetImageBaseRem(x) ((x) - 0x7FF654150000)//imagebase
int* GetVehicleMetaAddress(VehicleHash Hash)
{
	const char* DisplayName = get_display_name_from_vehicle_model(Hash);
	
	if (are_strings_equal(DisplayName, "CARNOTFOUND"))
		return nullptr;
	else
		return Sub64P((int*)DisplayName, VMI_DisplayName);
}
