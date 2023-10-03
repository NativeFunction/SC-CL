/*H**********************************************************************
* FILENAME :	natives64.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Native functions to be used with all 64 bit GTAV targets and platforms of SC-CL.
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshift-count-overflow"

//Fix for intellisense nonsense
#ifndef _MSC_VER
#define _native64(hash) __attribute((native(hash & 0xFFFFFFFF, hash >> 32)))
#define l ;
#else
#define l {}
#define _native64(hash)
#endif

#pragma region BUILTIN //{
extern _native64(0x4EDE34FBADD967A6) void WAIT(int ms)l
extern _native64(0xE81651AD79516E48) int START_NEW_SCRIPT(const char* scriptName, int stackSize)l
extern _native64(0xB8BA7F44DF1575E1) int START_NEW_SCRIPT_WITH_ARGS(const char* scriptName, any* args, int argCount, int stackSize)l
extern _native64(0xEB1C67C3A5333A92) int START_NEW_SCRIPT_WITH_NAME_HASH(Hash scriptHash, int stackSize)l
extern _native64(0xC4BB298BD441BE78) int START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(Hash scriptHash, any* args, int argCount, int stackSize)l
extern _native64(0x83666F9FB8FEBD4B) int TIMERA()l
extern _native64(0xC9D9444186B5A374) int TIMERB()l
extern _native64(0xC1B1E9A034A63A62) void SETTIMERA(int value)l
extern _native64(0x5AE11BC36633DE4E) void SETTIMERB(int value)l
extern _native64(0x0000000050597EE2) float TIMESTEP()l
extern _native64(0x0BADBFA3B172435F) float SIN(float value)l
extern _native64(0xD0FFB162F40A139C) float COS(float value)l
extern _native64(0x71D93B57D07F9804) float SQRT(float value)l
extern _native64(0xE3621CC40F31FE2E) float POW(float base, float exponent)l
extern _native64(0xE816E655DE37FE20) float LOG10(float value)l
extern _native64(0x652D2EEEF1D3E62C) float VMAG(float x, float y, float z)l
extern _native64(0xA8CEACB4F35AE058) float VMAG2(float x, float y, float z)l
extern _native64(0x2A488C176D52CCA5) float VDIST(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0xB7A628320EFF8E47) float VDIST2(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0xEDD95A39E5544DE8) int SHIFT_LEFT(int value, int bitShift)l
extern _native64(0x97EF1E5BCE9DC075) int SHIFT_RIGHT(int value, int bitShift)l
extern _native64(0xF34EE736CF047844) int FLOOR(float value)l
extern _native64(0x11E019C8F43ACC8A) int CEIL(float value)l
extern _native64(0xF2DB717A73826179) int ROUND(float value)l
extern _native64(0xBBDA792448DB5A89) float TO_FLOAT(int value)l
extern _native64(0x42B65DEEF2EDF2A1) void SET_THIS_THREAD_PRIORITY(int priority)l
#pragma endregion //}
#pragma region APP //{
extern _native64(0x846AA8E7D55EE5B6) bool APP_DATA_VALID()l
extern _native64(0xD3A58A12C77D9D4B) int APP_GET_INT(const char* property)l
extern _native64(0x1514FB24C02C2322) float APP_GET_FLOAT(const char* property)l
extern _native64(0x749B023950D2311C) const char* APP_GET_STRING(const char* property)l
extern _native64(0x607E8E3D3E4F9611) void APP_SET_INT(const char* property, int value)l
extern _native64(0x25D7687C68E0DAA4) void APP_SET_FLOAT(const char* property, float value)l
extern _native64(0x3FF2FCEC4B7721B4) void APP_SET_STRING(const char* property, const char* value)l
extern _native64(0xCFD0406ADAF90D2B) void APP_SET_APP(const char* appName)l
extern _native64(0x262AB456A3D21F93) void APP_SET_BLOCK(const char* blockName)l
extern _native64(0x5FE1DF3342DB7DBA) void APP_CLEAR_BLOCK()l
extern _native64(0xE41C65E07A5F05FC) void APP_CLOSE_APP()l
extern _native64(0xE8E3FCF72EAC0EF8) void APP_CLOSE_BLOCK()l
extern _native64(0x71EEE69745088DA0) bool APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT()l
extern _native64(0xCA52279A7271517F) bool APP_HAS_SYNCED_DATA(const char* appName)l
extern _native64(0x95C5D356CDA6E85F) void APP_SAVE_DATA()l
extern _native64(0xC9853A2BE3DED1A6) int APP_GET_DELETED_FILE_STATUS()l
extern _native64(0x44151AEA95C8A003) bool APP_DELETE_APP_DATA(const char* appName)l
#pragma endregion //}
#pragma region AUDIO //{
extern _native64(0xF9E56683CA8E11A5) void PLAY_PED_RINGTONE(const char* ringtoneName, Ped ped, bool p2)l
extern _native64(0x1E8E5E20937E3137) bool IS_PED_RINGTONE_PLAYING(Ped ped)l
extern _native64(0x6C5AE23EFA885092) void STOP_PED_RINGTONE(Ped ped)l
extern _native64(0x7497D2CE2C30D24C) bool IS_MOBILE_PHONE_CALL_ONGOING()l
extern _native64(0xC8B1B2425604CDD0) bool IS_MOBILE_INTERFERENCE_ACTIVE()l
extern _native64(0xD2C91A0B572AAE56) void CREATE_NEW_SCRIPTED_CONVERSATION()l
extern _native64(0xC5EF963405593646) void ADD_LINE_TO_CONVERSATION(int index, const char* p1, const char* p2, int p3, int p4, bool p5, bool p6, bool p7, bool p8, int p9, bool p10, bool p11, bool p12)l
extern _native64(0x95D9F4BC443956E7) void ADD_PED_TO_CONVERSATION(int index, Ped ped, const char* p2)l
extern _native64(0x33E3C6C6F2F0B506) void SET_POSITION_FOR_NULL_CONV_PED(any p0, float p1, float p2, float p3)l
extern _native64(0x892B6AB8F33606F5) void SET_ENTITY_FOR_NULL_CONV_PED(int p0, Entity entity)l
extern _native64(0xB6AE90EDDE95C762) void SET_MICROPHONE_POSITION(bool toggle, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)l
extern _native64(0x0B568201DD99F0EB) void SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM(bool p0)l
extern _native64(0x61631F5DF50D1C34) void SET_CONVERSATION_AUDIO_PLACEHOLDER(bool p0)l
extern _native64(0x252E5F915EABB675) void START_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)l
extern _native64(0x6004BCB0E226AAEA) void PRELOAD_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)l
extern _native64(0x6B17C62C9635D2DC) void START_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x3B3CAD6166916D87) void PRELOAD_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x23641AFE870AF385) void START_PRELOADED_CONVERSATION()l
extern _native64(0xE73364DB90778FFA) bool GET_IS_PRELOADED_CONVERSATION_READY()l
extern _native64(0x16754C556D2EDE3D) bool IS_SCRIPTED_CONVERSATION_ONGOING()l
extern _native64(0xDF0D54BE7A776737) bool IS_SCRIPTED_CONVERSATION_LOADED()l
extern _native64(0x480357EE890C295A) int GET_CURRENT_SCRIPTED_CONVERSATION_LINE()l
extern _native64(0x8530AD776CD72B12) void PAUSE_SCRIPTED_CONVERSATION(bool p0)l
extern _native64(0x9AEB285D1818C9AC) void RESTART_SCRIPTED_CONVERSATION()l
extern _native64(0xD79DEEFB53455EBA) int STOP_SCRIPTED_CONVERSATION(bool p0)l
extern _native64(0x9663FE6B7A61EB00) void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE()l
extern _native64(0xA018A12E5C5C2FA6) void INTERRUPT_CONVERSATION(Ped ped, const char* voiceline, const char* speaker)l
extern _native64(0x8A694D7A68F8DC38) void INTERRUPT_CONVERSATION_AND_PAUSE(Ped ped, const char* p1, const char* speaker)l
extern _native64(0xAA19F5572C38B564) int GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE(any* p0)l
extern _native64(0xB542DE8C3D1CB210) void SET_NO_DUCKING_FOR_CONVERSATION(bool p0)l
extern _native64(0xC6ED9D5092438D91) void REGISTER_SCRIPT_WITH_AUDIO(int p0)l
extern _native64(0xA8638BE228D4751A) void UNREGISTER_SCRIPT_WITH_AUDIO()l
extern _native64(0x7345BDD95E62E0F2) bool REQUEST_MISSION_AUDIO_BANK(const char* audioBank, bool p1, any p2)l
extern _native64(0xFE02FFBED8CA9D99) bool REQUEST_AMBIENT_AUDIO_BANK(const char* audioBank, bool p1, any p2)l
extern _native64(0x2F844A8B08D76685) bool REQUEST_SCRIPT_AUDIO_BANK(const char* audioBank, bool p1, any p2)l
extern _native64(0x40763EA7B9B783E7) bool HINT_MISSION_AUDIO_BANK(const char* audioBank, bool p1, any p2)l
extern _native64(0x8F8C0E370AE62F5C) bool HINT_AMBIENT_AUDIO_BANK(const char* audioBank, bool p1, any p2)l
extern _native64(0xFB380A29641EC31A) bool HINT_SCRIPT_AUDIO_BANK(const char* audioBank, bool p1, any p2)l
extern _native64(0x0EC92A1BF0857187) void RELEASE_MISSION_AUDIO_BANK()l
extern _native64(0x65475A218FFAA93D) void RELEASE_AMBIENT_AUDIO_BANK()l
extern _native64(0x77ED170667F50170) void RELEASE_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank)l
extern _native64(0x7A2D8AD0A9EB9C3F) void RELEASE_SCRIPT_AUDIO_BANK()l
extern _native64(0x19AF7ED9B9D23058) void UNHINT_AMBIENT_AUDIO_BANK()l
extern _native64(0x9AC92EED5E4793AB) void UNHINT_SCRIPT_AUDIO_BANK()l
extern _native64(0x11579D940949C49E) void UNHINT_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank)l
extern _native64(0x430386FE9BF80B45) int GET_SOUND_ID()l
extern _native64(0x353FC880830B88FA) void RELEASE_SOUND_ID(int soundId)l
extern _native64(0x7FF4944CC209192D) void PLAY_SOUND(int soundId, const char* audioName, const char* audioRef, bool p3, any p4, bool p5)l
extern _native64(0x67C540AA08E4A6F5) void PLAY_SOUND_FRONTEND(int soundId, const char* audioName, const char* audioRef, bool p3)l
extern _native64(0xCADA5A0D0702381E) void PLAY_DEFERRED_SOUND_FRONTEND(const char* soundName, const char* soundsetName)l
extern _native64(0xE65F427EB70AB1ED) void PLAY_SOUND_FROM_ENTITY(int soundId, const char* audioName, Entity entity, const char* audioRef, bool isNetwork, any p5)l
extern _native64(0x5B9853296731E88D) void PLAY_SOUND_FROM_ENTITY_HASH(int soundId, Hash model, Entity entity, Hash soundSetHash, any p4, any p5)l
extern _native64(0x8D8686B622B88120) void PLAY_SOUND_FROM_COORD(int soundId, const char* audioName, float x, float y, float z, const char* audioRef, bool isNetwork, int range, bool p8)l
extern _native64(0x7EC3C679D0E7E46B) void UPDATE_SOUND_COORD(int soundId, float x, float y, float z)l
extern _native64(0xA3B0C41BA5CC0BB5) void STOP_SOUND(int soundId)l
extern _native64(0x2DE3F0A134FFBC0D) int GET_NETWORK_ID_FROM_SOUND_ID(int soundId)l
extern _native64(0x75262FD12D0A1C84) int GET_SOUND_ID_FROM_NETWORK_ID(int netId)l
extern _native64(0xAD6B3148A78AE9B6) void SET_VARIABLE_ON_SOUND(int soundId, const char* variable, float p2)l
extern _native64(0x2F9D3834AEB9EF79) void SET_VARIABLE_ON_STREAM(const char* variable, float p1)l
extern _native64(0xF2A9CDABCEA04BD6) void OVERRIDE_UNDERWATER_STREAM(const char* p0, bool p1)l
extern _native64(0x733ADF241531E5C2) void SET_VARIABLE_ON_UNDER_WATER_STREAM(const char* variableName, float value)l
extern _native64(0xFCBDCE714A7C88E5) bool HAS_SOUND_FINISHED(int soundId)l
extern _native64(0x8E04FEDD28D42462) void PLAY_PED_AMBIENT_SPEECH_NATIVE(Ped ped, const char* speechName, const char* speechParam, any p3)l
extern _native64(0xC6941B4A3A8FBBB9) void PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE(Ped ped, const char* speechName, const char* speechParam, any p3)l
extern _native64(0x3523634255FC3318) void PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(Ped ped, const char* speechName, const char* voiceName, const char* speechParam, bool p4)l
extern _native64(0xED640017ED337E45) void PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE(const char* speechName, const char* voiceName, float x, float y, float z, const char* speechParam)l
extern _native64(0x13AD665062541A7E) void OVERRIDE_TREVOR_RAGE(const char* voiceEffect)l
extern _native64(0xE78503B10C4314E0) void RESET_TREVOR_RAGE()l
extern _native64(0xEA241BB04110F091) void SET_PLAYER_ANGRY(Ped ped, bool toggle)l
extern _native64(0xBC9AE166038A5CEC) void PLAY_PAIN(Ped ped, int painID, int p1, any p3)l
extern _native64(0xCE4AC0439F607045) void RELEASE_WEAPON_AUDIO()l
extern _native64(0xD01005D2BA2EB778) void ACTIVATE_AUDIO_SLOWMO_MODE(const char* mode)l
extern _native64(0xDDC635D5B3262C56) void DEACTIVATE_AUDIO_SLOWMO_MODE(const char* mode)l
extern _native64(0x6C8065A3B780185B) void SET_AMBIENT_VOICE_NAME(Ped ped, const char* name)l
extern _native64(0x9A53DED9921DE990) void SET_AMBIENT_VOICE_NAME_HASH(Ped ped, Hash hash)l
extern _native64(0x5E203DA2BA15D436) Hash GET_AMBIENT_VOICE_NAME_HASH(Ped ped)l
extern _native64(0x40CF0D12D142A9E8) void SET_PED_VOICE_FULL(Ped ped)l
extern _native64(0x1B7ABE26CBCBF8C7) void SET_PED_RACE_AND_VOICE_GROUP(Ped ped, int p1, Hash voiceGroup)l
extern _native64(0x7CDC8C3B89F661B3) void SET_PED_VOICE_GROUP(Ped ped, Hash voiceGroupHash)l
extern _native64(0x0BABC1345ABBFB16) void SET_PED_VOICE_GROUP_FROM_RACE_TO_PVG(Ped ped, Hash voiceGroupHash)l
extern _native64(0xA5342D390CDA41D6) void SET_PED_GENDER(Ped ped, bool p1)l
extern _native64(0x7A73D05A607734C7) void STOP_CURRENT_PLAYING_SPEECH(Ped ped)l
extern _native64(0xB8BEC0CA6F0EDB0F) void STOP_CURRENT_PLAYING_AMBIENT_SPEECH(Ped ped)l
extern _native64(0x9072C8B49907BFAD) bool IS_AMBIENT_SPEECH_PLAYING(Ped ped)l
extern _native64(0xCC9AA18DCC7084F4) bool IS_SCRIPTED_SPEECH_PLAYING(Ped p0)l
extern _native64(0x729072355FA39EC9) bool IS_ANY_SPEECH_PLAYING(Ped ped)l
extern _native64(0x30CA2EF91D15ADF8) bool IS_ANY_POSITIONAL_SPEECH_PLAYING()l
extern _native64(0x49B99BF3FDA89A7A) bool DOES_CONTEXT_EXIST_FOR_THIS_PED(Ped ped, const char* speechName, bool p2)l
extern _native64(0x049E937F18F4020C) bool IS_PED_IN_CURRENT_CONVERSATION(Ped ped)l
extern _native64(0x95D2D383D5396B8A) void SET_PED_IS_DRUNK(Ped ped, bool toggle)l
extern _native64(0xEE066C7006C49C0A) void PLAY_ANIMAL_VOCALIZATION(Ped pedHandle, int p1, const char* speechName)l
extern _native64(0xC265DF9FB44A9FBD) bool IS_ANIMAL_VOCALIZATION_PLAYING(Ped pedHandle)l
extern _native64(0xCC97B29285B1DC3B) void SET_ANIMAL_MOOD(Ped animal, int mood)l
extern _native64(0xB35CE999E8EF317E) bool IS_MOBILE_PHONE_RADIO_ACTIVE()l
extern _native64(0xBF286C554784F3DF) void SET_MOBILE_PHONE_RADIO_STATE(bool state)l
extern _native64(0xE8AF77C4C06ADC93) int GET_PLAYER_RADIO_STATION_INDEX()l
extern _native64(0xF6D733C32076AD03) const char* GET_PLAYER_RADIO_STATION_NAME()l
extern _native64(0xB28ECA15046CA8B9) const char* GET_RADIO_STATION_NAME(int radioStation)l
extern _native64(0xA571991A7FE6CCEB) int GET_PLAYER_RADIO_STATION_GENRE()l
extern _native64(0xA151A7394A214E65) bool IS_RADIO_RETUNING()l
extern _native64(0x0626A247D2405330) bool IS_RADIO_FADED_OUT()l
extern _native64(0xFF266D1D0EB1195D) void SET_RADIO_RETUNE_UP()l
extern _native64(0xDD6BCF9E94425DF9) void SET_RADIO_RETUNE_DOWN()l
extern _native64(0xC69EDA28699D5107) void SET_RADIO_TO_STATION_NAME(const char* stationName)l
extern _native64(0x1B9C0099CB942AC6) void SET_VEH_RADIO_STATION(Vehicle vehicle, const char* radioStation)l
extern _native64(0x3E45765F3FBB582F) void SET_VEH_HAS_NORMAL_RADIO(Vehicle vehicle)l
extern _native64(0x0BE4BE946463F917) bool IS_VEHICLE_RADIO_ON(Vehicle vehicle)l
extern _native64(0xC1805D05E6D4FE10) void SET_VEH_FORCED_RADIO_THIS_FRAME(Vehicle vehicle)l
extern _native64(0xACF57305B12AF907) void SET_EMITTER_RADIO_STATION(const char* emitterName, const char* radioStation, any p2)l
extern _native64(0x399D2D3B33F1B8EB) void SET_STATIC_EMITTER_ENABLED(const char* emitterName, bool toggle)l
extern _native64(0x651D3228960D08AF) void LINK_STATIC_EMITTER_TO_ENTITY(const char* emitterName, Entity entity)l
extern _native64(0xA619B168B8A8570F) void SET_RADIO_TO_STATION_INDEX(int radioStation)l
extern _native64(0xF7F26C6E9CC9EBB8) void SET_FRONTEND_RADIO_ACTIVE(bool active)l
extern _native64(0xB165AB7C248B2DC1) void UNLOCK_MISSION_NEWS_STORY(int newsStory)l
extern _native64(0x66E49BF55B4B1874) bool IS_MISSION_NEWS_STORY_UNLOCKED(int newsStory)l
extern _native64(0x50B196FC9ED6545B) int GET_AUDIBLE_MUSIC_TRACK_TEXT_ID()l
extern _native64(0xCD536C4D33DCC900) void PLAY_END_CREDITS_MUSIC(bool play)l
extern _native64(0x6DDBBDD98E2E9C25) void SKIP_RADIO_FORWARD()l
extern _native64(0x344F393B027E38C3) void FREEZE_RADIO_STATION(const char* radioStation)l
extern _native64(0xFC00454CF60B91DD) void UNFREEZE_RADIO_STATION(const char* radioStation)l
extern _native64(0xC1AA9F53CE982990) void SET_RADIO_AUTO_UNFREEZE(bool toggle)l
extern _native64(0x88795F13FACDA88D) void SET_INITIAL_PLAYER_STATION(const char* radioStation)l
extern _native64(0x19F21E63AE6EAE4E) void SET_USER_RADIO_CONTROL_ENABLED(bool toggle)l
extern _native64(0xB39786F201FEE30B) void SET_RADIO_TRACK(const char* radioStation, const char* radioTrack)l
extern _native64(0x2CB0075110BE1E56) void SET_RADIO_TRACK_WITH_START_OFFSET(const char* radioStationName, const char* mixName, int p2)l
extern _native64(0x55ECF4D13D9903B0) void SET_NEXT_RADIO_TRACK(const char* radioName, const char* radioTrack, const char* p2, const char* p3)l
extern _native64(0xBB6F1CAEC68B0BCE) void SET_VEHICLE_RADIO_LOUD(Vehicle vehicle, bool toggle)l
extern _native64(0x032A116663A4D5AC) bool CAN_VEHICLE_RECEIVE_CB_RADIO(Vehicle vehicle)l
extern _native64(0x1098355A16064BB3) void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(bool toggle)l
extern _native64(0x109697E2FFBAC8A1) bool DOES_PLAYER_VEH_HAVE_RADIO()l
extern _native64(0x5F43D83FD6738741) bool IS_PLAYER_VEH_RADIO_ENABLE()l
extern _native64(0x3B988190C0AA6C0B) void SET_VEHICLE_RADIO_ENABLED(Vehicle vehicle, bool toggle)l
extern _native64(0xDA07819E452FFE8F) void SET_POSITIONED_PLAYER_VEHICLE_RADIO_EMITTER_ENABLED(any p0)l
extern _native64(0x4E404A9361F75BB2) void SET_CUSTOM_RADIO_TRACK_LIST(const char* radioStation, const char* trackListName, bool p2)l
extern _native64(0x1654F24A88A8E3FE) void CLEAR_CUSTOM_RADIO_TRACK_LIST(const char* radioStation)l
extern _native64(0xF1620ECB50E01DE7) int GET_NUM_UNLOCKED_RADIO_STATIONS()l
extern _native64(0x8D67489793FF428B) int FIND_RADIO_STATION_INDEX(Hash stationNameHash)l
extern _native64(0x774BD811F656A122) void SET_RADIO_STATION_MUSIC_ONLY(const char* radioStation, bool toggle)l
extern _native64(0x2C96CDB04FCA358E) void SET_RADIO_FRONTEND_FADE_TIME(float fadeTime)l
extern _native64(0x031ACB6ABA18C729) void UNLOCK_RADIO_STATION_TRACK_LIST(const char* radioStation, const char* trackListName)l
extern _native64(0xFF5E5EA2DCEEACF3) void LOCK_RADIO_STATION_TRACK_LIST(const char* radioStation, const char* trackListName)l
extern _native64(0x47AED84213A47510) void UPDATE_UNLOCKABLE_DJ_RADIO_TRACKS(bool enableMixes)l
extern _native64(0x477D9DB48F889591) void LOCK_RADIO_STATION(const char* radioStationName, bool toggle)l
extern _native64(0x4CAFEBFA21EC188D) void SET_RADIO_STATION_AS_FAVOURITE(const char* radioStation, bool toggle)l
extern _native64(0x2B1784DB08AFEA79) bool IS_RADIO_STATION_FAVOURITED(const char* radioStation)l
extern _native64(0xC64A06D939F826F5) bool GET_NEXT_AUDIBLE_BEAT(float* out1, float* out2, int* out3)l
extern _native64(0x4E0AF9114608257C) void FORCE_MUSIC_TRACK_LIST(const char* radioStation, const char* trackListName, int milliseconds)l
extern _native64(0x3E65CDE5215832C1) int GET_CURRENT_TRACK_PLAY_TIME(const char* radioStationName)l
extern _native64(0x34D66BC058019CE0) Hash GET_CURRENT_TRACK_SOUND_NAME(const char* radioStationName)l
extern _native64(0xF3365489E0DD50F9) void SET_VEHICLE_MISSILE_WARNING_ENABLED(Vehicle vehicle, bool toggle)l
extern _native64(0xBDA07E5950085E46) void SET_AMBIENT_ZONE_STATE(const char* zoneName, bool p1, bool p2)l
extern _native64(0x218DD44AAAC964FF) void CLEAR_AMBIENT_ZONE_STATE(const char* zoneName, bool p1)l
extern _native64(0x9748FA4DE50CCE3E) void SET_AMBIENT_ZONE_LIST_STATE(const char* ambientZone, bool p1, bool p2)l
extern _native64(0x120C48C614909FA4) void CLEAR_AMBIENT_ZONE_LIST_STATE(const char* ambientZone, bool p1)l
extern _native64(0x1D6650420CEC9D3B) void SET_AMBIENT_ZONE_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2)l
extern _native64(0xF3638DAE8C4045E1) void SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2)l
extern _native64(0x01E2817A479A7F9B) bool IS_AMBIENT_ZONE_ENABLED(const char* ambientZone)l
extern _native64(0x5D2BFAAB8D956E0E) void REFRESH_CLOSEST_OCEAN_SHORELINE()l
extern _native64(0x3B4BF5F0859204D9) void SET_CUTSCENE_AUDIO_OVERRIDE(const char* name)l
extern _native64(0xBCC29F935ED07688) void SET_VARIABLE_ON_SYNCH_SCENE_AUDIO(const char* variableName, float value)l
extern _native64(0xDFEBD56D9BD1EB16) int PLAY_POLICE_REPORT(const char* name, float p1)l
extern _native64(0xB4F90FAF7670B16F) void CANCEL_ALL_POLICE_REPORTS()l
extern _native64(0x1B9025BDA76822B6) void BLIP_SIREN(Vehicle vehicle)l
extern _native64(0x3CDC1E622CCE0356) void OVERRIDE_VEH_HORN(Vehicle vehicle, bool override, int hornHash)l
extern _native64(0x9D6BFC12B05C6121) bool IS_HORN_ACTIVE(Vehicle vehicle)l
extern _native64(0x395BF71085D1B1D9) void SET_AGGRESSIVE_HORNS(bool toggle)l
extern _native64(0x02E93C796ABD3A97) void SET_RADIO_POSITION_AUDIO_MUTE(bool p0)l
extern _native64(0x58BB377BEC7CD5F4) void SET_VEHICLE_CONVERSATIONS_PERSIST(bool p0, bool p1)l
extern _native64(0x9BD7BD55E4533183) void SET_VEHICLE_CONVERSATIONS_PERSIST_NEW(bool p0, bool p1, bool p2)l
extern _native64(0xD11FA52EB849D978) bool IS_STREAM_PLAYING()l
extern _native64(0x4E72BBDBCA58A3DB) int GET_STREAM_PLAY_TIME()l
extern _native64(0x1F1F957154EC51DF) bool LOAD_STREAM(const char* streamName, const char* soundSet)l
extern _native64(0x59C16B79F53B3712) bool LOAD_STREAM_WITH_START_OFFSET(const char* streamName, int startOffset, const char* soundSet)l
extern _native64(0x89049DD63C08B5D1) void PLAY_STREAM_FROM_PED(Ped ped)l
extern _native64(0xB70374A758007DFA) void PLAY_STREAM_FROM_VEHICLE(Vehicle vehicle)l
extern _native64(0xEBAA9B64D76356FD) void PLAY_STREAM_FROM_OBJECT(Object object)l
extern _native64(0x58FCE43488F9F5F4) void PLAY_STREAM_FRONTEND()l
extern _native64(0x21442F412E8DE56B) void PLAY_STREAM_FROM_POSITION(float x, float y, float z)l
extern _native64(0xA4718A1419D18151) void STOP_STREAM()l
extern _native64(0x9D64D7405520E3D3) void STOP_PED_SPEAKING(Ped ped, bool shaking)l
extern _native64(0xF8AD2EED7C47E8FE) void BLOCK_ALL_SPEECH_FROM_PED(Ped ped, bool p1, bool p2)l
extern _native64(0xAB6781A5F3101470) void STOP_PED_SPEAKING_SYNCED(Ped ped, bool p1)l
extern _native64(0xA9A41C1E940FB0E8) void DISABLE_PED_PAIN_AUDIO(Ped ped, bool toggle)l
extern _native64(0x932C2D096A2C3FFF) bool IS_AMBIENT_SPEECH_DISABLED(Ped ped)l
extern _native64(0xA8A7D434AFB4B97B) void BLOCK_SPEECH_CONTEXT_GROUP(const char* p0, int p1)l
extern _native64(0x2ACABED337622DF2) void UNBLOCK_SPEECH_CONTEXT_GROUP(const char* p0)l
extern _native64(0x1FEF0683B96EBCF2) void SET_SIREN_WITH_NO_DRIVER(Vehicle vehicle, bool toggle)l
extern _native64(0xF584CF8529B51434) void SET_SIREN_BYPASS_MP_DRIVER_CHECK(Vehicle vehicle, bool toggle)l
extern _native64(0x66C3FB05206041BA) void TRIGGER_SIREN_AUDIO(Vehicle vehicle)l
extern _native64(0x9C11908013EA4715) void SET_HORN_PERMANENTLY_ON(Vehicle vehicle)l
extern _native64(0x76D683C108594D0E) void SET_HORN_ENABLED(Vehicle vehicle, bool toggle)l
extern _native64(0xE5564483E407F914) void SET_AUDIO_VEHICLE_PRIORITY(Vehicle vehicle, any p1)l
extern _native64(0x9D3AF56E94C9AE98) void SET_HORN_PERMANENTLY_ON_TIME(Vehicle vehicle, float time)l
extern _native64(0xFA932DE350266EF8) void USE_SIREN_AS_HORN(Vehicle vehicle, bool toggle)l
extern _native64(0x4F0C413926060B38) void FORCE_USE_AUDIO_GAME_OBJECT(Vehicle vehicle, const char* audioName)l
extern _native64(0xCA4CEA6AE0000A7E) void PRELOAD_VEHICLE_AUDIO_BANK(Hash vehicleModel)l
extern _native64(0xF1F8157B8C3F171C) void SET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle, const char* p1, const char* p2)l
extern _native64(0xD2DCCD8E16E20997) void RESET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle)l
extern _native64(0x97FFB4ADEED08066) void SET_VEHICLE_FORCE_REVERSE_WARNING(any p0, any p1)l
extern _native64(0x5DB8010EE71FDEF2) bool IS_VEHICLE_AUDIBLY_DAMAGED(Vehicle vehicle)l
extern _native64(0x59E7B488451F4D3A) void SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR(Vehicle vehicle, float damageFactor)l
extern _native64(0x01BB4D577D38BD9E) void SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR(Vehicle vehicle, float intensity)l
extern _native64(0x1C073274E065C6D2) void ENABLE_VEHICLE_FANBELT_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0x2BE4BC731D039D5A) void ENABLE_VEHICLE_EXHAUST_POPS(Vehicle vehicle, bool toggle)l
extern _native64(0x4A04DE7CAB2739A1) void SET_VEHICLE_BOOST_ACTIVE(Vehicle vehicle, bool toggle)l
extern _native64(0x6FDDAD856E36988A) void SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE(Vehicle vehicle, bool toggle)l
extern _native64(0x06C0023BED16DD6B) void SET_SCRIPT_UPDATE_DOOR_AUDIO(Hash doorHash, bool toggle)l
extern _native64(0x3A539D52857EA82D) void PLAY_VEHICLE_DOOR_OPEN_SOUND(Vehicle vehicle, int doorId)l
extern _native64(0x62A456AA4769EF34) void PLAY_VEHICLE_DOOR_CLOSE_SOUND(Vehicle vehicle, int doorId)l
extern _native64(0xC15907D667F7CFB2) void ENABLE_STALL_WARNING_SOUNDS(Vehicle vehicle, bool toggle)l
extern _native64(0x6D28DC1671E334FD) bool IS_GAME_IN_CONTROL_OF_MUSIC()l
extern _native64(0x3BD3F52BA9B1E4E8) void SET_GPS_ACTIVE(bool active)l
extern _native64(0xB138AAB8A70D3C69) void PLAY_MISSION_COMPLETE_AUDIO(const char* audioName)l
extern _native64(0x19A30C23F5827F8A) bool IS_MISSION_COMPLETE_PLAYING()l
extern _native64(0x6F259F82D873B8B8) bool IS_MISSION_COMPLETE_READY_FOR_UI()l
extern _native64(0xF154B8D1775B2DEC) void BLOCK_DEATH_JINGLE(bool toggle)l
extern _native64(0x013A80FC08F6E4F2) bool START_AUDIO_SCENE(const char* scene)l
extern _native64(0xDFE8422B3B94E688) void STOP_AUDIO_SCENE(const char* scene)l
extern _native64(0xBAC7FC81A75EC1A1) void STOP_AUDIO_SCENES()l
extern _native64(0xB65B60556E2A9225) bool IS_AUDIO_SCENE_ACTIVE(const char* scene)l
extern _native64(0xEF21A9EF089A2668) void SET_AUDIO_SCENE_VARIABLE(const char* scene, const char* variable, float value)l
extern _native64(0xA5F377B175A699C5) void SET_AUDIO_SCRIPT_CLEANUP_TIME(int time)l
extern _native64(0x153973AB99FE8980) void ADD_ENTITY_TO_AUDIO_MIX_GROUP(Entity entity, const char* groupName, float p2)l
extern _native64(0x18EB48CFC41F2EA0) void REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP(Entity entity, float p1)l
extern _native64(0x845FFC3A4FEEFA3E) bool AUDIO_IS_MUSIC_PLAYING()l
extern _native64(0x2DD39BF3E2F9C47F) bool AUDIO_IS_SCRIPTED_MUSIC_PLAYING()l
extern _native64(0x1E5185B72EF5158A) bool PREPARE_MUSIC_EVENT(const char* eventName)l
extern _native64(0x5B17A90291133DA5) bool CANCEL_MUSIC_EVENT(const char* eventName)l
extern _native64(0x706D57B0F50DA710) bool TRIGGER_MUSIC_EVENT(const char* eventName)l
extern _native64(0xA097AB275061FB21) bool IS_MUSIC_ONESHOT_PLAYING()l
extern _native64(0xE7A0D23DC414507B) int GET_MUSIC_PLAYTIME()l
extern _native64(0x159B7318403A1CD8) void SET_GLOBAL_RADIO_SIGNAL_LEVEL(any p0)l
extern _native64(0xFBE20329593DEC9D) void RECORD_BROKEN_GLASS(float x, float y, float z, float radius)l
extern _native64(0xB32209EFFDC04913) void CLEAR_ALL_BROKEN_GLASS()l
extern _native64(0x70B8EC8FC108A634) void SCRIPT_OVERRIDES_WIND_ELEVATION(bool p0, any p1)l
extern _native64(0x149AEE66F0CB3A99) void SET_PED_WALLA_DENSITY(float p0, float p1)l
extern _native64(0x8BF907833BE275DE) void SET_PED_INTERIOR_WALLA_DENSITY(float p0, float p1)l
extern _native64(0x062D5EAD4DA2FA6A) void FORCE_PED_PANIC_WALLA()l
extern _native64(0x9D74AE343DB65533) bool PREPARE_ALARM(const char* alarmName)l
extern _native64(0x0355EF116C4C97B2) void START_ALARM(const char* alarmName, bool p2)l
extern _native64(0xA1CADDCD98415A41) void STOP_ALARM(const char* alarmName, bool toggle)l
extern _native64(0x2F794A877ADD4C92) void STOP_ALL_ALARMS(bool stop)l
extern _native64(0x226435CB96CCFC8C) bool IS_ALARM_PLAYING(const char* alarmName)l
extern _native64(0x02165D55000219AC) Hash GET_VEHICLE_DEFAULT_HORN(Vehicle vehicle)l
extern _native64(0xACB5DCCA1EC76840) Hash GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS(Vehicle vehicle)l
extern _native64(0xF54BB7B61036F335) void RESET_PED_AUDIO_FLAGS(Ped ped)l
extern _native64(0x0653B735BFBDFE87) void SET_PED_FOOTSTEPS_EVENTS_ENABLED(Ped ped, bool toggle)l
extern _native64(0x29DA3CA8D8B2692D) void SET_PED_CLOTH_EVENTS_ENABLED(Ped ped, bool toggle)l
extern _native64(0xD2CC78CD3D0B50F9) void OVERRIDE_PLAYER_GROUND_MATERIAL(Hash hash, bool toggle)l
extern _native64(0xBF4DC1784BE94DFA) void USE_FOOTSTEP_SCRIPT_SWEETENERS(Ped ped, bool p1, Hash hash)l
extern _native64(0x75773E11BA459E90) void OVERRIDE_MICROPHONE_SETTINGS(Hash hash, bool toggle)l
extern _native64(0xD57AAAE0E2214D11) void FREEZE_MICROPHONE()l
extern _native64(0x552369F549563AD5) void DISTANT_COP_CAR_SIRENS(bool value)l
extern _native64(0x43FA0DFC5DF87815) void SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO(Vehicle vehicle, bool p1)l
extern _native64(0xB81CF134AEB56FFB) void ENABLE_STUNT_JUMP_AUDIO()l
extern _native64(0xB9EFD5C25018725A) void SET_AUDIO_FLAG(const char* flagName, bool toggle)l
extern _native64(0xC7ABCACA4985A766) bool PREPARE_SYNCHRONIZED_AUDIO_EVENT(const char* audioEvent, any p1)l
extern _native64(0x029FE7CD1B7E2E75) bool PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(int sceneID, const char* audioEvent)l
extern _native64(0x8B2FD4560E55DD2D) bool PLAY_SYNCHRONIZED_AUDIO_EVENT(int sceneID)l
extern _native64(0x92D6A88E64A94430) bool STOP_SYNCHRONIZED_AUDIO_EVENT(int sceneID)l
extern _native64(0xC8EDE9BDBCCBA6D4) void INIT_SYNCH_SCENE_AUDIO_WITH_POSITION(const char* audioEvent, float x, float y, float z)l
extern _native64(0x950A154B8DAB6185) void INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY(const char* audioEvent, Entity entity)l
extern _native64(0x12561FCBB62D5B9C) void SET_AUDIO_SPECIAL_EFFECT_MODE(int mode)l
extern _native64(0x044DBAD7A7FA2BE5) void SET_PORTAL_SETTINGS_OVERRIDE(const char* p0, const char* p1)l
extern _native64(0xB4BBFD9CD8B3922B) void REMOVE_PORTAL_SETTINGS_OVERRIDE(const char* p0)l
extern _native64(0xE4E6DD5566D28C82) void STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS()l
extern _native64(0x3A48AB4445D499BE) int GET_MUSIC_VOL_SLIDER()l
extern _native64(0x4ADA3F19BE4A6047) void REQUEST_TENNIS_BANKS(Ped ped)l
extern _native64(0x0150B6FF25A9E2E5) void UNREQUEST_TENNIS_BANKS()l
extern _native64(0xBEF34B1D9624D5DD) void SET_SKIP_MINIGUN_SPIN_UP_AUDIO(bool p0)l
extern _native64(0x806058BBDC136E06) void STOP_CUTSCENE_AUDIO()l
extern _native64(0x544810ED9DB6BBE6) bool HAS_LOADED_MP_DATA_SET()l
extern _native64(0x5B50ABB1FE3746F4) bool HAS_LOADED_SP_DATA_SET()l
extern _native64(0xD53F3A29BCE2580E) int GET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle)l
extern _native64(0x0350E7E17BA767D0) void SET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle, int value)l
#pragma endregion //}
#pragma region BRAIN //{
extern _native64(0x4EE5367468A65CCC) void ADD_SCRIPT_TO_RANDOM_PED(const char* name, Hash model, float p2, float p3)l
extern _native64(0x0BE84C318BA6EC22) void REGISTER_OBJECT_SCRIPT_BRAIN(const char* scriptName, Hash modelHash, int p2, float activationRange, int p4, int p5)l
extern _native64(0xCCBA154209823057) bool IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Object object)l
extern _native64(0x3CDC7136613284BD) void REGISTER_WORLD_POINT_SCRIPT_BRAIN(const char* scriptName, float activationRange, int p2)l
extern _native64(0xC5042CC6F5E3D450) bool IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE()l
extern _native64(0x67AA4D73F0CFA86B) void ENABLE_SCRIPT_BRAIN_SET(int brainSet)l
extern _native64(0x14D8518E9760F08F) void DISABLE_SCRIPT_BRAIN_SET(int brainSet)l
extern _native64(0x0B40ED49D7D6FF84) void REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE()l
extern _native64(0x4D953DF78EBF8158) void REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE()l
extern _native64(0x6D6840CEE8845831) void REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE(const char* scriptName)l
extern _native64(0x6E91B04E08773030) void REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE(const char* scriptName)l
#pragma endregion //}
#pragma region CAM //{
extern _native64(0x07E5B515DB0636FC) void RENDER_SCRIPT_CAMS(bool render, bool ease, int easeTime, bool p3, bool p4, any p5)l
extern _native64(0xC819F3CBB62BF692) void STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP(bool render, float p1, int p2, any p3)l
extern _native64(0xC3981DCE61D9E13F) Cam CREATE_CAM(const char* camName, bool p1)l
extern _native64(0xB51194800B257161) Cam CREATE_CAM_WITH_PARAMS(const char* camName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, int p9)l
extern _native64(0x5E3CF89C6BCCA67D) Cam CREATE_CAMERA(Hash camHash, bool p1)l
extern _native64(0x6ABFA3E16460F22D) Cam CREATE_CAMERA_WITH_PARAMS(Hash camHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, any p9)l
extern _native64(0x865908C81A2C22E9) void DESTROY_CAM(Cam cam, bool bScriptHostCam)l
extern _native64(0x8E5FB15663F79120) void DESTROY_ALL_CAMS(bool bScriptHostCam)l
extern _native64(0xA7A932170592B50E) bool DOES_CAM_EXIST(Cam cam)l
extern _native64(0x026FB97D0A425F84) void SET_CAM_ACTIVE(Cam cam, bool active)l
extern _native64(0xDFB2B516207D3534) bool IS_CAM_ACTIVE(Cam cam)l
extern _native64(0x02EC0AF5C5A49B7A) bool IS_CAM_RENDERING(Cam cam)l
extern _native64(0x5234F9F10919EABA) Cam GET_RENDERING_CAM()l
extern _native64(0xBAC038F7459AE5AE) vector3 GET_CAM_COORD(Cam cam)l
extern _native64(0x7D304C1C955E3E12) vector3 GET_CAM_ROT(Cam cam, int rotationOrder)l
extern _native64(0xC3330A45CCCDB26A) float GET_CAM_FOV(Cam cam)l
extern _native64(0xC520A34DAFBF24B1) float GET_CAM_NEAR_CLIP(Cam cam)l
extern _native64(0xB60A9CFEB21CA6AA) float GET_CAM_FAR_CLIP(Cam cam)l
extern _native64(0xC2612D223D915A1C) float GET_CAM_NEAR_DOF(Cam cam)l
extern _native64(0x255F8DAFD540D397) float GET_CAM_FAR_DOF(Cam cam)l
extern _native64(0x06D153C0B99B6128) float GET_CAM_DOF_STRENGTH(Cam cam)l
extern _native64(0xBFD8727AEA3CCEBA) void SET_CAM_PARAMS(Cam cam, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fieldOfView, any p8, int p9, int p10, int p11)l
extern _native64(0x4D41783FB745E42E) void SET_CAM_COORD(Cam cam, float posX, float posY, float posZ)l
extern _native64(0x85973643155D0B07) void SET_CAM_ROT(Cam cam, float rotX, float rotY, float rotZ, int rotationOrder)l
extern _native64(0xB13C14F66A00D047) void SET_CAM_FOV(Cam cam, float fieldOfView)l
extern _native64(0xC7848EFCCC545182) void SET_CAM_NEAR_CLIP(Cam cam, float nearClip)l
extern _native64(0xAE306F2A904BF86E) void SET_CAM_FAR_CLIP(Cam cam, float farClip)l
extern _native64(0xAABD62873FFB1A33) void FORCE_CAM_FAR_CLIP(Cam cam, float p1)l
extern _native64(0x6F0F77FBA9A8F2E6) void SET_CAM_MOTION_BLUR_STRENGTH(Cam cam, float strength)l
extern _native64(0x3FA4BF0A7AB7DE2C) void SET_CAM_NEAR_DOF(Cam cam, float nearDOF)l
extern _native64(0xEDD91296CD01AEE0) void SET_CAM_FAR_DOF(Cam cam, float farDOF)l
extern _native64(0x5EE29B4D7D5DF897) void SET_CAM_DOF_STRENGTH(Cam cam, float dofStrength)l
extern _native64(0x3CF48F6F96E749DC) void SET_CAM_DOF_PLANES(Cam cam, float p1, float p2, float p3, float p4)l
extern _native64(0x16A96863A17552BB) void SET_CAM_USE_SHALLOW_DOF_MODE(Cam cam, bool toggle)l
extern _native64(0xA13B0222F3D94A94) void SET_USE_HI_DOF()l
extern _native64(0x731A880555DA3647) void SET_USE_HI_DOF_ON_SYNCED_SCENE_THIS_UPDATE()l
extern _native64(0xF55E4046F6F831DC) void SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE(Cam camera, float p1)l
extern _native64(0xE111A7C0D200CBC5) void SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE_BLEND_LEVEL(any p0, float p1)l
extern _native64(0x7DD234D6F3914C5B) void SET_CAM_DOF_FNUMBER_OF_LENS(Cam camera, float p1)l
extern _native64(0x47B595D60664CFFA) void SET_CAM_DOF_FOCAL_LENGTH_MULTIPLIER(Cam camera, float multiplier)l
extern _native64(0xC669EEA5D031B7DE) void SET_CAM_DOF_FOCUS_DISTANCE_BIAS(Cam camera, float p1)l
extern _native64(0xC3654A441402562D) void SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(Cam camera, float p1)l
extern _native64(0x2C654B4943BDDF7C) void SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(Cam camera, float p1)l
extern _native64(0x7CF3AF51DCFE4108) void SET_CAM_DOF_SHOULD_KEEP_LOOK_AT_TARGET_IN_FOCUS(Cam camera, bool state)l
extern _native64(0xFEDB7D269E8C60E3) void ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xOffset, float yOffset, float zOffset, bool isRelative)l
extern _native64(0x61A3DBA14AB7F411) void ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, bool heading)l
extern _native64(0x149916F50C34A40D) void HARD_ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)l
extern _native64(0x202A5ED9CE01D6E7) void HARD_ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xRot, float yRot, float zRot, float xOffset, float yOffset, float zOffset, bool isRelative)l
extern _native64(0x8DB3F12A02CAEF72) void ATTACH_CAM_TO_VEHICLE_BONE(Cam cam, Vehicle vehicle, int boneIndex, bool relativeRotation, float rotX, float rotY, float rotZ, float offsetX, float offsetY, float offsetZ, bool fixedDirection)l
extern _native64(0xA2FABBE87F4BAD82) void DETACH_CAM(Cam cam)l
extern _native64(0x45F1DE9C34B93AE6) void SET_CAM_INHERIT_ROLL_VEHICLE(Cam cam, bool p1)l
extern _native64(0xF75497BB865F0803) void POINT_CAM_AT_COORD(Cam cam, float x, float y, float z)l
extern _native64(0x5640BFF86B16E8DC) void POINT_CAM_AT_ENTITY(Cam cam, Entity entity, float p2, float p3, float p4, bool p5)l
extern _native64(0x68B2B5F33BA63C41) void POINT_CAM_AT_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, bool p6)l
extern _native64(0xF33AB75780BA57DE) void STOP_CAM_POINTING(Cam cam)l
extern _native64(0x8C1DC7770C51DC8D) void SET_CAM_AFFECTS_AIMING(Cam cam, bool toggle)l
extern _native64(0x661B5C8654ADD825) void SET_CAM_CONTROLS_MINI_MAP_HEADING(Cam cam, bool toggle)l
extern _native64(0xA2767257A320FC82) void SET_CAM_IS_INSIDE_VEHICLE(Cam cam, bool toggle)l
extern _native64(0x271017B9BA825366) void ALLOW_MOTION_BLUR_DECAY(any p0, bool p1)l
extern _native64(0x1B93E0107865DD40) void SET_CAM_DEBUG_NAME(Cam camera, const char* name)l
extern _native64(0x77C3CEC46BE286F6) Cam GET_DEBUG_CAM()l
extern _native64(0x8609C75EC438FB3B) void ADD_CAM_SPLINE_NODE(Cam camera, float x, float y, float z, float xRot, float yRot, float zRot, int length, int smoothingStyle, int rotationOrder)l
extern _native64(0x0A9F2A468B328E74) void ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME(Cam cam, Cam cam2, int length, int p3)l
extern _native64(0x0FB82563989CF4FB) void ADD_CAM_SPLINE_NODE_USING_CAMERA(Cam cam, Cam cam2, int length, int p3)l
extern _native64(0x609278246A29CA34) void ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME(Cam cam, int length, int p2)l
extern _native64(0x242B5874F0A4E052) void SET_CAM_SPLINE_PHASE(Cam cam, float p1)l
extern _native64(0xB5349E36C546509A) float GET_CAM_SPLINE_PHASE(Cam cam)l
extern _native64(0xD9D0E694C8282C96) float GET_CAM_SPLINE_NODE_PHASE(Cam cam)l
extern _native64(0x1381539FEE034CDA) void SET_CAM_SPLINE_DURATION(Cam cam, int timeDuration)l
extern _native64(0xD1B0F412F109EA5D) void SET_CAM_SPLINE_SMOOTHING_STYLE(Cam cam, int smoothingStyle)l
extern _native64(0xB22B17DF858716A6) int GET_CAM_SPLINE_NODE_INDEX(Cam cam)l
extern _native64(0x83B8201ED82A9A2D) void SET_CAM_SPLINE_NODE_EASE(Cam cam, int easingFunction, int p2, float p3)l
extern _native64(0xA6385DEB180F319F) void SET_CAM_SPLINE_NODE_VELOCITY_SCALE(Cam cam, int p1, float scale)l
extern _native64(0x40B62FA033EB0346) void OVERRIDE_CAM_SPLINE_VELOCITY(Cam cam, int p1, float p2, float p3)l
extern _native64(0x7DCF7C708D292D55) void OVERRIDE_CAM_SPLINE_MOTION_BLUR(Cam cam, int p1, float p2, float p3)l
extern _native64(0x7BF1A54AE67AC070) void SET_CAM_SPLINE_NODE_EXTRA_FLAGS(Cam cam, int p1, int flags)l
extern _native64(0x0290F35C0AD97864) bool IS_CAM_SPLINE_PAUSED(Cam cam)l
extern _native64(0x9FBDA379383A52A4) void SET_CAM_ACTIVE_WITH_INTERP(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation)l
extern _native64(0x036F97C908C2B52C) bool IS_CAM_INTERPOLATING(Cam cam)l
extern _native64(0x6A25241C340D3822) void SHAKE_CAM(Cam cam, const char* type, float amplitude)l
extern _native64(0xA2746EEAE3E577CD) void ANIMATED_SHAKE_CAM(Cam cam, const char* p1, const char* p2, const char* p3, float amplitude)l
extern _native64(0x6B24BFE83A2BE47B) bool IS_CAM_SHAKING(Cam cam)l
extern _native64(0xD93DB43B82BC0D00) void SET_CAM_SHAKE_AMPLITUDE(Cam cam, float amplitude)l
extern _native64(0xBDECF64367884AC3) void STOP_CAM_SHAKING(Cam cam, bool p1)l
extern _native64(0xF4C8CF9E353AFECA) void SHAKE_SCRIPT_GLOBAL(const char* p0, float p1)l
extern _native64(0xC2EAE3FB8CDBED31) void ANIMATED_SHAKE_SCRIPT_GLOBAL(const char* p0, const char* p1, const char* p2, float p3)l
extern _native64(0xC912AF078AF19212) bool IS_SCRIPT_GLOBAL_SHAKING()l
extern _native64(0x1C9D7949FA533490) void STOP_SCRIPT_GLOBAL_SHAKING(bool p0)l
extern _native64(0x5D96CFB59DA076A0) void TRIGGER_VEHICLE_PART_BROKEN_CAMERA_SHAKE(Vehicle vehicle, int p1, float p2)l
extern _native64(0x9A2D0FB2E7852392) bool PLAY_CAM_ANIM(Cam cam, const char* animName, const char* animDictionary, float x, float y, float z, float xRot, float yRot, float zRot, bool p9, int p10)l
extern _native64(0xC90621D8A0CEECF2) bool IS_CAM_PLAYING_ANIM(Cam cam, const char* animName, const char* animDictionary)l
extern _native64(0x4145A4C44FF3B5A6) void SET_CAM_ANIM_CURRENT_PHASE(Cam cam, float phase)l
extern _native64(0xA10B2DB49E92A6B0) float GET_CAM_ANIM_CURRENT_PHASE(Cam cam)l
extern _native64(0xE32EFE9AB4A9AA0C) bool PLAY_SYNCHRONIZED_CAM_ANIM(any p0, any p1, const char* animName, const char* animDictionary)l
extern _native64(0x503F5920162365B2) void SET_FLY_CAM_HORIZONTAL_RESPONSE(Cam cam, float p1, float p2, float p3)l
extern _native64(0xE827B9382CFB41BA) void SET_FLY_CAM_VERTICAL_RESPONSE(Cam cam, float p1, float p2, float p3)l
extern _native64(0xF9D02130ECDD1D77) void SET_FLY_CAM_MAX_HEIGHT(Cam cam, float height)l
extern _native64(0xC91C6C55199308CA) void SET_FLY_CAM_COORD_AND_CONSTRAIN(Cam cam, float x, float y, float z)l
extern _native64(0xC8B5C4A79CC18B94) void SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE(Cam cam)l
extern _native64(0x5C48A1D6E3B33179) bool WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE(Cam cam)l
extern _native64(0xB16FCE9DDC7BA182) bool IS_SCREEN_FADED_OUT()l
extern _native64(0x5A859503B0C08678) bool IS_SCREEN_FADED_IN()l
extern _native64(0x797AC7CB535BA28F) bool IS_SCREEN_FADING_OUT()l
extern _native64(0x5C544BC6C57AC575) bool IS_SCREEN_FADING_IN()l
extern _native64(0xD4E8E24955024033) void DO_SCREEN_FADE_IN(int duration)l
extern _native64(0x891B5B39AC6302AF) void DO_SCREEN_FADE_OUT(int duration)l
extern _native64(0xDCD4EA924F42D01A) void SET_WIDESCREEN_BORDERS(bool p0, int p1)l
extern _native64(0x4879E4FE39074CDF) bool ARE_WIDESCREEN_BORDERS_ACTIVE()l
extern _native64(0x14D6F5678D8F1B37) vector3 GET_GAMEPLAY_CAM_COORD()l
extern _native64(0x837765A25378F0BB) vector3 GET_GAMEPLAY_CAM_ROT(int rotationOrder)l
extern _native64(0x65019750A0324133) float GET_GAMEPLAY_CAM_FOV()l
extern _native64(0x487A82C650EB7799) void SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE(float p0)l
extern _native64(0x0225778816FDC28C) void SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE(float p0)l
extern _native64(0x743607648ADD4587) float GET_GAMEPLAY_CAM_RELATIVE_HEADING()l
extern _native64(0xB4EC2312F4E5B1F1) void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading)l
extern _native64(0x3A6867B4845BEDA2) float GET_GAMEPLAY_CAM_RELATIVE_PITCH()l
extern _native64(0x6D0858B8EDFD2B7D) void SET_GAMEPLAY_CAM_RELATIVE_PITCH(float angle, float scalingFactor)l
extern _native64(0x7295C203DD659DFE) void RESET_GAMEPLAY_CAM_FULL_ATTACH_PARENT_TRANSFORM_TIMER()l
extern _native64(0x48608C3464F58AB4) void FORCE_CAMERA_RELATIVE_HEADING_AND_PITCH(float roll, float pitch, float yaw)l
extern _native64(0x28B022A17B068A3A) void FORCE_BONNET_CAMERA_RELATIVE_HEADING_AND_PITCH(float p0, float p1)l
extern _native64(0x103991D4A307D472) void SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(float yaw)l
extern _native64(0x759E13EBC1C15C5A) void SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(float pitch)l
extern _native64(0x469F2ECDEC046337) void SET_SCRIPTED_CAMERA_IS_FIRST_PERSON_THIS_FRAME(bool p0)l
extern _native64(0xFD55E49555E017CF) void SHAKE_GAMEPLAY_CAM(const char* shakeName, float intensity)l
extern _native64(0x016C090630DF1F89) bool IS_GAMEPLAY_CAM_SHAKING()l
extern _native64(0xA87E00932DB4D85D) void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(float amplitude)l
extern _native64(0x0EF93E9F3D08C178) void STOP_GAMEPLAY_CAM_SHAKING(bool p0)l
extern _native64(0x8BBACBF51DA047A8) void SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE(Ped ped)l
extern _native64(0x39B5D1B10383F0C8) bool IS_GAMEPLAY_CAM_RENDERING()l
extern _native64(0x3044240D2E0FA842) bool IS_INTERPOLATING_FROM_SCRIPT_CAMS()l
extern _native64(0x705A276EBFF3133D) bool IS_INTERPOLATING_TO_SCRIPT_CAMS()l
extern _native64(0xDB90C6CCA48940F1) void SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE(bool p0)l
extern _native64(0xEA7F0AD7E9BA676F) void DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE()l
extern _native64(0x70FDA869F3317EA9) bool IS_GAMEPLAY_CAM_LOOKING_BEHIND()l
extern _native64(0x2AED6301F67007D5) void SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE(Entity entity)l
extern _native64(0x49482F9FCD825AAA) void DISABLE_CAM_COLLISION_FOR_OBJECT(Entity entity)l
extern _native64(0xA7092AFE81944852) void BYPASS_CAMERA_COLLISION_BUOYANCY_TEST_THIS_UPDATE()l
extern _native64(0xFD3151CD37EA2245) void SET_GAMEPLAY_CAM_ENTITY_TO_LIMIT_FOCUS_OVER_BOUNDING_SPHERE_THIS_UPDATE(Entity entity)l
extern _native64(0xB1381B97F70C7B30) void DISABLE_FIRST_PERSON_CAMERA_WATER_CLIPPING_TEST_THIS_UPDATE()l
extern _native64(0xDD79DF9F4D26E1C9) void SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE()l
extern _native64(0xE33D59DA70B58FDF) bool IS_SPHERE_VISIBLE(float x, float y, float z, float radius)l
extern _native64(0xC6D3D26810C8E0F9) bool IS_FOLLOW_PED_CAM_ACTIVE()l
extern _native64(0x44A113DD6FFC48D1) bool SET_FOLLOW_PED_CAM_THIS_UPDATE(const char* camName, int p1)l
extern _native64(0x271401846BD26E92) void USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME(bool p0, bool p1)l
extern _native64(0xC8391C309684595A) void SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE()l
extern _native64(0x8F993D26E0CA5E8E) void SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float minimum, float maximum)l
extern _native64(0xA516C198B7DCA1E1) void SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float minimum, float maximum)l
extern _native64(0xDF2E1F7742402E81) void SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(float p0, float distance)l
extern _native64(0xE9EA16D6E54CDCA4) void SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE(Vehicle p0, int p1)l
extern _native64(0xDE2EF5DA284CC8DF) void DISABLE_ON_FOOT_FIRST_PERSON_VIEW_THIS_UPDATE()l
extern _native64(0x59424BD75174C9B1) void DISABLE_FIRST_PERSON_FLASH_EFFECT_THIS_UPDATE()l
extern _native64(0x9F97DA93681F87EA) void BLOCK_FIRST_PERSON_ORIENTATION_RESET_THIS_UPDATE()l
extern _native64(0x33E6C8EFD0CD93E9) int GET_FOLLOW_PED_CAM_ZOOM_LEVEL()l
extern _native64(0x8D4D46230B2C353A) int GET_FOLLOW_PED_CAM_VIEW_MODE()l
extern _native64(0x5A4F9EDF1673F704) void SET_FOLLOW_PED_CAM_VIEW_MODE(int viewMode)l
extern _native64(0xCBBDE6D335D6D496) bool IS_FOLLOW_VEHICLE_CAM_ACTIVE()l
extern _native64(0x91EF6EE6419E5B97) void SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE(bool p0)l
extern _native64(0x9DFE13ECDC1EC196) void SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE(bool p0, bool p1)l
extern _native64(0x79C0E43EB9B944E2) bool SET_TABLE_GAMES_CAMERA_THIS_UPDATE(Hash hash)l
extern _native64(0xEE82280AB767B690) int GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL()l
extern _native64(0x19464CB6E4078C8A) void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(int zoomLevel)l
extern _native64(0xA4FF579AC0E3AAAE) int GET_FOLLOW_VEHICLE_CAM_VIEW_MODE()l
extern _native64(0xAC253D7842768F48) void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(int viewMode)l
extern _native64(0xEE778F8C7E1142E2) int GET_CAM_VIEW_MODE_FOR_CONTEXT(int context)l
extern _native64(0x2A2173E46DAECD12) void SET_CAM_VIEW_MODE_FOR_CONTEXT(int context, int viewMode)l
extern _native64(0x19CAFA3C87F7C2FF) int GET_CAM_ACTIVE_VIEW_MODE_CONTEXT()l
extern _native64(0x6493CF69859B116A) void USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE()l
extern _native64(0x425A920FDB9A0DDA) void USE_DEDICATED_STUNT_CAMERA_THIS_UPDATE(const char* camName)l
extern _native64(0x0AA27680A0BD43FA) void FORCE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE()l
extern _native64(0x5C90CAB09951A12F) void SET_FOLLOW_VEHICLE_CAM_SEAT_THIS_UPDATE(int seatIndex)l
extern _native64(0x68EDDA28A5976D07) bool IS_AIM_CAM_ACTIVE()l
extern _native64(0x74BD83EA840F6BC9) bool IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE()l
extern _native64(0x5E346D934122613F) bool IS_FIRST_PERSON_AIM_CAM_ACTIVE()l
extern _native64(0x1A31FE0049E542F6) void DISABLE_AIM_CAM_THIS_UPDATE()l
extern _native64(0x7EC52CC40597D170) float GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR()l
extern _native64(0x70894BD0915C5BCA) void SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR(float zoomFactor)l
extern _native64(0xCED08CBE8EBB97C7) void SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE(float p0, float p1)l
extern _native64(0x2F7F2B26DD3F18EE) void SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float p0, float p1)l
extern _native64(0xBCFC632DB7673BF0) void SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float p0, float p1)l
extern _native64(0x0AF7B437918103B3) void SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0)l
extern _native64(0x42156508606DE65E) void SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0)l
extern _native64(0x4008EDF7D6E48175) void SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE(bool p0)l
extern _native64(0x380B4968D1E09E55) void FORCE_TIGHTSPACE_CUSTOM_FRAMING_THIS_UPDATE()l
extern _native64(0xA200EB1EE790F448) vector3 GET_FINAL_RENDERED_CAM_COORD()l
extern _native64(0x5B4E4C817FCC2DFB) vector3 GET_FINAL_RENDERED_CAM_ROT(int rotationOrder)l
extern _native64(0x26903D9CD1175F2C) vector3 GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT(Player player, int rotationOrder)l
extern _native64(0x80EC114669DAEFF4) float GET_FINAL_RENDERED_CAM_FOV()l
extern _native64(0x5F35F6732C3FBBA0) float GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV(Player player)l
extern _native64(0xD0082607100D7193) float GET_FINAL_RENDERED_CAM_NEAR_CLIP()l
extern _native64(0xDFC8CBC606FDB0FC) float GET_FINAL_RENDERED_CAM_FAR_CLIP()l
extern _native64(0xA03502FC581F7D9B) float GET_FINAL_RENDERED_CAM_NEAR_DOF()l
extern _native64(0x9780F32BCAF72431) float GET_FINAL_RENDERED_CAM_FAR_DOF()l
extern _native64(0x162F9D995753DC19) float GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH()l
extern _native64(0xD51ADCD2D8BC0FB3) void SET_GAMEPLAY_COORD_HINT(float x, float y, float z, int duration, int blendOutDuration, int blendInDuration, int p6)l
extern _native64(0x2B486269ACD548D3) void SET_GAMEPLAY_PED_HINT(Ped ped, float x1, float y1, float z1, bool p4, int duration, int blendOutDuration, int blendInDuration)l
extern _native64(0xA2297E18F3E71C2E) void SET_GAMEPLAY_VEHICLE_HINT(Vehicle vehicle, float offsetX, float offsetY, float offsetZ, bool p4, int time, int easeInTime, int easeOutTime)l
extern _native64(0x83E87508A2CA2AC6) void SET_GAMEPLAY_OBJECT_HINT(Object object, float xOffset, float yOffset, float zOffset, bool p4, int time, int easeInTime, int easeOutTime)l
extern _native64(0x189E955A8313E298) void SET_GAMEPLAY_ENTITY_HINT(Entity entity, float xOffset, float yOffset, float zOffset, bool p4, int time, int easeInTime, int easeOutTime, int p8)l
extern _native64(0xE520FF1AD2785B40) bool IS_GAMEPLAY_HINT_ACTIVE()l
extern _native64(0xF46C581C61718916) void STOP_GAMEPLAY_HINT(bool p0)l
extern _native64(0xCCD078C2665D2973) void STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE(bool p0)l
extern _native64(0x247ACBC4ABBC9D1C) void STOP_CODE_GAMEPLAY_HINT(bool p0)l
extern _native64(0xBF72910D0F26F025) bool IS_CODE_GAMEPLAY_HINT_ACTIVE()l
extern _native64(0x513403FB9C56211F) void SET_GAMEPLAY_HINT_FOV(float FOV)l
extern _native64(0xF8BDBF3D573049A1) void SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR(float value)l
extern _native64(0xD1F8363DFAD03848) void SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET(float value)l
extern _native64(0x5D7B620DAE436138) void SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET(float xOffset)l
extern _native64(0xC92717EF615B6704) void SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET(float yOffset)l
extern _native64(0xE3433EADAAF7EE40) void SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE(bool toggle)l
extern _native64(0x51669F7D1FB53D9F) void SET_CINEMATIC_BUTTON_ACTIVE(bool p0)l
extern _native64(0xB15162CB5826E9E8) bool IS_CINEMATIC_CAM_RENDERING()l
extern _native64(0xDCE214D9ED58F3CF) void SHAKE_CINEMATIC_CAM(const char* shakeType, float amount)l
extern _native64(0xBBC08F6B4CB8FF0A) bool IS_CINEMATIC_CAM_SHAKING()l
extern _native64(0xC724C701C30B2FE7) void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(float p0)l
extern _native64(0x2238E588E588A6D7) void STOP_CINEMATIC_CAM_SHAKING(bool p0)l
extern _native64(0xADFF1B2A555F5FBA) void DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE()l
extern _native64(0x62ECFCFDEE7885D6) void DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE()l
extern _native64(0x9E4CFFF989258472) void INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE()l
extern _native64(0xF4F2C0D4EE209E20) void INVALIDATE_IDLE_CAM()l
extern _native64(0xCA9D2AA3E326D720) bool IS_CINEMATIC_IDLE_CAM_RENDERING()l
extern _native64(0x4F32C0D5A90A9B40) bool IS_CINEMATIC_FIRST_PERSON_VEHICLE_INTERIOR_CAM_RENDERING()l
extern _native64(0x741B0129D4560F31) void CREATE_CINEMATIC_SHOT(Hash p0, int time, bool p2, Entity entity)l
extern _native64(0xCC9F3371A7C28BC9) bool IS_CINEMATIC_SHOT_ACTIVE(Hash p0)l
extern _native64(0x7660C6E75D3A078E) void STOP_CINEMATIC_SHOT(Hash p0)l
extern _native64(0xA41BCD7213805AAC) void FORCE_CINEMATIC_RENDERING_THIS_UPDATE(bool toggle)l
extern _native64(0xDC9DA9E8789F5246) void SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE()l
extern _native64(0xDCF0754AC3D6FD4E) void SET_CINEMATIC_MODE_ACTIVE(bool toggle)l
extern _native64(0x1F2300CB7FA7B7F6) bool IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING()l
extern _native64(0x17FCA7199A530203) bool DISABLE_CINEMATIC_SLOW_MO_THIS_UPDATE()l
extern _native64(0xD7360051C885628B) bool IS_BONNET_CINEMATIC_CAM_RENDERING()l
extern _native64(0xF5F1E89A970B7796) bool IS_CINEMATIC_CAM_INPUT_ACTIVE()l
extern _native64(0x7B8A361C1813FBEF) void IGNORE_MENU_PREFERENCE_FOR_BONNET_CAMERA_THIS_UPDATE()l
extern _native64(0xDB629FFD9285FA06) void BYPASS_CUTSCENE_CAM_RENDERING_THIS_UPDATE()l
extern _native64(0x324C5AA411DA7737) void STOP_CUTSCENE_CAM_SHAKING(any p0)l
extern _native64(0x12DED8CA53D47EA5) void SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE(float p0)l
extern _native64(0x89215EC747DF244A) Ped GET_FOCUS_PED_ON_SCREEN(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8)l
extern _native64(0x5A43C76F7FC7BA5F) void DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE()l
extern _native64(0x80C8B1846639BB19) void SET_CAM_DEATH_FAIL_EFFECT_STATE(int p0)l
extern _native64(0x5C41E6BABC9E2112) void SET_FIRST_PERSON_FLASH_EFFECT_TYPE(any p0)l
extern _native64(0x21E253A7F8DA5DFB) void SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_NAME(const char* vehicleName)l
extern _native64(0x11FA5D3479C7DD47) void SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_HASH(Hash vehicleModel)l
extern _native64(0xEAF0FA793D05C592) bool IS_ALLOWED_INDEPENDENT_CAMERA_MODES()l
extern _native64(0x62374889A4D59F72) void CAMERA_PREVENT_COLLISION_SETTINGS_FOR_TRIPLEHEAD_IN_INTERIORS_THIS_UPDATE()l
extern _native64(0x8BFCEB5EA1B161B6) float REPLAY_GET_MAX_DISTANCE_ALLOWED_FROM_PLAYER()l
#pragma endregion //}
#pragma region CLOCK //{
extern _native64(0x47C3B5848C3E45D8) void SET_CLOCK_TIME(int hour, int minute, int second)l
extern _native64(0x4055E40BD2DBEC1D) void PAUSE_CLOCK(bool toggle)l
extern _native64(0xC8CA9670B9D83B3B) void ADVANCE_CLOCK_TIME_TO(int hour, int minute, int second)l
extern _native64(0xD716F30D8C8980E2) void ADD_TO_CLOCK_TIME(int hours, int minutes, int seconds)l
extern _native64(0x25223CA6B4D20B7F) int GET_CLOCK_HOURS()l
extern _native64(0x13D2B8ADD79640F2) int GET_CLOCK_MINUTES()l
extern _native64(0x494E97C2EF27C470) int GET_CLOCK_SECONDS()l
extern _native64(0xB096419DF0D06CE7) void SET_CLOCK_DATE(int day, int month, int year)l
extern _native64(0xD972E4BD7AEB235F) int GET_CLOCK_DAY_OF_WEEK()l
extern _native64(0x3D10BC92A4DB1D35) int GET_CLOCK_DAY_OF_MONTH()l
extern _native64(0xBBC72712E80257A1) int GET_CLOCK_MONTH()l
extern _native64(0x961777E64BDAF717) int GET_CLOCK_YEAR()l
extern _native64(0x2F8B4D1C595B11DB) int GET_MILLISECONDS_PER_GAME_MINUTE()l
extern _native64(0xDA488F299A5B164E) void GET_POSIX_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second)l
extern _native64(0x8117E09A19EEF4D3) void GET_UTC_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second)l
extern _native64(0x50C7A99057A69748) void GET_LOCAL_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second)l
#pragma endregion //}
#pragma region CUTSCENE //{
extern _native64(0x7A86743F475D9E09) void REQUEST_CUTSCENE(const char* cutsceneName, int flags)l
extern _native64(0xC23DE0E91C30B58C) void REQUEST_CUTSCENE_WITH_PLAYBACK_LIST(const char* cutsceneName, int playbackFlags, int flags)l
extern _native64(0x440AF51A3462B86F) void REMOVE_CUTSCENE()l
extern _native64(0xC59F528E9AB9F339) bool HAS_CUTSCENE_LOADED()l
extern _native64(0x228D3D94F8A11C3C) bool HAS_THIS_CUTSCENE_LOADED(const char* cutsceneName)l
extern _native64(0x8D9DF6ECA8768583) void SET_SCRIPT_CAN_START_CUTSCENE(int threadId)l
extern _native64(0xB56BBBCC2955D9CB) bool CAN_REQUEST_ASSETS_FOR_CUTSCENE_ENTITY()l
extern _native64(0x71B74D2AE19338D0) bool IS_CUTSCENE_PLAYBACK_FLAG_SET(int flag)l
extern _native64(0x4C61C75BEE8184C2) void SET_CUTSCENE_ENTITY_STREAMING_FLAGS(const char* cutsceneEntName, int p1, int p2)l
extern _native64(0x06A3524161C502BA) void REQUEST_CUT_FILE(const char* cutsceneName)l
extern _native64(0xA1C996C2A744262E) bool HAS_CUT_FILE_LOADED(const char* cutsceneName)l
extern _native64(0xD00D76A7DFC9D852) void REMOVE_CUT_FILE(const char* cutsceneName)l
extern _native64(0x0ABC54DE641DC0FC) int GET_CUT_FILE_CONCAT_COUNT(const char* cutsceneName)l
extern _native64(0x186D5CB5E7B0FF7B) void START_CUTSCENE(int flags)l
extern _native64(0x1C9ADDA3244A1FBF) void START_CUTSCENE_AT_COORDS(float x, float y, float z, int flags)l
extern _native64(0xC7272775B4DC786E) void STOP_CUTSCENE(bool p0)l
extern _native64(0xD220BDD222AC4A1E) void STOP_CUTSCENE_IMMEDIATELY()l
extern _native64(0xB812B3FD1C01CF27) void SET_CUTSCENE_ORIGIN(float x, float y, float z, float p3, int p4)l
extern _native64(0x011883F41211432A) void SET_CUTSCENE_ORIGIN_AND_ORIENTATION(float x1, float y1, float z1, float x2, float y2, float z2, int p6)l
extern _native64(0xE625BEABBAFFDAB9) int GET_CUTSCENE_TIME()l
extern _native64(0xEE53B14A19E480D4) int GET_CUTSCENE_TOTAL_DURATION()l
extern _native64(0x971D7B15BCDBEF99) int GET_CUTSCENE_END_TIME()l
extern _native64(0x5D583F71C901F2A3) int GET_CUTSCENE_PLAY_DURATION()l
extern _native64(0x40C8656EDAEDD569) bool WAS_CUTSCENE_SKIPPED()l
extern _native64(0x7C0A893088881D57) bool HAS_CUTSCENE_FINISHED()l
extern _native64(0x991251AFC3981F84) bool IS_CUTSCENE_ACTIVE()l
extern _native64(0xD3C2E180A40F031E) bool IS_CUTSCENE_PLAYING()l
extern _native64(0x49010A6A396553D8) int GET_CUTSCENE_SECTION_PLAYING()l
extern _native64(0x0A2E9FDB9A8C62F6) Entity GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x583DF8E3D4AFBD98) int GET_CUTSCENE_CONCAT_SECTION_PLAYING()l
extern _native64(0x4CEBC1ED31E8925E) bool IS_CUTSCENE_AUTHORIZED(const char* cutsceneName)l
extern _native64(0x4FCD976DA686580C) int DOES_CUTSCENE_HANDLE_EXIST(int cutsceneHandle)l
extern _native64(0xE40C1C56DF95C2E8) void REGISTER_ENTITY_FOR_CUTSCENE(Ped cutscenePed, const char* cutsceneEntName, int p2, Hash modelHash, int p4)l
extern _native64(0xC0741A26499654CD) Entity GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x7F96F23FA9B73327) void SET_VEHICLE_MODEL_PLAYER_WILL_EXIT_SCENE(Hash modelHash)l
extern _native64(0x9896CE4721BE84BA) void SET_CUTSCENE_TRIGGER_AREA(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x645D0B458D8E17B5) bool CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x4C6A6451C79E4662) bool CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0xB2CBCD0930DFB420) bool CAN_SET_EXIT_STATE_FOR_CAMERA(bool p0)l
extern _native64(0xC61B86C9F61EB404) void SET_PAD_CAN_SHAKE_DURING_CUTSCENE(bool toggle)l
extern _native64(0x8093F23ABACCC7D4) void SET_CUTSCENE_FADE_VALUES(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x20746F7B1032A3C7) void SET_CUTSCENE_MULTIHEAD_FADE(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x06EE9048FD080382) void SET_CUTSCENE_MULTIHEAD_FADE_MANUAL(bool p0)l
extern _native64(0xA0FE76168A189DDB) bool IS_MULTIHEAD_FADE_UP()l
extern _native64(0x2F137B508DE238F2) void NETWORK_SET_MOCAP_CUTSCENE_CAN_BE_SKIPPED(bool p0)l
extern _native64(0xE36A98D8AB3D3C66) void SET_CAR_GENERATORS_CAN_UPDATE_DURING_CUTSCENE(bool p0)l
extern _native64(0x5EDEF0CF8C1DAB3C) bool CAN_USE_MOBILE_PHONE_DURING_CUTSCENE()l
extern _native64(0x41FAA8FB2ECE8720) void SET_CUTSCENE_CAN_BE_SKIPPED(bool p0)l
extern _native64(0x2131046957F31B04) void SET_CAN_DISPLAY_MINIMAP_DURING_CUTSCENE_THIS_UPDATE()l
extern _native64(0xBA01E7B6DEEFBBC9) void SET_CUTSCENE_PED_COMPONENT_VARIATION(const char* cutsceneEntName, int componentId, int drawableId, int textureId, Hash modelHash)l
extern _native64(0x2A56C06EBEF2B0D9) void SET_CUTSCENE_PED_COMPONENT_VARIATION_FROM_PED(const char* cutsceneEntName, Ped ped, Hash modelHash)l
extern _native64(0x499EF20C5DB25C59) bool DOES_CUTSCENE_ENTITY_EXIST(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x0546524ADE2E9723) void SET_CUTSCENE_PED_PROP_VARIATION(const char* cutsceneEntName, int componentId, int drawableId, int textureId, Hash modelHash)l
extern _native64(0x708BDD8CD795B043) bool HAS_CUTSCENE_CUT_THIS_FRAME()l
#pragma endregion //}
#pragma region DATAFILE //{
extern _native64(0xAD6875BBC0FC899C) void DATAFILE_WATCH_REQUEST_ID(int requestId)l
extern _native64(0x6CC86E78358D5119) void DATAFILE_CLEAR_WATCH_LIST()l
extern _native64(0xFCCAE5B92A830878) bool DATAFILE_IS_VALID_REQUEST_ID(int index)l
extern _native64(0x15FF52B809DB2353) bool DATAFILE_HAS_LOADED_FILE_DATA(int requestId)l
extern _native64(0xF8CC1EBE0B62E29F) bool DATAFILE_HAS_VALID_FILE_DATA(int requestId)l
extern _native64(0x22DA66936E0FFF37) bool DATAFILE_SELECT_ACTIVE_FILE(int requestId, any p1)l
extern _native64(0x8F5EA1C01D65A100) bool DATAFILE_DELETE_REQUESTED_FILE(int requestId)l
extern _native64(0xC84527E235FCA219) bool UGC_CREATE_CONTENT(any* data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, bool publish, any p7)l
extern _native64(0xA5EFC3E847D60507) bool UGC_CREATE_MISSION(const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, bool publish, any p5)l
extern _native64(0x648E7A5434AF7969) bool UGC_UPDATE_CONTENT(const char* contentId, any* data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, any p7)l
extern _native64(0x4645DE9980999E93) bool UGC_UPDATE_MISSION(const char* contentId, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, any p5)l
extern _native64(0x692D808C34A82143) bool UGC_SET_PLAYER_DATA(const char* contentId, float rating, const char* contentTypeName, any p3)l
extern _native64(0xA69AC4ADE82B57A4) bool DATAFILE_SELECT_UGC_DATA(int p0, any p1)l
extern _native64(0x9CB0BFA7A9342C3D) bool DATAFILE_SELECT_UGC_STATS(int p0, bool p1, any p2)l
extern _native64(0x52818819057F2B40) bool DATAFILE_SELECT_UGC_PLAYER_DATA(int p0, any p1)l
extern _native64(0x01095C95CD46B624) bool DATAFILE_SELECT_CREATOR_STATS(int p0, any p1)l
extern _native64(0xC5238C011AF405E4) bool DATAFILE_LOAD_OFFLINE_UGC(const char* filename, any p1)l
extern _native64(0xD27058A1CA2B13EE) void DATAFILE_CREATE(int p0)l
extern _native64(0x9AB9C1CFC8862DFB) void DATAFILE_DELETE(int p0)l
extern _native64(0x2ED61456317B8178) void DATAFILE_STORE_MISSION_HEADER(int p0)l
extern _native64(0xC55854C7D7274882) void DATAFILE_FLUSH_MISSION_HEADER()l
extern _native64(0x906B778CA1DC72B6) any* DATAFILE_GET_FILE_DICT(int p0)l
extern _native64(0x83BCCE3224735F05) bool DATAFILE_START_SAVE_TO_CLOUD(const char* filename, any p1)l
extern _native64(0x4DFDD9EB705F8140) bool DATAFILE_UPDATE_SAVE_TO_CLOUD(bool* p0)l
extern _native64(0xBEDB96A7584AA8CF) bool DATAFILE_IS_SAVE_PENDING()l
extern _native64(0xA6EEF01087181EDD) bool DATAFILE_LOAD_OFFLINE_UGC_FOR_ADDITIONAL_DATA_FILE(any p0, any p1)l
extern _native64(0x6AD0BD5E087866CB) void DATAFILE_DELETE_FOR_ADDITIONAL_DATA_FILE(any p0)l
extern _native64(0xDBF860CF1DB8E599) any* DATAFILE_GET_FILE_DICT_FOR_ADDITIONAL_DATA_FILE(any p0)l
extern _native64(0x35124302A556A325) void DATADICT_SET_BOOL(any* objectData, const char* key, bool value)l
extern _native64(0xE7E035450A7948D5) void DATADICT_SET_INT(any* objectData, const char* key, int value)l
extern _native64(0xC27E1CC2D795105E) void DATADICT_SET_FLOAT(any* objectData, const char* key, float value)l
extern _native64(0x8FF3847DADD8E30C) void DATADICT_SET_STRING(any* objectData, const char* key, const char* value)l
extern _native64(0x4CD49B76338C7DEE) void DATADICT_SET_VECTOR(any* objectData, const char* key, float valueX, float valueY, float valueZ)l
extern _native64(0xA358F56F10732EE1) any* DATADICT_CREATE_DICT(any* objectData, const char* key)l
extern _native64(0x5B11728527CA6E5F) any* DATADICT_CREATE_ARRAY(any* objectData, const char* key)l
extern _native64(0x1186940ED72FFEEC) bool DATADICT_GET_BOOL(any* objectData, const char* key)l
extern _native64(0x78F06F6B1FB5A80C) int DATADICT_GET_INT(any* objectData, const char* key)l
extern _native64(0x06610343E73B9727) float DATADICT_GET_FLOAT(any* objectData, const char* key)l
extern _native64(0x3D2FD9E763B24472) const char* DATADICT_GET_STRING(any* objectData, const char* key)l
extern _native64(0x46CD3CB66E0825CC) vector3 DATADICT_GET_VECTOR(any* objectData, const char* key)l
extern _native64(0xB6B9DDC412FCEEE2) any* DATADICT_GET_DICT(any* objectData, const char* key)l
extern _native64(0x7A983AA9DA2659ED) any* DATADICT_GET_ARRAY(any* objectData, const char* key)l
extern _native64(0x031C55ED33227371) int DATADICT_GET_TYPE(any* objectData, const char* key)l
extern _native64(0xF8B0F5A43E928C76) void DATAARRAY_ADD_BOOL(any* arrayData, bool value)l
extern _native64(0xCABDB751D86FE93B) void DATAARRAY_ADD_INT(any* arrayData, int value)l
extern _native64(0x57A995FD75D37F56) void DATAARRAY_ADD_FLOAT(any* arrayData, float value)l
extern _native64(0x2F0661C155AEEEAA) void DATAARRAY_ADD_STRING(any* arrayData, const char* value)l
extern _native64(0x407F8D034F70F0C2) void DATAARRAY_ADD_VECTOR(any* arrayData, float valueX, float valueY, float valueZ)l
extern _native64(0x6889498B3E19C797) any* DATAARRAY_ADD_DICT(any* arrayData)l
extern _native64(0x50C1B2874E50C114) bool DATAARRAY_GET_BOOL(any* arrayData, int arrayIndex)l
extern _native64(0x3E5AE19425CD74BE) int DATAARRAY_GET_INT(any* arrayData, int arrayIndex)l
extern _native64(0xC0C527B525D7CFB5) float DATAARRAY_GET_FLOAT(any* arrayData, int arrayIndex)l
extern _native64(0xD3F2FFEB8D836F52) const char* DATAARRAY_GET_STRING(any* arrayData, int arrayIndex)l
extern _native64(0x8D2064E5B64A628A) vector3 DATAARRAY_GET_VECTOR(any* arrayData, int arrayIndex)l
extern _native64(0x8B5FADCC4E3A145F) any* DATAARRAY_GET_DICT(any* arrayData, int arrayIndex)l
extern _native64(0x065DB281590CEA2D) int DATAARRAY_GET_COUNT(any* arrayData)l
extern _native64(0x3A0014ADB172A3C5) int DATAARRAY_GET_TYPE(any* arrayData, int arrayIndex)l
#pragma endregion //}
#pragma region DECORATOR //{
extern _native64(0x95AED7B8E39ECAA4) bool DECOR_SET_TIME(Entity entity, const char* propertyName, int timestamp)l
extern _native64(0x6B1E8E2ED1335B71) bool DECOR_SET_BOOL(Entity entity, const char* propertyName, bool value)l
extern _native64(0x211AB1DD8D0F363A) bool DECOR_SET_FLOAT(Entity entity, const char* propertyName, float value)l
extern _native64(0x0CE3AA5E1CA19E10) bool DECOR_SET_INT(Entity entity, const char* propertyName, int value)l
extern _native64(0xDACE671663F2F5DB) bool DECOR_GET_BOOL(Entity entity, const char* propertyName)l
extern _native64(0x6524A2F114706F43) float DECOR_GET_FLOAT(Entity entity, const char* propertyName)l
extern _native64(0xA06C969B02A97298) int DECOR_GET_INT(Entity entity, const char* propertyName)l
extern _native64(0x05661B80A8C9165F) bool DECOR_EXIST_ON(Entity entity, const char* propertyName)l
extern _native64(0x00EE9F297C738720) bool DECOR_REMOVE(Entity entity, const char* propertyName)l
extern _native64(0x9FD90732F56403CE) void DECOR_REGISTER(const char* propertyName, int type)l
extern _native64(0x4F14F9F870D6FBC8) bool DECOR_IS_REGISTERED_AS_TYPE(const char* propertyName, int type)l
extern _native64(0xA9D14EEA259F9248) void DECOR_REGISTER_LOCK()l
#pragma endregion //}
#pragma region DLC //{
extern _native64(0x241FCA5B1AA14F75) bool ARE_ANY_CCS_PENDING()l
extern _native64(0x812595A0644CE1DE) bool IS_DLC_PRESENT(Hash dlcHash)l
extern _native64(0xF2E07819EF1A5289) bool DLC_CHECK_CLOUD_DATA_CORRECT()l
extern _native64(0x9489659372A81585) int GET_EXTRACONTENT_CLOUD_RESULT()l
extern _native64(0xA213B11DFF526300) bool DLC_CHECK_COMPAT_PACK_CONFIGURATION()l
extern _native64(0x8D30F648014A92B5) bool GET_EVER_HAD_BAD_PACK_ORDER()l
extern _native64(0x10D0A8F259E93EC9) bool GET_IS_LOADING_SCREEN_ACTIVE()l
extern _native64(0xC4637A6D03C24CC3) bool GET_IS_INITIAL_LOADING_SCREEN_ACTIVE()l
extern _native64(0x46E2B844905BC5F0) bool HAS_CLOUD_REQUESTS_FINISHED(bool* p0, int unused)l
extern _native64(0xD7C10C4A637992C9) void ON_ENTER_SP()l
extern _native64(0x0888C3502DBBEEF5) void ON_ENTER_MP()l
#pragma endregion //}
#pragma region ENTITY //{
extern _native64(0x7239B21A38F536BA) bool DOES_ENTITY_EXIST(Entity entity)l
extern _native64(0xDDE6DF5AE89981D2) bool DOES_ENTITY_BELONG_TO_THIS_SCRIPT(Entity entity, bool p1)l
extern _native64(0x060D6E96F8B8E48D) bool DOES_ENTITY_HAVE_DRAWABLE(Entity entity)l
extern _native64(0xDA95EA3317CC5064) bool DOES_ENTITY_HAVE_PHYSICS(Entity entity)l
extern _native64(0x764EB96874EFFDC1) bool DOES_ENTITY_HAVE_SKELETON(Entity entity)l
extern _native64(0x2158E81A6AF65EA9) bool DOES_ENTITY_HAVE_ANIM_DIRECTOR(Entity entity)l
extern _native64(0x20B711662962B472) bool HAS_ENTITY_ANIM_FINISHED(Entity entity, const char* animDict, const char* animName, int p3)l
extern _native64(0x95EB9964FF5C5C65) bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity entity)l
extern _native64(0x605F5A140F202491) bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity entity)l
extern _native64(0xDFD5033FDBA0A9C8) bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity entity)l
extern _native64(0xC86D67D52A707CF8) bool HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2, bool p2)l
extern _native64(0xFCDFF7B72D23A1AC) bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Entity entity1, Entity entity2, int traceType)l
extern _native64(0x394BDE2A7BBA031E) bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER(Entity entity1, Entity entity2, int traceType)l
extern _native64(0x0267D00AF114F17A) bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Entity entity1, Entity entity2)l
extern _native64(0x8BAD02F0368D9E14) bool HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity entity)l
extern _native64(0xA75EE4F689B85391) Entity _GET_LAST_ENTITY_HIT_BY_ENTITY(Entity entity)l
extern _native64(0x5C3D0A935F535C4C) Hash GET_LAST_MATERIAL_HIT_BY_ENTITY(Entity entity)l
extern _native64(0xE465D4AB7CA6AE72) vector3 GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(Entity entity)l
extern _native64(0x40FDEDB72F8293B2) void FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(Entity entity)l
extern _native64(0x346D81500D088F42) float GET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDict, const char* animName)l
extern _native64(0x50BD2730B191E360) float GET_ENTITY_ANIM_TOTAL_TIME(Entity entity, const char* animDict, const char* animName)l
extern _native64(0xFEDDF04D62B8D790) float GET_ANIM_DURATION(const char* animDict, const char* animName)l
extern _native64(0x48C2BED9180FE123) Entity GET_ENTITY_ATTACHED_TO(Entity entity)l
extern _native64(0x3FEF770D40960D5A) vector3 GET_ENTITY_COORDS(Entity entity, bool alive)l
extern _native64(0x0A794A5A57F8DF91) vector3 GET_ENTITY_FORWARD_VECTOR(Entity entity)l
extern _native64(0x8BB4EF4214E0E6D5) float GET_ENTITY_FORWARD_X(Entity entity)l
extern _native64(0x866A4A5FAE349510) float GET_ENTITY_FORWARD_Y(Entity entity)l
extern _native64(0xE83D4F9BA2A38914) float GET_ENTITY_HEADING(Entity entity)l
extern _native64(0x846BF6291198A71E) float GET_ENTITY_HEADING_FROM_EULERS(Entity entity)l
extern _native64(0xEEF059FAD016D209) int GET_ENTITY_HEALTH(Entity entity)l
extern _native64(0x15D757606D170C3C) int GET_ENTITY_MAX_HEALTH(Entity entity)l
extern _native64(0x166E7CF68597D8B5) void SET_ENTITY_MAX_HEALTH(Entity entity, int value)l
extern _native64(0x5A504562485944DD) float GET_ENTITY_HEIGHT(Entity entity, float X, float Y, float Z, bool atTop, bool inWorldCoords)l
extern _native64(0x1DD55701034110E5) float GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity entity)l
extern _native64(0xECB2FC7235A7D137) void GET_ENTITY_MATRIX(Entity entity, vector3* forwardVector, vector3* rightVector, vector3* upVector, vector3* position)l
extern _native64(0x9F47B058362C84B5) Hash GET_ENTITY_MODEL(Entity entity)l
extern _native64(0x2274BC1C4885E333) vector3 GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Entity entity, float posX, float posY, float posZ)l
extern _native64(0x1899F328B0E12848) vector3 GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity entity, float offsetX, float offsetY, float offsetZ)l
extern _native64(0xD45DC2893621E1FE) float GET_ENTITY_PITCH(Entity entity)l
extern _native64(0x7B3703D2D32DFA18) void GET_ENTITY_QUATERNION(Entity entity, float* x, float* y, float* z, float* w)l
extern _native64(0x831E0242595560DF) float GET_ENTITY_ROLL(Entity entity)l
extern _native64(0xAFBD61CC738D9EB9) vector3 GET_ENTITY_ROTATION(Entity entity, int rotationOrder)l
extern _native64(0x213B91045D09B983) vector3 GET_ENTITY_ROTATION_VELOCITY(Entity entity)l
extern _native64(0xA6E9C38DB51D7748) const char* GET_ENTITY_SCRIPT(Entity entity, ScrHandle* script)l
extern _native64(0xD5037BA82E12416F) float GET_ENTITY_SPEED(Entity entity)l
extern _native64(0x9A8D700A51CB7B0D) vector3 GET_ENTITY_SPEED_VECTOR(Entity entity, bool relative)l
extern _native64(0x95EED5A694951F9F) float GET_ENTITY_UPRIGHT_VALUE(Entity entity)l
extern _native64(0x4805D2B1D8CF94A9) vector3 GET_ENTITY_VELOCITY(Entity entity)l
extern _native64(0xD7E3B9735C0F89D6) Object GET_OBJECT_INDEX_FROM_ENTITY_INDEX(Entity entity)l
extern _native64(0x04A2A40C73395041) Ped GET_PED_INDEX_FROM_ENTITY_INDEX(Entity entity)l
extern _native64(0x4B53F92932ADFAC0) Vehicle GET_VEHICLE_INDEX_FROM_ENTITY_INDEX(Entity entity)l
extern _native64(0x44A8FCB8ED227738) vector3 GET_WORLD_POSITION_OF_ENTITY_BONE(Entity entity, int boneIndex)l
extern _native64(0x7196842CB375CDB3) Player GET_NEAREST_PLAYER_TO_ENTITY(Entity entity)l
extern _native64(0x4DC9A62F844D9337) Player GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM(Entity entity, int team)l
extern _native64(0xFFBD7052D65BE0FF) int GET_NEAREST_PARTICIPANT_TO_ENTITY(Entity entity)l
extern _native64(0x8ACD366038D14505) int GET_ENTITY_TYPE(Entity entity)l
extern _native64(0xF6F5161F4534EDFF) int GET_ENTITY_POPULATION_TYPE(Entity entity)l
extern _native64(0x731EC8A916BD11A1) bool IS_AN_ENTITY(ScrHandle handle)l
extern _native64(0x524AC5ECEA15343E) bool IS_ENTITY_A_PED(Entity entity)l
extern _native64(0x0A7B270912999B3C) bool IS_ENTITY_A_MISSION_ENTITY(Entity entity)l
extern _native64(0x6AC7003FA6E5575E) bool IS_ENTITY_A_VEHICLE(Entity entity)l
extern _native64(0x8D68C8FD0FACA94E) bool IS_ENTITY_AN_OBJECT(Entity entity)l
extern _native64(0x20B60995556D004F) bool IS_ENTITY_AT_COORD(Entity entity, float xPos, float yPos, float zPos, float xSize, float ySize, float zSize, bool p7, bool p8, int p9)l
extern _native64(0x751B70C3D034E187) bool IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, float xSize, float ySize, float zSize, bool p5, bool p6, int p7)l
extern _native64(0xB346476EF1A64897) bool IS_ENTITY_ATTACHED(Entity entity)l
extern _native64(0xCF511840CEEDE0CC) bool IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Entity entity)l
extern _native64(0xB1632E9A5F988D11) bool IS_ENTITY_ATTACHED_TO_ANY_PED(Entity entity)l
extern _native64(0x26AA915AD89BFB4B) bool IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Entity entity)l
extern _native64(0xEFBE71898A993728) bool IS_ENTITY_ATTACHED_TO_ENTITY(Entity from, Entity to)l
extern _native64(0x5F9532F3B5CC2551) bool IS_ENTITY_DEAD(Entity entity, bool p1)l
extern _native64(0x886E37EC497200B6) bool IS_ENTITY_IN_AIR(Entity entity)l
extern _native64(0x51210CED3DA1C78A) bool IS_ENTITY_IN_ANGLED_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, float width, bool debug, bool includeZ, any p10)l
extern _native64(0x54736AA40E271165) bool IS_ENTITY_IN_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8, any p9)l
extern _native64(0xB6463CF6AF527071) bool IS_ENTITY_IN_ZONE(Entity entity, const char* zone)l
extern _native64(0xCFB0A0D8EDD145A3) bool IS_ENTITY_IN_WATER(Entity entity)l
extern _native64(0xE81AFC1BC4CC41CE) float GET_ENTITY_SUBMERGED_LEVEL(Entity entity)l
extern _native64(0x694E00132F2823ED) void SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK(Entity entity, bool toggle)l
extern _native64(0xE659E47AF827484B) bool IS_ENTITY_ON_SCREEN(Entity entity)l
extern _native64(0x1F0B79228E461EC9) bool IS_ENTITY_PLAYING_ANIM(Entity entity, const char* animDict, const char* animName, int taskFlag)l
extern _native64(0x1218E6886D3D8327) bool IS_ENTITY_STATIC(Entity entity)l
extern _native64(0x17FFC1B2BA35A494) bool IS_ENTITY_TOUCHING_ENTITY(Entity entity, Entity targetEntity)l
extern _native64(0x0F42323798A58C8C) bool IS_ENTITY_TOUCHING_MODEL(Entity entity, Hash modelHash)l
extern _native64(0x5333F526F6AB19AA) bool IS_ENTITY_UPRIGHT(Entity entity, float angle)l
extern _native64(0x1DBD58820FA61D71) bool IS_ENTITY_UPSIDEDOWN(Entity entity)l
extern _native64(0x47D6F43D77935C75) bool IS_ENTITY_VISIBLE(Entity entity)l
extern _native64(0xD796CB5BA8F20E32) bool IS_ENTITY_VISIBLE_TO_SCRIPT(Entity entity)l
extern _native64(0xE31C2C72B8692B64) bool IS_ENTITY_OCCLUDED(Entity entity)l
extern _native64(0xEE5D2A122E09EC42) bool WOULD_ENTITY_BE_OCCLUDED(Hash entityModelHash, float x, float y, float z, bool p4)l
extern _native64(0xD05BFF0C0A12C68F) bool IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Entity entity)l
extern _native64(0x18FF00FC7EFF559E) void APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(Entity entity, int forceType, float x, float y, float z, bool p5, bool isDirectionRel, bool isForceRel, bool p8)l
extern _native64(0xC5F68BE9613E2D18) void APPLY_FORCE_TO_ENTITY(Entity entity, int forceFlags, float x, float y, float z, float offX, float offY, float offZ, int boneIndex, bool isDirectionRel, bool ignoreUpVec, bool isForceRel, bool p12, bool p13)l
extern _native64(0x6B9BBD38AB0796DF) void ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, bool p9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot, any p15)l
extern _native64(0x5C48B75732C8456C) void ATTACH_ENTITY_BONE_TO_ENTITY_BONE(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, bool p4, bool p5)l
extern _native64(0xFD1695C5D3B05439) void ATTACH_ENTITY_BONE_TO_ENTITY_BONE_Y_FORWARD(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, bool p4, bool p5)l
extern _native64(0xC3675780C92F90F9) void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, float xPos1, float yPos1, float zPos1, float xPos2, float yPos2, float zPos2, float xRot, float yRot, float zRot, float breakForce, bool fixedRot, bool p15, bool collision, bool p17, int p18)l
extern _native64(0x168A09D1B25B0BA4) void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_OVERRIDE_INVERSE_MASS(Entity firstEntityIndex, Entity secondEntityIndex, int firstEntityBoneIndex, int secondEntityBoneIndex, float secondEntityOffsetX, float secondEntityOffsetY, float secondEntityOffsetZ, float firstEntityOffsetX, float firstEntityOffsetY, float firstEntityOffsetZ, float vecRotationX, float vecRotationY, float vecRotationZ, float physicalStrength, bool constrainRotation, bool doInitialWarp, bool collideWithEntity, bool addInitialSeperation, int rotOrder, float invMassScaleA, float invMassScaleB)l
extern _native64(0xF4080490ADC51C6F) void PROCESS_ENTITY_ATTACHMENTS(Entity entity)l
extern _native64(0xFB71170B7E76ACBA) int GET_ENTITY_BONE_INDEX_BY_NAME(Entity entity, const char* boneName)l
extern _native64(0xA72CD9CA74A5ECBA) void CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity)l
extern _native64(0xAE3CBE5BF394C9C9) void DELETE_ENTITY(Entity* entity)l
extern _native64(0x961AC54BF0613F5D) void DETACH_ENTITY(Entity entity, bool dynamic, bool collision)l
extern _native64(0x428CA6DBD1094446) void FREEZE_ENTITY_POSITION(Entity entity, bool toggle)l
extern _native64(0x3910051CCECDB00C) void SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Entity entity, bool toggle)l
extern _native64(0x7FB218262B810701) bool PLAY_ENTITY_ANIM(Entity entity, const char* animName, const char* animDict, float p3, bool loop, bool stayInAnim, bool p6, float delta, any bitset)l
extern _native64(0xC77720A12FE14A86) bool PLAY_SYNCHRONIZED_ENTITY_ANIM(Entity entity, int syncedScene, const char* animation, const char* propName, float p4, float p5, any p6, float p7)l
extern _native64(0xB9C54555ED30FBC4) bool PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, any y2, float z2, const char* p6, const char* p7, float p8, float p9, any p10, float p11)l
extern _native64(0x11E79CAB7183B6F5) bool STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, any y2, float z2)l
extern _native64(0x28004F88151E03E0) bool STOP_ENTITY_ANIM(Entity entity, const char* animation, const char* animGroup, float p3)l
extern _native64(0x43D3807C077261E3) bool STOP_SYNCHRONIZED_ENTITY_ANIM(Entity entity, float p1, bool p2)l
extern _native64(0xEAF4CD9EA3E7E922) bool HAS_ANIM_EVENT_FIRED(Entity entity, Hash actionHash)l
extern _native64(0x07F1BE2BCCAA27A7) bool FIND_ANIM_EVENT_PHASE(const char* animDictionary, const char* animName, const char* p2, any* p3, any* p4)l
extern _native64(0x4487C259F0F70977) void SET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDictionary, const char* animName, float time)l
extern _native64(0x28D1A16553C51776) void SET_ENTITY_ANIM_SPEED(Entity entity, const char* animDictionary, const char* animName, float speedMultiplier)l
extern _native64(0xAD738C3085FE7E11) void SET_ENTITY_AS_MISSION_ENTITY(Entity entity, bool p1, bool p2)l
extern _native64(0xB736A491E64A32CF) void SET_ENTITY_AS_NO_LONGER_NEEDED(Entity* entity)l
extern _native64(0x2595DD4236549CE3) void SET_PED_AS_NO_LONGER_NEEDED(Ped* ped)l
extern _native64(0x629BFA74418D6239) void SET_VEHICLE_AS_NO_LONGER_NEEDED(Vehicle* vehicle)l
extern _native64(0x3AE22DEB5BA5A3E6) void SET_OBJECT_AS_NO_LONGER_NEEDED(Object* object)l
extern _native64(0x1760FFA8AB074D66) void SET_ENTITY_CAN_BE_DAMAGED(Entity entity, bool toggle)l
extern _native64(0xD95CC5D2AB15A09F) bool GET_ENTITY_CAN_BE_DAMAGED(Entity entity)l
extern _native64(0xE22D8FDE858B8119) void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool bCanBeDamaged, int relGroup)l
extern _native64(0x352E2B5CF420BF3B) void SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_SCRIPT_PARTICIPANTS(Entity entity, bool toggle)l
extern _native64(0xD3997889736FD899) void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Entity entity, bool toggle)l
extern _native64(0x1A9205C1B9EE827F) void SET_ENTITY_COLLISION(Entity entity, bool toggle, bool keepPhysics)l
extern _native64(0xCCF1E97BEFDAE480) bool GET_ENTITY_COLLISION_DISABLED(Entity entity)l
extern _native64(0x9EBC85ED0FFFE51C) void SET_ENTITY_COMPLETELY_DISABLE_COLLISION(Entity entity, bool toggle, bool keepPhysics)l
extern _native64(0x06843DA7060A026B) void SET_ENTITY_COORDS(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis, bool clearArea)l
extern _native64(0x621873ECE1178967) void SET_ENTITY_COORDS_WITHOUT_PLANTS_RESET(Entity entity, float xPos, float yPos, float zPos, bool alive, bool deadFlag, bool ragdollFlag, bool clearArea)l
extern _native64(0x239A3351AC1DA385) void SET_ENTITY_COORDS_NO_OFFSET(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x1718DE8E3F2823CA) void SET_ENTITY_DYNAMIC(Entity entity, bool toggle)l
extern _native64(0x8E2530AA8ADA980E) void SET_ENTITY_HEADING(Entity entity, float heading)l
extern _native64(0x6B76DC1F3AE6E6A3) void SET_ENTITY_HEALTH(Entity entity, int health, int p2)l
extern _native64(0x3882114BDE571AD4) void SET_ENTITY_INVINCIBLE(Entity entity, bool toggle)l
extern _native64(0xEA02E132F5C68722) void SET_ENTITY_IS_TARGET_PRIORITY(Entity entity, bool p1, float p2)l
extern _native64(0x7CFBA6A80BDF3874) void SET_ENTITY_LIGHTS(Entity entity, bool toggle)l
extern _native64(0x0DC7CABAB1E9B67E) void SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, bool toggle, any p2)l
extern _native64(0xE9676F61BC0B3321) bool HAS_COLLISION_LOADED_AROUND_ENTITY(Entity entity)l
extern _native64(0x0E46A3FCBDE2A1B1) void SET_ENTITY_MAX_SPEED(Entity entity, float speed)l
extern _native64(0x79F020FF9EDC0748) void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Entity entity, bool toggle)l
extern _native64(0x7022BD828FA0B082) void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool p1, any p2)l
extern _native64(0xFAEE099C6F890BB8) void SET_ENTITY_PROOFS(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool steamProof, bool p7, bool waterProof)l
extern _native64(0xBE8CD9BE829BBEBF) bool GET_ENTITY_PROOFS(Entity entity, bool* bulletProof, bool* fireProof, bool* explosionProof, bool* collisionProof, bool* meleeProof, bool* steamProof, bool* p7, bool* drownProof)l
extern _native64(0x77B21BE7AC540F07) void SET_ENTITY_QUATERNION(Entity entity, float x, float y, float z, float w)l
extern _native64(0x0A50A1EEDAD01E65) void SET_ENTITY_RECORDS_COLLISIONS(Entity entity, bool toggle)l
extern _native64(0x8524A8B0171D5E07) void SET_ENTITY_ROTATION(Entity entity, float pitch, float roll, float yaw, int rotationOrder, bool p5)l
extern _native64(0xEA1C610A04DB6BBB) void SET_ENTITY_VISIBLE(Entity entity, bool toggle, bool p2)l
extern _native64(0xC34BC448DA29F5E9) void SET_ENTITY_WATER_REFLECTION_FLAG(Entity entity, bool toggle)l
extern _native64(0xE66377CDDADA4810) void SET_ENTITY_MIRROR_REFLECTION_FLAG(Entity entity, bool p1)l
extern _native64(0x1C99BB7B6E96D16F) void SET_ENTITY_VELOCITY(Entity entity, float x, float y, float z)l
extern _native64(0x8339643499D1222E) void SET_ENTITY_ANGULAR_VELOCITY(Entity entity, float x, float y, float z)l
extern _native64(0x4A4722448F18EEF5) void SET_ENTITY_HAS_GRAVITY(Entity entity, bool toggle)l
extern _native64(0x5927F96A78577363) void SET_ENTITY_LOD_DIST(Entity entity, int value)l
extern _native64(0x4159C2762B5791D6) int GET_ENTITY_LOD_DIST(Entity entity)l
extern _native64(0x44A0870B7E92D7C0) void SET_ENTITY_ALPHA(Entity entity, int alphaLevel, bool skin)l
extern _native64(0x5A47B3B5E63E94C6) int GET_ENTITY_ALPHA(Entity entity)l
extern _native64(0x9B1E824FFBB7027A) void RESET_ENTITY_ALPHA(Entity entity)l
extern _native64(0x490861B88F4FD846) void RESET_PICKUP_ENTITY_GLOW(Entity entity)l
extern _native64(0xCEA7C8E1B48FF68C) void SET_PICKUP_COLLIDES_WITH_PROJECTILES(any p0, any p1)l
extern _native64(0x5C3B791D580E0BC2) void SET_ENTITY_SORT_BIAS(Entity entity, float p1)l
extern _native64(0xACAD101E1FB66689) void SET_ENTITY_ALWAYS_PRERENDER(Entity entity, bool toggle)l
extern _native64(0x730F5F8D3F0F2050) void SET_ENTITY_RENDER_SCORCHED(Entity entity, bool toggle)l
extern _native64(0x57C5DB656185EAC4) void SET_ENTITY_TRAFFICLIGHT_OVERRIDE(Entity entity, int state)l
extern _native64(0x78E8E3A640178255) void SET_ENTITY_IS_IN_VEHICLE(Entity entity)l
extern _native64(0x92C47782FDA8B2A3) void CREATE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native64(0x033C0F9A64E229AE) void REMOVE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native64(0x8A97BCA30A0CE478) void CREATE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, bool p5)l
extern _native64(0x3A52AE588830BF7F) void CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(float x, float y, float z, float radius, Hash modelHash, bool p5)l
extern _native64(0xD9E3006FB3CBD765) void REMOVE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, bool p5)l
extern _native64(0x150E808B375A385A) void CREATE_FORCED_OBJECT(float x, float y, float z, any p3, Hash modelHash, bool p5)l
extern _native64(0x61B6775E83C0DB6F) void REMOVE_FORCED_OBJECT(float x, float y, float z, float p3, Hash modelHash)l
extern _native64(0xA53ED5520C07654A) void SET_ENTITY_NO_COLLISION_ENTITY(Entity entity1, Entity entity2, bool thisFrameOnly)l
extern _native64(0x295D82A8559F9150) void SET_ENTITY_MOTION_BLUR(Entity entity, bool toggle)l
extern _native64(0xE12ABE5E3A389A6C) void SET_CAN_AUTO_VAULT_ON_ENTITY(Entity entity, bool toggle)l
extern _native64(0xA80AE305E0A3044F) void SET_CAN_CLIMB_ON_ENTITY(Entity entity, bool toggle)l
extern _native64(0xDC6F8601FAF2E893) void SET_WAIT_FOR_COLLISIONS_BEFORE_PROBE(Entity entity, bool toggle)l
extern _native64(0x2C2E3DC128F44309) void SET_ENTITY_NOWEAPONDECALS(Entity entity, bool p1)l
extern _native64(0x1A092BB0C3808B96) void SET_ENTITY_USE_MAX_DISTANCE_FOR_WATER_REFLECTION(Entity entity, bool p1)l
extern _native64(0xCE6294A232D03786) vector3 GET_ENTITY_BONE_ROTATION(Entity entity, int boneIndex)l
extern _native64(0x46F8696933A63C9B) vector3 GET_ENTITY_BONE_POSTION(Entity entity, int boneIndex)l
extern _native64(0xBD8D32550E5CEBFE) vector3 GET_ENTITY_BONE_OBJECT_ROTATION(Entity entity, int boneIndex)l
extern _native64(0xCF1247CC86961FD6) vector3 GET_ENTITY_BONE_OBJECT_POSTION(Entity entity, int boneIndex)l
extern _native64(0xB328DCC3A3AA401B) int GET_ENTITY_BONE_COUNT(Entity entity)l
extern _native64(0x6CE177D014502E8A) void ENABLE_ENTITY_BULLET_COLLISION(Entity entity)l
extern _native64(0xB17BC6453F6CF5AC) void SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2)l
extern _native64(0x68B562E124CC0AEF) void SET_ENTITY_CANT_CAUSE_COLLISION_DAMAGED_ENTITY(Entity entity1, Entity entity2)l
extern _native64(0x36F32DE87082343E) void SET_ALLOW_MIGRATE_TO_SPECTATOR(Entity entity, any p1)l
extern _native64(0x1F922734E259BD26) Entity GET_ENTITY_OF_TYPE_ATTACHED_TO_ENTITY(Entity entity, Hash modelHash)l
extern _native64(0xD7B80E7C3BEFC396) void SET_PICK_UP_BY_CARGOBOB_DISABLED(Entity entity, bool toggle)l
#pragma endregion //}
#pragma region EVENT //{
extern _native64(0xB604A2942ADED0EE) void SET_DECISION_MAKER(Ped ped, Hash name)l
extern _native64(0x4FC9381A7AEE8968) void CLEAR_DECISION_MAKER_EVENT_RESPONSE(Hash name, int eventType)l
extern _native64(0xE42FCDFD0E4196F7) void BLOCK_DECISION_MAKER_EVENT(Hash name, int eventType)l
extern _native64(0xD7CD9CF34F2C99E8) void UNBLOCK_DECISION_MAKER_EVENT(Hash name, int eventType)l
extern _native64(0xD9F8455409B525E9) int ADD_SHOCKING_EVENT_AT_POSITION(int eventType, float x, float y, float z, float duration)l
extern _native64(0x7FD8F3BE76F89422) int ADD_SHOCKING_EVENT_FOR_ENTITY(int eventType, Entity entity, float duration)l
extern _native64(0x1374ABB7C15BAB92) bool IS_SHOCKING_EVENT_IN_SPHERE(int eventType, float x, float y, float z, float radius)l
extern _native64(0x2CDA538C44C6CCE5) bool REMOVE_SHOCKING_EVENT(ScrHandle event)l
extern _native64(0xEAABE8FDFA21274C) void REMOVE_ALL_SHOCKING_EVENTS(bool p0)l
extern _native64(0x340F1415B68AEADE) void REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS()l
extern _native64(0x2F9A292AD0A3BD89) void SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME()l
extern _native64(0x3FD2EC8BF1F1CF30) void SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(int eventType)l
extern _native64(0x5F3B7749C112D552) void SUPPRESS_AGITATION_EVENTS_NEXT_FRAME()l
#pragma endregion //}
#pragma region FILES //{
extern _native64(0x278F76C3B0A8F109) int GET_NUM_TATTOO_SHOP_DLC_ITEMS(int character)l
extern _native64(0xFF56381874F82086) bool GET_TATTOO_SHOP_DLC_ITEM_DATA(int characterType, int decorationIndex, any* outComponent)l
extern _native64(0x10144267DD22866C) int GET_TATTOO_SHOP_DLC_ITEM_INDEX(Hash overlayHash, any p1, int character)l
extern _native64(0x1E8C308FD312C036) void INIT_SHOP_PED_COMPONENT(any* outComponent)l
extern _native64(0xEB0A2B758F7B850F) void INIT_SHOP_PED_PROP(any* outProp)l
extern _native64(0x50F457823CE6EB5F) int SETUP_SHOP_PED_APPAREL_QUERY(int p0, int p1, int p2, int p3)l
extern _native64(0x9BDF59818B1E38C1) int SETUP_SHOP_PED_APPAREL_QUERY_TU(int character, int p1, int p2, bool p3, int p4, int componentId)l
extern _native64(0x249E310B2D920699) void GET_SHOP_PED_QUERY_COMPONENT(int componentId, any* outComponent)l
extern _native64(0x96E2929292A4DB77) int GET_SHOP_PED_QUERY_COMPONENT_INDEX(Hash componentHash)l
extern _native64(0x74C0E2A57EC66760) void GET_SHOP_PED_COMPONENT(Hash componentHash, any* outComponent)l
extern _native64(0xDE44A00999B2837D) void GET_SHOP_PED_QUERY_PROP(int componentId, any* outProp)l
extern _native64(0x6CEBE002E58DEE97) int GET_SHOP_PED_QUERY_PROP_INDEX(Hash componentHash)l
extern _native64(0x5D5CAFF661DDF6FC) void GET_SHOP_PED_PROP(Hash componentHash, any* outProp)l
extern _native64(0x0368B3A838070348) Hash GET_HASH_NAME_FOR_COMPONENT(Entity entity, int componentId, int drawableVariant, int textureVariant)l
extern _native64(0x5D6160275CAEC8DD) Hash GET_HASH_NAME_FOR_PROP(Entity entity, int componentId, int propIndex, int propTextureIndex)l
extern _native64(0xC17AD0E5752BECDA) int GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT(Hash componentHash)l
extern _native64(0xD40AAC51E8E4C663) int GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT(Hash propHash)l
extern _native64(0x6E11F282F11863B6) void GET_VARIANT_COMPONENT(Hash componentHash, int variantComponentIndex, Hash* nameHash, int* enumValue, int* componentType)l
extern _native64(0xD81B7F27BC773E66) void GET_VARIANT_PROP(Hash componentHash, int variantPropIndex, Hash* nameHash, int* enumValue, int* anchorPoint)l
extern _native64(0xC6B9DB42C04DD8C3) int GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT(Hash componentHash)l
extern _native64(0x017568A8182D98A6) int GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT(Hash componentHash)l
extern _native64(0x6C93ED8C2F74859B) void GET_FORCED_COMPONENT(Hash componentHash, int forcedComponentIndex, Hash* nameHash, int* enumValue, int* componentType)l
extern _native64(0xE1CA84EBF72E691D) void GET_FORCED_PROP(Hash componentHash, int forcedPropIndex, Hash* nameHash, int* enumValue, int* anchorPoint)l
extern _native64(0x341DE7ED1D2A1BFD) bool DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG(Hash componentHash, Hash restrictionTagHash, int componentId)l
extern _native64(0x7796B21B76221BC5) bool DOES_CURRENT_PED_COMPONENT_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash)l
extern _native64(0xD726BAB4554DA580) bool DOES_CURRENT_PED_PROP_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash)l
extern _native64(0xF3FBE2D50A6A8C28) int SETUP_SHOP_PED_OUTFIT_QUERY(int character, bool p1)l
extern _native64(0x6D793F03A631FE56) void GET_SHOP_PED_QUERY_OUTFIT(int outfitIndex, any* outfit)l
extern _native64(0xB7952076E444979D) void GET_SHOP_PED_OUTFIT(any p0, any* p1)l
extern _native64(0x073CA26B079F956E) int GET_SHOP_PED_OUTFIT_LOCATE(any p0)l
extern _native64(0xA9F9C2E0FDE11CBB) bool GET_SHOP_PED_OUTFIT_PROP_VARIANT(Hash outfitHash, int variantIndex, any* outPropVariant)l
extern _native64(0x19F2A026EDF0013F) bool GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT(Hash outfitHash, int variantIndex, any* outComponentVariant)l
extern _native64(0xA7A866D21CD2329B) int GET_NUM_DLC_VEHICLES()l
extern _native64(0xECC01B7C5763333C) Hash GET_DLC_VEHICLE_MODEL(int dlcVehicleIndex)l
extern _native64(0x33468EDC08E371F6) bool GET_DLC_VEHICLE_DATA(int dlcVehicleIndex, any* outData)l
extern _native64(0x5549EE11FA22FCF2) int GET_DLC_VEHICLE_FLAGS(int dlcVehicleIndex)l
extern _native64(0xEE47635F352DA367) int GET_NUM_DLC_WEAPONS()l
extern _native64(0x4160B65AE085B5A9) int GET_NUM_DLC_WEAPONS_SP()l
extern _native64(0x79923CD21BECE14E) bool GET_DLC_WEAPON_DATA(int dlcWeaponIndex, any* outData)l
extern _native64(0x310836EE7129BA33) bool GET_DLC_WEAPON_DATA_SP(int dlcWeaponIndex, any* outData)l
extern _native64(0x405425358A7D61FE) int GET_NUM_DLC_WEAPON_COMPONENTS(int dlcWeaponIndex)l
extern _native64(0xAD2A7A6DFF55841B) int GET_NUM_DLC_WEAPON_COMPONENTS_SP(int dlcWeaponIndex)l
extern _native64(0x6CF598A2957C2BF8) bool GET_DLC_WEAPON_COMPONENT_DATA(int dlcWeaponIndex, int dlcWeapCompIndex, any* ComponentDataPtr)l
extern _native64(0x31D5E073B6F93CDC) bool GET_DLC_WEAPON_COMPONENT_DATA_SP(int dlcWeaponIndex, int dlcWeapCompIndex, any* ComponentDataPtr)l
extern _native64(0xD4D7B033C3AA243C) bool IS_CONTENT_ITEM_LOCKED(Hash itemHash)l
extern _native64(0x0564B9FF9631B82C) bool IS_DLC_VEHICLE_MOD(Hash hash)l
extern _native64(0xC098810437312FFF) Hash GET_DLC_VEHICLE_MOD_LOCK_HASH(Hash hash)l
extern _native64(0x6BEDF5769AC2DC07) void EXECUTE_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash)l
extern _native64(0x3C1978285B036B25) void REVERT_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash)l
#pragma endregion //}
#pragma region FIRE //{
extern _native64(0x6B83617E04503888) FireId START_SCRIPT_FIRE(float X, float Y, float Z, int maxChildren, bool isGasFire)l
extern _native64(0x7FF548385680673F) void REMOVE_SCRIPT_FIRE(FireId fireHandle)l
extern _native64(0xF6A9D9708F6F23DF) FireId START_ENTITY_FIRE(Entity entity)l
extern _native64(0x7F0DD2EBBB651AFF) void STOP_ENTITY_FIRE(Entity entity)l
extern _native64(0x28D3FED7190D3A0B) bool IS_ENTITY_ON_FIRE(Entity entity)l
extern _native64(0x50CAD495A460B305) int GET_NUMBER_OF_FIRES_IN_RANGE(float x, float y, float z, float radius)l
extern _native64(0x8F390AC4155099BA) void SET_FLAMMABILITY_MULTIPLIER(float p0)l
extern _native64(0x056A8A219B8E829F) void STOP_FIRE_IN_RANGE(float x, float y, float z, float radius)l
extern _native64(0x352A9F6BCF90081F) bool GET_CLOSEST_FIRE_POS(vector3* outPosition, float x, float y, float z)l
extern _native64(0xE3AD2BDBAEE269AC) void ADD_EXPLOSION(float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake, bool noDamage)l
extern _native64(0x172AA1B624FA1013) void ADD_OWNED_EXPLOSION(Ped ped, float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native64(0x36DD3FE58B5E5212) void ADD_EXPLOSION_WITH_USER_VFX(float x, float y, float z, int explosionType, Hash explosionFx, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native64(0x2E2EBA0EE7CED0E0) bool IS_EXPLOSION_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x6070104B699B2EF4) bool IS_EXPLOSION_ACTIVE_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0xAB0F816885B0E483) bool IS_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius)l
extern _native64(0xB3CD51E3DB86F176) Entity GET_OWNER_OF_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius)l
extern _native64(0xA079A6C51525DC4B) bool IS_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float width)l
extern _native64(0x14BA4BA137AF6CEC) Entity GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float radius)l
#pragma endregion //}
#pragma region GRAPHICS //{
extern _native64(0x175B6BFC15CDD0C5) void SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(bool enabled)l
extern _native64(0x7FDFADE676AA3CB0) void DRAW_DEBUG_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha)l
extern _native64(0xD8B9A8AC5608FF94) void DRAW_DEBUG_LINE_WITH_TWO_COLOURS(float x1, float y1, float z1, float x2, float y2, float z2, int r1, int g1, int b1, int r2, int g2, int b2, int alpha1, int alpha2)l
extern _native64(0xAAD68E1AB39DA632) void DRAW_DEBUG_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, int alpha)l
extern _native64(0x083A2CA4F2E573BD) void DRAW_DEBUG_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha)l
extern _native64(0x73B1189623049839) void DRAW_DEBUG_CROSS(float x, float y, float z, float size, int red, int green, int blue, int alpha)l
extern _native64(0x3903E216620488E8) void DRAW_DEBUG_TEXT(const char* text, float x, float y, float z, int red, int green, int blue, int alpha)l
extern _native64(0xA3BB2E9555C05A8F) void DRAW_DEBUG_TEXT_2D(const char* text, float x, float y, float z, int red, int green, int blue, int alpha)l
extern _native64(0x6B7256074AE34680) void DRAW_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha)l
extern _native64(0xAC26716048436851) void DRAW_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha)l
extern _native64(0x29280002282F1928) void DRAW_TEXTURED_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha, const char* textureDict, const char* textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3)l
extern _native64(0x736D7AA1B750856B) void DRAW_TEXTURED_POLY_WITH_THREE_COLOURS(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float red1, float green1, float blue1, int alpha1, float red2, float green2, float blue2, int alpha2, float red3, float green3, float blue3, int alpha3, const char* textureDict, const char* textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3)l
extern _native64(0xD3A9971CADAC7252) void DRAW_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha)l
extern _native64(0x23BA6B0C2AD7B0D3) void SET_BACKFACECULLING(bool toggle)l
extern _native64(0xC5C8F970D4EDFF71) void SET_DEPTHWRITING(bool toggle)l
extern _native64(0x1DD2139A9A20DCE8) bool BEGIN_TAKE_MISSION_CREATOR_PHOTO()l
extern _native64(0x90A78ECAA4E78453) int GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO()l
extern _native64(0x0A46AF8A78DC5E0A) void FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO()l
extern _native64(0x4862437A486F91B0) bool LOAD_MISSION_CREATOR_PHOTO(any* p0, any p1, any p2, any p3)l
extern _native64(0x1670F8D05056F257) int GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO(any* p0)l
extern _native64(0x7FA5D82B8F58EC06) bool BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW()l
extern _native64(0x5B0316762AFD4A64) int GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW()l
extern _native64(0x346EF3ECAAAB149E) void FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW()l
extern _native64(0xA67C35C56EB1BD9D) bool BEGIN_TAKE_HIGH_QUALITY_PHOTO()l
extern _native64(0x0D6CA79EEEBD8CA3) int GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO()l
extern _native64(0xD801CC02177FA3F1) void FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO()l
extern _native64(0x1BBC135A4D25EDDE) void SET_TAKEN_PHOTO_IS_MUGSHOT(bool toggle)l
extern _native64(0xF3F776ADA161E47D) void SET_ARENA_THEME_AND_VARIATION_FOR_TAKEN_PHOTO(any p0, int p1)l
extern _native64(0xADD6627C4D325458) void SET_ON_ISLAND_X_FOR_TAKEN_PHOTO(any p0)l
extern _native64(0x3DEC726C25A11BAC) bool SAVE_HIGH_QUALITY_PHOTO(int unused)l
extern _native64(0x0C0C4E81E1AC60A0) int GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO()l
extern _native64(0x759650634F07B6B4) bool BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO(any p0)l
extern _native64(0xCB82A0BF0E3E3265) int GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO(int p0)l
extern _native64(0x6A12D88881435DCA) void FREE_MEMORY_FOR_LOW_QUALITY_PHOTO()l
extern _native64(0x1072F115DAB0717E) void DRAW_LOW_QUALITY_PHOTO_TO_PHONE(bool p0, bool p1)l
extern _native64(0x34D23450F028B0BF) int GET_MAXIMUM_NUMBER_OF_PHOTOS()l
extern _native64(0xDC54A7AF8B3A14EF) int GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS()l
extern _native64(0x473151EBC762C6DA) int GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS()l
extern _native64(0x2A893980E96B659A) bool QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS(any p0)l
extern _native64(0xF5BED327CEA362B1) int GET_STATUS_OF_SORTED_LIST_OPERATION(any p0)l
extern _native64(0x4AF92ACD3141D96C) void CLEAR_STATUS_OF_SORTED_LIST_OPERATION()l
extern _native64(0xE791DF1F73ED2C8B) bool DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO(any p0)l
extern _native64(0xEC72C258667BE5EA) bool LOAD_HIGH_QUALITY_PHOTO(any p0)l
extern _native64(0x40AFB081F8ADD4EE) int GET_LOAD_HIGH_QUALITY_PHOTO_STATUS(int p0)l
extern _native64(0xF49E9A9716A04595) void DRAW_LIGHT_WITH_RANGEEX(float x, float y, float z, int r, int g, int b, float range, float intensity, float shadow)l
extern _native64(0xF2A1B2771A01DBD4) void DRAW_LIGHT_WITH_RANGE(float posX, float posY, float posZ, int colorR, int colorG, int colorB, float range, float intensity)l
extern _native64(0xD0F64B265C8C8B33) void DRAW_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float hardness, float radius, float falloff)l
extern _native64(0x5BCA583A583194DB) void DRAW_SHADOWED_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float roundness, float radius, float falloff, int shadowId)l
extern _native64(0xC9B18B4619F48F7B) void FADE_UP_PED_LIGHT(float p0)l
extern _native64(0xDEADC0DEDEADC0DE) void UPDATE_LIGHTS_ON_ENTITY(Entity entity)l
extern _native64(0x9641588DAB93B4B5) void SET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE(any p0)l
extern _native64(0x393BD2275CEB7793) float GET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE()l
extern _native64(0x28477EC23D892089) void DRAW_MARKER(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, bool bobUpAndDown, bool faceCamera, int p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts)l
extern _native64(0xE82728F0DE75D13A) void DRAW_MARKER_EX(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, bool bobUpAndDown, bool faceCamera, any p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts, bool p24, bool p25)l
extern _native64(0x799017F9E3B10112) void DRAW_MARKER_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, float alpha)l
extern _native64(0x0134F0835AB6BFCB) int CREATE_CHECKPOINT(int type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float diameter, int red, int green, int blue, int alpha, int reserved)l
extern _native64(0x4B5B4DA5D79F1943) void SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE(int checkpoint, float scale)l
extern _native64(0x44621483FF966526) void SET_CHECKPOINT_INSIDE_CYLINDER_SCALE(int checkpoint, float scale)l
extern _native64(0x2707AAE9D9297D89) void SET_CHECKPOINT_CYLINDER_HEIGHT(int checkpoint, float nearHeight, float farHeight, float radius)l
extern _native64(0x7167371E8AD747F7) void SET_CHECKPOINT_RGBA(int checkpoint, int red, int green, int blue, int alpha)l
extern _native64(0xB9EA40907C680580) void SET_CHECKPOINT_RGBA2(int checkpoint, int red, int green, int blue, int alpha)l
extern _native64(0xF51D36185993515D) void SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM(int checkpoint, float posX, float posY, float posZ, float unkX, float unkY, float unkZ)l
extern _native64(0xFCF6788FC4860CD4) void SET_CHECKPOINT_FORCE_OLD_ARROW_POINTING(int checkpoint)l
extern _native64(0x615D3925E87A3B26) void SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT(int checkpoint)l
extern _native64(0xDB1EA9411C8911EC) void SET_CHECKPOINT_FORCE_DIRECTION(int checkpoint)l
extern _native64(0x3C788E7F6438754D) void SET_CHECKPOINT_DIRECTION(int checkpoint, float posX, float posY, float posZ)l
extern _native64(0xF5ED37F54CD4D52E) void DELETE_CHECKPOINT(int checkpoint)l
extern _native64(0x22A249A53034450A) void DONT_RENDER_IN_GAME_UI(bool p0)l
extern _native64(0xDC459CFA0CCE245B) void FORCE_RENDER_IN_GAME_UI(bool toggle)l
extern _native64(0xDFA2EF8E04127DD5) void REQUEST_STREAMED_TEXTURE_DICT(const char* textureDict, bool p1)l
extern _native64(0x0145F696AAAAD2E4) bool HAS_STREAMED_TEXTURE_DICT_LOADED(const char* textureDict)l
extern _native64(0xBE2CACCF5A8AA805) void SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(const char* textureDict)l
extern _native64(0x3A618A217E5154F0) void DRAW_RECT(float x, float y, float width, float height, int r, int g, int b, int a, bool p8)l
extern _native64(0xC6372ECD45D73BCD) void SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(bool toggle)l
extern _native64(0x61BB1D9B3A95D802) void SET_SCRIPT_GFX_DRAW_ORDER(int drawOrder)l
extern _native64(0xB8A850F20A067EB6) void SET_SCRIPT_GFX_ALIGN(int horizontalAlign, int verticalAlign)l
extern _native64(0xE3A3DB414A373DAB) void RESET_SCRIPT_GFX_ALIGN()l
extern _native64(0xF5A2C681787E579D) void SET_SCRIPT_GFX_ALIGN_PARAMS(float x, float y, float w, float h)l
extern _native64(0x6DD8F5AA635EB4B2) void GET_SCRIPT_GFX_ALIGN_POSITION(float x, float y, float* calculatedX, float* calculatedY)l
extern _native64(0xBAF107B6BB2C97F0) float GET_SAFE_ZONE_SIZE()l
extern _native64(0xE7FFAE5EBF23D890) void DRAW_SPRITE(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, bool p11, any p12)l
extern _native64(0x2D3B147AFAD49DE0) void DRAW_SPRITE_ARX(const char* textureDict, const char* textureName, float x, float y, float width, float height, float p6, int red, int green, int blue, int alpha, any p11, any p12)l
extern _native64(0x2BC54A8188768488) void DRAW_SPRITE_NAMED_RENDERTARGET(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, any p11)l
extern _native64(0x95812F9B26074726) void DRAW_SPRITE_ARX_WITH_UV(const char* textureDict, const char* textureName, float x, float y, float width, float height, float u1, float v1, float u2, float v2, float heading, int red, int green, int blue, int alpha, any p15)l
extern _native64(0x9CD43EEE12BF4DD0) int ADD_ENTITY_ICON(Entity entity, const char* icon)l
extern _native64(0xE0E8BEECCA96BA31) void SET_ENTITY_ICON_VISIBILITY(Entity entity, bool toggle)l
extern _native64(0x1D5F595CCAE2E238) void SET_ENTITY_ICON_COLOR(Entity entity, int red, int green, int blue, int alpha)l
extern _native64(0xAA0008F3BBB8F416) void SET_DRAW_ORIGIN(float x, float y, float z, bool p3)l
extern _native64(0xFF0B610F6BE0D7AF) void CLEAR_DRAW_ORIGIN()l
extern _native64(0x338D9F609FD632DB) int SET_BINK_MOVIE(const char* name)l
extern _native64(0x70D2CC8A542A973C) void PLAY_BINK_MOVIE(int binkMovie)l
extern _native64(0x63606A61DE68898A) void STOP_BINK_MOVIE(int binkMovie)l
extern _native64(0x04D950EEFA4EED8C) void RELEASE_BINK_MOVIE(int binkMovie)l
extern _native64(0x7118E83EEB9F7238) void DRAW_BINK_MOVIE(int binkMovie, float p1, float p2, float p3, float p4, float p5, int r, int g, int b, int a)l
extern _native64(0x0CB6B3446855B57A) void SET_BINK_MOVIE_TIME(int binkMovie, float progress)l
extern _native64(0x8E17DDD6B9D5BF29) float GET_BINK_MOVIE_TIME(int binkMovie)l
extern _native64(0xAFF33B1178172223) void SET_BINK_MOVIE_VOLUME(int binkMovie, float value)l
extern _native64(0x845BAD77CC770633) void ATTACH_TV_AUDIO_TO_ENTITY(Entity entity)l
extern _native64(0xF816F2933752322D) void SET_BINK_MOVIE_AUDIO_FRONTEND(int binkMovie, bool p1)l
extern _native64(0x113D2C5DC57E1774) void SET_TV_AUDIO_FRONTEND(bool toggle)l
extern _native64(0x6805D58CAA427B72) void SET_BINK_SHOULD_SKIP(int binkMovie, bool bShouldSkip)l
extern _native64(0xB66064452270E8F1) int LOAD_MOVIE_MESH_SET(const char* movieMeshSetName)l
extern _native64(0xEB119AA014E89183) void RELEASE_MOVIE_MESH_SET(int movieMeshSet)l
extern _native64(0x9B6E70C5CEEF4EEB) int QUERY_MOVIE_MESH_SET_STATE(any p0)l
extern _native64(0x888D57E407E63624) void GET_SCREEN_RESOLUTION(int* x, int* y)l
extern _native64(0x873C9F3104101DD3) void GET_ACTUAL_SCREEN_RESOLUTION(int* x, int* y)l
extern _native64(0xF1307EF624A80D87) float GET_ASPECT_RATIO(bool b)l
extern _native64(0xB2EBE8CBC58B90E9) float GET_SCREEN_ASPECT_RATIO()l
extern _native64(0x30CF4BDA4FCB1905) bool GET_IS_WIDESCREEN()l
extern _native64(0x84ED31191CC5D2C9) bool GET_IS_HIDEF()l
extern _native64(0xEFABC7722293DA7C) void ADJUST_NEXT_POS_SIZE_AS_NORMALIZED_16_9()l
extern _native64(0x18F621F7A5B1F85D) void SET_NIGHTVISION(bool toggle)l
extern _native64(0x35FB78DC42B7BD21) bool GET_REQUESTINGNIGHTVISION()l
extern _native64(0x2202A3F42C8E5F79) bool GET_USINGNIGHTVISION()l
extern _native64(0xEF398BEEE4EF45F9) void SET_EXPOSURETWEAK(bool toggle)l
extern _native64(0x814AF7DCAACC597B) void FORCE_EXPOSURE_READBACK(bool toggle)l
extern _native64(0x43FA7CBE20DAB219) void OVERRIDE_NIGHTVISION_LIGHT_RANGE(float p0)l
extern _native64(0xE787BF1C5CF823C9) void SET_NOISEOVERIDE(bool toggle)l
extern _native64(0xCB6A7C3BB17A0C67) void SET_NOISINESSOVERIDE(float value)l
extern _native64(0x34E82F05DF2974F5) bool GET_SCREEN_COORD_FROM_WORLD_COORD(float worldX, float worldY, float worldZ, float* screenX, float* screenY)l
extern _native64(0x35736EE65BD00C11) vector3 GET_TEXTURE_RESOLUTION(const char* textureDict, const char* textureName)l
extern _native64(0x95EB5E34F821BABE) bool OVERRIDE_PED_CREW_LOGO_TEXTURE(Ped ped, const char* txd, const char* txn)l
extern _native64(0xE2892E7E55D7073A) void SET_DISTANCE_BLUR_STRENGTH_OVERRIDE(float p0)l
extern _native64(0x0AB84296FED9CFC6) void SET_FLASH(float p0, float p1, float fadeIn, float duration, float fadeOut)l
extern _native64(0x3669F1B198DCAA4F) void DISABLE_OCCLUSION_THIS_FRAME()l
extern _native64(0x1268615ACE24D504) void SET_ARTIFICIAL_LIGHTS_STATE(bool state)l
extern _native64(0xE2B187C0939B3D32) void SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(bool toggle)l
extern _native64(0xC35A6D07C93802B2) void DISABLE_HDTEX_THIS_FRAME()l
extern _native64(0xE2C9439ED45DEA60) int CREATE_TRACKED_POINT()l
extern _native64(0x164ECBB3CF750CB0) void SET_TRACKED_POINT_INFO(int point, float x, float y, float z, float radius)l
extern _native64(0xC45CCDAAC9221CA8) bool IS_TRACKED_POINT_VISIBLE(int point)l
extern _native64(0xB25DC90BAD56CA42) void DESTROY_TRACKED_POINT(int point)l
extern _native64(0xBE197EAA669238F4) int SET_GRASS_CULL_SPHERE(float p0, float p1, float p2, float p3)l
extern _native64(0x61F95E5BB3E0A8C6) void REMOVE_GRASS_CULL_SPHERE(int handle)l
extern _native64(0xAE51BC858F32BA66) void PROCGRASS_ENABLE_CULLSPHERE(int handle, float x, float y, float z, float scale)l
extern _native64(0x649C97D52332341A) void PROCGRASS_DISABLE_CULLSPHERE(int handle)l
extern _native64(0x2C42340F916C5930) bool PROCGRASS_IS_CULLSPHERE_ENABLED(int handle)l
extern _native64(0x14FC5833464340A8) void PROCGRASS_ENABLE_AMBSCALESCAN()l
extern _native64(0x0218BA067D249DEA) void PROCGRASS_DISABLE_AMBSCALESCAN()l
extern _native64(0x1612C45F9E3E0D44) void DISABLE_PROCOBJ_CREATION()l
extern _native64(0x5DEBD9C4DC995692) void ENABLE_PROCOBJ_CREATION()l
extern _native64(0xAAE9BE70EC7C69AB) void GRASSBATCH_ENABLE_FLATTENING_EXT_IN_SPHERE(float x, float y, float z, any p3, float p4, float p5, float p6, float scale)l
extern _native64(0x6D955F6A9E0295B1) void GRASSBATCH_ENABLE_FLATTENING_IN_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6)l
extern _native64(0x302C91AB2D477F7E) void GRASSBATCH_DISABLE_FLATTENING()l
extern _native64(0x03FC694AE06C5A20) void CASCADE_SHADOWS_INIT_SESSION()l
extern _native64(0xD2936CAB8B58FCBD) void CASCADE_SHADOWS_SET_CASCADE_BOUNDS(any p0, bool p1, float p2, float p3, float p4, float p5, bool p6, float p7)l
extern _native64(0x5F0F3F56635809EF) void CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE(float p0)l
extern _native64(0x5E9DAF5A20F15908) void CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE(float p0)l
extern _native64(0x36F6626459D91457) void CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT(float p0)l
extern _native64(0x259BA6D4E6F808F1) void CASCADE_SHADOWS_SET_BOUND_POSITION(any p0)l
extern _native64(0x80ECBC0C856D3B0B) void CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER(bool toggle)l
extern _native64(0x25FC3E33A31AD0C9) void CASCADE_SHADOWS_SET_SCREEN_SIZE_CHECK_ENABLED(bool p0)l
extern _native64(0xB11D94BC55F41932) void CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE(const char* type)l
extern _native64(0x27CB772218215325) void CASCADE_SHADOWS_CLEAR_SHADOW_SAMPLE_TYPE()l
extern _native64(0x6DDBF9DFFC4AC080) void CASCADE_SHADOWS_SET_AIRCRAFT_MODE(bool p0)l
extern _native64(0xD39D13C9FEBF0511) void CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE(bool p0)l
extern _native64(0x02AC28F3A01FA04A) void CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE(float p0)l
extern _native64(0x0AE73D8DF3A762B2) void CASCADE_SHADOWS_ENABLE_FREEZER(bool p0)l
extern _native64(0xCA465D9CC0D231BA) void WATER_REFLECTION_SET_SCRIPT_OBJECT_VISIBILITY(any p0)l
extern _native64(0xA51C4B86B71652AE) void GOLF_TRAIL_SET_ENABLED(bool toggle)l
extern _native64(0x312342E1A4874F3F) void GOLF_TRAIL_SET_PATH(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8)l
extern _native64(0x2485D34E50A22E84) void GOLF_TRAIL_SET_RADIUS(float p0, float p1, float p2)l
extern _native64(0x12995F2E53FFA601) void GOLF_TRAIL_SET_COLOUR(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)l
extern _native64(0xDBAA5EC848BA2D46) void GOLF_TRAIL_SET_TESSELLATION(int p0, int p1)l
extern _native64(0xC0416B061F2B7E5E) void GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE(bool p0)l
extern _native64(0xB1BB03742917A5D6) void GOLF_TRAIL_SET_FIXED_CONTROL_POINT(int type, float xPos, float yPos, float zPos, float p4, int red, int green, int blue, int alpha)l
extern _native64(0x9CFDD90B2B844BF7) void GOLF_TRAIL_SET_SHADER_PARAMS(float p0, float p1, float p2, float p3, float p4)l
extern _native64(0x06F761EA47C1D3ED) void GOLF_TRAIL_SET_FACING(bool p0)l
extern _native64(0xA4819F5E23E2FFAD) float GOLF_TRAIL_GET_MAX_HEIGHT()l
extern _native64(0xA4664972A9B8F8BA) vector3 GOLF_TRAIL_GET_VISUAL_CONTROL_POINT(int p0)l
extern _native64(0x7E08924259E08CE0) void SET_SEETHROUGH(bool toggle)l
extern _native64(0x44B80ABAB9D80BD3) bool GET_USINGSEETHROUGH()l
extern _native64(0x70A64C0234EF522C) void SEETHROUGH_RESET()l
extern _native64(0xA78DE25577300BA1) void SEETHROUGH_SET_FADE_STARTDISTANCE(float distance)l
extern _native64(0x9D75795B9DC6EBBF) void SEETHROUGH_SET_FADE_ENDDISTANCE(float distance)l
extern _native64(0x43DBAE39626CE83F) float SEETHROUGH_GET_MAX_THICKNESS()l
extern _native64(0x0C8FAC83902A62DF) void SEETHROUGH_SET_MAX_THICKNESS(float thickness)l
extern _native64(0xFF5992E1C9E65D05) void SEETHROUGH_SET_NOISE_MIN(float amount)l
extern _native64(0xFEBFBFDFB66039DE) void SEETHROUGH_SET_NOISE_MAX(float amount)l
extern _native64(0x19E50EB6E33E1D28) void SEETHROUGH_SET_HILIGHT_INTENSITY(float intensity)l
extern _native64(0x1636D7FC127B10D2) void SEETHROUGH_SET_HIGHLIGHT_NOISE(float noise)l
extern _native64(0xD7D0B00177485411) void SEETHROUGH_SET_HEATSCALE(int index, float heatScale)l
extern _native64(0x1086127B3A63505E) void SEETHROUGH_SET_COLOR_NEAR(int red, int green, int blue)l
extern _native64(0xB3C641F3630BF6DA) void SET_MOTIONBLUR_MAX_VEL_SCALER(float p0)l
extern _native64(0xE59343E9E96529E7) float GET_MOTIONBLUR_MAX_VEL_SCALER()l
extern _native64(0x6A51F78772175A51) void SET_FORCE_MOTIONBLUR(bool toggle)l
extern _native64(0xE63D7C6EECECB66B) void TOGGLE_PLAYER_DAMAGE_OVERLAY(bool toggle)l
extern _native64(0xE3E2C1B4C59DBC77) void RESET_ADAPTATION(int p0)l
extern _native64(0xA328A24AAA6B7FDC) bool TRIGGER_SCREENBLUR_FADE_IN(float transitionTime)l
extern _native64(0xEFACC8AEF94430D5) bool TRIGGER_SCREENBLUR_FADE_OUT(float transitionTime)l
extern _native64(0xDE81239437E8C5A8) void DISABLE_SCREENBLUR_FADE()l
extern _native64(0x5CCABFFCA31DDE33) float GET_SCREENBLUR_FADE_CURRENT_TIME()l
extern _native64(0x7B226C785A52A0A9) bool IS_SCREENBLUR_FADE_RUNNING()l
extern _native64(0xDFC252D8A3E15AB7) void TOGGLE_PAUSED_RENDERPHASES(bool toggle)l
extern _native64(0xEB3DAC2C86001E5E) bool GET_TOGGLE_PAUSED_RENDERPHASES_STATUS()l
extern _native64(0xE1C8709406F2C41C) void RESET_PAUSED_RENDERPHASES()l
extern _native64(0x851CD923176EBA7C) void GRAB_PAUSEMENU_OWNERSHIP()l
extern _native64(0xBA3D65906822BED5) void SET_HIDOF_OVERRIDE(bool p0, bool p1, float nearplaneOut, float nearplaneIn, float farplaneOut, float farplaneIn)l
extern _native64(0xB569F41F3E7E83A4) void SET_LOCK_ADAPTIVE_DOF_DISTANCE(bool p0)l
extern _native64(0x7AC24EAB6D74118D) bool PHONEPHOTOEDITOR_TOGGLE(bool p0)l
extern _native64(0xBCEDB009461DA156) bool PHONEPHOTOEDITOR_IS_ACTIVE()l
extern _native64(0x27FEB5254759CDE3) bool PHONEPHOTOEDITOR_SET_FRAME_TXD(const char* textureDict, bool p1)l
extern _native64(0x25129531F77B9ED3) bool START_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0xF56B8137DF10135D) bool START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11)l
extern _native64(0x0E7E72961BA18619) bool START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0xA41B6A43642AC2CF) bool START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0x0D53A3B8DA0809D2) bool START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0xC95EB1DB6E92113D) bool START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0x02B1F2A72E0F5325) bool START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0x26143A59EF48B262) void SET_PARTICLE_FX_NON_LOOPED_COLOUR(float r, float g, float b)l
extern _native64(0x77168D722C58B2FC) void SET_PARTICLE_FX_NON_LOOPED_ALPHA(float alpha)l
extern _native64(0xB7EF5850C39FABCA) void SET_PARTICLE_FX_NON_LOOPED_SCALE(float scale)l
extern _native64(0x1E2E01C00837D26E) void SET_PARTICLE_FX_NON_LOOPED_EMITTER_SIZE(float p0, float p1, float scale)l
extern _native64(0x8CDE909A0370BB3A) void SET_PARTICLE_FX_FORCE_VEHICLE_INTERIOR(bool toggle)l
extern _native64(0xE184F4F0DC5910E7) int START_PARTICLE_FX_LOOPED_AT_COORD(const char* effectName, float x, float y, float z, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11)l
extern _native64(0xF28DA9F38CD1787C) int START_PARTICLE_FX_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x1AE42C1660FD6517) int START_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0xC6EB449E33977F0B) int START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x6F60E89A7B64EE1D) int START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, float r, float g, float b, float a)l
extern _native64(0xDDE23F30CC5A0F03) int START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis, float r, float g, float b, float a)l
extern _native64(0x8F75998877616996) void STOP_PARTICLE_FX_LOOPED(int ptfxHandle, bool p1)l
extern _native64(0xC401503DFE8D53CF) void REMOVE_PARTICLE_FX(int ptfxHandle, bool p1)l
extern _native64(0xB8FEAEEBCC127425) void REMOVE_PARTICLE_FX_FROM_ENTITY(Entity entity)l
extern _native64(0xDD19FA1C6D657305) void REMOVE_PARTICLE_FX_IN_RANGE(float X, float Y, float Z, float radius)l
extern _native64(0xBA0127DA25FD54C9) void FORCE_PARTICLE_FX_IN_VEHICLE_INTERIOR(any p0, any p1)l
extern _native64(0x74AFEF0D2E1E409B) bool DOES_PARTICLE_FX_LOOPED_EXIST(int ptfxHandle)l
extern _native64(0xF7DDEBEC43483C43) void SET_PARTICLE_FX_LOOPED_OFFSETS(int ptfxHandle, float x, float y, float z, float rotX, float rotY, float rotZ)l
extern _native64(0x5F0C4B5B1C393BE2) void SET_PARTICLE_FX_LOOPED_EVOLUTION(int ptfxHandle, const char* propertyName, float amount, bool noNetwork)l
extern _native64(0x7F8F65877F88783B) void SET_PARTICLE_FX_LOOPED_COLOUR(int ptfxHandle, float r, float g, float b, bool p4)l
extern _native64(0x726845132380142E) void SET_PARTICLE_FX_LOOPED_ALPHA(int ptfxHandle, float alpha)l
extern _native64(0xB44250AAA456492D) void SET_PARTICLE_FX_LOOPED_SCALE(int ptfxHandle, float scale)l
extern _native64(0xDCB194B85EF7B541) void SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST(int ptfxHandle, float range)l
extern _native64(0xEEC4047028426510) void SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(bool p0)l
extern _native64(0xACEE6F360FC1F6B6) void SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(Vehicle vehicle, bool p1)l
extern _native64(0x96EF97DAEB89BEF5) void SET_PARTICLE_FX_SHOOTOUT_BOAT(any p0)l
extern _native64(0x2A251AA48B2B46DB) void CLEAR_PARTICLE_FX_SHOOTOUT_BOAT()l
extern _native64(0x908311265D42A820) void SET_PARTICLE_FX_BLOOD_SCALE(any p0)l
extern _native64(0xCFD16F0DB5A3535C) void DISABLE_IN_WATER_PTFX(bool toggle)l
extern _native64(0x5F6DF3D92271E8A1) void DISABLE_DOWNWASH_PTFX(bool toggle)l
extern _native64(0x2B40A97646381508) void SET_PARTICLE_FX_SLIPSTREAM_LODRANGE_SCALE(float scale)l
extern _native64(0xD821490579791273) void ENABLE_CLOWN_BLOOD_VFX(bool toggle)l
extern _native64(0x9DCE1F0F78260875) void ENABLE_ALIEN_BLOOD_VFX(bool toggle)l
extern _native64(0x27E32866E9A5C416) void SET_PARTICLE_FX_BULLET_IMPACT_SCALE(float scale)l
extern _native64(0xBB90E12CAC1DAB25) void SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE(float p0)l
extern _native64(0xCA4AE345A153D573) void SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT(bool p0)l
extern _native64(0x54E22EA2C1956A8D) void SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE(float p0)l
extern _native64(0x949F397A288B28B3) void SET_PARTICLE_FX_FOOT_LODRANGE_SCALE(float p0)l
extern _native64(0xBA3D194057C79A7B) void SET_PARTICLE_FX_FOOT_OVERRIDE_NAME(const char* p0)l
extern _native64(0x5DBF05DB5926D089) void SET_SKIDMARK_RANGE_SCALE(float scale)l
extern _native64(0xC6730E0D14E50703) void SET_PTFX_FORCE_VEHICLE_INTERIOR_FLAG(any p0)l
extern _native64(0x170911F37F646F29) void REGISTER_POSTFX_BULLET_IMPACT(float weaponWorldPosX, float weaponWorldPosY, float weaponWorldPosZ, float intensity)l
extern _native64(0x9B079E5221D984D3) void FORCE_POSTFX_BULLET_IMPACTS_AFTER_HUD(bool p0)l
extern _native64(0x6C38AF3693A69A91) void USE_PARTICLE_FX_ASSET(const char* name)l
extern _native64(0xEA1E2D93F6F75ED9) void SET_PARTICLE_FX_OVERRIDE(const char* oldAsset, const char* newAsset)l
extern _native64(0x89C8553DD3274AAE) void RESET_PARTICLE_FX_OVERRIDE(const char* name)l
extern _native64(0xA46B73FAA3460AE1) void SET_WEATHER_PTFX_USE_OVERRIDE_SETTINGS(bool p0)l
extern _native64(0xF78B803082D4386F) void SET_WEATHER_PTFX_OVERRIDE_CURR_LEVEL(float p0)l
extern _native64(0x9C30613D50A6ADEF) void WASH_DECALS_IN_RANGE(float x, float y, float z, float range, float p4)l
extern _native64(0x5B712761429DBC14) void WASH_DECALS_FROM_VEHICLE(Vehicle vehicle, float p1)l
extern _native64(0xD77EDADB0420E6E0) void FADE_DECALS_IN_RANGE(float x, float y, float z, float p3, float p4)l
extern _native64(0x5D6B2D4830A67C62) void REMOVE_DECALS_IN_RANGE(float x, float y, float z, float range)l
extern _native64(0xCCF71CBDDF5B6CB9) void REMOVE_DECALS_FROM_OBJECT(Object obj)l
extern _native64(0xA6F6F70FDC6D144C) void REMOVE_DECALS_FROM_OBJECT_FACING(Object obj, float x, float y, float z)l
extern _native64(0xE91F1B65F2B48D57) void REMOVE_DECALS_FROM_VEHICLE(Vehicle vehicle)l
extern _native64(0xB302244A1839BDAD) int ADD_DECAL(int decalType, float posX, float posY, float posZ, float p4, float p5, float p6, float p7, float p8, float p9, float width, float height, float rCoef, float gCoef, float bCoef, float opacity, float timeout, bool p17, bool p18, bool p19)l
extern _native64(0x4F5212C7AD880DF8) int ADD_PETROL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency)l
extern _native64(0x126D7F89FE859A5E) int ADD_OIL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency)l
extern _native64(0x99AC7F0D8B9C893D) void START_PETROL_TRAIL_DECALS(float p0)l
extern _native64(0x967278682CB6967A) void ADD_PETROL_TRAIL_DECAL_INFO(float x, float y, float z, float p3)l
extern _native64(0x0A123435A26C36CD) void END_PETROL_TRAIL_DECALS()l
extern _native64(0xED3F346429CCD659) void REMOVE_DECAL(int decal)l
extern _native64(0xC694D74949CAFD0C) bool IS_DECAL_ALIVE(int decal)l
extern _native64(0x323F647679A09103) float GET_DECAL_WASH_LEVEL(int decal)l
extern _native64(0xD9454B5752C857DC) void SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME()l
extern _native64(0x27CFB1B1E078CB2D) void SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME()l
extern _native64(0x4B5CFC83122DF602) void SET_DISABLE_DECAL_RENDERING_THIS_FRAME()l
extern _native64(0x2F09F7976C512404) bool GET_IS_PETROL_DECAL_IN_RANGE(float xCoord, float yCoord, float zCoord, float radius)l
extern _native64(0x8A35C742130C6080) void PATCH_DECAL_DIFFUSE_MAP(int decalType, const char* textureDict, const char* textureName)l
extern _native64(0xB7ED70C49521A61D) void UNPATCH_DECAL_DIFFUSE_MAP(int decalType)l
extern _native64(0x84C8D7C2D30D3280) void MOVE_VEHICLE_DECALS(any p0, any p1)l
extern _native64(0x428BDCB9DA58DA53) bool ADD_VEHICLE_CREW_EMBLEM(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, any p13, int alpha)l
extern _native64(0x82ACC484FFA3B05F) bool ABORT_VEHICLE_CREW_EMBLEM_REQUEST(int* p0)l
extern _native64(0xD2300034310557E4) void REMOVE_VEHICLE_CREW_EMBLEM(Vehicle vehicle, int p1)l
extern _native64(0xFE26117A5841B2FF) int GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE(Vehicle vehicle, int p1)l
extern _native64(0x060D935D3981A275) bool DOES_VEHICLE_HAVE_CREW_EMBLEM(Vehicle vehicle, int p1)l
extern _native64(0x0E4299C549F0D1F1) void DISABLE_COMPOSITE_SHOTGUN_DECALS(bool toggle)l
extern _native64(0x02369D5C8A51FDCF) void DISABLE_SCUFF_DECALS(bool toggle)l
extern _native64(0x46D1A61A21F566FC) void SET_DECAL_BULLET_IMPACT_RANGE_SCALE(float p0)l
extern _native64(0x2A2A52824DB96700) void OVERRIDE_INTERIOR_SMOKE_NAME(const char* name)l
extern _native64(0x1600FD8CF72EBC12) void OVERRIDE_INTERIOR_SMOKE_LEVEL(float level)l
extern _native64(0xEFB55E7C25D3B3BE) void OVERRIDE_INTERIOR_SMOKE_END()l
extern _native64(0xA44FF770DFBC5DAE) void REGISTER_NOIR_LENS_EFFECT()l
extern _native64(0xC9F98AC1884E73A2) void DISABLE_VEHICLE_DISTANTLIGHTS(bool toggle)l
extern _native64(0x03300B57FCAC6DDB) void RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS(bool p0)l
extern _native64(0x98EDF76A7271E4F2) void REQUEST_EARLY_LIGHT_CHECK()l
extern _native64(0xAEEDAD1420C65CC0) void USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(bool toggle)l
extern _native64(0x4CC7F0FEA5283FE0) void USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(bool toggle)l
extern _native64(0xEFD97FF47B745B8D) void DISABLE_REGION_VFX(any p0)l
extern _native64(0xD7021272EB0A451E) void PRESET_INTERIOR_AMBIENT_CACHE(const char* timecycleModifierName)l
extern _native64(0x2C933ABF17A1DF41) void SET_TIMECYCLE_MODIFIER(const char* modifierName)l
extern _native64(0x82E7FFCD5B2326B3) void SET_TIMECYCLE_MODIFIER_STRENGTH(float strength)l
extern _native64(0x3BCF567485E1971C) void SET_TRANSITION_TIMECYCLE_MODIFIER(const char* modifierName, float transition)l
extern _native64(0x1CBA05AE7BD7EE05) void SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER(float strength)l
extern _native64(0x0F07E7745A236711) void CLEAR_TIMECYCLE_MODIFIER()l
extern _native64(0xFDF3D97C674AFB66) int GET_TIMECYCLE_MODIFIER_INDEX()l
extern _native64(0x459FD2C8D0AB78BC) int GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX()l
extern _native64(0x98D18905BF723B99) bool GET_IS_TIMECYCLE_TRANSITIONING_OUT()l
extern _native64(0x58F735290861E6B4) void PUSH_TIMECYCLE_MODIFIER()l
extern _native64(0x3C8938D7D872211E) void POP_TIMECYCLE_MODIFIER()l
extern _native64(0xBBF327DED94E4DEB) void SET_CURRENT_PLAYER_TCMODIFIER(const char* modifierName)l
extern _native64(0xBDEB86F4D5809204) void SET_PLAYER_TCMODIFIER_TRANSITION(float value)l
extern _native64(0xBF59707B3E5ED531) void SET_NEXT_PLAYER_TCMODIFIER(const char* modifierName)l
extern _native64(0x1A8E2C8B9CF4549C) void ADD_TCMODIFIER_OVERRIDE(const char* modifierName1, const char* modifierName2)l
extern _native64(0x15E33297C3E8DC60) void CLEAR_ALL_TCMODIFIER_OVERRIDES(const char* p0)l
extern _native64(0x5096FD9CCB49056D) void SET_EXTRA_TCMODIFIER(const char* modifierName)l
extern _native64(0x92CCC17A7A2285DA) void CLEAR_EXTRA_TCMODIFIER()l
extern _native64(0xBB0527EC6341496D) int GET_EXTRA_TCMODIFIER()l
extern _native64(0x2C328AF17210F009) void ENABLE_MOON_CYCLE_OVERRIDE(float strength)l
extern _native64(0x2BF72AD5B41AA739) void DISABLE_MOON_CYCLE_OVERRIDE()l
extern _native64(0x11FE353CF9733E6F) int REQUEST_SCALEFORM_MOVIE(const char* scaleformName)l
extern _native64(0x65E7E78842E74CDB) int REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN(const char* scaleformName)l
extern _native64(0xC514489CFB8AF806) int REQUEST_SCALEFORM_MOVIE_INSTANCE(const char* scaleformName)l
extern _native64(0xBD06C611BB9048C2) int REQUEST_SCALEFORM_MOVIE_SKIP_RENDER_WHILE_PAUSED(const char* scaleformName)l
extern _native64(0x85F01B8D5B90570E) bool HAS_SCALEFORM_MOVIE_LOADED(int scaleformHandle)l
extern _native64(0x2FCB133CA50A49EB) bool IS_ACTIVE_SCALEFORM_MOVIE_DELETING(int val)l
extern _native64(0x86255B1FC929E33E) bool IS_SCALEFORM_MOVIE_DELETING(int val)l
extern _native64(0x0C1C5D756FB5F337) bool HAS_SCALEFORM_MOVIE_FILENAME_LOADED(const char* scaleformName)l
extern _native64(0x8217150E1217EBFD) bool HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(int scaleformHandle)l
extern _native64(0x1D132D614DD86811) void SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(int* scaleformHandle)l
extern _native64(0x6D8EB211944DCE08) void SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(int scaleform, bool toggle)l
extern _native64(0x32F34FF7F617643B) void SET_SCALEFORM_MOVIE_TO_USE_LARGE_RT(int scaleformHandle, bool toggle)l
extern _native64(0xE6A9F00D4240B519) void SET_SCALEFORM_MOVIE_TO_USE_SUPER_LARGE_RT(int scaleformHandle, bool toggle)l
extern _native64(0x54972ADAF0294A93) void DRAW_SCALEFORM_MOVIE(int scaleformHandle, float x, float y, float width, float height, int red, int green, int blue, int alpha, int p9)l
extern _native64(0x0DF606929C105BE1) void DRAW_SCALEFORM_MOVIE_FULLSCREEN(int scaleform, int red, int green, int blue, int alpha, int p5)l
extern _native64(0xCF537FDE4FBD4CE5) void DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(int scaleform1, int scaleform2, int red, int green, int blue, int alpha)l
extern _native64(0x87D51D72255D4E78) void DRAW_SCALEFORM_MOVIE_3D(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder)l
extern _native64(0x1CE592FDC749D6F5) void DRAW_SCALEFORM_MOVIE_3D_SOLID(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder)l
extern _native64(0xFBD96D87AC96D533) void CALL_SCALEFORM_MOVIE_METHOD(int scaleform, const char* method)l
extern _native64(0xD0837058AE2E4BEE) void CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER(int scaleform, const char* methodName, float param1, float param2, float param3, float param4, float param5)l
extern _native64(0x51BC1ED3CC44E8F7) void CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING(int scaleform, const char* methodName, const char* param1, const char* param2, const char* param3, const char* param4, const char* param5)l
extern _native64(0xEF662D8D57E290B1) void CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING(int scaleform, const char* methodName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, const char* stringParam1, const char* stringParam2, const char* stringParam3, const char* stringParam4, const char* stringParam5)l
extern _native64(0x98C494FD5BDFBFD5) bool BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD(int hudComponent, const char* methodName)l
extern _native64(0xF6E48914C7A8694E) bool BEGIN_SCALEFORM_MOVIE_METHOD(int scaleform, const char* methodName)l
extern _native64(0xAB58C27C2E6123C6) bool BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(const char* methodName)l
extern _native64(0xB9449845F73F5E9C) bool BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER(const char* methodName)l
extern _native64(0xC6796A8FFA375E53) void END_SCALEFORM_MOVIE_METHOD()l
extern _native64(0xC50AA39A577AF886) int END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE()l
extern _native64(0x768FF8961BA904D6) bool IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY(int methodReturn)l
extern _native64(0x2DE7EFA66B906036) int GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT(int methodReturn)l
extern _native64(0xD80A80346A45D761) bool GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL(int methodReturn)l
extern _native64(0xE1E258829A885245) const char* GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING(int methodReturn)l
extern _native64(0xC3D0841A0CC546A6) void SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(int value)l
extern _native64(0xD69736AAE04DB51A) void SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(float value)l
extern _native64(0xC58424BA936EB458) void SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(bool value)l
extern _native64(0x80338406F3475E55) void BEGIN_TEXT_COMMAND_SCALEFORM_STRING(const char* componentType)l
extern _native64(0x362E2D3FE93A9959) void END_TEXT_COMMAND_SCALEFORM_STRING()l
extern _native64(0xAE4E8157D9ECF087) void END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING()l
extern _native64(0x77FE3402004CD1B0) void SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(const char* string)l
extern _native64(0xBA7148484BD90365) void SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(const char* string)l
extern _native64(0xE83A3E3557A56640) void SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(const char* string)l
extern _native64(0x5E657EF1099EDD65) bool DOES_LATEST_BRIEF_STRING_EXIST(int p0)l
extern _native64(0xEC52C631A1831C03) void SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING(int value)l
extern _native64(0x9304881D6F6537EA) void REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent)l
extern _native64(0xDF6E5987D2B4D140) bool HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED(int hudComponent)l
extern _native64(0xF44A5456AC3F4F97) void REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent)l
extern _native64(0xD1C7CB175E012964) bool PASS_KEYBOARD_INPUT_TO_SCALEFORM(int scaleformHandle)l
extern _native64(0xBAABBB23EB6E484E) void SET_TV_CHANNEL(int channel)l
extern _native64(0xFC1E275A90D39995) int GET_TV_CHANNEL()l
extern _native64(0x2982BF73F66E9DDC) void SET_TV_VOLUME(float volume)l
extern _native64(0x2170813D3DD8661B) float GET_TV_VOLUME()l
extern _native64(0xFDDC2B4ED3C69DF0) void DRAW_TV_CHANNEL(float xPos, float yPos, float xScale, float yScale, float rotation, int red, int green, int blue, int alpha)l
extern _native64(0xF7B38B8305F1FE8B) void SET_TV_CHANNEL_PLAYLIST(int tvChannel, const char* playlistName, bool restart)l
extern _native64(0x2201C576FACAEBE8) void SET_TV_CHANNEL_PLAYLIST_AT_HOUR(int tvChannel, const char* playlistName, int hour)l
extern _native64(0xBEB3D46BB7F043C0) void CLEAR_TV_CHANNEL_PLAYLIST(int tvChannel)l
extern _native64(0x1F710BFF7DAE6261) bool IS_PLAYLIST_ON_CHANNEL(int tvChannel, any p1)l
extern _native64(0x0AD973CA1E077B60) bool IS_TVSHOW_CURRENTLY_PLAYING(Hash videoCliphash)l
extern _native64(0x74C180030FDE4B69) void ENABLE_MOVIE_KEYFRAME_WAIT(bool toggle)l
extern _native64(0xD1C55B110E4DF534) void SET_TV_PLAYER_WATCHING_THIS_FRAME(any p0)l
extern _native64(0x30432A0118736E00) Hash GET_CURRENT_TV_CLIP_NAMEHASH()l
extern _native64(0x873FA65C778AD970) void ENABLE_MOVIE_SUBTITLES(bool toggle)l
extern _native64(0xD3A10FC7FD8D98CD) bool UI3DSCENE_IS_AVAILABLE()l
extern _native64(0xF1CEA8A4198D8E9A) bool UI3DSCENE_PUSH_PRESET(const char* presetName)l
extern _native64(0x98C4FE6EC34154CA) bool UI3DSCENE_ASSIGN_PED_TO_SLOT(const char* presetName, Ped ped, int slot, float posX, float posY, float posZ)l
extern _native64(0x7A42B2E236E71415) void UI3DSCENE_CLEAR_PATCHED_DATA()l
extern _native64(0x108BE26959A9D9BB) void UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT(bool toggle)l
extern _native64(0xA356990E161C9E65) void TERRAINGRID_ACTIVATE(bool toggle)l
extern _native64(0x1C4FC5752BCD8E48) void TERRAINGRID_SET_PARAMS(float x, float y, float z, float forwardX, float forwardY, float forwardZ, float sizeX, float sizeY, float sizeZ, float gridScale, float glowIntensity, float normalHeight, float heightDiff)l
extern _native64(0x5CE62918F8D703C7) void TERRAINGRID_SET_COLOURS(int lowR, int lowG, int lowB, int lowAlpha, int r, int g, int b, int alpha, int highR, int highG, int highB, int highAlpha)l
extern _native64(0x2206BF9A37B7F724) void ANIMPOSTFX_PLAY(const char* effectName, int duration, bool looped)l
extern _native64(0x068E835A1D0DC0E3) void ANIMPOSTFX_STOP(const char* effectName)l
extern _native64(0xE35B38A27E8E7179) float ANIMPOSTFX_GET_CURRENT_TIME(const char* effectName)l
extern _native64(0x36AD3E690DA5ACEB) bool ANIMPOSTFX_IS_RUNNING(const char* effectName)l
extern _native64(0xB4EDDC19532BFB85) void ANIMPOSTFX_STOP_ALL()l
extern _native64(0xD2209BE128B5418C) void ANIMPOSTFX_STOP_AND_FLUSH_REQUESTS(const char* effectName)l
#pragma endregion //}
#pragma region HUD //{
extern _native64(0xABA17D7CE615ADBF) void BEGIN_TEXT_COMMAND_BUSYSPINNER_ON(const char* string)l
extern _native64(0xBD12F8228410D9B4) void END_TEXT_COMMAND_BUSYSPINNER_ON(int busySpinnerType)l
extern _native64(0x10D373323E5B9C0D) void BUSYSPINNER_OFF()l
extern _native64(0xC65AB383CD91DF98) void PRELOAD_BUSYSPINNER()l
extern _native64(0xD422FCC5F239A915) bool BUSYSPINNER_IS_ON()l
extern _native64(0xB2A592B04648A9CB) bool BUSYSPINNER_IS_DISPLAYING()l
extern _native64(0x9245E81072704B8A) void DISABLE_PAUSEMENU_SPINNER(bool p0)l
extern _native64(0xAAE7CE1D63167423) void SET_MOUSE_CURSOR_THIS_FRAME()l
extern _native64(0x8DB8CFFD58B62552) void SET_MOUSE_CURSOR_STYLE(int spriteId)l
extern _native64(0x98215325A695E78A) void SET_MOUSE_CURSOR_VISIBLE(bool toggle)l
extern _native64(0x3D9ACB1EB139E702) bool IS_MOUSE_ROLLED_OVER_INSTRUCTIONAL_BUTTONS()l
extern _native64(0x632B2940C67F4EA9) bool GET_MOUSE_EVENT(int scaleformHandle, any* p1, any* p2, any* p3)l
extern _native64(0x6F1554B0CC2089FA) void THEFEED_ONLY_SHOW_TOOLTIPS(bool toggle)l
extern _native64(0x55598D21339CB998) void THEFEED_SET_SCRIPTED_MENU_HEIGHT(float pos)l
extern _native64(0x32888337579A5970) void THEFEED_HIDE()l
extern _native64(0x25F87B30C382FCA7) void THEFEED_HIDE_THIS_FRAME()l
extern _native64(0x15CFA549788D35EF) void THEFEED_SHOW()l
extern _native64(0xA8FDB297A8D25FBA) void THEFEED_FLUSH_QUEUE()l
extern _native64(0xBE4390CB40B3E627) void THEFEED_REMOVE_ITEM(int notificationId)l
extern _native64(0xA13C11E1B5C06BFC) void THEFEED_FORCE_RENDER_ON()l
extern _native64(0x583049884A2EEE3C) void THEFEED_FORCE_RENDER_OFF()l
extern _native64(0xFDB423997FA30340) void THEFEED_PAUSE()l
extern _native64(0xE1CD1E48E025E661) void THEFEED_RESUME()l
extern _native64(0xA9CBFD40B3FA3010) bool THEFEED_IS_PAUSED()l
extern _native64(0xD4438C0564490E63) void THEFEED_REPORT_LOGO_ON()l
extern _native64(0xB695E2CD0A2DA9EE) void THEFEED_REPORT_LOGO_OFF()l
extern _native64(0x82352748437638CA) int THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID()l
extern _native64(0x56C8B608CFD49854) void THEFEED_AUTO_POST_GAMETIPS_ON()l
extern _native64(0xADED7F5748ACAFE6) void THEFEED_AUTO_POST_GAMETIPS_OFF()l
extern _native64(0x92F0DA1E27DB96DC) void THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(int hudColorIndex)l
extern _native64(0x17430B918701C342) void THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(int red, int green, int blue, int alpha)l
extern _native64(0x17AD8C9706BDD88A) void THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE(int count)l
extern _native64(0x4A0C7C9BB10ABB36) void THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE(bool toggle)l
extern _native64(0xFDD85225B2DEA55E) void THEFEED_RESET_ALL_PARAMETERS()l
extern _native64(0xFDEC055AB549E328) void THEFEED_FREEZE_NEXT_POST()l
extern _native64(0x80FE4F3AB4E1B62A) void THEFEED_CLEAR_FROZEN_POST()l
extern _native64(0xBAE4F9B97CD43B30) void THEFEED_SET_SNAP_FEED_ITEM_POSITIONS(bool p0)l
extern _native64(0x317EBA71D7543F52) void THEFEED_UPDATE_ITEM_TEXTURE(const char* txdString1, const char* txnString1, const char* txdString2, const char* txnString2)l
extern _native64(0x202709F4C58A0424) void BEGIN_TEXT_COMMAND_THEFEED_POST(const char* text)l
extern _native64(0x2B7E9A4EAAA93C89) int END_TEXT_COMMAND_THEFEED_POST_STATS(const char* statTitle, int iconEnum, bool stepVal, int barValue, bool isImportant, const char* pictureTextureDict, const char* pictureTextureName)l
extern _native64(0x1CCD9A37359072CF) int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject)l
extern _native64(0xC6F580E4C94926AC) int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_SUBTITLE_LABEL(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject)l
extern _native64(0x1E6611149DB3DB6B) int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject, float duration)l
extern _native64(0x5CBF7BADE20DB93E) int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject, float duration, const char* clanTag)l
extern _native64(0x531B84E7DA981FB6) int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON(const char* txdName, const char* textureName, bool flash, int iconType1, const char* sender, const char* subject, float duration, const char* clanTag, int iconType2, int p9)l
extern _native64(0x2ED7843F8F801023) int END_TEXT_COMMAND_THEFEED_POST_TICKER(bool blink, bool p1)l
extern _native64(0x44FA03975424A0EE) int END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED(bool blink, bool p1)l
extern _native64(0x378E809BF61EC840) int END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS(bool blink, bool p1)l
extern _native64(0xAA295B6F28BD587D) int END_TEXT_COMMAND_THEFEED_POST_AWARD(const char* textureDict, const char* textureName, int rpBonus, int colorOverlay, const char* titleLabel)l
extern _native64(0x97C9E4E7024A8F2C) int END_TEXT_COMMAND_THEFEED_POST_CREWTAG(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, int R, int G, int B)l
extern _native64(0x137BC35589E34E1E) int END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, const char* playerName, int R, int G, int B)l
extern _native64(0x33EE12743CCD6343) int END_TEXT_COMMAND_THEFEED_POST_UNLOCK(const char* gxtLabel1, int p1, const char* gxtLabel2)l
extern _native64(0xC8F3AAF93D0600BF) int END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU(const char* gxtLabel1, int p1, const char* gxtLabel2, int p3)l
extern _native64(0x7AE0589093A2E088) int END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xF020C96915705B3A) int END_TEXT_COMMAND_THEFEED_POST_MPTICKER(bool blink, bool p1)l
extern _native64(0x8EFCCF6EC66D85E4) int END_TEXT_COMMAND_THEFEED_POST_CREW_RANKUP_WITH_LITERAL_FLAG(const char* p0, const char* p1, const char* p2, bool p3, bool p4)l
extern _native64(0xB6871B0555B02996) int END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU(const char* txdName1, const char* textureName1, int count1, const char* txdName2, const char* textureName2, int count2, int hudColor1, int hudColor2)l
extern _native64(0xD202B92CBF1D816F) int END_TEXT_COMMAND_THEFEED_POST_REPLAY(int type, int image, const char* text)l
extern _native64(0xDD6CB2CCE7C2735C) int END_TEXT_COMMAND_THEFEED_POST_REPLAY_INPUT(int type, const char* button, const char* text)l
extern _native64(0xB87A37EEB7FAA67D) void BEGIN_TEXT_COMMAND_PRINT(const char* GxtEntry)l
extern _native64(0x9D77056A530643F6) void END_TEXT_COMMAND_PRINT(int duration, bool drawImmediately)l
extern _native64(0x853648FD1063A213) void BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(const char* text)l
extern _native64(0x8A9BA1AB3E237613) bool END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED()l
extern _native64(0x25FBB336DF1804CB) void BEGIN_TEXT_COMMAND_DISPLAY_TEXT(const char* text)l
extern _native64(0xCD015E5BB0D96A57) void END_TEXT_COMMAND_DISPLAY_TEXT(float x, float y, int p2)l
extern _native64(0x54CE8AC98E120CAB) void BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(const char* text)l
extern _native64(0x85F061DA64ED2F67) float END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(bool p0)l
extern _native64(0x521FB041D93DD0E4) void BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(const char* entry)l
extern _native64(0x9040DFB09BE75706) int END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(float x, float y)l
extern _native64(0x8509B634FBE7DA11) void BEGIN_TEXT_COMMAND_DISPLAY_HELP(const char* inputType)l
extern _native64(0x238FFE5C7B0498A6) void END_TEXT_COMMAND_DISPLAY_HELP(int p0, bool loop, bool beep, int shape)l
extern _native64(0x0A24DA3A41B718F5) void BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(const char* labelName)l
extern _native64(0x10BDDBFC529428DD) bool END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(int p0)l
extern _native64(0xF9113A30DE5C6670) void BEGIN_TEXT_COMMAND_SET_BLIP_NAME(const char* textLabel)l
extern _native64(0xBC38B49BCB83BC9B) void END_TEXT_COMMAND_SET_BLIP_NAME(Blip blip)l
extern _native64(0x23D69E0465570028) void BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(const char* p0)l
extern _native64(0xCFDBDF5AE59BA0F4) void END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(bool p0)l
extern _native64(0xE124FA80A759019C) void BEGIN_TEXT_COMMAND_CLEAR_PRINT(const char* text)l
extern _native64(0xFCC75460ABA29378) void END_TEXT_COMMAND_CLEAR_PRINT()l
extern _native64(0x8F9EE5687F8EECCD) void BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(const char* gxtEntry)l
extern _native64(0xA86911979638106F) void END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(int p0)l
extern _native64(0x03B504CF259931BC) void ADD_TEXT_COMPONENT_INTEGER(int value)l
extern _native64(0xE7DCB5B874BCD96E) void ADD_TEXT_COMPONENT_FLOAT(float value, int decimalPlaces)l
extern _native64(0xC63CD5D2920ACBE7) void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(const char* labelName)l
extern _native64(0x17299B63C7683A2B) void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(Hash gxtEntryHash)l
extern _native64(0x80EAD8E2E1D5D52E) void ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(Blip blip)l
extern _native64(0x6C188BE134E074AA) void ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const char* text)l
extern _native64(0x1115F16B8AB9E8BF) void ADD_TEXT_COMPONENT_SUBSTRING_TIME(int timestamp, int flags)l
extern _native64(0x0E4C749FF9DE9CC4) void ADD_TEXT_COMPONENT_FORMATTED_INTEGER(int value, bool commaSeparated)l
extern _native64(0x761B77454205A61D) void ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER(const char* p0, int p1)l
extern _native64(0x94CF4AC034C9C986) void ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(const char* website)l
extern _native64(0x5F68520888E69014) void ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY(const char* string)l
extern _native64(0x39BBF623FC803EAC) void SET_COLOUR_OF_NEXT_TEXT_COMPONENT(int hudColor)l
extern _native64(0x169BD9382084C8C0) const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME(const char* text, int position, int length)l
extern _native64(0xB2798643312205C5) const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT(const char* text, int position, int length, int maxLength)l
extern _native64(0xCE94AEBA5D82908A) const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES(const char* text, int startPosition, int endPosition)l
extern _native64(0x7B5280EBA9840C72) const char* GET_FILENAME_FOR_AUDIO_CONVERSATION(const char* labelName)l
extern _native64(0xCC33FA791322B9D9) void CLEAR_PRINTS()l
extern _native64(0x9D292F73ADBD9313) void CLEAR_BRIEF()l
extern _native64(0x6178F68A87A4D3A0) void CLEAR_ALL_HELP_MESSAGES()l
extern _native64(0xCF708001E1E536DD) void CLEAR_THIS_PRINT(const char* p0)l
extern _native64(0x2CEA2839313C09AC) void CLEAR_SMALL_PRINTS()l
extern _native64(0x1C7302E725259789) bool DOES_TEXT_BLOCK_EXIST(const char* gxt)l
extern _native64(0x71A78003C8E71424) void REQUEST_ADDITIONAL_TEXT(const char* gxt, int slot)l
extern _native64(0x6009F9F1AE90D8A6) void REQUEST_ADDITIONAL_TEXT_FOR_DLC(const char* gxt, int slot)l
extern _native64(0x02245FE4BED318B8) bool HAS_ADDITIONAL_TEXT_LOADED(int slot)l
extern _native64(0x2A179DF17CCF04CD) void CLEAR_ADDITIONAL_TEXT(int p0, bool p1)l
extern _native64(0x8B6817B71B85EBF0) bool IS_STREAMING_ADDITIONAL_TEXT(int p0)l
extern _native64(0xADBF060E2B30C5BC) bool HAS_THIS_ADDITIONAL_TEXT_LOADED(const char* gxt, int slot)l
extern _native64(0x7984C03AA5CC2F41) bool IS_MESSAGE_BEING_DISPLAYED()l
extern _native64(0xAC09CA973C564252) bool DOES_TEXT_LABEL_EXIST(const char* gxt)l
extern _native64(0x98C3CF913D895111) const char* GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING(const char* string, int length)l
extern _native64(0x801BD273D3A23F74) int GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(const char* gxt)l
extern _native64(0xF030907CCBB8A9FD) int GET_LENGTH_OF_LITERAL_STRING(const char* string)l
extern _native64(0x43E4111189E54F0E) int GET_LENGTH_OF_LITERAL_STRING_IN_BYTES(const char* string)l
extern _native64(0xD0EF8A959B8A4CB9) const char* GET_STREET_NAME_FROM_HASH_KEY(Hash hash)l
extern _native64(0x1930DFA731813EC4) bool IS_HUD_PREFERENCE_SWITCHED_ON()l
extern _native64(0x9EB6522EA68F22FE) bool IS_RADAR_PREFERENCE_SWITCHED_ON()l
extern _native64(0xAD6DACA4BA53E0A4) bool IS_SUBTITLE_PREFERENCE_SWITCHED_ON()l
extern _native64(0xA6294919E56FF02A) void DISPLAY_HUD(bool toggle)l
extern _native64(0x7669F9E39DC17063) void DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME()l
extern _native64(0x402F9ED62087E898) void DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME()l
extern _native64(0xA0EBB943C300E693) void DISPLAY_RADAR(bool toggle)l
extern _native64(0xCD74233600C4EA6B) void SET_FAKE_SPECTATOR_MODE(bool toggle)l
extern _native64(0xC2D2AD9EAAE265B8) bool GET_FAKE_SPECTATOR_MODE()l
extern _native64(0xA86478C6958735C5) bool IS_HUD_HIDDEN()l
extern _native64(0x157F93B036700462) bool IS_RADAR_HIDDEN()l
extern _native64(0xAF754F20EB5CD51A) bool IS_MINIMAP_RENDERING()l
extern _native64(0x0C698D8F099174C7) void USE_VEHICLE_TARGETING_RETICULE(any p0)l
extern _native64(0xE4C3B169876D33D7) void ADD_VALID_VEHICLE_HIT_HASH(any p0)l
extern _native64(0xEB81A3DADD503187) void CLEAR_VALID_VEHICLE_HIT_HASHES()l
extern _native64(0x4F7D8A9BFB0B43E9) void SET_BLIP_ROUTE(Blip blip, bool enabled)l
extern _native64(0xD12882D3FF82BF11) void CLEAR_ALL_BLIP_ROUTES()l
extern _native64(0x837155CD2F63DA09) void SET_BLIP_ROUTE_COLOUR(Blip blip, int colour)l
extern _native64(0x2790F4B17D098E26) void SET_FORCE_SHOW_GPS(bool toggle)l
extern _native64(0x6CDD58146A436083) void SET_USE_SET_DESTINATION_IN_PAUSE_MAP(bool toggle)l
extern _native64(0xD1942374085C8469) void SET_BLOCK_WANTED_FLASH(bool disabled)l
extern _native64(0x60296AF4BA14ABC5) void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(bool p0)l
extern _native64(0x57D760D55F54E071) void FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST(int p0)l
extern _native64(0xBD12C5EEE184C337) void SET_RADAR_ZOOM_PRECISE(float zoom)l
extern _native64(0x096EF57A0C999BBA) void SET_RADAR_ZOOM(int zoomLevel)l
extern _native64(0xF98E4B3E56AFC7B1) void SET_RADAR_ZOOM_TO_BLIP(Blip blip, float zoom)l
extern _native64(0xCB7CC0D58405AD41) void SET_RADAR_ZOOM_TO_DISTANCE(float zoom)l
extern _native64(0xD2049635DEB9C375) void UPDATE_RADAR_ZOOM_TO_BLIP()l
extern _native64(0x7C9C91AB74A0360F) void GET_HUD_COLOUR(int hudColorIndex, int* r, int* g, int* b, int* a)l
extern _native64(0xD68A5FF8A3A89874) void SET_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a)l
extern _native64(0x16A304E6CB2BFAB9) void SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a)l
extern _native64(0x1CCC708F0F850613) void REPLACE_HUD_COLOUR(int hudColorIndex, int hudColorIndex2)l
extern _native64(0xF314CF4F0211894E) void REPLACE_HUD_COLOUR_WITH_RGBA(int hudColorIndex, int r, int g, int b, int a)l
extern _native64(0x1DFEDD15019315A9) void SET_ABILITY_BAR_VISIBILITY(bool visible)l
extern _native64(0x889329C80FE5963C) void SET_ALLOW_ABILITY_BAR(bool toggle)l
extern _native64(0x02CFBA0C9E9275CE) void FLASH_ABILITY_BAR(int millisecondsToFlash)l
extern _native64(0x9969599CCFF5D85E) void SET_ABILITY_BAR_VALUE(float p0, float p1)l
extern _native64(0xA18AFB39081B6A1F) void FLASH_WANTED_DISPLAY(bool p0)l
extern _native64(0xBA8D65C1C65702E5) void FORCE_OFF_WANTED_STAR_FLASH(bool toggle)l
extern _native64(0x2ACCB195F3CCD9DE) void SET_CUSTOM_MP_HUD_COLOR(int hudColorId)l
extern _native64(0xDB88A37483346780) float GET_RENDERED_CHARACTER_HEIGHT(float size, int font)l
extern _native64(0x07C837F9A01C34C9) void SET_TEXT_SCALE(float scale, float size)l
extern _native64(0xBE6B23FFA53FB442) void SET_TEXT_COLOUR(int red, int green, int blue, int alpha)l
extern _native64(0xC02F4DBFB51D988B) void SET_TEXT_CENTRE(bool align)l
extern _native64(0x6B3C4650BC8BEE47) void SET_TEXT_RIGHT_JUSTIFY(bool toggle)l
extern _native64(0x4E096588B13FFECA) void SET_TEXT_JUSTIFICATION(int justifyType)l
extern _native64(0x63145D9C883A1A70) void SET_TEXT_WRAP(float start, float end)l
extern _native64(0xA50ABC31E3CDFAFF) void SET_TEXT_LEADING(int p0)l
extern _native64(0x038C1F517D7FDCF8) void SET_TEXT_PROPORTIONAL(bool p0)l
extern _native64(0x66E0276CC5F6B9DA) void SET_TEXT_FONT(int fontType)l
extern _native64(0x1CA3E9EAC9D93E5E) void SET_TEXT_DROP_SHADOW()l
extern _native64(0x465C84BC39F1C351) void SET_TEXT_DROPSHADOW(int distance, int r, int g, int b, int a)l
extern _native64(0x2513DFB0FB8400FE) void SET_TEXT_OUTLINE()l
extern _native64(0x441603240D202FA6) void SET_TEXT_EDGE(int p0, int r, int g, int b, int a)l
extern _native64(0x5F15302936E07111) void SET_TEXT_RENDER_ID(int renderId)l
extern _native64(0x52F0982D7FD156B6) int GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID()l
extern _native64(0x57D9C12635E25CE3) bool REGISTER_NAMED_RENDERTARGET(const char* name, bool p1)l
extern _native64(0x78DCDC15C9F116B4) bool IS_NAMED_RENDERTARGET_REGISTERED(const char* name)l
extern _native64(0xE9F6FFE837354DD4) bool RELEASE_NAMED_RENDERTARGET(const char* name)l
extern _native64(0xF6C09E276AEB3F2D) void LINK_NAMED_RENDERTARGET(Hash modelHash)l
extern _native64(0x1A6478B61C6BDC3B) int GET_NAMED_RENDERTARGET_RENDER_ID(const char* name)l
extern _native64(0x113750538FA31298) bool IS_NAMED_RENDERTARGET_LINKED(Hash modelHash)l
extern _native64(0x8DFCED7A656F8802) void CLEAR_HELP(bool toggle)l
extern _native64(0xDAD37F45428801AE) bool IS_HELP_MESSAGE_ON_SCREEN()l
extern _native64(0x214CD562A939246A) bool HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME()l
extern _native64(0x4D79439A6B55AC67) bool IS_HELP_MESSAGE_BEING_DISPLAYED()l
extern _native64(0x327EDEEEAC55C369) bool IS_HELP_MESSAGE_FADING_OUT()l
extern _native64(0xB9C362BABECDDC7A) void SET_HELP_MESSAGE_STYLE(int style, int hudColor, int alpha, int p3, int p4)l
extern _native64(0x4A9923385BDB9DAD) int GET_STANDARD_BLIP_ENUM_ID()l
extern _native64(0x186E5D252FA50E7D) int GET_WAYPOINT_BLIP_ENUM_ID()l
extern _native64(0x9A3FF3DE163034E8) int GET_NUMBER_OF_ACTIVE_BLIPS()l
extern _native64(0x14F96AA50D6FBEA7) Blip GET_NEXT_BLIP_INFO_ID(int blipSprite)l
extern _native64(0x1BEDE233E6CD2A1F) Blip GET_FIRST_BLIP_INFO_ID(int blipSprite)l
extern _native64(0xD484BF71050CA1EE) Blip GET_CLOSEST_BLIP_INFO_ID(int blipSprite)l
extern _native64(0xFA7C7F0AADF25D09) vector3 GET_BLIP_INFO_ID_COORD(Blip blip)l
extern _native64(0x1E314167F701DC3B) int GET_BLIP_INFO_ID_DISPLAY(Blip blip)l
extern _native64(0xBE9B0959FFD0779B) int GET_BLIP_INFO_ID_TYPE(Blip blip)l
extern _native64(0x4BA4E2553AFEDC2C) Entity GET_BLIP_INFO_ID_ENTITY_INDEX(Blip blip)l
extern _native64(0x9B6786E4C03DD382) Pickup GET_BLIP_INFO_ID_PICKUP_INDEX(Blip blip)l
extern _native64(0xBC8DBDCA2436F7E8) Blip GET_BLIP_FROM_ENTITY(Entity entity)l
extern _native64(0x46818D79B1F7499A) Blip ADD_BLIP_FOR_RADIUS(float posX, float posY, float posZ, float radius)l
extern _native64(0xCE5D0E5E315DB238) Blip ADD_BLIP_FOR_AREA(float x, float y, float z, float width, float height)l
extern _native64(0x5CDE92C702A8FCE7) Blip ADD_BLIP_FOR_ENTITY(Entity entity)l
extern _native64(0xBE339365C863BD36) Blip ADD_BLIP_FOR_PICKUP(Pickup pickup)l
extern _native64(0x5A039BB0BCA604B6) Blip ADD_BLIP_FOR_COORD(float x, float y, float z)l
extern _native64(0x72DD432F3CDFC0EE) void TRIGGER_SONAR_BLIP(float posX, float posY, float posZ, float radius, int p4)l
extern _native64(0x60734CC207C9833C) void ALLOW_SONAR_BLIPS(bool toggle)l
extern _native64(0xAE2AF67E9D9AF65D) void SET_BLIP_COORDS(Blip blip, float posX, float posY, float posZ)l
extern _native64(0x586AFE3FF72D996E) vector3 GET_BLIP_COORDS(Blip blip)l
extern _native64(0xDF735600A4696DAF) void SET_BLIP_SPRITE(Blip blip, int spriteId)l
extern _native64(0x1FC877464A04FC4F) int GET_BLIP_SPRITE(Blip blip)l
extern _native64(0x9FCB3CBFB3EAD69A) void SET_COP_BLIP_SPRITE(int p0, float p1)l
extern _native64(0xB7B873520C84C118) void SET_COP_BLIP_SPRITE_AS_STANDARD()l
extern _native64(0xEAA0FFE120D92784) void SET_BLIP_NAME_FROM_TEXT_FILE(Blip blip, const char* gxtEntry)l
extern _native64(0x127DE7B20C60A6A3) void SET_BLIP_NAME_TO_PLAYER_NAME(Blip blip, Player player)l
extern _native64(0x45FF974EEE1C8734) void SET_BLIP_ALPHA(Blip blip, int alpha)l
extern _native64(0x970F608F0EE6C885) int GET_BLIP_ALPHA(Blip blip)l
extern _native64(0x2AEE8F8390D2298C) void SET_BLIP_FADE(Blip blip, int opacity, int duration)l
extern _native64(0x2C173AE2BDB9385E) int GET_BLIP_FADE_DIRECTION(Blip blip)l
extern _native64(0xF87683CDF73C3F6E) void SET_BLIP_ROTATION(Blip blip, int rotation)l
extern _native64(0xA8B6AFDAC320AC87) void SET_BLIP_ROTATION_WITH_FLOAT(Blip blip, float heading)l
extern _native64(0x003E92BA477F9D7F) int GET_BLIP_ROTATION(Blip blip)l
extern _native64(0xD3CD6FD297AE87CC) void SET_BLIP_FLASH_TIMER(Blip blip, int duration)l
extern _native64(0xAA51DB313C010A7E) void SET_BLIP_FLASH_INTERVAL(Blip blip, any p1)l
extern _native64(0x03D7FB09E75D6B7E) void SET_BLIP_COLOUR(Blip blip, int color)l
extern _native64(0x14892474891E09EB) void SET_BLIP_SECONDARY_COLOUR(Blip blip, int r, int g, int b)l
extern _native64(0xDF729E8D20CF7327) int GET_BLIP_COLOUR(Blip blip)l
extern _native64(0x729B5F1EFBC0AAEE) int GET_BLIP_HUD_COLOUR(Blip blip)l
extern _native64(0xDA5F8727EB75B926) bool IS_BLIP_SHORT_RANGE(Blip blip)l
extern _native64(0xE41CA53051197A27) bool IS_BLIP_ON_MINIMAP(Blip blip)l
extern _native64(0xDD2238F57B977751) bool DOES_BLIP_HAVE_GPS_ROUTE(Blip blip)l
extern _native64(0x54318C915D27E4CE) void SET_BLIP_HIDDEN_ON_LEGEND(Blip blip, bool toggle)l
extern _native64(0xE2590BC29220CEBB) void SET_BLIP_HIGH_DETAIL(Blip blip, bool toggle)l
extern _native64(0x24AC0137444F9FD5) void SET_BLIP_AS_MISSION_CREATOR_BLIP(Blip blip, bool toggle)l
extern _native64(0x26F49BF3381D933D) bool IS_MISSION_CREATOR_BLIP(Blip blip)l
extern _native64(0x5C90988E7C8E1AF4) Blip GET_NEW_SELECTED_MISSION_CREATOR_BLIP()l
extern _native64(0x4167EFE0527D706E) bool IS_HOVERING_OVER_MISSION_CREATOR_BLIP()l
extern _native64(0xF1A6C18B35BCADE6) void SHOW_START_MISSION_INSTRUCTIONAL_BUTTON(bool toggle)l
extern _native64(0xC772A904CDE1186F) void SHOW_CONTACT_INSTRUCTIONAL_BUTTON(bool toggle)l
extern _native64(0x2916A928514C9827) void RELOAD_MAP_MENU()l
extern _native64(0xB552929B85FC27EC) void SET_BLIP_MARKER_LONG_DISTANCE(any p0, any p1)l
extern _native64(0xB14552383D39CE3E) void SET_BLIP_FLASHES(Blip blip, bool toggle)l
extern _native64(0x2E8D9498C56DD0D1) void SET_BLIP_FLASHES_ALTERNATE(Blip blip, bool toggle)l
extern _native64(0xA5E41FD83AD6CEF0) bool IS_BLIP_FLASHING(Blip blip)l
extern _native64(0xBE8BE4FE60E27B72) void SET_BLIP_AS_SHORT_RANGE(Blip blip, bool toggle)l
extern _native64(0xD38744167B2FA257) void SET_BLIP_SCALE(Blip blip, float scale)l
extern _native64(0xCD6524439909C979) void SET_BLIP_SCALE_2D(Blip blip, float xScale, float yScale)l
extern _native64(0xAE9FC9EF6A9FAC79) void SET_BLIP_PRIORITY(Blip blip, int priority)l
extern _native64(0x9029B2F3DA924928) void SET_BLIP_DISPLAY(Blip blip, int displayId)l
extern _native64(0x234CDD44D996FD9A) void SET_BLIP_CATEGORY(Blip blip, int index)l
extern _native64(0x86A652570E5F25DD) void REMOVE_BLIP(Blip* blip)l
extern _native64(0x6F6F290102C02AB4) void SET_BLIP_AS_FRIENDLY(Blip blip, bool toggle)l
extern _native64(0x742D6FD43115AF73) void PULSE_BLIP(Blip blip)l
extern _native64(0xA3C0B359DCB848B6) void SHOW_NUMBER_ON_BLIP(Blip blip, int number)l
extern _native64(0x532CFF637EF80148) void HIDE_NUMBER_ON_BLIP(Blip blip)l
extern _native64(0x75A16C3DA34F1245) void SHOW_HEIGHT_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0x74513EA3E505181E) void SHOW_TICK_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0xCAC2031EBF79B1A8) void SHOW_GOLD_TICK_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0x19BD6E3C0E16A8FA) void SHOW_FOR_SALE_ICON_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0x5FBCA48327B914DF) void SHOW_HEADING_INDICATOR_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0xB81656BC81FE24D1) void SHOW_OUTLINE_INDICATOR_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0x23C3EB807312F01A) void SHOW_FRIEND_INDICATOR_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0xDCFB5D4DB8BF367E) void SHOW_CREW_INDICATOR_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0xC4278F70131BAA6D) void SET_BLIP_EXTENDED_HEIGHT_THRESHOLD(Blip blip, bool toggle)l
extern _native64(0x4B5B620C9B59ED34) void SET_BLIP_SHORT_HEIGHT_THRESHOLD(any p0, any p1)l
extern _native64(0x2C9F302398E13141) void SET_BLIP_USE_HEIGHT_INDICATOR_ON_EDGE(Blip blip, any p1)l
extern _native64(0x2B6D467DAB714E8D) void SET_BLIP_AS_MINIMAL_ON_EDGE(Blip blip, bool toggle)l
extern _native64(0x25615540D894B814) void SET_RADIUS_BLIP_EDGE(Blip blip, bool toggle)l
extern _native64(0xA6DB27D19ECBB7DA) bool DOES_BLIP_EXIST(Blip blip)l
extern _native64(0xA7E4E2D361C2627F) void SET_WAYPOINT_OFF()l
extern _native64(0xD8E694757BCEA8E9) void DELETE_WAYPOINTS_FROM_THIS_PLAYER()l
extern _native64(0x81FA173F170560D1) void REFRESH_WAYPOINT()l
extern _native64(0x1DD1F58F493F1DA5) bool IS_WAYPOINT_ACTIVE()l
extern _native64(0xFE43368D2AA4F2FC) void SET_NEW_WAYPOINT(float x, float y)l
extern _native64(0xB203913733F27884) void SET_BLIP_BRIGHT(Blip blip, bool toggle)l
extern _native64(0x13127EC3665E8EE1) void SET_BLIP_SHOW_CONE(Blip blip, bool toggle, int hudColorIndex)l
extern _native64(0xC594B315EDF2D4AF) void REMOVE_COP_BLIP_FROM_PED(Ped ped)l
extern _native64(0xF83D0FEBE75E62C9) void SETUP_FAKE_CONE_DATA(Blip blip, float p1, float p2, float p3, float p4, float p5, float p6, any p7, int p8)l
extern _native64(0x35A3CD97B2C0A6D2) void REMOVE_FAKE_CONE_DATA(Blip blip)l
extern _native64(0x8410C5E0CD847B9D) void CLEAR_FAKE_CONE_ARRAY()l
extern _native64(0x75A9A10948D1DEA6) bool SET_MINIMAP_COMPONENT(int componentId, bool toggle, int overrideColor)l
extern _native64(0x6B50FC8749632EC1) void SET_MINIMAP_SONAR_SWEEP(bool toggle)l
extern _native64(0x60E892BA4F5BDCA4) void SHOW_ACCOUNT_PICKER()l
extern _native64(0xDCD4EC3F419D02FA) Blip GET_MAIN_PLAYER_BLIP_ID()l
extern _native64(0x41350B4FC28E3941) void SET_PM_WARNINGSCREEN_ACTIVE(bool p0)l
extern _native64(0x4B0311D3CDC4648F) void HIDE_LOADING_ON_FADE_THIS_FRAME()l
extern _native64(0x59E727A1C9D3E31A) void SET_RADAR_AS_INTERIOR_THIS_FRAME(Hash interior, float x, float y, int z, int zoom)l
extern _native64(0x504DFE62A1692296) void SET_INSIDE_VERY_SMALL_INTERIOR(bool toggle)l
extern _native64(0x7EC8ABA5E74B3D7A) void SET_INSIDE_VERY_LARGE_INTERIOR(bool toggle)l
extern _native64(0xE81B7D2A3DAB2D81) void SET_RADAR_AS_EXTERIOR_THIS_FRAME()l
extern _native64(0x77E2DD177910E1CF) void SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME(float x, float y)l
extern _native64(0xA17784FCA9548D15) void SET_FAKE_GPS_PLAYER_POSITION_THIS_FRAME(float x, float y, any p2)l
extern _native64(0x9049FE339D5F6F6F) bool IS_PAUSEMAP_IN_INTERIOR_MODE()l
extern _native64(0x5FBAE526203990C9) void HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME()l
extern _native64(0x20FE7FDFEEAD38C0) void HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME()l
extern _native64(0x5E1460624D194A38) void SET_USE_ISLAND_MAP(bool toggle)l
extern _native64(0x35CCE12EAECB4A51) void _SET_PAUSE_EXTERIOR_RENDERING_WHILE_IN_INTERIOR()l
extern _native64(0x6D14BFDC33B34F55) void DONT_TILT_MINIMAP_THIS_FRAME()l
extern _native64(0x89DA85D949CE57A0) void DONT_ZOOM_MINIMAP_WHEN_RUNNING_THIS_FRAME()l
extern _native64(0x55F5A5F07134DE60) void DONT_ZOOM_MINIMAP_WHEN_SNIPING_THIS_FRAME()l
extern _native64(0xC3B07BA00A83B0F1) void SET_WIDESCREEN_FORMAT(any p0)l
extern _native64(0x276B6CE369C33678) void DISPLAY_AREA_NAME(bool toggle)l
extern _native64(0x96DEC8D5430208B7) void DISPLAY_CASH(bool toggle)l
extern _native64(0x170F541E1CADD1DE) void USE_FAKE_MP_CASH(bool toggle)l
extern _native64(0x0772DF77852C2E30) void CHANGE_FAKE_MP_CASH(int cash, int bank)l
extern _native64(0xA5E78BA2B1331C55) void DISPLAY_AMMO_THIS_FRAME(bool display)l
extern _native64(0x73115226F4814E62) void DISPLAY_SNIPER_SCOPE_THIS_FRAME()l
extern _native64(0x719FF505F097FD20) void HIDE_HUD_AND_RADAR_THIS_FRAME()l
extern _native64(0xE67C6DFD386EA5E7) void ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT(bool allow)l
extern _native64(0xC2D15BEF167E27BC) void SET_MULTIPLAYER_WALLET_CASH()l
extern _native64(0x95CF81BD06EE1887) void REMOVE_MULTIPLAYER_WALLET_CASH()l
extern _native64(0xDD21B55DF695CD0A) void SET_MULTIPLAYER_BANK_CASH()l
extern _native64(0xC7C6789AA1CFEDD0) void REMOVE_MULTIPLAYER_BANK_CASH()l
extern _native64(0xFD1D220394BCB824) void SET_MULTIPLAYER_HUD_CASH(int p0, bool p1)l
extern _native64(0x968F270E39141ECA) void REMOVE_MULTIPLAYER_HUD_CASH()l
extern _native64(0xD46923FC481CA285) void HIDE_HELP_TEXT_THIS_FRAME()l
extern _native64(0x801879A9B4F4B2FB) bool IS_IME_IN_PROGRESS()l
extern _native64(0x960C9FF8F616E41C) void DISPLAY_HELP_TEXT_THIS_FRAME(const char* message, bool p1)l
extern _native64(0xEB354E5376BC81A7) void HUD_FORCE_WEAPON_WHEEL(bool show)l
extern _native64(0x488043841BBE156F) void HUD_FORCE_SPECIAL_VEHICLE_WEAPON_WHEEL()l
extern _native64(0x0AFC4AF510774B47) void HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME()l
extern _native64(0xA48931185F0536FE) Hash HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED()l
extern _native64(0x72C1056D678BB7D8) void HUD_SET_WEAPON_WHEEL_TOP_SLOT(Hash weaponHash)l
extern _native64(0xA13E93403F26C812) Hash HUD_GET_WEAPON_WHEEL_TOP_SLOT(int weaponTypeIndex)l
extern _native64(0x14C9FDCC41F81F63) void HUD_SHOWING_CHARACTER_SWITCH_SELECTION(bool toggle)l
extern _native64(0x5B440763A4C8D15B) void SET_GPS_FLAGS(int p0, float p1)l
extern _native64(0x21986729D6A3A830) void CLEAR_GPS_FLAGS()l
extern _native64(0x1EAC5F91BCBC5073) void SET_RACE_TRACK_RENDER(bool toggle)l
extern _native64(0x7AA5B4CE533C858B) void CLEAR_GPS_RACE_TRACK()l
extern _native64(0xDB34E8D56FC13B08) void START_GPS_CUSTOM_ROUTE(int hudColor, bool displayOnFoot, bool followPlayer)l
extern _native64(0x311438A071DD9B1A) void ADD_POINT_TO_GPS_CUSTOM_ROUTE(float x, float y, float z)l
extern _native64(0x900086F371220B6F) void SET_GPS_CUSTOM_ROUTE_RENDER(bool toggle, int radarThickness, int mapThickness)l
extern _native64(0xE6DE0561D9232A64) void CLEAR_GPS_CUSTOM_ROUTE()l
extern _native64(0x3D3D15AF7BCAAF83) void START_GPS_MULTI_ROUTE(int hudColor, bool routeFromPlayer, bool displayOnFoot)l
extern _native64(0xA905192A6781C41B) void ADD_POINT_TO_GPS_MULTI_ROUTE(float x, float y, float z)l
extern _native64(0x3DDA37128DD1ACA8) void SET_GPS_MULTI_ROUTE_RENDER(bool toggle)l
extern _native64(0x67EEDEA1B9BAFD94) void CLEAR_GPS_MULTI_ROUTE()l
extern _native64(0xFF4FB7C8CDFA3DA7) void CLEAR_GPS_PLAYER_WAYPOINT()l
extern _native64(0x320D0E0D936A0E9B) void SET_GPS_FLASHES(bool toggle)l
extern _native64(0x7B21E0BB01E8224A) void SET_PLAYER_ICON_COLOUR(int color)l
extern _native64(0xF2DD778C22B15BDA) void FLASH_MINIMAP_DISPLAY()l
extern _native64(0x6B1DE27EE78E6A19) void FLASH_MINIMAP_DISPLAY_WITH_COLOR(int hudColorIndex)l
extern _native64(0x6AFDFB93754950C7) void TOGGLE_STEALTH_RADAR(bool toggle)l
extern _native64(0x1A5CD7752DD28CD3) void SET_MINIMAP_IN_SPECTATOR_MODE(bool toggle, Ped ped)l
extern _native64(0x5F28ECF5FC84772F) void SET_MISSION_NAME(bool p0, const char* name)l
extern _native64(0xE45087D85F468BC2) void SET_MISSION_NAME_FOR_UGC_MISSION(bool p0, const char* name)l
extern _native64(0x817B86108EB94E51) void SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS(bool p0, const char* p1, const char* p2, const char* p3, const char* p4, const char* p5, const char* p6, const char* p7, const char* p8)l
extern _native64(0x58FADDED207897DC) void SET_MINIMAP_BLOCK_WAYPOINT(bool toggle)l
extern _native64(0x9133955F1A2DA957) void SET_MINIMAP_IN_PROLOGUE(bool toggle)l
extern _native64(0xF8DEE0A5600CBB93) void SET_MINIMAP_HIDE_FOW(bool toggle)l
extern _native64(0xE0130B41D3CF4574) float GET_MINIMAP_FOW_DISCOVERY_RATIO()l
extern _native64(0x6E31B91145873922) bool GET_MINIMAP_FOW_COORDINATE_IS_REVEALED(float x, float y, float z)l
extern _native64(0x62E849B7EB28E770) void SET_MINIMAP_FOW_DO_NOT_UPDATE(bool p0)l
extern _native64(0x0923DBF87DFF735E) void SET_MINIMAP_FOW_REVEAL_COORDINATE(float x, float y, float z)l
extern _native64(0x71BDB63DBAF8DA59) void SET_MINIMAP_GOLF_COURSE(int hole)l
extern _native64(0x35EDD5B2E3FF01C0) void SET_MINIMAP_GOLF_COURSE_OFF()l
extern _native64(0x299FAEBB108AE05B) void LOCK_MINIMAP_ANGLE(int angle)l
extern _native64(0x8183455E16C42E3A) void UNLOCK_MINIMAP_ANGLE()l
extern _native64(0x1279E861A329E73F) void LOCK_MINIMAP_POSITION(float x, float y)l
extern _native64(0x3E93E06DB8EF1F30) void UNLOCK_MINIMAP_POSITION()l
extern _native64(0xD201F3FF917A506D) void SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT(float altitude, bool p1, any p2)l
extern _native64(0x3F5CC444DCAAA8F2) void SET_HEALTH_HUD_DISPLAY_VALUES(int health, int capacity, bool wasAdded)l
extern _native64(0x975D66A0BC17064C) void SET_MAX_HEALTH_HUD_DISPLAY(int maximumValue)l
extern _native64(0x06A320535F5F0248) void SET_MAX_ARMOUR_HUD_DISPLAY(int maximumValue)l
extern _native64(0x231C8F89D0539D8F) void SET_BIGMAP_ACTIVE(bool toggleBigMap, bool showFullMap)l
extern _native64(0xBC4C9EA5391ECC0D) bool IS_HUD_COMPONENT_ACTIVE(int id)l
extern _native64(0xDD100EB17A94FF65) bool IS_SCRIPTED_HUD_COMPONENT_ACTIVE(int id)l
extern _native64(0xE374C498D8BADC14) void HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native64(0x4F38DCA127DAAEA2) void SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native64(0x09C0403ED9A751C2) bool IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME(int id)l
extern _native64(0x6806C51AD12B83B8) void HIDE_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native64(0x0B4DF1FA60C0E664) void SHOW_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native64(0xA4DEDE28B1814289) void HIDE_STREET_AND_CAR_NAMES_THIS_FRAME()l
extern _native64(0x12782CE0A636E9F0) void RESET_RETICULE_VALUES()l
extern _native64(0x450930E616475D0D) void RESET_HUD_COMPONENT_VALUES(int id)l
extern _native64(0xAABB1F56E2A17CED) void SET_HUD_COMPONENT_POSITION(int id, float x, float y)l
extern _native64(0x223CA69A8C4417FD) vector3 GET_HUD_COMPONENT_POSITION(int id)l
extern _native64(0xB57D8DD645CFA2CF) void CLEAR_REMINDER_MESSAGE()l
extern _native64(0xF9904D11F1ACBEC3) int GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(float worldX, float worldY, float worldZ, float* screenX, float* screenY)l
extern _native64(0x523A590C1A3CC0D3) void OPEN_REPORTUGC_MENU()l
extern _native64(0xEE4C0E6DBC6F2C6F) void FORCE_CLOSE_REPORTUGC_MENU()l
extern _native64(0x9135584D09A3437E) bool IS_REPORTUGC_MENU_OPEN()l
extern _native64(0x2432784ACA090DA4) bool IS_FLOATING_HELP_TEXT_ON_SCREEN(int hudIndex)l
extern _native64(0x7679CC1BCEBE3D4C) void SET_FLOATING_HELP_TEXT_SCREEN_POSITION(int hudIndex, float x, float y)l
extern _native64(0x784BA7E0ECEB4178) void SET_FLOATING_HELP_TEXT_WORLD_POSITION(int hudIndex, float x, float y, float z)l
extern _native64(0xB094BC1DB4018240) void SET_FLOATING_HELP_TEXT_TO_ENTITY(int hudIndex, Entity entity, float offsetX, float offsetY)l
extern _native64(0x788E7FD431BD67F1) void SET_FLOATING_HELP_TEXT_STYLE(int hudIndex, int p1, int p2, int p3, int p4, int p5)l
extern _native64(0x50085246ABD3FEFA) void CLEAR_FLOATING_HELP(int hudIndex, bool p1)l
extern _native64(0x6DD05E9D83EFA4C9) void CREATE_MP_GAMER_TAG_WITH_CREW_COLOR(Player player, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, int clanFlag, int r, int g, int b)l
extern _native64(0x6E0EB3EB47C8D7AA) bool IS_MP_GAMER_TAG_MOVIE_ACTIVE()l
extern _native64(0xBFEFE3321A3F5015) int CREATE_FAKE_MP_GAMER_TAG(Ped ped, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, int clanFlag)l
extern _native64(0x31698AA80E0223F8) void REMOVE_MP_GAMER_TAG(int gamerTagId)l
extern _native64(0x4E929E7A5796FD26) bool IS_MP_GAMER_TAG_ACTIVE(int gamerTagId)l
extern _native64(0x595B5178E412E199) bool IS_MP_GAMER_TAG_FREE(int gamerTagId)l
extern _native64(0x63BB75ABEDC1F6A0) void SET_MP_GAMER_TAG_VISIBILITY(int gamerTagId, int component, bool toggle, any p3)l
extern _native64(0xEE76FF7E6A0166B0) void SET_ALL_MP_GAMER_TAGS_VISIBILITY(int gamerTagId, bool toggle)l
extern _native64(0xA67F9C46D612B6F1) void SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH(int gamerTagId, bool toggle)l
extern _native64(0xD29EC58C2F6B5014) void SET_MP_GAMER_TAGS_SHOULD_USE_POINTS_HEALTH(int gamerTagId, bool toggle)l
extern _native64(0x1563FE35E9928E67) void SET_MP_GAMER_TAGS_POINT_HEALTH(int gamerTagId, int value, int maximumValue)l
extern _native64(0x613ED644950626AE) void SET_MP_GAMER_TAG_COLOUR(int gamerTagId, int component, int hudColorIndex)l
extern _native64(0x3158C77A7E888AB4) void SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR(int gamerTagId, int hudColorIndex)l
extern _native64(0xD48FE545CD46F857) void SET_MP_GAMER_TAG_ALPHA(int gamerTagId, int component, int alpha)l
extern _native64(0xCF228E2AA03099C3) void SET_MP_GAMER_TAG_WANTED_LEVEL(int gamerTagId, int wantedlvl)l
extern _native64(0x9C16459B2324B2CF) void SET_MP_GAMER_TAG_NUM_PACKAGES(int gamerTagId, int p1)l
extern _native64(0xDEA2B8283BAA3944) void SET_MP_GAMER_TAG_NAME(int gamerTagId, const char* string)l
extern _native64(0xEB709A36958ABE0D) bool IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS(int gamerTagId)l
extern _native64(0x7B7723747CCB55B6) void SET_MP_GAMER_TAG_BIG_TEXT(int gamerTagId, const char* string)l
extern _native64(0x01A358D9128B7A86) int GET_CURRENT_WEBPAGE_ID()l
extern _native64(0x97D47996FC48CBAD) int GET_CURRENT_WEBSITE_ID()l
extern _native64(0xE3B05614DCE1D014) int GET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex)l
extern _native64(0xB99C4E4D9499DF29) void RESET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex)l
extern _native64(0xAF42195A42C63BBA) bool IS_WARNING_MESSAGE_READY_FOR_CONTROL()l
extern _native64(0x7B1776B3B53F8D74) void SET_WARNING_MESSAGE(const char* titleMsg, int flags, const char* promptMsg, bool p3, int p4, const char* p5, const char* p6, bool showBackground, int errorCode)l
extern _native64(0xDC38CC1E35B6A5D7) void SET_WARNING_MESSAGE_WITH_HEADER(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, any p5, any* showBackground, any* p7, bool p8, any p9)l
extern _native64(0x701919482C74B5AB) void SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, any p5, any additionalIntInfo, const char* additionalTextInfoLine1, const char* additionalTextInfoLine2, bool showBackground, int errorCode)l
extern _native64(0x38B55259C2E078ED) void SET_WARNING_MESSAGE_WITH_HEADER_EXTENDED(const char* entryHeader, const char* entryLine1, int flags, const char* entryLine2, bool p4, any p5, any* p6, any* p7, bool showBg, any p9, any p10)l
extern _native64(0x15803FEC3B9A872B) void SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS_EXTENDED(const char* labelTitle, const char* labelMessage, int p2, int p3, const char* labelMessage2, bool p5, int p6, int p7, const char* p8, const char* p9, bool background, int errorCode)l
extern _native64(0x81DF9ABA6C83DFF9) Hash GET_WARNING_SCREEN_MESSAGE_HASH()l
extern _native64(0x0C5A80A9E096D529) bool SET_WARNING_MESSAGE_OPTION_ITEMS(int index, const char* name, int cash, int rp, int lvl, int colour)l
extern _native64(0xDAF87174BE7454FF) bool SET_WARNING_MESSAGE_OPTION_HIGHLIGHT(any p0)l
extern _native64(0x6EF54AB721DC6242) void REMOVE_WARNING_MESSAGE_OPTION_ITEMS()l
extern _native64(0xE18B138FABC53103) bool IS_WARNING_MESSAGE_ACTIVE()l
extern _native64(0x7792424AA0EAC32E) void CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE()l
extern _native64(0x5354C5BA2EA868A4) void CUSTOM_MINIMAP_SET_ACTIVE(bool toggle)l
extern _native64(0x1EAE6DD17B7A5EFA) void CUSTOM_MINIMAP_SET_BLIP_OBJECT(int spriteId)l
extern _native64(0x551DF99658DB6EE8) int CUSTOM_MINIMAP_CREATE_BLIP(float x, float y, float z)l
extern _native64(0x2708FC083123F9FF) void CUSTOM_MINIMAP_CLEAR_BLIPS()l
extern _native64(0x1121BFA1A1A522A8) bool FORCE_SONAR_BLIPS_THIS_FRAME()l
extern _native64(0x3F0CF9CB7E589B88) Blip GET_NORTH_BLID_INDEX()l
extern _native64(0x82CEDC33687E1F50) void DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS(bool toggle)l
extern _native64(0x211C4EF450086857) void DRAW_FRONTEND_BACKGROUND_THIS_FRAME()l
extern _native64(0xBF4F34A85CA2970C) void DRAW_HUD_OVER_FADE_THIS_FRAME()l
extern _native64(0xEF01D36B9C9D0C7B) void ACTIVATE_FRONTEND_MENU(Hash menuhash, bool togglePause, int component)l
extern _native64(0x10706DC6AD2D49C0) void RESTART_FRONTEND_MENU(Hash menuHash, int p1)l
extern _native64(0x2309595AD6145265) Hash GET_CURRENT_FRONTEND_MENU_VERSION()l
extern _native64(0xDF47FC56C71569CF) void SET_PAUSE_MENU_ACTIVE(bool toggle)l
extern _native64(0x6D3465A73092F0E6) void DISABLE_FRONTEND_THIS_FRAME()l
extern _native64(0xBA751764F0821256) void SUPPRESS_FRONTEND_RENDERING_THIS_FRAME()l
extern _native64(0xCC3FDDED67BCFC63) void ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME()l
extern _native64(0x745711A75AB09277) void SET_FRONTEND_ACTIVE(bool active)l
extern _native64(0xB0034A223497FFCB) bool IS_PAUSE_MENU_ACTIVE()l
extern _native64(0x2F057596F2BD0061) bool IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN()l
extern _native64(0x272ACD84970869C5) int GET_PAUSE_MENU_STATE()l
extern _native64(0x5BFF36D6ED83E0AE) vector3 GET_PAUSE_MENU_POSITION()l
extern _native64(0x1C491717107431C7) bool IS_PAUSE_MENU_RESTARTING()l
extern _native64(0x2162C446DFDF38FD) void FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE(const char* p0)l
extern _native64(0x77F16B447824DA6C) void PAUSE_MENUCEPTION_GO_DEEPER(int page)l
extern _native64(0xCDCA26E80FAECB8F) void PAUSE_MENUCEPTION_THE_KICK()l
extern _native64(0x2DE6C5E2E996F178) void PAUSE_TOGGLE_FULLSCREEN_MAP(any p0)l
extern _native64(0xDD564BDD0472C936) void PAUSE_MENU_ACTIVATE_CONTEXT(Hash contextHash)l
extern _native64(0x444D8CF241EC25C5) void PAUSE_MENU_DEACTIVATE_CONTEXT(Hash contextHash)l
extern _native64(0x84698AB38D0C6636) bool PAUSE_MENU_IS_CONTEXT_ACTIVE(Hash contextHash)l
extern _native64(0x2A25ADC48F87841F) bool PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE()l
extern _native64(0xDE03620F8703A9DF) int PAUSE_MENU_GET_HAIR_COLOUR_INDEX()l
extern _native64(0x359AF31A4B52F5ED) int PAUSE_MENU_GET_MOUSE_HOVER_INDEX()l
extern _native64(0x13C4B962653A5280) int PAUSE_MENU_GET_MOUSE_HOVER_UNIQUE_ID()l
extern _native64(0xC8E1071177A23BE5) bool PAUSE_MENU_GET_MOUSE_CLICK_EVENT(any* p0, any* p1, any* p2)l
extern _native64(0x4895BDEA16E7C080) void PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS(int p0)l
extern _native64(0xC78E239AC5B2DDB9) void PAUSE_MENU_SET_BUSY_SPINNER(bool p0, int position, int spinnerIndex)l
extern _native64(0xF06EBB91A81E09E3) void PAUSE_MENU_SET_WARN_ON_TAB_CHANGE(bool p0)l
extern _native64(0x3BAB9A4E4F2FF5C7) bool IS_FRONTEND_READY_FOR_CONTROL()l
extern _native64(0xEC9264727EEC0F28) void TAKE_CONTROL_OF_FRONTEND()l
extern _native64(0x14621BB1DF14E2B2) void RELEASE_CONTROL_OF_FRONTEND()l
extern _native64(0x66E7CB63C97B7D20) bool CODE_WANTS_SCRIPT_TO_TAKE_CONTROL()l
extern _native64(0x593FEAE1F73392D4) int GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL()l
extern _native64(0x4E3CD0EF8A489541) bool IS_NAVIGATING_MENU_CONTENT()l
extern _native64(0xF284AC67940C6812) bool HAS_MENU_TRIGGER_EVENT_OCCURRED()l
extern _native64(0x2E22FEFA0100275E) bool HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED()l
extern _native64(0x0CF54F20DE43879C) void SET_SAVEGAME_LIST_UNIQUE_ID(any p0)l
extern _native64(0x36C1451A88A09630) void GET_MENU_TRIGGER_EVENT_DETAILS(int* lastItemMenuId, int* selectedItemUniqueId)l
extern _native64(0x7E17BE53E1AAABAF) void GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS(int* lastItemMenuId, int* selectedItemMenuId, int* selectedItemUniqueId)l
extern _native64(0xA238192F33110615) bool GET_PM_PLAYER_CREW_COLOR(int* r, int* g, int* b)l
extern _native64(0xEF4CED81CEBEDC6D) bool GET_MENU_PED_INT_STAT(any p0, any* p1)l
extern _native64(0xCA6B2F7CE32AB653) bool GET_CHARACTER_MENU_PED_INT_STAT(any p0, any* p1, any p2)l
extern _native64(0x90A6526CF0381030) bool GET_MENU_PED_MASKED_INT_STAT(Hash statHash, int* outValue, int mask, bool p3)l
extern _native64(0x24A49BEAF468DC90) bool GET_CHARACTER_MENU_PED_MASKED_INT_STAT(Hash statHash, any* outValue, int p2, int mask, bool p4)l
extern _native64(0x5FBD7095FE7AE57F) bool GET_MENU_PED_FLOAT_STAT(Hash statHash, float* outValue)l
extern _native64(0x8F08017F9D7C47BD) bool GET_CHARACTER_MENU_PED_FLOAT_STAT(float statHash, float* outValue, bool p2)l
extern _native64(0x052991E59076E4E4) bool GET_MENU_PED_BOOL_STAT(Hash statHash, bool* outValue)l
extern _native64(0x5E62BE5DC58E9E06) void CLEAR_PED_IN_PAUSE_MENU()l
extern _native64(0xAC0BFBDC3BE00E14) void GIVE_PED_TO_PAUSE_MENU(Ped ped, int p1)l
extern _native64(0x3CA6050692BC61B0) void SET_PAUSE_MENU_PED_LIGHTING(bool state)l
extern _native64(0xECF128344E9FF9F1) void SET_PAUSE_MENU_PED_SLEEP_STATE(bool state)l
extern _native64(0x805D7CBB36FD6C4C) void OPEN_ONLINE_POLICIES_MENU()l
extern _native64(0xF13FE2A80C05C561) bool ARE_ONLINE_POLICIES_UP_TO_DATE()l
extern _native64(0x6F72CD94F7B5B68C) bool IS_ONLINE_POLICIES_MENU_ACTIVE()l
extern _native64(0x75D3691713C3B05A) void OPEN_SOCIAL_CLUB_MENU(Hash menu)l
extern _native64(0xD2B32BE3FC1626C6) void CLOSE_SOCIAL_CLUB_MENU()l
extern _native64(0x9E778248D6685FE0) void SET_SOCIAL_CLUB_TOUR(const char* name)l
extern _native64(0xC406BE343FC4B9AF) bool IS_SOCIAL_CLUB_ACTIVE()l
extern _native64(0x1185A8087587322C) void SET_TEXT_INPUT_BOX_ENABLED(bool p0)l
extern _native64(0x8817605C2BA76200) void FORCE_CLOSE_TEXT_INPUT_BOX()l
extern _native64(0x577599CCED639CA2) void SET_ALLOW_COMMA_ON_TEXT_INPUT(any p0)l
extern _native64(0x6A1738B4323FE2D9) void OVERRIDE_MP_TEXT_CHAT_TEAM_STRING(Hash gxtEntryHash)l
extern _native64(0xB118AF58B5F332A1) bool IS_MP_TEXT_CHAT_TYPING()l
extern _native64(0x1AC8F4AD40E22127) void CLOSE_MP_TEXT_CHAT()l
extern _native64(0x7C226D5346D4D10A) void MP_TEXT_CHAT_IS_TEAM_JOB(any p0)l
extern _native64(0xF47E567B3630DD12) void OVERRIDE_MP_TEXT_CHAT_COLOR(int p0, int hudColor)l
extern _native64(0x1DB21A44B09E8BA3) void MP_TEXT_CHAT_DISABLE(bool toggle)l
extern _native64(0xCEF214315D276FD1) void FLAG_PLAYER_CONTEXT_IN_TOURNAMENT(bool toggle)l
extern _native64(0xD30C50DF888D58B5) void SET_PED_HAS_AI_BLIP(Ped ped, bool hasCone)l
extern _native64(0xB13DCB4C6FAAD238) void SET_PED_HAS_AI_BLIP_WITH_COLOUR(Ped ped, bool hasCone, int color)l
extern _native64(0x15B8ECF844EE67ED) bool DOES_PED_HAVE_AI_BLIP(Ped ped)l
extern _native64(0xE52B8E7F85D39A08) void SET_PED_AI_BLIP_GANG_ID(Ped ped, int gangId)l
extern _native64(0x3EED80DFF7325CAA) void SET_PED_AI_BLIP_HAS_CONE(Ped ped, bool toggle)l
extern _native64(0x0C4BBF625CA98C4E) void SET_PED_AI_BLIP_FORCED_ON(Ped ped, bool toggle)l
extern _native64(0x97C65887D4B37FA9) void SET_PED_AI_BLIP_NOTICE_RANGE(Ped ped, float range)l
extern _native64(0xFCFACD0DB9D7A57D) void SET_PED_AI_BLIP_SPRITE(Ped ped, int spriteId)l
extern _native64(0x7CD934010E115C2C) Blip GET_AI_PED_PED_BLIP_INDEX(Ped ped)l
extern _native64(0x56176892826A4FE8) Blip GET_AI_PED_VEHICLE_BLIP_INDEX(Ped ped)l
extern _native64(0xA277800A9EAE340E) bool HAS_DIRECTOR_MODE_BEEN_LAUNCHED_BY_CODE()l
extern _native64(0x2632482FD6B9AB87) void SET_DIRECTOR_MODE_LAUNCHED_BY_SCRIPT()l
extern _native64(0x808519373FD336A3) void SET_PLAYER_IS_IN_DIRECTOR_MODE(bool toggle)l
extern _native64(0x04655F9D075D0AE5) void SET_DIRECTOR_MODE_AVAILABLE(bool toggle)l
extern _native64(0x243296A510B562B6) void HIDE_HUDMARKERS_THIS_FRAME()l
#pragma endregion //}
#pragma region INTERIOR //{
extern _native64(0xF49B58631D9E22D9) float GET_INTERIOR_HEADING(Interior interior)l
extern _native64(0x252BDC06B73FA6EA) void GET_INTERIOR_LOCATION_AND_NAMEHASH(Interior interior, vector3* position, Hash* nameHash)l
extern _native64(0xE4A84ABF135EF91A) int GET_INTERIOR_GROUP_ID(Interior interior)l
extern _native64(0x9E3B3E6D66F6E22F) vector3 GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(Interior interior, float x, float y, float z)l
extern _native64(0xBC72B5D7A1CBD54D) bool IS_INTERIOR_SCENE()l
extern _native64(0x26B0E73D7EAAF4D3) bool IS_VALID_INTERIOR(Interior interior)l
extern _native64(0xB365FC0C4E27FFA7) void CLEAR_ROOM_FOR_ENTITY(Entity entity)l
extern _native64(0x52923C4710DD9907) void FORCE_ROOM_FOR_ENTITY(Entity entity, Interior interior, Hash roomHashKey)l
extern _native64(0x47C2A06D4F5F424B) Hash GET_ROOM_KEY_FROM_ENTITY(Entity entity)l
extern _native64(0x399685DB942336BC) Hash GET_KEY_FOR_ENTITY_IN_ROOM(Entity entity)l
extern _native64(0x2107BA504071A6BB) Interior GET_INTERIOR_FROM_ENTITY(Entity entity)l
extern _native64(0x82EBB79E258FA2B7) void RETAIN_ENTITY_IN_INTERIOR(Entity entity, Interior interior)l
extern _native64(0x85D5422B2039A70D) void CLEAR_INTERIOR_STATE_OF_ENTITY(Entity entity)l
extern _native64(0x38C1CB1CB119A016) void FORCE_ACTIVATING_TRACKING_ON_ENTITY(any p0, any p1)l
extern _native64(0x920D853F3E17F1DA) void FORCE_ROOM_FOR_GAME_VIEWPORT(int interiorID, Hash roomHashKey)l
extern _native64(0xAF348AFCB575A441) void SET_ROOM_FOR_GAME_VIEWPORT_BY_NAME(const char* roomName)l
extern _native64(0x405DC2AEF6AF95B9) void SET_ROOM_FOR_GAME_VIEWPORT_BY_KEY(Hash roomHashKey)l
extern _native64(0xA6575914D2A0B450) Hash GET_ROOM_KEY_FOR_GAME_VIEWPORT()l
extern _native64(0x23B59D8912F94246) void CLEAR_ROOM_FOR_GAME_VIEWPORT()l
extern _native64(0xE7D267EC6CA966C3) Interior GET_INTERIOR_FROM_PRIMARY_VIEW()l
extern _native64(0xB0F7F8663821D9C3) Interior GET_INTERIOR_AT_COORDS(float x, float y, float z)l
extern _native64(0x3F6167F351168730) void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Pickup pickup, const char* roomName)l
extern _native64(0x2CA429C029CCF247) void PIN_INTERIOR_IN_MEMORY(Interior interior)l
extern _native64(0x261CCE7EED010641) void UNPIN_INTERIOR(Interior interior)l
extern _native64(0x6726BDCCC1932F0E) bool IS_INTERIOR_READY(Interior interior)l
extern _native64(0x4C2330E61D3DEB56) bool SET_INTERIOR_IN_USE(Interior interior)l
extern _native64(0x05B7A89BD78797FC) Interior GET_INTERIOR_AT_COORDS_WITH_TYPE(float x, float y, float z, const char* interiorType)l
extern _native64(0xF0F77ADB9F67E79D) Interior GET_INTERIOR_AT_COORDS_WITH_TYPEHASH(float x, float y, float z, Hash typeHash)l
extern _native64(0x483ACA1176CA93F1) void ACTIVATE_INTERIOR_GROUPS_USING_CAMERA()l
extern _native64(0xEEA5AC2EDA7C33E8) bool IS_COLLISION_MARKED_OUTSIDE(float x, float y, float z)l
extern _native64(0xEC4CF9FCB29A4424) Interior GET_INTERIOR_FROM_COLLISION(float x, float y, float z)l
extern _native64(0x7ECDF98587E92DEC) void ENABLE_STADIUM_PROBES_THIS_FRAME(bool toggle)l
extern _native64(0x55E86AF2712B36A1) void ACTIVATE_INTERIOR_ENTITY_SET(Interior interior, const char* entitySetName)l
extern _native64(0x420BD37289EEE162) void DEACTIVATE_INTERIOR_ENTITY_SET(Interior interior, const char* entitySetName)l
extern _native64(0x35F7DD45E8C0A16D) bool IS_INTERIOR_ENTITY_SET_ACTIVE(Interior interior, const char* entitySetName)l
extern _native64(0xC1F1920BAF281317) void SET_INTERIOR_ENTITY_SET_TINT_INDEX(Interior interior, const char* entitySetName, int color)l
extern _native64(0x41F37C3427C75AE0) void REFRESH_INTERIOR(Interior interior)l
extern _native64(0xA97F257D0151A6AB) void ENABLE_EXTERIOR_CULL_MODEL_THIS_FRAME(Hash mapObjectHash)l
extern _native64(0x50C375537449F369) void ENABLE_SHADOW_CULL_MODEL_THIS_FRAME(Hash mapObjectHash)l
extern _native64(0x6170941419D7D8EC) void DISABLE_INTERIOR(Interior interior, bool toggle)l
extern _native64(0xBC5115A5A939DD15) bool IS_INTERIOR_DISABLED(Interior interior)l
extern _native64(0xD9175F941610DB54) void CAP_INTERIOR(Interior interior, bool toggle)l
extern _native64(0x92BAC8ACF88CEC26) bool IS_INTERIOR_CAPPED(Interior interior)l
extern _native64(0x9E6542F0CE8E70A3) void DISABLE_METRO_SYSTEM(bool toggle)l
extern _native64(0x7241CCB7D020DB69) void SET_IS_EXTERIOR_ONLY(Entity entity, bool toggle)l
#pragma endregion //}
#pragma region ITEMSET //{
extern _native64(0x35AD299F50D91B24) ScrHandle CREATE_ITEMSET(bool p0)l
extern _native64(0xDE18220B1C183EDA) void DESTROY_ITEMSET(ScrHandle itemset)l
extern _native64(0xB1B1EA596344DFAB) bool IS_ITEMSET_VALID(ScrHandle itemset)l
extern _native64(0xE3945201F14637DD) bool ADD_TO_ITEMSET(ScrHandle item, ScrHandle itemset)l
extern _native64(0x25E68244B0177686) void REMOVE_FROM_ITEMSET(ScrHandle item, ScrHandle itemset)l
extern _native64(0xD9127E83ABF7C631) int GET_ITEMSET_SIZE(ScrHandle itemset)l
extern _native64(0x7A197E2521EE2BAB) ScrHandle GET_INDEXED_ITEM_IN_ITEMSET(int index, ScrHandle itemset)l
extern _native64(0x2D0FC594D1E9C107) bool IS_IN_ITEMSET(ScrHandle item, ScrHandle itemset)l
extern _native64(0x41BC0D722FC04221) void CLEAN_ITEMSET(ScrHandle itemset)l
#pragma endregion //}
#pragma region LOADINGSCREEN //{
extern _native64(0xF2CA003F167E21D2) bool LOBBY_AUTO_MULTIPLAYER_MENU()l
extern _native64(0xEF7D17BC6C85264C) bool LOBBY_AUTO_MULTIPLAYER_FREEMODE()l
extern _native64(0xB0C56BD3D808D863) void LOBBY_SET_AUTO_MULTIPLAYER(bool toggle)l
extern _native64(0x8AA464D4E0F6ACCD) bool LOBBY_AUTO_MULTIPLAYER_EVENT()l
extern _native64(0xFC309E94546FCDB5) void LOBBY_SET_AUTO_MULTIPLAYER_EVENT(bool toggle)l
extern _native64(0xC6DC823253FBB366) bool LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB()l
extern _native64(0xC7E7181C09F33B69) void LOBBY_SET_AUTO_MP_RANDOM_JOB(bool toggle)l
extern _native64(0xFA1E0E893D915215) void SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER(bool toggle)l
#pragma endregion //}
#pragma region LOCALIZATION //{
extern _native64(0x497420E022796B3F) int LOCALIZATION_GET_SYSTEM_LANGUAGE()l
extern _native64(0x2BDD44CC428A7EAE) int GET_CURRENT_LANGUAGE()l
extern _native64(0xA8AE43AEC1A61314) int LOCALIZATION_GET_SYSTEM_DATE_TYPE()l
#pragma endregion //}
#pragma region MISC //{
extern _native64(0x8B3CA62B1EF19B62) int GET_ALLOCATED_STACK_SIZE()l
extern _native64(0xFEAD16FC8F9DFC0F) int GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(int stackSize)l
extern _native64(0x444D98F98C11F3EC) void SET_RANDOM_SEED(int seed)l
extern _native64(0x1D408577D440E81E) void SET_TIME_SCALE(float timeScale)l
extern _native64(0xC4301E5121A0ED73) void SET_MISSION_FLAG(bool toggle)l
extern _native64(0xA33CDCCDA663159E) bool GET_MISSION_FLAG()l
extern _native64(0x971927086CFD2158) void SET_RANDOM_EVENT_FLAG(bool toggle)l
extern _native64(0xD2D57F1D764117B1) bool GET_RANDOM_EVENT_FLAG()l
extern _native64(0x24DA7D7667FD7B09) const char* GET_CONTENT_TO_LOAD()l
extern _native64(0x4DCDF92BF64236CD) void ACTIVITY_FEED_CREATE(const char* p0, const char* p1)l
extern _native64(0x31125FD509D9043F) void ACTIVITY_FEED_ADD_SUBSTRING_TO_CAPTION(const char* p0)l
extern _native64(0xEBD3205A207939ED) void ACTIVITY_FEED_ADD_LITERAL_SUBSTRING_TO_CAPTION(const char* p0)l
extern _native64(0x97E7E2C04245115B) void ACTIVITY_FEED_ADD_INT_TO_CAPTION(any p0)l
extern _native64(0x916CA67D26FD1E37) void ACTIVITY_FEED_LARGE_IMAGE_URL(const char* p0)l
extern _native64(0xEB078CA2B5E82ADD) void ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE(const char* p0, const char* p1)l
extern _native64(0x703CC7F60CBB2B57) void ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE_ADD(const char* p0)l
extern _native64(0x8951EB9C6906D3C8) void ACTIVITY_FEED_POST()l
extern _native64(0xBA4B8D83BDC75551) void ACTIVITY_FEED_ONLINE_PLAYED_WITH_POST(const char* p0)l
extern _native64(0xE8B9C0EC9E183F35) bool HAS_RESUMED_FROM_SUSPEND()l
extern _native64(0x65D2EBB47E1CEC21) void SET_SCRIPT_HIGH_PRIO(bool toggle)l
extern _native64(0x6F2135B6129620C1) void SET_THIS_IS_A_TRIGGER_SCRIPT(bool toggle)l
extern _native64(0x8D74E26F54B4E5C3) void INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION(const char* p0)l
extern _native64(0xB335F761606DB47C) bool GET_BASE_ELEMENT_LOCATION_FROM_METADATA_BLOCK(any* p0, any* p1, any p2, bool p3)l
extern _native64(0x564B884A05EC45A3) Hash GET_PREV_WEATHER_TYPE_HASH_NAME()l
extern _native64(0x711327CD09C8F162) Hash GET_NEXT_WEATHER_TYPE_HASH_NAME()l
extern _native64(0x44F28F86433B10A9) bool IS_PREV_WEATHER_TYPE(const char* weatherType)l
extern _native64(0x2FAA3A30BEC0F25D) bool IS_NEXT_WEATHER_TYPE(const char* weatherType)l
extern _native64(0x704983DF373B198F) void SET_WEATHER_TYPE_PERSIST(const char* weatherType)l
extern _native64(0xED712CA327900C8A) void SET_WEATHER_TYPE_NOW_PERSIST(const char* weatherType)l
extern _native64(0x29B487C359E19889) void SET_WEATHER_TYPE_NOW(const char* weatherType)l
extern _native64(0xFB5045B7C42B75BF) void SET_WEATHER_TYPE_OVERTIME_PERSIST(const char* weatherType, float time)l
extern _native64(0x8B05F884CF7E8020) void SET_RANDOM_WEATHER_TYPE()l
extern _native64(0xCCC39339BEF76CF5) void CLEAR_WEATHER_TYPE_PERSIST()l
extern _native64(0x0CF97F497FE7D048) void CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK(int milliseconds)l
extern _native64(0xF3BBE884A14BB413) void GET_CURR_WEATHER_STATE(Hash* weatherType1, Hash* weatherType2, float* percentWeather2)l
extern _native64(0x578C752848ECFA0C) void SET_CURR_WEATHER_STATE(Hash weatherType1, Hash weatherType2, float percentWeather2)l
extern _native64(0xA43D5C6FE51ADBEF) void SET_OVERRIDE_WEATHER(const char* weatherType)l
extern _native64(0x1178E104409FE58C) void SET_OVERRIDE_WEATHEREX(const char* weatherType, bool p1)l
extern _native64(0x338D2E3477711050) void CLEAR_OVERRIDE_WEATHER()l
extern _native64(0xB8F87EAD7533B176) void WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE(float amplitude)l
extern _native64(0xC3EAD29AB273ECE8) void WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE(float minAmplitude)l
extern _native64(0xA7A1127490312C36) void WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE(float maxAmplitude)l
extern _native64(0x31727907B2C43C55) void WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE(float minAmplitude)l
extern _native64(0x405591EC8FD9096D) void WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE(float amplitude)l
extern _native64(0xF751B16FB32ABC1D) void WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE(float minAmplitude)l
extern _native64(0xB3E6360DDE733E82) void WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE(float maxAmplitude)l
extern _native64(0x7C9C0B1EEB1F9072) void WATER_OVERRIDE_SET_RIPPLEBUMPINESS(float bumpiness)l
extern _native64(0x6216B116083A7CB4) void WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS(float minBumpiness)l
extern _native64(0x9F5E6BB6B34540DA) void WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS(float maxBumpiness)l
extern _native64(0xB9854DFDE0D833D6) void WATER_OVERRIDE_SET_RIPPLEDISTURB(float disturb)l
extern _native64(0xC54A08C85AE4D410) void WATER_OVERRIDE_SET_STRENGTH(float strength)l
extern _native64(0xA8434F1DFF41D6E7) void WATER_OVERRIDE_FADE_IN(float p0)l
extern _native64(0xC3C221ADDDE31A11) void WATER_OVERRIDE_FADE_OUT(float p0)l
extern _native64(0xAC3A74E8384A9919) void SET_WIND(float speed)l
extern _native64(0xEE09ECEDBABE47FC) void SET_WIND_SPEED(float speed)l
extern _native64(0xA8CF1CC0AFCD3F12) float GET_WIND_SPEED()l
extern _native64(0xEB0F4468467B4528) void SET_WIND_DIRECTION(float direction)l
extern _native64(0x1F400FEF721170DA) vector3 GET_WIND_DIRECTION()l
extern _native64(0x643E26EA6E024D92) void SET_RAIN(float intensity)l
extern _native64(0x96695E368AD855F3) float GET_RAIN_LEVEL()l
extern _native64(0x7F06937B0CDCBC1A) void SET_SNOW(float level)l
extern _native64(0xC5868A966E5BE3AE) float GET_SNOW_LEVEL()l
extern _native64(0xF6062E089251C898) void FORCE_LIGHTNING_FLASH()l
extern _native64(0x02DEAAC8F8EA7FE7) void SET_CLOUD_SETTINGS_OVERRIDE(const char* p0)l
extern _native64(0x11B56FBBF7224868) void PRELOAD_CLOUD_HAT(const char* name)l
extern _native64(0xFC4842A34657BFCB) void LOAD_CLOUD_HAT(const char* name, float transitionTime)l
extern _native64(0xA74802FB8D0B7814) void UNLOAD_CLOUD_HAT(const char* name, float p1)l
extern _native64(0x957E790EA1727B64) void UNLOAD_ALL_CLOUD_HATS()l
extern _native64(0xF36199225D6D8C86) void SET_CLOUDS_ALPHA(float opacity)l
extern _native64(0x20AC25E781AE4A84) float GET_CLOUDS_ALPHA()l
extern _native64(0x9CD27B0045628463) int GET_GAME_TIMER()l
extern _native64(0x15C40837039FFAF7) float GET_FRAME_TIME()l
extern _native64(0xE599A503B3837E1B) float GET_SYSTEM_TIME_STEP()l
extern _native64(0xFC8202EFC642E6F2) int GET_FRAME_COUNT()l
extern _native64(0x313CE5879CEB6FCD) float GET_RANDOM_FLOAT_IN_RANGE(float startRange, float endRange)l
extern _native64(0xD53343AA4FB7DD28) int GET_RANDOM_INT_IN_RANGE(int startRange, int endRange)l
extern _native64(0xF2D49816A804D134) int GET_RANDOM_MWC_INT_IN_RANGE(int startRange, int endRange)l
extern _native64(0xC906A7DAB05C8D2B) bool GET_GROUND_Z_FOR_3D_COORD(float x, float y, float z, float* groundZ, bool ignoreWater, bool p5)l
extern _native64(0x8BDC7BFC57A81E76) bool GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD(float x, float y, float z, float* groundZ, vector3* normal)l
extern _native64(0x9E82F0F362881B29) bool GET_GROUND_Z_EXCLUDING_OBJECTS_FOR_3D_COORD(float x, float y, float z, float* groundZ, bool p4, bool p5)l
extern _native64(0xC843060B5765DCE7) float ASIN(float p0)l
extern _native64(0x1D08B970013C34B6) float ACOS(float p0)l
extern _native64(0x632106CC96E82E91) float TAN(float p0)l
extern _native64(0xA9D1795CD5043663) float ATAN(float p0)l
extern _native64(0x8927CBF9D22261A4) float ATAN2(float p0, float p1)l
extern _native64(0xF1B760881820C952) float GET_DISTANCE_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, bool useZ)l
extern _native64(0x186FC4BE848E1C92) float GET_ANGLE_BETWEEN_2D_VECTORS(float x1, float y1, float x2, float y2)l
extern _native64(0x2FFB6B224F4B2926) float GET_HEADING_FROM_VECTOR_2D(float dx, float dy)l
extern _native64(0x7F8F6405F4777AF6) float GET_RATIO_OF_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, bool clamp)l
extern _native64(0x21C235BC64831E5A) vector3 GET_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, bool clamp)l
extern _native64(0xF56DFB7B61BE7276) bool GET_LINE_PLANE_INTERSECTION(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float* p12)l
extern _native64(0xA0AD167E4B39D9A2) bool GET_POINT_AREA_OVERLAP(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10, any p11, any p12, any p13)l
extern _native64(0x933D6A9EEC1BACD0) void SET_BIT(int* address, int offset)l
extern _native64(0xE80492A9AC099A93) void CLEAR_BIT(int* address, int offset)l
extern _native64(0xD24D37CC275948CC) Hash GET_HASH_KEY(const char* string)l
extern _native64(0xF2F6A2FA49278625) void SLERP_NEAR_QUATERNION(float t, float x, float y, float z, float w, float x1, float y1, float z1, float w1, float* outX, float* outY, float* outZ, float* outW)l
extern _native64(0xA61B4DF533DCB56E) bool IS_AREA_OCCUPIED(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9, bool p10, any p11, bool p12)l
extern _native64(0x39455BF4F4F55186) bool IS_AREA_OCCUPIED_SLOW(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10, any p11, any p12)l
extern _native64(0xADCDE75E1C60F32D) bool IS_POSITION_OCCUPIED(float x, float y, float z, float range, bool p4, bool checkVehicles, bool checkPeds, bool p7, bool p8, Entity ignoreEntity, bool p10)l
extern _native64(0xE54E209C35FFA18D) bool IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native64(0xA56F01F3765B93A0) void CLEAR_AREA(float X, float Y, float Z, float radius, bool p4, bool ignoreCopCars, bool ignoreObjects, bool p7)l
extern _native64(0x957838AAF91BD12D) void CLEAR_AREA_LEAVE_VEHICLE_HEALTH(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7)l
extern _native64(0x01C7B9B38428AEB6) void CLEAR_AREA_OF_VEHICLES(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7, bool p8, bool p9, any p10)l
extern _native64(0x11DB3500F042A8AA) void CLEAR_ANGLED_AREA_OF_VEHICLES(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool p7, bool p8, bool p9, bool p10, bool p11, any p12, any p13)l
extern _native64(0xDD9B9B385AAC7F5B) void CLEAR_AREA_OF_OBJECTS(float x, float y, float z, float radius, int flags)l
extern _native64(0xBE31FD6CE464AC59) void CLEAR_AREA_OF_PEDS(float x, float y, float z, float radius, int flags)l
extern _native64(0x04F8FC8FCF58F88D) void CLEAR_AREA_OF_COPS(float x, float y, float z, float radius, int flags)l
extern _native64(0x0A1CB9094635D1A6) void CLEAR_AREA_OF_PROJECTILES(float x, float y, float z, float radius, int flags)l
extern _native64(0x7EC6F9A478A6A512) void CLEAR_SCENARIO_SPAWN_HISTORY()l
extern _native64(0xC9BF75D28165FF77) void SET_SAVE_MENU_ACTIVE(bool ignoreVehicle)l
extern _native64(0x397BAA01068BAA96) int GET_STATUS_OF_MANUAL_SAVE()l
extern _native64(0xB938B7E6D3C0620C) void SET_CREDITS_ACTIVE(bool toggle)l
extern _native64(0xB51B9AB9EF81868C) void SET_CREDITS_FADE_OUT_WITH_SCREEN(bool toggle)l
extern _native64(0x075F1D57402C93BA) bool HAVE_CREDITS_REACHED_END()l
extern _native64(0xD19C0826DC20CF1C) bool ARE_CREDITS_RUNNING()l
extern _native64(0x9DC711BC69C548DF) void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(const char* scriptName)l
extern _native64(0x9243BAC96D64C050) void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME()l
extern _native64(0x1F464EF988465A81) int ADD_HOSPITAL_RESTART(float x, float y, float z, float p3, any p4)l
extern _native64(0xC8535819C450EBA8) void DISABLE_HOSPITAL_RESTART(int hospitalIndex, bool toggle)l
extern _native64(0x452736765B31FC4B) int ADD_POLICE_RESTART(float p0, float p1, float p2, float p3, any p4)l
extern _native64(0x23285DED6EBD7EA3) void DISABLE_POLICE_RESTART(int policeIndex, bool toggle)l
extern _native64(0x706B5EDCAA7FA663) void SET_RESTART_COORD_OVERRIDE(float x, float y, float z, float heading)l
extern _native64(0xA2716D40842EAF79) void CLEAR_RESTART_COORD_OVERRIDE()l
extern _native64(0x2C2B3493FBF51C71) void PAUSE_DEATH_ARREST_RESTART(bool toggle)l
extern _native64(0x21FFB63D8C615361) void IGNORE_NEXT_RESTART(bool toggle)l
extern _native64(0x4A18E01DF2C87B86) void SET_FADE_OUT_AFTER_DEATH(bool toggle)l
extern _native64(0x1E0B4DC0D990A4E7) void SET_FADE_OUT_AFTER_ARREST(bool toggle)l
extern _native64(0xDA66D2796BA33F12) void SET_FADE_IN_AFTER_DEATH_ARREST(bool toggle)l
extern _native64(0xF3D78F59DFE18D79) void SET_FADE_IN_AFTER_LOAD(bool toggle)l
extern _native64(0xC0714D0A7EEECA54) int REGISTER_SAVE_HOUSE(float x, float y, float z, float p3, const char* p4, any p5, any p6)l
extern _native64(0x4F548CABEAE553BC) void SET_SAVE_HOUSE(int savehouseHandle, bool p1, bool p2)l
extern _native64(0x1162EA8AE9D24EEA) bool OVERRIDE_SAVE_HOUSE(bool p0, float p1, float p2, float p3, float p4, bool p5, float p6, float p7)l
extern _native64(0xA4A0065E39C9F25C) bool GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD(vector3* p0, float* p1, bool* fadeInAfterLoad, bool* p3)l
extern _native64(0x50EEAAD86232EE55) void DO_AUTO_SAVE()l
extern _native64(0x6E04F06094C87047) bool GET_IS_AUTO_SAVE_OFF()l
extern _native64(0x69240733738C19A0) bool IS_AUTO_SAVE_IN_PROGRESS()l
extern _native64(0x2107A3773771186D) bool HAS_CODE_REQUESTED_AUTOSAVE()l
extern _native64(0x06462A961E94B67C) void CLEAR_CODE_REQUESTED_AUTOSAVE()l
extern _native64(0xE0E500246FF73D66) void BEGIN_REPLAY_STATS(any p0, any p1)l
extern _native64(0x69FE6DC87BD2A5E9) void ADD_REPLAY_STAT_VALUE(any value)l
extern _native64(0xA23E821FBDF8A5F2) void END_REPLAY_STATS()l
extern _native64(0xD642319C54AADEB6) bool HAVE_REPLAY_STATS_BEEN_STORED()l
extern _native64(0x5B1F2E327B6B6FE1) int GET_REPLAY_STAT_MISSION_ID()l
extern _native64(0x2B626A0150E4D449) int GET_REPLAY_STAT_MISSION_TYPE()l
extern _native64(0xDC9274A7EF6B2867) int GET_REPLAY_STAT_COUNT()l
extern _native64(0x8098C8D6597AAE18) int GET_REPLAY_STAT_AT_INDEX(int index)l
extern _native64(0x1B1AB132A16FDA55) void CLEAR_REPLAY_STATS()l
extern _native64(0x72DE52178C291CB5) bool QUEUE_MISSION_REPEAT_LOAD()l
extern _native64(0x44A0BDC559B35F6E) bool QUEUE_MISSION_REPEAT_SAVE()l
extern _native64(0xEB2104E905C6F2E9) bool QUEUE_MISSION_REPEAT_SAVE_FOR_BENCHMARK_TEST()l
extern _native64(0x2B5E102E4A42F2BF) int GET_STATUS_OF_MISSION_REPEAT_SAVE()l
extern _native64(0x8A75CE2956274ADD) bool IS_MEMORY_CARD_IN_USE()l
extern _native64(0x867654CBC7606F2C) void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed)l
extern _native64(0xE3A7742E0B7A2F8B) void SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, any p14)l
extern _native64(0xBFE5756E7407064A) void SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, bool p14, bool p15, Entity targetEntity, bool p17, any p18, any p19, any p20)l
extern _native64(0x03E8D3D5F549087A) void GET_MODEL_DIMENSIONS(Hash modelHash, vector3* minimum, vector3* maximum)l
extern _native64(0x1454F2448DE30163) void SET_FAKE_WANTED_LEVEL(int fakeWantedLevel)l
extern _native64(0x4C9296CBCD1B971E) int GET_FAKE_WANTED_LEVEL()l
extern _native64(0xF14878FC50BEC6EE) void USING_MISSION_CREATOR(bool toggle)l
extern _native64(0xDEA36202FC3382DF) void ALLOW_MISSION_CREATOR_WARP(bool toggle)l
extern _native64(0x19E00D7322C6F85B) void SET_MINIGAME_IN_PROGRESS(bool toggle)l
extern _native64(0x2B4A15E44DE0F478) bool IS_MINIGAME_IN_PROGRESS()l
extern _native64(0x7B30F65D7B710098) bool IS_THIS_A_MINIGAME_SCRIPT()l
extern _native64(0x61A23B7EDA9BDA24) bool IS_SNIPER_INVERTED()l
extern _native64(0xD3D15555431AB793) bool SHOULD_USE_METRIC_MEASUREMENTS()l
extern _native64(0xC488FF2356EA7791) int GET_PROFILE_SETTING(int profileSetting)l
extern _native64(0x0C515FAB3FF9EA92) bool ARE_STRINGS_EQUAL(const char* string1, const char* string2)l
extern _native64(0x1E34710ECD4AB0EB) int COMPARE_STRINGS(const char* str1, const char* str2, bool matchCase, int maxLength)l
extern _native64(0xF0D31AD191A74F87) int ABSI(int value)l
extern _native64(0x73D57CFFDD12C355) float ABSF(float value)l
extern _native64(0xFEFCF11B01287125) bool IS_SNIPER_BULLET_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x5270A8FBC098C3F8) bool IS_PROJECTILE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool ownedByPlayer)l
extern _native64(0x2E0DC353342C4A6D) bool IS_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, int type, bool ownedByPlayer)l
extern _native64(0xF0BC12401061DEA0) bool IS_PROJECTILE_TYPE_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, any p7, bool ownedByPlayer)l
extern _native64(0x34318593248C8FB2) bool IS_PROJECTILE_TYPE_WITHIN_DISTANCE(float x, float y, float z, Hash projectileHash, float radius, bool ownedByPlayer)l
extern _native64(0x8D7A43EC6A5FEA45) bool GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, Hash projectileHash, vector3* projectilePos, bool ownedByPlayer)l
extern _native64(0x3DA8C28346B62CED) bool GET_COORDS_OF_PROJECTILE_TYPE_IN_ANGLED_AREA(float vecAngledAreaPoint1X, float vecAngledAreaPoint1Y, float vecAngledAreaPoint1Z, float vecAngledAreaPoint2X, float vecAngledAreaPoint2Y, float vecAngledAreaPoint2Z, float distanceOfOppositeFace, Hash weaponType, vector3* positionOut, bool bIsPlayer)l
extern _native64(0xDFB4138EEFED7B81) bool GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, vector3* outCoords, bool p4)l
extern _native64(0x82FDE6A57EE4EE44) bool GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, vector3* outCoords, Object* outProjectile, bool p5)l
extern _native64(0x1A8B5F3C01E2B477) bool IS_BULLET_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool ownedByPlayer)l
extern _native64(0x3F2023999AD51C1F) bool IS_BULLET_IN_AREA(float x, float y, float z, float radius, bool ownedByPlayer)l
extern _native64(0xDE0F6D7450D37351) bool IS_BULLET_IN_BOX(float x1, float y1, float z1, float x2, float y2, float z2, bool ownedByPlayer)l
extern _native64(0x9870ACFB89A90995) bool HAS_BULLET_IMPACTED_IN_AREA(float x, float y, float z, float p3, bool p4, bool p5)l
extern _native64(0xDC8C5D7CFEAB8394) bool HAS_BULLET_IMPACTED_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7)l
extern _native64(0xA72BC0B675B1519E) bool IS_ORBIS_VERSION()l
extern _native64(0x4D982ADB1978442D) bool IS_DURANGO_VERSION()l
extern _native64(0xF6201B4DAF662A9D) bool IS_XBOX360_VERSION()l
extern _native64(0xCCA1072C29D096C2) bool IS_PS3_VERSION()l
extern _native64(0x48AF36444B965238) bool IS_PC_VERSION()l
extern _native64(0x0A27B2B6282F7169) bool IS_STEAM_VERSION()l
extern _native64(0x9F1935CA1F724008) bool IS_AUSSIE_VERSION()l
extern _native64(0xB8C0BB75D8A77DB3) bool IS_JAPANESE_VERSION()l
extern _native64(0x138679CA01E21F53) bool IS_XBOX_PLATFORM()l
extern _native64(0xC545AB1CF97ABB34) bool IS_SCARLETT_VERSION()l
extern _native64(0xF911E695C1EB8518) bool IS_SCE_PLATFORM()l
extern _native64(0x807ABE1AB65C24D2) bool IS_PROSPERO_VERSION()l
extern _native64(0xF22B6C47C6EAB066) bool IS_STRING_NULL(const char* string)l
extern _native64(0xCA042B6957743895) bool IS_STRING_NULL_OR_EMPTY(const char* string)l
extern _native64(0x5A5F40FE637EB584) bool STRING_TO_INT(const char* string, int* outInteger)l
extern _native64(0x8EF07E15701D61ED) void SET_BITS_IN_RANGE(int* var, int rangeStart, int rangeEnd, int p3)l
extern _native64(0x53158863FCC0893A) int GET_BITS_IN_RANGE(int var, int rangeStart, int rangeEnd)l
extern _native64(0x1A992DA297A4630C) int ADD_STUNT_JUMP(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float camX, float camY, float camZ, int p15, int p16, int p17)l
extern _native64(0xBBE5D803A5360CBF) int ADD_STUNT_JUMP_ANGLED(float x1, float y1, float z1, float x2, float y2, float z2, float radius1, float x3, float y3, float z3, float x4, float y4, float z4, float radius2, float camX, float camY, float camZ, int p17, int p18, int p19)l
extern _native64(0xFB80AB299D2EE1BD) void TOGGLE_SHOW_OPTIONAL_STUNT_JUMP_CAMERA(bool toggle)l
extern _native64(0xDC518000E39DAE1F) void DELETE_STUNT_JUMP(int p0)l
extern _native64(0xE369A5783B866016) void ENABLE_STUNT_JUMP_SET(int p0)l
extern _native64(0xA5272EBEDD4747F6) void DISABLE_STUNT_JUMP_SET(int p0)l
extern _native64(0xD79185689F8FD5DF) void SET_STUNT_JUMPS_CAN_TRIGGER(bool toggle)l
extern _native64(0x7A3F19700A4D0525) bool IS_STUNT_JUMP_IN_PROGRESS()l
extern _native64(0x2272B0A1343129F4) bool IS_STUNT_JUMP_MESSAGE_SHOWING()l
extern _native64(0x996DD1E1E02F1008) int GET_NUM_SUCCESSFUL_STUNT_JUMPS()l
extern _native64(0x6856EC3D35C81EA4) int GET_TOTAL_SUCCESSFUL_STUNT_JUMPS()l
extern _native64(0xE6B7B0ACD4E4B75E) void CANCEL_STUNT_JUMP()l
extern _native64(0x577D1284D6873711) void SET_GAME_PAUSED(bool toggle)l
extern _native64(0xAA391C728106F7AF) void SET_THIS_SCRIPT_CAN_BE_PAUSED(bool toggle)l
extern _native64(0xB98236CAAECEF897) void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(bool toggle)l
extern _native64(0x071E2A839DE82D90) bool HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash, int amount)l
extern _native64(0x557E43C447E700A8) bool HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash)l
extern _native64(0xFA3FFB0EEBC288A3) void OVERRIDE_FREEZE_FLAGS(bool p0)l
extern _native64(0x9BAE5AD2508DF078) void SET_INSTANCE_PRIORITY_MODE(int p0)l
extern _native64(0xC5F0A8EBD3F361CE) void SET_INSTANCE_PRIORITY_HINT(int flag)l
extern _native64(0x7EA2B6AF97ECA6ED) bool IS_FRONTEND_FADING()l
extern _native64(0x7472BB270D7B4F3E) void POPULATE_NOW()l
extern _native64(0xCBAD6729F7B1F4FC) int GET_INDEX_OF_CURRENT_LEVEL()l
extern _native64(0x740E14FAD5842351) void SET_GRAVITY_LEVEL(int level)l
extern _native64(0xA9575F812C6A7997) void START_SAVE_DATA(any* p0, any p1, bool p2)l
extern _native64(0x74E20C9145FB66FD) void STOP_SAVE_DATA()l
extern _native64(0xA09F896CE912481F) int GET_SIZE_OF_SAVE_DATA(bool p0)l
extern _native64(0x34C9EE5986258415) void REGISTER_INT_TO_SAVE(any* p0, const char* name)l
extern _native64(0xA735353C77334EA0) void REGISTER_INT64_TO_SAVE(any* p0, const char* name)l
extern _native64(0x10C2FA78D0E128A1) void REGISTER_ENUM_TO_SAVE(any* p0, const char* name)l
extern _native64(0x7CAEC29ECB5DFEBB) void REGISTER_FLOAT_TO_SAVE(any* p0, const char* name)l
extern _native64(0xC8F4131414C835A1) void REGISTER_BOOL_TO_SAVE(any* p0, const char* name)l
extern _native64(0xEDB1232C5BEAE62F) void REGISTER_TEXT_LABEL_TO_SAVE(any* p0, const char* name)l
extern _native64(0x6F7794F28C6B2535) void REGISTER_TEXT_LABEL_15_TO_SAVE(any* p0, const char* name)l
extern _native64(0x48F069265A0E4BEC) void REGISTER_TEXT_LABEL_23_TO_SAVE(any* p0, const char* name)l
extern _native64(0x8269816F6CFD40F8) void REGISTER_TEXT_LABEL_31_TO_SAVE(any* p0, const char* name)l
extern _native64(0xFAA457EF263E8763) void REGISTER_TEXT_LABEL_63_TO_SAVE(any* p0, const char* name)l
extern _native64(0xBF737600CDDBEADD) void START_SAVE_STRUCT_WITH_SIZE(any* p0, int size, const char* structName)l
extern _native64(0xEB1774DF12BB9F12) void STOP_SAVE_STRUCT()l
extern _native64(0x60FE567DF1B1AF9D) void START_SAVE_ARRAY_WITH_SIZE(any* p0, int size, const char* arrayName)l
extern _native64(0x04456F95153C6BE4) void STOP_SAVE_ARRAY()l
extern _native64(0x213AEB2B90CBA7AC) void COPY_SCRIPT_STRUCT(any* dst, any* src, int size)l
extern _native64(0xDC0F817884CDD856) void ENABLE_DISPATCH_SERVICE(int dispatchService, bool toggle)l
extern _native64(0x9B2BD3773123EA2F) void BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION(int dispatchService, bool toggle)l
extern _native64(0xEB4A0C2D56441717) int GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL(int dispatchService)l
extern _native64(0x3F892CAF67444AE7) bool CREATE_INCIDENT(int dispatchService, float x, float y, float z, int numUnits, float radius, int* outIncidentID, any p7, any p8)l
extern _native64(0x05983472F0494E60) bool CREATE_INCIDENT_WITH_ENTITY(int dispatchService, Ped ped, int numUnits, float radius, int* outIncidentID, any p5, any p6)l
extern _native64(0x556C1AA270D5A207) void DELETE_INCIDENT(int incidentId)l
extern _native64(0xC8BC6461E629BEAA) bool IS_INCIDENT_VALID(int incidentId)l
extern _native64(0xB08B85D860E7BA3C) void SET_INCIDENT_REQUESTED_UNITS(int incidentId, int dispatchService, int numUnits)l
extern _native64(0xD261BA3E7E998072) void SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT(int incidentId, float p1)l
extern _native64(0x6874E2190B0C1972) bool FIND_SPAWN_POINT_IN_DIRECTION(float posX, float posY, float posZ, float fwdVecX, float fwdVecY, float fwdVecZ, float distance, vector3* spawnPoint)l
extern _native64(0x67F6413D3220E18D) int ADD_POP_MULTIPLIER_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float p6, float p7, bool p8, bool p9)l
extern _native64(0x1327E2FE9746BAEE) bool DOES_POP_MULTIPLIER_AREA_EXIST(int id)l
extern _native64(0xB129E447A2EDA4BF) void REMOVE_POP_MULTIPLIER_AREA(int id, bool p1)l
extern _native64(0x1312F4B242609CE3) bool IS_POP_MULTIPLIER_AREA_NETWORKED(int id)l
extern _native64(0x32C7A7E8C43A1F80) int ADD_POP_MULTIPLIER_SPHERE(float x, float y, float z, float radius, float pedMultiplier, float vehicleMultiplier, bool p6, bool p7)l
extern _native64(0x171BAFB3C60389F4) bool DOES_POP_MULTIPLIER_SPHERE_EXIST(int id)l
extern _native64(0xE6869BECDD8F2403) void REMOVE_POP_MULTIPLIER_SPHERE(int id, bool p1)l
extern _native64(0x28A04B411933F8A6) void ENABLE_TENNIS_MODE(Ped ped, bool toggle, bool p2)l
extern _native64(0x5D5479D115290C3F) bool IS_TENNIS_MODE(Ped ped)l
extern _native64(0xE266ED23311F24D4) void PLAY_TENNIS_SWING_ANIM(Ped ped, const char* animDict, const char* animName, float p3, float p4, bool p5)l
extern _native64(0x17DF68D720AA77F8) bool GET_TENNIS_SWING_ANIM_COMPLETE(Ped ped)l
extern _native64(0x19BFED045C647C49) bool GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED(Ped ped)l
extern _native64(0xE95B0C7D5BA3B96B) bool GET_TENNIS_SWING_ANIM_SWUNG(Ped ped)l
extern _native64(0x8FA9C42FC5D7C64B) void PLAY_TENNIS_DIVE_ANIM(Ped ped, int p1, float p2, float p3, float p4, bool p5)l
extern _native64(0x54F157E0336A3822) void SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* p1, float p2)l
extern _native64(0x5896F2BD5683A4E1) void RESET_DISPATCH_SPAWN_LOCATION()l
extern _native64(0xD10F442036302D50) void SET_DISPATCH_SPAWN_LOCATION(float x, float y, float z)l
extern _native64(0x77A84429DD9F0A15) void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE()l
extern _native64(0x6FE601A64180D423) void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(float distance)l
extern _native64(0xEB2DB0CAD13154B3) void RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(any p0)l
extern _native64(0x44F7CBC1BEB3327D) void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(any p0, float p1)l
extern _native64(0x48838ED9937A15D1) void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(any p0, float p1)l
extern _native64(0x918C7B2D2FF3928B) int ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width)l
extern _native64(0x2D4259F1FEB81DA9) int ADD_DISPATCH_SPAWN_SPHERE_BLOCKING_AREA(float x1, float y1, float x2, float y2)l
extern _native64(0x264AC28B01B353A5) void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(int p0)l
extern _native64(0xAC7BFD5C1D83EA75) void RESET_DISPATCH_SPAWN_BLOCKING_AREAS()l
extern _native64(0xD9F692D349249528) void RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN()l
extern _native64(0xE532EC1A63231B4F) void SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN(int p0, int p1)l
extern _native64(0xB8721407EE9C3FF6) void ADD_TACTICAL_NAV_MESH_POINT(float x, float y, float z)l
extern _native64(0xB3CD58CCA6CDA852) void CLEAR_TACTICAL_NAV_MESH_POINTS()l
extern _native64(0x2587A48BC88DFADF) void SET_RIOT_MODE_ENABLED(bool toggle)l
extern _native64(0xCA78CFA0366592FE) void DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING(int p0, const char* windowTitle, any* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, const char* defaultConcat4, const char* defaultConcat5, const char* defaultConcat6, const char* defaultConcat7, int maxInputLength)l
extern _native64(0x00DC833F2568DBF6) void DISPLAY_ONSCREEN_KEYBOARD(int p0, const char* windowTitle, const char* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, int maxInputLength)l
extern _native64(0x0CF2B696BBF945AE) int UPDATE_ONSCREEN_KEYBOARD()l
extern _native64(0x8362B09B91893647) const char* GET_ONSCREEN_KEYBOARD_RESULT()l
extern _native64(0x58A39BE597CE99CD) void CANCEL_ONSCREEN_KEYBOARD()l
extern _native64(0x3ED1438C1F5C6612) void NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS(int p0)l
extern _native64(0xA6A12939F16D85BE) void ACTION_MANAGER_ENABLE_ACTION(Hash hash, bool enable)l
extern _native64(0x3F60413F5DF65748) int GET_REAL_WORLD_TIME()l
extern _native64(0x1EAE0A6E978894A2) void SUPRESS_RANDOM_EVENT_THIS_FRAME(int eventType, bool suppress)l
extern _native64(0xA66C71C98D5F2CFB) void SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player)l
extern _native64(0x11879CDD803D30F4) void SET_FIRE_AMMO_THIS_FRAME(Player player)l
extern _native64(0xFF1BED81BFDC0FE0) void SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player)l
extern _native64(0x57FFF03E423A4C0B) void SET_SUPER_JUMP_THIS_FRAME(Player player)l
extern _native64(0x438822C279B73B93) void SET_BEAST_JUMP_THIS_FRAME(Player player)l
extern _native64(0xA1183BCFEE0F93D1) void SET_FORCED_JUMP_THIS_FRAME(Player player)l
extern _native64(0x6FDDF453C0C756EC) bool HAS_GAME_INSTALLED_THIS_SESSION()l
extern _native64(0xFB00CA71DA386228) void SET_TICKER_JOHNMARSTON_IS_DONE()l
extern _native64(0x5AA3BEFA29F03AD4) bool ARE_PROFILE_SETTINGS_VALID()l
extern _native64(0xE3D969D2785FFB5E) void PREVENT_ARREST_STATE_THIS_FRAME()l
extern _native64(0xC0AA53F866B3134D) void FORCE_GAME_STATE_PLAYING()l
extern _native64(0x0A60017F841A54F2) void SCRIPT_RACE_INIT(int p0, int p1, any p2, any p3)l
extern _native64(0x1FF6BF9A63E5757F) void SCRIPT_RACE_SHUTDOWN()l
extern _native64(0x1BB299305C3E8C13) void SCRIPT_RACE_PLAYER_HIT_CHECKPOINT(Player player, any p1, any p2, any p3)l
extern _native64(0x8EF5573A1F801A5C) bool SCRIPT_RACE_GET_PLAYER_SPLIT_TIME(Player player, int* p1, int* p2)l
extern _native64(0x92790862E36C2ADA) void START_END_USER_BENCHMARK()l
extern _native64(0xC7DB36C24634F52B) void STOP_END_USER_BENCHMARK()l
extern _native64(0x437138B6A830166A) void RESET_END_USER_BENCHMARK()l
extern _native64(0x37DEB0AA183FB6D8) void SAVE_END_USER_BENCHMARK()l
extern _native64(0xEA2F2061875EED90) bool UI_STARTED_END_USER_BENCHMARK()l
extern _native64(0x3BBBD13E5041A79E) bool LANDING_SCREEN_STARTED_END_USER_BENCHMARK()l
extern _native64(0xA049A5BE0F04F2F8) bool IS_COMMANDLINE_END_USER_BENCHMARK()l
extern _native64(0x4750FC27570311EC) int GET_BENCHMARK_ITERATIONS()l
extern _native64(0x1B2366C3F2A5C8DF) int GET_BENCHMARK_PASS()l
extern _native64(0xE574A662ACAEFBB1) void RESTART_GAME()l
extern _native64(0xEB6891F03362FB12) void QUIT_GAME()l
extern _native64(0x14832BF2ABA53FC5) bool HAS_ASYNC_INSTALL_FINISHED()l
extern _native64(0xC79AE21974B01FB2) void CLEANUP_ASYNC_INSTALL()l
extern _native64(0x684A41975F077262) bool PLM_IS_IN_CONSTRAINED_MODE()l
extern _native64(0xABB2FA71C83A1B72) int PLM_GET_CONSTRAINED_DURATION_MS()l
extern _native64(0x4EBB7E87AA0DBED4) void SET_PLAYER_IS_IN_ANIMAL_FORM(bool toggle)l
extern _native64(0x9689123E3F213AA5) bool GET_IS_PLAYER_IN_ANIMAL_FORM()l
extern _native64(0x9D8D44ADBBA61EF2) void SET_PLAYER_IS_REPEATING_A_MISSION(bool toggle)l
extern _native64(0x23227DF0B2115469) void DISABLE_SCREEN_DIMMING_THIS_FRAME()l
extern _native64(0xD10282B6E3751BA0) float GET_CITY_DENSITY()l
extern _native64(0x693478ACBD7F18E7) void USE_ACTIVE_CAMERA_FOR_TIMESLICING_CENTRE()l
extern _native64(0x4B82FA6F2D624634) void SET_CONTENT_ID_INDEX(Hash contentId, int index)l
extern _native64(0xECF041186C5A94DC) int GET_CONTENT_ID_INDEX(Hash contentId)l
#pragma endregion //}
#pragma region MOBILE //{
extern _native64(0xA4E8E696C532FBC7) void CREATE_MOBILE_PHONE(int phoneType)l
extern _native64(0x3BC861DF703E5097) void DESTROY_MOBILE_PHONE()l
extern _native64(0xCBDD322A73D6D932) void SET_MOBILE_PHONE_SCALE(float scale)l
extern _native64(0xBB779C0CA917E865) void SET_MOBILE_PHONE_ROTATION(float rotX, float rotY, float rotZ, any p3)l
extern _native64(0x1CEFB61F193070AE) void GET_MOBILE_PHONE_ROTATION(vector3* rotation, Vehicle p1)l
extern _native64(0x693A5C6D6734085B) void SET_MOBILE_PHONE_POSITION(float posX, float posY, float posZ)l
extern _native64(0x584FDFDA48805B86) void GET_MOBILE_PHONE_POSITION(vector3* position)l
extern _native64(0xF511F759238A5122) void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(bool toggle)l
extern _native64(0xC4E2813898C97A4B) bool CAN_PHONE_BE_SEEN_ON_SCREEN()l
extern _native64(0x375A706A5C2FD084) void SET_MOBILE_PHONE_DOF_STATE(bool toggle)l
extern _native64(0x95C9E72F3D7DEC9B) void CELL_SET_INPUT(int direction)l
extern _native64(0x44E44169EF70138E) void CELL_HORIZONTAL_MODE_TOGGLE(bool toggle)l
extern _native64(0xFDE8F069C542D126) void CELL_CAM_ACTIVATE(bool p0, bool p1)l
extern _native64(0x015C49A93E3E086E) void CELL_CAM_ACTIVATE_SELFIE_MODE(bool toggle)l
extern _native64(0xA2CCBE62CD4C91A4) void CELL_CAM_ACTIVATE_SHALLOW_DOF_MODE(bool toggle)l
extern _native64(0x1B0B4AEED5B9B41C) void CELL_CAM_SET_SELFIE_MODE_SIDE_OFFSET_SCALING(float p0)l
extern _native64(0x53F4892D18EC90A4) void CELL_CAM_SET_SELFIE_MODE_HORZ_PAN_OFFSET(float horizontalPan)l
extern _native64(0x3117D84EFA60F77B) void CELL_CAM_SET_SELFIE_MODE_VERT_PAN_OFFSET(float vertPan)l
extern _native64(0x15E69E2802C24B8D) void CELL_CAM_SET_SELFIE_MODE_ROLL_OFFSET(float roll)l
extern _native64(0xAC2890471901861C) void CELL_CAM_SET_SELFIE_MODE_DISTANCE_SCALING(float distanceScaling)l
extern _native64(0xD6ADE981781FCA09) void CELL_CAM_SET_SELFIE_MODE_HEAD_YAW_OFFSET(float yaw)l
extern _native64(0xF1E22DC13F5EEBAD) void CELL_CAM_SET_SELFIE_MODE_HEAD_ROLL_OFFSET(float roll)l
extern _native64(0x466DA42C89865553) void CELL_CAM_SET_SELFIE_MODE_HEAD_PITCH_OFFSET(float pitch)l
extern _native64(0x439E9BC95B7E7FBE) bool CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Entity entity)l
extern _native64(0xB4A53E05F68B6FA1) void GET_MOBILE_PHONE_RENDER_ID(int* renderId)l
#pragma endregion //}
#pragma region MONEY //{
extern _native64(0x3DA5ECD1A56CBA6D) void NETWORK_INITIALIZE_CASH(int wallet, int bank)l
extern _native64(0x05A50AF38947EB8D) void NETWORK_DELETE_CHARACTER(int characterSlot, bool p1, bool p2)l
extern _native64(0x821418C727FCACD7) void NETWORK_MANUAL_DELETE_CHARACTER(int characterSlot)l
extern _native64(0xFB2456B2040A6A67) bool NETWORK_GET_PLAYER_IS_HIGH_EARNER()l
extern _native64(0xA921DED15FDF28F5) void NETWORK_CLEAR_CHARACTER_WALLET(int characterSlot)l
extern _native64(0xFB18DF9CB95E0105) void NETWORK_GIVE_PLAYER_JOBSHARE_CASH(int amount, any* gamerHandle)l
extern _native64(0x56A3B51944C50598) void NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(int value, any* gamerHandle)l
extern _native64(0x1C2473301B1C66BA) bool NETWORK_CAN_SHARE_JOB_CASH()l
extern _native64(0xF9C812CD7C46E817) void NETWORK_REFUND_CASH(int index, const char* context, const char* reason, bool p3)l
extern _native64(0x18B7AE224B087E26) void NETWORK_DEDUCT_CASH(int amount, const char* p1, const char* p2, bool p3, bool p4, bool p5)l
extern _native64(0x81404F3DC124FE5B) bool NETWORK_MONEY_CAN_BET(int amount, bool p1, bool p2)l
extern _native64(0x3A54E33660DED67F) bool NETWORK_CAN_BET(int amount)l
extern _native64(0x158C16F5E4CF41F8) bool NETWORK_CASINO_CAN_BET(Hash hash)l
extern _native64(0x394DCDB9E836B7A9) bool NETWORK_CASINO_CAN_BET_PVC()l
extern _native64(0xF62F6D9528358FE4) bool NETWORK_CASINO_CAN_BET_AMOUNT(any p0)l
extern _native64(0x8968D4D8C6C40C11) bool NETWORK_CASINO_CAN_BUY_CHIPS_PVC()l
extern _native64(0x3BD101471C7F9EEC) bool NETWORK_CASINO_BUY_CHIPS(int p0, int p1)l
extern _native64(0xED44897CB336F480) bool NETWORK_CASINO_SELL_CHIPS(int p0, int p1)l
extern _native64(0xCD0F5B5D932AE473) void NETWORK_DEFER_CASH_TRANSACTIONS_UNTIL_SHOP_SAVE()l
extern _native64(0x9777734DAD16992F) bool CAN_PAY_AMOUNT_TO_BOSS(int p0, int p1, int amount, int* p3)l
extern _native64(0xED1517D3AF17C698) void NETWORK_EARN_FROM_PICKUP(int amount)l
extern _native64(0x718FBBF67414FA36) void NETWORK_EARN_FROM_CASHING_OUT(int amount)l
extern _native64(0xA03D4ACE0A3284CE) void NETWORK_EARN_FROM_GANGATTACK_PICKUP(int amount)l
extern _native64(0xFA700D8A9905F78A) void NETWORK_EARN_ASSASSINATE_TARGET_KILLED(int amount)l
extern _native64(0xF514621E8EA463D0) void NETWORK_EARN_FROM_ROB_ARMORED_CARS(int amount)l
extern _native64(0xB1CC1B9EC3007A2A) void NETWORK_EARN_FROM_CRATE_DROP(int amount)l
extern _native64(0x827A5BA1A44ACA6D) void NETWORK_EARN_FROM_BETTING(int amount, const char* p1)l
extern _native64(0xB2CC4836834E8A98) void NETWORK_EARN_FROM_JOB(int amount, const char* p1)l
extern _native64(0xDEBBF584665411D0) void NETWORK_EARN_FROM_JOBX2(int amount, const char* p1)l
extern _native64(0xC8407624CEF2354B) void NETWORK_EARN_FROM_PREMIUM_JOB(int amount, const char* p1)l
extern _native64(0x61326EE6DF15B0CA) void NETWORK_EARN_FROM_BEND_JOB(int amount, const char* heistHash)l
extern _native64(0x2B171E6B2F64D8DF) void NETWORK_EARN_FROM_CHALLENGE_WIN(any p0, any* p1, bool p2)l
extern _native64(0x131BB5DA15453ACF) void NETWORK_EARN_FROM_BOUNTY(int amount, any* gamerHandle, any* p2, any p3)l
extern _native64(0xF92A014A634442D6) void NETWORK_EARN_FROM_IMPORT_EXPORT(int amount, Hash modelHash)l
extern _native64(0x45B8154E077D9E4D) void NETWORK_EARN_FROM_HOLDUPS(int amount)l
extern _native64(0x849648349D77F5C5) void NETWORK_EARN_FROM_PROPERTY(int amount, Hash propertyName)l
extern _native64(0x515B4A22E4D3C6D7) void NETWORK_EARN_FROM_AI_TARGET_KILL(any p0, any p1)l
extern _native64(0x4337511FA8221D36) void NETWORK_EARN_FROM_NOT_BADSPORT(int amount)l
extern _native64(0xB539BD8A4C1EECF8) void NETWORK_EARN_FROM_VEHICLE(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native64(0x3F4D00167E41E0AD) void NETWORK_EARN_FROM_PERSONAL_VEHICLE(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native64(0x6EA318C91C1A8786) void NETWORK_EARN_FROM_DAILY_OBJECTIVES(int amount, const char* type, int characterSlot)l
extern _native64(0xFB6DB092FBAE29E6) void NETWORK_EARN_FROM_AMBIENT_JOB(int p0, const char* p1, any* p2)l
extern _native64(0x6816FB4416760775) void NETWORK_EARN_FROM_JOB_BONUS(any p0, any* p1, any* p2)l
extern _native64(0xFA009A62990671D4) void NETWORK_EARN_FROM_CRIMINAL_MASTERMIND(any p0, any p1, any p2)l
extern _native64(0x9D4FDBB035229669) void NETWORK_EARN_HEIST_AWARD(any p0, any p1, any p2)l
extern _native64(0x11B0A20C493F7E36) void NETWORK_EARN_FIRST_TIME_BONUS(any p0, any p1, any p2)l
extern _native64(0xCDA1C62BE2777802) void NETWORK_EARN_GOON(any p0, any p1, any p2)l
extern _native64(0x08B0CA7A6AB3AC32) void NETWORK_EARN_BOSS(any p0, any p1, any p2)l
extern _native64(0x0CB1BE0633C024A8) void NETWORK_EARN_AGENCY(any p0, any p1, any p2, any p3)l
extern _native64(0x3E4ADAFF1830F146) void NETWORK_EARN_FROM_WAREHOUSE(int amount, int id)l
extern _native64(0xECA658CE2A4E5A72) void NETWORK_EARN_FROM_CONTRABAND(int amount, any p1)l
extern _native64(0x84C0116D012E8FC2) void NETWORK_EARN_FROM_DESTROYING_CONTRABAND(any p0, any p1, any p2)l
extern _native64(0x6B7E4FB50D5F3D65) void NETWORK_EARN_FROM_SMUGGLER_WORK(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x31BA138F6304FB9F) void NETWORK_EARN_FROM_HANGAR_TRADE(any p0, any p1)l
extern _native64(0x55A1E095DB052FA5) void NETWORK_EARN_PURCHASE_CLUB_HOUSE(any p0, any p1)l
extern _native64(0x8586789730B10CAF) void NETWORK_EARN_FROM_BUSINESS_PRODUCT(int amount, any p1, any p2, any p3)l
extern _native64(0xEDEAD9A91EC768B3) void NETWORK_EARN_FROM_VEHICLE_EXPORT(int amount, any p1, any p2)l
extern _native64(0xDEE612F2D71B0308) void NETWORK_EARN_SMUGGLER_AGENCY(int amount, any p1, any p2, any p3)l
extern _native64(0xF6B170F9A02E9E87) void NETWORK_EARN_BOUNTY_HUNTER_REWARD(any p0)l
extern _native64(0x42FCE14F50F27291) void NETWORK_EARN_FROM_BUSINESS_BATTLE(any p0)l
extern _native64(0xA75EAC69F59E96E7) void NETWORK_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION(any p0, int p1)l
extern _native64(0xC5156361F26E2212) void NETWORK_EARN_FROM_FMBB_PHONECALL_MISSION(any p0)l
extern _native64(0x0B39CF0D53F1C883) void NETWORK_EARN_FROM_BUSINESS_HUB_SELL(any p0, any p1, any p2)l
extern _native64(0x1FDA0AA679C9919B) void NETWORK_EARN_FROM_FMBB_BOSS_WORK(any p0)l
extern _native64(0xFFFBA1B1F7C0B6F4) void NETWORK_EARN_FMBB_WAGE_BONUS(any p0)l
extern _native64(0xAB3CAA6B422164DA) bool NETWORK_CAN_SPEND_MONEY(any p0, bool p1, bool p2, bool p3, any p4, any p5)l
extern _native64(0x7303E27CC6532080) bool NETWORK_CAN_SPEND_MONEY2(any p0, bool p1, bool p2, bool p3, any* p4, any p5, any p6)l
extern _native64(0xF0077C797F66A355) void NETWORK_BUY_ITEM(int amount, Hash item, any p2, any p3, bool p4, const char* item_name, any p6, any p7, any p8, bool p9)l
extern _native64(0x17C3A7D31EAE39F9) void NETWORK_SPENT_TAXI(int amount, bool p1, bool p2, any p3, any p4)l
extern _native64(0x5FD5ED82CBBE9989) void NETWORK_PAY_EMPLOYEE_WAGE(any p0, bool p1, bool p2)l
extern _native64(0x9346E14F2AF74D46) void NETWORK_PAY_MATCH_ENTRY_FEE(int amount, const char* matchId, bool p2, bool p3)l
extern _native64(0x1C436FD11FFA692F) void NETWORK_SPENT_BETTING(int amount, int p1, const char* matchId, bool p3, bool p4)l
extern _native64(0xD99DB210089617FE) void NETWORK_SPENT_WAGER(any p0, any p1, int amount)l
extern _native64(0xEE99784E4467689C) void NETWORK_SPENT_IN_STRIPCLUB(any p0, bool p1, any p2, bool p3)l
extern _native64(0xD9B067E55253E3DD) void NETWORK_BUY_HEALTHCARE(int cost, bool p1, bool p2)l
extern _native64(0x763B4BD305338F19) void NETWORK_BUY_AIRSTRIKE(int cost, bool p1, bool p2, any p3)l
extern _native64(0xA3EDDAA42411D3B9) void NETWORK_BUY_BACKUP_GANG(int p0, int p1, bool p2, bool p3, int npcProvider)l
extern _native64(0x81AA4610E3FD3A69) void NETWORK_BUY_HELI_STRIKE(int cost, bool p1, bool p2, any p3)l
extern _native64(0xB162DC95C0A3317B) void NETWORK_SPENT_AMMO_DROP(any p0, bool p1, bool p2, any p3)l
extern _native64(0x7B718E197453F2D9) void NETWORK_BUY_BOUNTY(int amount, Player victim, bool p2, bool p3, any p4)l
extern _native64(0x650A08A280870AF6) void NETWORK_BUY_PROPERTY(int cost, Hash propertyName, bool p2, bool p3)l
extern _native64(0x75AF80E61248EEBD) void NETWORK_BUY_SMOKES(int p0, bool p1, bool p2)l
extern _native64(0x7BF1D73DB2ECA492) void NETWORK_SPENT_HELI_PICKUP(any p0, bool p1, bool p2, any p3)l
extern _native64(0x524EE43A37232C00) void NETWORK_SPENT_BOAT_PICKUP(any p0, bool p1, bool p2, any p3)l
extern _native64(0xA6DD8458CE24012C) void NETWORK_SPENT_BULL_SHARK(any p0, bool p1, bool p2, any p3)l
extern _native64(0x289016EC778D60E0) void NETWORK_SPENT_CASH_DROP(int amount, bool p1, bool p2)l
extern _native64(0xE404BFB981665BF0) void NETWORK_SPENT_HIRE_MUGGER(any p0, bool p1, bool p2, any p3)l
extern _native64(0x995A65F15F581359) void NETWORK_SPENT_ROBBED_BY_MUGGER(int amount, bool p1, bool p2, any p3)l
extern _native64(0xE7B80E2BF9D80BD6) void NETWORK_SPENT_HIRE_MERCENARY(any p0, bool p1, bool p2, any p3)l
extern _native64(0xE1B13771A843C4F6) void NETWORK_SPENT_BUY_WANTEDLEVEL(any p0, any* p1, bool p2, bool p3, any p4)l
extern _native64(0xA628A745E2275C5D) void NETWORK_SPENT_BUY_OFFTHERADAR(any p0, bool p1, bool p2, any p3)l
extern _native64(0x6E176F1B18BC0637) void NETWORK_SPENT_BUY_REVEAL_PLAYERS(any p0, bool p1, bool p2, any p3)l
extern _native64(0xEC03C719DB2F4306) void NETWORK_SPENT_CARWASH(any p0, any p1, any p2, bool p3, bool p4)l
extern _native64(0x6B38ECB05A63A685) void NETWORK_SPENT_CINEMA(any p0, any p1, bool p2, bool p3)l
extern _native64(0x7FE61782AD94CC09) void NETWORK_SPENT_TELESCOPE(any p0, bool p1, bool p2)l
extern _native64(0xD9B86B9872039763) void NETWORK_SPENT_HOLDUPS(any p0, bool p1, bool p2)l
extern _native64(0x6D3A430D1A809179) void NETWORK_SPENT_BUY_PASSIVE_MODE(any p0, bool p1, bool p2, any p3)l
extern _native64(0xCA230C9682556CF1) void NETWORK_SPENT_BANK_INTEREST(int p0, bool p1, bool p2)l
extern _native64(0xB21B89501CFAC79E) void NETWORK_SPENT_PROSTITUTES(any p0, bool p1, bool p2)l
extern _native64(0x812F5488B1B2A299) void NETWORK_SPENT_ARREST_BAIL(any p0, bool p1, bool p2)l
extern _native64(0x9FF28D88C766E3E8) void NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(int amount, Hash vehicleModel, any* gamerHandle, bool notBankrupt, bool hasTheMoney)l
extern _native64(0xACDE7185B374177C) void NETWORK_SPENT_CALL_PLAYER(any p0, any* p1, bool p2, bool p3)l
extern _native64(0x29B260B84947DFCC) void NETWORK_SPENT_BOUNTY(any p0, bool p1, bool p2)l
extern _native64(0x6A445B64ED7ABEB5) void NETWORK_SPENT_FROM_ROCKSTAR(int p0, bool p1, bool p2)l
extern _native64(0x9B5016A6433A68C5) int NETWORK_SPEND_EARNED_FROM_BANK_AND_WALLETS(int amount)l
extern _native64(0x20194D48EAEC9A41) const char* PROCESS_CASH_GIFT(int* p0, int* p1, const char* p2)l
extern _native64(0xCD4D66B43B1DD28D) void NETWORK_SPENT_MOVE_SUBMARINE(any p0, any p1, any p2)l
extern _native64(0x7C99101F7FCE2EE5) void NETWORK_SPENT_PLAYER_HEALTHCARE(int p0, int p1, bool p2, bool p3)l
extern _native64(0xD5BB406F4E04019F) void NETWORK_SPENT_NO_COPS(any p0, bool p1, bool p2, any p3)l
extern _native64(0x948705F6F9C50824) void NETWORK_SPENT_CARGO_SOURCING(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x8204DA7934DF3155) void NETWORK_SPENT_REQUEST_JOB(any p0, bool p1, bool p2, any p3)l
extern _native64(0x9D26502BB97BFE62) void NETWORK_SPENT_REQUEST_HEIST(any p0, bool p1, bool p2, any p3)l
extern _native64(0x8A7B3952DD64D2B5) void NETWORK_BUY_FAIRGROUND_RIDE(int amount, any p1, bool p2, bool p3, any p4)l
extern _native64(0x7C4FCCD2E4DEB394) bool NETWORK_ECONOMY_HAS_FIXED_CRAZY_NUMBERS()l
extern _native64(0x28F174A67B8D0C2F) void NETWORK_SPENT_JOB_SKIP(int amount, const char* matchId, bool p2, bool p3)l
extern _native64(0xFFBE02CD385356BD) bool NETWORK_SPENT_BOSS_GOON(int amount, bool p1, bool p2)l
extern _native64(0x08A1B82B91900682) void NETWORK_SPEND_GOON(int p0, int p1, int amount)l
extern _native64(0xDBC966A01C02BCA7) void NETWORK_SPEND_BOSS(any p0, any p1, any p2)l
extern _native64(0xE7DF4E0545DFB56E) void NETWORK_SPENT_MOVE_YACHT(int amount, bool p1, bool p2)l
extern _native64(0xFC4EE00A7B3BFB76) void NETWORK_SPENT_RENAME_ORGANIZATION(any p0, any p1, any p2, any p3)l
extern _native64(0x30FD873ECE50E9F6) void NETWORK_BUY_CONTRABAND_MISSION(int p0, int p1, Hash p2, bool p3, bool p4)l
extern _native64(0x112209CE0290C03A) void NETWORK_SPENT_PA_SERVICE_HELI(any p0, any p1, any p2, any p3)l
extern _native64(0xED5FD7AF10F5E262) void NETWORK_SPENT_PA_SERVICE_VEHICLE(any p0, any p1, any p2, any p3)l
extern _native64(0x0D30EB83668E63C5) void NETWORK_SPENT_PA_SERVICE_SNACK(any p0, any p1, any p2, any p3)l
extern _native64(0xB49ECA122467D05F) void NETWORK_SPENT_PA_SERVICE_DANCER(any p0, any p1, any p2, any p3)l
extern _native64(0xE23ADC6FCB1F29AE) void NETWORK_SPENT_PA_SERVICE_IMPOUND(any p0, any p1, any p2)l
extern _native64(0x0FE8E1FCD2B86B33) void NETWORK_SPENT_PA_HELI_PICKUP(any p0, any p1, any p2, any p3)l
extern _native64(0x69EF772B192614C1) void NETWORK_SPENT_PURCHASE_OFFICE_PROPERTY(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x8E243837643D9583) void NETWORK_SPENT_UPGRADE_OFFICE_PROPERTY(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xBD0EFB25CCA8F97A) void NETWORK_SPENT_PURCHASE_WAREHOUSE_PROPERTY(any p0, any p1, any p2, any p3)l
extern _native64(0xA95F667A755725DA) void NETWORK_SPENT_UPGRADE_WAREHOUSE_PROPERTY(any p0, any p1, any p2, any p3)l
extern _native64(0x33981D6804E62F49) void NETWORK_SPENT_PURCHASE_IMPEXP_WAREHOUSE_PROPERTY(int amount, any* data, bool p2, bool p3)l
extern _native64(0x4128464231E3CA0B) void NETWORK_SPENT_UPGRADE_IMPEXP_WAREHOUSE_PROPERTY(any p0, any p1, any p2, any p3)l
extern _native64(0x2FAB6614CE22E196) void NETWORK_SPENT_TRADE_IMPEXP_WAREHOUSE_PROPERTY(any p0, any p1, any p2, any p3)l
extern _native64(0x05F04155A226FBBF) void NETWORK_SPENT_ORDER_WAREHOUSE_VEHICLE(any p0, any p1, any p2, any p3)l
extern _native64(0xE8B0B270B6E7C76E) void NETWORK_SPENT_ORDER_BODYGUARD_VEHICLE(any p0, any p1, any p2, any p3)l
extern _native64(0x5BCDE0F640C773D2) void NETWORK_SPENT_JUKEBOX(any p0, any p1, any p2, any p3)l
extern _native64(0x998E18CEB44487FC) void NETWORK_SPENT_PURCHASE_CLUB_HOUSE(any p0, any p1, any p2, any p3)l
extern _native64(0xFA07759E6FDDD7CF) void NETWORK_SPENT_UPGRADE_CLUB_HOUSE(any p0, any p1, any p2, any p3)l
extern _native64(0x6FD97159FE3C971A) void NETWORK_SPENT_PURCHASE_BUSINESS_PROPERTY(any p0, any p1, any p2, any p3)l
extern _native64(0x675D19C6067CAE08) void NETWORK_SPENT_UPGRADE_BUSINESS_PROPERTY(any p0, any p1, any p2, any p3)l
extern _native64(0xA51B086B0B2C0F7A) void NETWORK_SPENT_TRADE_BUSINESS_PROPERTY(any p0, any p1, any p2, any p3)l
extern _native64(0xD7CCCBA28C4ECAF0) void NETWORK_SPENT_MC_ABILITY(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x0035BB914316F1E3) void NETWORK_SPENT_PAY_BUSINESS_SUPPLIES(any p0, any p1, any p2, any p3)l
extern _native64(0x5F456788B05FAEAC) void NETWORK_SPENT_CHANGE_APPEARANCE(any p0, any p1, any p2)l
extern _native64(0xA75CCF58A60A5FD1) void NETWORK_SPENT_VEHICLE_EXPORT_MODS(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9)l
extern _native64(0xB4C2EC463672474E) void NETWORK_SPENT_PURCHASE_OFFICE_GARAGE(any p0, any p1, any p2, any p3)l
extern _native64(0x2AFC2D19B50797F2) void NETWORK_SPENT_UPGRADE_OFFICE_GARAGE(any p0, any p1, any p2, any p3)l
extern _native64(0xC1952F3773BA18FE) void NETWORK_SPENT_IMPORT_EXPORT_REPAIR(any p0, any p1, any p2)l
extern _native64(0xCCB339CC970452DA) void NETWORK_SPENT_PURCHASE_HANGAR(any p0, any p1, any p2, any p3)l
extern _native64(0x615EB504B0788DAF) void NETWORK_SPENT_UPGRADE_HANGAR(any p0, any p1, any p2, any p3)l
extern _native64(0xB18AC2ECBB15CB6A) void NETWORK_SPENT_HANGAR_UTILITY_CHARGES(int amount, bool p1, bool p2)l
extern _native64(0xB1F1346FD57685D7) void NETWORK_SPENT_HANGAR_STAFF_CHARGES(int amount, bool p1, bool p2)l
extern _native64(0xAC272C0AE01B4BD8) void NETWORK_SPENT_BUY_TRUCK(any p0, any p1, any p2, any p3)l
extern _native64(0x365E877C61D6988B) void NETWORK_SPENT_UPGRADE_TRUCK(any p0, any p1, any p2, any p3)l
extern _native64(0x12D148D26538D0F9) void NETWORK_SPENT_BUY_BUNKER(any p0, any p1, any p2, any p3)l
extern _native64(0x0C82D21A77C22D49) void NETWORK_SPENT_UPRADE_BUNKER(any p0, any p1, any p2, any p3)l
extern _native64(0x9251B6ABF2D0A5B4) void NETWORK_EARN_FROM_SELL_BUNKER(int amount, Hash bunkerHash)l
extern _native64(0x5D97630A8A0EF123) void NETWORK_SPENT_BALLISTIC_EQUIPMENT(int amount, bool p1, bool p2)l
extern _native64(0x7A5349B773584675) void NETWORK_EARN_RDR_BONUS(int amount, any p1)l
extern _native64(0x35F8DA0E8A31EF1B) void NETWORK_EARN_WAGE_PAYMENT(int amount, any p1)l
extern _native64(0x005ACA7100BD101D) void NETWORK_EARN_WAGE_PAYMENT_BONUS(int amount)l
extern _native64(0x4EA3F425C7744D21) void NETWORK_SPENT_BUY_BASE(any p0, any p1, any p2, any p3)l
extern _native64(0x3DD3F33A5D55EA6F) void NETWORK_SPENT_UPGRADE_BASE(any p0, any p1, any p2, any p3)l
extern _native64(0x0CCE73BC7A11E885) void NETWORK_SPENT_BUY_TILTROTOR(any p0, any p1, any p2, any p3)l
extern _native64(0x165E135D6DFA2907) void NETWORK_SPENT_UPGRADE_TILTROTOR(any p0, any p1, any p2, any p3)l
extern _native64(0x5BBBD92186E1F1C5) void NETWORK_SPENT_EMPLOY_ASSASSINS(any p0, any p1, any p2, any p3)l
extern _native64(0x771ADB0E7635B7BF) void NETWORK_SPEND_GANGOPS_CANNON(any p0, any p1, any p2, any p3)l
extern _native64(0xDA947AE8880D5C18) void NETWORK_SPEND_GANGOPS_SKIP_MISSION(any p0, any p1, any p2, any p3)l
extern _native64(0x487009DD91D93429) void NETWORK_SPEND_CASINO_HEIST_SKIP_MISSION(any p0, any p1, any p2, any p3)l
extern _native64(0x0E1E2FF3F4EC11AA) void NETWORK_EARN_SELL_BASE(int amount, Hash baseNameHash)l
extern _native64(0x5B669CF2299A271F) void NETWORK_EARN_TARGET_REFUND(int amount, int p1)l
extern _native64(0x2DCB19ABAB0380A8) void NETWORK_EARN_GANGOPS_WAGES(int amount, int p1)l
extern _native64(0x15BB2A5C757EB91F) void NETWORK_EARN_GANGOPS_WAGES_BONUS(int amount, int p1)l
extern _native64(0xCAC672087B4A24AB) void NETWORK_EARN_DAR_CHALLENGE(int amount, any p1)l
extern _native64(0x128A747F4A230952) void NETWORK_EARN_DOOMSDAY_FINALE_BONUS(int amount, Hash vehicleHash)l
extern _native64(0xA9A31475F530DFDA) void NETWORK_EARN_GANGOPS_AWARD(int amount, const char* p1, any p2)l
extern _native64(0x2597A0D4A4FC2C77) void NETWORK_EARN_GANGOPS_ELITE(int amount, const char* p1, int actIndex)l
extern _native64(0x1B882107C23A9022) void NETWORK_SERVICE_EARN_GANGOPS_RIVAL_DELIVERY(int earnedMoney)l
extern _native64(0xA19EC0786E326E06) void NETWORK_SPEND_GANGOPS_START_STRAND(int type, int amount, bool p2, bool p3)l
extern _native64(0x5ECE6FD7B4EC8D6A) void NETWORK_SPEND_GANGOPS_TRIP_SKIP(int amount, bool p1, bool p2)l
extern _native64(0xED26584F6BDCBBFD) void NETWORK_EARN_GANGOPS_PREP_PARTICIPATION(int amount)l
extern _native64(0xA9160796D47A2CF8) void NETWORK_EARN_GANGOPS_SETUP(int amount, const char* p1)l
extern _native64(0x1C121FC9545E0D52) void NETWORK_EARN_GANGOPS_FINALE(int amount, const char* p1)l
extern _native64(0x2A7CEC72C3443BCC) void NETWORK_SPEND_GANGOPS_REPAIR_COST(any p0, any p1, any p2)l
extern _native64(0xE0F82D68C7039158) void NETWORK_EARN_NIGHTCLUB(any p0)l
extern _native64(0xB4DEAE67F35E2ACD) void NETWORK_EARN_NIGHTCLUB_DANCING(any p0)l
extern _native64(0xFDD8D2440DAF1590) void NETWORK_EARN_BB_EVENT_BONUS(int amount)l
extern _native64(0x2A93C46AAB1EACC9) void NETWORK_SPENT_PURCHASE_HACKER_TRUCK(any p0, any p1, any p2, any p3)l
extern _native64(0x226C284C830D0CA8) void NETWORK_SPENT_UPGRADE_HACKER_TRUCK(any p0, any p1, any p2, any p3)l
extern _native64(0xE8815FE993896AD3) void NETWORK_EARN_HACKER_TRUCK(any p0, int amount, any p2, any p3)l
extern _native64(0xED76D195E6E3BF7F) void NETWORK_SPENT_PURCHASE_NIGHTCLUB_AND_WAREHOUSE(any p0, any p1, any p2, any p3)l
extern _native64(0x1DC9B749E7AE282B) void NETWORK_SPENT_UPGRADE_NIGHTCLUB_AND_WAREHOUSE(any p0, any p1, any p2, any p3)l
extern _native64(0xC6E74CF8C884C880) void NETWORK_EARN_NIGHTCLUB_AND_WAREHOUSE(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x65482BFD0923C8A1) void NETWORK_SPEND_NIGHTCLUB_AND_WAREHOUSE(any p0, any p1, any p2, any p3)l
extern _native64(0xE284D46FFDB82E36) void NETWORK_SPENT_RDR_HATCHET_BONUS(int amount, bool p1, bool p2)l
extern _native64(0x876056684281655D) void NETWORK_SPENT_NIGHTCLUB_ENTRY_FEE(Player player, int amount, any p1, bool p2, bool p3)l
extern _native64(0xDD21B016E4289465) void NETWORK_SPEND_NIGHTCLUB_BAR_DRINK(int amount, any p1, bool p2, bool p3)l
extern _native64(0x1BEA0CD93470BB1F) void NETWORK_SPEND_BOUNTY_HUNTER_MISSION(int amount, bool p1, bool p2)l
extern _native64(0xF6C8A544E4CF14FC) void NETWORK_SPENT_REHIRE_DJ(int amount, any p1, bool p2, bool p3)l
extern _native64(0x14EAEA58F93B55AF) void NETWORK_SPENT_ARENA_JOIN_SPECTATOR(int amount, any p1, bool p2, bool p3)l
extern _native64(0xE08256F972C7BB2C) void NETWORK_EARN_ARENA_SKILL_LEVEL_PROGRESSION(int amount, any p1)l
extern _native64(0x0F99F70C61F14619) void NETWORK_EARN_ARENA_CAREER_PROGRESSION(int amount, any p1)l
extern _native64(0xE5F5A060439C2F5D) void NETWORK_SPEND_MAKE_IT_RAIN(int amount, bool p1, bool p2)l
extern _native64(0x40D5DA9550B7CB46) void NETWORK_SPEND_BUY_ARENA(int amount, bool p1, bool p2, const char* p3)l
extern _native64(0x037ABB06825D7AB1) void NETWORK_SPEND_UPGRADE_ARENA(int amount, bool p1, bool p2, const char* p3)l
extern _native64(0x7049BF858601DC0F) void NETWORK_SPEND_ARENA_SPECTATOR_BOX(int amount, int type, bool p2, bool p3)l
extern _native64(0x9A5BD1D0000B339C) void NETWORK_SPEND_SPIN_THE_WHEEL_PAYMENT(int amount, any p1, bool p2)l
extern _native64(0x676C48776CACBB5A) void NETWORK_EARN_SPIN_THE_WHEEL_CASH(int amount)l
extern _native64(0x619496D837EFD920) void NETWORK_SPEND_ARENA_PREMIUM(int amount, bool p1, bool p2)l
extern _native64(0x631F1CB8FB4130AA) void NETWORK_EARN_ARENA_WAR(int amount, any p1, any p2, any p3)l
extern _native64(0x5E7AE8AABE8B7C0D) void NETWORK_EARN_ARENA_WAR_ASSASSINATE_TARGET(int amount)l
extern _native64(0xA82959062361B259) void NETWORK_EARN_ARENA_WAR_EVENT_CARGO(int amount)l
extern _native64(0xDFF49EE984E7AAE8) void NETWORK_EARN_RC_TIME_TRIAL(int amount)l
extern _native64(0x5128DF14A5BB86FC) void NETWORK_EARN_DAILY_OBJECTIVE_EVENT(int amount)l
extern _native64(0xFBBE0570EDF39D46) void NETWORK_SPEND_CASINO_MEMBERSHIP(int amount, bool p1, bool p2, int p3)l
extern _native64(0x34A6FC4D06C4DA0F) void NETWORK_SPEND_BUY_CASINO(int amount, bool p1, bool p2, any* data)l
extern _native64(0x4740D62BC1B4EBEA) void NETWORK_SPEND_UPGRADE_CASINO(int amount, bool p1, bool p2, any* data)l
extern _native64(0x88BF9B612B84D3C3) void NETWORK_SPEND_CASINO_GENERIC(int amount, any p1, any p2, any p3, any p4)l
extern _native64(0x0819DB99FD2FBBD8) void NETWORK_EARN_CASINO_TIME_TRIAL_WIN(int amount)l
extern _native64(0x5517F90043466049) void NETWORK_EARN_COLLECTABLES_ACTION_FIGURES(int amount)l
extern _native64(0x83AD64F53F4E9483) void NETWORK_EARN_CASINO_COLLECTABLE_COMPLETED_COLLECTION(int amount)l
extern _native64(0x8BCB27A057DF7B7F) void NETWORK_EARN_SELL_PRIZE_VEHICLE(int amount, any p1, any p2)l
extern _native64(0x566FD402B25787DE) void NETWORK_EARN_CASINO_MISSION_REWARD(int amount)l
extern _native64(0xAC95ED552157E092) void NETWORK_EARN_CASINO_STORY_MISSION_REWARD(int amount)l
extern _native64(0x09E8F18641BE2575) void NETWORK_EARN_CASINO_MISSION_PARTICIPATION(int amount)l
extern _native64(0x973A9781A34F8DEB) void NETWORK_EARN_CASINO_AWARD(int amount, Hash hash)l
extern _native64(0x870289A558348378) void NETWORK_SPEND_BUY_ARCADE(any p0, any p1, any p2, any p3)l
extern _native64(0x5574637681911FDA) void NETWORK_SPEND_UPGRADE_ARCADE(any p0, any p1, any p2, any p3)l
extern _native64(0xD30E8392F407C328) void NETWORK_SPEND_CASINO_HEIST(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10)l
extern _native64(0xB5B58E24868CB09E) void NETWORK_SPEND_ARCADE_MGMT(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xEAD3D81F2C3A1458) void NETWORK_SPEND_PLAY_ARCADE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x43AA7FAC4E6D6687) void NETWORK_SPEND_ARCADE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x72E7C7B9615FA3C3) void NETWORK_EARN_CASINO_HEIST(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x4C3B75694F7E0D9C) void NETWORK_EARN_UPGRADE_ARCADE(any p0, any p1, any p2)l
extern _native64(0xD29334ED1A256DBF) void NETWORK_EARN_ARCADE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xA95CFB4E02390842) void NETWORK_EARN_COLLECTABLES(any p0, any p1, any p2)l
extern _native64(0x0DD362F14F18942A) void NETWORK_EARN_CHALLENGE(int amount, any p1, any p2)l
extern _native64(0x3EC7471E6909798A) void NETWORK_EARN_CASINO_HEIST_AWARDS(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x84FF63BD4966F33D) void NETWORK_EARN_COLLECTABLE_ITEM(int amount, any p1)l
extern _native64(0x5C9B198AF5A54FA6) void NETWORK_EARN_COLLECTABLE_COMPLETED_COLLECTION(int amount, any p1)l
extern _native64(0xDE68E30D89F97132) void NETWORK_EARN_YATCH_MISSION(int amount, any p1)l
extern _native64(0xE2E244AB823B4483) void NETWORK_EARN_DISPATCH_CALL(int amount, any p1)l
extern _native64(0x54ABA22FA6371249) void NETWORK_SPEND_BEACH_PARTY(any p0)l
extern _native64(0x6C8BC1488527AAAB) void NETWORK_SPEND_SUBMARINE(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xC991C255AA6D90B2) void NETWORK_SPEND_CASINO_CLUB(int amount1, any p1, bool p2, any p3, int p4, int p5, int p6, int amount2, any p8)l
extern _native64(0x90CD7C6871FBF1B4) void NETWORK_SPEND_BUY_SUB(any p0, any p1, any p2, any p3)l
extern _native64(0x89049A84065CE68E) void NETWORK_SPEND_UPGRADE_SUB(any p0, any p1, any p2, any p3)l
extern _native64(0xE86689E5F82DE429) void NETWORK_SPEND_ISLAND_HEIST(any p0, any p1, any p2, any p3)l
extern _native64(0xD21D111C46BA9F15) void NETWORK_EARN_ISLAND_HEIST(int amount1, any p1, any p2, any p3, int amount2, int p5)l
extern _native64(0xA51338E0DCCD4065) void NETWORK_EARN_BEACH_PARTY_LOST_FOUND(any p0, any p1, any p2)l
extern _native64(0xE2BB399D90942091) void NETWORK_EARN_FROM_ISLAND_HEIST_DJ_MISSION(any p0, any p1)l
extern _native64(0x1464E17207CD36E2) void NETWORK_SPEND_CAR_CLUB_MEMBERSHIP(int amount1, any p1, any p2, int amount2, any p4)l
extern _native64(0x925227803A0EAA1B) void NETWORK_SPEND_CAR_CLUB_BAR(any p0, bool p1, bool p2, any p3)l
extern _native64(0x9BEA350D7C48061B) void NETWORK_SPEND_AUTOSHOP_MODIFY(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xD1E46824E6FB92B5) void NETWORK_SPEND_CAR_CLUB_TAKEOVER(any p0, any p1, any p2, any p3)l
extern _native64(0xEEB7E5D1FEB20869) void NETWORK_SPEND_BUY_AUTOSHOP(any p0, any p1, any p2, any p3)l
extern _native64(0xDD829AA198FDC46C) void NETWORK_SPEND_UPGRADE_AUTOSHOP(any p0, any p1, any p2, any p3)l
extern _native64(0x36A7FD5A7194B03E) void NETWORK_EARN_AUTOSHOP_BUSINESS(any p0, any p1, any p2)l
extern _native64(0xC66D1CF99ED7FE25) void NETWORK_EARN_AUTOSHOP_INCOME(any p0, int p1)l
extern _native64(0xBC6227792A188E2E) void NETWORK_EARN_CARCLUB_MEMBERSHIP(any p0)l
extern _native64(0x533073E8A596008C) void NETWORK_EARN_DAILY_VEHICLE(any p0, any p1)l
extern _native64(0xFE65AFE7308E32B2) void NETWORK_EARN_DAILY_VEHICLE_BONUS(any p0)l
extern _native64(0xB846F547D3792DF6) void NETWORK_EARN_TUNER_AWARD(any p0, any p1, any p2)l
extern _native64(0xBCB266247193AC61) void NETWORK_EARN_TUNER_ROBBERY(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xC10322A8D3E061EE) void NETWORK_EARN_UPGRADE_AUTOSHOP(any p0, any p1)l
extern _native64(0x93AA4165CB67E925) void NETWORK_SPEND_INTERACTION_MENU_ABILITY(any p0, any p1, any p2, any p3)l
extern _native64(0xB9F7A469460E7A4A) void NETWORK_SPEND_SET_COMMON_FIELDS(any p0, any p1, any p2, bool p3)l
extern _native64(0x7E2F4E8F44CAF4E0) void NETWORK_SPEND_SET_DISCOUNT(bool p0)l
extern _native64(0xEA8CD3C9B3C35884) void NETWORK_SPEND_BUY_AGENCY(any p0, any p1, any p2, any p3)l
extern _native64(0x6CCA64840589A3B6) void NETWORK_SPEND_UPGRADE_AGENCY(any p0, any p1, any p2, any p3)l
extern _native64(0x1B2120405080125C) void NETWORK_SPEND_AGENCY(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xBF8793B91EA094A7) void NETWORK_SPEND_HIDDEN(any p0, any p1, any p2, any p3)l
extern _native64(0xD9DF467CBE4398C8) void NETWORK_SPEND_SOURCE_BIKE(any p0, any p1, any p2, any p3)l
extern _native64(0xD86581F9E7CDA383) void NETWORK_SPEND_COMP_SUV(any p0, any p1, any p2, any p3)l
extern _native64(0x61A2DF64ED2D396E) void NETWORK_SPEND_SUV_FST_TRVL(int p0, bool p1, bool p2, any p3)l
extern _native64(0xEBD482B82ACB8BAD) void NETWORK_SPEND_SUPPLY(any p0, any p1, any p2, any p3)l
extern _native64(0x923AEA8E78F8DF0B) void NETWORK_SPEND_BIKE_SHOP(any p0, any p1, any p2, any p3)l
extern _native64(0x02D24A35A9CC3503) void NETWORK_SPEND_VEHICLE_REQUESTED(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x2CEB0E0BC2A77C05) void NETWORK_SPEND_GUNRUNNING(any p0, any p1, any p2, any p3)l
extern _native64(0x663B4B9D11742A12) void NETWORK_EARN_AGENCY_SAFE(any p0)l
extern _native64(0x146D4EB6D22A403F) void NETWORK_EARN_AWARD_CONTRACT(any p0, any p1)l
extern _native64(0x38482AD49CB905C7) void NETWORK_EARN_AGENCY_CONTRACT(any p0, any p1)l
extern _native64(0x7397A115030F1BE3) void NETWORK_EARN_AWARD_PHONE(any p0, any p1)l
extern _native64(0xE29F3D5FA63B1B82) void NETWORK_EARN_AGENCY_PHONE(any p0, any p1, any p2)l
extern _native64(0x88D6C327D6C57C45) void NETWORK_EARN_AWARD_FIXER_MISSION(any p0, any p1)l
extern _native64(0x6283E5DE4C4460C6) void NETWORK_EARN_FIXER_PREP(any p0, any p1)l
extern _native64(0xBA154373C5FE51E8) void NETWORK_EARN_FIXER_FINALE(any p0, any p1)l
extern _native64(0xF4A8E57460BF2037) void NETWORK_EARN_FIXER_AGENCY_SHORT_TRIP(any p0, any p1)l
extern _native64(0x5B4DBDED84D6A420) void NETWORK_EARN_AWARD_SHORT_TRIP(any p0, any p1)l
extern _native64(0x235D41210B3A1A5E) void NETWORK_EARN_FIXER_RIVAL_DELIVERY(any p0, any p1)l
extern _native64(0xD07C7C3F1995108C) void NETWORK_EARN_UPGRADE_AGENCY(any p0, any p1)l
extern _native64(0x1254B5B3925EFD3D) void NETWORK_SPEND_APARTMENT_UTILITIES(int amount, bool p1, bool p2, any* data)l
extern _native64(0x92D1CFDA1227FF1C) void NETWORK_SPEND_BUSINESS_PROPERTY_FEES(any p0, any p1, any p2, any p3)l
extern _native64(0x45087AE480B233AC) void NETWORK_EARN_SIGHTSEEING_REWARD(any p0, any p1, any p2, any p3)l
extern _native64(0x2C5809EB9DF57257) void NETWORK_EARN_BIKER_SHOP(any p0, any p1)l
extern _native64(0x71BEC32FA466E105) void NETWORK_EARN_BIKER(any p0)l
extern _native64(0x59498BC8B1C8B15C) void NETWORK_YOHAN_SOURCE_GOODS(any p0, any p1, any p2, any p3)l
extern _native64(0xA2ED36DCF0FCA413) void _NETWORK_SPEND_BUY_MFGARAGE(any p0, any p1, any p2, any p3)l
extern _native64(0xCF8F346DDDC66643) void _NETWORK_SPEND_UPGRADE_MFGARAGE(any p0, any p1, any p2, any p3)l
extern _native64(0xB48185C0CA67B16B) void _NETWORK_SPEND_BUY_SUPPLIES(int p0, bool p1, bool p2, int p3)l
extern _native64(0xF1E26A7924327152) void _NETWORK_SPEND_BUY_ACID_LAB(any p0, any p1, any p2, any p3)l
extern _native64(0x110EE9D486C23126) void _NETWORK_SPEND_UPGRADE_ACID_LAB_EQUIPMENT(any p0, any p1, any p2, any p3)l
extern _native64(0xA7D541C9ACD63133) void _NETWORK_SPEND_UPGRADE_ACID_LAB_ARMOR(int p0, bool p1, bool p2, int p3)l
extern _native64(0x2940558E05BCC2EC) void _NETWORK_SPEND_UPGRADE_ACID_LAB_SCOOP(int p0, bool p1, bool p2, int p3)l
extern _native64(0x4B99AB08C92C54E4) void _NETWORK_SPEND_UPGRADE_ACID_LAB_MINES(int p0, bool p1, bool p2, int p3)l
extern _native64(0x842B1C5AF61ACDE9) void _NETWORK_SPEND_RENAME_ACID_LAB(any p0, any p1, any p2, any p3)l
extern _native64(0x446798F7495DD7D8) void _NETWORK_SPEND_RENAME_ACID_PRODUCT(any p0, any p1, any p2, any p3)l
extern _native64(0xDDF047577F1A02A7) void _NETWORK_EARN_AWARD_JUGGALO_MISSION(any p0, any p1)l
extern _native64(0xD1A8165767AD2D23) void _NETWORK_EARN_AWARD_ACID_LAB(any p0, any p1)l
extern _native64(0xC30650FA74A19D02) void _NETWORK_EARN_AWARD_DAILY_STASH(any p0, any p1)l
extern _native64(0xD01EBAEA1F905EF6) void _NETWORK_EARN_AWARD_DEAD_DROP(any p0, any p1)l
extern _native64(0xBEAFBB1B98B7EF55) void _NETWORK_EARN_AWARD_RANDOM_EVENT(any p0, any p1)l
extern _native64(0xA914768AD35CD3A5) void _NETWORK_EARN_AWARD_TAXI(any p0, any p1)l
extern _native64(0xA81017EE1324FDFE) void _NETWORK_EARN_STREET_DEALER(any p0, any p1)l
extern _native64(0x79B656937DF6DF5D) void _NETWORK_EARN_SELL_ACID(any p0, any p1)l
extern _native64(0xE3942D59E8A7F70D) void _NETWORK_EARN_SETUP_PARTICIPATION_ACID_LAB(any p0, any p1)l
extern _native64(0x136F11B5DF1B304D) void _NETWORK_EARN_SOURCE_PARTICIPATION_ACID_LAB(any p0, any p1)l
extern _native64(0xCA3EF9B09A8D76B4) void _NETWORK_EARN_SELL_PARTICIPATION_ACID_LAB(any p0, any p1)l
extern _native64(0xE01D10BA8CD53621) void _NETWORK_EARN_JUGGALO_STORY_MISSION(any p0, any p1)l
extern _native64(0x40FF6CCCC476185C) void _NETWORK_EARN_JUGGALO_STORY_MISSION_PARTICIPATION(any p0, any p1)l
extern _native64(0xCE4452AE85F5E252) void _NETWORK_EARN_FOOLIGAN_JOB(any p0, any p1)l
extern _native64(0xC376B92D0E060970) void _NETWORK_EARN_FOOLIGAN_JOB_PARTICIPATION(any p0, any p1)l
extern _native64(0x991E1588FAD9019D) void _NETWORK_EARN_TAXI_JOB(any p0, any p1)l
extern _native64(0xCABC9874AFA70D6D) void _NETWORK_EARN_DAILY_STASH_HOUSE_COMPLETED(any p0, any p1)l
extern _native64(0x9C0C6BD0F94CE391) void _NETWORK_EARN_DAILY_STASH_HOUSE_PARTICIPATION(any p0, any p1)l
extern _native64(0x55F006B9D4A46C1D) void _NETWORK_EARN_AVENGER(int amount, int p1)l
extern _native64(0xDEA273D5F8A9661A) void _NETWORK_EARN_SMUGGLER_OPS(any p0, any p1, any p2)l
extern _native64(0xDCEF983C24191997) void _NETWORK_EARN_BONUS_OBJECTIVE(int amount, any p1, any p2)l
extern _native64(0xF8332B06F0EECC9C) void _NETWORK_EARN_PROGRESS_HUB(any p0, any p1)l
extern _native64(0x8C7E8D6F96C9E948) void _NETWORK_SPENT_AIR_FREIGHT(int hangarCargoSourcingPrice, bool fromBank, bool fromBankAndWallet, int cost, int warehouseId, int warehouseSlot)l
extern _native64(0xED1B407BADA42CEC) void _NETWORK_SPENT_SKIP_CARGO_SOURCE_SETUP(int amount, bool fromBank, bool fromBankAndWallet, int cost)l
extern _native64(0x95CE79A6939C537A) void _NETWORK_SPENT_STEALTH_MODULE(int amount, bool fromBank, bool fromBankAndWallet, Hash p3)l
extern _native64(0xD687100F616163F4) void _NETWORK_SPENT_MISSILE_JAMMER(int amount, bool fromBank, bool fromBankAndWallet, Hash p3)l
extern _native64(0x76EF28DA05EA395A) int NETWORK_GET_VC_BANK_BALANCE()l
extern _native64(0xA40F9C2623F6A8B5) int NETWORK_GET_VC_WALLET_BALANCE(int characterSlot)l
extern _native64(0x5CBAD97E059E1B94) int NETWORK_GET_VC_BALANCE()l
extern _native64(0x5D1E75F91C07DEE5) int NETWORK_GET_EVC_BALANCE()l
extern _native64(0x4F54F3B6C202FB4E) int NETWORK_GET_PVC_BALANCE()l
extern _native64(0xF9B10B529DCFB33B) const char* NETWORK_GET_STRING_WALLET_BALANCE(int characterSlot)l
extern _native64(0xA6FA3979BED01B81) const char* NETWORK_GET_STRING_BANK_BALANCE()l
extern _native64(0x700AF71AE615E6DD) const char* NETWORK_GET_STRING_BANK_WALLET_BALANCE(int character)l
extern _native64(0xED5AB8860415BABA) bool NETWORK_GET_CAN_SPEND_FROM_WALLET(int amount, int characterSlot)l
extern _native64(0xA31FD6A0865B6D14) bool NETWORK_GET_CAN_SPEND_FROM_BANK(int amount)l
extern _native64(0xDC18531D7019A535) bool NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET(int amount, int characterSlot)l
extern _native64(0x13A8DE2FD77D04F3) int NETWORK_GET_PVC_TRANSFER_BALANCE()l
extern _native64(0x08E8EEADFD0DC4A0) bool NETWORK_GET_CAN_TRANSFER_CASH(int amount)l
extern _native64(0x5D17BE59D2123284) bool NETWORK_CAN_RECEIVE_PLAYER_CASH(any p0, any p1, any p2, any p3)l
extern _native64(0xEA560AC9EEB1E19B) int NETWORK_GET_REMAINING_TRANSFER_BALANCE()l
extern _native64(0xF70EFA14FE091429) int WITHDRAW_VC(int amount)l
extern _native64(0xE260E0BB9CD995AC) bool DEPOSIT_VC(int amount)l
extern _native64(0xE154B48B68EF72BC) bool HAS_VC_WITHDRAWAL_COMPLETED(any p0)l
extern _native64(0x6FCF8DDEA146C45B) bool WAS_VC_WITHDRAWAL_SUCCESSFUL(any p0)l
#pragma endregion //}
#pragma region NETSHOPPING //{
extern _native64(0x7D2708796355B20B) bool NET_GAMESERVER_USE_SERVER_TRANSACTIONS()l
extern _native64(0xBD4D7EAF8A30F637) bool NET_GAMESERVER_CATALOG_ITEM_IS_VALID(const char* name)l
extern _native64(0x247F0F73A182EA0B) bool NET_GAMESERVER_CATALOG_ITEM_KEY_IS_VALID(Hash hash)l
extern _native64(0xC27009422FCCA88D) int NET_GAMESERVER_GET_PRICE(Hash itemHash, Hash categoryHash, bool p2)l
extern _native64(0x3C4487461E9B0DCB) bool NET_GAMESERVER_CATALOG_IS_VALID()l
extern _native64(0x2B949A1E6AEC8F6A) bool NET_GAMESERVER_IS_CATALOG_CURRENT()l
extern _native64(0x85F6C9ABA1DE2BCF) Hash NET_GAMESERVER_GET_CATALOG_CLOUD_CRC()l
extern _native64(0x357B152EF96C30B6) bool NET_GAMESERVER_REFRESH_SERVER_CATALOG()l
extern _native64(0xCF38DAFBB49EDE5E) bool NET_GAMESERVER_RETRIEVE_CATALOG_REFRESH_STATUS(int* state)l
extern _native64(0xE3E5A7C64CA2C6ED) bool NET_GAMESERVER_INIT_SESSION()l
extern _native64(0x0395CB47B022E62C) bool NET_GAMESERVER_RETRIEVE_INIT_SESSION_STATUS(int* p0)l
extern _native64(0xA135AC892A58FC07) bool NET_GAMESERVER_START_SESSION(int charSlot)l
extern _native64(0x72EB7BA9B69BF6AB) bool NET_GAMESERVER_START_SESSION_PENDING()l
extern _native64(0x170910093218C8B9) bool NET_GAMESERVER_RETRIEVE_START_SESSION_STATUS(int* p0)l
extern _native64(0xC13C38E47EA5DF31) bool NET_GAMESERVER_RETRIEVE_SESSION_ERROR_CODE(int* p0)l
extern _native64(0xB24F0944DA203D9E) bool NET_GAMESERVER_IS_SESSION_VALID(int charSlot)l
extern _native64(0x74A0FD0688F1EE45) bool NET_GAMESERVER_CLEAR_SESSION(int p0)l
extern _native64(0x2F41D51BA3BCD1F1) bool NET_GAMESERVER_SESSION_APPLY_RECEIVED_DATA(int charSlot)l
extern _native64(0x810E8431C0614BF9) bool NET_GAMESERVER_IS_SESSION_REFRESH_PENDING()l
extern _native64(0x35A1B3E1D1315CFA) bool NET_GAMESERVER_START_SESSION_RESTART(bool inventory, bool playerbalance)l
extern _native64(0x613F125BA3BD2EB9) bool NET_GAMESERVER_TRANSACTION_IN_PROGRESS()l
extern _native64(0x897433D292B44130) bool NET_GAMESERVER_GET_SESSION_STATE_AND_STATUS(int* p0, bool* p1)l
extern _native64(0x279F08B1A4B29B7E) bool NET_GAMESERVER_BASKET_START(int* transactionId, Hash categoryHash, Hash actionHash, int flags)l
extern _native64(0xFA336E7F40C0A0D0) bool NET_GAMESERVER_BASKET_END()l
extern _native64(0xA65568121DF2EA26) bool NET_GAMESERVER_BASKET_IS_ACTIVE()l
extern _native64(0xF30980718C8ED876) bool NET_GAMESERVER_BASKET_ADD_ITEM(any* itemData, int quantity)l
extern _native64(0x27F76CC6C55AD30E) bool NET_GAMESERVER_BASKET_IS_FULL()l
extern _native64(0xE1A0450ED46A7812) bool NET_GAMESERVER_BASKET_APPLY_SERVER_DATA(any p0, any* p1)l
extern _native64(0x39BE7CEA8D9CC8E6) bool NET_GAMESERVER_CHECKOUT_START(int transactionId)l
extern _native64(0x3C5FD37B5499582E) bool NET_GAMESERVER_BEGIN_SERVICE(int* transactionId, Hash categoryHash, Hash itemHash, Hash actionTypeHash, int value, int flags)l
extern _native64(0xE2A99A9B524BEFFF) bool NET_GAMESERVER_END_SERVICE(int transactionId)l
extern _native64(0x51F1A8E48C3D2F6D) bool NET_GAMESERVER_DELETE_CHARACTER(int slot, bool transfer, Hash reason)l
extern _native64(0x0A6D923DFFC9BD89) int NET_GAMESERVER_DELETE_CHARACTER_GET_STATUS()l
extern _native64(0x112CEF1615A1139F) bool NET_GAMESERVER_DELETE_SET_TELEMETRY_NONCE_SEED()l
extern _native64(0xD47A2C1BA117471D) bool NET_GAMESERVER_TRANSFER_BANK_TO_WALLET(int charSlot, int amount)l
extern _native64(0xC2F7FE5309181C7D) bool NET_GAMESERVER_TRANSFER_WALLET_TO_BANK(int charSlot, int amount)l
extern _native64(0x23789E777D14CE44) int NET_GAMESERVER_TRANSFER_BANK_TO_WALLET_GET_STATUS()l
extern _native64(0x350AA5EBC03D3BD2) int NET_GAMESERVER_TRANSFER_WALLET_TO_BANK_GET_STATUS()l
extern _native64(0x498C1E05CE5F7877) bool NET_GAMESERVER_TRANSFER_CASH_SET_TELEMETRY_NONCE_SEED()l
extern _native64(0x9507D4271988E1AE) bool NET_GAMESERVER_SET_TELEMETRY_NONCE_SEED(int p0)l
#pragma endregion //}
#pragma region NETWORK //{
extern _native64(0xFCA9373EF340AC0A) const char* GET_ONLINE_VERSION()l
extern _native64(0x054354A99211EB96) bool NETWORK_IS_SIGNED_IN()l
extern _native64(0x1077788E268557C2) bool NETWORK_IS_SIGNED_ONLINE()l
extern _native64(0xBD545D44CCE70597) bool NETWORK_IS_NP_AVAILABLE()l
extern _native64(0xEBCAB9E5048434F4) bool NETWORK_IS_NP_PENDING()l
extern _native64(0x74FB3E29E6D10FA9) int NETWORK_GET_NP_UNAVAILABLE_REASON()l
extern _native64(0x7808619F31FF22DB) bool NETWORK_IS_CONNETED_TO_NP_PRESENCE()l
extern _native64(0xA0FA4EC6A05DA44E) bool NETWORK_IS_LOGGED_IN_TO_PSN()l
extern _native64(0x85443FF4C328F53B) bool NETWORK_HAS_VALID_ROS_CREDENTIALS()l
extern _native64(0x8D11E61A4ABF49CC) bool NETWORK_IS_REFRESHING_ROS_CREDENTIALS()l
extern _native64(0x9A4CF4F48AD77302) bool NETWORK_IS_CLOUD_AVAILABLE()l
extern _native64(0x67A5589628E0CFF6) bool NETWORK_HAS_SOCIAL_CLUB_ACCOUNT()l
extern _native64(0xBA9775570DB788CF) bool NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT()l
extern _native64(0x8DB296B814EDDA07) bool NETWORK_IS_HOST()l
extern _native64(0x8251FB94DC4FDFC8) Player NETWORK_GET_HOST_PLAYER_INDEX()l
extern _native64(0x4237E822315D8BA9) bool NETWORK_WAS_GAME_SUSPENDED()l
extern _native64(0x25CB5A9F37BFD063) bool NETWORK_HAVE_ONLINE_PRIVILEGES()l
extern _native64(0x1353F87E89946207) bool NETWORK_HAS_AGE_RESTRICTIONS()l
extern _native64(0x72D918C99BCACC54) bool NETWORK_HAVE_USER_CONTENT_PRIVILEGES(int p0)l
extern _native64(0xAEEF48CDF5B6CE7C) bool NETWORK_HAVE_COMMUNICATION_PRIVILEGES(int p0, Player player)l
extern _native64(0x78321BEA235FD8CD) bool NETWORK_CHECK_ONLINE_PRIVILEGES(any p0, bool p1)l
extern _native64(0x595F028698072DD9) bool NETWORK_CHECK_USER_CONTENT_PRIVILEGES(int p0, int p1, bool p2)l
extern _native64(0x83F28CE49FBBFFBA) bool NETWORK_CHECK_COMMUNICATION_PRIVILEGES(int p0, int p1, bool p2)l
extern _native64(0x07EAB372C8841D99) bool NETWORK_CHECK_TEXT_COMMUNICATION_PRIVILEGES(any p0, any p1, any p2)l
extern _native64(0x906CA41A4B74ECA4) bool NETWORK_IS_USING_ONLINE_PROMOTION()l
extern _native64(0x023ACAB2DC9DC4A4) bool NETWORK_SHOULD_SHOW_PROMOTION_ALERT_SCREEN()l
extern _native64(0x76BF03FADBF154F5) bool NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV()l
extern _native64(0x9614B71F8ADB982B) int NETWORK_GET_AGE_GROUP()l
extern _native64(0x0CF6CC51AA18F0F8) bool NETWORK_CHECK_PRIVILEGES(any p0, any p1, any p2)l
extern _native64(0x64E5C4CC82847B73) bool NETWORK_IS_PRIVILEGE_CHECK_IN_PROGRESS()l
extern _native64(0x1F7BC3539F9E0224) void NETWORK_SET_PRIVILEGE_CHECK_RESULT_NOT_NEEDED()l
extern _native64(0xDE9225854F37BF72) bool NETWORK_RESOLVE_PRIVILEGE_USER_CONTENT()l
extern _native64(0x5EA784D197556507) bool NETWORK_HAVE_PLATFORM_SUBSCRIPTION()l
extern _native64(0xA8ACB6459542A8C8) bool NETWORK_IS_PLATFORM_SUBSCRIPTION_CHECK_PENDING()l
extern _native64(0x83FE8D7229593017) void NETWORK_SHOW_ACCOUNT_UPGRADE_UI()l
extern _native64(0x7788DFE15016A182) bool NETWORK_IS_SHOWING_SYSTEM_UI_OR_RECENTLY_REQUESTED_UPSELL()l
extern _native64(0x53C10C8BD774F2C9) bool NETWORK_NEED_TO_START_NEW_GAME_BUT_BLOCKED()l
extern _native64(0x580CE4438479CC61) bool NETWORK_CAN_BAIL()l
extern _native64(0x95914459A87EBA28) void NETWORK_BAIL(int p0, int p1, int p2)l
extern _native64(0x283B6062A2C01E9B) void NETWORK_ON_RETURN_TO_SINGLE_PLAYER()l
extern _native64(0x8B4FFC790CA131EF) bool NETWORK_TRANSITION_START(int p0, any p1, any p2, any p3)l
extern _native64(0xC3BFED92026A2AAD) bool NETWORK_TRANSITION_ADD_STAGE(Hash hash, int p1, int p2, int state, int p4)l
extern _native64(0x04918A41BC9B8157) bool NETWORK_TRANSITION_FINISH(any p0, any p1, any p2)l
extern _native64(0xAF50DA1A3F8B1BA4) bool NETWORK_CAN_ACCESS_MULTIPLAYER(int* loadingState)l
extern _native64(0x9747292807126EDA) bool NETWORK_IS_MULTIPLAYER_DISABLED()l
extern _native64(0x7E782A910C362C25) bool NETWORK_CAN_ENTER_MULTIPLAYER()l
extern _native64(0x330ED4D05491934F) bool NETWORK_SESSION_DO_FREEROAM_QUICKMATCH(any p0, any p1, any p2)l
extern _native64(0x2CFC76E0D087C994) bool NETWORK_SESSION_DO_FRIEND_MATCHMAKING(int p0, int p1, int p2)l
extern _native64(0x94BC51E9449D917F) bool NETWORK_SESSION_DO_CREW_MATCHMAKING(int crewId, int p1, int p2, int maxPlayers)l
extern _native64(0xBE3E347A87ACEB82) bool NETWORK_SESSION_DO_ACTIVITY_QUICKMATCH(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x6F3D4ED9BEE4E61D) bool NETWORK_SESSION_HOST(int p0, int maxPlayers, bool p2)l
extern _native64(0xED34C0C02C098BB7) bool NETWORK_SESSION_HOST_CLOSED(int p0, int maxPlayers)l
extern _native64(0xB9CFD27A5D578D83) bool NETWORK_SESSION_HOST_FRIENDS_ONLY(int p0, int maxPlayers)l
extern _native64(0xFBCFA2EA2E206890) bool NETWORK_SESSION_IS_CLOSED_FRIENDS()l
extern _native64(0x74732C6CA90DA2B4) bool NETWORK_SESSION_IS_CLOSED_CREW()l
extern _native64(0xF3929C2379B60CCE) bool NETWORK_SESSION_IS_SOLO()l
extern _native64(0xCEF70AA5B3F89BA1) bool NETWORK_SESSION_IS_PRIVATE()l
extern _native64(0xA02E59562D711006) bool NETWORK_SESSION_END(bool p0, bool p1)l
extern _native64(0xB9351A07A0D458B1) bool NETWORK_SESSION_LEAVE(any p0)l
extern _native64(0xFA8904DC5F304220) void NETWORK_SESSION_KICK_PLAYER(Player player)l
extern _native64(0xD6D09A6F32F49EF1) bool NETWORK_SESSION_GET_KICK_VOTE(Player player)l
extern _native64(0x041C7F2A6C9894E6) bool NETWORK_SESSION_RESERVE_SLOTS_TRANSITION(any p0, any p1, any p2)l
extern _native64(0x59DF79317F85A7E0) bool NETWORK_JOIN_PREVIOUSLY_FAILED_SESSION()l
extern _native64(0xFFE1E5B792D92B34) bool NETWORK_JOIN_PREVIOUSLY_FAILED_TRANSITION()l
extern _native64(0x49EC8030F5015F8B) void NETWORK_SESSION_SET_MATCHMAKING_GROUP(int matchmakingGroup)l
extern _native64(0x8B6A4DD0AF9CE215) void NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(int playerType, int playerCount)l
extern _native64(0x56CE820830EF040B) int NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE(int p0)l
extern _native64(0xCAE55F48D3D7875C) void NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP(int groupId)l
extern _native64(0xF49ABC20D8552257) void NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT(any p0)l
extern _native64(0x4811BBAC21C5FCD5) void NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION(any p0)l
extern _native64(0x5539C3EBF104A53A) void NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION(bool p0)l
extern _native64(0x702BC4D605522539) void NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION(any p0)l
extern _native64(0x3F52E880AAF6C8CA) void NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID(bool p0)l
extern _native64(0xF1EEA2DDA9FFA69D) void NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE(int p0)l
extern _native64(0x59D421683D31835A) void NETWORK_SESSION_SET_NUM_BOSSES(int num)l
extern _native64(0x1153FA02A659051C) void NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN()l
extern _native64(0xC19F6C8E7865A6FF) void NETWORK_SESSION_VALIDATE_JOIN(bool p0)l
extern _native64(0x236406F60CF216D6) void NETWORK_ADD_FOLLOWERS(int* p0, int p1)l
extern _native64(0x058F43EC59A8631A) void NETWORK_CLEAR_FOLLOWERS()l
extern _native64(0x6D03BFBD643B2A02) void NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(int* hours, int* minutes, int* seconds)l
extern _native64(0x600F8CB31C7AAB6E) void NETWORK_SESSION_SET_GAMEMODE(any p0)l
extern _native64(0xDFFA5BE8381C3314) int NETWORK_SESSION_GET_HOST_AIM_PREFERENCE()l
extern _native64(0xE532D6811B3A4D2A) bool NETWORK_FIND_GAMERS_IN_CREW(int crewId)l
extern _native64(0xF7B2CFDE5C9F700D) bool NETWORK_FIND_MATCHED_GAMERS(int attribute, float fallbackLimit, float lowerLimit, float upperLimit)l
extern _native64(0xDDDF64C91BFCF0AA) bool NETWORK_IS_FINDING_GAMERS()l
extern _native64(0xF9B83B77929D8863) bool NETWORK_DID_FIND_GAMERS_SUCCEED()l
extern _native64(0xA1B043EE79A916FB) int NETWORK_GET_NUM_FOUND_GAMERS()l
extern _native64(0x9DCFF2AFB68B3476) bool NETWORK_GET_FOUND_GAMER(any* p0, any p1)l
extern _native64(0x6D14CCEE1B40381A) void NETWORK_CLEAR_FOUND_GAMERS()l
extern _native64(0x85A0EF54A500882C) bool NETWORK_QUEUE_GAMER_FOR_STATUS(any* p0)l
extern _native64(0x2CC848A861D01493) bool NETWORK_GET_GAMER_STATUS_FROM_QUEUE()l
extern _native64(0x94A8394D150B013A) bool NETWORK_IS_GETTING_GAMER_STATUS()l
extern _native64(0x5AE17C6B0134B7F1) bool NETWORK_DID_GET_GAMER_STATUS_SUCCEED()l
extern _native64(0x02A8BEC6FD9AF660) bool NETWORK_GET_GAMER_STATUS_RESULT(any* p0, any p1)l
extern _native64(0x86E0660E4F5C956D) void NETWORK_CLEAR_GET_GAMER_STATUS()l
extern _native64(0xC6F8AB8A4189CF3A) void NETWORK_SESSION_JOIN_INVITE()l
extern _native64(0x2FBF47B1B36D36F9) void NETWORK_SESSION_CANCEL_INVITE()l
extern _native64(0xA29177F7703B5644) void NETWORK_SESSION_FORCE_CANCEL_INVITE()l
extern _native64(0xAC8C7B9B88C4A668) bool NETWORK_HAS_PENDING_INVITE()l
extern _native64(0xC42DD763159F3461) bool NETWORK_HAS_CONFIRMED_INVITE()l
extern _native64(0x62A0296C1BB1CEB3) bool NETWORK_REQUEST_INVITE_CONFIRMED_EVENT()l
extern _native64(0x23DFB504655D0CE4) bool NETWORK_SESSION_WAS_INVITED()l
extern _native64(0xE57397B4A3429DD0) void NETWORK_SESSION_GET_INVITER(any* gamerHandle)l
extern _native64(0xD313DE83394AF134) bool NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE()l
extern _native64(0xBDB6F89C729CF388) bool NETWORK_SESSION_IS_DISPLAYING_INVITE_CONFIRMATION()l
extern _native64(0xA0682D67EF1FBA3D) void NETWORK_SUPPRESS_INVITE(bool toggle)l
extern _native64(0x34F9E9049454A7A0) void NETWORK_BLOCK_INVITES(bool toggle)l
extern _native64(0xCFEB8AF24FC1D0BB) void NETWORK_BLOCK_JOIN_QUEUE_INVITES(bool toggle)l
extern _native64(0x68980414688F7F9D) void NETWORK_SET_CAN_RECEIVE_RS_INVITES(bool p0)l
extern _native64(0xF814FEC6A19FD6E0) void NETWORK_STORE_INVITE_THROUGH_RESTART()l
extern _native64(0x6B07B9CE4D390375) void NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH(bool p0)l
extern _native64(0x7AC752103856FB20) void NETWORK_SET_SCRIPT_READY_FOR_EVENTS(bool toggle)l
extern _native64(0x74698374C45701D2) bool NETWORK_IS_OFFLINE_INVITE_PENDING()l
extern _native64(0x140E6A44870A11CE) void NETWORK_CLEAR_OFFLINE_INVITE_PENDING()l
extern _native64(0xC74C33FCA52856D5) void NETWORK_SESSION_HOST_SINGLE_PLAYER(int p0)l
extern _native64(0x3442775428FD2DAA) void NETWORK_SESSION_LEAVE_SINGLE_PLAYER()l
extern _native64(0x10FAB35428CCC9D7) bool NETWORK_IS_GAME_IN_PROGRESS()l
extern _native64(0xD83C2B94E7508980) bool NETWORK_IS_SESSION_ACTIVE()l
extern _native64(0xCA97246103B63917) bool NETWORK_IS_IN_SESSION()l
extern _native64(0x9DE624D2FC4B603F) bool NETWORK_IS_SESSION_STARTED()l
extern _native64(0xF4435D66A8E2905E) bool NETWORK_IS_SESSION_BUSY()l
extern _native64(0x4EEBC3694E49C572) bool NETWORK_CAN_SESSION_END()l
extern _native64(0x4C9034162368E206) int NETWORK_GET_GAME_MODE()l
extern _native64(0x271CC6AB59EBF9A5) void NETWORK_SESSION_MARK_VISIBLE(bool toggle)l
extern _native64(0xBA416D68C631496A) bool NETWORK_SESSION_IS_VISIBLE()l
extern _native64(0xA73667484D7037C3) void NETWORK_SESSION_BLOCK_JOIN_REQUESTS(bool toggle)l
extern _native64(0xB4AB419E0D86ACAE) void NETWORK_SESSION_CHANGE_SLOTS(int slots, bool p1)l
extern _native64(0x53AFD64C6758F2F9) int NETWORK_SESSION_GET_PRIVATE_SLOTS()l
extern _native64(0x9C1556705F864230) bool NETWORK_SESSION_VOICE_HOST()l
extern _native64(0x6793E42BE02B575D) bool NETWORK_SESSION_VOICE_LEAVE()l
extern _native64(0xABD5E88B8A2D3DB2) void NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER(any* gamerHandle)l
extern _native64(0x7F8413B7FC2AA6B9) void NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST(bool p0, int p1)l
extern _native64(0x5B8ED3DB018927B1) void NETWORK_SESSION_VOICE_SET_TIMEOUT(int timeout)l
extern _native64(0x855BC38818F6F684) bool NETWORK_SESSION_IS_IN_VOICE_SESSION()l
extern _native64(0xB5D3453C98456528) bool NETWORK_SESSION_IS_VOICE_SESSION_ACTIVE()l
extern _native64(0xEF0912DDF7C4CB4B) bool NETWORK_SESSION_IS_VOICE_SESSION_BUSY()l
extern _native64(0x3A214F2EC889B100) bool NETWORK_SEND_TEXT_MESSAGE(const char* message, any* gamerHandle)l
extern _native64(0x75138790B4359A74) void NETWORK_SET_ACTIVITY_SPECTATOR(bool toggle)l
extern _native64(0x12103B9E0C9F92FB) bool NETWORK_IS_ACTIVITY_SPECTATOR()l
extern _native64(0x0E4F77F7B9D74D84) void NETWORK_SET_ACTIVITY_PLAYER_MAX(any p0)l
extern _native64(0x9D277B76D1D12222) void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(int maxSpectators)l
extern _native64(0x73E2B500410DA5A2) int NETWORK_GET_ACTIVITY_PLAYER_NUM(bool p0)l
extern _native64(0x2763BBAA72A7BCB9) bool NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(any* gamerHandle)l
extern _native64(0xA60BB5CE242BB254) bool NETWORK_HOST_TRANSITION(int p0, int p1, int p2, int p3, any p4, bool p5, bool p6, int p7, any p8, int p9)l
extern _native64(0x71FB0EBCD4915D56) bool NETWORK_DO_TRANSITION_QUICKMATCH(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xA091A5E44F0072E5) bool NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x9C4AB58491FDC98A) bool NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP(any p0, any p1, any p2, any p3, any* p4, any p5, any p6, any p7)l
extern _native64(0xA06509A691D12BE4) bool NETWORK_JOIN_GROUP_ACTIVITY()l
extern _native64(0x1888694923EF4591) void NETWORK_CLEAR_GROUP_ACTIVITY()l
extern _native64(0xB13E88E655E5A3BC) void NETWORK_RETAIN_ACTIVITY_GROUP()l
extern _native64(0x6512765E3BE78C50) bool NETWORK_IS_TRANSITION_CLOSED_FRIENDS()l
extern _native64(0x0DBD5D7E3C5BEC3B) bool NETWORK_IS_TRANSITION_CLOSED_CREW()l
extern _native64(0x5DC577201723960A) bool NETWORK_IS_TRANSITION_SOLO()l
extern _native64(0x5A6AA44FF8E931E6) bool NETWORK_IS_TRANSITION_PRIVATE()l
extern _native64(0x617F49C2668E6155) int NETWORK_GET_NUM_TRANSITION_NON_ASYNC_GAMERS()l
extern _native64(0x261E97AD7BCF3D40) void NETWORK_MARK_AS_PREFERRED_ACTIVITY(bool p0)l
extern _native64(0x39917E1B4CB0F911) void NETWORK_MARK_AS_WAITING_ASYNC(bool p0)l
extern _native64(0x2CE9D95E4051AECD) void NETWORK_SET_IN_PROGRESS_FINISH_TIME(any p0)l
extern _native64(0xEF26739BCD9907D5) void NETWORK_SET_TRANSITION_CREATOR_HANDLE(any* p0)l
extern _native64(0xFB3272229A82C759) void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE()l
extern _native64(0x4A595C32F77DFF76) bool NETWORK_INVITE_GAMERS_TO_TRANSITION(any* p0, any p1)l
extern _native64(0xCA2C8073411ECDB6) void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(any* gamerHandle)l
extern _native64(0xD23A1A815D21DB19) bool NETWORK_LEAVE_TRANSITION()l
extern _native64(0x2DCF46CB1A4F0884) bool NETWORK_LAUNCH_TRANSITION()l
extern _native64(0xA2E9C1AB8A92E8CD) void NETWORK_SET_DO_NOT_LAUNCH_FROM_JOIN_AS_MIGRATED_HOST(bool toggle)l
extern _native64(0x023782EFC70585EE) void NETWORK_CANCEL_TRANSITION_MATCHMAKING()l
extern _native64(0xEAA572036990CD1B) void NETWORK_BAIL_TRANSITION(int p0, int p1, int p2)l
extern _native64(0x3E9BB38102A589B0) bool NETWORK_DO_TRANSITION_TO_GAME(bool p0, int maxPlayers)l
extern _native64(0x4665F51EFED00034) bool NETWORK_DO_TRANSITION_TO_NEW_GAME(bool p0, int maxPlayers, bool p2)l
extern _native64(0x3AAD8B2FCA1E289F) bool NETWORK_DO_TRANSITION_TO_FREEMODE(any* p0, any p1, bool p2, int players, bool p4)l
extern _native64(0x9E80A5BA8109F974) bool NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(any* p0, any p1, int players, bool p3, bool p4, bool p5)l
extern _native64(0x9D7696D8F4FA6CB7) bool NETWORK_IS_TRANSITION_TO_GAME()l
extern _native64(0x73B000F7FBC55829) int NETWORK_GET_TRANSITION_MEMBERS(any* data, int dataCount)l
extern _native64(0x521638ADA1BA0D18) void NETWORK_APPLY_TRANSITION_PARAMETER(int p0, int p1)l
extern _native64(0xEBEFC2E77084F599) void NETWORK_APPLY_TRANSITION_PARAMETER_STRING(int p0, const char* string, bool p2)l
extern _native64(0x31D1D2B858D25E6B) bool NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(any* gamerHandle, const char* p1, int p2, int p3, bool p4)l
extern _native64(0x5728BB6D63E3FF1D) bool NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(any* p0)l
extern _native64(0x0B824797C9BF2159) bool NETWORK_IS_TRANSITION_HOST()l
extern _native64(0x6B5C83BA3EFE6A10) bool NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(any* gamerHandle)l
extern _native64(0x65042B9774C4435E) bool NETWORK_GET_TRANSITION_HOST(any* gamerHandle)l
extern _native64(0x68049AEFF83D8F0A) bool NETWORK_IS_IN_TRANSITION()l
extern _native64(0x53FA83401D9C07FE) bool NETWORK_IS_TRANSITION_STARTED()l
extern _native64(0x520F3282A53D26B7) bool NETWORK_IS_TRANSITION_BUSY()l
extern _native64(0x292564C735375EDF) bool NETWORK_IS_TRANSITION_MATCHMAKING()l
extern _native64(0xC571D0E77D8BBC29) bool NETWORK_IS_TRANSITION_LEAVE_POSTPONED()l
extern _native64(0x1398582B7F72B3ED) void NETWORK_TRANSITION_SET_IN_PROGRESS(any p0)l
extern _native64(0x1F8E00FB18239600) void NETWORK_TRANSITION_SET_CONTENT_CREATOR(any p0)l
extern _native64(0xF6F4383B7C92F11A) void NETWORK_TRANSITION_SET_ACTIVITY_ISLAND(any p0)l
extern _native64(0x2B3A8F7CA3A38FDE) void NETWORK_OPEN_TRANSITION_MATCHMAKING()l
extern _native64(0x43F4DBA69710E01E) void NETWORK_CLOSE_TRANSITION_MATCHMAKING()l
extern _native64(0x37A4494483B9F5C9) bool NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING()l
extern _native64(0x0C978FDA19692C2C) void NETWORK_SET_TRANSITION_VISIBILITY_LOCK(bool p0, bool p1)l
extern _native64(0xD0A484CB2F829FBE) bool NETWORK_IS_TRANSITION_VISIBILITY_LOCKED()l
extern _native64(0x30DE938B516F0AD2) void NETWORK_SET_TRANSITION_ACTIVITY_ID(any p0)l
extern _native64(0xEEEDA5E6D7080987) void NETWORK_CHANGE_TRANSITION_SLOTS(any p0, bool p1)l
extern _native64(0x973D76AA760A6CB6) void NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS(bool p0)l
extern _native64(0x9AC9CCBFA8C29795) bool NETWORK_HAS_PLAYER_STARTED_TRANSITION(Player player)l
extern _native64(0x2615AA2A695930C1) bool NETWORK_ARE_TRANSITION_DETAILS_VALID(any p0)l
extern _native64(0x9D060B08CD63321A) bool NETWORK_JOIN_TRANSITION(Player player)l
extern _native64(0x7284A47B3540E6CF) bool NETWORK_HAS_INVITED_GAMER_TO_TRANSITION(any* p0)l
extern _native64(0x3F9990BF5F22759C) bool NETWORK_HAS_TRANSITION_INVITE_BEEN_ACKED(any* p0)l
extern _native64(0x05095437424397FA) bool NETWORK_IS_ACTIVITY_SESSION()l
extern _native64(0x236905C700FDB54D) void NETWORK_DISABLE_REALTIME_MULTIPLAYER()l
extern _native64(0x4A9FDE3A5A6D0437) void NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED(bool toggle)l
extern _native64(0xC3C7A6AFDB244624) bool NETWORK_SEND_INVITE_VIA_PRESENCE(any* gamerHandle, const char* p1, int dataCount, int p3)l
extern _native64(0xC116FF9B4D488291) bool NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE(any* gamerHandle, const char* p1, int dataCount, int p3)l
extern _native64(0x1171A97A3D3981B6) bool NETWORK_SEND_IMPORTANT_TRANSITION_INVITE_VIA_PRESENCE(any* gamerHandle, const char* p1, int dataCount, int p3)l
extern _native64(0x742B58F723233ED9) int NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID(int p0)l
extern _native64(0xCEFA968912D0F78D) int NETWORK_GET_NUM_PRESENCE_INVITES()l
extern _native64(0xFA91550DF9318B22) bool NETWORK_ACCEPT_PRESENCE_INVITE(int p0)l
extern _native64(0xF0210268DB0974B1) bool NETWORK_REMOVE_PRESENCE_INVITE(int p0)l
extern _native64(0xDFF09646E12EC386) int NETWORK_GET_PRESENCE_INVITE_ID(int p0)l
extern _native64(0x4962CC4AA2F345B7) const char* NETWORK_GET_PRESENCE_INVITE_INVITER(int p0)l
extern _native64(0x38D5B0FEBB086F75) bool NETWORK_GET_PRESENCE_INVITE_HANDLE(any p0, any* p1)l
extern _native64(0x26E1CD96B0903D60) int NETWORK_GET_PRESENCE_INVITE_SESSION_ID(any p0)l
extern _native64(0x24409FC4C55CB22D) const char* NETWORK_GET_PRESENCE_INVITE_CONTENT_ID(int p0)l
extern _native64(0xD39B3FFF8FFDD5BF) int NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH(int p0)l
extern _native64(0x728C4CC7920CD102) int NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT(int p0)l
extern _native64(0x3DBF2DF0AEB7D289) bool NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN(int p0)l
extern _native64(0x8806CEBFABD3CE05) bool NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT(any p0)l
extern _native64(0x76D9B976C4C09FDE) bool NETWORK_HAS_FOLLOW_INVITE()l
extern _native64(0xC88156EBB786F8D5) bool NETWORK_ACTION_FOLLOW_INVITE()l
extern _native64(0x439BFDE3CD0610F6) bool NETWORK_CLEAR_FOLLOW_INVITE()l
extern _native64(0xEBF8284D8CADEB53) void NETWORK_REMOVE_AND_CANCEL_ALL_INVITES()l
extern _native64(0x7524B431B2E6F7EE) void NETWORK_REMOVE_TRANSITION_INVITE(any* p0)l
extern _native64(0x726E0375C7A26368) void NETWORK_REMOVE_ALL_TRANSITION_INVITE()l
extern _native64(0xF083835B70BA9BFE) void NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES()l
extern _native64(0x9D80CD1D0E6327DE) bool NETWORK_INVITE_GAMERS(any* p0, any p1, any* p2, any p3)l
extern _native64(0x4D86CD31E8976ECE) bool NETWORK_HAS_INVITED_GAMER(any* p0)l
extern _native64(0x71DC455F5CD1C2B1) bool NETWORK_HAS_MADE_INVITE_DECISION(any* gamerHandle)l
extern _native64(0x3855FB5EB2C5E8B2) int NETWORK_GET_INVITE_REPLY_STATUS(any p0)l
extern _native64(0x74881E6BCAE2327C) bool NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(any* p0)l
extern _native64(0x7206F674F2A3B1BB) bool NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(any* p0)l
extern _native64(0x66F010A4B031A331) void NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU(any* p0)l
extern _native64(0x44B37CDCAE765AAE) bool NETWORK_CHECK_DATA_MANAGER_SUCCEEDED_FOR_HANDLE(int p0, any* gamerHandle)l
extern _native64(0x4AD490AE1536933B) bool NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE(any p0, any* gamerHandle)l
extern _native64(0x0D77A82DC2D0DA59) void NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU(any* p0, any* p1)l
extern _native64(0xCBBD7C4991B64809) bool FILLOUT_PM_PLAYER_LIST(any* gamerHandle, any p1, any p2)l
extern _native64(0x716B6DB9D1886106) bool FILLOUT_PM_PLAYER_LIST_WITH_NAMES(any* p0, any* p1, any p2, any p3)l
extern _native64(0xE26CCFF8094D8C74) bool REFRESH_PLAYER_LIST_STATS(int p0)l
extern _native64(0x796A87B3B68D1F3D) bool NETWORK_SET_CURRENT_DATA_MANAGER_HANDLE(any* p0)l
extern _native64(0x2FC5650B0271CB57) bool NETWORK_IS_IN_PLATFORM_PARTY()l
extern _native64(0x01ABCE5E7CBDA196) int NETWORK_GET_PLATFORM_PARTY_MEMBER_COUNT()l
extern _native64(0x120364DE2845DAF8) int NETWORK_GET_PLATFORM_PARTY_MEMBERS(any* data, int dataSize)l
extern _native64(0xFD8B834A8BA05048) bool NETWORK_IS_IN_PLATFORM_PARTY_CHAT()l
extern _native64(0x8DE9945BCC9AEC52) bool NETWORK_IS_CHATTING_IN_PLATFORM_PARTY(any* gamerHandle)l
extern _native64(0x2BF66D2E7414F686) bool NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN()l
extern _native64(0x14922ED3E38761F0) bool NETWORK_IS_QUEUING_FOR_SESSION_JOIN()l
extern _native64(0x6CE50E47F5543D0C) void NETWORK_CLEAR_QUEUED_JOIN_REQUEST()l
extern _native64(0xFA2888E3833C8E96) void NETWORK_SEND_QUEUED_JOIN_REQUEST()l
extern _native64(0x25D990F8E0E3F13C) void NETWORK_REMOVE_ALL_QUEUED_JOIN_REQUESTS()l
extern _native64(0xF1B84178F8674195) void NETWORK_SEED_RANDOM_NUMBER_GENERATOR(int seed)l
extern _native64(0x599E4FA1F87EB5FF) int NETWORK_GET_RANDOM_INT()l
extern _native64(0xE30CF56F1EFA5F43) int NETWORK_GET_RANDOM_INT_RANGED(int rangeStart, int rangeEnd)l
extern _native64(0x04BD27B5ACB67067) float _NETWORK_GET_RANDOM_FLOAT_RANGED(float rangeStart, float rangeEnd)l
extern _native64(0x655B91F1495A9090) bool NETWORK_PLAYER_IS_CHEATER()l
extern _native64(0x172F75B6EE2233BA) int NETWORK_PLAYER_GET_CHEATER_REASON()l
extern _native64(0x19D8DA0E5A68045A) bool NETWORK_PLAYER_IS_BADSPORT()l
extern _native64(0x472841A026D26D8B) bool REMOTE_CHEATER_PLAYER_DETECTED(Player player, int a, int b)l
extern _native64(0xEC5E3AF5289DCA81) bool BAD_SPORT_PLAYER_LEFT_DETECTED(any* gamerHandle, int event, int amountReceived)l
extern _native64(0x7F562DBC212E81F9) void NETWORK_ADD_INVALID_OBJECT_MODEL(Hash modelHash)l
extern _native64(0x791EDB5803B2F468) void NETWORK_REMOVE_INVALID_OBJECT_MODEL(Hash modelHash)l
extern _native64(0x03B2F03A53D85E41) void NETWORK_CLEAR_INVALID_OBJECT_MODELS()l
extern _native64(0xE66C690248F11150) void NETWORK_APPLY_PED_SCAR_DATA(Ped ped, int p1)l
extern _native64(0x1CA59E306ECB80A5) void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(int maxNumMissionParticipants, bool p1, int instanceId)l
extern _native64(0xD1110739EEADB592) bool NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(any p0, bool p1, any p2)l
extern _native64(0x2910669969E9535E) bool NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT()l
extern _native64(0xA6C90FBC38E395EE) int NETWORK_GET_MAX_NUM_PARTICIPANTS()l
extern _native64(0x18D0456E86604654) int NETWORK_GET_NUM_PARTICIPANTS()l
extern _native64(0x57D158647A6BFABF) int NETWORK_GET_SCRIPT_STATUS()l
extern _native64(0x3E9B2F01C50DF595) void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(int* vars, int numVars, const char* debugName)l
extern _native64(0x3364AA97340CA215) void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(int* vars, int numVars, const char* debugName)l
extern _native64(0xEA8C0DDB10E2822A) void NETWORK_REGISTER_HIGH_FREQUENCY_HOST_BROADCAST_VARIABLES(any p0, any p1, any p2)l
extern _native64(0xD6D7478CA62B8D41) void NETWORK_REGISTER_HIGH_FREQUENCY_PLAYER_BROADCAST_VARIABLES(any p0, any p1, any p2)l
extern _native64(0x64F62AFB081E260D) void NETWORK_FINISH_BROADCASTING_DATA()l
extern _native64(0x5D10B3795F3FC886) bool NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA()l
extern _native64(0x24FB80D107371267) Player NETWORK_GET_PLAYER_INDEX(Player player)l
extern _native64(0x1B84DF6AF2A46938) int NETWORK_GET_PARTICIPANT_INDEX(int index)l
extern _native64(0x6C0E2E0125610278) Player NETWORK_GET_PLAYER_INDEX_FROM_PED(Ped ped)l
extern _native64(0xA4A79DD2D9600654) int NETWORK_GET_NUM_CONNECTED_PLAYERS()l
extern _native64(0x93DC1BE4E1ABE9D1) bool NETWORK_IS_PLAYER_CONNECTED(Player player)l
extern _native64(0xCF61D4B4702EE9EB) int NETWORK_GET_TOTAL_NUM_PLAYERS()l
extern _native64(0x6FF8FF40B6357D45) bool NETWORK_IS_PARTICIPANT_ACTIVE(int p0)l
extern _native64(0xB8DFD30D6973E135) bool NETWORK_IS_PLAYER_ACTIVE(Player player)l
extern _native64(0x3CA58F6CB7CBD784) bool NETWORK_IS_PLAYER_A_PARTICIPANT(Player player)l
extern _native64(0x83CD99A1E6061AB5) bool NETWORK_IS_HOST_OF_THIS_SCRIPT()l
extern _native64(0xC7B4D79B01FA7A5C) Player NETWORK_GET_HOST_OF_THIS_SCRIPT()l
extern _native64(0x1D6A14F1F9A736FC) Player NETWORK_GET_HOST_OF_SCRIPT(const char* scriptName, int instance_id, int position_hash)l
extern _native64(0x3B3D11CD9FFCDFC9) void NETWORK_SET_MISSION_FINISHED()l
extern _native64(0x9D40DF90FAD26098) bool NETWORK_IS_SCRIPT_ACTIVE(const char* scriptName, int instance_id, bool p2, int position_hash)l
extern _native64(0xDA7DE67F5FE5EE13) bool NETWORK_IS_SCRIPT_ACTIVE_BY_HASH(Hash scriptHash, int p1, bool p2, int p3)l
extern _native64(0x560B423D73015E77) bool NETWORK_IS_THREAD_A_NETWORK_SCRIPT(int threadId)l
extern _native64(0x3658E8CD94FC121A) int NETWORK_GET_NUM_SCRIPT_PARTICIPANTS(const char* scriptName, int instance_id, int position_hash)l
extern _native64(0x638A3A81733086DB) int NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT()l
extern _native64(0x257ED0FADF750BCF) Hash NETWORK_GET_POSITION_HASH_OF_THIS_SCRIPT()l
extern _native64(0x1AD5B71586B94820) bool NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(Player player, const char* script, int instance_id)l
extern _native64(0x2302C0264EA58D31) void NETWORK_PREVENT_SCRIPT_HOST_MIGRATION()l
extern _native64(0x741A3D8380319A81) void NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT()l
extern _native64(0x90986E8876CE0A83) Player PARTICIPANT_ID()l
extern _native64(0x57A3BDDAD8E5AA0A) int PARTICIPANT_ID_TO_INT()l
extern _native64(0x2DA41ED6E1FCD7A5) Player NETWORK_GET_KILLER_OF_PLAYER(Player player, Hash* weaponHash)l
extern _native64(0x7A1ADEEF01740A24) Player NETWORK_GET_DESTROYER_OF_NETWORK_ID(int netId, Hash* weaponHash)l
extern _native64(0xC434133D9BA52777) Player NETWORK_GET_DESTROYER_OF_ENTITY(Entity entity, Hash* weaponHash)l
extern _native64(0x83660B734994124D) bool NETWORK_GET_ASSISTED_KILL_OF_ENTITY(Player player, Entity entity, int* p2)l
extern _native64(0x4CACA84440FA26F6) bool NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY(Player player, Entity entity, int* p2)l
extern _native64(0x42B2DAA6B596F5F8) Entity NETWORK_GET_ENTITY_KILLER_OF_PLAYER(Player player, Hash* weaponHash)l
extern _native64(0x2C863ACDCD12B3DB) void NETWORK_SET_CURRENT_PUBLIC_CONTENT_ID(const char* missionId)l
extern _native64(0x3DAD00265FBF356B) void NETWORK_SET_CURRENT_CHAT_OPTION(int newChatOption)l
extern _native64(0xAA6D5451DC3448B6) void NETWORK_SET_CURRENT_SPAWN_LOCATION_OPTION(Hash mpSettingSpawn)l
extern _native64(0x8C70252FC40F320B) void NETWORK_SET_VEHICLE_DRIVEN_IN_TEST_DRIVE(bool toggle)l
extern _native64(0xA0CE91E47531D3BB) void NETWORK_SET_VEHICLE_DRIVEN_LOCATION(Hash location)l
extern _native64(0xEA23C49EAA83ACFB) void NETWORK_RESURRECT_LOCAL_PLAYER(float x, float y, float z, float heading, bool p4, bool changetime, bool p6, int p7, int p8)l
extern _native64(0x2D95C7E2D7E07307) void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(int time)l
extern _native64(0x8A8694B48715B000) bool NETWORK_IS_LOCAL_PLAYER_INVINCIBLE()l
extern _native64(0x9DD368BF06983221) void NETWORK_DISABLE_INVINCIBLE_FLASHING(Player player, bool toggle)l
extern _native64(0xF0BC9BCD24A511D5) void NETWORK_PATCH_POST_CUTSCENE_HS4F_TUN_ENT(Ped ped)l
extern _native64(0x524FF0AEFF9C3973) void NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT(bool toggle)l
extern _native64(0xB07D3185E11657A5) bool NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD(Entity entity)l
extern _native64(0xA11700682F3AD45C) int NETWORK_GET_NETWORK_ID_FROM_ENTITY(Entity entity)l
extern _native64(0xCE4E5D9B0A4FF560) Entity NETWORK_GET_ENTITY_FROM_NETWORK_ID(int netId)l
extern _native64(0xC7827959479DCC78) bool NETWORK_GET_ENTITY_IS_NETWORKED(Entity entity)l
extern _native64(0x0991549DE4D64762) bool NETWORK_GET_ENTITY_IS_LOCAL(Entity entity)l
extern _native64(0x06FAACD625D80CAA) void NETWORK_REGISTER_ENTITY_AS_NETWORKED(Entity entity)l
extern _native64(0x7368E683BB9038D6) void NETWORK_UNREGISTER_NETWORKED_ENTITY(Entity entity)l
extern _native64(0x38CE16C96BD11344) bool NETWORK_DOES_NETWORK_ID_EXIST(int netId)l
extern _native64(0x18A47D074708FD68) bool NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(int netId)l
extern _native64(0xA670B3662FAFFBD0) bool NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(int netId)l
extern _native64(0x4D36070FE0215186) bool NETWORK_HAS_CONTROL_OF_NETWORK_ID(int netId)l
extern _native64(0x7242F8B741CE1086) bool NETWORK_IS_NETWORK_ID_REMOTELY_CONTROLLED(int netId)l
extern _native64(0xB69317BF5E782347) bool NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity entity)l
extern _native64(0x870DDFD5A4A796E4) bool NETWORK_REQUEST_CONTROL_OF_DOOR(int doorID)l
extern _native64(0x01BF60A500E28887) bool NETWORK_HAS_CONTROL_OF_ENTITY(Entity entity)l
extern _native64(0x5BC9495F0B3B6FA6) bool NETWORK_HAS_CONTROL_OF_PICKUP(Pickup pickup)l
extern _native64(0xCB3C68ADB06195DF) bool NETWORK_HAS_CONTROL_OF_DOOR(Hash doorHash)l
extern _native64(0xC01E93FAC20C3346) bool NETWORK_IS_DOOR_NETWORKED(Hash doorHash)l
extern _native64(0xB4C94523F023419C) int VEH_TO_NET(Vehicle vehicle)l
extern _native64(0x0EDEC3C276198689) int PED_TO_NET(Ped ped)l
extern _native64(0x99BFDC94A603E541) int OBJ_TO_NET(Object object)l
extern _native64(0x367B936610BA360C) Vehicle NET_TO_VEH(int netHandle)l
extern _native64(0xBDCD95FC216A8B3E) Ped NET_TO_PED(int netHandle)l
extern _native64(0xD8515F5FEA14CB3F) Object NET_TO_OBJ(int netHandle)l
extern _native64(0xBFFEAB45A9A9094A) Entity NET_TO_ENT(int netHandle)l
extern _native64(0xE86051786B66CD8E) void NETWORK_GET_LOCAL_HANDLE(any* gamerHandle, int gamerHandleSize)l
extern _native64(0xDCD51DD8F87AEC5C) void NETWORK_HANDLE_FROM_USER_ID(const char* userId, any* gamerHandle, int gamerHandleSize)l
extern _native64(0xA0FD21BED61E5C4C) void NETWORK_HANDLE_FROM_MEMBER_ID(const char* memberId, any* gamerHandle, int gamerHandleSize)l
extern _native64(0x388EB2B86C73B6B3) void NETWORK_HANDLE_FROM_PLAYER(Player player, any* gamerHandle, int gamerHandleSize)l
extern _native64(0xBC1D768F2F5D6C05) Hash NETWORK_HASH_FROM_PLAYER_HANDLE(Player player)l
extern _native64(0x58575AC3CF2CA8EC) Hash NETWORK_HASH_FROM_GAMER_HANDLE(any* gamerHandle)l
extern _native64(0xD45CB817D7E177D2) void NETWORK_HANDLE_FROM_FRIEND(int friendIndex, any* gamerHandle, int gamerHandleSize)l
extern _native64(0x9F0C0A981D73FA56) bool NETWORK_GAMERTAG_FROM_HANDLE_START(any* gamerHandle)l
extern _native64(0xB071E27958EF4CF0) bool NETWORK_GAMERTAG_FROM_HANDLE_PENDING()l
extern _native64(0xFD00798DBA7523DD) bool NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED()l
extern _native64(0x426141162EBE5CDB) const char* NETWORK_GET_GAMERTAG_FROM_HANDLE(any* gamerHandle)l
extern _native64(0xD66C9E72B3CC4982) int NETWORK_DISPLAYNAMES_FROM_HANDLES_START(any* p0, any p1)l
extern _native64(0x58CC181719256197) int NETWORK_GET_DISPLAYNAMES_FROM_HANDLES(any p0, any p1, any p2)l
extern _native64(0x57DBA049E110F217) bool NETWORK_ARE_HANDLES_THE_SAME(any* gamerHandle1, any* gamerHandle2)l
extern _native64(0x6F79B93B0A8E4133) bool NETWORK_IS_HANDLE_VALID(any* gamerHandle, int gamerHandleSize)l
extern _native64(0xCE5F689CF5A0A49D) Player NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(any* gamerHandle)l
extern _native64(0xC82630132081BB6F) const char* NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(any* gamerHandle)l
extern _native64(0x0F10B05DDF8D16E9) bool NETWORK_IS_GAMER_IN_MY_SESSION(any* gamerHandle)l
extern _native64(0x859ED1CEA343FCA8) void NETWORK_SHOW_PROFILE_UI(any* gamerHandle)l
extern _native64(0x7718D2E2060837D2) const char* NETWORK_PLAYER_GET_NAME(Player player)l
extern _native64(0x4927FC39CD0869A0) const char* NETWORK_PLAYER_GET_USERID(Player player, int* userID)l
extern _native64(0x544ABDDA3B409B6D) bool NETWORK_PLAYER_IS_ROCKSTAR_DEV(Player player)l
extern _native64(0x565E430DB3B05BEC) bool NETWORK_PLAYER_INDEX_IS_CHEATER(Player player)l
extern _native64(0x815F18AD865F057F) int NETWORK_ENTITY_GET_OBJECT_ID(Entity entity)l
extern _native64(0x37D5F739FD494675) Entity NETWORK_GET_ENTITY_FROM_OBJECT_ID(any p0)l
extern _native64(0x7E58745504313A2E) bool NETWORK_IS_INACTIVE_PROFILE(any* p0)l
extern _native64(0xAFEBB0D5D8F687D2) int NETWORK_GET_MAX_FRIENDS()l
extern _native64(0x203F1CFD823B27A4) int NETWORK_GET_FRIEND_COUNT()l
extern _native64(0xE11EBBB2A783FE8B) const char* NETWORK_GET_FRIEND_NAME(int friendIndex)l
extern _native64(0x4164F227D052E293) const char* NETWORK_GET_FRIEND_DISPLAY_NAME(int friendIndex)l
extern _native64(0x425A44533437B64D) bool NETWORK_IS_FRIEND_ONLINE(const char* name)l
extern _native64(0x87EB7A3FFCB314DB) bool NETWORK_IS_FRIEND_HANDLE_ONLINE(any* gamerHandle)l
extern _native64(0x2EA9A3BEDF3F17B8) bool NETWORK_IS_FRIEND_IN_SAME_TITLE(const char* friendName)l
extern _native64(0x57005C18827F3A28) bool NETWORK_IS_FRIEND_IN_MULTIPLAYER(const char* friendName)l
extern _native64(0x1A24A179F9B31654) bool NETWORK_IS_FRIEND(any* gamerHandle)l
extern _native64(0x0BE73DA6984A6E33) bool NETWORK_IS_PENDING_FRIEND(any p0)l
extern _native64(0x6EA101606F6E4D81) bool NETWORK_IS_ADDING_FRIEND()l
extern _native64(0x8E02D73914064223) bool NETWORK_ADD_FRIEND(any* gamerHandle, const char* message)l
extern _native64(0xBAD8F2A42B844821) bool NETWORK_IS_FRIEND_INDEX_ONLINE(int friendIndex)l
extern _native64(0x1B857666604B1A74) void NETWORK_SET_PLAYER_IS_PASSIVE(bool toggle)l
extern _native64(0x82377B65E943F72D) bool NETWORK_GET_PLAYER_OWNS_WAYPOINT(Player player)l
extern _native64(0xC927EC229934AF60) bool NETWORK_CAN_SET_WAYPOINT()l
extern _native64(0x4C2A9FDC22377075) void NETWORK_IGNORE_REMOTE_WAYPOINTS()l
extern _native64(0xAD4326FCA30D62F8) bool NETWORK_IS_PLAYER_ON_BLOCKLIST(any* gamerHandle)l
extern _native64(0xB309EBEA797E001F) bool NETWORK_SET_SCRIPT_AUTOMUTED(any p0)l
extern _native64(0x26F07DD83A5F7F98) bool NETWORK_HAS_AUTOMUTE_OVERRIDE()l
extern _native64(0xE870F9F1F7B4F1FA) bool NETWORK_HAS_HEADSET()l
extern _native64(0x7D395EA61622E116) void NETWORK_SET_LOOK_AT_TALKERS(bool p0)l
extern _native64(0xC0D2AF00BCC234CA) bool NETWORK_IS_PUSH_TO_TALK_ACTIVE()l
extern _native64(0xF2FD55CB574BCC55) bool NETWORK_GAMER_HAS_HEADSET(any* gamerHandle)l
extern _native64(0x71C33B22606CD88A) bool NETWORK_IS_GAMER_TALKING(any* gamerHandle)l
extern _native64(0x559EBF901A8C68E0) bool NETWORK_PERMISSIONS_HAS_GAMER_RECORD(any* gamerHandle)l
extern _native64(0x8F5D1AD832AEB06C) bool NETWORK_CAN_COMMUNICATE_WITH_GAMER(any* gamerHandle)l
extern _native64(0xA150A4F065806B1F) bool NETWORK_CAN_TEXT_CHAT_WITH_GAMER(any* gamerHandle)l
extern _native64(0xCE60DE011B6C7978) bool NETWORK_IS_GAMER_MUTED_BY_ME(any* gamerHandle)l
extern _native64(0xDF02A2C93F1F26DA) bool NETWORK_AM_I_MUTED_BY_GAMER(any* gamerHandle)l
extern _native64(0xE944C4F5AF1B5883) bool NETWORK_IS_GAMER_BLOCKED_BY_ME(any* gamerHandle)l
extern _native64(0x15337C7C268A27B2) bool NETWORK_AM_I_BLOCKED_BY_GAMER(any* gamerHandle)l
extern _native64(0xB57A49545BA53CE7) bool NETWORK_CAN_VIEW_GAMER_USER_CONTENT(any* gamerHandle)l
extern _native64(0xCCA4318E1AB03F1F) bool NETWORK_HAS_VIEW_GAMER_USER_CONTENT_RESULT(any* gamerHandle)l
extern _native64(0x07DD29D5E22763F1) bool NETWORK_CAN_PLAY_MULTIPLAYER_WITH_GAMER(any* gamerHandle)l
extern _native64(0x135F9B7B7ADD2185) bool NETWORK_CAN_GAMER_PLAY_MULTIPLAYER_WITH_ME(any* gamerHandle)l
extern _native64(0x021ABCBD98EC4320) bool NETWORK_CAN_SEND_LOCAL_INVITE(any* gamerHandle)l
extern _native64(0x421E34C55F125964) bool NETWORK_CAN_RECEIVE_LOCAL_INVITE(any* gamerHandle)l
extern _native64(0x031E11F3D447647E) bool NETWORK_IS_PLAYER_TALKING(Player player)l
extern _native64(0x3FB99A8B08D18FD6) bool NETWORK_PLAYER_HAS_HEADSET(Player player)l
extern _native64(0x8C71288AE68EDE39) bool NETWORK_IS_PLAYER_MUTED_BY_ME(Player player)l
extern _native64(0x9D6981DFC91A8604) bool NETWORK_AM_I_MUTED_BY_PLAYER(Player player)l
extern _native64(0x57AF1F8E27483721) bool NETWORK_IS_PLAYER_BLOCKED_BY_ME(Player player)l
extern _native64(0x87F395D957D4353D) bool NETWORK_AM_I_BLOCKED_BY_PLAYER(Player player)l
extern _native64(0x21A1684A25C2867F) float NETWORK_GET_PLAYER_LOUDNESS(Player player)l
extern _native64(0xCBF12D65F95AD686) void NETWORK_SET_TALKER_PROXIMITY(float value)l
extern _native64(0x84F0F13120B4E098) float NETWORK_GET_TALKER_PROXIMITY()l
extern _native64(0xBABEC9E69A91C57B) void NETWORK_SET_VOICE_ACTIVE(bool toggle)l
extern _native64(0xCFEB46DCD7D8D5EB) void NETWORK_REMAIN_IN_GAME_CHAT(bool p0)l
extern _native64(0xAF66059A131AA269) void NETWORK_OVERRIDE_TRANSITION_CHAT(bool p0)l
extern _native64(0xD5B4883AC32F24C3) void NETWORK_SET_TEAM_ONLY_CHAT(bool toggle)l
extern _native64(0x265559DA40B3F327) void NETWORK_SET_SCRIPT_CONTROLLING_TEAMS(any p0)l
extern _native64(0x4348BFDA56023A2F) bool NETWORK_SET_SAME_TEAM_AS_LOCAL_PLAYER(any p0, any p1)l
extern _native64(0x6F697A66CE78674E) void NETWORK_OVERRIDE_TEAM_RESTRICTIONS(int team, bool toggle)l
extern _native64(0x70DA3BF8DACD3210) void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(bool toggle)l
extern _native64(0x3C5C1E2C2FF814B1) void NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT(bool toggle)l
extern _native64(0x9D7AFCBF21C51712) void NETWORK_SET_PROXIMITY_AFFECTS_TEAM(bool toggle)l
extern _native64(0xF46A1E03E8755980) void NETWORK_SET_NO_SPECTATOR_CHAT(bool toggle)l
extern _native64(0x6A5D89D7769A40D8) void NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM(bool toggle)l
extern _native64(0x3039AE5AD2C9C0C4) void NETWORK_OVERRIDE_CHAT_RESTRICTIONS(Player player, bool toggle)l
extern _native64(0x97DD4C5944CC2E6A) void NETWORK_OVERRIDE_SEND_RESTRICTIONS(Player player, bool toggle)l
extern _native64(0x57B192B4D4AD23D5) void NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(bool toggle)l
extern _native64(0xDDF73E2B1FEC5AB4) void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(Player player, bool toggle)l
extern _native64(0x0FF2862B61A58AF9) void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(bool toggle)l
extern _native64(0xEF6212C2EFEF1A23) void NETWORK_SET_VOICE_CHANNEL(int channel)l
extern _native64(0xE036A705F989E049) void NETWORK_CLEAR_VOICE_CHANNEL()l
extern _native64(0xDBD2056652689917) void NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE(float x, float y, float z)l
extern _native64(0xF03755696450470C) void NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE()l
extern _native64(0x5E3AA4CA2B6FB0EE) void NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION(Player player)l
extern _native64(0xCA575C391FEA25CC) void NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION(Player player)l
extern _native64(0xADB57E5B663CCA8B) void NETWORK_GET_MUTE_COUNT_FOR_PLAYER(Player p0, float* p1, float* p2)l
extern _native64(0x8EF52ACAECC51D9C) void NETWORK_SET_SPECTATOR_TO_NON_SPECTATOR_TEXT_CHAT(bool toggle)l
extern _native64(0x5FCF4D7069B09026) bool NETWORK_TEXT_CHAT_IS_TYPING()l
extern _native64(0x593850C16A36B692) void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME()l
extern _native64(0x9ECA15ADFE141431) bool SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE()l
extern _native64(0xF808475FA571D823) void NETWORK_SET_FRIENDLY_FIRE_OPTION(bool toggle)l
extern _native64(0x1DCCACDCFC569362) void NETWORK_SET_RICH_PRESENCE(int p0, int p1, any p2, any p3)l
extern _native64(0x3E200C2BCF4164EB) void NETWORK_SET_RICH_PRESENCE_STRING(int p0, const char* textLabel)l
extern _native64(0x5ED0356A0CE3A34F) int NETWORK_GET_TIMEOUT_TIME()l
extern _native64(0x9769F811D1785B03) void NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP(Player player, float x, float y, float z, bool p4, bool p5)l
extern _native64(0xBF22E0F32968E967) void NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE(Player player, bool p1)l
extern _native64(0x715135F4B82AC90D) void REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY(Entity entity, Ped ped)l
extern _native64(0x17C9E241111A674D) void NETWORK_KEEP_ENTITY_COLLISION_DISABLED_AFTER_ANIM_SCENE(any p0, any p1)l
extern _native64(0x2E4C123D1C8A710E) bool NETWORK_IS_ANY_PLAYER_NEAR(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x579CCED0265D4896) bool NETWORK_CLAN_SERVICE_IS_VALID()l
extern _native64(0xB124B57F571D8F18) bool NETWORK_CLAN_PLAYER_IS_ACTIVE(any* gamerHandle)l
extern _native64(0xEEE6EACBE8874FBA) bool NETWORK_CLAN_PLAYER_GET_DESC(any* clanDesc, int bufferSize, any* gamerHandle)l
extern _native64(0x7543BB439F63792B) bool NETWORK_CLAN_IS_ROCKSTAR_CLAN(any* clanDesc, int bufferSize)l
extern _native64(0xF45352426FF3A4F0) void NETWORK_CLAN_GET_UI_FORMATTED_TAG(any* clanDesc, int bufferSize, char* formattedTag)l
extern _native64(0x1F471B79ACC90BEF) int NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT()l
extern _native64(0x48DE78AF2C8885B8) bool NETWORK_CLAN_GET_MEMBERSHIP_DESC(any* memberDesc, int p1)l
extern _native64(0xA989044E70010ABE) bool NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(any* gamerHandle)l
extern _native64(0x5B9E023DC6EBEDC0) bool NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(any* p0)l
extern _native64(0xB3F64A6A91432477) bool NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING()l
extern _native64(0xBB6E6FEE99D866B2) bool NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE(int* p0)l
extern _native64(0xAAB11F6C4ADBC2C1) int NETWORK_CLAN_GET_MEMBERSHIP_COUNT(int* p0)l
extern _native64(0x48A59CF88D43DF0E) bool NETWORK_CLAN_GET_MEMBERSHIP_VALID(int* p0, any p1)l
extern _native64(0xC8BC2011F67B3411) bool NETWORK_CLAN_GET_MEMBERSHIP(int* p0, any* clanMembership, int p2)l
extern _native64(0x9FAAA4F4FC71F87F) bool NETWORK_CLAN_JOIN(int clanDesc)l
extern _native64(0x729E3401F0430686) bool NETWORK_CLAN_CREWINFO_GET_STRING_VALUE(const char* animDict, const char* animName)l
extern _native64(0x2B51EDBEFC301339) bool NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE(int p0, const char* p1)l
extern _native64(0xC32EA7A2F6CA7557) bool NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED()l
extern _native64(0x5835D9CD92E83184) bool NETWORK_CLAN_GET_EMBLEM_TXD_NAME(any* netHandle, char* txdName)l
extern _native64(0x13518FF1C6B28938) bool NETWORK_CLAN_REQUEST_EMBLEM(any p0)l
extern _native64(0xA134777FF7F33331) bool NETWORK_CLAN_IS_EMBLEM_READY(any p0, any* p1)l
extern _native64(0x113E6E3E50E286B0) void NETWORK_CLAN_RELEASE_EMBLEM(any p0)l
extern _native64(0x9AA46BADAD0E27ED) bool NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR()l
extern _native64(0x042E4B70B93E6054) void NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL()l
extern _native64(0xCE86D8191B762107) bool NETWORK_GET_PRIMARY_CLAN_DATA_START(any* p0, any p1)l
extern _native64(0xB5074DB804E28CE7) bool NETWORK_GET_PRIMARY_CLAN_DATA_PENDING()l
extern _native64(0x5B4F04F19376A0BA) bool NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS()l
extern _native64(0xC080FF658B2E41DA) bool NETWORK_GET_PRIMARY_CLAN_DATA_NEW(any* p0, any* p1)l
extern _native64(0x299EEB23175895FC) void SET_NETWORK_ID_CAN_MIGRATE(int netId, bool toggle)l
extern _native64(0xE05E81A888FA63C8) void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int netId, bool toggle)l
extern _native64(0xA8A024587329F36A) void SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER(int netId, Player player, bool toggle)l
extern _native64(0x9D724B400A7E8FFC) void SET_NETWORK_ID_CAN_BE_REASSIGNED(int netId, bool toggle)l
extern _native64(0xD830567D88A1E873) void NETWORK_SET_ENTITY_CAN_BLEND(Entity entity, bool toggle)l
extern _native64(0x0379DAF89BA09AA5) void NETWORK_SET_OBJECT_CAN_BLEND_WHEN_FIXED(Object object, bool toggle)l
extern _native64(0xF1CA12B18AEF5298) void NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(Entity entity, bool toggle)l
extern _native64(0xA6928482543022B4) void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(int netId, bool p1, bool p2)l
extern _native64(0x32EBD154CB6B8B99) void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_HACK(int netId, bool p1, bool p2)l
extern _native64(0x76B3F29D3F967692) void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_REMAIN_HACK(any p0, any p1)l
extern _native64(0xAAA553E7DD28A457) void SET_NETWORK_CUTSCENE_ENTITIES(bool toggle)l
extern _native64(0x66D6A5E9C511214A) bool ARE_CUTSCENE_ENTITIES_NETWORKED()l
extern _native64(0x3FA36981311FA4FF) void SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL(int netId, bool state)l
extern _native64(0xA1607996431332DF) bool IS_NETWORK_ID_OWNED_BY_PARTICIPANT(int netId)l
extern _native64(0x96320E6549DAE7B4) void SET_REMOTE_PLAYER_VISIBLE_IN_CUTSCENE(Player player, bool locallyVisible)l
extern _native64(0xD1065D68947E7B6E) void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(bool p0, bool p1)l
extern _native64(0xE5F773C1A1D9D168) void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(bool bIncludePlayersVehicle)l
extern _native64(0x7619364C82D3BF14) void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(bool bIncludePlayersVehicle)l
extern _native64(0x12B37D54667DB0B8) void SET_PLAYER_INVISIBLE_LOCALLY(Player player, bool bIncludePlayersVehicle)l
extern _native64(0xFAA10F1FAFB11AF2) void SET_PLAYER_VISIBLE_LOCALLY(Player player, bool bIncludePlayersVehicle)l
extern _native64(0x416DBD4CD6ED8DD2) void FADE_OUT_LOCAL_PLAYER(bool p0)l
extern _native64(0xDE564951F95E09ED) void NETWORK_FADE_OUT_ENTITY(Entity entity, bool normal, bool slow)l
extern _native64(0x1F4ED342ACEFE62D) void NETWORK_FADE_IN_ENTITY(Entity entity, bool state, any p2)l
extern _native64(0x631DC5DFF4B110E3) bool NETWORK_IS_PLAYER_FADING(Player player)l
extern _native64(0x422F32CC7E56ABAD) bool NETWORK_IS_ENTITY_FADING(Entity entity)l
extern _native64(0xE73092F4157CD126) bool IS_PLAYER_IN_CUTSCENE(Player player)l
extern _native64(0xE0031D3C8F36AB82) void SET_ENTITY_VISIBLE_IN_CUTSCENE(any p0, bool p1, bool p2)l
extern _native64(0xE135A9FF3F5D05D8) void SET_ENTITY_LOCALLY_INVISIBLE(Entity entity)l
extern _native64(0x241E289B5C059EDC) void SET_ENTITY_LOCALLY_VISIBLE(Entity entity)l
extern _native64(0x6E192E33AD436366) bool IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(int netID)l
extern _native64(0xD45B1FFCCD52FF19) void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(int netID, bool toggle)l
extern _native64(0xB2092A1EAA7FD45F) bool IS_DAMAGE_TRACKER_ACTIVE_ON_PLAYER(Player player)l
extern _native64(0xBEC0816FF5ACBCDA) void ACTIVATE_DAMAGE_TRACKER_ON_PLAYER(Player player, bool toggle)l
extern _native64(0xD82CF8E64C8729D8) bool IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(float p0, float p1, float p2, float p3)l
extern _native64(0xDC3A310219E5DA62) bool IS_SPHERE_VISIBLE_TO_PLAYER(any p0, float p1, float p2, float p3, float p4)l
extern _native64(0x4E5C93BD0C32FBF8) void RESERVE_NETWORK_MISSION_OBJECTS(int amount)l
extern _native64(0xB60FEBA45333D36F) void RESERVE_NETWORK_MISSION_PEDS(int amount)l
extern _native64(0x76B02E21ED27A469) void RESERVE_NETWORK_MISSION_VEHICLES(int amount)l
extern _native64(0x797F9C5E661D920E) void RESERVE_LOCAL_NETWORK_MISSION_OBJECTS(int amount)l
extern _native64(0x2C8DF5D129595281) void RESERVE_LOCAL_NETWORK_MISSION_PEDS(int amount)l
extern _native64(0x42613035157E4208) void RESERVE_LOCAL_NETWORK_MISSION_VEHICLES(int amount)l
extern _native64(0x800DD4721A8B008B) bool CAN_REGISTER_MISSION_OBJECTS(int amount)l
extern _native64(0xBCBF4FEF9FA5D781) bool CAN_REGISTER_MISSION_PEDS(int amount)l
extern _native64(0x7277F1F2E085EE74) bool CAN_REGISTER_MISSION_VEHICLES(int amount)l
extern _native64(0x0A49D1CB6E34AF72) bool CAN_REGISTER_MISSION_PICKUPS(int amount)l
extern _native64(0xE16AA70CE9BEEDC3) bool CAN_REGISTER_MISSION_DOORS(any p0)l
extern _native64(0x69778E7564BADE6D) bool CAN_REGISTER_MISSION_ENTITIES(int ped_amt, int vehicle_amt, int object_amt, int pickup_amt)l
extern _native64(0xAA81B5F10BC43AC2) int GET_NUM_RESERVED_MISSION_OBJECTS(bool p0, any p1)l
extern _native64(0x1F13D5AE5CB17E17) int GET_NUM_RESERVED_MISSION_PEDS(bool p0, any p1)l
extern _native64(0xCF3A965906452031) int GET_NUM_RESERVED_MISSION_VEHICLES(bool p0, any p1)l
extern _native64(0x12B6281B6C6706C0) int GET_NUM_CREATED_MISSION_OBJECTS(bool p0)l
extern _native64(0xCB215C4B56A7FAE7) int GET_NUM_CREATED_MISSION_PEDS(bool p0)l
extern _native64(0x0CD9AB83489430EA) int GET_NUM_CREATED_MISSION_VEHICLES(bool p0)l
extern _native64(0xE42D626EEC94E5D9) void GET_RESERVED_MISSION_ENTITIES_IN_AREA(float x, float y, float z, any p3, any* out1, any* out2, any* out3)l
extern _native64(0xC7BE335216B5EC7C) int GET_MAX_NUM_NETWORK_OBJECTS()l
extern _native64(0x0C1F7D49C39D2289) int GET_MAX_NUM_NETWORK_PEDS()l
extern _native64(0x0AFCE529F69B21FF) int GET_MAX_NUM_NETWORK_VEHICLES()l
extern _native64(0xA72835064DD63E4C) int GET_MAX_NUM_NETWORK_PICKUPS()l
extern _native64(0xBA7F0B77D80A4EB7) void NETWORK_SET_OBJECT_SCOPE_DISTANCE(Object object, float range)l
extern _native64(0x0F1A4B45B7693B95) void NETWORK_ALLOW_CLONING_WHILE_IN_TUTORIAL(any p0, any p1)l
extern _native64(0xC6FCEE21C6FCEE21) void NETWORK_SET_TASK_CUTSCENE_INSCOPE_MULTIPLER(any p0)l
extern _native64(0x7A5487FE9FAA6B48) int GET_NETWORK_TIME()l
extern _native64(0x89023FBBF9200E9F) int GET_NETWORK_TIME_ACCURATE()l
extern _native64(0x46718ACEEDEAFC84) bool HAS_NETWORK_TIME_STARTED()l
extern _native64(0x017008CCDAD48503) int GET_TIME_OFFSET(int timeA, int timeB)l
extern _native64(0xCB2CF5148012C8D0) bool IS_TIME_LESS_THAN(int timeA, int timeB)l
extern _native64(0xDE350F8651E4346C) bool IS_TIME_MORE_THAN(int timeA, int timeB)l
extern _native64(0xF5BC95857BD6D512) bool IS_TIME_EQUAL_TO(int timeA, int timeB)l
extern _native64(0xA2C6FC031D46FFF0) int GET_TIME_DIFFERENCE(int timeA, int timeB)l
extern _native64(0x9E23B1777A927DAD) const char* GET_TIME_AS_STRING(int time)l
extern _native64(0xF12E6CD06C73D69E) const char* GET_CLOUD_TIME_AS_STRING()l
extern _native64(0x9A73240B49945C76) int GET_CLOUD_TIME_AS_INT()l
extern _native64(0xAC97AF97FA68E5D5) void CONVERT_POSIX_TIME(int posixTime, any* timeStructure)l
extern _native64(0x423DE3854BB50894) void NETWORK_SET_IN_SPECTATOR_MODE(bool toggle, Ped playerPed)l
extern _native64(0x419594E137637120) void NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED(bool toggle, Ped playerPed, bool p2)l
extern _native64(0xFC18DB55AE19E046) void NETWORK_SET_IN_FREE_CAM_MODE(bool toggle)l
extern _native64(0x5C707A667DF8B9FA) void NETWORK_SET_ANTAGONISTIC_TO_PLAYER(bool toggle, Player player)l
extern _native64(0x048746E388762E11) bool NETWORK_IS_IN_SPECTATOR_MODE()l
extern _native64(0x9CA5DE655269FEC4) void NETWORK_SET_IN_MP_CUTSCENE(bool p0, bool p1)l
extern _native64(0x6CC27C9FA2040220) bool NETWORK_IS_IN_MP_CUTSCENE()l
extern _native64(0x63F9EE203C3619F2) bool NETWORK_IS_PLAYER_IN_MP_CUTSCENE(Player player)l
extern _native64(0xFAC18E7356BD3210) void NETWORK_HIDE_PROJECTILE_IN_CUTSCENE()l
extern _native64(0xEC51713AB6EC36E8) void SET_NETWORK_VEHICLE_RESPOT_TIMER(int netId, int time, any p2, any p3)l
extern _native64(0xDD7CEF5B3A4DA8A6) bool IS_NETWORK_VEHICLE_RUNNING_RESPOT_TIMER(int networkID)l
extern _native64(0x6274C4712850841E) void SET_NETWORK_VEHICLE_AS_GHOST(Vehicle vehicle, bool toggle)l
extern _native64(0xA2A707979FE754DC) void SET_NETWORK_VEHICLE_MAX_POSITION_DELTA_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native64(0x838DA0936A24ED4D) void SET_NETWORK_ENABLE_HIGH_SPEED_EDGE_FALL_DETECTION(Vehicle vehicle, bool toggle)l
extern _native64(0x5FFE9B4144F9712F) void SET_LOCAL_PLAYER_AS_GHOST(bool toggle, bool p1)l
extern _native64(0x21D04D7BC538C146) bool IS_ENTITY_A_GHOST(Entity entity)l
extern _native64(0x13F1FCB111B820B0) void SET_NON_PARTICIPANTS_OF_THIS_SCRIPT_AS_GHOSTS(bool p0)l
extern _native64(0xA7C511FA1C5BDA38) void SET_REMOTE_PLAYER_AS_GHOST(Player player, bool p1)l
extern _native64(0x658500AE6D723A7E) void SET_GHOST_ALPHA(int alpha)l
extern _native64(0x17330EBF2F2124A8) void RESET_GHOST_ALPHA()l
extern _native64(0x4BA166079D658ED4) void SET_ENTITY_GHOSTED_FOR_GHOST_PLAYERS(Entity entity, bool toggle)l
extern _native64(0xD7B6C73CAD419BCF) void SET_INVERT_GHOSTING(bool p0)l
extern _native64(0x7EF7649B64D7FF10) bool IS_ENTITY_IN_GHOST_COLLISION(Entity entity)l
extern _native64(0x77758139EC9B66C7) void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(bool toggle)l
extern _native64(0x7CD6BC4C2BBDD526) int NETWORK_CREATE_SYNCHRONISED_SCENE(float x, float y, float z, float xRot, float yRot, float zRot, int rotationOrder, bool useOcclusionPortal, bool looped, float p9, float animTime, float p11)l
extern _native64(0x742A637471BCECD9) void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Ped ped, int netScene, const char* animDict, const char* animnName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, any p9)l
extern _native64(0xA5EAFE473E45C442) void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_WITH_IK(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9)l
extern _native64(0xF2404D68CBC855FA) void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag)l
extern _native64(0x45F35C0EDC33B03B) void NETWORK_ADD_MAP_ENTITY_TO_SYNCHRONISED_SCENE(int netScene, Hash modelHash, float x, float y, float z, float p5, const char* p6, float p7, float p8, int flags)l
extern _native64(0xCF8BD3B0BD6D42D7) void NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA(int netScene, const char* animDict, const char* animName)l
extern _native64(0x478DCBD2A98B705A) void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(int netScene, Entity entity, int bone)l
extern _native64(0x9A1B3FCDB36C8697) void NETWORK_START_SYNCHRONISED_SCENE(int netScene)l
extern _native64(0xC254481A4574CB2F) void NETWORK_STOP_SYNCHRONISED_SCENE(int netScene)l
extern _native64(0x02C40BF885C567B6) int NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID(int netId)l
extern _native64(0xC9B43A33D09CADA7) void NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA(int netScene)l
extern _native64(0x144DA052257AE7D8) void NETWORK_ALLOW_REMOTE_SYNCED_SCENE_LOCAL_PLAYER_REQUESTS(any p0)l
extern _native64(0xFB1F9381E80FA13F) bool NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS(int p0, any p1)l
extern _native64(0x5A6FFA2433E2F14C) bool NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER(Player player, float x, float y, float z, float radius, float p5, float p6, float p7, int flags)l
extern _native64(0x4BA92A18502BCA61) bool NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER(Player player, float x1, float y1, float z1, float x2, float y2, float z2, float width, float p8, float p9, float p10, int flags)l
extern _native64(0x3C891A251567DFCE) int NETWORK_QUERY_RESPAWN_RESULTS(any* p0)l
extern _native64(0xFB8F2A6F3DF08CBE) void NETWORK_CANCEL_RESPAWN_SEARCH()l
extern _native64(0x371EA43692861CF1) void NETWORK_GET_RESPAWN_RESULT(int randomInt, vector3* coordinates, float* heading)l
extern _native64(0x6C34F1208B8923FD) int NETWORK_GET_RESPAWN_RESULT_FLAGS(int p0)l
extern _native64(0x17E0198B3882C2CB) void NETWORK_START_SOLO_TUTORIAL_SESSION()l
extern _native64(0xFB680D403909DC70) void NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION(int teamId, int instanceId)l
extern _native64(0xD0AFAFF5A51D72F7) void NETWORK_END_TUTORIAL_SESSION()l
extern _native64(0xADA24309FE08DACF) bool NETWORK_IS_IN_TUTORIAL_SESSION()l
extern _native64(0xB37E4E6A2388CA7B) bool NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION()l
extern _native64(0x35F0B98A8387274D) bool NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING()l
extern _native64(0x3B39236746714134) int NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE(Player player)l
extern _native64(0x9DE986FC9A87C474) bool NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION(Player player, int index)l
extern _native64(0xFEA7A352DDB34D52) void NETWORK_BLOCK_PROXY_MIGRATION_BETWEEN_TUTORIAL_SESSIONS(any p0)l
extern _native64(0xBBDF066252829606) void NETWORK_CONCEAL_PLAYER(Player player, bool toggle, bool p2)l
extern _native64(0x919B3C98ED8292F9) bool NETWORK_IS_PLAYER_CONCEALED(Player player)l
extern _native64(0x1632BE0AC1E62876) void NETWORK_CONCEAL_ENTITY(Entity entity, bool toggle)l
extern _native64(0x71302EC70689052A) bool NETWORK_IS_ENTITY_CONCEALED(Entity entity)l
extern _native64(0xE679E3E06E363892) void NETWORK_OVERRIDE_CLOCK_TIME(int hours, int minutes, int seconds)l
extern _native64(0x42BF1D2E723B6D7E) void NETWORK_OVERRIDE_CLOCK_RATE(int ms)l
extern _native64(0xD972DF67326F966E) void NETWORK_CLEAR_CLOCK_TIME_OVERRIDE()l
extern _native64(0xD7C95D322FF57522) bool NETWORK_IS_CLOCK_TIME_OVERRIDDEN()l
extern _native64(0x494C8FB299290269) int NETWORK_ADD_ENTITY_AREA(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x376C6375BA60293A) int NETWORK_ADD_ENTITY_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width)l
extern _native64(0x25B99872D588A101) int NETWORK_ADD_CLIENT_ENTITY_AREA(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x2B1C623823DB0D9D) int NETWORK_ADD_CLIENT_ENTITY_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float radius)l
extern _native64(0x93CF869BAA0C4874) bool NETWORK_REMOVE_ENTITY_AREA(int areaHandle)l
extern _native64(0xE64A3CA08DFA37A9) bool NETWORK_ENTITY_AREA_DOES_EXIST(int areaHandle)l
extern _native64(0x4DF7CFFF471A7FB1) bool NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED(int areaHandle)l
extern _native64(0x4A2D4E8BF4265B0F) bool NETWORK_ENTITY_AREA_IS_OCCUPIED(int areaHandle)l
extern _native64(0x2B1813ABA29016C5) void NETWORK_USE_HIGH_PRECISION_BLENDING(int netID, bool toggle)l
extern _native64(0xA6FCECCF4721D679) void NETWORK_SET_CUSTOM_ARENA_BALL_PARAMS(int netId)l
extern _native64(0x95BAF97C82464629) void NETWORK_ENTITY_USE_HIGH_PRECISION_ROTATION(int netId, bool toggle)l
extern _native64(0x924426BFFD82E915) bool NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS()l
extern _native64(0x8132C0EB8B2B3293) bool NETWORK_IS_CLOUD_BACKGROUND_SCRIPT_REQUEST_PENDING()l
extern _native64(0x42FB3B532D526E6C) void NETWORK_REQUEST_CLOUD_TUNABLES()l
extern _native64(0x0467C11ED88B7D28) bool NETWORK_IS_TUNABLE_CLOUD_REQUEST_PENDING()l
extern _native64(0x10BD227A753B0D84) int NETWORK_GET_TUNABLE_CLOUD_CRC()l
extern _native64(0x85E5F8B9B898B20A) bool NETWORK_DOES_TUNABLE_EXIST(const char* tunableContext, const char* tunableName)l
extern _native64(0x8BE1146DFD5D4468) bool NETWORK_ACCESS_TUNABLE_INT(const char* tunableContext, const char* tunableName, int* value)l
extern _native64(0xE5608CA7BC163A5F) bool NETWORK_ACCESS_TUNABLE_FLOAT(const char* tunableContext, const char* tunableName, float* value)l
extern _native64(0xAA6A47A573ABB75A) bool NETWORK_ACCESS_TUNABLE_BOOL(const char* tunableContext, const char* tunableName)l
extern _native64(0xE4E53E1419D81127) bool NETWORK_DOES_TUNABLE_EXIST_HASH(Hash tunableContext, Hash tunableName)l
extern _native64(0xFAFC23AEE23868DB) bool NETWORK_ACCESS_TUNABLE_MODIFICATION_DETECTION_CLEAR()l
extern _native64(0x40FCE03E50E8DBE8) bool NETWORK_ACCESS_TUNABLE_INT_HASH(Hash tunableContext, Hash tunableName, int* value)l
extern _native64(0x3A8B55FDA4C8DDEF) bool NETWORK_ACCESS_TUNABLE_INT_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, int* value)l
extern _native64(0x972BC203BBC4C4D5) bool NETWORK_ACCESS_TUNABLE_FLOAT_HASH(Hash tunableContext, Hash tunableName, float* value)l
extern _native64(0x1950DAE9848A4739) bool NETWORK_ACCESS_TUNABLE_FLOAT_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, float* value)l
extern _native64(0xEA16B69D93D71A45) bool NETWORK_ACCESS_TUNABLE_BOOL_HASH(Hash tunableContext, Hash tunableName)l
extern _native64(0x697F508861875B42) bool NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, bool* value)l
extern _native64(0xC7420099936CE286) bool NETWORK_TRY_ACCESS_TUNABLE_BOOL_HASH(Hash tunableContext, Hash tunableName, bool defaultValue)l
extern _native64(0x187382F8A3E0A6C3) int NETWORK_GET_CONTENT_MODIFIER_LIST_ID(Hash contentHash)l
extern _native64(0x7DB53B37A2F211A0) int NETWORK_GET_BONE_ID_OF_FATAL_HIT()l
extern _native64(0x72433699B4E6DD64) void NETWORK_RESET_BODY_TRACKER()l
extern _native64(0xD38C4A6D047C019D) int NETWORK_GET_NUMBER_BODY_TRACKER_HITS()l
extern _native64(0x2E0BF682CC778D49) bool NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER(int boneIndex)l
extern _native64(0x0EDE326D47CD0F3E) bool NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER(Ped ped, Player player)l
extern _native64(0x890E2C5ABED7236D) void NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_DAMAGE(Entity entity, bool toggle)l
extern _native64(0x38B7C51AB1EDC7D8) void NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_WEAPON_HASH(Entity entity, bool toggle)l
extern _native64(0x3FC795691834481D) void NETWORK_SET_NO_LONGER_NEEDED(Entity entity, bool toggle)l
extern _native64(0x301A42153C9AD707) bool NETWORK_EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible, int netId)l
extern _native64(0x2A5E0621DD815A9A) void NETWORK_EXPLODE_HELI(Vehicle vehicle, bool isAudible, bool isInvisible, int netId)l
extern _native64(0xCD71A4ECAB22709E) void NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME(Entity entity)l
extern _native64(0xA7E30DE9272B6D49) void NETWORK_OVERRIDE_COORDS_AND_HEADING(Entity entity, float x, float y, float z, float heading)l
extern _native64(0xE6717E652B8C8D8A) void NETWORK_ENABLE_EXTRA_VEHICLE_ORIENTATION_BLEND_CHECKS(int netId, bool toggle)l
extern _native64(0x407091CF6037118E) void NETWORK_DISABLE_PROXIMITY_MIGRATION(int netID)l
extern _native64(0x1775961C2FBBCB5C) void NETWORK_SET_PROPERTY_ID(int id)l
extern _native64(0xC2B82527CA77053E) void NETWORK_CLEAR_PROPERTY_ID()l
extern _native64(0x367EF5E2F439B4C6) void NETWORK_SET_PLAYER_MENTAL_STATE(int p0)l
extern _native64(0x94538037EE44F5CF) void NETWORK_SET_MINIMUM_RANK_FOR_MISSION(bool p0)l
extern _native64(0xBD0BE0BFC927EAC1) void NETWORK_CACHE_LOCAL_PLAYER_HEAD_BLEND_DATA()l
extern _native64(0x237D5336A9A54108) bool NETWORK_HAS_CACHED_PLAYER_HEAD_BLEND_DATA(Player player)l
extern _native64(0x99B72C7ABDE5C910) bool NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA(Ped ped, Player player)l
extern _native64(0xF2EAC213D5EA0623) int GET_NUM_COMMERCE_ITEMS()l
extern _native64(0xEA14EEF5B7CD2C30) bool IS_COMMERCE_DATA_VALID()l
extern _native64(0xB606E6CC59664972) void TRIGGER_COMMERCE_DATA_FETCH(any p0)l
extern _native64(0x1D4DC17C38FEAFF0) bool IS_COMMERCE_DATA_FETCH_IN_PROGRESS()l
extern _native64(0x662635855957C411) const char* GET_COMMERCE_ITEM_ID(int index)l
extern _native64(0xB4271092CA7EDF48) const char* GET_COMMERCE_ITEM_NAME(int index)l
extern _native64(0xCA94551B50B4932C) const char* GET_COMMERCE_PRODUCT_PRICE(int index)l
extern _native64(0x2A7776C709904AB0) int GET_COMMERCE_ITEM_NUM_CATS(int index)l
extern _native64(0x6F44CBF56D79FAC0) const char* GET_COMMERCE_ITEM_CAT(int index, int index2)l
extern _native64(0x58C21165F6545892) void OPEN_COMMERCE_STORE(const char* p0, const char* p1, int p2)l
extern _native64(0x2EAC52B4019E2782) bool IS_COMMERCE_STORE_OPEN()l
extern _native64(0x9641A9FF718E9C5E) void SET_STORE_ENABLED(bool toggle)l
extern _native64(0xA2F952104FC6DD4B) bool REQUEST_COMMERCE_ITEM_IMAGE(int index)l
extern _native64(0x72D0706CD6CCDB58) void RELEASE_ALL_COMMERCE_ITEM_IMAGES()l
extern _native64(0x722F5D28B61C5EA8) const char* GET_COMMERCE_ITEM_TEXTURENAME(int index)l
extern _native64(0x883D79C4071E18B3) bool IS_STORE_AVAILABLE_TO_USER()l
extern _native64(0x265635150FB0D82E) void DELAY_MP_STORE_OPEN()l
extern _native64(0x444C4525ECE0A4B9) void RESET_STORE_NETWORK_GAME_TRACKING()l
extern _native64(0x59328EB08C5CEB2B) bool IS_USER_OLD_ENOUGH_TO_ACCESS_STORE()l
extern _native64(0xFAE628F1E9ADB239) void SET_LAST_VIEWED_SHOP_ITEM(Hash p0, int p1, Hash p2)l
extern _native64(0x754615490A029508) int GET_USER_PREMIUM_ACCESS()l
extern _native64(0x155467ACA0F55705) int GET_USER_STARTER_ACCESS()l
extern _native64(0xC64DED7EF0D2FE37) int CLOUD_DELETE_MEMBER_FILE(const char* p0)l
extern _native64(0x4C61B39930D045DA) bool CLOUD_HAS_REQUEST_COMPLETED(int requestId)l
extern _native64(0x3A3D5568AF297CD5) bool CLOUD_DID_REQUEST_SUCCEED(int requestId)l
extern _native64(0x4F18196C8D38768D) void CLOUD_CHECK_AVAILABILITY()l
extern _native64(0xC7ABAC5DE675EE3B) bool CLOUD_IS_CHECKING_AVAILABILITY()l
extern _native64(0x0B0CC10720653F3B) bool CLOUD_GET_AVAILABILITY_CHECK_RESULT()l
extern _native64(0x8B0C2964BA471961) int GET_CONTENT_TO_LOAD_TYPE()l
extern _native64(0x88B588B41FF7868E) bool GET_IS_LAUNCH_FROM_LIVE_AREA()l
extern _native64(0x67FC09BC554A75E5) bool GET_IS_LIVE_AREA_LAUNCH_WITH_CONTENT()l
extern _native64(0x966DD84FB6A46017) void CLEAR_SERVICE_EVENT_ARGUMENTS()l
extern _native64(0x152D90E4C1B4738A) bool UGC_COPY_CONTENT(any* p0, any* p1)l
extern _native64(0x9FEDF86898F100E9) bool UGC_IS_CREATING()l
extern _native64(0x5E24341A7F92A74B) bool UGC_HAS_CREATE_FINISHED()l
extern _native64(0x24E4E51FC16305F9) bool UGC_DID_CREATE_SUCCEED()l
extern _native64(0xFBC5E768C7A77A6A) int UGC_GET_CREATE_RESULT()l
extern _native64(0xC55A0B40FFB1ED23) const char* UGC_GET_CREATE_CONTENT_ID()l
extern _native64(0x17440AA15D1D3739) void UGC_CLEAR_CREATE_RESULT()l
extern _native64(0x9BF438815F5D96EA) bool UGC_QUERY_MY_CONTENT(any p0, any p1, any* p2, any p3, any p4, any p5)l
extern _native64(0x692D58DF40657E8C) bool UGC_QUERY_BY_CATEGORY(any p0, any p1, any p2, const char* p3, any p4, bool p5)l
extern _native64(0x158EC424F35EC469) bool UGC_QUERY_BY_CONTENT_ID(const char* contentId, bool latestVersion, const char* contentTypeName)l
extern _native64(0xC7397A83F7A2A462) bool UGC_QUERY_BY_CONTENT_IDS(any* data, int count, bool latestVersion, const char* contentTypeName)l
extern _native64(0x6D4CB481FAC835E8) bool UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT(int offset, int count, const char* contentTypeName, int p3)l
extern _native64(0xD5A4B59980401588) bool UGC_GET_BOOKMARKED_CONTENT(any p0, any p1, const char* p2, any* p3)l
extern _native64(0x3195F8DD0D531052) bool UGC_GET_MY_CONTENT(any p0, any p1, const char* p2, any* p3)l
extern _native64(0xF9E1CCAE8BA4C281) bool UGC_GET_FRIEND_CONTENT(any p0, any p1, const char* p2, any* p3)l
extern _native64(0x9F6E2821885CAEE2) bool UGC_GET_CREW_CONTENT(any p0, any p1, any p2, const char* p3, any* p4)l
extern _native64(0x678BB03C1A3BD51E) bool UGC_GET_GET_BY_CATEGORY(any p0, any p1, any p2, const char* p3, any* p4)l
extern _native64(0x815E5E3073DA1D67) bool UGC_GET_GET_BY_CONTENT_ID(const char* contentId, const char* contentTypeName)l
extern _native64(0xB8322EEB38BE7C26) bool UGC_GET_GET_BY_CONTENT_IDS(any* data, int dataCount, const char* contentTypeName)l
extern _native64(0xA7862BC5ED1DFD7E) bool UGC_GET_MOST_RECENTLY_CREATED_CONTENT(any p0, any p1, any* p2, any* p3)l
extern _native64(0x97A770BEEF227E2B) bool UGC_GET_MOST_RECENTLY_PLAYED_CONTENT(any p0, any p1, any* p2, any* p3)l
extern _native64(0x5324A0E3E4CE3570) bool UGC_GET_TOP_RATED_CONTENT(any p0, any p1, any* p2, any* p3)l
extern _native64(0xE9B99B6853181409) void UGC_CANCEL_QUERY()l
extern _native64(0xD53ACDBEF24A46E8) bool UGC_IS_GETTING()l
extern _native64(0x02ADA21EA2F6918F) bool UGC_HAS_GET_FINISHED()l
extern _native64(0x941E5306BCD7C2C7) bool UGC_DID_GET_SUCCEED()l
extern _native64(0xC87E740D9F3872CC) bool UGC_WAS_QUERY_FORCE_CANCELLED()l
extern _native64(0xEDF7F927136C224B) int UGC_GET_QUERY_RESULT()l
extern _native64(0xE0A6138401BCB837) int UGC_GET_CONTENT_NUM()l
extern _native64(0x769951E2455E2EB5) int UGC_GET_CONTENT_TOTAL()l
extern _native64(0x3A17A27D75C74887) Hash UGC_GET_CONTENT_HASH()l
extern _native64(0xBA96394A0EECFA65) void UGC_CLEAR_QUERY_RESULTS()l
extern _native64(0xCD67AD041A394C9C) const char* UGC_GET_CONTENT_USER_ID(int p0)l
extern _native64(0x584770794D758C18) bool UGC_GET_CONTENT_CREATOR_GAMER_HANDLE(int p0, any* p1)l
extern _native64(0x8C8D2739BA44AF0F) bool UGC_GET_CONTENT_CREATED_BY_LOCAL_PLAYER(any p0)l
extern _native64(0x703F12425ECA8BF5) const char* UGC_GET_CONTENT_USER_NAME(any p0)l
extern _native64(0xAEAB987727C5A8A4) bool UGC_GET_CONTENT_IS_USING_SC_NICKNAME(any p0)l
extern _native64(0xA7BAB11E7C9C6C5A) int UGC_GET_CONTENT_CATEGORY(int p0)l
extern _native64(0x55AA95F481D694D2) const char* UGC_GET_CONTENT_ID(int p0)l
extern _native64(0xC0173D6BFF4E0348) const char* UGC_GET_ROOT_CONTENT_ID(int p0)l
extern _native64(0xBF09786A7FCAB582) const char* UGC_GET_CONTENT_NAME(any p0)l
extern _native64(0x7CF0448787B23758) int UGC_GET_CONTENT_DESCRIPTION_HASH(any p0)l
extern _native64(0xBAF6BABF9E7CCC13) const char* UGC_GET_CONTENT_PATH(int p0, int p1)l
extern _native64(0xCFD115B373C0DF63) void UGC_GET_CONTENT_UPDATED_DATE(any p0, any* p1)l
extern _native64(0x37025B27D9B658B1) int UGC_GET_CONTENT_FILE_VERSION(any p0, any p1)l
extern _native64(0x1D610EB0FEA716D9) bool UGC_GET_CONTENT_HAS_LO_RES_PHOTO(int p0)l
extern _native64(0x7FCC39C46C3C03BD) bool UGC_GET_CONTENT_HAS_HI_RES_PHOTO(int p0)l
extern _native64(0x32DD916F3F7C9672) int UGC_GET_CONTENT_LANGUAGE(any p0)l
extern _native64(0x3054F114121C21EA) bool UGC_GET_CONTENT_IS_PUBLISHED(any p0)l
extern _native64(0xA9240A96C74CCA13) bool UGC_GET_CONTENT_IS_VERIFIED(any p0)l
extern _native64(0x1ACCFBA3D8DAB2EE) float UGC_GET_CONTENT_RATING(any p0, any p1)l
extern _native64(0x759299C5BB31D2A9) int UGC_GET_CONTENT_RATING_COUNT(any p0, any p1)l
extern _native64(0x87E5C46C187FE0AE) int UGC_GET_CONTENT_RATING_POSITIVE_COUNT(any p0, any p1)l
extern _native64(0x4E548C0D7AE39FF9) int UGC_GET_CONTENT_RATING_NEGATIVE_COUNT(any p0, any p1)l
extern _native64(0x70EA8DA57840F9BE) bool UGC_GET_CONTENT_HAS_PLAYER_RECORD(any p0)l
extern _native64(0x993CBE59D350D225) bool UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED(any p0)l
extern _native64(0x171DF6A0C07FB3DC) int UGC_REQUEST_CONTENT_DATA_FROM_INDEX(int p0, int p1)l
extern _native64(0x7FD2990AF016795E) int UGC_REQUEST_CONTENT_DATA_FROM_PARAMS(const char* contentTypeName, const char* contentId, int p2, int p3, int p4)l
extern _native64(0x5E0165278F6339EE) int UGC_REQUEST_CACHED_DESCRIPTION(int p0)l
extern _native64(0x2D5DC831176D0114) bool UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS(any p0)l
extern _native64(0xEBFA8D50ADDC54C4) bool UGC_HAS_DESCRIPTION_REQUEST_FINISHED(any p0)l
extern _native64(0x162C23CA83ED0A62) bool UGC_DID_DESCRIPTION_REQUEST_SUCCEED(any p0)l
extern _native64(0x40F7E66472DF3E5C) const char* UGC_GET_CACHED_DESCRIPTION(any p0, any p1)l
extern _native64(0x5A34CD9C3C5BEC44) bool UGC_RELEASE_CACHED_DESCRIPTION(any p0)l
extern _native64(0x68103E2247887242) void UGC_RELEASE_ALL_CACHED_DESCRIPTIONS()l
extern _native64(0x1DE0F5F50D723CAA) bool UGC_PUBLISH(const char* contentId, const char* baseContentId, const char* contentTypeName)l
extern _native64(0x274A1519DFC1094F) bool UGC_SET_BOOKMARKED(const char* contentId, bool bookmarked, const char* contentTypeName)l
extern _native64(0xD05D1A6C74DA3498) bool UGC_SET_DELETED(any* p0, bool p1, const char* p2)l
extern _native64(0x45E816772E93A9DB) bool UGC_IS_MODIFYING()l
extern _native64(0x299EF3C576773506) bool UGC_HAS_MODIFY_FINISHED()l
extern _native64(0x793FF272D5B365F4) bool UGC_DID_MODIFY_SUCCEED()l
extern _native64(0x5A0A3D1A186A5508) int UGC_GET_MODIFY_RESULT()l
extern _native64(0xA1E5E0204A6FCC70) void UGC_CLEAR_MODIFY_RESULT()l
extern _native64(0xB746D20B17F2A229) bool UGC_GET_CREATORS_BY_USER_ID(any* p0, any* p1)l
extern _native64(0x63B406D7884BFA95) bool UGC_HAS_QUERY_CREATORS_FINISHED()l
extern _native64(0x4D02279C83BE69FE) bool UGC_DID_QUERY_CREATORS_SUCCEED()l
extern _native64(0x597F8DBA9B206FC7) int UGC_GET_CREATOR_NUM()l
extern _native64(0x5CAE833B0EE0C500) bool UGC_LOAD_OFFLINE_QUERY(any p0)l
extern _native64(0x61A885D3F7CFEE9A) void UGC_CLEAR_OFFLINE_QUERY()l
extern _native64(0xF98DDE0A8ED09323) void UGC_SET_QUERY_DATA_FROM_OFFLINE(bool p0)l
extern _native64(0xFD75DABC0957BF33) void UGC_SET_USING_OFFLINE_CONTENT(bool p0)l
extern _native64(0xF53E48461B71EECB) bool UGC_IS_LANGUAGE_SUPPORTED(any p0)l
extern _native64(0x098AB65B9ED9A9EC) bool FACEBOOK_POST_COMPLETED_HEIST(const char* heistName, int cashEarned, int xpEarned)l
extern _native64(0xDC48473142545431) bool FACEBOOK_POST_CREATE_CHARACTER()l
extern _native64(0x0AE1F1653B554AB9) bool FACEBOOK_POST_COMPLETED_MILESTONE(int milestoneId)l
extern _native64(0x62B9FEC9A11F10EF) bool FACEBOOK_HAS_POST_COMPLETED()l
extern _native64(0xA75E2B6733DA5142) bool FACEBOOK_DID_POST_SUCCEED()l
extern _native64(0x43865688AE10F0D7) bool FACEBOOK_CAN_POST_TO_FACEBOOK()l
extern _native64(0x16160DA74A8E74A2) int TEXTURE_DOWNLOAD_REQUEST(any* gamerHandle, const char* filePath, const char* name, bool p3)l
extern _native64(0x0B203B4AFDE53A4F) int TITLE_TEXTURE_DOWNLOAD_REQUEST(const char* filePath, const char* name, bool p2)l
extern _native64(0x308F96458B7087CC) int UGC_TEXTURE_DOWNLOAD_REQUEST(const char* p0, int p1, int p2, int p3, const char* p4, bool p5)l
extern _native64(0x487EB90B98E9FB19) void TEXTURE_DOWNLOAD_RELEASE(int p0)l
extern _native64(0x5776ED562C134687) bool TEXTURE_DOWNLOAD_HAS_FAILED(int p0)l
extern _native64(0x3448505B6E35262D) const char* TEXTURE_DOWNLOAD_GET_NAME(int p0)l
extern _native64(0x8BD6C6DEA20E82C6) int GET_STATUS_OF_TEXTURE_DOWNLOAD(int p0)l
extern _native64(0x60EDD13EB3AC1FF3) bool NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET()l
extern _native64(0x82A2B386716608F1) bool NETWORK_SHOULD_SHOW_STRICT_NAT_WARNING()l
extern _native64(0xEFFB25453D8600F9) bool NETWORK_IS_CABLE_CONNECTED()l
extern _native64(0x66B59CFFD78467AF) bool NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV()l
extern _native64(0x606E4D3E3CCCF3EB) bool NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV()l
extern _native64(0x8020A73847E0CA7D) bool NETWORK_HAVE_ROS_BANNED_PRIV()l
extern _native64(0xA0AD7E2AF5349F61) bool NETWORK_HAVE_ROS_CREATE_TICKET_PRIV()l
extern _native64(0x5F91D5D0B36AA310) bool NETWORK_HAVE_ROS_MULTIPLAYER_PRIV()l
extern _native64(0x422D396F80A96547) bool NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV()l
extern _native64(0xA699957E60D80214) bool NETWORK_HAS_ROS_PRIVILEGE(int index)l
extern _native64(0xC22912B1D85F26B1) bool NETWORK_HAS_ROS_PRIVILEGE_END_DATE(int privilege, int* banType, any* timeData)l
extern _native64(0x593570C289A77688) bool NETWORK_HAS_ROS_PRIVILEGE_PLAYED_LAST_GEN()l
extern _native64(0x91B87C55093DE351) bool NETWORK_HAS_ROS_PRIVILEGE_SPECIAL_EDITION_CONTENT()l
extern _native64(0x36391F397731595D) int NETWORK_START_COMMUNICATION_PERMISSIONS_CHECK(any p0)l
extern _native64(0xDEB2B99A1AF1A2A6) int NETWORK_START_USER_CONTENT_PERMISSIONS_CHECK(any* netHandle)l
extern _native64(0x9465E683B12D3F6B) void NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE()l
extern _native64(0xCA59CCAE5D01E4CE) void NETWORK_SKIP_RADIO_RESET_NEXT_OPEN()l
extern _native64(0x659CF2EF7F550C4F) bool NETWORK_SKIP_RADIO_WARNING()l
extern _native64(0xB7C7F6AD6424304B) void NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC()l
extern _native64(0xC505036A35AFD01B) void NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND(bool toggle)l
extern _native64(0x267C78C60E806B9A) void NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION(Entity entity, bool toggle)l
extern _native64(0x6BFF5F84102DF80A) void NETWORK_SHOW_CHAT_RESTRICTION_MSC(Player player)l
extern _native64(0x5C497525F803486B) void NETWORK_SHOW_PSN_UGC_RESTRICTION()l
extern _native64(0x6FB7BB3607D27FA2) bool NETWORK_IS_TITLE_UPDATE_REQUIRED()l
extern _native64(0x45A83257ED02D9BC) void NETWORK_QUIT_MP_TO_DESKTOP()l
extern _native64(0x16D3D49902F697BB) bool NETWORK_IS_CONNECTED_VIA_RELAY(Player player)l
extern _native64(0xD414BE129BB81B32) float NETWORK_GET_AVERAGE_LATENCY(Player player)l
extern _native64(0x0E3A041ED6AC2B45) float NETWORK_GET_AVERAGE_PING(Player player)l
extern _native64(0x350C23949E43686C) float NETWORK_GET_AVERAGE_PACKET_LOSS(Player player)l
extern _native64(0xFF8FCF9FFC458A1C) int NETWORK_GET_NUM_UNACKED_RELIABLES(Player player)l
extern _native64(0x3765C3A3E8192E10) int NETWORK_GET_UNRELIABLE_RESEND_COUNT(Player player)l
extern _native64(0x52C1EADAF7B10302) int NETWORK_GET_HIGHEST_RELIABLE_RESEND_COUNT(Player player)l
extern _native64(0x5626D9D6810730D5) void NETWORK_REPORT_CODE_TAMPER()l
extern _native64(0x64D779659BC37B19) vector3 NETWORK_GET_LAST_ENTITY_POS_RECEIVED_OVER_NETWORK(Entity entity)l
extern _native64(0x125E6D638B8605D4) vector3 NETWORK_GET_LAST_PLAYER_POS_RECEIVED_OVER_NETWORK(Player player)l
extern _native64(0x33DE49EDF4DDE77A) vector3 NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK(Entity entity)l
extern _native64(0xAA5FAFCD2C5F5E47) vector3 NETWORK_GET_PREDICTED_VELOCITY(Entity entity, float maxSpeedToPredict)l
extern _native64(0xAEDF1BC1C133D6E3) void NETWORK_DUMP_NET_IF_CONFIG()l
extern _native64(0x2555CF7DA5473794) void NETWORK_GET_SIGNALLING_INFO(any* p0)l
extern _native64(0x6FD992C4A1C1B986) void NETWORK_GET_NET_STATISTICS_INFO(any* p0)l
extern _native64(0xDB663CC9FF3407A9) int NETWORK_GET_PLAYER_ACCOUNT_ID(Player player)l
extern _native64(0xC1447451DDB512F0) void NETWORK_UGC_NAV(any p0, any p1)l
#pragma endregion //}
#pragma region OBJECT //{
extern _native64(0x509D5878EB39E842) Object CREATE_OBJECT(Hash modelHash, float x, float y, float z, bool isNetwork, bool bScriptHostObj, bool dynamic)l
extern _native64(0x9A294B2138ABB884) Object CREATE_OBJECT_NO_OFFSET(Hash modelHash, float x, float y, float z, bool isNetwork, bool bScriptHostObj, bool dynamic)l
extern _native64(0x539E0AE3E6634B9F) void DELETE_OBJECT(Object* object)l
extern _native64(0x58A850EAEE20FAA3) bool PLACE_OBJECT_ON_GROUND_PROPERLY(Object object)l
extern _native64(0xD76EEEF746057FD6) bool PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(Object object)l
extern _native64(0xAFE24E4D29249E4A) bool ROTATE_OBJECT(Object object, float p1, float p2, bool p3)l
extern _native64(0x2FDFF4107B8C1147) bool SLIDE_OBJECT(Object object, float toX, float toY, float toZ, float speedX, float speedY, float speedZ, bool collision)l
extern _native64(0x8A7391690F5AFD81) void SET_OBJECT_TARGETTABLE(Object object, bool targettable)l
extern _native64(0x77F33F2CCF64B3AA) void SET_OBJECT_FORCE_VEHICLES_TO_AVOID(Object object, bool toggle)l
extern _native64(0xE143FA2249364369) Object GET_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, bool isMission, bool p6, bool p7)l
extern _native64(0x8ABFB70C49CC43E2) bool HAS_OBJECT_BEEN_BROKEN(Object object, any p1)l
extern _native64(0x761B0E69AC4D007E) bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(float p0, float p1, float p2, float p3, Hash modelHash, any p5)l
extern _native64(0x46494A2475701343) bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED(float x, float y, float z, float radius, Hash modelHash, bool p5)l
extern _native64(0x2542269291C6AC84) bool GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED(any p0)l
extern _native64(0x163E252DE035A133) vector3 GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS(float xPos, float yPos, float zPos, float heading, float xOffset, float yOffset, float zOffset)l
extern _native64(0x163F8B586BC95F2A) bool GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, vector3* outPosition, vector3* outRotation, int rotationOrder)l
extern _native64(0xF82D8F1926A02C3D) void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, bool locked, float heading, bool p6)l
extern _native64(0xEDC1A5B84AEF33FF) void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, bool* locked, float* heading)l
extern _native64(0x9B12F9A24FABEDB0) void SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(Hash modelHash, float x, float y, float z, bool locked, float xRotMult, float yRotMult, float zRotMult)l
extern _native64(0x006E4B040ED37EC3) void PLAY_OBJECT_AUTO_START_ANIM(any p0)l
extern _native64(0x6F8838D03D1DC226) void ADD_DOOR_TO_SYSTEM(Hash doorHash, Hash modelHash, float x, float y, float z, bool p5, bool scriptDoor, bool isLocal)l
extern _native64(0x464D8E1427156FE4) void REMOVE_DOOR_FROM_SYSTEM(Hash doorHash, any p1)l
extern _native64(0x6BAB9442830C7F53) void DOOR_SYSTEM_SET_DOOR_STATE(Hash doorHash, int state, bool requestDoor, bool forceUpdate)l
extern _native64(0x160AA1B32F6139B8) int DOOR_SYSTEM_GET_DOOR_STATE(Hash doorHash)l
extern _native64(0x4BC2854478F3A749) int DOOR_SYSTEM_GET_DOOR_PENDING_STATE(Hash doorHash)l
extern _native64(0x03C27E13B42A0E82) void DOOR_SYSTEM_SET_AUTOMATIC_RATE(Hash doorHash, float rate, bool requestDoor, bool forceUpdate)l
extern _native64(0x9BA001CB45CBF627) void DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(Hash doorHash, float distance, bool requestDoor, bool forceUpdate)l
extern _native64(0xB6E6FBA95C7324AC) void DOOR_SYSTEM_SET_OPEN_RATIO(Hash doorHash, float ajar, bool requestDoor, bool forceUpdate)l
extern _native64(0xE851471AEFC3374F) float DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE(Hash doorHash)l
extern _native64(0x65499865FCA6E5EC) float DOOR_SYSTEM_GET_OPEN_RATIO(Hash doorHash)l
extern _native64(0xC485E07E4F0B7958) void DOOR_SYSTEM_SET_SPRING_REMOVED(Hash doorHash, bool removed, bool requestDoor, bool forceUpdate)l
extern _native64(0xD9B71952F78A2640) void DOOR_SYSTEM_SET_HOLD_OPEN(Hash doorHash, bool toggle)l
extern _native64(0xA85A21582451E951) void DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES(Hash doorHash, bool p1)l
extern _native64(0xC153C43EA202C8C1) bool IS_DOOR_REGISTERED_WITH_SYSTEM(Hash doorHash)l
extern _native64(0xC531EE8A1145A149) bool IS_DOOR_CLOSED(Hash doorHash)l
extern _native64(0xC7F29CA00F46350E) void OPEN_ALL_BARRIERS_FOR_RACE(bool p0)l
extern _native64(0x701FDA1E82076BA4) void CLOSE_ALL_BARRIERS_FOR_RACE()l
extern _native64(0xDF97CDD4FC08FD34) bool DOOR_SYSTEM_GET_IS_PHYSICS_LOADED(any p0)l
extern _native64(0x589F80B325CC82C5) bool DOOR_SYSTEM_FIND_EXISTING_DOOR(float x, float y, float z, Hash modelHash, Hash* outDoorHash)l
extern _native64(0x90E47239EA1980B8) bool IS_GARAGE_EMPTY(Hash garageHash, bool p1, int p2)l
extern _native64(0x024A60DEB0EA69F0) bool IS_PLAYER_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Player player, float p2, int p3)l
extern _native64(0x1761DC5D8471CBAA) bool IS_PLAYER_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Player player, int p2)l
extern _native64(0x85B6C850546FDDE2) bool ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE(Hash garageHash, bool p1, bool p2, bool p3, any p4)l
extern _native64(0x673ED815D6E323B7) bool IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE(Hash garageHash, bool p1, bool p2, bool p3, any p4)l
extern _native64(0x372EF6699146A1E4) bool IS_OBJECT_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Entity entity, float p2, int p3)l
extern _native64(0xF0EED5A6BC7B237A) bool IS_OBJECT_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Entity entity, int p2)l
extern _native64(0xDA05194260CDCDF9) void CLEAR_GARAGE(Hash garageHash, bool isNetwork)l
extern _native64(0x190428512B240692) void CLEAR_OBJECTS_INSIDE_GARAGE(Hash garageHash, bool vehicles, bool peds, bool objects, bool isNetwork)l
extern _native64(0x659F9D71F52843F8) void DISABLE_TIDYING_UP_IN_GARAGE(int id, bool toggle)l
extern _native64(0xF2E1A7133DD356A6) void ENABLE_SAVING_IN_GARAGE(Hash garageHash, bool toggle)l
extern _native64(0x66A49D021870FE88) void CLOSE_SAFEHOUSE_GARAGES()l
extern _native64(0xBFA48E2FF417213F) bool DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(float x, float y, float z, float radius, Hash hash, bool p5)l
extern _native64(0x2A70BAE8883E4C81) bool IS_POINT_IN_ANGLED_AREA(float xPos, float yPos, float zPos, float x1, float y1, float z1, float x2, float y2, float z2, float width, bool debug, bool includeZ)l
extern _native64(0x4D89D607CB3DD1D2) void SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(Object object, bool toggle)l
extern _native64(0xF6DF6E90DE7DF90F) void SET_OBJECT_PHYSICS_PARAMS(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy)l
extern _native64(0xB6FBFD079B8D0596) float GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(any p0, bool p1)l
extern _native64(0x406137F8EF90EAF5) void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Object object, bool toggle)l
extern _native64(0x397DC58FF00298D1) bool IS_ANY_OBJECT_NEAR_POINT(float x, float y, float z, float range, bool p4)l
extern _native64(0x8C90FE4B381BA60A) bool IS_OBJECT_NEAR_POINT(Hash objectHash, float x, float y, float z, float range)l
extern _native64(0x4A39DB43E47CF3AA) void REMOVE_OBJECT_HIGH_DETAIL_MODEL(Object object)l
extern _native64(0xE7E4C198B0185900) void BREAK_OBJECT_FRAGMENT_CHILD(Object p0, any p1, bool p2)l
extern _native64(0xE05F6AEEFEB0BB02) void DAMAGE_OBJECT_FRAGMENT_CHILD(any p0, any p1, any p2)l
extern _native64(0xF9C1681347C8BD15) void FIX_OBJECT_FRAGMENT(Object object)l
extern _native64(0xB252BC036B525623) void TRACK_OBJECT_VISIBILITY(Object object)l
extern _native64(0x8B32ACE6326A7546) bool IS_OBJECT_VISIBLE(Object object)l
extern _native64(0xC6033D32241F6FB5) void SET_OBJECT_IS_SPECIAL_GOLFBALL(Object object, bool toggle)l
extern _native64(0xEB6F1A9B5510A5D2) void SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS(any p0, bool p1)l
extern _native64(0xABDABF4E1EDECBFA) void ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS(bool value)l
extern _native64(0xBCE595371A5FBAAF) void SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME(Object object, bool toggle)l
extern _native64(0xB48FCED898292E52) Object GET_RAYFIRE_MAP_OBJECT(float x, float y, float z, float radius, const char* name)l
extern _native64(0x5C29F698D404C5E1) void SET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object, int state)l
extern _native64(0x899BA936634A322E) int GET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object)l
extern _native64(0x52AF537A0C5B8AAD) bool DOES_RAYFIRE_MAP_OBJECT_EXIST(Object object)l
extern _native64(0x260EE4FDBDF4DB01) float GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE(Object object)l
extern _native64(0xFBA08C503DD5FA58) Pickup CREATE_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int p4, int value, bool p6, Hash modelHash)l
extern _native64(0x891804727E0A98B7) Pickup CREATE_PICKUP_ROTATE(Hash pickupHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, int flag, int amount, any p9, bool p10, Hash modelHash)l
extern _native64(0x394CD08E31313C28) void FORCE_PICKUP_ROTATE_FACE_UP()l
extern _native64(0x826D1EE4D1CAFC78) void SET_CUSTOM_PICKUP_WEAPON_HASH(Hash pickupHash, Pickup pickup)l
extern _native64(0x673966A0C0FD7171) Object CREATE_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, bool p7, bool p8)l
extern _native64(0x9C93764223E29C50) Object CREATE_NON_NETWORKED_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, bool p7, bool p8)l
extern _native64(0x1E3F1B1B891A2AAA) void BLOCK_PLAYERS_FOR_AMBIENT_PICKUP(any p0, any p1)l
extern _native64(0x2EAF1FDB2FB55698) Object CREATE_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, bool placeOnGround, Hash modelHash)l
extern _native64(0x125494B98A21AAF7) Object CREATE_NON_NETWORKED_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, bool placeOnGround, Hash modelHash)l
extern _native64(0x8DC39368BDD57755) void ATTACH_PORTABLE_PICKUP_TO_PED(Object pickupObject, Ped ped)l
extern _native64(0xCF463D1E9A0AECB1) void DETACH_PORTABLE_PICKUP_FROM_PED(Object pickupObject)l
extern _native64(0x5CE2E45A5CE2E45A) void FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING(Object object)l
extern _native64(0x867458251D47CCB2) void HIDE_PORTABLE_PICKUP_WHEN_DETACHED(Object pickupObject, bool toggle)l
extern _native64(0x0BF3B3BD47D79C08) void SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER(Hash modelHash, int number)l
extern _native64(0x78857FC65CADB909) void SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS(bool toggle)l
extern _native64(0x6E16BC2503FF1FF0) vector3 GET_SAFE_PICKUP_COORDS(float x, float y, float z, float p3, float p4)l
extern _native64(0xD4A7A435B3710D05) void ADD_EXTENDED_PICKUP_PROBE_AREA(float x, float y, float z, float radius)l
extern _native64(0xB7C6D80FB371659A) void CLEAR_EXTENDED_PICKUP_PROBE_AREAS()l
extern _native64(0x225B8B35C88029B3) vector3 GET_PICKUP_COORDS(Pickup pickup)l
extern _native64(0x8DCA505A5C196F05) void SUPPRESS_PICKUP_SOUND_FOR_PICKUP(any p0, any p1)l
extern _native64(0x27F9D613092159CF) void REMOVE_ALL_PICKUPS_OF_TYPE(Hash pickupHash)l
extern _native64(0x80EC48E6679313F9) bool HAS_PICKUP_BEEN_COLLECTED(Pickup pickup)l
extern _native64(0x3288D8ACAECD2AB2) void REMOVE_PICKUP(Pickup pickup)l
extern _native64(0x0589B5E791CE9B2B) void CREATE_MONEY_PICKUPS(float x, float y, float z, int value, int amount, Hash model)l
extern _native64(0xAFC1CA75AD4074D1) bool DOES_PICKUP_EXIST(Pickup pickup)l
extern _native64(0xD9EFB6DBF7DAAEA3) bool DOES_PICKUP_OBJECT_EXIST(Object pickupObject)l
extern _native64(0x5099BC55630B25AE) Object GET_PICKUP_OBJECT(Pickup pickup)l
extern _native64(0xFC481C641EBBD27D) bool IS_OBJECT_A_PICKUP(Object object)l
extern _native64(0x0378C08504160D0D) bool IS_OBJECT_A_PORTABLE_PICKUP(Object object)l
extern _native64(0xF9C36251F6E48E33) bool DOES_PICKUP_OF_TYPE_EXIST_IN_AREA(Hash pickupHash, float x, float y, float z, float radius)l
extern _native64(0x78015C9B4B3ECC9D) void SET_PICKUP_REGENERATION_TIME(Pickup pickup, int duration)l
extern _native64(0x758A5C1B3B1E1990) void FORCE_PICKUP_REGENERATE(any p0)l
extern _native64(0x616093EC6B139DD9) void SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE(Player player, Hash pickupHash, bool toggle)l
extern _native64(0x88EAEC617CD26926) void SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL(Hash modelHash, bool toggle)l
extern _native64(0xFDC07C58E8AAB715) void ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE(Hash pickupHash)l
extern _native64(0x53E0DF1A2A3CF0CA) void SET_TEAM_PICKUP_OBJECT(Object object, any p1, bool p2)l
extern _native64(0x92AEFB5F6E294023) void PREVENT_COLLECTION_OF_PORTABLE_PICKUP(Object object, bool p1, bool p2)l
extern _native64(0x27F248C3FEBFAAD3) void SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)l
extern _native64(0x0596843B34B95CE5) void SET_PICKUP_GLOW_OFFSET(Pickup pickup, float p1)l
extern _native64(0xA08FE5E49BDC39DD) void SET_PICKUP_OBJECT_GLOW_OFFSET(Pickup pickup, float p1, bool p2)l
extern _native64(0x62454A641B41F3C5) void SET_OBJECT_GLOW_IN_SAME_TEAM(Pickup pickup)l
extern _native64(0x39A5FB7EAF150840) void SET_PICKUP_OBJECT_ARROW_MARKER(Pickup pickup, bool toggle)l
extern _native64(0x834344A414C7C85D) void ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)l
extern _native64(0xDB41D07A45A6D4B7) int GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP(Hash pickupHash)l
extern _native64(0x318516E02DE3ECE2) void SET_PICKUP_GENERATION_RANGE_MULTIPLIER(float multiplier)l
extern _native64(0xB3ECA65C7317F174) float GET_PICKUP_GENERATION_RANGE_MULTIPLIER()l
extern _native64(0x31F924B53EADDF65) void SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW(bool p0)l
extern _native64(0x1C1B69FAE509BA97) void SET_PICKUP_UNCOLLECTABLE(Pickup pickup, bool toggle)l
extern _native64(0x858EC9FD25DE04AA) void SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)l
extern _native64(0x3ED2B83AB2E82799) void SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)l
extern _native64(0x8881C98A31117998) void SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle)l
extern _native64(0x8CFF648FBD7330F1) void SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT(int p0)l
extern _native64(0x46F3ADD1E2D5BAF2) void SET_PORTABLE_PICKUP_PERSIST(Pickup pickup, bool toggle)l
extern _native64(0x641F272B52E2F0F8) void ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS(Pickup pickup, bool toggle)l
extern _native64(0x4C134B4DF76025D0) void FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP(Pickup pickup, bool toggle)l
extern _native64(0xAA059C615DE9DD03) void ALLOW_PICKUP_BY_NONE_PARTICIPANT(Pickup pickup, bool toggle)l
extern _native64(0xF92099527DB8E2A7) void SUPPRESS_PICKUP_REWARD_TYPE(int rewardType, bool suppress)l
extern _native64(0xA2C1F5E92AFE49ED) void CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION()l
extern _native64(0x762DB2D380B48D04) void CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION(int rewardType)l
extern _native64(0x3430676B11CDF21D) void RENDER_FAKE_PICKUP_GLOW(float x, float y, float z, int colorIndex)l
extern _native64(0x7813E8B8C4AE4799) void SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE(Pickup pickup)l
extern _native64(0xBFFE53AE7E67FCDC) void SET_PICKUP_TRACK_DAMAGE_EVENTS(Pickup pickup, bool toggle)l
extern _native64(0xD05A3241B9A86F19) void SET_ENTITY_FLAG_SUPPRESS_SHADOW(Entity entity, bool toggle)l
extern _native64(0xB2D0BDE54F0E8E5A) void SET_ENTITY_FLAG_RENDER_SMALL_SHADOW(Object object, bool toggle)l
extern _native64(0x08F96CA6C551AD51) Hash GET_WEAPON_TYPE_FROM_PICKUP_TYPE(Hash pickupHash)l
extern _native64(0xD6429A016084F1A5) Hash GET_PICKUP_TYPE_FROM_WEAPON_HASH(Hash weaponHash)l
extern _native64(0x11D1E53A726891FE) bool IS_PICKUP_WEAPON_OBJECT_VALID(Object object)l
extern _native64(0xE84EB93729C5F36A) int GET_OBJECT_TINT_INDEX(Object object)l
extern _native64(0x971DA0055324D033) void SET_OBJECT_TINT_INDEX(Object object, int textureVariation)l
extern _native64(0xF12E33034D887F66) bool SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, int textureVariation)l
extern _native64(0x31574B1B41268673) void SET_PROP_TINT_INDEX(any p0, any p1)l
extern _native64(0x5F048334B4A4E774) bool SET_PROP_LIGHT_COLOR(Object object, bool p1, int r, int g, int b)l
extern _native64(0xADF084FB8F075D06) bool IS_PROP_LIGHT_OVERRIDEN(Object object)l
extern _native64(0x3B2FD68DB5F8331C) void SET_OBJECT_IS_VISIBLE_IN_MIRRORS(Object object, bool toggle)l
extern _native64(0x96EE0EBA0163DF80) void SET_OBJECT_SPEED_BOOST_AMOUNT(Object object, any p1)l
extern _native64(0xDF6CA0330F2E737B) void SET_OBJECT_SPEED_BOOST_DURATION(Object object, float duration)l
extern _native64(0x5EAAD83F8CFB4575) Hash CONVERT_OLD_PICKUP_TYPE_TO_NEW(Hash pickupHash)l
extern _native64(0xF538081986E49E9D) void SET_FORCE_OBJECT_THIS_FRAME(float x, float y, float z, float p3)l
extern _native64(0xADBE4809F19F927A) void ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE(Object object)l
extern _native64(0x8CAAB2BD3EA58BD4) void SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE(any p0)l
extern _native64(0x63ECF581BC70E363) void SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT(Entity entity, any p1)l
extern _native64(0x911024442F4898F0) void SET_DRIVE_ARTICULATED_JOINT(Object object, bool toggle, int p2)l
extern _native64(0xB20834A7DD3D8896) void SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR(Object object, bool toggle, int p2, Ped ped)l
extern _native64(0x734E1714D077DA9A) void SET_OBJECT_IS_A_PRESSURE_PLATE(Object object, bool toggle)l
extern _native64(0x1A6CBB06E2D0D79D) void SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE(Object object, bool p1)l
extern _native64(0x43C677F1E1158005) bool GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE(Object object, any p1)l
extern _native64(0x3BD770D281982DB5) bool GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE(any p0, any p1)l
extern _native64(0x1C57C94A6446492A) void SET_IS_OBJECT_ARTICULATED(Object object, bool toggle)l
extern _native64(0xB5B7742424BD4445) void SET_IS_OBJECT_BALL(Object object, bool toggle)l
#pragma endregion //}
#pragma region PAD //{
extern _native64(0x1CEA6BFDF248E5D9) bool IS_CONTROL_ENABLED(int control, int action)l
extern _native64(0xF3A21BCD95725A4A) bool IS_CONTROL_PRESSED(int control, int action)l
extern _native64(0x648EE3E7F38877DD) bool IS_CONTROL_RELEASED(int control, int action)l
extern _native64(0x580417101DDB492F) bool IS_CONTROL_JUST_PRESSED(int control, int action)l
extern _native64(0x50F940259D3841E6) bool IS_CONTROL_JUST_RELEASED(int control, int action)l
extern _native64(0xD95E79E8686D2C27) int GET_CONTROL_VALUE(int control, int action)l
extern _native64(0xEC3C9B8D5327B563) float GET_CONTROL_NORMAL(int control, int action)l
extern _native64(0x5B73C77D9EB66E24) void SET_USE_ADJUSTED_MOUSE_COORDS(bool toggle)l
extern _native64(0x5B84D09CEC5209C5) float GET_CONTROL_UNBOUND_NORMAL(int control, int action)l
extern _native64(0xE8A25867FBA3B05E) bool SET_CONTROL_VALUE_NEXT_FRAME(int control, int action, float value)l
extern _native64(0xE2587F8CBBD87B1D) bool IS_DISABLED_CONTROL_PRESSED(int control, int action)l
extern _native64(0xFB6C4072E9A32E92) bool IS_DISABLED_CONTROL_RELEASED(int control, int action)l
extern _native64(0x91AEF906BCA88877) bool IS_DISABLED_CONTROL_JUST_PRESSED(int control, int action)l
extern _native64(0x305C8DCD79DA8B0F) bool IS_DISABLED_CONTROL_JUST_RELEASED(int control, int action)l
extern _native64(0x11E65974A982637C) float GET_DISABLED_CONTROL_NORMAL(int control, int action)l
extern _native64(0x4F8A26A890FD62FB) float GET_DISABLED_CONTROL_UNBOUND_NORMAL(int control, int action)l
extern _native64(0xD7D22F5592AED8BA) int GET_CONTROL_HOW_LONG_AGO(int control)l
extern _native64(0xA571D46727E2B718) bool IS_USING_KEYBOARD_AND_MOUSE(int control)l
extern _native64(0x13337B38DB572509) bool IS_USING_CURSOR(int control)l
extern _native64(0xFC695459D4D0E219) bool SET_CURSOR_POSITION(float x, float y)l
extern _native64(0x23F09EADC01449D6) bool IS_USING_REMOTE_PLAY(int control)l
extern _native64(0x6CD79468A1E595C6) bool HAVE_CONTROLS_CHANGED(int control)l
extern _native64(0x0499D7B09FC9B407) const char* GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(int control, int action, bool allowXOSwap)l
extern _native64(0x80C2FD58D720C801) const char* GET_CONTROL_GROUP_INSTRUCTIONAL_BUTTONS_STRING(int control, int controlGroup, bool allowXOSwap)l
extern _native64(0x8290252FFF36ACB5) void SET_CONTROL_LIGHT_EFFECT_COLOR(int control, int red, int green, int blue)l
extern _native64(0xCB0360EFEFB2580D) void CLEAR_CONTROL_LIGHT_EFFECT(int control)l
extern _native64(0x48B3886C1358D0D5) void SET_CONTROL_SHAKE(int control, int duration, int frequency)l
extern _native64(0x14D29BB12D47F68C) void SET_CONTROL_TRIGGER_SHAKE(int control, int leftDuration, int leftFrequency, int rightDuration, int rightFrequency)l
extern _native64(0x38C16A305E8CDC8D) void STOP_CONTROL_SHAKE(int control)l
extern _native64(0xF239400E16C23E08) void SET_CONTROL_SHAKE_SUPPRESSED_ID(int control, int uniqueId)l
extern _native64(0xA0CEFCEA390AAB9B) void CLEAR_CONTROL_SHAKE_SUPPRESSED_ID(int control)l
extern _native64(0x77B612531280010D) bool IS_LOOK_INVERTED()l
extern _native64(0xE1615EC03B3BB4FD) bool IS_MOUSE_LOOK_INVERTED()l
extern _native64(0xBB41AFBBBC0A0287) int GET_LOCAL_PLAYER_AIM_STATE()l
extern _native64(0x59B9A7AF4C95133C) int GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE()l
extern _native64(0x25AAA32BDC98F2A3) bool GET_IS_USING_ALTERNATE_HANDBRAKE()l
extern _native64(0x0F70731BACCFBB96) bool GET_IS_USING_ALTERNATE_DRIVEBY()l
extern _native64(0xFC859E2374407556) bool GET_ALLOW_MOVEMENT_WHILE_ZOOMED()l
extern _native64(0x798FDEB5B1575088) void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(bool toggle)l
extern _native64(0xEDE476E5EE29EDB1) void SET_INPUT_EXCLUSIVE(int control, int action)l
extern _native64(0xFE99B66D079CF6BC) void DISABLE_CONTROL_ACTION(int control, int action, bool disableRelatedActions)l
extern _native64(0x351220255D64C155) void ENABLE_CONTROL_ACTION(int control, int action, bool enableRelatedActions)l
extern _native64(0x5F4B6931816E599B) void DISABLE_ALL_CONTROL_ACTIONS(int control)l
extern _native64(0xA5FFE9B05F199DE7) void ENABLE_ALL_CONTROL_ACTIONS(int control)l
extern _native64(0x3D42B92563939375) bool INIT_PC_SCRIPTED_CONTROLS(const char* schemeName)l
extern _native64(0x4683149ED1DDE7A1) bool SWITCH_PC_SCRIPTED_CONTROLS(const char* schemeName)l
extern _native64(0x643ED62D5EA3BEBD) void SHUTDOWN_PC_SCRIPTED_CONTROLS()l
extern _native64(0x7F4724035FDCA1DD) void ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT(int control)l
#pragma endregion //}
#pragma region PATHFIND //{
extern _native64(0xBF1A602B5BA52FEE) void SET_ROADS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool nodeEnabled, bool unknown2)l
extern _native64(0x1A5AA1208AF5DB59) void SET_ROADS_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool unknown1, bool unknown2, bool unknown3)l
extern _native64(0x34F060F4BF92E018) void SET_PED_PATHS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, any p7)l
extern _native64(0xB61C8E878A4199CA) bool GET_SAFE_COORD_FOR_PED(float x, float y, float z, bool onGround, vector3* outPosition, int flags)l
extern _native64(0x240A18690AE96513) bool GET_CLOSEST_VEHICLE_NODE(float x, float y, float z, vector3* outPosition, int nodeFlags, float p5, float p6)l
extern _native64(0x2EABE3B06F58C1BE) bool GET_CLOSEST_MAJOR_VEHICLE_NODE(float x, float y, float z, vector3* outPosition, float unknown1, float unknown2)l
extern _native64(0xFF071FB798B803B0) bool GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, vector3* outPosition, float* outHeading, int nodeType, float p6, float p7)l
extern _native64(0xE50E52416CCF948B) bool GET_NTH_CLOSEST_VEHICLE_NODE(float x, float y, float z, int nthClosest, vector3* outPosition, int nodeFlags, float unknown1, float unknown2)l
extern _native64(0x22D7275A79FE8215) int GET_NTH_CLOSEST_VEHICLE_NODE_ID(float x, float y, float z, int nth, int nodeFlags, float p5, float p6)l
extern _native64(0x80CA6A8B6C094CC4) bool GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, int nthClosest, vector3* outPosition, float* outHeading, int* outNumLanes, int nodeFlags, float unknown3, float unknown4)l
extern _native64(0x6448050E9C2A7207) int GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(float x, float y, float z, int nthClosest, vector3* outPosition, float* outHeading, int nodeFlags, float p7, float p8)l
extern _native64(0x45905BE8654AE067) bool GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(float x, float y, float z, float desiredX, float desiredY, float desiredZ, int nthClosest, vector3* outPosition, float* outHeading, int nodeFlags, float p10, float p11)l
extern _native64(0x0568566ACBB5DEDC) bool GET_VEHICLE_NODE_PROPERTIES(float x, float y, float z, int* density, int* flags)l
extern _native64(0x1EAF30FCFBF5AF74) bool IS_VEHICLE_NODE_ID_VALID(int vehicleNodeId)l
extern _native64(0x703123E5E7D429C2) void GET_VEHICLE_NODE_POSITION(int nodeId, vector3* outPosition)l
extern _native64(0xA2AE5C478B96E3B6) bool GET_VEHICLE_NODE_IS_GPS_ALLOWED(int nodeID)l
extern _native64(0x4F5070AA58F69279) bool GET_VEHICLE_NODE_IS_SWITCHED_OFF(int nodeID)l
extern _native64(0x132F52BBA570FE92) bool GET_CLOSEST_ROAD(float x, float y, float z, float p3, int p4, vector3* p5, vector3* p6, any* p7, any* p8, float* p9, bool p10)l
extern _native64(0xC2AB6BFE34E92F8B) bool LOAD_ALL_PATH_NODES(bool set)l
extern _native64(0x228E5C6AD4D74BFD) void SET_ALLOW_STREAM_PROLOGUE_NODES(bool toggle)l
extern _native64(0xF74B1FFA4A15FBEA) void SET_ALLOW_STREAM_HEIST_ISLAND_NODES(int type)l
extern _native64(0xF7B79A50B905A30D) bool ARE_NODES_LOADED_FOR_AREA(float x1, float y1, float x2, float y2)l
extern _native64(0x07FB139B592FA687) bool REQUEST_PATH_NODES_IN_AREA_THIS_FRAME(float x1, float y1, float x2, float y2)l
extern _native64(0x1EE7063B80FFC77C) void SET_ROADS_BACK_TO_ORIGINAL(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native64(0x0027501B9F3B407E) void SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, any p7)l
extern _native64(0x0B919E1FB47CC4E0) void SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0xAA76052DDA9BFC3E) void ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0xE04B48F2CC926253) void SET_PED_PATHS_BACK_TO_ORIGINAL(float x1, float y1, float z1, float x2, float y2, float z2, any p6)l
extern _native64(0x93E0DB8440B73A7D) bool GET_RANDOM_VEHICLE_NODE(float x, float y, float z, float radius, bool p4, bool p5, bool p6, vector3* outPosition, int* nodeId)l
extern _native64(0x809549AFC7AEC597) vector3 GET_SPAWN_COORDS_FOR_VEHICLE_NODE(int nodeAddress, float towardsCoorsX, float towardsCoorsY, float towardsCoorsZ, vector3* centrePoint, float* heading)l
extern _native64(0x2EB41072B4C1E4C0) void GET_STREET_NAME_AT_COORD(float x, float y, float z, Hash* streetName, Hash* crossingRoad)l
extern _native64(0xF90125F1F79ECDF8) int GENERATE_DIRECTIONS_TO_COORD(float x, float y, float z, bool p3, int* direction, float* p5, float* distToNxJunction)l
extern _native64(0x72751156E7678833) void SET_IGNORE_NO_GPS_FLAG(bool toggle)l
extern _native64(0x1FC289A0C3FF470F) void SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE(bool toggle)l
extern _native64(0xDC20483CD3DD5201) void SET_GPS_DISABLED_ZONE(float x1, float y1, float z1, float x2, float y2, float z3)l
extern _native64(0xBBB45C3CF5C8AA85) int GET_GPS_BLIP_ROUTE_LENGTH()l
extern _native64(0xF3162836C28F9DA5) bool GET_POS_ALONG_GPS_TYPE_ROUTE(vector3* result, bool p1, float p2, int p3)l
extern _native64(0x869DAACBBE9FA006) bool GET_GPS_BLIP_ROUTE_FOUND()l
extern _native64(0xA0F8A7517A273C05) bool GET_ROAD_BOUNDARY_USING_HEADING(float x, float y, float z, float heading, vector3* outPosition)l
extern _native64(0x16F46FB18C8009E4) bool GET_POSITION_BY_SIDE_OF_ROAD(float x, float y, float z, int p3, vector3* outPosition)l
extern _native64(0x125BF4ABFC536B09) bool IS_POINT_ON_ROAD(float x, float y, float z, Vehicle vehicle)l
extern _native64(0xD3A6A0EF48823A8C) int GET_NEXT_GPS_DISABLED_ZONE_INDEX()l
extern _native64(0xD0BC1C6FB18EE154) void SET_GPS_DISABLED_ZONE_AT_INDEX(float x1, float y1, float z1, float x2, float y2, float z2, int index)l
extern _native64(0x2801D0012266DF07) void CLEAR_GPS_DISABLED_ZONE_AT_INDEX(int index)l
extern _native64(0x387EAD7EE42F6685) void ADD_NAVMESH_REQUIRED_REGION(float x, float y, float radius)l
extern _native64(0x916F0A3CDEC3445E) void REMOVE_NAVMESH_REQUIRED_REGIONS()l
extern _native64(0x705A844002B39DC0) bool IS_NAVMESH_REQUIRED_REGION_IN_USE()l
extern _native64(0x4C8872D8CDBE1B8B) void DISABLE_NAVMESH_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool toggle)l
extern _native64(0x8415D95B194A3AEA) bool ARE_ALL_NAVMESH_REGIONS_LOADED()l
extern _native64(0xF813C7E63F9062A5) bool IS_NAVMESH_LOADED_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x01708E8DD3FF8C65) int GET_NUM_NAVMESHES_EXISTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0xFCD5C8E06E502F5A) int ADD_NAVMESH_BLOCKING_OBJECT(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, any p8)l
extern _native64(0x109E99373F290687) void UPDATE_NAVMESH_BLOCKING_OBJECT(any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8)l
extern _native64(0x46399A7895957C0E) void REMOVE_NAVMESH_BLOCKING_OBJECT(any p0)l
extern _native64(0x0EAEB0DB4B132399) bool DOES_NAVMESH_BLOCKING_OBJECT_EXIST(any p0)l
extern _native64(0x29C24BFBED8AB8FB) float GET_APPROX_HEIGHT_FOR_POINT(float x, float y)l
extern _native64(0x8ABE8608576D9CE3) float GET_APPROX_HEIGHT_FOR_AREA(float x1, float y1, float x2, float y2)l
extern _native64(0x336511A34F2E5185) float GET_APPROX_FLOOR_FOR_POINT(float x, float y)l
extern _native64(0x3599D741C9AC6310) float GET_APPROX_FLOOR_FOR_AREA(float x1, float y1, float x2, float y2)l
extern _native64(0xADD95C7005C4A197) float CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(float x1, float y1, float z1, float x2, float y2, float z2)l
#pragma endregion //}
#pragma region PED //{
extern _native64(0xD49F9B0955C367DE) Ped CREATE_PED(int pedType, Hash modelHash, float x, float y, float z, float heading, bool isNetwork, bool bScriptHostPed)l
extern _native64(0x9614299DCB53E54B) void DELETE_PED(Ped* ped)l
extern _native64(0xEF29A16337FACADB) Ped CLONE_PED(Ped ped, bool isNetwork, bool bScriptHostPed, bool copyHeadBlendFlag)l
extern _native64(0x668FD40BCBA5DE48) Ped CLONE_PED_ALT(Ped ped, bool isNetwork, bool bScriptHostPed, bool copyHeadBlendFlag, bool p4)l
extern _native64(0xE952D6431689AD9A) void CLONE_PED_TO_TARGET(Ped ped, Ped targetPed)l
extern _native64(0x148B08C2D2ACB884) void CLONE_PED_TO_TARGET_ALT(Ped ped, Ped targetPed, bool p2)l
extern _native64(0xA3EE4A07279BB9DB) bool IS_PED_IN_VEHICLE(Ped ped, Vehicle vehicle, bool atGetIn)l
extern _native64(0x796D90EFB19AA332) bool IS_PED_IN_MODEL(Ped ped, Hash modelHash)l
extern _native64(0x997ABD671D25CA0B) bool IS_PED_IN_ANY_VEHICLE(Ped ped, bool atGetIn)l
extern _native64(0x16EC4839969F9F5E) bool IS_COP_PED_IN_AREA_3D(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x84A2DD9AC37C35C1) bool IS_PED_INJURED(Ped ped)l
extern _native64(0x5983BB449D7FDB12) bool IS_PED_HURT(Ped ped)l
extern _native64(0xD839450756ED5A80) bool IS_PED_FATALLY_INJURED(Ped ped)l
extern _native64(0x3317DEDB88C95038) bool IS_PED_DEAD_OR_DYING(Ped ped, bool p1)l
extern _native64(0xE0A0AEC214B1FABA) bool IS_CONVERSATION_PED_DEAD(Ped ped)l
extern _native64(0x3998B1276A3300E5) bool IS_PED_AIMING_FROM_COVER(Ped ped)l
extern _native64(0x24B100C68C645951) bool IS_PED_RELOADING(Ped ped)l
extern _native64(0x12534C348C6CB68B) bool IS_PED_A_PLAYER(Ped ped)l
extern _native64(0x7DD959874C1FD534) Ped CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, bool isNetwork, bool bScriptHostPed)l
extern _native64(0xAA5A7ECE2AA8FE70) void SET_PED_DESIRED_HEADING(Ped ped, float heading)l
extern _native64(0xFF287323B0E2C69A) void FORCE_ALL_HEADING_VALUES_TO_ALIGN(Ped ped)l
extern _native64(0xD71649DB0A545AA3) bool IS_PED_FACING_PED(Ped ped, Ped otherPed, float angle)l
extern _native64(0x4E209B2C1EAD5159) bool IS_PED_IN_MELEE_COMBAT(Ped ped)l
extern _native64(0x530944F6F4B8A214) bool IS_PED_STOPPED(Ped ped)l
extern _native64(0x7E9DFE24AC1E58EF) bool IS_PED_SHOOTING_IN_AREA(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8)l
extern _native64(0xA0D3D71EA1086C55) bool IS_ANY_PED_SHOOTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7)l
extern _native64(0x34616828CD07F1A1) bool IS_PED_SHOOTING(Ped ped)l
extern _native64(0x7AEFB85C1D49DEB6) void SET_PED_ACCURACY(Ped ped, int accuracy)l
extern _native64(0x37F4AD56ECBC0CD6) int GET_PED_ACCURACY(Ped ped)l
extern _native64(0x87DDEB611B329A9C) void SET_AMBIENT_LAW_PED_ACCURACY_MODIFIER(float multiplier)l
extern _native64(0xC9D55B1A358A5BF7) bool IS_PED_MODEL(Ped ped, Hash modelHash)l
extern _native64(0x2D05CED3A38D0F3A) void EXPLODE_PED_HEAD(Ped ped, Hash weaponHash)l
extern _native64(0xAC6D445B994DF95E) void REMOVE_PED_ELEGANTLY(Ped* ped)l
extern _native64(0x5BA652A0CD14DF2F) void ADD_ARMOUR_TO_PED(Ped ped, int amount)l
extern _native64(0xCEA04D83135264CC) void SET_PED_ARMOUR(Ped ped, int amount)l
extern _native64(0xF75B0D629E1C063D) void SET_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seatIndex)l
extern _native64(0x3C028C636A414ED9) void SET_PED_ALLOW_VEHICLES_OVERRIDE(Ped ped, bool toggle)l
extern _native64(0x3E8349C08E4B82E4) bool CAN_CREATE_RANDOM_PED(bool p0)l
extern _native64(0xB4AC7D0CF06BFE8F) Ped CREATE_RANDOM_PED(float posX, float posY, float posZ)l
extern _native64(0x9B62392B474F44A0) Ped CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicle, bool returnHandle)l
extern _native64(0xB8EB95E5B4E56978) bool CAN_CREATE_RANDOM_DRIVER()l
extern _native64(0xEACEEDA81751915C) bool CAN_CREATE_RANDOM_BIKE_RIDER()l
extern _native64(0x9E8C908F41584ECD) void SET_PED_MOVE_ANIMS_BLEND_OUT(Ped ped)l
extern _native64(0xC1670E958EEE24E5) void SET_PED_CAN_BE_DRAGGED_OUT(Ped ped, bool toggle)l
extern _native64(0xF2BEBCDFAFDAA19E) void SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS(bool toggle)l
extern _native64(0x6D9F5FAA7488BA46) bool IS_PED_MALE(Ped ped)l
extern _native64(0xB980061DA992779D) bool IS_PED_HUMAN(Ped ped)l
extern _native64(0x9A9112A0FE9A4713) Vehicle GET_VEHICLE_PED_IS_IN(Ped ped, bool includeEntering)l
extern _native64(0xBB8DE8CF6A8DD8BB) void RESET_PED_LAST_VEHICLE(Ped ped)l
extern _native64(0x95E3D6257B166CF2) void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0x7A556143A1C03898) void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0, float p1)l
extern _native64(0x5A7F62FDA59759BD) void SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME()l
extern _native64(0x5086C7843552CF85) void SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(float x, float y, float z)l
extern _native64(0xEE01041D559983EA) void SET_PED_NON_CREATION_AREA(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x2E05208086BA0651) void CLEAR_PED_NON_CREATION_AREA()l
extern _native64(0x4759CC730F947C81) void INSTANTLY_FILL_PED_POPULATION()l
extern _native64(0x460BC76A0E10655E) bool IS_PED_ON_MOUNT(Ped ped)l
extern _native64(0xE7E11B8DCBED1058) Ped GET_MOUNT(Ped ped)l
extern _native64(0x67722AEB798E5FAB) bool IS_PED_ON_VEHICLE(Ped ped)l
extern _native64(0xEC5F66E459AF3BB2) bool IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle vehicle)l
extern _native64(0xA9C8960E8684C1B5) void SET_PED_MONEY(Ped ped, int amount)l
extern _native64(0x3F69145BBA87BAE7) int GET_PED_MONEY(Ped ped)l
extern _native64(0xFF4803BC019852D9) void SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS(float p0, any p1)l
extern _native64(0x6B0E6172C9A4D902) void SET_AMBIENT_PEDS_DROP_MONEY(bool p0)l
extern _native64(0x9911F4A24485F653) void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME(bool p0)l
extern _native64(0xEBD76F2359F190AC) void SET_PED_SUFFERS_CRITICAL_HITS(Ped ped, bool toggle)l
extern _native64(0xAFC976FD0580C7B3) void SET_PED_UPPER_BODY_DAMAGE_ONLY(Ped ped, bool toggle)l
extern _native64(0xA808AA1D79230FC2) bool IS_PED_SITTING_IN_VEHICLE(Ped ped, Vehicle vehicle)l
extern _native64(0x826AA586EDB9FEF8) bool IS_PED_SITTING_IN_ANY_VEHICLE(Ped ped)l
extern _native64(0x01FEE67DB37F59B2) bool IS_PED_ON_FOOT(Ped ped)l
extern _native64(0x94495889E22C6479) bool IS_PED_ON_ANY_BIKE(Ped ped)l
extern _native64(0xC70B5FAE151982D8) bool IS_PED_PLANTING_BOMB(Ped ped)l
extern _native64(0xCD5003B097200F36) vector3 GET_DEAD_PED_PICKUP_COORDS(Ped ped, float p1, float p2)l
extern _native64(0x2E0E1C2B4F6CB339) bool IS_PED_IN_ANY_BOAT(Ped ped)l
extern _native64(0xFBFC01CCFB35D99E) bool IS_PED_IN_ANY_SUB(Ped ped)l
extern _native64(0x298B91AE825E5705) bool IS_PED_IN_ANY_HELI(Ped ped)l
extern _native64(0x5FFF4CFC74D8FB80) bool IS_PED_IN_ANY_PLANE(Ped ped)l
extern _native64(0x9134873537FA419C) bool IS_PED_IN_FLYING_VEHICLE(Ped ped)l
extern _native64(0x56CEF0AC79073BDE) void SET_PED_DIES_IN_WATER(Ped ped, bool toggle)l
extern _native64(0x65671A4FB8218930) bool GET_PED_DIES_IN_WATER(Ped ped)l
extern _native64(0xD718A22995E2B4BC) void SET_PED_DIES_IN_SINKING_VEHICLE(Ped ped, bool toggle)l
extern _native64(0x9483AF821605B1D8) int GET_PED_ARMOUR(Ped ped)l
extern _native64(0xEDF4079F9D54C9A1) void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(Ped ped, bool toggle)l
extern _native64(0xC7EF1BA83230BA07) void SET_PED_CAN_BE_SHOT_IN_VEHICLE(Ped ped, bool toggle)l
extern _native64(0xD75960F6BD9EA49C) bool GET_PED_LAST_DAMAGE_BONE(Ped ped, int* outBone)l
extern _native64(0x8EF6B7AC68E2F01B) void CLEAR_PED_LAST_DAMAGE_BONE(Ped ped)l
extern _native64(0x1B1E2A40A65B8521) void SET_AI_WEAPON_DAMAGE_MODIFIER(float value)l
extern _native64(0xEA16670E7BA4743C) void RESET_AI_WEAPON_DAMAGE_MODIFIER()l
extern _native64(0x66460DEDDD417254) void SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(float modifier)l
extern _native64(0x46E56A7CD1D63C3F) void RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER()l
extern _native64(0x2F3C3D9F50681DE4) void SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON(Ped ped, bool p1)l
extern _native64(0x63F58F7C80513AAD) void SET_PED_CAN_BE_TARGETTED(Ped ped, bool toggle)l
extern _native64(0xBF1CA77833E58F2C) void SET_PED_CAN_BE_TARGETTED_BY_TEAM(Ped ped, int team, bool toggle)l
extern _native64(0x66B57B72E0836A76) void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Ped ped, Player player, bool toggle)l
extern _native64(0x061CB768363D6424) void SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY(Ped ped, bool toggle)l
extern _native64(0xFD325494792302D7) void SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST(Ped ped, bool toggle)l
extern _native64(0x0BD04E29640C9C12) bool IS_PED_IN_ANY_POLICE_VEHICLE(Ped ped)l
extern _native64(0x16E42E800B472221) void FORCE_PED_TO_OPEN_PARACHUTE(Ped ped)l
extern _native64(0x7DCE8BDA0F1C1200) bool IS_PED_IN_PARACHUTE_FREE_FALL(Ped ped)l
extern _native64(0xFB92A102F1C4DFA3) bool IS_PED_FALLING(Ped ped)l
extern _native64(0xCEDABC5900A0BF97) bool IS_PED_JUMPING(Ped ped)l
extern _native64(0x412F1364FA066CFB) bool IS_PED_LANDING(any p0)l
extern _native64(0x451D05012CCEC234) bool IS_PED_DOING_A_BEAST_JUMP(any p0)l
extern _native64(0x53E8CB4F48BFE623) bool IS_PED_CLIMBING(Ped ped)l
extern _native64(0x117C70D1F5730B5E) bool IS_PED_VAULTING(Ped ped)l
extern _native64(0x5527B8246FEF9B11) bool IS_PED_DIVING(Ped ped)l
extern _native64(0x433DDFFE2044B636) bool IS_PED_JUMPING_OUT_OF_VEHICLE(Ped ped)l
extern _native64(0x26AF0E8E30BD2A2C) bool IS_PED_OPENING_DOOR(Ped ped)l
extern _native64(0x79CFD9827CC979B6) int GET_PED_PARACHUTE_STATE(Ped ped)l
extern _native64(0x8B9F1FC6AE8166C0) int GET_PED_PARACHUTE_LANDING_TYPE(Ped ped)l
extern _native64(0x333FC8DB079B7186) void SET_PED_PARACHUTE_TINT_INDEX(Ped ped, int tintIndex)l
extern _native64(0xEAF5F7E5AE7C6C9D) void GET_PED_PARACHUTE_TINT_INDEX(Ped ped, int* outTintIndex)l
extern _native64(0xE88DA0751C22A2AD) void SET_PED_RESERVE_PARACHUTE_TINT_INDEX(Ped ped, any p1)l
extern _native64(0x8C4F3BF23B6237DB) Object CREATE_PARACHUTE_BAG_OBJECT(Ped ped, bool p1, bool p2)l
extern _native64(0x030983CA930B692D) void SET_PED_DUCKING(Ped ped, bool toggle)l
extern _native64(0xD125AE748725C6BC) bool IS_PED_DUCKING(Ped ped)l
extern _native64(0x6E575D6A898AB852) bool IS_PED_IN_ANY_TAXI(Ped ped)l
extern _native64(0xF107E836A70DCE05) void SET_PED_ID_RANGE(Ped ped, float value)l
extern _native64(0x52D59AB61DDC05DD) void SET_PED_HIGHLY_PERCEPTIVE(Ped ped, bool toggle)l
extern _native64(0x2F074C904D85129E) void SET_COP_PERCEPTION_OVERRIDES(float seeingRange, float seeingRangePeripheral, float hearingRange, float visualFieldMinAzimuthAngle, float visualFieldMaxAzimuthAngle, float fieldOfGazeMaxAngle, float p6)l
extern _native64(0xEC4B4B3B9908052A) void SET_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped, float p1)l
extern _native64(0x733C87D4CE22BEA2) void DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped)l
extern _native64(0xF29CF591C4BF6CEE) void SET_PED_SEEING_RANGE(Ped ped, float value)l
extern _native64(0x33A8F7F7D5F7F33C) void SET_PED_HEARING_RANGE(Ped ped, float value)l
extern _native64(0x2DB492222FB21E26) void SET_PED_VISUAL_FIELD_MIN_ANGLE(Ped ped, float value)l
extern _native64(0x70793BDCA1E854D4) void SET_PED_VISUAL_FIELD_MAX_ANGLE(Ped ped, float value)l
extern _native64(0x7A276EB2C224D70F) void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Ped ped, float angle)l
extern _native64(0x78D0B67629D75856) void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Ped ped, float angle)l
extern _native64(0x9C74B0BC831B753A) void SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Ped ped, float range)l
extern _native64(0x3B6405E8AB34A907) void SET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped, float angle)l
extern _native64(0xEF2C71A32CAD5FBD) float GET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped)l
extern _native64(0x88CBB5CEB96B7BD2) void SET_PED_STEALTH_MOVEMENT(Ped ped, bool p1, const char* action)l
extern _native64(0x7C2AC9CA66575FBF) bool GET_PED_STEALTH_MOVEMENT(Ped ped)l
extern _native64(0x90370EBE0FEE1A3D) int CREATE_GROUP(int unused)l
extern _native64(0x2A7819605465FBCE) void SET_PED_AS_GROUP_LEADER(Ped ped, int groupId)l
extern _native64(0x9F3480FE65DB31B5) void SET_PED_AS_GROUP_MEMBER(Ped ped, int groupId)l
extern _native64(0x2E2F4240B3F24647) void SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(Ped pedHandle, int groupHandle, bool toggle)l
extern _native64(0x8EB2F69076AF7053) void REMOVE_GROUP(int groupId)l
extern _native64(0xED74007FFB146BC2) void REMOVE_PED_FROM_GROUP(Ped ped)l
extern _native64(0x9BB01E3834671191) bool IS_PED_GROUP_MEMBER(Ped ped, int groupId)l
extern _native64(0x1C86D8AEF8254B78) bool IS_PED_HANGING_ON_TO_VEHICLE(Ped ped)l
extern _native64(0x4102C7858CFEE4E4) void SET_GROUP_SEPARATION_RANGE(int groupHandle, float separationRange)l
extern _native64(0xFA0675AB151073FA) void SET_PED_MIN_GROUND_TIME_FOR_STUNGUN(Ped ped, int ms)l
extern _native64(0xD6A86331A537A7B9) bool IS_PED_PRONE(Ped ped)l
extern _native64(0x4859F1FC66A6278E) bool IS_PED_IN_COMBAT(Ped ped, Ped target)l
extern _native64(0x32C27A11307B01CC) Entity GET_PED_TARGET_FROM_COMBAT_PED(Ped ped, any p1)l
extern _native64(0xEAD42DE3610D0721) bool CAN_PED_IN_COMBAT_SEE_TARGET(Ped ped, Ped target)l
extern _native64(0xB2C086CC1BF8F2BF) bool IS_PED_DOING_DRIVEBY(Ped ped)l
extern _native64(0x4AE4FF911DFB61DA) bool IS_PED_JACKING(Ped ped)l
extern _native64(0x9A497FE2DF198913) bool IS_PED_BEING_JACKED(Ped ped)l
extern _native64(0x4FBACCE3B4138EE8) bool IS_PED_BEING_STUNNED(Ped ped, int p1)l
extern _native64(0x9B128DC36C1E04CF) Ped GET_PEDS_JACKER(Ped ped)l
extern _native64(0x5486A79D9FBD342D) Ped GET_JACK_TARGET(Ped ped)l
extern _native64(0xBBCCE00B381F8482) bool IS_PED_FLEEING(Ped ped)l
extern _native64(0x60DFD0691A170B88) bool IS_PED_IN_COVER(Ped ped, bool exceptUseWeapon)l
extern _native64(0x845333B3150583AB) bool IS_PED_IN_COVER_FACING_LEFT(Ped ped)l
extern _native64(0x6A03BF943D767C93) bool IS_PED_IN_HIGH_COVER(Ped ped)l
extern _native64(0x9F65DBC537E59AD5) bool IS_PED_GOING_INTO_COVER(Ped ped)l
extern _native64(0xAAD6D1ACF08F4612) bool SET_PED_PINNED_DOWN(Ped ped, bool pinned, int i)l
extern _native64(0x6F4C85ACD641BCD2) int GET_SEAT_PED_IS_TRYING_TO_ENTER(Ped ped)l
extern _native64(0x814FA8BE5449445D) Vehicle GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Ped ped)l
extern _native64(0x93C8B64DEB84728C) Entity GET_PED_SOURCE_OF_DEATH(Ped ped)l
extern _native64(0x16FFE42AB2D2DC59) Hash GET_PED_CAUSE_OF_DEATH(Ped ped)l
extern _native64(0x1E98817B311AE98A) int GET_PED_TIME_OF_DEATH(Ped ped)l
extern _native64(0x5407B7288D0478B7) int COUNT_PEDS_IN_COMBAT_WITH_TARGET(Ped ped)l
extern _native64(0x336B3D200AB007CB) int COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS(Ped ped, float x, float y, float z, float radius)l
extern _native64(0xADB3F206518799E8) void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped, Hash hash)l
extern _native64(0xC80A74AC829DDD92) void SET_PED_RELATIONSHIP_GROUP_HASH(Ped ped, Hash hash)l
extern _native64(0xBF25EB89375A37AD) void SET_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)l
extern _native64(0x5E29243FB56FC6D4) void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)l
extern _native64(0xF372BC22FCB88606) bool ADD_RELATIONSHIP_GROUP(const char* name, Hash* groupHash)l
extern _native64(0xB6BA2444AB393DA2) void REMOVE_RELATIONSHIP_GROUP(Hash groupHash)l
extern _native64(0xCC6E3B6BB69501F1) bool DOES_RELATIONSHIP_GROUP_EXIST(Hash groupHash)l
extern _native64(0xEBA5AD3A0EAF7121) int GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2)l
extern _native64(0x42FDD0F017B1E38E) Hash GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped)l
extern _native64(0x7DBDD04862D95F04) Hash GET_PED_RELATIONSHIP_GROUP_HASH(Ped ped)l
extern _native64(0x9E6B70061662AE5C) int GET_RELATIONSHIP_BETWEEN_GROUPS(Hash group1, Hash group2)l
extern _native64(0x5615E0C5EB2BC6E2) void SET_RELATIONSHIP_GROUP_AFFECTS_WANTED_LEVEL(Hash group, bool p1)l
extern _native64(0xAD27D957598E49E9) void TELL_GROUP_PEDS_IN_AREA_TO_ATTACK(Ped ped, any p1, float p2, Hash hash, any p4, any p5)l
extern _native64(0x4328652AE5769C71) void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Ped ped, bool toggle)l
extern _native64(0x112942C6E708F70B) void SET_PED_TO_INFORM_RESPECTED_FRIENDS(Ped ped, float radius, int maxFriends)l
extern _native64(0x625B774D75C87068) bool IS_PED_RESPONDING_TO_EVENT(Ped ped, any event)l
extern _native64(0xBA656A3BB01BDEA3) bool GET_POS_FROM_FIRED_EVENT(Ped ped, int eventType, any* outData)l
extern _native64(0x9AC577F5A12AD8A9) void SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash)l
extern _native64(0x614DA022990752DC) void SET_PED_SHOOT_RATE(Ped ped, int shootRate)l
extern _native64(0xFF41B4B141ED981C) void SET_COMBAT_FLOAT(Ped ped, int combatType, float p2)l
extern _native64(0x52DFF8A10508090A) float GET_COMBAT_FLOAT(Ped ped, int p1)l
extern _native64(0x8DE69FE35CA09A45) void GET_GROUP_SIZE(int groupID, any* p1, int* sizeInMembers)l
extern _native64(0x7C6B0C22F9F40BBE) bool DOES_GROUP_EXIST(int groupId)l
extern _native64(0xF162E133B4E7A675) int GET_PED_GROUP_INDEX(Ped ped)l
extern _native64(0x5891CAC5D4ACFF74) bool IS_PED_IN_GROUP(Ped ped)l
extern _native64(0x6A3975DEA89F9A17) Player GET_PLAYER_PED_IS_FOLLOWING(Ped ped)l
extern _native64(0xCE2F5FC3AF7E8C1E) void SET_GROUP_FORMATION(int groupId, int formationType)l
extern _native64(0x1D9D45004C28C916) void SET_GROUP_FORMATION_SPACING(int groupId, float x, float y, float z)l
extern _native64(0x63DAB4CCB3273205) void RESET_GROUP_FORMATION_DEFAULT_SPACING(int groupHandle)l
extern _native64(0x6094AD011A2EA87D) Vehicle GET_VEHICLE_PED_IS_USING(Ped ped)l
extern _native64(0xF92691AED837A5FC) Vehicle GET_VEHICLE_PED_IS_ENTERING(Ped ped)l
extern _native64(0x9FF447B6B6AD960A) void SET_PED_GRAVITY(Ped ped, bool toggle)l
extern _native64(0x697157CED63F18D4) void APPLY_DAMAGE_TO_PED(Ped ped, int damageAmount, bool p2, any p3)l
extern _native64(0x36B77BB84687C318) int GET_TIME_PED_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash)l
extern _native64(0xDA1F1B7BE1A8766F) void SET_PED_ALLOWED_TO_DUCK(Ped ped, bool toggle)l
extern _native64(0x3DBFC55D5C9BB447) void SET_PED_NEVER_LEAVES_GROUP(Ped ped, bool toggle)l
extern _native64(0xFF059E1E4C01E63C) int GET_PED_TYPE(Ped ped)l
extern _native64(0xBB03C38DD3FB7FFD) void SET_PED_AS_COP(Ped ped, bool toggle)l
extern _native64(0xB3352E018D6F89DF) void SET_PED_HEALTH_PENDING_LAST_DAMAGE_EVENT_OVERRIDE_FLAG(bool toggle)l
extern _native64(0xF5F6378C4F3419D3) void SET_PED_MAX_HEALTH(Ped ped, int value)l
extern _native64(0x4700A416E8324EF3) int GET_PED_MAX_HEALTH(Ped ped)l
extern _native64(0x43C851690662113D) void SET_PED_MAX_TIME_IN_WATER(Ped ped, float value)l
extern _native64(0x6BA428C528D9E522) void SET_PED_MAX_TIME_UNDERWATER(Ped ped, float value)l
extern _native64(0x2735233A786B1BEF) void SET_CORPSE_RAGDOLL_FRICTION(Ped ped, float p1)l
extern _native64(0x952F06BEECD775CC) void SET_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped, Vehicle vehicle, int seatIndex, int flags, any p4)l
extern _native64(0xE6CA85E7259CE16B) void CLEAR_ALL_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped)l
extern _native64(0xB282749D5E028163) void SET_PED_CAN_BE_KNOCKED_OFF_BIKE(any p0, any p1)l
extern _native64(0x7A6535691B477C48) void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped ped, int state)l
extern _native64(0x51AC07A44D4F5B8A) bool CAN_KNOCK_PED_OFF_VEHICLE(Ped ped)l
extern _native64(0x45BBCBA77C29A841) void KNOCK_PED_OFF_VEHICLE(Ped ped)l
extern _native64(0x87052FE446E07247) void SET_PED_COORDS_NO_GANG(Ped ped, float posX, float posY, float posZ)l
extern _native64(0x51455483CF23ED97) Ped GET_PED_AS_GROUP_MEMBER(int groupID, int memberNumber)l
extern _native64(0x5CCE68DBD5FE93EC) Ped GET_PED_AS_GROUP_LEADER(int groupID)l
extern _native64(0x971D38760FBC02EF) void SET_PED_KEEP_TASK(Ped ped, bool toggle)l
extern _native64(0x49E50BDB8BA4DAB2) void SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED(Ped ped, bool toggle)l
extern _native64(0x9DE327631295B4C2) bool IS_PED_SWIMMING(Ped ped)l
extern _native64(0xC024869A53992F34) bool IS_PED_SWIMMING_UNDER_WATER(Ped ped)l
extern _native64(0x9AFEFF481A85AB2E) void SET_PED_COORDS_KEEP_VEHICLE(Ped ped, float posX, float posY, float posZ)l
extern _native64(0x2A30922C90C9B42C) void SET_PED_DIES_IN_VEHICLE(Ped ped, bool toggle)l
extern _native64(0x102E68B2024D536D) void SET_CREATE_RANDOM_COPS(bool toggle)l
extern _native64(0x8A4986851C4EF6E7) void SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(bool toggle)l
extern _native64(0x444CB7D7DBE6973D) void SET_CREATE_RANDOM_COPS_ON_SCENARIOS(bool toggle)l
extern _native64(0x5EE2CAFF7F17770D) bool CAN_CREATE_RANDOM_COPS()l
extern _native64(0x02A0C9720B854BFA) void SET_PED_AS_ENEMY(Ped ped, bool toggle)l
extern _native64(0x1CCE141467FF42A2) void SET_PED_CAN_SMASH_GLASS(Ped ped, bool p1, bool p2)l
extern _native64(0x6F972C1AB75A1ED0) bool IS_PED_IN_ANY_TRAIN(Ped ped)l
extern _native64(0xBB062B2B5722478E) bool IS_PED_GETTING_INTO_A_VEHICLE(Ped ped)l
extern _native64(0x44D28D5DDFE5F68C) bool IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(Ped ped)l
extern _native64(0xDF1AF8B5D56542FA) void SET_ENABLE_HANDCUFFS(Ped ped, bool toggle)l
extern _native64(0xC52E0F855C58FC2E) void SET_ENABLE_BOUND_ANKLES(Ped ped, bool toggle)l
extern _native64(0xF99F62004024D506) void SET_ENABLE_SCUBA(Ped ped, bool toggle)l
extern _native64(0xB3B1CB349FF9C75D) void SET_CAN_ATTACK_FRIENDLY(Ped ped, bool toggle, bool p2)l
extern _native64(0xF6AA118530443FD2) int GET_PED_ALERTNESS(Ped ped)l
extern _native64(0xDBA71115ED9941A6) void SET_PED_ALERTNESS(Ped ped, int value)l
extern _native64(0xBC0ED94165A48BC2) void SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(Ped ped, bool toggle)l
extern _native64(0xAF8A94EDE7712BEF) void SET_PED_MOVEMENT_CLIPSET(Ped ped, const char* clipSet, float transitionSpeed)l
extern _native64(0xAA74EC0CB0AAEA2C) void RESET_PED_MOVEMENT_CLIPSET(Ped ped, float p1)l
extern _native64(0x29A28F3F8CF6D854) void SET_PED_STRAFE_CLIPSET(Ped ped, const char* clipSet)l
extern _native64(0x20510814175EA477) void RESET_PED_STRAFE_CLIPSET(Ped ped)l
extern _native64(0x2622E35B77D3ACA2) void SET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped, const char* clipSet)l
extern _native64(0x97B0DB5B4AA74E77) void RESET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped)l
extern _native64(0xED34AB6C5CB36520) void SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped, const char* clipset)l
extern _native64(0x4AFE3690D7E0B5AC) void CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped)l
extern _native64(0x9DBA107B4937F809) void SET_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped, const char* p1)l
extern _native64(0xC79196DCB36F6121) void CLEAR_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped)l
extern _native64(0x80054D7FCC70EEC6) void CLEAR_PED_FALL_UPPER_BODY_CLIPSET_OVERRIDE(Ped ped)l
extern _native64(0x530071295899A8C6) void SET_PED_IN_VEHICLE_CONTEXT(Ped ped, Hash context)l
extern _native64(0x22EF8FF8778030EB) void RESET_PED_IN_VEHICLE_CONTEXT(Ped ped)l
extern _native64(0x6EC47A344923E1ED) bool IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(Ped ped, const char* animDict, const char* anim)l
extern _native64(0x6C60394CB4F75E9A) void SET_PED_ALTERNATE_WALK_ANIM(Ped ped, const char* animDict, const char* animName, float p3, bool p4)l
extern _native64(0x8844BBFCE30AA9E9) void CLEAR_PED_ALTERNATE_WALK_ANIM(Ped ped, float p1)l
extern _native64(0x90A43CC281FFAB46) void SET_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, const char* animDictionary, const char* animationName, float p4, bool p5)l
extern _native64(0xD8D19675ED5FBDCE) void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, float p2)l
extern _native64(0xDDF803377F94AAA8) void SET_PED_GESTURE_GROUP(Ped ped, const char* animGroupGesture)l
extern _native64(0xBE22B26DD764C040) vector3 GET_ANIM_INITIAL_OFFSET_POSITION(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9)l
extern _native64(0x4B805E6046EE9E47) vector3 GET_ANIM_INITIAL_OFFSET_ROTATION(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9)l
extern _native64(0x67F3780DD425D4FC) int GET_PED_DRAWABLE_VARIATION(Ped ped, int componentId)l
extern _native64(0x27561561732A7842) int GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped ped, int componentId)l
extern _native64(0x04A355E041E004E6) int GET_PED_TEXTURE_VARIATION(Ped ped, int componentId)l
extern _native64(0x8F7156A3142A6BAD) int GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped ped, int componentId, int drawableId)l
extern _native64(0x5FAF9754E789FB47) int GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Ped ped, int propId)l
extern _native64(0xA6E7F1CEB523E171) int GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Ped ped, int propId, int drawableId)l
extern _native64(0xE3DD5F2A84B42281) int GET_PED_PALETTE_VARIATION(Ped ped, int componentId)l
extern _native64(0x9E30E91FB03A2CAF) bool GET_MP_OUTFIT_DATA_FROM_METADATA(any* p0, any* p1)l
extern _native64(0x1E77FA7A62EE6C4C) int GET_FM_MALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0)l
extern _native64(0xF033419D1B81FAE8) int GET_FM_FEMALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0)l
extern _native64(0xE825F6B6CEA7671D) bool IS_PED_COMPONENT_VARIATION_VALID(Ped ped, int componentId, int drawableId, int textureId)l
extern _native64(0x262B14F48D29DE80) void SET_PED_COMPONENT_VARIATION(Ped ped, int componentId, int drawableId, int textureId, int paletteId)l
extern _native64(0xC8A9481A01E63C28) void SET_PED_RANDOM_COMPONENT_VARIATION(Ped ped, int p1)l
extern _native64(0xC44AA05345C992C6) void SET_PED_RANDOM_PROPS(Ped ped)l
extern _native64(0x45EEE61580806D63) void SET_PED_DEFAULT_COMPONENT_VARIATION(Ped ped)l
extern _native64(0x137BBD05230DB22D) void SET_PED_BLEND_FROM_PARENTS(Ped ped, any p1, any p2, float p3, float p4)l
extern _native64(0x9414E18B9434C2FE) void SET_PED_HEAD_BLEND_DATA(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, bool isParent)l
extern _native64(0x2746BD9D88C5C5D0) bool GET_PED_HEAD_BLEND_DATA(Ped ped, any* headBlendData)l
extern _native64(0x723538F61C647C5A) void UPDATE_PED_HEAD_BLEND_DATA(Ped ped, float shapeMix, float skinMix, float thirdMix)l
extern _native64(0x50B56988B170AFDF) void SET_HEAD_BLEND_EYE_COLOR(Ped ped, int index)l
extern _native64(0x76BBA2CEE66D47E9) int GET_HEAD_BLEND_EYE_COLOR(Ped ped)l
extern _native64(0x48F44967FA05CC1E) void SET_PED_HEAD_OVERLAY(Ped ped, int overlayID, int index, float opacity)l
extern _native64(0xA60EF3B6461A4D43) int GET_PED_HEAD_OVERLAY(Ped ped, int overlayID)l
extern _native64(0xCF1CE768BB43480E) int GET_PED_HEAD_OVERLAY_NUM(int overlayID)l
extern _native64(0x497BF74A7B9CB952) void SET_PED_HEAD_OVERLAY_TINT(Ped ped, int overlayID, int colorType, int colorID, int secondColorID)l
extern _native64(0x4CFFC65454C93A49) void SET_PED_HAIR_TINT(Ped ped, int colorID, int highlightColorID)l
extern _native64(0xE5C0CF872C2AD150) int GET_NUM_PED_HAIR_TINTS()l
extern _native64(0xD1F7CA1535D22818) int GET_NUM_PED_MAKEUP_TINTS()l
extern _native64(0x4852FC386E2E1BB5) void GET_PED_HAIR_TINT_COLOR(int hairColorIndex, int* outR, int* outG, int* outB)l
extern _native64(0x013E5CFC38CD5387) void GET_PED_MAKEUP_TINT_COLOR(int makeupColorIndex, int* outR, int* outG, int* outB)l
extern _native64(0xED6D8E27A43B8CDE) bool IS_PED_HAIR_TINT_FOR_CREATOR(int colorId)l
extern _native64(0xEA9960D07DADCF10) int GET_DEFAULT_SECONDARY_TINT_FOR_CREATOR(int colorId)l
extern _native64(0x3E802F11FBE27674) bool IS_PED_LIPSTICK_TINT_FOR_CREATOR(int colorId)l
extern _native64(0xF41B5D290C99A3D6) bool IS_PED_BLUSH_TINT_FOR_CREATOR(int colorId)l
extern _native64(0xE0D36E5D9E99CC21) bool IS_PED_HAIR_TINT_FOR_BARBER(int colorID)l
extern _native64(0xAAA6A3698A69E048) int GET_DEFAULT_SECONDARY_TINT_FOR_BARBER(int colorID)l
extern _native64(0x0525A2C2562F3CD4) bool IS_PED_LIPSTICK_TINT_FOR_BARBER(int colorID)l
extern _native64(0x604E810189EE3A59) bool IS_PED_BLUSH_TINT_FOR_BARBER(int colorID)l
extern _native64(0x09E7ECA981D9B210) bool IS_PED_BLUSH_FACEPAINT_TINT_FOR_BARBER(int colorId)l
extern _native64(0xC56FBF2F228E1DAC) int GET_TINT_INDEX_FOR_LAST_GEN_HAIR_TEXTURE(Hash modelHash, int drawableId, int textureId)l
extern _native64(0x71A5C1DBA060049E) void SET_PED_MICRO_MORPH(Ped ped, int index, float scale)l
extern _native64(0x654CD0A825161131) bool HAS_PED_HEAD_BLEND_FINISHED(Ped ped)l
extern _native64(0x4668D80430D6C299) void FINALIZE_HEAD_BLEND(Ped ped)l
extern _native64(0xCC9682B8951C5229) void SET_HEAD_BLEND_PALETTE_COLOR(Ped ped, int r, int g, int b, int id)l
extern _native64(0xA21C118553BBDF02) void DISABLE_HEAD_BLEND_PALETTE_COLOR(Ped ped)l
extern _native64(0x68D353AB88B97E0C) int GET_PED_HEAD_BLEND_FIRST_INDEX(int type)l
extern _native64(0x5EF37013A6539C9D) int GET_PED_HEAD_BLEND_NUM_HEADS(int type)l
extern _native64(0x39D55A620FCB6A3A) int SET_PED_PRELOAD_VARIATION_DATA(Ped ped, int slot, int drawableId, int textureId)l
extern _native64(0x66680A92700F43DF) bool HAS_PED_PRELOAD_VARIATION_DATA_FINISHED(Ped ped)l
extern _native64(0x5AAB586FFEC0FD96) void RELEASE_PED_PRELOAD_VARIATION_DATA(Ped ped)l
extern _native64(0x2B16A3BFF1FBCE49) int SET_PED_PRELOAD_PROP_DATA(Ped ped, int componentId, int drawableId, int TextureId)l
extern _native64(0x784002A632822099) bool HAS_PED_PRELOAD_PROP_DATA_FINISHED(Ped ped)l
extern _native64(0xF79F9DEF0AADE61A) void RELEASE_PED_PRELOAD_PROP_DATA(Ped ped)l
extern _native64(0x898CC20EA75BACD8) int GET_PED_PROP_INDEX(Ped ped, int componentId, any p2)l
extern _native64(0x93376B65A266EB5F) void SET_PED_PROP_INDEX(Ped ped, int componentId, int drawableId, int TextureId, bool attach, any p5)l
extern _native64(0x6FD7816A36615F48) void KNOCK_OFF_PED_PROP(Ped ped, bool p1, bool p2, bool p3, bool p4)l
extern _native64(0x0943E5B8E078E76E) void CLEAR_PED_PROP(Ped ped, int propId, any p2)l
extern _native64(0xCD8A7537A9B52F06) void CLEAR_ALL_PED_PROPS(Ped ped, any p1)l
extern _native64(0xAFF4710E2A0A6C12) void DROP_AMBIENT_PROP(Ped ped)l
extern _native64(0xE131A28626F81AB2) int GET_PED_PROP_TEXTURE_INDEX(Ped ped, int componentId)l
extern _native64(0x1280804F7CFD2D6C) void CLEAR_PED_PARACHUTE_PACK_VARIATION(Ped ped)l
extern _native64(0x36C6984C3ED0C911) void SET_PED_SCUBA_GEAR_VARIATION(Ped ped)l
extern _native64(0xB50EB4CCB29704AC) void CLEAR_PED_SCUBA_GEAR_VARIATION(Ped ped)l
extern _native64(0xFEC9A3B1820F3331) bool IS_USING_PED_SCUBA_GEAR_VARIATION(any p0)l
extern _native64(0x9F8AA94D6D97DBF4) void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)l
extern _native64(0x4F5F651ACCC9C4CF) void SET_PED_BOUNDS_ORIENTATION(Ped ped, float p1, float p2, float x, float y, float z)l
extern _native64(0x2F25D9AEFA34FBA2) void REGISTER_TARGET(Ped ped, Ped target)l
extern _native64(0x9222F300BF8354FE) void REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius)l
extern _native64(0x876046A8E3A4B71C) Ped GET_RANDOM_PED_AT_COORD(float x, float y, float z, float xRadius, float yRadius, float zRadius, int pedType)l
extern _native64(0xC33AB876A77F8164) bool GET_CLOSEST_PED(float x, float y, float z, float radius, bool p4, bool p5, Ped* outPed, bool p7, bool p8, int pedType)l
extern _native64(0x14F19A8782C8071E) void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(bool value)l
extern _native64(0x03EA03AF85A85CB7) bool GET_CAN_PED_BE_GRABBED_BY_SCRIPT(Ped ped, bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, any p8)l
extern _native64(0xDED5AF5A0EA4B297) void SET_DRIVER_RACING_MODIFIER(Ped driver, float modifier)l
extern _native64(0xB195FFA8042FC5C3) void SET_DRIVER_ABILITY(Ped driver, float ability)l
extern _native64(0xA731F608CA104E3C) void SET_DRIVER_AGGRESSIVENESS(Ped driver, float aggressiveness)l
extern _native64(0x128F79EDCECE4FD5) bool CAN_PED_RAGDOLL(Ped ped)l
extern _native64(0xAE99FB955581844A) bool SET_PED_TO_RAGDOLL(Ped ped, int time1, int time2, int ragdollType, bool p4, bool p5, bool p6)l
extern _native64(0xD76632D99E4966C8) bool SET_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int time, int p2, int ragdollType, float x, float y, float z, float velocity, float p8, float p9, float p10, float p11, float p12, float p13)l
extern _native64(0xF0A4F1BBF4FA7497) void SET_PED_RAGDOLL_ON_COLLISION(Ped ped, bool toggle)l
extern _native64(0x47E4E977581C5B55) bool IS_PED_RAGDOLL(Ped ped)l
extern _native64(0xE3B6097CC25AA69E) bool IS_PED_RUNNING_RAGDOLL_TASK(Ped ped)l
extern _native64(0x01F6594B923B9251) void SET_PED_RAGDOLL_FORCE_FALL(Ped ped)l
extern _native64(0x9FA4664CF62E47E8) void RESET_PED_RAGDOLL_TIMER(Ped ped)l
extern _native64(0xB128377056A54E2A) void SET_PED_CAN_RAGDOLL(Ped ped, bool toggle)l
extern _native64(0xD1871251F3B5ACD7) bool IS_PED_RUNNING_MELEE_TASK(Ped ped)l
extern _native64(0x2AFE52F782F25775) bool IS_PED_RUNNING_MOBILE_PHONE_TASK(Ped ped)l
extern _native64(0xA3F3564A5B3646C0) bool IS_MOBILE_PHONE_TO_PED_EAR(Ped ped)l
extern _native64(0x26695EC767728D84) void SET_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag)l
extern _native64(0xD86D101FCFD00A4B) void CLEAR_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag)l
extern _native64(0xC7F76DF27A5045A1) void SET_PED_ANGLED_DEFENSIVE_AREA(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8, bool p9)l
extern _native64(0x9D3151A373974804) void SET_PED_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius, bool p5, bool p6)l
extern _native64(0xF9B8F91AAD3B953E) void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(Ped ped, Ped target, float xOffset, float yOffset, float zOffset, float radius, bool p6)l
extern _native64(0xE4723DB6E736CCFF) void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE(Ped ped, Vehicle target, float xOffset, float yOffset, float zOffset, float radius, bool p6)l
extern _native64(0x4EF47FE21698A8B6) void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9, bool p10)l
extern _native64(0x413C6C763A4AFFAD) void SET_PED_DEFENSIVE_AREA_DIRECTION(Ped ped, float p1, float p2, float p3, bool p4)l
extern _native64(0x74D4E028107450A9) void REMOVE_PED_DEFENSIVE_AREA(Ped ped, bool toggle)l
extern _native64(0x3C06B8786DD94CD1) vector3 GET_PED_DEFENSIVE_AREA_POSITION(Ped ped, bool p1)l
extern _native64(0xBA63D9FE45412247) bool IS_PED_DEFENSIVE_AREA_ACTIVE(Ped ped, bool p1)l
extern _native64(0x8421EB4DA7E391B9) void SET_PED_PREFERRED_COVER_SET(Ped ped, any itemSet)l
extern _native64(0xFDDB234CF74073D9) void REMOVE_PED_PREFERRED_COVER_SET(Ped ped)l
extern _native64(0x8D8ACD8388CD99CE) void REVIVE_INJURED_PED(Ped ped)l
extern _native64(0x71BC8E838B9C6035) void RESURRECT_PED(Ped ped)l
extern _native64(0x98EFA132A4117BE1) void SET_PED_NAME_DEBUG(Ped ped, const char* name)l
extern _native64(0xE0AF41401ADF87E3) vector3 GET_PED_EXTRACTED_DISPLACEMENT(Ped ped, bool worldSpace)l
extern _native64(0x5BA7919BED300023) void SET_PED_DIES_WHEN_INJURED(Ped ped, bool toggle)l
extern _native64(0x97A790315D3831FD) void SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, bool toggle)l
extern _native64(0xF9ACF4A08098EA25) void SPECIAL_FUNCTION_DO_NOT_USE(Ped ped, bool p1)l
extern _native64(0x3AC1F7B898F30C05) void RESET_PED_VISIBLE_DAMAGE(Ped ped)l
extern _native64(0x816F6981C60BF53B) void APPLY_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, any p1, float p2, float p3, any p4)l
extern _native64(0x83F7E01C7B769A26) void APPLY_PED_BLOOD(Ped ped, int boneIndex, float xRot, float yRot, float zRot, const char* woundType)l
extern _native64(0x3311E47B91EDCBBC) void APPLY_PED_BLOOD_BY_ZONE(Ped ped, int p1, float p2, float p3, const char* p4)l
extern _native64(0xEF0D582CBF2D9B0F) void APPLY_PED_BLOOD_SPECIFIC(Ped ped, int p1, float p2, float p3, float p4, float p5, int p6, float p7, const char* p8)l
extern _native64(0x397C38AA7B4A5F83) void APPLY_PED_DAMAGE_DECAL(Ped ped, int damageZone, float xOffset, float yOffset, float heading, float scale, float alpha, int variation, bool fadeIn, const char* decalName)l
extern _native64(0x46DF918788CB093F) void APPLY_PED_DAMAGE_PACK(Ped ped, const char* damagePack, float damage, float mult)l
extern _native64(0x8FE22675A5A45817) void CLEAR_PED_BLOOD_DAMAGE(Ped ped)l
extern _native64(0x56E3B78C5408D9F4) void CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, int p1)l
extern _native64(0x62AB793144DE75DC) void HIDE_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, any p1, bool p2)l
extern _native64(0x523C79AEEFCC4A2A) void CLEAR_PED_DAMAGE_DECAL_BY_ZONE(Ped ped, int p1, const char* p2)l
extern _native64(0x71EAB450D86954A1) int GET_PED_DECORATIONS_STATE(Ped ped)l
extern _native64(0x2B694AFCF64E6994) void MARK_PED_DECORATIONS_AS_CLONED_FROM_LOCAL_PLAYER(Ped ped, bool p1)l
extern _native64(0x9C720776DAA43E7E) void CLEAR_PED_WETNESS(Ped ped)l
extern _native64(0x44CB6447D2571AA0) void SET_PED_WETNESS_HEIGHT(Ped ped, float height)l
extern _native64(0xB5485E4907B53019) void SET_PED_WETNESS_ENABLED_THIS_FRAME(Ped ped)l
extern _native64(0xAC0BB4D87777CAE2) void SET_PED_WETNESS(Ped ped, float wetLevel)l
extern _native64(0x6585D955A68452A5) void CLEAR_PED_ENV_DIRT(Ped ped)l
extern _native64(0x27B0405F59637D1F) void SET_PED_SWEAT(Ped ped, float sweat)l
extern _native64(0x5F5D1665E352A839) void ADD_PED_DECORATION_FROM_HASHES(Ped ped, Hash collection, Hash overlay)l
extern _native64(0x5619BFA07CFD7833) void ADD_PED_DECORATION_FROM_HASHES_IN_CORONA(Ped ped, Hash collection, Hash overlay)l
extern _native64(0x9FD452BFBE7A7A8B) int GET_PED_DECORATION_ZONE_FROM_HASHES(Hash collection, Hash overlay)l
extern _native64(0x0E5173C163976E38) void CLEAR_PED_DECORATIONS(Ped ped)l
extern _native64(0xE3B27E70CEAB9F0C) void CLEAR_PED_DECORATIONS_LEAVE_SCARS(Ped ped)l
extern _native64(0x11B499C1E0FF8559) bool WAS_PED_SKELETON_UPDATED(Ped ped)l
extern _native64(0x17C07FC640E86B4E) vector3 GET_PED_BONE_COORDS(Ped ped, int boneId, float offsetX, float offsetY, float offsetZ)l
extern _native64(0x418EF2A1BCE56685) void CREATE_NM_MESSAGE(bool startImmediately, int messageId)l
extern _native64(0xB158DFCCC56E5C5B) void GIVE_PED_NM_MESSAGE(Ped ped)l
extern _native64(0x1B5C85C612E5256E) int ADD_SCENARIO_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7, bool p8, bool p9)l
extern _native64(0xD37401D78A929A49) void REMOVE_SCENARIO_BLOCKING_AREAS()l
extern _native64(0x31D16B74C6E29D66) void REMOVE_SCENARIO_BLOCKING_AREA(any p0, bool p1)l
extern _native64(0x28157D43CF600981) void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(float x, float y, float z, float range, int p4)l
extern _native64(0x8A24B067D175A7BD) bool DOES_SCENARIO_BLOCKING_AREA_EXISTS(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x1BF094736DD62C2E) bool IS_PED_USING_SCENARIO(Ped ped, const char* scenario)l
extern _native64(0x57AB4A3080F85143) bool IS_PED_USING_ANY_SCENARIO(Ped ped)l
extern _native64(0xFE07FF6495D52E2A) bool SET_PED_PANIC_EXIT_SCENARIO(any p0, any p1, any p2, any p3)l
extern _native64(0x9A77DFD295E29B09) void TOGGLE_SCENARIO_PED_COWER_IN_PLACE(Ped ped, bool toggle)l
extern _native64(0x25361A96E0F7E419) bool TRIGGER_PED_SCENARIO_PANICEXITTOFLEE(any p0, any p1, any p2, any p3)l
extern _native64(0xEC6935EBE0847B90) bool SET_PED_SHOULD_PLAY_DIRECTED_NORMAL_SCENARIO_EXIT(any p0, any p1, any p2, any p3)l
extern _native64(0xA3A9299C4F2ADB98) void SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT(Ped ped)l
extern _native64(0xF1C03A5352243A30) void SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT(Ped ped)l
extern _native64(0xEEED8FAFEC331A70) bool SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT(Ped ped, any p1, any p2, any p3)l
extern _native64(0x425AECF167663F48) void SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS(Ped ped, bool p1)l
extern _native64(0x5B6010B3CBC29095) void SET_PED_SHOULD_IGNORE_SCENARIO_NAV_CHECKS(any p0, bool p1)l
extern _native64(0xCEDA60A74219D064) void SET_PED_SHOULD_PROBE_FOR_SCENARIO_EXITS_IN_ONE_FRAME(any p0, bool p1)l
extern _native64(0xC30BDAEE47256C13) bool IS_PED_GESTURING(any p0)l
extern _native64(0x007FDE5A7897E426) void RESET_FACIAL_IDLE_ANIM(Ped ped)l
extern _native64(0xE1E65CA8AC9C00ED) void PLAY_FACIAL_ANIM(Ped ped, const char* animName, const char* animDict)l
extern _native64(0x5687C7F05B39E401) void SET_FACIAL_CLIPSET(Ped ped, const char* animDict)l
extern _native64(0xFFC24B988B938B38) void SET_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped, const char* animName, const char* animDict)l
extern _native64(0x726256CC1EEB182F) void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped)l
extern _native64(0xBAF20C5432058024) void SET_PED_CAN_PLAY_GESTURE_ANIMS(Ped ped, bool toggle)l
extern _native64(0xF833DDBA3B104D43) void SET_PED_CAN_PLAY_VISEME_ANIMS(Ped ped, bool toggle, bool p2)l
extern _native64(0x33A60D8BDD6E508C) void SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(Ped ped, bool p1)l
extern _native64(0x6373D1349925A70E) void SET_PED_CAN_PLAY_AMBIENT_ANIMS(Ped ped, bool toggle)l
extern _native64(0x0EB0585D15254740) void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Ped ped, bool toggle)l
extern _native64(0xC2EE020F5FB4DB53) void TRIGGER_IDLE_ANIMATION_ON_PED(Ped ped)l
extern _native64(0x6C3B4D6D13B4C841) void SET_PED_CAN_ARM_IK(Ped ped, bool toggle)l
extern _native64(0xC11C18092C5530DC) void SET_PED_CAN_HEAD_IK(Ped ped, bool toggle)l
extern _native64(0x73518ECE2485412B) void SET_PED_CAN_LEG_IK(Ped ped, bool toggle)l
extern _native64(0xF2B7106D37947CE0) void SET_PED_CAN_TORSO_IK(Ped ped, bool toggle)l
extern _native64(0xF5846EDB26A98A24) void SET_PED_CAN_TORSO_REACT_IK(Ped ped, bool p1)l
extern _native64(0x6647C5F6F5792496) void SET_PED_CAN_TORSO_VEHICLE_IK(Ped ped, bool p1)l
extern _native64(0xEC4686EC06434678) void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Ped ped, bool toggle)l
extern _native64(0x5CD3CB88A7F8850D) bool IS_PED_HEADTRACKING_PED(Ped ped1, Ped ped2)l
extern _native64(0x813A0A7C9D2E831F) bool IS_PED_HEADTRACKING_ENTITY(Ped ped, Entity entity)l
extern _native64(0xCD17B554996A8D9E) void SET_PED_PRIMARY_LOOKAT(Ped ped, Ped lookAt)l
extern _native64(0x78C4E9961DB3EB5B) void SET_PED_CLOTH_PIN_FRAMES(any p0, any p1)l
extern _native64(0x82A3D6D9CC2CB8E3) void SET_PED_CLOTH_PACKAGE_INDEX(any p0, any p1)l
extern _native64(0xA660FAF550EB37E5) void SET_PED_CLOTH_PRONE(any p0, bool p1)l
extern _native64(0x1913FE4CBF41C463) void SET_PED_CONFIG_FLAG(Ped ped, int flagId, bool value)l
extern _native64(0xC1E8A365BF3B29F2) void SET_PED_RESET_FLAG(Ped ped, int flagId, bool doReset)l
extern _native64(0x7EE53118C892B513) bool GET_PED_CONFIG_FLAG(Ped ped, int flagId, bool p2)l
extern _native64(0xAF9E59B1B1FBF2A0) bool GET_PED_RESET_FLAG(Ped ped, int flagId)l
extern _native64(0x0BDDB8D9EC6BCF3C) void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Ped ped, int index)l
extern _native64(0x6B7A646C242A7059) void SET_PED_CAN_EVASIVE_DIVE(Ped ped, bool toggle)l
extern _native64(0x414641C26E105898) bool IS_PED_EVASIVE_DIVING(Ped ped, Entity* evadingEntity)l
extern _native64(0x96A05E4FB321B1BA) void SET_PED_SHOOTS_AT_COORD(Ped ped, float x, float y, float z, bool toggle)l
extern _native64(0xE163A4BCE4DE6F11) void SET_PED_MODEL_IS_SUPPRESSED(Hash modelHash, bool toggle)l
extern _native64(0xB47BD05FA66B40CF) void STOP_ANY_PED_MODEL_BEING_SUPPRESSED()l
extern _native64(0x638C03B0F9878F57) void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Ped ped, bool toggle)l
extern _native64(0x7FB17BA2E7DECA5B) void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, bool toggle)l
extern _native64(0xE43A13C9E4CCCBCF) void BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD(Ped ped, bool toggle)l
extern _native64(0x3E9679C1DFCF422C) void SET_PED_WILL_ONLY_ATTACK_WANTED_PLAYER(any p0, any p1)l
extern _native64(0xDF993EE5E90ABA25) void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, bool toggle)l
extern _native64(0x54C7C4A94367717E) void GIVE_PED_HELMET(Ped ped, bool cannotRemove, int helmetFlag, int textureIndex)l
extern _native64(0xA7B2458D0AD6DED8) void REMOVE_PED_HELMET(Ped ped, bool instantly)l
extern _native64(0x14590DDBEDB1EC85) bool IS_PED_TAKING_OFF_HELMET(Ped ped)l
extern _native64(0x560A43136EB58105) void SET_PED_HELMET(Ped ped, bool canWearHelmet)l
extern _native64(0xC0E78D5C2CE3EB25) void SET_PED_HELMET_FLAG(Ped ped, int helmetFlag)l
extern _native64(0x26D83693ED99291C) void SET_PED_HELMET_PROP_INDEX(Ped ped, int propIndex, bool p2)l
extern _native64(0x3F7325574E41B44D) void SET_PED_HELMET_VISOR_PROP_INDICES(Ped ped, bool p1, int p2, int p3)l
extern _native64(0xB9496CE47546DB2C) bool IS_PED_HELMET_VISOR_UP(Ped ped)l
extern _native64(0xF1550C4BD22582E2) void SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int textureIndex)l
extern _native64(0xF33BDFE19B309B19) bool IS_PED_WEARING_HELMET(Ped ped)l
extern _native64(0x687C0B594907D2E8) void CLEAR_PED_STORED_HAT_PROP(Ped ped)l
extern _native64(0x451294E859ECC018) int GET_PED_HELMET_STORED_HAT_PROP_INDEX(Ped ped)l
extern _native64(0x9D728C1E12BF5518) int GET_PED_HELMET_STORED_HAT_TEX_INDEX(Ped ped)l
extern _native64(0xF2385935BFFD4D92) bool IS_CURRENT_HEAD_PROP_A_HELMET(any p0)l
extern _native64(0x332B562EEDA62399) void SET_PED_TO_LOAD_COVER(Ped ped, bool toggle)l
extern _native64(0xCB7553CDCEF4A735) void SET_PED_CAN_COWER_IN_COVER(Ped ped, bool toggle)l
extern _native64(0xC514825C507E3736) void SET_PED_CAN_PEEK_IN_COVER(Ped ped, bool toggle)l
extern _native64(0x94D94BF1A75AED3D) void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Ped ped, bool toggle)l
extern _native64(0xC396F5B86FF9FEBD) void SET_PED_LEG_IK_MODE(Ped ped, int mode)l
extern _native64(0x0A986918B102B448) void SET_PED_MOTION_BLUR(Ped ped, bool toggle)l
extern _native64(0xED7F7EFE9FABF340) void SET_PED_CAN_SWITCH_WEAPON(Ped ped, bool toggle)l
extern _native64(0xEEB64139BA29A7CF) void SET_PED_DIES_INSTANTLY_IN_WATER(Ped ped, bool toggle)l
extern _native64(0x1A330D297AAC6BC1) void SET_LADDER_CLIMB_INPUT_STATE(Ped ped, int p1)l
extern _native64(0xC158D28142A34608) void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped)l
extern _native64(0x5917BBA32D06C230) void SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float p1)l
extern _native64(0x4D9CA1009AFBD057) void SET_PED_COMBAT_MOVEMENT(Ped ped, int combatMovement)l
extern _native64(0xDEA92412FCAEB3F5) int GET_PED_COMBAT_MOVEMENT(Ped ped)l
extern _native64(0xC7622C0D36B2FDA8) void SET_PED_COMBAT_ABILITY(Ped ped, int abilityLevel)l
extern _native64(0x3C606747B23E497B) void SET_PED_COMBAT_RANGE(Ped ped, int combatRange)l
extern _native64(0xF9D9F7F2DB8E2FA0) int GET_PED_COMBAT_RANGE(Ped ped)l
extern _native64(0x9F7794730795E019) void SET_PED_COMBAT_ATTRIBUTES(Ped ped, int attributeId, bool enabled)l
extern _native64(0x0703B9079823DA4A) void SET_PED_TARGET_LOSS_RESPONSE(Ped ped, int responseType)l
extern _native64(0xDCCA191DF9980FD7) bool IS_PED_PERFORMING_MELEE_ACTION(Ped ped)l
extern _native64(0xFD4CCDBCC59941B7) bool IS_PED_PERFORMING_STEALTH_KILL(Ped ped)l
extern _native64(0xEBD0EDBA5BE957CF) bool IS_PED_PERFORMING_A_COUNTER_ATTACK(Ped ped)l
extern _native64(0x863B23EFDE9C5DF2) bool IS_PED_BEING_STEALTH_KILLED(Ped ped)l
extern _native64(0x18A3E9EE1297FD39) Ped GET_MELEE_TARGET_FOR_PED(Ped ped)l
extern _native64(0xF9800AA1A771B000) bool WAS_PED_KILLED_BY_STEALTH(Ped ped)l
extern _native64(0x7F08E26039C7347C) bool WAS_PED_KILLED_BY_TAKEDOWN(Ped ped)l
extern _native64(0x61767F73EACEED21) bool WAS_PED_KNOCKED_OUT(Ped ped)l
extern _native64(0x70A2D1137C8ED7C9) void SET_PED_FLEE_ATTRIBUTES(Ped ped, int attributeFlags, bool enable)l
extern _native64(0xA549131166868ED3) void SET_PED_COWER_HASH(Ped ped, const char* p1)l
extern _native64(0x2016C603D6B8987C) void SET_PED_STEERS_AROUND_DEAD_BODIES(Ped ped, bool toggle)l
extern _native64(0x46F2193B3AD1D891) void SET_PED_STEERS_AROUND_PEDS(Ped ped, bool toggle)l
extern _native64(0x1509C089ADC208BF) void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, bool toggle)l
extern _native64(0xEB6FB9D48DDE23EC) void SET_PED_STEERS_AROUND_VEHICLES(Ped ped, bool toggle)l
extern _native64(0xA9B61A329BFDCBEA) void SET_PED_IS_AVOIDED_BY_OTHERS(any p0, bool p1)l
extern _native64(0x570389D1C3DE3C6B) void SET_PED_INCREASED_AVOIDANCE_RADIUS(Ped ped)l
extern _native64(0x576594E8D64375E2) void SET_PED_BLOCKS_PATHING_WHEN_DEAD(Ped ped, bool toggle)l
extern _native64(0xA52D5247A4227E14) void SET_PED_NO_TIME_DELAY_BEFORE_SHOT(any p0)l
extern _native64(0x083961498679DC9F) bool IS_ANY_PED_NEAR_POINT(float x, float y, float z, float radius)l
extern _native64(0x2208438012482A1A) void FORCE_PED_AI_AND_ANIMATION_UPDATE(Ped ped, bool p1, bool p2)l
extern _native64(0xFCF37A457CB96DC0) bool IS_PED_HEADING_TOWARDS_POSITION(Ped ped, float x, float y, float z, float p4)l
extern _native64(0x7D7A2E43E74E2EB8) void REQUEST_PED_VISIBILITY_TRACKING(Ped ped)l
extern _native64(0x2BC338A7B21F4608) void REQUEST_PED_VEHICLE_VISIBILITY_TRACKING(Ped ped, bool p1)l
extern _native64(0xCD018C591F94CB43) void REQUEST_PED_RESTRICTED_VEHICLE_VISIBILITY_TRACKING(Ped ped, bool p1)l
extern _native64(0x75BA1CB3B7D40CAF) void REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING(Ped ped, bool p1)l
extern _native64(0x91C8E617F64188AC) bool IS_TRACKED_PED_VISIBLE(Ped ped)l
extern _native64(0x511F1A683387C7E2) int GET_TRACKED_PED_PIXELCOUNT(Ped ped)l
extern _native64(0x4C5E1F087CD10BB7) bool IS_PED_TRACKED(Ped ped)l
extern _native64(0x8507BCB710FA6DC0) bool HAS_PED_RECEIVED_EVENT(Ped ped, int eventId)l
extern _native64(0x6CD5A433374D4CFB) bool CAN_PED_SEE_HATED_PED(Ped ped1, Ped ped2)l
extern _native64(0x9C6A6C19B6C0C496) bool CAN_PED_SHUFFLE_TO_OR_FROM_TURRET_SEAT(Ped ped, int* p1)l
extern _native64(0x2DFC81C9B9608549) bool CAN_PED_SHUFFLE_TO_OR_FROM_EXTRA_SEAT(Ped ped, int* p1)l
extern _native64(0x3F428D08BE5AAE31) int GET_PED_BONE_INDEX(Ped ped, int boneId)l
extern _native64(0x2057EF813397A772) int GET_PED_RAGDOLL_BONE_INDEX(Ped ped, int bone)l
extern _native64(0xBF29516833893561) void SET_PED_ENVEFF_SCALE(Ped ped, float value)l
extern _native64(0x9C14D30395A51A3C) float GET_PED_ENVEFF_SCALE(Ped ped)l
extern _native64(0xD2C5AA0C0E8D0F1E) void SET_ENABLE_PED_ENVEFF_SCALE(Ped ped, bool toggle)l
extern _native64(0x110F526AB784111F) void SET_PED_ENVEFF_CPV_ADD(Ped ped, float p1)l
extern _native64(0xD69411AA0CEBF9E9) void SET_PED_ENVEFF_COLOR_MODULATOR(Ped ped, int p1, int p2, int p3)l
extern _native64(0x4E90D746056E273D) void SET_PED_EMISSIVE_SCALE(Ped ped, float intensity)l
extern _native64(0x1461B28A06717D68) float GET_PED_EMISSIVE_SCALE(Ped ped)l
extern _native64(0x81AA517FBBA05D39) bool IS_PED_SHADER_READY(Ped ped)l
extern _native64(0xE906EC930F5FE7C8) void SET_PED_ENABLE_CREW_EMBLEM(Ped ped, bool toggle)l
extern _native64(0x1216E0BFA72CC703) void REQUEST_RAGDOLL_BOUNDS_UPDATE(any p0, any p1)l
extern _native64(0x2B5AA717A181FB4C) void SET_PED_AO_BLOB_RENDERING(Ped ped, bool toggle)l
extern _native64(0xB8B52E498014F5B0) bool IS_PED_SHELTERED(Ped ped)l
extern _native64(0x8C18E0F9080ADD73) int CREATE_SYNCHRONIZED_SCENE(float x, float y, float z, float roll, float pitch, float yaw, int p6)l
extern _native64(0x62EC273D00187DCA) int CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT(float x, float y, float z, float radius, Hash object)l
extern _native64(0x25D39B935A038A26) bool IS_SYNCHRONIZED_SCENE_RUNNING(int sceneId)l
extern _native64(0x6ACF6B7225801CD7) void SET_SYNCHRONIZED_SCENE_ORIGIN(int sceneID, float x, float y, float z, float roll, float pitch, float yaw, bool p7)l
extern _native64(0x734292F4F0ABF6D0) void SET_SYNCHRONIZED_SCENE_PHASE(int sceneID, float phase)l
extern _native64(0xE4A310B1D7FA73CC) float GET_SYNCHRONIZED_SCENE_PHASE(int sceneID)l
extern _native64(0xB6C49F8A5E295A5D) void SET_SYNCHRONIZED_SCENE_RATE(int sceneID, float rate)l
extern _native64(0xD80932D577274D40) float GET_SYNCHRONIZED_SCENE_RATE(int sceneID)l
extern _native64(0xD9A897A4C6C2974F) void SET_SYNCHRONIZED_SCENE_LOOPED(int sceneID, bool toggle)l
extern _native64(0x62522002E0C391BA) bool IS_SYNCHRONIZED_SCENE_LOOPED(int sceneID)l
extern _native64(0x394B9CD12435C981) void SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID, bool toggle)l
extern _native64(0x7F2F4F13AC5257EF) bool IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID)l
extern _native64(0x272E4723B56A3B96) void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(int sceneID, Entity entity, int boneIndex)l
extern _native64(0x6D38F1F04CBB37EA) void DETACH_SYNCHRONIZED_SCENE(int sceneID)l
extern _native64(0xCD9CC7E200A52A6F) void TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE(int scene)l
extern _native64(0xF28965D04F570DCA) bool FORCE_PED_MOTION_STATE(Ped ped, Hash motionStateHash, bool p2, int p3, bool p4)l
extern _native64(0xF60165E1D2C5370B) bool GET_PED_CURRENT_MOVE_BLEND_RATIO(Ped ped, float* speedX, float* speedY)l
extern _native64(0x433083750C5E064A) void SET_PED_MAX_MOVE_BLEND_RATIO(Ped ped, float value)l
extern _native64(0x01A898D26E2333DD) void SET_PED_MIN_MOVE_BLEND_RATIO(Ped ped, float value)l
extern _native64(0x085BF80FA50A39D1) void SET_PED_MOVE_RATE_OVERRIDE(Ped ped, float value)l
extern _native64(0x0B3E35AC043707D9) void SET_PED_MOVE_RATE_IN_WATER_OVERRIDE(Ped ped, float p1)l
extern _native64(0x46B05BCAE43856B0) bool PED_HAS_SEXINESS_FLAG_SET(Ped ped, int sexinessFlag)l
extern _native64(0xCFF869CBFA210D82) int GET_PED_NEARBY_VEHICLES(Ped ped, any* sizeAndVehs)l
extern _native64(0x23F8F5FC7E8C4A6B) int GET_PED_NEARBY_PEDS(Ped ped, any* sizeAndPeds, int ignore)l
extern _native64(0x7350823473013C02) bool HAVE_ALL_STREAMING_REQUESTS_COMPLETED(Ped ped)l
extern _native64(0x00E73468D085F745) bool IS_PED_USING_ACTION_MODE(Ped ped)l
extern _native64(0xD75ACCF5E0FB5367) void SET_PED_USING_ACTION_MODE(Ped ped, bool p1, int p2, const char* action)l
extern _native64(0x781DE8FA214E87D2) void SET_MOVEMENT_MODE_OVERRIDE(Ped ped, const char* name)l
extern _native64(0x364DF566EC833DE2) void SET_PED_CAPSULE(Ped ped, float value)l
extern _native64(0x4462658788425076) int REGISTER_PEDHEADSHOT(Ped ped)l
extern _native64(0xBA8805A1108A2515) int REGISTER_PEDHEADSHOT_HIRES(Ped ped)l
extern _native64(0x953563CE563143AF) int REGISTER_PEDHEADSHOT_TRANSPARENT(Ped ped)l
extern _native64(0x96B1361D9B24C2FF) void UNREGISTER_PEDHEADSHOT(int id)l
extern _native64(0xA0A9668F158129A2) bool IS_PEDHEADSHOT_VALID(int id)l
extern _native64(0x7085228842B13A67) bool IS_PEDHEADSHOT_READY(int id)l
extern _native64(0xDB4EACD4AD0A5D6B) const char* GET_PEDHEADSHOT_TXD_STRING(int id)l
extern _native64(0xF0DAEF2F545BEE25) bool REQUEST_PEDHEADSHOT_IMG_UPLOAD(int id)l
extern _native64(0x5D517B27CF6ECD04) void RELEASE_PEDHEADSHOT_IMG_UPLOAD(int id)l
extern _native64(0xEBB376779A760AA8) bool IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE()l
extern _native64(0x876928DDDFCCC9CD) bool HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED()l
extern _native64(0xE8A169E666CBC541) bool HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED()l
extern _native64(0xC1F6EBF9A3D55538) void SET_PED_HEATSCALE_OVERRIDE(Ped ped, float heatScale)l
extern _native64(0x600048C60D5C2C51) void DISABLE_PED_HEATSCALE_OVERRIDE(Ped ped)l
extern _native64(0x2DF9038C90AD5264) void SPAWNPOINTS_START_SEARCH(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration)l
extern _native64(0xB2AFF10216DEFA2F) void SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, int interiorFlags, float scale, int duration)l
extern _native64(0xFEE4A5459472A9F8) void SPAWNPOINTS_CANCEL_SEARCH()l
extern _native64(0x3C67506996001F5E) bool SPAWNPOINTS_IS_SEARCH_ACTIVE()l
extern _native64(0xA586FBEB32A53DBB) bool SPAWNPOINTS_IS_SEARCH_COMPLETE()l
extern _native64(0xF445DE8DA80A1792) bool SPAWNPOINTS_IS_SEARCH_FAILED()l
extern _native64(0xA635C11B8C44AFC2) int SPAWNPOINTS_GET_NUM_SEARCH_RESULTS()l
extern _native64(0x280C7E3AC7F56E90) void SPAWNPOINTS_GET_SEARCH_RESULT(int randomInt, float* x, float* y, float* z)l
extern _native64(0xB782F8238512BAD5) void SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS(int p0, int* p1)l
extern _native64(0xC32779C16FCEECD9) void SET_IK_TARGET(Ped ped, int ikIndex, Entity entityLookAt, int boneLookAt, float offsetX, float offsetY, float offsetZ, any p7, int blendInDuration, int blendOutDuration)l
extern _native64(0xED3C76ADFA6D07C4) void FORCE_INSTANT_LEG_IK_SETUP(Ped ped)l
extern _native64(0x290E2780BB7AA598) void REQUEST_ACTION_MODE_ASSET(const char* asset)l
extern _native64(0xE4B5F4BF2CB24E65) bool HAS_ACTION_MODE_ASSET_LOADED(const char* asset)l
extern _native64(0x13E940F88470FA51) void REMOVE_ACTION_MODE_ASSET(const char* asset)l
extern _native64(0x2A0A62FCDEE16D4F) void REQUEST_STEALTH_MODE_ASSET(const char* asset)l
extern _native64(0xE977FC5B08AF3441) bool HAS_STEALTH_MODE_ASSET_LOADED(const char* asset)l
extern _native64(0x9219857D21F0E842) void REMOVE_STEALTH_MODE_ASSET(const char* asset)l
extern _native64(0xDC2C5C242AAC342B) void SET_PED_LOD_MULTIPLIER(Ped ped, float multiplier)l
extern _native64(0xE861D0B05C7662B8) void SET_PED_CAN_LOSE_PROPS_ON_DAMAGE(Ped ped, bool toggle, int p2)l
extern _native64(0x129466ED55140F8D) void SET_FORCE_FOOTSTEP_UPDATE(Ped ped, bool toggle)l
extern _native64(0xCB968B53FC7F916D) void SET_FORCE_STEP_TYPE(Ped ped, bool p1, int type, int p3)l
extern _native64(0x68772DB2B2526F9F) bool IS_ANY_HOSTILE_PED_NEAR_POINT(Ped ped, float x, float y, float z, float radius)l
extern _native64(0x820E9892A77E97CD) void SET_PED_CAN_PLAY_IN_CAR_IDLES(Ped ped, bool toggle)l
extern _native64(0x06087579E7AA85A9) bool IS_TARGET_PED_IN_PERCEPTION_AREA(Ped ped, Ped targetPed, float p2, float p3, float p4, float p5)l
extern _native64(0xD8C3BE3EE94CAF2D) void SET_POP_CONTROL_SPHERE_THIS_FRAME(float x, float y, float z, float min, float max)l
extern _native64(0xD33DAA36272177C4) void FORCE_ZERO_MASS_IN_COLLISIONS(Ped ped)l
extern _native64(0x711794453CFD692B) void SET_DISABLE_HIGH_FALL_DEATH(Ped ped, bool toggle)l
extern _native64(0x83A169EABCDB10A2) void SET_PED_PHONE_PALETTE_IDX(any p0, any p1)l
extern _native64(0x288DF530C92DAD6F) void SET_PED_STEER_BIAS(Ped ped, float value)l
extern _native64(0x3795688A307E1EB6) bool IS_PED_SWITCHING_WEAPON(Ped Ped)l
extern _native64(0x0F62619393661D6E) void SET_PED_TREATED_AS_FRIENDLY(any p0, any p1, any p2)l
extern _native64(0xDFE68C4B787E1BFB) void SET_DISABLE_PED_MAP_COLLISION(Ped ped)l
extern _native64(0xEE2476B9EE4A094F) void ENABLE_MP_LIGHT(Ped ped, bool toggle)l
extern _native64(0x88274C11CF0D866D) bool GET_MP_LIGHT_ENABLED(Ped ped)l
extern _native64(0x637822DC2AFEEBF8) void CLEAR_COVER_POINT_FOR_PED(Ped ped)l
extern _native64(0xFAB944D4D481ACCB) void SET_ALLOW_STUNT_JUMP_CAMERA(Ped ped, bool toggle)l
#pragma endregion //}
#pragma region PHYSICS //{
extern _native64(0xE832D760399EB220) int ADD_ROPE(float x, float y, float z, float rotX, float rotY, float rotZ, float length, int ropeType, float maxLength, float minLength, float windingSpeed, bool p11, bool p12, bool rigid, float p14, bool breakWhenShot, any* unkPtr)l
extern _native64(0x52B4829281364649) void DELETE_ROPE(int* ropeId)l
extern _native64(0xAA5D6B1888E4DB20) void DELETE_CHILD_ROPE(int ropeId)l
extern _native64(0xFD5448BE3111ED96) bool DOES_ROPE_EXIST(int* ropeId)l
extern _native64(0xA1AE736541B0FCA3) void ROPE_DRAW_ENABLED(int* ropeId, bool p1)l
extern _native64(0xF159A63806BB5BA8) void ROPE_DRAW_SHADOW_ENABLED(int* ropeId, bool toggle)l
extern _native64(0xCBB203C04D1ABD27) void LOAD_ROPE_DATA(int ropeId, const char* rope_preset)l
extern _native64(0x2B320CF14146B69A) void PIN_ROPE_VERTEX(int ropeId, int vertex, float x, float y, float z)l
extern _native64(0x4B5AE2EEE4A8F180) void UNPIN_ROPE_VERTEX(int ropeId, int vertex)l
extern _native64(0x3655F544CD30F0B5) int GET_ROPE_VERTEX_COUNT(int ropeId)l
extern _native64(0x3D95EC8B6D940AC3) void ATTACH_ENTITIES_TO_ROPE(int ropeId, Entity ent1, Entity ent2, float ent1_x, float ent1_y, float ent1_z, float ent2_x, float ent2_y, float ent2_z, float length, bool p10, bool p11, any* p12, any* p13)l
extern _native64(0x4B490A6832559A65) void ATTACH_ROPE_TO_ENTITY(int ropeId, Entity entity, float x, float y, float z, bool p5)l
extern _native64(0xBCF3026912A8647D) void DETACH_ROPE_FROM_ENTITY(int ropeId, Entity entity)l
extern _native64(0xC8D667EE52114ABA) void ROPE_SET_UPDATE_PINVERTS(int ropeId)l
extern _native64(0xDC57A637A20006ED) void ROPE_SET_UPDATE_ORDER(int ropeId, any p1)l
extern _native64(0x36CCB9BE67B970FD) void ROPE_SET_SMOOTH_REELIN(int ropeId, bool p1)l
extern _native64(0x84DE3B5FB3E666F0) bool IS_ROPE_ATTACHED_AT_BOTH_ENDS(int* ropeId)l
extern _native64(0x21BB0FBD3E217C2D) vector3 GET_ROPE_LAST_VERTEX_COORD(int ropeId)l
extern _native64(0xEA61CA8E80F09E4D) vector3 GET_ROPE_VERTEX_COORD(int ropeId, int vertex)l
extern _native64(0x1461C72C889E343E) void START_ROPE_WINDING(int ropeId)l
extern _native64(0xCB2D4AB84A19AA7C) void STOP_ROPE_WINDING(int ropeId)l
extern _native64(0x538D1179EC1AA9A9) void START_ROPE_UNWINDING_FRONT(int ropeId)l
extern _native64(0xFFF3A50779EFBBB3) void STOP_ROPE_UNWINDING_FRONT(int ropeId)l
extern _native64(0x5389D48EFA2F079A) void ROPE_CONVERT_TO_SIMPLE(int ropeId)l
extern _native64(0x9B9039DBF2D258C1) void ROPE_LOAD_TEXTURES()l
extern _native64(0xF2D0E6A75CC05597) bool ROPE_ARE_TEXTURES_LOADED()l
extern _native64(0x6CE36C35C1AC8163) void ROPE_UNLOAD_TEXTURES()l
extern _native64(0x271C9D3ACA5D6409) bool DOES_SCRIPT_OWN_ROPE(int ropeId)l
extern _native64(0xBC0CE682D4D05650) void ROPE_ATTACH_VIRTUAL_BOUND_GEOM(int ropeId, int p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13)l
extern _native64(0xB1B6216CA2E7B55E) void ROPE_CHANGE_SCRIPT_OWNER(any p0, bool p1, bool p2)l
extern _native64(0xB743F735C03D7810) void ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER(int ropeId, int p1)l
extern _native64(0x73040398DFF9A4A6) float ROPE_GET_DISTANCE_BETWEEN_ENDS(int ropeId)l
extern _native64(0xD009F759A723DB1B) void ROPE_FORCE_LENGTH(int ropeId, float length)l
extern _native64(0xC16DE94D9BEA14A0) void ROPE_RESET_LENGTH(int ropeId, float length)l
extern _native64(0xE37F721824571784) void APPLY_IMPULSE_TO_CLOTH(float posX, float posY, float posZ, float vecX, float vecY, float vecZ, float impulse)l
extern _native64(0xEEA3B200A6FEB65B) void SET_DAMPING(Entity entity, int vertex, float value)l
extern _native64(0x710311ADF0E20730) void ACTIVATE_PHYSICS(Entity entity)l
extern _native64(0xD8FA3908D7B86904) void SET_CGOFFSET(Entity entity, float x, float y, float z)l
extern _native64(0x8214A4B5A7A33612) vector3 GET_CGOFFSET(Entity entity)l
extern _native64(0xBE520D9761FF811F) void SET_CG_AT_BOUNDCENTER(Entity entity)l
extern _native64(0x2E648D16F6E308F3) void BREAK_ENTITY_GLASS(Entity entity, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, any p9, bool p10)l
extern _native64(0x0C112765300C7E1E) bool GET_IS_ENTITY_A_FRAG(Object object)l
extern _native64(0x5CEC1A84620E7D5B) void SET_DISABLE_BREAKING(Object object, bool toggle)l
extern _native64(0xCC6E963682533882) void RESET_DISABLE_BREAKING(Object object)l
extern _native64(0x01BA3AED21C16CFB) void SET_DISABLE_FRAG_DAMAGE(Object object, bool toggle)l
extern _native64(0x15F944730C832252) void SET_USE_KINEMATIC_PHYSICS(Entity entity, bool toggle)l
extern _native64(0x9EBD751E5787BAF2) void SET_IN_STUNT_MODE(bool p0)l
extern _native64(0xAA6A6098851C396F) void SET_IN_ARENA_MODE(bool toggle)l
#pragma endregion //}
#pragma region PLAYER //{
extern _native64(0x43A66C31C68491C0) Ped GET_PLAYER_PED(Player player)l
extern _native64(0x50FAC3A3E030A6E1) Ped GET_PLAYER_PED_SCRIPT_INDEX(Player player)l
extern _native64(0x00A1CADD00108836) void SET_PLAYER_MODEL(Player player, Hash model)l
extern _native64(0x048189FAC643DEEE) void CHANGE_PLAYER_PED(Player player, Ped ped, bool p2, bool resetDamage)l
extern _native64(0xE902EF951DCE178F) void GET_PLAYER_RGB_COLOUR(Player player, int* r, int* g, int* b)l
extern _native64(0x407C7F91DDB46C16) int GET_NUMBER_OF_PLAYERS()l
extern _native64(0x37039302F4E0A008) int GET_PLAYER_TEAM(Player player)l
extern _native64(0x0299FA38396A4940) void SET_PLAYER_TEAM(Player player, int team)l
extern _native64(0x1FC200409F10E6F1) int GET_NUMBER_OF_PLAYERS_IN_TEAM(int team)l
extern _native64(0x6D0DE6A7B5DA71F8) const char* GET_PLAYER_NAME(Player player)l
extern _native64(0x085DEB493BE80812) float GET_WANTED_LEVEL_RADIUS(Player player)l
extern _native64(0x0C92BA89F1AF26F8) vector3 GET_PLAYER_WANTED_CENTRE_POSITION(Player player)l
extern _native64(0x520E541A97A13354) void SET_PLAYER_WANTED_CENTRE_POSITION(Player player, vector3* position, bool p2, bool p3)l
extern _native64(0xFDD179EAF45B556C) int GET_WANTED_LEVEL_THRESHOLD(int wantedLevel)l
extern _native64(0x39FF19C64EF7DA5B) void SET_PLAYER_WANTED_LEVEL(Player player, int wantedLevel, bool disableNoMission)l
extern _native64(0x340E61DE7F471565) void SET_PLAYER_WANTED_LEVEL_NO_DROP(Player player, int wantedLevel, bool p2)l
extern _native64(0xE0A7D1E497FFCD6F) void SET_PLAYER_WANTED_LEVEL_NOW(Player player, bool p1)l
extern _native64(0xAFAF86043E5874E9) bool ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(Player player)l
extern _native64(0x0A6EB355EE14A2DB) bool ARE_PLAYER_STARS_GREYED_OUT(Player player)l
extern _native64(0x7E07C78925D5FD96) bool IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS(Player player)l
extern _native64(0xDB172424876553F4) void SET_DISPATCH_COPS_FOR_PLAYER(Player player, bool toggle)l
extern _native64(0x238DB2A2C23EE9EF) bool IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel)l
extern _native64(0xB302540597885499) void CLEAR_PLAYER_WANTED_LEVEL(Player player)l
extern _native64(0x424D4687FA1E5652) bool IS_PLAYER_DEAD(Player player)l
extern _native64(0xFA1E2BF8B10598F9) bool IS_PLAYER_PRESSING_HORN(Player player)l
extern _native64(0x8D32347D6D4C40A2) void SET_PLAYER_CONTROL(Player player, bool bHasControl, int flags)l
extern _native64(0xE28E54788CE8F12D) int GET_PLAYER_WANTED_LEVEL(Player player)l
extern _native64(0xAA5F02DB48D704B9) void SET_MAX_WANTED_LEVEL(int maxWantedLevel)l
extern _native64(0x43286D561B72B8BF) void SET_POLICE_RADAR_BLIPS(bool toggle)l
extern _native64(0x32C62AA929C2DA6A) void SET_POLICE_IGNORE_PLAYER(Player player, bool toggle)l
extern _native64(0x5E9564D8246B909A) bool IS_PLAYER_PLAYING(Player player)l
extern _native64(0x8EEDA153AD141BA4) void SET_EVERYONE_IGNORE_PLAYER(Player player, bool toggle)l
extern _native64(0x056E0FE8534C2949) void SET_ALL_RANDOM_PEDS_FLEE(Player player, bool toggle)l
extern _native64(0x471D2FF42A94B4F2) void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player)l
extern _native64(0xDE45D1A1EF45EE61) void SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE(Player player, bool toggle)l
extern _native64(0xC3376F42B1FACCC6) void SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player)l
extern _native64(0xFAC75988A7D078D3) void SET_LAW_PEDS_CAN_ATTACK_NON_WANTED_PLAYER_THIS_FRAME(Player player)l
extern _native64(0x596976B02B6B5700) void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Player player, bool toggle)l
extern _native64(0x020E5F00CDA207BA) void SET_WANTED_LEVEL_MULTIPLIER(float multiplier)l
extern _native64(0x9B0BB33B04405E7A) void SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty)l
extern _native64(0xB9D0DD990DC141DD) void RESET_WANTED_LEVEL_DIFFICULTY(Player player)l
extern _native64(0xA72200F51875FEA4) int GET_WANTED_LEVEL_TIME_TO_ESCAPE()l
extern _native64(0x49B856B1360C47C7) void SET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player, int wantedLevel, int lossTime)l
extern _native64(0x823EC8E82BA45986) void RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player)l
extern _native64(0xBF9BD71691857E48) void START_FIRING_AMNESTY(int duration)l
extern _native64(0xE9B09589827545E7) void REPORT_CRIME(Player player, int crimeType, int wantedLvlThresh)l
extern _native64(0x9A987297ED8BD838) void SUPPRESS_CRIME_THIS_FRAME(Player player, int crimeType)l
extern _native64(0xBC9490CA15AEA8FB) void UPDATE_WANTED_POSITION_THIS_FRAME(Player player)l
extern _native64(0x4669B3ED80F24B4E) void SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME(Player player)l
extern _native64(0x2F41A3BAE005E5FA) void ALLOW_EVASION_HUD_IF_DISABLING_HIDDEN_EVASION_THIS_FRAME(Player player, any p1)l
extern _native64(0xAD73CE5A09E42D12) void FORCE_START_HIDDEN_EVASION(Player player)l
extern _native64(0x36F1B38855F2A8DF) void SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME(Player player)l
extern _native64(0xDC64D2C53493ED12) void REPORT_POLICE_SPOTTED_PLAYER(Player player)l
extern _native64(0xB45EFF719D8427A6) void SET_LAW_RESPONSE_DELAY_OVERRIDE(float p0)l
extern _native64(0x0032A6DBA562C518) void RESET_LAW_RESPONSE_DELAY_OVERRIDE()l
extern _native64(0xDE7465A27D403C06) bool CAN_PLAYER_START_MISSION(Player player)l
extern _native64(0x908CBECC2CAA3690) bool IS_PLAYER_READY_FOR_CUTSCENE(Player player)l
extern _native64(0x7912F7FC4F6264B6) bool IS_PLAYER_TARGETTING_ENTITY(Player player, Entity entity)l
extern _native64(0x13EDE1A5DBF797C9) bool GET_PLAYER_TARGET_ENTITY(Player player, Entity* entity)l
extern _native64(0x2E397FD2ECD37C87) bool IS_PLAYER_FREE_AIMING(Player player)l
extern _native64(0x3C06B5C839B38F7B) bool IS_PLAYER_FREE_AIMING_AT_ENTITY(Player player, Entity entity)l
extern _native64(0x2975C866E6713290) bool GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(Player player, Entity* entity)l
extern _native64(0x29961D490E5814FD) void SET_PLAYER_LOCKON_RANGE_OVERRIDE(Player player, float range)l
extern _native64(0x6E8834B52EC20C77) void SET_PLAYER_CAN_DO_DRIVE_BY(Player player, bool toggle)l
extern _native64(0xD5E460AD7020A246) void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Player player, bool toggle)l
extern _native64(0xD465A8599DFF6814) void SET_PLAYER_CAN_USE_COVER(Player player, bool toggle)l
extern _native64(0x462E0DB9B137DC5F) int GET_MAX_WANTED_LEVEL()l
extern _native64(0x78CFE51896B6B8A4) bool IS_PLAYER_TARGETTING_ANYTHING(Player player)l
extern _native64(0xA01B8075D8B92DF4) void SET_PLAYER_SPRINT(Player player, bool toggle)l
extern _native64(0xA6F312FCCE9C1DFE) void RESET_PLAYER_STAMINA(Player player)l
extern _native64(0xA352C1B864CAFD33) void RESTORE_PLAYER_STAMINA(Player player, float p1)l
extern _native64(0x3F9F16F8E65A7ED7) float GET_PLAYER_SPRINT_STAMINA_REMAINING(Player player)l
extern _native64(0x1885BC9B108B4C99) float GET_PLAYER_SPRINT_TIME_REMAINING(Player player)l
extern _native64(0xA1FCF8E6AF40B731) float GET_PLAYER_UNDERWATER_TIME_REMAINING(Player player)l
extern _native64(0xA0D3E4F7AAFB7E78) float SET_PLAYER_UNDERWATER_BREATH_PERCENT_REMAINING(Player player, float time)l
extern _native64(0x0D127585F77030AF) int GET_PLAYER_GROUP(Player player)l
extern _native64(0x92659B4CE1863CB3) int GET_PLAYER_MAX_ARMOUR(Player player)l
extern _native64(0x49C32D60007AFA47) bool IS_PLAYER_CONTROL_ON(Player player)l
extern _native64(0x7C814D2FB49F40C0) bool GET_ARE_CAMERA_CONTROLS_DISABLED()l
extern _native64(0x8A876A65283DD7D7) bool IS_PLAYER_SCRIPT_CONTROL_ON(Player player)l
extern _native64(0x95E8F73DC65EFB9C) bool IS_PLAYER_CLIMBING(Player player)l
extern _native64(0x388A47C51ABDAC8E) bool IS_PLAYER_BEING_ARRESTED(Player player, bool atArresting)l
extern _native64(0x2D03E13C460760D6) void RESET_PLAYER_ARREST_STATE(Player player)l
extern _native64(0xB6997A7EB3F5C8C0) Vehicle GET_PLAYERS_LAST_VEHICLE()l
extern _native64(0xA5EDC40EF369B48D) Player GET_PLAYER_INDEX()l
extern _native64(0x41BD2A6B006AF756) Player INT_TO_PLAYERINDEX(int value)l
extern _native64(0x9EC6603812C24710) int INT_TO_PARTICIPANTINDEX(int value)l
extern _native64(0x5D35ECF3A81A0EE0) int GET_TIME_SINCE_PLAYER_HIT_VEHICLE(Player player)l
extern _native64(0xE36A25322DC35F42) int GET_TIME_SINCE_PLAYER_HIT_PED(Player player)l
extern _native64(0xD559D2BE9E37853B) int GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Player player)l
extern _native64(0xDB89591E290D9182) int GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(Player player)l
extern _native64(0xDCCFD3F106C36AB4) bool IS_PLAYER_FREE_FOR_AMBIENT_TASK(Player player)l
extern _native64(0x4F8644AF03D0E0D6) Player PLAYER_ID()l
extern _native64(0xD80958FC74E988A6) Ped PLAYER_PED_ID()l
extern _native64(0xEE68096F9F37341E) int NETWORK_PLAYER_ID_TO_INT()l
extern _native64(0xC968670BFACE42D9) bool HAS_FORCE_CLEANUP_OCCURRED(int cleanupFlags)l
extern _native64(0xBC8983F38F78ED51) void FORCE_CLEANUP(int cleanupFlags)l
extern _native64(0x4C68DDDDF0097317) void FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(const char* name, int cleanupFlags)l
extern _native64(0xF745B37630DF176B) void FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID(int id, int cleanupFlags)l
extern _native64(0x9A41CF4674A12272) int GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP()l
extern _native64(0x8026FF78F208978A) void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(Player player, Vehicle vehicle)l
extern _native64(0x1DE37BBF9E9CC14A) void SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE(Player player)l
extern _native64(0xBEC7076D64130195) bool GIVE_ACHIEVEMENT_TO_PLAYER(int achievementId)l
extern _native64(0xC2AFFFDABBDC2C5C) bool SET_ACHIEVEMENT_PROGRESS(int achievementId, int progress)l
extern _native64(0x1C186837D0619335) int GET_ACHIEVEMENT_PROGRESS(int achievementId)l
extern _native64(0x867365E111A3B6EB) bool HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId)l
extern _native64(0xF25D331DC2627BBC) bool IS_PLAYER_ONLINE()l
extern _native64(0x74556E1420867ECA) bool IS_PLAYER_LOGGING_IN_NP()l
extern _native64(0x94DD7888C10A979E) void DISPLAY_SYSTEM_SIGNIN_UI(bool p0)l
extern _native64(0x5D511E3867C87139) bool IS_SYSTEM_UI_BEING_DISPLAYED()l
extern _native64(0x239528EACDC3E7DE) void SET_PLAYER_INVINCIBLE(Player player, bool toggle)l
extern _native64(0xB721981B2B939E07) bool GET_PLAYER_INVINCIBLE(Player player)l
extern _native64(0xDCC07526B8EC45AF) bool GET_PLAYER_DEBUG_INVINCIBLE(Player player)l
extern _native64(0x6BC97F4F4BB3C04B) void SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS(Player player, bool toggle)l
extern _native64(0xCAC57395B151135F) void SET_PLAYER_CAN_COLLECT_DROPPED_MONEY(Player player, bool p1)l
extern _native64(0xF3AC26D3CC576528) void REMOVE_PLAYER_HELMET(Player player, bool p2)l
extern _native64(0x3C49C870E66F0A28) void GIVE_PLAYER_RAGDOLL_CONTROL(Player player, bool toggle)l
extern _native64(0x5C8B2F450EE4328E) void SET_PLAYER_LOCKON(Player player, bool toggle)l
extern _native64(0xB1906895227793F3) void SET_PLAYER_TARGETING_MODE(int targetMode)l
extern _native64(0x5702B917B99DB1CD) void SET_PLAYER_TARGET_LEVEL(int targetLevel)l
extern _native64(0xB9CF1F793A9F1BF1) bool GET_IS_USING_FPS_THIRD_PERSON_COVER()l
extern _native64(0xCB645E85E97EA48B) bool GET_IS_USING_HOOD_CAMERA()l
extern _native64(0xF0B67A4DE6AB5F98) void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Player player)l
extern _native64(0x20CE80B0C2BF4ACC) bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Player player)l
extern _native64(0x4AACB96203D11A31) void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player)l
extern _native64(0xE4B90F367BD81752) bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player)l
extern _native64(0xCA7DC8329F0A1E9E) void SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(Player player, float multiplier)l
extern _native64(0xA91C6F0FF7D16A13) void SET_SWIM_MULTIPLIER_FOR_PLAYER(Player player, float multiplier)l
extern _native64(0x6DB47AA77FD94E09) void SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(Player player, float multiplier)l
extern _native64(0x5063F92F07C2A316) int GET_TIME_SINCE_LAST_ARREST()l
extern _native64(0xC7034807558DDFCA) int GET_TIME_SINCE_LAST_DEATH()l
extern _native64(0xAEBF081FFC0A0E5E) void ASSISTED_MOVEMENT_CLOSE_ROUTE()l
extern _native64(0x8621390F0CDCFE1F) void ASSISTED_MOVEMENT_FLUSH_ROUTE()l
extern _native64(0x0FEE4F80AC44A726) void SET_PLAYER_FORCED_AIM(Player player, bool toggle)l
extern _native64(0x75E7D505F2B15902) void SET_PLAYER_FORCED_ZOOM(Player player, bool toggle)l
extern _native64(0x7651BC64AE59E128) void SET_PLAYER_FORCE_SKIP_AIM_INTRO(Player player, bool toggle)l
extern _native64(0x5E6CC07646BBEAB8) void DISABLE_PLAYER_FIRING(Player player, bool toggle)l
extern _native64(0xB885852C39CC265D) void DISABLE_PLAYER_THROW_GRENADE_WHILE_USING_GUN()l
extern _native64(0x2E8AABFA40A84F8C) void SET_DISABLE_AMBIENT_MELEE_MOVE(Player player, bool toggle)l
extern _native64(0x77DFCCF5948B8C71) void SET_PLAYER_MAX_ARMOUR(Player player, int value)l
extern _native64(0x821FDC827D6F4090) void SPECIAL_ABILITY_ACTIVATE(Player player, int p1)l
extern _native64(0xB214D570EAD7F81A) void SET_SPECIAL_ABILITY_MP(Player player, int p1, any p2)l
extern _native64(0x17F7471EACA78290) void SPECIAL_ABILITY_DEACTIVATE_MP(Player player, int p1)l
extern _native64(0xD6A953C6D1492057) void SPECIAL_ABILITY_DEACTIVATE(Player player, any p1)l
extern _native64(0x9CB5CE07A3968D5A) void SPECIAL_ABILITY_DEACTIVATE_FAST(Player player, any p1)l
extern _native64(0x375F0E738F861A94) void SPECIAL_ABILITY_RESET(Player player, any p1)l
extern _native64(0xC9A763D8FE87436A) void SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED(Player player, any p1)l
extern _native64(0x2E7B9B683481687D) void SPECIAL_ABILITY_CHARGE_SMALL(Player player, bool p1, bool p2, any p3)l
extern _native64(0xF113E3AA9BC54613) void SPECIAL_ABILITY_CHARGE_MEDIUM(Player player, bool p1, bool p2, any p3)l
extern _native64(0xF733F45FA4497D93) void SPECIAL_ABILITY_CHARGE_LARGE(Player player, bool p1, bool p2, any p3)l
extern _native64(0xED481732DFF7E997) void SPECIAL_ABILITY_CHARGE_CONTINUOUS(Player player, Ped p1, any p2)l
extern _native64(0xB7B0870EB531D08D) void SPECIAL_ABILITY_CHARGE_ABSOLUTE(Player player, int p1, bool p2, any p3)l
extern _native64(0xA0696A65F009EE18) void SPECIAL_ABILITY_CHARGE_NORMALIZED(Player player, float normalizedValue, bool p2, any p3)l
extern _native64(0x3DACA8DDC6FD4980) void SPECIAL_ABILITY_FILL_METER(Player player, bool p1, any p2)l
extern _native64(0x1D506DBBBC51E64B) void SPECIAL_ABILITY_DEPLETE_METER(Player player, bool p1, any p2)l
extern _native64(0x6A09D0D590A47D13) void SPECIAL_ABILITY_LOCK(Hash playerModel, any p1)l
extern _native64(0xF145F3BE2EFA9A3B) void SPECIAL_ABILITY_UNLOCK(Hash playerModel, any p1)l
extern _native64(0xC6017F6A6CDFA694) bool IS_SPECIAL_ABILITY_UNLOCKED(Hash playerModel)l
extern _native64(0x3E5F7FC85D854E15) bool IS_SPECIAL_ABILITY_ACTIVE(Player player, any p1)l
extern _native64(0x05A1FE504B7F2587) bool IS_SPECIAL_ABILITY_METER_FULL(Player player, any p1)l
extern _native64(0x181EC197DAEFE121) void ENABLE_SPECIAL_ABILITY(Player player, bool toggle, any p2)l
extern _native64(0xB1D200FE26AEF3CB) bool IS_SPECIAL_ABILITY_ENABLED(Player player, any p1)l
extern _native64(0xA49C426ED0CA4AB7) void SET_SPECIAL_ABILITY_MULTIPLIER(float multiplier)l
extern _native64(0xFFEE8FA29AB9A18E) void UPDATE_SPECIAL_ABILITY_FROM_STAT(Player player, any p1)l
extern _native64(0x5FC472C501CCADB3) bool GET_IS_PLAYER_DRIVING_ON_HIGHWAY(Player player)l
extern _native64(0xF10B44FD479D69F3) bool GET_IS_PLAYER_DRIVING_WRECKLESS(Player player, int p1)l
extern _native64(0xDD2620B7B9D16FF1) bool GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER(Player player, float p1)l
extern _native64(0xAD15F075A4DA0FDE) void START_PLAYER_TELEPORT(Player player, float x, float y, float z, float heading, bool p5, bool findCollisionLand, bool p7)l
extern _native64(0xE23D5873C2394C61) bool UPDATE_PLAYER_TELEPORT(Player player)l
extern _native64(0xC449EDED9D73009C) void STOP_PLAYER_TELEPORT()l
extern _native64(0x02B15662D7F8886F) bool IS_PLAYER_TELEPORT_ACTIVE()l
extern _native64(0x2F395D61F3A1F877) float GET_PLAYER_CURRENT_STEALTH_NOISE(Player player)l
extern _native64(0x5DB660B38DD98A31) void SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(Player player, float regenRate)l
extern _native64(0x8BC515BAE4AAF8FF) float GET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player)l
extern _native64(0xC388A0F065F5BC34) void SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player, float limit)l
extern _native64(0xBCB06442F7E52666) void DISABLE_PLAYER_HEALTH_RECHARGE(Player player)l
extern _native64(0xEFD79FA81DFBA9CB) void SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE(Player player, float p1)l
extern _native64(0xCE07B9F7817AADA3) void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float modifier)l
extern _native64(0x2D83BC011CA14A3C) void SET_PLAYER_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native64(0xBCFDE9EDE4CF27DC) void SET_PLAYER_WEAPON_MINIGUN_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native64(0x4A3DC7ECCC321032) void SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Player player, float modifier, bool p2)l
extern _native64(0xAE540335B4ABC4E2) void SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native64(0xA50E117CDDF82F0C) void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player player, float modifier)l
extern _native64(0x4C60E6EFDAFF2462) void SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native64(0x8D768602ADEF2245) void SET_PLAYER_MAX_EXPLOSIVE_DAMAGE(Player player, float p1)l
extern _native64(0xD821056B9ACF8052) void SET_PLAYER_EXPLOSIVE_DAMAGE_MODIFIER(Player player, any p1)l
extern _native64(0x31E90B8873A4CD3B) void SET_PLAYER_WEAPON_TAKEDOWN_DEFENSE_MODIFIER(Player player, float p1)l
extern _native64(0xA3D0E54541D9A5E5) void SET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int tintIndex)l
extern _native64(0x75D3F7A1B0D9B145) void GET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int* tintIndex)l
extern _native64(0xAF04C87F5DC1DF38) void SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int index)l
extern _native64(0xD5A016BC3C09CF40) void GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int* index)l
extern _native64(0x93B0FB27C9A04060) void SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int tintIndex)l
extern _native64(0x6E9C742F340CE5A2) void GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int* tintIndex)l
extern _native64(0x7DDAB28D31FAC363) void SET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)l
extern _native64(0x5DDFE2FF727F3CA3) bool GET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)l
extern _native64(0xF401B182DBA8AF53) void SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(Player player, bool enabled)l
extern _native64(0x8217FD371A4625CF) void SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int r, int g, int b)l
extern _native64(0xEF56DBABD3CD4887) void GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int* r, int* g, int* b)l
extern _native64(0x11D5F725F0E780E0) void SET_PLAYER_PHONE_PALETTE_IDX(Player player, int flags)l
extern _native64(0xDB89EF50FF25FCE9) void SET_PLAYER_NOISE_MULTIPLIER(Player player, float multiplier)l
extern _native64(0xB2C1A29588A9F47C) void SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(Player player, float multiplier)l
extern _native64(0xF297383AA91DCA29) bool CAN_PED_HEAR_PLAYER(Player player, Ped ped)l
extern _native64(0x477D5D63E63ECA5D) void SIMULATE_PLAYER_INPUT_GAIT(Player player, float amount, int gaitType, float speed, bool p4, bool p5, any p6)l
extern _native64(0x19531C47A2ABD691) void RESET_PLAYER_INPUT_GAIT(Player player)l
extern _native64(0x9F343285A00B4BB6) void SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(Player player, bool toggle)l
extern _native64(0xD2B315B6689D537D) void SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE(Player player, bool toggle)l
extern _native64(0x4E9021C1FCDD507A) void SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(Player player, float value)l
extern _native64(0x690A61A6D13583F6) bool IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(Player player)l
extern _native64(0x9EDD76E87D5D51BA) void INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE(Player player)l
extern _native64(0xC54C95DA968EC5B5) void SET_PLAYER_SIMULATE_AIMING(Player player, bool toggle)l
extern _native64(0x749FADDF97DFE930) void SET_PLAYER_CLOTH_PIN_FRAMES(Player player, int p1)l
extern _native64(0x9F7BBA2EA6372500) void SET_PLAYER_CLOTH_PACKAGE_INDEX(int index)l
extern _native64(0x14D913B777DFF5DA) void SET_PLAYER_CLOTH_LOCK_COUNTER(int value)l
extern _native64(0xED51733DC73AED51) void PLAYER_ATTACH_VIRTUAL_BOUND(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7)l
extern _native64(0x1DD5897E2FA6E7C9) void PLAYER_DETACH_VIRTUAL_BOUND()l
extern _native64(0xD705740BB0A1CF4C) bool HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(Player player)l
extern _native64(0x38D28DA81E4E9BF9) bool IS_PLAYER_BATTLE_AWARE(Player player)l
extern _native64(0xBC0753C9CA14B506) bool GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY(Player player, int p1, bool p2)l
extern _native64(0x5006D96C995A5827) void EXTEND_WORLD_BOUNDARY_FOR_PLAYER(float x, float y, float z)l
extern _native64(0xDA1DF03D5A315F4E) void RESET_WORLD_BOUNDARY_FOR_PLAYER()l
extern _native64(0x4EC12697209F2196) bool IS_PLAYER_RIDING_TRAIN(Player player)l
extern _native64(0xD55DDFB47991A294) bool HAS_PLAYER_LEFT_THE_WORLD(Player player)l
extern _native64(0xFF300C7649724A0B) void SET_PLAYER_LEAVE_PED_BEHIND(Player player, bool toggle)l
extern _native64(0xD9284A8C0D48352C) void SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player, int p1, any p2, any p3, bool p4)l
extern _native64(0x0F4CC924CF8C7B21) void CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player)l
extern _native64(0x977DB4641F6FC3DB) void SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model)l
extern _native64(0x0764486AEDE748DB) void SET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model)l
extern _native64(0xC219887CA3E65C41) Hash GET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player)l
extern _native64(0x37FAAA68DCA9D08D) Hash GET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player)l
extern _native64(0x8753997EB5F6EE3F) void CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player)l
extern _native64(0x290D248E25815AE8) void CLEAR_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player)l
extern _native64(0xDC80A4C2F18A2B64) void SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player, Hash model)l
extern _native64(0x10C54E4389C12B42) void CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player)l
extern _native64(0xC142BE3BB9CE125F) void DISABLE_PLAYER_VEHICLE_REWARDS(Player player)l
extern _native64(0x2F7CEB6520288061) void SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE(bool p0)l
extern _native64(0x5DC40A8869C22141) void SET_PLAYER_BLUETOOTH_STATE(Player player, bool state)l
extern _native64(0x65FAEE425DE637B0) bool IS_PLAYER_BLUETOOTH_ENABLE(Player player)l
extern _native64(0x5501B7A5CDB79D37) void DISABLE_CAMERA_VIEW_MODE_CYCLE(Player player)l
extern _native64(0x56105E599CAB0EFA) int GET_PLAYER_FAKE_WANTED_LEVEL(Player player)l
extern _native64(0x55FCC0C390620314) void SET_PLAYER_CAN_DAMAGE_PLAYER(Player player1, Player player2, bool toggle)l
extern _native64(0x2382AB11450AE7BA) void SET_APPLY_WAYPOINT_OF_PLAYER(Player player, int hudColor)l
extern _native64(0x6E4361FF3E8CD7CA) bool IS_PLAYER_VEHICLE_WEAPON_TOGGLED_TO_NON_HOMING(any p0)l
extern _native64(0x237440E46D918649) void SET_PLAYER_VEHICLE_WEAPON_TO_NON_HOMING(any p0)l
extern _native64(0xEE4EBDD2593BA844) void SET_PLAYER_HOMING_DISABLED_FOR_ALL_VEHICLE_WEAPONS(any p0, any p1)l
extern _native64(0x9097EB6D4BB9A12A) void ADD_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity)l
extern _native64(0x9F260BFB59ADBCA3) void REMOVE_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity)l
extern _native64(0x7BAE68775557AE0B) void SET_PLAYER_PREVIOUS_VARIATION_DATA(Player player, int p1, int p2, any p3, any p4, any p5)l
extern _native64(0x7148E0F43D11F0D9) void REMOVE_SCRIPT_FIRE_POSITION()l
extern _native64(0x70A382ADEC069DD3) void SET_SCRIPT_FIRE_POSITION(float coordX, float coordY, float coordZ)l
#pragma endregion //}
#pragma region RECORDING //{
extern _native64(0x48621C9FCA3EBD28) void REPLAY_START_EVENT(int p0)l
extern _native64(0x81CBAE94390F9F89) void REPLAY_STOP_EVENT()l
extern _native64(0x13B350B8AD0EEE10) void REPLAY_CANCEL_EVENT()l
extern _native64(0x293220DA1B46CEBC) void REPLAY_RECORD_BACK_FOR_TIME(float p0, float p1, int p2)l
extern _native64(0x208784099002BC30) void REPLAY_CHECK_FOR_EVENT_THIS_FRAME(const char* missionNameLabel, any p1)l
extern _native64(0xEB2D525B57F42B40) void REPLAY_PREVENT_RECORDING_THIS_FRAME()l
extern _native64(0xF854439EFBB3B583) void REPLAY_RESET_EVENT_INFO()l
extern _native64(0xAF66DCEE6609B148) void REPLAY_DISABLE_CAMERA_MOVEMENT_THIS_FRAME()l
extern _native64(0x66972397E0757E7A) void RECORD_GREATEST_MOMENT(int p0, int p1, int p2)l
extern _native64(0xC3AC2FFF9612AC81) void START_REPLAY_RECORDING(int mode)l
extern _native64(0x071A5197D6AFC8B3) void STOP_REPLAY_RECORDING()l
extern _native64(0x88BB3507ED41A240) void CANCEL_REPLAY_RECORDING()l
extern _native64(0x644546EC5287471B) bool SAVE_REPLAY_RECORDING()l
extern _native64(0x1897CA71995A90B4) bool IS_REPLAY_RECORDING()l
extern _native64(0xDF4B952F7D381B95) bool IS_REPLAY_INITIALIZED()l
extern _native64(0x4282E08174868BE3) bool IS_REPLAY_AVAILABLE()l
extern _native64(0x33D47E85B476ABCD) bool IS_REPLAY_RECORD_SPACE_AVAILABLE(bool p0)l
#pragma endregion //}
#pragma region REPLAY //{
extern _native64(0x7E2BD3EF6C205F09) void REGISTER_EFFECT_FOR_REPLAY_EDITOR(const char* p0, bool p1)l
extern _native64(0x95AB8B5C992C7B58) bool REPLAY_SYSTEM_HAS_REQUESTED_A_SCRIPT_CLEANUP()l
extern _native64(0x5AD3932DAEB1E5D3) void SET_SCRIPTS_HAVE_CLEANED_UP_FOR_REPLAY_SYSTEM()l
extern _native64(0xE058175F8EAFE79A) void SET_REPLAY_SYSTEM_PAUSED_FOR_SAVE(bool p0)l
extern _native64(0x3353D13F09307691) void REPLAY_CONTROL_SHUTDOWN()l
extern _native64(0x49DA8145672B2725) void ACTIVATE_ROCKSTAR_EDITOR(int p0)l
#pragma endregion //}
#pragma region SAVEMIGRATION //{
extern _native64(0x84B418E93894AC1C) bool SAVEMIGRATION_IS_MP_ENABLED()l
extern _native64(0x85F41F9225D08C72) bool SAVEMIGRATION_MP_REQUEST_ACCOUNTS()l
extern _native64(0xC8CB5999919EA2CA) int SAVEMIGRATION_MP_GET_ACCOUNTS_STATUS()l
extern _native64(0x77A16200E18E0C55) int SAVEMIGRATION_MP_NUM_ACCOUNTS()l
extern _native64(0xFCE2747EEF1D05FC) bool SAVEMIGRATION_MP_GET_ACCOUNT(int p0, any* p1)l
extern _native64(0xE5E9746A66359F9D) bool SAVEMIGRATION_MP_REQUEST_STATUS()l
extern _native64(0x690B76BD2763E068) int SAVEMIGRATION_MP_GET_STATUS()l
#pragma endregion //}
#pragma region SCRIPT //{
extern _native64(0x6EB5F71AA68F2E8E) void REQUEST_SCRIPT(const char* scriptName)l
extern _native64(0xC90D2DCACD56184C) void SET_SCRIPT_AS_NO_LONGER_NEEDED(const char* scriptName)l
extern _native64(0xE6CC9F3BA0FB9EF1) bool HAS_SCRIPT_LOADED(const char* scriptName)l
extern _native64(0xFC04745FBE67C19A) bool DOES_SCRIPT_EXIST(const char* scriptName)l
extern _native64(0xD62A67D26D9653E6) void REQUEST_SCRIPT_WITH_NAME_HASH(Hash scriptHash)l
extern _native64(0xC5BC038960E9DB27) void SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(Hash scriptHash)l
extern _native64(0x5F0F0C783EB16C04) bool HAS_SCRIPT_WITH_NAME_HASH_LOADED(Hash scriptHash)l
extern _native64(0xF86AA3C56BA31381) bool DOES_SCRIPT_WITH_NAME_HASH_EXIST(Hash scriptHash)l
extern _native64(0xC8B189ED9138BCD4) void TERMINATE_THREAD(int threadId)l
extern _native64(0x46E9AE36D8FA6417) bool IS_THREAD_ACTIVE(int threadId)l
extern _native64(0x05A42BA9FC8DA96B) const char* GET_NAME_OF_SCRIPT_WITH_THIS_ID(int threadId)l
extern _native64(0xDADFADA5A20143A8) void SCRIPT_THREAD_ITERATOR_RESET()l
extern _native64(0x30B4FA1C82DD4B9F) int SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID()l
extern _native64(0xC30338E8088E2E21) int GET_ID_OF_THIS_THREAD()l
extern _native64(0x1090044AD1DA76FA) void TERMINATE_THIS_THREAD()l
extern _native64(0x2C83A9DA6BFFC4F9) int GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(Hash scriptHash)l
extern _native64(0x442E0A7EDE4A738A) const char* GET_THIS_SCRIPT_NAME()l
extern _native64(0x8A1C8B1738FFE87E) Hash GET_HASH_OF_THIS_SCRIPT_NAME()l
extern _native64(0x5F92A689A06620AA) int GET_NUMBER_OF_EVENTS(int eventGroup)l
extern _native64(0x936E6168A9BCEDB5) bool GET_EVENT_EXISTS(int eventGroup, int eventIndex)l
extern _native64(0xD8F66A3A60C62153) int GET_EVENT_AT_INDEX(int eventGroup, int eventIndex)l
extern _native64(0x2902843FCD2B2D79) bool GET_EVENT_DATA(int eventGroup, int eventIndex, any* eventData, int eventDataSize)l
extern _native64(0x5AE99C571D5BBE5D) void TRIGGER_SCRIPT_EVENT(int eventGroup, any* eventData, int eventDataSize, int playerBits)l
extern _native64(0x078EBE9809CCD637) void SHUTDOWN_LOADING_SCREEN()l
extern _native64(0x5262CC1995D07E09) void SET_NO_LOADING_SCREEN(bool toggle)l
extern _native64(0x18C1270EA7F199BC) bool GET_NO_LOADING_SCREEN()l
extern _native64(0xB1577667C3708F9B) void COMMIT_TO_LOADINGSCREEN_SELCTION()l
extern _native64(0x836B62713E0534CA) bool BG_IS_EXITFLAG_SET()l
extern _native64(0x760910B49D2B98EA) void BG_SET_EXITFLAG_RESPONSE()l
extern _native64(0x75B18E49607874C7) void BG_START_CONTEXT_HASH(Hash contextHash)l
extern _native64(0x107E5CC7CA942BC1) void BG_END_CONTEXT_HASH(Hash contextHash)l
extern _native64(0x9D5A25BADB742ACD) void BG_START_CONTEXT(const char* contextName)l
extern _native64(0xDC2BACD920D0A0DD) void BG_END_CONTEXT(const char* contextName)l
extern _native64(0x0F6F1EBBC4E1D5E6) bool BG_DOES_LAUNCH_PARAM_EXIST(int scriptIndex, const char* p1)l
extern _native64(0x22E21FBCFC88C149) int BG_GET_LAUNCH_PARAM_VALUE(int scriptIndex, const char* p1)l
extern _native64(0x829CD22E043A2577) int BG_GET_SCRIPT_ID_FROM_NAME_HASH(Hash p0)l
extern _native64(0xA40CC53DF8E50837) void SEND_TU_SCRIPT_EVENT(int eventGroup, any* eventData, int eventDataSize, int playerBits)l
#pragma endregion //}
#pragma region SECURITY //{
extern _native64(0x40EB1EFD921822BC) void REGISTER_SCRIPT_VARIABLE(any* variable)l
extern _native64(0x340A36A700E99699) void UNREGISTER_SCRIPT_VARIABLE(any* variable)l
extern _native64(0x8E580AB902917360) void FORCE_CHECK_SCRIPT_VARIABLES()l
#pragma endregion //}
#pragma region SHAPETEST //{
extern _native64(0x7EE9F5D83DD4F90E) int START_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8)l
extern _native64(0x377906D8A31E5586) int START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8)l
extern _native64(0x052837721A854EC7) int START_SHAPE_TEST_BOUNDING_BOX(Entity entity, int flags1, int flags2)l
extern _native64(0xFE466162C4401D18) int START_SHAPE_TEST_BOX(float x, float y, float z, float dimX, float dimY, float dimZ, float rotX, float rotY, float rotZ, any p9, int flags, Entity entity, any p12)l
extern _native64(0x37181417CE7C8900) int START_SHAPE_TEST_BOUND(Entity entity, int flags1, int flags2)l
extern _native64(0x28579D1B8F8AAC80) int START_SHAPE_TEST_CAPSULE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, int p9)l
extern _native64(0xE6AC6C45FBE83004) int START_SHAPE_TEST_SWEPT_SPHERE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, any p9)l
extern _native64(0xFF6BE494C7987F34) int START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE(vector3* pVec1, vector3* pVec2, int flag, Entity entity, int flag2)l
extern _native64(0x3D87450E15D98694) int GET_SHAPE_TEST_RESULT(int shapeTestHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Entity* entityHit)l
extern _native64(0x65287525D951F6BE) int GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL(int shapeTestHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Hash* materialHash, Entity* entityHit)l
extern _native64(0x2B3334BCA57CD799) void RELEASE_SCRIPT_GUID_FROM_ENTITY(Entity entityHit)l
#pragma endregion //}
#pragma region SOCIALCLUB //{
extern _native64(0x03A93FF1A2CA0864) int SC_INBOX_GET_TOTAL_NUM_MESSAGES()l
extern _native64(0xBB8EA16ECBC976C4) Hash SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX(int msgIndex)l
extern _native64(0x93028F1DB42BFD08) bool SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX(int msgIndex)l
extern _native64(0x2C015348CF19CA1D) bool SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX(int msgIndex)l
extern _native64(0xA00EFE4082C4056E) bool SC_INBOX_MESSAGE_GET_DATA_INT(int p0, const char* context, int* out)l
extern _native64(0xFFE5C16F402D851D) bool SC_INBOX_MESSAGE_GET_DATA_BOOL(int p0, const char* p1)l
extern _native64(0x7572EF42FC6A9B6D) bool SC_INBOX_MESSAGE_GET_DATA_STRING(int p0, const char* context, char* out)l
extern _native64(0x9A2C8064B6C1E41A) bool SC_INBOX_MESSAGE_DO_APPLY(int p0)l
extern _native64(0xF3E31D16CBDCB304) const char* SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX(int p0)l
extern _native64(0xDA024BDBD600F44A) void SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST(any* gamerHandle)l
extern _native64(0xA68D3D229F4F3B06) void SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST(any* data)l
extern _native64(0x69D82604A1A5A254) bool SC_INBOX_MESSAGE_GET_UGCDATA(int p0, any* p1)l
extern _native64(0x6AFD2CD753FEEF83) bool SC_INBOX_SEND_BOUNTY_TO_RECIP_LIST(any* data)l
extern _native64(0x87E0052F08BD64E6) bool SC_INBOX_GET_BOUNTY_DATA_AT_INDEX(int index, any* outData)l
extern _native64(0x040ADDCBAFA1018A) void SC_EMAIL_RETRIEVE_EMAILS(int offset, int limit)l
extern _native64(0x16DA8172459434AA) int SC_EMAIL_GET_RETRIEVAL_STATUS()l
extern _native64(0x7DB18CA8CAD5B098) int SC_EMAIL_GET_NUM_RETRIEVED_EMAILS()l
extern _native64(0x4737980E8A283806) bool SC_EMAIL_GET_EMAIL_AT_INDEX(int p0, any* p1)l
extern _native64(0x44ACA259D67651DB) void SC_EMAIL_DELETE_EMAILS(any* p0, any p1)l
extern _native64(0x2330C12A7A605D16) void SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST(any* gamerHandle)l
extern _native64(0x55DF6DB45179236E) void SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST()l
extern _native64(0x116FB94DC4B79F17) void SC_EMAIL_SEND_EMAIL(const char* p0)l
extern _native64(0x07DBD622D9533857) bool SC_EMAIL_SET_CURRENT_EMAIL_TAG(any p0)l
extern _native64(0xBFA0A56A817C6C7D) void SC_CACHE_NEW_ROCKSTAR_MSGS(bool toggle)l
extern _native64(0xBC1CC91205EC8D6E) bool SC_HAS_NEW_ROCKSTAR_MSG()l
extern _native64(0xDF649C4E9AFDD788) const char* SC_GET_NEW_ROCKSTAR_MSG()l
extern _native64(0x1F1E9682483697C7) bool SC_PRESENCE_ATTR_SET_INT(Hash attrHash, int value)l
extern _native64(0xC4C4575F62534A24) bool SC_PRESENCE_ATTR_SET_FLOAT(Hash attrHash, float value)l
extern _native64(0x287F1F75D2803595) bool SC_PRESENCE_ATTR_SET_STRING(Hash attrHash, const char* value)l
extern _native64(0x487912FD248EFDDF) bool SC_PRESENCE_SET_ACTIVITY_RATING(any p0, float p1)l
extern _native64(0xC85A7127E7AD02AA) bool SC_GAMERDATA_GET_INT(const char* name, int* value)l
extern _native64(0xA770C8EEC6FB2AC5) bool SC_GAMERDATA_GET_FLOAT(const char* name, float* value)l
extern _native64(0x8416FE4E4629D7D7) bool SC_GAMERDATA_GET_BOOL(const char* name)l
extern _native64(0x7FFCBFEE44ECFABF) bool SC_GAMERDATA_GET_STRING(const char* name, char* value)l
extern _native64(0x2D874D4AE612A65F) bool SC_GAMERDATA_GET_ACTIVE_XP_BONUS(float* value)l
extern _native64(0x75632C5ECD7ED843) bool SC_PROFANITY_CHECK_STRING(const char* string, int* token)l
extern _native64(0xEB2BF817463DFA28) bool SC_PROFANITY_CHECK_STRING_UGC(const char* string, int* token)l
extern _native64(0x1753344C770358AE) bool SC_PROFANITY_GET_CHECK_IS_VALID(int token)l
extern _native64(0x82E4A58BABC15AE7) bool SC_PROFANITY_GET_CHECK_IS_PENDING(int token)l
extern _native64(0x85535ACF97FC0969) bool SC_PROFANITY_GET_STRING_PASSED(int token)l
extern _native64(0x930DE22F07B1CCE3) int SC_PROFANITY_GET_STRING_STATUS(int token)l
extern _native64(0xF6BAAAF762E1BF40) bool SC_LICENSEPLATE_CHECK_STRING(const char* p0, int* p1)l
extern _native64(0xF22CA0FD74B80E7A) bool SC_LICENSEPLATE_GET_CHECK_IS_VALID(any p0)l
extern _native64(0x9237E334F6E43156) bool SC_LICENSEPLATE_GET_CHECK_IS_PENDING(any p0)l
extern _native64(0x700569DBA175A77C) int SC_LICENSEPLATE_GET_COUNT(int token)l
extern _native64(0x1D4446A62D35B0D0) const char* SC_LICENSEPLATE_GET_PLATE(int token, int plateIndex)l
extern _native64(0x2E89990DDFF670C3) const char* SC_LICENSEPLATE_GET_PLATE_DATA(int token, int plateIndex)l
extern _native64(0xD0EE05FE193646EA) bool SC_LICENSEPLATE_SET_PLATE_DATA(const char* oldPlateText, const char* newPlateText, any* plateData)l
extern _native64(0x1989C6E6F67E76A8) bool SC_LICENSEPLATE_ADD(const char* plateText, any* plateData, int* token)l
extern _native64(0x07C61676E5BB52CD) bool SC_LICENSEPLATE_GET_ADD_IS_PENDING(int token)l
extern _native64(0x8147FFF6A718E1AD) int SC_LICENSEPLATE_GET_ADD_STATUS(int token)l
extern _native64(0x0F73393BAC7E6730) bool SC_LICENSEPLATE_ISVALID(const char* plateText, int* token)l
extern _native64(0xD302E99EDF0449CF) bool SC_LICENSEPLATE_GET_ISVALID_IS_PENDING(int token)l
extern _native64(0x5C4EBFFA98BDB41C) int SC_LICENSEPLATE_GET_ISVALID_STATUS(int token)l
extern _native64(0xFF8F3A92B75ED67A) bool SC_COMMUNITY_EVENT_IS_ACTIVE()l
extern _native64(0x4ED9C8D6DA297639) int SC_COMMUNITY_EVENT_GET_EVENT_ID()l
extern _native64(0x710BCDA8071EDED1) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT(const char* p0, int* p1)l
extern _native64(0x50A8A36201DBF83E) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT(const char* p0, float* p1)l
extern _native64(0x9DE5D2F723575ED0) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING(const char* p0, char* p1)l
extern _native64(0xC2C97EA97711D1AE) bool SC_COMMUNITY_EVENT_GET_DISPLAY_NAME(char* p0)l
extern _native64(0x450819D8CF90C416) bool SC_COMMUNITY_EVENT_IS_ACTIVE_FOR_TYPE(const char* p0)l
extern _native64(0x4A7D6E727F941747) int SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE(const char* p0)l
extern _native64(0xE75A4A2E5E316D86) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_FOR_TYPE(const char* p0, int* p1, const char* p2)l
extern _native64(0x2570E26BE63964E3) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_FOR_TYPE(const char* p0, float* p1, const char* p2)l
extern _native64(0x1D12A56FC95BE92E) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_FOR_TYPE(const char* p0, char* p1, const char* p2)l
extern _native64(0x33DF47CC0642061B) bool SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_FOR_TYPE(char* p0, const char* p1)l
extern _native64(0xA468E0BE12B12C70) bool SC_COMMUNITY_EVENT_IS_ACTIVE_BY_ID(int p0)l
extern _native64(0x8CC469AB4D349B7C) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID(int p0, const char* p1, int* p2)l
extern _native64(0xC5A35C73B68F3C49) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_BY_ID(int p0, const char* p1, float* p2)l
extern _native64(0x699E4A5C8C893A18) bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID(int p0, const char* p1, char* p2)l
extern _native64(0x19853B5B17D77BCA) bool SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID(int p0, char* p1)l
extern _native64(0x6BFB12CE158E3DD4) bool SC_TRANSITION_NEWS_SHOW(any p0)l
extern _native64(0xFE4C1D0D3B9CC17E) bool SC_TRANSITION_NEWS_SHOW_TIMED(any p0, any p1)l
extern _native64(0xD8122C407663B995) bool SC_TRANSITION_NEWS_SHOW_NEXT_ITEM()l
extern _native64(0x3001BEF2FECA3680) bool SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU()l
extern _native64(0x92DA6E70EF249BD1) bool SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU(const char* p0, int* p1)l
extern _native64(0x675721C9F644D161) void SC_TRANSITION_NEWS_END()l
extern _native64(0xE4F6E8D07A2F0F51) bool SC_PAUSE_NEWS_INIT_STARTER_PACK(any p0)l
extern _native64(0x8A4416C0DB05FA66) bool SC_PAUSE_NEWS_GET_PENDING_STORY(any p0)l
extern _native64(0xEA95C0853A27888E) void SC_PAUSE_NEWS_SHUTDOWN()l
extern _native64(0x198D161F458ECC7F) const char* SC_ACCOUNT_INFO_GET_NICKNAME()l
extern _native64(0x225798743970412B) bool SC_ACHIEVEMENT_INFO_STATUS(int* p0)l
extern _native64(0x418DC16FAE452C1C) bool SC_HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId)l
#pragma endregion //}
#pragma region STATS //{
extern _native64(0xEB0A72181D4AA4AD) bool STAT_CLEAR_SLOT_FOR_RELOAD(int statSlot)l
extern _native64(0xA651443F437B1CE6) bool STAT_LOAD(int statSlot)l
extern _native64(0xE07BCA305B82D2FD) bool STAT_SAVE(int p0, bool p1, int p2, bool p3)l
extern _native64(0x5688585E6D563CD8) void STAT_SET_OPEN_SAVETYPE_IN_JOB(int p0)l
extern _native64(0xA1750FFAFA181661) bool STAT_LOAD_PENDING(int statSlot)l
extern _native64(0x7D3A583856F2C5AC) bool STAT_SAVE_PENDING()l
extern _native64(0xBBB6AD006F1BBEA3) bool STAT_SAVE_PENDING_OR_REQUESTED()l
extern _native64(0x49A49BED12794D70) bool STAT_DELETE_SLOT(int p0)l
extern _native64(0x0D0A9F0E7BD91E3C) bool STAT_SLOT_IS_LOADED(int statSlot)l
extern _native64(0x7F2C4CDF2E82DF4C) bool STAT_CLOUD_SLOT_LOAD_FAILED(int p0)l
extern _native64(0xE496A53BA5F50A56) int STAT_CLOUD_SLOT_LOAD_FAILED_CODE(any p0)l
extern _native64(0xF434A10BA01C37D0) void STAT_SET_BLOCK_SAVES(bool toggle)l
extern _native64(0x6A7F19756F1A9016) bool STAT_GET_BLOCK_SAVES()l
extern _native64(0x7E6946F68A38B74F) bool STAT_CLOUD_SLOT_SAVE_FAILED(any p0)l
extern _native64(0xA8733668D1047B51) void STAT_CLEAR_PENDING_SAVES(any p0)l
extern _native64(0xECB41AC6AB754401) bool STAT_LOAD_DIRTY_READ_DETECTED()l
extern _native64(0x9B4BD21D69B1E609) void STAT_CLEAR_DIRTY_READ_DETECTED()l
extern _native64(0xC0E0D686DDFC6EAE) bool STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP()l
extern _native64(0xD69CE161FE614531) Hash _GET_STAT_HASH_FOR_CHARACTER_STAT(int dataType, int statIndex, int charSlot)l
extern _native64(0xB3271D7AB655B441) bool STAT_SET_INT(Hash statName, int value, bool save)l
extern _native64(0x4851997F37FE9B3C) bool STAT_SET_FLOAT(Hash statName, float value, bool save)l
extern _native64(0x4B33C4243DE0C432) bool STAT_SET_BOOL(Hash statName, bool value, bool save)l
extern _native64(0x17695002FD8B2AE0) bool STAT_SET_GXT_LABEL(Hash statName, const char* value, bool save)l
extern _native64(0x2C29BFB64F4FCBE4) bool STAT_SET_DATE(Hash statName, any* value, int numFields, bool save)l
extern _native64(0xA87B2335D12531D7) bool STAT_SET_STRING(Hash statName, const char* value, bool save)l
extern _native64(0xDB283FDE680FE72E) bool STAT_SET_POS(Hash statName, float x, float y, float z, bool save)l
extern _native64(0x7BBB1B54583ED410) bool STAT_SET_MASKED_INT(Hash statName, int p1, int p2, int p3, bool save)l
extern _native64(0x8CDDF1E452BABE11) bool STAT_SET_USER_ID(Hash statName, const char* value, bool save)l
extern _native64(0xC2F84B7F9C4D0C61) bool STAT_SET_CURRENT_POSIX_TIME(Hash statName, bool p1)l
extern _native64(0x767FBC2AC802EF3D) bool STAT_GET_INT(Hash statHash, int* outValue, int p2)l
extern _native64(0xD7AE6C9C9C6AC54C) bool STAT_GET_FLOAT(Hash statHash, float* outValue, any p2)l
extern _native64(0x11B5E6D2AE73F48E) bool STAT_GET_BOOL(Hash statHash, bool* outValue, any p2)l
extern _native64(0x8B0FACEFC36C824B) bool STAT_GET_DATE(Hash statHash, any* outValue, int numFields, any p3)l
extern _native64(0xE50384ACC2C3DB74) const char* STAT_GET_STRING(Hash statHash, int p1)l
extern _native64(0x350F82CCB186AA1B) bool STAT_GET_POS(Hash statName, float* outX, float* outY, float* outZ, any p4)l
extern _native64(0x655185A06D9EEAAB) bool STAT_GET_MASKED_INT(Hash statHash, int* outValue, int p2, int p3, any p4)l
extern _native64(0x2365C388E393BBE2) const char* STAT_GET_USER_ID(Hash statHash)l
extern _native64(0x5473D4195058B2E4) const char* STAT_GET_LICENSE_PLATE(Hash statName)l
extern _native64(0x69FF13266D7296DA) bool STAT_SET_LICENSE_PLATE(Hash statName, const char* str)l
extern _native64(0x9B5A68C6489E9909) void STAT_INCREMENT(Hash statName, float value)l
extern _native64(0x5A556B229A169402) bool STAT_COMMUNITY_START_SYNCH()l
extern _native64(0xB1D2BB1E1631F5B1) bool STAT_COMMUNITY_SYNCH_IS_PENDING()l
extern _native64(0xBED9F5693F34ED17) bool STAT_COMMUNITY_GET_HISTORY(Hash statName, int p1, float* outValue)l
extern _native64(0x26D7399B9587FE89) void STAT_RESET_ALL_ONLINE_CHARACTER_STATS(int p0)l
extern _native64(0xA78B8FA58200DA56) void STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS(int p0)l
extern _native64(0xE0E854F5280FB769) int STAT_GET_NUMBER_OF_DAYS(Hash statName)l
extern _native64(0xF2D4B2FE415AAFC3) int STAT_GET_NUMBER_OF_HOURS(Hash statName)l
extern _native64(0x7583B4BE4C5A41B5) int STAT_GET_NUMBER_OF_MINUTES(Hash statName)l
extern _native64(0x2CE056FF3723F00B) int STAT_GET_NUMBER_OF_SECONDS(Hash statName)l
extern _native64(0x68F01422BE1D838F) void STAT_SET_PROFILE_SETTING_VALUE(int profileSetting, int value)l
extern _native64(0xC01D2470F22CDE5A) void STATS_COMPLETED_CHARACTER_CREATION(any p0)l
extern _native64(0x94F12ABF9C79E339) int PACKED_STAT_GET_INT_STAT_INDEX(int p0)l
extern _native64(0x61E111E323419E07) Hash GET_PACKED_INT_STAT_KEY(int index, bool spStat, bool charStat, int character)l
extern _native64(0xD16C2AD6B8E32854) Hash GET_PACKED_TU_INT_STAT_KEY(int index, bool spStat, bool charStat, int character)l
extern _native64(0x2B4CDCA6F07FF3DA) Hash GET_PACKED_NG_INT_STAT_KEY(int index, bool spStat, bool charStat, int character, const char* section)l
extern _native64(0xDA7EBFC49AE3F1B0) bool GET_PACKED_STAT_BOOL_CODE(int index, int characterSlot)l
extern _native64(0x0BC900A6FE73770C) int GET_PACKED_STAT_INT_CODE(int index, int characterSlot)l
extern _native64(0xDB8A58AEAA67CD07) void SET_PACKED_STAT_BOOL_CODE(int index, bool value, int characterSlot)l
extern _native64(0x1581503AE529CD2E) void SET_PACKED_STAT_INT_CODE(int index, int value, int characterSlot)l
extern _native64(0x5009DFD741329729) void PLAYSTATS_BACKGROUND_SCRIPT_ACTION(const char* action, int value)l
extern _native64(0xE6A27CDA42887F93) void _PLAYSTATS_FLOW_LOW(float posX, float posY, float posZ, const char* p3, any p4, int amount)l
extern _native64(0x93054C88E6AA7C44) void PLAYSTATS_NPC_INVITE(const char* p0)l
extern _native64(0x46F917F6B4128FE4) void PLAYSTATS_AWARD_XP(int amount, Hash type, Hash category)l
extern _native64(0xC7F2DE41D102BFB4) void PLAYSTATS_RANK_UP(int rank)l
extern _native64(0x098760C7461724CD) void PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE()l
extern _native64(0xA071E0ED98F91286) void PLAYSTATS_ACTIVITY_DONE(int p0, int activityId)l
extern _native64(0xC5BE134EC7BA96A0) void PLAYSTATS_LEAVE_JOB_CHAIN(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xC19A2925C34D2231) void PLAYSTATS_MISSION_STARTED(const char* p0, any p1, any p2, bool p3)l
extern _native64(0x7C4BB33A8CED7324) void PLAYSTATS_MISSION_OVER(const char* p0, any p1, any p2, bool p3, bool p4, bool p5)l
extern _native64(0xC900596A63978C1D) void PLAYSTATS_MISSION_CHECKPOINT(const char* p0, any p1, any p2, any p3)l
extern _native64(0x71862B1D855F32E1) void PLAYSTATS_RANDOM_MISSION_DONE(const char* name, any p1, any p2, any p3)l
extern _native64(0x121FB4DDDC2D5291) void PLAYSTATS_ROS_BET(int amount, int act, Player player, float cm)l
extern _native64(0x9C375C315099DDE4) void PLAYSTATS_RACE_CHECKPOINT(Vehicle p0, any p1, int p2, int p3, any p4)l
extern _native64(0x6DEE77AFF8C21BD1) bool PLAYSTATS_CREATE_MATCH_HISTORY_ID_2(int* playerAccountId, int* posixTime)l
extern _native64(0xBC80E22DED931E3D) void PLAYSTATS_MATCH_STARTED(any p0, any p1, any p2)l
extern _native64(0x176852ACAAC173D1) void PLAYSTATS_SHOP_ITEM(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x1CAE5D2E3F9A07F0) void PLAYSTATS_CRATE_DROP_MISSION_DONE(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native64(0xAFC7E5E075A96F46) void PLAYSTATS_CRATE_CREATED(float p0, float p1, float p2)l
extern _native64(0xCB00196B31C39EB1) void PLAYSTATS_HOLD_UP_MISSION_DONE(any p0, any p1, any p2, any p3)l
extern _native64(0x2B69F5074C894811) void PLAYSTATS_IMPORT_EXPORT_MISSION_DONE(any p0, any p1, any p2, any p3)l
extern _native64(0xADDD1C754E2E2914) void PLAYSTATS_RACE_TO_POINT_MISSION_DONE(int p0, any p1, any p2, any p3)l
extern _native64(0x79AB33F0FBFAC40C) void PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE(any p0)l
extern _native64(0xDDF24D535060F811) void PLAYSTATS_WEBSITE_VISITED(Hash scaleformHash, int p1)l
extern _native64(0x0F71DE29AB2258F1) void PLAYSTATS_FRIEND_ACTIVITY(int p0, bool p1)l
extern _native64(0x69DEA3E9DB727B4C) void PLAYSTATS_ODDJOB_DONE(int totalTimeMs, int p1, bool p2)l
extern _native64(0xBA739D6D5A05D6E7) void PLAYSTATS_PROP_CHANGE(Ped p0, int p1, int p2, int p3)l
extern _native64(0x34B973047A2268B9) void PLAYSTATS_CLOTH_CHANGE(Ped p0, any p1, any p2, any p3, any p4)l
extern _native64(0xE95C8A1875A02CA4) void PLAYSTATS_WEAPON_MODE_CHANGE(Hash weaponHash, Hash componentHashTo, Hash componentHashFrom)l
extern _native64(0x6058665D72302D3F) void PLAYSTATS_CHEAT_APPLIED(const char* cheat)l
extern _native64(0xF8C54A461C3E11DC) void PLAYSTATS_JOB_ACTIVITY_END(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0xF5BB8DAC426A52C0) void PLAYSTATS_JOB_BEND(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0xA736CF7FB7C5BFF4) void PLAYSTATS_JOB_LTS_END(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0x14E0B2D1AD1044E0) void PLAYSTATS_JOB_LTS_ROUND_END(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0x90D0622866E80445) void PLAYSTATS_QUICKFIX_TOOL(int element, const char* item)l
extern _native64(0x5DA3A8DE8CB6226F) void PLAYSTATS_IDLE_KICK(int msStoodIdle)l
extern _native64(0xD1032E482629049E) void PLAYSTATS_SET_JOIN_TYPE(int joinType)l
extern _native64(0xF4FF020A08BC8863) void PLAYSTATS_HEIST_SAVE_CHEAT(Hash hash, int p1)l
extern _native64(0x46326E13DA4E0546) void PLAYSTATS_APPEND_DIRECTOR_METRIC(any* p0)l
extern _native64(0x47B32F5611E6E483) void PLAYSTATS_AWARD_BAD_SPORT(int id)l
extern _native64(0x9572BD4DD6B72122) void PLAYSTATS_PEGASUS_AS_PERSONAL_AIRCRAFT(Hash modelHash)l
extern _native64(0xF96E9EA876D9DC92) void _PLAYSTATS_SHOPMENU_NAV(any p0, any p1, any p2)l
extern _native64(0x6A60E43998228229) void PLAYSTATS_FM_EVENT_CHALLENGES(any p0)l
extern _native64(0xBFAFDB5FAAA5C5AB) void PLAYSTATS_FM_EVENT_VEHICLETARGET(any p0)l
extern _native64(0x8C9D11605E59D955) void PLAYSTATS_FM_EVENT_URBANWARFARE(any p0)l
extern _native64(0x3DE3AA516FB126A4) void PLAYSTATS_FM_EVENT_CHECKPOINTCOLLECTION(any p0)l
extern _native64(0xBAA2F0490E146BE8) void PLAYSTATS_FM_EVENT_ATOB(any p0)l
extern _native64(0x1A7CE7CD3E653485) void PLAYSTATS_FM_EVENT_PENNEDIN(any p0)l
extern _native64(0x419615486BBF1956) void PLAYSTATS_FM_EVENT_PASSTHEPARCEL(any p0)l
extern _native64(0x84DFC579C2FC214C) void PLAYSTATS_FM_EVENT_HOTPROPERTY(any p0)l
extern _native64(0x0A9C7F36E5D7B683) void PLAYSTATS_FM_EVENT_DEADDROP(any p0)l
extern _native64(0x164C5FF663790845) void PLAYSTATS_FM_EVENT_KINGOFTHECASTLE(any p0)l
extern _native64(0xEDBF6C9B0D2C65C8) void PLAYSTATS_FM_EVENT_CRIMINALDAMAGE(any p0)l
extern _native64(0x6551B1F7F6CD46EA) void PLAYSTATS_FM_EVENT_COMPETITIVEURBANWARFARE(any p0)l
extern _native64(0x2CD90358F67D0AA8) void PLAYSTATS_FM_EVENT_HUNTBEAST(any p0)l
extern _native64(0x203B381133817079) void PLAYSTATS_PIMENU_HIDE_OPTIONS(any* data)l
extern _native64(0x117B45156D7EFF2E) int LEADERBOARDS_GET_NUMBER_OF_COLUMNS(int p0, any p1)l
extern _native64(0xC4B5467A1886EA7E) int LEADERBOARDS_GET_COLUMN_ID(int p0, int p1, int p2)l
extern _native64(0xBF4FEF46DB7894D3) int LEADERBOARDS_GET_COLUMN_TYPE(int p0, any p1, any p2)l
extern _native64(0xA34CB6E6F0DF4A0B) int LEADERBOARDS_READ_CLEAR_ALL()l
extern _native64(0x7CCE5C737A665701) int LEADERBOARDS_READ_CLEAR(any p0, any p1, any p2)l
extern _native64(0xAC392C8483342AC2) bool LEADERBOARDS_READ_PENDING(any p0, any p1, any p2)l
extern _native64(0xA31FD15197B192BD) bool LEADERBOARDS_READ_ANY_PENDING()l
extern _native64(0x2FB19228983E832C) bool LEADERBOARDS_READ_SUCCESSFUL(any p0, any p1, any p2)l
extern _native64(0x918B101666F9CB83) bool LEADERBOARDS2_READ_FRIENDS_BY_ROW(any* p0, any* p1, any p2, bool p3, any p4, any p5)l
extern _native64(0xC30713A383BFBF0E) bool LEADERBOARDS2_READ_BY_HANDLE(any* p0, any* p1)l
extern _native64(0xA9CDB1E3F0A49883) bool LEADERBOARDS2_READ_BY_ROW(any* p0, any* p1, any p2, any* p3, any p4, any* p5, any p6)l
extern _native64(0xBA2C7DB0C129449A) bool LEADERBOARDS2_READ_BY_RANK(any* p0, any p1, any p2)l
extern _native64(0x5CE587FB5A42C8C4) bool LEADERBOARDS2_READ_BY_RADIUS(any* p0, any p1, any* p2)l
extern _native64(0x7EEC7E4F6984A16A) bool LEADERBOARDS2_READ_BY_SCORE_INT(any* p0, any p1, any p2)l
extern _native64(0xE662C8B759D08F3C) bool LEADERBOARDS2_READ_BY_SCORE_FLOAT(any* p0, float p1, any p2)l
extern _native64(0xC38DC1E90D22547C) bool LEADERBOARDS2_READ_RANK_PREDICTION(any* p0, any* p1, any* p2)l
extern _native64(0xF1AE5DCDBFCA2721) bool LEADERBOARDS2_READ_BY_PLAFORM(any* p0, const char* gamerHandleCsv, const char* platformName)l
extern _native64(0xA0F93D5465B3094D) bool LEADERBOARDS2_READ_GET_ROW_DATA_START(any* p0)l
extern _native64(0x71B008056E5692D6) void LEADERBOARDS2_READ_GET_ROW_DATA_END()l
extern _native64(0x34770B9CE0E03B91) bool LEADERBOARDS2_READ_GET_ROW_DATA_INFO(any p0, any* p1)l
extern _native64(0x88578F6EC36B4A3A) int LEADERBOARDS2_READ_GET_ROW_DATA_INT(any p0, any p1)l
extern _native64(0x38491439B6BA7F7D) float LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT(any p0, any p1)l
extern _native64(0xAE2206545888AE49) bool LEADERBOARDS2_WRITE_DATA(any* p0)l
extern _native64(0x0BCA1D2C47B0D269) void LEADERBOARDS_WRITE_ADD_COLUMN(any p0, any p1, float p2)l
extern _native64(0x2E65248609523599) void LEADERBOARDS_WRITE_ADD_COLUMN_LONG(any p0, any p1, any p2)l
extern _native64(0xB9BB18E2C40142ED) bool LEADERBOARDS_CACHE_DATA_ROW(any* p0)l
extern _native64(0xD4B02A6B476E1FDC) void LEADERBOARDS_CLEAR_CACHE_DATA()l
extern _native64(0x8EC74CEB042E7CFF) void LEADERBOARDS_CLEAR_CACHE_DATA_ID(any p0)l
extern _native64(0x9C51349BE6CDFE2C) bool LEADERBOARDS_GET_CACHE_EXISTS(any p0)l
extern _native64(0xF04C1C27DA35F6C8) int LEADERBOARDS_GET_CACHE_TIME(any p0)l
extern _native64(0x58A651CD201D89AD) int LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS(any p0)l
extern _native64(0x9120E8DBA3D69273) bool LEADERBOARDS_GET_CACHE_DATA_ROW(any p0, any p1, any* p2)l
extern _native64(0x11FF1C80276097ED) void PRESENCE_EVENT_UPDATESTAT_INT(Hash statHash, int value, int p2)l
extern _native64(0x30A6614C1F7799B8) void PRESENCE_EVENT_UPDATESTAT_FLOAT(Hash statHash, float value, int p2)l
extern _native64(0x6483C25849031C4F) void PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING(Hash statHash, int value, int p2, const char* string)l
extern _native64(0x5EAD2BF6484852E4) bool GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES()l
extern _native64(0xC141B8917E0017EC) void SET_HAS_POSTED_ALL_VEHICLES_DRIVEN()l
extern _native64(0xB475F27C6A994D65) void SET_PROFILE_SETTING_PROLOGUE_COMPLETE()l
extern _native64(0xC67E2DA1CBE759E2) void SET_PROFILE_SETTING_SP_CHOP_MISSION_COMPLETE()l
extern _native64(0xF1A1803D3476F215) void SET_PROFILE_SETTING_CREATOR_RACES_DONE(int value)l
extern _native64(0x38BAAA5DD4C9D19F) void SET_PROFILE_SETTING_CREATOR_DM_DONE(int value)l
extern _native64(0x55384438FC55AD8E) void SET_PROFILE_SETTING_CREATOR_CTF_DONE(int value)l
extern _native64(0x723C1CE13FBFDB67) void SET_JOB_ACTIVITY_ID_STARTED(any p0, int characterSlot)l
extern _native64(0x0D01D20616FC73FB) void SET_FREEMODE_PROLOGUE_DONE(any p0, int characterSlot)l
extern _native64(0x79D310A861697CC9) void SET_FREEMODE_STRAND_PROGRESSION_STATUS(int profileSetting, int settingValue)l
extern _native64(0x428EAF89E24F6C36) void STAT_NETWORK_INCREMENT_ON_SUICIDE(any p0, float p1)l
extern _native64(0x047CBED6F6F8B63C) void STAT_SET_CHEAT_IS_ACTIVE()l
extern _native64(0xC980E62E33DF1D5C) bool LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE(any* p0, any* p1)l
extern _native64(0x6F361B8889A792A3) void FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE()l
extern _native64(0xC847B43F369AC0B5) void STAT_MIGRATE_CLEAR_FOR_RESTART()l
extern _native64(0xA5C80D8E768A9E66) bool STAT_MIGRATE_SAVEGAME_START(const char* platformName)l
extern _native64(0x9A62EC95AE10E011) int STAT_MIGRATE_SAVEGAME_GET_STATUS()l
extern _native64(0x4C89FE2BDEB3F169) bool STAT_MIGRATE_CHECK_ALREADY_DONE()l
extern _native64(0xC6E0E2616A7576BB) bool STAT_MIGRATE_CHECK_START()l
extern _native64(0x5BD5F255321C4AAF) int STAT_MIGRATE_CHECK_GET_IS_PLATFORM_AVAILABLE(int p0)l
extern _native64(0xDEAAF77EB3687E97) int STAT_MIGRATE_CHECK_GET_PLATFORM_STATUS(int p0, any* p1)l
extern _native64(0x886913BBEACA68C1) int STAT_GET_SAVE_MIGRATION_STATUS(any* data)l
extern _native64(0x4FEF53183C3C6414) bool STAT_SAVE_MIGRATION_CANCEL_PENDING_OPERATION()l
extern _native64(0x567384DFA67029E6) int STAT_GET_CANCEL_SAVE_MIGRATION_STATUS()l
extern _native64(0x3270F67EED31FBC1) bool STAT_SAVE_MIGRATION_CONSUME_CONTENT(Hash contentId, const char* srcPlatform, const char* srcGamerHandle)l
extern _native64(0xCE5AA445ABA8DEE0) int STAT_GET_SAVE_MIGRATION_CONSUME_CONTENT_STATUS(int* p0)l
extern _native64(0x98E2BC1CA26287C3) void STAT_ENABLE_STATS_TRACKING()l
extern _native64(0x629526ABA383BCAA) void STAT_DISABLE_STATS_TRACKING()l
extern _native64(0xBE3DB208333D9844) bool STAT_IS_STATS_TRACKING_ENABLED()l
extern _native64(0x33D72899E24C3365) bool STAT_START_RECORD_STAT(int statType, int valueType)l
extern _native64(0xA761D4AC6115623D) bool STAT_STOP_RECORD_STAT()l
extern _native64(0xF11F01D98113536A) bool STAT_GET_RECORDED_VALUE(float* value)l
extern _native64(0x8B9CDBD6C566C38C) bool STAT_IS_RECORDING_STAT()l
extern _native64(0xE8853FBCE7D8D0D6) int STAT_GET_CURRENT_NEAR_MISS_NOCRASH_PRECISE()l
extern _native64(0xA943FD1722E11EFD) float STAT_GET_CURRENT_REAR_WHEEL_DISTANCE()l
extern _native64(0x84A810B375E69C0E) float STAT_GET_CURRENT_FRONT_WHEEL_DISTANCE()l
extern _native64(0x9EC8858184CD253A) float STAT_GET_CURRENT_JUMP_DISTANCE()l
extern _native64(0xBA9749CC94C1FD85) float STAT_GET_CURRENT_DRIVE_NOCRASH_DISTANCE()l
extern _native64(0x55A8BECAF28A4EB7) float STAT_GET_CURRENT_SPEED()l
extern _native64(0x32CAC93C9DE73D32) float STAT_GET_CURRENT_DRIVING_REVERSE_DISTANCE()l
extern _native64(0xAFF47709F1D5DCCE) float STAT_GET_CURRENT_SKYDIVING_DISTANCE()l
extern _native64(0x6E0A5253375C4584) float STAT_GET_CHALLENGE_FLYING_DIST()l
extern _native64(0x1A8EA222F9C67DBB) bool STAT_GET_FLYING_ALTITUDE(float* outValue)l
extern _native64(0xF9F2922717B819EC) bool STAT_IS_PLAYER_VEHICLE_ABOVE_OCEAN()l
extern _native64(0x0B8B7F74BF061C6D) float STAT_GET_VEHICLE_BAIL_DISTANCE()l
extern _native64(0xB3DA2606774A8E2D) bool STAT_ROLLBACK_SAVE_MIGRATION()l
extern _native64(0xDAC073C7901F9E15) void SET_HAS_SPECIALEDITION_CONTENT(int value)l
extern _native64(0xF6792800AC95350D) void SET_SAVE_MIGRATION_TRANSACTION_ID_WARNING(int transactionId)l
extern _native64(0x6BC0ACD0673ACEBE) void GET_BOSS_GOON_UUID(int characterSlot, any p1, any p2)l
extern _native64(0x8D8ADB562F09A245) void PLAYSTATS_BW_BOSSONBOSSDEATHMATCH(any p0)l
extern _native64(0xD1A1EE3B4FA8E760) void PLAYSTATS_BW_YATCHATTACK(any p0)l
extern _native64(0x88087EE1F28024AE) void PLAYSTATS_BW_HUNT_THE_BOSS(any p0)l
extern _native64(0xFCC228E07217FCAC) void PLAYSTATS_BW_SIGHTSEER(any p0)l
extern _native64(0x678F86D8FC040BDB) void PLAYSTATS_BW_ASSAULT(any p0)l
extern _native64(0xA6F54BB2FFCA35EA) void PLAYSTATS_BW_BELLY_OF_THE_BEAST(any p0)l
extern _native64(0x5FF2C33B13A02A11) void PLAYSTATS_BW_HEAD_HUNTER(any p0)l
extern _native64(0x282B6739644F4347) void PLAYSTATS_BW_FRAGILE_GOODS(any p0)l
extern _native64(0xF06A6F41CB445443) void PLAYSTATS_BW_AIR_FREIGHT(any p0)l
extern _native64(0x7B18DA61F6BAE9D5) void PLAYSTATS_BC_CAR_JACKING(any p0)l
extern _native64(0x06EAF70AE066441E) void PLAYSTATS_BC_SMASH_AND_GRAB(any p0)l
extern _native64(0x14EDA9EE27BD1626) void PLAYSTATS_BC_PROTECTION_RACKET(any p0)l
extern _native64(0x930F504203F561C9) void PLAYSTATS_BC_MOST_WANTED(any p0)l
extern _native64(0xE3261D791EB44ACB) void PLAYSTATS_BC_FINDERS_KEEPERS(any p0)l
extern _native64(0x73001E34F85137F8) void PLAYSTATS_BC_POINT_TO_POINT(any p0)l
extern _native64(0x53CAE13E9B426993) void PLAYSTATS_BC_CASHING(any p0)l
extern _native64(0x7D36291161859389) void PLAYSTATS_BC_SALVAGE(any p0)l
extern _native64(0xBE509B0A3693DE8B) void PLAYSTATS_SPENT_PI_CUSTOM_LOADOUT(int amount)l
extern _native64(0xD6781E42755531F7) void PLAYSTATS_BUY_CONTRABAND_MISSION(any* data)l
extern _native64(0xC729991A9065376E) void PLAYSTATS_SELL_CONTRABAND_MISSION(any* data)l
extern _native64(0x2605663BD4F23B5D) void PLAYSTATS_DEFEND_CONTRABAND_MISSION(any* data)l
extern _native64(0x04D90BA8207ADA2D) void PLAYSTATS_RECOVER_CONTRABAND_MISSION(any* data)l
extern _native64(0x60EEDC12AF66E846) void PLAYSTATS_HIT_CONTRABAND_DESTROY_LIMIT(any p0)l
extern _native64(0x3EBEAC6C3F81F6BD) void START_BEING_BOSS(any p0, any p1)l
extern _native64(0x96E6D5150DBF1C09) void START_BEING_GOON(any p0, any p1, any p2)l
extern _native64(0xA3C53804BDB68ED2) void END_BEING_BOSS(any p0, any p1, any p2)l
extern _native64(0x6BCCF9948492FD85) void END_BEING_GOON(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x792271AB35C356A4) void HIRED_LIMO(any p0, any p1)l
extern _native64(0xCEA553E35C2246E1) void ORDER_BOSS_VEHICLE(any p0, any p1, Hash vehicleHash)l
extern _native64(0xD1C9B92BDD3F151D) void CHANGE_UNIFORM(any p0, any p1, any p2)l
extern _native64(0x44919CC079BB60BF) void CHANGE_GOON_LOOKING_FOR_WORK(any p0)l
extern _native64(0x7033EEFD9B28088E) void SEND_METRIC_GHOSTING_TO_PLAYER(any p0)l
extern _native64(0xAA525DFF66BB82F5) void SEND_METRIC_VIP_POACH(any p0, any p1, any p2)l
extern _native64(0x015B03EE1C43E6EC) void SEND_METRIC_PUNISH_BODYGUARD(any p0)l
extern _native64(0x928DBFB892638EF3) void PLAYSTATS_START_TRACKING_STUNTS()l
extern _native64(0x8A800DACCC0DA55D) void PLAYSTATS_STOP_TRACKING_STUNTS()l
extern _native64(0xBF371CD2B64212FD) void PLAYSTATS_MISSION_ENDED(any p0)l
extern _native64(0x7D8BA05688AD64C7) void PLAYSTATS_IMPEXP_MISSION_ENDED(any p0)l
extern _native64(0x0B565B0AAE56A0E8) void PLAYSTATS_CHANGE_MC_ROLE(any p0, any p1, any p2, any p3, int role, int p5, any p6)l
extern _native64(0x28ECB8AC2F607DB2) void PLAYSTATS_CHANGE_MC_OUTFIT(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x0A50D2604E05CB94) void PLAYSTATS_SWITCH_MC_EMBLEM(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xCC25A4553DFBF9EA) void PLAYSTATS_MC_REQUEST_BIKE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xF534D94DFA2EAD26) void PLAYSTATS_MC_KILLED_RIVAL_MC_MEMBER(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xD558BEC0BBA7E8D2) void PLAYSTATS_ABANDONED_MC(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x501478855A6074CE) void PLAYSTATS_EARNED_MC_POINTS(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x03C2EEBB04B3FB72) void PLAYSTATS_MC_FORMATION_ENDS(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x8989CBD7B4E82534) void PLAYSTATS_MC_CLUBHOUSE_ACTIVITY(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native64(0x27AA1C973CACFE63) void PLAYSTATS_RIVAL_BEHAVIOR(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9)l
extern _native64(0xB7257BA2550EA10A) void PLAYSTATS_COPY_RANK_INTO_NEW_SLOT(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x848B66100EE33B05) void PLAYSTATS_DUPE_DETECTED(any* data)l
extern _native64(0x516FC96EB88EEFE5) void PLAYSTATS_BAN_ALERT(int p0)l
extern _native64(0x0EACDF8487D5155A) void PLAYSTATS_GUNRUNNING_MISSION_ENDED(any* data)l
extern _native64(0xDAF80797FC534BEC) void PLAYSTATS_GUNRUNNING_RND(any p0)l
extern _native64(0x316DB59CD14C1774) void PLAYSTATS_BUSINESS_BATTLE_ENDED(any p0)l
extern _native64(0x2D7A9B577E72385E) void PLAYSTATS_WAREHOUSE_MISSION_ENDED(any p0)l
extern _native64(0x830C3A44EB3F2CF9) void PLAYSTATS_NIGHTCLUB_MISSION_ENDED(any p0)l
extern _native64(0xB26F670685631727) void PLAYSTATS_DJ_USAGE(any p0, any p1)l
extern _native64(0xC14BD9F5337219B2) void PLAYSTATS_MINIGAME_USAGE(any p0, any p1, any p2)l
extern _native64(0x35E39E5570358630) void PLAYSTATS_STONE_HATCHET_ENDED(any* data)l
extern _native64(0x320C35147D5B5DDD) void PLAYSTATS_SMUGGLER_MISSION_ENDED(any* data)l
extern _native64(0xD8AFB345A9C5CCBB) void PLAYSTATS_FM_HEIST_PREP_ENDED(any* data)l
extern _native64(0x1E1497D0D2108115) void PLAYSTATS_INSTANCED_HEIST_ENDED(any* data, any p1, any p2, any p3)l
extern _native64(0x0BC254FF3A911501) void PLAYSTATS_DAR_CHECKPOINT(any* data)l
extern _native64(0x878FF156D36E9956) void PLAYSTATS_ENTER_SESSION_PACK(any* data)l
extern _native64(0x66C7BB2416ED3FCE) void PLAYSTATS_DRONE_USAGE(int p0, int p1, int p2)l
extern _native64(0x6731DE84A38BFAD0) void PLAYSTATS_SPIN_WHEEL(int p0, int p1, int p2, int p3)l
extern _native64(0x6F4F599753F8200A) void PLAYSTATS_ARENA_WARS_SPECTATOR(int p0, int p1, int p2, int p3, int p4)l
extern _native64(0xB479D9F0D48A1BC5) void PLAYSTATS_ARENA_WARS_ENDED(any* data)l
extern _native64(0x35EEC6C2BC821A71) void PLAYSTATS_SWITCH_PASSIVE_MODE(bool p0, int p1, int p2, int p3)l
extern _native64(0xCD0A8A9338681CF2) void PLAYSTATS_COLLECTIBLE_PICKED_UP(int p0, Hash objectHash, any p2, any p3, int moneyAmount, int rpAmount, int chipsAmount, any p7, int p8, any p9, any p10)l
extern _native64(0xFCCCAC2BD3C1F180) void PLAYSTATS_CASINO_STORY_MISSION_ENDED(any p0, any p1)l
extern _native64(0x0999F3F090EC5012) void PLAYSTATS_CASINO_CHIP(any p0)l
extern _native64(0x95101C443A84E7F1) void PLAYSTATS_CASINO_ROULETTE(any p0)l
extern _native64(0x3EAE97309727E7AD) void PLAYSTATS_CASINO_BLACKJACK(any p0)l
extern _native64(0xF740FB339D471C35) void PLAYSTATS_CASINO_THREE_CARD_POKER(any p0)l
extern _native64(0xEF5EC67D392B830A) void PLAYSTATS_CASINO_SLOT_MACHINE(any p0)l
extern _native64(0x049F059625058A86) void PLAYSTATS_CASINO_INSIDE_TRACK(any p0)l
extern _native64(0x0C432C1435F5E4FA) void PLAYSTATS_CASINO_LUCKY_SEVEN(any p0)l
extern _native64(0x6572ABA3DE1197FC) void PLAYSTATS_CASINO_ROULETTE_LIGHT(any p0)l
extern _native64(0xD5451C7BF151EB6F) void PLAYSTATS_CASINO_BLACKJACK_LIGHT(any p0)l
extern _native64(0xC9001364B4388F22) void PLAYSTATS_CASINO_THREE_CARD_POKER_LIGHT(any p0)l
extern _native64(0xE60054A0FAE8227F) void PLAYSTATS_CASINO_SLOT_MACHINE_LIGHT(any p0)l
extern _native64(0x23A3CBCD50D54E47) void PLAYSTATS_CASINO_INSIDE_TRACK_LIGHT(any p0)l
extern _native64(0x533A7D1EA58DF958) void PLAYSTATS_ARCADE_GAME(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x4FCDBD3F0A813C25) void PLAYSTATS_ARCADE_LOVE_MATCH(any p0, any p1)l
extern _native64(0x1A0D4A6C336B7BC5) void PLAYSTATS_FREEMODE_CASINO_MISSION_ENDED(any* data)l
extern _native64(0xDFBD93BF2943E29B) void PLAYSTATS_HEIST3_DRONE(any p0)l
extern _native64(0x92FC0EEDFAC04A14) void PLAYSTATS_HEIST3_HACK(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x0077F15613D36993) void PLAYSTATS_NPC_PHONE(any* p0)l
extern _native64(0xF9096193DF1F99D4) void PLAYSTATS_ARCADE_CABINET(any p0)l
extern _native64(0x2E0259BABC27A327) void PLAYSTATS_HEIST3_FINALE(any p0)l
extern _native64(0x53C31853EC9531FF) void PLAYSTATS_HEIST3_PREP(any p0)l
extern _native64(0x810B5FCC52EC7FF0) void PLAYSTATS_MASTER_CONTROL(any p0, any p1, any p2, any p3)l
extern _native64(0x5BF29846C6527C54) void PLAYSTATS_QUIT_MODE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xC03FAB2C2F92289B) void PLAYSTATS_MISSION_VOTE(any p0)l
extern _native64(0x5CDAED54B34B0ED0) void PLAYSTATS_NJVS_VOTE(any p0)l
extern _native64(0x4AFF7E02E485E92B) void PLAYSTATS_KILL_YOURSELF()l
extern _native64(0x46A70777BE6CEAB9) void PLAYSTATS_FM_MISSION_END(any p0, any p1, any p2)l
extern _native64(0xDFCDB14317A9B361) void PLAYSTATS_HEIST4_PREP(any p0)l
extern _native64(0xC1E963C58664B556) void PLAYSTATS_HEIST4_FINALE(any p0)l
extern _native64(0x2FA3173480008493) void PLAYSTATS_HEIST4_HACK(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xD4367D310F079DB0) void PLAYSTATS_SUB_WEAP(any p0, any p1, any p2, any p3)l
extern _native64(0x4DC416F246A41FC8) void PLAYSTATS_FAST_TRVL(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10)l
extern _native64(0x2818FF6638CB09DE) void PLAYSTATS_HUB_ENTRY(any p0)l
extern _native64(0xD6CA58B3B53A0F22) void PLAYSTATS_DJ_MISSION_ENDED(any p0)l
extern _native64(0x1A67DFBF1F5C3835) void PLAYSTATS_ROBBERY_PREP(any p0)l
extern _native64(0xBBA55BE9AAAABF44) void PLAYSTATS_ROBBERY_FINALE(any p0)l
extern _native64(0xFA5B74BAB8A7EF99) void PLAYSTATS_EXTRA_EVENT(any p0)l
extern _native64(0xFF14D6FEEC507BBE) void PLAYSTATS_CARCLUB_POINTS(any p0)l
extern _native64(0x1187CB58D7F3BED7) void PLAYSTATS_CARCLUB_CHALLENGE(any p0, any p1, any p2, any p3)l
extern _native64(0x69C922B677621428) void PLAYSTATS_CARCLUB_PRIZE(int p0, Hash vehicleModel)l
extern _native64(0x70F52471E758EBAE) void PLAYSTATS_AWARD_NAV(any p0, any p1, any p2, any p3)l
extern _native64(0xFEA3F7E83C0610FA) void PLAYSTATS_INST_MISSION_END(any p0)l
extern _native64(0x5A46ACE5C4661132) void PLAYSTATS_HUB_EXIT(any p0)l
extern _native64(0x10A691F5756416D0) void PLAYSTATS_VEH_DEL(int bossId1, int bossId2, int bossType, int vehicleID, int reason)l
extern _native64(0x887DAD63CF5B7908) void PLAYSTATS_INVENTORY(any p0)l
extern _native64(0x8A23D1324F6B2BAC) void _PLAYSTATS_ACID_MISSION_END(any p0)l
extern _native64(0xCEACCF0550FDC5BA) void _PLAYSTATS_ACID_RND(any p0)l
extern _native64(0xEC9553A178E8F1D1) void _PLAYSTATS_IDLE(any p0, any p1, any p2)l
extern _native64(0x48FAC5DC7AC6EA99) void _PLAYSTATS_PLAYER_STYLE(any p0)l
extern _native64(0x7EA06F970F999394) void _PLAYSTATS_RANDOM_EVENT(any p0)l
extern _native64(0xBD642335A732F1A8) void _PLAYSTATS_ATTRITION_STAGE_END(any p0)l
extern _native64(0x961D4157B9B428DB) void _PLAYSTATS_SHOWROOM_NAV(any p0, any p1, Hash entity)l
extern _native64(0x151D6C04C9E2742F) void _PLAYSTATS_SHOWROOM_OVERVIEW(any* data)l
#pragma endregion //}
#pragma region STREAMING //{
extern _native64(0xBD6E84632DD4CB3F) void LOAD_ALL_OBJECTS_NOW()l
extern _native64(0x4448EB75B4904BDB) void LOAD_SCENE(float x, float y, float z)l
extern _native64(0xC4582015556D1C46) bool NETWORK_UPDATE_LOAD_SCENE()l
extern _native64(0x41CA5A33160EA4AB) bool IS_NETWORK_LOADING_SCENE()l
extern _native64(0xE37B76C387BE28ED) void SET_INTERIOR_ACTIVE(int interiorID, bool toggle)l
extern _native64(0x963D27A58DF860AC) void REQUEST_MODEL(Hash model)l
extern _native64(0xA0261AEF7ACFC51E) void REQUEST_MENU_PED_MODEL(Hash model)l
extern _native64(0x98A4EB5D89A0C952) bool HAS_MODEL_LOADED(Hash model)l
extern _native64(0x8A7A40100EDFEC58) void REQUEST_MODELS_IN_ROOM(Interior interior, const char* roomName)l
extern _native64(0xE532F5D78798DAAB) void SET_MODEL_AS_NO_LONGER_NEEDED(Hash model)l
extern _native64(0x35B9E0803292B641) bool IS_MODEL_IN_CDIMAGE(Hash model)l
extern _native64(0xC0296A2EDF545E92) bool IS_MODEL_VALID(Hash model)l
extern _native64(0x75816577FEA6DAD5) bool IS_MODEL_A_PED(Hash model)l
extern _native64(0x19AAC8F07BFEC53E) bool IS_MODEL_A_VEHICLE(Hash model)l
extern _native64(0x07503F7948F491A7) void REQUEST_COLLISION_AT_COORD(float x, float y, float z)l
extern _native64(0x923CB32A3B874FCB) void REQUEST_COLLISION_FOR_MODEL(Hash model)l
extern _native64(0x22CCA434E368F03A) bool HAS_COLLISION_FOR_MODEL_LOADED(Hash model)l
extern _native64(0xC9156DC11411A9EA) void REQUEST_ADDITIONAL_COLLISION_AT_COORD(float x, float y, float z)l
extern _native64(0x2DA49C3B79856961) bool DOES_ANIM_DICT_EXIST(const char* animDict)l
extern _native64(0xD3BD40951412FEF6) void REQUEST_ANIM_DICT(const char* animDict)l
extern _native64(0xD031A9162D01088C) bool HAS_ANIM_DICT_LOADED(const char* animDict)l
extern _native64(0xF66A602F829E2A06) void REMOVE_ANIM_DICT(const char* animDict)l
extern _native64(0x6EA47DAE7FAD0EED) void REQUEST_ANIM_SET(const char* animSet)l
extern _native64(0xC4EA073D86FB29B0) bool HAS_ANIM_SET_LOADED(const char* animSet)l
extern _native64(0x16350528F93024B3) void REMOVE_ANIM_SET(const char* animSet)l
extern _native64(0xD2A71E1A77418A49) void REQUEST_CLIP_SET(const char* clipSet)l
extern _native64(0x318234F4F3738AF3) bool HAS_CLIP_SET_LOADED(const char* clipSet)l
extern _native64(0x01F73A131C18CD94) void REMOVE_CLIP_SET(const char* clipSet)l
extern _native64(0x41B4893843BBDB74) void REQUEST_IPL(const char* iplName)l
extern _native64(0xEE6C5AD3ECE0A82D) void REMOVE_IPL(const char* iplName)l
extern _native64(0x88A741E44A2B3495) bool IS_IPL_ACTIVE(const char* iplName)l
extern _native64(0x6E0C692677008888) void SET_STREAMING(bool toggle)l
extern _native64(0x7E3F55ED251B76D3) void LOAD_GLOBAL_WATER_FILE(int waterType)l
extern _native64(0xF741BD853611592D) int GET_GLOBAL_WATER_FILE()l
extern _native64(0x717CD6E6FAEBBEDC) void SET_GAME_PAUSES_FOR_STREAMING(bool toggle)l
extern _native64(0x77B5F9A36BF96710) void SET_REDUCE_PED_MODEL_BUDGET(bool toggle)l
extern _native64(0x80C527893080CCF3) void SET_REDUCE_VEHICLE_MODEL_BUDGET(bool toggle)l
extern _native64(0x42CBE54462D92634) void SET_DITCH_POLICE_MODELS(bool toggle)l
extern _native64(0x4060057271CEBC89) int GET_NUMBER_OF_STREAMING_REQUESTS()l
extern _native64(0x944955FB2A3935C8) void REQUEST_PTFX_ASSET()l
extern _native64(0xCA7D9B86ECA7481B) bool HAS_PTFX_ASSET_LOADED()l
extern _native64(0x88C6814073DD4A73) void REMOVE_PTFX_ASSET()l
extern _native64(0xB80D8756B4668AB6) void REQUEST_NAMED_PTFX_ASSET(const char* fxName)l
extern _native64(0x8702416E512EC454) bool HAS_NAMED_PTFX_ASSET_LOADED(const char* fxName)l
extern _native64(0x5F61EBBE1A00F96D) void REMOVE_NAMED_PTFX_ASSET(const char* fxName)l
extern _native64(0xCB9E1EB3BE2AF4E9) void SET_VEHICLE_POPULATION_BUDGET(int p0)l
extern _native64(0x8C95333CFC3340F3) void SET_PED_POPULATION_BUDGET(int p0)l
extern _native64(0x31B73D1EA9F01DA2) void CLEAR_FOCUS()l
extern _native64(0xBB7454BAFF08FE25) void SET_FOCUS_POS_AND_VEL(float x, float y, float z, float offsetX, float offsetY, float offsetZ)l
extern _native64(0x198F77705FA0931D) void SET_FOCUS_ENTITY(Entity entity)l
extern _native64(0x2DDFF3FB9075D747) bool IS_ENTITY_FOCUS(Entity entity)l
extern _native64(0x0811381EF5062FEC) void SET_RESTORE_FOCUS_ENTITY(Entity p0)l
extern _native64(0xAF12610C644A35C9) void SET_MAPDATACULLBOX_ENABLED(const char* name, bool toggle)l
extern _native64(0x4E52E752C76E7E7A) void SET_ALL_MAPDATA_CULLED(any p0)l
extern _native64(0x219C7B8D53E429FD) int STREAMVOL_CREATE_SPHERE(float x, float y, float z, float rad, any p4, any p5)l
extern _native64(0x1F3F018BC3AFA77C) int STREAMVOL_CREATE_FRUSTUM(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7, any p8)l
extern _native64(0x0AD9710CEE2F590F) int STREAMVOL_CREATE_LINE(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native64(0x1EE7D8DF4425F053) void STREAMVOL_DELETE(any unused)l
extern _native64(0x7D41E9D2D17C5B2D) bool STREAMVOL_HAS_LOADED(any unused)l
extern _native64(0x07C313F94746702C) bool STREAMVOL_IS_VALID(any unused)l
extern _native64(0xBC9823AB80A3DCAC) bool IS_STREAMVOL_ACTIVE()l
extern _native64(0x212A8D0D2BABFAC2) bool NEW_LOAD_SCENE_START(float posX, float posY, float posZ, float offsetX, float offsetY, float offsetZ, float radius, int p7)l
extern _native64(0xACCFB4ACF53551B0) bool NEW_LOAD_SCENE_START_SPHERE(float x, float y, float z, float radius, any p4)l
extern _native64(0xC197616D221FF4A4) void NEW_LOAD_SCENE_STOP()l
extern _native64(0xA41A05B6CB741B85) bool IS_NEW_LOAD_SCENE_ACTIVE()l
extern _native64(0x01B8247A7A8B9AD1) bool IS_NEW_LOAD_SCENE_LOADED()l
extern _native64(0x71E7B2E657449AAD) bool IS_SAFE_TO_START_PLAYER_SWITCH()l
extern _native64(0xFAA23F2CBA159D67) void START_PLAYER_SWITCH(Ped from, Ped to, int flags, int switchType)l
extern _native64(0x95C0A5BBDC189AA1) void STOP_PLAYER_SWITCH()l
extern _native64(0xD9D2CFFF49FAB35F) bool IS_PLAYER_SWITCH_IN_PROGRESS()l
extern _native64(0xB3C94A90D9FC9E62) int GET_PLAYER_SWITCH_TYPE()l
extern _native64(0xB5D7B26B45720E05) int GET_IDEAL_PLAYER_SWITCH_TYPE(float x1, float y1, float z1, float x2, float y2, float z2)l
extern _native64(0x470555300D10B2A5) int GET_PLAYER_SWITCH_STATE()l
extern _native64(0x20F898A5D9782800) int GET_PLAYER_SHORT_SWITCH_STATE()l
extern _native64(0x5F2013F8BC24EE69) void SET_PLAYER_SHORT_SWITCH_STYLE(int p0)l
extern _native64(0x78C0D93253149435) int GET_PLAYER_SWITCH_JUMP_CUT_INDEX()l
extern _native64(0xC208B673CE446B61) void SET_PLAYER_SWITCH_OUTRO(float cameraCoordX, float cameraCoordY, float cameraCoordZ, float camRotationX, float camRotationY, float camRotationZ, float camFov, float camFarClip, int rotationOrder)l
extern _native64(0x0FDE9DBFC0A6BC65) void SET_PLAYER_SWITCH_ESTABLISHING_SHOT(const char* name)l
extern _native64(0x43D1680C6D19A8E9) void ALLOW_PLAYER_SWITCH_PAN()l
extern _native64(0x74DE2E8739086740) void ALLOW_PLAYER_SWITCH_OUTRO()l
extern _native64(0x8E2A065ABDAE6994) void ALLOW_PLAYER_SWITCH_ASCENT()l
extern _native64(0xAD5FDF34B81BFE79) void ALLOW_PLAYER_SWITCH_DESCENT()l
extern _native64(0xDFA80CB25D0A19B3) bool IS_SWITCH_READY_FOR_DESCENT()l
extern _native64(0xD4793DFF3AF2ABCD) void ENABLE_SWITCH_PAUSE_BEFORE_DESCENT()l
extern _native64(0xBD605B8E0E18B3BB) void DISABLE_SWITCH_OUTRO_FX()l
extern _native64(0xAAB3200ED59016BC) void SWITCH_TO_MULTI_FIRSTPART(Ped ped, int flags, int switchType)l
extern _native64(0xD8295AF639FD9CB8) void SWITCH_TO_MULTI_SECONDPART(Ped ped)l
extern _native64(0x933BBEEB8C61B5F4) bool IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED()l
extern _native64(0x08C2D6C52A3104BB) int GET_PLAYER_SWITCH_INTERP_OUT_DURATION()l
extern _native64(0x5B48A06DD0E792A5) int GET_PLAYER_SWITCH_INTERP_OUT_CURRENT_TIME()l
extern _native64(0x5B74EA8CFD5E3E7E) bool IS_SWITCH_SKIPPING_DESCENT()l
extern _native64(0x1E9057A74FD73E23) void SET_SCENE_STREAMING_TRACKS_CAM_POS_THIS_FRAME()l
extern _native64(0x0C15B0E443B2349D) float GET_LODSCALE()l
extern _native64(0xA76359FC80B2438E) void OVERRIDE_LODSCALE_THIS_FRAME(float scaling)l
extern _native64(0xBED8CA5FF5E04113) void REMAP_LODSCALE_RANGE_THIS_FRAME(float p0, float p1, float p2, float p3)l
extern _native64(0x472397322E92A856) void SUPPRESS_HD_MAP_STREAMING_THIS_FRAME()l
extern _native64(0x40AEFD1A244741F2) void SET_RENDER_HD_ONLY(bool toggle)l
extern _native64(0x03F1A106BDA7DD3E) void FORCE_ALLOW_TIME_BASED_FADING_THIS_FRAME()l
extern _native64(0x95A7DABDDBB78AE7) void IPL_GROUP_SWAP_START(const char* iplName1, const char* iplName2)l
extern _native64(0x63EB2B972A218CAC) void IPL_GROUP_SWAP_CANCEL()l
extern _native64(0xFB199266061F820A) bool IPL_GROUP_SWAP_IS_READY()l
extern _native64(0xF4A0DADB70F57FA6) void IPL_GROUP_SWAP_FINISH()l
extern _native64(0x5068F488DDB54DD8) bool IPL_GROUP_SWAP_IS_ACTIVE()l
extern _native64(0x3D245789CE12982C) void PREFETCH_SRL(const char* srl)l
extern _native64(0xD0263801A4C5B0BB) bool IS_SRL_LOADED()l
extern _native64(0x9BADDC94EF83B823) void BEGIN_SRL()l
extern _native64(0x0A41540E63C9EE17) void END_SRL()l
extern _native64(0xA74A541C6884E7B8) void SET_SRL_TIME(float p0)l
extern _native64(0xEF39EE20C537E98C) void SET_SRL_POST_CUTSCENE_CAMERA(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xBEB2D9A1D9A8F55A) void SET_SRL_READAHEAD_TIMES(any p0, any p1, any p2, any p3)l
extern _native64(0x20C6C7E4EB082A7F) void SET_SRL_LONG_JUMP_MODE(bool p0)l
extern _native64(0xF8155A7F03DDFC8E) void SET_SRL_FORCE_PRESTREAM(any p0)l
extern _native64(0xB85F26619073E775) void SET_HD_AREA(float x, float y, float z, float radius)l
extern _native64(0xCE58B1CFB9290813) void CLEAR_HD_AREA()l
extern _native64(0xB5A4DB34FE89B88A) void INIT_CREATOR_BUDGET()l
extern _native64(0xCCE26000E9A6FAD7) void SHUTDOWN_CREATOR_BUDGET()l
extern _native64(0x0BC3144DEB678666) bool ADD_MODEL_TO_CREATOR_BUDGET(Hash modelHash)l
extern _native64(0xF086AD9354FAC3A3) void REMOVE_MODEL_FROM_CREATOR_BUDGET(Hash modelHash)l
extern _native64(0x3D3D8B3BE5A83D35) float GET_USED_CREATOR_BUDGET()l
extern _native64(0x9A9D1BA639675CF1) void SET_ISLAND_ENABLED(const char* name, bool toggle)l
#pragma endregion //}
#pragma region TASK //{
extern _native64(0xE73A266DB0CA9042) void TASK_PAUSE(Ped ped, int ms)l
extern _native64(0x919BE13EED931959) void TASK_STAND_STILL(Ped ped, int time)l
extern _native64(0x0AE4086104E067B1) void TASK_JUMP(Ped ped, bool usePlayerLaunchForce, bool doSuperJump, bool useFullSuperJumpForce)l
extern _native64(0x3EB1FE9E8E908E15) void TASK_COWER(Ped ped, int duration)l
extern _native64(0xF2EAB31979A7F910) void TASK_HANDS_UP(Ped ped, int duration, Ped facingPed, int timeToFacePed, int flags)l
extern _native64(0xA98FCAFD7893C834) void UPDATE_TASK_HANDS_UP_DURATION(Ped ped, int duration)l
extern _native64(0x965791A9A488A062) void TASK_OPEN_VEHICLE_DOOR(Ped ped, Vehicle vehicle, int timeOut, int seat, float speed)l
extern _native64(0xC20E50AA46D09CA8) void TASK_ENTER_VEHICLE(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int flag, const char* overrideEntryClipsetName)l
extern _native64(0xD3DBCE61A490BE02) void TASK_LEAVE_VEHICLE(Ped ped, Vehicle vehicle, int flags)l
extern _native64(0x9C00E77AF14B2DFF) void TASK_GET_OFF_BOAT(Ped ped, Vehicle boat)l
extern _native64(0x601736CFE536B0A0) void TASK_SKY_DIVE(Ped ped, bool instant)l
extern _native64(0xD2F1C53C97EE81AB) void TASK_PARACHUTE(Ped ped, bool giveParachuteItem, bool instant)l
extern _native64(0xB33E291AFA6BD03A) void TASK_PARACHUTE_TO_TARGET(Ped ped, float x, float y, float z)l
extern _native64(0xC313379AF0FCEDA7) void SET_PARACHUTE_TASK_TARGET(Ped ped, float x, float y, float z)l
extern _native64(0x0729BAC1B8C64317) void SET_PARACHUTE_TASK_THRUST(Ped ped, float thrust)l
extern _native64(0x09693B0312F91649) void TASK_RAPPEL_FROM_HELI(Ped ped, float minHeightAboveGround)l
extern _native64(0xE2A2AA2F659D77A7) void TASK_VEHICLE_DRIVE_TO_COORD(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, any p6, Hash vehicleModel, int drivingMode, float stopRange, float straightLineDistance)l
extern _native64(0x158BB33F920D360C) void TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int driveMode, float stopRange)l
extern _native64(0x480142959D337D00) void TASK_VEHICLE_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, int drivingStyle)l
extern _native64(0x304AE42E357B8C7E) void TASK_FOLLOW_TO_OFFSET_OF_ENTITY(Ped ped, Entity entity, float offsetX, float offsetY, float offsetZ, float movementSpeed, int timeout, float stoppingRange, bool persistFollowing)l
extern _native64(0xD76B57B44F1E6F8B) void TASK_GO_STRAIGHT_TO_COORD(Ped ped, float x, float y, float z, float speed, int timeout, float targetHeading, float distanceToSlide)l
extern _native64(0x61E360B7E040D12E) void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(Ped ped, Entity entity, float x, float y, float z, float moveBlendRatio, int time)l
extern _native64(0x93B93A37987F1F3D) void TASK_ACHIEVE_HEADING(Ped ped, float heading, int timeout)l
extern _native64(0x841142A1376E9006) void TASK_FLUSH_ROUTE()l
extern _native64(0x1E7889778264843A) void TASK_EXTEND_ROUTE(float x, float y, float z)l
extern _native64(0x595583281858626E) void TASK_FOLLOW_POINT_ROUTE(Ped ped, float speed, int mode)l
extern _native64(0x6A071245EB0D1882) void TASK_GO_TO_ENTITY(Entity entity, Entity target, int duration, float distance, float moveBlendRatio, float slowDownDistance, int flags)l
extern _native64(0x94587F17E9C365D5) void TASK_SMART_FLEE_COORD(Ped ped, float x, float y, float z, float distance, int time, bool preferPavements, bool quitIfOutOfRange)l
extern _native64(0x22B0D0E37CCB840D) void TASK_SMART_FLEE_PED(Ped ped, Ped fleeTarget, float safeDistance, int fleeTime, bool preferPavements, bool updateToNearestHatedPed)l
extern _native64(0x72C896464915D1B1) void TASK_REACT_AND_FLEE_PED(Ped ped, Ped fleeTarget)l
extern _native64(0x452419CBD838065B) void TASK_SHOCKING_EVENT_REACT(Ped ped, int eventHandle)l
extern _native64(0xE054346CA3A0F315) void TASK_WANDER_IN_AREA(Ped ped, float x, float y, float z, float radius, float minimalLength, float timeBetweenWalks)l
extern _native64(0xBB9CE077274F6A1B) void TASK_WANDER_STANDARD(Ped ped, float heading, int flags)l
extern _native64(0x6919A2F136426098) void TASK_WANDER_SPECIFIC(Ped ped, const char* conditionalAnimGroupStr, const char* conditionalAnimStr, float heading)l
extern _native64(0x0F3E34E968EA374E) void TASK_VEHICLE_PARK(Ped ped, Vehicle vehicle, float x, float y, float z, float heading, int mode, float radius, bool keepEngineOn)l
extern _native64(0xAA5DC05579D60BD9) void TASK_STEALTH_KILL(Ped killer, Ped target, Hash stealthKillActionResultHash, float desiredMoveBlendRatio, int stealthFlags)l
extern _native64(0x965FEC691D55E9BF) void TASK_PLANT_BOMB(Ped ped, float x, float y, float z, float heading)l
extern _native64(0x15D3A79D4E44B913) void TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float targetHeading)l
extern _native64(0x17F58B88D085DBAC) void TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float slideToCoordHeading, float maxSlopeNavigable, float clampMaxSearchDistance, float targetHeading)l
extern _native64(0x8E06A6FE76C9EFF4) void SET_PED_PATH_CAN_USE_CLIMBOVERS(Ped ped, bool Toggle)l
extern _native64(0x77A5B103C87F476E) void SET_PED_PATH_CAN_USE_LADDERS(Ped ped, bool Toggle)l
extern _native64(0xE361C5C71C431A4F) void SET_PED_PATH_CAN_DROP_FROM_HEIGHT(Ped ped, bool Toggle)l
extern _native64(0x88E32DB8C1A4AA4B) void SET_PED_PATH_CLIMB_COST_MODIFIER(Ped ped, float modifier)l
extern _native64(0xF35425A4204367EC) void SET_PED_PATH_MAY_ENTER_WATER(Ped ped, bool mayEnterWater)l
extern _native64(0x38FE1EC73743793C) void SET_PED_PATH_PREFER_TO_AVOID_WATER(Ped ped, bool avoidWater)l
extern _native64(0x4455517B28441E60) void SET_PED_PATH_AVOID_FIRE(Ped ped, bool avoidFire)l
extern _native64(0x6C6B148586F934F7) void SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(float height)l
extern _native64(0xC6F5C0BCDC74D62D) int GET_NAVMESH_ROUTE_DISTANCE_REMAINING(Ped ped, float* distanceRemaining, bool* isPathReady)l
extern _native64(0x632E831F382A0FA8) int GET_NAVMESH_ROUTE_RESULT(Ped ped)l
extern _native64(0x3E38E28A1D80DDF6) bool IS_CONTROLLED_VEHICLE_UNABLE_TO_GET_TO_ROAD(Ped ped)l
extern _native64(0x5BC448CB78FA3E88) void TASK_GO_TO_COORD_ANY_MEANS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets)l
extern _native64(0x1DD45F9ECFDB1BC9) void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float warpTimerMS)l
extern _native64(0xB8ECD61F531A7B02) void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float cruiseSpeed, float targetArriveDist)l
extern _native64(0xEA47FE3719165B94) void TASK_PLAY_ANIM(Ped ped, const char* animDictionary, const char* animationName, float blendInSpeed, float blendOutSpeed, int duration, int flag, float playbackRate, bool lockX, bool lockY, bool lockZ)l
extern _native64(0x83CDB10EA29B370B) void TASK_PLAY_ANIM_ADVANCED(Ped ped, const char* animDict, const char* animName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float animEnterSpeed, float animExitSpeed, int duration, any flag, float animTime, int rotOrder, int ikFlags)l
extern _native64(0x97FF36A1D40EA00A) void STOP_ANIM_TASK(Entity entity, const char* animDictionary, const char* animationName, float blendDelta)l
extern _native64(0x126EF75F1E17ABE5) void TASK_SCRIPTED_ANIMATION(Ped ped, int* priorityLowData, int* priorityMidData, int* priorityHighData, float blendInDelta, float blendOutDelta)l
extern _native64(0x77A1EEC547E7FCF1) void PLAY_ENTITY_SCRIPTED_ANIM(Entity entity, int* priorityLowData, int* priorityMidData, int* priorityHighData, float blendInDelta, float blendOutDelta)l
extern _native64(0xEE08C992D238C5D1) void STOP_ANIM_PLAYBACK(Entity entity, int priority, bool secondary)l
extern _native64(0x207F1A47C0342F48) void SET_ANIM_WEIGHT(Entity entity, float weight, int priority, int index, bool secondary)l
extern _native64(0xDDF3CB5A0A4C0B49) void SET_ANIM_PHASE(Entity entity, float phase, int priority, bool secondary)l
extern _native64(0x032D49C5E359C847) void SET_ANIM_RATE(Entity entity, float rate, int priority, bool secondary)l
extern _native64(0x70033C3CC29A1FF4) void SET_ANIM_LOOPED(Entity entity, bool looped, int priority, bool secondary)l
extern _native64(0x8FBB6758B3B3E9EC) void TASK_PLAY_PHONE_GESTURE_ANIMATION(Ped ped, const char* animDict, const char* animation, const char* boneMaskType, float blendInDuration, float blendOutDuration, bool isLooping, bool holdLastFrame)l
extern _native64(0x3FA00D4F4641BFAE) void TASK_STOP_PHONE_GESTURE_ANIMATION(Ped ped, float blendOutOverride)l
extern _native64(0xB8EBB1E9D3588C10) bool IS_PLAYING_PHONE_GESTURE_ANIM(Ped ped)l
extern _native64(0x47619ABE8B268C60) float GET_PHONE_GESTURE_ANIM_CURRENT_TIME(Ped ped)l
extern _native64(0x1EE0F68A7C25DEC6) float GET_PHONE_GESTURE_ANIM_TOTAL_TIME(Ped ped)l
extern _native64(0x69F5C3BD0F3EBD89) void TASK_VEHICLE_PLAY_ANIM(Vehicle vehicle, const char* animationSet, const char* animationName)l
extern _native64(0x6FA46612594F7973) void TASK_LOOK_AT_COORD(Entity entity, float x, float y, float z, int duration, int flags, int priority)l
extern _native64(0x69F4BE8C8CC4796C) void TASK_LOOK_AT_ENTITY(Ped ped, Entity lookAt, int duration, int flags, int priority)l
extern _native64(0x0F804F1DB19B9689) void TASK_CLEAR_LOOK_AT(Ped ped)l
extern _native64(0xE8854A4326B9E12B) void OPEN_SEQUENCE_TASK(int* taskSequenceId)l
extern _native64(0x39E72BC99E6360CB) void CLOSE_SEQUENCE_TASK(int taskSequenceId)l
extern _native64(0x5ABA3986D90D8A3B) void TASK_PERFORM_SEQUENCE(Ped ped, int taskSequenceId)l
extern _native64(0x8C33220C8D78CA0D) void TASK_PERFORM_SEQUENCE_LOCALLY(Ped ped, int taskSequenceId)l
extern _native64(0x3841422E9C488D8C) void CLEAR_SEQUENCE_TASK(int* taskSequenceId)l
extern _native64(0x58C70CF3A41E4AE7) void SET_SEQUENCE_TO_REPEAT(int taskSequenceId, bool repeat)l
extern _native64(0x00A9010CFE1E3533) int GET_SEQUENCE_PROGRESS(Ped ped)l
extern _native64(0xB0760331C7AA4155) bool GET_IS_TASK_ACTIVE(Ped ped, int taskIndex)l
extern _native64(0x77F1BEB8863288D5) int GET_SCRIPT_TASK_STATUS(Ped ped, Hash taskHash)l
extern _native64(0x534AEBA6E5ED4CAB) int GET_ACTIVE_VEHICLE_MISSION_TYPE(Vehicle vehicle)l
extern _native64(0x504D54DF3F6F2247) void TASK_LEAVE_ANY_VEHICLE(Ped ped, int delayTime, int flags)l
extern _native64(0x7A192BE16D373D00) void TASK_AIM_GUN_SCRIPTED(Ped ped, Hash scriptTask, bool disableBlockingClip, bool instantBlendToAim)l
extern _native64(0x8605AF0DE8B3A5AC) void TASK_AIM_GUN_SCRIPTED_WITH_TARGET(Ped ped, Ped target, float x, float y, float z, int gunTaskType, bool disableBlockingClip, bool forceAim)l
extern _native64(0x9724FB59A3E72AD0) void UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(Ped ped, Ped target, float x, float y, float z, bool disableBlockingClip)l
extern _native64(0x3A8CADC7D37AACC5) const char* GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(int gunTaskType)l
extern _native64(0x9B53BB6E8943AF53) void TASK_AIM_GUN_AT_ENTITY(Ped ped, Entity entity, int duration, bool instantBlendToAim)l
extern _native64(0x5AD23D40115353AC) void TASK_TURN_PED_TO_FACE_ENTITY(Ped ped, Entity entity, int duration)l
extern _native64(0x6671F3EEC681BDA1) void TASK_AIM_GUN_AT_COORD(Ped ped, float x, float y, float z, int time, bool instantBlendToAim, bool playAnimIntro)l
extern _native64(0x46A6CC01E0826106) void TASK_SHOOT_AT_COORD(Ped ped, float x, float y, float z, int duration, Hash firingPattern)l
extern _native64(0x7AA80209BDA643EB) void TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(Ped ped, Vehicle vehicle, bool useAlternateShuffle)l
extern _native64(0xE1EF3C1216AFF2CD) void CLEAR_PED_TASKS(Ped ped)l
extern _native64(0x176CECF6F920D707) void CLEAR_PED_SECONDARY_TASK(Ped ped)l
extern _native64(0x7F93691AB4B92272) void TASK_EVERYONE_LEAVE_VEHICLE(Vehicle vehicle)l
extern _native64(0xE39B4FF4FDEBDE27) void TASK_GOTO_ENTITY_OFFSET(Ped ped, Entity entity, int time, float seekRadius, float seekAngleDeg, float moveBlendRatio, int gotoEntityOffsetFlags)l
extern _native64(0x338E7EF52B6095A9) void TASK_GOTO_ENTITY_OFFSET_XY(Ped ped, Entity entity, int duration, float targetRadius, float offsetX, float offsetY, float moveBlendRatio, int gotoEntityOffsetFlags)l
extern _native64(0x1DDA930A0AC38571) void TASK_TURN_PED_TO_FACE_COORD(Ped ped, float x, float y, float z, int duration)l
extern _native64(0xC429DCEEB339E129) void TASK_VEHICLE_TEMP_ACTION(Ped driver, Vehicle vehicle, int action, int time)l
extern _native64(0x659427E0EF36BCDE) void TASK_VEHICLE_MISSION(Ped driver, Vehicle vehicle, Vehicle vehicleTarget, int missionType, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, bool DriveAgainstTraffic)l
extern _native64(0x9454528DF15D657A) void TASK_VEHICLE_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped pedTarget, int missionType, float maxSpeed, int drivingStyle, float minDistance, float straightLineDistance, bool DriveAgainstTraffic)l
extern _native64(0xF0AF20AA7731F8C3) void TASK_VEHICLE_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, float x, float y, float z, int mission, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, bool DriveAgainstTraffic)l
extern _native64(0x0FA6E4B75F302400) void TASK_VEHICLE_ESCORT(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int minHeightAboveTerrain, float noRoadsDistance)l
extern _native64(0xFC545A9F0626E3B6) void TASK_VEHICLE_FOLLOW(Ped driver, Vehicle vehicle, Entity targetEntity, float speed, int drivingStyle, int minDistance)l
extern _native64(0x3C08A8E30363B353) void TASK_VEHICLE_CHASE(Ped driver, Entity targetEnt)l
extern _native64(0x1E09C32048FEFD1C) void TASK_VEHICLE_HELI_PROTECT(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int drivingFlags, float radius, int altitude, int heliFlags)l
extern _native64(0xCC665AAC360D31E7) void SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(Ped ped, int flag, bool set)l
extern _native64(0x639B642FACBE4EDD) void SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(Ped ped, float distance)l
extern _native64(0xAC83B1DB38D0ADA0) void TASK_HELI_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z)l
extern _native64(0x2D2386F273FF7A25) void TASK_PLANE_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z)l
extern _native64(0xBF19721FA34D32C0) void TASK_PLANE_LAND(Ped pilot, Vehicle plane, float runwayStartX, float runwayStartY, float runwayStartZ, float runwayEndX, float runwayEndY, float runwayEndZ)l
extern _native64(0x6100B3CEFD43452E) void CLEAR_DEFAULT_PRIMARY_TASK(Ped ped)l
extern _native64(0xDBBC7A2432524127) void CLEAR_PRIMARY_VEHICLE_TASK(Vehicle vehicle)l
extern _native64(0x53DDC75BC3AC0A90) void CLEAR_VEHICLE_CRASH_TASK(Vehicle vehicle)l
extern _native64(0xF7F9DCCA89E7505B) void TASK_PLANE_GOTO_PRECISE_VTOL(Ped ped, Vehicle vehicle, float x, float y, float z, int flightHeight, int minHeightAboveTerrain, bool useDesiredOrientation, float desiredOrientation, bool autopilot)l
extern _native64(0xC22B40579A498CA4) void TASK_SUBMARINE_GOTO_AND_STOP(Ped ped, Vehicle submarine, float x, float y, float z, bool autopilot)l
extern _native64(0xDAD029E187A2BEB4) void TASK_HELI_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float maxSpeed, float radius, float targetHeading, int maxHeight, int minHeight, float slowDownDistance, int behaviorFlags)l
extern _native64(0xB385523325077210) void TASK_HELI_ESCORT_HELI(Ped pilot, Vehicle heli1, Vehicle heli2, float offsetX, float offsetY, float offsetZ)l
extern _native64(0x23703CD154E83B88) void TASK_PLANE_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float angularDrag, float targetReached, float targetHeading, float maxZ, float minZ, bool precise)l
extern _native64(0x92C360B5F15D2302) void TASK_PLANE_TAXI(Ped pilot, Vehicle aircraft, float x, float y, float z, float cruiseSpeed, float targetReached)l
extern _native64(0x15C86013127CE63F) void TASK_BOAT_MISSION(Ped pedDriver, Vehicle vehicle, Vehicle targetVehicle, Ped targetPed, float x, float y, float z, int mission, float maxSpeed, int drivingStyle, float targetReached, any boatFlags)l
extern _native64(0x2F8AF0E82773A171) void TASK_DRIVE_BY(Ped driverPed, Ped targetPed, Vehicle targetVehicle, float targetX, float targetY, float targetZ, float distanceToShoot, int pedAccuracy, bool pushUnderneathDrivingTaskIfDriving, Hash firingPattern)l
extern _native64(0xE5B302114D8162EE) void SET_DRIVEBY_TASK_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z)l
extern _native64(0xC35B5CDB2824CF69) void CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native64(0x8785E6E40C7A8818) bool IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native64(0xDCFE42068FE0135A) bool CONTROL_MOUNTED_WEAPON(Ped ped)l
extern _native64(0xCCD892192C6D2BB9) void SET_MOUNTED_WEAPON_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z, int taskMode, bool ignoreTargetVehDeadCheck)l
extern _native64(0xA320EF046186FA3B) bool IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native64(0xBD2A8EC3AF4DE7DB) void TASK_USE_MOBILE_PHONE(Ped ped, bool usePhone, int desiredPhoneMode)l
extern _native64(0x5EE02954A14C69DB) void TASK_USE_MOBILE_PHONE_TIMED(Ped ped, int duration)l
extern _native64(0x8C338E0263E4FD19) void TASK_CHAT_TO_PED(Ped ped, Ped target, int flags, float goToLocationX, float goToLocationY, float goToLocationZ, float headingDegs, float idleTime)l
extern _native64(0x9A7D091411C5F684) void TASK_WARP_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seat)l
extern _native64(0x08DA95E8298AE772) void TASK_SHOOT_AT_ENTITY(Entity entity, Entity target, int duration, Hash firingPattern)l
extern _native64(0x89D9FCC2435112F1) void TASK_CLIMB(Ped ped, bool usePlayerLaunchForce)l
extern _native64(0xB6C987F9285A3814) void TASK_CLIMB_LADDER(Ped ped, bool fast)l
extern _native64(0xEAF66ACDDC794793) void TASK_RAPPEL_DOWN_WALL_USING_CLIPSET_OVERRIDE(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, float minZ, int ropeHandle, const char* clipSet, any p10)l
extern _native64(0x9D252648778160DF) int GET_TASK_RAPPEL_DOWN_WALL_STATE(Ped ped)l
extern _native64(0xAAA34F8A7CB32098) void CLEAR_PED_TASKS_IMMEDIATELY(Ped ped)l
extern _native64(0x89221B16730234F0) void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(Ped ped, int taskIndex, int progress1, int progress2)l
extern _native64(0xF1B9F16E89E2C93A) void SET_NEXT_DESIRED_MOVE_STATE(float nextMoveState)l
extern _native64(0x1E982AC8716912C5) void SET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped, float newMoveBlendRatio)l
extern _native64(0x8517D4A6CA8513ED) float GET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped)l
extern _native64(0xA9DA48FAB8A76C12) void TASK_GOTO_ENTITY_AIMING(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist)l
extern _native64(0xEB8517DDA73720DA) void TASK_SET_DECISION_MAKER(Ped ped, Hash decisionMakerId)l
extern _native64(0x933C06518B52A9A4) void TASK_SET_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius)l
extern _native64(0x95A6C46A31D1917D) void TASK_CLEAR_DEFENSIVE_AREA(Ped ped)l
extern _native64(0xD04FE6765D990A06) void TASK_PED_SLIDE_TO_COORD(Ped ped, float x, float y, float z, float heading, float speed)l
extern _native64(0x5A4A6A6D3DC64F52) void TASK_PED_SLIDE_TO_COORD_HDG_RATE(Ped ped, float x, float y, float z, float heading, float speed, float headingChangeRate)l
extern _native64(0xD5C12A75C7B9497F) ScrHandle ADD_COVER_POINT(float x, float y, float z, float direction, int usage, int height, int arc, bool isPriority)l
extern _native64(0xAE287C923D891715) void REMOVE_COVER_POINT(ScrHandle coverpoint)l
extern _native64(0xA98B8E3C088E5A31) bool DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(float x, float y, float z)l
extern _native64(0x594A1028FC2A3E85) vector3 GET_SCRIPTED_COVER_POINT_COORDS(ScrHandle coverpoint)l
extern _native64(0x28B7B9BFDAF274AA) void ADD_SCRIPTED_COVER_AREA(float x, float y, float z, float radius)l
extern _native64(0xF166E48407BAC484) void TASK_COMBAT_PED(Ped ped, Ped targetPed, int combatFlags, int threatResponseFlags)l
extern _native64(0x944F30DCB7096BDE) void TASK_COMBAT_PED_TIMED(Ped ped, Ped target, int time, int flags)l
extern _native64(0x75AC2B60386D89F2) void TASK_SEEK_COVER_FROM_POS(Ped ped, float x, float y, float z, int duration, bool allowPeekingAndFiring)l
extern _native64(0x84D32B3BEC531324) void TASK_SEEK_COVER_FROM_PED(Ped ped, Ped target, int duration, bool allowPeekingAndFiring)l
extern _native64(0xD43D95C7A869447F) void TASK_SEEK_COVER_TO_COVER_POINT(Ped ped, ScrHandle coverpoint, float x, float y, float z, int time, bool allowPeekingAndFiring)l
extern _native64(0x39246A6958EF072C) void TASK_SEEK_COVER_TO_COORDS(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, int timeout, bool shortRoute)l
extern _native64(0x4172393E6BE1FECE) void TASK_PUT_PED_DIRECTLY_INTO_COVER(Ped ped, float x, float y, float z, int time, bool allowPeekingAndFiring, float blendInDuration, bool forceInitialFacingDirection, bool forceFaceLeft, int identifier, bool doEntry)l
extern _native64(0x6E01E9E8D89F8276) void TASK_WARP_PED_DIRECTLY_INTO_COVER(Ped ped, int time, bool allowPeekingAndFiring, bool forceInitialFacingDirection, bool forceFaceLeft, int identifier)l
extern _native64(0x79B258E397854D29) void TASK_EXIT_COVER(Ped ped, int exitType, float x, float y, float z)l
extern _native64(0x1C6CD14A876FFE39) void TASK_PUT_PED_DIRECTLY_INTO_MELEE(Ped ped, Ped meleeTarget, float blendInDuration, float timeInMelee, float strafePhaseSync, int aiCombatFlags)l
extern _native64(0xAC96609B9995EDF8) void TASK_TOGGLE_DUCK(Ped ped, int toggleType)l
extern _native64(0x4A58A47A72E3FCB4) void TASK_GUARD_CURRENT_POSITION(Ped ped, float maxPatrolProximity, float defensiveAreaRadius, bool setDefensiveArea)l
extern _native64(0xD2A207EEBDF9889B) void TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float heading, float maxPatrolProximity, int timer)l
extern _native64(0xC946FE14BE0EB5E2) void TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped ped, float defendPositionX, float defendPositionY, float defendPositionZ, float heading, float maxPatrolProximity, int time, float x, float y, float z, float defensiveAreaRadius)l
extern _native64(0xAE032F8BBA959E90) void TASK_STAND_GUARD(Ped ped, float x, float y, float z, float heading, const char* scenarioName)l
extern _native64(0x5C9B84BD7D31D908) void SET_DRIVE_TASK_CRUISE_SPEED(Ped driver, float cruiseSpeed)l
extern _native64(0x404A5AA9B9F0B746) void SET_DRIVE_TASK_MAX_CRUISE_SPEED(Ped ped, float speed)l
extern _native64(0xDACE1BE37D88AF67) void SET_DRIVE_TASK_DRIVING_STYLE(Ped ped, int drivingStyle)l
extern _native64(0x45C597097DD7CB81) void ADD_COVER_BLOCKING_AREA(float startX, float startY, float startZ, float endX, float endY, float endZ, bool blockObjects, bool blockVehicles, bool blockMap, bool blockPlayer)l
extern _native64(0xDB6708C0B46F56D8) void REMOVE_ALL_COVER_BLOCKING_AREAS()l
extern _native64(0xFA83CA6776038F64) void REMOVE_COVER_BLOCKING_AREAS_AT_POSITION(float x, float y, float z)l
extern _native64(0x1F351CF1C6475734) void REMOVE_SPECIFIC_COVER_BLOCKING_AREAS(float startX, float startY, float startZ, float endX, float endY, float endZ, bool blockObjects, bool blockVehicles, bool blockMap, bool blockPlayer)l
extern _native64(0x142A02425FF02BD9) void TASK_START_SCENARIO_IN_PLACE(Ped ped, const char* scenarioName, int unkDelay, bool playEnterAnim)l
extern _native64(0xFA4EFC79F69D4F07) void TASK_START_SCENARIO_AT_POSITION(Ped ped, const char* scenarioName, float x, float y, float z, float heading, int duration, bool sittingScenario, bool teleport)l
extern _native64(0x277F471BA9DB000B) void TASK_USE_NEAREST_SCENARIO_TO_COORD(Ped ped, float x, float y, float z, float distance, int duration)l
extern _native64(0x58E2E0F23F6B76C3) void TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave)l
extern _native64(0x9FDA1B3D7E7028B3) void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(Ped ped, float x, float y, float z, float maxRange, int timeToLeave)l
extern _native64(0x97A28E63F0BA5631) void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave)l
extern _native64(0x5A59271FFADD33C1) bool DOES_SCENARIO_EXIST_IN_AREA(float x, float y, float z, float radius, bool mustBeFree)l
extern _native64(0x0A9D0C2A3BBC86C1) bool DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(float x, float y, float z, const char* scenarioName, float radius, bool mustBeFree)l
extern _native64(0x788756D73AC2E07C) bool IS_SCENARIO_OCCUPIED(float x, float y, float z, float maxRange, bool onlyUsersActuallyAtScenario)l
extern _native64(0x295E3CCEC879CCD7) bool PED_HAS_USE_SCENARIO_TASK(Ped ped)l
extern _native64(0x748040460F8DF5DC) void PLAY_ANIM_ON_RUNNING_SCENARIO(Ped ped, const char* animDict, const char* animName)l
extern _native64(0xF9034C136C9E00D3) bool DOES_SCENARIO_GROUP_EXIST(const char* scenarioGroup)l
extern _native64(0x367A09DED4E05B99) bool IS_SCENARIO_GROUP_ENABLED(const char* scenarioGroup)l
extern _native64(0x02C8E5B49848664E) void SET_SCENARIO_GROUP_ENABLED(const char* scenarioGroup, bool enabled)l
extern _native64(0xDD902D0349AFAD3A) void RESET_SCENARIO_GROUPS_ENABLED()l
extern _native64(0x535E97E1F7FC0C6A) void SET_EXCLUSIVE_SCENARIO_GROUP(const char* scenarioGroup)l
extern _native64(0x4202BBCB8684563D) void RESET_EXCLUSIVE_SCENARIO_GROUP()l
extern _native64(0x3A815DB3EA088722) bool IS_SCENARIO_TYPE_ENABLED(const char* scenarioType)l
extern _native64(0xEB47EC4E34FB7EE1) void SET_SCENARIO_TYPE_ENABLED(const char* scenarioType, bool toggle)l
extern _native64(0x0D40EE2A7F2B2D6D) void RESET_SCENARIO_TYPES_ENABLED()l
extern _native64(0xAA135F9482C82CC3) bool IS_PED_ACTIVE_IN_SCENARIO(Ped ped)l
extern _native64(0x621C6E4729388E41) bool IS_PED_PLAYING_BASE_CLIP_IN_SCENARIO(Ped ped)l
extern _native64(0x8FD89A6240813FD0) void SET_PED_CAN_PLAY_AMBIENT_IDLES(Ped ped, bool blockIdleClips, bool removeIdleClipIfPlaying)l
extern _native64(0x4CF5F55DAC3280A0) void TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, float x, float y, float z, float radius, int combatFlags)l
extern _native64(0x7BF835BB9E2698C8) void TASK_COMBAT_HATED_TARGETS_AROUND_PED(Ped ped, float radius, int combatFlags)l
extern _native64(0x2BBA30B854534A0C) void TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(Ped ped, float radius, int time, int combatFlags)l
extern _native64(0x7285951DBF6B5A51) void TASK_THROW_PROJECTILE(Ped ped, float x, float y, float z, int ignoreCollisionEntityIndex, bool createInvincibleProjectile)l
extern _native64(0xA21C51255B205245) void TASK_SWAP_WEAPON(Ped ped, bool drawWeapon)l
extern _native64(0x62D2916F56B9CD2D) void TASK_RELOAD_WEAPON(Ped ped, bool drawWeapon)l
extern _native64(0x2A74E1D5F2F00EEC) bool IS_PED_GETTING_UP(Ped ped)l
extern _native64(0xCDDC2B77CE54AC6E) void TASK_WRITHE(Ped ped, Ped target, int minFireLoops, int startState, bool forceShootOnGround, int shootFromGroundTimer)l
extern _native64(0xDEB6D52126E7D640) bool IS_PED_IN_WRITHE(Ped ped)l
extern _native64(0xA36BFB5EE89F3D82) void OPEN_PATROL_ROUTE(const char* patrolRoute)l
extern _native64(0xB043ECA801B8CBC1) void CLOSE_PATROL_ROUTE()l
extern _native64(0x8EDF950167586B7C) void ADD_PATROL_ROUTE_NODE(int nodeId, const char* nodeType, float posX, float posY, float posZ, float headingX, float headingY, float headingZ, int duration)l
extern _native64(0x23083260DEC3A551) void ADD_PATROL_ROUTE_LINK(int nodeId1, int nodeId2)l
extern _native64(0xAF8A443CCC8018DC) void CREATE_PATROL_ROUTE()l
extern _native64(0x7767DD9D65E91319) void DELETE_PATROL_ROUTE(const char* patrolRoute)l
extern _native64(0x52F734CEBE20DFBA) bool GET_PATROL_TASK_INFO(Ped ped, int* timeLeftAtNode, int* nodeId)l
extern _native64(0xBDA5DF49D080FE4E) void TASK_PATROL(Ped ped, const char* patrolRouteName, int alertState, bool canChatToPeds, bool useHeadLookAt)l
extern _native64(0xE5DA8615A6180789) void TASK_STAY_IN_COVER(Ped ped)l
extern _native64(0x5CF0D8F9BBA0DD75) void ADD_VEHICLE_SUBTASK_ATTACK_COORD(Ped ped, float x, float y, float z)l
extern _native64(0x85F462BADC7DA47F) void ADD_VEHICLE_SUBTASK_ATTACK_PED(Ped ped, Ped target)l
extern _native64(0x10AB107B887214D8) void TASK_VEHICLE_SHOOT_AT_PED(Ped ped, Ped target, float fireTolerance)l
extern _native64(0xE41885592B08B097) void TASK_VEHICLE_AIM_AT_PED(Ped ped, Ped target)l
extern _native64(0x5190796ED39C9B6D) void TASK_VEHICLE_SHOOT_AT_COORD(Ped ped, float x, float y, float z, float fireTolerance)l
extern _native64(0x447C1E9EF844BC0F) void TASK_VEHICLE_AIM_AT_COORD(Ped ped, float x, float y, float z)l
extern _native64(0x195AEEB13CEFE2EE) void TASK_VEHICLE_GOTO_NAVMESH(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int behaviorFlag, float stoppingRange)l
extern _native64(0x11315AB3385B8AC0) void TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Ped ped, float x, float y, float z, float aimAtX, float aimAtY, float aimAtZ, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, int navFlags, bool instantBlendToAim, Hash firingPattern)l
extern _native64(0xB2A16444EAD9AE47) void TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(Ped ped, float x, float y, float z, Entity aimAtID, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, int navFlags, bool instantBlendToAim, Hash firingPattern, int time)l
extern _native64(0xA55547801EB331FC) void TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(Ped pedHandle, float goToLocationX, float goToLocationY, float goToLocationZ, float focusLocationX, float focusLocationY, float focusLocationZ, float speed, bool shootAtEnemies, float distanceToStopAt, float noRoadsDistance, bool useNavMesh, int navFlags, int taskFlags, Hash firingPattern)l
extern _native64(0x04701832B739DCE5) void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(Ped ped, Entity entity, float aimX, float aimY, float aimZ, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, bool instantBlendToAim, Hash firingPattern)l
extern _native64(0x97465886D35210E9) void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, bool shootatEntity, float targetRadius, float slowDistance, bool useNavMesh, bool instantBlendToAim, Hash firingPattern)l
extern _native64(0x8C825BDC7741D37C) void SET_HIGH_FALL_TASK(Ped ped, int minTime, int maxTime, int entryType)l
extern _native64(0x9EEFB62EB27B5792) void REQUEST_WAYPOINT_RECORDING(const char* name)l
extern _native64(0xCB4E8BE8A0063C5D) bool GET_IS_WAYPOINT_RECORDING_LOADED(const char* name)l
extern _native64(0xFF1B8B4AA1C25DC8) void REMOVE_WAYPOINT_RECORDING(const char* name)l
extern _native64(0x5343532C01A07234) bool WAYPOINT_RECORDING_GET_NUM_POINTS(const char* name, int* points)l
extern _native64(0x2FB897405C90B361) bool WAYPOINT_RECORDING_GET_COORD(const char* name, int point, vector3* coord)l
extern _native64(0x005622AEBC33ACA9) float WAYPOINT_RECORDING_GET_SPEED_AT_POINT(const char* name, int point)l
extern _native64(0xB629A298081F876F) bool WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(const char* name, float x, float y, float z, int* point)l
extern _native64(0x0759591819534F7B) void TASK_FOLLOW_WAYPOINT_RECORDING(Ped ped, const char* name, int p2, int p3, int p4)l
extern _native64(0xE03B3F2D3DC59B64) bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(Ped ped)l
extern _native64(0x2720AAA75001E094) int GET_PED_WAYPOINT_PROGRESS(Ped ped)l
extern _native64(0xE6A877C64CAF1BC5) float GET_PED_WAYPOINT_DISTANCE(any p0)l
extern _native64(0xED98E10B0AFCE4B4) bool SET_PED_WAYPOINT_ROUTE_OFFSET(Ped ped, float x, float y, float z)l
extern _native64(0xA5B769058763E497) float GET_WAYPOINT_DISTANCE_ALONG_ROUTE(const char* name, int point)l
extern _native64(0x701375A7D43F01CB) bool WAYPOINT_PLAYBACK_GET_IS_PAUSED(any p0)l
extern _native64(0x0F342546AA06FED5) void WAYPOINT_PLAYBACK_PAUSE(any p0, bool p1, bool p2)l
extern _native64(0x244F70C84C547D2D) void WAYPOINT_PLAYBACK_RESUME(any p0, bool p1, any p2, any p3)l
extern _native64(0x7D7D2B47FA788E85) void WAYPOINT_PLAYBACK_OVERRIDE_SPEED(any p0, float p1, bool p2)l
extern _native64(0x6599D834B12D0800) void WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(any p0)l
extern _native64(0x5A353B8E6B1095B5) void USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(const char* name, bool p1, float p2, float p3)l
extern _native64(0x20E330937C399D29) void WAYPOINT_PLAYBACK_START_AIMING_AT_PED(Ped ped, Ped target, bool p2)l
extern _native64(0x8968400D900ED8B3) void WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(Ped ped, float x, float y, float z, bool p4)l
extern _native64(0xE70BA7B90F8390DC) void WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED(Ped ped, Ped ped2, bool p2, bool p3)l
extern _native64(0x057A25CFCC9DB671) void WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(Ped ped, float x, float y, float z, bool p4, Hash firingPattern)l
extern _native64(0x47EFA040EBB8E2EA) void WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(Ped ped)l
extern _native64(0x817268968605947A) void ASSISTED_MOVEMENT_REQUEST_ROUTE(const char* route)l
extern _native64(0x3548536485DD792B) void ASSISTED_MOVEMENT_REMOVE_ROUTE(const char* route)l
extern _native64(0x60F9A4393A21F741) bool ASSISTED_MOVEMENT_IS_ROUTE_LOADED(const char* route)l
extern _native64(0xD5002D78B7162E1B) void ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(const char* route, int props)l
extern _native64(0x13945951E16EF912) void ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(float dist)l
extern _native64(0x3123FAA6DB1CF7ED) void TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(Ped ped, Vehicle vehicle, const char* WPRecording, int p3, int p4, int p5, int p6, float p7, bool p8, float p9)l
extern _native64(0xF5134943EA29868C) bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle)l
extern _native64(0x9824CFF8FC66E159) int GET_VEHICLE_WAYPOINT_PROGRESS(Vehicle vehicle)l
extern _native64(0x416B62AC8B9E5BBD) int GET_VEHICLE_WAYPOINT_TARGET_POINT(Vehicle vehicle)l
extern _native64(0x8A4E6AC373666BC5) void VEHICLE_WAYPOINT_PLAYBACK_PAUSE(Vehicle vehicle)l
extern _native64(0xDC04FCAA7839D492) void VEHICLE_WAYPOINT_PLAYBACK_RESUME(Vehicle vehicle)l
extern _native64(0x5CEB25A7D2848963) void VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Vehicle vehicle)l
extern _native64(0x121F0593E0A431D7) void VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Vehicle vehicle, float speed)l
extern _native64(0x90D2156198831D69) void TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)l
extern _native64(0x4F056E1AFFEF17AB) void TASK_FORCE_MOTION_STATE(Ped ped, Hash state, bool forceRestart)l
extern _native64(0x2D537BA194896636) void TASK_MOVE_NETWORK_BY_NAME(Ped ped, const char* task, float multiplier, bool allowOverrideCloneUpdate, const char* animDict, int flags)l
extern _native64(0xD5B35BEA41919ACB) void TASK_MOVE_NETWORK_ADVANCED_BY_NAME(Ped ped, const char* network, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, bool allowOverrideCloneUpdate, const char* animDict, int flags)l
extern _native64(0x3D45B0B355C5E0C9) void TASK_MOVE_NETWORK_BY_NAME_WITH_INIT_PARAMS(Ped ped, const char* network, int* initialParameters, float blendDuration, bool allowOverrideCloneUpdate, const char* animDict, int flags)l
extern _native64(0x29682E2CCF21E9B5) void TASK_MOVE_NETWORK_ADVANCED_BY_NAME_WITH_INIT_PARAMS(Ped ped, const char* network, int* initialParameters, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, bool allowOverrideCloneUpdate, const char* dictionary, int flags)l
extern _native64(0x921CE12C489C4C41) bool IS_TASK_MOVE_NETWORK_ACTIVE(Ped ped)l
extern _native64(0x30ED88D5E0C56A37) bool IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION(Ped ped)l
extern _native64(0xD01015C7316AE176) bool REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION(Ped ped, const char* name)l
extern _native64(0xAB13A5565480B6D9) bool SET_EXPECTED_CLONE_NEXT_TASK_MOVE_NETWORK_STATE(Ped ped, const char* state)l
extern _native64(0x717E4D1F2048376D) const char* GET_TASK_MOVE_NETWORK_STATE(Ped ped)l
extern _native64(0x8423541E8B3A1589) void SET_TASK_MOVE_NETWORK_ANIM_SET(Ped ped, Hash clipSet, Hash variableClipSet)l
extern _native64(0xD5BB4025AE449A4E) void SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* signalName, float value)l
extern _native64(0x373EF409B82697A3) void SET_TASK_MOVE_NETWORK_SIGNAL_LOCAL_FLOAT(Ped ped, const char* signalName, float value)l
extern _native64(0x8634CEF2522D987B) void SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT_LERP_RATE(Ped ped, const char* signalName, float value)l
extern _native64(0xB0A6CFD2C69C1088) void SET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, const char* signalName, bool value)l
extern _native64(0x44AB0B3AFECCE242) float GET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* signalName)l
extern _native64(0xA7FFBA498E4AAF67) bool GET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, const char* signalName)l
extern _native64(0xB4F47213DF45A64C) bool GET_TASK_MOVE_NETWORK_EVENT(Ped ped, const char* eventName)l
extern _native64(0x0FFB3C758E8C07B9) bool SET_TASK_MOVE_NETWORK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(Ped ped, bool enable)l
extern _native64(0x349CE7B56DAFD95C) bool IS_MOVE_BLEND_RATIO_STILL(Ped ped)l
extern _native64(0xF133BBBE91E1691F) bool IS_MOVE_BLEND_RATIO_WALKING(Ped ped)l
extern _native64(0xD4D8636C0199A939) bool IS_MOVE_BLEND_RATIO_RUNNING(Ped ped)l
extern _native64(0x24A2AD74FA9814E2) bool IS_MOVE_BLEND_RATIO_SPRINTING(Ped ped)l
extern _native64(0xAC29253EEF8F0180) bool IS_PED_STILL(Ped ped)l
extern _native64(0xDE4C184B2B9B071A) bool IS_PED_WALKING(Ped ped)l
extern _native64(0xC5286FFC176F28A2) bool IS_PED_RUNNING(Ped ped)l
extern _native64(0x57E457CD2C0FC168) bool IS_PED_SPRINTING(Ped ped)l
extern _native64(0xE45B7F222DE47E09) bool IS_PED_STRAFING(Ped ped)l
extern _native64(0xEEA929141F699854) void TASK_SYNCHRONIZED_SCENE(Ped ped, int scene, const char* animDictionary, const char* animationName, float blendIn, float blendOut, int flags, int ragdollBlockingFlags, float moverBlendDelta, int ikFlags)l
extern _native64(0x19D1B791CB3670FE) void TASK_AGITATED_ACTION_CONFRONT_RESPONSE(Ped ped, Ped ped2)l
extern _native64(0x2047C02158D6405A) void TASK_SWEEP_AIM_ENTITY(Ped ped, const char* animDict, const char* lowAnimName, const char* medAnimName, const char* hiAnimName, int runtime, Entity targetEntity, float turnRate, float blendInDuration)l
extern _native64(0xE4973DBDBE6E44B3) void UPDATE_TASK_SWEEP_AIM_ENTITY(Ped ped, Entity entity)l
extern _native64(0x7AFE8FDC10BC07D2) void TASK_SWEEP_AIM_POSITION(Ped ped, const char* animDict, const char* lowAnimName, const char* medAnimName, const char* hiAnimName, int runtime, float x, float y, float z, float turnRate, float blendInDuration)l
extern _native64(0xBB106883F5201FC4) void UPDATE_TASK_SWEEP_AIM_POSITION(Ped ped, float x, float y, float z)l
extern _native64(0xF3B9A78A178572B1) void TASK_ARREST_PED(Ped ped, Ped target)l
extern _native64(0x3DC52677769B4AE0) bool IS_PED_RUNNING_ARREST_TASK(Ped ped)l
extern _native64(0x90A09F3A45FED688) bool IS_PED_BEING_ARRESTED(Ped ped)l
extern _native64(0x67406F2C8F87FC4F) void UNCUFF_PED(Ped ped)l
extern _native64(0x74E559B3BC910685) bool IS_PED_CUFFED(Ped ped)l
#pragma endregion //}
#pragma region VEHICLE //{
extern _native64(0xAF35D0D2583051B0) Vehicle CREATE_VEHICLE(Hash modelHash, float x, float y, float z, float heading, bool isNetwork, bool bScriptHostVeh, bool p7)l
extern _native64(0xEA386986E786A54F) void DELETE_VEHICLE(Vehicle* vehicle)l
extern _native64(0x7D6F9A3EF26136A0) void SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON(Vehicle vehicle, bool toggle, bool p2)l
extern _native64(0x1DDA078D12879EEE) void SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED(Vehicle vehicle, bool canBeLockedOn, bool p2)l
extern _native64(0x5D14D4154BFE7B2C) void SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(Vehicle veh, bool toggle)l
extern _native64(0xE6B0E8CFC3633BF0) int GET_VEHICLE_HOMING_LOCKON_STATE(Vehicle vehicle)l
extern _native64(0x6EAAEFC76ACC311F) int GET_VEHICLE_HOMING_LOCKEDONTO_STATE(any p0)l
extern _native64(0x407DC5E97DB1A4D3) void SET_VEHICLE_HOMING_LOCKEDONTO_STATE(any p0, any p1)l
extern _native64(0x423E8DE37D934D89) bool IS_VEHICLE_MODEL(Vehicle vehicle, Hash model)l
extern _native64(0xF6086BC836400876) bool DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(int vehicleGenerator)l
extern _native64(0x9DEF883114668116) int CREATE_SCRIPT_VEHICLE_GENERATOR(float x, float y, float z, float heading, float p4, float p5, Hash modelHash, int p7, int p8, int p9, int p10, bool p11, bool p12, bool p13, bool p14, bool p15, int p16)l
extern _native64(0x22102C9ABFCF125D) void DELETE_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator)l
extern _native64(0xD9D620E0AC6DC4B0) void SET_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator, bool enabled)l
extern _native64(0xC12321827687FE4D) void SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool toggle, bool p7)l
extern _native64(0x34AD89078831A4BC) void SET_ALL_VEHICLE_GENERATORS_ACTIVE()l
extern _native64(0x608207E7A8FB787C) void SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(bool active)l
extern _native64(0x9A75585FB2E54FAD) void SET_VEHICLE_GENERATOR_AREA_OF_INTEREST(float x, float y, float z, float radius)l
extern _native64(0x0A436B8643716D14) void CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST()l
extern _native64(0x49733E92263139D1) bool SET_VEHICLE_ON_GROUND_PROPERLY(Vehicle vehicle, float p1)l
extern _native64(0xE023E8AC4EF7C117) bool SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION(Vehicle p0, bool p1, bool p2, bool p3)l
extern _native64(0xB497F06B288DCFDF) bool IS_VEHICLE_STUCK_ON_ROOF(Vehicle vehicle)l
extern _native64(0xB72E26D81006005B) void ADD_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)l
extern _native64(0xC53EB42A499A7E90) void REMOVE_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)l
extern _native64(0x5721B434AD84D57A) bool IS_VEHICLE_STOPPED(Vehicle vehicle)l
extern _native64(0x24CB2137731FFE89) int GET_VEHICLE_NUMBER_OF_PASSENGERS(Vehicle vehicle, bool includeDriver, bool includeDeadOccupants)l
extern _native64(0xA7C4F2C6E744A550) int GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vehicle vehicle)l
extern _native64(0x2AD93716F184EDA4) int GET_VEHICLE_MODEL_NUMBER_OF_SEATS(Hash modelHash)l
extern _native64(0xF7F203E31F96F6A1) bool IS_SEAT_WARP_ONLY(Vehicle vehicle, int seatIndex)l
extern _native64(0xE33FFA906CE74880) bool IS_TURRET_SEAT(Vehicle vehicle, int seatIndex)l
extern _native64(0x4E417C547182C84D) bool DOES_VEHICLE_ALLOW_RAPPEL(Vehicle vehicle)l
extern _native64(0x245A6883D966D537) void SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0xB3B3359379FE77D3) void SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0xEAE6DCC7EEE3DB1D) void SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0xD4B8E3D1917BC86B) void SET_DISABLE_RANDOM_TRAINS_THIS_FRAME(bool toggle)l
extern _native64(0x90B6DA738A9A25DA) void SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(float value)l
extern _native64(0x26324F33423F3CC3) void SET_FAR_DRAW_VEHICLES(bool toggle)l
extern _native64(0xCAA15F13EBD417FF) void SET_NUMBER_OF_PARKED_VEHICLES(int value)l
extern _native64(0xB664292EAECF7FA6) void SET_VEHICLE_DOORS_LOCKED(Vehicle vehicle, int doorLockStatus)l
extern _native64(0xBE70724027F85BCD) void SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED(Vehicle vehicle, int doorId, int doorLockStatus)l
extern _native64(0xD8050E0EB60CF274) void SET_VEHICLE_HAS_MUTED_SIRENS(Vehicle vehicle, bool toggle)l
extern _native64(0x517AAF684BB50CD1) void SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player, bool toggle)l
extern _native64(0xF6AF6CB341349015) bool GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player)l
extern _native64(0xA2F80B8D040727CC) void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(Vehicle vehicle, bool toggle)l
extern _native64(0x9737A37136F07E75) void SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS(Vehicle vehicle, bool toggle)l
extern _native64(0xB81F6D4A8F5EEBA8) void SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(Vehicle vehicle, int team, bool toggle)l
extern _native64(0x203B527D1B77904C) void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_TEAMS(Vehicle vehicle, bool toggle)l
extern _native64(0x76D26A22750E849E) void SET_VEHICLE_DONT_TERMINATE_TASK_WHEN_ACHIEVED(Vehicle vehicle)l
extern _native64(0xBA71116ADF5B514C) void EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible)l
extern _native64(0xF19D095E42D430CC) void SET_VEHICLE_OUT_OF_CONTROL(Vehicle vehicle, bool killDriver, bool explodeOnImpact)l
extern _native64(0x2E0A74E1002380B1) void SET_VEHICLE_TIMED_EXPLOSION(Vehicle vehicle, Ped ped, bool toggle)l
extern _native64(0x99AD4CCCB128CBC9) void ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE(Vehicle vehicle)l
extern _native64(0xAA3F739ABDDCF21F) void CLEAR_VEHICLE_PHONE_EXPLOSIVE_DEVICE()l
extern _native64(0x6ADAABD3068C5235) bool HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE()l
extern _native64(0xEF49CF0270307CBE) void DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE()l
extern _native64(0x6B407F2525E93644) bool HAVE_VEHICLE_REAR_DOORS_BEEN_BLOWN_OPEN_BY_STICKYBOMB(Vehicle vehicle)l
extern _native64(0x598803E85E8448D9) void SET_TAXI_LIGHTS(Vehicle vehicle, bool state)l
extern _native64(0x7504C0F113AB50FC) bool IS_TAXI_LIGHT_ON(Vehicle vehicle)l
extern _native64(0xCEE4490CD57BB3C2) bool IS_VEHICLE_IN_GARAGE_AREA(const char* garageName, Vehicle vehicle)l
extern _native64(0x4F1D4BE3A7F24601) void SET_VEHICLE_COLOURS(Vehicle vehicle, int colorPrimary, int colorSecondary)l
extern _native64(0x8B7FD87F0DDB421E) void SET_VEHICLE_FULLBEAM(Vehicle vehicle, bool toggle)l
extern _native64(0x07116E24E9D1929D) void SET_VEHICLE_IS_RACING(Vehicle vehicle, bool toggle)l
extern _native64(0x7141766F91D15BEA) void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int r, int g, int b)l
extern _native64(0xB64CF2CCA9D95F52) void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x55E1D2758F34E437) void CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle)l
extern _native64(0xF095C0405307B21B) bool GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Vehicle vehicle)l
extern _native64(0x36CED73BFED89754) void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int r, int g, int b)l
extern _native64(0x8389CD56CA8072DC) void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x5FFBDEEC3E8E2009) void CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle)l
extern _native64(0x910A32E7AAD2656C) bool GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Vehicle vehicle)l
extern _native64(0x3AFDC536C3D01674) void SET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle, float fade)l
extern _native64(0xA82819CAC9C4C403) float GET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle)l
extern _native64(0x52BBA29D5EC69356) void SET_CAN_RESPRAY_VEHICLE(Vehicle vehicle, bool state)l
extern _native64(0xAB31EF4DE6800CE9) void SET_GOON_BOSS_VEHICLE(Vehicle vehicle, bool toggle)l
extern _native64(0x1B212B26DD3C04DF) void SET_OPEN_REAR_DOORS_ON_EXPLOSION(Vehicle vehicle, bool toggle)l
extern _native64(0x33506883545AC0DF) void FORCE_SUBMARINE_SURFACE_MODE(Vehicle vehicle, bool toggle)l
extern _native64(0xC67DB108A9ADE3BE) void FORCE_SUBMARINE_NEURTAL_BUOYANCY(any p0, any p1)l
extern _native64(0xC59872A5134879C7) void SET_SUBMARINE_CRUSH_DEPTHS(Vehicle vehicle, bool p1, float depth1, float depth2, float depth3)l
extern _native64(0x3E71D0B300B7AA79) bool GET_SUBMARINE_IS_UNDER_DESIGN_DEPTH(Vehicle submarine)l
extern _native64(0x093D6DDCA5B8FBAE) int GET_SUBMARINE_NUMBER_OF_AIR_LEAKS(Vehicle submarine)l
extern _native64(0xED5EDE9E676643C9) void SET_BOAT_IGNORE_LAND_PROBES(any p0, any p1)l
extern _native64(0x85FC953F6C6CBDE1) void _SET_BOUNDS_AFFECT_WATER_PROBES(Vehicle vehicle, bool toggle)l
extern _native64(0x75DBEC174AEEAD10) void SET_BOAT_ANCHOR(Vehicle vehicle, bool toggle)l
extern _native64(0x26C10ECBDA5D043B) bool CAN_ANCHOR_BOAT_HERE(Vehicle vehicle)l
extern _native64(0x24F4121D07579880) bool CAN_ANCHOR_BOAT_HERE_IGNORE_PLAYERS(Vehicle vehicle)l
extern _native64(0xE3EBAAE484798530) void SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER(Vehicle vehicle, bool toggle)l
extern _native64(0xB28B1FE5BFADD7F5) void SET_FORCE_LOW_LOD_ANCHOR_MODE(Vehicle vehicle, bool p1)l
extern _native64(0xE842A9398079BD82) void SET_BOAT_LOW_LOD_ANCHOR_DISTANCE(Vehicle vehicle, float value)l
extern _native64(0xB0AD1238A709B1A2) bool IS_BOAT_ANCHORED(Vehicle vehicle)l
extern _native64(0x8F719973E1445BA2) void SET_BOAT_SINKS_WHEN_WRECKED(Vehicle vehicle, bool toggle)l
extern _native64(0xBD32E46AA95C1DD2) void SET_BOAT_WRECKED(Vehicle vehicle)l
extern _native64(0xF4924635A19EB37D) void SET_VEHICLE_SIREN(Vehicle vehicle, bool toggle)l
extern _native64(0x4C9BF537BE2634B2) bool IS_VEHICLE_SIREN_ON(Vehicle vehicle)l
extern _native64(0xB5CC40FBCB586380) bool IS_VEHICLE_SIREN_AUDIO_ON(Vehicle vehicle)l
extern _native64(0x3E8C8727991A8A0B) void SET_VEHICLE_STRONG(Vehicle vehicle, bool toggle)l
extern _native64(0x8386BFB614D06749) void REMOVE_VEHICLE_STUCK_CHECK(Vehicle vehicle)l
extern _native64(0xA19435F193E081AC) void GET_VEHICLE_COLOURS(Vehicle vehicle, int* colorPrimary, int* colorSecondary)l
extern _native64(0x22AC59A870E6A669) bool IS_VEHICLE_SEAT_FREE(Vehicle vehicle, int seatIndex, bool isTaskRunning)l
extern _native64(0xBB40DD2270B65366) Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex, bool p2)l
extern _native64(0x83F969AA1EE2A664) Ped GET_LAST_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex)l
extern _native64(0xB91B4C20085BD12F) bool GET_VEHICLE_LIGHTS_STATE(Vehicle vehicle, bool* lightsOn, bool* highbeamsOn)l
extern _native64(0xBA291848A0815CA9) bool IS_VEHICLE_TYRE_BURST(Vehicle vehicle, int wheelID, bool completely)l
extern _native64(0xAB54A438726D25D5) void SET_VEHICLE_FORWARD_SPEED(Vehicle vehicle, float speed)l
extern _native64(0x6501129C9E0FFA05) void SET_VEHICLE_FORWARD_SPEED_XY(Vehicle vehicle, float speed)l
extern _native64(0x260BE8F09E326A20) void BRING_VEHICLE_TO_HALT(Vehicle vehicle, float distance, int duration, bool p3)l
extern _native64(0xDCE97BDF8A0EABC8) void SET_VEHICLE_STEER_FOR_BUILDINGS(Vehicle vehicle, any p1)l
extern _native64(0x9849DE24FCF23CCC) void SET_VEHICLE_CAUSES_SWERVING(Vehicle vehicle, bool toggle)l
extern _native64(0x8664170EF165C4A6) void SET_IGNORE_PLANES_SMALL_PITCH_CHANGE(any p0, any p1)l
extern _native64(0x7C06330BFDDA182E) void STOP_BRINGING_VEHICLE_TO_HALT(Vehicle vehicle)l
extern _native64(0xC69BB1D832A710EF) bool IS_VEHICLE_BEING_BROUGHT_TO_HALT(Vehicle vehicle)l
extern _native64(0x923A293361DF44E5) void LOWER_FORKLIFT_FORKS(Vehicle forklift)l
extern _native64(0x37EBBF3117BD6A25) void SET_FORKLIFT_FORK_HEIGHT(Vehicle vehicle, float height)l
extern _native64(0x57715966069157AD) bool IS_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle, Entity entity)l
extern _native64(0x62CA17B74C435651) bool IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle)l
extern _native64(0x375E7FC44F21C8AB) Vehicle FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO(Entity entity)l
extern _native64(0x89D630CF5EA96D23) bool IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER(Vehicle vehicle, Entity entity)l
extern _native64(0x6A98C2ECF57FA5D4) void ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP(Vehicle vehicle, Entity entity)l
extern _native64(0x7C0043FDFF6436BC) void DETACH_CONTAINER_FROM_HANDLER_FRAME(Vehicle vehicle)l
extern _native64(0x8AA9180DE2FEDD45) void SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE(Vehicle vehicle, bool p1)l
extern _native64(0x0A6A279F3AA4FD70) void SET_BOAT_DISABLE_AVOIDANCE(Vehicle vehicle, bool p1)l
extern _native64(0x634148744F385576) bool IS_HELI_LANDING_AREA_BLOCKED(Vehicle vehicle)l
extern _native64(0x107A473D7A6647A9) void SET_SHORT_SLOWDOWN_FOR_LANDING(Vehicle vehicle)l
extern _native64(0xE6F13851780394DA) void SET_HELI_TURBULENCE_SCALAR(Vehicle vehicle, float p1)l
extern _native64(0xFC40CBF7B90CA77C) void SET_CAR_BOOT_OPEN(Vehicle vehicle)l
extern _native64(0xEC6A202EE4960385) void SET_VEHICLE_TYRE_BURST(Vehicle vehicle, int index, bool onRim, float p3)l
extern _native64(0x781B3D62BB013EF5) void SET_VEHICLE_DOORS_SHUT(Vehicle vehicle, bool closeInstantly)l
extern _native64(0xEB9DC3C7D8596C46) void SET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle, bool toggle)l
extern _native64(0x678B9BB8C3F58FEB) bool GET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle)l
extern _native64(0x29B18B4FD460CA8F) void SET_VEHICLE_WHEELS_CAN_BREAK(Vehicle vehicle, bool enabled)l
extern _native64(0x7C65DAC73C35C862) void SET_VEHICLE_DOOR_OPEN(Vehicle vehicle, int doorId, bool loose, bool openInstantly)l
extern _native64(0x3B458DDB57038F08) void SET_VEHICLE_DOOR_AUTO_LOCK(Vehicle vehicle, int doorId, bool toggle)l
extern _native64(0xA247F9EF01D8082E) void SET_FLEEING_VEHICLES_USE_SWITCHED_OFF_NODES(any p0)l
extern _native64(0xA711568EEDB43069) void REMOVE_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x85796B0549DDE156) void ROLL_DOWN_WINDOWS(Vehicle vehicle)l
extern _native64(0x7AD9E6CE657D69E3) void ROLL_DOWN_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x602E548F46E24D59) void ROLL_UP_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x9E5B5E4D2CCD2259) void SMASH_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x772282EBEB95E682) void FIX_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x6D645D59FB5F5AD3) void POP_OUT_VEHICLE_WINDSCREEN(Vehicle vehicle)l
extern _native64(0xE38CB9D7D39FDBCC) void POP_OFF_VEHICLE_ROOF_WITH_IMPULSE(Vehicle vehicle, float x, float y, float z)l
extern _native64(0x34E710FF01247C5A) void SET_VEHICLE_LIGHTS(Vehicle vehicle, int state)l
extern _native64(0xC45C27EF50F36ADC) void SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS(Vehicle vehicle, bool toggle)l
extern _native64(0x1FD09E7390A74D54) void SET_VEHICLE_HEADLIGHT_SHADOWS(Vehicle vehicle, int p1)l
extern _native64(0xCDE5E70C1DDB954C) void SET_VEHICLE_ALARM(Vehicle vehicle, bool state)l
extern _native64(0xB8FF7AB45305C345) void START_VEHICLE_ALARM(Vehicle vehicle)l
extern _native64(0x4319E335B71FFF34) bool IS_VEHICLE_ALARM_ACTIVATED(Vehicle vehicle)l
extern _native64(0xBC2042F090AF6AD3) void SET_VEHICLE_INTERIORLIGHT(Vehicle vehicle, bool toggle)l
extern _native64(0x8821196D91FA2DE5) void SET_VEHICLE_FORCE_INTERIORLIGHT(Vehicle vehicle, bool toggle)l
extern _native64(0xB385454F8791F57C) void SET_VEHICLE_LIGHT_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native64(0x3C7D42D58F770B54) void ATTACH_VEHICLE_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float radius)l
extern _native64(0x16B5E274BDE402F8) void ATTACH_VEHICLE_ON_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float offsetX, float offsetY, float offsetZ, float coordsX, float coordsY, float coordsZ, float rotationX, float rotationY, float rotationZ, float disableCollisions)l
extern _native64(0x374706271354CB18) void STABILISE_ENTITY_ATTACHED_TO_HELI(Vehicle vehicle, Entity entity, float p2)l
extern _native64(0x90532EDF0D2BDD86) void DETACH_VEHICLE_FROM_TRAILER(Vehicle vehicle)l
extern _native64(0xE7CF3C4F9F489F0C) bool IS_VEHICLE_ATTACHED_TO_TRAILER(Vehicle vehicle)l
extern _native64(0x2A8F319B392E7B3F) void SET_TRAILER_INVERSE_MASS_SCALE(Vehicle vehicle, float p1)l
extern _native64(0x95CF53B3D687F9FA) void SET_TRAILER_LEGS_RAISED(Vehicle vehicle)l
extern _native64(0x878C75C09FBDB942) void SET_TRAILER_LEGS_LOWERED(Vehicle vehicle)l
extern _native64(0x6E13FC662B882D1D) void SET_VEHICLE_TYRE_FIXED(Vehicle vehicle, int tyreIndex)l
extern _native64(0x95A88F0B409CDA47) void SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle, const char* plateText)l
extern _native64(0x7CE1CCB9B293020E) const char* GET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle)l
extern _native64(0x4C4D6B2644F458CB) int GET_NUMBER_OF_VEHICLE_NUMBER_PLATES()l
extern _native64(0x9088EB5A43FFB0A1) void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle, int plateIndex)l
extern _native64(0xF11BC2DD9A3E7195) int GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle)l
extern _native64(0x80D9F74197EA47D9) void SET_RANDOM_TRAINS(bool toggle)l
extern _native64(0x63C6CCA8E68AE8C8) Vehicle CREATE_MISSION_TRAIN(int variation, float x, float y, float z, bool direction, any p5, any p6)l
extern _native64(0xFD813BB7DB977F20) void SWITCH_TRAIN_TRACK(int trackId, bool state)l
extern _native64(0x21973BBF8D17EDFA) void SET_TRAIN_TRACK_SPAWN_FREQUENCY(int trackIndex, int frequency)l
extern _native64(0x2310A8F9421EBF43) void ALLOW_TRAIN_TO_BE_REMOVED_BY_POPULATION(any p0)l
extern _native64(0x736A718577F39C7D) void DELETE_ALL_TRAINS()l
extern _native64(0xAA0BC91BE0B796E3) void SET_TRAIN_SPEED(Vehicle train, float speed)l
extern _native64(0x16469284DB8C62B5) void SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed)l
extern _native64(0x84436EC293B1415F) void SET_RANDOM_BOATS(bool toggle)l
extern _native64(0xDA5E12F728DB30CA) void SET_RANDOM_BOATS_MP(bool toggle)l
extern _native64(0x2AFD795EEAC8D30D) void SET_GARBAGE_TRUCKS(bool toggle)l
extern _native64(0x57E4C39DE5EE8470) bool DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(Vehicle vehicle)l
extern _native64(0x21543C612379DB3C) int GET_VEHICLE_RECORDING_ID(int recording, const char* script)l
extern _native64(0xAF514CABE74CBF15) void REQUEST_VEHICLE_RECORDING(int recording, const char* script)l
extern _native64(0x300D614A4C785FC4) bool HAS_VEHICLE_RECORDING_BEEN_LOADED(int recording, const char* script)l
extern _native64(0xF1160ACCF98A3FC8) void REMOVE_VEHICLE_RECORDING(int recording, const char* script)l
extern _native64(0x92523B76657A517D) vector3 GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time)l
extern _native64(0xD242728AA6F0FBA2) vector3 GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, const char* script)l
extern _native64(0xF0F2103EFAF8CBA7) vector3 GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time)l
extern _native64(0x2058206FBE79A8AD) vector3 GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, const char* script)l
extern _native64(0x102D125411A7B6E6) float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(int id)l
extern _native64(0x0E48D1C262390950) float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(int recording, const char* script)l
extern _native64(0x2DACD605FC681475) float GET_POSITION_IN_RECORDING(Vehicle vehicle)l
extern _native64(0x5746F3A7AB7FE544) float GET_TIME_POSITION_IN_RECORDING(Vehicle vehicle)l
extern _native64(0x3F878F92B3A7A071) void START_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, int recording, const char* script, bool p3)l
extern _native64(0x7D80FD645D4DA346) void START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(Vehicle vehicle, int recording, const char* script, int flags, int time, int drivingStyle)l
extern _native64(0x1F2E4E06DEA8992B) void FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE(Vehicle vehicle, bool p1)l
extern _native64(0x54833611C17ABDEA) void STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)l
extern _native64(0x632A689BF42301B1) void PAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)l
extern _native64(0x8879EE09268305D5) void UNPAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)l
extern _native64(0x1C8A4C2C19E68EEC) bool IS_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle)l
extern _native64(0xAEA8FD591FAD4106) bool IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(Vehicle vehicle)l
extern _native64(0x42BC05C27A946054) int GET_CURRENT_PLAYBACK_FOR_VEHICLE(Vehicle vehicle)l
extern _native64(0xAB8E2EDA0C0A5883) void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)l
extern _native64(0x6683AB880E427778) void SET_PLAYBACK_SPEED(Vehicle vehicle, float speed)l
extern _native64(0x29DE5FA52D00428C) void START_PLAYBACK_RECORDED_VEHICLE_USING_AI(Vehicle vehicle, int recording, const char* script, float speed, int drivingStyle)l
extern _native64(0x9438F7AD68771A20) void SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, float time)l
extern _native64(0xA549C3B37EA28131) void SET_PLAYBACK_TO_USE_AI(Vehicle vehicle, int drivingStyle)l
extern _native64(0x6E63860BBB190730) void SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(Vehicle vehicle, int time, int drivingStyle, bool p3)l
extern _native64(0x5845066D8A1EA7F7) void SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z, any p4)l
extern _native64(0x796A877E459B99EA) void SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z)l
extern _native64(0xFAF2A78061FD9EF4) void SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z)l
extern _native64(0x063AE2B2CC273588) void SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING(Vehicle vehicle, bool p1)l
extern _native64(0x786A4EB67B01BF0B) void EXPLODE_VEHICLE_IN_CUTSCENE(Vehicle vehicle, bool p1)l
extern _native64(0x2FA9923062DD396C) void ADD_VEHICLE_STUCK_CHECK_WITH_WARP(any p0, float p1, any p2, bool p3, bool p4, bool p5, any p6)l
extern _native64(0x0FC2D89AC25A5814) void SET_VEHICLE_MODEL_IS_SUPPRESSED(Hash model, bool suppressed)l
extern _native64(0x386F6CE5BAF6091C) Vehicle GET_RANDOM_VEHICLE_IN_SPHERE(float x, float y, float z, float radius, Hash modelHash, int flags)l
extern _native64(0xC5574E0AEB86BA68) Vehicle GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native64(0xB50807EABE20A8DC) Vehicle GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native64(0xF73EB622C4F1689B) Vehicle GET_CLOSEST_VEHICLE(float x, float y, float z, float radius, Hash modelHash, int flags)l
extern _native64(0x08AAFD0814722BC3) Vehicle GET_TRAIN_CARRIAGE(Vehicle train, int trailerNumber)l
extern _native64(0xAD464F2E18836BFC) bool IS_MISSION_TRAIN(Vehicle train)l
extern _native64(0x5B76B14AE875C795) void DELETE_MISSION_TRAIN(Vehicle* train)l
extern _native64(0xBBE7648349B49BE8) void SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Vehicle* train, bool p1)l
extern _native64(0x591CA673AA6AB736) void SET_MISSION_TRAIN_COORDS(Vehicle train, float x, float y, float z)l
extern _native64(0x45A9187928F4B9E3) bool IS_THIS_MODEL_A_BOAT(Hash model)l
extern _native64(0x9537097412CF75FE) bool IS_THIS_MODEL_A_JETSKI(Hash model)l
extern _native64(0xA0948AB42D7BA0DE) bool IS_THIS_MODEL_A_PLANE(Hash model)l
extern _native64(0xDCE4334788AF94EA) bool IS_THIS_MODEL_A_HELI(Hash model)l
extern _native64(0x7F6DB52EEFC96DF8) bool IS_THIS_MODEL_A_CAR(Hash model)l
extern _native64(0xAB935175B22E822B) bool IS_THIS_MODEL_A_TRAIN(Hash model)l
extern _native64(0xB50C0B0CEDC6CE84) bool IS_THIS_MODEL_A_BIKE(Hash model)l
extern _native64(0xBF94DD42F63BDED2) bool IS_THIS_MODEL_A_BICYCLE(Hash model)l
extern _native64(0x39DAC362EE65FA28) bool IS_THIS_MODEL_A_QUADBIKE(Hash model)l
extern _native64(0x633F6F44A537EBB6) bool IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(Hash model)l
extern _native64(0xA1A9FC1C76A6730D) bool IS_THIS_MODEL_AN_AMPHIBIOUS_QUADBIKE(Hash model)l
extern _native64(0xA178472EBB8AE60D) void SET_HELI_BLADES_FULL_SPEED(Vehicle vehicle)l
extern _native64(0xFD280B4D7F3ABC4D) void SET_HELI_BLADES_SPEED(Vehicle vehicle, float speed)l
extern _native64(0x99CAD8E7AFDB60FA) void FORCE_SUB_THROTTLE_FOR_TIME(Vehicle vehicle, float p1, float p2)l
extern _native64(0x3750146A28097A82) void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle vehicle, bool state)l
extern _native64(0xDBC631F109350B8C) void SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER(Vehicle vehicle, bool p1)l
extern _native64(0x4C7028F78FFD3681) void SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, bool state)l
extern _native64(0x1AA8A837D2169D94) void SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(Vehicle vehicle, bool toggle)l
extern _native64(0x2311DD7159F00582) void SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER(Vehicle vehicle, bool p1)l
extern _native64(0x065D03A9D6B2C6B5) void SET_VEHICLE_CAN_EJECT_PASSENGERS_IF_LOCKED(any p0, any p1)l
extern _native64(0x8F17BC8BA08DA62B) float GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle)l
extern _native64(0x79D3B596FE44EE8B) void SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float dirtLevel)l
extern _native64(0xBCDC5017D3CE1E9E) bool GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(Vehicle vehicle)l
extern _native64(0x3E933CFF7B111C22) bool IS_VEHICLE_DOOR_FULLY_OPEN(Vehicle vehicle, int doorId)l
extern _native64(0x2497C4717C8B881E) void SET_VEHICLE_ENGINE_ON(Vehicle vehicle, bool value, bool instantly, bool disableAutoStart)l
extern _native64(0x8ABA6AF54B942B95) void SET_VEHICLE_UNDRIVEABLE(Vehicle vehicle, bool toggle)l
extern _native64(0x5AFEEDD9BB2899D7) void SET_VEHICLE_PROVIDES_COVER(Vehicle vehicle, bool toggle)l
extern _native64(0xF2BFA0430F0A0FCB) void SET_VEHICLE_DOOR_CONTROL(Vehicle vehicle, int doorId, int speed, float angle)l
extern _native64(0xA5A9653A8D2CAF48) void SET_VEHICLE_DOOR_LATCHED(Vehicle vehicle, int doorId, bool p2, bool p3, bool p4)l
extern _native64(0xFE3F9C29F7B32BD5) float GET_VEHICLE_DOOR_ANGLE_RATIO(Vehicle vehicle, int doorId)l
extern _native64(0x218297BF0CFD853B) Ped GET_PED_USING_VEHICLE_DOOR(Vehicle vehicle, int doord)l
extern _native64(0x93D9BD300D7789E5) void SET_VEHICLE_DOOR_SHUT(Vehicle vehicle, int doorId, bool closeInstantly)l
extern _native64(0xD4D4F6A4AB575A33) void SET_VEHICLE_DOOR_BROKEN(Vehicle vehicle, int doorId, bool deleteDoor)l
extern _native64(0x59BF8C3D52C92F66) void SET_VEHICLE_CAN_BREAK(Vehicle vehicle, bool toggle)l
extern _native64(0x8AC862B0B32C5B80) bool DOES_VEHICLE_HAVE_ROOF(Vehicle vehicle)l
extern _native64(0xC4B3347BD68BD609) void SET_VEHICLE_REMOVE_AGGRESSIVE_CARJACK_MISSION(any p0)l
extern _native64(0xD3301660A57C9272) void SET_VEHICLE_AVOID_PLAYER_VEHICLE_RIOT_VAN_MISSION(any p0)l
extern _native64(0xB9562064627FF9DB) void SET_CARJACK_MISSION_REMOVAL_PARAMETERS(any p0, any p1)l
extern _native64(0x9F243D3919F442FE) bool IS_BIG_VEHICLE(Vehicle vehicle)l
extern _native64(0x3B963160CD65D41E) int GET_NUMBER_OF_VEHICLE_COLOURS(Vehicle vehicle)l
extern _native64(0x33E8CD3322E2FE31) void SET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle, int colorCombination)l
extern _native64(0x6A842D197F845D56) int GET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle)l
extern _native64(0xE41033B25D003A07) void SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle, int colorIndex)l
extern _native64(0x3DFF319A831E0CDB) int GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle)l
extern _native64(0x31B927BBC44156CD) void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle vehicle, bool toggle)l
extern _native64(0xBE5C1255A1830FF5) void SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP(Vehicle vehicle, bool toggle)l
extern _native64(0x9BECD4B9FEF3F8A6) void SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON(Vehicle vehicle, bool p1)l
extern _native64(0x88BC673CA9E0AE99) void SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS(Vehicle vehicle, bool p1)l
extern _native64(0xE851E480B814D4BA) void SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS(Vehicle vehicle, bool p1)l
extern _native64(0x055BF0AC0C34F4FD) void GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(bool p0, Hash* modelHash, int* successIndicator)l
extern _native64(0x25BC98A59C2EA962) int GET_VEHICLE_DOOR_LOCK_STATUS(Vehicle vehicle)l
extern _native64(0xCA4AC3EAAE46EC7B) int GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS(Vehicle vehicle, int doorId)l
extern _native64(0xB8E181E559464527) bool IS_VEHICLE_DOOR_DAMAGED(Vehicle veh, int doorID)l
extern _native64(0x2FA133A4A9D37ED8) void SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(Vehicle vehicle, int doorId, bool isBreakable)l
extern _native64(0x27B926779DEB502D) bool IS_VEHICLE_BUMPER_BOUNCING(Vehicle vehicle, bool frontBumper)l
extern _native64(0x468056A6BB6F3846) bool IS_VEHICLE_BUMPER_BROKEN_OFF(Vehicle vehicle, bool frontBumper)l
extern _native64(0x7EEF65D5F153E26A) bool IS_COP_VEHICLE_IN_AREA_3D(float x1, float x2, float y1, float y2, float z1, float z2)l
extern _native64(0xB104CD1BABF302E2) bool IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle)l
extern _native64(0x5873C14A52D74236) int GET_VEHICLE_MODEL_VALUE(Hash vehicleModel)l
extern _native64(0x28D37D4F71AC5C58) Hash GET_VEHICLE_LAYOUT_HASH(Vehicle vehicle)l
extern _native64(0xA01BC64DD4BFBBAC) Hash GET_IN_VEHICLE_CLIPSET_HASH_FOR_SEAT(Vehicle vehicle, int p1)l
extern _native64(0x317B11A312DF5534) void SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, bool toggle)l
extern _native64(0x2036F561ADD12E33) void SET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int pearlescentColor, int wheelColor)l
extern _native64(0x3BC4245933A166F7) void GET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int* pearlescentColor, int* wheelColor)l
extern _native64(0xF40DD601A65F7F19) void SET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int color)l
extern _native64(0x7D1464D472D32136) void GET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int* color)l
extern _native64(0x6089CDF6A57F326C) void SET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int color)l
extern _native64(0xB7635E80A5C31BFF) void GET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int* color)l
extern _native64(0x0F87E938BDF29D66) void STOP_ALL_GARAGE_ACTIVITY()l
extern _native64(0x115722B1B9C14C1C) void SET_VEHICLE_FIXED(Vehicle vehicle)l
extern _native64(0x953DA1E1B12C0491) void SET_VEHICLE_DEFORMATION_FIXED(Vehicle vehicle)l
extern _native64(0x206BC5DC9D1AC70A) void SET_VEHICLE_CAN_ENGINE_MISSFIRE(Vehicle vehicle, bool toggle)l
extern _native64(0x51BB2D88D31A914B) void SET_VEHICLE_CAN_LEAK_OIL(Vehicle vehicle, bool toggle)l
extern _native64(0x192547247864DFDD) void SET_VEHICLE_CAN_LEAK_PETROL(Vehicle vehicle, bool toggle)l
extern _native64(0x465BF26AB9684352) void SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(Vehicle vehicle, bool toggle)l
extern _native64(0x37C8252A7C92D017) void SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0x91A0BD635321F145) void SET_DISABLE_VEHICLE_ENGINE_FIRES(Vehicle vehicle, bool toggle)l
extern _native64(0xC50CE861B55EAB8B) void SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE(Vehicle vehicle, bool toggle)l
extern _native64(0x6EBFB22D646FFC18) void SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE(Vehicle vehicle, bool toggle)l
extern _native64(0x25367DE49D64CF16) void SET_DISABLE_PRETEND_OCCUPANTS(Vehicle vehicle, bool toggle)l
extern _native64(0x46A1E1A299EC4BBA) void REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, any p6)l
extern _native64(0x42A8EC77D5150CBE) void SET_VEHICLE_STEER_BIAS(Vehicle vehicle, float value)l
extern _native64(0xD2E6822DBFD6C8BD) bool IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, int extraId)l
extern _native64(0x7EE3A3C5E4A40CC9) void SET_VEHICLE_EXTRA(Vehicle vehicle, int extraId, bool disable)l
extern _native64(0x1262D55792428154) bool DOES_EXTRA_EXIST(Vehicle vehicle, int extraId)l
extern _native64(0x534E36D4DB9ECC5D) bool IS_EXTRA_BROKEN_OFF(Vehicle vehicle, int extraId)l
extern _native64(0xF39C4F538B5124C2) void SET_CONVERTIBLE_ROOF(Vehicle vehicle, bool p1)l
extern _native64(0xDED51F703D0FA83D) void LOWER_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyLower)l
extern _native64(0x8F5FB35D7E88FC70) void RAISE_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyRaise)l
extern _native64(0xF8C397922FC03F41) int GET_CONVERTIBLE_ROOF_STATE(Vehicle vehicle)l
extern _native64(0x52F357A30698BCCE) bool IS_VEHICLE_A_CONVERTIBLE(Vehicle vehicle, bool p1)l
extern _native64(0xBE4C854FFDB6EEBE) bool TRANSFORM_TO_SUBMARINE(Vehicle vehicle, bool noAnimation)l
extern _native64(0x2A69FFD1B42BFF9E) void TRANSFORM_TO_CAR(Vehicle vehicle, bool noAnimation)l
extern _native64(0xA77DC70BD689A1E5) bool IS_VEHICLE_IN_SUBMARINE_MODE(Vehicle vehicle)l
extern _native64(0x2959F696AE390A99) bool IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle)l
extern _native64(0xA1DD317EA8FD4F29) void SET_VEHICLE_DAMAGE(Vehicle vehicle, float xOffset, float yOffset, float zOffset, float damage, float radius, bool focusOnModel)l
extern _native64(0x35BB21DE06784373) void SET_VEHICLE_OCCUPANTS_TAKE_EXPLOSIVE_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0xC45D23BAF168AAB8) float GET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle)l
extern _native64(0x45F6D8EEF34ABEF1) void SET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle, float health)l
extern _native64(0x2A86A0475B6A1434) void SET_PLANE_ENGINE_HEALTH(Vehicle vehicle, float health)l
extern _native64(0x7D5DABE888D2D074) float GET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle)l
extern _native64(0x70DB57649FA8D0D8) void SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle, float health)l
extern _native64(0x679BE1DAF71DA874) bool IS_VEHICLE_STUCK_TIMER_UP(Vehicle vehicle, int p1, int ms)l
extern _native64(0xD7591B0065AFAA7A) void RESET_VEHICLE_STUCK_TIMER(Vehicle vehicle, int nullAttributes)l
extern _native64(0x4C241E39B23DF959) bool IS_VEHICLE_DRIVEABLE(Vehicle vehicle, bool isOnFireCheck)l
extern _native64(0x2B5F9D2AF1F1722D) void SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Vehicle vehicle, bool owned)l
extern _native64(0xFBA550EA44404EE6) void SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(Vehicle vehicle, bool toggle)l
extern _native64(0x9F3F689B814F2599) void SET_VEHICLE_BLIP_THROTTLE_RANDOMLY(Vehicle vehicle, bool p1)l
extern _native64(0x4E74E62E0A97E901) void SET_POLICE_FOCUS_WILL_TRACK_VEHICLE(Vehicle vehicle, bool toggle)l
extern _native64(0x9C8C6504B5B63D2C) void START_VEHICLE_HORN(Vehicle vehicle, int duration, Hash mode, bool forever)l
extern _native64(0x9D44FCCE98450843) void SET_VEHICLE_IN_CAR_MOD_SHOP(Vehicle vehicle, bool toggle)l
extern _native64(0x92F0CF722BC4202F) void SET_VEHICLE_HAS_STRONG_AXLES(Vehicle vehicle, bool toggle)l
extern _native64(0xB215AAC32D25D019) const char* GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Hash modelHash)l
extern _native64(0xF7AF4F159FF99F97) const char* GET_MAKE_NAME_FROM_VEHICLE_MODEL(Hash modelHash)l
extern _native64(0x4EC6CFBC7B2E9536) vector3 GET_VEHICLE_DEFORMATION_AT_POS(Vehicle vehicle, float offsetX, float offsetY, float offsetZ)l
extern _native64(0x60BF608F1B8CD1B6) void SET_VEHICLE_LIVERY(Vehicle vehicle, int livery)l
extern _native64(0x2BB9230590DA5E8A) int GET_VEHICLE_LIVERY(Vehicle vehicle)l
extern _native64(0x87B63E25A529D526) int GET_VEHICLE_LIVERY_COUNT(Vehicle vehicle)l
extern _native64(0xA6D3A8750DC73270) void SET_VEHICLE_LIVERY2(Vehicle vehicle, int livery)l
extern _native64(0x60190048C0764A26) int GET_VEHICLE_LIVERY2(Vehicle vehicle)l
extern _native64(0x5ECB40269053C0D4) int GET_VEHICLE_LIVERY2_COUNT(Vehicle vehicle)l
extern _native64(0x46E571A0E20D01F1) bool IS_VEHICLE_WINDOW_INTACT(Vehicle vehicle, int windowIndex)l
extern _native64(0x11D862A3E977A9EF) bool ARE_ALL_VEHICLE_WINDOWS_INTACT(Vehicle vehicle)l
extern _native64(0x2D34FC3BC4ADB780) bool ARE_ANY_VEHICLE_SEATS_FREE(Vehicle vehicle)l
extern _native64(0x21D2E5662C1F6FED) void RESET_VEHICLE_WHEELS(Vehicle vehicle, bool toggle)l
extern _native64(0xBC74B4BE25EB6C8A) bool IS_HELI_PART_BROKEN(Vehicle vehicle, bool p1, bool p2, bool p3)l
extern _native64(0xE4CB7541F413D2C5) float GET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle)l
extern _native64(0xAE8CE82A4219AC8C) float GET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle)l
extern _native64(0xAC51915D27E4A5F7) float GET_HELI_TAIL_BOOM_HEALTH(Vehicle vehicle)l
extern _native64(0x4056EA1105F5ABD7) void SET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle, float health)l
extern _native64(0xFE205F38AAA58E5B) void SET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle, float health)l
extern _native64(0x3EC8BF18AA453FE9) bool SET_HELI_TAIL_BOOM_CAN_BREAK_OFF(Vehicle vehicle, bool toggle)l
extern _native64(0xBFDF984E2C22B94F) void SET_VEHICLE_NAME_DEBUG(Vehicle vehicle, const char* name)l
extern _native64(0x71B0892EC081D60A) void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0xD565F438137F0E10) void SET_VEHICLE_EXPLODES_ON_EXPLOSION_DAMAGE_AT_ZERO_BODY_HEALTH(Vehicle vehicle, bool toggle)l
extern _native64(0x3441CAD2F2231923) void SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT(Vehicle vehicle, bool toggle)l
extern _native64(0x2B6747FAA9DB9D6B) void SET_VEHICLE_DISABLE_TOWING(Vehicle vehicle, bool toggle)l
extern _native64(0xE43701C36CAFF1A4) bool GET_VEHICLE_HAS_LANDING_GEAR(Vehicle vehicle)l
extern _native64(0xCFC8BE9A5E1FE575) void CONTROL_LANDING_GEAR(Vehicle vehicle, int state)l
extern _native64(0x9B0F3DCA3DB0F4CD) int GET_LANDING_GEAR_STATE(Vehicle vehicle)l
extern _native64(0x61E1DD6125A3EEE6) bool IS_ANY_VEHICLE_NEAR_POINT(float x, float y, float z, float radius)l
extern _native64(0xA6E9FDCB2C76785E) void REQUEST_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)l
extern _native64(0x00689CDE5F7C6787) void REMOVE_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)l
extern _native64(0x1F25887F3C104278) bool IS_VEHICLE_HIGH_DETAIL(Vehicle vehicle)l
extern _native64(0x81A15811460FAB3A) void REQUEST_VEHICLE_ASSET(Hash vehicleHash, int vehicleAsset)l
extern _native64(0x1BBE0523B8DB9A21) bool HAS_VEHICLE_ASSET_LOADED(int vehicleAsset)l
extern _native64(0xACE699C71AB9DEB5) void REMOVE_VEHICLE_ASSET(int vehicleAsset)l
extern _native64(0xFE54B92A344583CA) void SET_VEHICLE_TOW_TRUCK_ARM_POSITION(Vehicle vehicle, float position)l
extern _native64(0x29A16F8D621C4508) void ATTACH_VEHICLE_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle, bool rear, float hookOffsetX, float hookOffsetY, float hookOffsetZ)l
extern _native64(0xC2DB6B6708350ED8) void DETACH_VEHICLE_FROM_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)l
extern _native64(0xD0E9CE05A1E68CD8) bool DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(Vehicle vehicle)l
extern _native64(0x146DF9EC4C4B9FD4) bool IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)l
extern _native64(0xEFEA18DCF10F8F75) Entity GET_ENTITY_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck)l
extern _native64(0x8BA6F76BC53A1493) Entity SET_VEHICLE_AUTOMATICALLY_ATTACHES(Vehicle vehicle, bool p1, any p2)l
extern _native64(0xF8EBCCC96ADB9FB7) void SET_VEHICLE_BULLDOZER_ARM_POSITION(Vehicle vehicle, float position, bool p2)l
extern _native64(0x56B94C6D7127DFBA) void SET_VEHICLE_TANK_TURRET_POSITION(Vehicle vehicle, float position, bool p2)l
extern _native64(0x0581730AB9380412) void SET_VEHICLE_TURRET_TARGET(Vehicle vehicle, bool p1, float x, float y, float z, bool p5)l
extern _native64(0x737E398138550FFF) void SET_VEHICLE_TANK_STATIONARY(Vehicle vehicle, bool p1)l
extern _native64(0x1093408B4B9D1146) void SET_VEHICLE_TURRET_SPEED_THIS_FRAME(Vehicle vehicle, float speed)l
extern _native64(0x32CAEDF24A583345) void DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME(Vehicle vehicle)l
extern _native64(0x30D779DE7C4F6DD3) void SET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle vehicle, float angleRatio)l
extern _native64(0x9AA47FFF660CB932) void SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE(Vehicle vehicle, float angle)l
extern _native64(0xDA62027C8BDB326E) float GET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle plane)l
extern _native64(0xCE2B43770B655F8F) void SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION(Vehicle vehicle, bool toggle)l
extern _native64(0xA4822F1CF23F4810) bool GENERATE_VEHICLE_CREATION_POS_FROM_PATHS(vector3* outVec, any p1, vector3* outVec1, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native64(0xFB8794444A7D60FB) void SET_VEHICLE_BURNOUT(Vehicle vehicle, bool toggle)l
extern _native64(0x1297A88E081430EB) bool IS_VEHICLE_IN_BURNOUT(Vehicle vehicle)l
extern _native64(0x222FF6A823D122E2) void SET_VEHICLE_REDUCE_GRIP(Vehicle vehicle, bool toggle)l
extern _native64(0x6DEE944E1EE90CFB) void SET_VEHICLE_REDUCE_GRIP_LEVEL(Vehicle vehicle, int val)l
extern _native64(0xB5D45264751B7DF0) void SET_VEHICLE_INDICATOR_LIGHTS(Vehicle vehicle, int turnSignal, bool toggle)l
extern _native64(0x92B35082E0B42F66) void SET_VEHICLE_BRAKE_LIGHTS(Vehicle vehicle, bool toggle)l
extern _native64(0x5815BD2763178DF4) void SET_VEHICLE_TAIL_LIGHTS(Vehicle vehicle, bool toggle)l
extern _native64(0x684785568EF26A22) void SET_VEHICLE_HANDBRAKE(Vehicle vehicle, bool toggle)l
extern _native64(0xE4E2FD323574965C) void SET_VEHICLE_BRAKE(Vehicle vehicle, bool toggle)l
extern _native64(0x48ADC8A773564670) void INSTANTLY_FILL_VEHICLE_POPULATION()l
extern _native64(0x91D6DD290888CBAB) bool HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED()l
extern _native64(0x51DB102F4A3BA5E0) void NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL(bool toggle)l
extern _native64(0xA4A9A4C40E615885) void NETWORK_CAP_EMPTY_CROWDING_VEHICLES_REMOVAL(int p0)l
extern _native64(0x1CDD6BADC297830D) bool GET_VEHICLE_TRAILER_VEHICLE(Vehicle vehicle, Vehicle* trailer)l
extern _native64(0x80D9D32636369C92) Vehicle _GET_VEHICLE_TRAILER_PARENT_VEHICLE(Vehicle trailer)l
extern _native64(0xCAC66558B944DA67) void SET_VEHICLE_USES_LARGE_REAR_RAMP(Vehicle vehicle, bool toggle)l
extern _native64(0x09606148B6C71DEF) void SET_VEHICLE_RUDDER_BROKEN(Vehicle vehicle, bool toggle)l
extern _native64(0x1A78AD3D8240536F) void SET_CONVERTIBLE_ROOF_LATCH_STATE(Vehicle vehicle, bool state)l
extern _native64(0x53AF99BAA671CA47) float GET_VEHICLE_ESTIMATED_MAX_SPEED(Vehicle vehicle)l
extern _native64(0xAD7E85FC227197C4) float GET_VEHICLE_MAX_BRAKING(Vehicle vehicle)l
extern _native64(0xA132FB5370554DB0) float GET_VEHICLE_MAX_TRACTION(Vehicle vehicle)l
extern _native64(0x5DD35C8D074E57AE) float GET_VEHICLE_ACCELERATION(Vehicle vehicle)l
extern _native64(0xF417C2502FFFED43) float GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(Hash modelHash)l
extern _native64(0xDC53FD41B4ED944C) float GET_VEHICLE_MODEL_MAX_BRAKING(Hash modelHash)l
extern _native64(0xBFBA3BA79CFF7EBF) float GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS(Hash modelHash)l
extern _native64(0x539DE94D44FDFD0D) float GET_VEHICLE_MODEL_MAX_TRACTION(Hash modelHash)l
extern _native64(0x8C044C5C84505B6A) float GET_VEHICLE_MODEL_ACCELERATION(Hash modelHash)l
extern _native64(0x53409B5163D5B846) float GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS(Hash modelHash)l
extern _native64(0xC6AD107DDC9054CC) float GET_FLYING_VEHICLE_MODEL_AGILITY(Hash modelHash)l
extern _native64(0x5AA3F878A178C4FC) float GET_BOAT_VEHICLE_MODEL_AGILITY(Hash modelHash)l
extern _native64(0x00C09F246ABEDD82) float GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED(int vehicleClass)l
extern _native64(0xDBC86D85C5059461) float GET_VEHICLE_CLASS_MAX_TRACTION(int vehicleClass)l
extern _native64(0x4F930AD022D6DE3B) float GET_VEHICLE_CLASS_MAX_AGILITY(int vehicleClass)l
extern _native64(0x2F83E7E45D9EA7AE) float GET_VEHICLE_CLASS_MAX_ACCELERATION(int vehicleClass)l
extern _native64(0x4BF54C16EC8FEC03) float GET_VEHICLE_CLASS_MAX_BRAKING(int vehicleClass)l
extern _native64(0x2CE544C68FB812A0) int ADD_ROAD_NODE_SPEED_ZONE(float x, float y, float z, float radius, float speed, bool p5)l
extern _native64(0x1033371FC8E842A7) bool REMOVE_ROAD_NODE_SPEED_ZONE(int speedzone)l
extern _native64(0x87E7F24270732CB1) void OPEN_BOMB_BAY_DOORS(Vehicle vehicle)l
extern _native64(0x3556041742A0DC74) void CLOSE_BOMB_BAY_DOORS(Vehicle vehicle)l
extern _native64(0xD0917A423314BBA8) bool GET_ARE_BOMB_BAY_DOORS_OPEN(Vehicle aircraft)l
extern _native64(0xC0F97FCE55094987) bool IS_VEHICLE_SEARCHLIGHT_ON(Vehicle vehicle)l
extern _native64(0x14E85C5EE7A4D542) void SET_VEHICLE_SEARCHLIGHT(Vehicle heli, bool toggle, bool canBeUsedByAI)l
extern _native64(0x99015ED7DBEA5113) bool DOES_VEHICLE_HAVE_SEARCHLIGHT(Vehicle vehicle)l
extern _native64(0x639431E895B9AA57) bool IS_ENTRY_POINT_FOR_SEAT_CLEAR(Ped ped, Vehicle vehicle, int seatIndex, bool side, bool onEnter)l
extern _native64(0xC0572928C0ABFDA3) vector3 GET_ENTRY_POINT_POSITION(Vehicle vehicle, int doorId)l
extern _native64(0x30785D90C956BF35) bool CAN_SHUFFLE_SEAT(Vehicle vehicle, int seatIndex)l
extern _native64(0x33F2E3FE70EAAE1D) int GET_NUM_MOD_KITS(Vehicle vehicle)l
extern _native64(0x1F2AA07F00B3217A) void SET_VEHICLE_MOD_KIT(Vehicle vehicle, int modKit)l
extern _native64(0x6325D1A044AE510D) int GET_VEHICLE_MOD_KIT(Vehicle vehicle)l
extern _native64(0xFC058F5121E54C32) int GET_VEHICLE_MOD_KIT_TYPE(Vehicle vehicle)l
extern _native64(0xB3ED1BFB4BE636DC) int GET_VEHICLE_WHEEL_TYPE(Vehicle vehicle)l
extern _native64(0x487EB21CC7295BA1) void SET_VEHICLE_WHEEL_TYPE(Vehicle vehicle, int WheelType)l
extern _native64(0xA551BE18C11A476D) int GET_NUM_MOD_COLORS(int paintType, bool p1)l
extern _native64(0x43FEB945EE7F85B8) void SET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int paintType, int color, int pearlescentColor)l
extern _native64(0x816562BADFDEC83E) void SET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int paintType, int color)l
extern _native64(0xE8D65CA700C9A693) void GET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int* paintType, int* color, int* pearlescentColor)l
extern _native64(0x81592BE4E3878728) void GET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int* paintType, int* color)l
extern _native64(0xB45085B721EFD38C) const char* GET_VEHICLE_MOD_COLOR_1_NAME(Vehicle vehicle, bool p1)l
extern _native64(0x4967A516ED23A5A1) const char* GET_VEHICLE_MOD_COLOR_2_NAME(Vehicle vehicle)l
extern _native64(0x9A83F5F9963775EF) bool HAVE_VEHICLE_MODS_STREAMED_IN(Vehicle vehicle)l
extern _native64(0x00834EAC4A96E010) bool IS_VEHICLE_MOD_GEN9_EXCLUSIVE(Vehicle vehicle, int modType, int modIndex)l
extern _native64(0x6AF0636DDEDCB6DD) void SET_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex, bool customTires)l
extern _native64(0x772960298DA26FDB) int GET_VEHICLE_MOD(Vehicle vehicle, int modType)l
extern _native64(0xB3924ECD70E095DC) int GET_VEHICLE_MOD_VARIATION(Vehicle vehicle, int modType)l
extern _native64(0xE38E9162A2500646) int GET_NUM_VEHICLE_MODS(Vehicle vehicle, int modType)l
extern _native64(0x92D619E420858204) void REMOVE_VEHICLE_MOD(Vehicle vehicle, int modType)l
extern _native64(0x2A1F4F37F95BAD08) void TOGGLE_VEHICLE_MOD(Vehicle vehicle, int modType, bool toggle)l
extern _native64(0x84B233A8C8FC8AE7) bool IS_TOGGLE_MOD_ON(Vehicle vehicle, int modType)l
extern _native64(0x8935624F8C5592CC) const char* GET_MOD_TEXT_LABEL(Vehicle vehicle, int modType, int modValue)l
extern _native64(0x51F0FEB9F6AE98C0) const char* GET_MOD_SLOT_NAME(Vehicle vehicle, int modType)l
extern _native64(0xB4C7A93837C91A1F) const char* GET_LIVERY_NAME(Vehicle vehicle, int liveryIndex)l
extern _native64(0x90A38E9838E0A8C1) int GET_VEHICLE_MOD_MODIFIER_VALUE(Vehicle vehicle, int modType, int modIndex)l
extern _native64(0x4593CF82AA179706) Hash GET_VEHICLE_MOD_IDENTIFIER_HASH(Vehicle vehicle, int modType, int modIndex)l
extern _native64(0x758F49C24925568A) void PRELOAD_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex)l
extern _native64(0x06F43E5175EB6D96) bool HAS_PRELOAD_MODS_FINISHED(Vehicle vehicle)l
extern _native64(0x445D79F995508307) void RELEASE_PRELOAD_MODS(Vehicle vehicle)l
extern _native64(0xB5BA80F839791C0F) void SET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int r, int g, int b)l
extern _native64(0xB635392A4938B3C3) void GET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x57C51E6BAD752696) void SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int tint)l
extern _native64(0x0EE21293DAD47C95) int GET_VEHICLE_WINDOW_TINT(Vehicle vehicle)l
extern _native64(0x9D1224004B3A6707) int GET_NUM_VEHICLE_WINDOW_TINTS()l
extern _native64(0xF3CC740D36221548) void GET_VEHICLE_COLOR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0xEEBFC7A7EFDC35B4) int GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET(Vehicle vehicle)l
extern _native64(0xE495D1EF4C91FD20) Hash GET_VEHICLE_CAUSE_OF_DESTRUCTION(Vehicle vehicle)l
extern _native64(0x5EE5632F47AE9695) void OVERRIDE_PLANE_DAMAGE_THREHSOLD(Vehicle vehicle, float health)l
extern _native64(0x5EF77C9ADD3B11A3) bool GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)l
extern _native64(0xA7ECB73355EB2F20) bool GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)l
extern _native64(0xEC69ADF931AAE0C3) bool GET_BOTH_VEHICLE_HEADLIGHTS_DAMAGED(Vehicle vehicle)l
extern _native64(0x93A3996368C94158) void MODIFY_VEHICLE_TOP_SPEED(Vehicle vehicle, float value)l
extern _native64(0xBAA045B4E42F3C06) void SET_VEHICLE_MAX_SPEED(Vehicle vehicle, float speed)l
extern _native64(0x1CF38D529D7441D9) void SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP(Vehicle vehicle, bool toggle)l
extern _native64(0x1F9FB66F3A3842D2) void SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING(Vehicle vehicle, bool p1)l
extern _native64(0x59C3757B3B7408E8) void SET_PEDS_CAN_FALL_OFF_THIS_VEHICLE_FROM_LARGE_FALL_DAMAGE(Vehicle vehicle, bool toggle, float p2)l
extern _native64(0x54B0F614960F4A5F) int ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native64(0xE30524E1871F481D) void REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA(int p0)l
extern _native64(0x291E373D483E7EE7) bool IS_ANY_PED_RAPPELLING_FROM_HELI(Vehicle vehicle)l
extern _native64(0xB59E4BD37AE292DB) void SET_VEHICLE_CHEAT_POWER_INCREASE(Vehicle vehicle, float value)l
extern _native64(0x0AD9E8F87FF7C16F) void SET_VEHICLE_INFLUENCES_WANTED_LEVEL(any p0, bool p1)l
extern _native64(0xF7EC25A3EBEEC726) void SET_VEHICLE_IS_WANTED(Vehicle vehicle, bool state)l
extern _native64(0xF488C566413B4232) void SWING_BOAT_BOOM_TO_RATIO(Vehicle vehicle, float ratio)l
extern _native64(0xC1F981A6F74F0C23) void SWING_BOAT_BOOM_FREELY(Vehicle vehicle, bool toggle)l
extern _native64(0x0F3B4D4E43177236) void ALLOW_BOAT_BOOM_TO_ANIMATE(Vehicle vehicle, bool toggle)l
extern _native64(0x6636C535F6CC2725) float GET_BOAT_BOOM_POSITION_RATIO(Vehicle vehicle)l
extern _native64(0x23428FC53C60919C) void DISABLE_PLANE_AILERON(Vehicle vehicle, bool p1, bool p2)l
extern _native64(0xAE31E7DF9B5B132E) bool GET_IS_VEHICLE_ENGINE_RUNNING(Vehicle vehicle)l
extern _native64(0x1D97D1E3A70A649F) void SET_VEHICLE_USE_ALTERNATE_HANDLING(Vehicle vehicle, bool toggle)l
extern _native64(0x9CFA4896C3A53CBB) void SET_BIKE_ON_STAND(Vehicle vehicle, float x, float y)l
extern _native64(0xAB04325045427AAE) void SET_VEHICLE_NOT_STEALABLE_AMBIENTLY(Vehicle vehicle, bool p1)l
extern _native64(0xCFD778E7904C255E) void LOCK_DOORS_WHEN_NO_LONGER_NEEDED(Vehicle vehicle)l
extern _native64(0xACFB2463CC22BED2) void SET_LAST_DRIVEN_VEHICLE(Vehicle vehicle)l
extern _native64(0xB2D06FAEDE65B577) Vehicle GET_LAST_DRIVEN_VEHICLE()l
extern _native64(0xE01903C47C7AC89E) void CLEAR_LAST_DRIVEN_VEHICLE()l
extern _native64(0x02398B627547189C) void SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG(Vehicle vehicle, bool toggle)l
extern _native64(0xB893215D8D4C015B) void SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN(Vehicle plane, int height)l
extern _native64(0x93AE6A61BE015BF1) void SET_VEHICLE_LOD_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native64(0x428BACCDF5E26EAD) void SET_VEHICLE_CAN_SAVE_IN_GARAGE(Vehicle vehicle, bool toggle)l
extern _native64(0x42A4BEB35D372407) int GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS(Vehicle vehicle)l
extern _native64(0x2C8CBFE1EA5FC631) int GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS(Vehicle vehicle)l
extern _native64(0x4D9D109F63FEE1D4) void SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET(any p0, bool p1)l
extern _native64(0x279D50DE5652D935) void SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS(Vehicle vehicle, bool toggle)l
extern _native64(0xE44A982368A4AF23) void COPY_VEHICLE_DAMAGES(Vehicle sourceVehicle, Vehicle targetVehicle)l
extern _native64(0xF25E02CB9C5818F8) void DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS()l
extern _native64(0xBC3CCA5844452B06) void SET_LIGHTS_CUTOFF_DISTANCE_TWEAK(float distance)l
extern _native64(0x74CD9A9327A282EA) void SET_VEHICLE_SHOOT_AT_TARGET(Ped driver, Entity entity, float xTarget, float yTarget, float zTarget)l
extern _native64(0x8F5EBAB1F260CFCE) bool GET_VEHICLE_LOCK_ON_TARGET(Vehicle vehicle, Entity* entity)l
extern _native64(0x97CE68CB032583F0) void SET_FORCE_HD_VEHICLE(Vehicle vehicle, bool toggle)l
extern _native64(0x182F266C2D9E2BEB) void SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS(Vehicle vehicle, float p1)l
extern _native64(0x9CCC9525BF2408E0) int GET_VEHICLE_PLATE_TYPE(Vehicle vehicle)l
extern _native64(0x64473AEFDCF47DCA) void TRACK_VEHICLE_VISIBILITY(Vehicle vehicle)l
extern _native64(0xAA0A52D24FB98293) bool IS_VEHICLE_VISIBLE(Vehicle vehicle)l
extern _native64(0x89F149B6131E57DA) void SET_VEHICLE_GRAVITY(Vehicle vehicle, bool toggle)l
extern _native64(0xE6C0C80B8C867537) void SET_ENABLE_VEHICLE_SLIPSTREAMING(bool toggle)l
extern _native64(0xF051D9BFB6BA39C0) void SET_VEHICLE_SLIPSTREAMING_SHOULD_TIME_OUT(bool toggle)l
extern _native64(0x36492C2F0D134C56) float GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM(Vehicle vehicle)l
extern _native64(0x48C633E94A8142A7) bool IS_VEHICLE_PRODUCING_SLIP_STREAM(Vehicle vehicle)l
extern _native64(0x06582AFF74894C75) void SET_VEHICLE_INACTIVE_DURING_PLAYBACK(Vehicle vehicle, bool toggle)l
extern _native64(0xDFFCEF48E511DB48) void SET_VEHICLE_ACTIVE_DURING_PLAYBACK(Vehicle vehicle, bool toggle)l
extern _native64(0x8D474C8FAEFF6CDE) bool IS_VEHICLE_SPRAYABLE(Vehicle vehicle)l
extern _native64(0x983765856F2564F9) void SET_VEHICLE_ENGINE_CAN_DEGRADE(Vehicle vehicle, bool toggle)l
extern _native64(0xF0E4BA16D1DB546C) void DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle, int p1, int p2)l
extern _native64(0xF87D9F2301F7D206) void ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle)l
extern _native64(0x4198AB0022B15F87) bool IS_PLANE_LANDING_GEAR_INTACT(Vehicle plane)l
extern _native64(0x755D6D5267CBBD7E) bool ARE_PLANE_PROPELLERS_INTACT(Vehicle plane)l
extern _native64(0x4C815EB175086F84) bool SET_PLANE_PROPELLER_HEALTH(Vehicle plane, float health)l
extern _native64(0x0CDDA42F9E360CA6) void SET_VEHICLE_CAN_DEFORM_WHEELS(Vehicle vehicle, bool toggle)l
extern _native64(0x4AF9BD80EEBEB453) bool IS_VEHICLE_STOLEN(Vehicle vehicle)l
extern _native64(0x67B2C79AA7FF5738) void SET_VEHICLE_IS_STOLEN(Vehicle vehicle, bool isStolen)l
extern _native64(0xAD2D28A1AFDFF131) void SET_PLANE_TURBULENCE_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native64(0x5991A01434CE9677) bool ARE_WINGS_OF_PLANE_INTACT(Vehicle plane)l
extern _native64(0xB264C4D2F2B0A78B) void ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS(Vehicle vehicle)l
extern _native64(0x0E21D3DF1051399D) void DETACH_VEHICLE_FROM_CARGOBOB(Vehicle vehicle, Vehicle cargobob)l
extern _native64(0xADF7BE450512C12F) bool DETACH_VEHICLE_FROM_ANY_CARGOBOB(Vehicle vehicle)l
extern _native64(0xAF03011701811146) bool DETACH_ENTITY_FROM_CARGOBOB(Vehicle cargobob, Entity entity)l
extern _native64(0xD40148F22E81A1D9) bool IS_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicleAttached)l
extern _native64(0x873B82D42AC2B9E5) Vehicle GET_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob)l
extern _native64(0x99093F60746708CA) Entity GET_ENTITY_ATTACHED_TO_CARGOBOB(any p0)l
extern _native64(0x4127F1D84E347769) void ATTACH_VEHICLE_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicle, int p2, float x, float y, float z)l
extern _native64(0xA1DD82F3CCF9A01E) void ATTACH_ENTITY_TO_CARGOBOB(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x571FEB383F629926) void SET_CARGOBOB_FORCE_DONT_DETACH_VEHICLE(Vehicle cargobob, bool toggle)l
extern _native64(0x1F34B0626C594380) void SET_CARGOBOB_EXCLUDE_FROM_PICKUP_ENTITY(any p0, any p1)l
extern _native64(0x2C1D8B3B19E517CC) bool CAN_CARGOBOB_PICK_UP_ENTITY(any p0, any p1)l
extern _native64(0xCBDB9B923CACC92D) vector3 GET_ATTACHED_PICK_UP_HOOK_POSITION(Vehicle cargobob)l
extern _native64(0x1821D91AD4B56108) bool DOES_CARGOBOB_HAVE_PICK_UP_ROPE(Vehicle cargobob)l
extern _native64(0x7BEB0C7A235F6F3B) void CREATE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob, int state)l
extern _native64(0x9768CF648F54C804) void REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob)l
extern _native64(0x877C1EAEAC531023) void SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB(Vehicle cargobob, float length1, float length2, bool p3)l
extern _native64(0xC0ED6438E6D39BA8) void SET_PICKUP_ROPE_LENGTH_WITHOUT_CREATING_ROPE_FOR_CARGOBOB(any p0, any p1, any p2)l
extern _native64(0xCF1182F682F65307) void SET_CARGOBOB_PICKUP_ROPE_DAMPING_MULTIPLIER(any p0, any p1)l
extern _native64(0x0D5F65A8F4EBDAB5) void SET_CARGOBOB_PICKUP_ROPE_TYPE(any p0, any p1)l
extern _native64(0x6E08BF5B3722BAC9) bool DOES_CARGOBOB_HAVE_PICKUP_MAGNET(Vehicle cargobob)l
extern _native64(0x9A665550F8DA349B) void SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(Vehicle cargobob, bool isActive)l
extern _native64(0xBCBFCD9D1DAC19E2) void SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(Vehicle cargobob, float strength)l
extern _native64(0xA17BAD153B51547E) void SET_CARGOBOB_PICKUP_MAGNET_FALLOFF(Vehicle cargobob, float p1)l
extern _native64(0x66979ACF5102FD2F) void SET_CARGOBOB_PICKUP_MAGNET_REDUCED_STRENGTH(Vehicle cargobob, float p1)l
extern _native64(0x6D8EAC07506291FB) void SET_CARGOBOB_PICKUP_MAGNET_REDUCED_FALLOFF(Vehicle cargobob, float p1)l
extern _native64(0xED8286F71A819BAA) void SET_CARGOBOB_PICKUP_MAGNET_PULL_STRENGTH(Vehicle cargobob, float p1)l
extern _native64(0x685D5561680D088B) void SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH(Vehicle vehicle, float p1)l
extern _native64(0xE301BD63E9E13CF0) void SET_CARGOBOB_PICKUP_MAGNET_SET_TARGETED_MODE(Vehicle vehicle, Vehicle cargobob)l
extern _native64(0x9BDDC73CC6A115D4) void SET_CARGOBOB_PICKUP_MAGNET_SET_AMBIENT_MODE(Vehicle vehicle, bool p1, bool p2)l
extern _native64(0x56EB5E94318D3FB6) void SET_CARGOBOB_PICKUP_MAGNET_ENSURE_PICKUP_ENTITY_UPRIGHT(Vehicle vehicle, bool p1)l
extern _native64(0x25ECB9F8017D98E0) bool DOES_VEHICLE_HAVE_WEAPONS(Vehicle vehicle)l
extern _native64(0x2C4A1590ABF43E8B) void SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY(Vehicle vehicle, bool p1)l
extern _native64(0xF4FC6A6F67D8D856) void DISABLE_VEHICLE_WEAPON(bool disabled, Hash weaponHash, Vehicle vehicle, Ped owner)l
extern _native64(0x563B65A643ED072E) bool IS_VEHICLE_WEAPON_DISABLED(Hash weaponHash, Vehicle vehicle, Ped owner)l
extern _native64(0xE05DD0E9707003A3) void SET_VEHICLE_USED_FOR_PILOT_SCHOOL(Vehicle vehicle, bool toggle)l
extern _native64(0x21115BCD6E44656A) void SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION(Vehicle vehicle, bool toggle)l
extern _native64(0x29439776AAA00A62) int GET_VEHICLE_CLASS(Vehicle vehicle)l
extern _native64(0xDEDF1C8BD47C2200) int GET_VEHICLE_CLASS_FROM_NAME(Hash modelHash)l
extern _native64(0xBCDF8BAF56C87B6A) void SET_PLAYERS_LAST_VEHICLE(Vehicle vehicle)l
extern _native64(0x300504B23BD3B711) void SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(Vehicle vehicle, bool toggle)l
extern _native64(0xE5810AC70602F2F5) void SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR(Vehicle vehicle, float p1)l
extern _native64(0x068F64F2470F9656) void SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP(Vehicle vehicle, bool toggle)l
extern _native64(0xB8FBC8B1330CA9B4) void SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED(Vehicle vehicle, bool toggle)l
extern _native64(0x6A973569BA094650) void SET_VEHICLE_IMPATIENCE_TIMER(Vehicle vehicle, any p1)l
extern _native64(0x10655FAB9915623D) void SET_VEHICLE_HANDLING_OVERRIDE(Vehicle vehicle, Hash hash)l
extern _native64(0x79DF7E806202CE01) void SET_VEHICLE_EXTENDED_REMOVAL_RANGE(Vehicle vehicle, int range)l
extern _native64(0x9007A2F21DC108D4) void SET_VEHICLE_STEERING_BIAS_SCALAR(any p0, float p1)l
extern _native64(0x6E0859B530A365CC) void SET_HELI_CONTROL_LAGGING_RATE_SCALAR(Vehicle helicopter, float multiplier)l
extern _native64(0x1837AF7C627009BA) void SET_VEHICLE_FRICTION_OVERRIDE(Vehicle vehicle, float friction)l
extern _native64(0xA37B9A517B133349) void SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(Vehicle vehicle, bool toggle)l
extern _native64(0xF78F94D60248C737) bool ARE_PLANE_CONTROL_PANELS_INTACT(Vehicle vehicle, bool p1)l
extern _native64(0xA46413066687A328) void SET_VEHICLE_CEILING_HEIGHT(Vehicle vehicle, float height)l
extern _native64(0x5E569EC46EC21CAE) void SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER(Vehicle vehicle, bool toggle)l
extern _native64(0x6D6AF961B72728AE) void CLEAR_VEHICLE_ROUTE_HISTORY(Vehicle vehicle)l
extern _native64(0x956B409B984D9BF7) Vehicle DOES_VEHICLE_EXIST_WITH_DECORATOR(const char* decorator)l
extern _native64(0x41062318F23ED854) void SET_VEHICLE_AI_CAN_USE_EXCLUSIVE_SEATS(Vehicle vehicle, bool toggle)l
extern _native64(0xB5C51B5502E85E83) void SET_VEHICLE_EXCLUSIVE_DRIVER(Vehicle vehicle, Ped ped, int index)l
extern _native64(0xB09D25E77C33EB3F) bool IS_PED_EXCLUSIVE_DRIVER_OF_VEHICLE(Ped ped, Vehicle vehicle, int* outIndex)l
extern _native64(0x500873A45724C863) void DISABLE_INDIVIDUAL_PLANE_PROPELLER(Vehicle vehicle, int propeller)l
extern _native64(0xB055A34527CB8FD7) void SET_VEHICLE_FORCE_AFTERBURNER(Vehicle vehicle, bool toggle)l
extern _native64(0x1087BC8EC540DAEB) void SET_DONT_PROCESS_VEHICLE_GLASS(Vehicle vehicle, bool toggle)l
extern _native64(0x4AD280EB48B2D8E6) void SET_DISABLE_WANTED_CONES_RESPONSE(Vehicle vehicle, bool toggle)l
extern _native64(0xB68CFAF83A02768D) void SET_USE_DESIRED_Z_CRUISE_SPEED_FOR_LANDING(Vehicle vehicle, bool toggle)l
extern _native64(0x0205F5365292D2EB) void SET_ARRIVE_DISTANCE_OVERRIDE_FOR_VEHICLE_PERSUIT_ATTACK(Vehicle vehicle, float p1)l
extern _native64(0xCF9159024555488C) void SET_VEHICLE_READY_FOR_CLEANUP(any p0)l
extern _native64(0xF796359A959DF65D) void SET_DISTANT_CARS_ENABLED(bool toggle)l
extern _native64(0x8E0A582209A62695) void SET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int r, int g, int b)l
extern _native64(0xB93B2867F7B479D1) void SET_VEHICLE_NEON_INDEX_COLOUR(Vehicle vehicle, int index)l
extern _native64(0x7619EEE8C886757F) void GET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x2AA720E4287BF269) void SET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index, bool toggle)l
extern _native64(0x8C4B92553E4766A5) bool GET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index)l
extern _native64(0x35E0654F4BAD7971) void SET_AMBIENT_VEHICLE_NEON_ENABLED(bool p0)l
extern _native64(0x83F813570FF519DE) void SUPPRESS_NEONS_ON_VEHICLE(Vehicle vehicle, bool toggle)l
extern _native64(0xB088E9A47AE6EDD5) void SET_DISABLE_SUPERDUMMY(Vehicle vehicle, bool p1)l
extern _native64(0xDBA3C090E3D74690) void REQUEST_VEHICLE_DIAL(Vehicle vehicle)l
extern _native64(0xF271147EB7B40F12) float GET_VEHICLE_BODY_HEALTH(Vehicle vehicle)l
extern _native64(0xB77D05AC8C78AADB) void SET_VEHICLE_BODY_HEALTH(Vehicle vehicle, float value)l
extern _native64(0xDF7E3EEB29642C38) void GET_VEHICLE_SIZE(Vehicle vehicle, vector3* out1, vector3* out2)l
extern _native64(0x53952FD2BAA19F17) float GET_FAKE_SUSPENSION_LOWERING_AMOUNT(Vehicle vehicle)l
extern _native64(0x84FD40F56075E816) void SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(float multiplier)l
extern _native64(0x92922A607497B14D) int GET_NUMBER_OF_VEHICLE_DOORS(Vehicle vehicle)l
extern _native64(0x28B18377EB6E25F6) void SET_HYDRAULICS_CONTROL(Vehicle vehicle, bool toggle)l
extern _native64(0xA7DCDF4DED40A8F4) void SET_CAN_ADJUST_GROUND_CLEARANCE(Vehicle vehicle, bool p1)l
extern _native64(0xB8EF61207C2393A9) float GET_VEHICLE_HEALTH_PERCENTAGE(Vehicle vehicle, float maxEngineHealth, float maxPetrolTankHealth, float maxBodyHealth, float maxMainRotorHealth, float maxTailRotorHealth, float maxUnkHealth)l
extern _native64(0xD4C4642CB7F50B5D) bool GET_VEHICLE_IS_MERCENARY(Vehicle vehicle)l
extern _native64(0xC361AA040D6637A8) void SET_VEHICLE_BROKEN_PARTS_DONT_AFFECT_AI_HANDLING(Vehicle vehicle, bool p1)l
extern _native64(0x99C82F8A139F3E4E) void SET_VEHICLE_KERS_ALLOWED(Vehicle vehicle, bool toggle)l
extern _native64(0x50634E348C8D44EF) bool GET_VEHICLE_HAS_KERS(Vehicle vehicle)l
extern _native64(0xE16142B94664DEFD) void SET_PLANE_RESIST_TO_EXPLOSION(Vehicle vehicle, bool toggle)l
extern _native64(0x8074CC1886802912) void SET_HELI_RESIST_TO_EXPLOSION(Vehicle vehicle, bool toggle)l
extern _native64(0x26D99D5A82FD18E8) void SET_DISABLE_BMX_EXTRA_TRICK_FORCES(any p0)l
extern _native64(0x84EA99C62CB3EF0C) void SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId, float value)l
extern _native64(0x0BB5CBDDD0F25AE3) float GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId)l
extern _native64(0x1201E8A3290A3B98) void SET_CAN_USE_HYDRAULICS(Vehicle vehicle, bool toggle)l
extern _native64(0x8EA86DF356801C7D) void SET_HYDRAULIC_VEHICLE_STATE(Vehicle vehicle, int state)l
extern _native64(0xC24075310A8B9CD1) void SET_HYDRAULIC_WHEEL_STATE(Vehicle vehicle, int wheelId, int state, float value, any p4)l
extern _native64(0x5BA68A0840D546AC) bool HAS_VEHICLE_PETROLTANK_SET_ON_FIRE_BY_ENTITY(any p0, any p1)l
extern _native64(0x4419966C9936071A) void CLEAR_VEHICLE_PETROLTANK_FIRE_CULPRIT(Vehicle vehicle)l
extern _native64(0x870B8B7A766615C8) void SET_VEHICLE_BOBBLEHEAD_VELOCITY(float x, float y, float p2)l
extern _native64(0x8533CAFDE1F0F336) bool GET_VEHICLE_IS_DUMMY(any p0)l
extern _native64(0x4E20D2A627011E8E) bool SET_VEHICLE_DAMAGE_SCALE(Vehicle vehicle, float p1)l
extern _native64(0x45A561A9421AB6AD) bool SET_VEHICLE_WEAPON_DAMAGE_SCALE(Vehicle vehicle, float multiplier)l
extern _native64(0xD4196117AF7BB974) bool SET_DISABLE_DAMAGE_WITH_PICKED_UP_ENTITY(any p0, any p1)l
extern _native64(0xBB2333BB87DDD87F) void SET_VEHICLE_USES_MP_PLAYER_DAMAGE_MULTIPLIER(any p0, any p1)l
extern _native64(0x73561D4425A021A2) void SET_BIKE_EASY_TO_LAND(Vehicle vehicle, bool toggle)l
extern _native64(0x5B91B229243351A8) void SET_INVERT_VEHICLE_CONTROLS(Vehicle vehicle, bool state)l
extern _native64(0x7BBE7FF626A591FE) void SET_SPEED_BOOST_EFFECT_DISABLED(bool disabled)l
extern _native64(0x65B080555EA48149) void SET_SLOW_DOWN_EFFECT_DISABLED(bool disabled)l
extern _native64(0x428AD3E26C8D9EB0) void SET_FORMATION_LEADER(Vehicle vehicle, float x, float y, float z, float p4)l
extern _native64(0xE2F53F172B45EDE1) void RESET_FORMATION_LEADER()l
extern _native64(0xBA91D045575699AD) bool GET_IS_BOAT_CAPSIZED(Vehicle vehicle)l
extern _native64(0x80E3357FDEF45C21) void SET_ALLOW_RAMMING_SOOP_OR_RAMP(any p0, any p1)l
extern _native64(0xEFC13B1CE30D755D) void SET_SCRIPT_RAMP_IMPULSE_SCALE(Vehicle vehicle, float impulseScale)l
extern _native64(0x645F4B6E8499F632) bool GET_IS_DOOR_VALID(Vehicle vehicle, int doorId)l
extern _native64(0xE00F2AB100B76E89) void SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(Vehicle vehicle, float seconds)l
extern _native64(0x36D782F68B309BDA) bool GET_HAS_ROCKET_BOOST(Vehicle vehicle)l
extern _native64(0x3D34E80EED4AE3BE) bool IS_ROCKET_BOOST_ACTIVE(Vehicle vehicle)l
extern _native64(0x81E1552E35DC3839) void SET_ROCKET_BOOST_ACTIVE(Vehicle vehicle, bool active)l
extern _native64(0xDCA174A42133F08C) bool GET_HAS_RETRACTABLE_WHEELS(Vehicle vehicle)l
extern _native64(0x1DA0DA9CB3F0C8BF) bool GET_IS_WHEELS_RETRACTED(Vehicle vehicle)l
extern _native64(0xF660602546D27BA8) void SET_WHEELS_EXTENDED_INSTANTLY(Vehicle vehicle)l
extern _native64(0x5335BE58C083E74E) void SET_WHEELS_RETRACTED_INSTANTLY(Vehicle vehicle)l
extern _native64(0x9078C0C5EF8C19E9) bool GET_CAR_HAS_JUMP(Vehicle vehicle)l
extern _native64(0xF06A16CA55D138D8) void SET_USE_HIGHER_CAR_JUMP(Vehicle vehicle, bool toggle)l
extern _native64(0xB2E0C0D6922D31F2) void SET_CLEAR_FREEZE_WAITING_ON_COLLISION_ONCE_PLAYER_ENTERS(Vehicle vehicle, bool toggle)l
extern _native64(0x44CD1F493DB2A0A6) void SET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex, int capacity)l
extern _native64(0x8181CE2F25CB9BB7) int GET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex)l
extern _native64(0xBC9CFF381338CB4F) bool GET_VEHICLE_HAS_PARACHUTE(Vehicle vehicle)l
extern _native64(0xA916396DF4154EE3) bool GET_VEHICLE_CAN_DEPLOY_PARACHUTE(Vehicle vehicle)l
extern _native64(0x0BFFB028B3DD0A97) void VEHICLE_START_PARACHUTING(Vehicle vehicle, bool active)l
extern _native64(0x3DE51E9C80B116CF) bool IS_VEHICLE_PARACHUTE_DEPLOYED(Vehicle vehicle)l
extern _native64(0x28D034A93FE31BF5) void VEHICLE_SET_RAMP_AND_RAMMING_CARS_TAKE_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0x1BBAC99C0BC53656) void VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE(any p0, any p1)l
extern _native64(0x756AE6E962168A04) void VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY(any p0, any p1)l
extern _native64(0x9D30687C57BAA0BB) void VEHICLE_SET_JET_WASH_FORCE_ENABLED(any p0)l
extern _native64(0x86B4B6212CB8B627) void SET_VEHICLE_WEAPON_CAN_TARGET_OBJECTS(Vehicle vehicle, bool toggle)l
extern _native64(0x41290B40FA63E6DA) void SET_VEHICLE_USE_BOOST_BUTTON_FOR_WHEEL_RETRACT(bool toggle)l
extern _native64(0x4D610C6B56031351) void VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(Vehicle vehicle, Hash modelHash)l
extern _native64(0xA74AD2439468C883) void VEHICLE_SET_PARACHUTE_MODEL_TINT_INDEX(Vehicle vehicle, int textureVariation)l
extern _native64(0x0419B167EE128F33) int VEHICLE_SET_OVERRIDE_EXTENABLE_SIDE_RATIO(any p0, any p1)l
extern _native64(0xF3B0E0AED097A3F5) int VEHICLE_SET_EXTENABLE_SIDE_TARGET_RATIO(any p0, any p1)l
extern _native64(0xD3E51C0AB8C26EEE) int VEHICLE_SET_OVERRIDE_SIDE_RATIO(any p0, any p1)l
extern _native64(0x9B8E1BF04B51F2E8) int GET_ALL_VEHICLES(any* vehsStruct)l
extern _native64(0x72BECCF4B829522E) void SET_CARGOBOB_EXTA_PICKUP_RANGE(any p0, any p1)l
extern _native64(0x66E3AAFACE2D1EB8) void SET_OVERRIDE_VEHICLE_DOOR_TORQUE(any p0, any p1, any p2)l
extern _native64(0x1312DDD8385AEE4E) void SET_WHEELIE_ENABLED(Vehicle vehicle, bool enabled)l
extern _native64(0xEDBC8405B3895CC9) void SET_DISABLE_HELI_EXPLODE_FROM_BODY_DAMAGE(any p0, any p1)l
extern _native64(0x26E13D440E7F6064) void SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_ON_COLLISION(Vehicle vehicle, float value)l
extern _native64(0x2FA2494B47FDD009) void SET_TRAILER_ATTACHMENT_ENABLED(any p0, any p1)l
extern _native64(0xFEB2DDED3509562E) void SET_ROCKET_BOOST_FILL(Vehicle vehicle, float percentage)l
extern _native64(0x544996C0081ABDEB) void SET_GLIDER_ACTIVE(Vehicle vehicle, bool state)l
extern _native64(0x78CEEE41F49F421F) void SET_SHOULD_RESET_TURRET_IN_SCRIPTED_CAMERAS(Vehicle vehicle, bool shouldReset)l
extern _native64(0xAF60E6A2936F982A) void SET_VEHICLE_DISABLE_COLLISION_UPON_CREATION(Vehicle vehicle, bool disable)l
extern _native64(0x430A7631A84C9BE7) void SET_GROUND_EFFECT_REDUCES_DRAG(bool toggle)l
extern _native64(0x75627043C6AA90AD) void SET_DISABLE_MAP_COLLISION(Vehicle vehicle)l
extern _native64(0x8235F1BEAD557629) void SET_DISABLE_PED_STAND_ON_TOP(Vehicle vehicle, bool toggle)l
extern _native64(0x9640E30A7F395E4B) void SET_VEHICLE_DAMAGE_SCALES(Vehicle vehicle, any p1, any p2, any p3, any p4)l
extern _native64(0x0BBB9A7A8FFE931B) void SET_PLANE_SECTION_DAMAGE_SCALE(Vehicle vehicle, any p1, any p2)l
extern _native64(0x94A68DA412C4007D) void SET_HELI_CAN_PICKUP_ENTITY_THAT_HAS_PICK_UP_DISABLED(Vehicle vehicle, bool toggle)l
extern _native64(0xF4B2ED59DEB5D774) void SET_VEHICLE_BOMB_AMMO(Vehicle vehicle, int bombCount)l
extern _native64(0xEA12BD130D7569A1) int GET_VEHICLE_BOMB_AMMO(Vehicle vehicle)l
extern _native64(0x9BDA23BF666F0855) void SET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle, int counterMeasureCount)l
extern _native64(0xF846AA63DF56B804) int GET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle)l
extern _native64(0x0A3F820A9A9A9AC5) void SET_HELI_COMBAT_OFFSET(Vehicle vehicle, float x, float y, float z)l
extern _native64(0x51F30DB60626A20E) bool GET_CAN_VEHICLE_BE_PLACED_HERE(Vehicle vehicle, float x, float y, float z, float rotX, float rotY, float rotZ, int p7, any p8)l
extern _native64(0x97841634EF7DF1D6) void SET_DISABLE_AUTOMATIC_CRASH_TASK(Vehicle vehicle, bool toggle)l
extern _native64(0xD138FA15C9776837) void SET_SPECIAL_FLIGHT_MODE_RATIO(Vehicle vehicle, float ratio)l
extern _native64(0x438B3D7CA026FE91) void SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO(Vehicle vehicle, float targetRatio)l
extern _native64(0xF1211889DF15A763) void SET_SPECIAL_FLIGHT_MODE_ALLOWED(Vehicle vehicle, bool toggle)l
extern _native64(0x2D55FE374D5FDB91) void SET_DISABLE_HOVER_MODE_FLIGHT(Vehicle vehicle, bool toggle)l
extern _native64(0x3A9128352EAC9E85) bool GET_OUTRIGGERS_DEPLOYED(Vehicle vehicle)l
extern _native64(0x8DC9675797123522) vector3 FIND_SPAWN_COORDINATES_FOR_HELI(Ped ped)l
extern _native64(0xB251E0B33E58B424) void SET_DEPLOY_FOLDING_WINGS(Vehicle vehicle, bool deploy, bool p2)l
extern _native64(0xAEF12960FA943792) bool ARE_FOLDING_WINGS_DEPLOYED(Vehicle vehicle)l
extern _native64(0x0C02468829E4AA65) void _SET_DEPLOY_MISSILE_BAYS(Vehicle vehicle, bool deploy)l
extern _native64(0xEA4743874D515F13) bool _ARE_MISSILE_BAYS_DEPLOYED(Vehicle vehicle)l
extern _native64(0xAA653AE61924B0A0) void SET_DIP_STRAIGHT_DOWN_WHEN_CRASHING_PLANE(Vehicle vehicle, bool toggle)l
extern _native64(0xC60060EB0D8AC7B1) void SET_TURRET_HIDDEN(Vehicle vehicle, int index, bool toggle)l
extern _native64(0x70A252F60A3E036B) void SET_HOVER_MODE_WING_RATIO(Vehicle vehicle, float ratio)l
extern _native64(0xE615BB7A7752C76A) void SET_DISABLE_TURRET_MOVEMENT(Vehicle vehicle, int turretId)l
extern _native64(0x887FA38787DE8C72) void SET_FORCE_FIX_LINK_MATRICES(Vehicle vehicle)l
extern _native64(0x498218259FB7C72D) void SET_TRANSFORM_RATE_FOR_ANIMATION(Vehicle vehicle, float transformRate)l
extern _native64(0x41B9FB92EDED32A6) void SET_TRANSFORM_TO_SUBMARINE_USES_ALTERNATE_INPUT(Vehicle vehicle, bool toggle)l
extern _native64(0x36DE109527A2C0C4) void SET_VEHICLE_COMBAT_MODE(bool toggle)l
extern _native64(0x82E0AC411E41A5B4) void SET_VEHICLE_DETONATION_MODE(bool toggle)l
extern _native64(0x99A05839C46CE316) void SET_VEHICLE_SHUNT_ON_STICK(bool toggle)l
extern _native64(0xA2459F72C14E2E8D) bool GET_IS_VEHICLE_SHUNTING(Vehicle vehicle)l
extern _native64(0xE8718FAF591FD224) bool GET_HAS_VEHICLE_BEEN_HIT_BY_SHUNT(Vehicle vehicle)l
extern _native64(0x04F2FA6E234162F7) Vehicle GET_LAST_SHUNT_VEHICLE(Vehicle vehicle)l
extern _native64(0x143921E45EC44D62) void SET_DISABLE_VEHICLE_EXPLOSIONS_DAMAGE(bool toggle)l
extern _native64(0xC8E9B6B71B8E660D) void SET_OVERRIDE_NITROUS_LEVEL(Vehicle vehicle, bool toggle, float level, float power, float rechargeTime, bool disableSound)l
extern _native64(0x2970EAA18FD5E42F) void SET_INCREASE_WHEEL_CRUSH_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0x211E95CE9903940C) void SET_DISABLE_WEAPON_BLADE_FORCES(bool toggle)l
extern _native64(0x5BBCF35BF6E456F7) void SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP(bool toggle)l
extern _native64(0x71AFB258CCED3A27) bool GET_DOES_VEHICLE_HAVE_TOMBSTONE(Vehicle vehicle)l
extern _native64(0xAE71FB656C600587) void HIDE_TOMBSTONE(Vehicle vehicle, bool toggle)l
extern _native64(0x0506ED94363AD905) bool GET_IS_VEHICLE_DISABLED_BY_EMP(Vehicle vehicle)l
extern _native64(0x8F0D5BA1C2CC91D7) void SET_DISABLE_RETRACTING_WEAPON_BLADES(bool toggle)l
extern _native64(0x55EAB010FAEE9380) float GET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex)l
extern _native64(0x74C68EF97645E79D) void SET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex, float health)l
extern _native64(0x6E387895952F4F71) float GET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex)l
extern _native64(0x01894E2EDE923CA2) void SET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier)l
extern _native64(0x392183BB9EA57697) void SET_TYRE_WEAR_RATE_SCALE(Vehicle vehicle, int wheelIndex, float multiplier)l
extern _native64(0xC970D0E0FC31D768) void SET_TYRE_MAXIMUM_GRIP_DIFFERENCE_DUE_TO_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier)l
extern _native64(0xF8B49F5BA7F850E7) void SET_AIRCRAFT_IGNORE_HIGHTMAP_OPTIMISATION(Vehicle vehicle, int p1)l
extern _native64(0x3A375167F5782A65) void SET_REDUCED_SUSPENSION_FORCE(Vehicle vehicle, bool enable)l
extern _native64(0x5AC79C98C5C17F05) void SET_DRIFT_TYRES(Vehicle vehicle, bool toggle)l
extern _native64(0x2F5A72430E78C8D3) bool GET_DRIFT_TYRES_SET(Vehicle vehicle)l
extern _native64(0xEC0C1D4922AF9754) void NETWORK_USE_HIGH_PRECISION_TRAIN_BLENDING(Vehicle vehicle, bool toggle)l
extern _native64(0xEF9D388F8D377F44) void SET_CHECK_FOR_ENOUGH_ROOM_FOR_PED(Vehicle vehicle, bool p1)l
#pragma endregion //}
#pragma region WATER //{
extern _native64(0xF6829842C06AE524) bool GET_WATER_HEIGHT(float x, float y, float z, float* height)l
extern _native64(0x8EE6B53CE13A9794) bool GET_WATER_HEIGHT_NO_WAVES(float x, float y, float z, float* height)l
extern _native64(0xFFA5D878809819DB) bool TEST_PROBE_AGAINST_WATER(float x1, float y1, float z1, float x2, float y2, float z2, vector3* result)l
extern _native64(0x8974647ED222EA5F) int TEST_PROBE_AGAINST_ALL_WATER(float x1, float y1, float z1, float x2, float y2, float z2, int flags, float* waterHeight)l
extern _native64(0x2B3451FA1E3142E2) int TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(float x, float y, float z, int flags, float* waterHeight)l
extern _native64(0xC443FD757C3BA637) void MODIFY_WATER(float x, float y, float radius, float height)l
extern _native64(0xFDBF4CDBC07E1706) int ADD_EXTRA_CALMING_QUAD(float xLow, float yLow, float xHigh, float yHigh, float height)l
extern _native64(0xB1252E3E59A82AAF) void REMOVE_EXTRA_CALMING_QUAD(int calmingQuad)l
extern _native64(0xB96B00E976BE977F) void SET_DEEP_OCEAN_SCALER(float intensity)l
extern _native64(0x2B2A2CC86778B619) float GET_DEEP_OCEAN_SCALER()l
extern _native64(0x547237AA71AB44DE) void SET_CALMED_WAVE_HEIGHT_SCALER(float height)l
extern _native64(0x5E5E99285AE812DB) void RESET_DEEP_OCEAN_SCALER()l
#pragma endregion //}
#pragma region WEAPON //{
extern _native64(0xC8B46D7727D864AA) void ENABLE_LASER_SIGHT_RENDERING(bool toggle)l
extern _native64(0x0DB57B41EC1DB083) Hash GET_WEAPON_COMPONENT_TYPE_MODEL(Hash componentHash)l
extern _native64(0xF46CDC33180FDA94) Hash GET_WEAPONTYPE_MODEL(Hash weaponHash)l
extern _native64(0x4215460B9B8B7FA0) Hash GET_WEAPONTYPE_SLOT(Hash weaponHash)l
extern _native64(0xC3287EE3050FB74C) Hash GET_WEAPONTYPE_GROUP(Hash weaponHash)l
extern _native64(0x6558AC7C17BFEF58) int GET_WEAPON_COMPONENT_VARIANT_EXTRA_COUNT(Hash componentHash)l
extern _native64(0x4D1CB8DC40208A17) Hash GET_WEAPON_COMPONENT_VARIANT_EXTRA_MODEL(Hash componentHash, int extraComponentIndex)l
extern _native64(0xADF692B254977C0C) void SET_CURRENT_PED_WEAPON(Ped ped, Hash weaponHash, bool bForceInHand)l
extern _native64(0x3A87E44BB9A01D54) bool GET_CURRENT_PED_WEAPON(Ped ped, Hash* weaponHash, bool p2)l
extern _native64(0x3B390A939AF0B5FC) Entity GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Ped ped, any p1)l
extern _native64(0x8483E98E8B888AE2) Hash GET_BEST_PED_WEAPON(Ped ped, bool p1)l
extern _native64(0x75C55983C2C39DAA) bool SET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash weaponHash)l
extern _native64(0x1017582BCD3832DC) bool GET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash* weaponHash)l
extern _native64(0x50276EF8172F5F12) void SET_PED_CYCLE_VEHICLE_WEAPONS_ONLY(Ped ped)l
extern _native64(0x475768A975D5AD17) bool IS_PED_ARMED(Ped ped, int typeFlags)l
extern _native64(0x937C71165CF334B3) bool IS_WEAPON_VALID(Hash weaponHash)l
extern _native64(0x8DECB02F88F428BC) bool HAS_PED_GOT_WEAPON(Ped ped, Hash weaponHash, bool p2)l
extern _native64(0xB80CA294F2F26749) bool IS_PED_WEAPON_READY_TO_SHOOT(Ped ped)l
extern _native64(0xEFFED78E9011134D) Hash GET_PED_WEAPONTYPE_IN_SLOT(Ped ped, Hash weaponSlot)l
extern _native64(0x015A522136D7F951) int GET_AMMO_IN_PED_WEAPON(Ped ped, Hash weaponhash)l
extern _native64(0x78F0424C34306220) void ADD_AMMO_TO_PED(Ped ped, Hash weaponHash, int ammo)l
extern _native64(0x14E56BC5B5DB6A19) void SET_PED_AMMO(Ped ped, Hash weaponHash, int ammo, bool p3)l
extern _native64(0x3EDCB0505123623B) void SET_PED_INFINITE_AMMO(Ped ped, bool toggle, Hash weaponHash)l
extern _native64(0x183DADC6AA953186) void SET_PED_INFINITE_AMMO_CLIP(Ped ped, bool toggle)l
extern _native64(0x24C024BA8379A70A) void SET_PED_STUN_GUN_FINITE_AMMO(any p0, any p1)l
extern _native64(0xBF0FD6E56C964FCB) void GIVE_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool isHidden, bool bForceInHand)l
extern _native64(0xB282DC6EBD803C75) void GIVE_DELAYED_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool bForceInHand)l
extern _native64(0xF25DF915FA38C5F3) void REMOVE_ALL_PED_WEAPONS(Ped ped, bool p1)l
extern _native64(0x4899CB088EDF59B8) void REMOVE_WEAPON_FROM_PED(Ped ped, Hash weaponHash)l
extern _native64(0x6F6981D2253C208F) void HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(Ped ped, bool toggle)l
extern _native64(0x0725A4CCFDED9A70) void SET_PED_CURRENT_WEAPON_VISIBLE(Ped ped, bool visible, bool deselectWeapon, bool p3, bool p4)l
extern _native64(0x476AE72C1D19D1A8) void SET_PED_DROPS_WEAPONS_WHEN_DEAD(Ped ped, bool toggle)l
extern _native64(0x2D343D2219CD027A) bool HAS_PED_BEEN_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash, int weaponType)l
extern _native64(0x0E98F88A24C5F4B8) void CLEAR_PED_LAST_WEAPON_DAMAGE(Ped ped)l
extern _native64(0x131D401334815E94) bool HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(Entity entity, Hash weaponHash, int weaponType)l
extern _native64(0xAC678E40BE7C74D2) void CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Entity entity)l
extern _native64(0x6B7513D9966FBEC0) void SET_PED_DROPS_WEAPON(Ped ped)l
extern _native64(0x208A1888007FC0E6) void SET_PED_DROPS_INVENTORY_WEAPON(Ped ped, Hash weaponHash, float xOffset, float yOffset, float zOffset, int ammoCount)l
extern _native64(0xA38DCFFCEA8962FA) int GET_MAX_AMMO_IN_CLIP(Ped ped, Hash weaponHash, bool p2)l
extern _native64(0x2E1202248937775C) bool GET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int* ammo)l
extern _native64(0xDCD2A934D65CB497) bool SET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int ammo)l
extern _native64(0xDC16122C7A20C933) bool GET_MAX_AMMO(Ped ped, Hash weaponHash, int* ammo)l
extern _native64(0x585847C5E4E11709) bool GET_MAX_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int* ammo)l
extern _native64(0x2472622CE1F2D45F) void ADD_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo)l
extern _native64(0x5FD1E1F011E76D7E) void SET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo)l
extern _native64(0x39D22031557946C1) int GET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash)l
extern _native64(0xA4EFEF9440A5B0EF) void SET_PED_AMMO_TO_DROP(Ped ped, int p1)l
extern _native64(0xE620FD3512A04F18) void SET_PICKUP_AMMO_AMOUNT_SCALER(float p0)l
extern _native64(0x7FEAD38B326B9F74) Hash GET_PED_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash)l
extern _native64(0xF489B44DD5AF4BD9) Hash GET_PED_ORIGINAL_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash)l
extern _native64(0x6C4D0409BA1A2BC2) bool GET_PED_LAST_WEAPON_IMPACT_COORD(Ped ped, vector3* coords)l
extern _native64(0xD0D7B1E680ED4A1A) void SET_PED_GADGET(Ped ped, Hash gadgetHash, bool p2)l
extern _native64(0xF731332072F5156C) bool GET_IS_PED_GADGET_EQUIPPED(Ped ped, Hash gadgetHash)l
extern _native64(0x0A6DB4965674D243) Hash GET_SELECTED_PED_WEAPON(Ped ped)l
extern _native64(0xFC4BD125DE7611E4) void EXPLODE_PROJECTILES(Ped ped, Hash weaponHash, bool p2)l
extern _native64(0xFC52E0F37E446528) void REMOVE_ALL_PROJECTILES_OF_TYPE(Hash weaponHash, bool explode)l
extern _native64(0x840F03E9041E2C9C) float GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON(Ped ped)l
extern _native64(0x814C9D19DFD69679) float GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(Ped ped)l
extern _native64(0x717C8481234E3B88) bool HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Ped driver, Vehicle vehicle, Hash weaponHash, any p3)l
extern _native64(0xD966D51AA5B28BB9) void GIVE_WEAPON_COMPONENT_TO_PED(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0x1E8BE90C74FB4C09) void REMOVE_WEAPON_COMPONENT_FROM_PED(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0xC593212475FAE340) bool HAS_PED_GOT_WEAPON_COMPONENT(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0x0D78DE0572D3969E) bool IS_PED_WEAPON_COMPONENT_ACTIVE(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0x8C0D57EA686FAD87) bool REFILL_AMMO_INSTANTLY(Ped ped)l
extern _native64(0x20AE33F3AC9C0033) bool MAKE_PED_RELOAD(Ped ped)l
extern _native64(0x5443438F033E29C3) void REQUEST_WEAPON_ASSET(Hash weaponHash, int p1, int p2)l
extern _native64(0x36E353271F0E90EE) bool HAS_WEAPON_ASSET_LOADED(Hash weaponHash)l
extern _native64(0xAA08EF13F341C8FC) void REMOVE_WEAPON_ASSET(Hash weaponHash)l
extern _native64(0x9541D3CF0D398F36) Object CREATE_WEAPON_OBJECT(Hash weaponHash, int ammoCount, float x, float y, float z, bool showWorldModel, float scale, any p7, any p8, any p9)l
extern _native64(0x33E179436C0B31DB) void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Object weaponObject, Hash componentHash)l
extern _native64(0xF7D82B0D66777611) void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(Object object, Hash componentHash)l
extern _native64(0x76A18844E743BF91) bool HAS_WEAPON_GOT_WEAPON_COMPONENT(Object weapon, Hash componentHash)l
extern _native64(0xB1FA61371AF7C4B7) void GIVE_WEAPON_OBJECT_TO_PED(Object weaponObject, Ped ped)l
extern _native64(0x5CEE3DF569CECAB0) bool DOES_WEAPON_TAKE_WEAPON_COMPONENT(Hash weaponHash, Hash componentHash)l
extern _native64(0xCAE1DC9A0E22A16D) Object GET_WEAPON_OBJECT_FROM_PED(Ped ped, bool p1)l
extern _native64(0x68F8BE6AF5CDF8A6) void GIVE_LOADOUT_TO_PED(Ped ped, Hash loadoutHash)l
extern _native64(0x50969B9B89ED5738) void SET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash, int tintIndex)l
extern _native64(0x2B9EEDC07BD06B9F) int GET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash)l
extern _native64(0xF827589017D4E4A9) void SET_WEAPON_OBJECT_TINT_INDEX(Object weapon, int tintIndex)l
extern _native64(0xCD183314F7CD2E57) int GET_WEAPON_OBJECT_TINT_INDEX(Object weapon)l
extern _native64(0x5DCF6C5CAB2E9BF7) int GET_WEAPON_TINT_COUNT(Hash weaponHash)l
extern _native64(0x9FE5633880ECD8ED) void SET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash, int colorIndex)l
extern _native64(0xF0A60040BE558F2D) int GET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash)l
extern _native64(0x5DA825A85D0EA6E6) void SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash, int colorIndex)l
extern _native64(0xB3EA4FEABF41464B) int GET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash)l
extern _native64(0xA2C9AC24B4061285) int GET_PED_WEAPON_CAMO_INDEX(Ped ped, Hash weaponHash)l
extern _native64(0x977CA98939E82E4B) void SET_WEAPON_OBJECT_CAMO_INDEX(Object weaponObject, int p1)l
extern _native64(0xD92C739EE34C9EBA) bool GET_WEAPON_HUD_STATS(Hash weaponHash, any* outData)l
extern _native64(0xB3CAF387AE12E9F8) bool GET_WEAPON_COMPONENT_HUD_STATS(Hash componentHash, any* outData)l
extern _native64(0x3133B907D8B32053) float GET_WEAPON_DAMAGE(Hash weaponHash, Hash componentHash)l
extern _native64(0x583BE370B1EC6EB4) int GET_WEAPON_CLIP_SIZE(Hash weaponHash)l
extern _native64(0x065D2AACAD8CF7A4) float GET_WEAPON_TIME_BETWEEN_SHOTS(Hash weaponHash)l
extern _native64(0x8378627201D5497D) void SET_PED_CHANCE_OF_FIRING_BLANKS(Ped ped, float xBias, float yBias)l
extern _native64(0xB4C8D77C80C0421E) Object SET_PED_SHOOT_ORDNANCE_WEAPON(Ped ped, float p1)l
extern _native64(0x48164DBB970AC3F0) void REQUEST_WEAPON_HIGH_DETAIL_MODEL(Entity weaponObject)l
extern _native64(0x4757F00BC6323CFE) void SET_WEAPON_DAMAGE_MODIFIER(Hash weaponHash, float damageMultiplier)l
extern _native64(0x4AE5AC8B852D642C) void SET_WEAPON_AOE_MODIFIER(Hash weaponHash, float multiplier)l
extern _native64(0xE6D2CEDD370FF98E) void SET_WEAPON_EFFECT_DURATION_MODIFIER(Hash p0, float p1)l
extern _native64(0x65F0C5AE05943EC7) bool IS_PED_CURRENT_WEAPON_SILENCED(Ped ped)l
extern _native64(0x4B7620C47217126C) bool IS_FLASH_LIGHT_ON(Ped ped)l
extern _native64(0xCEA66DAD478CD39B) bool SET_FLASH_LIGHT_FADE_DISTANCE(float distance)l
extern _native64(0x988DB6FE9B3AC000) void SET_FLASH_LIGHT_ACTIVE_HISTORY(Ped ped, bool toggle)l
extern _native64(0x1055AC3A667F09D9) void SET_WEAPON_ANIMATION_OVERRIDE(Ped ped, Hash animStyle)l
extern _native64(0x3BE0BB12D25FB305) int GET_WEAPON_DAMAGE_TYPE(Hash weaponHash)l
extern _native64(0xE4DCEC7FD5B739A5) void SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED(Ped ped)l
extern _native64(0xBC7BE5ABC0879F74) bool CAN_USE_WEAPON_ON_PARACHUTE(Hash weaponHash)l
extern _native64(0x91EF34584710BE99) int CREATE_AIR_DEFENCE_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6, Hash weaponHash)l
extern _native64(0x9DA58CDBF6BDBC08) int CREATE_AIR_DEFENCE_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float radius, Hash weaponHash)l
extern _native64(0x0ABF535877897560) bool REMOVE_AIR_DEFENCE_SPHERE(int zoneId)l
extern _native64(0x1E45B34ADEBEE48E) void REMOVE_ALL_AIR_DEFENCE_SPHERES()l
extern _native64(0xECDC202B25E5CF48) void SET_PLAYER_TARGETTABLE_FOR_AIR_DEFENCE_SPHERE(Player player, int zoneId, bool enable)l
extern _native64(0xDAB963831DBFD3F4) bool IS_AIR_DEFENCE_SPHERE_IN_AREA(float x, float y, float z, float radius, int* outZoneId)l
extern _native64(0x44F1012B69313374) void FIRE_AIR_DEFENCE_SPHERE_WEAPON_AT_POSITION(int zoneId, float x, float y, float z)l
extern _native64(0xCD79A550999D7D4F) bool DOES_AIR_DEFENCE_SPHERE_EXIST(int zoneId)l
extern _native64(0xB4771B9AAF4E68E4) void SET_CAN_PED_SELECT_INVENTORY_WEAPON(Ped ped, Hash weaponHash, bool toggle)l
extern _native64(0xEFF296097FF1E509) void SET_CAN_PED_SELECT_ALL_WEAPONS(Ped ped, bool toggle)l
#pragma endregion //}
#pragma region ZONE //{
extern _native64(0x27040C25DE6CB2F4) int GET_ZONE_AT_COORDS(float x, float y, float z)l
extern _native64(0x98CD1D2934B76CC1) int GET_ZONE_FROM_NAME_ID(const char* zoneName)l
extern _native64(0x4334BC40AA0CB4BB) int GET_ZONE_POPSCHEDULE(int zoneId)l
extern _native64(0xCD90657D4C30E1CA) const char* GET_NAME_OF_ZONE(float x, float y, float z)l
extern _native64(0xBA5ECEEA120E5611) void SET_ZONE_ENABLED(int zoneId, bool toggle)l
extern _native64(0x5F7B268D15BA0739) int GET_ZONE_SCUMMINESS(int zoneId)l
extern _native64(0x5F7D596BAC2E7777) void OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(int scheduleId, Hash vehicleHash)l
extern _native64(0x5C0DE367AA0D911C) void CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(int scheduleId)l
extern _native64(0x7EE64D51E8498728) Hash GET_HASH_OF_MAP_AREA_AT_COORDS(float x, float y, float z)l
#pragma endregion //}

	
#undef _native64
#undef l
#pragma clang diagnostic pop