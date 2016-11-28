#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "Utils.h"
#include "common.h"

#include "MenuExecutionHandling.h"

static float SavedTestCoordPrecision = 0;

char* Parser_EnumTest(int ItemIndex)
{
	switch (GetEnumParserValue(ItemIndex))
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

void Option_Blank()
{

}
void Menu_LargeSubmenuTest()
{
	SetHeader("Large Submenu Test");
	AddItem("Item1", Option_Blank);
	AddItem("Item2", Option_Blank);
	AddItem("Item3", Option_Blank);
	AddItem("Item4", Option_Blank);
	AddItem("Item5", Option_Blank);
	AddItem("Item6", Option_Blank);
	AddItem("Item7", Option_Blank);
	AddItem("Item8", Option_Blank);
	AddItem("Item9", Option_Blank);
	AddItemIntAdvanced("Item10", false, nullptr, true, false, 0, 50, 0, 1, Option_Blank);
	AddItemFloatAdvanced("Item11", false, nullptr, true, false, 0, 10, 0, 1, Option_Blank);
	AddItemBoolAdvanced("Item12", false, nullptr, true, false, Option_Blank);
	AddItemEnumAdvanced("Item13", false, nullptr, true, false, 0, 50, 0, 1, Option_Blank, Parser_EnumTest);
	AddItemAdvanced("BJ_JUMP_06", true, "Must Come Down.~n~(Gxt Test)", true, Option_Blank);
	AddItemAdvanced("Item15", false, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", false, Option_Blank);
	AddItemAdvanced("Item16", false, nullptr, false, Option_Blank);
	AddItem("Item17", Option_Blank);
	AddItem("Item18", Option_Blank);
	AddItem("Item19", Option_Blank);
	AddItem("Item20", Option_Blank);
	AddItem("Item21", Option_Blank);
	AddItem("Item22", Option_Blank);
	AddItem("Item23", Option_Blank);
	AddItem("Item24", Option_Blank);
	AddItem("Item25", Option_Blank);
	AddItem("Item26", Option_Blank);
	AddItem("Item27", Option_Blank);
	AddItem("Item28", Option_Blank);
	AddItem("Item29", Option_Blank);
	AddItem("Item30", Option_Blank);
	AddItem("Item31", Option_Blank);
	AddItem("Item32", Option_Blank);
	AddItem("Item33", Option_Blank);
	AddItem("Item34", Option_Blank);
	AddItem("Item35", Option_Blank);
	AddItem("Item36", Option_Blank);
	AddItem("Item37", Option_Blank);
	AddItem("Item38", Option_Blank);
	AddItem("Item39", Option_Blank);
	AddItem("Item40", Option_Blank);
	AddItem("Item41", Option_Blank);
	AddItem("Item42", Option_Blank);
	AddItem("Item43", Option_Blank);
	AddItem("Item44", Option_Blank);
	AddItem("Item45", Option_Blank);
	AddItem("Item46", Option_Blank);
	AddItem("Item47", Option_Blank);
	AddItem("Item48", Option_Blank);
	AddItem("Item49", Option_Blank);
	AddItem("Item50", Option_Blank);
}

void Option_LoadingOnTest()
{
	SetMenuLoadingTime(30);
}
void Option_LoadingOffTest()
{
	SetMenuLoadingTime(0);
}
void Option_UiTestPrecision()
{
	SavedTestCoordPrecision = PrecisionToFloat(GetCurrentItem()->Selection.Value.Int);

	ItemContainer* Buffer;

	if (GetItemRelativeToCursor(1, &Buffer))
		Buffer->Selection.Precision = SavedTestCoordPrecision;
	if (GetItemRelativeToCursor(2, &Buffer))
		Buffer->Selection.Precision = SavedTestCoordPrecision;
}
void Option_TestUiCoordX()
{
	DEBUG__GetContainer()->UiTestCoords.x = GetCurrentItem()->Selection.Value.Float;
}
void Option_TestUiCoordY()
{
	DEBUG__GetContainer()->UiTestCoords.y = GetCurrentItem()->Selection.Value.Float;
}
void Option_TestInt()
{
	DEBUG__GetContainer()->TestInt = GetCurrentItem()->Selection.Value.Int;
}
void Option_BoolTest()
{

}
void Option_EnumTest()
{

}

void Menu_DebugOptions()
{
	SetHeader("Debug Options");
	AddItemAdvanced("Loading Test", false, "Turns loading icon on.", true, Option_LoadingOnTest);
	AddItemAdvanced("Loading Off Test", false, "Turns loading icon on.", false, Option_LoadingOffTest);
	AddItemInt("Ui Test Precision", true, 0, 4, FloatToPrecision(SavedTestCoordPrecision), Option_UiTestPrecision);
	AddItemFloat("Ui Test Coord X", true, 0, 10, DEBUG__GetContainer()->UiTestCoords.x, SavedTestCoordPrecision, Option_TestUiCoordX);
	AddItemFloat("Ui Test Coord Y", true, 0, 10, DEBUG__GetContainer()->UiTestCoords.y, SavedTestCoordPrecision, Option_TestUiCoordY);
	AddItemInt("Ui Test Int", true, -100, 1000, DEBUG__GetContainer()->TestInt, Option_TestInt);
	AddItemBool("Bool Test", false, Option_BoolTest);
	AddItemEnum("Enum Test", false, 0, 10, 0, Option_EnumTest, Parser_EnumTest);
	AddItemMenu("Large Submenu Test", Menu_LargeSubmenuTest);

}

inline void MainMenu()
{
	SetHeader("Main Menu");
	AddItemMenu("Debug Options", Menu_DebugOptions);

}




