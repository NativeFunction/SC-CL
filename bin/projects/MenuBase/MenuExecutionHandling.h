#pragma once
#include "MenuUiHandling.h"


#define MaxAsyncParams 10
#define Async(Func) (bool(*)(uint,...))Func
#define AsyncParam(...) (int[MaxAsyncParams]){__VA_ARGS__}

void ExecutionEntry();//MenuUiHandling uses MainMenu 
void LoopedExecutionEntry();
void InitMenuExecution();
void AsynchronousLoop();

//For Description and AlternateExecution use nullptr for disabled
void SetHeaderAdvanced(char* HeaderText, bool IsItemGxt);
void AddItemAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)());
void AddItemIntAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), void(*AlternateCallback)());
void AddItemFloatAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)(), void(*AlternateCallback)());
void AddItemBoolAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool StartIndex, void(*Callback)(), void(*AlternateCallback)());
void AddItemEnumAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)());
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
bool UpdateBoolConditional(bool Condition, bool* BoolToSet);
bool UpdateBoolConditionalCeil(bool Condition, bool* BoolToSet);
bool UpdateBoolConditionalFloor(bool Condition, bool* BoolToSet);
void StartAsynchronousFunction(bool(*AsynchronousFunction)(uint CurrentFrame, ...), const uint ParamCount, uint FramesToLoop, int Params[MaxAsyncParams]);

Page* DEBUG__GetContainer();