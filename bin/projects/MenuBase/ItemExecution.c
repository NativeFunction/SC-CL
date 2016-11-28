#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "Utils.h"
#include "common.h"

#include "MenuExecutionHandling.h"

static float SavedTestCoordPrecision = 0;
static bool SavedBoolTest = false;

char* Parser_EnumTest(int ItemIndex)
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

void Option_Blank()
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


int FindFreeCarSeat(Vehicle VehicleToFindSeat)
{
	int MaxPassengers = get_vehicle_max_number_of_passengers(VehicleToFindSeat);

	for (int i = -1; i < MaxPassengers; i++)
	{
		if (is_vehicle_seat_free(VehicleToFindSeat, i))
			return i;
	}
	return -2;
}
Vehicle GetCurrentVehicle()
{
	Ped MyPed = player_ped_id();
	return is_ped_in_any_vehicle(MyPed, false) ? get_vehicle_ped_is_in(MyPed, false) : 0;
}
bool SpawnVehicle(uint CurrentFrame, Hash Model)
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


void Option_DebugTest0()
{
	StartAsynchronousFunction(Async(SpawnVehicle), 1, 150, AsyncParam(hashof("adder")) );
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
}
void Option_EnumTest()
{

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
	AddItemMenu("Large Submenu Test", Menu_LargeSubmenuTest);

}

inline void MainMenu()
{
	SetHeader("Main Menu");
	AddItemMenu("Debug Options", Menu_DebugOptions);

}




