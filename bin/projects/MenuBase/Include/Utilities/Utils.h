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
bool IsPlayerInGame(int PlayerIndex);
int FindFreeCarSeat(Vehicle VehicleToFindSeat);
Vehicle GetCurrentVehicle();
void Assert(const char* File, int Line, const char* Expression);


//TODO: create ui for assert because print cant hold the amount of text you need to print
#define assert(expression) do { if (!(expression)) { Assert(__FILE__, __LINE__, #expression); } } while (false)

#define PlayMenuSound(SoundName) play_sound_frontend(-1, SoundName, "HUD_FRONTEND_DEFAULT_SOUNDSET", true)

