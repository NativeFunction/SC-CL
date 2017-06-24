#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"

//bitfield overflow 1 bit = 2 = 1


#if TARGET == TARGET_GTAV

const int j = 40000;

struct MenuToggles
{
	//unsigned int start;
	unsigned Invulnerability : 1;
	unsigned InfiniteDeadeye : 8;
	unsigned FlyMod : 1;
	unsigned BlazingGuns : 1;
	unsigned InfiniteHorseStamina : 1;
	unsigned ExplosiveWeapons : 1;
	unsigned endi : 19;

	unsigned startnbs : 1;
	//unsigned int end;
} MenuToggles = { 1, 2, 4, 0, 5, 10, j };


void main()
{
	//do init str/uni bitfield
	//do init str/uni bitfield gbl
	//do str/uni bitfield gbl
	int t = 0b00000001111101000001001111010010;
	
	
	MenuToggles.startnbs = true;
	MenuToggles.endi = 138371;
	MenuToggles.Invulnerability = true;
	MenuToggles.Invulnerability = false;
	MenuToggles.InfiniteDeadeye = 239;
	MenuToggles.ExplosiveWeapons = true;
	MenuToggles.InfiniteDeadeye = 200;
	
}

#elif TARGET == TARGET_GTAIV
//function pointer need fixing
//jump table needs fixing
//

void print(char *text) { CLEAR_PRINTS(); PRINT_STRING_WITH_LITERAL_STRING_NOW("string", text, 5000, 1); }
void print_int(int number) { CLEAR_PRINTS(); PRINT_WITH_NUMBER("number", number, 5000, 1); }
void print_two(char* text, char* text2) { CLEAR_PRINTS(); PRINT_STRING_WITH_TWO_LITERAL_STRINGS_NOW("STRTNM3", text, text2, 5000, 1); }


int func(int var)
{
	print("Hello World", var);
	return 1000;
}

void main()
{
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();

	int(*funcCall)(int) = func;


	print_int(funcCall);
	WAIT(1000);


	funcCall(3000);

}
#elif TARGET == TARGET_RDR

GUIWindow MainWindow;

void Print(const char* Str, float SecTime, bool IsStringliteral)
{
	_clear_prints();
	_print_subtitle(Str, SecTime, IsStringliteral, 2, 1, 0, 0, 0);
}
Actor GetPlayerActor()
{
	if (_is_actor_id_valid(0))
		return get_player_actor(0);
	else 
		return 0;
}
Controller GetPlayerController()
{
	if (_is_actor_id_valid(0))
		return _get_actor_controller(0);
	else 
		return 0;
}
Actor CreateActor(Layout Layout, const char* ActorName, eActor ActorID, vector3 Position)
{
	Actor CreatedActor = find_actor_in_layout(Layout, ActorName);
	if (is_actor_valid(find_actor_in_layout(Layout, ActorName)))
		destroy_actor(CreatedActor);

	bool ActorLoaded = false;
	CreatedActor = create_actor_in_layout(Layout, ActorName, ActorID, Position, Vector3(0, 0, 0));

	for (int i = 0; i < 500; i++)
	{
		if (is_actor_valid(CreatedActor))
		{
			ActorLoaded = true;
			break;
		}
		wait(0);
	}

	if (ActorLoaded)
	{
		set_actor_rideable(CreatedActor, true);
		set_allow_ride_by_player(CreatedActor, true);


		if (is_actor_vehicle(CreatedActor))
		{
			enable_vehicle_seat(CreatedActor, 0, true);
			set_vehicle_allowed_to_drive(CreatedActor, true);
			set_vehicle_engine_running(CreatedActor, true);
			vehicle_set_handbrake(CreatedActor, false);
			start_vehicle(CreatedActor);

			set_actor_in_vehicle(GetPlayerActor(), CreatedActor, 0);
		}
		release_actor(CreatedActor);
		return CreatedActor;
	}
	else
	{
		Print("Actor took too long to load.", 5, 1);
	}

	return 0;
}


void CheckUiInput(Object OptionState)
{
	if (!is_object_valid(OptionState))
		return;

	if (decor_check_string(OptionState, "Param", "RM_MainMenu_Selected"))
	{
		switch (ui_get_selected_index("RM_MainMenu", 0))
		{
			case 0:
			Print("rm_helloworld", 5, 0);
			break;
			case 1:
			Print("rm_test", 5, 0);
			break;
		}
	}
}
void FUIEventIterator()
{
	Layout Formations = find_named_layout("Formations");
	if (!_is_layout_valid(Formations))
	{
		Print("Failed to find FUI layout. Script will not receive FUI events", 5, true);
		return;
	}
	
	Iterator FormationsIterator = create_object_iterator(Formations);
	if (!is_iterator_valid(FormationsIterator))
	{
		Print("Failed to find FUI iterator. Script will not receive FUI events", 5, true);
		return;
	}

	iterate_on_object_type(FormationsIterator, 3);
	iterate_in_set(FormationsIterator, _get_iteration_set(75));

	Object CurrentObject = start_object_iterator(FormationsIterator);

	while (true)
	{
		if (is_object_valid(CurrentObject))
		{
			if (is_object_valid(unk_0x184BD1BC(CurrentObject)))
				CheckUiInput(CurrentObject);

			CurrentObject = object_iterator_next(FormationsIterator);
		}
		else
		{
			destroy_iterator(FormationsIterator);
			return;
		}
	}
}

