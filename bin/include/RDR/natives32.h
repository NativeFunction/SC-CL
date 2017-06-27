/*H**********************************************************************
* FILENAME :	natives32.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Native functions to be used with all RDR targets and platforms of SC-CL.
*
* NOTES :
*		This file is part of SC-CL's include library.
*
* LICENSE :
*
*		Copyright 2016 SC-CL
*
*		Redistribution and use in source and binary forms, with or without
*		modification, are permitted provided that the following conditions are met:
*
*		* Redistributions of source code must retain the above copyright
*		notice, this list of conditions and the following disclaimer.
*
*		* Redistributions in binary form must reproduce the above copyright
*		notice, this list of conditions and the following disclaimer in the
*		documentation and/or other materials provided with the distribution.
*
*		* Neither SC-CL nor its contributors may be used to endorse or promote products
*		derived from this software without specific prior written permission.
*
*		* Redistribution of this software in source or binary forms shall be free
*		of all charges or fees to the recipient of this software.
*
*		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*		ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*		WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*		DISCLAIMED. IN NO EVENT SHALL SC-CL BE LIABLE FOR ANY
*		DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*		(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* AUTHORS :
*		Rocko Tompkins
*		Nathan James
*H*/
#pragma once
#include "types.h"
#include "constants.h"

//Fix for intellisense nonsense
#ifndef _MSC_VER
#define _native __attribute((native))
#define _native32(hash) __attribute((native(hash)))
#define l ;
#else
#define _native
#define _native32(hash)
#define l {};
#endif

#define SIN SIN_DEGREE
#define COS COS_DEGREE
#define TAN TAN_DEGREE
#define ATAN ATAN_DEGREE
#define ATAN2 ATAN2_DEGREE

