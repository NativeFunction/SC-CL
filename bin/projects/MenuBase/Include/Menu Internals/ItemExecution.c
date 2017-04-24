#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "Utils.h"
#include "common.h"

#include "MenuExecutionHandling.h"
#include "Memory.h"

#pragma region SavedMenuVars
static float SavedTestCoordPrecision = 0;
static bool SavedBoolTest = false;
static int SavedMenuParam[3] = { 0 };
static int SelectedPlayerId = 0;
enum MenuBits
{
	MB_FlyMod,
	MB_FlyModToggle,
	MB_GodMode,
	MB_VehicleHelper,
	MB_NeverWanted
};
static int MenuLoopedBitset = 0;
#pragma endregion

#pragma region Helpers



#pragma endregion

#pragma region Parsers
const char* Parser_EnumTest(int ItemIndex)
{
	switch (GetEnumParserValue(ItemIndex))
	{
		case 0:  return "Parse0";
		case 1:  return "Parse1";
		case 2:  return "Parse2";
		case 3:  return "Parse3";
		case 4:  return "Parse4";
		case 5:  return "Parse5";
		case 6:  return "Parse6";
		case 7:  return "Parse7";
		case 8:  return "Parse8";
		case 9:  return "Parse9";
		case 10: return "Parse10";
	}
	return "NULL";
}
#pragma endregion

#pragma region Async
//NOTE: Async Functions must return a bool (has completed successfully), first param must be uint CurrentFrame and can have up to 10 params past CurrentFrame
bool Async_SpawnVehicle(uint CurrentFrame, Hash Model)
{
	if (is_model_in_cdimage(Model))
	{
		if (has_model_loaded(Model))
		{
			Ped MyPed = player_ped_id();
			Vehicle MyVehicle = create_vehicle(Model, get_entity_coords(MyPed, true), get_entity_heading(MyPed), true, true);
			int NetworkId = veh_to_net(MyVehicle);
			if (network_does_network_id_exist(NetworkId))
			{
				set_network_id_exists_on_all_machines(NetworkId, true);

				if (does_entity_exist(MyVehicle))
				{
					decor_set_int(MyVehicle, "MPBitset", 0);
					
					Vehicle CurrentVehicle = GetCurrentVehicle();
					float CurrentSpeed = 0.0f;
					int Station = -1;
					if (CurrentVehicle)
					{
						Station = get_player_radio_station_index();
						set_veh_radio_station(MyVehicle, get_radio_station_name(Station));

						CurrentSpeed = get_entity_speed(CurrentVehicle);
						set_entity_as_mission_entity(CurrentVehicle, false, true);
						delete_vehicle(&CurrentVehicle);
					}
					int SeatIndex = FindFreeCarSeat(MyVehicle);
					if (SeatIndex != -2)
					{
						set_ped_into_vehicle(MyPed, MyVehicle, SeatIndex);
						set_vehicle_engine_on(MyVehicle, true, true, false);//last param not on console remove if issues arise
						if (is_this_model_a_plane(Model) || is_this_model_a_heli(Model))
							set_heli_blades_full_speed(MyVehicle);

						if (Station != -1 && Station != 255)
						{
							set_radio_to_station_index(Station);
						}

						set_vehicle_forward_speed(MyVehicle, CurrentSpeed);
					}
					else
						Warn("Could not find available seat");
					set_model_as_no_longer_needed(Model);
					return true;
				}
			}
		}
		else if (CurrentFrame == 0)
			request_model(Model);
	}
	return false;
}
#pragma endregion

