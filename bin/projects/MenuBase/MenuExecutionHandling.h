#pragma once
#include "MenuUiHandling.h"


#define MaxAsyncParams 10
#define Async(Func) (bool(*)(uint,...))Func
#define AsyncParam(...) (int[MaxAsyncParams]){__VA_ARGS__}

typedef struct { int Items[MaxDynamicItems]; } DynamicIdArray;

void ExecutionEntry();//MenuUiHandling uses MainMenu 
void LoopedExecutionEntry();
void InitMenuExecution();
void AsynchronousLoop();

//For Description and AlternateExecution use nullptr for disabled

//if IsMenuDynamic then menu items have to be dynamic items
void SetHeaderAdvanced(const char* HeaderText, bool IsItemGxt, bool IsMenuDynamic);
void AddItemAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)());
void AddItemIntAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), void(*AlternateCallback)());
void AddItemFloatAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)(), void(*AlternateCallback)());
void AddItemBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool StartIndex, void(*Callback)(), void(*AlternateCallback)());
void AddItemEnumAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), const char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)());
void AddItemMenuAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, bool IsDisabled, void(*Callback)());
void AddItemMenuWithParamAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, bool IsDisabled, int Param, void(*Callback)());
void AddItemWithParamAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, int Param, void(*Callback)(), void(*AlternateCallback)());
void AddItemIntBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, int MinValue, int MaxValue, int StartIndex, int Precision, bool BoolStartIndex, void(*Callback)(), void(*AlternateCallback)());
void AddItemEnumBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, int MinValue, int MaxValue, int StartIndex, int Precision, bool BoolStartIndex, void(*Callback)(), const char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)());
void AddItemFloatBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, float MinValue, float MaxValue, float StartIndex, float Precision, bool BoolStartIndex, void(*Callback)(), void(*AlternateCallback)());
void AddItemPlayerAdvanced(int PlayerId, const char* Description, const char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)());
void AddItemVehicleAdvanced(int VehicleHash, const char* Description, const char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)());


void SetHeader(const char* HeaderText);
void AddItem(const char* ItemText, void(*Callback)());
void AddItemInt(const char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)());
void AddItemFloat(const char* ItemText, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)());
void AddItemBool(const char* ItemText, bool StartIndex, void(*Callback)());
void AddItemEnum(const char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)(), const char*(*EnumParser)(int ItemIndex));
void AddItemMenu(const char* ItemText, void(*Callback)());
void AddItemMenuWithParam(const char* ItemText, int Param, void(*Callback)());
void AddItemWithParam(const char* ItemText, int Param, void(*Callback)());
void AddItemIntBool(const char* ItemText, int MinValue, int MaxValue, int StartIndex, bool BoolStartIndex, void(*Callback)());
void AddItemEnumBool(const char* ItemText, int MinValue, int MaxValue, int StartIndex, bool BoolStartIndex, void(*Callback)(), const char*(*EnumParser)(int ItemIndex));
void AddItemFloatBool(const char* ItemText, float MinValue, float MaxValue, float StartIndex, float Precision, bool BoolStartIndex, void(*Callback)());
void AddItemPlayer(int PlayerId, void(*Callback)(), char* netTestName);
void AddItemVehicle(int VehicleHash, void(*Callback)());

DynamicIdArray DumpDynamicIds();
int GetCurrentItemCount();
void SetCurrentMenuInvalid(bool value);
bool WasLastMenuDirectionForward();
ItemContainer* GetCurrentItem();
ItemContainer* GetCurrentItemFromLastMenu();
ItemContainer* GetCurrentItemAtIndex(int Index);
int FloatToPrecision(float Precision);
float PrecisionToFloat(int Precision);
int GetEnumParserValue(int ItemIndex);
bool GetItemRelativeToCursor(int Index, ItemContainer** Out);
bool GetItemByName(const char* Name, ItemContainer** Out);
bool UpdateBoolConditional(bool Condition, bool* BoolToSet);
bool UpdateBoolConditionalCeil(bool Condition, bool* BoolToSet);
bool UpdateBoolConditionalFloor(bool Condition, bool* BoolToSet);
void StartAsynchronousFunction(bool(*AsynchronousFunction)(uint CurrentFrame, ...), const uint ParamCount, uint FramesToLoop, int Params[MaxAsyncParams]);
int* GetExecutableAddress();

Page* DEBUG__GetContainer();