extern _native int FLOOR(float x)l
extern _native float SIN_DEGREE(float x)l
extern _native float COS_DEGREE(float x)l
extern _native float TAN_DEGREE(float x)l
extern _native float ATAN_DEGREE(float x)l
extern _native float ATAN2_DEGREE(float x, float y)l
extern _native void UNK_0x0728B211()l
extern _native void UNK_0xF037DCA2(int pram0)l
extern _native void UNK_0x1F0CD262(int pram0)l
extern _native void RETRIEVE_GAME_STATE(int pram0, int pram1, int pram2)l
extern _native void UI_DISABLE(const char* uiLayer)l
extern _native void UI_EXCLUDE(const char* uiLayer)l
extern _native void UI_ENABLE(const char* uiLayer)l
extern _native void UI_INCLUDE(const char* uiLayer)l
extern _native int UNK_0x3B004817()l
extern _native void SET_RICH_PRESENCE(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x7CE2C2E1()l
extern _native void UNK_0x49E4EB10(int pram0)l
extern _native void TOGGLE_COVER_PROPS(int pram0)l
extern _native void LOG_MESSAGE(char* message)l
extern _native int UNK_0x814D97E8()l
extern _native void UNK_0x6CD7DCE1(int pram0, int pram1)l
extern _native int RAND_INT_RANGE(int min, int max)l
extern _native int TO_FLOAT(int pram0)l
extern _native bool UI_ISACTIVE(const char* UiLayer)l
extern _native void UI_ACTIVATE(const char* UiLayer)l
extern _native void SET_START_POS(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int REQUEST_ASSET(const char* AssetDir, eAssetType AssetType)l
extern _native void WAIT(int ms)l
extern _native int LAUNCH_NEW_SCRIPT(const char* ScriptDir, int Unk0)l
extern _native bool IS_SCRIPT_VALID(int ScriptID)l
extern _native Layout FIND_NAMED_LAYOUT(const char* LayoutName)l
extern _native32(0xFC8E55ED) bool _IS_LAYOUT_VALID(Layout Layout)l
extern _native Actor FIND_ACTOR_IN_LAYOUT(Layout Layout, const char* ActorName)l
extern _native bool IS_ACTOR_VALID(Actor Actor)l
extern _native Time MAKE_TIME_OF_DAY(int Hour, int Minute, int Second)l
extern _native void SET_WEATHER(eWeather WeatherType, Time Time)l
extern _native int STREAMING_IS_WORLD_LOADED()l
extern _native void HUD_FADE_IN(int pram0, int pram1)l
extern _native void CAMERA_RESET(int pram0)l
extern _native void STREAMING_SET_CUTSCENE_MODE(int pram0)l
extern _native void TERMINATE_THIS_SCRIPT()l
extern _native Layout CREATE_LAYOUT(const char* layoutName)l
extern _native void CLEAR_REGIONS()l
extern _native int IS_PS3()l
extern _native void UNK_0x7ABDE1F0(int pram0)l
extern _native void UNK_0x7D7F9770(int pram0)l
extern _native void PRINTNL()l
extern _native int UI_GET_NUM_CHILDREN(int pram0)l
extern _native void UI_ADD_CHILD(int pram0, int pram1)l
extern _native void UI_SET_DATA(int pram0, int pram1, int pram2)l
extern _native void UNK_0xEC86DB0E()l
extern _native void UNK_0x3B25299D(int pram0)l
extern _native void PRINTINT(int pram0)l
extern _native void PRINTSTRING(int pram0)l
extern _native void UNK_0x1C8CA53C(int pram0, int pram1)l
extern _native void UNK_0xE8960298(int pram0)l
extern _native void UNK_0xA8ADCAEB(int pram0)l
extern _native void STORE_GAME_STATE(int pram0, int pram1, int pram2)l
extern _native int UNK_0x95CDCE7A()l
extern _native void UI_SET_STRING(char* entry, char* string)l
extern _native Layout GET_AMBIENT_LAYOUT()l
extern _native void ITERATE_IN_LAYOUT(int pram0, int pram1)l
extern _native void SET_PAUSE_SCRIPT(int pram0)l
extern _native void SET_TIME_ACCELERATION(int pram0)l
extern _native void LIGHTS_SET_ON_TIME(int pram0, int pram1)l
extern _native void LIGHTS_SET_OFF_TIME(int pram0, int pram1)l
extern _native int UNK_0x8BA565F7(int pram0)l
extern _native int UNK_0xB8E09389(int pram0)l
extern _native int UNK_0x0E453CF0(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_TIME_OF_DAY(Time UnixTime)l
extern _native int NET_IS_SESSION_HOST()l
extern _native int NET_IS_IN_SESSION()l
extern _native int UNK_0x5D934CCB(int pram0, int pram1)l
extern _native float RAND_FLOAT_RANGE(float Min, float Max)l
extern _native void UNK_0xB35C0660(int pram0)l
extern _native int DECOR_GET_INT(int pram0, int pram1)l
extern _native void UNK_0x0E4B7A33(int pram0, int pram1)l
extern _native void GIVE_WEAPON_TO_ACTOR(Actor Actor, int WeaponID, int Unk0, int Unk1, int _Unk1)l
extern _native int ADD_ITEM(const char* ItemName, Actor Actor, int Unk1)l
extern _native void SET_PLAYER_DEADEYE_POINTS(int pram0, int pram1, int pram2)l
extern _native void SET_DISABLE_DEADEYE(int pram0, int pram1)l
extern _native void SET_DEADEYE_MULTILOCK_ENABLE(int pram0, int pram1)l
extern _native void SET_DEADEYE_TARGETPAINT_ENABLE(int pram0, int pram1)l
extern _native void UNK_0xCB017277(int pram0, int pram1)l
extern _native void UNK_0x98B3ABFA(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x3417766E(int pram0, int pram1, int pram2)l
extern _native32(0x5842B9D1) int _GET_CURRENT_TIME()l
extern _native void UNK_0x7D5C0C4D()l
extern _native void UNK_0x7E4A92CF(int pram0, int pram1)l
extern _native void UI_SET_MONEY(int pram0, int pram1, int pram2)l
extern _native const char* UNK_0x47EF426D(const char* pram0)l
extern _native int NET_GET_PLAYMODE()l
extern _native const char* UI_GET_STRING(const char* GXTEntry)l
extern _native void SAVE_SOFT_SAVE(int pram0)l
extern _native int UNK_0x82F63365(int pram0)l
extern _native void SET_PLAYER_CONTROL_RUMBLE(int pram0, int pram1)l
extern _native void SCRIPT_DONE_LOADING()l
extern _native int IS_EXITFLAG_SET()l
extern _native int GET_PROFILE_TIME()l
extern _native void UNK_0xB9D95B4C()l
extern _native int UNK_0x5C8DD257(int pram0)l
extern _native Time GET_TIME_OF_DAY()l
extern _native int GET_HOUR(Time T)l
extern _native int HUD_IS_FADED()l
extern _native int HUD_IS_FADING()l
extern _native void UNK_0x2E5F186B()l
extern _native int UNK_0xEF6BF96E()l
extern _native int NET_IS_UNLOCKED(int pram0)l
extern _native void PRINTFLOAT(int pram0)l
extern _native void HUD_FADE_OUT(int pram0, int pram1, int pram2)l
extern _native void RELEASE_LAYOUT_REF(int pram0)l
extern _native void UNK_0x86B0B004(int pram0, int pram1)l
extern _native int IS_BLIP_VALID(int pram0)l
extern _native void REMOVE_BLIP(int pram0)l
extern _native void ANIMAL_SPECIES_GRINGO_CLEAR_ALL()l
extern _native void STREAMING_EVICT_PROP(int pram0)l
extern _native void STREAMING_EVICT_PROPSET(int pram0)l
extern _native void STREAMING_EVICT_ACTOR(int pram0, int pram1)l
extern _native int GET_ASSET_NAME(int pram0, int pram1)l
extern _native void REMOVE_ANIM_SET(int pram0)l
extern _native void STREAMING_EVICT_GRINGO(int pram0)l
extern _native void REMOVE_ACTION_TREE(int pram0)l
extern _native void REMOVE_STRING_TABLE(int pram0)l
extern _native void STREAMING_EVICT_SCRIPT(int pram0)l
extern _native void STREAMING_UNREQUEST_MOVABLE_NAV_MESH(int pram0)l
extern _native void UNK_0x32FCA813(int pram0)l
extern _native void LOG_ERROR(char* message)l
extern _native int ABS(int pram0)l
extern _native void REMOVE_COLLECTABLE(int pram0, int pram1)l
extern _native int ROUND(int pram0)l
extern _native int UNK_0xFA6BDD8E(int pram0, int pram1, int pram2)l
extern _native32(0x8ED1FF95) const char* _FLOAT_TO_STRING(float Flt, int unk3, int Precision)l
extern _native const char* INT_TO_STRING(int i)l
extern _native void CLEAR_STAT_MESSAGE()l
extern _native int STRING_TO_HASH(int pram0)l
extern _native void SET_STAT_MESSAGE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12)l
extern _native bool IS_STRING_VALID(const char* pram0)l
extern _native void LOG_WARNING(char* message)l
extern _native int ADD_COLLECTABLE(int pram0, int pram1, int pram2)l
extern _native int SHIFT_LEFT(int pram0, int pram1)l
extern _native int UNK_0x7AB722D8()l
extern _native int UNK_0x84B0B5D6()l
extern _native int IS_ACTOR_ALIVE(int pram0)l
extern _native void SET_WEAPON_GOLD(Actor Actor, int Weapon, bool Gold)l
extern _native void UNK_0x7D6A8D4A(int pram0, int pram1)l
extern _native int HAS_ACHIEVEMENT_BEEN_PASSED(int pram0)l
extern _native int AWARD_ACHIEVEMENT(int pram0)l
extern _native int AWARD_AVATAR(int pram0)l
extern _native int DECOR_CHECK_EXIST(int pram0, int pram1)l
extern _native bool IS_DEV_BUILD()l
extern _native const char* SS_GET_STRING(int pram0, int pram1)l
extern _native int SAVE_GAME(int pram0)l
extern _native void UNK_0x17F34613(int pram0)l
extern _native void UNK_0xED40F27D(int pram0)l
extern _native int UNK_0xBAB151CB()l
extern _native int UNK_0x5545C218(int pram0)l
extern _native int UNK_0xE623B382(int pram0)l
extern _native int GET_PLAYER_DEADEYE_POINTS(int pram0)l
extern _native int GET_NUM_JOURNAL_ENTRIES_IN_LIST(int pram0)l
extern _native int GET_JOURNAL_ENTRY_IN_LIST(int pram0, int pram1)l
extern _native int GET_JOURNAL_ENTRY_TYPE(int pram0)l
extern _native int GET_JOURNAL_ENTRY_MISC_FLAG(int pram0)l
extern _native int IS_JOURNAL_ENTRY_UPDATED(int pram0)l
extern _native int GET_TARGETED_JOURNAL_ENTRY()l
extern _native int UNK_0x118D085E(int pram0)l
extern _native int UNK_0xA4B2016D(int pram0)l
extern _native int UNK_0x6262DC5E(int pram0, int pram1)l
extern _native int UNK_0x0CDD6F94(int pram0)l
extern _native int UNK_0x7BF75BCE(int pram0, int pram1)l
extern _native int UNK_0x4BB2BC20(int pram0, int pram1)l
extern _native int UNK_0x78A3CD3D(int pram0)l
extern _native int UNK_0x7F4D5AE0(int pram0, int pram1)l
extern _native int IS_FRONTEND_DEATH(int pram0, int pram1, int pram2)l
extern _native Weapon GET_WEAPON_EQUIPPED(Actor Actor, int Index)l
extern _native int UNK_0x0E0EFB13(int pram0)l
extern _native int UNK_0x2C23CBE7(int pram0)l
extern _native int UNK_0x608DCAEF(int pram0, int pram1)l
extern _native int UNK_0xCC02BBD3(int pram0)l
extern _native int UNK_0xA8040D70(int pram0)l
extern _native int UNK_0xCCE4A339(int pram0)l
extern _native32(0x0ADC17E9) bool _IS_ACTOR_PLAYER(Actor actorId)l
extern _native Actor GET_PLAYER_ACTOR(int PlayerId)l
extern _native int GET_DAY(Time T)l
extern _native float FABS(float f)l
extern _native int UNK_0x6CC9CCE7()l
extern _native int GET_ITEM_COUNT(int pram0, int pram1)l
extern _native void PRINT_OBJECTIVE_FORMAT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int DECOR_SET_INT(int pram0, int pram1, int pram2)l
extern _native bool IS_OBJECT_VALID(Object Object)l
extern _native int GET_OBJECT_POSITION(int pram0, int pram1)l
extern _native int GET_OBJECT_TYPE(int pram0)l
extern _native void GET_VOLUME_SCALE(int pram0, int pram1)l
extern _native int ADD_BLIP_FOR_COORD(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_BLIP_SCALE(int pram0, int pram1)l
extern _native void SET_BLIP_COLOR(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_BLIP_PRIORITY(int pram0, int pram1)l
extern _native void SET_BLIP_NAME(int pram0, int pram1)l
extern _native int IS_JOURNAL_ENTRY_IN_LIST(int pram0, int pram1)l
extern _native int CREATE_JOURNAL_ENTRY(int pram0, int pram1, int pram2, int pram3)l
extern _native void APPEND_JOURNAL_ENTRY(int pram0, int pram1)l
extern _native void PREPEND_JOURNAL_ENTRY_DETAIL(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_JOURNAL_ENTRY_DETAIL_STYLE(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_JOURNAL_ENTRY_PROGRESS(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x2AA8E2FA(int pram0, int pram1, int pram2)l
extern _native int IS_JOURNAL_ENTRY_TARGETED(int pram0)l
extern _native void REMOVE_JOURNAL_ENTRY(int pram0, int pram1)l
extern _native void UNK_0x87DC7F5B(int pram0, int pram1)l
extern _native void TARGET_JOURNAL_ENTRY(int pram0)l
extern _native void CLEAR_JOURNAL_ENTRY(int pram0)l
extern _native int UNK_0x60135878()l
extern _native int UNK_0x4B2FCAF6()l
extern _native int UNK_0x2F0E7DE7()l
extern _native int UNK_0x710B3A83()l
extern _native int UNK_0x7AB368CF(int pram0, int pram1)l
extern _native void UNK_0x08A655C5(int pram0, int pram1)l
extern _native void UNK_0x1E98AFEC(int pram0, int pram1)l
extern _native void UNK_0xFF3DB575(int pram0, int pram1)l
extern _native int SHIFT_RIGHT(int pram0, int pram1)l
extern _native int VDIST(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x115CD0CC(int pram0)l
extern _native void UNK_0x4F52CB58(int pram0)l
extern _native void DESTROY_OBJECT(Object Object)l
extern _native int IS_DOOR_VALID(int pram0)l
extern _native int DECOR_GET_OBJECT(int pram0, int pram1)l
extern _native int IS_DOOR_LOCKED(int pram0)l
extern _native int UNK_0x502DAC62(int pram0)l
extern _native int IS_ACTOR_IN_VOLUME(int pram0, int pram1)l
extern _native int GATEWAY_UPDATE(int pram0)l
extern _native int UNK_0xD7591B0E(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int WAS_SCRIPT_USE_CONTEXT_EVER_PRESSED(int pram0)l
extern _native int UNK_0x64BEDDEA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12, int pram13, int pram14, int pram15, int pram16, int pram17)l
extern _native int ADD_BLIP_FOR_OBJECT(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xE3E30992(int pram0)l
extern _native void UNK_0xCE79F8E2(int pram0, int pram1)l
extern _native int GET_GRINGO_FROM_OBJECT(int pram0)l
extern _native void GRINGO_ALLOW_ACTIVATION(int pram0, int pram1)l
extern _native int DECOR_REMOVE(int pram0, int pram1)l
extern _native int UNK_0xCB3F7DA5(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int DECOR_SET_BOOL(Actor Actor, const char* DecorName, bool set)l
extern _native void PRINT_MONEY(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void SET_DOOR_LOCK(int pram0, int pram1)l
extern _native int GET_LATEST_CONSOLE_COMMAND()l
extern _native void RESET_LATEST_CONSOLE_COMMAND()l
extern _native int STRING_CONTAINS_STRING(int pram0, int pram1)l
extern _native int UNK_0x8C37CA1A(int pram0, int pram1)l
extern _native int UNK_0x39286DE5(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x6745191B(int pram0, int pram1, int pram2, int pram3)l
extern _native void TERMINATE_SCRIPT(int ScriptID)l
extern _native int UNK_0x3B1B6407()l
extern _native void UNK_0x4C02E1E5()l
extern _native void REQUEST_ANIM_SET(int pram0, int pram1)l
extern _native int REQUEST_ACTION_TREE(int pram0)l
extern _native int HAS_ANIM_SET_LOADED(int pram0)l
extern _native int HAS_ACTION_TREE_LOADED(int pram0)l
extern _native int SET_ANIM_SET_FOR_ACTOR(int pram0, int pram1, int pram2)l
extern _native int SET_ACTION_NODE_FOR_ACTOR(int pram0, int pram1)l
extern _native int SET_REACT_NODE_FOR_ACTOR(int pram0, int pram1)l
extern _native int GET_NUM_CONSOLE_COMMAND_TOKENS()l
extern _native int GET_CONSOLE_COMMAND_TOKEN(int pram0)l
extern _native int UNK_0xAC830865(int pram0, int pram1)l
extern _native void GET_VOLUME_CENTER(int pram0, int pram1)l
extern _native int FIND_GROUND_INTERSECTION(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x19B26C78(int pram0)l
extern _native void UNK_0x272D756C(int pram0, int pram1, int pram2)l
extern _native void UNK_0x76341F1A(int pram0)l
extern _native void UNK_0x5A6418A2(int pram0, int pram1)l
extern _native void UNK_0xBCD4979C(int pram0, int pram1, int pram2)l
extern _native void UNK_0x30C67D05(int pram0)l
extern _native void UNK_0x762192EB(int pram0)l
extern _native void UNK_0x309D058C(int pram0)l
extern _native void UNK_0x1900A97E(int pram0, int pram1)l
extern _native void UNK_0xAA99E18E(int pram0)l
extern _native void UNK_0x2CCE1115(int pram0)l
extern _native float STRING_TO_FLOAT(const char* Str)l
extern _native Iterator CREATE_OBJECT_ITERATOR(Layout layout)l
extern _native void ITERATE_ON_OBJECT_TYPE(Iterator Iterator, int Type)l
extern _native Object START_OBJECT_ITERATOR(Iterator Iterator)l
extern _native int UNK_0x024B2FFC(int pram0)l
extern _native int UNK_0x36CC24A4(int pram0)l
extern _native void UNK_0x4028CE77(int pram0)l
extern _native int OBJECT_ITERATOR_NEXT(int pram0)l
extern _native void DESTROY_ITERATOR(int pram0)l
extern _native int STRING_LENGTH(const char* pram0)l
extern _native int STRING_UPPER(int pram0)l
extern _native32(0x8218D693) bool _STRING_COMPARE(const char* Str1, const char* Str2)l
extern _native int STRING_TO_INT(const char* pram0)l
extern _native void GET_POSITION(int pram0, vector3* outCoords)l
extern _native float GET_HEADING(int pram0)l
extern _native int LOAD_SOFT_SAVE(int pram0)l
extern _native int DOES_FILE_EXIST(int pram0)l
extern _native int LOAD_GAME(int pram0)l
extern _native int UNK_0x8C710D3E(int pram0)l
extern _native void NET_LOG(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native Camera GET_GAME_CAMERA()l
extern _native void GET_CAMERA_DIRECTION(Camera Cam, vector3* OutDirection)l
extern _native void GET_CAMERA_POSITION(Camera Cam, vector3* OutPosition)l
extern _native void VSCALE(vector3* Vector, float Scale)l
extern _native int GET_ACTORENUM_FROM_STRING(const char* ActorName)l //case sensitive
extern _native void STREAMING_REQUEST_ACTOR(int pram0, int pram1, int pram2)l
extern _native int STREAMING_IS_ACTOR_LOADED(int pram0, int pram1)l
extern _native int UNK_0x4A2063EC(int pram0)l
extern _native int GET_OBJECT_ORIENTATION(int pram0, int pram1)l
extern _native Layout UNK_0xADE13224()l//ambient object layout?
extern _native Actor CREATE_ACTOR_IN_LAYOUT(Layout Layout, const char* ActorName, eActor ActorID, vector3 Position, vector3 Rotation)l
extern _native void TASK_STAND_STILL(int pram0, int pram1, int pram2, int pram3)l
extern _native int STRING_LOWER(int pram0)l
extern _native void KILL_ACTOR(int pram0)l
extern _native void PRINT_FRAME_TIME(int pram0)l
extern _native int LAUNCH_NEW_SCRIPT_WITH_ARGS(int pram0, int pram1, int pram2, int pram3)l
extern _native int GET_ACTOR_AXIS(int pram0, int pram1, int pram2)l
extern _native void SCRIPT_BREAKPOINT(int pram0)l
extern _native int UNK_0x025C9845(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native Object CREATE_PROP_IN_LAYOUT(Layout Layout, const char* PropName, const char* FragmentPath, vector3 Position, vector3 Rotation, bool Frozen)l
extern _native int FIND_OBJECT_IN_OBJECT(int pram0, int pram1)l
extern _native int IN_TARGETTING_POSSE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int SNAP_ACTOR_TO_GRINGO(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void AUDIO_MUSIC_FORCE_TRACK(const char* SongName, const char* Mood, int pram2, int pram3, int pram4, float pram5, int pram6)l
extern _native int UNK_0x6A9CFA2A(int pram0)l
extern _native int AI_IGNORE_ACTOR(int pram0)l
extern _native void UNK_0x4DF3C5D1()l
extern _native int UNK_0xCCB57C38(int pram0)l
extern _native void UNK_0x5AEB2E4F(int pram0)l
extern _native int UNK_0x17883570(int pram0)l
extern _native void UNK_0x10873616()l
extern _native int SET_OWNERSHIP_STRAGGLER(int pram0, int pram1)l
extern _native int STRING_NUM_TOKENS()l
extern _native int STRING_GET_TOKEN(int pram0)l
extern _native int UNK_0x990614C1(int pram0)l
extern _native int IS_VOLUME_VALID(int pram0)l
extern _native void UNK_0xC0C6245E(int pram0)l
extern _native int GET_OBJECT_NAME(int pram0)l
extern _native int UNK_0x2803BDA8(int pram0)l
extern _native void UNK_0x1BD78730(int pram0, int pram1, int pram2)l
extern _native int UNK_0xF437B3D9(int pram0, int pram1, int pram2, int pram3)l
extern _native int GET_OBJECT_RELATIVE_POSITION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GET_OBJECT_RELATIVE_ORIENTATION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xC07681C1(int pram0, int pram1, int pram2, int pram3)l
extern _native int GET_ASSET_ID(const char* AssetPath, eAssetType AssetType)l
extern _native void STREAMING_REQUEST_PROPSET(int pram0)l
extern _native int STREAMING_IS_PROPSET_LOADED(int pram0)l
extern _native void UNK_0x836466F8(int pram0)l
extern _native int UNK_0x779267C3(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int UNK_0x51D6DA2C(int pram0)l
extern _native int UNK_0x5219B7D0(int pram0)l
extern _native int DECOR_CHECK_STRING(Object decor, const char* EventType, const char* EventName)l
extern _native void UNK_0x3E509DF1(int pram0, int pram1)l
extern _native int UNK_0xDB70DF0C(int pram0)l
extern _native void SET_PHYSINST_FROZEN(int pram0, int pram1)l
extern _native int UNK_0x6B72661F(int pram0)l
extern _native int UNK_0x3CD2C250(int pram0)l
extern _native int ADD_AI_COVERSET_FOR_PROPSET(int pram0)l
extern _native int GET_VEHICLE(int pram0)l
extern _native void PRINTVECTOR(int pram0, int pram1, int pram2)l
extern _native void UNK_0xD695F857(int pram0)l
extern _native int UNK_0x8F4B473D(int pram0, int pram1, int pram2)l
extern _native void TASK_KILL_CHAR(int pram0, int pram1)l
extern _native void TASK_MELEE_ATTACK(int pram0, int pram1, int pram2)l
extern _native int ACTOR_MOUNT_ACTOR(int pram0, int pram1)l
extern _native void RESET_ANALOG_POSITIONS(int pram0, int pram1)l
extern _native void ITERATE_IN_SPHERE(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GET_NUM_ITERATOR_MATCHES(int pram0)l
extern _native int UNK_0x960DB7A5()l
extern _native bool IS_ITERATOR_VALID(Iterator iterator)l
extern _native void ITERATE_EVERYWHERE(int pram0)l
extern _native int UNK_0xB578DB52(int pram0)l
extern _native int UNK_0xE07C2D99(int pram0)l
extern _native void UNK_0x6761D53A(int pram0, int pram1)l
extern _native int UNK_0x85C58BE1(int pram0)l
extern _native void UNK_0x2D6CD106(int pram0, int pram1)l
extern _native int UNK_0xD60032F6(int pram0)l
extern _native Object FIND_OBJECT_IN_LAYOUT(Layout Layout, const char* ObjectName)l
extern _native int IS_CRIME_VALID(int pram0)l
extern _native void SET_CRIME_TYPE(int pram0, int pram1)l
extern _native void SET_CRIME_VICTIM(int pram0, int pram1)l
extern _native void SET_CRIME_CRIMINAL(int pram0, int pram1)l
extern _native void UNK_0x2AE7D51F(int pram0, int pram1)l
extern _native void UNK_0x898B00F4(int pram0, int pram1)l
extern _native int SET_CRIME_POSITION(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x921B5F2B(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_CRIME_OBJECTSET(int pram0, int pram1)l
extern _native void SET_CRIME_FACTION(int pram0, int pram1)l
extern _native void UNK_0x54E7F26B(int pram0, int pram1)l
extern _native void SET_CRIME_COUNTER(int pram0, int pram1)l
extern _native void UNK_0x8521A685(int pram0, int pram1)l
extern _native int UNK_0x831338D9(int pram0)l
extern _native int UNK_0x2CB3B980(int pram0)l
extern _native int UNK_0x43FBBDE1(int pram0, int pram1)l
extern _native int SET_ACTOR_TIME_OF_LAST_CRIME(int pram0, int pram1)l
extern _native void ITERATE_IN_SET(Iterator Iterator, IterationSet IterationSet)l
extern _native int GET_ITERATOR_PARENT(int pram0)l
extern _native int UNK_0x7C3D1193(int pram0)l
extern _native void ADD_TIME(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_RAIN_AMOUNT(float Amount)l
extern _native void UNK_0xF0C9645A(float Amount)l
extern _native void UNK_0xEB866555()l
extern _native void SET_WIND(int pram0, int pram1, int pram2)l
extern _native void SET_AUTO_WIND()l
extern _native void UNK_0x063F900A(int pram0)l
extern _native bool DOES_SCRIPT_EXIST(const char* ScriptPath)l
extern _native void FILE_START_PATH(int pram0)l
extern _native void UNK_0x63CDBB01(int pram0)l
extern _native void FILE_END_PATH()l
extern _native int UNK_0x6F323C5F()l
extern _native int UNK_0x4417C9F2(int pram0)l
extern _native void UNK_0x05719022(int pram0)l
extern _native int NET_START_NEW_SCRIPT(int pram0, int pram1)l
extern _native int UNK_0xC739D1D2(int pram0)l
extern _native int UNK_0xB50E95D7(int pram0)l
extern _native void UNK_0x95FBA0B0(int pram0, int pram1)l
extern _native void SET_PLAYER_CONTROL(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x243AF970(int pram0, int pram1, int pram2)l
extern _native void UNK_0x598815BD(int pram0)l
extern _native32(0xE42A8278) void _PRINT_HELP(char* txt, float time, bool isStringLiteral, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int UNK_0x9C9529D8(int pram0, int pram1)l
extern _native int GET_MINUTE(Time T)l
extern _native int GET_SECOND(Time T)l
extern _native int IS_OBJECTSET_VALID(int pram0)l
extern _native int GET_OBJECTSET_SIZE(int pram0)l
extern _native void CLEAN_OBJECTSET(int pram0)l
extern _native int UNK_0x50D39153(int pram0, int pram1)l
extern _native void UNK_0xA3E05BAE(int pram0, int pram1)l
extern _native int UNK_0x49D0DF2E(int pram0)l
extern _native void RELEASE_CURVE(int pram0)l
extern _native int VMAG(int pram0, int pram1, int pram2)l
extern _native int UNK_0xD3FE15FB()l
extern _native int UNK_0xD34F7B3A()l
extern _native int UNK_0x913A5CB6()l
extern _native int UNK_0x214AFB8C(int pram0)l
extern _native int UNK_0x2AF84928(int pram0)l
extern _native int UNK_0x87C5471F(int pram0)l
extern _native int CEIL(int pram0)l
extern _native void UNK_0x4D918005(int pram0, int pram1)l
extern _native int HAS_ITEM(int pram0, int pram1)l
extern _native void DELETE_ITEM(int pram0, int pram1, int pram2)l
extern _native void UNK_0x40121E4F(int pram0, int pram1)l
extern _native void UNK_0xDE84B637(int pram0, int pram1)l
extern _native void AI_SPEECH_SET_ALLOW_CONTEXT_GLOBAL(int pram0, int pram1)l
extern _native void SET_ACTOR_SHOULD_TAUNT(int pram0, int pram1)l
extern _native void UNK_0x4B0D6152(int pram0, int pram1)l
extern _native int UNK_0x0CC3D8F6(int pram0, int pram1)l
extern _native int UNK_0xFAC315B7(int pram0, int pram1, int pram2)l
extern _native int DECOR_SET_FLOAT(int pram0, int pram1, int pram2)l
extern _native void UPDATE_PROFILE_STAT(int pram0, int pram1, int pram2)l
extern _native void SET_JOURNAL_ENTRY_TROPHY(int pram0, int pram1)l
extern _native int UNK_0x5CAFCBD4(int pram0, int pram1, int pram2)l
extern _native int GET_AMMO_ENUM(int pram0)l
extern _native int UNK_0xDB679ED9(int pram0)l
extern _native void UNK_0x4372593E(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xA534CD14(int pram0, int pram1, int pram2)l
extern _native int IS_POINT_IN_VOLUME(int pram0, int pram1, int pram2, int pram3)l
extern _native int IS_ACTOR_RIDING(int pram0)l
extern _native int IS_ANY_SPEECH_PLAYING(int pram0)l
extern _native void UNK_0x31BAF169(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int GET_ACTOR_VELOCITY(int pram0, int pram1)l
extern _native int GET_CAMERA_CHANNEL_POSITION(int pram0, int pram1)l
extern _native int GET_ACTOR_HEALTH(int pram0)l
extern _native int GET_ACTOR_MAX_HEALTH(int pram0)l
extern _native int IS_ACTOR_IN_WATER(int pram0)l
extern _native void SET_BLIP_BLINK(int pram0, int pram1, int pram2, int pram3)l
extern _native int IS_ACTOR_DRIVING_VEHICLE(int pram0)l
extern _native int UNK_0x5D41D423(int pram0)l
extern _native int UNK_0xDF024C94(int pram0, int pram1, int pram2)l
extern _native void HUD_CLEAR_OBJECTIVE()l
extern _native32(0xE4DACF40) void _CLEAR_PRINTS()l
extern _native32(0x32394BB6) void _PRINT_SUBTITLE(const char* txt, float time, bool isStringLiteral, int printType, int pram4, int pram5, int pram6, int pram7)l
extern _native void SET_DEADEYE_POINT_MODIFIER(int pram0, int pram1)l
extern _native void SET_MAX_DEADEYE_POINTS(int pram0, int pram1)l
extern _native void UNK_0x27A96719(int pram0, int pram1)l
extern _native void SET_WEATHER_COMPLEX(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12, int pram13, int pram14)l
extern _native void ITERATE_ON_PARTIAL_NAME(int pram0, int pram1)l
extern _native void ITERATE_ON_PARTIAL_MODEL_NAME(int pram0, int pram1)l
extern _native void HUD_CLEAR_BIG_TEXT()l
extern _native void HUD_CLEAR_COUNTER()l
extern _native void HUD_CLEAR_HELP()l
extern _native void HUD_CLEAR_SMALL_TEXT()l
extern _native void UNK_0x777A1CA2()l
extern _native void HUD_CLEAR_HELP_QUEUE()l
extern _native void UNK_0x02E1E708()l
extern _native void CLEAR_GPS_PATH(int pram0)l
extern _native int UNK_0x5C51D43C(int pram0, int pram1)l
extern _native int UNK_0xFDF42AAC(int pram0, int pram1)l
extern _native void UNK_0xD923CD1B(int pram0, int pram1)l
extern _native int UNK_0x0E2C4B68(int pram0, int pram1)l
extern _native int UNK_0xFAD5A270(int pram0, int pram1)l
extern _native void UNK_0xA9459BB6(int pram0, int pram1, int pram2)l
extern _native void UNK_0x9D9784B8(int pram0, int pram1)l
extern _native void UNK_0xE1124E00()l
extern _native void RESET_GAME()l
extern _native void UNK_0x9C80A3A4(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void EQUIP_ACCESSORY(int pram0, int pram1, int pram2)l
extern _native int UNK_0xA677B204(int pram0)l
extern _native int ACTOR_HAS_WEAPON(int pram0, int pram1)l
extern _native int UNK_0xFEEC4EE2(int pram0)l
extern _native void ENABLE_WEATHER_SPHERE(int pram0, int pram1)l
extern _native void UNK_0xC0556FB8(int pram0, int pram1)l
extern _native int APPEND_REGION(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0xA17311E4(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native int UNK_0x177A3843(int pram0, int pram1)l
extern _native void UNK_0xB104FF3E(int pram0, int pram1)l
extern _native int UNK_0x31D76951(int pram0, int pram1)l
extern _native int UNK_0x1FEECD4C(int pram0)l
extern _native int UNK_0x24C18749(int pram0, int pram1, int pram2)l
extern _native void UNK_0x08765C6B(int pram0, int pram1)l
extern _native void UNK_0xFD0AA999()l
extern _native void UNK_0xBFB65BE8()l
extern _native void UNK_0x71BE51F4()l
extern _native int IS_MISSION_SCRIPT()l
extern _native int STREAMING_REQUEST_PROP(int pram0, int pram1)l
extern _native void STREAMING_REQUEST_GRINGO(int pram0)l
extern _native void REQUEST_STRING_TABLE(const char* StringTablePath)l
extern _native void STREAMING_REQUEST_SCRIPT(int pram0)l
extern _native void STREAMING_REQUEST_MOVABLE_NAV_MESH(int pram0)l
extern _native void UNK_0x620649B4(int pram0)l
extern _native int STREAMING_IS_PROP_LOADED(int pram0)l
extern _native int STREAMING_IS_GRINGO_LOADED(int pram0)l
extern _native bool HAS_STRING_TABLE_LOADED(const char* StringTablePath)l
extern _native int STREAMING_IS_SCRIPT_LOADED(int pram0)l
extern _native int STREAMING_IS_MOVABLE_NAV_MESH_RESIDENT(int pram0)l
extern _native int UNK_0x67994764(int pram0)l
extern _native32(0x9C424E0D) int _GET_ID_OF_THIS_SCRIPT()l
extern _native int UNK_0x01309706(int pram0)l
extern _native void UNK_0x90CD8795(int pram0, int pram1)l
extern _native void UNK_0x9E88643A(int pram0, int pram1)l
extern _native void UNK_0xDAD46FAB()l
extern _native32(0xB731EB45) void _CHEAT_INFINITE_HORSE_STAMINA(bool Activate)l
extern _native32(0x3F67DEDB) int _CHEAT_BLAZING_GUNS(bool Activate)l
extern _native void UNK_0x7D0EFDD8(int pram0)l
extern _native void PUSH_COMMAND_HANDLE(int pram0, int pram1)l
extern _native void UNK_0xF1A723D0(int pram0, int pram1)l
extern _native void CREATE_STAT(int pram0, int pram1, int pram2, int pram3)l
extern _native void DISABLE_CHILD_SECTOR(int pram0)l
extern _native void ENABLE_CHILD_SECTOR(int pram0)l
extern _native void SET_CURVE_WEIGHT(int pram0, int pram1)l
extern _native void DISABLE_WORLD_SECTOR(int pram0)l
extern _native void ENABLE_WORLD_SECTOR(int pram0)l
extern _native int ENABLE_CURVE(int pram0, int pram1)l
extern _native int UNK_0xC7612A79(int pram0, int pram1)l
extern _native void UNK_0xD44F7102(int pram0, int pram1, int pram2)l
extern _native const char* VECTOR_TO_STRING(vector3* Vec)l
extern _native void AUDIO_MUSIC_SET_STATE(int pram0)l
extern _native int UNK_0x38771B89(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int UNK_0xC426D16F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void LOAD_AUDIO_BANK(const char* RefName, const char* BankPath)l
extern _native32(0x98CD7340) bool _IS_AUDIO_BANK_LOADING(const char* RefName, const char* BankPath)l
extern _native void UNK_0x176E921C(const char* pram0)l
extern _native int REQUEST_MISSION_AUDIO_BANK(const char* pram0)l
extern _native void UNK_0xA82D893C(int pram0, int pram1)l
extern _native void DESTROY_VOLUME(int pram0)l
extern _native void UNK_0xBFD6D55F(int pram0, int pram1)l
extern _native void SET_PLAYER_ENDLESS_READYMODE(int pram0, int pram1)l
extern _native void RESET_ANIM_SET_FOR_ACTOR(int pram0, int pram1)l
extern _native void SET_PLAYER_POSTURE(int pram0, int pram1, int pram2)l
extern _native int UNK_0xD86BFBD8(int pram0, int pram1)l
extern _native void UNK_0x851F88F6(int pram0)l
extern _native void UNK_0xF86010D1(int pram0, int pram1)l
extern _native void UNK_0xBAEC56D1(int pram0)l
extern _native void APPEND_JOURNAL_ENTRY_DETAIL(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GET_PLAYER_COMBATMODE()l
extern _native int DECOR_GET_FLOAT(int pram0, int pram1)l
extern _native void DISBAND_OBJECTSET(int pram0)l
extern _native int UNK_0xF5EE5874(int pram0)l
extern _native int UNK_0x2F358B89(int pram0, int pram1)l
extern _native int UNK_0x061A2A3C()l
extern _native void UNK_0xCA840DBB(int pram0)l
extern _native int UNK_0x0B1569C5(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9A73C2CD()l
extern _native int UNK_0x8E0D7219(int pram0, int pram1)l
extern _native void UI_SEND_EVENT(int pram0)l
extern _native int UNK_0xD8E31D42()l
extern _native int UNK_0x4BA92498()l
extern _native void SET_CAMERA_POSITION(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_CAMERA_ORIENTATION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_CAMERA_DIRECTION(Camera Cam, vector3 Direction, bool Unk1)l
extern _native void SET_CURRENT_CAMERA_ON_CHANNEL(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void UNK_0x2A3B1045(int pram0)l
extern _native void UNK_0x8F82B7D4(int pram0, int pram1)l
extern _native void UNK_0x9E6D7105(int pram0)l
extern _native void UNK_0xBB2EABF9(int pram0)l
extern _native void UNK_0x18346D88()l
extern _native void UNK_0x0C197810()l
extern _native void REMOVE_CAMERA_FROM_CHANNEL(int pram0, int pram1)l
extern _native void DESTROY_LAYOUT(int pram0)l
extern _native void HUD_ENABLE(int pram0)l
extern _native void SETTIMERA(int pram0)l
extern _native int UNK_0x82A290D4()l
extern _native int UNK_0x111554E2(int pram0)l
extern _native int UNK_0xC64DF45D()l
extern _native int UI_ISFOCUSED(const char* UiLayer)l
extern _native int NET_IS_ONLINE_AVAILABLE()l
extern _native int UNK_0xCF02D1D6(int pram0)l
extern _native bool IS_BUTTON_PRESSED(Controller Controller, eButton Button, int Unk1, int Unk0)l
extern _native void UI_EXIT(const char* uiLayer)l
extern _native int UNK_0x03962973()l
extern _native void DESTROY_OBJECTSET(int pram0)l
extern _native int UNK_0x2D160228(int pram0, int pram1)l
extern _native int SQUAD_IS_VALID(int pram0)l
extern _native int SQUAD_GET_SIZE(int pram0)l
extern _native int SQUAD_GET_ACTOR_BY_INDEX(int pram0, int pram1)l
extern _native void UNK_0xEA86A817(int pram0)l
extern _native void UNK_0x1D4786CF(int pram0)l
extern _native void UNK_0xED6D63FE(int pram0)l
extern _native int UNK_0xE18028C1(int pram0)l
extern _native void UNK_0x25690082(int pram0)l
extern _native void UNK_0x57478561(int pram0)l
extern _native void SQUAD_LEAVE(int pram0)l
extern _native void DESTROY_ACTOR(int pram0)l
extern _native void RELEASE_ACTOR_AS_AMBIENT(int pram0)l
extern _native void RELEASE_ACTOR(Actor Actor)l
extern _native int CAMERA_IS_VISIBLE_ACTOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void RELEASE_OBJECT_REF(int pram0)l
extern _native32(0xF6207DF5) GUIWindow _GUI_GET_WINDOW(int GUIHandle, const char* WindowName)l
extern _native int GUI_WINDOW_VALID(int pram0)l
extern _native int GUI_CLOSE_WINDOW(int pram0)l
extern _native void UNK_0x5AC72FCC(int pram0)l
extern _native void UNK_0x73BE57AF(int pram0)l
extern _native void UNK_0xA094152A(int pram0)l
extern _native void SET_ACTOR_INVULNERABILITY(Actor Actor, bool Invulnerable)l
extern _native void UNK_0xA737CCAC(int pram0)l
extern _native void UI_POP(const char* pram0)l
extern _native void STREAMING_UNLOAD_BOUNDS()l
extern _native int UNK_0xCE043618()l
extern _native void UNK_0x0DFF578A(int pram0, int pram1, int pram2)l
extern _native int WOULD_ACTOR_BE_VISIBLE(int pram0, int pram1, int pram2)l
extern _native int UNK_0x44A34042(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void SQUAD_MAKE_EMPTY(int pram0)l
extern _native int UNK_0x1D69F321(int pram0, int pram1, int pram2)l
extern _native void TASK_BIRD_LAND_AT_COORD(int pram0, int pram1)l
extern _native int UNK_0x5F7176D6()l
extern _native int GET_WEATHER()l
extern _native int FIND_NAMED_POPULATION_SET(int pram0)l
extern _native int IS_POPSET_VALID(int pram0)l
extern _native int OBJECT_ITERATOR_CURRENT(int pram0)l
extern _native int IS_GRINGO_VALID(int pram0)l
extern _native int UNK_0xE2DCFF34(int pram0, int pram1, int pram2)l
extern _native void UNK_0x8EB5CE58(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x0DC149BD(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xD92BA5B6(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int UNK_0xFF8CBD07(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int GET_LOCATOR_OFFSETS(int pram0, int pram1, int pram2, int pram3)l
extern _native int SET_OBJECT_POSITION(Object Obj, vector3 Position)l
extern _native void UNK_0x47C5E353(int pram0, int pram1)l
extern _native void UNK_0x3932B786(int pram0)l
extern _native int UNK_0xF7277A0F(int pram0, int pram1)l
extern _native int UNK_0xD0C471FB(int pram0)l
extern _native int GET_ACTOR_FROM_OBJECT(int pram0)l
extern _native bool IS_ACTOR_VEHICLE(Actor Actor)l
extern _native int UNK_0x994F2BD1(int pram0, int pram1)l
extern _native void UNK_0x43F59172(int pram0)l
extern _native void UNK_0x52D984AF(int pram0)l
extern _native void AI_GOAL_LOOK_CLEAR(int pram0)l
extern _native void UNK_0x031E983D(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void SET_ACTOR_ALLOW_WEAPON_REACTIONS(int pram0, int pram1)l
extern _native void AI_QUICK_EXIT_GRINGO(int pram0, int pram1)l
extern _native int GET_LAST_ATTACKER(int pram0)l
extern _native int GET_RIDER(int pram0)l
extern _native void TASK_CLEAR(int pram0)l
extern _native void TASK_WANDER(int pram0, int pram1)l
extern _native void MEMORY_PREFER_RIDING(int pram0, int pram1)l
extern _native void RELEASE_LAYOUT_OBJECTS(int pram0)l
extern _native bool IS_ACTOR_RIDING_VEHICLE(Actor Actor)l
extern _native int GET_MOUNT(int pram0)l
extern _native int UNK_0xF68C926F(int pram0)l
extern _native int UNK_0xD85CA776(int pram0)l
extern _native int GET_DRAFT_ACTOR(int pram0, int pram1)l
extern _native bool IS_ACTOR_DEAD(Actor actor)l
extern _native int IS_OBJECT_IN_OBJECTSET(int pram0, int pram1)l
extern _native const char* GET_ACTOR_NAME(Actor actor)l
extern _native int UNK_0x1449EE9E(int pram0)l
extern _native void AI_SET_NAV_MATERIAL_USAGE(int pram0, int pram1, int pram2)l
extern _native void SET_ACTOR_EXEMPT_FROM_AMBIENT_RESTRICTIONS(int pram0, int pram1)l
extern _native void SET_ACTOR_OBEY_AMBIENT_MOVE_RESTRICTIONS(int pram0, int pram1)l
extern _native void AI_SET_ENABLE_DEAD_BODY_REACTIONS(int pram0, int pram1)l
extern _native int DECOR_SET_OBJECT(int pram0, int pram1, int pram2)l
extern _native int DECOR_GET_BOOL(int pram0, int pram1)l
extern _native int CAMERA_IS_VISIBLE_POINT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void MEMORY_IDENTIFY(int pram0, int pram1)l
extern _native void MEMORY_CONSIDER_AS(int pram0, int pram1, int pram2)l
extern _native int IS_AI_ACTOR_UNALERTED(int pram0)l
extern _native void AI_GOAL_LOOK_AT_ACTOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void UNK_0xFE5715A1(int pram0, int pram1, int pram2)l
extern _native void UNK_0x15B7044B(int pram0, int pram1, int pram2, int pram3)l
extern _native bool IS_ACTOR_ON_FOOT(int actor)l
extern _native void AI_SET_PLAYER_PROJECTILE_IMPACT_HEAR_RANGE(int pram0, int pram1)l
extern _native int AI_HAS_PLAYER_PROJECTILE_IMPACTED_WITHIN(int pram0, int pram1)l
extern _native int AI_HAS_PLAYER_PROJECTILE_NEAR_MISSED_WITHIN(int pram0, int pram1, int pram2)l
extern _native int UNK_0xA5A24484(int pram0)l
extern _native int UNK_0x86BAAC6C(int pram0, int pram1)l
extern _native int IS_PLAYER_WEAPON_ZOOMED(int pram0)l
extern _native int MEMORY_GET_IS_VISIBLE(int pram0, int pram1)l
extern _native int UNK_0x02365961(int pram0)l
extern _native int UNK_0x7F454A92(int pram0)l
extern _native void CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(int pram0)l
extern _native void AI_SPEECH_SET_ALLOW_FOR_ACTOR(int pram0, int pram1)l
extern _native void UNK_0x99AFD2D1(int pram0, int pram1, int pram2)l
extern _native int GET_ACTOR_ENUM(int pram0)l
extern _native void UNK_0xC1F9A360(int pram0)l
extern _native void UNK_0xAD42EABC(int pram0, int pram1)l
extern _native int UNK_0x5C4262F9(int pram0)l
extern _native int UNK_0x6C939AA7(int pram0, int pram1)l
extern _native void TASK_USE_GRINGO(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_ACTOR_STAY_WITHIN_VOLUME(int pram0, int pram1, int pram2, int pram3)l
extern _native void AI_GOAL_LOOK_AT_NEUTRAL(int pram0, int pram1)l
extern _native int UNK_0xFA37C0FA(int pram0, int pram1, int pram2)l
extern _native void TASK_PRIORITY_SET(int pram0, int pram1)l
extern _native void TASK_WANDER_IN_VOLUME(int pram0, int pram1, int pram2)l
extern _native void SQUAD_JOIN(int pram0, int pram1)l
extern _native int UNK_0x7080E24A(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9A93E7CA(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x002B0698(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x9AA8A1B1(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x426828CB(int pram0)l
extern _native int GRINGO_ENABLE_SPAWN(int pram0, int pram1)l
extern _native int ATTACH_OBJECTS(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int IS_ATTACHMENT_VALID(int pram0)l
extern _native int UNK_0x000079CB(int pram0)l
extern _native int UNK_0x1F003E6C(int pram0, int pram1, int pram2)l
extern _native int UNK_0x35CD589C(int pram0)l
extern _native void CREATE_OBJECT_GLOW(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void RELEASE_VOLUME(int pram0)l
extern _native void ADD_AI_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME_SET(int pram0, int pram1)l
extern _native void UNK_0x0ACF7E75(int pram0)l
extern _native void REMOVE_AI_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME_SET(int pram0, int pram1)l
extern _native void UNK_0x80FF115A(int pram0)l
extern _native int UNK_0xD3503922(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int GET_ACTORENUM_SPECIES(int pram0)l
extern _native int IS_POPULATION_SET_READY(int pram0, int pram1, int pram2)l
extern _native int UNK_0x8FD12F97(int pram0)l
extern _native int GET_ACTORENUM_IN_POPULATION(int pram0, int pram1)l
extern _native int GET_ACTORENUM_IN_POPULATION_WEIGHT(int pram0, int pram1)l
extern _native void TASK_FLEE_ACTOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void MEMORY_CLEAR_ALL(int pram0)l
extern _native int GET_CURRENT_GRINGO(int pram0)l
extern _native int UNK_0x111501F7(int pram0)l
extern _native int CREATE_CORPSE_IN_LAYOUT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int REQUEST_FIXED_CORPSE(int pram0, int pram1)l
extern _native void UNK_0x05D69EA6(int pram0, int pram1)l
extern _native int UNK_0xCC277C0A(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int UNK_0x3DD1DC3F(int pram0, int pram1)l
extern _native int UNK_0x9C40E671(int pram0)l
extern _native int SET_OBJECT_POSITION_ON_GROUND(Object Obj, vector3 Position)l
extern _native int UNK_0x7A6146DB(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void SET_CAMERA_FOCUS_PROMPT_TEXT(int pram0, int pram1)l
extern _native void UNK_0x601FC9F4(int pram0, int pram1)l
extern _native void UNK_0x04A38C60(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native const char* GET_SCRIPT_NAME()l
extern _native int GET_TOTAL_MINUTES(int pram0)l
extern _native int UNK_0xA5FF6076(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x0E018669(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int UNK_0x8E551A7C(int pram0)l
extern _native int UNK_0xE531DCAE(int pram0, int pram1, int pram2)l
extern _native int UNK_0xBD4E48A6(int pram0, int pram1)l
extern _native void UNK_0xDF93BD7C(int pram0)l
extern _native int IS_PERS_CHAR_ALIVE(int pram0)l
extern _native int UNK_0x2CA16327(int pram0)l
extern _native void AMBIENT_SET_SEARCH_CENTER_PLAYER()l
extern _native void UNK_0xA89B77A7(int pram0, int pram1)l
extern _native void UNK_0x609514AE(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x45190938(int pram0, int pram1, int pram2)l
extern _native void UNK_0x912EEC43(int pram0, int pram1, int pram2)l
extern _native void UNK_0x9A35520B(int pram0)l
extern _native void UNK_0xA337135A(int pram0)l
extern _native void UNK_0x0AC99007(int pram0, int pram1)l
extern _native void UNK_0x54BD1C65(int pram0, int pram1)l
extern _native void UNK_0xC8B149B4(int pram0)l
extern _native int UNK_0x0C6EF9E1(int pram0, int pram1)l
extern _native void UNK_0xB1609063(int pram0)l
extern _native void UNK_0x9CD2B55F(int pram0, int pram1, int pram2)l
extern _native void UNK_0x391F3607(int pram0, int pram1, int pram2)l
extern _native int UNK_0xBADCF1E9(int pram0)l
extern _native void UNK_0x19D652F9(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x30A9FA0A(int pram0, int pram1)l
extern _native int GET_X(int pram0)l
extern _native int GET_Z(int pram0)l
extern _native int CREATE_POPULATION_SET(int pram0)l
extern _native void UNK_0x0C1B8DEA(int pram0, int pram1, int pram2)l
extern _native void UNK_0x50ED77F1(int pram0, int pram1)l
extern _native void AI_SET_ENABLE_HORSE_CHARGE_REACTIONS(int pram0, int pram1)l
extern _native void UNK_0xF4429710(int pram0, int pram1)l
extern _native void UNK_0xB421AFCA(int pram0)l
extern _native void HOGTIE_ACTOR(int pram0)l
extern _native void TASK_FACE_ACTOR(int pram0, int pram1, int pram2, int pram3)l
extern _native void MEMORY_SET_WEAPON_DRAW_PREFERENCE(int pram0, int pram1)l
extern _native void TASK_POINT_GUN_AT_OBJECT(int pram0, int pram1, int pram2, int pram3)l
extern _native int IS_ACTOR_HOGTIED(int pram0)l
extern _native int GET_HOGTIED_MASTER(int pram0)l
extern _native int UNK_0xFF0B53EF()l
extern _native int AI_IS_HOSTILE_OR_ENEMY(int pram0, int pram1)l
extern _native int UNK_0xA936E73B(int pram0, int pram1)l
extern _native void MARK_OBJECT_FOR_AGGRESSIVE_CLEANUP(int pram0, int pram1)l
extern _native void UNK_0xA8BD64D1(int pram0)l
extern _native void MEMORY_REPORT_POSITION_AUTO(int pram0, int pram1, int pram2)l
extern _native int ADD_BLIP_FOR_ACTOR(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0xA4F209D5(int pram0)l
extern _native int IS_AMBIENT_SPEECH_PLAYING(int pram0)l
extern _native int UNK_0xD98CB6F6(int pram0)l
extern _native int TASK_SEQUENCE_OPEN()l
extern _native void TASK_SEQUENCE_CLOSE()l
extern _native void TASK_SEQUENCE_PERFORM(int pram0, int pram1)l
extern _native void TASK_SEQUENCE_RELEASE(int pram0, int pram1)l
extern _native void UNK_0xA343FDBB()l
extern _native int UNK_0x7957CA4F(int pram0, int pram1, int pram2)l
extern _native void TASK_MOUNT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void SET_ACTOR_ONE_SHOT_DEATH(int pram0, int pram1)l
extern _native void UNK_0x2EBE540D(int pram0, int pram1)l
extern _native void COMBAT_CLASS_AI_SET_FRIENDLY_FIRE_CONSIDERATION(int pram0, int pram1)l
extern _native void COMBAT_CLASS_AI_SET_ATTRIB_FLOAT(int pram0, int pram1, int pram2)l
extern _native int UNK_0xF270EAC1(int pram0)l
extern _native int DECOR_SET_VECTOR(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xBF680846(int pram0)l
extern _native int UNK_0x016C6801(int pram0, int pram1)l
extern _native int ACTORS_IN_RANGE(int pram0, int pram1, int pram2)l
extern _native void PRINT_HELP_FORMAT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native32(0xB114332D) int _PUSH_NEG_ONE()l
extern _native void UNK_0x45589499(int pram0)l
extern _native int GUI_SET_TEXT(int TextHandle, const char* MenuName)l
extern _native32(0xCBC97619) bool _IS_KEY_PRESSED(eKey KeyCode)l
extern _native int GUI_MAKE_TEXT(int GUIHandle, SizedArray Position, const char* MenuTitle, const char* GXTText, float pram4)l
extern _native int GUI_SET_TEXT_COLOR(int TextHandle, float* ColorArea)l
extern _native32(0x524F6981) Controller _GET_ACTOR_CONTROLLER(int ActorId)l
extern _native float GET_STICK_Y(Controller Controller, bool IsRightStick, int unk1)l
extern _native float GET_STICK_X(Controller Controller, bool IsRightStick, int unk1)l
extern _native void UNK_0x3C2D93C1(float x, float y, const char* Text, float r, float g, float b, float a)l
extern _native int GUI_SET_TEXT_JUSTIFY(int TextHandle, int JustifyType)l
extern _native int GET_TASK_STATUS(int pram0, int pram1)l
extern _native void MEMORY_CLEAR_EVENTS(int pram0, int pram1)l
extern _native int UNK_0xAFB1CC55(int pram0)l
extern _native int AI_IMPAIRMENT_MASK_MATCHES(int pram0, int pram1)l
extern _native int SQUAD_GET(int pram0)l
extern _native int UNK_0xAEDD7512(int pram0)l
extern _native int SAY_SINGLE_LINE_STRING_BEAT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void UNK_0xBA734A15(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native bool IS_ACTOR_HUMAN(int actor)l
extern _native void MEMORY_ALLOW_TAKE_COVER(int pram0, int pram1)l
extern _native int UNK_0xEE0AB3DD(int pram0)l
extern _native int GET_CRIME_CRIMINAL(int pram0)l
extern _native int GET_CRIME_TYPE(int pram0)l
extern _native int IS_ACTOR_ON_TRAIN(int pram0, int pram1)l
extern _native int GET_LAST_HIT_TIME(int pram0)l
extern _native int UNK_0xFF5F7D2C(int pram0, int pram1)l
extern _native int UNK_0xCC04895F(int pram0, int pram1)l
extern _native int UNK_0xB1FCFFDC(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x4685D538(int pram0, int pram1, int pram2, int pram3)l
extern _native int GRINGO_UPDATE_INT(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_ACTOR_UPDATE_PRIORITY(int pram0, int pram1)l
extern _native int UNK_0xBE5D84BF(int pram0)l
extern _native void GET_FORMATION_LOCATION(int pram0, int pram1, int pram2)l
extern _native void SET_DRAW_ACTOR(Actor pram0, bool ToDraw)l
extern _native void CLEAR_ACTOR_MAX_SPEED(int pram0)l
extern _native bool IS_ACTOR_ANIMAL(Actor Actor)l
extern _native int ANIMAL_ACTOR_GET_SPECIES(int pram0)l
extern _native void ANIMAL_SPECIES_REL_SET_CAN_ATTACK(int pram0, int pram1, int pram2)l
extern _native void COMBAT_CLASS_AI_SET_ATTRIB_BOOL(int pram0, int pram1, int pram2)l
extern _native void MEMORY_ALLOW_SHOOTING(int pram0, int pram1)l
extern _native void SET_ACTOR_MAX_SPEED(int pram0, int pram1)l
extern _native void UNK_0xD1CF9793(int pram0)l
extern _native int ADD_SCRIPT_USE_CONTEXT_IN_VOLUME(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int UNK_0x758F993A(int pram0)l
extern _native void BREAK_OFF_ABOVE(int pram0, int pram1)l
extern _native int SET_PROP_VELOCITY(int pram0, int pram1)l
extern _native int UNK_0xFADF0B96(int pram0)l
extern _native void SET_VOLUME_ENABLED(int pram0, int pram1)l
extern _native void UNK_0xDC6DEE92(int pram0, int pram1)l
extern _native void AI_SET_ENABLE_STICKUP_OVERRIDE(int pram0, int pram1)l
extern _native void SET_ACTOR_CUTSCENE_MODE(int pram0, int pram1)l
extern _native void AUDIO_MUSIC_ONE_SHOT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x9398BE8F(int pram0)l
extern _native bool ENABLE_VEHICLE_SEAT(Actor Vehicle, int SeatId, bool Enable)l
extern _native int DECOR_SET_STRING(int pram0, int pram1, int pram2)l
extern _native int CREATE_WEAPON_PICKUP(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void SET_DRAW_OBJECT(int pram0, int pram1)l
extern _native int UNK_0xDAB0D820(int pram0)l
extern _native int UNK_0x3ACE659E(int pram0)l
extern _native Actor GET_ACTOR_IN_VEHICLE_SEAT(Vehicle Veh, int SeatID)l
extern _native32(0xE7023D23) void _CREATE_EXPLOSION(vector3* coords, const char* explosionName, bool pram2, vector3* damageVector, bool pram4)l
extern _native int UNK_0xF04335A6(int pram0, int pram1)l
extern _native int UNK_0x4FF36FA7(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int IS_PHYSINST_VALID(int pram0)l
extern _native int UNK_0x0550E178(int pram0)l
extern _native int UNK_0x659532FB(int pram0, int pram1)l
extern _native void UNK_0x9AC1CA75(int pram0, int pram1, int pram2)l
extern _native int UNK_0xCBB2267A(int pram0, int pram1)l
extern _native int GET_OBJECT_OWNER(int pram0)l
extern _native int UNK_0x65C3D8F6()l
extern _native int ATTACH_DRAFT_TO_VEHICLE(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xB12584C8(int pram0, int pram1)l
extern _native void UNK_0x6F9C399B(int pram0)l
extern _native void UNK_0xCB1E8485(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0x12325AE7(int pram0)l
extern _native void START_VEHICLE(Actor Vehicle)l
extern _native void STREAMING_UNLOAD_SCENE()l
extern _native int UNK_0xE975BE40(int pram0)l
extern _native int IS_ACTOR_USING_LEDGE(int pram0)l
extern _native int UNK_0x231E7034(int pram0)l
extern _native int UNK_0x8FFDCE5C(int pram0, int pram1)l
extern _native void ENABLE_USE_CONTEXTS(int pram0)l
extern _native void UNK_0x15547025()l
extern _native void UNK_0xF03CC7A7(int pram0)l
extern _native int UNK_0x21C59F4C(int pram0)l
extern _native void REMOVE_AMBIENT_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(int pram0)l
extern _native int DOES_AMBIENT_SPAWN_RESTRICTION_VOLUME_EXIST(int pram0)l
extern _native void REMOVE_AMBIENT_SPAWN_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(int pram0)l
extern _native void UI_PUSH(const char* pram0)l
extern _native void UNK_0x5C94F6EC(int pram0, int pram1, int pram2, int pram3)l
extern _native void PLAY_CUTSCENEOBJECT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void UNK_0xDCC91F8C(int pram0, int pram1)l
extern _native void STOP_VEHICLE(int pram0)l
extern _native int UNK_0xA923A22D(int pram0, int pram1, int pram2, int pram3)l
extern _native int CHECK_CUTSCENE_COLLISIONS(int pram0)l
extern _native int GET_CAMERA_FROM_CUTSCENEOBJECT(int pram0)l
extern _native int SET_CAMERA_LIGHTING_SCHEME(int pram0, int pram1)l
extern _native void SET_CUTSCENEOBJECT_PAUSED(int pram0, int pram1)l
extern _native int GET_CAMERASHOT_FROM_CUTSCENEOBJECT(int pram0, int pram1)l
extern _native void UNK_0xDCD3A7DE(int pram0, int pram1)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_HOLD(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_CAMERASHOT_PERSPECTIVE(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_FOV(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_NEAR_CLIP_PLANE(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_COLLISION_PARAMETERS(int pram0, int pram1, int pram2)l
extern _native void SET_CAMERASHOT_COLLISION_ENABLED(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_POSITION(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_CAMERASHOT_ORIENTATION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0x714D6F72(int pram0)l
extern _native void UI_CLEAR_MESSAGE_QUEUE(int pram0)l
extern _native int ABORT_SCRIPTED_CONVERSATION(int pram0)l
extern _native void ADD_COMPANION_PERMANENT()l
extern _native void FREE_FROM_HOGTIE(int pram0)l
extern _native void TASK_OVERRIDE_SET_POSTURE(int pram0, int pram1)l
extern _native void SET_ACTOR_HEALTH(int pram0, int pram1)l
extern _native int IS_PLAYER_DEADEYE(int pram0)l
extern _native void CANCEL_DEADEYE()l
extern _native void UNK_0xAF50E8A1(int pram0)l
extern _native void UNK_0x11A65FFB(int pram0)l
extern _native void UNK_0x0F474297(int pram0)l
extern _native void UNK_0x15001332()l
extern _native void UNK_0xAF94B7D9()l
extern _native void CLEAR_CHARACTER_BLOOD()l
extern _native void CLEAR_TUMBLEWEEDS()l
extern _native int UNK_0xD4048969(int pram0)l
extern _native void DESTROY_CAMERA(int pram0)l
extern _native void UNK_0xE6C1DBD9(int pram0)l
extern _native void SHOW_PHYSINST(int pram0)l
extern _native void UNK_0xA5A6A3E3(int pram0, int pram1, int pram2)l
extern _native void AUDIO_MUSIC_SUSPEND(int pram0)l
extern _native void AUDIO_MUSIC_RELEASE_CONTROL(int pram0, int pram1)l
extern _native int GET_CRIME_POSITION(int pram0, int pram1)l
extern _native void PLAYER_RUMBLE(int pram0, int pram1, int pram2)l
extern _native int IS_ACTOR_CRIPPLED(int pram0, int pram1)l
extern _native void MEMORY_PREFER_WALKING(int pram0, int pram1)l
extern _native int GET_ACTOR_FROM_PERS_CHAR(int pram0)l
extern _native void REFERENCE_ACTOR(int pram0)l
extern _native void SET_PERS_CHAR_EXEMPT_FROM_AMBIENT_RESTRICTIONS(int pram0, int pram1)l
extern _native void TASK_FOLLOW_OBJECT_AT_DISTANCE(int pram0, int pram1, int pram2, int pram3)l
extern _native void TASK_GO_NEAR_COORD(int pram0, int pram1, int pram2, int pram3)l
extern _native void TASK_VEHICLE_LEAVE(int pram0)l
extern _native void TASK_SEARCH(int pram0, int pram1, int pram2)l
extern _native int CREATE_NAV_QUERY(int pram0, int pram1)l
extern _native void NAV_QUERY_START_CAN_PATH_TO_POINT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int NAV_QUERY_IS_DONE(int pram0)l
extern _native int NAV_QUERY_CAN_PATH_TO_POINT(int pram0)l
extern _native int UNK_0xBCC98808(int pram0)l
extern _native void UNK_0x3ECD8FEE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x9613C2D0(int pram0)l
extern _native int FIND_NEAREST_DOOR(int pram0, int pram1)l
extern _native int IS_PLAYER_IN_COMBAT(int pram0)l
extern _native int IS_ACTOR_MALE(int pram0)l
extern _native void UNK_0x91DE3A31(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int GET_CRIME_VICTIM(int pram0)l
extern _native void UNK_0xAF6A3160(int pram0, int pram1)l
extern _native int ACTOR_HOLSTER_WEAPON(int pram0, int pram1)l
extern _native int IS_ACTOR_RAGDOLL(int pram0)l
extern _native void TELEPORT_ACTOR(Actor Actor, vector3* Position, bool Unk1, bool _Unk1, bool __Unk1)l
extern _native void DEREFERENCE_ACTOR(int pram0)l
extern _native void NAV_QUERY_STOP(int pram0)l
extern _native void AI_ACTOR_SET_MATCH_WALK_SPEED_ENABLED(int pram0, int pram1)l
extern _native void AI_COMBAT_SET_NEW_STATE_MACHINE_ENABLED(int pram0, int pram1)l
extern _native int UNK_0x35B5587D(int pram0)l
extern _native int GRINGO_UPDATE_BOOL(int pram0, int pram1, int pram2, int pram3)l
extern _native int GET_CRIME_OBJECTSET(int pram0)l
extern _native int UNK_0xD96DBABD(int pram0)l
extern _native void SET_ACTOR_HEADING(Actor Actor, float Heading, bool Unk1)l
extern _native int GET_ACTOR_FACTION(int pram0)l
extern _native void SET_MOVER_FROZEN(int pram0, int pram1)l
extern _native int IS_MOVER_FROZEN(int pram0)l
extern _native int GET_CRIME_COUNTER(int pram0)l
extern _native void TASK_OVERRIDE_CLEAR_MOVETYPE(int pram0)l
extern _native int CAN_ANYONE_OF_FACTION_SEE_OBJECT(int pram0, int pram1)l
extern _native int UNK_0xA2DA4D24(int pram0)l
extern _native void ITERATE_IN_VOLUME(int pram0, int pram1)l
extern _native int IS_FACTION_VALID(int pram0)l
extern _native int AI_GET_TASK_RETREAT_FLAG(int pram0)l
extern _native int GET_ACTOR_VEHICLE_STATE(int pram0, int pram1, int pram2)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_EASE_IN_OUT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UNK_0x3DEB0933(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_FAR_CLIP_PLANE(int pram0, int pram1)l
extern _native void RESET_CAMERASHOT_TARGETDOF(int pram0)l
extern _native void UNK_0x8BCB6B86(int pram0, int pram1)l
extern _native int GET_PERS_CHAR_DEATH_TIMESTAMP(int pram0)l
extern _native void UNK_0x19C3CF93(int pram0)l
extern _native void UNK_0x4C28B11E(int pram0, int pram1, int pram2)l
extern _native void INIT_CAMERA_FROM_GAME_CAMERA(int pram0)l
extern _native void SET_CAMERA_TARGET_POSITION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_CAMERA_FOV(int pram0, int pram1)l
extern _native int SQUAD_GOAL_ADD_GENERAL_TASK(int pram0, int pram1, int pram2, int pram3)l
extern _native void TASK_USE_LASSO(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void AI_SET_NAV_ACTOR_WIDTH(int pram0, int pram1)l
extern _native void MEMORY_CONSIDER_AS_ENEMY(int pram0, int pram1)l
extern _native void TASK_GO_TO_COORD(int pram0, int pram1, int pram2)l
extern _native void TASK_FOLLOW_OBJECT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void TASK_SHOOT_AT_COORD(int pram0, int pram1, int pram2)l
extern _native int UNK_0x5402321A()l
extern _native int CREATE_FIRE_IN_VOLUME(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void TASK_FOLLOW_ACTOR(int pram0, int pram1)l
extern _native int IS_ACTOR_MOUNTED(int pram0)l
extern _native void TASK_DISMOUNT(int pram0, int pram1)l
extern _native int FIND_INTERSECTION(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void TASK_SHOOT_AT_COORD_FROM_POSITION(int pram0, int pram1, int pram2, int pram3)l
extern _native int IS_ACTOR_RELOADING(int pram0)l
extern _native void TASK_SEEK_COVER_FROM_ACTOR(int pram0, int pram1)l
extern _native void TASK_DIVE(int pram0, int pram1)l
extern _native void AMBIENT_SET_SEARCH_CENTER_ACTOR(int pram0)l
extern _native int MEMORY_GET_IS_IDENTIFIED(int pram0, int pram1)l
extern _native int UNK_0x69DA275F(int pram0)l
extern _native int REVIVE_PERS_CHAR(int pram0, int pram1)l
extern _native int CREATE_PERS_CHAR_IN_LAYOUT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0x80FB8BDE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int GRINGO_UPDATE_STRUCT(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GET_BLIP_ICON(int pram0)l
extern _native void UNK_0xABD125F6(int pram0, int pram1)l
extern _native void UNK_0xFBA76D7E(int pram0, int pram1)l
extern _native void SET_BLIP_FLAG(int pram0, int pram1, int pram2)l
extern _native int UNK_0xE78A0469(int pram0)l
extern _native void UNK_0x02755628(int pram0, int pram1)l
extern _native void UNK_0x5EA2E02D(int pram0)l
extern _native int UNK_0xD76F1E9A(int pram0)l
extern _native void SET_BLIP_IMPAIRMENT_MASK(int pram0, int pram1)l
extern _native void TASK_DRAW_HOLSTER_WEAPON(int pram0, int pram1)l
extern _native void MEMORY_ATTACK_ON_SIGHT(int pram0, int pram1)l
extern _native void SET_ACTOR_FACTION(int pram0, int pram1)l
extern _native void UNK_0x0B5E1904(int pram0, int pram1)l
extern _native int ACTOR_RESET_ANIMS(int pram0, int pram1)l
extern _native void PLAY_SOUND_FRONTEND(const char* SoundName)l
extern _native void SET_ACTOR_CAN_BUMP(int pram0, int pram1)l
extern _native void UNK_0xC52B5F18(int pram0, int pram1)l
extern _native void UNK_0xEB7B0FAA(int pram0, int pram1)l
extern _native void PRINT_BIG_FORMAT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int UNK_0xCE210220(int pram0, int pram1, int pram2)l
extern _native int GET_OBJECT_HEADING(int pram0)l
extern _native int IS_ACTION_NODE_PLAYING(int pram0, int pram1)l
extern _native int ATTACH_SLOT_FROM_STRING(int pram0)l
extern _native int ATTACH_PROP_TO_ANIM(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ADD_AMBIENT_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(int pram0)l
extern _native void ADD_AMBIENT_SPAWN_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(int pram0)l
extern _native void UNK_0xC9365FBC(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_INDEFINITE(int pram0, int pram1, int pram2)l
extern _native void RESET_CAMERASHOT_TARGET(int pram0, int pram1)l
extern _native void TOGGLE_ACTOR_ACTION_SIGNAL_ON(int pram0, int pram1, int pram2)l
extern _native int IS_ACTOR_IN_HOGTIE(int pram0)l
extern _native void UNK_0x33CE49C9()l
extern _native void TOGGLE_ACTOR_ACTION_SIGNAL_OFF(int pram0)l
extern _native void DESTROY_POPULATION_SET(int pram0)l
extern _native void UNK_0x95D0FC79(int pram0)l
extern _native int IS_ACTOR_HORSE(int pram0)l
extern _native int SET_ACTOR_VISION_XRAY(int pram0, int pram1)l
extern _native void TASK_FLEE_ACTORSET(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void SET_BLIP_POS(int pram0, int pram1)l
extern _native int UNK_0x55DAC120(int pram0)l
extern _native void UNK_0xBE39208A(int pram0, int pram1, int pram2)l
extern _native void TASK_OVERRIDE_SET_MOVETYPE(int pram0, int pram1)l
extern _native void UNK_0xCA950EF0(int pram0)l
extern _native void TASK_GO_TO_COORD_NONSTOP(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x435A982F(int pram0, int pram1)l
extern _native int UNK_0x4DD06256(int pram0, int pram1, int pram2, int pram3)l
extern _native int SQUAD_GOAL_ADD_STAY_WITHIN_VOLUME(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void TASK_GO_NEAR_ACTOR(int pram0, int pram1, int pram2, int pram3)l
extern _native void TASK_SEARCH_FOR_OBJECT(int pram0, int pram1, int pram2, int pram3)l
extern _native int SQUAD_GOAL_LINK_MODIFIER_TO_OTHER_GOAL(int pram0, int pram1, int pram2)l
extern _native void TASK_GO_TO_COORD_AND_STAY(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x817AC6D6(int pram0, int pram1, int pram2)l
extern _native int SQUAD_GOAL_ADD_MEET_AT_POSITION(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int SET_LINKED_ANIM_TARGET(int pram0, int pram1)l
extern _native void TASK_ACTION_PERFORM(int pram0, int pram1)l
extern _native void AUDIO_STOP_PAIN(int pram0)l
extern _native void UNK_0x12D077CA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UNK_0x31A55281(int pram0)l
extern _native void UNK_0x651C1FC2(int pram0)l
extern _native void UI_SET_STYLE(int pram0, int pram1)l
extern _native int UNK_0xB7CE8FCC(int pram0, int pram1, int pram2)l
extern _native int UNK_0x430207A4(int pram0)l
extern _native int UNK_0x55842354(int pram0)l
extern _native int UNK_0x91C6AC0E(int pram0, int pram1, int pram2)l
extern _native int ADD_FORMATION_LOCATION(int pram0, int pram1)l
extern _native int IS_SLOT_VALID(int SlotID)l
extern _native void MEMORY_REPORT_POSITION(int pram0, int pram1, int pram2)l
extern _native int GET_LASSO_TARGET(int pram0)l
extern _native int UNK_0xEB40C2FC(int pram0)l
extern _native int UNK_0x69FA5315(int pram0)l
extern _native int MEMORY_GET_POSITION_LAST_KNOWN_TIME(int pram0, int pram1)l
extern _native void AI_CLEAR_NAV_MATERIAL_USAGE(int pram0)l
extern _native int UNK_0x7A207FFE(int pram0)l
extern _native void AI_CLEAR_FIRE_DELAY(int pram0)l
extern _native void AI_CLEAR_FIRE_DELAY_RANDOMNESS(int pram0)l
extern _native void AI_CLEAR_BURST_DURATION(int pram0)l
extern _native void AI_CLEAR_BURST_DURATION_RANDOMNESS(int pram0)l
extern _native void AI_CLEAR_SHOTS_PER_BURST(int pram0)l
extern _native void COMBAT_CLASS_AI_SET_RANGE_BETWEEN_BURSTS_DELAY(int pram0, int pram1, int pram2)l
extern _native Object UNK_0x184BD1BC(Object pram0)l
extern _native int UNK_0xE2ED95CC(int pram0)l
extern _native int UNK_0x2ECF04F3(int pram0, int pram1)l
extern _native void UNK_0x52B2F3F0(int pram0)l
extern _native int IS_ACTOR_PERFORMING_LINKED_ANIMATION(int pram0)l
extern _native int UNK_0xBEC2871A(int pram0)l
extern _native int UNK_0xEF4F4F20(int pram0)l
extern _native int GET_ACTOR_VISION_XRAY(int pram0)l
extern _native int TIMESTEP()l
extern _native int IS_PLAYER_USING_COVER(int pram0)l
extern _native int UNK_0x5B792331(int pram0, int pram1)l
extern _native int UNK_0xF6BF4242(int pram0)l
extern _native int IS_ACTOR_DRUNK(int pram0)l
extern _native int UNK_0x30C4CA99(int pram0)l
extern _native int GET_LASSO_USER(int pram0)l
extern _native void UNK_0xA6D794FE(int pram0, int pram1)l
extern _native void UNK_0xC09B114B(int pram0, int pram1)l
extern _native void AI_BEHAVIOR_SET_ALLOW(int pram0, int pram1, int pram2)l
extern _native void SET_TOUGH_ACTOR(int pram0, int pram1)l
extern _native void AI_SET_RANGE_ACCURACY_MODIFIER(int pram0, int pram1, int pram2)l
extern _native int SET_ACTOR_VISION_MAX_RANGE(int pram0, int pram1, int pram2)l
extern _native int SET_ACTOR_VISION_FIELD_OF_VIEW(int pram0, int pram1)l
extern _native void MEMORY_PREFER_MELEE(int pram0, int pram1)l
extern _native void AI_SET_SHOTS_PER_BURST(int pram0, int pram1)l
extern _native void AI_SET_BURST_DURATION(int pram0, int pram1)l
extern _native void AI_SET_BURST_DURATION_RANDOMNESS(int pram0, int pram1)l
extern _native void AI_SET_FIRE_DELAY(int pram0, int pram1)l
extern _native void AI_SET_FIRE_DELAY_RANDOMNESS(int pram0, int pram1)l
extern _native void ACTOR_ENABLE_VARIABLE_MESH(int pram0, int pram1, int pram2)l
extern _native void COMBAT_CLASS_AI_CLEAR_ALL_ATTRIBS(int pram0)l
extern _native void COMBAT_CLASS_AI_SET_FIGHT_ATTACK_DISTANCE(int pram0, int pram1, int pram2)l
extern _native void COMBAT_CLASS_AI_SET_FIGHT_DESIRED_DISTANCE(int pram0, int pram1, int pram2)l
extern _native void COMBAT_CLASS_AI_SET_FIGHT_TIME_BETWEEN_ATTACKS(int pram0, int pram1)l
extern _native void COMBAT_CLASS_AI_SET_RANGE_ACCURACY(int pram0, int pram1)l
extern _native void TOUGH_ARMOUR_SET_TUNING_REGENERATION_RATE(int pram0, int pram1)l
extern _native void TOUGH_ARMOUR_SET_TUNING_PAD_ARMOUR(int pram0, int pram1)l
extern _native void AI_PERCEPTION_SET_VISUAL_ID_DISTANCE(int pram0, int pram1)l
extern _native void AI_PERCEPTION_SET_VISUAL_ID_TIME(int pram0, int pram1)l
extern _native void TOUGH_ARMOUR_SET_TUNING_HIT_DEDUCTION(int pram0, int pram1, int pram2)l
extern _native int IS_ACTOR_PLAYER(int pram0)l
extern _native void AI_PREDICATE_OVERRIDE_CLEAR_ALL(int pram0)l
extern _native void AI_PREDICATE_OVERRIDE_SET_BOOL(int pram0, int pram1, int pram2)l
extern _native void SQUAD_SET_NOT_ELIMINATED_IMPAIRMENT_MASK(int pram0, int pram1)l
extern _native void SQUAD_SET_FACTION(int pram0, int pram1)l
extern _native int NET_IS_OBJECT_LOCAL(int pram0)l
extern _native int UNK_0x2B8C3258(int pram0)l
extern _native int GET_LOCAL_SLOT()l
extern _native int UNK_0xA2866F3B(int pram0)l
extern _native int UNK_0xADB08F12(int pram0)l
extern _native int UNK_0xB4D1D8A3(int pram0, int pram1)l
extern _native int GET_CURVE_NAME(int pram0)l
extern _native void UNK_0x7B07D449()l
extern _native int UNK_0x0B40BBE3(int pram0, int pram1, int pram2)l
extern _native int GET_SLOT_ACTOR(int pram0)l
extern _native int UNK_0x579C2014(int pram0)l
extern _native void UNK_0xA6403262(int pram0, int pram1)l
extern _native void UI_ENTER(const char* uiLayer)l
extern _native void TASK_SHOOT_FROM_POSITION(int pram0, int pram1, int pram2)l
extern _native void UNK_0xEF270DC9()l
extern _native void UNK_0xD1628C57()l
extern _native void UNK_0xF7696B8B(int pram0, int pram1)l
extern _native int UNK_0xE094DB31(int pram0, int pram1)l
extern _native void UNK_0xBB77E597(int pram0, int pram1)l
extern _native void UNK_0xF349D0B6(int pram0, int pram1)l
extern _native void CLOSE_DOOR_FAST(int pram0)l
extern _native void ACTOR_DISABLE_WEAPON_RENDER(int pram0, int pram1, int pram2)l
extern _native void SET_PERS_CHAR_ENABLED(int pram0, int pram1)l
extern _native void SET_DAY(int pram0)l
extern _native void TELEPORT_ACTOR_WITH_HEADING(Actor Actor, vector3 Position, float Heading, bool Unk1, bool _Unk1, bool __Unk1)l
extern _native int SET_OBJECT_ORIENTATION(int pram0, int pram1, int pram2, int pram3)l
extern _native void OPEN_DOOR_FAST(int pram0, int pram1)l
extern _native int UNK_0x76FBF412()l
extern _native void UNK_0x6ADAAD87(int pram0, int pram1, int pram2)l
extern _native void UNK_0xB3E331AC()l
extern _native void UNK_0xB09D5B43()l
extern _native void UNK_0x9028B082()l
extern _native void CLEAR_DECALS()l
extern _native void UNK_0x2CB5D7AF()l
extern _native int IS_ACTORSET_VALID(int pram0)l
extern _native int GET_ACTORSET_SIZE(int pram0)l
extern _native int UNK_0xC5202810(int pram0, int pram1)l
extern _native int GET_SLOT_POSITION(int pram0, int pram1)l
extern _native int VDIST2(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0xEE4E2461(int pram0)l
extern _native void UNK_0xAA24E0CC(int pram0)l
extern _native void UNK_0xDE9AA6E5(int pram0)l
extern _native int UNK_0x54F8EAA4(int pram0)l
extern _native void UNK_0x0D8BA78E(int pram0, int pram1)l
extern _native int UNK_0x0B5431C9(int pram0)l
extern _native int IS_ACTOR_IN_ACTORSET(int pram0, int pram1)l
extern _native int ADD_ACTORSET_MEMBER(int pram0, int pram1)l
extern _native int IS_ACTOR_RIDEABLE(int pram0)l
extern _native int NEW_SCRIPTED_CONVERSATION()l
extern _native void ADD_LINE_TO_CONVERSATION(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void ADD_NEW_FRONTEND_CONVERSATION_SPEAKER(int pram0, int pram1)l
extern _native void START_SCRIPT_CONVERSATION(int pram0, int pram1)l
extern _native int UNK_0x5E985228(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void PRINT_BIG(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xE2163ECC(int pram0, int pram1)l
extern _native int UNK_0x4957E482(int pram0, int pram1)l
extern _native int UNK_0xB13DD691(int pram0, int pram1, int pram2)l
extern _native int UNK_0x009DFC82(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9253CC79(int pram0, int pram1)l
extern _native void UNK_0xC73DAD2B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void IS_HORSES_RELATIVE(int pram0, int pram1)l
extern _native void UNK_0x1082715D()l
extern _native int UNK_0x6226328F()l
extern _native void UNK_0x59F98CA9(int pram0)l
extern _native void SET_DEBUG_DRAW(int pram0)l
extern _native int UNK_0x943BE053(int pram0)l
extern _native int UNK_0x2DB3AC0F(int pram0, int pram1)l
extern _native void STREAMING_LOAD_BOUNDS(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0x2CCEA76C(int pram0)l
extern _native void UNK_0xE9C41DFE(int pram0)l
extern _native void RESET_FACTIONS()l
extern _native void HUD_COUNTER_DISPLAY(int pram0)l
extern _native void HUD_TIMER_DISPLAY(int pram0)l
extern _native void SET_ACTOR_MIN_SPEED(int pram0, int pram1)l
extern _native void SET_ACTOR_RIDEABLE(Actor Actor, bool Rideable)l
extern _native void TASK_FOLLOW_PATH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void TASK_SEQUENCE_PERFORM_REPEATEDLY(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_ACTOR_SET_DOMESTICATION(Actor Actor, bool Domestication)l
extern _native void ANIMAL_TUNING_SET_ATTRIB_BOOL(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9A4CD54B(int pram0)l
extern _native void AUDIO_MUSIC_SET_MOOD(const char* Mood, int pram1, int pram2, int pram3)l
extern _native int IS_WEAPON_DRAWN(int pram0)l
extern _native int UNK_0x09950C1B(int pram0, int pram1)l
extern _native void OPEN_DOOR_DIRECTION(int pram0, int pram1)l
extern _native int IS_CAMERA_ACTIVE_ON_CHANNEL(int pram0, int pram1)l
extern _native void TASK_FACE_COORD(int pram0, int pram1, int pram2)l
extern _native int IS_SCRIPTED_SPEECH_PLAYING(int pram0)l
extern _native int GATEWAY_GET_ACTOR(int pram0)l
extern _native void SIMULATE_PLAYER_INPUT_GAIT(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xB89CC342(int pram0, int pram1, int pram2)l
extern _native int UNK_0x4251BF6C(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int IS_AI_ACTOR_IN_COMBAT(int pram0)l
extern _native int UNK_0x07B7AA6B(int pram0)l
extern _native int IS_WORLD_SECTOR_LOADED(int pram0)l
extern _native int UNK_0xA5F229C9(int pram0, int pram1, int pram2)l
extern _native int GET_DOOR_FROM_OBJECT(int pram0)l
extern _native int UNK_0xB6709FF4(int pram0, int pram1, int pram2)l
extern _native int UNK_0x5831679F()l
extern _native void STREAMING_EVICT_ALL()l
extern _native void UNK_0xF1607937(int pram0, int pram1)l
extern _native void SET_ACTOR_MAX_HEALTH(int pram0, int pram1)l
extern _native void SET_ALLOW_RIDE_BY_PLAYER(Actor Actor, bool Ride)l
extern _native void UNK_0x135EA21D(int pram0)l
extern _native void SET_NPC_TO_ACTOR_DAMAGE_SCALE_FACTOR(int pram0, int pram1)l
extern _native void SET_PLAYER_CAUSE_WEAPON_REACTION_COMBAT(int pram0, int pram1)l
extern _native void DEACTIVATE_ACTORS_FOR_PERS_CHARS_IN_VOLUME(int pram0)l
extern _native void TASK_GO_TO_OBJECT(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x76876FEA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void SET_CAMERA_FOCUS_PROMPT_ENABLED(int pram0, int pram1)l
extern _native void TASK_OVERRIDE_SET_MOVESPEED_ABSOLUTE(int pram0, int pram1)l
extern _native void UNK_0x7EDD316C(int pram0)l
extern _native int GET_ACTORS_HORSE(int pram0)l
extern _native void ADD_CAMERATRANSITION_EVENT_GAMECAMERARESET(int pram0, int pram1, int pram2, int pram3)l
extern _native void PLAY_SOUND_FROM_POSITION(const char* SoundName, vector3 Position)l
extern _native void AUDIO_PLAY_VOCAL_EFFECT(int pram0, int pram1, int pram2)l
extern _native int PLAY_SOUND_FROM_ACTOR(int pram0, int pram1, int pram2)l
extern _native void OPEN_DOOR_DIRECTION_FAST(int pram0, int pram1)l
extern _native int GET_OBJECT_AXIS(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9BCC06E2(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12, int pram13, int pram14)l
extern _native int UNK_0x82A73B3D(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void TASK_ANIMAL_CIRCLE_AGGRESSIVELY(int pram0, int pram1)l
extern _native int UNK_0x951B8DF7(int pram0, int pram1)l
extern _native int IS_PLAYER_TARGETTING_ACTOR(int pram0, int pram1, int pram2)l
extern _native void TASK_FLEE_COORD(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x98790639(int pram0)l
extern _native void TASK_CROUCH(int pram0, int pram1)l
extern _native int UNK_0xEDA897FA(int pram0)l
extern _native void MEMORY_CONSIDER_ACCORDING_TO_FACTION(int pram0, int pram1)l
extern _native int DESTROY_ACTORSET(int pram0)l
extern _native void UNK_0x1BED8493(int pram0, int pram1, int pram2)l
extern _native void SET_ACTOR_WEAPON_REACTION_ACTOR_TYPE(int pram0, int pram1)l
extern _native void UNK_0x4EEC6628(int pram0, int pram1)l
extern _native void UNK_0x3A2D7759(int pram0, int pram1)l
extern _native void CLEAR_LAST_HIT(int pram0)l
extern _native int UNK_0x08308EBA(int pram0)l
extern _native void CLEAR_LAST_ATTACK(int pram0)l
extern _native void SET_ALLOW_EXECUTE(int pram0, int pram1)l
extern _native void SET_ALLOW_COLD_WEATHER_BREATH(int pram0, int pram1)l
extern _native void ANIMAL_TUNING_SET_ATTRIB_FLOAT(int pram0, int pram1, int pram2)l
extern _native void UNK_0x900165CE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0x63925367(int pram0, int pram1)l
extern _native void SET_CRIPPLE_ENABLE(int pram0, int pram1)l
extern _native int GET_OBJECT_NAMED_BONE_POSITION(int pram0, int pram1, int pram2)l
extern _native void TASK_GO_TO_COORD_PRECISELY(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void SET_ACTOR_DRUNK(int pram0, int pram1)l
extern _native int UNK_0xA36ED4A6(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void MAKE_NEXT_RAND_ACTORENUMS_UNIQUE(int pram0)l
extern _native void AI_SET_NAV_ACTOR_AVOIDANCE_MODE(int pram0, int pram1)l
extern _native int UNK_0x4634B6BE(int pram0, int pram1, int pram2)l
extern _native void STOP_SOUND(int pram0)l
extern _native void UNK_0x44986367(int pram0, int pram1)l
extern _native void TASK_TAUNT_ACTOR_IN_PLACE(int pram0, int pram1, int pram2)l
extern _native int UNK_0x50AE988A(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x90AD2C2D(int pram0)l
extern _native void TASK_HIDE_AT_COVER(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int REMOVE_ACTORSET_MEMBER(int pram0, int pram1)l
extern _native void UNK_0x6118212B(int pram0, int pram1, int pram2)l
extern _native void UNK_0xF9C5DC76(int pram0, int pram1)l
extern _native bool IS_BUTTON_DOWN(Controller Controller, eButton Button, int Unk1, int Unk0)l
extern _native void FEED_CODE_WARP_DIST(int pram0)l
extern _native void UNK_0xD4FECCBC(int pram0)l
extern _native void CLEAR_ACTORS_HORSE(int pram0)l
extern _native void UNK_0x96AC812B(int pram0)l
extern _native int IS_ACTOR_MULE(int pram0)l
extern _native void SET_ACTORS_HORSE(int pram0, int pram1)l
extern _native void UNK_0x327E4426(int pram0, int pram1)l
extern _native void UNK_0x57055A7D(int pram0, int pram1)l
extern _native void UNK_0x5CC16A49(int pram0, int pram1)l
extern _native void UNK_0x6400E005(int pram0, int pram1)l
extern _native int FIND_TRAFFIC_PATH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void GET_CURVE_POINT(int pram0, int pram1, int pram2, int pram3)l
extern _native int POW(int pram0, int pram1)l
extern _native int UNK_0x39DA0B3A(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xF48F8F09(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int UNK_0xAE168124()l
extern _native void SET_ACTOR_MOVE_CONFLICT_ALLOWED_TO_RUN_OVER_SMALL_ANIMALS(int pram0, int pram1)l
extern _native void SET_ACTOR_MOVE_CONFLICT_HIGH_PRIORITY(int pram0, int pram1)l
extern _native void UNK_0x9F1F8669(int pram0)l
extern _native void FORCE_VEHICLE_CINEMATIC_CAMERA(int pram0)l
extern _native void UNK_0x2692B771(int pram0)l
extern _native int UNK_0x71A3F193(int pram0)l
extern _native int UNK_0xFB252BA9(int pram0)l
extern _native void AI_SET_NAV_ACTOR_AVOIDANCE_ALLOW_TURNS(int pram0, int pram1)l
extern _native int UNK_0x49D2C1DA(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xC6AF3662(int pram0, int pram1)l
extern _native void UNK_0x4F8FAF8F(int pram0, int pram1)l
extern _native void UNK_0x04D89A35(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GET_CURVE_TYPE(int pram0)l
extern _native int UNK_0xFAD7A113(int pram0)l
extern _native int SQUAD_GOAL_ADD_FOLLOW_TRAFFIC_CURVE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void SQUAD_FOLLOW_TRAFFIC_CURVE_SET_BEHAVIOR_FLAG(int pram0, int pram1, int pram2, int pram3)l
extern _native void SQUAD_FOLLOW_TRAFFIC_CURVE_SET_TASK_PRIORITY(int pram0, int pram1, int pram2)l
extern _native int UNK_0xA4BC2A1B(int pram0, int pram1, int pram2)l
extern _native int SQUAD_FOLLOW_TRAFFIC_CURVE_IS_CURVE_ALREADY_IN_LIST(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SQUAD_FOLLOW_TRAFFIC_CURVE_ENQUEUE_CURVE(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x8C221B4D(int pram0)l
extern _native int AI_GET_IS_RETREATING(int pram0)l
extern _native void PAUSE_GAME(int pram0)l
extern _native void UNPAUSE_GAME()l
extern _native void REMOVE_OBJECT_ATTACHMENT(int pram0)l
extern _native void DEREFERENCE_OBJECT(int pram0)l
extern _native int DISBAND_ACTORSET(int pram0)l
extern _native int UNK_0x0F701FF7(int pram0, int pram1, int pram2, int pram3)l
extern _native int IS_GRINGO_READY(int pram0)l
extern _native void UNK_0xF635B9EA(int pram0)l
extern _native void CLEAR_ACTOR_MIN_SPEED(int pram0)l
extern _native void AI_SET_NAV_PATHFINDING_ENABLED(int pram0, int pram1)l
extern _native int IS_CUTSCENEOBJECT_PAUSED(int pram0)l
extern _native void ACTOR_DISMOUNT_NOW(int pram0)l
extern _native int UNK_0x3C45D66A(int pram0, int pram1, int pram2)l
extern _native void UNK_0x67FC68DB(int pram0)l
extern _native void DELETE_ACCESSORY(int pram0, int pram1)l
extern _native void UNK_0x2E84E682(int pram0, int pram1)l
extern _native void AI_GOAL_AIM_AT_OBJECT(int pram0, int pram1, int pram2)l
extern _native void OPEN_DOOR(int pram0, int pram1, int pram2)l
extern _native int CLEAR_LINKED_ANIM_TARGET(int pram0)l
extern _native void SET_CRIPPLE_FLAG(int pram0, int pram1)l
extern _native int GET_MOST_RECENT_MOUNT(int pram0)l
extern _native int GET_Y(int pram0)l
extern _native int UNK_0xD14515A3(int pram0, int pram1)l
extern _native void TASK_VEHICLE_ENTER(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_VEHICLE_ALLOWED_TO_DRIVE(Actor Vehicle, bool Allowed)l
extern _native bool SET_ACTOR_IN_VEHICLE(Actor Source, Actor Destination, int SeatID)l
extern _native void SET_ACTOR_AUTO_TRANSITION_TO_DRIVER_SEAT(int pram0, int pram1)l
extern _native void REFERENCE_OBJECT(int pram0)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_DECORATOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int ATTACH_CAMERASHOT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void SET_CAMERASHOT_TARGET_OBJECT(int pram0, int pram1, int pram2)l
extern _native void SET_CAMERASHOT_TARGET_OBJECT_OFFSETS(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void SET_CAMERASHOT_TARGET_OBJECT_ROLL(int pram0, int pram1)l
extern _native int AI_IS_AGGROING(int pram0, int pram1)l
extern _native void DETACH_LASSO(int pram0)l
extern _native int UNK_0xAF2597E8(int pram0)l
extern _native int UNK_0x16EB367C(int pram0)l
extern _native int FIND_WATER_INTERSECTION(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void ADD_ACTOR_STAY_OUTSIDE_OF_VOLUME(int pram0, int pram1)l
extern _native int UNK_0x9265B24B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void TASK_FOLLOW_AND_ATTACK_OBJECT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void TASK_SHOOT_ENEMIES_FROM_ANY_COVER(int pram0, int pram1)l
extern _native int GET_ACTOR_VISION_MAX_RANGE(int pram0)l
extern _native int MEMORY_GET_WAS_VISIBLE_WITHIN_TIME(int pram0, int pram1, int pram2)l
extern _native int CREATE_OBSTACLE_IN_LAYOUT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int COMBAT_CLASS_AI_GET_RANGE_ACCURACY(int pram0)l
extern _native void ADD_ACTOR_STAY_WITHIN_VOLUME(int pram0, int pram1)l
extern _native void SET_ACTOR_VOLUME_PARAMETERS(int pram0, int pram1, int pram2)l
extern _native void SET_CAMERA_ASPECT_RATIO(int pram0, int pram1)l
extern _native void SET_CAMERA_NEAR_CLIP_PLANE(int pram0, int pram1)l
extern _native void SET_CAMERA_FAR_CLIP_PLANE(int pram0, int pram1)l
extern _native void SET_CAMERA_COLLISION_PARAMETERS(int pram0, int pram1, int pram2)l
extern _native void SET_CAMERA_COLLISION_ENABLED(int pram0, int pram1)l
extern _native void RESET_CAMERA_TARGET(int pram0, int pram1)l
extern _native void RESET_CAMERA_TARGETDOF(int pram0)l
extern _native int GRINGO_DEACTIVATE(int pram0)l
extern _native int MEMORY_GET_MUST_IDENTIFY(int pram0, int pram1)l
extern _native int IS_CAMERA_FOCUS_ENABLED(int pram0)l
extern _native void SET_CAMERA_FOCUS_ENABLED(int pram0, int pram1)l
extern _native int IS_CAMERA_FOCUS_ACTIVE(int pram0)l
extern _native void AI_PREDICATE_OVERRIDE_CLEAR(int pram0, int pram1)l
extern _native int IS_SCRIPT_USE_CONTEXT_PRESSED(int pram0)l
extern _native int UNK_0x211DE185(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void UNK_0x6077F3AE(int pram0, int pram1)l
extern _native int UNK_0x52261CE0(int pram0)l
extern _native void SET_ACTOR_STAY_OUTSIDE_OF_VOLUME(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_CAMERA_FOCUS_PLAYER_INVULNERABLE(int pram0, int pram1)l
extern _native void SET_CAMERA_FOCUS_PLAYER_INPUT_DISABLED(int pram0, int pram1)l
extern _native int SET_PROP_AI_OBSTACLE_ENABLED(int pram0, int pram1)l
extern _native void UNK_0x547166A7(int pram0)l
extern _native void FIRE_RELEASE_HANDLE(int pram0, int pram1)l
extern _native void UNK_0x983ED842(int pram0)l
extern _native void UNK_0x902781BF(int pram0, int pram1)l
extern _native int UNK_0x965A4652(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int CREATE_CORPSE_IN_LAYOUT_RANDOM(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void CREATE_DECAL(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void UNK_0x0E41A6AC(int pram0)l
extern _native int FIRE_CREATE_HANDLE()l
extern _native int UNK_0xB65ADFAC(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x3D5D3B26(int pram0, int pram1)l
extern _native int UNK_0xF1F8AFCA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int IS_SCRIPTED_CONVERSATION_ONGOING()l
extern _native int GET_JOURNAL_ENTRY(int pram0)l
extern _native void CLEAR_JOURNAL_ENTRY_DETAIL_LIST(int pram0, int pram1)l
extern _native void ADD_NEW_CONVERSATION_SPEAKER(int pram0, int pram1, int pram2)l
extern _native int SQUAD_GOAL_ADD_BATTLE_ALLIES(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x74CA8E22(int pram0)l
extern _native void UNK_0x80317230(int pram0, int pram1, int pram2)l
extern _native int UNK_0x35C8FD4A(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x211DD9D2(int pram0)l
extern _native int UNK_0x2CF0010F(int pram0)l
extern _native void SET_ACTOR_PROOF(int pram0, int pram1)l
extern _native void UNK_0x76A72D9A(int pram0, int pram1)l
extern _native int CREATE_COVER_LOCATION_IN_LAYOUT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void AI_SPEECH_SET_ALLOW_CONTEXT_FOR_ACTOR(int pram0, int pram1, int pram2)l
extern _native int UNK_0xD4FBCCE0(int pram0)l
extern _native int SC_CHALLENGE_LAUNCH(int pram0)l
extern _native void TASK_SHOOT_ENEMIES_FROM_COVER(int pram0, int pram1, int pram2, int pram3)l
extern _native void TASK_GO_NEAR_OBJECT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ATTACH_PLAYER_TO_COVER(int pram0, int pram1, int pram2)l
extern _native void ACTOR_POP_NEXT_GAIT(int pram0, int pram1, int pram2)l
extern _native void UNK_0x6C194C1F(int pram0)l
extern _native void HUD_TIMER_COUNTDOWN(int pram0)l
extern _native void SET_ACTOR_FACE_STYLE(int pram0, int pram1)l
extern _native void TASK_VEHICLE_ENTER_SPECIFIC_LOCATION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xB6E791F6(int pram0, int pram1)l
extern _native int GET_VEHICLE_BUMP_COUNT(int pram0)l
extern _native void UNK_0x0E9BA223(int pram0)l
extern _native void UI_SET_TEXT(char* entry, char* text)l
extern _native void UNK_0xE5D53722(int pram0, int pram1)l
extern _native void SET_TRANSITION_COLLISION_PARAMS(int pram0, int pram1, int pram2)l
extern _native void UNK_0xF76F2BB3(int pram0, int pram1, int pram2, int pram3)l
extern _native void ADD_CAMERASHOT_COLLISION_EXCLUSION(int pram0, int pram1, int pram2)l
extern _native void AI_DISABLE_PERCEPTION(int pram0)l
extern _native void AI_ENABLE_PERCEPTION(int pram0)l
extern _native void TASK_SHOOT_ENEMIES_FROM_POSITION(int pram0, int pram1, int pram2, int pram3)l
extern _native int SET_ACTOR_ANIM_CURRENT_TIME(int pram0, int pram1)l
extern _native void SET_ALLOW_DEADEYE_LOCKS(int pram0, int pram1)l
extern _native void UNK_0xAC8D3A0C(int pram0, int pram1)l
extern _native void SET_DEADEYE_LOCKS_ON_HEAD_ONLY(int pram0, int pram1)l
extern _native32(0x358F874F) bool _IS_KEY_DOWN(int keyCode)l
extern _native int UNK_0x5E339E16(int pram0)l
extern _native int ATTACH_OBJECTS_CONTINUOUS(int pram0, int pram1, int pram2)l
extern _native void TASK_OVERRIDE_CLEAR_POSTURE(int pram0)l
extern _native int UNK_0x0208A8E0(int pram0, int pram1)l
extern _native void UNK_0x77402033(int pram0)l
extern _native void AI_RESET_FIRING_FSM(int pram0)l
extern _native void STOP_PED_SPEAKING(int pram0, int pram1)l
extern _native int UNK_0x77964B0C(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native bool IS_ACTOR_DRAFTED(int actor)l
extern _native void SET_ACTOR_POSTURE(int pram0, int pram1)l
extern _native bool IS_ACTOR_LOCAL_PLAYER(int actor)l
extern _native int UNK_0x8A0D25F2(int pram0, int pram1)l
extern _native void AI_GOAL_LOOK_AT_COORD(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int LEASH_CONSTRAIN(int pram0)l
extern _native int LEASH_RESTART(int pram0)l
extern _native int UNK_0x7F190CA3(int pram0, int pram1)l
extern _native int UNK_0x14BEC6F5(int pram0, int pram1)l
extern _native int LEASH_BREAK(int pram0, int pram1)l
extern _native void TASK_TAUNT_ACTOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0xAFC96669(int pram0)l
extern _native void NAV_QUERY_RECEIVE_CAN_PATH_TO_POINT(int pram0, int pram1)l
extern _native int UNK_0x734CC17B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int LEASH_IS_BROKEN(int pram0)l
extern _native int LEASH_RELEASE_CONSTRAINT(int pram0)l
extern _native void SET_ACTOR_HANGING_FROM_NOOSE(int pram0, int pram1)l
extern _native void REMOVE_ACTOR_STAY_WITHIN_VOLUME(int pram0, int pram1)l
extern _native int UNK_0x5A72DD49(int pram0, int pram1)l
extern _native int LEASH_ATTACH_TO_WORLD(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void UNK_0x65DAA654(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x4B67B8BB(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void UNK_0x1CD960B8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UI_REFRESH(const char* pram0)l
extern _native void UNK_0x6B5DF46D(int pram0, int pram1)l
extern _native int GRINGO_GET_TARGET(int pram0)l
extern _native int UNK_0x1FCC8FEF(int pram0)l
extern _native int UNK_0x48588CCB(int pram0, int pram1, int pram2, int pram3)l
extern _native void SQUAD_FLOCK_ADD_EXTERNAL_ALERT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void SQUAD_FLOCK_ADD_EXTERNAL_REPULSION(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void SQUAD_FLOCK_PLAYER_PROXIMITY_BOOST_SET_ENABLED(int pram0, int pram1, int pram2)l
extern _native int UNK_0x66A8AF91(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void UNK_0x731F2C21(int pram0)l
extern _native void UNK_0xA90A13A5(int pram0, int pram1)l
extern _native void UNK_0x7A759A53(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_ACTOR_PASSED_OUT(int pram0, int pram1)l
extern _native void FIRE_PROJECTILE(Actor Actor, const char* WeapGroup, float pram2, vector3* Origin, vector3* Target)l
extern _native int ANIMAL_SPECIES_REL_GET_CAN_ATTACK(int pram0, int pram1)l
extern _native int GET_ACTOR_MAX_SPEED_ABSOLUTE(int pram0)l
extern _native void AI_ACTOR_FORCE_SPEED(int pram0, int pram1)l
extern _native void SET_ACTOR_MAX_SPEED_ABSOLUTE(int pram0, int pram1)l
extern _native int IS_ACTOR_ON_GROUND(int actor)l
extern _native bool GET_ACTOR_MOST_RECENT_VEHICLE(int pram0)l
extern _native int GET_ACTOR_HOGTIE_STATE(int actor)l
extern _native int UNK_0xF7400A47(int pram0, int pram1)l
extern _native void UNK_0xBFC8EF7C(int pram0, int pram1)l
extern _native int UNK_0xD02757C1(int pram0, int pram1)l
extern _native void UNK_0x0871084C(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int UNK_0xF0354E46(int pram0)l
extern _native void CREATE_DIRECTION_DECAL(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void ACTIVATE_PHYSINST(int pram0)l
extern _native void AI_GLOBAL_SET_PERMANENT_DANGER(int pram0, int pram1)l
extern _native void REMOVE_ACTOR_STAY_OUTSIDE_OF_VOLUME(int pram0, int pram1)l
extern _native void TASK_SURROUND_ACTOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void AI_GOAL_AIM_CLEAR(int pram0)l
extern _native void MEMORY_CLEAR_WEAPON_DRAW_PREFERENCE(int pram0)l
extern _native void AI_SET_WEAPON_MIN_RANGE(int pram0, int pram1)l
extern _native void AI_GOAL_SHOOT_CLEAR(int pram0)l
extern _native void ACTOR_FORCE_WEAPON_RENDER(int pram0, int pram1, int pram2)l
extern _native void AI_SET_WEAPON_MAX_RANGE(int pram0, int pram1)l
extern _native int HUD_TIMER_GET()l
extern _native int UNK_0xAAC96EFF(int pram0, int pram1)l
extern _native void TASK_BIRD_SOAR_AT_COORD(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_ACTOR_UNKILLABLE(int pram0, int pram1)l
extern _native void UNK_0xF1A53C41(int pram0, int pram1, int pram2, int pram3)l
extern _native int LEASH_ATTACH_TO_OBJECT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void UNK_0x88943B5B(int pram0, int pram1)l
extern _native int UNK_0x941FC468(int pram0)l
extern _native void GET_GRINGO_ACTIVATION_SPHERE(int pram0, int pram1, int pram2)l
extern _native int UNK_0x8EB0B2AD()l
extern _native void SET_CAMERA_TARGET_OBJECT(int pram0, int pram1, int pram2)l
extern _native int UNK_0xBFD6AE3D(int pram0)l
extern _native int GRINGO_QUERY_PROP(int pram0, int pram1)l
extern _native int ATTACH_OBJECTS_USING_LOCATOR(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GET_PROP_VELOCITY(int pram0, int pram1)l
extern _native int UNK_0x945F518F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void UNK_0x338F85D9(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0xFF642652(int pram0)l
extern _native int UNK_0xE27EBCBD(int pram0)l
extern _native int IS_ACTOR_PLAYING_NODE_IN_TREE(int pram0, int pram1)l
extern _native int UNK_0x80B8A1BE(int pram0, int pram1, int pram2)l
extern _native int UNK_0xECC40138(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x43E2808B(int pram0)l
extern _native void UNK_0x527CB774(int pram0, int pram1)l
extern _native int UNK_0x0733E811(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int IS_AREA_OBSTRUCTED(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UNK_0x561C9A6D(int pram0)l
extern _native void UNK_0x528C7F3D(int pram0)l
extern _native void UNK_0xE9E8C31A(int pram0)l
extern _native void SET_ACTOR_ACTION_SIGNAL(int pram0, int pram1, int pram2)l
extern _native void UNK_0x5685A440(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void UNK_0x761BA4BD(int pram0, int pram1)l
extern _native int UNK_0x92FE8D74(int pram0, int pram1)l
extern _native int UNK_0x08FD1D81(int pram0)l
extern _native void UNK_0x3627F773(int pram0, int pram1)l
extern _native void AI_SET_NAV_FAILSAFE_MOVEMENT_ENABLED(int pram0, int pram1)l
extern _native void MEMORY_CLEAR_RIDING_PREFERENCE(int pram0)l
extern _native void SET_ACTOR_IS_COMPANION(int pram0, int pram1)l
extern _native void SET_ACTOR_IS_AMBIENT(int pram0, int pram1)l
extern _native void UNK_0xC28A5950(int pram0, int pram1)l
extern _native void SET_ALLOW_JACK(int pram0, int pram1)l
extern _native void MEMORY_SHOULD_ALWAYS_PATHFIND_IN_FORMATION(int pram0, int pram1)l
extern _native void ACTOR_DRAW_WEAPON(int pram0, int pram1, int pram2)l
extern _native int UNK_0x8F8EDCCF(int pram0, int pram1, int pram2)l
extern _native int UNK_0x6ADC74CE(int pram0, int pram1)l
extern _native void UNK_0x8DFF31DF(int pram0, int pram1)l
extern _native int UNK_0x620178B3(int pram0)l
extern _native void UNK_0xB3E44649(int pram0)l
extern _native void TOGGLE_COOP_JOURNAL_UI(int pram0)l
extern _native void UNK_0xE822010A(int pram0, int pram1)l
extern _native int UNK_0x55C5BB93(int pram0)l
extern _native int UNK_0xBFCF32D9(int pram0)l
extern _native int UNK_0xE8FFE727(int pram0, int pram1, int pram2)l
extern _native void UNK_0x57D9950B(int pram0)l
extern _native void UNK_0xF4D0807E(int pram0, int pram1)l
extern _native void HUD_SET_FADE_COLOR(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x2148AC15(int pram0, int pram1)l
extern _native void STOP_ALL_FIRES()l
extern _native void UNK_0xA393AC4E(int pram0)l
extern _native int UNK_0xFC52BD15(int pram0)l
extern _native void MISSION_AUDIO_BANK_NO_LONGER_NEEDED()l
extern _native void UNK_0x87E40FB8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int GET_CUTSCENEOBJECT_SEQUENCE(int pram0)l
extern _native void END_CURRENT_TRANSITION_FROM_CUTSCENEOBJECT(int pram0)l
extern _native void UNK_0x2FB85996(int pram0)l
extern _native void UNK_0xB226E8E3(int pram0)l
extern _native int GET_CAMERA_CHANNEL_DIRECTION(int pram0, int pram1)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_EASE_IN(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_LERP(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void SET_CAMERASHOT_TARGET_POSITION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UI_RESTORE(char* uiLayer)l
extern _native void UNK_0x444C3C32(int pram0, int pram1, int pram2)l
extern _native void UNREGISTER_HOST_BROADCAST_VARIABLES()l
extern _native void UNREGISTER_CLIENT_BROADCAST_VARIABLES()l
extern _native void UNK_0x4D0C8AA4(int pram0)l
extern _native void NET_UPDATE_LEADERBOARD(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x89277EA3()l
extern _native void UNK_0x7154D15B()l
extern _native int UNK_0xE5C5CE63()l
extern _native int UNK_0xA684E813()l
extern _native void UNK_0x88249424(int pram0, int pram1, int pram2)l
extern _native int UNK_0x81F24788()l
extern _native int UNK_0xA80C6DE6(int pram0)l
extern _native int GET_TIME_ACCELERATION()l
extern _native int GET_NUM_PLAYERS()l
extern _native int UNK_0x49F96787()l
extern _native int NET_GET_NET_TIME()l
extern _native void UNK_0xB5DDEF68(int pram0, int pram1)l
extern _native void UNK_0x7725001B(int pram0, int pram1, int pram2)l
extern _native void UNK_0x437588E6(int pram0)l
extern _native void CLEAR_ACTOR_PROOF(int pram0, int pram1)l
extern _native int UNK_0x6396ABB7(int pram0)l
extern _native void UNK_0x7E0CDD87()l
extern _native void UI_FOCUS(const char* uiLayer)l
extern _native int UNK_0x8EFDFE89(int pram0)l
extern _native int UNK_0x7609A328(int pram0)l
extern _native void UNK_0x1105FB64(int pram0, int pram1)l
extern _native int UNK_0x9D20BDC4(int pram0)l
extern _native int FLASH_GET_INT(const char* scaleformName, const char* scaleformVarName)l
extern _native void UNK_0x8266C617(int pram0, int pram1, int pram2)l
extern _native int UNK_0xAB2D8A68(int pram0, int pram1, int pram2)l
extern _native void UNK_0x3E8E7D7B(int pram0)l
extern _native int UNK_0x0B071844(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native32(0x637E446B) Actor _CHANGE_ACTOR_MODEL_IN_LAYOUT(Layout Layout, Actor Actor, const char* ActorInLayout, eActor ActorID, vector3 Position, vector3 Rotation, int unk0)l
extern _native void UNK_0x6F6D942B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void SET_AMBIENT_VOICE_NAME(int pram0, int pram1)l
extern _native void UNK_0xF2F77F44(int pram0, int pram1)l
extern _native void SET_LOCAL_PLAYER_VOICE(int pram0)l
extern _native void SET_LOCAL_PLAYER_PAIN_VOICE(int pram0)l
extern _native void UNK_0x1E56BAFD(int pram0)l
extern _native void SET_DEADEYE_INVULNERABILITY(int pram0, int pram1)l
extern _native void SET_DEADEYE_DAMAGE_SCALING(int UNK0, float Scaling)l
extern _native void SET_DEADEYE_REGENERATION_RATE(int pram0, int pram1, int pram2)l
extern _native void SET_DEADEYE_TIMESCALE(int UNK0, float TimeScale)l
extern _native int DECOR_HANDLES_RELATIVE(int pram0)l
extern _native void UNK_0x9FC69F27(int pram0, int pram1)l
extern _native void DETACH_CAMERASHOT(int pram0)l
extern _native int GET_ACTOR_SLOT(int pram0)l
extern _native void GET_CAMERASHOT_POSITION(int pram0, int pram1)l
extern _native int UNK_0x457A0510(int pram0, int pram1)l
extern _native void GET_CAMERASHOT_DIRECTION(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_DIRECTION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GET_CAMERASHOT_FOV(int pram0)l
extern _native void INIT_CAMERASHOT_FROM_GAME_CAMERA(int pram0)l
extern _native void STREAMING_ENABLE_FORCE_FRAGMENT_HIGH_LOD(int pram0)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_EASE_OUT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ADD_CAMERASHOT_COLLISION_BOUNDFLAG(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_OBJECT(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_TARGET_OFFSET(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_FOCAL_LENGTH(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_CUTOFF_DISTANCE(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_USING_SOFT_DOF(int pram0, int pram1, int pram2)l
extern _native void SET_CAMERASHOT_TARGETDOF_SMOOTHING(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_FILTERTYPE(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_FSTOP(int pram0, int pram1)l
extern _native void CAMERASHOT_ADD_ARC_BEHAVIOR(int pram0, int pram1)l
extern _native void UI_SET_STRING_FORMAT(const char* GXTName, const char* FormatString, const char* String1, const char* String2, const char* String3)l
extern _native int IN_SELECTED_PEDPATH(int pram0)l
extern _native int UNK_0xF81E2097(int pram0, int pram1)l
extern _native int UNK_0xA6AA7B9E(int pram0, int pram1)l
extern _native int UNK_0xF83666A6()l
extern _native void UNK_0xC78B7436()l
extern _native void UNK_0x49053A94(int pram0, int pram1)l
extern _native void UI_UNFOCUS(const char* uiLayer)l
extern _native int UNK_0xBA89F5EA(int pram0)l
extern _native const char* GET_SLOT_NAME(int SlotID)l
extern _native int UNK_0xC0FC4B57()l
extern _native int NET_IS_HOST_OF_THIS_SCRIPT()l
extern _native void UNK_0x2547029C(int pram0, int pram1)l
extern _native void UNK_0x46C39437(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void OBJECT_ITERATOR_RESET(int pram0)l
extern _native void UNK_0xEA2A40BC(int pram0, int pram1)l
extern _native void MEMORY_ALLOW_THROWING_EXPLOSIVES(int pram0, int pram1)l
extern _native void TASK_USE_TURRET_AGAINST_COORD(int pram0, int pram1, int pram2, int pram3)l
extern _native int COMBAT_CLASS_AI_GET_ATTRIB_FLOAT(int pram0, int pram1)l
extern _native int UNK_0xCDA6BB6C()l
extern _native int UNK_0xFF1F1730()l
extern _native int UNK_0x93050734()l
extern _native void UNK_0xE7A1C191()l
extern _native void ADD_CAMERATRANSITION_EVENT_HUDFADEIN(int pram0, int pram1, int pram2, int pram3)l
extern _native void ADD_CAMERATRANSITION_EVENT_HUDFADEOUT(int pram0, int pram1, int pram2, int pram3)l
extern _native int GET_VOLUME_HEADING(int pram0)l
extern _native void TASK_USE_TURRET(int pram0, int pram1, int pram2)l
extern _native void UNK_0x03240324(int pram0, int pram1)l
extern _native void UNK_0x6471D75C(int pram0, int pram1)l
extern _native void UNK_0x53895856(int pram0, int pram1)l
extern _native void UNK_0x9C471E7D(int pram0, int pram1)l
extern _native void UNK_0x1A82B949(int pram0, int pram1)l
extern _native void UNK_0xE5E04E83(int pram0, int pram1)l
extern _native void UNK_0x6CEFA97A(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0x5E84F53E(int pram0)l
extern _native void UNK_0x4FA19C01()l
extern _native int UNK_0x5BD2295E()l
extern _native void UNK_0x3AE77125(int pram0, int pram1, int pram2, int pram3)l
extern _native void AI_SET_WEAPON_DESIRED_RANGE(int pram0, int pram1)l
extern _native void UNK_0xA4E29C31(int pram0, int pram1)l
extern _native void REGISTER_HOST_BROADCAST_VARIABLES(int pram0, int pram1)l
extern _native void REGISTER_CLIENT_BROADCAST_VARIABLES(int pram0, int pram1)l
extern _native int UNK_0x704DBAC9(int pram0)l
extern _native void DESTROY_OBJECT_GLOW(int pram0)l
extern _native void UNK_0x77403213(int pram0, int pram1, int pram2)l
extern _native void UNK_0x418A22D5(int pram0, int pram1)l
extern _native void UNK_0xCEC355CE(int pram0, int pram1)l
extern _native int UNK_0x650A7440(int pram0, int pram1)l
extern _native void UNK_0xD771AF0B(int pram0, int pram1, int pram2)l
extern _native int UNK_0x7AB65B0C()l
extern _native int UNK_0xFB2B0CCF(int pram0)l
extern _native int UNK_0x2ADA3DD4()l
extern _native void UNK_0x7837890B(int pram0)l
extern _native void UNREGISTER_SCRIPT_WITH_AUDIO()l
extern _native int UNK_0x78B73E47(int pram0)l
extern _native int UNK_0x5908F7FE(int pram0)l
extern _native int UNK_0x19BD222F(int pram0)l
extern _native void DESTROY_OBJECT_ANIMATOR(int pram0)l
extern _native void TRAIN_SET_ENGINE_ENABLED(int pram0, int pram1)l
extern _native void UNK_0xADE865AE(int pram0, int pram1)l
extern _native void VEHICLE_SET_HANDBRAKE(Actor Vehicle, bool Handbreak)l
extern _native void TRAIN_SET_TARGET_SPEED(int pram0, int pram1)l
extern _native int UNK_0x5B417C9C(int pram0)l
extern _native int UNK_0x1A4C98C1(int pram0, int pram1)l
extern _native void GATEWAY_DISABLE(int pram0, int pram1)l
extern _native void ADD_PLAYER_DEADEYE_POINTS(int pram0, int pram1, int pram2)l
extern _native void TASK_FOLLOW_PATH_FROM_NEAREST_POINT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void TRAIN_SET_POSITION_DIRECTION(int pram0, int pram1, int pram2)l
extern _native int GATEWAY_GET_VOLUME(int pram0)l
extern _native void UNK_0x5FEA3E61(int pram0, int pram1)l
extern _native int UNK_0x7D397CAA(int pram0)l
extern _native int GET_OBJECT_ATTACHED_TO(int pram0)l
extern _native int UNK_0x97931B87(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xFE83A4FE(int pram0)l
extern _native void UNK_0x1C147E14(int pram0, int pram1)l
extern _native void UNK_0x1306549E(int pram0, int pram1)l
extern _native int UNK_0xCA6231C1(int pram0)l
extern _native void REMOVE_CAMERA_COLLISION_EXCLUSION(int pram0, int pram1)l
extern _native int IS_PHYSINST_READY(int pram0)l
extern _native void SET_PROP_FIXED(int pram0, int pram1)l
extern _native int IS_ACTOR_JUMPING(int pram0)l
extern _native int IS_ACTOR_USING_COVER(int pram0)l
extern _native int GET_PLAYER_ZOOM_STATE(int pram0)l
extern _native int UNK_0x8C7E41E2(int pram0, int pram1)l
extern _native int GET_EVENT_TYPE(int pram0)l
extern _native int UNK_0x7EB1ED99(int pram0)l
extern _native void UI_ANIM_SETUP(int pram0, int pram1, int pram2, int pram3)l
extern _native void UI_ANIM_RESTART(int pram0)l
extern _native int UNK_0xFF65A07C()l
extern _native int SQUAD_GOAL_ADD_BATTLE_DEFEND_VOLUME(int pram0, int pram1, int pram2, int pram3)l
extern _native void SCALE_VOLUME(int pram0, int pram1)l
extern _native int UNK_0x860FCDBD()l
extern _native int UNK_0x0D0A66B6(int pram0, int pram1, int pram2, int pram3)l
extern _native int LINK_OBJECT_ANIMATOR_TO_ACTOR(int pram0, int pram1, int pram2)l
extern _native void ADD_CAMERA_COLLISION_EXCLUSION(int pram0, int pram1, int pram2)l
extern _native void PRINT_SMALL_FORMAT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native32(0x4FE2B586) void _SET_ACTOR_INFINITE_AMMO(Actor Actor, int WeapId, bool Infinite)l
extern _native Layout GET_EVENT_LAYOUT()l
extern _native int IS_EVENT_VALID(int pram0)l
extern _native int UNK_0xB64DDA6F(int pram0)l
extern _native int TRAIN_CREATE_NEW_TRAIN(int pram0, int pram1, int pram2)l
extern _native void UNK_0xA7A672FA(int pram0, int pram1)l
extern _native int TRAIN_GET_CAR(int pram0, int pram1)l
extern _native int CREATE_WORLD_SECTOR(int pram0, int pram1)l
extern _native int UNK_0xC5E372BC(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xD4A54348(int pram0, int pram1, int pram2, int pram3)l
extern _native int SQUAD_GOAL_ADD_STAY_OUTSIDE_OF_VOLUME(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void TASK_GO_NEAR_ACTORSET(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xA9F5CDCB(int pram0)l
extern _native void TRAIN_ENABLE_VISUAL_DEBUG(int pram0)l
extern _native void DESTROY_LAYOUT_OBJECTS(int pram0)l
extern _native void UI_HIDE(const char* uiLayer)l
extern _native void UI_SHOW(const char* uiLayer)l
extern _native void UNK_0xB3FC8CB7(int pram0, int pram1)l
extern _native void UNK_0x5AEA32D1(int pram0, int pram1)l
extern _native void UNK_0x175BE678(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0xB4D9B233(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void SQUAD_FLOCK_ADD_EXTERNAL_VELOCITY_MATCH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void SQUAD_FLOCK_ADD_EXTERNAL_ATTRACTION_PATH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void SQUAD_FLOCK_PLAYER_WHISTLE_BOOST_SET_ENABLED(int pram0, int pram1, int pram2)l
extern _native int UNK_0x142D9F3A(int pram0, int pram1)l
extern _native int UNK_0xBD374C00(int pram0)l
extern _native void GET_PATH_POINT(int pram0, int pram1, int pram2)l
extern _native void AI_SET_NAV_MAX_WATER_DEPTH_LEVEL(int pram0, int pram1)l
extern _native void SQUAD_FLOCK_SET_EXTERNAL_MOVEMENT_TUNING(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void GATEWAY_SET_ACTOR(int pram0, int pram1)l
extern _native void GRINGO_ENABLE_TYPE(int pram0)l
extern _native void TRAIN_RELEASE_TRAIN(int pram0, int pram1)l
extern _native void TRAIN_DESTROY_TRAIN(int pram0)l
extern _native int TRAIN_GET_NUM_CARS(int pram0)l
extern _native int UNK_0x138F38AC(int pram0)l
extern _native void TASK_POINT_GUN_AT_COORD(int pram0, int pram1, int pram2)l
extern _native int ACTOR_HAS_ANIM_SET(int pram0, int pram1)l
extern _native void CLEAR_FACTION_STATUS_TO_INDIVIDUAL_ACTOR(int pram0, int pram1)l
extern _native int GET_ACTOR_STUCK_STATE(int pram0)l
extern _native void UNK_0xD95C01D2(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xE79F6CD4(int pram0, int pram1)l
extern _native void SET_PLAYER_CONTROL_CONFIG(int pram0, int pram1)l
extern _native void SET_FORCE_PLAYER_AIM_MODE(int pram0, int pram1)l
extern _native void UNK_0xB6CA7EBF(int pram0)l
extern _native void UNK_0x160E79C6(int pram0, int pram1)l
extern _native void UNK_0x6E946AF8(int pram0)l
extern _native int UNK_0xF9CC7F63(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void UI_SUPPRESS(char* uiLayer)l
extern _native int UNK_0x42A4CCD5(int pram0)l
extern _native void GRINGO_DISABLE_TYPE(int pram0)l
extern _native void UNK_0xFD759593(int pram0, int pram1)l
extern _native void SET_BOAT_EXTRA_STEER(int pram0, int pram1)l
extern _native void UNK_0x44930268(int pram0, int pram1)l
extern _native void UNK_0x4FCE7B9D(int pram0)l
extern _native void UNK_0xDD0320CB()l
extern _native void SET_DAMAGE_SCALE_ENABLE(int pram0, int pram1)l
extern _native void TASK_OVERRIDE_SET_MOVESPEED_NORMALIZED(int pram0, int pram1)l
extern _native void UNK_0x0753A098(int pram0, int pram1)l
extern _native void SET_FACTION_STATUS_TO_INDIVIDUAL_ACTOR(int pram0, int pram1, int pram2)l
extern _native void SET_VEHICLE_EJECTION_ENABLED(int pram0, int pram1)l
extern _native void UNK_0x2B8F86ED(int pram0)l
extern _native int UNK_0x794F5C21(int pram0)l
extern _native int UNK_0xC673362C(int pram0, int pram1)l
extern _native int UNK_0xC09ACD5C(int pram0)l
extern _native int UNK_0x95A543E2(int pram0)l
extern _native void UNK_0xBD42097A(int pram0)l
extern _native int UNK_0xFD355ED1(int pram0, int pram1)l
extern _native int UNK_0x805AC16A(int pram0, int pram1)l
extern _native void UNK_0x67031EDA()l
extern _native void UNK_0xD6111569(int pram0)l
extern _native void UNK_0x0AAE9E6B(int pram0)l
extern _native int UNK_0x4F652A00()l
extern _native int UNK_0xFC564903()l
extern _native void UNK_0xD7572C68(int pram0)l
extern _native int UNK_0x76F09F04()l
extern _native void UNK_0x87A3A38D(int pram0)l
extern _native int UNK_0xEC6F465F(int pram0, int pram1)l
extern _native void UNK_0x98FC68AF(int pram0)l
extern _native32(0xA56B459C) void _UI_DISABLE(bool disable)l
extern _native void UNK_0x20B684AB(int pram0)l
extern _native void UNK_0xFA382FCB(int pram0, int pram1)l
extern _native void UNK_0x0547A660(int pram0)l
extern _native void UNK_0xCF065186(int pram0)l
extern _native void UNK_0xBE7965C8(int pram0)l
extern _native void UNK_0xD4C7E0D5(int pram0)l
extern _native int UNK_0x59466B4D()l
extern _native int PLAY_SOUND_FROM_OBJECT(int pram0, int pram1)l
extern _native void RELEASE_SOUND_ID(int pram0)l
extern _native int UNK_0xADF7D54B(int pram0)l
extern _native Object CREATE_MP_TEXT(Object Prop, const char* UnkNullStr, const char* GXTTextToDisplay, vector3 Position, vector3 Rotation, bool MaybeIsStringLiteral)l
extern _native int UNK_0xE8739A48(int pram0)l
extern _native void UNK_0x1F9EE9E1(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x6AFF3122(int pram0)l
extern _native void UNK_0x1904CC1D(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x08D06543(int pram0)l
extern _native void SET_SECTOR_PROPS_SUPER_LOCKED(int pram0, int pram1)l
extern _native void UNK_0x84CD0651(int pram0, int pram1, int pram2)l
extern _native int UNK_0x0AFC0B99()l
extern _native int IS_DOOR_CLOSING(int pram0)l
extern _native int IS_DOOR_CLOSED(int pram0)l
extern _native int IS_DOOR_OPENING(int pram0)l
extern _native void CLOSE_DOOR(int pram0, int pram1)l
extern _native void UNK_0x7CFD539A(int pram0, int pram1, int pram2)l
extern _native int UNK_0xE92C3435(int pram0)l
extern _native void UNK_0x591339B9(int pram0, int pram1)l
extern _native void TOGGLE_JOURNAL_UI(int pram0, int pram1)l
extern _native void UNK_0xB1B643E0(int pram0)l
extern _native void UNK_0xA0AE0C98(int pram0, int pram1)l
extern _native void UNK_0x48123591(int pram0)l
extern _native void UNK_0xC741F051(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void UNK_0xD291A820(int pram0)l
extern _native void UNK_0xCE5CCF2E(int pram0, int pram1)l
extern _native int UNK_0xC589CD7D()l
extern _native void UNK_0xB0B4296A()l
extern _native void UNK_0x8A1D83F2()l
extern _native int UNK_0x44C07DA5(int pram0)l
extern _native int UNK_0x69BE2817(int pram0)l
extern _native int UNK_0xD8C8BEA1(int pram0)l
extern _native int UNK_0x679C5955(int pram0)l
extern _native int GET_OBJECT_NAMED_BONE_ORIENTATION(int pram0, int pram1, int pram2)l
extern _native int UNK_0x8BD88B43()l
extern _native int UNK_0x1C7C0F86(int pram0, int pram1, int pram2)l
extern _native int UNK_0x836F42DA(int pram0, int pram1, int pram2, int pram3)l
extern _native void INIT_CAMERA_FROM_CHANNEL(int pram0, int pram1)l
extern _native int UNK_0x85049505(int pram0, int pram1)l
extern _native void UNK_0x9A56C3F3(int pram0, int pram1)l
extern _native int UNK_0xD9965A9A()l
extern _native void UNK_0x4585821E(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x4238C471()l
extern _native void SET_BLIP_VISIBLE(int pram0, int pram1)l
extern _native bool IS_BUTTON_RELEASED(Controller Controller, eButton Button, int Unk1, int Unk0)l
extern _native void UNK_0x408E28E2(int pram0)l
extern _native int NET_IS_PLAYER_PARTICIPANT(int pram0)l
extern _native void SET_FACTION_IS_LAWFUL_TO_ATTACK(int pram0, int pram1)l
extern _native void MARK_REGION_READY(int pram0)l
extern _native void TASK_ANIMAL_PATROL(int pram0, int pram1)l
extern _native void UNK_0x27A00456(int pram0)l
extern _native void UNK_0x5C4CAE3A(int pram0)l
extern _native int NET_GET_HOST_OF_THIS_SCRIPT()l
extern _native int UNK_0xB6006EA9(int pram0)l
extern _native int NET_GET_SCRIPT_STATUS()l
extern _native void NET_SET_THIS_SCRIPT_IS_NET_SCRIPT(int pram0)l
extern _native void UNK_0x4897DD37(int pram0)l
extern _native int UNK_0xE1D265FA(int pram0)l
extern _native void REMOVE_ALL_PICKUPS()l
extern _native int GET_SOUND_ID()l
extern _native void UNK_0xB157BBB4(int pram0, int pram1)l
extern _native void AT_FIRED_LAST(int pram0, int pram1, int pram2)l
extern _native void UNK_0x1182C34F(int pram0)l
extern _native void UNK_0xD0FB6AF0(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xDF50D8DE(int pram0, int pram1)l
extern _native int FLASH_SET_INT(const char* scaleformName, const char* scaleformVarName, int value)l
extern _native int UNK_0x554CF528(int pram0)l
extern _native int SET_OBJECT_ANIMATOR_NODE(int pram0, int pram1)l
extern _native void UNK_0xC00F8181(int pram0)l
extern _native int CUTSCENEOBJECT_GET_CURRENT_TRANSITION_TYPE(int pram0)l
extern _native int UNK_0x28DAED2A(int pram0)l
extern _native int UNK_0xD4DEBC08(int pram0)l
extern _native void UNK_0x75DD203B(int pram0)l
extern _native void UNK_0xB829A92D(int pram0)l
extern _native void END_SCRIPTED_REQUEST(int pram0)l
extern _native void UNK_0xE783219A(int pram0)l
extern _native void UNK_0x6AF07F86(int pram0)l
extern _native void UNK_0xCE7CE46D(int pram0, int pram1)l
extern _native void UNK_0xEA2B35DB()l
extern _native void UI_HIDE_PROMPT(int pram0)l
extern _native void UNK_0x5C7F63E3(int pram0)l
extern _native void SET_AUTO_CONVERSATION_LOOK(int pram0, int pram1)l
extern _native int UNK_0xECD4F604(int pram0, int pram1)l
extern _native int UNK_0xDD807723(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xAD313D88(int pram0, int pram1)l
extern _native int UNK_0x9AD6D5B1(int pram0, int pram1)l
extern _native int IS_PROCESSING_CAMERA_SHOT_TRANSITION(int pram0)l
extern _native void END_CURRENT_CAMERA_SHOT_TRANSITION(int pram0)l
extern _native void UNK_0x7D95325E()l
extern _native int CREATE_OBJECT_LOCATOR(int pram0, int pram1)l
extern _native int UNK_0xE25F407D(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void UNK_0x8FB32562(int pram0)l
extern _native float GET_ANALOG_BUTTON_VALUE(Controller Controller, eButton Analog, bool Unk1)l
extern _native void UNK_0x77D6ABF5(int pram0, int pram1)l
extern _native int CAMERA_GET_CURRENT_TRANSITION_TYPE(int pram0)l
extern _native void UI_SET_PROMPT_STRING(int pram0, int pram1)l
extern _native int UNK_0xE39B92B7(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void UI_SET_PROMPT_ICON(int pram0, int pram1)l
extern _native int UNK_0x0627DDEC(int pram0, int pram1)l
extern _native int UNK_0x9BC05C90(int pram0, int pram1)l
extern _native int SET_PANIM_PHASE(int pram0, int pram1)l
extern _native int FLASH_SET_STRING(const char* scaleformName, const char* scaleformVarName, int pram2, int pram3)l
extern _native int UNK_0x54A417F3(int pram0, int pram1)l
extern _native void SET_CAMERASHOT_TARGETDOF_FIXED_DISTANCE(int pram0, int pram1)l
extern _native int ADD_CAMERA_SHOT_TRANSITION_EASE_IN_OUT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int ADD_CAMERA_SHOT_TRANSITION_INDEFINITE(int pram0, int pram1, int pram2)l
extern _native int UNK_0x31940E4C(int pram0, int pram1)l
extern _native void HIDE_PHYSINST(int pram0)l
extern _native int UNK_0xD12802AF(int pram0)l
extern _native void UNK_0xB3C3FF5E()l
extern _native int UNK_0x64C2DD40(int pram0, int pram1)l
extern _native int UNK_0x0D914C89()l
extern _native int UNK_0x9B903F45(int pram0)l
extern _native void UNK_0xCF1B9B11(int pram0, int pram1)l
extern _native int NET_IS_POSSE_LEADER()l
extern _native int NET_GET_POSSE_COUNT()l
extern _native void END_CURRENT_MINIGAME()l
extern _native void START_MINIGAME(int pram0)l
extern _native int IS_LOCAL_PLAYER(int pram0)l
extern _native int UNK_0x554FC5E0()l
extern _native void UNK_0x1EEE7494(int pram0, int pram1)l
extern _native void SET_ACTOR_ALLOW_DISMOUNT(int pram0, int pram1)l
extern _native void UI_DEACTIVATE(const char* pram0)l
extern _native int UNK_0x1A59E608(int pram0)l
extern _native void UNK_0xA3AE09EF()l
extern _native void UNK_0x27D40FD1(int pram0, int pram1, int pram2)l
extern _native void UNK_0xB4C867BD(int pram0, int pram1, int pram2, int pram3)l
extern _native bool IS_ACTOR_SHOOTING(Actor Actor)l
extern _native int IS_ACTOR_THROWING(int pram0)l
extern _native void SET_EQUIP_SLOT_ENABLED(int pram0, int pram1, int pram2)l
extern _native int COPY_VOLUME(int pram0, int pram1, int pram2, int pram3)l
extern _native int OBJECT_ITERATOR_PREV(int pram0)l
extern _native int UNK_0x276EFF8E(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xD792B93B(int pram0, int pram1)l
extern _native void SET_CAMERA_TARGETDOF_USING_SOFT_DOF(int pram0, int pram1, int pram2)l
extern _native void UNK_0x0AA5D947(int pram0, int pram1)l
extern _native void UNK_0xEEC81873(int pram0, int pram1)l
extern _native int UNK_0x4A8066FB()l
extern _native void UNK_0xBEDF7AA8()l
extern _native int SS_REGISTER(int pram0, int pram1, int pram2)l
extern _native void UNK_0xEC1E8210()l
extern _native void UNK_0x06B4A139(int pram0)l
extern _native void UNK_0x22424394(int pram0, int pram1)l
extern _native void UNK_0x83E043A6()l
extern _native void UNK_0x03CD9C87(int pram0, int pram1)l
extern _native void UNK_0x39F5EF0F(int pram0, int pram1)l
extern _native void UNK_0xD6CC6907(int pram0, int pram1)l
extern _native void UNK_0x9D886C2F(int pram0, int pram1)l
extern _native void UNK_0x714D5D09(int pram0, int pram1)l
extern _native void UNK_0xBF959948(int pram0)l
extern _native void UNK_0x3C163FDD(int pram0)l
extern _native void UNK_0x67770F4B(int pram0, int pram1, int pram2, int pram3)l
extern _native void ANIMAL_SPECIES_TUNING_SET_ATTRIB_BOOL(int pram0, int pram1, int pram2, int pram3)l
extern _native void ANIMAL_SPECIES_TUNING_SET_ATTRIB_FLOAT(int pram0, int pram1, int pram2, int pram3)l
extern _native void ANIMAL_SPECIES_FLOCK_SET_PARAMETER(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ANIMAL_SPECIES_REL_SET_PREDATOR_AND_PREY(int pram0, int pram1)l
extern _native void ANIMAL_SPECIES_FLOCK_SET_BOOLEAN_PARAMETER(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ANIMAL_SPECIES_FLOCK_SET_ENABLED(int pram0, int pram1, int pram2, int pram3)l
extern _native void ANIMAL_SPECIES_TUNING_MOVE_SET_ATTRIB(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ANIMAL_SPECIES_INIT_BEGIN(int pram0)l
extern _native void ANIMAL_SPECIES_INIT_REGISTER(int pram0, int pram1)l
extern _native void ANIMAL_SPECIES_INIT_END()l
extern _native void ANIMAL_SPECIES_FLOCK_AND_TUNING_CLEAR_ALL()l
extern _native void ANIMAL_SPECIES_REL_CLEAR_ALL()l
extern _native void ANIMAL_SPECIES_TUNING_SET_ATTACHMENT_WITH_OFFSET(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void ANIMAL_SPECIES_REL_SET_EAT_GRINGO(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_REL_SET_CAN_WARN(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_REL_SET_THREAT(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_ADD_EXTERNAL_INFLUENCE_FLOCK_REASONER(int pram0, int pram1)l
extern _native void ANIMAL_SPECIES_TUNING_SET_ATTRIB_FLOAT_FROM_TIME(int pram0, int pram1, int pram2, int pram3)l
extern _native void ANIMAL_SPECIES_ADD_EXTERNAL_REPULSION(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ANIMAL_SPECIES_REL_SET_AVOID(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_ADD_EXTERNAL_RANDOM_NOISE(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ANIMAL_SPECIES_SET_SPECIAL_USE_GRINGO(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ANIMAL_SPECIES_TUNING_SET_HUNTING_PREY_PROP(int pram0, int pram1)l
extern _native void ANIMAL_SPECIES_REL_SET_ATTACK_GRAB_ENABLED(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_REL_SET_PLAY_GROWL(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_REL_SET_PLAY_SNIFF(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_REL_SET_PLAY_HUNT(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_REL_SET_PLAY_CHASE(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_REL_SET_PLAY_BEG(int pram0, int pram1, int pram2)l
extern _native void ANIMAL_SPECIES_SET_UNALERTED_BEHAVIOR(int pram0, int pram1, int pram2, int pram3)l
extern _native void ANIMAL_SPECIES_TUNING_SET_ATTACHMENT_WITH_CHILDBONE(int pram0, int pram1, int pram2, int pram3)l
extern _native void ANIMAL_SPECIES_NEEDS_DOMESTICATION_LEVELS(int pram0)l
extern _native void UNK_0x1957B498(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x88FD9623(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x192973A0(int pram0, int pram1, int pram2, int pram3)l
extern _native void SET_FACTION_TO_FACTION_ACCURACY_SCALE_FACTOR(int pram0, int pram1, int pram2)l
extern _native void UNK_0xAD3877AF(int pram0)l
extern _native void RELOAD_FACTIONS(int pram0)l
extern _native void UNK_0x0079FD0F()l
extern _native void SET_VEHICLE_APPOINTMENT_TARGET()l
extern _native void UNK_0xF4641CF4(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x4BCFADB1(int pram0, int pram1)l
extern _native void UNK_0xF435CCDE(int pram0)l
extern _native void UNK_0x39EF8DA7()l
extern _native void UNK_0x8BE2D8B0(int pram0)l
extern _native void UNK_0x724B4E9B(int pram0, int pram1)l
extern _native int REMOVE_ASSET(int pram0, int pram1)l
extern _native void UNK_0x10BD98C9(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x4D42E285(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xE694F53A(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x82609DC7(int pram0, int pram1, int pram2)l
extern _native void UNK_0x628E3173(int pram0, int pram1, int pram2)l
extern _native void UNK_0xA6C4E59F(int pram0, int pram1, int pram2)l
extern _native void UNK_0xEA06907B(int pram0, int pram1, int pram2)l
extern _native void UNK_0xA2597101(int pram0, int pram1, int pram2)l
extern _native int UNK_0x629E2E88()l
extern _native int COMBAT_CLASS_REQUEST_GET_ACTOR()l
extern _native void COMBAT_CLASS_REQUEST_COMPLETED()l
extern _native void SET_ACTOR_ALLOW_WEAPON_REACTION_FLEE(int pram0, int pram1)l
extern _native void AI_SET_NAV_HAZARD_AVOIDANCE_ENABLED(int pram0, int pram1, int pram2)l
extern _native void SET_ACTOR_SEX(int pram0, int pram1)l
extern _native void UNK_0x4D53AC21(int pram0, int pram1)l
extern _native void UNK_0x12A86E9D(int pram0, int pram1)l
extern _native void UNK_0x91220723(int pram0, int pram1, int pram2)l
extern _native void UNK_0x5613615B(int pram0, int pram1)l
extern _native int UNK_0x76478D6E()l
extern _native int UNK_0xA488E930(int pram0)l
extern _native void UNK_0x9679CF84(int pram0, int pram1)l
extern _native void UNK_0x39928706(int pram0, int pram1)l
extern _native int UNK_0x1EE7153B(int pram0, int pram1, int pram2)l
extern _native int UNK_0xA8F64D32(int pram0, int pram1)l
extern _native int ACTOR_GET_WEAPON_AMMO(int pram0, int pram1)l
extern _native void AI_SHOOT_TARGET_SET_BONE(int pram0, int pram1, int pram2)l
extern _native void TASK_USE_TURRET_AGAINST_OBJECT(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x856C3A8A(int pram0, int pram1, int pram2)l
extern _native int ANIMAL_ACTOR_GET_DOMESTICATION(int pram0)l
extern _native int UNK_0x2A902148(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void AI_GLOBAL_CLEAR_DANGER(int pram0)l
extern _native void UNK_0x468DDDB3(int pram0, int pram1)l
extern _native int UNK_0x5DE07F18(int pram0)l
extern _native int SET_CURRENT_MAP(int pram0)l
extern _native int UNK_0xF62EE158()l
extern _native void UNK_0x449D4A89(int pram0)l
extern _native int UNK_0xAEC955F8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x28FCBDF2(int pram0)l
extern _native void ALLOW_TUMBLEWEEDS(int pram0)l
extern _native void UI_SET_ICON(int pram0, int pram1)l
extern _native void UNK_0xDF4627D1(int pram0, int pram1)l
extern _native void UNK_0xDC330FB9(int pram0)l
extern _native int UNK_0x9AC89564(int pram0, int pram1, int pram2)l
extern _native int UNK_0xA61FA36B()l
extern _native int UNK_0x1E81DB60(int pram0, int pram1, int pram2)l
extern _native void UNK_0x2F7CB0E3(int pram0, int pram1)l
extern _native void UNK_0x955E5EEB(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void UNK_0x59A7835E()l
extern _native int UNK_0x57FC0E16(int pram0)l
extern _native int IS_PHYSINST_IN_LEVEL(int pram0)l
extern _native int GET_JOURNAL_ENTRY_NUM_DETAILS(int pram0)l
extern _native int GET_JOURNAL_ENTRY_DETAIL_HASH_BY_INDEX(int pram0, int pram1)l
extern _native void UNK_0x5209C0C0(int pram0, int pram1, int pram2, int pram3)l
extern _native void ENABLE_MOVER(int pram0)l
extern _native int UNK_0x7246F438(int pram0)l
extern _native int UNK_0x6A0FE2A0(int pram0, int pram1)l
extern _native int UNK_0xAC5043C5()l
extern _native void UNK_0x9E6CAD1D(int pram0, int pram1)l
extern _native void SUSPEND_MOVER(int pram0)l
extern _native void SET_CURVE_ACTIVE(int pram0, int pram1)l
extern _native void RELEASE_CONSTRAINT(int pram0)l
extern _native void SET_BRIDGE_STIFFNESS(int pram0, int pram1)l
extern _native int UNK_0x4A05AA7D(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void SET_SLEEP_TOLERANCE(int pram0, int pram1)l
extern _native int UNK_0xC039BBF1(int pram0, int pram1, int pram2)l
extern _native int UNK_0x51CF9A54(int pram0, int pram1, int pram2)l
extern _native int GET_OBJECT_RELATIVE_OFFSET(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0xBE17EB88(int pram0)l
extern _native void UNK_0xABC78721(int pram0)l
extern _native int GRINGO_QUERY_STRUCT(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xBBB2780E()l
extern _native int UNK_0xF4015EFC()l
extern _native int IS_GRINGO_ACTIVE()l
extern _native int UNK_0xF550F8E7()l
extern _native int UNK_0xCA589BAB()l
extern _native int UNK_0x2F096285()l
extern _native int UNK_0x54745DB0()l
extern _native int UNK_0xD62D413C(int pram0)l
extern _native void GRINGO_ENABLE_PLAYER_CONTROL(int pram0, int pram1)l
extern _native int UNK_0x926FD361()l
extern _native void GRINGO_SET_MESSAGE_RETURN(int pram0)l
extern _native void GRINGO_WAIT(int pram0)l
extern _native void GRINGO_STOP()l
extern _native int GRINGO_HANDLES_MOVEMENT(int pram0)l
extern _native int SET_GRINGO_BOOL_ATTR(int pram0, int pram1, int pram2)l
extern _native int GET_TARGET_OBJECT()l
extern _native void UNK_0x9A756A72(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0x0A0E660E()l
extern _native int GET_GRINGO_BOOL_ATTR(int pram0, int pram1, int pram2)l
extern _native void UNK_0x89DE8A75(int pram0, int pram1)l
extern _native int GET_GRINGO_STRING_ATTR(int pram0, int pram1, int pram2)l
extern _native int GET_GRINGO_FLOAT_ATTR(int pram0, int pram1, int pram2)l
extern _native void UNK_0x7284A71B(int pram0, int pram1)l
extern _native int UNK_0x5CFBF505(int pram0)l
extern _native int UNK_0x3A31175A(int pram0)l
extern _native int UNK_0x6426CCD6(int pram0)l
extern _native int IS_GRINGO_COMPONENT_VALID(int pram0)l
extern _native int UNK_0xE18BCD70(int pram0, int pram1, int pram2)l
extern _native int UNK_0x4DB7C61C(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xA20141C0(int pram0)l
extern _native int GRINGO_GET_ATTRIBUTE(int pram0, int pram1)l
extern _native int GRINGO_GET_ATTRIBUTE_COUNT(int pram0)l
extern _native int UNK_0xBED45A9A(int pram0)l
extern _native int UNK_0xBF322F5C(int pram0)l
extern _native int GRINGO_GET_ATTRIBUTE_HASH(int pram0)l
extern _native int UNK_0xD7BB1792(int pram0, int pram1)l
extern _native int UNK_0xD282013F(int pram0, int pram1)l
extern _native int IS_PROP_FIXED(int pram0)l
extern _native int UNK_0x663F1464(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x4A1D2E25(int pram0)l
extern _native int UNK_0x817B6952(int pram0)l
extern _native void UNK_0x53B9569C(int pram0, int pram1)l
extern _native int UNK_0x0912622D(int pram0)l
extern _native int NET_SET_NODE_REPLICATION(int pram0, int pram1, int pram2)l
extern _native int UNK_0xC17BAD12(int pram0)l
extern _native void SET_ANIMAL_CAN_ATTACK(int pram0, int pram1)l
extern _native int UNK_0x35279C3F(int pram0, int pram1)l
extern _native int UNK_0x5F516FC3(int pram0)l
extern _native void UNK_0xB62FE25C(int pram0, int pram1)l
extern _native int AI_SPEECH_GET_ALLOW_FOR_ACTOR(int pram0)l
extern _native int UNK_0xE4C686BA(int pram0, int pram1, int pram2)l
extern _native int UNK_0xAE7B3880()l
extern _native int UNK_0x600A0EE4(int pram0, int pram1)l
extern _native int UNK_0xAFF7D382(int pram0, int pram1, int pram2)l
extern _native int GRINGO_RETURN_ACTOR_TO_DEFAULT_ANIMS(int pram0)l
extern _native void REPORT_GRINGO_USE_PHASE(int pram0, int pram1)l
extern _native int UNK_0xD3D8E8ED(int pram0, int pram1)l
extern _native void UNK_0x29AEB2DB(int pram0, int pram1)l
extern _native void UNK_0x6695E185(int pram0, int pram1)l
extern _native int UNK_0x1D711058(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x87BA5FE9(int pram0, int pram1)l
extern _native int UNK_0x721FC9A4(int pram0)l
extern _native int UNK_0x6263F909(int pram0)l
extern _native int UNK_0x3E8F94BE(int pram0, int pram1)l
extern _native int GRINGO_GET_PHYSINST(int pram0)l
extern _native int UNK_0xB96874B4(int pram0)l
extern _native int UNK_0x5B46757F(int pram0)l
extern _native int UNK_0x15A0E28B(int pram0)l
extern _native int UNK_0x5AF74E19(int pram0, int pram1)l
extern _native int UNK_0x1F74EE6C(int pram0, int pram1, int pram2)l
extern _native int UNK_0x405E3903(int pram0, int pram1)l
extern _native int UNK_0xEEE9C799(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int GET_GRINGO_VECTOR_ATTR(int pram0, int pram1, int pram2)l
extern _native void UNK_0x026F7060(int pram0, int pram1, int pram2, int pram3)l
extern _native int SET_GRINGO_VECTOR_ATTR(int pram0, int pram1, int pram2)l
extern _native int SET_GRINGO_FLOAT_ATTR(int pram0, int pram1, int pram2)l
extern _native int GRINGO_ACTOR_MOVE_TO_AND_FACE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int UNK_0xFF1FC1EF()l
extern _native int UNK_0x24BAABCA(int pram0)l
extern _native void RESET_REACT_NODE_FOR_ACTOR(int pram0)l
extern _native int UNK_0x5C11B011(int pram0, int pram1)l
extern _native int UNK_0xA7E9DA22(int pram0)l
extern _native void UNK_0x61664EC0(int pram0, int pram1, int pram2)l
extern _native int UNK_0x4F10FD5B(int pram0)l
extern _native void RESET_PROP(int pram0)l
extern _native void UNK_0x90FBBB8B(int pram0)l
extern _native void UNK_0x8C2914C4(int pram0, int pram1)l
extern _native void UNK_0x22D573D2(int pram0)l
extern _native int UNK_0x51581898(int pram0)l
extern _native int UNK_0x7E81694C(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native void GRINGO_SET_COMPONENT_USER(int pram0, int pram1)l
extern _native int UNK_0x9CD3385E(int pram0)l
extern _native void GRINGO_SET_REQUEST_STRING(int pram0)l
extern _native int UNK_0xBC32DA9A(int pram0, int pram1, int pram2)l
extern _native int GET_ACTOR_GAIT_TYPE(int pram0)l
extern _native void UNK_0x8CAF5C5C(int pram0)l
extern _native int UNK_0x65CA3037(int pram0)l
extern _native int UNK_0x5388F37D()l
extern _native int UNK_0x284DD17C(int pram0, int pram1)l
extern _native int UNK_0x3FA5FC03(int pram0)l
extern _native int UNK_0xD6EE9534(int pram0, int pram1, int pram2)l
extern _native void UNK_0xC8C0C708(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x7BF01CCB()l
extern _native void UNK_0x8EA46104(int pram0)l
extern _native int GET_TARGET_ACTOR()l
extern _native void UNK_0xBEF32D17(int pram0, int pram1)l
extern _native void UNK_0x7D600F2F(int pram0, int pram1)l
extern _native int UNK_0x2C57A529(int pram0, int pram1)l
extern _native void GRINGO_SET_PROP_COLLISIONS(int pram0, int pram1)l
extern _native void UNK_0x175CD937(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x47D2DE08(int pram0, int pram1)l
extern _native int UNK_0x48B7C279(int pram0, int pram1)l
extern _native void UNK_0xEB046CD9(int pram0)l
extern _native void UNK_0x1C462085(int pram0)l
extern _native void UNK_0x58018D83(int pram0)l
extern _native int IS_PLAYER_SIGNED_IN()l
extern _native int UNK_0x1D177160()l
extern _native int UNK_0x1ADA1769()l
extern _native void SET_CAMERASHOT_FROM_LENS(int pram0, int pram1)l
extern _native void FORCE_CAMERASHOT_UPDATE(int pram0)l
extern _native int CAMERASHOT_IS_VISIBLE_ACTOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0xF52BA99F(int pram0)l
extern _native int IS_OBJECT_ATTACHED(int pram0)l
extern _native int IS_ACTOR_ON_BOAT(int pram0)l
extern _native int TRAIN_GET_LOD_LEVEL(int pram0)l
extern _native int TRAIN_GET_VELOCITY(int pram0)l
extern _native void UNK_0x1344515B()l
extern _native void UNK_0x364F41D6()l
extern _native int IS_POPULATION_SET_REQUIRED_RESIDENT(int pram0)l
extern _native int CREATE_ZONE_VOLUME(int pram0)l
extern _native void SET_ZONE_POPULATION_TYPE(int pram0, int pram1)l
extern _native void UNK_0x9381D459(int pram0, int pram1)l
extern _native void UNK_0xE0FDD026(int pram0, int pram1)l
extern _native void UNK_0x5996941F(int pram0, int pram1)l
extern _native void UNK_0x84FB15FA(int pram0, int pram1)l
extern _native void UNK_0x1B271D85(int pram0, int pram1)l
extern _native void SET_ZONE_POPULATION_COUNT_RANDOM(int pram0, int pram1, int pram2)l
extern _native void UNK_0xD28A3706(int pram0)l
extern _native void UNK_0x04EFC113(int pram0)l
extern _native void SET_ACCESSORYSET_ON_SPAWN(int pram0, int pram1, int pram2)l
extern _native int UNK_0xB0882841(int pram0, int pram1)l
extern _native int UNK_0x03B2D067(int pram0)l
extern _native void UNK_0x93B6135B(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void AMBIENT_SPAWN_PRESTREAM_SET(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UNK_0x0B24CE10(int pram0, int pram1)l
extern _native void UNK_0xE4A789D8(int pram0, int pram1)l
extern _native void UNK_0x07FD0A76(int pram0, int pram1)l
extern _native int UNK_0xC1195126(int pram0)l
extern _native void SET_TOWN_DENSITY(int pram0)l
extern _native void UNK_0x6C526E7B(int pram0)l
extern _native int IS_ZONE_VALID(int pram0)l
extern _native void UNK_0xD72DF5C6(int pram0, int pram1)l
extern _native void UNK_0x7D4FB8C8(int pram0, int pram1)l
extern _native void SET_ZONE_PRIORITY(int pram0, int pram1)l
extern _native void UNK_0xE7F19909(int pram0, int pram1)l
extern _native void AI_GOAL_SHOOT_AT_COORD(int pram0, int pram1)l
extern _native void SET_ALLOW_RIDE_BY_AI(int pram0, int pram1)l
extern _native void AI_SET_ALLOWED_MOUNT_DIRECTIONS(int pram0, int pram1)l
extern _native int UNK_0x3F226995(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12)l
extern _native void UNK_0x261A4C0E(int pram0, int pram1, int pram2)l
extern _native void SET_DOOR_CURRENT_SPEED(int pram0, int pram1, int pram2)l
extern _native int CAMERA_IS_VISIBLE_VOLUME(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void UNK_0x15040CD2(int pram0)l
extern _native void RESET_EXCLUSIVE_JOURNAL_ID()l
extern _native void UNK_0x14ED45FB()l
extern _native void UNK_0x1BB84187()l
extern _native void UNK_0xAC72E757(int pram0)l
extern _native void AUDIO_MISSION_RELEASE()l
extern _native void ENABLE_JOURNAL_REPLAY(int pram0)l
extern _native void UNK_0xF1779E65()l
extern _native void UNK_0x6C7A3CE6()l
extern _native void UNK_0xBEF6031B(int pram0, int pram1)l
extern _native int UNK_0xDB86F53B(int pram0)l
extern _native void DISABLE_VERIFY_SS(int pram0)l
extern _native void UNK_0xB42EBC65(int pram0)l
extern _native void UNK_0x374DE883(int pram0)l
extern _native void STREAMING_ENABLE_BOUNDS(int pram0)l
extern _native void CLEAR_MISSION_INFO()l
extern _native void SET_DEADEYE_REGENERATION_RATE_MULTIPLIER(int pram0, int pram1)l
extern _native void UNK_0x07EC142B(int pram0)l
extern _native void UNK_0x7AB17813(int pram0, int pram1)l
extern _native int UNK_0xDE339CE1()l
extern _native int UNK_0xA6CFA220()l
extern _native int UNK_0xEDF1D0B4()l
extern _native void UNK_0xC175F2B5(int pram0, int pram1)l
extern _native int UNK_0x8287F8B3(int pram0, int pram1, int pram2)l
extern _native int UNK_0x3D014AB1(int pram0)l
extern _native int UNK_0x24F97294()l
extern _native void UNK_0x2B45FADE()l
extern _native int UNK_0xA5691922()l
extern _native int UNK_0xED0BA189(int pram0)l
extern _native int UNK_0xD89902F1(int pram0)l
extern _native void UNK_0xFD300D15(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0x0FE90DCB()l
extern _native void UNK_0x98A9AC9E()l
extern _native void UNK_0xE808BFFB(int pram0)l
extern _native int UNK_0x7653788C()l
extern _native void UNK_0x98D0F458()l
extern _native int ACTOR_IS_GRABBED_BY_CUTSCENE(int pram0)l
extern _native void SET_MOST_RECENT_MOUNT(int pram0, int pram1)l
extern _native void UNK_0x755382BC(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int CUTSCENE_MANAGER_GET_INITIAL_STREAMING_LOAD_SCENE_EXT(int pram0, int pram1)l
extern _native void UNK_0x99D215B4(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UNK_0x7716B12B()l
extern _native int UNK_0xB2F2A7F2(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9410D992(int pram0, int pram1, int pram2)l
extern _native int UNK_0xC6557710(int pram0)l
extern _native int GET_LAST_NOTE_OBJECTIVE()l
extern _native int UNK_0xD9E4A8DA()l
extern _native int UNK_0xA56DCCF2(int pram0, int pram1, int pram2)l
extern _native int UNK_0xEBAB5F62(int pram0)l
extern _native void UNK_0x6287203C(int pram0)l
extern _native int AI_HAS_ACTOR_BUMPED_INTO_ME(int pram0, int pram1, int pram2)l
extern _native int UNK_0x7263860F()l
extern _native void SET_CUTSCENE_STREAMING_LOAD_SCENE(int pram0, int pram1)l
extern _native void UNK_0x9E6A776F(int pram0, int pram1)l
extern _native int UNK_0x2DB208A1()l
extern _native void AI_SET_NAV_PATHFINDING_ENABLED_WHEN_DRIVING(int pram0, int pram1)l
extern _native int UNK_0x8020C45E(int pram0, int pram1, int pram2)l
extern _native void UNK_0xF0DDF83D(int pram0)l
extern _native int AUDIO_MUSIC_IS_PREPARED()l
extern _native int AUDIO_MUSIC_PLAY_PREPARED()l
extern _native void UNK_0xE613AE52(int pram0)l
extern _native void UNK_0xF55B50ED(int pram0)l
extern _native void UNK_0x6336182D(int pram0)l
extern _native void UNK_0x84F3DD81(int pram0, int pram1)l
extern _native int UNK_0xCE01609D(int pram0)l
extern _native void UNK_0x3A6960B2(int pram0)l
extern _native void SET_ACTOR_SPEED(int pram0, int pram1)l
extern _native void AUDIO_MISSION_INIT()l
extern _native void UNK_0x66FCA3F7(int pram0)l
extern _native void SET_EXCLUSIVE_JOURNAL_ID(int pram0)l
extern _native void SET_MISSION_INFO(int pram0, int pram1)l
extern _native int UNK_0xBDD4D4D5(int pram0)l
extern _native void TRAIN_SET_MAX_ACCEL(int pram0, int pram1)l
extern _native void TRAIN_SET_TARGET_POS(int pram0, int pram1)l
extern _native void UNK_0x1440C806(int pram0, int pram1)l
extern _native void UNK_0x0911BA31(int pram0, int pram1)l
extern _native void UNK_0x47FAE768(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0xB0479CB8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void TRAIN_FORCE_HIGH_LOD(int pram0, int pram1)l
extern _native void TRAIN_SET_MAX_DECEL(int pram0, int pram1)l
extern _native void UNK_0x268D546D(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xE0BE8235(int pram0)l
extern _native void TASK_SHOOT_FROM_COVER(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ACTOR_SET_GRABBED_BY_CUTSCENE(int pram0, int pram1)l
extern _native int UNK_0x1F9F8C04(int pram0, int pram1, int pram2)l
extern _native int UNK_0xF37E8A9E(int pram0, int pram1)l
extern _native void UNK_0x7007019D(int pram0, int pram1)l
extern _native int UNK_0x8C0E3E29(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int UNK_0xB550D120(int pram0)l
extern _native void SET_PROP_TARGETABLE(int pram0, int pram1, int pram2)l
extern _native void AI_AVOID_IGNORE_ACTOR(int pram0, int pram1)l
extern _native void AI_SET_NAV_SUBGRID_CELL_SIZE(int pram0, int pram1)l
extern _native int UNK_0x8ED2B0BC(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void TASK_FOLLOW_OBJECT_ALONG_PATH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ESTIMATE_TWO_DISTANCES_ALONG_PATH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void TASK_HORSE_ACTION(int pram0, int pram1)l
extern _native int UNK_0x5DB05BBC(int pram0)l
extern _native void UNK_0x8062BD74(int pram0, int pram1, int pram2)l
extern _native void DESTROY_POINT_LIGHT(int pram0)l
extern _native void UNK_0x205E891C(int pram0, int pram1, int pram2)l
extern _native void SET_DEADEYE_BLINK(int pram0)l
extern _native void UNK_0x134AAF17(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x12558DBD(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x88863344()l
extern _native int UNK_0xD062CBF6(int pram0, int pram1)l
extern _native void DEACTIVATE_JOURNAL_ENTRY(int pram0, int pram1)l
extern _native void SET_RCM_ACTOR_CALL_OVER_ENABLE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int GET_JOURNAL_ENTRY_DISALLOW_TRACKING(int pram0)l
extern _native int GATEWAY_GET_MARKER(int pram0)l
extern _native int GET_ACTOR_INVULNERABILITY(int pram0)l
extern _native int IS_AI_ACTOR_ENGAGED_IN_COMBAT(int pram0)l
extern _native void UNK_0xD15B53F8(int pram0)l
extern _native int UNK_0xD89C14BA(int pram0)l
extern _native int GET_LAYOUT_NAME(int pram0)l
extern _native void UNK_0x50A2051C(int pram0)l
extern _native int UNK_0x79C748BE(int pram0, int pram1, int pram2)l
extern _native int IS_BLIP_VISIBLE(int pram0)l
extern _native void UNK_0x2D40E85C(int pram0, int pram1, int pram2)l
extern _native int SET_ACTOR_HEARING_MAX_RANGE(int pram0, int pram1)l
extern _native int IS_DOOR_OPEN_IN_DIRECTION(int pram0, int pram1)l
extern _native void SET_DOOR_AUTO_CLOSE(int pram0, int pram1)l
extern _native int UNK_0xD6F4FDAD(int pram0)l
extern _native bool GET_DRAW_ACTOR(Actor Actor)l
extern _native void SET_PLAYER_DEADEYE_MODE(int pram0, int pram1)l
extern _native void UNK_0xCC69DCC1(int pram0, int pram1, int pram2)l
extern _native void TASK_GUARD_STAND(int pram0, int pram1, int pram2)l
extern _native int UNK_0x22558E3F(int pram0)l
extern _native int UNK_0x26884138()l
extern _native int UNK_0xE7371670()l
extern _native void SET_INFINITE_DEADEYE(int UNK0, bool Infinite)l
extern _native int HORSE_UNLOCK_FRESHNESS(int pram0)l
extern _native int HORSE_SET_CURR_FRESHNESS(int pram0, int pram1)l
extern _native int HORSE_LOCK_FRESHNESS(int pram0)l
extern _native int DECOR_GET_VECTOR(int pram0, int pram1, int pram2)l
extern _native void SET_STAMINA_BLINK(int pram0)l
extern _native int SET_ACTOR_MAX_FRESHNESS(int pram0, int pram1)l
extern _native int UNK_0x21BCC0A9(int pram0)l
extern _native int UNK_0x75D4E33F(int pram0, int pram1)l
extern _native int UNK_0x99356925(int pram0, int pram1, int pram2)l
extern _native int UNK_0x35051831(int pram0, int pram1, int pram2)l
extern _native void UNK_0x14585073(int pram0, int pram1)l
extern _native void SET_RCM_WAS_JOHN_NOW_JACK(int pram0, int pram1)l
extern _native void AI_GOAL_LOOK_AT_PLAYER_WHEN_WITHIN(int pram0, int pram1)l
extern _native int AI_WAS_PUSHED_OVER(int pram0, int pram1)l
extern _native int UNK_0xEBC9C2FD(int pram0, int pram1)l
extern _native int AI_GLOBAL_IS_DANGER(int pram0, int pram1)l
extern _native int GET_RADAR_RADIUS()l
extern _native void UNK_0xC6E36B1D(int pram0)l
extern _native void PLAY_SOUND(int pram0)l
extern _native int UNK_0x191658C0()l
extern _native int UNK_0x32D1DEB0()l
extern _native void SET_JOURNAL_ENTRY_UPDATED(int pram0, int pram1)l
extern _native void REGISTER_TRAFFIC_OBJECTSET(int pram0)l
extern _native void SET_ACTOR_WEAPON_REACTION_NO_FLEE_HACK(int pram0, int pram1)l
extern _native void REGISTER_TRAFFIC_ACTOR(int pram0, int pram1)l
extern _native int UNK_0x1BA90C92(int pram0)l
extern _native int IS_ACTOR_WHISTLING(int pram0)l
extern _native int UNK_0x87C49DBD(int pram0, int pram1)l
extern _native int UNK_0x72F6EED0()l
extern _native int GET_EVENT_TIME(int pram0)l
extern _native void SET_GPS_PATH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void REGISTER_GPS_CURVE_OBJECTSET(int pram0)l
extern _native int UNK_0xAA322DFC(int pram0)l
extern _native void SET_JOURNAL_ENTRY_DISALLOW_TRACKING(int pram0, int pram1)l
extern _native int UNK_0x427F4D58(int pram0, int pram1, int pram2)l
extern _native int UNK_0x94F5E63F(int pram0)l
extern _native void UNK_0xAB8A1C15(int pram0)l
extern _native void UNK_0x8392855D(int pram0, int pram1)l
extern _native int UNK_0x6B439149()l
extern _native int NET_MAILBOX_IS_CHALLENGE_VALID(int pram0)l
extern _native int UNK_0xE85942F0(int pram0)l
extern _native int UNK_0xFD6197EB(int pram0, int pram1)l
extern _native int SC_CHALLENGE_GET_VAR_INT(int pram0, int pram1)l
extern _native int UNK_0xA183D927()l
extern _native void UI_CHALLENGE_SET_OBJECTIVE(int pram0, int pram1, int pram2)l
extern _native void UNK_0x761A6750(int pram0, int pram1)l
extern _native void UNK_0xAFC9071D(int pram0, int pram1, int pram2)l
extern _native void UI_BUTTON_SET_TEXT(int pram0, int pram1)l
extern _native void UNK_0xC201524D(int pram0, int pram1, int pram2)l
extern _native void UI_CHALLENGE_SET_DESCRIPTION(int pram0, int pram1)l
extern _native void UNK_0x3731AC9F(int pram0, int pram1)l
extern _native int SC_CHALLENGE_GET_COMMUNITY_VALUE(int pram0)l
extern _native int SC_CHALLENGE_GET_COMMUNITY_TOTAL(int pram0)l
extern _native void UNK_0x4A598723(int pram0, int pram1, int pram2)l
extern _native void UNK_0x9272926C(int pram0, int pram1, int pram2)l
extern _native void UI_CHALLENGE_MAKE_CURRENT(int pram0)l
extern _native int UNK_0xA3E1EF71()l
extern _native int UNK_0x34711B59()l
extern _native int UNK_0x5725C84F()l
extern _native int UNK_0x5FD52711()l
extern _native int UNK_0x86BC0A55(int pram0, int pram1)l
extern _native void UNK_0xEB4A6D85()l
extern _native int UNK_0xD0808C42()l
extern _native int UNK_0xE89C6E4F()l
extern _native int UNK_0x49C2B05F(int pram0)l
extern _native int UNK_0x0791F35A()l
extern _native int UNK_0xC813DBEF()l
extern _native int UNK_0x70AF0351(int pram0)l
extern _native int UNK_0xE6B4F505()l
extern _native int UNK_0x097BB984()l
extern _native int UNK_0x3A8C77AD(int pram0)l
extern _native int UNK_0xEA7ADF42()l
extern _native int UNK_0x293C3288()l
extern _native int UNK_0x984749B4(int pram0)l
extern _native int UNK_0xA7F231B0()l
extern _native void UNK_0x970AC1F7(int pram0, int pram1)l
extern _native void UNK_0x0A87A573(int pram0, int pram1)l
extern _native int UNK_0x25EF49AD(int pram0)l
extern _native void UNK_0x23EB81F0(int pram0, int pram1)l
extern _native void UPDATE_STAT(int pram0, int pram1, int pram2)l
extern _native void HIDE_STAT(int pram0, int pram1)l
extern _native int UNK_0x5B404EDA()l
extern _native int UNK_0x6A307D5F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void UNK_0x7FF20D84(int pram0)l
extern _native void UNK_0x364450B1(int pram0)l
extern _native int CAN_PLAYER_DIE()l
extern _native void UNK_0xCFE22435(int pram0)l
extern _native void RESET_RUMBLE()l
extern _native void UNK_0x39B0CFE5()l
extern _native void SET_FACTION_TO_FACTION_DAMAGE_SCALE_FACTOR(int pram0, int pram1, int pram2)l
extern _native int NET_REQUEST_OBJECT(int pram0)l
extern _native void TASK_RESPOND_TO_HORSE_WHISTLE(int pram0, int pram1)l
extern _native int UNK_0x50A7E334(int pram0)l
extern _native void UNK_0x48DB367D(int pram0)l
extern _native void UNK_0xB4614D11(int pram0, int pram1)l
extern _native int UNK_0x919142BE()l
extern _native int UNK_0x3A899B0E(int pram0)l
extern _native int GET_ACTOR_GROUND_MATERIAL(int pram0)l
extern _native int UNK_0x3E758743(int pram0)l
extern _native void UNK_0xE7F781B8()l
extern _native void AI_SET_SPECIAL_AREAS_TIME(int pram0, int pram1)l
extern _native int TOUGH_ARMOUR_GET_TUNING_REGENERATION_RATE(int pram0)l
extern _native void SET_PLAYER_ENABLE_MOUNT_USE_CONTEXTS(int pram0, int pram1)l
extern _native int GRINGO_QUERY_BOOL(int pram0, int pram1, int pram2, int pram3)l
extern _native int GET_GAME_STATE()l
extern _native int CREATE_JOURNAL_ENTRY_BY_HASH(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x50C0E83F(int pram0)l
extern _native int UNK_0x2776B0F5(int pram0)l
extern _native void UNK_0xB008EF49(int pram0, int pram1, int pram2)l
extern _native int UNK_0xF750D150(int pram0, int pram1, int pram2)l
extern _native void UNK_0x0E712FCB(int pram0, int pram1)l
extern _native void SET_PROP_TARGETABLE_ACQUISITION_RADIUS(int pram0, int pram1)l
extern _native void SET_PROP_TARGETABLE_SCORE_BIAS(int pram0, int pram1)l
extern _native void SET_PROP_TARGETABLE_AS_ENEMY(int pram0, int pram1)l
extern _native void SET_PROP_TARGETABLE_TARGET_BOX_SIZE(int pram0, int pram1, int pram2)l
extern _native void SET_ACTOR_DEATH_DROP_DISTANCE(int pram0, int pram1)l
extern _native void FIRE_SET_OWNER(int pram0, int pram1)l
extern _native int UNK_0x375A33F0(int pram0, int pram1)l
extern _native int ACTOR_IS_VARIABLE_MESH_ENABLED(int pram0, int pram1)l
extern _native int GET_ACTOR_PROOF(int pram0)l
extern _native void UNK_0x49BC0219(int pram0)l
extern _native void UNK_0x6085F7AC(int pram0, int pram1)l
extern _native void ADD_CAMERATRANSITION_EVENT_GAMECAMERARESETTILT(int pram0, int pram1, int pram2)l
extern _native int UNK_0xE5645CB3()l
extern _native void UNK_0xC9FCD3EC(int pram0)l
extern _native void UNK_0xEC906A7A(int pram0)l
extern _native void UNK_0xFA43DCC5(int pram0)l
extern _native int IS_ACTOR_FLYING(int pram0)l
extern _native int COPY_EVENT(int pram0, int pram1)l
extern _native int GET_LINKED_ANIM_TARGET(int pram0)l
extern _native int UNK_0x19F62133()l
extern _native int UNK_0x586714AE(int pram0)l
extern _native int UNK_0xB573FF63(int pram0)l
extern _native void SET_PROP_HEALTH(int pram0, int pram1)l
extern _native int UNK_0xFC718FC5(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void GRINGO_SET_TARGET_OBJECT(int pram0, int pram1, int pram2)l
extern _native int UNK_0xB78BC233(int pram0, int pram1, int pram2)l
extern _native void ADD_CAMERATRANSITION_EVENT_CUTGAMECAMERABEHINDPLAYER(int pram0, int pram1, int pram2)l
extern _native bool CAMERA_PROBE(vector3* Result, vector3 Source, vector3 Target, Actor Owner, int Flag)l
extern _native void UNK_0x8B011F5D()l
extern _native void UNK_0xA8226DFF(int pram0)l
extern _native void UNK_0x831FC466(int pram0)l
extern _native void UNK_0xCC9E6F4C(int pram0, int pram1, int pram2, int pram3)l
extern _native void ADD_PERSISTENT_SCRIPT(int pram0)l
extern _native void REMOVE_PERSISTENT_SCRIPT(int pram0)l
extern _native int IS_GAME_PAUSED()l
extern _native32(0xBC58F1EA) IterationSet _GET_ITERATION_SET(int SetId)l
extern _native int UI_GET_SELECTED_INDEX(const char* MenuID, bool UNK0)l
extern _native void UI_TRANSITION_TO(int pram0)l
extern _native void UNK_0x7BD7A465(int pram0, int pram1)l
extern _native int UNK_0xFD91BE0D(int pram0)l
extern _native void UNK_0xCF674E31(int pram0, int pram1)l
extern _native void SET_PLAYER_COMBATMODE(int pram0)l
extern _native void UI_GOTO(int pram0)l
extern _native void UNK_0x5F66B23E(int pram0, int pram1)l
extern _native void SET_PERS_CHAR_ALLOW_SPAWN_ELSEWHERE(int pram0, int pram1)l
extern _native void UNK_0x7614AEBA(int pram0, int pram1)l
extern _native int UNK_0xD036DF91()l
extern _native void UNK_0x69FC319E()l
extern _native int HAS_SOUND_FINISHED(int pram0)l
extern _native void UNK_0x5B05E3E0(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void MAKE_BIRD_FLY_FROM_POINT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void SQUAD_BATTLE_ALLIES_SET_FORMATION_DENSITY(int pram0, int pram1, int pram2)l
extern _native int PLAY_SIMPLE_PROP_ANIMATION(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0xA607D290()l
extern _native void SET_INDICATOR_DRAW(int pram0, int pram1)l
extern _native void UNK_0x3375FB38(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0xE7A0A109(int pram0)l
extern _native void UNK_0x0073024E(int pram0)l
extern _native void UNK_0x82C54B8A(int pram0, int pram1)l
extern _native void UNK_0x92CC441F(int pram0, int pram1)l
extern _native void SNAPSHOT_GLOBALS()l
extern _native void UNK_0xFB227D11(int pram0)l
extern _native void UNK_0x85D62384()l
extern _native int UNK_0x8DF144C2(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x17CF885F(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x20CE8AA8(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0x6D59A25F(int pram0, int pram1)l
extern _native void UNK_0x8E867DDD(int pram0)l
extern _native void UNK_0x6E79F939(int pram0, int pram1)l
extern _native void UNK_0xE8637D2B(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0x3E647734(int pram0, int pram1, int pram2)l
extern _native void UNK_0xE0553D6B(int pram0, int pram1)l
extern _native void UNK_0xD68E04BB(int pram0, int pram1)l
extern _native void UNK_0x638EAF70(int pram0, int pram1)l
extern _native void UNK_0xEA975A79(int pram0, int pram1)l
extern _native void UNK_0x6BB42C21(int pram0)l
extern _native void UNK_0x0E634931(int pram0)l
extern _native void UNK_0x567712E5(int pram0)l
extern _native void UNK_0xB888B369(int pram0)l
extern _native void UNK_0x306D9FEE(int pram0)l
extern _native void UNK_0xC3614E0A(int pram0)l
extern _native void UNK_0xF962F2B8(int pram0)l
extern _native void UNK_0x22D0DF9B(int pram0)l
extern _native void UNK_0xA234C5D0(int pram0)l
extern _native void UNK_0x733BA9F5(int pram0)l
extern _native void UNK_0x79351E54(int pram0)l
extern _native void UNK_0xCCBE7F0F(int pram0)l
extern _native void UNK_0x5FCF3B85(int pram0)l
extern _native void UNK_0xF07F5E41(int pram0)l
extern _native void UNK_0xCB139D15(int pram0)l
extern _native void UNK_0x886E06C2(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void UNK_0xB6839756()l
extern _native void UNK_0x6D0B8619(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x807B9519(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xCBA75200(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x0A23A69C()l
extern _native void UNK_0x01C7193C(int pram0, int pram1)l
extern _native void UNK_0xE0DF7B3B(int pram0, int pram1, int pram2)l
extern _native void UNK_0x2AD5D078(int pram0, int pram1, int pram2)l
extern _native void UNK_0xF82711CC(int pram0, int pram1, int pram2)l
extern _native void UNK_0x92FE3677(int pram0, int pram1, int pram2)l
extern _native void UNK_0xA72B6620(int pram0, int pram1, int pram2)l
extern _native void UNK_0xBAC27559(int pram0, int pram1, int pram2)l
extern _native void SS_INIT(int pram0)l
extern _native int SS_SET_TABLE_SIZE(int pram0, int pram1)l
extern _native void COMBAT_CLASS_NAME_REGISTER_INT(int pram0, int pram1)l
extern _native void UNK_0x0B396DFF(int pram0)l
extern _native void UNK_0x24F3A0DB(int pram0)l
extern _native void UNK_0x9FEFA743(int pram0)l
extern _native void AI_SPEECH_REGISTER_EVENT(int pram0, int pram1)l
extern _native void AI_SPEECH_REGISTER_TAGS_BEGIN(int pram0)l
extern _native void AI_SPEECH_REGISTER_TAG(int pram0, int pram1, int pram2, int pram3)l
extern _native void AI_SPEECH_REGISTER_TAGS_END()l
extern _native int UNK_0xE77F61B2(int pram0, int pram1)l
extern _native int AI_SPEECH_ADD_PHRASE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void AI_SPEECH_ADD_TAG_FOR_PHRASE(int pram0, int pram1, int pram2)l
extern _native void DEBUG_PLAYER_LOG(int pram0)l
extern _native void UNK_0x9953D4FC(int pram0)l
extern _native void UNK_0x751809BB(int pram0)l
extern _native void UNK_0x25A42C69(int pram0)l
extern _native void UNK_0x86CB8CFB(int pram0)l
extern _native void UNK_0xD6AD0016(int pram0)l
extern _native void UNK_0x8C00C0BE(int pram0)l
extern _native void UNK_0x7CC67B30(int pram0)l
extern _native void UNK_0xD4ECD97D(int pram0)l
extern _native void UNK_0x826BB889(int pram0)l
extern _native void UNK_0x5473B93A(int pram0)l
extern _native void UNK_0x1B1EFCCB(int pram0)l
extern _native void UNK_0xD85BAFA8(int pram0)l
extern _native void UNK_0xEB99D1A9(int pram0, int pram1, int pram2)l
extern _native void UNK_0x3C6FE75D(int pram0, int pram1)l
extern _native void UNK_0x7DA34015(int pram0, int pram1)l
extern _native void UNK_0x79EFDF7E(int pram0, int pram1)l
extern _native void UNK_0xCA669478(int pram0, int pram1)l
extern _native void UNK_0x74E7F898(int pram0, int pram1)l
extern _native void GET_LOCKON_MISSION(int pram0, int pram1)l
extern _native void UNK_0xFCD2DE48(int pram0)l
extern _native void UNK_0xB8F1D736(int pram0)l
extern _native void UNK_0x30402375(int pram0)l
extern _native void UNK_0x7922F870(int pram0)l
extern _native void UNK_0x663723A0(int pram0)l
extern _native void UNK_0x93CFB180(int pram0)l
extern _native void UNK_0xA1FCBA24(int pram0)l
extern _native void UNK_0x7ED8B78C()l
extern _native void UNK_0xD4871BDB(int pram0)l
extern _native void UNK_0xA88359B9(int pram0, int pram1)l
extern _native void UNK_0xC65F6751(int pram0)l
extern _native void UNK_0x83CBD612(int pram0)l
extern _native void UNK_0x4AD2BC30(int pram0)l
extern _native void UNK_0xA13D379B(int pram0, int pram1)l
extern _native void UNK_0xC4C59CA4(int pram0)l
extern _native void UNK_0xA915DC46(int pram0)l
extern _native void UNK_0xBAD8B9A8(int pram0)l
extern _native void UNK_0x6CBF76AB(int pram0)l
extern _native void UNK_0x4F64116B(int pram0)l
extern _native void UNK_0x0386C556(int pram0, int pram1, int pram2)l
extern _native void UNK_0xE0DD373F(int pram0)l
extern _native void UNK_0xF63FA0A1(int pram0)l
extern _native void UNK_0x375BBD85(int pram0)l
extern _native void UNK_0x4819FB7C(int pram0)l
extern _native void UNK_0xC4F468AA(int pram0)l
extern _native void GAME_ESTIMATE_MOUNT(int pram0)l
extern _native void UNK_0xD6BBC8AA(int pram0)l
extern _native void UNK_0x354DDFED(int pram0, int pram1)l
extern _native void UNK_0x230AB95E(int pram0)l
extern _native void ADD_TO_ZONE_ALLOWED_GRINGO_TYPE_LIST(int pram0, int pram1)l
extern _native void UNK_0xC43C4D76(int pram0, int pram1)l
extern _native void UNK_0xFCA83D15(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9189EB8B(int pram0)l
extern _native int UNK_0x00CDD849(int pram0)l
extern _native int UNK_0x6138B1B8(int pram0)l
extern _native void REMOVE_GLOW_INDICATOR(int pram0)l
extern _native int IS_VOLUME_ENABLED(int pram0)l
extern _native int COUNT_FLAMES_IN_VOLUME(int pram0)l
extern _native int UNK_0x3B32AB84(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x3E30A514(int pram0, int pram1)l
extern _native int SET_PANIM_PARAMS(int pram0, int pram1, int pram2)l
extern _native int GET_CURRENT_DUEL_SCORE(int pram0)l
extern _native int UNK_0x26011C78(int pram0)l
extern _native int HAS_ACCESSORY_ENUM(int pram0, int pram1)l
extern _native void UNK_0xD021B37F(int pram0)l
extern _native void UNK_0x94A24A5C(int pram0)l
extern _native int BEGIN_DUEL(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12)l
extern _native int UNK_0x7FDDF876(int pram0, int pram1)l
extern _native int ADD_DUEL_HOSTAGE(int pram0, int pram1)l
extern _native void SET_EMOTION(int pram0, int pram1, int pram2)l
extern _native int SET_DUEL_DIFFICULTY(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xADCC16A2()l
extern _native int REMOVE_EVENT_RESPONSE(int pram0, int pram1, int pram2)l
extern _native void CLEAR_PLAYER_BLOOD()l
extern _native void UNK_0x9D9E093E(int pram0)l
extern _native void UNK_0x338DF299()l
extern _native int IS_ACTOR_ANIM_PHASE_LOCKED(int pram0)l
extern _native void RELEASE_ACTOR_ANIM_PHASE_LOCK(int pram0)l
extern _native void UNK_0xDE7C65CE()l
extern _native void UNK_0x32F2D6F1(int pram0)l
extern _native void HUD_TIMER_PAUSE()l
extern _native void UNK_0x7784BB85()l
extern _native int UNK_0xD3A523FD(int pram0)l
extern _native void SET_ACTOR_ANIM_PHASE_LOCK(int pram0, int pram1)l
extern _native void UNK_0x24AE7AFB()l
extern _native int UNK_0xA091179F(int pram0, int pram1)l
extern _native void UNK_0x0CCE435E(int pram0, int pram1, int pram2)l
extern _native void UNK_0x87A2C1D5(int pram0)l
extern _native void AI_RESET_NAV_SUBGRID_CELL_SIZE(int pram0)l
extern _native int UNK_0x544BCE48(int pram0, int pram1)l
extern _native void UNK_0x4D629653(int pram0, int pram1, int pram2)l
extern _native int UNK_0x9B083FD2()l
extern _native int GET_PHYSINST_VELOCITY(int pram0, int pram1)l
extern _native float SQRT(float pram0)l
extern _native int GET_ACTOR_UPDATE_PRIORITY(int pram0)l
extern _native void HUD_COUNTER_SET(int pram0)l
extern _native int EXP(int pram0)l
extern _native int UNK_0xD058BD70()l
extern _native int UNK_0x4C48EA4D()l
extern _native int UNK_0x35CDFDC5(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x8A2A1A51(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x581CAC89()l
extern _native int UNK_0x79AFAB1F(int pram0, int pram1)l
extern _native int GUI_MAKE_OVERLAY(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int UNK_0xD019FF37(int pram0)l
extern _native int UNK_0xA7FF2899(int pram0, int pram1, int pram2)l
extern _native GUIWindow GUI_MAIN_WINDOW()l
extern _native void UNK_0x72168160(int pram0)l
extern _native int GET_MOST_RECENT_RIDER(int pram0)l
extern _native void UNK_0x8DEC3E03(int pram0)l
extern _native int UNK_0x14708CB1()l
extern _native void UNK_0x7A99E7DE()l
extern _native void UNK_0x1D5E39A0()l
extern _native int GRINGO_QUERY_FLOAT(int pram0, int pram1, int pram2, int pram3)l
extern _native int IS_ACTOR_INITED(int pram0)l
extern _native void UNK_0xA870B28E(int pram0, int pram1)l
extern _native int UNK_0x9DDB29B1(int pram0)l
extern _native int UNK_0x24A1B923()l
extern _native int DECOR_REMOVE_ALL(int pram0)l
extern _native void UNK_0x713B1D7F(int pram0, int pram1)l
extern _native int UNK_0x34F03EC7(int pram0, int pram1, int pram2)l
extern _native void UNK_0x573BEF3B(int pram0, int pram1)l
extern _native void UI_SET_TEXT_HASH(int pram0, int pram1)l
extern _native void UNK_0x50C18480(int pram0, int pram1)l
extern _native int UNK_0x6A0A241A(int pram0)l
extern _native int NET_GET_NAT_TYPE()l
extern _native int UNK_0xC1A30BB5()l
extern _native void UNK_0x2C4CBC25(int pram0)l
extern _native int UNK_0xF2140DEE(int pram0)l
extern _native void UNK_0xBECB3EEC(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x98A5CDC5(int pram0)l
extern _native int UNK_0x8808546E()l
extern _native int UNK_0x1A47001B()l
extern _native int UNK_0x0FF6B8F4()l
extern _native int NET_SESSION_LEAVE_SESSION()l
extern _native void UNK_0xCE8F6304(int pram0)l
extern _native void UNK_0x41921C98(int pram0)l
extern _native void UNK_0xAB32D5D9(int pram0)l
extern _native int UNK_0x75F27D60(int pram0)l
extern _native int UNK_0x6A7B9FAD(int pram0)l
extern _native int UNK_0x106CE441(int pram0)l
extern _native void UNK_0xA64A451E(int pram0, int pram1)l
extern _native int UNK_0xB514ECA7(int pram0, int pram1)l
extern _native int GET_ACTOR_COMBAT_CLASS(int pram0)l
extern _native void SET_VEHICLE_PASSENGERS_ALLOWED(int pram0, int pram1)l
extern _native void SQUADS_MERGE(int pram0, int pram1)l
extern _native void UNK_0x91BB8548(int pram0, int pram1)l
extern _native void SET_VOLUME_PARAMS(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int UNK_0x15D6F3C7(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x746897AB(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x0B24362F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int GET_PLAYER_CONTROL_CONFIG(int pram0)l
extern _native void UNK_0x72B03551()l
extern _native void UNK_0xE5FE0A6A(int pram0)l
extern _native void UNK_0x08D84437(int pram0)l
extern _native void UNK_0xAFFBBE78(int pram0)l
extern _native void UNK_0xF34B8448(int pram0)l
extern _native void UNK_0x796E66E7(int pram0)l
extern _native void UNK_0x784F04DD(int pram0)l
extern _native void UNK_0x3248D20E(int pram0)l
extern _native void UNK_0xBC46E3E1(int pram0, int pram1, int pram2)l
extern _native void UNK_0x2634F265(int pram0, int pram1)l
extern _native void UNK_0xA0A5FF80(int pram0, int pram1)l
extern _native int UNK_0x52C10147(int pram0)l
extern _native void UNK_0x90008899(int pram0)l
extern _native int NET_GET_AREA_OVERLOAD_STATE_FOR_SLOT(int pram0)l
extern _native int NET_IS_BUSY()l
extern _native int UNK_0x63034F52(int pram0)l
extern _native int UNK_0x2037A74F(int pram0)l
extern _native int UNK_0x89D8FC30()l
extern _native int UNK_0xE9EAC45C(int pram0)l
extern _native int UNK_0xBDF22FCA(int pram0)l
extern _native int UNK_0xA174152C(int pram0)l
extern _native int UNK_0x0183A3F0(int pram0)l
extern _native int UNK_0xF6E40FF3(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int NET_IS_FACTION_SAFE(int pram0)l
extern _native void UNK_0x9EA132A3(int pram0)l
extern _native int GUI_MAKE_WINDOW(GUIWindow Parent, int pram1, const char* WindowName, const char* pram3)l
extern _native int UNK_0x9180FF1C(int pram0)l
extern _native void UNK_0x2F7B457B(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xC0849D70()l
extern _native int UNK_0x8DF05A4F(int pram0)l
extern _native void UNK_0x651F6299(int pram0)l
extern _native int UNK_0x4A721118(int pram0)l
extern _native int UNK_0x4500B98A(int pram0)l
extern _native int GET_WEAPON_GOLD(Actor Actor, Weapon Weapon)l
extern _native int UNK_0x3AE1062C()l
extern _native32(0xC666B987) bool _IS_ACTOR_AMMO_INFINITE(Actor Actor, int pram1)l
extern _native void READY_ITEM(const char* ItemName, Actor Actor)l
extern _native int UNK_0x0B2D5E4B()l
extern _native int UNK_0x2010ABE6()l
extern _native int UNK_0xFA0E1F8B(int pram0)l
extern _native void UNK_0xCB0BCAE2(int pram0)l
extern _native void DISABLE_PLAYER_GRINGO_USE(int pram0, int pram1)l
extern _native int UNK_0x3A5C56E3(int pram0)l
extern _native void UNK_0xCC7D0431(int pram0)l
extern _native void UNK_0xF7B747CA()l
extern _native void UNK_0x1184EC7B(int pram0)l
extern _native int UNK_0x81FD9851()l
extern _native void UNK_0x120E6123(int pram0)l
extern _native int UNK_0x86FF3A9B()l
extern _native int UNK_0xDC88B308()l
extern _native int UNK_0xF5B7B208()l
extern _native int UNK_0xBD269877(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0x43C5F320()l
extern _native void UNK_0xAD85A378()l
extern _native void SET_CAMERA_FOCUS_OBJECT(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UNK_0xEB214384(int pram0)l
extern _native int GET_SLOT_FACING(int pram0, int pram1)l
extern _native void UNK_0x6E303287(int pram0, int pram1)l
extern _native32(0xB1A2028A) void _UI_ENTER_EXCLUSIVE(char* scaleformLayer)l
extern _native void BURN_ACTOR(int pram0, int pram1, int pram2)l
extern _native int GRINGO_STAY_ACTIVE(int pram0, int pram1)l
extern _native int UNK_0xD8218A5B()l
extern _native int UNK_0x74EE96B8(int pram0)l
extern _native int UNK_0x2374C1E0()l
extern _native void TRAIN_DESTROY_CAR(int pram0, int pram1)l
extern _native int TRAIN_GET_NEAREST_POI_DISTANCE(int pram0)l
extern _native void UNK_0x90DD37E7(int pram0, int pram1, int pram2)l
extern _native int AI_GLOBAL_GET_PERMANENT_DANGER(int pram0)l
extern _native void DESTROY_CRIME(int pram0)l
extern _native int UNK_0x72A048B7(int pram0)l
extern _native int GET_CRIME_FACTION(int pram0)l
extern _native int UNK_0x67F224B4(int pram0)l
extern _native int AI_SELF_DEFENSE_GET_ATTACKED_PLAYER_FIRST(int pram0)l
extern _native int GET_LAST_DAMAGE(int pram0)l
extern _native int GET_JOURNAL_ENTRY_PROGRESS(int pram0)l
extern _native int UNK_0x91396EB7(int pram0)l
extern _native int FIRE_GET_OWNER(int pram0)l
extern _native void UNK_0x40C2576F(int pram0, int pram1)l
extern _native void UNK_0xDF3DF05A(int pram0)l
extern _native int AUDIO_IS_SCRIPTED_MUSIC_PLAYING()l
extern _native int GET_ACTOR_WEAPON_REACTION_ACTOR_TYPE(int pram0)l
extern _native int UNK_0xD19EFFC1(int pram0, int pram1)l
extern _native void HUD_STAMINA_OVERRIDE(int pram0, int pram1, int pram2)l
extern _native int UNK_0x6F513950(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int GET_CAMERA_SHOT_TRANSITION(int pram0)l
extern _native void SET_FIXED_TRANSITION_T(int pram0, int pram1)l
extern _native void ANIMAL_ACTOR_SET_DOCILE(Actor Actor, bool Docile)l
extern _native void GET_CAMERA_UP_VECTOR(int pram0, int pram1)l
extern _native int CUTSCENEOBJECT_ADD_TRANSITION_FIXED(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void UNK_0xCA99D3B4()l
extern _native int SC_CHALLENGE_GET_VAR_BOOL(int pram0, int pram1)l
extern _native int SC_CHALLENGE_GET_VAR_FLOAT(int pram0, int pram1)l
extern _native void UI_CHALLENGE_CREATE(int pram0, int pram1, int pram2)l
extern _native void UI_CHALLENGE_SET_PROGRESS(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int SC_CHALLENGE_GET_EXPIRATION_STATE(int pram0)l
extern _native void SC_CHALLENGE_PROCESS_EXPIRATION(int pram0)l
extern _native void SC_CHALLENGE_RELEASE(int pram0)l
extern _native int SC_CHALLENGE_GET_LEADERBOARD_ID(int pram0, int pram1)l
extern _native void SC_CHALLENGE_CLEAN_UP(int pram0)l
extern _native void UNK_0x9D9CDCE3(int pram0, int pram1)l
extern _native void UNK_0xD5ED5FCB(int pram0, int pram1)l
extern _native void SC_CHALLENGE_RESET_EXPIRATION_STATE(int pram0)l
extern _native int SC_CHALLENGE_IS_ACTIVE(int pram0)l
extern _native int SC_CHALLENGE_IS_RUNNING(int pram0)l
extern _native int UNK_0xBBF4F7E4()l
extern _native int UNK_0xAFD53217(int pram0, int pram1, int pram2)l
extern _native int UNK_0xB555A648(int pram0, int pram1, int pram2)l
extern _native int GET_GRINGO_INT_ATTR(int pram0, int pram1, int pram2)l
extern _native int SET_GRINGO_INT_ATTR(int pram0, int pram1, int pram2)l
extern _native int GRINGO_GET_COMPONENT_HASH(int pram0)l
extern _native int UNK_0xC15C3361(int pram0, int pram1)l
extern _native int UNK_0xA766EA5C(int pram0, int pram1)l
extern _native int IS_PROP_STREAMED_IN(int pram0)l
extern _native void GRAVE_SET_DUG_UP(int pram0, int pram1)l
extern _native int GET_GRAVE_FROM_OBJECT(int pram0)l
extern _native int UNK_0x04507DBC(int pram0, int pram1)l
extern _native int UNK_0x88F7432C(int pram0, int pram1)l
extern _native int GET_ACTOR_ANIM_CURRENT_TIME(int pram0, int pram1)l
extern _native int SET_PROP_VELOCITY_ON_AXIS(int pram0, int pram1, int pram2)l
extern _native int UNK_0x3736FF43(int pram0)l
extern _native void UNK_0xF95DDBF2(int pram0, int pram1)l
extern _native void UNK_0x6BA667B5(int pram0)l
extern _native int UNK_0xB8C419C3(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int IS_ACTOR_ANIM_PLAYING(int pram0, int pram1)l
extern _native int UNK_0x08D76BB0(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xA2DEC153(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int IS_VEHICLE_ENGINE_RUNNING(int pram0)l
extern _native void SET_VEHICLE_ENGINE_RUNNING(Actor Vehicle, bool Running)l
extern _native int UNK_0x6517FF1B(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int GRINGO_IS_ACTIVE(int pram0)l
extern _native void DESTROY_ZONE(int pram0)l
extern _native int UNK_0x7E4681E8(int pram0, int pram1, int pram2)l
extern _native int GRINGO_ACTOR_FACE(int pram0, int pram1, int pram2)l
extern _native int UNK_0x217B4264(int pram0, int pram1, int pram2)l
extern _native int UNK_0x3DEA631B(int pram0, int pram1)l
extern _native void PUSH_MINIGAME_INPUT(int pram0, int pram1)l
extern _native void UNK_0x8275FDD4(int pram0)l
extern _native int UNK_0x6AAD0420(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0x655D350B(int pram0, int pram1, int pram2, int pram3)l
extern _native int SET_OBJECT_ANIMATOR_RATE(int pram0, int pram1)l
extern _native int SET_OBJECT_ANIMATOR_PHASE(int pram0, int pram1)l
extern _native int IS_MINIGAME_RUNNING()l
extern _native int HAS_PROP_BEEN_DAMAGED(int pram0)l
extern _native int CREATE_OBJECT_ANIMATOR(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x188B6431(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xB57D4110(int pram0, int pram1, int pram2)l
extern _native int UNK_0x97951004(int pram0)l
extern _native int UNK_0x325F7E50(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void UNK_0x507BBD3A(int pram0, int pram1)l
extern _native void UNK_0xC93116B1()l
extern _native int UNK_0xEB33480A(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int UNK_0xA9E00433(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void AI_SET_DISARMED(int pram0, int pram1)l
extern _native void LASSO_EVENT(int pram0, int pram1)l
extern _native void UNK_0x96161235(int pram0)l
extern _native int UNK_0x1AA3A0C0(int pram0, int pram1)l
extern _native void AI_GLOBAL_REPORT_DANGER(int pram0)l
extern _native int UNK_0x6689F85C(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xEC28CA8E(int pram0, int pram1, int pram2)l
extern _native int UNK_0xA332ACE3(int pram0, int pram1)l
extern _native void UNK_0x3184B507()l
extern _native void UNK_0x489B3078()l
extern _native void AUDIO_PLAY_PAIN(int pram0, int pram1)l
extern _native int GRINGO_ACTOR_MOVE_TO(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0xC5205015(int pram0)l
extern _native int UNK_0xADBF3ADF(int pram0)l
extern _native void UNK_0x38636EBF(int pram0, int pram1)l
extern _native int UNK_0x869D5D92(int pram0, int pram1, int pram2)l
extern _native int IS_HOGTIE_CUTFREE_OBSTRUCTED(int pram0, int pram1)l
extern _native void CLEAR_HOGTIE_ATTACH_VICTIM(int pram0)l
extern _native int UNK_0x60D10483(int pram0, int pram1)l
extern _native void SET_HOGTIE_ATTACH_VICTIM(int pram0, int pram1)l
extern _native int GET_FACTION_STATUS_TO_INDIVIDUAL_ACTOR(int pram0, int pram1)l
extern _native int UNK_0xBCED635B(int pram0)l
extern _native int UNK_0x9634D42E(int pram0, int pram1)l
extern _native int GET_ACTOR_POSTURE(int pram0)l
extern _native void SET_PLAYER_DISABLE_TARGETING(int pram0, int pram1)l
extern _native void UNK_0x6E86FCB5(int pram0, int pram1, int pram2)l
extern _native void UNK_0x7BCE4845(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native void UNK_0xD1C91A7F(int pram0, int pram1, int pram2, int pram3)l
extern _native void TRAIN_GET_POSITION(int pram0, int pram1)l
extern _native int UNK_0x90B514B9(int pram0, int pram1, int pram2)l
extern _native void GRINGO_UNLOAD_ANIMATION(int pram0)l
extern _native void GRINGO_LOAD_ANIMATION(int pram0)l
extern _native void CAMERASHOT_ADD_LOOKSTICK_ROTATION_BEHAVIOR(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int UNK_0xE782EB20(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native void UNK_0x660DBDDD(int pram0)l
extern _native int GRINGO_QUERY_INT(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xDEE6523D(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x466C02BA(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xE9C74577(int pram0)l
extern _native int UNK_0xF573B7DE(int pram0, int pram1)l
extern _native int GET_GRINGO_STRUCT_ATTR(int pram0, int pram1, int pram2, int pram3)l
extern _native int DEACTIVATE_ACTOR_FOR_PERS_CHAR(int pram0)l
extern _native void TASK_WANDER_IN_BOX(int pram0, int pram1, int pram2, int pram3)l
extern _native void TASK_GUARD_PATROL_PATH(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int GRINGO_QUERY_STRING(int pram0, int pram1, int pram2, int pram3)l
extern _native int UNK_0xF0991C9F(int pram0, int pram1)l
extern _native int UNK_0x257C73C5(int pram0)l
extern _native int GET_ACTOR_HEIGHT(int pram0)l
extern _native int UNK_0xE9612679(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x67258116(int pram0, int pram1)l
extern _native void SET_ACTOR_IS_SHOPKEEPER(int pram0, int pram1, int pram2)l
extern _native int WAS_AI_ACTOR_PLAYER_WEAPON_THREATENED_BY(int pram0, int pram1, int pram2)l
extern _native int AI_HAS_ACTOR_THREATENED_RECENTLY(int pram0)l
extern _native void UNK_0x0B9AE52F(int pram0)l
extern _native void UNK_0x5F4C08A2(int pram0)l
extern _native void DOF_POP()l
extern _native void UNK_0x3601E3E2(int pram0)l
extern _native int UNK_0x5A12BB48()l
extern _native void UNK_0xB84DE662(int pram0)l
extern _native void SHOP_REFRESH(int pram0)l
extern _native int UNK_0x42CBA241(int pram0)l
extern _native int UNK_0x1BF8FD6D(int pram0)l
extern _native int UNK_0x94D8F49E(int pram0)l
extern _native void UNK_0xB75FAD6A(int pram0)l
extern _native int UNK_0xFAF37414(int pram0)l
extern _native void UNK_0xA40EFFFF(int pram0, int pram1)l
extern _native int SS_GET_STRING_ID(int pram0, int pram1)l
extern _native int UNK_0xB954DE78(int pram0)l
extern _native void UNK_0x777CF9FA(int pram0, int pram1)l
extern _native void UNK_0x7A34C33D(int pram0, int pram1)l
extern _native void SHOP_CLEAR()l
extern _native int UNK_0x2FCD8CCA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void DOF_PUSH()l
extern _native int GET_CAMERASHOT_FAR_CLIP_PLANE(int pram0)l
extern _native void DOF_SET(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0x47A8DDED(int pram0)l
extern _native int STRINGTABLE_LENGTH(int pram0)l
extern _native int TRAIN_IS_VALID(int pram0)l
extern _native void TASK_FAILURE_MODE_SET(int pram0, int pram1)l
extern _native int HORSE_GET_CURR_FRESHNESS(int pram0)l
extern _native int GET_ACTOR_MAX_FRESHNESS(int pram0)l
extern _native void UNK_0x9603D3B2(int pram0, int pram1)l
extern _native int UNK_0x00EF33EF()l
extern _native int GET_CAMERA_FOV(int pram0)l
extern _native void UPDATE_AIMRAMP(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int UNK_0x9BD37A3D(int pram0)l
extern _native int UNK_0xDA50B18B(int pram0, int pram1)l
extern _native int UNK_0x4062688A(int pram0)l
extern _native int UNK_0xE13B49BD(int pram0)l
extern _native void UNK_0x4486E8C7()l
extern _native int UNK_0x55E6227E(int pram0, int pram1)l
extern _native void UNK_0x02DB5C93(int pram0, int pram1, int pram2)l
extern _native void UNK_0x8DD4BC60(int pram0)l
extern _native void UNK_0xD5501B1B(int pram0, int pram1)l
extern _native void UNK_0x1CB7C07D(int pram0)l
extern _native void UNK_0x4C3F3C71(int pram0)l
extern _native void UNK_0xAF7D851C()l
extern _native int UNK_0x95132289()l
extern _native void UNK_0x18D7E687(int pram0, int pram1, int pram2, int pram3)l
extern _native void UNK_0xC3BE5695()l
extern _native void UNK_0xF38E8BBE()l
extern _native void UNK_0xBD829B6B()l
extern _native void UNK_0x7306CC72(int pram0)l
extern _native void UNK_0x9631DFD0(int pram0, int pram1, int pram2)l
extern _native void UNK_0x3BED7D9F()l
extern _native void UNK_0xEB8325B3(int pram0)l
extern _native void UNK_0x77C8F279(int pram0)l
extern _native void UNK_0x868E29C1(int pram0, int pram1)l
extern _native void UNK_0xCEED74A5()l
extern _native void UNK_0xE74C4851()l
extern _native void SET_CAMERASHOT_CONTROL_SEQUENCE_VEC3(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void UNK_0x382C47C5(int pram0)l
extern _native int GET_TASK_NEXT_POINT_ON_PATH(int pram0, int pram1)l
extern _native int SET_CUTSCENEINPUTS_TARGET_GUID(int pram0, int pram1, int pram2)l
extern _native int UNK_0x8701F1F6()l
extern _native int UNK_0xB5401D4A()l
extern _native int UNK_0x80B30545()l
extern _native bool GET_LAST_HIT_ZONE(Actor Actor, int* out)l
extern _native const char* GET_WEAPON_DISPLAY_NAME(eWeapon WeaponID)l
extern _native Blip GET_BLIP_ON_OBJECT(Object Obj)l


/******************** Undocumented Natives ********************
ACTOR_HAS_ANIM_LOADED
ACTOR_IS_HIDDEN_BY_CUTSCENE
ACTOR_SET_MAX_GAIT
ADD_ACCESSORY
ADD_CAMERA_SHOT_TRANSITION_EASE_OUT
ADD_CAMERA_SHOT_TRANSITION_HOLD
AI_ACTION_IS_ACTIVE
AI_AVOID_CLEAR_IGNORE_ACTOR
AI_DONT_SLOW_DOWN_TO_WALK_FOR_TURNS
AI_GOAL_AIM_AT_COORD
AI_GOAL_SHOOT_AT_OBJECT
AI_GOAL_STAND_AT_COORD
AI_GOAL_STAND_CLEAR
AI_HAS_PLAYER_FIRED_GUN_WITHIN
AI_RESET_NAV_ACTOR_WIDTH
AI_RIDING_SET_ATTRIBUTE
AI_SET_ENABLE_REACTION_VO
AI_SET_IGNORE_OPEN_AREA_MATERIAL
AI_SET_NAV_ALLOW_TWEAK_DESIRED_MOVEMENT
AI_SET_NAV_MAX_SLOPE
AI_SHOOT_TARGET_CLEAR_OFFSET
AI_SHOOT_TARGET_SET_OFFSET
ANIMAL_ACTOR_GET_DOCILE
ANIMAL_SPECIES_ADD_EXTERNAL_PATH_ATTRACTION
ANIMAL_SPECIES_REMOVE_EXTERNAL_PATH_ATTRACTION
APPEND_JOURNAL_NOTE
CLEAR_ACTOR_PROOF_ALL
CLEAR_PLAYER_CONTROL_HORSE_FOLLOW
COMBAT_CLASS_AI_GET_ATTRIB_BOOL
COMBAT_CLASS_AI_SET_FIGHT_TIME_BETWEEN_ATTACKS_MULTIPLIER
CREATE_CORPSE_VARIATION_IN_LAYOUT
DETACH_DRAFT_FROM_VEHICLE_BY_ACTOR
ESTIMATE_DISTANCE_ALONG_PATH
ESTIMATE_PATH_LENGTH
GATEWAY_IS_DISABLED
GET_ACTOR_MAX_SPEED
GET_ACTOR_MIN_SPEED
GET_ACTOR_VISION_FIELD_OF_VIEW
GET_ALLOW_RIDE
GET_ALLOW_RIDE_BY_PLAYER
GET_DRAW_OBJECT
GET_MAX_SPEED
GET_PROP_HEALTH
GRAVE_IS_DUG_UP
GRINGO_FORCE_UPDATE
GRINGO_SET_MONEY_PRESENCE
HORSE_AUTO_JUMP_ENABLED_FOR_AI_RIDERS
HORSE_ENABLE_AUTO_JUMP_FOR_AI_RIDERS
IS_ACTOR_ON_PATH
IS_CAMERA_FOCUS_PROMPT_ENABLED
IS_PLAYER_IN_HORSE_FOLLOW
IS_PLAYER_TARGETTING_OBJECT
ITERATE_IN_AREA
MEMORY_ALLOW_PICKUP_WEAPONS
PAUSE_SCRIPTED_CONVERSATION
REMOVE_HORSE_ACCESSORY
RESTART_SCRIPTED_CONVERSATION
SET_ACTOR_FROZEN_AFTER_CORPSIFY
SET_ACTOR_MIN_SPEED_ABSOLUTE
SET_ACTOR_MOVABLE_NAV_MESH
SET_ACTOR_OBSERVED_TARGETED_REACTIONS
SET_ACTOR_PERMANENT
SET_ALLOW_LASSO_MINI_GAME
SET_ALLOW_MELEE_SPECIAL_MOVE
SET_ALLOW_RIDE
SET_PLAYER_ALLOW_PICKUP
SET_PLAYER_CAUSE_WEAPON_REACTIONS
SET_PLAYER_MELEE_MODE_SELECTED
SET_PLAYER_VEHICLE_INPUT
SET_TIME_WARP
SQUAD_BATTLE_ALLIES_SET_OBJECTIVE
SQUAD_FLOCK_EVENT_BOOST_SET_ENABLED
SQUAD_FLOCK_SET_ALLOW_STRAGGLERS
SQUAD_FLOCK_SET_FLOCKING_PARAMETER
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_BEHAVIOR_FLAG
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_DESIRED_LEADER
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_NONSTOP
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_PATH
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_SPEED
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_SPEED_ABSOLUTE
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_SPEED_NORMALIZED
SQUAD_GOAL_ADD_FLOCK
SQUAD_GOAL_ADD_FOLLOW_PATH_IN_FORMATION
STREAMING_SET_CUSTCENE_MODE
TASK_ACTION_PERFORM_AT_POSITION
TASK_ANIMAL_FOLLOW_AGGRESSIVELY
TASK_ANIMAL_HUNT
TASK_BIRD_FLY_NEAR_COORD
TASK_BIRD_SOAR
TASK_FOLLOW_AND_ATTACK_OBJECT_ALONG_PATH
TASK_FOLLOW_PATH_FROM_POINT
TASK_GO_TO_COORD_USING_MATERIAL
TASK_GUARD_PATROL_AUTO
TASK_JUMP_OVER_OBSTRUCTION
TASK_JUMP_TO_OBJECT
TASK_SHOOT_ENEMIES_FROM_PREFERRED_COVER
TRAIN_SET_SPEED
SET_CORPSE_PERMANENT
SET_RADAR_STREAMING
DESTROY_CAMERA_SHOT
HAS_ACCESSORY
NET_SESSION_GAMER_COUNT
REMOVE_PHYSINST
IS_PROP_BROKEN
IS_USING_TURRET
IS_PHYSINST_ACTIVE
IS_PHYSINST_FROZEN
HUD_TIMER_SET
HUD_TIMER_UNPAUSE
FIND_NAMED_ACTORSET
TRAIN_SET_FX
LEASH_DETATCH_OBJECT
SET_GRINGO_STRUCT_ATTR
UI_DISABLE_INPUT
START_NEW_SCRIPT
WAITUNWARPED
WAITUNPAUSED
GET_TIMESTAMP
TASK_DIVETOWARD
TASK_DIVEAWAYFROM
CANCEL_DUEL
GET_ACTOR_TYPE
TASK_PLAY_ANIM
START_NEW_SCRIPT_WITH_ARGS
SET_CAMERA_TARGETDOF_FOCAL_LENGTH
GET_CAMERASHOT_UP_VECTOR
GET_CAMERASHOT_X_VECTOR
SET_CAMERASHOT_TARGET_OBJECT_BONE
GET_EQUIP_SLOT_ENABLED
CREATE_CORPSE_VARIATION_IN_LAYOUT_RANDOM
SET_ACTOR_REACT_TO_LASSO
TASK_BE_DEAD
TASK_BE_DEAD_RANDOM
TASK_BIRD_LAND
TASK_DOOR_ACTION
TASK_WARN_CHAR
TASK_ACTION_PERFORM_ON_TARGET
TASK_FOLLOW_OBJECT_IN_FORMATION
TASK_LEDGE_ACTION
TASK_SEEK_COVER_FROM_COORD
TASK_SIMPLE_BEHAVIOR
TASK_STEALTH_ATTACK
TASK_TR_ACTION
TASK_TR_ACTION_ON_ACTOR
TASK_USE_GRINGO_GROUP
SQUAD_FLOCK_SET_BOOL_FLOCKING_PARAMETER
SQUAD_FOLLOW_TRAFFIC_CURVE_GET_ALL_BEHAVIOR_FLAGS
SQUAD_FOLLOW_TRAFFIC_CURVE_SET_ALL_BEHAVIOR_FLAGS
SQUAD_FOLLOW_TRAFFIC_CURVE_GET_BEHAVIOR_FLAG
SQUAD_FOLLOW_TRAFFIC_CURVE_SET_SPEED
SQUAD_FOLLOW_TRAFFIC_CURVE_SET_SPEED_ABSOLUTE
SQUAD_FOLLOW_TRAFFIC_CURVE_SET_SPEED_NORMALIZED
SQUAD_FOLLOW_TRAFFIC_CURVE_SET_OFFSET_X
SQUAD_FOLLOW_TRAFFIC_CURVE_SET_DESIRED_LEADER
SQUAD_FOLLOW_TRAFFIC_CURVE_CLEAR_DESIRED_LEADER
SQUAD_FOLLOW_PATH_IN_FORMATION_GET_ALL_BEHAVIOR_FLAGS
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_ALL_BEHAVIOR_FLAGS
SQUAD_FOLLOW_PATH_IN_FORMATION_GET_BEHAVIOR_FLAG
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_TASK_PRIORITY
SQUAD_FOLLOW_PATH_IN_FORMATION_SET_OFFSET_X
SQUAD_FOLLOW_PATH_IN_FORMATION_CLEAR_DESIRED_LEADER
SQUAD_FOLLOW_TRAFFIC_CURVE_SET_CURVE
SQUAD_GOAL_ADD_FOLLOW_OBJECT_IN_FORMATION
AI_GET_NAV_ACTOR_AVOIDANCE_ALLOW_TURNS
AI_GET_NAV_ALLOW_TWEAK_DESIRED_MOVEMENT
AI_SET_NAV_UNALERTED_PREFER_PEDPATH
AI_GOAL_LOOK_AT_PLAYER_WHEN_WITHIN_CLEAR
IS_AI_ACTOR_PERFORMING_TASK
AI_SELF_DEFENSE_GET_PLAYER_ATTACKED_FIRST
AI_SELF_DEFENSE_SET_PLAYER_ATTACKED_FIRST
AI_GET_IGNORE_OPEN_AREA_MATERIAL
AI_WAS_PUSHED_OVER_BY
MEMORY_GET_WEAPON_DRAW_PREFERENCE
MEMORY_SET_UNARMED_RETREAT
SET_PROP_NO_FADE
STREAMING_LOAD_ALL_REQUESTS_NOW
SET_DEADEYE_TIME_LIMIT
SET_WAGON_TO_WAGON_JACK_ENABLE
TOGGLE_COVER_PROP
DETACH_DRAFT_FROM_VEHICLE_BY_INDEX
NET_GET_OVERLOAD_STATE_FOR_SLOT
GET_FACTION_IS_LAWFUL_TO_ATTACK
IS_PHYSINST_HIDE
SET_ACTOR_STAMINA
SET_PHYSINST_HIDE
DEBUG_DRAW_LINE
DEBUG_DRAW_STRING
DEBUG_DRAW_VECTOR
DEBUG_DRAW_SPHERE
FIND_CLOSEST_DOOR
CREATE_NAMED_POPULATION_SET
CREATE_EVENT_TRAP
CREATE_OBJECT_ANIMATOR_ON_OBJECT
CREATE_GATEWAY_TYPE
CREATE_LEASH_OBJECT
CREATE_OBSTACLE_ON_OBJECT
CREATE_FIRE_ON_OBJECT
GRINGO_IS_PROP_READY
IS_ACTOR_ON_LADDER
IS_ACTOR_DRAFT_VEHICLE
IS_ACTOR_HOGTIE_ATTACHED
IS_ACTOR_BEING_DRAGGED
RESET_VEHICLE_BUMP_COUNT
RESET_PROPS_IN_VOLUME
LEASH_DETACH_OBJECT
DECOR_GET_STRING_HASH
IS_OBJECT_ANIMATOR_VALID
IS_OBJECT_ANIMATOR_READY
IS_VEHICLE_ALLOWED_TO_DRIVE
IS_LOCAL_PLAYER_VALID
IS_SCRIPT_USE_CONTEXT_VALID
IS_PERS_CHAR_VALID
IS_DOOR_OPENED
IS_OBJECT_IN_VOLUME
IS_ACTOR_IN_ROOM
SET_ZONE_POPULATION_COUNT
SET_ZONE_POPULATION_DENSITY
GET_OBJECT_FROM_ACTOR
GET_OBJECT_FROM_CRIME
GET_OBJECT_FROM_EVENT
GET_OBJECT_FROM_VOLUME
GET_OBJECT_FROM_GRINGO
GET_OBJECT_FROM_OBJECTSET
GET_OBJECT_FROM_PERS_CHAR
GET_OBJECT_FROM_PHYSINST
GET_OBJECT_FROM_ANIMATOR
GET_OBJECT_FROM_SQUAD
GET_OBJECT_ANIMATOR_ON_OBJECT
GET_OBJECT_ANIMATOR_PHASE
GET_OBJECT_MODEL_NAME
DESTROY_PERS_CHAR
RELEASE_SCRIPT_USE_CONTEXT
ADD_SCRIPT_USE_CONTEXT
GET_ACTOR_FROM_ACTORSET
GET_ACTOR_ENUM_STRING
GET_ACTOR_ENUM_FACTION
GET_ACTOR_DRAFTED_TO
RELEASE_PERS_CHAR
SET_ACTOR_TO_SEAT
GET_LOCAL_PLAYER_NAME
GET_SYSTEM_TIME
GET_LAST_HIT_FLAGS
GET_LAST_HIT_WEAPON
GET_CAMERA_FROM_OBJECT
GET_BLIP_ON_OBJECT
GET_CAMERA_ASPECT_RATIO
GET_POPULATION_SET_NAME
GET_FACTIONS_STATUS
GET_WEAPON_MAX_AMMO
GET_WEAPON_IN_HAND
GET_WEAPON_FRAGMENT_NAME
SET_CAMERA_FOLLOW_ACTOR
NET_IS_SESSION_CLIENT
CUTSCENE_MANAGER_LOAD_CUTSCENE
CUTSCENE_MANAGER_LOAD_CUTFILE
CUTSCENE_MANAGER_HIDE_ACTOR
CUTSCENE_MANAGER_UNLOAD_CUTSCENE
CUTSCENE_MANAGER_PLAY_CUTSCENE
CUTSCENE_MANAGER_STOP_CUTSCENE
CUTSCENE_MANAGER_SHOW_ACTOR
HIDE_CHILD_SECTOR
SHOW_CHILD_SECTOR
PREPEND_JOURNAL_ENTRY
NET_GET_GAMER_POSSE_SIZE
NET_GET_GAMER_POSSE_LEADER
NET_GET_SESSION_GAMER_COUNT
ENABLE_GAME_CAMERA_FOCUS
DISABLE_GAME_CAMERA_FOCUS
SHOP_ADD_ITEM
SHOP_GET_ITEM_QUANTITY
SHOP_SET_PLAYER_BANK
SHOP_SET_ITEM_QUANTITY
SHOP_IS_SELL_SELECTED
CREATE_FIRE_PROPERTY
IS_ACTOR_CROUCHING
IS_ACTOR_BLINDFIRING
SET_ACTOR_STOP_UPDATE
GET_ACTOR_STOP_UPDATE
IS_DISPLAY_WIDESCREEN
IS_PLAYER_TELEPORTING
IS_SEAT_OCCUPIED
NET_SESSION_SET_INVITABLE
NET_SESSION_START_GAMEPLAY
NET_SESSION_END_GAMEPLAY
GET_GAME_EDITION
GET_FIRE_PROPERTY
GET_EVENT_PERPETRATOR
GET_ACTOR_INCAPACITATED
UI_LABEL_SET_TEXT
GET_LAST_FRAME_TIME
GET_LAST_ATTACK_TIME
GET_LAST_ATTACK_TARGET
UI_LABEL_SET_VALUE
GET_CORPSE_ACTOR_ENUM
GET_BLIP_ON_ACTOR
FIRE_SET_MAX_FLAMES
FLASH_SET_BOOL
FLASH_SET_FLOAT
FLASH_GET_BOOL
FLASH_GET_FLOAT
FLASH_SET_ARRAY_INT
FLASH_SET_ARRAY_STRING
NET_POSSE_REMOVE_GAMER
FLASH_SET_EXTENT_BOOL
IS_ACTOR_INSIDE_VEHICLE
CAN_ACTOR_HOGTIE_TARGET
SET_GAME_CAMERA_FOCUS
CREATE_ACTORSET_IN_LAYOUT
CREATE_POINT_IN_LAYOUT
CREATE_VOLUME_IN_LAYOUT
CREATE_GRINGO_IN_LAYOUT
CREATE_PROPSET_IN_LAYOUT
CREATE_PATH_IN_LAYOUT
CREATE_SQUAD_IN_LAYOUT
CREATE_FORMATION_IN_LAYOUT
CREATE_CRIME_IN_LAYOUT
CREATE_OBJECTSET_IN_LAYOUT
CREATE_GATEWAY_IN_LAYOUT
CREATE_CAMERA_IN_LAYOUT
CREATE_CAMERASHOT_IN_LAYOUT
CREATE_AIMRAMP_IN_LAYOUT
CREATE_CUTSCENEOBJECT_IN_LAYOUT
GET_PROP_FROM_OBJECT
GET_CRIME_FROM_OBJECT
GET_EVENT_FROM_OBJECT
GET_PHYSINST_FROM_ACTOR
GET_PHYSINST_FROM_OBJECT
GET_ITERATOR_FROM_OBJECT
GET_CURVE_FROM_OBJECT
GET_VOLUME_FROM_OBJECT
GET_SQUAD_FROM_OBJECT
GET_OBJECTSET_FROM_OBJECT
SET_PROP_CAUSE_ARM_UP
AI_GET_NAV_FAILSAFE_MOVEMENT_ENABLED
AI_SET_TR_PROGRAM_FOR_ACTOR
ANIMAL_SPECIES_TUNING_GET_ATTRIB_FLOAT
GET_JOURNAL_ENTRY_DETAIL_STYLE_BY_HASH
SET_ACTOR_LOW_DROP_DAMAGE
SET_ACTOR_MEDIUM_DROP_DAMAGE
SET_ACTOR_HIGH_DROP_DAMAGE
SET_ACTOR_FLY_FX
TURN_ACTOR_INTO_ZOMBIE
SET_DOOR_LOCK_VISIBLE
SET_ACTOR_BASE_SCORE
SET_ACTOR_ALLOW_DISARM
AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED
DYNAMICMIXER_TRIGGERSTATE
DYNAMICMIXER_DETRIGGERSTATE
RAND_SET_SEED
RAND_INT_RANGE
RAND_INT_RANGE_DIFFERENT
RAND_FLOAT_GAUSSIAN
NET_GAMER_SET_TITLE


*/

#undef _native
#undef _native32
#undef l