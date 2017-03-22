#pragma once

//Max item count displayable
#define MaxDynamicItems 100
#define MaxDisplayableItems 25
#define MaxMenuLevels 10

typedef enum MenuSelectionType
{
	MST_None,
	MST_Param,
	MST_Int,
	MST_Enum,
	MST_Float,
	MST_Bool,
	MST_Menu,
	MST_MenuParam,
	MST_IntBool,
	MST_EnumBool,
	MST_FloatBool,
	MST_Player,
} MenuSelectionType;
enum ItemContainerBits
{
	ICB_IsItemGxt,//Gets whether the item is using gxt text
	ICB_ExecuteOnChange,//Gets whether the item executes on left, right scroll
	ICB_IsItemDisabled,//Gets whether the item is disabled
	ICB_BoolNumValue,//Current bool value for BoolNum operations
	ICB_DoesItemHaveConfirmation,//Gets if the item selection has to be confirmed
	ICB_DoesItemForwardHeaderText,//Gets if the item forwards header text to the next submenu
};
enum PageBits
{
	PB_IsMenuOpen,
	PB_IsCurrentMenuDynamic,//Dynamic Updating
	PB_IsCurrentMenuInvalid,//ex: invalid selected player index
	PB_LastMenuDirection,//Back = 0, Forward = 1
	PB_IsDisplayingConfirmation,
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
		MenuSelectionType Type;
		int DynamicId;
		union { flint CursorIndex; flint Value; };
		float Precision;
		flint StartIndex;
		flint EndIndex;//ItemCount = EndIndex - StartIndex + 1
		const char* (*ParseEnum)(int ItemIndex);//nullptr == no enum

	} Selection;

} ItemContainer;

typedef struct MenuLevel
{
	void(*UpdateToMenuLevel)();
	bool(*DynamicChecker)(int Id);
	struct
	{
		union { int CursorIndex; int DynamicId; };
		union { int ItemStartIndex; int DynamicRange; };
	} SavedCursor;

} MenuLevel;

typedef struct Page//Menu Page
{
	vector2 UiTestCoords;
	int TestInt;

	//size: 64

	int BitSet;
	int DisableMenuOpenControls;//frames to disable controls to prevent miss clicks when exiting the menu

	int CursorIndex;
	int TotalItemCount;
	int ItemStartIndex;//index for draw MaxDisplayableItems

	int CurrentMenuLevel;
	MenuLevel Level[MaxMenuLevels];

	
	//size: 4
	union
	{
		bool IsMenuLoading;
		uint FramesToLoad;
	} Loading;

	//size: 112
	struct
	{
		char* HeaderText[MaxMenuLevels];
		int IsHeaderGxtBitSet;
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
