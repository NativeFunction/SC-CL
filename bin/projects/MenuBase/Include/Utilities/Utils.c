#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "common.h"

bool LoadTextureDictionary(const char* DictionaryName)
{
	if (has_streamed_texture_dict_loaded(DictionaryName))
		return true;

	request_streamed_texture_dict(DictionaryName, 0);

	for (int i = 0; i < 100; i++)
	{
		if (has_streamed_texture_dict_loaded(DictionaryName))
			return true;
		wait(0);
	}

	Warn("Unable to load texture dictionary.");
	return false;
}
void CheckTextureDictionary(const char* DictionaryName)
{
	//TODO: add bool to not request multiple times
	if (!has_streamed_texture_dict_loaded(DictionaryName))
		request_streamed_texture_dict(DictionaryName, 0);
}
bool InitScaleformMovie(const char* MovieName, int* SavedScaleformId)
{
	if (has_scaleform_movie_loaded(*SavedScaleformId))
		return true;

	*SavedScaleformId = request_scaleform_movie(MovieName);

	for (int i = 0; i < 100; i++)
	{
		if (has_scaleform_movie_loaded(*SavedScaleformId))
			return true;
		wait(0);
	}

	Warn("Unable to initialize scaleform.");
	return false;
}
void CheckScaleformMovie(const char* MovieName, int* SavedScaleformId)
{
	//TODO: add bool to not request multiple times
	if (has_scaleform_movie_loaded(*SavedScaleformId))
		*SavedScaleformId = request_scaleform_movie(MovieName);
}


Size GetSizeFromTexture(const char* DictionaryName, const char* TextureName)
{
	int ScreenRes[2];
	
	get_screen_resolution(&ScreenRes[0], &ScreenRes[1]);
	vector3 TextureRes = get_texture_resolution(DictionaryName, TextureName);
	return Vector2(TextureRes.x / (float)ScreenRes[0], TextureRes.y / (float)ScreenRes[1]);
}
Size GetSizeFromResolution(vector2 Resolution)
{
	int ScreenRes[2];
	get_screen_resolution(&ScreenRes[0], &ScreenRes[1]);
	return Vector2(Resolution.x / (float)ScreenRes[0], Resolution.y / (float)ScreenRes[1]);
}
float GetFloatWidth(float Value, Font FontType, float Scale)
{
	_begin_text_command_width("NUMBER");
	add_text_component_float(Value, 4);
	set_text_font(FontType);
	set_text_scale(1.0f, Scale);
	return _end_text_command_get_width(true);
}
float GetIntWidth(int Value, Font FontType, float Scale)
{
	_begin_text_command_width("NUMBER");
	add_text_component_integer(Value);
	set_text_font(FontType);
	set_text_scale(1.0f, Scale);
	return _end_text_command_get_width(true);
}
float GetStringWidth(const char* Value, Font FontType, float Scale)
{
	_begin_text_command_width("STRING");
	add_text_component_substring_player_name(Value);
	set_text_font(FontType);
	set_text_scale(1.0f, Scale);
	return _end_text_command_get_width(true);
}
float GetStringHeight(const char* Value, Font FontType, float Scale, float Wrap, vector2 Pos)
{
	set_text_font(FontType);
	set_text_wrap(0.0f, Wrap);
	set_text_scale(1.0f, Scale);
	_begin_text_command_line_count("STRING");
	add_text_component_substring_player_name(Value);

	return _get_text_scale_height(Scale, FontType) * (float)_end_text_command_get_line_count(Pos);
}
void Break(const char* str)
{
	//TODO: This breaks > char Buffer[256] = "~r~Breakpoint~s~: ";
	char Buffer[256];
	strcpy(Buffer, "~r~Breakpoint~s~: ", 255);
	stradd(Buffer, str, 255);

	wait(0);//a button press before break
	while (!is_disabled_control_just_pressed(2, INPUT_FRONTEND_ACCEPT))
	{
		print(Buffer, 1000);
		wait(0);
	}
	wait(0);//a button press after break
}
void Notify(const char* str)
{
	_set_notification_text_entry("STRING");
	add_text_component_substring_player_name(str);
	_draw_notification(false, true);
}
void PrintMult(const char* StrArr[10], int ms)
{
	begin_text_command_print("CELL_EMAIL_BCON");
	for (int i = 0; i < 10; i++)
	{
		if (StrArr[i])
			add_text_component_substring_player_name(StrArr[i]);
		else
			break;
	}
	end_text_command_print(ms, 1);
}
bool IsPlayerInGame(int PlayerIndex)
{
	return network_is_player_active(PlayerIndex) && does_entity_exist(get_player_ped(PlayerIndex));
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
vector3 GetCoordInFrontOfGameplayCam(float Range)
{
	vector3 GameplayCamRot = get_gameplay_cam_rot(2);
	vector3 GameplayCamCoord = get_gameplay_cam_coord();
	float Tan = Range * cos(GameplayCamRot.x);
	return Vector3(Tan * sin(-GameplayCamRot.z) + GameplayCamCoord.x, Tan * cos(-GameplayCamRot.z) + GameplayCamCoord.y, Range * sin(GameplayCamRot.x) + GameplayCamCoord.z);
}


void Assert(const char* File, int Line, const char* Expression)
{
	const int FileEndPos = get_length_of_literal_string(File);
	const int ExprEndPos = get_length_of_literal_string(File);
	wait(0);
	while (!is_disabled_control_just_pressed(2, INPUT_FRONTEND_ACCEPT))
	{
		set_text_centre(true);
		begin_text_command_display_text("CELL_EMAIL_BCON");
		add_text_component_substring_player_name("Assertion failed!~n~~n~File: ");


		for (int i = 0; i < FileEndPos; i += 99)
			add_text_component_substring_player_name(File + i);

		add_text_component_substring_player_name(straddiGlobal("~n~Line: ", Line));
		add_text_component_substring_player_name("~n~~n~Expression: ");

		for (int i = 0; i < ExprEndPos; i += 99)
			add_text_component_substring_player_name(Expression + i);

		end_text_command_display_text(Vector2(0.5f, 0.5f));
		wait(0);
	}
	wait(0);
}
