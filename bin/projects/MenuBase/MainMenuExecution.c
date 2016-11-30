#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "common.h"

#include "Utils.h"
#include "MenuUiHandling.h"


int AddItemCounter = 0;
static Page* Container;

#define GetRelativeCursorIndex Container->CursorIndex - Container->ItemStartIndex
#define this Container->Item[GetRelativeCursorIndex].Selection

void InitMenuExecution()
{
	Container = GetMenuContainer();
	if (Container == nullptr)
		Throw("Container Was Null");
}

#pragma region Reset
void ResetCurrentItem()
{
	Container->Item[AddItemCounter].Execute = nullptr;
	Container->Item[AddItemCounter].Ui.IsItemGxt = false;
	Container->Item[AddItemCounter].Ui.ItemText = nullstr;
	Container->Item[AddItemCounter].Ui.Description = nullptr;
	Container->Item[AddItemCounter].Selection.CursorIndex.Int = null;
	Container->Item[AddItemCounter].Selection.EndIndex.Int = null;
	Container->Item[AddItemCounter].Selection.ParseEnum = nullptr;
	Container->Item[AddItemCounter].Selection.Precision = 1.0f;
	Container->Item[AddItemCounter].Selection.StartIndex.Int = null;
	Container->Item[AddItemCounter].Selection.Type = DT_None;
	Container->Item[AddItemCounter].Selection.ExecuteOnChange = false;
}
#pragma endregion

