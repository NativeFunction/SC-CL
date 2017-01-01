#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "Utils.h"
#include "MenuUiHandling.h"
#include "MenuExecutionHandling.h"
#include "common.h"

void main()
{
	//Break("script start");
	int HostBroadcastVars[3];
	int PlayerBroadcastVars[LobbySize + 1];
	//network_set_script_is_safe_for_network_game();
	network_set_this_script_is_network_script(LobbySize, false, 0);
	network_register_host_broadcast_variables(HostBroadcastVars, 3);
	network_register_player_broadcast_variables(PlayerBroadcastVars, LobbySize + 1);
	reserve_network_mission_vehicles(1);
	
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

