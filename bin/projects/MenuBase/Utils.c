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
	_set_text_entry_for_width("NUMBER");
	add_text_component_float(Value, 4);
	set_text_font(FontType);
	set_text_scale(1.0f, Scale);
	return _get_text_screen_width(true);
}
float GetIntWidth(int Value, Font FontType, float Scale)
{
	_set_text_entry_for_width("NUMBER");
	add_text_component_integer(Value);
	set_text_font(FontType);
	set_text_scale(1.0f, Scale);
	return _get_text_screen_width(true);
}
float GetStringWidth(const char* Value, Font FontType, float Scale)
{
	_set_text_entry_for_width("STRING");
	add_text_component_substring_player_name(Value);
	set_text_font(FontType);
	set_text_scale(1.0f, Scale);
	return _get_text_screen_width(true);
}
float GetStringHeight(const char* Value, Font FontType, float Scale, float Wrap, vector2 Pos)
{
	set_text_font(FontType);
	set_text_wrap(0.0f, Wrap);
	set_text_scale(1.0f, Scale);
	_set_text_gxt_entry("STRING");
	add_text_component_substring_player_name(Value);

	return _get_text_scale_height(Scale, FontType) * (float)_get_text_screen_line_count(Pos);
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