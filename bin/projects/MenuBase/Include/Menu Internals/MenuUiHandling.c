#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "common.h"

#include "Utils.h"
#include "MenuExecutionHandling.h"
#include "MenuUiHandling.h"

static Page Container =
{
    .UiTestCoords = {null},
    .TestInt = null,
    .BitSet = null,
    .DisableMenuOpenControls = null,
    .CursorIndex = null,
    .TotalItemCount = null,
    .ItemStartIndex = null,
    .CurrentMenuLevel = null,
    .Loading = {null},
    .Item = {null},
    .Ui.HeaderText = {nullptr},
    .Ui.IsHeaderGxtBitSet = false,
    .Ui.MenuControlSFID = null,
    .Ui.MenuControlSFID2 = null,


    .Level = { ExecutionEntry },
    .Ui.HeaderFont = Font_SignPainter_HouseScript,
    .Ui.TextFont = Font_Chalet_LondonNineteenSixty,
    .Ui.DrawPos = { 0.76f, 0.16f },
    .Ui.BackgroundDrawSize = { 0.25000, 0.08f },
    .Ui.BackgroundColor = { 0, 0, 0, 180 },
    .Ui.HeaderTextColor = { 255, 255, 255, 255 },
    .Ui.ScrollBarColor = { 230, 230, 230, 255 },
    .Ui.SelectedTextColor = { 0, 0, 0, 255 },
    .Ui.UnselectedTextColor = { 230, 230, 230, 255 },
    .Ui.DisabledUnselectedTextColor = { 155, 155, 155, 255 },
    .Ui.DisabledSelectedTextColor = { 50, 50, 50, 255 },
    .Ui.DisabledScrollBarColor = { 190, 190, 190, 255 }
};

#define GetRelativeCursorIndex Container.CursorIndex - Container.ItemStartIndex
#define ItemFontSize 0.35f

