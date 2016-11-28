#pragma once

//Max item count displayable
#define MaxDisplayableItems 25
#define MaxMenuLevels 10

typedef enum ItemContainerBits
{
	ICB_IsItemGxt,
	ICB_ExecuteOnChange,
	ICB_IsItemDisabled
} ItemContainerBits;
typedef struct ItemContainer
{
	//0 = IsItemGxt, 1 = ExecuteOnChange, 2 = IsItemDisabled
	int BitSet;//BitSet is used to cut down static size

	struct
	{
		char* ItemText;
		char* Description;
	} Ui;
	struct
	{
		DataType Type;
		union { flint CursorIndex; flint Value; };
		float Precision;
		flint StartIndex;
		flint EndIndex;//ItemCount = EndIndex - StartIndex + 1
		char* (*ParseEnum)(int ItemIndex);//nullptr == no enum

	} Selection;

	void(*Execute)();

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
		uint LoadEndTime;
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
void SetMenuLoadingTime(uint LoadingTimeMs);
