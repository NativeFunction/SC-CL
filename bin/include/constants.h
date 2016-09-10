#pragma once

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define NULL 0
#define null 0
#define nullptr 0

#define KEY_ESC 1
#define KEY_1 2
#define KEY_2 3
#define KEY_3 4
#define KEY_4 5
#define KEY_5 6
#define KEY_6 7
#define KEY_7 8
#define KEY_8 9
#define KEY_9 10
#define KEY_0 11
#define KEY_MINUS 12
#define KEY_EQUAL 13
#define KEY_BACKSPACE 14
#define KEY_TAB 15
#define KEY_Q 16
#define KEY_W 17
#define KEY_E 18
#define KEY_R 19
#define KEY_T 20
#define KEY_Y 21
#define KEY_U 22
#define KEY_I 23
#define KEY_O 24
#define KEY_P 25
#define KEY_SQUARE_BRACKET_LEFT 26
#define KEY_SQUARE_BRACKET_RIGHT 27
#define KEY_ENTER 28
#define KEY_LEFT_CTRL 29
#define KEY_A 30
#define KEY_S 31
#define KEY_D 32
#define KEY_F 33
#define KEY_G 34
#define KEY_H 35
#define KEY_J 36
#define KEY_K 37
#define KEY_L 38
#define KEY_SEMI_COLON 39
#define KEY_APOSTROPHE 40
#define KEY_GRAVE 41
#define KEY_LEFT_SHIFT 42
#define KEY_BACKSLASH 43
#define KEY_Z 44
#define KEY_X 45
#define KEY_C 46
#define KEY_V 47
#define KEY_B 48
#define KEY_N 49
#define KEY_M 50
#define KEY_COMMA 51
#define KEY_PERIOD 52
#define KEY_FORWARDSLASH 53
#define KEY_RIGHT_SHIFT 54
#define KEY_ASTERISK 55
#define KEY_LEFT_ALT 56
#define KEY_SPACE 57
#define KEY_CAPS_LOCK 58
#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67
#define KEY_F10 68
#define KEY_NUMLOCK 69
#define KEY_SCROLL_LOCK 70
#define KEY_NUMPAD_7 71
#define KEY_NUMPAD_8 72
#define KEY_NUMPAD_9 73
#define KEY_NUMPAD_MINUS 74
#define KEY_NUMPAD_4 75
#define KEY_NUMPAD_5 76
#define KEY_NUMPAD_6 77
#define KEY_NUMPAD_PLUS 78
#define KEY_NUMPAD_1 79
#define KEY_NUMPAD_2 80
#define KEY_NUMPAD_3 81
#define KEY_NUMPAD_0 82
#define KEY_NUMPAD_PERIOD 83

#define KEY_F11 87
#define KEY_F12 88
#define KEY_F13 100//			(NEC PC98)
#define KEY_F14 101//			(NEC PC98)
#define KEY_F15 102//			(NEC PC98)

#define KEY_PAUSE 119//			Might Be Wrong Pause and Break acts as different keys

#define KEY_KANA 112//			(Japanese keyboard)
#define KEY_CONVERT 121//		(Japanese keyboard)
#define KEY_NOCONVERT 123//		(Japanese keyboard)
#define KEY_YEN 125//			(Japanese keyboard)
#define KEY_NUMPAD_EQUAL 141//	(NEC PC98) = on numeric keypad
#define KEY_CIRCUMFLEX 144//	(Japanese keyboard)
#define KEY_AT 145//			(NEC PC98)
#define KEY_COLON 146//			(NEC PC98)
#define KEY_UNDERLINE 147//		(NEC PC98)
#define KEY_KANJI 148//			(Japanese keyboard)
#define KEY_STOP 149//			(NEC PC98)
#define KEY_AX 150//			(Japan AX)
#define KEY_UNLABELED 151//		(J3100)
#define KEY_NUMPAD_ENTER 156
#define KEY_RIGHT_CRTL 157
#define KEY_NUMPAD_COMMA 179//	(NEC PC98) , on numeric keypad
#define KEY_NUMPAD_FORWARDSLASH 181
#define KEY_SYSRQ 183
#define KEY_RIGHT_ALT 184
#define KEY_HOME 199
#define KEY_ARROW_UP 200
#define KEY_PAGEUP 201
#define KEY_ARROW_LEFT 203
#define KEY_ARROW_RIGHT 205
#define KEY_END 207
#define KEY_ARROW_DOWN 208
#define KEY_PAGEDOWN 209
#define KEY_INSERT 210
#define KEY_DELETE 211
#define KEY_LEFT_WINDOWS 219//	Left Windows key
#define KEY_RIGHT_WINDOWS 220//	Right Windows key
#define KEY_APPMENU 221//		AppMenu key

//Other Key Definitions
#define KEY_NUMPAD_HOME 71
#define KEY_NUMPAD_UP 72
#define KEY_NUMPAD_PAGEUP 73
#define KEY_NUMPAD_LEFT 75
#define KEY_NUMPAD_RIGHT 77
#define KEY_NUMPAD_END 79
#define KEY_NUMPAD_DOWN 80
#define KEY_NUMPAD_PAGEDOWN 81
#define KEY_NUMPAD_INSERT 82
#define KEY_NUMPAD_DELETE 83
#define KEY_PRTSC 183

enum eButton
{
	BUTTON_LT,
	BUTTON_RT,
	BUTTON_LB,
	BUTTON_RB,
	BUTTON_Y,
	BUTTON_B,
	BUTTON_A,
	BUTTON_X,
	BUTTON_BACK,
	BUTTON_L3,
	BUTTON_R3,
	BUTTON_START,
	DPAD_UP,
	DPAD_RIGHT,
	DPAD_DOWN,
	DPAD_LEFT
};