#pragma region ItemTypes
void SetHeader(char* HeaderText, bool IsItemGxt)
{
	AddItemCounter = 0;
	Container->TotalItemCount = 0;
	
	Container->Ui.HeaderText = HeaderText;
	Container->Ui.IsHeaderGxt = IsItemGxt;
}
void AddItem(char* ItemText, bool IsItemGxt, char* Description, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.Description = Description;
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.IsItemGxt = IsItemGxt;
		Container->Item[AddItemCounter].Execute = Callback;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemInt(char* ItemText, bool IsItemGxt, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)())
{
	//Break(straddiGlobal("Before Cmpq: ", AddItemCounter));
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		//Break(straddiGlobal("Item Index: ", AddItemCounter));
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.IsItemGxt = IsItemGxt;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		Container->Item[AddItemCounter].Selection.ExecuteOnChange = ExecuteOnChange;
		Container->Item[AddItemCounter].Selection.Type = DT_Int;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemFloat(char* ItemText, bool IsItemGxt, bool ExecuteOnChange, float MinValue, float MaxValue, float StartIndex, float Precision, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.IsItemGxt = IsItemGxt;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Float = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Float = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Float = StartIndex;
		Container->Item[AddItemCounter].Selection.ExecuteOnChange = ExecuteOnChange;
		Container->Item[AddItemCounter].Selection.Type = DT_Float;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemBool(char* ItemText, bool IsItemGxt, bool StartIndex, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.IsItemGxt = IsItemGxt;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		Container->Item[AddItemCounter].Selection.ExecuteOnChange = true;
		Container->Item[AddItemCounter].Selection.Type = DT_Bool;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemEnum(char* ItemText, bool IsItemGxt, bool ExecuteOnChange, int MinValue, int MaxValue, int StartIndex, int Precision, void(*Callback)(), char*(*EnumParser)(int ItemIndex))
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.IsItemGxt = IsItemGxt;
		Container->Item[AddItemCounter].Execute = Callback;

		Container->Item[AddItemCounter].Selection.StartIndex.Int = MinValue;
		Container->Item[AddItemCounter].Selection.EndIndex.Int = MaxValue;
		Container->Item[AddItemCounter].Selection.CursorIndex.Int = StartIndex;
		Container->Item[AddItemCounter].Selection.ExecuteOnChange = ExecuteOnChange;
		Container->Item[AddItemCounter].Selection.Type = DT_Int;
		Container->Item[AddItemCounter].Selection.Precision = Precision;
		Container->Item[AddItemCounter].Selection.ParseEnum = EnumParser;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
void AddItemMenu(char* ItemText, bool IsItemGxt, void(*Callback)())
{
	if (Container->TotalItemCount >= Container->ItemStartIndex && AddItemCounter < MaxDisplayableItems)
	{
		ResetCurrentItem();
		Container->Item[AddItemCounter].Ui.ItemText = ItemText;
		Container->Item[AddItemCounter].Ui.IsItemGxt = IsItemGxt;
		Container->Item[AddItemCounter].Execute = Callback;
		Container->Item[AddItemCounter].Selection.Type = DT_FunctionP;
		AddItemCounter++;
	}

	Container->TotalItemCount++;
}
//add item bool enum, int, float
//add alternate execution for x button
//add item small spacers between items to make items appear as buttons
//add bool group that sets all other bools on menu to 0 (enum expansion)
//test having a bool error and not change
//add left right scroll bar with dds in timerbars.xtd
//test disable all controls on xbox
//add ability to set description on all options


//add item spacer item
//add small scroll bar on right
//have cursor blink slow on selected item
//have cursor y size shrink on selection



#pragma endregion

void test()
{
	SetMenuLoadingTime(30);
}
void test2()
{
	SetMenuLoadingTime(0);
}
void test3()
{
	Container->TestInt = this.Value.Int;
}
char* testParser(int ItemIndex)
{
	
	switch (Container->Item[ItemIndex].Selection.Value.Int)
	{
		case 0:  return "Parse0";
		case 1:  return "Parse1";
		case 2:  return "Parse2";
		case 3:  return "Parse3";
		case 4:  return "Parse4";
		case 5:  return "Parse5";
		case 6:  return "Parse6";
		case 7:  return "Parse7";
		case 8:  return "Parse8";
		case 9:  return "Parse9";
		case 10: return "Parse10";
	}
	return "NULL";
}


void TestUiCoordPrecision()
{
	float Precision;
	switch (this.Value.Int)
	{
		case 0: Precision = 1.0; break;
		case 1: Precision = 0.1; break;
		case 2: Precision = 0.01; break;
		case 3: Precision = 0.001; break;
		case 4: Precision = 0.0001; break;
	}

	if (GetRelativeCursorIndex < MaxDisplayableItems - 2)
	{
		Container->Item[GetRelativeCursorIndex + 1].Selection.Precision = Precision;
		Container->Item[GetRelativeCursorIndex + 2].Selection.Precision = Precision;
	}
	
}
void TestUiCoordX()
{
	Container->UiTestCoords.x = this.Value.Float;
}
void TestUiCoordY()
{
	Container->UiTestCoords.y = this.Value.Float;
}

void SubMenu()
{
	SetHeader("Sub Menu", false);
	AddItem("test0", false, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", test);
	AddItemInt("test1", false, false, 0, 10, 0, 2, test2);
	AddItemFloat("test2", false, false, 0, 10, 0, 0.1f, test2);
	AddItemBool("test3", false, false, test2);
	AddItemEnum("test4", false, false, 0, 10, 0, 1, test2, testParser);
	AddItemMenu("Submenu Test5", false, SubMenu);
	AddItemMenu("Submenu Test6", false, SubMenu);
	AddItemMenu("Submenu Test7", false, SubMenu);
	AddItemMenu("Submenu Test8", false, SubMenu);
	AddItemMenu("Submenu Test9", false, SubMenu);
	AddItemMenu("Submenu Test10", false, SubMenu);
	AddItemMenu("Submenu Test11", false, SubMenu);
	AddItemMenu("Submenu Test12", false, SubMenu);
	AddItemMenu("Submenu Test13", false, SubMenu);
	AddItemMenu("Submenu Test14", false, SubMenu);
	AddItemMenu("Submenu Test15", false, SubMenu);
	AddItemMenu("Submenu Test16", false, SubMenu);
	AddItemMenu("Submenu Test17", false, SubMenu);
	AddItemMenu("Submenu Test18", false, SubMenu);
	AddItemMenu("Submenu Test19", false, SubMenu);
	AddItemMenu("Submenu Test20", false, SubMenu);
	AddItemMenu("Submenu Test21", false, SubMenu);
	AddItemMenu("Submenu Test22", false, SubMenu);
	AddItemMenu("Submenu Test23", false, SubMenu);

	AddItemMenu("Submenu Test24", false, SubMenu);
	AddItemMenu("Submenu Test25", false, SubMenu);
	AddItem("Item Test", false, "This is a description. I describe things. OoOoOo.", test);
	AddItemInt("Int Test", false, false, 0, 10, 0, 2, test2);
	AddItemFloat("Float Test", false, false, 0, 10, 0, 0.1f, test2);
	AddItemBool("Bool Test", false, false, test2);
	AddItemEnum("Enum Test", false, false, 0, 10, 0, 1, test2, testParser);
}

void MainMenu() 
{
	SetHeader("Main Menu", false);
	AddItem("Loading Test", false, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", test);
	AddItem("Loading Off Test", false, "This is a description. I describe things. OoOoOo.", test2);
	AddItemInt("Ui Test Precision", false, true, 0, 4, 0, 1, TestUiCoordPrecision);
	AddItemFloat("Ui Test Coord X", false, true, 0, 10, Container->UiTestCoords.x, 0.1f, TestUiCoordX);
	AddItemFloat("Ui Test Coord Y", false, true, 0, 10, Container->UiTestCoords.y, 0.1f, TestUiCoordY);
	AddItemBool("Bool Test", false, false, test2);
	AddItemEnum("Enum Test", false, false, 0, 10, 0, 1, test3, testParser);
	AddItemMenu("Submenu Test", false, SubMenu);

}




