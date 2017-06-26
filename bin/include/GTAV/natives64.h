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

#pragma region PLAYER //{
extern _native64(0x43A66C31C68491C0) Ped GET_PLAYER_PED(Player player)l
extern _native64(0x50FAC3A3E030A6E1) Entity GET_PLAYER_PED_SCRIPT_INDEX(Player player)l
extern _native64(0x00A1CADD00108836) void SET_PLAYER_MODEL(Player player, Hash model)l
extern _native64(0x048189FAC643DEEE) void CHANGE_PLAYER_PED(Player player, Ped ped, bool b2, bool b3)l
extern _native64(0xE902EF951DCE178F) void GET_PLAYER_RGB_COLOUR(Player player, int* r, int* g, int* b)l
extern _native64(0x407C7F91DDB46C16) int GET_NUMBER_OF_PLAYERS()l
extern _native64(0x37039302F4E0A008) int GET_PLAYER_TEAM(Player player)l
extern _native64(0x0299FA38396A4940) void SET_PLAYER_TEAM(Player player, int team)l
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
extern _native64(0xDB172424876553F4) void SET_DISPATCH_COPS_FOR_PLAYER(Player player, bool toggle)l
extern _native64(0x238DB2A2C23EE9EF) bool IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel)l
extern _native64(0xB302540597885499) void CLEAR_PLAYER_WANTED_LEVEL(Player player)l
extern _native64(0x424D4687FA1E5652) bool IS_PLAYER_DEAD(Player player)l
extern _native64(0xFA1E2BF8B10598F9) bool IS_PLAYER_PRESSING_HORN(Player player)l
extern _native64(0x8D32347D6D4C40A2) void SET_PLAYER_CONTROL(Player player, bool toggle, int possiblyFlags)l
extern _native64(0xE28E54788CE8F12D) int GET_PLAYER_WANTED_LEVEL(Player player)l
extern _native64(0xAA5F02DB48D704B9) void SET_MAX_WANTED_LEVEL(int maxWantedLevel)l
extern _native64(0x43286D561B72B8BF) void SET_POLICE_RADAR_BLIPS(bool toggle)l
extern _native64(0x32C62AA929C2DA6A) void SET_POLICE_IGNORE_PLAYER(Player player, bool toggle)l
extern _native64(0x5E9564D8246B909A) bool IS_PLAYER_PLAYING(Player player)l
extern _native64(0x8EEDA153AD141BA4) void SET_EVERYONE_IGNORE_PLAYER(Player player, bool toggle)l
extern _native64(0x056E0FE8534C2949) void SET_ALL_RANDOM_PEDS_FLEE(Player player, bool toggle)l
extern _native64(0x471D2FF42A94B4F2) void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player)l
extern _native64(0xDE45D1A1EF45EE61) void UNK_0xDE45D1A1EF45EE61(Player player, bool toggle)l
extern _native64(0xC3376F42B1FACCC6) void UNK_0xC3376F42B1FACCC6(Player player)l
extern _native64(0x596976B02B6B5700) void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Player player, bool toggle)l
extern _native64(0x020E5F00CDA207BA) void SET_WANTED_LEVEL_MULTIPLIER(float multiplier)l
extern _native64(0x9B0BB33B04405E7A) void SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty)l
extern _native64(0xB9D0DD990DC141DD) void RESET_WANTED_LEVEL_DIFFICULTY(Player player)l
extern _native64(0xBF9BD71691857E48) void START_FIRING_AMNESTY(int duration)l
extern _native64(0xE9B09589827545E7) void REPORT_CRIME(Player player, int crimeType, int wantedLvlThresh)l
extern _native64(0x9A987297ED8BD838) void _SWITCH_CRIME_TYPE(Player player, int p1)l
extern _native64(0xBC9490CA15AEA8FB) void UNK_0xBC9490CA15AEA8FB(Player player)l
extern _native64(0x4669B3ED80F24B4E) any UNK_0x4669B3ED80F24B4E(Player player)l
extern _native64(0xAD73CE5A09E42D12) any UNK_0xAD73CE5A09E42D12(Player player)l
extern _native64(0x36F1B38855F2A8DF) void UNK_0x36F1B38855F2A8DF(Player player)l
extern _native64(0xDC64D2C53493ED12) void UNK_0xDC64D2C53493ED12(Player player)l
extern _native64(0xB45EFF719D8427A6) void UNK_0xB45EFF719D8427A6(float p0)l
extern _native64(0x0032A6DBA562C518) void UNK_0x0032A6DBA562C518()l
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
extern _native64(0xD465A8599DFF6814) any SET_PLAYER_CAN_USE_COVER(Player player, bool toggle)l
extern _native64(0x462E0DB9B137DC5F) int GET_MAX_WANTED_LEVEL()l
extern _native64(0x78CFE51896B6B8A4) bool IS_PLAYER_TARGETTING_ANYTHING(Player player)l
extern _native64(0xA01B8075D8B92DF4) void SET_PLAYER_SPRINT(Player player, bool toggle)l
extern _native64(0xA6F312FCCE9C1DFE) void RESET_PLAYER_STAMINA(Player player)l
extern _native64(0xA352C1B864CAFD33) void RESTORE_PLAYER_STAMINA(Player player, float p1)l
extern _native64(0x3F9F16F8E65A7ED7) float GET_PLAYER_SPRINT_STAMINA_REMAINING(Player player)l
extern _native64(0x1885BC9B108B4C99) float GET_PLAYER_SPRINT_TIME_REMAINING(Player player)l
extern _native64(0xA1FCF8E6AF40B731) float GET_PLAYER_UNDERWATER_TIME_REMAINING(Player player)l
extern _native64(0x0D127585F77030AF) int GET_PLAYER_GROUP(Player player)l
extern _native64(0x92659B4CE1863CB3) int GET_PLAYER_MAX_ARMOUR(Player player)l
extern _native64(0x49C32D60007AFA47) bool IS_PLAYER_CONTROL_ON(Player player)l
extern _native64(0x7C814D2FB49F40C0) bool _IS_PLAYER_CAM_CONTROL_DISABLED()l
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
extern _native64(0xBEC7076D64130195) bool GIVE_ACHIEVEMENT_TO_PLAYER(int achievement)l
extern _native64(0xC2AFFFDABBDC2C5C) bool UNK_0xC2AFFFDABBDC2C5C(any p0, any p1)l
extern _native64(0x1C186837D0619335) Cam UNK_0x1C186837D0619335(any p0)l
extern _native64(0x867365E111A3B6EB) bool HAS_ACHIEVEMENT_BEEN_PASSED(int achievement)l
extern _native64(0xF25D331DC2627BBC) bool IS_PLAYER_ONLINE()l
extern _native64(0x74556E1420867ECA) bool IS_PLAYER_LOGGING_IN_NP()l
extern _native64(0x94DD7888C10A979E) void DISPLAY_SYSTEM_SIGNIN_UI(bool unk)l
extern _native64(0x5D511E3867C87139) bool IS_SYSTEM_UI_BEING_DISPLAYED()l
extern _native64(0x239528EACDC3E7DE) void SET_PLAYER_INVINCIBLE(Player player, bool toggle)l
extern _native64(0xB721981B2B939E07) bool GET_PLAYER_INVINCIBLE(Player player)l
extern _native64(0xCAC57395B151135F) void UNK_0xCAC57395B151135F(Player player, bool p1)l
extern _native64(0xF3AC26D3CC576528) any REMOVE_PLAYER_HELMET(Player player, bool p2)l
extern _native64(0x3C49C870E66F0A28) void GIVE_PLAYER_RAGDOLL_CONTROL(Player player, bool toggle)l
extern _native64(0x5C8B2F450EE4328E) void SET_PLAYER_LOCKON(Player player, bool toggle)l
extern _native64(0xB1906895227793F3) void SET_PLAYER_TARGETING_MODE(int targetMode)l
extern _native64(0x5702B917B99DB1CD) void UNK_0x5702B917B99DB1CD(any p0)l
extern _native64(0xB9CF1F793A9F1BF1) any UNK_0xB9CF1F793A9F1BF1()l
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
extern _native64(0xB885852C39CC265D) void UNK_0xB885852C39CC265D()l
extern _native64(0x2E8AABFA40A84F8C) void SET_DISABLE_AMBIENT_MELEE_MOVE(Player player, bool toggle)l
extern _native64(0x77DFCCF5948B8C71) void SET_PLAYER_MAX_ARMOUR(Player player, int value)l
extern _native64(0xD6A953C6D1492057) void SPECIAL_ABILITY_DEACTIVATE(Player player)l
extern _native64(0x9CB5CE07A3968D5A) void SPECIAL_ABILITY_DEACTIVATE_FAST(Player player)l
extern _native64(0x375F0E738F861A94) void SPECIAL_ABILITY_RESET(Player player)l
extern _native64(0xC9A763D8FE87436A) void UNK_0xC9A763D8FE87436A(Player player)l
extern _native64(0x2E7B9B683481687D) void SPECIAL_ABILITY_CHARGE_SMALL(Player player, bool p1, bool p2)l
extern _native64(0xF113E3AA9BC54613) void SPECIAL_ABILITY_CHARGE_MEDIUM(Player player, bool p1, bool p2)l
extern _native64(0xF733F45FA4497D93) void SPECIAL_ABILITY_CHARGE_LARGE(Player player, bool p1, bool p2)l
extern _native64(0xED481732DFF7E997) void SPECIAL_ABILITY_CHARGE_CONTINUOUS(Player player, Ped p2)l
extern _native64(0xB7B0870EB531D08D) void SPECIAL_ABILITY_CHARGE_ABSOLUTE(Player player, int p1, bool p2)l
extern _native64(0xA0696A65F009EE18) void SPECIAL_ABILITY_CHARGE_NORMALIZED(Player player, float normalizedValue, bool p2)l
extern _native64(0x3DACA8DDC6FD4980) void SPECIAL_ABILITY_FILL_METER(Player player, bool p1)l
extern _native64(0x1D506DBBBC51E64B) void SPECIAL_ABILITY_DEPLETE_METER(Player player, bool p1)l
extern _native64(0x6A09D0D590A47D13) void SPECIAL_ABILITY_LOCK(Hash playerModel)l
extern _native64(0xF145F3BE2EFA9A3B) void SPECIAL_ABILITY_UNLOCK(Hash playerModel)l
extern _native64(0xC6017F6A6CDFA694) bool IS_SPECIAL_ABILITY_UNLOCKED(Hash playerModel)l
extern _native64(0x3E5F7FC85D854E15) bool IS_SPECIAL_ABILITY_ACTIVE(Player player)l
extern _native64(0x05A1FE504B7F2587) bool IS_SPECIAL_ABILITY_METER_FULL(Player player)l
extern _native64(0x181EC197DAEFE121) void ENABLE_SPECIAL_ABILITY(Player player, bool toggle)l
extern _native64(0xB1D200FE26AEF3CB) bool IS_SPECIAL_ABILITY_ENABLED(Player player)l
extern _native64(0xA49C426ED0CA4AB7) void SET_SPECIAL_ABILITY_MULTIPLIER(float multiplier)l
extern _native64(0xFFEE8FA29AB9A18E) void UNK_0xFFEE8FA29AB9A18E(Player player)l
extern _native64(0x5FC472C501CCADB3) bool UNK_0x5FC472C501CCADB3(Player player)l
extern _native64(0xF10B44FD479D69F3) bool UNK_0xF10B44FD479D69F3(Player player, int p1)l
extern _native64(0xDD2620B7B9D16FF1) bool UNK_0xDD2620B7B9D16FF1(Player player, float p1)l
extern _native64(0xAD15F075A4DA0FDE) void START_PLAYER_TELEPORT(Player player, vector3 vec, float heading, bool p5, bool p6, bool p7)l
extern _native64(0xE23D5873C2394C61) bool _HAS_PLAYER_TELEPORT_FINISHED(Player player)l
extern _native64(0xC449EDED9D73009C) void STOP_PLAYER_TELEPORT()l
extern _native64(0x02B15662D7F8886F) bool IS_PLAYER_TELEPORT_ACTIVE()l
extern _native64(0x2F395D61F3A1F877) float GET_PLAYER_CURRENT_STEALTH_NOISE(Player player)l
extern _native64(0x5DB660B38DD98A31) void SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(Player player, float regenRate)l
extern _native64(0xCE07B9F7817AADA3) void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float damageAmount)l
extern _native64(0x2D83BC011CA14A3C) void SET_PLAYER_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native64(0x4A3DC7ECCC321032) void SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Player player, float modifier, int p2)l
extern _native64(0xAE540335B4ABC4E2) void SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native64(0xA50E117CDDF82F0C) void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player player, float damageAmount)l
extern _native64(0x4C60E6EFDAFF2462) void SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native64(0xA3D0E54541D9A5E5) void SET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int tintIndex)l
extern _native64(0x75D3F7A1B0D9B145) void GET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int* tintIndex)l
extern _native64(0xAF04C87F5DC1DF38) void SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int index)l
extern _native64(0xD5A016BC3C09CF40) void GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int* index)l
extern _native64(0x93B0FB27C9A04060) void SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int tintIndex)l
extern _native64(0x6E9C742F340CE5A2) void GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int* tintIndex)l
extern _native64(0x7DDAB28D31FAC363) void SET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)l
extern _native64(0x5DDFE2FF727F3CA3) bool GET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)l
extern _native64(0xF401B182DBA8AF53) void SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(Player player, bool enabled)l
extern _native64(0x8217FD371A4625CF) void SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, RGB colour)l
extern _native64(0xEF56DBABD3CD4887) void GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int* r, int* g, int* b)l
extern _native64(0x11D5F725F0E780E0) void SET_PLAYER_RESET_FLAG_PREFER_REAR_SEATS(Player player, int flags)l
extern _native64(0xDB89EF50FF25FCE9) void SET_PLAYER_NOISE_MULTIPLIER(Player player, float multiplier)l
extern _native64(0xB2C1A29588A9F47C) void SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(Player player, float multiplier)l
extern _native64(0xF297383AA91DCA29) bool CAN_PED_HEAR_PLAYER(Player player, Ped ped)l
extern _native64(0x477D5D63E63ECA5D) void SIMULATE_PLAYER_INPUT_GAIT(Player player, float amount, int gaitType, float speed, bool p4, bool p5)l
extern _native64(0x19531C47A2ABD691) void RESET_PLAYER_INPUT_GAIT(Player player)l
extern _native64(0x9F343285A00B4BB6) void SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(Player player, bool toggle)l
extern _native64(0xD2B315B6689D537D) void UNK_0xD2B315B6689D537D(Player player, bool p1)l
extern _native64(0x4E9021C1FCDD507A) void SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(Player player, float value)l
extern _native64(0x690A61A6D13583F6) bool UNK_0x690A61A6D13583F6(any p0)l
extern _native64(0x9EDD76E87D5D51BA) void UNK_0x9EDD76E87D5D51BA(Player player)l
extern _native64(0xC54C95DA968EC5B5) void SET_PLAYER_SIMULATE_AIMING(Player player, bool toggle)l
extern _native64(0x749FADDF97DFE930) void SET_PLAYER_CLOTH_PIN_FRAMES(Player player, bool toggle)l
extern _native64(0x9F7BBA2EA6372500) void SET_PLAYER_CLOTH_PACKAGE_INDEX(int index)l
extern _native64(0x14D913B777DFF5DA) void SET_PLAYER_CLOTH_LOCK_COUNTER(int value)l
extern _native64(0xED51733DC73AED51) void PLAYER_ATTACH_VIRTUAL_BOUND(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7)l
extern _native64(0x1DD5897E2FA6E7C9) void PLAYER_DETACH_VIRTUAL_BOUND()l
extern _native64(0xD705740BB0A1CF4C) bool HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(Player player)l
extern _native64(0x38D28DA81E4E9BF9) bool UNK_0x38D28DA81E4E9BF9(Player player)l
extern _native64(0xBC0753C9CA14B506) bool UNK_0xBC0753C9CA14B506(Player player, int p1, bool p2)l
extern _native64(0x5006D96C995A5827) void _EXPAND_WORLD_LIMITS(vector3 vec)l
extern _native64(0x4EC12697209F2196) bool IS_PLAYER_RIDING_TRAIN(Player player)l
extern _native64(0xD55DDFB47991A294) bool HAS_PLAYER_LEFT_THE_WORLD(Player player)l
extern _native64(0xFF300C7649724A0B) void UNK_0xFF300C7649724A0B(Player player, bool p1)l
extern _native64(0xD9284A8C0D48352C) void SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player, int p1, any p2, any p3, bool p4)l
extern _native64(0x0F4CC924CF8C7B21) void CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player)l
extern _native64(0x977DB4641F6FC3DB) void SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model)l
extern _native64(0x8753997EB5F6EE3F) void CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player)l
extern _native64(0xDC80A4C2F18A2B64) void SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player, Hash model)l
extern _native64(0x10C54E4389C12B42) void CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player)l
extern _native64(0xC142BE3BB9CE125F) void DISABLE_PLAYER_VEHICLE_REWARDS(Player player)l
extern _native64(0x2F7CEB6520288061) void UNK_0x2F7CEB6520288061(bool p0)l
extern _native64(0x5DC40A8869C22141) void UNK_0x5DC40A8869C22141(bool p0, ScrHandle p1)l
extern _native64(0x65FAEE425DE637B0) bool UNK_0x65FAEE425DE637B0(Player p0)l
extern _native64(0x5501B7A5CDB79D37) void UNK_0x5501B7A5CDB79D37(any p0)l
extern _native64(0x56105E599CAB0EFA) Player UNK_0x56105E599CAB0EFA(int* p0)l
extern _native64(0x8BC515BAE4AAF8FF) float _GET_PLAYER_HEALTH_RECHARGE_LIMIT(Player player)l
extern _native64(0xC388A0F065F5BC34) void _SET_PLAYER_HEALTH_RECHARGE_LIMIT(Player player, float value)l
extern _native64(0x6BC97F4F4BB3C04B) void _SET_PLAYER_INVINCIBLE_KEEP_RAGDOLL_ENABLED(Player player, bool enabled)l
#pragma endregion //}
#pragma region ENTITY //{
extern _native64(0x7239B21A38F536BA) bool DOES_ENTITY_EXIST(Entity entity)l
extern _native64(0xDDE6DF5AE89981D2) bool DOES_ENTITY_BELONG_TO_THIS_SCRIPT(Entity entity, bool p1)l
extern _native64(0x060D6E96F8B8E48D) bool DOES_ENTITY_HAVE_DRAWABLE(Entity entity)l
extern _native64(0xDA95EA3317CC5064) bool DOES_ENTITY_HAVE_PHYSICS(Entity entity)l
extern _native64(0x20B711662962B472) bool HAS_ENTITY_ANIM_FINISHED(Entity entity, const char* animDict, const char* animName, int p3)l
extern _native64(0x95EB9964FF5C5C65) bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity entity)l
extern _native64(0x605F5A140F202491) bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity entity)l
extern _native64(0xDFD5033FDBA0A9C8) bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity entity)l
extern _native64(0xC86D67D52A707CF8) bool HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2, bool p2)l
extern _native64(0xFCDFF7B72D23A1AC) bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Entity entity1, Entity entity2, int traceType)l
extern _native64(0x0267D00AF114F17A) bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Entity entity1, Entity entity2)l
extern _native64(0x8BAD02F0368D9E14) bool HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity entity)l
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
extern _native64(0x846BF6291198A71E) float _GET_ENTITY_PHYSICS_HEADING(Entity entity)l
extern _native64(0xEEF059FAD016D209) int GET_ENTITY_HEALTH(Entity entity)l
extern _native64(0x15D757606D170C3C) int GET_ENTITY_MAX_HEALTH(Entity entity)l
extern _native64(0x166E7CF68597D8B5) void SET_ENTITY_MAX_HEALTH(Entity entity, int value)l
extern _native64(0x5A504562485944DD) float GET_ENTITY_HEIGHT(Entity entity, vector3 vec, bool atTop, bool inWorldCoords)l
extern _native64(0x1DD55701034110E5) float GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity entity)l
extern _native64(0xECB2FC7235A7D137) void GET_ENTITY_MATRIX(Entity entity, vector3* rightVector, vector3* forwardVector, vector3* upVector, vector3* position)l
extern _native64(0x9F47B058362C84B5) Hash GET_ENTITY_MODEL(Entity entity)l
extern _native64(0x2274BC1C4885E333) vector3 GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Entity entity, vector3 pos)l
extern _native64(0x1899F328B0E12848) vector3 GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity entity, vector3 offset)l
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
extern _native64(0x8ACD366038D14505) int GET_ENTITY_TYPE(Entity entity)l
extern _native64(0xF6F5161F4534EDFF) int GET_ENTITY_POPULATION_TYPE(Entity entity)l
extern _native64(0x731EC8A916BD11A1) bool IS_AN_ENTITY(int handle)l
extern _native64(0x524AC5ECEA15343E) bool IS_ENTITY_A_PED(Entity entity)l
extern _native64(0x0A7B270912999B3C) bool IS_ENTITY_A_MISSION_ENTITY(Entity entity)l
extern _native64(0x6AC7003FA6E5575E) bool IS_ENTITY_A_VEHICLE(Entity entity)l
extern _native64(0x8D68C8FD0FACA94E) bool IS_ENTITY_AN_OBJECT(Entity entity)l
extern _native64(0x20B60995556D004F) bool IS_ENTITY_AT_COORD(Entity entity, vector3 Pos, vector3 Size, bool p7, bool p8, int p9)l
extern _native64(0x751B70C3D034E187) bool IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, vector3 Size, bool p5, bool p6, int p7)l
extern _native64(0xB346476EF1A64897) bool IS_ENTITY_ATTACHED(Entity entity)l
extern _native64(0xCF511840CEEDE0CC) bool IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Entity entity)l
extern _native64(0xB1632E9A5F988D11) bool IS_ENTITY_ATTACHED_TO_ANY_PED(Entity entity)l
extern _native64(0x26AA915AD89BFB4B) bool IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Entity entity)l
extern _native64(0xEFBE71898A993728) bool IS_ENTITY_ATTACHED_TO_ENTITY(Entity from, Entity to)l
extern _native64(0x5F9532F3B5CC2551) bool IS_ENTITY_DEAD(Entity entity)l
extern _native64(0x886E37EC497200B6) bool IS_ENTITY_IN_AIR(Entity entity)l
extern _native64(0x51210CED3DA1C78A) bool IS_ENTITY_IN_ANGLED_AREA(Entity entity, vector3 origin, vector3 edge, float angle, bool p8, bool p9, any p10)l
extern _native64(0x54736AA40E271165) bool IS_ENTITY_IN_AREA(Entity entity, vector3 vec_1, vector3 vec_2, bool p7, bool p8, any p9)l
extern _native64(0xB6463CF6AF527071) bool IS_ENTITY_IN_ZONE(Entity entity, const char* zone)l
extern _native64(0xCFB0A0D8EDD145A3) bool IS_ENTITY_IN_WATER(Entity entity)l
extern _native64(0xE81AFC1BC4CC41CE) float GET_ENTITY_SUBMERGED_LEVEL(Entity entity)l
extern _native64(0x694E00132F2823ED) void UNK_0x694E00132F2823ED(Entity entity, bool p1)l
extern _native64(0xE659E47AF827484B) bool IS_ENTITY_ON_SCREEN(Entity entity)l
extern _native64(0x1F0B79228E461EC9) bool IS_ENTITY_PLAYING_ANIM(Entity entity, const char* animDict, const char* animName, int p4)l
extern _native64(0x1218E6886D3D8327) bool IS_ENTITY_STATIC(Entity entity)l
extern _native64(0x17FFC1B2BA35A494) bool IS_ENTITY_TOUCHING_ENTITY(Entity entity, Entity targetEntity)l
extern _native64(0x0F42323798A58C8C) bool IS_ENTITY_TOUCHING_MODEL(Entity entity, Hash modelHash)l
extern _native64(0x5333F526F6AB19AA) bool IS_ENTITY_UPRIGHT(Entity entity, float angle)l
extern _native64(0x1DBD58820FA61D71) bool IS_ENTITY_UPSIDEDOWN(Entity entity)l
extern _native64(0x47D6F43D77935C75) bool IS_ENTITY_VISIBLE(Entity entity)l
extern _native64(0xD796CB5BA8F20E32) bool IS_ENTITY_VISIBLE_TO_SCRIPT(Entity entity)l
extern _native64(0xE31C2C72B8692B64) bool IS_ENTITY_OCCLUDED(Entity entity)l
extern _native64(0xEE5D2A122E09EC42) bool WOULD_ENTITY_BE_OCCLUDED(Hash entityModelHash, vector3 vec, bool p4)l
extern _native64(0xD05BFF0C0A12C68F) bool IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Entity entity)l
extern _native64(0x18FF00FC7EFF559E) void APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(Entity entity, int forceType, vector3 vec, bool p5, bool isRel, bool highForce, bool p8)l
extern _native64(0xC5F68BE9613E2D18) void APPLY_FORCE_TO_ENTITY(Entity entity, int forceType, vector3 vec, vector3 Rot, int p8, bool isRel, bool p10, bool highForce, bool p12, bool p13)l
extern _native64(0x6B9BBD38AB0796DF) void ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, vector3 Pos, vector3 Rot, bool p9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot)l
extern _native64(0xC3675780C92F90F9) void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, vector3 Pos1, vector3 Pos2, vector3 Rot, float breakForce, bool fixedRot, bool p15, bool collision, bool p17, int p18)l
extern _native64(0xF4080490ADC51C6F) void PROCESS_ENTITY_ATTACHMENTS(Entity entity)l
extern _native64(0xFB71170B7E76ACBA) int GET_ENTITY_BONE_INDEX_BY_NAME(Entity entity, const char* boneName)l
extern _native64(0xA72CD9CA74A5ECBA) any CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity)l
extern _native64(0xAE3CBE5BF394C9C9) void DELETE_ENTITY(Entity* entity)l
extern _native64(0x961AC54BF0613F5D) void DETACH_ENTITY(Entity entity, bool p1, bool collision)l
extern _native64(0x428CA6DBD1094446) void FREEZE_ENTITY_POSITION(Entity entity, bool toggle)l
extern _native64(0x3910051CCECDB00C) void _SET_ENTITY_REGISTER(Entity entity, bool toggle)l
extern _native64(0x7FB218262B810701) bool PLAY_ENTITY_ANIM(Entity entity, const char* animName, const char* animDict, float p3, bool loop, bool stayInAnim, bool p6, float delta, any bitset)l
extern _native64(0xC77720A12FE14A86) bool PLAY_SYNCHRONIZED_ENTITY_ANIM(Entity entity, int syncedScene, const char* animation, const char* propName, float p4, float p5, any p6, float p7)l
extern _native64(0xB9C54555ED30FBC4) bool PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(float p0, float p1, float p2, float p3, any p4, any p5, any* p6, any* p7, float p8, float p9, any p10, float p11)l
extern _native64(0x11E79CAB7183B6F5) bool STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(float p0, float p1, float p2, float p3, any p4, float p5)l
extern _native64(0x28004F88151E03E0) any STOP_ENTITY_ANIM(Entity entity, const char* animation, const char* animGroup, float p3)l
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
extern _native64(0xE22D8FDE858B8119) void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool bCanBeDamaged, int relGroup)l
extern _native64(0xD3997889736FD899) void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Entity entity, bool toggle)l
extern _native64(0x1A9205C1B9EE827F) void SET_ENTITY_COLLISION(Entity entity, bool toggle, bool keepPhysics)l
extern _native64(0xCCF1E97BEFDAE480) bool GET_ENTITY_COLLISON_DISABLED(Entity entity)l
extern _native64(0x9EBC85ED0FFFE51C) void UNK_0x9EBC85ED0FFFE51C(Entity entity, bool p1, bool p2)l
extern _native64(0x06843DA7060A026B) void SET_ENTITY_COORDS(Entity entity, vector3 Pos, bool xAxis, bool yAxis, bool zAxis, bool clearArea)l
extern _native64(0x621873ECE1178967) void _SET_ENTITY_COORDS_2(Entity entity, vector3 Pos, bool xAxis, bool yAxis, bool zAxis, bool clearArea)l
extern _native64(0x239A3351AC1DA385) void SET_ENTITY_COORDS_NO_OFFSET(Entity entity, vector3 Pos, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x1718DE8E3F2823CA) void SET_ENTITY_DYNAMIC(Entity entity, bool toggle)l
extern _native64(0x8E2530AA8ADA980E) void SET_ENTITY_HEADING(Entity entity, float heading)l
extern _native64(0x6B76DC1F3AE6E6A3) void SET_ENTITY_HEALTH(Entity entity, int health)l
extern _native64(0x3882114BDE571AD4) void SET_ENTITY_INVINCIBLE(Entity entity, bool toggle)l
extern _native64(0xEA02E132F5C68722) void SET_ENTITY_IS_TARGET_PRIORITY(Entity entity, bool p1, float p2)l
extern _native64(0x7CFBA6A80BDF3874) void SET_ENTITY_LIGHTS(Entity entity, bool toggle)l
extern _native64(0x0DC7CABAB1E9B67E) void SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, bool toggle)l
extern _native64(0xE9676F61BC0B3321) bool HAS_COLLISION_LOADED_AROUND_ENTITY(Entity entity)l
extern _native64(0x0E46A3FCBDE2A1B1) void SET_ENTITY_MAX_SPEED(Entity entity, float speed)l
extern _native64(0x79F020FF9EDC0748) void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Entity entity, bool toggle)l
extern _native64(0x7022BD828FA0B082) void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool p1, any p2)l
extern _native64(0xFAEE099C6F890BB8) void SET_ENTITY_PROOFS(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool p6, bool p7, bool drownProof)l
extern _native64(0x77B21BE7AC540F07) void SET_ENTITY_QUATERNION(Entity entity, quaternion quat)l
extern _native64(0x0A50A1EEDAD01E65) void SET_ENTITY_RECORDS_COLLISIONS(Entity entity, bool toggle)l
extern _native64(0x8524A8B0171D5E07) void SET_ENTITY_ROTATION(Entity entity, vector3 rot, int rotationOrder, bool p5)l
extern _native64(0xEA1C610A04DB6BBB) void SET_ENTITY_VISIBLE(Entity entity, bool toggle, bool unk)l
extern _native64(0x1C99BB7B6E96D16F) void SET_ENTITY_VELOCITY(Entity entity, vector3 vec)l
extern _native64(0x4A4722448F18EEF5) void SET_ENTITY_HAS_GRAVITY(Entity entity, bool toggle)l
extern _native64(0x5927F96A78577363) void SET_ENTITY_LOD_DIST(Entity entity, int value)l
extern _native64(0x4159C2762B5791D6) int GET_ENTITY_LOD_DIST(Entity entity)l
extern _native64(0x44A0870B7E92D7C0) void SET_ENTITY_ALPHA(Entity entity, int alphaLevel, bool skin)l
extern _native64(0x5A47B3B5E63E94C6) int GET_ENTITY_ALPHA(Entity entity)l
extern _native64(0x9B1E824FFBB7027A) any RESET_ENTITY_ALPHA(Entity entity)l
extern _native64(0x5C3B791D580E0BC2) void UNK_0x5C3B791D580E0BC2(Entity entity, float p1)l
extern _native64(0xACAD101E1FB66689) void SET_ENTITY_ALWAYS_PRERENDER(Entity entity, bool toggle)l
extern _native64(0x730F5F8D3F0F2050) void SET_ENTITY_RENDER_SCORCHED(Entity entity, bool toggle)l
extern _native64(0x57C5DB656185EAC4) void SET_ENTITY_TRAFFICLIGHT_OVERRIDE(Entity entity, int state)l
extern _native64(0x78E8E3A640178255) void UNK_0x78E8E3A640178255(Entity entity)l
extern _native64(0x92C47782FDA8B2A3) void CREATE_MODEL_SWAP(vector3 vec, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native64(0x033C0F9A64E229AE) void REMOVE_MODEL_SWAP(vector3 vec, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native64(0x8A97BCA30A0CE478) void CREATE_MODEL_HIDE(vector3 vec, float radius, Hash model, bool p5)l
extern _native64(0x3A52AE588830BF7F) void CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(vector3 vec, float radius, Hash model, bool p5)l
extern _native64(0xD9E3006FB3CBD765) void REMOVE_MODEL_HIDE(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x150E808B375A385A) void CREATE_FORCED_OBJECT(vector3 vec, any p3, Hash modelHash, bool p5)l
extern _native64(0x61B6775E83C0DB6F) void REMOVE_FORCED_OBJECT(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xA53ED5520C07654A) void SET_ENTITY_NO_COLLISION_ENTITY(Entity entity1, Entity entity2, bool unknown)l
extern _native64(0x295D82A8559F9150) void SET_ENTITY_MOTION_BLUR(Entity entity, bool toggle)l
extern _native64(0xE12ABE5E3A389A6C) void UNK_0xE12ABE5E3A389A6C(Entity entity, bool p1)l
extern _native64(0xA80AE305E0A3044F) void UNK_0xA80AE305E0A3044F(Entity entity, bool p1)l
extern _native64(0xDC6F8601FAF2E893) void UNK_0xDC6F8601FAF2E893(Entity entity, bool p1)l
extern _native64(0x2C2E3DC128F44309) void UNK_0x2C2E3DC128F44309(Entity entity, bool p1)l
extern _native64(0x1A092BB0C3808B96) void UNK_0x1A092BB0C3808B96(Entity entity, bool p1)l
#pragma endregion //}
#pragma region PED //{
extern _native64(0xD49F9B0955C367DE) Ped CREATE_PED(int pedType, Hash modelHash, vector3 vec, float heading, bool isNetwork, bool p7)l
extern _native64(0x9614299DCB53E54B) void DELETE_PED(Ped* ped)l
extern _native64(0xEF29A16337FACADB) Ped CLONE_PED(Ped ped, float heading, bool isNetwork, bool p3)l
extern _native64(0xE952D6431689AD9A) void CLONE_PED_TO_TARGET(Ped ped, Ped targetPed)l
extern _native64(0xA3EE4A07279BB9DB) bool IS_PED_IN_VEHICLE(Ped ped, Vehicle vehicle, bool atGetIn)l
extern _native64(0x796D90EFB19AA332) bool IS_PED_IN_MODEL(Ped ped, Hash modelHash)l
extern _native64(0x997ABD671D25CA0B) bool IS_PED_IN_ANY_VEHICLE(Ped ped, bool atGetIn)l
extern _native64(0x16EC4839969F9F5E) bool IS_COP_PED_IN_AREA_3D(vector3 vec_1, vector3 vec_2)l
extern _native64(0x84A2DD9AC37C35C1) bool IS_PED_INJURED(Ped ped)l
extern _native64(0x5983BB449D7FDB12) bool IS_PED_HURT(Ped ped)l
extern _native64(0xD839450756ED5A80) bool IS_PED_FATALLY_INJURED(Ped ped)l
extern _native64(0x3317DEDB88C95038) bool IS_PED_DEAD_OR_DYING(Ped ped, bool p1)l
extern _native64(0xE0A0AEC214B1FABA) bool IS_CONVERSATION_PED_DEAD(Ped ped)l
extern _native64(0x3998B1276A3300E5) bool IS_PED_AIMING_FROM_COVER(Ped ped)l
extern _native64(0x24B100C68C645951) bool IS_PED_RELOADING(Ped ped)l
extern _native64(0x12534C348C6CB68B) bool IS_PED_A_PLAYER(Ped ped)l
extern _native64(0x7DD959874C1FD534) Ped CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, bool isNetwork, bool p5)l
extern _native64(0xAA5A7ECE2AA8FE70) void SET_PED_DESIRED_HEADING(Ped ped, float heading)l
extern _native64(0xFF287323B0E2C69A) void _FREEZE_PED_CAMERA_ROTATION(Ped ped)l
extern _native64(0xD71649DB0A545AA3) bool IS_PED_FACING_PED(Ped ped, Ped otherPed, float angle)l
extern _native64(0x4E209B2C1EAD5159) bool IS_PED_IN_MELEE_COMBAT(Ped ped)l
extern _native64(0x530944F6F4B8A214) bool IS_PED_STOPPED(Ped ped)l
extern _native64(0x7E9DFE24AC1E58EF) bool IS_PED_SHOOTING_IN_AREA(Ped ped, vector3 vec_1, vector3 vec_2, bool p7, bool p8)l
extern _native64(0xA0D3D71EA1086C55) bool IS_ANY_PED_SHOOTING_IN_AREA(vector3 vec_1, vector3 vec_2, bool p6, bool p7)l
extern _native64(0x34616828CD07F1A1) bool IS_PED_SHOOTING(Ped ped)l
extern _native64(0x7AEFB85C1D49DEB6) any SET_PED_ACCURACY(Ped ped, int accuracy)l
extern _native64(0x37F4AD56ECBC0CD6) int GET_PED_ACCURACY(Ped ped)l
extern _native64(0xC9D55B1A358A5BF7) bool IS_PED_MODEL(Ped ped, Hash modelHash)l
extern _native64(0x2D05CED3A38D0F3A) void EXPLODE_PED_HEAD(Ped ped, Hash weaponHash)l
extern _native64(0xAC6D445B994DF95E) void REMOVE_PED_ELEGANTLY(Ped* ped)l
extern _native64(0x5BA652A0CD14DF2F) void ADD_ARMOUR_TO_PED(Ped ped, int amount)l
extern _native64(0xCEA04D83135264CC) void SET_PED_ARMOUR(Ped ped, int amount)l
extern _native64(0xF75B0D629E1C063D) void SET_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seatIndex)l
extern _native64(0x3C028C636A414ED9) void SET_PED_ALLOW_VEHICLES_OVERRIDE(Ped ped, bool toggle)l
extern _native64(0x3E8349C08E4B82E4) bool CAN_CREATE_RANDOM_PED(bool unk)l
extern _native64(0xB4AC7D0CF06BFE8F) Ped CREATE_RANDOM_PED(vector3 pos)l
extern _native64(0x9B62392B474F44A0) Ped CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicle, bool returnHandle)l
extern _native64(0xB8EB95E5B4E56978) bool CAN_CREATE_RANDOM_DRIVER()l
extern _native64(0xEACEEDA81751915C) bool CAN_CREATE_RANDOM_BIKE_RIDER()l
extern _native64(0x9E8C908F41584ECD) void SET_PED_MOVE_ANIMS_BLEND_OUT(Ped ped)l
extern _native64(0xC1670E958EEE24E5) void SET_PED_CAN_BE_DRAGGED_OUT(Ped ped, bool toggle)l
extern _native64(0xF2BEBCDFAFDAA19E) void UNK_0xF2BEBCDFAFDAA19E(bool toggle)l
extern _native64(0x6D9F5FAA7488BA46) bool IS_PED_MALE(Ped ped)l
extern _native64(0xB980061DA992779D) bool IS_PED_HUMAN(Ped ped)l
extern _native64(0x9A9112A0FE9A4713) Vehicle GET_VEHICLE_PED_IS_IN(Ped ped, bool lastVehicle)l
extern _native64(0xBB8DE8CF6A8DD8BB) void RESET_PED_LAST_VEHICLE(Ped ped)l
extern _native64(0x95E3D6257B166CF2) void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0x7A556143A1C03898) void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0, float p1)l
extern _native64(0x5A7F62FDA59759BD) void UNK_0x5A7F62FDA59759BD()l
extern _native64(0x5086C7843552CF85) void SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(vector3 vec)l
extern _native64(0xEE01041D559983EA) void SET_PED_NON_CREATION_AREA(vector3 vec_1, vector3 vec_2)l
extern _native64(0x2E05208086BA0651) void CLEAR_PED_NON_CREATION_AREA()l
extern _native64(0x4759CC730F947C81) void UNK_0x4759CC730F947C81()l
extern _native64(0x460BC76A0E10655E) bool IS_PED_ON_MOUNT(Ped ped)l
extern _native64(0xE7E11B8DCBED1058) Ped GET_MOUNT(Ped ped)l
extern _native64(0x67722AEB798E5FAB) bool IS_PED_ON_VEHICLE(Ped ped)l
extern _native64(0xEC5F66E459AF3BB2) bool IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle vehicle)l
extern _native64(0xA9C8960E8684C1B5) void SET_PED_MONEY(Ped ped, int amount)l
extern _native64(0x3F69145BBA87BAE7) int GET_PED_MONEY(Ped ped)l
extern _native64(0xFF4803BC019852D9) void UNK_0xFF4803BC019852D9(float p0, any p1)l
extern _native64(0x6B0E6172C9A4D902) void UNK_0x6B0E6172C9A4D902(bool p0)l
extern _native64(0x9911F4A24485F653) void UNK_0x9911F4A24485F653(bool p0)l
extern _native64(0xEBD76F2359F190AC) void SET_PED_SUFFERS_CRITICAL_HITS(Ped ped, bool toggle)l
extern _native64(0xAFC976FD0580C7B3) void UNK_0xAFC976FD0580C7B3(Ped ped, bool toggle)l
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
extern _native64(0x2F3C3D9F50681DE4) void UNK_0x2F3C3D9F50681DE4(any p0, bool p1)l
extern _native64(0x63F58F7C80513AAD) void SET_PED_CAN_BE_TARGETTED(Ped ped, bool toggle)l
extern _native64(0xBF1CA77833E58F2C) void SET_PED_CAN_BE_TARGETTED_BY_TEAM(Ped ped, int team, bool toggle)l
extern _native64(0x66B57B72E0836A76) void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Ped ped, Player player, bool toggle)l
extern _native64(0x061CB768363D6424) void UNK_0x061CB768363D6424(any p0, bool p1)l
extern _native64(0xFD325494792302D7) void SET_TIME_EXCLUSIVE_DISPLAY_TEXTURE(any p0, bool p1)l
extern _native64(0x0BD04E29640C9C12) bool IS_PED_IN_ANY_POLICE_VEHICLE(Ped ped)l
extern _native64(0x16E42E800B472221) void FORCE_PED_TO_OPEN_PARACHUTE(Ped ped)l
extern _native64(0x7DCE8BDA0F1C1200) bool IS_PED_IN_PARACHUTE_FREE_FALL(Ped ped)l
extern _native64(0xFB92A102F1C4DFA3) bool IS_PED_FALLING(Ped ped)l
extern _native64(0xCEDABC5900A0BF97) bool IS_PED_JUMPING(Ped ped)l
extern _native64(0x53E8CB4F48BFE623) bool IS_PED_CLIMBING(Ped ped)l
extern _native64(0x117C70D1F5730B5E) bool IS_PED_VAULTING(Ped ped)l
extern _native64(0x5527B8246FEF9B11) bool IS_PED_DIVING(Ped ped)l
extern _native64(0x433DDFFE2044B636) bool IS_PED_JUMPING_OUT_OF_VEHICLE(Ped ped)l
extern _native64(0x26AF0E8E30BD2A2C) bool UNK_0x26AF0E8E30BD2A2C(Ped ped)l
extern _native64(0x79CFD9827CC979B6) int GET_PED_PARACHUTE_STATE(Ped ped)l
extern _native64(0x8B9F1FC6AE8166C0) int GET_PED_PARACHUTE_LANDING_TYPE(Ped ped)l
extern _native64(0x333FC8DB079B7186) void SET_PED_PARACHUTE_TINT_INDEX(Ped ped, int tintIndex)l
extern _native64(0xEAF5F7E5AE7C6C9D) void GET_PED_PARACHUTE_TINT_INDEX(Ped ped, int* outTintIndex)l
extern _native64(0xE88DA0751C22A2AD) void SET_PED_RESERVE_PARACHUTE_TINT_INDEX(Ped ped, any p1)l
extern _native64(0x8C4F3BF23B6237DB) Entity UNK_0x8C4F3BF23B6237DB(Ped ped, bool p1, bool p2)l
extern _native64(0x030983CA930B692D) void SET_PED_DUCKING(Ped ped, bool toggle)l
extern _native64(0xD125AE748725C6BC) bool IS_PED_DUCKING(Ped ped)l
extern _native64(0x6E575D6A898AB852) bool IS_PED_IN_ANY_TAXI(Ped ped)l
extern _native64(0xF107E836A70DCE05) void SET_PED_ID_RANGE(Ped ped, float value)l
extern _native64(0x52D59AB61DDC05DD) void UNK_0x52D59AB61DDC05DD(Ped ped, bool p1)l
extern _native64(0xEC4B4B3B9908052A) void UNK_0xEC4B4B3B9908052A(Ped ped, float unk)l
extern _native64(0x733C87D4CE22BEA2) void UNK_0x733C87D4CE22BEA2(any p0)l
extern _native64(0xF29CF591C4BF6CEE) void SET_PED_SEEING_RANGE(Ped ped, float value)l
extern _native64(0x33A8F7F7D5F7F33C) void SET_PED_HEARING_RANGE(Ped ped, float value)l
extern _native64(0x2DB492222FB21E26) void SET_PED_VISUAL_FIELD_MIN_ANGLE(Ped ped, float value)l
extern _native64(0x70793BDCA1E854D4) void SET_PED_VISUAL_FIELD_MAX_ANGLE(Ped ped, float value)l
extern _native64(0x7A276EB2C224D70F) void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Ped ped, float angle)l
extern _native64(0x78D0B67629D75856) void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Ped ped, float angle)l
extern _native64(0x9C74B0BC831B753A) void SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Ped ped, float range)l
extern _native64(0x3B6405E8AB34A907) void SET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped, float angle)l
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
extern _native64(0xEAD42DE3610D0721) bool CAN_PED_IN_COMBAT_SEE_TARGET(Ped ped, Ped target)l
extern _native64(0xB2C086CC1BF8F2BF) bool IS_PED_DOING_DRIVEBY(Ped ped)l
extern _native64(0x4AE4FF911DFB61DA) bool IS_PED_JACKING(Ped ped)l
extern _native64(0x9A497FE2DF198913) bool IS_PED_BEING_JACKED(Ped ped)l
extern _native64(0x4FBACCE3B4138EE8) bool IS_PED_BEING_STUNNED(Ped ped, int p1)l
extern _native64(0x9B128DC36C1E04CF) Ped GET_PEDS_JACKER(Ped ped)l
extern _native64(0x5486A79D9FBD342D) Ped GET_JACK_TARGET(Ped ped)l
extern _native64(0xBBCCE00B381F8482) bool IS_PED_FLEEING(Ped ped)l
extern _native64(0x60DFD0691A170B88) bool IS_PED_IN_COVER(Ped ped, bool p1)l
extern _native64(0x845333B3150583AB) bool IS_PED_IN_COVER_FACING_LEFT(Ped ped)l
extern _native64(0x6A03BF943D767C93) bool _IS_PED_STANDING_IN_COVER(Ped ped)l
extern _native64(0x9F65DBC537E59AD5) bool IS_PED_GOING_INTO_COVER(Ped ped)l
extern _native64(0xAAD6D1ACF08F4612) any SET_PED_PINNED_DOWN(Ped ped, bool pinned, int i)l
extern _native64(0x6F4C85ACD641BCD2) int GET_SEAT_PED_IS_TRYING_TO_ENTER(Ped ped)l
extern _native64(0x814FA8BE5449445D) Vehicle GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Ped ped)l
extern _native64(0x93C8B64DEB84728C) Entity GET_PED_SOURCE_OF_DEATH(Ped ped)l
extern _native64(0x16FFE42AB2D2DC59) Hash GET_PED_CAUSE_OF_DEATH(Ped ped)l
extern _native64(0x1E98817B311AE98A) int _GET_PED_TIME_OF_DEATH(Ped ped)l
extern _native64(0x5407B7288D0478B7) int UNK_0x5407B7288D0478B7(any p0)l
extern _native64(0x336B3D200AB007CB) any UNK_0x336B3D200AB007CB(any p0, float p1, float p2, float p3, float p4)l
extern _native64(0xADB3F206518799E8) void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped, Hash hash)l
extern _native64(0xC80A74AC829DDD92) void SET_PED_RELATIONSHIP_GROUP_HASH(Ped ped, Hash hash)l
extern _native64(0xBF25EB89375A37AD) void SET_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)l
extern _native64(0x5E29243FB56FC6D4) void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)l
extern _native64(0xF372BC22FCB88606) any ADD_RELATIONSHIP_GROUP(const char* name, Hash* groupHash)l
extern _native64(0xB6BA2444AB393DA2) void REMOVE_RELATIONSHIP_GROUP(Hash groupHash)l
extern _native64(0xEBA5AD3A0EAF7121) int GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2)l
extern _native64(0x42FDD0F017B1E38E) Hash GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped)l
extern _native64(0x7DBDD04862D95F04) Hash GET_PED_RELATIONSHIP_GROUP_HASH(Ped ped)l
extern _native64(0x9E6B70061662AE5C) int GET_RELATIONSHIP_BETWEEN_GROUPS(Hash group1, Hash group2)l
extern _native64(0x4328652AE5769C71) void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Ped ped, bool toggle)l
extern _native64(0x112942C6E708F70B) void SET_PED_TO_INFORM_RESPECTED_FRIENDS(Ped ped, float radius, int maxFriends)l
extern _native64(0x625B774D75C87068) bool IS_PED_RESPONDING_TO_EVENT(Ped ped, any event)l
extern _native64(0x9AC577F5A12AD8A9) void SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash)l
extern _native64(0x614DA022990752DC) void SET_PED_SHOOT_RATE(Ped ped, int shootRate)l
extern _native64(0xFF41B4B141ED981C) void SET_COMBAT_FLOAT(Ped ped, int combatType, float p2)l
extern _native64(0x52DFF8A10508090A) float GET_COMBAT_FLOAT(Ped ped, int p1)l
extern _native64(0x8DE69FE35CA09A45) void GET_GROUP_SIZE(int groupID, any* unknown, int* sizeInMembers)l
extern _native64(0x7C6B0C22F9F40BBE) bool DOES_GROUP_EXIST(int groupId)l
extern _native64(0xF162E133B4E7A675) int GET_PED_GROUP_INDEX(Ped ped)l
extern _native64(0x5891CAC5D4ACFF74) bool IS_PED_IN_GROUP(Ped ped)l
extern _native64(0x6A3975DEA89F9A17) Player GET_PLAYER_PED_IS_FOLLOWING(Ped ped)l
extern _native64(0xCE2F5FC3AF7E8C1E) void SET_GROUP_FORMATION(int groupId, int formationType)l
extern _native64(0x1D9D45004C28C916) void SET_GROUP_FORMATION_SPACING(int groupId, float p1, float p2, float p3)l
extern _native64(0x63DAB4CCB3273205) void RESET_GROUP_FORMATION_DEFAULT_SPACING(int groupHandle)l
extern _native64(0x6094AD011A2EA87D) Vehicle GET_VEHICLE_PED_IS_USING(Ped ped)l
extern _native64(0xF92691AED837A5FC) Vehicle SET_EXCLUSIVE_PHONE_RELATIONSHIPS(Ped ped)l
extern _native64(0x9FF447B6B6AD960A) void SET_PED_GRAVITY(Ped ped, bool toggle)l
extern _native64(0x697157CED63F18D4) void APPLY_DAMAGE_TO_PED(Ped ped, int damageAmount, bool p2)l
extern _native64(0x36B77BB84687C318) any UNK_0x36B77BB84687C318(Ped ped, any p1)l
extern _native64(0xDA1F1B7BE1A8766F) void SET_PED_ALLOWED_TO_DUCK(Ped ped, bool toggle)l
extern _native64(0x3DBFC55D5C9BB447) void SET_PED_NEVER_LEAVES_GROUP(Ped ped, bool toggle)l
extern _native64(0xFF059E1E4C01E63C) int GET_PED_TYPE(Ped ped)l
extern _native64(0xBB03C38DD3FB7FFD) void SET_PED_AS_COP(Ped ped, bool toggle)l
extern _native64(0xF5F6378C4F3419D3) void SET_PED_MAX_HEALTH(Ped ped, int value)l
extern _native64(0x4700A416E8324EF3) int GET_PED_MAX_HEALTH(Ped ped)l
extern _native64(0x43C851690662113D) void SET_PED_MAX_TIME_IN_WATER(Ped ped, float value)l
extern _native64(0x6BA428C528D9E522) void SET_PED_MAX_TIME_UNDERWATER(Ped ped, float value)l
extern _native64(0x2735233A786B1BEF) void UNK_0x2735233A786B1BEF(Ped ped, float p1)l
extern _native64(0x952F06BEECD775CC) void UNK_0x952F06BEECD775CC(any p0, any p1, any p2, any p3)l
extern _native64(0xE6CA85E7259CE16B) void UNK_0xE6CA85E7259CE16B(any p0)l
extern _native64(0x7A6535691B477C48) void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped ped, int state)l
extern _native64(0x51AC07A44D4F5B8A) bool CAN_KNOCK_PED_OFF_VEHICLE(Ped ped)l
extern _native64(0x45BBCBA77C29A841) void KNOCK_PED_OFF_VEHICLE(Ped ped)l
extern _native64(0x87052FE446E07247) void SET_PED_COORDS_NO_GANG(Ped ped, vector3 pos)l
extern _native64(0x51455483CF23ED97) Ped GET_PED_AS_GROUP_MEMBER(int groupID, int memberNumber)l
extern _native64(0x5CCE68DBD5FE93EC) Ped _GET_PED_AS_GROUP_LEADER(int groupID)l
extern _native64(0x971D38760FBC02EF) void SET_PED_KEEP_TASK(Ped ped, bool toggle)l
extern _native64(0x49E50BDB8BA4DAB2) void UNK_0x49E50BDB8BA4DAB2(Ped ped, bool p1)l
extern _native64(0x9DE327631295B4C2) bool IS_PED_SWIMMING(Ped ped)l
extern _native64(0xC024869A53992F34) bool IS_PED_SWIMMING_UNDER_WATER(Ped ped)l
extern _native64(0x9AFEFF481A85AB2E) void SET_PED_COORDS_KEEP_VEHICLE(Ped ped, vector3 pos)l
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
extern _native64(0xAF8A94EDE7712BEF) void SET_PED_MOVEMENT_CLIPSET(Ped ped, const char* clipSet, float p2)l
extern _native64(0xAA74EC0CB0AAEA2C) void RESET_PED_MOVEMENT_CLIPSET(Ped ped, float p1)l
extern _native64(0x29A28F3F8CF6D854) void SET_PED_STRAFE_CLIPSET(Ped ped, const char* clipSet)l
extern _native64(0x20510814175EA477) void RESET_PED_STRAFE_CLIPSET(Ped ped)l
extern _native64(0x2622E35B77D3ACA2) void SET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped, const char* clipSet)l
extern _native64(0x97B0DB5B4AA74E77) void RESET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped)l
extern _native64(0xED34AB6C5CB36520) void SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped, const char* clipset)l
extern _native64(0x4AFE3690D7E0B5AC) void CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped)l
extern _native64(0x9DBA107B4937F809) void UNK_0x9DBA107B4937F809(any p0, const char* p1)l
extern _native64(0xC79196DCB36F6121) void UNK_0xC79196DCB36F6121(any p0)l
extern _native64(0x80054D7FCC70EEC6) void UNK_0x80054D7FCC70EEC6(any p0)l
extern _native64(0x530071295899A8C6) void SET_PED_IN_VEHICLE_CONTEXT(Ped ped, Hash context)l
extern _native64(0x22EF8FF8778030EB) void RESET_PED_IN_VEHICLE_CONTEXT(Ped ped)l
extern _native64(0x6EC47A344923E1ED) bool IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(Ped ped, const char* animDict, const char* anim)l
extern _native64(0x6C60394CB4F75E9A) void SET_PED_ALTERNATE_WALK_ANIM(Ped ped, const char* animDict, const char* animName, float p3, bool p4)l
extern _native64(0x8844BBFCE30AA9E9) void CLEAR_PED_ALTERNATE_WALK_ANIM(Ped ped, float p1)l
extern _native64(0x90A43CC281FFAB46) void SET_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, const char* animDictionary, const char* animationName, float p4, bool p5)l
extern _native64(0xD8D19675ED5FBDCE) void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, float p2)l
extern _native64(0xDDF803377F94AAA8) void SET_PED_GESTURE_GROUP(Ped ped, const char* animGroupGesture)l
extern _native64(0xBE22B26DD764C040) vector3 GET_ANIM_INITIAL_OFFSET_POSITION(const char* animDict, const char* animName, vector3 vec, vector3 Rot, float p8, int p9)l
extern _native64(0x4B805E6046EE9E47) vector3 GET_ANIM_INITIAL_OFFSET_ROTATION(const char* animDict, const char* animName, vector3 vec, vector3 Rot, float p8, int p9)l
extern _native64(0x67F3780DD425D4FC) int GET_PED_DRAWABLE_VARIATION(Ped ped, int componentId)l
extern _native64(0x27561561732A7842) int GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped ped, int componentId)l
extern _native64(0x04A355E041E004E6) int GET_PED_TEXTURE_VARIATION(Ped ped, int componentId)l
extern _native64(0x8F7156A3142A6BAD) int GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped ped, int componentId, int drawableId)l
extern _native64(0x5FAF9754E789FB47) int GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Ped ped, int propId)l
extern _native64(0xA6E7F1CEB523E171) int GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Ped ped, int propId, int drawableId)l
extern _native64(0xE3DD5F2A84B42281) int GET_PED_PALETTE_VARIATION(Ped ped, int componentId)l
extern _native64(0x9E30E91FB03A2CAF) bool UNK_0x9E30E91FB03A2CAF(any* p0, any* p1)l
extern _native64(0x1E77FA7A62EE6C4C) any UNK_0x1E77FA7A62EE6C4C(any p0)l
extern _native64(0xF033419D1B81FAE8) any UNK_0xF033419D1B81FAE8(any p0)l
extern _native64(0xE825F6B6CEA7671D) bool IS_PED_COMPONENT_VARIATION_VALID(Ped ped, int componentId, int drawableId, int textureId)l
extern _native64(0x262B14F48D29DE80) void SET_PED_COMPONENT_VARIATION(Ped ped, int componentId, int drawableId, int textureId, int paletteId)l
extern _native64(0xC8A9481A01E63C28) void SET_PED_RANDOM_COMPONENT_VARIATION(Ped ped, bool p1)l
extern _native64(0xC44AA05345C992C6) void SET_PED_RANDOM_PROPS(Ped ped)l
extern _native64(0x45EEE61580806D63) void SET_PED_DEFAULT_COMPONENT_VARIATION(Ped ped)l
extern _native64(0x137BBD05230DB22D) void SET_PED_BLEND_FROM_PARENTS(Ped ped, any p1, any p2, float p3, float p4)l
extern _native64(0x9414E18B9434C2FE) void SET_PED_HEAD_BLEND_DATA(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, bool isParent)l
extern _native64(0x2746BD9D88C5C5D0) bool _GET_PED_HEAD_BLEND_DATA(Ped ped, any* headBlendData)l
extern _native64(0x723538F61C647C5A) void UPDATE_PED_HEAD_BLEND_DATA(Ped ped, float shapeMix, float skinMix, float thirdMix)l
extern _native64(0x50B56988B170AFDF) void _SET_PED_EYE_COLOR(Ped ped, int index)l
extern _native64(0x48F44967FA05CC1E) void SET_PED_HEAD_OVERLAY(Ped ped, int overlayID, int index, float opacity)l
extern _native64(0xA60EF3B6461A4D43) int _GET_PED_HEAD_OVERLAY_VALUE(Ped ped, int overlayID)l
extern _native64(0xCF1CE768BB43480E) int _GET_NUM_HEAD_OVERLAY_VALUES(int overlayID)l
extern _native64(0x497BF74A7B9CB952) void _SET_PED_HEAD_OVERLAY_COLOR(Ped ped, int overlayID, int colorType, int colorID, int secondColorID)l
extern _native64(0x4CFFC65454C93A49) void _SET_PED_HAIR_COLOR(Ped ped, int colorID, int highlightColorID)l
extern _native64(0xE5C0CF872C2AD150) int _GET_NUM_HAIR_COLORS()l
extern _native64(0xD1F7CA1535D22818) int _GET_NUM_MAKEUP_COLORS()l
extern _native64(0x4852FC386E2E1BB5) void UNK_0x4852FC386E2E1BB5(any p0, any* p1, any* p2, any* p3)l
extern _native64(0x013E5CFC38CD5387) void UNK_0x013E5CFC38CD5387(any p0, any* p1, any* p2, any* p3)l
extern _native64(0xED6D8E27A43B8CDE) bool UNK_0xED6D8E27A43B8CDE(any p0)l
extern _native64(0xEA9960D07DADCF10) int UNK_0xEA9960D07DADCF10(any p0)l
extern _native64(0x3E802F11FBE27674) bool UNK_0x3E802F11FBE27674(any p0)l
extern _native64(0xF41B5D290C99A3D6) bool UNK_0xF41B5D290C99A3D6(any p0)l
extern _native64(0xE0D36E5D9E99CC21) bool _IS_PED_HAIR_COLOR_VALID(int colorID)l
extern _native64(0xAAA6A3698A69E048) any UNK_0xAAA6A3698A69E048(any p0)l
extern _native64(0x0525A2C2562F3CD4) bool _IS_PED_LIPSTICK_COLOR_VALID(int colorID)l
extern _native64(0x604E810189EE3A59) bool _IS_PED_BLUSH_COLOR_VALID(int colorID)l
extern _native64(0xC56FBF2F228E1DAC) any UNK_0xC56FBF2F228E1DAC(any p0, any p1, any p2)l
extern _native64(0x71A5C1DBA060049E) void _SET_PED_FACE_FEATURE(Ped ped, int index, float scale)l
extern _native64(0x654CD0A825161131) bool HAS_PED_HEAD_BLEND_FINISHED(Ped ped)l
extern _native64(0x4668D80430D6C299) void UNK_0x4668D80430D6C299(Ped ped)l
extern _native64(0xCC9682B8951C5229) void UNK_0xCC9682B8951C5229(Ped ped, RGB colour, int p4)l
extern _native64(0xA21C118553BBDF02) void UNK_0xA21C118553BBDF02(any p0)l
extern _native64(0x68D353AB88B97E0C) int _GET_FIRST_PARENT_ID_FOR_PED_TYPE(int type)l
extern _native64(0x5EF37013A6539C9D) int _GET_NUM_PARENT_PEDS_OF_TYPE(int type)l
extern _native64(0x39D55A620FCB6A3A) any UNK_0x39D55A620FCB6A3A(Ped ped, int p1, int drawableId, int textureId)l
extern _native64(0x66680A92700F43DF) bool UNK_0x66680A92700F43DF(Ped p0)l
extern _native64(0x5AAB586FFEC0FD96) void UNK_0x5AAB586FFEC0FD96(any p0)l
extern _native64(0x2B16A3BFF1FBCE49) bool _IS_PED_PROP_VALID(Ped ped, int componentId, int drawableId, int TextureId)l
extern _native64(0x784002A632822099) bool UNK_0x784002A632822099(Ped ped)l
extern _native64(0xF79F9DEF0AADE61A) void UNK_0xF79F9DEF0AADE61A(Ped ped)l
extern _native64(0x898CC20EA75BACD8) int GET_PED_PROP_INDEX(Ped ped, int componentId)l
extern _native64(0x93376B65A266EB5F) void SET_PED_PROP_INDEX(Ped ped, int componentId, int drawableId, int TextureId, bool attach)l
extern _native64(0x6FD7816A36615F48) void KNOCK_OFF_PED_PROP(Ped ped, bool p1, bool p2, bool p3, bool p4)l
extern _native64(0x0943E5B8E078E76E) void CLEAR_PED_PROP(Ped ped, int propId)l
extern _native64(0xCD8A7537A9B52F06) void CLEAR_ALL_PED_PROPS(Ped ped)l
extern _native64(0xAFF4710E2A0A6C12) void UNK_0xAFF4710E2A0A6C12(Ped ped)l
extern _native64(0xE131A28626F81AB2) int GET_PED_PROP_TEXTURE_INDEX(Ped ped, int componentId)l
extern _native64(0x1280804F7CFD2D6C) void UNK_0x1280804F7CFD2D6C(any p0)l
extern _native64(0x36C6984C3ED0C911) void UNK_0x36C6984C3ED0C911(any p0)l
extern _native64(0xB50EB4CCB29704AC) void UNK_0xB50EB4CCB29704AC(any p0)l
extern _native64(0xFEC9A3B1820F3331) bool UNK_0xFEC9A3B1820F3331(any p0)l
extern _native64(0x9F8AA94D6D97DBF4) void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)l
extern _native64(0x4F5F651ACCC9C4CF) void SET_PED_BOUNDS_ORIENTATION(Ped ped, float p1, float p2, float p3, float p4, float p5)l
extern _native64(0x2F25D9AEFA34FBA2) void REGISTER_TARGET(Ped ped, Ped target)l
extern _native64(0x9222F300BF8354FE) void REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius)l
extern _native64(0x876046A8E3A4B71C) Ped GET_RANDOM_PED_AT_COORD(vector3 vec, vector3 Radius, int pedType)l
extern _native64(0xC33AB876A77F8164) bool GET_CLOSEST_PED(vector3 vec, float radius, bool p4, bool p5, Ped* outPed, bool p7, bool p8, int pedType)l
extern _native64(0x14F19A8782C8071E) void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(bool value)l
extern _native64(0x03EA03AF85A85CB7) bool UNK_0x03EA03AF85A85CB7(Ped ped, bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, any p8)l
extern _native64(0xDED5AF5A0EA4B297) void UNK_0xDED5AF5A0EA4B297(Ped driver, float p1)l
extern _native64(0xB195FFA8042FC5C3) void SET_DRIVER_ABILITY(Ped driver, float ability)l
extern _native64(0xA731F608CA104E3C) void SET_DRIVER_AGGRESSIVENESS(Ped driver, float aggressiveness)l
extern _native64(0x128F79EDCECE4FD5) bool CAN_PED_RAGDOLL(Ped ped)l
extern _native64(0xAE99FB955581844A) bool SET_PED_TO_RAGDOLL(Ped ped, int time1, int time2, int ragdollType, bool p4, bool p5, bool p6)l
extern _native64(0xD76632D99E4966C8) bool SET_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int time, int p2, int ragdollType, vector3 vec, float p7, float p8, float p9, float p10, float p11, float p12, float p13)l
extern _native64(0xF0A4F1BBF4FA7497) void SET_PED_RAGDOLL_ON_COLLISION(Ped ped, bool toggle)l
extern _native64(0x47E4E977581C5B55) bool IS_PED_RAGDOLL(Ped ped)l
extern _native64(0xE3B6097CC25AA69E) bool IS_PED_RUNNING_RAGDOLL_TASK(Ped ped)l
extern _native64(0x01F6594B923B9251) any SET_PED_RAGDOLL_FORCE_FALL(Ped ped)l
extern _native64(0x9FA4664CF62E47E8) void RESET_PED_RAGDOLL_TIMER(Ped ped)l
extern _native64(0xB128377056A54E2A) void SET_PED_CAN_RAGDOLL(Ped ped, bool toggle)l
extern _native64(0xD1871251F3B5ACD7) bool UNK_0xD1871251F3B5ACD7(Ped ped)l
extern _native64(0x2AFE52F782F25775) bool IS_PED_RUNNING_MOBILE_PHONE_TASK(Ped ped)l
extern _native64(0xA3F3564A5B3646C0) bool UNK_0xA3F3564A5B3646C0(Ped ped)l
extern _native64(0x26695EC767728D84) void _SET_PED_RAGDOLL_BLOCKING_FLAGS(Ped ped, int flags)l
extern _native64(0xD86D101FCFD00A4B) void _RESET_PED_RAGDOLL_BLOCKING_FLAGS(Ped ped, int flags)l
extern _native64(0xC7F76DF27A5045A1) void SET_PED_ANGLED_DEFENSIVE_AREA(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8, bool p9)l
extern _native64(0x9D3151A373974804) void SET_PED_SPHERE_DEFENSIVE_AREA(Ped ped, vector3 vec, float radius, bool p5, bool p6)l
extern _native64(0xF9B8F91AAD3B953E) void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(Ped ped, Ped target, vector3 Offset, float radius, bool p6)l
extern _native64(0xE4723DB6E736CCFF) void UNK_0xE4723DB6E736CCFF(Ped ped, any p1, float p2, float p3, float p4, float p5, bool p6)l
extern _native64(0x4EF47FE21698A8B6) void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9, bool p10)l
extern _native64(0x413C6C763A4AFFAD) void SET_PED_DEFENSIVE_AREA_DIRECTION(Ped ped, float p1, float p2, float p3, bool p4)l
extern _native64(0x74D4E028107450A9) void REMOVE_PED_DEFENSIVE_AREA(Ped ped, bool toggle)l
extern _native64(0x3C06B8786DD94CD1) vector3 GET_PED_DEFENSIVE_AREA_POSITION(Ped ped, bool p1)l
extern _native64(0xBA63D9FE45412247) bool UNK_0xBA63D9FE45412247(Ped ped, bool p1)l
extern _native64(0x8421EB4DA7E391B9) void SET_PED_PREFERRED_COVER_SET(Ped ped, any itemSet)l
extern _native64(0xFDDB234CF74073D9) void REMOVE_PED_PREFERRED_COVER_SET(Ped ped)l
extern _native64(0x8D8ACD8388CD99CE) void REVIVE_INJURED_PED(Ped ped)l
extern _native64(0x71BC8E838B9C6035) void RESURRECT_PED(Ped ped)l
extern _native64(0x98EFA132A4117BE1) void SET_PED_NAME_DEBUG(Ped ped, const char* name)l
extern _native64(0xE0AF41401ADF87E3) vector3 GET_PED_EXTRACTED_DISPLACEMENT(Ped ped, bool worldSpace)l
extern _native64(0x5BA7919BED300023) any SET_PED_DIES_WHEN_INJURED(Ped ped, bool toggle)l
extern _native64(0x97A790315D3831FD) any SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, bool toggle)l
extern _native64(0xF9ACF4A08098EA25) void UNK_0xF9ACF4A08098EA25(Ped ped, bool p1)l
extern _native64(0x3AC1F7B898F30C05) any RESET_PED_VISIBLE_DAMAGE(Ped ped)l
extern _native64(0x816F6981C60BF53B) void APPLY_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, any p1, float p2, float p3, any p4)l
extern _native64(0x83F7E01C7B769A26) void APPLY_PED_BLOOD(Ped ped, int boneIndex, vector3 Rot, const char* woundType)l
extern _native64(0x3311E47B91EDCBBC) void APPLY_PED_BLOOD_BY_ZONE(Ped ped, any p1, float p2, float p3, any* p4)l
extern _native64(0xEF0D582CBF2D9B0F) void APPLY_PED_BLOOD_SPECIFIC(Ped ped, any p1, float p2, float p3, float p4, float p5, any p6, float p7, any* p8)l
extern _native64(0x397C38AA7B4A5F83) void APPLY_PED_DAMAGE_DECAL(Ped ped, int p1, float p2, float p3, float p4, float p5, float p6, int p7, bool p8, const char* p9)l
extern _native64(0x46DF918788CB093F) void APPLY_PED_DAMAGE_PACK(Ped ped, const char* damagePack, float damage, float mult)l
extern _native64(0x8FE22675A5A45817) void CLEAR_PED_BLOOD_DAMAGE(Ped ped)l
extern _native64(0x56E3B78C5408D9F4) void CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, int p1)l
extern _native64(0x62AB793144DE75DC) void HIDE_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, any p1, bool p2)l
extern _native64(0x523C79AEEFCC4A2A) void CLEAR_PED_DAMAGE_DECAL_BY_ZONE(Ped ped, int p1, const char* p2)l
extern _native64(0x71EAB450D86954A1) any GET_PED_DECORATIONS_STATE(Ped ped)l
extern _native64(0x2B694AFCF64E6994) void UNK_0x2B694AFCF64E6994(Ped ped, bool p1)l
extern _native64(0x9C720776DAA43E7E) void CLEAR_PED_WETNESS(Ped ped)l
extern _native64(0x44CB6447D2571AA0) void SET_PED_WETNESS_HEIGHT(Ped ped, float height)l
extern _native64(0xB5485E4907B53019) void SET_PED_WETNESS_ENABLED_THIS_FRAME(Ped ped)l
extern _native64(0x6585D955A68452A5) any UNK_0x6585D955A68452A5(Ped ped)l
extern _native64(0x27B0405F59637D1F) void SET_PED_SWEAT(Ped ped, float sweat)l
extern _native64(0x5F5D1665E352A839) void _SET_PED_DECORATION(Ped ped, Hash collection, Hash overlay)l
extern _native64(0x5619BFA07CFD7833) void _SET_PED_FACIAL_DECORATION(Ped ped, Hash collection, Hash overlay)l
extern _native64(0x9FD452BFBE7A7A8B) int _GET_TATTOO_ZONE(Hash collection, Hash overlay)l
extern _native64(0x0E5173C163976E38) void CLEAR_PED_DECORATIONS(Ped ped)l
extern _native64(0xE3B27E70CEAB9F0C) void _CLEAR_PED_FACIAL_DECORATIONS(Ped ped)l
extern _native64(0x11B499C1E0FF8559) bool WAS_PED_SKELETON_UPDATED(Ped ped)l
extern _native64(0x17C07FC640E86B4E) vector3 GET_PED_BONE_COORDS(Ped ped, int boneId, vector3 offset)l
extern _native64(0x418EF2A1BCE56685) void CREATE_NM_MESSAGE(bool startImmediately, int messageId)l
extern _native64(0xB158DFCCC56E5C5B) void GIVE_PED_NM_MESSAGE(Ped ped)l
extern _native64(0x1B5C85C612E5256E) any ADD_SCENARIO_BLOCKING_AREA(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9)l
extern _native64(0xD37401D78A929A49) void REMOVE_SCENARIO_BLOCKING_AREAS()l
extern _native64(0x31D16B74C6E29D66) void REMOVE_SCENARIO_BLOCKING_AREA(any p0, bool p1)l
extern _native64(0x28157D43CF600981) void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x1BF094736DD62C2E) bool IS_PED_USING_SCENARIO(Ped ped, const char* scenario)l
extern _native64(0x57AB4A3080F85143) bool IS_PED_USING_ANY_SCENARIO(Ped ped)l
extern _native64(0xFE07FF6495D52E2A) any UNK_0xFE07FF6495D52E2A(any p0, any p1, any p2, any p3)l
extern _native64(0x9A77DFD295E29B09) void UNK_0x9A77DFD295E29B09(any p0, bool p1)l
extern _native64(0x25361A96E0F7E419) any UNK_0x25361A96E0F7E419(any p0, any p1, any p2, any p3)l
extern _native64(0xEC6935EBE0847B90) any UNK_0xEC6935EBE0847B90(any p0, any p1, any p2, any p3)l
extern _native64(0xA3A9299C4F2ADB98) void UNK_0xA3A9299C4F2ADB98(any p0)l
extern _native64(0xF1C03A5352243A30) void UNK_0xF1C03A5352243A30(any p0)l
extern _native64(0xEEED8FAFEC331A70) any UNK_0xEEED8FAFEC331A70(any p0, any p1, any p2, any p3)l
extern _native64(0x425AECF167663F48) void UNK_0x425AECF167663F48(Ped ped, bool p1)l
extern _native64(0x5B6010B3CBC29095) void UNK_0x5B6010B3CBC29095(any p0, bool p1)l
extern _native64(0xCEDA60A74219D064) void UNK_0xCEDA60A74219D064(any p0, bool p1)l
extern _native64(0xE1E65CA8AC9C00ED) void PLAY_FACIAL_ANIM(Ped ped, const char* animName, const char* animDict)l
extern _native64(0xFFC24B988B938B38) void SET_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped, const char* animName, const char* animDict)l
extern _native64(0x726256CC1EEB182F) void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped)l
extern _native64(0xBAF20C5432058024) void SET_PED_CAN_PLAY_GESTURE_ANIMS(Ped ped, bool toggle)l
extern _native64(0xF833DDBA3B104D43) void SET_PED_CAN_PLAY_VISEME_ANIMS(Ped ped, bool toggle, bool p2)l
extern _native64(0x33A60D8BDD6E508C) void UNK_0x33A60D8BDD6E508C(Ped ped, bool p1)l
extern _native64(0x6373D1349925A70E) void SET_PED_CAN_PLAY_AMBIENT_ANIMS(Ped ped, bool toggle)l
extern _native64(0x0EB0585D15254740) void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Ped ped, bool toggle)l
extern _native64(0xC2EE020F5FB4DB53) void UNK_0xC2EE020F5FB4DB53(Ped ped)l
extern _native64(0x6C3B4D6D13B4C841) void SET_PED_CAN_ARM_IK(Ped ped, bool toggle)l
extern _native64(0xC11C18092C5530DC) void SET_PED_CAN_HEAD_IK(Ped ped, bool toggle)l
extern _native64(0x73518ECE2485412B) void SET_PED_CAN_LEG_IK(Ped ped, bool toggle)l
extern _native64(0xF2B7106D37947CE0) void SET_PED_CAN_TORSO_IK(Ped ped, bool toggle)l
extern _native64(0xF5846EDB26A98A24) void UNK_0xF5846EDB26A98A24(Ped ped, bool p1)l
extern _native64(0x6647C5F6F5792496) void UNK_0x6647C5F6F5792496(Ped ped, bool p1)l
extern _native64(0xEC4686EC06434678) void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Ped ped, bool toggle)l
extern _native64(0x5CD3CB88A7F8850D) bool IS_PED_HEADTRACKING_PED(Ped ped1, Ped ped2)l
extern _native64(0x813A0A7C9D2E831F) bool IS_PED_HEADTRACKING_ENTITY(Ped ped, Entity entity)l
extern _native64(0xCD17B554996A8D9E) void SET_PED_PRIMARY_LOOKAT(Ped ped, Ped lookAt)l
extern _native64(0x78C4E9961DB3EB5B) void UNK_0x78C4E9961DB3EB5B(any p0, any p1)l
extern _native64(0x82A3D6D9CC2CB8E3) void SET_PED_CLOTH_PRONE(any p0, any p1)l
extern _native64(0xA660FAF550EB37E5) void UNK_0xA660FAF550EB37E5(any p0, bool p1)l
extern _native64(0x1913FE4CBF41C463) void SET_PED_CONFIG_FLAG(Ped ped, int flagId, bool value)l
extern _native64(0xC1E8A365BF3B29F2) void SET_PED_RESET_FLAG(Ped ped, int flagId, bool doReset)l
extern _native64(0x7EE53118C892B513) bool GET_PED_CONFIG_FLAG(Ped ped, int flagId, bool p2)l
extern _native64(0xAF9E59B1B1FBF2A0) bool GET_PED_RESET_FLAG(Ped ped, int flagId)l
extern _native64(0x0BDDB8D9EC6BCF3C) void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Ped ped, int index)l
extern _native64(0x6B7A646C242A7059) void SET_PED_CAN_EVASIVE_DIVE(Ped ped, bool toggle)l
extern _native64(0x414641C26E105898) bool IS_PED_EVASIVE_DIVING(Ped ped, Entity* evadingEntity)l
extern _native64(0x96A05E4FB321B1BA) void SET_PED_SHOOTS_AT_COORD(Ped ped, vector3 vec, bool toggle)l
extern _native64(0xE163A4BCE4DE6F11) void SET_PED_MODEL_IS_SUPPRESSED(Ped ped, bool toggle)l
extern _native64(0xB47BD05FA66B40CF) void STOP_ANY_PED_MODEL_BEING_SUPPRESSED()l
extern _native64(0x638C03B0F9878F57) void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Ped ped, bool toggle)l
extern _native64(0x7FB17BA2E7DECA5B) void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, bool toggle)l
extern _native64(0xE43A13C9E4CCCBCF) void UNK_0xE43A13C9E4CCCBCF(Ped ped, bool p1)l
extern _native64(0xDF993EE5E90ABA25) void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, bool toggle)l
extern _native64(0x54C7C4A94367717E) void GIVE_PED_HELMET(Ped ped, bool cannotRemove, int helmetFlag, int textureIndex)l
extern _native64(0xA7B2458D0AD6DED8) void REMOVE_PED_HELMET(Ped ped, bool instantly)l
extern _native64(0x14590DDBEDB1EC85) bool UNK_0x14590DDBEDB1EC85(Ped ped)l
extern _native64(0x560A43136EB58105) void SET_PED_HELMET(Ped ped, bool canWearHelmet)l
extern _native64(0xC0E78D5C2CE3EB25) void SET_PED_HELMET_FLAG(Ped ped, int helmetFlag)l
extern _native64(0x26D83693ED99291C) void SET_PED_HELMET_PROP_INDEX(Ped ped, int propIndex)l
extern _native64(0xF1550C4BD22582E2) void SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int textureIndex)l
extern _native64(0xF33BDFE19B309B19) bool IS_PED_WEARING_HELMET(Ped ped)l
extern _native64(0x687C0B594907D2E8) void UNK_0x687C0B594907D2E8(Ped ped)l
extern _native64(0x451294E859ECC018) any UNK_0x451294E859ECC018(any p0)l
extern _native64(0x9D728C1E12BF5518) any UNK_0x9D728C1E12BF5518(any p0)l
extern _native64(0xF2385935BFFD4D92) bool UNK_0xF2385935BFFD4D92(any p0)l
extern _native64(0x332B562EEDA62399) void SET_PED_TO_LOAD_COVER(Ped ped, bool toggle)l
extern _native64(0xCB7553CDCEF4A735) void SET_PED_CAN_COWER_IN_COVER(Ped ped, bool toggle)l
extern _native64(0xC514825C507E3736) void SET_PED_CAN_PEEK_IN_COVER(Ped ped, bool toggle)l
extern _native64(0x94D94BF1A75AED3D) void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Ped ped, bool toggle)l
extern _native64(0xC396F5B86FF9FEBD) void SET_PED_LEG_IK_MODE(Ped ped, int mode)l
extern _native64(0x0A986918B102B448) void SET_PED_MOTION_BLUR(Ped ped, bool toggle)l
extern _native64(0xED7F7EFE9FABF340) void SET_PED_CAN_SWITCH_WEAPON(Ped ped, bool toggle)l
extern _native64(0xEEB64139BA29A7CF) void SET_PED_DIES_INSTANTLY_IN_WATER(Ped ped, bool toggle)l
extern _native64(0x1A330D297AAC6BC1) void UNK_0x1A330D297AAC6BC1(Ped ped, int p1)l
extern _native64(0xC158D28142A34608) void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped)l
extern _native64(0x5917BBA32D06C230) void SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float p1)l
extern _native64(0x4D9CA1009AFBD057) void SET_PED_COMBAT_MOVEMENT(Ped ped, int combatMovement)l
extern _native64(0xDEA92412FCAEB3F5) int GET_PED_COMBAT_MOVEMENT(Ped ped)l
extern _native64(0xC7622C0D36B2FDA8) void SET_PED_COMBAT_ABILITY(Ped ped, int p1)l
extern _native64(0x3C606747B23E497B) void SET_PED_COMBAT_RANGE(Ped ped, int p1)l
extern _native64(0xF9D9F7F2DB8E2FA0) any GET_PED_COMBAT_RANGE(Ped ped)l
extern _native64(0x9F7794730795E019) void SET_PED_COMBAT_ATTRIBUTES(Ped ped, int attributeIndex, bool enabled)l
extern _native64(0x0703B9079823DA4A) void SET_PED_TARGET_LOSS_RESPONSE(Ped ped, int responseType)l
extern _native64(0xDCCA191DF9980FD7) bool UNK_0xDCCA191DF9980FD7(Ped ped)l
extern _native64(0xFD4CCDBCC59941B7) bool IS_PED_PERFORMING_STEALTH_KILL(Ped ped)l
extern _native64(0xEBD0EDBA5BE957CF) bool UNK_0xEBD0EDBA5BE957CF(Ped ped)l
extern _native64(0x863B23EFDE9C5DF2) bool IS_PED_BEING_STEALTH_KILLED(Ped ped)l
extern _native64(0x18A3E9EE1297FD39) Ped GET_MELEE_TARGET_FOR_PED(Ped ped)l
extern _native64(0xF9800AA1A771B000) bool WAS_PED_KILLED_BY_STEALTH(Ped ped)l
extern _native64(0x7F08E26039C7347C) bool WAS_PED_KILLED_BY_TAKEDOWN(Ped ped)l
extern _native64(0x61767F73EACEED21) bool UNK_0x61767F73EACEED21(Ped ped)l
extern _native64(0x70A2D1137C8ED7C9) void SET_PED_FLEE_ATTRIBUTES(Ped ped, int attributes, bool p2)l
extern _native64(0xA549131166868ED3) void SET_PED_COWER_HASH(Ped ped, const char* p1)l
extern _native64(0x2016C603D6B8987C) void UNK_0x2016C603D6B8987C(any p0, bool p1)l
extern _native64(0x46F2193B3AD1D891) void SET_PED_STEERS_AROUND_PEDS(Ped ped, bool toggle)l
extern _native64(0x1509C089ADC208BF) void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, bool toggle)l
extern _native64(0xEB6FB9D48DDE23EC) void SET_PED_STEERS_AROUND_VEHICLES(Ped ped, bool toggle)l
extern _native64(0xA9B61A329BFDCBEA) void UNK_0xA9B61A329BFDCBEA(any p0, bool p1)l
extern _native64(0x570389D1C3DE3C6B) void UNK_0x570389D1C3DE3C6B(any p0)l
extern _native64(0x576594E8D64375E2) void UNK_0x576594E8D64375E2(any p0, bool p1)l
extern _native64(0xA52D5247A4227E14) void UNK_0xA52D5247A4227E14(any p0)l
extern _native64(0x083961498679DC9F) bool IS_ANY_PED_NEAR_POINT(vector3 vec, float radius)l
extern _native64(0x2208438012482A1A) void UNK_0x2208438012482A1A(Ped ped, bool p1, bool p2)l
extern _native64(0xFCF37A457CB96DC0) bool UNK_0xFCF37A457CB96DC0(any p0, float p1, float p2, float p3, float p4)l
extern _native64(0x7D7A2E43E74E2EB8) void UNK_0x7D7A2E43E74E2EB8(any p0)l
extern _native64(0x2BC338A7B21F4608) void GET_PED_FLOOD_INVINCIBILITY(Ped ped, bool p1)l
extern _native64(0xCD018C591F94CB43) void UNK_0xCD018C591F94CB43(any p0, bool p1)l
extern _native64(0x75BA1CB3B7D40CAF) void UNK_0x75BA1CB3B7D40CAF(Ped ped, bool p1)l
extern _native64(0x91C8E617F64188AC) bool IS_TRACKED_PED_VISIBLE(Ped ped)l
extern _native64(0x511F1A683387C7E2) any UNK_0x511F1A683387C7E2(any p0)l
extern _native64(0x4C5E1F087CD10BB7) bool IS_PED_TRACKED(Ped ped)l
extern _native64(0x8507BCB710FA6DC0) bool HAS_PED_RECEIVED_EVENT(any p0, any p1)l
extern _native64(0x6CD5A433374D4CFB) bool UNK_0x6CD5A433374D4CFB(any p0, any p1)l
extern _native64(0x9C6A6C19B6C0C496) bool UNK_0x9C6A6C19B6C0C496(Ped p0, any* p1)l
extern _native64(0x3F428D08BE5AAE31) int GET_PED_BONE_INDEX(Ped ped, int boneId)l
extern _native64(0x2057EF813397A772) int GET_PED_RAGDOLL_BONE_INDEX(Ped ped, int bone)l
extern _native64(0xBF29516833893561) void SET_PED_ENVEFF_SCALE(Ped ped, float value)l
extern _native64(0x9C14D30395A51A3C) float GET_PED_ENVEFF_SCALE(Ped ped)l
extern _native64(0xD2C5AA0C0E8D0F1E) void SET_ENABLE_PED_ENVEFF_SCALE(Ped ped, bool toggle)l
extern _native64(0x110F526AB784111F) void UNK_0x110F526AB784111F(Ped ped, float p1)l
extern _native64(0xD69411AA0CEBF9E9) void UNK_0xD69411AA0CEBF9E9(Ped ped, int p1, int p2, int p3)l
extern _native64(0x1216E0BFA72CC703) void UNK_0x1216E0BFA72CC703(any p0, any p1)l
extern _native64(0x2B5AA717A181FB4C) void UNK_0x2B5AA717A181FB4C(any p0, bool p1)l
extern _native64(0xB8B52E498014F5B0) bool UNK_0xB8B52E498014F5B0(Ped ped)l
extern _native64(0x8C18E0F9080ADD73) int CREATE_SYNCHRONIZED_SCENE(vector3 vec, float roll, float pitch, float yaw, int p6)l
extern _native64(0x62EC273D00187DCA) int UNK_0x62EC273D00187DCA(vector3 vec, float radius, Hash object)l
extern _native64(0x25D39B935A038A26) bool IS_SYNCHRONIZED_SCENE_RUNNING(int sceneId)l
extern _native64(0x6ACF6B7225801CD7) void SET_SYNCHRONIZED_SCENE_ORIGIN(int sceneID, vector3 vec, float roll, float pitch, float yaw, bool p7)l
extern _native64(0x734292F4F0ABF6D0) void SET_SYNCHRONIZED_SCENE_PHASE(int sceneID, float phase)l
extern _native64(0xE4A310B1D7FA73CC) float GET_SYNCHRONIZED_SCENE_PHASE(int sceneID)l
extern _native64(0xB6C49F8A5E295A5D) void SET_SYNCHRONIZED_SCENE_RATE(int sceneID, float rate)l
extern _native64(0xD80932D577274D40) float GET_SYNCHRONIZED_SCENE_RATE(int sceneID)l
extern _native64(0xD9A897A4C6C2974F) void SET_SYNCHRONIZED_SCENE_LOOPED(int sceneID, bool toggle)l
extern _native64(0x62522002E0C391BA) bool IS_SYNCHRONIZED_SCENE_LOOPED(int sceneID)l
extern _native64(0x394B9CD12435C981) void _SET_SYNCHRONIZED_SCENE_OCCLUSION_PORTAL(any sceneID, bool p1)l
extern _native64(0x7F2F4F13AC5257EF) bool UNK_0x7F2F4F13AC5257EF(any p0)l
extern _native64(0x272E4723B56A3B96) void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(int sceneID, Entity entity, int boneIndex)l
extern _native64(0x6D38F1F04CBB37EA) void DETACH_SYNCHRONIZED_SCENE(int sceneID)l
extern _native64(0xCD9CC7E200A52A6F) void _DISPOSE_SYNCHRONIZED_SCENE(int scene)l
extern _native64(0xF28965D04F570DCA) bool FORCE_PED_MOTION_STATE(Ped ped, Hash motionStateHash, bool p2, bool p3, bool p4)l
extern _native64(0xF60165E1D2C5370B) bool UNK_0xF60165E1D2C5370B(Ped ped, any* p1, any* p2)l
extern _native64(0x433083750C5E064A) void SET_PED_MAX_MOVE_BLEND_RATIO(Ped ped, float value)l
extern _native64(0x01A898D26E2333DD) void SET_PED_MIN_MOVE_BLEND_RATIO(Ped ped, float value)l
extern _native64(0x085BF80FA50A39D1) void SET_PED_MOVE_RATE_OVERRIDE(Ped ped, float value)l
extern _native64(0x46B05BCAE43856B0) bool UNK_0x46B05BCAE43856B0(Ped ped, int flag)l
extern _native64(0xCFF869CBFA210D82) int GET_PED_NEARBY_VEHICLES(Ped ped, int* sizeAndVehs)l
extern _native64(0x23F8F5FC7E8C4A6B) int GET_PED_NEARBY_PEDS(Ped ped, int* sizeAndPeds, int ignore)l
extern _native64(0x7350823473013C02) bool UNK_0x7350823473013C02(Ped ped)l
extern _native64(0x00E73468D085F745) bool IS_PED_USING_ACTION_MODE(Ped ped)l
extern _native64(0xD75ACCF5E0FB5367) void SET_PED_USING_ACTION_MODE(Ped ped, bool p1, any p2, const char* action)l
extern _native64(0x781DE8FA214E87D2) void UNK_0x781DE8FA214E87D2(Ped ped, const char* p1)l
extern _native64(0x364DF566EC833DE2) void SET_PED_CAPSULE(Ped ped, float value)l
extern _native64(0x4462658788425076) any REGISTER_PEDHEADSHOT(Ped ped)l
extern _native64(0x953563CE563143AF) any UNK_0x953563CE563143AF(any p0)l
extern _native64(0x96B1361D9B24C2FF) void UNREGISTER_PEDHEADSHOT(Ped ped)l
extern _native64(0xA0A9668F158129A2) int IS_PEDHEADSHOT_VALID(int handle)l
extern _native64(0x7085228842B13A67) bool IS_PEDHEADSHOT_READY(int handle)l
extern _native64(0xDB4EACD4AD0A5D6B) const char* GET_PEDHEADSHOT_TXD_STRING(int handle)l
extern _native64(0xF0DAEF2F545BEE25) bool UNK_0xF0DAEF2F545BEE25(any p0)l
extern _native64(0x5D517B27CF6ECD04) void UNK_0x5D517B27CF6ECD04(any p0)l
extern _native64(0xEBB376779A760AA8) any UNK_0xEBB376779A760AA8()l
extern _native64(0x876928DDDFCCC9CD) any UNK_0x876928DDDFCCC9CD()l
extern _native64(0xE8A169E666CBC541) any UNK_0xE8A169E666CBC541()l
extern _native64(0xC1F6EBF9A3D55538) void UNK_0xC1F6EBF9A3D55538(any p0, any p1)l
extern _native64(0x600048C60D5C2C51) void UNK_0x600048C60D5C2C51(any p0)l
extern _native64(0x2DF9038C90AD5264) void UNK_0x2DF9038C90AD5264(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration)l
extern _native64(0xB2AFF10216DEFA2F) void UNK_0xB2AFF10216DEFA2F(vector3 vec, float p3, float p4, float p5, float p6, int interiorFlags, float scale, int duration)l
extern _native64(0xFEE4A5459472A9F8) void UNK_0xFEE4A5459472A9F8()l
extern _native64(0x3C67506996001F5E) any UNK_0x3C67506996001F5E()l
extern _native64(0xA586FBEB32A53DBB) any UNK_0xA586FBEB32A53DBB()l
extern _native64(0xF445DE8DA80A1792) any UNK_0xF445DE8DA80A1792()l
extern _native64(0xA635C11B8C44AFC2) any UNK_0xA635C11B8C44AFC2()l
extern _native64(0x280C7E3AC7F56E90) void UNK_0x280C7E3AC7F56E90(any p0, any* p1, any* p2, any* p3)l
extern _native64(0xB782F8238512BAD5) void UNK_0xB782F8238512BAD5(any p0, any* p1)l
extern _native64(0xC32779C16FCEECD9) void SET_IK_TARGET(Ped ped, int p1, Ped targetPed, int boneLookAt, vector3 vec, any p7, int duration, int duration1)l
extern _native64(0xED3C76ADFA6D07C4) void UNK_0xED3C76ADFA6D07C4(any p0)l
extern _native64(0x290E2780BB7AA598) void REQUEST_ACTION_MODE_ASSET(const char* asset)l
extern _native64(0xE4B5F4BF2CB24E65) bool HAS_ACTION_MODE_ASSET_LOADED(const char* asset)l
extern _native64(0x13E940F88470FA51) void REMOVE_ACTION_MODE_ASSET(const char* asset)l
extern _native64(0x2A0A62FCDEE16D4F) void REQUEST_STEALTH_MODE_ASSET(const char* asset)l
extern _native64(0xE977FC5B08AF3441) bool HAS_STEALTH_MODE_ASSET_LOADED(const char* asset)l
extern _native64(0x9219857D21F0E842) void REMOVE_STEALTH_MODE_ASSET(const char* asset)l
extern _native64(0xDC2C5C242AAC342B) void SET_PED_LOD_MULTIPLIER(Ped ped, float multiplier)l
extern _native64(0xE861D0B05C7662B8) void UNK_0xE861D0B05C7662B8(any p0, bool p1, any p2)l
extern _native64(0x129466ED55140F8D) void UNK_0x129466ED55140F8D(Ped ped, bool toggle)l
extern _native64(0xCB968B53FC7F916D) void UNK_0xCB968B53FC7F916D(any p0, bool p1, any p2, any p3)l
extern _native64(0x68772DB2B2526F9F) bool UNK_0x68772DB2B2526F9F(Ped ped, vector3 vec, float range)l
extern _native64(0x06087579E7AA85A9) bool UNK_0x06087579E7AA85A9(any p0, any p1, float p2, float p3, float p4, float p5)l
extern _native64(0xD8C3BE3EE94CAF2D) void UNK_0xD8C3BE3EE94CAF2D(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xD33DAA36272177C4) void UNK_0xD33DAA36272177C4(Ped ped)l
extern _native64(0x83A169EABCDB10A2) void UNK_0x83A169EABCDB10A2(any p0, any p1)l
extern _native64(0x288DF530C92DAD6F) void UNK_0x288DF530C92DAD6F(any p0, float p1)l
#pragma endregion //}
#pragma region VEHICLE //{
extern _native64(0xAF35D0D2583051B0) Vehicle CREATE_VEHICLE(Hash modelHash, vector3 vec, float heading, bool isNetwork, bool p6)l
extern _native64(0xEA386986E786A54F) void DELETE_VEHICLE(Vehicle* vehicle)l
extern _native64(0x7D6F9A3EF26136A0) void UNK_0x7D6F9A3EF26136A0(Vehicle vehicle, bool p1, bool p2)l
extern _native64(0x5D14D4154BFE7B2C) void SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(Vehicle veh, bool toggle)l
extern _native64(0xE6B0E8CFC3633BF0) int UNK_0xE6B0E8CFC3633BF0(Vehicle vehicle)l
extern _native64(0x423E8DE37D934D89) bool IS_VEHICLE_MODEL(Vehicle vehicle, Hash model)l
extern _native64(0xF6086BC836400876) bool DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(int vehicleGenerator)l
extern _native64(0x9DEF883114668116) int CREATE_SCRIPT_VEHICLE_GENERATOR(vector3 vec, float heading, float p4, float p5, Hash modelHash, int p7, int p8, int p9, int p10, bool p11, bool p12, bool p13, bool p14, bool p15, int p16)l
extern _native64(0x22102C9ABFCF125D) void DELETE_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator)l
extern _native64(0xD9D620E0AC6DC4B0) void SET_SCRIPT_VEHICLE_GENERATOR(any vehicleGenerator, bool enabled)l
extern _native64(0xC12321827687FE4D) void SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(vector3 vec_1, vector3 vec_2, bool p6, bool p7)l
extern _native64(0x34AD89078831A4BC) void SET_ALL_VEHICLE_GENERATORS_ACTIVE()l
extern _native64(0x608207E7A8FB787C) void SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(bool active)l
extern _native64(0x9A75585FB2E54FAD) void UNK_0x9A75585FB2E54FAD(float p0, float p1, float p2, float p3)l
extern _native64(0x0A436B8643716D14) void UNK_0x0A436B8643716D14()l
extern _native64(0x49733E92263139D1) bool SET_VEHICLE_ON_GROUND_PROPERLY(Vehicle vehicle, float p1)l
extern _native64(0xE023E8AC4EF7C117) any SET_ALL_VEHICLES_SPAWN(Vehicle p0, bool p1, bool p2, bool p3)l
extern _native64(0xB497F06B288DCFDF) bool IS_VEHICLE_STUCK_ON_ROOF(Vehicle vehicle)l
extern _native64(0xB72E26D81006005B) void ADD_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)l
extern _native64(0xC53EB42A499A7E90) void REMOVE_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)l
extern _native64(0x5721B434AD84D57A) bool IS_VEHICLE_STOPPED(Vehicle vehicle)l
extern _native64(0x24CB2137731FFE89) int GET_VEHICLE_NUMBER_OF_PASSENGERS(Vehicle vehicle)l
extern _native64(0xA7C4F2C6E744A550) int GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vehicle vehicle)l
extern _native64(0x2AD93716F184EDA4) int GET_VEHICLE_MODEL_NUMBER_OF_SEATS(Hash modelHash)l
extern _native64(0xF7F203E31F96F6A1) bool UNK_0xF7F203E31F96F6A1(Vehicle vehicle, bool flag)l
extern _native64(0xE33FFA906CE74880) bool UNK_0xE33FFA906CE74880(Vehicle vehicle, any p1)l
extern _native64(0x245A6883D966D537) void SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0xB3B3359379FE77D3) void SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0xEAE6DCC7EEE3DB1D) void SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native64(0xD4B8E3D1917BC86B) void UNK_0xD4B8E3D1917BC86B(bool toggle)l
extern _native64(0x90B6DA738A9A25DA) void _SET_SOME_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float value)l
extern _native64(0x26324F33423F3CC3) void SET_FAR_DRAW_VEHICLES(bool toggle)l
extern _native64(0xCAA15F13EBD417FF) any SET_NUMBER_OF_PARKED_VEHICLES(int value)l
extern _native64(0xB664292EAECF7FA6) void SET_VEHICLE_DOORS_LOCKED(Vehicle vehicle, int doorLockStatus)l
extern _native64(0xBE70724027F85BCD) void SET_PED_TARGETTABLE_VEHICLE_DESTROY(Vehicle vehicle, int vehicleComponent, int destroyType)l
extern _native64(0xD8050E0EB60CF274) void DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(Vehicle vehicle, bool toggle)l
extern _native64(0x517AAF684BB50CD1) void SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player, bool toggle)l
extern _native64(0xF6AF6CB341349015) bool GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player)l
extern _native64(0xA2F80B8D040727CC) void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(Vehicle vehicle, bool toggle)l
extern _native64(0x9737A37136F07E75) void UNK_0x9737A37136F07E75(Vehicle vehicle, bool toggle)l
extern _native64(0xB81F6D4A8F5EEBA8) void SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(Vehicle vehicle, int team, bool toggle)l
extern _native64(0xBA71116ADF5B514C) void EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible)l
extern _native64(0xF19D095E42D430CC) void SET_VEHICLE_OUT_OF_CONTROL(Vehicle vehicle, bool killDriver, bool explodeOnImpact)l
extern _native64(0x2E0A74E1002380B1) void SET_VEHICLE_TIMED_EXPLOSION(Vehicle vehicle, Ped ped, bool toggle)l
extern _native64(0x99AD4CCCB128CBC9) void UNK_0x99AD4CCCB128CBC9(Vehicle vehicle)l
extern _native64(0x6ADAABD3068C5235) any UNK_0x6ADAABD3068C5235()l
extern _native64(0xEF49CF0270307CBE) void UNK_0xEF49CF0270307CBE()l
extern _native64(0xAE3FEE8709B39DCB) bool UNK_0xAE3FEE8709B39DCB(Vehicle vehicle)l
extern _native64(0x598803E85E8448D9) void SET_TAXI_LIGHTS(Vehicle vehicle, bool state)l
extern _native64(0x7504C0F113AB50FC) bool IS_TAXI_LIGHT_ON(Vehicle vehicle)l
extern _native64(0xCEE4490CD57BB3C2) bool IS_VEHICLE_IN_GARAGE_AREA(const char* garageName, Vehicle vehicle)l
extern _native64(0x4F1D4BE3A7F24601) void SET_VEHICLE_COLOURS(Vehicle vehicle, int colorPrimary, int colorSecondary)l
extern _native64(0x8B7FD87F0DDB421E) void SET_VEHICLE_FULLBEAM(Vehicle vehicle, bool toggle)l
extern _native64(0x07116E24E9D1929D) void STEER_UNLOCK_BIAS(Vehicle vehicle, bool toggle)l
extern _native64(0x7141766F91D15BEA) void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, RGB colour)l
extern _native64(0xB64CF2CCA9D95F52) void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x55E1D2758F34E437) any CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle)l
extern _native64(0xF095C0405307B21B) bool GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Vehicle vehicle)l
extern _native64(0x36CED73BFED89754) void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, RGB colour)l
extern _native64(0x8389CD56CA8072DC) void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x5FFBDEEC3E8E2009) any CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle)l
extern _native64(0x910A32E7AAD2656C) bool GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Vehicle vehicle)l
extern _native64(0x3AFDC536C3D01674) void SET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle, float fade)l
extern _native64(0xA82819CAC9C4C403) float GET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle)l
extern _native64(0x52BBA29D5EC69356) void SET_CAN_RESPRAY_VEHICLE(Vehicle vehicle, bool state)l
extern _native64(0x33506883545AC0DF) void UNK_0x33506883545AC0DF(Vehicle vehicle, bool p1)l
extern _native64(0xC59872A5134879C7) void _JITTER_VEHICLE(Vehicle vehicle, bool p1, float yaw, float pitch, float roll)l
extern _native64(0x75DBEC174AEEAD10) void SET_BOAT_ANCHOR(Vehicle vehicle, bool toggle)l
extern _native64(0x26C10ECBDA5D043B) bool _GET_BOAT_ANCHOR(Vehicle vehicle)l
extern _native64(0xE3EBAAE484798530) void UNK_0xE3EBAAE484798530(Vehicle vehicle, bool p1)l
extern _native64(0xB28B1FE5BFADD7F5) void UNK_0xB28B1FE5BFADD7F5(Vehicle vehicle, bool p1)l
extern _native64(0xE842A9398079BD82) void UNK_0xE842A9398079BD82(Vehicle vehicle, float p1)l
extern _native64(0x8F719973E1445BA2) void UNK_0x8F719973E1445BA2(Vehicle vehicle, bool p1)l
extern _native64(0xF4924635A19EB37D) void SET_VEHICLE_SIREN(Vehicle vehicle, bool toggle)l
extern _native64(0x4C9BF537BE2634B2) bool IS_VEHICLE_SIREN_ON(Vehicle vehicle)l
extern _native64(0xB5CC40FBCB586380) bool _IS_VEHICLE_SIREN_SOUND_ON(Vehicle vehicle)l
extern _native64(0x3E8C8727991A8A0B) void SET_VEHICLE_STRONG(Vehicle vehicle, bool toggle)l
extern _native64(0x8386BFB614D06749) void REMOVE_VEHICLE_STUCK_CHECK(Vehicle vehicle)l
extern _native64(0xA19435F193E081AC) void GET_VEHICLE_COLOURS(Vehicle vehicle, int* colorPrimary, int* colorSecondary)l
extern _native64(0x22AC59A870E6A669) bool IS_VEHICLE_SEAT_FREE(Vehicle vehicle, int seatIndex)l
extern _native64(0xBB40DD2270B65366) Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int index)l
extern _native64(0x83F969AA1EE2A664) Ped GET_LAST_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex)l
extern _native64(0xB91B4C20085BD12F) bool GET_VEHICLE_LIGHTS_STATE(Vehicle vehicle, bool* lightsOn, bool* highbeamsOn)l
extern _native64(0xBA291848A0815CA9) bool IS_VEHICLE_TYRE_BURST(Vehicle vehicle, int wheelID, bool completely)l
extern _native64(0xAB54A438726D25D5) void SET_VEHICLE_FORWARD_SPEED(Vehicle vehicle, float speed)l
extern _native64(0x260BE8F09E326A20) void _SET_VEHICLE_HALT(Vehicle vehicle, float distance, int killEngine, bool unknown)l
extern _native64(0x37EBBF3117BD6A25) void UNK_0x37EBBF3117BD6A25(Vehicle vehicle, float p1)l
extern _native64(0x57715966069157AD) bool SET_PED_ENABLED_BIKE_RINGTONE(Vehicle vehicle, Entity entity)l
extern _native64(0x62CA17B74C435651) bool UNK_0x62CA17B74C435651(Vehicle vehicle)l
extern _native64(0x375E7FC44F21C8AB) Vehicle _GET_VEHICLE_ATTACHED_TO_ENTITY(Object object)l
extern _native64(0x89D630CF5EA96D23) bool UNK_0x89D630CF5EA96D23(Vehicle vehicle, Entity entity)l
extern _native64(0x6A98C2ECF57FA5D4) void UNK_0x6A98C2ECF57FA5D4(Vehicle vehicle, Entity entity)l
extern _native64(0x7C0043FDFF6436BC) void UNK_0x7C0043FDFF6436BC(Vehicle vehicle)l
extern _native64(0x8AA9180DE2FEDD45) void UNK_0x8AA9180DE2FEDD45(Vehicle vehicle, bool p1)l
extern _native64(0x0A6A279F3AA4FD70) void UNK_0x0A6A279F3AA4FD70(Vehicle vehicle, bool p1)l
extern _native64(0x634148744F385576) bool UNK_0x634148744F385576(Vehicle vehicle)l
extern _native64(0xE6F13851780394DA) void UNK_0xE6F13851780394DA(Vehicle vehicle, float p1)l
extern _native64(0xEC6A202EE4960385) void SET_VEHICLE_TYRE_BURST(Vehicle vehicle, int index, bool onRim, float p3)l
extern _native64(0x781B3D62BB013EF5) void SET_VEHICLE_DOORS_SHUT(Vehicle vehicle, bool closeInstantly)l
extern _native64(0xEB9DC3C7D8596C46) void SET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle, bool toggle)l
extern _native64(0x678B9BB8C3F58FEB) bool GET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle)l
extern _native64(0x29B18B4FD460CA8F) any SET_VEHICLE_WHEELS_CAN_BREAK(Vehicle vehicle, bool enabled)l
extern _native64(0x7C65DAC73C35C862) void SET_VEHICLE_DOOR_OPEN(Vehicle vehicle, int doorIndex, bool loose, bool openInstantly)l
extern _native64(0xA711568EEDB43069) void REMOVE_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x85796B0549DDE156) void ROLL_DOWN_WINDOWS(Vehicle vehicle)l
extern _native64(0x7AD9E6CE657D69E3) any ROLL_DOWN_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x602E548F46E24D59) any ROLL_UP_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native64(0x9E5B5E4D2CCD2259) any SMASH_VEHICLE_WINDOW(Vehicle vehicle, int index)l
extern _native64(0x772282EBEB95E682) any FIX_VEHICLE_WINDOW(Vehicle vehicle, int index)l
extern _native64(0x6D645D59FB5F5AD3) void _DETACH_VEHICLE_WINDSCREEN(Vehicle vehicle)l
extern _native64(0xE38CB9D7D39FDBCC) void _EJECT_JB700_ROOF(Vehicle vehicle, vector3 vec)l
extern _native64(0x34E710FF01247C5A) void SET_VEHICLE_LIGHTS(Vehicle vehicle, int state)l
extern _native64(0xC45C27EF50F36ADC) void UNK_0xC45C27EF50F36ADC(Vehicle vehicle, bool p1)l
extern _native64(0x1FD09E7390A74D54) void _SET_VEHICLE_LIGHTS_MODE(Vehicle vehicle, int p1)l
extern _native64(0xCDE5E70C1DDB954C) void SET_VEHICLE_ALARM(Vehicle vehicle, bool state)l
extern _native64(0xB8FF7AB45305C345) any START_VEHICLE_ALARM(Vehicle vehicle)l
extern _native64(0x4319E335B71FFF34) bool IS_VEHICLE_ALARM_ACTIVATED(Vehicle vehicle)l
extern _native64(0xBC2042F090AF6AD3) void SET_VEHICLE_INTERIORLIGHT(Vehicle vehicle, bool toggle)l
extern _native64(0xB385454F8791F57C) void SET_VEHICLE_LIGHT_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native64(0x3C7D42D58F770B54) void ATTACH_VEHICLE_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float radius)l
extern _native64(0x16B5E274BDE402F8) void UNK_0x16B5E274BDE402F8(Vehicle vehicle, Vehicle trailer, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11)l
extern _native64(0x374706271354CB18) void UNK_0x374706271354CB18(Vehicle vehicle, Entity p1, float p2)l
extern _native64(0x90532EDF0D2BDD86) void DETACH_VEHICLE_FROM_TRAILER(Vehicle vehicle)l
extern _native64(0xE7CF3C4F9F489F0C) bool IS_VEHICLE_ATTACHED_TO_TRAILER(Vehicle vehicle)l
extern _native64(0x2A8F319B392E7B3F) void UNK_0x2A8F319B392E7B3F(Vehicle vehicle, float p1)l
extern _native64(0x95CF53B3D687F9FA) void UNK_0x95CF53B3D687F9FA(Vehicle vehicle)l
extern _native64(0x6E13FC662B882D1D) void SET_VEHICLE_TYRE_FIXED(Vehicle vehicle, int tyreIndex)l
extern _native64(0x95A88F0B409CDA47) void SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle, const char* plateText)l
extern _native64(0x7CE1CCB9B293020E) const char* GET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle)l
extern _native64(0x4C4D6B2644F458CB) int GET_NUMBER_OF_VEHICLE_NUMBER_PLATES()l
extern _native64(0x9088EB5A43FFB0A1) void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle, int plateIndex)l
extern _native64(0xF11BC2DD9A3E7195) int GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle)l
extern _native64(0x80D9F74197EA47D9) void SET_RANDOM_TRAINS(bool toggle)l
extern _native64(0x63C6CCA8E68AE8C8) Vehicle CREATE_MISSION_TRAIN(int variation, vector3 vec, bool direction)l
extern _native64(0xFD813BB7DB977F20) any SWITCH_TRAIN_TRACK(int intersectionId, bool state)l
extern _native64(0x21973BBF8D17EDFA) void UNK_0x21973BBF8D17EDFA(any p0, any p1)l
extern _native64(0x736A718577F39C7D) void DELETE_ALL_TRAINS()l
extern _native64(0xAA0BC91BE0B796E3) any SET_TRAIN_SPEED(Vehicle train, float speed)l
extern _native64(0x16469284DB8C62B5) any SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed)l
extern _native64(0x84436EC293B1415F) any SET_RANDOM_BOATS(bool toggle)l
extern _native64(0x2AFD795EEAC8D30D) any SET_GARBAGE_TRUCKS(bool toggle)l
extern _native64(0x57E4C39DE5EE8470) bool DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(Vehicle vehicle)l
extern _native64(0x21543C612379DB3C) any GET_VEHICLE_RECORDING_ID(int p0, const char* p1)l
extern _native64(0xAF514CABE74CBF15) void REQUEST_VEHICLE_RECORDING(any p0, any* p1)l
extern _native64(0x300D614A4C785FC4) bool HAS_VEHICLE_RECORDING_BEEN_LOADED(any p0, any* p1)l
extern _native64(0xF1160ACCF98A3FC8) void REMOVE_VEHICLE_RECORDING(any p0, any* p1)l
extern _native64(0x92523B76657A517D) int UNK_0x92523B76657A517D(any p0, float p1)l
extern _native64(0xD242728AA6F0FBA2) vector3 GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(int p0, float p1, const char* p2)l
extern _native64(0xF0F2103EFAF8CBA7) vector3 UNK_0xF0F2103EFAF8CBA7(any p0, float p1)l
extern _native64(0x2058206FBE79A8AD) int GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(any p0, float p1, any* p2)l
extern _native64(0x102D125411A7B6E6) float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(any p0)l
extern _native64(0x0E48D1C262390950) any GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(any p0, any p1)l
extern _native64(0x2DACD605FC681475) float GET_POSITION_IN_RECORDING(any p0)l
extern _native64(0x5746F3A7AB7FE544) float GET_TIME_POSITION_IN_RECORDING(any p0)l
extern _native64(0x3F878F92B3A7A071) void START_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, int p1, const char* playback, bool p3)l
extern _native64(0x7D80FD645D4DA346) void START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(Vehicle vehicle, any p1, const char* playback, any p3, any p4, any p5)l
extern _native64(0x1F2E4E06DEA8992B) void UNK_0x1F2E4E06DEA8992B(any p0, bool p1)l
extern _native64(0x54833611C17ABDEA) void STOP_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native64(0x632A689BF42301B1) void PAUSE_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native64(0x8879EE09268305D5) void UNPAUSE_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native64(0x1C8A4C2C19E68EEC) bool IS_PLAYBACK_GOING_ON_FOR_VEHICLE(any p0)l
extern _native64(0xAEA8FD591FAD4106) bool IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(any p0)l
extern _native64(0x42BC05C27A946054) any GET_CURRENT_PLAYBACK_FOR_VEHICLE(any p0)l
extern _native64(0xAB8E2EDA0C0A5883) void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native64(0x6683AB880E427778) any SET_PLAYBACK_SPEED(any p0, float speed)l
extern _native64(0x29DE5FA52D00428C) void START_PLAYBACK_RECORDED_VEHICLE_USING_AI(any p0, any p1, any* p2, float p3, any p4)l
extern _native64(0x9438F7AD68771A20) void SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(any p0, float p1)l
extern _native64(0xA549C3B37EA28131) void SET_PLAYBACK_TO_USE_AI(Vehicle vehicle, int flag)l
extern _native64(0x6E63860BBB190730) void SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(any p0, any p1, any p2, bool p3)l
extern _native64(0x5845066D8A1EA7F7) void UNK_0x5845066D8A1EA7F7(Vehicle vehicle, vector3 vec, any p4)l
extern _native64(0x796A877E459B99EA) void UNK_0x796A877E459B99EA(any p0, float p1, float p2, float p3)l
extern _native64(0xFAF2A78061FD9EF4) void UNK_0xFAF2A78061FD9EF4(any p0, float p1, float p2, float p3)l
extern _native64(0x063AE2B2CC273588) void UNK_0x063AE2B2CC273588(any p0, bool p1)l
extern _native64(0x786A4EB67B01BF0B) void EXPLODE_VEHICLE_IN_CUTSCENE(Vehicle vehicle, bool p1)l
extern _native64(0x2FA9923062DD396C) void ADD_VEHICLE_STUCK_CHECK_WITH_WARP(any p0, float p1, any p2, bool p3, bool p4, bool p5, any p6)l
extern _native64(0x0FC2D89AC25A5814) void SET_VEHICLE_MODEL_IS_SUPPRESSED(Hash model, bool suppressed)l
extern _native64(0x386F6CE5BAF6091C) Vehicle GET_RANDOM_VEHICLE_IN_SPHERE(vector3 vec, float radius, Hash modelHash, int flags)l
extern _native64(0xC5574E0AEB86BA68) Vehicle GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native64(0xB50807EABE20A8DC) Vehicle GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native64(0xF73EB622C4F1689B) Vehicle GET_CLOSEST_VEHICLE(vector3 vec, float radius, Hash modelHash, int flags)l
extern _native64(0x08AAFD0814722BC3) Entity GET_TRAIN_CARRIAGE(Vehicle train, int trailerNumber)l
extern _native64(0x5B76B14AE875C795) void DELETE_MISSION_TRAIN(Vehicle* train)l
extern _native64(0xBBE7648349B49BE8) void SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Vehicle* train, bool p1)l
extern _native64(0x591CA673AA6AB736) void SET_MISSION_TRAIN_COORDS(Vehicle train, vector3 vec)l
extern _native64(0x45A9187928F4B9E3) bool IS_THIS_MODEL_A_BOAT(Hash model)l
extern _native64(0x9537097412CF75FE) bool _IS_THIS_MODEL_AN_EMERGENCY_BOAT(Hash model)l
extern _native64(0xA0948AB42D7BA0DE) bool IS_THIS_MODEL_A_PLANE(Hash model)l
extern _native64(0xDCE4334788AF94EA) bool IS_THIS_MODEL_A_HELI(Hash model)l
extern _native64(0x7F6DB52EEFC96DF8) bool IS_THIS_MODEL_A_CAR(Hash model)l
extern _native64(0xAB935175B22E822B) bool IS_THIS_MODEL_A_TRAIN(Hash model)l
extern _native64(0xB50C0B0CEDC6CE84) bool IS_THIS_MODEL_A_BIKE(Hash model)l
extern _native64(0xBF94DD42F63BDED2) bool IS_THIS_MODEL_A_BICYCLE(Hash model)l
extern _native64(0x39DAC362EE65FA28) bool IS_THIS_MODEL_A_QUADBIKE(Hash model)l
extern _native64(0xA178472EBB8AE60D) void SET_HELI_BLADES_FULL_SPEED(Vehicle vehicle)l
extern _native64(0xFD280B4D7F3ABC4D) void SET_HELI_BLADES_SPEED(Vehicle vehicle, float speed)l
extern _native64(0x99CAD8E7AFDB60FA) void UNK_0x99CAD8E7AFDB60FA(Vehicle vehicle, float p1, float p2)l
extern _native64(0x3750146A28097A82) void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle vehicle, bool state)l
extern _native64(0xDBC631F109350B8C) void UNK_0xDBC631F109350B8C(Vehicle vehicle, bool p1)l
extern _native64(0x4C7028F78FFD3681) void SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, bool state)l
extern _native64(0x1AA8A837D2169D94) void UNK_0x1AA8A837D2169D94(Vehicle vehicle, bool p1)l
extern _native64(0x2311DD7159F00582) void UNK_0x2311DD7159F00582(Vehicle vehicle, bool p1)l
extern _native64(0x8F17BC8BA08DA62B) float GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle)l
extern _native64(0x79D3B596FE44EE8B) void SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float dirtLevel)l
extern _native64(0xBCDC5017D3CE1E9E) bool _IS_VEHICLE_DAMAGED(Vehicle vehicle)l
extern _native64(0x3E933CFF7B111C22) bool IS_VEHICLE_DOOR_FULLY_OPEN(Vehicle vehicle, int doorIndex)l
extern _native64(0x2497C4717C8B881E) void SET_VEHICLE_ENGINE_ON(Vehicle vehicle, bool value, bool instantly, bool otherwise)l
extern _native64(0x8ABA6AF54B942B95) void SET_VEHICLE_UNDRIVEABLE(Vehicle vehicle, bool toggle)l
extern _native64(0x5AFEEDD9BB2899D7) void SET_VEHICLE_PROVIDES_COVER(Vehicle vehicle, bool toggle)l
extern _native64(0xF2BFA0430F0A0FCB) void SET_VEHICLE_DOOR_CONTROL(Vehicle vehicle, int doorIndex, int speed, float angle)l
extern _native64(0xA5A9653A8D2CAF48) void SET_VEHICLE_DOOR_LATCHED(Vehicle vehicle, int doorIndex, bool p2, bool p3, bool p4)l
extern _native64(0xFE3F9C29F7B32BD5) float GET_VEHICLE_DOOR_ANGLE_RATIO(Vehicle vehicle, int door)l
extern _native64(0x218297BF0CFD853B) Ped _GET_PED_USING_VEHICLE_DOOR(Vehicle vehicle, int doorIndex)l
extern _native64(0x93D9BD300D7789E5) void SET_VEHICLE_DOOR_SHUT(Vehicle vehicle, int doorIndex, bool closeInstantly)l
extern _native64(0xD4D4F6A4AB575A33) void SET_VEHICLE_DOOR_BROKEN(Vehicle vehicle, int doorIndex, bool deleteDoor)l
extern _native64(0x59BF8C3D52C92F66) void SET_VEHICLE_CAN_BREAK(Vehicle vehicle, bool toggle)l
extern _native64(0x8AC862B0B32C5B80) bool DOES_VEHICLE_HAVE_ROOF(Vehicle vehicle)l
extern _native64(0x9F243D3919F442FE) bool IS_BIG_VEHICLE(Vehicle vehicle)l
extern _native64(0x3B963160CD65D41E) int GET_NUMBER_OF_VEHICLE_COLOURS(Vehicle vehicle)l
extern _native64(0x33E8CD3322E2FE31) void SET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle, int colorCombination)l
extern _native64(0x6A842D197F845D56) int GET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle)l
extern _native64(0x31B927BBC44156CD) void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle vehicle, bool toggle)l
extern _native64(0xBE5C1255A1830FF5) void UNK_0xBE5C1255A1830FF5(Vehicle vehicle, bool toggle)l
extern _native64(0x9BECD4B9FEF3F8A6) void UNK_0x9BECD4B9FEF3F8A6(Vehicle vehicle, bool p1)l
extern _native64(0x88BC673CA9E0AE99) void UNK_0x88BC673CA9E0AE99(Vehicle vehicle, bool p1)l
extern _native64(0xE851E480B814D4BA) void UNK_0xE851E480B814D4BA(Vehicle vehicle, bool p1)l
extern _native64(0x055BF0AC0C34F4FD) void GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(bool p0, Hash* modelHash, int* p2)l
extern _native64(0x25BC98A59C2EA962) int GET_VEHICLE_DOOR_LOCK_STATUS(Vehicle vehicle)l
extern _native64(0xB8E181E559464527) bool IS_VEHICLE_DOOR_DAMAGED(Vehicle veh, int doorID)l
extern _native64(0x2FA133A4A9D37ED8) void _SET_VEHICLE_DOOR_CAN_BREAK(Vehicle vehicle, int doorIndex, bool isBreakable)l
extern _native64(0x27B926779DEB502D) bool UNK_0x27B926779DEB502D(Vehicle vehicle, bool p1)l
extern _native64(0x468056A6BB6F3846) bool IS_VEHICLE_BUMPER_BROKEN_OFF(Vehicle vehicle, bool front)l
extern _native64(0x7EEF65D5F153E26A) bool IS_COP_VEHICLE_IN_AREA_3D(float x1, float x2, float y1, float y2, float z1, float z2)l
extern _native64(0xB104CD1BABF302E2) bool IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle)l
extern _native64(0x28D37D4F71AC5C58) Hash GET_VEHICLE_LAYOUT_HASH(Vehicle vehicle)l
extern _native64(0xA01BC64DD4BFBBAC) any UNK_0xA01BC64DD4BFBBAC(Vehicle vehicle, int p1)l
extern _native64(0x317B11A312DF5534) void SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, bool toggle)l
extern _native64(0x2036F561ADD12E33) void SET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int pearlescentColor, int wheelColor)l
extern _native64(0x3BC4245933A166F7) void GET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int* pearlescentColor, int* wheelColor)l
extern _native64(0x0F87E938BDF29D66) void STOP_ALL_GARAGE_ACTIVITY()l
extern _native64(0x115722B1B9C14C1C) void SET_VEHICLE_FIXED(Vehicle vehicle)l
extern _native64(0x953DA1E1B12C0491) void SET_VEHICLE_DEFORMATION_FIXED(Vehicle vehicle)l
extern _native64(0x206BC5DC9D1AC70A) void UNK_0x206BC5DC9D1AC70A(Vehicle vehicle, bool p1)l
extern _native64(0x51BB2D88D31A914B) void UNK_0x51BB2D88D31A914B(Vehicle vehicle, bool p1)l
extern _native64(0x192547247864DFDD) void UNK_0x192547247864DFDD(Vehicle vehicle, bool p1)l
extern _native64(0x465BF26AB9684352) void SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(Vehicle vehicle, bool toggle)l
extern _native64(0x37C8252A7C92D017) void SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0x91A0BD635321F145) void UNK_0x91A0BD635321F145(Vehicle vehicle, bool p1)l
extern _native64(0xC50CE861B55EAB8B) void UNK_0xC50CE861B55EAB8B(Vehicle vehicle, bool p1)l
extern _native64(0x6EBFB22D646FFC18) void UNK_0x6EBFB22D646FFC18(Vehicle vehicle, bool p1)l
extern _native64(0x25367DE49D64CF16) void UNK_0x25367DE49D64CF16(Vehicle vehicle, bool p1)l
extern _native64(0x46A1E1A299EC4BBA) void REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(vector3 vec_1, vector3 vec_2, any unk)l
extern _native64(0x42A8EC77D5150CBE) void SET_VEHICLE_STEER_BIAS(Vehicle vehicle, float value)l
extern _native64(0xD2E6822DBFD6C8BD) bool IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, int extraId)l
extern _native64(0x7EE3A3C5E4A40CC9) void SET_VEHICLE_EXTRA(Vehicle vehicle, int extraId, bool toggle)l
extern _native64(0x1262D55792428154) bool DOES_EXTRA_EXIST(Vehicle vehicle, int extraId)l
extern _native64(0xF39C4F538B5124C2) void SET_CONVERTIBLE_ROOF(Vehicle vehicle, bool p1)l
extern _native64(0xDED51F703D0FA83D) void LOWER_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyLower)l
extern _native64(0x8F5FB35D7E88FC70) void RAISE_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyRaise)l
extern _native64(0xF8C397922FC03F41) int GET_CONVERTIBLE_ROOF_STATE(Vehicle vehicle)l
extern _native64(0x52F357A30698BCCE) bool IS_VEHICLE_A_CONVERTIBLE(Vehicle vehicle, bool p1)l
extern _native64(0x2959F696AE390A99) bool IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle)l
extern _native64(0xA1DD317EA8FD4F29) void SET_VEHICLE_DAMAGE(Vehicle vehicle, vector3 Offset, float damage, float radius, bool p6)l
extern _native64(0xC45D23BAF168AAB8) float GET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle)l
extern _native64(0x45F6D8EEF34ABEF1) void SET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle, float health)l
extern _native64(0x7D5DABE888D2D074) float GET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle)l
extern _native64(0x70DB57649FA8D0D8) void SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle, float health)l
extern _native64(0x679BE1DAF71DA874) bool IS_VEHICLE_STUCK_TIMER_UP(Vehicle vehicle, int p1, int p2)l
extern _native64(0xD7591B0065AFAA7A) void RESET_VEHICLE_STUCK_TIMER(Vehicle vehicle, bool nullAttributes)l
extern _native64(0x4C241E39B23DF959) bool IS_VEHICLE_DRIVEABLE(Vehicle vehicle, bool p1)l
extern _native64(0x2B5F9D2AF1F1722D) void SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Vehicle vehicle, bool owned)l
extern _native64(0xFBA550EA44404EE6) void SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(Vehicle vehicle, bool toggle)l
extern _native64(0x9F3F689B814F2599) void UNK_0x9F3F689B814F2599(Vehicle vehicle, bool p1)l
extern _native64(0x4E74E62E0A97E901) void UNK_0x4E74E62E0A97E901(Vehicle vehicle, bool p1)l
extern _native64(0x9C8C6504B5B63D2C) void START_VEHICLE_HORN(Vehicle vehicle, int duration, Hash mode, bool forever)l
extern _native64(0x9D44FCCE98450843) void _SET_VEHICLE_SILENT(Vehicle vehicle, bool toggle)l
extern _native64(0x92F0CF722BC4202F) void SET_VEHICLE_HAS_STRONG_AXLES(Vehicle vehicle, bool toggle)l
extern _native64(0xB215AAC32D25D019) const char* GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Hash modelHash)l
extern _native64(0x4EC6CFBC7B2E9536) vector3 GET_VEHICLE_DEFORMATION_AT_POS(Vehicle vehicle, vector3 offset)l
extern _native64(0x60BF608F1B8CD1B6) void SET_VEHICLE_LIVERY(Vehicle vehicle, int livery)l
extern _native64(0x2BB9230590DA5E8A) int GET_VEHICLE_LIVERY(Vehicle vehicle)l
extern _native64(0x87B63E25A529D526) int GET_VEHICLE_LIVERY_COUNT(Vehicle vehicle)l
extern _native64(0x46E571A0E20D01F1) bool IS_VEHICLE_WINDOW_INTACT(Vehicle vehicle, int windowIndex)l
extern _native64(0x11D862A3E977A9EF) bool ARE_ALL_VEHICLE_WINDOWS_INTACT(Vehicle vehicle)l
extern _native64(0x2D34FC3BC4ADB780) bool ARE_ANY_VEHICLE_SEATS_FREE(Vehicle vehicle)l
extern _native64(0x21D2E5662C1F6FED) void RESET_VEHICLE_WHEELS(Vehicle vehicle, bool toggle)l
extern _native64(0xBC74B4BE25EB6C8A) bool IS_HELI_PART_BROKEN(Vehicle vehicle, bool p1, bool p2, bool p3)l
extern _native64(0xE4CB7541F413D2C5) float _GET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle)l
extern _native64(0xAE8CE82A4219AC8C) float _GET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle)l
extern _native64(0xAC51915D27E4A5F7) float _GET_HELI_ENGINE_HEALTH(Vehicle vehicle)l
extern _native64(0x3EC8BF18AA453FE9) bool WAS_COUNTER_ACTIVATED(Vehicle vehicle, any p1)l
extern _native64(0xBFDF984E2C22B94F) void SET_VEHICLE_NAME_DEBUG(Vehicle vehicle, const char* name)l
extern _native64(0x71B0892EC081D60A) void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native64(0x3441CAD2F2231923) void UNK_0x3441CAD2F2231923(Vehicle vehicle, bool p1)l
extern _native64(0x2B6747FAA9DB9D6B) any UNK_0x2B6747FAA9DB9D6B(Vehicle vehicle, bool p1)l
extern _native64(0xCFC8BE9A5E1FE575) void CONTROL_LANDING_GEAR(Vehicle vehicle, int state)l
extern _native64(0x9B0F3DCA3DB0F4CD) int GET_LANDING_GEAR_STATE(Vehicle vehicle)l
extern _native64(0x61E1DD6125A3EEE6) bool IS_ANY_VEHICLE_NEAR_POINT(vector3 vec, float radius)l
extern _native64(0xA6E9FDCB2C76785E) void REQUEST_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)l
extern _native64(0x00689CDE5F7C6787) void REMOVE_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)l
extern _native64(0x1F25887F3C104278) bool IS_VEHICLE_HIGH_DETAIL(Vehicle vehicle)l
extern _native64(0x81A15811460FAB3A) void REQUEST_VEHICLE_ASSET(Hash vehicleHash, int vehicleAsset)l
extern _native64(0x1BBE0523B8DB9A21) bool HAS_VEHICLE_ASSET_LOADED(int vehicleAsset)l
extern _native64(0xACE699C71AB9DEB5) void REMOVE_VEHICLE_ASSET(int vehicleAsset)l
extern _native64(0xFE54B92A344583CA) void _SET_TOW_TRUCK_CRANE_HEIGHT(Vehicle towTruck, float height)l
extern _native64(0x29A16F8D621C4508) void ATTACH_VEHICLE_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle, bool rear, vector3 hookOffset)l
extern _native64(0xC2DB6B6708350ED8) void DETACH_VEHICLE_FROM_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)l
extern _native64(0xD0E9CE05A1E68CD8) bool DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(Vehicle vehicle)l
extern _native64(0x146DF9EC4C4B9FD4) bool IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)l
extern _native64(0xEFEA18DCF10F8F75) Entity GET_ENTITY_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck)l
extern _native64(0x8BA6F76BC53A1493) any SET_VEHICLE_AUTOMATICALLY_ATTACHES(Vehicle vehicle, any p1, any p2)l
extern _native64(0xF8EBCCC96ADB9FB7) void UNK_0xF8EBCCC96ADB9FB7(any p0, float p1, bool p2)l
extern _native64(0x56B94C6D7127DFBA) void UNK_0x56B94C6D7127DFBA(any p0, float p1, bool p2)l
extern _native64(0x1093408B4B9D1146) void UNK_0x1093408B4B9D1146(any p0, float p1)l
extern _native64(0x30D779DE7C4F6DD3) void UNK_0x30D779DE7C4F6DD3(any p0, float p1)l
extern _native64(0x9AA47FFF660CB932) void UNK_0x9AA47FFF660CB932(any p0, float p1)l
extern _native64(0xA4822F1CF23F4810) bool UNK_0xA4822F1CF23F4810(vector3* outVec, any p1, vector3* outVec1, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native64(0xFB8794444A7D60FB) void SET_VEHICLE_BURNOUT(Vehicle vehicle, bool toggle)l
extern _native64(0x1297A88E081430EB) bool IS_VEHICLE_IN_BURNOUT(Vehicle vehicle)l
extern _native64(0x222FF6A823D122E2) void SET_VEHICLE_REDUCE_GRIP(Vehicle vehicle, bool toggle)l
extern _native64(0xB5D45264751B7DF0) void SET_VEHICLE_INDICATOR_LIGHTS(Vehicle vehicle, int turnSignal, bool toggle)l
extern _native64(0x92B35082E0B42F66) void SET_VEHICLE_BRAKE_LIGHTS(Vehicle vehicle, bool toggle)l
extern _native64(0x684785568EF26A22) void SET_VEHICLE_HANDBRAKE(Vehicle vehicle, bool toggle)l
extern _native64(0x48ADC8A773564670) void UNK_0x48ADC8A773564670()l
extern _native64(0x91D6DD290888CBAB) bool UNK_0x91D6DD290888CBAB()l
extern _native64(0x51DB102F4A3BA5E0) void UNK_0x51DB102F4A3BA5E0(bool p0)l
extern _native64(0x1CDD6BADC297830D) bool GET_VEHICLE_TRAILER_VEHICLE(Vehicle vehicle, Vehicle* trailer)l
extern _native64(0xCAC66558B944DA67) void UNK_0xCAC66558B944DA67(Vehicle vehicle, bool p1)l
extern _native64(0x09606148B6C71DEF) void SET_VEHICLE_RUDDER_BROKEN(Vehicle vehicle, bool p1)l
extern _native64(0x1A78AD3D8240536F) void UNK_0x1A78AD3D8240536F(Vehicle vehicle, bool p1)l
extern _native64(0x53AF99BAA671CA47) float UNK_0x53AF99BAA671CA47(Vehicle vehicle)l
extern _native64(0xAD7E85FC227197C4) float GET_VEHICLE_MAX_BRAKING(Vehicle vehicle)l
extern _native64(0xA132FB5370554DB0) float GET_VEHICLE_MAX_TRACTION(Vehicle vehicle)l
extern _native64(0x5DD35C8D074E57AE) float GET_VEHICLE_ACCELERATION(Vehicle vehicle)l
extern _native64(0xF417C2502FFFED43) float _GET_VEHICLE_MODEL_MAX_SPEED(Hash modelHash)l
extern _native64(0xDC53FD41B4ED944C) float GET_VEHICLE_MODEL_MAX_BRAKING(Hash modelHash)l
extern _native64(0xBFBA3BA79CFF7EBF) float UNK_0xBFBA3BA79CFF7EBF(Hash modelHash)l
extern _native64(0x539DE94D44FDFD0D) float GET_VEHICLE_MODEL_MAX_TRACTION(Hash modelHash)l
extern _native64(0x8C044C5C84505B6A) float GET_VEHICLE_MODEL_ACCELERATION(Hash modelHash)l
extern _native64(0x53409B5163D5B846) float UNK_0x53409B5163D5B846(Hash modelHash)l
extern _native64(0xC6AD107DDC9054CC) float UNK_0xC6AD107DDC9054CC(Hash modelHash)l
extern _native64(0x5AA3F878A178C4FC) float UNK_0x5AA3F878A178C4FC(Hash modelHash)l
extern _native64(0x00C09F246ABEDD82) float UNK_0x00C09F246ABEDD82(int vehicleClass)l
extern _native64(0xDBC86D85C5059461) float GET_VEHICLE_CLASS_MAX_TRACTION(int vehicleClass)l
extern _native64(0x4F930AD022D6DE3B) float GET_VEHICLE_CLASS_MAX_AGILITY(int vehicleClass)l
extern _native64(0x2F83E7E45D9EA7AE) float GET_VEHICLE_CLASS_MAX_ACCELERATION(int vehicleClass)l
extern _native64(0x4BF54C16EC8FEC03) float GET_VEHICLE_CLASS_MAX_BRAKING(int vehicleClass)l
extern _native64(0x2CE544C68FB812A0) any UNK_0x2CE544C68FB812A0(float p0, float p1, float p2, float p3, float p4, bool p5)l
extern _native64(0x1033371FC8E842A7) bool UNK_0x1033371FC8E842A7(any p0)l
extern _native64(0x87E7F24270732CB1) void OPEN_BOMB_BAY_DOORS(Vehicle vehicle)l
extern _native64(0x3556041742A0DC74) void CLOSE_BOMB_BAY_DOORS(Vehicle vehicle)l
extern _native64(0xC0F97FCE55094987) bool IS_VEHICLE_SEARCHLIGHT_ON(Vehicle vehicle)l
extern _native64(0x14E85C5EE7A4D542) void SET_VEHICLE_SEARCHLIGHT(Vehicle heli, bool toggle, bool canBeUsedByAI)l
extern _native64(0x639431E895B9AA57) bool UNK_0x639431E895B9AA57(Ped ped, Vehicle vehicle, bool p2, bool p3, bool p4)l
extern _native64(0x30785D90C956BF35) bool CAN_SHUFFLE_SEAT(Vehicle vehicle, any p1)l
extern _native64(0x33F2E3FE70EAAE1D) int GET_NUM_MOD_KITS(Vehicle vehicle)l
extern _native64(0x1F2AA07F00B3217A) void SET_VEHICLE_MOD_KIT(Vehicle vehicle, int modKit)l
extern _native64(0x6325D1A044AE510D) int GET_VEHICLE_MOD_KIT(Vehicle vehicle)l
extern _native64(0xFC058F5121E54C32) int GET_VEHICLE_MOD_KIT_TYPE(Vehicle vehicle)l
extern _native64(0xB3ED1BFB4BE636DC) int GET_VEHICLE_WHEEL_TYPE(Vehicle vehicle)l
extern _native64(0x487EB21CC7295BA1) void SET_VEHICLE_WHEEL_TYPE(Vehicle vehicle, int WheelType)l
extern _native64(0xA551BE18C11A476D) int GET_NUM_MOD_COLORS(int p0, bool p1)l
extern _native64(0x43FEB945EE7F85B8) void SET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int paintType, int color, int p3)l
extern _native64(0x816562BADFDEC83E) void SET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int paintType, int color)l
extern _native64(0xE8D65CA700C9A693) void GET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int* paintType, int* color, int* p3)l
extern _native64(0x81592BE4E3878728) void GET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int* paintType, int* color)l
extern _native64(0xB45085B721EFD38C) const char* GET_VEHICLE_MOD_COLOR_1_NAME(Vehicle vehicle, bool p1)l
extern _native64(0x4967A516ED23A5A1) const char* GET_VEHICLE_MOD_COLOR_2_NAME(Vehicle vehicle)l
extern _native64(0x9A83F5F9963775EF) bool UNK_0x9A83F5F9963775EF(Vehicle vehicle)l
extern _native64(0x6AF0636DDEDCB6DD) void SET_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex, bool customTires)l
extern _native64(0x772960298DA26FDB) int GET_VEHICLE_MOD(Vehicle vehicle, int modType)l
extern _native64(0xB3924ECD70E095DC) bool GET_VEHICLE_MOD_VARIATION(Vehicle vehicle, int modType)l
extern _native64(0xE38E9162A2500646) int GET_NUM_VEHICLE_MODS(Vehicle vehicle, int modType)l
extern _native64(0x92D619E420858204) void REMOVE_VEHICLE_MOD(Vehicle vehicle, int modType)l
extern _native64(0x2A1F4F37F95BAD08) void TOGGLE_VEHICLE_MOD(Vehicle vehicle, int modType, bool toggle)l
extern _native64(0x84B233A8C8FC8AE7) bool IS_TOGGLE_MOD_ON(Vehicle vehicle, int modType)l
extern _native64(0x8935624F8C5592CC) const char* GET_MOD_TEXT_LABEL(Vehicle vehicle, int modType, int modValue)l
extern _native64(0x51F0FEB9F6AE98C0) const char* GET_MOD_SLOT_NAME(Vehicle vehicle, int modType)l
extern _native64(0xB4C7A93837C91A1F) const char* GET_LIVERY_NAME(Vehicle vehicle, int liveryIndex)l
extern _native64(0x90A38E9838E0A8C1) any GET_VEHICLE_MOD_MODIFIER_VALUE(Vehicle vehicle, int modType, int modIndex)l
extern _native64(0x4593CF82AA179706) any _GET_VEHICLE_MOD_DATA(Vehicle vehicle, int modType, int modIndex)l
extern _native64(0x758F49C24925568A) void PRELOAD_VEHICLE_MOD(any p0, any p1, any p2)l
extern _native64(0x06F43E5175EB6D96) bool HAS_PRELOAD_MODS_FINISHED(any p0)l
extern _native64(0x445D79F995508307) void RELEASE_PRELOAD_MODS(Vehicle vehicle)l
extern _native64(0xB5BA80F839791C0F) void SET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, RGB colour)l
extern _native64(0xB635392A4938B3C3) void GET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x57C51E6BAD752696) void SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int tint)l
extern _native64(0x0EE21293DAD47C95) int GET_VEHICLE_WINDOW_TINT(Vehicle vehicle)l
extern _native64(0x9D1224004B3A6707) int GET_NUM_VEHICLE_WINDOW_TINTS()l
extern _native64(0xF3CC740D36221548) void GET_VEHICLE_COLOR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0xEEBFC7A7EFDC35B4) int UNK_0xEEBFC7A7EFDC35B4(Vehicle vehicle)l
extern _native64(0xE495D1EF4C91FD20) Hash GET_VEHICLE_CAUSE_OF_DESTRUCTION(Vehicle vehicle)l
extern _native64(0x5EF77C9ADD3B11A3) bool GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)l
extern _native64(0xA7ECB73355EB2F20) bool GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)l
extern _native64(0x93A3996368C94158) void _SET_VEHICLE_ENGINE_POWER_MULTIPLIER(Vehicle vehicle, float value)l
extern _native64(0x1CF38D529D7441D9) void UNK_0x1CF38D529D7441D9(Vehicle vehicle, bool toggle)l
extern _native64(0x1F9FB66F3A3842D2) void UNK_0x1F9FB66F3A3842D2(Vehicle vehicle, bool p1)l
extern _native64(0x54B0F614960F4A5F) any UNK_0x54B0F614960F4A5F(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native64(0xE30524E1871F481D) void UNK_0xE30524E1871F481D(any p0)l
extern _native64(0x291E373D483E7EE7) bool _ANY_PASSENGERS_RAPPELING(Vehicle vehicle)l
extern _native64(0xB59E4BD37AE292DB) void _SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(Vehicle vehicle, float value)l
extern _native64(0x0AD9E8F87FF7C16F) void UNK_0x0AD9E8F87FF7C16F(any p0, bool p1)l
extern _native64(0xF7EC25A3EBEEC726) void SET_VEHICLE_IS_WANTED(Vehicle vehicle, bool state)l
extern _native64(0xF488C566413B4232) void UNK_0xF488C566413B4232(any p0, float p1)l
extern _native64(0xC1F981A6F74F0C23) void UNK_0xC1F981A6F74F0C23(any p0, bool p1)l
extern _native64(0x0F3B4D4E43177236) void UNK_0x0F3B4D4E43177236(any p0, bool p1)l
extern _native64(0x6636C535F6CC2725) float UNK_0x6636C535F6CC2725(Vehicle vehicle)l
extern _native64(0x23428FC53C60919C) void DISABLE_PLANE_AILERON(Vehicle vehicle, bool p1, bool p2)l
extern _native64(0xAE31E7DF9B5B132E) bool GET_IS_VEHICLE_ENGINE_RUNNING(Vehicle vehicle)l
extern _native64(0x1D97D1E3A70A649F) void UNK_0x1D97D1E3A70A649F(Vehicle vehicle, bool p1)l
extern _native64(0x9CFA4896C3A53CBB) void _SET_BIKE_LEAN_ANGLE(Vehicle vehicle, vector2 vector)l
extern _native64(0xAB04325045427AAE) void UNK_0xAB04325045427AAE(Vehicle vehicle, bool p1)l
extern _native64(0xCFD778E7904C255E) void UNK_0xCFD778E7904C255E(Vehicle vehicle)l
extern _native64(0xACFB2463CC22BED2) void SET_LAST_DRIVEN_VEHICLE(Vehicle vehicle)l
extern _native64(0xB2D06FAEDE65B577) Vehicle GET_LAST_DRIVEN_VEHICLE()l
extern _native64(0xE01903C47C7AC89E) void UNK_0xE01903C47C7AC89E()l
extern _native64(0x02398B627547189C) void UNK_0x02398B627547189C(any p0, bool p1)l
extern _native64(0xB893215D8D4C015B) void _SET_PLANE_MIN_HEIGHT_ABOVE_GROUND(Vehicle plane, int height)l
extern _native64(0x93AE6A61BE015BF1) void SET_VEHICLE_LOD_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native64(0x428BACCDF5E26EAD) void UNK_0x428BACCDF5E26EAD(Vehicle vehicle, bool p1)l
extern _native64(0x42A4BEB35D372407) any UNK_0x42A4BEB35D372407(any p0)l
extern _native64(0x2C8CBFE1EA5FC631) any UNK_0x2C8CBFE1EA5FC631(any p0)l
extern _native64(0x4D9D109F63FEE1D4) void UNK_0x4D9D109F63FEE1D4(any p0, bool p1)l
extern _native64(0x279D50DE5652D935) void UNK_0x279D50DE5652D935(any p0, bool p1)l
extern _native64(0xE44A982368A4AF23) void UNK_0xE44A982368A4AF23(Vehicle vehicle, Vehicle vehicle2)l
extern _native64(0xF25E02CB9C5818F8) void UNK_0xF25E02CB9C5818F8()l
extern _native64(0xBC3CCA5844452B06) void UNK_0xBC3CCA5844452B06(float p0)l
extern _native64(0x74CD9A9327A282EA) void SET_VEHICLE_SHOOT_AT_TARGET(Ped driver, Entity entity, vector3 Target)l
extern _native64(0x8F5EBAB1F260CFCE) bool _GET_VEHICLE_OWNER(Vehicle vehicle, Entity* entity)l
extern _native64(0x97CE68CB032583F0) void SET_FORCE_HD_VEHICLE(Vehicle vehicle, bool toggle)l
extern _native64(0x182F266C2D9E2BEB) void UNK_0x182F266C2D9E2BEB(Vehicle vehicle, float p1)l
extern _native64(0x9CCC9525BF2408E0) int GET_VEHICLE_PLATE_TYPE(Vehicle vehicle)l
extern _native64(0x64473AEFDCF47DCA) void TRACK_VEHICLE_VISIBILITY(Vehicle vehicle)l
extern _native64(0xAA0A52D24FB98293) bool IS_VEHICLE_VISIBLE(Vehicle vehicle)l
extern _native64(0x89F149B6131E57DA) void SET_VEHICLE_GRAVITY(Vehicle vehicle, bool toggle)l
extern _native64(0xE6C0C80B8C867537) void UNK_0xE6C0C80B8C867537(bool p0)l
extern _native64(0x36492C2F0D134C56) any UNK_0x36492C2F0D134C56(any p0)l
extern _native64(0x06582AFF74894C75) void UNK_0x06582AFF74894C75(any p0, bool p1)l
extern _native64(0xDFFCEF48E511DB48) void UNK_0xDFFCEF48E511DB48(any p0, bool p1)l
extern _native64(0x8D474C8FAEFF6CDE) bool _IS_VEHICLE_SHOP_RESPRAY_ALLOWED(Vehicle vehicle)l
extern _native64(0x983765856F2564F9) void SET_VEHICLE_ENGINE_CAN_DEGRADE(Vehicle vehicle, bool toggle)l
extern _native64(0xF0E4BA16D1DB546C) void UNK_0xF0E4BA16D1DB546C(Vehicle vehicle, int p1, int p2)l
extern _native64(0xF87D9F2301F7D206) void UNK_0xF87D9F2301F7D206(any p0)l
extern _native64(0x4198AB0022B15F87) bool _VEHICLE_HAS_LANDING_GEAR(Vehicle vehicle)l
extern _native64(0x755D6D5267CBBD7E) bool _ARE_PROPELLERS_UNDAMAGED(Vehicle vehicle)l
extern _native64(0x0CDDA42F9E360CA6) void UNK_0x0CDDA42F9E360CA6(Vehicle vehicle, bool p1)l
extern _native64(0x4AF9BD80EEBEB453) bool IS_VEHICLE_STOLEN(Vehicle vehicle)l
extern _native64(0x67B2C79AA7FF5738) any SET_VEHICLE_IS_STOLEN(Vehicle vehicle, bool isStolen)l
extern _native64(0xAD2D28A1AFDFF131) void UNK_0xAD2D28A1AFDFF131(Vehicle vehicle, float p1)l
extern _native64(0x5991A01434CE9677) bool ADD_A_MARKER_OVER_VEHICLE(Vehicle vehicle)l
extern _native64(0xB264C4D2F2B0A78B) void UNK_0xB264C4D2F2B0A78B(Vehicle vehicle)l
extern _native64(0x0E21D3DF1051399D) void DETACH_VEHICLE_FROM_CARGOBOB(Vehicle vehicle, Vehicle cargobob)l
extern _native64(0xADF7BE450512C12F) bool DETACH_VEHICLE_FROM_ANY_CARGOBOB(Vehicle vehicle)l
extern _native64(0xD40148F22E81A1D9) bool IS_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicleAttached)l
extern _native64(0x873B82D42AC2B9E5) Vehicle GET_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob)l
extern _native64(0x4127F1D84E347769) void ATTACH_VEHICLE_TO_CARGOBOB(Vehicle vehicle, Vehicle cargobob, int p2, vector3 vec)l
extern _native64(0x571FEB383F629926) void UNK_0x571FEB383F629926(Vehicle cargobob, bool p1)l
extern _native64(0xCBDB9B923CACC92D) vector3 _GET_CARGOBOB_HOOK_POSITION(Vehicle cargobob)l
extern _native64(0x1821D91AD4B56108) bool DOES_CARGOBOB_HAVE_PICK_UP_ROPE(Vehicle cargobob)l
extern _native64(0x7BEB0C7A235F6F3B) void CREATE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob, int state)l
extern _native64(0x9768CF648F54C804) void REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob)l
extern _native64(0x877C1EAEAC531023) void _SET_CARGOBOB_HOOK_POSITION(any p0, float p1, float p2, int state)l
extern _native64(0xCF1182F682F65307) void UNK_0xCF1182F682F65307(any p0, float p1)l
extern _native64(0x6E08BF5B3722BAC9) bool DOES_CARGOBOB_HAVE_PICKUP_MAGNET(Vehicle cargobob)l
extern _native64(0x9A665550F8DA349B) void SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(Vehicle cargobob, bool isActive)l
extern _native64(0xBCBFCD9D1DAC19E2) void SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(Vehicle cargobob, float strength)l
extern _native64(0xA17BAD153B51547E) void UNK_0xA17BAD153B51547E(Vehicle cargobob, float p1)l
extern _native64(0x66979ACF5102FD2F) void UNK_0x66979ACF5102FD2F(Vehicle cargobob, float p1)l
extern _native64(0x6D8EAC07506291FB) void UNK_0x6D8EAC07506291FB(Vehicle cargobob, float p1)l
extern _native64(0xED8286F71A819BAA) void UNK_0xED8286F71A819BAA(Vehicle cargobob, float p1)l
extern _native64(0x685D5561680D088B) void UNK_0x685D5561680D088B(any p0, float p1)l
extern _native64(0xE301BD63E9E13CF0) void UNK_0xE301BD63E9E13CF0(Vehicle cargobob, Vehicle vehicle)l
extern _native64(0x9BDDC73CC6A115D4) void UNK_0x9BDDC73CC6A115D4(any p0, bool p1, bool p2)l
extern _native64(0x56EB5E94318D3FB6) void UNK_0x56EB5E94318D3FB6(any p0, bool p1)l
extern _native64(0x25ECB9F8017D98E0) bool DOES_VEHICLE_HAVE_WEAPONS(Vehicle vehicle)l
extern _native64(0x2C4A1590ABF43E8B) void UNK_0x2C4A1590ABF43E8B(any p0, bool p1)l
extern _native64(0xF4FC6A6F67D8D856) void DISABLE_VEHICLE_WEAPON(bool disabled, Hash weaponHash, Vehicle vehicle, Ped owner)l
extern _native64(0xE05DD0E9707003A3) void UNK_0xE05DD0E9707003A3(any p0, bool p1)l
extern _native64(0x21115BCD6E44656A) void UNK_0x21115BCD6E44656A(any p0, bool p1)l
extern _native64(0x29439776AAA00A62) int GET_VEHICLE_CLASS(Vehicle vehicle)l
extern _native64(0xDEDF1C8BD47C2200) int GET_VEHICLE_CLASS_FROM_NAME(Hash modelHash)l
extern _native64(0xBCDF8BAF56C87B6A) any SET_PLAYERS_LAST_VEHICLE(Vehicle vehicle)l
extern _native64(0x300504B23BD3B711) void SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(Vehicle vehicle, bool toggle)l
extern _native64(0xE5810AC70602F2F5) void UNK_0xE5810AC70602F2F5(Vehicle vehicle, float p1)l
extern _native64(0x068F64F2470F9656) void _SET_VEHICLE_CREATES_MONEY_PICKUPS_WHEN_EXPLODED(Vehicle vehicle, bool toggle)l
extern _native64(0xB8FBC8B1330CA9B4) void _SET_VEHICLE_JET_ENGINE_ON(Vehicle vehicle, bool toggle)l
extern _native64(0x10655FAB9915623D) void UNK_0x10655FAB9915623D(any p0, any p1)l
extern _native64(0x79DF7E806202CE01) void UNK_0x79DF7E806202CE01(any p0, any p1)l
extern _native64(0x9007A2F21DC108D4) void UNK_0x9007A2F21DC108D4(any p0, float p1)l
extern _native64(0x6E0859B530A365CC) void _SET_HELICOPTER_ROLL_PITCH_YAW_MULT(Vehicle helicopter, float multiplier)l
extern _native64(0x1837AF7C627009BA) void SET_VEHICLE_FRICTION_OVERRIDE(Vehicle vehicle, float friction)l
extern _native64(0xA37B9A517B133349) void SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(Vehicle vehicle, bool toggle)l
extern _native64(0xF78F94D60248C737) bool UNK_0xF78F94D60248C737(any p0, bool p1)l
extern _native64(0xA46413066687A328) void SET_VEHICLE_CEILING_HEIGHT(Vehicle vehicle, float p1)l
extern _native64(0x5E569EC46EC21CAE) void UNK_0x5E569EC46EC21CAE(Vehicle vehicle, bool toggle)l
extern _native64(0x6D6AF961B72728AE) void UNK_0x6D6AF961B72728AE(Vehicle vehicle)l
extern _native64(0x956B409B984D9BF7) bool DOES_VEHICLE_EXIST_WITH_DECORATOR(const char* decorator)l
extern _native64(0x41062318F23ED854) void SET_VEHICLE_EXCLUSIVE_DRIVER(Vehicle vehicle, bool p1)l
extern _native64(0xB5C51B5502E85E83) void _SET_VEHICLE_EXCLUSIVE_DRIVER_2(Vehicle vehicle, Ped ped, int p2)l
extern _native64(0x500873A45724C863) void UNK_0x500873A45724C863(Vehicle vehicle, any p1)l
extern _native64(0xB055A34527CB8FD7) void UNK_0xB055A34527CB8FD7(Vehicle vehicle, bool p1)l
extern _native64(0xF796359A959DF65D) void _DISPLAY_DISTANT_VEHICLES(bool toggle)l
extern _native64(0x8E0A582209A62695) void _SET_VEHICLE_NEON_LIGHTS_COLOUR(Vehicle vehicle, RGB colour)l
extern _native64(0x7619EEE8C886757F) void _GET_VEHICLE_NEON_LIGHTS_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native64(0x2AA720E4287BF269) void _SET_VEHICLE_NEON_LIGHT_ENABLED(Vehicle vehicle, int index, bool toggle)l
extern _native64(0x8C4B92553E4766A5) bool _IS_VEHICLE_NEON_LIGHT_ENABLED(Vehicle vehicle, int index)l
extern _native64(0x35E0654F4BAD7971) void UNK_0x35E0654F4BAD7971(bool p0)l
extern _native64(0xB088E9A47AE6EDD5) void UNK_0xB088E9A47AE6EDD5(Vehicle vehicle, bool p1)l
extern _native64(0xDBA3C090E3D74690) void UNK_0xDBA3C090E3D74690(Vehicle vehicle)l
extern _native64(0xF271147EB7B40F12) float GET_VEHICLE_BODY_HEALTH(Vehicle vehicle)l
extern _native64(0xB77D05AC8C78AADB) void SET_VEHICLE_BODY_HEALTH(Vehicle vehicle, float value)l
extern _native64(0xDF7E3EEB29642C38) void UNK_0xDF7E3EEB29642C38(Vehicle vehicle, any p1, any p2)l
extern _native64(0x53952FD2BAA19F17) float _GET_VEHICLE_SUSPENSION_HEIGHT(Vehicle vehicle)l
extern _native64(0x84FD40F56075E816) void UNK_0x84FD40F56075E816(float p0)l
extern _native64(0xA7DCDF4DED40A8F4) void UNK_0xA7DCDF4DED40A8F4(Vehicle vehicle, bool p1)l
extern _native64(0xB8EF61207C2393A9) float _GET_VEHICLE_BODY_HEALTH_2(Vehicle vehicle)l
extern _native64(0xD4C4642CB7F50B5D) bool UNK_0xD4C4642CB7F50B5D(Vehicle vehicle)l
extern _native64(0xC361AA040D6637A8) void UNK_0xC361AA040D6637A8(any p0, bool p1)l
extern _native64(0x99C82F8A139F3E4E) void _SET_VEHICLE_HUD_SPECIAL_ABILITY_BAR_ACTIVE(Vehicle vehicle, bool p1)l
extern _native64(0xE16142B94664DEFD) void UNK_0xE16142B94664DEFD(any p0, bool p1)l
extern _native64(0x44CD1F493DB2A0A6) void _SET_VEHICLE_WEAPON_CAPACITY(Vehicle vehicle, int weaponIndex, int capacity)l
extern _native64(0x8181CE2F25CB9BB7) int _GET_VEHICLE_WEAPON_CAPACITY(Vehicle vehicle, int weaponIndex)l
extern _native64(0x563B65A643ED072E) bool _IS_VEHICLE_WEAPON_DISABLED(Hash weaponHash, Vehicle vehicle)l
extern _native64(0x36D782F68B309BDA) bool _GET_HAS_VEHICLE_GOT_ROCKET_BOOST(Vehicle vehicle)l
extern _native64(0x3D34E80EED4AE3BE) bool _IS_VEHICLE_ROCKET_BOOST_ACTIVE(Vehicle vehicle)l
extern _native64(0x81E1552E35DC3839) void _SET_ROCKET_BOOST_ACTIVE(Vehicle rocketCar, bool isActive)l
extern _native64(0xE00F2AB100B76E89) void _SET_ROCKET_BOOST_REFILL_TIME(Vehicle rocketCar, float refillTime)l
extern _native64(0x28D034A93FE31BF5) bool _SET_RAMP_VEHICLE_RECEIVES_RAMP_DAMAGE(Vehicle rampCar, bool receivesDamage)l
extern _native64(0xDCA174A42133F08C) bool _GET_HAS_VEHICLE_GOT_RETRACTABLE_WHEELS(Vehicle vehicle)l
extern _native64(0x5335BE58C083E74E) void _SET_WHEELS_RAISED(Vehicle vehicle)l
extern _native64(0xF660602546D27BA8) void _SET_WHEELS_LOWERED(Vehicle vehicle)l
extern _native64(0x1DA0DA9CB3F0C8BF) bool _GET_IS_WHEELS_LOWERED(Vehicle vehicle)l
extern _native64(0xBC9CFF381338CB4F) bool _GET_VEHICLE_HAS_PARACHUTE(Vehicle vehicle)l
extern _native64(0xA916396DF4154EE3) bool _GET_VEHICLE_CAN_USE_PARACHUTE(Vehicle vehicle)l
extern _native64(0x0BFFB028B3DD0A97) void _VEHICLE_PARACHUTE_SET_ACTIVE(Vehicle vehicle, bool isActive)l
extern _native64(0xB7635E80A5C31BFF) void _GET_VEHICLE_DASHBOARD_COLOR(Vehicle vehicle, int* colour)l
extern _native64(0x6089CDF6A57F326C) void _SET_VEHICLE_DASHBOARD_COLOR(Vehicle vehicle, int colour)l
extern _native64(0x7D1464D472D32136) void _GET_VEHICLE_INTERIOR_COLOR(Vehicle vehicle, int* colour)l
extern _native64(0xF40DD601A65F7F19) void _SET_VEHICLE_INTERIOR_COLOR(Vehicle vehicle, int colour)l
extern _native64(0x633F6F44A537EBB6) bool _IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(Hash model)l
extern _native64(0x645F4B6E8499F632) bool _DOES_VEHICLE_HAVE_DOOR(Vehicle vehicle, int doorIndex)l
extern _native64(0x92922A607497B14D) int _GET_NUMBER_OF_VEHICLE_DOORS(Vehicle vehicle)l
extern _native64(0xC0572928C0ABFDA3) vector3 _GET_ENTRY_POSITION_OF_DOOR(Vehicle vehicle, int doorIndex)l
extern _native64(0x5ECB40269053C0D4) int _GET_VEHICLE_LIVERY2_COUNT(Vehicle vehicle)l
extern _native64(0x60190048C0764A26) int _GET_VEHICLE_LIVERY2(Vehicle vehicle)l
extern _native64(0xA6D3A8750DC73270) void _SET_VEHICLE_LIVERY2(Vehicle vehicle, int liveryIndex)l
extern _native64(0x86B4B6212CB8B627) void _SET_VEHICLE_WEAPONS_DISABLED(Vehicle vehicle, bool disable)l
extern _native64(0xB0AD1238A709B1A2) bool _IS_BOAT(Vehicle vehicle)l
extern _native64(0x3B458DDB57038F08) void _SET_VEHICLE_DOOR_UNKN(Vehicle vehicle, int doorIndex, bool p2)l
extern _native64(0x4D610C6B56031351) void _VEHICLE_SET_CUSTOM_PARACHUTE_MODEL(Vehicle vehicle, Hash parachuteModel)l
extern _native64(0xA74AD2439468C883) void _VEHICLE_SET_CUSTOM_PARACHUTE_TEXTURE(Vehicle vehicle, int colorIndex)l
#pragma endregion //}
#pragma region OBJECT //{
extern _native64(0x509D5878EB39E842) Object CREATE_OBJECT(Object modelHash, vector3 vec, bool isNetwork, bool p5, bool dynamic)l
extern _native64(0x9A294B2138ABB884) Object CREATE_OBJECT_NO_OFFSET(Hash modelHash, vector3 vec, bool isNetwork, bool p5, bool dynamic)l
extern _native64(0x539E0AE3E6634B9F) void DELETE_OBJECT(Object* object)l
extern _native64(0x58A850EAEE20FAA3) bool PLACE_OBJECT_ON_GROUND_PROPERLY(Object object)l
extern _native64(0x2FDFF4107B8C1147) bool SLIDE_OBJECT(Object object, vector3 to, vector3 speed, bool collision)l
extern _native64(0x8A7391690F5AFD81) any SET_OBJECT_TARGETTABLE(Object object, bool targettable)l
extern _native64(0x77F33F2CCF64B3AA) void UNK_0x77F33F2CCF64B3AA(Object object, bool p1)l
extern _native64(0xE143FA2249364369) Object GET_CLOSEST_OBJECT_OF_TYPE(vector3 vec, float radius, Hash modelHash, bool isMission, bool p6, bool p7)l
extern _native64(0x8ABFB70C49CC43E2) bool HAS_OBJECT_BEEN_BROKEN(Object object)l
extern _native64(0x761B0E69AC4D007E) bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(float p0, float p1, float p2, float p3, Hash modelHash, any p5)l
extern _native64(0x46494A2475701343) bool UNK_0x46494A2475701343(float p0, float p1, float p2, float p3, Hash modelHash, bool p5)l
extern _native64(0x163E252DE035A133) vector3 _GET_OBJECT_OFFSET_FROM_COORDS(vector3 Pos, float heading, vector3 Offset)l
extern _native64(0x163F8B586BC95F2A) any UNK_0x163F8B586BC95F2A(any coords, float radius, Hash modelHash, vector3 vec, vector3* p6, int p7)l
extern _native64(0xF82D8F1926A02C3D) void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, vector3 vec, bool locked, float heading, bool p6)l
extern _native64(0xEDC1A5B84AEF33FF) void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, vector3 vec, bool* locked, float* heading)l
extern _native64(0x9B12F9A24FABEDB0) void _DOOR_CONTROL(Hash doorHash, vector3 vec, bool locked, float p5, float p6, float p7)l
extern _native64(0x6F8838D03D1DC226) void ADD_DOOR_TO_SYSTEM(Hash doorHash, Hash modelHash, vector3 vec, bool p5, bool p6, bool p7)l
extern _native64(0x464D8E1427156FE4) void REMOVE_DOOR_FROM_SYSTEM(Hash doorHash)l
extern _native64(0x6BAB9442830C7F53) void _SET_DOOR_ACCELERATION_LIMIT(Hash doorHash, int limit, bool p2, bool p3)l
extern _native64(0x160AA1B32F6139B8) int UNK_0x160AA1B32F6139B8(Hash doorHash)l
extern _native64(0x4BC2854478F3A749) int UNK_0x4BC2854478F3A749(Hash doorHash)l
extern _native64(0x03C27E13B42A0E82) void UNK_0x03C27E13B42A0E82(Hash doorHash, float p1, bool p2, bool p3)l
extern _native64(0x9BA001CB45CBF627) void UNK_0x9BA001CB45CBF627(Hash doorHash, float heading, bool p2, bool p3)l
extern _native64(0xB6E6FBA95C7324AC) void _SET_DOOR_AJAR_ANGLE(Hash doorHash, float ajar, bool p2, bool p3)l
extern _native64(0x65499865FCA6E5EC) float UNK_0x65499865FCA6E5EC(Hash doorHash)l
extern _native64(0xC485E07E4F0B7958) void UNK_0xC485E07E4F0B7958(Hash doorHash, bool p1, bool p2, bool p3)l
extern _native64(0xD9B71952F78A2640) void UNK_0xD9B71952F78A2640(Hash doorHash, bool p1)l
extern _native64(0xA85A21582451E951) void UNK_0xA85A21582451E951(Hash doorHash, bool p1)l
extern _native64(0xC153C43EA202C8C1) bool _DOES_DOOR_EXIST(Hash doorHash)l
extern _native64(0xC531EE8A1145A149) bool IS_DOOR_CLOSED(Hash door)l
extern _native64(0xC7F29CA00F46350E) void UNK_0xC7F29CA00F46350E(bool p0)l
extern _native64(0x701FDA1E82076BA4) void UNK_0x701FDA1E82076BA4()l
extern _native64(0xDF97CDD4FC08FD34) bool UNK_0xDF97CDD4FC08FD34(any p0)l
extern _native64(0x589F80B325CC82C5) bool UNK_0x589F80B325CC82C5(float p0, float p1, float p2, any p3, any* p4)l
extern _native64(0x90E47239EA1980B8) bool IS_GARAGE_EMPTY(any garage, bool p1, int p2)l
extern _native64(0x024A60DEB0EA69F0) bool UNK_0x024A60DEB0EA69F0(any p0, Player player, float p2, int p3)l
extern _native64(0x1761DC5D8471CBAA) bool UNK_0x1761DC5D8471CBAA(any p0, Player player, int p2)l
extern _native64(0x85B6C850546FDDE2) bool UNK_0x85B6C850546FDDE2(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native64(0x673ED815D6E323B7) bool UNK_0x673ED815D6E323B7(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native64(0x372EF6699146A1E4) bool UNK_0x372EF6699146A1E4(any p0, Entity entity, float p2, int p3)l
extern _native64(0xF0EED5A6BC7B237A) bool UNK_0xF0EED5A6BC7B237A(any p0, Entity entity, int p2)l
extern _native64(0x190428512B240692) void UNK_0x190428512B240692(any p0, bool p1, bool p2, bool p3, bool p4)l
extern _native64(0xF2E1A7133DD356A6) void UNK_0xF2E1A7133DD356A6(Hash hash, bool toggle)l
extern _native64(0x66A49D021870FE88) void UNK_0x66A49D021870FE88()l
extern _native64(0xBFA48E2FF417213F) bool DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(vector3 vec, float radius, Hash hash, bool p5)l
extern _native64(0x2A70BAE8883E4C81) bool IS_POINT_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, bool p10, bool p11)l
extern _native64(0x4D89D607CB3DD1D2) void UNK_0x4D89D607CB3DD1D2(Object object, bool toggle)l
extern _native64(0xF6DF6E90DE7DF90F) void SET_OBJECT_PHYSICS_PARAMS(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy)l
extern _native64(0xB6FBFD079B8D0596) float GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(any p0, bool p1)l
extern _native64(0x406137F8EF90EAF5) void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Object object, bool toggle)l
extern _native64(0x397DC58FF00298D1) bool IS_ANY_OBJECT_NEAR_POINT(vector3 vec, float range, bool p4)l
extern _native64(0x8C90FE4B381BA60A) bool IS_OBJECT_NEAR_POINT(Hash objectHash, vector3 vec, float range)l
extern _native64(0x4A39DB43E47CF3AA) void UNK_0x4A39DB43E47CF3AA(any p0)l
extern _native64(0xE7E4C198B0185900) void UNK_0xE7E4C198B0185900(Object p0, any p1, bool p2)l
extern _native64(0xF9C1681347C8BD15) void UNK_0xF9C1681347C8BD15(Object object)l
extern _native64(0xB252BC036B525623) void TRACK_OBJECT_VISIBILITY(any p0)l
extern _native64(0x8B32ACE6326A7546) bool IS_OBJECT_VISIBLE(Object object)l
extern _native64(0xC6033D32241F6FB5) void UNK_0xC6033D32241F6FB5(any p0, bool p1)l
extern _native64(0xEB6F1A9B5510A5D2) void UNK_0xEB6F1A9B5510A5D2(any p0, bool p1)l
extern _native64(0xBCE595371A5FBAAF) void UNK_0xBCE595371A5FBAAF(any p0, bool p1)l
extern _native64(0xB48FCED898292E52) int _GET_DES_OBJECT(vector3 vec, float rotation, const char* name)l
extern _native64(0x5C29F698D404C5E1) void _SET_DES_OBJECT_STATE(int handle, int state)l
extern _native64(0x899BA936634A322E) any _GET_DES_OBJECT_STATE(int handle)l
extern _native64(0x52AF537A0C5B8AAD) bool _DOES_DES_OBJECT_EXIST(int handle)l
extern _native64(0x260EE4FDBDF4DB01) float UNK_0x260EE4FDBDF4DB01(any p0)l
extern _native64(0xFBA08C503DD5FA58) Pickup CREATE_PICKUP(Hash pickupHash, vector3 pos, int p4, int value, bool p6, Hash modelHash)l
extern _native64(0x891804727E0A98B7) Pickup CREATE_PICKUP_ROTATE(Hash pickupHash, vector3 pos, vector3 rot, int flag, int amount, any p9, bool p10, Hash modelHash)l
extern _native64(0x673966A0C0FD7171) Pickup CREATE_AMBIENT_PICKUP(Hash pickupHash, vector3 pos, int p4, int value, Hash modelHash, bool p7, bool p8)l
extern _native64(0x2EAF1FDB2FB55698) Pickup CREATE_PORTABLE_PICKUP(Hash pickupHash, vector3 vec, bool placeOnGround, Hash modelHash)l
extern _native64(0x125494B98A21AAF7) Pickup _CREATE_PORTABLE_PICKUP_2(Hash pickupHash, vector3 vec, bool placeOnGround, Hash modelHash)l
extern _native64(0x8DC39368BDD57755) void ATTACH_PORTABLE_PICKUP_TO_PED(Ped ped, any p1)l
extern _native64(0xCF463D1E9A0AECB1) void DETACH_PORTABLE_PICKUP_FROM_PED(Ped ped)l
extern _native64(0x0BF3B3BD47D79C08) void UNK_0x0BF3B3BD47D79C08(any p0, int p1)l
extern _native64(0x78857FC65CADB909) void UNK_0x78857FC65CADB909(bool p0)l
extern _native64(0x6E16BC2503FF1FF0) vector3 GET_SAFE_PICKUP_COORDS(vector3 vec, any p3, any p4)l
extern _native64(0x225B8B35C88029B3) vector3 GET_PICKUP_COORDS(Pickup pickup)l
extern _native64(0x27F9D613092159CF) void REMOVE_ALL_PICKUPS_OF_TYPE(Hash pickupHash)l
extern _native64(0x80EC48E6679313F9) bool HAS_PICKUP_BEEN_COLLECTED(Pickup pickup)l
extern _native64(0x3288D8ACAECD2AB2) void REMOVE_PICKUP(Pickup pickup)l
extern _native64(0x0589B5E791CE9B2B) void CREATE_MONEY_PICKUPS(vector3 vec, int value, int amount, Hash model)l
extern _native64(0xAFC1CA75AD4074D1) bool DOES_PICKUP_EXIST(Pickup pickup)l
extern _native64(0xD9EFB6DBF7DAAEA3) bool DOES_PICKUP_OBJECT_EXIST(Object pickupObject)l
extern _native64(0x5099BC55630B25AE) Object GET_PICKUP_OBJECT(Pickup pickup)l
extern _native64(0x0378C08504160D0D) bool UNK_0x0378C08504160D0D(any p0)l
extern _native64(0xF9C36251F6E48E33) bool _IS_PICKUP_WITHIN_RADIUS(Hash pickupHash, vector3 vec, float radius)l
extern _native64(0x78015C9B4B3ECC9D) void SET_PICKUP_REGENERATION_TIME(any p0, any p1)l
extern _native64(0x616093EC6B139DD9) void UNK_0x616093EC6B139DD9(Player player, Hash pickupHash, bool p2)l
extern _native64(0x88EAEC617CD26926) void UNK_0x88EAEC617CD26926(Hash p0, bool p1)l
extern _native64(0x53E0DF1A2A3CF0CA) void SET_TEAM_PICKUP_OBJECT(Object object, any p1, bool p2)l
extern _native64(0x92AEFB5F6E294023) void UNK_0x92AEFB5F6E294023(Object object, bool p1, bool p2)l
extern _native64(0xA08FE5E49BDC39DD) void UNK_0xA08FE5E49BDC39DD(any p0, float p1, bool p2)l
extern _native64(0xDB41D07A45A6D4B7) any UNK_0xDB41D07A45A6D4B7(any p0)l
extern _native64(0x318516E02DE3ECE2) void UNK_0x318516E02DE3ECE2(float p0)l
extern _native64(0x31F924B53EADDF65) void UNK_0x31F924B53EADDF65(bool p0)l
extern _native64(0xF92099527DB8E2A7) void UNK_0xF92099527DB8E2A7(any p0, any p1)l
extern _native64(0xA2C1F5E92AFE49ED) void UNK_0xA2C1F5E92AFE49ED()l
extern _native64(0x762DB2D380B48D04) void UNK_0x762DB2D380B48D04(any p0)l
extern _native64(0x3430676B11CDF21D) void _HIGHLIGHT_PLACEMENT_COORDS(vector3 vec, int colorIndex)l
extern _native64(0xB2D0BDE54F0E8E5A) void UNK_0xB2D0BDE54F0E8E5A(Object object, bool toggle)l
extern _native64(0x08F96CA6C551AD51) Hash _GET_WEAPON_HASH_FROM_PICKUP(Pickup pickupHash)l
extern _native64(0x11D1E53A726891FE) bool UNK_0x11D1E53A726891FE(any p0)l
extern _native64(0x971DA0055324D033) void _SET_OBJECT_TEXTURE_VARIANT(Object object, int paintIndex)l
extern _native64(0x5EAAD83F8CFB4575) Hash UNK_0x5EAAD83F8CFB4575(Pickup pickupHash)l
extern _native64(0xF538081986E49E9D) void SET_FORCE_OBJECT_THIS_FRAME(any p0, any p1, any p2, any p3)l
extern _native64(0xADBE4809F19F927A) void _MARK_OBJECT_FOR_DELETION(Object object)l
#pragma endregion //}
#pragma region AI //{
extern _native64(0xE73A266DB0CA9042) void TASK_PAUSE(Ped ped, int ms)l
extern _native64(0x919BE13EED931959) void TASK_STAND_STILL(Ped ped, int time)l
extern _native64(0x0AE4086104E067B1) void TASK_JUMP(Ped ped, bool unused)l
extern _native64(0x3EB1FE9E8E908E15) void TASK_COWER(Ped ped, int duration)l
extern _native64(0xF2EAB31979A7F910) void TASK_HANDS_UP(Ped ped, int duration, Ped facingPed, int p3, bool p4)l
extern _native64(0xA98FCAFD7893C834) void UPDATE_TASK_HANDS_UP_DURATION(Ped ped, int duration)l
extern _native64(0x965791A9A488A062) void TASK_OPEN_VEHICLE_DOOR(Ped ped, Vehicle vehicle, int timeOut, int doorIndex, float speed)l
extern _native64(0xC20E50AA46D09CA8) void TASK_ENTER_VEHICLE(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int p5, any p6)l
extern _native64(0xD3DBCE61A490BE02) void TASK_LEAVE_VEHICLE(Ped ped, Vehicle vehicle, int flags)l
extern _native64(0x9C00E77AF14B2DFF) void _TASK_GET_OFF_BOAT(Ped ped, Vehicle boat)l
extern _native64(0x601736CFE536B0A0) void TASK_SKY_DIVE(Ped ped)l
extern _native64(0xD2F1C53C97EE81AB) void TASK_PARACHUTE(Ped ped, bool p1)l
extern _native64(0xB33E291AFA6BD03A) void TASK_PARACHUTE_TO_TARGET(Ped ped, vector3 vec)l
extern _native64(0xC313379AF0FCEDA7) void SET_PARACHUTE_TASK_TARGET(Ped ped, vector3 vec)l
extern _native64(0x0729BAC1B8C64317) void SET_PARACHUTE_TASK_THRUST(Ped ped, float thrust)l
extern _native64(0x09693B0312F91649) void TASK_RAPPEL_FROM_HELI(Ped ped, int unused)l
extern _native64(0xE2A2AA2F659D77A7) void TASK_VEHICLE_DRIVE_TO_COORD(Ped ped, Vehicle vehicle, vector3 vec, float speed, any p6, Hash vehicleModel, int drivingMode, float stopRange, float p10)l
extern _native64(0x158BB33F920D360C) void TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Ped ped, Vehicle vehicle, vector3 vec, float speed, int driveMode, float stopRange)l
extern _native64(0x480142959D337D00) void TASK_VEHICLE_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, int drivingStyle)l
extern _native64(0x304AE42E357B8C7E) void TASK_FOLLOW_TO_OFFSET_OF_ENTITY(Ped ped, Entity entity, vector3 offset, float movementSpeed, int timeout, float stoppingRange, bool persistFollowing)l
extern _native64(0xD76B57B44F1E6F8B) void TASK_GO_STRAIGHT_TO_COORD(Ped ped, vector3 vec, float speed, int timeout, float targetHeading, float distanceToSlide)l
extern _native64(0x61E360B7E040D12E) void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(Entity entity1, Entity entity2, float p2, float p3, float p4, float p5, any p6)l
extern _native64(0x93B93A37987F1F3D) void TASK_ACHIEVE_HEADING(Ped ped, float heading, int timeout)l
extern _native64(0x841142A1376E9006) void TASK_FLUSH_ROUTE()l
extern _native64(0x1E7889778264843A) void TASK_EXTEND_ROUTE(vector3 vec)l
extern _native64(0x595583281858626E) void TASK_FOLLOW_POINT_ROUTE(Ped ped, float speed, int unknown)l
extern _native64(0x6A071245EB0D1882) void TASK_GO_TO_ENTITY(Entity entity, Entity target, int duration, float distance, float speed, float p5, int p6)l
extern _native64(0x94587F17E9C365D5) void TASK_SMART_FLEE_COORD(Ped ped, vector3 vec, float distance, int time, bool p6, bool p7)l
extern _native64(0x22B0D0E37CCB840D) void TASK_SMART_FLEE_PED(Ped ped, Ped fleeTarget, float distance, any fleeTime, bool p4, bool p5)l
extern _native64(0x72C896464915D1B1) void TASK_REACT_AND_FLEE_PED(Ped ped, Ped fleeTarget)l
extern _native64(0x452419CBD838065B) void TASK_SHOCKING_EVENT_REACT(Ped ped, int eventHandle)l
extern _native64(0xE054346CA3A0F315) void TASK_WANDER_IN_AREA(Ped ped, vector3 vec, float radius, float minimalLength, float timeBetweenWalks)l
extern _native64(0xBB9CE077274F6A1B) void TASK_WANDER_STANDARD(Ped ped, float p1, int p2)l
extern _native64(0x0F3E34E968EA374E) void TASK_VEHICLE_PARK(Ped ped, Vehicle vehicle, vector3 vec, float heading, int mode, float radius, bool keepEngineOn)l
extern _native64(0xAA5DC05579D60BD9) any TASK_STEALTH_KILL(Ped killer, Ped target, Hash killType, float p3, bool p4)l
extern _native64(0x965FEC691D55E9BF) void TASK_PLANT_BOMB(Ped ped, vector3 vec, float heading)l
extern _native64(0x15D3A79D4E44B913) void TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, vector3 vec, float speed, int timeout, float stoppingRange, bool persistFollowing, float unk)l
extern _native64(0x17F58B88D085DBAC) void TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(Ped ped, vector3 vec, float speed, int timeout, float unkFloat, int unkInt, vector3 unk, float unk_40000f)l
extern _native64(0x8E06A6FE76C9EFF4) any SET_PED_PATH_CAN_USE_CLIMBOVERS(Ped ped, bool Toggle)l
extern _native64(0x77A5B103C87F476E) any SET_PED_PATH_CAN_USE_LADDERS(Ped ped, bool Toggle)l
extern _native64(0xE361C5C71C431A4F) void SET_PED_PATH_CAN_DROP_FROM_HEIGHT(Ped ped, bool Toggle)l
extern _native64(0x88E32DB8C1A4AA4B) void UNK_0x88E32DB8C1A4AA4B(Ped ped, float p1)l
extern _native64(0xF35425A4204367EC) void SET_PED_PATHS_WIDTH_PLANT(Ped ped, bool mayEnterWater)l
extern _native64(0x38FE1EC73743793C) void SET_PED_PATH_PREFER_TO_AVOID_WATER(Ped ped, bool avoidWater)l
extern _native64(0x4455517B28441E60) void SET_PED_PATH_AVOID_FIRE(Ped ped, bool avoidFire)l
extern _native64(0x6C6B148586F934F7) void SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(float height)l
extern _native64(0xC6F5C0BCDC74D62D) any GET_NAVMESH_ROUTE_DISTANCE_REMAINING(Ped ped, any* p1, any* p2)l
extern _native64(0x632E831F382A0FA8) int GET_NAVMESH_ROUTE_RESULT(Ped ped)l
extern _native64(0x3E38E28A1D80DDF6) bool UNK_0x3E38E28A1D80DDF6(Ped ped)l
extern _native64(0x5BC448CB78FA3E88) void TASK_GO_TO_COORD_ANY_MEANS(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8)l
extern _native64(0x1DD45F9ECFDB1BC9) void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8, any p9, any p10, any p11)l
extern _native64(0xB8ECD61F531A7B02) void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8, any p9, any p10, any p11, any p12)l
extern _native64(0xEA47FE3719165B94) void TASK_PLAY_ANIM(Ped ped, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, bool lockX, bool lockY, bool lockZ)l
extern _native64(0x83CDB10EA29B370B) void TASK_PLAY_ANIM_ADVANCED(Ped ped, const char* animDict, const char* animName, vector3 pos, vector3 rot, float speed, float speedMultiplier, int duration, any flag, float animTime, any p14, any p15)l
extern _native64(0x97FF36A1D40EA00A) void STOP_ANIM_TASK(Ped ped, const char* animDictionary, const char* animationName, float p3)l
extern _native64(0x126EF75F1E17ABE5) void TASK_SCRIPTED_ANIMATION(Ped ped, any* p1, any* p2, any* p3, float p4, float p5)l
extern _native64(0x77A1EEC547E7FCF1) void PLAY_ENTITY_SCRIPTED_ANIM(any p0, any* p1, any* p2, any* p3, float p4, float p5)l
extern _native64(0xEE08C992D238C5D1) void STOP_ANIM_PLAYBACK(Ped ped, any p1, bool p2)l
extern _native64(0x207F1A47C0342F48) void SET_ANIM_WEIGHT(any p0, float p1, any p2, any p3, bool p4)l
extern _native64(0x032D49C5E359C847) void SET_ANIM_RATE(any p0, float p1, any p2, bool p3)l
extern _native64(0x70033C3CC29A1FF4) void SET_ANIM_LOOPED(any p0, bool p1, any p2, bool p3)l
extern _native64(0x8FBB6758B3B3E9EC) void TASK_PLAY_PHONE_GESTURE_ANIMATION(Ped ped, const char* animDict, const char* animation, const char* boneMaskType, float p4, float p5, bool p6, bool p7)l
extern _native64(0x3FA00D4F4641BFAE) void _TASK_STOP_PHONE_GESTURE_ANIMATION(Ped ped)l
extern _native64(0xB8EBB1E9D3588C10) bool IS_PLAYING_PHONE_GESTURE_ANIM(Ped ped)l
extern _native64(0x47619ABE8B268C60) float GET_PHONE_GESTURE_ANIM_CURRENT_TIME(Ped ped)l
extern _native64(0x1EE0F68A7C25DEC6) float GET_PHONE_GESTURE_ANIM_TOTAL_TIME(Ped ped)l
extern _native64(0x69F5C3BD0F3EBD89) void TASK_VEHICLE_PLAY_ANIM(Vehicle vehicle, const char* animation_set, const char* animation_name)l
extern _native64(0x6FA46612594F7973) void TASK_LOOK_AT_COORD(Entity entity, vector3 vec, float duration, any p5, any p6)l
extern _native64(0x69F4BE8C8CC4796C) void TASK_LOOK_AT_ENTITY(Ped ped, Entity lookAt, int duration, int unknown1, int unknown2)l
extern _native64(0x0F804F1DB19B9689) void TASK_CLEAR_LOOK_AT(Ped ped)l
extern _native64(0xE8854A4326B9E12B) any OPEN_SEQUENCE_TASK(Object* taskSequence)l
extern _native64(0x39E72BC99E6360CB) any CLOSE_SEQUENCE_TASK(Object taskSequence)l
extern _native64(0x5ABA3986D90D8A3B) any TASK_PERFORM_SEQUENCE(Ped ped, Object taskSequence)l
extern _native64(0x3841422E9C488D8C) any CLEAR_SEQUENCE_TASK(Object* taskSequence)l
extern _native64(0x58C70CF3A41E4AE7) void SET_SEQUENCE_TO_REPEAT(Object taskSequence, bool repeat)l
extern _native64(0x00A9010CFE1E3533) int GET_SEQUENCE_PROGRESS(Ped ped)l
extern _native64(0xB0760331C7AA4155) bool GET_IS_TASK_ACTIVE(Ped ped, int taskNumber)l
extern _native64(0x77F1BEB8863288D5) int GET_SCRIPT_TASK_STATUS(Ped targetPed, Hash taskHash)l
extern _native64(0x534AEBA6E5ED4CAB) int GET_ACTIVE_VEHICLE_MISSION_TYPE(Vehicle veh)l
extern _native64(0x504D54DF3F6F2247) void TASK_LEAVE_ANY_VEHICLE(Ped ped, int p1, int p2)l
extern _native64(0x7A192BE16D373D00) void TASK_AIM_GUN_SCRIPTED(Ped ped, Hash scriptTask, bool p2, bool p3)l
extern _native64(0x8605AF0DE8B3A5AC) void TASK_AIM_GUN_SCRIPTED_WITH_TARGET(any p0, any p1, float p2, float p3, float p4, any p5, bool p6, bool p7)l
extern _native64(0x9724FB59A3E72AD0) void UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(Ped p0, Ped p1, float p2, float p3, float p4, bool p5)l
extern _native64(0x3A8CADC7D37AACC5) const char* GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(int p0)l
extern _native64(0x9B53BB6E8943AF53) void TASK_AIM_GUN_AT_ENTITY(Ped ped, Entity entity, int duration, bool p3)l
extern _native64(0x5AD23D40115353AC) void TASK_TURN_PED_TO_FACE_ENTITY(Ped ped, Entity entity, int duration)l
extern _native64(0x6671F3EEC681BDA1) void TASK_AIM_GUN_AT_COORD(Ped ped, vector3 vec, int time, bool p5, bool p6)l
extern _native64(0x46A6CC01E0826106) void TASK_SHOOT_AT_COORD(Ped ped, vector3 vec, int duration, Hash firingPattern)l
extern _native64(0x7AA80209BDA643EB) void TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(Ped ped, Vehicle vehicle)l
extern _native64(0xE1EF3C1216AFF2CD) void CLEAR_PED_TASKS(Ped ped)l
extern _native64(0x176CECF6F920D707) void CLEAR_PED_SECONDARY_TASK(Ped ped)l
extern _native64(0x7F93691AB4B92272) void TASK_EVERYONE_LEAVE_VEHICLE(Vehicle vehicle)l
extern _native64(0xE39B4FF4FDEBDE27) void TASK_GOTO_ENTITY_OFFSET(Ped ped, any p1, any p2, vector3 vec, int duration)l
extern _native64(0x338E7EF52B6095A9) void TASK_GOTO_ENTITY_OFFSET_XY(any p0, any p1, any p2, float p3, float p4, float p5, float p6, any p7)l
extern _native64(0x1DDA930A0AC38571) void TASK_TURN_PED_TO_FACE_COORD(Ped ped, vector3 vec, int duration)l
extern _native64(0xC429DCEEB339E129) void TASK_VEHICLE_TEMP_ACTION(Ped driver, Vehicle vehicle, int action, int time)l
extern _native64(0x659427E0EF36BCDE) void TASK_VEHICLE_MISSION(any p0, any p1, any p2, any p3, float p4, any p5, float p6, float p7, bool p8)l
extern _native64(0x9454528DF15D657A) void TASK_VEHICLE_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped pedTarget, int mode, float maxSpeed, int drivingStyle, float minDistance, float p7, bool p8)l
extern _native64(0xF0AF20AA7731F8C3) void TASK_VEHICLE_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, vector3 vec, int p5, int p6, int p7, float p8, float p9, bool p10)l
extern _native64(0x0FA6E4B75F302400) void TASK_VEHICLE_ESCORT(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int p7, float noRoadsDistance)l
extern _native64(0xFC545A9F0626E3B6) void _TASK_VEHICLE_FOLLOW(Ped driver, Vehicle vehicle, Entity targetEntity, int drivingStyle, float speed, int minDistance)l
extern _native64(0x3C08A8E30363B353) void TASK_VEHICLE_CHASE(Ped driver, Entity targetEnt)l
extern _native64(0x1E09C32048FEFD1C) void TASK_VEHICLE_HELI_PROTECT(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int p4, float radius, int altitude, int p7)l
extern _native64(0xCC665AAC360D31E7) void SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(Ped ped, int flag, bool set)l
extern _native64(0x639B642FACBE4EDD) void SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(Ped ped, float distance)l
extern _native64(0xAC83B1DB38D0ADA0) void TASK_HELI_CHASE(Ped pilot, Entity entityToFollow, vector3 vec)l
extern _native64(0x2D2386F273FF7A25) void TASK_PLANE_CHASE(Ped pilot, Entity entityToFollow, vector3 vec)l
extern _native64(0xBF19721FA34D32C0) void TASK_PLANE_LAND(Ped pilot, Vehicle plane, vector3 runwayStart, vector3 runwayEnd)l
extern _native64(0xDAD029E187A2BEB4) void TASK_HELI_MISSION(Ped pilot, Vehicle vehicle, Vehicle vehicleToFollow, Ped pedToFollow, vector3 pos, int mode, float speed, float radius, float angle, int p11, int height, float p13, int p14)l
extern _native64(0x23703CD154E83B88) void TASK_PLANE_MISSION(Ped pilot, Vehicle plane, Vehicle targetVehicle, Ped targetPed, vector3 destination, int missionType, float vehicleSpeed, float p9, float heading, float maxAltitude, float minAltitude)l
extern _native64(0x15C86013127CE63F) void TASK_BOAT_MISSION(Ped pedDriver, Vehicle boat, any p2, any p3, vector3 vec, any p7, float maxSpeed, int drivingStyle, float p10, any p11)l
extern _native64(0x2F8AF0E82773A171) void TASK_DRIVE_BY(Ped driverPed, Ped targetPed, Vehicle targetVehicle, vector3 target, float distanceToShoot, int pedAccuracy, bool p8, Hash firingPattern)l
extern _native64(0xE5B302114D8162EE) void SET_DRIVEBY_TASK_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, vector3 vec)l
extern _native64(0xC35B5CDB2824CF69) void CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native64(0x8785E6E40C7A8818) bool IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native64(0xDCFE42068FE0135A) bool CONTROL_MOUNTED_WEAPON(Ped ped)l
extern _native64(0xCCD892192C6D2BB9) void SET_MOUNTED_WEAPON_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, vector3 vec)l
extern _native64(0xA320EF046186FA3B) bool IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native64(0xBD2A8EC3AF4DE7DB) void TASK_USE_MOBILE_PHONE(Ped ped, int p1)l
extern _native64(0x5EE02954A14C69DB) void TASK_USE_MOBILE_PHONE_TIMED(Ped ped, int duration)l
extern _native64(0x8C338E0263E4FD19) void TASK_CHAT_TO_PED(Ped ped, Ped target, any p2, float p3, float p4, float p5, float p6, float p7)l
extern _native64(0x9A7D091411C5F684) void TASK_WARP_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seat)l
extern _native64(0x08DA95E8298AE772) void TASK_SHOOT_AT_ENTITY(Entity entity, Entity target, int duration, Hash firingPattern)l
extern _native64(0x89D9FCC2435112F1) void TASK_CLIMB(Ped ped, bool unused)l
extern _native64(0xB6C987F9285A3814) void TASK_CLIMB_LADDER(Ped ped, int p1)l
extern _native64(0xAAA34F8A7CB32098) void CLEAR_PED_TASKS_IMMEDIATELY(Ped ped)l
extern _native64(0x89221B16730234F0) void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(any p0, any p1, any p2, any p3)l
extern _native64(0xF1B9F16E89E2C93A) void SET_NEXT_DESIRED_MOVE_STATE(float p0)l
extern _native64(0x1E982AC8716912C5) void SET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped, float p1)l
extern _native64(0x8517D4A6CA8513ED) float GET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped)l
extern _native64(0xA9DA48FAB8A76C12) void TASK_GOTO_ENTITY_AIMING(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist)l
extern _native64(0xEB8517DDA73720DA) void TASK_SET_DECISION_MAKER(Ped p0, Hash p1)l
extern _native64(0x933C06518B52A9A4) void TASK_SET_SPHERE_DEFENSIVE_AREA(any p0, float p1, float p2, float p3, float p4)l
extern _native64(0x95A6C46A31D1917D) void TASK_CLEAR_DEFENSIVE_AREA(any p0)l
extern _native64(0xD04FE6765D990A06) void TASK_PED_SLIDE_TO_COORD(Ped ped, vector3 vec, float heading, float p5)l
extern _native64(0x5A4A6A6D3DC64F52) void TASK_PED_SLIDE_TO_COORD_HDG_RATE(Ped ped, vector3 vec, float heading, float p5, float p6)l
extern _native64(0xD5C12A75C7B9497F) ScrHandle ADD_COVER_POINT(float p0, float p1, float p2, float p3, any p4, any p5, any p6, bool p7)l
extern _native64(0xAE287C923D891715) void REMOVE_COVER_POINT(ScrHandle coverpoint)l
extern _native64(0xA98B8E3C088E5A31) bool DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(vector3 vec)l
extern _native64(0x594A1028FC2A3E85) vector3 GET_SCRIPTED_COVER_POINT_COORDS(ScrHandle coverpoint)l
extern _native64(0xF166E48407BAC484) void TASK_COMBAT_PED(Ped ped, Ped targetPed, int p2, int p3)l
extern _native64(0x944F30DCB7096BDE) void TASK_COMBAT_PED_TIMED(any p0, Ped ped, int p2, any p3)l
extern _native64(0x75AC2B60386D89F2) void TASK_SEEK_COVER_FROM_POS(Ped ped, vector3 vec, int duration, bool p5)l
extern _native64(0x84D32B3BEC531324) void TASK_SEEK_COVER_FROM_PED(Ped ped, Ped target, int duration, bool p3)l
extern _native64(0xD43D95C7A869447F) void TASK_SEEK_COVER_TO_COVER_POINT(any p0, any p1, float p2, float p3, float p4, any p5, bool p6)l
extern _native64(0x39246A6958EF072C) void TASK_SEEK_COVER_TO_COORDS(Ped ped, vector3 vec_1, vector3 vec_2, any p7, bool p8)l
extern _native64(0x4172393E6BE1FECE) void TASK_PUT_PED_DIRECTLY_INTO_COVER(Ped ped, vector3 vec, any timeout, bool p5, float p6, bool p7, bool p8, any p9, bool p10)l
extern _native64(0x79B258E397854D29) void TASK_EXIT_COVER(any p0, any p1, float p2, float p3, float p4)l
extern _native64(0x1C6CD14A876FFE39) void TASK_PUT_PED_DIRECTLY_INTO_MELEE(Ped ped, Ped meleeTarget, float p2, float p3, float p4, bool p5)l
extern _native64(0xAC96609B9995EDF8) void TASK_TOGGLE_DUCK(bool p0, bool p1)l
extern _native64(0x4A58A47A72E3FCB4) void TASK_GUARD_CURRENT_POSITION(Ped p0, float p1, float p2, bool p3)l
extern _native64(0xD2A207EEBDF9889B) void TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(any p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native64(0xC946FE14BE0EB5E2) void TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped p0, float p1, float p2, float p3, float p4, float p5, any p6, float p7, float p8, float p9, float p10)l
extern _native64(0xAE032F8BBA959E90) void TASK_STAND_GUARD(Ped ped, vector3 vec, float heading, const char* scenarioName)l
extern _native64(0x5C9B84BD7D31D908) void SET_DRIVE_TASK_CRUISE_SPEED(Ped driver, float cruiseSpeed)l
extern _native64(0x404A5AA9B9F0B746) void SET_DRIVE_TASK_MAX_CRUISE_SPEED(any p0, float p1)l
extern _native64(0xDACE1BE37D88AF67) void SET_DRIVE_TASK_DRIVING_STYLE(Ped ped, int drivingStyle)l
extern _native64(0x45C597097DD7CB81) void ADD_COVER_BLOCKING_AREA(vector3 player, vector3 radius, bool p6, bool p7, bool p8, bool p9)l
extern _native64(0xDB6708C0B46F56D8) void REMOVE_ALL_COVER_BLOCKING_AREAS()l
extern _native64(0x142A02425FF02BD9) void TASK_START_SCENARIO_IN_PLACE(Ped ped, const char* scenarioName, int unkDelay, bool playEnterAnim)l
extern _native64(0xFA4EFC79F69D4F07) void TASK_START_SCENARIO_AT_POSITION(Ped ped, const char* scenarioName, vector3 vec, float heading, int duration, bool sittingScenario, bool teleport)l
extern _native64(0x277F471BA9DB000B) void TASK_USE_NEAREST_SCENARIO_TO_COORD(Ped ped, vector3 vec, float distance, int duration)l
extern _native64(0x58E2E0F23F6B76C3) void TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(Ped ped, vector3 vec, float radius, any p5)l
extern _native64(0x9FDA1B3D7E7028B3) void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(any p0, float p1, float p2, float p3, float p4, any p5)l
extern _native64(0x97A28E63F0BA5631) void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(any p0, float p1, float p2, float p3, float p4, any p5)l
extern _native64(0x5A59271FFADD33C1) bool DOES_SCENARIO_EXIST_IN_AREA(vector3 vec, float radius, bool b)l
extern _native64(0x0A9D0C2A3BBC86C1) bool DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(float p0, float p1, float p2, any* p3, float p4, bool p5)l
extern _native64(0x788756D73AC2E07C) bool IS_SCENARIO_OCCUPIED(float p0, float p1, float p2, float p3, bool p4)l
extern _native64(0x295E3CCEC879CCD7) bool PED_HAS_USE_SCENARIO_TASK(Ped ped)l
extern _native64(0x748040460F8DF5DC) void PLAY_ANIM_ON_RUNNING_SCENARIO(Ped ped, const char* animDict, const char* animName)l
extern _native64(0xF9034C136C9E00D3) bool DOES_SCENARIO_GROUP_EXIST(const char* scenarioGroup)l
extern _native64(0x367A09DED4E05B99) bool IS_SCENARIO_GROUP_ENABLED(const char* scenarioGroup)l
extern _native64(0x02C8E5B49848664E) void SET_SCENARIO_GROUP_ENABLED(const char* scenarioGroup, bool p1)l
extern _native64(0xDD902D0349AFAD3A) void RESET_SCENARIO_GROUPS_ENABLED()l
extern _native64(0x535E97E1F7FC0C6A) void SET_EXCLUSIVE_SCENARIO_GROUP(const char* scenarioGroup)l
extern _native64(0x4202BBCB8684563D) void RESET_EXCLUSIVE_SCENARIO_GROUP()l
extern _native64(0x3A815DB3EA088722) bool IS_SCENARIO_TYPE_ENABLED(const char* scenarioType)l
extern _native64(0xEB47EC4E34FB7EE1) void SET_SCENARIO_TYPE_ENABLED(const char* scenarioType, bool toggle)l
extern _native64(0x0D40EE2A7F2B2D6D) void RESET_SCENARIO_TYPES_ENABLED()l
extern _native64(0xAA135F9482C82CC3) bool IS_PED_ACTIVE_IN_SCENARIO(Ped ped)l
extern _native64(0x621C6E4729388E41) bool UNK_0x621C6E4729388E41(Ped ped)l
extern _native64(0x8FD89A6240813FD0) void UNK_0x8FD89A6240813FD0(Ped ped, bool p1, bool p2)l
extern _native64(0x4CF5F55DAC3280A0) void TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, vector3 vec, float radius, any p5)l
extern _native64(0x7BF835BB9E2698C8) void TASK_COMBAT_HATED_TARGETS_AROUND_PED(Ped ped, float radius, int p2)l
extern _native64(0x2BBA30B854534A0C) void TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(any p0, float p1, any p2, any p3)l
extern _native64(0x7285951DBF6B5A51) void TASK_THROW_PROJECTILE(int ped, vector3 vec)l
extern _native64(0xA21C51255B205245) void TASK_SWAP_WEAPON(Ped ped, bool p1)l
extern _native64(0x62D2916F56B9CD2D) void TASK_RELOAD_WEAPON(Ped ped, bool unused)l
extern _native64(0x2A74E1D5F2F00EEC) bool IS_PED_GETTING_UP(Ped ped)l
extern _native64(0xCDDC2B77CE54AC6E) void TASK_WRITHE(Ped ped, Ped target, int time, int p3)l
extern _native64(0xDEB6D52126E7D640) bool IS_PED_IN_WRITHE(Ped ped)l
extern _native64(0xA36BFB5EE89F3D82) void OPEN_PATROL_ROUTE(const char* patrolRoute)l
extern _native64(0xB043ECA801B8CBC1) void CLOSE_PATROL_ROUTE()l
extern _native64(0x8EDF950167586B7C) void ADD_PATROL_ROUTE_NODE(int p0, const char* p1, vector3 vec_1, vector3 vec_2, int p8)l
extern _native64(0x23083260DEC3A551) void ADD_PATROL_ROUTE_LINK(any p0, any p1)l
extern _native64(0xAF8A443CCC8018DC) void CREATE_PATROL_ROUTE()l
extern _native64(0x7767DD9D65E91319) void DELETE_PATROL_ROUTE(const char* patrolRoute)l
extern _native64(0xBDA5DF49D080FE4E) void TASK_PATROL(Ped ped, const char* p1, any p2, bool p3, bool p4)l
extern _native64(0xE5DA8615A6180789) void TASK_STAY_IN_COVER(Ped ped)l
extern _native64(0x5CF0D8F9BBA0DD75) void ADD_VEHICLE_SUBTASK_ATTACK_COORD(Ped ped, vector3 vec)l
extern _native64(0x85F462BADC7DA47F) void ADD_VEHICLE_SUBTASK_ATTACK_PED(Ped ped, Ped ped2)l
extern _native64(0x10AB107B887214D8) void TASK_VEHICLE_SHOOT_AT_PED(Ped ped, Ped target, float p2)l
extern _native64(0xE41885592B08B097) void TASK_VEHICLE_AIM_AT_PED(Ped ped, Ped target)l
extern _native64(0x5190796ED39C9B6D) void TASK_VEHICLE_SHOOT_AT_COORD(Ped ped, vector3 vec, float p4)l
extern _native64(0x447C1E9EF844BC0F) void TASK_VEHICLE_AIM_AT_COORD(Ped ped, vector3 vec)l
extern _native64(0x195AEEB13CEFE2EE) void TASK_VEHICLE_GOTO_NAVMESH(Ped ped, Vehicle vehicle, vector3 vec, float speed, int behaviorFlag, float stoppingRange)l
extern _native64(0x11315AB3385B8AC0) void TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Ped ped, vector3 vec, vector3 aimAt, float moveSpeed, bool p8, float p9, float p10, bool p11, any flags, bool p13, Hash firingPattern)l
extern _native64(0xB2A16444EAD9AE47) void TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(any p0, float p1, float p2, float p3, any p4, float p5, bool p6, float p7, float p8, bool p9, any p10, bool p11, any p12, any p13)l
extern _native64(0xA55547801EB331FC) void TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(Ped pedHandle, vector3 goToLocation, vector3 focusLocation, float speed, bool shootAtEnemies, float distanceToStopAt, float noRoadsDistance, bool unkTrue, int unkFlag, int aimingFlag, Hash firingPattern)l
extern _native64(0x04701832B739DCE5) void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(any p0, any p1, float p2, float p3, float p4, float p5, bool p6, float p7, float p8, bool p9, bool p10, any p11)l
extern _native64(0x97465886D35210E9) void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, bool shootatEntity, float p5, float p6, bool p7, bool p8, Hash firingPattern)l
extern _native64(0x8C825BDC7741D37C) void SET_HIGH_FALL_TASK(Ped ped, any p1, any p2, any p3)l
extern _native64(0x9EEFB62EB27B5792) void REQUEST_WAYPOINT_RECORDING(const char* name)l
extern _native64(0xCB4E8BE8A0063C5D) bool GET_IS_WAYPOINT_RECORDING_LOADED(const char* name)l
extern _native64(0xFF1B8B4AA1C25DC8) void REMOVE_WAYPOINT_RECORDING(const char* name)l
extern _native64(0x5343532C01A07234) bool WAYPOINT_RECORDING_GET_NUM_POINTS(const char* name, int* points)l
extern _native64(0x2FB897405C90B361) bool WAYPOINT_RECORDING_GET_COORD(const char* name, int point, vector3* coord)l
extern _native64(0x005622AEBC33ACA9) float WAYPOINT_RECORDING_GET_SPEED_AT_POINT(const char* name, int point)l
extern _native64(0xB629A298081F876F) bool WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(const char* name, vector3 vec, int* point)l
extern _native64(0x0759591819534F7B) void TASK_FOLLOW_WAYPOINT_RECORDING(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xE03B3F2D3DC59B64) bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(any p0)l
extern _native64(0x2720AAA75001E094) any GET_PED_WAYPOINT_PROGRESS(any p0)l
extern _native64(0xE6A877C64CAF1BC5) float GET_PED_WAYPOINT_DISTANCE(any p0)l
extern _native64(0xED98E10B0AFCE4B4) any SET_PED_WAYPOINT_ROUTE_OFFSET(any p0, any p1, any p2, any p3)l
extern _native64(0xA5B769058763E497) float GET_WAYPOINT_DISTANCE_ALONG_ROUTE(const char* p0, int p1)l
extern _native64(0x701375A7D43F01CB) bool WAYPOINT_PLAYBACK_GET_IS_PAUSED(any p0)l
extern _native64(0x0F342546AA06FED5) void WAYPOINT_PLAYBACK_PAUSE(any p0, bool p1, bool p2)l
extern _native64(0x244F70C84C547D2D) void WAYPOINT_PLAYBACK_RESUME(any p0, bool p1, any p2, any p3)l
extern _native64(0x7D7D2B47FA788E85) void WAYPOINT_PLAYBACK_OVERRIDE_SPEED(any p0, float p1, bool p2)l
extern _native64(0x6599D834B12D0800) void WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(any p0)l
extern _native64(0x5A353B8E6B1095B5) void USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(any* p0, bool p1, float p2, float p3)l
extern _native64(0x20E330937C399D29) void WAYPOINT_PLAYBACK_START_AIMING_AT_PED(any p0, any p1, bool p2)l
extern _native64(0x8968400D900ED8B3) void WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(any p0, float p1, float p2, float p3, bool p4)l
extern _native64(0xE70BA7B90F8390DC) void UNK_0xE70BA7B90F8390DC(any p0, any p1, bool p2, any p3)l
extern _native64(0x057A25CFCC9DB671) void WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(any p0, float p1, float p2, float p3, bool p4, any p5)l
extern _native64(0x47EFA040EBB8E2EA) void WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(any p0)l
extern _native64(0x817268968605947A) void ASSISTED_MOVEMENT_REQUEST_ROUTE(const char* route)l
extern _native64(0x3548536485DD792B) void ASSISTED_MOVEMENT_REMOVE_ROUTE(const char* route)l
extern _native64(0x60F9A4393A21F741) bool ASSISTED_MOVEMENT_IS_ROUTE_LOADED(const char* route)l
extern _native64(0xD5002D78B7162E1B) void ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(const char* route, int props)l
extern _native64(0x13945951E16EF912) void ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(float dist)l
extern _native64(0x3123FAA6DB1CF7ED) void TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(Ped ped, Vehicle vehicle, const char* WPRecording, int p3, int p4, int p5, int p6, float p7, bool p8, float p9)l
extern _native64(0xF5134943EA29868C) bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(any p0)l
extern _native64(0x9824CFF8FC66E159) any GET_VEHICLE_WAYPOINT_PROGRESS(any p0)l
extern _native64(0x416B62AC8B9E5BBD) any GET_VEHICLE_WAYPOINT_TARGET_POINT(any p0)l
extern _native64(0x8A4E6AC373666BC5) void VEHICLE_WAYPOINT_PLAYBACK_PAUSE(any p0)l
extern _native64(0xDC04FCAA7839D492) void VEHICLE_WAYPOINT_PLAYBACK_RESUME(any p0)l
extern _native64(0x5CEB25A7D2848963) void VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(any p0)l
extern _native64(0x121F0593E0A431D7) void VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(any p0, float p1)l
extern _native64(0x90D2156198831D69) void TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)l
extern _native64(0x4F056E1AFFEF17AB) void TASK_FORCE_MOTION_STATE(Ped ped, Hash state, bool p2)l
extern _native64(0x2D537BA194896636) void _TASK_MOVE_NETWORK(Ped ped, const char* task, float multiplier, bool p3, const char* animDict, int flags)l
extern _native64(0xD5B35BEA41919ACB) void _TASK_MOVE_NETWORK_ADVANCED(Ped ped, const char* p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8, float p9, bool p10, const char* animDict, int flags)l
extern _native64(0x921CE12C489C4C41) bool UNK_0x921CE12C489C4C41(int PlayerID)l
extern _native64(0x30ED88D5E0C56A37) bool UNK_0x30ED88D5E0C56A37(any p0)l
extern _native64(0xD01015C7316AE176) any UNK_0xD01015C7316AE176(Ped ped, const char* p1)l
extern _native64(0xAB13A5565480B6D9) any UNK_0xAB13A5565480B6D9(any p0, any p1)l
extern _native64(0x717E4D1F2048376D) const char* UNK_0x717E4D1F2048376D(Ped ped)l
extern _native64(0xD5BB4025AE449A4E) void UNK_0xD5BB4025AE449A4E(Ped p0, const char* p1, float p2)l
extern _native64(0xB0A6CFD2C69C1088) void UNK_0xB0A6CFD2C69C1088(Ped p0, any* p1, bool p2)l
extern _native64(0xA7FFBA498E4AAF67) bool UNK_0xA7FFBA498E4AAF67(any p0, const char* p1)l
extern _native64(0xB4F47213DF45A64C) bool UNK_0xB4F47213DF45A64C(any p0, any* p1)l
extern _native64(0x349CE7B56DAFD95C) bool IS_MOVE_BLEND_RATIO_STILL(Ped ped)l
extern _native64(0xF133BBBE91E1691F) bool IS_MOVE_BLEND_RATIO_WALKING(Ped ped)l
extern _native64(0xD4D8636C0199A939) bool IS_MOVE_BLEND_RATIO_RUNNING(Ped ped)l
extern _native64(0x24A2AD74FA9814E2) bool IS_MOVE_BLEND_RATIO_SPRINTING(Ped ped)l
extern _native64(0xAC29253EEF8F0180) bool IS_PED_STILL(Ped ped)l
extern _native64(0xDE4C184B2B9B071A) bool IS_PED_WALKING(Ped ped)l
extern _native64(0xC5286FFC176F28A2) bool IS_PED_RUNNING(Ped ped)l
extern _native64(0x57E457CD2C0FC168) bool IS_PED_SPRINTING(Ped ped)l
extern _native64(0xE45B7F222DE47E09) bool IS_PED_STRAFING(Ped ped)l
extern _native64(0xEEA929141F699854) void TASK_SYNCHRONIZED_SCENE(Ped ped, int scene, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, any p9)l
extern _native64(0x2047C02158D6405A) void TASK_SWEEP_AIM_ENTITY(Ped ped, const char* anim, const char* p2, const char* p3, const char* p4, int p5, Vehicle vehicle, float p7, float p8)l
extern _native64(0xE4973DBDBE6E44B3) void UPDATE_TASK_SWEEP_AIM_ENTITY(Ped ped, Entity entity)l
extern _native64(0x7AFE8FDC10BC07D2) void TASK_SWEEP_AIM_POSITION(any p0, any* p1, any* p2, any* p3, any* p4, any p5, float p6, float p7, float p8, float p9, float p10)l
extern _native64(0xBB106883F5201FC4) void UPDATE_TASK_SWEEP_AIM_POSITION(any p0, float p1, float p2, float p3)l
extern _native64(0xF3B9A78A178572B1) void TASK_ARREST_PED(Ped ped, Ped target)l
extern _native64(0x3DC52677769B4AE0) bool IS_PED_RUNNING_ARREST_TASK(Ped ped)l
extern _native64(0x90A09F3A45FED688) bool IS_PED_BEING_ARRESTED(Ped ped)l
extern _native64(0x67406F2C8F87FC4F) void UNCUFF_PED(Ped ped)l
extern _native64(0x74E559B3BC910685) bool IS_PED_CUFFED(Ped ped)l
#pragma endregion //}
#pragma region GAMEPLAY //{
extern _native64(0x8B3CA62B1EF19B62) int GET_ALLOCATED_STACK_SIZE()l
extern _native64(0xFEAD16FC8F9DFC0F) int _GET_FREE_STACK_SLOTS_COUNT(int stackSize)l
extern _native64(0x444D98F98C11F3EC) void SET_RANDOM_SEED(int time)l
extern _native64(0x1D408577D440E81E) void SET_TIME_SCALE(float time)l
extern _native64(0xC4301E5121A0ED73) void SET_MISSION_FLAG(bool toggle)l
extern _native64(0xA33CDCCDA663159E) bool GET_MISSION_FLAG()l
extern _native64(0x971927086CFD2158) void SET_RANDOM_EVENT_FLAG(bool p0)l
extern _native64(0xD2D57F1D764117B1) any GET_RANDOM_EVENT_FLAG()l
extern _native64(0x24DA7D7667FD7B09) const char* _GET_GLOBAL_CHAR_BUFFER()l
extern _native64(0x4DCDF92BF64236CD) void UNK_0x4DCDF92BF64236CD(any p0, any p1)l
extern _native64(0x31125FD509D9043F) void UNK_0x31125FD509D9043F(any p0)l
extern _native64(0xEBD3205A207939ED) void UNK_0xEBD3205A207939ED(any p0)l
extern _native64(0x97E7E2C04245115B) void UNK_0x97E7E2C04245115B(any p0)l
extern _native64(0xEB078CA2B5E82ADD) void UNK_0xEB078CA2B5E82ADD(any p0, any p1)l
extern _native64(0x703CC7F60CBB2B57) void UNK_0x703CC7F60CBB2B57(any p0)l
extern _native64(0x8951EB9C6906D3C8) void UNK_0x8951EB9C6906D3C8()l
extern _native64(0xBA4B8D83BDC75551) void UNK_0xBA4B8D83BDC75551(any p0)l
extern _native64(0xE8B9C0EC9E183F35) any UNK_0xE8B9C0EC9E183F35()l
extern _native64(0x65D2EBB47E1CEC21) void UNK_0x65D2EBB47E1CEC21(bool p0)l
extern _native64(0x6F2135B6129620C1) void UNK_0x6F2135B6129620C1(bool p0)l
extern _native64(0x8D74E26F54B4E5C3) void UNK_0x8D74E26F54B4E5C3(const char* p0)l
extern _native64(0xB335F761606DB47C) bool UNK_0xB335F761606DB47C(any* p0, any* p1, any p2, bool p3)l
extern _native64(0x564B884A05EC45A3) Hash GET_PREV_WEATHER_TYPE_HASH_NAME()l
extern _native64(0x711327CD09C8F162) Hash GET_NEXT_WEATHER_TYPE_HASH_NAME()l
extern _native64(0x44F28F86433B10A9) bool IS_PREV_WEATHER_TYPE(const char* weatherType)l
extern _native64(0x2FAA3A30BEC0F25D) bool IS_NEXT_WEATHER_TYPE(const char* weatherType)l
extern _native64(0x704983DF373B198F) void SET_WEATHER_TYPE_PERSIST(const char* weatherType)l
extern _native64(0xED712CA327900C8A) void SET_WEATHER_TYPE_NOW_PERSIST(const char* weatherType)l
extern _native64(0x29B487C359E19889) void SET_WEATHER_TYPE_NOW(const char* weatherType)l
extern _native64(0xFB5045B7C42B75BF) void _SET_WEATHER_TYPE_OVER_TIME(const char* weatherType, float time)l
extern _native64(0x8B05F884CF7E8020) void SET_RANDOM_WEATHER_TYPE()l
extern _native64(0xCCC39339BEF76CF5) void CLEAR_WEATHER_TYPE_PERSIST()l
extern _native64(0xF3BBE884A14BB413) void _GET_WEATHER_TYPE_TRANSITION(any* p0, any* p1, float* progress_or_time)l
extern _native64(0x578C752848ECFA0C) void _SET_WEATHER_TYPE_TRANSITION(Hash weatherType1, Hash weatherType2, float percentWeather2)l
extern _native64(0xA43D5C6FE51ADBEF) void SET_OVERRIDE_WEATHER(const char* weatherType)l
extern _native64(0x338D2E3477711050) void CLEAR_OVERRIDE_WEATHER()l
extern _native64(0xB8F87EAD7533B176) void UNK_0xB8F87EAD7533B176(float p0)l
extern _native64(0xC3EAD29AB273ECE8) void UNK_0xC3EAD29AB273ECE8(float p0)l
extern _native64(0xA7A1127490312C36) void UNK_0xA7A1127490312C36(float p0)l
extern _native64(0x31727907B2C43C55) void UNK_0x31727907B2C43C55(float p0)l
extern _native64(0x405591EC8FD9096D) void UNK_0x405591EC8FD9096D(float p0)l
extern _native64(0xF751B16FB32ABC1D) void UNK_0xF751B16FB32ABC1D(float p0)l
extern _native64(0xB3E6360DDE733E82) void UNK_0xB3E6360DDE733E82(float p0)l
extern _native64(0x7C9C0B1EEB1F9072) void UNK_0x7C9C0B1EEB1F9072(float p0)l
extern _native64(0x6216B116083A7CB4) void UNK_0x6216B116083A7CB4(float p0)l
extern _native64(0x9F5E6BB6B34540DA) void UNK_0x9F5E6BB6B34540DA(float p0)l
extern _native64(0xB9854DFDE0D833D6) void UNK_0xB9854DFDE0D833D6(float p0)l
extern _native64(0xC54A08C85AE4D410) void UNK_0xC54A08C85AE4D410(float p0)l
extern _native64(0xA8434F1DFF41D6E7) void UNK_0xA8434F1DFF41D6E7(float p0)l
extern _native64(0xC3C221ADDDE31A11) void UNK_0xC3C221ADDDE31A11(float p0)l
extern _native64(0xAC3A74E8384A9919) void SET_WIND(float speed)l
extern _native64(0xEE09ECEDBABE47FC) void SET_WIND_SPEED(float speed)l
extern _native64(0xA8CF1CC0AFCD3F12) float GET_WIND_SPEED()l
extern _native64(0xEB0F4468467B4528) void SET_WIND_DIRECTION(float direction)l
extern _native64(0x1F400FEF721170DA) vector3 GET_WIND_DIRECTION()l
extern _native64(0x643E26EA6E024D92) void _SET_RAIN_FX_INTENSITY(float intensity)l
extern _native64(0x96695E368AD855F3) any GET_RAIN_LEVEL()l
extern _native64(0xC5868A966E5BE3AE) any GET_SNOW_LEVEL()l
extern _native64(0xF6062E089251C898) void _CREATE_LIGHTNING_THUNDER()l
extern _native64(0x02DEAAC8F8EA7FE7) void UNK_0x02DEAAC8F8EA7FE7(const char* p0)l
extern _native64(0x11B56FBBF7224868) void UNK_0x11B56FBBF7224868(const char* p0)l
extern _native64(0xFC4842A34657BFCB) void _SET_CLOUD_HAT_TRANSITION(const char* type, float transitionTime)l
extern _native64(0xA74802FB8D0B7814) void UNK_0xA74802FB8D0B7814(const char* p0, float p1)l
extern _native64(0x957E790EA1727B64) void _CLEAR_CLOUD_HAT()l
extern _native64(0xF36199225D6D8C86) void _SET_CLOUD_HAT_OPACITY(float opacity)l
extern _native64(0x20AC25E781AE4A84) float _GET_CLOUD_HAT_OPACITY()l
extern _native64(0x9CD27B0045628463) int GET_GAME_TIMER()l
extern _native64(0x15C40837039FFAF7) float GET_FRAME_TIME()l
extern _native64(0xE599A503B3837E1B) float UNK_0xE599A503B3837E1B()l
extern _native64(0xFC8202EFC642E6F2) int GET_FRAME_COUNT()l
extern _native64(0x313CE5879CEB6FCD) float GET_RANDOM_FLOAT_IN_RANGE(float startRange, float endRange)l
extern _native64(0xD53343AA4FB7DD28) int GET_RANDOM_INT_IN_RANGE(int startRange, int endRange)l
extern _native64(0xC906A7DAB05C8D2B) bool GET_GROUND_Z_FOR_3D_COORD(vector3 vec, float* groundZ, bool unk)l
extern _native64(0x8BDC7BFC57A81E76) bool UNK_0x8BDC7BFC57A81E76(vector3 vec, float* p3, vector3* p4)l
extern _native64(0xC843060B5765DCE7) float ASIN(float p0)l
extern _native64(0x1D08B970013C34B6) float ACOS(float p0)l
extern _native64(0x632106CC96E82E91) float TAN(float p0)l
extern _native64(0xA9D1795CD5043663) float ATAN(float p0)l
extern _native64(0x8927CBF9D22261A4) float ATAN2(float p0, float p1)l
extern _native64(0xF1B760881820C952) float GET_DISTANCE_BETWEEN_COORDS(vector3 vec_1, vector3 vec_2, bool useZ)l
extern _native64(0x186FC4BE848E1C92) float GET_ANGLE_BETWEEN_2D_VECTORS(vector2 vector_1, vector2 vector_2)l
extern _native64(0x2FFB6B224F4B2926) float GET_HEADING_FROM_VECTOR_2D(vector2 d)l
extern _native64(0x7F8F6405F4777AF6) float UNK_0x7F8F6405F4777AF6(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)l
extern _native64(0x21C235BC64831E5A) vector3 UNK_0x21C235BC64831E5A(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)l
extern _native64(0xF56DFB7B61BE7276) bool UNK_0xF56DFB7B61BE7276(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, any* p12)l
extern _native64(0x933D6A9EEC1BACD0) void SET_BIT(int* address, int offset)l
extern _native64(0xE80492A9AC099A93) void CLEAR_BIT(int* address, int offset)l
extern _native64(0xD24D37CC275948CC) Hash GET_HASH_KEY(const char* value)l
extern _native64(0xF2F6A2FA49278625) void UNK_0xF2F6A2FA49278625(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, any* p9, any* p10, any* p11, any* p12)l
extern _native64(0xA61B4DF533DCB56E) bool IS_AREA_OCCUPIED(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9, bool p10, any p11, bool p12)l
extern _native64(0xADCDE75E1C60F32D) bool IS_POSITION_OCCUPIED(vector3 vec, float range, bool p4, bool p5, bool p6, bool p7, bool p8, any p9, bool p10)l
extern _native64(0xE54E209C35FFA18D) bool IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native64(0xA56F01F3765B93A0) void CLEAR_AREA(vector3 vec, float radius, bool p4, bool ignoreCopCars, bool ignoreObjects, bool p7)l
extern _native64(0x957838AAF91BD12D) void _CLEAR_AREA_OF_EVERYTHING(vector3 vec, float radius, bool p4, bool p5, bool p6, bool p7)l
extern _native64(0x01C7B9B38428AEB6) void CLEAR_AREA_OF_VEHICLES(vector3 vec, float radius, bool p4, bool p5, bool p6, bool p7, bool p8)l
extern _native64(0x11DB3500F042A8AA) void CLEAR_ANGLED_AREA_OF_VEHICLES(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, bool p8, bool p9, bool p10, bool p11)l
extern _native64(0xDD9B9B385AAC7F5B) void CLEAR_AREA_OF_OBJECTS(vector3 vec, float radius, int flags)l
extern _native64(0xBE31FD6CE464AC59) void CLEAR_AREA_OF_PEDS(vector3 vec, float radius, int flags)l
extern _native64(0x04F8FC8FCF58F88D) void CLEAR_AREA_OF_COPS(vector3 vec, float radius, int flags)l
extern _native64(0x0A1CB9094635D1A6) void CLEAR_AREA_OF_PROJECTILES(vector3 vec, float radius, int flags)l
extern _native64(0x7EC6F9A478A6A512) void UNK_0x7EC6F9A478A6A512()l
extern _native64(0xC9BF75D28165FF77) void SET_SAVE_MENU_ACTIVE(bool unk)l
extern _native64(0x397BAA01068BAA96) int UNK_0x397BAA01068BAA96()l
extern _native64(0xB938B7E6D3C0620C) void SET_CREDITS_ACTIVE(bool toggle)l
extern _native64(0xB51B9AB9EF81868C) void UNK_0xB51B9AB9EF81868C(bool toggle)l
extern _native64(0x075F1D57402C93BA) any UNK_0x075F1D57402C93BA()l
extern _native64(0x9DC711BC69C548DF) void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(const char* scriptName)l
extern _native64(0x9243BAC96D64C050) void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME()l
extern _native64(0x1F464EF988465A81) int ADD_HOSPITAL_RESTART(vector3 vec, float p3, any p4)l
extern _native64(0xC8535819C450EBA8) void DISABLE_HOSPITAL_RESTART(int hospitalIndex, bool toggle)l
extern _native64(0x452736765B31FC4B) any ADD_POLICE_RESTART(float p0, float p1, float p2, float p3, any p4)l
extern _native64(0x23285DED6EBD7EA3) void DISABLE_POLICE_RESTART(int policeIndex, bool toggle)l
extern _native64(0x706B5EDCAA7FA663) void _SET_CUSTOM_RESPAWN_POSITION(vector3 vec, float heading)l
extern _native64(0xA2716D40842EAF79) void _SET_NEXT_RESPAWN_TO_CUSTOM()l
extern _native64(0x2C2B3493FBF51C71) void _DISABLE_AUTOMATIC_RESPAWN(bool disableRespawn)l
extern _native64(0x21FFB63D8C615361) void IGNORE_NEXT_RESTART(bool toggle)l
extern _native64(0x4A18E01DF2C87B86) void SET_FADE_OUT_AFTER_DEATH(bool toggle)l
extern _native64(0x1E0B4DC0D990A4E7) void SET_FADE_OUT_AFTER_ARREST(bool toggle)l
extern _native64(0xDA66D2796BA33F12) void SET_FADE_IN_AFTER_DEATH_ARREST(bool toggle)l
extern _native64(0xF3D78F59DFE18D79) void SET_FADE_IN_AFTER_LOAD(bool toggle)l
extern _native64(0xC0714D0A7EEECA54) any REGISTER_SAVE_HOUSE(float p0, float p1, float p2, float p3, any* p4, any p5, any p6)l
extern _native64(0x4F548CABEAE553BC) void SET_SAVE_HOUSE(any p0, bool p1, bool p2)l
extern _native64(0x1162EA8AE9D24EEA) bool OVERRIDE_SAVE_HOUSE(bool p0, float p1, float p2, float p3, float p4, bool p5, float p6, float p7)l
extern _native64(0xA4A0065E39C9F25C) any UNK_0xA4A0065E39C9F25C(any p0, any p1, any p2, any p3)l
extern _native64(0x50EEAAD86232EE55) void DO_AUTO_SAVE()l
extern _native64(0x6E04F06094C87047) any UNK_0x6E04F06094C87047()l
extern _native64(0x69240733738C19A0) bool IS_AUTO_SAVE_IN_PROGRESS()l
extern _native64(0x2107A3773771186D) any UNK_0x2107A3773771186D()l
extern _native64(0x06462A961E94B67C) void UNK_0x06462A961E94B67C()l
extern _native64(0xE0E500246FF73D66) void BEGIN_REPLAY_STATS(any p0, any p1)l
extern _native64(0x69FE6DC87BD2A5E9) void UNK_0x69FE6DC87BD2A5E9(any p0)l
extern _native64(0xA23E821FBDF8A5F2) void END_REPLAY_STATS()l
extern _native64(0xD642319C54AADEB6) any UNK_0xD642319C54AADEB6()l
extern _native64(0x5B1F2E327B6B6FE1) any UNK_0x5B1F2E327B6B6FE1()l
extern _native64(0x2B626A0150E4D449) any UNK_0x2B626A0150E4D449()l
extern _native64(0xDC9274A7EF6B2867) any UNK_0xDC9274A7EF6B2867()l
extern _native64(0x8098C8D6597AAE18) any UNK_0x8098C8D6597AAE18(any p0)l
extern _native64(0x1B1AB132A16FDA55) void CLEAR_REPLAY_STATS()l
extern _native64(0x72DE52178C291CB5) any UNK_0x72DE52178C291CB5()l
extern _native64(0x44A0BDC559B35F6E) any UNK_0x44A0BDC559B35F6E()l
extern _native64(0xEB2104E905C6F2E9) any UNK_0xEB2104E905C6F2E9()l
extern _native64(0x2B5E102E4A42F2BF) any UNK_0x2B5E102E4A42F2BF()l
extern _native64(0x8A75CE2956274ADD) bool IS_MEMORY_CARD_IN_USE()l
extern _native64(0x867654CBC7606F2C) void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(vector3 vec_1, vector3 vec_2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed)l
extern _native64(0xE3A7742E0B7A2F8B) void UNK_0xE3A7742E0B7A2F8B(vector3 vec_1, vector3 vec_2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity)l
extern _native64(0xBFE5756E7407064A) void UNK_0xBFE5756E7407064A(vector3 vec_1, vector3 vec_2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, bool p14, bool p15, bool p16, bool p17)l
extern _native64(0x03E8D3D5F549087A) void GET_MODEL_DIMENSIONS(Hash modelHash, vector3* minimum, vector3* maximum)l
extern _native64(0x1454F2448DE30163) void SET_FAKE_WANTED_LEVEL(int fakeWantedLevel)l
extern _native64(0x4C9296CBCD1B971E) int GET_FAKE_WANTED_LEVEL()l
extern _native64(0xA921AA820C25702F) bool IS_BIT_SET(int address, int offset)l
extern _native64(0xF14878FC50BEC6EE) void USING_MISSION_CREATOR(bool toggle)l
extern _native64(0xDEA36202FC3382DF) void UNK_0xDEA36202FC3382DF(bool p0)l
extern _native64(0x19E00D7322C6F85B) void SET_MINIGAME_IN_PROGRESS(bool toggle)l
extern _native64(0x2B4A15E44DE0F478) bool IS_MINIGAME_IN_PROGRESS()l
extern _native64(0x7B30F65D7B710098) bool IS_THIS_A_MINIGAME_SCRIPT()l
extern _native64(0x61A23B7EDA9BDA24) bool IS_SNIPER_INVERTED()l
extern _native64(0xD3D15555431AB793) any UNK_0xD3D15555431AB793()l
extern _native64(0xC488FF2356EA7791) int GET_PROFILE_SETTING(int profileSetting)l
extern _native64(0x0C515FAB3FF9EA92) bool ARE_STRINGS_EQUAL(const char* string1, const char* string2)l
extern _native64(0x1E34710ECD4AB0EB) int COMPARE_STRINGS(const char* str1, const char* str2, bool matchCase, int maxLength)l
extern _native64(0xF0D31AD191A74F87) int ABSI(int value)l
extern _native64(0x73D57CFFDD12C355) float ABSF(float value)l
extern _native64(0xFEFCF11B01287125) bool IS_SNIPER_BULLET_IN_AREA(vector3 vec_1, vector3 vec_2)l
extern _native64(0x5270A8FBC098C3F8) bool IS_PROJECTILE_IN_AREA(vector3 vec_1, vector3 vec_2, bool ownedByPlayer)l
extern _native64(0x2E0DC353342C4A6D) bool IS_PROJECTILE_TYPE_IN_AREA(vector3 vec_1, vector3 vec_2, int type, bool p7)l
extern _native64(0xF0BC12401061DEA0) bool IS_PROJECTILE_TYPE_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7, bool p8)l
extern _native64(0x34318593248C8FB2) bool UNK_0x34318593248C8FB2(float p0, float p1, float p2, any p3, float p4, bool p5)l
extern _native64(0x8D7A43EC6A5FEA45) any UNK_0x8D7A43EC6A5FEA45(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native64(0xDFB4138EEFED7B81) bool UNK_0xDFB4138EEFED7B81(Ped ped, Hash weaponHash, float radius, Entity* entity, bool p4)l
extern _native64(0x82FDE6A57EE4EE44) any UNK_0x82FDE6A57EE4EE44(Ped ped, Hash weaponhash, float p2, float p3, float p4, bool p5)l
extern _native64(0x1A8B5F3C01E2B477) bool IS_BULLET_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7)l
extern _native64(0x3F2023999AD51C1F) bool IS_BULLET_IN_AREA(float p0, float p1, float p2, float p3, bool p4)l
extern _native64(0xDE0F6D7450D37351) bool IS_BULLET_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, bool p6)l
extern _native64(0x9870ACFB89A90995) bool HAS_BULLET_IMPACTED_IN_AREA(vector3 vec, float p3, bool p4, bool p5)l
extern _native64(0xDC8C5D7CFEAB8394) bool HAS_BULLET_IMPACTED_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7)l
extern _native64(0xA72BC0B675B1519E) bool IS_ORBIS_VERSION()l
extern _native64(0x4D982ADB1978442D) bool IS_DURANGO_VERSION()l
extern _native64(0xF6201B4DAF662A9D) bool IS_XBOX360_VERSION()l
extern _native64(0xCCA1072C29D096C2) bool IS_PS3_VERSION()l
extern _native64(0x48AF36444B965238) bool IS_PC_VERSION()l
extern _native64(0x9F1935CA1F724008) bool IS_AUSSIE_VERSION()l
extern _native64(0xF22B6C47C6EAB066) bool IS_STRING_NULL(const char* string)l
extern _native64(0xCA042B6957743895) bool IS_STRING_NULL_OR_EMPTY(const char* string)l
extern _native64(0x5A5F40FE637EB584) bool STRING_TO_INT(const char* string, int* outInteger)l
extern _native64(0x8EF07E15701D61ED) void SET_BITS_IN_RANGE(int* var, int rangeStart, int rangeEnd, int p3)l
extern _native64(0x53158863FCC0893A) int GET_BITS_IN_RANGE(int var, int rangeStart, int rangeEnd)l
extern _native64(0x1A992DA297A4630C) int ADD_STUNT_JUMP(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, any p15, any p16)l
extern _native64(0xBBE5D803A5360CBF) int ADD_STUNT_JUMP_ANGLED(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, float p15, float p16, any p17, any p18)l
extern _native64(0xDC518000E39DAE1F) void DELETE_STUNT_JUMP(int p0)l
extern _native64(0xE369A5783B866016) void ENABLE_STUNT_JUMP_SET(int p0)l
extern _native64(0xA5272EBEDD4747F6) void DISABLE_STUNT_JUMP_SET(int p0)l
extern _native64(0xD79185689F8FD5DF) void UNK_0xD79185689F8FD5DF(bool p0)l
extern _native64(0x7A3F19700A4D0525) bool IS_STUNT_JUMP_IN_PROGRESS()l
extern _native64(0x2272B0A1343129F4) bool IS_STUNT_JUMP_MESSAGE_SHOWING()l
extern _native64(0x996DD1E1E02F1008) any UNK_0x996DD1E1E02F1008()l
extern _native64(0x6856EC3D35C81EA4) any UNK_0x6856EC3D35C81EA4()l
extern _native64(0xE6B7B0ACD4E4B75E) void CANCEL_STUNT_JUMP()l
extern _native64(0x577D1284D6873711) void SET_GAME_PAUSED(bool toggle)l
extern _native64(0xAA391C728106F7AF) void SET_THIS_SCRIPT_CAN_BE_PAUSED(bool toggle)l
extern _native64(0xB98236CAAECEF897) void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(bool toggle)l
extern _native64(0x071E2A839DE82D90) bool _HAS_BUTTON_COMBINATION_JUST_BEEN_ENTERED(Hash hash, int amount)l
extern _native64(0x557E43C447E700A8) bool _HAS_CHEAT_STRING_JUST_BEEN_ENTERED(Hash hash)l
extern _native64(0x9BAE5AD2508DF078) void _USE_FREEMODE_MAP_BEHAVIOR(bool toggle)l
extern _native64(0xC5F0A8EBD3F361CE) void _SET_UNK_MAP_FLAG(int flag)l
extern _native64(0x7EA2B6AF97ECA6ED) bool IS_FRONTEND_FADING()l
extern _native64(0x7472BB270D7B4F3E) void POPULATE_NOW()l
extern _native64(0xCBAD6729F7B1F4FC) int GET_INDEX_OF_CURRENT_LEVEL()l
extern _native64(0x740E14FAD5842351) void SET_GRAVITY_LEVEL(int level)l
extern _native64(0xA9575F812C6A7997) void START_SAVE_DATA(any* p0, any p1, bool p2)l
extern _native64(0x74E20C9145FB66FD) void STOP_SAVE_DATA()l
extern _native64(0xA09F896CE912481F) any UNK_0xA09F896CE912481F(bool p0)l
extern _native64(0x34C9EE5986258415) void REGISTER_INT_TO_SAVE(any* p0, const char* name)l
extern _native64(0xA735353C77334EA0) void UNK_0xA735353C77334EA0(any* p0, any* p1)l
extern _native64(0x10C2FA78D0E128A1) void REGISTER_ENUM_TO_SAVE(any* p0, const char* name)l
extern _native64(0x7CAEC29ECB5DFEBB) void REGISTER_FLOAT_TO_SAVE(any* p0, const char* name)l
extern _native64(0xC8F4131414C835A1) void REGISTER_BOOL_TO_SAVE(any* p0, const char* name)l
extern _native64(0xEDB1232C5BEAE62F) void REGISTER_TEXT_LABEL_TO_SAVE(any* p0, const char* name)l
extern _native64(0x6F7794F28C6B2535) void UNK_0x6F7794F28C6B2535(any* p0, const char* name)l
extern _native64(0x48F069265A0E4BEC) void UNK_0x48F069265A0E4BEC(any* p0, const char* name)l
extern _native64(0x8269816F6CFD40F8) void UNK_0x8269816F6CFD40F8(any* p0, const char* name)l
extern _native64(0xFAA457EF263E8763) void UNK_0xFAA457EF263E8763(any* p0, const char* name)l
extern _native64(0xBF737600CDDBEADD) void _START_SAVE_STRUCT(any* p0, int p1, const char* structName)l
extern _native64(0xEB1774DF12BB9F12) void STOP_SAVE_STRUCT()l
extern _native64(0x60FE567DF1B1AF9D) void _START_SAVE_ARRAY(any* p0, int p1, const char* arrayName)l
extern _native64(0x04456F95153C6BE4) void STOP_SAVE_ARRAY()l
extern _native64(0xDC0F817884CDD856) void ENABLE_DISPATCH_SERVICE(int dispatchType, bool toggle)l
extern _native64(0x9B2BD3773123EA2F) void UNK_0x9B2BD3773123EA2F(int type, bool toggle)l
extern _native64(0xEB4A0C2D56441717) int UNK_0xEB4A0C2D56441717(int p0)l
extern _native64(0x3F892CAF67444AE7) bool CREATE_INCIDENT(int incidentType, vector3 vec, int p5, float radius, int* outIncidentID)l
extern _native64(0x05983472F0494E60) bool CREATE_INCIDENT_WITH_ENTITY(int incidentType, Ped ped, int amountOfPeople, float radius, int* outIncidentID)l
extern _native64(0x556C1AA270D5A207) void DELETE_INCIDENT(int incidentId)l
extern _native64(0xC8BC6461E629BEAA) bool IS_INCIDENT_VALID(int incidentId)l
extern _native64(0xB08B85D860E7BA3C) void UNK_0xB08B85D860E7BA3C(any p0, any p1, any p2)l
extern _native64(0xD261BA3E7E998072) void UNK_0xD261BA3E7E998072(any p0, float p1)l
extern _native64(0x6874E2190B0C1972) bool FIND_SPAWN_POINT_IN_DIRECTION(vector3 vec_1, vector3 vec_2, float distance, vector3* spawnPoint)l
extern _native64(0x67F6413D3220E18D) any UNK_0x67F6413D3220E18D(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native64(0x1327E2FE9746BAEE) bool UNK_0x1327E2FE9746BAEE(any p0)l
extern _native64(0xB129E447A2EDA4BF) void UNK_0xB129E447A2EDA4BF(any p0, bool p1)l
extern _native64(0x32C7A7E8C43A1F80) any UNK_0x32C7A7E8C43A1F80(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7)l
extern _native64(0xE6869BECDD8F2403) void UNK_0xE6869BECDD8F2403(any p0, bool p1)l
extern _native64(0x28A04B411933F8A6) void ENABLE_TENNIS_MODE(Ped ped, bool toggle, bool p2)l
extern _native64(0x5D5479D115290C3F) bool IS_TENNIS_MODE(Ped ped)l
extern _native64(0xE266ED23311F24D4) void UNK_0xE266ED23311F24D4(any p0, any* p1, any* p2, float p3, float p4, bool p5)l
extern _native64(0x17DF68D720AA77F8) bool UNK_0x17DF68D720AA77F8(any p0)l
extern _native64(0x19BFED045C647C49) bool UNK_0x19BFED045C647C49(any p0)l
extern _native64(0xE95B0C7D5BA3B96B) bool UNK_0xE95B0C7D5BA3B96B(any p0)l
extern _native64(0x8FA9C42FC5D7C64B) void UNK_0x8FA9C42FC5D7C64B(any p0, any p1, float p2, float p3, float p4, bool p5)l
extern _native64(0x54F157E0336A3822) void UNK_0x54F157E0336A3822(any p0, const char* p1, float p2)l
extern _native64(0xD10F442036302D50) void UNK_0xD10F442036302D50(any p0, any p1, any p2)l
extern _native64(0x77A84429DD9F0A15) void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE()l
extern _native64(0x6FE601A64180D423) void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(float p0)l
extern _native64(0x44F7CBC1BEB3327D) void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(any p0, float p1)l
extern _native64(0x48838ED9937A15D1) void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(any p0, float p1)l
extern _native64(0x918C7B2D2FF3928B) any UNK_0x918C7B2D2FF3928B(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native64(0x2D4259F1FEB81DA9) any UNK_0x2D4259F1FEB81DA9(float p0, float p1, float p2, float p3)l
extern _native64(0x264AC28B01B353A5) void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(any p0)l
extern _native64(0xAC7BFD5C1D83EA75) void RESET_DISPATCH_SPAWN_BLOCKING_AREAS()l
extern _native64(0xD9F692D349249528) void UNK_0xD9F692D349249528()l
extern _native64(0xE532EC1A63231B4F) void UNK_0xE532EC1A63231B4F(any p0, any p1)l
extern _native64(0xB8721407EE9C3FF6) void UNK_0xB8721407EE9C3FF6(any p0, any p1, any p2)l
extern _native64(0xB3CD58CCA6CDA852) void UNK_0xB3CD58CCA6CDA852()l
extern _native64(0x2587A48BC88DFADF) void UNK_0x2587A48BC88DFADF(bool p0)l
extern _native64(0xCA78CFA0366592FE) void _DISPLAY_ONSCREEN_KEYBOARD_2(int p0, const char* windowTitle, any* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, const char* defaultConcat4, const char* defaultConcat5, const char* defaultConcat6, const char* defaultConcat7, int maxInputLength)l
extern _native64(0x00DC833F2568DBF6) void DISPLAY_ONSCREEN_KEYBOARD(int p0, const char* windowTitle, const char* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, int maxInputLength)l
extern _native64(0x0CF2B696BBF945AE) int UPDATE_ONSCREEN_KEYBOARD()l
extern _native64(0x8362B09B91893647) const char* GET_ONSCREEN_KEYBOARD_RESULT()l
extern _native64(0x3ED1438C1F5C6612) void UNK_0x3ED1438C1F5C6612(int p0)l
extern _native64(0xA6A12939F16D85BE) void UNK_0xA6A12939F16D85BE(Hash hash, bool p1)l
extern _native64(0x1EAE0A6E978894A2) void UNK_0x1EAE0A6E978894A2(int p0, bool p1)l
extern _native64(0xA66C71C98D5F2CFB) any SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player)l
extern _native64(0x11879CDD803D30F4) any SET_FIRE_AMMO_THIS_FRAME(Player player)l
extern _native64(0xFF1BED81BFDC0FE0) any SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player)l
extern _native64(0x57FFF03E423A4C0B) any SET_SUPER_JUMP_THIS_FRAME(Player player)l
extern _native64(0x6FDDF453C0C756EC) bool UNK_0x6FDDF453C0C756EC()l
extern _native64(0xFB00CA71DA386228) void UNK_0xFB00CA71DA386228()l
extern _native64(0x5AA3BEFA29F03AD4) any UNK_0x5AA3BEFA29F03AD4()l
extern _native64(0xE3D969D2785FFB5E) void UNK_0xE3D969D2785FFB5E()l
extern _native64(0xC0AA53F866B3134D) void _RESET_LOCALPLAYER_STATE()l
extern _native64(0x0A60017F841A54F2) void UNK_0x0A60017F841A54F2(any p0, any p1, any p2, any p3)l
extern _native64(0x1FF6BF9A63E5757F) void UNK_0x1FF6BF9A63E5757F()l
extern _native64(0x1BB299305C3E8C13) void UNK_0x1BB299305C3E8C13(any p0, any p1, any p2, any p3)l
extern _native64(0x8EF5573A1F801A5C) bool UNK_0x8EF5573A1F801A5C(any p0, any* p1, any* p2)l
extern _native64(0x92790862E36C2ADA) void UNK_0x92790862E36C2ADA()l
extern _native64(0xC7DB36C24634F52B) void UNK_0xC7DB36C24634F52B()l
extern _native64(0x437138B6A830166A) void UNK_0x437138B6A830166A()l
extern _native64(0x37DEB0AA183FB6D8) void UNK_0x37DEB0AA183FB6D8()l
extern _native64(0xEA2F2061875EED90) any UNK_0xEA2F2061875EED90()l
extern _native64(0x3BBBD13E5041A79E) any UNK_0x3BBBD13E5041A79E()l
extern _native64(0xA049A5BE0F04F2F8) any UNK_0xA049A5BE0F04F2F8()l
extern _native64(0x4750FC27570311EC) any UNK_0x4750FC27570311EC()l
extern _native64(0x1B2366C3F2A5C8DF) any UNK_0x1B2366C3F2A5C8DF()l
extern _native64(0xEB6891F03362FB12) void _FORCE_SOCIAL_CLUB_UPDATE()l
extern _native64(0x14832BF2ABA53FC5) any UNK_0x14832BF2ABA53FC5()l
extern _native64(0xC79AE21974B01FB2) void UNK_0xC79AE21974B01FB2()l
extern _native64(0x684A41975F077262) bool UNK_0x684A41975F077262()l
extern _native64(0xABB2FA71C83A1B72) any UNK_0xABB2FA71C83A1B72()l
extern _native64(0x4EBB7E87AA0DBED4) void _SHOW_PED_IN_PAUSE_MENU(bool toggle)l
extern _native64(0x9689123E3F213AA5) bool UNK_0x9689123E3F213AA5()l
extern _native64(0x9D8D44ADBBA61EF2) void UNK_0x9D8D44ADBBA61EF2(bool p0)l
extern _native64(0x23227DF0B2115469) void UNK_0x23227DF0B2115469()l
extern _native64(0xD10282B6E3751BA0) any UNK_0xD10282B6E3751BA0()l
extern _native64(0x213AEB2B90CBA7AC) void _MEMMOVE(void* ptr1, const void* ptr2, int bufferSize64)l
#pragma endregion //}
#pragma region AUDIO //{
extern _native64(0xF9E56683CA8E11A5) void PLAY_PED_RINGTONE(const char* ringtoneName, Ped ped, bool p2)l
extern _native64(0x1E8E5E20937E3137) bool IS_PED_RINGTONE_PLAYING(Ped ped)l
extern _native64(0x6C5AE23EFA885092) void STOP_PED_RINGTONE(Ped ped)l
extern _native64(0x7497D2CE2C30D24C) bool IS_MOBILE_PHONE_CALL_ONGOING()l
extern _native64(0xC8B1B2425604CDD0) any UNK_0xC8B1B2425604CDD0()l
extern _native64(0xD2C91A0B572AAE56) void CREATE_NEW_SCRIPTED_CONVERSATION()l
extern _native64(0xC5EF963405593646) void ADD_LINE_TO_CONVERSATION(int p0, const char* p1, const char* p2, int p3, int p4, bool p5, bool p6, bool p7, bool p8, int p9, bool p10, bool p11, bool p12)l
extern _native64(0x95D9F4BC443956E7) void ADD_PED_TO_CONVERSATION(any p0, any ped, const char* p2)l
extern _native64(0x33E3C6C6F2F0B506) void UNK_0x33E3C6C6F2F0B506(any p0, float p1, float p2, float p3)l
extern _native64(0x892B6AB8F33606F5) void UNK_0x892B6AB8F33606F5(any p0, any p1)l
extern _native64(0xB6AE90EDDE95C762) void SET_MICROPHONE_POSITION(bool p0, vector3 vec_1, vector3 vec_2, vector3 vec_3)l
extern _native64(0x0B568201DD99F0EB) void UNK_0x0B568201DD99F0EB(bool p0)l
extern _native64(0x61631F5DF50D1C34) void UNK_0x61631F5DF50D1C34(bool p0)l
extern _native64(0x252E5F915EABB675) void START_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)l
extern _native64(0x6004BCB0E226AAEA) void PRELOAD_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)l
extern _native64(0x6B17C62C9635D2DC) void START_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x3B3CAD6166916D87) void PRELOAD_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x23641AFE870AF385) void START_PRELOADED_CONVERSATION()l
extern _native64(0xE73364DB90778FFA) any UNK_0xE73364DB90778FFA()l
extern _native64(0x16754C556D2EDE3D) bool IS_SCRIPTED_CONVERSATION_ONGOING()l
extern _native64(0xDF0D54BE7A776737) bool IS_SCRIPTED_CONVERSATION_LOADED()l
extern _native64(0x480357EE890C295A) any GET_CURRENT_SCRIPTED_CONVERSATION_LINE()l
extern _native64(0x8530AD776CD72B12) void PAUSE_SCRIPTED_CONVERSATION(bool p0)l
extern _native64(0x9AEB285D1818C9AC) void RESTART_SCRIPTED_CONVERSATION()l
extern _native64(0xD79DEEFB53455EBA) any STOP_SCRIPTED_CONVERSATION(bool p0)l
extern _native64(0x9663FE6B7A61EB00) void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE()l
extern _native64(0xA018A12E5C5C2FA6) void INTERRUPT_CONVERSATION(any p0, any* p1, any* p2)l
extern _native64(0x8A694D7A68F8DC38) void UNK_0x8A694D7A68F8DC38(Ped p0, const char* p1, const char* p2)l
extern _native64(0xAA19F5572C38B564) any UNK_0xAA19F5572C38B564(any* p0)l
extern _native64(0xB542DE8C3D1CB210) void UNK_0xB542DE8C3D1CB210(bool p0)l
extern _native64(0xC6ED9D5092438D91) void REGISTER_SCRIPT_WITH_AUDIO(any p0)l
extern _native64(0xA8638BE228D4751A) void UNREGISTER_SCRIPT_WITH_AUDIO()l
extern _native64(0x7345BDD95E62E0F2) bool REQUEST_MISSION_AUDIO_BANK(const char* p0, bool p1)l
extern _native64(0xFE02FFBED8CA9D99) bool REQUEST_AMBIENT_AUDIO_BANK(const char* p0, bool p1)l
extern _native64(0x2F844A8B08D76685) bool REQUEST_SCRIPT_AUDIO_BANK(const char* p0, bool p1)l
extern _native64(0x8F8C0E370AE62F5C) any HINT_AMBIENT_AUDIO_BANK(any p0, any p1)l
extern _native64(0xFB380A29641EC31A) any HINT_SCRIPT_AUDIO_BANK(any p0, any p1)l
extern _native64(0x0EC92A1BF0857187) void RELEASE_MISSION_AUDIO_BANK()l
extern _native64(0x65475A218FFAA93D) void RELEASE_AMBIENT_AUDIO_BANK()l
extern _native64(0x77ED170667F50170) void RELEASE_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank)l
extern _native64(0x7A2D8AD0A9EB9C3F) void RELEASE_SCRIPT_AUDIO_BANK()l
extern _native64(0x19AF7ED9B9D23058) void UNK_0x19AF7ED9B9D23058()l
extern _native64(0x9AC92EED5E4793AB) void UNK_0x9AC92EED5E4793AB()l
extern _native64(0x430386FE9BF80B45) int GET_SOUND_ID()l
extern _native64(0x353FC880830B88FA) void RELEASE_SOUND_ID(int soundId)l
extern _native64(0x7FF4944CC209192D) void PLAY_SOUND(Player soundId, const char* audioName, const char* audioRef, bool p3, any p4, bool p5)l
extern _native64(0x67C540AA08E4A6F5) void PLAY_SOUND_FRONTEND(int soundId, const char* audioName, const char* audioRef, bool p3)l
extern _native64(0xCADA5A0D0702381E) void UNK_0xCADA5A0D0702381E(const char* p0, const char* soundset)l
extern _native64(0xE65F427EB70AB1ED) void PLAY_SOUND_FROM_ENTITY(int soundId, const char* audioName, Entity entity, const char* audioRef, bool p4, any p5)l
extern _native64(0x8D8686B622B88120) void PLAY_SOUND_FROM_COORD(int soundId, const char* audioName, vector3 vec, const char* audioRef, bool p6, int range, bool p8)l
extern _native64(0xA3B0C41BA5CC0BB5) void STOP_SOUND(int soundId)l
extern _native64(0x2DE3F0A134FFBC0D) int GET_NETWORK_ID_FROM_SOUND_ID(int soundId)l
extern _native64(0x75262FD12D0A1C84) int GET_SOUND_ID_FROM_NETWORK_ID(int netId)l
extern _native64(0xAD6B3148A78AE9B6) void SET_VARIABLE_ON_SOUND(int soundId, any* p1, float p2)l
extern _native64(0x2F9D3834AEB9EF79) void SET_VARIABLE_ON_STREAM(const char* p0, float p1)l
extern _native64(0xF2A9CDABCEA04BD6) void OVERRIDE_UNDERWATER_STREAM(any* p0, bool p1)l
extern _native64(0x733ADF241531E5C2) void UNK_0x733ADF241531E5C2(const char* name, float p1)l
extern _native64(0xFCBDCE714A7C88E5) bool HAS_SOUND_FINISHED(int soundId)l
extern _native64(0x8E04FEDD28D42462) void _PLAY_AMBIENT_SPEECH1(Ped ped, const char* speechName, const char* speechParam)l
extern _native64(0xC6941B4A3A8FBBB9) void _PLAY_AMBIENT_SPEECH2(Ped ped, const char* speechName, const char* speechParam)l
extern _native64(0x3523634255FC3318) void _PLAY_AMBIENT_SPEECH_WITH_VOICE(Ped p0, const char* speechName, const char* voiceName, const char* speechParam, bool p4)l
extern _native64(0xED640017ED337E45) void _PLAY_AMBIENT_SPEECH_AT_COORDS(const char* p0, const char* p1, float p2, float p3, float p4, const char* p5)l
extern _native64(0x13AD665062541A7E) void OVERRIDE_TREVOR_RAGE(any* p0)l
extern _native64(0xE78503B10C4314E0) void RESET_TREVOR_RAGE()l
extern _native64(0xEA241BB04110F091) void SET_PLAYER_ANGRY(Ped playerPed, bool disabled)l
extern _native64(0xBC9AE166038A5CEC) void PLAY_PAIN(Ped ped, int painID, int p1)l
extern _native64(0xD01005D2BA2EB778) void UNK_0xD01005D2BA2EB778(any* p0)l
extern _native64(0xDDC635D5B3262C56) void UNK_0xDDC635D5B3262C56(any* p0)l
extern _native64(0x6C8065A3B780185B) void SET_AMBIENT_VOICE_NAME(Ped ped, const char* name)l
extern _native64(0x40CF0D12D142A9E8) void UNK_0x40CF0D12D142A9E8(Ped ped)l
extern _native64(0x7CDC8C3B89F661B3) void UNK_0x7CDC8C3B89F661B3(Ped playerPed, Hash p1)l
extern _native64(0xA5342D390CDA41D6) void UNK_0xA5342D390CDA41D6(any p0, bool p1)l
extern _native64(0x7A73D05A607734C7) void UNK_0x7A73D05A607734C7(Ped ped)l
extern _native64(0xB8BEC0CA6F0EDB0F) void STOP_CURRENT_PLAYING_AMBIENT_SPEECH(Ped ped)l
extern _native64(0x9072C8B49907BFAD) bool IS_AMBIENT_SPEECH_PLAYING(Ped p0)l
extern _native64(0xCC9AA18DCC7084F4) bool IS_SCRIPTED_SPEECH_PLAYING(any p0)l
extern _native64(0x729072355FA39EC9) bool IS_ANY_SPEECH_PLAYING(Ped ped)l
extern _native64(0x49B99BF3FDA89A7A) bool UNK_0x49B99BF3FDA89A7A(Ped ped, const char* speechName, bool unk)l
extern _native64(0x049E937F18F4020C) bool IS_PED_IN_CURRENT_CONVERSATION(Ped ped)l
extern _native64(0x95D2D383D5396B8A) void SET_PED_IS_DRUNK(Ped ped, bool toggle)l
extern _native64(0xEE066C7006C49C0A) void UNK_0xEE066C7006C49C0A(any p0, any p1, any* p2)l
extern _native64(0xC265DF9FB44A9FBD) bool UNK_0xC265DF9FB44A9FBD(any p0)l
extern _native64(0xCC97B29285B1DC3B) void SET_ANIMAL_MOOD(Ped animal, int mood)l
extern _native64(0xB35CE999E8EF317E) bool IS_MOBILE_PHONE_RADIO_ACTIVE()l
extern _native64(0xBF286C554784F3DF) void SET_MOBILE_PHONE_RADIO_STATE(bool state)l
extern _native64(0xE8AF77C4C06ADC93) int GET_PLAYER_RADIO_STATION_INDEX()l
extern _native64(0xF6D733C32076AD03) const char* GET_PLAYER_RADIO_STATION_NAME()l
extern _native64(0xB28ECA15046CA8B9) const char* GET_RADIO_STATION_NAME(int radioStation)l
extern _native64(0xA571991A7FE6CCEB) any GET_PLAYER_RADIO_STATION_GENRE()l
extern _native64(0xA151A7394A214E65) bool IS_RADIO_RETUNING()l
extern _native64(0x0626A247D2405330) any UNK_0x0626A247D2405330()l
extern _native64(0xFF266D1D0EB1195D) void UNK_0xFF266D1D0EB1195D()l
extern _native64(0xDD6BCF9E94425DF9) void UNK_0xDD6BCF9E94425DF9()l
extern _native64(0xC69EDA28699D5107) void SET_RADIO_TO_STATION_NAME(const char* stationName)l
extern _native64(0x1B9C0099CB942AC6) void SET_VEH_RADIO_STATION(Vehicle vehicle, const char* radioStation)l
extern _native64(0xC1805D05E6D4FE10) void UNK_0xC1805D05E6D4FE10(Vehicle vehicle)l
extern _native64(0xACF57305B12AF907) void SET_EMITTER_RADIO_STATION(const char* emitterName, const char* radioStation)l
extern _native64(0x399D2D3B33F1B8EB) void SET_STATIC_EMITTER_ENABLED(const char* emitterName, bool toggle)l
extern _native64(0xA619B168B8A8570F) void SET_RADIO_TO_STATION_INDEX(int radioStation)l
extern _native64(0xF7F26C6E9CC9EBB8) void SET_FRONTEND_RADIO_ACTIVE(bool active)l
extern _native64(0xB165AB7C248B2DC1) void UNLOCK_MISSION_NEWS_STORY(int newsStory)l
extern _native64(0x66E49BF55B4B1874) int GET_NUMBER_OF_PASSENGER_VOICE_VARIATIONS(any p0)l
extern _native64(0x50B196FC9ED6545B) int GET_AUDIBLE_MUSIC_TRACK_TEXT_ID()l
extern _native64(0xCD536C4D33DCC900) void PLAY_END_CREDITS_MUSIC(bool play)l
extern _native64(0x6DDBBDD98E2E9C25) void SKIP_RADIO_FORWARD()l
extern _native64(0x344F393B027E38C3) void FREEZE_RADIO_STATION(const char* radioStation)l
extern _native64(0xFC00454CF60B91DD) void UNFREEZE_RADIO_STATION(const char* radioStation)l
extern _native64(0xC1AA9F53CE982990) void SET_RADIO_AUTO_UNFREEZE(bool toggle)l
extern _native64(0x88795F13FACDA88D) void SET_INITIAL_PLAYER_STATION(const char* radioStation)l
extern _native64(0x19F21E63AE6EAE4E) void SET_USER_RADIO_CONTROL_ENABLED(bool toggle)l
extern _native64(0xB39786F201FEE30B) void SET_RADIO_TRACK(const char* radioStation, const char* radioTrack)l
extern _native64(0xBB6F1CAEC68B0BCE) void SET_VEHICLE_RADIO_LOUD(Vehicle vehicle, bool toggle)l
extern _native64(0x032A116663A4D5AC) bool _IS_VEHICLE_RADIO_LOUD(Vehicle vehicle)l
extern _native64(0x1098355A16064BB3) void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(bool Toggle)l
extern _native64(0x109697E2FFBAC8A1) bool UNK_0x109697E2FFBAC8A1()l
extern _native64(0x5F43D83FD6738741) bool _IS_PLAYER_VEHICLE_RADIO_ENABLED()l
extern _native64(0x3B988190C0AA6C0B) void SET_VEHICLE_RADIO_ENABLED(Vehicle vehicle, bool toggle)l
extern _native64(0x4E404A9361F75BB2) void UNK_0x4E404A9361F75BB2(const char* radioStation, const char* p1, bool p2)l
extern _native64(0x1654F24A88A8E3FE) void UNK_0x1654F24A88A8E3FE(const char* radioStation)l
extern _native64(0xF1620ECB50E01DE7) int _MAX_RADIO_STATION_INDEX()l
extern _native64(0x8D67489793FF428B) int FIND_RADIO_STATION_INDEX(int station)l
extern _native64(0x774BD811F656A122) void UNK_0x774BD811F656A122(const char* radioStation, bool p1)l
extern _native64(0x2C96CDB04FCA358E) void UNK_0x2C96CDB04FCA358E(float p0)l
extern _native64(0x031ACB6ABA18C729) void UNK_0x031ACB6ABA18C729(const char* radioStation, const char* p1)l
extern _native64(0xF3365489E0DD50F9) void UNK_0xF3365489E0DD50F9(any p0, bool p1)l
extern _native64(0xBDA07E5950085E46) void SET_AMBIENT_ZONE_STATE(any* p0, bool p1, bool p2)l
extern _native64(0x218DD44AAAC964FF) void CLEAR_AMBIENT_ZONE_STATE(const char* zoneName, bool p1)l
extern _native64(0x9748FA4DE50CCE3E) void SET_AMBIENT_ZONE_LIST_STATE(any* p0, bool p1, bool p2)l
extern _native64(0x120C48C614909FA4) void CLEAR_AMBIENT_ZONE_LIST_STATE(any* p0, bool p1)l
extern _native64(0x1D6650420CEC9D3B) void SET_AMBIENT_ZONE_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2)l
extern _native64(0xF3638DAE8C4045E1) void SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2)l
extern _native64(0x01E2817A479A7F9B) bool IS_AMBIENT_ZONE_ENABLED(const char* ambientZone)l
extern _native64(0x3B4BF5F0859204D9) void SET_CUTSCENE_AUDIO_OVERRIDE(const char* p0)l
extern _native64(0xBCC29F935ED07688) void GET_PLAYER_HEADSET_SOUND_ALTERNATE(const char* p0, float p1)l
extern _native64(0xDFEBD56D9BD1EB16) any PLAY_POLICE_REPORT(const char* name, float p1)l
extern _native64(0xB4F90FAF7670B16F) void _DISABLE_POLICE_REPORTS()l
extern _native64(0x1B9025BDA76822B6) void BLIP_SIREN(Vehicle vehicle)l
extern _native64(0x3CDC1E622CCE0356) void OVERRIDE_VEH_HORN(Vehicle vehicle, bool mute, int p2)l
extern _native64(0x9D6BFC12B05C6121) bool IS_HORN_ACTIVE(Vehicle vehicle)l
extern _native64(0x395BF71085D1B1D9) void SET_AGGRESSIVE_HORNS(bool toggle)l
extern _native64(0x02E93C796ABD3A97) void UNK_0x02E93C796ABD3A97(bool p0)l
extern _native64(0x58BB377BEC7CD5F4) void UNK_0x58BB377BEC7CD5F4(bool p0, bool p1)l
extern _native64(0xD11FA52EB849D978) bool IS_STREAM_PLAYING()l
extern _native64(0x4E72BBDBCA58A3DB) int GET_STREAM_PLAY_TIME()l
extern _native64(0x1F1F957154EC51DF) bool LOAD_STREAM(const char* streamName, const char* soundSet)l
extern _native64(0x59C16B79F53B3712) bool LOAD_STREAM_WITH_START_OFFSET(const char* streamName, int startOffset, const char* soundSet)l
extern _native64(0x89049DD63C08B5D1) void PLAY_STREAM_FROM_PED(Ped ped)l
extern _native64(0xB70374A758007DFA) void PLAY_STREAM_FROM_VEHICLE(Vehicle vehicle)l
extern _native64(0xEBAA9B64D76356FD) void PLAY_STREAM_FROM_OBJECT(Object object)l
extern _native64(0x58FCE43488F9F5F4) void PLAY_STREAM_FRONTEND()l
extern _native64(0x21442F412E8DE56B) void SPECIAL_FRONTEND_EQUAL(vector3 vec)l
extern _native64(0xA4718A1419D18151) void STOP_STREAM()l
extern _native64(0x9D64D7405520E3D3) void STOP_PED_SPEAKING(Ped ped, bool shaking)l
extern _native64(0xA9A41C1E940FB0E8) void DISABLE_PED_PAIN_AUDIO(Ped ped, bool toggle)l
extern _native64(0x932C2D096A2C3FFF) bool IS_AMBIENT_SPEECH_DISABLED(Ped ped)l
extern _native64(0x1FEF0683B96EBCF2) void SET_SIREN_WITH_NO_DRIVER(Vehicle vehicle, bool toggle)l
extern _native64(0x9C11908013EA4715) void _SOUND_VEHICLE_HORN_THIS_FRAME(Vehicle vehicle)l
extern _native64(0x76D683C108594D0E) void SET_HORN_ENABLED(Vehicle vehicle, bool toggle)l
extern _native64(0xE5564483E407F914) void SET_AUDIO_VEHICLE_PRIORITY(Vehicle vehicle, any p1)l
extern _native64(0x9D3AF56E94C9AE98) void UNK_0x9D3AF56E94C9AE98(any p0, float p1)l
extern _native64(0xFA932DE350266EF8) void USE_SIREN_AS_HORN(Vehicle vehicle, bool toggle)l
extern _native64(0x4F0C413926060B38) void _SET_VEHICLE_AUDIO(Vehicle vehicle, const char* audioName)l
extern _native64(0xF1F8157B8C3F171C) void UNK_0xF1F8157B8C3F171C(any p0, const char* p1, const char* p2)l
extern _native64(0xD2DCCD8E16E20997) void UNK_0xD2DCCD8E16E20997(any p0)l
extern _native64(0x5DB8010EE71FDEF2) bool UNK_0x5DB8010EE71FDEF2(Vehicle vehicle)l
extern _native64(0x59E7B488451F4D3A) void UNK_0x59E7B488451F4D3A(any p0, float p1)l
extern _native64(0x01BB4D577D38BD9E) void UNK_0x01BB4D577D38BD9E(any p0, float p1)l
extern _native64(0x1C073274E065C6D2) void UNK_0x1C073274E065C6D2(any p0, bool p1)l
extern _native64(0x2BE4BC731D039D5A) void UNK_0x2BE4BC731D039D5A(any p0, bool p1)l
extern _native64(0x4A04DE7CAB2739A1) void SET_VEHICLE_BOOST_ACTIVE(Vehicle vehicle, bool Toggle)l
extern _native64(0x6FDDAD856E36988A) void UNK_0x6FDDAD856E36988A(any p0, bool p1)l
extern _native64(0x06C0023BED16DD6B) void UNK_0x06C0023BED16DD6B(any p0, bool p1)l
extern _native64(0x3A539D52857EA82D) void PLAY_VEHICLE_DOOR_OPEN_SOUND(Vehicle vehicle, int p1)l
extern _native64(0x62A456AA4769EF34) void PLAY_VEHICLE_DOOR_CLOSE_SOUND(Vehicle vehicle, int p1)l
extern _native64(0xC15907D667F7CFB2) void UNK_0xC15907D667F7CFB2(Vehicle vehicle, bool toggle)l
extern _native64(0x6D28DC1671E334FD) bool IS_GAME_IN_CONTROL_OF_MUSIC()l
extern _native64(0x3BD3F52BA9B1E4E8) void SET_GPS_ACTIVE(bool active)l
extern _native64(0xB138AAB8A70D3C69) void PLAY_MISSION_COMPLETE_AUDIO(const char* audioName)l
extern _native64(0x19A30C23F5827F8A) bool IS_MISSION_COMPLETE_PLAYING()l
extern _native64(0x6F259F82D873B8B8) any UNK_0x6F259F82D873B8B8()l
extern _native64(0xF154B8D1775B2DEC) void UNK_0xF154B8D1775B2DEC(bool p0)l
extern _native64(0x013A80FC08F6E4F2) bool START_AUDIO_SCENE(const char* scene)l
extern _native64(0xDFE8422B3B94E688) void STOP_AUDIO_SCENE(const char* scene)l
extern _native64(0xBAC7FC81A75EC1A1) void STOP_AUDIO_SCENES()l
extern _native64(0xB65B60556E2A9225) bool IS_AUDIO_SCENE_ACTIVE(const char* scene)l
extern _native64(0xEF21A9EF089A2668) void SET_AUDIO_SCENE_VARIABLE(const char* scene, const char* variable, float value)l
extern _native64(0xA5F377B175A699C5) void UNK_0xA5F377B175A699C5(any p0)l
extern _native64(0x153973AB99FE8980) void _DYNAMIC_MIXER_RELATED_FN(Entity p0, const char* p1, float p2)l
extern _native64(0x18EB48CFC41F2EA0) void UNK_0x18EB48CFC41F2EA0(any p0, float p1)l
extern _native64(0x845FFC3A4FEEFA3E) any AUDIO_IS_SCRIPTED_MUSIC_PLAYING()l
extern _native64(0x1E5185B72EF5158A) bool PREPARE_MUSIC_EVENT(const char* eventName)l
extern _native64(0x5B17A90291133DA5) bool CANCEL_MUSIC_EVENT(const char* eventName)l
extern _native64(0x706D57B0F50DA710) bool TRIGGER_MUSIC_EVENT(const char* eventName)l
extern _native64(0xA097AB275061FB21) any UNK_0xA097AB275061FB21()l
extern _native64(0xE7A0D23DC414507B) any GET_MUSIC_PLAYTIME()l
extern _native64(0xFBE20329593DEC9D) void UNK_0xFBE20329593DEC9D(any p0, any p1, any p2, any p3)l
extern _native64(0xB32209EFFDC04913) any CLEAR_ALL_BROKEN_GLASS()l
extern _native64(0x70B8EC8FC108A634) void UNK_0x70B8EC8FC108A634(bool p0, any p1)l
extern _native64(0x149AEE66F0CB3A99) void UNK_0x149AEE66F0CB3A99(float p0, float p1)l
extern _native64(0x8BF907833BE275DE) void UNK_0x8BF907833BE275DE(float p0, float p1)l
extern _native64(0x062D5EAD4DA2FA6A) void UNK_0x062D5EAD4DA2FA6A()l
extern _native64(0x9D74AE343DB65533) bool PREPARE_ALARM(const char* alarmName)l
extern _native64(0x0355EF116C4C97B2) void START_ALARM(const char* alarmName, bool p2)l
extern _native64(0xA1CADDCD98415A41) void STOP_ALARM(const char* alarmName, bool toggle)l
extern _native64(0x2F794A877ADD4C92) void STOP_ALL_ALARMS(bool stop)l
extern _native64(0x226435CB96CCFC8C) bool IS_ALARM_PLAYING(const char* alarmName)l
extern _native64(0x02165D55000219AC) Hash GET_VEHICLE_DEFAULT_HORN(Vehicle vehicle)l
extern _native64(0xACB5DCCA1EC76840) Hash UNK_0xACB5DCCA1EC76840(Vehicle vehicle)l
extern _native64(0xF54BB7B61036F335) void RESET_PED_AUDIO_FLAGS(any p0)l
extern _native64(0xD2CC78CD3D0B50F9) void UNK_0xD2CC78CD3D0B50F9(any p0, bool p1)l
extern _native64(0xBF4DC1784BE94DFA) void UNK_0xBF4DC1784BE94DFA(any p0, bool p1, any p2)l
extern _native64(0x75773E11BA459E90) void UNK_0x75773E11BA459E90(any p0, bool p1)l
extern _native64(0xD57AAAE0E2214D11) void UNK_0xD57AAAE0E2214D11()l
extern _native64(0x552369F549563AD5) void _FORCE_AMBIENT_SIREN(bool value)l
extern _native64(0x43FA0DFC5DF87815) void UNK_0x43FA0DFC5DF87815(Vehicle vehicle, bool p1)l
extern _native64(0xB9EFD5C25018725A) void SET_AUDIO_FLAG(const char* flagName, bool toggle)l
extern _native64(0xC7ABCACA4985A766) any PREPARE_SYNCHRONIZED_AUDIO_EVENT(const char* p0, any p1)l
extern _native64(0x029FE7CD1B7E2E75) bool PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(any p0, any* p1)l
extern _native64(0x8B2FD4560E55DD2D) bool PLAY_SYNCHRONIZED_AUDIO_EVENT(any p0)l
extern _native64(0x92D6A88E64A94430) bool STOP_SYNCHRONIZED_AUDIO_EVENT(any p0)l
extern _native64(0xC8EDE9BDBCCBA6D4) void UNK_0xC8EDE9BDBCCBA6D4(any* p0, float p1, float p2, float p3)l
extern _native64(0x950A154B8DAB6185) void _SET_SYNCHRONIZED_AUDIO_EVENT_POSITION_THIS_FRAME(const char* p0, Entity p1)l
extern _native64(0x12561FCBB62D5B9C) void UNK_0x12561FCBB62D5B9C(int p0)l
extern _native64(0x044DBAD7A7FA2BE5) void UNK_0x044DBAD7A7FA2BE5(const char* p0, const char* p1)l
extern _native64(0xB4BBFD9CD8B3922B) void UNK_0xB4BBFD9CD8B3922B(const char* p0)l
extern _native64(0xE4E6DD5566D28C82) void UNK_0xE4E6DD5566D28C82()l
extern _native64(0x3A48AB4445D499BE) any UNK_0x3A48AB4445D499BE()l
extern _native64(0x4ADA3F19BE4A6047) void UNK_0x4ADA3F19BE4A6047(Ped ped)l
extern _native64(0x0150B6FF25A9E2E5) void UNK_0x0150B6FF25A9E2E5()l
extern _native64(0xBEF34B1D9624D5DD) void UNK_0xBEF34B1D9624D5DD(bool p0)l
extern _native64(0x806058BBDC136E06) void UNK_0x806058BBDC136E06()l
extern _native64(0x544810ED9DB6BBE6) any UNK_0x544810ED9DB6BBE6()l
extern _native64(0x5B50ABB1FE3746F4) any UNK_0x5B50ABB1FE3746F4()l
#pragma endregion //}
#pragma region CUTSCENE //{
extern _native64(0x7A86743F475D9E09) void REQUEST_CUTSCENE(const char* cutsceneName, int p1)l
extern _native64(0xC23DE0E91C30B58C) void _REQUEST_CUTSCENE_EX(const char* cutsceneName, int p1, int p2)l
extern _native64(0x440AF51A3462B86F) void REMOVE_CUTSCENE()l
extern _native64(0xC59F528E9AB9F339) bool HAS_CUTSCENE_LOADED()l
extern _native64(0x228D3D94F8A11C3C) bool HAS_THIS_CUTSCENE_LOADED(const char* cutsceneName)l
extern _native64(0x8D9DF6ECA8768583) void UNK_0x8D9DF6ECA8768583(int p0)l
extern _native64(0xB56BBBCC2955D9CB) bool UNK_0xB56BBBCC2955D9CB()l
extern _native64(0x71B74D2AE19338D0) bool UNK_0x71B74D2AE19338D0(int p0)l
extern _native64(0x4C61C75BEE8184C2) void UNK_0x4C61C75BEE8184C2(const char* p0, any p1, any p2)l
extern _native64(0x06A3524161C502BA) void UNK_0x06A3524161C502BA(any* p0)l
extern _native64(0xA1C996C2A744262E) bool UNK_0xA1C996C2A744262E(any* p0)l
extern _native64(0xD00D76A7DFC9D852) void UNK_0xD00D76A7DFC9D852(any* p0)l
extern _native64(0x0ABC54DE641DC0FC) any UNK_0x0ABC54DE641DC0FC(any* p0)l
extern _native64(0x186D5CB5E7B0FF7B) void START_CUTSCENE(int p0)l
extern _native64(0x1C9ADDA3244A1FBF) void START_CUTSCENE_AT_COORDS(vector3 vec, int p3)l
extern _native64(0xC7272775B4DC786E) void STOP_CUTSCENE(bool p0)l
extern _native64(0xD220BDD222AC4A1E) void STOP_CUTSCENE_IMMEDIATELY()l
extern _native64(0xB812B3FD1C01CF27) void SET_CUTSCENE_ORIGIN(vector3 vec, float p3, int p4)l
extern _native64(0x011883F41211432A) void UNK_0x011883F41211432A(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0xE625BEABBAFFDAB9) int GET_CUTSCENE_TIME()l
extern _native64(0xEE53B14A19E480D4) int GET_CUTSCENE_TOTAL_DURATION()l
extern _native64(0x40C8656EDAEDD569) bool WAS_CUTSCENE_SKIPPED()l
extern _native64(0x7C0A893088881D57) bool HAS_CUTSCENE_FINISHED()l
extern _native64(0x991251AFC3981F84) bool IS_CUTSCENE_ACTIVE()l
extern _native64(0xD3C2E180A40F031E) bool IS_CUTSCENE_PLAYING()l
extern _native64(0x49010A6A396553D8) int GET_CUTSCENE_SECTION_PLAYING()l
extern _native64(0x0A2E9FDB9A8C62F6) Entity GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x583DF8E3D4AFBD98) int UNK_0x583DF8E3D4AFBD98()l
extern _native64(0x4CEBC1ED31E8925E) bool UNK_0x4CEBC1ED31E8925E(const char* cutsceneName)l
extern _native64(0xE40C1C56DF95C2E8) void REGISTER_ENTITY_FOR_CUTSCENE(Ped cutscenePed, const char* cutsceneEntName, int p2, Hash modelHash, int p4)l
extern _native64(0xC0741A26499654CD) Entity GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x7F96F23FA9B73327) void UNK_0x7F96F23FA9B73327(Hash modelHash)l
extern _native64(0x9896CE4721BE84BA) void SET_CUTSCENE_TRIGGER_AREA(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native64(0x645D0B458D8E17B5) bool CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x4C6A6451C79E4662) bool CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0xB2CBCD0930DFB420) bool CAN_SET_EXIT_STATE_FOR_CAMERA(bool p0)l
extern _native64(0xC61B86C9F61EB404) void UNK_0xC61B86C9F61EB404(bool toggle)l
extern _native64(0x8093F23ABACCC7D4) void SET_CUTSCENE_FADE_VALUES(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x20746F7B1032A3C7) void UNK_0x20746F7B1032A3C7(bool p0, bool p1, bool p2, bool p3)l
extern _native64(0x06EE9048FD080382) void UNK_0x06EE9048FD080382(bool p0)l
extern _native64(0xA0FE76168A189DDB) int UNK_0xA0FE76168A189DDB()l
extern _native64(0x2F137B508DE238F2) void UNK_0x2F137B508DE238F2(bool p0)l
extern _native64(0xE36A98D8AB3D3C66) void UNK_0xE36A98D8AB3D3C66(bool p0)l
extern _native64(0x5EDEF0CF8C1DAB3C) any UNK_0x5EDEF0CF8C1DAB3C()l
extern _native64(0x41FAA8FB2ECE8720) void UNK_0x41FAA8FB2ECE8720(bool p0)l
extern _native64(0x2131046957F31B04) void REGISTER_SYNCHRONISED_SCRIPT_SPEECH()l
extern _native64(0xBA01E7B6DEEFBBC9) void SET_CUTSCENE_PED_COMPONENT_VARIATION(const char* cutsceneEntName, int p1, int p2, int p3, Hash modelHash)l
extern _native64(0x2A56C06EBEF2B0D9) void UNK_0x2A56C06EBEF2B0D9(const char* cutsceneEntName, Ped ped, Hash modelHash)l
extern _native64(0x499EF20C5DB25C59) bool DOES_CUTSCENE_ENTITY_EXIST(const char* cutsceneEntName, Hash modelHash)l
extern _native64(0x0546524ADE2E9723) void SET_CUTSCENE_PED_PROP_VARIATION(const char* cutsceneEntName, int p1, int p2, int p3, Hash modelHash)l
extern _native64(0x708BDD8CD795B043) bool UNK_0x708BDD8CD795B043()l
#pragma endregion //}
#pragma region INTERIOR //{
extern _native64(0xE4A84ABF135EF91A) int GET_INTERIOR_GROUP_ID(int interiorID)l
extern _native64(0x9E3B3E6D66F6E22F) vector3 GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(int interiorID, vector3 vec)l
extern _native64(0xBC72B5D7A1CBD54D) bool IS_INTERIOR_SCENE()l
extern _native64(0x26B0E73D7EAAF4D3) bool IS_VALID_INTERIOR(int interiorID)l
extern _native64(0xB365FC0C4E27FFA7) void CLEAR_ROOM_FOR_ENTITY(Entity entity)l
extern _native64(0x52923C4710DD9907) void FORCE_ROOM_FOR_ENTITY(Entity entity, int interiorID, Hash roomHashKey)l
extern _native64(0x47C2A06D4F5F424B) Hash GET_ROOM_KEY_FROM_ENTITY(Entity entity)l
extern _native64(0x399685DB942336BC) Hash GET_KEY_FOR_ENTITY_IN_ROOM(Entity entity)l
extern _native64(0x2107BA504071A6BB) int GET_INTERIOR_FROM_ENTITY(Entity entity)l
extern _native64(0x82EBB79E258FA2B7) void UNK_0x82EBB79E258FA2B7(Entity entity, int interiorID)l
extern _native64(0x920D853F3E17F1DA) void UNK_0x920D853F3E17F1DA(int interiorID, Hash roomHashKey)l
extern _native64(0xAF348AFCB575A441) void UNK_0xAF348AFCB575A441(const char* roomName)l
extern _native64(0x405DC2AEF6AF95B9) void UNK_0x405DC2AEF6AF95B9(Hash roomHashKey)l
extern _native64(0xA6575914D2A0B450) Hash _GET_ROOM_KEY_FROM_GAMEPLAY_CAM()l
extern _native64(0x23B59D8912F94246) void UNK_0x23B59D8912F94246()l
extern _native64(0xB0F7F8663821D9C3) int GET_INTERIOR_AT_COORDS(vector3 vec)l
extern _native64(0x3F6167F351168730) void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Pickup pickup, const char* roomName)l
extern _native64(0x2CA429C029CCF247) void _LOAD_INTERIOR(int interiorID)l
extern _native64(0x261CCE7EED010641) void UNPIN_INTERIOR(int interiorID)l
extern _native64(0x6726BDCCC1932F0E) bool IS_INTERIOR_READY(int interiorID)l
extern _native64(0x4C2330E61D3DEB56) any UNK_0x4C2330E61D3DEB56(int interiorID)l
extern _native64(0x05B7A89BD78797FC) int GET_INTERIOR_AT_COORDS_WITH_TYPE(vector3 vec, const char* interiorType)l
extern _native64(0xF0F77ADB9F67E79D) int _UNK_GET_INTERIOR_AT_COORDS(vector3 vec, int unk)l
extern _native64(0xEEA5AC2EDA7C33E8) bool _ARE_COORDS_COLLIDING_WITH_EXTERIOR(vector3 vec)l
extern _native64(0xEC4CF9FCB29A4424) int GET_INTERIOR_FROM_COLLISION(vector3 vec)l
extern _native64(0x55E86AF2712B36A1) void _ENABLE_INTERIOR_PROP(int interiorID, const char* propName)l
extern _native64(0x420BD37289EEE162) void _DISABLE_INTERIOR_PROP(int interiorID, const char* propName)l
extern _native64(0x35F7DD45E8C0A16D) bool _IS_INTERIOR_PROP_ENABLED(int interiorID, const char* propName)l
extern _native64(0x41F37C3427C75AE0) void REFRESH_INTERIOR(int interiorID)l
extern _native64(0xA97F257D0151A6AB) void _HIDE_MAP_OBJECT_THIS_FRAME(Hash mapObjectHash)l
extern _native64(0x6170941419D7D8EC) void DISABLE_INTERIOR(int interiorID, bool toggle)l
extern _native64(0xBC5115A5A939DD15) bool IS_INTERIOR_DISABLED(int interiorID)l
extern _native64(0xD9175F941610DB54) void CAP_INTERIOR(int interiorID, bool toggle)l
extern _native64(0x92BAC8ACF88CEC26) bool IS_INTERIOR_CAPPED(int interiorID)l
extern _native64(0x9E6542F0CE8E70A3) void UNK_0x9E6542F0CE8E70A3(bool toggle)l
#pragma endregion //}
#pragma region CAM //{
extern _native64(0x07E5B515DB0636FC) void RENDER_SCRIPT_CAMS(bool render, bool ease, int easeTime, bool p3, bool p4)l
extern _native64(0xC819F3CBB62BF692) void UNK_0xC819F3CBB62BF692(bool render, any p1, any p2)l
extern _native64(0xC3981DCE61D9E13F) Cam CREATE_CAM(const char* camName, bool p1)l
extern _native64(0xB51194800B257161) Cam CREATE_CAM_WITH_PARAMS(const char* camName, vector3 pos, vector3 rot, float fov, bool p8, int p9)l
extern _native64(0x5E3CF89C6BCCA67D) Cam CREATE_CAMERA(Hash camHash, bool p1)l
extern _native64(0x6ABFA3E16460F22D) Cam CREATE_CAMERA_WITH_PARAMS(Hash camHash, vector3 pos, vector3 rot, float fov, bool p8, any p9)l
extern _native64(0x865908C81A2C22E9) void DESTROY_CAM(Cam cam, bool thisScriptCheck)l
extern _native64(0x8E5FB15663F79120) void DESTROY_ALL_CAMS(bool thisScriptCheck)l
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
extern _native64(0x255F8DAFD540D397) float GET_CAM_FAR_DOF(Cam cam)l
extern _native64(0xBFD8727AEA3CCEBA) void SET_CAM_PARAMS(Cam cam, vector3 pos, vector3 rot, float fieldOfView, any p8, int p9, int p10, int p11)l
extern _native64(0x4D41783FB745E42E) void SET_CAM_COORD(Cam cam, vector3 pos)l
extern _native64(0x85973643155D0B07) void SET_CAM_ROT(Cam cam, vector3 rot, int rotationOrder)l
extern _native64(0xB13C14F66A00D047) void SET_CAM_FOV(Cam cam, float fieldOfView)l
extern _native64(0xC7848EFCCC545182) void SET_CAM_NEAR_CLIP(Cam cam, float nearClip)l
extern _native64(0xAE306F2A904BF86E) void SET_CAM_FAR_CLIP(Cam cam, float farClip)l
extern _native64(0x6F0F77FBA9A8F2E6) void SET_CAM_MOTION_BLUR_STRENGTH(Cam cam, float strength)l
extern _native64(0x3FA4BF0A7AB7DE2C) void SET_CAM_NEAR_DOF(Cam cam, float nearDOF)l
extern _native64(0xEDD91296CD01AEE0) void SET_CAM_FAR_DOF(Cam cam, float farDOF)l
extern _native64(0x5EE29B4D7D5DF897) void SET_CAM_DOF_STRENGTH(Cam cam, float dofStrength)l
extern _native64(0x3CF48F6F96E749DC) void SET_CAM_DOF_PLANES(Cam cam, float p1, float p2, float p3, float p4)l
extern _native64(0x16A96863A17552BB) void SET_CAM_USE_SHALLOW_DOF_MODE(Cam cam, bool toggle)l
extern _native64(0xA13B0222F3D94A94) void SET_USE_HI_DOF()l
extern _native64(0xF55E4046F6F831DC) void UNK_0xF55E4046F6F831DC(any p0, float p1)l
extern _native64(0xE111A7C0D200CBC5) void UNK_0xE111A7C0D200CBC5(any p0, float p1)l
extern _native64(0x7DD234D6F3914C5B) void _SET_CAM_DOF_FNUMBER_OF_LENS(Cam camera, float p1)l
extern _native64(0xC669EEA5D031B7DE) void _SET_CAM_DOF_FOCUS_DISTANCE_BIAS(Cam camera, float p1)l
extern _native64(0xC3654A441402562D) void _SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(Cam camera, float p1)l
extern _native64(0x2C654B4943BDDF7C) void _SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(Cam camera, float p1)l
extern _native64(0xFEDB7D269E8C60E3) void ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, vector3 Offset, bool isRelative)l
extern _native64(0x61A3DBA14AB7F411) void ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, vector3 vec, bool heading)l
extern _native64(0xA2FABBE87F4BAD82) void DETACH_CAM(Cam cam)l
extern _native64(0x45F1DE9C34B93AE6) void SET_CAM_INHERIT_ROLL_VEHICLE(Cam cam, bool p1)l
extern _native64(0xF75497BB865F0803) void POINT_CAM_AT_COORD(Cam cam, vector3 vec)l
extern _native64(0x5640BFF86B16E8DC) void POINT_CAM_AT_ENTITY(Cam cam, Entity entity, float p2, float p3, float p4, bool p5)l
extern _native64(0x68B2B5F33BA63C41) void POINT_CAM_AT_PED_BONE(Cam cam, int ped, int boneIndex, vector3 vec, bool p6)l
extern _native64(0xF33AB75780BA57DE) void STOP_CAM_POINTING(Cam cam)l
extern _native64(0x8C1DC7770C51DC8D) void SET_CAM_AFFECTS_AIMING(Cam cam, bool toggle)l
extern _native64(0x661B5C8654ADD825) void UNK_0x661B5C8654ADD825(any p0, bool p1)l
extern _native64(0xA2767257A320FC82) void UNK_0xA2767257A320FC82(any p0, bool p1)l
extern _native64(0x271017B9BA825366) void UNK_0x271017B9BA825366(any p0, bool p1)l
extern _native64(0x1B93E0107865DD40) void SET_CAM_DEBUG_NAME(Cam camera, const char* name)l
extern _native64(0x8609C75EC438FB3B) void ADD_CAM_SPLINE_NODE(Cam camera, vector3 vec, vector3 Rot, int length, int p8, int p9)l
extern _native64(0x0A9F2A468B328E74) void UNK_0x0A9F2A468B328E74(any p0, any p1, any p2, any p3)l
extern _native64(0x0FB82563989CF4FB) void UNK_0x0FB82563989CF4FB(any p0, any p1, any p2, any p3)l
extern _native64(0x609278246A29CA34) void UNK_0x609278246A29CA34(any p0, any p1, any p2)l
extern _native64(0x242B5874F0A4E052) void SET_CAM_SPLINE_PHASE(Cam cam, float p1)l
extern _native64(0xB5349E36C546509A) float GET_CAM_SPLINE_PHASE(Cam cam)l
extern _native64(0xD9D0E694C8282C96) float GET_CAM_SPLINE_NODE_PHASE(Cam cam)l
extern _native64(0x1381539FEE034CDA) void SET_CAM_SPLINE_DURATION(int cam, int timeDuration)l
extern _native64(0xD1B0F412F109EA5D) void UNK_0xD1B0F412F109EA5D(any p0, any p1)l
extern _native64(0xB22B17DF858716A6) bool GET_CAM_SPLINE_NODE_INDEX(Cam cam)l
extern _native64(0x83B8201ED82A9A2D) void UNK_0x83B8201ED82A9A2D(any p0, any p1, any p2, float p3)l
extern _native64(0xA6385DEB180F319F) void UNK_0xA6385DEB180F319F(any p0, any p1, float p2)l
extern _native64(0x40B62FA033EB0346) void OVERRIDE_CAM_SPLINE_VELOCITY(Cam cam, int p1, float p2, float p3)l
extern _native64(0x7DCF7C708D292D55) void OVERRIDE_CAM_SPLINE_MOTION_BLUR(Cam cam, int p1, float p2, float p3)l
extern _native64(0x7BF1A54AE67AC070) void UNK_0x7BF1A54AE67AC070(any p0, any p1, any p2)l
extern _native64(0x0290F35C0AD97864) bool IS_CAM_SPLINE_PAUSED(any p0)l
extern _native64(0x9FBDA379383A52A4) void SET_CAM_ACTIVE_WITH_INTERP(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation)l
extern _native64(0x036F97C908C2B52C) bool IS_CAM_INTERPOLATING(Cam cam)l
extern _native64(0x6A25241C340D3822) void SHAKE_CAM(Cam cam, const char* type, float amplitude)l
extern _native64(0xA2746EEAE3E577CD) void ANIMATED_SHAKE_CAM(Cam cam, const char* p1, const char* p2, const char* p3, float amplitude)l
extern _native64(0x6B24BFE83A2BE47B) bool IS_CAM_SHAKING(Cam cam)l
extern _native64(0xD93DB43B82BC0D00) void SET_CAM_SHAKE_AMPLITUDE(Cam cam, float amplitude)l
extern _native64(0xBDECF64367884AC3) void STOP_CAM_SHAKING(Cam cam, bool p1)l
extern _native64(0xF4C8CF9E353AFECA) void UNK_0xF4C8CF9E353AFECA(const char* p0, float p1)l
extern _native64(0xC2EAE3FB8CDBED31) void UNK_0xC2EAE3FB8CDBED31(const char* p0, const char* p1, const char* p2, float p3)l
extern _native64(0xC912AF078AF19212) bool IS_SCRIPT_GLOBAL_SHAKING()l
extern _native64(0x1C9D7949FA533490) void STOP_SCRIPT_GLOBAL_SHAKING(bool p0)l
extern _native64(0x9A2D0FB2E7852392) bool PLAY_CAM_ANIM(Cam cam, const char* animName, const char* animDictionary, vector3 vec, vector3 Rot, bool p9, int p10)l
extern _native64(0xC90621D8A0CEECF2) bool IS_CAM_PLAYING_ANIM(Cam cam, const char* animName, const char* animDictionary)l
extern _native64(0x4145A4C44FF3B5A6) void SET_CAM_ANIM_CURRENT_PHASE(Cam cam, float phase)l
extern _native64(0xA10B2DB49E92A6B0) float GET_CAM_ANIM_CURRENT_PHASE(Cam cam)l
extern _native64(0xE32EFE9AB4A9AA0C) bool PLAY_SYNCHRONIZED_CAM_ANIM(any p0, any p1, const char* animName, const char* animDictionary)l
extern _native64(0x503F5920162365B2) void UNK_0x503F5920162365B2(any p0, float p1, float p2, float p3)l
extern _native64(0xF9D02130ECDD1D77) void _SET_CAMERA_RANGE(Cam cam, float range)l
extern _native64(0xC91C6C55199308CA) void UNK_0xC91C6C55199308CA(any p0, float p1, float p2, float p3)l
extern _native64(0xC8B5C4A79CC18B94) void UNK_0xC8B5C4A79CC18B94(Cam p0)l
extern _native64(0x5C48A1D6E3B33179) bool UNK_0x5C48A1D6E3B33179(any p0)l
extern _native64(0xB16FCE9DDC7BA182) bool IS_SCREEN_FADED_OUT()l
extern _native64(0x5A859503B0C08678) bool IS_SCREEN_FADED_IN()l
extern _native64(0x797AC7CB535BA28F) bool IS_SCREEN_FADING_OUT()l
extern _native64(0x5C544BC6C57AC575) bool IS_SCREEN_FADING_IN()l
extern _native64(0xD4E8E24955024033) void DO_SCREEN_FADE_IN(int duration)l
extern _native64(0x891B5B39AC6302AF) void DO_SCREEN_FADE_OUT(int duration)l
extern _native64(0xDCD4EA924F42D01A) any SET_WIDESCREEN_BORDERS(bool p0, int p1)l
extern _native64(0x14D6F5678D8F1B37) vector3 GET_GAMEPLAY_CAM_COORD()l
extern _native64(0x837765A25378F0BB) vector3 GET_GAMEPLAY_CAM_ROT(int rotationOrder)l
extern _native64(0x65019750A0324133) float GET_GAMEPLAY_CAM_FOV()l
extern _native64(0x487A82C650EB7799) void CUSTOM_MENU_COORDINATES(float p0)l
extern _native64(0x0225778816FDC28C) void UNK_0x0225778816FDC28C(float p0)l
extern _native64(0x743607648ADD4587) float GET_GAMEPLAY_CAM_RELATIVE_HEADING()l
extern _native64(0xB4EC2312F4E5B1F1) void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading)l
extern _native64(0x3A6867B4845BEDA2) float GET_GAMEPLAY_CAM_RELATIVE_PITCH()l
extern _native64(0x6D0858B8EDFD2B7D) any SET_GAMEPLAY_CAM_RELATIVE_PITCH(float x, float Value2)l
extern _native64(0x103991D4A307D472) void _SET_GAMEPLAY_CAM_RAW_YAW(float yaw)l
extern _native64(0x759E13EBC1C15C5A) void _SET_GAMEPLAY_CAM_RAW_PITCH(float pitch)l
extern _native64(0x469F2ECDEC046337) void UNK_0x469F2ECDEC046337(bool p0)l
extern _native64(0xFD55E49555E017CF) void SHAKE_GAMEPLAY_CAM(const char* shakeName, float intensity)l
extern _native64(0x016C090630DF1F89) bool IS_GAMEPLAY_CAM_SHAKING()l
extern _native64(0xA87E00932DB4D85D) void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(float amplitude)l
extern _native64(0x0EF93E9F3D08C178) void STOP_GAMEPLAY_CAM_SHAKING(bool p0)l
extern _native64(0x8BBACBF51DA047A8) void UNK_0x8BBACBF51DA047A8(any p0)l
extern _native64(0x39B5D1B10383F0C8) bool IS_GAMEPLAY_CAM_RENDERING()l
extern _native64(0x3044240D2E0FA842) bool UNK_0x3044240D2E0FA842()l
extern _native64(0x705A276EBFF3133D) bool UNK_0x705A276EBFF3133D()l
extern _native64(0xDB90C6CCA48940F1) void UNK_0xDB90C6CCA48940F1(bool p0)l
extern _native64(0xEA7F0AD7E9BA676F) void _ENABLE_CROSSHAIR_THIS_FRAME()l
extern _native64(0x70FDA869F3317EA9) bool IS_GAMEPLAY_CAM_LOOKING_BEHIND()l
extern _native64(0x2AED6301F67007D5) void UNK_0x2AED6301F67007D5(Entity entity)l
extern _native64(0x49482F9FCD825AAA) void UNK_0x49482F9FCD825AAA(Entity entity)l
extern _native64(0xFD3151CD37EA2245) void UNK_0xFD3151CD37EA2245(any p0)l
extern _native64(0xDD79DF9F4D26E1C9) void UNK_0xDD79DF9F4D26E1C9()l
extern _native64(0xE33D59DA70B58FDF) bool IS_SPHERE_VISIBLE(vector3 vec, float radius)l
extern _native64(0xC6D3D26810C8E0F9) bool IS_FOLLOW_PED_CAM_ACTIVE()l
extern _native64(0x44A113DD6FFC48D1) bool SET_FOLLOW_PED_CAM_CUTSCENE_CHAT(const char* p0, int p1)l
extern _native64(0x271401846BD26E92) void UNK_0x271401846BD26E92(bool p0, bool p1)l
extern _native64(0xC8391C309684595A) void UNK_0xC8391C309684595A()l
extern _native64(0x8F993D26E0CA5E8E) any _CLAMP_GAMEPLAY_CAM_YAW(float minimum, float maximum)l
extern _native64(0xA516C198B7DCA1E1) any _CLAMP_GAMEPLAY_CAM_PITCH(float minimum, float maximum)l
extern _native64(0xDF2E1F7742402E81) void _ANIMATE_GAMEPLAY_CAM_ZOOM(float p0, float distance)l
extern _native64(0xE9EA16D6E54CDCA4) any UNK_0xE9EA16D6E54CDCA4(Vehicle p0, int p1)l
extern _native64(0xDE2EF5DA284CC8DF) void _DISABLE_FIRST_PERSON_CAM_THIS_FRAME()l
extern _native64(0x59424BD75174C9B1) void UNK_0x59424BD75174C9B1()l
extern _native64(0x33E6C8EFD0CD93E9) int GET_FOLLOW_PED_CAM_ZOOM_LEVEL()l
extern _native64(0x8D4D46230B2C353A) int GET_FOLLOW_PED_CAM_VIEW_MODE()l
extern _native64(0x5A4F9EDF1673F704) void SET_FOLLOW_PED_CAM_VIEW_MODE(int viewMode)l
extern _native64(0xCBBDE6D335D6D496) bool IS_FOLLOW_VEHICLE_CAM_ACTIVE()l
extern _native64(0x91EF6EE6419E5B97) void UNK_0x91EF6EE6419E5B97(bool p0)l
extern _native64(0x9DFE13ECDC1EC196) void SET_TIME_IDLE_DROP(bool p0, bool p1)l
extern _native64(0xEE82280AB767B690) int GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL()l
extern _native64(0x19464CB6E4078C8A) void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(int zoomLevel)l
extern _native64(0xA4FF579AC0E3AAAE) int GET_FOLLOW_VEHICLE_CAM_VIEW_MODE()l
extern _native64(0xAC253D7842768F48) void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(int viewMode)l
extern _native64(0xEE778F8C7E1142E2) any UNK_0xEE778F8C7E1142E2(any p0)l
extern _native64(0x2A2173E46DAECD12) void UNK_0x2A2173E46DAECD12(any p0, any p1)l
extern _native64(0x19CAFA3C87F7C2FF) any UNK_0x19CAFA3C87F7C2FF()l
extern _native64(0x68EDDA28A5976D07) bool IS_AIM_CAM_ACTIVE()l
extern _native64(0x74BD83EA840F6BC9) bool UNK_0x74BD83EA840F6BC9()l
extern _native64(0x5E346D934122613F) bool IS_FIRST_PERSON_AIM_CAM_ACTIVE()l
extern _native64(0x1A31FE0049E542F6) void DISABLE_AIM_CAM_THIS_UPDATE()l
extern _native64(0x7EC52CC40597D170) float _GET_GAMEPLAY_CAM_ZOOM()l
extern _native64(0x70894BD0915C5BCA) any UNK_0x70894BD0915C5BCA(float p0)l
extern _native64(0xCED08CBE8EBB97C7) void UNK_0xCED08CBE8EBB97C7(float p0, float p1)l
extern _native64(0x2F7F2B26DD3F18EE) void UNK_0x2F7F2B26DD3F18EE(float p0, float p1)l
extern _native64(0xBCFC632DB7673BF0) void UNK_0xBCFC632DB7673BF0(float p0, float p1)l
extern _native64(0x0AF7B437918103B3) void UNK_0x0AF7B437918103B3(float p0)l
extern _native64(0x42156508606DE65E) void UNK_0x42156508606DE65E(float p0)l
extern _native64(0x4008EDF7D6E48175) void UNK_0x4008EDF7D6E48175(bool p0)l
extern _native64(0xA200EB1EE790F448) vector3 _GET_GAMEPLAY_CAM_COORDS()l
extern _native64(0x5B4E4C817FCC2DFB) vector3 _GET_GAMEPLAY_CAM_ROT(int rotationOrder)l
extern _native64(0x26903D9CD1175F2C) int UNK_0x26903D9CD1175F2C(any p0, any p1)l
extern _native64(0x80EC114669DAEFF4) float UNK_0x80EC114669DAEFF4()l
extern _native64(0x5F35F6732C3FBBA0) float UNK_0x5F35F6732C3FBBA0(any p0)l
extern _native64(0xD0082607100D7193) float UNK_0xD0082607100D7193()l
extern _native64(0xDFC8CBC606FDB0FC) float UNK_0xDFC8CBC606FDB0FC()l
extern _native64(0xA03502FC581F7D9B) float UNK_0xA03502FC581F7D9B()l
extern _native64(0x9780F32BCAF72431) float UNK_0x9780F32BCAF72431()l
extern _native64(0x162F9D995753DC19) float UNK_0x162F9D995753DC19()l
extern _native64(0xD51ADCD2D8BC0FB3) void SET_GAMEPLAY_COORD_HINT(float p0, float p1, float p2, any p3, any p4, any p5, any p6)l
extern _native64(0x2B486269ACD548D3) void SET_GAMEPLAY_PED_HINT(Ped p0, vector3 vec_1, bool p4, any p5, any p6, any p7)l
extern _native64(0xA2297E18F3E71C2E) void SET_GAMEPLAY_VEHICLE_HINT(any p0, float p1, float p2, float p3, bool p4, any p5, any p6, any p7)l
extern _native64(0x83E87508A2CA2AC6) void SET_GAMEPLAY_OBJECT_HINT(any p0, float p1, float p2, float p3, bool p4, any p5, any p6, any p7)l
extern _native64(0x189E955A8313E298) void SET_GAMEPLAY_ENTITY_HINT(Entity entity, vector3 Offset, bool p4, int p5, int p6, int p7, any p8)l
extern _native64(0xE520FF1AD2785B40) bool IS_GAMEPLAY_HINT_ACTIVE()l
extern _native64(0xF46C581C61718916) void STOP_GAMEPLAY_HINT(bool p0)l
extern _native64(0xCCD078C2665D2973) void UNK_0xCCD078C2665D2973(bool p0)l
extern _native64(0x247ACBC4ABBC9D1C) void UNK_0x247ACBC4ABBC9D1C(bool p0)l
extern _native64(0xBF72910D0F26F025) any UNK_0xBF72910D0F26F025()l
extern _native64(0x513403FB9C56211F) void SET_GAMEPLAY_HINT_FOV(float FOV)l
extern _native64(0xF8BDBF3D573049A1) void UNK_0xF8BDBF3D573049A1(float p0)l
extern _native64(0xD1F8363DFAD03848) void UNK_0xD1F8363DFAD03848(float p0)l
extern _native64(0x5D7B620DAE436138) void UNK_0x5D7B620DAE436138(float p0)l
extern _native64(0xC92717EF615B6704) void UNK_0xC92717EF615B6704(float p0)l
extern _native64(0xE3433EADAAF7EE40) void GET_IS_MULTIPLAYER_BRIEF(bool p0)l
extern _native64(0x51669F7D1FB53D9F) void SET_CINEMATIC_BUTTON_ACTIVE(bool p0)l
extern _native64(0xB15162CB5826E9E8) bool IS_CINEMATIC_CAM_RENDERING()l
extern _native64(0xDCE214D9ED58F3CF) void SHAKE_CINEMATIC_CAM(const char* p0, float p1)l
extern _native64(0xBBC08F6B4CB8FF0A) bool IS_CINEMATIC_CAM_SHAKING()l
extern _native64(0xC724C701C30B2FE7) void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(float p0)l
extern _native64(0x2238E588E588A6D7) void STOP_CINEMATIC_CAM_SHAKING(bool p0)l
extern _native64(0xADFF1B2A555F5FBA) void _DISABLE_VEHICLE_FIRST_PERSON_CAM_THIS_FRAME()l
extern _native64(0x62ECFCFDEE7885D6) void UNK_0x62ECFCFDEE7885D6()l
extern _native64(0x9E4CFFF989258472) void UNK_0x9E4CFFF989258472()l
extern _native64(0xF4F2C0D4EE209E20) void UNK_0xF4F2C0D4EE209E20()l
extern _native64(0xCA9D2AA3E326D720) bool UNK_0xCA9D2AA3E326D720()l
extern _native64(0x4F32C0D5A90A9B40) bool _IS_IN_VEHICLE_CAM_DISABLED()l
extern _native64(0x741B0129D4560F31) void CREATE_CINEMATIC_SHOT(any p0, int p1, any p2, Entity entity)l
extern _native64(0xCC9F3371A7C28BC9) bool IS_CINEMATIC_SHOT_ACTIVE(any p0)l
extern _native64(0x7660C6E75D3A078E) void STOP_CINEMATIC_SHOT(any p0)l
extern _native64(0xA41BCD7213805AAC) void UNK_0xA41BCD7213805AAC(bool p0)l
extern _native64(0xDC9DA9E8789F5246) void UNK_0xDC9DA9E8789F5246()l
extern _native64(0xDCF0754AC3D6FD4E) void SET_CINEMATIC_MODE_ACTIVE(bool p0)l
extern _native64(0x1F2300CB7FA7B7F6) any UNK_0x1F2300CB7FA7B7F6()l
extern _native64(0x17FCA7199A530203) any UNK_0x17FCA7199A530203()l
extern _native64(0xDB629FFD9285FA06) void STOP_CUTSCENE_CAM_SHAKING()l
extern _native64(0x12DED8CA53D47EA5) void UNK_0x12DED8CA53D47EA5(float p0)l
extern _native64(0x89215EC747DF244A) Entity UNK_0x89215EC747DF244A(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8)l
extern _native64(0x5A43C76F7FC7BA5F) void UNK_0x5A43C76F7FC7BA5F()l
extern _native64(0x80C8B1846639BB19) void _SET_CAM_EFFECT(int p0)l
extern _native64(0x5C41E6BABC9E2112) void UNK_0x5C41E6BABC9E2112(any p0)l
extern _native64(0x21E253A7F8DA5DFB) void UNK_0x21E253A7F8DA5DFB(const char* vehicleName)l
extern _native64(0x11FA5D3479C7DD47) void UNK_0x11FA5D3479C7DD47(any p0)l
extern _native64(0xEAF0FA793D05C592) any UNK_0xEAF0FA793D05C592()l
extern _native64(0x8BFCEB5EA1B161B6) any UNK_0x8BFCEB5EA1B161B6()l
#pragma endregion //}
#pragma region WEAPON //{
extern _native64(0xC8B46D7727D864AA) void ENABLE_LASER_SIGHT_RENDERING(bool toggle)l
extern _native64(0x0DB57B41EC1DB083) Hash GET_WEAPON_COMPONENT_TYPE_MODEL(Hash componentHash)l
extern _native64(0xF46CDC33180FDA94) Hash GET_WEAPONTYPE_MODEL(Hash weaponHash)l
extern _native64(0x4215460B9B8B7FA0) Hash GET_WEAPONTYPE_SLOT(Hash weaponHash)l
extern _native64(0xC3287EE3050FB74C) Hash GET_WEAPONTYPE_GROUP(Hash weaponHash)l
extern _native64(0xADF692B254977C0C) void SET_CURRENT_PED_WEAPON(Ped ped, Hash weaponHash, bool equipNow)l
extern _native64(0x3A87E44BB9A01D54) bool GET_CURRENT_PED_WEAPON(Ped ped, Hash* weaponHash, bool p2)l
extern _native64(0x3B390A939AF0B5FC) Entity GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Ped ped)l
extern _native64(0x8483E98E8B888AE2) Hash GET_BEST_PED_WEAPON(Ped ped, bool p1)l
extern _native64(0x75C55983C2C39DAA) bool SET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash weaponHash)l
extern _native64(0x1017582BCD3832DC) bool GET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash* weaponHash)l
extern _native64(0x475768A975D5AD17) bool IS_PED_ARMED(Ped ped, int p1)l
extern _native64(0x937C71165CF334B3) bool IS_WEAPON_VALID(Hash weaponHash)l
extern _native64(0x8DECB02F88F428BC) bool HAS_PED_GOT_WEAPON(Ped ped, Hash weaponHash, bool p2)l
extern _native64(0xB80CA294F2F26749) bool IS_PED_WEAPON_READY_TO_SHOOT(Ped ped)l
extern _native64(0xEFFED78E9011134D) Hash GET_PED_WEAPONTYPE_IN_SLOT(Ped ped, Hash weaponSlot)l
extern _native64(0x015A522136D7F951) int GET_AMMO_IN_PED_WEAPON(Ped ped, Hash weaponhash)l
extern _native64(0x78F0424C34306220) void ADD_AMMO_TO_PED(Ped ped, Hash weaponHash, int ammo)l
extern _native64(0x14E56BC5B5DB6A19) void SET_PED_AMMO(Ped ped, Hash weaponHash, int ammo)l
extern _native64(0x3EDCB0505123623B) void SET_PED_INFINITE_AMMO(Ped ped, bool toggle, Hash weaponHash)l
extern _native64(0x183DADC6AA953186) void SET_PED_INFINITE_AMMO_CLIP(Ped ped, bool toggle)l
extern _native64(0xBF0FD6E56C964FCB) void GIVE_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool isHidden, bool equipNow)l
extern _native64(0xB282DC6EBD803C75) void GIVE_DELAYED_WEAPON_TO_PED(Ped ped, Hash weaponHash, int time, bool equipNow)l
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
extern _native64(0x208A1888007FC0E6) void SET_PED_DROPS_INVENTORY_WEAPON(Ped ped, Hash weaponHash, vector3 Offset, any p5)l
extern _native64(0xA38DCFFCEA8962FA) int GET_MAX_AMMO_IN_CLIP(Ped ped, Hash weaponHash, bool p2)l
extern _native64(0x2E1202248937775C) bool GET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int* ammo)l
extern _native64(0xDCD2A934D65CB497) bool SET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int ammo)l
extern _native64(0xDC16122C7A20C933) bool GET_MAX_AMMO(Ped ped, Hash weaponHash, int* ammo)l
extern _native64(0x5FD1E1F011E76D7E) void SET_PED_AMMO_BY_TYPE(Ped ped, any ammoType, int ammo)l
extern _native64(0x39D22031557946C1) int GET_PED_AMMO_BY_TYPE(Ped ped, any ammoType)l
extern _native64(0xA4EFEF9440A5B0EF) void SET_PED_AMMO_TO_DROP(any p0, any p1)l
extern _native64(0xE620FD3512A04F18) void UNK_0xE620FD3512A04F18(float p0)l
extern _native64(0x7FEAD38B326B9F74) Hash GET_PED_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash)l
extern _native64(0x6C4D0409BA1A2BC2) bool GET_PED_LAST_WEAPON_IMPACT_COORD(Ped ped, vector3* coords)l
extern _native64(0xD0D7B1E680ED4A1A) void SET_PED_GADGET(Ped ped, Hash gadgetHash, bool p2)l
extern _native64(0xF731332072F5156C) bool GET_IS_PED_GADGET_EQUIPPED(Ped ped, Hash gadgetHash)l
extern _native64(0x0A6DB4965674D243) Hash GET_SELECTED_PED_WEAPON(Ped ped)l
extern _native64(0xFC4BD125DE7611E4) void EXPLODE_PROJECTILES(Ped ped, Hash weaponHash, bool p2)l
extern _native64(0xFC52E0F37E446528) void REMOVE_ALL_PROJECTILES_OF_TYPE(Hash weaponHash, bool p1)l
extern _native64(0x840F03E9041E2C9C) float _GET_LOCKON_RANGE_OF_CURRENT_PED_WEAPON(Ped ped)l
extern _native64(0x814C9D19DFD69679) float GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(Ped ped)l
extern _native64(0x717C8481234E3B88) bool HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Ped driver, Vehicle vehicle, Hash weaponHash, any p3)l
extern _native64(0xD966D51AA5B28BB9) void GIVE_WEAPON_COMPONENT_TO_PED(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0x1E8BE90C74FB4C09) void REMOVE_WEAPON_COMPONENT_FROM_PED(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0xC593212475FAE340) bool HAS_PED_GOT_WEAPON_COMPONENT(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0x0D78DE0572D3969E) bool IS_PED_WEAPON_COMPONENT_ACTIVE(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native64(0x8C0D57EA686FAD87) bool _PED_SKIP_NEXT_RELOADING(Ped ped)l
extern _native64(0x20AE33F3AC9C0033) bool MAKE_PED_RELOAD(Ped ped)l
extern _native64(0x5443438F033E29C3) void REQUEST_WEAPON_ASSET(Hash weaponHash, int p1, int p2)l
extern _native64(0x36E353271F0E90EE) bool HAS_WEAPON_ASSET_LOADED(Hash weaponHash)l
extern _native64(0xAA08EF13F341C8FC) void REMOVE_WEAPON_ASSET(Hash weaponHash)l
extern _native64(0x9541D3CF0D398F36) Object CREATE_WEAPON_OBJECT(Hash weaponHash, int ammoCount, vector3 vec, bool showWorldModel, float heading, any p7)l
extern _native64(0x33E179436C0B31DB) void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Object weaponObject, Hash addonHash)l
extern _native64(0xF7D82B0D66777611) void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(any p0, any p1)l
extern _native64(0x76A18844E743BF91) bool HAS_WEAPON_GOT_WEAPON_COMPONENT(Object weapon, Hash addonHash)l
extern _native64(0xB1FA61371AF7C4B7) void GIVE_WEAPON_OBJECT_TO_PED(Object weaponObject, Ped ped)l
extern _native64(0x5CEE3DF569CECAB0) bool DOES_WEAPON_TAKE_WEAPON_COMPONENT(Hash weaponHash, Hash componentHash)l
extern _native64(0xCAE1DC9A0E22A16D) Object GET_WEAPON_OBJECT_FROM_PED(Ped ped, bool p1)l
extern _native64(0x50969B9B89ED5738) void SET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash, int tintIndex)l
extern _native64(0x2B9EEDC07BD06B9F) int GET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash)l
extern _native64(0xF827589017D4E4A9) void SET_WEAPON_OBJECT_TINT_INDEX(Object weapon, int tintIndex)l
extern _native64(0xCD183314F7CD2E57) int GET_WEAPON_OBJECT_TINT_INDEX(Object weapon)l
extern _native64(0x5DCF6C5CAB2E9BF7) int GET_WEAPON_TINT_COUNT(Hash weaponHash)l
extern _native64(0xD92C739EE34C9EBA) bool GET_WEAPON_HUD_STATS(Hash weaponHash, int* outData)l
extern _native64(0xB3CAF387AE12E9F8) bool GET_WEAPON_COMPONENT_HUD_STATS(Hash componentHash, int* outData)l
extern _native64(0x3133B907D8B32053) float UNK_0x3133B907D8B32053(any p0, any p1)l
extern _native64(0x583BE370B1EC6EB4) int GET_WEAPON_CLIP_SIZE(Hash weaponHash)l
extern _native64(0x8378627201D5497D) void SET_PED_CHANCE_OF_FIRING_BLANKS(Ped ped, vector2 Bias)l
extern _native64(0xB4C8D77C80C0421E) Entity UNK_0xB4C8D77C80C0421E(Ped ped, float p1)l
extern _native64(0x48164DBB970AC3F0) void REQUEST_WEAPON_HIGH_DETAIL_MODEL(Entity weaponObject)l
extern _native64(0x65F0C5AE05943EC7) bool IS_PED_CURRENT_WEAPON_SILENCED(Ped ped)l
extern _native64(0x4B7620C47217126C) bool SET_WEAPON_SMOKEGRENADE_ASSIGNED(Ped ped)l
extern _native64(0xCEA66DAD478CD39B) any SET_FLASH_LIGHT_FADE_DISTANCE(float distance)l
extern _native64(0x1055AC3A667F09D9) void SET_WEAPON_ANIMATION_OVERRIDE(Ped ped, Hash animStyle)l
extern _native64(0x3BE0BB12D25FB305) int GET_WEAPON_DAMAGE_TYPE(Hash weaponHash)l
extern _native64(0xE4DCEC7FD5B739A5) void UNK_0xE4DCEC7FD5B739A5(Ped ped)l
extern _native64(0xBC7BE5ABC0879F74) bool CAN_USE_WEAPON_ON_PARACHUTE(Hash weaponHash)l
extern _native64(0x4757F00BC6323CFE) void _SET_WEAPON_DAMAGE_MODIFIER(Hash weaponHash, float modifier)l
#pragma endregion //}
#pragma region ITEMSET //{
extern _native64(0x35AD299F50D91B24) any CREATE_ITEMSET(bool p0)l
extern _native64(0xDE18220B1C183EDA) void DESTROY_ITEMSET(any p0)l
extern _native64(0xB1B1EA596344DFAB) bool IS_ITEMSET_VALID(any p0)l
extern _native64(0xE3945201F14637DD) bool ADD_TO_ITEMSET(any p0, any p1)l
extern _native64(0x25E68244B0177686) void REMOVE_FROM_ITEMSET(any p0, any p1)l
extern _native64(0xD9127E83ABF7C631) any GET_ITEMSET_SIZE(any p0)l
extern _native64(0x7A197E2521EE2BAB) any GET_INDEXED_ITEM_IN_ITEMSET(any p0, any p1)l
extern _native64(0x2D0FC594D1E9C107) bool IS_IN_ITEMSET(any p0, any p1)l
extern _native64(0x41BC0D722FC04221) void CLEAN_ITEMSET(any p0)l
#pragma endregion //}
#pragma region STREAMING //{
extern _native64(0xBD6E84632DD4CB3F) void LOAD_ALL_OBJECTS_NOW()l
extern _native64(0x4448EB75B4904BDB) void LOAD_SCENE(vector3 vec)l
extern _native64(0xC4582015556D1C46) any NETWORK_UPDATE_LOAD_SCENE()l
extern _native64(0x64E630FAF5F60F44) void NETWORK_STOP_LOAD_SCENE()l
extern _native64(0x41CA5A33160EA4AB) bool IS_NETWORK_LOADING_SCENE()l
extern _native64(0xE37B76C387BE28ED) void SET_INTERIOR_ACTIVE(int interiorID, bool toggle)l
extern _native64(0x963D27A58DF860AC) void REQUEST_MODEL(Hash model)l
extern _native64(0xA0261AEF7ACFC51E) void REQUEST_MENU_PED_MODEL(Hash model)l
extern _native64(0x98A4EB5D89A0C952) bool HAS_MODEL_LOADED(Hash model)l
extern _native64(0x8A7A40100EDFEC58) void UNK_0x8A7A40100EDFEC58(int interiorID, const char* roomName)l
extern _native64(0xE532F5D78798DAAB) void SET_MODEL_AS_NO_LONGER_NEEDED(Hash model)l
extern _native64(0x35B9E0803292B641) bool IS_MODEL_IN_CDIMAGE(Hash model)l
extern _native64(0xC0296A2EDF545E92) bool IS_MODEL_VALID(Hash model)l
extern _native64(0x19AAC8F07BFEC53E) bool IS_MODEL_A_VEHICLE(Hash model)l
extern _native64(0x07503F7948F491A7) any REQUEST_COLLISION_AT_COORD(vector3 vec)l
extern _native64(0x923CB32A3B874FCB) void REQUEST_COLLISION_FOR_MODEL(Hash model)l
extern _native64(0x22CCA434E368F03A) bool HAS_COLLISION_FOR_MODEL_LOADED(Hash model)l
extern _native64(0xC9156DC11411A9EA) void REQUEST_ADDITIONAL_COLLISION_AT_COORD(float p0, float p1, float p2)l
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
extern _native64(0x717CD6E6FAEBBEDC) void SET_GAME_PAUSES_FOR_STREAMING(bool toggle)l
extern _native64(0x77B5F9A36BF96710) void SET_REDUCE_PED_MODEL_BUDGET(bool toggle)l
extern _native64(0x80C527893080CCF3) void SET_REDUCE_VEHICLE_MODEL_BUDGET(bool toggle)l
extern _native64(0x42CBE54462D92634) void SET_DITCH_POLICE_MODELS(bool toggle)l
extern _native64(0x4060057271CEBC89) int GET_NUMBER_OF_STREAMING_REQUESTS()l
extern _native64(0x944955FB2A3935C8) any REQUEST_PTFX_ASSET()l
extern _native64(0xCA7D9B86ECA7481B) bool HAS_PTFX_ASSET_LOADED()l
extern _native64(0x88C6814073DD4A73) void REMOVE_PTFX_ASSET()l
extern _native64(0xB80D8756B4668AB6) void REQUEST_NAMED_PTFX_ASSET(const char* fxName)l
extern _native64(0x8702416E512EC454) bool HAS_NAMED_PTFX_ASSET_LOADED(const char* fxName)l
extern _native64(0x5F61EBBE1A00F96D) void _REMOVE_NAMED_PTFX_ASSET(const char* fxName)l
extern _native64(0xCB9E1EB3BE2AF4E9) void SET_VEHICLE_POPULATION_BUDGET(int p0)l
extern _native64(0x8C95333CFC3340F3) void SET_PED_POPULATION_BUDGET(int p0)l
extern _native64(0x31B73D1EA9F01DA2) void CLEAR_FOCUS()l
extern _native64(0xBB7454BAFF08FE25) void _SET_FOCUS_AREA(vector3 vec, vector3 offset)l
extern _native64(0x198F77705FA0931D) void SET_FOCUS_ENTITY(Entity entity)l
extern _native64(0x2DDFF3FB9075D747) bool IS_ENTITY_FOCUS(Entity entity)l
extern _native64(0x0811381EF5062FEC) void UNK_0x0811381EF5062FEC(Entity p0)l
extern _native64(0xAF12610C644A35C9) void UNK_0xAF12610C644A35C9(const char* p0, bool p1)l
extern _native64(0x4E52E752C76E7E7A) void UNK_0x4E52E752C76E7E7A(any p0)l
extern _native64(0x219C7B8D53E429FD) any FORMAT_FOCUS_HEADING(vector3 vec, float rad, any p4, any p5)l
extern _native64(0x1F3F018BC3AFA77C) any UNK_0x1F3F018BC3AFA77C(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7, any p8)l
extern _native64(0x0AD9710CEE2F590F) any UNK_0x0AD9710CEE2F590F(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native64(0x1EE7D8DF4425F053) void UNK_0x1EE7D8DF4425F053(any p0)l
extern _native64(0x7D41E9D2D17C5B2D) any UNK_0x7D41E9D2D17C5B2D(any p0)l
extern _native64(0x07C313F94746702C) any UNK_0x07C313F94746702C(any p0)l
extern _native64(0xBC9823AB80A3DCAC) any UNK_0xBC9823AB80A3DCAC()l
extern _native64(0x212A8D0D2BABFAC2) bool NEW_LOAD_SCENE_START(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7)l
extern _native64(0xACCFB4ACF53551B0) bool NEW_LOAD_SCENE_START_SPHERE(float p0, float p1, float p2, float p3, any p4)l
extern _native64(0xC197616D221FF4A4) void NEW_LOAD_SCENE_STOP()l
extern _native64(0xA41A05B6CB741B85) bool IS_NEW_LOAD_SCENE_ACTIVE()l
extern _native64(0x01B8247A7A8B9AD1) bool IS_NEW_LOAD_SCENE_LOADED()l
extern _native64(0x71E7B2E657449AAD) any UNK_0x71E7B2E657449AAD()l
extern _native64(0xFAA23F2CBA159D67) void START_PLAYER_SWITCH(Ped from, Ped to, int flags, int switchType)l
extern _native64(0x95C0A5BBDC189AA1) void STOP_PLAYER_SWITCH()l
extern _native64(0xD9D2CFFF49FAB35F) bool IS_PLAYER_SWITCH_IN_PROGRESS()l
extern _native64(0xB3C94A90D9FC9E62) int GET_PLAYER_SWITCH_TYPE()l
extern _native64(0xB5D7B26B45720E05) int GET_IDEAL_PLAYER_SWITCH_TYPE(vector3 vec_1, vector3 vec_2)l
extern _native64(0x470555300D10B2A5) int GET_PLAYER_SWITCH_STATE()l
extern _native64(0x20F898A5D9782800) int GET_PLAYER_SHORT_SWITCH_STATE()l
extern _native64(0x5F2013F8BC24EE69) void UNK_0x5F2013F8BC24EE69(int p0)l
extern _native64(0x78C0D93253149435) any UNK_0x78C0D93253149435()l
extern _native64(0xC208B673CE446B61) void SET_PLAYER_SWITCH_OUTRO(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8)l
extern _native64(0x0FDE9DBFC0A6BC65) void UNK_0x0FDE9DBFC0A6BC65(any* p0)l
extern _native64(0x43D1680C6D19A8E9) void UNK_0x43D1680C6D19A8E9()l
extern _native64(0x74DE2E8739086740) void UNK_0x74DE2E8739086740()l
extern _native64(0x8E2A065ABDAE6994) void UNK_0x8E2A065ABDAE6994()l
extern _native64(0xAD5FDF34B81BFE79) void UNK_0xAD5FDF34B81BFE79()l
extern _native64(0xDFA80CB25D0A19B3) any UNK_0xDFA80CB25D0A19B3()l
extern _native64(0xD4793DFF3AF2ABCD) void UNK_0xD4793DFF3AF2ABCD()l
extern _native64(0xBD605B8E0E18B3BB) void UNK_0xBD605B8E0E18B3BB()l
extern _native64(0xAAB3200ED59016BC) void _SWITCH_OUT_PLAYER(Ped ped, int flags, int unknown)l
extern _native64(0xD8295AF639FD9CB8) void UNK_0xD8295AF639FD9CB8(any p0)l
extern _native64(0x933BBEEB8C61B5F4) any UNK_0x933BBEEB8C61B5F4()l
extern _native64(0x08C2D6C52A3104BB) int SET_PLAYER_INVERTED_UP()l
extern _native64(0x5B48A06DD0E792A5) any UNK_0x5B48A06DD0E792A5()l
extern _native64(0x5B74EA8CFD5E3E7E) any DESTROY_PLAYER_IN_PAUSE_MENU()l
extern _native64(0x1E9057A74FD73E23) void UNK_0x1E9057A74FD73E23()l
extern _native64(0x0C15B0E443B2349D) any UNK_0x0C15B0E443B2349D()l
extern _native64(0xA76359FC80B2438E) void UNK_0xA76359FC80B2438E(float p0)l
extern _native64(0xBED8CA5FF5E04113) void UNK_0xBED8CA5FF5E04113(float p0, float p1, float p2, float p3)l
extern _native64(0x472397322E92A856) void UNK_0x472397322E92A856()l
extern _native64(0x40AEFD1A244741F2) void UNK_0x40AEFD1A244741F2(bool p0)l
extern _native64(0x03F1A106BDA7DD3E) void UNK_0x03F1A106BDA7DD3E()l
extern _native64(0x95A7DABDDBB78AE7) void UNK_0x95A7DABDDBB78AE7(any* p0, any* p1)l
extern _native64(0x63EB2B972A218CAC) void UNK_0x63EB2B972A218CAC()l
extern _native64(0xFB199266061F820A) any UNK_0xFB199266061F820A()l
extern _native64(0xF4A0DADB70F57FA6) void UNK_0xF4A0DADB70F57FA6()l
extern _native64(0x5068F488DDB54DD8) any UNK_0x5068F488DDB54DD8()l
extern _native64(0x3D245789CE12982C) void PREFETCH_SRL(const char* srl)l
extern _native64(0xD0263801A4C5B0BB) bool IS_SRL_LOADED()l
extern _native64(0x9BADDC94EF83B823) void BEGIN_SRL()l
extern _native64(0x0A41540E63C9EE17) void END_SRL()l
extern _native64(0xA74A541C6884E7B8) void SET_SRL_TIME(float p0)l
extern _native64(0xEF39EE20C537E98C) void UNK_0xEF39EE20C537E98C(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xBEB2D9A1D9A8F55A) void UNK_0xBEB2D9A1D9A8F55A(any p0, any p1, any p2, any p3)l
extern _native64(0x20C6C7E4EB082A7F) void UNK_0x20C6C7E4EB082A7F(bool p0)l
extern _native64(0xF8155A7F03DDFC8E) void UNK_0xF8155A7F03DDFC8E(any p0)l
extern _native64(0xB85F26619073E775) void SET_HD_AREA(vector3 vec, float ground)l
extern _native64(0xCE58B1CFB9290813) void CLEAR_HD_AREA()l
extern _native64(0xB5A4DB34FE89B88A) void UNK_0xB5A4DB34FE89B88A()l
extern _native64(0xCCE26000E9A6FAD7) void SHUTDOWN_CREATOR_BUDGET()l
extern _native64(0x0BC3144DEB678666) bool UNK_0x0BC3144DEB678666(Hash modelHash)l
extern _native64(0xF086AD9354FAC3A3) void UNK_0xF086AD9354FAC3A3(any p0)l
extern _native64(0x3D3D8B3BE5A83D35) any UNK_0x3D3D8B3BE5A83D35()l
#pragma endregion //}
#pragma region SCRIPT //{
extern _native64(0x6EB5F71AA68F2E8E) void REQUEST_SCRIPT(const char* scriptName)l
extern _native64(0xC90D2DCACD56184C) void SET_SCRIPT_AS_NO_LONGER_NEEDED(const char* scriptName)l
extern _native64(0xE6CC9F3BA0FB9EF1) bool HAS_SCRIPT_LOADED(const char* scriptName)l
extern _native64(0xFC04745FBE67C19A) bool DOES_SCRIPT_EXIST(const char* scriptName)l
extern _native64(0xD62A67D26D9653E6) void REQUEST_SCRIPT_WITH_NAME_HASH(Hash scriptHash)l
extern _native64(0xC5BC038960E9DB27) void SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(Hash scriptHash)l
extern _native64(0x5F0F0C783EB16C04) bool HAS_SCRIPT_WITH_NAME_HASH_LOADED(Hash scriptHash)l
extern _native64(0xF86AA3C56BA31381) bool _DOES_SCRIPT_WITH_NAME_HASH_EXIST(Hash scriptHash)l
extern _native64(0xC8B189ED9138BCD4) void TERMINATE_THREAD(int threadId)l
extern _native64(0x46E9AE36D8FA6417) bool IS_THREAD_ACTIVE(int threadId)l
extern _native64(0x05A42BA9FC8DA96B) const char* _GET_NAME_OF_THREAD(int threadId)l
extern _native64(0xDADFADA5A20143A8) void _BEGIN_ENUMERATING_THREADS()l
extern _native64(0x30B4FA1C82DD4B9F) int _GET_ID_OF_NEXT_THREAD_IN_ENUMERATION()l
extern _native64(0xC30338E8088E2E21) int GET_ID_OF_THIS_THREAD()l
extern _native64(0x1090044AD1DA76FA) void TERMINATE_THIS_THREAD()l
extern _native64(0x2C83A9DA6BFFC4F9) int _GET_NUMBER_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH(Hash scriptHash)l
extern _native64(0x442E0A7EDE4A738A) const char* GET_THIS_SCRIPT_NAME()l
extern _native64(0x8A1C8B1738FFE87E) Hash GET_HASH_OF_THIS_SCRIPT_NAME()l
extern _native64(0x5F92A689A06620AA) int GET_NUMBER_OF_EVENTS(bool p0)l
extern _native64(0x936E6168A9BCEDB5) bool GET_EVENT_EXISTS(bool p0, int p1)l
extern _native64(0xD8F66A3A60C62153) int GET_EVENT_AT_INDEX(bool p0, int p1)l
extern _native64(0x2902843FCD2B2D79) bool GET_EVENT_DATA(bool p0, int p1, const void* p2, int p3)l
extern _native64(0x5AE99C571D5BBE5D) void TRIGGER_SCRIPT_EVENT(bool p0, const void* args, int argCount, int bitset)l
extern _native64(0x078EBE9809CCD637) void SHUTDOWN_LOADING_SCREEN()l
extern _native64(0x5262CC1995D07E09) void SET_NO_LOADING_SCREEN(bool toggle)l
extern _native64(0x18C1270EA7F199BC) bool _GET_NO_LOADING_SCREEN()l
extern _native64(0xB1577667C3708F9B) void UNK_0xB1577667C3708F9B()l
#pragma endregion //}
#pragma region UI //{
extern _native64(0xABA17D7CE615ADBF) void _SET_LOADING_PROMPT_TEXT_ENTRY(const char* string)l
extern _native64(0xBD12F8228410D9B4) void _SHOW_LOADING_PROMPT(int busySpinnerType)l
extern _native64(0x10D373323E5B9C0D) void _REMOVE_LOADING_PROMPT()l
extern _native64(0xC65AB383CD91DF98) void UNK_0xC65AB383CD91DF98()l
extern _native64(0xD422FCC5F239A915) bool _IS_LOADING_PROMPT_BEING_DISPLAYED()l
extern _native64(0xB2A592B04648A9CB) any UNK_0xB2A592B04648A9CB()l
extern _native64(0x9245E81072704B8A) void UNK_0x9245E81072704B8A(bool p0)l
extern _native64(0xAAE7CE1D63167423) void _SHOW_CURSOR_THIS_FRAME()l
extern _native64(0x8DB8CFFD58B62552) void _SET_CURSOR_SPRITE(int spriteId)l
extern _native64(0x98215325A695E78A) void UNK_0x98215325A695E78A(bool p0)l
extern _native64(0x3D9ACB1EB139E702) any UNK_0x3D9ACB1EB139E702()l
extern _native64(0x632B2940C67F4EA9) bool UNK_0x632B2940C67F4EA9(int scaleformHandle, any* p1, any* p2, any* p3)l
extern _native64(0x6F1554B0CC2089FA) void UNK_0x6F1554B0CC2089FA(bool p0)l
extern _native64(0x55598D21339CB998) void UNK_0x55598D21339CB998(float p0)l
extern _native64(0x25F87B30C382FCA7) void UNK_0x25F87B30C382FCA7()l
extern _native64(0xA8FDB297A8D25FBA) void UNK_0xA8FDB297A8D25FBA()l
extern _native64(0xBE4390CB40B3E627) void _REMOVE_NOTIFICATION(int notificationId)l
extern _native64(0xA13C11E1B5C06BFC) void UNK_0xA13C11E1B5C06BFC()l
extern _native64(0x583049884A2EEE3C) void UNK_0x583049884A2EEE3C()l
extern _native64(0xFDB423997FA30340) void UNK_0xFDB423997FA30340()l
extern _native64(0xE1CD1E48E025E661) void UNK_0xE1CD1E48E025E661()l
extern _native64(0xA9CBFD40B3FA3010) any UNK_0xA9CBFD40B3FA3010()l
extern _native64(0xD4438C0564490E63) void UNK_0xD4438C0564490E63()l
extern _native64(0xB695E2CD0A2DA9EE) void UNK_0xB695E2CD0A2DA9EE()l
extern _native64(0x82352748437638CA) int _GET_CURRENT_NOTIFICATION()l
extern _native64(0x56C8B608CFD49854) void UNK_0x56C8B608CFD49854()l
extern _native64(0xADED7F5748ACAFE6) void UNK_0xADED7F5748ACAFE6()l
extern _native64(0x92F0DA1E27DB96DC) void UNK_0x92F0DA1E27DB96DC(int p0)l
extern _native64(0x17430B918701C342) void _SET_NOTIFICATION_FLASH_COLOR(RGBA colour)l
extern _native64(0x17AD8C9706BDD88A) void UNK_0x17AD8C9706BDD88A(any p0)l
extern _native64(0x4A0C7C9BB10ABB36) void UNK_0x4A0C7C9BB10ABB36(bool p0)l
extern _native64(0xFDD85225B2DEA55E) void UNK_0xFDD85225B2DEA55E()l
extern _native64(0xFDEC055AB549E328) void UNK_0xFDEC055AB549E328()l
extern _native64(0x80FE4F3AB4E1B62A) void UNK_0x80FE4F3AB4E1B62A()l
extern _native64(0xBAE4F9B97CD43B30) void UNK_0xBAE4F9B97CD43B30(bool p0)l
extern _native64(0x317EBA71D7543F52) void UNK_0x317EBA71D7543F52(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0x202709F4C58A0424) void _SET_NOTIFICATION_TEXT_ENTRY(const char* type)l
extern _native64(0x2B7E9A4EAAA93C89) int _SET_NOTIFICATION_MESSAGE_2(const char* p0, int p1, int p2, int p3, bool p4, const char* picName1, const char* picName2)l
extern _native64(0x1CCD9A37359072CF) int _SET_NOTIFICATION_MESSAGE(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject)l
extern _native64(0xC6F580E4C94926AC) int _SET_NOTIFICATION_MESSAGE_3(const char* picName1, const char* picName2, bool p2, any p3, const char* p4, const char* p5)l
extern _native64(0x1E6611149DB3DB6B) int _SET_NOTIFICATION_MESSAGE_4(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration)l
extern _native64(0x5CBF7BADE20DB93E) int _SET_NOTIFICATION_MESSAGE_CLAN_TAG(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration, const char* clanTag)l
extern _native64(0x531B84E7DA981FB6) int _SET_NOTIFICATION_MESSAGE_CLAN_TAG_2(const char* picName1, const char* picName2, bool flash, int iconType1, const char* sender, const char* subject, float duration, const char* clanTag, int iconType2, int p9)l
extern _native64(0x2ED7843F8F801023) int _DRAW_NOTIFICATION(bool blink, bool p1)l
extern _native64(0x44FA03975424A0EE) int _DRAW_NOTIFICATION_2(bool blink, bool p1)l
extern _native64(0x378E809BF61EC840) int _DRAW_NOTIFICATION_3(bool blink, bool p1)l
extern _native64(0xAA295B6F28BD587D) int _DRAW_NOTIFICATION_ICON(const char* p0, const char* p1, int p2, int p3, const char* p4)l
extern _native64(0x97C9E4E7024A8F2C) int _NOTIFICATION_SEND_APARTMENT_INVITE(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, RGB colour)l
extern _native64(0x137BC35589E34E1E) int _NOTIFICATION_SEND_CLAN_INVITE(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, const char* playerName, RGB colour)l
extern _native64(0x33EE12743CCD6343) any UNK_0x33EE12743CCD6343(any p0, any p1, any p2)l
extern _native64(0xC8F3AAF93D0600BF) any UNK_0xC8F3AAF93D0600BF(any p0, any p1, any p2, any p3)l
extern _native64(0x7AE0589093A2E088) any UNK_0x7AE0589093A2E088(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xF020C96915705B3A) int _DRAW_NOTIFICATION_4(bool blink, bool p1)l
extern _native64(0x8EFCCF6EC66D85E4) any UNK_0x8EFCCF6EC66D85E4(any* p0, any* p1, any* p2, bool p3, bool p4)l
extern _native64(0xB6871B0555B02996) any UNK_0xB6871B0555B02996(any* p0, any* p1, any p2, any* p3, any* p4, any p5)l
extern _native64(0xD202B92CBF1D816F) any UNK_0xD202B92CBF1D816F(int type, int image, const char* text)l
extern _native64(0xDD6CB2CCE7C2735C) any UNK_0xDD6CB2CCE7C2735C(int type, const char* button, const char* text)l
extern _native64(0xB87A37EEB7FAA67D) void BEGIN_TEXT_COMMAND_PRINT(const char* GxtEntry)l
extern _native64(0x9D77056A530643F6) void END_TEXT_COMMAND_PRINT(int duration, bool drawImmediately)l
extern _native64(0x853648FD1063A213) void BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(const char* text)l
extern _native64(0x8A9BA1AB3E237613) bool END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED()l
extern _native64(0x25FBB336DF1804CB) void BEGIN_TEXT_COMMAND_DISPLAY_TEXT(const char* text)l
extern _native64(0xCD015E5BB0D96A57) void END_TEXT_COMMAND_DISPLAY_TEXT(vector2 vector)l
extern _native64(0x54CE8AC98E120CAB) void _BEGIN_TEXT_COMMAND_WIDTH(const char* text)l
extern _native64(0x85F061DA64ED2F67) float _END_TEXT_COMMAND_GET_WIDTH(int font)l
extern _native64(0x521FB041D93DD0E4) void _BEGIN_TEXT_COMMAND_LINE_COUNT(const char* entry)l
extern _native64(0x9040DFB09BE75706) int _END_TEXT_COMMAND_GET_LINE_COUNT(vector2 vector)l
extern _native64(0x8509B634FBE7DA11) void BEGIN_TEXT_COMMAND_DISPLAY_HELP(const char* inputType)l
extern _native64(0x238FFE5C7B0498A6) void END_TEXT_COMMAND_DISPLAY_HELP(any p0, bool loop, bool beep, int shape)l
extern _native64(0x0A24DA3A41B718F5) void BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(const char* labelName)l
extern _native64(0x10BDDBFC529428DD) bool END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(int p0)l
extern _native64(0xF9113A30DE5C6670) void BEGIN_TEXT_COMMAND_SET_BLIP_NAME(const char* gxtentry)l
extern _native64(0xBC38B49BCB83BC9B) void END_TEXT_COMMAND_SET_BLIP_NAME(Blip blip)l
extern _native64(0x23D69E0465570028) void _BEGIN_TEXT_COMMAND_OBJECTIVE(const char* p0)l
extern _native64(0xCFDBDF5AE59BA0F4) void _END_TEXT_COMMAND_OBJECTIVE(bool p0)l
extern _native64(0xE124FA80A759019C) void BEGIN_TEXT_COMMAND_CLEAR_PRINT(const char* text)l
extern _native64(0xFCC75460ABA29378) void END_TEXT_COMMAND_CLEAR_PRINT()l
extern _native64(0x8F9EE5687F8EECCD) void _BEGIN_TEXT_COMMAND_TIMER(const char* p0)l
extern _native64(0xA86911979638106F) void _END_TEXT_COMMAND_TIMER(bool p0)l
extern _native64(0x03B504CF259931BC) void ADD_TEXT_COMPONENT_INTEGER(int value)l
extern _native64(0xE7DCB5B874BCD96E) void ADD_TEXT_COMPONENT_FLOAT(float value, int decimalPlaces)l
extern _native64(0xC63CD5D2920ACBE7) void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(const char* labelName)l
extern _native64(0x17299B63C7683A2B) void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(Hash gxtEntryHash)l
extern _native64(0x80EAD8E2E1D5D52E) void ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(Blip blip)l
extern _native64(0x6C188BE134E074AA) void ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const char* text)l
extern _native64(0x1115F16B8AB9E8BF) void ADD_TEXT_COMPONENT_SUBSTRING_TIME(int timestamp, int flags)l
extern _native64(0x0E4C749FF9DE9CC4) void ADD_TEXT_COMPONENT_FORMATTED_INTEGER(int value, bool commaSeparated)l
extern _native64(0x761B77454205A61D) void _ADD_TEXT_COMPONENT_APP_TITLE(const char* p0, int p1)l
extern _native64(0x94CF4AC034C9C986) void ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(const char* website)l
extern _native64(0x5F68520888E69014) void _ADD_TEXT_COMPONENT_SCALEFORM(const char* p0)l
extern _native64(0x39BBF623FC803EAC) void _SET_NOTIFICATION_COLOR_NEXT(int p0)l
extern _native64(0x169BD9382084C8C0) const char* _GET_TEXT_SUBSTRING(const char* text, int position, int length)l
extern _native64(0xB2798643312205C5) const char* _GET_TEXT_SUBSTRING_SAFE(const char* text, int position, int length, int maxLength)l
extern _native64(0xCE94AEBA5D82908A) const char* _GET_TEXT_SUBSTRING_SLICE(const char* text, int startPosition, int endPosition)l
extern _native64(0x7B5280EBA9840C72) const char* _GET_LABEL_TEXT(const char* labelName)l
extern _native64(0xCC33FA791322B9D9) void CLEAR_PRINTS()l
extern _native64(0x9D292F73ADBD9313) void CLEAR_BRIEF()l
extern _native64(0x6178F68A87A4D3A0) void CLEAR_ALL_HELP_MESSAGES()l
extern _native64(0xCF708001E1E536DD) void CLEAR_THIS_PRINT(const char* p0)l
extern _native64(0x2CEA2839313C09AC) void CLEAR_SMALL_PRINTS()l
extern _native64(0x1C7302E725259789) bool DOES_TEXT_BLOCK_EXIST(const char* gxt)l
extern _native64(0x71A78003C8E71424) void REQUEST_ADDITIONAL_TEXT(const char* gxt, int slot)l
extern _native64(0x6009F9F1AE90D8A6) void _REQUEST_ADDITIONAL_TEXT_2(const char* gxt, int slot)l
extern _native64(0x02245FE4BED318B8) bool HAS_ADDITIONAL_TEXT_LOADED(int slot)l
extern _native64(0x2A179DF17CCF04CD) void CLEAR_ADDITIONAL_TEXT(int p0, bool p1)l
extern _native64(0x8B6817B71B85EBF0) bool IS_STREAMING_ADDITIONAL_TEXT(int p0)l
extern _native64(0xADBF060E2B30C5BC) bool HAS_THIS_ADDITIONAL_TEXT_LOADED(const char* gxt, int slot)l
extern _native64(0x7984C03AA5CC2F41) bool IS_MESSAGE_BEING_DISPLAYED()l
extern _native64(0xAC09CA973C564252) bool DOES_TEXT_LABEL_EXIST(const char* gxt)l
extern _native64(0x801BD273D3A23F74) int GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(const char* gxt)l
extern _native64(0xF030907CCBB8A9FD) int GET_LENGTH_OF_LITERAL_STRING(const char* string)l
extern _native64(0x43E4111189E54F0E) int _GET_LENGTH_OF_STRING(const char* p0)l
extern _native64(0xD0EF8A959B8A4CB9) const char* GET_STREET_NAME_FROM_HASH_KEY(Hash hash)l
extern _native64(0x1930DFA731813EC4) bool IS_HUD_PREFERENCE_SWITCHED_ON()l
extern _native64(0x9EB6522EA68F22FE) bool IS_RADAR_PREFERENCE_SWITCHED_ON()l
extern _native64(0xAD6DACA4BA53E0A4) bool IS_SUBTITLE_PREFERENCE_SWITCHED_ON()l
extern _native64(0xA6294919E56FF02A) void DISPLAY_HUD(bool toggle)l
extern _native64(0x7669F9E39DC17063) void UNK_0x7669F9E39DC17063()l
extern _native64(0x402F9ED62087E898) void UNK_0x402F9ED62087E898()l
extern _native64(0xA0EBB943C300E693) any DISPLAY_RADAR(bool Toggle)l
extern _native64(0xA86478C6958735C5) bool IS_HUD_HIDDEN()l
extern _native64(0x157F93B036700462) bool IS_RADAR_HIDDEN()l
extern _native64(0xAF754F20EB5CD51A) bool _IS_RADAR_ENABLED()l
extern _native64(0x4F7D8A9BFB0B43E9) void SET_BLIP_ROUTE(Blip blip, bool enabled)l
extern _native64(0x837155CD2F63DA09) void SET_BLIP_ROUTE_COLOUR(Blip blip, int colour)l
extern _native64(0x60296AF4BA14ABC5) void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(bool p0)l
extern _native64(0x57D760D55F54E071) void UNK_0x57D760D55F54E071(bool p0)l
extern _native64(0xBD12C5EEE184C337) void RESPONDING_AS_TEMP(float p0)l
extern _native64(0x096EF57A0C999BBA) void SET_RADAR_ZOOM(int zoomLevel)l
extern _native64(0xF98E4B3E56AFC7B1) void UNK_0xF98E4B3E56AFC7B1(any p0, float p1)l
extern _native64(0xCB7CC0D58405AD41) void _SET_RADAR_ZOOM_LEVEL_THIS_FRAME(float zoomLevel)l
extern _native64(0xD2049635DEB9C375) void UNK_0xD2049635DEB9C375()l
extern _native64(0x7C9C91AB74A0360F) void GET_HUD_COLOUR(int hudColorIndex, int* r, int* g, int* b, int* a)l
extern _native64(0xD68A5FF8A3A89874) void UNK_0xD68A5FF8A3A89874(RGBA colour)l
extern _native64(0x16A304E6CB2BFAB9) void UNK_0x16A304E6CB2BFAB9(RGBA colour)l
extern _native64(0x1CCC708F0F850613) void _SET_HUD_COLOURS_SWITCH(int hudColorIndex, int hudColorIndex2)l
extern _native64(0xF314CF4F0211894E) void _SET_HUD_COLOUR(int hudColorIndex, RGBA colour)l
extern _native64(0x02CFBA0C9E9275CE) void FLASH_ABILITY_BAR(bool toggle)l
extern _native64(0x9969599CCFF5D85E) void SET_ABILITY_BAR_VALUE(float p0, float p1)l
extern _native64(0xA18AFB39081B6A1F) any FLASH_WANTED_DISPLAY(bool p0)l
extern _native64(0xBA8D65C1C65702E5) void UNK_0xBA8D65C1C65702E5(bool p0)l
extern _native64(0xDB88A37483346780) float _GET_TEXT_SCALE_HEIGHT(float size, int font)l
extern _native64(0x07C837F9A01C34C9) void SET_TEXT_SCALE(float p0, float size)l
extern _native64(0xBE6B23FFA53FB442) void SET_TEXT_COLOUR(RGBA colour)l
extern _native64(0xC02F4DBFB51D988B) void SET_TEXT_CENTRE(bool align)l
extern _native64(0x6B3C4650BC8BEE47) void SET_TEXT_RIGHT_JUSTIFY(bool toggle)l
extern _native64(0x4E096588B13FFECA) void SET_TEXT_JUSTIFICATION(int justifyType)l
extern _native64(0x63145D9C883A1A70) void SET_TEXT_WRAP(float start, float end)l
extern _native64(0xA50ABC31E3CDFAFF) void SET_TEXT_LEADING(bool p0)l
extern _native64(0x038C1F517D7FDCF8) void SET_TEXT_PROPORTIONAL(bool p0)l
extern _native64(0x66E0276CC5F6B9DA) void SET_TEXT_FONT(int fontType)l
extern _native64(0x1CA3E9EAC9D93E5E) void SET_TEXT_DROP_SHADOW()l
extern _native64(0x465C84BC39F1C351) void SET_TEXT_DROPSHADOW(int distance, RGBA colour)l
extern _native64(0x2513DFB0FB8400FE) void SET_TEXT_OUTLINE()l
extern _native64(0x441603240D202FA6) void SET_TEXT_EDGE(int p0, RGBA colour)l
extern _native64(0x5F15302936E07111) void SET_TEXT_RENDER_ID(int renderId)l
extern _native64(0x52F0982D7FD156B6) int GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID()l
extern _native64(0x57D9C12635E25CE3) bool REGISTER_NAMED_RENDERTARGET(const char* p0, bool p1)l
extern _native64(0x78DCDC15C9F116B4) bool IS_NAMED_RENDERTARGET_REGISTERED(const char* p0)l
extern _native64(0xE9F6FFE837354DD4) bool RELEASE_NAMED_RENDERTARGET(any* p0)l
extern _native64(0xF6C09E276AEB3F2D) void LINK_NAMED_RENDERTARGET(Hash hash)l
extern _native64(0x1A6478B61C6BDC3B) any GET_NAMED_RENDERTARGET_RENDER_ID(const char* p0)l
extern _native64(0x113750538FA31298) bool IS_NAMED_RENDERTARGET_LINKED(Hash hash)l
extern _native64(0x8DFCED7A656F8802) void CLEAR_HELP(bool toggle)l
extern _native64(0xDAD37F45428801AE) bool IS_HELP_MESSAGE_ON_SCREEN()l
extern _native64(0x214CD562A939246A) bool UNK_0x214CD562A939246A()l
extern _native64(0x4D79439A6B55AC67) bool IS_HELP_MESSAGE_BEING_DISPLAYED()l
extern _native64(0x327EDEEEAC55C369) bool IS_HELP_MESSAGE_FADING_OUT()l
extern _native64(0x4A9923385BDB9DAD) bool UNK_0x4A9923385BDB9DAD()l
extern _native64(0x186E5D252FA50E7D) int _GET_BLIP_INFO_ID_ITERATOR()l
extern _native64(0x9A3FF3DE163034E8) int GET_NUMBER_OF_ACTIVE_BLIPS()l
extern _native64(0x14F96AA50D6FBEA7) Blip GET_NEXT_BLIP_INFO_ID(int blipSprite)l
extern _native64(0x1BEDE233E6CD2A1F) Blip GET_FIRST_BLIP_INFO_ID(int blipSprite)l
extern _native64(0xFA7C7F0AADF25D09) vector3 GET_BLIP_INFO_ID_COORD(Blip blip)l
extern _native64(0x1E314167F701DC3B) int GET_BLIP_INFO_ID_DISPLAY(Blip blip)l
extern _native64(0xBE9B0959FFD0779B) int GET_BLIP_INFO_ID_TYPE(Blip blip)l
extern _native64(0x4BA4E2553AFEDC2C) Entity GET_BLIP_INFO_ID_ENTITY_INDEX(Blip blip)l
extern _native64(0x9B6786E4C03DD382) Pickup GET_BLIP_INFO_ID_PICKUP_INDEX(Blip blip)l
extern _native64(0xBC8DBDCA2436F7E8) Blip GET_BLIP_FROM_ENTITY(Entity entity)l
extern _native64(0x46818D79B1F7499A) Blip ADD_BLIP_FOR_RADIUS(vector3 pos, float radius)l
extern _native64(0x5CDE92C702A8FCE7) Blip ADD_BLIP_FOR_ENTITY(Entity entity)l
extern _native64(0xBE339365C863BD36) Blip ADD_BLIP_FOR_PICKUP(Pickup pickup)l
extern _native64(0x5A039BB0BCA604B6) Blip ADD_BLIP_FOR_COORD(vector3 vec)l
extern _native64(0x72DD432F3CDFC0EE) void UNK_0x72DD432F3CDFC0EE(vector3 pos, float radius, int p4)l
extern _native64(0x60734CC207C9833C) void UNK_0x60734CC207C9833C(bool p0)l
extern _native64(0xAE2AF67E9D9AF65D) void SET_BLIP_COORDS(Blip blip, vector3 pos)l
extern _native64(0x586AFE3FF72D996E) vector3 GET_BLIP_COORDS(Blip blip)l
extern _native64(0xDF735600A4696DAF) void SET_BLIP_SPRITE(Blip blip, int spriteId)l
extern _native64(0x1FC877464A04FC4F) int GET_BLIP_SPRITE(Blip blip)l
extern _native64(0xEAA0FFE120D92784) void SET_BLIP_NAME_FROM_TEXT_FILE(Blip blip, const char* gxtEntry)l
extern _native64(0x127DE7B20C60A6A3) void SET_BLIP_NAME_TO_PLAYER_NAME(Blip blip, Player player)l
extern _native64(0x45FF974EEE1C8734) void SET_BLIP_ALPHA(Blip blip, int alpha)l
extern _native64(0x970F608F0EE6C885) int GET_BLIP_ALPHA(Blip blip)l
extern _native64(0x2AEE8F8390D2298C) void SET_BLIP_FADE(Blip blip, int opacity, int duration)l
extern _native64(0xF87683CDF73C3F6E) void SET_BLIP_ROTATION(Blip blip, int rotation)l
extern _native64(0xD3CD6FD297AE87CC) void SET_BLIP_FLASH_TIMER(Blip blip, int duration)l
extern _native64(0xAA51DB313C010A7E) void SET_BLIP_FLASH_INTERVAL(Blip blip, any p1)l
extern _native64(0x03D7FB09E75D6B7E) void SET_BLIP_COLOUR(Blip blip, int color)l
extern _native64(0x14892474891E09EB) void SET_BLIP_SECONDARY_COLOUR(Blip blip, FloatRGB colour)l
extern _native64(0xDF729E8D20CF7327) int GET_BLIP_COLOUR(Blip blip)l
extern _native64(0x729B5F1EFBC0AAEE) int GET_BLIP_HUD_COLOUR(Blip blip)l
extern _native64(0xDA5F8727EB75B926) bool IS_BLIP_SHORT_RANGE(Blip blip)l
extern _native64(0xE41CA53051197A27) bool IS_BLIP_ON_MINIMAP(Blip blip)l
extern _native64(0xDD2238F57B977751) bool UNK_0xDD2238F57B977751(any p0)l
extern _native64(0x54318C915D27E4CE) void UNK_0x54318C915D27E4CE(any p0, bool p1)l
extern _native64(0xE2590BC29220CEBB) void SET_BLIP_HIGH_DETAIL(Blip blip, bool toggle)l
extern _native64(0x24AC0137444F9FD5) void SET_BLIP_AS_MISSION_CREATOR_BLIP(Blip blip, bool toggle)l
extern _native64(0x26F49BF3381D933D) bool IS_MISSION_CREATOR_BLIP(Blip blip)l
extern _native64(0x5C90988E7C8E1AF4) Blip DISABLE_BLIP_NAME_FOR_VAR()l
extern _native64(0x4167EFE0527D706E) bool UNK_0x4167EFE0527D706E()l
extern _native64(0xF1A6C18B35BCADE6) void UNK_0xF1A6C18B35BCADE6(bool p0)l
extern _native64(0xB14552383D39CE3E) void SET_BLIP_FLASHES(Blip blip, bool toggle)l
extern _native64(0x2E8D9498C56DD0D1) void SET_BLIP_FLASHES_ALTERNATE(Blip blip, bool toggle)l
extern _native64(0xA5E41FD83AD6CEF0) bool IS_BLIP_FLASHING(Blip blip)l
extern _native64(0xBE8BE4FE60E27B72) void SET_BLIP_AS_SHORT_RANGE(Blip blip, bool toggle)l
extern _native64(0xD38744167B2FA257) void SET_BLIP_SCALE(Blip blip, float scale)l
extern _native64(0xAE9FC9EF6A9FAC79) void SET_BLIP_PRIORITY(Blip blip, int priority)l
extern _native64(0x9029B2F3DA924928) void SET_BLIP_DISPLAY(Blip blip, int displayId)l
extern _native64(0x234CDD44D996FD9A) void SET_BLIP_CATEGORY(Blip blip, int index)l
extern _native64(0x86A652570E5F25DD) void REMOVE_BLIP(Blip* blip)l
extern _native64(0x6F6F290102C02AB4) void SET_BLIP_AS_FRIENDLY(Blip blip, bool toggle)l
extern _native64(0x742D6FD43115AF73) void PULSE_BLIP(Blip blip)l
extern _native64(0xA3C0B359DCB848B6) void SHOW_NUMBER_ON_BLIP(Blip blip, int number)l
extern _native64(0x532CFF637EF80148) void HIDE_NUMBER_ON_BLIP(Blip blip)l
extern _native64(0x75A16C3DA34F1245) void UNK_0x75A16C3DA34F1245(any p0, bool p1)l
extern _native64(0x74513EA3E505181E) void _SET_BLIP_CHECKED(Blip blip, bool toggle)l
extern _native64(0x5FBCA48327B914DF) void SHOW_HEADING_INDICATOR_ON_BLIP(Blip blip, bool toggle)l
extern _native64(0xB81656BC81FE24D1) void _SET_BLIP_FRIENDLY(Blip blip, bool toggle)l
extern _native64(0x23C3EB807312F01A) void _SET_BLIP_FRIEND(Blip blip, bool toggle)l
extern _native64(0xDCFB5D4DB8BF367E) void UNK_0xDCFB5D4DB8BF367E(any p0, bool p1)l
extern _native64(0xC4278F70131BAA6D) void UNK_0xC4278F70131BAA6D(any p0, bool p1)l
extern _native64(0x2B6D467DAB714E8D) void _SET_BLIP_SHRINK(Blip blip, bool toggle)l
extern _native64(0x25615540D894B814) void UNK_0x25615540D894B814(any p0, bool p1)l
extern _native64(0xA6DB27D19ECBB7DA) bool DOES_BLIP_EXIST(Blip blip)l
extern _native64(0xA7E4E2D361C2627F) void SET_WAYPOINT_OFF()l
extern _native64(0xD8E694757BCEA8E9) void UNK_0xD8E694757BCEA8E9()l
extern _native64(0x81FA173F170560D1) void REFRESH_WAYPOINT()l
extern _native64(0x1DD1F58F493F1DA5) bool IS_WAYPOINT_ACTIVE()l
extern _native64(0xFE43368D2AA4F2FC) void SET_NEW_WAYPOINT(vector2 vector)l
extern _native64(0xB203913733F27884) void SET_BLIP_BRIGHT(Blip blip, bool toggle)l
extern _native64(0x13127EC3665E8EE1) void SET_BLIP_SHOW_CONE(Blip blip, bool toggle)l
extern _native64(0xC594B315EDF2D4AF) void UNK_0xC594B315EDF2D4AF(Ped ped)l
extern _native64(0x75A9A10948D1DEA6) any SET_MINIMAP_COMPONENT(int p0, bool p1, int p2)l
extern _native64(0x60E892BA4F5BDCA4) void UNK_0x60E892BA4F5BDCA4()l
extern _native64(0xDCD4EC3F419D02FA) Blip GET_MAIN_PLAYER_BLIP_ID()l
extern _native64(0x41350B4FC28E3941) void UNK_0x41350B4FC28E3941(bool p0)l
extern _native64(0x4B0311D3CDC4648F) void HIDE_LOADING_ON_FADE_THIS_FRAME()l
extern _native64(0x59E727A1C9D3E31A) void SET_RADAR_AS_INTERIOR_THIS_FRAME(Hash interior, vector2 vector, int z, int zoom)l
extern _native64(0xE81B7D2A3DAB2D81) void SET_RADAR_AS_EXTERIOR_THIS_FRAME()l
extern _native64(0x77E2DD177910E1CF) void _SET_PLAYER_BLIP_POSITION_THIS_FRAME(vector2 vector)l
extern _native64(0x9049FE339D5F6F6F) any UNK_0x9049FE339D5F6F6F()l
extern _native64(0x5FBAE526203990C9) void _DISABLE_RADAR_THIS_FRAME()l
extern _native64(0x20FE7FDFEEAD38C0) void UNK_0x20FE7FDFEEAD38C0()l
extern _native64(0x6D14BFDC33B34F55) void _CENTER_PLAYER_ON_RADAR_THIS_FRAME()l
extern _native64(0xC3B07BA00A83B0F1) void SET_WIDESCREEN_FORMAT(any p0)l
extern _native64(0x276B6CE369C33678) void DISPLAY_AREA_NAME(bool toggle)l
extern _native64(0x96DEC8D5430208B7) void DISPLAY_CASH(bool toggle)l
extern _native64(0x170F541E1CADD1DE) void UNK_0x170F541E1CADD1DE(bool p0)l
extern _native64(0x0772DF77852C2E30) void _SET_PLAYER_CASH_CHANGE(int cash, int bank)l
extern _native64(0xA5E78BA2B1331C55) void DISPLAY_AMMO_THIS_FRAME(bool display)l
extern _native64(0x73115226F4814E62) void DISPLAY_SNIPER_SCOPE_THIS_FRAME()l
extern _native64(0x719FF505F097FD20) void HIDE_HUD_AND_RADAR_THIS_FRAME()l
extern _native64(0xE67C6DFD386EA5E7) void UNK_0xE67C6DFD386EA5E7(bool p0)l
extern _native64(0xC2D15BEF167E27BC) void UNK_0xC2D15BEF167E27BC()l
extern _native64(0x95CF81BD06EE1887) void UNK_0x95CF81BD06EE1887()l
extern _native64(0xDD21B55DF695CD0A) void SET_MULTIPLAYER_BANK_CASH()l
extern _native64(0xC7C6789AA1CFEDD0) void REMOVE_MULTIPLAYER_BANK_CASH()l
extern _native64(0xFD1D220394BCB824) void SET_MULTIPLAYER_HUD_CASH(int p0, int p1)l
extern _native64(0x968F270E39141ECA) void REMOVE_MULTIPLAYER_HUD_CASH()l
extern _native64(0xD46923FC481CA285) void HIDE_HELP_TEXT_THIS_FRAME()l
extern _native64(0x960C9FF8F616E41C) void DISPLAY_HELP_TEXT_THIS_FRAME(const char* message, bool p1)l
extern _native64(0xEB354E5376BC81A7) void _SHOW_WEAPON_WHEEL(bool forcedShow)l
extern _native64(0x0AFC4AF510774B47) void UNK_0x0AFC4AF510774B47()l
extern _native64(0xA48931185F0536FE) Hash UNK_0xA48931185F0536FE()l
extern _native64(0x72C1056D678BB7D8) void UNK_0x72C1056D678BB7D8(Hash weaponHash)l
extern _native64(0xA13E93403F26C812) any UNK_0xA13E93403F26C812(any p0)l
extern _native64(0x14C9FDCC41F81F63) void UNK_0x14C9FDCC41F81F63(bool p0)l
extern _native64(0x5B440763A4C8D15B) void SET_GPS_FLAGS(int p0, float p1)l
extern _native64(0x21986729D6A3A830) void CLEAR_GPS_FLAGS()l
extern _native64(0x1EAC5F91BCBC5073) void UNK_0x1EAC5F91BCBC5073(bool p0)l
extern _native64(0x7AA5B4CE533C858B) void CLEAR_GPS_RACE_TRACK()l
extern _native64(0xDB34E8D56FC13B08) void UNK_0xDB34E8D56FC13B08(any p0, bool p1, bool p2)l
extern _native64(0x311438A071DD9B1A) void UNK_0x311438A071DD9B1A(any p0, any p1, any p2)l
extern _native64(0x900086F371220B6F) void UNK_0x900086F371220B6F(bool p0, any p1, any p2)l
extern _native64(0xE6DE0561D9232A64) void UNK_0xE6DE0561D9232A64()l
extern _native64(0x3D3D15AF7BCAAF83) void UNK_0x3D3D15AF7BCAAF83(any p0, bool p1, bool p2)l
extern _native64(0xA905192A6781C41B) void UNK_0xA905192A6781C41B(vector3 vec)l
extern _native64(0x3DDA37128DD1ACA8) void UNK_0x3DDA37128DD1ACA8(bool p0)l
extern _native64(0x67EEDEA1B9BAFD94) void UNK_0x67EEDEA1B9BAFD94()l
extern _native64(0xFF4FB7C8CDFA3DA7) void CLEAR_GPS_PLAYER_WAYPOINT()l
extern _native64(0x320D0E0D936A0E9B) void SET_GPS_FLASHES(bool toggle)l
extern _native64(0x7B21E0BB01E8224A) void UNK_0x7B21E0BB01E8224A(any p0)l
extern _native64(0xF2DD778C22B15BDA) void FLASH_MINIMAP_DISPLAY()l
extern _native64(0x6B1DE27EE78E6A19) void UNK_0x6B1DE27EE78E6A19(any p0)l
extern _native64(0x6AFDFB93754950C7) void TOGGLE_STEALTH_RADAR(bool toggle)l
extern _native64(0x1A5CD7752DD28CD3) void KEY_HUD_COLOUR(bool p0, any p1)l
extern _native64(0x5F28ECF5FC84772F) void SET_MISSION_NAME(bool p0, const char* name)l
extern _native64(0xE45087D85F468BC2) void UNK_0xE45087D85F468BC2(bool p0, any* p1)l
extern _native64(0x817B86108EB94E51) void UNK_0x817B86108EB94E51(bool p0, any* p1, any* p2, any* p3, any* p4, any* p5, any* p6, any* p7, any* p8)l
extern _native64(0x58FADDED207897DC) void SET_MINIMAP_BLOCK_WAYPOINT(bool toggle)l
extern _native64(0x9133955F1A2DA957) void _SET_NORTH_YANKTON_MAP(bool toggle)l
extern _native64(0xF8DEE0A5600CBB93) void _SET_MINIMAP_REVEALED(bool toggle)l
extern _native64(0xE0130B41D3CF4574) float UNK_0xE0130B41D3CF4574()l
extern _native64(0x6E31B91145873922) bool _IS_MINIMAP_AREA_REVEALED(vector2 vector, float radius)l
extern _native64(0x62E849B7EB28E770) void UNK_0x62E849B7EB28E770(bool p0)l
extern _native64(0x0923DBF87DFF735E) void UNK_0x0923DBF87DFF735E(vector3 vec)l
extern _native64(0x71BDB63DBAF8DA59) void UNK_0x71BDB63DBAF8DA59(any p0)l
extern _native64(0x35EDD5B2E3FF01C0) void UNK_0x35EDD5B2E3FF01C0()l
extern _native64(0x299FAEBB108AE05B) void LOCK_MINIMAP_ANGLE(int angle)l
extern _native64(0x8183455E16C42E3A) void UNLOCK_MINIMAP_ANGLE()l
extern _native64(0x1279E861A329E73F) void LOCK_MINIMAP_POSITION(vector2 vector)l
extern _native64(0x3E93E06DB8EF1F30) void UNLOCK_MINIMAP_POSITION()l
extern _native64(0xD201F3FF917A506D) void _SET_MINIMAP_ATTITUDE_INDICATOR_LEVEL(float altitude, bool p1)l
extern _native64(0x3F5CC444DCAAA8F2) void UNK_0x3F5CC444DCAAA8F2(any p0, any p1, bool p2)l
extern _native64(0x975D66A0BC17064C) void UNK_0x975D66A0BC17064C(any p0)l
extern _native64(0x06A320535F5F0248) void UNK_0x06A320535F5F0248(any p0)l
extern _native64(0x231C8F89D0539D8F) void _SET_RADAR_BIGMAP_ENABLED(bool toggleBigMap, bool showFullMap)l
extern _native64(0xBC4C9EA5391ECC0D) bool IS_HUD_COMPONENT_ACTIVE(int id)l
extern _native64(0xDD100EB17A94FF65) bool IS_SCRIPTED_HUD_COMPONENT_ACTIVE(int id)l
extern _native64(0xE374C498D8BADC14) void HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native64(0x09C0403ED9A751C2) bool UNK_0x09C0403ED9A751C2(any p0)l
extern _native64(0x6806C51AD12B83B8) void HIDE_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native64(0x0B4DF1FA60C0E664) void SHOW_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native64(0xA4DEDE28B1814289) void UNK_0xA4DEDE28B1814289()l
extern _native64(0x12782CE0A636E9F0) void RESET_RETICULE_VALUES()l
extern _native64(0x450930E616475D0D) void RESET_HUD_COMPONENT_VALUES(int id)l
extern _native64(0xAABB1F56E2A17CED) void SET_HUD_COMPONENT_POSITION(int id, vector2 vector)l
extern _native64(0x223CA69A8C4417FD) vector3 GET_HUD_COMPONENT_POSITION(int id)l
extern _native64(0xB57D8DD645CFA2CF) void CLEAR_REMINDER_MESSAGE()l
extern _native64(0xF9904D11F1ACBEC3) bool _GET_SCREEN_COORD_FROM_WORLD_COORD(vector3 world, float* screenX, float* screenY)l
extern _native64(0x523A590C1A3CC0D3) void UNK_0x523A590C1A3CC0D3()l
extern _native64(0xEE4C0E6DBC6F2C6F) void UNK_0xEE4C0E6DBC6F2C6F()l
extern _native64(0x9135584D09A3437E) any UNK_0x9135584D09A3437E()l
extern _native64(0x2432784ACA090DA4) bool UNK_0x2432784ACA090DA4(any p0)l
extern _native64(0x7679CC1BCEBE3D4C) void UNK_0x7679CC1BCEBE3D4C(any p0, float p1, float p2)l
extern _native64(0x784BA7E0ECEB4178) void UNK_0x784BA7E0ECEB4178(any p0, vector3 vec)l
extern _native64(0xB094BC1DB4018240) void UNK_0xB094BC1DB4018240(any p0, any p1, float p2, float p3)l
extern _native64(0x788E7FD431BD67F1) void UNK_0x788E7FD431BD67F1(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x50085246ABD3FEFA) void CLEAR_FLOATING_HELP(any p0, bool p1)l
extern _native64(0x6DD05E9D83EFA4C9) void _CREATE_MP_GAMER_TAG_COLOR(int headDisplayId, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, any p5, RGB colour)l
extern _native64(0x6E0EB3EB47C8D7AA) bool UNK_0x6E0EB3EB47C8D7AA()l
extern _native64(0xBFEFE3321A3F5015) int _CREATE_MP_GAMER_TAG(Ped ped, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, any p5)l
extern _native64(0x31698AA80E0223F8) void REMOVE_MP_GAMER_TAG(int gamerTagId)l
extern _native64(0x4E929E7A5796FD26) bool IS_MP_GAMER_TAG_ACTIVE(int gamerTagId)l
extern _native64(0x595B5178E412E199) bool ADD_TREVOR_RANDOM_MODIFIER(int gamerTagId)l
extern _native64(0x63BB75ABEDC1F6A0) void SET_MP_GAMER_TAG_VISIBILITY(int gamerTagId, int component, bool toggle)l
extern _native64(0xEE76FF7E6A0166B0) void UNK_0xEE76FF7E6A0166B0(int headDisplayId, bool p1)l
extern _native64(0xA67F9C46D612B6F1) void UNK_0xA67F9C46D612B6F1(int headDisplayId, bool p1)l
extern _native64(0x613ED644950626AE) void SET_MP_GAMER_TAG_COLOUR(int gamerTagId, int flag, int color)l
extern _native64(0x3158C77A7E888AB4) void _SET_MP_GAMER_TAG_HEALTH_BAR_COLOR(int headDisplayId, int color)l
extern _native64(0xD48FE545CD46F857) void SET_MP_GAMER_TAG_ALPHA(int gamerTagId, int component, int alpha)l
extern _native64(0xCF228E2AA03099C3) void SET_MP_GAMER_TAG_WANTED_LEVEL(int gamerTagId, int wantedlvl)l
extern _native64(0xDEA2B8283BAA3944) void SET_MP_GAMER_TAG_NAME(int gamerTagId, const char* string)l
extern _native64(0xEB709A36958ABE0D) bool UNK_0xEB709A36958ABE0D(int gamerTagId)l
extern _native64(0x7B7723747CCB55B6) void UNK_0x7B7723747CCB55B6(int gamerTagId, const char* string)l
extern _native64(0x01A358D9128B7A86) any UNK_0x01A358D9128B7A86()l
extern _native64(0x97D47996FC48CBAD) int GET_CURRENT_WEBSITE_ID()l
extern _native64(0xE3B05614DCE1D014) any UNK_0xE3B05614DCE1D014(any p0)l
extern _native64(0xB99C4E4D9499DF29) void UNK_0xB99C4E4D9499DF29(bool p0)l
extern _native64(0xAF42195A42C63BBA) any UNK_0xAF42195A42C63BBA()l
extern _native64(0x7B1776B3B53F8D74) void SET_WARNING_MESSAGE(const char* entryLine1, int instructionalKey, const char* entryLine2, bool p3, any p4, any* p5, any* p6, bool background)l
extern _native64(0xDC38CC1E35B6A5D7) void _SET_WARNING_MESSAGE_2(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, any p5, any* p6, any* p7, bool background)l
extern _native64(0x701919482C74B5AB) void _SET_WARNING_MESSAGE_3(const char* entryHeader, const char* entryLine1, any instructionalKey, const char* entryLine2, bool p4, any p5, any p6, any* p7, any* p8, bool p9)l
extern _native64(0x0C5A80A9E096D529) bool UNK_0x0C5A80A9E096D529(any p0, any* p1, any p2, any p3, any p4, any p5)l
extern _native64(0xDAF87174BE7454FF) bool UNK_0xDAF87174BE7454FF(any p0)l
extern _native64(0x6EF54AB721DC6242) void UNK_0x6EF54AB721DC6242()l
extern _native64(0xE18B138FABC53103) bool IS_WARNING_MESSAGE_ACTIVE()l
extern _native64(0x7792424AA0EAC32E) void UNK_0x7792424AA0EAC32E()l
extern _native64(0x5354C5BA2EA868A4) void _SET_MAP_FULL_SCREEN(bool toggle)l
extern _native64(0x1EAE6DD17B7A5EFA) void UNK_0x1EAE6DD17B7A5EFA(any p0)l
extern _native64(0x551DF99658DB6EE8) any UNK_0x551DF99658DB6EE8(float p0, float p1, float p2)l
extern _native64(0x2708FC083123F9FF) void UNK_0x2708FC083123F9FF()l
extern _native64(0x1121BFA1A1A522A8) any UNK_0x1121BFA1A1A522A8()l
extern _native64(0x82CEDC33687E1F50) void UNK_0x82CEDC33687E1F50(bool p0)l
extern _native64(0x211C4EF450086857) void UNK_0x211C4EF450086857()l
extern _native64(0xBF4F34A85CA2970C) void UNK_0xBF4F34A85CA2970C()l
extern _native64(0xEF01D36B9C9D0C7B) void ACTIVATE_FRONTEND_MENU(Hash menuhash, bool Toggle_Pause, int component)l
extern _native64(0x10706DC6AD2D49C0) void RESTART_FRONTEND_MENU(Hash menuHash, int p1)l
extern _native64(0x2309595AD6145265) Hash _GET_CURRENT_FRONTEND_MENU()l
extern _native64(0xDF47FC56C71569CF) void SET_PAUSE_MENU_ACTIVE(bool toggle)l
extern _native64(0x6D3465A73092F0E6) void DISABLE_FRONTEND_THIS_FRAME()l
extern _native64(0xBA751764F0821256) void UNK_0xBA751764F0821256()l
extern _native64(0xCC3FDDED67BCFC63) void UNK_0xCC3FDDED67BCFC63()l
extern _native64(0x745711A75AB09277) void SET_FRONTEND_ACTIVE(bool active)l
extern _native64(0xB0034A223497FFCB) bool IS_PAUSE_MENU_ACTIVE()l
extern _native64(0x2F057596F2BD0061) any UNK_0x2F057596F2BD0061()l
extern _native64(0x272ACD84970869C5) int GET_PAUSE_MENU_STATE()l
extern _native64(0x5BFF36D6ED83E0AE) vector3 UNK_0x5BFF36D6ED83E0AE()l
extern _native64(0x1C491717107431C7) bool IS_PAUSE_MENU_RESTARTING()l
extern _native64(0x2162C446DFDF38FD) void _LOG_DEBUG_INFO(const char* p0)l
extern _native64(0x77F16B447824DA6C) void UNK_0x77F16B447824DA6C(any p0)l
extern _native64(0xCDCA26E80FAECB8F) void UNK_0xCDCA26E80FAECB8F()l
extern _native64(0xDD564BDD0472C936) void _ADD_FRONTEND_MENU_CONTEXT(Hash hash)l
extern _native64(0x444D8CF241EC25C5) void OBJECT_DECAL_TOGGLE(Hash hash)l
extern _native64(0x84698AB38D0C6636) bool UNK_0x84698AB38D0C6636(Hash hash)l
extern _native64(0x2A25ADC48F87841F) any UNK_0x2A25ADC48F87841F()l
extern _native64(0xDE03620F8703A9DF) any UNK_0xDE03620F8703A9DF()l
extern _native64(0x359AF31A4B52F5ED) any UNK_0x359AF31A4B52F5ED()l
extern _native64(0x13C4B962653A5280) any UNK_0x13C4B962653A5280()l
extern _native64(0xC8E1071177A23BE5) bool UNK_0xC8E1071177A23BE5(any* p0, any* p1, any* p2)l
extern _native64(0x4895BDEA16E7C080) void ENABLE_DEATHBLOOD_SEETHROUGH(bool p0)l
extern _native64(0xC78E239AC5B2DDB9) void UNK_0xC78E239AC5B2DDB9(bool p0, any p1, any p2)l
extern _native64(0xF06EBB91A81E09E3) void UNK_0xF06EBB91A81E09E3(bool p0)l
extern _native64(0x3BAB9A4E4F2FF5C7) any UNK_0x3BAB9A4E4F2FF5C7()l
extern _native64(0xEC9264727EEC0F28) void UNK_0xEC9264727EEC0F28()l
extern _native64(0x14621BB1DF14E2B2) void UNK_0x14621BB1DF14E2B2()l
extern _native64(0x66E7CB63C97B7D20) any UNK_0x66E7CB63C97B7D20()l
extern _native64(0x593FEAE1F73392D4) any UNK_0x593FEAE1F73392D4()l
extern _native64(0x4E3CD0EF8A489541) any UNK_0x4E3CD0EF8A489541()l
extern _native64(0xF284AC67940C6812) any UNK_0xF284AC67940C6812()l
extern _native64(0x2E22FEFA0100275E) any UNK_0x2E22FEFA0100275E()l
extern _native64(0x0CF54F20DE43879C) void UNK_0x0CF54F20DE43879C(any p0)l
extern _native64(0x36C1451A88A09630) void UNK_0x36C1451A88A09630(any* p0, any* p1)l
extern _native64(0x7E17BE53E1AAABAF) void UNK_0x7E17BE53E1AAABAF(any* p0, any* p1, any* p2)l
extern _native64(0xA238192F33110615) bool UNK_0xA238192F33110615(int* p0, int* p1, int* p2)l
extern _native64(0xEF4CED81CEBEDC6D) bool SET_USERIDS_UIHIDDEN(any p0, any* p1)l
extern _native64(0xCA6B2F7CE32AB653) bool UNK_0xCA6B2F7CE32AB653(any p0, any* p1, any p2)l
extern _native64(0x90A6526CF0381030) bool UNK_0x90A6526CF0381030(any p0, any* p1, any p2, any p3)l
extern _native64(0x24A49BEAF468DC90) bool UNK_0x24A49BEAF468DC90(any p0, any* p1, any p2, any p3, any p4)l
extern _native64(0x5FBD7095FE7AE57F) bool UNK_0x5FBD7095FE7AE57F(any p0, float* p1)l
extern _native64(0x8F08017F9D7C47BD) bool UNK_0x8F08017F9D7C47BD(any p0, any* p1, any p2)l
extern _native64(0x052991E59076E4E4) bool UNK_0x052991E59076E4E4(Hash p0, any* p1)l
extern _native64(0x5E62BE5DC58E9E06) void CLEAR_PED_IN_PAUSE_MENU()l
extern _native64(0xAC0BFBDC3BE00E14) void GIVE_PED_TO_PAUSE_MENU(Ped ped, int p1)l
extern _native64(0x3CA6050692BC61B0) void UNK_0x3CA6050692BC61B0(bool p0)l
extern _native64(0xECF128344E9FF9F1) void UNK_0xECF128344E9FF9F1(bool p0)l
extern _native64(0x805D7CBB36FD6C4C) void _SHOW_SOCIAL_CLUB_LEGAL_SCREEN()l
extern _native64(0xF13FE2A80C05C561) any UNK_0xF13FE2A80C05C561()l
extern _native64(0x6F72CD94F7B5B68C) int UNK_0x6F72CD94F7B5B68C()l
extern _native64(0x75D3691713C3B05A) void UNK_0x75D3691713C3B05A()l
extern _native64(0xD2B32BE3FC1626C6) void UNK_0xD2B32BE3FC1626C6()l
extern _native64(0x9E778248D6685FE0) void UNK_0x9E778248D6685FE0(const char* p0)l
extern _native64(0xC406BE343FC4B9AF) bool IS_SOCIAL_CLUB_ACTIVE()l
extern _native64(0x1185A8087587322C) void UNK_0x1185A8087587322C(bool p0)l
extern _native64(0x8817605C2BA76200) void UNK_0x8817605C2BA76200()l
extern _native64(0xB118AF58B5F332A1) bool _IS_TEXT_CHAT_ACTIVE()l
extern _native64(0x1AC8F4AD40E22127) void _ABORT_TEXT_CHAT()l
extern _native64(0x1DB21A44B09E8BA3) void _SET_TEXT_CHAT_UNK(bool p0)l
extern _native64(0xCEF214315D276FD1) void UNK_0xCEF214315D276FD1(bool p0)l
extern _native64(0xD30C50DF888D58B5) void _SET_PED_ENEMY_AI_BLIP(int pedHandle, bool showViewCones)l
extern _native64(0x15B8ECF844EE67ED) bool DOES_PED_HAVE_AI_BLIP(Ped ped)l
extern _native64(0xE52B8E7F85D39A08) void UNK_0xE52B8E7F85D39A08(Ped ped, int unk)l
extern _native64(0x3EED80DFF7325CAA) void HIDE_SPECIAL_ABILITY_LOCKON_OPERATION(any p0, bool p1)l
extern _native64(0x0C4BBF625CA98C4E) void UNK_0x0C4BBF625CA98C4E(Ped ped, bool p1)l
extern _native64(0x97C65887D4B37FA9) void _SET_AI_BLIP_MAX_DISTANCE(Ped ped, float p1)l
extern _native64(0x7CD934010E115C2C) any* UNK_0x7CD934010E115C2C(Ped ped)l
extern _native64(0x56176892826A4FE8) Blip UNK_0x56176892826A4FE8(Ped ped)l
extern _native64(0xA277800A9EAE340E) any UNK_0xA277800A9EAE340E()l
extern _native64(0x2632482FD6B9AB87) void UNK_0x2632482FD6B9AB87()l
extern _native64(0x808519373FD336A3) void _SET_DIRECTOR_MODE(bool toggle)l
extern _native64(0x04655F9D075D0AE5) void UNK_0x04655F9D075D0AE5(bool p0)l
#pragma endregion //}
#pragma region GRAPHICS //{
extern _native64(0x175B6BFC15CDD0C5) void SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(bool enabled)l
extern _native64(0x7FDFADE676AA3CB0) void DRAW_DEBUG_LINE(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native64(0xD8B9A8AC5608FF94) void DRAW_DEBUG_LINE_WITH_TWO_COLOURS(vector3 vec_1, vector3 vec_2, RGB colour_1, RGB colour_2, int alpha1, int alpha2)l
extern _native64(0xAAD68E1AB39DA632) void DRAW_DEBUG_SPHERE(vector3 vec, float radius, RGBA colour)l
extern _native64(0x083A2CA4F2E573BD) void DRAW_DEBUG_BOX(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native64(0x73B1189623049839) void DRAW_DEBUG_CROSS(vector3 vec, float size, RGBA colour)l
extern _native64(0x3903E216620488E8) void DRAW_DEBUG_TEXT(const char* text, vector3 vec, RGBA colour)l
extern _native64(0xA3BB2E9555C05A8F) void DRAW_DEBUG_TEXT_2D(const char* text, vector3 vec, RGBA colour)l
extern _native64(0x6B7256074AE34680) void DRAW_LINE(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native64(0xAC26716048436851) void DRAW_POLY(vector3 vec_1, vector3 vec_2, vector3 vec_3, RGBA colour)l
extern _native64(0xD3A9971CADAC7252) void DRAW_BOX(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native64(0x23BA6B0C2AD7B0D3) void UNK_0x23BA6B0C2AD7B0D3(bool p0)l
extern _native64(0x1DD2139A9A20DCE8) any UNK_0x1DD2139A9A20DCE8()l
extern _native64(0x90A78ECAA4E78453) any UNK_0x90A78ECAA4E78453()l
extern _native64(0x0A46AF8A78DC5E0A) void UNK_0x0A46AF8A78DC5E0A()l
extern _native64(0x4862437A486F91B0) bool UNK_0x4862437A486F91B0(any* p0, any p1, any p2, any p3)l
extern _native64(0x1670F8D05056F257) int UNK_0x1670F8D05056F257(any* p0)l
extern _native64(0x7FA5D82B8F58EC06) any UNK_0x7FA5D82B8F58EC06()l
extern _native64(0x5B0316762AFD4A64) any UNK_0x5B0316762AFD4A64()l
extern _native64(0x346EF3ECAAAB149E) void UNK_0x346EF3ECAAAB149E()l
extern _native64(0xA67C35C56EB1BD9D) any UNK_0xA67C35C56EB1BD9D()l
extern _native64(0x0D6CA79EEEBD8CA3) any UNK_0x0D6CA79EEEBD8CA3()l
extern _native64(0xD801CC02177FA3F1) void UNK_0xD801CC02177FA3F1()l
extern _native64(0x1BBC135A4D25EDDE) void UNK_0x1BBC135A4D25EDDE(bool p0)l
extern _native64(0x3DEC726C25A11BAC) any UNK_0x3DEC726C25A11BAC(int p0)l
extern _native64(0x0C0C4E81E1AC60A0) any UNK_0x0C0C4E81E1AC60A0()l
extern _native64(0x759650634F07B6B4) bool UNK_0x759650634F07B6B4(any p0)l
extern _native64(0xCB82A0BF0E3E3265) any UNK_0xCB82A0BF0E3E3265(any p0)l
extern _native64(0x6A12D88881435DCA) void UNK_0x6A12D88881435DCA()l
extern _native64(0x1072F115DAB0717E) void UNK_0x1072F115DAB0717E(bool p0, bool p1)l
extern _native64(0x34D23450F028B0BF) int GET_MAXIMUM_NUMBER_OF_PHOTOS()l
extern _native64(0xDC54A7AF8B3A14EF) any UNK_0xDC54A7AF8B3A14EF()l
extern _native64(0x473151EBC762C6DA) int UNK_0x473151EBC762C6DA()l
extern _native64(0x2A893980E96B659A) any UNK_0x2A893980E96B659A(any p0)l
extern _native64(0xF5BED327CEA362B1) any UNK_0xF5BED327CEA362B1(any p0)l
extern _native64(0x4AF92ACD3141D96C) void UNK_0x4AF92ACD3141D96C()l
extern _native64(0xE791DF1F73ED2C8B) any UNK_0xE791DF1F73ED2C8B(any p0)l
extern _native64(0xEC72C258667BE5EA) any UNK_0xEC72C258667BE5EA(any p0)l
extern _native64(0x40AFB081F8ADD4EE) int _RETURN_TWO(any p0)l
extern _native64(0xF49E9A9716A04595) void _DRAW_LIGHT_WITH_RANGE_AND_SHADOW(vector3 vec, RGB colour, float range, float intensity, float shadow)l
extern _native64(0xF2A1B2771A01DBD4) void DRAW_LIGHT_WITH_RANGE(vector3 pos, RGB color, float range, float intensity)l
extern _native64(0xD0F64B265C8C8B33) void DRAW_SPOT_LIGHT(vector3 pos, vector3 dir, RGB color, float distance, float brightness, float roundness, float radius, float falloff)l
extern _native64(0x5BCA583A583194DB) void _DRAW_SPOT_LIGHT_WITH_SHADOW(vector3 pos, vector3 dir, RGB color, float distance, float brightness, float roundness, float radius, float falloff, float shadow)l
extern _native64(0xC9B18B4619F48F7B) void UNK_0xC9B18B4619F48F7B(float p0)l
extern _native64(0xDEADC0DEDEADC0DE) void UNK_0xDEADC0DEDEADC0DE(Object object)l
extern _native64(0x28477EC23D892089) void DRAW_MARKER(int type, vector3 pos, vector3 dir, vector3 rot, vector3 scale, RGBA colour, bool bobUpAndDown, bool faceCamera, int p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts)l
extern _native64(0x0134F0835AB6BFCB) int CREATE_CHECKPOINT(int type, vector3 pos1, vector3 pos2, float radius, RGBA colour, int reserved)l
extern _native64(0x4B5B4DA5D79F1943) void UNK_0x4B5B4DA5D79F1943(int checkpoint, float p0)l
extern _native64(0x2707AAE9D9297D89) void SET_CHECKPOINT_CYLINDER_HEIGHT(int checkpoint, float nearHeight, float farHeight, float radius)l
extern _native64(0x7167371E8AD747F7) void SET_CHECKPOINT_RGBA(int checkpoint, RGBA colour)l
extern _native64(0xB9EA40907C680580) void _SET_CHECKPOINT_ICON_RGBA(int checkpoint, RGBA colour)l
extern _native64(0xF51D36185993515D) void UNK_0xF51D36185993515D(int checkpoint, vector3 pos, vector3 unk)l
extern _native64(0x615D3925E87A3B26) void UNK_0x615D3925E87A3B26(int checkpoint)l
extern _native64(0xF5ED37F54CD4D52E) void DELETE_CHECKPOINT(int checkpoint)l
extern _native64(0x22A249A53034450A) void UNK_0x22A249A53034450A(bool p0)l
extern _native64(0xDC459CFA0CCE245B) void UNK_0xDC459CFA0CCE245B(bool p0)l
extern _native64(0xDFA2EF8E04127DD5) void REQUEST_STREAMED_TEXTURE_DICT(const char* textureDict, bool p1)l
extern _native64(0x0145F696AAAAD2E4) bool HAS_STREAMED_TEXTURE_DICT_LOADED(const char* textureDict)l
extern _native64(0xBE2CACCF5A8AA805) void SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(const char* textureDict)l
extern _native64(0x3A618A217E5154F0) void DRAW_RECT(vector2 vector, Size size, RGBA colour)l
extern _native64(0xC6372ECD45D73BCD) void UNK_0xC6372ECD45D73BCD(bool p0)l
extern _native64(0x61BB1D9B3A95D802) void _SET_2D_LAYER(int layer)l
extern _native64(0xB8A850F20A067EB6) void _SET_SCREEN_DRAW_POSITION(int x, int y)l
extern _native64(0xE3A3DB414A373DAB) void _SCREEN_DRAW_POSITION_END()l
extern _native64(0xF5A2C681787E579D) void _SCREEN_DRAW_POSITION_RATIO(vector2 vector, float p2, float p3)l
extern _native64(0x6DD8F5AA635EB4B2) void UNK_0x6DD8F5AA635EB4B2(float p0, float p1, any* p2, any* p3)l
extern _native64(0xBAF107B6BB2C97F0) float GET_SAFE_ZONE_SIZE()l
extern _native64(0xE7FFAE5EBF23D890) void DRAW_SPRITE(const char* textureDict, const char* textureName, vector2 screen, Size size, float heading, RGBA colour)l
extern _native64(0x9CD43EEE12BF4DD0) any ADD_ENTITY_ICON(Entity entity, const char* icon)l
extern _native64(0xE0E8BEECCA96BA31) void SET_ENTITY_ICON_VISIBILITY(Entity entity, bool toggle)l
extern _native64(0x1D5F595CCAE2E238) void SET_ENTITY_ICON_COLOR(Entity entity, RGBA colour)l
extern _native64(0xAA0008F3BBB8F416) void SET_DRAW_ORIGIN(vector3 vec, any p3)l
extern _native64(0xFF0B610F6BE0D7AF) void CLEAR_DRAW_ORIGIN()l
extern _native64(0x845BAD77CC770633) void ATTACH_TV_AUDIO_TO_ENTITY(Entity entity)l
extern _native64(0x113D2C5DC57E1774) void SET_TV_AUDIO_FRONTEND(bool toggle)l
extern _native64(0xB66064452270E8F1) int LOAD_MOVIE_MESH_SET(const char* movieMeshSetName)l
extern _native64(0xEB119AA014E89183) void RELEASE_MOVIE_MESH_SET(int movieMeshSet)l
extern _native64(0x9B6E70C5CEEF4EEB) any UNK_0x9B6E70C5CEEF4EEB(any p0)l
extern _native64(0x888D57E407E63624) void GET_SCREEN_RESOLUTION(int* x, int* y)l
extern _native64(0x873C9F3104101DD3) void _GET_ACTIVE_SCREEN_RESOLUTION(int* x, int* y)l
extern _native64(0xF1307EF624A80D87) float _GET_ASPECT_RATIO(bool b)l
extern _native64(0xB2EBE8CBC58B90E9) any UNK_0xB2EBE8CBC58B90E9()l
extern _native64(0x30CF4BDA4FCB1905) bool GET_IS_WIDESCREEN()l
extern _native64(0x84ED31191CC5D2C9) bool GET_IS_HIDEF()l
extern _native64(0xEFABC7722293DA7C) void UNK_0xEFABC7722293DA7C()l
extern _native64(0x18F621F7A5B1F85D) void SET_NIGHTVISION(bool toggle)l
extern _native64(0x35FB78DC42B7BD21) any UNK_0x35FB78DC42B7BD21()l
extern _native64(0x2202A3F42C8E5F79) bool _IS_NIGHTVISION_INACTIVE()l
extern _native64(0xEF398BEEE4EF45F9) void UNK_0xEF398BEEE4EF45F9(bool p0)l
extern _native64(0xE787BF1C5CF823C9) void SET_NOISEOVERIDE(bool toggle)l
extern _native64(0xCB6A7C3BB17A0C67) void SET_NOISINESSOVERIDE(float value)l
extern _native64(0x34E82F05DF2974F5) bool GET_SCREEN_COORD_FROM_WORLD_COORD(vector3 world, float* screenX, float* screenY)l
extern _native64(0x35736EE65BD00C11) vector3 GET_TEXTURE_RESOLUTION(const char* textureDict, const char* textureName)l
extern _native64(0xE2892E7E55D7073A) void UNK_0xE2892E7E55D7073A(float p0)l
extern _native64(0x0AB84296FED9CFC6) void SET_FLASH(float p0, float p1, float fadeIn, float duration, float fadeOut)l
extern _native64(0x3669F1B198DCAA4F) void UNK_0x3669F1B198DCAA4F()l
extern _native64(0x1268615ACE24D504) void _SET_BLACKOUT(bool enable)l
extern _native64(0xC35A6D07C93802B2) void UNK_0xC35A6D07C93802B2()l
extern _native64(0xE2C9439ED45DEA60) Object CREATE_TRACKED_POINT()l
extern _native64(0x164ECBB3CF750CB0) any SET_TRACKED_POINT_INFO(Object point, vector3 vec, float radius)l
extern _native64(0xC45CCDAAC9221CA8) bool IS_TRACKED_POINT_VISIBLE(Object point)l
extern _native64(0xB25DC90BAD56CA42) void DESTROY_TRACKED_POINT(Object point)l
extern _native64(0xBE197EAA669238F4) any UNK_0xBE197EAA669238F4(any p0, any p1, any p2, any p3)l
extern _native64(0x61F95E5BB3E0A8C6) void UNK_0x61F95E5BB3E0A8C6(any p0)l
extern _native64(0xAE51BC858F32BA66) void UNK_0xAE51BC858F32BA66(any p0, float p1, float p2, float p3, float p4)l
extern _native64(0x649C97D52332341A) void UNK_0x649C97D52332341A(any p0)l
extern _native64(0x2C42340F916C5930) any UNK_0x2C42340F916C5930(any p0)l
extern _native64(0x14FC5833464340A8) void UNK_0x14FC5833464340A8()l
extern _native64(0x0218BA067D249DEA) void UNK_0x0218BA067D249DEA()l
extern _native64(0x1612C45F9E3E0D44) void UNK_0x1612C45F9E3E0D44()l
extern _native64(0x5DEBD9C4DC995692) void UNK_0x5DEBD9C4DC995692()l
extern _native64(0x6D955F6A9E0295B1) void UNK_0x6D955F6A9E0295B1(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x302C91AB2D477F7E) void UNK_0x302C91AB2D477F7E()l
extern _native64(0x03FC694AE06C5A20) void UNK_0x03FC694AE06C5A20()l
extern _native64(0xD2936CAB8B58FCBD) void UNK_0xD2936CAB8B58FCBD(any p0, bool p1, float p2, float p3, float p4, float p5, bool p6, float p7)l
extern _native64(0x5F0F3F56635809EF) void UNK_0x5F0F3F56635809EF(float p0)l
extern _native64(0x5E9DAF5A20F15908) void UNK_0x5E9DAF5A20F15908(float p0)l
extern _native64(0x36F6626459D91457) void UNK_0x36F6626459D91457(float p0)l
extern _native64(0x80ECBC0C856D3B0B) void _SET_FAR_SHADOWS_SUPPRESSED(bool toggle)l
extern _native64(0x25FC3E33A31AD0C9) void UNK_0x25FC3E33A31AD0C9(bool p0)l
extern _native64(0xB11D94BC55F41932) void UNK_0xB11D94BC55F41932(const char* p0)l
extern _native64(0x27CB772218215325) void UNK_0x27CB772218215325()l
extern _native64(0x6DDBF9DFFC4AC080) void UNK_0x6DDBF9DFFC4AC080(bool p0)l
extern _native64(0xD39D13C9FEBF0511) void UNK_0xD39D13C9FEBF0511(bool p0)l
extern _native64(0x02AC28F3A01FA04A) any UNK_0x02AC28F3A01FA04A(float p0)l
extern _native64(0x0AE73D8DF3A762B2) void UNK_0x0AE73D8DF3A762B2(bool p0)l
extern _native64(0xA51C4B86B71652AE) void UNK_0xA51C4B86B71652AE(bool p0)l
extern _native64(0x312342E1A4874F3F) void UNK_0x312342E1A4874F3F(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8)l
extern _native64(0x2485D34E50A22E84) void UNK_0x2485D34E50A22E84(float p0, float p1, float p2)l
extern _native64(0x12995F2E53FFA601) void UNK_0x12995F2E53FFA601(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)l
extern _native64(0xDBAA5EC848BA2D46) void UNK_0xDBAA5EC848BA2D46(any p0, any p1)l
extern _native64(0xC0416B061F2B7E5E) void UNK_0xC0416B061F2B7E5E(bool p0)l
extern _native64(0xB1BB03742917A5D6) void UNK_0xB1BB03742917A5D6(int type, vector3 Pos, float p4, RGBA colour)l
extern _native64(0x9CFDD90B2B844BF7) void UNK_0x9CFDD90B2B844BF7(float p0, float p1, float p2, float p3, float p4)l
extern _native64(0x06F761EA47C1D3ED) void UNK_0x06F761EA47C1D3ED(bool p0)l
extern _native64(0xA4819F5E23E2FFAD) any UNK_0xA4819F5E23E2FFAD()l
extern _native64(0xA4664972A9B8F8BA) int UNK_0xA4664972A9B8F8BA(any p0)l
extern _native64(0x7E08924259E08CE0) void SET_SEETHROUGH(bool toggle)l
extern _native64(0x44B80ABAB9D80BD3) bool _IS_SEETHROUGH_ACTIVE()l
extern _native64(0xD7D0B00177485411) void UNK_0xD7D0B00177485411(any p0, float p1)l
extern _native64(0xB3C641F3630BF6DA) void UNK_0xB3C641F3630BF6DA(float p0)l
extern _native64(0xE59343E9E96529E7) any UNK_0xE59343E9E96529E7()l
extern _native64(0xE63D7C6EECECB66B) void UNK_0xE63D7C6EECECB66B(bool p0)l
extern _native64(0xE3E2C1B4C59DBC77) void UNK_0xE3E2C1B4C59DBC77(any p0)l
extern _native64(0xA328A24AAA6B7FDC) bool _TRANSITION_TO_BLURRED(float transitionTime)l
extern _native64(0xEFACC8AEF94430D5) bool _TRANSITION_FROM_BLURRED(float transitionTime)l
extern _native64(0xDE81239437E8C5A8) void UNK_0xDE81239437E8C5A8()l
extern _native64(0x5CCABFFCA31DDE33) float IS_PARTICLE_FX_DELAYED_BLINK()l
extern _native64(0x7B226C785A52A0A9) any UNK_0x7B226C785A52A0A9()l
extern _native64(0xDFC252D8A3E15AB7) void _SET_FROZEN_RENDERING_DISABLED(bool enabled)l
extern _native64(0xEB3DAC2C86001E5E) bool UNK_0xEB3DAC2C86001E5E()l
extern _native64(0xE1C8709406F2C41C) void UNK_0xE1C8709406F2C41C()l
extern _native64(0x851CD923176EBA7C) void UNK_0x851CD923176EBA7C()l
extern _native64(0xBA3D65906822BED5) void UNK_0xBA3D65906822BED5(bool p0, bool p1, float p2, float p3, float p4, float p5)l
extern _native64(0x7AC24EAB6D74118D) bool UNK_0x7AC24EAB6D74118D(bool p0)l
extern _native64(0xBCEDB009461DA156) any UNK_0xBCEDB009461DA156()l
extern _native64(0x27FEB5254759CDE3) bool UNK_0x27FEB5254759CDE3(const char* textureDict, bool p1)l
extern _native64(0x25129531F77B9ED3) int START_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, vector3 Pos, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0xF56B8137DF10135D) bool _START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(const char* effectName, vector3 Pos, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x0E7E72961BA18619) bool START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, vector3 offset, vector3 rot, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0xA41B6A43642AC2CF) bool _START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(const char* effectName, Ped ped, vector3 offset, vector3 rot, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0x0D53A3B8DA0809D2) bool START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, vector3 offset, vector3 rot, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0xC95EB1DB6E92113D) bool _START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2(const char* effectName, Entity entity, vector3 offset, vector3 rot, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native64(0x26143A59EF48B262) void SET_PARTICLE_FX_NON_LOOPED_COLOUR(FloatRGB colour)l
extern _native64(0x77168D722C58B2FC) void SET_PARTICLE_FX_NON_LOOPED_ALPHA(float alpha)l
extern _native64(0x8CDE909A0370BB3A) void UNK_0x8CDE909A0370BB3A(bool p0)l
extern _native64(0xE184F4F0DC5910E7) int START_PARTICLE_FX_LOOPED_AT_COORD(const char* effectName, vector3 vec, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11)l
extern _native64(0xF28DA9F38CD1787C) int START_PARTICLE_FX_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, vector3 Offset, vector3 Rot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x1AE42C1660FD6517) int START_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0xC6EB449E33977F0B) int _START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x6F60E89A7B64EE1D) int _START_PARTICLE_FX_LOOPED_ON_ENTITY_2(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0xDDE23F30CC5A0F03) int _START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE_2(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native64(0x8F75998877616996) void STOP_PARTICLE_FX_LOOPED(int ptfxHandle, bool p1)l
extern _native64(0xC401503DFE8D53CF) void REMOVE_PARTICLE_FX(int ptfxHandle, bool p1)l
extern _native64(0xB8FEAEEBCC127425) void REMOVE_PARTICLE_FX_FROM_ENTITY(Entity entity)l
extern _native64(0xDD19FA1C6D657305) void REMOVE_PARTICLE_FX_IN_RANGE(vector3 vec, float radius)l
extern _native64(0x74AFEF0D2E1E409B) bool DOES_PARTICLE_FX_LOOPED_EXIST(int ptfxHandle)l
extern _native64(0xF7DDEBEC43483C43) void SET_PARTICLE_FX_LOOPED_OFFSETS(int ptfxHandle, vector3 vec, vector3 rot)l
extern _native64(0x5F0C4B5B1C393BE2) void SET_PARTICLE_FX_LOOPED_EVOLUTION(int ptfxHandle, const char* propertyName, float amount, bool Id)l
extern _native64(0x7F8F65877F88783B) void SET_PARTICLE_FX_LOOPED_COLOUR(int ptfxHandle, FloatRGB colour, bool p4)l
extern _native64(0x726845132380142E) void SET_PARTICLE_FX_LOOPED_ALPHA(int ptfxHandle, float alpha)l
extern _native64(0xB44250AAA456492D) void SET_PARTICLE_FX_LOOPED_SCALE(int ptfxHandle, float scale)l
extern _native64(0xDCB194B85EF7B541) void _SET_PARTICLE_FX_LOOPED_RANGE(int ptfxHandle, float range)l
extern _native64(0xEEC4047028426510) void SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(bool p0)l
extern _native64(0xACEE6F360FC1F6B6) void SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(any p0, bool p1)l
extern _native64(0x96EF97DAEB89BEF5) void SET_PARTICLE_FX_SHOOTOUT_BOAT(any p0)l
extern _native64(0x5F6DF3D92271E8A1) void SET_PARTICLE_FX_BLOOD_SCALE(bool p0)l
extern _native64(0xD821490579791273) void ENABLE_CLOWN_BLOOD_VFX(bool toggle)l
extern _native64(0x9DCE1F0F78260875) void ENABLE_ALIEN_BLOOD_VFX(bool Toggle)l
extern _native64(0x27E32866E9A5C416) void UNK_0x27E32866E9A5C416(float p0)l
extern _native64(0xBB90E12CAC1DAB25) void UNK_0xBB90E12CAC1DAB25(float p0)l
extern _native64(0xCA4AE345A153D573) void UNK_0xCA4AE345A153D573(bool p0)l
extern _native64(0x54E22EA2C1956A8D) void UNK_0x54E22EA2C1956A8D(float p0)l
extern _native64(0x949F397A288B28B3) void UNK_0x949F397A288B28B3(float p0)l
extern _native64(0x9B079E5221D984D3) void UNK_0x9B079E5221D984D3(bool p0)l
extern _native64(0x6C38AF3693A69A91) void _USE_PARTICLE_FX_ASSET_NEXT_CALL(const char* name)l
extern _native64(0xEA1E2D93F6F75ED9) void _SET_PARTICLE_FX_ASSET_OLD_TO_NEW(const char* oldAsset, const char* newAsset)l
extern _native64(0x89C8553DD3274AAE) void _RESET_PARTICLE_FX_ASSET_OLD_TO_NEW(const char* name)l
extern _native64(0xA46B73FAA3460AE1) void UNK_0xA46B73FAA3460AE1(bool p0)l
extern _native64(0xF78B803082D4386F) void UNK_0xF78B803082D4386F(float p0)l
extern _native64(0x9C30613D50A6ADEF) void WASH_DECALS_IN_RANGE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x5B712761429DBC14) void WASH_DECALS_FROM_VEHICLE(Vehicle vehicle, float p1)l
extern _native64(0xD77EDADB0420E6E0) void FADE_DECALS_IN_RANGE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x5D6B2D4830A67C62) void REMOVE_DECALS_IN_RANGE(vector3 vec, float range)l
extern _native64(0xCCF71CBDDF5B6CB9) void REMOVE_DECALS_FROM_OBJECT(Object obj)l
extern _native64(0xA6F6F70FDC6D144C) void REMOVE_DECALS_FROM_OBJECT_FACING(Object obj, vector3 vec)l
extern _native64(0xE91F1B65F2B48D57) void REMOVE_DECALS_FROM_VEHICLE(Vehicle vehicle)l
extern _native64(0xB302244A1839BDAD) int ADD_DECAL(int decalType, vector3 pos, float p4, float p5, float p6, float p7, float p8, float p9, Size size, FloatRGB Coef, float opacity, float timeout, bool p17, bool p18, bool p19)l
extern _native64(0x4F5212C7AD880DF8) any ADD_PETROL_DECAL(vector3 vec, float groundLvl, float width, float transparency)l
extern _native64(0x99AC7F0D8B9C893D) void UNK_0x99AC7F0D8B9C893D(float p0)l
extern _native64(0x967278682CB6967A) void UNK_0x967278682CB6967A(any p0, any p1, any p2, any p3)l
extern _native64(0x0A123435A26C36CD) void UNK_0x0A123435A26C36CD()l
extern _native64(0xED3F346429CCD659) void REMOVE_DECAL(int decal)l
extern _native64(0xC694D74949CAFD0C) bool IS_DECAL_ALIVE(int decal)l
extern _native64(0x323F647679A09103) float GET_DECAL_WASH_LEVEL(int decal)l
extern _native64(0xD9454B5752C857DC) void UNK_0xD9454B5752C857DC()l
extern _native64(0x27CFB1B1E078CB2D) void UNK_0x27CFB1B1E078CB2D()l
extern _native64(0x4B5CFC83122DF602) void UNK_0x4B5CFC83122DF602()l
extern _native64(0x2F09F7976C512404) bool UNK_0x2F09F7976C512404(vector3 Coord, float p3)l
extern _native64(0x8A35C742130C6080) void UNK_0x8A35C742130C6080(any p0, any* p1, any* p2)l
extern _native64(0xB7ED70C49521A61D) void UNK_0xB7ED70C49521A61D(any p0)l
extern _native64(0x84C8D7C2D30D3280) void MOVE_VEHICLE_DECALS(any p0, any p1)l
extern _native64(0x428BDCB9DA58DA53) bool _ADD_CLAN_DECAL_TO_VEHICLE(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, any p13, int alpha)l
extern _native64(0xD2300034310557E4) void UNK_0xD2300034310557E4(Vehicle vehicle, any p1)l
extern _native64(0xFE26117A5841B2FF) int UNK_0xFE26117A5841B2FF(Vehicle vehicle, any p1)l
extern _native64(0x060D935D3981A275) bool _DOES_VEHICLE_HAVE_DECAL(Vehicle vehicle, any p1)l
extern _native64(0x0E4299C549F0D1F1) void UNK_0x0E4299C549F0D1F1(bool p0)l
extern _native64(0x02369D5C8A51FDCF) void UNK_0x02369D5C8A51FDCF(bool p0)l
extern _native64(0x46D1A61A21F566FC) void UNK_0x46D1A61A21F566FC(float p0)l
extern _native64(0x2A2A52824DB96700) void UNK_0x2A2A52824DB96700(any* p0)l
extern _native64(0x1600FD8CF72EBC12) void UNK_0x1600FD8CF72EBC12(float p0)l
extern _native64(0xEFB55E7C25D3B3BE) void UNK_0xEFB55E7C25D3B3BE()l
extern _native64(0xA44FF770DFBC5DAE) void UNK_0xA44FF770DFBC5DAE()l
extern _native64(0xC9F98AC1884E73A2) void DISABLE_VEHICLE_DISTANTLIGHTS(bool toggle)l
extern _native64(0x03300B57FCAC6DDB) void UNK_0x03300B57FCAC6DDB(bool p0)l
extern _native64(0x98EDF76A7271E4F2) void UNK_0x98EDF76A7271E4F2()l
extern _native64(0xAEEDAD1420C65CC0) void _SET_FORCE_PED_FOOTSTEPS_TRACKS(bool toggle)l
extern _native64(0x4CC7F0FEA5283FE0) void _SET_FORCE_VEHICLE_TRAILS(bool toggle)l
extern _native64(0xD7021272EB0A451E) void UNK_0xD7021272EB0A451E(const char* p0)l
extern _native64(0x2C933ABF17A1DF41) void SET_TIMECYCLE_MODIFIER(const char* modifierName)l
extern _native64(0x82E7FFCD5B2326B3) void SET_TIMECYCLE_MODIFIER_STRENGTH(float strength)l
extern _native64(0x3BCF567485E1971C) void SET_TRANSITION_TIMECYCLE_MODIFIER(const char* modifierName, float transition)l
extern _native64(0x1CBA05AE7BD7EE05) void UNK_0x1CBA05AE7BD7EE05(float p0)l
extern _native64(0x0F07E7745A236711) void CLEAR_TIMECYCLE_MODIFIER()l
extern _native64(0xFDF3D97C674AFB66) int GET_TIMECYCLE_MODIFIER_INDEX()l
extern _native64(0x459FD2C8D0AB78BC) any UNK_0x459FD2C8D0AB78BC()l
extern _native64(0x58F735290861E6B4) void PUSH_TIMECYCLE_MODIFIER()l
extern _native64(0x3C8938D7D872211E) void POP_TIMECYCLE_MODIFIER()l
extern _native64(0xBBF327DED94E4DEB) void UNK_0xBBF327DED94E4DEB(const char* p0)l
extern _native64(0xBDEB86F4D5809204) void UNK_0xBDEB86F4D5809204(float p0)l
extern _native64(0xBF59707B3E5ED531) void UNK_0xBF59707B3E5ED531(const char* p0)l
extern _native64(0x1A8E2C8B9CF4549C) void UNK_0x1A8E2C8B9CF4549C(any* p0, any* p1)l
extern _native64(0x15E33297C3E8DC60) void UNK_0x15E33297C3E8DC60(any p0)l
extern _native64(0x5096FD9CCB49056D) void UNK_0x5096FD9CCB49056D(any* p0)l
extern _native64(0x92CCC17A7A2285DA) void UNK_0x92CCC17A7A2285DA()l
extern _native64(0xBB0527EC6341496D) any UNK_0xBB0527EC6341496D()l
extern _native64(0x2C328AF17210F009) void UNK_0x2C328AF17210F009(float p0)l
extern _native64(0x2BF72AD5B41AA739) void UNK_0x2BF72AD5B41AA739()l
extern _native64(0x11FE353CF9733E6F) int REQUEST_SCALEFORM_MOVIE(const char* scaleformName)l
extern _native64(0xC514489CFB8AF806) int REQUEST_SCALEFORM_MOVIE_INSTANCE(const char* scaleformName)l
extern _native64(0xBD06C611BB9048C2) int _REQUEST_SCALEFORM_MOVIE_INTERACTIVE(const char* scaleformName)l
extern _native64(0x85F01B8D5B90570E) bool HAS_SCALEFORM_MOVIE_LOADED(int scaleformHandle)l
extern _native64(0x0C1C5D756FB5F337) bool _HAS_NAMED_SCALEFORM_MOVIE_LOADED(const char* scaleformName)l
extern _native64(0x8217150E1217EBFD) bool HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(int scaleformHandle)l
extern _native64(0x1D132D614DD86811) void SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(int* scaleformHandle)l
extern _native64(0x6D8EB211944DCE08) void SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(int scaleform, bool toggle)l
extern _native64(0x54972ADAF0294A93) void DRAW_SCALEFORM_MOVIE(int scaleformHandle, vector2 vector, Size size, RGBA colour, int unk)l
extern _native64(0x0DF606929C105BE1) void DRAW_SCALEFORM_MOVIE_FULLSCREEN(int scaleform, RGBA colour, int unk)l
extern _native64(0xCF537FDE4FBD4CE5) void DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(int scaleform1, int scaleform2, RGBA colour)l
extern _native64(0x87D51D72255D4E78) void DRAW_SCALEFORM_MOVIE_3D(int scaleform, vector3 pos, vector3 rot, float p7, float p8, float p9, vector3 scale, any p13)l
extern _native64(0x1CE592FDC749D6F5) void _DRAW_SCALEFORM_MOVIE_3D_NON_ADDITIVE(int scaleform, vector3 pos, vector3 rot, float p7, float p8, float p9, vector3 scale, any p13)l
extern _native64(0xFBD96D87AC96D533) void CALL_SCALEFORM_MOVIE_METHOD(int scaleform, const char* method)l
extern _native64(0xD0837058AE2E4BEE) void _CALL_SCALEFORM_MOVIE_FUNCTION_FLOAT_PARAMS(int scaleform, const char* functionName, float param1, float param2, float param3, float param4, float param5)l
extern _native64(0x51BC1ED3CC44E8F7) void _CALL_SCALEFORM_MOVIE_FUNCTION_STRING_PARAMS(int scaleform, const char* functionName, const char* param1, const char* param2, const char* param3, const char* param4, const char* param5)l
extern _native64(0xEF662D8D57E290B1) void _CALL_SCALEFORM_MOVIE_FUNCTION_MIXED_PARAMS(int scaleform, const char* functionName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, const char* stringParam1, const char* stringParam2, const char* stringParam3, const char* stringParam4, const char* stringParam5)l
extern _native64(0x98C494FD5BDFBFD5) bool _PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT(int hudComponent, const char* functionName)l
extern _native64(0xF6E48914C7A8694E) bool _PUSH_SCALEFORM_MOVIE_FUNCTION(int scaleform, const char* functionName)l
extern _native64(0xAB58C27C2E6123C6) bool _PUSH_SCALEFORM_MOVIE_FUNCTION_N(const char* functionName)l
extern _native64(0xB9449845F73F5E9C) bool UNK_0xB9449845F73F5E9C(const char* functionName)l
extern _native64(0xC6796A8FFA375E53) void _POP_SCALEFORM_MOVIE_FUNCTION_VOID()l
extern _native64(0xC50AA39A577AF886) any _POP_SCALEFORM_MOVIE_FUNCTION()l
extern _native64(0x768FF8961BA904D6) bool UNK_0x768FF8961BA904D6(any funcData)l
extern _native64(0x2DE7EFA66B906036) int UNK_0x2DE7EFA66B906036(any funcData)l
extern _native64(0xE1E258829A885245) const char* SITTING_TV(int scaleform)l
extern _native64(0xC3D0841A0CC546A6) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(int value)l
extern _native64(0xD69736AAE04DB51A) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(float value)l
extern _native64(0xC58424BA936EB458) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(bool value)l
extern _native64(0x80338406F3475E55) void BEGIN_TEXT_COMMAND_SCALEFORM_STRING(const char* componentType)l
extern _native64(0x362E2D3FE93A9959) void END_TEXT_COMMAND_SCALEFORM_STRING()l
extern _native64(0xAE4E8157D9ECF087) void _END_TEXT_COMMAND_SCALEFORM_STRING_2()l
extern _native64(0xBA7148484BD90365) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(const char* value)l
extern _native64(0xE83A3E3557A56640) void UNK_0xE83A3E3557A56640(const char* p0)l
extern _native64(0x5E657EF1099EDD65) bool UNK_0x5E657EF1099EDD65(any p0)l
extern _native64(0xEC52C631A1831C03) void UNK_0xEC52C631A1831C03(any p0)l
extern _native64(0x9304881D6F6537EA) void _REQUEST_HUD_SCALEFORM(int hudComponent)l
extern _native64(0xDF6E5987D2B4D140) bool _HAS_HUD_SCALEFORM_LOADED(int hudComponent)l
extern _native64(0xF44A5456AC3F4F97) void UNK_0xF44A5456AC3F4F97(any p0)l
extern _native64(0xD1C7CB175E012964) bool UNK_0xD1C7CB175E012964(int scaleformHandle)l
extern _native64(0xBAABBB23EB6E484E) void SET_TV_CHANNEL(int channel)l
extern _native64(0xFC1E275A90D39995) int GET_TV_CHANNEL()l
extern _native64(0x2982BF73F66E9DDC) void SET_TV_VOLUME(float volume)l
extern _native64(0x2170813D3DD8661B) float GET_TV_VOLUME()l
extern _native64(0xFDDC2B4ED3C69DF0) void DRAW_TV_CHANNEL(vector2 Pos, Size Scale, float rotation, RGBA colour)l
extern _native64(0xF7B38B8305F1FE8B) void UNK_0xF7B38B8305F1FE8B(int p0, const char* p1, bool p2)l
extern _native64(0x2201C576FACAEBE8) void UNK_0x2201C576FACAEBE8(any p0, const char* p1, any p2)l
extern _native64(0xBEB3D46BB7F043C0) void UNK_0xBEB3D46BB7F043C0(any p0)l
extern _native64(0x0AD973CA1E077B60) bool _LOAD_TV_CHANNEL(Hash tvChannel)l
extern _native64(0x74C180030FDE4B69) void UNK_0x74C180030FDE4B69(bool p0)l
extern _native64(0xD1C55B110E4DF534) void UNK_0xD1C55B110E4DF534(any p0)l
extern _native64(0x873FA65C778AD970) void ENABLE_MOVIE_SUBTITLES(bool toggle)l
extern _native64(0xD3A10FC7FD8D98CD) bool UNK_0xD3A10FC7FD8D98CD()l
extern _native64(0xF1CEA8A4198D8E9A) bool UNK_0xF1CEA8A4198D8E9A(const char* p0)l
extern _native64(0x98C4FE6EC34154CA) bool UNK_0x98C4FE6EC34154CA(const char* p0, Ped ped, int p2, vector3 pos)l
extern _native64(0x7A42B2E236E71415) void UNK_0x7A42B2E236E71415()l
extern _native64(0x108BE26959A9D9BB) void UNK_0x108BE26959A9D9BB(bool p0)l
extern _native64(0xA356990E161C9E65) void UNK_0xA356990E161C9E65(bool p0)l
extern _native64(0x1C4FC5752BCD8E48) void UNK_0x1C4FC5752BCD8E48(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12)l
extern _native64(0x5CE62918F8D703C7) void UNK_0x5CE62918F8D703C7(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)l
extern _native64(0x2206BF9A37B7F724) void _START_SCREEN_EFFECT(const char* effectName, int duration, bool looped)l
extern _native64(0x068E835A1D0DC0E3) void _STOP_SCREEN_EFFECT(const char* effectName)l
extern _native64(0x36AD3E690DA5ACEB) bool _GET_SCREEN_EFFECT_IS_ACTIVE(const char* effectName)l
extern _native64(0xB4EDDC19532BFB85) void _STOP_ALL_SCREEN_EFFECTS()l
extern _native64(0xD2209BE128B5418C) void UNK_0xD2209BE128B5418C(const char* graphicsName)l
#pragma endregion //}
#pragma region STATS //{
extern _native64(0xEB0A72181D4AA4AD) any STAT_CLEAR_SLOT_FOR_RELOAD(int statSlot)l
extern _native64(0xA651443F437B1CE6) bool STAT_LOAD(int p0)l
extern _native64(0xE07BCA305B82D2FD) bool STAT_SAVE(int p0, bool p1, int p2)l
extern _native64(0x5688585E6D563CD8) void UNK_0x5688585E6D563CD8(any p0)l
extern _native64(0xA1750FFAFA181661) bool STAT_LOAD_PENDING(any p0)l
extern _native64(0x7D3A583856F2C5AC) any STAT_SAVE_PENDING()l
extern _native64(0xBBB6AD006F1BBEA3) any STAT_SAVE_PENDING_OR_REQUESTED()l
extern _native64(0x49A49BED12794D70) any STAT_DELETE_SLOT(any p0)l
extern _native64(0x0D0A9F0E7BD91E3C) bool STAT_SLOT_IS_LOADED(any p0)l
extern _native64(0x7F2C4CDF2E82DF4C) bool UNK_0x7F2C4CDF2E82DF4C(any p0)l
extern _native64(0xE496A53BA5F50A56) any UNK_0xE496A53BA5F50A56(any p0)l
extern _native64(0xF434A10BA01C37D0) void UNK_0xF434A10BA01C37D0(bool p0)l
extern _native64(0x7E6946F68A38B74F) bool UNK_0x7E6946F68A38B74F(any p0)l
extern _native64(0xA8733668D1047B51) void UNK_0xA8733668D1047B51(any p0)l
extern _native64(0xECB41AC6AB754401) any UNK_0xECB41AC6AB754401()l
extern _native64(0x9B4BD21D69B1E609) void UNK_0x9B4BD21D69B1E609()l
extern _native64(0xC0E0D686DDFC6EAE) any UNK_0xC0E0D686DDFC6EAE()l
extern _native64(0xB3271D7AB655B441) bool STAT_SET_INT(Hash statName, int value, bool save)l
extern _native64(0x4851997F37FE9B3C) bool STAT_SET_FLOAT(Hash statName, float value, bool save)l
extern _native64(0x4B33C4243DE0C432) bool STAT_SET_BOOL(Hash statName, bool value, bool save)l
extern _native64(0x17695002FD8B2AE0) bool STAT_SET_GXT_LABEL(Hash statName, const char* value, bool save)l
extern _native64(0x2C29BFB64F4FCBE4) bool STAT_SET_DATE(Hash statName, any* value, int numFields, bool save)l
extern _native64(0xA87B2335D12531D7) bool STAT_SET_STRING(Hash statName, const char* value, bool save)l
extern _native64(0xDB283FDE680FE72E) bool STAT_SET_POS(Hash statName, vector3 vec, bool save)l
extern _native64(0x7BBB1B54583ED410) bool STAT_SET_MASKED_INT(Hash statName, any p1, any p2, int p3, bool save)l
extern _native64(0x8CDDF1E452BABE11) bool STAT_SET_USER_ID(Hash statName, const char* value, bool save)l
extern _native64(0xC2F84B7F9C4D0C61) bool STAT_SET_CURRENT_POSIX_TIME(Hash statName, bool p1)l
extern _native64(0x767FBC2AC802EF3D) bool STAT_GET_INT(Hash statHash, int* outValue, int p2)l
extern _native64(0xD7AE6C9C9C6AC54C) bool STAT_GET_FLOAT(Hash statHash, float* outValue, any p2)l
extern _native64(0x11B5E6D2AE73F48E) bool STAT_GET_BOOL(Hash statHash, bool* outValue, any p2)l
extern _native64(0x8B0FACEFC36C824B) bool STAT_GET_DATE(Hash statHash, any* p1, any p2, any p3)l
extern _native64(0xE50384ACC2C3DB74) const char* STAT_GET_STRING(Hash statHash, int p1)l
extern _native64(0x350F82CCB186AA1B) bool STAT_GET_POS(any p0, any* p1, any* p2, any* p3, any p4)l
extern _native64(0x655185A06D9EEAAB) bool STAT_GET_MASKED_INT(any p0, any* p1, any p2, any p3, any p4)l
extern _native64(0x2365C388E393BBE2) const char* STAT_GET_USER_ID(any p0)l
extern _native64(0x5473D4195058B2E4) const char* STAT_GET_LICENSE_PLATE(Hash statName)l
extern _native64(0x69FF13266D7296DA) bool STAT_SET_LICENSE_PLATE(Hash statName, const char* str)l
extern _native64(0x9B5A68C6489E9909) void STAT_INCREMENT(Hash statName, float value)l
extern _native64(0x5A556B229A169402) bool UNK_0x5A556B229A169402()l
extern _native64(0xB1D2BB1E1631F5B1) bool UNK_0xB1D2BB1E1631F5B1()l
extern _native64(0xBED9F5693F34ED17) bool UNK_0xBED9F5693F34ED17(Hash statName, int p1, float* outValue)l
extern _native64(0x26D7399B9587FE89) void UNK_0x26D7399B9587FE89(int p0)l
extern _native64(0xA78B8FA58200DA56) void UNK_0xA78B8FA58200DA56(int p0)l
extern _native64(0xE0E854F5280FB769) int STAT_GET_NUMBER_OF_DAYS(Hash statName)l
extern _native64(0xF2D4B2FE415AAFC3) int STAT_GET_NUMBER_OF_HOURS(Hash statName)l
extern _native64(0x7583B4BE4C5A41B5) int STAT_GET_NUMBER_OF_MINUTES(Hash statName)l
extern _native64(0x2CE056FF3723F00B) int STAT_GET_NUMBER_OF_SECONDS(Hash statName)l
extern _native64(0x68F01422BE1D838F) void _STAT_SET_PROFILE_SETTING(int profileSetting, int value)l
extern _native64(0xF4D8E7AC2A27758C) int UNK_0xF4D8E7AC2A27758C(int p0)l
extern _native64(0x94F12ABF9C79E339) int UNK_0x94F12ABF9C79E339(int p0)l
extern _native64(0x80C75307B1C42837) Hash _GET_PSTAT_BOOL_HASH(int index, bool spStat, bool charStat, int character)l
extern _native64(0x61E111E323419E07) Hash _GET_PSTAT_INT_HASH(int index, bool spStat, bool charStat, int character)l
extern _native64(0xC4BB08EE7907471E) Hash _GET_TUPSTAT_BOOL_HASH(int index, bool spStat, bool charStat, int character)l
extern _native64(0xD16C2AD6B8E32854) Hash _GET_TUPSTAT_INT_HASH(int index, bool spStat, bool charStat, int character)l
extern _native64(0xBA52FF538ED2BC71) Hash _GET_NGSTAT_BOOL_HASH(int index, bool spStat, bool charStat, int character, const char* section)l
extern _native64(0x2B4CDCA6F07FF3DA) Hash _GET_NGSTAT_INT_HASH(int index, bool spStat, bool charStat, int character, const char* section)l
extern _native64(0x10FE3F1B79F9B071) bool STAT_GET_BOOL_MASKED(Hash statName, int mask, int p2)l
extern _native64(0x5BC62EC1937B9E5B) bool STAT_SET_BOOL_MASKED(Hash statName, bool value, int mask, bool save)l
extern _native64(0x5009DFD741329729) void UNK_0x5009DFD741329729(const char* p0, any p1)l
extern _native64(0x93054C88E6AA7C44) void PLAYSTATS_NPC_INVITE(any* p0)l
extern _native64(0x46F917F6B4128FE4) void PLAYSTATS_AWARD_XP(any p0, any p1, any p2)l
extern _native64(0xC7F2DE41D102BFB4) void PLAYSTATS_RANK_UP(any p0)l
extern _native64(0x098760C7461724CD) void UNK_0x098760C7461724CD()l
extern _native64(0xA071E0ED98F91286) void UNK_0xA071E0ED98F91286(any p0, any p1)l
extern _native64(0xC5BE134EC7BA96A0) void UNK_0xC5BE134EC7BA96A0(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xC19A2925C34D2231) void PLAYSTATS_MISSION_STARTED(any* p0, any p1, any p2, bool p3)l
extern _native64(0x7C4BB33A8CED7324) void PLAYSTATS_MISSION_OVER(any* p0, any p1, any p2, bool p3, bool p4, bool p5)l
extern _native64(0xC900596A63978C1D) void PLAYSTATS_MISSION_CHECKPOINT(any* p0, any p1, any p2, any p3)l
extern _native64(0x71862B1D855F32E1) void UNK_0x71862B1D855F32E1(any* p0, any p1, any p2, any p3)l
extern _native64(0x121FB4DDDC2D5291) void UNK_0x121FB4DDDC2D5291(any p0, any p1, any p2, float p3)l
extern _native64(0x9C375C315099DDE4) void PLAYSTATS_RACE_CHECKPOINT(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x6DEE77AFF8C21BD1) bool UNK_0x6DEE77AFF8C21BD1(any* p0, any* p1)l
extern _native64(0xBC80E22DED931E3D) void PLAYSTATS_MATCH_STARTED(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x176852ACAAC173D1) void PLAYSTATS_SHOP_ITEM(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x1CAE5D2E3F9A07F0) void UNK_0x1CAE5D2E3F9A07F0(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xAFC7E5E075A96F46) void _PLAYSTATS_AMBIENT_MISSION_CRATE_CREATED(float p0, float p1, float p2)l
extern _native64(0xCB00196B31C39EB1) void UNK_0xCB00196B31C39EB1(any p0, any p1, any p2, any p3)l
extern _native64(0x2B69F5074C894811) void UNK_0x2B69F5074C894811(any p0, any p1, any p2, any p3)l
extern _native64(0x7EEC2A316C250073) void UNK_0x7EEC2A316C250073(any p0, any p1, any p2)l
extern _native64(0xADDD1C754E2E2914) void UNK_0xADDD1C754E2E2914(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9)l
extern _native64(0x79AB33F0FBFAC40C) void UNK_0x79AB33F0FBFAC40C(any p0)l
extern _native64(0xDDF24D535060F811) void PLAYSTATS_WEBSITE_VISITED(Hash scaleformHash, int p1)l
extern _native64(0x0F71DE29AB2258F1) void PLAYSTATS_FRIEND_ACTIVITY(any p0, any p1)l
extern _native64(0x69DEA3E9DB727B4C) void PLAYSTATS_ODDJOB_DONE(any p0, any p1, any p2)l
extern _native64(0xBA739D6D5A05D6E7) void PLAYSTATS_PROP_CHANGE(any p0, any p1, any p2, any p3)l
extern _native64(0x34B973047A2268B9) void PLAYSTATS_CLOTH_CHANGE(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0xE95C8A1875A02CA4) void UNK_0xE95C8A1875A02CA4(any p0, any p1, any p2)l
extern _native64(0x6058665D72302D3F) void PLAYSTATS_CHEAT_APPLIED(const char* cheat)l
extern _native64(0xF8C54A461C3E11DC) void UNK_0xF8C54A461C3E11DC(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0xF5BB8DAC426A52C0) void UNK_0xF5BB8DAC426A52C0(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0xA736CF7FB7C5BFF4) void UNK_0xA736CF7FB7C5BFF4(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0x14E0B2D1AD1044E0) void UNK_0x14E0B2D1AD1044E0(any* p0, any* p1, any* p2, any* p3)l
extern _native64(0x90D0622866E80445) void UNK_0x90D0622866E80445(int p0, const char* p1)l
extern _native64(0x5DA3A8DE8CB6226F) void UNK_0x5DA3A8DE8CB6226F(int time)l
extern _native64(0xD1032E482629049E) void UNK_0xD1032E482629049E(bool p0)l
extern _native64(0xF4FF020A08BC8863) void UNK_0xF4FF020A08BC8863(any p0, any p1)l
extern _native64(0x46326E13DA4E0546) void UNK_0x46326E13DA4E0546(any* p0)l
extern _native64(0x117B45156D7EFF2E) any LEADERBOARDS_GET_NUMBER_OF_COLUMNS(any p0, any p1)l
extern _native64(0xC4B5467A1886EA7E) any LEADERBOARDS_GET_COLUMN_ID(any p0, any p1, any p2)l
extern _native64(0xBF4FEF46DB7894D3) any LEADERBOARDS_GET_COLUMN_TYPE(any p0, any p1, any p2)l
extern _native64(0xA34CB6E6F0DF4A0B) any LEADERBOARDS_READ_CLEAR_ALL()l
extern _native64(0x7CCE5C737A665701) any LEADERBOARDS_READ_CLEAR(any p0, any p1, any p2)l
extern _native64(0xAC392C8483342AC2) bool LEADERBOARDS_READ_PENDING(any p0, any p1, any p2)l
extern _native64(0xA31FD15197B192BD) any UNK_0xA31FD15197B192BD()l
extern _native64(0x2FB19228983E832C) bool LEADERBOARDS_READ_SUCCESSFUL(any p0, any p1, any p2)l
extern _native64(0x918B101666F9CB83) bool LEADERBOARDS2_READ_FRIENDS_BY_ROW(any* p0, any* p1, any p2, bool p3, any p4, any p5)l
extern _native64(0xC30713A383BFBF0E) bool LEADERBOARDS2_READ_BY_HANDLE(any* p0, any* p1)l
extern _native64(0xA9CDB1E3F0A49883) bool LEADERBOARDS2_READ_BY_ROW(any* p0, any* p1, any p2, any* p3, any p4, any* p5, any p6)l
extern _native64(0xBA2C7DB0C129449A) bool LEADERBOARDS2_READ_BY_RANK(any* p0, any p1, any p2)l
extern _native64(0x5CE587FB5A42C8C4) bool LEADERBOARDS2_READ_BY_RADIUS(any* p0, any p1, any* p2)l
extern _native64(0x7EEC7E4F6984A16A) bool LEADERBOARDS2_READ_BY_SCORE_INT(any* p0, any p1, any p2)l
extern _native64(0xE662C8B759D08F3C) bool LEADERBOARDS2_READ_BY_SCORE_FLOAT(any* p0, float p1, any p2)l
extern _native64(0xC38DC1E90D22547C) bool UNK_0xC38DC1E90D22547C(any* p0, any* p1, any* p2)l
extern _native64(0xF1AE5DCDBFCA2721) bool UNK_0xF1AE5DCDBFCA2721(any* p0, any* p1, any* p2)l
extern _native64(0xA0F93D5465B3094D) bool UNK_0xA0F93D5465B3094D(any* p0)l
extern _native64(0x71B008056E5692D6) void UNK_0x71B008056E5692D6()l
extern _native64(0x34770B9CE0E03B91) bool UNK_0x34770B9CE0E03B91(any p0, any* p1)l
extern _native64(0x88578F6EC36B4A3A) any UNK_0x88578F6EC36B4A3A(any p0, any p1)l
extern _native64(0x38491439B6BA7F7D) float UNK_0x38491439B6BA7F7D(any p0, any p1)l
extern _native64(0xAE2206545888AE49) bool LEADERBOARDS2_WRITE_DATA(any* p0)l
extern _native64(0x0BCA1D2C47B0D269) void UNK_0x0BCA1D2C47B0D269(any p0, any p1, float p2)l
extern _native64(0x2E65248609523599) void UNK_0x2E65248609523599(any p0, any p1, any p2)l
extern _native64(0xB9BB18E2C40142ED) bool LEADERBOARDS_CACHE_DATA_ROW(any* p0)l
extern _native64(0xD4B02A6B476E1FDC) void LEADERBOARDS_CLEAR_CACHE_DATA()l
extern _native64(0x8EC74CEB042E7CFF) void UNK_0x8EC74CEB042E7CFF(any p0)l
extern _native64(0x9C51349BE6CDFE2C) bool LEADERBOARDS_GET_CACHE_EXISTS(any p0)l
extern _native64(0xF04C1C27DA35F6C8) any LEADERBOARDS_GET_CACHE_TIME(any p0)l
extern _native64(0x58A651CD201D89AD) any UNK_0x58A651CD201D89AD(any p0)l
extern _native64(0x9120E8DBA3D69273) bool LEADERBOARDS_GET_CACHE_DATA_ROW(any p0, any p1, any* p2)l
extern _native64(0x11FF1C80276097ED) void UNK_0x11FF1C80276097ED(any p0, any p1, any p2)l
extern _native64(0x30A6614C1F7799B8) void UNK_0x30A6614C1F7799B8(any p0, float p1, any p2)l
extern _native64(0x6483C25849031C4F) void UNK_0x6483C25849031C4F(any p0, any p1, any p2, any* p3)l
extern _native64(0x5EAD2BF6484852E4) bool UNK_0x5EAD2BF6484852E4()l
extern _native64(0xC141B8917E0017EC) void UNK_0xC141B8917E0017EC()l
extern _native64(0xB475F27C6A994D65) void UNK_0xB475F27C6A994D65()l
extern _native64(0xF1A1803D3476F215) void UNK_0xF1A1803D3476F215(int value)l
extern _native64(0x38BAAA5DD4C9D19F) void UNK_0x38BAAA5DD4C9D19F(int value)l
extern _native64(0x55384438FC55AD8E) void UNK_0x55384438FC55AD8E(int value)l
extern _native64(0x723C1CE13FBFDB67) void UNK_0x723C1CE13FBFDB67(any p0, any p1)l
extern _native64(0x0D01D20616FC73FB) void UNK_0x0D01D20616FC73FB(any p0, any p1)l
extern _native64(0x428EAF89E24F6C36) void UNK_0x428EAF89E24F6C36(any p0, float p1)l
extern _native64(0x047CBED6F6F8B63C) void UNK_0x047CBED6F6F8B63C()l
extern _native64(0xC980E62E33DF1D5C) bool UNK_0xC980E62E33DF1D5C(any* p0, any* p1)l
extern _native64(0x6F361B8889A792A3) void UNK_0x6F361B8889A792A3()l
extern _native64(0xC847B43F369AC0B5) void UNK_0xC847B43F369AC0B5()l
extern _native64(0xA5C80D8E768A9E66) bool UNK_0xA5C80D8E768A9E66(any* p0)l
extern _native64(0x9A62EC95AE10E011) any UNK_0x9A62EC95AE10E011()l
extern _native64(0x4C89FE2BDEB3F169) any UNK_0x4C89FE2BDEB3F169()l
extern _native64(0xC6E0E2616A7576BB) any UNK_0xC6E0E2616A7576BB()l
extern _native64(0x5BD5F255321C4AAF) any UNK_0x5BD5F255321C4AAF(any p0)l
extern _native64(0xDEAAF77EB3687E97) any UNK_0xDEAAF77EB3687E97(any p0, any* p1)l
extern _native64(0xC70DDCE56D0D3A99) any UNK_0xC70DDCE56D0D3A99()l
extern _native64(0x886913BBEACA68C1) any UNK_0x886913BBEACA68C1(any* p0)l
extern _native64(0x4FEF53183C3C6414) any UNK_0x4FEF53183C3C6414()l
extern _native64(0x567384DFA67029E6) any UNK_0x567384DFA67029E6()l
extern _native64(0x3270F67EED31FBC1) bool UNK_0x3270F67EED31FBC1(any p0, any* p1, any* p2)l
extern _native64(0xCE5AA445ABA8DEE0) any UNK_0xCE5AA445ABA8DEE0(any* p0)l
extern _native64(0x98E2BC1CA26287C3) void UNK_0x98E2BC1CA26287C3()l
extern _native64(0x629526ABA383BCAA) void UNK_0x629526ABA383BCAA()l
extern _native64(0xB3DA2606774A8E2D) any UNK_0xB3DA2606774A8E2D()l
extern _native64(0xDAC073C7901F9E15) void UNK_0xDAC073C7901F9E15(any p0)l
extern _native64(0xF6792800AC95350D) void UNK_0xF6792800AC95350D(any p0)l
extern _native64(0x848B66100EE33B05) void UNK_0x848B66100EE33B05(const void* data)l
#pragma endregion //}
#pragma region BRAIN //{
extern _native64(0x4EE5367468A65CCC) void ADD_SCRIPT_TO_RANDOM_PED(const char* name, Hash model, float p2, float p3)l
extern _native64(0x0BE84C318BA6EC22) void REGISTER_OBJECT_SCRIPT_BRAIN(const char* scriptName, Hash objectName, int p2, float p3, int p4, int p5)l
extern _native64(0xCCBA154209823057) bool IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Object object)l
extern _native64(0x3CDC7136613284BD) void REGISTER_WORLD_POINT_SCRIPT_BRAIN(any* p0, float p1, any p2)l
extern _native64(0xC5042CC6F5E3D450) bool IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE()l
extern _native64(0x67AA4D73F0CFA86B) void ENABLE_SCRIPT_BRAIN_SET(int brainSet)l
extern _native64(0x14D8518E9760F08F) void DISABLE_SCRIPT_BRAIN_SET(int brainSet)l
extern _native64(0x0B40ED49D7D6FF84) void UNK_0x0B40ED49D7D6FF84()l
extern _native64(0x4D953DF78EBF8158) void UNK_0x4D953DF78EBF8158()l
extern _native64(0x6D6840CEE8845831) void UNK_0x6D6840CEE8845831(const char* action)l
extern _native64(0x6E91B04E08773030) void UNK_0x6E91B04E08773030(const char* action)l
#pragma endregion //}
#pragma region MOBILE //{
extern _native64(0xA4E8E696C532FBC7) void CREATE_MOBILE_PHONE(int phoneType)l
extern _native64(0x3BC861DF703E5097) void DESTROY_MOBILE_PHONE()l
extern _native64(0xCBDD322A73D6D932) void SET_MOBILE_PHONE_SCALE(float scale)l
extern _native64(0xBB779C0CA917E865) void SET_MOBILE_PHONE_ROTATION(vector3 rot, any p3)l
extern _native64(0x1CEFB61F193070AE) void GET_MOBILE_PHONE_ROTATION(vector3* rotation, any p1)l
extern _native64(0x693A5C6D6734085B) void SET_MOBILE_PHONE_POSITION(vector3 pos)l
extern _native64(0x584FDFDA48805B86) void GET_MOBILE_PHONE_POSITION(vector3* position)l
extern _native64(0xF511F759238A5122) void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(bool toggle)l
extern _native64(0xC4E2813898C97A4B) bool CAN_PHONE_BE_SEEN_ON_SCREEN()l
extern _native64(0x95C9E72F3D7DEC9B) void _MOVE_FINGER(int direction)l
extern _native64(0x44E44169EF70138E) void _SET_PHONE_LEAN(bool Toggle)l
extern _native64(0xFDE8F069C542D126) void CELL_CAM_ACTIVATE(bool p0, bool p1)l
extern _native64(0x015C49A93E3E086E) void _DISABLE_PHONE_THIS_FRAME(bool toggle)l
extern _native64(0xA2CCBE62CD4C91A4) void UNK_0xA2CCBE62CD4C91A4(int* toggle)l
extern _native64(0x1B0B4AEED5B9B41C) void UNK_0x1B0B4AEED5B9B41C(float p0)l
extern _native64(0x53F4892D18EC90A4) void UNK_0x53F4892D18EC90A4(float p0)l
extern _native64(0x3117D84EFA60F77B) void UNK_0x3117D84EFA60F77B(float p0)l
extern _native64(0x15E69E2802C24B8D) void UNK_0x15E69E2802C24B8D(float p0)l
extern _native64(0xAC2890471901861C) void UNK_0xAC2890471901861C(float p0)l
extern _native64(0xD6ADE981781FCA09) void UNK_0xD6ADE981781FCA09(float p0)l
extern _native64(0xF1E22DC13F5EEBAD) void UNK_0xF1E22DC13F5EEBAD(float p0)l
extern _native64(0x466DA42C89865553) void UNK_0x466DA42C89865553(float p0)l
extern _native64(0x439E9BC95B7E7FBE) bool CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Entity entity)l
extern _native64(0xB4A53E05F68B6FA1) void GET_MOBILE_PHONE_RENDER_ID(int* renderId)l
extern _native64(0xBD4D7EAF8A30F637) bool _NETWORK_SHOP_IS_ITEM_UNLOCKED(const char* name)l
extern _native64(0x247F0F73A182EA0B) bool _NETWORK_SHOP_IS_ITEM_UNLOCKED_HASH(Hash hash)l
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
extern _native64(0xC9853A2BE3DED1A6) any APP_GET_DELETED_FILE_STATUS()l
extern _native64(0x44151AEA95C8A003) bool APP_DELETE_APP_DATA(const char* appName)l
#pragma endregion //}
#pragma region TIME //{
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
extern _native64(0x8117E09A19EEF4D3) void _GET_UTC_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second)l
extern _native64(0x50C7A99057A69748) void GET_LOCAL_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second)l
#pragma endregion //}
#pragma region PATHFIND //{
extern _native64(0xBF1A602B5BA52FEE) void SET_ROADS_IN_AREA(vector3 vec_1, vector3 vec_2, bool unknown1, bool unknown2)l
extern _native64(0x1A5AA1208AF5DB59) void SET_ROADS_IN_ANGLED_AREA(vector3 vec_1, vector3 vec_2, float angle, bool unknown1, bool unknown2, bool unknown3)l
extern _native64(0x34F060F4BF92E018) void SET_PED_PATHS_IN_AREA(vector3 vec_1, vector3 vec_2, bool unknown)l
extern _native64(0xB61C8E878A4199CA) bool GET_SAFE_COORD_FOR_PED(vector3 vec, bool onGround, vector3* outPosition, int flags)l
extern _native64(0x240A18690AE96513) bool GET_CLOSEST_VEHICLE_NODE(vector3 vec, vector3* outPosition, int nodeType, float p5, float p6)l
extern _native64(0x2EABE3B06F58C1BE) bool GET_CLOSEST_MAJOR_VEHICLE_NODE(vector3 vec, vector3* outPosition, float unknown1, int unknown2)l
extern _native64(0xFF071FB798B803B0) bool GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(vector3 vec, vector3* outPosition, float* outHeading, int nodeType, float p6, int p7)l
extern _native64(0xE50E52416CCF948B) bool GET_NTH_CLOSEST_VEHICLE_NODE(vector3 vec, int nthClosest, vector3* outPosition, any unknown1, any unknown2, any unknown3)l
extern _native64(0x22D7275A79FE8215) int GET_NTH_CLOSEST_VEHICLE_NODE_ID(vector3 vec, int nth, int nodetype, float p5, float p6)l
extern _native64(0x80CA6A8B6C094CC4) bool GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(vector3 vec, int nthClosest, vector3* outPosition, float* heading, any* unknown1, int unknown2, float unknown3, float unknown4)l
extern _native64(0x6448050E9C2A7207) any GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(vector3 vec, int nthClosest, vector3* outPosition, float outHeading, any p6, float p7, float p8)l
extern _native64(0x45905BE8654AE067) bool GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(vector3 vec, vector3 desired, int nthClosest, vector3* outPosition, float* outHeading, int nodetype, any p10, any p11)l
extern _native64(0x0568566ACBB5DEDC) bool GET_VEHICLE_NODE_PROPERTIES(vector3 vec, int* density, int* flags)l
extern _native64(0x1EAF30FCFBF5AF74) bool IS_VEHICLE_NODE_ID_VALID(int vehicleNodeId)l
extern _native64(0x703123E5E7D429C2) void GET_VEHICLE_NODE_POSITION(int nodeId, vector3* outPosition)l
extern _native64(0xA2AE5C478B96E3B6) bool _GET_SUPPORTS_GPS_ROUTE_FLAG(int nodeID)l
extern _native64(0x4F5070AA58F69279) bool _GET_IS_SLOW_ROAD_FLAG(int nodeID)l
extern _native64(0x132F52BBA570FE92) any GET_CLOSEST_ROAD(vector3 vec, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10)l
extern _native64(0x80E4A6EDDB0BE8D9) bool LOAD_ALL_PATH_NODES(bool keepInMemory)l
extern _native64(0x228E5C6AD4D74BFD) void UNK_0x228E5C6AD4D74BFD(bool p0)l
extern _native64(0xF7B79A50B905A30D) bool UNK_0xF7B79A50B905A30D(float p0, float p1, float p2, float p3)l
extern _native64(0x07FB139B592FA687) bool UNK_0x07FB139B592FA687(float p0, float p1, float p2, float p3)l
extern _native64(0x1EE7063B80FFC77C) void SET_ROADS_BACK_TO_ORIGINAL(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native64(0x0027501B9F3B407E) void SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(vector3 vec_1, vector3 vec_2, float p6)l
extern _native64(0x0B919E1FB47CC4E0) void UNK_0x0B919E1FB47CC4E0(float p0)l
extern _native64(0xAA76052DDA9BFC3E) void UNK_0xAA76052DDA9BFC3E(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0xE04B48F2CC926253) void SET_PED_PATHS_BACK_TO_ORIGINAL(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x93E0DB8440B73A7D) bool GET_RANDOM_VEHICLE_NODE(vector3 vec, float radius, bool p4, bool p5, bool p6, vector3* outPosition, float* heading)l
extern _native64(0x2EB41072B4C1E4C0) void GET_STREET_NAME_AT_COORD(vector3 vec, Hash* streetName, Hash* crossingRoad)l
extern _native64(0xF90125F1F79ECDF8) int GENERATE_DIRECTIONS_TO_COORD(vector3 vec, bool p3, float* direction, float* p5, float* distToNxJunction)l
extern _native64(0x72751156E7678833) void SET_IGNORE_NO_GPS_FLAG(bool ignore)l
extern _native64(0x1FC289A0C3FF470F) any UNK_0x1FC289A0C3FF470F(bool p0)l
extern _native64(0xDC20483CD3DD5201) void SET_GPS_DISABLED_ZONE(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0xBBB45C3CF5C8AA85) any UNK_0xBBB45C3CF5C8AA85()l
extern _native64(0x869DAACBBE9FA006) any UNK_0x869DAACBBE9FA006()l
extern _native64(0x16F46FB18C8009E4) any UNK_0x16F46FB18C8009E4(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x125BF4ABFC536B09) bool IS_POINT_ON_ROAD(vector3 vec, Vehicle vehicle)l
extern _native64(0xD3A6A0EF48823A8C) any UNK_0xD3A6A0EF48823A8C()l
extern _native64(0xD0BC1C6FB18EE154) void UNK_0xD0BC1C6FB18EE154(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x2801D0012266DF07) void UNK_0x2801D0012266DF07(any p0)l
extern _native64(0x387EAD7EE42F6685) void ADD_NAVMESH_REQUIRED_REGION(vector2 vector, float radius)l
extern _native64(0x916F0A3CDEC3445E) void REMOVE_NAVMESH_REQUIRED_REGIONS()l
extern _native64(0x4C8872D8CDBE1B8B) void DISABLE_NAVMESH_IN_AREA(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0x8415D95B194A3AEA) bool ARE_ALL_NAVMESH_REGIONS_LOADED()l
extern _native64(0xF813C7E63F9062A5) bool IS_NAVMESH_LOADED_IN_AREA(vector3 vec_1, vector3 vec_2)l
extern _native64(0x01708E8DD3FF8C65) any UNK_0x01708E8DD3FF8C65(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native64(0xFCD5C8E06E502F5A) any ADD_NAVMESH_BLOCKING_OBJECT(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, any p8)l
extern _native64(0x109E99373F290687) void UPDATE_NAVMESH_BLOCKING_OBJECT(any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8)l
extern _native64(0x46399A7895957C0E) void REMOVE_NAVMESH_BLOCKING_OBJECT(any p0)l
extern _native64(0x0EAEB0DB4B132399) bool DOES_NAVMESH_BLOCKING_OBJECT_EXIST(any p0)l
extern _native64(0x29C24BFBED8AB8FB) float UNK_0x29C24BFBED8AB8FB(float p0, float p1)l
extern _native64(0x8ABE8608576D9CE3) float UNK_0x8ABE8608576D9CE3(float p0, float p1, float p2, float p3)l
extern _native64(0x336511A34F2E5185) float UNK_0x336511A34F2E5185(float left, float right)l
extern _native64(0x3599D741C9AC6310) float UNK_0x3599D741C9AC6310(float p0, float p1, float p2, float p3)l
extern _native64(0xADD95C7005C4A197) float CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(vector3 vec_1, vector3 vec_2)l
#pragma endregion //}
#pragma region CONTROLS //{
extern _native64(0x1CEA6BFDF248E5D9) bool IS_CONTROL_ENABLED(int inputGroup, int control)l
extern _native64(0xF3A21BCD95725A4A) bool IS_CONTROL_PRESSED(int inputGroup, int control)l
extern _native64(0x648EE3E7F38877DD) bool IS_CONTROL_RELEASED(int inputGroup, int control)l
extern _native64(0x580417101DDB492F) bool IS_CONTROL_JUST_PRESSED(int inputGroup, int control)l
extern _native64(0x50F940259D3841E6) bool IS_CONTROL_JUST_RELEASED(int inputGroup, int control)l
extern _native64(0xD95E79E8686D2C27) int GET_CONTROL_VALUE(int inputGroup, int control)l
extern _native64(0xEC3C9B8D5327B563) float GET_CONTROL_NORMAL(int inputGroup, int control)l
extern _native64(0x5B73C77D9EB66E24) void UNK_0x5B73C77D9EB66E24(bool p0)l
extern _native64(0x5B84D09CEC5209C5) float UNK_0x5B84D09CEC5209C5(int inputGroup, int control)l
extern _native64(0xE8A25867FBA3B05E) bool _SET_CONTROL_NORMAL(int inputGroup, int control, float amount)l
extern _native64(0xE2587F8CBBD87B1D) bool IS_DISABLED_CONTROL_PRESSED(int inputGroup, int control)l
extern _native64(0x91AEF906BCA88877) bool IS_DISABLED_CONTROL_JUST_PRESSED(int inputGroup, int control)l
extern _native64(0x305C8DCD79DA8B0F) bool IS_DISABLED_CONTROL_JUST_RELEASED(int inputGroup, int control)l
extern _native64(0x11E65974A982637C) float GET_DISABLED_CONTROL_NORMAL(int inputGroup, int control)l
extern _native64(0x4F8A26A890FD62FB) float UNK_0x4F8A26A890FD62FB(int inputGroup, int control)l
extern _native64(0xD7D22F5592AED8BA) int UNK_0xD7D22F5592AED8BA(int p0)l
extern _native64(0xA571D46727E2B718) bool _IS_INPUT_DISABLED(int inputGroup)l
extern _native64(0x13337B38DB572509) bool _IS_INPUT_JUST_DISABLED(int inputGroup)l
extern _native64(0xFC695459D4D0E219) bool _SET_CURSOR_LOCATION(vector2 vector)l
extern _native64(0x23F09EADC01449D6) bool UNK_0x23F09EADC01449D6(bool p0)l
extern _native64(0x6CD79468A1E595C6) bool UNK_0x6CD79468A1E595C6(int inputGroup)l
extern _native64(0x0499D7B09FC9B407) const char* GET_CONTROL_INSTRUCTIONAL_BUTTON(int inputGroup, int control, bool p2)l
extern _native64(0x80C2FD58D720C801) const char* UNK_0x80C2FD58D720C801(int inputGroup, int control, bool p2)l
extern _native64(0x8290252FFF36ACB5) void UNK_0x8290252FFF36ACB5(int p0, RGB colour)l
extern _native64(0xCB0360EFEFB2580D) void UNK_0xCB0360EFEFB2580D(any p0)l
extern _native64(0x48B3886C1358D0D5) void SET_PAD_SHAKE(int p0, int duration, int frequency)l
extern _native64(0x14D29BB12D47F68C) void UNK_0x14D29BB12D47F68C(any p0, any p1, any p2, any p3, any p4)l
extern _native64(0x38C16A305E8CDC8D) void STOP_PAD_SHAKE(any p0)l
extern _native64(0xF239400E16C23E08) void UNK_0xF239400E16C23E08(any p0, any p1)l
extern _native64(0xA0CEFCEA390AAB9B) void UNK_0xA0CEFCEA390AAB9B(any p0)l
extern _native64(0x77B612531280010D) bool IS_LOOK_INVERTED()l
extern _native64(0xE1615EC03B3BB4FD) bool UNK_0xE1615EC03B3BB4FD()l
extern _native64(0xBB41AFBBBC0A0287) int GET_LOCAL_PLAYER_AIM_STATE()l
extern _native64(0x59B9A7AF4C95133C) any UNK_0x59B9A7AF4C95133C()l
extern _native64(0x0F70731BACCFBB96) bool UNK_0x0F70731BACCFBB96()l
extern _native64(0xFC859E2374407556) bool UNK_0xFC859E2374407556()l
extern _native64(0x798FDEB5B1575088) void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(bool toggle)l
extern _native64(0xEDE476E5EE29EDB1) void SET_INPUT_EXCLUSIVE(int inputGroup, int control)l
extern _native64(0xFE99B66D079CF6BC) void DISABLE_CONTROL_ACTION(int inputGroup, int control, bool disable)l
extern _native64(0x351220255D64C155) void ENABLE_CONTROL_ACTION(int inputGroup, int control, bool enable)l
extern _native64(0x5F4B6931816E599B) void DISABLE_ALL_CONTROL_ACTIONS(int inputGroup)l
extern _native64(0xA5FFE9B05F199DE7) void ENABLE_ALL_CONTROL_ACTIONS(int inputGroup)l
extern _native64(0x3D42B92563939375) bool UNK_0x3D42B92563939375(const char* p0)l
extern _native64(0x4683149ED1DDE7A1) bool UNK_0x4683149ED1DDE7A1(const char* p0)l
extern _native64(0x643ED62D5EA3BEBD) void UNK_0x643ED62D5EA3BEBD()l
extern _native64(0x7F4724035FDCA1DD) void _DISABLE_INPUT_GROUP(int inputGroup)l
#pragma endregion //}
#pragma region DATAFILE //{
extern _native64(0xAD6875BBC0FC899C) void UNK_0xAD6875BBC0FC899C(any p0)l
extern _native64(0x6CC86E78358D5119) void UNK_0x6CC86E78358D5119()l
extern _native64(0xFCCAE5B92A830878) bool UNK_0xFCCAE5B92A830878(any p0)l
extern _native64(0x15FF52B809DB2353) bool UNK_0x15FF52B809DB2353(any p0)l
extern _native64(0xF8CC1EBE0B62E29F) bool UNK_0xF8CC1EBE0B62E29F(any p0)l
extern _native64(0x22DA66936E0FFF37) bool UNK_0x22DA66936E0FFF37(any p0)l
extern _native64(0x8F5EA1C01D65A100) bool UNK_0x8F5EA1C01D65A100(any p0)l
extern _native64(0xC84527E235FCA219) bool UNK_0xC84527E235FCA219(const char* p0, bool p1, const char* p2, any* p3, any* p4, const char* type, bool p6)l
extern _native64(0xA5EFC3E847D60507) bool UNK_0xA5EFC3E847D60507(const char* p0, const char* p1, const char* p2, const char* p3, bool p4)l
extern _native64(0x648E7A5434AF7969) bool UNK_0x648E7A5434AF7969(const char* p0, any* p1, bool p2, any* p3, any* p4, any* p5, const char* type)l
extern _native64(0x4645DE9980999E93) bool UNK_0x4645DE9980999E93(const char* p0, const char* p1, const char* p2, const char* p3, const char* type)l
extern _native64(0x692D808C34A82143) bool UNK_0x692D808C34A82143(const char* p0, float p1, const char* type)l
extern _native64(0xA69AC4ADE82B57A4) bool UNK_0xA69AC4ADE82B57A4(int p0)l
extern _native64(0x9CB0BFA7A9342C3D) bool UNK_0x9CB0BFA7A9342C3D(int p0, bool p1)l
extern _native64(0x52818819057F2B40) bool UNK_0x52818819057F2B40(int p0)l
extern _native64(0x01095C95CD46B624) bool UNK_0x01095C95CD46B624(int p0)l
extern _native64(0xC5238C011AF405E4) bool _LOAD_UGC_FILE(const char* filename)l
extern _native64(0xD27058A1CA2B13EE) void DATAFILE_CREATE()l
extern _native64(0x9AB9C1CFC8862DFB) void DATAFILE_DELETE()l
extern _native64(0x2ED61456317B8178) void UNK_0x2ED61456317B8178()l
extern _native64(0xC55854C7D7274882) void UNK_0xC55854C7D7274882()l
extern _native64(0x906B778CA1DC72B6) const char* DATAFILE_GET_FILE_DICT()l
extern _native64(0x83BCCE3224735F05) bool UNK_0x83BCCE3224735F05(const char* filename)l
extern _native64(0x4DFDD9EB705F8140) bool UNK_0x4DFDD9EB705F8140(bool* p0)l
extern _native64(0xBEDB96A7584AA8CF) bool DATAFILE_IS_SAVE_PENDING()l
extern _native64(0x35124302A556A325) void _OBJECT_VALUE_ADD_BOOLEAN(any* objectData, const char* key, bool value)l
extern _native64(0xE7E035450A7948D5) void _OBJECT_VALUE_ADD_INTEGER(any* objectData, const char* key, int value)l
extern _native64(0xC27E1CC2D795105E) void _OBJECT_VALUE_ADD_FLOAT(any* objectData, const char* key, float value)l
extern _native64(0x8FF3847DADD8E30C) void _OBJECT_VALUE_ADD_STRING(any* objectData, const char* key, const char* value)l
extern _native64(0x4CD49B76338C7DEE) void _OBJECT_VALUE_ADD_VECTOR3(any* objectData, const char* key, vector3 value)l
extern _native64(0xA358F56F10732EE1) any* _OBJECT_VALUE_ADD_OBJECT(any* objectData, const char* key)l
extern _native64(0x5B11728527CA6E5F) any* _OBJECT_VALUE_ADD_ARRAY(any* objectData, const char* key)l
extern _native64(0x1186940ED72FFEEC) bool _OBJECT_VALUE_GET_BOOLEAN(any* objectData, const char* key)l
extern _native64(0x78F06F6B1FB5A80C) int _OBJECT_VALUE_GET_INTEGER(any* objectData, const char* key)l
extern _native64(0x06610343E73B9727) float _OBJECT_VALUE_GET_FLOAT(any* objectData, const char* key)l
extern _native64(0x3D2FD9E763B24472) const char* _OBJECT_VALUE_GET_STRING(any* objectData, const char* key)l
extern _native64(0x46CD3CB66E0825CC) vector3 _OBJECT_VALUE_GET_VECTOR3(any* objectData, const char* key)l
extern _native64(0xB6B9DDC412FCEEE2) any* _OBJECT_VALUE_GET_OBJECT(any* objectData, const char* key)l
extern _native64(0x7A983AA9DA2659ED) any* _OBJECT_VALUE_GET_ARRAY(any* objectData, const char* key)l
extern _native64(0x031C55ED33227371) int _OBJECT_VALUE_GET_TYPE(any* objectData, const char* key)l
extern _native64(0xF8B0F5A43E928C76) void _ARRAY_VALUE_ADD_BOOLEAN(any* arrayData, bool value)l
extern _native64(0xCABDB751D86FE93B) void _ARRAY_VALUE_ADD_INTEGER(any* arrayData, int value)l
extern _native64(0x57A995FD75D37F56) void _ARRAY_VALUE_ADD_FLOAT(any* arrayData, float value)l
extern _native64(0x2F0661C155AEEEAA) void _ARRAY_VALUE_ADD_STRING(any* arrayData, const char* value)l
extern _native64(0x407F8D034F70F0C2) void _ARRAY_VALUE_ADD_VECTOR3(any* arrayData, vector3 value)l
extern _native64(0x6889498B3E19C797) any* _ARRAY_VALUE_ADD_OBJECT(any* arrayData)l
extern _native64(0x50C1B2874E50C114) bool _ARRAY_VALUE_GET_BOOLEAN(any* arrayData, int arrayIndex)l
extern _native64(0x3E5AE19425CD74BE) int _ARRAY_VALUE_GET_INTEGER(any* arrayData, int arrayIndex)l
extern _native64(0xC0C527B525D7CFB5) float _ARRAY_VALUE_GET_FLOAT(any* arrayData, int arrayIndex)l
extern _native64(0xD3F2FFEB8D836F52) const char* _ARRAY_VALUE_GET_STRING(any* arrayData, int arrayIndex)l
extern _native64(0x8D2064E5B64A628A) vector3 _ARRAY_VALUE_GET_VECTOR3(any* arrayData, int arrayIndex)l
extern _native64(0x8B5FADCC4E3A145F) any* _ARRAY_VALUE_GET_OBJECT(any* arrayData, int arrayIndex)l
extern _native64(0x065DB281590CEA2D) int _ARRAY_VALUE_GET_SIZE(any* arrayData)l
extern _native64(0x3A0014ADB172A3C5) int _ARRAY_VALUE_GET_TYPE(any* arrayData, int arrayIndex)l
#pragma endregion //}
#pragma region FIRE //{
extern _native64(0x6B83617E04503888) int START_SCRIPT_FIRE(vector3 vec, int maxChildren, bool isGasFire)l
extern _native64(0x7FF548385680673F) void REMOVE_SCRIPT_FIRE(int fireHandle)l
extern _native64(0xF6A9D9708F6F23DF) any START_ENTITY_FIRE(Entity entity)l
extern _native64(0x7F0DD2EBBB651AFF) void STOP_ENTITY_FIRE(Entity entity)l
extern _native64(0x28D3FED7190D3A0B) bool IS_ENTITY_ON_FIRE(Entity entity)l
extern _native64(0x50CAD495A460B305) int GET_NUMBER_OF_FIRES_IN_RANGE(vector3 vec, float radius)l
extern _native64(0x056A8A219B8E829F) void STOP_FIRE_IN_RANGE(vector3 vec, float radius)l
extern _native64(0x352A9F6BCF90081F) bool GET_CLOSEST_FIRE_POS(vector3* outPosition, vector3 vec)l
extern _native64(0xE3AD2BDBAEE269AC) void ADD_EXPLOSION(vector3 vec, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake, bool unk0)l
extern _native64(0x172AA1B624FA1013) void ADD_OWNED_EXPLOSION(Ped ped, vector3 vec, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native64(0x36DD3FE58B5E5212) void ADD_EXPLOSION_WITH_USER_VFX(vector3 vec, int explosionType, Hash explosionFx, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native64(0x2E2EBA0EE7CED0E0) bool IS_EXPLOSION_IN_AREA(int explosionType, vector3 vec_1, vector3 vec_2)l
extern _native64(0x6070104B699B2EF4) any UNK_0x6070104B699B2EF4(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native64(0xAB0F816885B0E483) bool IS_EXPLOSION_IN_SPHERE(int explosionType, vector3 vec, float radius)l
extern _native64(0xA079A6C51525DC4B) bool IS_EXPLOSION_IN_ANGLED_AREA(int explosionType, vector3 vec_1, vector3 vec_2, float angle)l
extern _native64(0x14BA4BA137AF6CEC) Entity _GET_PED_INSIDE_EXPLOSION_AREA(int explosionType, vector3 vec_1, vector3 vec_2, float radius)l
#pragma endregion //}
#pragma region DECISIONEVENT //{
extern _native64(0xB604A2942ADED0EE) void SET_DECISION_MAKER(Ped ped, Hash name)l
extern _native64(0x4FC9381A7AEE8968) void CLEAR_DECISION_MAKER_EVENT_RESPONSE(Hash name, int type)l
extern _native64(0xE42FCDFD0E4196F7) void BLOCK_DECISION_MAKER_EVENT(Hash name, int type)l
extern _native64(0xD7CD9CF34F2C99E8) void UNBLOCK_DECISION_MAKER_EVENT(Hash name, int type)l
extern _native64(0xD9F8455409B525E9) ScrHandle ADD_SHOCKING_EVENT_AT_POSITION(int type, vector3 vec, float duration)l
extern _native64(0x7FD8F3BE76F89422) ScrHandle ADD_SHOCKING_EVENT_FOR_ENTITY(int type, Entity entity, float duration)l
extern _native64(0x1374ABB7C15BAB92) bool IS_SHOCKING_EVENT_IN_SPHERE(int type, vector3 vec, float radius)l
extern _native64(0x2CDA538C44C6CCE5) bool REMOVE_SHOCKING_EVENT(ScrHandle event)l
extern _native64(0xEAABE8FDFA21274C) void REMOVE_ALL_SHOCKING_EVENTS(bool p0)l
extern _native64(0x340F1415B68AEADE) void REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS()l
extern _native64(0x2F9A292AD0A3BD89) void SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME()l
extern _native64(0x3FD2EC8BF1F1CF30) void SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(int type)l
extern _native64(0x5F3B7749C112D552) void SUPPRESS_AGITATION_EVENTS_NEXT_FRAME()l
#pragma endregion //}
#pragma region ZONE //{
extern _native64(0x27040C25DE6CB2F4) int GET_ZONE_AT_COORDS(vector3 vec)l
extern _native64(0x98CD1D2934B76CC1) int GET_ZONE_FROM_NAME_ID(const char* zoneName)l
extern _native64(0x4334BC40AA0CB4BB) int GET_ZONE_POPSCHEDULE(int zoneId)l
extern _native64(0xCD90657D4C30E1CA) const char* GET_NAME_OF_ZONE(vector3 vec)l
extern _native64(0xBA5ECEEA120E5611) void SET_ZONE_ENABLED(int zoneId, bool toggle)l
extern _native64(0x5F7B268D15BA0739) int GET_ZONE_SCUMMINESS(int zoneId)l
extern _native64(0x5F7D596BAC2E7777) void OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(int scheduleId, Hash vehicleHash)l
extern _native64(0x5C0DE367AA0D911C) void CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(int scheduleId)l
extern _native64(0x7EE64D51E8498728) Hash GET_HASH_OF_MAP_AREA_AT_COORDS(vector3 vec)l
#pragma endregion //}
#pragma region ROPE //{
extern _native64(0xE832D760399EB220) Object ADD_ROPE(vector3 vec, vector3 rot, float length, int ropeType, float maxLength, float minLength, float p10, bool p11, bool p12, bool rigid, float p14, bool breakWhenShot, any* unkPtr)l
extern _native64(0x52B4829281364649) void DELETE_ROPE(Object* rope)l
extern _native64(0xAA5D6B1888E4DB20) any DELETE_CHILD_ROPE(Object rope)l
extern _native64(0xFD5448BE3111ED96) bool DOES_ROPE_EXIST(Object* rope)l
extern _native64(0xF159A63806BB5BA8) void ROPE_DRAW_SHADOW_ENABLED(Object* rope, bool toggle)l
extern _native64(0xCBB203C04D1ABD27) any LOAD_ROPE_DATA(Object rope, const char* rope_preset)l
extern _native64(0x2B320CF14146B69A) void PIN_ROPE_VERTEX(Object rope, int vertex, vector3 vec)l
extern _native64(0x4B5AE2EEE4A8F180) any UNPIN_ROPE_VERTEX(Object rope, int vertex)l
extern _native64(0x3655F544CD30F0B5) int GET_ROPE_VERTEX_COUNT(Object rope)l
extern _native64(0x3D95EC8B6D940AC3) void ATTACH_ENTITIES_TO_ROPE(Object rope, Entity ent1, Entity ent2, vector3 ent1_, vector3 ent2_, float length, bool p10, bool p11, any* p12, any* p13)l
extern _native64(0x4B490A6832559A65) void ATTACH_ROPE_TO_ENTITY(Object rope, Entity entity, vector3 vec, bool p5)l
extern _native64(0xBCF3026912A8647D) void DETACH_ROPE_FROM_ENTITY(Object rope, Entity entity)l
extern _native64(0xC8D667EE52114ABA) void ROPE_SET_UPDATE_PINVERTS(Object rope)l
extern _native64(0xDC57A637A20006ED) void UNK_0xDC57A637A20006ED(any p0, any p1)l
extern _native64(0x36CCB9BE67B970FD) void UNK_0x36CCB9BE67B970FD(any p0, bool p1)l
extern _native64(0x84DE3B5FB3E666F0) bool UNK_0x84DE3B5FB3E666F0(any* p0)l
extern _native64(0x21BB0FBD3E217C2D) any GET_ROPE_LAST_VERTEX_COORD(Object rope)l
extern _native64(0xEA61CA8E80F09E4D) any GET_ROPE_VERTEX_COORD(Object rope, int vertex)l
extern _native64(0x1461C72C889E343E) void START_ROPE_WINDING(Object rope)l
extern _native64(0xCB2D4AB84A19AA7C) void STOP_ROPE_WINDING(Object rope)l
extern _native64(0x538D1179EC1AA9A9) void START_ROPE_UNWINDING_FRONT(Object rope)l
extern _native64(0xFFF3A50779EFBBB3) void STOP_ROPE_UNWINDING_FRONT(Object rope)l
extern _native64(0x5389D48EFA2F079A) void ROPE_CONVERT_TO_SIMPLE(Object rope)l
extern _native64(0x9B9039DBF2D258C1) any ROPE_LOAD_TEXTURES()l
extern _native64(0xF2D0E6A75CC05597) bool ROPE_ARE_TEXTURES_LOADED()l
extern _native64(0x6CE36C35C1AC8163) any ROPE_UNLOAD_TEXTURES()l
extern _native64(0x271C9D3ACA5D6409) bool UNK_0x271C9D3ACA5D6409(Object rope)l
extern _native64(0xBC0CE682D4D05650) void UNK_0xBC0CE682D4D05650(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10, any p11, any p12, any p13)l
extern _native64(0xB1B6216CA2E7B55E) void UNK_0xB1B6216CA2E7B55E(any p0, bool p1, bool p2)l
extern _native64(0xB743F735C03D7810) void UNK_0xB743F735C03D7810(any p0, any p1)l
extern _native64(0x73040398DFF9A4A6) float _GET_ROPE_LENGTH(Object rope)l
extern _native64(0xD009F759A723DB1B) any ROPE_FORCE_LENGTH(Object rope, float length)l
extern _native64(0xC16DE94D9BEA14A0) any ROPE_RESET_LENGTH(Object rope, bool length)l
extern _native64(0xE37F721824571784) void APPLY_IMPULSE_TO_CLOTH(vector3 pos, vector3 vec, float impulse)l
extern _native64(0xEEA3B200A6FEB65B) void SET_DAMPING(Object rope, int vertex, float value)l
extern _native64(0x710311ADF0E20730) void ACTIVATE_PHYSICS(Entity entity)l
extern _native64(0xD8FA3908D7B86904) void SET_CGOFFSET(Object rope, vector3 vec)l
extern _native64(0x8214A4B5A7A33612) vector3 GET_CGOFFSET(Object rope)l
extern _native64(0xBE520D9761FF811F) void SET_CG_AT_BOUNDCENTER(Object rope)l
extern _native64(0x2E648D16F6E308F3) void BREAK_ENTITY_GLASS(any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, any p9, bool p10)l
extern _native64(0x5CEC1A84620E7D5B) any SET_DISABLE_BREAKING(Object rope, bool enabled)l
extern _native64(0xCC6E963682533882) void UNK_0xCC6E963682533882(any p0)l
extern _native64(0x01BA3AED21C16CFB) void SET_DISABLE_FRAG_DAMAGE(Object object, bool toggle)l
#pragma endregion //}
#pragma region WATER //{
extern _native64(0xF6829842C06AE524) bool GET_WATER_HEIGHT(vector3 vec, float* height)l
extern _native64(0x8EE6B53CE13A9794) bool GET_WATER_HEIGHT_NO_WAVES(vector3 vec, float* height)l
extern _native64(0xFFA5D878809819DB) bool TEST_PROBE_AGAINST_WATER(vector3 vec_1, vector3 vec_2, vector3* result)l
extern _native64(0x8974647ED222EA5F) bool TEST_PROBE_AGAINST_ALL_WATER(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native64(0x2B3451FA1E3142E2) bool TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(vector3 vec, any p3, any* p4)l
extern _native64(0xC443FD757C3BA637) void MODIFY_WATER(vector2 vector, float radius, float height)l
extern _native64(0xFDBF4CDBC07E1706) int UNK_0xFDBF4CDBC07E1706(vector3 vec, float radius, float unk)l
extern _native64(0xB1252E3E59A82AAF) void UNK_0xB1252E3E59A82AAF(int p0)l
extern _native64(0xB96B00E976BE977F) void _SET_WAVES_INTENSITY(float intensity)l
extern _native64(0x2B2A2CC86778B619) float _GET_WAVES_INTENSITY()l
extern _native64(0x5E5E99285AE812DB) void _RESET_WAVES_INTENSITY()l
#pragma endregion //}
#pragma region WORLDPROBE //{
extern _native64(0x7EE9F5D83DD4F90E) int START_SHAPE_TEST_LOS_PROBE(vector3 vec_1, vector3 vec_2, int flags, Entity entity, int p8)l
extern _native64(0x377906D8A31E5586) int _START_SHAPE_TEST_RAY(vector3 vec_1, vector3 vec_2, int flags, Entity entity, int p8)l
extern _native64(0x052837721A854EC7) int START_SHAPE_TEST_BOUNDING_BOX(Entity entity, int flags1, int flags2)l
extern _native64(0xFE466162C4401D18) int START_SHAPE_TEST_BOX(vector3 vec, float x1, float y2, float z2, vector3 rot, any p9, any p10, any entity, any p12)l
extern _native64(0x37181417CE7C8900) int START_SHAPE_TEST_BOUND(Entity entity, int flags1, int flags2)l
extern _native64(0x28579D1B8F8AAC80) int START_SHAPE_TEST_CAPSULE(vector3 vec_1, vector3 vec_2, float radius, int flags, Entity entity, int p9)l
extern _native64(0xE6AC6C45FBE83004) int UNK_0xE6AC6C45FBE83004(vector3 vec_1, vector3 vec_2, float radius, int flags, Entity entity, any p9)l
extern _native64(0xFF6BE494C7987F34) int UNK_0xFF6BE494C7987F34(vector3* pVec1, vector3* pVec2, int flag, Entity entity, int flag2)l
extern _native64(0x3D87450E15D98694) int GET_SHAPE_TEST_RESULT(int rayHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Entity* entityHit)l
extern _native64(0x65287525D951F6BE) int _GET_SHAPE_TEST_RESULT_EX(int rayHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Hash* materialHash, Entity* entityHit)l
extern _native64(0x2B3334BCA57CD799) void UNK_0x2B3334BCA57CD799(Entity p0)l
#pragma endregion //}
#pragma region NETWORK //{
extern _native64(0x054354A99211EB96) bool NETWORK_IS_SIGNED_IN()l
extern _native64(0x1077788E268557C2) bool NETWORK_IS_SIGNED_ONLINE()l
extern _native64(0xBD545D44CCE70597) bool UNK_0xBD545D44CCE70597()l
extern _native64(0xEBCAB9E5048434F4) any UNK_0xEBCAB9E5048434F4()l
extern _native64(0x74FB3E29E6D10FA9) any UNK_0x74FB3E29E6D10FA9()l
extern _native64(0x7808619F31FF22DB) any UNK_0x7808619F31FF22DB()l
extern _native64(0xA0FA4EC6A05DA44E) any UNK_0xA0FA4EC6A05DA44E()l
extern _native64(0x85443FF4C328F53B) bool _NETWORK_ARE_ROS_AVAILABLE()l
extern _native64(0x8D11E61A4ABF49CC) bool UNK_0x8D11E61A4ABF49CC()l
extern _native64(0x9A4CF4F48AD77302) bool NETWORK_IS_CLOUD_AVAILABLE()l
extern _native64(0x67A5589628E0CFF6) bool UNK_0x67A5589628E0CFF6()l
extern _native64(0xBA9775570DB788CF) any UNK_0xBA9775570DB788CF()l
extern _native64(0x8DB296B814EDDA07) bool NETWORK_IS_HOST()l
extern _native64(0xA306F470D1660581) any UNK_0xA306F470D1660581()l
extern _native64(0x4237E822315D8BA9) bool UNK_0x4237E822315D8BA9()l
extern _native64(0x25CB5A9F37BFD063) bool NETWORK_HAVE_ONLINE_PRIVILEGES()l
extern _native64(0x1353F87E89946207) bool UNK_0x1353F87E89946207()l
extern _native64(0x72D918C99BCACC54) bool UNK_0x72D918C99BCACC54(any p0)l
extern _native64(0xAEEF48CDF5B6CE7C) bool UNK_0xAEEF48CDF5B6CE7C(any p0, any p1)l
extern _native64(0x78321BEA235FD8CD) bool UNK_0x78321BEA235FD8CD(any p0, bool p1)l
extern _native64(0x595F028698072DD9) bool UNK_0x595F028698072DD9(any p0, any p1, bool p2)l
extern _native64(0x83F28CE49FBBFFBA) bool UNK_0x83F28CE49FBBFFBA(any p0, any p1, bool p2)l
extern _native64(0x76BF03FADBF154F5) any UNK_0x76BF03FADBF154F5()l
extern _native64(0x9614B71F8ADB982B) any UNK_0x9614B71F8ADB982B()l
extern _native64(0x5EA784D197556507) any UNK_0x5EA784D197556507()l
extern _native64(0xA8ACB6459542A8C8) any UNK_0xA8ACB6459542A8C8()l
extern _native64(0x83FE8D7229593017) void UNK_0x83FE8D7229593017()l
extern _native64(0x580CE4438479CC61) bool NETWORK_CAN_BAIL()l
extern _native64(0x95914459A87EBA28) void NETWORK_BAIL()l
extern _native64(0x283B6062A2C01E9B) void UNK_0x283B6062A2C01E9B()l
extern _native64(0xAF50DA1A3F8B1BA4) bool NETWORK_CAN_ACCESS_MULTIPLAYER(int* loadingState)l
extern _native64(0x9747292807126EDA) bool NETWORK_IS_MULTIPLAYER_DISABLED()l
extern _native64(0x7E782A910C362C25) bool NETWORK_CAN_ENTER_MULTIPLAYER()l
extern _native64(0x330ED4D05491934F) any NETWORK_SESSION_ENTER(any p0, any p1, any p2, int maxPlayers, any p4, any p5)l
extern _native64(0x2CFC76E0D087C994) bool NETWORK_SESSION_FRIEND_MATCHMAKING(int p0, int p1, int maxPlayers, bool p3)l
extern _native64(0x94BC51E9449D917F) bool NETWORK_SESSION_CREW_MATCHMAKING(int p0, int p1, int p2, int maxPlayers, bool p4)l
extern _native64(0xBE3E347A87ACEB82) bool NETWORK_SESSION_ACTIVITY_QUICKMATCH(any p0, any p1, any p2, any p3)l
extern _native64(0x6F3D4ED9BEE4E61D) bool NETWORK_SESSION_HOST(int p0, int maxPlayers, bool p2)l
extern _native64(0xED34C0C02C098BB7) bool NETWORK_SESSION_HOST_CLOSED(int p0, int maxPlayers)l
extern _native64(0xB9CFD27A5D578D83) bool NETWORK_SESSION_HOST_FRIENDS_ONLY(int p0, int maxPlayers)l
extern _native64(0xFBCFA2EA2E206890) bool NETWORK_SESSION_IS_CLOSED_FRIENDS()l
extern _native64(0x74732C6CA90DA2B4) bool NETWORK_SESSION_IS_CLOSED_CREW()l
extern _native64(0xF3929C2379B60CCE) bool NETWORK_SESSION_IS_SOLO()l
extern _native64(0xCEF70AA5B3F89BA1) bool NETWORK_SESSION_IS_PRIVATE()l
extern _native64(0xA02E59562D711006) bool NETWORK_SESSION_END(bool p0, bool p1)l
extern _native64(0xFA8904DC5F304220) void NETWORK_SESSION_KICK_PLAYER(Player player)l
extern _native64(0xD6D09A6F32F49EF1) bool _NETWORK_SESSION_IS_PLAYER_VOTED_TO_KICK(Player player)l
extern _native64(0x59DF79317F85A7E0) any UNK_0x59DF79317F85A7E0()l
extern _native64(0xFFE1E5B792D92B34) any UNK_0xFFE1E5B792D92B34()l
extern _native64(0x49EC8030F5015F8B) void UNK_0x49EC8030F5015F8B(int p0)l
extern _native64(0x8B6A4DD0AF9CE215) void _NETWORK_SESSION_SET_MAX_PLAYERS(int playerType, int playerCount)l
extern _native64(0x56CE820830EF040B) int _NETWORK_SESSION_GET_UNK(int p0)l
extern _native64(0xCAE55F48D3D7875C) void UNK_0xCAE55F48D3D7875C(any p0)l
extern _native64(0xF49ABC20D8552257) void UNK_0xF49ABC20D8552257(any p0)l
extern _native64(0x4811BBAC21C5FCD5) void UNK_0x4811BBAC21C5FCD5(any p0)l
extern _native64(0x5539C3EBF104A53A) void UNK_0x5539C3EBF104A53A(bool p0)l
extern _native64(0x702BC4D605522539) void UNK_0x702BC4D605522539(any p0)l
extern _native64(0x3F52E880AAF6C8CA) void UNK_0x3F52E880AAF6C8CA(bool p0)l
extern _native64(0xF1EEA2DDA9FFA69D) void UNK_0xF1EEA2DDA9FFA69D(any p0)l
extern _native64(0x1153FA02A659051C) void UNK_0x1153FA02A659051C()l
extern _native64(0xC19F6C8E7865A6FF) void _NETWORK_SESSION_HOSTED(bool p0)l
extern _native64(0x236406F60CF216D6) void NETWORK_ADD_FOLLOWERS(int* p0, int p1)l
extern _native64(0x058F43EC59A8631A) void NETWORK_CLEAR_FOLLOWERS()l
extern _native64(0x6D03BFBD643B2A02) void _NETWORK_GET_SERVER_TIME(int* hours, int* minutes, int* seconds)l
extern _native64(0x600F8CB31C7AAB6E) void UNK_0x600F8CB31C7AAB6E(any p0)l
extern _native64(0xE532D6811B3A4D2A) bool NETWORK_X_AFFECTS_GAMERS(any p0)l
extern _native64(0xF7B2CFDE5C9F700D) bool NETWORK_FIND_MATCHED_GAMERS(any p0, float p1, float p2, float p3)l
extern _native64(0xDDDF64C91BFCF0AA) bool NETWORK_IS_FINDING_GAMERS()l
extern _native64(0xF9B83B77929D8863) any UNK_0xF9B83B77929D8863()l
extern _native64(0xA1B043EE79A916FB) int NETWORK_GET_NUM_FOUND_GAMERS()l
extern _native64(0x9DCFF2AFB68B3476) bool NETWORK_GET_FOUND_GAMER(any* p0, any p1)l
extern _native64(0x6D14CCEE1B40381A) void NETWORK_CLEAR_FOUND_GAMERS()l
extern _native64(0x85A0EF54A500882C) bool UNK_0x85A0EF54A500882C(any* p0)l
extern _native64(0x2CC848A861D01493) any UNK_0x2CC848A861D01493()l
extern _native64(0x94A8394D150B013A) any UNK_0x94A8394D150B013A()l
extern _native64(0x5AE17C6B0134B7F1) any UNK_0x5AE17C6B0134B7F1()l
extern _native64(0x02A8BEC6FD9AF660) bool UNK_0x02A8BEC6FD9AF660(any* p0, any p1)l
extern _native64(0x86E0660E4F5C956D) void UNK_0x86E0660E4F5C956D()l
extern _native64(0xC6F8AB8A4189CF3A) void NETWORK_IS_PLAYER_ANIMATION_DRAWING_SYNCHRONIZED()l
extern _native64(0x2FBF47B1B36D36F9) void NETWORK_SESSION_CANCEL_INVITE()l
extern _native64(0xA29177F7703B5644) void NETWORK_SESSION_FORCE_CANCEL_INVITE()l
extern _native64(0xAC8C7B9B88C4A668) bool NETWORK_HAS_PENDING_INVITE()l
extern _native64(0xC42DD763159F3461) any UNK_0xC42DD763159F3461()l
extern _native64(0x62A0296C1BB1CEB3) any UNK_0x62A0296C1BB1CEB3()l
extern _native64(0x23DFB504655D0CE4) bool NETWORK_SESSION_WAS_INVITED()l
extern _native64(0xE57397B4A3429DD0) void NETWORK_SESSION_GET_INVITER(int* networkHandle)l
extern _native64(0xD313DE83394AF134) any UNK_0xD313DE83394AF134()l
extern _native64(0xBDB6F89C729CF388) any UNK_0xBDB6F89C729CF388()l
extern _native64(0xA0682D67EF1FBA3D) void NETWORK_SUPPRESS_INVITE(bool toggle)l
extern _native64(0x34F9E9049454A7A0) void NETWORK_BLOCK_INVITES(bool toggle)l
extern _native64(0xCFEB8AF24FC1D0BB) void UNK_0xCFEB8AF24FC1D0BB(bool p0)l
extern _native64(0xF814FEC6A19FD6E0) void UNK_0xF814FEC6A19FD6E0()l
extern _native64(0x6B07B9CE4D390375) void _NETWORK_BLOCK_KICKED_PLAYERS(bool p0)l
extern _native64(0x7AC752103856FB20) void UNK_0x7AC752103856FB20(bool p0)l
extern _native64(0x74698374C45701D2) any UNK_0x74698374C45701D2()l
extern _native64(0x140E6A44870A11CE) void UNK_0x140E6A44870A11CE()l
extern _native64(0xC74C33FCA52856D5) void NETWORK_SESSION_HOST_SINGLE_PLAYER(int p0)l
extern _native64(0x3442775428FD2DAA) void NETWORK_SESSION_LEAVE_SINGLE_PLAYER()l
extern _native64(0x10FAB35428CCC9D7) bool NETWORK_IS_GAME_IN_PROGRESS()l
extern _native64(0xD83C2B94E7508980) bool NETWORK_IS_SESSION_ACTIVE()l
extern _native64(0xCA97246103B63917) bool NETWORK_IS_IN_SESSION()l
extern _native64(0x9DE624D2FC4B603F) bool NETWORK_IS_SESSION_STARTED()l
extern _native64(0xF4435D66A8E2905E) bool NETWORK_IS_SESSION_BUSY()l
extern _native64(0x4EEBC3694E49C572) bool NETWORK_CAN_SESSION_END()l
extern _native64(0x271CC6AB59EBF9A5) void NETWORK_SESSION_MARK_VISIBLE(bool p0)l
extern _native64(0xBA416D68C631496A) any NETWORK_SESSION_IS_VISIBLE()l
extern _native64(0xA73667484D7037C3) void NETWORK_SESSION_BLOCK_JOIN_REQUESTS(bool p0)l
extern _native64(0xB4AB419E0D86ACAE) void NETWORK_SESSION_CHANGE_SLOTS(int p0, bool p1)l
extern _native64(0x53AFD64C6758F2F9) any UNK_0x53AFD64C6758F2F9()l
extern _native64(0x9C1556705F864230) void NETWORK_SESSION_VOICE_HOST()l
extern _native64(0x6793E42BE02B575D) void NETWORK_SESSION_VOICE_LEAVE()l
extern _native64(0xABD5E88B8A2D3DB2) void UNK_0xABD5E88B8A2D3DB2(any* globalPtr)l
extern _native64(0x7F8413B7FC2AA6B9) void NETWORK_SET_KEEP_FOCUSPOINT(bool p0, any p1)l
extern _native64(0x5B8ED3DB018927B1) void UNK_0x5B8ED3DB018927B1(any p0)l
extern _native64(0x855BC38818F6F684) bool UNK_0x855BC38818F6F684()l
extern _native64(0xB5D3453C98456528) any UNK_0xB5D3453C98456528()l
extern _native64(0xEF0912DDF7C4CB4B) bool UNK_0xEF0912DDF7C4CB4B()l
extern _native64(0x3A214F2EC889B100) int NETWORK_SEND_TEXT_MESSAGE(const char* message, const NetworkHandle* networkHandle)l
extern _native64(0x75138790B4359A74) void NETWORK_SET_ACTIVITY_SPECTATOR(bool toggle)l
extern _native64(0x12103B9E0C9F92FB) any NETWORK_IS_ACTIVITY_SPECTATOR()l
extern _native64(0x9D277B76D1D12222) void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(int maxSpectators)l
extern _native64(0x73E2B500410DA5A2) int NETWORK_GET_ACTIVITY_PLAYER_NUM(bool p0)l
extern _native64(0x2763BBAA72A7BCB9) bool NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(int* networkHandle)l
extern _native64(0xA60BB5CE242BB254) any NETWORK_HOST_TRANSITION(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native64(0x71FB0EBCD4915D56) bool NETWORK_DO_TRANSITION_QUICKMATCH(any p0, any p1, any p2, any p3)l
extern _native64(0xA091A5E44F0072E5) bool NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC(any p0, any p1, any p2, any p3)l
extern _native64(0x9C4AB58491FDC98A) bool NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP(any p0, any p1, any p2, any p3, any* p4, any p5)l
extern _native64(0xA06509A691D12BE4) any NETWORK_JOIN_GROUP_ACTIVITY()l
extern _native64(0xB13E88E655E5A3BC) void UNK_0xB13E88E655E5A3BC()l
extern _native64(0x6512765E3BE78C50) any UNK_0x6512765E3BE78C50()l
extern _native64(0x0DBD5D7E3C5BEC3B) any UNK_0x0DBD5D7E3C5BEC3B()l
extern _native64(0x5DC577201723960A) bool UNK_0x5DC577201723960A()l
extern _native64(0x5A6AA44FF8E931E6) bool UNK_0x5A6AA44FF8E931E6()l
extern _native64(0x261E97AD7BCF3D40) void UNK_0x261E97AD7BCF3D40(bool p0)l
extern _native64(0x39917E1B4CB0F911) void UNK_0x39917E1B4CB0F911(bool p0)l
extern _native64(0xEF26739BCD9907D5) void NETWORK_SET_TRANSITION_CREATOR_HANDLE(any* p0)l
extern _native64(0xFB3272229A82C759) void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE()l
extern _native64(0x4A595C32F77DFF76) bool NETWORK_INVITE_GAMERS_TO_TRANSITION(any* p0, any p1)l
extern _native64(0xCA2C8073411ECDB6) void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(int* networkHandle)l
extern _native64(0xD23A1A815D21DB19) any NETWORK_LEAVE_TRANSITION()l
extern _native64(0x2DCF46CB1A4F0884) any NETWORK_LAUNCH_TRANSITION()l
extern _native64(0xA2E9C1AB8A92E8CD) void UNK_0xA2E9C1AB8A92E8CD(bool p0)l
extern _native64(0xEAA572036990CD1B) void NETWORK_BAIL_TRANSITION()l
extern _native64(0x3E9BB38102A589B0) bool NETWORK_DO_TRANSITION_TO_GAME(bool p0, int maxPlayers)l
extern _native64(0x4665F51EFED00034) bool NETWORK_DO_TRANSITION_TO_NEW_GAME(bool p0, int maxPlayers, bool p2)l
extern _native64(0x3AAD8B2FCA1E289F) bool NETWORK_DO_TRANSITION_TO_FREEMODE(any* p0, any p1, bool p2, int players, bool p4)l
extern _native64(0x9E80A5BA8109F974) bool NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(any* p0, any* p1, int players, bool p3, bool p4, bool p5)l
extern _native64(0x9D7696D8F4FA6CB7) any NETWORK_IS_TRANSITION_TO_GAME()l
extern _native64(0x73B000F7FBC55829) any NETWORK_GET_TRANSITION_MEMBERS(any* p0, any p1)l
extern _native64(0x521638ADA1BA0D18) void NETWORK_APPLY_TRANSITION_PARAMETER(any p0, any p1)l
extern _native64(0xEBEFC2E77084F599) void UNK_0xEBEFC2E77084F599(any p0, const char* p1, bool p2)l
extern _native64(0x31D1D2B858D25E6B) bool NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(int* networkHandle, const char* p1, int p2, int p3, bool p4)l
extern _native64(0x5728BB6D63E3FF1D) bool NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(any* p0)l
extern _native64(0x0B824797C9BF2159) any NETWORK_IS_TRANSITION_HOST()l
extern _native64(0x6B5C83BA3EFE6A10) bool NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(int* networkHandle)l
extern _native64(0x65042B9774C4435E) bool NETWORK_GET_TRANSITION_HOST(int* networkHandle)l
extern _native64(0x68049AEFF83D8F0A) bool NETWORK_IS_IN_TRANSITION()l
extern _native64(0x53FA83401D9C07FE) bool NETWORK_IS_TRANSITION_STARTED()l
extern _native64(0x520F3282A53D26B7) any NETWORK_IS_TRANSITION_BUSY()l
extern _native64(0x292564C735375EDF) any NETWORK_IS_TRANSITION_MATCHMAKING()l
extern _native64(0xC571D0E77D8BBC29) any UNK_0xC571D0E77D8BBC29()l
extern _native64(0x2B3A8F7CA3A38FDE) void NETWORK_OPEN_TRANSITION_MATCHMAKING()l
extern _native64(0x43F4DBA69710E01E) void NETWORK_CLOSE_TRANSITION_MATCHMAKING()l
extern _native64(0x37A4494483B9F5C9) any UNK_0x37A4494483B9F5C9()l
extern _native64(0x0C978FDA19692C2C) void UNK_0x0C978FDA19692C2C(bool p0, bool p1)l
extern _native64(0xD0A484CB2F829FBE) any UNK_0xD0A484CB2F829FBE()l
extern _native64(0x30DE938B516F0AD2) void NETWORK_SET_TRANSITION_ACTIVITY_ID(any p0)l
extern _native64(0xEEEDA5E6D7080987) void NETWORK_CHANGE_TRANSITION_SLOTS(any p0, any p1)l
extern _native64(0x973D76AA760A6CB6) void UNK_0x973D76AA760A6CB6(bool p0)l
extern _native64(0x9AC9CCBFA8C29795) bool NETWORK_HAS_PLAYER_STARTED_TRANSITION(Player player)l
extern _native64(0x2615AA2A695930C1) bool NETWORK_ARE_TRANSITION_DETAILS_VALID(any p0)l
extern _native64(0x9D060B08CD63321A) bool NETWORK_JOIN_TRANSITION(Player player)l
extern _native64(0x7284A47B3540E6CF) bool NETWORK_HAS_INVITED_GAMER_TO_TRANSITION(any* p0)l
extern _native64(0x3F9990BF5F22759C) bool UNK_0x3F9990BF5F22759C(any* p0)l
extern _native64(0x05095437424397FA) bool NETWORK_IS_ACTIVITY_SESSION()l
extern _native64(0x4A9FDE3A5A6D0437) void UNK_0x4A9FDE3A5A6D0437(any p0)l
extern _native64(0xC3C7A6AFDB244624) bool _NETWORK_SEND_PRESENCE_INVITE(int* networkHandle, any* p1, any p2, any p3)l
extern _native64(0xC116FF9B4D488291) bool _NETWORK_SEND_PRESENCE_TRANSITION_INVITE(any* p0, any* p1, any p2, any p3)l
extern _native64(0x1171A97A3D3981B6) bool UNK_0x1171A97A3D3981B6(any* p0, any* p1, any p2, any p3)l
extern _native64(0x742B58F723233ED9) any UNK_0x742B58F723233ED9(any p0)l
extern _native64(0xCEFA968912D0F78D) int NETWORK_GET_NUM_PRESENCE_INVITES()l
extern _native64(0xFA91550DF9318B22) bool NETWORK_ACCEPT_PRESENCE_INVITE(any p0)l
extern _native64(0xF0210268DB0974B1) bool NETWORK_REMOVE_PRESENCE_INVITE(any p0)l
extern _native64(0xDFF09646E12EC386) any NETWORK_GET_PRESENCE_INVITE_ID(any p0)l
extern _native64(0x4962CC4AA2F345B7) any NETWORK_GET_PRESENCE_INVITE_INVITER(any p0)l
extern _native64(0x38D5B0FEBB086F75) bool NETWORK_GET_PRESENCE_INVITE_HANDLE(any p0, any* p1)l
extern _native64(0x26E1CD96B0903D60) any NETWORK_GET_PRESENCE_INVITE_SESSION_ID(any p0)l
extern _native64(0x24409FC4C55CB22D) any UNK_0x24409FC4C55CB22D(any p0)l
extern _native64(0xD39B3FFF8FFDD5BF) any UNK_0xD39B3FFF8FFDD5BF(any p0)l
extern _native64(0x728C4CC7920CD102) any UNK_0x728C4CC7920CD102(any p0)l
extern _native64(0x3DBF2DF0AEB7D289) bool UNK_0x3DBF2DF0AEB7D289(any p0)l
extern _native64(0x8806CEBFABD3CE05) bool UNK_0x8806CEBFABD3CE05(any p0)l
extern _native64(0x76D9B976C4C09FDE) bool NETWORK_HAS_FOLLOW_INVITE()l
extern _native64(0xC88156EBB786F8D5) any NETWORK_ACTION_FOLLOW_INVITE()l
extern _native64(0x439BFDE3CD0610F6) any NETWORK_CLEAR_FOLLOW_INVITE()l
extern _native64(0xEBF8284D8CADEB53) void UNK_0xEBF8284D8CADEB53()l
extern _native64(0x7524B431B2E6F7EE) void NETWORK_REMOVE_TRANSITION_INVITE(any* p0)l
extern _native64(0x726E0375C7A26368) void NETWORK_REMOVE_ALL_TRANSITION_INVITE()l
extern _native64(0xF083835B70BA9BFE) void UNK_0xF083835B70BA9BFE()l
extern _native64(0x9D80CD1D0E6327DE) bool NETWORK_INVITE_GAMERS(any* p0, any p1, any* p2, any* p3)l
extern _native64(0x4D86CD31E8976ECE) bool NETWORK_HAS_INVITED_GAMER(any* p0)l
extern _native64(0x74881E6BCAE2327C) bool NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(any* p0)l
extern _native64(0x7206F674F2A3B1BB) bool NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(any* p0)l
extern _native64(0x66F010A4B031A331) void UNK_0x66F010A4B031A331(any* p0)l
extern _native64(0x44B37CDCAE765AAE) bool UNK_0x44B37CDCAE765AAE(any p0, any* p1)l
extern _native64(0x0D77A82DC2D0DA59) void UNK_0x0D77A82DC2D0DA59(any* p0, any* p1)l
extern _native64(0xCBBD7C4991B64809) bool FILLOUT_PM_PLAYER_LIST(int* networkHandle, any p1, any p2)l
extern _native64(0x716B6DB9D1886106) bool FILLOUT_PM_PLAYER_LIST_WITH_NAMES(any* p0, any* p1, any p2, any p3)l
extern _native64(0xE26CCFF8094D8C74) bool USING_NETWORK_WEAPONTYPE(any p0)l
extern _native64(0x796A87B3B68D1F3D) bool UNK_0x796A87B3B68D1F3D(any* p0)l
extern _native64(0x2FC5650B0271CB57) any UNK_0x2FC5650B0271CB57()l
extern _native64(0x01ABCE5E7CBDA196) any UNK_0x01ABCE5E7CBDA196()l
extern _native64(0x120364DE2845DAF8) any UNK_0x120364DE2845DAF8(any* p0, any p1)l
extern _native64(0xFD8B834A8BA05048) any UNK_0xFD8B834A8BA05048()l
extern _native64(0x8DE9945BCC9AEC52) bool NETWORK_IS_CHATTING_IN_PLATFORM_PARTY(int* networkHandle)l
extern _native64(0x966C2BC2A7FE3F30) bool NETWORK_IS_IN_PARTY()l
extern _native64(0x676ED266AADD31E0) bool NETWORK_IS_PARTY_MEMBER(int* networkHandle)l
extern _native64(0x2BF66D2E7414F686) any UNK_0x2BF66D2E7414F686()l
extern _native64(0x14922ED3E38761F0) any UNK_0x14922ED3E38761F0()l
extern _native64(0xFA2888E3833C8E96) void UNK_0xFA2888E3833C8E96()l
extern _native64(0x25D990F8E0E3F13C) void UNK_0x25D990F8E0E3F13C()l
extern _native64(0x77FADDCBE3499DF7) void UNK_0x77FADDCBE3499DF7(any p0)l
extern _native64(0xF1B84178F8674195) void UNK_0xF1B84178F8674195(any p0)l
extern _native64(0x599E4FA1F87EB5FF) int NETWORK_GET_RANDOM_INT()l
extern _native64(0xE30CF56F1EFA5F43) int _NETWORK_GET_RANDOM_INT_IN_RANGE(int rangeStart, int rangeEnd)l
extern _native64(0x655B91F1495A9090) bool NETWORK_PLAYER_IS_CHEATER()l
extern _native64(0x172F75B6EE2233BA) any UNK_0x172F75B6EE2233BA()l
extern _native64(0x19D8DA0E5A68045A) bool NETWORK_PLAYER_IS_BADSPORT()l
extern _native64(0x46FB3ED415C7641C) bool UNK_0x46FB3ED415C7641C(any p0, any p1, any p2)l
extern _native64(0xEC5E3AF5289DCA81) bool BAD_SPORT_PLAYER_LEFT_DETECTED(any* p0, any p1, any p2)l
extern _native64(0xE66C690248F11150) void UNK_0xE66C690248F11150(any p0, any p1)l
extern _native64(0x1CA59E306ECB80A5) void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(int lobbySize, bool p1, int playerId)l
extern _native64(0xD1110739EEADB592) bool _NETWORK_SET_THIS_SCRIPT_MARKED(any p0, bool p1, any p2)l
extern _native64(0x2910669969E9535E) bool NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT()l
extern _native64(0xA6C90FBC38E395EE) int _NETWORK_GET_NUM_PARTICIPANTS_HOST()l
extern _native64(0x18D0456E86604654) int NETWORK_GET_NUM_PARTICIPANTS()l
extern _native64(0x57D158647A6BFABF) int NETWORK_GET_SCRIPT_STATUS()l
extern _native64(0x3E9B2F01C50DF595) void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(int* vars, int numVars)l
extern _native64(0x3364AA97340CA215) void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(int* vars, int numVars)l
extern _native64(0x64F62AFB081E260D) void UNK_0x64F62AFB081E260D()l
extern _native64(0x5D10B3795F3FC886) bool UNK_0x5D10B3795F3FC886()l
extern _native64(0x24FB80D107371267) int NETWORK_GET_PLAYER_INDEX(Player player)l
extern _native64(0x1B84DF6AF2A46938) int NETWORK_GET_PARTICIPANT_INDEX(int index)l
extern _native64(0x6C0E2E0125610278) Player NETWORK_GET_PLAYER_INDEX_FROM_PED(Ped ped)l
extern _native64(0xA4A79DD2D9600654) int NETWORK_GET_NUM_CONNECTED_PLAYERS()l
extern _native64(0x93DC1BE4E1ABE9D1) bool NETWORK_IS_PLAYER_CONNECTED(Player player)l
extern _native64(0xCF61D4B4702EE9EB) int UNK_0xCF61D4B4702EE9EB()l
extern _native64(0x6FF8FF40B6357D45) bool NETWORK_IS_PARTICIPANT_ACTIVE(any p0)l
extern _native64(0xB8DFD30D6973E135) bool NETWORK_IS_PLAYER_ACTIVE(Player player)l
extern _native64(0x3CA58F6CB7CBD784) bool NETWORK_IS_PLAYER_A_PARTICIPANT(any p0)l
extern _native64(0x83CD99A1E6061AB5) bool NETWORK_IS_HOST_OF_THIS_SCRIPT()l
extern _native64(0xC7B4D79B01FA7A5C) any NETWORK_GET_HOST_OF_THIS_SCRIPT()l
extern _native64(0x1D6A14F1F9A736FC) int NETWORK_GET_HOST_OF_SCRIPT(const char* scriptName, int p1, int p2)l
extern _native64(0x3B3D11CD9FFCDFC9) void NETWORK_SET_MISSION_FINISHED()l
extern _native64(0x9D40DF90FAD26098) bool NETWORK_IS_SCRIPT_ACTIVE(const char* scriptName, any p1, bool p2, any p3)l
extern _native64(0x3658E8CD94FC121A) int NETWORK_GET_NUM_SCRIPT_PARTICIPANTS(any* p0, any p1, any p2)l
extern _native64(0x638A3A81733086DB) any UNK_0x638A3A81733086DB()l
extern _native64(0x1AD5B71586B94820) bool UNK_0x1AD5B71586B94820(Player p0, any* p1, any p2)l
extern _native64(0x2302C0264EA58D31) void UNK_0x2302C0264EA58D31()l
extern _native64(0x741A3D8380319A81) void UNK_0x741A3D8380319A81()l
extern _native64(0x90986E8876CE0A83) Player PARTICIPANT_ID()l
extern _native64(0x57A3BDDAD8E5AA0A) int PARTICIPANT_ID_TO_INT()l
extern _native64(0x7A1ADEEF01740A24) int NETWORK_GET_DESTROYER_OF_NETWORK_ID(int netId, Hash* weaponHash)l
extern _native64(0x4CACA84440FA26F6) bool _NETWORK_GET_DESROYER_OF_ENTITY(any p0, any p1, Hash* p2)l
extern _native64(0x42B2DAA6B596F5F8) Entity NETWORK_GET_ENTITY_KILLER_OF_PLAYER(Player player, Hash* weaponHash)l
extern _native64(0xEA23C49EAA83ACFB) void NETWORK_RESURRECT_LOCAL_PLAYER(vector3 vec, float heading, bool unk, bool changetime)l
extern _native64(0x2D95C7E2D7E07307) void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(int time)l
extern _native64(0x8A8694B48715B000) bool NETWORK_IS_LOCAL_PLAYER_INVINCIBLE()l
extern _native64(0x9DD368BF06983221) void NETWORK_DISABLE_INVINCIBLE_FLASHING(int player, bool p1)l
extern _native64(0x524FF0AEFF9C3973) void UNK_0x524FF0AEFF9C3973(any p0)l
extern _native64(0xB07D3185E11657A5) bool UNK_0xB07D3185E11657A5(Entity p0)l
extern _native64(0xA11700682F3AD45C) int NETWORK_GET_NETWORK_ID_FROM_ENTITY(Entity entity)l
extern _native64(0xCE4E5D9B0A4FF560) Entity NETWORK_GET_ENTITY_FROM_NETWORK_ID(int netId)l
extern _native64(0xC7827959479DCC78) bool NETWORK_GET_ENTITY_IS_NETWORKED(Entity entity)l
extern _native64(0x0991549DE4D64762) bool NETWORK_GET_ENTITY_IS_LOCAL(Entity entity)l
extern _native64(0x06FAACD625D80CAA) void NETWORK_REGISTER_ENTITY_AS_NETWORKED(Entity entity)l
extern _native64(0x7368E683BB9038D6) void NETWORK_UNREGISTER_NETWORKED_ENTITY(Entity entity)l
extern _native64(0x38CE16C96BD11344) bool NETWORK_DOES_NETWORK_ID_EXIST(int netID)l
extern _native64(0x18A47D074708FD68) bool NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(Entity entity)l
extern _native64(0xA670B3662FAFFBD0) bool NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(int netId)l
extern _native64(0x4D36070FE0215186) bool NETWORK_HAS_CONTROL_OF_NETWORK_ID(int netId)l
extern _native64(0xB69317BF5E782347) bool NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity entity)l
extern _native64(0x870DDFD5A4A796E4) bool NETWORK_REQUEST_CONTROL_OF_DOOR(int doorID)l
extern _native64(0x01BF60A500E28887) bool NETWORK_HAS_CONTROL_OF_ENTITY(Entity entity)l
extern _native64(0x5BC9495F0B3B6FA6) bool NETWORK_HAS_CONTROL_OF_PICKUP(Pickup pickup)l
extern _native64(0xCB3C68ADB06195DF) bool NETWORK_HAS_CONTROL_OF_DOOR(int doorID)l
extern _native64(0xC01E93FAC20C3346) bool _NETWORK_HAS_CONTROL_OF_PAVEMENT_STATS(Hash hash)l
extern _native64(0xB4C94523F023419C) int VEH_TO_NET(Vehicle vehicle)l
extern _native64(0x0EDEC3C276198689) int PED_TO_NET(Ped ped)l
extern _native64(0x99BFDC94A603E541) int OBJ_TO_NET(Object object)l
extern _native64(0x367B936610BA360C) Vehicle NET_TO_VEH(int netHandle)l
extern _native64(0xBDCD95FC216A8B3E) Ped NET_TO_PED(int netHandle)l
extern _native64(0xD8515F5FEA14CB3F) Object NET_TO_OBJ(int netHandle)l
extern _native64(0xBFFEAB45A9A9094A) Entity NET_TO_ENT(int netHandle)l
extern _native64(0xE86051786B66CD8E) void NETWORK_GET_LOCAL_HANDLE(NetworkHandle* networkHandle, int bufferSize)l
extern _native64(0xDCD51DD8F87AEC5C) void NETWORK_HANDLE_FROM_USER_ID(const char* userId, NetworkHandle* networkHandle, int bufferSize)l
extern _native64(0xA0FD21BED61E5C4C) void NETWORK_HANDLE_FROM_MEMBER_ID(const char* memberId, NetworkHandle* networkHandle, int bufferSize)l
extern _native64(0x388EB2B86C73B6B3) void NETWORK_HANDLE_FROM_PLAYER(Player player, NetworkHandle* networkHandle, int bufferSize)l
extern _native64(0xBC1D768F2F5D6C05) Hash _NETWORK_HASH_FROM_PLAYER_HANDLE(Player player)l
extern _native64(0x58575AC3CF2CA8EC) Hash _NETWORK_HASH_FROM_GAMER_HANDLE(NetworkHandle* networkHandle)l
extern _native64(0xD45CB817D7E177D2) void NETWORK_HANDLE_FROM_FRIEND(Player friendIndex, NetworkHandle* networkHandle, int bufferSize)l
extern _native64(0x9F0C0A981D73FA56) bool NETWORK_GAMERTAG_FROM_HANDLE_START(NetworkHandle* networkHandle)l
extern _native64(0xB071E27958EF4CF0) bool NETWORK_GAMERTAG_FROM_HANDLE_PENDING()l
extern _native64(0xFD00798DBA7523DD) bool NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED()l
extern _native64(0x426141162EBE5CDB) const char* NETWORK_GET_GAMERTAG_FROM_HANDLE(NetworkHandle* networkHandle)l
extern _native64(0xD66C9E72B3CC4982) int UNK_0xD66C9E72B3CC4982(any* p0, any p1)l
extern _native64(0x58CC181719256197) any UNK_0x58CC181719256197(any p0, any p1, any p2)l
extern _native64(0x57DBA049E110F217) bool NETWORK_ARE_HANDLES_THE_SAME(NetworkHandle* netHandle1, NetworkHandle* netHandle2)l
extern _native64(0x6F79B93B0A8E4133) bool NETWORK_IS_HANDLE_VALID(NetworkHandle* networkHandle, int bufferSize)l
extern _native64(0xCE5F689CF5A0A49D) Player NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(NetworkHandle* networkHandle)l
extern _native64(0xC82630132081BB6F) const char* NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(NetworkHandle* networkHandle)l
extern _native64(0x0F10B05DDF8D16E9) bool NETWORK_IS_GAMER_IN_MY_SESSION(NetworkHandle* networkHandle)l
extern _native64(0x859ED1CEA343FCA8) void NETWORK_SHOW_PROFILE_UI(int* networkHandle)l
extern _native64(0x7718D2E2060837D2) const char* NETWORK_PLAYER_GET_NAME(Player player)l
extern _native64(0x4927FC39CD0869A0) const char* NETWORK_PLAYER_GET_USERID(Player player, int* userID)l
extern _native64(0x544ABDDA3B409B6D) bool NETWORK_PLAYER_IS_ROCKSTAR_DEV(Player player)l
extern _native64(0x565E430DB3B05BEC) bool UNK_0x565E430DB3B05BEC(any p0)l
extern _native64(0x7E58745504313A2E) bool NETWORK_IS_INACTIVE_PROFILE(any* p0)l
extern _native64(0xAFEBB0D5D8F687D2) int NETWORK_GET_MAX_FRIENDS()l
extern _native64(0x203F1CFD823B27A4) int NETWORK_GET_FRIEND_COUNT()l
extern _native64(0xE11EBBB2A783FE8B) const char* NETWORK_GET_FRIEND_NAME(Player player)l
extern _native64(0x4164F227D052E293) const char* _NETWORK_GET_FRIEND_NAME_FROM_INDEX(int friendIndex)l
extern _native64(0x425A44533437B64D) bool NETWORK_IS_FRIEND_ONLINE(const char* name)l
extern _native64(0x87EB7A3FFCB314DB) bool UNK_0x87EB7A3FFCB314DB(any* p0)l
extern _native64(0x2EA9A3BEDF3F17B8) bool NETWORK_IS_FRIEND_IN_SAME_TITLE(NetworkHandle* networkHandle)l
extern _native64(0x57005C18827F3A28) bool NETWORK_IS_FRIEND_IN_MULTIPLAYER(NetworkHandle* networkHandle)l
extern _native64(0x1A24A179F9B31654) bool NETWORK_IS_FRIEND(NetworkHandle* networkHandle)l
extern _native64(0x0BE73DA6984A6E33) any NETWORK_IS_PENDING_FRIEND(any p0)l
extern _native64(0x6EA101606F6E4D81) any NETWORK_IS_ADDING_FRIEND()l
extern _native64(0x8E02D73914064223) bool NETWORK_ADD_FRIEND(any* p0, const char* p1)l
extern _native64(0xBAD8F2A42B844821) bool NETWORK_IS_FRIEND_INDEX_ONLINE(int friendIndex)l
extern _native64(0x1B857666604B1A74) void UNK_0x1B857666604B1A74(bool p0)l
extern _native64(0x82377B65E943F72D) bool UNK_0x82377B65E943F72D(any p0)l
extern _native64(0xC927EC229934AF60) bool NETWORK_CAN_SET_WAYPOINT()l
extern _native64(0xB309EBEA797E001F) any UNK_0xB309EBEA797E001F(any p0)l
extern _native64(0x26F07DD83A5F7F98) any UNK_0x26F07DD83A5F7F98()l
extern _native64(0xE870F9F1F7B4F1FA) bool NETWORK_HAS_HEADSET()l
extern _native64(0x7D395EA61622E116) void UNK_0x7D395EA61622E116(bool p0)l
extern _native64(0xC0D2AF00BCC234CA) any UNK_0xC0D2AF00BCC234CA()l
extern _native64(0xF2FD55CB574BCC55) bool NETWORK_GAMER_HAS_HEADSET(any* p0)l
extern _native64(0x71C33B22606CD88A) bool NETWORK_IS_GAMER_TALKING(int* p0)l
extern _native64(0xA150A4F065806B1F) bool NETWORK_CAN_COMMUNICATE_WITH_GAMER(int* player)l
extern _native64(0xCE60DE011B6C7978) bool NETWORK_IS_GAMER_MUTED_BY_ME(int* p0)l
extern _native64(0xDF02A2C93F1F26DA) bool NETWORK_AM_I_MUTED_BY_GAMER(any* p0)l
extern _native64(0xE944C4F5AF1B5883) bool NETWORK_IS_GAMER_BLOCKED_BY_ME(any* p0)l
extern _native64(0x15337C7C268A27B2) bool NETWORK_AM_I_BLOCKED_BY_GAMER(any* p0)l
extern _native64(0xB57A49545BA53CE7) bool UNK_0xB57A49545BA53CE7(any* p0)l
extern _native64(0xCCA4318E1AB03F1F) bool UNK_0xCCA4318E1AB03F1F(any* p0)l
extern _native64(0x07DD29D5E22763F1) bool UNK_0x07DD29D5E22763F1(any* p0)l
extern _native64(0x135F9B7B7ADD2185) bool UNK_0x135F9B7B7ADD2185(any* p0)l
extern _native64(0x031E11F3D447647E) bool NETWORK_IS_PLAYER_TALKING(Player player)l
extern _native64(0x3FB99A8B08D18FD6) bool NETWORK_PLAYER_HAS_HEADSET(Player player)l
extern _native64(0x8C71288AE68EDE39) bool NETWORK_IS_PLAYER_MUTED_BY_ME(Player player)l
extern _native64(0x9D6981DFC91A8604) bool NETWORK_AM_I_MUTED_BY_PLAYER(Player player)l
extern _native64(0x57AF1F8E27483721) bool NETWORK_IS_PLAYER_BLOCKED_BY_ME(Player player)l
extern _native64(0x87F395D957D4353D) bool NETWORK_AM_I_BLOCKED_BY_PLAYER(Player player)l
extern _native64(0x21A1684A25C2867F) float NETWORK_GET_PLAYER_LOUDNESS(any p0)l
extern _native64(0xCBF12D65F95AD686) void NETWORK_SET_TALKER_PROXIMITY(float p0)l
extern _native64(0x84F0F13120B4E098) any NETWORK_GET_TALKER_PROXIMITY()l
extern _native64(0xBABEC9E69A91C57B) void NETWORK_SET_VOICE_ACTIVE(bool toggle)l
extern _native64(0xCFEB46DCD7D8D5EB) void UNK_0xCFEB46DCD7D8D5EB(bool p0)l
extern _native64(0xAF66059A131AA269) void NETWORK_OVERRIDE_TRANSITION_CHAT(bool p0)l
extern _native64(0xD5B4883AC32F24C3) void NETWORK_SET_TEAM_ONLY_CHAT(bool toggle)l
extern _native64(0x6F697A66CE78674E) void UNK_0x6F697A66CE78674E(int team, bool toggle)l
extern _native64(0x70DA3BF8DACD3210) void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(bool toggle)l
extern _native64(0x3C5C1E2C2FF814B1) void UNK_0x3C5C1E2C2FF814B1(bool p0)l
extern _native64(0x9D7AFCBF21C51712) void UNK_0x9D7AFCBF21C51712(bool p0)l
extern _native64(0xF46A1E03E8755980) void UNK_0xF46A1E03E8755980(bool p0)l
extern _native64(0x6A5D89D7769A40D8) void UNK_0x6A5D89D7769A40D8(bool p0)l
extern _native64(0x3039AE5AD2C9C0C4) void NETWORK_OVERRIDE_CHAT_RESTRICTIONS(Player player, bool toggle)l
extern _native64(0x97DD4C5944CC2E6A) void _NETWORK_OVERRIDE_SEND_RESTRICTIONS(Player player, bool toggle)l
extern _native64(0x57B192B4D4AD23D5) void UNK_0x57B192B4D4AD23D5(bool p0)l
extern _native64(0xDDF73E2B1FEC5AB4) void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(Player player, bool toggle)l
extern _native64(0x0FF2862B61A58AF9) void UNK_0x0FF2862B61A58AF9(bool p0)l
extern _native64(0xEF6212C2EFEF1A23) void NETWORK_SET_VOICE_CHANNEL(any p0)l
extern _native64(0xE036A705F989E049) void NETWORK_CLEAR_VOICE_CHANNEL()l
extern _native64(0xDBD2056652689917) bool IS_NETWORK_VEHICLE_BEEN_DAMAGED_BY_ANY_OBJECT(vector3 vec)l
extern _native64(0xF03755696450470C) void UNK_0xF03755696450470C()l
extern _native64(0x5E3AA4CA2B6FB0EE) void UNK_0x5E3AA4CA2B6FB0EE(any p0)l
extern _native64(0xCA575C391FEA25CC) void UNK_0xCA575C391FEA25CC(any p0)l
extern _native64(0xADB57E5B663CCA8B) void UNK_0xADB57E5B663CCA8B(Player p0, float* p1, float* p2)l
extern _native64(0x5FCF4D7069B09026) bool _NETWORK_IS_TEXT_CHAT_ACTIVE()l
extern _native64(0x593850C16A36B692) void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME()l
extern _native64(0xF808475FA571D823) void NETWORK_SET_FRIENDLY_FIRE_OPTION(bool toggle)l
extern _native64(0x1DCCACDCFC569362) void NETWORK_SET_RICH_PRESENCE(any p0, any p1, any p2, any p3)l
extern _native64(0x3E200C2BCF4164EB) void UNK_0x3E200C2BCF4164EB(any p0, any p1)l
extern _native64(0x5ED0356A0CE3A34F) int NETWORK_GET_TIMEOUT_TIME()l
extern _native64(0x9769F811D1785B03) void UNK_0x9769F811D1785B03(Player player, vector3 vec, bool p4, bool p5)l
extern _native64(0xBF22E0F32968E967) void UNK_0xBF22E0F32968E967(Player player, bool p1)l
extern _native64(0x715135F4B82AC90D) void UNK_0x715135F4B82AC90D(Entity entity)l
extern _native64(0x579CCED0265D4896) bool _NETWORK_PLAYER_IS_IN_CLAN()l
extern _native64(0xB124B57F571D8F18) bool NETWORK_CLAN_PLAYER_IS_ACTIVE(NetworkHandle* networkHandle)l
extern _native64(0xEEE6EACBE8874FBA) bool NETWORK_CLAN_PLAYER_GET_DESC(int* clanDesc, int bufferSize, NetworkHandle* networkHandle)l
extern _native64(0x7543BB439F63792B) bool UNK_0x7543BB439F63792B(int* clanDesc, int bufferSize)l
extern _native64(0xF45352426FF3A4F0) void UNK_0xF45352426FF3A4F0(int* clanDesc, int bufferSize, NetworkHandle* networkHandle)l
extern _native64(0x1F471B79ACC90BEF) int _GET_NUM_MEMBERSHIP_DESC()l
extern _native64(0x48DE78AF2C8885B8) bool NETWORK_CLAN_GET_MEMBERSHIP_DESC(int* memberDesc, int p1)l
extern _native64(0xA989044E70010ABE) bool NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(NetworkHandle* networkHandle)l
extern _native64(0x5B9E023DC6EBEDC0) bool NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(any* p0)l
extern _native64(0xB3F64A6A91432477) bool _NETWORK_IS_CLAN_MEMBERSHIP_FINISHED_DOWNLOADING()l
extern _native64(0xBB6E6FEE99D866B2) bool NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE(int* p0)l
extern _native64(0xAAB11F6C4ADBC2C1) int NETWORK_CLAN_GET_MEMBERSHIP_COUNT(int* p0)l
extern _native64(0x48A59CF88D43DF0E) bool NETWORK_CLAN_GET_MEMBERSHIP_VALID(int* p0, any p1)l
extern _native64(0xC8BC2011F67B3411) bool NETWORK_CLAN_GET_MEMBERSHIP(int* p0, int* clanMembership, int p2)l
extern _native64(0x9FAAA4F4FC71F87F) bool NETWORK_CLAN_JOIN(int clanDesc)l
extern _native64(0x729E3401F0430686) bool _NETWORK_CLAN_ANIMATION(const char* animDict, const char* animName)l
extern _native64(0x2B51EDBEFC301339) bool UNK_0x2B51EDBEFC301339(int p0, const char* p1)l
extern _native64(0xC32EA7A2F6CA7557) any UNK_0xC32EA7A2F6CA7557()l
extern _native64(0x5835D9CD92E83184) bool UNK_0x5835D9CD92E83184(any* p0, any* p1)l
extern _native64(0x13518FF1C6B28938) bool UNK_0x13518FF1C6B28938(any p0)l
extern _native64(0xA134777FF7F33331) bool UNK_0xA134777FF7F33331(any p0, any* p1)l
extern _native64(0x113E6E3E50E286B0) void UNK_0x113E6E3E50E286B0(any p0)l
extern _native64(0x9AA46BADAD0E27ED) any NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR()l
extern _native64(0x042E4B70B93E6054) void NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL()l
extern _native64(0xCE86D8191B762107) bool NETWORK_GET_PRIMARY_CLAN_DATA_START(any* p0, any p1)l
extern _native64(0xB5074DB804E28CE7) any NETWORK_GET_PRIMARY_CLAN_DATA_PENDING()l
extern _native64(0x5B4F04F19376A0BA) any NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS()l
extern _native64(0xC080FF658B2E41DA) bool NETWORK_GET_PRIMARY_CLAN_DATA_NEW(any* p0, any* p1)l
extern _native64(0x299EEB23175895FC) void SET_NETWORK_ID_CAN_MIGRATE(int netId, bool toggle)l
extern _native64(0xE05E81A888FA63C8) void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int netId, bool toggle)l
extern _native64(0xA8A024587329F36A) void _SET_NETWORK_ID_SYNC_TO_PLAYER(int netId, Player player, bool toggle)l
extern _native64(0xD830567D88A1E873) void NETWORK_SET_ENTITY_CAN_BLEND(Entity entity, bool toggle)l
extern _native64(0xF1CA12B18AEF5298) void _NETWORK_SET_ENTITY_VISIBLE_TO_NETWORK(Entity entity, bool toggle)l
extern _native64(0xA6928482543022B4) void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(int netId, bool p1, bool p2)l
extern _native64(0xAAA553E7DD28A457) void UNK_0xAAA553E7DD28A457(bool p0)l
extern _native64(0x3FA36981311FA4FF) void UNK_0x3FA36981311FA4FF(int netId, bool state)l
extern _native64(0xA1607996431332DF) bool UNK_0xA1607996431332DF(int netId)l
extern _native64(0xD1065D68947E7B6E) void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(bool p0, bool p1)l
extern _native64(0xE5F773C1A1D9D168) void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(bool p0)l
extern _native64(0x7619364C82D3BF14) void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(bool p0)l
extern _native64(0x12B37D54667DB0B8) void SET_PLAYER_INVISIBLE_LOCALLY(Player player, bool toggle)l
extern _native64(0xFAA10F1FAFB11AF2) void SET_PLAYER_VISIBLE_LOCALLY(Player player, bool toggle)l
extern _native64(0x416DBD4CD6ED8DD2) void FADE_OUT_LOCAL_PLAYER(bool p0)l
extern _native64(0xDE564951F95E09ED) void NETWORK_FADE_OUT_ENTITY(Entity entity, bool normal, bool slow)l
extern _native64(0x1F4ED342ACEFE62D) void NETWORK_FADE_IN_ENTITY(Entity entity, bool state, bool fast)l
extern _native64(0x631DC5DFF4B110E3) bool UNK_0x631DC5DFF4B110E3(any p0)l
extern _native64(0x422F32CC7E56ABAD) bool UNK_0x422F32CC7E56ABAD(any p0)l
extern _native64(0xE73092F4157CD126) bool IS_PLAYER_IN_CUTSCENE(Player player)l
extern _native64(0xE0031D3C8F36AB82) void SET_ENTITY_VISIBLE_IN_CUTSCENE(any p0, bool p1, bool p2)l
extern _native64(0xE135A9FF3F5D05D8) void SET_ENTITY_LOCALLY_INVISIBLE(Entity entity)l
extern _native64(0x241E289B5C059EDC) void SET_ENTITY_LOCALLY_VISIBLE(Entity entity)l
extern _native64(0x6E192E33AD436366) bool IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(int netID)l
extern _native64(0xD45B1FFCCD52FF19) void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(int netID, bool p1)l
extern _native64(0xD82CF8E64C8729D8) bool IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(float p0, float p1, float p2, float p3)l
extern _native64(0xDC3A310219E5DA62) bool IS_SPHERE_VISIBLE_TO_PLAYER(any p0, float p1, float p2, float p3, float p4)l
extern _native64(0x4E5C93BD0C32FBF8) void RESERVE_NETWORK_MISSION_OBJECTS(int p0)l
extern _native64(0xB60FEBA45333D36F) void RESERVE_NETWORK_MISSION_PEDS(int p0)l
extern _native64(0x76B02E21ED27A469) void RESERVE_NETWORK_MISSION_VEHICLES(int p0)l
extern _native64(0x800DD4721A8B008B) bool CAN_REGISTER_MISSION_OBJECTS(int p0)l
extern _native64(0xBCBF4FEF9FA5D781) bool CAN_REGISTER_MISSION_PEDS(int p0)l
extern _native64(0x7277F1F2E085EE74) bool CAN_REGISTER_MISSION_VEHICLES(int p0)l
extern _native64(0x69778E7564BADE6D) bool CAN_REGISTER_MISSION_ENTITIES(int p0, any p1, any p2, any p3)l
extern _native64(0xAA81B5F10BC43AC2) int GET_NUM_RESERVED_MISSION_OBJECTS(bool p0)l
extern _native64(0x1F13D5AE5CB17E17) int GET_NUM_RESERVED_MISSION_PEDS(bool p0)l
extern _native64(0xCF3A965906452031) int GET_NUM_RESERVED_MISSION_VEHICLES(bool p0)l
extern _native64(0x12B6281B6C6706C0) int UNK_0x12B6281B6C6706C0(bool p0)l
extern _native64(0xCB215C4B56A7FAE7) int UNK_0xCB215C4B56A7FAE7(bool p0)l
extern _native64(0x0CD9AB83489430EA) int UNK_0x0CD9AB83489430EA(bool p0)l
extern _native64(0xC7BE335216B5EC7C) any UNK_0xC7BE335216B5EC7C()l
extern _native64(0x0C1F7D49C39D2289) any UNK_0x0C1F7D49C39D2289()l
extern _native64(0x0AFCE529F69B21FF) any UNK_0x0AFCE529F69B21FF()l
extern _native64(0xA72835064DD63E4C) any UNK_0xA72835064DD63E4C()l
extern _native64(0x7A5487FE9FAA6B48) int GET_NETWORK_TIME()l
extern _native64(0x89023FBBF9200E9F) int UNK_0x89023FBBF9200E9F()l
extern _native64(0x46718ACEEDEAFC84) bool HAS_NETWORK_TIME_STARTED()l
extern _native64(0x017008CCDAD48503) int GET_TIME_OFFSET(int timeA, int timeB)l
extern _native64(0xCB2CF5148012C8D0) bool IS_TIME_LESS_THAN(int timeA, int timeB)l
extern _native64(0xDE350F8651E4346C) bool IS_TIME_MORE_THAN(int timeA, int timeB)l
extern _native64(0xF5BC95857BD6D512) bool IS_TIME_EQUAL_TO(int timeA, int timeB)l
extern _native64(0xA2C6FC031D46FFF0) int GET_TIME_DIFFERENCE(int timeA, int timeB)l
extern _native64(0x9E23B1777A927DAD) const char* GET_TIME_AS_STRING(int time)l
extern _native64(0x9A73240B49945C76) int _GET_POSIX_TIME()l
extern _native64(0xAC97AF97FA68E5D5) void _GET_DATE_AND_TIME_FROM_UNIX_EPOCH(int unixEpoch, any* timeStructure)l
extern _native64(0x423DE3854BB50894) void NETWORK_SET_IN_SPECTATOR_MODE(bool toggle, Ped playerPed)l
extern _native64(0x419594E137637120) void UNK_0x419594E137637120(bool p0, any p1, bool p2)l
extern _native64(0xFC18DB55AE19E046) void UNK_0xFC18DB55AE19E046(bool p0)l
extern _native64(0x5C707A667DF8B9FA) void UNK_0x5C707A667DF8B9FA(bool p0, any p1)l
extern _native64(0x048746E388762E11) bool NETWORK_IS_IN_SPECTATOR_MODE()l
extern _native64(0x9CA5DE655269FEC4) void NETWORK_SET_IN_MP_CUTSCENE(bool p0, bool p1)l
extern _native64(0x6CC27C9FA2040220) bool NETWORK_IS_IN_MP_CUTSCENE()l
extern _native64(0x63F9EE203C3619F2) bool NETWORK_IS_PLAYER_IN_MP_CUTSCENE(Player player)l
extern _native64(0xEC51713AB6EC36E8) void SET_NETWORK_VEHICLE_RESPOT_TIMER(int netId, any p1)l
extern _native64(0x6274C4712850841E) void UNK_0x6274C4712850841E(Entity entity, bool p1)l
extern _native64(0x5FFE9B4144F9712F) void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(bool toggle)l
extern _native64(0x21D04D7BC538C146) bool UNK_0x21D04D7BC538C146(any p0)l
extern _native64(0x77758139EC9B66C7) void UNK_0x77758139EC9B66C7(bool p0)l
extern _native64(0x7CD6BC4C2BBDD526) int NETWORK_CREATE_SYNCHRONISED_SCENE(vector3 vec, vector3 Rot, int p6, bool p7, bool p8, float p9,  int,  float)l
extern _native64(0x742A637471BCECD9) void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Ped ped, int netScene, const char* animDict, const char* animnName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, int p9)l
extern _native64(0xF2404D68CBC855FA) void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag)l
extern _native64(0xCF8BD3B0BD6D42D7) void _NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA(int netScene, const char* animDict, const char* animName)l
extern _native64(0x478DCBD2A98B705A) void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(int netScene, Entity entity, int bone)l
extern _native64(0x9A1B3FCDB36C8697) void NETWORK_START_SYNCHRONISED_SCENE(int netScene)l
extern _native64(0xC254481A4574CB2F) void NETWORK_STOP_SYNCHRONISED_SCENE(int netScene)l
extern _native64(0x02C40BF885C567B6) int _NETWORK_UNLINK_NETWORKED_SYNCHRONISED_SCENE(int netScene)l
extern _native64(0xC9B43A33D09CADA7) void UNK_0xC9B43A33D09CADA7(any p0)l
extern _native64(0xFB1F9381E80FA13F) any UNK_0xFB1F9381E80FA13F(int p0, any p1)l
extern _native64(0x5A6FFA2433E2F14C) bool UNK_0x5A6FFA2433E2F14C(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, int flags)l
extern _native64(0x4BA92A18502BCA61) bool UNK_0x4BA92A18502BCA61(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, int flags)l
extern _native64(0x3C891A251567DFCE) any UNK_0x3C891A251567DFCE(any* p0)l
extern _native64(0xFB8F2A6F3DF08CBE) void UNK_0xFB8F2A6F3DF08CBE()l
extern _native64(0x371EA43692861CF1) void NETWORK_GET_RESPAWN_RESULT(int randomInt, vector3* coordinates, float* heading)l
extern _native64(0x6C34F1208B8923FD) any UNK_0x6C34F1208B8923FD(any p0)l
extern _native64(0x17E0198B3882C2CB) void UNK_0x17E0198B3882C2CB()l
extern _native64(0xFB680D403909DC70) void UNK_0xFB680D403909DC70(any p0, any p1)l
extern _native64(0xD0AFAFF5A51D72F7) void NETWORK_END_TUTORIAL_SESSION()l
extern _native64(0xADA24309FE08DACF) any NETWORK_IS_IN_TUTORIAL_SESSION()l
extern _native64(0xB37E4E6A2388CA7B) any UNK_0xB37E4E6A2388CA7B()l
extern _native64(0x35F0B98A8387274D) any UNK_0x35F0B98A8387274D()l
extern _native64(0x3B39236746714134) any UNK_0x3B39236746714134(any p0)l
extern _native64(0x9DE986FC9A87C474) bool _NETWORK_IS_PLAYER_EQUAL_TO_INDEX(Player player, int index)l
extern _native64(0xBBDF066252829606) void UNK_0xBBDF066252829606(any p0, bool p1)l
extern _native64(0x919B3C98ED8292F9) bool UNK_0x919B3C98ED8292F9(any p0)l
extern _native64(0xE679E3E06E363892) void NETWORK_OVERRIDE_CLOCK_TIME(int Hours, int Minutes, int Seconds)l
extern _native64(0xD972DF67326F966E) void UNK_0xD972DF67326F966E()l
extern _native64(0xD7C95D322FF57522) any UNK_0xD7C95D322FF57522()l
extern _native64(0x494C8FB299290269) any NETWORK_ADD_ENTITY_AREA(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native64(0x376C6375BA60293A) any _NETWORK_ADD_ENTITY_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native64(0x25B99872D588A101) any UNK_0x25B99872D588A101(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native64(0x93CF869BAA0C4874) bool NETWORK_REMOVE_ENTITY_AREA(any p0)l
extern _native64(0xE64A3CA08DFA37A9) bool UNK_0xE64A3CA08DFA37A9(any p0)l
extern _native64(0x4DF7CFFF471A7FB1) bool UNK_0x4DF7CFFF471A7FB1(any p0)l
extern _native64(0x4A2D4E8BF4265B0F) bool UNK_0x4A2D4E8BF4265B0F(any p0)l
extern _native64(0x2B1813ABA29016C5) void _NETWORK_SET_NETWORK_ID_DYNAMIC(int netID, bool toggle)l
extern _native64(0x924426BFFD82E915) bool _NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS()l
extern _native64(0x8132C0EB8B2B3293) bool _HAS_BG_SCRIPT_BEEN_DOWNLOADED()l
extern _native64(0x42FB3B532D526E6C) void NETWORK_REQUEST_CLOUD_TUNABLES()l
extern _native64(0x0467C11ED88B7D28) bool _HAS_TUNABLES_BEEN_DOWNLOADED()l
extern _native64(0x10BD227A753B0D84) any UNK_0x10BD227A753B0D84()l
extern _native64(0x85E5F8B9B898B20A) bool NETWORK_DOES_TUNABLE_EXIST(const char* tunableContext, const char* tunableName)l
extern _native64(0x8BE1146DFD5D4468) bool NETWORK_ACCESS_TUNABLE_INT(const char* tunableContext, const char* tunableName, int* value)l
extern _native64(0xE5608CA7BC163A5F) bool NETWORK_ACCESS_TUNABLE_FLOAT(const char* tunableContext, const char* tunableName, float* value)l
extern _native64(0xAA6A47A573ABB75A) bool NETWORK_ACCESS_TUNABLE_BOOL(const char* tunableContext, const char* tunableName)l
extern _native64(0xE4E53E1419D81127) bool _NETWORK_DOES_TUNABLE_EXIST_HASH(Hash tunbaleContext, Hash tunableName)l
extern _native64(0x40FCE03E50E8DBE8) bool _NETWORK_ACCESS_TUNABLE_INT_HASH(Hash tunableContext, Hash tunableName, int* value)l
extern _native64(0x972BC203BBC4C4D5) bool _NETWORK_ACCESS_TUNABLE_FLOAT_HASH(Hash tunableContext, Hash tunableName, float* value)l
extern _native64(0xEA16B69D93D71A45) bool _NETWORK_ACCESS_TUNABLE_BOOL_HASH(Hash tunableContext, Hash tunableName)l
extern _native64(0xC7420099936CE286) bool _NETWORK_ACCESS_TUNABLE_BOOL_HASH_FAIL_VAL(Hash tunableContext, Hash tunableName, bool defaultValue)l
extern _native64(0x187382F8A3E0A6C3) int _GET_TUNABLES_CONTENT_MODIFIER_ID(Hash contentHash)l
extern _native64(0x7DB53B37A2F211A0) any UNK_0x7DB53B37A2F211A0()l
extern _native64(0x72433699B4E6DD64) void NETWORK_RESET_BODY_TRACKER()l
extern _native64(0xD38C4A6D047C019D) any UNK_0xD38C4A6D047C019D()l
extern _native64(0x2E0BF682CC778D49) bool UNK_0x2E0BF682CC778D49(any p0)l
extern _native64(0x0EDE326D47CD0F3E) bool UNK_0x0EDE326D47CD0F3E(Ped ped, Player player)l
extern _native64(0x301A42153C9AD707) any NETWORK_EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible, bool p3)l
extern _native64(0xCD71A4ECAB22709E) void UNK_0xCD71A4ECAB22709E(Entity entity)l
extern _native64(0xA7E30DE9272B6D49) void UNK_0xA7E30DE9272B6D49(Ped ped, vector3 vec, float p4)l
extern _native64(0x407091CF6037118E) void UNK_0x407091CF6037118E(int netID)l
extern _native64(0x1775961C2FBBCB5C) void NETWORK_SET_PROPERTY_ID(any p0)l
extern _native64(0xC2B82527CA77053E) void NETWORK_CLEAR_PROPERTY_ID()l
extern _native64(0x367EF5E2F439B4C6) void UNK_0x367EF5E2F439B4C6(int p0)l
extern _native64(0x94538037EE44F5CF) void UNK_0x94538037EE44F5CF(bool p0)l
extern _native64(0xBD0BE0BFC927EAC1) void UNK_0xBD0BE0BFC927EAC1()l
extern _native64(0x237D5336A9A54108) bool UNK_0x237D5336A9A54108(any p0)l
extern _native64(0x99B72C7ABDE5C910) bool UNK_0x99B72C7ABDE5C910(Ped ped, Player player)l
extern _native64(0xF2EAC213D5EA0623) any UNK_0xF2EAC213D5EA0623()l
extern _native64(0xEA14EEF5B7CD2C30) any UNK_0xEA14EEF5B7CD2C30()l
extern _native64(0xB606E6CC59664972) void UNK_0xB606E6CC59664972(any p0)l
extern _native64(0x1D4DC17C38FEAFF0) any UNK_0x1D4DC17C38FEAFF0()l
extern _native64(0x662635855957C411) any UNK_0x662635855957C411(any p0)l
extern _native64(0xB4271092CA7EDF48) any UNK_0xB4271092CA7EDF48(any p0)l
extern _native64(0xCA94551B50B4932C) any UNK_0xCA94551B50B4932C(any p0)l
extern _native64(0x2A7776C709904AB0) any UNK_0x2A7776C709904AB0(any p0)l
extern _native64(0x6F44CBF56D79FAC0) any UNK_0x6F44CBF56D79FAC0(any p0, any p1)l
extern _native64(0x58C21165F6545892) void UNK_0x58C21165F6545892(any p0, any p1)l
extern _native64(0x2EAC52B4019E2782) any UNK_0x2EAC52B4019E2782()l
extern _native64(0x9641A9FF718E9C5E) void SET_STORE_ENABLED(bool toggle)l
extern _native64(0xA2F952104FC6DD4B) bool UNK_0xA2F952104FC6DD4B(any p0)l
extern _native64(0x72D0706CD6CCDB58) void UNK_0x72D0706CD6CCDB58()l
extern _native64(0x722F5D28B61C5EA8) any UNK_0x722F5D28B61C5EA8(any p0)l
extern _native64(0x883D79C4071E18B3) any UNK_0x883D79C4071E18B3()l
extern _native64(0x265635150FB0D82E) void UNK_0x265635150FB0D82E()l
extern _native64(0x444C4525ECE0A4B9) void UNK_0x444C4525ECE0A4B9()l
extern _native64(0x59328EB08C5CEB2B) any UNK_0x59328EB08C5CEB2B()l
extern _native64(0xFAE628F1E9ADB239) void UNK_0xFAE628F1E9ADB239(any p0, any p1, any p2)l
extern _native64(0xC64DED7EF0D2FE37) any UNK_0xC64DED7EF0D2FE37(any* p0)l
extern _native64(0x4C61B39930D045DA) bool UNK_0x4C61B39930D045DA(any p0)l
extern _native64(0x3A3D5568AF297CD5) bool UNK_0x3A3D5568AF297CD5(any p0)l
extern _native64(0x4F18196C8D38768D) void _DOWNLOAD_CHECK()l
extern _native64(0xC7ABAC5DE675EE3B) any UNK_0xC7ABAC5DE675EE3B()l
extern _native64(0x0B0CC10720653F3B) any NETWORK_ENABLE_MOTION_DRUGGED()l
extern _native64(0x8B0C2964BA471961) any UNK_0x8B0C2964BA471961()l
extern _native64(0x88B588B41FF7868E) any UNK_0x88B588B41FF7868E()l
extern _native64(0x67FC09BC554A75E5) any UNK_0x67FC09BC554A75E5()l
extern _native64(0x966DD84FB6A46017) void UNK_0x966DD84FB6A46017()l
extern _native64(0x152D90E4C1B4738A) bool UNK_0x152D90E4C1B4738A(any* p0, any* p1)l
extern _native64(0x9FEDF86898F100E9) any UNK_0x9FEDF86898F100E9()l
extern _native64(0x5E24341A7F92A74B) any UNK_0x5E24341A7F92A74B()l
extern _native64(0x24E4E51FC16305F9) any UNK_0x24E4E51FC16305F9()l
extern _native64(0xFBC5E768C7A77A6A) any UNK_0xFBC5E768C7A77A6A()l
extern _native64(0xC55A0B40FFB1ED23) any UNK_0xC55A0B40FFB1ED23()l
extern _native64(0x17440AA15D1D3739) void UNK_0x17440AA15D1D3739()l
extern _native64(0x9BF438815F5D96EA) bool UNK_0x9BF438815F5D96EA(any p0, any p1, any* p2, any p3, any p4, any p5)l
extern _native64(0x692D58DF40657E8C) bool UNK_0x692D58DF40657E8C(any p0, any p1, any p2, any* p3, any p4, bool p5)l
extern _native64(0x158EC424F35EC469) bool UNK_0x158EC424F35EC469(any* p0, bool p1, any* p2)l
extern _native64(0xC7397A83F7A2A462) bool UNK_0xC7397A83F7A2A462(any* p0, any p1, bool p2, any* p3)l
extern _native64(0x6D4CB481FAC835E8) bool UNK_0x6D4CB481FAC835E8(any p0, any p1, any* p2, any p3)l
extern _native64(0xD5A4B59980401588) bool UNK_0xD5A4B59980401588(any p0, any p1, any* p2, any* p3)l
extern _native64(0x3195F8DD0D531052) bool UNK_0x3195F8DD0D531052(any p0, any p1, any* p2, any* p3)l
extern _native64(0xF9E1CCAE8BA4C281) bool UNK_0xF9E1CCAE8BA4C281(any p0, any p1, any* p2, any* p3)l
extern _native64(0x9F6E2821885CAEE2) bool UNK_0x9F6E2821885CAEE2(any p0, any p1, any p2, any* p3, any* p4)l
extern _native64(0x678BB03C1A3BD51E) bool UNK_0x678BB03C1A3BD51E(any p0, any p1, any p2, any* p3, any* p4)l
extern _native64(0x815E5E3073DA1D67) bool SET_BALANCE_ADD_MACHINE(any* p0, any* p1)l
extern _native64(0xB8322EEB38BE7C26) bool SET_BALANCE_ADD_MACHINES(any* p0, any p1, any* p2)l
extern _native64(0xA7862BC5ED1DFD7E) bool UNK_0xA7862BC5ED1DFD7E(any p0, any p1, any* p2, any* p3)l
extern _native64(0x97A770BEEF227E2B) bool NETWORK_GET_BACKGROUND_LOADING_RECIPIENTS(any p0, any p1, any* p2, any* p3)l
extern _native64(0x5324A0E3E4CE3570) bool UNK_0x5324A0E3E4CE3570(any p0, any p1, any* p2, any* p3)l
extern _native64(0xE9B99B6853181409) void UNK_0xE9B99B6853181409()l
extern _native64(0xD53ACDBEF24A46E8) any UNK_0xD53ACDBEF24A46E8()l
extern _native64(0x02ADA21EA2F6918F) any UNK_0x02ADA21EA2F6918F()l
extern _native64(0x941E5306BCD7C2C7) any UNK_0x941E5306BCD7C2C7()l
extern _native64(0xC87E740D9F3872CC) any UNK_0xC87E740D9F3872CC()l
extern _native64(0xEDF7F927136C224B) any UNK_0xEDF7F927136C224B()l
extern _native64(0xE0A6138401BCB837) any UNK_0xE0A6138401BCB837()l
extern _native64(0x769951E2455E2EB5) any UNK_0x769951E2455E2EB5()l
extern _native64(0x3A17A27D75C74887) any UNK_0x3A17A27D75C74887()l
extern _native64(0xBA96394A0EECFA65) void UNK_0xBA96394A0EECFA65()l
extern _native64(0xCD67AD041A394C9C) const char* _GET_CONTENT_USER_ID(int p0)l
extern _native64(0x584770794D758C18) bool UNK_0x584770794D758C18(any p0, any* p1)l
extern _native64(0x8C8D2739BA44AF0F) bool UNK_0x8C8D2739BA44AF0F(any p0)l
extern _native64(0x703F12425ECA8BF5) any UNK_0x703F12425ECA8BF5(any p0)l
extern _native64(0xAEAB987727C5A8A4) bool UNK_0xAEAB987727C5A8A4(any p0)l
extern _native64(0xA7BAB11E7C9C6C5A) int _GET_CONTENT_CATEGORY(int p0)l
extern _native64(0x55AA95F481D694D2) const char* _GET_CONTENT_ID(any p0)l
extern _native64(0xC0173D6BFF4E0348) const char* _GET_ROOT_CONTENT_ID(any p0)l
extern _native64(0xBF09786A7FCAB582) any UNK_0xBF09786A7FCAB582(any p0)l
extern _native64(0x7CF0448787B23758) int _GET_CONTENT_DESCRIPTION_HASH(any p0)l
extern _native64(0xBAF6BABF9E7CCC13) any UNK_0xBAF6BABF9E7CCC13(any p0, any p1)l
extern _native64(0xCFD115B373C0DF63) void UNK_0xCFD115B373C0DF63(any p0, any* p1)l
extern _native64(0x37025B27D9B658B1) any _GET_CONTENT_FILE_VERSION(any p0, any p1)l
extern _native64(0x1D610EB0FEA716D9) bool UNK_0x1D610EB0FEA716D9(any p0)l
extern _native64(0x7FCC39C46C3C03BD) bool UNK_0x7FCC39C46C3C03BD(any p0)l
extern _native64(0x32DD916F3F7C9672) any UNK_0x32DD916F3F7C9672(any p0)l
extern _native64(0x3054F114121C21EA) bool UNK_0x3054F114121C21EA(any p0)l
extern _native64(0xA9240A96C74CCA13) bool UNK_0xA9240A96C74CCA13(any p0)l
extern _native64(0x1ACCFBA3D8DAB2EE) any UNK_0x1ACCFBA3D8DAB2EE(any p0, any p1)l
extern _native64(0x759299C5BB31D2A9) any UNK_0x759299C5BB31D2A9(any p0, any p1)l
extern _native64(0x87E5C46C187FE0AE) any UNK_0x87E5C46C187FE0AE(any p0, any p1)l
extern _native64(0x4E548C0D7AE39FF9) any UNK_0x4E548C0D7AE39FF9(any p0, any p1)l
extern _native64(0x70EA8DA57840F9BE) bool UNK_0x70EA8DA57840F9BE(any p0)l
extern _native64(0x993CBE59D350D225) bool UNK_0x993CBE59D350D225(any p0)l
extern _native64(0x171DF6A0C07FB3DC) any UNK_0x171DF6A0C07FB3DC(any p0, any p1)l
extern _native64(0x7FD2990AF016795E) any UNK_0x7FD2990AF016795E(any* p0, any* p1, any p2, any p3, any p4)l
extern _native64(0x5E0165278F6339EE) any UNK_0x5E0165278F6339EE(any p0)l
extern _native64(0x2D5DC831176D0114) bool UNK_0x2D5DC831176D0114(any p0)l
extern _native64(0xEBFA8D50ADDC54C4) bool UNK_0xEBFA8D50ADDC54C4(any p0)l
extern _native64(0x162C23CA83ED0A62) bool UNK_0x162C23CA83ED0A62(any p0)l
extern _native64(0x40F7E66472DF3E5C) any UNK_0x40F7E66472DF3E5C(any p0, any p1)l
extern _native64(0x5A34CD9C3C5BEC44) bool UNK_0x5A34CD9C3C5BEC44(any p0)l
extern _native64(0x68103E2247887242) void UNK_0x68103E2247887242()l
extern _native64(0x1DE0F5F50D723CAA) bool UNK_0x1DE0F5F50D723CAA(any* p0, any* p1, any* p2)l
extern _native64(0x274A1519DFC1094F) bool UNK_0x274A1519DFC1094F(any* p0, bool p1, any* p2)l
extern _native64(0xD05D1A6C74DA3498) bool UNK_0xD05D1A6C74DA3498(any* p0, bool p1, any* p2)l
extern _native64(0x45E816772E93A9DB) any UNK_0x45E816772E93A9DB()l
extern _native64(0x299EF3C576773506) any UNK_0x299EF3C576773506()l
extern _native64(0x793FF272D5B365F4) any UNK_0x793FF272D5B365F4()l
extern _native64(0x5A0A3D1A186A5508) any UNK_0x5A0A3D1A186A5508()l
extern _native64(0xA1E5E0204A6FCC70) void UNK_0xA1E5E0204A6FCC70()l
extern _native64(0xB746D20B17F2A229) bool UNK_0xB746D20B17F2A229(any* p0, any* p1)l
extern _native64(0x63B406D7884BFA95) any UNK_0x63B406D7884BFA95()l
extern _native64(0x4D02279C83BE69FE) any UNK_0x4D02279C83BE69FE()l
extern _native64(0x597F8DBA9B206FC7) any UNK_0x597F8DBA9B206FC7()l
extern _native64(0x5CAE833B0EE0C500) bool UNK_0x5CAE833B0EE0C500(any p0)l
extern _native64(0x61A885D3F7CFEE9A) void UNK_0x61A885D3F7CFEE9A()l
extern _native64(0xF98DDE0A8ED09323) void UNK_0xF98DDE0A8ED09323(bool p0)l
extern _native64(0xFD75DABC0957BF33) void UNK_0xFD75DABC0957BF33(bool p0)l
extern _native64(0xF53E48461B71EECB) bool UNK_0xF53E48461B71EECB(any p0)l
extern _native64(0x098AB65B9ED9A9EC) bool UNK_0x098AB65B9ED9A9EC(any* p0, any p1, any p2)l
extern _native64(0xDC48473142545431) any UNK_0xDC48473142545431()l
extern _native64(0x0AE1F1653B554AB9) bool UNK_0x0AE1F1653B554AB9(any p0)l
extern _native64(0x62B9FEC9A11F10EF) any UNK_0x62B9FEC9A11F10EF()l
extern _native64(0xA75E2B6733DA5142) any UNK_0xA75E2B6733DA5142()l
extern _native64(0x43865688AE10F0D7) any UNK_0x43865688AE10F0D7()l
extern _native64(0x16160DA74A8E74A2) int TEXTURE_DOWNLOAD_REQUEST(int* PlayerHandle, const char* FilePath, const char* Name, bool p3)l
extern _native64(0x0B203B4AFDE53A4F) any UNK_0x0B203B4AFDE53A4F(any* p0, any* p1, bool p2)l
extern _native64(0x308F96458B7087CC) any UNK_0x308F96458B7087CC(any* p0, any p1, any p2, any p3, any* p4, bool p5)l
extern _native64(0x487EB90B98E9FB19) void TEXTURE_DOWNLOAD_RELEASE(int p0)l
extern _native64(0x5776ED562C134687) bool TEXTURE_DOWNLOAD_HAS_FAILED(int p0)l
extern _native64(0x3448505B6E35262D) const char* TEXTURE_DOWNLOAD_GET_NAME(int p0)l
extern _native64(0x8BD6C6DEA20E82C6) any UNK_0x8BD6C6DEA20E82C6(any p0)l
extern _native64(0x60EDD13EB3AC1FF3) any UNK_0x60EDD13EB3AC1FF3()l
extern _native64(0xEFFB25453D8600F9) bool NETWORK_IS_CABLE_CONNECTED()l
extern _native64(0x66B59CFFD78467AF) any UNK_0x66B59CFFD78467AF()l
extern _native64(0x606E4D3E3CCCF3EB) any UNK_0x606E4D3E3CCCF3EB()l
extern _native64(0x8020A73847E0CA7D) bool _IS_ROCKSTAR_BANNED()l
extern _native64(0xA0AD7E2AF5349F61) bool _IS_SOCIALCLUB_BANNED()l
extern _native64(0x5F91D5D0B36AA310) bool _CAN_PLAY_ONLINE()l
extern _native64(0x422D396F80A96547) any UNK_0x422D396F80A96547()l
extern _native64(0xA699957E60D80214) bool UNK_0xA699957E60D80214(any p0)l
extern _native64(0xC22912B1D85F26B1) bool UNK_0xC22912B1D85F26B1(any p0, any* p1, any* p2)l
extern _native64(0x593570C289A77688) any UNK_0x593570C289A77688()l
extern _native64(0x91B87C55093DE351) any UNK_0x91B87C55093DE351()l
extern _native64(0x36391F397731595D) any UNK_0x36391F397731595D(any p0)l
extern _native64(0xDEB2B99A1AF1A2A6) any UNK_0xDEB2B99A1AF1A2A6(any p0)l
extern _native64(0x9465E683B12D3F6B) void UNK_0x9465E683B12D3F6B()l
extern _native64(0xB7C7F6AD6424304B) void UNK_0xB7C7F6AD6424304B()l
extern _native64(0xC505036A35AFD01B) void UNK_0xC505036A35AFD01B(bool p0)l
extern _native64(0x267C78C60E806B9A) void UNK_0x267C78C60E806B9A(any p0, bool p1)l
extern _native64(0x6BFF5F84102DF80A) void UNK_0x6BFF5F84102DF80A(any p0)l
extern _native64(0x5C497525F803486B) void UNK_0x5C497525F803486B()l
extern _native64(0x6FB7BB3607D27FA2) any UNK_0x6FB7BB3607D27FA2()l
extern _native64(0x45A83257ED02D9BC) void UNK_0x45A83257ED02D9BC()l
extern _native64(0xDFFA5BE8381C3314) int GET_NETWORK_TARGETING_MODE()l
extern _native64(0x125E6D638B8605D4) vector3 _NETWORK_GET_COORDS_OF_PLAYER(Player player)l
#pragma endregion //}
#pragma region NETWORKCASH //{
extern _native64(0x3DA5ECD1A56CBA6D) void NETWORK_INITIALIZE_CASH(int p0, int p1)l
extern _native64(0x05A50AF38947EB8D) void NETWORK_DELETE_CHARACTER(int characterIndex, bool p1, bool p2)l
extern _native64(0xA921DED15FDF28F5) void NETWORK_CLEAR_CHARACTER_WALLET(any p0)l
extern _native64(0xFB18DF9CB95E0105) void NETWORK_GIVE_PLAYER_JOBSHARE_CASH(int amount, int* networkHandle)l
extern _native64(0x56A3B51944C50598) void NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(int value, int* networkHandle)l
extern _native64(0x1C2473301B1C66BA) any UNK_0x1C2473301B1C66BA()l
extern _native64(0xF9C812CD7C46E817) void NETWORK_REFUND_CASH(int index, const char* context, const char* reason, bool unk)l
extern _native64(0x81404F3DC124FE5B) bool NETWORK_MONEY_CAN_BET(any p0, bool p1, bool p2)l
extern _native64(0x3A54E33660DED67F) bool NETWORK_CAN_BET(any p0)l
extern _native64(0xED1517D3AF17C698) any NETWORK_EARN_FROM_PICKUP(int amount)l
extern _native64(0xA03D4ACE0A3284CE) void _NETWORK_EARN_FROM_GANG_PICKUP(int amount)l
extern _native64(0xF514621E8EA463D0) void _NETWORK_EARN_FROM_ARMOUR_TRUCK(int amount)l
extern _native64(0xB1CC1B9EC3007A2A) void NETWORK_EARN_FROM_CRATE_DROP(int amount)l
extern _native64(0x827A5BA1A44ACA6D) void NETWORK_EARN_FROM_BETTING(int amount, const char* p1)l
extern _native64(0xB2CC4836834E8A98) void NETWORK_EARN_FROM_JOB(int amount, const char* p1)l
extern _native64(0x61326EE6DF15B0CA) void NETWORK_EARN_FROM_MISSION_H(int amount, const char* heistHash)l
extern _native64(0x2B171E6B2F64D8DF) void NETWORK_EARN_FROM_CHALLENGE_WIN(any p0, any* p1, bool p2)l
extern _native64(0x131BB5DA15453ACF) void NETWORK_EARN_FROM_BOUNTY(int amount, int* networkHandle, any* p2, any p3)l
extern _native64(0xF92A014A634442D6) void NETWORK_EARN_FROM_IMPORT_EXPORT(any p0, any p1)l
extern _native64(0x45B8154E077D9E4D) void NETWORK_EARN_FROM_HOLDUPS(int amount)l
extern _native64(0x849648349D77F5C5) void NETWORK_EARN_FROM_PROPERTY(int amount, Hash propertyName)l
extern _native64(0x515B4A22E4D3C6D7) void NETWORK_EARN_FROM_AI_TARGET_KILL(any p0, any p1)l
extern _native64(0x4337511FA8221D36) void NETWORK_EARN_FROM_NOT_BADSPORT(int amount)l
extern _native64(0x02CE1D6AC0FC73EA) void NETWORK_EARN_FROM_ROCKSTAR(int amount)l
extern _native64(0xB539BD8A4C1EECF8) void NETWORK_EARN_FROM_VEHICLE(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native64(0x3F4D00167E41E0AD) void NETWORK_EARN_FROM_PERSONAL_VEHICLE(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native64(0x6EA318C91C1A8786) void _NETWORK_EARN_FROM_DAILY_OBJECTIVE(int p0, const char* p1, int p2)l
extern _native64(0xFB6DB092FBAE29E6) void _NETWORK_EARN_FROM_AMBIENT_JOB(int p0, const char* p1, any* p2)l
extern _native64(0x6816FB4416760775) void _NETWORK_EARN_FROM_JOB_BONUS(any p0, any* p1, any* p2)l
extern _native64(0xAB3CAA6B422164DA) bool NETWORK_CAN_SPEND_MONEY(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native64(0x7303E27CC6532080) bool UNK_0x7303E27CC6532080(any p0, bool p1, bool p2, bool p3, any* p4, any p5)l
extern _native64(0xF0077C797F66A355) void NETWORK_BUY_ITEM(Ped player, Hash item, any p2, any p3, bool p4, const char* item_name, any p6, any p7, any p8, bool p9)l
extern _native64(0x17C3A7D31EAE39F9) void NETWORK_SPENT_TAXI(int amount, bool p1, bool p2)l
extern _native64(0x5FD5ED82CBBE9989) void NETWORK_PAY_EMPLOYEE_WAGE(any p0, bool p1, bool p2)l
extern _native64(0xAFE08B35EC0C9EAE) void NETWORK_PAY_UTILITY_BILL(any p0, bool p1, bool p2)l
extern _native64(0x9346E14F2AF74D46) void NETWORK_PAY_MATCH_ENTRY_FEE(int value, int* p1, bool p2, bool p3)l
extern _native64(0x1C436FD11FFA692F) void NETWORK_SPENT_BETTING(any p0, any p1, any* p2, bool p3, bool p4)l
extern _native64(0xEE99784E4467689C) void NETWORK_SPENT_IN_STRIPCLUB(any p0, bool p1, any p2, bool p3)l
extern _native64(0xD9B067E55253E3DD) void NETWORK_BUY_HEALTHCARE(int cost, bool p1, bool p2)l
extern _native64(0x763B4BD305338F19) void NETWORK_BUY_AIRSTRIKE(int cost, bool p1, bool p2)l
extern _native64(0x81AA4610E3FD3A69) void NETWORK_BUY_HELI_STRIKE(int cost, bool p1, bool p2)l
extern _native64(0xB162DC95C0A3317B) void NETWORK_SPENT_AMMO_DROP(any p0, bool p1, bool p2)l
extern _native64(0x7B718E197453F2D9) void NETWORK_BUY_BOUNTY(int amount, Player victim, bool p2, bool p3)l
extern _native64(0x650A08A280870AF6) void NETWORK_BUY_PROPERTY(float propertyCost, Hash propertyName, bool p2, bool p3)l
extern _native64(0x7BF1D73DB2ECA492) void NETWORK_SPENT_HELI_PICKUP(any p0, bool p1, bool p2)l
extern _native64(0x524EE43A37232C00) void NETWORK_SPENT_BOAT_PICKUP(any p0, bool p1, bool p2)l
extern _native64(0xA6DD8458CE24012C) void NETWORK_SPENT_BULL_SHARK(any p0, bool p1, bool p2)l
extern _native64(0x289016EC778D60E0) void NETWORK_SPENT_CASH_DROP(any p0, bool p1, bool p2)l
extern _native64(0xE404BFB981665BF0) void NETWORK_SPENT_HIRE_MUGGER(any p0, bool p1, bool p2)l
extern _native64(0x995A65F15F581359) void NETWORK_SPENT_ROBBED_BY_MUGGER(int amount, bool p1, bool p2)l
extern _native64(0xE7B80E2BF9D80BD6) void NETWORK_SPENT_HIRE_MERCENARY(any p0, bool p1, bool p2)l
extern _native64(0xE1B13771A843C4F6) void NETWORK_SPENT_BUY_WANTEDLEVEL(any p0, any* p1, bool p2, bool p3)l
extern _native64(0xA628A745E2275C5D) void NETWORK_SPENT_BUY_OFFTHERADAR(any p0, bool p1, bool p2)l
extern _native64(0x6E176F1B18BC0637) void NETWORK_SPENT_BUY_REVEAL_PLAYERS(any p0, bool p1, bool p2)l
extern _native64(0xEC03C719DB2F4306) void NETWORK_SPENT_CARWASH(any p0, any p1, any p2, bool p3, bool p4)l
extern _native64(0x6B38ECB05A63A685) void NETWORK_SPENT_CINEMA(any p0, any p1, bool p2, bool p3)l
extern _native64(0x7FE61782AD94CC09) void NETWORK_SPENT_TELESCOPE(any p0, bool p1, bool p2)l
extern _native64(0xD9B86B9872039763) void NETWORK_SPENT_HOLDUPS(any p0, bool p1, bool p2)l
extern _native64(0x6D3A430D1A809179) void NETWORK_SPENT_BUY_PASSIVE_MODE(any p0, bool p1, bool p2)l
extern _native64(0xB21B89501CFAC79E) void NETWORK_SPENT_PROSTITUTES(any p0, bool p1, bool p2)l
extern _native64(0x812F5488B1B2A299) void NETWORK_SPENT_ARREST_BAIL(any p0, bool p1, bool p2)l
extern _native64(0x9FF28D88C766E3E8) void NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(int amount, Hash vehicleModel, int* networkHandle, bool notBankrupt, bool hasTheMoney)l
extern _native64(0xACDE7185B374177C) void NETWORK_SPENT_CALL_PLAYER(any p0, any* p1, bool p2, bool p3)l
extern _native64(0x29B260B84947DFCC) void NETWORK_SPENT_BOUNTY(any p0, bool p1, bool p2)l
extern _native64(0x6A445B64ED7ABEB5) void NETWORK_SPENT_FROM_ROCKSTAR(int bank, bool p1, bool p2)l
extern _native64(0x20194D48EAEC9A41) const char* PROCESS_CASH_GIFT(int* p0, int* p1, const char* p2)l
extern _native64(0x7C99101F7FCE2EE5) void NETWORK_SPENT_PLAYER_HEALTHCARE(any p0, any p1, bool p2, bool p3)l
extern _native64(0xD5BB406F4E04019F) void NETWORK_SPENT_NO_COPS(any p0, bool p1, bool p2)l
extern _native64(0x8204DA7934DF3155) void NETWORK_SPENT_REQUEST_JOB(any p0, bool p1, bool p2)l
extern _native64(0x9D26502BB97BFE62) void _NETWORK_SPENT_REQUEST_HEIST(any p0, bool p1, bool p2)l
extern _native64(0x8A7B3952DD64D2B5) void NETWORK_BUY_FAIRGROUND_RIDE(int amountSpent, any p1, bool p2, bool p3)l
extern _native64(0x7C4FCCD2E4DEB394) bool UNK_0x7C4FCCD2E4DEB394()l
extern _native64(0x76EF28DA05EA395A) int NETWORK_GET_VC_BANK_BALANCE()l
extern _native64(0xA40F9C2623F6A8B5) int NETWORK_GET_VC_WALLET_BALANCE(int character)l
extern _native64(0x5CBAD97E059E1B94) int NETWORK_GET_VC_BALANCE()l
extern _native64(0xA6FA3979BED01B81) const char* _NETWORK_GET_BANK_BALANCE_STRING()l
extern _native64(0xDC18531D7019A535) bool UNK_0xDC18531D7019A535(any p0, any p1)l
extern _native64(0x5D17BE59D2123284) bool NETWORK_CAN_RECEIVE_PLAYER_CASH(any p0, any p1, any p2, any p3)l
extern _native64(0xF70EFA14FE091429) any UNK_0xF70EFA14FE091429(any p0)l
extern _native64(0xE260E0BB9CD995AC) bool UNK_0xE260E0BB9CD995AC(any p0)l
extern _native64(0xE154B48B68EF72BC) any UNK_0xE154B48B68EF72BC(any p0)l
extern _native64(0x6FCF8DDEA146C45B) any UNK_0x6FCF8DDEA146C45B(any p0)l
extern _native64(0x998E18CEB44487FC) void NETWORK_SPENT_PURCHASE_CLUBHOUSE(int p0, void* p1, bool p2, bool p3)l
extern _native64(0xFA07759E6FDDD7CF) void NETWORK_SPENT_VEHICLE_MODSHOP(int p0, void* p1, bool p2, bool p3)l
#pragma endregion //}
#pragma region DLC1 //{
extern _native64(0x278F76C3B0A8F109) int _GET_NUM_DECORATIONS(int character)l
extern _native64(0xFF56381874F82086) bool UNK_0xFF56381874F82086(int p0, int p1, int* outComponent)l
extern _native64(0x1E8C308FD312C036) void INIT_SHOP_PED_COMPONENT(int* outComponent)l
extern _native64(0xEB0A2B758F7B850F) void INIT_SHOP_PED_PROP(int* outProp)l
extern _native64(0x50F457823CE6EB5F) int UNK_0x50F457823CE6EB5F(int p0, int p1, int p2, int p3)l
extern _native64(0x9BDF59818B1E38C1) int _GET_NUM_PROPS_FROM_OUTFIT(int character, int p1, int p2, bool p3, int p4, int componentId)l
extern _native64(0x249E310B2D920699) void GET_SHOP_PED_QUERY_COMPONENT(int componentId, int* outComponent)l
extern _native64(0x74C0E2A57EC66760) void GET_SHOP_PED_COMPONENT(Hash p0, any* p1)l
extern _native64(0xDE44A00999B2837D) void GET_SHOP_PED_QUERY_PROP(any p0, any* p1)l
extern _native64(0x5D5CAFF661DDF6FC) void UNK_0x5D5CAFF661DDF6FC(any p0, any* p1)l
extern _native64(0x0368B3A838070348) Hash GET_HASH_NAME_FOR_COMPONENT(Entity entity, int componentId, int drawableVariant, int textureVariant)l
extern _native64(0x5D6160275CAEC8DD) Hash GET_HASH_NAME_FOR_PROP(Entity entity, int componentId, int propIndex, int propTextureIndex)l
extern _native64(0xC17AD0E5752BECDA) int UNK_0xC17AD0E5752BECDA(Hash componentHash)l
extern _native64(0x6E11F282F11863B6) void GET_VARIANT_COMPONENT(Hash componentHash, int componentId, any* p2, any* p3, any* p4)l
extern _native64(0xC6B9DB42C04DD8C3) int _GET_NUM_FORCED_COMPONENTS(Hash componentHash)l
extern _native64(0x017568A8182D98A6) any UNK_0x017568A8182D98A6(any p0)l
extern _native64(0x6C93ED8C2F74859B) void GET_FORCED_COMPONENT(Hash componentHash, int componentId, any* p2, any* p3, any* p4)l
extern _native64(0xE1CA84EBF72E691D) void UNK_0xE1CA84EBF72E691D(any p0, any p1, any* p2, any* p3, any* p4)l
extern _native64(0x341DE7ED1D2A1BFD) bool UNK_0x341DE7ED1D2A1BFD(Hash componentHash, Hash drawableSlotHash, bool p2)l
extern _native64(0xF3FBE2D50A6A8C28) int UNK_0xF3FBE2D50A6A8C28(int character, bool p1)l
extern _native64(0x6D793F03A631FE56) void GET_SHOP_PED_QUERY_OUTFIT(any p0, any* outfit)l
extern _native64(0xB7952076E444979D) void GET_SHOP_PED_OUTFIT(any p0, any* p1)l
extern _native64(0x073CA26B079F956E) any GET_SHOP_PED_OUTFIT_LOCATE(any p0)l
extern _native64(0xA9F9C2E0FDE11CBB) bool UNK_0xA9F9C2E0FDE11CBB(any p0, any p1, any* p2)l
extern _native64(0x19F2A026EDF0013F) bool _GET_PROP_FROM_OUTFIT(any outfit, int slot, any* item)l
extern _native64(0xA7A866D21CD2329B) int GET_NUM_DLC_VEHICLES()l
extern _native64(0xECC01B7C5763333C) Hash GET_DLC_VEHICLE_MODEL(int dlcVehicleIndex)l
extern _native64(0x33468EDC08E371F6) bool GET_DLC_VEHICLE_DATA(int dlcVehicleIndex, int* outData)l
extern _native64(0x5549EE11FA22FCF2) int GET_DLC_VEHICLE_FLAGS(int dlcVehicleIndex)l
extern _native64(0xEE47635F352DA367) int GET_NUM_DLC_WEAPONS()l
extern _native64(0x79923CD21BECE14E) bool GET_DLC_WEAPON_DATA(int dlcWeaponIndex, int* outData)l
extern _native64(0x405425358A7D61FE) int GET_NUM_DLC_WEAPON_COMPONENTS(int dlcWeaponIndex)l
extern _native64(0x6CF598A2957C2BF8) bool GET_DLC_WEAPON_COMPONENT_DATA(int dlcWeaponIndex, int dlcWeapCompIndex, int* ComponentDataPtr)l
extern _native64(0xD4D7B033C3AA243C) bool _IS_DLC_DATA_EMPTY(int dlcData)l
extern _native64(0x0564B9FF9631B82C) bool IS_DLC_VEHICLE_MOD(int modData)l
extern _native64(0xC098810437312FFF) int UNK_0xC098810437312FFF(int modData)l
#pragma endregion //}
#pragma region DLC2 //{
extern _native64(0x812595A0644CE1DE) bool IS_DLC_PRESENT(Hash dlcHash)l
extern _native64(0xF2E07819EF1A5289) bool UNK_0xF2E07819EF1A5289()l
extern _native64(0x9489659372A81585) any UNK_0x9489659372A81585()l
extern _native64(0xA213B11DFF526300) any UNK_0xA213B11DFF526300()l
extern _native64(0x8D30F648014A92B5) any UNK_0x8D30F648014A92B5()l
extern _native64(0x10D0A8F259E93EC9) bool GET_IS_LOADING_SCREEN_ACTIVE()l
extern _native64(0x46E2B844905BC5F0) bool _NULLIFY(any* variable, any unused)l
extern _native64(0xD7C10C4A637992C9) void _LOAD_SP_DLC_MAPS()l
extern _native64(0x0888C3502DBBEEF5) void _LOAD_MP_DLC_MAPS()l
#pragma endregion //}
#pragma region SYSTEM //{
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
extern _native64(0x652D2EEEF1D3E62C) float VMAG(vector3 vec)l
extern _native64(0xA8CEACB4F35AE058) float VMAG2(vector3 vec)l
extern _native64(0x2A488C176D52CCA5) float VDIST(vector3 vec_1, vector3 vec_2)l
extern _native64(0xB7A628320EFF8E47) float VDIST2(vector3 vec_1, vector3 vec_2)l
extern _native64(0xEDD95A39E5544DE8) int SHIFT_LEFT(int value, int bitShift)l
extern _native64(0x97EF1E5BCE9DC075) int SHIFT_RIGHT(int value, int bitShift)l
extern _native64(0xF34EE736CF047844) int FLOOR(float value)l
extern _native64(0x11E019C8F43ACC8A) int CEIL(float value)l
extern _native64(0xF2DB717A73826179) int ROUND(float value)l
extern _native64(0xBBDA792448DB5A89) float TO_FLOAT(int value)l
extern _native64(0x42B65DEEF2EDF2A1) void UNK_0x42B65DEEF2EDF2A1(int p0)l
#pragma endregion //}
#pragma region DECORATOR //{
extern _native64(0x95AED7B8E39ECAA4) bool DECOR_SET_TIME(Entity entity, const char* propertyName, int value)l
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
extern _native64(0x241FCA5B1AA14F75) int UNK_0x241FCA5B1AA14F75()l
#pragma endregion //}
#pragma region SOCIALCLUB //{
extern _native64(0x03A93FF1A2CA0864) int _GET_TOTAL_SC_INBOX_IDS()l
extern _native64(0xBB8EA16ECBC976C4) Hash _SC_INBOX_MESSAGE_INIT(int p0)l
extern _native64(0x93028F1DB42BFD08) bool _IS_SC_INBOX_VALID(int p0)l
extern _native64(0x2C015348CF19CA1D) bool _SC_INBOX_MESSAGE_POP(int p0)l
extern _native64(0xA00EFE4082C4056E) bool SC_INBOX_MESSAGE_GET_DATA_INT(int p0, const char* context, int* out)l
extern _native64(0xFFE5C16F402D851D) bool _SC_INBOX_MESSAGE_GET_DATA_BOOL(int p0, const char* p1)l
extern _native64(0x7572EF42FC6A9B6D) bool SC_INBOX_MESSAGE_GET_DATA_STRING(int p0, const char* context, const char* out)l
extern _native64(0x9A2C8064B6C1E41A) bool _SC_INBOX_MESSAGE_PUSH(int p0)l
extern _native64(0xF3E31D16CBDCB304) const char* _SC_INBOX_MESSAGE_GET_STRING(int p0)l
extern _native64(0xDA024BDBD600F44A) void UNK_0xDA024BDBD600F44A(int* p0)l
extern _native64(0xA68D3D229F4F3B06) void UNK_0xA68D3D229F4F3B06(const char* p0)l
extern _native64(0x69D82604A1A5A254) bool SC_INBOX_MESSAGE_GET_UGCDATA(any p0, any* p1)l
extern _native64(0x6AFD2CD753FEEF83) bool UNK_0x6AFD2CD753FEEF83(const char* p0)l
extern _native64(0x87E0052F08BD64E6) bool UNK_0x87E0052F08BD64E6(any p0, int* p1)l
extern _native64(0x040ADDCBAFA1018A) void _SC_INBOX_GET_EMAILS(int offset, int limit)l
extern _native64(0x16DA8172459434AA) any UNK_0x16DA8172459434AA()l
extern _native64(0x4737980E8A283806) bool UNK_0x4737980E8A283806(int p0, any* p1)l
extern _native64(0x44ACA259D67651DB) void UNK_0x44ACA259D67651DB(any* p0, any p1)l
extern _native64(0x2330C12A7A605D16) void SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST(Player* player)l
extern _native64(0x55DF6DB45179236E) void SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST()l
extern _native64(0x116FB94DC4B79F17) void UNK_0x116FB94DC4B79F17(const char* p0)l
extern _native64(0xBFA0A56A817C6C7D) void UNK_0xBFA0A56A817C6C7D(bool p0)l
extern _native64(0xBC1CC91205EC8D6E) any UNK_0xBC1CC91205EC8D6E()l
extern _native64(0xDF649C4E9AFDD788) any UNK_0xDF649C4E9AFDD788()l
extern _native64(0x1F1E9682483697C7) bool UNK_0x1F1E9682483697C7(any p0, any p1)l
extern _native64(0x287F1F75D2803595) bool UNK_0x287F1F75D2803595(any p0, any* p1)l
extern _native64(0x487912FD248EFDDF) bool UNK_0x487912FD248EFDDF(any p0, float p1)l
extern _native64(0x8416FE4E4629D7D7) bool UNK_0x8416FE4E4629D7D7(const char* p0)l
extern _native64(0x75632C5ECD7ED843) bool _SC_START_CHECK_STRING_TASK(const char* string, int* taskHandle)l
extern _native64(0x1753344C770358AE) bool _SC_HAS_CHECK_STRING_TASK_COMPLETED(int taskHandle)l
extern _native64(0x82E4A58BABC15AE7) int _SC_GET_CHECK_STRING_STATUS(int taskHandle)l
extern _native64(0x85535ACF97FC0969) any UNK_0x85535ACF97FC0969(any p0)l
extern _native64(0x930DE22F07B1CCE3) int UNK_0x930DE22F07B1CCE3(any p0)l
extern _native64(0xF6BAAAF762E1BF40) bool UNK_0xF6BAAAF762E1BF40(const char* p0, int* p1)l
extern _native64(0xF22CA0FD74B80E7A) bool UNK_0xF22CA0FD74B80E7A(any p0)l
extern _native64(0x9237E334F6E43156) any UNK_0x9237E334F6E43156(any p0)l
extern _native64(0x700569DBA175A77C) any UNK_0x700569DBA175A77C(any p0)l
extern _native64(0x1D4446A62D35B0D0) any UNK_0x1D4446A62D35B0D0(any p0, any p1)l
extern _native64(0x2E89990DDFF670C3) any UNK_0x2E89990DDFF670C3(any p0, any p1)l
extern _native64(0xD0EE05FE193646EA) bool UNK_0xD0EE05FE193646EA(any* p0, any* p1, any* p2)l
extern _native64(0x1989C6E6F67E76A8) bool UNK_0x1989C6E6F67E76A8(any* p0, any* p1, any* p2)l
extern _native64(0x07C61676E5BB52CD) any UNK_0x07C61676E5BB52CD(any p0)l
extern _native64(0x8147FFF6A718E1AD) any UNK_0x8147FFF6A718E1AD(any p0)l
extern _native64(0x0F73393BAC7E6730) bool UNK_0x0F73393BAC7E6730(any* p0, int* p1)l
extern _native64(0xD302E99EDF0449CF) any UNK_0xD302E99EDF0449CF(any p0)l
extern _native64(0x5C4EBFFA98BDB41C) any UNK_0x5C4EBFFA98BDB41C(any p0)l
extern _native64(0xFF8F3A92B75ED67A) any UNK_0xFF8F3A92B75ED67A()l
extern _native64(0x4A7D6E727F941747) any UNK_0x4A7D6E727F941747(any* p0)l
extern _native64(0x8CC469AB4D349B7C) bool UNK_0x8CC469AB4D349B7C(int p0, const char* p1, any* p2)l
extern _native64(0x699E4A5C8C893A18) bool UNK_0x699E4A5C8C893A18(int p0, const char* p1, any* p2)l
extern _native64(0x19853B5B17D77BCA) bool UNK_0x19853B5B17D77BCA(any p0, any* p1)l
extern _native64(0x6BFB12CE158E3DD4) bool UNK_0x6BFB12CE158E3DD4(any p0)l
extern _native64(0xFE4C1D0D3B9CC17E) bool UNK_0xFE4C1D0D3B9CC17E(any p0, any p1)l
extern _native64(0xD8122C407663B995) any UNK_0xD8122C407663B995()l
extern _native64(0x3001BEF2FECA3680) bool UNK_0x3001BEF2FECA3680()l
extern _native64(0x92DA6E70EF249BD1) bool UNK_0x92DA6E70EF249BD1(const char* p0, int* p1)l
extern _native64(0x675721C9F644D161) void UNK_0x675721C9F644D161()l
extern _native64(0x198D161F458ECC7F) const char* _SC_GET_NICKNAME()l
extern _native64(0x225798743970412B) bool UNK_0x225798743970412B(int* p0)l
extern _native64(0x418DC16FAE452C1C) bool UNK_0x418DC16FAE452C1C(int p0)l
#pragma endregion //}
#pragma region UNK //{
extern _native64(0xF2CA003F167E21D2) int UNK_0xF2CA003F167E21D2()l
extern _native64(0xEF7D17BC6C85264C) bool UNK_0xEF7D17BC6C85264C()l
extern _native64(0xB0C56BD3D808D863) void UNK_0xB0C56BD3D808D863(bool p0)l
extern _native64(0x8AA464D4E0F6ACCD) any UNK_0x8AA464D4E0F6ACCD()l
extern _native64(0xFC309E94546FCDB5) void UNK_0xFC309E94546FCDB5(bool p0)l
extern _native64(0xC6DC823253FBB366) bool _IS_UI_LOADING_MULTIPLAYER()l
extern _native64(0xC7E7181C09F33B69) void UNK_0xC7E7181C09F33B69(bool p0)l
extern _native64(0xFA1E0E893D915215) void UNK_0xFA1E0E893D915215(bool p0)l
extern _native64(0x2BDD44CC428A7EAE) int _GET_CURRENT_LANGUAGE_ID()l
extern _native64(0xA8AE43AEC1A61314) int _GET_USER_LANGUAGE_ID()l
#pragma endregion //}
#pragma region UNK1 //{
extern _native64(0x48621C9FCA3EBD28) void UNK_0x48621C9FCA3EBD28(bool p0)l
extern _native64(0x81CBAE94390F9F89) void UNK_0x81CBAE94390F9F89()l
extern _native64(0x13B350B8AD0EEE10) void UNK_0x13B350B8AD0EEE10()l
extern _native64(0x293220DA1B46CEBC) void UNK_0x293220DA1B46CEBC(float p0, float p1, bool p2)l
extern _native64(0x208784099002BC30) void UNK_0x208784099002BC30(const char* missionNameLabel, any p1)l
extern _native64(0xEB2D525B57F42B40) void UNK_0xEB2D525B57F42B40()l
extern _native64(0xF854439EFBB3B583) void UNK_0xF854439EFBB3B583()l
extern _native64(0xAF66DCEE6609B148) void UNK_0xAF66DCEE6609B148()l
extern _native64(0x66972397E0757E7A) void UNK_0x66972397E0757E7A(any p0, any p1, any p2)l
extern _native64(0xC3AC2FFF9612AC81) void _START_RECORDING(int mode)l
extern _native64(0x071A5197D6AFC8B3) void _STOP_RECORDING_AND_SAVE_CLIP()l
extern _native64(0x88BB3507ED41A240) void _STOP_RECORDING_AND_DISCARD_CLIP()l
extern _native64(0x644546EC5287471B) bool UNK_0x644546EC5287471B()l
extern _native64(0x1897CA71995A90B4) bool _IS_RECORDING()l
extern _native64(0xDF4B952F7D381B95) any UNK_0xDF4B952F7D381B95()l
extern _native64(0x4282E08174868BE3) any UNK_0x4282E08174868BE3()l
extern _native64(0x33D47E85B476ABCD) bool UNK_0x33D47E85B476ABCD(bool p0)l
#pragma endregion //}
#pragma region UNK2 //{
extern _native64(0x7E2BD3EF6C205F09) void UNK_0x7E2BD3EF6C205F09(any p0, any p1)l
extern _native64(0x95AB8B5C992C7B58) bool _IS_INTERIOR_RENDERING_DISABLED()l
extern _native64(0x5AD3932DAEB1E5D3) void UNK_0x5AD3932DAEB1E5D3()l
extern _native64(0xE058175F8EAFE79A) void UNK_0xE058175F8EAFE79A(bool p0)l
extern _native64(0x3353D13F09307691) void _RESET_EDITOR_VALUES()l
extern _native64(0x49DA8145672B2725) void _ACTIVATE_ROCKSTAR_EDITOR()l
#pragma endregion //}
#pragma region UNK3 //{
extern _native64(0xC27009422FCCA88D) int _NETWORK_SHOP_GET_PRICE(Hash hash, Hash hash2, bool p2)l
extern _native64(0x3C4487461E9B0DCB) any UNK_0x3C4487461E9B0DCB()l
extern _native64(0x2B949A1E6AEC8F6A) any UNK_0x2B949A1E6AEC8F6A()l
extern _native64(0x85F6C9ABA1DE2BCF) any UNK_0x85F6C9ABA1DE2BCF()l
extern _native64(0x357B152EF96C30B6) any UNK_0x357B152EF96C30B6()l
extern _native64(0xCF38DAFBB49EDE5E) bool UNK_0xCF38DAFBB49EDE5E(any* p0)l
extern _native64(0xE3E5A7C64CA2C6ED) any UNK_0xE3E5A7C64CA2C6ED()l
extern _native64(0x0395CB47B022E62C) bool UNK_0x0395CB47B022E62C(any* p0)l
extern _native64(0xA135AC892A58FC07) bool _NETWORK_SHOP_START_SESSION(any p0)l
extern _native64(0x72EB7BA9B69BF6AB) any UNK_0x72EB7BA9B69BF6AB()l
extern _native64(0x170910093218C8B9) bool UNK_0x170910093218C8B9(any* p0)l
extern _native64(0xC13C38E47EA5DF31) bool UNK_0xC13C38E47EA5DF31(any* p0)l
extern _native64(0xB24F0944DA203D9E) bool _NETWORK_SHOP_GET_TRANSACTIONS_ENABLED_FOR_CHARACTER(int mpChar)l
extern _native64(0x74A0FD0688F1EE45) bool UNK_0x74A0FD0688F1EE45(any p0)l
extern _native64(0x2F41D51BA3BCD1F1) bool _NETWORK_SHOP_SESSION_APPLY_RECEIVED_DATA(any p0)l
extern _native64(0x810E8431C0614BF9) bool _NETWORK_SHOP_GET_TRANSACTIONS_DISABLED()l
extern _native64(0x35A1B3E1D1315CFA) bool UNK_0x35A1B3E1D1315CFA(bool p0, bool p1)l
extern _native64(0x897433D292B44130) bool UNK_0x897433D292B44130(any* p0, any* p1)l
extern _native64(0x279F08B1A4B29B7E) bool _NETWORK_SHOP_BASKET_START(any* p0, any p1, any p2, any p3)l
extern _native64(0xA65568121DF2EA26) any _NETWORK_SHOP_BASKET_END()l
extern _native64(0xF30980718C8ED876) any _NETWORK_SHOP_BASKET_ADD_ITEM(any* p0, any p1)l
extern _native64(0x27F76CC6C55AD30E) any _NETWORK_SHOP_BASKET_IS_FULL()l
extern _native64(0xE1A0450ED46A7812) bool _NETWORK_SHOP_BASKET_APPLY_SERVER_DATA(any p0, any* p1)l
extern _native64(0x39BE7CEA8D9CC8E6) bool _NETWORK_SHOP_CHECKOUT_START(any p0)l
extern _native64(0x3C5FD37B5499582E) bool _NETWORK_SHOP_BEGIN_SERVICE(int* value, any p1, any p2, any p3, any p4, int p5)l
extern _native64(0xE2A99A9B524BEFFF) bool _NETWORK_SHOP_END_SERVICE(any p0)l
extern _native64(0x51F1A8E48C3D2F6D) bool UNK_0x51F1A8E48C3D2F6D(any p0, bool p1, any p2)l
extern _native64(0x0A6D923DFFC9BD89) any UNK_0x0A6D923DFFC9BD89()l
extern _native64(0x112CEF1615A1139F) any _NETWORK_SHOP_DELETE_SET_TELEMETRY_NONCE_SEED()l
extern _native64(0xD47A2C1BA117471D) bool _NETWORK_TRANSFER_BANK_TO_WALLET(int charStatInt, int amount)l
extern _native64(0xC2F7FE5309181C7D) bool _NETWORK_TRANSFER_WALLET_TO_BANK(int charStatInt, int amount)l
extern _native64(0x23789E777D14CE44) any UNK_0x23789E777D14CE44()l
extern _native64(0x350AA5EBC03D3BD2) any UNK_0x350AA5EBC03D3BD2()l
extern _native64(0x498C1E05CE5F7877) any _NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED()l
extern _native64(0x9507D4271988E1AE) bool _NETWORK_SHOP_SET_TELEMETRY_NONCE_SEED(any p0)l
extern _native64(0xFCA9373EF340AC0A) const char* _GET_ONLINE_VERSION()l
extern _native64(0xFA336E7F40C0A0D0) void UNK_0xFA336E7F40C0A0D0()l
#pragma endregion //}

	
#undef _native64
#pragma clang diagnostic pop
