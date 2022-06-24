#include "natives.h"
#include "intrinsics.h"
#include "types.h"
#include "constants.h"
#include "common.h"

bool LoadTextureDictionary(const char* DictionaryName)
{
	if (HAS_STREAMED_TEXTURE_DICT_LOADED(DictionaryName))
		return true;

	REQUEST_STREAMED_TEXTURE_DICT(DictionaryName, 0);

	for (int i = 0; i < 100; i++)
	{
		if (HAS_STREAMED_TEXTURE_DICT_LOADED(DictionaryName))
			return true;
		WAIT(0);
	}

	Warn("Unable to load texture dictionary.");
	return false;
}
void CheckTextureDictionary(const char* DictionaryName)
{
	//TODO: add bool to not request multiple times
	if (!HAS_STREAMED_TEXTURE_DICT_LOADED(DictionaryName))
		REQUEST_STREAMED_TEXTURE_DICT(DictionaryName, 0);
}
bool InitScaleformMovie(const char* MovieName, int* SavedScaleformId)
{
	if (HAS_SCALEFORM_MOVIE_LOADED(*SavedScaleformId))
		return true;

	*SavedScaleformId = REQUEST_SCALEFORM_MOVIE(MovieName);

	for (int i = 0; i < 100; i++)
	{
		if (HAS_SCALEFORM_MOVIE_LOADED(*SavedScaleformId))
			return true;
		WAIT(0);
	}

	Warn("Unable to initialize scaleform.");
	return false;
}
void CheckScaleformMovie(const char* MovieName, int* SavedScaleformId)
{
	//TODO: add bool to not request multiple times
	if (HAS_SCALEFORM_MOVIE_LOADED(*SavedScaleformId))
		*SavedScaleformId = REQUEST_SCALEFORM_MOVIE(MovieName);
}


Size GetSizeFromTexture(const char* DictionaryName, const char* TextureName)
{
	int ScreenRes[2];
	
	GET_SCREEN_RESOLUTION(&ScreenRes[0], &ScreenRes[1]);
	vector3 TextureRes = GET_TEXTURE_RESOLUTION(DictionaryName, TextureName);
	return Vector2(TextureRes.x / (float)ScreenRes[0], TextureRes.y / (float)ScreenRes[1]);
}
Size GetSizeFromResolution(vector2 Resolution)
{
	int ScreenRes[2];
	GET_SCREEN_RESOLUTION(&ScreenRes[0], &ScreenRes[1]);
	return Vector2(Resolution.x / (float)ScreenRes[0], Resolution.y / (float)ScreenRes[1]);
}
float GetFloatWidth(float Value, Font FontType, float Scale)
{
	_BEGIN_TEXT_COMMAND_WIDTH("NUMBER");
	ADD_TEXT_COMPONENT_FLOAT(Value, 4);
	SET_TEXT_FONT(FontType);
	SET_TEXT_SCALE(1.0f, Scale);
	return _END_TEXT_COMMAND_GET_WIDTH(true);
}
float GetIntWidth(int Value, Font FontType, float Scale)
{
	_BEGIN_TEXT_COMMAND_WIDTH("NUMBER");
	ADD_TEXT_COMPONENT_INTEGER(Value);
	SET_TEXT_FONT(FontType);
	SET_TEXT_SCALE(1.0f, Scale);
	return _END_TEXT_COMMAND_GET_WIDTH(true);
}
float GetStringWidth(const char* Value, Font FontType, float Scale)
{
	_BEGIN_TEXT_COMMAND_WIDTH("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Value);
	SET_TEXT_FONT(FontType);
	SET_TEXT_SCALE(1.0f, Scale);
	return _END_TEXT_COMMAND_GET_WIDTH(true);
}
float GetStringHeight(const char* Value, Font FontType, float Scale, float Wrap, vector2 Pos)
{
	SET_TEXT_FONT(FontType);
	SET_TEXT_WRAP(0.0f, Wrap);
	SET_TEXT_SCALE(1.0f, Scale);
	_BEGIN_TEXT_COMMAND_LINE_COUNT("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Value);

	return _GET_TEXT_SCALE_HEIGHT(Scale, FontType) * (float)_END_TEXT_COMMAND_GET_LINE_COUNT(Pos);
}
void Break(const char* str)
{
	//TODO: This breaks > char Buffer[256] = "~r~Breakpoint~s~: ";
	char Buffer[256];
	strcpy(Buffer, "~r~Breakpoint~s~: ", 255);
	stradd(Buffer, str, 255);

	WAIT(0);//a button press before break
	while (!IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_ACCEPT))
	{
		print(Buffer, 1000);
		WAIT(0);
	}
	WAIT(0);//a button press after break
}
void Notify(const char* str)
{
	_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str);
	_DRAW_NOTIFICATION(false, true);
}
void PrintMult(const char* StrArr[10], int ms)
{
	BEGIN_TEXT_COMMAND_PRINT("CELL_EMAIL_BCON");
	for (int i = 0; i < 10; i++)
	{
		if (StrArr[i])
			ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(StrArr[i]);
		else
			break;
	}
	END_TEXT_COMMAND_PRINT(ms, 1);
}
bool IsPlayerInGame(int PlayerIndex)
{
	return NETWORK_IS_PLAYER_ACTIVE(PlayerIndex) && DOES_ENTITY_EXIST(GET_PLAYER_PED(PlayerIndex));
}
int FindFreeCarSeat(Vehicle VehicleToFindSeat)
{
	int MaxPassengers = GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(VehicleToFindSeat);

	for (int i = -1; i < MaxPassengers; i++)
	{
		if (IS_VEHICLE_SEAT_FREE(VehicleToFindSeat, i))
			return i;
	}
	return -2;
}
Vehicle GetCurrentVehicle()
{
	Ped MyPed = PLAYER_PED_ID();
	return IS_PED_IN_ANY_VEHICLE(MyPed, false) ? GET_VEHICLE_PED_IS_IN(MyPed, false) : 0;
}
vector3 GetCoordInFrontOfGameplayCam(float Range)
{
	vector3 GameplayCamRot = GET_GAMEPLAY_CAM_ROT(2);
	vector3 GameplayCamCoord = GET_GAMEPLAY_CAM_COORD();
	float Tan = Range * COS(GameplayCamRot.x);
	return Vector3(Tan * SIN(-GameplayCamRot.z) + GameplayCamCoord.x, Tan * COS(-GameplayCamRot.z) + GameplayCamCoord.y, Range * SIN(GameplayCamRot.x) + GameplayCamCoord.z);
}


void Assert(const char* File, int Line, const char* Expression)
{
	const int FileEndPos = GET_LENGTH_OF_LITERAL_STRING(File);
	const int ExprEndPos = GET_LENGTH_OF_LITERAL_STRING(File);
	WAIT(0);
	while (!IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_ACCEPT))
	{
		SET_TEXT_CENTRE(true);
		BEGIN_TEXT_COMMAND_DISPLAY_TEXT("CELL_EMAIL_BCON");
		ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Assertion failed!~n~~n~File: ");


		for (int i = 0; i < FileEndPos; i += 99)
			ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(File + i);

		ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(straddiGlobal("~n~Line: ", Line));
		ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~n~~n~Expression: ");

		for (int i = 0; i < ExprEndPos; i += 99)
			ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Expression + i);

		END_TEXT_COMMAND_DISPLAY_TEXT(Vector2(0.5f, 0.5f));
		WAIT(0);
	}
	WAIT(0);
}
