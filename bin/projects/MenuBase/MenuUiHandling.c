#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "common.h"

#include "Utils.h"
#include "MenuExecutionHandling.h"
#include "MenuUiHandling.h"

int externTest;

static Page Container =
{
	.Ui.HeaderFont = Font_SignPainter_HouseScript,
	.Ui.TextFont = Font_Chalet_LondonNineteenSixty,
	.Level = { ExecutionEntry },
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
	externTest = 5;
	if (is_disabled_control_pressed(2, INPUT_SCRIPT_RB))
	{
		set_input_exclusive(2, INPUT_FRONTEND_X);
		DisableControl(0, INPUT_JUMP);
		return is_disabled_control_just_pressed(2, INPUT_FRONTEND_X);
	}
	return false;
}
inline void ShutDownMenu()
{
	Container.IsMenuOpen = false;
	Container.DisableMenuOpenControls = 30;
	set_cinematic_button_active(true);
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
	if (is_mobile_phone_call_ongoing())
		stop_scripted_conversation(false);

	display_ammo_this_frame(false);
	set_cinematic_button_active(false);

	hide_hud_component_this_frame(HUD_VEHICLE_NAME);
	hide_hud_component_this_frame(HUD_AREA_NAME);
	hide_hud_component_this_frame(HUD_STREET_NAME);
	hide_hud_component_this_frame(HUD_VEHICLE_CLASS);

	//this disables hidden controls that are difficult to disable
	disable_all_control_actions(0);
	for (int i = 0; i < 338; i++)
		EnableControl(0, i);

	DisableControl(2, INPUT_NEXT_CAMERA);
	DisableControl(0, INPUT_NEXT_CAMERA);
	DisableControl(0, INPUT_VEHICLE_SELECT_NEXT_WEAPON);
	DisableControl(2, INPUT_VEHICLE_CIN_CAM);
	DisableControl(0, INPUT_HUD_SPECIAL);

	set_input_exclusive(2, INPUT_FRONTEND_ACCEPT);
	set_input_exclusive(2, INPUT_FRONTEND_CANCEL);
	set_input_exclusive(2, INPUT_FRONTEND_UP);
	set_input_exclusive(2, INPUT_FRONTEND_DOWN);
	set_input_exclusive(2, INPUT_FRONTEND_LEFT);
	set_input_exclusive(2, INPUT_FRONTEND_RIGHT);
	set_input_exclusive(2, INPUT_FRONTEND_X);

	DisableControl(2, INPUT_FRONTEND_ACCEPT);
	DisableControl(2, INPUT_FRONTEND_CANCEL);
	DisableControl(2, INPUT_FRONTEND_UP);
	DisableControl(2, INPUT_FRONTEND_DOWN);
	DisableControl(2, INPUT_FRONTEND_LEFT);
	DisableControl(2, INPUT_FRONTEND_RIGHT);

	DisableControl(0, INPUT_WEAPON_WHEEL_NEXT);
	DisableControl(0, INPUT_WEAPON_WHEEL_PREV);
	DisableControl(0, INPUT_WEAPON_SPECIAL);
	DisableControl(0, INPUT_WEAPON_SPECIAL2);
	DisableControl(0, INPUT_MELEE_ATTACK_LIGHT);
	DisableControl(0, INPUT_MELEE_ATTACK_HEAVY);
	DisableControl(0, INPUT_MELEE_BLOCK);
	DisableControl(0, INPUT_DETONATE);
	DisableControl(0, INPUT_VEHICLE_HEADLIGHT);
	DisableControl(0, INPUT_VEHICLE_RADIO_WHEEL);
	DisableControl(0, INPUT_CONTEXT);
	DisableControl(0, INPUT_RELOAD);
	DisableControl(0, INPUT_DIVE);
	DisableControl(0, INPUT_VEHICLE_SELECT_NEXT_WEAPON);
	DisableControl(0, INPUT_VEHICLE_FLY_SELECT_NEXT_WEAPON);
	DisableControl(0, INPUT_SELECT_CHARACTER_FRANKLIN);
	DisableControl(0, INPUT_SELECT_CHARACTER_MICHAEL);
	DisableControl(0, INPUT_SELECT_CHARACTER_TREVOR);
	DisableControl(0, INPUT_SELECT_CHARACTER_MULTIPLAYER);
	DisableControl(0, INPUT_CHARACTER_WHEEL);
	DisableControl(0, INPUT_COVER);

}
Page* GetMenuContainer()
{
	return &Container;
}
void SetMenuLoading(bool IsLoading)
{
	if (IsLoading)
	{
		_push_scaleform_movie_function(Container.Ui.MenuControlSFID2, "SET_BACKGROUND_COLOUR");
		_push_scaleform_movie_function_parameter_int(0);
		_push_scaleform_movie_function_parameter_int(0);
		_push_scaleform_movie_function_parameter_int(0);
		_push_scaleform_movie_function_parameter_int(0);
		_pop_scaleform_movie_function_void();
		_push_scaleform_movie_function(Container.Ui.MenuControlSFID2, "SET_SAVING_TEXT");
		_push_scaleform_movie_function_parameter_int(SFS_LOADING_CIRCLE_RIGHT);
		_begin_text_component("STRING");
		add_text_component_substring_player_name("Loading");
		_end_text_component();
		_pop_scaleform_movie_function_void();
	}
	else
	{
		Container.Loading.IsMenuLoading = false;
		_push_scaleform_movie_function(Container.Ui.MenuControlSFID2, "REMOVE_SAVING");
		_pop_scaleform_movie_function_void();
	}
	
}
void SetDataSlot(int SlotIndex, ScaleformButton ButtonId, const char* ItemText, bool IsGxtText)
{
	_push_scaleform_movie_function(Container.Ui.MenuControlSFID, "SET_DATA_SLOT");
	_push_scaleform_movie_function_parameter_int(SlotIndex);//slot index
	_push_scaleform_movie_function_parameter_int(ButtonId);//button id

	if (IsGxtText)
	{
		if (does_text_label_exist(ItemText))
		{
			_begin_text_component(ItemText);
		}
		else
		{
			_begin_text_component("STRING");
			add_text_component_substring_player_name("INVALID_GXT");
		}
	}
	else
	{
		_begin_text_component("STRING");
		add_text_component_substring_player_name(ItemText);
	}

	_end_text_component();
	_pop_scaleform_movie_function_void();
}
void UpdateMenuControls()
{
	int SlotIdCounter = 0;
	
	_push_scaleform_movie_function(Container.Ui.MenuControlSFID, "CLEAR_ALL");
	_pop_scaleform_movie_function_void();
	
	//Loading display padding
	if (Container.Loading.FramesToLoad >= 5)
		SetDataSlot(SlotIdCounter++, 255, "                  ", false);

	if (Container.IsMenuOpen)
	{
		bool IsItemEnabled = !bit_test(Container.Item[GetRelativeCursorIndex].BitSet, ICB_IsItemDisabled);

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

	_push_scaleform_movie_function(Container.Ui.MenuControlSFID, "SET_BACKGROUND_COLOUR");
	_push_scaleform_movie_function_parameter_int(Container.Ui.BackgroundColor.red);
	_push_scaleform_movie_function_parameter_int(Container.Ui.BackgroundColor.green);
	_push_scaleform_movie_function_parameter_int(Container.Ui.BackgroundColor.blue);
	_push_scaleform_movie_function_parameter_int(80);
	_pop_scaleform_movie_function_void();

	_push_scaleform_movie_function(Container.Ui.MenuControlSFID, "DRAW_INSTRUCTIONAL_BUTTONS");
	_push_scaleform_movie_function_parameter_int(0);//0 = DrawHorizontal, 1 = DrawVertical, -1 = ?
	_pop_scaleform_movie_function_void();


	DrawScaleformMovie(Container.Ui.MenuControlSFID, Container.Ui.UnselectedTextColor);
}

#pragma endregion

#pragma region Parsing
bool IsAutoScrollActive(uint* HoldCounter, int ScrollInput)
{
	bool IsControlPressed = is_disabled_control_pressed(2, ScrollInput);
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
	
	if (Container.TotalItemCount > 1)
	{
		if (is_disabled_control_just_pressed(2, INPUT_SCRIPT_PAD_UP) || (IsAutoScrollActive(&HoldUpCounter, INPUT_SCRIPT_PAD_UP)))
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
		if (is_disabled_control_just_pressed(2, INPUT_SCRIPT_PAD_DOWN) || (IsAutoScrollActive(&HoldDownCounter, INPUT_SCRIPT_PAD_DOWN)))
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

	if (!bit_test(Container.Item[GetRelativeCursorIndex].BitSet, ICB_IsItemDisabled))
	{
		MenuSelectionType CurrentType = Container.Item[GetRelativeCursorIndex].Selection.Type;
		
		//Number selector
		switch (CurrentType)
		{
			case MST_Int:
			case MST_Enum:
			case MST_IntBool:
			case MST_EnumBool:
			{
				if (is_disabled_control_just_pressed(2, INPUT_SCRIPT_PAD_LEFT) || (IsAutoScrollActive(&HoldLeftCounter, INPUT_SCRIPT_PAD_LEFT)))
				{
					PlayMenuSound("NAV_LEFT_RIGHT");
					if (Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int <= Container.Item[GetRelativeCursorIndex].Selection.StartIndex.Int)
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int = Container.Item[GetRelativeCursorIndex].Selection.EndIndex.Int;
					else
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int -= (int)Container.Item[GetRelativeCursorIndex].Selection.Precision;

				}
				else if (is_disabled_control_just_pressed(2, INPUT_SCRIPT_PAD_RIGHT) || (IsAutoScrollActive(&HoldRightCounter, INPUT_SCRIPT_PAD_RIGHT)))
				{
					PlayMenuSound("NAV_LEFT_RIGHT");
					if (Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int >= Container.Item[GetRelativeCursorIndex].Selection.EndIndex.Int)
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int = Container.Item[GetRelativeCursorIndex].Selection.StartIndex.Int;
					else
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int += (int)Container.Item[GetRelativeCursorIndex].Selection.Precision;

				}

				if (bit_test(Container.Item[GetRelativeCursorIndex].BitSet, ICB_ExecuteOnChange))
					Container.Item[GetRelativeCursorIndex].Execute();
			}
			break;
			case MST_Float:
			case MST_FloatBool:
			{
				if (is_disabled_control_just_pressed(2, INPUT_SCRIPT_PAD_LEFT) || (IsAutoScrollActive(&HoldLeftCounter, INPUT_SCRIPT_PAD_LEFT)))
				{
					PlayMenuSound("NAV_LEFT_RIGHT");
					if (Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Float <= Container.Item[GetRelativeCursorIndex].Selection.StartIndex.Float + 0.000015)//0.000000015 fixes rounding errors
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Float = Container.Item[GetRelativeCursorIndex].Selection.EndIndex.Float;
					else
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Float -= Container.Item[GetRelativeCursorIndex].Selection.Precision;

				}
				else if (is_disabled_control_just_pressed(2, INPUT_SCRIPT_PAD_RIGHT) || (IsAutoScrollActive(&HoldRightCounter, INPUT_SCRIPT_PAD_RIGHT)))
				{
					PlayMenuSound("NAV_LEFT_RIGHT");
					if (Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Float >= Container.Item[GetRelativeCursorIndex].Selection.EndIndex.Float)
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Float = Container.Item[GetRelativeCursorIndex].Selection.StartIndex.Float;
					else
						Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Float += Container.Item[GetRelativeCursorIndex].Selection.Precision;

				}

				if (bit_test(Container.Item[GetRelativeCursorIndex].BitSet, ICB_ExecuteOnChange))
					Container.Item[GetRelativeCursorIndex].Execute();
			}
			break;
			default:
			break;
		}

		if (is_disabled_control_just_pressed(2, INPUT_FRONTEND_ACCEPT))
		{
			PlayMenuSound("SELECT");
			
			if (Container.Item[GetRelativeCursorIndex].Execute != nullptr)
			{
				switch (CurrentType)
				{
					case MST_Bool:
					Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int = !Container.Item[GetRelativeCursorIndex].Selection.CursorIndex.Int;
					break;
					case MST_Menu:
					{
						Container.Level[Container.CurrentMenuLevel].SavedCursor.CursorIndex = Container.CursorIndex;
						Container.Level[Container.CurrentMenuLevel].SavedCursor.ItemStartIndex = Container.ItemStartIndex;

						Container.CurrentMenuLevel++;
						if (Container.CurrentMenuLevel < MaxMenuLevels)
						{
							Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel = Container.Item[GetRelativeCursorIndex].Execute;

							//Update to menu level
							Container.ItemStartIndex = 0;
							Container.CursorIndex = 0;
							Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();
							return;
						}
						else
						{
							Warn(straddiGlobal("Menu level out of bounds couldn't advance level. Value: ", Container.CurrentMenuLevel));
							Container.CurrentMenuLevel--;
							return;
						}
					}
					break;
					case MST_IntBool:
					case MST_FloatBool:
					case MST_EnumBool:
					bit_flip(&Container.Item[GetRelativeCursorIndex].BitSet, ICB_BoolNumValue);
					break;
					default:
					break;
				}
				Container.Item[GetRelativeCursorIndex].Execute();
			}
			else
				Throw(straddiGlobal("Execute was null at: ", Container.CursorIndex));
		}
		
		if (Container.Item[GetRelativeCursorIndex].HasAlternateExecution && is_disabled_control_just_pressed(2, INPUT_FRONTEND_X))
		{
			PlayMenuSound("SELECT");
			Container.Item[GetRelativeCursorIndex].AlternateExecute();
		}

	}

	if (is_disabled_control_just_pressed(2, INPUT_FRONTEND_CANCEL))
	{
		
		if (Container.CurrentMenuLevel == 0)
		{
			PlayMenuSound("QUIT");
			ShutDownMenu();
		}
		else
		{
			PlayMenuSound("BACK");
			Container.CurrentMenuLevel--;
			if (Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel != nullptr)
			{
				//TODO: update to last sel cursor index
				Container.ItemStartIndex = Container.Level[Container.CurrentMenuLevel].SavedCursor.ItemStartIndex;
				Container.CursorIndex = Container.Level[Container.CurrentMenuLevel].SavedCursor.CursorIndex;
				Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();
			}
			else
				Throw(straddiGlobal("MenuLevel change was null at: ", Container.CurrentMenuLevel));
		}
		
	}

}
#pragma endregion

#pragma region Drawing
void SetUpDraw(Font font, float wrap, float scale, bool center, bool right_justify, bool drop_shadow, bool outline, RGBA color)
{
	set_text_font(font);
	set_text_wrap(0.0f, wrap);
	set_text_scale(1.0f, scale);
	set_text_centre(center);
	set_text_right_justify(right_justify);
	if (drop_shadow)
		set_text_drop_shadow();

	if (outline)
		set_text_outline();

	set_text_colour(color);
	return;
}
void SetDrawPosRight()
{
	_set_screen_draw_position(76, 84);
	_screen_draw_position_ratio(Vector2(get_safe_zone_size() - 1.0f, -0.05f), 0.0f, 0.0f);
}
void SetDrawPosLeft()
{
	_set_screen_draw_position(76, 84);
	_screen_draw_position_ratio(Vector2(-0.05f, get_safe_zone_size() - 1.0f), 0.0f, 0.0f);
}
void DrawText(const char* str, vector2 pos, bool IsGtxText) {
	if (IsGtxText)
	{
		if (does_text_label_exist(str))
		{
			_set_text_entry(str);
			_draw_text(pos);
			return;
		}
		else
			str = "INVALID_GXT";
	}
	_set_text_entry("STRING");
	add_text_component_substring_player_name(str);
	_draw_text(pos);
}
void DrawFloat(float value, vector2 pos) {

	_set_text_entry("NUMBER");
	add_text_component_float(value, 4);
	_draw_text(pos);
}
void DrawInt(int value, vector2 pos) {

	_set_text_entry("NUMBER");
	add_text_component_integer(value);
	_draw_text(pos);
}
void DrawBackgroundAndHeader()
{

	#pragma region Background
	//Draw Background
	draw_rect(
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
	draw_rect(Vector2(Container.Ui.DrawPos.x + 0.115f, Container.Ui.DrawPos.y - 0.025f), Size(0.2500f, 0.0510f), RGBA(Container.Ui.BackgroundColor.red, Container.Ui.BackgroundColor.green, Container.Ui.BackgroundColor.blue, 120));

	//Draw header text
	SetUpDraw(Container.Ui.HeaderFont, 1.0f, 0.62f, true, false, false, false, Container.Ui.HeaderTextColor);
	DrawText(Container.Ui.HeaderText, Vector2(Container.Ui.DrawPos.x + 0.115f, Container.Ui.DrawPos.y - 0.045f), Container.Ui.IsHeaderGxt);

	#pragma endregion

	#pragma region Footer
	//Draw small footer background overlay for dark footer
	draw_rect(Vector2(Container.Ui.DrawPos.x + 0.115f,
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

		if (InfoBoxFooterStart + 0.006f > get_safe_zone_size() + 0.01f)
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

		draw_rect(Vector2(InfoBoxStart.x + 0.115f, InfoBoxBackgroundStart), Size(0.2500f, InfoBoxBackgroundHeight),
				  Container.Ui.BackgroundColor);

		SetUpDraw(Container.Ui.TextFont,
				  InfoBoxStart.x
				  + 0.239f//gets right of menu
				  - 0.01//sub to get number pos from right of menu
				  , 0.35f, false, false, false, false, Container.Ui.HeaderTextColor);
		DrawText(Container.Item[GetRelativeCursorIndex].Ui.Description, Vector2(InfoBoxStart.x, HeaderBottom + 0.0085f), false);//padding for small footer and space 

		#pragma endregion

		#pragma region InfoBoxFooter
		draw_rect(Vector2(InfoBoxStart.x + 0.115f, InfoBoxFooterStart),
				  Size(0.2500f, 0.012f),
				  RGBA(Container.Ui.BackgroundColor.red,
				  Container.Ui.BackgroundColor.green,
				  Container.Ui.BackgroundColor.blue, Container.Ui.BackgroundColor.alpha + 30));
		#pragma endregion


	}
	#pragma endregion

	#pragma region InfoBoxHeader
	//this draws after InfoBoxBody because we need to check overlap and update values
	draw_rect(Vector2(InfoBoxStart.x + 0.115f, InfoBoxStart.y + 0.03),
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

	_set_text_entry("CM_ITEM_COUNT");
	add_text_component_integer(Container.CursorIndex + 1);
	add_text_component_integer(Container.TotalItemCount);
	_draw_text(Vector2(0.0f, InfoBoxStart.y + 0.017f));//padding for small footer and space 
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

		draw_rect(Vector2(Container.Ui.DrawPos.x
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
		draw_sprite("CommonMenu", "arrowright",
					Vector2(Container.Ui.DrawPos.x + 0.229f - 0.005f - PaddingAmount, CurrentYIndex + 0.018f),
					GetSizeFromResolution(Vector2(16.0f, 16.0f)),
					0.0f,
					CurrentColor);

		if (Container.Item[i].Selection.ParseEnum != nullptr)
		{
			const char* Enum = Container.Item[i].Selection.ParseEnum(i);

			draw_sprite("CommonMenu", "arrowleft",
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
			draw_sprite("CommonMenu", "arrowleft",
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
		draw_sprite("CommonMenu", "arrowright",
					Vector2(Container.Ui.DrawPos.x + 0.229f - 0.005f - PaddingAmount, CurrentYIndex + 0.018f)
					, GetSizeFromResolution(Vector2(16.0f, 16.0f)),
					0.0f,
					CurrentColor);
		draw_sprite("CommonMenu", "arrowleft",
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
		draw_sprite("CommonMenu", "shop_box_blank",
					Vector2(Container.Ui.DrawPos.x + 0.229f - 0.007f, CurrentYIndex + 0.02),
					vector2Sub(GetSizeFromResolution(Vector2(32.0f, 32.0f)), Vector2(0.004f, 0.004f)),
					0.0f,
					CurrentColor);
	}

	if (IsActive)
	{
		draw_sprite("CommonMenu", "shop_tick_icon",
					Vector2(Container.Ui.DrawPos.x + 0.229f - 0.007, CurrentYIndex + 0.02),
					vector2Sub(GetSizeFromResolution(Vector2(32.0f, 32.0f)), Vector2(0.004f, 0.004f)),
					0.0f,
					CurrentColor);
	}
}
void DrawMenuPlayer(int i, float CurrentYIndex, RGBA CurrentColor)
{
	//TODO: find a better way to detect host
	bool IsPlayerLocal = Container.Item[i].Selection.Value.Int == player_id();
	bool IsPlayerHost = IsPlayerLocal && !network_is_game_in_progress() ? true : network_get_host_of_script("freemode", -1, Any(0)) == Container.Item[i].Selection.Value.Int;
	bool DoesPlayerHaveHeadset = IsPlayerLocal ? network_has_headset() : network_player_has_headset(Container.Item[i].Selection.Value.Int);

	if (DoesPlayerHaveHeadset)
	{
		//TODO: find network_is_local_talking equivalent on pc
		#ifdef __YSC__
		bool IsPlayerTalking = network_is_player_talking(Container.Item[i].Selection.Value.Int);
		#else
		bool IsPlayerTalking = IsPlayerLocal ? network_is_local_talking() : network_is_player_talking(Container.Item[i].Selection.Value.Int);
		#endif
		const char* AudioIcon = IsPlayerTalking ? "leaderboard_audio_3" : "leaderboard_audio_inactive";
		
		//TODO: pulsate audio icon when talking
		draw_sprite("mpleaderboard", AudioIcon,
					Vector2(Container.Ui.DrawPos.x + 0.229f - 0.005f, CurrentYIndex + 0.018f),
					vector2Sub(GetSizeFromResolution(Vector2(32.0f, 32.0f)), Vector2(0.005f, 0.005f)),
					0.0f, CurrentColor);
	}

	if (IsPlayerHost)
	{
		
		draw_sprite("CommonMenu", "mp_hostcrown",
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
			bool IsItemDisabled = bit_test(Container.Item[i].BitSet, ICB_IsItemDisabled);

			RGBA CurrentScrollBarColor = IsItemDisabled ? Container.Ui.DisabledScrollBarColor : Container.Ui.ScrollBarColor;
			RGBA CurrentColor = IsItemDisabled ? Container.Ui.DisabledSelectedTextColor : Container.Ui.SelectedTextColor;
			
			//draw scroll bar
			if (Container.TotalItemCount > MaxDisplayableItems)
			{
				//makes room for scroll bar
				draw_rect(Vector2(Container.Ui.DrawPos.x + 0.115f - 0.005f, CurrentYIndex + 0.02f),
						  Size(Container.Ui.BackgroundDrawSize.x - 0.01f, Container.Ui.BackgroundDrawSize.y - 0.055f),
						  CurrentScrollBarColor);
			}
			else
			{
				draw_rect(Vector2(Container.Ui.DrawPos.x + 0.115f, CurrentYIndex + 0.02f),
						  Size(Container.Ui.BackgroundDrawSize.x, Container.Ui.BackgroundDrawSize.y - 0.055f),
						  CurrentScrollBarColor);
			}

			SetUpDraw(Container.Ui.TextFont, 1.0f, 0.45f, false, false, false, false, CurrentColor);
			DrawText(Container.Item[i].Ui.ItemText,
					 Vector2(Container.Ui.DrawPos.x, CurrentYIndex),
					 bit_test(Container.Item[i].BitSet, ICB_IsItemGxt));

			//TODO: update_player_in_playerlist

			switch (Container.Item[i].Selection.Type)
			{
				case MST_None:
				case MST_Param:
				break;
				case MST_Menu:
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
					DrawMenuBool(i, CurrentYIndex, bit_test(Container.Item[i].BitSet, ICB_BoolNumValue), !IsItemDisabled, CurrentColor);
				}
				break;
				case MST_FloatBool:
				{
					vector2 BoolTextureSize = GetSizeFromResolution(Vector2(32.0f, 32.0f));
					DrawMenuFloat(i, CurrentYIndex, BoolTextureSize.x / 2, !IsItemDisabled, CurrentColor);
					DrawMenuBool(i, CurrentYIndex, bit_test(Container.Item[i].BitSet, ICB_BoolNumValue), !IsItemDisabled, CurrentColor);
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
			bool IsItemDisabled = bit_test(Container.Item[i].BitSet, ICB_IsItemDisabled);
			RGBA CurrentColor = IsItemDisabled ? Container.Ui.DisabledUnselectedTextColor : Container.Ui.UnselectedTextColor;

			SetUpDraw(Container.Ui.TextFont, 1.0f, 0.45f, false, false, false, false, CurrentColor);
			DrawText(Container.Item[i].Ui.ItemText,
					 Vector2(Container.Ui.DrawPos.x,
					 CurrentYIndex),
					 bit_test(Container.Item[i].BitSet, ICB_IsItemGxt));

			//TODO: update_player_in_playerlist

			switch (Container.Item[i].Selection.Type)
			{
				case MST_None:
				case MST_Param:
				case MST_Menu:
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
					DrawMenuBool(i, CurrentYIndex, bit_test(Container.Item[i].BitSet, ICB_BoolNumValue), false, CurrentColor);
				}
				break;
				case MST_FloatBool:
				{
					vector2 BoolTextureSize = GetSizeFromResolution(Vector2(32.0f, 32.0f));
					DrawMenuFloat(i, CurrentYIndex, BoolTextureSize.x / 2, false, CurrentColor);
					DrawMenuBool(i, CurrentYIndex, bit_test(Container.Item[i].BitSet, ICB_BoolNumValue), false, CurrentColor);
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
	_screen_draw_position_end();
}
#pragma endregion

void DynamicMenuHandling()
{
	int SavedCursorIndex = Container.CursorIndex;
	char* SavedOptions[MaxDisplayableItems];

	if (Container.TotalItemCount > MaxDisplayableItems)
	{
	}
	else
	{
		Container.Level[Container.CurrentMenuLevel].UpdateToMenuLevel();
		for (int i = 0; i < GetItemCountWithMaxItemLimit(); i++)
		{
			if (are_strings_equal(Container.Item[i].Ui.ItemText, SavedOptions[SavedCursorIndex]))
			{
				Container.CursorIndex = i;
				break;
			}

		}


	}
}

void InitMenuDraw()
{
	InitMenuExecution();

	Container.Loading.IsMenuLoading = false;
	Container.Ui.HeaderFont = Font_SignPainter_HouseScript;
	Container.Ui.TextFont = Font_Chalet_LondonNineteenSixty;
	Container.Level[0] = (MenuLevel) { ExecutionEntry, {0, 0} };
	Container.Ui.DrawPos = (vector2) { 0.76f, 0.16f };
	Container.Ui.BackgroundDrawSize = (vector2) { 0.25000, 0.08f };
	Container.Ui.BackgroundColor = (RGBA) { 0, 0, 0, 180 };
	Container.Ui.HeaderTextColor = (RGBA) { 255, 255, 255, 255 };
	Container.Ui.ScrollBarColor = (RGBA) { 230, 230, 230, 255 };
	Container.Ui.SelectedTextColor = (RGBA) { 0, 0, 0, 255 };
	Container.Ui.UnselectedTextColor = (RGBA) { 230, 230, 230, 255 };
	Container.Ui.DisabledUnselectedTextColor = (RGBA) { 155,155,155,255 };
	Container.Ui.DisabledSelectedTextColor = (RGBA) { 50, 50, 50, 255 };
	Container.Ui.DisabledScrollBarColor = (RGBA) { 190, 190, 190, 255 };
	LoadTextureDictionary("CommonMenu");
	LoadTextureDictionary("mpleaderboard");

	InitScaleformMovie("instructional_buttons", &Container.Ui.MenuControlSFID);
	InitScaleformMovie("busy_spinner", &Container.Ui.MenuControlSFID2);

	ExecutionEntry();
}
void HandleMenuUi()
{
	if (Container.DisableMenuOpenControls > 0)
	{
		DisableControl(0, INPUT_VEHICLE_CIN_CAM);
		DisableControl(0, INPUT_COVER);
		Container.DisableMenuOpenControls--;
	}

	if (HasPlayerOpenedMenu())
	{
		if (Container.IsMenuOpen)
		{
			PlayMenuSound("QUIT");
			ShutDownMenu();
		}
		else 
			Container.IsMenuOpen = true;
	}

	if (Container.IsMenuOpen)
	{
		CheckTextureDictionary("CommonMenu");
		CheckTextureDictionary("mpleaderboard");
		CheckScaleformMovie("instructional_buttons", &Container.Ui.MenuControlSFID);
		CheckScaleformMovie("busy_spinner", &Container.Ui.MenuControlSFID2);

		if (is_pause_menu_active())
			ShutDownMenu();

		DisableUnusedInputs();
		ParseMenuControls();

		if(Container.IsCurrentMenuDynamic)
			DynamicMenuHandling();

		DrawMenu();
	}
	if (Container.IsMenuOpen || Container.Loading.FramesToLoad >= 5)
	{
		UpdateMenuControls();
		DrawScaleformMovie(Container.Ui.MenuControlSFID2, Container.Ui.UnselectedTextColor);
	}
}


