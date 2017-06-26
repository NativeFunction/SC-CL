/*H**********************************************************************
* FILENAME :	natives32.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Native functions to be used with all 32 bit GTAV targets and platforms of SC-CL.
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

#pragma region PLAYER //{
extern _native Ped GET_PLAYER_PED(Player player)l
extern _native Entity GET_PLAYER_PED_SCRIPT_INDEX(Player player)l
extern _native void SET_PLAYER_MODEL(Player player, Hash model)l
extern _native void CHANGE_PLAYER_PED(Player player, Ped ped, bool b2, bool b3)l
extern _native void GET_PLAYER_RGB_COLOUR(Player player, int* r, int* g, int* b)l
extern _native int GET_NUMBER_OF_PLAYERS()l
extern _native int GET_PLAYER_TEAM(Player player)l
extern _native void SET_PLAYER_TEAM(Player player, int team)l
extern _native const char* GET_PLAYER_NAME(Player player)l
extern _native float GET_WANTED_LEVEL_RADIUS(Player player)l
extern _native vector3 GET_PLAYER_WANTED_CENTRE_POSITION(Player player)l
extern _native void SET_PLAYER_WANTED_CENTRE_POSITION(Player player, vector3* position, bool p2, bool p3)l
extern _native int GET_WANTED_LEVEL_THRESHOLD(int wantedLevel)l
extern _native void SET_PLAYER_WANTED_LEVEL(Player player, int wantedLevel, bool disableNoMission)l
extern _native void SET_PLAYER_WANTED_LEVEL_NO_DROP(Player player, int wantedLevel, bool p2)l
extern _native void SET_PLAYER_WANTED_LEVEL_NOW(Player player, bool p1)l
extern _native bool ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(Player player)l
extern _native bool ARE_PLAYER_STARS_GREYED_OUT(Player player)l
extern _native void SET_DISPATCH_COPS_FOR_PLAYER(Player player, bool toggle)l
extern _native bool IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel)l
extern _native void CLEAR_PLAYER_WANTED_LEVEL(Player player)l
extern _native bool IS_PLAYER_DEAD(Player player)l
extern _native bool IS_PLAYER_PRESSING_HORN(Player player)l
extern _native void SET_PLAYER_CONTROL(Player player, bool toggle, int possiblyFlags)l
extern _native int GET_PLAYER_WANTED_LEVEL(Player player)l
extern _native void SET_MAX_WANTED_LEVEL(int maxWantedLevel)l
extern _native void SET_POLICE_RADAR_BLIPS(bool toggle)l
extern _native void SET_POLICE_IGNORE_PLAYER(Player player, bool toggle)l
extern _native bool IS_PLAYER_PLAYING(Player player)l
extern _native void SET_EVERYONE_IGNORE_PLAYER(Player player, bool toggle)l
extern _native void SET_ALL_RANDOM_PEDS_FLEE(Player player, bool toggle)l
extern _native void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player)l
extern _native void UNK_0x274631FE(Player player, bool toggle)l
extern _native void UNK_0x02DF7AF4(Player player)l
extern _native void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Player player, bool toggle)l
extern _native void SET_WANTED_LEVEL_MULTIPLIER(float multiplier)l
extern _native void SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty)l
extern _native void RESET_WANTED_LEVEL_DIFFICULTY(Player player)l
extern _native void START_FIRING_AMNESTY(int duration)l
extern _native void REPORT_CRIME(Player player, int crimeType, int wantedLvlThresh)l
extern _native32(0x59B5C2A2) void _SWITCH_CRIME_TYPE(Player player, int p1)l
extern _native void UNK_0x6B34A160(Player player)l
extern _native any UNK_0xB9FB142F(Player player)l
extern _native any UNK_0x85725848(Player player)l
extern _native void UNK_0x3A7E5FB6(Player player)l
extern _native void UNK_0xD15C4B1C(Player player)l
extern _native void UNK_0xBF6993C7(float p0)l
extern _native void UNK_0x47CAB814()l
extern _native bool CAN_PLAYER_START_MISSION(Player player)l
extern _native bool IS_PLAYER_READY_FOR_CUTSCENE(Player player)l
extern _native bool IS_PLAYER_TARGETTING_ENTITY(Player player, Entity entity)l
extern _native bool GET_PLAYER_TARGET_ENTITY(Player player, Entity* entity)l
extern _native bool IS_PLAYER_FREE_AIMING(Player player)l
extern _native bool IS_PLAYER_FREE_AIMING_AT_ENTITY(Player player, Entity entity)l
extern _native bool GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(Player player, Entity* entity)l
extern _native void SET_PLAYER_LOCKON_RANGE_OVERRIDE(Player player, float range)l
extern _native void SET_PLAYER_CAN_DO_DRIVE_BY(Player player, bool toggle)l
extern _native void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Player player, bool toggle)l
extern _native any SET_PLAYER_CAN_USE_COVER(Player player, bool toggle)l
extern _native int GET_MAX_WANTED_LEVEL()l
extern _native bool IS_PLAYER_TARGETTING_ANYTHING(Player player)l
extern _native void SET_PLAYER_SPRINT(Player player, bool toggle)l
extern _native void RESET_PLAYER_STAMINA(Player player)l
extern _native void RESTORE_PLAYER_STAMINA(Player player, float p1)l
extern _native float GET_PLAYER_SPRINT_STAMINA_REMAINING(Player player)l
extern _native float GET_PLAYER_SPRINT_TIME_REMAINING(Player player)l
extern _native float GET_PLAYER_UNDERWATER_TIME_REMAINING(Player player)l
extern _native int GET_PLAYER_GROUP(Player player)l
extern _native int GET_PLAYER_MAX_ARMOUR(Player player)l
extern _native bool IS_PLAYER_CONTROL_ON(Player player)l
extern _native bool IS_PLAYER_SCRIPT_CONTROL_ON(Player player)l
extern _native bool IS_PLAYER_CLIMBING(Player player)l
extern _native bool IS_PLAYER_BEING_ARRESTED(Player player, bool atArresting)l
extern _native void RESET_PLAYER_ARREST_STATE(Player player)l
extern _native Vehicle GET_PLAYERS_LAST_VEHICLE()l
extern _native Player GET_PLAYER_INDEX()l
extern _native Player INT_TO_PLAYERINDEX(int value)l
extern _native int INT_TO_PARTICIPANTINDEX(int value)l
extern _native int GET_TIME_SINCE_PLAYER_HIT_VEHICLE(Player player)l
extern _native int GET_TIME_SINCE_PLAYER_HIT_PED(Player player)l
extern _native int GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Player player)l
extern _native int GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(Player player)l
extern _native bool IS_PLAYER_FREE_FOR_AMBIENT_TASK(Player player)l
extern _native Player PLAYER_ID()l
extern _native Ped PLAYER_PED_ID()l
extern _native int NETWORK_PLAYER_ID_TO_INT()l
extern _native bool HAS_FORCE_CLEANUP_OCCURRED(int cleanupFlags)l
extern _native void FORCE_CLEANUP(int cleanupFlags)l
extern _native void FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(const char* name, int cleanupFlags)l
extern _native void FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID(int id, int cleanupFlags)l
extern _native int GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP()l
extern _native void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(Player player, Vehicle vehicle)l
extern _native void SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE(Player player)l
extern _native bool GIVE_ACHIEVEMENT_TO_PLAYER(int achievement)l
extern _native bool HAS_ACHIEVEMENT_BEEN_PASSED(int achievement)l
extern _native bool IS_PLAYER_ONLINE()l
extern _native bool IS_PLAYER_LOGGING_IN_NP()l
extern _native void DISPLAY_SYSTEM_SIGNIN_UI(bool unk)l
extern _native bool IS_SYSTEM_UI_BEING_DISPLAYED()l
extern _native void SET_PLAYER_INVINCIBLE(Player player, bool toggle)l
extern _native bool GET_PLAYER_INVINCIBLE(Player player)l
extern _native void UNK_0x00563E0D(Player player, bool p1)l
extern _native any REMOVE_PLAYER_HELMET(Player player, bool p2)l
extern _native void GIVE_PLAYER_RAGDOLL_CONTROL(Player player, bool toggle)l
extern _native void SET_PLAYER_LOCKON(Player player, bool toggle)l
extern _native void SET_PLAYER_TARGETING_MODE(int targetMode)l
extern _native void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Player player)l
extern _native bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Player player)l
extern _native void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player)l
extern _native bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player)l
extern _native void SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(Player player, float multiplier)l
extern _native void SET_SWIM_MULTIPLIER_FOR_PLAYER(Player player, float multiplier)l
extern _native void SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(Player player, float multiplier)l
extern _native int GET_TIME_SINCE_LAST_ARREST()l
extern _native int GET_TIME_SINCE_LAST_DEATH()l
extern _native void ASSISTED_MOVEMENT_CLOSE_ROUTE()l
extern _native void ASSISTED_MOVEMENT_FLUSH_ROUTE()l
extern _native void SET_PLAYER_FORCED_AIM(Player player, bool toggle)l
extern _native void SET_PLAYER_FORCED_ZOOM(Player player, bool toggle)l
extern _native void SET_PLAYER_FORCE_SKIP_AIM_INTRO(Player player, bool toggle)l
extern _native void DISABLE_PLAYER_FIRING(Player player, bool toggle)l
extern _native void SET_DISABLE_AMBIENT_MELEE_MOVE(Player player, bool toggle)l
extern _native void SET_PLAYER_MAX_ARMOUR(Player player, int value)l
extern _native void SPECIAL_ABILITY_DEACTIVATE(Player player)l
extern _native void SPECIAL_ABILITY_DEACTIVATE_FAST(Player player)l
extern _native void SPECIAL_ABILITY_RESET(Player player)l
extern _native void UNK_0x4136829A(Player player)l
extern _native void SPECIAL_ABILITY_CHARGE_SMALL(Player player, bool p1, bool p2)l
extern _native void SPECIAL_ABILITY_CHARGE_MEDIUM(Player player, bool p1, bool p2)l
extern _native void SPECIAL_ABILITY_CHARGE_LARGE(Player player, bool p1, bool p2)l
extern _native void SPECIAL_ABILITY_CHARGE_CONTINUOUS(Player player, Ped p2)l
extern _native void SPECIAL_ABILITY_CHARGE_ABSOLUTE(Player player, int p1, bool p2)l
extern _native void SPECIAL_ABILITY_CHARGE_NORMALIZED(Player player, float normalizedValue, bool p2)l
extern _native void SPECIAL_ABILITY_FILL_METER(Player player, bool p1)l
extern _native void SPECIAL_ABILITY_DEPLETE_METER(Player player, bool p1)l
extern _native void SPECIAL_ABILITY_LOCK(Hash playerModel)l
extern _native void SPECIAL_ABILITY_UNLOCK(Hash playerModel)l
extern _native bool IS_SPECIAL_ABILITY_UNLOCKED(Hash playerModel)l
extern _native bool IS_SPECIAL_ABILITY_ACTIVE(Player player)l
extern _native bool IS_SPECIAL_ABILITY_METER_FULL(Player player)l
extern _native void ENABLE_SPECIAL_ABILITY(Player player, bool toggle)l
extern _native bool IS_SPECIAL_ABILITY_ENABLED(Player player)l
extern _native void SET_SPECIAL_ABILITY_MULTIPLIER(float multiplier)l
extern _native void UNK_0x5D0FE25B(Player player)l
extern _native bool UNK_0x46E7E31D(Player player)l
extern _native bool UNK_0x1E359CC8(Player player, int p1)l
extern _native bool UNK_0x8CB53C9F(Player player, float p1)l
extern _native void START_PLAYER_TELEPORT(Player player, vector3 vec, float heading, bool p5, bool p6, bool p7)l
extern _native void STOP_PLAYER_TELEPORT()l
extern _native bool IS_PLAYER_TELEPORT_ACTIVE()l
extern _native float GET_PLAYER_CURRENT_STEALTH_NOISE(Player player)l
extern _native void SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(Player player, float regenRate)l
extern _native void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float damageAmount)l
extern _native void SET_PLAYER_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native void SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player player, float damageAmount)l
extern _native void SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(Player player, float modifier)l
extern _native void SET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int tintIndex)l
extern _native void GET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int* tintIndex)l
extern _native void SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int index)l
extern _native void GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int* index)l
extern _native void SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int tintIndex)l
extern _native void GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int* tintIndex)l
extern _native void SET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)l
extern _native bool GET_PLAYER_HAS_RESERVE_PARACHUTE(Player player)l
extern _native void SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(Player player, bool enabled)l
extern _native void SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, RGB colour)l
extern _native void GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int* r, int* g, int* b)l
extern _native void SET_PLAYER_RESET_FLAG_PREFER_REAR_SEATS(Player player, int flags)l
extern _native void SET_PLAYER_NOISE_MULTIPLIER(Player player, float multiplier)l
extern _native void SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(Player player, float multiplier)l
extern _native bool CAN_PED_HEAR_PLAYER(Player player, Ped ped)l
extern _native void SIMULATE_PLAYER_INPUT_GAIT(Player player, float amount, int gaitType, float speed, bool p4, bool p5)l
extern _native void RESET_PLAYER_INPUT_GAIT(Player player)l
extern _native void SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(Player player, bool toggle)l
extern _native void UNK_0xA25D767E(Player player, bool p1)l
extern _native void SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(Player player, float value)l
extern _native bool UNK_0x1D371529(any p0)l
extern _native void UNK_0xE30A64DC(Player player)l
extern _native void SET_PLAYER_SIMULATE_AIMING(Player player, bool toggle)l
extern _native void SET_PLAYER_CLOTH_PIN_FRAMES(Player player, bool toggle)l
extern _native void SET_PLAYER_CLOTH_PACKAGE_INDEX(int index)l
extern _native void SET_PLAYER_CLOTH_LOCK_COUNTER(int value)l
extern _native void PLAYER_ATTACH_VIRTUAL_BOUND(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7)l
extern _native void PLAYER_DETACH_VIRTUAL_BOUND()l
extern _native bool HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(Player player)l
extern _native bool UNK_0x013B4F72(Player player)l
extern _native bool UNK_0x9DF75B2A(Player player, int p1, bool p2)l
extern _native bool IS_PLAYER_RIDING_TRAIN(Player player)l
extern _native bool HAS_PLAYER_LEFT_THE_WORLD(Player player)l
extern _native void UNK_0xAD8383FA(Player player, bool p1)l
extern _native void SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player, int p1, any p2, any p3, bool p4)l
extern _native void CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player)l
extern _native void SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model)l
extern _native void CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player)l
extern _native void SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player, Hash model)l
extern _native void CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player)l
extern _native void DISABLE_PLAYER_VEHICLE_REWARDS(Player player)l
extern _native void UNK_0x2849D4B2(bool p0)l
#pragma endregion //}
#pragma region ENTITY //{
extern _native bool DOES_ENTITY_EXIST(Entity entity)l
extern _native bool DOES_ENTITY_BELONG_TO_THIS_SCRIPT(Entity entity, bool p1)l
extern _native bool DOES_ENTITY_HAVE_DRAWABLE(Entity entity)l
extern _native bool DOES_ENTITY_HAVE_PHYSICS(Entity entity)l
extern _native bool HAS_ENTITY_ANIM_FINISHED(Entity entity, const char* animDict, const char* animName, int p3)l
extern _native bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity entity)l
extern _native bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity entity)l
extern _native bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity entity)l
extern _native bool HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2, bool p2)l
extern _native bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Entity entity1, Entity entity2, int traceType)l
extern _native bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Entity entity1, Entity entity2)l
extern _native bool HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity entity)l
extern _native Hash GET_LAST_MATERIAL_HIT_BY_ENTITY(Entity entity)l
extern _native vector3 GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(Entity entity)l
extern _native void FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(Entity entity)l
extern _native float GET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDict, const char* animName)l
extern _native float GET_ENTITY_ANIM_TOTAL_TIME(Entity entity, const char* animDict, const char* animName)l
extern _native float GET_ANIM_DURATION(const char* animDict, const char* animName)l
extern _native Entity GET_ENTITY_ATTACHED_TO(Entity entity)l
extern _native vector3 GET_ENTITY_COORDS(Entity entity, bool alive)l
extern _native vector3 GET_ENTITY_FORWARD_VECTOR(Entity entity)l
extern _native float GET_ENTITY_FORWARD_X(Entity entity)l
extern _native float GET_ENTITY_FORWARD_Y(Entity entity)l
extern _native float GET_ENTITY_HEADING(Entity entity)l
extern _native int GET_ENTITY_HEALTH(Entity entity)l
extern _native int GET_ENTITY_MAX_HEALTH(Entity entity)l
extern _native void SET_ENTITY_MAX_HEALTH(Entity entity, int value)l
extern _native float GET_ENTITY_HEIGHT(Entity entity, vector3 vec, bool atTop, bool inWorldCoords)l
extern _native float GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity entity)l
extern _native void GET_ENTITY_MATRIX(Entity entity, vector3* rightVector, vector3* forwardVector, vector3* upVector, vector3* position)l
extern _native Hash GET_ENTITY_MODEL(Entity entity)l
extern _native vector3 GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Entity entity, vector3 pos)l
extern _native vector3 GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity entity, vector3 offset)l
extern _native float GET_ENTITY_PITCH(Entity entity)l
extern _native void GET_ENTITY_QUATERNION(Entity entity, float* x, float* y, float* z, float* w)l
extern _native float GET_ENTITY_ROLL(Entity entity)l
extern _native vector3 GET_ENTITY_ROTATION(Entity entity, int rotationOrder)l
extern _native vector3 GET_ENTITY_ROTATION_VELOCITY(Entity entity)l
extern _native const char* GET_ENTITY_SCRIPT(Entity entity, ScrHandle* script)l
extern _native float GET_ENTITY_SPEED(Entity entity)l
extern _native vector3 GET_ENTITY_SPEED_VECTOR(Entity entity, bool relative)l
extern _native float GET_ENTITY_UPRIGHT_VALUE(Entity entity)l
extern _native vector3 GET_ENTITY_VELOCITY(Entity entity)l
extern _native Object GET_OBJECT_INDEX_FROM_ENTITY_INDEX(Entity entity)l
extern _native Ped GET_PED_INDEX_FROM_ENTITY_INDEX(Entity entity)l
extern _native Vehicle GET_VEHICLE_INDEX_FROM_ENTITY_INDEX(Entity entity)l
extern _native vector3 GET_WORLD_POSITION_OF_ENTITY_BONE(Entity entity, int boneIndex)l
extern _native Player GET_NEAREST_PLAYER_TO_ENTITY(Entity entity)l
extern _native Player GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM(Entity entity, int team)l
extern _native int GET_ENTITY_TYPE(Entity entity)l
extern _native int GET_ENTITY_POPULATION_TYPE(Entity entity)l
extern _native bool IS_AN_ENTITY(int handle)l
extern _native bool IS_ENTITY_A_PED(Entity entity)l
extern _native bool IS_ENTITY_A_MISSION_ENTITY(Entity entity)l
extern _native bool IS_ENTITY_A_VEHICLE(Entity entity)l
extern _native bool IS_ENTITY_AN_OBJECT(Entity entity)l
extern _native bool IS_ENTITY_AT_COORD(Entity entity, vector3 Pos, vector3 Size, bool p7, bool p8, int p9)l
extern _native bool IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, vector3 Size, bool p5, bool p6, int p7)l
extern _native bool IS_ENTITY_ATTACHED(Entity entity)l
extern _native bool IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Entity entity)l
extern _native bool IS_ENTITY_ATTACHED_TO_ANY_PED(Entity entity)l
extern _native bool IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Entity entity)l
extern _native bool IS_ENTITY_ATTACHED_TO_ENTITY(Entity from, Entity to)l
extern _native bool IS_ENTITY_DEAD(Entity entity)l
extern _native bool IS_ENTITY_IN_AIR(Entity entity)l
extern _native bool IS_ENTITY_IN_ANGLED_AREA(Entity entity, vector3 origin, vector3 edge, float angle, bool p8, bool p9, any p10)l
extern _native bool IS_ENTITY_IN_AREA(Entity entity, vector3 vec_1, vector3 vec_2, bool p7, bool p8, any p9)l
extern _native bool IS_ENTITY_IN_ZONE(Entity entity, const char* zone)l
extern _native bool IS_ENTITY_IN_WATER(Entity entity)l
extern _native float GET_ENTITY_SUBMERGED_LEVEL(Entity entity)l
extern _native void UNK_0x40C84A74(Entity entity, bool p1)l
extern _native bool IS_ENTITY_ON_SCREEN(Entity entity)l
extern _native bool IS_ENTITY_PLAYING_ANIM(Entity entity, const char* animDict, const char* animName, int p4)l
extern _native bool IS_ENTITY_STATIC(Entity entity)l
extern _native bool IS_ENTITY_TOUCHING_ENTITY(Entity entity, Entity targetEntity)l
extern _native bool IS_ENTITY_TOUCHING_MODEL(Entity entity, Hash modelHash)l
extern _native bool IS_ENTITY_UPRIGHT(Entity entity, float angle)l
extern _native bool IS_ENTITY_UPSIDEDOWN(Entity entity)l
extern _native bool IS_ENTITY_VISIBLE(Entity entity)l
extern _native bool IS_ENTITY_VISIBLE_TO_SCRIPT(Entity entity)l
extern _native bool IS_ENTITY_OCCLUDED(Entity entity)l
extern _native bool WOULD_ENTITY_BE_OCCLUDED(Hash entityModelHash, vector3 vec, bool p4)l
extern _native bool IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Entity entity)l
extern _native void APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(Entity entity, int forceType, vector3 vec, bool p5, bool isRel, bool highForce, bool p8)l
extern _native void APPLY_FORCE_TO_ENTITY(Entity entity, int forceType, vector3 vec, vector3 Rot, int p8, bool isRel, bool p10, bool highForce, bool p12, bool p13)l
extern _native void ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, vector3 Pos, vector3 Rot, bool p9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot)l
extern _native void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, vector3 Pos1, vector3 Pos2, vector3 Rot, float breakForce, bool fixedRot, bool p15, bool collision, bool p17, int p18)l
extern _native void PROCESS_ENTITY_ATTACHMENTS(Entity entity)l
extern _native int GET_ENTITY_BONE_INDEX_BY_NAME(Entity entity, const char* boneName)l
extern _native any CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity)l
extern _native void DELETE_ENTITY(Entity* entity)l
extern _native void DETACH_ENTITY(Entity entity, bool p1, bool collision)l
extern _native void FREEZE_ENTITY_POSITION(Entity entity, bool toggle)l
extern _native32(0xD3850671) void _SET_ENTITY_REGISTER(Entity entity, bool toggle)l
extern _native bool PLAY_ENTITY_ANIM(Entity entity, const char* animName, const char* animDict, float p3, bool loop, bool stayInAnim, bool p6, float delta, any bitset)l
extern _native bool PLAY_SYNCHRONIZED_ENTITY_ANIM(Entity entity, int syncedScene, const char* animation, const char* propName, float p4, float p5, any p6, float p7)l
extern _native bool PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(float p0, float p1, float p2, float p3, any p4, any p5, any* p6, any* p7, float p8, float p9, any p10, float p11)l
extern _native bool STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(float p0, float p1, float p2, float p3, any p4, float p5)l
extern _native any STOP_ENTITY_ANIM(Entity entity, const char* animation, const char* animGroup, float p3)l
extern _native bool STOP_SYNCHRONIZED_ENTITY_ANIM(Entity entity, float p1, bool p2)l
extern _native bool HAS_ANIM_EVENT_FIRED(Entity entity, Hash actionHash)l
extern _native bool FIND_ANIM_EVENT_PHASE(const char* animDictionary, const char* animName, const char* p2, any* p3, any* p4)l
extern _native void SET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDictionary, const char* animName, float time)l
extern _native void SET_ENTITY_ANIM_SPEED(Entity entity, const char* animDictionary, const char* animName, float speedMultiplier)l
extern _native void SET_ENTITY_AS_MISSION_ENTITY(Entity entity, bool p1, bool p2)l
extern _native void SET_ENTITY_AS_NO_LONGER_NEEDED(Entity* entity)l
extern _native void SET_PED_AS_NO_LONGER_NEEDED(Ped* ped)l
extern _native void SET_VEHICLE_AS_NO_LONGER_NEEDED(Vehicle* vehicle)l
extern _native void SET_OBJECT_AS_NO_LONGER_NEEDED(Object* object)l
extern _native void SET_ENTITY_CAN_BE_DAMAGED(Entity entity, bool toggle)l
extern _native void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool bCanBeDamaged, int relGroup)l
extern _native void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Entity entity, bool toggle)l
extern _native void SET_ENTITY_COLLISION(Entity entity, bool toggle, bool keepPhysics)l
extern _native bool GET_ENTITY_COLLISON_DISABLED(Entity entity)l
extern _native void SET_ENTITY_COORDS(Entity entity, vector3 Pos, bool xAxis, bool yAxis, bool zAxis, bool clearArea)l
extern _native void SET_ENTITY_COORDS_NO_OFFSET(Entity entity, vector3 Pos, bool xAxis, bool yAxis, bool zAxis)l
extern _native void SET_ENTITY_DYNAMIC(Entity entity, bool toggle)l
extern _native void SET_ENTITY_HEADING(Entity entity, float heading)l
extern _native void SET_ENTITY_HEALTH(Entity entity, int health)l
extern _native void SET_ENTITY_INVINCIBLE(Entity entity, bool toggle)l
extern _native void SET_ENTITY_IS_TARGET_PRIORITY(Entity entity, bool p1, float p2)l
extern _native void SET_ENTITY_LIGHTS(Entity entity, bool toggle)l
extern _native void SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, bool toggle)l
extern _native bool HAS_COLLISION_LOADED_AROUND_ENTITY(Entity entity)l
extern _native void SET_ENTITY_MAX_SPEED(Entity entity, float speed)l
extern _native void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Entity entity, bool toggle)l
extern _native void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool p1, any p2)l
extern _native void SET_ENTITY_PROOFS(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool p6, bool p7, bool drownProof)l
extern _native void SET_ENTITY_QUATERNION(Entity entity, quaternion quat)l
extern _native void SET_ENTITY_RECORDS_COLLISIONS(Entity entity, bool toggle)l
extern _native void SET_ENTITY_ROTATION(Entity entity, vector3 rot, int rotationOrder, bool p5)l
extern _native void SET_ENTITY_VISIBLE(Entity entity, bool toggle, bool unk)l
extern _native void SET_ENTITY_VELOCITY(Entity entity, vector3 vec)l
extern _native void SET_ENTITY_HAS_GRAVITY(Entity entity, bool toggle)l
extern _native void SET_ENTITY_LOD_DIST(Entity entity, int value)l
extern _native int GET_ENTITY_LOD_DIST(Entity entity)l
extern _native void SET_ENTITY_ALPHA(Entity entity, int alphaLevel, bool skin)l
extern _native int GET_ENTITY_ALPHA(Entity entity)l
extern _native any RESET_ENTITY_ALPHA(Entity entity)l
extern _native void SET_ENTITY_ALWAYS_PRERENDER(Entity entity, bool toggle)l
extern _native void SET_ENTITY_RENDER_SCORCHED(Entity entity, bool toggle)l
extern _native void SET_ENTITY_TRAFFICLIGHT_OVERRIDE(Entity entity, int state)l
extern _native void CREATE_MODEL_SWAP(vector3 vec, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native void REMOVE_MODEL_SWAP(vector3 vec, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native void CREATE_MODEL_HIDE(vector3 vec, float radius, Hash model, bool p5)l
extern _native void CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(vector3 vec, float radius, Hash model, bool p5)l
extern _native void REMOVE_MODEL_HIDE(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void CREATE_FORCED_OBJECT(vector3 vec, any p3, Hash modelHash, bool p5)l
extern _native void REMOVE_FORCED_OBJECT(any p0, any p1, any p2, any p3, any p4)l
extern _native void SET_ENTITY_NO_COLLISION_ENTITY(Entity entity1, Entity entity2, bool unknown)l
extern _native void SET_ENTITY_MOTION_BLUR(Entity entity, bool toggle)l
extern _native void UNK_0x44767B31(Entity entity, bool p1)l
extern _native void UNK_0xE224A6A5(Entity entity, bool p1)l
#pragma endregion //}
#pragma region PED //{
extern _native Ped CREATE_PED(int pedType, Hash modelHash, vector3 vec, float heading, bool isNetwork, bool p7)l
extern _native void DELETE_PED(Ped* ped)l
extern _native Ped CLONE_PED(Ped ped, float heading, bool isNetwork, bool p3)l
extern _native void CLONE_PED_TO_TARGET(Ped ped, Ped targetPed)l
extern _native bool IS_PED_IN_VEHICLE(Ped ped, Vehicle vehicle, bool atGetIn)l
extern _native bool IS_PED_IN_MODEL(Ped ped, Hash modelHash)l
extern _native bool IS_PED_IN_ANY_VEHICLE(Ped ped, bool atGetIn)l
extern _native bool IS_COP_PED_IN_AREA_3D(vector3 vec_1, vector3 vec_2)l
extern _native bool IS_PED_INJURED(Ped ped)l
extern _native bool IS_PED_HURT(Ped ped)l
extern _native bool IS_PED_FATALLY_INJURED(Ped ped)l
extern _native bool IS_PED_DEAD_OR_DYING(Ped ped, bool p1)l
extern _native bool IS_CONVERSATION_PED_DEAD(Ped ped)l
extern _native bool IS_PED_AIMING_FROM_COVER(Ped ped)l
extern _native bool IS_PED_RELOADING(Ped ped)l
extern _native bool IS_PED_A_PLAYER(Ped ped)l
extern _native Ped CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, bool isNetwork, bool p5)l
extern _native void SET_PED_DESIRED_HEADING(Ped ped, float heading)l
extern _native32(0x290421BE) void _FREEZE_PED_CAMERA_ROTATION(Ped ped)l
extern _native bool IS_PED_FACING_PED(Ped ped, Ped otherPed, float angle)l
extern _native bool IS_PED_IN_MELEE_COMBAT(Ped ped)l
extern _native bool IS_PED_STOPPED(Ped ped)l
extern _native bool IS_PED_SHOOTING_IN_AREA(Ped ped, vector3 vec_1, vector3 vec_2, bool p7, bool p8)l
extern _native bool IS_ANY_PED_SHOOTING_IN_AREA(vector3 vec_1, vector3 vec_2, bool p6, bool p7)l
extern _native bool IS_PED_SHOOTING(Ped ped)l
extern _native any SET_PED_ACCURACY(Ped ped, int accuracy)l
extern _native int GET_PED_ACCURACY(Ped ped)l
extern _native bool IS_PED_MODEL(Ped ped, Hash modelHash)l
extern _native void EXPLODE_PED_HEAD(Ped ped, Hash weaponHash)l
extern _native void REMOVE_PED_ELEGANTLY(Ped* ped)l
extern _native void ADD_ARMOUR_TO_PED(Ped ped, int amount)l
extern _native void SET_PED_ARMOUR(Ped ped, int amount)l
extern _native void SET_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seatIndex)l
extern _native void SET_PED_ALLOW_VEHICLES_OVERRIDE(Ped ped, bool toggle)l
extern _native bool CAN_CREATE_RANDOM_PED(bool unk)l
extern _native Ped CREATE_RANDOM_PED(vector3 pos)l
extern _native Ped CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicle, bool returnHandle)l
extern _native bool CAN_CREATE_RANDOM_DRIVER()l
extern _native bool CAN_CREATE_RANDOM_BIKE_RIDER()l
extern _native void SET_PED_MOVE_ANIMS_BLEND_OUT(Ped ped)l
extern _native void SET_PED_CAN_BE_DRAGGED_OUT(Ped ped, bool toggle)l
extern _native void UNK_0x6CD58238(bool toggle)l
extern _native bool IS_PED_MALE(Ped ped)l
extern _native bool IS_PED_HUMAN(Ped ped)l
extern _native Vehicle GET_VEHICLE_PED_IS_IN(Ped ped, bool lastVehicle)l
extern _native void RESET_PED_LAST_VEHICLE(Ped ped)l
extern _native void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0, float p1)l
extern _native void UNK_0xB48C0C04()l
extern _native void SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(vector3 vec)l
extern _native void SET_PED_NON_CREATION_AREA(vector3 vec_1, vector3 vec_2)l
extern _native void CLEAR_PED_NON_CREATION_AREA()l
extern _native void UNK_0x8C555ADD()l
extern _native bool IS_PED_ON_MOUNT(Ped ped)l
extern _native Ped GET_MOUNT(Ped ped)l
extern _native bool IS_PED_ON_VEHICLE(Ped ped)l
extern _native bool IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle vehicle)l
extern _native void SET_PED_MONEY(Ped ped, int amount)l
extern _native int GET_PED_MONEY(Ped ped)l
extern _native void UNK_0xD41C9AED(float p0, any p1)l
extern _native void UNK_0x30B98369(bool p0)l
extern _native void UNK_0x02A080C8(bool p0)l
extern _native void SET_PED_SUFFERS_CRITICAL_HITS(Ped ped, bool toggle)l
extern _native void UNK_0x1572022A(Ped ped, bool toggle)l
extern _native bool IS_PED_SITTING_IN_VEHICLE(Ped ped, Vehicle vehicle)l
extern _native bool IS_PED_SITTING_IN_ANY_VEHICLE(Ped ped)l
extern _native bool IS_PED_ON_FOOT(Ped ped)l
extern _native bool IS_PED_ON_ANY_BIKE(Ped ped)l
extern _native bool IS_PED_PLANTING_BOMB(Ped ped)l
extern _native vector3 GET_DEAD_PED_PICKUP_COORDS(Ped ped, float p1, float p2)l
extern _native bool IS_PED_IN_ANY_BOAT(Ped ped)l
extern _native bool IS_PED_IN_ANY_SUB(Ped ped)l
extern _native bool IS_PED_IN_ANY_HELI(Ped ped)l
extern _native bool IS_PED_IN_ANY_PLANE(Ped ped)l
extern _native bool IS_PED_IN_FLYING_VEHICLE(Ped ped)l
extern _native void SET_PED_DIES_IN_WATER(Ped ped, bool toggle)l
extern _native void SET_PED_DIES_IN_SINKING_VEHICLE(Ped ped, bool toggle)l
extern _native int GET_PED_ARMOUR(Ped ped)l
extern _native void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_BE_SHOT_IN_VEHICLE(Ped ped, bool toggle)l
extern _native bool GET_PED_LAST_DAMAGE_BONE(Ped ped, int* outBone)l
extern _native void CLEAR_PED_LAST_DAMAGE_BONE(Ped ped)l
extern _native void SET_AI_WEAPON_DAMAGE_MODIFIER(float value)l
extern _native void RESET_AI_WEAPON_DAMAGE_MODIFIER()l
extern _native void SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(float modifier)l
extern _native void RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER()l
extern _native void UNK_0xCC9D7F1A(any p0, bool p1)l
extern _native void SET_PED_CAN_BE_TARGETTED(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_BE_TARGETTED_BY_TEAM(Ped ped, int team, bool toggle)l
extern _native void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Ped ped, Player player, bool toggle)l
extern _native void UNK_0x7DA12905(any p0, bool p1)l
extern _native void SET_TIME_EXCLUSIVE_DISPLAY_TEXTURE(any p0, bool p1)l
extern _native bool IS_PED_IN_ANY_POLICE_VEHICLE(Ped ped)l
extern _native void FORCE_PED_TO_OPEN_PARACHUTE(Ped ped)l
extern _native bool IS_PED_IN_PARACHUTE_FREE_FALL(Ped ped)l
extern _native bool IS_PED_FALLING(Ped ped)l
extern _native bool IS_PED_JUMPING(Ped ped)l
extern _native bool IS_PED_CLIMBING(Ped ped)l
extern _native bool IS_PED_VAULTING(Ped ped)l
extern _native bool IS_PED_DIVING(Ped ped)l
extern _native bool IS_PED_JUMPING_OUT_OF_VEHICLE(Ped ped)l
extern _native int GET_PED_PARACHUTE_STATE(Ped ped)l
extern _native int GET_PED_PARACHUTE_LANDING_TYPE(Ped ped)l
extern _native void SET_PED_PARACHUTE_TINT_INDEX(Ped ped, int tintIndex)l
extern _native void GET_PED_PARACHUTE_TINT_INDEX(Ped ped, int* outTintIndex)l
extern _native void SET_PED_RESERVE_PARACHUTE_TINT_INDEX(Ped ped, any p1)l
extern _native void SET_PED_DUCKING(Ped ped, bool toggle)l
extern _native bool IS_PED_DUCKING(Ped ped)l
extern _native bool IS_PED_IN_ANY_TAXI(Ped ped)l
extern _native void SET_PED_ID_RANGE(Ped ped, float value)l
extern _native void UNK_0x9A2180FF(Ped ped, bool p1)l
extern _native void UNK_0xF30658D2(Ped ped, float unk)l
extern _native void UNK_0x43709044(any p0)l
extern _native void SET_PED_SEEING_RANGE(Ped ped, float value)l
extern _native void SET_PED_HEARING_RANGE(Ped ped, float value)l
extern _native void SET_PED_VISUAL_FIELD_MIN_ANGLE(Ped ped, float value)l
extern _native void SET_PED_VISUAL_FIELD_MAX_ANGLE(Ped ped, float value)l
extern _native void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Ped ped, float angle)l
extern _native void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Ped ped, float angle)l
extern _native void SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Ped ped, float range)l
extern _native void SET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped, float angle)l
extern _native void SET_PED_STEALTH_MOVEMENT(Ped ped, bool p1, const char* action)l
extern _native bool GET_PED_STEALTH_MOVEMENT(Ped ped)l
extern _native int CREATE_GROUP(int unused)l
extern _native void SET_PED_AS_GROUP_LEADER(Ped ped, int groupId)l
extern _native void SET_PED_AS_GROUP_MEMBER(Ped ped, int groupId)l
extern _native void SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(Ped pedHandle, int groupHandle, bool toggle)l
extern _native void REMOVE_GROUP(int groupId)l
extern _native void REMOVE_PED_FROM_GROUP(Ped ped)l
extern _native bool IS_PED_GROUP_MEMBER(Ped ped, int groupId)l
extern _native bool IS_PED_HANGING_ON_TO_VEHICLE(Ped ped)l
extern _native void SET_GROUP_SEPARATION_RANGE(int groupHandle, float separationRange)l
extern _native void SET_PED_MIN_GROUND_TIME_FOR_STUNGUN(Ped ped, int ms)l
extern _native bool IS_PED_PRONE(Ped ped)l
extern _native bool IS_PED_IN_COMBAT(Ped ped, Ped target)l
extern _native bool CAN_PED_IN_COMBAT_SEE_TARGET(Ped ped, Ped target)l
extern _native bool IS_PED_DOING_DRIVEBY(Ped ped)l
extern _native bool IS_PED_JACKING(Ped ped)l
extern _native bool IS_PED_BEING_JACKED(Ped ped)l
extern _native bool IS_PED_BEING_STUNNED(Ped ped, int p1)l
extern _native Ped GET_PEDS_JACKER(Ped ped)l
extern _native Ped GET_JACK_TARGET(Ped ped)l
extern _native bool IS_PED_FLEEING(Ped ped)l
extern _native bool IS_PED_IN_COVER(Ped ped, bool p1)l
extern _native bool IS_PED_IN_COVER_FACING_LEFT(Ped ped)l
extern _native bool IS_PED_GOING_INTO_COVER(Ped ped)l
extern _native any SET_PED_PINNED_DOWN(Ped ped, bool pinned, int i)l
extern _native int GET_SEAT_PED_IS_TRYING_TO_ENTER(Ped ped)l
extern _native Vehicle GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Ped ped)l
extern _native Entity GET_PED_SOURCE_OF_DEATH(Ped ped)l
extern _native Hash GET_PED_CAUSE_OF_DEATH(Ped ped)l
extern _native int UNK_0xEF0B78E6(any p0)l
extern _native any UNK_0xFB18CB19(any p0, float p1, float p2, float p3, float p4)l
extern _native void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped, Hash hash)l
extern _native void SET_PED_RELATIONSHIP_GROUP_HASH(Ped ped, Hash hash)l
extern _native void SET_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)l
extern _native void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)l
extern _native any ADD_RELATIONSHIP_GROUP(const char* name, Hash* groupHash)l
extern _native void REMOVE_RELATIONSHIP_GROUP(Hash groupHash)l
extern _native int GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2)l
extern _native Hash GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped)l
extern _native Hash GET_PED_RELATIONSHIP_GROUP_HASH(Ped ped)l
extern _native int GET_RELATIONSHIP_BETWEEN_GROUPS(Hash group1, Hash group2)l
extern _native void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Ped ped, bool toggle)l
extern _native void SET_PED_TO_INFORM_RESPECTED_FRIENDS(Ped ped, float radius, int maxFriends)l
extern _native bool IS_PED_RESPONDING_TO_EVENT(Ped ped, any event)l
extern _native void SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash)l
extern _native void SET_PED_SHOOT_RATE(Ped ped, int shootRate)l
extern _native void SET_COMBAT_FLOAT(Ped ped, int combatType, float p2)l
extern _native float GET_COMBAT_FLOAT(Ped ped, int p1)l
extern _native void GET_GROUP_SIZE(int groupID, any* unknown, int* sizeInMembers)l
extern _native bool DOES_GROUP_EXIST(int groupId)l
extern _native int GET_PED_GROUP_INDEX(Ped ped)l
extern _native bool IS_PED_IN_GROUP(Ped ped)l
extern _native Player GET_PLAYER_PED_IS_FOLLOWING(Ped ped)l
extern _native void SET_GROUP_FORMATION(int groupId, int formationType)l
extern _native void SET_GROUP_FORMATION_SPACING(int groupId, float p1, float p2, float p3)l
extern _native void RESET_GROUP_FORMATION_DEFAULT_SPACING(int groupHandle)l
extern _native Vehicle GET_VEHICLE_PED_IS_USING(Ped ped)l
extern _native Vehicle SET_EXCLUSIVE_PHONE_RELATIONSHIPS(Ped ped)l
extern _native void SET_PED_GRAVITY(Ped ped, bool toggle)l
extern _native void APPLY_DAMAGE_TO_PED(Ped ped, int damageAmount, bool p2)l
extern _native void SET_PED_ALLOWED_TO_DUCK(Ped ped, bool toggle)l
extern _native void SET_PED_NEVER_LEAVES_GROUP(Ped ped, bool toggle)l
extern _native int GET_PED_TYPE(Ped ped)l
extern _native void SET_PED_AS_COP(Ped ped, bool toggle)l
extern _native void SET_PED_MAX_HEALTH(Ped ped, int value)l
extern _native int GET_PED_MAX_HEALTH(Ped ped)l
extern _native void SET_PED_MAX_TIME_IN_WATER(Ped ped, float value)l
extern _native void SET_PED_MAX_TIME_UNDERWATER(Ped ped, float value)l
extern _native void UNK_0x373CC405(Ped ped, float p1)l
extern _native void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped ped, int state)l
extern _native bool CAN_KNOCK_PED_OFF_VEHICLE(Ped ped)l
extern _native void KNOCK_PED_OFF_VEHICLE(Ped ped)l
extern _native void SET_PED_COORDS_NO_GANG(Ped ped, vector3 pos)l
extern _native Ped GET_PED_AS_GROUP_MEMBER(int groupID, int memberNumber)l
extern _native void SET_PED_KEEP_TASK(Ped ped, bool toggle)l
extern _native void UNK_0x397F06E3(Ped ped, bool p1)l
extern _native bool IS_PED_SWIMMING(Ped ped)l
extern _native bool IS_PED_SWIMMING_UNDER_WATER(Ped ped)l
extern _native void SET_PED_COORDS_KEEP_VEHICLE(Ped ped, vector3 pos)l
extern _native void SET_PED_DIES_IN_VEHICLE(Ped ped, bool toggle)l
extern _native void SET_CREATE_RANDOM_COPS(bool toggle)l
extern _native void SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(bool toggle)l
extern _native void SET_CREATE_RANDOM_COPS_ON_SCENARIOS(bool toggle)l
extern _native bool CAN_CREATE_RANDOM_COPS()l
extern _native void SET_PED_AS_ENEMY(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_SMASH_GLASS(Ped ped, bool p1, bool p2)l
extern _native bool IS_PED_IN_ANY_TRAIN(Ped ped)l
extern _native bool IS_PED_GETTING_INTO_A_VEHICLE(Ped ped)l
extern _native bool IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(Ped ped)l
extern _native void SET_ENABLE_HANDCUFFS(Ped ped, bool toggle)l
extern _native void SET_ENABLE_BOUND_ANKLES(Ped ped, bool toggle)l
extern _native void SET_ENABLE_SCUBA(Ped ped, bool toggle)l
extern _native void SET_CAN_ATTACK_FRIENDLY(Ped ped, bool toggle, bool p2)l
extern _native int GET_PED_ALERTNESS(Ped ped)l
extern _native void SET_PED_ALERTNESS(Ped ped, int value)l
extern _native void SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(Ped ped, bool toggle)l
extern _native void SET_PED_MOVEMENT_CLIPSET(Ped ped, const char* clipSet, float p2)l
extern _native void RESET_PED_MOVEMENT_CLIPSET(Ped ped, float p1)l
extern _native void SET_PED_STRAFE_CLIPSET(Ped ped, const char* clipSet)l
extern _native void RESET_PED_STRAFE_CLIPSET(Ped ped)l
extern _native void SET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped, const char* clipSet)l
extern _native void RESET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped)l
extern _native void SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped, const char* clipset)l
extern _native void CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped)l
extern _native void SET_PED_IN_VEHICLE_CONTEXT(Ped ped, Hash context)l
extern _native void RESET_PED_IN_VEHICLE_CONTEXT(Ped ped)l
extern _native bool IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(Ped ped, const char* animDict, const char* anim)l
extern _native void SET_PED_ALTERNATE_WALK_ANIM(Ped ped, const char* animDict, const char* animName, float p3, bool p4)l
extern _native void CLEAR_PED_ALTERNATE_WALK_ANIM(Ped ped, float p1)l
extern _native void SET_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, const char* animDictionary, const char* animationName, float p4, bool p5)l
extern _native void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, float p2)l
extern _native void SET_PED_GESTURE_GROUP(Ped ped, const char* animGroupGesture)l
extern _native vector3 GET_ANIM_INITIAL_OFFSET_POSITION(const char* animDict, const char* animName, vector3 vec, vector3 Rot, float p8, int p9)l
extern _native vector3 GET_ANIM_INITIAL_OFFSET_ROTATION(const char* animDict, const char* animName, vector3 vec, vector3 Rot, float p8, int p9)l
extern _native int GET_PED_DRAWABLE_VARIATION(Ped ped, int componentId)l
extern _native int GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped ped, int componentId)l
extern _native int GET_PED_TEXTURE_VARIATION(Ped ped, int componentId)l
extern _native int GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped ped, int componentId, int drawableId)l
extern _native int GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Ped ped, int propId)l
extern _native int GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Ped ped, int propId, int drawableId)l
extern _native int GET_PED_PALETTE_VARIATION(Ped ped, int componentId)l
extern _native bool IS_PED_COMPONENT_VARIATION_VALID(Ped ped, int componentId, int drawableId, int textureId)l
extern _native void SET_PED_COMPONENT_VARIATION(Ped ped, int componentId, int drawableId, int textureId, int paletteId)l
extern _native void SET_PED_RANDOM_COMPONENT_VARIATION(Ped ped, bool p1)l
extern _native void SET_PED_RANDOM_PROPS(Ped ped)l
extern _native void SET_PED_DEFAULT_COMPONENT_VARIATION(Ped ped)l
extern _native void SET_PED_BLEND_FROM_PARENTS(Ped ped, any p1, any p2, float p3, float p4)l
extern _native void SET_PED_HEAD_BLEND_DATA(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, bool isParent)l
extern _native void UPDATE_PED_HEAD_BLEND_DATA(Ped ped, float shapeMix, float skinMix, float thirdMix)l
extern _native void SET_PED_HEAD_OVERLAY(Ped ped, int overlayID, int index, float opacity)l
extern _native32(0xFF43C18D) int _GET_NUM_HEAD_OVERLAY_VALUES(int overlayID)l
extern _native bool HAS_PED_HEAD_BLEND_FINISHED(Ped ped)l
extern _native void UNK_0x894314A4(Ped ped)l
extern _native void UNK_0x57E5B3F9(Ped ped, RGB colour, int p4)l
extern _native void UNK_0xC6F36292(any p0)l
extern _native32(0x211DEFEC) int _GET_FIRST_PARENT_ID_FOR_PED_TYPE(int type)l
extern _native32(0x095D3BD8) int _GET_NUM_PARENT_PEDS_OF_TYPE(int type)l
extern _native any UNK_0x45F3BDFB(Ped ped, int p1, int drawableId, int textureId)l
extern _native bool UNK_0xC6517D52(Ped p0)l
extern _native void UNK_0x6435F67F(any p0)l
extern _native32(0xC0E23671) bool _IS_PED_PROP_VALID(Ped ped, int componentId, int drawableId, int TextureId)l
extern _native bool UNK_0x3B0CA391(Ped ped)l
extern _native void UNK_0xFD103BA7(Ped ped)l
extern _native int GET_PED_PROP_INDEX(Ped ped, int componentId)l
extern _native void SET_PED_PROP_INDEX(Ped ped, int componentId, int drawableId, int TextureId, bool attach)l
extern _native void KNOCK_OFF_PED_PROP(Ped ped, bool p1, bool p2, bool p3, bool p4)l
extern _native void CLEAR_PED_PROP(Ped ped, int propId)l
extern _native void CLEAR_ALL_PED_PROPS(Ped ped)l
extern _native int GET_PED_PROP_TEXTURE_INDEX(Ped ped, int componentId)l
extern _native void UNK_0x7BCD8991(any p0)l
extern _native void UNK_0x080275EE(any p0)l
extern _native void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)l
extern _native void SET_PED_BOUNDS_ORIENTATION(Ped ped, float p1, float p2, float p3, float p4, float p5)l
extern _native void REGISTER_TARGET(Ped ped, Ped target)l
extern _native void REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius)l
extern _native Ped GET_RANDOM_PED_AT_COORD(vector3 vec, vector3 Radius, int pedType)l
extern _native bool GET_CLOSEST_PED(vector3 vec, float radius, bool p4, bool p5, Ped* outPed, bool p7, bool p8, int pedType)l
extern _native void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(bool value)l
extern _native bool UNK_0x18DD76A1(Ped ped, bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, any p8)l
extern _native void UNK_0x6D55B3B3(Ped driver, float p1)l
extern _native void SET_DRIVER_ABILITY(Ped driver, float ability)l
extern _native void SET_DRIVER_AGGRESSIVENESS(Ped driver, float aggressiveness)l
extern _native bool CAN_PED_RAGDOLL(Ped ped)l
extern _native bool SET_PED_TO_RAGDOLL(Ped ped, int time1, int time2, int ragdollType, bool p4, bool p5, bool p6)l
extern _native bool SET_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int time, int p2, int ragdollType, vector3 vec, float p7, float p8, float p9, float p10, float p11, float p12, float p13)l
extern _native void SET_PED_RAGDOLL_ON_COLLISION(Ped ped, bool toggle)l
extern _native bool IS_PED_RAGDOLL(Ped ped)l
extern _native bool IS_PED_RUNNING_RAGDOLL_TASK(Ped ped)l
extern _native any SET_PED_RAGDOLL_FORCE_FALL(Ped ped)l
extern _native void RESET_PED_RAGDOLL_TIMER(Ped ped)l
extern _native void SET_PED_CAN_RAGDOLL(Ped ped, bool toggle)l
extern _native bool IS_PED_RUNNING_MOBILE_PHONE_TASK(Ped ped)l
extern _native bool UNK_0x97353375(Ped ped)l
extern _native32(0x9C8F830D) void _SET_PED_RAGDOLL_BLOCKING_FLAGS(Ped ped, int flags)l
extern _native32(0x77CBA290) void _RESET_PED_RAGDOLL_BLOCKING_FLAGS(Ped ped, int flags)l
extern _native void SET_PED_ANGLED_DEFENSIVE_AREA(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8, bool p9)l
extern _native void SET_PED_SPHERE_DEFENSIVE_AREA(Ped ped, vector3 vec, float radius, bool p5, bool p6)l
extern _native void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(Ped ped, Ped target, vector3 Offset, float radius, bool p6)l
extern _native void UNK_0x4763B2C6(Ped ped, any p1, float p2, float p3, float p4, float p5, bool p6)l
extern _native void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9, bool p10)l
extern _native void SET_PED_DEFENSIVE_AREA_DIRECTION(Ped ped, float p1, float p2, float p3, bool p4)l
extern _native void REMOVE_PED_DEFENSIVE_AREA(Ped ped, bool toggle)l
extern _native vector3 GET_PED_DEFENSIVE_AREA_POSITION(Ped ped, bool p1)l
extern _native void SET_PED_PREFERRED_COVER_SET(Ped ped, any itemSet)l
extern _native void REMOVE_PED_PREFERRED_COVER_SET(Ped ped)l
extern _native void REVIVE_INJURED_PED(Ped ped)l
extern _native void RESURRECT_PED(Ped ped)l
extern _native void SET_PED_NAME_DEBUG(Ped ped, const char* name)l
extern _native vector3 GET_PED_EXTRACTED_DISPLACEMENT(Ped ped, bool worldSpace)l
extern _native any SET_PED_DIES_WHEN_INJURED(Ped ped, bool toggle)l
extern _native any SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, bool toggle)l
extern _native void UNK_0x141CC936(Ped ped, bool p1)l
extern _native any RESET_PED_VISIBLE_DAMAGE(Ped ped)l
extern _native void APPLY_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, any p1, float p2, float p3, any p4)l
extern _native void APPLY_PED_BLOOD(Ped ped, int boneIndex, vector3 Rot, const char* woundType)l
extern _native void APPLY_PED_BLOOD_BY_ZONE(Ped ped, any p1, float p2, float p3, any* p4)l
extern _native void APPLY_PED_BLOOD_SPECIFIC(Ped ped, any p1, float p2, float p3, float p4, float p5, any p6, float p7, any* p8)l
extern _native void APPLY_PED_DAMAGE_DECAL(Ped ped, int p1, float p2, float p3, float p4, float p5, float p6, int p7, bool p8, const char* p9)l
extern _native void APPLY_PED_DAMAGE_PACK(Ped ped, const char* damagePack, float damage, float mult)l
extern _native void CLEAR_PED_BLOOD_DAMAGE(Ped ped)l
extern _native void CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, int p1)l
extern _native void HIDE_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, any p1, bool p2)l
extern _native void CLEAR_PED_DAMAGE_DECAL_BY_ZONE(Ped ped, int p1, const char* p2)l
extern _native any GET_PED_DECORATIONS_STATE(Ped ped)l
extern _native void CLEAR_PED_WETNESS(Ped ped)l
extern _native void SET_PED_WETNESS_HEIGHT(Ped ped, float height)l
extern _native void SET_PED_WETNESS_ENABLED_THIS_FRAME(Ped ped)l
extern _native any UNK_0xA993915F(Ped ped)l
extern _native void SET_PED_SWEAT(Ped ped, float sweat)l
extern _native32(0x70559AC7) void _SET_PED_DECORATION(Ped ped, Hash collection, Hash overlay)l
extern _native32(0x3543019E) int _GET_TATTOO_ZONE(Hash collection, Hash overlay)l
extern _native void CLEAR_PED_DECORATIONS(Ped ped)l
extern _native32(0xEFD58EB9) void _CLEAR_PED_FACIAL_DECORATIONS(Ped ped)l
extern _native bool WAS_PED_SKELETON_UPDATED(Ped ped)l
extern _native vector3 GET_PED_BONE_COORDS(Ped ped, int boneId, vector3 offset)l
extern _native void CREATE_NM_MESSAGE(bool startImmediately, int messageId)l
extern _native void GIVE_PED_NM_MESSAGE(Ped ped)l
extern _native any ADD_SCENARIO_BLOCKING_AREA(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9)l
extern _native void REMOVE_SCENARIO_BLOCKING_AREAS()l
extern _native void REMOVE_SCENARIO_BLOCKING_AREA(any p0, bool p1)l
extern _native void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(any p0, any p1, any p2, any p3, any p4)l
extern _native bool IS_PED_USING_SCENARIO(Ped ped, const char* scenario)l
extern _native bool IS_PED_USING_ANY_SCENARIO(Ped ped)l
extern _native any UNK_0x59DE73AC(any p0, any p1, any p2, any p3)l
extern _native void UNK_0xC08FE5F6(any p0, bool p1)l
extern _native any UNK_0x58C0F6CF(any p0, any p1, any p2, any p3)l
extern _native any UNK_0x761F8F48(any p0, any p1, any p2, any p3)l
extern _native void UNK_0x033F43FA(any p0)l
extern _native void UNK_0x4C684C81(any p0)l
extern _native any UNK_0x7B4C3E6F(any p0, any p1, any p2, any p3)l
extern _native void UNK_0x5BC276AE(Ped ped, bool p1)l
extern _native void PLAY_FACIAL_ANIM(Ped ped, const char* animName, const char* animDict)l
extern _native void SET_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped, const char* animName, const char* animDict)l
extern _native void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped)l
extern _native void SET_PED_CAN_PLAY_GESTURE_ANIMS(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_PLAY_VISEME_ANIMS(Ped ped, bool toggle, bool p2)l
extern _native void UNK_0xADB2511A(Ped ped, bool p1)l
extern _native void SET_PED_CAN_PLAY_AMBIENT_ANIMS(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Ped ped, bool toggle)l
extern _native void UNK_0xB7CD0A49(Ped ped)l
extern _native void SET_PED_CAN_ARM_IK(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_HEAD_IK(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_LEG_IK(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_TORSO_IK(Ped ped, bool toggle)l
extern _native void UNK_0x7B0040A8(Ped ped, bool p1)l
extern _native void UNK_0x0FDA62DE(Ped ped, bool p1)l
extern _native void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Ped ped, bool toggle)l
extern _native bool IS_PED_HEADTRACKING_PED(Ped ped1, Ped ped2)l
extern _native bool IS_PED_HEADTRACKING_ENTITY(Ped ped, Entity entity)l
extern _native void SET_PED_PRIMARY_LOOKAT(Ped ped, Ped lookAt)l
extern _native void UNK_0xFC942D7C(any p0, any p1)l
extern _native void SET_PED_CLOTH_PRONE(any p0, any p1)l
extern _native void SET_PED_CONFIG_FLAG(Ped ped, int flagId, bool value)l
extern _native void SET_PED_RESET_FLAG(Ped ped, int flagId, bool doReset)l
extern _native bool GET_PED_CONFIG_FLAG(Ped ped, int flagId, bool p2)l
extern _native bool GET_PED_RESET_FLAG(Ped ped, int flagId)l
extern _native void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Ped ped, int index)l
extern _native void SET_PED_CAN_EVASIVE_DIVE(Ped ped, bool toggle)l
extern _native bool IS_PED_EVASIVE_DIVING(Ped ped, Entity* evadingEntity)l
extern _native void SET_PED_SHOOTS_AT_COORD(Ped ped, vector3 vec, bool toggle)l
extern _native void SET_PED_MODEL_IS_SUPPRESSED(Ped ped, bool toggle)l
extern _native void STOP_ANY_PED_MODEL_BEING_SUPPRESSED()l
extern _native void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Ped ped, bool toggle)l
extern _native void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, bool toggle)l
extern _native void UNK_0xFF1F6AEB(Ped ped, bool p1)l
extern _native void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, bool toggle)l
extern _native void GIVE_PED_HELMET(Ped ped, bool cannotRemove, int helmetFlag, int textureIndex)l
extern _native void REMOVE_PED_HELMET(Ped ped, bool instantly)l
extern _native void SET_PED_HELMET(Ped ped, bool canWearHelmet)l
extern _native void SET_PED_HELMET_FLAG(Ped ped, int helmetFlag)l
extern _native void SET_PED_HELMET_PROP_INDEX(Ped ped, int propIndex)l
extern _native void SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int textureIndex)l
extern _native bool IS_PED_WEARING_HELMET(Ped ped)l
extern _native void UNK_0x24A1284E(Ped ped)l
extern _native any UNK_0x8A3A3116(any p0)l
extern _native any UNK_0x74EB662D(any p0)l
extern _native bool UNK_0xFFF149FE(any p0)l
extern _native void SET_PED_TO_LOAD_COVER(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_COWER_IN_COVER(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_PEEK_IN_COVER(Ped ped, bool toggle)l
extern _native void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Ped ped, bool toggle)l
extern _native void SET_PED_LEG_IK_MODE(Ped ped, int mode)l
extern _native void SET_PED_MOTION_BLUR(Ped ped, bool toggle)l
extern _native void SET_PED_CAN_SWITCH_WEAPON(Ped ped, bool toggle)l
extern _native void SET_PED_DIES_INSTANTLY_IN_WATER(Ped ped, bool toggle)l
extern _native void UNK_0x77BB7CB8(Ped ped, int p1)l
extern _native void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped)l
extern _native void SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float p1)l
extern _native void SET_PED_COMBAT_MOVEMENT(Ped ped, int combatMovement)l
extern _native int GET_PED_COMBAT_MOVEMENT(Ped ped)l
extern _native void SET_PED_COMBAT_ABILITY(Ped ped, int p1)l
extern _native void SET_PED_COMBAT_RANGE(Ped ped, int p1)l
extern _native any GET_PED_COMBAT_RANGE(Ped ped)l
extern _native void SET_PED_COMBAT_ATTRIBUTES(Ped ped, int attributeIndex, bool enabled)l
extern _native void SET_PED_TARGET_LOSS_RESPONSE(Ped ped, int responseType)l
extern _native bool UNK_0x139C0875(Ped ped)l
extern _native bool IS_PED_PERFORMING_STEALTH_KILL(Ped ped)l
extern _native bool UNK_0x9BE7C860(Ped ped)l
extern _native bool IS_PED_BEING_STEALTH_KILLED(Ped ped)l
extern _native Ped GET_MELEE_TARGET_FOR_PED(Ped ped)l
extern _native bool WAS_PED_KILLED_BY_STEALTH(Ped ped)l
extern _native bool WAS_PED_KILLED_BY_TAKEDOWN(Ped ped)l
extern _native bool UNK_0x3993092B(Ped ped)l
extern _native void SET_PED_FLEE_ATTRIBUTES(Ped ped, int attributes, bool p2)l
extern _native void SET_PED_COWER_HASH(Ped ped, const char* p1)l
extern _native void UNK_0xA6F2C057(any p0, bool p1)l
extern _native void SET_PED_STEERS_AROUND_PEDS(Ped ped, bool toggle)l
extern _native void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, bool toggle)l
extern _native void SET_PED_STEERS_AROUND_VEHICLES(Ped ped, bool toggle)l
extern _native void UNK_0x2276DE0D(any p0, bool p1)l
extern _native void UNK_0x59C52BE6(any p0)l
extern _native void UNK_0x1D87DDC1(any p0, bool p1)l
extern _native void UNK_0xB52BA5F5(any p0)l
extern _native bool IS_ANY_PED_NEAR_POINT(vector3 vec, float radius)l
extern _native void UNK_0x187B9070(Ped ped, bool p1, bool p2)l
extern _native bool UNK_0x45037B9B(any p0, float p1, float p2, float p3, float p4)l
extern _native void UNK_0x840D24D3(any p0)l
extern _native void GET_PED_FLOOD_INVINCIBILITY(Ped ped, bool p1)l
extern _native void UNK_0x9194DB71(Ped ped, bool p1)l
extern _native bool IS_TRACKED_PED_VISIBLE(Ped ped)l
extern _native any UNK_0x5B1B70AA(any p0)l
extern _native bool IS_PED_TRACKED(Ped ped)l
extern _native bool HAS_PED_RECEIVED_EVENT(any p0, any p1)l
extern _native bool UNK_0x74A0F291(any p0, any p1)l
extern _native int GET_PED_BONE_INDEX(Ped ped, int boneId)l
extern _native int GET_PED_RAGDOLL_BONE_INDEX(Ped ped, int bone)l
extern _native void SET_PED_ENVEFF_SCALE(Ped ped, float value)l
extern _native float GET_PED_ENVEFF_SCALE(Ped ped)l
extern _native void SET_ENABLE_PED_ENVEFF_SCALE(Ped ped, bool toggle)l
extern _native void UNK_0x3B882533(Ped ped, float p1)l
extern _native void UNK_0x87A0C174(Ped ped, int p1, int p2, int p3)l
extern _native void UNK_0x7BD26837(any p0, any p1)l
extern _native void UNK_0x98E29ED0(any p0, bool p1)l
extern _native int CREATE_SYNCHRONIZED_SCENE(vector3 vec, float roll, float pitch, float yaw, int p6)l
extern _native int UNK_0xF3876894(vector3 vec, float radius, Hash object)l
extern _native bool IS_SYNCHRONIZED_SCENE_RUNNING(int sceneId)l
extern _native void SET_SYNCHRONIZED_SCENE_ORIGIN(int sceneID, vector3 vec, float roll, float pitch, float yaw, bool p7)l
extern _native void SET_SYNCHRONIZED_SCENE_PHASE(int sceneID, float phase)l
extern _native float GET_SYNCHRONIZED_SCENE_PHASE(int sceneID)l
extern _native void SET_SYNCHRONIZED_SCENE_RATE(int sceneID, float rate)l
extern _native float GET_SYNCHRONIZED_SCENE_RATE(int sceneID)l
extern _native void SET_SYNCHRONIZED_SCENE_LOOPED(int sceneID, bool toggle)l
extern _native bool IS_SYNCHRONIZED_SCENE_LOOPED(int sceneID)l
extern _native32(0x2DE48DA1) void _SET_SYNCHRONIZED_SCENE_OCCLUSION_PORTAL(any sceneID, bool p1)l
extern _native bool UNK_0x72CF2514(any p0)l
extern _native void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(int sceneID, Entity entity, int boneIndex)l
extern _native void DETACH_SYNCHRONIZED_SCENE(int sceneID)l
extern _native32(0xBF7F9035) void _DISPOSE_SYNCHRONIZED_SCENE(int scene)l
extern _native bool FORCE_PED_MOTION_STATE(Ped ped, Hash motionStateHash, bool p2, bool p3, bool p4)l
extern _native void SET_PED_MAX_MOVE_BLEND_RATIO(Ped ped, float value)l
extern _native void SET_PED_MIN_MOVE_BLEND_RATIO(Ped ped, float value)l
extern _native void SET_PED_MOVE_RATE_OVERRIDE(Ped ped, float value)l
extern _native bool UNK_0x79543043(Ped ped, int flag)l
extern _native int GET_PED_NEARBY_VEHICLES(Ped ped, int* sizeAndVehs)l
extern _native int GET_PED_NEARBY_PEDS(Ped ped, int* sizeAndPeds, int ignore)l
extern _native bool UNK_0xF9FB4B71(Ped ped)l
extern _native bool IS_PED_USING_ACTION_MODE(Ped ped)l
extern _native void SET_PED_USING_ACTION_MODE(Ped ped, bool p1, any p2, const char* action)l
extern _native void SET_PED_CAPSULE(Ped ped, float value)l
extern _native any REGISTER_PEDHEADSHOT(Ped ped)l
extern _native any UNK_0x4DD03628(any p0)l
extern _native void UNREGISTER_PEDHEADSHOT(Ped ped)l
extern _native int IS_PEDHEADSHOT_VALID(int handle)l
extern _native bool IS_PEDHEADSHOT_READY(int handle)l
extern _native const char* GET_PEDHEADSHOT_TXD_STRING(int handle)l
extern _native bool UNK_0x10F2C023(any p0)l
extern _native void UNK_0x0DBB2FA7(any p0)l
extern _native any UNK_0x810158F8()l
extern _native any UNK_0x05023F8F()l
extern _native any UNK_0xAA39FD6C()l
extern _native void UNK_0xEF9142DB(any p0, any p1)l
extern _native void UNK_0x0688DE64(any p0)l
extern _native void UNK_0x909A1D76(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration)l
extern _native void UNK_0x4AAD0ECB(vector3 vec, float p3, float p4, float p5, float p6, int interiorFlags, float scale, int duration)l
extern _native void UNK_0x492C9E46()l
extern _native any UNK_0x814A28F4()l
extern _native any UNK_0x0B60D2BA()l
extern _native any UNK_0x6B83ABDF()l
extern _native any UNK_0xF46B4DC8()l
extern _native void UNK_0x36A4AC65(any p0, any* p1, any* p2, any* p3)l
extern _native void UNK_0xBA699DDF(any p0, any* p1)l
extern _native void SET_IK_TARGET(Ped ped, int p1, Ped targetPed, int boneLookAt, vector3 vec, any p7, int duration, int duration1)l
extern _native void UNK_0xFB4000DC(any p0)l
extern _native void REQUEST_ACTION_MODE_ASSET(const char* asset)l
extern _native bool HAS_ACTION_MODE_ASSET_LOADED(const char* asset)l
extern _native void REMOVE_ACTION_MODE_ASSET(const char* asset)l
extern _native void REQUEST_STEALTH_MODE_ASSET(const char* asset)l
extern _native bool HAS_STEALTH_MODE_ASSET_LOADED(const char* asset)l
extern _native void REMOVE_STEALTH_MODE_ASSET(const char* asset)l
extern _native void SET_PED_LOD_MULTIPLIER(Ped ped, float multiplier)l
extern _native void UNK_0x2F9550C2(any p0, bool p1, any p2)l
extern _native void UNK_0x37DBC2AD(Ped ped, bool toggle)l
extern _native void UNK_0xC0F1BC91(any p0, bool p1, any p2, any p3)l
extern _native bool UNK_0x1A464167(Ped ped, vector3 vec, float range)l
extern _native bool UNK_0xD0567D41(any p0, any p1, float p2, float p3, float p4, float p5)l
extern _native void UNK_0x4BBE5E2C(any p0, any p1, any p2, any p3, any p4)l
extern _native void UNK_0xA89A53F2(Ped ped)l
#pragma endregion //}
#pragma region VEHICLE //{
extern _native Vehicle CREATE_VEHICLE(Hash modelHash, vector3 vec, float heading, bool isNetwork, bool p6)l
extern _native void DELETE_VEHICLE(Vehicle* vehicle)l
extern _native void UNK_0xBB54ECCA(Vehicle vehicle, bool p1, bool p2)l
extern _native void SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(Vehicle veh, bool toggle)l
extern _native int UNK_0xFBDE9FD8(Vehicle vehicle)l
extern _native bool IS_VEHICLE_MODEL(Vehicle vehicle, Hash model)l
extern _native bool DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(int vehicleGenerator)l
extern _native int CREATE_SCRIPT_VEHICLE_GENERATOR(vector3 vec, float heading, float p4, float p5, Hash modelHash, int p7, int p8, int p9, int p10, bool p11, bool p12, bool p13, bool p14, bool p15, int p16)l
extern _native void DELETE_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator)l
extern _native void SET_SCRIPT_VEHICLE_GENERATOR(any vehicleGenerator, bool enabled)l
extern _native void SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(vector3 vec_1, vector3 vec_2, bool p6, bool p7)l
extern _native void SET_ALL_VEHICLE_GENERATORS_ACTIVE()l
extern _native void SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(bool active)l
extern _native void UNK_0x935A95DA(float p0, float p1, float p2, float p3)l
extern _native void UNK_0x6C73E45A()l
extern _native any SET_ALL_VEHICLES_SPAWN(Vehicle p0, bool p1, bool p2, bool p3)l
extern _native bool IS_VEHICLE_STUCK_ON_ROOF(Vehicle vehicle)l
extern _native void ADD_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)l
extern _native void REMOVE_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)l
extern _native bool IS_VEHICLE_STOPPED(Vehicle vehicle)l
extern _native int GET_VEHICLE_NUMBER_OF_PASSENGERS(Vehicle vehicle)l
extern _native int GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vehicle vehicle)l
extern _native int GET_VEHICLE_MODEL_NUMBER_OF_SEATS(Hash modelHash)l
extern _native bool UNK_0x769E5CF2(Vehicle vehicle, bool flag)l
extern _native void SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native void SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native void SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)l
extern _native void UNK_0x09462665(bool toggle)l
extern _native32(0xDAE2A2BE) void _SET_SOME_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float value)l
extern _native void SET_FAR_DRAW_VEHICLES(bool toggle)l
extern _native any SET_NUMBER_OF_PARKED_VEHICLES(int value)l
extern _native void SET_VEHICLE_DOORS_LOCKED(Vehicle vehicle, int doorLockStatus)l
extern _native void SET_PED_TARGETTABLE_VEHICLE_DESTROY(Vehicle vehicle, int vehicleComponent, int destroyType)l
extern _native void DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player, bool toggle)l
extern _native bool GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player)l
extern _native void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(Vehicle vehicle, bool toggle)l
extern _native void UNK_0xE4EF6514(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(Vehicle vehicle, int team, bool toggle)l
extern _native void EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible)l
extern _native void SET_VEHICLE_OUT_OF_CONTROL(Vehicle vehicle, bool killDriver, bool explodeOnImpact)l
extern _native void SET_VEHICLE_TIMED_EXPLOSION(Vehicle vehicle, Ped ped, bool toggle)l
extern _native void UNK_0x811373DE(Vehicle vehicle)l
extern _native any UNK_0xA4E69134()l
extern _native void UNK_0x65255524()l
extern _native bool UNK_0xE39DAF36(Vehicle vehicle)l
extern _native void SET_TAXI_LIGHTS(Vehicle vehicle, bool state)l
extern _native bool IS_TAXI_LIGHT_ON(Vehicle vehicle)l
extern _native bool IS_VEHICLE_IN_GARAGE_AREA(const char* garageName, Vehicle vehicle)l
extern _native void SET_VEHICLE_COLOURS(Vehicle vehicle, int colorPrimary, int colorSecondary)l
extern _native void SET_VEHICLE_FULLBEAM(Vehicle vehicle, bool toggle)l
extern _native void STEER_UNLOCK_BIAS(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, RGB colour)l
extern _native void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native any CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle)l
extern _native bool GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Vehicle vehicle)l
extern _native void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, RGB colour)l
extern _native void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native any CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle)l
extern _native bool GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Vehicle vehicle)l
extern _native void SET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle, float fade)l
extern _native float GET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle)l
extern _native void SET_CAN_RESPRAY_VEHICLE(Vehicle vehicle, bool state)l
extern _native void UNK_0x54E9EE75(Vehicle vehicle, bool p1)l
extern _native32(0x4A46E814) void _JITTER_VEHICLE(Vehicle vehicle, bool p1, float yaw, float pitch, float roll)l
extern _native void SET_BOAT_ANCHOR(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x0ED84792(Vehicle vehicle, bool p1)l
extern _native void UNK_0xA739012A(Vehicle vehicle, bool p1)l
extern _native void UNK_0x66FA450C(Vehicle vehicle, float p1)l
extern _native void UNK_0x35614622(Vehicle vehicle, bool p1)l
extern _native void SET_VEHICLE_SIREN(Vehicle vehicle, bool toggle)l
extern _native bool IS_VEHICLE_SIREN_ON(Vehicle vehicle)l
extern _native void SET_VEHICLE_STRONG(Vehicle vehicle, bool toggle)l
extern _native void REMOVE_VEHICLE_STUCK_CHECK(Vehicle vehicle)l
extern _native void GET_VEHICLE_COLOURS(Vehicle vehicle, int* colorPrimary, int* colorSecondary)l
extern _native bool IS_VEHICLE_SEAT_FREE(Vehicle vehicle, int seatIndex)l
extern _native Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int index)l
extern _native Ped GET_LAST_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex)l
extern _native bool GET_VEHICLE_LIGHTS_STATE(Vehicle vehicle, bool* lightsOn, bool* highbeamsOn)l
extern _native bool IS_VEHICLE_TYRE_BURST(Vehicle vehicle, int wheelID, bool completely)l
extern _native void SET_VEHICLE_FORWARD_SPEED(Vehicle vehicle, float speed)l
extern _native32(0xCBC7D3C8) void _SET_VEHICLE_HALT(Vehicle vehicle, float distance, int killEngine, bool unknown)l
extern _native void UNK_0x943A6CFC(Vehicle vehicle, float p1)l
extern _native bool SET_PED_ENABLED_BIKE_RINGTONE(Vehicle vehicle, Entity entity)l
extern _native bool UNK_0x593143B9(Vehicle vehicle)l
extern _native32(0x70DD5E25) Vehicle _GET_VEHICLE_ATTACHED_TO_ENTITY(Object object)l
extern _native bool UNK_0xFBF5536A(Vehicle vehicle, Entity entity)l
extern _native void UNK_0x20AB5783(Vehicle vehicle, Entity entity)l
extern _native void UNK_0x0F11D01F(Vehicle vehicle)l
extern _native void UNK_0xAE040377(Vehicle vehicle, bool p1)l
extern _native void UNK_0x4C0E4031(Vehicle vehicle, bool p1)l
extern _native bool UNK_0x6346B7CC(Vehicle vehicle)l
extern _native void UNK_0xCCB41A55(Vehicle vehicle, float p1)l
extern _native void SET_VEHICLE_TYRE_BURST(Vehicle vehicle, int index, bool onRim, float p3)l
extern _native void SET_VEHICLE_DOORS_SHUT(Vehicle vehicle, bool closeInstantly)l
extern _native void SET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle, bool toggle)l
extern _native bool GET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle)l
extern _native any SET_VEHICLE_WHEELS_CAN_BREAK(Vehicle vehicle, bool enabled)l
extern _native void SET_VEHICLE_DOOR_OPEN(Vehicle vehicle, int doorIndex, bool loose, bool openInstantly)l
extern _native void REMOVE_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native void ROLL_DOWN_WINDOWS(Vehicle vehicle)l
extern _native any ROLL_DOWN_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native any ROLL_UP_WINDOW(Vehicle vehicle, int windowIndex)l
extern _native any SMASH_VEHICLE_WINDOW(Vehicle vehicle, int index)l
extern _native any FIX_VEHICLE_WINDOW(Vehicle vehicle, int index)l
extern _native32(0xCC95C96B) void _DETACH_VEHICLE_WINDSCREEN(Vehicle vehicle)l
extern _native32(0xFDA7B6CA) void _EJECT_JB700_ROOF(Vehicle vehicle, vector3 vec)l
extern _native void SET_VEHICLE_LIGHTS(Vehicle vehicle, int state)l
extern _native void UNK_0x4221E435(Vehicle vehicle, bool p1)l
extern _native void SET_VEHICLE_ALARM(Vehicle vehicle, bool state)l
extern _native any START_VEHICLE_ALARM(Vehicle vehicle)l
extern _native bool IS_VEHICLE_ALARM_ACTIVATED(Vehicle vehicle)l
extern _native void SET_VEHICLE_INTERIORLIGHT(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_LIGHT_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native void ATTACH_VEHICLE_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float radius)l
extern _native void UNK_0x12AC1A16(Vehicle vehicle, Vehicle trailer, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11)l
extern _native void UNK_0x40C4763F(Vehicle vehicle, Entity p1, float p2)l
extern _native void DETACH_VEHICLE_FROM_TRAILER(Vehicle vehicle)l
extern _native bool IS_VEHICLE_ATTACHED_TO_TRAILER(Vehicle vehicle)l
extern _native void UNK_0xE74E85CE(Vehicle vehicle, float p1)l
extern _native void UNK_0x06C47A6F(Vehicle vehicle)l
extern _native void SET_VEHICLE_TYRE_FIXED(Vehicle vehicle, int tyreIndex)l
extern _native void SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle, const char* plateText)l
extern _native const char* GET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle)l
extern _native int GET_NUMBER_OF_VEHICLE_NUMBER_PLATES()l
extern _native void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle, int plateIndex)l
extern _native int GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle)l
extern _native void SET_RANDOM_TRAINS(bool toggle)l
extern _native Vehicle CREATE_MISSION_TRAIN(int variation, vector3 vec, bool direction)l
extern _native any SWITCH_TRAIN_TRACK(int intersectionId, bool state)l
extern _native void UNK_0xD5774FB7(any p0, any p1)l
extern _native void DELETE_ALL_TRAINS()l
extern _native any SET_TRAIN_SPEED(Vehicle train, float speed)l
extern _native any SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed)l
extern _native any SET_RANDOM_BOATS(bool toggle)l
extern _native any SET_GARBAGE_TRUCKS(bool toggle)l
extern _native bool DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(Vehicle vehicle)l
extern _native any GET_VEHICLE_RECORDING_ID(int p0, const char* p1)l
extern _native void REQUEST_VEHICLE_RECORDING(any p0, any* p1)l
extern _native bool HAS_VEHICLE_RECORDING_BEEN_LOADED(any p0, any* p1)l
extern _native void REMOVE_VEHICLE_RECORDING(any p0, any* p1)l
extern _native int UNK_0xF31973BB(any p0, float p1)l
extern _native vector3 GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(int p0, float p1, const char* p2)l
extern _native vector3 UNK_0x4D1C15C2(any p0, float p1)l
extern _native int GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(any p0, float p1, any* p2)l
extern _native float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(any p0)l
extern _native any GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(any p0, any p1)l
extern _native float GET_POSITION_IN_RECORDING(any p0)l
extern _native float GET_TIME_POSITION_IN_RECORDING(any p0)l
extern _native void START_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, int p1, const char* playback, bool p3)l
extern _native void START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(Vehicle vehicle, any p1, const char* playback, any p3, any p4, any p5)l
extern _native void UNK_0x01B91CD0(any p0, bool p1)l
extern _native void STOP_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native void PAUSE_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native void UNPAUSE_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native bool IS_PLAYBACK_GOING_ON_FOR_VEHICLE(any p0)l
extern _native bool IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(any p0)l
extern _native any GET_CURRENT_PLAYBACK_FOR_VEHICLE(any p0)l
extern _native void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(any p0)l
extern _native any SET_PLAYBACK_SPEED(any p0, float speed)l
extern _native void START_PLAYBACK_RECORDED_VEHICLE_USING_AI(any p0, any p1, any* p2, float p3, any p4)l
extern _native void SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(any p0, float p1)l
extern _native void SET_PLAYBACK_TO_USE_AI(Vehicle vehicle, int flag)l
extern _native void SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(any p0, any p1, any p2, bool p3)l
extern _native void UNK_0x943A58EB(Vehicle vehicle, vector3 vec, any p4)l
extern _native void UNK_0x5C9F477C(any p0, float p1, float p2, float p3)l
extern _native void UNK_0xCD83C393(any p0, float p1, float p2, float p3)l
extern _native void UNK_0x2EF8435C(any p0, bool p1)l
extern _native void EXPLODE_VEHICLE_IN_CUTSCENE(Vehicle vehicle, bool p1)l
extern _native void ADD_VEHICLE_STUCK_CHECK_WITH_WARP(any p0, float p1, any p2, bool p3, bool p4, bool p5, any p6)l
extern _native void SET_VEHICLE_MODEL_IS_SUPPRESSED(Hash model, bool suppressed)l
extern _native Vehicle GET_RANDOM_VEHICLE_IN_SPHERE(vector3 vec, float radius, Hash modelHash, int flags)l
extern _native Vehicle GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native Vehicle GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native Vehicle GET_CLOSEST_VEHICLE(vector3 vec, float radius, Hash modelHash, int flags)l
extern _native Entity GET_TRAIN_CARRIAGE(Vehicle train, int trailerNumber)l
extern _native void DELETE_MISSION_TRAIN(Vehicle* train)l
extern _native void SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Vehicle* train, bool p1)l
extern _native void SET_MISSION_TRAIN_COORDS(Vehicle train, vector3 vec)l
extern _native bool IS_THIS_MODEL_A_BOAT(Hash model)l
extern _native bool IS_THIS_MODEL_A_PLANE(Hash model)l
extern _native bool IS_THIS_MODEL_A_HELI(Hash model)l
extern _native bool IS_THIS_MODEL_A_CAR(Hash model)l
extern _native bool IS_THIS_MODEL_A_TRAIN(Hash model)l
extern _native bool IS_THIS_MODEL_A_BIKE(Hash model)l
extern _native bool IS_THIS_MODEL_A_BICYCLE(Hash model)l
extern _native bool IS_THIS_MODEL_A_QUADBIKE(Hash model)l
extern _native void SET_HELI_BLADES_FULL_SPEED(Vehicle vehicle)l
extern _native void SET_HELI_BLADES_SPEED(Vehicle vehicle, float speed)l
extern _native void UNK_0x1128A45B(Vehicle vehicle, float p1, float p2)l
extern _native void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle vehicle, bool state)l
extern _native void UNK_0x486C1280(Vehicle vehicle, bool p1)l
extern _native void SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, bool state)l
extern _native void UNK_0x009AB49E(Vehicle vehicle, bool p1)l
extern _native void UNK_0x758C5E2E(Vehicle vehicle, bool p1)l
extern _native float GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle)l
extern _native void SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float dirtLevel)l
extern _native32(0xDAC523BC) bool _IS_VEHICLE_DAMAGED(Vehicle vehicle)l
extern _native bool IS_VEHICLE_DOOR_FULLY_OPEN(Vehicle vehicle, int doorIndex)l
extern _native void SET_VEHICLE_ENGINE_ON(Vehicle vehicle, bool value, bool instantly, bool otherwise)l
extern _native void SET_VEHICLE_UNDRIVEABLE(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_PROVIDES_COVER(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_DOOR_CONTROL(Vehicle vehicle, int doorIndex, int speed, float angle)l
extern _native void SET_VEHICLE_DOOR_LATCHED(Vehicle vehicle, int doorIndex, bool p2, bool p3, bool p4)l
extern _native float GET_VEHICLE_DOOR_ANGLE_RATIO(Vehicle vehicle, int door)l
extern _native void SET_VEHICLE_DOOR_SHUT(Vehicle vehicle, int doorIndex, bool closeInstantly)l
extern _native void SET_VEHICLE_DOOR_BROKEN(Vehicle vehicle, int doorIndex, bool deleteDoor)l
extern _native void SET_VEHICLE_CAN_BREAK(Vehicle vehicle, bool toggle)l
extern _native bool DOES_VEHICLE_HAVE_ROOF(Vehicle vehicle)l
extern _native bool IS_BIG_VEHICLE(Vehicle vehicle)l
extern _native int GET_NUMBER_OF_VEHICLE_COLOURS(Vehicle vehicle)l
extern _native void SET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle, int colorCombination)l
extern _native int GET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle)l
extern _native void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle vehicle, bool toggle)l
extern _native void UNK_0xA6D8D7A5(Vehicle vehicle, bool toggle)l
extern _native void UNK_0xACAB8FF3(Vehicle vehicle, bool p1)l
extern _native void UNK_0xF0E5C41D(Vehicle vehicle, bool p1)l
extern _native void UNK_0x2F98B4B7(Vehicle vehicle, bool p1)l
extern _native void GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(bool p0, Hash* modelHash, int* p2)l
extern _native int GET_VEHICLE_DOOR_LOCK_STATUS(Vehicle vehicle)l
extern _native bool IS_VEHICLE_DOOR_DAMAGED(Vehicle veh, int doorID)l
extern _native32(0x065B92B3) void _SET_VEHICLE_DOOR_CAN_BREAK(Vehicle vehicle, int doorIndex, bool isBreakable)l
extern _native bool UNK_0xB3A2CC4F(Vehicle vehicle, bool p1)l
extern _native bool IS_VEHICLE_BUMPER_BROKEN_OFF(Vehicle vehicle, bool front)l
extern _native bool IS_COP_VEHICLE_IN_AREA_3D(float x1, float x2, float y1, float y2, float z1, float z2)l
extern _native bool IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle)l
extern _native Hash GET_VEHICLE_LAYOUT_HASH(Vehicle vehicle)l
extern _native void SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, bool toggle)l
extern _native void SET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int pearlescentColor, int wheelColor)l
extern _native void GET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int* pearlescentColor, int* wheelColor)l
extern _native void STOP_ALL_GARAGE_ACTIVITY()l
extern _native void SET_VEHICLE_FIXED(Vehicle vehicle)l
extern _native void SET_VEHICLE_DEFORMATION_FIXED(Vehicle vehicle)l
extern _native void UNK_0x88F0F7E7(Vehicle vehicle, bool p1)l
extern _native void UNK_0x90D6EE57(Vehicle vehicle, bool p1)l
extern _native void SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(Vehicle vehicle, bool toggle)l
extern _native void SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x1784BA1A(Vehicle vehicle, bool p1)l
extern _native void UNK_0x40C323AE(Vehicle vehicle, bool p1)l
extern _native void UNK_0x847F1304(Vehicle vehicle, bool p1)l
extern _native void UNK_0xCBD98BA1(Vehicle vehicle, bool p1)l
extern _native void REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(vector3 vec_1, vector3 vec_2, any unk)l
extern _native void SET_VEHICLE_STEER_BIAS(Vehicle vehicle, float value)l
extern _native bool IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, int extraId)l
extern _native void SET_VEHICLE_EXTRA(Vehicle vehicle, int extraId, bool toggle)l
extern _native bool DOES_EXTRA_EXIST(Vehicle vehicle, int extraId)l
extern _native void SET_CONVERTIBLE_ROOF(Vehicle vehicle, bool p1)l
extern _native void LOWER_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyLower)l
extern _native void RAISE_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyRaise)l
extern _native int GET_CONVERTIBLE_ROOF_STATE(Vehicle vehicle)l
extern _native bool IS_VEHICLE_A_CONVERTIBLE(Vehicle vehicle, bool p1)l
extern _native bool IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle)l
extern _native void SET_VEHICLE_DAMAGE(Vehicle vehicle, vector3 Offset, float damage, float radius, bool p6)l
extern _native float GET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle)l
extern _native void SET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle, float health)l
extern _native float GET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle)l
extern _native void SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle, float health)l
extern _native bool IS_VEHICLE_STUCK_TIMER_UP(Vehicle vehicle, int p1, int p2)l
extern _native void RESET_VEHICLE_STUCK_TIMER(Vehicle vehicle, bool nullAttributes)l
extern _native bool IS_VEHICLE_DRIVEABLE(Vehicle vehicle, bool p1)l
extern _native void SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Vehicle vehicle, bool owned)l
extern _native void SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(Vehicle vehicle, bool toggle)l
extern _native void START_VEHICLE_HORN(Vehicle vehicle, int duration, Hash mode, bool forever)l
extern _native32(0x968E5770) void _SET_VEHICLE_SILENT(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_HAS_STRONG_AXLES(Vehicle vehicle, bool toggle)l
extern _native const char* GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Hash modelHash)l
extern _native vector3 GET_VEHICLE_DEFORMATION_AT_POS(Vehicle vehicle, vector3 offset)l
extern _native void SET_VEHICLE_LIVERY(Vehicle vehicle, int livery)l
extern _native int GET_VEHICLE_LIVERY(Vehicle vehicle)l
extern _native int GET_VEHICLE_LIVERY_COUNT(Vehicle vehicle)l
extern _native bool IS_VEHICLE_WINDOW_INTACT(Vehicle vehicle, int windowIndex)l
extern _native bool ARE_ALL_VEHICLE_WINDOWS_INTACT(Vehicle vehicle)l
extern _native bool ARE_ANY_VEHICLE_SEATS_FREE(Vehicle vehicle)l
extern _native void RESET_VEHICLE_WHEELS(Vehicle vehicle, bool toggle)l
extern _native bool IS_HELI_PART_BROKEN(Vehicle vehicle, bool p1, bool p2, bool p3)l
extern _native32(0xF01E2AAB) float _GET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle)l
extern _native32(0xA41BC13D) float _GET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle)l
extern _native32(0x8A68388F) float _GET_HELI_ENGINE_HEALTH(Vehicle vehicle)l
extern _native bool WAS_COUNTER_ACTIVATED(Vehicle vehicle, any p1)l
extern _native void SET_VEHICLE_NAME_DEBUG(Vehicle vehicle, const char* name)l
extern _native void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle vehicle, bool toggle)l
extern _native void UNK_0xC306A9A3(Vehicle vehicle, bool p1)l
extern _native any UNK_0x95A9ACCB(Vehicle vehicle, bool p1)l
extern _native void CONTROL_LANDING_GEAR(Vehicle vehicle, int state)l
extern _native int GET_LANDING_GEAR_STATE(Vehicle vehicle)l
extern _native bool IS_ANY_VEHICLE_NEAR_POINT(vector3 vec, float radius)l
extern _native void REQUEST_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)l
extern _native void REMOVE_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)l
extern _native bool IS_VEHICLE_HIGH_DETAIL(Vehicle vehicle)l
extern _native void REQUEST_VEHICLE_ASSET(Hash vehicleHash, int vehicleAsset)l
extern _native bool HAS_VEHICLE_ASSET_LOADED(int vehicleAsset)l
extern _native void REMOVE_VEHICLE_ASSET(int vehicleAsset)l
extern _native32(0x88236E22) void _SET_TOW_TRUCK_CRANE_HEIGHT(Vehicle towTruck, float height)l
extern _native void ATTACH_VEHICLE_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle, bool rear, vector3 hookOffset)l
extern _native void DETACH_VEHICLE_FROM_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)l
extern _native bool DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(Vehicle vehicle)l
extern _native bool IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)l
extern _native Entity GET_ENTITY_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck)l
extern _native any SET_VEHICLE_AUTOMATICALLY_ATTACHES(Vehicle vehicle, any p1, any p2)l
extern _native void UNK_0xED23C8A3(any p0, float p1, bool p2)l
extern _native void UNK_0xB1A52EF7(any p0, float p1, bool p2)l
extern _native void UNK_0xF30C566F(any p0, float p1)l
extern _native void UNK_0xA7DF64D7(any p0, float p1)l
extern _native void UNK_0xDD7936F5(any p0, float p1)l
extern _native bool UNK_0x34E02FCD(vector3* outVec, any p1, vector3* outVec1, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native void SET_VEHICLE_BURNOUT(Vehicle vehicle, bool toggle)l
extern _native bool IS_VEHICLE_IN_BURNOUT(Vehicle vehicle)l
extern _native void SET_VEHICLE_REDUCE_GRIP(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_INDICATOR_LIGHTS(Vehicle vehicle, int turnSignal, bool toggle)l
extern _native void SET_VEHICLE_BRAKE_LIGHTS(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_HANDBRAKE(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x37BC6ACB()l
extern _native bool UNK_0x71D898EF()l
extern _native void UNK_0x0B0523B0(bool p0)l
extern _native bool GET_VEHICLE_TRAILER_VEHICLE(Vehicle vehicle, Vehicle* trailer)l
extern _native void UNK_0x0B200CE2(Vehicle vehicle, bool p1)l
extern _native void SET_VEHICLE_RUDDER_BROKEN(Vehicle vehicle, bool p1)l
extern _native void UNK_0x0858678C(Vehicle vehicle, bool p1)l
extern _native float UNK_0x7D1A0616(Vehicle vehicle)l
extern _native float GET_VEHICLE_MAX_BRAKING(Vehicle vehicle)l
extern _native float GET_VEHICLE_MAX_TRACTION(Vehicle vehicle)l
extern _native float GET_VEHICLE_ACCELERATION(Vehicle vehicle)l
extern _native32(0x8F291C4A) float _GET_VEHICLE_MODEL_MAX_SPEED(Hash modelHash)l
extern _native float GET_VEHICLE_MODEL_MAX_BRAKING(Hash modelHash)l
extern _native float UNK_0xF3A7293F(Hash modelHash)l
extern _native float GET_VEHICLE_MODEL_MAX_TRACTION(Hash modelHash)l
extern _native float GET_VEHICLE_MODEL_ACCELERATION(Hash modelHash)l
extern _native float UNK_0x37FBA7BC(Hash modelHash)l
extern _native float UNK_0x95BB67EB(Hash modelHash)l
extern _native float UNK_0x87C5D271(Hash modelHash)l
extern _native float UNK_0xCE67162C(int vehicleClass)l
extern _native float GET_VEHICLE_CLASS_MAX_TRACTION(int vehicleClass)l
extern _native float GET_VEHICLE_CLASS_MAX_AGILITY(int vehicleClass)l
extern _native float GET_VEHICLE_CLASS_MAX_ACCELERATION(int vehicleClass)l
extern _native float GET_VEHICLE_CLASS_MAX_BRAKING(int vehicleClass)l
extern _native any UNK_0xD6685803(float p0, float p1, float p2, float p3, float p4, bool p5)l
extern _native bool UNK_0x0C0332A6(any p0)l
extern _native void OPEN_BOMB_BAY_DOORS(Vehicle vehicle)l
extern _native void CLOSE_BOMB_BAY_DOORS(Vehicle vehicle)l
extern _native bool IS_VEHICLE_SEARCHLIGHT_ON(Vehicle vehicle)l
extern _native void SET_VEHICLE_SEARCHLIGHT(Vehicle heli, bool toggle, bool canBeUsedByAI)l
extern _native bool UNK_0xAB0E79EB(Ped ped, Vehicle vehicle, bool p2, bool p3, bool p4)l
extern _native bool CAN_SHUFFLE_SEAT(Vehicle vehicle, any p1)l
extern _native int GET_NUM_MOD_KITS(Vehicle vehicle)l
extern _native void SET_VEHICLE_MOD_KIT(Vehicle vehicle, int modKit)l
extern _native int GET_VEHICLE_MOD_KIT(Vehicle vehicle)l
extern _native int GET_VEHICLE_MOD_KIT_TYPE(Vehicle vehicle)l
extern _native int GET_VEHICLE_WHEEL_TYPE(Vehicle vehicle)l
extern _native void SET_VEHICLE_WHEEL_TYPE(Vehicle vehicle, int WheelType)l
extern _native int GET_NUM_MOD_COLORS(int p0, bool p1)l
extern _native void SET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int paintType, int color, int p3)l
extern _native void SET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int paintType, int color)l
extern _native void GET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int* paintType, int* color, int* p3)l
extern _native void GET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int* paintType, int* color)l
extern _native const char* GET_VEHICLE_MOD_COLOR_1_NAME(Vehicle vehicle, bool p1)l
extern _native const char* GET_VEHICLE_MOD_COLOR_2_NAME(Vehicle vehicle)l
extern _native bool UNK_0x112D637A(Vehicle vehicle)l
extern _native void SET_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex, bool customTires)l
extern _native int GET_VEHICLE_MOD(Vehicle vehicle, int modType)l
extern _native bool GET_VEHICLE_MOD_VARIATION(Vehicle vehicle, int modType)l
extern _native int GET_NUM_VEHICLE_MODS(Vehicle vehicle, int modType)l
extern _native void REMOVE_VEHICLE_MOD(Vehicle vehicle, int modType)l
extern _native void TOGGLE_VEHICLE_MOD(Vehicle vehicle, int modType, bool toggle)l
extern _native bool IS_TOGGLE_MOD_ON(Vehicle vehicle, int modType)l
extern _native const char* GET_MOD_TEXT_LABEL(Vehicle vehicle, int modType, int modValue)l
extern _native const char* GET_MOD_SLOT_NAME(Vehicle vehicle, int modType)l
extern _native const char* GET_LIVERY_NAME(Vehicle vehicle, int liveryIndex)l
extern _native any GET_VEHICLE_MOD_MODIFIER_VALUE(Vehicle vehicle, int modType, int modIndex)l
extern _native32(0x94850968) any _GET_VEHICLE_MOD_DATA(Vehicle vehicle, int modType, int modIndex)l
extern _native void PRELOAD_VEHICLE_MOD(any p0, any p1, any p2)l
extern _native bool HAS_PRELOAD_MODS_FINISHED(any p0)l
extern _native void RELEASE_PRELOAD_MODS(Vehicle vehicle)l
extern _native void SET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, RGB colour)l
extern _native void GET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native void SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int tint)l
extern _native int GET_VEHICLE_WINDOW_TINT(Vehicle vehicle)l
extern _native int GET_NUM_VEHICLE_WINDOW_TINTS()l
extern _native void GET_VEHICLE_COLOR(Vehicle vehicle, int* r, int* g, int* b)l
extern _native int UNK_0x749DEEA2(Vehicle vehicle)l
extern _native Hash GET_VEHICLE_CAUSE_OF_DESTRUCTION(Vehicle vehicle)l
extern _native bool GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)l
extern _native bool GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)l
extern _native32(0xE943B09C) void _SET_VEHICLE_ENGINE_POWER_MULTIPLIER(Vehicle vehicle, float value)l
extern _native void UNK_0xDF594D8D(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x4D840FC4(Vehicle vehicle, bool p1)l
extern _native any UNK_0x5AB26C2B(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native void UNK_0xEF05F807(any p0)l
extern _native32(0xD656E7E5) bool _ANY_PASSENGERS_RAPPELING(Vehicle vehicle)l
extern _native32(0x642DA5AA) void _SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(Vehicle vehicle, float value)l
extern _native void UNK_0x04F5546C(any p0, bool p1)l
extern _native void SET_VEHICLE_IS_WANTED(Vehicle vehicle, bool state)l
extern _native void UNK_0xA25CCB8C(any p0, float p1)l
extern _native void UNK_0x00966934(any p0, bool p1)l
extern _native void UNK_0x113DF5FD(any p0, bool p1)l
extern _native float UNK_0x7C8D6464(Vehicle vehicle)l
extern _native void DISABLE_PLANE_AILERON(Vehicle vehicle, bool p1, bool p2)l
extern _native bool GET_IS_VEHICLE_ENGINE_RUNNING(Vehicle vehicle)l
extern _native void UNK_0xA03E42DF(Vehicle vehicle, bool p1)l
extern _native32(0x15D40761) void _SET_BIKE_LEAN_ANGLE(Vehicle vehicle, vector2 vector)l
extern _native void UNK_0x1984F88D(Vehicle vehicle, bool p1)l
extern _native void UNK_0x3FBE904F(Vehicle vehicle)l
extern _native void SET_LAST_DRIVEN_VEHICLE(Vehicle vehicle)l
extern _native Vehicle GET_LAST_DRIVEN_VEHICLE()l
extern _native void UNK_0x08CD58F9(any p0, bool p1)l
extern _native32(0x8C4B63E2) void _SET_PLANE_MIN_HEIGHT_ABOVE_GROUND(Vehicle plane, int height)l
extern _native void SET_VEHICLE_LOD_MULTIPLIER(Vehicle vehicle, float multiplier)l
extern _native void UNK_0x1604C2F5(Vehicle vehicle, bool p1)l
extern _native any UNK_0x8CDB0C09(any p0)l
extern _native any UNK_0xABC99E21(any p0)l
extern _native void UNK_0x900C878C(any p0, bool p1)l
extern _native void UNK_0xB3200F72(any p0, bool p1)l
extern _native void UNK_0xBAE491C7(Vehicle vehicle, Vehicle vehicle2)l
extern _native void UNK_0xF0E59BC1()l
extern _native void UNK_0x929801C6(float p0)l
extern _native void SET_VEHICLE_SHOOT_AT_TARGET(Ped driver, Entity entity, vector3 Target)l
extern _native32(0x4A557117) bool _GET_VEHICLE_OWNER(Vehicle vehicle, Entity* entity)l
extern _native void SET_FORCE_HD_VEHICLE(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x7D0DE7EA(Vehicle vehicle, float p1)l
extern _native int GET_VEHICLE_PLATE_TYPE(Vehicle vehicle)l
extern _native void TRACK_VEHICLE_VISIBILITY(Vehicle vehicle)l
extern _native bool IS_VEHICLE_VISIBLE(Vehicle vehicle)l
extern _native void SET_VEHICLE_GRAVITY(Vehicle vehicle, bool toggle)l
extern _native void UNK_0xD2B8ACBD(bool p0)l
extern _native any UNK_0xA4A75FCF(any p0)l
extern _native void UNK_0x50F89338(any p0, bool p1)l
extern _native void UNK_0xEB7D7C27(any p0, bool p1)l
extern _native32(0x5EB00A6A) bool _IS_VEHICLE_SHOP_RESPRAY_ALLOWED(Vehicle vehicle)l
extern _native void SET_VEHICLE_ENGINE_CAN_DEGRADE(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x5BD8D82D(Vehicle vehicle, int p1, int p2)l
extern _native void UNK_0x450AD03A(any p0)l
extern _native32(0xBD085DCA) bool _VEHICLE_HAS_LANDING_GEAR(Vehicle vehicle)l
extern _native32(0xABBDD5C6) bool _ARE_PROPELLERS_UNDAMAGED(Vehicle vehicle)l
extern _native void UNK_0x9B581DE7(Vehicle vehicle, bool p1)l
extern _native bool IS_VEHICLE_STOLEN(Vehicle vehicle)l
extern _native any SET_VEHICLE_IS_STOLEN(Vehicle vehicle, bool isStolen)l
extern _native void UNK_0xED159AE6(Vehicle vehicle, float p1)l
extern _native bool ADD_A_MARKER_OVER_VEHICLE(Vehicle vehicle)l
extern _native void UNK_0x45F72495(Vehicle vehicle)l
extern _native void DETACH_VEHICLE_FROM_CARGOBOB(Vehicle vehicle, Vehicle cargobob)l
extern _native bool DETACH_VEHICLE_FROM_ANY_CARGOBOB(Vehicle vehicle)l
extern _native bool IS_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicleAttached)l
extern _native Vehicle GET_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob)l
extern _native void ATTACH_VEHICLE_TO_CARGOBOB(Vehicle vehicle, Vehicle cargobob, int p2, vector3 vec)l
extern _native bool DOES_CARGOBOB_HAVE_PICK_UP_ROPE(Vehicle cargobob)l
extern _native void CREATE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob, int state)l
extern _native void REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob)l
extern _native32(0x3A8AB081) void _SET_CARGOBOB_HOOK_POSITION(any p0, float p1, float p2, int state)l
extern _native bool DOES_CARGOBOB_HAVE_PICKUP_MAGNET(Vehicle cargobob)l
extern _native void SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(Vehicle cargobob, bool isActive)l
extern _native void SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(Vehicle cargobob, float strength)l
extern _native bool DOES_VEHICLE_HAVE_WEAPONS(Vehicle vehicle)l
extern _native void UNK_0x2EC19A8B(any p0, bool p1)l
extern _native void DISABLE_VEHICLE_WEAPON(bool disabled, Hash weaponHash, Vehicle vehicle, Ped owner)l
extern _native void UNK_0x123E5B90(any p0, bool p1)l
extern _native void UNK_0xEBC225C1(any p0, bool p1)l
extern _native int GET_VEHICLE_CLASS(Vehicle vehicle)l
extern _native int GET_VEHICLE_CLASS_FROM_NAME(Hash modelHash)l
extern _native any SET_PLAYERS_LAST_VEHICLE(Vehicle vehicle)l
extern _native void SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(Vehicle vehicle, bool toggle)l
extern _native void UNK_0xB6BE07E0(Vehicle vehicle, float p1)l
extern _native32(0x4BB5605D) void _SET_VEHICLE_CREATES_MONEY_PICKUPS_WHEN_EXPLODED(Vehicle vehicle, bool toggle)l
extern _native32(0x51E0064F) void _SET_VEHICLE_JET_ENGINE_ON(Vehicle vehicle, bool toggle)l
extern _native void UNK_0xAEF9611C(any p0, any p1)l
extern _native void UNK_0x585E49B6(any p0, float p1)l
extern _native32(0x6E67FD35) void _SET_HELICOPTER_ROLL_PITCH_YAW_MULT(Vehicle helicopter, float multiplier)l
extern _native void SET_VEHICLE_FRICTION_OVERRIDE(Vehicle vehicle, float friction)l
extern _native void SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(Vehicle vehicle, bool toggle)l
extern _native void SET_VEHICLE_CEILING_HEIGHT(Vehicle vehicle, float p1)l
extern _native void UNK_0xBC649C49(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x8DD9AA0C(Vehicle vehicle)l
extern _native bool DOES_VEHICLE_EXIST_WITH_DECORATOR(const char* decorator)l
extern _native void SET_VEHICLE_EXCLUSIVE_DRIVER(Vehicle vehicle, bool p1)l
extern _native32(0xB5CC548B) void _DISPLAY_DISTANT_VEHICLES(bool toggle)l
extern _native float GET_VEHICLE_BODY_HEALTH(Vehicle vehicle)l
extern _native void SET_VEHICLE_BODY_HEALTH(Vehicle vehicle, float value)l
extern _native32(0xB73A1486) float _GET_VEHICLE_SUSPENSION_HEIGHT(Vehicle vehicle)l
#pragma endregion //}
#pragma region OBJECT //{
extern _native Object CREATE_OBJECT(Object modelHash, vector3 vec, bool isNetwork, bool p5, bool dynamic)l
extern _native Object CREATE_OBJECT_NO_OFFSET(Hash modelHash, vector3 vec, bool isNetwork, bool p5, bool dynamic)l
extern _native void DELETE_OBJECT(Object* object)l
extern _native bool PLACE_OBJECT_ON_GROUND_PROPERLY(Object object)l
extern _native bool SLIDE_OBJECT(Object object, vector3 to, vector3 speed, bool collision)l
extern _native any SET_OBJECT_TARGETTABLE(Object object, bool targettable)l
extern _native void UNK_0x483C5C88(Object object, bool p1)l
extern _native Object GET_CLOSEST_OBJECT_OF_TYPE(vector3 vec, float radius, Hash modelHash, bool isMission, bool p6, bool p7)l
extern _native bool HAS_OBJECT_BEEN_BROKEN(Object object)l
extern _native bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(float p0, float p1, float p2, float p3, Hash modelHash, any p5)l
extern _native bool UNK_0x7DB578DD(float p0, float p1, float p2, float p3, Hash modelHash, bool p5)l
extern _native32(0x87A42A12) vector3 _GET_OBJECT_OFFSET_FROM_COORDS(vector3 Pos, float heading, vector3 Offset)l
extern _native any UNK_0x65213FC3(any coords, float radius, Hash modelHash, vector3 vec, vector3* p6, int p7)l
extern _native void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, vector3 vec, bool locked, float heading, bool p6)l
extern _native void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, vector3 vec, bool* locked, float* heading)l
extern _native32(0x4E0A260B) void _DOOR_CONTROL(Hash doorHash, vector3 vec, bool locked, float p5, float p6, float p7)l
extern _native void ADD_DOOR_TO_SYSTEM(Hash doorHash, Hash modelHash, vector3 vec, bool p5, bool p6, bool p7)l
extern _native void REMOVE_DOOR_FROM_SYSTEM(Hash doorHash)l
extern _native32(0xDF83DB47) void _SET_DOOR_ACCELERATION_LIMIT(Hash doorHash, int limit, bool p2, bool p3)l
extern _native int UNK_0xD42A41C2(Hash doorHash)l
extern _native int UNK_0xD649B7E1(Hash doorHash)l
extern _native void UNK_0x4F44AF21(Hash doorHash, float p1, bool p2, bool p3)l
extern _native void UNK_0x47531446(Hash doorHash, float heading, bool p2, bool p3)l
extern _native32(0x34883DE3) void _SET_DOOR_AJAR_ANGLE(Hash doorHash, float ajar, bool p2, bool p3)l
extern _native float UNK_0xB74C3BD7(Hash doorHash)l
extern _native void UNK_0xB4A9A558(Hash doorHash, bool p1, bool p2, bool p3)l
extern _native void UNK_0xECE58AE0(Hash doorHash, bool p1)l
extern _native void UNK_0xF736227C(Hash doorHash, bool p1)l
extern _native32(0x5AFCD8A1) bool _DOES_DOOR_EXIST(Hash doorHash)l
extern _native bool IS_DOOR_CLOSED(Hash door)l
extern _native void UNK_0x9BF33E41(bool p0)l
extern _native void UNK_0xF592AD10()l
extern _native bool UNK_0x17FF9393(any p0)l
extern _native bool UNK_0xE9AE494F(float p0, float p1, float p2, any p3, any* p4)l
extern _native bool IS_GARAGE_EMPTY(any garage, bool p1, int p2)l
extern _native bool UNK_0xC33ED360(any p0, Player player, float p2, int p3)l
extern _native bool UNK_0x41924877(any p0, Player player, int p2)l
extern _native bool UNK_0x4BD59750(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native bool UNK_0x7B44D659(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native bool UNK_0x142C8F76(any p0, Entity entity, float p2, int p3)l
extern _native bool UNK_0x95A9AB2B(any p0, Entity entity, int p2)l
extern _native void UNK_0xA565E27E(any p0, bool p1, bool p2, bool p3, bool p4)l
extern _native void UNK_0x43BB7E48(Hash hash, bool toggle)l
extern _native void UNK_0x6158959E()l
extern _native bool DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(vector3 vec, float radius, Hash hash, bool p5)l
extern _native bool IS_POINT_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, bool p10, bool p11)l
extern _native void UNK_0x19B17769(Object object, bool toggle)l
extern _native void SET_OBJECT_PHYSICS_PARAMS(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy)l
extern _native float GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(any p0, bool p1)l
extern _native void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Object object, bool toggle)l
extern _native bool IS_ANY_OBJECT_NEAR_POINT(vector3 vec, float range, bool p4)l
extern _native bool IS_OBJECT_NEAR_POINT(Hash objectHash, vector3 vec, float range)l
extern _native void UNK_0xE3261B35(any p0)l
extern _native void UNK_0x1E82C2AE(Object p0, any p1, bool p2)l
extern _native void TRACK_OBJECT_VISIBILITY(any p0)l
extern _native bool IS_OBJECT_VISIBLE(Object object)l
extern _native void UNK_0xF4A1A14A(any p0, bool p1)l
extern _native void UNK_0xAF016CC1(any p0, bool p1)l
extern _native void UNK_0x3A68AA46(any p0, bool p1)l
extern _native32(0xA286DE96) int _GET_DES_OBJECT(vector3 vec, float rotation, const char* name)l
extern _native32(0x21F51560) void _SET_DES_OBJECT_STATE(int handle, int state)l
extern _native32(0xF1B8817A) any _GET_DES_OBJECT_STATE(int handle)l
extern _native32(0xE08C834D) bool _DOES_DES_OBJECT_EXIST(int handle)l
extern _native float UNK_0x020497DE(any p0)l
extern _native Pickup CREATE_PICKUP(Hash pickupHash, vector3 pos, int p4, int value, bool p6, Hash modelHash)l
extern _native Pickup CREATE_PICKUP_ROTATE(Hash pickupHash, vector3 pos, vector3 rot, int flag, int amount, any p9, bool p10, Hash modelHash)l
extern _native Pickup CREATE_AMBIENT_PICKUP(Hash pickupHash, vector3 pos, int p4, int value, Hash modelHash, bool p7, bool p8)l
extern _native Pickup CREATE_PORTABLE_PICKUP(Hash pickupHash, vector3 vec, bool placeOnGround, Hash modelHash)l
extern _native32(0x56A02502) Pickup _CREATE_PORTABLE_PICKUP_2(Hash pickupHash, vector3 vec, bool placeOnGround, Hash modelHash)l
extern _native void ATTACH_PORTABLE_PICKUP_TO_PED(Ped ped, any p1)l
extern _native void DETACH_PORTABLE_PICKUP_FROM_PED(Ped ped)l
extern _native void UNK_0x7EFBA039(any p0, int p1)l
extern _native void UNK_0xA3CDF152(bool p0)l
extern _native vector3 GET_SAFE_PICKUP_COORDS(vector3 vec, any p3, any p4)l
extern _native vector3 GET_PICKUP_COORDS(Pickup pickup)l
extern _native void REMOVE_ALL_PICKUPS_OF_TYPE(Hash pickupHash)l
extern _native bool HAS_PICKUP_BEEN_COLLECTED(Pickup pickup)l
extern _native void REMOVE_PICKUP(Pickup pickup)l
extern _native void CREATE_MONEY_PICKUPS(vector3 vec, int value, int amount, Hash model)l
extern _native bool DOES_PICKUP_EXIST(Pickup pickup)l
extern _native bool DOES_PICKUP_OBJECT_EXIST(Object pickupObject)l
extern _native Object GET_PICKUP_OBJECT(Pickup pickup)l
extern _native32(0xF139681B) bool _IS_PICKUP_WITHIN_RADIUS(Hash pickupHash, vector3 vec, float radius)l
extern _native void SET_PICKUP_REGENERATION_TIME(any p0, any p1)l
extern _native void UNK_0x7FADB4B9(Player player, Hash pickupHash, bool p2)l
extern _native void UNK_0x3A8F1BF7(Hash p0, bool p1)l
extern _native void SET_TEAM_PICKUP_OBJECT(Object object, any p1, bool p2)l
extern _native void UNK_0xCBB5F9B6(Object object, bool p1, bool p2)l
extern _native void UNK_0x276A7807(any p0, float p1, bool p2)l
extern _native any UNK_0x000E92DC(any p0)l
extern _native void UNK_0x9879AC51(float p0)l
extern _native void UNK_0xDB18FA01(bool p0)l
extern _native void UNK_0xA7E936FD(any p0, any p1)l
extern _native void UNK_0xB241806C()l
extern _native void UNK_0xD1BAAFB7(any p0)l
extern _native32(0x63B02FAD) void _HIGHLIGHT_PLACEMENT_COORDS(vector3 vec, int colorIndex)l
extern _native void UNK_0x132B6D92(Object object, bool toggle)l
extern _native32(0xEDD01937) Hash _GET_WEAPON_HASH_FROM_PICKUP(Pickup pickupHash)l
extern _native Hash UNK_0x6AE36192(Pickup pickupHash)l
extern _native void SET_FORCE_OBJECT_THIS_FRAME(any p0, any p1, any p2, any p3)l
extern _native32(0x2048A7DD) void _MARK_OBJECT_FOR_DELETION(Object object)l
#pragma endregion //}
#pragma region AI //{
extern _native void TASK_PAUSE(Ped ped, int ms)l
extern _native void TASK_STAND_STILL(Ped ped, int time)l
extern _native void TASK_JUMP(Ped ped, bool unused)l
extern _native void TASK_COWER(Ped ped, int duration)l
extern _native void TASK_HANDS_UP(Ped ped, int duration, Ped facingPed, int p3, bool p4)l
extern _native void UPDATE_TASK_HANDS_UP_DURATION(Ped ped, int duration)l
extern _native void TASK_OPEN_VEHICLE_DOOR(Ped ped, Vehicle vehicle, int timeOut, int doorIndex, float speed)l
extern _native void TASK_ENTER_VEHICLE(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int p5, any p6)l
extern _native void TASK_LEAVE_VEHICLE(Ped ped, Vehicle vehicle, int flags)l
extern _native void TASK_SKY_DIVE(Ped ped)l
extern _native void TASK_PARACHUTE(Ped ped, bool p1)l
extern _native void TASK_PARACHUTE_TO_TARGET(Ped ped, vector3 vec)l
extern _native void SET_PARACHUTE_TASK_TARGET(Ped ped, vector3 vec)l
extern _native void SET_PARACHUTE_TASK_THRUST(Ped ped, float thrust)l
extern _native void TASK_RAPPEL_FROM_HELI(Ped ped, int unused)l
extern _native void TASK_VEHICLE_DRIVE_TO_COORD(Ped ped, Vehicle vehicle, vector3 vec, float speed, any p6, Hash vehicleModel, int drivingMode, float stopRange, float p10)l
extern _native void TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Ped ped, Vehicle vehicle, vector3 vec, float speed, int driveMode, float stopRange)l
extern _native void TASK_VEHICLE_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, int drivingStyle)l
extern _native void TASK_FOLLOW_TO_OFFSET_OF_ENTITY(Ped ped, Entity entity, vector3 offset, float movementSpeed, int timeout, float stoppingRange, bool persistFollowing)l
extern _native void TASK_GO_STRAIGHT_TO_COORD(Ped ped, vector3 vec, float speed, int timeout, float targetHeading, float distanceToSlide)l
extern _native void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(Entity entity1, Entity entity2, float p2, float p3, float p4, float p5, any p6)l
extern _native void TASK_ACHIEVE_HEADING(Ped ped, float heading, int timeout)l
extern _native void TASK_FLUSH_ROUTE()l
extern _native void TASK_EXTEND_ROUTE(vector3 vec)l
extern _native void TASK_FOLLOW_POINT_ROUTE(Ped ped, float speed, int unknown)l
extern _native void TASK_GO_TO_ENTITY(Entity entity, Entity target, int duration, float distance, float speed, float p5, int p6)l
extern _native void TASK_SMART_FLEE_COORD(Ped ped, vector3 vec, float distance, int time, bool p6, bool p7)l
extern _native void TASK_SMART_FLEE_PED(Ped ped, Ped fleeTarget, float distance, any fleeTime, bool p4, bool p5)l
extern _native void TASK_REACT_AND_FLEE_PED(Ped ped, Ped fleeTarget)l
extern _native void TASK_SHOCKING_EVENT_REACT(Ped ped, int eventHandle)l
extern _native void TASK_WANDER_IN_AREA(Ped ped, vector3 vec, float radius, float minimalLength, float timeBetweenWalks)l
extern _native void TASK_WANDER_STANDARD(Ped ped, float p1, int p2)l
extern _native void TASK_VEHICLE_PARK(Ped ped, Vehicle vehicle, vector3 vec, float heading, int mode, float radius, bool keepEngineOn)l
extern _native any TASK_STEALTH_KILL(Ped killer, Ped target, Hash killType, float p3, bool p4)l
extern _native void TASK_PLANT_BOMB(Ped ped, vector3 vec, float heading)l
extern _native void TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, vector3 vec, float speed, int timeout, float stoppingRange, bool persistFollowing, float unk)l
extern _native void TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(Ped ped, vector3 vec, float speed, int timeout, float unkFloat, int unkInt, vector3 unk, float unk_40000f)l
extern _native any SET_PED_PATH_CAN_USE_CLIMBOVERS(Ped ped, bool Toggle)l
extern _native any SET_PED_PATH_CAN_USE_LADDERS(Ped ped, bool Toggle)l
extern _native void SET_PED_PATH_CAN_DROP_FROM_HEIGHT(Ped ped, bool Toggle)l
extern _native void UNK_0x55E06443(Ped ped, float p1)l
extern _native void SET_PED_PATHS_WIDTH_PLANT(Ped ped, bool mayEnterWater)l
extern _native void SET_PED_PATH_PREFER_TO_AVOID_WATER(Ped ped, bool avoidWater)l
extern _native void SET_PED_PATH_AVOID_FIRE(Ped ped, bool avoidFire)l
extern _native void SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(float height)l
extern _native any GET_NAVMESH_ROUTE_DISTANCE_REMAINING(Ped ped, any* p1, any* p2)l
extern _native int GET_NAVMESH_ROUTE_RESULT(Ped ped)l
extern _native void TASK_GO_TO_COORD_ANY_MEANS(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8)l
extern _native void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8, any p9, any p10, any p11)l
extern _native void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8, any p9, any p10, any p11, any p12)l
extern _native void TASK_PLAY_ANIM(Ped ped, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, bool lockX, bool lockY, bool lockZ)l
extern _native void TASK_PLAY_ANIM_ADVANCED(Ped ped, const char* animDict, const char* animName, vector3 pos, vector3 rot, float speed, float speedMultiplier, int duration, any flag, float animTime, any p14, any p15)l
extern _native void STOP_ANIM_TASK(Ped ped, const char* animDictionary, const char* animationName, float p3)l
extern _native void TASK_SCRIPTED_ANIMATION(Ped ped, any* p1, any* p2, any* p3, float p4, float p5)l
extern _native void PLAY_ENTITY_SCRIPTED_ANIM(any p0, any* p1, any* p2, any* p3, float p4, float p5)l
extern _native void STOP_ANIM_PLAYBACK(Ped ped, any p1, bool p2)l
extern _native void SET_ANIM_WEIGHT(any p0, float p1, any p2, any p3, bool p4)l
extern _native void SET_ANIM_RATE(any p0, float p1, any p2, bool p3)l
extern _native void SET_ANIM_LOOPED(any p0, bool p1, any p2, bool p3)l
extern _native void TASK_PLAY_PHONE_GESTURE_ANIMATION(Ped ped, const char* animDict, const char* animation, const char* boneMaskType, float p4, float p5, bool p6, bool p7)l
extern _native bool IS_PLAYING_PHONE_GESTURE_ANIM(Ped ped)l
extern _native float GET_PHONE_GESTURE_ANIM_CURRENT_TIME(Ped ped)l
extern _native float GET_PHONE_GESTURE_ANIM_TOTAL_TIME(Ped ped)l
extern _native void TASK_VEHICLE_PLAY_ANIM(Vehicle vehicle, const char* animation_set, const char* animation_name)l
extern _native void TASK_LOOK_AT_COORD(Entity entity, vector3 vec, float duration, any p5, any p6)l
extern _native void TASK_LOOK_AT_ENTITY(Ped ped, Entity lookAt, int duration, int unknown1, int unknown2)l
extern _native void TASK_CLEAR_LOOK_AT(Ped ped)l
extern _native any OPEN_SEQUENCE_TASK(Object* taskSequence)l
extern _native any CLOSE_SEQUENCE_TASK(Object taskSequence)l
extern _native any TASK_PERFORM_SEQUENCE(Ped ped, Object taskSequence)l
extern _native any CLEAR_SEQUENCE_TASK(Object* taskSequence)l
extern _native void SET_SEQUENCE_TO_REPEAT(Object taskSequence, bool repeat)l
extern _native int GET_SEQUENCE_PROGRESS(Ped ped)l
extern _native bool GET_IS_TASK_ACTIVE(Ped ped, int taskNumber)l
extern _native int GET_SCRIPT_TASK_STATUS(Ped targetPed, Hash taskHash)l
extern _native int GET_ACTIVE_VEHICLE_MISSION_TYPE(Vehicle veh)l
extern _native void TASK_LEAVE_ANY_VEHICLE(Ped ped, int p1, int p2)l
extern _native void TASK_AIM_GUN_SCRIPTED(Ped ped, Hash scriptTask, bool p2, bool p3)l
extern _native void TASK_AIM_GUN_SCRIPTED_WITH_TARGET(any p0, any p1, float p2, float p3, float p4, any p5, bool p6, bool p7)l
extern _native void UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(Ped p0, Ped p1, float p2, float p3, float p4, bool p5)l
extern _native const char* GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(int p0)l
extern _native void TASK_AIM_GUN_AT_ENTITY(Ped ped, Entity entity, int duration, bool p3)l
extern _native void TASK_TURN_PED_TO_FACE_ENTITY(Ped ped, Entity entity, int duration)l
extern _native void TASK_AIM_GUN_AT_COORD(Ped ped, vector3 vec, int time, bool p5, bool p6)l
extern _native void TASK_SHOOT_AT_COORD(Ped ped, vector3 vec, int duration, Hash firingPattern)l
extern _native void TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(Ped ped, Vehicle vehicle)l
extern _native void CLEAR_PED_TASKS(Ped ped)l
extern _native void CLEAR_PED_SECONDARY_TASK(Ped ped)l
extern _native void TASK_EVERYONE_LEAVE_VEHICLE(Vehicle vehicle)l
extern _native void TASK_GOTO_ENTITY_OFFSET(Ped ped, any p1, any p2, vector3 vec, int duration)l
extern _native void TASK_GOTO_ENTITY_OFFSET_XY(any p0, any p1, any p2, float p3, float p4, float p5, float p6, any p7)l
extern _native void TASK_TURN_PED_TO_FACE_COORD(Ped ped, vector3 vec, int duration)l
extern _native void TASK_VEHICLE_TEMP_ACTION(Ped driver, Vehicle vehicle, int action, int time)l
extern _native void TASK_VEHICLE_MISSION(any p0, any p1, any p2, any p3, float p4, any p5, float p6, float p7, bool p8)l
extern _native void TASK_VEHICLE_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped pedTarget, int mode, float maxSpeed, int drivingStyle, float minDistance, float p7, bool p8)l
extern _native void TASK_VEHICLE_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, vector3 vec, int p5, int p6, int p7, float p8, float p9, bool p10)l
extern _native void TASK_VEHICLE_ESCORT(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int p7, float noRoadsDistance)l
extern _native void TASK_VEHICLE_CHASE(Ped driver, Entity targetEnt)l
extern _native void TASK_VEHICLE_HELI_PROTECT(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int p4, float radius, int altitude, int p7)l
extern _native void SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(Ped ped, int flag, bool set)l
extern _native void SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(Ped ped, float distance)l
extern _native void TASK_HELI_CHASE(Ped pilot, Entity entityToFollow, vector3 vec)l
extern _native void TASK_PLANE_CHASE(Ped pilot, Entity entityToFollow, vector3 vec)l
extern _native void TASK_PLANE_LAND(Ped pilot, Vehicle plane, vector3 runwayStart, vector3 runwayEnd)l
extern _native void TASK_HELI_MISSION(Ped pilot, Vehicle vehicle, Vehicle vehicleToFollow, Ped pedToFollow, vector3 pos, int mode, float speed, float radius, float angle, int p11, int height, float p13, int p14)l
extern _native void TASK_PLANE_MISSION(Ped pilot, Vehicle plane, Vehicle targetVehicle, Ped targetPed, vector3 destination, int missionType, float vehicleSpeed, float p9, float heading, float maxAltitude, float minAltitude)l
extern _native void TASK_BOAT_MISSION(Ped pedDriver, Vehicle boat, any p2, any p3, vector3 vec, any p7, float maxSpeed, int drivingStyle, float p10, any p11)l
extern _native void TASK_DRIVE_BY(Ped driverPed, Ped targetPed, Vehicle targetVehicle, vector3 target, float distanceToShoot, int pedAccuracy, bool p8, Hash firingPattern)l
extern _native void SET_DRIVEBY_TASK_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, vector3 vec)l
extern _native void CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native bool IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native bool CONTROL_MOUNTED_WEAPON(Ped ped)l
extern _native void SET_MOUNTED_WEAPON_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, vector3 vec)l
extern _native bool IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(Ped ped)l
extern _native void TASK_USE_MOBILE_PHONE(Ped ped, int p1)l
extern _native void TASK_USE_MOBILE_PHONE_TIMED(Ped ped, int duration)l
extern _native void TASK_CHAT_TO_PED(Ped ped, Ped target, any p2, float p3, float p4, float p5, float p6, float p7)l
extern _native void TASK_WARP_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seat)l
extern _native void TASK_SHOOT_AT_ENTITY(Entity entity, Entity target, int duration, Hash firingPattern)l
extern _native void TASK_CLIMB(Ped ped, bool unused)l
extern _native void TASK_CLIMB_LADDER(Ped ped, int p1)l
extern _native void CLEAR_PED_TASKS_IMMEDIATELY(Ped ped)l
extern _native void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(any p0, any p1, any p2, any p3)l
extern _native void SET_NEXT_DESIRED_MOVE_STATE(float p0)l
extern _native void SET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped, float p1)l
extern _native float GET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped)l
extern _native void TASK_GOTO_ENTITY_AIMING(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist)l
extern _native void TASK_SET_DECISION_MAKER(Ped p0, Hash p1)l
extern _native void TASK_SET_SPHERE_DEFENSIVE_AREA(any p0, float p1, float p2, float p3, float p4)l
extern _native void TASK_CLEAR_DEFENSIVE_AREA(any p0)l
extern _native void TASK_PED_SLIDE_TO_COORD(Ped ped, vector3 vec, float heading, float p5)l
extern _native void TASK_PED_SLIDE_TO_COORD_HDG_RATE(Ped ped, vector3 vec, float heading, float p5, float p6)l
extern _native ScrHandle ADD_COVER_POINT(float p0, float p1, float p2, float p3, any p4, any p5, any p6, bool p7)l
extern _native void REMOVE_COVER_POINT(ScrHandle coverpoint)l
extern _native bool DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(vector3 vec)l
extern _native vector3 GET_SCRIPTED_COVER_POINT_COORDS(ScrHandle coverpoint)l
extern _native void TASK_COMBAT_PED(Ped ped, Ped targetPed, int p2, int p3)l
extern _native void TASK_COMBAT_PED_TIMED(any p0, Ped ped, int p2, any p3)l
extern _native void TASK_SEEK_COVER_FROM_POS(Ped ped, vector3 vec, int duration, bool p5)l
extern _native void TASK_SEEK_COVER_FROM_PED(Ped ped, Ped target, int duration, bool p3)l
extern _native void TASK_SEEK_COVER_TO_COVER_POINT(any p0, any p1, float p2, float p3, float p4, any p5, bool p6)l
extern _native void TASK_SEEK_COVER_TO_COORDS(Ped ped, vector3 vec_1, vector3 vec_2, any p7, bool p8)l
extern _native void TASK_PUT_PED_DIRECTLY_INTO_COVER(Ped ped, vector3 vec, any timeout, bool p5, float p6, bool p7, bool p8, any p9, bool p10)l
extern _native void TASK_EXIT_COVER(any p0, any p1, float p2, float p3, float p4)l
extern _native void TASK_PUT_PED_DIRECTLY_INTO_MELEE(Ped ped, Ped meleeTarget, float p2, float p3, float p4, bool p5)l
extern _native void TASK_TOGGLE_DUCK(bool p0, bool p1)l
extern _native void TASK_GUARD_CURRENT_POSITION(Ped p0, float p1, float p2, bool p3)l
extern _native void TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(any p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native void TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped p0, float p1, float p2, float p3, float p4, float p5, any p6, float p7, float p8, float p9, float p10)l
extern _native void TASK_STAND_GUARD(Ped ped, vector3 vec, float heading, const char* scenarioName)l
extern _native void SET_DRIVE_TASK_CRUISE_SPEED(Ped driver, float cruiseSpeed)l
extern _native void SET_DRIVE_TASK_MAX_CRUISE_SPEED(any p0, float p1)l
extern _native void SET_DRIVE_TASK_DRIVING_STYLE(Ped ped, int drivingStyle)l
extern _native void ADD_COVER_BLOCKING_AREA(vector3 player, vector3 radius, bool p6, bool p7, bool p8, bool p9)l
extern _native void REMOVE_ALL_COVER_BLOCKING_AREAS()l
extern _native void TASK_START_SCENARIO_IN_PLACE(Ped ped, const char* scenarioName, int unkDelay, bool playEnterAnim)l
extern _native void TASK_START_SCENARIO_AT_POSITION(Ped ped, const char* scenarioName, vector3 vec, float heading, int duration, bool sittingScenario, bool teleport)l
extern _native void TASK_USE_NEAREST_SCENARIO_TO_COORD(Ped ped, vector3 vec, float distance, int duration)l
extern _native void TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(Ped ped, vector3 vec, float radius, any p5)l
extern _native void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(any p0, float p1, float p2, float p3, float p4, any p5)l
extern _native void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(any p0, float p1, float p2, float p3, float p4, any p5)l
extern _native bool DOES_SCENARIO_EXIST_IN_AREA(vector3 vec, float radius, bool b)l
extern _native bool DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(float p0, float p1, float p2, any* p3, float p4, bool p5)l
extern _native bool IS_SCENARIO_OCCUPIED(float p0, float p1, float p2, float p3, bool p4)l
extern _native bool PED_HAS_USE_SCENARIO_TASK(Ped ped)l
extern _native void PLAY_ANIM_ON_RUNNING_SCENARIO(Ped ped, const char* animDict, const char* animName)l
extern _native bool DOES_SCENARIO_GROUP_EXIST(const char* scenarioGroup)l
extern _native bool IS_SCENARIO_GROUP_ENABLED(const char* scenarioGroup)l
extern _native void SET_SCENARIO_GROUP_ENABLED(const char* scenarioGroup, bool p1)l
extern _native void RESET_SCENARIO_GROUPS_ENABLED()l
extern _native void SET_EXCLUSIVE_SCENARIO_GROUP(const char* scenarioGroup)l
extern _native void RESET_EXCLUSIVE_SCENARIO_GROUP()l
extern _native bool IS_SCENARIO_TYPE_ENABLED(const char* scenarioType)l
extern _native void SET_SCENARIO_TYPE_ENABLED(const char* scenarioType, bool toggle)l
extern _native void RESET_SCENARIO_TYPES_ENABLED()l
extern _native bool IS_PED_ACTIVE_IN_SCENARIO(Ped ped)l
extern _native void TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, vector3 vec, float radius, any p5)l
extern _native void TASK_COMBAT_HATED_TARGETS_AROUND_PED(Ped ped, float radius, int p2)l
extern _native void TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(any p0, float p1, any p2, any p3)l
extern _native void TASK_THROW_PROJECTILE(int ped, vector3 vec)l
extern _native void TASK_SWAP_WEAPON(Ped ped, bool p1)l
extern _native void TASK_RELOAD_WEAPON(Ped ped, bool unused)l
extern _native bool IS_PED_GETTING_UP(Ped ped)l
extern _native void TASK_WRITHE(Ped ped, Ped target, int time, int p3)l
extern _native bool IS_PED_IN_WRITHE(Ped ped)l
extern _native void OPEN_PATROL_ROUTE(const char* patrolRoute)l
extern _native void CLOSE_PATROL_ROUTE()l
extern _native void ADD_PATROL_ROUTE_NODE(int p0, const char* p1, vector3 vec_1, vector3 vec_2, int p8)l
extern _native void ADD_PATROL_ROUTE_LINK(any p0, any p1)l
extern _native void CREATE_PATROL_ROUTE()l
extern _native void DELETE_PATROL_ROUTE(const char* patrolRoute)l
extern _native void TASK_PATROL(Ped ped, const char* p1, any p2, bool p3, bool p4)l
extern _native void TASK_STAY_IN_COVER(Ped ped)l
extern _native void ADD_VEHICLE_SUBTASK_ATTACK_COORD(Ped ped, vector3 vec)l
extern _native void ADD_VEHICLE_SUBTASK_ATTACK_PED(Ped ped, Ped ped2)l
extern _native void TASK_VEHICLE_SHOOT_AT_PED(Ped ped, Ped target, float p2)l
extern _native void TASK_VEHICLE_AIM_AT_PED(Ped ped, Ped target)l
extern _native void TASK_VEHICLE_SHOOT_AT_COORD(Ped ped, vector3 vec, float p4)l
extern _native void TASK_VEHICLE_AIM_AT_COORD(Ped ped, vector3 vec)l
extern _native void TASK_VEHICLE_GOTO_NAVMESH(Ped ped, Vehicle vehicle, vector3 vec, float speed, int behaviorFlag, float stoppingRange)l
extern _native void TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Ped ped, vector3 vec, vector3 aimAt, float moveSpeed, bool p8, float p9, float p10, bool p11, any flags, bool p13, Hash firingPattern)l
extern _native void TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(any p0, float p1, float p2, float p3, any p4, float p5, bool p6, float p7, float p8, bool p9, any p10, bool p11, any p12, any p13)l
extern _native void TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(Ped pedHandle, vector3 goToLocation, vector3 focusLocation, float speed, bool shootAtEnemies, float distanceToStopAt, float noRoadsDistance, bool unkTrue, int unkFlag, int aimingFlag, Hash firingPattern)l
extern _native void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(any p0, any p1, float p2, float p3, float p4, float p5, bool p6, float p7, float p8, bool p9, bool p10, any p11)l
extern _native void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, bool shootatEntity, float p5, float p6, bool p7, bool p8, Hash firingPattern)l
extern _native void SET_HIGH_FALL_TASK(Ped ped, any p1, any p2, any p3)l
extern _native void REQUEST_WAYPOINT_RECORDING(const char* name)l
extern _native bool GET_IS_WAYPOINT_RECORDING_LOADED(const char* name)l
extern _native void REMOVE_WAYPOINT_RECORDING(const char* name)l
extern _native bool WAYPOINT_RECORDING_GET_NUM_POINTS(const char* name, int* points)l
extern _native bool WAYPOINT_RECORDING_GET_COORD(const char* name, int point, vector3* coord)l
extern _native float WAYPOINT_RECORDING_GET_SPEED_AT_POINT(const char* name, int point)l
extern _native bool WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(const char* name, vector3 vec, int* point)l
extern _native void TASK_FOLLOW_WAYPOINT_RECORDING(any p0, any p1, any p2, any p3, any p4)l
extern _native bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(any p0)l
extern _native any GET_PED_WAYPOINT_PROGRESS(any p0)l
extern _native float GET_PED_WAYPOINT_DISTANCE(any p0)l
extern _native any SET_PED_WAYPOINT_ROUTE_OFFSET(any p0, any p1, any p2, any p3)l
extern _native float GET_WAYPOINT_DISTANCE_ALONG_ROUTE(const char* p0, int p1)l
extern _native bool WAYPOINT_PLAYBACK_GET_IS_PAUSED(any p0)l
extern _native void WAYPOINT_PLAYBACK_PAUSE(any p0, bool p1, bool p2)l
extern _native void WAYPOINT_PLAYBACK_RESUME(any p0, bool p1, any p2, any p3)l
extern _native void WAYPOINT_PLAYBACK_OVERRIDE_SPEED(any p0, float p1, bool p2)l
extern _native void WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(any p0)l
extern _native void USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(any* p0, bool p1, float p2, float p3)l
extern _native void WAYPOINT_PLAYBACK_START_AIMING_AT_PED(any p0, any p1, bool p2)l
extern _native void WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(any p0, float p1, float p2, float p3, bool p4)l
extern _native void WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(any p0, float p1, float p2, float p3, bool p4, any p5)l
extern _native void WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(any p0)l
extern _native void ASSISTED_MOVEMENT_REQUEST_ROUTE(const char* route)l
extern _native void ASSISTED_MOVEMENT_REMOVE_ROUTE(const char* route)l
extern _native bool ASSISTED_MOVEMENT_IS_ROUTE_LOADED(const char* route)l
extern _native void ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(const char* route, int props)l
extern _native void ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(float dist)l
extern _native void TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(Ped ped, Vehicle vehicle, const char* WPRecording, int p3, int p4, int p5, int p6, float p7, bool p8, float p9)l
extern _native bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(any p0)l
extern _native any GET_VEHICLE_WAYPOINT_PROGRESS(any p0)l
extern _native any GET_VEHICLE_WAYPOINT_TARGET_POINT(any p0)l
extern _native void VEHICLE_WAYPOINT_PLAYBACK_PAUSE(any p0)l
extern _native void VEHICLE_WAYPOINT_PLAYBACK_RESUME(any p0)l
extern _native void VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(any p0)l
extern _native void VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(any p0, float p1)l
extern _native void TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle)l
extern _native void TASK_FORCE_MOTION_STATE(Ped ped, Hash state, bool p2)l
extern _native32(0x6F5D215F) void _TASK_MOVE_NETWORK(Ped ped, const char* task, float multiplier, bool p3, const char* animDict, int flags)l
extern _native32(0x71A5C5DB) void _TASK_MOVE_NETWORK_ADVANCED(Ped ped, const char* p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8, float p9, bool p10, const char* animDict, int flags)l
extern _native bool UNK_0x902656EB(int PlayerID)l
extern _native bool UNK_0x92FDBAE6(any p0)l
extern _native any UNK_0x885724DE(Ped ped, const char* p1)l
extern _native const char* UNK_0x96C0277B(Ped ped)l
extern _native void UNK_0xA79BE783(Ped p0, const char* p1, float p2)l
extern _native void UNK_0xF3538041(Ped p0, any* p1, bool p2)l
extern _native bool UNK_0x1EBB6F3D(any p0, const char* p1)l
extern _native bool UNK_0x72FA5EF2(any p0, any* p1)l
extern _native bool IS_MOVE_BLEND_RATIO_STILL(Ped ped)l
extern _native bool IS_MOVE_BLEND_RATIO_WALKING(Ped ped)l
extern _native bool IS_MOVE_BLEND_RATIO_RUNNING(Ped ped)l
extern _native bool IS_MOVE_BLEND_RATIO_SPRINTING(Ped ped)l
extern _native bool IS_PED_STILL(Ped ped)l
extern _native bool IS_PED_WALKING(Ped ped)l
extern _native bool IS_PED_RUNNING(Ped ped)l
extern _native bool IS_PED_SPRINTING(Ped ped)l
extern _native bool IS_PED_STRAFING(Ped ped)l
extern _native void TASK_SYNCHRONIZED_SCENE(Ped ped, int scene, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, any p9)l
extern _native void TASK_SWEEP_AIM_ENTITY(Ped ped, const char* anim, const char* p2, const char* p3, const char* p4, int p5, Vehicle vehicle, float p7, float p8)l
extern _native void UPDATE_TASK_SWEEP_AIM_ENTITY(Ped ped, Entity entity)l
extern _native void TASK_SWEEP_AIM_POSITION(any p0, any* p1, any* p2, any* p3, any* p4, any p5, float p6, float p7, float p8, float p9, float p10)l
extern _native void UPDATE_TASK_SWEEP_AIM_POSITION(any p0, float p1, float p2, float p3)l
extern _native void TASK_ARREST_PED(Ped ped, Ped target)l
extern _native bool IS_PED_RUNNING_ARREST_TASK(Ped ped)l
extern _native bool IS_PED_BEING_ARRESTED(Ped ped)l
extern _native void UNCUFF_PED(Ped ped)l
extern _native bool IS_PED_CUFFED(Ped ped)l
#pragma endregion //}
#pragma region GAMEPLAY //{
extern _native int GET_ALLOCATED_STACK_SIZE()l
extern _native32(0x11A178B8) int _GET_FREE_STACK_SLOTS_COUNT(int stackSize)l
extern _native void SET_RANDOM_SEED(int time)l
extern _native void SET_TIME_SCALE(float time)l
extern _native void SET_MISSION_FLAG(bool toggle)l
extern _native bool GET_MISSION_FLAG()l
extern _native void SET_RANDOM_EVENT_FLAG(bool p0)l
extern _native any GET_RANDOM_EVENT_FLAG()l
extern _native void UNK_0x8B2DE971(bool p0)l
extern _native void UNK_0xE77199F7(const char* p0)l
extern _native Hash GET_PREV_WEATHER_TYPE_HASH_NAME()l
extern _native Hash GET_NEXT_WEATHER_TYPE_HASH_NAME()l
extern _native bool IS_PREV_WEATHER_TYPE(const char* weatherType)l
extern _native bool IS_NEXT_WEATHER_TYPE(const char* weatherType)l
extern _native void SET_WEATHER_TYPE_PERSIST(const char* weatherType)l
extern _native void SET_WEATHER_TYPE_NOW_PERSIST(const char* weatherType)l
extern _native void SET_WEATHER_TYPE_NOW(const char* weatherType)l
extern _native32(0x386F0D25) void _SET_WEATHER_TYPE_OVER_TIME(const char* weatherType, float time)l
extern _native void SET_RANDOM_WEATHER_TYPE()l
extern _native void CLEAR_WEATHER_TYPE_PERSIST()l
extern _native32(0x9A5C1D56) void _GET_WEATHER_TYPE_TRANSITION(any* p0, any* p1, float* progress_or_time)l
extern _native32(0x5CA74040) void _SET_WEATHER_TYPE_TRANSITION(Hash weatherType1, Hash weatherType2, float percentWeather2)l
extern _native void SET_OVERRIDE_WEATHER(const char* weatherType)l
extern _native void CLEAR_OVERRIDE_WEATHER()l
extern _native void UNK_0x625181DC(float p0)l
extern _native void UNK_0xBEBBFDC8(float p0)l
extern _native void UNK_0x6926AB03(float p0)l
extern _native void UNK_0xD447439D(float p0)l
extern _native void UNK_0x584E9C59(float p0)l
extern _native void UNK_0x5656D578(float p0)l
extern _native void UNK_0x0DE40C28(float p0)l
extern _native void UNK_0x98C9138B(float p0)l
extern _native void UNK_0xFB1A9CDE(float p0)l
extern _native void UNK_0x1C0CAE89(float p0)l
extern _native void UNK_0x4671AC2E(float p0)l
extern _native void UNK_0xDA02F415(float p0)l
extern _native void UNK_0x5F3DDEC0(float p0)l
extern _native void UNK_0x63A89684(float p0)l
extern _native void SET_WIND(float speed)l
extern _native void SET_WIND_SPEED(float speed)l
extern _native float GET_WIND_SPEED()l
extern _native void SET_WIND_DIRECTION(float direction)l
extern _native vector3 GET_WIND_DIRECTION()l
extern _native any GET_RAIN_LEVEL()l
extern _native any GET_SNOW_LEVEL()l
extern _native32(0xDF38165E) void _CREATE_LIGHTNING_THUNDER()l
extern _native void UNK_0x8727A4C5(const char* p0)l
extern _native32(0xED88FC61) void _SET_CLOUD_HAT_TRANSITION(const char* type, float transitionTime)l
extern _native void UNK_0xC9FA6E07(const char* p0, float p1)l
extern _native32(0x2D7787BC) void _CLEAR_CLOUD_HAT()l
extern _native int GET_GAME_TIMER()l
extern _native float GET_FRAME_TIME()l
extern _native int GET_FRAME_COUNT()l
extern _native float GET_RANDOM_FLOAT_IN_RANGE(float startRange, float endRange)l
extern _native int GET_RANDOM_INT_IN_RANGE(int startRange, int endRange)l
extern _native bool GET_GROUND_Z_FOR_3D_COORD(vector3 vec, float* groundZ, bool unk)l
extern _native bool UNK_0x64D91CED(vector3 vec, float* p3, vector3* p4)l
extern _native float ASIN(float p0)l
extern _native float ACOS(float p0)l
extern _native float TAN(float p0)l
extern _native float ATAN(float p0)l
extern _native float ATAN2(float p0, float p1)l
extern _native float GET_DISTANCE_BETWEEN_COORDS(vector3 vec_1, vector3 vec_2, bool useZ)l
extern _native float GET_ANGLE_BETWEEN_2D_VECTORS(vector2 vector_1, vector2 vector_2)l
extern _native float GET_HEADING_FROM_VECTOR_2D(vector2 d)l
extern _native float UNK_0x89459F0A(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)l
extern _native vector3 UNK_0xCAECF37E(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)l
extern _native bool UNK_0xC6CC812C(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, any* p12)l
extern _native void SET_BIT(int* address, int offset)l
extern _native void CLEAR_BIT(int* address, int offset)l
extern _native Hash GET_HASH_KEY(const char* value)l
extern _native void UNK_0x87B92190(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, any* p9, any* p10, any* p11, any* p12)l
extern _native bool IS_AREA_OCCUPIED(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9, bool p10, any p11, bool p12)l
extern _native bool IS_POSITION_OCCUPIED(vector3 vec, float range, bool p4, bool p5, bool p6, bool p7, bool p8, any p9, bool p10)l
extern _native bool IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native void CLEAR_AREA(vector3 vec, float radius, bool p4, bool ignoreCopCars, bool ignoreObjects, bool p7)l
extern _native32(0x20E4FFD9) void _CLEAR_AREA_OF_EVERYTHING(vector3 vec, float radius, bool p4, bool p5, bool p6, bool p7)l
extern _native void CLEAR_AREA_OF_VEHICLES(vector3 vec, float radius, bool p4, bool p5, bool p6, bool p7, bool p8)l
extern _native void CLEAR_ANGLED_AREA_OF_VEHICLES(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, bool p8, bool p9, bool p10, bool p11)l
extern _native void CLEAR_AREA_OF_OBJECTS(vector3 vec, float radius, int flags)l
extern _native void CLEAR_AREA_OF_PEDS(vector3 vec, float radius, int flags)l
extern _native void CLEAR_AREA_OF_COPS(vector3 vec, float radius, int flags)l
extern _native void CLEAR_AREA_OF_PROJECTILES(vector3 vec, float radius, int flags)l
extern _native void SET_SAVE_MENU_ACTIVE(bool unk)l
extern _native int UNK_0x39771F21()l
extern _native void SET_CREDITS_ACTIVE(bool toggle)l
extern _native void UNK_0x75B06B5A(bool toggle)l
extern _native any UNK_0x2569C9A7()l
extern _native void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(const char* scriptName)l
extern _native void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME()l
extern _native int ADD_HOSPITAL_RESTART(vector3 vec, float p3, any p4)l
extern _native void DISABLE_HOSPITAL_RESTART(int hospitalIndex, bool toggle)l
extern _native any ADD_POLICE_RESTART(float p0, float p1, float p2, float p3, any p4)l
extern _native void DISABLE_POLICE_RESTART(int policeIndex, bool toggle)l
extern _native32(0x296574AE) void _DISABLE_AUTOMATIC_RESPAWN(bool disableRespawn)l
extern _native void IGNORE_NEXT_RESTART(bool toggle)l
extern _native void SET_FADE_OUT_AFTER_DEATH(bool toggle)l
extern _native void SET_FADE_OUT_AFTER_ARREST(bool toggle)l
extern _native void SET_FADE_IN_AFTER_DEATH_ARREST(bool toggle)l
extern _native void SET_FADE_IN_AFTER_LOAD(bool toggle)l
extern _native any REGISTER_SAVE_HOUSE(float p0, float p1, float p2, float p3, any* p4, any p5, any p6)l
extern _native void SET_SAVE_HOUSE(any p0, bool p1, bool p2)l
extern _native bool OVERRIDE_SAVE_HOUSE(bool p0, float p1, float p2, float p3, float p4, bool p5, float p6, float p7)l
extern _native any UNK_0xC4D71AB4(any p0, any p1, any p2, any p3)l
extern _native void DO_AUTO_SAVE()l
extern _native any UNK_0xA8546914()l
extern _native bool IS_AUTO_SAVE_IN_PROGRESS()l
extern _native any UNK_0x78350773()l
extern _native void UNK_0x5A45B11A()l
extern _native void BEGIN_REPLAY_STATS(any p0, any p1)l
extern _native void UNK_0x81216EE0(any p0)l
extern _native void END_REPLAY_STATS()l
extern _native any UNK_0xC58250F1()l
extern _native any UNK_0x50C39926()l
extern _native any UNK_0x710E5D1E()l
extern _native any UNK_0xC7BD1AF0()l
extern _native any UNK_0x22BE2423(any p0)l
extern _native void CLEAR_REPLAY_STATS()l
extern _native any UNK_0xF62B3C48()l
extern _native any UNK_0x3589452B()l
extern _native any UNK_0x144AAF22()l
extern _native bool IS_MEMORY_CARD_IN_USE()l
extern _native void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(vector3 vec_1, vector3 vec_2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed)l
extern _native void UNK_0x52ACCB7B(vector3 vec_1, vector3 vec_2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity)l
extern _native void GET_MODEL_DIMENSIONS(Hash modelHash, vector3* minimum, vector3* maximum)l
extern _native void SET_FAKE_WANTED_LEVEL(int fakeWantedLevel)l
extern _native int GET_FAKE_WANTED_LEVEL()l
extern _native bool IS_BIT_SET(int address, int offset)l
extern _native void USING_MISSION_CREATOR(bool toggle)l
extern _native void UNK_0x082BA6F2(bool p0)l
extern _native void SET_MINIGAME_IN_PROGRESS(bool toggle)l
extern _native bool IS_MINIGAME_IN_PROGRESS()l
extern _native bool IS_THIS_A_MINIGAME_SCRIPT()l
extern _native bool IS_SNIPER_INVERTED()l
extern _native any UNK_0xBAF17315()l
extern _native int GET_PROFILE_SETTING(int profileSetting)l
extern _native bool ARE_STRINGS_EQUAL(const char* string1, const char* string2)l
extern _native int COMPARE_STRINGS(const char* str1, const char* str2, bool matchCase, int maxLength)l
extern _native int ABSI(int value)l
extern _native float ABSF(float value)l
extern _native bool IS_SNIPER_BULLET_IN_AREA(vector3 vec_1, vector3 vec_2)l
extern _native bool IS_PROJECTILE_IN_AREA(vector3 vec_1, vector3 vec_2, bool ownedByPlayer)l
extern _native bool IS_PROJECTILE_TYPE_IN_AREA(vector3 vec_1, vector3 vec_2, int type, bool p7)l
extern _native bool IS_PROJECTILE_TYPE_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7, bool p8)l
extern _native bool UNK_0xBE81F1E2(float p0, float p1, float p2, any p3, float p4, bool p5)l
extern _native any UNK_0x1A40454B(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native bool UNK_0x6BDE5CE4(Ped ped, Hash weaponHash, float radius, Entity* entity, bool p4)l
extern _native any UNK_0x507BC6F7(Ped ped, Hash weaponhash, float p2, float p3, float p4, bool p5)l
extern _native bool IS_BULLET_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7)l
extern _native bool IS_BULLET_IN_AREA(float p0, float p1, float p2, float p3, bool p4)l
extern _native bool IS_BULLET_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, bool p6)l
extern _native bool HAS_BULLET_IMPACTED_IN_AREA(vector3 vec, float p3, bool p4, bool p5)l
extern _native bool HAS_BULLET_IMPACTED_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7)l
extern _native bool IS_ORBIS_VERSION()l
extern _native bool IS_DURANGO_VERSION()l
extern _native bool IS_XBOX360_VERSION()l
extern _native bool IS_PS3_VERSION()l
extern _native bool IS_PC_VERSION()l
extern _native bool IS_AUSSIE_VERSION()l
extern _native bool IS_STRING_NULL(const char* string)l
extern _native bool IS_STRING_NULL_OR_EMPTY(const char* string)l
extern _native bool STRING_TO_INT(const char* string, int* outInteger)l
extern _native void SET_BITS_IN_RANGE(int* var, unsigned int rangeStart, unsigned int rangeEnd, int sourceNum)l
extern _native int GET_BITS_IN_RANGE(int var, int rangeStart, int rangeEnd)l
extern _native int ADD_STUNT_JUMP(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, any p15, any p16)l
extern _native int ADD_STUNT_JUMP_ANGLED(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, float p15, float p16, any p17, any p18)l
extern _native void DELETE_STUNT_JUMP(int p0)l
extern _native void ENABLE_STUNT_JUMP_SET(int p0)l
extern _native void DISABLE_STUNT_JUMP_SET(int p0)l
extern _native void UNK_0x3C806A2D(bool p0)l
extern _native bool IS_STUNT_JUMP_IN_PROGRESS()l
extern _native bool IS_STUNT_JUMP_MESSAGE_SHOWING()l
extern _native any UNK_0x006F9BA2()l
extern _native void CANCEL_STUNT_JUMP()l
extern _native void SET_GAME_PAUSED(bool toggle)l
extern _native void SET_THIS_SCRIPT_CAN_BE_PAUSED(bool toggle)l
extern _native void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(bool toggle)l
extern _native32(0xFF6191E1) bool _HAS_BUTTON_COMBINATION_JUST_BEEN_ENTERED(Hash hash, int amount)l
extern _native32(0x721B2492) void _USE_FREEMODE_MAP_BEHAVIOR(bool toggle)l
extern _native32(0xE202879D) void _SET_UNK_MAP_FLAG(int flag)l
extern _native bool IS_FRONTEND_FADING()l
extern _native void POPULATE_NOW()l
extern _native int GET_INDEX_OF_CURRENT_LEVEL()l
extern _native void SET_GRAVITY_LEVEL(int level)l
extern _native void START_SAVE_DATA(any* p0, any p1, bool p2)l
extern _native void STOP_SAVE_DATA()l
extern _native any UNK_0x9EF0BC64(bool p0)l
extern _native void REGISTER_INT_TO_SAVE(any* p0, const char* name)l
extern _native void REGISTER_ENUM_TO_SAVE(any* p0, const char* name)l
extern _native void REGISTER_FLOAT_TO_SAVE(any* p0, const char* name)l
extern _native void REGISTER_BOOL_TO_SAVE(any* p0, const char* name)l
extern _native void REGISTER_TEXT_LABEL_TO_SAVE(any* p0, const char* name)l
extern _native void UNK_0xE2089749(any* p0, const char* name)l
extern _native void UNK_0xF91B8C33(any* p0, const char* name)l
extern _native void UNK_0x74E8FAD9(any* p0, const char* name)l
extern _native void UNK_0x6B4335DD(any* p0, const char* name)l
extern _native32(0xFB45728E) void _START_SAVE_STRUCT(any* p0, int p1, const char* structName)l
extern _native void STOP_SAVE_STRUCT()l
extern _native32(0x893A342C) void _START_SAVE_ARRAY(any* p0, int p1, const char* arrayName)l
extern _native void STOP_SAVE_ARRAY()l
extern _native void ENABLE_DISPATCH_SERVICE(int dispatchType, bool toggle)l
extern _native void UNK_0xE0F0684F(int type, bool toggle)l
extern _native int UNK_0x3CE5BF6B(int p0)l
extern _native bool CREATE_INCIDENT(int incidentType, vector3 vec, int p5, float radius, int* outIncidentID)l
extern _native bool CREATE_INCIDENT_WITH_ENTITY(int incidentType, Ped ped, int amountOfPeople, float radius, int* outIncidentID)l
extern _native void DELETE_INCIDENT(int incidentId)l
extern _native bool IS_INCIDENT_VALID(int incidentId)l
extern _native void UNK_0x0242D88E(any p0, any p1, any p2)l
extern _native void UNK_0x1F38102E(any p0, float p1)l
extern _native bool FIND_SPAWN_POINT_IN_DIRECTION(vector3 vec_1, vector3 vec_2, float distance, vector3* spawnPoint)l
extern _native any UNK_0x42BF09B3(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native void UNK_0xFBDBE374(any p0, bool p1)l
extern _native void ENABLE_TENNIS_MODE(Ped ped, bool toggle, bool p2)l
extern _native bool IS_TENNIS_MODE(Ped ped)l
extern _native void UNK_0xC20A7D2B(any p0, any* p1, any* p2, float p3, float p4, bool p5)l
extern _native bool UNK_0x8501E727(any p0)l
extern _native bool UNK_0x1A332D2D(any p0)l
extern _native void UNK_0x0C8865DF(any p0, any p1, float p2, float p3, float p4, bool p5)l
extern _native void UNK_0x49F977A9(any p0, const char* p1, float p2)l
extern _native void UNK_0x6F009E33(any p0, any p1, any p2)l
extern _native void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE()l
extern _native void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(float p0)l
extern _native void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(any p0, float p1)l
extern _native void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(any p0, float p1)l
extern _native any UNK_0xF557BAF9(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(any p0)l
extern _native void RESET_DISPATCH_SPAWN_BLOCKING_AREAS()l
extern _native void UNK_0xE0C9307E()l
extern _native void UNK_0xA0D8C749(any p0, any p1)l
extern _native void UNK_0x24A4E0B2(any p0, any p1, any p2)l
extern _native void UNK_0x66C3C59C()l
extern _native void UNK_0xD9660339(bool p0)l
extern _native32(0xD2688412) void _DISPLAY_ONSCREEN_KEYBOARD_2(int p0, const char* windowTitle, any* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, const char* defaultConcat4, const char* defaultConcat5, const char* defaultConcat6, const char* defaultConcat7, int maxInputLength)l
extern _native void DISPLAY_ONSCREEN_KEYBOARD(int p0, const char* windowTitle, const char* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, int maxInputLength)l
extern _native int UPDATE_ONSCREEN_KEYBOARD()l
extern _native const char* GET_ONSCREEN_KEYBOARD_RESULT()l
extern _native void UNK_0x3301EA47(int p0)l
extern _native void UNK_0x42B484ED(Hash hash, bool p1)l
extern _native void UNK_0x8F60366E(int p0, bool p1)l
extern _native any SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player)l
extern _native any SET_FIRE_AMMO_THIS_FRAME(Player player)l
extern _native any SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player)l
extern _native any SET_SUPER_JUMP_THIS_FRAME(Player player)l
extern _native bool UNK_0xC3C10FCC()l
extern _native void UNK_0x054EC103()l
extern _native any UNK_0x46B5A15C()l
extern _native32(0x5D209F25) void _RESET_LOCALPLAYER_STATE()l
extern _native void UNK_0x2D33F15A(any p0, any p1, any p2, any p3)l
extern _native void UNK_0xDF99925C()l
extern _native void UNK_0xA27F4472(any p0, any p1, any p2, any p3)l
extern _native bool UNK_0x07FF553F(any p0, any* p1, any* p2)l
#pragma endregion //}
#pragma region AUDIO //{
extern _native void PLAY_PED_RINGTONE(const char* ringtoneName, Ped ped, bool p2)l
extern _native bool IS_PED_RINGTONE_PLAYING(Ped ped)l
extern _native void STOP_PED_RINGTONE(Ped ped)l
extern _native bool IS_MOBILE_PHONE_CALL_ONGOING()l
extern _native any UNK_0x16FB88B5()l
extern _native void CREATE_NEW_SCRIPTED_CONVERSATION()l
extern _native void ADD_LINE_TO_CONVERSATION(int p0, const char* p1, const char* p2, int p3, int p4, bool p5, bool p6, bool p7, bool p8, int p9, bool p10, bool p11, bool p12)l
extern _native void ADD_PED_TO_CONVERSATION(any p0, any ped, const char* p2)l
extern _native void UNK_0x73C6F979(any p0, float p1, float p2, float p3)l
extern _native void UNK_0x88203DDA(any p0, any p1)l
extern _native void SET_MICROPHONE_POSITION(bool p0, vector3 vec_1, vector3 vec_2, vector3 vec_3)l
extern _native void UNK_0x1193ED6E(bool p0)l
extern _native void START_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)l
extern _native void PRELOAD_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)l
extern _native void START_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)l
extern _native void PRELOAD_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)l
extern _native void START_PRELOADED_CONVERSATION()l
extern _native any UNK_0x336F3D35()l
extern _native bool IS_SCRIPTED_CONVERSATION_ONGOING()l
extern _native bool IS_SCRIPTED_CONVERSATION_LOADED()l
extern _native any GET_CURRENT_SCRIPTED_CONVERSATION_LINE()l
extern _native void PAUSE_SCRIPTED_CONVERSATION(bool p0)l
extern _native void RESTART_SCRIPTED_CONVERSATION()l
extern _native any STOP_SCRIPTED_CONVERSATION(bool p0)l
extern _native void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE()l
extern _native void INTERRUPT_CONVERSATION(any p0, any* p1, any* p2)l
extern _native any UNK_0xB58B8FF3(any* p0)l
extern _native void UNK_0x789D8C6C(bool p0)l
extern _native void REGISTER_SCRIPT_WITH_AUDIO(any p0)l
extern _native void UNREGISTER_SCRIPT_WITH_AUDIO()l
extern _native bool REQUEST_MISSION_AUDIO_BANK(const char* p0, bool p1)l
extern _native bool REQUEST_AMBIENT_AUDIO_BANK(const char* p0, bool p1)l
extern _native bool REQUEST_SCRIPT_AUDIO_BANK(const char* p0, bool p1)l
extern _native any HINT_AMBIENT_AUDIO_BANK(any p0, any p1)l
extern _native any HINT_SCRIPT_AUDIO_BANK(any p0, any p1)l
extern _native void RELEASE_MISSION_AUDIO_BANK()l
extern _native void RELEASE_AMBIENT_AUDIO_BANK()l
extern _native void RELEASE_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank)l
extern _native void RELEASE_SCRIPT_AUDIO_BANK()l
extern _native void UNK_0xA58BBF4F()l
extern _native int GET_SOUND_ID()l
extern _native void RELEASE_SOUND_ID(int soundId)l
extern _native void PLAY_SOUND(Player soundId, const char* audioName, const char* audioRef, bool p3, any p4, bool p5)l
extern _native void PLAY_SOUND_FRONTEND(int soundId, const char* audioName, const char* audioRef, bool p3)l
extern _native void UNK_0xC70E6CFA(const char* p0, const char* soundset)l
extern _native void PLAY_SOUND_FROM_ENTITY(int soundId, const char* audioName, Entity entity, const char* audioRef, bool p4, any p5)l
extern _native void PLAY_SOUND_FROM_COORD(int soundId, const char* audioName, vector3 vec, const char* audioRef, bool p6, int range, bool p8)l
extern _native void STOP_SOUND(int soundId)l
extern _native int GET_NETWORK_ID_FROM_SOUND_ID(int soundId)l
extern _native int GET_SOUND_ID_FROM_NETWORK_ID(int netId)l
extern _native void SET_VARIABLE_ON_SOUND(int soundId, any* p1, float p2)l
extern _native void SET_VARIABLE_ON_STREAM(const char* p0, float p1)l
extern _native void OVERRIDE_UNDERWATER_STREAM(any* p0, bool p1)l
extern _native void UNK_0x62D026BE(const char* name, float p1)l
extern _native bool HAS_SOUND_FINISHED(int soundId)l
extern _native32(0x5C57B85D) void _PLAY_AMBIENT_SPEECH1(Ped ped, const char* speechName, const char* speechParam)l
extern _native32(0x444180DB) void _PLAY_AMBIENT_SPEECH2(Ped ped, const char* speechName, const char* speechParam)l
extern _native32(0x8386AE28) void _PLAY_AMBIENT_SPEECH_WITH_VOICE(Ped p0, const char* speechName, const char* voiceName, const char* speechParam, bool p4)l
extern _native32(0xA1A1402E) void _PLAY_AMBIENT_SPEECH_AT_COORDS(const char* p0, const char* p1, float p2, float p3, float p4, const char* p5)l
extern _native void OVERRIDE_TREVOR_RAGE(any* p0)l
extern _native void RESET_TREVOR_RAGE()l
extern _native void SET_PLAYER_ANGRY(Ped playerPed, bool disabled)l
extern _native void PLAY_PAIN(Ped ped, int painID, int p1)l
extern _native void UNK_0x59A3A17D(any* p0)l
extern _native void UNK_0x0E387BFE(any* p0)l
extern _native void SET_AMBIENT_VOICE_NAME(Ped ped, const char* name)l
extern _native void STOP_CURRENT_PLAYING_AMBIENT_SPEECH(Ped ped)l
extern _native bool IS_AMBIENT_SPEECH_PLAYING(Ped p0)l
extern _native bool IS_SCRIPTED_SPEECH_PLAYING(any p0)l
extern _native bool IS_ANY_SPEECH_PLAYING(Ped ped)l
extern _native bool UNK_0x8BD5F11E(Ped ped, const char* speechName, bool unk)l
extern _native bool IS_PED_IN_CURRENT_CONVERSATION(Ped ped)l
extern _native void SET_PED_IS_DRUNK(Ped ped, bool toggle)l
extern _native void UNK_0x498849F3(any p0, any p1, any* p2)l
extern _native bool UNK_0x0CBAF2EF(any p0)l
extern _native void SET_ANIMAL_MOOD(Ped animal, int mood)l
extern _native bool IS_MOBILE_PHONE_RADIO_ACTIVE()l
extern _native void SET_MOBILE_PHONE_RADIO_STATE(bool state)l
extern _native int GET_PLAYER_RADIO_STATION_INDEX()l
extern _native const char* GET_PLAYER_RADIO_STATION_NAME()l
extern _native const char* GET_RADIO_STATION_NAME(int radioStation)l
extern _native any GET_PLAYER_RADIO_STATION_GENRE()l
extern _native bool IS_RADIO_RETUNING()l
extern _native void UNK_0x53DB6994()l
extern _native void UNK_0xD70ECC80()l
extern _native void SET_RADIO_TO_STATION_NAME(const char* stationName)l
extern _native void SET_VEH_RADIO_STATION(Vehicle vehicle, const char* radioStation)l
extern _native void UNK_0x7ABB89D2(Vehicle vehicle)l
extern _native void SET_EMITTER_RADIO_STATION(const char* emitterName, const char* radioStation)l
extern _native void SET_STATIC_EMITTER_ENABLED(const char* emitterName, bool toggle)l
extern _native void SET_RADIO_TO_STATION_INDEX(int radioStation)l
extern _native void SET_FRONTEND_RADIO_ACTIVE(bool active)l
extern _native void UNLOCK_MISSION_NEWS_STORY(int newsStory)l
extern _native int GET_NUMBER_OF_PASSENGER_VOICE_VARIATIONS(any p0)l
extern _native int GET_AUDIBLE_MUSIC_TRACK_TEXT_ID()l
extern _native void PLAY_END_CREDITS_MUSIC(bool play)l
extern _native void SKIP_RADIO_FORWARD()l
extern _native void FREEZE_RADIO_STATION(const char* radioStation)l
extern _native void UNFREEZE_RADIO_STATION(const char* radioStation)l
extern _native void SET_RADIO_AUTO_UNFREEZE(bool toggle)l
extern _native void SET_INITIAL_PLAYER_STATION(const char* radioStation)l
extern _native void SET_USER_RADIO_CONTROL_ENABLED(bool toggle)l
extern _native void SET_RADIO_TRACK(const char* radioStation, const char* radioTrack)l
extern _native void SET_VEHICLE_RADIO_LOUD(Vehicle vehicle, bool toggle)l
extern _native32(0xCBA99F4A) bool _IS_VEHICLE_RADIO_LOUD(Vehicle vehicle)l
extern _native void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(bool Toggle)l
extern _native bool UNK_0x46B0C696()l
extern _native32(0x2A3E5E8B) bool _IS_PLAYER_VEHICLE_RADIO_ENABLED()l
extern _native void SET_VEHICLE_RADIO_ENABLED(Vehicle vehicle, bool toggle)l
extern _native void UNK_0x128C3873(const char* radioStation, const char* p1, bool p2)l
extern _native void UNK_0x1D766976(const char* radioStation)l
extern _native32(0xCC91FCF5) int _MAX_RADIO_STATION_INDEX()l
extern _native int FIND_RADIO_STATION_INDEX(int station)l
extern _native void UNK_0xB1FF7137(const char* radioStation, bool p1)l
extern _native void UNK_0xC8B514E2(float p0)l
extern _native void UNK_0xBE998184(const char* radioStation, const char* p1)l
extern _native void UNK_0x8AFC488D(any p0, bool p1)l
extern _native void SET_AMBIENT_ZONE_STATE(any* p0, bool p1, bool p2)l
extern _native void CLEAR_AMBIENT_ZONE_STATE(const char* zoneName, bool p1)l
extern _native void SET_AMBIENT_ZONE_LIST_STATE(any* p0, bool p1, bool p2)l
extern _native void CLEAR_AMBIENT_ZONE_LIST_STATE(any* p0, bool p1)l
extern _native void SET_AMBIENT_ZONE_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2)l
extern _native void SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2)l
extern _native bool IS_AMBIENT_ZONE_ENABLED(const char* ambientZone)l
extern _native void SET_CUTSCENE_AUDIO_OVERRIDE(const char* p0)l
extern _native void GET_PLAYER_HEADSET_SOUND_ALTERNATE(const char* p0, float p1)l
extern _native any PLAY_POLICE_REPORT(const char* name, float p1)l
extern _native void BLIP_SIREN(Vehicle vehicle)l
extern _native void OVERRIDE_VEH_HORN(Vehicle vehicle, bool mute, int p2)l
extern _native bool IS_HORN_ACTIVE(Vehicle vehicle)l
extern _native void SET_AGGRESSIVE_HORNS(bool toggle)l
extern _native void UNK_0x3C395AEE(bool p0)l
extern _native void UNK_0x8CE63FA1(bool p0, bool p1)l
extern _native bool IS_STREAM_PLAYING()l
extern _native int GET_STREAM_PLAY_TIME()l
extern _native bool LOAD_STREAM(const char* streamName, const char* soundSet)l
extern _native bool LOAD_STREAM_WITH_START_OFFSET(const char* streamName, int startOffset, const char* soundSet)l
extern _native void PLAY_STREAM_FROM_PED(Ped ped)l
extern _native void PLAY_STREAM_FROM_VEHICLE(Vehicle vehicle)l
extern _native void PLAY_STREAM_FROM_OBJECT(Object object)l
extern _native void PLAY_STREAM_FRONTEND()l
extern _native void SPECIAL_FRONTEND_EQUAL(vector3 vec)l
extern _native void STOP_STREAM()l
extern _native void STOP_PED_SPEAKING(Ped ped, bool shaking)l
extern _native void DISABLE_PED_PAIN_AUDIO(Ped ped, bool toggle)l
extern _native bool IS_AMBIENT_SPEECH_DISABLED(Ped ped)l
extern _native void SET_SIREN_WITH_NO_DRIVER(Vehicle vehicle, bool toggle)l
extern _native32(0xDE8BA3CD) void _SOUND_VEHICLE_HORN_THIS_FRAME(Vehicle vehicle)l
extern _native void SET_HORN_ENABLED(Vehicle vehicle, bool toggle)l
extern _native void SET_AUDIO_VEHICLE_PRIORITY(Vehicle vehicle, any p1)l
extern _native void UNK_0x2F0A16D1(any p0, float p1)l
extern _native void USE_SIREN_AS_HORN(Vehicle vehicle, bool toggle)l
extern _native32(0x33B0B007) void _SET_VEHICLE_AUDIO(Vehicle vehicle, const char* audioName)l
extern _native void UNK_0x1C0C5E4C(any p0, const char* p1, const char* p2)l
extern _native bool UNK_0x6E660D3F(Vehicle vehicle)l
extern _native void UNK_0x23BE6432(any p0, float p1)l
extern _native void UNK_0xE81FAC68(any p0, float p1)l
extern _native void UNK_0x9365E042(any p0, bool p1)l
extern _native void UNK_0x2A60A90E(any p0, bool p1)l
extern _native void SET_VEHICLE_BOOST_ACTIVE(Vehicle vehicle, bool Toggle)l
extern _native void UNK_0x934BE749(any p0, bool p1)l
extern _native void UNK_0xE61110A2(any p0, bool p1)l
extern _native void PLAY_VEHICLE_DOOR_OPEN_SOUND(Vehicle vehicle, int p1)l
extern _native void PLAY_VEHICLE_DOOR_CLOSE_SOUND(Vehicle vehicle, int p1)l
extern _native void UNK_0x563B635D(Vehicle vehicle, bool toggle)l
extern _native bool IS_GAME_IN_CONTROL_OF_MUSIC()l
extern _native void SET_GPS_ACTIVE(bool active)l
extern _native void PLAY_MISSION_COMPLETE_AUDIO(const char* audioName)l
extern _native bool IS_MISSION_COMPLETE_PLAYING()l
extern _native any UNK_0xCBE09AEC()l
extern _native void UNK_0xD2858D8A(bool p0)l
extern _native bool START_AUDIO_SCENE(const char* scene)l
extern _native void STOP_AUDIO_SCENE(const char* scene)l
extern _native void STOP_AUDIO_SCENES()l
extern _native bool IS_AUDIO_SCENE_ACTIVE(const char* scene)l
extern _native void SET_AUDIO_SCENE_VARIABLE(const char* scene, const char* variable, float value)l
extern _native void UNK_0xE812925D(any p0)l
extern _native32(0x2BC93264) void _DYNAMIC_MIXER_RELATED_FN(Entity p0, const char* p1, float p2)l
extern _native void UNK_0x308ED0EC(any p0, float p1)l
extern _native any AUDIO_IS_SCRIPTED_MUSIC_PLAYING()l
extern _native bool PREPARE_MUSIC_EVENT(const char* eventName)l
extern _native bool CANCEL_MUSIC_EVENT(const char* eventName)l
extern _native bool TRIGGER_MUSIC_EVENT(const char* eventName)l
extern _native any UNK_0x2705C4D5()l
extern _native any GET_MUSIC_PLAYTIME()l
extern _native void UNK_0x53FC3FEC(any p0, any p1, any p2, any p3)l
extern _native any CLEAR_ALL_BROKEN_GLASS()l
extern _native void UNK_0x95050CAD(bool p0, any p1)l
extern _native void UNK_0xE64F97A0(float p0, float p1)l
extern _native void UNK_0xD87AF337()l
extern _native bool PREPARE_ALARM(const char* alarmName)l
extern _native void START_ALARM(const char* alarmName, bool p2)l
extern _native void STOP_ALARM(const char* alarmName, bool toggle)l
extern _native void STOP_ALL_ALARMS(bool stop)l
extern _native bool IS_ALARM_PLAYING(const char* alarmName)l
extern _native Hash GET_VEHICLE_DEFAULT_HORN(Vehicle vehicle)l
extern _native Hash UNK_0xFD4B5B3B(Vehicle vehicle)l
extern _native void RESET_PED_AUDIO_FLAGS(any p0)l
extern _native void UNK_0xC307D531(any p0, bool p1)l
extern _native32(0x13EB5861) void _FORCE_AMBIENT_SIREN(bool value)l
extern _native void UNK_0x7BED1872(Vehicle vehicle, bool p1)l
extern _native void SET_AUDIO_FLAG(const char* flagName, bool toggle)l
extern _native any PREPARE_SYNCHRONIZED_AUDIO_EVENT(const char* p0, any p1)l
extern _native bool PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(any p0, any* p1)l
extern _native bool PLAY_SYNCHRONIZED_AUDIO_EVENT(any p0)l
extern _native bool STOP_SYNCHRONIZED_AUDIO_EVENT(any p0)l
extern _native void UNK_0x55A21772(any* p0, float p1, float p2, float p3)l
extern _native32(0xA17F9AB0) void _SET_SYNCHRONIZED_AUDIO_EVENT_POSITION_THIS_FRAME(const char* p0, Entity p1)l
extern _native void UNK_0x62B43677(int p0)l
extern _native void UNK_0x8AD670EC(const char* p0, const char* p1)l
extern _native void UNK_0xD24B4D0C(const char* p0)l
extern _native void UNK_0x7262B5BA()l
extern _native any UNK_0x93A44A1F()l
extern _native void UNK_0x13777A0B(Ped ped)l
extern _native void UNK_0x1134F68B()l
extern _native void UNK_0xE0047BFD(bool p0)l
#pragma endregion //}
#pragma region CUTSCENE //{
extern _native void REQUEST_CUTSCENE(const char* cutsceneName, int p1)l
extern _native32(0xD98F656A) void _REQUEST_CUTSCENE_EX(const char* cutsceneName, int p1, int p2)l
extern _native void REMOVE_CUTSCENE()l
extern _native bool HAS_CUTSCENE_LOADED()l
extern _native bool HAS_THIS_CUTSCENE_LOADED(const char* cutsceneName)l
extern _native void UNK_0x25A2CABC(int p0)l
extern _native bool UNK_0xDD8878E9()l
extern _native bool UNK_0x7B93CDAA(int p0)l
extern _native void UNK_0x47DB08A9(const char* p0, any p1, any p2)l
extern _native void START_CUTSCENE(int p0)l
extern _native void START_CUTSCENE_AT_COORDS(vector3 vec, int p3)l
extern _native void STOP_CUTSCENE(bool p0)l
extern _native void STOP_CUTSCENE_IMMEDIATELY()l
extern _native void SET_CUTSCENE_ORIGIN(vector3 vec, float p3, int p4)l
extern _native int GET_CUTSCENE_TIME()l
extern _native int GET_CUTSCENE_TOTAL_DURATION()l
extern _native bool WAS_CUTSCENE_SKIPPED()l
extern _native bool HAS_CUTSCENE_FINISHED()l
extern _native bool IS_CUTSCENE_ACTIVE()l
extern _native bool IS_CUTSCENE_PLAYING()l
extern _native int GET_CUTSCENE_SECTION_PLAYING()l
extern _native Entity GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native int UNK_0x5AE68AE6()l
extern _native void REGISTER_ENTITY_FOR_CUTSCENE(Ped cutscenePed, const char* cutsceneEntName, int p2, Hash modelHash, int p4)l
extern _native Entity GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native void SET_CUTSCENE_TRIGGER_AREA(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native bool CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native bool CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash)l
extern _native bool CAN_SET_EXIT_STATE_FOR_CAMERA(bool p0)l
extern _native void UNK_0x35721A08(bool toggle)l
extern _native void SET_CUTSCENE_FADE_VALUES(bool p0, bool p1, bool p2, bool p3)l
extern _native void UNK_0x8338DA1D(bool p0)l
extern _native void UNK_0x04377C10(bool p0)l
extern _native any UNK_0xDBD88708()l
extern _native void UNK_0x28D54A7F(bool p0)l
extern _native void REGISTER_SYNCHRONISED_SCRIPT_SPEECH()l
extern _native void SET_CUTSCENE_PED_COMPONENT_VARIATION(const char* cutsceneEntName, int p1, int p2, int p3, Hash modelHash)l
extern _native void UNK_0x1E7DA95E(const char* cutsceneEntName, Ped ped, Hash modelHash)l
extern _native bool DOES_CUTSCENE_ENTITY_EXIST(const char* cutsceneEntName, Hash modelHash)l
extern _native void SET_CUTSCENE_PED_PROP_VARIATION(const char* cutsceneEntName, int p1, int p2, int p3, Hash modelHash)l
extern _native bool UNK_0x4315A7C5()l
#pragma endregion //}
#pragma region INTERIOR //{
extern _native int GET_INTERIOR_GROUP_ID(int interiorID)l
extern _native vector3 GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(int interiorID, vector3 vec)l
extern _native bool IS_INTERIOR_SCENE()l
extern _native bool IS_VALID_INTERIOR(int interiorID)l
extern _native void CLEAR_ROOM_FOR_ENTITY(Entity entity)l
extern _native void FORCE_ROOM_FOR_ENTITY(Entity entity, int interiorID, Hash roomHashKey)l
extern _native Hash GET_ROOM_KEY_FROM_ENTITY(Entity entity)l
extern _native Hash GET_KEY_FOR_ENTITY_IN_ROOM(Entity entity)l
extern _native int GET_INTERIOR_FROM_ENTITY(Entity entity)l
extern _native void UNK_0xE645E162(Entity entity, int interiorID)l
extern _native void UNK_0xD79803B5(int interiorID, Hash roomHashKey)l
extern _native void UNK_0x1F6B4B13(const char* roomName)l
extern _native void UNK_0x0E9529CC(Hash roomHashKey)l
extern _native32(0x4FF3D3F5) Hash _GET_ROOM_KEY_FROM_GAMEPLAY_CAM()l
extern _native void UNK_0x617DC75D()l
extern _native int GET_INTERIOR_AT_COORDS(vector3 vec)l
extern _native void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Pickup pickup, const char* roomName)l
extern _native32(0x3ADA414E) void _LOAD_INTERIOR(int interiorID)l
extern _native void UNPIN_INTERIOR(int interiorID)l
extern _native bool IS_INTERIOR_READY(int interiorID)l
extern _native int GET_INTERIOR_AT_COORDS_WITH_TYPE(vector3 vec, const char* interiorType)l
extern _native32(0x7762249C) bool _ARE_COORDS_COLLIDING_WITH_EXTERIOR(vector3 vec)l
extern _native int GET_INTERIOR_FROM_COLLISION(vector3 vec)l
extern _native32(0xC80A5DDF) void _ENABLE_INTERIOR_PROP(int interiorID, const char* propName)l
extern _native32(0xDBA768A1) void _DISABLE_INTERIOR_PROP(int interiorID, const char* propName)l
extern _native32(0x39A3CC6F) bool _IS_INTERIOR_PROP_ENABLED(int interiorID, const char* propName)l
extern _native void REFRESH_INTERIOR(int interiorID)l
extern _native32(0x1F375B4C) void _HIDE_MAP_OBJECT_THIS_FRAME(Hash mapObjectHash)l
extern _native void DISABLE_INTERIOR(int interiorID, bool toggle)l
extern _native bool IS_INTERIOR_DISABLED(int interiorID)l
extern _native void CAP_INTERIOR(int interiorID, bool toggle)l
extern _native bool IS_INTERIOR_CAPPED(int interiorID)l
extern _native void UNK_0x5EF9C5C2(bool toggle)l
#pragma endregion //}
#pragma region CAM //{
extern _native void RENDER_SCRIPT_CAMS(bool render, bool ease, int easeTime, bool p3, bool p4)l
extern _native void UNK_0xD3C08183(bool render, any p1, any p2)l
extern _native Cam CREATE_CAM(const char* camName, bool p1)l
extern _native Cam CREATE_CAM_WITH_PARAMS(const char* camName, vector3 pos, vector3 rot, float fov, bool p8, int p9)l
extern _native Cam CREATE_CAMERA(Hash camHash, bool p1)l
extern _native Cam CREATE_CAMERA_WITH_PARAMS(Hash camHash, vector3 pos, vector3 rot, float fov, bool p8, any p9)l
extern _native void DESTROY_CAM(Cam cam, bool thisScriptCheck)l
extern _native void DESTROY_ALL_CAMS(bool thisScriptCheck)l
extern _native bool DOES_CAM_EXIST(Cam cam)l
extern _native void SET_CAM_ACTIVE(Cam cam, bool active)l
extern _native bool IS_CAM_ACTIVE(Cam cam)l
extern _native bool IS_CAM_RENDERING(Cam cam)l
extern _native Cam GET_RENDERING_CAM()l
extern _native vector3 GET_CAM_COORD(Cam cam)l
extern _native vector3 GET_CAM_ROT(Cam cam, int rotationOrder)l
extern _native float GET_CAM_FOV(Cam cam)l
extern _native float GET_CAM_NEAR_CLIP(Cam cam)l
extern _native float GET_CAM_FAR_CLIP(Cam cam)l
extern _native float GET_CAM_FAR_DOF(Cam cam)l
extern _native void SET_CAM_PARAMS(Cam cam, vector3 pos, vector3 rot, float fieldOfView, any p8, int p9, int p10, int p11)l
extern _native void SET_CAM_COORD(Cam cam, vector3 pos)l
extern _native void SET_CAM_ROT(Cam cam, vector3 rot, int rotationOrder)l
extern _native void SET_CAM_FOV(Cam cam, float fieldOfView)l
extern _native void SET_CAM_NEAR_CLIP(Cam cam, float nearClip)l
extern _native void SET_CAM_FAR_CLIP(Cam cam, float farClip)l
extern _native void SET_CAM_MOTION_BLUR_STRENGTH(Cam cam, float strength)l
extern _native void SET_CAM_NEAR_DOF(Cam cam, float nearDOF)l
extern _native void SET_CAM_FAR_DOF(Cam cam, float farDOF)l
extern _native void SET_CAM_DOF_STRENGTH(Cam cam, float dofStrength)l
extern _native void SET_CAM_DOF_PLANES(Cam cam, float p1, float p2, float p3, float p4)l
extern _native void SET_CAM_USE_SHALLOW_DOF_MODE(Cam cam, bool toggle)l
extern _native void SET_USE_HI_DOF()l
extern _native void ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, vector3 Offset, bool isRelative)l
extern _native void ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, vector3 vec, bool heading)l
extern _native void DETACH_CAM(Cam cam)l
extern _native void SET_CAM_INHERIT_ROLL_VEHICLE(Cam cam, bool p1)l
extern _native void POINT_CAM_AT_COORD(Cam cam, vector3 vec)l
extern _native void POINT_CAM_AT_ENTITY(Cam cam, Entity entity, float p2, float p3, float p4, bool p5)l
extern _native void POINT_CAM_AT_PED_BONE(Cam cam, int ped, int boneIndex, vector3 vec, bool p6)l
extern _native void STOP_CAM_POINTING(Cam cam)l
extern _native void SET_CAM_AFFECTS_AIMING(Cam cam, bool toggle)l
extern _native void UNK_0xE1A0B2F1(any p0, bool p1)l
extern _native void UNK_0x43220969(any p0, bool p1)l
extern _native void SET_CAM_DEBUG_NAME(Cam camera, const char* name)l
extern _native void ADD_CAM_SPLINE_NODE(Cam camera, vector3 vec, vector3 Rot, int length, int p8, int p9)l
extern _native void UNK_0x30510511(any p0, any p1, any p2, any p3)l
extern _native void UNK_0xBA6C085B(any p0, any p1, any p2, any p3)l
extern _native void UNK_0xB4737F03(any p0, any p1, any p2)l
extern _native void SET_CAM_SPLINE_PHASE(Cam cam, float p1)l
extern _native float GET_CAM_SPLINE_PHASE(Cam cam)l
extern _native float GET_CAM_SPLINE_NODE_PHASE(Cam cam)l
extern _native void SET_CAM_SPLINE_DURATION(int cam, int timeDuration)l
extern _native void UNK_0x15E141CE(any p0, any p1)l
extern _native bool GET_CAM_SPLINE_NODE_INDEX(Cam cam)l
extern _native void UNK_0x21D275DA(any p0, any p1, any p2, float p3)l
extern _native void UNK_0xA3BD9E94(any p0, any p1, float p2)l
extern _native void OVERRIDE_CAM_SPLINE_VELOCITY(Cam cam, int p1, float p2, float p3)l
extern _native void OVERRIDE_CAM_SPLINE_MOTION_BLUR(Cam cam, int p1, float p2, float p3)l
extern _native void UNK_0xC90B2DDC(any p0, any p1, any p2)l
extern _native bool IS_CAM_SPLINE_PAUSED(any p0)l
extern _native void SET_CAM_ACTIVE_WITH_INTERP(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation)l
extern _native bool IS_CAM_INTERPOLATING(Cam cam)l
extern _native void SHAKE_CAM(Cam cam, const char* type, float amplitude)l
extern _native void ANIMATED_SHAKE_CAM(Cam cam, const char* p1, const char* p2, const char* p3, float amplitude)l
extern _native bool IS_CAM_SHAKING(Cam cam)l
extern _native void SET_CAM_SHAKE_AMPLITUDE(Cam cam, float amplitude)l
extern _native void STOP_CAM_SHAKING(Cam cam, bool p1)l
extern _native void UNK_0x2B0F05CD(const char* p0, float p1)l
extern _native void UNK_0xCB75BD9C(const char* p0, const char* p1, const char* p2, float p3)l
extern _native bool IS_SCRIPT_GLOBAL_SHAKING()l
extern _native void STOP_SCRIPT_GLOBAL_SHAKING(bool p0)l
extern _native bool PLAY_CAM_ANIM(Cam cam, const char* animName, const char* animDictionary, vector3 vec, vector3 Rot, bool p9, int p10)l
extern _native bool IS_CAM_PLAYING_ANIM(Cam cam, const char* animName, const char* animDictionary)l
extern _native void SET_CAM_ANIM_CURRENT_PHASE(Cam cam, float phase)l
extern _native float GET_CAM_ANIM_CURRENT_PHASE(Cam cam)l
extern _native bool PLAY_SYNCHRONIZED_CAM_ANIM(any p0, any p1, const char* animName, const char* animDictionary)l
extern _native void UNK_0x56F9ED27(any p0, float p1, float p2, float p3)l
extern _native32(0x71570DBA) void _SET_CAMERA_RANGE(Cam cam, float range)l
extern _native void UNK_0x60B345DE(any p0, float p1, float p2, float p3)l
extern _native void UNK_0x44473EFC(Cam p0)l
extern _native bool UNK_0xDA931D65(any p0)l
extern _native bool IS_SCREEN_FADED_OUT()l
extern _native bool IS_SCREEN_FADED_IN()l
extern _native bool IS_SCREEN_FADING_OUT()l
extern _native bool IS_SCREEN_FADING_IN()l
extern _native void DO_SCREEN_FADE_IN(int duration)l
extern _native void DO_SCREEN_FADE_OUT(int duration)l
extern _native any SET_WIDESCREEN_BORDERS(bool p0, int p1)l
extern _native vector3 GET_GAMEPLAY_CAM_COORD()l
extern _native vector3 GET_GAMEPLAY_CAM_ROT(int rotationOrder)l
extern _native float GET_GAMEPLAY_CAM_FOV()l
extern _native void CUSTOM_MENU_COORDINATES(float p0)l
extern _native void UNK_0x1126E37C(float p0)l
extern _native float GET_GAMEPLAY_CAM_RELATIVE_HEADING()l
extern _native void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading)l
extern _native float GET_GAMEPLAY_CAM_RELATIVE_PITCH()l
extern _native any SET_GAMEPLAY_CAM_RELATIVE_PITCH(float x, float Value2)l
extern _native void SHAKE_GAMEPLAY_CAM(const char* shakeName, float intensity)l
extern _native bool IS_GAMEPLAY_CAM_SHAKING()l
extern _native void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(float amplitude)l
extern _native void STOP_GAMEPLAY_CAM_SHAKING(bool p0)l
extern _native void UNK_0x7D3007A2(any p0)l
extern _native bool IS_GAMEPLAY_CAM_RENDERING()l
extern _native bool UNK_0xC0B00C20()l
extern _native bool UNK_0x60C23785()l
extern _native void UNK_0x20BFF6E5(bool p0)l
extern _native32(0xA61FF9AC) void _ENABLE_CROSSHAIR_THIS_FRAME()l
extern _native bool IS_GAMEPLAY_CAM_LOOKING_BEHIND()l
extern _native void UNK_0x2701A9AD(Entity entity)l
extern _native void UNK_0xC4736ED3(Entity entity)l
extern _native void UNK_0x6B0E9D57()l
extern _native bool IS_SPHERE_VISIBLE(vector3 vec, float radius)l
extern _native bool IS_FOLLOW_PED_CAM_ACTIVE()l
extern _native bool SET_FOLLOW_PED_CAM_CUTSCENE_CHAT(const char* p0, int p1)l
extern _native void UNK_0x8DC53629(bool p0, bool p1)l
extern _native void UNK_0x1F9DE6E4()l
extern _native32(0x749909AC) any _CLAMP_GAMEPLAY_CAM_YAW(float minimum, float maximum)l
extern _native32(0xFA3A16E7) any _CLAMP_GAMEPLAY_CAM_PITCH(float minimum, float maximum)l
extern _native32(0x77340650) void _ANIMATE_GAMEPLAY_CAM_ZOOM(float p0, float distance)l
extern _native any UNK_0x4B22C5CB(Vehicle p0, int p1)l
extern _native int GET_FOLLOW_PED_CAM_ZOOM_LEVEL()l
extern _native int GET_FOLLOW_PED_CAM_VIEW_MODE()l
extern _native void SET_FOLLOW_PED_CAM_VIEW_MODE(int viewMode)l
extern _native bool IS_FOLLOW_VEHICLE_CAM_ACTIVE()l
extern _native void UNK_0x9DB5D391(bool p0)l
extern _native void SET_TIME_IDLE_DROP(bool p0, bool p1)l
extern _native int GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL()l
extern _native void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(int zoomLevel)l
extern _native int GET_FOLLOW_VEHICLE_CAM_VIEW_MODE()l
extern _native void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(int viewMode)l
extern _native any UNK_0xF3B148A6(any p0)l
extern _native void UNK_0x1DEBCB45(any p0, any p1)l
extern _native bool IS_AIM_CAM_ACTIVE()l
extern _native bool UNK_0x8F320DE4()l
extern _native bool IS_FIRST_PERSON_AIM_CAM_ACTIVE()l
extern _native void DISABLE_AIM_CAM_THIS_UPDATE()l
extern _native32(0x33951005) float _GET_GAMEPLAY_CAM_ZOOM()l
extern _native any UNK_0x9F4AF763(float p0)l
extern _native void UNK_0x68BA0730(float p0, float p1)l
extern _native void UNK_0x2F29F0D5(float p0, float p1)l
extern _native void UNK_0x76DAC96C(float p0, float p1)l
extern _native void UNK_0x0E21069D(float p0)l
extern _native void UNK_0x71E9C63E(float p0)l
extern _native void UNK_0xD1EEBC45(bool p0)l
extern _native32(0x9C84BDA0) vector3 _GET_GAMEPLAY_CAM_COORDS()l
extern _native32(0x1FFBEFC5) vector3 _GET_GAMEPLAY_CAM_ROT(int rotationOrder)l
extern _native int UNK_0xACADF916(any p0, any p1)l
extern _native float UNK_0x721B763B()l
extern _native float UNK_0x23E3F106(any p0)l
extern _native float UNK_0x457AE195()l
extern _native float UNK_0x46CB3A49()l
extern _native float UNK_0x19297A7A()l
extern _native float UNK_0xF24777CA()l
extern _native float UNK_0x38992E83()l
extern _native void SET_GAMEPLAY_COORD_HINT(float p0, float p1, float p2, any p3, any p4, any p5, any p6)l
extern _native void SET_GAMEPLAY_PED_HINT(Ped p0, vector3 vec_1, bool p4, any p5, any p6, any p7)l
extern _native void SET_GAMEPLAY_VEHICLE_HINT(any p0, float p1, float p2, float p3, bool p4, any p5, any p6, any p7)l
extern _native void SET_GAMEPLAY_OBJECT_HINT(any p0, float p1, float p2, float p3, bool p4, any p5, any p6, any p7)l
extern _native void SET_GAMEPLAY_ENTITY_HINT(Entity entity, vector3 Offset, bool p4, int p5, int p6, int p7, any p8)l
extern _native bool IS_GAMEPLAY_HINT_ACTIVE()l
extern _native void STOP_GAMEPLAY_HINT(bool p0)l
extern _native void UNK_0xCAFEE798(bool p0)l
extern _native void SET_GAMEPLAY_HINT_FOV(float FOV)l
extern _native void UNK_0x72E8CD3A(float p0)l
extern _native void UNK_0x79472AE3(float p0)l
extern _native void UNK_0xFC7464A0(float p0)l
extern _native void UNK_0x3554AA0E(float p0)l
extern _native void GET_IS_MULTIPLAYER_BRIEF(bool p0)l
extern _native void SET_CINEMATIC_BUTTON_ACTIVE(bool p0)l
extern _native bool IS_CINEMATIC_CAM_RENDERING()l
extern _native void SHAKE_CINEMATIC_CAM(const char* p0, float p1)l
extern _native bool IS_CINEMATIC_CAM_SHAKING()l
extern _native void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(float p0)l
extern _native void STOP_CINEMATIC_CAM_SHAKING(bool p0)l
extern _native32(0x5AC6DAC9) void _DISABLE_VEHICLE_FIRST_PERSON_CAM_THIS_FRAME()l
extern _native void UNK_0x837F8581()l
extern _native void UNK_0x65DDE8AF()l
extern _native void UNK_0xD75CDD75()l
extern _native bool UNK_0x96A07066()l
extern _native void CREATE_CINEMATIC_SHOT(any p0, int p1, any p2, Entity entity)l
extern _native bool IS_CINEMATIC_SHOT_ACTIVE(any p0)l
extern _native void STOP_CINEMATIC_SHOT(any p0)l
extern _native void UNK_0xFBB85E02(bool p0)l
extern _native void UNK_0x4938C82F()l
extern _native void SET_CINEMATIC_MODE_ACTIVE(bool p0)l
extern _native any UNK_0x6739AD55()l
extern _native void STOP_CUTSCENE_CAM_SHAKING()l
extern _native void UNK_0x067BA6F5(float p0)l
extern _native Entity UNK_0xFD99BE2B(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8)l
extern _native void UNK_0xE206C450()l
extern _native32(0xB06CCD38) void _SET_CAM_EFFECT(int p0)l
#pragma endregion //}
#pragma region WEAPON //{
extern _native void ENABLE_LASER_SIGHT_RENDERING(bool toggle)l
extern _native Hash GET_WEAPON_COMPONENT_TYPE_MODEL(Hash componentHash)l
extern _native Hash GET_WEAPONTYPE_MODEL(Hash weaponHash)l
extern _native Hash GET_WEAPONTYPE_SLOT(Hash weaponHash)l
extern _native Hash GET_WEAPONTYPE_GROUP(Hash weaponHash)l
extern _native void SET_CURRENT_PED_WEAPON(Ped ped, Hash weaponHash, bool equipNow)l
extern _native bool GET_CURRENT_PED_WEAPON(Ped ped, Hash* weaponHash, bool p2)l
extern _native Entity GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Ped ped)l
extern _native Hash GET_BEST_PED_WEAPON(Ped ped, bool p1)l
extern _native bool SET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash weaponHash)l
extern _native bool GET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash* weaponHash)l
extern _native bool IS_PED_ARMED(Ped ped, int p1)l
extern _native bool IS_WEAPON_VALID(Hash weaponHash)l
extern _native bool HAS_PED_GOT_WEAPON(Ped ped, Hash weaponHash, bool p2)l
extern _native bool IS_PED_WEAPON_READY_TO_SHOOT(Ped ped)l
extern _native Hash GET_PED_WEAPONTYPE_IN_SLOT(Ped ped, Hash weaponSlot)l
extern _native int GET_AMMO_IN_PED_WEAPON(Ped ped, Hash weaponhash)l
extern _native void ADD_AMMO_TO_PED(Ped ped, Hash weaponHash, int ammo)l
extern _native void SET_PED_AMMO(Ped ped, Hash weaponHash, int ammo)l
extern _native void SET_PED_INFINITE_AMMO(Ped ped, bool toggle, Hash weaponHash)l
extern _native void SET_PED_INFINITE_AMMO_CLIP(Ped ped, bool toggle)l
extern _native void GIVE_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool isHidden, bool equipNow)l
extern _native void GIVE_DELAYED_WEAPON_TO_PED(Ped ped, Hash weaponHash, int time, bool equipNow)l
extern _native void REMOVE_ALL_PED_WEAPONS(Ped ped, bool p1)l
extern _native void REMOVE_WEAPON_FROM_PED(Ped ped, Hash weaponHash)l
extern _native void HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(Ped ped, bool toggle)l
extern _native void SET_PED_CURRENT_WEAPON_VISIBLE(Ped ped, bool visible, bool deselectWeapon, bool p3, bool p4)l
extern _native void SET_PED_DROPS_WEAPONS_WHEN_DEAD(Ped ped, bool toggle)l
extern _native bool HAS_PED_BEEN_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash, int weaponType)l
extern _native void CLEAR_PED_LAST_WEAPON_DAMAGE(Ped ped)l
extern _native bool HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(Entity entity, Hash weaponHash, int weaponType)l
extern _native void CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Entity entity)l
extern _native void SET_PED_DROPS_WEAPON(Ped ped)l
extern _native void SET_PED_DROPS_INVENTORY_WEAPON(Ped ped, Hash weaponHash, vector3 Offset, any p5)l
extern _native int GET_MAX_AMMO_IN_CLIP(Ped ped, Hash weaponHash, bool p2)l
extern _native bool GET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int* ammo)l
extern _native bool SET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int ammo)l
extern _native bool GET_MAX_AMMO(Ped ped, Hash weaponHash, int* ammo)l
extern _native void SET_PED_AMMO_BY_TYPE(Ped ped, any ammoType, int ammo)l
extern _native int GET_PED_AMMO_BY_TYPE(Ped ped, any ammoType)l
extern _native void SET_PED_AMMO_TO_DROP(any p0, any p1)l
extern _native void UNK_0xD6460EA2(float p0)l
extern _native Hash GET_PED_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash)l
extern _native bool GET_PED_LAST_WEAPON_IMPACT_COORD(Ped ped, vector3* coords)l
extern _native void SET_PED_GADGET(Ped ped, Hash gadgetHash, bool p2)l
extern _native bool GET_IS_PED_GADGET_EQUIPPED(Ped ped, Hash gadgetHash)l
extern _native Hash GET_SELECTED_PED_WEAPON(Ped ped)l
extern _native void EXPLODE_PROJECTILES(Ped ped, Hash weaponHash, bool p2)l
extern _native void REMOVE_ALL_PROJECTILES_OF_TYPE(Hash weaponHash, bool p1)l
extern _native32(0x3612110D) float _GET_LOCKON_RANGE_OF_CURRENT_PED_WEAPON(Ped ped)l
extern _native float GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(Ped ped)l
extern _native bool HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Ped driver, Vehicle vehicle, Hash weaponHash, any p3)l
extern _native void GIVE_WEAPON_COMPONENT_TO_PED(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native void REMOVE_WEAPON_COMPONENT_FROM_PED(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native bool HAS_PED_GOT_WEAPON_COMPONENT(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native bool IS_PED_WEAPON_COMPONENT_ACTIVE(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native32(0x82EEAF0F) bool _PED_SKIP_NEXT_RELOADING(Ped ped)l
extern _native bool MAKE_PED_RELOAD(Ped ped)l
extern _native void REQUEST_WEAPON_ASSET(Hash weaponHash, int p1, int p2)l
extern _native bool HAS_WEAPON_ASSET_LOADED(Hash weaponHash)l
extern _native void REMOVE_WEAPON_ASSET(Hash weaponHash)l
extern _native Object CREATE_WEAPON_OBJECT(Hash weaponHash, int ammoCount, vector3 vec, bool showWorldModel, float heading, any p7)l
extern _native void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Object weaponObject, Hash addonHash)l
extern _native void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(any p0, any p1)l
extern _native bool HAS_WEAPON_GOT_WEAPON_COMPONENT(Object weapon, Hash addonHash)l
extern _native void GIVE_WEAPON_OBJECT_TO_PED(Object weaponObject, Ped ped)l
extern _native bool DOES_WEAPON_TAKE_WEAPON_COMPONENT(Hash weaponHash, Hash componentHash)l
extern _native Object GET_WEAPON_OBJECT_FROM_PED(Ped ped, bool p1)l
extern _native void SET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash, int tintIndex)l
extern _native int GET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash)l
extern _native void SET_WEAPON_OBJECT_TINT_INDEX(Object weapon, int tintIndex)l
extern _native int GET_WEAPON_OBJECT_TINT_INDEX(Object weapon)l
extern _native int GET_WEAPON_TINT_COUNT(Hash weaponHash)l
extern _native bool GET_WEAPON_HUD_STATS(Hash weaponHash, int* outData)l
extern _native bool GET_WEAPON_COMPONENT_HUD_STATS(Hash componentHash, int* outData)l
extern _native int GET_WEAPON_CLIP_SIZE(Hash weaponHash)l
extern _native void SET_PED_CHANCE_OF_FIRING_BLANKS(Ped ped, vector2 Bias)l
extern _native Entity UNK_0xEC2E5304(Ped ped, float p1)l
extern _native void REQUEST_WEAPON_HIGH_DETAIL_MODEL(Entity weaponObject)l
extern _native bool IS_PED_CURRENT_WEAPON_SILENCED(Ped ped)l
extern _native bool SET_WEAPON_SMOKEGRENADE_ASSIGNED(Ped ped)l
extern _native any SET_FLASH_LIGHT_FADE_DISTANCE(float distance)l
extern _native void SET_WEAPON_ANIMATION_OVERRIDE(Ped ped, Hash animStyle)l
extern _native int GET_WEAPON_DAMAGE_TYPE(Hash weaponHash)l
extern _native void UNK_0x64646F1D(Ped ped)l
extern _native bool CAN_USE_WEAPON_ON_PARACHUTE(Hash weaponHash)l
#pragma endregion //}
#pragma region ITEMSET //{
extern _native any CREATE_ITEMSET(bool p0)l
extern _native void DESTROY_ITEMSET(any p0)l
extern _native bool IS_ITEMSET_VALID(any p0)l
extern _native bool ADD_TO_ITEMSET(any p0, any p1)l
extern _native void REMOVE_FROM_ITEMSET(any p0, any p1)l
extern _native any GET_ITEMSET_SIZE(any p0)l
extern _native any GET_INDEXED_ITEM_IN_ITEMSET(any p0, any p1)l
extern _native bool IS_IN_ITEMSET(any p0, any p1)l
extern _native void CLEAN_ITEMSET(any p0)l
#pragma endregion //}
#pragma region STREAMING //{
extern _native void LOAD_ALL_OBJECTS_NOW()l
extern _native void LOAD_SCENE(vector3 vec)l
extern _native any NETWORK_UPDATE_LOAD_SCENE()l
extern _native void NETWORK_STOP_LOAD_SCENE()l
extern _native bool IS_NETWORK_LOADING_SCENE()l
extern _native void SET_INTERIOR_ACTIVE(int interiorID, bool toggle)l
extern _native void REQUEST_MODEL(Hash model)l
extern _native void REQUEST_MENU_PED_MODEL(Hash model)l
extern _native bool HAS_MODEL_LOADED(Hash model)l
extern _native void UNK_0x939243FB(int interiorID, const char* roomName)l
extern _native void SET_MODEL_AS_NO_LONGER_NEEDED(Hash model)l
extern _native bool IS_MODEL_IN_CDIMAGE(Hash model)l
extern _native bool IS_MODEL_VALID(Hash model)l
extern _native bool IS_MODEL_A_VEHICLE(Hash model)l
extern _native any REQUEST_COLLISION_AT_COORD(vector3 vec)l
extern _native void REQUEST_COLLISION_FOR_MODEL(Hash model)l
extern _native bool HAS_COLLISION_FOR_MODEL_LOADED(Hash model)l
extern _native void REQUEST_ADDITIONAL_COLLISION_AT_COORD(float p0, float p1, float p2)l
extern _native bool DOES_ANIM_DICT_EXIST(const char* animDict)l
extern _native void REQUEST_ANIM_DICT(const char* animDict)l
extern _native bool HAS_ANIM_DICT_LOADED(const char* animDict)l
extern _native void REMOVE_ANIM_DICT(const char* animDict)l
extern _native void REQUEST_ANIM_SET(const char* animSet)l
extern _native bool HAS_ANIM_SET_LOADED(const char* animSet)l
extern _native void REMOVE_ANIM_SET(const char* animSet)l
extern _native void REQUEST_CLIP_SET(const char* clipSet)l
extern _native bool HAS_CLIP_SET_LOADED(const char* clipSet)l
extern _native void REMOVE_CLIP_SET(const char* clipSet)l
extern _native void REQUEST_IPL(const char* iplName)l
extern _native void REMOVE_IPL(const char* iplName)l
extern _native bool IS_IPL_ACTIVE(const char* iplName)l
extern _native void SET_STREAMING(bool toggle)l
extern _native void SET_GAME_PAUSES_FOR_STREAMING(bool toggle)l
extern _native void SET_REDUCE_PED_MODEL_BUDGET(bool toggle)l
extern _native void SET_REDUCE_VEHICLE_MODEL_BUDGET(bool toggle)l
extern _native void SET_DITCH_POLICE_MODELS(bool toggle)l
extern _native int GET_NUMBER_OF_STREAMING_REQUESTS()l
extern _native any REQUEST_PTFX_ASSET()l
extern _native bool HAS_PTFX_ASSET_LOADED()l
extern _native void REMOVE_PTFX_ASSET()l
extern _native void REQUEST_NAMED_PTFX_ASSET(const char* fxName)l
extern _native bool HAS_NAMED_PTFX_ASSET_LOADED(const char* fxName)l
extern _native void SET_VEHICLE_POPULATION_BUDGET(int p0)l
extern _native void SET_PED_POPULATION_BUDGET(int p0)l
extern _native void CLEAR_FOCUS()l
extern _native32(0x14680A60) void _SET_FOCUS_AREA(vector3 vec, vector3 offset)l
extern _native void SET_FOCUS_ENTITY(Entity entity)l
extern _native bool IS_ENTITY_FOCUS(Entity entity)l
extern _native void UNK_0x403CD434(const char* p0, bool p1)l
extern _native void UNK_0xA07BAEB9(any p0)l
extern _native any FORMAT_FOCUS_HEADING(vector3 vec, float rad, any p4, any p5)l
extern _native any UNK_0x72344191(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7, any p8)l
extern _native any UNK_0xC0157255(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native void UNK_0xE80F8ABE(any p0)l
extern _native any UNK_0x1B3521F4(any p0)l
extern _native any UNK_0x42CFE9C0(any p0)l
extern _native any UNK_0x56253356()l
extern _native bool NEW_LOAD_SCENE_START(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7)l
extern _native bool NEW_LOAD_SCENE_START_SPHERE(float p0, float p1, float p2, float p3, any p4)l
extern _native void NEW_LOAD_SCENE_STOP()l
extern _native bool IS_NEW_LOAD_SCENE_ACTIVE()l
extern _native bool IS_NEW_LOAD_SCENE_LOADED()l
extern _native any UNK_0xEAA51103()l
extern _native void START_PLAYER_SWITCH(Ped from, Ped to, int flags, int switchType)l
extern _native void STOP_PLAYER_SWITCH()l
extern _native bool IS_PLAYER_SWITCH_IN_PROGRESS()l
extern _native int GET_PLAYER_SWITCH_TYPE()l
extern _native int GET_IDEAL_PLAYER_SWITCH_TYPE(vector3 vec_1, vector3 vec_2)l
extern _native int GET_PLAYER_SWITCH_STATE()l
extern _native int GET_PLAYER_SHORT_SWITCH_STATE()l
extern _native void UNK_0xF0BD420D(int p0)l
extern _native any UNK_0x02BA7AC2()l
extern _native void SET_PLAYER_SWITCH_OUTRO(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8)l
extern _native void UNK_0x279077B0(any* p0)l
extern _native void UNK_0x55CB21F9()l
extern _native void UNK_0x1084F2F4()l
extern _native void UNK_0x5B1E995D()l
extern _native void UNK_0x4B4B9A13()l
extern _native any UNK_0x408F7148()l
extern _native32(0xFB4D062D) void _SWITCH_OUT_PLAYER(Ped ped, int flags, int unknown)l
extern _native void UNK_0x2349373B(any p0)l
extern _native any UNK_0x74C16879()l
extern _native int SET_PLAYER_INVERTED_UP()l
extern _native any UNK_0xC7A3D279()l
extern _native any DESTROY_PLAYER_IN_PAUSE_MENU()l
extern _native any UNK_0x7154B6FD()l
extern _native void UNK_0xE5612C1A(float p0)l
extern _native void UNK_0x9CD6A451(float p0, float p1, float p2, float p3)l
extern _native void UNK_0x4267DA87()l
extern _native void UNK_0x9FA4AF99(bool p0)l
extern _native void UNK_0x9EF0A9CF(any* p0, any* p1)l
extern _native void UNK_0xF2CDD6A8()l
extern _native any UNK_0x17B0A1CD()l
extern _native void UNK_0x3DA7AA5D()l
extern _native any UNK_0xDAB4BAC0()l
extern _native void PREFETCH_SRL(const char* srl)l
extern _native bool IS_SRL_LOADED()l
extern _native void BEGIN_SRL()l
extern _native void END_SRL()l
extern _native void SET_SRL_TIME(float p0)l
extern _native void UNK_0x814D0752(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void UNK_0x62F02485(any p0, any p1, any p2, any p3)l
extern _native void UNK_0xA6459CAA(bool p0)l
extern _native void UNK_0xF8F515E4(any p0)l
extern _native void SET_HD_AREA(vector3 vec, float ground)l
extern _native void CLEAR_HD_AREA()l
extern _native void UNK_0xE243B2AF()l
extern _native void SHUTDOWN_CREATOR_BUDGET()l
extern _native bool UNK_0xC0E83320(Hash modelHash)l
extern _native void UNK_0x1C576388(any p0)l
extern _native any UNK_0x3E9C4CBE()l
#pragma endregion //}
#pragma region SCRIPT //{
extern _native void REQUEST_SCRIPT(const char* scriptName)l
extern _native void SET_SCRIPT_AS_NO_LONGER_NEEDED(const char* scriptName)l
extern _native bool HAS_SCRIPT_LOADED(const char* scriptName)l
extern _native bool DOES_SCRIPT_EXIST(const char* scriptName)l
extern _native void REQUEST_SCRIPT_WITH_NAME_HASH(Hash scriptHash)l
extern _native void SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(Hash scriptHash)l
extern _native bool HAS_SCRIPT_WITH_NAME_HASH_LOADED(Hash scriptHash)l
extern _native void TERMINATE_THREAD(int threadId)l
extern _native bool IS_THREAD_ACTIVE(int threadId)l
extern _native32(0xBE7ACD89) const char* _GET_NAME_OF_THREAD(int threadId)l
extern _native32(0xBB4E2F66) void _BEGIN_ENUMERATING_THREADS()l
extern _native32(0x1E28B28F) int _GET_ID_OF_NEXT_THREAD_IN_ENUMERATION()l
extern _native int GET_ID_OF_THIS_THREAD()l
extern _native void TERMINATE_THIS_THREAD()l
extern _native32(0x029D3841) int _GET_NUMBER_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH(Hash scriptHash)l
extern _native const char* GET_THIS_SCRIPT_NAME()l
extern _native Hash GET_HASH_OF_THIS_SCRIPT_NAME()l
extern _native int GET_NUMBER_OF_EVENTS(bool p0)l
extern _native bool GET_EVENT_EXISTS(bool p0, int p1)l
extern _native int GET_EVENT_AT_INDEX(bool p0, int p1)l
extern _native bool GET_EVENT_DATA(bool p0, int p1, int* p2, int p3)l
extern _native void SHUTDOWN_LOADING_SCREEN()l
extern _native void SET_NO_LOADING_SCREEN(bool toggle)l
extern _native void UNK_0xB03BCCDF()l
#pragma endregion //}
#pragma region UI //{
extern _native32(0xCB7C8994) void _SET_LOADING_PROMPT_TEXT_ENTRY(const char* string)l
extern _native32(0x903F5EE4) void _SHOW_LOADING_PROMPT(int busySpinnerType)l
extern _native32(0x94119534) void _REMOVE_LOADING_PROMPT()l
extern _native void UNK_0x71077FBD()l
extern _native32(0xB8B3A5D0) bool _IS_LOADING_PROMPT_BEING_DISPLAYED()l
extern _native void UNK_0xA7C8594B(bool p0)l
extern _native void UNK_0x1DA7E41A(float p0)l
extern _native void UNK_0x1E63088A()l
extern _native void UNK_0x5205C6F5()l
extern _native32(0xECA8ACB9) void _REMOVE_NOTIFICATION(int notificationId)l
extern _native void UNK_0x520FCB6D()l
extern _native void UNK_0xC8BAB2F2()l
extern _native void UNK_0x4D0449C6()l
extern _native void UNK_0xD3F40140()l
extern _native any UNK_0xC5223796()l
extern _native void UNK_0x709B4BCB()l
extern _native void UNK_0x4A4A40A4()l
extern _native32(0x294405D4) int _GET_CURRENT_NOTIFICATION()l
extern _native void UNK_0xF881AB87()l
extern _native void UNK_0x1D6859CA()l
extern _native32(0xCF14D7F2) void _SET_NOTIFICATION_FLASH_COLOR(RGBA colour)l
extern _native void UNK_0x24A97AF8(any p0)l
extern _native void UNK_0x44018EDB(bool p0)l
extern _native void UNK_0xA4524B23()l
extern _native void UNK_0xAFA1148B()l
extern _native void UNK_0x3CD4307C()l
extern _native32(0x574EE85C) void _SET_NOTIFICATION_TEXT_ENTRY(const char* type)l
extern _native32(0xED130FA1) int _SET_NOTIFICATION_MESSAGE_2(const char* p0, int p1, int p2, int p3, bool p4, const char* picName1, const char* picName2)l
extern _native32(0xE7E3C98B) int _SET_NOTIFICATION_MESSAGE(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject)l
extern _native32(0x0EB382B7) int _SET_NOTIFICATION_MESSAGE_4(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration)l
extern _native32(0x3E807FE3) int _SET_NOTIFICATION_MESSAGE_CLAN_TAG(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration, const char* clanTag)l
extern _native32(0xDEB491C8) int _SET_NOTIFICATION_MESSAGE_CLAN_TAG_2(const char* picName1, const char* picName2, bool flash, int iconType1, const char* sender, const char* subject, float duration, const char* clanTag, int iconType2, int p9)l
extern _native32(0x08F7AF78) int _DRAW_NOTIFICATION(bool blink, bool p1)l
extern _native32(0x57B8D0D4) int _DRAW_NOTIFICATION_2(bool blink, bool p1)l
extern _native32(0x02BCAF9B) int _DRAW_NOTIFICATION_3(bool blink, bool p1)l
extern _native32(0x02DED2B8) int _DRAW_NOTIFICATION_ICON(const char* p0, const char* p1, int p2, int p3, const char* p4)l
extern _native32(0xA9CCEF66) int _NOTIFICATION_SEND_APARTMENT_INVITE(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, RGB colour)l
extern _native32(0x88B9B909) int _NOTIFICATION_SEND_CLAN_INVITE(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, const char* playerName, RGB colour)l
extern _native any UNK_0xE05E7052(any p0, any p1, any p2)l
extern _native any UNK_0x4FA43BA4(any p0, any p1, any p2, any p3)l
extern _native any UNK_0x8C90D22F(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native32(0x8E319AB8) int _DRAW_NOTIFICATION_4(bool blink, bool p1)l
extern _native any UNK_0x5E93FBFA(any* p0, any* p1, any p2, any* p3, any* p4, any p5)l
extern _native void BEGIN_TEXT_COMMAND_PRINT(const char* GxtEntry)l
extern _native void END_TEXT_COMMAND_PRINT(int duration, bool drawImmediately)l
extern _native void BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(const char* text)l
extern _native bool END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED()l
extern _native void BEGIN_TEXT_COMMAND_DISPLAY_TEXT(const char* text)l
extern _native void END_TEXT_COMMAND_DISPLAY_TEXT(vector2 vector)l
extern _native32(0x51E7A037) void _BEGIN_TEXT_COMMAND_WIDTH(const char* text)l
extern _native32(0xD12A643A) float _END_TEXT_COMMAND_GET_WIDTH(int font)l
extern _native32(0x94B82066) void _BEGIN_TEXT_COMMAND_LINE_COUNT(const char* entry)l
extern _native32(0xAA318785) int _END_TEXT_COMMAND_GET_LINE_COUNT(vector2 vector)l
extern _native void BEGIN_TEXT_COMMAND_DISPLAY_HELP(const char* inputType)l
extern _native void END_TEXT_COMMAND_DISPLAY_HELP(any p0, bool loop, bool beep, int shape)l
extern _native void BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(const char* labelName)l
extern _native bool END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(int p0)l
extern _native void BEGIN_TEXT_COMMAND_SET_BLIP_NAME(const char* gxtentry)l
extern _native void END_TEXT_COMMAND_SET_BLIP_NAME(Blip blip)l
extern _native32(0x0E103475) void _BEGIN_TEXT_COMMAND_OBJECTIVE(const char* p0)l
extern _native32(0x2944A6C5) void _END_TEXT_COMMAND_OBJECTIVE(bool p0)l
extern _native void BEGIN_TEXT_COMMAND_CLEAR_PRINT(const char* text)l
extern _native void END_TEXT_COMMAND_CLEAR_PRINT()l
extern _native32(0xBF855650) void _BEGIN_TEXT_COMMAND_TIMER(const char* p0)l
extern _native32(0x6E7FDA1C) void _END_TEXT_COMMAND_TIMER(bool p0)l
extern _native void ADD_TEXT_COMPONENT_INTEGER(int value)l
extern _native void ADD_TEXT_COMPONENT_FLOAT(float value, int decimalPlaces)l
extern _native void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(const char* labelName)l
extern _native void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(Hash gxtEntryHash)l
extern _native void ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(Blip blip)l
extern _native void ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const char* text)l
extern _native void ADD_TEXT_COMPONENT_SUBSTRING_TIME(int timestamp, int flags)l
extern _native void ADD_TEXT_COMPONENT_FORMATTED_INTEGER(int value, bool commaSeparated)l
extern _native32(0x65E1D404) void _ADD_TEXT_COMPONENT_APP_TITLE(const char* p0, int p1)l
extern _native void ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(const char* website)l
extern _native32(0x0829A799) void _ADD_TEXT_COMPONENT_SCALEFORM(const char* p0)l
extern _native32(0x6F1A1901) void _SET_NOTIFICATION_COLOR_NEXT(int p0)l
extern _native32(0x34A396EE) const char* _GET_TEXT_SUBSTRING(const char* text, int position, int length)l
extern _native32(0x0183A66C) const char* _GET_TEXT_SUBSTRING_SAFE(const char* text, int position, int length, int maxLength)l
extern _native32(0xFA6373BB) const char* _GET_TEXT_SUBSTRING_SLICE(const char* text, int startPosition, int endPosition)l
extern _native32(0x95C4B5AD) const char* _GET_LABEL_TEXT(const char* labelName)l
extern _native void CLEAR_PRINTS()l
extern _native void CLEAR_BRIEF()l
extern _native void CLEAR_ALL_HELP_MESSAGES()l
extern _native void CLEAR_THIS_PRINT(const char* p0)l
extern _native void CLEAR_SMALL_PRINTS()l
extern _native bool DOES_TEXT_BLOCK_EXIST(const char* gxt)l
extern _native void REQUEST_ADDITIONAL_TEXT(const char* gxt, int slot)l
extern _native32(0xF4D27EBE) void _REQUEST_ADDITIONAL_TEXT_2(const char* gxt, int slot)l
extern _native bool HAS_ADDITIONAL_TEXT_LOADED(int slot)l
extern _native void CLEAR_ADDITIONAL_TEXT(int p0, bool p1)l
extern _native bool IS_STREAMING_ADDITIONAL_TEXT(int p0)l
extern _native bool HAS_THIS_ADDITIONAL_TEXT_LOADED(const char* gxt, int slot)l
extern _native bool IS_MESSAGE_BEING_DISPLAYED()l
extern _native bool DOES_TEXT_LABEL_EXIST(const char* gxt)l
extern _native int GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(const char* gxt)l
extern _native int GET_LENGTH_OF_LITERAL_STRING(const char* string)l
extern _native32(0x7DBC0764) int _GET_LENGTH_OF_STRING(const char* p0)l
extern _native const char* GET_STREET_NAME_FROM_HASH_KEY(Hash hash)l
extern _native bool IS_HUD_PREFERENCE_SWITCHED_ON()l
extern _native bool IS_RADAR_PREFERENCE_SWITCHED_ON()l
extern _native bool IS_SUBTITLE_PREFERENCE_SWITCHED_ON()l
extern _native void DISPLAY_HUD(bool toggle)l
extern _native void UNK_0xC380AC85()l
extern _native void UNK_0xC47AB1B0()l
extern _native any DISPLAY_RADAR(bool Toggle)l
extern _native bool IS_HUD_HIDDEN()l
extern _native bool IS_RADAR_HIDDEN()l
extern _native void SET_BLIP_ROUTE(Blip blip, bool enabled)l
extern _native void SET_BLIP_ROUTE_COLOUR(Blip blip, int colour)l
extern _native void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(bool p0)l
extern _native void UNK_0x9854485F(bool p0)l
extern _native void RESPONDING_AS_TEMP(float p0)l
extern _native void SET_RADAR_ZOOM(int zoomLevel)l
extern _native void UNK_0x25EC28C0(any p0, float p1)l
extern _native32(0x09CF1CE5) void _SET_RADAR_ZOOM_LEVEL_THIS_FRAME(float zoomLevel)l
extern _native void UNK_0xE8D3A910()l
extern _native void GET_HUD_COLOUR(int hudColorIndex, int* r, int* g, int* b, int* a)l
extern _native void UNK_0x0E41E45C(RGBA colour)l
extern _native void UNK_0x6BE3ACA8(RGBA colour)l
extern _native32(0x3B216749) void _SET_HUD_COLOURS_SWITCH(int hudColorIndex, int hudColorIndex2)l
extern _native32(0xF6E7E92B) void _SET_HUD_COLOUR(int hudColorIndex, RGBA colour)l
extern _native void FLASH_ABILITY_BAR(bool toggle)l
extern _native void SET_ABILITY_BAR_VALUE(float p0, float p1)l
extern _native any FLASH_WANTED_DISPLAY(bool p0)l
extern _native32(0x3330175B) float _GET_TEXT_SCALE_HEIGHT(float size, int font)l
extern _native void SET_TEXT_SCALE(float p0, float size)l
extern _native void SET_TEXT_COLOUR(RGBA colour)l
extern _native void SET_TEXT_CENTRE(bool align)l
extern _native void SET_TEXT_RIGHT_JUSTIFY(bool toggle)l
extern _native void SET_TEXT_JUSTIFICATION(int justifyType)l
extern _native void SET_TEXT_WRAP(float start, float end)l
extern _native void SET_TEXT_LEADING(bool p0)l
extern _native void SET_TEXT_PROPORTIONAL(bool p0)l
extern _native void SET_TEXT_FONT(int fontType)l
extern _native void SET_TEXT_DROP_SHADOW()l
extern _native void SET_TEXT_DROPSHADOW(int distance, RGBA colour)l
extern _native void SET_TEXT_OUTLINE()l
extern _native void SET_TEXT_EDGE(int p0, RGBA colour)l
extern _native void SET_TEXT_RENDER_ID(int renderId)l
extern _native int GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID()l
extern _native bool REGISTER_NAMED_RENDERTARGET(const char* p0, bool p1)l
extern _native bool IS_NAMED_RENDERTARGET_REGISTERED(const char* p0)l
extern _native bool RELEASE_NAMED_RENDERTARGET(any* p0)l
extern _native void LINK_NAMED_RENDERTARGET(Hash hash)l
extern _native any GET_NAMED_RENDERTARGET_RENDER_ID(const char* p0)l
extern _native bool IS_NAMED_RENDERTARGET_LINKED(Hash hash)l
extern _native void CLEAR_HELP(bool toggle)l
extern _native bool IS_HELP_MESSAGE_ON_SCREEN()l
extern _native bool UNK_0x812CBE0E()l
extern _native bool IS_HELP_MESSAGE_BEING_DISPLAYED()l
extern _native bool IS_HELP_MESSAGE_FADING_OUT()l
extern _native bool UNK_0x87871CE0()l
extern _native32(0xB9827942) int _GET_BLIP_INFO_ID_ITERATOR()l
extern _native int GET_NUMBER_OF_ACTIVE_BLIPS()l
extern _native Blip GET_NEXT_BLIP_INFO_ID(int blipSprite)l
extern _native Blip GET_FIRST_BLIP_INFO_ID(int blipSprite)l
extern _native vector3 GET_BLIP_INFO_ID_COORD(Blip blip)l
extern _native int GET_BLIP_INFO_ID_DISPLAY(Blip blip)l
extern _native int GET_BLIP_INFO_ID_TYPE(Blip blip)l
extern _native Entity GET_BLIP_INFO_ID_ENTITY_INDEX(Blip blip)l
extern _native Pickup GET_BLIP_INFO_ID_PICKUP_INDEX(Blip blip)l
extern _native Blip GET_BLIP_FROM_ENTITY(Entity entity)l
extern _native Blip ADD_BLIP_FOR_RADIUS(vector3 pos, float radius)l
extern _native Blip ADD_BLIP_FOR_ENTITY(Entity entity)l
extern _native Blip ADD_BLIP_FOR_PICKUP(Pickup pickup)l
extern _native Blip ADD_BLIP_FOR_COORD(vector3 vec)l
extern _native void UNK_0xBF25E7B2(vector3 pos, float radius, int p4)l
extern _native void UNK_0xE7E1E32B(bool p0)l
extern _native void SET_BLIP_COORDS(Blip blip, vector3 pos)l
extern _native vector3 GET_BLIP_COORDS(Blip blip)l
extern _native void SET_BLIP_SPRITE(Blip blip, int spriteId)l
extern _native int GET_BLIP_SPRITE(Blip blip)l
extern _native void SET_BLIP_NAME_FROM_TEXT_FILE(Blip blip, const char* gxtEntry)l
extern _native void SET_BLIP_NAME_TO_PLAYER_NAME(Blip blip, Player player)l
extern _native void SET_BLIP_ALPHA(Blip blip, int alpha)l
extern _native int GET_BLIP_ALPHA(Blip blip)l
extern _native void SET_BLIP_FADE(Blip blip, int opacity, int duration)l
extern _native void SET_BLIP_ROTATION(Blip blip, int rotation)l
extern _native void SET_BLIP_FLASH_TIMER(Blip blip, int duration)l
extern _native void SET_BLIP_FLASH_INTERVAL(Blip blip, any p1)l
extern _native void SET_BLIP_COLOUR(Blip blip, int color)l
extern _native void SET_BLIP_SECONDARY_COLOUR(Blip blip, FloatRGB colour)l
extern _native int GET_BLIP_COLOUR(Blip blip)l
extern _native int GET_BLIP_HUD_COLOUR(Blip blip)l
extern _native bool IS_BLIP_SHORT_RANGE(Blip blip)l
extern _native bool IS_BLIP_ON_MINIMAP(Blip blip)l
extern _native bool UNK_0x3E47F357(any p0)l
extern _native void UNK_0x43996428(any p0, bool p1)l
extern _native void SET_BLIP_HIGH_DETAIL(Blip blip, bool toggle)l
extern _native void SET_BLIP_AS_MISSION_CREATOR_BLIP(Blip blip, bool toggle)l
extern _native bool IS_MISSION_CREATOR_BLIP(Blip blip)l
extern _native Blip DISABLE_BLIP_NAME_FOR_VAR()l
extern _native bool UNK_0xC5EB849A()l
extern _native void UNK_0xA2CAAB4F(bool p0)l
extern _native void SET_BLIP_FLASHES(Blip blip, bool toggle)l
extern _native void SET_BLIP_FLASHES_ALTERNATE(Blip blip, bool toggle)l
extern _native bool IS_BLIP_FLASHING(Blip blip)l
extern _native void SET_BLIP_AS_SHORT_RANGE(Blip blip, bool toggle)l
extern _native void SET_BLIP_SCALE(Blip blip, float scale)l
extern _native void SET_BLIP_PRIORITY(Blip blip, int priority)l
extern _native void SET_BLIP_DISPLAY(Blip blip, int displayId)l
extern _native void SET_BLIP_CATEGORY(Blip blip, int index)l
extern _native void REMOVE_BLIP(Blip* blip)l
extern _native void SET_BLIP_AS_FRIENDLY(Blip blip, bool toggle)l
extern _native void PULSE_BLIP(Blip blip)l
extern _native void SHOW_NUMBER_ON_BLIP(Blip blip, int number)l
extern _native void HIDE_NUMBER_ON_BLIP(Blip blip)l
extern _native void UNK_0x1D99F676(any p0, bool p1)l
extern _native32(0x3DCF0092) void _SET_BLIP_CHECKED(Blip blip, bool toggle)l
extern _native void SHOW_HEADING_INDICATOR_ON_BLIP(Blip blip, bool toggle)l
extern _native32(0x8DE82C15) void _SET_BLIP_FRIENDLY(Blip blip, bool toggle)l
extern _native32(0x4C8F02B4) void _SET_BLIP_FRIEND(Blip blip, bool toggle)l
extern _native void UNK_0xABBE1E45(any p0, bool p1)l
extern _native void UNK_0x6AA6A1CC(any p0, bool p1)l
extern _native32(0xC575F0BC) void _SET_BLIP_SHRINK(Blip blip, bool toggle)l
extern _native void UNK_0x40E25DB8(any p0, bool p1)l
extern _native bool DOES_BLIP_EXIST(Blip blip)l
extern _native void SET_WAYPOINT_OFF()l
extern _native void UNK_0x62BABF2C()l
extern _native void REFRESH_WAYPOINT()l
extern _native bool IS_WAYPOINT_ACTIVE()l
extern _native void SET_NEW_WAYPOINT(vector2 vector)l
extern _native void SET_BLIP_BRIGHT(Blip blip, bool toggle)l
extern _native void SET_BLIP_SHOW_CONE(Blip blip, bool toggle)l
extern _native void UNK_0x41B0D022(Ped ped)l
extern _native any SET_MINIMAP_COMPONENT(int p0, bool p1, int p2)l
extern _native Blip GET_MAIN_PLAYER_BLIP_ID()l
extern _native void HIDE_LOADING_ON_FADE_THIS_FRAME()l
extern _native void SET_RADAR_AS_INTERIOR_THIS_FRAME(Hash interior, vector2 vector, int z, int zoom)l
extern _native void SET_RADAR_AS_EXTERIOR_THIS_FRAME()l
extern _native32(0x54E75C7D) void _SET_PLAYER_BLIP_POSITION_THIS_FRAME(vector2 vector)l
extern _native any UNK_0x199DED14()l
extern _native32(0x1A4318F7) void _DISABLE_RADAR_THIS_FRAME()l
extern _native void UNK_0xCE36E3FE()l
extern _native32(0x334EFD46) void _CENTER_PLAYER_ON_RADAR_THIS_FRAME()l
extern _native void SET_WIDESCREEN_FORMAT(any p0)l
extern _native void DISPLAY_AREA_NAME(bool toggle)l
extern _native void DISPLAY_CASH(bool toggle)l
extern _native void DISPLAY_AMMO_THIS_FRAME(bool display)l
extern _native void DISPLAY_SNIPER_SCOPE_THIS_FRAME()l
extern _native void HIDE_HUD_AND_RADAR_THIS_FRAME()l
extern _native void UNK_0x5476B9FD(bool p0)l
extern _native void UNK_0xF4F3C796()l
extern _native void UNK_0x7BFFE82F()l
extern _native void SET_MULTIPLAYER_BANK_CASH()l
extern _native void REMOVE_MULTIPLAYER_BANK_CASH()l
extern _native void SET_MULTIPLAYER_HUD_CASH(int p0, int p1)l
extern _native void REMOVE_MULTIPLAYER_HUD_CASH()l
extern _native void HIDE_HELP_TEXT_THIS_FRAME()l
extern _native void DISPLAY_HELP_TEXT_THIS_FRAME(const char* message, bool p1)l
extern _native32(0x1EFFB02A) void _SHOW_WEAPON_WHEEL(bool forcedShow)l
extern _native void UNK_0xB26FED2B()l
extern _native Hash UNK_0x22E9F555()l
extern _native void UNK_0x83B608A0(Hash weaponHash)l
extern _native void UNK_0xE70D1F43(bool p0)l
extern _native void SET_GPS_FLAGS(int p0, float p1)l
extern _native void CLEAR_GPS_FLAGS()l
extern _native void UNK_0xFB9BABF5(bool p0)l
extern _native void CLEAR_GPS_RACE_TRACK()l
extern _native void UNK_0x7F93799B(any p0, bool p1, bool p2)l
extern _native void UNK_0xEEBDFE55(any p0, any p1, any p2)l
extern _native void UNK_0xDA0AF00E(bool p0, any p1, any p2)l
extern _native void UNK_0xCF2E3E24()l
extern _native void UNK_0xC3DCBEDB(any p0, bool p1, bool p2)l
extern _native void UNK_0xFE485135(vector3 vec)l
extern _native void UNK_0xE87CBE4C(bool p0)l
extern _native void UNK_0x0D9969E4()l
extern _native void CLEAR_GPS_PLAYER_WAYPOINT()l
extern _native void SET_GPS_FLASHES(bool toggle)l
extern _native void FLASH_MINIMAP_DISPLAY()l
extern _native void UNK_0x79A6CAF6(any p0)l
extern _native void TOGGLE_STEALTH_RADAR(bool toggle)l
extern _native void KEY_HUD_COLOUR(bool p0, any p1)l
extern _native void SET_MISSION_NAME(bool p0, const char* name)l
extern _native void UNK_0x8D9A1734(bool p0, any* p1)l
extern _native void UNK_0xD2161E77(bool p0, any* p1, any* p2, any* p3, any* p4, any* p5, any* p6, any* p7, any* p8)l
extern _native void SET_MINIMAP_BLOCK_WAYPOINT(bool toggle)l
extern _native32(0x02F5F1D1) void _SET_NORTH_YANKTON_MAP(bool toggle)l
extern _native32(0xD8D77733) void _SET_MINIMAP_REVEALED(bool toggle)l
extern _native float UNK_0xA4098ACC()l
extern _native32(0x65B705F6) bool _IS_MINIMAP_AREA_REVEALED(vector2 vector, float radius)l
extern _native void UNK_0xE010F081(vector3 vec)l
extern _native void UNK_0x5133A750(any p0)l
extern _native void UNK_0x20FD3E87()l
extern _native void LOCK_MINIMAP_ANGLE(int angle)l
extern _native void UNLOCK_MINIMAP_ANGLE()l
extern _native void LOCK_MINIMAP_POSITION(vector2 vector)l
extern _native void UNLOCK_MINIMAP_POSITION()l
extern _native32(0x0308EDF6) void _SET_MINIMAP_ATTITUDE_INDICATOR_LEVEL(float altitude, bool p1)l
extern _native void UNK_0x7FB6FB2A(any p0, any p1, bool p2)l
extern _native void UNK_0xF07D8CEF(any p0)l
extern _native void UNK_0x827F14DE(any p0)l
extern _native32(0x08EB83D2) void _SET_RADAR_BIGMAP_ENABLED(bool toggleBigMap, bool showFullMap)l
extern _native bool IS_HUD_COMPONENT_ACTIVE(int id)l
extern _native bool IS_SCRIPTED_HUD_COMPONENT_ACTIVE(int id)l
extern _native void HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native bool UNK_0xE8C8E535(any p0)l
extern _native void HIDE_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native void SHOW_HUD_COMPONENT_THIS_FRAME(int id)l
extern _native void UNK_0x52746FE1()l
extern _native void RESET_RETICULE_VALUES()l
extern _native void RESET_HUD_COMPONENT_VALUES(int id)l
extern _native void SET_HUD_COMPONENT_POSITION(int id, vector2 vector)l
extern _native vector3 GET_HUD_COMPONENT_POSITION(int id)l
extern _native void CLEAR_REMINDER_MESSAGE()l
extern _native32(0xFE9A39F8) bool _GET_SCREEN_COORD_FROM_WORLD_COORD(vector3 world, float* screenX, float* screenY)l
extern _native void UNK_0x10DE5150()l
extern _native void UNK_0x67649EE0()l
extern _native any UNK_0x9D2C94FA()l
extern _native bool UNK_0x45472FD5(any p0)l
extern _native void UNK_0x198F32D7(any p0, float p1, float p2)l
extern _native void UNK_0x93045157(any p0, vector3 vec)l
extern _native void UNK_0x18B012B7(any p0, any p1, float p2, float p3)l
extern _native void UNK_0x97852A82(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void CLEAR_FLOATING_HELP(any p0, bool p1)l
extern _native32(0xC969F2D0) void _CREATE_MP_GAMER_TAG_COLOR(int headDisplayId, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, any p5, RGB colour)l
extern _native bool UNK_0xEFD2564A()l
extern _native32(0xF5CD2AA4) int _CREATE_MP_GAMER_TAG(Ped ped, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, any p5)l
extern _native void REMOVE_MP_GAMER_TAG(int gamerTagId)l
extern _native bool IS_MP_GAMER_TAG_ACTIVE(int gamerTagId)l
extern _native bool ADD_TREVOR_RANDOM_MODIFIER(int gamerTagId)l
extern _native void SET_MP_GAMER_TAG_VISIBILITY(int gamerTagId, int component, bool toggle)l
extern _native void UNK_0x767DED29(int headDisplayId, bool p1)l
extern _native void UNK_0xB01A5434(int headDisplayId, bool p1)l
extern _native void SET_MP_GAMER_TAG_COLOUR(int gamerTagId, int flag, int color)l
extern _native32(0x5777EC77) void _SET_MP_GAMER_TAG_HEALTH_BAR_COLOR(int headDisplayId, int color)l
extern _native void SET_MP_GAMER_TAG_ALPHA(int gamerTagId, int component, int alpha)l
extern _native void SET_MP_GAMER_TAG_WANTED_LEVEL(int gamerTagId, int wantedlvl)l
extern _native void SET_MP_GAMER_TAG_NAME(int gamerTagId, const char* string)l
extern _native bool UNK_0xF11414C4(int gamerTagId)l
extern _native void UNK_0x939218AB(int gamerTagId, const char* string)l
extern _native any UNK_0xAB5B7C18()l
extern _native int GET_CURRENT_WEBSITE_ID()l
extern _native any UNK_0xD217EE7E(any p0)l
extern _native void SET_WARNING_MESSAGE(const char* entryLine1, int instructionalKey, const char* entryLine2, bool p3, any p4, any* p5, any* p6, bool background)l
extern _native32(0x2DB9EAB5) void _SET_WARNING_MESSAGE_2(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, any p5, any* p6, any* p7, bool background)l
extern _native32(0x749929D3) void _SET_WARNING_MESSAGE_3(const char* entryHeader, const char* entryLine1, any instructionalKey, const char* entryLine2, bool p4, any p5, any p6, any* p7, any* p8, bool p9)l
extern _native bool IS_WARNING_MESSAGE_ACTIVE()l
extern _native void UNK_0x2F9A309C()l
extern _native32(0xE4FD20D8) void _SET_MAP_FULL_SCREEN(bool toggle)l
extern _native void UNK_0x13E7A5A9(any p0)l
extern _native any UNK_0x786CA0A2(float p0, float p1, float p2)l
extern _native void UNK_0xCBEC9369()l
extern _native any UNK_0x3F4AFB13()l
extern _native void UNK_0x2F28F0A6(bool p0)l
extern _native void UNK_0x801D0D86()l
extern _native void UNK_0x317775DF()l
extern _native void ACTIVATE_FRONTEND_MENU(Hash menuhash, bool Toggle_Pause, int component)l
extern _native void RESTART_FRONTEND_MENU(Hash menuHash, int p1)l
extern _native32(0x33D6868F) Hash _GET_CURRENT_FRONTEND_MENU()l
extern _native void SET_PAUSE_MENU_ACTIVE(bool toggle)l
extern _native void DISABLE_FRONTEND_THIS_FRAME()l
extern _native void UNK_0x7F349900()l
extern _native void UNK_0x630CD8EE()l
extern _native void SET_FRONTEND_ACTIVE(bool active)l
extern _native bool IS_PAUSE_MENU_ACTIVE()l
extern _native any UNK_0xC85C4487()l
extern _native int GET_PAUSE_MENU_STATE()l
extern _native bool IS_PAUSE_MENU_RESTARTING()l
extern _native32(0x2DFD35C7) void _LOG_DEBUG_INFO(const char* p0)l
extern _native void UNK_0x0A89336C(any p0)l
extern _native void UNK_0xC84BE309()l
extern _native32(0x9FE8FD5E) void _ADD_FRONTEND_MENU_CONTEXT(Hash hash)l
extern _native void OBJECT_DECAL_TOGGLE(Hash hash)l
extern _native bool UNK_0xC51BC42F(Hash hash)l
extern _native any UNK_0x016D7AF9()l
extern _native void ENABLE_DEATHBLOOD_SEETHROUGH(bool p0)l
extern _native void UNK_0x6C67131A(bool p0, any p1, any p2)l
extern _native void UNK_0x11D09737(bool p0)l
extern _native any UNK_0xD3BF3ABD()l
extern _native void UNK_0xC06B763D()l
extern _native void UNK_0xB9392CE7()l
extern _native any UNK_0x92DAFA78()l
extern _native any UNK_0x22CA9F2A()l
extern _native any UNK_0xDA7951A2()l
extern _native any UNK_0x7D95AFFF()l
extern _native any UNK_0x96863460()l
extern _native void UNK_0x8543AAC8(any* p0, any* p1)l
extern _native void UNK_0x6025AA2F(any* p0, any* p1, any* p2)l
extern _native bool UNK_0x46794EB2(int* p0, int* p1, int* p2)l
extern _native bool SET_USERIDS_UIHIDDEN(any p0, any* p1)l
extern _native bool UNK_0xD6CC4766(any p0, any* p1, any p2, any p3)l
extern _native bool UNK_0x51972B04(any p0, float* p1)l
extern _native bool UNK_0xD43BB56D(Hash p0, any* p1)l
extern _native void CLEAR_PED_IN_PAUSE_MENU()l
extern _native void GIVE_PED_TO_PAUSE_MENU(Ped ped, int p1)l
extern _native void UNK_0x127310EB(bool p0)l
extern _native void UNK_0x8F45D327(bool p0)l
extern _native32(0x19FCBBB2) void _SHOW_SOCIAL_CLUB_LEGAL_SCREEN()l
extern _native any UNK_0x850690FF()l
extern _native int UNK_0x9D4934F4()l
extern _native void UNK_0x57218529()l
extern _native void UNK_0x5F86AA39()l
extern _native void UNK_0x7AD67C95(const char* p0)l
extern _native bool IS_SOCIAL_CLUB_ACTIVE()l
extern _native void UNK_0xFF06772A(bool p0)l
extern _native32(0x96C4C4DD) void _SET_PED_ENEMY_AI_BLIP(int pedHandle, bool showViewCones)l
extern _native bool DOES_PED_HAVE_AI_BLIP(Ped ped)l
extern _native void UNK_0xD8E31B1A(Ped ped, int unk)l
extern _native void HIDE_SPECIAL_ABILITY_LOCKON_OPERATION(any p0, bool p1)l
extern _native void UNK_0xFFDF46F0(Ped ped, bool p1)l
extern _native32(0xF9DC2AF7) void _SET_AI_BLIP_MAX_DISTANCE(Ped ped, float p1)l
extern _native any* UNK_0x06349065(Ped ped)l
extern _native Blip UNK_0xCA52CF43(Ped ped)l
#pragma endregion //}
#pragma region GRAPHICS //{
extern _native void SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(bool enabled)l
extern _native void DRAW_DEBUG_LINE(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void DRAW_DEBUG_LINE_WITH_TWO_COLOURS(vector3 vec_1, vector3 vec_2, RGB colour_1, RGB colour_2, int alpha1, int alpha2)l
extern _native void DRAW_DEBUG_SPHERE(vector3 vec, float radius, RGBA colour)l
extern _native void DRAW_DEBUG_BOX(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void DRAW_DEBUG_CROSS(vector3 vec, float size, RGBA colour)l
extern _native void DRAW_DEBUG_TEXT(const char* text, vector3 vec, RGBA colour)l
extern _native void DRAW_DEBUG_TEXT_2D(const char* text, vector3 vec, RGBA colour)l
extern _native void DRAW_LINE(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void DRAW_POLY(vector3 vec_1, vector3 vec_2, vector3 vec_3, RGBA colour)l
extern _native void DRAW_BOX(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void UNK_0xC44C2F44(bool p0)l
extern _native any UNK_0xBA9AD458()l
extern _native any UNK_0xADBBA287()l
extern _native void UNK_0x9E553002()l
extern _native bool UNK_0x56C1E488(any* p0, any p1, any p2, any p3)l
extern _native int UNK_0x226B08EA(any* p0)l
extern _native any UNK_0x1F3CADB0()l
extern _native any UNK_0xA9DC8558()l
extern _native void UNK_0x88EAF398()l
extern _native any UNK_0x47B0C137()l
extern _native any UNK_0x65376C9B()l
extern _native void UNK_0x9CBA682A()l
extern _native any UNK_0x3B15D33C(int p0)l
extern _native any UNK_0xEC5D0317()l
extern _native bool UNK_0x25D569EB(any p0)l
extern _native any UNK_0xCFCDC518(any p0)l
extern _native void UNK_0x108F36CC()l
extern _native void UNK_0xE9F2B68F(bool p0, bool p1)l
extern _native int GET_MAXIMUM_NUMBER_OF_PHOTOS()l
extern _native any UNK_0x239272BD()l
extern _native int UNK_0x21DBF0C9()l
extern _native any UNK_0x199FABF0(any p0)l
extern _native any UNK_0x596B900D(any p0)l
extern _native void UNK_0xC9EF81ED()l
extern _native any UNK_0x9D84554C(any p0)l
extern _native any UNK_0x9C106AD9(any p0)l
extern _native32(0x762E5C5F) int _RETURN_TWO(any p0)l
extern _native void DRAW_LIGHT_WITH_RANGE(vector3 pos, RGB color, float range, float intensity)l
extern _native void DRAW_SPOT_LIGHT(vector3 pos, vector3 dir, RGB color, float distance, float brightness, float roundness, float radius, float falloff)l
extern _native32(0x32BF9598) void _DRAW_SPOT_LIGHT_WITH_SHADOW(vector3 pos, vector3 dir, RGB color, float distance, float brightness, float roundness, float radius, float falloff, float shadow)l
extern _native void UNK_0x93628786(float p0)l
extern _native void DRAW_MARKER(int type, vector3 pos, vector3 dir, vector3 rot, vector3 scale, RGBA colour, bool bobUpAndDown, bool faceCamera, int p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts)l
extern _native int CREATE_CHECKPOINT(int type, vector3 pos1, vector3 pos2, float radius, RGBA colour, int reserved)l
extern _native void UNK_0x80151CCF(int checkpoint, float p0)l
extern _native void SET_CHECKPOINT_CYLINDER_HEIGHT(int checkpoint, float nearHeight, float farHeight, float radius)l
extern _native void SET_CHECKPOINT_RGBA(int checkpoint, RGBA colour)l
extern _native32(0xA5456DBB) void _SET_CHECKPOINT_ICON_RGBA(int checkpoint, RGBA colour)l
extern _native void UNK_0x20EABD0F(int checkpoint, vector3 pos, vector3 unk)l
extern _native void UNK_0x1E3A3126(int checkpoint)l
extern _native void DELETE_CHECKPOINT(int checkpoint)l
extern _native void UNK_0x932FDB81(bool p0)l
extern _native void UNK_0x7E946E87(bool p0)l
extern _native void REQUEST_STREAMED_TEXTURE_DICT(const char* textureDict, bool p1)l
extern _native bool HAS_STREAMED_TEXTURE_DICT_LOADED(const char* textureDict)l
extern _native void SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(const char* textureDict)l
extern _native void DRAW_RECT(vector2 vector, Size size, RGBA colour)l
extern _native void UNK_0xF8FBCC25(bool p0)l
extern _native32(0xADF81D24) void _SET_2D_LAYER(int layer)l
extern _native32(0x228A2598) void _SET_SCREEN_DRAW_POSITION(int x, int y)l
extern _native32(0x3FE33BD6) void _SCREEN_DRAW_POSITION_END()l
extern _native32(0x76C641E4) void _SCREEN_DRAW_POSITION_RATIO(vector2 vector, float p2, float p3)l
extern _native float GET_SAFE_ZONE_SIZE()l
extern _native void DRAW_SPRITE(const char* textureDict, const char* textureName, vector2 screen, Size size, float heading, RGBA colour)l
extern _native any ADD_ENTITY_ICON(Entity entity, const char* icon)l
extern _native void SET_ENTITY_ICON_VISIBILITY(Entity entity, bool toggle)l
extern _native void SET_ENTITY_ICON_COLOR(Entity entity, RGBA colour)l
extern _native void SET_DRAW_ORIGIN(vector3 vec, any p3)l
extern _native void CLEAR_DRAW_ORIGIN()l
extern _native void ATTACH_TV_AUDIO_TO_ENTITY(Entity entity)l
extern _native void SET_TV_AUDIO_FRONTEND(bool toggle)l
extern _native int LOAD_MOVIE_MESH_SET(const char* movieMeshSetName)l
extern _native void RELEASE_MOVIE_MESH_SET(int movieMeshSet)l
extern _native any UNK_0x9D5D9B38(any p0)l
extern _native void GET_SCREEN_RESOLUTION(int* x, int* y)l
extern _native bool GET_IS_WIDESCREEN()l
extern _native bool GET_IS_HIDEF()l
extern _native void SET_NIGHTVISION(bool toggle)l
extern _native32(0x62619061) bool _IS_NIGHTVISION_INACTIVE()l
extern _native void SET_NOISEOVERIDE(bool toggle)l
extern _native void SET_NOISINESSOVERIDE(float value)l
extern _native bool GET_SCREEN_COORD_FROM_WORLD_COORD(vector3 world, float* screenX, float* screenY)l
extern _native vector3 GET_TEXTURE_RESOLUTION(const char* textureDict, const char* textureName)l
extern _native void UNK_0x455F1084(float p0)l
extern _native void SET_FLASH(float p0, float p1, float fadeIn, float duration, float fadeOut)l
extern _native void UNK_0x0DCC0B8B()l
extern _native32(0xAA2A0EAF) void _SET_BLACKOUT(bool enable)l
extern _native Object CREATE_TRACKED_POINT()l
extern _native any SET_TRACKED_POINT_INFO(Object point, vector3 vec, float radius)l
extern _native bool IS_TRACKED_POINT_VISIBLE(Object point)l
extern _native void DESTROY_TRACKED_POINT(Object point)l
extern _native void UNK_0x48F16186()l
extern _native void UNK_0x13D4ABC0(float p0)l
extern _native void UNK_0xD2157428(float p0)l
extern _native void UNK_0xC07C64C9(float p0)l
extern _native32(0xFE903D0F) void _SET_FAR_SHADOWS_SUPPRESSED(bool toggle)l
extern _native void UNK_0xDE10BA1F(const char* p0)l
extern _native void UNK_0x9F470BE3(bool p0)l
extern _native void UNK_0x4A124267(bool p0)l
extern _native any UNK_0xB19B2764(float p0)l
extern _native void UNK_0x342FA2B4(bool p0)l
extern _native void UNK_0x5D3BFFC9(bool p0)l
extern _native void UNK_0xD9653728(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8)l
extern _native void UNK_0x72BA8A14(float p0, float p1, float p2)l
extern _native void UNK_0x804F444C(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)l
extern _native void UNK_0xBB1A1294(any p0, any p1)l
extern _native void UNK_0x1A1A72EF(bool p0)l
extern _native void UNK_0x3BB12B75(int type, vector3 Pos, float p4, RGBA colour)l
extern _native void UNK_0x4EA70FB4(float p0, float p1, float p2, float p3, float p4)l
extern _native void UNK_0x0D830DC7(bool p0)l
extern _native any UNK_0xA08B46AD()l
extern _native int UNK_0xECD470F0(any p0)l
extern _native void SET_SEETHROUGH(bool toggle)l
extern _native32(0x1FE547F2) bool _IS_SEETHROUGH_ACTIVE()l
extern _native void UNK_0x654F0287(any p0, float p1)l
extern _native void UNK_0xF6B837F0(float p0)l
extern _native any UNK_0xD906A3A9()l
extern _native void UNK_0xD34A6CBA(bool p0)l
extern _native void UNK_0xD8CC7221(any p0)l
extern _native32(0x5604B890) bool _TRANSITION_TO_BLURRED(float transitionTime)l
extern _native32(0x46617502) bool _TRANSITION_FROM_BLURRED(float transitionTime)l
extern _native void UNK_0xDB7AECDA()l
extern _native float IS_PARTICLE_FX_DELAYED_BLINK()l
extern _native any UNK_0x926B8734()l
extern _native32(0x30ADE541) void _SET_FROZEN_RENDERING_DISABLED(bool enabled)l
extern _native void UNK_0x0113EAE4()l
extern _native void UNK_0xDCBA251B()l
extern _native void UNK_0x513D444B(bool p0, bool p1, float p2, float p3, float p4, float p5)l
extern _native bool UNK_0xB2410EAB(bool p0)l
extern _native any UNK_0x5AB94128()l
extern _native bool UNK_0xD63FCB3E(const char* textureDict, bool p1)l
extern _native int START_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, vector3 Pos, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native32(0x633F8C48) bool _START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(const char* effectName, vector3 Pos, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native bool START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, vector3 offset, vector3 rot, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native32(0x161780C1) bool _START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(const char* effectName, Ped ped, vector3 offset, vector3 rot, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native bool START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, vector3 offset, vector3 rot, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native void SET_PARTICLE_FX_NON_LOOPED_COLOUR(FloatRGB colour)l
extern _native void SET_PARTICLE_FX_NON_LOOPED_ALPHA(float alpha)l
extern _native int START_PARTICLE_FX_LOOPED_AT_COORD(const char* effectName, vector3 vec, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11)l
extern _native int START_PARTICLE_FX_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, vector3 Offset, vector3 Rot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native int START_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native32(0x110752B2) int _START_PARTICLE_FX_LOOPED_ON_ENTITY_2(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native void STOP_PARTICLE_FX_LOOPED(int ptfxHandle, bool p1)l
extern _native void REMOVE_PARTICLE_FX(int ptfxHandle, bool p1)l
extern _native void REMOVE_PARTICLE_FX_FROM_ENTITY(Entity entity)l
extern _native void REMOVE_PARTICLE_FX_IN_RANGE(vector3 vec, float radius)l
extern _native bool DOES_PARTICLE_FX_LOOPED_EXIST(int ptfxHandle)l
extern _native void SET_PARTICLE_FX_LOOPED_OFFSETS(int ptfxHandle, vector3 vec, vector3 rot)l
extern _native void SET_PARTICLE_FX_LOOPED_EVOLUTION(int ptfxHandle, const char* propertyName, float amount, bool Id)l
extern _native void SET_PARTICLE_FX_LOOPED_COLOUR(int ptfxHandle, FloatRGB colour, bool p4)l
extern _native void SET_PARTICLE_FX_LOOPED_ALPHA(int ptfxHandle, float alpha)l
extern _native void SET_PARTICLE_FX_LOOPED_SCALE(int ptfxHandle, float scale)l
extern _native32(0x233DE879) void _SET_PARTICLE_FX_LOOPED_RANGE(int ptfxHandle, float range)l
extern _native void SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(bool p0)l
extern _native void SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(any p0, bool p1)l
extern _native void SET_PARTICLE_FX_SHOOTOUT_BOAT(any p0)l
extern _native void SET_PARTICLE_FX_BLOOD_SCALE(bool p0)l
extern _native void ENABLE_CLOWN_BLOOD_VFX(bool toggle)l
extern _native void ENABLE_ALIEN_BLOOD_VFX(bool Toggle)l
extern _native32(0x9C720B61) void _USE_PARTICLE_FX_ASSET_NEXT_CALL(const char* name)l
extern _native void WASH_DECALS_IN_RANGE(any p0, any p1, any p2, any p3, any p4)l
extern _native void WASH_DECALS_FROM_VEHICLE(Vehicle vehicle, float p1)l
extern _native void FADE_DECALS_IN_RANGE(any p0, any p1, any p2, any p3, any p4)l
extern _native void REMOVE_DECALS_IN_RANGE(vector3 vec, float range)l
extern _native void REMOVE_DECALS_FROM_OBJECT(Object obj)l
extern _native void REMOVE_DECALS_FROM_OBJECT_FACING(Object obj, vector3 vec)l
extern _native void REMOVE_DECALS_FROM_VEHICLE(Vehicle vehicle)l
extern _native int ADD_DECAL(int decalType, vector3 pos, float p4, float p5, float p6, float p7, float p8, float p9, Size size, FloatRGB Coef, float opacity, float timeout, bool p17, bool p18, bool p19)l
extern _native any ADD_PETROL_DECAL(vector3 vec, float groundLvl, float width, float transparency)l
extern _native void UNK_0xE3938B0B(float p0)l
extern _native void UNK_0xBAEC6ADD(any p0, any p1, any p2, any p3)l
extern _native void UNK_0xCCCA6855()l
extern _native void REMOVE_DECAL(int decal)l
extern _native bool IS_DECAL_ALIVE(int decal)l
extern _native float GET_DECAL_WASH_LEVEL(int decal)l
extern _native void UNK_0xEAB6417C()l
extern _native void UNK_0xC2703B88()l
extern _native void UNK_0xA706E84D()l
extern _native bool UNK_0x242C6A04(vector3 Coord, float p3)l
extern _native void UNK_0x335695CF(any p0, any* p1, any* p2)l
extern _native void UNK_0x7B786555(any p0)l
extern _native void MOVE_VEHICLE_DECALS(any p0, any p1)l
extern _native32(0x12077738) bool _ADD_CLAN_DECAL_TO_VEHICLE(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, any p13, int alpha)l
extern _native void UNK_0x667046A8(Vehicle vehicle, any p1)l
extern _native int UNK_0x4F4D76E8(Vehicle vehicle, any p1)l
extern _native32(0x6D58F73B) bool _DOES_VEHICLE_HAVE_DECAL(Vehicle vehicle, any p1)l
extern _native void UNK_0x9BABCBA4(bool p0)l
extern _native void UNK_0xFDF6D8DA(bool p0)l
extern _native void UNK_0x2056A015(float p0)l
extern _native void UNK_0x0F486429(any* p0)l
extern _native void UNK_0xD87CC710(float p0)l
extern _native void UNK_0xE29EE145()l
extern _native void DISABLE_VEHICLE_DISTANTLIGHTS(bool toggle)l
extern _native void UNK_0x60F72371(bool p0)l
extern _native void SET_TIMECYCLE_MODIFIER(const char* modifierName)l
extern _native void SET_TIMECYCLE_MODIFIER_STRENGTH(float strength)l
extern _native void SET_TRANSITION_TIMECYCLE_MODIFIER(const char* modifierName, float transition)l
extern _native void UNK_0x56345F6B(float p0)l
extern _native void CLEAR_TIMECYCLE_MODIFIER()l
extern _native int GET_TIMECYCLE_MODIFIER_INDEX()l
extern _native any UNK_0x03C44E4B()l
extern _native void PUSH_TIMECYCLE_MODIFIER()l
extern _native void POP_TIMECYCLE_MODIFIER()l
extern _native void UNK_0x85BA15A4(const char* p0)l
extern _native void UNK_0x9559BB38(float p0)l
extern _native void UNK_0x554BA16E(const char* p0)l
extern _native void UNK_0xE8F538B5(any* p0, any* p1)l
extern _native void UNK_0x805BAB08(any p0)l
extern _native void UNK_0x908A335E(any* p0)l
extern _native void UNK_0x6776720A()l
extern _native int REQUEST_SCALEFORM_MOVIE(const char* scaleformName)l
extern _native int REQUEST_SCALEFORM_MOVIE_INSTANCE(const char* scaleformName)l
extern _native bool HAS_SCALEFORM_MOVIE_LOADED(int scaleformHandle)l
extern _native bool HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(int scaleformHandle)l
extern _native void SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(int* scaleformHandle)l
extern _native void SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(int scaleform, bool toggle)l
extern _native void DRAW_SCALEFORM_MOVIE(int scaleformHandle, vector2 vector, Size size, RGBA colour, int unk)l
extern _native void DRAW_SCALEFORM_MOVIE_FULLSCREEN(int scaleform, RGBA colour, int unk)l
extern _native void DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(int scaleform1, int scaleform2, RGBA colour)l
extern _native void DRAW_SCALEFORM_MOVIE_3D(int scaleform, vector3 pos, vector3 rot, float p7, float p8, float p9, vector3 scale, any p13)l
extern _native32(0x899933C8) void _DRAW_SCALEFORM_MOVIE_3D_NON_ADDITIVE(int scaleform, vector3 pos, vector3 rot, float p7, float p8, float p9, vector3 scale, any p13)l
extern _native void CALL_SCALEFORM_MOVIE_METHOD(int scaleform, const char* method)l
extern _native32(0x557EDA1D) void _CALL_SCALEFORM_MOVIE_FUNCTION_FLOAT_PARAMS(int scaleform, const char* functionName, float param1, float param2, float param3, float param4, float param5)l
extern _native32(0x91A7FCEB) void _CALL_SCALEFORM_MOVIE_FUNCTION_STRING_PARAMS(int scaleform, const char* functionName, const char* param1, const char* param2, const char* param3, const char* param4, const char* param5)l
extern _native32(0x6EAF56DE) void _CALL_SCALEFORM_MOVIE_FUNCTION_MIXED_PARAMS(int scaleform, const char* functionName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, const char* stringParam1, const char* stringParam2, const char* stringParam3, const char* stringParam4, const char* stringParam5)l
extern _native32(0x5D66CE1E) bool _PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT(int hudComponent, const char* functionName)l
extern _native32(0x215ABBE8) bool _PUSH_SCALEFORM_MOVIE_FUNCTION(int scaleform, const char* functionName)l
extern _native32(0xF6015178) bool _PUSH_SCALEFORM_MOVIE_FUNCTION_N(const char* functionName)l
extern _native bool UNK_0x5E219B67(const char* functionName)l
extern _native32(0x02DBF2D7) void _POP_SCALEFORM_MOVIE_FUNCTION_VOID()l
extern _native32(0x2F38B526) any _POP_SCALEFORM_MOVIE_FUNCTION()l
extern _native bool UNK_0x5CD7C3C0(any funcData)l
extern _native int UNK_0x2CFB0E6D(any funcData)l
extern _native const char* SITTING_TV(int scaleform)l
extern _native32(0x716777CB) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(int value)l
extern _native32(0x9A01FFDA) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(float value)l
extern _native32(0x0D4AE8CB) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(bool value)l
extern _native void BEGIN_TEXT_COMMAND_SCALEFORM_STRING(const char* componentType)l
extern _native void END_TEXT_COMMAND_SCALEFORM_STRING()l
extern _native32(0x2E80DB52) void _END_TEXT_COMMAND_SCALEFORM_STRING_2()l
extern _native32(0x4DAAD55B) void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(const char* value)l
extern _native void UNK_0xCCBF0334(const char* p0)l
extern _native bool UNK_0x91A081A1(any p0)l
extern _native void UNK_0x83A9811D(any p0)l
extern _native32(0x7AF85862) void _REQUEST_HUD_SCALEFORM(int hudComponent)l
extern _native32(0x79B43255) bool _HAS_HUD_SCALEFORM_LOADED(int hudComponent)l
extern _native void UNK_0x03D87600(any p0)l
extern _native bool UNK_0xE9183D3A(int scaleformHandle)l
extern _native void SET_TV_CHANNEL(int channel)l
extern _native int GET_TV_CHANNEL()l
extern _native void SET_TV_VOLUME(float volume)l
extern _native float GET_TV_VOLUME()l
extern _native void DRAW_TV_CHANNEL(vector2 Pos, Size Scale, float rotation, RGBA colour)l
extern _native void UNK_0xB262DE67(int p0, const char* p1, bool p2)l
extern _native void UNK_0x78C4DCBE(any p0, const char* p1, any p2)l
extern _native void UNK_0xCBE7068F(any p0)l
extern _native32(0x4D1EB0FB) bool _LOAD_TV_CHANNEL(Hash tvChannel)l
extern _native void UNK_0x796DE696(bool p0)l
extern _native void UNK_0xD99EC000(any p0)l
extern _native void ENABLE_MOVIE_SUBTITLES(bool toggle)l
extern _native bool UNK_0xE40A0F1A()l
extern _native bool UNK_0x2E7D9B98(const char* p0)l
extern _native bool UNK_0x9A0E3BFE(const char* p0, Ped ped, int p2, vector3 pos)l
extern _native void UNK_0x431AA036()l
extern _native void UNK_0x24A7A7F6(bool p0)l
extern _native void UNK_0xA1CB6C94(bool p0)l
extern _native void UNK_0x3B637AA7(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12)l
extern _native void UNK_0xDF552973(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)l
extern _native32(0x1D980479) void _START_SCREEN_EFFECT(const char* effectName, int duration, bool looped)l
extern _native32(0x06BB5CDA) void _STOP_SCREEN_EFFECT(const char* effectName)l
extern _native32(0x089D5921) bool _GET_SCREEN_EFFECT_IS_ACTIVE(const char* effectName)l
extern _native32(0x4E6D875B) void _STOP_ALL_SCREEN_EFFECTS()l
#pragma endregion //}
#pragma region STATS //{
extern _native any STAT_CLEAR_SLOT_FOR_RELOAD(int statSlot)l
extern _native bool STAT_LOAD(int p0)l
extern _native bool STAT_SAVE(int p0, bool p1, int p2)l
extern _native void UNK_0xC62406A6(any p0)l
extern _native bool STAT_LOAD_PENDING(any p0)l
extern _native any STAT_SAVE_PENDING()l
extern _native any STAT_SAVE_PENDING_OR_REQUESTED()l
extern _native any STAT_DELETE_SLOT(any p0)l
extern _native bool STAT_SLOT_IS_LOADED(any p0)l
extern _native bool UNK_0x0BF0F4B2(any p0)l
extern _native any UNK_0xCE6B62B5(any p0)l
extern _native void UNK_0xCE7A2411(bool p0)l
extern _native bool UNK_0x22804C20(any p0)l
extern _native void UNK_0x395D18B1(any p0)l
extern _native any UNK_0xED7000C8()l
extern _native any UNK_0x099FCC86()l
extern _native bool STAT_SET_INT(Hash statName, int value, bool save)l
extern _native bool STAT_SET_FLOAT(Hash statName, float value, bool save)l
extern _native bool STAT_SET_BOOL(Hash statName, bool value, bool save)l
extern _native bool STAT_SET_GXT_LABEL(Hash statName, const char* value, bool save)l
extern _native bool STAT_SET_DATE(Hash statName, any* value, int numFields, bool save)l
extern _native bool STAT_SET_STRING(Hash statName, const char* value, bool save)l
extern _native bool STAT_SET_POS(Hash statName, vector3 vec, bool save)l
extern _native bool STAT_SET_MASKED_INT(Hash statName, any p1, any p2, int p3, bool save)l
extern _native bool STAT_SET_USER_ID(Hash statName, const char* value, bool save)l
extern _native bool STAT_SET_CURRENT_POSIX_TIME(Hash statName, bool p1)l
extern _native bool STAT_GET_INT(Hash statHash, int* outValue, int p2)l
extern _native bool STAT_GET_FLOAT(Hash statHash, float* outValue, any p2)l
extern _native bool STAT_GET_BOOL(Hash statHash, bool* outValue, any p2)l
extern _native bool STAT_GET_DATE(Hash statHash, any* p1, any p2, any p3)l
extern _native const char* STAT_GET_STRING(Hash statHash, int p1)l
extern _native bool STAT_GET_POS(any p0, any* p1, any* p2, any* p3, any p4)l
extern _native bool STAT_GET_MASKED_INT(any p0, any* p1, any p2, any p3, any p4)l
extern _native const char* STAT_GET_USER_ID(any p0)l
extern _native const char* STAT_GET_LICENSE_PLATE(Hash statName)l
extern _native bool STAT_SET_LICENSE_PLATE(Hash statName, const char* str)l
extern _native void STAT_INCREMENT(Hash statName, float value)l
extern _native bool UNK_0x46F21343()l
extern _native bool UNK_0x02F283CE()l
extern _native bool UNK_0xC4110917(Hash statName, int p1, float* outValue)l
extern _native void UNK_0x343B27E2(int p0)l
extern _native void UNK_0xE3247582(int p0)l
extern _native int STAT_GET_NUMBER_OF_DAYS(Hash statName)l
extern _native int STAT_GET_NUMBER_OF_HOURS(Hash statName)l
extern _native int STAT_GET_NUMBER_OF_MINUTES(Hash statName)l
extern _native int STAT_GET_NUMBER_OF_SECONDS(Hash statName)l
extern _native32(0x24DD4929) void _STAT_SET_PROFILE_SETTING(int profileSetting, int value)l
extern _native int UNK_0xDFC25D66(int p0)l
extern _native int UNK_0xCA160BCC(int p0)l
extern _native32(0xB5BF87B2) Hash _GET_PSTAT_BOOL_HASH(int index, bool spStat, bool charStat, int character)l
extern _native32(0x1F938864) Hash _GET_PSTAT_INT_HASH(int index, bool spStat, bool charStat, int character)l
extern _native32(0x3F8E893B) Hash _GET_TUPSTAT_BOOL_HASH(int index, bool spStat, bool charStat, int character)l
extern _native32(0xFB93C5A2) Hash _GET_TUPSTAT_INT_HASH(int index, bool spStat, bool charStat, int character)l
extern _native bool STAT_GET_BOOL_MASKED(Hash statName, int mask, int p2)l
extern _native bool STAT_SET_BOOL_MASKED(Hash statName, bool value, int mask, bool save)l
extern _native void UNK_0x61ECC465(const char* p0, any p1)l
extern _native void PLAYSTATS_NPC_INVITE(any* p0)l
extern _native void PLAYSTATS_AWARD_XP(any p0, any p1, any p2)l
extern _native void PLAYSTATS_RANK_UP(any p0)l
extern _native void UNK_0x896CDF8D()l
extern _native void UNK_0x1A66945F(any p0, any p1)l
extern _native void UNK_0xC960E161(any p0, any p1, any p2, any p3, any p4)l
extern _native void PLAYSTATS_MISSION_STARTED(any* p0, any p1, any p2, bool p3)l
extern _native void PLAYSTATS_MISSION_OVER(any* p0, any p1, any p2, bool p3, bool p4, bool p5)l
extern _native void PLAYSTATS_MISSION_CHECKPOINT(any* p0, any p1, any p2, any p3)l
extern _native void UNK_0xAC2C7C63(any* p0, any p1, any p2, any p3)l
extern _native void UNK_0x413539BC(any p0, any p1, any p2, float p3)l
extern _native void PLAYSTATS_RACE_CHECKPOINT(any p0, any p1, any p2, any p3, any p4)l
extern _native bool UNK_0x489E27E7(any* p0, any* p1)l
extern _native void PLAYSTATS_MATCH_STARTED(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native void PLAYSTATS_SHOP_ITEM(any p0, any p1, any p2, any p3, any p4)l
extern _native void UNK_0x6602CED6(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void UNK_0x759E0EC9(any p0, any p1, any p2, any p3)l
extern _native void UNK_0x62073DF7(any p0, any p1, any p2, any p3)l
extern _native void UNK_0x30558CFD(any p0, any p1, any p2)l
extern _native void UNK_0x06CE3692(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9)l
extern _native void UNK_0x8D5C7B37(any p0)l
extern _native void PLAYSTATS_WEBSITE_VISITED(Hash scaleformHash, int p1)l
extern _native void PLAYSTATS_FRIEND_ACTIVITY(any p0, any p1)l
extern _native void PLAYSTATS_ODDJOB_DONE(any p0, any p1, any p2)l
extern _native void PLAYSTATS_PROP_CHANGE(any p0, any p1, any p2, any p3)l
extern _native void PLAYSTATS_CLOTH_CHANGE(any p0, any p1, any p2, any p3, any p4)l
extern _native void UNK_0x79716890(any p0, any p1, any p2)l
extern _native void PLAYSTATS_CHEAT_APPLIED(const char* cheat)l
extern _native void UNK_0x04181752(any* p0, any* p1, any* p2, any* p3)l
extern _native void UNK_0x31002201(any* p0, any* p1, any* p2, any* p3)l
extern _native void UNK_0xDDD1F1F3(any* p0, any* p1, any* p2, any* p3)l
extern _native void UNK_0x66FEB701(int p0, const char* p1)l
extern _native void UNK_0x9E2B9522(int time)l
extern _native any LEADERBOARDS_GET_NUMBER_OF_COLUMNS(any p0, any p1)l
extern _native any LEADERBOARDS_GET_COLUMN_ID(any p0, any p1, any p2)l
extern _native any LEADERBOARDS_GET_COLUMN_TYPE(any p0, any p1, any p2)l
extern _native any LEADERBOARDS_READ_CLEAR_ALL()l
extern _native any LEADERBOARDS_READ_CLEAR(any p0, any p1, any p2)l
extern _native bool LEADERBOARDS_READ_PENDING(any p0, any p1, any p2)l
extern _native any UNK_0x1789437B()l
extern _native bool LEADERBOARDS_READ_SUCCESSFUL(any p0, any p1, any p2)l
extern _native bool LEADERBOARDS2_READ_FRIENDS_BY_ROW(any* p0, any* p1, any p2, bool p3, any p4, any p5)l
extern _native bool LEADERBOARDS2_READ_BY_HANDLE(any* p0, any* p1)l
extern _native bool LEADERBOARDS2_READ_BY_ROW(any* p0, any* p1, any p2, any* p3, any p4, any* p5, any p6)l
extern _native bool LEADERBOARDS2_READ_BY_RANK(any* p0, any p1, any p2)l
extern _native bool LEADERBOARDS2_READ_BY_RADIUS(any* p0, any p1, any* p2)l
extern _native bool LEADERBOARDS2_READ_BY_SCORE_INT(any* p0, any p1, any p2)l
extern _native bool LEADERBOARDS2_READ_BY_SCORE_FLOAT(any* p0, float p1, any p2)l
extern _native bool UNK_0x9BEC3401(any* p0, any* p1, any* p2)l
extern _native bool UNK_0xC977D6E2(any* p0)l
extern _native void UNK_0xF2DB6A82()l
extern _native bool UNK_0x766A74FE(any p0, any* p1)l
extern _native any UNK_0x6B90E730(any p0, any p1)l
extern _native float UNK_0x509A286F(any p0, any p1)l
extern _native bool LEADERBOARDS2_WRITE_DATA(any* p0)l
extern _native void UNK_0x7524E27B(any p0, any p1, float p2)l
extern _native void UNK_0x1C5CCC3A(any p0, any p1, any p2)l
extern _native bool LEADERBOARDS_CACHE_DATA_ROW(any* p0)l
extern _native void LEADERBOARDS_CLEAR_CACHE_DATA()l
extern _native void UNK_0x88AE9667(any p0)l
extern _native bool LEADERBOARDS_GET_CACHE_EXISTS(any p0)l
extern _native any LEADERBOARDS_GET_CACHE_TIME(any p0)l
extern _native any UNK_0xCE7CB520(any p0)l
extern _native bool LEADERBOARDS_GET_CACHE_DATA_ROW(any p0, any p1, any* p2)l
extern _native void UNK_0x4AC39C6C(any p0, any p1, any p2)l
extern _native void UNK_0x3E69E7C3(any p0, float p1, any p2)l
extern _native void UNK_0x2FFD2FA5(any p0, any p1, any p2, any* p3)l
extern _native bool UNK_0x23D70C39()l
extern _native void UNK_0x0AD43306()l
extern _native void UNK_0xC7DE5C30()l
extern _native void UNK_0xA3DAC790(int value)l
extern _native void UNK_0x726FAE66(int value)l
extern _native void UNK_0xF03895A4(int value)l
extern _native void UNK_0x4C39CF10(any p0, any p1)l
extern _native void UNK_0x2180AE13(any p0, any p1)l
extern _native void UNK_0xEE292B91(any p0, float p1)l
extern _native void UNK_0xA063CABD()l
extern _native bool UNK_0x62C19A3D(any* p0, any* p1)l
extern _native void UNK_0x3B4EF322()l
extern _native any UNK_0x54E775E0()l
extern _native any UNK_0xE3F0D62D(any* p0)l
#pragma endregion //}
#pragma region BRAIN //{
extern _native void ADD_SCRIPT_TO_RANDOM_PED(const char* name, Hash model, float p2, float p3)l
extern _native void REGISTER_OBJECT_SCRIPT_BRAIN(const char* scriptName, Hash objectName, int p2, float p3, int p4, int p5)l
extern _native bool IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Object object)l
extern _native void REGISTER_WORLD_POINT_SCRIPT_BRAIN(any* p0, float p1, any p2)l
extern _native bool IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE()l
extern _native void ENABLE_SCRIPT_BRAIN_SET(int brainSet)l
extern _native void DISABLE_SCRIPT_BRAIN_SET(int brainSet)l
extern _native void UNK_0x19B27825()l
extern _native void UNK_0xF3A3AB08()l
extern _native void UNK_0x949FE53E(const char* action)l
extern _native void UNK_0x29CE8BAA(const char* action)l
#pragma endregion //}
#pragma region MOBILE //{
extern _native void CREATE_MOBILE_PHONE(int phoneType)l
extern _native void DESTROY_MOBILE_PHONE()l
extern _native void SET_MOBILE_PHONE_SCALE(float scale)l
extern _native void SET_MOBILE_PHONE_ROTATION(vector3 rot, any p3)l
extern _native void GET_MOBILE_PHONE_ROTATION(vector3* rotation, any p1)l
extern _native void SET_MOBILE_PHONE_POSITION(vector3 pos)l
extern _native void GET_MOBILE_PHONE_POSITION(vector3* position)l
extern _native void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(bool toggle)l
extern _native bool CAN_PHONE_BE_SEEN_ON_SCREEN()l
extern _native void CELL_CAM_ACTIVATE(bool p0, bool p1)l
extern _native32(0x4479B304) void _DISABLE_PHONE_THIS_FRAME(bool toggle)l
extern _native void UNK_0xC273BB4D(int* toggle)l
extern _native void UNK_0x66DCD9D2(float p0)l
extern _native bool CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Entity entity)l
extern _native void GET_MOBILE_PHONE_RENDER_ID(int* renderId)l
#pragma endregion //}
#pragma region APP //{
extern _native bool APP_DATA_VALID()l
extern _native int APP_GET_INT(const char* property)l
extern _native float APP_GET_FLOAT(const char* property)l
extern _native const char* APP_GET_STRING(const char* property)l
extern _native void APP_SET_INT(const char* property, int value)l
extern _native void APP_SET_FLOAT(const char* property, float value)l
extern _native void APP_SET_STRING(const char* property, const char* value)l
extern _native void APP_SET_APP(const char* appName)l
extern _native void APP_SET_BLOCK(const char* blockName)l
extern _native void APP_CLEAR_BLOCK()l
extern _native void APP_CLOSE_APP()l
extern _native void APP_CLOSE_BLOCK()l
extern _native bool APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT()l
extern _native bool APP_HAS_SYNCED_DATA(const char* appName)l
extern _native void APP_SAVE_DATA()l
extern _native any APP_GET_DELETED_FILE_STATUS()l
extern _native bool APP_DELETE_APP_DATA(const char* appName)l
#pragma endregion //}
#pragma region TIME //{
extern _native void SET_CLOCK_TIME(int hour, int minute, int second)l
extern _native void PAUSE_CLOCK(bool toggle)l
extern _native void ADVANCE_CLOCK_TIME_TO(int hour, int minute, int second)l
extern _native void ADD_TO_CLOCK_TIME(int hours, int minutes, int seconds)l
extern _native int GET_CLOCK_HOURS()l
extern _native int GET_CLOCK_MINUTES()l
extern _native int GET_CLOCK_SECONDS()l
extern _native void SET_CLOCK_DATE(int day, int month, int year)l
extern _native int GET_CLOCK_DAY_OF_WEEK()l
extern _native int GET_CLOCK_DAY_OF_MONTH()l
extern _native int GET_CLOCK_MONTH()l
extern _native int GET_CLOCK_YEAR()l
extern _native int GET_MILLISECONDS_PER_GAME_MINUTE()l
extern _native void GET_POSIX_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second)l
extern _native void GET_LOCAL_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second)l
#pragma endregion //}
#pragma region PATHFIND //{
extern _native void SET_ROADS_IN_AREA(vector3 vec_1, vector3 vec_2, bool unknown1, bool unknown2)l
extern _native void SET_ROADS_IN_ANGLED_AREA(vector3 vec_1, vector3 vec_2, float angle, bool unknown1, bool unknown2, bool unknown3)l
extern _native void SET_PED_PATHS_IN_AREA(vector3 vec_1, vector3 vec_2, bool unknown)l
extern _native bool GET_SAFE_COORD_FOR_PED(vector3 vec, bool onGround, vector3* outPosition, int flags)l
extern _native bool GET_CLOSEST_VEHICLE_NODE(vector3 vec, vector3* outPosition, int nodeType, float p5, float p6)l
extern _native bool GET_CLOSEST_MAJOR_VEHICLE_NODE(vector3 vec, vector3* outPosition, float unknown1, int unknown2)l
extern _native bool GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(vector3 vec, vector3* outPosition, float* outHeading, int nodeType, float p6, int p7)l
extern _native bool GET_NTH_CLOSEST_VEHICLE_NODE(vector3 vec, int nthClosest, vector3* outPosition, any unknown1, any unknown2, any unknown3)l
extern _native int GET_NTH_CLOSEST_VEHICLE_NODE_ID(vector3 vec, int nth, int nodetype, float p5, float p6)l
extern _native bool GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(vector3 vec, int nthClosest, vector3* outPosition, float* heading, any* unknown1, int unknown2, float unknown3, float unknown4)l
extern _native any GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(vector3 vec, int nthClosest, vector3* outPosition, float outHeading, any p6, float p7, float p8)l
extern _native bool GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(vector3 vec, vector3 desired, int nthClosest, vector3* outPosition, float* outHeading, int nodetype, any p10, any p11)l
extern _native bool GET_VEHICLE_NODE_PROPERTIES(vector3 vec, int* density, int* flags)l
extern _native bool IS_VEHICLE_NODE_ID_VALID(int vehicleNodeId)l
extern _native void GET_VEHICLE_NODE_POSITION(int nodeId, vector3* outPosition)l
extern _native32(0xEE4B1219) bool _GET_SUPPORTS_GPS_ROUTE_FLAG(int nodeID)l
extern _native32(0x56737A3C) bool _GET_IS_SLOW_ROAD_FLAG(int nodeID)l
extern _native any GET_CLOSEST_ROAD(vector3 vec, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10)l
extern _native bool LOAD_ALL_PATH_NODES(bool keepInMemory)l
extern _native void UNK_0xD6A3B458(bool p0)l
extern _native bool UNK_0x86E80A17(float p0, float p1, float p2, float p3)l
extern _native bool UNK_0x2CDA5012(float p0, float p1, float p2, float p3)l
extern _native void SET_ROADS_BACK_TO_ORIGINAL(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native void SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(vector3 vec_1, vector3 vec_2, float p6)l
extern _native void UNK_0x3C5085E4(float p0)l
extern _native void UNK_0xD0F51299(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native void SET_PED_PATHS_BACK_TO_ORIGINAL(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native bool GET_RANDOM_VEHICLE_NODE(vector3 vec, float radius, bool p4, bool p5, bool p6, vector3* outPosition, float* heading)l
extern _native void GET_STREET_NAME_AT_COORD(vector3 vec, Hash* streetName, Hash* crossingRoad)l
extern _native int GENERATE_DIRECTIONS_TO_COORD(vector3 vec, bool p3, float* direction, float* p5, float* distToNxJunction)l
extern _native void SET_IGNORE_NO_GPS_FLAG(bool ignore)l
extern _native any UNK_0x90DF7A4C(bool p0)l
extern _native void SET_GPS_DISABLED_ZONE(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native any UNK_0x4B770634()l
extern _native any UNK_0x286F82CC()l
extern _native any UNK_0xF6422F9A(any p0, any p1, any p2, any p3, any p4)l
extern _native bool IS_POINT_ON_ROAD(vector3 vec, Vehicle vehicle)l
extern _native void ADD_NAVMESH_REQUIRED_REGION(vector2 vector, float radius)l
extern _native void REMOVE_NAVMESH_REQUIRED_REGIONS()l
extern _native void DISABLE_NAVMESH_IN_AREA(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native bool ARE_ALL_NAVMESH_REGIONS_LOADED()l
extern _native bool IS_NAVMESH_LOADED_IN_AREA(vector3 vec_1, vector3 vec_2)l
extern _native any ADD_NAVMESH_BLOCKING_OBJECT(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, any p8)l
extern _native void UPDATE_NAVMESH_BLOCKING_OBJECT(any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8)l
extern _native void REMOVE_NAVMESH_BLOCKING_OBJECT(any p0)l
extern _native bool DOES_NAVMESH_BLOCKING_OBJECT_EXIST(any p0)l
extern _native float UNK_0x3FE8C5A0(float p0, float p1)l
extern _native float UNK_0x3ED21C90(float p0, float p1, float p2, float p3)l
extern _native float UNK_0xA07C5B7D(float left, float right)l
extern _native float UNK_0x76751DD4(float p0, float p1, float p2, float p3)l
extern _native float CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(vector3 vec_1, vector3 vec_2)l
#pragma endregion //}
#pragma region CONTROLS //{
extern _native bool IS_CONTROL_ENABLED(int inputGroup, int control)l
extern _native bool IS_CONTROL_PRESSED(int inputGroup, int control)l
extern _native bool IS_CONTROL_RELEASED(int inputGroup, int control)l
extern _native bool IS_CONTROL_JUST_PRESSED(int inputGroup, int control)l
extern _native bool IS_CONTROL_JUST_RELEASED(int inputGroup, int control)l
extern _native int GET_CONTROL_VALUE(int inputGroup, int control)l
extern _native float GET_CONTROL_NORMAL(int inputGroup, int control)l
extern _native float UNK_0xC49343BB(int inputGroup, int control)l
extern _native bool IS_DISABLED_CONTROL_PRESSED(int inputGroup, int control)l
extern _native bool IS_DISABLED_CONTROL_JUST_PRESSED(int inputGroup, int control)l
extern _native bool IS_DISABLED_CONTROL_JUST_RELEASED(int inputGroup, int control)l
extern _native float GET_DISABLED_CONTROL_NORMAL(int inputGroup, int control)l
extern _native float UNK_0xF2A65A4C(int inputGroup, int control)l
extern _native int UNK_0x0E8EF929(int p0)l
extern _native const char* GET_CONTROL_INSTRUCTIONAL_BUTTON(int inputGroup, int control, bool p2)l
extern _native const char* UNK_0x3EE71F6A(int inputGroup, int control, bool p2)l
extern _native void SET_PAD_SHAKE(int p0, int duration, int frequency)l
extern _native void STOP_PAD_SHAKE(any p0)l
extern _native void UNK_0x7D65EB6E(any p0, any p1)l
extern _native bool IS_LOOK_INVERTED()l
extern _native int GET_LOCAL_PLAYER_AIM_STATE()l
extern _native void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(bool toggle)l
extern _native void SET_INPUT_EXCLUSIVE(int inputGroup, int control)l
extern _native void DISABLE_CONTROL_ACTION(int inputGroup, int control, bool disable)l
extern _native void ENABLE_CONTROL_ACTION(int inputGroup, int control, bool enable)l
extern _native void DISABLE_ALL_CONTROL_ACTIONS(int inputGroup)l
extern _native void ENABLE_ALL_CONTROL_ACTIONS(int inputGroup)l
extern _native bool UNK_0xD2C80B2E(const char* p0)l
extern _native bool UNK_0xBBFC9050(const char* p0)l
extern _native void UNK_0x42140FF9()l
extern _native32(0x2CEDE6C5) void _DISABLE_INPUT_GROUP(int inputGroup)l
#pragma endregion //}
#pragma region DATAFILE //{
extern _native void UNK_0x621388FF(any p0)l
extern _native bool UNK_0xB41064A4(any p0)l
extern _native bool UNK_0x9DB63CFF(any p0)l
extern _native bool UNK_0xF09157B0(const char* p0, bool p1, const char* p2, any* p3, any* p4, const char* type, bool p6)l
extern _native bool UNK_0xD96860FC(const char* p0, const char* p1, const char* p2, const char* p3, bool p4)l
extern _native bool UNK_0x459F2683(const char* p0, any* p1, bool p2, any* p3, any* p4, any* p5, const char* type)l
extern _native bool UNK_0xDBB83E2B(const char* p0, const char* p1, const char* p2, const char* p3, const char* type)l
extern _native bool UNK_0xBB6321BD(const char* p0, float p1, const char* type)l
extern _native bool UNK_0xE8D56DA2(int p0)l
extern _native bool UNK_0xCB6A351E(int p0, bool p1)l
extern _native bool UNK_0xA4D1B30E(int p0)l
extern _native bool UNK_0xB8515B2F(int p0)l
extern _native32(0x660C468E) bool _LOAD_UGC_FILE(const char* filename)l
extern _native void DATAFILE_CREATE()l
extern _native void DATAFILE_DELETE()l
extern _native void UNK_0x4E03F632()l
extern _native void UNK_0xF11F956F()l
extern _native const char* DATAFILE_GET_FILE_DICT()l
extern _native bool UNK_0x768CBB35(const char* filename)l
extern _native bool UNK_0x0B4087F7(bool* p0)l
extern _native bool DATAFILE_IS_SAVE_PENDING()l
extern _native32(0x9B29D99B) void _OBJECT_VALUE_ADD_BOOLEAN(any* objectData, const char* key, bool value)l
extern _native32(0xEFCF554A) void _OBJECT_VALUE_ADD_INTEGER(any* objectData, const char* key, int value)l
extern _native32(0xE972CACF) void _OBJECT_VALUE_ADD_FLOAT(any* objectData, const char* key, float value)l
extern _native32(0xD437615C) void _OBJECT_VALUE_ADD_STRING(any* objectData, const char* key, const char* value)l
extern _native32(0x75FC6C3C) void _OBJECT_VALUE_ADD_VECTOR3(any* objectData, const char* key, vector3 value)l
extern _native32(0x96A8E05F) any* _OBJECT_VALUE_ADD_OBJECT(any* objectData, const char* key)l
extern _native32(0x03939B8D) any* _OBJECT_VALUE_ADD_ARRAY(any* objectData, const char* key)l
extern _native32(0x8876C872) bool _OBJECT_VALUE_GET_BOOLEAN(any* objectData, const char* key)l
extern _native32(0xA6C68693) int _OBJECT_VALUE_GET_INTEGER(any* objectData, const char* key)l
extern _native32(0xA92C1AF4) float _OBJECT_VALUE_GET_FLOAT(any* objectData, const char* key)l
extern _native32(0x942160EC) const char* _OBJECT_VALUE_GET_STRING(any* objectData, const char* key)l
extern _native32(0xE84A127A) vector3 _OBJECT_VALUE_GET_VECTOR3(any* objectData, const char* key)l
extern _native32(0xC9C13D8D) any* _OBJECT_VALUE_GET_OBJECT(any* objectData, const char* key)l
extern _native32(0x1F2F7D00) any* _OBJECT_VALUE_GET_ARRAY(any* objectData, const char* key)l
extern _native32(0x2678342A) int _OBJECT_VALUE_GET_TYPE(any* objectData, const char* key)l
extern _native32(0x08174B90) void _ARRAY_VALUE_ADD_BOOLEAN(any* arrayData, bool value)l
extern _native32(0xF29C0B36) void _ARRAY_VALUE_ADD_INTEGER(any* arrayData, int value)l
extern _native32(0xE4302123) void _ARRAY_VALUE_ADD_FLOAT(any* arrayData, float value)l
extern _native32(0xF3C01350) void _ARRAY_VALUE_ADD_STRING(any* arrayData, const char* value)l
extern _native32(0x16F464B6) void _ARRAY_VALUE_ADD_VECTOR3(any* arrayData, vector3 value)l
extern _native32(0xC174C71B) any* _ARRAY_VALUE_ADD_OBJECT(any* arrayData)l
extern _native32(0xA2E5F921) bool _ARRAY_VALUE_GET_BOOLEAN(any* arrayData, int arrayIndex)l
extern _native32(0xBB120CFC) int _ARRAY_VALUE_GET_INTEGER(any* arrayData, int arrayIndex)l
extern _native32(0x08AD2CC2) float _ARRAY_VALUE_GET_FLOAT(any* arrayData, int arrayIndex)l
extern _native32(0x93F985A6) const char* _ARRAY_VALUE_GET_STRING(any* arrayData, int arrayIndex)l
extern _native32(0x80E3DA55) vector3 _ARRAY_VALUE_GET_VECTOR3(any* arrayData, int arrayIndex)l
extern _native32(0xECE81278) any* _ARRAY_VALUE_GET_OBJECT(any* arrayData, int arrayIndex)l
extern _native32(0xA8A21766) int _ARRAY_VALUE_GET_SIZE(any* arrayData)l
extern _native32(0xFA2402C8) int _ARRAY_VALUE_GET_TYPE(any* arrayData, int arrayIndex)l
#pragma endregion //}
#pragma region FIRE //{
extern _native int START_SCRIPT_FIRE(vector3 vec, int maxChildren, bool isGasFire)l
extern _native void REMOVE_SCRIPT_FIRE(int fireHandle)l
extern _native any START_ENTITY_FIRE(Entity entity)l
extern _native void STOP_ENTITY_FIRE(Entity entity)l
extern _native bool IS_ENTITY_ON_FIRE(Entity entity)l
extern _native int GET_NUMBER_OF_FIRES_IN_RANGE(vector3 vec, float radius)l
extern _native void STOP_FIRE_IN_RANGE(vector3 vec, float radius)l
extern _native bool GET_CLOSEST_FIRE_POS(vector3* outPosition, vector3 vec)l
extern _native void ADD_OWNED_EXPLOSION(Ped ped, vector3 vec, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native void ADD_EXPLOSION_WITH_USER_VFX(vector3 vec, int explosionType, Hash explosionFx, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native bool IS_EXPLOSION_IN_AREA(int explosionType, vector3 vec_1, vector3 vec_2)l
extern _native bool IS_EXPLOSION_IN_SPHERE(int explosionType, vector3 vec, float radius)l
extern _native bool IS_EXPLOSION_IN_ANGLED_AREA(int explosionType, vector3 vec_1, vector3 vec_2, float angle)l
extern _native32(0xAEC0D176) Entity _GET_PED_INSIDE_EXPLOSION_AREA(int explosionType, vector3 vec_1, vector3 vec_2, float radius)l
#pragma endregion //}
#pragma region DECISIONEVENT //{
extern _native void SET_DECISION_MAKER(Ped ped, Hash name)l
extern _native void CLEAR_DECISION_MAKER_EVENT_RESPONSE(Hash name, int type)l
extern _native void BLOCK_DECISION_MAKER_EVENT(Hash name, int type)l
extern _native void UNBLOCK_DECISION_MAKER_EVENT(Hash name, int type)l
extern _native ScrHandle ADD_SHOCKING_EVENT_AT_POSITION(int type, vector3 vec, float duration)l
extern _native ScrHandle ADD_SHOCKING_EVENT_FOR_ENTITY(int type, Entity entity, float duration)l
extern _native bool IS_SHOCKING_EVENT_IN_SPHERE(int type, vector3 vec, float radius)l
extern _native bool REMOVE_SHOCKING_EVENT(ScrHandle event)l
extern _native void REMOVE_ALL_SHOCKING_EVENTS(bool p0)l
extern _native void REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS()l
extern _native void SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME()l
extern _native void SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(int type)l
extern _native void SUPPRESS_AGITATION_EVENTS_NEXT_FRAME()l
#pragma endregion //}
#pragma region ZONE //{
extern _native int GET_ZONE_AT_COORDS(vector3 vec)l
extern _native int GET_ZONE_FROM_NAME_ID(const char* zoneName)l
extern _native int GET_ZONE_POPSCHEDULE(int zoneId)l
extern _native const char* GET_NAME_OF_ZONE(vector3 vec)l
extern _native void SET_ZONE_ENABLED(int zoneId, bool toggle)l
extern _native int GET_ZONE_SCUMMINESS(int zoneId)l
extern _native void OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(int scheduleId, Hash vehicleHash)l
extern _native void CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(int scheduleId)l
extern _native Hash GET_HASH_OF_MAP_AREA_AT_COORDS(vector3 vec)l
#pragma endregion //}
#pragma region ROPE //{
extern _native Object ADD_ROPE(vector3 vec, vector3 rot, float length, int ropeType, float maxLength, float minLength, float p10, bool p11, bool p12, bool rigid, float p14, bool breakWhenShot, any* unkPtr)l
extern _native void DELETE_ROPE(Object* rope)l
extern _native any DELETE_CHILD_ROPE(Object rope)l
extern _native bool DOES_ROPE_EXIST(Object* rope)l
extern _native void ROPE_DRAW_SHADOW_ENABLED(Object* rope, bool toggle)l
extern _native any LOAD_ROPE_DATA(Object rope, const char* rope_preset)l
extern _native void PIN_ROPE_VERTEX(Object rope, int vertex, vector3 vec)l
extern _native any UNPIN_ROPE_VERTEX(Object rope, int vertex)l
extern _native int GET_ROPE_VERTEX_COUNT(Object rope)l
extern _native void ATTACH_ENTITIES_TO_ROPE(Object rope, Entity ent1, Entity ent2, vector3 ent1_, vector3 ent2_, float length, bool p10, bool p11, any* p12, any* p13)l
extern _native void ATTACH_ROPE_TO_ENTITY(Object rope, Entity entity, vector3 vec, bool p5)l
extern _native void DETACH_ROPE_FROM_ENTITY(Object rope, Entity entity)l
extern _native void ROPE_SET_UPDATE_PINVERTS(Object rope)l
extern _native void UNK_0x80DB77A7(any p0, any p1)l
extern _native void UNK_0xC67D5CF6(any p0, bool p1)l
extern _native bool UNK_0x7A18BB9C(any* p0)l
extern _native any GET_ROPE_LAST_VERTEX_COORD(Object rope)l
extern _native any GET_ROPE_VERTEX_COORD(Object rope, int vertex)l
extern _native void START_ROPE_WINDING(Object rope)l
extern _native void STOP_ROPE_WINDING(Object rope)l
extern _native void START_ROPE_UNWINDING_FRONT(Object rope)l
extern _native void STOP_ROPE_UNWINDING_FRONT(Object rope)l
extern _native void ROPE_CONVERT_TO_SIMPLE(Object rope)l
extern _native any ROPE_LOAD_TEXTURES()l
extern _native bool ROPE_ARE_TEXTURES_LOADED()l
extern _native any ROPE_UNLOAD_TEXTURES()l
extern _native void UNK_0x106BA127(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10, any p11, any p12, any p13)l
extern _native void UNK_0x7C6F7668(any p0, bool p1, bool p2)l
extern _native void UNK_0x686672DD(any p0, any p1)l
extern _native32(0xFD309DC8) float _GET_ROPE_LENGTH(Object rope)l
extern _native any ROPE_FORCE_LENGTH(Object rope, float length)l
extern _native any ROPE_RESET_LENGTH(Object rope, bool length)l
extern _native void APPLY_IMPULSE_TO_CLOTH(vector3 pos, vector3 vec, float impulse)l
extern _native void SET_DAMPING(Object rope, int vertex, float value)l
extern _native void ACTIVATE_PHYSICS(Entity entity)l
extern _native void SET_CGOFFSET(Object rope, vector3 vec)l
extern _native vector3 GET_CGOFFSET(Object rope)l
extern _native void SET_CG_AT_BOUNDCENTER(Object rope)l
extern _native void BREAK_ENTITY_GLASS(any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, any p9, bool p10)l
extern _native any SET_DISABLE_BREAKING(Object rope, bool enabled)l
extern _native void SET_DISABLE_FRAG_DAMAGE(Object object, bool toggle)l
#pragma endregion //}
#pragma region WATER //{
extern _native bool GET_WATER_HEIGHT(vector3 vec, float* height)l
extern _native bool GET_WATER_HEIGHT_NO_WAVES(vector3 vec, float* height)l
extern _native bool TEST_PROBE_AGAINST_WATER(vector3 vec_1, vector3 vec_2, vector3* result)l
extern _native bool TEST_PROBE_AGAINST_ALL_WATER(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native bool TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(vector3 vec, any p3, any* p4)l
extern _native void MODIFY_WATER(vector2 vector, float radius, float height)l
#pragma endregion //}
#pragma region WORLDPROBE //{
extern _native int START_SHAPE_TEST_LOS_PROBE(vector3 vec_1, vector3 vec_2, int flags, Entity entity, int p8)l
extern _native32(0x8251485D) int _START_SHAPE_TEST_RAY(vector3 vec_1, vector3 vec_2, int flags, Entity entity, int p8)l
extern _native int START_SHAPE_TEST_BOUNDING_BOX(Entity entity, int flags1, int flags2)l
extern _native int START_SHAPE_TEST_BOX(vector3 vec, float x1, float y2, float z2, vector3 rot, any p9, any p10, any entity, any p12)l
extern _native int START_SHAPE_TEST_BOUND(Entity entity, int flags1, int flags2)l
extern _native int START_SHAPE_TEST_CAPSULE(vector3 vec_1, vector3 vec_2, float radius, int flags, Entity entity, int p9)l
extern _native int UNK_0x4559460A(vector3 vec_1, vector3 vec_2, float radius, int flags, Entity entity, any p9)l
extern _native int GET_SHAPE_TEST_RESULT(int rayHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Entity* entityHit)l
extern _native32(0x4301E10C) int _GET_SHAPE_TEST_RESULT_EX(int rayHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Hash* materialHash, Entity* entityHit)l
extern _native void UNK_0xEC2AAF06(Entity p0)l
#pragma endregion //}
#pragma region NETWORK //{
extern _native bool NETWORK_IS_SIGNED_IN()l
extern _native bool NETWORK_IS_SIGNED_ONLINE()l
extern _native32(0x3FB40673) bool _NETWORK_ARE_ROS_AVAILABLE()l
extern _native bool NETWORK_IS_CLOUD_AVAILABLE()l
extern _native bool UNK_0x66EC713F()l
extern _native any UNK_0x358D1D77()l
extern _native bool NETWORK_IS_HOST()l
extern _native bool NETWORK_HAVE_ONLINE_PRIVILEGES()l
extern _native bool UNK_0x1F88819D(any p0)l
extern _native bool UNK_0x2D817A5E(any p0, any p1)l
extern _native bool UNK_0xBB54AA3D(any p0, any p1, bool p2)l
extern _native bool NETWORK_CAN_BAIL()l
extern _native void NETWORK_BAIL()l
extern _native void UNK_0x96E28FE2()l
extern _native bool NETWORK_CAN_ACCESS_MULTIPLAYER(int* loadingState)l
extern _native bool NETWORK_IS_MULTIPLAYER_DISABLED()l
extern _native bool NETWORK_CAN_ENTER_MULTIPLAYER()l
extern _native any NETWORK_SESSION_ENTER(any p0, any p1, any p2, int maxPlayers, any p4, any p5)l
extern _native bool NETWORK_SESSION_FRIEND_MATCHMAKING(int p0, int p1, int maxPlayers, bool p3)l
extern _native bool NETWORK_SESSION_CREW_MATCHMAKING(int p0, int p1, int p2, int maxPlayers, bool p4)l
extern _native bool NETWORK_SESSION_ACTIVITY_QUICKMATCH(any p0, any p1, any p2, any p3)l
extern _native bool NETWORK_SESSION_HOST(int p0, int maxPlayers, bool p2)l
extern _native bool NETWORK_SESSION_HOST_CLOSED(int p0, int maxPlayers)l
extern _native bool NETWORK_SESSION_HOST_FRIENDS_ONLY(int p0, int maxPlayers)l
extern _native bool NETWORK_SESSION_IS_CLOSED_FRIENDS()l
extern _native bool NETWORK_SESSION_IS_CLOSED_CREW()l
extern _native bool NETWORK_SESSION_IS_SOLO()l
extern _native bool NETWORK_SESSION_IS_PRIVATE()l
extern _native bool NETWORK_SESSION_END(bool p0, bool p1)l
extern _native void NETWORK_SESSION_KICK_PLAYER(Player player)l
extern _native32(0x8A559D26) bool _NETWORK_SESSION_IS_PLAYER_VOTED_TO_KICK(Player player)l
extern _native void UNK_0x3C3E2AB6(int p0)l
extern _native32(0x5F29A7E0) void _NETWORK_SESSION_SET_MAX_PLAYERS(int playerType, int playerCount)l
extern _native32(0x36EAD960) int _NETWORK_SESSION_GET_UNK(int p0)l
extern _native void UNK_0x5BE529F7(any p0)l
extern _native void UNK_0x454C7B67(any p0)l
extern _native void UNK_0xE5961511(any p0)l
extern _native void UNK_0xAE396263(bool p0)l
extern _native void UNK_0x913FD7D6(any p0)l
extern _native void UNK_0xB3D9A67F(bool p0)l
extern _native void UNK_0x6CC062FC(any p0)l
extern _native void UNK_0x57F9BC83()l
extern _native32(0xF3768F90) void _NETWORK_SESSION_HOSTED(bool p0)l
extern _native void NETWORK_ADD_FOLLOWERS(int* p0, int p1)l
extern _native void NETWORK_CLEAR_FOLLOWERS()l
extern _native32(0x74E8C53E) void _NETWORK_GET_SERVER_TIME(int* hours, int* minutes, int* seconds)l
extern _native void UNK_0x959E43A3(any p0)l
extern _native bool NETWORK_X_AFFECTS_GAMERS(any p0)l
extern _native bool NETWORK_FIND_MATCHED_GAMERS(any p0, float p1, float p2, float p3)l
extern _native bool NETWORK_IS_FINDING_GAMERS()l
extern _native any UNK_0xBEDC4503()l
extern _native int NETWORK_GET_NUM_FOUND_GAMERS()l
extern _native bool NETWORK_GET_FOUND_GAMER(any* p0, any p1)l
extern _native void NETWORK_CLEAR_FOUND_GAMERS()l
extern _native bool UNK_0x42BD0780(any* p0)l
extern _native any UNK_0xBEB98840()l
extern _native any UNK_0x08029970()l
extern _native any UNK_0xC871E745()l
extern _native bool UNK_0xB5ABC4B4(any* p0, any p1)l
extern _native void UNK_0x3F7EDBBD()l
extern _native void NETWORK_IS_PLAYER_ANIMATION_DRAWING_SYNCHRONIZED()l
extern _native void NETWORK_SESSION_CANCEL_INVITE()l
extern _native void NETWORK_SESSION_FORCE_CANCEL_INVITE()l
extern _native bool NETWORK_HAS_PENDING_INVITE()l
extern _native any UNK_0xFBBAC350()l
extern _native any UNK_0x0907A6BF()l
extern _native bool NETWORK_SESSION_WAS_INVITED()l
extern _native void NETWORK_SESSION_GET_INVITER(int* networkHandle)l
extern _native any UNK_0x3EA9D44C()l
extern _native void NETWORK_SUPPRESS_INVITE(bool toggle)l
extern _native void NETWORK_BLOCK_INVITES(bool toggle)l
extern _native void UNK_0x32B7A076()l
extern _native32(0x0FCE995D) void _NETWORK_BLOCK_KICKED_PLAYERS(bool p0)l
extern _native void UNK_0xA639DCA2(bool p0)l
extern _native any UNK_0x70ED476A()l
extern _native void UNK_0x50507BED()l
extern _native void NETWORK_SESSION_HOST_SINGLE_PLAYER(int p0)l
extern _native void NETWORK_SESSION_LEAVE_SINGLE_PLAYER()l
extern _native bool NETWORK_IS_GAME_IN_PROGRESS()l
extern _native bool NETWORK_IS_SESSION_ACTIVE()l
extern _native bool NETWORK_IS_IN_SESSION()l
extern _native bool NETWORK_IS_SESSION_STARTED()l
extern _native bool NETWORK_IS_SESSION_BUSY()l
extern _native bool NETWORK_CAN_SESSION_END()l
extern _native void NETWORK_SESSION_MARK_VISIBLE(bool p0)l
extern _native any NETWORK_SESSION_IS_VISIBLE()l
extern _native void NETWORK_SESSION_BLOCK_JOIN_REQUESTS(bool p0)l
extern _native void NETWORK_SESSION_CHANGE_SLOTS(int p0, bool p1)l
extern _native void NETWORK_SESSION_VOICE_HOST()l
extern _native void NETWORK_SESSION_VOICE_LEAVE()l
extern _native void UNK_0x9DFD89E6(any* globalPtr)l
extern _native void NETWORK_SET_KEEP_FOCUSPOINT(bool p0, any p1)l
extern _native void UNK_0x6EFC2FD0(any p0)l
extern _native bool UNK_0x60AA4AA1()l
extern _native bool UNK_0x132CA01E()l
extern _native void NETWORK_SET_ACTIVITY_SPECTATOR(bool toggle)l
extern _native any NETWORK_IS_ACTIVITY_SPECTATOR()l
extern _native void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(int maxSpectators)l
extern _native int NETWORK_GET_ACTIVITY_PLAYER_NUM(bool p0)l
extern _native bool NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(int* networkHandle)l
extern _native any NETWORK_HOST_TRANSITION(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native bool NETWORK_DO_TRANSITION_QUICKMATCH(any p0, any p1, any p2, any p3)l
extern _native bool NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC(any p0, any p1, any p2, any p3)l
extern _native bool NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP(any p0, any p1, any p2, any p3, any* p4, any p5)l
extern _native any NETWORK_JOIN_GROUP_ACTIVITY()l
extern _native void UNK_0x36A5F2DA()l
extern _native void UNK_0x7EF353E1(bool p0)l
extern _native void UNK_0xF60986FC(bool p0)l
extern _native void NETWORK_SET_TRANSITION_CREATOR_HANDLE(any* p0)l
extern _native void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE()l
extern _native bool NETWORK_INVITE_GAMERS_TO_TRANSITION(any* p0, any p1)l
extern _native void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(int* networkHandle)l
extern _native any NETWORK_LEAVE_TRANSITION()l
extern _native any NETWORK_LAUNCH_TRANSITION()l
extern _native void NETWORK_BAIL_TRANSITION()l
extern _native bool NETWORK_DO_TRANSITION_TO_GAME(bool p0, int maxPlayers)l
extern _native bool NETWORK_DO_TRANSITION_TO_NEW_GAME(bool p0, int maxPlayers, bool p2)l
extern _native bool NETWORK_DO_TRANSITION_TO_FREEMODE(any* p0, any p1, bool p2, int players, bool p4)l
extern _native bool NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(any* p0, any* p1, int players, bool p3, bool p4, bool p5)l
extern _native any NETWORK_IS_TRANSITION_TO_GAME()l
extern _native any NETWORK_GET_TRANSITION_MEMBERS(any* p0, any p1)l
extern _native void NETWORK_APPLY_TRANSITION_PARAMETER(any p0, any p1)l
extern _native void UNK_0xE0C28DB5(any p0, const char* p1, bool p2)l
extern _native bool NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(int* networkHandle, const char* p1, int p2, int p3, bool p4)l
extern _native bool NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(any* p0)l
extern _native any NETWORK_IS_TRANSITION_HOST()l
extern _native bool NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(int* networkHandle)l
extern _native bool NETWORK_GET_TRANSITION_HOST(int* networkHandle)l
extern _native bool NETWORK_IS_IN_TRANSITION()l
extern _native bool NETWORK_IS_TRANSITION_STARTED()l
extern _native any NETWORK_IS_TRANSITION_BUSY()l
extern _native any NETWORK_IS_TRANSITION_MATCHMAKING()l
extern _native void NETWORK_OPEN_TRANSITION_MATCHMAKING()l
extern _native void NETWORK_CLOSE_TRANSITION_MATCHMAKING()l
extern _native any UNK_0xC901AA9F()l
extern _native void NETWORK_SET_TRANSITION_ACTIVITY_ID(any p0)l
extern _native void NETWORK_CHANGE_TRANSITION_SLOTS(any p0, any p1)l
extern _native void UNK_0x0532DDD2(bool p0)l
extern _native bool NETWORK_HAS_PLAYER_STARTED_TRANSITION(Player player)l
extern _native bool NETWORK_ARE_TRANSITION_DETAILS_VALID(any p0)l
extern _native bool NETWORK_JOIN_TRANSITION(Player player)l
extern _native bool NETWORK_HAS_INVITED_GAMER_TO_TRANSITION(any* p0)l
extern _native bool NETWORK_IS_ACTIVITY_SESSION()l
extern _native void UNK_0x18F03AFD(any p0)l
extern _native32(0x8B99B72B) bool _NETWORK_SEND_PRESENCE_INVITE(int* networkHandle, any* p1, any p2, any p3)l
extern _native32(0x877C0E1C) bool _NETWORK_SEND_PRESENCE_TRANSITION_INVITE(any* p0, any* p1, any p2, any p3)l
extern _native any UNK_0x5E832444(any p0)l
extern _native int NETWORK_GET_NUM_PRESENCE_INVITES()l
extern _native bool NETWORK_ACCEPT_PRESENCE_INVITE(any p0)l
extern _native bool NETWORK_REMOVE_PRESENCE_INVITE(any p0)l
extern _native any NETWORK_GET_PRESENCE_INVITE_ID(any p0)l
extern _native any NETWORK_GET_PRESENCE_INVITE_INVITER(any p0)l
extern _native bool NETWORK_GET_PRESENCE_INVITE_HANDLE(any p0, any* p1)l
extern _native any NETWORK_GET_PRESENCE_INVITE_SESSION_ID(any p0)l
extern _native any UNK_0xA4302183(any p0)l
extern _native any UNK_0x51B2D848(any p0)l
extern _native any UNK_0x4677C656(any p0)l
extern _native bool UNK_0xF5E3401C(any p0)l
extern _native bool UNK_0x7D593B4C(any p0)l
extern _native bool NETWORK_HAS_FOLLOW_INVITE()l
extern _native any NETWORK_ACTION_FOLLOW_INVITE()l
extern _native any NETWORK_CLEAR_FOLLOW_INVITE()l
extern _native void UNK_0x9773F36A()l
extern _native void NETWORK_REMOVE_TRANSITION_INVITE(any* p0)l
extern _native void NETWORK_REMOVE_ALL_TRANSITION_INVITE()l
extern _native void UNK_0xC47352E7()l
extern _native bool NETWORK_INVITE_GAMERS(any* p0, any p1, any* p2, any* p3)l
extern _native bool NETWORK_HAS_INVITED_GAMER(any* p0)l
extern _native bool NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(any* p0)l
extern _native bool NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(any* p0)l
extern _native void UNK_0x0808D4CC(any* p0, any* p1)l
extern _native bool FILLOUT_PM_PLAYER_LIST(int* networkHandle, any p1, any p2)l
extern _native bool FILLOUT_PM_PLAYER_LIST_WITH_NAMES(any* p0, any* p1, any p2, any p3)l
extern _native bool USING_NETWORK_WEAPONTYPE(any p0)l
extern _native any UNK_0xA812B6CB()l
extern _native any UNK_0xF30E5814(any* p0, any p1)l
extern _native any UNK_0xC6609191()l
extern _native bool NETWORK_IS_CHATTING_IN_PLATFORM_PARTY(int* networkHandle)l
extern _native bool NETWORK_IS_IN_PARTY()l
extern _native bool NETWORK_IS_PARTY_MEMBER(int* networkHandle)l
extern _native any UNK_0x9156EFC0()l
extern _native any UNK_0x8FA6EE0E()l
extern _native void UNK_0x7F70C15A()l
extern _native void UNK_0x8179C48A(any p0)l
extern _native void UNK_0x41702C8A(any p0)l
extern _native int NETWORK_GET_RANDOM_INT()l
extern _native32(0xF9B6426D) int _NETWORK_GET_RANDOM_INT_IN_RANGE(int rangeStart, int rangeEnd)l
extern _native bool NETWORK_PLAYER_IS_CHEATER()l
extern _native any UNK_0x1720ABA6()l
extern _native bool NETWORK_PLAYER_IS_BADSPORT()l
extern _native bool UNK_0xF9A51B92(any p0, any p1, any p2)l
extern _native bool BAD_SPORT_PLAYER_LEFT_DETECTED(any* p0, any p1, any p2)l
extern _native void UNK_0x4818ACD0(any p0, any p1)l
extern _native void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(int lobbySize, bool p1, int playerId)l
extern _native bool NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT()l
extern _native32(0xCCD8C02D) int _NETWORK_GET_NUM_PARTICIPANTS_HOST()l
extern _native int NETWORK_GET_NUM_PARTICIPANTS()l
extern _native int NETWORK_GET_SCRIPT_STATUS()l
extern _native void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(int* vars, int numVars)l
extern _native void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(int* vars, int numVars)l
extern _native void UNK_0xA71A1D2A()l
extern _native bool UNK_0x0B739F53()l
extern _native int NETWORK_GET_PLAYER_INDEX(Player player)l
extern _native int NETWORK_GET_PARTICIPANT_INDEX(int index)l
extern _native Player NETWORK_GET_PLAYER_INDEX_FROM_PED(Ped ped)l
extern _native int NETWORK_GET_NUM_CONNECTED_PLAYERS()l
extern _native bool NETWORK_IS_PLAYER_CONNECTED(Player player)l
extern _native int UNK_0xF4F13B06()l
extern _native bool NETWORK_IS_PARTICIPANT_ACTIVE(any p0)l
extern _native bool NETWORK_IS_PLAYER_ACTIVE(Player player)l
extern _native bool NETWORK_IS_PLAYER_A_PARTICIPANT(any p0)l
extern _native bool NETWORK_IS_HOST_OF_THIS_SCRIPT()l
extern _native any NETWORK_GET_HOST_OF_THIS_SCRIPT()l
extern _native int NETWORK_GET_HOST_OF_SCRIPT(const char* scriptName, int p1, int p2)l
extern _native void NETWORK_SET_MISSION_FINISHED()l
extern _native bool NETWORK_IS_SCRIPT_ACTIVE(const char* scriptName, any p1, bool p2, any p3)l
extern _native int NETWORK_GET_NUM_SCRIPT_PARTICIPANTS(any* p0, any p1, any p2)l
extern _native any UNK_0xDB8B5D71()l
extern _native bool UNK_0xCEA55F4C(Player p0, any* p1, any p2)l
extern _native void UNK_0x8DCFE77D()l
extern _native void UNK_0x331D9A27()l
extern _native Player PARTICIPANT_ID()l
extern _native int PARTICIPANT_ID_TO_INT()l
extern _native int NETWORK_GET_DESTROYER_OF_NETWORK_ID(int netId, Hash* weaponHash)l
extern _native32(0x28A45454) bool _NETWORK_GET_DESROYER_OF_ENTITY(any p0, any p1, Hash* p2)l
extern _native Entity NETWORK_GET_ENTITY_KILLER_OF_PLAYER(Player player, Hash* weaponHash)l
extern _native void NETWORK_RESURRECT_LOCAL_PLAYER(vector3 vec, float heading, bool unk, bool changetime)l
extern _native void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(int time)l
extern _native bool NETWORK_IS_LOCAL_PLAYER_INVINCIBLE()l
extern _native void NETWORK_DISABLE_INVINCIBLE_FLASHING(int player, bool p1)l
extern _native void UNK_0xB72F086D(any p0)l
extern _native bool UNK_0xEDA68956(Entity p0)l
extern _native int NETWORK_GET_NETWORK_ID_FROM_ENTITY(Entity entity)l
extern _native Entity NETWORK_GET_ENTITY_FROM_NETWORK_ID(int netId)l
extern _native bool NETWORK_GET_ENTITY_IS_NETWORKED(Entity entity)l
extern _native bool NETWORK_GET_ENTITY_IS_LOCAL(Entity entity)l
extern _native void NETWORK_REGISTER_ENTITY_AS_NETWORKED(Entity entity)l
extern _native void NETWORK_UNREGISTER_NETWORKED_ENTITY(Entity entity)l
extern _native bool NETWORK_DOES_NETWORK_ID_EXIST(int netID)l
extern _native bool NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(Entity entity)l
extern _native bool NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(int netId)l
extern _native bool NETWORK_HAS_CONTROL_OF_NETWORK_ID(int netId)l
extern _native bool NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity entity)l
extern _native bool NETWORK_REQUEST_CONTROL_OF_DOOR(int doorID)l
extern _native bool NETWORK_HAS_CONTROL_OF_ENTITY(Entity entity)l
extern _native bool NETWORK_HAS_CONTROL_OF_PICKUP(Pickup pickup)l
extern _native bool NETWORK_HAS_CONTROL_OF_DOOR(int doorID)l
extern _native int VEH_TO_NET(Vehicle vehicle)l
extern _native int PED_TO_NET(Ped ped)l
extern _native int OBJ_TO_NET(Object object)l
extern _native Vehicle NET_TO_VEH(int netHandle)l
extern _native Ped NET_TO_PED(int netHandle)l
extern _native Object NET_TO_OBJ(int netHandle)l
extern _native Entity NET_TO_ENT(int netHandle)l
extern _native bool NETWORK_GAMERTAG_FROM_HANDLE_PENDING()l
extern _native bool NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED()l
extern _native void NETWORK_SHOW_PROFILE_UI(int* networkHandle)l
extern _native const char* NETWORK_PLAYER_GET_NAME(Player player)l
extern _native const char* NETWORK_PLAYER_GET_USERID(Player player, int* userID)l
extern _native bool NETWORK_PLAYER_IS_ROCKSTAR_DEV(Player player)l
extern _native bool UNK_0xD265B049(any p0)l
extern _native bool NETWORK_IS_INACTIVE_PROFILE(any* p0)l
extern _native int NETWORK_GET_MAX_FRIENDS()l
extern _native int NETWORK_GET_FRIEND_COUNT()l
extern _native const char* NETWORK_GET_FRIEND_NAME(Player player)l
extern _native bool NETWORK_IS_FRIEND_ONLINE(const char* name)l
extern _native any NETWORK_IS_PENDING_FRIEND(any p0)l
extern _native any NETWORK_IS_ADDING_FRIEND()l
extern _native bool NETWORK_ADD_FRIEND(any* p0, const char* p1)l
extern _native bool NETWORK_IS_FRIEND_INDEX_ONLINE(int friendIndex)l
extern _native bool UNK_0xB802B671(any p0)l
extern _native bool NETWORK_CAN_SET_WAYPOINT()l
extern _native any UNK_0x5C0AB2A9(any p0)l
extern _native any UNK_0x9A176B6E()l
extern _native bool NETWORK_HAS_HEADSET()l
extern _native void UNK_0x5C05B7E1(bool p0)l
extern _native bool NETWORK_GAMER_HAS_HEADSET(any* p0)l
extern _native bool NETWORK_IS_GAMER_TALKING(int* p0)l
extern _native bool NETWORK_CAN_COMMUNICATE_WITH_GAMER(int* player)l
extern _native bool NETWORK_IS_GAMER_MUTED_BY_ME(int* p0)l
extern _native bool NETWORK_AM_I_MUTED_BY_GAMER(any* p0)l
extern _native bool NETWORK_IS_GAMER_BLOCKED_BY_ME(any* p0)l
extern _native bool NETWORK_AM_I_BLOCKED_BY_GAMER(any* p0)l
extern _native bool NETWORK_IS_PLAYER_TALKING(Player player)l
extern _native bool NETWORK_PLAYER_HAS_HEADSET(Player player)l
extern _native bool NETWORK_IS_PLAYER_MUTED_BY_ME(Player player)l
extern _native bool NETWORK_AM_I_MUTED_BY_PLAYER(Player player)l
extern _native bool NETWORK_IS_PLAYER_BLOCKED_BY_ME(Player player)l
extern _native bool NETWORK_AM_I_BLOCKED_BY_PLAYER(Player player)l
extern _native float NETWORK_GET_PLAYER_LOUDNESS(any p0)l
extern _native void NETWORK_SET_TALKER_PROXIMITY(float p0)l
extern _native any NETWORK_GET_TALKER_PROXIMITY()l
extern _native void NETWORK_SET_VOICE_ACTIVE(bool toggle)l
extern _native void UNK_0x1A3EA6CD(bool p0)l
extern _native void NETWORK_OVERRIDE_TRANSITION_CHAT(bool p0)l
extern _native void NETWORK_SET_TEAM_ONLY_CHAT(bool toggle)l
extern _native void UNK_0xC8CC9E75(int team, bool toggle)l
extern _native void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(bool toggle)l
extern _native void UNK_0xC9DDA85B(bool p0)l
extern _native void UNK_0xD33AFF79(bool p0)l
extern _native void UNK_0x4FFEFE43(bool p0)l
extern _native void NETWORK_OVERRIDE_CHAT_RESTRICTIONS(Player player, bool toggle)l
extern _native void UNK_0x2F98B405(bool p0)l
extern _native void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(Player player, bool toggle)l
extern _native void UNK_0x1BCD3DDF(bool p0)l
extern _native void NETWORK_SET_VOICE_CHANNEL(any p0)l
extern _native void NETWORK_CLEAR_VOICE_CHANNEL()l
extern _native bool IS_NETWORK_VEHICLE_BEEN_DAMAGED_BY_ANY_OBJECT(vector3 vec)l
extern _native void UNK_0x7F9B9052()l
extern _native void UNK_0x7BBEA8CF(any p0)l
extern _native void UNK_0xE797A4B6(any p0)l
extern _native void UNK_0x92268BB5(Player p0, float* p1, float* p2)l
extern _native void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME()l
extern _native void NETWORK_SET_FRIENDLY_FIRE_OPTION(bool toggle)l
extern _native void NETWORK_SET_RICH_PRESENCE(any p0, any p1, any p2, any p3)l
extern _native void UNK_0x017E6777(any p0, any p1)l
extern _native int NETWORK_GET_TIMEOUT_TIME()l
extern _native void UNK_0xBE6A30C3(Player player, vector3 vec, bool p4, bool p5)l
extern _native void UNK_0x22E03AD0(Player player, bool p1)l
extern _native void UNK_0xCEAE5AFC(Entity entity)l
extern _native32(0xF5F4BD95) bool _NETWORK_PLAYER_IS_IN_CLAN()l
extern _native bool UNK_0x54E79E9C(int* clanDesc, int bufferSize)l
extern _native32(0x807B3450) int _GET_NUM_MEMBERSHIP_DESC()l
extern _native bool NETWORK_CLAN_GET_MEMBERSHIP_DESC(int* memberDesc, int p1)l
extern _native bool NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(any* p0)l
extern _native32(0x83ED8E08) bool _NETWORK_IS_CLAN_MEMBERSHIP_FINISHED_DOWNLOADING()l
extern _native bool NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE(int* p0)l
extern _native int NETWORK_CLAN_GET_MEMBERSHIP_COUNT(int* p0)l
extern _native bool NETWORK_CLAN_GET_MEMBERSHIP_VALID(int* p0, any p1)l
extern _native bool NETWORK_CLAN_GET_MEMBERSHIP(int* p0, int* clanMembership, int p2)l
extern _native bool NETWORK_CLAN_JOIN(int clanDesc)l
extern _native32(0xBDA90BAC) bool _NETWORK_CLAN_ANIMATION(const char* animDict, const char* animName)l
extern _native bool UNK_0x8E952B12(int p0, const char* p1)l
extern _native any UNK_0x966C90FD()l
extern _native bool UNK_0xBA672146(any* p0, any* p1)l
extern _native bool UNK_0x7963FA4D(any p0)l
extern _native bool UNK_0x88B13CDC(any p0, any* p1)l
extern _native void UNK_0xD6E3D5EA(any p0)l
extern _native any NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR()l
extern _native void NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL()l
extern _native bool NETWORK_GET_PRIMARY_CLAN_DATA_START(any* p0, any p1)l
extern _native any NETWORK_GET_PRIMARY_CLAN_DATA_PENDING()l
extern _native any NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS()l
extern _native bool NETWORK_GET_PRIMARY_CLAN_DATA_NEW(any* p0, any* p1)l
extern _native void SET_NETWORK_ID_CAN_MIGRATE(int netId, bool toggle)l
extern _native void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int netId, bool toggle)l
extern _native32(0x4D15FDB1) void _SET_NETWORK_ID_SYNC_TO_PLAYER(int netId, Player player, bool toggle)l
extern _native void NETWORK_SET_ENTITY_CAN_BLEND(Entity entity, bool toggle)l
extern _native32(0x09CBC4B0) void _NETWORK_SET_ENTITY_VISIBLE_TO_NETWORK(Entity entity, bool toggle)l
extern _native void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(int netId, bool p1, bool p2)l
extern _native void UNK_0x00AE4E17(int netId, bool state)l
extern _native bool UNK_0xEA5176C0(int netId)l
extern _native void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(bool p0, bool p1)l
extern _native void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(bool p0)l
extern _native void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(bool p0)l
extern _native void SET_PLAYER_INVISIBLE_LOCALLY(Player player, bool toggle)l
extern _native void SET_PLAYER_VISIBLE_LOCALLY(Player player, bool toggle)l
extern _native void FADE_OUT_LOCAL_PLAYER(bool p0)l
extern _native void NETWORK_FADE_OUT_ENTITY(Entity entity, bool normal, bool slow)l
extern _native bool IS_PLAYER_IN_CUTSCENE(Player player)l
extern _native void SET_ENTITY_VISIBLE_IN_CUTSCENE(any p0, bool p1, bool p2)l
extern _native void SET_ENTITY_LOCALLY_INVISIBLE(Entity entity)l
extern _native void SET_ENTITY_LOCALLY_VISIBLE(Entity entity)l
extern _native bool IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(int netID)l
extern _native void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(int netID, bool p1)l
extern _native bool IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(float p0, float p1, float p2, float p3)l
extern _native bool IS_SPHERE_VISIBLE_TO_PLAYER(any p0, float p1, float p2, float p3, float p4)l
extern _native void RESERVE_NETWORK_MISSION_OBJECTS(int p0)l
extern _native void RESERVE_NETWORK_MISSION_PEDS(int p0)l
extern _native void RESERVE_NETWORK_MISSION_VEHICLES(int p0)l
extern _native bool CAN_REGISTER_MISSION_OBJECTS(int p0)l
extern _native bool CAN_REGISTER_MISSION_PEDS(int p0)l
extern _native bool CAN_REGISTER_MISSION_VEHICLES(int p0)l
extern _native bool CAN_REGISTER_MISSION_ENTITIES(int p0, any p1, any p2, any p3)l
extern _native int GET_NUM_RESERVED_MISSION_OBJECTS(bool p0)l
extern _native int GET_NUM_RESERVED_MISSION_PEDS(bool p0)l
extern _native int GET_NUM_RESERVED_MISSION_VEHICLES(bool p0)l
extern _native int UNK_0x603FA104(bool p0)l
extern _native int UNK_0xD8FEC4F8(bool p0)l
extern _native int UNK_0x20527695(bool p0)l
extern _native any UNK_0x8687E285()l
extern _native any UNK_0x744AC008()l
extern _native any UNK_0xC3A12135()l
extern _native any UNK_0x6A036061()l
extern _native int GET_NETWORK_TIME()l
extern _native int UNK_0x98AA48E5()l
extern _native bool HAS_NETWORK_TIME_STARTED()l
extern _native int GET_TIME_OFFSET(int timeA, int timeB)l
extern _native bool IS_TIME_LESS_THAN(int timeA, int timeB)l
extern _native bool IS_TIME_MORE_THAN(int timeA, int timeB)l
extern _native bool IS_TIME_EQUAL_TO(int timeA, int timeB)l
extern _native int GET_TIME_DIFFERENCE(int timeA, int timeB)l
extern _native const char* GET_TIME_AS_STRING(int time)l
extern _native32(0xF2FDF2E0) int _GET_POSIX_TIME()l
extern _native32(0xBB7CCE49) void _GET_DATE_AND_TIME_FROM_UNIX_EPOCH(int unixEpoch, any* timeStructure)l
extern _native void NETWORK_SET_IN_SPECTATOR_MODE(bool toggle, Ped playerPed)l
extern _native void UNK_0x54058F5F(bool p0, any p1, bool p2)l
extern _native void UNK_0xA7E36020(bool p0)l
extern _native void UNK_0x64235620(bool p0, any p1)l
extern _native bool NETWORK_IS_IN_SPECTATOR_MODE()l
extern _native void NETWORK_SET_IN_MP_CUTSCENE(bool p0, bool p1)l
extern _native bool NETWORK_IS_IN_MP_CUTSCENE()l
extern _native bool NETWORK_IS_PLAYER_IN_MP_CUTSCENE(Player player)l
extern _native void SET_NETWORK_VEHICLE_RESPOT_TIMER(int netId, any p1)l
extern _native void UNK_0xEA235081(Entity entity, bool p1)l
extern _native void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(bool toggle)l
extern _native void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag)l
extern _native32(0xBFFE8B5C) void _NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA(int netScene, const char* animDict, const char* animName)l
extern _native void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(int netScene, Entity entity, int bone)l
extern _native void NETWORK_START_SYNCHRONISED_SCENE(int netScene)l
extern _native void NETWORK_STOP_SYNCHRONISED_SCENE(int netScene)l
extern _native32(0x16AED87B) int _NETWORK_UNLINK_NETWORKED_SYNCHRONISED_SCENE(int netScene)l
extern _native any UNK_0x0679CE71(int p0, any p1)l
extern _native bool UNK_0xC62E77B3(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, int flags)l
extern _native bool UNK_0x74D6B13C(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, int flags)l
extern _native any UNK_0x90700C7D(any* p0)l
extern _native void UNK_0x44BFB619()l
extern _native void NETWORK_GET_RESPAWN_RESULT(int randomInt, vector3* coordinates, float* heading)l
extern _native any UNK_0x03287FD2(any p0)l
extern _native void UNK_0x408A9436()l
extern _native void UNK_0xFFB2ADA1(any p0, any p1)l
extern _native void NETWORK_END_TUTORIAL_SESSION()l
extern _native any NETWORK_IS_IN_TUTORIAL_SESSION()l
extern _native any UNK_0x755A2B3E()l
extern _native any UNK_0xA003C40B()l
extern _native any UNK_0x5E1020CC(any p0)l
extern _native32(0xE66A0B40) bool _NETWORK_IS_PLAYER_EQUAL_TO_INDEX(Player player, int index)l
extern _native void UNK_0x72052DB3(any p0, bool p1)l
extern _native bool UNK_0xB0313590(any p0)l
extern _native void NETWORK_OVERRIDE_CLOCK_TIME(int Hours, int Minutes, int Seconds)l
extern _native void UNK_0xC4AEAF49()l
extern _native any UNK_0x2465296D()l
extern _native any NETWORK_ADD_ENTITY_AREA(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native any UNK_0x4C2C2B12(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native bool NETWORK_REMOVE_ENTITY_AREA(any p0)l
extern _native bool UNK_0x69956127(any p0)l
extern _native bool UNK_0xCB1CD6D3(any p0)l
extern _native bool UNK_0xC6D53AA0(any p0)l
extern _native32(0x155465EE) void _NETWORK_SET_NETWORK_ID_DYNAMIC(int netID, bool toggle)l
extern _native32(0x29532731) bool _NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS()l
extern _native void NETWORK_REQUEST_CLOUD_TUNABLES()l
extern _native any UNK_0x231CFD12()l
extern _native bool NETWORK_DOES_TUNABLE_EXIST(const char* tunableContext, const char* tunableName)l
extern _native bool NETWORK_ACCESS_TUNABLE_INT(const char* tunableContext, const char* tunableName, int* value)l
extern _native bool NETWORK_ACCESS_TUNABLE_FLOAT(const char* tunableContext, const char* tunableName, float* value)l
extern _native bool NETWORK_ACCESS_TUNABLE_BOOL(const char* tunableContext, const char* tunableName)l
extern _native32(0xA78571CA) int _GET_TUNABLES_CONTENT_MODIFIER_ID(Hash contentHash)l
extern _native any UNK_0x053BB329()l
extern _native void NETWORK_RESET_BODY_TRACKER()l
extern _native any UNK_0x17CBC608()l
extern _native bool UNK_0xBFAA349B(any p0)l
extern _native bool UNK_0xBEB7281A(Ped ped, Player player)l
extern _native any NETWORK_EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible, bool p3)l
extern _native void UNK_0xBC54371B(Entity entity)l
extern _native void UNK_0x644141C5(Ped ped, vector3 vec, float p4)l
extern _native void NETWORK_SET_PROPERTY_ID(any p0)l
extern _native void NETWORK_CLEAR_PROPERTY_ID()l
extern _native void UNK_0x53C9563C(int p0)l
extern _native void UNK_0x6B97075B(bool p0)l
extern _native any UNK_0x965EA007()l
extern _native any UNK_0xEEFC8A55()l
extern _native void UNK_0x866D1B67(any p0)l
extern _native any UNK_0xED4A272F()l
extern _native any UNK_0x4ACF110C(any p0)l
extern _native any UNK_0x1AA3A0D5(any p0)l
extern _native any UNK_0x37877757(any p0)l
extern _native any UNK_0x1CF89DA5(any p0)l
extern _native any UNK_0x16E53875(any p0, any p1)l
extern _native void UNK_0x365C50EE(any p0, any p1)l
extern _native any UNK_0x25E2DBA9()l
extern _native void SET_STORE_ENABLED(bool toggle)l
extern _native bool UNK_0x1FDC75DC(any p0)l
extern _native void UNK_0xCA7A0A49()l
extern _native any UNK_0x44A58B0A(any p0)l
extern _native any UNK_0xD32FA11F()l
extern _native void UNK_0xA7FA70AE()l
extern _native void UNK_0xCC7DCE24()l
extern _native any UNK_0x70F6D3AD()l
extern _native any UNK_0x2B7B57B3(any* p0)l
extern _native bool UNK_0xBAF52DD8(any p0)l
extern _native bool UNK_0x9B9AFFF1(any p0)l
extern _native32(0xC38E9DB0) void _DOWNLOAD_CHECK()l
extern _native any UNK_0x32A4EB22()l
extern _native any NETWORK_ENABLE_MOTION_DRUGGED()l
extern _native bool UNK_0x08243B79(any* p0, any* p1)l
extern _native any UNK_0x798D6C27()l
extern _native any UNK_0xE69E8D0D()l
extern _native any UNK_0x742075FE()l
extern _native any UNK_0xCE569932()l
extern _native any UNK_0x82146BE9()l
extern _native void UNK_0x133FF2D5()l
extern _native bool UNK_0xCBA7242F(any p0, any p1, any* p2, any p3, any p4, any p5)l
extern _native bool UNK_0xDED82A6E(any* p0, bool p1, any* p2)l
extern _native bool UNK_0x40CF0783(any p0, any p1, any* p2, any p3)l
extern _native bool UNK_0x4609D596(any p0, any p1, any* p2, any* p3)l
extern _native bool UNK_0x4C2C0D1F(any p0, any p1, any* p2, any* p3)l
extern _native bool UNK_0x9EFBD5D1(any p0, any p1, any* p2, any* p3)l
extern _native bool UNK_0xA6D8B798(any p0, any p1, any p2, any* p3, any* p4)l
extern _native bool UNK_0x67E74842(any p0, any p1, any p2, any* p3, any* p4)l
extern _native bool SET_BALANCE_ADD_MACHINE(any* p0, any* p1)l
extern _native bool SET_BALANCE_ADD_MACHINES(any* p0, any p1, any* p2)l
extern _native bool UNK_0x37F5BD93(any p0, any p1, any* p2, any* p3)l
extern _native bool NETWORK_GET_BACKGROUND_LOADING_RECIPIENTS(any p0, any p1, any* p2, any* p3)l
extern _native bool UNK_0x87D1E6BD(any p0, any p1, any* p2, any* p3)l
extern _native void UNK_0x021D5A94()l
extern _native any UNK_0x4908A514()l
extern _native any UNK_0x50296140()l
extern _native any UNK_0x3970B0DA()l
extern _native any UNK_0xC1487110()l
extern _native any UNK_0xCC2356E3()l
extern _native any UNK_0x2DE69817()l
extern _native any UNK_0x81BD8D3B()l
extern _native any UNK_0x8E1D8F78()l
extern _native void UNK_0x0D35DD93()l
extern _native32(0x8F3137E6) const char* _GET_CONTENT_USER_ID(int p0)l
extern _native any UNK_0xB9137BA7(any p0)l
extern _native bool UNK_0x9FEEAA9C(any p0)l
extern _native32(0x5E8A7559) int _GET_CONTENT_CATEGORY(int p0)l
extern _native32(0x331AEABF) const char* _GET_CONTENT_ID(any p0)l
extern _native32(0x0E5E8E5C) const char* _GET_ROOT_CONTENT_ID(any p0)l
extern _native any UNK_0xA5A0C695(any p0)l
extern _native32(0x91534C6E) int _GET_CONTENT_DESCRIPTION_HASH(any p0)l
extern _native any UNK_0x744A9EA5(any p0, any p1)l
extern _native void UNK_0xA19A238D(any p0, any* p1)l
extern _native32(0xFF7D44E6) any _GET_CONTENT_FILE_VERSION(any p0, any p1)l
extern _native any UNK_0xA2C5BD9D(any p0)l
extern _native bool UNK_0xA850DDE1(any p0)l
extern _native bool UNK_0x8F6754AE(any p0)l
extern _native any UNK_0x1E34953F(any p0, any p1)l
extern _native any UNK_0x771FE190(any p0, any p1)l
extern _native any UNK_0x3276D9D3(any p0, any p1)l
extern _native any UNK_0x41A0FB02(any p0, any p1)l
extern _native bool UNK_0x11DC0F27(any p0)l
extern _native bool UNK_0x0DEB3F5A(any p0)l
extern _native any UNK_0x84315226(any p0, any p1)l
extern _native any UNK_0x38FC2EEB(any* p0, any* p1, any p2, any p3, any p4)l
extern _native any UNK_0x1C4F9FDB(any p0)l
extern _native bool UNK_0xA69AE16C(any p0)l
extern _native bool UNK_0xF50BC67A(any p0)l
extern _native bool UNK_0xB3BBD241(any p0)l
extern _native any UNK_0x70A2845C(any p0, any p1)l
extern _native bool UNK_0x346B506C(any p0)l
extern _native void UNK_0x0095DB71()l
extern _native bool UNK_0xAD334B40(any* p0, any* p1, any* p2)l
extern _native bool UNK_0x980D45D7(any* p0, bool p1, any* p2)l
extern _native bool UNK_0x48CCC328(any* p0, bool p1, any* p2)l
extern _native any UNK_0x8E664EFD()l
extern _native any UNK_0x611E0BE2()l
extern _native any UNK_0xF0211AC1()l
extern _native any UNK_0x1F0DD8AF()l
extern _native void UNK_0x405ECA16()l
extern _native bool UNK_0x9567392B(any* p0, any* p1)l
extern _native any UNK_0xF79FFF3C()l
extern _native any UNK_0xA7F3F82B()l
extern _native any UNK_0x410C61D1()l
extern _native bool UNK_0x0D4F845D(any p0)l
extern _native void UNK_0xE13C1F7F()l
extern _native void UNK_0x213C6D36(bool p0)l
extern _native void UNK_0x511E6F50(bool p0)l
extern _native bool UNK_0xB4668B23(any p0)l
extern _native bool UNK_0x30B51753(any* p0, any p1, any p2)l
extern _native any UNK_0x02DAD93F()l
extern _native bool UNK_0x2D947814(any p0)l
extern _native any UNK_0x37A28C26()l
extern _native any UNK_0x11E8B5CD()l
extern _native any UNK_0x429AEAB3()l
extern _native int TEXTURE_DOWNLOAD_REQUEST(int* PlayerHandle, const char* FilePath, const char* Name, bool p3)l
extern _native any UNK_0x1856D008(any* p0, any* p1, bool p2)l
extern _native any UNK_0x68C9AF69(any* p0, any p1, any p2, any p3, any* p4, bool p5)l
extern _native void TEXTURE_DOWNLOAD_RELEASE(int p0)l
extern _native bool TEXTURE_DOWNLOAD_HAS_FAILED(int p0)l
extern _native const char* TEXTURE_DOWNLOAD_GET_NAME(int p0)l
extern _native any UNK_0x03225BA3(any p0)l
extern _native any UNK_0x4DEBC227()l
extern _native bool NETWORK_IS_CABLE_CONNECTED()l
extern _native any UNK_0x0CA1167F()l
extern _native any UNK_0x424C6E27()l
extern _native32(0xD3BBE42F) bool _IS_ROCKSTAR_BANNED()l
extern _native32(0xBDBB5948) bool _IS_SOCIALCLUB_BANNED()l
extern _native32(0x97287D68) bool _CAN_PLAY_ONLINE()l
extern _native any UNK_0xC6EA802E()l
extern _native bool UNK_0xFD261E30(any p0)l
extern _native bool UNK_0x8570DD34(any p0, any* p1, any* p2)l
extern _native void UNK_0x273C6180()l
extern _native void UNK_0x371BBA08()l
extern _native void UNK_0xA100CC97(bool p0)l
extern _native void UNK_0xBB2D33D3(any p0, bool p1)l
#pragma endregion //}
#pragma region NETWORKCASH //{
extern _native void NETWORK_INITIALIZE_CASH(int p0, int p1)l
extern _native void NETWORK_DELETE_CHARACTER(int characterIndex, bool p1, bool p2)l
extern _native void NETWORK_CLEAR_CHARACTER_WALLET(any p0)l
extern _native void NETWORK_GIVE_PLAYER_JOBSHARE_CASH(int amount, int* networkHandle)l
extern _native void NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(int value, int* networkHandle)l
extern _native any UNK_0xA27B9FE8()l
extern _native void NETWORK_REFUND_CASH(int index, const char* context, const char* reason, bool unk)l
extern _native bool NETWORK_MONEY_CAN_BET(any p0, bool p1, bool p2)l
extern _native bool NETWORK_CAN_BET(any p0)l
extern _native any NETWORK_EARN_FROM_PICKUP(int amount)l
extern _native32(0x33C20BC4) void _NETWORK_EARN_FROM_GANG_PICKUP(int amount)l
extern _native32(0x30B3EC0A) void _NETWORK_EARN_FROM_ARMOUR_TRUCK(int amount)l
extern _native void NETWORK_EARN_FROM_CRATE_DROP(int amount)l
extern _native void NETWORK_EARN_FROM_BETTING(int amount, const char* p1)l
extern _native void NETWORK_EARN_FROM_JOB(int amount, const char* p1)l
extern _native void NETWORK_EARN_FROM_MISSION_H(int amount, const char* heistHash)l
extern _native void NETWORK_EARN_FROM_CHALLENGE_WIN(any p0, any* p1, bool p2)l
extern _native void NETWORK_EARN_FROM_BOUNTY(int amount, int* networkHandle, any* p2, any p3)l
extern _native void NETWORK_EARN_FROM_IMPORT_EXPORT(any p0, any p1)l
extern _native void NETWORK_EARN_FROM_HOLDUPS(int amount)l
extern _native void NETWORK_EARN_FROM_PROPERTY(int amount, Hash propertyName)l
extern _native void NETWORK_EARN_FROM_AI_TARGET_KILL(any p0, any p1)l
extern _native void NETWORK_EARN_FROM_NOT_BADSPORT(int amount)l
extern _native void NETWORK_EARN_FROM_ROCKSTAR(int amount)l
extern _native void NETWORK_EARN_FROM_VEHICLE(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native void NETWORK_EARN_FROM_PERSONAL_VEHICLE(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native bool NETWORK_CAN_SPEND_MONEY(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native void NETWORK_BUY_ITEM(Ped player, Hash item, any p2, any p3, bool p4, const char* item_name, any p6, any p7, any p8, bool p9)l
extern _native void NETWORK_SPENT_TAXI(int amount, bool p1, bool p2)l
extern _native void NETWORK_PAY_EMPLOYEE_WAGE(any p0, bool p1, bool p2)l
extern _native void NETWORK_PAY_UTILITY_BILL(any p0, bool p1, bool p2)l
extern _native void NETWORK_PAY_MATCH_ENTRY_FEE(int value, int* p1, bool p2, bool p3)l
extern _native void NETWORK_SPENT_BETTING(any p0, any p1, any* p2, bool p3, bool p4)l
extern _native void NETWORK_SPENT_IN_STRIPCLUB(any p0, bool p1, any p2, bool p3)l
extern _native void NETWORK_BUY_HEALTHCARE(int cost, bool p1, bool p2)l
extern _native void NETWORK_BUY_AIRSTRIKE(int cost, bool p1, bool p2)l
extern _native void NETWORK_BUY_HELI_STRIKE(int cost, bool p1, bool p2)l
extern _native void NETWORK_SPENT_AMMO_DROP(any p0, bool p1, bool p2)l
extern _native void NETWORK_BUY_BOUNTY(int amount, Player victim, bool p2, bool p3)l
extern _native void NETWORK_BUY_PROPERTY(float propertyCost, Hash propertyName, bool p2, bool p3)l
extern _native void NETWORK_SPENT_HELI_PICKUP(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_BOAT_PICKUP(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_BULL_SHARK(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_CASH_DROP(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_HIRE_MUGGER(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_ROBBED_BY_MUGGER(int amount, bool p1, bool p2)l
extern _native void NETWORK_SPENT_HIRE_MERCENARY(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_BUY_WANTEDLEVEL(any p0, any* p1, bool p2, bool p3)l
extern _native void NETWORK_SPENT_BUY_OFFTHERADAR(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_BUY_REVEAL_PLAYERS(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_CARWASH(any p0, any p1, any p2, bool p3, bool p4)l
extern _native void NETWORK_SPENT_CINEMA(any p0, any p1, bool p2, bool p3)l
extern _native void NETWORK_SPENT_TELESCOPE(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_HOLDUPS(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_BUY_PASSIVE_MODE(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_PROSTITUTES(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_ARREST_BAIL(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(int amount, Hash vehicleModel, int* networkHandle, bool notBankrupt, bool hasTheMoney)l
extern _native void NETWORK_SPENT_CALL_PLAYER(any p0, any* p1, bool p2, bool p3)l
extern _native void NETWORK_SPENT_BOUNTY(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_FROM_ROCKSTAR(int bank, bool p1, bool p2)l
extern _native const char* PROCESS_CASH_GIFT(int* p0, int* p1, const char* p2)l
extern _native void NETWORK_SPENT_PLAYER_HEALTHCARE(any p0, any p1, bool p2, bool p3)l
extern _native void NETWORK_SPENT_NO_COPS(any p0, bool p1, bool p2)l
extern _native void NETWORK_SPENT_REQUEST_JOB(any p0, bool p1, bool p2)l
extern _native void NETWORK_BUY_FAIRGROUND_RIDE(int amountSpent, any p1, bool p2, bool p3)l
extern _native int NETWORK_GET_VC_BANK_BALANCE()l
extern _native int NETWORK_GET_VC_WALLET_BALANCE(int character)l
extern _native int NETWORK_GET_VC_BALANCE()l
extern _native bool NETWORK_CAN_RECEIVE_PLAYER_CASH(any p0, any p1, any p2, any p3)l
extern _native any UNK_0x8B755993(any p0)l
extern _native bool UNK_0x8F266745(any p0)l
extern _native any UNK_0x531E4892(any p0)l
extern _native any UNK_0xB96C7ABE(any p0)l
#pragma endregion //}
#pragma region DLC1 //{
extern _native32(0x71D0CF3E) int _GET_NUM_DECORATIONS(int character)l
extern _native bool UNK_0x2E9D628C(int p0, int p1, int* outComponent)l
extern _native void INIT_SHOP_PED_COMPONENT(int* outComponent)l
extern _native void INIT_SHOP_PED_PROP(int* outProp)l
extern _native int UNK_0xC937FF3D(int p0, int p1, int p2, int p3)l
extern _native32(0x594E862C) int _GET_NUM_PROPS_FROM_OUTFIT(int character, int p1, int p2, bool p3, int p4, int componentId)l
extern _native void GET_SHOP_PED_QUERY_COMPONENT(int componentId, int* outComponent)l
extern _native void GET_SHOP_PED_COMPONENT(Hash p0, any* p1)l
extern _native void GET_SHOP_PED_QUERY_PROP(any p0, any* p1)l
extern _native Hash GET_HASH_NAME_FOR_COMPONENT(Entity entity, int componentId, int drawableVariant, int textureVariant)l
extern _native Hash GET_HASH_NAME_FOR_PROP(Entity entity, int componentId, int propIndex, int propTextureIndex)l
extern _native int UNK_0x159751B4(Hash componentHash)l
extern _native void GET_VARIANT_COMPONENT(Hash componentHash, int componentId, any* p2, any* p3, any* p4)l
extern _native32(0xCE70F183) int _GET_NUM_FORCED_COMPONENTS(Hash componentHash)l
extern _native void GET_FORCED_COMPONENT(Hash componentHash, int componentId, any* p2, any* p3, any* p4)l
extern _native bool UNK_0x8E2C7FD5(Hash componentHash, Hash drawableSlotHash, bool p2)l
extern _native int UNK_0x1ECD23E7(int character, bool p1)l
extern _native void GET_SHOP_PED_QUERY_OUTFIT(any p0, any* outfit)l
extern _native void GET_SHOP_PED_OUTFIT(any p0, any* p1)l
extern _native any GET_SHOP_PED_OUTFIT_LOCATE(any p0)l
extern _native bool UNK_0x6641A864(any p0, any p1, any* p2)l
extern _native32(0x818534AC) bool _GET_PROP_FROM_OUTFIT(any outfit, int slot, any* item)l
extern _native int GET_NUM_DLC_VEHICLES()l
extern _native Hash GET_DLC_VEHICLE_MODEL(int dlcVehicleIndex)l
extern _native bool GET_DLC_VEHICLE_DATA(int dlcVehicleIndex, int* outData)l
extern _native int GET_DLC_VEHICLE_FLAGS(int dlcVehicleIndex)l
extern _native int GET_NUM_DLC_WEAPONS()l
extern _native bool GET_DLC_WEAPON_DATA(int dlcWeaponIndex, int* outData)l
extern _native int GET_NUM_DLC_WEAPON_COMPONENTS(int dlcWeaponIndex)l
extern _native bool GET_DLC_WEAPON_COMPONENT_DATA(int dlcWeaponIndex, int dlcWeapCompIndex, int* ComponentDataPtr)l
extern _native32(0x06396058) bool _IS_DLC_DATA_EMPTY(int dlcData)l
extern _native bool IS_DLC_VEHICLE_MOD(int modData)l
extern _native int UNK_0x59352658(int modData)l
#pragma endregion //}
#pragma region DLC2 //{
extern _native bool IS_DLC_PRESENT(Hash dlcHash)l
extern _native bool UNK_0x881B1FDB()l
extern _native any UNK_0xC2169164()l
extern _native any UNK_0xF79A97F5()l
extern _native any UNK_0xF69B729C()l
extern _native bool GET_IS_LOADING_SCREEN_ACTIVE()l
extern _native32(0x6087C10C) bool _NULLIFY(any* variable, any unused)l
#pragma endregion //}
#pragma region SYSTEM //{
extern _native void WAIT(int ms)l
extern _native int START_NEW_SCRIPT(const char* scriptName, int stackSize)l
extern _native int START_NEW_SCRIPT_WITH_ARGS(const char* scriptName, any* args, int argCount, int stackSize)l
extern _native int START_NEW_SCRIPT_WITH_NAME_HASH(Hash scriptHash, int stackSize)l
extern _native int START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(Hash scriptHash, any* args, int argCount, int stackSize)l
extern _native int TIMERA()l
extern _native int TIMERB()l
extern _native void SETTIMERA(int value)l
extern _native void SETTIMERB(int value)l
extern _native float TIMESTEP()l
extern _native float SIN(float value)l
extern _native float COS(float value)l
extern _native float SQRT(float value)l
extern _native float POW(float base, float exponent)l
extern _native float VMAG(vector3 vec)l
extern _native float VMAG2(vector3 vec)l
extern _native float VDIST(vector3 vec_1, vector3 vec_2)l
extern _native float VDIST2(vector3 vec_1, vector3 vec_2)l
extern _native int SHIFT_LEFT(int value, int bitShift)l
extern _native int SHIFT_RIGHT(int value, int bitShift)l
extern _native int FLOOR(float value)l
extern _native int CEIL(float value)l
extern _native int ROUND(float value)l
extern _native float TO_FLOAT(int value)l
#pragma endregion //}
#pragma region DECORATOR //{
extern _native bool DECOR_SET_TIME(Entity entity, const char* propertyName, int value)l
extern _native bool DECOR_SET_BOOL(Entity entity, const char* propertyName, bool value)l
extern _native bool DECOR_SET_FLOAT(Entity entity, const char* propertyName, float value)l
extern _native bool DECOR_SET_INT(Entity entity, const char* propertyName, int value)l
extern _native bool DECOR_GET_BOOL(Entity entity, const char* propertyName)l
extern _native float DECOR_GET_FLOAT(Entity entity, const char* propertyName)l
extern _native int DECOR_GET_INT(Entity entity, const char* propertyName)l
extern _native bool DECOR_EXIST_ON(Entity entity, const char* propertyName)l
extern _native bool DECOR_REMOVE(Entity entity, const char* propertyName)l
extern _native void DECOR_REGISTER(const char* propertyName, int type)l
extern _native bool DECOR_IS_REGISTERED_AS_TYPE(const char* propertyName, int type)l
extern _native void DECOR_REGISTER_LOCK()l
#pragma endregion //}
#pragma region SOCIALCLUB //{
extern _native32(0x6BE5DF29) int _GET_TOTAL_SC_INBOX_IDS()l
extern _native32(0x5ECF955D) Hash _SC_INBOX_MESSAGE_INIT(int p0)l
extern _native32(0xD1ED1D48) bool _IS_SC_INBOX_VALID(int p0)l
extern _native32(0x19EE0CCB) bool _SC_INBOX_MESSAGE_POP(int p0)l
extern _native bool SC_INBOX_MESSAGE_GET_DATA_INT(int p0, const char* context, int* out)l
extern _native bool SC_INBOX_MESSAGE_GET_DATA_STRING(int p0, const char* context, const char* out)l
extern _native32(0xEBE420A4) bool _SC_INBOX_MESSAGE_PUSH(int p0)l
extern _native32(0x2C959AF9) const char* _SC_INBOX_MESSAGE_GET_STRING(int p0)l
extern _native void UNK_0x0B9A3512(int* p0)l
extern _native void UNK_0x75324674(const char* p0)l
extern _native bool SC_INBOX_MESSAGE_GET_UGCDATA(any p0, any* p1)l
extern _native bool UNK_0x628F489B(const char* p0)l
extern _native bool UNK_0xAB3346B5(any p0, int* p1)l
extern _native void SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST(Player* player)l
extern _native void SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST()l
extern _native void UNK_0xAF3C081B(const char* p0)l
extern _native void UNK_0x2FB9F53C(bool p0)l
extern _native any UNK_0x6C5738AB()l
extern _native any UNK_0x468668F0()l
extern _native bool UNK_0x90C74343(any p0, any p1)l
extern _native bool UNK_0x3ACE6D6B(any p0, any* p1)l
extern _native bool UNK_0x579B4510(any p0, float p1)l
extern _native bool UNK_0xDF45B2A7(const char* p0)l
extern _native32(0xDF084A6B) bool _SC_START_CHECK_STRING_TASK(const char* string, int* taskHandle)l
extern _native32(0xFFED3676) bool _SC_HAS_CHECK_STRING_TASK_COMPLETED(int taskHandle)l
extern _native32(0xA796D7A7) int _SC_GET_CHECK_STRING_STATUS(int taskHandle)l
extern _native any UNK_0x09497F31(any p0)l
extern _native int UNK_0x4D8A6521(any p0)l
extern _native bool UNK_0x7AA36406(const char* p0, int* p1)l
extern _native bool UNK_0xF379DCE4(any p0)l
extern _native any UNK_0x65D84665(any p0)l
extern _native any UNK_0xC96456BA()l
extern _native any UNK_0x8E7AEEB7(any* p0)l
extern _native bool UNK_0xE778B2A7(int p0, const char* p1, any* p2)l
extern _native bool UNK_0xCE7D50A8(int p0, const char* p1, any* p2)l
extern _native bool UNK_0xD26CCA46(any p0, any* p1)l
extern _native bool UNK_0x24D84334(any p0)l
extern _native bool UNK_0x8A023024(any p0, any p1)l
extern _native any UNK_0x1C65B038()l
extern _native bool UNK_0x4D4C37B3()l
extern _native bool UNK_0xAED95A6F(const char* p0, int* p1)l
extern _native void UNK_0x486867E6()l
#pragma endregion //}
#pragma region UNK //{
extern _native int UNK_0x106C8317()l
extern _native bool UNK_0xD87F3A9E()l
extern _native void UNK_0xC0B971EA(bool p0)l
extern _native any UNK_0x94BCAC7C()l
extern _native void UNK_0x7D90EEE5(bool p0)l
extern _native32(0x734CFEDA) bool _IS_UI_LOADING_MULTIPLAYER()l
extern _native void UNK_0x8C227332(bool p0)l
extern _native void UNK_0x5C350D78(bool p0)l
#pragma endregion //}
#pragma region UNK1 //{
#pragma endregion //}
#pragma region UNK2 //{
#pragma endregion //}
#pragma region UNK3 //{
#pragma endregion //}

/************ Console Only Natives ************/
extern _native bool NETWORK_IS_LOCAL_TALKING();

/************ Undocumented Console Only Natives ************
SC_INBOX_MESSAGE_GET_DATA_FLOAT
NETWORK_IS_LOCAL_TALKING
GET_NUMBER_OF_VEHICLE_MODEL_COLOURS
PLAY_STREAM_FROM_POSITION
NETWORK_GET_KILLER_OF_PLAYER
WAITUNPAUSED
WAITUNWARPED
GET_VEHICLE_MODEL_VALUE
NETWORK_GIVE_PLAYER_CASH
NETWORK_INVITE_GAMER
NETWORK_INVITE_GAMER_TO_TRANSITION
NETWORK_RECEIVE_PLAYER_CASH
TASK_VEHICLE_FOLLOW
CLEAR_TEXT_LABEL
GET_CURRENT_LANGUAGE
NETWORK_SET_PLAYER_MUTED
NETWORK_REMOVE_ALL_INVITES
IS_FLASH_LIGHT_ON
SET_ENTITY_ICON_ID_COLOR
SET_ENTITY_ICON_ID_VISIBILITY
ADD_ENTITY_ICON_BY_VECTOR
SET_VEHICLE_BRAKE
NETWORK_IS_ROCKSTAR_DEV
GET_PED_HEAD_OVERLAY
NETWORK_CHECK_GIVE_PLAYER_CASH
NETWORK_CHECK_RECEIVE_PLAYER_CASH
NETWORK_EARN_FROM_BANK_INTEREST
NETWORK_SPENT_BANK_INTEREST
SET_POI
SET_CONTROL_SHAKE
SET_POI_SPECIAL
NETWORK_GET_GAME_REGION
GET_SHOP_PED_PROP
GET_FORCED_PROP
GET_SHOP_PED_OUTFIT_PROP
GET_SHOP_PED_OUTFIT_COMPONENT
IS_CAM_TRANSITIONING
DOES_ENTITY_HAVE_ICON_ID
NETWORK_IS_UNLOCKED
REMOVE_VEHICLE_MOD_KIT
NETWORK_BUY_SMOKES
NETWORK_REMOVE_FOLLOWERS
NETWORK_HAS_FOLLOWER
NETWORK_RETAIN_FOLLOWERS
RESTORE_SCRIPT_VALUES_FOR_NETWORK_GAME
STORE_SCRIPT_VALUES_FOR_NETWORK_GAME
GET_ANIM_DURATION
GET_CUTSCENE_NAME
***********************************************************/


#undef _native
#undef _native32
