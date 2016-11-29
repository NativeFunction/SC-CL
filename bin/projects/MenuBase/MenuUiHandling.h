#pragma once

//Max item count displayable
#define MaxDisplayableItems 25
#define MaxMenuLevels 10

enum ItemContainerBits
{
	ICB_IsItemGxt,
	ICB_ExecuteOnChange,
	ICB_IsItemDisabled,
};
typedef struct ItemContainer
{
	//using ItemContainerBits
	int BitSet;//BitSet is used to cut down static size

	void(*Execute)();
	union { void(*AlternateExecute)(); bool HasAlternateExecution; };

	struct
	{
		char* ItemText;
		char* Description;
		char* AltExeControlText;
	} Ui;
	struct
	{
		DataType Type;
		union { flint CursorIndex; flint Value; };
		float Precision;
		flint StartIndex;
		flint EndIndex;//ItemCount = EndIndex - StartIndex + 1
		const char* (*ParseEnum)(int ItemIndex);//nullptr == no enum

	} Selection;

} ItemContainer;

typedef struct Page//Menu Page
{
	vector2 UiTestCoords;
	int TestInt;

	//size: 64
	bool IsMenuOpen;
	int DisableMenuOpenControls;//frames to disable controls to prevent miss clicks when exiting the menu

	int CursorIndex;
	int TotalItemCount;
	int ItemStartIndex;//index for draw MaxDisplayableItems

	int CurrentMenuLevel;
	void(*UpdateToMenuLevel[MaxMenuLevels])();//might have to add a param for it ItemStartIndex
	
	//size: 4
	union
	{
		bool IsMenuLoading;
		uint FramesToLoad;
	} Loading;

	//size: 112
	struct
	{
		char* HeaderText;
		bool IsHeaderGxt;
		Font HeaderFont;
		Font TextFont;
		vector2 DrawPos;
		Size BackgroundDrawSize;
		RGBA BackgroundColor;
		RGBA HeaderTextColor;
		RGBA ScrollBarColor;
		RGBA SelectedTextColor;
		RGBA UnselectedTextColor;
		RGBA DisabledSelectedTextColor;
		RGBA DisabledUnselectedTextColor;
		RGBA DisabledScrollBarColor;
		int MenuControlSFID;
		int MenuControlSFID2;//loading work around
	} Ui;

	//size: 40 * MaxDisplayableItems = 1000
	ItemContainer Item[MaxDisplayableItems];



} Page;

void HandleMenuUi();
void InitMenuDraw();

Page* GetMenuContainer();
bool HasPlayerOpenedMenu();
void SetMenuLoading(bool IsLoading);
