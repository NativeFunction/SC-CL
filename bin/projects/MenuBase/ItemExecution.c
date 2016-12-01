#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "Utils.h"
#include "common.h"

#include "MenuExecutionHandling.h"

#pragma region SavedMenuVars
static float SavedTestCoordPrecision = 0;
static bool SavedBoolTest = false;

enum MenuBits
{
	MB_FlyMod,
	MB_FlyModToggle,
};
static int MenuLoopedBitset;
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
					Vehicle CurrentVehicle = GetCurrentVehicle();
					vector3 CurrentSpeed = toVector3(0.0f);
					if (CurrentVehicle)
					{
						CurrentSpeed = get_entity_speed_vector(CurrentVehicle, true);

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

						apply_force_to_entity(MyVehicle, FT_MAX_FORCE_ROT, CurrentSpeed, toVector3(0.0f), 0, true, true, true, false, true);
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
	if (!UpdateBoolConditional(DEBUG__GetContainer()->TestInt != 5, &SavedBoolTest))
		Warn("Unable to toggle bool at this test int index");
	print(__FILE__, 5000);

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
#pragma endregion

#pragma region Menus
void Menu_PlayerList()
{
	SetHeader("Player list");
	for (int i = 0; i < LobbySizeWithSpectators; i++)
	{
		if (IsPlayerInGame(i))
			AddItemPlayer(i, Option_Blank);
	}
}
void Async_PlayerList()
{

}
void Menu_LargeSubmenuTest()
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
	AddItemIntAdvanced("Item10", false, nullptr, nullptr, true, false, 0, 50, 0, 1, Option_Blank, nullptr);
	AddItemFloatAdvanced("Item11", false, nullptr, nullptr, true, false, 0, 10, 0, 1, Option_Blank, nullptr);
	AddItemBoolAdvanced("Item12", false, nullptr, nullptr, true, false, Option_Blank, nullptr);
	AddItemEnumAdvanced("Item13", false, nullptr, nullptr, true, false, 0, 50, 0, 1, Option_Blank, Parser_EnumTest, nullptr);
	AddItemAdvanced("BJ_JUMP_06", true, "Must Come Down.~n~(Gxt Test)", nullptr, true, Option_Blank, nullptr);
	AddItemAdvanced("Item15", false, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", nullptr, false, Option_Blank, nullptr);
	AddItemAdvanced("Item16", false, nullptr, nullptr, false, Option_Blank, nullptr);
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
void Menu_MiscOptions()
{
	SetHeader("Misc Options");
	AddItemBoolAdvanced("Fly Mod", false, "Hold X and press Left Stick to use Fly Mod.", nullptr, false, bit_test(MenuLoopedBitset, MB_FlyMod), Option_FlyMod, nullptr);
}
void Menu_DebugOptions()
{
	SetHeader("Debug Options");
	AddItemAdvanced("Vehicle Spawn Test", false, "Spawns the adder.", nullptr, false, Option_DebugTest0, nullptr);
	AddItemAdvanced("Loading Off Test", false, "Turns loading icon off.", "test", false, Option_LoadingOffTest, Option_Blank);
	AddItemInt("Ui Test Precision", true, 0, 4, FloatToPrecision(SavedTestCoordPrecision), Option_UiTestPrecision);
	AddItemFloat("Ui Test Coord X", true, 0, 10, DEBUG__GetContainer()->UiTestCoords.x, SavedTestCoordPrecision, Option_TestUiCoordX);
	AddItemFloat("Ui Test Coord Y", true, 0, 10, DEBUG__GetContainer()->UiTestCoords.y, SavedTestCoordPrecision, Option_TestUiCoordY);
	AddItemInt("Ui Test Int", true, -100, 1000, DEBUG__GetContainer()->TestInt, Option_TestInt);
	AddItemBool("Bool Test", SavedBoolTest, Option_BoolTest);
	AddItemEnum("Enum Test", false, 0, 10, 0, Option_EnumTest, Parser_EnumTest);
	AddItemIntBool("Int Bool Test", 0, 10, 0, 0, Option_Blank);
	AddItemEnumBool("Enum Bool Test", 0, 10, 0, 0, Option_Blank, Parser_EnumTest);
	AddItemFloatBool("Float Bool Test", 0, 10, 0, 1.0f, 0, Option_Blank);
	AddItemMenu("Large Submenu Test", Menu_LargeSubmenuTest);

}
inline void MainMenu()
{
	SetHeader("Main Menu");

	AddItemMenu("Player List", Menu_PlayerList);
	AddItemMenu("Misc Options", Menu_MiscOptions);
	AddItemMenu("Debug Options", Menu_DebugOptions);

}
#pragma endregion

#pragma region LoopedOptions
void FlyMod(Player CurrentPlayerPed)
{
	DisableControl(2, INPUT_VEHICLE_LOOK_BEHIND);
	DisableControl(2, INPUT_LOOK_BEHIND);
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
		}
	}
	if (bit_test(MenuLoopedBitset, MB_FlyModToggle))
		FlyMod(CurrentPlayerPed);
}


inline void LoopedOptions()
{
	Player CurrentPlayerPed = player_ped_id();

	if (bit_test(MenuLoopedBitset, MB_FlyMod) && !is_pause_menu_active())
		FlyModController(CurrentPlayerPed);
}
#pragma endregion




