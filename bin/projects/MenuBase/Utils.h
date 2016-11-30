#pragma once

bool LoadTextureDictionary(const char* DictionaryName);
void CheckTextureDictionary(const char* DictionaryName);
bool InitScaleformMovie(const char* MovieName, int* SavedScaleformId);
void CheckScaleformMovie(const char* MovieName, int* SavedScaleformId);
Size GetSizeFromTexture(const char* DictionaryName, const char* TextureName);
Size GetSizeFromResolution(vector2 Resolution);
float GetFloatWidth(float Value, Font FontType, float Scale);
float GetIntWidth(int Value, Font FontType, float Scale);
float GetStringWidth(const char* Value, Font FontType, float Scale);
float GetStringHeight(const char* Value, Font FontType, float Scale, float Wrap, vector2 Pos);
void Break(const char* str);
void Notify(const char* str);

//TODO: create ui for assert because print cant hold the amount of text you need to print
#define assert(expression) do { if (!(expression)) { wait(0); while (!is_disabled_control_just_pressed(2, INPUT_FRONTEND_ACCEPT)) { _set_text_entry_2("CELL_CL04"); add_text_component_substring_player_name("Assertion failed!~n~~n~File: "); add_text_component_substring_player_name(__FILE__); add_text_component_substring_player_name(straddiGlobal("Line ", __LINE__)); add_text_component_substring_player_name("~n~~n~Expression: "); add_text_component_substring_player_name(#expression); _draw_subtitle_timed(1000, 1); wait(0); } wait(0); } } while (false)