#pragma region MenuCommands
bool HasPlayerOpenedMenu()
{
    if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_RB))
    {
        SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_X);
        DISABLE_CONTROL_ACTION(0, INPUT_JUMP, true);
        return IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_X);
    }
    return false;
}
inline void ShutDownMenu()
{
    bitReset(&Container.BitSet, PB_IsMenuOpen);
    Container.DisableMenuOpenControls = 30;
    SET_CINEMATIC_BUTTON_ACTIVE(true);
}
inline int GetItemCountWithMaxItemLimit()
{
    return Container.TotalItemCount > MaxDisplayableItems ? MaxDisplayableItems : Container.TotalItemCount;
}
inline int GetItemCountStartIndex()
{
    return Container.TotalItemCount > MaxDisplayableItems ? Container.ItemStartIndex : 0;
}
void DisableUnusedInputs()
{
    if (IS_MOBILE_PHONE_CALL_ONGOING())
        STOP_SCRIPTED_CONVERSATION(false);

    DISPLAY_AMMO_THIS_FRAME(false);
    SET_CINEMATIC_BUTTON_ACTIVE(false);

    HIDE_HUD_COMPONENT_THIS_FRAME(HUD_VEHICLE_NAME);
    HIDE_HUD_COMPONENT_THIS_FRAME(HUD_AREA_NAME);
    HIDE_HUD_COMPONENT_THIS_FRAME(HUD_STREET_NAME);
    HIDE_HUD_COMPONENT_THIS_FRAME(HUD_VEHICLE_CLASS);

    //this disables hidden controls that are difficult to disable
    DISABLE_ALL_CONTROL_ACTIONS(0);
    for (int i = 0; i < 338; i++)
        ENABLE_CONTROL_ACTION(0, i, true);

    DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
    DISABLE_CONTROL_ACTION(0, INPUT_NEXT_CAMERA, true);
    DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, true);
    DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
    DISABLE_CONTROL_ACTION(0, INPUT_HUD_SPECIAL, true);

    SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_ACCEPT);
    SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_CANCEL);
    SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_UP);
    SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_DOWN);
    SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_LEFT);
    SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_RIGHT);
    SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_X);

    DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, true);
    DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_CANCEL, true);
    DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_UP, true);
    DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_DOWN, true);
    DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_LEFT, true);
    DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RIGHT, true);

    DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_NEXT, true);
    DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_PREV, true);
    DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_SPECIAL, true);
    DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_SPECIAL_TWO, true);
    DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_LIGHT, true);
    DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_HEAVY, true);
    DISABLE_CONTROL_ACTION(0, INPUT_MELEE_BLOCK, true);
    DISABLE_CONTROL_ACTION(0, INPUT_DETONATE, true);
    DISABLE_CONTROL_ACTION(0, INPUT_VEH_HEADLIGHT, true);
    DISABLE_CONTROL_ACTION(0, INPUT_VEH_RADIO_WHEEL, true);
    DISABLE_CONTROL_ACTION(0, INPUT_CONTEXT, true);
    DISABLE_CONTROL_ACTION(0, INPUT_RELOAD, true);
    DISABLE_CONTROL_ACTION(0, INPUT_DIVE, true);
    DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, true);
    DISABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_SELECT_NEXT_WEAPON, true);
    DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, true);
    DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, true);
    DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, true);
    DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, true);
    DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, true);
    DISABLE_CONTROL_ACTION(0, INPUT_COVER, true);

}
Page* GetMenuContainer()
{
    return &Container;
}
void SetMenuLoading(bool IsLoading)
{
    if (IsLoading)
    {
        _PUSH_SCALEFORM_MOVIE_FUNCTION(Container.Ui.MenuControlSFID2, "SET_BACKGROUND_COLOUR");
        _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
        _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
        _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
        _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
        _POP_SCALEFORM_MOVIE_FUNCTION_VOID();
        _PUSH_SCALEFORM_MOVIE_FUNCTION(Container.Ui.MenuControlSFID2, "SET_SAVING_TEXT");
        _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(SFS_LOADING_CIRCLE_RIGHT);
        BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
        ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Loading");
        END_TEXT_COMMAND_SCALEFORM_STRING();
        _POP_SCALEFORM_MOVIE_FUNCTION_VOID();
    }
    else
    {
        Container.Loading.IsMenuLoading = false;
        _PUSH_SCALEFORM_MOVIE_FUNCTION(Container.Ui.MenuControlSFID2, "REMOVE_SAVING");
        _POP_SCALEFORM_MOVIE_FUNCTION_VOID();
    }

}
void SetDataSlot(int SlotIndex, ScaleformButton ButtonId, const char* ItemText, bool IsGxtText)
{
    _PUSH_SCALEFORM_MOVIE_FUNCTION(Container.Ui.MenuControlSFID, "SET_DATA_SLOT");
    _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(SlotIndex);//slot index
    _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(ButtonId);//button id

    if (IsGxtText)
    {
        if (DOES_TEXT_LABEL_EXIST(ItemText))
        {
            BEGIN_TEXT_COMMAND_SCALEFORM_STRING(ItemText);
        }
        else
        {
            BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
            ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("INVALID_GXT");
        }
    }
    else
    {
        BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
        ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(ItemText);
    }

    END_TEXT_COMMAND_SCALEFORM_STRING();
    _POP_SCALEFORM_MOVIE_FUNCTION_VOID();
}
void UpdateMenuControls()
{
    int SlotIdCounter = 0;

    _PUSH_SCALEFORM_MOVIE_FUNCTION(Container.Ui.MenuControlSFID, "CLEAR_ALL");
    _POP_SCALEFORM_MOVIE_FUNCTION_VOID();

    //Loading display padding
    if (Container.Loading.FramesToLoad >= 5)
        SetDataSlot(SlotIdCounter++, 255, "                  ", false);

    if (bitTest(Container.BitSet, PB_IsMenuOpen))
    {
        bool IsItemEnabled = !bitTest(Container.Item[GetRelativeCursorIndex].BitSet, ICB_IsItemDisabled);

        if (IsItemEnabled)
        {
            switch (Container.Item[GetRelativeCursorIndex].Selection.Type)
            {
            case MST_Int:
            case MST_Float:
            case MST_Enum:
            case MST_IntBool:
            case MST_FloatBool:
            case MST_EnumBool:
                SetDataSlot(SlotIdCounter++, SFB_BUTTON_DPAD_LEFT_RIGHT, "Next", false);
                break;
            default:
                break;
            }
        }

        if (Container.CurrentMenuLevel == 0)
            SetDataSlot(SlotIdCounter++, SFB_BUTTON_B, "Close", false);
        else
            SetDataSlot(SlotIdCounter++, SFB_BUTTON_B, "Back", false);

        if (IsItemEnabled)
        {
            if (Container.Item[GetRelativeCursorIndex].HasAlternateExecution)
            {
                if (Container.Item[GetRelativeCursorIndex].Ui.AltExeControlText)
                    SetDataSlot(SlotIdCounter++, SFB_BUTTON_X, (const char*)Container.Item[GetRelativeCursorIndex].Ui.AltExeControlText, false);
                else
                    SetDataSlot(SlotIdCounter++, SFB_BUTTON_X, "Select", false);
            }

            SetDataSlot(SlotIdCounter++, SFB_BUTTON_A, "Select", false);
        }

    }

    _PUSH_SCALEFORM_MOVIE_FUNCTION(Container.Ui.MenuControlSFID, "SET_BACKGROUND_COLOUR");
    _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(Container.Ui.BackgroundColor.red);
    _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(Container.Ui.BackgroundColor.green);
    _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(Container.Ui.BackgroundColor.blue);
    _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(80);
    _POP_SCALEFORM_MOVIE_FUNCTION_VOID();

    _PUSH_SCALEFORM_MOVIE_FUNCTION(Container.Ui.MenuControlSFID, "DRAW_INSTRUCTIONAL_BUTTONS");
    _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);//0 = DrawHorizontal, 1 = DrawVertical, -1 = ?
    _POP_SCALEFORM_MOVIE_FUNCTION_VOID();


    DRAW_SCALEFORM_MOVIE_FULLSCREEN(Container.Ui.MenuControlSFID, Container.Ui.UnselectedTextColor, false);
}
bool UpdateDynamicCursor(int Id, int Range)
{
    bool HasFoundIndex = false;
    int ClosestIndexBefore = 0;
    DynamicIdArray Menu = DumpDynamicIds();

#define BreakDynamicMenu 0

    const int MaxIds = Container.TotalItemCount < MaxDynamicItems ? Container.TotalItemCount : MaxDynamicItems;
    const int HighestStartIndex = MaxIds - MaxDisplayableItems > 0 ? MaxIds - MaxDisplayableItems : 0;

    for (int i = 0; i < MaxIds; i++)
    {
        if (Menu.Items[i] == Id)
        {
            Container.CursorIndex = i;
            /*
            HighestStartIndex 32 - 25 = 7

            26 - 6

            20 > HighestStartIndex

            */

            int StartIndexRelativeToCursor = i - Range;

            if (StartIndexRelativeToCursor < 0)
                Container.ItemStartIndex = 0;
            else if (StartIndexRelativeToCursor > HighestStartIndex)
                Container.ItemStartIndex = HighestStartIndex;
            else
                Container.ItemStartIndex = StartIndexRelativeToCursor;

#if BreakDynamicMenu == 1
            if (Container.CursorIndex != SavedCursorIndex)
            {
                char* str = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
                //CError: no strcpy on char* init
                strcpy(str, "CursorIndex: ", 32);
                straddi(str, Container.CursorIndex, 32);
                stradd(str, " StartIndex: ", 32);
                straddi(str, Container.ItemStartIndex, 32);
                Break(strcatGlobal("== change~n~", str));
            }
#endif

            HasFoundIndex = true;
            break;
        }
        if (!HasFoundIndex)
        {
            if (Menu.Items[i] < Id)
                ClosestIndexBefore = i;
            else if (Menu.Items[i] > Id)
            {
                Container.CursorIndex = i;

                int StartIndexRelativeToCursor = i - Range;

                if (StartIndexRelativeToCursor < 0)
                    Container.ItemStartIndex = 0;
                else if (StartIndexRelativeToCursor > HighestStartIndex)
                    Container.ItemStartIndex = HighestStartIndex;
                else
                    Container.ItemStartIndex = StartIndexRelativeToCursor;

#if BreakDynamicMenu == 1
                if (Container.CursorIndex != SavedCursorIndex)
                {
                    char* str = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
                    strcpy(str, "CursorIndex: ", 32);
                    straddi(str, Container.CursorIndex, 32);
                    stradd(str, " StartIndex: ", 32);
                    straddi(str, Container.ItemStartIndex, 32);
                    Break(strcatGlobal("> change~n~", str));
                }
#endif

                HasFoundIndex = true;
            }
        }
    }

    if (!HasFoundIndex)
    {
        if (Container.TotalItemCount > 0)
        {
            Container.CursorIndex = ClosestIndexBefore;

            int StartIndexRelativeToCursor = ClosestIndexBefore - Range;

            if (StartIndexRelativeToCursor < 0)
                Container.ItemStartIndex = 0;
            else if (StartIndexRelativeToCursor > HighestStartIndex)
                Container.ItemStartIndex = HighestStartIndex;
            else
                Container.ItemStartIndex = StartIndexRelativeToCursor;

#if BreakDynamicMenu == 1
            if (Container.CursorIndex != SavedCursorIndex)
            {
                char* str = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
                strcpy(str, "CursorIndex: ", 32);
                straddi(str, Container.CursorIndex, 32);
                stradd(str, " StartIndex: ", 32);
                straddi(str, Container.ItemStartIndex, 32);
                Break(strcatGlobal("< change~n~", str));
            }
#endif
        }
        else
        {
            SetCurrentMenuInvalid(true, "");
            return false;
        }
    }
    return true;
}
void UpdateMenuLevel(int DirectionAndAmount)
{
    bitReset(&Container.BitSet, PB_IsDisplayingConfirmation);
    bitReset(&Container.BitSet, PB_IsCurrentMenuInvalid);

    if (DirectionAndAmount > 0 && DirectionAndAmount <= MaxMenuLevels)
    {
        bitSet(&Container.BitSet, PB_LastMenuDirection);

        if (bitTest(Container.BitSet, PB_IsCurrentMenuDynamic))
        {
            Container.Level[Container.CurrentMenuLevel].SavedCursor.DynamicId = Container.Item[GetRelativeCursorIndex].Selection.DynamicId;
            Container.Level[Container.CurrentMenuLevel].SavedCursor.DynamicRange = Container.CursorIndex - Container.ItemStartIndex;
        }
        else
        {
            Container.Level[Container.CurrentMenuLevel].SavedCursor.CursorIndex = Container.CursorIndex;
            Container.Level[Container.CurrentMenuLevel].SavedCursor.ItemStartIndex = Container.ItemStartIndex;
        }

        char* ForwardedHeaderText = nullptr;
        bool IsForwardedHeaderTextGxt = null;

        if (bitTest(Container.Item[GetRelativeCursorIndex].BitSet, ICB_DoesItemForwardHeaderText))
        {
            ForwardedHeaderText = Container.Item[GetRelativeCursorIndex].Ui.ItemText;
            IsForwardedHeaderTextGxt = bitTest(Container.Item[GetRelativeCursorIndex].BitSet, ICB_IsItemGxt);
        }

        Container.CurrentMenuLevel++;
        if (Container.CurrentMenuLevel < MaxMenuLevels)
        {
            Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel = Container.Item[GetRelativeCursorIndex].Execute;

            //Update to menu level
            Container.ItemStartIndex = 0;
            Container.CursorIndex = 0;
            if (ForwardedHeaderText)
            {
                Container.Ui.HeaderText[Container.CurrentMenuLevel] = ForwardedHeaderText;
                if (IsForwardedHeaderTextGxt)
                    SET_BIT(&Container.Ui.IsHeaderGxtBitSet, Container.CurrentMenuLevel);
                else
                    CLEAR_BIT(&Container.Ui.IsHeaderGxtBitSet, Container.CurrentMenuLevel);
            }

            Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();
        }
        else
        {
            Warn(straddiGlobal("Menu level out of bounds couldn't advance level. Value: ", Container.CurrentMenuLevel));
            Container.CurrentMenuLevel--;
        }
        UpdateMenuLevel(DirectionAndAmount - 1);
    }
    else if (DirectionAndAmount < 0 && DirectionAndAmount >= -MaxMenuLevels)
    {
        bitReset(&Container.BitSet, PB_LastMenuDirection);
        if (Container.CurrentMenuLevel == 0)
        {
            PlayMenuSound("QUIT");
            ShutDownMenu();
            return;
        }
        else
        {
            PlayMenuSound("BACK");
            Container.CurrentMenuLevel--;
            if (Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel != nullptr)
            {
                Container.Level[Container.CurrentMenuLevel + 1] = (MenuLevel){ 0 };

                if (Container.Level[Container.CurrentMenuLevel].DynamicChecker != nullptr)
                {
                    bitSet(&Container.BitSet, PB_IsCurrentMenuDynamic);
                    UpdateDynamicCursor(Container.Level[Container.CurrentMenuLevel].SavedCursor.DynamicId, Container.Level[Container.CurrentMenuLevel].SavedCursor.DynamicRange);
                }
                else
                {
                    Container.ItemStartIndex = Container.Level[Container.CurrentMenuLevel].SavedCursor.ItemStartIndex;
                    Container.CursorIndex = Container.Level[Container.CurrentMenuLevel].SavedCursor.CursorIndex;
                }

                Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();
            }
            else
                Throw(straddiGlobal("MenuLevel change was null at: ", Container.CurrentMenuLevel++));
        }
        UpdateMenuLevel(DirectionAndAmount + 1);
    }
}
#pragma endregion

