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
	MB_GodMode,
	MB_VehicleHelper,
	MB_NeverWanted
};
static int MenuLoopedBitset;
#pragma endregion

#pragma region AlignedDataTesting
noinline short NoInlineShort()
{
	return 5;
}
static short InlineShort()
{
	return 3000;
}
noinline ushort NoInlineUShort()
{
	return 5;
}
ushort InlineUShort()
{
	return 300;
}
noinline void asmComment(const char* x)
{

}
void ShortTesting()
{
	short sArr2D[3][5] = { { 1000,2000,3000,4000 },{ 6000,7000,8000,9000,10000 },{ 11000,12000,13000,14000,15000 } };

	int IntToShortConv = 50000000;
	char CharToShortConv = 'A';

	asmComment("-------Static Short Initialization---------");
	short StaticShortInit = 30000;
	short StaticShortInitNeg = (short)-30000;
	short StaticShortInitNegOverflow = (short)-300000000;
	short StaticShortInitOverflow = (short)300000000;

	asmComment("-------Static UShort Initialization---------");
	ushort StaticUShortInit = 50000;
	ushort StaticUShortInitNegConv = (short)-30000;
	ushort StaticUShortInitNegConv2 = (short)-1;
	ushort StaticUShortInitNegOverflow = (short)-300000000;
	ushort StaticUShortInitOverflow = (short)300000000;

	asmComment("-------Dynamic Short Initialization---------");
	short DynamicShortInit_WithShort = StaticShortInit;
	short DynamicShortInit_WithNegShort = StaticShortInitNegOverflow;
	short DynamicShortInit_WithUShort = StaticUShortInit;
	short DynamicShortInit_WithNegUShort = StaticUShortInitNegOverflow;
	short DynamicShortInit_WithInt = IntToShortConv;
	short DynamicShortInit_WithChar = CharToShortConv;
	short DynamicShortInit_WithShortArray = sArr2D[1][1];
	short DynamicShortInit_WithShortFunction = NoInlineShort();
	short DynamicShortInit_WithShortFunctionInline = InlineShort();
	short DynamicShortInit_WithUShortFunction = NoInlineUShort();
	short DynamicShortInit_WithUShortFunctionInline = InlineUShort();

	asmComment("-------Dynamic UShort Initialization---------");
	ushort DynamicUShortInit_WithShort = StaticShortInit;
	ushort DynamicUShortInit_WithNegShort = StaticShortInitNegOverflow;
	ushort DynamicUShortInit_WithUShort = StaticUShortInit;
	ushort DynamicUShortInit_WithNegUShort = StaticUShortInitNegOverflow;
	ushort DynamicUShortInit_WithInt = IntToShortConv;
	ushort DynamicUShortInit_WithChar = CharToShortConv;
	ushort DynamicUShortInit_WithShortArray = sArr2D[1][2];
	ushort DynamicUShortInit_WithShortFunction = NoInlineShort();
	ushort DynamicUShortInit_WithShortFunctionInline = InlineShort();
	ushort DynamicUShortInit_WithUShortFunction = NoInlineUShort();
	ushort DynamicUShortInit_WithUShortFunctionInline = InlineUShort();

	asmComment("setting short 2d array");
	sArr2D[2][1] = 5000;
	asmComment("setting derefed short 2d array with math");
	*(sArr2D[1] + 3) = 6000;
	asmComment("setting derefed short 2d array with math and sizeof");
	*(*sArr2D + sizeof(sArr2D[0]) + 3) = 7000;//CError: #64: sizeof short arrays of arrays are too big (mult bug)
	asmComment("setting derefed short 2d array");
	*(*sArr2D) = 7000;
	asmComment("short 2d array to int");
	int stoi_2d = sArr2D[0][3];
	asmComment("short 2d array to short");
	short stos_2d = sArr2D[0][3];
	asmComment("short 2d array to char");
	char stoc_2d = sArr2D[0][2];

	short sArr3D[3][4][5] =
	{ { { 1000,2000,3000,4000 },{ 6000,7000,8000,9000,10000 },{ 11000,12000,13000,14000 } },
	{ { 16000,17000,18000,19000 },{ 20000,21000,22000,23000,24000 },{ 25000,26000,27000,28000,29000 },{ 30000,31000,32000,33000,34000 } },
	{ { 38000,39000,40000,41000,42000 } } };

	asmComment("-------seting normal and getting test---------");
	asmComment("simple set array value");
	sArr3D[1][0][2] = 4444;
	asmComment("simple set array negitive value");
	sArr3D[2][3][4] = -5555;
	asmComment("set array value narrowing conversion literal");
	sArr3D[0][0][0] = (short)1000000;
	asmComment("set array value to array value");
	sArr3D[1][1][3] = sArr3D[2][0][3];
	asmComment("set array value to array pointer + index deref");
	sArr3D[2][2][2] = *(sArr3D[2][0] + 3);
	asmComment("set array value to array pointer + array pointer deref + index deref");
	sArr3D[1][2][0] = *(*(sArr3D[2] + 2) + 1);
	asmComment("set array value to array pointer with only adding index");
	sArr3D[0][2][1] = ***(sArr3D + 1);

	asmComment("--------setting to it self---------");
	*(sArr3D[2][0] + 3) = *(sArr3D[2][0] + 3);
	*(*(sArr3D[2] + 2) + 1) = *(*(sArr3D[2] + 2) + 1);
	***(sArr3D + 1) = ***(sArr3D + 1);

	asmComment("--------incrementation----------");
	sArr3D[1][1][3]++;
	(*(sArr3D[2][0] + 3))++;
	(*(*(sArr3D[2] + 2) + 1))--;
	(***(sArr3D + 1))++;

	asmComment("---------increment it self----------");
	*(sArr3D[2][0] + 3) += *(sArr3D[2][0] + 3);
	*(*(sArr3D[2] + 2) + 1) -= *(*(sArr3D[2] + 2) + 1);
	***(sArr3D + 1) += ***(sArr3D + 1);




	*(sArr2D[1] + 3) = 6000;
	*(*sArr2D + sizeof(sArr2D[0]) + 3) = 7000;
	*(*sArr2D) = 7000;
	int stoi = sArr2D[0][1];
	uint stoui = sArr2D[0][2];
	short stos = sArr2D[0][4];
	ushort stous = sArr2D[0][3];
	char stoc = sArr2D[0][2];
	uchar stouc = sArr2D[0][3];

	//ShortParamTest(NoInlineUShort(), sArr2D[0], *sArr2D, (short**)sArr2D);
	//short ShortParamTest(short a, short b[], short* c, short* d[])

}

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
					if (CurrentVehicle)
					{
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
	is_this_model_a_heli(VEHICLE_ADDER);
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
#pragma endregion

#pragma region Menus

void Menu__PlayerList()
{
	SetHeaderAdvanced("Player list", false, true);
	//for (int i = 0; i < LobbySizeWithSpectators; i++)
	//{
	//	if (IsPlayerInGame(i))
	//		AddItemPlayer(i, Option_Blank);
	//}

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
		AddItemPlayer(0, Option_Blank, "player0");
		AddItemPlayer(1, Option_Blank, "player1");
		AddItemPlayer(2, Option_Blank, "player2");
		AddItemPlayer(3, Option_Blank, "player3");
		AddItemPlayer(4, Option_Blank, "player4");
		AddItemPlayer(5, Option_Blank, "player5");
		AddItemPlayer(6, Option_Blank, "player6");
		AddItemPlayer(7, Option_Blank, "player7");
		AddItemPlayer(8, Option_Blank, "player8");
		AddItemPlayer(9, Option_Blank, "player9");
		AddItemPlayer(10, Option_Blank, "player10");
		AddItemPlayer(11, Option_Blank, "player11");
		AddItemPlayer(12, Option_Blank, "player12");
		AddItemPlayer(13, Option_Blank, "player13");
		AddItemPlayer(14, Option_Blank, "player14");
		AddItemPlayer(15, Option_Blank, "player15");
		AddItemPlayer(16, Option_Blank, "player16");
		AddItemPlayer(17, Option_Blank, "player17");
		AddItemPlayer(18, Option_Blank, "player18");
		AddItemPlayer(19, Option_Blank, "player19");
		AddItemPlayer(20, Option_Blank, "player20");
		AddItemPlayer(21, Option_Blank, "player21");
		AddItemPlayer(22, Option_Blank, "player22");
		AddItemPlayer(23, Option_Blank, "player23");
		AddItemPlayer(24, Option_Blank, "player24");
		AddItemPlayer(25, Option_Blank, "player25");
		AddItemPlayer(26, Option_Blank, "player26");
		AddItemPlayer(27, Option_Blank, "player27");
		AddItemPlayer(28, Option_Blank, "player28");
		AddItemPlayer(29, Option_Blank, "player29");
		AddItemPlayer(30, Option_Blank, "player30");
		AddItemPlayer(31, Option_Blank, "player31");
	}
	else if (timera() < 20000)
	{
		//AddItemPlayer(0, Option_Blank, "player0");
		AddItemPlayer(1, Option_Blank, "player1");
		AddItemPlayer(2, Option_Blank, "player2");
		AddItemPlayer(3, Option_Blank, "player3");
		//AddItemPlayer(4, Option_Blank, "player4");
		AddItemPlayer(5, Option_Blank, "player5");
		AddItemPlayer(6, Option_Blank, "player6");
		AddItemPlayer(7, Option_Blank, "player7");
		AddItemPlayer(8, Option_Blank, "player8");
		AddItemPlayer(9, Option_Blank, "player9");
		AddItemPlayer(10, Option_Blank, "player10");
		AddItemPlayer(11, Option_Blank, "player11");
		AddItemPlayer(12, Option_Blank, "player12");
		AddItemPlayer(13, Option_Blank, "player13");
		//AddItemPlayer(14, Option_Blank, "player14");
		AddItemPlayer(15, Option_Blank, "player15");
		AddItemPlayer(16, Option_Blank, "player16");
		AddItemPlayer(17, Option_Blank, "player17");
		AddItemPlayer(18, Option_Blank, "player18");
		AddItemPlayer(19, Option_Blank, "player19");
		AddItemPlayer(20, Option_Blank, "player20");
		AddItemPlayer(21, Option_Blank, "player21");
		AddItemPlayer(22, Option_Blank, "player22");
		AddItemPlayer(23, Option_Blank, "player23");
		AddItemPlayer(24, Option_Blank, "player24");
		//AddItemPlayer(25, Option_Blank, "player25");
		AddItemPlayer(26, Option_Blank, "player26");
		AddItemPlayer(27, Option_Blank, "player27");
		AddItemPlayer(28, Option_Blank, "player28");
		AddItemPlayer(29, Option_Blank, "player29");
		AddItemPlayer(30, Option_Blank, "player30");
		//AddItemPlayer(31, Option_Blank, "player31");
	}
	else if (timera() < 30000)
	{
		//AddItemPlayer(0, Option_Blank, "player0");
		//AddItemPlayer(1, Option_Blank, "player1");
		//AddItemPlayer(2, Option_Blank, "player2");
		//AddItemPlayer(3, Option_Blank, "player3");
		//AddItemPlayer(4, Option_Blank, "player4");
		//AddItemPlayer(5, Option_Blank, "player5");
		//AddItemPlayer(6, Option_Blank, "player6");
		AddItemPlayer(7, Option_Blank, "player7");
		AddItemPlayer(8, Option_Blank, "player8");
		AddItemPlayer(9, Option_Blank, "player9");
		AddItemPlayer(10, Option_Blank, "player10");
		AddItemPlayer(11, Option_Blank, "player11");
		AddItemPlayer(12, Option_Blank, "player12");
		AddItemPlayer(13, Option_Blank, "player13");
		//AddItemPlayer(14, Option_Blank, "player14");
		AddItemPlayer(15, Option_Blank, "player15");
		AddItemPlayer(16, Option_Blank, "player16");
		AddItemPlayer(17, Option_Blank, "player17");
		AddItemPlayer(18, Option_Blank, "player18");
		AddItemPlayer(19, Option_Blank, "player19");
		//AddItemPlayer(20, Option_Blank, "player20");
		AddItemPlayer(21, Option_Blank, "player21");
		AddItemPlayer(22, Option_Blank, "player22");
		AddItemPlayer(23, Option_Blank, "player23");
		AddItemPlayer(24, Option_Blank, "player24");
		//AddItemPlayer(25, Option_Blank, "player25");
		AddItemPlayer(26, Option_Blank, "player26");
		AddItemPlayer(27, Option_Blank, "player27");
		AddItemPlayer(28, Option_Blank, "player28");
		AddItemPlayer(29, Option_Blank, "player29");
		AddItemPlayer(30, Option_Blank, "player30");
		//AddItemPlayer(31, Option_Blank, "player31");
	}
	else
	{
		netsimstart = true;
		goto startnettime;
	}
	#pragma endregion
	//todo: fix menu invalid (soft freezes)
	if(!GetCurrentItemCount())
		SetCurrentMenuInvalid(true);
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
void Menu__PlayerOptions()
{
	SetHeader("Player Options");
	AddItemBoolAdvanced("God Mode", false, "Makes player invincible.", nullptr, false, bit_test(MenuLoopedBitset, MB_GodMode), Option_GodMode, nullptr);
	AddItemBoolAdvanced("Never Wanted", false, "Disables police.", nullptr, false, bit_test(MenuLoopedBitset, MB_NeverWanted), Option_NeverWanted, nullptr);

}

#pragma region VehicleSpawner
void Menu__VehicleSpawner_Sports()
{
	SetHeader("Sports");
	AddItemVehicle(hashof("ninef"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ninef2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("banshee"), Option_SpawnVehicle);
	AddItemVehicle(hashof("buffalo"), Option_SpawnVehicle);
	AddItemVehicle(hashof("buffalo2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("carbonizzare"), Option_SpawnVehicle);
	AddItemVehicle(hashof("comet2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("coquette"), Option_SpawnVehicle);
	AddItemVehicle(hashof("elegy2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("feltzer2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("fusilade"), Option_SpawnVehicle);
	AddItemVehicle(hashof("futo"), Option_SpawnVehicle);
	AddItemVehicle(hashof("khamelion"), Option_SpawnVehicle);
	AddItemVehicle(hashof("penumbra"), Option_SpawnVehicle);
	AddItemWithParam("Rapid GT Cabrio", hashof("rapidgt2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("schwarzer"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sultan"), Option_SpawnVehicle);
	AddItemVehicle(hashof("surano"), Option_SpawnVehicle);
	AddItemVehicle(hashof("jester"), Option_SpawnVehicle);

	if (is_dlc_present(Update_mpBusiness))
		AddItemVehicle(hashof("alpha"), Option_SpawnVehicle);
	if (is_dlc_present(Update_mpBusiness2))
		AddItemVehicle(hashof("massacro"), Option_SpawnVehicle);
	if (is_dlc_present(Update_mpLTS))
		AddItemVehicle(hashof("furoregt"), Option_SpawnVehicle);
	if (is_dlc_present(Update_mpChristmas2))
	{
		AddItemVehicle(hashof("jester2"), Option_SpawnVehicle);
		AddItemVehicle(hashof("massacro2"), Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpHeist))
	{
		AddItemVehicle(hashof("kuruma"), Option_SpawnVehicle);
		AddItemVehicle(hashof("kuruma2"), Option_SpawnVehicle);
	}
	
	#ifdef __YSC__
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_BLISTA2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BLISTA3, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BUFFALO3, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_SCHAFTER3, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SCHAFTER4, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_VERLIERER2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_SEVEN70, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BESTIAGTS, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_LYNX, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_OMNIS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_TROPOS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_TAMPA2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpBiker))
	{
		AddItemVehicle(VEHICLE_RAPTOR, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_ELEGY, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SPECTER, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SPECTER2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_COMET3, Option_SpawnVehicle);
	}

	#endif
	
}
void Menu__VehicleSpawner_Super()
{
	SetHeader("Super");
	AddItemVehicle(hashof("bullet"), Option_SpawnVehicle);
	AddItemVehicle(hashof("cheetah"), Option_SpawnVehicle);
	AddItemVehicle(hashof("entityxf"), Option_SpawnVehicle);
	AddItemVehicle(hashof("infernus"), Option_SpawnVehicle);
	AddItemVehicle(hashof("adder"), Option_SpawnVehicle);
	AddItemVehicle(hashof("voltic"), Option_SpawnVehicle);
	AddItemVehicle(hashof("vacca"), Option_SpawnVehicle);
	AddItemVehicle(hashof("turismor"), Option_SpawnVehicle);
	AddItemVehicle(hashof("zentorno"), Option_SpawnVehicle);
	AddItemVehicle(hashof("osiris"), Option_SpawnVehicle);
	AddItemVehicle(hashof("t20"), Option_SpawnVehicle);

	#ifdef __YSC__
	if (is_dlc_present(Update_mpJanuary2016))
	{
		AddItemVehicle(VEHICLE_SULTANRS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BANSHEE2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_FMJ, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_PFISTER811, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_PROTOTIPO, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_REAPER, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_TYRUS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SHEAVA, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_LE7B, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_TEMPESTA, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_ITALIGTB, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_ITALIGTB2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_NERO, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_NERO2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_VOLTIC2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_PENETRATOR, Option_SpawnVehicle);
	}

	#endif

}
void Menu__VehicleSpawner_Coupes()
{
	SetHeader("Coupes");
	AddItemVehicle(hashof("cogcabrio"), Option_SpawnVehicle);
	AddItemVehicle(hashof("exemplar"), Option_SpawnVehicle);
	AddItemVehicle(hashof("f620"), Option_SpawnVehicle);
	AddItemVehicle(hashof("felon"), Option_SpawnVehicle);
	AddItemVehicle(hashof("felon2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("Jackal"), Option_SpawnVehicle);
	AddItemVehicle(hashof("oracle"), Option_SpawnVehicle);
	AddItemVehicle(hashof("oracle2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sentinel"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sentinel2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("zion"), Option_SpawnVehicle);
	AddItemVehicle(hashof("zion2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("windsor"), Option_SpawnVehicle);


	#ifdef __YSC__
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_WINDSOR2, Option_SpawnVehicle);
	}
	#endif

}
void Menu__VehicleSpawner_Compacts()
{
	SetHeader("Compacts");
	AddItemVehicle(hashof("blista"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dilettante"), Option_SpawnVehicle);
	AddItemWithParam("Dilettante (Merryweather)", hashof("dilettante2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("issi2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("prairie"), Option_SpawnVehicle);
	AddItemVehicle(hashof("rhapsody"), Option_SpawnVehicle);
	AddItemVehicle(hashof("panto"), Option_SpawnVehicle);

	#ifdef __YSC__
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_BRIOSO, Option_SpawnVehicle);
	}
	#endif

}
void Menu__VehicleSpawner_Sedans()
{
	SetHeader("Sedans");

	AddItemVehicle(hashof("asea"), Option_SpawnVehicle);
	AddItemWithParam("Asea (Snowy)", hashof("asea2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("asterope"), Option_SpawnVehicle);
	AddItemVehicle(hashof("emperor"), Option_SpawnVehicle);
	AddItemWithParam("Emperor (Rusty)", hashof("emperor2"), Option_SpawnVehicle);
	AddItemWithParam("Emperor (Snowy)", hashof("emperor3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("fugitive"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ingot"), Option_SpawnVehicle);
	AddItemVehicle(hashof("intruder"), Option_SpawnVehicle);
	AddItemVehicle(hashof("premier"), Option_SpawnVehicle);
	AddItemVehicle(hashof("primo"), Option_SpawnVehicle);
	AddItemVehicle(hashof("regina"), Option_SpawnVehicle);
	AddItemVehicle(hashof("romero"), Option_SpawnVehicle);
	AddItemVehicle(hashof("schafter2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("stanier"), Option_SpawnVehicle);
	AddItemVehicle(hashof("stratum"), Option_SpawnVehicle);
	AddItemVehicle(hashof("stretch"), Option_SpawnVehicle);
	AddItemVehicle(hashof("superd"), Option_SpawnVehicle);
	AddItemVehicle(hashof("surge"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tailgater"), Option_SpawnVehicle);
	AddItemVehicle(hashof("washington"), Option_SpawnVehicle);
	AddItemVehicle(hashof("warrener"), Option_SpawnVehicle);
	AddItemVehicle(hashof("glendale"), Option_SpawnVehicle);


	#ifdef __YSC__
	if (is_dlc_present(Update_mpLowrider))
	{
		AddItemVehicle(VEHICLE_PRIMO2, Option_SpawnVehicle);
	}

	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_LIMO2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SCHAFTER5, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SCHAFTER6, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_COG55, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_COG552, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_COGNOSCENTI, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_COGNOSCENTI2, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_SportsClassic()
{
	SetHeader("Sports Classics");
	AddItemVehicle(hashof("jb700"), Option_SpawnVehicle);
	AddItemVehicle(hashof("manana"), Option_SpawnVehicle);
	AddItemVehicle(hashof("monroe"), Option_SpawnVehicle);
	AddItemVehicle(hashof("peyote"), Option_SpawnVehicle);
	AddItemVehicle(hashof("stinger"), Option_SpawnVehicle);
	AddItemVehicle(hashof("stingergt"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tornado"), Option_SpawnVehicle);
	AddItemWithParam("Tornado Cabrio", hashof("tornado2"), Option_SpawnVehicle);
	AddItemWithParam("Tornado (Rusty)", hashof("tornado3"), Option_SpawnVehicle);
	AddItemWithParam("Tornado (Guitar)", hashof("tornado4"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ztype"), Option_SpawnVehicle);
	AddItemVehicle(hashof("btype"), Option_SpawnVehicle);
	AddItemVehicle(hashof("pigalle"), Option_SpawnVehicle);
	AddItemVehicle(hashof("coquette2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("casco"), Option_SpawnVehicle);
	AddItemVehicle(hashof("feltzer3"), Option_SpawnVehicle);
	
	#ifdef __YSC__
	if (is_dlc_present(Update_mpHalloween))
		AddItemVehicle(VEHICLE_BTYPE2, Option_SpawnVehicle);
	if (is_dlc_present(Update_mpApartment))
		AddItemVehicle(VEHICLE_MAMBA, Option_SpawnVehicle);
	if (is_dlc_present(Update_mpValentines2))
		AddItemVehicle(VEHICLE_BTYPE3, Option_SpawnVehicle);
	if (is_dlc_present(Update_mpLowrider2))
		AddItemVehicle(VEHICLE_TORNADO5, Option_SpawnVehicle);
	if (is_dlc_present(Update_mpBiker))
		AddItemVehicle(VEHICLE_TORNADO6, Option_SpawnVehicle);

	#endif
}
void Menu__VehicleSpawner_Muscle()
{
	SetHeader("Muscle");
	AddItemVehicle(hashof("buccaneer"), Option_SpawnVehicle);
	AddItemVehicle(hashof("hotknife"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dominator"), Option_SpawnVehicle);
	AddItemVehicle(hashof("gauntlet"), Option_SpawnVehicle);
	AddItemVehicle(hashof("phoenix"), Option_SpawnVehicle);
	AddItemVehicle(hashof("picador"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ratloader"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ruiner"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sabregt"), Option_SpawnVehicle);
	AddItemVehicle(hashof("voodoo2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("vigero"), Option_SpawnVehicle);
	AddItemVehicle(hashof("blade"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ratloader2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("slamvan"), Option_SpawnVehicle);
	AddItemVehicle(hashof("slamvan2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("virgo"), Option_SpawnVehicle);
	AddItemVehicle(hashof("chino"), Option_SpawnVehicle);
	AddItemVehicle(hashof("coquette3"), Option_SpawnVehicle);

	
	#ifdef __YSC__
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_DUKES, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DUKES2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DOMINATOR2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_GAUNTLET2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_STALION, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_STALION2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpLowrider))
	{
		AddItemVehicle(VEHICLE_MOONBEAM, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_MOONBEAM2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_FACTION, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_FACTION2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_CHINO2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BUCCANEER2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_VOODOO, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpHalloween))
	{
		AddItemVehicle(VEHICLE_LURCHER, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_NIGHTSHADE, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpXmas))
	{
		AddItemVehicle(VEHICLE_TAMPA, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpLowrider2))
	{
		AddItemVehicle(VEHICLE_FACTION3, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SABREGT2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SLAMVAN3, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_VIRGO2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_VIRGO3, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_RUINER2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_RUINER3, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Suv()
{
	SetHeader("SUVs");
	AddItemVehicle(hashof("baller2"), Option_SpawnVehicle);
	AddItemWithParam("Baller (Old)", hashof("baller"), Option_SpawnVehicle);
	AddItemVehicle(hashof("bjxl"), Option_SpawnVehicle);
	AddItemVehicle(hashof("cavalcade2"), Option_SpawnVehicle);
	AddItemWithParam("Cavalcade (Old)", hashof("cavalcade"), Option_SpawnVehicle);
	AddItemVehicle(hashof("gresley"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dubsta"), Option_SpawnVehicle);
	AddItemWithParam("Dubsta (Blacked Out)", hashof("dubsta2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("fq2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("granger"), Option_SpawnVehicle);
	AddItemVehicle(hashof("habanero"), Option_SpawnVehicle);
	AddItemVehicle(hashof("landstalker"), Option_SpawnVehicle);
	AddItemVehicle(hashof("mesa"), Option_SpawnVehicle);
	AddItemWithParam("Mesa (Snowy)", hashof("mesa2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("patriot"), Option_SpawnVehicle);
	AddItemVehicle(hashof("radi"), Option_SpawnVehicle);
	AddItemVehicle(hashof("rocoto"), Option_SpawnVehicle);
	AddItemVehicle(hashof("seminole"), Option_SpawnVehicle);
	AddItemVehicle(hashof("serrano"), Option_SpawnVehicle);
	AddItemVehicle(hashof("huntley"), Option_SpawnVehicle);

	#ifdef __YSC__
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_BALLER3, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BALLER4, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BALLER5, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BALLER6, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_XLS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_XLS2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_CONTENDER, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Van()
{
	SetHeader("Vans");
	AddItemVehicle(hashof("bison"), Option_SpawnVehicle);
	AddItemWithParam("Bison (Construction)", hashof("bison2"), Option_SpawnVehicle);
	AddItemWithParam("Bison (Landscapeing)", hashof("bison3"), Option_SpawnVehicle);
	AddItemWithParam("Boxville (Water&Power)", hashof("boxville"), Option_SpawnVehicle);
	AddItemWithParam("Boxville (Postal)", hashof("boxville2"), Option_SpawnVehicle);
	AddItemWithParam("Boxville (Humane)", hashof("boxville3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("bobcatxl"), Option_SpawnVehicle);
	AddItemVehicle(hashof("burrito3"), Option_SpawnVehicle);
	AddItemWithParam("Burrito (Multi Livery)", hashof("burrito"), Option_SpawnVehicle);
	AddItemWithParam("Burrito (Bugstars)", hashof("burrito2"), Option_SpawnVehicle);
	AddItemWithParam("Burrito (Construction)", hashof("burrito4"), Option_SpawnVehicle);
	AddItemWithParam("Burrito (Snowy)", hashof("burrito5"), Option_SpawnVehicle);
	AddItemVehicle(hashof("gburrito"), Option_SpawnVehicle);
	AddItemVehicle(hashof("camper"), Option_SpawnVehicle);
	AddItemVehicle(hashof("journey"), Option_SpawnVehicle);
	AddItemVehicle(hashof("minivan"), Option_SpawnVehicle);
	AddItemVehicle(hashof("pony"), Option_SpawnVehicle);
	AddItemWithParam("Weed Van", hashof("pony2"), Option_SpawnVehicle);
	AddItemWithParam("Rumpo (Weazel News)", hashof("rumpo"), Option_SpawnVehicle);
	AddItemWithParam("Rumpo (Deludamol)", hashof("rumpo2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("speedo"), Option_SpawnVehicle);
	AddItemVehicle(hashof("speedo2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("surfer"), Option_SpawnVehicle);
	AddItemWithParam("Surfer (Rusty)", hashof("surfer2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("taco"), Option_SpawnVehicle);
	AddItemVehicle(hashof("youga"), Option_SpawnVehicle);
	AddItemVehicle(hashof("paradise"), Option_SpawnVehicle);
	AddItemWithParam("Boxville (Post OP)", hashof("boxville4"), Option_SpawnVehicle);
	AddItemWithParam("Gang Burrito (No Livery)", hashof("gburrito2"), Option_SpawnVehicle);
	
	#ifdef __YSC__
	if (is_dlc_present(Update_mpLowrider2))
	{
		AddItemVehicle(VEHICLE_MINIVAN2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_RUMPO3, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpBiker))
		AddItemVehicle(VEHICLE_YOUGA2, Option_SpawnVehicle);
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_BOXVILLE5, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Offroad()
{
	SetHeader("Off-Road");
	AddItemVehicle(hashof("bfinjection"), Option_SpawnVehicle);
	AddItemVehicle(hashof("blazer"), Option_SpawnVehicle);
	AddItemVehicle(hashof("blazer2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("blazer3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("bodhi2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dune"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dune2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dloader"), Option_SpawnVehicle);
	AddItemWithParam("Mesa (Merryweather)", hashof("mesa3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("rancherxl"), Option_SpawnVehicle);
	AddItemWithParam("Rancher XL (Snowy)", hashof("rancherxl2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("rebel2"), Option_SpawnVehicle);
	AddItemWithParam("Rebel (Rusty)", hashof("rebel"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sandking"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sandking2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("bifta"), Option_SpawnVehicle);
	AddItemVehicle(hashof("kalahari"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dubsta3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("monster"), Option_SpawnVehicle);
	AddItemVehicle(hashof("insurgent"), Option_SpawnVehicle);
	AddItemWithParam("Insurgent Transport", hashof("insurgent2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("technical"), Option_SpawnVehicle);
	AddItemVehicle(hashof("brawler"), Option_SpawnVehicle);

	
	#ifdef __YSC__
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_MARSHALL, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_TROPHYTRUCK, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_TROPHYTRUCK2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpBiker))
	{
		AddItemVehicle(VEHICLE_BLAZER4, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_BLAZER5, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DUNE4, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DUNE5, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_TECHNICAL2, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Commercial()
{
	SetHeader("Commercial");
	AddItemVehicle(hashof("benson"), Option_SpawnVehicle);
	AddItemVehicle(hashof("biff"), Option_SpawnVehicle);
	AddItemVehicle(hashof("hauler"), Option_SpawnVehicle);
	AddItemVehicle(hashof("mule"), Option_SpawnVehicle);
	AddItemWithParam("Mule (Drop Down Trunk)", hashof("mule2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("packer"), Option_SpawnVehicle);
	AddItemVehicle(hashof("phantom"), Option_SpawnVehicle);
	AddItemVehicle(hashof("pounder"), Option_SpawnVehicle);
	AddItemVehicle(hashof("stockade"), Option_SpawnVehicle);
	AddItemWithParam("Stockade (Snowy)", hashof("stockade3"), Option_SpawnVehicle);
	AddItemWithParam("Mule (No Livery)", hashof("mule3"), Option_SpawnVehicle);
	#ifdef __YSC__
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_PHANTOM2, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Service()
{
	SetHeader("Service");
	AddItemVehicle(hashof("bus"), Option_SpawnVehicle);
	AddItemVehicle(hashof("coach"), Option_SpawnVehicle);
	AddItemVehicle(hashof("airbus"), Option_SpawnVehicle);
	AddItemVehicle(hashof("rentalbus"), Option_SpawnVehicle);
	AddItemVehicle(hashof("taxi"), Option_SpawnVehicle);
	AddItemVehicle(hashof("trash"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tourbus"), Option_SpawnVehicle);
	AddItemWithParam("Trashmaster (Rusty)", hashof("trash2"), Option_SpawnVehicle);
	#ifdef __YSC__
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_BRICKADE, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_RALLYTRUCK, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_WASTELANDER, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Utility()
{
	SetHeader("Utility");
	AddItemVehicle(hashof("airtug"), Option_SpawnVehicle);
	AddItemVehicle(hashof("caddy"), Option_SpawnVehicle);
	AddItemWithParam("Caddy (Old)", hashof("caddy2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("docktug"), Option_SpawnVehicle);
	AddItemVehicle(hashof("forklift"), Option_SpawnVehicle);
	AddItemVehicle(hashof("mower"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ripley"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sadler"), Option_SpawnVehicle);
	AddItemWithParam("Sadler (Snowy)", hashof("sadler2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("scrap"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tractor2"), Option_SpawnVehicle);
	AddItemWithParam("Tractor (Rusty)", hashof("tractor"), Option_SpawnVehicle);
	AddItemWithParam("Tractor (Snowy)", hashof("tractor3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("towtruck"), Option_SpawnVehicle);
	AddItemWithParam("Towtruck (Small)", hashof("towtruck2"), Option_SpawnVehicle);
	AddItemWithParam("Basket Truck", hashof("utillitruck"), Option_SpawnVehicle);
	AddItemVehicle(hashof("utillitruck2"), Option_SpawnVehicle);
	AddItemWithParam("Utility Pick-up Truck", hashof("utillitruck3"), Option_SpawnVehicle);
	#ifdef __YSC__

	#endif
}
void Menu__VehicleSpawner_Industrial()
{
	SetHeader("Industrial");
	AddItemVehicle(hashof("bulldozer"), Option_SpawnVehicle);
	AddItemVehicle(hashof("cutter"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dump"), Option_SpawnVehicle);
	AddItemVehicle(hashof("rubble"), Option_SpawnVehicle);
	AddItemVehicle(hashof("flatbed"), Option_SpawnVehicle);
	AddItemVehicle(hashof("handler"), Option_SpawnVehicle);
	AddItemVehicle(hashof("mixer"), Option_SpawnVehicle);
	AddItemWithParam("Mixer (Wheels On Back)", hashof("mixer2"), Option_SpawnVehicle);
	AddItemWithParam("Tipper (6-Wheeler)", hashof("tiptruck"), Option_SpawnVehicle);
	AddItemWithParam("Tipper (10-Wheeler)", hashof("tiptruck2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("guardian"), Option_SpawnVehicle);
	#ifdef __YSC__

	#endif
}
void Menu__VehicleSpawner_Emergency()
{
	SetHeader("Emergency");
	AddItemVehicle(hashof("ambulance"), Option_SpawnVehicle);
	AddItemVehicle(hashof("policet"), Option_SpawnVehicle);
	AddItemWithParam("FIB Buffalo", hashof("fbi"), Option_SpawnVehicle);
	AddItemWithParam("FIB Granger", hashof("fbi2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("firetruk"), Option_SpawnVehicle);
	AddItemVehicle(hashof("lguard"), Option_SpawnVehicle);
	AddItemVehicle(hashof("pbus"), Option_SpawnVehicle);
	AddItemWithParam("Police Stanier", hashof("police"), Option_SpawnVehicle);
	AddItemWithParam("Police Buffalo", hashof("police2"), Option_SpawnVehicle);
	AddItemWithParam("Police Interceptor", hashof("police3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("police4"), Option_SpawnVehicle);
	AddItemVehicle(hashof("policeold1"), Option_SpawnVehicle);
	AddItemVehicle(hashof("policeold2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("pranger"), Option_SpawnVehicle);
	AddItemVehicle(hashof("riot"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sheriff"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sheriff2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("policeb"), Option_SpawnVehicle);
	#ifdef __YSC__

	#endif
}
void Menu__VehicleSpawner_Military()
{
	SetHeader("Military");
	AddItemVehicle(hashof("barracks"), Option_SpawnVehicle);
	AddItemVehicle(hashof("barracks2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("crusader"), Option_SpawnVehicle);
	AddItemVehicle(hashof("rhino"), Option_SpawnVehicle);
	AddItemWithParam("Barracks (Dark Camo)", hashof("barracks3"), Option_SpawnVehicle);
	#ifdef __YSC__

	#endif
}
void Menu__VehicleSpawner_Motorcycle()
{
	SetHeader("Motorcycles");
	AddItemVehicle(hashof("sanchez"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sanchez2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("akuma"), Option_SpawnVehicle);
	AddItemVehicle(hashof("carbonrs"), Option_SpawnVehicle);
	AddItemVehicle(hashof("bagger"), Option_SpawnVehicle);
	AddItemVehicle(hashof("bati"), Option_SpawnVehicle);
	AddItemVehicle(hashof("bati2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("ruffian"), Option_SpawnVehicle);
	AddItemVehicle(hashof("daemon"), Option_SpawnVehicle);
	AddItemVehicle(hashof("double"), Option_SpawnVehicle);
	AddItemVehicle(hashof("pcj"), Option_SpawnVehicle);
	AddItemVehicle(hashof("vader"), Option_SpawnVehicle);
	AddItemVehicle(hashof("faggio2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("hexer"), Option_SpawnVehicle);
	AddItemVehicle(hashof("nemesis"), Option_SpawnVehicle);
	AddItemVehicle(hashof("thrust"), Option_SpawnVehicle);
	AddItemVehicle(hashof("sovereign"), Option_SpawnVehicle);
	AddItemVehicle(hashof("innovation"), Option_SpawnVehicle);
	AddItemVehicle(hashof("hakuchou"), Option_SpawnVehicle);
	AddItemVehicle(hashof("enduro"), Option_SpawnVehicle);
	AddItemVehicle(hashof("lectro"), Option_SpawnVehicle);
	AddItemVehicle(hashof("vindicator"), Option_SpawnVehicle);

	#ifdef __YSC__
	if (is_dlc_present(Update_mpStunt))
	{
		AddItemVehicle(VEHICLE_GARGOYLE, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_CLIFFHANGER, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BF400, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpBiker))
	{
		AddItemVehicle(VEHICLE_FAGGIO3, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_FAGGIO, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_VORTEX, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_AVARUS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SANCTUS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_HAKUCHOU2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_NIGHTBLADE, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_CHIMERA, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_ESSKEY, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_WOLFSBANE, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_ZOMBIEA, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_ZOMBIEB, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DEFILER, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DAEMON2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_RATBIKE, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SHOTARO, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_MANCHEZ, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpImportExport))
	{
		AddItemVehicle(VEHICLE_DIABLOUS, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DIABLOUS2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_FCR, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_FCR2, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Bicycle()
{
	SetHeader("Cycles");
	AddItemVehicle(hashof("scorcher"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tribike"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tribike2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tribike3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("fixter"), Option_SpawnVehicle);
	AddItemVehicle(hashof("cruiser"), Option_SpawnVehicle);
	AddItemVehicle(hashof("BMX"), Option_SpawnVehicle);
	#ifdef __YSC__

	#endif
}
void Menu__VehicleSpawner_Plane()
{
	SetHeader("Planes");
	AddItemVehicle(hashof("blimp"), Option_SpawnVehicle);
	AddItemVehicle(hashof("cuban800"), Option_SpawnVehicle);
	AddItemVehicle(hashof("duster"), Option_SpawnVehicle);
	AddItemVehicle(hashof("stunt"), Option_SpawnVehicle);
	AddItemVehicle(hashof("mammatus"), Option_SpawnVehicle);
	AddItemVehicle(hashof("jet"), Option_SpawnVehicle);
	AddItemVehicle(hashof("shamal"), Option_SpawnVehicle);
	AddItemVehicle(hashof("luxor"), Option_SpawnVehicle);
	AddItemVehicle(hashof("titan"), Option_SpawnVehicle);
	AddItemVehicle(hashof("lazer"), Option_SpawnVehicle);
	AddItemVehicle(hashof("cargoplane"), Option_SpawnVehicle);
	AddItemVehicle(hashof("velum"), Option_SpawnVehicle);
	AddItemVehicle(hashof("vestra"), Option_SpawnVehicle);
	AddItemVehicle(hashof("besra"), Option_SpawnVehicle);
	AddItemVehicle(hashof("miljet"), Option_SpawnVehicle);
	AddItemVehicle(hashof("velum2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("hydra"), Option_SpawnVehicle);
	AddItemVehicle(hashof("luxor2"), Option_SpawnVehicle);

	
	#ifdef __YSC__
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_DODO, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_BLIMP2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_NIMBUS, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Helicopter()
{
	SetHeader("Helicopters");
	AddItemVehicle(hashof("annihilator"), Option_SpawnVehicle);
	AddItemVehicle(hashof("buzzard"), Option_SpawnVehicle);
	AddItemVehicle(hashof("buzzard2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("cargobob"), Option_SpawnVehicle);
	AddItemWithParam("Medical Cargobob", hashof("cargobob2"), Option_SpawnVehicle);
	AddItemWithParam("Trevor's Cargobob", hashof("cargobob3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("skylift"), Option_SpawnVehicle);
	AddItemVehicle(hashof("polmav"), Option_SpawnVehicle);
	AddItemVehicle(hashof("maverick"), Option_SpawnVehicle);
	AddItemVehicle(hashof("frogger"), Option_SpawnVehicle);
	AddItemWithParam("Trevor's Frogger", hashof("frogger2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("swift"), Option_SpawnVehicle);
	AddItemVehicle(hashof("savage"), Option_SpawnVehicle);
	AddItemVehicle(hashof("valkyrie"), Option_SpawnVehicle);
	AddItemVehicle(hashof("swift2"), Option_SpawnVehicle);
	#ifdef __YSC__
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemWithParam("Cargobob 2-Seater", VEHICLE_CARGOBOB4, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SUPERVOLITO, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SUPERVOLITO2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_VALKYRIE2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_VOLATUS, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Boat()
{
	SetHeader("Boats");
	AddItemVehicle(hashof("squalo"), Option_SpawnVehicle);
	AddItemVehicle(hashof("marquis"), Option_SpawnVehicle);
	AddItemVehicle(hashof("dinghy"), Option_SpawnVehicle);
	AddItemWithParam("Dinghy 2-Seater", hashof("dinghy2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("jetmax"), Option_SpawnVehicle);
	AddItemVehicle(hashof("predator"), Option_SpawnVehicle);
	AddItemVehicle(hashof("tropic"), Option_SpawnVehicle);
	AddItemVehicle(hashof("seashark"), Option_SpawnVehicle);
	AddItemWithParam("Seashark Lifeguard", hashof("seashark2"), Option_SpawnVehicle);
	AddItemVehicle(hashof("submersible"), Option_SpawnVehicle);
	AddItemVehicle(hashof("suntrap"), Option_SpawnVehicle);
	AddItemVehicle(hashof("speeder"), Option_SpawnVehicle);
	AddItemWithParam("Dinghy (Heist)", hashof("dinghy3"), Option_SpawnVehicle);
	AddItemVehicle(hashof("toro"), Option_SpawnVehicle);

	
	#ifdef __YSC__
	if (is_dlc_present(Update_spUpgrade))
	{
		AddItemVehicle(VEHICLE_SUBMERSIBLE2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpApartment))
	{
		AddItemVehicle(VEHICLE_TORO2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SEASHARK3, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_DINGHY4, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_TROPIC2, Option_SpawnVehicle);
		AddItemVehicle(VEHICLE_SPEEDER2, Option_SpawnVehicle);
	}
	if (is_dlc_present(Update_mpExecutive))
	{
		AddItemVehicle(VEHICLE_TUG, Option_SpawnVehicle);
	}
	#endif
}
void Menu__VehicleSpawner_Trailer()
{
	SetHeader("Trailers");
	AddItemVehicle(hashof("boattrailer"), Option_SpawnVehicle);
	AddItemWithParam("Army Tanker", hashof("armytanker"), Option_SpawnVehicle);
	AddItemWithParam("Army Flatbed", hashof("armytrailer"), Option_SpawnVehicle);
	AddItemWithParam("Army Flatbed With Cutter", hashof("armytrailer2"), Option_SpawnVehicle);
	AddItemWithParam("Freight Train Flatbed", hashof("freighttrailer"), Option_SpawnVehicle);
	AddItemWithParam("Mobile Home", hashof("proptrailer"), Option_SpawnVehicle);
	AddItemWithParam("Grain Trailer", hashof("graintrailer"), Option_SpawnVehicle);
	AddItemWithParam("Hay Bale Trailer", hashof("baletrailer"), Option_SpawnVehicle);
	AddItemWithParam("Shipping Container Trailer", hashof("docktrailer"), Option_SpawnVehicle);
	AddItemWithParam("Metal/Tarp Covered Trailer", hashof("trailers"), Option_SpawnVehicle);
	AddItemWithParam("Misc Livery Trailer", hashof("trailers2"), Option_SpawnVehicle);
	AddItemWithParam("Big Goods Trailer", hashof("trailers3"), Option_SpawnVehicle);
	AddItemWithParam("Fame or Shame Trailer", hashof("tvtrailer"), Option_SpawnVehicle);
	AddItemWithParam("Farm Cultivator", hashof("raketrailer"), Option_SpawnVehicle);
	AddItemWithParam("Tanker", hashof("tanker"), Option_SpawnVehicle);
	AddItemWithParam("Log Trailer", hashof("trailerlogs"), Option_SpawnVehicle);
	AddItemWithParam("Empty Car Carrier Trailer", hashof("tr2"), Option_SpawnVehicle);
	AddItemWithParam("Marquis Trailer", hashof("tr3"), Option_SpawnVehicle);
	AddItemWithParam("Super Car Carrier Trailer", hashof("tr4"), Option_SpawnVehicle);
	AddItemWithParam("Flatbed", hashof("trflat"), Option_SpawnVehicle);
	AddItemWithParam("Small Construction Trailer", hashof("trailersmall"), Option_SpawnVehicle);
	AddItemWithParam("Tanker (No Livery)", hashof("tanker2"), Option_SpawnVehicle);
	#ifdef __YSC__

	#endif
}
void Menu__VehicleSpawner_Rail()
{
	SetHeader("Trains");
	AddItemVehicle(hashof("cablecar"), Option_SpawnVehicle);
	AddItemWithParam("Freight Train", hashof("freight"), Option_SpawnVehicle);
	AddItemWithParam("Train Well Car", hashof("freightcar"), Option_SpawnVehicle);
	AddItemWithParam("Train Container", hashof("freightcont1"), Option_SpawnVehicle);
	AddItemWithParam("Train Container (livery)", hashof("freightcont2"), Option_SpawnVehicle);
	AddItemWithParam("Train Boxcar", hashof("freightgrain"), Option_SpawnVehicle);
	AddItemWithParam("Train Fuel Tank Car", hashof("tankercar"), Option_SpawnVehicle);
	AddItemWithParam("Metro Train", hashof("metrotrain"), Option_SpawnVehicle);
	#ifdef __YSC__

	#endif
}
void Menu__VehicleSpawner()
{
	SetHeader("Vehicle Spawner");
	AddItemMenu("Sports", Menu__VehicleSpawner_Sports);
	AddItemMenu("Super", Menu__VehicleSpawner_Super);
	AddItemMenu("Coupes", Menu__VehicleSpawner_Coupes);
	AddItemMenu("Compacts", Menu__VehicleSpawner_Compacts);
	AddItemMenu("Sedans", Menu__VehicleSpawner_Sedans);
	AddItemMenu("Sports Classics", Menu__VehicleSpawner_SportsClassic);
	AddItemMenu("Muscle", Menu__VehicleSpawner_Muscle);
	AddItemMenu("SUVs", Menu__VehicleSpawner_Suv);
	AddItemMenu("Vans", Menu__VehicleSpawner_Van);
	AddItemMenu("Off-Road", Menu__VehicleSpawner_Offroad);
	AddItemMenu("Commercial", Menu__VehicleSpawner_Commercial);
	AddItemMenu("Service", Menu__VehicleSpawner_Service);
	AddItemMenu("Utility", Menu__VehicleSpawner_Utility);
	AddItemMenu("Industrial", Menu__VehicleSpawner_Industrial);
	AddItemMenu("Emergency", Menu__VehicleSpawner_Emergency);
	AddItemMenu("Military", Menu__VehicleSpawner_Military);
	AddItemMenu("Motorcycles", Menu__VehicleSpawner_Motorcycle);
	AddItemMenu("Cycles", Menu__VehicleSpawner_Bicycle);
	AddItemMenu("Planes", Menu__VehicleSpawner_Plane);
	AddItemMenu("Helicopters", Menu__VehicleSpawner_Helicopter);
	AddItemMenu("Boats", Menu__VehicleSpawner_Boat);
	AddItemMenu("Trailers", Menu__VehicleSpawner_Trailer);
	AddItemMenu("Trains", Menu__VehicleSpawner_Rail);
	#ifdef __YSC__

	#endif
}
#pragma endregion

void Menu__VehicleOptions()
{
	SetHeader("Vehicle Options");
	AddItemMenu("Vehicle Spawner", Menu__VehicleSpawner);
	AddItemBoolAdvanced("Vehicle Helper", false, "Makes vehicle invincible.", nullptr, false, bit_test(MenuLoopedBitset, MB_VehicleHelper), Option_VehicleHelper, nullptr);
}
void Menu__MiscOptions()
{
	SetHeader("Misc Options");
	AddItemBoolAdvanced("Fly Mod", false, "Hold X and press Left Stick to use Fly Mod.", nullptr, false, bit_test(MenuLoopedBitset, MB_FlyMod), Option_FlyMod, nullptr);
}
void Menu__DebugOptions()
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
	DisableControl(2, INPUT_VEHICLE_LOOK_BEHIND);
	DisableControl(2, INPUT_LOOK_BEHIND);
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
		DisableControl(2, INPUT_VEHICLE_LOOK_BEHIND);
		DisableControl(2, INPUT_LOOK_BEHIND);
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
	

}
#pragma endregion




