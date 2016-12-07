
#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "Utils.h"
#include "MenuUiHandling.h"
#include "MenuExecutionHandling.h"
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

void main()
{
	//Break("script start");
	int HostBroadcastVars[3];
	int PlayerBroadcastVars[LobbySize + 1];
	network_set_script_is_safe_for_network_game();
	network_set_this_script_is_network_script(Any(LobbySize), false, Any(0));
	network_register_host_broadcast_variables(HostBroadcastVars, 3);
	network_register_player_broadcast_variables(PlayerBroadcastVars, LobbySize + 1);
	reserve_network_mission_vehicles(1);
	
	NullStatics();
	
	InitMenuDraw();

	while (true)
	{
		wait(0);

		HandleMenuUi();

		AsynchronousLoop();

		if (!network_is_in_transition())
			LoopedExecutionEntry();
	}
}

