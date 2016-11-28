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

bool(*AsyncFunction)(uint CurrentFrame, ...);
int AsyncFunctionParams[MaxAsyncParams];
uint AsyncFunctionParamCount;
uint AsyncFrameCount;//this is needed to provide nice 0 - FrameCountMax for CurrentFrame on AsynchronousFunction and for loading ui display slow start

#pragma region Reset
static void ResetCurrentItem()
{

	Container->Item[AddItemCounter].BitSet = null;
	Container->Item[AddItemCounter].Execute = nullptr;
	Container->Item[AddItemCounter].Ui.ItemText = nullstr;
	Container->Item[AddItemCounter].Ui.Description = nullptr;
	Container->Item[AddItemCounter].Ui.AltExeControlText = nullptr;
	Container->Item[AddItemCounter].Selection.CursorIndex.Int = null;
	Container->Item[AddItemCounter].Selection.EndIndex.Int = null;
	Container->Item[AddItemCounter].Selection.ParseEnum = nullptr;
	Container->Item[AddItemCounter].Selection.Precision = 1.0f;
	Container->Item[AddItemCounter].Selection.StartIndex.Int = null;
	Container->Item[AddItemCounter].Selection.Type = DT_None;
}
#pragma endregion

#pragma region ItemTypes
void SetHeaderAdvanced(char* HeaderText, bool IsItemGxt)
{
	AddItemCounter = 0;
	Container->TotalItemCount = 0;
	
	Container->Ui.HeaderText = HeaderText;
	Container->Ui.IsHeaderGxt = IsItemGxt;
}
void AddItemAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.Description = Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = AltExeControlText;
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
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
void AddItemIntAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Ui.Description = Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = AltExeControlText;
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = DT_Int;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemFloatAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.Description = Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = AltExeControlText;
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
		Container->Item[AddItemCounter].Selection.Type = DT_Float;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemBoolAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool StartIndex, void(*Callback)(), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.Description = Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = AltExeControlText;
		if (IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].AlternateExecute = AlternateCallback;

		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = DT_Bool;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemEnumAdvanced(char* ItemText, bool IsItemGxt, char* Description, char* AltExeControlText, bool IsDisabled, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), char*(*EnumParser)(int ItemIndex), void(*AlternateCallback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.Description = Description;
		Container->Item[AddItemCounter].Ui.AltExeControlText = AltExeControlText;
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
		Container->Item[AddItemCounter].Selection.Type = DT_Int;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		Container->Item[AddItemCounter].Selection.ParseEnum = EnumParser;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemMenuAdvanced(char* ItemText, bool IsItemGxt, char* Description, bool IsDisabled, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.Description = Description;
		if(IsItemGxt)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemGxt);
		if (IsDisabled)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_IsItemDisabled);
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].Selection.Type = DT_FunctionP;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}

void SetHeader(char* HeaderText)
{
	AddItemCounter = 0;
	Container->TotalItemCount = 0;

	Container->Ui.HeaderText = HeaderText;
}
void AddItem(char* ItemText, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Execute = Callback;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemInt(char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)())
{
	//Break(straddiGlobal("Before Cmpq: ", AddItemCounter));
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		//Break(straddiGlobal("Item Index: ", AddItemCounter));
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = DT_Int;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemFloat(char* ItemText, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Float = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Float = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Float = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = DT_Float;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemBool(char* ItemText, bool StartIndex, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = DT_Bool;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemEnum(char* ItemText, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, void(*Callback)(), char*(*EnumParser)(int ItemIndex))
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		if (ExecuteOnChange)
			bit_set(&Container->Item[AddItemCounter].BitSet, ICB_ExecuteOnChange);
		Container->Item[AddItemCounter].Selection.Type = DT_Int;
		Container->Item[AddItemCounter].Selection.ParseEnum = EnumParser;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemMenu(char* ItemText, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].Selection.Type = DT_FunctionP;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}


//TODO: add item bool enum, int, float
//TODO: add alternate execution for x button
//TODO: add bool group that sets all other bools on menu to 0 (enum expansion)
//TODO: add left right scroll bar with dds in timerbars.xtd
//TODO: add AddItemWithInt using selection value for function that needs params
//TODO: add item spacer item

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
bool GetItemByName(char* Name, ItemContainer** Out)
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
	if ((int)AsyncFunction != 0 && AsyncFrameCount != 0)
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

}
void ExecutionEntry() 
{
	MainMenu();
}