#pragma region Parsing
bool IsAutoScrollActive(uint* HoldCounter, int ScrollInput)
{
    bool IsControlPressed = IS_DISABLED_CONTROL_PRESSED(2, ScrollInput);
    if (IsControlPressed)
        (*HoldCounter)++;
    else
    {
        *HoldCounter = 0;
        return false;
    }
    if (*HoldCounter <= 30)
    {
        if (*HoldCounter < 10)
            return false;
        switch (*HoldCounter)
        {
        case 10:
        case 15:
        case 20:
        case 24:
        case 27:
        case 29:
            return IsControlPressed;
        default:
            return false;
        }
    }
    return IsControlPressed;
}
void ParseMenuControls()
{
    static uint HoldUpCounter = 0, HoldDownCounter = 0, HoldLeftCounter = 0, HoldRightCounter = 0;
    static char* SavedDescription = nullstr;
    ItemContainer* CurrentItem = &Container.Item[GetRelativeCursorIndex];

    if (Container.TotalItemCount > 1 && !bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
    {
        if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_PAD_UP) || (IsAutoScrollActive(&HoldUpCounter, INPUT_SCRIPT_PAD_UP)))
        {
            PlayMenuSound("NAV_UP_DOWN");
            if (Container.CursorIndex <= 0)//if 0 jump to end item
            {
                Container.CursorIndex = Container.TotalItemCount - 1;
                if (Container.TotalItemCount > MaxDisplayableItems)
                {
                    //sets draw index for scroll
                    Container.ItemStartIndex = Container.TotalItemCount - MaxDisplayableItems;
                    Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();//update text for scroll
                }

            }
            else if (Container.TotalItemCount > MaxDisplayableItems && Container.ItemStartIndex != 0 && Container.CursorIndex == Container.ItemStartIndex)
            {
                Container.ItemStartIndex--;
                Container.CursorIndex--;
                Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();//update text for scroll
            }
            else
                Container.CursorIndex--;
        }
        if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_PAD_DOWN) || (IsAutoScrollActive(&HoldDownCounter, INPUT_SCRIPT_PAD_DOWN)))
        {
            PlayMenuSound("NAV_UP_DOWN");
            if (Container.CursorIndex >= Container.TotalItemCount - 1)
            {
                Container.CursorIndex = 0;
                if (Container.TotalItemCount > MaxDisplayableItems)
                {
                    Container.ItemStartIndex = 0;
                    Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();//update text for scroll
                }
            }
            else if (Container.TotalItemCount > MaxDisplayableItems &&
                Container.CursorIndex >= MaxDisplayableItems - 1 &&
                Container.CursorIndex == Container.ItemStartIndex + MaxDisplayableItems - 1)
            {
                Container.CursorIndex++;
                Container.ItemStartIndex = Container.CursorIndex - (MaxDisplayableItems - 1);
                Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();//update text for scroll
            }
            else
                Container.CursorIndex++;
        }

    }

    if (!bitTest(CurrentItem->BitSet, ICB_IsItemDisabled))
    {
        MenuSelectionType CurrentType = CurrentItem->Selection.Type;

        //Number selector
        if (!bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
        {
            switch (CurrentType)
            {
            case MST_Int:
            case MST_Enum:
            case MST_IntBool:
            case MST_EnumBool:
            {
                if (bitTest(CurrentItem->BitSet, ICB_ExecuteOnChange) && bitTest(CurrentItem->BitSet, ICB_DoesItemHaveConfirmation) && !bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
                {
                    SavedDescription = CurrentItem->Ui.Description;
                    CurrentItem->Ui.Description = "Are you sure you want to select this item?";
                    bitSet(&Container.BitSet, PB_IsDisplayingConfirmation);
                    return;
                }
                if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_PAD_LEFT) || (IsAutoScrollActive(&HoldLeftCounter, INPUT_SCRIPT_PAD_LEFT)))
                {
                    PlayMenuSound("NAV_LEFT_RIGHT");
                    if (CurrentItem->Selection.CursorIndex.Int <= CurrentItem->Selection.StartIndex.Int)
                        CurrentItem->Selection.CursorIndex.Int = CurrentItem->Selection.EndIndex.Int;
                    else
                        CurrentItem->Selection.CursorIndex.Int -= (int)CurrentItem->Selection.Precision;

                }
                else if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_PAD_RIGHT) || (IsAutoScrollActive(&HoldRightCounter, INPUT_SCRIPT_PAD_RIGHT)))
                {
                    PlayMenuSound("NAV_LEFT_RIGHT");
                    if (CurrentItem->Selection.CursorIndex.Int >= CurrentItem->Selection.EndIndex.Int)
                        CurrentItem->Selection.CursorIndex.Int = CurrentItem->Selection.StartIndex.Int;
                    else
                        CurrentItem->Selection.CursorIndex.Int += (int)CurrentItem->Selection.Precision;

                }

                if (bitTest(CurrentItem->BitSet, ICB_ExecuteOnChange))
                    CurrentItem->Execute();
            }
            break;
            case MST_Float:
            case MST_FloatBool:
            {
                if (bitTest(CurrentItem->BitSet, ICB_ExecuteOnChange) && bitTest(CurrentItem->BitSet, ICB_DoesItemHaveConfirmation) && !bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
                {
                    SavedDescription = CurrentItem->Ui.Description;
                    CurrentItem->Ui.Description = "Are you sure you want to select this item?";
                    bitSet(&Container.BitSet, PB_IsDisplayingConfirmation);
                    return;
                }

                if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_PAD_LEFT) || (IsAutoScrollActive(&HoldLeftCounter, INPUT_SCRIPT_PAD_LEFT)))
                {
                    PlayMenuSound("NAV_LEFT_RIGHT");
                    if (CurrentItem->Selection.CursorIndex.Float <= CurrentItem->Selection.StartIndex.Float + 0.000015)//0.000000015 fixes rounding errors
                        CurrentItem->Selection.CursorIndex.Float = CurrentItem->Selection.EndIndex.Float;
                    else
                        CurrentItem->Selection.CursorIndex.Float -= CurrentItem->Selection.Precision;

                }
                else if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_PAD_RIGHT) || (IsAutoScrollActive(&HoldRightCounter, INPUT_SCRIPT_PAD_RIGHT)))
                {
                    PlayMenuSound("NAV_LEFT_RIGHT");
                    if (CurrentItem->Selection.CursorIndex.Float >= CurrentItem->Selection.EndIndex.Float)
                        CurrentItem->Selection.CursorIndex.Float = CurrentItem->Selection.StartIndex.Float;
                    else
                        CurrentItem->Selection.CursorIndex.Float += CurrentItem->Selection.Precision;

                }

                if (bitTest(CurrentItem->BitSet, ICB_ExecuteOnChange))
                    CurrentItem->Execute();
            }
            break;
            default:
                break;
            }
        }

        if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_ACCEPT))
        {
            PlayMenuSound("SELECT");
            if (CurrentItem->Execute != nullptr)
            {
                if (bitTest(CurrentItem->BitSet, ICB_DoesItemHaveConfirmation) && !bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
                {
                    SavedDescription = CurrentItem->Ui.Description;
                    CurrentItem->Ui.Description = "Are you sure you want to select this item?";
                    bitSet(&Container.BitSet, PB_IsDisplayingConfirmation);
                    return;
                }
                if (bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
                {
                    bitReset(&Container.BitSet, PB_IsDisplayingConfirmation);
                    CurrentItem->Ui.Description = SavedDescription;
                }

                switch (CurrentType)
                {
                case MST_Bool:
                    CurrentItem->Selection.CursorIndex.Int = !CurrentItem->Selection.CursorIndex.Int;
                    break;
                case MST_Menu:
                case MST_MenuParam:
                    UpdateMenuLevel(1);
                    return;
                case MST_IntBool:
                case MST_FloatBool:
                case MST_EnumBool:
                    bitFlip(&CurrentItem->BitSet, ICB_BoolNumValue);
                    break;
                default:
                    break;
                }
                CurrentItem->Execute();
            }
            else
                Throw(straddiGlobal("Execute was null at: ", Container.CursorIndex));

        }

        if (CurrentItem->HasAlternateExecution && IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_X))
        {
            PlayMenuSound("SELECT");

            if (bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
            {
                bitReset(&Container.BitSet, PB_IsDisplayingConfirmation);
                CurrentItem->Ui.Description = SavedDescription;
            }
            else
            {
                if (CurrentItem->AlternateExecute != nullptr)
                {
                    if (bitTest(CurrentItem->BitSet, ICB_DoesItemHaveConfirmation) && !bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
                    {
                        SavedDescription = CurrentItem->Ui.Description;
                        CurrentItem->Ui.Description = "Are you sure you want to select this item?";
                        bitSet(&Container.BitSet, PB_IsDisplayingConfirmation);
                        return;
                    }
                    CurrentItem->AlternateExecute();
                }
                else
                    Throw(straddiGlobal("Alternate Execute was null at: ", Container.CursorIndex));
            }
        }

    }

    if (IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_CANCEL))
    {
        if (bitTest(Container.BitSet, PB_IsDisplayingConfirmation))
        {
            PlayMenuSound("BACK");
            bitReset(&Container.BitSet, PB_IsDisplayingConfirmation);
            CurrentItem->Ui.Description = SavedDescription;
        }
        else
            UpdateMenuLevel(-1);
    }

}
#pragma endregion

