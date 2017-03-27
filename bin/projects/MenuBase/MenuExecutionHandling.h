#pragma once
#include "MenuUiHandling.h"


#define MaxAsyncParams 10
#define Async(Func) (bool(*)(uint,...))Func
#define AsyncParam(...) (int[MaxAsyncParams]){__VA_ARGS__}

typedef struct { int Items[MaxDynamicItems]; } DynamicIdArray;

//For Description and AlternateExecution use nullptr for disabled
#pragma region AdvancedItems
//if DynamicChecker is enabled then menu items have to be dynamic items
void SetHeaderForwardedAdvanced(bool(*DynamicChecker)(int Id));
//if DynamicChecker is enabled then menu items have to be dynamic items
void SetHeaderAdvanced(const char* HeaderText, bool IsItemGxt, bool(*DynamicChecker)(int Id));
void AddItemAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, void(*Callback)(), void(*AlternateCallback)());
void AddItemIntAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, bool HasConformation, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), void(*AlternateCallback)());
void AddItemFloatAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, bool HasConformation, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)(), void(*AlternateCallback)());
void AddItemBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, bool StartIndex, void(*Callback)(), void(*AlternateCallback)());
void AddItemEnumAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, bool HasConformation, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), const char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)());
void AddItemMenuAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, bool IsDisabled, bool HasConformation, bool ForwardsHeaderText, void(*Callback)());
void AddItemMenuWithParamAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, bool IsDisabled, bool HasConformation, bool ForwardsHeaderText, int Param, void(*Callback)());
void AddItemWithParamAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, int Param, void(*Callback)(), void(*AlternateCallback)());
void AddItemIntBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, int MinValue, int MaxValue, int StartIndex, int Precision, bool BoolStartIndex, void(*Callback)(), void(*AlternateCallback)());
void AddItemEnumBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, int MinValue, int MaxValue, int StartIndex, int Precision, bool BoolStartIndex, void(*Callback)(), const char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)());
void AddItemFloatBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, float MinValue, float MaxValue, float StartIndex, float Precision, bool BoolStartIndex, void(*Callback)(), void(*AlternateCallback)());
void AddItemPlayerAdvanced(int PlayerId, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, void(*Callback)(), void(*AlternateCallback)());
void AddItemVehicleAdvanced(int VehicleHash, const char* Description, const char* AltExeControlText, bool IsDisabled, bool HasConformation, void(*Callback)(), void(*AlternateCallback)());
#pragma endregion

#pragma region NormalItems
void SetHeaderForwarded();
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
void AddItemVehicle(int VehicleHash, void(*Callback)());
#pragma endregion

#pragma region DynamicNormalItems
void AddItemMenuDynamicAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, bool IsDisabled, bool HasConformation, bool ForwardsHeaderText, int DynamicId, void(*Callback)());
void AddItemMenuDynamic(const char* ItemText, int DynamicId, void(*Callback)());
void AddItemDynamic(const char* ItemText, int DynamicId, void(*Callback)());
void AddItemPlayer(int PlayerId, void(*Callback)());
#pragma endregion

#pragma region ExternalMenuCommands
DynamicIdArray DumpDynamicIds();
int GetCurrentItemCount();
void SetCurrentMenuInvalid(bool value, const char* Reason);
bool WasLastMenuDirectionForward();
ItemContainer* GetCurrentItem();
//Note: Only works in the forward direction
ItemContainer* GetCurrentItemFromLastMenu();
int GetLastDynamicId();
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
//[Do not use] This is for menu ui testing
Page* DEBUG__GetContainer();
#pragma endregion

#pragma region InternalMenuCommands
//ExecutionEntry uses MainMenu as entry
void ExecutionEntry();
void LoopedExecutionEntry();
void InitMenuExecution();
void AsynchronousLoop();
#pragma endregion