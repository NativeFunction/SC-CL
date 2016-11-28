#pragma once

bool LoadTextureDictionary(char* DictionaryName);
void CheckTextureDictionary(char* DictionaryName);
bool InitScaleformMovie(char* MovieName, int* SavedScaleformId);
void CheckScaleformMovie(char* MovieName, int* SavedScaleformId);
Size GetSizeFromTexture(char* DictionaryName, char* TextureName);
Size GetSizeFromResolution(vector2 Resolution);
float GetFloatWidth(float Value, Font FontType, float Scale);
float GetIntWidth(int Value, Font FontType, float Scale);
float GetStringWidth(char* Value, Font FontType, float Scale);
float GetStringHeight(char* Value, Font FontType, float Scale, float Wrap, vector2 Pos);
void Break(char* str);

