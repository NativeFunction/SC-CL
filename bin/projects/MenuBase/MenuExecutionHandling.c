#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "common.h"

#include "Utils.h"
#include "MenuUiHandling.h"
#include "ItemExecution.h"
#include "MenuExecutionHandling.h"

#define GetRelativeCursorIndex Container->CursorIndex - Container->ItemStartIndex
#define this Container->Item[GetRelativeCursorIndex].Selection

static int AddItemCounter = 0;
static Page* Container;
static bool(*AsyncFunction)(uint CurrentFrame, ...);
static int AsyncFunctionParams[MaxAsyncParams];
static uint AsyncFunctionParamCount;
static uint AsyncFrameCount;//this is needed to provide nice 0 - FrameCountMax for CurrentFrame on AsynchronousFunction and for loading ui display slow start

#pragma region Reset
static void ResetCurrentItem()
{

	Container->Item[AddItemCounter].BitSet = null;
	Container->Item[AddItemCounter].Execute = nullptr;
	Container->Item[AddItemCounter].AlternateExecute = nullptr;
	Container->Item[AddItemCounter].Ui.ItemText = nullstr;
	Container->Item[AddItemCounter].Ui.Description = nullptr;
	Container->Item[AddItemCounter].Ui.AltExeControlText = nullptr;
	Container->Item[AddItemCounter].Selection.CursorIndex.Int = null;
	Container->Item[AddItemCounter].Selection.EndIndex.Int = null;
	Container->Item[AddItemCounter].Selection.ParseEnum = nullptr;
	Container->Item[AddItemCounter].Selection.Precision = 1.0f;
	Container->Item[AddItemCounter].Selection.StartIndex.Int = null;
	Container->Item[AddItemCounter].Selection.Type = MST_None;
}
#pragma endregion

#pragma region ItemTypes
void SetHeaderAdvanced(const char* HeaderText, bool IsItemGxt, bool IsMenuDynamic)
{
	AddItemCounter = 0;
	Container->TotalItemCount = 0;
	Container->IsCurrentMenuDynamic = IsMenuDynamic;

	Container->Ui.HeaderText = (char*)HeaderText;
	Container->Ui.IsHeaderGxt = IsItemGxt;
}
void AddItemAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemIntAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;

		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);

		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Int;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemFloatAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.StartIndex.Float = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Float = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Float = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Float;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool StartIndex, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Bool;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemEnumAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), const char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if(ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Enum;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		Container->Item[AddItemCounter].Selection.ParseEnum = EnumParser;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemMenuAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, bool IsDisabled, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		if(IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].Selection.Type = MST_Menu;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemWithParamAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, int Param, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);

		Container->Item[AddItemCounter].Selection.Type = MST_Param;
		Container->Item[AddItemCounter].Selection.Value.Int = Param;
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemIntBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, int MinValue, int MaxValue, int StartIndex, int Precision, bool BoolStartIndex, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;

		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		if (BoolStartIndex)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_BoolNumValue);

		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_IntBool;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemEnumBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, int MinValue, int MaxValue, int StartIndex, int Precision, bool BoolStartIndex, void(*Callback)(), const char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		if (BoolStartIndex)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_BoolNumValue);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_EnumBool;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		Container->Item[AddItemCounter].Selection.ParseEnum = EnumParser;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemFloatBoolAdvanced(const char* ItemText, bool IsItemGxt, const char* Description, const char* AltExeControlText, bool IsDisabled, float MinValue, float MaxValue, float StartIndex, float Precision, bool BoolStartIndex, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		if (BoolStartIndex)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_BoolNumValue);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.StartIndex.Float = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Float = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Float = StartIndex;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_FloatBool;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemPlayerAdvanced(int PlayerId, const char* Description, const char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)get_player_name(PlayerId);
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;
		Container->Item[AddItemCounter].Selection.Type = MST_Player;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemVehicleAdvanced(int VehicleHash, const char* Description, const char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Selection.Value.Int = VehicleHash;
		Container->Item[AddItemCounter].Ui.ItemText = (char*)get_display_name_from_vehicle_model(VehicleHash);
		Container->Item[AddItemCounter].Ui.Description = (char*)Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = (char*)AltExeControlText;
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);

		AddItemCounter++;
	}

	Container->TotalItemCount++;
}