#pragma region Drawing
void SetUpDraw(Font font, float wrap, float scale, bool center, bool right_justify, bool drop_shadow, bool outline, RGBA color)
{
    SET_TEXT_FONT(font);
    SET_TEXT_WRAP(0.0f, wrap);
    SET_TEXT_SCALE(1.0f, scale);
    SET_TEXT_CENTRE(center);
    SET_TEXT_RIGHT_JUSTIFY(right_justify);
    if (drop_shadow)
        SET_TEXT_DROP_SHADOW();

    if (outline)
        SET_TEXT_OUTLINE();

    SET_TEXT_COLOUR(color);
    return;
}
void SetDrawPosRight()
{
    _SET_SCREEN_DRAW_POSITION(76, 84);
    _SCREEN_DRAW_POSITION_RATIO(Vector2(GET_SAFE_ZONE_SIZE() - 1.0f, -0.05f), 0.0f, 0.0f);
}
void SetDrawPosLeft()
{
    _SET_SCREEN_DRAW_POSITION(76, 84);
    _SCREEN_DRAW_POSITION_RATIO(Vector2(-0.05f, GET_SAFE_ZONE_SIZE() - 1.0f), 0.0f, 0.0f);
}
void DrawText(const char* str, vector2 pos, bool IsGtxText)
{
    if (IsGtxText)
    {
        if (DOES_TEXT_LABEL_EXIST(str))
        {
            BEGIN_TEXT_COMMAND_DISPLAY_TEXT(str);
            END_TEXT_COMMAND_DISPLAY_TEXT(pos);
            return;
        }
        else
            str = "INVALID_GXT";
    }
    BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
    ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str);
    END_TEXT_COMMAND_DISPLAY_TEXT(pos);
}
void DrawFloat(float value, vector2 pos)
{

    BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
    ADD_TEXT_COMPONENT_FLOAT(value, 4);
    END_TEXT_COMMAND_DISPLAY_TEXT(pos);
}
void DrawInt(int value, vector2 pos)
{

    BEGIN_TEXT_COMMAND_DISPLAY_TEXT("NUMBER");
    ADD_TEXT_COMPONENT_INTEGER(value);
    END_TEXT_COMMAND_DISPLAY_TEXT(pos);
}
void DrawBackgroundAndHeader()
{

#pragma region Background
    //Draw Background
    DRAW_RECT(
        Vector2(Container.Ui.DrawPos.x + 0.115f,
            ((((float)GetItemCountWithMaxItemLimit()
                - 1.0f)//item count needs to start at 0 for mult
                * 0.025f)//item size
                + Container.Ui.DrawPos.y * 2)
            / 2//median
        ),
        Size(Container.Ui.BackgroundDrawSize.x,
            (((float)GetItemCountWithMaxItemLimit()
                * 0.05f)
                / 2.0f)//median
            + Container.Ui.BackgroundDrawSize.y),
        Container.Ui.BackgroundColor);
#pragma endregion

#pragma region Header
    //Draw header background overlay for dark header
    DRAW_RECT(Vector2(Container.Ui.DrawPos.x + 0.115f, Container.Ui.DrawPos.y - 0.025f), Size(0.2500f, 0.0510f), RGBA(Container.Ui.BackgroundColor.red, Container.Ui.BackgroundColor.green, Container.Ui.BackgroundColor.blue, 120));

    //Draw header text
    SetUpDraw(Container.Ui.HeaderFont, 1.0f, 0.62f, true, false, false, false, Container.Ui.HeaderTextColor);
    DrawText(Container.Ui.HeaderText[Container.CurrentMenuLevel], Vector2(Container.Ui.DrawPos.x + 0.115f, Container.Ui.DrawPos.y - 0.045f), IS_BIT_SET(Container.Ui.IsHeaderGxtBitSet, Container.CurrentMenuLevel));

#pragma endregion

#pragma region Footer
    //Draw small footer background overlay for dark footer
    DRAW_RECT(Vector2(Container.Ui.DrawPos.x + 0.115f,
        ((((float)GetItemCountWithMaxItemLimit()
            - 1.0f)//item count needs to start at 0 for mult
            * 0.025f)//item size
            + 0.045f)//padding for small footer
        + Container.Ui.DrawPos.y),
        Size(0.2500f, 0.012f),
        RGBA(Container.Ui.BackgroundColor.red,
            Container.Ui.BackgroundColor.green,
            Container.Ui.BackgroundColor.blue, 120));
#pragma endregion

}
void DrawInfoBox()
{
    vector2 InfoBoxStart =
        Vector2(Container.Ui.DrawPos.x,
            ((((float)GetItemCountWithMaxItemLimit()
                - 1.0f)//item count needs to start at 0 for mult
                * 0.025f)//item size
                + Container.Ui.DrawPos.y)
            + 0.045f);


#pragma region InfoBoxBody
    if (Container.Item[GetRelativeCursorIndex].Ui.Description)
    {
        //check end pos for overlap

        float HeaderBottom = InfoBoxStart.y
            + 0.03f//header start
            + 0.039f / 2;//header size
        float StrHeight = GetStringHeight(Container.Item[GetRelativeCursorIndex].Ui.Description, Container.Ui.TextFont, 0.35f,
            InfoBoxStart.x
            + 0.239f//gets right of menu
            - 0.01f,//sub to get number pos from right of menu)
            Vector2(InfoBoxStart.x, HeaderBottom + 0.0085f));
        float InfoBoxBackgroundStart = HeaderBottom + (StrHeight / 2.0f) + (0.0085f * 2);
        float InfoBoxBackgroundHeight = StrHeight + 0.0085f * 4.0f;
        float InfoBoxFooterStart = InfoBoxBackgroundStart + InfoBoxBackgroundHeight / 2 + 0.006f;

        if (InfoBoxFooterStart + 0.006f > GET_SAFE_ZONE_SIZE() + 0.01f)
        {
            //if too large recalculate values
            InfoBoxStart =
                Vector2(Container.Ui.DrawPos.x - Container.Ui.BackgroundDrawSize.x - 0.0025,
                    Container.Ui.DrawPos.y - 0.063f);
            HeaderBottom = InfoBoxStart.y
                + 0.03f//header start
                + 0.039f / 2;//header size
            StrHeight = GetStringHeight(Container.Item[GetRelativeCursorIndex].Ui.Description, Container.Ui.TextFont, 0.35f,
                InfoBoxStart.x
                + 0.239f//gets right of menu
                - 0.01f,//sub to get number pos from right of menu)
                Vector2(InfoBoxStart.x, HeaderBottom + 0.0085f));
            InfoBoxBackgroundStart = HeaderBottom + (StrHeight / 2.0f) + (0.0085f * 2.0f);
            InfoBoxBackgroundHeight = StrHeight + 0.0085f * 4.0f;
            InfoBoxFooterStart = InfoBoxBackgroundStart + InfoBoxBackgroundHeight / 2.0f + 0.006f;
        }

#pragma region InfoBox

        DRAW_RECT(Vector2(InfoBoxStart.x + 0.115f, InfoBoxBackgroundStart), Size(0.2500f, InfoBoxBackgroundHeight),
            Container.Ui.BackgroundColor);

        SetUpDraw(Container.Ui.TextFont,
            InfoBoxStart.x
            + 0.239f//gets right of menu
            - 0.01//sub to get number pos from right of menu
            , 0.35f, false, false, false, false, Container.Ui.HeaderTextColor);
        DrawText(Container.Item[GetRelativeCursorIndex].Ui.Description, Vector2(InfoBoxStart.x, HeaderBottom + 0.0085f), false);//padding for small footer and space 

#pragma endregion

#pragma region InfoBoxFooter
        DRAW_RECT(Vector2(InfoBoxStart.x + 0.115f, InfoBoxFooterStart),
            Size(0.2500f, 0.012f),
            RGBA(Container.Ui.BackgroundColor.red,
                Container.Ui.BackgroundColor.green,
                Container.Ui.BackgroundColor.blue, Container.Ui.BackgroundColor.alpha + 30));
#pragma endregion


    }
#pragma endregion

#pragma region InfoBoxHeader
    //this draws after InfoBoxBody because we need to check overlap and update values
    DRAW_RECT(Vector2(InfoBoxStart.x + 0.115f, InfoBoxStart.y + 0.03),
        Size(0.2500f, 0.039f),
        RGBA(Container.Ui.BackgroundColor.red,
            Container.Ui.BackgroundColor.green,
            Container.Ui.BackgroundColor.blue, Container.Ui.BackgroundColor.alpha + 30));

    SetUpDraw(Container.Ui.TextFont, 1.0f, 0.35f, false, false, false, false, Container.Ui.HeaderTextColor);
    DrawText("Item Information:", Vector2(InfoBoxStart.x, InfoBoxStart.y + 0.017), false);

    SetUpDraw(Container.Ui.TextFont,
        InfoBoxStart.x
        + 0.239f//gets right of menu
        - 0.01//sub to get number pos from right of menu
        , 0.35f, false, true, false, false, Container.Ui.HeaderTextColor);

    BEGIN_TEXT_COMMAND_DISPLAY_TEXT("CM_ITEM_COUNT");
    ADD_TEXT_COMPONENT_INTEGER(Container.CursorIndex + 1);
    ADD_TEXT_COMPONENT_INTEGER(Container.TotalItemCount);
    END_TEXT_COMMAND_DISPLAY_TEXT(Vector2(0.0f, InfoBoxStart.y + 0.017f));//padding for small footer and space 
#pragma endregion


}
void DrawScrollBar()
{
    if (Container.TotalItemCount > MaxDisplayableItems)
    {
        //1.0 max
        const float BarSize = (float)MaxDisplayableItems / (float)Container.TotalItemCount;
        const float MenuItemsSize = (float)MaxDisplayableItems * 0.025f
            + 0.007f * 2.0f;//padding

        float FinalSize = BarSize * MenuItemsSize;
        float LentoGo = MenuItemsSize - FinalSize;
        float Percent = DivFloat((float)Container.ItemStartIndex, (float)(Container.TotalItemCount - MaxDisplayableItems));

        DRAW_RECT(Vector2(Container.Ui.DrawPos.x
            + 0.239f//right of menu
            - 0.002f,//scrollbar size
            Container.Ui.DrawPos.y + FinalSize / 2.0f + LentoGo * Percent),
            Size(0.004f, FinalSize),
            RGBA(200, 200, 200, 130));

    }

}
inline void SetUpDrawNum(RGBA Color, bool IsArrow, float PaddingAmount)
{
    float TextStartPosFromRight = IsArrow ? 0.018f : 0.01f;

    SetUpDraw(Container.Ui.TextFont,
        Container.Ui.DrawPos.x
        + 0.239f//gets right of menu
        - TextStartPosFromRight//sub to get number pos from right of menu
        - PaddingAmount,
        ItemFontSize, false, true, false, false, Color);
}