int ParseGUIMenu(int* SelectedIndex, SizedArray Items, const char* MenuName, int UNK0)
{





	unk_0x45589499(1);

	*(SelectedIndex + 3) = -1;
	*(SelectedIndex + 4) = UNK0;


	int UnkArray0[5];
	float UnkArray1[15];

	//Function_26
	UnkArray1[9] = 100.0f;
	UnkArray1[10] = 110.0f;
	UnkArray1[11] = 1.0f;
	UnkArray1[12] = 1.0f;
	UnkArray1[13] = 1.0f;
	UnkArray1[14] = 1.6f;

	UnkArray1[8] = 0;
	UnkArray1[4] = 0;

	UnkArray0[4] = 0;
	UnkArray0[1] = 10;
	UnkArray0[3] = 3;
	UnkArray0[0] = 0;
	UnkArray0[2] = 0;

	//Function_27
	int UnkSize = (GetSizedArraySize(Items) / UnkArray1[0]) / UnkArray1[3];


	//Function_28
	const char* MenuTitle = "DB_MENU_TITLE";
	GUIWindow Win = _gui_get_window(MainWindow, MenuTitle);//instead of global might need to init menu myself
	int CurrentTextHandle;
	
	if (!gui_window_valid(Win))
	{
		CreateSizedArray(float, WinPos, 3, 50, 1280, 150);
		CurrentTextHandle = gui_make_text(MainWindow, &WinPos, MenuTitle, "berrylium", 2);
	}

	float ColorArea[4] = { 1, 1, 1, 1 };//these were params

	gui_set_text(CurrentTextHandle, MenuName);
	gui_set_text_color(CurrentTextHandle, ColorArea);
	gui_set_text_justify(CurrentTextHandle, true);


	//Function_29
	static int StaticMenuHandle[7];//5 = (left - right index)

	
	unk_0x3C2D93C1(0.1f, 0.9f, "Previous Page<-Dpad->Next Page", 1, 1, 1, 1);

	for (int i = 0; i < 5; i++)
	{
		char buffer[16] = "DB_MENU_";

		
		unk_0x47EF426D(GetSizedArrayItem(Items, const char*, i));
		stradd(buffer, unk_0x47EF426D(GetSizedArrayItem(Items, const char*, i)), 16);

		GUIWindow Win = _gui_get_window(MainWindow, buffer);
		if (gui_window_valid(Win))
		{
			gui_set_text(Win, " ");
		}
		else
			Print("Window Not Valid", 2, true);

		//if (wasselected)
		//{
		//	
		//	unk_0x45589499(0);
		//	unk_0x5AC72FCC(1);
		//	return i;
		//}
	}

	unk_0x45589499(0);
	return -1;
}
void GUITestInit()
{
	int SelectedIndex;
	CreateSizedArray(const char*, MenuItems, 5, "Pas", "Fai", "Can", "DaF", "Las");
	ParseGUIMenu(&SelectedIndex, &MenuItems, "RDR MISSION MENU", 0);

}

Layout GlobalLayout;

void main()
{
	CreateSizedArray(float, WinPos, 3, 50, 1280, 150);
	MainWindow = gui_make_window(gui_main_window(), 0, "PlayerGUI", "");
	gui_make_text(MainWindow, &WinPos, "clock", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "calendar", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "deed", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "ambdebug", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "pop", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "stream", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "pursuit", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "pursuitclock", "berrylium", 2);
	gui_make_text(MainWindow, &WinPos, "pursuitcalendar", "berrylium", 2);

	add_persistent_script(_get_id_of_this_script());
	GlobalLayout = create_layout("GlobalLayout");
	bool GUITest = false;

	while (true)
	{
		set_actor_invulnerability(GetPlayerActor(), true);
		set_deadeye_timescale(0, 0.1);
		set_infinite_deadeye(0, 1);
		set_deadeye_damage_scaling(0, 5);

		if (_is_key_pressed(KEY_1))
		{
			vector3 PlayerPosition;
			get_position(GetPlayerActor(), &PlayerPosition);
			CreateActor(GlobalLayout, "Actor0", ACTOR_VEHICLE_Car01, PlayerPosition);
		}
		else if (_is_key_pressed(KEY_2))
		{
			GUITest = true;
		}
		else if (_is_key_pressed(KEY_3))
		{
			Print(__TIMESTAMP__, 5, 1);
		}
		else if (_is_key_pressed(KEY_4))
		{
			request_asset("systemTest/PerformanceTests/test03_firefight", 4);
			wait(5000);
			launch_new_script("systemTest/PerformanceTests/test03_firefight", 0);
		}

		if(GUITest)
			GUITestInit();

		wait(0);
	}
}

#endif