#pragma region Options
void Option_Blank()
{

}
void Option_DebugTest0()
{
	StartAsynchronousFunction(Async(Async_SpawnVehicle), 1, 150, AsyncParam(hashof("adder")));
}
void Option_LoadingOffTest()
{
	SetMenuLoading(false);
}
void Option_UiTestPrecision()
{
	SavedTestCoordPrecision = PrecisionToFloat(GetCurrentItem()->Selection.Value.Int);

	ItemContainer* Buffer;

	if (GetItemRelativeToCursor(1, &Buffer))
		Buffer->Selection.Precision = SavedTestCoordPrecision;
	if (GetItemRelativeToCursor(2, &Buffer))
		Buffer->Selection.Precision = SavedTestCoordPrecision;
}
void Option_TestUiCoordX()
{
	DEBUG__GetContainer()->UiTestCoords.x = GetCurrentItem()->Selection.Value.Float;
}
void Option_TestUiCoordY()
{
	DEBUG__GetContainer()->UiTestCoords.y = GetCurrentItem()->Selection.Value.Float;
}
void Option_TestInt()
{
	DEBUG__GetContainer()->TestInt = GetCurrentItem()->Selection.Value.Int;
}
void Option_BoolTest()
{
	//short sArr2D[3][5] = { { 1000,2000,3000,4000 },{ 6000,7000,8000,9000,10000 },{ 11000,12000,13000,14000,15000 } };

	//*Add64P(GetVehicleMetaAddress(VEHICLE_ADDER), VMI_VehicleType) = VEHICLE_TYPE_HELI;
	//*Add64P(GetVehicleMetaAddress(VEHICLE_ADDER), VMI_HandlingId) = 239;//ANNIHL
	//
	//*Add64P(GetVehicleMetaAddress(VEHICLE_DUMP), VMI_VehicleType) = VEHICLE_TYPE_AMPHIBIOUS_QUADBIKE;
	//*Add64P(GetVehicleMetaAddress(VEHICLE_DUMP), VMI_HandlingId) = 398;//blazer aqua

	//int t = (int)Push64P(0xFFFFFFFF, 0xFFFFFFFF);
	//t = (int)Add64P((int*)t, 1, 0);
	//Break(itosGlobal(t));
	//Break(itosGlobal(*(int*)((char*)&t + 4)));

	Break(itosGlobal(SwapEndian32(0xDEADBAB4)));

	//int data = 0xDEADBAB4;
	//short* ptr = (short*)&data;
	//*ptr = 34901;
	//Break(itosGlobal(*ptr));
	//
	//short stest = *ptr;
	//stest++;
	//stest = 1000;

	if (!UpdateBoolConditional(DEBUG__GetContainer()->TestInt != 5, &SavedBoolTest))
		Warn("Unable to toggle bool at this test int index");
	//print(itosGlobal(sArr2D[1][1]), 5000);
	//assert(false && "hello");

}
void Option_EnumTest()
{

}
void Option_FlyMod()
{
	if (GetCurrentItem()->Selection.Value.Int)
		bit_set(&MenuLoopedBitset, MB_FlyMod);
	else
		bit_reset(&MenuLoopedBitset, MB_FlyMod);

}
void Option_GodMode()
{
	if (GetCurrentItem()->Selection.Value.Int)
		bit_set(&MenuLoopedBitset, MB_GodMode);
	else
	{
		Ped MyPed = player_ped_id();
		bit_reset(&MenuLoopedBitset, MB_GodMode);
		set_player_invincible(player_id(), false);
		set_ped_can_be_knocked_off_vehicle(MyPed, 0);
		set_ped_can_be_dragged_out(MyPed, true);
		set_ped_can_ragdoll(MyPed, true);
		set_ped_can_ragdoll_from_player_impact(MyPed, true);
		set_ped_config_flag(MyPed, 32, true);
	}

}
void Option_VehicleHelper()
{
	if (GetCurrentItem()->Selection.Value.Int)
		bit_set(&MenuLoopedBitset, MB_VehicleHelper);
	else
	{
		bit_reset(&MenuLoopedBitset, MB_VehicleHelper);
		Vehicle MyVeh = GetCurrentVehicle();
		if (MyVeh)
		{
			set_vehicle_can_be_visibly_damaged(MyVeh, true);
			set_entity_can_be_damaged(MyVeh, true);
			set_entity_invincible(MyVeh, false);
			set_vehicle_can_break(MyVeh, true);
			set_vehicle_engine_can_degrade(MyVeh, true);
		}

	}

}
void Option_NeverWanted()
{
	if (GetCurrentItem()->Selection.Value.Int)
	{
		bit_set(&MenuLoopedBitset, MB_NeverWanted);
		clear_player_wanted_level(player_id());
		set_max_wanted_level(0);
	}
	else
	{
		bit_reset(&MenuLoopedBitset, MB_NeverWanted);
		set_max_wanted_level(5);
	}
}
void Option_SpawnVehicle()
{
	StartAsynchronousFunction(Async(Async_SpawnVehicle), 1, 150, AsyncParam(GetCurrentItem()->Selection.Value.Int));
}
void Option_SetVehicleType()
{
	const int Type = GetCurrentItem()->Selection.Value.Int;
	int* MetaAddress = GetVehicleMetaAddress(SavedMenuParam[0]);

	if (MetaAddress == nullptr)
	{
		Notify("Vehicle was not found");
		return;
	}
	//CError:	On PC VMI_VehicleType and VMI_HandlingId are 4 bytes in memory yet we are setting 8 bytes
	*Add64P(MetaAddress, VMI_VehicleType, 0) = Type;
	
	switch (Type)
	{
		case VEHICLE_TYPE_CAR:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = HANDLING_INDEX_BUFFALO;
		break;
		case VEHICLE_TYPE_PLANE:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = HANDLING_INDEX_LAZER;
		break;
		case VEHICLE_TYPE_QUADBIKE:
		#if PLATFORM == PLATFORM_PC
		case VEHICLE_TYPE_AMPHIBIOUS_AUTOMOBILE:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = 397;//technical aqua
		break;
		case VEHICLE_TYPE_AMPHIBIOUS_QUADBIKE:
		//*Add64P(MetaAddress, VMI_HandlingId, 0) = 398;//blazer aqua
		break;
		#endif
		case VEHICLE_TYPE_HELI:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = HANDLING_INDEX_ANNIHL;
		break;
		case VEHICLE_TYPE_BLIMP:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = HANDLING_INDEX_BLIMP;
		break;
		case VEHICLE_TYPE_BIKE:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = HANDLING_INDEX_RUFFIAN;
		break;
		case VEHICLE_TYPE_BICYCLE:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = HANDLING_INDEX_BMX;
		break;
		case VEHICLE_TYPE_BOAT:
		*Add64P(MetaAddress, VMI_HandlingId, 0) = HANDLING_INDEX_DINGHY;
		break;
	}
	Notify("Type has been set");
}
#pragma endregion