void DrawMenuInt(int i, float CurrentYIndex, float PaddingAmount, bool IsSelected, RGBA CurrentColor)
{
    if (IsSelected)
    {
        DRAW_SPRITE("CommonMenu", "arrowright",
            Vector2(Container.Ui.DrawPos.x + 0.229f - 0.005f - PaddingAmount, CurrentYIndex + 0.018f),
            GetSizeFromResolution(Vector2(16.0f, 16.0f)),
            0.0f,
            CurrentColor);

        if (Container.Item[i].Selection.ParseEnum != nullptr)
        {
            const char* Enum = Container.Item[i].Selection.ParseEnum(i);

            DRAW_SPRITE("CommonMenu", "arrowleft",
                Vector2(((
                    Container.Ui.DrawPos.x + 0.229f - 0.008f - PaddingAmount
                    - GetStringWidth(Enum, Container.Ui.TextFont, ItemFontSize))
                    - 0.003f)//arrow spacing
                    , CurrentYIndex + 0.018f),
                GetSizeFromResolution(Vector2(16.0f, 16.0f)),
                0.0f,
                CurrentColor);

            SetUpDrawNum(CurrentColor, true, PaddingAmount);
            DrawText(Enum, Vector2(0.0f, CurrentYIndex + 0.005f), false);
        }
        else
        {
            DRAW_SPRITE("CommonMenu", "arrowleft",
                Vector2(((
                    Container.Ui.DrawPos.x + 0.229f - 0.008f - PaddingAmount
                    - GetIntWidth(Container.Item[i].Selection.Value.Int, Container.Ui.TextFont, ItemFontSize))
                    - 0.003f)//arrow spacing
                    , CurrentYIndex + 0.018f)
                , GetSizeFromResolution(Vector2(16.0f, 16.0f)),
                0.0f,
                CurrentColor);

            SetUpDrawNum(CurrentColor, true, PaddingAmount);
            DrawInt(Container.Item[i].Selection.Value.Int, Vector2(0.0f, CurrentYIndex + 0.005f));

        }

    }
    else
    {
        //disabled text cant be selected
        if (Container.Item[i].Selection.ParseEnum != nullptr)
        {
            SetUpDrawNum(CurrentColor, false, PaddingAmount);
            DrawText(Container.Item[i].Selection.ParseEnum(i), Vector2(0.0f, CurrentYIndex + 0.005f), false);
        }
        else
        {
            SetUpDrawNum(CurrentColor, false, PaddingAmount);
            DrawInt(Container.Item[i].Selection.Value.Int, Vector2(0.0f, CurrentYIndex + 0.005f));
        }
    }


}
void DrawMenuFloat(int i, float CurrentYIndex, float PaddingAmount, bool IsSelected, RGBA CurrentColor)
{
    if (IsSelected)
    {
        DRAW_SPRITE("CommonMenu", "arrowright",
            Vector2(Container.Ui.DrawPos.x + 0.229f - 0.005f - PaddingAmount, CurrentYIndex + 0.018f)
            , GetSizeFromResolution(Vector2(16.0f, 16.0f)),
            0.0f,
            CurrentColor);
        DRAW_SPRITE("CommonMenu", "arrowleft",
            Vector2(((
                Container.Ui.DrawPos.x + 0.229f - 0.008f - PaddingAmount
                - GetFloatWidth(Container.Item[i].Selection.Value.Float, Container.Ui.TextFont, ItemFontSize))
                - 0.003f)//arrow spacing
                , CurrentYIndex + 0.018f)
            , GetSizeFromResolution(Vector2(16.0f, 16.0f)),
            0.0f,
            CurrentColor);

        SetUpDrawNum(CurrentColor, true, PaddingAmount);
        DrawFloat(Container.Item[i].Selection.Value.Float, Vector2(0.0f, CurrentYIndex + 0.005f));

    }
    else
    {
        //disabled text cant be selected
        SetUpDrawNum(CurrentColor, false, PaddingAmount);
        DrawFloat(Container.Item[i].Selection.Value.Float, Vector2(Container.Ui.DrawPos.x + 0.180f, CurrentYIndex + 0.005f));

    }


}
void DrawMenuBool(int i, float CurrentYIndex, bool IsActive, bool IsSelected, RGBA CurrentColor)
{
    if (IsSelected)
    {
        DRAW_SPRITE("CommonMenu", "shop_box_blank",
            Vector2(Container.Ui.DrawPos.x + 0.229f - 0.007f, CurrentYIndex + 0.02),
            vector2Sub(GetSizeFromResolution(Vector2(32.0f, 32.0f)), Vector2(0.004f, 0.004f)),
            0.0f,
            CurrentColor);
    }

    if (IsActive)
    {
        DRAW_SPRITE("CommonMenu", "shop_tick_icon",
            Vector2(Container.Ui.DrawPos.x + 0.229f - 0.007, CurrentYIndex + 0.02),
            vector2Sub(GetSizeFromResolution(Vector2(32.0f, 32.0f)), Vector2(0.004f, 0.004f)),
            0.0f,
            CurrentColor);
    }
}
void DrawMenuPlayer(int i, float CurrentYIndex, RGBA CurrentColor)
{
    //TODO: find a better way to detect host
    bool IsPlayerLocal = Container.Item[i].Selection.Value.Int == PLAYER_ID();
    bool IsPlayerHost = IsPlayerLocal && !NETWORK_IS_GAME_IN_PROGRESS() ? true : NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == Container.Item[i].Selection.Value.Int;
    bool DoesPlayerHaveHeadset = IsPlayerLocal ? NETWORK_HAS_HEADSET() : NETWORK_PLAYER_HAS_HEADSET(Container.Item[i].Selection.Value.Int);

    if (DoesPlayerHaveHeadset)
    {
        //TODO: find NETWORK_IS_LOCAL_TALKING equivalent on pc
#if PLATFORM == PLATFORM_PC
        bool IsPlayerTalking = NETWORK_IS_PLAYER_TALKING(Container.Item[i].Selection.Value.Int);
#else
        bool IsPlayerTalking = IsPlayerLocal ? NETWORK_IS_LOCAL_TALKING() : NETWORK_IS_PLAYER_TALKING(Container.Item[i].Selection.Value.Int);
#endif
        const char* AudioIcon = IsPlayerTalking ? "leaderboard_audio_3" : "leaderboard_audio_inactive";

        //TODO: pulsate audio icon when talking
        DRAW_SPRITE("mpleaderboard", AudioIcon,
            Vector2(Container.Ui.DrawPos.x + 0.229f - 0.005f, CurrentYIndex + 0.018f),
            vector2Sub(GetSizeFromResolution(Vector2(32.0f, 32.0f)), Vector2(0.005f, 0.005f)),
            0.0f, CurrentColor);
    }

    if (IsPlayerHost)
    {

        DRAW_SPRITE("CommonMenu", "mp_hostcrown",
            Vector2(Container.Ui.DrawPos.x + 0.229f - (DoesPlayerHaveHeadset ? 0.025f : 0.005f), CurrentYIndex + 0.018f),
            vector2Sub(GetSizeFromResolution(Vector2(32.0f, 32.0f)), Vector2(0.005f, 0.005f)), 0.0f, CurrentColor);
    }
}


