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
