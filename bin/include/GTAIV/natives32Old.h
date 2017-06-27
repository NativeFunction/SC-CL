/*H**********************************************************************
* FILENAME :	natives32Old.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Native functions to be used with all GTAIV(1.0.4.0) targets and platforms of SC-CL.
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

#pragma region CHAR//{
extern _native bool ARE_ANY_CHARS_NEAR_CHAR(Ped ped, float radius)l
extern _native bool CAN_CHAR_SEE_DEAD_CHAR(Ped ped, Ped pednext)l
extern _native bool CELL_CAM_IS_CHAR_VISIBLE(Ped ped)l
extern _native bool CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Ped ped)l
extern _native bool DOES_CHAR_EXIST(Ped ped)l
extern _native bool GET_CHAR_ALLOWED_TO_RUN_ON_BOATS(Ped ped)l
extern _native bool GET_CHAR_ANIM_IS_EVENT(Ped ped, const char* AnimName0, const char* AnimName1, bool flag)l
extern _native bool GET_CHAR_MELEE_ACTION_FLAG0(Ped ped)l
extern _native bool GET_CHAR_MELEE_ACTION_FLAG1(Ped ped)l
extern _native bool GET_CHAR_MELEE_ACTION_FLAG2(Ped ped)l
extern _native bool GET_CHAR_MOVEMENT_ANIMS_BLOCKED(Ped ped)l
extern _native bool GET_CHAR_READY_TO_BE_EXECUTED(Ped ped)l
extern _native bool GET_CHAR_READY_TO_BE_STUNNED(Ped ped)l
extern _native bool GET_CHAR_SWIM_STATE(Ped ped, int *state)l
extern _native bool GET_CHAR_WALK_ALONGSIDE_LEADER_WHEN_APPROPRIATE(Ped ped)l
extern _native bool GET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING(Ped ped)l
extern _native bool GET_CHAR_WILL_TRY_TO_LEAVE_BOAT_AFTER_LEADER(Ped ped)l
extern _native bool GET_CHAR_WILL_TRY_TO_LEAVE_WATER(Ped ped)l
extern _native bool GET_CLOSEST_CHAR(float x, float y, float z, float radius, bool unknown1, bool unknown2, Ped *pPed)l
extern _native bool GET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT(Ped ped)l
extern _native bool HAS_CAR_BEEN_DAMAGED_BY_CHAR(Vehicle vehicle, Ped ped)l
extern _native bool HAS_CHAR_ANIM_FINISHED(Ped ped, const char* AnimName0, const char* AnimName1)l
extern _native bool HAS_CHAR_BEEN_ARRESTED(Ped ped)l
extern _native bool HAS_CHAR_BEEN_DAMAGED_BY_CHAR(Ped ped, Ped otherChar, bool unknownFalse)l
extern _native bool HAS_CHAR_BEEN_PHOTOGRAPHED(Ped ped)l
extern _native bool HAS_CHAR_SPOTTED_CHAR(Ped ped, Ped otherChar)l
extern _native bool HAS_CHAR_SPOTTED_CHAR_IN_FRONT(Ped ped, Ped otherChar)l
extern _native bool IS_ANY_CHAR_SHOOTING_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1, bool flag)l
extern _native bool IS_CHAR_ARMED(Ped ped, uint slot)l
extern _native bool IS_CHAR_DEAD(Ped ped)l
extern _native bool IS_CHAR_DUCKING(Ped ped)l
extern _native bool IS_CHAR_FACING_CHAR(Ped ped, Ped otherChar, float angle)l
extern _native bool IS_CHAR_FATALLY_INJURED(Ped ped)l
extern _native bool IS_CHAR_GESTURING(Ped ped)l
extern _native bool IS_CHAR_GETTING_IN_TO_A_CAR(Ped ped)l
extern _native bool IS_CHAR_GETTING_UP(Ped ped)l
extern _native bool IS_CHAR_HEALTH_GREATER(Ped ped, uint health)l
extern _native bool IS_CHAR_INJURED(Ped ped)l
extern _native bool IS_CHAR_IN_AIR(Ped ped)l
extern _native bool IS_CHAR_IN_ANGLED_AREA_2D(Ped ped, float x1, float y1, float x2, float y2, float unknown, bool unknownFalse)l
extern _native bool IS_CHAR_IN_ANGLED_AREA_3D(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, float unknown, bool unknownFalse)l
extern _native bool IS_CHAR_IN_ANY_BOAT(Ped ped)l
extern _native bool IS_CHAR_IN_ANY_CAR(Ped ped)l
extern _native bool IS_CHAR_IN_ANY_HELI(Ped ped)l
extern _native bool IS_CHAR_IN_ANY_PLANE(Ped ped)l
extern _native bool IS_CHAR_IN_ANY_TRAIN(Ped ped)l
extern _native bool IS_CHAR_IN_AREA_2D(Ped ped, float x1, float y1, float x2, float y2, bool unknownFalse)l
extern _native bool IS_CHAR_IN_AREA_3D(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, bool unknownFalse)l
extern _native bool IS_CHAR_IN_AREA_ON_FOOT_2D(Ped ped, float x1, float y1, float x2, float y2, bool unknownFalse)l
extern _native bool IS_CHAR_IN_FLYING_VEHICLE(Ped ped)l
extern _native bool IS_CHAR_IN_MELEE_COMBAT(Ped ped)l
extern _native bool IS_CHAR_IN_TAXI(Ped ped)l
extern _native bool IS_CHAR_IN_WATER(Ped ped)l
extern _native bool IS_CHAR_MALE(Ped ped)l
extern _native bool IS_CHAR_MODEL(Ped ped, uint model)l
extern _native bool IS_CHAR_ON_ANY_BIKE(Ped ped)l
extern _native bool IS_CHAR_ON_FIRE(Ped ped)l
extern _native bool IS_CHAR_ON_FOOT(Ped ped)l
extern _native bool IS_CHAR_ON_SCREEN(Ped ped)l
extern _native bool IS_CHAR_PLAYING_ANIM(Ped ped, const char* animSet, const char* animName)l
extern _native bool IS_CHAR_RESPONDING_TO_ANY_EVENT(Ped ped)l
extern _native bool IS_CHAR_RESPONDING_TO_EVENT(Ped ped, int eventid)l
extern _native bool IS_CHAR_SHOOTING(Ped ped)l
extern _native bool IS_CHAR_SHOOTING_IN_AREA(Ped ped, float x1, float y1, float x2, float y2, bool unknownFalse)l
extern _native bool IS_CHAR_SITTING_IDLE(Ped ped)l
extern _native bool IS_CHAR_SITTING_IN_ANY_CAR(Ped ped)l
extern _native bool IS_CHAR_SITTING_IN_CAR(Ped ped, Vehicle vehicle)l
extern _native bool IS_CHAR_STOPPED(Ped ped)l
extern _native bool IS_CHAR_STUCK_UNDER_CAR(Ped ped)l
extern _native bool IS_CHAR_SWIMMING(Ped ped)l
extern _native bool IS_CHAR_TOUCHING_CHAR(Ped ped, Ped otherChar)l
extern _native bool IS_CHAR_TOUCHING_OBJECT(Ped ped, Object obj)l
extern _native bool IS_CHAR_TOUCHING_OBJECT_ON_FOOT(Ped ped, Object obj)l
extern _native bool IS_CHAR_TRYING_TO_ENTER_A_LOCKED_CAR(Ped ped)l
extern _native bool IS_CHAR_USING_ANY_SCENARIO(Ped ped)l
extern _native bool IS_CHAR_USING_MAP_ATTRACTOR(Ped ped)l
extern _native bool IS_CHAR_USING_SCENARIO(Ped ped, const char* scenarioName)l
extern _native bool IS_CHAR_VISIBLE(Ped ped)l
extern _native bool IS_CHAR_WAITING_FOR_WORLD_COLLISION(Ped ped)l
extern _native bool LOCATE_CHAR_ANY_MEANS_2D(Ped ped, float x0, float y0, float x1, float y1, bool flag)l
extern _native bool LOCATE_CHAR_ANY_MEANS_3D(Ped ped, float x0, float y0, float z0, float x1, float y1, float z1, bool flag)l
extern _native bool LOCATE_CHAR_ANY_MEANS_CAR_2D(Ped ped, Vehicle car, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_ANY_MEANS_CAR_3D(Ped ped, Vehicle car, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_ANY_MEANS_CHAR_2D(Ped ped, Ped pednext, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_ANY_MEANS_CHAR_3D(Ped ped, Ped pednext, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_ANY_MEANS_OBJECT_2D(Ped ped, Object obj, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_ANY_MEANS_OBJECT_3D(Ped ped, Object obj, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_2D(Ped ped, float x0, float y0, float x1, float y1, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_3D(Ped ped, float x0, float y0, float z0, float x1, float y1, float z, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_CAR_2D(Ped ped, Vehicle car, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_CAR_3D(Ped ped, Vehicle car, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_CHAR_2D(Ped ped, Ped pednext, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_CHAR_3D(Ped ped, Vehicle pednext, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_OBJECT_2D(Ped ped, Object obj, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_IN_CAR_OBJECT_3D(Ped ped, Object obj, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_2D(Ped ped, float x0, float y0, float x1, float y1, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_3D(Ped ped, float x0, float y0, float z0, float x1, float y1, float z1, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_CAR_2D(Ped ped, Vehicle car, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_CAR_3D(Ped ped, Vehicle car, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_CHAR_2D(Ped ped, Ped pednext, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_CHAR_3D(Ped ped, Ped pednext, float x, float y, float z, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_OBJECT_2D(Ped ped, Object obj, float x, float y, bool flag)l
extern _native bool LOCATE_CHAR_ON_FOOT_OBJECT_3D(Ped ped, Object obj, float x, float y, float z, bool flag)l
extern _native bool SET_CHAR_ANIM_PLAYING_FLAG(Ped ped, const char* AnimName0, const char* AnimName1, bool flag)l
extern _native const char* GET_ANIM_GROUP_FROM_CHAR(Ped ped)l
extern _native float GET_CHAR_MAX_MOVE_BLEND_RATIO(Ped ped)l
extern _native int GET_CHAR_GRAVITY(Ped ped)l
extern _native ScriptAny GET_CHAR_LAST_DAMAGE_BONE(Ped ped, uint *pBone)l
extern _native ScriptAny SET_CHAR_DUCKING(Ped ped, bool set)l
extern _native ScriptAny TOGGLE_CHAR_DUCKING(Ped ped)l
extern _native uint GET_CHAR_DRAWABLE_VARIATION(Ped ped, uint component)l
extern _native uint GET_CHAR_MONEY(Ped ped)l
extern _native uint GET_CHAR_TEXTURE_VARIATION(Ped ped, uint component)l
extern _native uint GET_NUMBER_OF_CHAR_DRAWABLE_VARIATIONS(Ped ped, uint component)l
extern _native uint GET_NUMBER_OF_CHAR_TEXTURE_VARIATIONS(Ped ped, uint component, uint unknown1)l
extern _native void ADD_ARMOUR_TO_CHAR(Ped ped, uint amount)l
extern _native void ATTACH_ANIMS_TO_MODEL(uint model, const char* anims)l
extern _native void BEGIN_CHAR_SEARCH_CRITERIA(void)l
extern _native void BLEND_FROM_NM_WITH_ANIM(Ped ped, const char* AnimName0, const char* AnimName1, int Unk1, float x, float y, float z)l
extern _native void BLEND_OUT_CHAR_MOVE_ANIMS(Ped ped)l
extern _native void BLOCK_CHAR_AMBIENT_ANIMS(Ped ped, bool block)l
extern _native void BLOCK_CHAR_GESTURE_ANIMS(Ped ped, bool value)l
extern _native void BLOCK_CHAR_HEAD_IK(Ped ped, bool block)l
extern _native void BLOCK_CHAR_VISEME_ANIMS(Ped ped, bool block)l
extern _native void CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(Ped ped)l
extern _native void CHANGE_CHAR_SIT_IDLE_ANIM(Ped ped, ScriptAny Unk2, ScriptAny Unk3, ScriptAny Unk4)l
extern _native void CLEAR_ALL_CHAR_PROPS(Ped ped)l
extern _native void CLEAR_ALL_CHAR_RELATIONSHIPS(Ped ped, int relgroup)l
extern _native void CLEAR_CHAR_LAST_DAMAGE_BONE(Ped ped)l
extern _native void CLEAR_CHAR_LAST_DAMAGE_ENTITY(Ped ped)l
extern _native void CLEAR_CHAR_LAST_WEAPON_DAMAGE(Ped ped)l
extern _native void CLEAR_CHAR_PROP(Ped ped, bool unknown)l
extern _native void CLEAR_CHAR_RELATIONSHIP(Ped ped, int reltype, int relgroup)l
extern _native void CLEAR_CHAR_SECONDARY_TASK(Ped ped)l
extern _native void CLEAR_CHAR_TASKS(Ped ped)l
extern _native void CLEAR_CHAR_TASKS_IMMEDIATELY(Ped ped)l
extern _native void CLEAR_RELATIONSHIP(int p0, int p1, int p2)l
extern _native void CLEAR_ROOM_FOR_CHAR(Ped ped)l
extern _native void CREATE_CHAR(eRelationshipGroup type, uint model, float x, float y, float z, Ped *pPed, bool unknownTrue)l
extern _native void CREATE_CHAR_AS_PASSENGER(Vehicle vehicle, uint charType, uint model, uint passengerIndex, Ped *pPed)l
extern _native void CREATE_CHAR_INSIDE_CAR(Vehicle vehicle, uint charType, uint model, Ped *pPed)l
extern _native void CREATE_RANDOM_CHAR(float x, float y, float z, Ped *pPed)l
extern _native void CREATE_RANDOM_CHAR_AS_PASSENGER(Vehicle vehicle, uint seat, Ped *pPed)l
extern _native void CREATE_RANDOM_FEMALE_CHAR(float x, float y, float z, Ped *pPed)l
extern _native void CREATE_RANDOM_MALE_CHAR(float x, float y, float z, Ped *pPed)l
extern _native void DAMAGE_CHAR(Ped ped, uint hitPoints, bool unknown)l
extern _native void DELETE_CHAR(Ped *pPed)l
extern _native void DONT_REMOVE_CHAR(Ped ped)l
extern _native void END_CHAR_SEARCH_CRITERIA(void)l
extern _native void EXPLODE_CHAR_HEAD(Ped ped)l
extern _native void EXTINGUISH_CHAR_FIRE(Ped ped)l
extern _native void FREEZE_CHAR_POSITION(Ped ped, bool frozen)l
extern _native void FREEZE_CHAR_POSITION_AND_DONT_LOAD_COLLISION(Ped ped, bool frozen)l
extern _native void GET_CHAR_ANIM_BLEND_AMOUNT(Ped ped, const char* AnimName0, const char* AnimName1, float *amount)l
extern _native void GET_CHAR_ANIM_CURRENT_TIME(Ped ped, const char* animGroup, const char* animName, float *pValue)l
extern _native void GET_CHAR_ANIM_TOTAL_TIME(Ped ped, const char* animGroup, const char* animName, float *pValue)l
extern _native void GET_CHAR_ARMOUR(Ped ped, uint *pArmour)l
extern _native void GET_CHAR_COORDINATES(Ped ped, float *pX, float *pY, float *pZ)l
extern _native void GET_CHAR_EXTRACTED_DISPLACEMENT(Ped ped, bool unknown, float *pX, float *pY, float *pZ)l
extern _native void GET_CHAR_EXTRACTED_VELOCITY(Ped ped, bool Unk5, float *x, float *y, float *z)l
extern _native void GET_CHAR_HEADING(Ped ped, float *pValue)l
extern _native void GET_CHAR_HEALTH(Ped ped, uint *pHealth)l
extern _native void GET_CHAR_HEIGHT_ABOVE_GROUND(Ped ped, float *pValue)l
extern _native void GET_CHAR_HIGHEST_PRIORITY_EVENT(Ped ped, int *event)l
extern _native void GET_CHAR_IN_CAR_PASSENGER_SEAT(Vehicle vehicle, uint seatIndex, Ped *pPed)l
extern _native void GET_CHAR_MODEL(Ped ped, uint *pModel)l
extern _native void GET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER(Ped ped, float *multiplier)l
extern _native void GET_CHAR_PROP_INDEX(Ped ped, bool unknown, uint *pIndex)l
extern _native void GET_CHAR_SPEED(Ped ped, float *pValue)l
extern _native void GET_CHAR_VELOCITY(Ped ped, float *pX, float *pY, float *pZ)l
//extern _native void GET_DEAD_CHAR_COORDINATES(Ped ped, float *pX, float *pY, float *pZ)l
extern _native void GET_DEAD_CHAR_PICKUP_COORDS(Ped ped, float *pX, float *pY, float *pZ)l
extern _native void GET_KEY_FOR_CHAR_IN_ROOM(Ped ped, uint *pKey)l
extern _native void GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(Ped ped, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ)l
extern _native void MARK_CHAR_AS_NO_LONGER_NEEDED(Ped *pPed)l
extern _native void MODIFY_CHAR_MOVE_BLEND_RATIO(Ped ped, ScriptAny Unk6)l
extern _native void MODIFY_CHAR_MOVE_STATE(Ped ped, uint state)l
extern _native void REMOVE_CHAR_DEFENSIVE_AREA(Ped ped)l
extern _native void REMOVE_CHAR_ELEGANTLY(Ped ped)l
extern _native void REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION(Ped ped, Vehicle car)l
extern _native void REMOVE_CHAR_FROM_GROUP(Ped ped)l
extern _native void SET_ANIM_GROUP_FOR_CHAR(Ped ped, const char* grname)l
extern _native void SET_CHAR_ACCURACY(Ped ped, uint value)l
extern _native void SET_CHAR_ALLOWED_TO_DUCK(Ped ped, bool set)l
extern _native void SET_CHAR_ALLOWED_TO_RUN_ON_BOATS(Ped ped, bool set)l
extern _native void SET_CHAR_ALL_ANIMS_SPEED(Ped ped, float speed)l
extern _native void SET_CHAR_ANGLED_DEFENSIVE_AREA(Ped ped, float x0, float y0, float z0, float x1, float y1, float z1, float angle)l
extern _native void SET_CHAR_ANIM_BLEND_OUT_DELTA(Ped ped, const char* AnimName0, const char* AnimName1, float delta)l
extern _native void SET_CHAR_ANIM_CURRENT_TIME(Ped ped, const char* AnimName0, const char* AnimName1, float time)l
extern _native void SET_CHAR_ANIM_SPEED(Ped ped, const char* AnimName0, const char* AnimName1, float speed)l
extern _native void SET_CHAR_AS_ENEMY(Ped ped, bool value)l
extern _native void SET_CHAR_AS_MISSION_CHAR(Ped ped)l
extern _native void SET_CHAR_BLEEDING(Ped ped, bool set)l
extern _native void SET_CHAR_BULLETPROOF_VEST(Ped ped, bool set)l
extern _native void SET_CHAR_CANT_BE_DRAGGED_OUT(Ped ped, bool enabled)l
extern _native void SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE(Ped ped, bool value)l
extern _native void SET_CHAR_CAN_BE_SHOT_IN_VEHICLE(Ped ped, bool enabled)l
extern _native void SET_CHAR_CAN_SMASH_GLASS(Ped ped, bool set)l
extern _native void SET_CHAR_CLIMB_ANIM_RATE(Ped ped, float rate)l
extern _native void SET_CHAR_COLLISION(Ped ped, bool set)l
extern _native void SET_CHAR_COMPONENT_VARIATION(Ped ped, uint component, uint modelVariation, uint textureVariation)l
extern _native void SET_CHAR_COORDINATES(Ped ped, float x, float y, float z)l
extern _native void SET_CHAR_COORDINATES_DONT_CLEAR_PLAYER_TASKS(Ped ped, float x, float y, float z)l
extern _native void SET_CHAR_COORDINATES_DONT_WARP_GANG(Ped ped, float x, float y, float z)l
extern _native void SET_CHAR_COORDINATES_DONT_WARP_GANG_NO_OFFSET(Ped ped, float x, float y, float z)l
extern _native void SET_CHAR_COORDINATES_NO_OFFSET(Ped ped, float x, float y, float z)l
extern _native void SET_CHAR_DEFAULT_COMPONENT_VARIATION(Ped ped)l
extern _native void SET_CHAR_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped pednext, float x0, float y0, float z0, float x1, float y1, float z1, int Unk7, int Unk8)l
extern _native void SET_CHAR_DESIRED_HEADING(Ped ped, float heading)l
extern _native void SET_CHAR_DIES_INSTANTLY_IN_WATER(Ped ped, bool allow)l
extern _native void SET_CHAR_DROPS_WEAPONS_WHEN_DEAD(Ped ped, bool value)l
extern _native void SET_CHAR_DROWNS_IN_SINKING_VEHICLE(Ped ped, bool set)l
extern _native void SET_CHAR_DROWNS_IN_WATER(Ped ped, bool set)l
extern _native void SET_CHAR_DRUGGED_UP(Ped ped, bool drugged)l
extern _native void SET_CHAR_DUCKING_TIMED(Ped ped, int timed)l
extern _native void SET_CHAR_FIRE_DAMAGE_MULTIPLIER(Ped ped, float multiplier)l
extern _native void SET_CHAR_FORCE_DIE_IN_CAR(Ped ped, bool set)l
extern _native void SET_CHAR_GESTURE_GROUP(Ped ped, const char* AnimGroup)l
extern _native void SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(Ped ped, bool set)l
extern _native void SET_CHAR_GRAVITY(Ped ped, float value)l
extern _native void SET_CHAR_HEADING(Ped ped, float heading)l
extern _native void SET_CHAR_HEALTH(Ped ped, uint health)l
extern _native void SET_CHAR_INVINCIBLE(Ped ped, bool enable)l
extern _native void SET_CHAR_IN_CUTSCENE(Ped ped, bool set)l
extern _native void SET_CHAR_IS_TARGET_PRIORITY(Ped ped, bool enable)l
extern _native void SET_CHAR_KEEP_TASK(Ped ped, bool value)l
extern _native void SET_CHAR_MAX_HEALTH(Ped ped, uint value)l
extern _native void SET_CHAR_MAX_MOVE_BLEND_RATIO(Ped ped, float ratio)l
extern _native void SET_CHAR_MAX_TIME_IN_WATER(Ped ped, float time)l
extern _native void SET_CHAR_MAX_TIME_UNDERWATER(Ped ped, float time)l
extern _native void SET_CHAR_MELEE_ACTION_FLAG0(Ped ped, bool set)l
extern _native void SET_CHAR_MELEE_ACTION_FLAG1(Ped ped, bool set)l
extern _native void SET_CHAR_MELEE_ACTION_FLAG2(Ped ped, bool set)l
extern _native void SET_CHAR_MELEE_MOVEMENT_CONSTAINT_BOX(Ped ped, float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SET_CHAR_MONEY(Ped ped, uint amount)l
extern _native void SET_CHAR_MOVEMENT_ANIMS_BLOCKED(Ped ped, bool set)l
extern _native void SET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER(Ped ped, float multiplier)l
extern _native void SET_CHAR_NEVER_LEAVES_GROUP(Ped ped, bool value)l
extern _native void SET_CHAR_NEVER_TARGETTED(Ped ped, bool set)l
extern _native void SET_CHAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP(Ped ped, eRelationshipGroup relationshipGroup, bool enable)l
extern _native void SET_CHAR_ONLY_DAMAGED_BY_PLAYER(Ped ped, bool set)l
extern _native void SET_CHAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Ped ped, bool set, int relgroup)l
extern _native void SET_CHAR_PROOFS(Ped ped, bool unknown0, bool fallingDamage, bool unknown1, bool unknown2, bool unknown3)l
extern _native void SET_CHAR_PROP_INDEX(Ped ped, uint propType, uint index)l
extern _native void SET_CHAR_PROP_INDEX_TEXTURE(Ped ped, int Unk9, int Unk10, int Unk11)l
extern _native void SET_CHAR_PROVIDE_COVERING_FIRE(Ped ped, bool set)l
extern _native void SET_CHAR_RANDOM_COMPONENT_VARIATION(Ped ped)l
extern _native void SET_CHAR_READY_TO_BE_EXECUTED(Ped ped, bool set)l
extern _native void SET_CHAR_READY_TO_BE_STUNNED(Ped ped, bool set)l
extern _native void SET_CHAR_RELATIONSHIP(Ped ped, uint relationshipLevel, eRelationshipGroup relationshipGroup)l
extern _native void SET_CHAR_RELATIONSHIP_GROUP(Ped ped, eRelationshipGroup relationshipGroup)l
extern _native void SET_CHAR_ROTATION(Ped ped, float xr, float yr, float zr)l
extern _native void SET_CHAR_SHOOT_RATE(Ped ped, int rate)l
extern _native void SET_CHAR_SIGNAL_AFTER_KILL(Ped ped, bool set)l
extern _native void SET_CHAR_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius)l
extern _native void SET_CHAR_STAY_IN_CAR_WHEN_JACKED(Ped ped, bool set)l
extern _native void SET_CHAR_SUFFERS_CRITICAL_HITS(Ped ped, bool value)l
extern _native void SET_CHAR_USES_DEAFULT_ANIM_GROUP_WHEN_FLEEING(Ped ped, bool set)l
extern _native void SET_CHAR_USES_UPPERBODY_DAMAGE_ANIMS_ONLY(Ped ped, bool set)l
extern _native void SET_CHAR_VELOCITY(Ped ped, float x, float y, float z)l
extern _native void SET_CHAR_VISIBLE(Ped ped, bool value)l
extern _native void SET_CHAR_WALK_ALONGSIDE_LEADER_WHEN_APPROPRIATE(Ped ped, bool set)l
extern _native void SET_CHAR_WATCH_MELEE(Ped ped, bool set)l
extern _native void SET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING(Ped ped, bool set)l
extern _native void SET_CHAR_WILL_DO_DRIVEBYS(Ped ped, bool value)l
extern _native void SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(Ped ped, bool value)l
extern _native void SET_CHAR_WILL_LEAVE_CAR_IN_COMBAT(Ped ped, bool set)l
extern _native void SET_CHAR_WILL_MOVE_WHEN_INJURED(Ped ped, bool value)l
extern _native void SET_CHAR_WILL_ONLY_FIRE_WITH_CLEAR_LOS(Ped ped, bool set)l
extern _native void SET_CHAR_WILL_REMAIN_ON_BOAT_AFTER_MISSION_ENDS(Ped ped, bool set)l
extern _native void SET_CHAR_WILL_TRY_TO_LEAVE_BOAT_AFTER_LEADER(Ped ped, bool set)l
extern _native void SET_CHAR_WILL_TRY_TO_LEAVE_WATER(Ped ped, bool set)l
extern _native void SET_CHAR_WILL_USE_CARS_IN_COMBAT(Ped ped, bool value)l
extern _native void SET_CHAR_WILL_USE_COVER(Ped ped, bool value)l
extern _native void SET_DEAD_CHAR_COORDINATES(Ped ped, float x, float y, float z)l
extern _native void SET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT(Ped ped, bool value)l
extern _native void SET_LOAD_COLLISION_FOR_CHAR_FLAG(Ped ped, bool set)l
extern _native void SET_ROOM_FOR_CHAR_BY_KEY(Ped ped, uint key)l
extern _native void SET_ROOM_FOR_CHAR_BY_NAME(Ped ped, const char* roomname)l
extern _native void UNSET_CHAR_MELEE_MOVEMENT_CONSTAINT_BOX(Ped ped)l
#pragma endregion//}
#pragma region PLAYER//{
extern _native bool CAN_PLAYER_START_MISSION(int player)l
extern _native bool GET_PLAYER_HAS_TRACKS(void)l
extern _native bool HAS_ACHIEVEMENT_BEEN_PASSED(uint achievement)l
extern _native bool HAS_PLAYER_COLLECTED_PICKUP(Player playerIndex, Pickup pikcup)l
extern _native bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Player playerIndex)l
extern _native bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_VEHICLE(Player playerIndex)l
extern _native bool IS_PLACE_CAR_BOMB_ACTIVE(void)l
extern _native bool IS_PLAYER_BEING_ARRESTED(void)l
extern _native bool IS_PLAYER_CLIMBING(Player playerIndex)l
extern _native bool IS_PLAYER_CONTROL_ON(Player playerIndex)l
extern _native bool IS_PLAYER_DEAD(Player playerIndex)l
extern _native bool IS_PLAYER_FREE_AIMING_AT_CHAR(Player playerIndex, Ped ped)l
extern _native bool IS_PLAYER_FREE_FOR_AMBIENT_TASK(Player playerIndex)l
extern _native bool IS_PLAYER_IN_REMOTE_MODE(int player)l
extern _native bool IS_PLAYER_ONLINE(void)l
extern _native bool IS_PLAYER_PERFORMING_STOPPIE(int player)l
extern _native bool IS_PLAYER_PERFORMING_WHEELIE(int player)l
extern _native bool IS_PLAYER_PLAYING(Player playerIndex)l
extern _native bool IS_PLAYER_PRESSING_HORN(Player playerIndex)l
extern _native bool IS_PLAYER_READY_FOR_CUTSCENE(int player)l
extern _native bool IS_PLAYER_SCRIPT_CONTROL_ON(int player)l
extern _native bool IS_PLAYER_SIGNED_IN_LOCALLY(void)l
extern _native bool IS_PLAYER_TARGETTING_ANYTHING(Player playerIndex)l
extern _native bool IS_PLAYER_TARGETTING_CHAR(Player playerIndex, Ped ped)l
extern _native bool IS_PLAYER_TARGETTING_OBJECT(Player playerIndex, Object obj)l
extern _native bool IS_PLAYER_VEHICLE_ENTRY_DISABLED(int player)l
extern _native bool IS_SCORE_GREATER(Player playerIndex, uint score)l
extern _native bool PLAYER_HAS_CHAR(Player playerIndex)l
extern _native bool PLAYER_HAS_FLASHING_STARS_ABOUT_TO_DROP(Player playerIndex)l
extern _native bool PLAYER_HAS_GREYED_OUT_STARS(Player playerIndex)l
extern _native bool PLAYER_IS_INTERACTING_WITH_GARAGE(void)l
extern _native bool PLAYER_IS_NEAR_FIRST_PIGEON(float x, float y, float z)l
extern _native bool PLAYER_IS_PISSED_OFF(int player)l
extern _native const char* GET_PLAYER_RADIO_STATION_NAME(void)l
extern _native const char* GET_PLAYER_RADIO_STATION_NAME_ROLL(void)l
extern _native const char* GET_PLAYER_NAME(Player playerIndex)l
extern _native const char* GET_PLAYER_RADIO_STATION_NAME(void)l
extern _native int GET_LOCAL_PLAYER_MP_CASH(void)l
extern _native int GET_NO_LAW_VEHICLES_DESTROYED_BY_LOCAL_PLAYER(void)l
extern _native int GET_PLAYER_ID_FOR_THIS_PED(Ped ped)l
extern _native int GET_PLAYER_RADIO_MODE(void)l
extern _native Player CONVERT_INT_TO_PLAYERINDEX(uint playerId)l
extern _native ScriptAny GET_PLAYER_TO_PLACE_BOMB_IN_CAR(Vehicle vehicle)l
extern _native uint GET_LEFT_PLAYER_CASH_TO_REACH_LEVEL(uint playerRank)l
extern _native uint GET_PLAYERSETTINGS_MODEL_CHOICE(void)l
extern _native uint GET_PLAYER_ID(void)l
extern _native uint GET_PLAYER_RADIO_STATION_INDEX(void)l
extern _native uint GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(Player playerIndex)l
extern _native uint GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Player playerIndex)l
extern _native uint GET_TIME_SINCE_PLAYER_HIT_BUILDING(Player playerIndex)l
extern _native uint GET_TIME_SINCE_PLAYER_HIT_CAR(Player playerIndex)l
extern _native uint GET_TIME_SINCE_PLAYER_HIT_OBJECT(Player playerIndex)l
extern _native uint GET_TIME_SINCE_PLAYER_HIT_PED(Player playerIndex)l
extern _native uint GET_TIME_SINCE_PLAYER_RAN_LIGHT(Player playerIndex)l
extern _native void ADD_SCORE(Player playerIndex, int score)l
extern _native void ALLOW_LOCKON_TO_RANDOM_PEDS(int player, bool allow)l
extern _native void ALLOW_PLAYER_TO_CARRY_NON_MISSION_OBJECTS(Player playerIndex, bool allow)l
extern _native void AWARD_PLAYER_MISSION_RESPECT(float respect)l
extern _native void BLOCK_STATS_MENU_ACTIONS(int player)l
extern _native void CHANGE_PLAYER_MODEL(Player playerIndex, uint model)l
extern _native void CHANGE_PLAYER_PHONE_MODEL(int player, uint model)l
extern _native void CHANGE_PLAYER_PHONE_MODEL_OFFSETS(int player, float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Player playerIndex)l
extern _native void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_VEHICLE(int player)l
extern _native void CREATE_PLAYER(uint playerId, float x, float y, float z, Player *pPlayerIndex)l
extern _native void DELETE_PLAYER(void)l
extern _native void DISABLE_LOCAL_PLAYER_PICKUPS(bool disable)l
extern _native void DISABLE_PLAYER_AUTO_VEHICLE_EXIT(Ped ped, bool disable)l
extern _native void DISABLE_PLAYER_LOCKON(Player playerIndex, bool disabled)l
extern _native void DISABLE_PLAYER_SPRINT(Player playerIndex, bool disabled)l
extern _native void DISABLE_PLAYER_VEHICLE_ENTRY(int player, bool disable)l
extern _native void FAKE_DEATHARREST(void)l
extern _native void FORCE_AIR_DRAG_MULT_FOR_PLAYERS_CAR(int player, float multiplier)l
extern _native void FORCE_INTERIOR_LIGHTING_FOR_PLAYER(int player, bool force)l
extern _native void GET_NUM_OF_MODELS_KILLED_BY_PLAYER(int player, uint model, int *num)l
extern _native void GET_PLAYERS_LAST_CAR_NO_SAVE(Vehicle* pVehicle)l
extern _native void GET_PLAYER_CHAR(Player playerIndex, Ped *pPed)l
extern _native void GET_PLAYER_GROUP(Player playerIndex, Group *pGroup)l
extern _native void GET_PLAYER_MAX_ARMOUR(Player playerIndex, uint *pMaxArmour)l
extern _native void GET_PLAYER_MAX_HEALTH(int player, int *maxhealth)l
extern _native void GIVE_PLAYER_RAGDOLL_CONTROL(int player, bool give)l
extern _native void INCREASE_PLAYER_MAX_ARMOUR(int player, float armour)l
extern _native void INCREASE_PLAYER_MAX_HEALTH(int player, int maxhealth)l
extern _native void LISTEN_TO_PLAYER_GROUP_COMMANDS(Ped ped, bool set)l
extern _native void MAKE_PLAYER_FIRE_PROOF(int player, bool proof)l
extern _native void MAKE_PLAYER_GANG_DISAPPEAR(void)l
extern _native void MAKE_PLAYER_GANG_REAPPEAR(void)l
extern _native void MAKE_PLAYER_SAFE_FOR_CUTSCENE(int player)l
extern _native void REGISTER_PLAYER_RESPAWN_COORDS(Player playerIndex, float x, float y, float z)l
extern _native void REMOVE_PLAYER_HELMET(Player playerIndex, bool remove)l
extern _native void RESET_NO_LAW_VEHICLES_DESTROYED_BY_LOCAL_PLAYER(void)l
extern _native void RESET_NUM_OF_MODELS_KILLED_BY_PLAYER(uint model)l
extern _native void SET_ALL_RANDOM_PEDS_FLEE(int player, bool set)l
extern _native void SET_DISABLE_PLAYER_SHOVE_ANIMATION(Ped ped, bool disable)l
extern _native void SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, bool set)l
extern _native void SET_DRAW_PLAYER_COMPONENT(int component, bool set)l
extern _native void SET_EVERYONE_IGNORE_PLAYER(Player playerIndex, bool value)l
extern _native void SET_FORCE_LOOK_BEHIND(bool set)l
extern _native void SET_FORCE_PLAYER_TO_ENTER_THROUGH_DIRECT_DOOR(Ped ped, bool set)l
extern _native void SET_FREE_HEALTH_CARE(int player, bool set)l
extern _native void SET_LOCAL_PLAYER_PAIN_VOICE(const char* name)l
extern _native void SET_LOCAL_PLAYER_VOICE(const char* name)l
extern _native void SET_PLAYERSETTINGS_MODEL_VARIATIONS_CHOICE(Player playerIndex)l
extern _native void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Player playerIndex, bool value)l
extern _native void SET_PLAYER_CAN_DO_DRIVE_BY(Player playerIndex, bool value)l
extern _native void SET_PLAYER_CAN_DROP_WEAPONS_IN_CAR(bool set)l
extern _native void SET_PLAYER_CAN_USE_COVER(Player playerIndex, bool value)l
extern _native void SET_PLAYER_CONTROL(Player playerIndex, bool value)l
extern _native void SET_PLAYER_CONTROL_ADVANCED(Player playerIndex, bool unknown1, bool unknown2, bool unknown3)l
extern _native void SET_PLAYER_CONTROL_FOR_AMBIENT_SCRIPT(int player, bool flag0, bool flag1)l
extern _native void SET_PLAYER_CONTROL_FOR_TEXT_CHAT(int player, bool set)l
extern _native void SET_PLAYER_CONTROL_ON_IN_MISSION_CLEANUP(bool set)l
extern _native void SET_PLAYER_DISABLE_CROUCH(int player, bool set)l
extern _native void SET_PLAYER_DISABLE_JUMP(int player, bool set)l
extern _native void SET_PLAYER_FAST_RELOAD(Player playerIndex, bool value)l
extern _native void SET_PLAYER_FORCED_AIM(int player, bool set)l
extern _native void SET_PLAYER_GROUP_RECRUITMENT(int player, bool set)l
extern _native void SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS(Player playerIndex, bool value)l
extern _native void SET_PLAYER_GROUP_TO_FOLLOW_NEVER(int player, bool set)l
extern _native void SET_PLAYER_ICON_COLOUR(int colour)l
extern _native void SET_PLAYER_INVINCIBLE(Player playerIndex, bool value)l
extern _native void SET_PLAYER_INVISIBLE_TO_AI(bool set)l
extern _native void SET_PLAYER_IS_IN_STADIUM(bool set)l
extern _native void SET_PLAYER_KEEPS_WEAPONS_WHEN_RESPAWNED(bool set)l
extern _native void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(int player, Vehicle veh)l
extern _native void SET_PLAYER_MOOD_NORMAL(Player playerIndex)l
extern _native void SET_PLAYER_MOOD_PISSED_OFF(Player playerIndex, uint unknown150)l
extern _native void SET_PLAYER_MP_MODIFIER(int player, int Unk12, float modifier)l
extern _native void SET_PLAYER_NEVER_GETS_TIRED(Player playerIndex, bool value)l
extern _native void SET_PLAYER_PAIN_ROOT_BANK_NAME(const char* name)l
extern _native void SET_PLAYER_PLAYER_TARGETTING(bool set)l
extern _native void SET_PLAYER_SETTINGS_GENRE(Ped ped)l
extern _native void SET_USE_LEG_IK(int player, bool set)l
extern _native void STORE_SCORE(Player playerIndex, uint* value)l
extern _native void ALLOW_LOCKON_TO_FRIENDLY_PLAYERS(int player, bool allow)l
#pragma endregion//}
#pragma region PED//{
extern _native bool ARE_ENEMY_PEDS_IN_AREA(Ped ped, float x, float y, float z, float radius)l
extern _native bool CAN_PED_SHIMMY_IN_DIRECTION(Ped ped, int direction)l
extern _native bool CHECK_NM_FEEDBACK(Ped ped, int id, bool Unk13)l
extern _native bool DOES_GROUP_EXIST(Group group)l
extern _native bool GET_PED_PATH_MAY_DROP_FROM_HEIGHT(Ped ped)l
extern _native bool GET_PED_PATH_MAY_USE_CLIMBOVERS(Ped ped)l
extern _native bool GET_PED_PATH_MAY_USE_LADDERS(Ped ped)l
extern _native bool GET_PED_PATH_WILL_AVOID_DYNAMIC_OBJECTS(Ped ped)l
extern _native bool GET_PED_STEERS_AROUND_OBJECTS(Ped ped)l
extern _native bool GET_PED_STEERS_AROUND_PEDS(Ped ped)l
extern _native bool GET_TASK_PLACE_CAR_BOMB_UNSUCCESSFUL(void)l
extern _native bool HAS_OVERRIDEN_SIT_IDLE_ANIM_FINISHED(Ped ped)l
extern _native bool IS_GROUP_LEADER(Ped ped, Group group)l
extern _native bool IS_GROUP_MEMBER(Ped ped, Group group)l
extern _native bool IS_PEDS_VEHICLE_HOT(Ped ped)l
extern _native bool IS_PED_ATTACHED_TO_ANY_CAR(Ped ped)l
extern _native bool IS_PED_ATTACHED_TO_OBJECT(Ped ped, Object obj)l
extern _native bool IS_PED_A_MISSION_PED(Ped ped)l
extern _native bool IS_PED_BEING_JACKED(Ped ped)l
extern _native bool IS_PED_CLIMBING(Ped ped)l
extern _native bool IS_PED_DOING_DRIVEBY(Ped ped)l
extern _native bool IS_PED_FLEEING(Ped ped)l
extern _native bool IS_PED_HOLDING_AN_OBJECT(Ped ped)l
extern _native bool IS_PED_IN_COMBAT(Ped ped)l
extern _native bool IS_PED_IN_COVER(Ped ped)l
extern _native bool IS_PED_IN_CUTSCENE_BLOCKING_BOUNDS(Ped ped)l
extern _native bool IS_PED_IN_GROUP(Ped ped)l
extern _native bool IS_PED_JACKING(Ped ped)l
extern _native bool IS_PED_LOOKING_AT_CAR(Ped ped, Vehicle car)l
extern _native bool IS_PED_LOOKING_AT_OBJECT(Ped ped, Object obj)l
extern _native bool IS_PED_LOOKING_AT_PED(Ped ped, Ped otherChar)l
extern _native bool IS_PED_PINNED_DOWN(Ped ped)l
extern _native bool IS_PED_RAGDOLL(Ped ped)l
extern _native bool IS_PED_RETREATING(Ped ped)l
extern _native bool IS_THIS_PED_A_PLAYER(Ped ped)l
extern _native bool SWITCH_PED_TO_RAGDOLL(Ped ped, int Unk14, int time, bool flag0, bool flag1, bool flag2, bool flag3)l
extern _native bool SWITCH_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int Unk15, int Unk16, int Unk17, float Unk18, float Unk19, int Unk20, float Unk21, float Unk22, float Unk23, float Unk24, float Unk25, float Unk26, float Unk27)l
extern _native bool WAS_PED_KILLED_BY_HEADSHOT(Ped ped)l
extern _native bool WAS_PED_SKELETON_UPDATED(Ped ped)l
extern _native int FIND_MAX_NUMBER_OF_GROUP_MEMBERS(void)l
extern _native int GET_NUMBER_OF_ACTIVE_STICKY_BOMBS_OWNED_BY_PED(Ped ped)l
extern _native int GET_NUMBER_OF_INJURED_PEDS_IN_RANGE(float x, float y, float z, float radius)l
extern _native Ped GET_PED_OBJECT_IS_ATTACHED_TO(Object obj)l
extern _native uint GET_DAMAGE_TO_PED_BODY_PART(Ped ped, uint part)l
extern _native uint GET_PED_CLIMB_STATE(Ped ped)l
extern _native uint GET_PED_MODEL_FROM_INDEX(int index)l
extern _native void ADD_PED_TO_CINEMATOGRAPHY_AI(int Unk28, Ped ped)l
extern _native void ADD_PED_TO_MISSION_DELETION_LIST(Ped ped, bool Unk29)l
extern _native void ALLOW_TARGET_WHEN_INJURED(Ped ped, bool allow)l
extern _native void ALWAYS_USE_HEAD_ON_HORN_ANIM_WHEN_DEAD_IN_CAR(Ped ped, bool use)l
extern _native void APPLY_FORCE_TO_PED(Ped ped, uint unknown0_3, float x, float y, float z, float spinX, float spinY, float spinZ, uint unknown4_0, uint unknown5_1, uint unknown6_1, uint unknown7_1)l
extern _native void ATTACH_PED_TO_CAR_PHYSICALLY(Ped ped, Vehicle car, int pedbone, float x, float y, float z, float angle, float Unk30, bool Unk31, bool Unk32)l
extern _native void ATTACH_PED_TO_OBJECT(Ped ped, Object obj, int pedbone, float x, float y, float z, float angle, float Unk33, bool Unk34, bool Unk35)l
extern _native void ATTACH_PED_TO_OBJECT_PHYSICALLY(Ped ped, Object obj, int pedbone, float x, float y, float z, float angle, float Unk36, bool Unk37, bool Unk38)l
extern _native void ATTACH_PED_TO_SHIMMY_EDGE(Ped ped, float x, float y, float z, float Unk39)l
extern _native void CLOSE_MIC_PED(int id, Ped ped)l
extern _native void COPY_ANIMATIONS(Ped ped, Ped pednext, float speed)l
extern _native void CREATE_GROUP(bool unknownFalse, Group *pGroup, bool unknownTrue)l
extern _native void CREATE_NM_MESSAGE(bool Unk40, int id)l
extern _native void DAMAGE_PED_BODY_PART(Ped ped, uint part, uint hitPoints)l
extern _native void DEFINE_PED_GENERATION_CONSTRAINT_AREA(float x, float y, float z, float radius)l
extern _native void DESTROY_PED_GENERATION_CONSTRAINT_AREA(void)l
extern _native void DETACH_PED(Ped ped, bool unknown)l
//extern _native void DETACH_PED_FROM_WITHIN_CAR(Ped ped, bool unknown)l
extern _native void DONT_SUPPRESS_ANY_PED_MODELS(void)l
extern _native void DONT_SUPPRESS_PED_MODEL(uint model)l
extern _native void ENABLE_ALL_PED_HELMETS(bool enable)l
extern _native void ENABLE_PED_HELMET(Ped ped, bool enable)l
extern _native void FORCE_FULL_VOICE(Ped ped)l
extern _native void FORCE_PED_PINNED_DOWN(Ped ped, bool force, uint timerMaybe)l
extern _native void FORCE_PED_TO_FLEE_WHILST_DRIVING_VEHICLE(Ped ped, Vehicle vehicle)l
extern _native void FORCE_PED_TO_LOAD_COVER(Ped ped, bool force)l
extern _native void FORCE_RANDOM_PED_TYPE(uint type)l
extern _native void FORCE_SPAWN_SCENARIO_PEDS_IN_AREA(float x, float y, float z, float radius, int Unk41)l
extern _native void GET_CUTSCENE_PED_POSITION(int unkped, vector3 *pos)l
extern _native void GET_DRIVER_OF_CAR(Vehicle vehicle, Ped *pPed)l
extern _native void GET_GROUP_FORMATION(int group, int *formation)l
extern _native void GET_GROUP_FORMATION_SPACING(int group, float *spacing)l
extern _native void GET_GROUP_LEADER(Group group, Ped *pPed)l
extern _native void GET_GROUP_MEMBER(Group group, uint index, Ped *pPed)l
extern _native void GET_GROUP_SIZE(Group group, uint *pStartIndex, uint *pCount)l
extern _native void GET_NTH_GROUP_MEMBER(int group, int n, Ped *ped)l
extern _native void GET_NUMBER_OF_FOLLOWERS(Ped ped, int *followers)l
extern _native void GET_PED_BONE_POSITION(Ped ped, uint bone, float x, float y, float z, vector3 *pPosition)l
extern _native void GET_PED_GROUP_INDEX(Ped ped, uint* pIndex)l
extern _native void GET_PED_TYPE(Ped ped, uint *pType)l
extern _native void GET_SCRIPT_TASK_STATUS(Ped ped, int task, int *status)l
extern _native void GIVE_PED_AMBIENT_OBJECT(Ped ped, uint model)l
extern _native void GIVE_PED_FAKE_NETWORK_NAME(Ped ped, const char* name, int r, int g, int b, int a)l
extern _native void GIVE_PED_HELMET(Ped ped)l
extern _native void GIVE_PED_HELMET_WITH_OPTS(Ped ped, bool Unk42)l
extern _native void GIVE_PED_PICKUP_OBJECT(Ped ped, Object obj, bool flag)l
extern _native void KNOCK_PED_OFF_BIKE(Vehicle vehicle)l
extern _native void PED_QUEUE_CONSIDER_PEDS_WITH_FLAG_FALSE(int flagid)l
extern _native void PED_QUEUE_CONSIDER_PEDS_WITH_FLAG_TRUE(int flagid)l
extern _native void PED_QUEUE_REJECT_PEDS_WITH_FLAG_FALSE(int flagid)l
extern _native void PED_QUEUE_REJECT_PEDS_WITH_FLAG_TRUE(int flagid)l
extern _native void REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius)l
extern _native void REGISTER_HATED_TARGETS_IN_AREA(Ped ped, float x, float y, float z, float radius)l
extern _native void REGISTER_TARGET(Ped ped, Ped target)l
extern _native void REMOVE_CLOSE_MIC_PED(Ped ped)l
extern _native void REMOVE_FAKE_NETWORK_NAME_FROM_PED(Ped ped)l
extern _native void REMOVE_GROUP(Group group)l
extern _native void REMOVE_PED_HELMET(Ped ped, bool removed)l
extern _native void RESET_VISIBLE_PED_DAMAGE(Ped ped)l
extern _native void REVIVE_INJURED_PED(Ped ped)l
extern _native void SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_FALSE(int flagid)l
extern _native void SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_TRUE(uint flagId)l
extern _native void SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_FALSE(int flagid)l
extern _native void SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_TRUE(uint flagId)l
extern _native void SEND_NM_MESSAGE(Ped ped)l
extern _native void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool value)l
extern _native void SET_BRIANS_MOOD(int mood)l
extern _native void SET_COLLIDE_WITH_PEDS(bool set)l
extern _native void SET_DEAD_PEDS_DROP_WEAPONS(bool set)l
extern _native void SET_DEATH_WEAPONS_PERSIST(Ped ped, bool set)l
extern _native void SET_GROUP_FOLLOW_STATUS(Group group, uint status)l
extern _native void SET_GROUP_FORMATION(Group group, uint formation)l
extern _native void SET_GROUP_FORMATION_SPACING(Group group, float space)l
extern _native void SET_GROUP_LEADER(Group group, Ped leader)l
extern _native void SET_GROUP_MEMBER(Group group, Ped member)l
extern _native void SET_GROUP_SEPARATION_RANGE(Group group, float seperation)l
extern _native void SET_HEADING_LIMIT_FOR_ATTACHED_PED(Ped ped, float heading0, float heading1)l
extern _native void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Ped ped, bool value)l
extern _native void SET_INFORM_RESPECTED_FRIENDS(Ped ped, int Unk43, int Unk44)l
extern _native void SET_MIN_MAX_PED_ACCURACY(Ped ped, float min, float max)l
extern _native void SET_MONEY_CARRIED_BY_ALL_NEW_PEDS(int money)l
extern _native void SET_MONEY_CARRIED_BY_PED_WITH_MODEL(uint model, int m0, int m1)l
extern _native void SET_NM_ANIM_POSE(Ped ped, const char* AnimName0, const char* AnimName1, float pose)l
extern _native void SET_NM_MESSAGE_BOOL(int id, bool value)l
extern _native void SET_NM_MESSAGE_FLOAT(int id, float value)l
extern _native void SET_NM_MESSAGE_INSTANCE_INDEX(int id, Ped ped, Vehicle car, Object obj)l
extern _native void SET_NM_MESSAGE_INT(int id, int value)l
extern _native void SET_NM_MESSAGE_STRING(int id, const char* string)l
extern _native void SET_NM_MESSAGE_VEC3(int id, float x, float y, float z)l
extern _native void SET_PED_ALLOW_MISSION_ONLY_DRIVEBY_USE(Ped ped, bool set)l
extern _native void SET_PED_ALPHA(Ped ped, int alpha)l
extern _native void SET_PED_DENSITY_MULTIPLIER(float density)l
extern _native void SET_PED_DIES_WHEN_INJURED(Ped ped, bool value)l
extern _native void SET_PED_DONT_DO_EVASIVE_DIVES(Ped ped, bool value)l
extern _native void SET_PED_DONT_USE_VEHICLE_SPECIFIC_ANIMS(Ped ped, bool set)l
extern _native void SET_PED_ENABLE_LEG_IK(Ped ped, bool set)l
extern _native void SET_PED_FALL_OFF_BIKES_WHEN_SHOT(Ped ped, bool set)l
extern _native void SET_PED_FIRE_FX_LOD_SCALER(float scale)l
extern _native void SET_PED_FORCE_FLY_THROUGH_WINDSCREEN(Ped ped, bool set)l
extern _native void SET_PED_FORCE_VISUALISE_HEAD_DAMAGE_FROM_BULLETS(Ped ped, bool set)l
extern _native void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, bool set)l
extern _native void SET_PED_HEEDS_THE_EVERYONE_IGNORE_PLAYER_FLAG(Ped ped, bool set)l
extern _native void SET_PED_HELI_PILOT_RESPECTS_MINIMUMM_HEIGHT(Ped ped, bool set)l
extern _native void SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int index)l
extern _native void SET_PED_INSTANT_BLENDS_WEAPON_ANIMS(Ped ped, bool set)l
extern _native void SET_PED_IS_BLIND_RAGING(Ped ped, bool value)l
extern _native void SET_PED_IS_DRUNK(Ped ped, bool value)l
extern _native void SET_PED_MOBILE_RING_TYPE(Ped ped, int RingtoneId)l
extern _native void SET_PED_MOTION_BLUR(Ped ped, bool set)l
extern _native void SET_PED_NON_CREATION_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SET_PED_NON_REMOVAL_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SET_PED_PATH_MAY_DROP_FROM_HEIGHT(Ped ped, bool value)l
extern _native void SET_PED_PATH_MAY_USE_CLIMBOVERS(Ped ped, bool value)l
extern _native void SET_PED_PATH_MAY_USE_LADDERS(Ped ped, bool value)l
extern _native void SET_PED_PATH_WILL_AVOID_DYNAMIC_OBJECTS(Ped ped, bool set)l
extern _native void SET_PED_SKIPS_COMPLEX_COVER_COLLISION_CHECKS(Ped ped, bool set)l
extern _native void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, bool set)l
extern _native void SET_PED_STEERS_AROUND_PEDS(Ped ped, bool set)l
extern _native void SET_PED_WINDY_CLOTHING_SCALE(Ped ped, float scale)l
extern _native void SET_PED_WITH_BRAIN_CAN_BE_CONVERTED_TO_DUMMY_PED(Ped ped, bool set)l
extern _native void SET_REDUCE_PED_MODEL_BUDGET(bool set)l
extern _native void SET_RELATIONSHIP(uint relationshipLevel, eRelationshipGroup relationshipGroup1, eRelationshipGroup relationshipGroup2)l
extern _native void SET_ROMANS_MOOD(int moood)l
extern _native void SET_ROTATION_FOR_ATTACHED_PED(Ped ped, float xr, float yr, float zr)l
extern _native void SET_SCENARIO_PED_DENSITY_MULTIPLIER(float density, float densitynext)l
extern _native void SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float offset)l
extern _native void SET_SENSE_RANGE(Ped ped, float value)l
extern _native void SET_SPECIFIC_PASSENGER_INDEX_TO_USE_IN_GROUPS(Ped ped, int index)l
extern _native void SET_SWIM_SPEED(Ped ped, float speed)l
extern _native void STOP_PED_DOING_FALL_OFF_TESTS_WHEN_SHOT(Ped ped)l
extern _native void STOP_PED_MOBILE_RINGING(Ped ped)l
extern _native void STOP_PED_SPEAKING(Ped ped, bool stopspeaking)l
extern _native void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped)l
extern _native void SUPPRESS_PED_MODEL(uint model)l
extern _native void SWITCH_PED_TO_ANIMATED(Ped ped, bool unknownTrue)l
extern _native void UNLOCK_RAGDOLL(Ped ped, bool value)l
extern _native void UPDATE_PED_PHYSICAL_ATTACHMENT_POSITION(Ped ped, float x0, float y0, float z0, float x1, float y1)l
#pragma endregion//}
#pragma region VEHICLE//{
extern _native bool ARE_TAXI_LIGHTS_ON(Vehicle vehicle)l
extern _native bool CAN_BE_DESCRIBED_AS_A_CAR(Vehicle veh)l
extern _native bool CHECK_STUCK_TIMER(Vehicle car, int timernum, int timeout)l
extern _native bool CREATE_EMERGENCY_SERVICES_CAR(uint model, float x, float y, float z)l
extern _native bool CREATE_EMERGENCY_SERVICES_CAR_RETURN_DRIVER(uint model, float x, float y, float z, Vehicle *car, Ped *cardriver, Ped *carpass)l
extern _native bool CREATE_EMERGENCY_SERVICES_CAR_THEN_WALK(uint model, float x, float y, float z)l
extern _native bool DOES_CAR_HAVE_HYDRAULICS(Vehicle car)l
extern _native bool DOES_CAR_HAVE_ROOF(Vehicle vehicle)l
extern _native bool DOES_CAR_HAVE_STUCK_CAR_CHECK(Vehicle vehicle)l
extern _native bool DOES_VEHICLE_EXIST(Vehicle vehicle)l
extern _native bool GET_IS_STICKY_BOMB_STUCK_TO_VEHICLE(Vehicle veh)l
extern _native bool GET_VEHICLE_COMPONENT_INFO(Vehicle veh, int component_id, vector3 * Unk45, vector3 * Unk46, int * Unk47, bool flag)l
extern _native bool HAS_CAR_BEEN_DAMAGED_BY_CAR(Vehicle vehicle, Vehicle otherCar)l
extern _native bool HAS_CAR_BEEN_DAMAGED_BY_WEAPON(Vehicle vehicle, uint weapon)l
extern _native bool HAS_CAR_BEEN_DROPPED_OFF(Vehicle car)l
extern _native bool HAS_CAR_BEEN_RESPRAYED(Vehicle vehicle)l
extern _native bool HAS_CAR_RECORDING_BEEN_LOADED(int CarRec)l
extern _native bool HAS_CAR_STOPPED_BECAUSE_OF_LIGHT(Vehicle car)l
extern _native bool HAS_CHAR_BEEN_DAMAGED_BY_CAR(Ped ped, Vehicle vehicle)l
extern _native bool HAS_OBJECT_BEEN_DAMAGED_BY_CAR(Object obj, Vehicle vehicle)l
extern _native bool HAS_RESPRAY_HAPPENED(void)l
extern _native bool IS_BIG_VEHICLE(Vehicle vehicle)l
extern _native bool IS_CAR_ATTACHED(Vehicle vehicle)l
extern _native bool IS_CAR_A_MISSION_CAR(Vehicle vehicle)l
extern _native bool IS_CAR_DEAD(Vehicle vehicle)l
extern _native bool IS_CAR_DOOR_DAMAGED(Vehicle vehicle, uint door)l
extern _native bool IS_CAR_DOOR_FULLY_OPEN(Vehicle vehicle, uint door)l
extern _native bool IS_CAR_HEALTH_GREATER(Vehicle car, float health)l
extern _native bool IS_CAR_IN_AIR_PROPER(Vehicle vehicle)l
extern _native bool IS_CAR_IN_AREA_2D(Vehicle vehicle, float x1, float y1, float x2, float y2, bool unknownFalse)l
extern _native bool IS_CAR_IN_AREA_3D(Vehicle vehicle, float x1, float y1, float z1, float x2, float y2, float z2, uint unknownFalse)l
extern _native bool IS_CAR_IN_GARAGE_AREA(const char* garageName, Vehicle vehicle)l
extern _native bool IS_CAR_IN_WATER(Vehicle vehicle)l
extern _native bool IS_CAR_LOW_RIDER(Vehicle car)l
extern _native bool IS_CAR_MODEL(Vehicle vehicle, uint model)l
extern _native bool IS_CAR_ON_FIRE(Vehicle vehicle)l
extern _native bool IS_CAR_ON_SCREEN(Vehicle vehicle)l
extern _native bool IS_CAR_PASSENGER_SEAT_FREE(Vehicle vehicle, uint seatIndex)l
extern _native bool IS_CAR_PLAYING_ANIM(Vehicle car, const char* animname0, const char* animname1)l
extern _native bool IS_CAR_SIREN_ON(Vehicle vehicle)l
extern _native bool IS_CAR_STOPPED(Vehicle vehicle)l
extern _native bool IS_CAR_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle)l
extern _native bool IS_CAR_STREET_RACER(Vehicle car)l
extern _native bool IS_CAR_STUCK(Vehicle car)l
extern _native bool IS_CAR_STUCK_ON_ROOF(Vehicle vehicle)l
extern _native bool IS_CAR_TOUCHING_CAR(Vehicle vehicle, Vehicle otherCar)l
extern _native bool IS_CAR_TYRE_BURST(Vehicle vehicle, uint tyre)l
extern _native bool IS_CAR_UPRIGHT(Vehicle vehicle)l
extern _native bool IS_CAR_UPSIDEDOWN(Vehicle vehicle)l
extern _native bool IS_CAR_WAITING_FOR_WORLD_COLLISION(Vehicle vehicle)l
extern _native bool IS_CHAR_IN_CAR(Ped ped, Vehicle vehicle)l
extern _native bool IS_CHAR_IN_MODEL(Ped ped, uint model)l
extern _native bool IS_CHAR_TOUCHING_VEHICLE(Ped ped, Vehicle vehicle)l
extern _native bool IS_EMERGENCY_SERVICES_VEHICLE(Vehicle veh)l
extern _native bool IS_HELI_PART_BROKEN(Vehicle heli, bool flag0, bool flag1, bool flag2)l
extern _native bool IS_NEXT_STATION_ALLOWED(Vehicle veh)l
extern _native bool IS_PLAYBACK_GOING_ON_FOR_CAR(Vehicle car)l
extern _native bool IS_THIS_MODEL_A_BIKE(uint model)l
extern _native bool IS_THIS_MODEL_A_BOAT(uint model)l
extern _native bool IS_THIS_MODEL_A_CAR(uint model)l
extern _native bool IS_THIS_MODEL_A_HELI(uint model)l
extern _native bool IS_THIS_MODEL_A_PED(uint model)l
extern _native bool IS_THIS_MODEL_A_PLANE(uint model)l
extern _native bool IS_THIS_MODEL_A_TRAIN(uint model)l
extern _native bool IS_THIS_MODEL_A_VEHICLE(uint model)l
extern _native bool IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, uint extra)l
extern _native bool IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle)l
extern _native bool IS_VEHICLE_TOUCHING_OBJECT(Vehicle veh, Object obj)l
extern _native bool IS_VEH_DRIVEABLE(Vehicle vehicle)l
extern _native bool IS_VEH_STUCK(Vehicle veh, int time, bool flag0, bool flag1, bool flag2)l
extern _native bool IS_VEH_WINDOW_INTACT(Vehicle vehicle, uint window)l
extern _native bool LOCATE_CAR_2D(Vehicle car, float x0, float y0, float xUnk48, float yUnk49, bool flag)l
extern _native bool LOCATE_CAR_3D(Vehicle car, float x, float y, float z, float xa, float ya, float za, bool flag)l
extern _native bool LOCATE_DEAD_CAR_3D(Vehicle car, float x, float y, float z, float xa, float ya, float za, bool flag)l
extern _native bool PLAY_CAR_ANIM(Vehicle car, const char* animname0, const char* animname1, float Unk50, bool flag0, bool flag1)l
extern _native const char* GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(uint model)l
extern _native const char* GET_STATION_NAME(Train train, uint station)l
extern _native float FIND_POSITION_IN_RECORDING(Vehicle car)l
extern _native float FIND_TIME_POSITION_IN_RECORDING(Vehicle car)l
extern _native float GET_ENGINE_HEALTH(Vehicle vehicle)l
extern _native float GET_HEIGHT_OF_VEHICLE(Vehicle vehicle, float x, float y, float z, bool unknownTrue1, bool unknownTrue2)l
extern _native float GET_PETROL_TANK_HEALTH(Vehicle vehicle)l
extern _native float GET_TIME_TIL_NEXT_STATION(Vehicle train)l
extern _native float GET_TOTAL_DURATION_OF_CAR_RECORDING(int CarRec)l
extern _native float GET_VEHICLE_ENGINE_REVS(Vehicle veh)l
extern _native int FIND_TRAIN_DIRECTION(Vehicle train)l
extern _native int GET_CAR_SIREN_HEALTH(Vehicle car)l
extern _native int GET_CURRENT_PLAYBACK_NUMBER_FOR_CAR(Vehicle car)l
extern _native int GET_NUMBER_OF_STICKY_BOMBS_STUCK_TO_VEHICLE(Vehicle veh)l
extern _native int GET_VEHICLE_GEAR(Vehicle veh)l
extern _native int GET_VEHICLE_TYPE_OF_MODEL(uint model)l
extern _native int SET_HELI_FORCE_ENGINE_ON(Vehicle heli, bool set)l
extern _native ScriptAny SET_CAR_ON_GROUND_PROPERLY(Vehicle vehicle)l
extern _native uint GET_CURRENT_STATION_FOR_TRAIN(Train train)l
extern _native uint GET_VEHICLE_MODEL_FROM_INDEX(int index)l
extern _native Vehicle GET_CAR_OBJECT_IS_ATTACHED_TO(Object obj)l
extern _native Vehicle GET_CLOSEST_CAR(float x, float y, float z, float radius, bool unknownFalse, uint unknown70)l
extern _native void ACTIVATE_HELI_SPEED_CHEAT(Vehicle heli, int cheat)l	//10
extern _native void ADD_CAR_TO_MISSION_DELETION_LIST(Vehicle car)l
extern _native void ADD_STUCK_CAR_CHECK(Vehicle car, float stuckdif, int timeout)l
extern _native void ADD_STUCK_CAR_CHECK_WITH_WARP(Vehicle car, float stuckdif, int time, bool flag0, bool flag1, bool flag2, bool flag3)l
extern _native void ADD_UPSIDEDOWN_CAR_CHECK(Vehicle vehicle)l
extern _native void ANCHOR_BOAT(Vehicle boat, bool anchor)l
extern _native void APPLY_FORCE_TO_CAR(Vehicle vehicle, uint unknown0_3, float x, float y, float z, float spinX, float spinY, float spinZ, uint unknown4_0, uint unknown5_1, uint unknown6_1, uint unknown7_1)l
extern _native void ATTACH_CAR_TO_CAR(Vehicle car0, Vehicle car1, int Unk51, float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void ATTACH_CAR_TO_CAR_PHYSICALLY(int vehid1, int vehid2, bool Unk52, int Unk53, float xoffset, float yoffset, float zoffset, float xbuffer, float ybuffer, float zbuffer, float xrotateveh1, float yrotateveh1, float Unk54, float Unk55, float Unk56)l
extern _native void ATTACH_CAR_TO_OBJECT(Vehicle car, Object obj, float Unk57, float Unk58, float Unk59, float Unk60, float Unk61, float Unk62, float Unk63)l
extern _native void ATTACH_PED_TO_CAR(Ped ped, Vehicle vehicle, uint unknown0_0, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, bool Unk64, bool Unk65)l
extern _native void BREAK_CAR_DOOR(Vehicle vehicle, uint door, bool unknownFalse)l
extern _native void BURST_CAR_TYRE(Vehicle vehicle, uint tyre)l
extern _native void CHANGE_CAR_COLOUR(Vehicle vehicle, ColourIndex colour1, ColourIndex colour2)l
extern _native void CHANGE_PLAYBACK_TO_USE_AI(Vehicle car)l
extern _native void CLEAR_CAR_LAST_DAMAGE_ENTITY(Vehicle vehicle)l
extern _native void CLEAR_CAR_LAST_WEAPON_DAMAGE(Vehicle vehicle)l
extern _native void CLEAR_ROOM_FOR_CAR(Vehicle vehicle)l
extern _native void CLOSE_ALL_CAR_DOORS(Vehicle vehicle)l
extern _native void CONTROL_CAR_DOOR(Vehicle vehicle, uint door, uint unknown_maybe_open, float angle)l
extern _native void CREATE_CAR(uint nameHash, float x, float y, float z, Vehicle *pVehicle, bool unknownTrue)l
extern _native void CREATE_CARS_ON_GENERATORS_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void CREATE_CAR_GENERATOR(float x, float y, float z, float yaw, float pitch, float roll, uint model, uint color1, uint color2, uint spec1, uint spec2, int Unk66, bool alarm, bool doorlock, int *handle)l
extern _native void CREATE_MISSION_TRAIN(uint unknown1, float x, float y, float z, bool unknown2, Train *pTrain)l
extern _native void CREATE_RANDOM_CAR_FOR_CAR_PARK(float x, float y, float z, float radius)l
extern _native void CREATE_RANDOM_CHAR_AS_DRIVER(Vehicle vehicle, Ped *pPed)l
extern _native void DAMAGE_CAR(Vehicle car, float x, float y, float z, float unkforce0, float unkforce1, bool flag)l
extern _native void DELETE_ALL_TRAINS(void)l
extern _native void DELETE_CAR(Vehicle *pVehicle)l
extern _native void DELETE_CAR_GENERATOR(int handle)l
extern _native void DELETE_MISSION_TRAIN(Train *pTrain)l
extern _native void DELETE_MISSION_TRAINS(void)l
extern _native void DETACH_CAR(Vehicle vehicle)l
extern _native void DISABLE_CAR_GENERATORS(bool flag0, bool flag1)l
extern _native void DISABLE_CAR_GENERATORS_WITH_HELI(bool disable)l
extern _native void DONT_SUPPRESS_ANY_CAR_MODELS(void)l
extern _native void DONT_SUPPRESS_CAR_MODEL(uint model)l
extern _native void ENABLE_GPS_IN_VEHICLE(Vehicle veh, bool enable)l
extern _native void FIX_CAR(Vehicle vehicle)l
extern _native void FIX_CAR_TYRE(Vehicle vehicle, uint tyre)l
extern _native void FORCE_ALL_VEHICLE_LIGHTS_OFF(bool off)l
extern _native void FORCE_CAR_LIGHTS(Vehicle car, int lights)l
extern _native void FORCE_GENERATE_PARKED_CARS_TOO_CLOSE_TO_OTHERS(bool set)l
extern _native void FORCE_RANDOM_CAR_MODEL(uint hash)l
extern _native void FREEZE_CAR_POSITION(Vehicle vehicle, bool frozen)l
extern _native void FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION(Vehicle vehicle, bool frozen)l
extern _native void GET_CAR_ANIM_CURRENT_TIME(Vehicle car, const char* animname0, const char* animname1, float *time)l
extern _native void GET_CAR_ANIM_TOTAL_TIME(Vehicle car, const char* animname0, const char* animname1, float *time)l
extern _native void GET_CAR_BLOCKING_CAR(Vehicle car0, Vehicle *car1)l
extern _native void GET_CAR_CHAR_IS_USING(Ped ped, Vehicle *pVehicle)l
extern _native void GET_CAR_COLOURS(Vehicle vehicle, ColourIndex *pColour1, ColourIndex *pColour2)l
extern _native void GET_CAR_COORDINATES(Vehicle vehicle, float *pX, float *pY, float *pZ)l
extern _native void GET_CAR_DEFORMATION_AT_POS(Vehicle vehicle, float x, float y, float z, vector3 *pDeformation)l
extern _native void GET_CAR_DOOR_LOCK_STATUS(Vehicle vehicle, uint *pValue)l
extern _native void GET_CAR_FORWARD_VECTOR(Vehicle car, vector3 *vec)l
extern _native void GET_CAR_FORWARD_X(Vehicle vehicle, float *pValue)l
extern _native void GET_CAR_FORWARD_Y(Vehicle vehicle, float *pValue)l
extern _native void GET_CAR_HEADING(Vehicle vehicle, float *pValue)l
extern _native void GET_CAR_HEALTH(Vehicle vehicle, uint *pValue)l
extern _native void GET_CAR_LIVERY(Vehicle car, int *livery)l
extern _native void GET_CAR_MASS(Vehicle car, float *mass)l
extern _native void GET_CAR_MODEL(Vehicle vehicle, uint *pValue)l
extern _native void GET_CAR_MODEL_VALUE(Vehicle car, int *value)l
extern _native void GET_CAR_PITCH(Vehicle vehicle, float *pValue)l
extern _native void GET_CAR_ROLL(Vehicle vehicle, float *pValue)l
extern _native void GET_CAR_SPEED(Vehicle vehicle, float *pValue)l
extern _native void GET_CAR_SPEED_VECTOR(Vehicle vehicle, vector3 *pVector, bool unknownFalse)l
extern _native void GET_CAR_UPRIGHT_VALUE(Vehicle vehicle, float *pValue)l
extern _native void GET_CURRENT_TAXI_CAR_MODEL(uint *pModel)l
extern _native void GET_DEAD_CAR_COORDINATES(Vehicle vehicle, float *pX, float *pY, float *pZ)l
extern _native void GET_DOOR_ANGLE_RATIO(Vehicle vehicle, uint door, float *pAngleRatio)l
extern _native void GET_EXTRA_CAR_COLOURS(Vehicle vehicle, ColourIndex *pColour1, ColourIndex *pColour2)l
extern _native void GET_KEY_FOR_CAR_IN_ROOM(Vehicle vehicle, uint *pKey)l
extern _native void GET_MAXIMUM_NUMBER_OF_PASSENGERS(Vehicle vehicle, uint *pMax)l
extern _native void GET_NEAREST_CABLE_CAR(float x, float y, float z, float radius, Vehicle *pVehicle)l
extern _native void GET_NUMBER_OF_PASSENGERS(Vehicle vehicle, uint *pNumPassengers)l
extern _native void GET_NUM_CAR_COLOURS(Vehicle vehicle, uint *pNumColours)l
extern _native void GET_NUM_CAR_LIVERIES(Vehicle car, int *num)l
extern _native void GET_OFFSETS_FOR_ATTACH_CAR_TO_CAR(Vehicle car0, Vehicle car1, vector3 * Unk67, vector3 * Unk68)l
extern _native void GET_OFFSET_FROM_CAR_GIVEN_WORLD_COORDS(Vehicle vehicle, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ)l
extern _native void GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(Vehicle vehicle, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ)l
extern _native void GET_PLANE_UNDERCARRIAGE_POSITION(Vehicle plane, float *pos)l
extern _native void GET_POSITION_OF_CAR_RECORDING_AT_TIME(int CarRec, float time, float *pos)l
extern _native void GET_TRAIN_CABOOSE(Vehicle train, Vehicle *caboose)l
extern _native void GET_TRAIN_CARRIAGE(Vehicle train, int num, Vehicle *carriage)l
extern _native void GET_TRAIN_PLAYER_WOULD_ENTER(int player, int *train)l
extern _native void GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float* pIntensity)l
extern _native void GET_VEHICLE_PLAYER_WOULD_ENTER(int player, Vehicle *veh)l
extern _native void GET_VEHICLE_QUATERNION(Vehicle veh, float *qx, float *qy, float *qz, float *qw)l
extern _native void HAND_VEHICLE_CONTROL_BACK_TO_PLAYER(Vehicle veh)l
extern _native void LOCK_CAR_DOORS(Vehicle vehicle, uint value)l
extern _native void MARK_CAR_AS_CONVOY_CAR(Vehicle vehicle, bool convoyCar)l
extern _native void MARK_CAR_AS_NO_LONGER_NEEDED(Vehicle *pVehicle)l
extern _native void MARK_MISSION_TRAINS_AS_NO_LONGER_NEEDED(void)l
extern _native void MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Train train)l
extern _native void OPEN_CAR_DOOR(Vehicle vehicle, uint door)l
extern _native void OVERRIDE_NUMBER_OF_PARKED_CARS(int num)l
extern _native void PAUSE_PLAYBACK_RECORDED_CAR(Vehicle car)l
extern _native void PLANE_STARTS_IN_AIR(Vehicle plane)l
extern _native void POP_CAR_BOOT(Vehicle vehicle)l
extern _native void REMOVE_CARS_FROM_GENERATORS_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void REMOVE_CAR_RECORDING(int CarRec)l
extern _native void REMOVE_CAR_WINDOW(Vehicle car, int windnum)l
extern _native void REMOVE_STUCK_CAR_CHECK(Vehicle vehicle)l
extern _native void REMOVE_UPSIDEDOWN_CAR_CHECK(Vehicle vehicle)l
extern _native void RESET_CAR_WHEELS(Vehicle car, bool reset)l
extern _native void RESET_STUCK_TIMER(Vehicle car, int timer_num)l
extern _native void SELECT_WEAPONS_FOR_VEHICLE(Vehicle veh, int weapon)l
extern _native void SET_ALL_CARS_CAN_BE_DAMAGED(bool set)l
extern _native void SET_ALL_CAR_GENERATORS_BACK_TO_ACTIVE(void)l
extern _native void SET_AMBIENT_PLANES_SPEED_MULTIPLIER(float multiplier)l
extern _native void SET_BIKE_RIDER_WILL_PUT_FOOT_DOWN_WHEN_STOPPED(Vehicle bike, bool set)l
extern _native void SET_BLIP_THROTTLE_RANDOMLY(Vehicle veh, bool set)l
extern _native void SET_CAN_BURST_CAR_TYRES(Vehicle car, bool set)l
extern _native void SET_CAN_RESPRAY_CAR(Vehicle car, bool can)l
extern _native void SET_CAR_ALLOWED_TO_DROWN(Vehicle car, bool allowed)l
extern _native void SET_CAR_ALWAYS_CREATE_SKIDS(Vehicle car, bool set)l
extern _native void SET_CAR_ANIM_CURRENT_TIME(Vehicle car, const char* animname0, const char* animname1, float time)l
extern _native void SET_CAR_ANIM_SPEED(Vehicle car, const char* animname0, const char* animname1, float speed)l
extern _native void SET_CAR_AS_MISSION_CAR(Vehicle car)l
extern _native void SET_CAR_CAN_BE_DAMAGED(Vehicle vehicle, bool value)l
extern _native void SET_CAR_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, bool value)l
extern _native void SET_CAR_COLLISION(Vehicle car, bool set)l
extern _native void SET_CAR_COLOUR_COMBINATION(Vehicle car, int combination)l
extern _native void SET_CAR_COORDINATES(Vehicle vehicle, float pX, float pY, float pZ)l
extern _native void SET_CAR_COORDINATES_NO_OFFSET(Vehicle car, float x, float y, float z)l
extern _native void SET_CAR_DENSITY_MULTIPLIER(float density)l
extern _native void SET_CAR_DISTANCE_AHEAD_MULTIPLIER(Vehicle car, float multiplier)l
extern _native void SET_CAR_DOOR_LATCHED(Vehicle car, int door, bool flag0, bool flag1)l
extern _native void SET_CAR_ENGINE_ON(Vehicle car, bool flag0, bool flag1)l
extern _native void SET_CAR_FORWARD_SPEED(Vehicle vehicle, float speed)l
extern _native void SET_CAR_FOV_FADE_MULT(float multiplier)l
extern _native void SET_CAR_FOV_MAX(float maxfov)l
extern _native void SET_CAR_FOV_MIN(float minfov)l
extern _native void SET_CAR_FOV_RATE(float rate)l
extern _native void SET_CAR_FOV_START_SPEED(float speed)l
extern _native void SET_CAR_FOV_START_SPEED_BOAT(float speed)l
extern _native void SET_CAR_GENERATORS_ACTIVE_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1, bool set)l
extern _native void SET_CAR_HEADING(Vehicle vehicle, float dir)l
extern _native void SET_CAR_HEALTH(Vehicle vehicle, uint Value)l
extern _native void SET_CAR_IN_CUTSCENE(Vehicle car, bool set)l
extern _native void SET_CAR_LANE_SHIFT(Vehicle car, float shift)l
extern _native void SET_CAR_LIGHT_MULTIPLIER(Vehicle car, float multiplier)l
extern _native void SET_CAR_LIVERY(Vehicle car, int livery)l
extern _native void SET_CAR_MOTION_BLUR_EFFECT_BOAT(float blur)l
extern _native void SET_CAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP(Vehicle car, bool set, int group)l
extern _native void SET_CAR_ONLY_DAMAGED_BY_PLAYER(Vehicle car, bool set)l
extern _native void SET_CAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Vehicle car, bool set, int group)l
extern _native void SET_CAR_PROOFS(Vehicle vehicle, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof)l
extern _native void SET_CAR_RANDOM_ROUTE_SEED(Vehicle car, int seed)l
extern _native void SET_CAR_STAY_IN_FAST_LANE(Vehicle car, bool set)l
extern _native void SET_CAR_STAY_IN_SLOW_LANE(Vehicle car, bool set)l
extern _native void SET_CAR_STRONG(Vehicle vehicle, bool strong)l
extern _native void SET_CAR_TRACTION(Vehicle car, float traction)l
extern _native void SET_CAR_VISIBLE(Vehicle vehicle, bool value)l
extern _native void SET_CAR_WATERTIGHT(Vehicle car, bool set)l
extern _native void SET_CONVERTIBLE_ROOF(Vehicle car, bool set)l
extern _native void SET_ENGINE_HEALTH(Vehicle vehicle, float health)l
extern _native void SET_EXTRA_CAR_COLOURS(Vehicle vehicle, ColourIndex colour1, ColourIndex colour2)l
extern _native void SET_FREEBIES_IN_VEHICLE(Vehicle veh, bool set)l
extern _native void SET_FREE_RESPRAYS(bool set)l
extern _native void SET_GANG_CAR(Vehicle car, bool set)l
extern _native void SET_GPS_REMAINS_WHEN_TARGET_REACHED_FLAG(bool set)l
extern _native void SET_GPS_TEST_IN_3D_FLAG(bool set)l
extern _native void SET_HAS_BEEN_OWNED_BY_PLAYER(Vehicle car, bool set)l
extern _native void SET_HAS_BEEN_OWNED_FOR_CAR_GENERATOR(int CarGen, bool set)l
extern _native void SET_HELI_BLADES_FULL_SPEED(Vehicle heli)l
extern _native void SET_HELI_STABILISER(Vehicle heli, bool set)l
extern _native void SET_IGNORE_NO_GPS_FLAG(bool set)l
extern _native void SET_INTERP_IN_OUT_VEHICLE_ENABLED_THIS_FRAME(bool set)l
extern _native void SET_LOAD_COLLISION_FOR_CAR_FLAG(Vehicle car, bool set)l
extern _native void SET_MISSION_TRAIN_COORDINATES(Vehicle train, float x, float y, float z)l
extern _native void SET_NEEDS_TO_BE_HOTWIRED(Vehicle veh, bool set)l
extern _native void SET_NO_RESPRAYS(bool set)l
extern _native void SET_PARKED_CAR_DENSITY_MULTIPLIER(float multiplier)l
extern _native void SET_PETROL_TANK_HEALTH(Vehicle vehicle, float value)l
extern _native void SET_PETROL_TANK_WEAKPOINT(Vehicle car, bool set)l
extern _native void SET_PLANE_THROTTLE(Vehicle plane, float throttle)l
extern _native void SET_PLANE_UNDERCARRIAGE_UP(Vehicle plain, bool set)l
extern _native void SET_PLAYBACK_SPEED(Vehicle car, float speed)l
extern _native void SET_RANDOM_CAR_DENSITY_MULTIPLIER(float density)l
extern _native void SET_RECORDING_TO_POINT_NEAREST_TO_COORS(Vehicle cat, float x, float y, float z)l
extern _native void SET_REDUCE_VEHICLE_MODEL_BUDGET(bool set)l
extern _native void SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, bool set)l
extern _native void SET_ROCKET_LAUNCHER_FREEBIE_IN_HELI(bool set)l
extern _native void SET_ROOM_FOR_CAR_BY_KEY(Vehicle car, uint roomkey)l
extern _native void SET_ROOM_FOR_CAR_BY_NAME(Vehicle car, const char* roomname)l
extern _native void SET_SIREN_WITH_NO_DRIVER(Vehicle car, bool set)l
extern _native void SET_SUPPRESS_HEADLIGHT_SWITCH(bool set)l
extern _native void SET_TARGET_CAR_FOR_MISSION_GARAGE(int garage, Vehicle car)l
extern _native void SET_TAXI_LIGHTS(Vehicle car, bool set)l
extern _native void SET_TRAIN_AUDIO_ROLLOFF(Vehicle train, float rolloff)l
extern _native void SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed)l
extern _native void SET_TRAIN_FORCED_TO_SLOW_DOWN(Vehicle train, bool set)l
extern _native void SET_TRAIN_IS_STOPPED_AT_STATION(Vehicle train)l
extern _native void SET_TRAIN_SPEED(Vehicle train, float speed)l
extern _native void SET_TRAIN_STOPS_FOR_STATIONS(Vehicle train, bool set)l
extern _native void SET_UPSIDEDOWN_CAR_NOT_DAMAGED(Vehicle car, bool set)l
extern _native void SET_VEHICLE_ALPHA(Vehicle veh, int alpha)l
extern _native void SET_VEHICLE_ALWAYS_RENDER(Vehicle veh)l
extern _native void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle veh, bool set)l
extern _native void SET_VEHICLE_DEFORMATION_MULT(Vehicle veh, float multiplier)l
extern _native void SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float intensity)l
extern _native void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle veh, bool set)l
extern _native void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle veh, bool set)l
extern _native void SET_VEHICLE_QUATERNION(Vehicle veh, float qx, float qy, float qz, float qw)l
extern _native void SET_VEHICLE_RENDER_SCORCHED(Vehicle veh, bool set)l
extern _native void SET_VEHICLE_STEER_BIAS(Vehicle veh, float val)l
extern _native void SET_VEH_ALARM(Vehicle veh, bool set)l
extern _native void SET_VEH_ALARM_DURATION(Vehicle veh, int duration)l
extern _native void SET_VEH_HAS_STRONG_AXLES(Vehicle veh, bool set)l
extern _native void SET_VEH_HAZARDLIGHTS(Vehicle vehicle, bool on)l
extern _native void SET_VEH_INDICATORLIGHTS(Vehicle veh, bool set)l
extern _native void SET_VEH_INTERIORLIGHT(Vehicle veh, bool set)l
extern _native void SHUT_CAR_DOOR(Vehicle vehicle, uint door)l
extern _native void SKIP_IN_PLAYBACK_RECORDED_CAR(Vehicle car, float time)l
extern _native void SKIP_TIME_IN_PLAYBACK_RECORDED_CAR(int CarRec, float time)l
extern _native void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_CAR(Vehicle car)l
extern _native void SKIP_TO_NEXT_ALLOWED_STATION(Vehicle train)l
extern _native void SMASH_CAR_WINDOW(Vehicle car, int windownum)l
extern _native void SOUND_CAR_HORN(Vehicle vehicle, uint duration)l
extern _native void START_PLAYBACK_RECORDED_CAR(Vehicle car, int CarRec)l
extern _native void START_PLAYBACK_RECORDED_CAR_LOOPED(Vehicle car, int Unk69)l
extern _native void START_PLAYBACK_RECORDED_CAR_USING_AI(Vehicle car, int CarRec)l
extern _native void START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(Vehicle car, int CarRec, float x, float y, float z)l
extern _native void STOP_CAR_BREAKING(Vehicle car, bool stop)l
extern _native void STOP_PLAYBACK_RECORDED_CAR(Vehicle car)l
extern _native void STOP_VEHICLE_ALWAYS_RENDER(Vehicle veh)l
extern _native void STORE_CAR_CHAR_IS_IN_NO_SAVE(Ped ped, Vehicle *car)l
extern _native void SUPPRESS_CAR_MODEL(uint model)l
extern _native void SWITCH_CAR_GENERATOR(int handle, int type)l
extern _native void SWITCH_CAR_SIREN(Vehicle car, bool siren)l
extern _native void TRAIN_LEAVE_STATION(Vehicle train)l
extern _native void TRIGGER_VEH_ALARM(Vehicle car)l
extern _native void TURN_CAR_TO_FACE_COORD(Vehicle car, float x, float y)l
extern _native void TURN_OFF_VEHICLE_EXTRA(Vehicle veh, int extra, bool turnoff)l
extern _native void UNPAUSE_PLAYBACK_RECORDED_CAR(Vehicle car)l
extern _native void VEHICLE_CAN_BE_TARGETTED_BY_HS_MISSILE(Vehicle car, bool set)l
extern _native void VEHICLE_DOES_PROVIDE_COVER(Vehicle veh, bool cover)l
extern _native void WARP_CHAR_FROM_CAR_TO_CAR(Ped ped, Vehicle vehicle, uint seatIndex)l
extern _native void WARP_CHAR_FROM_CAR_TO_COORD(Ped ped, float x, float y, float z)l
extern _native void WARP_CHAR_INTO_CAR(Ped ped, Vehicle vehicle)l
extern _native void WARP_CHAR_INTO_CAR_AS_PASSENGER(Ped ped, Vehicle vehicle, uint seatIndex)l
extern _native void WASH_VEHICLE_TEXTURES(Vehicle vehicle, uint intensity)l
#pragma endregion//}
#pragma region OBJECT//{
extern _native bool DOES_OBJECT_EXIST(Object obj)l
extern _native bool DOES_OBJECT_HAVE_PHYSICS(Object obj)l
extern _native bool DOES_OBJECT_HAVE_THIS_MODEL(Object obj, uint model)l
extern _native bool DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(float x, float y, float z, float radius, uint model)l
extern _native bool GET_IS_STICKY_BOMB_STUCK_TO_OBJECT(Object obj)l
extern _native bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED_BY_CAR(float x, float y, float z, float radius, uint type_or_model, Vehicle car)l
extern _native bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED_BY_CHAR(float x, float y, float z, float radius, uint objectModel, Ped ped)l
extern _native bool HAS_FRAGMENT_ROOT_OF_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED(float x, float y, float z, float radius, uint Unk70)l
extern _native bool HAS_OBJECT_BEEN_DAMAGED(Object obj)l
extern _native bool HAS_OBJECT_BEEN_DAMAGED_BY_CHAR(Object obj, Ped ped)l
extern _native bool HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON(Object obj, int Unk71)l
extern _native bool HAS_OBJECT_BEEN_PHOTOGRAPHED(Object obj)l
extern _native bool HAS_OBJECT_BEEN_UPROOTED(Object obj)l
extern _native bool HAS_OBJECT_COLLIDED_WITH_ANYTHING(Object obj)l
extern _native bool HAS_OBJECT_FRAGMENT_ROOT_BEEN_DAMAGED(Object obj)l
extern _native bool HAS_POOL_OBJECT_COLLIDED_WITH_CUSHION(Object obj)l
extern _native bool HAS_POOL_OBJECT_COLLIDED_WITH_OBJECT(Object obj, Object otherObj)l
extern _native bool IS_CLOSEST_OBJECT_OF_TYPE_SMASHED_OR_DAMAGED(float x, float y, float z, float radius, uint type_or_model, bool flag0, bool flag1)l
extern _native bool IS_GARAGE_CLOSED(const char* garageName)l
extern _native bool IS_GARAGE_OPEN(const char* garageName)l
extern _native bool IS_NON_FRAG_OBJECT_SMASHED(float x, float y, float z, float radius, uint model)l
extern _native bool IS_OBJECT_ATTACHED(Object obj)l
extern _native bool IS_OBJECT_IN_ANGLED_AREA_3D(Object obj, float x0, float y0, float z0, float x1, float y1, float z1, float Unk72, bool flag)l
extern _native bool IS_OBJECT_IN_AREA_2D(Object obj, float x0, float y0, float x1, float y2, bool flag)l
extern _native bool IS_OBJECT_IN_AREA_3D(Object obj, float x0, float y0, float z0, float x1, float y1, float z1, bool flag)l
extern _native bool IS_OBJECT_IN_WATER(Object obj)l
extern _native bool IS_OBJECT_ON_FIRE(Object obj)l
extern _native bool IS_OBJECT_ON_SCREEN(Object obj)l
extern _native bool IS_OBJECT_PLAYING_ANIM(Object obj, const char* animname0, const char* animname1)l
extern _native bool IS_OBJECT_STATIC(Object obj)l
extern _native bool IS_OBJECT_TOUCHING_OBJECT(Object obj0, Object obj1)l
extern _native bool IS_OBJECT_UPRIGHT(Object obj, float angle)l
extern _native bool IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Object obj)l
extern _native bool IS_SITTING_OBJECT_NEAR(float x, float y, float z, int Unk73)l
extern _native bool LOCATE_OBJECT_2D(Object obj, float x0, float y0, float x1, float y1, bool flag)l
extern _native bool LOCATE_OBJECT_3D(Object obj, float x, float y, float z, float xr, float yr, float zr, bool flag)l
extern _native bool PLAY_OBJECT_ANIM(Object obj, const char* animname0, const char* animname1, float Unk74, bool flag0, bool flag1)l
extern _native bool ROTATE_OBJECT(Object obj, float x, float y, bool flag)l
extern _native bool SLIDE_OBJECT(Object obj, float x, float y, float z, float xs, float ys, float zs, bool flag)l
extern _native bool SMASH_GLASS_ON_OBJECT(float x, float y, float z, float Unk75, uint model, float Unk76)l
extern _native float GET_FRAGMENT_DAMAGE_HEALTH_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, uint Unk77, bool flag)l
extern _native float GET_LEVEL_DESIGN_COORDS_FOR_OBJECT(Object obj, int Unk78, float *x, float *y, float *z)l
extern _native float GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(Object obj, bool unknown)l
extern _native int GET_NUMBER_OF_STICKY_BOMBS_STUCK_TO_OBJECT(Object obj)l
extern _native Object GET_OBJECT_PED_IS_HOLDING(Ped ped)l
extern _native Object WHAT_WILL_PLAYER_PICKUP(int player)l
extern _native uint GET_MODEL_PED_IS_HOLDING(Ped ped)l
extern _native void ADD_OBJECT_TO_INTERIOR_ROOM_BY_KEY(Object obj, uint roomKey)l
extern _native void ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(Object obj, const char* room_name)l
extern _native void ADD_STUNT_JUMP(float x, float y, float z, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int reward)l
extern _native void ANCHOR_OBJECT(Object obj, bool anchor, uint flags)l
extern _native void APPLY_FORCE_TO_OBJECT(Object obj, uint uk0_3, float pX, float pY, float pZ, float spinX, float spinY, float spinZ, uint uk4_0, uint uk5_1, uint uk6_1, uint uk7_1)l
extern _native void ATTACH_OBJECT_TO_CAR(Object obj, Vehicle v, uint unknown0_0, float pX, float pY, float pZ, float rX, float rY, float rZ)l
extern _native void ATTACH_OBJECT_TO_CAR_PHYSICALLY(Object obj, Vehicle car, ScriptAny Unk79, ScriptAny Unk80, ScriptAny Unk81, ScriptAny Unk82, ScriptAny Unk83, ScriptAny Unk84, ScriptAny Unk85, ScriptAny Unk86, ScriptAny Unk87, ScriptAny Unk88, ScriptAny Unk89, ScriptAny Unk90, bool flag)l
extern _native void ATTACH_OBJECT_TO_OBJECT(Object obj0, Object obj1_attach_to, int Unk91, float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void ATTACH_OBJECT_TO_PED(Object obj, Ped c, uint bone, float pX, float pY, float pZ, float rX, float rY, float rZ, uint unknown1_0)l
extern _native void ATTACH_OBJECT_TO_PED_PHYSICALLY(Object obj, Ped c, bool unknown, uint bone, float pX, float pY, float pZ, float rX, float rY, float rZ, uint unknown1_0, uint unknown2_0)l
extern _native void ATTACH_PARACHUTE_MODEL_TO_PLAYER(Ped ped, Object obj)l
extern _native void CHANGE_GARAGE_TYPE(int garage, int type)l
extern _native void CLEAR_OBJECT_LAST_DAMAGE_ENTITY(Object obj)l
extern _native void CLEAR_OBJECT_LAST_WEAPON_DAMAGE(Object obj)l
extern _native void CLEAR_ROOM_FOR_OBJECT(Object obj)l
extern _native void CLOSE_GARAGE(const char* garageName)l
extern _native void CONNECT_LODS(Object obj0, Object obj1)l
extern _native void CREATE_OBJECT(uint model, float x, float y, float z, Object *pObj, bool unknownTrue)l
extern _native void CREATE_OBJECT_NO_OFFSET(uint model, float x, float y, float z, Object *pObj, bool unknownTrue)l
extern _native void DELETE_OBJECT(Object *pObj)l
extern _native void DETACH_OBJECT(Object obj, bool unknown)l
extern _native void DETACH_OBJECT_NO_COLLIDE(Object obj, bool flag)l
extern _native void DONT_REMOVE_OBJECT(Object obj)l
extern _native void DROP_OBJECT(Ped ped, bool unknownTrue)l
extern _native void ENABLE_DISABLED_ATTRACTORS_ON_OBJECT(Object obj, bool enable)l
extern _native void FREEZE_OBJECT_POSITION(Object obj, bool frozen)l
extern _native void FREEZE_OBJECT_POSITION(Object obj, bool set)l
extern _native void FREEZE_OBJECT_POSITION_AND_DONT_LOAD_COLLISION(Object obj, bool freeze)l
extern _native void FREEZE_POSITION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, uint model, bool frozen)l
extern _native void GET_CLOSEST_STEALABLE_OBJECT(float x, float y, float z, float radius, Object *obj)l
extern _native void GET_DOOR_STATE(Object obj, uint * Unk92, float * Unk93)l
extern _native void GET_OBJECT_ANIM_CURRENT_TIME(Object obj, const char* animname0, const char* animname1, float *time)l
extern _native void GET_OBJECT_ANIM_TOTAL_TIME(Object obj, const char* animname0, const char* animname1, float *time)l
extern _native void GET_OBJECT_COORDINATES(Object obj, float *pX, float *pY, float *pZ)l
extern _native void GET_OBJECT_HEADING(Object obj, float *pHeading)l
extern _native void GET_OBJECT_HEALTH(Object obj, float *pHealth)l
extern _native void GET_OBJECT_MASS(Object obj, float *mass)l
extern _native void GET_OBJECT_MODEL(Object obj, uint *pModel)l
extern _native void GET_OBJECT_QUATERNION(Object obj, float *qx, float *qy, float *qz, float *qw)l
extern _native void GET_OBJECT_ROTATION_VELOCITY(Object obj, float *pX, float *pY, float *pZ)l
extern _native void GET_OBJECT_SPEED(Object obj, float *pSpeed)l
extern _native void GET_OBJECT_TURN_MASS(Object obj, float *turnmass)l
extern _native void GET_OBJECT_VELOCITY(Object obj, float *pX, float *pY, float *pZ)l
extern _native void GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(Object obj, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ)l
extern _native void GET_ROOM_KEY_FROM_OBJECT(Object obj, uint *pRoomKey)l
extern _native void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(uint model, float x, float y, float z, int *state, float * Unk94)l
extern _native void GRAB_NEARBY_OBJECT_WITH_SPECIAL_ATTRIBUTE(int attribute, Object *obj)l
extern _native void MAKE_OBJECT_TARGETTABLE(Object obj, bool targettable)l
extern _native void MARK_OBJECT_AS_NO_LONGER_NEEDED(Object *pObj)l
extern _native void OPEN_GARAGE(const char* name)l
extern _native void PLACE_OBJECT_RELATIVE_TO_CAR(Object obj, Vehicle car, float x, float y, float z)l
extern _native void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Object obj, bool set)l
extern _native void SET_DOOR_STATE(Object door, bool flag, float Unk95)l
extern _native void SET_GARAGE_LEAVE_CAMERA_ALONE(const char* garageName, bool set)l
extern _native void SET_HEADING_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, uint type_or_model, float heading)l
extern _native void SET_LOAD_COLLISION_FOR_OBJECT_FLAG(Object obj, bool set)l
extern _native void SET_OBJECT_ALPHA(Object obj, int alpha)l
extern _native void SET_OBJECT_ANIM_CURRENT_TIME(Object obj, const char* animname0, const char* animname1, float time)l
extern _native void SET_OBJECT_ANIM_PLAYING_FLAG(Object obj, const char* animname0, const char* animname1, bool flag)l
extern _native void SET_OBJECT_ANIM_SPEED(Object obj, const char* animname0, const char* animname1, float speed)l
extern _native void SET_OBJECT_AS_STEALABLE(Object obj, bool set)l
extern _native void SET_OBJECT_CCD(Object obj, bool set)l
extern _native void SET_OBJECT_COLLISION(Object obj, bool value)l
extern _native void SET_OBJECT_COORDINATES(Object obj, float pX, float pY, float pZ)l
extern _native void SET_OBJECT_DRAW_LAST(Object obj, bool set)l
extern _native void SET_OBJECT_DYNAMIC(Object obj, bool set)l
extern _native void SET_OBJECT_HEADING(Object obj, float value)l
extern _native void SET_OBJECT_HEALTH(Object obj, float health)l
extern _native void SET_OBJECT_INITIAL_ROTATION_VELOCITY(Object obj, float x, float y, float z)l
extern _native void SET_OBJECT_INITIAL_VELOCITY(Object obj, float x, float y, float z)l
extern _native void SET_OBJECT_INVINCIBLE(Object obj, bool set)l
extern _native void SET_OBJECT_LIGHTS(Object obj, bool lights)l
extern _native void SET_OBJECT_ONLY_DAMAGED_BY_PLAYER(Object obj, bool set)l
extern _native void SET_OBJECT_PHYSICS_PARAMS(Object obj, float Unk96, float Unk97, float v0x, float v0y, float v0z, float v1x, float v1y, float v1z, uint flag0, uint flag1)l
extern _native void SET_OBJECT_PROOFS(Object obj, bool unknown0, bool fallingDamage, bool unknown1, bool unknown2, bool unknown3)l
extern _native void SET_OBJECT_QUATERNION(Object obj, float qx, float qy, float qz, float qw)l
extern _native void SET_OBJECT_RECORDS_COLLISIONS(Object obj, bool set)l
extern _native void SET_OBJECT_RENDER_SCORCHED(Object obj, bool set)l
extern _native void SET_OBJECT_ROTATION(Object obj, float Pitch, float Roll, float Yaw)l
extern _native void SET_OBJECT_SCALE(Object obj, float scale)l
extern _native void SET_OBJECT_USED_IN_POOL_GAME(Object obj, bool set)l
extern _native void SET_OBJECT_VISIBLE(Object obj, bool value)l
extern _native void SET_USES_COLLISION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, uint type_or_model, bool flag)l
extern _native void SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, uint type_or_model, bool set)l
extern _native void SWAP_NEAREST_BUILDING_MODEL(float x, float y, float z, float radius, uint modelfrom, uint modelto)l
extern _native void WINCH_CAN_PICK_OBJECT_UP(Object obj, bool can)l
#pragma endregion//}
#pragma region ENTITY//{
extern _native bool LOOK_AT_NEARBY_ENTITY_WITH_SPECIAL_ATTRIBUTE(int Unk98, vector3 * Unk99, float * Unk100, ScriptAny * Unk101, ScriptAny * Unk102, ScriptAny * Unk103)l
extern _native void FIND_NEAREST_ENTITIES_WITH_SPECIAL_ATTRIBUTE(float x, float y, float z)l
extern _native void SET_VISIBILITY_OF_NEARBY_ENTITY_WITH_SPECIAL_ATTRIBUTE(int attribute, bool set)l
#pragma endregion//}
#pragma region AI//{
extern _native bool DOES_SCENARIO_EXIST_IN_AREA(ScriptAny Unk104, ScriptAny Unk105, ScriptAny Unk106, ScriptAny Unk107, ScriptAny Unk108)l
extern _native bool IS_PAIN_PLAYING(Ped ped)l
extern _native bool TASK_SHIMMY_CLIMB_UP(Ped ped)l
extern _native bool TASK_SHIMMY_IN_DIRECTION(Ped ped, ScriptAny Unk109)l
extern _native bool TASK_SHIMMY_LET_GO(Ped ped)l
extern _native void ADD_COVER_BLOCKING_AREA(ScriptAny Unk110, ScriptAny Unk111, ScriptAny Unk112, ScriptAny Unk113, ScriptAny Unk114, ScriptAny Unk115, ScriptAny Unk116, ScriptAny Unk117, ScriptAny Unk118)l
extern _native void ADD_COVER_POINT(ScriptAny Unk119, ScriptAny Unk120, ScriptAny Unk121, ScriptAny Unk122, ScriptAny Unk123, ScriptAny Unk124, ScriptAny Unk125, ScriptAny Unk126)l
extern _native void ADD_FOLLOW_NAVMESH_TO_PHONE_TASK(Ped ped, ScriptAny Unk127, ScriptAny Unk128, ScriptAny Unk129)l
extern _native void ADD_NEEDED_AT_POSN(float x, float y, float z)l
extern _native void ADD_POINT_TO_GPS_RACE_TRACK(vector3 *point)l
extern _native void ADD_SCENARIO_BLOCKING_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void BLOCK_COWERING_IN_COVER(Ped ped, bool set)l
extern _native void BLOCK_PEEKING_IN_COVER(Ped ped, bool set)l
extern _native void CLEAR_SEQUENCE_TASK(TaskSequence taskSequence)l
extern _native void CLOSE_SEQUENCE_TASK(TaskSequence taskSequence)l
extern _native void FIRE_PED_WEAPON(Ped ped, float x, float y, float z)l
extern _native void HIGH_FALL_SCREAM(Ped ped)l
extern _native void ON_FIRE_SCREAM(Ped ped)l
extern _native void OPEN_SEQUENCE_TASK(TaskSequence *pTaskSequence)l
extern _native void PANIC_SCREAM(Ped ped)l
extern _native void REMOVE_COVER_POINT(CoverPoint coverPoint)l
extern _native void SET_DEFAULT_TARGET_SCORING_FUNCTION(Ped ped, ScriptAny Unk132)l
extern _native void SET_DRIVE_TASK_CRUISE_SPEED(Ped ped, float speed)l
extern _native void TAKE_CAR_OUT_OF_PARKED_CARS_BUDGET(Vehicle car, bool out)l
extern _native void TASK_ACHIEVE_HEADING(Ped ped, float heading)l
extern _native void TASK_AIM_GUN_AT_CHAR(Ped ped, Ped targetPed, uint duration)l
extern _native void TASK_AIM_GUN_AT_COORD(Ped ped, float tX, float tY, float tZ, uint duration)l
extern _native void TASK_CAR_DRIVE_TO_COORD(Ped ped, Vehicle veh, float Unk133, float Unk134, float Unk135, float Unk136, int Unk137, int Unk138, int Unk139, float Unk140, int Unk141)l
extern _native void TASK_CAR_DRIVE_TO_COORD_NOT_AGAINST_TRAFFIC(Ped ped, ScriptAny Unk142, ScriptAny Unk143, ScriptAny Unk144, ScriptAny Unk145, ScriptAny Unk146, ScriptAny Unk147, ScriptAny Unk148, ScriptAny Unk149, ScriptAny Unk150, ScriptAny Unk151)l
extern _native void TASK_CAR_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, uint drivingStyle)l
extern _native void TASK_CAR_MISSION(Ped ped, Vehicle vehicle, uint targetEntity, uint missionType, float speed, uint drivingStyle, uint unknown6_10, uint unknown7_5)l
extern _native void TASK_CAR_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, float x, float y, float z, uint unknown0_4, float speed, uint unknown2_1, uint unknown3_5, uint unknown4_10)l
extern _native void TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(Ped ped, Vehicle vehicle, float x, float y, float z, uint unknown0_4, float speed, uint unknown2_1, uint unknown3_5, uint unknown4_10)l
extern _native void TASK_CAR_MISSION_NOT_AGAINST_TRAFFIC(Ped ped, Vehicle vehicle, uint targetEntity, uint missionType, float speed, uint drivingStyle, uint unknown6_10, uint unknown7_5)l
extern _native void TASK_CAR_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped target, uint unknown0_4, float speed, uint unknown2_1, uint unknown3_5, uint unknown4_10)l
extern _native void TASK_CAR_MISSION_PED_TARGET_NOT_AGAINST_TRAFFIC(Ped ped, ScriptAny Unk152, ScriptAny Unk153, ScriptAny Unk154, ScriptAny Unk155, ScriptAny Unk156, ScriptAny Unk157, ScriptAny Unk158)l
extern _native void TASK_CAR_TEMP_ACTION(Ped ped, Vehicle vehicle, uint action, uint duration)l
extern _native void TASK_CHAR_ARREST_CHAR(Ped ped0, Ped ped1)l
extern _native void TASK_CHAR_SLIDE_TO_COORD(Ped ped, ScriptAny Unk159, ScriptAny Unk160, ScriptAny Unk161, ScriptAny Unk162, ScriptAny Unk163)l
extern _native void TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM(Ped ped, ScriptAny Unk164, ScriptAny Unk165, ScriptAny Unk166, ScriptAny Unk167, ScriptAny Unk168, ScriptAny Unk169, ScriptAny Unk170, ScriptAny Unk171, ScriptAny Unk172, ScriptAny Unk173, ScriptAny Unk174, ScriptAny Unk175, ScriptAny Unk176)l
extern _native void TASK_CHAR_SLIDE_TO_COORD_HDG_RATE(Ped ped, ScriptAny Unk177, ScriptAny Unk178, ScriptAny Unk179, ScriptAny Unk180, ScriptAny Unk181, ScriptAny Unk182)l
extern _native void TASK_CHAT_WITH_CHAR(Ped ped, Ped pednext, bool Unk183, bool Unk184)l
extern _native void TASK_CLEAR_LOOK_AT(Ped ped)l
extern _native void TASK_CLIMB(Ped ped, bool Unk185)l
extern _native void TASK_CLIMB_LADDER(Ped ped, ScriptAny Unk186)l
extern _native void TASK_COMBAT(Ped ped, Ped target)l
extern _native void TASK_COMBAT_HATED_TARGETS_AROUND_CHAR(Ped ped, float radius)l
extern _native void TASK_COMBAT_HATED_TARGETS_AROUND_CHAR_TIMED(Ped ped, float radius, uint duration)l
extern _native void TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, ScriptAny Unk187, ScriptAny Unk188, ScriptAny Unk189, ScriptAny Unk190)l
extern _native void TASK_COMBAT_ROLL(Ped ped, ScriptAny Unk191)l
extern _native void TASK_COMBAT_TIMED(Ped ped, Ped target, uint duration)l
extern _native void TASK_COWER(Ped ped)l
extern _native void TASK_DEAD(Ped ped)l
extern _native void TASK_DESTROY_CAR(Ped ped, Vehicle car)l
extern _native void TASK_DIE(Ped ped)l
extern _native void TASK_DRIVE_BY(Ped ped, Ped pednext, int Unk192, float x, float y, float z, float angle, int Unk193, bool Unk194, int Unk195)l
extern _native void TASK_DRIVE_POINT_ROUTE(Ped ped, int point, float radius)l
extern _native void TASK_DRIVE_POINT_ROUTE_ADVANCED(Ped ped, ScriptAny Unk197, ScriptAny Unk198, ScriptAny Unk199, ScriptAny Unk200, ScriptAny Unk201)l
extern _native void TASK_DUCK(Ped ped, ScriptAny Unk202)l
extern _native void TASK_ENTER_CAR_AS_DRIVER(Ped ped, Vehicle vehicle, uint duration)l
extern _native void TASK_ENTER_CAR_AS_PASSENGER(Ped ped, Vehicle vehicle, uint duration, uint seatIndex)l
extern _native void TASK_EVERYONE_LEAVE_CAR(Vehicle vehicle)l
extern _native void TASK_EXTEND_ROUTE(Ped ped, ScriptAny Unk203, ScriptAny Unk204)l
extern _native void TASK_FALL_AND_GET_UP(Ped ped, ScriptAny Unk205, ScriptAny Unk206)l
extern _native void TASK_FLEE_CHAR_ANY_MEANS(Ped ped, ScriptAny Unk207, ScriptAny Unk208, ScriptAny Unk209, ScriptAny Unk210, ScriptAny Unk211, ScriptAny Unk212, ScriptAny Unk213)l
extern _native void TASK_FLUSH_ROUTE(void)l
extern _native void TASK_FOLLOW_FOOTSTEPS(Ped ped, ScriptAny Unk214)l
extern _native void TASK_FOLLOW_NAV_MESH_AND_SLIDE_TO_COORD(Ped ped, float x, float y, float z, int Unk215, int Unk216, float Unk217, float angle)l
extern _native void TASK_FOLLOW_NAV_MESH_AND_SLIDE_TO_COORD_HDG_RATE(Ped ped, float x, float y, float z, int Unk218, int Unk219, float Unk220, float angle, float rate)l
extern _native void TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, float x, float y, float z, uint unknown0_2, uint unknown1_minus1, float unknown2_1)l
extern _native void TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(Ped ped, float x, float y, float z, uint unknown0_2, uint unknown1_minus1, float unknown2_1)l
extern _native void TASK_GET_OFF_BOAT(Ped ped, int timeout)l
extern _native void TASK_GOTO_CAR(Ped ped, ScriptAny Unk221, ScriptAny Unk222, ScriptAny Unk223)l
extern _native void TASK_GOTO_CHAR_AIMING(Ped ped, ScriptAny Unk224, ScriptAny Unk225, ScriptAny Unk226)l
extern _native void TASK_GOTO_CHAR_OFFSET(Ped ped, Ped target, uint duration, float offsetRight, float offsetFront)l
extern _native void TASK_GO_STRAIGHT_TO_COORD(Ped ped, float x, float y, float z, uint unknown2, uint unknown45000)l
extern _native void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_CAR(Ped ped, ScriptAny Unk227, ScriptAny Unk228, ScriptAny Unk229, ScriptAny Unk230, ScriptAny Unk231, ScriptAny Unk232)l
extern _native void TASK_GO_TO_CHAR(Ped ped, ScriptAny Unk233, ScriptAny Unk234, ScriptAny Unk235)l
extern _native void TASK_GO_TO_COORD_ANY_MEANS(Ped ped, ScriptAny Unk236, ScriptAny Unk237, ScriptAny Unk238, ScriptAny Unk239, ScriptAny Unk240)l
extern _native void TASK_GO_TO_COORD_WHILE_AIMING(Ped ped, ScriptAny Unk241, ScriptAny Unk242, ScriptAny Unk243, ScriptAny Unk244, ScriptAny Unk245, ScriptAny Unk246, ScriptAny Unk247, ScriptAny Unk248, ScriptAny Unk249, ScriptAny Unk250, ScriptAny Unk251)l
extern _native void TASK_GO_TO_COORD_WHILE_SHOOTING(Ped ped, ScriptAny Unk252, ScriptAny Unk253, ScriptAny Unk254, ScriptAny Unk255, ScriptAny Unk256, ScriptAny Unk257, ScriptAny Unk258, ScriptAny Unk259)l
extern _native void TASK_GO_TO_OBJECT(Ped ped, ScriptAny Unk260, ScriptAny Unk261, ScriptAny Unk262)l
extern _native void TASK_GUARD_ANGLED_DEFENSIVE_AREA(Ped ped, ScriptAny Unk263, ScriptAny Unk264, ScriptAny Unk265, ScriptAny Unk266, ScriptAny Unk267, ScriptAny Unk268, ScriptAny Unk269, ScriptAny Unk270, ScriptAny Unk271, ScriptAny Unk272, ScriptAny Unk273, ScriptAny Unk274, ScriptAny Unk275)l
extern _native void TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(Ped ped, ScriptAny Unk276, ScriptAny Unk277, ScriptAny Unk278, ScriptAny Unk279, ScriptAny Unk280, ScriptAny Unk281)l
extern _native void TASK_GUARD_CURRENT_POSITION(Ped ped, float unknown0_15, float unknown1_10, uint unknown2_1)l
extern _native void TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped ped, ScriptAny Unk282, ScriptAny Unk283, ScriptAny Unk284, ScriptAny Unk285, ScriptAny Unk286, ScriptAny Unk287, ScriptAny Unk288, ScriptAny Unk289, ScriptAny Unk290, ScriptAny Unk291)l
extern _native void TASK_HANDS_UP(Ped ped, uint duration)l
extern _native void TASK_HELI_MISSION(Ped ped, Vehicle heli, uint uk0_0, uint uk1_0, float pX, float pY, float pZ, uint uk2_4, float speed, uint uk3_5, float uk4_minus1, uint uk5_round_z_plus_1, uint uk6_40)l
extern _native void TASK_JUMP(Ped ped, bool flag)l
extern _native void TASK_LEAVE_ANY_CAR(Ped ped)l
extern _native void TASK_LEAVE_CAR(Ped ped, Vehicle vehicle)l
extern _native void TASK_LEAVE_CAR_AND_FLEE(Ped ped, ScriptAny Unk292, ScriptAny Unk293, ScriptAny Unk294, ScriptAny Unk295)l
extern _native void TASK_LEAVE_CAR_DONT_CLOSE_DOOR(Ped ped, Vehicle vehicle)l
extern _native void TASK_LEAVE_CAR_IMMEDIATELY(Ped ped, Vehicle vehicle)l
extern _native void TASK_LEAVE_CAR_IN_DIRECTION(Ped ped, Vehicle car, bool direction)l
extern _native void TASK_LEAVE_GROUP(Ped ped)l
extern _native void TASK_LOOK_AT_CHAR(Ped ped, Ped targetPed, uint duration, uint unknown_0)l
extern _native void TASK_LOOK_AT_COORD(Ped ped, float x, float y, float z, uint duration, uint unknown_0)l
extern _native void TASK_LOOK_AT_OBJECT(Ped ped, Object targetObject, uint duration, uint unknown_0)l
extern _native void TASK_LOOK_AT_VEHICLE(Ped ped, Vehicle targetVehicle, uint duration, uint unknown_0)l
extern _native void TASK_MOBILE_CONVERSATION(Ped ped, ScriptAny Unk296)l
extern _native void TASK_OPEN_DRIVER_DOOR(Ped ped, Vehicle vehicle, uint unknown0)l
extern _native void TASK_OPEN_PASSENGER_DOOR(Ped ped, Vehicle vehicle, uint seatIndex, uint unknown0)l
extern _native void TASK_PAUSE(Ped ped, uint duration)l
extern _native void TASK_PERFORM_SEQUENCE(Ped ped, TaskSequence taskSequence)l
extern _native void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(Ped ped, ScriptAny Unk297, ScriptAny Unk298, ScriptAny Unk299)l
extern _native void TASK_PERFORM_SEQUENCE_LOCALLY(Ped ped, ScriptAny Unk300)l
extern _native void TASK_PICKUP_AND_CARRY_OBJECT(Ped ped, ScriptAny Unk301, ScriptAny Unk302, ScriptAny Unk303, ScriptAny Unk304, ScriptAny Unk305)l
extern _native void TASK_PLAY_ANIM(Ped ped, ScriptAny Unk306, ScriptAny Unk307, ScriptAny Unk308, ScriptAny Unk309, ScriptAny Unk310, ScriptAny Unk311, ScriptAny Unk312, ScriptAny Unk313)l
extern _native void TASK_PLAY_ANIM_FACIAL(Ped ped, ScriptAny Unk314, ScriptAny Unk315, ScriptAny Unk316, ScriptAny Unk317, ScriptAny Unk318, ScriptAny Unk319)l
extern _native void TASK_PLAY_ANIM_NON_INTERRUPTABLE(Ped ped, const char* animname0, const char* animname1, float Unk320, int Unk321, int Unk322, int Unk323, int Unk324, int Unk325)l
extern _native void TASK_PLAY_ANIM_ON_CLONE(Ped ped, ScriptAny Unk326, ScriptAny Unk327, ScriptAny Unk328, ScriptAny Unk329, ScriptAny Unk330, ScriptAny Unk331, ScriptAny Unk332, ScriptAny Unk333)l
extern _native void TASK_PLAY_ANIM_READY_TO_BE_EXECUTED(Ped ped, ScriptAny Unk334, ScriptAny Unk335, ScriptAny Unk336)l
extern _native void TASK_PLAY_ANIM_SECONDARY(Ped ped, ScriptAny Unk337, ScriptAny Unk338, ScriptAny Unk339, ScriptAny Unk340, ScriptAny Unk341, ScriptAny Unk342, ScriptAny Unk343, ScriptAny Unk344)l
extern _native void TASK_PLAY_ANIM_SECONDARY_IN_CAR(Ped ped, ScriptAny Unk345, ScriptAny Unk346, ScriptAny Unk347, ScriptAny Unk348, ScriptAny Unk349, ScriptAny Unk350, ScriptAny Unk351, ScriptAny Unk352)l
extern _native void TASK_PLAY_ANIM_SECONDARY_NO_INTERRUPT(Ped ped, ScriptAny Unk353, ScriptAny Unk354, ScriptAny Unk355, ScriptAny Unk356, ScriptAny Unk357, ScriptAny Unk358, ScriptAny Unk359, ScriptAny Unk360)l
extern _native void TASK_PLAY_ANIM_SECONDARY_UPPER_BODY(Ped ped, ScriptAny Unk361, ScriptAny Unk362, ScriptAny Unk363, ScriptAny Unk364, ScriptAny Unk365, ScriptAny Unk366, ScriptAny Unk367, ScriptAny Unk368)l
extern _native void TASK_PLAY_ANIM_UPPER_BODY(Ped ped, ScriptAny Unk369, ScriptAny Unk370, ScriptAny Unk371, ScriptAny Unk372, ScriptAny Unk373, ScriptAny Unk374, ScriptAny Unk375, ScriptAny Unk376)l
extern _native void TASK_PLAY_ANIM_WITH_ADVANCED_FLAGS(Ped ped, ScriptAny Unk377, ScriptAny Unk378, ScriptAny Unk379, ScriptAny Unk380, ScriptAny Unk381, ScriptAny Unk382, ScriptAny Unk383, ScriptAny Unk384, ScriptAny Unk385, ScriptAny Unk386, ScriptAny Unk387)l
extern _native void TASK_PLAY_ANIM_WITH_FLAGS(Ped ped, const char* animName, const char* animSet, float unknown0_8, uint unknown1_0, uint flags)l
extern _native void TASK_PLAY_ANIM_WITH_FLAGS_AND_START_PHASE(Ped ped, ScriptAny Unk388, ScriptAny Unk389, ScriptAny Unk390, ScriptAny Unk391, ScriptAny Unk392, ScriptAny Unk393)l
extern _native void TASK_PUT_CHAR_DIRECTLY_INTO_COVER(ScriptAny Unk394, ScriptAny Unk395, ScriptAny Unk396, ScriptAny Unk397, ScriptAny Unk398)l
extern _native void TASK_SEEK_COVER_FROM_PED(Ped ped, ScriptAny Unk399, ScriptAny Unk400)l
extern _native void TASK_SEEK_COVER_FROM_POS(Ped ped, ScriptAny Unk401, ScriptAny Unk402, ScriptAny Unk403, ScriptAny Unk404)l
extern _native void TASK_SEEK_COVER_TO_COORDS(Ped ped, ScriptAny Unk405, ScriptAny Unk406, ScriptAny Unk407, ScriptAny Unk408, ScriptAny Unk409, ScriptAny Unk410, ScriptAny Unk411)l
extern _native void TASK_SEEK_COVER_TO_COVER_POINT(Ped ped, ScriptAny Unk412, ScriptAny Unk413, ScriptAny Unk414, ScriptAny Unk415, ScriptAny Unk416)l
extern _native void TASK_SEEK_COVER_TO_OBJECT(Ped ped, ScriptAny Unk417, ScriptAny Unk418, ScriptAny Unk419, ScriptAny Unk420, ScriptAny Unk421)l
extern _native void TASK_SET_IGNORE_WEAPON_RANGE_FLAG(Ped ped, bool ignore)l
extern _native void TASK_SHAKE_FIST(Ped ped)l
extern _native void TASK_SHIMMY(Ped ped, ScriptAny Unk422)l
extern _native void TASK_SHOOT_AT_CHAR(Ped shooter, Ped victim, int time, eShootMode shootmode)l
extern _native void TASK_SHOOT_AT_COORD(Ped ped, ScriptAny Unk423, ScriptAny Unk424, ScriptAny Unk425, ScriptAny Unk426, ScriptAny Unk427)l
extern _native void TASK_SHUFFLE_TO_NEXT_CAR_SEAT(Ped ped, ScriptAny Unk428)l
extern _native void TASK_SIT_DOWN(Ped ped, ScriptAny Unk429, ScriptAny Unk430, ScriptAny Unk431)l
extern _native void TASK_SIT_DOWN_INSTANTLY(Ped ped, ScriptAny Unk432, ScriptAny Unk433, ScriptAny Unk434)l
extern _native void TASK_SIT_DOWN_ON_NEAREST_OBJECT(Ped ped, ScriptAny Unk435, ScriptAny Unk436, ScriptAny Unk437, ScriptAny Unk438, ScriptAny Unk439, ScriptAny Unk440, ScriptAny Unk441, ScriptAny Unk442, ScriptAny Unk443)l
extern _native void TASK_SIT_DOWN_ON_OBJECT(Ped ped, ScriptAny Unk444, ScriptAny Unk445, ScriptAny Unk446, ScriptAny Unk447, ScriptAny Unk448, ScriptAny Unk449, ScriptAny Unk450, ScriptAny Unk451, ScriptAny Unk452)l
extern _native void TASK_SIT_DOWN_ON_SEAT(Ped ped, ScriptAny Unk453, ScriptAny Unk454, ScriptAny Unk455, ScriptAny Unk456, ScriptAny Unk457, ScriptAny Unk458, ScriptAny Unk459)l
extern _native void TASK_SMART_FLEE_CHAR(Ped ped, Ped fleeFromPed, float unknown0_100, uint duration)l
extern _native void TASK_SMART_FLEE_CHAR_PREFERRING_PAVEMENTS(Ped ped, Ped fleeFromPed, float unknown0_100, uint duration)l
extern _native void TASK_SMART_FLEE_POINT(Ped ped, float x, float y, float z, float unknown0_100, uint duration)l
extern _native void TASK_SMART_FLEE_POINT_PREFERRING_PAVEMENTS(Ped ped, float x, float y, float z, float radius, int time_prob)l
extern _native void TASK_STAND_GUARD(Ped ped, float x, float y, float z, float Unk460, float Unk461, bool Unk462, int Unk463)l
extern _native void TASK_STAND_STILL(Ped ped, int duration)l
extern _native void TASK_START_SCENARIO_AT_POSITION(Ped ped, ScriptAny Unk464, ScriptAny Unk465, ScriptAny Unk466, ScriptAny Unk467, ScriptAny Unk468)l
extern _native void TASK_START_SCENARIO_IN_PLACE(Ped ped, ScriptAny Unk469, ScriptAny Unk470)l
extern _native void TASK_SWAP_WEAPON(Ped ped, uint weapon)l
extern _native void TASK_SWIM_TO_COORD(Ped ped, float x, float y, float z)l
extern _native void TASK_TIRED(Ped ped, int Unk471)l
extern _native void TASK_TOGGLE_DUCK(Ped ped, int Unk472)l
extern _native void TASK_TOGGLE_PED_THREAT_SCANNER(Ped ped, bool Unk473, bool Unk474, bool Unk475)l
extern _native void TASK_TURN_CHAR_TO_FACE_CHAR(Ped ped, Ped targetPed)l
extern _native void TASK_TURN_CHAR_TO_FACE_COORD(Ped ped, float x, float y, float z)l
extern _native void TASK_USE_MOBILE_PHONE(Ped ped, bool use)l
extern _native void TASK_USE_MOBILE_PHONE_TIMED(Ped ped, uint duration)l
extern _native void TASK_USE_NEAREST_SCENARIO_TO_POS(Ped ped, ScriptAny Unk476, ScriptAny Unk477, ScriptAny Unk478, ScriptAny Unk479)l
extern _native void TASK_USE_NEAREST_SCENARIO_TO_POS_WARP(Ped ped, ScriptAny Unk480, ScriptAny Unk481, ScriptAny Unk482, ScriptAny Unk483)l
extern _native void TASK_WANDER_STANDARD(Ped ped)l
extern _native void TASK_WARP_CHAR_INTO_CAR_AS_DRIVER(Ped ped, Vehicle vehicle)l
extern _native void TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER(Ped ped, Vehicle vehicle, uint seatIndex)l
#pragma endregion//}
#pragma region POLICE//{
extern _native bool GET_CREATE_RANDOM_COPS(void)l
extern _native bool IS_CHAR_IN_ANY_POLICE_VEHICLE(Ped ped)l
extern _native bool IS_COP_PED_IN_AREA_3D_NO_SAVE(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native bool IS_COP_VEHICLE_IN_AREA_3D_NO_SAVE(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native bool IS_WANTED_LEVEL_GREATER(Player playerIndex, uint level)l
extern _native bool WANTED_STARS_ARE_FLASHING(void)l
extern _native void ADD_HOSPITAL_RESTART(float x, float y, float z, float radius, int islandnum)l
extern _native void ADD_POLICE_RESTART(float x, float y, float z, float radius, int islandnum)l
extern _native void ALTER_WANTED_LEVEL(Player playerIndex, uint level)l
extern _native void ALTER_WANTED_LEVEL_NO_DROP(Player playerIndex, uint level)l
extern _native void APPLY_WANTED_LEVEL_CHANGE_NOW(Player playerIndex)l
extern _native void CLEAR_AREA_OF_COPS(float x, float y, float z, float radius)l
extern _native void CLEAR_WANTED_LEVEL(Player playerIndex)l
extern _native void DISABLE_POLICE_SCANNER(void)l
extern _native void DONT_DISPATCH_COPS_FOR_PLAYER(int player, bool dont)l
extern _native void ENABLE_POLICE_SCANNER(void)l
extern _native void EXTEND_PATROL_ROUTE(ScriptAny Unk484, ScriptAny Unk485, ScriptAny Unk486, ScriptAny Unk487, ScriptAny Unk488)l
extern _native void FLUSH_PATROL_ROUTE(void)l
extern _native void GET_CURRENT_BASIC_COP_MODEL(uint *pModel)l
extern _native void GET_CURRENT_BASIC_POLICE_CAR_MODEL(uint *pModel)l
extern _native void GET_CURRENT_COP_MODEL(uint *pModel)l
extern _native void GET_CURRENT_POLICE_CAR_MODEL(uint *pModel)l
extern _native void GET_MAX_WANTED_LEVEL(uint *pMaxWantedLevel)l
extern _native void GET_PLAYER_WANTED_LEVEL_INCREMENT(int player, int *increment)l
extern _native void MAINTAIN_FLASHING_STAR_AFTER_OFFENCE(int player, bool maintain)l
extern _native void REPORT_CRIME(float x, float y, float z, const char* name)l
extern _native void REPORT_DISPATCH(int id, float x, float y, float z)l
extern _native void REPORT_POLICE_SPOTTING_SUSPECT(Vehicle veh)l
extern _native void REPORT_SUSPECT_ARRESTED(void)l
extern _native void REPORT_SUSPECT_DOWN(void)l
extern _native void SET_CHAR_WANTED_BY_POLICE(Ped ped, bool wanted)l
extern _native void SET_CREATE_RANDOM_COPS(bool set)l
extern _native void SET_DITCH_POLICE_MODELS(bool set)l
extern _native void SET_EXTRA_HOSPITAL_RESTART_POINT(float x, float y, float z, float Unk489, float Unk490)l
extern _native void SET_EXTRA_POLICE_STATION_RESTART_POINT(float x, float y, float z, float Unk491, float Unk492)l
extern _native void SET_FAKE_WANTED_CIRCLE(float x, float y, float radius)l
extern _native void SET_FAKE_WANTED_LEVEL(int lvl)l
extern _native void SET_MAX_WANTED_LEVEL(uint lvl)l
extern _native void SET_PED_WONT_ATTACK_PLAYER_WITHOUT_WANTED_LEVEL(Ped ped, bool set)l
extern _native void SET_PLAYER_AS_COP(int player, bool set)l
extern _native void SET_POLICE_FOCUS_WILL_TRACK_CAR(Vehicle car, bool set)l
extern _native void SET_POLICE_IGNORE_PLAYER(Player playerIndex, bool value)l
extern _native void SET_POLICE_RADAR_BLIPS(bool set)l
extern _native void SET_WANTED_MULTIPLIER(float multiplier)l
extern _native void SET_ZONE_NO_COPS(const char* name, bool set)l
extern _native void SPECIFY_SCRIPT_POPULATION_ZONE_PERCENTAGE_COPS(int percentage)l
extern _native void STORE_WANTED_LEVEL(Player playerIndex, uint* value)l
extern _native void SWITCH_POLICE_HELIS(bool set)l
extern _native void TRIGGER_POLICE_REPORT(const char* name)l
extern _native void TRIGGER_VIGILANTE_CRIME(int id, float x, float y, float z)l
#pragma endregion//}
#pragma region GAMEPLAY//{
//extern _native bool IS_PC_VERSION(void)l
//extern _native bool IS_XBOX360_VERSION(void)l
extern _native bool ARE_ALL_NAVMESH_REGIONS_LOADED(void)l
extern _native bool ARE_CREDITS_FINISHED(void)l
extern _native bool CAN_CREATE_RANDOM_CHAR(bool flag0, bool flag1)l
extern _native bool CAN_FONT_BE_LOADED(int fontid)l
extern _native bool CAN_START_MISSION_PASSED_TUNE(void)l
extern _native bool CHEAT_HAPPENED_RECENTLY(int cheat, int time)l
extern _native bool DID_SAVE_COMPLETE_SUCCESSFULLY(void)l
extern _native bool DOES_THIS_MINIGAME_SCRIPT_ALLOW_NON_MINIGAME_HELP_MESSAGES(void)l
extern _native bool GET_GFWL_HAS_SAFE_HOUSE(void)l
extern _native bool GET_IS_AUTOSAVE_OFF(void)l
extern _native bool GET_IS_DEPOSIT_ANIM_RUNNING(void)l
extern _native bool GET_IS_DISPLAYINGSAVEMESSAGE(void)l
extern _native bool GET_IS_PROJECTILE_TYPE_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1, int type)l
extern _native bool GET_MISSION_FLAG(void)l
extern _native bool HAS_DEATHARREST_EXECUTED(void)l
extern _native bool IS_AREA_OCCUPIED(float x1, float y1, float z1, float x2, float y2, float z2, bool unknownFalse1, bool unknownTrue, bool unknownFalse2, bool unknownFalse3, bool unknownFalse4)l
//extern _native bool IS_AUSSIE_VERSION(void)l
extern _native bool IS_AUTO_AIMING_ON(void)l
extern _native bool IS_AUTO_SAVE_IN_PROGRESS(void)l
extern _native bool IS_BIT_SET(int val, int bitnum)l
extern _native bool IS_BULLET_IN_AREA(float x, float y, float z, float radius, bool unknownTrue)l
extern _native bool IS_BULLET_IN_BOX(float x1, float y1, float z1, float x2, float y2, float z2, bool unknown)l
extern _native bool IS_EPISODE_AVAILABLE(int episode)l
extern _native bool IS_EPISODIC_DISC_BUILD(void)l
extern _native bool IS_FONT_LOADED(uint font)l
extern _native bool IS_FRONTEND_FADING(void)l
extern _native bool IS_GAME_IN_CONTROL_OF_MUSIC(void)l
//extern _native bool IS_GERMAN_VERSION(void)l
extern _native bool IS_HELP_MESSAGE_BEING_DISPLAYED(void)l
extern _native bool IS_HINT_RUNNING(void)l
extern _native bool IS_HUD_PREFERENCE_SWITCHED_ON(void)l
extern _native bool IS_HUD_RETICULE_COMPLEX(void)l
extern _native bool IS_INTERIOR_SCENE(void)l
extern _native bool IS_IN_LAN_MODE(void)l
extern _native bool IS_IN_PLAYER_SETTINGS_MENU(void)l
extern _native bool IS_IN_SPECTATOR_MODE(void)l
extern _native bool IS_JAPANESE_VERSION(void)l
extern _native bool IS_LAZLOW_STATION_LOCKED(void)l
extern _native bool IS_LOOK_INVERTED(void)l
extern _native bool IS_MEMORY_CARD_IN_USE(void)l
extern _native bool IS_MESSAGE_BEING_DISPLAYED(void)l
extern _native bool IS_MINIGAME_IN_PROGRESS(void)l
extern _native bool IS_MISSION_COMPLETE_PLAYING(void)l
extern _native bool IS_PAUSE_MENU_ACTIVE(void)l
extern _native bool IS_PAY_N_SPRAY_ACTIVE(void)l
extern _native bool IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float pX, float pY, float pZ, float sizeX, float sizeY, float sizeZ)l
extern _native bool IS_POS_IN_CUTSCENE_BLOCKING_BOUNDS(float x, float y, float z)l
extern _native bool IS_PROJECTILE_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native bool IS_RADIO_HUD_ON(void)l
extern _native bool IS_RADIO_RETUNING(void)l
extern _native bool IS_RELATIONSHIP_SET(int Unk493, int Unk494, int Unk495)l
extern _native bool IS_REPLAY_SAVING(void)l
extern _native bool IS_REPLAY_SYSTEM_SAVING(void)l
extern _native bool IS_SCREEN_FADED_IN(void)l
extern _native bool IS_SCREEN_FADED_OUT(void)l
extern _native bool IS_SCREEN_FADING(void)l
extern _native bool IS_SCREEN_FADING_IN(void)l
extern _native bool IS_SCREEN_FADING_OUT(void)l
extern _native bool IS_SNIPER_INVERTED(void)l
extern _native bool IS_SYSTEM_UI_SHOWING(void)l
extern _native bool IS_THIS_A_MINIGAME_SCRIPT(void)l
extern _native bool SECUROM_SPOT_CHECK1(void)l
extern _native bool SECUROM_SPOT_CHECK2(void)l
extern _native bool SECUROM_SPOT_CHECK3(void)l
extern _native bool SECUROM_SPOT_CHECK4(void)l
extern _native bool SPOT_CHECK5(void)l
extern _native bool SPOT_CHECK6(void)l
extern _native bool SPOT_CHECK7(void)l
extern _native bool SPOT_CHECK8(void)l
extern _native bool STRING_TO_INT(const char* str, int *intval)l
extern _native const char* ASCII_INT_TO_STRING(int ascii)l
extern _native const char* GET_EPISODE_NAME(uint episodeIndex)l
extern _native const char* GET_RADIO_NAME(int id)l
extern _native const char* OBFUSCATE_STRING(const char* str)l
extern _native const char* UNOBFUSCATE_STRING(const char* str)l
extern _native float ABSF(float value)l
extern _native float ABSI(float value)l
extern _native float ACOS(float Unk496)l
extern _native float ASIN(float value)l
extern _native float ATAN(float value)l
extern _native float ATAN2(float Unk497, float Unk498)l
extern _native float GET_ASPECT_RATIO(void)l
extern _native float GET_PROGRESS_PERCENTAGE(void)l
extern _native int COMPARE_STRING(const char* str0, const char* str1)l
extern _native int COMPARE_TWO_DATES(int date0_0, int date0_1, int date1_0, int date1_1)l
extern _native int CONVERT_METRES_TO_FEET_INT(int metres)l
extern _native int FIND_STATIC_EMITTER_INDEX(const char* StaticEmitterName)l
extern _native int GET_BITS_IN_RANGE(int val, int rangebegin, int rangeend)l
extern _native int GET_CURRENT_STACK_SIZE(void)l
extern _native int GET_FILTER_SAVE_SETTING(int filterid)l
extern _native int GET_NAVMESH_ROUTE_RESULT(int navmesh)l
extern _native int GET_PROFILE_SETTING(int settingid)l
extern _native int GET_ROUTE_SIZE(void)l
extern _native int GET_SCREEN_FADE_ALPHA(void)l
extern _native int GET_STATIC_EMITTER_PLAYTIME(int StaticEmitterIndex)l
extern _native int GET_STREAM_PLAYTIME(void)l
extern _native int READ_KILL_FRENZY_STATUS(void)l
extern _native int STRING_DIFFERENCE(const char* str0, const char* str1)l//only works on 1.0.7
extern _native int STRING_STRING(const char* str0, const char* str1)l//only works on 1.0.7
extern _native ScriptAny AWARD_ACHIEVEMENT(uint achievement)l
extern _native ScriptAny GET_GROUND_Z_FOR_3D_COORD(float x, float y, float z, float *pGroundZ)l
extern _native ScriptAny IS_SNIPER_BULLET_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native uint GET_CURRENT_DAY_OF_WEEK(void)l
extern _native uint GET_CURRENT_EPISODE(void)l
extern _native uint GET_CURRENT_LANGUAGE(void)l
extern _native uint GET_EPISODE_INDEX_FROM_SUMMONS(void)l
extern _native uint GET_HASH_KEY(const char* value)l
extern _native uint GET_HOURS_OF_DAY(void)l
extern _native uint GET_MAP_AREA_FROM_COORDS(float x, float y, float z)l
extern _native uint GET_MINUTES_OF_DAY(void)l
extern _native uint GET_MINUTES_TO_TIME_OF_DAY(uint hour, uint minute)l
extern _native uint GET_NEXT_STATION_FOR_TRAIN(Train train)l
extern _native uint GET_NUM_STREAMING_REQUESTS(void)l
extern _native uint GET_TIME_SINCE_LAST_ARREST(void)l
extern _native uint GET_TIME_SINCE_LAST_DEATH(void)l
extern _native uint REGISTER_SAVE_HOUSE(float x, float y, float z, float unkf, const char* name, uint unk0)l
extern _native void ABORT_ALL_GARAGE_ACTIVITY(void)l
extern _native void ACTIVATE_CHEAT(uint cheat)l//0 - 15
extern _native void ALLOW_AUTO_CONVERSATION_LOOKATS(Ped ped, bool allow)l
extern _native void ALLOW_EMERGENCY_SERVICES(bool allow)l
extern _native void ALLOW_GAME_TO_PAUSE_FOR_STREAMING(bool allow)l
extern _native void ALLOW_GANG_RELATIONSHIPS_TO_BE_CHANGED_BY_NEXT_COMMAND(bool value)l
extern _native void ALLOW_MULTIPLE_DRIVEBY_PICKUPS(bool allow)l
extern _native void ALLOW_REACTION_ANIMS(Ped ped, bool allow)l
extern _native void ALLOW_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(bool value)l
extern _native void ALLOW_STUNT_JUMPS_TO_TRIGGER(bool allow)l
extern _native void CANCEL_OVERRIDE_RESTART(void)l
extern _native void CLEAR_ANGLED_AREA_OF_CARS(float x0, float y0, float z0, float x1, float y1, float z1, float radius)l
extern _native void CLEAR_AREA(float x, float y, float z, float radius, bool unknown)l
extern _native void CLEAR_AREA_OF_CARS(float x, float y, float z, float radius)l
extern _native void CLEAR_AREA_OF_CHARS(float x, float y, float z, float radius)l
extern _native void CLEAR_AREA_OF_OBJECTS(float x, float y, float z, float radius)l
extern _native void CLEAR_BIT(int *val, int bit)l
extern _native void CLEAR_PED_NON_CREATION_AREA(void)l
extern _native void CLEAR_PED_NON_REMOVAL_AREA(void)l
extern _native void CLEAR_SCRIPTED_CONVERSION_CENTRE(void)l
extern _native void DISABLE_PAUSE_MENU(bool disabled)l
extern _native void DONT_DISPLAY_LOADING_ON_FADE_THIS_FRAME(void)l
extern _native void DO_AUTO_SAVE(void)l
extern _native void ENABLE_FANCY_WATER(bool enable)l
extern _native void ENABLE_SAVE_HOUSE(uint savehouse, bool enable)l
extern _native void FAIL_KILL_FRENZY(void)l
extern _native void FIND_NEAREST_COLLECTABLE_BIN_BAGS(float x, float y, float z)l
extern _native void FIND_STREET_NAME_AT_POSITION(float pX, float pY, float pZ, uint *strHash0, uint *strHash1)l
extern _native void FIX_AMBIENCE_ORIENTATION(bool fix)l
extern _native void FIX_SCRIPT_MIC_TO_CURRENT_POSISITION(void)l
extern _native void FLUSH_ALL_OUT_OF_DATE_RADAR_BLIPS_FROM_MISSION_CLEANUP_LIST(void)l
extern _native void FLUSH_COVER_BLOCKING_AREAS(void)l
extern _native void FLUSH_SCENARIO_BLOCKING_AREAS(void)l
extern _native void FORCE_HIGH_LOD(bool force)l
extern _native void FORCE_LOADING_SCREEN(bool force)l
extern _native void FORCE_POPULATION_INIT(void)l
extern _native void FORCE_WEATHER(uint weather)l
extern _native void FORCE_WEATHER_NOW(uint weather)l
extern _native void FORCE_WIND(float wind)l
extern _native void GET_ANGLE_BETWEEN_2D_VECTORS(float x1, float y1, float x2, float y2, float *pResult)l
extern _native void GET_CURRENT_DATE(uint *day, uint *month)l
extern _native void GET_CURRENT_WEATHER(uint *pWeather)l
extern _native void GET_CURRENT_WEATHER_FULL(int *weatherparam0, int *weatherparam1, int *weatherparam2)l
extern _native void GET_DISTANCE_BETWEEN_COORDS_2D(float x1, float y1, float x2, float y2, float *pDist)l
extern _native void GET_DISTANCE_BETWEEN_COORDS_3D(float x1, float y1, float z1, float x2, float y2, float z2, float *pDist)l
extern _native void GET_FRONTEND_DESIGN_VALUE(int frontendid, float * Unk499, float * Unk500)l
extern _native void GET_HEADING_FROM_VECTOR_2D(float x, float y, float *pHeading)l
extern _native void GET_HUD_COLOUR(uint type, uint *pR, uint *pG, uint *pB, uint *pA)l
extern _native void GET_SEQUENCE_PROGRESS(int seq, int *progress)l
extern _native void GET_STREAM_BEAT_INFO(int * Unk501, int * Unk502, int * Unk503)l
extern _native void LIMIT_ANGLE(float angle, float *anglelimited)l
extern _native void LIMIT_TWO_PLAYER_DISTANCE(float distance)l
extern _native void LOCK_LAZLOW_STATION(void)l
extern _native void LOCK_PLAYER_SETTINGS_GENRE_CHANGE(int lock_bit_mask)l
extern _native void LOOP_RACE_TRACK(bool loop)l
extern _native void OVERRIDE_FREEZE_FLAGS(bool Unk504)l
extern _native void OVERRIDE_NEXT_RESTART(float x, float y, float z, float heading)l
extern _native void PICKUPS_PASS_TIME(uint time)l
extern _native void POPULATE_NOW(void)l
extern _native void PRIORITIZE_STREAMING_REQUEST(void)l
extern _native void PROCESS_MISSION_DELETION_LIST(void)l
extern _native void REGISTER_BEST_POSITION(int Unk505, int position)l
extern _native void REGISTER_MISSION_PASSED(const char* str)l
extern _native void REGISTER_ODDJOB_MISSION_PASSED(void)l
extern _native void REGISTER_TRACK_NUMBER(int number)l
extern _native void RELEASE_TEXTURE(Texture texture)l
extern _native void RELEASE_TIME_OF_DAY(void)l
extern _native void RELEASE_WEATHER(void)l
extern _native void REMOVE_SCRIPT_MIC(void)l
extern _native void RENDER_RACE_TRACK(bool render)l
extern _native void REPORT_TAGGED_RADIO_TRACK(int TrackTextId)l
extern _native void RESET_ACHIEVEMENTS_AWARD(void)l
extern _native void SAVE_SETTINGS(void)l
extern _native void SET_ALLOW_DUMMY_CONVERSIONS(bool set)l
extern _native void SET_BIT(int *val, int bit)l
extern _native void SET_BITS_IN_RANGE(int * Unk506, int rangebegin, int rangeend, int val)l
extern _native void SET_CLEAR_HELP_IN_MISSION_CLEANUP(bool set)l
extern _native void SET_CLEAR_MANIFOLDS(bool set)l
extern _native void SET_COLLECTABLE1_TOTAL(int total)l
extern _native void SET_CREDITS_TO_RENDER_BEFORE_FADE(bool set)l
extern _native void SET_DEFAULT_GLOBAL_INSTANCE_PRIORITY(void)l
extern _native void SET_FADE_IN_AFTER_LOAD(bool set)l
extern _native void SET_FILTER_SAVE_SETTING(int filterid, int setting)l
extern _native void SET_FOV_CHANNEL_SCRIPT(bool set)l
extern _native void SET_GLOBAL_INSTANCE_PRIORITY(int priority)l
extern _native void SET_GLOBAL_RENDER_FLAGS(bool Unk507, bool Unk508, bool Unk509, bool Unk510)l
extern _native void SET_GRAVITY_OFF(bool set)l
extern _native void SET_GFWL_HAS_SAFE_HOUSE(uint ukn)l
extern _native void SET_GUNSHOT_SENSE_RANGE_FOR_RIOT2(float range)l
extern _native void SET_MINIGAME_IN_PROGRESS(bool set)l
extern _native void SET_MISSION_FLAG(bool isMission)l
extern _native void SET_MISSION_PASSED_CASH(bool add, int cash, int Unk511)l
extern _native void SET_MISSION_PICKUP_SOUND(uint model, const char* SoundName)l
extern _native void SET_MISSION_RESPECT_TOTAL(float respect)l
extern _native void SET_NEXT_DESIRED_MOVE_STATE(int state)l
extern _native void SET_PHYS_CCD_HANDLES_ROTATION(bool set)l
extern _native void SET_RAILTRACK_RESISTANCE_MULT(float resistance)l
extern _native void SET_RANDOM_SEED(int seed)l
extern _native void SET_ROT_ORDER(int order)l
extern _native void SET_SCRIPTED_CONVERSION_CENTRE(float x, float y, float z)l
extern _native void SET_SEQUENCE_TO_REPEAT(int seq, int repeat)l
extern _native void SET_SLEEP_MODE_ACTIVE(bool set)l
extern _native void SET_SNIPER_ZOOM_FACTOR(float factor)l
extern _native void SET_TAXI_GARAGE_RADIO_STATE(bool radiostate)l
extern _native void SET_TOTAL_NUMBER_OF_MISSIONS(float floatstatval)l
extern _native void SET_USE_POOL_GAME_PHYSICS_SETTINGS(bool set)l
extern _native void START_CREDITS(void)l
extern _native void START_FIRING_AMNESTY(void)l
extern _native void START_GPS_RACE_TRACK(int trackid)l
extern _native void START_KILL_FRENZY(const char* gxtname, int Unk512, int Unk513, int Unk514, int Unk515, int Unk516, int Unk517, int Unk518, bool Unk519)l
extern _native void STOP_CREDITS(void)l
extern _native void SUPPRESS_FADE_IN_AFTER_DEATH_ARREST(bool set)l
extern _native void SWITCH_AMBIENT_PLANES(bool on)l
extern _native void SWITCH_GARBAGE_TRUCKS(bool on)l
extern _native void SWITCH_MAD_DRIVERS(bool on)l
extern _native void SWITCH_OFF_WAYPOINT(void)l
extern _native void SWITCH_RANDOM_BOATS(bool on)l
extern _native void SWITCH_RANDOM_TRAINS(bool on)l
extern _native void SWITCH_STREAMING(bool on)l
extern _native void SYNCH_AMBIENT_PLANES(int Unk520, int Unk521)l
extern _native void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(const char* name)l
extern _native void UNLOCK_GENERIC_NEWS_STORY(int StoryId)l
extern _native void UNLOCK_LAZLOW_STATION(void)l
extern _native void UNLOCK_MISSION_NEWS_STORY(int id)l
#pragma endregion//}
#pragma region AUDIO//{
extern _native bool HAS_SOUND_FINISHED(uint sound)l
extern _native bool IS_AMBIENT_SPEECH_DISABLED(Ped ped)l
extern _native bool IS_AMBIENT_SPEECH_PLAYING(Ped ped)l
extern _native bool IS_ANY_SPEECH_PLAYING(Ped ped)l
extern _native bool IS_SCRIPTED_CONVERSATION_ONGOING(void)l
extern _native bool IS_SCRIPTED_SPEECH_PLAYING(Ped ped)l
extern _native bool REQUEST_AMBIENT_AUDIO_BANK(const char* name)l
extern _native bool REQUEST_MISSION_AUDIO_BANK(const char* name)l
extern _native bool ENABLE_SCRIPT_CONTROLLED_MICROPHONE(void)l
extern _native const char* GET_SPEECH_FOR_EMERGENCY_SERVICE_CALL(void)l
extern _native int ABORT_SCRIPTED_CONVERSATION(bool abort)l
extern _native int GET_AUDIBLE_MUSIC_TRACK_TEXT_ID(void)l
extern _native int GET_AUDIO_ROOM_ID(void)l
extern _native int GET_CURRENT_SCRIPTED_CONVERSATION_LINE(void)l
extern _native uint GET_SOUND_ID(void)l
extern _native void ADD_LINE_TO_CONVERSATION(ScriptAny Unk522, ScriptAny Unk523, ScriptAny Unk524, ScriptAny Unk525, ScriptAny Unk526)l
extern _native void ADD_LINE_TO_SCRIPTED_CONVERSATION(uint conversation, int Unk527, int Unk528)l
extern _native void ADD_NEW_CONVERSATION_SPEAKER(int id, int Unk529, int * Unk530)l
extern _native void ADD_NEW_FRONTEND_CONVERSATION_SPEAKER(int Unk531, int Unk532)l
extern _native void AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED(void)l
extern _native void CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(Ped ped)l
extern _native void DISABLE_FRONTEND_RADIO(void)l
extern _native void DISABLE_GPS(bool disable)l
extern _native void DISABLE_STICKY_BOMB_ACTIVE_SOUND(Ped ped, bool disable)l
extern _native void DONT_ABORT_CAR_CONVERSATIONS(bool flag0, bool flag1)l
extern _native void ENABLE_CHASE_AUDIO(bool enable)l
extern _native void ENABLE_FRONTEND_RADIO(void)l
extern _native void FORCE_INITIAL_PLAYER_STATION(const char* stationName)l
extern _native void FORCE_NOISE_OFF(bool off)l
extern _native void FORCE_RADIO_TRACK(const char* radiostation, const char* trackname, int Unk533, int Unk534)l
extern _native void FREEZE_RADIO_STATION(const char* stationName)l
extern _native void GET_SOUND_LEVEL_AT_COORDS(Ped ped, float x, float y, float z, int *level)l
extern _native void HANDLE_AUDIO_ANIM_EVENT(Ped ped, const char* AudioAnimEventName)l
extern _native void HELI_AUDIO_SHOULD_SKIP_STARTUP(Vehicle heli, bool skip)l
extern _native void MISSION_AUDIO_BANK_NO_LONGER_NEEDED(void)l
extern _native void MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV(bool mute)l
extern _native void MUTE_GAMEWORLD_AUDIO(bool mute)l
extern _native void MUTE_POSITIONED_RADIO(bool mute)l
extern _native void MUTE_STATIC_EMITTER(int StaticEmitterIndex, bool mute)l
extern _native void NEW_SCRIPTED_CONVERSATION(void)l
extern _native void PAUSE_SCRIPTED_CONVERSATION(bool pause)l
extern _native void PLAY_AUDIO_EVENT(const char* name)l
extern _native void PLAY_AUDIO_EVENT_FROM_OBJECT(const char* EventName, Object obj)l
extern _native void PLAY_AUDIO_EVENT_FROM_PED(const char* name, Ped ped)l
extern _native void PLAY_AUDIO_EVENT_FROM_VEHICLE(const char* name, Vehicle veh)l
extern _native void PLAY_FIRE_SOUND_FROM_POSITION(int sound_id, float x, float y, float z)l
extern _native void PLAY_SCRIPTED_CONVERSATION_FRONTEND(bool play)l
extern _native void PLAY_SOUND(int SoundId, const char* SoundName)l
extern _native void PLAY_SOUND_FROM_OBJECT(int sound_id, const char* name, Object obj)l
extern _native void PLAY_SOUND_FROM_PED(int SoundId, const char* SoundName, Ped ped)l
extern _native void PLAY_SOUND_FROM_POSITION(int sound_id, const char* name, float x, float y, float z)l
extern _native void PLAY_SOUND_FROM_VEHICLE(int SoundId, const char* SoundName, Vehicle veh)l
extern _native void PLAY_SOUND_FRONTEND(uint sound, const char* soundName)l
extern _native void PLAY_STREAM_FROM_OBJECT(Object obj)l
extern _native void PLAY_STREAM_FROM_PED(Ped ped)l
extern _native void PLAY_STREAM_FRONTEND(void)l
extern _native void REGISTER_SCRIPT_WITH_AUDIO(bool reg)l
extern _native void RELEASE_SCRIPT_CONTROLLED_MICROPHONE(void)l
extern _native void RELEASE_SOUND_ID(uint sound)l
extern _native void RESTART_SCRIPTED_CONVERSATION(void)l
extern _native void RETUNE_RADIO_DOWN(void)l
extern _native void RETUNE_RADIO_TO_STATION_INDEX(uint radioStation)l
extern _native void RETUNE_RADIO_TO_STATION_NAME(const char* name)l
extern _native void RETUNE_RADIO_UP(void)l
extern _native void SAY_AMBIENT_SPEECH(Ped ped, const char* phraseName, bool flag0, bool flag1, int style)l
extern _native void SAY_AMBIENT_SPEECH_WITH_VOICE(Ped ped, const char* SpeechName, const char* VoiceName, bool flag0, bool flag1, int style)l
extern _native void SET_AMBIENT_VOICE_NAME(Ped ped, const char* name)l
extern _native void SET_GPS_VOICE_FOR_VEHICLE(Vehicle veh, int VoiceId)l
extern _native void SET_LOUD_VEHICLE_RADIO(Vehicle veh, bool set)l
extern _native void SET_MOVIE_VOLUME(float volume)l
extern _native void SET_SCRIPT_MIC_LOOK_AT(float x, float y, float z)l
extern _native void SET_SCRIPT_MIC_POSITION(float x, float y, float z)l
extern _native void SET_VARIABLE_ON_SOUND(uint sound, const char* varname, float value)l
extern _native void SET_VOICE_ID_FROM_HEAD_COMPONENT(Ped ped, int VoiceId, bool IsMale)l
extern _native void SKIP_RADIO_FORWARD(void)l
extern _native void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE(void)l
extern _native void START_END_CREDITS_MUSIC(void)l
extern _native void START_SCRIPT_CONVERSATION(bool flag0, bool flag1)l
extern _native void STOP_END_CREDITS_MUSIC(void)l
extern _native void STOP_SOUND(uint sound)l
extern _native void TRIGGER_LOADING_MUSIC_ON_NEXT_FADE(void)l
extern _native void TRIGGER_MISSION_COMPLETE_AUDIO(int id)l
extern _native void UNFREEZE_RADIO_STATION(const char* radiostation)l
extern _native void UNPAUSE_RADIO(void)l
extern _native void UNREGISTER_SCRIPT_WITH_AUDIO(void)l
#pragma endregion//}
#pragma region CUTSCENE//{
extern _native bool HAS_CUTSCENE_FINISHED(void)l
extern _native bool HAS_CUTSCENE_LOADED(void)l
extern _native bool WAS_CUTSCENE_SKIPPED(void)l
extern _native int GET_CUTSCENE_AUDIO_TIME_MS(void)l
extern _native int GET_CUTSCENE_SECTION_PLAYING(void)l
extern _native int GET_CUTSCENE_TIME(void)l
extern _native void CLEAR_CUTSCENE(void)l
extern _native void CLEAR_NAMED_CUTSCENE(const char* name)l
extern _native void INIT_CUTSCENE(const char* name)l
extern _native void SET_CUTSCENE_EXTRA_ROOM_POS(float x, float y, float z)l
extern _native void START_CUTSCENE(void)l
extern _native void START_CUTSCENE_NOW(const char* name)l
extern _native void STOP_CUTSCENE(void)l
extern _native void STREAM_CUTSCENE(void)l
#pragma endregion//}
#pragma region INTERIOR//{
extern _native void ACTIVATE_INTERIOR(Interior interior, bool unknownTrue)l
extern _native void GET_INTERIOR_AT_COORDS(float x, float y, float z, Interior *pInterior)l
extern _native void GET_INTERIOR_FROM_CAR(Vehicle vehicle, Interior *pInterior)l
extern _native void GET_INTERIOR_FROM_CHAR(Ped ped, Interior *pInterior)l
extern _native void GET_INTERIOR_HEADING(Interior interior, float *pHeading)l
extern _native void GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(Interior interior, float x, float y, float z, float *pOffset)l
#pragma endregion//}
#pragma region CAM//{
extern _native bool CAM_IS_SPHERE_VISIBLE(Camera camera, float pX, float pY, float pZ, float radius)l
extern _native bool DOES_CAM_EXIST(Camera camera)l
extern _native bool DOES_VIEWPORT_EXIST(int viewportid)l
extern _native bool GET_VIEWPORT_POSITION_OF_COORD(float x, float y, float z, float *vx, float *vy, float *vz)l
extern _native bool IS_CAM_ACTIVE(Camera camera)l
extern _native bool IS_CAM_HAPPY(int cam)l
extern _native bool IS_CAM_INTERPOLATING(void)l
extern _native bool IS_CAM_PROPAGATING(Camera camera)l
extern _native bool IS_CAM_SEQUENCE_COMPLETE(int Unk535)l
extern _native bool IS_CAM_SHAKING(void)l
extern _native bool IS_FOLLOW_VEHICLE_CAM_OFFSET_ACTIVE(void)l
extern _native bool IS_SPECIFIC_CAM_INTERPOLATING(int cam)l
extern _native bool IS_VIEWPORT_ACTIVE(int viewportid)l
extern _native int COUNT_SCRIPT_CAMS(void)l
extern _native int COUNT_SCRIPT_CAMS_BY_TYPE_AND_OR_STATE(int type, int Unk536, int Unk537)l
extern _native int GET_CAM_STATE(int cam)l
extern _native void ACTIVATE_SCRIPTED_CAMS(bool Unk538, bool Unk539)l
extern _native void ACTIVATE_VIEWPORT(int viewportid, bool activate)l
extern _native void ADD_CAM_SPLINE_NODE(int cam, int camnode)l
extern _native void ATTACH_CAM_TO_OBJECT(int cam, Object obj)l
extern _native void ATTACH_CAM_TO_PED(int cam, Ped ped)l
extern _native void ATTACH_CAM_TO_VEHICLE(int cam, Vehicle veh)l
extern _native void ATTACH_CAM_TO_VIEWPORT(int cam, int viewportid)l
extern _native void BEGIN_CAM_COMMANDS(int * Unk540)l
extern _native void CAM_PROCESS(int cam)l
extern _native void CAM_RESTORE(void)l
extern _native void CAM_RESTORE_JUMPCUT(void)l
extern _native void CAM_SEQUENCE_CLOSE(void)l
extern _native void CAM_SEQUENCE_GET_PROGRESS(int Unk541, int *progress)l
extern _native void CAM_SEQUENCE_OPEN(int Unk542)l
extern _native void CAM_SEQUENCE_REMOVE(int Unk543)l
extern _native void CAM_SEQUENCE_START(int Unk544)l
extern _native void CAM_SEQUENCE_STOP(int Unk545)l
extern _native void CAM_SEQUENCE_WAIT(int cam, int time)l
extern _native void CAM_SET_CINEMATIC(Vehicle veh, bool set)l
extern _native void CAM_SET_DOLLY_ZOOM_LOCK(int cam, bool set)l
extern _native void CAM_SET_INTERPOLATION_DETAILS(int Unk546)l
extern _native void CAM_SET_INTERP_GRAPH_POS(int cam, int Unk547)l
extern _native void CAM_SET_INTERP_GRAPH_ROT(int cam, int val)l
extern _native void CAM_SET_INTERP_STATE_SRC(int cam, int Unk548)l
extern _native void CAM_SET_INTERP_STATE_SRC(int Unk549, int Unk550)l
extern _native void CELL_CAM_ACTIVATE(bool Unk551, bool Unk552)l
extern _native void CELL_CAM_SET_CENTRE_POS(float x, float y)l
extern _native void CELL_CAM_SET_COLOUR_BRIGHTNESS(float Unk553, float Unk554, float Unk555, float Unk556)l
extern _native void CELL_CAM_SET_ZOOM(float zoom)l
extern _native void CLEAR_ROOM_FOR_VIEWPORT(int viewportid)l
extern _native void CLONE_CAM(int cam, int *camcopy)l
extern _native void CREATE_CAM(uint camtype_usually14, Camera *camera)l
extern _native void CREATE_HTML_VIEWPORT(int *htmlviewport)l
extern _native void CREATE_VIEWPORT(int *viewport)l
extern _native void DESTROY_ALL_CAMS(void)l
extern _native void DESTROY_ALL_SCRIPT_VIEWPORTS(void)l
extern _native void DESTROY_CAM(Camera camera)l
extern _native void DESTROY_VIEWPORT(int viewportid)l
extern _native void DETACH_CAM_FROM_VIEWPORT(int Unk557)l
extern _native void DISABLE_HELI_CHASE_CAM_BONNET_NITRO_FIX(void)l
extern _native void DISABLE_HELI_CHASE_CAM_THIS_UPDATE(void)l
extern _native void DISABLE_INTERMEZZO_CAMS(void)l
extern _native void ENABLE_CAM_COLLISION(int cam, bool enable)l
extern _native void ENABLE_FOV_LOD_MULTIPLIER(bool enable)l
extern _native void END_CAM_COMMANDS(int * Unk558)l
extern _native void FORCE_GAME_TELESCOPE_CAM(bool force)l
extern _native void FORCE_NO_CAM_PAUSE(bool foce)l
extern _native void GET_CAM_FAR_CLIP(int cam, float *clip)l
extern _native void GET_CAM_FAR_DOF(int cam, float *fardof)l
extern _native void GET_CAM_FOV(Camera camera, float *fov)l
extern _native void GET_CAM_MOTION_BLUR(int cam, int *blur)l
extern _native void GET_CAM_NEAR_CLIP(int cam, float *clip)l
extern _native void GET_CAM_NEAR_DOF(int cam, float *dof)l
extern _native void GET_CAM_POS(Camera camera, float *pX, float *pY, float *pZ)l
extern _native void GET_CAM_ROT(Camera camera, float *angleX, float *angleY, float *angleZ)l
extern _native void GET_CINEMATIC_CAM(int *cam)l
extern _native void GET_FOLLOW_VEHICLE_CAM_SUBMODE(int *mode)l
extern _native void GET_FREE_CAM(int *cam)l
extern _native void GET_GAME_CAM(Camera *camera)l
extern _native void GET_GAME_CAM_CHILD(Camera *camera)l
extern _native void GET_GAME_VIEWPORT_ID(int *viewportid)l
extern _native void GET_KEY_FOR_VIEWPORT_IN_ROOM(int viewportid, int *roomkey)l
extern _native void GET_RADAR_VIEWPORT_ID(int *viewport)l
extern _native void GET_ROOT_CAM(Cam *rootcam)l
extern _native void GET_SCREEN_VIEWPORT_ID(int *viewportid)l
extern _native void GET_SCRIPT_CAM(int *cam)l
extern _native void GET_SCRIPT_DRAW_CAM(int *cam)l
extern _native void GET_VIEWPORT_POS_AND_SIZE(int viewportid, float *x, float *y, float *xsize, float *ysize)l
extern _native void HINT_CAM(float x, float y, float z, int Unk559, int Unk560, int Unk561, int Unk562)l
extern _native void M(int cam, int heading)l	//set cam follow heading , "m" is a corect name
extern _native void POINT_CAM_AT_CAM(int cam, int camnext)l
extern _native void POINT_CAM_AT_COORD(int cam, float x, float y, float z)l
extern _native void POINT_CAM_AT_OBJECT(int cam, Object obj)l
extern _native void POINT_CAM_AT_PED(int cam, Ped ped)l
extern _native void POINT_CAM_AT_VEHICLE(int cam, Vehicle veh)l
extern _native void POINT_FIXED_CAM(float x, float y, float z, int Unk563)l
extern _native void POINT_FIXED_CAM_AT_OBJ(Object obj, int cam)l
extern _native void POINT_FIXED_CAM_AT_PED(Ped ped, int cam)l
extern _native void POINT_FIXED_CAM_AT_POS(float x, float y, float z, int cam)l
extern _native void POINT_FIXED_CAM_AT_VEHICLE(Vehicle veh, int cam)l
extern _native void PROSTITUTE_CAM_ACTIVATE(bool activate)l
extern _native void RESET_CAM_INTERP_CUSTOM_SPEED_GRAPH(void)l
extern _native void RESET_CAM_SPLINE_CUSTOM_SPEED_GRAPH(void)l
extern _native void SET_BLOCK_CAMERA_TOGGLE(bool set)l
extern _native void SET_CAMERA_AUTO_SCRIPT_ACTIVATION(bool set)l
extern _native void SET_CAMERA_BEGIN_CAM_COMMANDS_REQUIRED(bool set)l
extern _native void SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS(bool value)l
extern _native void SET_CAMERA_STATE(int cam, int state)l
extern _native void SET_CAM_ACTIVE(Camera camera, bool value)l
extern _native void SET_CAM_ATTACH_OFFSET(int cam, float x, float y, float z)l
extern _native void SET_CAM_ATTACH_OFFSET_IS_RELATIVE(int cam, bool set)l
extern _native void SET_CAM_BEHIND_PED(Ped ped)l
extern _native void SET_CAM_COMPONENT_SHAKE(int cam, int componentid, int Unk564, int time, float x, float y, float z)l
extern _native void SET_CAM_DOF_FOCUSPOINT(int cam, float x, float y, float z, float Unk565)l
extern _native void SET_CAM_FAR_CLIP(int cam, float clip)l
extern _native void SET_CAM_FAR_DOF(int cam, float fardof)l
extern _native void SET_CAM_FOV(Camera camera, float fov)l
extern _native void SET_CAM_INHERIT_ROLL_OBJECT(int cam, Object obj)l
extern _native void SET_CAM_INHERIT_ROLL_PED(int cam, Ped ped)l
extern _native void SET_CAM_INHERIT_ROLL_VEHICLE(int cam, Vehicle veh)l
extern _native void SET_CAM_INTERP_CUSTOM_SPEED_GRAPH(float speed)l
extern _native void SET_CAM_INTERP_DETAIL_ROT_STYLE_ANGLES(int Unk566)l
extern _native void SET_CAM_INTERP_DETAIL_ROT_STYLE_QUATS(int Unk567)l
extern _native void SET_CAM_INTERP_STYLE_CORE(int cam0, int cam1, int cam2, int time, bool flag)l
extern _native void SET_CAM_INTERP_STYLE_DETAILED(int cam, bool Unk568, bool Unk569, bool Unk570, bool Unk571)l
extern _native void SET_CAM_IN_FRONT_OF_PED(Ped ped)l
extern _native void SET_CAM_MOTION_BLUR(int cam, float blur)l
extern _native void SET_CAM_NAME(int cam, const char* camname)l
extern _native void SET_CAM_NEAR_CLIP(int cam, float clip)l
extern _native void SET_CAM_NEAR_DOF(int cam, float dof)l
extern _native void SET_CAM_POINT_DAMPING_PARAMS(int cam, float x, float y, float z)l
extern _native void SET_CAM_POINT_OFFSET(int cam, float x, float y, float z)l
extern _native void SET_CAM_POINT_OFFSET_IS_RELATIVE(int cam, bool set)l
extern _native void SET_CAM_POS(Camera camera, float pX, float pY, float pZ)l
extern _native void SET_CAM_PROPAGATE(Camera camera, bool value)l
extern _native void SET_CAM_ROLL(int cam, float roll)l
extern _native void SET_CAM_ROT(Camera camera, float angleX, float angleY, float angleZ)l
extern _native void SET_CAM_SHAKE(int cam, bool Unk572, int shakeval)l
extern _native void SET_CAM_SPLINE_CUSTOM_SPEED_GRAPH(float speed)l
extern _native void SET_CAM_SPLINE_DURATION(int cam, int duration)l
extern _native void SET_CAM_SPLINE_PROGRESS(int cam, float progress)l
extern _native void SET_CAM_SPLINE_SPEED_CONSTANT(int cam, bool set)l
extern _native void SET_CAM_SPLINE_SPEED_GRAPH(int cam, int Unk573)l
extern _native void SET_CAM_TARGET_PED(Camera camera, Ped ped)l
extern _native void SET_CINEMATIC_BUTTON_ENABLED(bool set)l
extern _native void SET_DANCE_SHAKE_ACTIVE_THIS_UPDATE(float shake)l
extern _native void SET_DANCE_SHAKE_INACTIVE_IMMEDIATELY(void)l
extern _native void SET_DRUNK_CAM(Cam cam, float val, int time)l
extern _native void SET_FIXED_CAM_POS(float x, float y, float z)l
extern _native void SET_FOLLOW_PED_PITCH_LIMIT_DOWN(float pitchdownlim)l
extern _native void SET_FOLLOW_PED_PITCH_LIMIT_UP(float pitchuplim)l
extern _native void SET_FOLLOW_VEHICLE_CAM_OFFSET(bool Unk574, float x, float y, float z)l
extern _native void SET_FOLLOW_VEHICLE_CAM_SUBMODE(int mode)l
extern _native void SET_FOLLOW_VEHICLE_PITCH_LIMIT_DOWN(float pitchdownlim)l
extern _native void SET_FOLLOW_VEHICLE_PITCH_LIMIT_UP(float pitchuplim)l
extern _native void SET_GAME_CAMERA_CONTROLS_ACTIVE(bool active)l
extern _native void SET_GAME_CAM_HEADING(float heading)l
extern _native void SET_GAME_CAM_PITCH(float pitch)l
extern _native void SET_HINT_ADVANCED_PARAMS(float Unk575, float Unk576, float Unk577, float Unk578, bool Unk579)l
extern _native void SET_HINT_FOV(float fov)l
extern _native void SET_HINT_MOVE_IN_DIST(float dist)l
extern _native void SET_HINT_MOVE_IN_DIST_DEFAULT(void)l
extern _native void SET_HINT_TIMES(float Unk580, float Unk581, float Unk582)l
extern _native void SET_HINT_TIMES_DEFAULT(void)l
extern _native void SET_PTFX_CAM_INSIDE_VEHICLE(bool set)l
extern _native void SET_ROOM_FOR_VIEWPORT_BY_KEY(int viewportid, uint roomkey)l
extern _native void SET_ROOM_FOR_VIEWPORT_BY_NAME(int viewportid, const char* roomname)l
extern _native void SET_TELESCOPE_CAM_ANGLE_LIMITS(float Unk583, float Unk584, float Unk585, float Unk586, float Unk587, float Unk588)l
extern _native void SET_VIEWPORT(int viewportid, float Unk589, float Unk590, float Unk591, float Unk592)l
extern _native void SET_VIEWPORT_DESTINATION(int viewportid, float x, float y, float z, float Unk593, int Unk594, int Unk595)l
extern _native void SET_VIEWPORT_MIRRORED(int viewportid, bool set)l
extern _native void SET_VIEWPORT_PRIORITY(int viewportid, int priority)l
extern _native void SET_VIEWPORT_SHAPE(int cam, int shape)l
extern _native void SNAPSHOT_CAM(int cam, int Unk596)l
extern _native void UNATTACH_CAM(int cam)l
extern _native void UNINHERIT_CAM_ROLL(int cam)l
extern _native void UNPOINT_CAM(int cam)l
#pragma endregion//}
#pragma region WEAPON//{
extern _native bool GET_AMMO_IN_CLIP(Ped ped, uint weapon, uint *pAmmo)l
extern _native bool GET_CURRENT_CHAR_WEAPON(Ped ped, uint *pWeapon)l
extern _native bool GET_MAX_AMMO(Ped ped, uint weapon, uint *pMaxAmmo)l
extern _native bool HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(Ped ped, uint weapon)l
extern _native bool HAS_CHAR_GOT_WEAPON(Ped ped, uint weapon)l
extern _native float GET_LOCAL_PLAYER_WEAPON_STAT(int wtype, int wid)l
extern _native ScriptAny SET_AMMO_IN_CLIP(Ped ped, uint weapon, uint ammo)l
extern _native void ADD_AMMO_TO_CHAR(Ped ped, uint weapon, uint amount)l
extern _native void BLOCK_PED_WEAPON_SWITCHING(Ped ped, bool value)l
extern _native void ENABLE_MAX_AMMO_CAP(bool enable)l
extern _native void FIRE_SINGLE_BULLET(float x, float y, float z, float targetX, float targetY, float targetZ, uint unknown)l
extern _native void FORCE_CHAR_TO_DROP_WEAPON(Ped ped)l
extern _native void GET_AMMO_IN_CHAR_WEAPON(Ped ped, uint weapon, uint *pAmmo)l
extern _native void GET_CHAR_WEAPON_IN_SLOT(Ped ped, uint slot, uint *pWeapon, uint *pAmmo0, uint *pAmmo1)l
extern _native void GET_MAX_AMMO_IN_CLIP(Ped ped, uint weapon, uint *pMaxAmmo)l
extern _native void GET_WEAPONTYPE_MODEL(int weapontype, uint *model)l
extern _native void GET_WEAPONTYPE_SLOT(int weapon, int *slot)l
extern _native void GIVE_DELAYED_WEAPON_TO_CHAR(Ped ped, int weapon, int delaytime, bool flag)l
extern _native void GIVE_WEAPON_TO_CHAR(Ped ped, uint weapon, uint ammo, bool unknown0)l
extern _native void HIDE_CHAR_WEAPON_FOR_SCRIPTED_CUTSCENE(Ped ped, bool hide)l
extern _native void REMOVE_ALL_CHAR_WEAPONS(Ped ped)l
extern _native void REMOVE_WEAPON_FROM_CHAR(Ped ped, uint weapon)l
extern _native void RESET_LOCAL_PLAYER_WEAPON_STAT(int wtype, int wid)l
extern _native void SET_CAN_TARGET_CHAR_WITHOUT_LOS(Ped ped, bool set)l
extern _native void SET_CHAR_AMMO(Ped ped, uint weapon, uint ammo)l
extern _native void SET_CHAR_CURRENT_WEAPON_VISIBLE(Ped ped, bool visble)l
extern _native void SET_CHAR_WEAPON_SKILL(Ped ped, int skill)l
extern _native void SET_CURRENT_CHAR_WEAPON(Ped ped, uint w, bool unknownTrue)l
extern _native void SET_ENABLE_NEAR_CLIP_SCAN(bool set)l
extern _native void SET_ENABLE_RC_DETONATE(bool set)l
extern _native void SET_ENABLE_RC_DETONATE_ON_CONTACT(bool set)l
extern _native void SET_HOT_WEAPON_SWAP(bool set)l
#pragma endregion//}
#pragma region STREAMING//{
extern _native bool HAS_COLLISION_FOR_MODEL_LOADED(uint model)l
extern _native bool HAS_MODEL_LOADED(uint model)l
extern _native bool HAS_STREAMED_TXD_LOADED(const char* txdName)l
extern _native bool HAS_THIS_ADDITIONAL_TEXT_LOADED(const char* textName, uint textIndex)l
extern _native bool HAVE_ANIMS_LOADED(const char* animName)l
extern _native bool HAVE_REQUESTED_PATH_NODES_BEEN_LOADED(uint requestId)l
extern _native bool IS_MODEL_IN_CDIMAGE(uint model)l
extern _native bool IS_STREAMING_ADDITIONAL_TEXT(uint textIndex)l
extern _native bool IS_STREAMING_PRIORITY_REQUESTS(void)l
extern _native bool IS_STREAMING_THIS_ADDITIONAL_TEXT(const char* str0, int Unk597, int Unk598)l
extern _native bool PRELOAD_STREAM(const char* name)l
extern _native bool PRELOAD_STREAM_WITH_START_OFFSET(const char* StreamName, int StartOffset)l
extern _native bool REMOVE_NAVMESH_REQUIRED_REGION(float Unk599, float Unk600)l
extern _native bool UPDATE_LOAD_SCENE(void)l
extern _native void ADD_ADDITIONAL_POPULATION_MODEL(uint model)l
extern _native void ENABLE_SCENE_STREAMING(bool enable)l
extern _native void FINISH_STREAMING_REQUEST_LIST(void)l
extern _native void GET_MODEL_DIMENSIONS(uint model, vector3 *pMinVector, vector3 *pMaxVector)l
extern _native void LOAD_ALL_OBJECTS_NOW(void)l
extern _native void LOAD_SCENE(float x, float y, float z)l
extern _native void LOAD_SCENE_FOR_ROOM_BY_KEY(int interior, uint roomhash)l
extern _native void MARK_MODEL_AS_NO_LONGER_NEEDED(uint model)l
extern _native void MARK_STREAMED_TXD_AS_NO_LONGER_NEEDED(const char* txdName)l
extern _native void REMOVE_ADDITIONAL_POPULATION_MODEL(uint model)l
extern _native void REMOVE_ALL_INACTIVE_GROUPS_FROM_CLEANUP_LIST(void)l
extern _native void REMOVE_ANIMS(const char* animName)l
extern _native void REMOVE_IPL(const char* iplName)l
extern _native void REMOVE_IPL_DISCREETLY(const char* iplname)l
extern _native void REMOVE_TXD(TextureDict txd)l
extern _native void REQUEST_ADDITIONAL_TEXT(const char* textName, uint textIndex)l
extern _native void REQUEST_ALL_SLODS_IN_WORLD(void)l
extern _native void REQUEST_ANIMS(const char* animName)l
extern _native void REQUEST_CAR_RECORDING(int CarRecId)l
extern _native void REQUEST_COLLISION_AT_POSN(float x, float y, float z)l
extern _native void REQUEST_COLLISION_FOR_MODEL(uint model)l
extern _native void REQUEST_INTERIOR_MODELS(uint model, const char* interiorName)l
extern _native void REQUEST_IPL(const char* iplName)l
extern _native void REQUEST_MODEL(uint model)l
extern _native void REQUEST_STREAMED_TXD(const char* txdName, bool unknown)l
extern _native void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(uint model, float x, float y, float z, int state, float Unk601)l
extern _native void SET_STREAMING_REQUEST_LIST_TIME(int time)l
extern _native void SET_STREAM_PARAMS(float rolloff, int UnkTime)l
extern _native void SIMULATE_UPDATE_LOAD_SCENE(void)l
extern _native void START_LOAD_SCENE(float x, float y, float z)l
extern _native void START_STREAMING_REQUEST_LIST(const char* name)l
extern _native void STOP_STREAM(void)l
extern _native Texture GET_TEXTURE(TextureDict dictionary, const char* textureName)l
extern _native Texture GET_TEXTURE_FROM_STREAMED_TXD(const char* txdName, const char* textureName)l
extern _native TextureDict GET_TXD(const char* txdName)l
extern _native TextureDict LOAD_TXD(const char* txdName)l
#pragma endregion//}
#pragma region SCRIPT//{
extern _native bool DOES_SCRIPT_EXIST(const char* name)l
extern _native bool HAS_SCRIPT_LOADED(const char* scriptName)l
extern _native bool IS_THREAD_ACTIVE(uint threadId)l
extern _native uint GET_ID_OF_THIS_THREAD(void)l
extern _native uint GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(const char* scriptName)l
extern _native void ALLOCATE_SCRIPT_TO_OBJECT(const char* ScriptName, uint model, int Unk602, float radius, int UnkTime)l
extern _native void ALLOCATE_SCRIPT_TO_RANDOM_PED(const char* ScriptName, uint model, int Unk603, bool flag)l
extern _native void ALLOW_THIS_SCRIPT_TO_BE_PAUSED(bool allows)l
extern _native void DESTROY_THREAD(int ScriptHandle)l
extern _native void GET_SCRIPT_RENDERTARGET_RENDER_ID(uint *pRenderId)l
extern _native void MARK_SCRIPT_AS_NO_LONGER_NEEDED(const char* scriptName)l
extern _native void REQUEST_SCRIPT(const char* scriptName)l
extern _native void SET_INTERP_FROM_GAME_TO_SCRIPT(bool Unk604, int Unk605)l
extern _native void SET_INTERP_FROM_SCRIPT_TO_GAME(bool Unk606, int Unk607)l
extern _native void SET_SCRIPT_LIMIT_TO_GANG_SIZE(int size)l
extern _native void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(bool allow)l
extern _native void TERMINATE_THIS_SCRIPT(void)l
extern _native void THIS_SCRIPT_SHOULD_BE_SAVED(void)l
#pragma endregion//}
#pragma region UI//{
extern _native Blip GET_FIRST_BLIP_INFO_ID(uint type)l
extern _native Blip GET_NEXT_BLIP_INFO_ID(uint type)l
extern _native bool DOES_BLIP_EXIST(Blip blip)l
extern _native bool DOES_TEXT_LABEL_EXIST(const char* gxtentry)l
extern _native bool HAS_ADDITIONAL_TEXT_LOADED(uint textIndex)l
extern _native bool IS_BLIP_SHORT_RANGE(Blip blip)l
extern _native bool IS_STRING_NULL(const char* str)l
extern _native bool IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(const char* gxtentry)l
extern _native bool IS_THIS_HELP_MESSAGE_WITH_NUMBER_BEING_DISPLAYED(const char* gxtentry, int number)l
extern _native bool IS_THIS_HELP_MESSAGE_WITH_STRING_BEING_DISPLAYED(const char* gxtentry, const char* str)l
extern _native const char* GET_STRING_FROM_STRING(const char* str, int startsymb, int endsymb)l
extern _native const char* GET_STRING_FROM_TEXT_FILE(const char* gxtentry)l
//extern _native const char* GET_BLIP_NAME(Blip blip)l
extern _native const char* GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING(const char* literalString, uint chars)l
extern _native const char* GET_FIRST_N_CHARACTERS_OF_STRING(const char* gxtName, uint chars)l
extern _native const char* GET_NTH_INTEGER_IN_STRING(const char* gxtName, uint index)l
extern _native const char* GET_STRING_FROM_HASH_KEY(uint hash)l
extern _native float GET_STRING_WIDTH_WITH_STRING(const char* gxtName, const char* literalString)l
extern _native int GET_BLIP_INFO_ID_ROTATION(int blip)l
extern _native int GET_LENGTH_OF_STRING_WITH_THIS_HASH_KEY(uint gxtkey)l
extern _native int GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL_INS_NUM(ScriptAny Unk608, ScriptAny Unk609, ScriptAny Unk610)l
extern _native int GET_SIMPLE_BLIP_ID(void)l
extern _native int GET_STRING_WIDTH(const char* gxtName)l
extern _native int GET_STRING_WIDTH_WITH_NUMBER(const char* gxtName, int number)l
extern _native int GET_STRING_WIDTH_WITH_TEXT_AND_INT(const char* gxtname, const char* gxtnamenext, int val)l
extern _native int GET_WIDTH_OF_LITERAL_STRING(const char* str)l
extern _native int GET_WIDTH_OF_SUBSTRING_GIVEN_TEXT_LABEL(const char* gxtname, bool Unk611, ScriptAny Unk612, ScriptAny Unk613, ScriptAny Unk614)l
extern _native Object GET_BLIP_INFO_ID_OBJECT_INDEX(Blip blip)l
extern _native Ped GET_BLIP_INFO_ID_PED_INDEX(Blip blip)l
extern _native Pickup GET_BLIP_INFO_ID_PICKUP_INDEX(Blip blip)l
extern _native ScriptAny IS_THIS_PRINT_BEING_DISPLAYED(const char* gxtentry, int Unk615, int Unk616, int Unk617, int Unk618, int Unk619, int Unk620, int Unk621, int Unk622, int Unk623, int Unk624)l
extern _native uint GET_BLIP_INFO_ID_DISPLAY(Blip blip)l
extern _native uint GET_BLIP_INFO_ID_TYPE(Blip blip)l
extern _native uint GET_BLIP_SPRITE(Blip blip)l
extern _native uint GET_LENGTH_OF_LITERAL_STRING(const char* literalString)l
extern _native uint GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(const char* gxtName)l
extern _native Vehicle GET_BLIP_INFO_ID_CAR_INDEX(Blip blip)l
extern _native void ACTIVATE_FRONTEND(void)l
extern _native void ACTIVATE_REPLAY_MENU(void)l
extern _native void ACTIVATE_SAVE_MENU(void)l
extern _native void ADD_BLIP_FOR_CAR(Vehicle vehicle, Blip *pBlip)l
extern _native void ADD_BLIP_FOR_CHAR(Ped ped, Blip *pBlip)l
extern _native void ADD_BLIP_FOR_CONTACT(float x, float y, float z, Blip *pBlip)l
extern _native void ADD_BLIP_FOR_COORD(float x, float y, float z, Blip *pBlip)l
extern _native void ADD_BLIP_FOR_GANG_TERRITORY(float x0, float y0, float x1, float y1, int colour, int *blip)l
extern _native void ADD_BLIP_FOR_OBJECT(Object obj, Blip *pBlip)l
extern _native void ADD_BLIP_FOR_PICKUP(Pickup pickup, Blip *pBlip)l
extern _native void ADD_BLIP_FOR_RADIUS(float x, float y, float z, int type, int *blip)l
extern _native void ADD_BLIP_FOR_WEAPON(float x, float y, float z, int *blip)l
extern _native void ADD_FIRST_N_CHARACTERS_OF_STRING_TO_HTML_SCRIPT_OBJECT(int htmlobj, const char* str, int n)l
extern _native void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(bool add)l
extern _native void ADD_SIMPLE_BLIP_FOR_PICKUP(Pickup pickup)l
extern _native void ADD_STRING_TO_HTML_SCRIPT_OBJECT(int htmlobj, const char* str)l
extern _native void ADD_STRING_TO_NEWS_SCROLLBAR(const char* str)l
extern _native void ADD_STRING_WITH_THIS_TEXT_LABEL_TO_PREVIOUS_BRIEF(const char* gxtname)l
extern _native void ADD_TICKER_TO_PREVIOUS_BRIEF_WITH_UNDERSCORE(ScriptAny Unk625, ScriptAny Unk626, ScriptAny Unk627, ScriptAny Unk628, ScriptAny Unk629, ScriptAny Unk630, ScriptAny Unk631)l	//used for japanese text correcting
extern _native void ADD_TO_PREVIOUS_BRIEF(const char* gxtentry)l
extern _native void ADD_TO_PREVIOUS_BRIEF_WITH_UNDERSCORE(const char* gxtentry)l
extern _native void CHANGE_BLIP_ALPHA(Blip blip, int alpha)l
extern _native void CHANGE_BLIP_COLOUR(Blip blip, ColourIndex colour)l
extern _native void CHANGE_BLIP_DISPLAY(Blip blip, uint display)l
extern _native void CHANGE_BLIP_NAME_FROM_ASCII(Blip blip, const char* blipName)l
extern _native void CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip blip, const char* gxtName)l
extern _native void CHANGE_BLIP_NAME_TO_PLAYER_NAME(int blip, int playerid)l
extern _native void CHANGE_BLIP_PRIORITY(Blip blip, uint priority)l
extern _native void CHANGE_BLIP_ROTATION(int blip, int rotation)l
extern _native void CHANGE_BLIP_SCALE(Blip blip, float scale)l
extern _native void CHANGE_BLIP_SPRITE(Blip blip, uint sprite)l
extern _native void CHANGE_BLIP_TEAM_RELEVANCE(int blip, int relevance)l
extern _native void CHANGE_PICKUP_BLIP_COLOUR(int colour)l
extern _native void CHANGE_PICKUP_BLIP_DISPLAY(int display)l
extern _native void CHANGE_PICKUP_BLIP_PRIORITY(int priority)l
extern _native void CHANGE_PICKUP_BLIP_SCALE(float scale)l
extern _native void CHANGE_PICKUP_BLIP_SPRITE(int sprite)l
extern _native void CHANGE_TERRITORY_BLIP_SCALE(int blip, float Unk632, float Unk633)l
extern _native void CLEAR_ADDITIONAL_TEXT(int textid, bool Unk634)l
extern _native void CLEAR_BRIEF(void)l
extern _native void CLEAR_HELP(void)l
extern _native void CLEAR_NEWS_SCROLLBAR(void)l
extern _native void CLEAR_ONSCREEN_COUNTER(int counterid)l
extern _native void CLEAR_ONSCREEN_TIMER(int timerid)l
extern _native void CLEAR_PRINTS(void)l
extern _native void CLEAR_SMALL_PRINTS(void)l
extern _native void CLEAR_TEXT_LABEL(const char* label)l
extern _native void CLEAR_THIS_BIG_PRINT(const char* gxtentry)l
extern _native void CLEAR_THIS_PRINT(const char* gxtentry)l
extern _native void CLEAR_THIS_PRINT_BIG_NOW(bool Unk635)l
extern _native void CONVERT_THEN_ADD_STRING_TO_HTML_SCRIPT_OBJECT(int htmlobj, const char* strgxtkey)l
extern _native void CREATE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS_IN_AREA(float x, float y, float z, float radius, int bliptype)l
extern _native void DEACTIVATE_FRONTEND(void)l
extern _native void DIM_BLIP(Blip blip, bool unknownTrue)l
extern _native void DISPLAY_ALTIMETER_THIS_FRAME(void)l
extern _native void DISPLAY_AMMO(bool display)l
extern _native void DISPLAY_AREA_NAME(bool display)l
extern _native void DISPLAY_CASH(bool display)l
extern _native void DISPLAY_FRONTEND_MAP_BLIPS(bool display)l
extern _native void DISPLAY_GRIME_THIS_FRAME(void)l
extern _native void DISPLAY_HELP_TEXT_THIS_FRAME(const char* gxtkey, bool Unk636)l
extern _native void DISPLAY_HUD(bool display)l
extern _native void DISPLAY_LOADING_THIS_FRAME_WITH_SCRIPT_SPRITES(void)l
extern _native void DISPLAY_NON_MINIGAME_HELP_MESSAGES(bool Unk637)l
extern _native void DISPLAY_NTH_ONSCREEN_COUNTER_WITH_STRING(int Unk638, int Unk639, int Unk640, const char* str)l
extern _native void DISPLAY_ONSCREEN_TIMER_WITH_STRING(int timerid, bool Unk641, const char* str)l
extern _native void DISPLAY_RADAR(bool display)l
extern _native void DISPLAY_SNIPER_SCOPE_THIS_FRAME(void)l
extern _native void DISPLAY_TEXT(float x, float y, const char* gxtName)l
extern _native void DISPLAY_TEXT_SUBSTRING(ScriptAny Unk642, ScriptAny Unk643, ScriptAny Unk644, ScriptAny Unk645, ScriptAny Unk646, ScriptAny Unk647, ScriptAny Unk648)l
extern _native void DISPLAY_TEXT_WITH_2_NUMBERS(float x, float y, const char* gxtName, int number1, int number2)l
extern _native void DISPLAY_TEXT_WITH_3_NUMBERS(float x, float y, const char* gxtentry, int Unk649, int Unk650, int Unk651)l
extern _native void DISPLAY_TEXT_WITH_BLIP_NAME(float x, float y, const char* str, int blip)l
extern _native void DISPLAY_TEXT_WITH_FLOAT(float x, float y, const char* gxtName, float value, uint unknown)l
extern _native void DISPLAY_TEXT_WITH_LITERAL_STRING(float x, float y, const char* gxtName, const char* literalStr)l
extern _native void DISPLAY_TEXT_WITH_LITERAL_SUBSTRING(ScriptAny Unk652, ScriptAny Unk653, ScriptAny Unk654, ScriptAny Unk655, ScriptAny Unk656, ScriptAny Unk657)l
extern _native void DISPLAY_TEXT_WITH_NUMBER(float x, float y, const char* gxtName, int value)l
extern _native void DISPLAY_TEXT_WITH_STRING(float x, float y, const char* gxtName, const char* gxtStringName)l
extern _native void DISPLAY_TEXT_WITH_STRING_AND_INT(float x, float y, const char* gxtname, const char* gxtnamenext, int val)l
extern _native void DISPLAY_TEXT_WITH_SUBSTRING_GIVEN_HASH_KEY(float x, float y, const char* gxtkey, uint gxtkey0)l
extern _native void DISPLAY_TEXT_WITH_TWO_LITERAL_STRINGS(float x, float y, const char* gxtName, const char* literalStr1, const char* literalStr2)l
extern _native void DISPLAY_TEXT_WITH_TWO_STRINGS(float x, float y, const char* gxtName, const char* gxtStringName1, const char* gxtStringName2)l
extern _native void DISPLAY_TEXT_WITH_TWO_SUBSTRINGS_GIVEN_HASH_KEYS(float x, float y, const char* gxtkey, uint gxtkey0, uint gxtkey1)l
extern _native void FLASH_BLIP(Blip blip, bool on)l
extern _native void FLASH_BLIP_ALT(Blip blip, bool on)l
extern _native void FLASH_RADAR(bool flash)l
extern _native void FLASH_ROUTE(bool flash)l
extern _native void FLASH_WEAPON_ICON(bool on)l
extern _native void GET_BLIP_ALPHA(int blip, int *alpha)l
extern _native void GET_BLIP_COLOUR(Blip blip, ColourIndex *pColour)l
extern _native void GET_BLIP_COORDS(Blip blip, vector3 *pVector)l
extern _native void HIDE_HELP_TEXT_THIS_FRAME(void)l
extern _native void HIDE_HUD_AND_RADAR_THIS_FRAME(void)l
extern _native void INIT_FRONTEND_HELPER_TEXT(void)l
extern _native void LOAD_ADDITIONAL_TEXT(const char* textName, uint textIndex)l
extern _native void LOAD_SETTINGS(void)l
extern _native void LOAD_TEXT_FONT(uint font)l
extern _native void PAUSE_GAME(void)l
extern _native void PRINT(const char* gxtName, uint timeMS, bool enable)l
extern _native void PRINTFLOAT(float value)l
extern _native void PRINTINT(int value)l
extern _native void PRINTNL(void)l
extern _native void PRINTSTRING(const char* value)l
extern _native void PRINTVECTOR(float x, float y, float z)l
extern _native void PRINT_BIG(const char* gxtName, uint timeMS, bool enable)l
extern _native void PRINT_BIG_Q(const char* gxtentry, int time, int flag)l
extern _native void PRINT_HELP(const char* gxtName)l
extern _native void PRINT_HELP_FOREVER(const char* gxtName)l
extern _native void PRINT_HELP_FOREVER_WITH_NUMBER(const char* gxtName, int value)l
extern _native void PRINT_HELP_FOREVER_WITH_STRING(const char* gxtName, const char* gxtText)l
extern _native void PRINT_HELP_FOREVER_WITH_STRING_NO_SOUND(const char* gxtName, const char* gxtText)l
extern _native void PRINT_HELP_FOREVER_WITH_TWO_NUMBERS(const char* gxtentry, int Unk658, int Unk659)l
extern _native void PRINT_HELP_OVER_FRONTEND(const char* gxtentry)l
extern _native void PRINT_HELP_WITH_NUMBER(const char* gxtName, int value)l
extern _native void PRINT_HELP_WITH_STRING(const char* gxtName, const char* gxtText)l
extern _native void PRINT_HELP_WITH_STRING_NO_SOUND(const char* gxtName, const char* gxtText)l
extern _native void PRINT_HELP_WITH_TWO_NUMBERS(const char* gxtentry, int Unk660, int Unk661)l
extern _native void PRINT_NOW(const char* gxtName, uint timeMS, bool enable)l
extern _native void PRINT_STRING_IN_STRING(const char* gxtName, const char* gxtText, uint timeMS, bool enable)l
extern _native void PRINT_STRING_IN_STRING_NOW(const char* gxtName, const char* gxtText, uint timeMS, bool enable)l
extern _native void PRINT_STRING_WITH_LITERAL_STRING(const char* gxtentry, const char* string, int time, int flag)l
extern _native void PRINT_STRING_WITH_LITERAL_STRING_NOW(const char* gxtName, const char* text, uint timeMS, bool enable)l
extern _native void PRINT_STRING_WITH_SUBSTRING_GIVEN_HASH_KEY_NOW(const char* gxtkey0, uint gxtkey1, int time, int style)l
extern _native void PRINT_STRING_WITH_TWO_LITERAL_STRINGS(const char* gxtentry, const char* string1, const char* string2, int time, int flag)l
extern _native void PRINT_STRING_WITH_TWO_LITERAL_STRINGS_NOW(const char* gxtentry, const char* string1, const char* string2, int time, int flag)l
extern _native void PRINT_WITH_2_NUMBERS(const char* gxtName, int value1, int value2, uint timeMS, bool enable)l
extern _native void PRINT_WITH_2_NUMBERS_BIG(const char* gxtentry, int Unk662, int Unk663, int time, int flag)l
extern _native void PRINT_WITH_2_NUMBERS_NOW(const char* gxtName, int value1, int value2, uint timeMS, bool enable)l
extern _native void PRINT_WITH_3_NUMBERS(const char* gxtentry, int Unk664, int Unk665, int Unk666, int time, int flag)l
extern _native void PRINT_WITH_3_NUMBERS_NOW(const char* gxtentry, int Unk667, int Unk668, int Unk669, int time, int flag)l
extern _native void PRINT_WITH_4_NUMBERS(const char* gxtentry, int Unk670, int Unk671, int Unk672, int Unk673, int time, int flag)l
extern _native void PRINT_WITH_4_NUMBERS_NOW(const char* gxtentry, int Unk674, int Unk675, int Unk676, int Unk677, int time, int flag)l
extern _native void PRINT_WITH_5_NUMBERS(const char* gxtentry, int Unk678, int Unk679, int Unk680, int Unk681, int Unk682, int time, int flag)l
extern _native void PRINT_WITH_5_NUMBERS_NOW(const char* gxtentry, int Unk683, int Unk684, int Unk685, int Unk686, int Unk687, int time, int flag)l
extern _native void PRINT_WITH_6_NUMBERS(const char* gxtentry, int Unk688, int Unk689, int Unk690, int Unk691, int Unk692, int Unk693, int time, int flag)l
extern _native void PRINT_WITH_6_NUMBERS_NOW(const char* gxtentry, int Unk694, int Unk695, int Unk696, int Unk697, int Unk698, int Unk699, int time, int flag)l
extern _native void PRINT_WITH_NUMBER(const char* gxtName, int value, uint timeMS, bool enable)l
extern _native void PRINT_WITH_NUMBER_BIG(const char* gxtName, int value, uint timeMS, bool enable)l
extern _native void PRINT_WITH_NUMBER_NOW(const char* gxtName, int value, uint timeMS, bool enable)l
extern _native void REMOVE_BLIP(Blip blip)l
extern _native void REMOVE_BLIP_AND_CLEAR_INDEX(int blip)l
extern _native void SET_ALWAYS_DISPLAY_WEAPON_PICKUP_MESSAGE(bool set)l
extern _native void SET_BLIP_AS_FRIENDLY(Blip blip, bool value)l
extern _native void SET_BLIP_AS_SHORT_RANGE(Blip blip, bool value)l
extern _native void SET_BLIP_COORDINATES(int blip, float x, float y, float z)l
extern _native void SET_BLIP_MARKER_LONG_DISTANCE(int blip, bool set)l
extern _native void SET_HIDE_WEAPON_ICON(bool set)l
extern _native void SET_MESSAGES_WAITING(bool set)l
extern _native void SET_MESSAGE_FORMATTING(bool Unk700, int Unk701, int Unk702)l
extern _native void SET_MULTIPLAYER_HUD_CASH(uint cash)l
extern _native void SET_MULTIPLAYER_HUD_TIME(const char* str)l
extern _native void SET_ONSCREEN_COUNTER_FLASH_WHEN_FIRST_DISPLAYED(int counterid, bool flash)l
extern _native void SET_RADAR_AS_INTERIOR_THIS_FRAME(void)l
extern _native void SET_RADAR_SCALE(float scale)l
extern _native void SET_RADAR_ZOOM(float zoom)l
extern _native void SET_ROUTE(Blip blip, bool value)l
extern _native void SET_TEXT_BACKGROUND(bool value)l
extern _native void SET_TEXT_CENTRE(bool value)l
extern _native void SET_TEXT_CENTRE_WRAPX(float wrapx)l
extern _native void SET_TEXT_COLOUR(uint r, uint g, uint b, uint a)l
extern _native void SET_TEXT_DRAW_BEFORE_FADE(bool value)l
extern _native void SET_TEXT_DROPSHADOW(bool displayShadow, uint r, uint g, uint b, uint a)l
extern _native void SET_TEXT_EDGE(bool displayEdge, uint r, uint g, uint b, uint a)l
extern _native void SET_TEXT_FONT(uint font)l
extern _native void SET_TEXT_INPUT_ACTIVE(bool set)l
extern _native void SET_TEXT_JUSTIFY(bool value)l
extern _native void SET_TEXT_LINE_DISPLAY(uint unk1, uint unk2)l
extern _native void SET_TEXT_LINE_HEIGHT_MULT(float lineHeight)l
extern _native void SET_TEXT_PROPORTIONAL(bool value)l
extern _native void SET_TEXT_RENDER_ID(uint renderId)l
extern _native void SET_TEXT_RIGHT_JUSTIFY(bool value)l
extern _native void SET_TEXT_SCALE(float w, float h)l
extern _native void SET_TEXT_TO_USE_TEXT_FILE_COLOURS(bool value)l
extern _native void SET_TEXT_USE_UNDERSCORE(bool value)l
extern _native void SET_TEXT_VIEWPORT_ID(int id)l
extern _native void SET_TEXT_WRAP(float unk1, float unk2)l
extern _native void SHOW_BLIP_ON_ALTIMETER(int blip, bool show)l
extern _native void SHOW_SIGNIN_UI(void)l
extern _native void SHOW_UPDATE_STATS(bool show)l
extern _native void UNLOAD_TEXT_FONT(void)l
extern _native void UNPAUSE_GAME(void)l
extern _native void USE_PREVIOUS_FONT_SETTINGS(void)l
#pragma endregion//}
#pragma region GRAPHICS//{
extern _native bool ARE_WIDESCREEN_BORDERS_ACTIVE(void)l
extern _native bool GET_IS_HIDEF(void)l
extern _native bool GET_IS_WIDESCREEN(void)l
extern _native float GET_LINE_HEIGHT(void)l
extern _native int GET_FRAME_COUNT(void)l
extern _native int GET_NUMBER_LINES(float Unk703, float Unk704, const char* str)l
extern _native int GET_NUMBER_LINES_WITH_LITERAL_STRINGS(float Unk705, float Unk706, const char* str1, const char* str2, const char* str3)l
extern _native int GET_NUMBER_LINES_WITH_SUBSTRINGS(float Unk707, float Unk708, const char* str1, const char* str2, const char* str3)l
extern _native uint CREATE_CHECKPOINT(int type, float x, float y, float z, float Unk709, float Unk710)l
extern _native void DELETE_CHECKPOINT(uint checkpoint)l
extern _native void DISABLE_END_CREDITS_FADE(void)l
extern _native void DO_SCREEN_FADE_IN(uint timeMS)l
extern _native void DO_SCREEN_FADE_IN_UNHACKED(uint timeMS)l
extern _native void DO_SCREEN_FADE_OUT(uint timeMS)l
extern _native void DO_SCREEN_FADE_OUT_UNHACKED(uint timeMS)l
extern _native void DRAW_CHECKPOINT(float x, float y, float z, float radius, int r, int g, int b)l
extern _native void DRAW_CHECKPOINT_WITH_ALPHA(float x, float y, float z, float radius, int r, int g, int b, int a)l
extern _native void DRAW_COLOURED_CYLINDER(float x, float y, float z, float Unk712, float Unk713, int r, int g, int b, int a)l
extern _native void DRAW_CORONA(float x, float y, float z, float radius, ScriptAny Unk714, ScriptAny Unk715, ScriptAny Unk716, ScriptAny Unk717, ScriptAny Unk718)l
extern _native void DRAW_CURVED_WINDOW(float Unk719, float Unk720, float Unk721, float Unk722, uint alpha)l
extern _native void DRAW_CURVED_WINDOW_NOTEXT(float Unk723, float Unk724, float Unk725, float Unk726, int Unk727)l
extern _native void DRAW_CURVED_WINDOW_TEXT(float Unk728, float Unk729, float Unk730, int Unk731, int Unk732, const char* str0, const char* str1, int Unk733)l
extern _native void DRAW_FRONTEND_HELPER_TEXT(const char* str0, const char* str1, bool Unk734)l
extern _native void DRAW_LIGHT_WITH_RANGE(float x, float y, float z, int r, int g, int b, float width, float height)l
extern _native void DRAW_MOVIE(float Unk735, float Unk736, float Unk737, float Unk738, float Unk739, int r, int g, int b, int a)l
extern _native void DRAW_RECT(float x1, float y1, float x2, float y2, uint r, uint g, uint b, uint a)l
extern _native void DRAW_SPHERE(float x, float y, float z, float radius)l
extern _native void DRAW_SPRITE(uint texture, float Unk740, float Unk741, float Unk742, float Unk743, float angle, int r, int g, int b, int a)l
extern _native void DRAW_SPRITE_FRONT_BUFF(float x0, float y0, float x1, float y1, float rotation, int r, int g, int b, int a)l
extern _native void DRAW_SPRITE_PHOTO(float x0, float y0, float x1, float y1, float rotation, int r, int g, int b, int a)l
extern _native void DRAW_SPRITE_WITH_FIXED_ROTATION(uint texture, float Unk744, float Unk745, float Unk746, float Unk747, float angle, int r, int g, int b, int a)l
extern _native void DRAW_SPRITE_WITH_UV(uint texture, float Unk748, float Unk749, float Unk750, float Unk751, float angle, int r, int g, int b, int a)l
extern _native void DRAW_SPRITE_WITH_UV_COORDS(uint texture, float Unk752, float Unk753, float Unk754, float Unk755, float Unk756, float Unk757, float Unk758, float Unk759, float angle, int r, int g, int b, int a)l
extern _native void DRAW_TOPLEVEL_SPRITE(uint texture, float Unk760, float Unk761, float Unk762, float Unk763, float angle, int r, int g, int b, int a)l
extern _native void DRAW_WINDOW(float Unk764, float Unk765, float Unk766, float Unk767, const char* str, uint alpha)l
extern _native void DRAW_WINDOW_TEXT(float Unk768, float Unk769, float Unk770, int Unk771, const char* str0, int Unk772)l
extern _native void ENABLE_DEFERRED_LIGHTING(bool enable)l
extern _native void ENABLE_END_CREDITS_FADE(void)l
extern _native void ENABLE_SHADOWS(bool enable)l
extern _native void GET_FRAME_TIME(float *time)l
extern _native void GET_HELP_MESSAGE_BOX_SIZE(float *x, float *y)l
extern _native void GET_PHYSICAL_SCREEN_RESOLUTION(float *x, float *y)l
extern _native void GET_SCREEN_RESOLUTION(float *x, float *y)l
extern _native void GET_TEXTURE_RESOLUTION(uint texture, float *x, float *y)l
extern _native void IMPROVE_LOW_PERFORMANCE_MISSION_PER_FRAME_FLAG(void)l
extern _native void LINE(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void PLAY_MOVIE(void)l
extern _native void RELEASE_MOVIE(void)l
extern _native void SET_CURRENT_MOVIE(const char* filename)l
extern _native void SET_HELP_MESSAGE_BOX_SIZE(float Unk773)l
extern _native void SET_HELP_MESSAGE_BOX_SIZE_F(float size)l
extern _native void SET_INSTANT_WIDESCREEN_BORDERS(bool set)l
extern _native void SET_MASK(float Unk774, float Unk775, float Unk776, float Unk777)l
extern _native void SET_SCREEN_FADE(int viewportid, int Unk778, int Unk779, bool Unk780, int r, int g, int b, int a, int Unk781, float Unk782, float Unk783)l
extern _native void SET_SPRITES_DRAW_BEFORE_FADE(bool set)l
extern _native void SET_USE_HIGHDOF(bool set)l
extern _native void SET_WIDESCREEN_BORDERS(bool set)l
extern _native void SET_WIDESCREEN_FORMAT(int wideformatid)l
extern _native void STOP_MOVIE(void)l
extern _native void TOGGLE_TOPLEVEL_SPRITE(bool toggle)l
extern _native void USE_MASK(bool use)l
int ADD_SPHERE(float x, float y, float z, float radius, uint Unk784)l
void REMOVE_SPHERE(uint sphere)l
#pragma endregion//}
#pragma region STATS//{
extern _native bool CAN_THE_STAT_HAVE_STRING(int stat)l
extern _native bool GET_STAT_FRONTEND_VISIBILITY(int stat)l
extern _native float GET_FLOAT_STAT(uint stat)l
extern _native int GET_STAT_FRONTEND_DISPLAY_TYPE(int stat)l
extern _native int GET_TOTAL_NUMBER_OF_STATS(void)l
extern _native uint GET_INT_STAT(uint stat)l
extern _native void DECREMENT_FLOAT_STAT(int stat, float val)l
extern _native void DECREMENT_INT_STAT(uint stat, uint amount)l
extern _native void INCREMENT_FLOAT_STAT(int stat, float val)l
extern _native void INCREMENT_FLOAT_STAT_NO_MESSAGE(uint stat, float value)l
extern _native void INCREMENT_INT_STAT(uint stat, uint value)l
extern _native void INCREMENT_INT_STAT_NO_MESSAGE(uint stat, uint value)l
extern _native void PLAYSTATS_CHEAT(int stat)l
extern _native void PLAYSTATS_FLOAT(int Unk785, float Unk786)l
extern _native void PLAYSTATS_INT(ScriptAny Unk787, int Unk788)l
extern _native void PLAYSTATS_INT_FLOAT(ScriptAny Unk789, int Unk790, float Unk791)l
extern _native void PLAYSTATS_INT_INT(ScriptAny Unk792, int Unk793, int Unk794)l
extern _native void PLAYSTATS_MISSION_CANCELLED(int Unk795)l
extern _native void PLAYSTATS_MISSION_FAILED(int Unk796)l
extern _native void PLAYSTATS_MISSION_PASSED(const char* str0)l
extern _native void PLAYSTATS_MISSION_STARTED(int Unk797)l
extern _native void REGISTER_FLOAT_STAT(int stat, float val)l
extern _native void REGISTER_INT_STAT(int stat, int val)l
extern _native void REGISTER_STRING_FOR_FRONTEND_STAT(int stat, const char* str)l
extern _native void SET_FLOAT_STAT(uint stat, float value)l
extern _native void SET_INT_STAT(uint stat, uint value)l
extern _native void SET_STAT_FRONTEND_ALWAYS_VISIBLE(bool set)l
extern _native void SET_STAT_FRONTEND_DISPLAY_TYPE(int stat, int type)l
extern _native void SET_STAT_FRONTEND_NEVER_VISIBLE(int stat)l
extern _native void SET_STAT_FRONTEND_VISIBILITY(int stat, bool set)l
extern _native void SET_STAT_FRONTEND_VISIBLE_AFTER_INCREMENTED(int stat)l
#pragma endregion//}
#pragma region BRAIN//{
extern _native bool IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE(void)l
extern _native void REGISTER_WORLD_POINT_SCRIPT_BRAIN(const char* ScriptName, float radius)l
extern _native void SWITCH_OBJECT_BRAINS(int brain, bool switchstate)l
#pragma endregion//}
#pragma region MOBILE//{
extern _native bool CAN_PHONE_BE_SEEN_ON_SCREEN(void)l
extern _native bool CODE_WANTS_MOBILE_PHONE_REMOVED(void)l
extern _native bool CODE_WANTS_MOBILE_PHONE_REMOVED_FOR_WEAPON_SWITCHING(void)l
extern _native bool GET_MOBILE_PHONE_TASK_SUB_TASK(Ped ped, int * Unk798)l
extern _native bool IS_MOBILE_PHONE_CALL_ONGOING(void)l
extern _native bool IS_MOBILE_PHONE_RADIO_ACTIVE(void)l
extern _native float GET_MOBILE_PHONE_SCALE(void)l
extern _native int GET_NUMBER_OF_WEB_PAGE_LINKS(int htmlviewport)l
extern _native void ADD_LINE_TO_MOBILE_PHONE_CALL(int id, const char* name, const char* text)l
extern _native void CREATE_MOBILE_PHONE(int Unk799)l
extern _native void DESTROY_MOBILE_PHONE(void)l
extern _native void GET_MOBILE_PHONE_RENDER_ID(uint *pRenderId)l
extern _native void NEW_MOBILE_PHONE_CALL(void)l
extern _native void PREVIEW_RINGTONE(int RingtoneId)l
extern _native void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(bool set)l
extern _native void SCRIPT_IS_USING_MOBILE_PHONE(bool set)l
extern _native void SET_MOBILE_PHONE_POSITION(float x, float y, float z)l
extern _native void SET_MOBILE_PHONE_RADIO_STATE(bool state)l
extern _native void SET_MOBILE_PHONE_ROTATION(float x, float y, float z)l
extern _native void SET_MOBILE_PHONE_SCALE(float scale)l
extern _native void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(bool set)l
extern _native void SET_MOBILE_RING_TYPE(int type)l
extern _native void SET_PHONE_HUD_ITEM(int id, const char* gxttext, int Unk800)l
extern _native void START_CUSTOM_MOBILE_PHONE_RINGING(int RingtoneId)l
extern _native void START_MOBILE_PHONE_CALL(Ped callfrom, const char* callfromvoice, Ped callto, const char* calltovoice, bool flag0, bool flag1)l
extern _native void START_MOBILE_PHONE_CALLING(void)l
extern _native void START_MOBILE_PHONE_RINGING(void)l
extern _native void START_PED_MOBILE_RINGING(Ped ped, int Unk801)l
extern _native void STOP_MOBILE_PHONE_RINGING(void)l
extern _native void STOP_PREVIEW_RINGTONE(void)l
#pragma endregion//}
#pragma region INTERNET//{
extern _native bool DOES_WEB_PAGE_EXIST(const char* webaddress)l
extern _native const char* GET_WEB_PAGE_LINK_HREF(int htmlviewport, int linkid)l
extern _native float GET_WEB_PAGE_HEIGHT(int htmlviewport)l
extern _native int CREATE_HTML_SCRIPT_OBJECT(const char* objname)l
extern _native int GET_WEB_PAGE_LINK_AT_POSN(int htmlviewport, float x, float y)l
extern _native void ADD_TO_HTML_SCRIPT_OBJECT(int htmlobj, const char* htmlcode)l
extern _native void DELETE_ALL_HTML_SCRIPT_OBJECTS(void)l
extern _native void DELETE_HTML_SCRIPT_OBJECT(int htmlobj)l
extern _native void GET_WEB_PAGE_LINK_POSN(int htmlviewport, int linkid, float *x, float *y)l
extern _native void LOAD_WEB_PAGE(int htmlviewport, const char* webaddress)l
extern _native void RELOAD_WEB_PAGE(int htmlviewport)l
extern _native void SET_WEB_PAGE_LINK_ACTIVE(int htmlviewport, int linkid, bool active)l
extern _native void SET_WEB_PAGE_SCROLL(int htmlviewport, float scroll)l
#pragma endregion//}
#pragma region TIME//{
extern _native void CLEAR_TIMECYCLE_MODIFIER(void)l
extern _native void FORCE_TIME_OF_DAY(uint hour, uint minute)l
extern _native void FORWARD_TO_TIME_OF_DAY(uint hour, uint minute)l
extern _native void FREEZE_ONSCREEN_TIMER(bool freeze)l
extern _native void GET_GAME_TIMER(uint *pTimer)l
extern _native void GET_TIME_OF_DAY(uint *hour, uint *minute)l
extern _native void SET_MOVIE_TIME(float time)l
extern _native void SET_TIMECYCLE_MODIFIER(const char* name)l
extern _native void SET_TIMER_BEEP_COUNTDOWN_TIME(int timerid, int beeptime)l
extern _native void SET_TIME_CYCLE_FAR_CLIP_DISABLED(bool set)l
extern _native void SET_TIME_OF_DAY(uint hour, uint minute)l
extern _native void SET_TIME_OF_NEXT_APPOINTMENT(int time)l
extern _native void SET_TIME_ONE_DAY_BACK(void)l
extern _native void SET_TIME_ONE_DAY_FORWARD(void)l
extern _native void SET_TIME_SCALE(float scale)l
#pragma endregion//}
#pragma region PATHFIND//{
extern _native bool GET_CLOSEST_CAR_NODE(float x, float y, float z, float *pResX, float *pResY, float *pResZ)l
extern _native bool GET_CLOSEST_CAR_NODE_FAVOUR_DIRECTION(int Unk802, float x, float y, float z, float *pX, float *pY, float *pZ, float *heading)l
extern _native bool GET_CLOSEST_CAR_NODE_WITH_HEADING(float x, float y, float z, float *pResX, float *pResY, float *pResZ, float *pHeading)l
extern _native bool GET_CLOSEST_MAJOR_CAR_NODE(float x, float y, float z, float *pResX, float *pResY, float *pResZ)l
extern _native bool GET_CLOSEST_ROAD(float x, float y, float z, float Unk803, int Unk804, vector3 * Unk805, vector3 * Unk806, float * Unk807, float * Unk808, float * Unk809)l
extern _native bool GET_NEXT_CLOSEST_CAR_NODE(float x, float y, float z, float *pX, float *pY, float *pZ)l
extern _native bool GET_NEXT_CLOSEST_CAR_NODE_FAVOUR_DIRECTION(float x, float y, float z, float *pX, float *pY, float *pZ, float *direction)l
extern _native bool GET_NEXT_CLOSEST_CAR_NODE_WITH_HEADING(float x, float y, float z, float *pX, float *pY, float *pZ, float *heading)l
extern _native bool GET_NEXT_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND(float x, float y, float z, float *pX, float *pY, float *pZ, float *heading)l
extern _native bool GET_NTH_CLOSEST_CAR_NODE(float x, float y, float z, int n, float *pX, float *pY, float *pZ)l
extern _native bool GET_NTH_CLOSEST_CAR_NODE_FAVOUR_DIRECTION(int Unk810, float x, float y, float z, int n, float *pX, float *pY, float *pZ, float *direction)l
extern _native bool GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING(float x, float y, float z, uint nodeNum, float *pResX, float *pResY, float *pResZ, float *pHeading)l
extern _native bool GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND(float x, float y, float z, uint nodeNum, uint areaId, float *pResX, float *pResY, float *pResZ, float *pHeading, uint *pUnknownMaybeAreaId)l
extern _native bool GET_NTH_CLOSEST_WATER_NODE_WITH_HEADING(float x, float y, float z, bool flag0, bool flag1, vector3* node, float *heading)l
extern _native bool GET_RANDOM_CAR_NODE(float x, float y, float z, float radius, bool flag0, bool flag1, bool flag2, float *pX, float *pY, float *pZ, float *heading)l
extern _native bool GET_RANDOM_CAR_NODE_INCLUDE_SWITCHED_OFF_NODES(float x, float y, float z, float radius, bool flag0, bool flag1, bool flag2, float *pX, float *pY, float *pZ, float *heading)l
extern _native bool GET_RANDOM_WATER_NODE(float x, float y, float z, float radius, bool flag0, bool flag1, bool flag2, bool flag3, float *pX, float *pY, float *pZ, float *heading)l
extern _native bool GET_SAFE_POSITION_FOR_CHAR(float x, float y, float z, bool unknownTrue, float *pSafeX, float *pSafeY, float *pSafeZ)l
extern _native float CALCULATE_TRAVEL_DISTANCE_BETWEEN_NODES(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native int ADD_NAVMESH_REQUIRED_REGION(float x, float y, float z)l
extern _native uint LOAD_ALL_PATH_NODES(bool value)l
extern _native void GENERATE_DIRECTIONS(float x, float y, float z, int *direction, vector3 * Unk811)l
extern _native void GET_RANDOM_CAR_BACK_BUMPER_IN_SPHERE(float x, float y, float z, float radius, int Unk812, int Unk813, Vehicle *veh)l
extern _native void GET_RANDOM_CAR_FRONT_BUMPER_IN_SPHERE_NO_SAVE(float x, float y, float z, float radius, bool flag0, bool flag1, int *handle, bool flag2)l
extern _native void GET_RANDOM_CAR_IN_SPHERE(float x, float y, float z, float radius, uint model, int Unk814, Vehicle *car)l
extern _native void GET_RANDOM_CAR_IN_SPHERE_NO_SAVE(float x, float y, float z, float radius, uint model, bool flag, Vehicle *car)l
extern _native void GET_RANDOM_CAR_MODEL_IN_MEMORY(bool MustIncludeSpecialModels, uint *pHash, int *pErrorId)l//-1 if error , 0 if no error
extern _native void GET_RANDOM_CAR_OF_TYPE_IN_ANGLED_AREA_NO_SAVE(float Unk815, float Unk816, float Unk817, float Unk818, float Unk819, uint type, Vehicle *car)l
extern _native void GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE(float x0, float y0, float x1, float y1, uint model, Vehicle *car)l
extern _native void GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE(float x, float y, float z, float sx, float sy, float sz, Ped *pPed)l
extern _native void LOAD_PATH_NODES_IN_AREA(float x, float y, float z, float radius)l
extern _native void MARK_ROAD_NODE_AS_DONT_WANDER(float x, float y, float z)l
extern _native void RELEASE_PATH_NODES(void)l
extern _native void SWITCH_PED_PATHS_OFF(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SWITCH_PED_PATHS_ON(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SWITCH_PED_ROADS_BACK_TO_ORIGINAL(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SWITCH_ROADS_BACK_TO_ORIGINAL(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SWITCH_ROADS_OFF(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void SWITCH_ROADS_ON(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native void UNMARK_ALL_ROAD_NODES_AS_DONT_WANDER(void)l
#pragma endregion//}
#pragma region CONTROLS//{
extern _native bool GET_ASCII_PRESSED(int key, int * Unk820)l
extern _native bool GET_BUFFERED_ASCII(int key, int * Unk821)l
extern _native bool GET_PAD_PITCH_ROLL(uint padIndex, float *pPitch, float *pRoll)l
extern _native bool HAS_RELOADED_WITH_MOTION_CONTROL(int ukn0, bool *ukn)l
extern _native bool IS_BUTTON_JUST_PRESSED(uint padIndex, uint button)l
extern _native bool IS_BUTTON_PRESSED(uint padIndex, uint button)l
extern _native bool IS_CONTROL_JUST_PRESSED(int Unk822, int controlid)l
extern _native bool IS_CONTROL_PRESSED(int Unk823, int controlid)l
extern _native bool IS_GAME_KEYBOARD_KEY_JUST_PRESSED(int key)l
extern _native bool IS_GAME_KEYBOARD_KEY_PRESSED(int key)l
extern _native bool IS_GAME_KEYBOARD_NAV_DOWN_PRESSED(bool Unk824)l
extern _native bool IS_GAME_KEYBOARD_NAV_LEFT_PRESSED(bool Unk825)l
extern _native bool IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED(bool Unk826)l
extern _native bool IS_GAME_KEYBOARD_NAV_UP_PRESSED(bool Unk827)l
extern _native bool IS_IN_CAR_FIRE_BUTTON_PRESSED(void)l
extern _native bool IS_KEYBOARD_KEY_JUST_PRESSED(int key)l
extern _native bool IS_KEYBOARD_KEY_PRESSED(int key)l
extern _native bool IS_MOUSE_BUTTON_JUST_PRESSED(int Unk828)l
extern _native bool IS_MOUSE_BUTTON_PRESSED(int Unk829)l
extern _native bool IS_MOUSE_USING_VERTICAL_INVERSION(void)l
extern _native bool IS_NUMLOCK_ENABLED(void)l
extern _native bool IS_PC_USING_JOYPAD(void)l
extern _native bool IS_USING_CONTROLLER(void)l
extern _native bool USING_STANDARD_CONTROLS(void)l
extern _native float GET_MOUSE_SENSITIVITY(void)l
extern _native int GET_ACCEPT_BUTTON(void)l
extern _native int GET_ASCII_JUST_PRESSED(int key, int Unk830)l
extern _native int GET_CONTROL_VALUE(int Unk831, int controlid)l
extern _native void CLEAR_SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED(void)l
extern _native void GET_KEYBOARD_MOVE_INPUT(int * Unk832, int * Unk833)l
extern _native void GET_MOUSE_INPUT(int *x, int *y)l
extern _native void GET_MOUSE_POSITION(int *x, int *y)l
extern _native void GET_MOUSE_WHEEL(int * Unk834)l
extern _native void GET_PAD_STATE(int Unk835, int Unk836, int * Unk837)l
extern _native void GET_POSITION_OF_ANALOGUE_STICKS(uint padIndex, int *pLeftX, int *pLeftY, int *pRightX, int *pRightY)l
extern _native void SHAKE_PAD(int Unk838, int Unk839, int Unk840)l
extern _native void SHAKE_PAD_IN_CUTSCENE(int Unk841, int Unk842, int Unk843)l
extern _native void SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED(void)l
#pragma endregion//}
#pragma region FIRE//{
extern _native bool DOES_SCRIPT_FIRE_EXIST(int fire)l
extern _native bool IS_EXPLOSION_IN_AREA(int expnum, float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native bool IS_EXPLOSION_IN_SPHERE(int expnum, float x, float y, float z, float radius)l
extern _native bool IS_SCRIPT_FIRE_EXTINGUISHED(FireId fire)l
extern _native FireId START_CAR_FIRE(Vehicle vehicle)l
extern _native FireId START_CHAR_FIRE(Ped ped)l
extern _native FireId START_SCRIPT_FIRE(float x, float y, float z, uint numGenerationsAllowed, uint strength)l
extern _native int GET_NUMBER_OF_FIRES_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native ScriptAny START_OBJECT_FIRE(Object obj)l
extern _native uint GET_NUMBER_OF_FIRES_IN_RANGE(float x, float y, float z, float radius)l
extern _native void ADD_EXPLOSION(float x, float y, float z, eExplosionType exptype, float radius, bool playsound, bool novisual, float camshake)l
extern _native void EXPLODE_CAR(Vehicle vehicle, bool unknownTrue, bool unknownFalse)l
extern _native void EXPLODE_CAR_IN_CUTSCENE(Vehicle car, bool explode)l
extern _native void EXPLODE_CAR_IN_CUTSCENE_SHAKE_AND_BIT(Vehicle car, bool flag0, bool flag1, bool flag2)l
extern _native void EXTINGUISH_CAR_FIRE(Vehicle vehicle)l
extern _native void EXTINGUISH_FIRE_AT_POINT(float x, float y, float z, float radius)l
extern _native void EXTINGUISH_OBJECT_FIRE(Object obj)l
extern _native void GET_SCRIPT_FIRE_COORDS(int fire, float *x, float *y, float *z)l
extern _native void REMOVE_SCRIPT_FIRE(FireId fire)l
extern _native void SET_MAX_FIRE_GENERATIONS(int max)l
#pragma endregion//}
#pragma region DECISIONEVENT//{
extern _native bool DOES_DECISION_MAKER_EXIST(DecisionMaker dm)l
extern _native void ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, uint eventid, uint responseid, float param1, float param2, float param3, float param4, uint unknown0_1, uint unknown1_1)l
//extern _native void ADD_COMBAT_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, uint eventid, uint responseid, float param1, float param2, float param3, float param4, uint unknown0_1, uint unknown1_1)l
extern _native void ADD_GROUP_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, uint eventid, uint responseid, float param1, float param2, float param3, float param4, uint unknown0_1, uint unknown1_1)l
//extern _native void CLEAR_CHAR_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, uint eventid)l
//extern _native void CLEAR_COMBAT_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, uint eventid)l
extern _native void CLEAR_GROUP_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, uint eventid)l
extern _native void COPY_CHAR_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void COPY_COMBAT_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void COPY_GROUP_CHAR_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void COPY_GROUP_COMBAT_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void COPY_SHARED_CHAR_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void COPY_SHARED_COMBAT_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void LOAD_CHAR_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void LOAD_COMBAT_DECISION_MAKER(uint type, DecisionMaker *pDM)l
//extern _native void LOAD_GROUP_DECISION_MAKER(uint type, DecisionMaker *pDM)l
extern _native void REMOVE_DECISION_MAKER(DecisionMaker dm)l
extern _native void SET_ADVANCED_BOOL_IN_DECISION_MAKER(int dm, int Unk844, int Unk845, int Unk846, bool Unk847)l
extern _native void SET_CHAR_DECISION_MAKER(Ped ped, DecisionMaker dm)l
extern _native void SET_CHAR_DECISION_MAKER_TO_DEFAULT(Ped ped)l
extern _native void SET_COMBAT_DECISION_MAKER(Ped ped, DecisionMaker dm)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_CAN_CHANGE_TARGET(DecisionMaker dm, bool value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_CAUTION(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_FIRE_RATE(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_LOW_HEALTH(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_MOVEMENT_STYLE(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_NAVIGATION_STYLE(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_RETREATING_BEHAVIOUR(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_STANDING_STYLE(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_TARGET_INJURED_REACTION(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_TARGET_LOSS_RESPONSE(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_TEAMWORK(DecisionMaker dm, uint value)l
extern _native void SET_DECISION_MAKER_ATTRIBUTE_WEAPON_ACCURACY(DecisionMaker dm, uint value)l
extern _native void SET_GROUP_CHAR_DECISION_MAKER(Group group, DecisionMaker dm)l
extern _native void SET_GROUP_COMBAT_DECISION_MAKER(Group group, DecisionMaker dm)l
//extern _native void SET_GROUP_DECISION_MAKER(Group group, DecisionMaker dm)l
extern _native void TASK_SET_CHAR_DECISION_MAKER(Ped ped, DecisionMaker dm)l
extern _native void TASK_SET_COMBAT_DECISION_MAKER(Ped ped, DecisionMaker dm)l
#pragma endregion//}
#pragma region ZONE//{
extern _native bool IS_CHAR_IN_ZONE(Ped ped, const char* zonename)l
extern _native const char* GET_NAME_OF_INFO_ZONE(float x, float y, float z)l
extern _native const char* GET_NAME_OF_ZONE(float x, float y, float z)l
extern _native int GET_CURRENT_POPULATION_ZONE_TYPE(void)l
extern _native int GET_CURRENT_ZONE_SCUMMINESS(void)l
extern _native void ACTIVATE_SCRIPT_POPULATION_ZONE(void)l
extern _native void DEACTIVATE_SCRIPT_POPULATION_ZONE(void)l
extern _native void FIND_PRIMARY_POPULATION_ZONE_GROUP(int *groupparam0, int *groupparam1)l
extern _native void SET_ZONE_POPULATION_TYPE(const char* zone, int poptype)l
extern _native void SET_ZONE_SCUMMINESS(const char* zone, int scumminess)l
extern _native void SPECIFY_SCRIPT_POPULATION_ZONE_AREA(int Unk848, int Unk849, int Unk850, int Unk851, int Unk852, int Unk853)l
extern _native void SPECIFY_SCRIPT_POPULATION_ZONE_GROUPS(int Unk854, int Unk855, int Unk856, int Unk857, int Unk858)l
extern _native void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_CARS(int num)l
extern _native void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_PARKED_CARS(int num)l
extern _native void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_PEDS(int num)l
extern _native void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_SCENARIO_PEDS(int num)l
#pragma endregion//}
#pragma region WATER//{
extern _native bool GET_WATER_HEIGHT(float x, float y, float z, float *pheight)l
extern _native bool GET_WATER_HEIGHT_NO_WAVES(float x, float y, float z, float *height)l
extern _native bool SYNCH_RECORDING_WITH_WATER(void)l
#pragma endregion//}
#pragma region MENU//{
extern _native int GET_MENU_ITEM_ACCEPTED(int menuid)l
extern _native int GET_MENU_ITEM_SELECTED(int menuid)l
extern _native void ACTIVATE_MENU_ITEM(int menuid, int item, bool activate)l
extern _native void CREATE_MENU(const char* gxtentry, ScriptAny Unk859, ScriptAny Unk860, ScriptAny Unk861, ScriptAny Unk862, ScriptAny Unk863, ScriptAny Unk864, ScriptAny Unk865, int *menuid)l
extern _native void DELETE_MENU(int menuid)l
extern _native void GET_MENU_POSITION(int menuid, float *x, float *y)l
extern _native void HIGHLIGHT_MENU_ITEM(int menuid, int item, bool highlight)l
extern _native void SET_MENU_COLUMN(int menuid, ScriptAny Unk866, ScriptAny Unk867, ScriptAny Unk868, ScriptAny Unk869, ScriptAny Unk870, ScriptAny Unk871, ScriptAny Unk872, ScriptAny Unk873, ScriptAny Unk874, ScriptAny Unk875, ScriptAny Unk876, ScriptAny Unk877, ScriptAny Unk878, ScriptAny Unk879)l
extern _native void SET_MENU_COLUMN_ORIENTATION(int menuid, int column, int orientation)l
extern _native void SET_MENU_COLUMN_WIDTH(int menuid, int column, float width)l
extern _native void SET_MENU_ITEM_WITH_2_NUMBERS(int menuid, int item, int Unk880, const char* gxtkey, int number0, int number1)l
extern _native void SET_MENU_ITEM_WITH_NUMBER(int menuid, int item, int Unk881, const char* gxtkey, int number)l
extern _native void SET_SELECTED_MENU_ITEM(int menuid, int item)l
#pragma endregion//}
#pragma region NETWORK//{
extern _native bool IS_NETWORK_PLAYER_ACTIVE(Player playerIndex)l
extern _native bool CAN_REGISTER_MISSION_OBJECT(void)l
extern _native bool CAN_REGISTER_MISSION_PED(void)l
extern _native bool CAN_REGISTER_MISSION_VEHICLE(void)l
extern _native bool DOES_GAME_CODE_WANT_TO_LEAVE_NETWORK_SESSION(void)l
extern _native bool DOES_OBJECT_EXIST_WITH_NETWORK_ID(int netid)l
extern _native bool DOES_PED_EXIST_WITH_NETWORK_ID(int netid)l
extern _native bool DOES_PLAYER_HAVE_CONTROL_OF_NETWORK_ID(int player, int id)l
extern _native bool DOES_VEHICLE_EXIST_WITH_NETWORK_ID(int nedid)l
extern _native bool GET_CELLPHONE_RANKED(void)l
extern _native bool GET_FILTER_MENU_ON(void)l
extern _native bool GET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER(void)l
extern _native bool GET_HOST_MATCH_ON(void)l
extern _native bool GET_NETWORK_JOIN_FAIL(void)l
extern _native bool GET_RETURN_TO_FILTER_MENU(void)l
extern _native bool HAS_CONTROL_OF_NETWORK_ID(int netid)l
extern _native bool HAS_GAMER_CHANGED_NETWORK_MODEL_SETTINGS(void)l
extern _native bool HAS_NETWORK_PLAYER_LEFT_GAME(Player playerIndex)l
extern _native bool IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(ScriptAny Unk882)l
extern _native bool IS_NETWORK_GAME_PENDING(void)l
extern _native bool IS_NETWORK_GAME_RUNNING(void)l
extern _native bool IS_NETWORK_SESSION(void)l
extern _native bool IS_OBJECT_REASSIGNMENT_IN_PROGRESS(void)l
extern _native bool IS_OUR_PLAYER_HIGHER_PRIORITY_FOR_CAR_GENERATION(Player playerIndex)l
extern _native bool IS_PARTY_MODE(void)l
extern _native bool IS_THIS_MACHINE_THE_SERVER(void)l
extern _native bool LOCAL_PLAYER_IS_READY_TO_START_PLAYING(void)l
extern _native bool NETWORK_ALL_PARTY_MEMBERS_PRESENT(void)l
extern _native bool NETWORK_AM_I_BLOCKED_BY_PLAYER(Player playerIndex)l
extern _native bool NETWORK_AM_I_MUTED_BY_PLAYER(Player playerIndex)l
extern _native bool NETWORK_CHANGE_GAME_MODE_PENDING(void)l
extern _native bool NETWORK_CHANGE_GAME_MODE_SUCCEEDED(void)l
extern _native bool NETWORK_CHECK_INVITE_ARRIVAL(void)l
extern _native bool NETWORK_DID_INVITE_FRIEND(const char* FRIENDNAME)l
extern _native bool NETWORK_END_SESSION_PENDING(void)l
extern _native bool NETWORK_FIND_GAME_PENDING(void)l
extern _native bool NETWORK_GET_LAN_SESSION(void)l
extern _native bool NETWORK_HAS_STRICT_NAT(void)l
extern _native bool NETWORK_HAVE_ACCEPTED_INVITE(void)l
extern _native bool NETWORK_HAVE_ONLINE_PRIVILEGES(void)l
extern _native bool NETWORK_HAVE_SUMMONS(void)l
extern _native bool NETWORK_HOST_GAME_E1(int Gamemode, int Ranked, int Slots, int Private, int Episode, int MaxTeams)l
extern _native bool NETWORK_HOST_GAME_PENDING(void)l
extern _native bool NETWORK_HOST_GAME_SUCCEEDED(void)l
extern _native bool NETWORK_HOST_RENDEZVOUS_E1(int Gamemode, int Slots, int Episode)l
extern _native bool NETWORK_IS_BEING_KICKED(void)l
extern _native bool NETWORK_IS_COMMON_EPISODE(int id)l
extern _native bool NETWORK_IS_FIND_RESULT_UPDATED(int ukn0)l
extern _native bool NETWORK_IS_FIND_RESULT_VALID(int Unk883)l
extern _native bool NETWORK_IS_FRIEND_IN_SAME_TITLE(uint friendid)l
extern _native bool NETWORK_IS_GAME_RANKED(void)l
extern _native bool NETWORK_IS_INVITEE_ONLINE(void)l
extern _native bool NETWORK_IS_NETWORK_AVAILABLE(void)l
extern _native bool NETWORK_IS_OPERATION_PENDING(void)l
extern _native bool NETWORK_IS_PLAYER_BLOCKED_BY_ME(Player playerIndex)l
extern _native bool NETWORK_IS_PLAYER_MUTED_BY_ME(Player playerIndex)l
extern _native bool NETWORK_IS_PLAYER_TALKING(Player playerIndex)l
extern _native bool NETWORK_IS_PLAYER_TYPING(Player playerIndex)l
extern _native bool NETWORK_IS_RENDEZVOUS(void)l
extern _native bool NETWORK_IS_RENDEZVOUS_HOST(void)l
extern _native bool NETWORK_IS_ROCKSTART_SESSION_ID_VALID(void)l
//extern _native bool NETWORK_IS_SESSION_ADVERTISED(void)l
extern _native bool NETWORK_IS_SESSION_ADVERTISE(void)l	//1.0.7 only
extern _native bool NETWORK_IS_SESSION_INVITABLE(void)l
extern _native bool NETWORK_IS_SESSION_STARTED(void)l
extern _native bool NETWORK_IS_TVT(void)l
extern _native bool NETWORK_JOIN_GAME_PENDING(void)l
extern _native bool NETWORK_JOIN_GAME_SUCCEEDED(void)l
extern _native bool NETWORK_JOIN_SUMMONS(void)l
extern _native bool NETWORK_LEAVE_GAME_PENDING(void)l
extern _native bool NETWORK_PLAYER_HAS_COMM_PRIVS(void)l
extern _native bool NETWORK_PLAYER_HAS_DIED_RECENTLY(Player playerIndex)l
extern _native bool NETWORK_PLAYER_HAS_HEADSET(ScriptAny Unk884)l
extern _native bool NETWORK_PLAYER_HAS_KEYBOARD(Player playerIndex)l
extern _native bool NETWORK_RESULT_MATCHES_SEARCH_CRITERIA(int result)l
extern _native bool NETWORK_RETURN_TO_RENDEZVOUS(void)l
extern _native bool NETWORK_RETURN_TO_RENDEZVOUS_PENDING(void)l
extern _native bool NETWORK_RETURN_TO_RENDEZVOUS_SUCCEEDED(void)l
extern _native bool NETWORK_START_SESSION_PENDING(void)l
extern _native bool NETWORK_START_SESSION_SUCCEEDED(void)l
extern _native bool NETWORK_STRING_VERIFY_PENDING(void)l
extern _native bool NETWORK_STRING_VERIFY_SUCCEEDED(void)l
extern _native bool PLAYER_WANTS_TO_JOIN_NETWORK_GAME(int Unk885)l
extern _native bool REQUEST_CONTROL_OF_NETWORK_ID(int netid)l
extern _native const char* NETWORK_GET_HOST_SERVER_NAME(int host)l
extern _native const char* NETWORK_GET_FRIEND_NAME(int id)l
extern _native const char* NETWORK_GET_NEXT_TEXT_CHAT(void)l
extern _native const char* NETWORK_GET_UNACCEPTED_INVITER_NAME(int Unk886)l
extern _native float GET_ONLINE_SCORE(int Unk887)l	//147, 148, or 149
extern _native int FIND_NETWORK_KILLER_OF_PLAYER(Player playerIndex)l
extern _native int GET_DESTROYER_OF_NETWORK_ID(Player playerIndex, int id)l
extern _native int GET_GAMER_NETWORK_SCORE(Player playerIndex, int Unk888, int Unk889)l
extern _native int GET_NO_OF_PLAYERS_IN_TEAM(int team)l
extern _native int GET_ONLINE_LAN(void)l
extern _native int GET_PLAYER_RANK_LEVEL_DURING_MP(Player playerIndex)l
extern _native int GET_PLAYER_TEAM(int Player)l
extern _native int HOW_LONG_HAS_NETWORK_PLAYER_BEEN_DEAD_FOR(Player playerIndex)l
extern _native int MP_GET_AMOUNT_OF_ANCHOR_POINTS(Ped ped, int id)l
extern _native int MP_GET_AMOUNT_OF_VARIATION_COMPONENT(Ped ped, int componentid)l
extern _native int MP_GET_PREFERENCE_VALUE(int prefid)l
extern _native int MP_GET_PROP_SETUP(Ped ped, int ukn0, int ukn1, int ukn2, int ukn3)l
extern _native int MP_GET_VARIATION_SETUP(Ped ped, int Unk890, int Unk891, int Unk892, int Unk893)l
extern _native int NETWORK_ACCEPT_INVITE(Player playerIndex)l
extern _native int NETWORK_GET_FRIEND_COUNT(void)l
extern _native int NETWORK_GET_GAME_MODE(void)l
extern _native int NETWORK_GET_HOST_AVERAGE_RANK(int host)l
extern _native int NETWORK_GET_HOST_LATENCY(int host)l
extern _native int NETWORK_GET_HOST_MATCH_PROGRESS(int host)l
extern _native int NETWORK_GET_NUMBER_OF_GAMES(void)l
extern _native int NETWORK_GET_NUM_OPEN_PUBLIC_SLOTS(void)l
extern _native int NETWORK_GET_NUM_PARTY_MEMBERS(void)l
extern _native int NETWORK_GET_NUM_PLAYERS_MET(void)l
extern _native int NETWORK_GET_NUM_UNACCEPTED_INVITES(void)l
extern _native int NETWORK_GET_NUM_UNFILLED_RESERVATIONS(void)l
extern _native int NETWORK_GET_PLAYER_ID_OF_NEXT_TEXT_CHAT(void)l
extern _native int NETWORK_GET_RENDEZVOUS_HOST_PLAYER_ID(void)l
extern _native int NETWORK_GET_UNACCEPTED_INVITE_EPISODE(ScriptAny Unk894)l
extern _native int NETWORK_SET_SERVER_NAME(const char* name)l
extern _native int STORE_DAMAGE_TRACKER_FOR_NETWORK_PLAYER(Player playerIndex, int ukn57, ScriptAny Unk895)l
extern _native ScriptAny GET_SERVER_ID(void)l
extern _native ScriptAny NETWORK_GET_SERVER_NAME(void)l
extern _native ScriptAny NETWORK_IS_FRIEND_ONLINE(ScriptAny Unk896)l
extern _native uint GET_HOST_ID(void)l
extern _native uint GET_LOCAL_GAMERLEVEL_FROM_PROFILESETTINGS(void)l
extern _native uint GET_NUMBER_OF_PLAYERS(void)l
extern _native uint GET_PLAYER_COLOUR(int Player)l
extern _native uint NETWORK_GET_MAX_PRIVATE_SLOTS(void)l
extern _native uint NETWORK_GET_MAX_SLOTS(void)l
extern _native void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(ScriptAny Unk897, ScriptAny Unk898)l
extern _native void ACTIVATE_NETWORK_SETTINGS_MENU(void)l
extern _native void ADD_GROUP_TO_NETWORK_RESTART_NODE_GROUP_LIST(int Unk899)l
extern _native void ADD_SPAWN_BLOCKING_AREA(ScriptAny Unk900, ScriptAny Unk901, ScriptAny Unk902, ScriptAny Unk903)l
extern _native void ADD_SPAWN_BLOCKING_DISC(ScriptAny Unk904, ScriptAny Unk905, ScriptAny Unk906, ScriptAny Unk907, ScriptAny Unk908)l
extern _native void CLEAR_NETWORK_RESTART_NODE_GROUP_LIST(void)l
extern _native void CLEAR_SCRIPT_ARRAY_FROM_SCRATCHPAD(int Unk909)l
extern _native void DEACTIVATE_NETWORK_SETTINGS_MENU(void)l
extern _native void DISPLAY_PLAYER_NAMES(ScriptAny Unk910)l
extern _native void FIND_NETWORK_RESTART_POINT(ScriptAny Unk911, ScriptAny Unk912, ScriptAny Unk913)l
extern _native void FLUSH_ALL_SPAWN_BLOCKING_AREAS(void)l
extern _native void GET_COORDINATES_FOR_NETWORK_RESTART_NODE(ScriptAny Unk914, ScriptAny Unk915, ScriptAny Unk916)l
extern _native void GET_NETWORK_ID_FROM_OBJECT(Object obj, int *netid)l
extern _native void GET_NETWORK_ID_FROM_PED(Ped ped, int *netid)l
extern _native void GET_NETWORK_ID_FROM_VEHICLE(Vehicle vehicle, int *netid)l
extern _native void GET_NETWORK_TIMER(int Unk917)l
extern _native void GET_OBJECT_FROM_NETWORK_ID(int netid, Object *obj)l
extern _native void GET_PED_FROM_NETWORK_ID(int netid, Ped *ped)l
extern _native void GET_PLAYER_RGB_COLOUR(int Player, int *r, int *g, int *b)l
extern _native void GET_SPAWN_COORDINATES_FOR_CAR_NODE(ScriptAny Unk918, ScriptAny Unk919, ScriptAny Unk920, ScriptAny Unk921, ScriptAny Unk922, ScriptAny Unk923)l
extern _native void GET_TEAM_RGB_COLOUR(int team, int *R, int *G, int *B)l
extern _native void GET_VEHICLE_FROM_NETWORK_ID(int netid, Vehicle *vehicle)l
extern _native void LAUNCH_LOCAL_PLAYER_IN_NETWORK_GAME(void)l
extern _native void MP_SET_PREFERENCE_VALUE(int prefid, int value)l
extern _native void NETWORK_ADVERTISE_SESSION(bool advertise)l
extern _native void NETWORK_CHANGE_EXTENDED_GAME_CONFIG(ScriptAny Unk924)l
extern _native void NETWORK_CLEAR_INVITE_ARRIVAL(void)l
extern _native void NETWORK_CLEAR_SUMMONS(void)l
extern _native void NETWORK_END_SESSION(void)l
extern _native void NETWORK_EXPAND_TO_32_PLAYERS(void)l
extern _native void NETWORK_FIND_GAME(int GameMode, int ukn0, int ukn1, int ukn2)l
extern _native void NETWORK_FINISH_EXTENDED_SEARCH(void)l
extern _native void NETWORK_GET_FIND_RESULT(ScriptAny Unk925, ScriptAny Unk926)l
extern _native void NETWORK_INVITE_FRIEND(const char* friendname, const char* ukn)l
extern _native void NETWORK_KICK_PLAYER(Player playerIndex, bool value)l
extern _native void NETWORK_LEAVE_GAME(void)l
extern _native void NETWORK_LIMIT_TO_16_PLAYERS(void)l
extern _native void NETWORK_SET_FRIENDLY_FIRE_OPTION(ScriptAny Unk927)l
extern _native void NETWORK_SET_HEALTH_RETICULE_OPTION(bool Unk928)l
extern _native void NETWORK_SET_LAN_SESSION(ScriptAny Unk929)l
extern _native void NETWORK_SET_LOCAL_PLAYER_IS_TYPING(Player playerIndex)l
extern _native void NETWORK_SET_MATCH_PROGRESS(float Unk930)l
extern _native bool NETWORK_SET_PLAYER_MUTED(int playerIndex, bool value)l
extern _native void NETWORK_SET_SCRIPT_LOBBY_STATE(ScriptAny Unk931)l
extern _native void NETWORK_SET_SESSION_INVITABLE(bool invitable)l
extern _native void NETWORK_SET_TALKER_FOCUS(ScriptAny Unk932)l
extern _native void NETWORK_SET_TALKER_PROXIMITY(ScriptAny Unk933)l
extern _native void NETWORK_SET_TEAM_ONLY_CHAT(bool Unk934)l
extern _native void NETWORK_SET_TEXT_CHAT_RECIPIENTS(ScriptAny Unk935)l
extern _native void NETWORK_SHOW_FRIEND_PROFILE_UI(ScriptAny Unk936)l
extern _native void NETWORK_SHOW_MET_PLAYER_FEEDBACK_UI(Player metPlayerIndex)l
extern _native void NETWORK_SHOW_PLAYER_FEEDBACK_UI(Player payerIndex)l
extern _native void NETWORK_SHOW_MET_PLAYER_PROFILE_UI(ScriptAny Unk937)l
extern _native void NETWORK_SHOW_PLAYER_PROFILE_UI(Player playerIndex)l
extern _native void NETWORK_START_EXTENDED_SEARCH(ScriptAny Unk938)l
extern _native void NETWORK_START_SESSION(void)l
extern _native void NETWORK_STORE_GAME_CONFIG(ScriptAny Unk939)l
extern _native void NETWORK_VERIFY_USER_STRING(ScriptAny Unk940)l
extern _native void OBFUSCATE_INT(int Unk941, int Unk942)l
extern _native void OBFUSCATE_INT_ARRAY(ScriptAny Unk943, ScriptAny Unk944)l
extern _native void REGISTER_CLIENT_BROADCAST_VARIABLES(ScriptAny Unk945, ScriptAny Unk946, ScriptAny Unk947)l
extern _native void REGISTER_HOST_BROADCAST_VARIABLES(ScriptAny Unk948, int ukn0, int ukn1)l
extern _native void REGISTER_KILL_IN_MULTIPLAYER_GAME(Player playerIndex, int id, uint ukn)l
extern _native void REGISTER_MULTIPLAYER_GAME_WIN(Player playerIndex, bool Unk949)l
extern _native void REGISTER_NETWORK_BEST_GAME_SCORES(Player playerIndex, int Unk950, int Unk951)l
extern _native void RESERVE_NETWORK_MISSION_OBJECTS_FOR_HOST(int count)l
extern _native void RESERVE_NETWORK_MISSION_PEDS_FOR_HOST(int Unk952)l
extern _native void RESERVE_NETWORK_MISSION_VEHICLES(int Unk953)l
extern _native void RESERVE_NETWORK_MISSION_VEHICLES_FOR_HOST(int Unk954)l
extern _native void RESTORE_SCRIPT_ARRAY_FROM_SCRATCHPAD(ScriptAny Unk955, ScriptAny Unk956, ScriptAny Unk957, ScriptAny Unk958)l
extern _native void RESURRECT_NETWORK_PLAYER(Player playerIndex, float x, float y, float z, int ukn0)l
extern _native void SAVE_SCRIPT_ARRAY_IN_SCRATCHPAD(ScriptAny Unk959, ScriptAny Unk960, ScriptAny Unk961, ScriptAny Unk962)l
extern _native void SET_ARMOUR_PICKUP_NETWORK_REGEN_TIME(uint timeMS)l
extern _native void SET_CAR_EXISTS_ON_ALL_MACHINES(Vehicle vehicle, bool exists)l
extern _native void SET_CELLPHONE_RANKED(bool toggle)l
extern _native void SET_FILTER_MENU_ON(bool toggle)l
extern _native void SET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER(ScriptAny Unk963)l
extern _native void SET_HEALTH_PICKUP_NETWORK_REGEN_TIME(uint timeMS)l
extern _native void SET_HOST_MATCH_ON(bool Unk964)l
extern _native void SET_IK_DISABLED_FOR_NETWORK_PLAYER(Player playerIndex, bool Unk965)l
extern _native void SET_IN_MP_TUTORIAL(bool set)l
extern _native void SET_IN_SPECTATOR_MODE(bool spectate)l
extern _native void SET_KILLSTREAK(void)l
extern _native void SET_LOBBY_MUTE_OVERRIDE(bool set)l
extern _native void SET_MSG_FOR_LOADING_SCREEN(const char* label)l
extern _native void SET_NETWORK_ID_CAN_MIGRATE(int netid, bool value)l
extern _native void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int netID, bool set)l
extern _native void SET_NETWORK_ID_STOP_CLONING(int id, bool Unk966)l
extern _native void SET_NETWORK_JOIN_FAIL(bool ukn0)l
extern _native void SET_NETWORK_PLAYER_AS_VIP(Player playerIndex, bool Unk967)l
extern _native void SET_NETWORK_VEHICLE_RESPOT_TIMER(int id, int ukn4000)l
extern _native void SET_OBJECT_EXISTS_ON_ALL_MACHINES(Object obj, bool exists)l
extern _native void SET_ONLINE_LAN(bool Unk968)l
extern _native void SET_OVERRIDE_NO_SPRINTING_ON_PHONE_IN_MULTIPLAYER(bool Unk969)l
extern _native void SET_PED_COMPONENTS_TO_NETWORK_PLAYERSETTINGS_MODEL(Ped ped)l
extern _native void SET_PED_EXISTS_ON_ALL_MACHINES(Ped ped, bool exists)l
extern _native void SET_PLAYERS_DROP_MONEY_IN_NETWORK_GAME(bool toggle)l
extern _native void SET_PLAYER_CONTROL_FOR_NETWORK(Player playerIndex, bool unknownTrue, bool unknownFalse)l
extern _native void SET_PLAYER_TEAM(int Player, int team)l
extern _native void SET_RETURN_TO_FILTER_MENU(bool Unk970)l
extern _native void SET_RICH_PRESENCE(ScriptAny Unk971, ScriptAny Unk972, ScriptAny Unk973, ScriptAny Unk974, ScriptAny Unk975)l
extern _native void SET_RICH_PRESENCE_TEMPLATEFILTER(void)l
extern _native void SET_RICH_PRESENCE_TEMPLATELOBBY(ScriptAny Unk976)l
extern _native void SET_RICH_PRESENCE_TEMPLATEMP1(ScriptAny Unk977, ScriptAny Unk978, ScriptAny Unk979, ScriptAny Unk980)l
extern _native void SET_RICH_PRESENCE_TEMPLATEMP2(ScriptAny Unk981)l
extern _native void SET_RICH_PRESENCE_TEMPLATEMP3(int Unk982, int Unk983)l
extern _native void SET_RICH_PRESENCE_TEMPLATEMP4(ScriptAny Unk984, ScriptAny Unk985)l
extern _native void SET_RICH_PRESENCE_TEMPLATEMP5(ScriptAny Unk986, ScriptAny Unk987, ScriptAny Unk988)l
extern _native void SET_RICH_PRESENCE_TEMPLATEMP6(ScriptAny Unk989, ScriptAny Unk990, ScriptAny Unk991)l
extern _native void SET_RICH_PRESENCE_TEMPLATEPARTY(void)l
extern _native void SET_RICH_PRESENCE_TEMPLATESP1(ScriptAny Unk992, ScriptAny Unk993, ScriptAny Unk994)l
extern _native void SET_RICH_PRESENCE_TEMPLATESP2(int Unk995)l
extern _native void SET_SERVER_ID(int id)l
extern _native void SET_START_FROM_FILTER_MENU(ScriptAny Unk996)l
extern _native void SET_SYNC_WEATHER_AND_GAME_TIME(bool Unk997)l
extern _native void SET_THIS_MACHINE_RUNNING_SERVER_SCRIPT(bool host)l
extern _native void SET_WEAPON_PICKUP_NETWORK_REGEN_TIME(int weaponType, uint timeMS)l
extern _native void SHUTDOWN_AND_LAUNCH_NETWORK_GAME(uint episode)l
extern _native void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME(void)l
extern _native void STORE_SCRIPT_VALUES_FOR_NETWORK_GAME(ScriptAny Unk998)l
extern _native void TELL_NET_PLAYER_TO_START_PLAYING(Player playerIndex, bool Unk999)l
extern _native void TERMINATE_ALL_SCRIPTS_FOR_NETWORK_GAME(void)l
extern _native void THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME(void)l
extern _native void TURN_OFF_RADIOHUD_IN_LOBBY(void)l
extern _native void UNOBFUSCATE_INT(int count, int *val)l
extern _native void UNOBFUSCATE_INT_ARRAY(ScriptAny Unk1000, ScriptAny Unk1001)l
extern _native void UPDATE_NETWORK_RELATIVE_SCORE(ScriptAny Unk1002, ScriptAny Unk1003, ScriptAny Unk1004)l
extern _native void UPDATE_NETWORK_STATISTICS(Player playerIndex, int ukn0, int ukn1, int ukn2)l
extern _native void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(bool Unk1005)l
extern _native ScriptAny CALCULATE_CHECKSUM(ScriptAny Unk1006, ScriptAny Unk1007)l
extern _native ScriptAny GET_CLOSEST_NETWORK_RESTART_NODE(ScriptAny Unk1008, ScriptAny Unk1009, ScriptAny Unk1010, ScriptAny Unk1011, ScriptAny Unk1012)l
extern _native ScriptAny GET_RANDOM_NETWORK_RESTART_NODE(ScriptAny Unk1013, ScriptAny Unk1014, ScriptAny Unk1015, ScriptAny Unk1016, ScriptAny Unk1017, ScriptAny Unk1018)l
extern _native ScriptAny GET_RANDOM_NETWORK_RESTART_NODE_USING_GROUP_LIST(ScriptAny Unk1019, ScriptAny Unk1020, ScriptAny Unk1021, ScriptAny Unk1022, ScriptAny Unk1023, ScriptAny Unk1024)l
extern _native ScriptAny GET_SORTED_NETWORK_RESTART_NODE(ScriptAny Unk1025, ScriptAny Unk1026, ScriptAny Unk1027, ScriptAny Unk1028, ScriptAny Unk1029, ScriptAny Unk1030, ScriptAny Unk1031, ScriptAny Unk1032, ScriptAny Unk1033)l
extern _native ScriptAny GET_SORTED_NETWORK_RESTART_NODE_USING_GROUP_LIST(ScriptAny Unk1034, ScriptAny Unk1035, ScriptAny Unk1036, ScriptAny Unk1037, ScriptAny Unk1038, ScriptAny Unk1039, ScriptAny Unk1040, ScriptAny Unk1041, ScriptAny Unk1042)l
extern _native ScriptAny GET_START_FROM_FILTER_MENU(void)l
extern _native ScriptAny IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(ScriptAny Unk1043, ScriptAny Unk1044, ScriptAny Unk1045, ScriptAny Unk1046)l
extern _native ScriptAny NETWORK_CHANGE_GAME_MODE(ScriptAny Unk1047, ScriptAny Unk1048, ScriptAny Unk1049, ScriptAny Unk1050)l
extern _native ScriptAny NETWORK_GET_MET_PLAYER_NAME(ScriptAny Unk1051)l
extern _native ScriptAny NETWORK_GET_UNACCEPTED_INVITE_GAME_MODE(ScriptAny Unk1052)l
extern _native ScriptAny NETWORK_JOIN_GAME(ScriptAny Unk1053)l
extern _native ScriptAny NETWORK_RESTORE_GAME_CONFIG(ScriptAny Unk1054)l
extern _native ScriptAny NETWORK_SEND_TEXT_CHAT(Player playerIndex, ScriptAny Unk1055)l
extern _native ScriptAny NETWORK_STORE_SINGLE_PLAYER_GAME(void)l
extern _native ScriptAny RESTORE_SCRIPT_VALUES_FOR_NETWORK_GAME(ScriptAny Unk1056)l
extern _native void GET_CAMERA_FROM_NETWORK_ID(int ned_id, int *cam)l
#pragma endregion//}
#pragma region DLC1//{
extern _native void FLUSH_ALL_PLAYER_RESPAWN_COORDS(void)l
extern _native void SEND_CLIENT_BROADCAST_VARIABLES_NOW(void)l
extern _native void SET_PLAYER_AS_DAMAGED_PLAYER(Player playerIndex, int Unk1057, bool Unk1058)l
#pragma endregion//}
#pragma region DLC2//{
extern _native bool IS_LCPD_DATA_VALID(void)l
extern _native void SET_DISPLAY_PLAYER_NAME_AND_ICON(Player playerIndex, bool set)l
extern _native void SET_NETWORK_PED_USING_PARACHUTE(Ped ped)l
extern _native void SET_ONLINE_SCORE(int Unk1059, ScriptAny Unk1060)l//147, 148, or 149
extern _native void STOP_SYNCING_SCRIPT_ANIMATIONS(bool Unk1061)l
#pragma endregion//}
#pragma region PTFX//{
extern _native bool TRIGGER_PTFX(const char* name, float x, float y, float z, float Unk1062, float Unk1063, float Unk1064, uint flags)l
extern _native bool TRIGGER_PTFX_ON_OBJ(const char* name, Object obj, float x, float y, float z, float Unk1065, float Unk1066, float Unk1067, uint flags)l
extern _native bool TRIGGER_PTFX_ON_OBJ_BONE(const char* name, Object obj, float x, float y, float z, float Unk1068, float Unk1069, float Unk1070, int objbone, uint flags)l
extern _native bool TRIGGER_PTFX_ON_PED(const char* name, Ped ped, float x, float y, float z, float Unk1071, float Unk1072, float Unk1073, uint flags)l
extern _native bool TRIGGER_PTFX_ON_PED_BONE(const char* name, Ped ped, float x, float y, float z, float Unk1074, float Unk1075, float Unk1076, int pedbone, uint flags)l
extern _native bool TRIGGER_PTFX_ON_VEH(const char* name, Vehicle veh, float x, float y, float z, float Unk1077, float Unk1078, float Unk1079, float Unk1080)l
extern _native uint START_PTFX(const char* name, float x, float y, float z, float yaw, float pitch, float roll, float scale)l
extern _native uint START_PTFX_ON_OBJ(const char* name, Object obj, float x, float y, float z, float yaw, float pitch, float roll, float scale)l
extern _native uint START_PTFX_ON_OBJ_BONE(const char* name, Object obj, float x, float y, float z, float yaw, float pitch, float roll, int objbone, float scale)l
extern _native uint START_PTFX_ON_PED(const char* name, Ped ped, float x, float y, float z, float yaw, float pitch, float roll, float scale)l
extern _native uint START_PTFX_ON_PED_BONE(const char* name, Ped ped, float x, float y, float z, float yaw, float pitch, float roll, int pedbone, float scale)l
extern _native uint START_PTFX_ON_VEH(const char* name, Vehicle veh, float x, float y, float z, float yaw, float pitch, float roll, float scale)l
extern _native void EVOLVE_PTFX(uint ptfx, const char* evolvetype, float val)l
extern _native void REMOVE_PROJTEX_FROM_OBJECT(Object obj)l
extern _native void REMOVE_PROJTEX_IN_RANGE(float x, float y, float z, float radius)l
extern _native void REMOVE_PTFX(uint ptfx)l
extern _native void REMOVE_PTFX_FROM_OBJECT(Object obj)l
extern _native void REMOVE_PTFX_FROM_PED(Ped ped)l
extern _native void REMOVE_PTFX_FROM_VEHICLE(Vehicle veh)l
extern _native void STOP_PTFX(uint ptfx)l
extern _native void UPDATE_PTFX_OFFSETS(uint ptfx, float x, float y, float z, float Unk1081, float Unk1082, float Unk1083)l
extern _native void UPDATE_PTFX_TINT(uint ptfx, float r, float g, float b, float a)l
#pragma endregion//}
#pragma region SYSTEM//{
extern _native bool ALLOW_ONE_TIME_ONLY_COMMANDS_TO_RUN(void)l
extern _native bool GET_TEXT_INPUT_ACTIVE(void)l
extern _native float CONVERT_METRES_TO_FEET(float metres)l
extern _native float COS(float value)l
extern _native float EXP(float Unk1084)l
extern _native float POW(float base, float power)l
extern _native float SIN(float value)l
extern _native float SQRT(float value)l
extern _native float TAN(float value)l
extern _native float TIMESTEPUNWARPED(void)l
extern _native float TO_FLOAT(uint value)l
extern _native float VDIST(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native float VDIST2(float x0, float y0, float z0, float x1, float y1, float z1)l
extern _native float VMAG(float x, float y, float z)l
extern _native float VMAG2(float x, float y, float z)l
extern _native int CEIL(float value)l
extern _native int FLOOR(float value)l
extern _native int ROUND(float Unk1085)l
extern _native int SHIFT_LEFT(int val, uint shifts)l
extern _native int SHIFT_RIGHT(int val, uint shifts)l
extern _native int TIMERC(void)l
extern _native uint START_NEW_SCRIPT(const char* scriptName, uint stacksize)l
extern _native uint START_NEW_SCRIPT_WITH_ARGS(const char* scriptname, void *params, int paramcount, uint stacksize)l
extern _native uint TIMERA(void)l
extern _native uint TIMERB(void)l
extern _native uint TIMESTEP(void)l
extern _native void GENERATE_RANDOM_FLOAT(float * Unk1086)l
extern _native void GENERATE_RANDOM_FLOAT_IN_RANGE(float min, float max, float *pValue)l
extern _native void GENERATE_RANDOM_INT(int * Unk1087)l
extern _native void GENERATE_RANDOM_INT_IN_RANGE(uint min, uint max, uint *pValue)l
extern _native void GET_CORRECTED_COLOUR(uint r, uint g, uint b, uint *pR, uint *pG, uint *pB)l
extern _native void SETTIMERA(uint value)l
extern _native void SETTIMERB(uint value)l
extern _native void SETTIMERC(int Unk1088)l
extern _native void WAIT(int timeMS)l
#pragma endregion//}
#pragma region PICKUP//{
extern _native bool DOES_PICKUP_EXIST(Pickup pickup)l
extern _native bool HAS_PICKUP_BEEN_COLLECTED(Pickup pickup)l
extern _native bool IS_ANY_PICKUP_AT_COORDS(float x, float y, float z)l
extern _native bool IS_MONEY_PICKUP_AT_COORDS(float x, float y, float z)l
extern _native int COUNT_PICKUPS_OF_TYPE(int type)l
extern _native void ADD_PICKUP_TO_INTERIOR_ROOM_BY_KEY(Object pickup, uint room_hash)l
extern _native void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Pickup pickup, const char* roomName)l
extern _native void CREATE_MONEY_PICKUP(float x, float y, float z, uint amount, bool unknownTrue, Pickup *pPickup)l
extern _native void CREATE_PICKUP(uint model, uint pickupType, float x, float y, float z, Pickup *pPickup, bool unknownFalse)l
extern _native void CREATE_PICKUP_ROTATE(uint model, uint pickupType, uint unknown, float x, float y, float z, float rX, float rY, float rZ, Pickup *pPickup)l
extern _native void CREATE_PICKUP_WITH_AMMO(uint model, uint pickupType, uint unknown, float x, float y, float z, Pickup *pPickup)l
extern _native void GET_PICKUP_COORDINATES(Pickup pickup, float *pX, float *pY, float *pZ)l
extern _native void GET_ROOM_KEY_FROM_PICKUP(int pickup, uint *hash)l
extern _native void GET_SAFE_PICKUP_COORDS(float x, float y, float z, float *pSafeX, float *pSafeY, float *pSafeZ)l
extern _native void REMOVE_ALL_PICKUPS_OF_TYPE(uint type)l
extern _native void REMOVE_PICKUP(Pickup pickup)l
extern _native void REMOVE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS(void)l
extern _native void RENDER_WEAPON_PICKUPS_BIGGER(bool value)l
extern _native void SET_ALL_PICKUPS_OF_TYPE_COLLECTABLE_BY_CAR(int pickuptype, bool set)l
extern _native void SET_DO_NOT_SPAWN_PARKED_CARS_ON_TOP(int pickup, bool set)l
extern _native void SET_PICKUPS_FIX_CARS(bool set)l
extern _native void SET_PICKUP_COLLECTABLE_BY_CAR(Object pickup, bool set)l
extern _native void SWITCH_ARROW_ABOVE_BLIPPED_PICKUPS(bool on)l
#pragma endregion//}
#pragma region WIDGET//{
extern _native const char* ADD_TEXT_WIDGET(ScriptAny Unk1089)l
extern _native int GET_CONTENTS_OF_TEXT_WIDGET(ScriptAny Unk1090)l
extern _native void ADD_TO_WIDGET_COMBO(ScriptAny Unk1091)l
extern _native void ADD_WIDGET_FLOAT_READ_ONLY(ScriptAny Unk1092, ScriptAny Unk1093)l
extern _native void ADD_WIDGET_FLOAT_SLIDER(ScriptAny Unk1094, ScriptAny Unk1095, ScriptAny Unk1096, ScriptAny Unk1097, ScriptAny Unk1098)l
extern _native void ADD_WIDGET_READ_ONLY(ScriptAny Unk1099, ScriptAny Unk1100)l
extern _native void ADD_WIDGET_SLIDER(ScriptAny Unk1101, ScriptAny Unk1102, ScriptAny Unk1103, ScriptAny Unk1104, ScriptAny Unk1105)l
extern _native void ADD_WIDGET_STRING(ScriptAny Unk1106)l
extern _native void ADD_WIDGET_TOGGLE(ScriptAny Unk1107, ScriptAny Unk1108)l
extern _native void CREATE_WIDGET_GROUP(ScriptAny Unk1109)l
extern _native void DELETE_WIDGET(ScriptAny Unk1110)l
extern _native void DELETE_WIDGET_GROUP(ScriptAny Unk1111)l
extern _native void END_WIDGET_GROUP(void)l
extern _native void FINISH_WIDGET_COMBO(ScriptAny Unk1112, ScriptAny Unk1113)l
extern _native bool DOES_WIDGET_GROUP_EXIST(ScriptAny Unk1114)l
extern _native void SET_CONTENTS_OF_TEXT_WIDGET(ScriptAny Unk1115, ScriptAny Unk1116)l
extern _native void START_NEW_WIDGET_COMBO(void)l
#pragma endregion//}
#pragma region DEBUG//{
extern _native void SET_CHAR_NAME_DEBUG(Ped ped, const char* debugName)l
extern _native void OPEN_DEBUG_FILE(void)l
extern _native void CLOSE_DEBUG_FILE(void)l
extern _native void DEBUG_OFF(void)l
extern _native void DRAW_DEBUG_SPHERE(float x, float y, float z, float radius)l
extern _native void SAVE_FLOAT_TO_DEBUG_FILE(ScriptAny Unk1117)l
extern _native void SAVE_INT_TO_DEBUG_FILE(ScriptAny Unk1118)l
extern _native void SAVE_NEWLINE_TO_DEBUG_FILE(void)l
extern _native void SAVE_STRING_TO_DEBUG_FILE(ScriptAny Unk1119)l
extern _native bool IS_DEBUG_CAMERA_ON(void)l
extern _native const char* GET_MODEL_NAME_FOR_DEBUG(uint model)l
extern _native void ENABLE_DEBUG_CAM(bool enable)l
extern _native void GET_DEBUG_CAM(int *cam)l
extern _native void INIT_DEBUG_WIDGETS(void)l
extern _native void SCRIPT_ASSERT(const char* text)l
extern _native void SET_DEBUG_TEXT_VISIBLE(bool Unk1120)l
extern _native int GET_CONSOLE_COMMAND_TOKEN(void)l
extern _native int GET_LATEST_CONSOLE_COMMAND(void)l
#pragma endregion//}
/*namespace DEPRECATED//{
ACTIVATE_VECTOR_MAP
ADD_AREA_TO_NETWORK_RESTART_NODE_GROUP_MAPPING
ADD_EXPLOSION_WITH_DIRECTION
ADD_NETWORK_RESTART
ADD_PED_QUEUE
ALLOW_NETWORK_POPULATION_GROUP_CYCLING
ATTACH_CAR_TO_OBJECT_PHYSICALLY
ATTACH_OBJECT_TO_OBJECT_PHYSICALLY
ATTACH_PED_TO_CAR2
ATTACH_PED_TO_WORLD_PHYSICALLY
BEGIN_PED_QUEUE_MEMBERSHIP_LIST
BREAKPOINT
CALCULATE_FURTHEST_NETWORK_RESTART_NODES
CAN_REGISTER_MISSION_ENTITIES
CAN_RENDER_RADIOHUD_SPRITE_IN_MOBILE_PHONE
CLAN_IS_PENDING
CLEAR_EVENT_PRECEDENCE
CLEAR_UP_TRIP_SKIP
CREATE_CAR_GENERATOR_WITH_PLATE
CREATE_DUMMY_CHAR
DEBUG_ON
DELETE_DUMMY_CHAR
DISABLE_DEBUG_CAM_AND_PLAYER_WARPING
DISPLAY_PLAYER_ICONS
DO_WEAPON_STUFF_AT_START_OF_2P_GAME
END_PED_QUEUE_MEMBERSHIP_LIST
FORCE_NET_PLAYER_INVISIBLE
GET_BLIP_INFO_ID_POSITION
GET_CAMERA_FROM_NETWORK_ID
GET_CHAR_ANIM_EVENT_TIME
GET_CHAR_AREA_VISIBLE
GET_CLOSEST_STRAIGHT_ROAD
GET_FURTHEST_NETWORK_RESTART_NODE
GET_INTERIOR_FROM_DUMMY_CHAR
GET_KILL_TRACKING_RESULTS
GET_LAST_TIME_NETWORK_ID_DAMAGED
GET_LCPD_COP_SCORE
GET_LCPD_CRIMINAL_SCORE
GET_LOCAL_GAMERLEVEL_FROM_PROFILESETTINGS
GET_MOBILE_PHONE_POSITION
GET_MOBILE_PHONE_ROTATION
GET_MODEL_NAME_OF_CAR_FOR_DEBUG_ONLY
GET_MOTION_CONTROLS_ENABLED
GET_MOTION_SENSOR_VALUES
GET_NAME_OF_SCRIPT_TO_AUTOMATICALLY_START
GET_NEEDED_PLAYER_CASH_FOR_LEVEL
GET_NETWORK_PLAYER_VIP
GET_NETWORK_RESTART_NODE_DEBUG
GET_NUM_CONSOLE_COMMAND_TOKENS
GET_NUM_KILLS_FOR_RANK_POINTS
GET_OVERRIDE_NO_SPRINTING_ON_PHONE_IN_MULTIPLAYER
GET_PAD_ORIENTATION
GET_PARKING_NODE_IN_AREA
GET_PED_AT_HEAD_OF_QUEUE
GET_PLAYER_LCPD_SCORE
GET_RANDOM_NETWORK_RESTART_NODE_EXCLUDING_GROUP
GET_RANDOM_NETWORK_RESTART_NODE_OF_GROUP
GET_REMOTE_CONTROLLED_CAR
GET_ROOM_NAME_FROM_CHAR_DEBUG
GET_SAFE_LOCAL_RESTART_COORDS
GET_SEQUENCE_PROGRESS_RECURSIVE
GET_SORTED_NETWORK_RESTART_NODE_EXCLUDING_GROUP
GET_SORTED_NETWORK_RESTART_NODE_OF_GROUP
GET_TEAM_COLOUR
GET_VEHICLE_CLASS
GIVE_PLAYER_HELMET
GIVE_REMOTE_CONTROLLED_MODEL_TO_PLAYER
HAS_NET_ID_BEEN_CLONED
HAS_PLAYER_RANK_BEEN_UPGRADED
IS_2PLAYER_GAME_GOING_ON
IS_ATTACHED_PLAYER_HEADING_ACHIEVED
IS_CAM_COLLIDING
IS_CAR_IN_ANGLED_AREA_2D
IS_CAR_IN_ANGLED_AREA_3D
IS_CAR_STOPPED_IN_AREA_2D
IS_CHAR_ON_PLAYER_MACHINE
IS_IN_MP_TUTORIAL
IS_NETWORK_CONNECTED
IS_NETWORK_PLAYER_VISIBLE
IS_OBJECT_IN_ANGLED_AREA_2D
IS_OBJECT_ON_PLAYER_MACHINE
IS_PLAYER_IN_SHORTCUT_TAXI
IS_VEHICLE_ON_PLAYER_MACHINE
LCPD_FIRST_TIME
LCPD_HAS_BEEN_CONFIGURED
MAKE_ROOM_IN_PLAYER_GANG_FOR_MISSION_PEDS
NETWORK_DISPLAY_HOST_GAMER_CARD
NETWORK_GET_FRIENDLY_FIRE_OPTION
NETWORK_GET_HEALTH_RETICULE_OPTION
NETWORK_GET_HOST_NAME
NETWORK_GET_TEAM_OPTION
NETWORK_HOST_GAME_CNC
NETWORK_JOIN_GAME_CNC
NETWORK_SET_LOCAL_PLAYER_CAN_TALK
PLAYER_HAS_FLASHING_STAR_AFTER_OFFENCE
PRINTFLOAT2
PRINTINT2
PRINT_MISSION_DESCRIPTION
READ_LOBBY_PREFERENCE
REGISTER_MOD
REGISTER_MODEL_FOR_RANK_POINTS
RELEASE_ENTITY_FROM_ROPE_FOR_OBJECT
RELEASE_TWO_PLAYER_DISTANCE
REMOVE_ALL_NETWORK_RESTART_POINTS
REMOVE_ALL_SCRIPT_FIRES
REMOVE_PED_QUEUE
REMOVE_RC_BUGGY
RENDER_LOADING_CLOCK
RENDER_RADIOHUD_SPRITE_IN_LOBBY
RENDER_RADIOHUD_SPRITE_IN_MOBILE_PHONE
RESERVE_NETWORK_MISSION_OBJECTS
RESERVE_NETWORK_MISSION_PEDS
RESET_ARMOUR_PICKUP_NETWORK_REGEN_TIME
RESET_HEALTH_PICKUP_NETWORK_REGEN_TIME
RESET_LATEST_CONSOLE_COMMAND
RESET_MONEY_PICKUP_NETWORK_REGEN_TIME
RESET_NETWORK_RESTART_NODE_GROUP_MAPPING
RESET_WEAPON_PICKUP_NETWORK_REGEN_TIME
SEND_HOST_BROADCAST_VARIABLES_NOW
SET_ALL_PEDS_SPAWNED_ARE_COPS
SET_ALTERNATIVE_HEAD_FOR_PED_QUEUE
SET_AREA_NAME
SET_CAR_STOP_CLONING
SET_CHAR_DEFENSIVE_AREA_ATTACHED_TO_CAR
SET_EVENT_PRECEDENCE
SET_HEADING_FOR_ATTACHED_PLAYER
SET_IGNORE_SERVER_UPDATE
SET_INVINCIBILITY_TIMER_DURATION
SET_LCPD_COP_SCORE
SET_LCPD_CRIMINAL_SCORE
SET_MONEY_PICKUP_NETWORK_REGEN_TIME
SET_MULTIPLAYER_BRIEF
SET_NETWORK_ID_STOP_CLONING_FOR_ENEMIES
SET_NETWORK_VISIBILITY
SET_OBJECT_STOP_CLONING
SET_PED_QUEUE_MEMBERSHIP_LIST
SET_PED_STOP_CLONING
SET_PLAYERS_CAN_BE_IN_SEPARATE_CARS
SET_PLAYER_COLOUR
SET_ROPE_HEIGHT_FOR_OBJECT
SET_SCRIPT_FIRE_AUDIO
SET_TEAM_COLOUR
SET_UP_TRIP_SKIP
SET_UP_TRIP_SKIP_AFTER_MISSION
SET_UP_TRIP_SKIP_FOR_VEHICLE_FINISHED_BY_SCRIPT
SET_UP_TRIP_SKIP_TO_BE_FINISHED_BY_SCRIPT
START_KILL_TRACKING
START_PROFILE_TIMER
STOP_KILL_TRACKING
STOP_PROFILE_TIMER
TAKE_REMOTE_CONTROL_OF_CAR
TAKE_SCREEN_SHOT
TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM_HDG_RATE
TASK_FOLLOW_PATROL_ROUTE
TASK_JETPACK
TASK_SAY
TASK_SIT_DOWN_PLAY_ANIM
TASK_SPACE_SHIP_GO_TO_COORD
TELEPORT_NETWORK_PLAYER
TURN_ON_RADIOHUD_IN_LOBBY
UPDATE_PLAYER_LCPD_SCORE
USE_DETONATOR
WAITUNPAUSED
WAITUNWARPED
WRITE_LOBBY_PREFERENCE
extern _native uint CREATE_USER_3D_MARKER(float x, float y, float z)l
extern _native void REMOVE_USER_3D_MARKER(uint marker)l
bool IS_PLAYER_IN_INFO_ZONE(int player, int zoneid)l
void CLEAR_ROOM_FOR_DUMMY_CHAR(Ped ped)l
void GET_CONSOLE_COMMAND
void GET_KEY_FOR_DUMMY_CHAR_IN_ROOM(Ped ped, int *room)l
void GET_ROPE_HEIGHT_FOR_OBJECT(Object obj, float *height)l
void GRAB_ENTITY_ON_ROPE_FOR_OBJECT(Object obj, int * Unk1121, int * Unk1122, int * Unk1123)l
void RESET_CONSOLE_COMMAND
void SET_ROOM_FOR_DUMMY_CHAR_BY_KEY(Ped dummy, int key)l
void SET_ROOM_FOR_DUMMY_CHAR_BY_NAME(Ped ped, const char* roomname)l
void SET_SPRITE_HDR_MULTIPLIER(float multiplier)l
void SET_UP_TRIP_SKIP_FOR_SPECIFIC_VEHICLE(float Unk1124, float Unk1125, float Unk1126, float Unk1127, Vehicle veh)l
}*/

#undef _native
#undef _native32