void DrawItems()
{
    float CurrentYIndex = Container.Ui.DrawPos.y;
    for (int i = 0; i < GetItemCountWithMaxItemLimit(); i++, CurrentYIndex += 0.025f)
    {

        if (Container.CursorIndex == i + Container.ItemStartIndex)//draw selected
        {
            bool IsItemDisabled = bitTest(Container.Item[i].BitSet, ICB_IsItemDisabled);

            RGBA CurrentScrollBarColor = IsItemDisabled ? Container.Ui.DisabledScrollBarColor : Container.Ui.ScrollBarColor;
            RGBA CurrentColor = IsItemDisabled ? Container.Ui.DisabledSelectedTextColor : Container.Ui.SelectedTextColor;

            //draw scroll bar
            if (Container.TotalItemCount > MaxDisplayableItems)
            {
                //makes room for scroll bar
                DRAW_RECT(Vector2(Container.Ui.DrawPos.x + 0.115f - 0.005f, CurrentYIndex + 0.02f),
                    Size(Container.Ui.BackgroundDrawSize.x - 0.01f, Container.Ui.BackgroundDrawSize.y - 0.055f),
                    CurrentScrollBarColor);
            }
            else
            {
                DRAW_RECT(Vector2(Container.Ui.DrawPos.x + 0.115f, CurrentYIndex + 0.02f),
                    Size(Container.Ui.BackgroundDrawSize.x, Container.Ui.BackgroundDrawSize.y - 0.055f),
                    CurrentScrollBarColor);
            }

            SetUpDraw(Container.Ui.TextFont, 1.0f, 0.45f, false, false, false, false, CurrentColor);
            DrawText(Container.Item[i].Ui.ItemText,
                Vector2(Container.Ui.DrawPos.x, CurrentYIndex),
                bitTest(Container.Item[i].BitSet, ICB_IsItemGxt));

            //TODO: update_player_in_playerlist

            switch (Container.Item[i].Selection.Type)
            {
            case MST_None:
            case MST_Param:
                break;
            case MST_Menu:
            case MST_MenuParam:
            {
                //Hamburger Button
                SetUpDraw(Font_RockstarTAG, 1.0f, 0.5f, false, false, false, false, CurrentColor);
                DrawText("(", Vector2(Container.Ui.DrawPos.x + 0.229f - 0.046f, CurrentYIndex + 0.006f), false);
            }
            break;
            case MST_Enum:
            case MST_Int:
                DrawMenuInt(i, CurrentYIndex, 0.0f, !IsItemDisabled, CurrentColor);
                break;
            case MST_Float:
                DrawMenuFloat(i, CurrentYIndex, 0.0f, !IsItemDisabled, CurrentColor);
                break;
            case MST_Bool:
                DrawMenuBool(i, CurrentYIndex, Container.Item[i].Selection.Value.Int, !IsItemDisabled, CurrentColor);
                break;
            case MST_EnumBool:
            case MST_IntBool:
            {
                vector2 BoolTextureSize = GetSizeFromResolution(Vector2(32.0f, 32.0f));
                DrawMenuInt(i, CurrentYIndex, BoolTextureSize.x / 2, !IsItemDisabled, CurrentColor);
                DrawMenuBool(i, CurrentYIndex, bitTest(Container.Item[i].BitSet, ICB_BoolNumValue), !IsItemDisabled, CurrentColor);
            }
            break;
            case MST_FloatBool:
            {
                vector2 BoolTextureSize = GetSizeFromResolution(Vector2(32.0f, 32.0f));
                DrawMenuFloat(i, CurrentYIndex, BoolTextureSize.x / 2, !IsItemDisabled, CurrentColor);
                DrawMenuBool(i, CurrentYIndex, bitTest(Container.Item[i].BitSet, ICB_BoolNumValue), !IsItemDisabled, CurrentColor);
            }
            break;
            case MST_Player:
                DrawMenuPlayer(i, CurrentYIndex, CurrentColor);
                break;
            default:
                Warn(straddiGlobal("Draw selection type isn't valid. Value: ", Container.Item[i].Selection.Type));

            }


        }
        else //draw unselected
        {
            bool IsItemDisabled = bitTest(Container.Item[i].BitSet, ICB_IsItemDisabled);
            RGBA CurrentColor = IsItemDisabled ? Container.Ui.DisabledUnselectedTextColor : Container.Ui.UnselectedTextColor;

            SetUpDraw(Container.Ui.TextFont, 1.0f, 0.45f, false, false, false, false, CurrentColor);
            DrawText(Container.Item[i].Ui.ItemText,
                Vector2(Container.Ui.DrawPos.x,
                    CurrentYIndex),
                bitTest(Container.Item[i].BitSet, ICB_IsItemGxt));

            //TODO: update_player_in_playerlist

            switch (Container.Item[i].Selection.Type)
            {
            case MST_None:
            case MST_Param:
            case MST_Menu:
            case MST_MenuParam:
                break;
            case MST_Int:
            case MST_Enum:
                DrawMenuInt(i, CurrentYIndex, 0.0f, false, CurrentColor);
                break;
            case MST_Float:
                DrawMenuFloat(i, CurrentYIndex, 0.0f, false, CurrentColor);
                break;
            case MST_Bool:
                DrawMenuBool(i, CurrentYIndex, Container.Item[i].Selection.Value.Int, false, CurrentColor);
                break;
            case MST_EnumBool:
            case MST_IntBool:
            {
                vector2 BoolTextureSize = GetSizeFromResolution(Vector2(32.0f, 32.0f));
                DrawMenuInt(i, CurrentYIndex, BoolTextureSize.x / 2, false, CurrentColor);
                DrawMenuBool(i, CurrentYIndex, bitTest(Container.Item[i].BitSet, ICB_BoolNumValue), false, CurrentColor);
            }
            break;
            case MST_FloatBool:
            {
                vector2 BoolTextureSize = GetSizeFromResolution(Vector2(32.0f, 32.0f));
                DrawMenuFloat(i, CurrentYIndex, BoolTextureSize.x / 2, false, CurrentColor);
                DrawMenuBool(i, CurrentYIndex, bitTest(Container.Item[i].BitSet, ICB_BoolNumValue), false, CurrentColor);
            }
            break;
            case MST_Player:
                DrawMenuPlayer(i, CurrentYIndex, CurrentColor);
                break;
            default:
                Warn(straddiGlobal("Draw type isn't valid. Value: ", Container.Item[i].Selection.Type));
            }


        }
    }
}
void DrawMenu()
{
    SetDrawPosRight();
    DrawBackgroundAndHeader();
    DrawItems();
    DrawScrollBar();
    DrawInfoBox();
    _SCREEN_DRAW_POSITION_END();
}
#pragma endregion