#pragma region Menus
void Menu__LargeSubmenuTest();
void Menu__PlayerList_Options()
{
	if (WasLastMenuDirectionForward())
	{
		SelectedPlayerId = GetLastDynamicId();
	}
	SetHeaderForwarded();
	AddItemMenu("Player Options", Menu__LargeSubmenuTest);
	AddItemMenu("Weapon Options", Menu__LargeSubmenuTest);
	AddItemMenu("Vehicle Options", Menu__LargeSubmenuTest);
	AddItemMenu("Teleport Options", Menu__LargeSubmenuTest);
	AddItemMenu("Attachable Options", Menu__LargeSubmenuTest);
}
bool DynamicChecker__PlayerList(int Id)
{
	//return IsPlayerInGame(Id);
	if (timera() < 10000)
	{
		return true;
	}
	else if (timera() < 20000)
	{
		switch (Id)
		{
			case 0:
			case 4:
			case 14:
			case 25:
			case 31:
			return false;
		}
		return true;
	}
	else if (timera() < 30000)
	{
		switch (Id)
		{
			case 0:
			case 1:
			case 2:
			case 4:
			case 5:
			case 6:
			case 14:
			case 16:
			case 20:
			case 25:
			case 31:
			return false;
		}
		return true;
	}
	return true;
}
void Menu__PlayerList()
{
	//savedcursorindex = id
	//savedstartindex = range
	//DynamicChecker[MaxMenuLevels]
	
	SetHeaderAdvanced("Player List", false, DynamicChecker__PlayerList);
	for (int i = 0; i < LobbySizeWithSpectators; i++)
	{
		if (DynamicChecker__PlayerList(i))
			AddItemPlayer(i, Option_Blank);
	}
	
	/*
	#pragma region net sim
	static int netsimstart = true;
	startnettime:
	if (netsimstart)
	{
		settimera(0);
		netsimstart = false;
	}
	if (timera() < 10000)
	{
		AddItemMenuDynamicAdvanced("player0", false, nullptr, false, false, true, 0, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player1", false, nullptr, false, false, true, 1, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player2", false, nullptr, false, false, true, 2, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player3", false, nullptr, false, false, true, 3, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player4", false, nullptr, false, false, true, 4, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player5", false, nullptr, false, false, true, 5, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player6", false, nullptr, false, false, true, 6, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player7", false, nullptr, false, false, true, 7, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player8", false, nullptr, false, false, true, 8, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player9", false, nullptr, false, false, true, 9, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player10", false, nullptr, false, false, true, 10, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player11", false, nullptr, false, false, true, 11, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player12", false, nullptr, false, false, true, 12, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player13", false, nullptr, false, false, true, 13, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player14", false, nullptr, false, false, true, 14, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player15", false, nullptr, false, false, true, 15, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player16", false, nullptr, false, false, true, 16, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player17", false, nullptr, false, false, true, 17, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player18", false, nullptr, false, false, true, 18, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player19", false, nullptr, false, false, true, 19, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player20", false, nullptr, false, false, true, 20, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player21", false, nullptr, false, false, true, 21, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player22", false, nullptr, false, false, true, 22, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player23", false, nullptr, false, false, true, 23, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player24", false, nullptr, false, false, true, 24, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player25", false, nullptr, false, false, true, 25, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player26", false, nullptr, false, false, true, 26, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player27", false, nullptr, false, false, true, 27, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player28", false, nullptr, false, false, true, 28, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player29", false, nullptr, false, false, true, 29, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player30", false, nullptr, false, false, true, 30, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player31", false, nullptr, false, false, true, 31, Menu__PlayerList_Options);
	}
	else if (timera() < 20000)
	{
		//AddItemMenuDynamicAdvanced("player0", false, nullptr, false, false, true, 0, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player1", false, nullptr, false, false, true, 1, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player2", false, nullptr, false, false, true, 2, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player3", false, nullptr, false, false, true, 3, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player4", false, nullptr, false, false, true, 4, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player5", false, nullptr, false, false, true, 5, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player6", false, nullptr, false, false, true, 6, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player7", false, nullptr, false, false, true, 7, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player8", false, nullptr, false, false, true, 8, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player9", false, nullptr, false, false, true, 9, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player10", false, nullptr, false, false, true, 10, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player11", false, nullptr, false, false, true, 11, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player12", false, nullptr, false, false, true, 12, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player13", false, nullptr, false, false, true, 13, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player14", false, nullptr, false, false, true, 14, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player15", false, nullptr, false, false, true, 15, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player16", false, nullptr, false, false, true, 16, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player17", false, nullptr, false, false, true, 17, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player18", false, nullptr, false, false, true, 18, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player19", false, nullptr, false, false, true, 19, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player20", false, nullptr, false, false, true, 20, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player21", false, nullptr, false, false, true, 21, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player22", false, nullptr, false, false, true, 22, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player23", false, nullptr, false, false, true, 23, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player24", false, nullptr, false, false, true, 24, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player25", false, nullptr, false, false, true, 25, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player26", false, nullptr, false, false, true, 26, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player27", false, nullptr, false, false, true, 27, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player28", false, nullptr, false, false, true, 28, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player29", false, nullptr, false, false, true, 29, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player30", false, nullptr, false, false, true, 30, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player31", false, nullptr, false, false, true, 31, Menu__PlayerList_Options);
	}
	else if (timera() < 30000)
	{
		//AddItemMenuDynamicAdvanced("player0", false, nullptr, false, false, true, 0, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player1", false, nullptr, false, false, true, 1, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player2", false, nullptr, false, false, true, 2, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player3", false, nullptr, false, false, true, 3, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player4", false, nullptr, false, false, true, 4, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player5", false, nullptr, false, false, true, 5, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player6", false, nullptr, false, false, true, 6, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player7", false, nullptr, false, false, true, 7, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player8", false, nullptr, false, false, true, 8, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player9", false, nullptr, false, false, true, 9, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player10", false, nullptr, false, false, true, 10, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player11", false, nullptr, false, false, true, 11, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player12", false, nullptr, false, false, true, 12, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player13", false, nullptr, false, false, true, 13, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player14", false, nullptr, false, false, true, 14, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player15", false, nullptr, false, false, true, 15, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player16", false, nullptr, false, false, true, 16, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player17", false, nullptr, false, false, true, 17, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player18", false, nullptr, false, false, true, 18, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player19", false, nullptr, false, false, true, 19, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player20", false, nullptr, false, false, true, 20, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player21", false, nullptr, false, false, true, 21, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player22", false, nullptr, false, false, true, 22, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player23", false, nullptr, false, false, true, 23, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player24", false, nullptr, false, false, true, 24, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player25", false, nullptr, false, false, true, 25, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player26", false, nullptr, false, false, true, 26, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player27", false, nullptr, false, false, true, 27, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player28", false, nullptr, false, false, true, 28, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player29", false, nullptr, false, false, true, 29, Menu__PlayerList_Options);
		AddItemMenuDynamicAdvanced("player30", false, nullptr, false, false, true, 30, Menu__PlayerList_Options);
		//AddItemMenuDynamicAdvanced("player31", false, nullptr, false, false, true, 31, Menu__PlayerList_Options);
	}
	//else if (timera() < 40000)
	//{
	//}
	else
	{
		netsimstart = true;
		goto startnettime;
	}
	#pragma endregion
	*/
	
if(!GetCurrentItemCount())
		SetCurrentMenuInvalid(true, "No active players in session");
}
void Menu__LargeSubmenuTest()
{
	SetHeader("Large Submenu Test");
	AddItem("Item1", Option_Blank);
	AddItem("Item2", Option_Blank);
	AddItem("Item3", Option_Blank);
	AddItem("Item4", Option_Blank);
	AddItem("Item5", Option_Blank);
	AddItem("Item6", Option_Blank);
	AddItem("Item7", Option_Blank);
	AddItem("Item8", Option_Blank);
	AddItem("Item9", Option_Blank);
	AddItemIntAdvanced("Item10", false, nullptr, nullptr, true, false, false, 0, 50, 0, 1, Option_Blank, nullptr);
	AddItemFloatAdvanced("Item11", false, nullptr, nullptr, true, false, false, 0, 10, 0, 1, Option_Blank, nullptr);
	AddItemBoolAdvanced("Item12", false, nullptr, nullptr, true, false, false, Option_Blank, nullptr);
	AddItemEnumAdvanced("Item13", false, nullptr, nullptr, true, false, false, 0, 50, 0, 1, Option_Blank, Parser_EnumTest, nullptr);
	AddItemAdvanced("BJ_JUMP_06", true, "Must Come Down.~n~(Gxt Test)", nullptr, true, false, Option_Blank, nullptr);
	AddItemAdvanced("Item15", false, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", nullptr, false, false, Option_Blank, nullptr);
	AddItemAdvanced("Item16", false, nullptr, nullptr, false, false, Option_Blank, nullptr);
	AddItem("Item17", Option_Blank);
	AddItem("Item18", Option_Blank);
	AddItem("Item19", Option_Blank);
	AddItem("Item20", Option_Blank);
	AddItem("Item21", Option_Blank);
	AddItem("Item22", Option_Blank);
	AddItem("Item23", Option_Blank);
	AddItem("Item24", Option_Blank);
	AddItem("Item25", Option_Blank);
	AddItem("Item26", Option_Blank);
	AddItem("Item27", Option_Blank);
	AddItem("Item28", Option_Blank);
	AddItem("Item29", Option_Blank);
	AddItem("Item30", Option_Blank);
	AddItem("Item31", Option_Blank);
	AddItem("Item32", Option_Blank);
	AddItem("Item33", Option_Blank);
	AddItem("Item34", Option_Blank);
	AddItem("Item35", Option_Blank);
	AddItem("Item36", Option_Blank);
	AddItem("Item37", Option_Blank);
	AddItem("Item38", Option_Blank);
	AddItem("Item39", Option_Blank);
	AddItem("Item40", Option_Blank);
	AddItem("Item41", Option_Blank);
	AddItem("Item42", Option_Blank);
	AddItem("Item43", Option_Blank);
	AddItem("Item44", Option_Blank);
	AddItem("Item45", Option_Blank);
	AddItem("Item46", Option_Blank);
	AddItem("Item47", Option_Blank);
	AddItem("Item48", Option_Blank);
	AddItem("Item49", Option_Blank);
	AddItem("Item50", Option_Blank);
}
void Menu__PlayerOptions()
{
	SetHeader("Player Options");
	AddItemBoolAdvanced("God Mode", false, "Makes player invincible.", nullptr, false, false, bit_test(MenuLoopedBitset, MB_GodMode), Option_GodMode, nullptr);
	AddItemBoolAdvanced("Never Wanted", false, "Disables police.", nullptr, false, false, bit_test(MenuLoopedBitset, MB_NeverWanted), Option_NeverWanted, nullptr);

}

#pragma region VehicleList
void Menu__VehicleList_Options_ChangeType()
{
	SetHeader("Change Type");
	AddItemWithParam("Car", VEHICLE_TYPE_CAR, Option_SetVehicleType);
	AddItemWithParam("Plane", VEHICLE_TYPE_PLANE, Option_SetVehicleType);
	AddItemWithParam("Quadbike", VEHICLE_TYPE_QUADBIKE, Option_SetVehicleType);
	#if PLATFORM == PLATFORM_PC
	AddItemWithParam("Amphibious Automobile", VEHICLE_TYPE_AMPHIBIOUS_AUTOMOBILE, Option_SetVehicleType);
	AddItemWithParam("Amphibious Quadbike", VEHICLE_TYPE_AMPHIBIOUS_QUADBIKE, Option_SetVehicleType);
	#endif
	AddItemWithParam("Helicopter", VEHICLE_TYPE_HELI, Option_SetVehicleType);
	AddItemWithParam("Blimp", VEHICLE_TYPE_BLIMP, Option_SetVehicleType);
	AddItemWithParamAdvanced("Bike", false, "This type is unstable on most vehicles", nullptr, false, true, VEHICLE_TYPE_BIKE, Option_SetVehicleType, nullptr);
	AddItemWithParamAdvanced("Bicycle", false, "This type is unstable on most vehicles", nullptr, false, true, VEHICLE_TYPE_BICYCLE, Option_SetVehicleType, nullptr);
	AddItemWithParamAdvanced("Boat", false, "This type is unstable on most vehicles", nullptr, false, true, VEHICLE_TYPE_BOAT, Option_SetVehicleType, nullptr);

}

void Menu__VehicleList_Options()
{
	if (WasLastMenuDirectionForward())
		SavedMenuParam[0] = GetCurrentItemFromLastMenu()->Selection.Value.Int;

	SetHeaderForwarded();
	AddItemWithParam("Spawn Vehicle", SavedMenuParam[0], Option_SpawnVehicle);
	AddItemMenu("Change Type", Menu__VehicleList_Options_ChangeType);
}
void Menu__VehicleList_Sports()
{
	SetHeader("Sports");
	AddItemVehicle(hashof("ninef"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ninef2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("banshee"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("buffalo"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("buffalo2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("carbonizzare"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("comet2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("coquette"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("elegy2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("feltzer2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("fusilade"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("futo"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("khamelion"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("penumbra"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Rapid GT Cabrio", false, nullptr, false, false, true, hashof("rapidgt2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("schwarzer"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sultan"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("surano"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("jester"), Menu__VehicleList_Options);

	if (is_dlc_present(Update_mpBusiness))
		AddItemVehicle(hashof("alpha"), Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpBusiness2))
		AddItemVehicle(hashof("massacro"), Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpLTS))
		AddItemVehicle(hashof("furoregt"), Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpChristmas2))
	{
		AddItemVehicle(hashof("jester2"), Menu__VehicleList_Options);
		AddItemVehicle(hashof("massacro2"), Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpHeist))
	{
		AddItemVehicle(hashof("kuruma"), Menu__VehicleList_Options);
		AddItemVehicle(hashof("kuruma2"), Menu__VehicleList_Options);
	}
	
	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_BLISTA2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BLISTA3, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BUFFALO3, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_SCHAFTER3, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SCHAFTER4, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_VERLIERER2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_SEVEN70, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BESTIAGTS, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_LYNX, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_OMNIS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_TROPOS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_TAMPA2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpBiker))
	{
		AddItemVehicle(VEHICLE_RAPTOR, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_ELEGY, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SPECTER, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SPECTER2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_COMET3, Menu__VehicleList_Options);
	}

	#endif
	
}
void Menu__VehicleList_Super()
{
	SetHeader("Super");
	AddItemVehicle(hashof("bullet"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("cheetah"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("entityxf"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("infernus"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("adder"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("voltic"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("vacca"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("turismor"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("zentorno"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("osiris"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("t20"), Menu__VehicleList_Options);

	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpJanuary2016))
	{
		AddItemVehicle(VEHICLE_SULTANRS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BANSHEE2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_FMJ, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_PFISTER811, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_PROTOTIPO, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_REAPER, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_TYRUS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SHEAVA, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_LE7B, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_TEMPESTA, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_ITALIGTB, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_ITALIGTB2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_NERO, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_NERO2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_VOLTIC2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_PENETRATOR, Menu__VehicleList_Options);
	}

	#endif

}
void Menu__VehicleList_Coupes()
{
	SetHeader("Coupes");
	AddItemVehicle(hashof("cogcabrio"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("exemplar"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("f620"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("felon"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("felon2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("Jackal"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("oracle"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("oracle2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sentinel"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sentinel2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("zion"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("zion2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("windsor"), Menu__VehicleList_Options);


	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_WINDSOR2, Menu__VehicleList_Options);
	}
	#endif

}
void Menu__VehicleList_Compacts()
{
	SetHeader("Compacts");
	AddItemVehicle(hashof("blista"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dilettante"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Dilettante (Merryweather)", false, nullptr, false, false, true, hashof("dilettante2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("issi2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("prairie"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("rhapsody"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("panto"), Menu__VehicleList_Options);

	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_BRIOSO, Menu__VehicleList_Options);
	}
	#endif

}
void Menu__VehicleList_Sedans()
{
	SetHeader("Sedans");

	AddItemVehicle(hashof("asea"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Asea (Snowy)", false, nullptr, false, false, true, hashof("asea2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("asterope"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("emperor"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Emperor (Rusty)", false, nullptr, false, false, true, hashof("emperor2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Emperor (Snowy)", false, nullptr, false, false, true, hashof("emperor3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("fugitive"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ingot"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("intruder"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("premier"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("primo"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("regina"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("romero"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("schafter2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("stanier"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("stratum"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("stretch"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("superd"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("surge"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tailgater"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("washington"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("warrener"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("glendale"), Menu__VehicleList_Options);


	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpLowrider))
	{
		AddItemVehicle(VEHICLE_PRIMO2, Menu__VehicleList_Options);
	}

	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_LIMO2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SCHAFTER5, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SCHAFTER6, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_COG55, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_COG552, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_COGNOSCENTI, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_COGNOSCENTI2, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_SportsClassic()
{
	SetHeader("Sports Classics");
	AddItemVehicle(hashof("jb700"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("manana"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("monroe"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("peyote"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("stinger"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("stingergt"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tornado"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tornado Cabrio", false, nullptr, false, false, true, hashof("tornado2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tornado (Rusty)", false, nullptr, false, false, true, hashof("tornado3"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tornado (Guitar)", false, nullptr, false, false, true, hashof("tornado4"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ztype"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("btype"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("pigalle"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("coquette2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("casco"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("feltzer3"), Menu__VehicleList_Options);

	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpHalloween))
		AddItemVehicle(VEHICLE_BTYPE2, Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpApartment))
		AddItemVehicle(VEHICLE_MAMBA, Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpValentines2))
		AddItemVehicle(VEHICLE_BTYPE3, Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpLowrider2))
		AddItemVehicle(VEHICLE_TORNADO5, Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpBiker))
		AddItemVehicle(VEHICLE_TORNADO6, Menu__VehicleList_Options);

	#endif
}
void Menu__VehicleList_Muscle()
{
	SetHeader("Muscle");
	AddItemVehicle(hashof("buccaneer"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("hotknife"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dominator"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("gauntlet"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("phoenix"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("picador"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ratloader"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ruiner"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sabregt"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("voodoo2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("vigero"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("blade"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ratloader2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("slamvan"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("slamvan2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("virgo"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("chino"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("coquette3"), Menu__VehicleList_Options);


	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_DUKES, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_DUKES2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_DOMINATOR2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_GAUNTLET2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_STALION, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_STALION2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpLowrider))
	{
		AddItemVehicle(VEHICLE_MOONBEAM, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_MOONBEAM2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_FACTION, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_FACTION2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_CHINO2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BUCCANEER2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_VOODOO, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpHalloween))
	{
		AddItemVehicle(VEHICLE_LURCHER, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_NIGHTSHADE, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpXmas))
	{
		AddItemVehicle(VEHICLE_TAMPA, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpLowrider2))
	{
		AddItemVehicle(VEHICLE_FACTION3, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SABREGT2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SLAMVAN3, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_VIRGO2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_VIRGO3, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_RUINER2, Menu__VehicleList_Options);
		AddItemMenuWithParamAdvanced("Ruiner (Destroyed)", false, nullptr, false, false, true, VEHICLE_RUINER3, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Suv()
{
	SetHeader("SUVs");
	AddItemVehicle(hashof("baller2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Baller (Old)", false, nullptr, false, false, true, hashof("baller"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("bjxl"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("cavalcade2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Cavalcade (Old)", false, nullptr, false, false, true, hashof("cavalcade"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("gresley"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dubsta"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Dubsta (Blacked Out)", false, nullptr, false, false, true, hashof("dubsta2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("fq2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("granger"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("habanero"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("landstalker"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("mesa"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Mesa (Snowy)", false, nullptr, false, false, true, hashof("mesa2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("patriot"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("radi"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("rocoto"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("seminole"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("serrano"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("huntley"), Menu__VehicleList_Options);

	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_BALLER3, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BALLER4, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BALLER5, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BALLER6, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_XLS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_XLS2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_CONTENDER, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Van()
{
	SetHeader("Vans");
	AddItemVehicle(hashof("bison"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Bison (Construction)", false, nullptr, false, false, true, hashof("bison2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Bison (Landscapeing)", false, nullptr, false, false, true, hashof("bison3"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Boxville (Water&Power)", false, nullptr, false, false, true, hashof("boxville"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Boxville (Postal)", false, nullptr, false, false, true, hashof("boxville2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Boxville (Humane)", false, nullptr, false, false, true, hashof("boxville3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("bobcatxl"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("burrito3"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Burrito (Multi Livery)", false, nullptr, false, false, true, hashof("burrito"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Burrito (Bugstars)", false, nullptr, false, false, true, hashof("burrito2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Burrito (Construction)", false, nullptr, false, false, true, hashof("burrito4"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Burrito (Snowy)", false, nullptr, false, false, true, hashof("burrito5"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("gburrito"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("camper"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("journey"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("minivan"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("pony"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Weed Van", false, nullptr, false, false, true, hashof("pony2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Rumpo (Weazel News)", false, nullptr, false, false, true, hashof("rumpo"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Rumpo (Deludamol)", false, nullptr, false, false, true, hashof("rumpo2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("speedo"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("speedo2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("surfer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Surfer (Rusty)", false, nullptr, false, false, true, hashof("surfer2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("taco"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("youga"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("paradise"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Boxville (Post OP)", false, nullptr, false, false, true, hashof("boxville4"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Gang Burrito (No Livery)", false, nullptr, false, false, true, hashof("gburrito2"), Menu__VehicleList_Options);

	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpLowrider2))
	{
		AddItemVehicle(VEHICLE_MINIVAN2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_RUMPO3, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpBiker))
		AddItemVehicle(VEHICLE_YOUGA2, Menu__VehicleList_Options);
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_BOXVILLE5, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Offroad()
{
	SetHeader("Off-Road");
	AddItemVehicle(hashof("bfinjection"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("blazer"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("blazer2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("blazer3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("bodhi2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dune"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dune2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dloader"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Mesa (Merryweather)", false, nullptr, false, false, true, hashof("mesa3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("rancherxl"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Rancher XL (Snowy)", false, nullptr, false, false, true, hashof("rancherxl2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("rebel2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Rebel (Rusty)", false, nullptr, false, false, true, hashof("rebel"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sandking"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sandking2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("bifta"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("kalahari"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dubsta3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("monster"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("insurgent"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Insurgent Transport", false, nullptr, false, false, true, hashof("insurgent2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("technical"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("brawler"), Menu__VehicleList_Options);


	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_MARSHALL, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_TROPHYTRUCK, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_TROPHYTRUCK2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpBiker))
	{
		AddItemVehicle(VEHICLE_BLAZER4, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_BLAZER5, Menu__VehicleList_Options);
		AddItemMenuWithParamAdvanced("Ramp Buggy Custom", false, nullptr, false, false, true, VEHICLE_DUNE4, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_DUNE5, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_TECHNICAL2, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Commercial()
{
	SetHeader("Commercial");
	AddItemVehicle(hashof("benson"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("biff"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("hauler"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("mule"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Mule (Drop Down Trunk)", false, nullptr, false, false, true, hashof("mule2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("packer"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("phantom"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("pounder"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("stockade"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Stockade (Snowy)", false, nullptr, false, false, true, hashof("stockade3"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Mule (No Livery)", false, nullptr, false, false, true, hashof("mule3"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_PHANTOM2, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Service()
{
	SetHeader("Service");
	AddItemVehicle(hashof("bus"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("coach"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("airbus"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("rentalbus"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("taxi"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("trash"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tourbus"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Trashmaster (Rusty)", false, nullptr, false, false, true, hashof("trash2"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_BRICKADE, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_RALLYTRUCK, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_WASTELANDER, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Utility()
{
	SetHeader("Utility");
	AddItemVehicle(hashof("airtug"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("caddy"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Caddy (Old)", false, nullptr, false, false, true, hashof("caddy2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("docktug"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("forklift"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("mower"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ripley"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sadler"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Sadler (Snowy)", false, nullptr, false, false, true, hashof("sadler2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("scrap"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tractor2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tractor (Rusty)", false, nullptr, false, false, true, hashof("tractor"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tractor (Snowy)", false, nullptr, false, false, true, hashof("tractor3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("towtruck"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Towtruck (Small)", false, nullptr, false, false, true, hashof("towtruck2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Basket Truck", false, nullptr, false, false, true, hashof("utillitruck"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("utillitruck2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Utility Pick-up Truck", false, nullptr, false, false, true, hashof("utillitruck3"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC

	#endif
}
void Menu__VehicleList_Industrial()
{
	SetHeader("Industrial");
	AddItemVehicle(hashof("bulldozer"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("cutter"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dump"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("rubble"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("flatbed"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("handler"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("mixer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Mixer (Wheels On Back)", false, nullptr, false, false, true, hashof("mixer2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tipper (6-Wheeler)", false, nullptr, false, false, true, hashof("tiptruck"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tipper (10-Wheeler)", false, nullptr, false, false, true, hashof("tiptruck2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("guardian"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC

	#endif
}
void Menu__VehicleList_Emergency()
{
	SetHeader("Emergency");
	AddItemVehicle(hashof("ambulance"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("policet"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("FIB Buffalo", false, nullptr, false, false, true, hashof("fbi"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("FIB Granger", false, nullptr, false, false, true, hashof("fbi2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("firetruk"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("lguard"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("pbus"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Police Stanier", false, nullptr, false, false, true, hashof("police"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Police Buffalo", false, nullptr, false, false, true, hashof("police2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Police Interceptor", false, nullptr, false, false, true, hashof("police3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("police4"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("policeold1"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("policeold2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("pranger"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("riot"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sheriff"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sheriff2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("policeb"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC

	#endif
}
void Menu__VehicleList_Military()
{
	SetHeader("Military");
	AddItemVehicle(hashof("barracks"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("barracks2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("crusader"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("rhino"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Barracks (Dark Camo)", false, nullptr, false, false, true, hashof("barracks3"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC

	#endif
}
void Menu__VehicleList_Motorcycle()
{
	SetHeader("Motorcycles");
	AddItemVehicle(hashof("sanchez"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sanchez2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("akuma"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("carbonrs"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("bagger"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("bati"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("bati2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("ruffian"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("daemon"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("double"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("pcj"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("vader"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("faggio2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("hexer"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("nemesis"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("thrust"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("sovereign"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("innovation"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("hakuchou"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("enduro"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("lectro"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("vindicator"), Menu__VehicleList_Options);

	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_GARGOYLE, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_CLIFFHANGER, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BF400, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpBiker))
	{
		AddItemVehicle(VEHICLE_FAGGIO3, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_FAGGIO, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_VORTEX, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_AVARUS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SANCTUS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_HAKUCHOU2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_NIGHTBLADE, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_CHIMERA, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_ESSKEY, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_WOLFSBANE, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_ZOMBIEA, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_ZOMBIEB, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_DEFILER, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_DAEMON2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_RATBIKE, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SHOTARO, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_MANCHEZ, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_DIABLOUS, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_DIABLOUS2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_FCR, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_FCR2, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Bicycle()
{
	SetHeader("Cycles");
	AddItemVehicle(hashof("scorcher"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tribike"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tribike2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tribike3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("fixter"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("cruiser"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("BMX"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC

	#endif
}
void Menu__VehicleList_Plane()
{
	SetHeader("Planes");
	AddItemVehicle(hashof("blimp"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("cuban800"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("duster"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("stunt"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("mammatus"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("jet"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("shamal"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("luxor"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("titan"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("lazer"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("cargoplane"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("velum"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("vestra"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("besra"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("miljet"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("velum2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("hydra"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("luxor2"), Menu__VehicleList_Options);


	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_DODO, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_BLIMP2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_NIMBUS, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Helicopter()
{
	SetHeader("Helicopters");
	AddItemVehicle(hashof("annihilator"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("buzzard"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("buzzard2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("cargobob"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Medical Cargobob", false, nullptr, false, false, true, hashof("cargobob2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Trevor's Cargobob", false, nullptr, false, false, true, hashof("cargobob3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("skylift"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("polmav"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("maverick"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("frogger"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Trevor's Frogger", false, nullptr, false, false, true, hashof("frogger2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("swift"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("savage"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("valkyrie"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("swift2"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemMenuWithParamAdvanced("Cargobob 2-Seater", false, nullptr, false, false, true, VEHICLE_CARGOBOB4, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SUPERVOLITO, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SUPERVOLITO2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_VALKYRIE2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_VOLATUS, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Boat()
{
	SetHeader("Boats");
	AddItemVehicle(hashof("squalo"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("marquis"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("dinghy"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Dinghy 2-Seater", false, nullptr, false, false, true, hashof("dinghy2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("jetmax"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("predator"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("tropic"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("seashark"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Seashark Lifeguard", false, nullptr, false, false, true, hashof("seashark2"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("submersible"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("suntrap"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("speeder"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Dinghy (Heist)", false, nullptr, false, false, true, hashof("dinghy3"), Menu__VehicleList_Options);
	AddItemVehicle(hashof("toro"), Menu__VehicleList_Options);


	#if PLATFORM == PLATFORM_PC
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_SUBMERSIBLE2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_TORO2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SEASHARK3, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_DINGHY4, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_TROPIC2, Menu__VehicleList_Options);
		AddItemVehicle(VEHICLE_SPEEDER2, Menu__VehicleList_Options);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_TUG, Menu__VehicleList_Options);
	}
	#endif
}
void Menu__VehicleList_Trailer()
{
	SetHeader("Trailers");
	AddItemVehicle(hashof("boattrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Army Tanker", false, nullptr, false, false, true, hashof("armytanker"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Army Flatbed", false, nullptr, false, false, true, hashof("armytrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Army Flatbed With Cutter", false, nullptr, false, false, true, hashof("armytrailer2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Freight Train Flatbed", false, nullptr, false, false, true, hashof("freighttrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Mobile Home", false, nullptr, false, false, true, hashof("proptrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Grain Trailer", false, nullptr, false, false, true, hashof("graintrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Hay Bale Trailer", false, nullptr, false, false, true, hashof("baletrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Shipping Container Trailer", false, nullptr, false, false, true, hashof("docktrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Metal/Tarp Covered Trailer", false, nullptr, false, false, true, hashof("trailers"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Misc Livery Trailer", false, nullptr, false, false, true, hashof("trailers2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Big Goods Trailer", false, nullptr, false, false, true, hashof("trailers3"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Fame or Shame Trailer", false, nullptr, false, false, true, hashof("tvtrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Farm Cultivator", false, nullptr, false, false, true, hashof("raketrailer"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tanker", false, nullptr, false, false, true, hashof("tanker"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Log Trailer", false, nullptr, false, false, true, hashof("trailerlogs"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Empty Car Carrier Trailer", false, nullptr, false, false, true, hashof("tr2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Marquis Trailer", false, nullptr, false, false, true, hashof("tr3"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Super Car Carrier Trailer", false, nullptr, false, false, true, hashof("tr4"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Flatbed", false, nullptr, false, false, true, hashof("trflat"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Small Construction Trailer", false, nullptr, false, false, true, hashof("trailersmall"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Tanker (No Livery)", false, nullptr, false, false, true, hashof("tanker2"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC

	#endif
}
void Menu__VehicleList_Rail()
{
	SetHeader("Trains");
	AddItemVehicle(hashof("cablecar"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Freight Train", false, nullptr, false, false, true, hashof("freight"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Train Well Car", false, nullptr, false, false, true, hashof("freightcar"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Train Container", false, nullptr, false, false, true, hashof("freightcont1"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Train Container (livery)", false, nullptr, false, false, true, hashof("freightcont2"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Train Boxcar", false, nullptr, false, false, true, hashof("freightgrain"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Train Fuel Tank Car", false, nullptr, false, false, true, hashof("tankercar"), Menu__VehicleList_Options);
	AddItemMenuWithParamAdvanced("Metro Train", false, nullptr, false, false, true, hashof("metrotrain"), Menu__VehicleList_Options);
	#if PLATFORM == PLATFORM_PC

	#endif
}

void Menu__VehicleList()
{
	SetHeader("Vehicle List");
	AddItemMenu("Sports", Menu__VehicleList_Sports);
	AddItemMenu("Super", Menu__VehicleList_Super);
	AddItemMenu("Coupes", Menu__VehicleList_Coupes);
	AddItemMenu("Compacts", Menu__VehicleList_Compacts);
	AddItemMenu("Sedans", Menu__VehicleList_Sedans);
	AddItemMenu("Sports Classics", Menu__VehicleList_SportsClassic);
	AddItemMenu("Muscle", Menu__VehicleList_Muscle);
	AddItemMenu("SUVs", Menu__VehicleList_Suv);
	AddItemMenu("Vans", Menu__VehicleList_Van);
	AddItemMenu("Off-Road", Menu__VehicleList_Offroad);
	AddItemMenu("Commercial", Menu__VehicleList_Commercial);
	AddItemMenu("Service", Menu__VehicleList_Service);
	AddItemMenu("Utility", Menu__VehicleList_Utility);
	AddItemMenu("Industrial", Menu__VehicleList_Industrial);
	AddItemMenu("Emergency", Menu__VehicleList_Emergency);
	AddItemMenu("Military", Menu__VehicleList_Military);
	AddItemMenu("Motorcycles", Menu__VehicleList_Motorcycle);
	AddItemMenu("Cycles", Menu__VehicleList_Bicycle);
	AddItemMenu("Planes", Menu__VehicleList_Plane);
	AddItemMenu("Helicopters", Menu__VehicleList_Helicopter);
	AddItemMenu("Boats", Menu__VehicleList_Boat);
	AddItemMenu("Trailers", Menu__VehicleList_Trailer);
	AddItemMenu("Trains", Menu__VehicleList_Rail);
}
#pragma endregion

void Menu__VehicleOptions()
{
	SetHeader("Vehicle Options");
	AddItemMenu("Vehicle List", Menu__VehicleList);
	AddItemBoolAdvanced("Vehicle Helper", false, "Makes vehicle invincible.", nullptr, false, false, bit_test(MenuLoopedBitset, MB_VehicleHelper), Option_VehicleHelper, nullptr);
}
void Menu__MiscOptions()
{
	SetHeader("Misc Options");
	AddItemBoolAdvanced("Fly Mod", false, "Hold X and press Left Stick to use Fly Mod.", nullptr, false, false, bit_test(MenuLoopedBitset, MB_FlyMod), Option_FlyMod, nullptr);
}
void Menu__DebugOptions()
{
	SetHeader("Debug Options");
	AddItemAdvanced("Vehicle Spawn Test", false, "Spawns the adder.", nullptr, false, false, Option_DebugTest0, nullptr);
	AddItemAdvanced("Loading Off Test", false, "Turns loading icon off.", "test", false, false, Option_LoadingOffTest, Option_Blank);
	AddItemInt("Ui Test Precision", true, 0, 4, FloatToPrecision(SavedTestCoordPrecision), Option_UiTestPrecision);
	AddItemFloat("Ui Test Coord X", true, 0, 10, DEBUG__GetContainer()->UiTestCoords.x, SavedTestCoordPrecision, Option_TestUiCoordX);
	AddItemFloat("Ui Test Coord Y", true, 0, 10, DEBUG__GetContainer()->UiTestCoords.y, SavedTestCoordPrecision, Option_TestUiCoordY);
	AddItemInt("Ui Test Int", true, -100, 1000, DEBUG__GetContainer()->TestInt, Option_TestInt);
	AddItemBool("Bool Test", SavedBoolTest, Option_BoolTest);
	AddItemEnum("Enum Test", false, 0, 10, 0, Option_EnumTest, Parser_EnumTest);
	AddItemIntBool("Int Bool Test", 0, 10, 0, 0, Option_Blank);
	AddItemEnumBool("Enum Bool Test", 0, 10, 0, 0, Option_Blank, Parser_EnumTest);
	AddItemFloatBool("Float Bool Test", 0, 10, 0, 1.0f, 0, Option_Blank);
	AddItemMenu("Large Submenu Test", Menu__LargeSubmenuTest);

}
inline void MainMenu()
{
	SetHeader("Main Menu");

	AddItemMenu("Player List", Menu__PlayerList);
	AddItemMenu("Player Options", Menu__PlayerOptions);
	AddItemMenu("Vehicle Options", Menu__VehicleOptions);
	AddItemMenu("Misc Options", Menu__MiscOptions);
	AddItemMenu("Debug Options", Menu__DebugOptions);

}
#pragma endregion

#pragma region LoopedOptions
void FlyMod(Player CurrentPlayerPed)
{
	disable_control_action(2, INPUT_VEH_LOOK_BEHIND, true);
	disable_control_action(2, INPUT_LOOK_BEHIND, true);
	set_input_exclusive(2, INPUT_FRONTEND_X);
	set_input_exclusive(2, INPUT_FRONTEND_LS);
	Entity CurrentEntity = GetCurrentVehicle();
	if (!CurrentEntity)
	{
		CurrentEntity = CurrentPlayerPed;
		if (get_ped_stealth_movement(CurrentPlayerPed))
			set_ped_stealth_movement(CurrentPlayerPed, 0, 0);
		if (get_ped_combat_movement(CurrentPlayerPed))
			set_ped_combat_movement(CurrentPlayerPed, 0);
	}

	float Speed = is_control_pressed(2, INPUT_SCRIPT_RB) ? 5.0f : 1.0f;
	vector3 CamRotation = get_gameplay_cam_rot(2);

	set_entity_heading(CurrentEntity, CamRotation.z);

	float SavedPitch = get_gameplay_cam_relative_pitch();
	set_gameplay_cam_relative_heading(0.0f);
	set_gameplay_cam_relative_pitch(SavedPitch, 0.0f);

	freeze_entity_position(CurrentEntity, true);

	if (!(get_control_normal(2, INPUT_SCRIPT_LEFT_AXIS_X) == 0.0f &&
		get_control_normal(2, INPUT_SCRIPT_LEFT_AXIS_Y) == 0.0f &&
		get_control_normal(2, INPUT_FRONTEND_LT) == 0.0f &&
		get_control_normal(2, INPUT_FRONTEND_RT) == 0.0f))
	{
		vector3 PlaceToBe = {
			get_control_normal(2, INPUT_SCRIPT_LEFT_AXIS_X) * Speed,
			-get_control_normal(2, INPUT_SCRIPT_LEFT_AXIS_Y) * Speed,
			-get_control_normal(2, INPUT_FRONTEND_LT) * Speed
			+get_control_normal(2, INPUT_FRONTEND_RT) * Speed
		};

		set_entity_coords_no_offset(CurrentEntity, get_offset_from_entity_in_world_coords(CurrentEntity, PlaceToBe), false, false, false);

	}
}
void FlyModController(Player CurrentPlayerPed)
{
	if (is_control_pressed(2, INPUT_FRONTEND_X) && is_control_just_pressed(2, INPUT_FRONTEND_LS))
	{
		disable_control_action(2, INPUT_VEH_LOOK_BEHIND, true);
		disable_control_action(2, INPUT_LOOK_BEHIND, true);
		set_input_exclusive(2, INPUT_FRONTEND_X);
		set_input_exclusive(2, INPUT_FRONTEND_LS);

		bit_flip(&MenuLoopedBitset, MB_FlyModToggle);
		Notify(strcatGlobal("Fly Mod ", bit_test(MenuLoopedBitset, MB_FlyModToggle) ? "On" : "Off"));

		if (!bit_test(MenuLoopedBitset, MB_FlyModToggle))
		{
			Vehicle CurrentVehicle = GetCurrentVehicle();
			Entity ToUnfreeze = CurrentVehicle ? CurrentVehicle : CurrentPlayerPed;

			freeze_entity_position(ToUnfreeze, false);
			apply_force_to_entity(ToUnfreeze, FT_MAX_FORCE_ROT, Vector3(0.0f, 0.0f, -0.1f), toVector3(0.0f), 0, true, false, false, false, true);

			if (get_ped_stealth_movement(CurrentPlayerPed))
				set_ped_stealth_movement(CurrentPlayerPed, 0, 0);
			if (get_ped_combat_movement(CurrentPlayerPed))
				set_ped_combat_movement(CurrentPlayerPed, 0);
		}
	}
	if (bit_test(MenuLoopedBitset, MB_FlyModToggle))
		FlyMod(CurrentPlayerPed);
}

inline void LoopedOptions()
{
	Player CurrentPlayerPed = player_ped_id();
	Vehicle CurrentVehicle = GetCurrentVehicle();

	if (bit_test(MenuLoopedBitset, MB_FlyMod) && !is_pause_menu_active())
		FlyModController(CurrentPlayerPed);
	if (bit_test(MenuLoopedBitset, MB_GodMode))
	{
		set_player_invincible(player_id(), true);
		set_ped_can_ragdoll(CurrentPlayerPed, false);
		set_ped_can_ragdoll_from_player_impact(CurrentPlayerPed, false);

		if (is_ped_in_any_vehicle(CurrentPlayerPed, false))
		{
			set_ped_can_be_knocked_off_vehicle(CurrentPlayerPed, 1);
			set_ped_can_be_dragged_out(CurrentPlayerPed, false);
			if (!network_is_game_in_progress())
			{
				set_ped_config_flag(CurrentPlayerPed, 32, false);
			}
		}

	}
	if (bit_test(MenuLoopedBitset, MB_VehicleHelper) && CurrentVehicle != 0)
	{
		set_vehicle_can_be_visibly_damaged(CurrentVehicle, false);
		set_entity_can_be_damaged(CurrentVehicle, false);
		set_vehicle_tyres_can_burst(CurrentVehicle, false);
		set_entity_invincible(CurrentVehicle, true);
		set_vehicle_can_break(CurrentVehicle, false);
		set_vehicle_engine_can_degrade(CurrentVehicle, false);
		set_vehicle_undriveable(CurrentVehicle, false);
		set_entity_health(CurrentVehicle, 1000);
		set_vehicle_engine_health(CurrentVehicle, 1000.0f);
		set_vehicle_petrol_tank_health(CurrentVehicle, 1000.0f);
		set_vehicle_body_health(CurrentVehicle, 1000.0f);
		if (!get_is_vehicle_engine_running(CurrentVehicle))
			set_vehicle_engine_on(CurrentVehicle, true, true, false);
	}
	if (bit_test(MenuLoopedBitset, MB_NeverWanted))
	{
		set_player_wanted_level(player_id(), 0, false);
		set_max_wanted_level(0);
	}
	


	
	/*
	//Single Player Snow Fall
	if (!has_named_ptfx_asset_loaded("core_snow"))
	{
		request_named_ptfx_asset("core_snow");
	
		//request_script_audio_bank("SNOW_FOOTSTEPS", false, -1)
		request_script_audio_bank("SNOW_FOOTSTEPS", false);
	}
	else
	{
		//XBOX TU27 Search "XMAS" Addr = IsNetworkGame function call
		#if PLATFORM == PLATFORM_X360
		*(int*)0x8274B3D0 = 0x60000000;
		*(int*)(0x8274B3D0 + 4) = 0x39200001;
		
		*(int*)0x82E910AC = 0x60000000;
		*(int*)(0x82E910AC + 4) = 0x39200001;
		#endif
		set_weather_type_now_persist("XMAS");
		_set_force_ped_footsteps_tracks(1);
		_set_force_vehicle_trails(1);
	
	
	}
	*/
}
#pragma endregion
