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
    NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(LobbySize, false, 0);
    NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(HostBroadcastVars, 3);
    NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(PlayerBroadcastVars, LobbySize + 1);
    RESERVE_NETWORK_MISSION_VEHICLES(1);

    InitMenuDraw();

    while (true)
    {
        WAIT(0);

        HandleMenuUi();

        AsynchronousLoop();

        if (!NETWORK_IS_IN_TRANSITION())
            LoopedExecutionEntry();
    }
}