void InitMenuDraw()
{
    InitMenuExecution();

    LoadTextureDictionary("CommonMenu");
    LoadTextureDictionary("mpleaderboard");

    InitScaleformMovie("instructional_buttons", &Container.Ui.MenuControlSFID);
    InitScaleformMovie("busy_spinner", &Container.Ui.MenuControlSFID2);

    ExecutionEntry();
}

inline void DisableControlsOnExit()
{
    if (Container.DisableMenuOpenControls > 0)
    {
        DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, true);
        DISABLE_CONTROL_ACTION(0, INPUT_COVER, true);
        Container.DisableMenuOpenControls--;
    }
}
inline void OpenMenuControls()
{
    if (HasPlayerOpenedMenu())
    {
        if (bitTest(Container.BitSet, PB_IsMenuOpen))
        {
            PlayMenuSound("QUIT");
            ShutDownMenu();
        }
        else
            bitSet(&Container.BitSet, PB_IsMenuOpen);
    }
}
inline void CheckResources()
{
    CheckTextureDictionary("CommonMenu");
    CheckTextureDictionary("mpleaderboard");
    CheckScaleformMovie("instructional_buttons", &Container.Ui.MenuControlSFID);
    CheckScaleformMovie("busy_spinner", &Container.Ui.MenuControlSFID2);
}
inline void DynamicMenuHandling()
{
    if (UpdateDynamicCursor(Container.Item[GetRelativeCursorIndex].Selection.DynamicId, Container.CursorIndex - Container.ItemStartIndex))
        Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();
}
inline void PreviousDynamicMenuChecker()
{
    for (int i = 0; i < Container.CurrentMenuLevel; i++)
    {
        if (Container.Level[i].DynamicChecker == nullptr)
            continue;
        else
        {
            if (Container.Level[i].DynamicChecker(Container.Level[i].SavedCursor.DynamicId))
                continue;
            else
            {
                UpdateMenuLevel(i - Container.CurrentMenuLevel);
            }
        }
    }
}
void HandleMenuUi()
{
    DisableControlsOnExit();
    OpenMenuControls();

    if (bitTest(Container.BitSet, PB_IsMenuOpen))
    {
        CheckResources();

        if (IS_PAUSE_MENU_ACTIVE())
            ShutDownMenu();

        PreviousDynamicMenuChecker();

        if (bitTest(Container.BitSet, PB_IsCurrentMenuDynamic))
            DynamicMenuHandling();

        while (bitTest(Container.BitSet, PB_IsCurrentMenuInvalid))
            UpdateMenuLevel(-1);

        DisableUnusedInputs();
        ParseMenuControls();

        //this is not perfect
        while (bitTest(Container.BitSet, PB_IsCurrentMenuInvalid))
            UpdateMenuLevel(-1);

        DrawMenu();
    }
    if (bitTest(Container.BitSet, PB_IsMenuOpen) || Container.Loading.FramesToLoad >= 5)
    {
        UpdateMenuControls();
        DRAW_SCALEFORM_MOVIE_FULLSCREEN(Container.Ui.MenuControlSFID2, Container.Ui.UnselectedTextColor, false);
    }
}


