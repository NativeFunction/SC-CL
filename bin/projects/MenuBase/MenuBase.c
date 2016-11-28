int Static0;
#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "Utils.h"
#include "MenuUiHandling.h"
#include "common.h"


inline void NullStatics()
{
	if (compare_strings(get_this_script_name(), "clothes_shop_mp", false, 16) == 0 
		|| compare_strings(get_this_script_name(), "clothes_shop_sp", false, 16) == 0
		|| compare_strings(get_this_script_name(), "hairdo_shop_sp", false, 15) == 0
		|| compare_strings(get_this_script_name(), "hairdo_shop_mp", false, 15) == 0
		)
		memset(getStaticPtrAtIndex(0), 0, 748 * item_size);
}
void LoopedOptions()
{
	
}


void main()
{
	//Break("script start");
	
	NullStatics();
	
	InitMenuDraw();

	while (true)
	{
		wait(0);

		if (!network_is_in_transition())
			LoopedOptions();

		HandleMenuUi();

	}
}

