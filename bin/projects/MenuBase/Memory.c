#include "natives.h"
#include "types.h"
#include "constants.h"
#include "common.h"
#include "Memory.h"

#define ImageBase 0x7FF654150000
#define GetImageBaseRem(x) ((x) - 0x7FF654150000)//imagebase
//GetVehicleMetaFromHash (search CARNOTFOUND in exe from GET_VEHICLE_CLASS_FROM_NAME)
int* GetVehicleMetaAddress(VehicleHash Hash)
{
	return Sub64P((int*)get_display_name_from_vehicle_model(Hash), VMI_DisplayName);
}
