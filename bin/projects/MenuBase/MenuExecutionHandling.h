#pragma once
#include "MenuUiHandling.h"

void ExecutionEntry();//MenuUiHandling uses MainMenu 
void InitMenuExecution();

void SetHeaderAdvanced(char* HeaderText, bool IsItemGxt);
void AddItemAdvanced(char* ItemText, bool IsItemGxt, char* Description, bool IsDisabled, void(*Callback)());
void AddItemIntAdvanced(char* ItemText, bool IsItemGxt, char* Description, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)());
void AddItemFloatAdvanced(char* ItemText, bool IsItemGxt, char* Description, bool IsDisabled, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)());
void AddItemBoolAdvanced(char* ItemText, bool IsItemGxt, char* Description, bool IsDisabled, bool StartIndex, void(*Callback)());
void AddItemEnumAdvanced(char* ItemText, bool IsItemGxt, char* Description, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), char*(*EnumParser)(int ItemIndex));
void AddItemMenuAdvanced(char* ItemText, bool IsItemGxt, char* Description, bool IsDisabled, void(*Callback)());

void SetHeader(char* HeaderText);
void AddItem(char* ItemText, void(*Callback)());
void AddItemInt(char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)());
void AddItemFloat(char* ItemText, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)());
void AddItemBool(char* ItemText, bool StartIndex, void(*Callback)());
void AddItemEnum(char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)(), char*(*EnumParser)(int ItemIndex));
void AddItemMenu(char* ItemText, void(*Callback)());


ItemContainer* GetCurrentItem();
int FloatToPrecision(float Precision);
float PrecisionToFloat(int Precision);
int GetEnumParserValue(int ItemIndex);
bool GetItemRelativeToCursor(int Index, ItemContainer** Out);
bool GetItemByName(char* Name, ItemContainer** Out);

Page* DEBUG__GetContainer();