void SetHeader(const char* HeaderText)
{
	AddItemCounter = 0;
	Container->TotalItemCount = 0;
	Container->IsCurrentMenuDynamic = false;

	Container->Ui.HeaderText = (char*)HeaderText;
}
void AddItem(const char* ItemText, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemInt(const char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Int;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemFloat(const char* ItemText, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Float = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Float = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Float = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Float;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemBool(const char* ItemText, bool StartIndex, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Bool;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemEnum(const char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)(), const char*(*EnumParser)(int ItemIndex))
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_Enum;
		Container->Item[AddItemCounter].Selection.ParseEnum = EnumParser;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemMenu(const char* ItemText, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].Selection.Type = MST_Menu;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemWithParam(const char* ItemText, int Param, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Selection.Type = MST_Param;
		Container->Item[AddItemCounter].Selection.Value.Int = Param;
		Container->Item[AddItemCounter].Execute = Callback;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemIntBool(const char* ItemText, int MinValue, int MaxValue, int StartIndex, bool BoolStartIndex, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (BoolStartIndex)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_BoolNumValue);
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_IntBool;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemEnumBool(const char* ItemText, int MinValue, int MaxValue, int StartIndex, bool BoolStartIndex, void(*Callback)(), const char*(*EnumParser)(int ItemIndex))
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (BoolStartIndex)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_BoolNumValue);
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_EnumBool;
		Container->Item[AddItemCounter].Selection.ParseEnum = EnumParser;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemFloatBool(const char* ItemText, float MinValue, float MaxValue, float StartIndex, float Precision, bool BoolStartIndex, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = (char*)ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Float = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Float = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Float = StartIndex;
		if (BoolStartIndex)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_BoolNumValue);
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = MST_FloatBool;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemPlayer(int PlayerId, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Selection.Value.Int = PlayerId;
		Container->Item[AddItemCounter].Ui.ItemText = (char*)get_player_name(PlayerId);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].Selection.Type = MST_Player;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemVehicle(int VehicleHash, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Selection.Value.Int = VehicleHash;
		Container->Item[AddItemCounter].Ui.ItemText = (char*)get_display_name_from_vehicle_model(VehicleHash);
		Container->Item[AddItemCounter].Execute = Callback;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}

//TODO: add bool group that sets all other bools on menu to 0 (enum expansion)
//TODO: add left right scroll bar with dds in timerbars.xtd
//TODO: add item spacer item
//TODO: support going back to selected index on back press

//TODO: add item small spacers between items to make items appear as buttons
//TODO: have cursor blink slow on selected item
//TODO: have cursor y size shrink on selection



#pragma endregion

#pragma region ExternalMenuCommands
void InitMenuExecution()
{
	Container = GetMenuContainer();
	if (Container == nullptr)
		Throw("Container Was Null");
}
inline ItemContainer* GetCurrentItem()
{
	return &Container->Item[GetRelativeCursorIndex];
}
float PrecisionToFloat(int Precision)
{
	switch (Precision)
	{
		default:
		case 0: return 1.0f;
		case 1: return 0.1f;
		case 2: return 0.01f;
		case 3: return 0.001f;
		case 4: return 0.0001f;
	}
}
int FloatToPrecision(float Precision)
{
	switch (reinterpretFloatToInt(Precision))
	{
		default:
		case 0x3F800000: return 0;
		case 0x3DCCCCCD: return 1;
		case 0x3C23D70A: return 2;
		case 0x3A83126F: return 3;
		case 0x38D1B717: return 4;
	}
}
inline int GetEnumParserValue(int ItemIndex)
{
	return Container->Item[ItemIndex].Selection.Value.Int;
}
bool GetItemRelativeToCursor(int Index, ItemContainer** Out)
{
	int IndexToSet = GetRelativeCursorIndex + Index;
	if (IndexToSet >= 0 && IndexToSet <= MaxDisplayableItems)
	{
		*Out = &Container->Item[IndexToSet];
		return true;
	}
	return false;
}
bool GetItemByName(const char* Name, ItemContainer** Out)
{
	for (int i = 0; i < MaxDisplayableItems; i++)
	{
		if (compare_strings(Name, Container->Item[i].Ui.ItemText, true, 99) == 0)
		{
			*Out = &Container->Item[i];
			return true;
		}
	}
	return false;
}
bool UpdateBoolConditional(bool Condition, bool* BoolToSet)
{
	if (Condition)
	{
		*BoolToSet = Container->Item[GetRelativeCursorIndex].Selection.Value.Int;
		return true;
	}

	//reset menu bool
	Container->Item[GetRelativeCursorIndex].Selection.Value.Int = !Container->Item[GetRelativeCursorIndex].Selection.Value.Int;
	return false;
}
bool UpdateBoolConditionalCeil(bool Condition, bool* BoolToSet)
{
	if (Condition)
	{
		*BoolToSet = Container->Item[GetRelativeCursorIndex].Selection.Value.Int;
		return true;
	}

	//reset menu bool
	*BoolToSet = true;
	Container->Item[GetRelativeCursorIndex].Selection.Value.Int = true;
	return false;
}
bool UpdateBoolConditionalFloor(bool Condition, bool* BoolToSet)
{
	if (Condition)
	{
		*BoolToSet = Container->Item[GetRelativeCursorIndex].Selection.Value.Int;
		return true;
	}

	//reset menu bool
	*BoolToSet = false;
	Container->Item[GetRelativeCursorIndex].Selection.Value.Int = false;
	return false;
}
void StartAsynchronousFunction(bool(*AsynchronousFunction)(uint CurrentFrame, ...), const uint ParamCount, uint FramesToLoop, int Params[MaxAsyncParams])
{
	if ((int)AsyncFunction == nullptr && AsyncFrameCount == 0)
	{
		if (ParamCount <= MaxAsyncParams)
		{
			AsyncFrameCount = FramesToLoop;
			Container->Loading.FramesToLoad = 0;
			AsyncFunction = AsynchronousFunction;
			memset(AsyncFunctionParams, 0, sizeof(AsyncFunctionParams));
			//*AsyncFunctionParams = (int[10]){0};
			memcpy(AsyncFunctionParams, Params, sizeof(AsyncFunctionParams));
			AsyncFunctionParamCount = ParamCount;
		}
		else
			Warn("Asynchronous function call has too many parameters");
	}
	else
		Notify("Menu is loading. Please wait.");
}


//[Do not use] This is for menu ui testing
inline Page* DEBUG__GetContainer()
{
	return Container;
}
#pragma endregion

unsafe void AsynchronousLoop()
{
	int CurrentFrames = Container->Loading.FramesToLoad;

	//CError: if ((int)AsyncFunction && CurrentFrames)
	if ((int)AsyncFunction != nullptr && AsyncFrameCount != 0)
	{
		__getNamedFrame("CurrentFrames");
		__getNamedStatic("AsyncFunctionParamCount");
		__getNamedStaticP("AsyncFunctionParams");
		__toStack();
		__getNamedStatic("AsyncFunction");
		__pCall();
		bool ret = __popI();

		CurrentFrames = Container->Loading.FramesToLoad++;
		bool IsTimeOut = CurrentFrames > AsyncFrameCount;
		if (ret || IsTimeOut)
		{
			memset(AsyncFunctionParams, 0, sizeof(AsyncFunctionParams));
			AsyncFunction = nullptr;
			AsyncFunctionParamCount = null;
			AsyncFrameCount = null;
			SetMenuLoading(false);
			if(IsTimeOut)
				Notify("Loading operation timed out.");
		}
		else if (CurrentFrames == 5)
			SetMenuLoading(true);
	}
}
void LoopedExecutionEntry()
{
	LoopedOptions();
}
void ExecutionEntry() 
{
	MainMenu();
}

