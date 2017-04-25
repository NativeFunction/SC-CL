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
extern _native Ped get_player_ped(Player player)l
extern _native Entity get_player_ped_script_index(Player player)l
extern _native void set_player_model(Player player, Hash model)l
extern _native void change_player_ped(Player player, Ped ped, bool b2, bool b3)l
extern _native void get_player_rgb_colour(Player player, int* r, int* g, int* b)l
extern _native int get_number_of_players()l
extern _native int get_player_team(Player player)l
extern _native void set_player_team(Player player, int team)l
extern _native const char* get_player_name(Player player)l
extern _native float get_wanted_level_radius(Player player)l
extern _native vector3 get_player_wanted_centre_position(Player player)l
extern _native void set_player_wanted_centre_position(Player player, vector3* position, bool p2, bool p3)l
extern _native int get_wanted_level_threshold(int wantedLevel)l
extern _native void set_player_wanted_level(Player player, int wantedLevel, bool disableNoMission)l
extern _native void set_player_wanted_level_no_drop(Player player, int wantedLevel, bool p2)l
extern _native void set_player_wanted_level_now(Player player, bool p1)l
extern _native bool are_player_flashing_stars_about_to_drop(Player player)l
extern _native bool are_player_stars_greyed_out(Player player)l
extern _native void set_dispatch_cops_for_player(Player player, bool toggle)l
extern _native bool is_player_wanted_level_greater(Player player, int wantedLevel)l
extern _native void clear_player_wanted_level(Player player)l
extern _native bool is_player_dead(Player player)l
extern _native bool is_player_pressing_horn(Player player)l
extern _native void set_player_control(Player player, bool toggle, int possiblyFlags)l
extern _native int get_player_wanted_level(Player player)l
extern _native void set_max_wanted_level(int maxWantedLevel)l
extern _native void set_police_radar_blips(bool toggle)l
extern _native void set_police_ignore_player(Player player, bool toggle)l
extern _native bool is_player_playing(Player player)l
extern _native void set_everyone_ignore_player(Player player, bool toggle)l
extern _native void set_all_random_peds_flee(Player player, bool toggle)l
extern _native void set_all_random_peds_flee_this_frame(Player player)l
extern _native void unk_0x274631FE(Player player, bool toggle)l
extern _native void unk_0x02DF7AF4(Player player)l
extern _native void set_ignore_low_priority_shocking_events(Player player, bool toggle)l
extern _native void set_wanted_level_multiplier(float multiplier)l
extern _native void set_wanted_level_difficulty(Player player, float difficulty)l
extern _native void reset_wanted_level_difficulty(Player player)l
extern _native void start_firing_amnesty(int duration)l
extern _native void report_crime(Player player, int crimeType, int wantedLvlThresh)l
extern _native32(0x59B5C2A2) void _switch_crime_type(Player player, int p1)l
extern _native void unk_0x6B34A160(Player player)l
extern _native any unk_0xB9FB142F(Player player)l
extern _native any unk_0x85725848(Player player)l
extern _native void unk_0x3A7E5FB6(Player player)l
extern _native void unk_0xD15C4B1C(Player player)l
extern _native void unk_0xBF6993C7(float p0)l
extern _native void unk_0x47CAB814()l
extern _native bool can_player_start_mission(Player player)l
extern _native bool is_player_ready_for_cutscene(Player player)l
extern _native bool is_player_targetting_entity(Player player, Entity entity)l
extern _native bool get_player_target_entity(Player player, Entity* entity)l
extern _native bool is_player_free_aiming(Player player)l
extern _native bool is_player_free_aiming_at_entity(Player player, Entity entity)l
extern _native bool get_entity_player_is_free_aiming_at(Player player, Entity* entity)l
extern _native void set_player_lockon_range_override(Player player, float range)l
extern _native void set_player_can_do_drive_by(Player player, bool toggle)l
extern _native void set_player_can_be_hassled_by_gangs(Player player, bool toggle)l
extern _native any set_player_can_use_cover(Player player, bool toggle)l
extern _native int get_max_wanted_level()l
extern _native bool is_player_targetting_anything(Player player)l
extern _native void set_player_sprint(Player player, bool toggle)l
extern _native void reset_player_stamina(Player player)l
extern _native void restore_player_stamina(Player player, float p1)l
extern _native float get_player_sprint_stamina_remaining(Player player)l
extern _native float get_player_sprint_time_remaining(Player player)l
extern _native float get_player_underwater_time_remaining(Player player)l
extern _native int get_player_group(Player player)l
extern _native int get_player_max_armour(Player player)l
extern _native bool is_player_control_on(Player player)l
extern _native bool is_player_script_control_on(Player player)l
extern _native bool is_player_climbing(Player player)l
extern _native bool is_player_being_arrested(Player player, bool atArresting)l
extern _native void reset_player_arrest_state(Player player)l
extern _native Vehicle get_players_last_vehicle()l
extern _native Player get_player_index()l
extern _native Player int_to_playerindex(int value)l
extern _native int int_to_participantindex(int value)l
extern _native int get_time_since_player_hit_vehicle(Player player)l
extern _native int get_time_since_player_hit_ped(Player player)l
extern _native int get_time_since_player_drove_on_pavement(Player player)l
extern _native int get_time_since_player_drove_against_traffic(Player player)l
extern _native bool is_player_free_for_ambient_task(Player player)l
extern _native Player player_id()l
extern _native Ped player_ped_id()l
extern _native int network_player_id_to_int()l
extern _native bool has_force_cleanup_occurred(int cleanupFlags)l
extern _native void force_cleanup(int cleanupFlags)l
extern _native void force_cleanup_for_all_threads_with_this_name(const char* name, int cleanupFlags)l
extern _native void force_cleanup_for_thread_with_this_id(int id, int cleanupFlags)l
extern _native int get_cause_of_most_recent_force_cleanup()l
extern _native void set_player_may_only_enter_this_vehicle(Player player, Vehicle vehicle)l
extern _native void set_player_may_not_enter_any_vehicle(Player player)l
extern _native bool give_achievement_to_player(int achievement)l
extern _native bool has_achievement_been_passed(int achievement)l
extern _native bool is_player_online()l
extern _native bool is_player_logging_in_np()l
extern _native void display_system_signin_ui(bool unk)l
extern _native bool is_system_ui_being_displayed()l
extern _native void set_player_invincible(Player player, bool toggle)l
extern _native bool get_player_invincible(Player player)l
extern _native void unk_0x00563E0D(Player player, bool p1)l
extern _native any remove_player_helmet(Player player, bool p2)l
extern _native void give_player_ragdoll_control(Player player, bool toggle)l
extern _native void set_player_lockon(Player player, bool toggle)l
extern _native void set_player_targeting_mode(int targetMode)l
extern _native void clear_player_has_damaged_at_least_one_ped(Player player)l
extern _native bool has_player_damaged_at_least_one_ped(Player player)l
extern _native void clear_player_has_damaged_at_least_one_non_animal_ped(Player player)l
extern _native bool has_player_damaged_at_least_one_non_animal_ped(Player player)l
extern _native void set_air_drag_multiplier_for_players_vehicle(Player player, float multiplier)l
extern _native void set_swim_multiplier_for_player(Player player, float multiplier)l
extern _native void set_run_sprint_multiplier_for_player(Player player, float multiplier)l
extern _native int get_time_since_last_arrest()l
extern _native int get_time_since_last_death()l
extern _native void assisted_movement_close_route()l
extern _native void assisted_movement_flush_route()l
extern _native void set_player_forced_aim(Player player, bool toggle)l
extern _native void set_player_forced_zoom(Player player, bool toggle)l
extern _native void set_player_force_skip_aim_intro(Player player, bool toggle)l
extern _native void disable_player_firing(Player player, bool toggle)l
extern _native void set_disable_ambient_melee_move(Player player, bool toggle)l
extern _native void set_player_max_armour(Player player, int value)l
extern _native void special_ability_deactivate(Player player)l
extern _native void special_ability_deactivate_fast(Player player)l
extern _native void special_ability_reset(Player player)l
extern _native void unk_0x4136829A(Player player)l
extern _native void special_ability_charge_small(Player player, bool p1, bool p2)l
extern _native void special_ability_charge_medium(Player player, bool p1, bool p2)l
extern _native void special_ability_charge_large(Player player, bool p1, bool p2)l
extern _native void special_ability_charge_continuous(Player player, Ped p2)l
extern _native void special_ability_charge_absolute(Player player, int p1, bool p2)l
extern _native void special_ability_charge_normalized(Player player, float normalizedValue, bool p2)l
extern _native void special_ability_fill_meter(Player player, bool p1)l
extern _native void special_ability_deplete_meter(Player player, bool p1)l
extern _native void special_ability_lock(Hash playerModel)l
extern _native void special_ability_unlock(Hash playerModel)l
extern _native bool is_special_ability_unlocked(Hash playerModel)l
extern _native bool is_special_ability_active(Player player)l
extern _native bool is_special_ability_meter_full(Player player)l
extern _native void enable_special_ability(Player player, bool toggle)l
extern _native bool is_special_ability_enabled(Player player)l
extern _native void set_special_ability_multiplier(float multiplier)l
extern _native void unk_0x5D0FE25B(Player player)l
extern _native bool unk_0x46E7E31D(Player player)l
extern _native bool unk_0x1E359CC8(Player player, int p1)l
extern _native bool unk_0x8CB53C9F(Player player, float p1)l
extern _native void start_player_teleport(Player player, vector3 vec, float heading, bool p5, bool p6, bool p7)l
extern _native void stop_player_teleport()l
extern _native bool is_player_teleport_active()l
extern _native float get_player_current_stealth_noise(Player player)l
extern _native void set_player_health_recharge_multiplier(Player player, float regenRate)l
extern _native void set_player_weapon_damage_modifier(Player player, float damageAmount)l
extern _native void set_player_weapon_defense_modifier(Player player, float modifier)l
extern _native void set_player_melee_weapon_defense_modifier(Player player, float modifier)l
extern _native void set_player_vehicle_damage_modifier(Player player, float damageAmount)l
extern _native void set_player_vehicle_defense_modifier(Player player, float modifier)l
extern _native void set_player_parachute_tint_index(Player player, int tintIndex)l
extern _native void get_player_parachute_tint_index(Player player, int* tintIndex)l
extern _native void set_player_reserve_parachute_tint_index(Player player, int index)l
extern _native void get_player_reserve_parachute_tint_index(Player player, int* index)l
extern _native void set_player_parachute_pack_tint_index(Player player, int tintIndex)l
extern _native void get_player_parachute_pack_tint_index(Player player, int* tintIndex)l
extern _native void set_player_has_reserve_parachute(Player player)l
extern _native bool get_player_has_reserve_parachute(Player player)l
extern _native void set_player_can_leave_parachute_smoke_trail(Player player, bool enabled)l
extern _native void set_player_parachute_smoke_trail_color(Player player, RGB colour)l
extern _native void get_player_parachute_smoke_trail_color(Player player, int* r, int* g, int* b)l
extern _native void set_player_reset_flag_prefer_rear_seats(Player player, int flags)l
extern _native void set_player_noise_multiplier(Player player, float multiplier)l
extern _native void set_player_sneaking_noise_multiplier(Player player, float multiplier)l
extern _native bool can_ped_hear_player(Player player, Ped ped)l
extern _native void simulate_player_input_gait(Player player, float amount, int gaitType, float speed, bool p4, bool p5)l
extern _native void reset_player_input_gait(Player player)l
extern _native void set_auto_give_parachute_when_enter_plane(Player player, bool toggle)l
extern _native void unk_0xA25D767E(Player player, bool p1)l
extern _native void set_player_stealth_perception_modifier(Player player, float value)l
extern _native bool unk_0x1D371529(any p0)l
extern _native void unk_0xE30A64DC(Player player)l
extern _native void set_player_simulate_aiming(Player player, bool toggle)l
extern _native void set_player_cloth_pin_frames(Player player, bool toggle)l
extern _native void set_player_cloth_package_index(int index)l
extern _native void set_player_cloth_lock_counter(int value)l
extern _native void player_attach_virtual_bound(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7)l
extern _native void player_detach_virtual_bound()l
extern _native bool has_player_been_spotted_in_stolen_vehicle(Player player)l
extern _native bool unk_0x013B4F72(Player player)l
extern _native bool unk_0x9DF75B2A(Player player, int p1, bool p2)l
extern _native bool is_player_riding_train(Player player)l
extern _native bool has_player_left_the_world(Player player)l
extern _native void unk_0xAD8383FA(Player player, bool p1)l
extern _native void set_player_parachute_variation_override(Player player, int p1, any p2, any p3, bool p4)l
extern _native void clear_player_parachute_variation_override(Player player)l
extern _native void set_player_parachute_model_override(Player player, Hash model)l
extern _native void clear_player_parachute_model_override(Player player)l
extern _native void set_player_parachute_pack_model_override(Player player, Hash model)l
extern _native void clear_player_parachute_pack_model_override(Player player)l
extern _native void disable_player_vehicle_rewards(Player player)l
extern _native void unk_0x2849D4B2(bool p0)l
#pragma endregion //}
#pragma region ENTITY //{
extern _native bool does_entity_exist(Entity entity)l
extern _native bool does_entity_belong_to_this_script(Entity entity, bool p1)l
extern _native bool does_entity_have_drawable(Entity entity)l
extern _native bool does_entity_have_physics(Entity entity)l
extern _native bool has_entity_anim_finished(Entity entity, const char* animDict, const char* animName, int p3)l
extern _native bool has_entity_been_damaged_by_any_object(Entity entity)l
extern _native bool has_entity_been_damaged_by_any_ped(Entity entity)l
extern _native bool has_entity_been_damaged_by_any_vehicle(Entity entity)l
extern _native bool has_entity_been_damaged_by_entity(Entity entity1, Entity entity2, bool p2)l
extern _native bool has_entity_clear_los_to_entity(Entity entity1, Entity entity2, int traceType)l
extern _native bool has_entity_clear_los_to_entity_in_front(Entity entity1, Entity entity2)l
extern _native bool has_entity_collided_with_anything(Entity entity)l
extern _native Hash get_last_material_hit_by_entity(Entity entity)l
extern _native vector3 get_collision_normal_of_last_hit_for_entity(Entity entity)l
extern _native void force_entity_ai_and_animation_update(Entity entity)l
extern _native float get_entity_anim_current_time(Entity entity, const char* animDict, const char* animName)l
extern _native float get_entity_anim_total_time(Entity entity, const char* animDict, const char* animName)l
extern _native float get_anim_duration(const char* animDict, const char* animName)l
extern _native Entity get_entity_attached_to(Entity entity)l
extern _native vector3 get_entity_coords(Entity entity, bool alive)l
extern _native vector3 get_entity_forward_vector(Entity entity)l
extern _native float get_entity_forward_x(Entity entity)l
extern _native float get_entity_forward_y(Entity entity)l
extern _native float get_entity_heading(Entity entity)l
extern _native int get_entity_health(Entity entity)l
extern _native int get_entity_max_health(Entity entity)l
extern _native void set_entity_max_health(Entity entity, int value)l
extern _native float get_entity_height(Entity entity, vector3 vec, bool atTop, bool inWorldCoords)l
extern _native float get_entity_height_above_ground(Entity entity)l
extern _native void get_entity_matrix(Entity entity, vector3* rightVector, vector3* forwardVector, vector3* upVector, vector3* position)l
extern _native Hash get_entity_model(Entity entity)l
extern _native vector3 get_offset_from_entity_given_world_coords(Entity entity, vector3 pos)l
extern _native vector3 get_offset_from_entity_in_world_coords(Entity entity, vector3 offset)l
extern _native float get_entity_pitch(Entity entity)l
extern _native void get_entity_quaternion(Entity entity, float* x, float* y, float* z, float* w)l
extern _native float get_entity_roll(Entity entity)l
extern _native vector3 get_entity_rotation(Entity entity, int rotationOrder)l
extern _native vector3 get_entity_rotation_velocity(Entity entity)l
extern _native const char* get_entity_script(Entity entity, ScrHandle* script)l
extern _native float get_entity_speed(Entity entity)l
extern _native vector3 get_entity_speed_vector(Entity entity, bool relative)l
extern _native float get_entity_upright_value(Entity entity)l
extern _native vector3 get_entity_velocity(Entity entity)l
extern _native Object get_object_index_from_entity_index(Entity entity)l
extern _native Ped get_ped_index_from_entity_index(Entity entity)l
extern _native Vehicle get_vehicle_index_from_entity_index(Entity entity)l
extern _native vector3 get_world_position_of_entity_bone(Entity entity, int boneIndex)l
extern _native Player get_nearest_player_to_entity(Entity entity)l
extern _native Player get_nearest_player_to_entity_on_team(Entity entity, int team)l
extern _native int get_entity_type(Entity entity)l
extern _native int get_entity_population_type(Entity entity)l
extern _native bool is_an_entity(int handle)l
extern _native bool is_entity_a_ped(Entity entity)l
extern _native bool is_entity_a_mission_entity(Entity entity)l
extern _native bool is_entity_a_vehicle(Entity entity)l
extern _native bool is_entity_an_object(Entity entity)l
extern _native bool is_entity_at_coord(Entity entity, vector3 Pos, vector3 Size, bool p7, bool p8, int p9)l
extern _native bool is_entity_at_entity(Entity entity1, Entity entity2, vector3 Size, bool p5, bool p6, int p7)l
extern _native bool is_entity_attached(Entity entity)l
extern _native bool is_entity_attached_to_any_object(Entity entity)l
extern _native bool is_entity_attached_to_any_ped(Entity entity)l
extern _native bool is_entity_attached_to_any_vehicle(Entity entity)l
extern _native bool is_entity_attached_to_entity(Entity from, Entity to)l
extern _native bool is_entity_dead(Entity entity)l
extern _native bool is_entity_in_air(Entity entity)l
extern _native bool is_entity_in_angled_area(Entity entity, vector3 origin, vector3 edge, float angle, bool p8, bool p9, any p10)l
extern _native bool is_entity_in_area(Entity entity, vector3 vec_1, vector3 vec_2, bool p7, bool p8, any p9)l
extern _native bool is_entity_in_zone(Entity entity, const char* zone)l
extern _native bool is_entity_in_water(Entity entity)l
extern _native float get_entity_submerged_level(Entity entity)l
extern _native void unk_0x40C84A74(Entity entity, bool p1)l
extern _native bool is_entity_on_screen(Entity entity)l
extern _native bool is_entity_playing_anim(Entity entity, const char* animDict, const char* animName, int p4)l
extern _native bool is_entity_static(Entity entity)l
extern _native bool is_entity_touching_entity(Entity entity, Entity targetEntity)l
extern _native bool is_entity_touching_model(Entity entity, Hash modelHash)l
extern _native bool is_entity_upright(Entity entity, float angle)l
extern _native bool is_entity_upsidedown(Entity entity)l
extern _native bool is_entity_visible(Entity entity)l
extern _native bool is_entity_visible_to_script(Entity entity)l
extern _native bool is_entity_occluded(Entity entity)l
extern _native bool would_entity_be_occluded(Hash entityModelHash, vector3 vec, bool p4)l
extern _native bool is_entity_waiting_for_world_collision(Entity entity)l
extern _native void apply_force_to_entity_center_of_mass(Entity entity, int forceType, vector3 vec, bool p5, bool isRel, bool highForce, bool p8)l
extern _native void apply_force_to_entity(Entity entity, int forceType, vector3 vec, vector3 Rot, int p8, bool isRel, bool p10, bool highForce, bool p12, bool p13)l
extern _native void attach_entity_to_entity(Entity entity1, Entity entity2, int boneIndex, vector3 Pos, vector3 Rot, bool p9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot)l
extern _native void attach_entity_to_entity_physically(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, vector3 Pos1, vector3 Pos2, vector3 Rot, float breakForce, bool fixedRot, bool p15, bool collision, bool p17, int p18)l
extern _native void process_entity_attachments(Entity entity)l
extern _native int get_entity_bone_index_by_name(Entity entity, const char* boneName)l
extern _native any clear_entity_last_damage_entity(Entity entity)l
extern _native void delete_entity(Entity* entity)l
extern _native void detach_entity(Entity entity, bool p1, bool collision)l
extern _native void freeze_entity_position(Entity entity, bool toggle)l
extern _native32(0xD3850671) void _set_entity_register(Entity entity, bool toggle)l
extern _native bool play_entity_anim(Entity entity, const char* animName, const char* animDict, float p3, bool loop, bool stayInAnim, bool p6, float delta, any bitset)l
extern _native bool play_synchronized_entity_anim(Entity entity, int syncedScene, const char* animation, const char* propName, float p4, float p5, any p6, float p7)l
extern _native bool play_synchronized_map_entity_anim(float p0, float p1, float p2, float p3, any p4, any p5, any* p6, any* p7, float p8, float p9, any p10, float p11)l
extern _native bool stop_synchronized_map_entity_anim(float p0, float p1, float p2, float p3, any p4, float p5)l
extern _native any stop_entity_anim(Entity entity, const char* animation, const char* animGroup, float p3)l
extern _native bool stop_synchronized_entity_anim(Entity entity, float p1, bool p2)l
extern _native bool has_anim_event_fired(Entity entity, Hash actionHash)l
extern _native bool find_anim_event_phase(const char* animDictionary, const char* animName, const char* p2, any* p3, any* p4)l
extern _native void set_entity_anim_current_time(Entity entity, const char* animDictionary, const char* animName, float time)l
extern _native void set_entity_anim_speed(Entity entity, const char* animDictionary, const char* animName, float speedMultiplier)l
extern _native void set_entity_as_mission_entity(Entity entity, bool p1, bool p2)l
extern _native void set_entity_as_no_longer_needed(Entity* entity)l
extern _native void set_ped_as_no_longer_needed(Ped* ped)l
extern _native void set_vehicle_as_no_longer_needed(Vehicle* vehicle)l
extern _native void set_object_as_no_longer_needed(Object* object)l
extern _native void set_entity_can_be_damaged(Entity entity, bool toggle)l
extern _native void set_entity_can_be_damaged_by_relationship_group(Entity entity, bool bCanBeDamaged, int relGroup)l
extern _native void set_entity_can_be_targeted_without_los(Entity entity, bool toggle)l
extern _native void set_entity_collision(Entity entity, bool toggle, bool keepPhysics)l
extern _native bool get_entity_collison_disabled(Entity entity)l
extern _native void set_entity_coords(Entity entity, vector3 Pos, bool xAxis, bool yAxis, bool zAxis, bool clearArea)l
extern _native void set_entity_coords_no_offset(Entity entity, vector3 Pos, bool xAxis, bool yAxis, bool zAxis)l
extern _native void set_entity_dynamic(Entity entity, bool toggle)l
extern _native void set_entity_heading(Entity entity, float heading)l
extern _native void set_entity_health(Entity entity, int health)l
extern _native void set_entity_invincible(Entity entity, bool toggle)l
extern _native void set_entity_is_target_priority(Entity entity, bool p1, float p2)l
extern _native void set_entity_lights(Entity entity, bool toggle)l
extern _native void set_entity_load_collision_flag(Entity entity, bool toggle)l
extern _native bool has_collision_loaded_around_entity(Entity entity)l
extern _native void set_entity_max_speed(Entity entity, float speed)l
extern _native void set_entity_only_damaged_by_player(Entity entity, bool toggle)l
extern _native void set_entity_only_damaged_by_relationship_group(Entity entity, bool p1, any p2)l
extern _native void set_entity_proofs(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool p6, bool p7, bool drownProof)l
extern _native void set_entity_quaternion(Entity entity, quaternion quat)l
extern _native void set_entity_records_collisions(Entity entity, bool toggle)l
extern _native void set_entity_rotation(Entity entity, vector3 rot, int rotationOrder, bool p5)l
extern _native void set_entity_visible(Entity entity, bool toggle, bool unk)l
extern _native void set_entity_velocity(Entity entity, vector3 vec)l
extern _native void set_entity_has_gravity(Entity entity, bool toggle)l
extern _native void set_entity_lod_dist(Entity entity, int value)l
extern _native int get_entity_lod_dist(Entity entity)l
extern _native void set_entity_alpha(Entity entity, int alphaLevel, bool skin)l
extern _native int get_entity_alpha(Entity entity)l
extern _native any reset_entity_alpha(Entity entity)l
extern _native void set_entity_always_prerender(Entity entity, bool toggle)l
extern _native void set_entity_render_scorched(Entity entity, bool toggle)l
extern _native void set_entity_trafficlight_override(Entity entity, int state)l
extern _native void create_model_swap(vector3 vec, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native void remove_model_swap(vector3 vec, float radius, Hash originalModel, Hash newModel, bool p6)l
extern _native void create_model_hide(vector3 vec, float radius, Hash model, bool p5)l
extern _native void create_model_hide_excluding_script_objects(vector3 vec, float radius, Hash model, bool p5)l
extern _native void remove_model_hide(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void create_forced_object(vector3 vec, any p3, Hash modelHash, bool p5)l
extern _native void remove_forced_object(any p0, any p1, any p2, any p3, any p4)l
extern _native void set_entity_no_collision_entity(Entity entity1, Entity entity2, bool unknown)l
extern _native void set_entity_motion_blur(Entity entity, bool toggle)l
extern _native void unk_0x44767B31(Entity entity, bool p1)l
extern _native void unk_0xE224A6A5(Entity entity, bool p1)l
#pragma endregion //}
#pragma region PED //{
extern _native Ped create_ped(int pedType, Hash modelHash, vector3 vec, float heading, bool isNetwork, bool p7)l
extern _native void delete_ped(Ped* ped)l
extern _native Ped clone_ped(Ped ped, float heading, bool isNetwork, bool p3)l
extern _native void clone_ped_to_target(Ped ped, Ped targetPed)l
extern _native bool is_ped_in_vehicle(Ped ped, Vehicle vehicle, bool atGetIn)l
extern _native bool is_ped_in_model(Ped ped, Hash modelHash)l
extern _native bool is_ped_in_any_vehicle(Ped ped, bool atGetIn)l
extern _native bool is_cop_ped_in_area_3d(vector3 vec_1, vector3 vec_2)l
extern _native bool is_ped_injured(Ped ped)l
extern _native bool is_ped_hurt(Ped ped)l
extern _native bool is_ped_fatally_injured(Ped ped)l
extern _native bool is_ped_dead_or_dying(Ped ped, bool p1)l
extern _native bool is_conversation_ped_dead(Ped ped)l
extern _native bool is_ped_aiming_from_cover(Ped ped)l
extern _native bool is_ped_reloading(Ped ped)l
extern _native bool is_ped_a_player(Ped ped)l
extern _native Ped create_ped_inside_vehicle(Vehicle vehicle, int pedType, Hash modelHash, int seat, bool isNetwork, bool p5)l
extern _native void set_ped_desired_heading(Ped ped, float heading)l
extern _native32(0x290421BE) void _freeze_ped_camera_rotation(Ped ped)l
extern _native bool is_ped_facing_ped(Ped ped, Ped otherPed, float angle)l
extern _native bool is_ped_in_melee_combat(Ped ped)l
extern _native bool is_ped_stopped(Ped ped)l
extern _native bool is_ped_shooting_in_area(Ped ped, vector3 vec_1, vector3 vec_2, bool p7, bool p8)l
extern _native bool is_any_ped_shooting_in_area(vector3 vec_1, vector3 vec_2, bool p6, bool p7)l
extern _native bool is_ped_shooting(Ped ped)l
extern _native any set_ped_accuracy(Ped ped, int accuracy)l
extern _native int get_ped_accuracy(Ped ped)l
extern _native bool is_ped_model(Ped ped, Hash modelHash)l
extern _native void explode_ped_head(Ped ped, Hash weaponHash)l
extern _native void remove_ped_elegantly(Ped* ped)l
extern _native void add_armour_to_ped(Ped ped, int amount)l
extern _native void set_ped_armour(Ped ped, int amount)l
extern _native void set_ped_into_vehicle(Ped ped, Vehicle vehicle, int seatIndex)l
extern _native void set_ped_allow_vehicles_override(Ped ped, bool toggle)l
extern _native bool can_create_random_ped(bool unk)l
extern _native Ped create_random_ped(vector3 pos)l
extern _native Ped create_random_ped_as_driver(Vehicle vehicle, bool returnHandle)l
extern _native bool can_create_random_driver()l
extern _native bool can_create_random_bike_rider()l
extern _native void set_ped_move_anims_blend_out(Ped ped)l
extern _native void set_ped_can_be_dragged_out(Ped ped, bool toggle)l
extern _native void unk_0x6CD58238(bool toggle)l
extern _native bool is_ped_male(Ped ped)l
extern _native bool is_ped_human(Ped ped)l
extern _native Vehicle get_vehicle_ped_is_in(Ped ped, bool lastVehicle)l
extern _native void reset_ped_last_vehicle(Ped ped)l
extern _native void set_ped_density_multiplier_this_frame(float multiplier)l
extern _native void set_scenario_ped_density_multiplier_this_frame(float p0, float p1)l
extern _native void unk_0xB48C0C04()l
extern _native void set_scripted_conversion_coord_this_frame(vector3 vec)l
extern _native void set_ped_non_creation_area(vector3 vec_1, vector3 vec_2)l
extern _native void clear_ped_non_creation_area()l
extern _native void unk_0x8C555ADD()l
extern _native bool is_ped_on_mount(Ped ped)l
extern _native Ped get_mount(Ped ped)l
extern _native bool is_ped_on_vehicle(Ped ped)l
extern _native bool is_ped_on_specific_vehicle(Ped ped, Vehicle vehicle)l
extern _native void set_ped_money(Ped ped, int amount)l
extern _native int get_ped_money(Ped ped)l
extern _native void unk_0xD41C9AED(float p0, any p1)l
extern _native void unk_0x30B98369(bool p0)l
extern _native void unk_0x02A080C8(bool p0)l
extern _native void set_ped_suffers_critical_hits(Ped ped, bool toggle)l
extern _native void unk_0x1572022A(Ped ped, bool toggle)l
extern _native bool is_ped_sitting_in_vehicle(Ped ped, Vehicle vehicle)l
extern _native bool is_ped_sitting_in_any_vehicle(Ped ped)l
extern _native bool is_ped_on_foot(Ped ped)l
extern _native bool is_ped_on_any_bike(Ped ped)l
extern _native bool is_ped_planting_bomb(Ped ped)l
extern _native vector3 get_dead_ped_pickup_coords(Ped ped, float p1, float p2)l
extern _native bool is_ped_in_any_boat(Ped ped)l
extern _native bool is_ped_in_any_sub(Ped ped)l
extern _native bool is_ped_in_any_heli(Ped ped)l
extern _native bool is_ped_in_any_plane(Ped ped)l
extern _native bool is_ped_in_flying_vehicle(Ped ped)l
extern _native void set_ped_dies_in_water(Ped ped, bool toggle)l
extern _native void set_ped_dies_in_sinking_vehicle(Ped ped, bool toggle)l
extern _native int get_ped_armour(Ped ped)l
extern _native void set_ped_stay_in_vehicle_when_jacked(Ped ped, bool toggle)l
extern _native void set_ped_can_be_shot_in_vehicle(Ped ped, bool toggle)l
extern _native bool get_ped_last_damage_bone(Ped ped, int* outBone)l
extern _native void clear_ped_last_damage_bone(Ped ped)l
extern _native void set_ai_weapon_damage_modifier(float value)l
extern _native void reset_ai_weapon_damage_modifier()l
extern _native void set_ai_melee_weapon_damage_modifier(float modifier)l
extern _native void reset_ai_melee_weapon_damage_modifier()l
extern _native void unk_0xCC9D7F1A(any p0, bool p1)l
extern _native void set_ped_can_be_targetted(Ped ped, bool toggle)l
extern _native void set_ped_can_be_targetted_by_team(Ped ped, int team, bool toggle)l
extern _native void set_ped_can_be_targetted_by_player(Ped ped, Player player, bool toggle)l
extern _native void unk_0x7DA12905(any p0, bool p1)l
extern _native void set_time_exclusive_display_texture(any p0, bool p1)l
extern _native bool is_ped_in_any_police_vehicle(Ped ped)l
extern _native void force_ped_to_open_parachute(Ped ped)l
extern _native bool is_ped_in_parachute_free_fall(Ped ped)l
extern _native bool is_ped_falling(Ped ped)l
extern _native bool is_ped_jumping(Ped ped)l
extern _native bool is_ped_climbing(Ped ped)l
extern _native bool is_ped_vaulting(Ped ped)l
extern _native bool is_ped_diving(Ped ped)l
extern _native bool is_ped_jumping_out_of_vehicle(Ped ped)l
extern _native int get_ped_parachute_state(Ped ped)l
extern _native int get_ped_parachute_landing_type(Ped ped)l
extern _native void set_ped_parachute_tint_index(Ped ped, int tintIndex)l
extern _native void get_ped_parachute_tint_index(Ped ped, int* outTintIndex)l
extern _native void set_ped_reserve_parachute_tint_index(Ped ped, any p1)l
extern _native void set_ped_ducking(Ped ped, bool toggle)l
extern _native bool is_ped_ducking(Ped ped)l
extern _native bool is_ped_in_any_taxi(Ped ped)l
extern _native void set_ped_id_range(Ped ped, float value)l
extern _native void unk_0x9A2180FF(Ped ped, bool p1)l
extern _native void unk_0xF30658D2(Ped ped, float unk)l
extern _native void unk_0x43709044(any p0)l
extern _native void set_ped_seeing_range(Ped ped, float value)l
extern _native void set_ped_hearing_range(Ped ped, float value)l
extern _native void set_ped_visual_field_min_angle(Ped ped, float value)l
extern _native void set_ped_visual_field_max_angle(Ped ped, float value)l
extern _native void set_ped_visual_field_min_elevation_angle(Ped ped, float angle)l
extern _native void set_ped_visual_field_max_elevation_angle(Ped ped, float angle)l
extern _native void set_ped_visual_field_peripheral_range(Ped ped, float range)l
extern _native void set_ped_visual_field_center_angle(Ped ped, float angle)l
extern _native void set_ped_stealth_movement(Ped ped, bool p1, const char* action)l
extern _native bool get_ped_stealth_movement(Ped ped)l
extern _native int create_group(int unused)l
extern _native void set_ped_as_group_leader(Ped ped, int groupId)l
extern _native void set_ped_as_group_member(Ped ped, int groupId)l
extern _native void set_ped_can_teleport_to_group_leader(Ped pedHandle, int groupHandle, bool toggle)l
extern _native void remove_group(int groupId)l
extern _native void remove_ped_from_group(Ped ped)l
extern _native bool is_ped_group_member(Ped ped, int groupId)l
extern _native bool is_ped_hanging_on_to_vehicle(Ped ped)l
extern _native void set_group_separation_range(int groupHandle, float separationRange)l
extern _native void set_ped_min_ground_time_for_stungun(Ped ped, int ms)l
extern _native bool is_ped_prone(Ped ped)l
extern _native bool is_ped_in_combat(Ped ped, Ped target)l
extern _native bool can_ped_in_combat_see_target(Ped ped, Ped target)l
extern _native bool is_ped_doing_driveby(Ped ped)l
extern _native bool is_ped_jacking(Ped ped)l
extern _native bool is_ped_being_jacked(Ped ped)l
extern _native bool is_ped_being_stunned(Ped ped, int p1)l
extern _native Ped get_peds_jacker(Ped ped)l
extern _native Ped get_jack_target(Ped ped)l
extern _native bool is_ped_fleeing(Ped ped)l
extern _native bool is_ped_in_cover(Ped ped, bool p1)l
extern _native bool is_ped_in_cover_facing_left(Ped ped)l
extern _native bool is_ped_going_into_cover(Ped ped)l
extern _native any set_ped_pinned_down(Ped ped, bool pinned, int i)l
extern _native int get_seat_ped_is_trying_to_enter(Ped ped)l
extern _native Vehicle get_vehicle_ped_is_trying_to_enter(Ped ped)l
extern _native Entity get_ped_source_of_death(Ped ped)l
extern _native Hash get_ped_cause_of_death(Ped ped)l
extern _native int unk_0xEF0B78E6(any p0)l
extern _native any unk_0xFB18CB19(any p0, float p1, float p2, float p3, float p4)l
extern _native void set_ped_relationship_group_default_hash(Ped ped, Hash hash)l
extern _native void set_ped_relationship_group_hash(Ped ped, Hash hash)l
extern _native void set_relationship_between_groups(int relationship, Hash group1, Hash group2)l
extern _native void clear_relationship_between_groups(int relationship, Hash group1, Hash group2)l
extern _native any add_relationship_group(const char* name, Hash* groupHash)l
extern _native void remove_relationship_group(Hash groupHash)l
extern _native int get_relationship_between_peds(Ped ped1, Ped ped2)l
extern _native Hash get_ped_relationship_group_default_hash(Ped ped)l
extern _native Hash get_ped_relationship_group_hash(Ped ped)l
extern _native int get_relationship_between_groups(Hash group1, Hash group2)l
extern _native void set_ped_can_be_targeted_without_los(Ped ped, bool toggle)l
extern _native void set_ped_to_inform_respected_friends(Ped ped, float radius, int maxFriends)l
extern _native bool is_ped_responding_to_event(Ped ped, any event)l
extern _native void set_ped_firing_pattern(Ped ped, Hash patternHash)l
extern _native void set_ped_shoot_rate(Ped ped, int shootRate)l
extern _native void set_combat_float(Ped ped, int combatType, float p2)l
extern _native float get_combat_float(Ped ped, int p1)l
extern _native void get_group_size(int groupID, any* unknown, int* sizeInMembers)l
extern _native bool does_group_exist(int groupId)l
extern _native int get_ped_group_index(Ped ped)l
extern _native bool is_ped_in_group(Ped ped)l
extern _native Player get_player_ped_is_following(Ped ped)l
extern _native void set_group_formation(int groupId, int formationType)l
extern _native void set_group_formation_spacing(int groupId, float p1, float p2, float p3)l
extern _native void reset_group_formation_default_spacing(int groupHandle)l
extern _native Vehicle get_vehicle_ped_is_using(Ped ped)l
extern _native Vehicle set_exclusive_phone_relationships(Ped ped)l
extern _native void set_ped_gravity(Ped ped, bool toggle)l
extern _native void apply_damage_to_ped(Ped ped, int damageAmount, bool p2)l
extern _native void set_ped_allowed_to_duck(Ped ped, bool toggle)l
extern _native void set_ped_never_leaves_group(Ped ped, bool toggle)l
extern _native int get_ped_type(Ped ped)l
extern _native void set_ped_as_cop(Ped ped, bool toggle)l
extern _native void set_ped_max_health(Ped ped, int value)l
extern _native int get_ped_max_health(Ped ped)l
extern _native void set_ped_max_time_in_water(Ped ped, float value)l
extern _native void set_ped_max_time_underwater(Ped ped, float value)l
extern _native void unk_0x373CC405(Ped ped, float p1)l
extern _native void set_ped_can_be_knocked_off_vehicle(Ped ped, int state)l
extern _native bool can_knock_ped_off_vehicle(Ped ped)l
extern _native void knock_ped_off_vehicle(Ped ped)l
extern _native void set_ped_coords_no_gang(Ped ped, vector3 pos)l
extern _native Ped get_ped_as_group_member(int groupID, int memberNumber)l
extern _native void set_ped_keep_task(Ped ped, bool toggle)l
extern _native void unk_0x397F06E3(Ped ped, bool p1)l
extern _native bool is_ped_swimming(Ped ped)l
extern _native bool is_ped_swimming_under_water(Ped ped)l
extern _native void set_ped_coords_keep_vehicle(Ped ped, vector3 pos)l
extern _native void set_ped_dies_in_vehicle(Ped ped, bool toggle)l
extern _native void set_create_random_cops(bool toggle)l
extern _native void set_create_random_cops_not_on_scenarios(bool toggle)l
extern _native void set_create_random_cops_on_scenarios(bool toggle)l
extern _native bool can_create_random_cops()l
extern _native void set_ped_as_enemy(Ped ped, bool toggle)l
extern _native void set_ped_can_smash_glass(Ped ped, bool p1, bool p2)l
extern _native bool is_ped_in_any_train(Ped ped)l
extern _native bool is_ped_getting_into_a_vehicle(Ped ped)l
extern _native bool is_ped_trying_to_enter_a_locked_vehicle(Ped ped)l
extern _native void set_enable_handcuffs(Ped ped, bool toggle)l
extern _native void set_enable_bound_ankles(Ped ped, bool toggle)l
extern _native void set_enable_scuba(Ped ped, bool toggle)l
extern _native void set_can_attack_friendly(Ped ped, bool toggle, bool p2)l
extern _native int get_ped_alertness(Ped ped)l
extern _native void set_ped_alertness(Ped ped, int value)l
extern _native void set_ped_get_out_upside_down_vehicle(Ped ped, bool toggle)l
extern _native void set_ped_movement_clipset(Ped ped, const char* clipSet, float p2)l
extern _native void reset_ped_movement_clipset(Ped ped, float p1)l
extern _native void set_ped_strafe_clipset(Ped ped, const char* clipSet)l
extern _native void reset_ped_strafe_clipset(Ped ped)l
extern _native void set_ped_weapon_movement_clipset(Ped ped, const char* clipSet)l
extern _native void reset_ped_weapon_movement_clipset(Ped ped)l
extern _native void set_ped_drive_by_clipset_override(Ped ped, const char* clipset)l
extern _native void clear_ped_drive_by_clipset_override(Ped ped)l
extern _native void set_ped_in_vehicle_context(Ped ped, Hash context)l
extern _native void reset_ped_in_vehicle_context(Ped ped)l
extern _native bool is_scripted_scenario_ped_using_conditional_anim(Ped ped, const char* animDict, const char* anim)l
extern _native void set_ped_alternate_walk_anim(Ped ped, const char* animDict, const char* animName, float p3, bool p4)l
extern _native void clear_ped_alternate_walk_anim(Ped ped, float p1)l
extern _native void set_ped_alternate_movement_anim(Ped ped, int stance, const char* animDictionary, const char* animationName, float p4, bool p5)l
extern _native void clear_ped_alternate_movement_anim(Ped ped, int stance, float p2)l
extern _native void set_ped_gesture_group(Ped ped, const char* animGroupGesture)l
extern _native vector3 get_anim_initial_offset_position(const char* animDict, const char* animName, vector3 vec, vector3 Rot, float p8, int p9)l
extern _native vector3 get_anim_initial_offset_rotation(const char* animDict, const char* animName, vector3 vec, vector3 Rot, float p8, int p9)l
extern _native int get_ped_drawable_variation(Ped ped, int componentId)l
extern _native int get_number_of_ped_drawable_variations(Ped ped, int componentId)l
extern _native int get_ped_texture_variation(Ped ped, int componentId)l
extern _native int get_number_of_ped_texture_variations(Ped ped, int componentId, int drawableId)l
extern _native int get_number_of_ped_prop_drawable_variations(Ped ped, int propId)l
extern _native int get_number_of_ped_prop_texture_variations(Ped ped, int propId, int drawableId)l
extern _native int get_ped_palette_variation(Ped ped, int componentId)l
extern _native bool is_ped_component_variation_valid(Ped ped, int componentId, int drawableId, int textureId)l
extern _native void set_ped_component_variation(Ped ped, int componentId, int drawableId, int textureId, int paletteId)l
extern _native void set_ped_random_component_variation(Ped ped, bool p1)l
extern _native void set_ped_random_props(Ped ped)l
extern _native void set_ped_default_component_variation(Ped ped)l
extern _native void set_ped_blend_from_parents(Ped ped, any p1, any p2, float p3, float p4)l
extern _native void set_ped_head_blend_data(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, bool isParent)l
extern _native void update_ped_head_blend_data(Ped ped, float shapeMix, float skinMix, float thirdMix)l
extern _native void set_ped_head_overlay(Ped ped, int overlayID, int index, float opacity)l
extern _native32(0xFF43C18D) int _get_num_head_overlay_values(int overlayID)l
extern _native bool has_ped_head_blend_finished(Ped ped)l
extern _native void unk_0x894314A4(Ped ped)l
extern _native void unk_0x57E5B3F9(Ped ped, RGB colour, int p4)l
extern _native void unk_0xC6F36292(any p0)l
extern _native32(0x211DEFEC) int _get_first_parent_id_for_ped_type(int type)l
extern _native32(0x095D3BD8) int _get_num_parent_peds_of_type(int type)l
extern _native any unk_0x45F3BDFB(Ped ped, int p1, int drawableId, int textureId)l
extern _native bool unk_0xC6517D52(Ped p0)l
extern _native void unk_0x6435F67F(any p0)l
extern _native32(0xC0E23671) bool _is_ped_prop_valid(Ped ped, int componentId, int drawableId, int TextureId)l
extern _native bool unk_0x3B0CA391(Ped ped)l
extern _native void unk_0xFD103BA7(Ped ped)l
extern _native int get_ped_prop_index(Ped ped, int componentId)l
extern _native void set_ped_prop_index(Ped ped, int componentId, int drawableId, int TextureId, bool attach)l
extern _native void knock_off_ped_prop(Ped ped, bool p1, bool p2, bool p3, bool p4)l
extern _native void clear_ped_prop(Ped ped, int propId)l
extern _native void clear_all_ped_props(Ped ped)l
extern _native int get_ped_prop_texture_index(Ped ped, int componentId)l
extern _native void unk_0x7BCD8991(any p0)l
extern _native void unk_0x080275EE(any p0)l
extern _native void set_blocking_of_non_temporary_events(Ped ped, bool toggle)l
extern _native void set_ped_bounds_orientation(Ped ped, float p1, float p2, float p3, float p4, float p5)l
extern _native void register_target(Ped ped, Ped target)l
extern _native void register_hated_targets_around_ped(Ped ped, float radius)l
extern _native Ped get_random_ped_at_coord(vector3 vec, vector3 Radius, int pedType)l
extern _native bool get_closest_ped(vector3 vec, float radius, bool p4, bool p5, Ped* outPed, bool p7, bool p8, int pedType)l
extern _native void set_scenario_peds_to_be_returned_by_next_command(bool value)l
extern _native bool unk_0x18DD76A1(Ped ped, bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, any p8)l
extern _native void unk_0x6D55B3B3(Ped driver, float p1)l
extern _native void set_driver_ability(Ped driver, float ability)l
extern _native void set_driver_aggressiveness(Ped driver, float aggressiveness)l
extern _native bool can_ped_ragdoll(Ped ped)l
extern _native bool set_ped_to_ragdoll(Ped ped, int time1, int time2, int ragdollType, bool p4, bool p5, bool p6)l
extern _native bool set_ped_to_ragdoll_with_fall(Ped ped, int time, int p2, int ragdollType, vector3 vec, float p7, float p8, float p9, float p10, float p11, float p12, float p13)l
extern _native void set_ped_ragdoll_on_collision(Ped ped, bool toggle)l
extern _native bool is_ped_ragdoll(Ped ped)l
extern _native bool is_ped_running_ragdoll_task(Ped ped)l
extern _native any set_ped_ragdoll_force_fall(Ped ped)l
extern _native void reset_ped_ragdoll_timer(Ped ped)l
extern _native void set_ped_can_ragdoll(Ped ped, bool toggle)l
extern _native bool is_ped_running_mobile_phone_task(Ped ped)l
extern _native bool unk_0x97353375(Ped ped)l
extern _native32(0x9C8F830D) void _set_ped_ragdoll_blocking_flags(Ped ped, int flags)l
extern _native32(0x77CBA290) void _reset_ped_ragdoll_blocking_flags(Ped ped, int flags)l
extern _native void set_ped_angled_defensive_area(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8, bool p9)l
extern _native void set_ped_sphere_defensive_area(Ped ped, vector3 vec, float radius, bool p5, bool p6)l
extern _native void set_ped_defensive_sphere_attached_to_ped(Ped ped, Ped target, vector3 Offset, float radius, bool p6)l
extern _native void unk_0x4763B2C6(Ped ped, any p1, float p2, float p3, float p4, float p5, bool p6)l
extern _native void set_ped_defensive_area_attached_to_ped(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9, bool p10)l
extern _native void set_ped_defensive_area_direction(Ped ped, float p1, float p2, float p3, bool p4)l
extern _native void remove_ped_defensive_area(Ped ped, bool toggle)l
extern _native vector3 get_ped_defensive_area_position(Ped ped, bool p1)l
extern _native void set_ped_preferred_cover_set(Ped ped, any itemSet)l
extern _native void remove_ped_preferred_cover_set(Ped ped)l
extern _native void revive_injured_ped(Ped ped)l
extern _native void resurrect_ped(Ped ped)l
extern _native void set_ped_name_debug(Ped ped, const char* name)l
extern _native vector3 get_ped_extracted_displacement(Ped ped, bool worldSpace)l
extern _native any set_ped_dies_when_injured(Ped ped, bool toggle)l
extern _native any set_ped_enable_weapon_blocking(Ped ped, bool toggle)l
extern _native void unk_0x141CC936(Ped ped, bool p1)l
extern _native any reset_ped_visible_damage(Ped ped)l
extern _native void apply_ped_blood_damage_by_zone(Ped ped, any p1, float p2, float p3, any p4)l
extern _native void apply_ped_blood(Ped ped, int boneIndex, vector3 Rot, const char* woundType)l
extern _native void apply_ped_blood_by_zone(Ped ped, any p1, float p2, float p3, any* p4)l
extern _native void apply_ped_blood_specific(Ped ped, any p1, float p2, float p3, float p4, float p5, any p6, float p7, any* p8)l
extern _native void apply_ped_damage_decal(Ped ped, int p1, float p2, float p3, float p4, float p5, float p6, int p7, bool p8, const char* p9)l
extern _native void apply_ped_damage_pack(Ped ped, const char* damagePack, float damage, float mult)l
extern _native void clear_ped_blood_damage(Ped ped)l
extern _native void clear_ped_blood_damage_by_zone(Ped ped, int p1)l
extern _native void hide_ped_blood_damage_by_zone(Ped ped, any p1, bool p2)l
extern _native void clear_ped_damage_decal_by_zone(Ped ped, int p1, const char* p2)l
extern _native any get_ped_decorations_state(Ped ped)l
extern _native void clear_ped_wetness(Ped ped)l
extern _native void set_ped_wetness_height(Ped ped, float height)l
extern _native void set_ped_wetness_enabled_this_frame(Ped ped)l
extern _native any unk_0xA993915F(Ped ped)l
extern _native void set_ped_sweat(Ped ped, float sweat)l
extern _native32(0x70559AC7) void _set_ped_decoration(Ped ped, Hash collection, Hash overlay)l
extern _native32(0x3543019E) int _get_tattoo_zone(Hash collection, Hash overlay)l
extern _native void clear_ped_decorations(Ped ped)l
extern _native32(0xEFD58EB9) void _clear_ped_facial_decorations(Ped ped)l
extern _native bool was_ped_skeleton_updated(Ped ped)l
extern _native vector3 get_ped_bone_coords(Ped ped, int boneId, vector3 offset)l
extern _native void create_nm_message(bool startImmediately, int messageId)l
extern _native void give_ped_nm_message(Ped ped)l
extern _native any add_scenario_blocking_area(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9)l
extern _native void remove_scenario_blocking_areas()l
extern _native void remove_scenario_blocking_area(any p0, bool p1)l
extern _native void set_scenario_peds_spawn_in_sphere_area(any p0, any p1, any p2, any p3, any p4)l
extern _native bool is_ped_using_scenario(Ped ped, const char* scenario)l
extern _native bool is_ped_using_any_scenario(Ped ped)l
extern _native any unk_0x59DE73AC(any p0, any p1, any p2, any p3)l
extern _native void unk_0xC08FE5F6(any p0, bool p1)l
extern _native any unk_0x58C0F6CF(any p0, any p1, any p2, any p3)l
extern _native any unk_0x761F8F48(any p0, any p1, any p2, any p3)l
extern _native void unk_0x033F43FA(any p0)l
extern _native void unk_0x4C684C81(any p0)l
extern _native any unk_0x7B4C3E6F(any p0, any p1, any p2, any p3)l
extern _native void unk_0x5BC276AE(Ped ped, bool p1)l
extern _native void play_facial_anim(Ped ped, const char* animName, const char* animDict)l
extern _native void set_facial_idle_anim_override(Ped ped, const char* animName, const char* animDict)l
extern _native void clear_facial_idle_anim_override(Ped ped)l
extern _native void set_ped_can_play_gesture_anims(Ped ped, bool toggle)l
extern _native void set_ped_can_play_viseme_anims(Ped ped, bool toggle, bool p2)l
extern _native void unk_0xADB2511A(Ped ped, bool p1)l
extern _native void set_ped_can_play_ambient_anims(Ped ped, bool toggle)l
extern _native void set_ped_can_play_ambient_base_anims(Ped ped, bool toggle)l
extern _native void unk_0xB7CD0A49(Ped ped)l
extern _native void set_ped_can_arm_ik(Ped ped, bool toggle)l
extern _native void set_ped_can_head_ik(Ped ped, bool toggle)l
extern _native void set_ped_can_leg_ik(Ped ped, bool toggle)l
extern _native void set_ped_can_torso_ik(Ped ped, bool toggle)l
extern _native void unk_0x7B0040A8(Ped ped, bool p1)l
extern _native void unk_0x0FDA62DE(Ped ped, bool p1)l
extern _native void set_ped_can_use_auto_conversation_lookat(Ped ped, bool toggle)l
extern _native bool is_ped_headtracking_ped(Ped ped1, Ped ped2)l
extern _native bool is_ped_headtracking_entity(Ped ped, Entity entity)l
extern _native void set_ped_primary_lookat(Ped ped, Ped lookAt)l
extern _native void unk_0xFC942D7C(any p0, any p1)l
extern _native void set_ped_cloth_prone(any p0, any p1)l
extern _native void set_ped_config_flag(Ped ped, int flagId, bool value)l
extern _native void set_ped_reset_flag(Ped ped, int flagId, bool doReset)l
extern _native bool get_ped_config_flag(Ped ped, int flagId, bool p2)l
extern _native bool get_ped_reset_flag(Ped ped, int flagId)l
extern _native void set_ped_group_member_passenger_index(Ped ped, int index)l
extern _native void set_ped_can_evasive_dive(Ped ped, bool toggle)l
extern _native bool is_ped_evasive_diving(Ped ped, Entity* evadingEntity)l
extern _native void set_ped_shoots_at_coord(Ped ped, vector3 vec, bool toggle)l
extern _native void set_ped_model_is_suppressed(Ped ped, bool toggle)l
extern _native void stop_any_ped_model_being_suppressed()l
extern _native void set_ped_can_be_targeted_when_injured(Ped ped, bool toggle)l
extern _native void set_ped_generates_dead_body_events(Ped ped, bool toggle)l
extern _native void unk_0xFF1F6AEB(Ped ped, bool p1)l
extern _native void set_ped_can_ragdoll_from_player_impact(Ped ped, bool toggle)l
extern _native void give_ped_helmet(Ped ped, bool cannotRemove, int helmetFlag, int textureIndex)l
extern _native void remove_ped_helmet(Ped ped, bool instantly)l
extern _native void set_ped_helmet(Ped ped, bool canWearHelmet)l
extern _native void set_ped_helmet_flag(Ped ped, int helmetFlag)l
extern _native void set_ped_helmet_prop_index(Ped ped, int propIndex)l
extern _native void set_ped_helmet_texture_index(Ped ped, int textureIndex)l
extern _native bool is_ped_wearing_helmet(Ped ped)l
extern _native void unk_0x24A1284E(Ped ped)l
extern _native any unk_0x8A3A3116(any p0)l
extern _native any unk_0x74EB662D(any p0)l
extern _native bool unk_0xFFF149FE(any p0)l
extern _native void set_ped_to_load_cover(Ped ped, bool toggle)l
extern _native void set_ped_can_cower_in_cover(Ped ped, bool toggle)l
extern _native void set_ped_can_peek_in_cover(Ped ped, bool toggle)l
extern _native void set_ped_plays_head_on_horn_anim_when_dies_in_vehicle(Ped ped, bool toggle)l
extern _native void set_ped_leg_ik_mode(Ped ped, int mode)l
extern _native void set_ped_motion_blur(Ped ped, bool toggle)l
extern _native void set_ped_can_switch_weapon(Ped ped, bool toggle)l
extern _native void set_ped_dies_instantly_in_water(Ped ped, bool toggle)l
extern _native void unk_0x77BB7CB8(Ped ped, int p1)l
extern _native void stop_ped_weapon_firing_when_dropped(Ped ped)l
extern _native void set_scripted_anim_seat_offset(Ped ped, float p1)l
extern _native void set_ped_combat_movement(Ped ped, int combatMovement)l
extern _native int get_ped_combat_movement(Ped ped)l
extern _native void set_ped_combat_ability(Ped ped, int p1)l
extern _native void set_ped_combat_range(Ped ped, int p1)l
extern _native any get_ped_combat_range(Ped ped)l
extern _native void set_ped_combat_attributes(Ped ped, int attributeIndex, bool enabled)l
extern _native void set_ped_target_loss_response(Ped ped, int responseType)l
extern _native bool unk_0x139C0875(Ped ped)l
extern _native bool is_ped_performing_stealth_kill(Ped ped)l
extern _native bool unk_0x9BE7C860(Ped ped)l
extern _native bool is_ped_being_stealth_killed(Ped ped)l
extern _native Ped get_melee_target_for_ped(Ped ped)l
extern _native bool was_ped_killed_by_stealth(Ped ped)l
extern _native bool was_ped_killed_by_takedown(Ped ped)l
extern _native bool unk_0x3993092B(Ped ped)l
extern _native void set_ped_flee_attributes(Ped ped, int attributes, bool p2)l
extern _native void set_ped_cower_hash(Ped ped, const char* p1)l
extern _native void unk_0xA6F2C057(any p0, bool p1)l
extern _native void set_ped_steers_around_peds(Ped ped, bool toggle)l
extern _native void set_ped_steers_around_objects(Ped ped, bool toggle)l
extern _native void set_ped_steers_around_vehicles(Ped ped, bool toggle)l
extern _native void unk_0x2276DE0D(any p0, bool p1)l
extern _native void unk_0x59C52BE6(any p0)l
extern _native void unk_0x1D87DDC1(any p0, bool p1)l
extern _native void unk_0xB52BA5F5(any p0)l
extern _native bool is_any_ped_near_point(vector3 vec, float radius)l
extern _native void unk_0x187B9070(Ped ped, bool p1, bool p2)l
extern _native bool unk_0x45037B9B(any p0, float p1, float p2, float p3, float p4)l
extern _native void unk_0x840D24D3(any p0)l
extern _native void get_ped_flood_invincibility(Ped ped, bool p1)l
extern _native void unk_0x9194DB71(Ped ped, bool p1)l
extern _native bool is_tracked_ped_visible(Ped ped)l
extern _native any unk_0x5B1B70AA(any p0)l
extern _native bool is_ped_tracked(Ped ped)l
extern _native bool has_ped_received_event(any p0, any p1)l
extern _native bool unk_0x74A0F291(any p0, any p1)l
extern _native int get_ped_bone_index(Ped ped, int boneId)l
extern _native int get_ped_ragdoll_bone_index(Ped ped, int bone)l
extern _native void set_ped_enveff_scale(Ped ped, float value)l
extern _native float get_ped_enveff_scale(Ped ped)l
extern _native void set_enable_ped_enveff_scale(Ped ped, bool toggle)l
extern _native void unk_0x3B882533(Ped ped, float p1)l
extern _native void unk_0x87A0C174(Ped ped, int p1, int p2, int p3)l
extern _native void unk_0x7BD26837(any p0, any p1)l
extern _native void unk_0x98E29ED0(any p0, bool p1)l
extern _native int create_synchronized_scene(vector3 vec, float roll, float pitch, float yaw, int p6)l
extern _native int unk_0xF3876894(vector3 vec, float radius, Hash object)l
extern _native bool is_synchronized_scene_running(int sceneId)l
extern _native void set_synchronized_scene_origin(int sceneID, vector3 vec, float roll, float pitch, float yaw, bool p7)l
extern _native void set_synchronized_scene_phase(int sceneID, float phase)l
extern _native float get_synchronized_scene_phase(int sceneID)l
extern _native void set_synchronized_scene_rate(int sceneID, float rate)l
extern _native float get_synchronized_scene_rate(int sceneID)l
extern _native void set_synchronized_scene_looped(int sceneID, bool toggle)l
extern _native bool is_synchronized_scene_looped(int sceneID)l
extern _native32(0x2DE48DA1) void _set_synchronized_scene_occlusion_portal(any sceneID, bool p1)l
extern _native bool unk_0x72CF2514(any p0)l
extern _native void attach_synchronized_scene_to_entity(int sceneID, Entity entity, int boneIndex)l
extern _native void detach_synchronized_scene(int sceneID)l
extern _native32(0xBF7F9035) void _dispose_synchronized_scene(int scene)l
extern _native bool force_ped_motion_state(Ped ped, Hash motionStateHash, bool p2, bool p3, bool p4)l
extern _native void set_ped_max_move_blend_ratio(Ped ped, float value)l
extern _native void set_ped_min_move_blend_ratio(Ped ped, float value)l
extern _native void set_ped_move_rate_override(Ped ped, float value)l
extern _native bool unk_0x79543043(Ped ped, int flag)l
extern _native int get_ped_nearby_vehicles(Ped ped, int* sizeAndVehs)l
extern _native int get_ped_nearby_peds(Ped ped, int* sizeAndPeds, int ignore)l
extern _native bool unk_0xF9FB4B71(Ped ped)l
extern _native bool is_ped_using_action_mode(Ped ped)l
extern _native void set_ped_using_action_mode(Ped ped, bool p1, any p2, const char* action)l
extern _native void set_ped_capsule(Ped ped, float value)l
extern _native any register_pedheadshot(Ped ped)l
extern _native any unk_0x4DD03628(any p0)l
extern _native void unregister_pedheadshot(Ped ped)l
extern _native int is_pedheadshot_valid(int handle)l
extern _native bool is_pedheadshot_ready(int handle)l
extern _native const char* get_pedheadshot_txd_string(int handle)l
extern _native bool unk_0x10F2C023(any p0)l
extern _native void unk_0x0DBB2FA7(any p0)l
extern _native any unk_0x810158F8()l
extern _native any unk_0x05023F8F()l
extern _native any unk_0xAA39FD6C()l
extern _native void unk_0xEF9142DB(any p0, any p1)l
extern _native void unk_0x0688DE64(any p0)l
extern _native void unk_0x909A1D76(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration)l
extern _native void unk_0x4AAD0ECB(vector3 vec, float p3, float p4, float p5, float p6, int interiorFlags, float scale, int duration)l
extern _native void unk_0x492C9E46()l
extern _native any unk_0x814A28F4()l
extern _native any unk_0x0B60D2BA()l
extern _native any unk_0x6B83ABDF()l
extern _native any unk_0xF46B4DC8()l
extern _native void unk_0x36A4AC65(any p0, any* p1, any* p2, any* p3)l
extern _native void unk_0xBA699DDF(any p0, any* p1)l
extern _native void set_ik_target(Ped ped, int p1, Ped targetPed, int boneLookAt, vector3 vec, any p7, int duration, int duration1)l
extern _native void unk_0xFB4000DC(any p0)l
extern _native void request_action_mode_asset(const char* asset)l
extern _native bool has_action_mode_asset_loaded(const char* asset)l
extern _native void remove_action_mode_asset(const char* asset)l
extern _native void request_stealth_mode_asset(const char* asset)l
extern _native bool has_stealth_mode_asset_loaded(const char* asset)l
extern _native void remove_stealth_mode_asset(const char* asset)l
extern _native void set_ped_lod_multiplier(Ped ped, float multiplier)l
extern _native void unk_0x2F9550C2(any p0, bool p1, any p2)l
extern _native void unk_0x37DBC2AD(Ped ped, bool toggle)l
extern _native void unk_0xC0F1BC91(any p0, bool p1, any p2, any p3)l
extern _native bool unk_0x1A464167(Ped ped, vector3 vec, float range)l
extern _native bool unk_0xD0567D41(any p0, any p1, float p2, float p3, float p4, float p5)l
extern _native void unk_0x4BBE5E2C(any p0, any p1, any p2, any p3, any p4)l
extern _native void unk_0xA89A53F2(Ped ped)l
#pragma endregion //}
#pragma region VEHICLE //{
extern _native Vehicle create_vehicle(Hash modelHash, vector3 vec, float heading, bool isNetwork, bool p6)l
extern _native void delete_vehicle(Vehicle* vehicle)l
extern _native void unk_0xBB54ECCA(Vehicle vehicle, bool p1, bool p2)l
extern _native void set_vehicle_allow_no_passengers_lockon(Vehicle veh, bool toggle)l
extern _native int unk_0xFBDE9FD8(Vehicle vehicle)l
extern _native bool is_vehicle_model(Vehicle vehicle, Hash model)l
extern _native bool does_script_vehicle_generator_exist(int vehicleGenerator)l
extern _native int create_script_vehicle_generator(vector3 vec, float heading, float p4, float p5, Hash modelHash, int p7, int p8, int p9, int p10, bool p11, bool p12, bool p13, bool p14, bool p15, int p16)l
extern _native void delete_script_vehicle_generator(int vehicleGenerator)l
extern _native void set_script_vehicle_generator(any vehicleGenerator, bool enabled)l
extern _native void set_all_vehicle_generators_active_in_area(vector3 vec_1, vector3 vec_2, bool p6, bool p7)l
extern _native void set_all_vehicle_generators_active()l
extern _native void set_all_low_priority_vehicle_generators_active(bool active)l
extern _native void unk_0x935A95DA(float p0, float p1, float p2, float p3)l
extern _native void unk_0x6C73E45A()l
extern _native any set_all_vehicles_spawn(Vehicle p0, bool p1, bool p2, bool p3)l
extern _native bool is_vehicle_stuck_on_roof(Vehicle vehicle)l
extern _native void add_vehicle_upsidedown_check(Vehicle vehicle)l
extern _native void remove_vehicle_upsidedown_check(Vehicle vehicle)l
extern _native bool is_vehicle_stopped(Vehicle vehicle)l
extern _native int get_vehicle_number_of_passengers(Vehicle vehicle)l
extern _native int get_vehicle_max_number_of_passengers(Vehicle vehicle)l
extern _native int get_vehicle_model_number_of_seats(Hash modelHash)l
extern _native bool unk_0x769E5CF2(Vehicle vehicle, bool flag)l
extern _native void set_vehicle_density_multiplier_this_frame(float multiplier)l
extern _native void set_random_vehicle_density_multiplier_this_frame(float multiplier)l
extern _native void set_parked_vehicle_density_multiplier_this_frame(float multiplier)l
extern _native void unk_0x09462665(bool toggle)l
extern _native32(0xDAE2A2BE) void _set_some_vehicle_density_multiplier_this_frame(float value)l
extern _native void set_far_draw_vehicles(bool toggle)l
extern _native any set_number_of_parked_vehicles(int value)l
extern _native void set_vehicle_doors_locked(Vehicle vehicle, int doorLockStatus)l
extern _native void set_ped_targettable_vehicle_destroy(Vehicle vehicle, int vehicleComponent, int destroyType)l
extern _native void disable_vehicle_impact_explosion_activation(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_doors_locked_for_player(Vehicle vehicle, Player player, bool toggle)l
extern _native bool get_vehicle_doors_locked_for_player(Vehicle vehicle, Player player)l
extern _native void set_vehicle_doors_locked_for_all_players(Vehicle vehicle, bool toggle)l
extern _native void unk_0xE4EF6514(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_doors_locked_for_team(Vehicle vehicle, int team, bool toggle)l
extern _native void explode_vehicle(Vehicle vehicle, bool isAudible, bool isInvisible)l
extern _native void set_vehicle_out_of_control(Vehicle vehicle, bool killDriver, bool explodeOnImpact)l
extern _native void set_vehicle_timed_explosion(Vehicle vehicle, Ped ped, bool toggle)l
extern _native void unk_0x811373DE(Vehicle vehicle)l
extern _native any unk_0xA4E69134()l
extern _native void unk_0x65255524()l
extern _native bool unk_0xE39DAF36(Vehicle vehicle)l
extern _native void set_taxi_lights(Vehicle vehicle, bool state)l
extern _native bool is_taxi_light_on(Vehicle vehicle)l
extern _native bool is_vehicle_in_garage_area(const char* garageName, Vehicle vehicle)l
extern _native void set_vehicle_colours(Vehicle vehicle, int colorPrimary, int colorSecondary)l
extern _native void set_vehicle_fullbeam(Vehicle vehicle, bool toggle)l
extern _native void steer_unlock_bias(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_custom_primary_colour(Vehicle vehicle, RGB colour)l
extern _native void get_vehicle_custom_primary_colour(Vehicle vehicle, int* r, int* g, int* b)l
extern _native any clear_vehicle_custom_primary_colour(Vehicle vehicle)l
extern _native bool get_is_vehicle_primary_colour_custom(Vehicle vehicle)l
extern _native void set_vehicle_custom_secondary_colour(Vehicle vehicle, RGB colour)l
extern _native void get_vehicle_custom_secondary_colour(Vehicle vehicle, int* r, int* g, int* b)l
extern _native any clear_vehicle_custom_secondary_colour(Vehicle vehicle)l
extern _native bool get_is_vehicle_secondary_colour_custom(Vehicle vehicle)l
extern _native void set_vehicle_enveff_scale(Vehicle vehicle, float fade)l
extern _native float get_vehicle_enveff_scale(Vehicle vehicle)l
extern _native void set_can_respray_vehicle(Vehicle vehicle, bool state)l
extern _native void unk_0x54E9EE75(Vehicle vehicle, bool p1)l
extern _native32(0x4A46E814) void _jitter_vehicle(Vehicle vehicle, bool p1, float yaw, float pitch, float roll)l
extern _native void set_boat_anchor(Vehicle vehicle, bool toggle)l
extern _native void unk_0x0ED84792(Vehicle vehicle, bool p1)l
extern _native void unk_0xA739012A(Vehicle vehicle, bool p1)l
extern _native void unk_0x66FA450C(Vehicle vehicle, float p1)l
extern _native void unk_0x35614622(Vehicle vehicle, bool p1)l
extern _native void set_vehicle_siren(Vehicle vehicle, bool toggle)l
extern _native bool is_vehicle_siren_on(Vehicle vehicle)l
extern _native void set_vehicle_strong(Vehicle vehicle, bool toggle)l
extern _native void remove_vehicle_stuck_check(Vehicle vehicle)l
extern _native void get_vehicle_colours(Vehicle vehicle, int* colorPrimary, int* colorSecondary)l
extern _native bool is_vehicle_seat_free(Vehicle vehicle, int seatIndex)l
extern _native Ped get_ped_in_vehicle_seat(Vehicle vehicle, int index)l
extern _native Ped get_last_ped_in_vehicle_seat(Vehicle vehicle, int seatIndex)l
extern _native bool get_vehicle_lights_state(Vehicle vehicle, bool* lightsOn, bool* highbeamsOn)l
extern _native bool is_vehicle_tyre_burst(Vehicle vehicle, int wheelID, bool completely)l
extern _native void set_vehicle_forward_speed(Vehicle vehicle, float speed)l
extern _native32(0xCBC7D3C8) void _set_vehicle_halt(Vehicle vehicle, float distance, int killEngine, bool unknown)l
extern _native void unk_0x943A6CFC(Vehicle vehicle, float p1)l
extern _native bool set_ped_enabled_bike_ringtone(Vehicle vehicle, Entity entity)l
extern _native bool unk_0x593143B9(Vehicle vehicle)l
extern _native32(0x70DD5E25) Vehicle _get_vehicle_attached_to_entity(Object object)l
extern _native bool unk_0xFBF5536A(Vehicle vehicle, Entity entity)l
extern _native void unk_0x20AB5783(Vehicle vehicle, Entity entity)l
extern _native void unk_0x0F11D01F(Vehicle vehicle)l
extern _native void unk_0xAE040377(Vehicle vehicle, bool p1)l
extern _native void unk_0x4C0E4031(Vehicle vehicle, bool p1)l
extern _native bool unk_0x6346B7CC(Vehicle vehicle)l
extern _native void unk_0xCCB41A55(Vehicle vehicle, float p1)l
extern _native void set_vehicle_tyre_burst(Vehicle vehicle, int index, bool onRim, float p3)l
extern _native void set_vehicle_doors_shut(Vehicle vehicle, bool closeInstantly)l
extern _native void set_vehicle_tyres_can_burst(Vehicle vehicle, bool toggle)l
extern _native bool get_vehicle_tyres_can_burst(Vehicle vehicle)l
extern _native any set_vehicle_wheels_can_break(Vehicle vehicle, bool enabled)l
extern _native void set_vehicle_door_open(Vehicle vehicle, int doorIndex, bool loose, bool openInstantly)l
extern _native void remove_vehicle_window(Vehicle vehicle, int windowIndex)l
extern _native void roll_down_windows(Vehicle vehicle)l
extern _native any roll_down_window(Vehicle vehicle, int windowIndex)l
extern _native any roll_up_window(Vehicle vehicle, int windowIndex)l
extern _native any smash_vehicle_window(Vehicle vehicle, int index)l
extern _native any fix_vehicle_window(Vehicle vehicle, int index)l
extern _native32(0xCC95C96B) void _detach_vehicle_windscreen(Vehicle vehicle)l
extern _native32(0xFDA7B6CA) void _eject_jb700_roof(Vehicle vehicle, vector3 vec)l
extern _native void set_vehicle_lights(Vehicle vehicle, int state)l
extern _native void unk_0x4221E435(Vehicle vehicle, bool p1)l
extern _native void set_vehicle_alarm(Vehicle vehicle, bool state)l
extern _native any start_vehicle_alarm(Vehicle vehicle)l
extern _native bool is_vehicle_alarm_activated(Vehicle vehicle)l
extern _native void set_vehicle_interiorlight(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_light_multiplier(Vehicle vehicle, float multiplier)l
extern _native void attach_vehicle_to_trailer(Vehicle vehicle, Vehicle trailer, float radius)l
extern _native void unk_0x12AC1A16(Vehicle vehicle, Vehicle trailer, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11)l
extern _native void unk_0x40C4763F(Vehicle vehicle, Entity p1, float p2)l
extern _native void detach_vehicle_from_trailer(Vehicle vehicle)l
extern _native bool is_vehicle_attached_to_trailer(Vehicle vehicle)l
extern _native void unk_0xE74E85CE(Vehicle vehicle, float p1)l
extern _native void unk_0x06C47A6F(Vehicle vehicle)l
extern _native void set_vehicle_tyre_fixed(Vehicle vehicle, int tyreIndex)l
extern _native void set_vehicle_number_plate_text(Vehicle vehicle, const char* plateText)l
extern _native const char* get_vehicle_number_plate_text(Vehicle vehicle)l
extern _native int get_number_of_vehicle_number_plates()l
extern _native void set_vehicle_number_plate_text_index(Vehicle vehicle, int plateIndex)l
extern _native int get_vehicle_number_plate_text_index(Vehicle vehicle)l
extern _native void set_random_trains(bool toggle)l
extern _native Vehicle create_mission_train(int variation, vector3 vec, bool direction)l
extern _native any switch_train_track(int intersectionId, bool state)l
extern _native void unk_0xD5774FB7(any p0, any p1)l
extern _native void delete_all_trains()l
extern _native any set_train_speed(Vehicle train, float speed)l
extern _native any set_train_cruise_speed(Vehicle train, float speed)l
extern _native any set_random_boats(bool toggle)l
extern _native any set_garbage_trucks(bool toggle)l
extern _native bool does_vehicle_have_stuck_vehicle_check(Vehicle vehicle)l
extern _native any get_vehicle_recording_id(int p0, const char* p1)l
extern _native void request_vehicle_recording(any p0, any* p1)l
extern _native bool has_vehicle_recording_been_loaded(any p0, any* p1)l
extern _native void remove_vehicle_recording(any p0, any* p1)l
extern _native int unk_0xF31973BB(any p0, float p1)l
extern _native vector3 get_position_of_vehicle_recording_at_time(int p0, float p1, const char* p2)l
extern _native vector3 unk_0x4D1C15C2(any p0, float p1)l
extern _native int get_rotation_of_vehicle_recording_at_time(any p0, float p1, any* p2)l
extern _native float get_total_duration_of_vehicle_recording_id(any p0)l
extern _native any get_total_duration_of_vehicle_recording(any p0, any p1)l
extern _native float get_position_in_recording(any p0)l
extern _native float get_time_position_in_recording(any p0)l
extern _native void start_playback_recorded_vehicle(Vehicle vehicle, int p1, const char* playback, bool p3)l
extern _native void start_playback_recorded_vehicle_with_flags(Vehicle vehicle, any p1, const char* playback, any p3, any p4, any p5)l
extern _native void unk_0x01B91CD0(any p0, bool p1)l
extern _native void stop_playback_recorded_vehicle(any p0)l
extern _native void pause_playback_recorded_vehicle(any p0)l
extern _native void unpause_playback_recorded_vehicle(any p0)l
extern _native bool is_playback_going_on_for_vehicle(any p0)l
extern _native bool is_playback_using_ai_going_on_for_vehicle(any p0)l
extern _native any get_current_playback_for_vehicle(any p0)l
extern _native void skip_to_end_and_stop_playback_recorded_vehicle(any p0)l
extern _native any set_playback_speed(any p0, float speed)l
extern _native void start_playback_recorded_vehicle_using_ai(any p0, any p1, any* p2, float p3, any p4)l
extern _native void skip_time_in_playback_recorded_vehicle(any p0, float p1)l
extern _native void set_playback_to_use_ai(Vehicle vehicle, int flag)l
extern _native void set_playback_to_use_ai_try_to_revert_back_later(any p0, any p1, any p2, bool p3)l
extern _native void unk_0x943A58EB(Vehicle vehicle, vector3 vec, any p4)l
extern _native void unk_0x5C9F477C(any p0, float p1, float p2, float p3)l
extern _native void unk_0xCD83C393(any p0, float p1, float p2, float p3)l
extern _native void unk_0x2EF8435C(any p0, bool p1)l
extern _native void explode_vehicle_in_cutscene(Vehicle vehicle, bool p1)l
extern _native void add_vehicle_stuck_check_with_warp(any p0, float p1, any p2, bool p3, bool p4, bool p5, any p6)l
extern _native void set_vehicle_model_is_suppressed(Hash model, bool suppressed)l
extern _native Vehicle get_random_vehicle_in_sphere(vector3 vec, float radius, Hash modelHash, int flags)l
extern _native Vehicle get_random_vehicle_front_bumper_in_sphere(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native Vehicle get_random_vehicle_back_bumper_in_sphere(float p0, float p1, float p2, float p3, int p4, int p5, int p6)l
extern _native Vehicle get_closest_vehicle(vector3 vec, float radius, Hash modelHash, int flags)l
extern _native Entity get_train_carriage(Vehicle train, int trailerNumber)l
extern _native void delete_mission_train(Vehicle* train)l
extern _native void set_mission_train_as_no_longer_needed(Vehicle* train, bool p1)l
extern _native void set_mission_train_coords(Vehicle train, vector3 vec)l
extern _native bool is_this_model_a_boat(Hash model)l
extern _native bool is_this_model_a_plane(Hash model)l
extern _native bool is_this_model_a_heli(Hash model)l
extern _native bool is_this_model_a_car(Hash model)l
extern _native bool is_this_model_a_train(Hash model)l
extern _native bool is_this_model_a_bike(Hash model)l
extern _native bool is_this_model_a_bicycle(Hash model)l
extern _native bool is_this_model_a_quadbike(Hash model)l
extern _native void set_heli_blades_full_speed(Vehicle vehicle)l
extern _native void set_heli_blades_speed(Vehicle vehicle, float speed)l
extern _native void unk_0x1128A45B(Vehicle vehicle, float p1, float p2)l
extern _native void set_vehicle_can_be_targetted(Vehicle vehicle, bool state)l
extern _native void unk_0x486C1280(Vehicle vehicle, bool p1)l
extern _native void set_vehicle_can_be_visibly_damaged(Vehicle vehicle, bool state)l
extern _native void unk_0x009AB49E(Vehicle vehicle, bool p1)l
extern _native void unk_0x758C5E2E(Vehicle vehicle, bool p1)l
extern _native float get_vehicle_dirt_level(Vehicle vehicle)l
extern _native void set_vehicle_dirt_level(Vehicle vehicle, float dirtLevel)l
extern _native32(0xDAC523BC) bool _is_vehicle_damaged(Vehicle vehicle)l
extern _native bool is_vehicle_door_fully_open(Vehicle vehicle, int doorIndex)l
extern _native void set_vehicle_engine_on(Vehicle vehicle, bool value, bool instantly, bool otherwise)l
extern _native void set_vehicle_undriveable(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_provides_cover(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_door_control(Vehicle vehicle, int doorIndex, int speed, float angle)l
extern _native void set_vehicle_door_latched(Vehicle vehicle, int doorIndex, bool p2, bool p3, bool p4)l
extern _native float get_vehicle_door_angle_ratio(Vehicle vehicle, int door)l
extern _native void set_vehicle_door_shut(Vehicle vehicle, int doorIndex, bool closeInstantly)l
extern _native void set_vehicle_door_broken(Vehicle vehicle, int doorIndex, bool deleteDoor)l
extern _native void set_vehicle_can_break(Vehicle vehicle, bool toggle)l
extern _native bool does_vehicle_have_roof(Vehicle vehicle)l
extern _native bool is_big_vehicle(Vehicle vehicle)l
extern _native int get_number_of_vehicle_colours(Vehicle vehicle)l
extern _native void set_vehicle_colour_combination(Vehicle vehicle, int colorCombination)l
extern _native int get_vehicle_colour_combination(Vehicle vehicle)l
extern _native void set_vehicle_is_considered_by_player(Vehicle vehicle, bool toggle)l
extern _native void unk_0xA6D8D7A5(Vehicle vehicle, bool toggle)l
extern _native void unk_0xACAB8FF3(Vehicle vehicle, bool p1)l
extern _native void unk_0xF0E5C41D(Vehicle vehicle, bool p1)l
extern _native void unk_0x2F98B4B7(Vehicle vehicle, bool p1)l
extern _native void get_random_vehicle_model_in_memory(bool p0, Hash* modelHash, int* p2)l
extern _native int get_vehicle_door_lock_status(Vehicle vehicle)l
extern _native bool is_vehicle_door_damaged(Vehicle veh, int doorID)l
extern _native32(0x065B92B3) void _set_vehicle_door_can_break(Vehicle vehicle, int doorIndex, bool isBreakable)l
extern _native bool unk_0xB3A2CC4F(Vehicle vehicle, bool p1)l
extern _native bool is_vehicle_bumper_broken_off(Vehicle vehicle, bool front)l
extern _native bool is_cop_vehicle_in_area_3d(float x1, float x2, float y1, float y2, float z1, float z2)l
extern _native bool is_vehicle_on_all_wheels(Vehicle vehicle)l
extern _native Hash get_vehicle_layout_hash(Vehicle vehicle)l
extern _native void set_render_train_as_derailed(Vehicle train, bool toggle)l
extern _native void set_vehicle_extra_colours(Vehicle vehicle, int pearlescentColor, int wheelColor)l
extern _native void get_vehicle_extra_colours(Vehicle vehicle, int* pearlescentColor, int* wheelColor)l
extern _native void stop_all_garage_activity()l
extern _native void set_vehicle_fixed(Vehicle vehicle)l
extern _native void set_vehicle_deformation_fixed(Vehicle vehicle)l
extern _native void unk_0x88F0F7E7(Vehicle vehicle, bool p1)l
extern _native void unk_0x90D6EE57(Vehicle vehicle, bool p1)l
extern _native void set_disable_vehicle_petrol_tank_fires(Vehicle vehicle, bool toggle)l
extern _native void set_disable_vehicle_petrol_tank_damage(Vehicle vehicle, bool toggle)l
extern _native void unk_0x1784BA1A(Vehicle vehicle, bool p1)l
extern _native void unk_0x40C323AE(Vehicle vehicle, bool p1)l
extern _native void unk_0x847F1304(Vehicle vehicle, bool p1)l
extern _native void unk_0xCBD98BA1(Vehicle vehicle, bool p1)l
extern _native void remove_vehicles_from_generators_in_area(vector3 vec_1, vector3 vec_2, any unk)l
extern _native void set_vehicle_steer_bias(Vehicle vehicle, float value)l
extern _native bool is_vehicle_extra_turned_on(Vehicle vehicle, int extraId)l
extern _native void set_vehicle_extra(Vehicle vehicle, int extraId, bool toggle)l
extern _native bool does_extra_exist(Vehicle vehicle, int extraId)l
extern _native void set_convertible_roof(Vehicle vehicle, bool p1)l
extern _native void lower_convertible_roof(Vehicle vehicle, bool instantlyLower)l
extern _native void raise_convertible_roof(Vehicle vehicle, bool instantlyRaise)l
extern _native int get_convertible_roof_state(Vehicle vehicle)l
extern _native bool is_vehicle_a_convertible(Vehicle vehicle, bool p1)l
extern _native bool is_vehicle_stopped_at_traffic_lights(Vehicle vehicle)l
extern _native void set_vehicle_damage(Vehicle vehicle, vector3 Offset, float damage, float radius, bool p6)l
extern _native float get_vehicle_engine_health(Vehicle vehicle)l
extern _native void set_vehicle_engine_health(Vehicle vehicle, float health)l
extern _native float get_vehicle_petrol_tank_health(Vehicle vehicle)l
extern _native void set_vehicle_petrol_tank_health(Vehicle vehicle, float health)l
extern _native bool is_vehicle_stuck_timer_up(Vehicle vehicle, int p1, int p2)l
extern _native void reset_vehicle_stuck_timer(Vehicle vehicle, bool nullAttributes)l
extern _native bool is_vehicle_driveable(Vehicle vehicle, bool p1)l
extern _native void set_vehicle_has_been_owned_by_player(Vehicle vehicle, bool owned)l
extern _native void set_vehicle_needs_to_be_hotwired(Vehicle vehicle, bool toggle)l
extern _native void start_vehicle_horn(Vehicle vehicle, int duration, Hash mode, bool forever)l
extern _native32(0x968E5770) void _set_vehicle_silent(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_has_strong_axles(Vehicle vehicle, bool toggle)l
extern _native const char* get_display_name_from_vehicle_model(Hash modelHash)l
extern _native vector3 get_vehicle_deformation_at_pos(Vehicle vehicle, vector3 offset)l
extern _native void set_vehicle_livery(Vehicle vehicle, int livery)l
extern _native int get_vehicle_livery(Vehicle vehicle)l
extern _native int get_vehicle_livery_count(Vehicle vehicle)l
extern _native bool is_vehicle_window_intact(Vehicle vehicle, int windowIndex)l
extern _native bool are_all_vehicle_windows_intact(Vehicle vehicle)l
extern _native bool are_any_vehicle_seats_free(Vehicle vehicle)l
extern _native void reset_vehicle_wheels(Vehicle vehicle, bool toggle)l
extern _native bool is_heli_part_broken(Vehicle vehicle, bool p1, bool p2, bool p3)l
extern _native32(0xF01E2AAB) float _get_heli_main_rotor_health(Vehicle vehicle)l
extern _native32(0xA41BC13D) float _get_heli_tail_rotor_health(Vehicle vehicle)l
extern _native32(0x8A68388F) float _get_heli_engine_health(Vehicle vehicle)l
extern _native bool was_counter_activated(Vehicle vehicle, any p1)l
extern _native void set_vehicle_name_debug(Vehicle vehicle, const char* name)l
extern _native void set_vehicle_explodes_on_high_explosion_damage(Vehicle vehicle, bool toggle)l
extern _native void unk_0xC306A9A3(Vehicle vehicle, bool p1)l
extern _native any unk_0x95A9ACCB(Vehicle vehicle, bool p1)l
extern _native void control_landing_gear(Vehicle vehicle, int state)l
extern _native int get_landing_gear_state(Vehicle vehicle)l
extern _native bool is_any_vehicle_near_point(vector3 vec, float radius)l
extern _native void request_vehicle_high_detail_model(Vehicle vehicle)l
extern _native void remove_vehicle_high_detail_model(Vehicle vehicle)l
extern _native bool is_vehicle_high_detail(Vehicle vehicle)l
extern _native void request_vehicle_asset(Hash vehicleHash, int vehicleAsset)l
extern _native bool has_vehicle_asset_loaded(int vehicleAsset)l
extern _native void remove_vehicle_asset(int vehicleAsset)l
extern _native32(0x88236E22) void _set_tow_truck_crane_height(Vehicle towTruck, float height)l
extern _native void attach_vehicle_to_tow_truck(Vehicle towTruck, Vehicle vehicle, bool rear, vector3 hookOffset)l
extern _native void detach_vehicle_from_tow_truck(Vehicle towTruck, Vehicle vehicle)l
extern _native bool detach_vehicle_from_any_tow_truck(Vehicle vehicle)l
extern _native bool is_vehicle_attached_to_tow_truck(Vehicle towTruck, Vehicle vehicle)l
extern _native Entity get_entity_attached_to_tow_truck(Vehicle towTruck)l
extern _native any set_vehicle_automatically_attaches(Vehicle vehicle, any p1, any p2)l
extern _native void unk_0xED23C8A3(any p0, float p1, bool p2)l
extern _native void unk_0xB1A52EF7(any p0, float p1, bool p2)l
extern _native void unk_0xF30C566F(any p0, float p1)l
extern _native void unk_0xA7DF64D7(any p0, float p1)l
extern _native void unk_0xDD7936F5(any p0, float p1)l
extern _native bool unk_0x34E02FCD(vector3* outVec, any p1, vector3* outVec1, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native void set_vehicle_burnout(Vehicle vehicle, bool toggle)l
extern _native bool is_vehicle_in_burnout(Vehicle vehicle)l
extern _native void set_vehicle_reduce_grip(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_indicator_lights(Vehicle vehicle, int turnSignal, bool toggle)l
extern _native void set_vehicle_brake_lights(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_handbrake(Vehicle vehicle, bool toggle)l
extern _native void unk_0x37BC6ACB()l
extern _native bool unk_0x71D898EF()l
extern _native void unk_0x0B0523B0(bool p0)l
extern _native bool get_vehicle_trailer_vehicle(Vehicle vehicle, Vehicle* trailer)l
extern _native void unk_0x0B200CE2(Vehicle vehicle, bool p1)l
extern _native void set_vehicle_rudder_broken(Vehicle vehicle, bool p1)l
extern _native void unk_0x0858678C(Vehicle vehicle, bool p1)l
extern _native float unk_0x7D1A0616(Vehicle vehicle)l
extern _native float get_vehicle_max_braking(Vehicle vehicle)l
extern _native float get_vehicle_max_traction(Vehicle vehicle)l
extern _native float get_vehicle_acceleration(Vehicle vehicle)l
extern _native32(0x8F291C4A) float _get_vehicle_model_max_speed(Hash modelHash)l
extern _native float get_vehicle_model_max_braking(Hash modelHash)l
extern _native float unk_0xF3A7293F(Hash modelHash)l
extern _native float get_vehicle_model_max_traction(Hash modelHash)l
extern _native float get_vehicle_model_acceleration(Hash modelHash)l
extern _native float unk_0x37FBA7BC(Hash modelHash)l
extern _native float unk_0x95BB67EB(Hash modelHash)l
extern _native float unk_0x87C5D271(Hash modelHash)l
extern _native float unk_0xCE67162C(int vehicleClass)l
extern _native float get_vehicle_class_max_traction(int vehicleClass)l
extern _native float get_vehicle_class_max_agility(int vehicleClass)l
extern _native float get_vehicle_class_max_acceleration(int vehicleClass)l
extern _native float get_vehicle_class_max_braking(int vehicleClass)l
extern _native any unk_0xD6685803(float p0, float p1, float p2, float p3, float p4, bool p5)l
extern _native bool unk_0x0C0332A6(any p0)l
extern _native void open_bomb_bay_doors(Vehicle vehicle)l
extern _native void close_bomb_bay_doors(Vehicle vehicle)l
extern _native bool is_vehicle_searchlight_on(Vehicle vehicle)l
extern _native void set_vehicle_searchlight(Vehicle heli, bool toggle, bool canBeUsedByAI)l
extern _native bool unk_0xAB0E79EB(Ped ped, Vehicle vehicle, bool p2, bool p3, bool p4)l
extern _native bool can_shuffle_seat(Vehicle vehicle, any p1)l
extern _native int get_num_mod_kits(Vehicle vehicle)l
extern _native void set_vehicle_mod_kit(Vehicle vehicle, int modKit)l
extern _native int get_vehicle_mod_kit(Vehicle vehicle)l
extern _native int get_vehicle_mod_kit_type(Vehicle vehicle)l
extern _native int get_vehicle_wheel_type(Vehicle vehicle)l
extern _native void set_vehicle_wheel_type(Vehicle vehicle, int WheelType)l
extern _native int get_num_mod_colors(int p0, bool p1)l
extern _native void set_vehicle_mod_color_1(Vehicle vehicle, int paintType, int color, int p3)l
extern _native void set_vehicle_mod_color_2(Vehicle vehicle, int paintType, int color)l
extern _native void get_vehicle_mod_color_1(Vehicle vehicle, int* paintType, int* color, int* p3)l
extern _native void get_vehicle_mod_color_2(Vehicle vehicle, int* paintType, int* color)l
extern _native const char* get_vehicle_mod_color_1_name(Vehicle vehicle, bool p1)l
extern _native const char* get_vehicle_mod_color_2_name(Vehicle vehicle)l
extern _native bool unk_0x112D637A(Vehicle vehicle)l
extern _native void set_vehicle_mod(Vehicle vehicle, int modType, int modIndex, bool customTires)l
extern _native int get_vehicle_mod(Vehicle vehicle, int modType)l
extern _native bool get_vehicle_mod_variation(Vehicle vehicle, int modType)l
extern _native int get_num_vehicle_mods(Vehicle vehicle, int modType)l
extern _native void remove_vehicle_mod(Vehicle vehicle, int modType)l
extern _native void toggle_vehicle_mod(Vehicle vehicle, int modType, bool toggle)l
extern _native bool is_toggle_mod_on(Vehicle vehicle, int modType)l
extern _native const char* get_mod_text_label(Vehicle vehicle, int modType, int modValue)l
extern _native const char* get_mod_slot_name(Vehicle vehicle, int modType)l
extern _native const char* get_livery_name(Vehicle vehicle, int liveryIndex)l
extern _native any get_vehicle_mod_modifier_value(Vehicle vehicle, int modType, int modIndex)l
extern _native32(0x94850968) any _get_vehicle_mod_data(Vehicle vehicle, int modType, int modIndex)l
extern _native void preload_vehicle_mod(any p0, any p1, any p2)l
extern _native bool has_preload_mods_finished(any p0)l
extern _native void release_preload_mods(Vehicle vehicle)l
extern _native void set_vehicle_tyre_smoke_color(Vehicle vehicle, RGB colour)l
extern _native void get_vehicle_tyre_smoke_color(Vehicle vehicle, int* r, int* g, int* b)l
extern _native void set_vehicle_window_tint(Vehicle vehicle, int tint)l
extern _native int get_vehicle_window_tint(Vehicle vehicle)l
extern _native int get_num_vehicle_window_tints()l
extern _native void get_vehicle_color(Vehicle vehicle, int* r, int* g, int* b)l
extern _native int unk_0x749DEEA2(Vehicle vehicle)l
extern _native Hash get_vehicle_cause_of_destruction(Vehicle vehicle)l
extern _native bool get_is_left_vehicle_headlight_damaged(Vehicle vehicle)l
extern _native bool get_is_right_vehicle_headlight_damaged(Vehicle vehicle)l
extern _native32(0xE943B09C) void _set_vehicle_engine_power_multiplier(Vehicle vehicle, float value)l
extern _native void unk_0xDF594D8D(Vehicle vehicle, bool toggle)l
extern _native void unk_0x4D840FC4(Vehicle vehicle, bool p1)l
extern _native any unk_0x5AB26C2B(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native void unk_0xEF05F807(any p0)l
extern _native32(0xD656E7E5) bool _any_passengers_rappeling(Vehicle vehicle)l
extern _native32(0x642DA5AA) void _set_vehicle_engine_torque_multiplier(Vehicle vehicle, float value)l
extern _native void unk_0x04F5546C(any p0, bool p1)l
extern _native void set_vehicle_is_wanted(Vehicle vehicle, bool state)l
extern _native void unk_0xA25CCB8C(any p0, float p1)l
extern _native void unk_0x00966934(any p0, bool p1)l
extern _native void unk_0x113DF5FD(any p0, bool p1)l
extern _native float unk_0x7C8D6464(Vehicle vehicle)l
extern _native void disable_plane_aileron(Vehicle vehicle, bool p1, bool p2)l
extern _native bool get_is_vehicle_engine_running(Vehicle vehicle)l
extern _native void unk_0xA03E42DF(Vehicle vehicle, bool p1)l
extern _native32(0x15D40761) void _set_bike_lean_angle(Vehicle vehicle, vector2 vector)l
extern _native void unk_0x1984F88D(Vehicle vehicle, bool p1)l
extern _native void unk_0x3FBE904F(Vehicle vehicle)l
extern _native void set_last_driven_vehicle(Vehicle vehicle)l
extern _native Vehicle get_last_driven_vehicle()l
extern _native void unk_0x08CD58F9(any p0, bool p1)l
extern _native32(0x8C4B63E2) void _set_plane_min_height_above_ground(Vehicle plane, int height)l
extern _native void set_vehicle_lod_multiplier(Vehicle vehicle, float multiplier)l
extern _native void unk_0x1604C2F5(Vehicle vehicle, bool p1)l
extern _native any unk_0x8CDB0C09(any p0)l
extern _native any unk_0xABC99E21(any p0)l
extern _native void unk_0x900C878C(any p0, bool p1)l
extern _native void unk_0xB3200F72(any p0, bool p1)l
extern _native void unk_0xBAE491C7(Vehicle vehicle, Vehicle vehicle2)l
extern _native void unk_0xF0E59BC1()l
extern _native void unk_0x929801C6(float p0)l
extern _native void set_vehicle_shoot_at_target(Ped driver, Entity entity, vector3 Target)l
extern _native32(0x4A557117) bool _get_vehicle_owner(Vehicle vehicle, Entity* entity)l
extern _native void set_force_hd_vehicle(Vehicle vehicle, bool toggle)l
extern _native void unk_0x7D0DE7EA(Vehicle vehicle, float p1)l
extern _native int get_vehicle_plate_type(Vehicle vehicle)l
extern _native void track_vehicle_visibility(Vehicle vehicle)l
extern _native bool is_vehicle_visible(Vehicle vehicle)l
extern _native void set_vehicle_gravity(Vehicle vehicle, bool toggle)l
extern _native void unk_0xD2B8ACBD(bool p0)l
extern _native any unk_0xA4A75FCF(any p0)l
extern _native void unk_0x50F89338(any p0, bool p1)l
extern _native void unk_0xEB7D7C27(any p0, bool p1)l
extern _native32(0x5EB00A6A) bool _is_vehicle_shop_respray_allowed(Vehicle vehicle)l
extern _native void set_vehicle_engine_can_degrade(Vehicle vehicle, bool toggle)l
extern _native void unk_0x5BD8D82D(Vehicle vehicle, int p1, int p2)l
extern _native void unk_0x450AD03A(any p0)l
extern _native32(0xBD085DCA) bool _vehicle_has_landing_gear(Vehicle vehicle)l
extern _native32(0xABBDD5C6) bool _are_propellers_undamaged(Vehicle vehicle)l
extern _native void unk_0x9B581DE7(Vehicle vehicle, bool p1)l
extern _native bool is_vehicle_stolen(Vehicle vehicle)l
extern _native any set_vehicle_is_stolen(Vehicle vehicle, bool isStolen)l
extern _native void unk_0xED159AE6(Vehicle vehicle, float p1)l
extern _native bool add_a_marker_over_vehicle(Vehicle vehicle)l
extern _native void unk_0x45F72495(Vehicle vehicle)l
extern _native void detach_vehicle_from_cargobob(Vehicle vehicle, Vehicle cargobob)l
extern _native bool detach_vehicle_from_any_cargobob(Vehicle vehicle)l
extern _native bool is_vehicle_attached_to_cargobob(Vehicle cargobob, Vehicle vehicleAttached)l
extern _native Vehicle get_vehicle_attached_to_cargobob(Vehicle cargobob)l
extern _native void attach_vehicle_to_cargobob(Vehicle vehicle, Vehicle cargobob, int p2, vector3 vec)l
extern _native bool does_cargobob_have_pick_up_rope(Vehicle cargobob)l
extern _native void create_pick_up_rope_for_cargobob(Vehicle cargobob, int state)l
extern _native void remove_pick_up_rope_for_cargobob(Vehicle cargobob)l
extern _native32(0x3A8AB081) void _set_cargobob_hook_position(any p0, float p1, float p2, int state)l
extern _native bool does_cargobob_have_pickup_magnet(Vehicle cargobob)l
extern _native void set_cargobob_pickup_magnet_active(Vehicle cargobob, bool isActive)l
extern _native void set_cargobob_pickup_magnet_strength(Vehicle cargobob, float strength)l
extern _native bool does_vehicle_have_weapons(Vehicle vehicle)l
extern _native void unk_0x2EC19A8B(any p0, bool p1)l
extern _native void disable_vehicle_weapon(bool disabled, Hash weaponHash, Vehicle vehicle, Ped owner)l
extern _native void unk_0x123E5B90(any p0, bool p1)l
extern _native void unk_0xEBC225C1(any p0, bool p1)l
extern _native int get_vehicle_class(Vehicle vehicle)l
extern _native int get_vehicle_class_from_name(Hash modelHash)l
extern _native any set_players_last_vehicle(Vehicle vehicle)l
extern _native void set_vehicle_can_be_used_by_fleeing_peds(Vehicle vehicle, bool toggle)l
extern _native void unk_0xB6BE07E0(Vehicle vehicle, float p1)l
extern _native32(0x4BB5605D) void _set_vehicle_creates_money_pickups_when_exploded(Vehicle vehicle, bool toggle)l
extern _native32(0x51E0064F) void _set_vehicle_jet_engine_on(Vehicle vehicle, bool toggle)l
extern _native void unk_0xAEF9611C(any p0, any p1)l
extern _native void unk_0x585E49B6(any p0, float p1)l
extern _native32(0x6E67FD35) void _set_helicopter_roll_pitch_yaw_mult(Vehicle helicopter, float multiplier)l
extern _native void set_vehicle_friction_override(Vehicle vehicle, float friction)l
extern _native void set_vehicle_wheels_can_break_off_when_blow_up(Vehicle vehicle, bool toggle)l
extern _native void set_vehicle_ceiling_height(Vehicle vehicle, float p1)l
extern _native void unk_0xBC649C49(Vehicle vehicle, bool toggle)l
extern _native void unk_0x8DD9AA0C(Vehicle vehicle)l
extern _native bool does_vehicle_exist_with_decorator(const char* decorator)l
extern _native void set_vehicle_exclusive_driver(Vehicle vehicle, bool p1)l
extern _native32(0xB5CC548B) void _display_distant_vehicles(bool toggle)l
extern _native float get_vehicle_body_health(Vehicle vehicle)l
extern _native void set_vehicle_body_health(Vehicle vehicle, float value)l
extern _native32(0xB73A1486) float _get_vehicle_suspension_height(Vehicle vehicle)l
#pragma endregion //}
#pragma region OBJECT //{
extern _native Object create_object(Object modelHash, vector3 vec, bool isNetwork, bool p5, bool dynamic)l
extern _native Object create_object_no_offset(Hash modelHash, vector3 vec, bool isNetwork, bool p5, bool dynamic)l
extern _native void delete_object(Object* object)l
extern _native bool place_object_on_ground_properly(Object object)l
extern _native bool slide_object(Object object, vector3 to, vector3 speed, bool collision)l
extern _native any set_object_targettable(Object object, bool targettable)l
extern _native void unk_0x483C5C88(Object object, bool p1)l
extern _native Object get_closest_object_of_type(vector3 vec, float radius, Hash modelHash, bool isMission, bool p6, bool p7)l
extern _native bool has_object_been_broken(Object object)l
extern _native bool has_closest_object_of_type_been_broken(float p0, float p1, float p2, float p3, Hash modelHash, any p5)l
extern _native bool unk_0x7DB578DD(float p0, float p1, float p2, float p3, Hash modelHash, bool p5)l
extern _native32(0x87A42A12) vector3 _get_object_offset_from_coords(vector3 Pos, float heading, vector3 Offset)l
extern _native any unk_0x65213FC3(any coords, float radius, Hash modelHash, vector3 vec, vector3* p6, int p7)l
extern _native void set_state_of_closest_door_of_type(Hash type, vector3 vec, bool locked, float heading, bool p6)l
extern _native void get_state_of_closest_door_of_type(Hash type, vector3 vec, bool* locked, float* heading)l
extern _native32(0x4E0A260B) void _door_control(Hash doorHash, vector3 vec, bool locked, float p5, float p6, float p7)l
extern _native void add_door_to_system(Hash doorHash, Hash modelHash, vector3 vec, bool p5, bool p6, bool p7)l
extern _native void remove_door_from_system(Hash doorHash)l
extern _native32(0xDF83DB47) void _set_door_acceleration_limit(Hash doorHash, int limit, bool p2, bool p3)l
extern _native int unk_0xD42A41C2(Hash doorHash)l
extern _native int unk_0xD649B7E1(Hash doorHash)l
extern _native void unk_0x4F44AF21(Hash doorHash, float p1, bool p2, bool p3)l
extern _native void unk_0x47531446(Hash doorHash, float heading, bool p2, bool p3)l
extern _native32(0x34883DE3) void _set_door_ajar_angle(Hash doorHash, float ajar, bool p2, bool p3)l
extern _native float unk_0xB74C3BD7(Hash doorHash)l
extern _native void unk_0xB4A9A558(Hash doorHash, bool p1, bool p2, bool p3)l
extern _native void unk_0xECE58AE0(Hash doorHash, bool p1)l
extern _native void unk_0xF736227C(Hash doorHash, bool p1)l
extern _native32(0x5AFCD8A1) bool _does_door_exist(Hash doorHash)l
extern _native bool is_door_closed(Hash door)l
extern _native void unk_0x9BF33E41(bool p0)l
extern _native void unk_0xF592AD10()l
extern _native bool unk_0x17FF9393(any p0)l
extern _native bool unk_0xE9AE494F(float p0, float p1, float p2, any p3, any* p4)l
extern _native bool is_garage_empty(any garage, bool p1, int p2)l
extern _native bool unk_0xC33ED360(any p0, Player player, float p2, int p3)l
extern _native bool unk_0x41924877(any p0, Player player, int p2)l
extern _native bool unk_0x4BD59750(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native bool unk_0x7B44D659(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native bool unk_0x142C8F76(any p0, Entity entity, float p2, int p3)l
extern _native bool unk_0x95A9AB2B(any p0, Entity entity, int p2)l
extern _native void unk_0xA565E27E(any p0, bool p1, bool p2, bool p3, bool p4)l
extern _native void unk_0x43BB7E48(Hash hash, bool toggle)l
extern _native void unk_0x6158959E()l
extern _native bool does_object_of_type_exist_at_coords(vector3 vec, float radius, Hash hash, bool p5)l
extern _native bool is_point_in_angled_area(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, bool p10, bool p11)l
extern _native void unk_0x19B17769(Object object, bool toggle)l
extern _native void set_object_physics_params(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy)l
extern _native float get_object_fragment_damage_health(any p0, bool p1)l
extern _native void set_activate_object_physics_as_soon_as_it_is_unfrozen(Object object, bool toggle)l
extern _native bool is_any_object_near_point(vector3 vec, float range, bool p4)l
extern _native bool is_object_near_point(Hash objectHash, vector3 vec, float range)l
extern _native void unk_0xE3261B35(any p0)l
extern _native void unk_0x1E82C2AE(Object p0, any p1, bool p2)l
extern _native void track_object_visibility(any p0)l
extern _native bool is_object_visible(Object object)l
extern _native void unk_0xF4A1A14A(any p0, bool p1)l
extern _native void unk_0xAF016CC1(any p0, bool p1)l
extern _native void unk_0x3A68AA46(any p0, bool p1)l
extern _native32(0xA286DE96) int _get_des_object(vector3 vec, float rotation, const char* name)l
extern _native32(0x21F51560) void _set_des_object_state(int handle, int state)l
extern _native32(0xF1B8817A) any _get_des_object_state(int handle)l
extern _native32(0xE08C834D) bool _does_des_object_exist(int handle)l
extern _native float unk_0x020497DE(any p0)l
extern _native Pickup create_pickup(Hash pickupHash, vector3 pos, int p4, int value, bool p6, Hash modelHash)l
extern _native Pickup create_pickup_rotate(Hash pickupHash, vector3 pos, vector3 rot, int flag, int amount, any p9, bool p10, Hash modelHash)l
extern _native Pickup create_ambient_pickup(Hash pickupHash, vector3 pos, int p4, int value, Hash modelHash, bool p7, bool p8)l
extern _native Pickup create_portable_pickup(Hash pickupHash, vector3 vec, bool placeOnGround, Hash modelHash)l
extern _native32(0x56A02502) Pickup _create_portable_pickup_2(Hash pickupHash, vector3 vec, bool placeOnGround, Hash modelHash)l
extern _native void attach_portable_pickup_to_ped(Ped ped, any p1)l
extern _native void detach_portable_pickup_from_ped(Ped ped)l
extern _native void unk_0x7EFBA039(any p0, int p1)l
extern _native void unk_0xA3CDF152(bool p0)l
extern _native vector3 get_safe_pickup_coords(vector3 vec, any p3, any p4)l
extern _native vector3 get_pickup_coords(Pickup pickup)l
extern _native void remove_all_pickups_of_type(Hash pickupHash)l
extern _native bool has_pickup_been_collected(Pickup pickup)l
extern _native void remove_pickup(Pickup pickup)l
extern _native void create_money_pickups(vector3 vec, int value, int amount, Hash model)l
extern _native bool does_pickup_exist(Pickup pickup)l
extern _native bool does_pickup_object_exist(Object pickupObject)l
extern _native Object get_pickup_object(Pickup pickup)l
extern _native32(0xF139681B) bool _is_pickup_within_radius(Hash pickupHash, vector3 vec, float radius)l
extern _native void set_pickup_regeneration_time(any p0, any p1)l
extern _native void unk_0x7FADB4B9(Player player, Hash pickupHash, bool p2)l
extern _native void unk_0x3A8F1BF7(Hash p0, bool p1)l
extern _native void set_team_pickup_object(Object object, any p1, bool p2)l
extern _native void unk_0xCBB5F9B6(Object object, bool p1, bool p2)l
extern _native void unk_0x276A7807(any p0, float p1, bool p2)l
extern _native any unk_0x000E92DC(any p0)l
extern _native void unk_0x9879AC51(float p0)l
extern _native void unk_0xDB18FA01(bool p0)l
extern _native void unk_0xA7E936FD(any p0, any p1)l
extern _native void unk_0xB241806C()l
extern _native void unk_0xD1BAAFB7(any p0)l
extern _native32(0x63B02FAD) void _highlight_placement_coords(vector3 vec, int colorIndex)l
extern _native void unk_0x132B6D92(Object object, bool toggle)l
extern _native32(0xEDD01937) Hash _get_weapon_hash_from_pickup(Pickup pickupHash)l
extern _native Hash unk_0x6AE36192(Pickup pickupHash)l
extern _native void set_force_object_this_frame(any p0, any p1, any p2, any p3)l
extern _native32(0x2048A7DD) void _mark_object_for_deletion(Object object)l
#pragma endregion //}
#pragma region AI //{
extern _native void task_pause(Ped ped, int ms)l
extern _native void task_stand_still(Ped ped, int time)l
extern _native void task_jump(Ped ped, bool unused)l
extern _native void task_cower(Ped ped, int duration)l
extern _native void task_hands_up(Ped ped, int duration, Ped facingPed, int p3, bool p4)l
extern _native void update_task_hands_up_duration(Ped ped, int duration)l
extern _native void task_open_vehicle_door(Ped ped, Vehicle vehicle, int timeOut, int doorIndex, float speed)l
extern _native void task_enter_vehicle(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int p5, any p6)l
extern _native void task_leave_vehicle(Ped ped, Vehicle vehicle, int flags)l
extern _native void task_sky_dive(Ped ped)l
extern _native void task_parachute(Ped ped, bool p1)l
extern _native void task_parachute_to_target(Ped ped, vector3 vec)l
extern _native void set_parachute_task_target(Ped ped, vector3 vec)l
extern _native void set_parachute_task_thrust(Ped ped, float thrust)l
extern _native void task_rappel_from_heli(Ped ped, int unused)l
extern _native void task_vehicle_drive_to_coord(Ped ped, Vehicle vehicle, vector3 vec, float speed, any p6, Hash vehicleModel, int drivingMode, float stopRange, float p10)l
extern _native void task_vehicle_drive_to_coord_longrange(Ped ped, Vehicle vehicle, vector3 vec, float speed, int driveMode, float stopRange)l
extern _native void task_vehicle_drive_wander(Ped ped, Vehicle vehicle, float speed, int drivingStyle)l
extern _native void task_follow_to_offset_of_entity(Ped ped, Entity entity, vector3 offset, float movementSpeed, int timeout, float stoppingRange, bool persistFollowing)l
extern _native void task_go_straight_to_coord(Ped ped, vector3 vec, float speed, int timeout, float targetHeading, float distanceToSlide)l
extern _native void task_go_straight_to_coord_relative_to_entity(Entity entity1, Entity entity2, float p2, float p3, float p4, float p5, any p6)l
extern _native void task_achieve_heading(Ped ped, float heading, int timeout)l
extern _native void task_flush_route()l
extern _native void task_extend_route(vector3 vec)l
extern _native void task_follow_point_route(Ped ped, float speed, int unknown)l
extern _native void task_go_to_entity(Entity entity, Entity target, int duration, float distance, float speed, float p5, int p6)l
extern _native void task_smart_flee_coord(Ped ped, vector3 vec, float distance, int time, bool p6, bool p7)l
extern _native void task_smart_flee_ped(Ped ped, Ped fleeTarget, float distance, any fleeTime, bool p4, bool p5)l
extern _native void task_react_and_flee_ped(Ped ped, Ped fleeTarget)l
extern _native void task_shocking_event_react(Ped ped, int eventHandle)l
extern _native void task_wander_in_area(Ped ped, vector3 vec, float radius, float minimalLength, float timeBetweenWalks)l
extern _native void task_wander_standard(Ped ped, float p1, int p2)l
extern _native void task_vehicle_park(Ped ped, Vehicle vehicle, vector3 vec, float heading, int mode, float radius, bool keepEngineOn)l
extern _native any task_stealth_kill(Ped killer, Ped target, Hash killType, float p3, bool p4)l
extern _native void task_plant_bomb(Ped ped, vector3 vec, float heading)l
extern _native void task_follow_nav_mesh_to_coord(Ped ped, vector3 vec, float speed, int timeout, float stoppingRange, bool persistFollowing, float unk)l
extern _native void task_follow_nav_mesh_to_coord_advanced(Ped ped, vector3 vec, float speed, int timeout, float unkFloat, int unkInt, vector3 unk, float unk_40000f)l
extern _native any set_ped_path_can_use_climbovers(Ped ped, bool Toggle)l
extern _native any set_ped_path_can_use_ladders(Ped ped, bool Toggle)l
extern _native void set_ped_path_can_drop_from_height(Ped ped, bool Toggle)l
extern _native void unk_0x55E06443(Ped ped, float p1)l
extern _native void set_ped_paths_width_plant(Ped ped, bool mayEnterWater)l
extern _native void set_ped_path_prefer_to_avoid_water(Ped ped, bool avoidWater)l
extern _native void set_ped_path_avoid_fire(Ped ped, bool avoidFire)l
extern _native void set_global_min_bird_flight_height(float height)l
extern _native any get_navmesh_route_distance_remaining(Ped ped, any* p1, any* p2)l
extern _native int get_navmesh_route_result(Ped ped)l
extern _native void task_go_to_coord_any_means(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8)l
extern _native void task_go_to_coord_any_means_extra_params(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8, any p9, any p10, any p11)l
extern _native void task_go_to_coord_any_means_extra_params_with_cruise_speed(Ped ped, vector3 vec, float speed, any p5, bool p6, int walkingStyle, float p8, any p9, any p10, any p11, any p12)l
extern _native void task_play_anim(Ped ped, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, bool lockX, bool lockY, bool lockZ)l
extern _native void task_play_anim_advanced(Ped ped, const char* animDict, const char* animName, vector3 pos, vector3 rot, float speed, float speedMultiplier, int duration, any flag, float animTime, any p14, any p15)l
extern _native void stop_anim_task(Ped ped, const char* animDictionary, const char* animationName, float p3)l
extern _native void task_scripted_animation(Ped ped, any* p1, any* p2, any* p3, float p4, float p5)l
extern _native void play_entity_scripted_anim(any p0, any* p1, any* p2, any* p3, float p4, float p5)l
extern _native void stop_anim_playback(Ped ped, any p1, bool p2)l
extern _native void set_anim_weight(any p0, float p1, any p2, any p3, bool p4)l
extern _native void set_anim_rate(any p0, float p1, any p2, bool p3)l
extern _native void set_anim_looped(any p0, bool p1, any p2, bool p3)l
extern _native void task_play_phone_gesture_animation(Ped ped, const char* animDict, const char* animation, const char* boneMaskType, float p4, float p5, bool p6, bool p7)l
extern _native bool is_playing_phone_gesture_anim(Ped ped)l
extern _native float get_phone_gesture_anim_current_time(Ped ped)l
extern _native float get_phone_gesture_anim_total_time(Ped ped)l
extern _native void task_vehicle_play_anim(Vehicle vehicle, const char* animation_set, const char* animation_name)l
extern _native void task_look_at_coord(Entity entity, vector3 vec, float duration, any p5, any p6)l
extern _native void task_look_at_entity(Ped ped, Entity lookAt, int duration, int unknown1, int unknown2)l
extern _native void task_clear_look_at(Ped ped)l
extern _native any open_sequence_task(Object* taskSequence)l
extern _native any close_sequence_task(Object taskSequence)l
extern _native any task_perform_sequence(Ped ped, Object taskSequence)l
extern _native any clear_sequence_task(Object* taskSequence)l
extern _native void set_sequence_to_repeat(Object taskSequence, bool repeat)l
extern _native int get_sequence_progress(Ped ped)l
extern _native bool get_is_task_active(Ped ped, int taskNumber)l
extern _native int get_script_task_status(Ped targetPed, Hash taskHash)l
extern _native int get_active_vehicle_mission_type(Vehicle veh)l
extern _native void task_leave_any_vehicle(Ped ped, int p1, int p2)l
extern _native void task_aim_gun_scripted(Ped ped, Hash scriptTask, bool p2, bool p3)l
extern _native void task_aim_gun_scripted_with_target(any p0, any p1, float p2, float p3, float p4, any p5, bool p6, bool p7)l
extern _native void update_task_aim_gun_scripted_target(Ped p0, Ped p1, float p2, float p3, float p4, bool p5)l
extern _native const char* get_clip_set_for_scripted_gun_task(int p0)l
extern _native void task_aim_gun_at_entity(Ped ped, Entity entity, int duration, bool p3)l
extern _native void task_turn_ped_to_face_entity(Ped ped, Entity entity, int duration)l
extern _native void task_aim_gun_at_coord(Ped ped, vector3 vec, int time, bool p5, bool p6)l
extern _native void task_shoot_at_coord(Ped ped, vector3 vec, int duration, Hash firingPattern)l
extern _native void task_shuffle_to_next_vehicle_seat(Ped ped, Vehicle vehicle)l
extern _native void clear_ped_tasks(Ped ped)l
extern _native void clear_ped_secondary_task(Ped ped)l
extern _native void task_everyone_leave_vehicle(Vehicle vehicle)l
extern _native void task_goto_entity_offset(Ped ped, any p1, any p2, vector3 vec, int duration)l
extern _native void task_goto_entity_offset_xy(any p0, any p1, any p2, float p3, float p4, float p5, float p6, any p7)l
extern _native void task_turn_ped_to_face_coord(Ped ped, vector3 vec, int duration)l
extern _native void task_vehicle_temp_action(Ped driver, Vehicle vehicle, int action, int time)l
extern _native void task_vehicle_mission(any p0, any p1, any p2, any p3, float p4, any p5, float p6, float p7, bool p8)l
extern _native void task_vehicle_mission_ped_target(Ped ped, Vehicle vehicle, Ped pedTarget, int mode, float maxSpeed, int drivingStyle, float minDistance, float p7, bool p8)l
extern _native void task_vehicle_mission_coors_target(Ped ped, Vehicle vehicle, vector3 vec, int p5, int p6, int p7, float p8, float p9, bool p10)l
extern _native void task_vehicle_escort(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int p7, float noRoadsDistance)l
extern _native void task_vehicle_chase(Ped driver, Entity targetEnt)l
extern _native void task_vehicle_heli_protect(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int p4, float radius, int altitude, int p7)l
extern _native void set_task_vehicle_chase_behavior_flag(Ped ped, int flag, bool set)l
extern _native void set_task_vehicle_chase_ideal_pursuit_distance(Ped ped, float distance)l
extern _native void task_heli_chase(Ped pilot, Entity entityToFollow, vector3 vec)l
extern _native void task_plane_chase(Ped pilot, Entity entityToFollow, vector3 vec)l
extern _native void task_plane_land(Ped pilot, Vehicle plane, vector3 runwayStart, vector3 runwayEnd)l
extern _native void task_heli_mission(Ped pilot, Vehicle vehicle, Vehicle vehicleToFollow, Ped pedToFollow, vector3 pos, int mode, float speed, float radius, float angle, int p11, int height, float p13, int p14)l
extern _native void task_plane_mission(Ped pilot, Vehicle plane, Vehicle targetVehicle, Ped targetPed, vector3 destination, int missionType, float vehicleSpeed, float p9, float heading, float maxAltitude, float minAltitude)l
extern _native void task_boat_mission(Ped pedDriver, Vehicle boat, any p2, any p3, vector3 vec, any p7, float maxSpeed, int drivingStyle, float p10, any p11)l
extern _native void task_drive_by(Ped driverPed, Ped targetPed, Vehicle targetVehicle, vector3 target, float distanceToShoot, int pedAccuracy, bool p8, Hash firingPattern)l
extern _native void set_driveby_task_target(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, vector3 vec)l
extern _native void clear_driveby_task_underneath_driving_task(Ped ped)l
extern _native bool is_driveby_task_underneath_driving_task(Ped ped)l
extern _native bool control_mounted_weapon(Ped ped)l
extern _native void set_mounted_weapon_target(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, vector3 vec)l
extern _native bool is_mounted_weapon_task_underneath_driving_task(Ped ped)l
extern _native void task_use_mobile_phone(Ped ped, int p1)l
extern _native void task_use_mobile_phone_timed(Ped ped, int duration)l
extern _native void task_chat_to_ped(Ped ped, Ped target, any p2, float p3, float p4, float p5, float p6, float p7)l
extern _native void task_warp_ped_into_vehicle(Ped ped, Vehicle vehicle, int seat)l
extern _native void task_shoot_at_entity(Entity entity, Entity target, int duration, Hash firingPattern)l
extern _native void task_climb(Ped ped, bool unused)l
extern _native void task_climb_ladder(Ped ped, int p1)l
extern _native void clear_ped_tasks_immediately(Ped ped)l
extern _native void task_perform_sequence_from_progress(any p0, any p1, any p2, any p3)l
extern _native void set_next_desired_move_state(float p0)l
extern _native void set_ped_desired_move_blend_ratio(Ped ped, float p1)l
extern _native float get_ped_desired_move_blend_ratio(Ped ped)l
extern _native void task_goto_entity_aiming(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist)l
extern _native void task_set_decision_maker(Ped p0, Hash p1)l
extern _native void task_set_sphere_defensive_area(any p0, float p1, float p2, float p3, float p4)l
extern _native void task_clear_defensive_area(any p0)l
extern _native void task_ped_slide_to_coord(Ped ped, vector3 vec, float heading, float p5)l
extern _native void task_ped_slide_to_coord_hdg_rate(Ped ped, vector3 vec, float heading, float p5, float p6)l
extern _native ScrHandle add_cover_point(float p0, float p1, float p2, float p3, any p4, any p5, any p6, bool p7)l
extern _native void remove_cover_point(ScrHandle coverpoint)l
extern _native bool does_scripted_cover_point_exist_at_coords(vector3 vec)l
extern _native vector3 get_scripted_cover_point_coords(ScrHandle coverpoint)l
extern _native void task_combat_ped(Ped ped, Ped targetPed, int p2, int p3)l
extern _native void task_combat_ped_timed(any p0, Ped ped, int p2, any p3)l
extern _native void task_seek_cover_from_pos(Ped ped, vector3 vec, int duration, bool p5)l
extern _native void task_seek_cover_from_ped(Ped ped, Ped target, int duration, bool p3)l
extern _native void task_seek_cover_to_cover_point(any p0, any p1, float p2, float p3, float p4, any p5, bool p6)l
extern _native void task_seek_cover_to_coords(Ped ped, vector3 vec_1, vector3 vec_2, any p7, bool p8)l
extern _native void task_put_ped_directly_into_cover(Ped ped, vector3 vec, any timeout, bool p5, float p6, bool p7, bool p8, any p9, bool p10)l
extern _native void task_exit_cover(any p0, any p1, float p2, float p3, float p4)l
extern _native void task_put_ped_directly_into_melee(Ped ped, Ped meleeTarget, float p2, float p3, float p4, bool p5)l
extern _native void task_toggle_duck(bool p0, bool p1)l
extern _native void task_guard_current_position(Ped p0, float p1, float p2, bool p3)l
extern _native void task_guard_assigned_defensive_area(any p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native void task_guard_sphere_defensive_area(Ped p0, float p1, float p2, float p3, float p4, float p5, any p6, float p7, float p8, float p9, float p10)l
extern _native void task_stand_guard(Ped ped, vector3 vec, float heading, const char* scenarioName)l
extern _native void set_drive_task_cruise_speed(Ped driver, float cruiseSpeed)l
extern _native void set_drive_task_max_cruise_speed(any p0, float p1)l
extern _native void set_drive_task_driving_style(Ped ped, int drivingStyle)l
extern _native void add_cover_blocking_area(vector3 player, vector3 radius, bool p6, bool p7, bool p8, bool p9)l
extern _native void remove_all_cover_blocking_areas()l
extern _native void task_start_scenario_in_place(Ped ped, const char* scenarioName, int unkDelay, bool playEnterAnim)l
extern _native void task_start_scenario_at_position(Ped ped, const char* scenarioName, vector3 vec, float heading, int duration, bool sittingScenario, bool teleport)l
extern _native void task_use_nearest_scenario_to_coord(Ped ped, vector3 vec, float distance, int duration)l
extern _native void task_use_nearest_scenario_to_coord_warp(Ped ped, vector3 vec, float radius, any p5)l
extern _native void task_use_nearest_scenario_chain_to_coord(any p0, float p1, float p2, float p3, float p4, any p5)l
extern _native void task_use_nearest_scenario_chain_to_coord_warp(any p0, float p1, float p2, float p3, float p4, any p5)l
extern _native bool does_scenario_exist_in_area(vector3 vec, float radius, bool b)l
extern _native bool does_scenario_of_type_exist_in_area(float p0, float p1, float p2, any* p3, float p4, bool p5)l
extern _native bool is_scenario_occupied(float p0, float p1, float p2, float p3, bool p4)l
extern _native bool ped_has_use_scenario_task(Ped ped)l
extern _native void play_anim_on_running_scenario(Ped ped, const char* animDict, const char* animName)l
extern _native bool does_scenario_group_exist(const char* scenarioGroup)l
extern _native bool is_scenario_group_enabled(const char* scenarioGroup)l
extern _native void set_scenario_group_enabled(const char* scenarioGroup, bool p1)l
extern _native void reset_scenario_groups_enabled()l
extern _native void set_exclusive_scenario_group(const char* scenarioGroup)l
extern _native void reset_exclusive_scenario_group()l
extern _native bool is_scenario_type_enabled(const char* scenarioType)l
extern _native void set_scenario_type_enabled(const char* scenarioType, bool toggle)l
extern _native void reset_scenario_types_enabled()l
extern _native bool is_ped_active_in_scenario(Ped ped)l
extern _native void task_combat_hated_targets_in_area(Ped ped, vector3 vec, float radius, any p5)l
extern _native void task_combat_hated_targets_around_ped(Ped ped, float radius, int p2)l
extern _native void task_combat_hated_targets_around_ped_timed(any p0, float p1, any p2, any p3)l
extern _native void task_throw_projectile(int ped, vector3 vec)l
extern _native void task_swap_weapon(Ped ped, bool p1)l
extern _native void task_reload_weapon(Ped ped, bool unused)l
extern _native bool is_ped_getting_up(Ped ped)l
extern _native void task_writhe(Ped ped, Ped target, int time, int p3)l
extern _native bool is_ped_in_writhe(Ped ped)l
extern _native void open_patrol_route(const char* patrolRoute)l
extern _native void close_patrol_route()l
extern _native void add_patrol_route_node(int p0, const char* p1, vector3 vec_1, vector3 vec_2, int p8)l
extern _native void add_patrol_route_link(any p0, any p1)l
extern _native void create_patrol_route()l
extern _native void delete_patrol_route(const char* patrolRoute)l
extern _native void task_patrol(Ped ped, const char* p1, any p2, bool p3, bool p4)l
extern _native void task_stay_in_cover(Ped ped)l
extern _native void add_vehicle_subtask_attack_coord(Ped ped, vector3 vec)l
extern _native void add_vehicle_subtask_attack_ped(Ped ped, Ped ped2)l
extern _native void task_vehicle_shoot_at_ped(Ped ped, Ped target, float p2)l
extern _native void task_vehicle_aim_at_ped(Ped ped, Ped target)l
extern _native void task_vehicle_shoot_at_coord(Ped ped, vector3 vec, float p4)l
extern _native void task_vehicle_aim_at_coord(Ped ped, vector3 vec)l
extern _native void task_vehicle_goto_navmesh(Ped ped, Vehicle vehicle, vector3 vec, float speed, int behaviorFlag, float stoppingRange)l
extern _native void task_go_to_coord_while_aiming_at_coord(Ped ped, vector3 vec, vector3 aimAt, float moveSpeed, bool p8, float p9, float p10, bool p11, any flags, bool p13, Hash firingPattern)l
extern _native void task_go_to_coord_while_aiming_at_entity(any p0, float p1, float p2, float p3, any p4, float p5, bool p6, float p7, float p8, bool p9, any p10, bool p11, any p12, any p13)l
extern _native void task_go_to_coord_and_aim_at_hated_entities_near_coord(Ped pedHandle, vector3 goToLocation, vector3 focusLocation, float speed, bool shootAtEnemies, float distanceToStopAt, float noRoadsDistance, bool unkTrue, int unkFlag, int aimingFlag, Hash firingPattern)l
extern _native void task_go_to_entity_while_aiming_at_coord(any p0, any p1, float p2, float p3, float p4, float p5, bool p6, float p7, float p8, bool p9, bool p10, any p11)l
extern _native void task_go_to_entity_while_aiming_at_entity(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, bool shootatEntity, float p5, float p6, bool p7, bool p8, Hash firingPattern)l
extern _native void set_high_fall_task(Ped ped, any p1, any p2, any p3)l
extern _native void request_waypoint_recording(const char* name)l
extern _native bool get_is_waypoint_recording_loaded(const char* name)l
extern _native void remove_waypoint_recording(const char* name)l
extern _native bool waypoint_recording_get_num_points(const char* name, int* points)l
extern _native bool waypoint_recording_get_coord(const char* name, int point, vector3* coord)l
extern _native float waypoint_recording_get_speed_at_point(const char* name, int point)l
extern _native bool waypoint_recording_get_closest_waypoint(const char* name, vector3 vec, int* point)l
extern _native void task_follow_waypoint_recording(any p0, any p1, any p2, any p3, any p4)l
extern _native bool is_waypoint_playback_going_on_for_ped(any p0)l
extern _native any get_ped_waypoint_progress(any p0)l
extern _native float get_ped_waypoint_distance(any p0)l
extern _native any set_ped_waypoint_route_offset(any p0, any p1, any p2, any p3)l
extern _native float get_waypoint_distance_along_route(const char* p0, int p1)l
extern _native bool waypoint_playback_get_is_paused(any p0)l
extern _native void waypoint_playback_pause(any p0, bool p1, bool p2)l
extern _native void waypoint_playback_resume(any p0, bool p1, any p2, any p3)l
extern _native void waypoint_playback_override_speed(any p0, float p1, bool p2)l
extern _native void waypoint_playback_use_default_speed(any p0)l
extern _native void use_waypoint_recording_as_assisted_movement_route(any* p0, bool p1, float p2, float p3)l
extern _native void waypoint_playback_start_aiming_at_ped(any p0, any p1, bool p2)l
extern _native void waypoint_playback_start_aiming_at_coord(any p0, float p1, float p2, float p3, bool p4)l
extern _native void waypoint_playback_start_shooting_at_coord(any p0, float p1, float p2, float p3, bool p4, any p5)l
extern _native void waypoint_playback_stop_aiming_or_shooting(any p0)l
extern _native void assisted_movement_request_route(const char* route)l
extern _native void assisted_movement_remove_route(const char* route)l
extern _native bool assisted_movement_is_route_loaded(const char* route)l
extern _native void assisted_movement_set_route_properties(const char* route, int props)l
extern _native void assisted_movement_override_load_distance_this_frame(float dist)l
extern _native void task_vehicle_follow_waypoint_recording(Ped ped, Vehicle vehicle, const char* WPRecording, int p3, int p4, int p5, int p6, float p7, bool p8, float p9)l
extern _native bool is_waypoint_playback_going_on_for_vehicle(any p0)l
extern _native any get_vehicle_waypoint_progress(any p0)l
extern _native any get_vehicle_waypoint_target_point(any p0)l
extern _native void vehicle_waypoint_playback_pause(any p0)l
extern _native void vehicle_waypoint_playback_resume(any p0)l
extern _native void vehicle_waypoint_playback_use_default_speed(any p0)l
extern _native void vehicle_waypoint_playback_override_speed(any p0, float p1)l
extern _native void task_set_blocking_of_non_temporary_events(Ped ped, bool toggle)l
extern _native void task_force_motion_state(Ped ped, Hash state, bool p2)l
extern _native32(0x6F5D215F) void _task_move_network(Ped ped, const char* task, float multiplier, bool p3, const char* animDict, int flags)l
extern _native32(0x71A5C5DB) void _task_move_network_advanced(Ped ped, const char* p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8, float p9, bool p10, const char* animDict, int flags)l
extern _native bool unk_0x902656EB(int PlayerID)l
extern _native bool unk_0x92FDBAE6(any p0)l
extern _native any unk_0x885724DE(Ped ped, const char* p1)l
extern _native const char* unk_0x96C0277B(Ped ped)l
extern _native void unk_0xA79BE783(Ped p0, const char* p1, float p2)l
extern _native void unk_0xF3538041(Ped p0, any* p1, bool p2)l
extern _native bool unk_0x1EBB6F3D(any p0, const char* p1)l
extern _native bool unk_0x72FA5EF2(any p0, any* p1)l
extern _native bool is_move_blend_ratio_still(Ped ped)l
extern _native bool is_move_blend_ratio_walking(Ped ped)l
extern _native bool is_move_blend_ratio_running(Ped ped)l
extern _native bool is_move_blend_ratio_sprinting(Ped ped)l
extern _native bool is_ped_still(Ped ped)l
extern _native bool is_ped_walking(Ped ped)l
extern _native bool is_ped_running(Ped ped)l
extern _native bool is_ped_sprinting(Ped ped)l
extern _native bool is_ped_strafing(Ped ped)l
extern _native void task_synchronized_scene(Ped ped, int scene, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, any p9)l
extern _native void task_sweep_aim_entity(Ped ped, const char* anim, const char* p2, const char* p3, const char* p4, int p5, Vehicle vehicle, float p7, float p8)l
extern _native void update_task_sweep_aim_entity(Ped ped, Entity entity)l
extern _native void task_sweep_aim_position(any p0, any* p1, any* p2, any* p3, any* p4, any p5, float p6, float p7, float p8, float p9, float p10)l
extern _native void update_task_sweep_aim_position(any p0, float p1, float p2, float p3)l
extern _native void task_arrest_ped(Ped ped, Ped target)l
extern _native bool is_ped_running_arrest_task(Ped ped)l
extern _native bool is_ped_being_arrested(Ped ped)l
extern _native void uncuff_ped(Ped ped)l
extern _native bool is_ped_cuffed(Ped ped)l
#pragma endregion //}
#pragma region GAMEPLAY //{
extern _native int get_allocated_stack_size()l
extern _native32(0x11A178B8) int _get_free_stack_slots_count(int stackSize)l
extern _native void set_random_seed(int time)l
extern _native void set_time_scale(float time)l
extern _native void set_mission_flag(bool toggle)l
extern _native bool get_mission_flag()l
extern _native void set_random_event_flag(bool p0)l
extern _native any get_random_event_flag()l
extern _native void unk_0x8B2DE971(bool p0)l
extern _native void unk_0xE77199F7(const char* p0)l
extern _native Hash get_prev_weather_type_hash_name()l
extern _native Hash get_next_weather_type_hash_name()l
extern _native bool is_prev_weather_type(const char* weatherType)l
extern _native bool is_next_weather_type(const char* weatherType)l
extern _native void set_weather_type_persist(const char* weatherType)l
extern _native void set_weather_type_now_persist(const char* weatherType)l
extern _native void set_weather_type_now(const char* weatherType)l
extern _native32(0x386F0D25) void _set_weather_type_over_time(const char* weatherType, float time)l
extern _native void set_random_weather_type()l
extern _native void clear_weather_type_persist()l
extern _native32(0x9A5C1D56) void _get_weather_type_transition(any* p0, any* p1, float* progress_or_time)l
extern _native32(0x5CA74040) void _set_weather_type_transition(Hash weatherType1, Hash weatherType2, float percentWeather2)l
extern _native void set_override_weather(const char* weatherType)l
extern _native void clear_override_weather()l
extern _native void unk_0x625181DC(float p0)l
extern _native void unk_0xBEBBFDC8(float p0)l
extern _native void unk_0x6926AB03(float p0)l
extern _native void unk_0xD447439D(float p0)l
extern _native void unk_0x584E9C59(float p0)l
extern _native void unk_0x5656D578(float p0)l
extern _native void unk_0x0DE40C28(float p0)l
extern _native void unk_0x98C9138B(float p0)l
extern _native void unk_0xFB1A9CDE(float p0)l
extern _native void unk_0x1C0CAE89(float p0)l
extern _native void unk_0x4671AC2E(float p0)l
extern _native void unk_0xDA02F415(float p0)l
extern _native void unk_0x5F3DDEC0(float p0)l
extern _native void unk_0x63A89684(float p0)l
extern _native void set_wind(float speed)l
extern _native void set_wind_speed(float speed)l
extern _native float get_wind_speed()l
extern _native void set_wind_direction(float direction)l
extern _native vector3 get_wind_direction()l
extern _native any get_rain_level()l
extern _native any get_snow_level()l
extern _native32(0xDF38165E) void _create_lightning_thunder()l
extern _native void unk_0x8727A4C5(const char* p0)l
extern _native32(0xED88FC61) void _set_cloud_hat_transition(const char* type, float transitionTime)l
extern _native void unk_0xC9FA6E07(const char* p0, float p1)l
extern _native32(0x2D7787BC) void _clear_cloud_hat()l
extern _native int get_game_timer()l
extern _native float get_frame_time()l
extern _native int get_frame_count()l
extern _native float get_random_float_in_range(float startRange, float endRange)l
extern _native int get_random_int_in_range(int startRange, int endRange)l
extern _native bool get_ground_z_for_3d_coord(vector3 vec, float* groundZ, bool unk)l
extern _native bool unk_0x64D91CED(vector3 vec, float* p3, vector3* p4)l
extern _native float asin(float p0)l
extern _native float acos(float p0)l
extern _native float tan(float p0)l
extern _native float atan(float p0)l
extern _native float atan2(float p0, float p1)l
extern _native float get_distance_between_coords(vector3 vec_1, vector3 vec_2, bool useZ)l
extern _native float get_angle_between_2d_vectors(vector2 vector_1, vector2 vector_2)l
extern _native float get_heading_from_vector_2d(vector2 d)l
extern _native float unk_0x89459F0A(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)l
extern _native vector3 unk_0xCAECF37E(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)l
extern _native bool unk_0xC6CC812C(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, any* p12)l
extern _native void set_bit(int* address, int offset)l
extern _native void clear_bit(int* address, int offset)l
extern _native Hash get_hash_key(const char* value)l
extern _native void unk_0x87B92190(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, any* p9, any* p10, any* p11, any* p12)l
extern _native bool is_area_occupied(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9, bool p10, any p11, bool p12)l
extern _native bool is_position_occupied(vector3 vec, float range, bool p4, bool p5, bool p6, bool p7, bool p8, any p9, bool p10)l
extern _native bool is_point_obscured_by_a_mission_entity(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native void clear_area(vector3 vec, float radius, bool p4, bool ignoreCopCars, bool ignoreObjects, bool p7)l
extern _native32(0x20E4FFD9) void _clear_area_of_everything(vector3 vec, float radius, bool p4, bool p5, bool p6, bool p7)l
extern _native void clear_area_of_vehicles(vector3 vec, float radius, bool p4, bool p5, bool p6, bool p7, bool p8)l
extern _native void clear_angled_area_of_vehicles(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, bool p8, bool p9, bool p10, bool p11)l
extern _native void clear_area_of_objects(vector3 vec, float radius, int flags)l
extern _native void clear_area_of_peds(vector3 vec, float radius, int flags)l
extern _native void clear_area_of_cops(vector3 vec, float radius, int flags)l
extern _native void clear_area_of_projectiles(vector3 vec, float radius, int flags)l
extern _native void set_save_menu_active(bool unk)l
extern _native int unk_0x39771F21()l
extern _native void set_credits_active(bool toggle)l
extern _native void unk_0x75B06B5A(bool toggle)l
extern _native any unk_0x2569C9A7()l
extern _native void terminate_all_scripts_with_this_name(const char* scriptName)l
extern _native void network_set_script_is_safe_for_network_game()l
extern _native int add_hospital_restart(vector3 vec, float p3, any p4)l
extern _native void disable_hospital_restart(int hospitalIndex, bool toggle)l
extern _native any add_police_restart(float p0, float p1, float p2, float p3, any p4)l
extern _native void disable_police_restart(int policeIndex, bool toggle)l
extern _native32(0x296574AE) void _disable_automatic_respawn(bool disableRespawn)l
extern _native void ignore_next_restart(bool toggle)l
extern _native void set_fade_out_after_death(bool toggle)l
extern _native void set_fade_out_after_arrest(bool toggle)l
extern _native void set_fade_in_after_death_arrest(bool toggle)l
extern _native void set_fade_in_after_load(bool toggle)l
extern _native any register_save_house(float p0, float p1, float p2, float p3, any* p4, any p5, any p6)l
extern _native void set_save_house(any p0, bool p1, bool p2)l
extern _native bool override_save_house(bool p0, float p1, float p2, float p3, float p4, bool p5, float p6, float p7)l
extern _native any unk_0xC4D71AB4(any p0, any p1, any p2, any p3)l
extern _native void do_auto_save()l
extern _native any unk_0xA8546914()l
extern _native bool is_auto_save_in_progress()l
extern _native any unk_0x78350773()l
extern _native void unk_0x5A45B11A()l
extern _native void begin_replay_stats(any p0, any p1)l
extern _native void unk_0x81216EE0(any p0)l
extern _native void end_replay_stats()l
extern _native any unk_0xC58250F1()l
extern _native any unk_0x50C39926()l
extern _native any unk_0x710E5D1E()l
extern _native any unk_0xC7BD1AF0()l
extern _native any unk_0x22BE2423(any p0)l
extern _native void clear_replay_stats()l
extern _native any unk_0xF62B3C48()l
extern _native any unk_0x3589452B()l
extern _native any unk_0x144AAF22()l
extern _native bool is_memory_card_in_use()l
extern _native void shoot_single_bullet_between_coords(vector3 vec_1, vector3 vec_2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed)l
extern _native void unk_0x52ACCB7B(vector3 vec_1, vector3 vec_2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity)l
extern _native void get_model_dimensions(Hash modelHash, vector3* minimum, vector3* maximum)l
extern _native void set_fake_wanted_level(int fakeWantedLevel)l
extern _native int get_fake_wanted_level()l
extern _native bool is_bit_set(int address, int offset)l
extern _native void using_mission_creator(bool toggle)l
extern _native void unk_0x082BA6F2(bool p0)l
extern _native void set_minigame_in_progress(bool toggle)l
extern _native bool is_minigame_in_progress()l
extern _native bool is_this_a_minigame_script()l
extern _native bool is_sniper_inverted()l
extern _native any unk_0xBAF17315()l
extern _native int get_profile_setting(int profileSetting)l
extern _native bool are_strings_equal(const char* string1, const char* string2)l
extern _native int compare_strings(const char* str1, const char* str2, bool matchCase, int maxLength)l
extern _native int absi(int value)l
extern _native float absf(float value)l
extern _native bool is_sniper_bullet_in_area(vector3 vec_1, vector3 vec_2)l
extern _native bool is_projectile_in_area(vector3 vec_1, vector3 vec_2, bool ownedByPlayer)l
extern _native bool is_projectile_type_in_area(vector3 vec_1, vector3 vec_2, int type, bool p7)l
extern _native bool is_projectile_type_in_angled_area(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7, bool p8)l
extern _native bool unk_0xBE81F1E2(float p0, float p1, float p2, any p3, float p4, bool p5)l
extern _native any unk_0x1A40454B(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native bool unk_0x6BDE5CE4(Ped ped, Hash weaponHash, float radius, Entity* entity, bool p4)l
extern _native any unk_0x507BC6F7(Ped ped, Hash weaponhash, float p2, float p3, float p4, bool p5)l
extern _native bool is_bullet_in_angled_area(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7)l
extern _native bool is_bullet_in_area(float p0, float p1, float p2, float p3, bool p4)l
extern _native bool is_bullet_in_box(float p0, float p1, float p2, float p3, float p4, float p5, bool p6)l
extern _native bool has_bullet_impacted_in_area(vector3 vec, float p3, bool p4, bool p5)l
extern _native bool has_bullet_impacted_in_box(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7)l
extern _native bool is_orbis_version()l
extern _native bool is_durango_version()l
extern _native bool is_xbox360_version()l
extern _native bool is_ps3_version()l
extern _native bool is_pc_version()l
extern _native bool is_aussie_version()l
extern _native bool is_string_null(const char* string)l
extern _native bool is_string_null_or_empty(const char* string)l
extern _native bool string_to_int(const char* string, int* outInteger)l
extern _native void set_bits_in_range(int* var, int rangeStart, int rangeEnd, int p3)l
extern _native int get_bits_in_range(int var, int rangeStart, int rangeEnd)l
extern _native int add_stunt_jump(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, any p15, any p16)l
extern _native int add_stunt_jump_angled(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, float p15, float p16, any p17, any p18)l
extern _native void delete_stunt_jump(int p0)l
extern _native void enable_stunt_jump_set(int p0)l
extern _native void disable_stunt_jump_set(int p0)l
extern _native void unk_0x3C806A2D(bool p0)l
extern _native bool is_stunt_jump_in_progress()l
extern _native bool is_stunt_jump_message_showing()l
extern _native any unk_0x006F9BA2()l
extern _native void cancel_stunt_jump()l
extern _native void set_game_paused(bool toggle)l
extern _native void set_this_script_can_be_paused(bool toggle)l
extern _native void set_this_script_can_remove_blips_created_by_any_script(bool toggle)l
extern _native32(0xFF6191E1) bool _has_button_combination_just_been_entered(Hash hash, int amount)l
extern _native32(0x721B2492) void _use_freemode_map_behavior(bool toggle)l
extern _native32(0xE202879D) void _set_unk_map_flag(int flag)l
extern _native bool is_frontend_fading()l
extern _native void populate_now()l
extern _native int get_index_of_current_level()l
extern _native void set_gravity_level(int level)l
extern _native void start_save_data(any* p0, any p1, bool p2)l
extern _native void stop_save_data()l
extern _native any unk_0x9EF0BC64(bool p0)l
extern _native void register_int_to_save(any* p0, const char* name)l
extern _native void register_enum_to_save(any* p0, const char* name)l
extern _native void register_float_to_save(any* p0, const char* name)l
extern _native void register_bool_to_save(any* p0, const char* name)l
extern _native void register_text_label_to_save(any* p0, const char* name)l
extern _native void unk_0xE2089749(any* p0, const char* name)l
extern _native void unk_0xF91B8C33(any* p0, const char* name)l
extern _native void unk_0x74E8FAD9(any* p0, const char* name)l
extern _native void unk_0x6B4335DD(any* p0, const char* name)l
extern _native32(0xFB45728E) void _start_save_struct(any* p0, int p1, const char* structName)l
extern _native void stop_save_struct()l
extern _native32(0x893A342C) void _start_save_array(any* p0, int p1, const char* arrayName)l
extern _native void stop_save_array()l
extern _native void enable_dispatch_service(int dispatchType, bool toggle)l
extern _native void unk_0xE0F0684F(int type, bool toggle)l
extern _native int unk_0x3CE5BF6B(int p0)l
extern _native bool create_incident(int incidentType, vector3 vec, int p5, float radius, int* outIncidentID)l
extern _native bool create_incident_with_entity(int incidentType, Ped ped, int amountOfPeople, float radius, int* outIncidentID)l
extern _native void delete_incident(int incidentId)l
extern _native bool is_incident_valid(int incidentId)l
extern _native void unk_0x0242D88E(any p0, any p1, any p2)l
extern _native void unk_0x1F38102E(any p0, float p1)l
extern _native bool find_spawn_point_in_direction(vector3 vec_1, vector3 vec_2, float distance, vector3* spawnPoint)l
extern _native any unk_0x42BF09B3(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native void unk_0xFBDBE374(any p0, bool p1)l
extern _native void enable_tennis_mode(Ped ped, bool toggle, bool p2)l
extern _native bool is_tennis_mode(Ped ped)l
extern _native void unk_0xC20A7D2B(any p0, any* p1, any* p2, float p3, float p4, bool p5)l
extern _native bool unk_0x8501E727(any p0)l
extern _native bool unk_0x1A332D2D(any p0)l
extern _native void unk_0x0C8865DF(any p0, any p1, float p2, float p3, float p4, bool p5)l
extern _native void unk_0x49F977A9(any p0, const char* p1, float p2)l
extern _native void unk_0x6F009E33(any p0, any p1, any p2)l
extern _native void reset_dispatch_ideal_spawn_distance()l
extern _native void set_dispatch_ideal_spawn_distance(float p0)l
extern _native void set_dispatch_time_between_spawn_attempts(any p0, float p1)l
extern _native void set_dispatch_time_between_spawn_attempts_multiplier(any p0, float p1)l
extern _native any unk_0xF557BAF9(float p0, float p1, float p2, float p3, float p4, float p5, float p6)l
extern _native void remove_dispatch_spawn_blocking_area(any p0)l
extern _native void reset_dispatch_spawn_blocking_areas()l
extern _native void unk_0xE0C9307E()l
extern _native void unk_0xA0D8C749(any p0, any p1)l
extern _native void unk_0x24A4E0B2(any p0, any p1, any p2)l
extern _native void unk_0x66C3C59C()l
extern _native void unk_0xD9660339(bool p0)l
extern _native32(0xD2688412) void _display_onscreen_keyboard_2(int p0, const char* windowTitle, any* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, const char* defaultConcat4, const char* defaultConcat5, const char* defaultConcat6, const char* defaultConcat7, int maxInputLength)l
extern _native void display_onscreen_keyboard(int p0, const char* windowTitle, const char* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, int maxInputLength)l
extern _native int update_onscreen_keyboard()l
extern _native const char* get_onscreen_keyboard_result()l
extern _native void unk_0x3301EA47(int p0)l
extern _native void unk_0x42B484ED(Hash hash, bool p1)l
extern _native void unk_0x8F60366E(int p0, bool p1)l
extern _native any set_explosive_ammo_this_frame(Player player)l
extern _native any set_fire_ammo_this_frame(Player player)l
extern _native any set_explosive_melee_this_frame(Player player)l
extern _native any set_super_jump_this_frame(Player player)l
extern _native bool unk_0xC3C10FCC()l
extern _native void unk_0x054EC103()l
extern _native any unk_0x46B5A15C()l
extern _native32(0x5D209F25) void _reset_localplayer_state()l
extern _native void unk_0x2D33F15A(any p0, any p1, any p2, any p3)l
extern _native void unk_0xDF99925C()l
extern _native void unk_0xA27F4472(any p0, any p1, any p2, any p3)l
extern _native bool unk_0x07FF553F(any p0, any* p1, any* p2)l
#pragma endregion //}
#pragma region AUDIO //{
extern _native void play_ped_ringtone(const char* ringtoneName, Ped ped, bool p2)l
extern _native bool is_ped_ringtone_playing(Ped ped)l
extern _native void stop_ped_ringtone(Ped ped)l
extern _native bool is_mobile_phone_call_ongoing()l
extern _native any unk_0x16FB88B5()l
extern _native void create_new_scripted_conversation()l
extern _native void add_line_to_conversation(int p0, const char* p1, const char* p2, int p3, int p4, bool p5, bool p6, bool p7, bool p8, int p9, bool p10, bool p11, bool p12)l
extern _native void add_ped_to_conversation(any p0, any ped, const char* p2)l
extern _native void unk_0x73C6F979(any p0, float p1, float p2, float p3)l
extern _native void unk_0x88203DDA(any p0, any p1)l
extern _native void set_microphone_position(bool p0, vector3 vec_1, vector3 vec_2, vector3 vec_3)l
extern _native void unk_0x1193ED6E(bool p0)l
extern _native void start_script_phone_conversation(bool p0, bool p1)l
extern _native void preload_script_phone_conversation(bool p0, bool p1)l
extern _native void start_script_conversation(bool p0, bool p1, bool p2, bool p3)l
extern _native void preload_script_conversation(bool p0, bool p1, bool p2, bool p3)l
extern _native void start_preloaded_conversation()l
extern _native any unk_0x336F3D35()l
extern _native bool is_scripted_conversation_ongoing()l
extern _native bool is_scripted_conversation_loaded()l
extern _native any get_current_scripted_conversation_line()l
extern _native void pause_scripted_conversation(bool p0)l
extern _native void restart_scripted_conversation()l
extern _native any stop_scripted_conversation(bool p0)l
extern _native void skip_to_next_scripted_conversation_line()l
extern _native void interrupt_conversation(any p0, any* p1, any* p2)l
extern _native any unk_0xB58B8FF3(any* p0)l
extern _native void unk_0x789D8C6C(bool p0)l
extern _native void register_script_with_audio(any p0)l
extern _native void unregister_script_with_audio()l
extern _native bool request_mission_audio_bank(const char* p0, bool p1)l
extern _native bool request_ambient_audio_bank(const char* p0, bool p1)l
extern _native bool request_script_audio_bank(const char* p0, bool p1)l
extern _native any hint_ambient_audio_bank(any p0, any p1)l
extern _native any hint_script_audio_bank(any p0, any p1)l
extern _native void release_mission_audio_bank()l
extern _native void release_ambient_audio_bank()l
extern _native void release_named_script_audio_bank(const char* audioBank)l
extern _native void release_script_audio_bank()l
extern _native void unk_0xA58BBF4F()l
extern _native int get_sound_id()l
extern _native void release_sound_id(int soundId)l
extern _native void play_sound(Player soundId, const char* audioName, const char* audioRef, bool p3, any p4, bool p5)l
extern _native void play_sound_frontend(int soundId, const char* audioName, const char* audioRef, bool p3)l
extern _native void unk_0xC70E6CFA(const char* p0, const char* soundset)l
extern _native void play_sound_from_entity(int soundId, const char* audioName, Entity entity, const char* audioRef, bool p4, any p5)l
extern _native void play_sound_from_coord(int soundId, const char* audioName, vector3 vec, const char* audioRef, bool p6, int range, bool p8)l
extern _native void stop_sound(int soundId)l
extern _native int get_network_id_from_sound_id(int soundId)l
extern _native int get_sound_id_from_network_id(int netId)l
extern _native void set_variable_on_sound(int soundId, any* p1, float p2)l
extern _native void set_variable_on_stream(const char* p0, float p1)l
extern _native void override_underwater_stream(any* p0, bool p1)l
extern _native void unk_0x62D026BE(const char* name, float p1)l
extern _native bool has_sound_finished(int soundId)l
extern _native32(0x5C57B85D) void _play_ambient_speech1(Ped ped, const char* speechName, const char* speechParam)l
extern _native32(0x444180DB) void _play_ambient_speech2(Ped ped, const char* speechName, const char* speechParam)l
extern _native32(0x8386AE28) void _play_ambient_speech_with_voice(Ped p0, const char* speechName, const char* voiceName, const char* speechParam, bool p4)l
extern _native32(0xA1A1402E) void _play_ambient_speech_at_coords(const char* p0, const char* p1, float p2, float p3, float p4, const char* p5)l
extern _native void override_trevor_rage(any* p0)l
extern _native void reset_trevor_rage()l
extern _native void set_player_angry(Ped playerPed, bool disabled)l
extern _native void play_pain(Ped ped, int painID, int p1)l
extern _native void unk_0x59A3A17D(any* p0)l
extern _native void unk_0x0E387BFE(any* p0)l
extern _native void set_ambient_voice_name(Ped ped, const char* name)l
extern _native void stop_current_playing_ambient_speech(Ped ped)l
extern _native bool is_ambient_speech_playing(Ped p0)l
extern _native bool is_scripted_speech_playing(any p0)l
extern _native bool is_any_speech_playing(Ped ped)l
extern _native bool unk_0x8BD5F11E(Ped ped, const char* speechName, bool unk)l
extern _native bool is_ped_in_current_conversation(Ped ped)l
extern _native void set_ped_is_drunk(Ped ped, bool toggle)l
extern _native void unk_0x498849F3(any p0, any p1, any* p2)l
extern _native bool unk_0x0CBAF2EF(any p0)l
extern _native void set_animal_mood(Ped animal, int mood)l
extern _native bool is_mobile_phone_radio_active()l
extern _native void set_mobile_phone_radio_state(bool state)l
extern _native int get_player_radio_station_index()l
extern _native const char* get_player_radio_station_name()l
extern _native const char* get_radio_station_name(int radioStation)l
extern _native any get_player_radio_station_genre()l
extern _native bool is_radio_retuning()l
extern _native void unk_0x53DB6994()l
extern _native void unk_0xD70ECC80()l
extern _native void set_radio_to_station_name(const char* stationName)l
extern _native void set_veh_radio_station(Vehicle vehicle, const char* radioStation)l
extern _native void unk_0x7ABB89D2(Vehicle vehicle)l
extern _native void set_emitter_radio_station(const char* emitterName, const char* radioStation)l
extern _native void set_static_emitter_enabled(const char* emitterName, bool toggle)l
extern _native void set_radio_to_station_index(int radioStation)l
extern _native void set_frontend_radio_active(bool active)l
extern _native void unlock_mission_news_story(int newsStory)l
extern _native int get_number_of_passenger_voice_variations(any p0)l
extern _native int get_audible_music_track_text_id()l
extern _native void play_end_credits_music(bool play)l
extern _native void skip_radio_forward()l
extern _native void freeze_radio_station(const char* radioStation)l
extern _native void unfreeze_radio_station(const char* radioStation)l
extern _native void set_radio_auto_unfreeze(bool toggle)l
extern _native void set_initial_player_station(const char* radioStation)l
extern _native void set_user_radio_control_enabled(bool toggle)l
extern _native void set_radio_track(const char* radioStation, const char* radioTrack)l
extern _native void set_vehicle_radio_loud(Vehicle vehicle, bool toggle)l
extern _native32(0xCBA99F4A) bool _is_vehicle_radio_loud(Vehicle vehicle)l
extern _native void set_mobile_radio_enabled_during_gameplay(bool Toggle)l
extern _native bool unk_0x46B0C696()l
extern _native32(0x2A3E5E8B) bool _is_player_vehicle_radio_enabled()l
extern _native void set_vehicle_radio_enabled(Vehicle vehicle, bool toggle)l
extern _native void unk_0x128C3873(const char* radioStation, const char* p1, bool p2)l
extern _native void unk_0x1D766976(const char* radioStation)l
extern _native32(0xCC91FCF5) int _max_radio_station_index()l
extern _native int find_radio_station_index(int station)l
extern _native void unk_0xB1FF7137(const char* radioStation, bool p1)l
extern _native void unk_0xC8B514E2(float p0)l
extern _native void unk_0xBE998184(const char* radioStation, const char* p1)l
extern _native void unk_0x8AFC488D(any p0, bool p1)l
extern _native void set_ambient_zone_state(any* p0, bool p1, bool p2)l
extern _native void clear_ambient_zone_state(const char* zoneName, bool p1)l
extern _native void set_ambient_zone_list_state(any* p0, bool p1, bool p2)l
extern _native void clear_ambient_zone_list_state(any* p0, bool p1)l
extern _native void set_ambient_zone_state_persistent(const char* ambientZone, bool p1, bool p2)l
extern _native void set_ambient_zone_list_state_persistent(const char* ambientZone, bool p1, bool p2)l
extern _native bool is_ambient_zone_enabled(const char* ambientZone)l
extern _native void set_cutscene_audio_override(const char* p0)l
extern _native void get_player_headset_sound_alternate(const char* p0, float p1)l
extern _native any play_police_report(const char* name, float p1)l
extern _native void blip_siren(Vehicle vehicle)l
extern _native void override_veh_horn(Vehicle vehicle, bool mute, int p2)l
extern _native bool is_horn_active(Vehicle vehicle)l
extern _native void set_aggressive_horns(bool toggle)l
extern _native void unk_0x3C395AEE(bool p0)l
extern _native void unk_0x8CE63FA1(bool p0, bool p1)l
extern _native bool is_stream_playing()l
extern _native int get_stream_play_time()l
extern _native bool load_stream(const char* streamName, const char* soundSet)l
extern _native bool load_stream_with_start_offset(const char* streamName, int startOffset, const char* soundSet)l
extern _native void play_stream_from_ped(Ped ped)l
extern _native void play_stream_from_vehicle(Vehicle vehicle)l
extern _native void play_stream_from_object(Object object)l
extern _native void play_stream_frontend()l
extern _native void special_frontend_equal(vector3 vec)l
extern _native void stop_stream()l
extern _native void stop_ped_speaking(Ped ped, bool shaking)l
extern _native void disable_ped_pain_audio(Ped ped, bool toggle)l
extern _native bool is_ambient_speech_disabled(Ped ped)l
extern _native void set_siren_with_no_driver(Vehicle vehicle, bool toggle)l
extern _native32(0xDE8BA3CD) void _sound_vehicle_horn_this_frame(Vehicle vehicle)l
extern _native void set_horn_enabled(Vehicle vehicle, bool toggle)l
extern _native void set_audio_vehicle_priority(Vehicle vehicle, any p1)l
extern _native void unk_0x2F0A16D1(any p0, float p1)l
extern _native void use_siren_as_horn(Vehicle vehicle, bool toggle)l
extern _native32(0x33B0B007) void _set_vehicle_audio(Vehicle vehicle, const char* audioName)l
extern _native void unk_0x1C0C5E4C(any p0, const char* p1, const char* p2)l
extern _native bool unk_0x6E660D3F(Vehicle vehicle)l
extern _native void unk_0x23BE6432(any p0, float p1)l
extern _native void unk_0xE81FAC68(any p0, float p1)l
extern _native void unk_0x9365E042(any p0, bool p1)l
extern _native void unk_0x2A60A90E(any p0, bool p1)l
extern _native void set_vehicle_boost_active(Vehicle vehicle, bool Toggle)l
extern _native void unk_0x934BE749(any p0, bool p1)l
extern _native void unk_0xE61110A2(any p0, bool p1)l
extern _native void play_vehicle_door_open_sound(Vehicle vehicle, int p1)l
extern _native void play_vehicle_door_close_sound(Vehicle vehicle, int p1)l
extern _native void unk_0x563B635D(Vehicle vehicle, bool toggle)l
extern _native bool is_game_in_control_of_music()l
extern _native void set_gps_active(bool active)l
extern _native void play_mission_complete_audio(const char* audioName)l
extern _native bool is_mission_complete_playing()l
extern _native any unk_0xCBE09AEC()l
extern _native void unk_0xD2858D8A(bool p0)l
extern _native bool start_audio_scene(const char* scene)l
extern _native void stop_audio_scene(const char* scene)l
extern _native void stop_audio_scenes()l
extern _native bool is_audio_scene_active(const char* scene)l
extern _native void set_audio_scene_variable(const char* scene, const char* variable, float value)l
extern _native void unk_0xE812925D(any p0)l
extern _native32(0x2BC93264) void _dynamic_mixer_related_fn(Entity p0, const char* p1, float p2)l
extern _native void unk_0x308ED0EC(any p0, float p1)l
extern _native any audio_is_scripted_music_playing()l
extern _native bool prepare_music_event(const char* eventName)l
extern _native bool cancel_music_event(const char* eventName)l
extern _native bool trigger_music_event(const char* eventName)l
extern _native any unk_0x2705C4D5()l
extern _native any get_music_playtime()l
extern _native void unk_0x53FC3FEC(any p0, any p1, any p2, any p3)l
extern _native any clear_all_broken_glass()l
extern _native void unk_0x95050CAD(bool p0, any p1)l
extern _native void unk_0xE64F97A0(float p0, float p1)l
extern _native void unk_0xD87AF337()l
extern _native bool prepare_alarm(const char* alarmName)l
extern _native void start_alarm(const char* alarmName, bool p2)l
extern _native void stop_alarm(const char* alarmName, bool toggle)l
extern _native void stop_all_alarms(bool stop)l
extern _native bool is_alarm_playing(const char* alarmName)l
extern _native Hash get_vehicle_default_horn(Vehicle vehicle)l
extern _native Hash unk_0xFD4B5B3B(Vehicle vehicle)l
extern _native void reset_ped_audio_flags(any p0)l
extern _native void unk_0xC307D531(any p0, bool p1)l
extern _native32(0x13EB5861) void _force_ambient_siren(bool value)l
extern _native void unk_0x7BED1872(Vehicle vehicle, bool p1)l
extern _native void set_audio_flag(const char* flagName, bool toggle)l
extern _native any prepare_synchronized_audio_event(const char* p0, any p1)l
extern _native bool prepare_synchronized_audio_event_for_scene(any p0, any* p1)l
extern _native bool play_synchronized_audio_event(any p0)l
extern _native bool stop_synchronized_audio_event(any p0)l
extern _native void unk_0x55A21772(any* p0, float p1, float p2, float p3)l
extern _native32(0xA17F9AB0) void _set_synchronized_audio_event_position_this_frame(const char* p0, Entity p1)l
extern _native void unk_0x62B43677(int p0)l
extern _native void unk_0x8AD670EC(const char* p0, const char* p1)l
extern _native void unk_0xD24B4D0C(const char* p0)l
extern _native void unk_0x7262B5BA()l
extern _native any unk_0x93A44A1F()l
extern _native void unk_0x13777A0B(Ped ped)l
extern _native void unk_0x1134F68B()l
extern _native void unk_0xE0047BFD(bool p0)l
#pragma endregion //}
#pragma region CUTSCENE //{
extern _native void request_cutscene(const char* cutsceneName, int p1)l
extern _native32(0xD98F656A) void _request_cutscene_ex(const char* cutsceneName, int p1, int p2)l
extern _native void remove_cutscene()l
extern _native bool has_cutscene_loaded()l
extern _native bool has_this_cutscene_loaded(const char* cutsceneName)l
extern _native void unk_0x25A2CABC(int p0)l
extern _native bool unk_0xDD8878E9()l
extern _native bool unk_0x7B93CDAA(int p0)l
extern _native void unk_0x47DB08A9(const char* p0, any p1, any p2)l
extern _native void start_cutscene(int p0)l
extern _native void start_cutscene_at_coords(vector3 vec, int p3)l
extern _native void stop_cutscene(bool p0)l
extern _native void stop_cutscene_immediately()l
extern _native void set_cutscene_origin(vector3 vec, float p3, int p4)l
extern _native int get_cutscene_time()l
extern _native int get_cutscene_total_duration()l
extern _native bool was_cutscene_skipped()l
extern _native bool has_cutscene_finished()l
extern _native bool is_cutscene_active()l
extern _native bool is_cutscene_playing()l
extern _native int get_cutscene_section_playing()l
extern _native Entity get_entity_index_of_cutscene_entity(const char* cutsceneEntName, Hash modelHash)l
extern _native int unk_0x5AE68AE6()l
extern _native void register_entity_for_cutscene(Ped cutscenePed, const char* cutsceneEntName, int p2, Hash modelHash, int p4)l
extern _native Entity get_entity_index_of_registered_entity(const char* cutsceneEntName, Hash modelHash)l
extern _native void set_cutscene_trigger_area(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native bool can_set_enter_state_for_registered_entity(const char* cutsceneEntName, Hash modelHash)l
extern _native bool can_set_exit_state_for_registered_entity(const char* cutsceneEntName, Hash modelHash)l
extern _native bool can_set_exit_state_for_camera(bool p0)l
extern _native void unk_0x35721A08(bool toggle)l
extern _native void set_cutscene_fade_values(bool p0, bool p1, bool p2, bool p3)l
extern _native void unk_0x8338DA1D(bool p0)l
extern _native void unk_0x04377C10(bool p0)l
extern _native any unk_0xDBD88708()l
extern _native void unk_0x28D54A7F(bool p0)l
extern _native void register_synchronised_script_speech()l
extern _native void set_cutscene_ped_component_variation(const char* cutsceneEntName, int p1, int p2, int p3, Hash modelHash)l
extern _native void unk_0x1E7DA95E(const char* cutsceneEntName, Ped ped, Hash modelHash)l
extern _native bool does_cutscene_entity_exist(const char* cutsceneEntName, Hash modelHash)l
extern _native void set_cutscene_ped_prop_variation(const char* cutsceneEntName, int p1, int p2, int p3, Hash modelHash)l
extern _native bool unk_0x4315A7C5()l
#pragma endregion //}
#pragma region INTERIOR //{
extern _native int get_interior_group_id(int interiorID)l
extern _native vector3 get_offset_from_interior_in_world_coords(int interiorID, vector3 vec)l
extern _native bool is_interior_scene()l
extern _native bool is_valid_interior(int interiorID)l
extern _native void clear_room_for_entity(Entity entity)l
extern _native void force_room_for_entity(Entity entity, int interiorID, Hash roomHashKey)l
extern _native Hash get_room_key_from_entity(Entity entity)l
extern _native Hash get_key_for_entity_in_room(Entity entity)l
extern _native int get_interior_from_entity(Entity entity)l
extern _native void unk_0xE645E162(Entity entity, int interiorID)l
extern _native void unk_0xD79803B5(int interiorID, Hash roomHashKey)l
extern _native void unk_0x1F6B4B13(const char* roomName)l
extern _native void unk_0x0E9529CC(Hash roomHashKey)l
extern _native32(0x4FF3D3F5) Hash _get_room_key_from_gameplay_cam()l
extern _native void unk_0x617DC75D()l
extern _native int get_interior_at_coords(vector3 vec)l
extern _native void add_pickup_to_interior_room_by_name(Pickup pickup, const char* roomName)l
extern _native32(0x3ADA414E) void _load_interior(int interiorID)l
extern _native void unpin_interior(int interiorID)l
extern _native bool is_interior_ready(int interiorID)l
extern _native int get_interior_at_coords_with_type(vector3 vec, const char* interiorType)l
extern _native32(0x7762249C) bool _are_coords_colliding_with_exterior(vector3 vec)l
extern _native int get_interior_from_collision(vector3 vec)l
extern _native32(0xC80A5DDF) void _enable_interior_prop(int interiorID, const char* propName)l
extern _native32(0xDBA768A1) void _disable_interior_prop(int interiorID, const char* propName)l
extern _native32(0x39A3CC6F) bool _is_interior_prop_enabled(int interiorID, const char* propName)l
extern _native void refresh_interior(int interiorID)l
extern _native32(0x1F375B4C) void _hide_map_object_this_frame(Hash mapObjectHash)l
extern _native void disable_interior(int interiorID, bool toggle)l
extern _native bool is_interior_disabled(int interiorID)l
extern _native void cap_interior(int interiorID, bool toggle)l
extern _native bool is_interior_capped(int interiorID)l
extern _native void unk_0x5EF9C5C2(bool toggle)l
#pragma endregion //}
#pragma region CAM //{
extern _native void render_script_cams(bool render, bool ease, int easeTime, bool p3, bool p4)l
extern _native void unk_0xD3C08183(bool render, any p1, any p2)l
extern _native Cam create_cam(const char* camName, bool p1)l
extern _native Cam create_cam_with_params(const char* camName, vector3 pos, vector3 rot, float fov, bool p8, int p9)l
extern _native Cam create_camera(Hash camHash, bool p1)l
extern _native Cam create_camera_with_params(Hash camHash, vector3 pos, vector3 rot, float fov, bool p8, any p9)l
extern _native void destroy_cam(Cam cam, bool thisScriptCheck)l
extern _native void destroy_all_cams(bool thisScriptCheck)l
extern _native bool does_cam_exist(Cam cam)l
extern _native void set_cam_active(Cam cam, bool active)l
extern _native bool is_cam_active(Cam cam)l
extern _native bool is_cam_rendering(Cam cam)l
extern _native Cam get_rendering_cam()l
extern _native vector3 get_cam_coord(Cam cam)l
extern _native vector3 get_cam_rot(Cam cam, int rotationOrder)l
extern _native float get_cam_fov(Cam cam)l
extern _native float get_cam_near_clip(Cam cam)l
extern _native float get_cam_far_clip(Cam cam)l
extern _native float get_cam_far_dof(Cam cam)l
extern _native void set_cam_params(Cam cam, vector3 pos, vector3 rot, float fieldOfView, any p8, int p9, int p10, int p11)l
extern _native void set_cam_coord(Cam cam, vector3 pos)l
extern _native void set_cam_rot(Cam cam, vector3 rot, int rotationOrder)l
extern _native void set_cam_fov(Cam cam, float fieldOfView)l
extern _native void set_cam_near_clip(Cam cam, float nearClip)l
extern _native void set_cam_far_clip(Cam cam, float farClip)l
extern _native void set_cam_motion_blur_strength(Cam cam, float strength)l
extern _native void set_cam_near_dof(Cam cam, float nearDOF)l
extern _native void set_cam_far_dof(Cam cam, float farDOF)l
extern _native void set_cam_dof_strength(Cam cam, float dofStrength)l
extern _native void set_cam_dof_planes(Cam cam, float p1, float p2, float p3, float p4)l
extern _native void set_cam_use_shallow_dof_mode(Cam cam, bool toggle)l
extern _native void set_use_hi_dof()l
extern _native void attach_cam_to_entity(Cam cam, Entity entity, vector3 Offset, bool isRelative)l
extern _native void attach_cam_to_ped_bone(Cam cam, Ped ped, int boneIndex, vector3 vec, bool heading)l
extern _native void detach_cam(Cam cam)l
extern _native void set_cam_inherit_roll_vehicle(Cam cam, bool p1)l
extern _native void point_cam_at_coord(Cam cam, vector3 vec)l
extern _native void point_cam_at_entity(Cam cam, Entity entity, float p2, float p3, float p4, bool p5)l
extern _native void point_cam_at_ped_bone(Cam cam, int ped, int boneIndex, vector3 vec, bool p6)l
extern _native void stop_cam_pointing(Cam cam)l
extern _native void set_cam_affects_aiming(Cam cam, bool toggle)l
extern _native void unk_0xE1A0B2F1(any p0, bool p1)l
extern _native void unk_0x43220969(any p0, bool p1)l
extern _native void set_cam_debug_name(Cam camera, const char* name)l
extern _native void add_cam_spline_node(Cam camera, vector3 vec, vector3 Rot, int length, int p8, int p9)l
extern _native void unk_0x30510511(any p0, any p1, any p2, any p3)l
extern _native void unk_0xBA6C085B(any p0, any p1, any p2, any p3)l
extern _native void unk_0xB4737F03(any p0, any p1, any p2)l
extern _native void set_cam_spline_phase(Cam cam, float p1)l
extern _native float get_cam_spline_phase(Cam cam)l
extern _native float get_cam_spline_node_phase(Cam cam)l
extern _native void set_cam_spline_duration(int cam, int timeDuration)l
extern _native void unk_0x15E141CE(any p0, any p1)l
extern _native bool get_cam_spline_node_index(Cam cam)l
extern _native void unk_0x21D275DA(any p0, any p1, any p2, float p3)l
extern _native void unk_0xA3BD9E94(any p0, any p1, float p2)l
extern _native void override_cam_spline_velocity(Cam cam, int p1, float p2, float p3)l
extern _native void override_cam_spline_motion_blur(Cam cam, int p1, float p2, float p3)l
extern _native void unk_0xC90B2DDC(any p0, any p1, any p2)l
extern _native bool is_cam_spline_paused(any p0)l
extern _native void set_cam_active_with_interp(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation)l
extern _native bool is_cam_interpolating(Cam cam)l
extern _native void shake_cam(Cam cam, const char* type, float amplitude)l
extern _native void animated_shake_cam(Cam cam, const char* p1, const char* p2, const char* p3, float amplitude)l
extern _native bool is_cam_shaking(Cam cam)l
extern _native void set_cam_shake_amplitude(Cam cam, float amplitude)l
extern _native void stop_cam_shaking(Cam cam, bool p1)l
extern _native void unk_0x2B0F05CD(const char* p0, float p1)l
extern _native void unk_0xCB75BD9C(const char* p0, const char* p1, const char* p2, float p3)l
extern _native bool is_script_global_shaking()l
extern _native void stop_script_global_shaking(bool p0)l
extern _native bool play_cam_anim(Cam cam, const char* animName, const char* animDictionary, vector3 vec, vector3 Rot, bool p9, int p10)l
extern _native bool is_cam_playing_anim(Cam cam, const char* animName, const char* animDictionary)l
extern _native void set_cam_anim_current_phase(Cam cam, float phase)l
extern _native float get_cam_anim_current_phase(Cam cam)l
extern _native bool play_synchronized_cam_anim(any p0, any p1, const char* animName, const char* animDictionary)l
extern _native void unk_0x56F9ED27(any p0, float p1, float p2, float p3)l
extern _native32(0x71570DBA) void _set_camera_range(Cam cam, float range)l
extern _native void unk_0x60B345DE(any p0, float p1, float p2, float p3)l
extern _native void unk_0x44473EFC(Cam p0)l
extern _native bool unk_0xDA931D65(any p0)l
extern _native bool is_screen_faded_out()l
extern _native bool is_screen_faded_in()l
extern _native bool is_screen_fading_out()l
extern _native bool is_screen_fading_in()l
extern _native void do_screen_fade_in(int duration)l
extern _native void do_screen_fade_out(int duration)l
extern _native any set_widescreen_borders(bool p0, int p1)l
extern _native vector3 get_gameplay_cam_coord()l
extern _native vector3 get_gameplay_cam_rot(int rotationOrder)l
extern _native float get_gameplay_cam_fov()l
extern _native void custom_menu_coordinates(float p0)l
extern _native void unk_0x1126E37C(float p0)l
extern _native float get_gameplay_cam_relative_heading()l
extern _native void set_gameplay_cam_relative_heading(float heading)l
extern _native float get_gameplay_cam_relative_pitch()l
extern _native any set_gameplay_cam_relative_pitch(float x, float Value2)l
extern _native void shake_gameplay_cam(const char* shakeName, float intensity)l
extern _native bool is_gameplay_cam_shaking()l
extern _native void set_gameplay_cam_shake_amplitude(float amplitude)l
extern _native void stop_gameplay_cam_shaking(bool p0)l
extern _native void unk_0x7D3007A2(any p0)l
extern _native bool is_gameplay_cam_rendering()l
extern _native bool unk_0xC0B00C20()l
extern _native bool unk_0x60C23785()l
extern _native void unk_0x20BFF6E5(bool p0)l
extern _native32(0xA61FF9AC) void _enable_crosshair_this_frame()l
extern _native bool is_gameplay_cam_looking_behind()l
extern _native void unk_0x2701A9AD(Entity entity)l
extern _native void unk_0xC4736ED3(Entity entity)l
extern _native void unk_0x6B0E9D57()l
extern _native bool is_sphere_visible(vector3 vec, float radius)l
extern _native bool is_follow_ped_cam_active()l
extern _native bool set_follow_ped_cam_cutscene_chat(const char* p0, int p1)l
extern _native void unk_0x8DC53629(bool p0, bool p1)l
extern _native void unk_0x1F9DE6E4()l
extern _native32(0x749909AC) any _clamp_gameplay_cam_yaw(float minimum, float maximum)l
extern _native32(0xFA3A16E7) any _clamp_gameplay_cam_pitch(float minimum, float maximum)l
extern _native32(0x77340650) void _animate_gameplay_cam_zoom(float p0, float distance)l
extern _native any unk_0x4B22C5CB(Vehicle p0, int p1)l
extern _native int get_follow_ped_cam_zoom_level()l
extern _native int get_follow_ped_cam_view_mode()l
extern _native void set_follow_ped_cam_view_mode(int viewMode)l
extern _native bool is_follow_vehicle_cam_active()l
extern _native void unk_0x9DB5D391(bool p0)l
extern _native void set_time_idle_drop(bool p0, bool p1)l
extern _native int get_follow_vehicle_cam_zoom_level()l
extern _native void set_follow_vehicle_cam_zoom_level(int zoomLevel)l
extern _native int get_follow_vehicle_cam_view_mode()l
extern _native void set_follow_vehicle_cam_view_mode(int viewMode)l
extern _native any unk_0xF3B148A6(any p0)l
extern _native void unk_0x1DEBCB45(any p0, any p1)l
extern _native bool is_aim_cam_active()l
extern _native bool unk_0x8F320DE4()l
extern _native bool is_first_person_aim_cam_active()l
extern _native void disable_aim_cam_this_update()l
extern _native32(0x33951005) float _get_gameplay_cam_zoom()l
extern _native any unk_0x9F4AF763(float p0)l
extern _native void unk_0x68BA0730(float p0, float p1)l
extern _native void unk_0x2F29F0D5(float p0, float p1)l
extern _native void unk_0x76DAC96C(float p0, float p1)l
extern _native void unk_0x0E21069D(float p0)l
extern _native void unk_0x71E9C63E(float p0)l
extern _native void unk_0xD1EEBC45(bool p0)l
extern _native32(0x9C84BDA0) vector3 _get_gameplay_cam_coords()l
extern _native32(0x1FFBEFC5) vector3 _get_gameplay_cam_rot(int rotationOrder)l
extern _native int unk_0xACADF916(any p0, any p1)l
extern _native float unk_0x721B763B()l
extern _native float unk_0x23E3F106(any p0)l
extern _native float unk_0x457AE195()l
extern _native float unk_0x46CB3A49()l
extern _native float unk_0x19297A7A()l
extern _native float unk_0xF24777CA()l
extern _native float unk_0x38992E83()l
extern _native void set_gameplay_coord_hint(float p0, float p1, float p2, any p3, any p4, any p5, any p6)l
extern _native void set_gameplay_ped_hint(Ped p0, vector3 vec_1, bool p4, any p5, any p6, any p7)l
extern _native void set_gameplay_vehicle_hint(any p0, float p1, float p2, float p3, bool p4, any p5, any p6, any p7)l
extern _native void set_gameplay_object_hint(any p0, float p1, float p2, float p3, bool p4, any p5, any p6, any p7)l
extern _native void set_gameplay_entity_hint(Entity entity, vector3 Offset, bool p4, int p5, int p6, int p7, any p8)l
extern _native bool is_gameplay_hint_active()l
extern _native void stop_gameplay_hint(bool p0)l
extern _native void unk_0xCAFEE798(bool p0)l
extern _native void set_gameplay_hint_fov(float FOV)l
extern _native void unk_0x72E8CD3A(float p0)l
extern _native void unk_0x79472AE3(float p0)l
extern _native void unk_0xFC7464A0(float p0)l
extern _native void unk_0x3554AA0E(float p0)l
extern _native void get_is_multiplayer_brief(bool p0)l
extern _native void set_cinematic_button_active(bool p0)l
extern _native bool is_cinematic_cam_rendering()l
extern _native void shake_cinematic_cam(const char* p0, float p1)l
extern _native bool is_cinematic_cam_shaking()l
extern _native void set_cinematic_cam_shake_amplitude(float p0)l
extern _native void stop_cinematic_cam_shaking(bool p0)l
extern _native32(0x5AC6DAC9) void _disable_vehicle_first_person_cam_this_frame()l
extern _native void unk_0x837F8581()l
extern _native void unk_0x65DDE8AF()l
extern _native void unk_0xD75CDD75()l
extern _native bool unk_0x96A07066()l
extern _native void create_cinematic_shot(any p0, int p1, any p2, Entity entity)l
extern _native bool is_cinematic_shot_active(any p0)l
extern _native void stop_cinematic_shot(any p0)l
extern _native void unk_0xFBB85E02(bool p0)l
extern _native void unk_0x4938C82F()l
extern _native void set_cinematic_mode_active(bool p0)l
extern _native any unk_0x6739AD55()l
extern _native void stop_cutscene_cam_shaking()l
extern _native void unk_0x067BA6F5(float p0)l
extern _native Entity unk_0xFD99BE2B(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8)l
extern _native void unk_0xE206C450()l
extern _native32(0xB06CCD38) void _set_cam_effect(int p0)l
#pragma endregion //}
#pragma region WEAPON //{
extern _native void enable_laser_sight_rendering(bool toggle)l
extern _native Hash get_weapon_component_type_model(Hash componentHash)l
extern _native Hash get_weapontype_model(Hash weaponHash)l
extern _native Hash get_weapontype_slot(Hash weaponHash)l
extern _native Hash get_weapontype_group(Hash weaponHash)l
extern _native void set_current_ped_weapon(Ped ped, Hash weaponHash, bool equipNow)l
extern _native bool get_current_ped_weapon(Ped ped, Hash* weaponHash, bool p2)l
extern _native Entity get_current_ped_weapon_entity_index(Ped ped)l
extern _native Hash get_best_ped_weapon(Ped ped, bool p1)l
extern _native bool set_current_ped_vehicle_weapon(Ped ped, Hash weaponHash)l
extern _native bool get_current_ped_vehicle_weapon(Ped ped, Hash* weaponHash)l
extern _native bool is_ped_armed(Ped ped, int p1)l
extern _native bool is_weapon_valid(Hash weaponHash)l
extern _native bool has_ped_got_weapon(Ped ped, Hash weaponHash, bool p2)l
extern _native bool is_ped_weapon_ready_to_shoot(Ped ped)l
extern _native Hash get_ped_weapontype_in_slot(Ped ped, Hash weaponSlot)l
extern _native int get_ammo_in_ped_weapon(Ped ped, Hash weaponhash)l
extern _native void add_ammo_to_ped(Ped ped, Hash weaponHash, int ammo)l
extern _native void set_ped_ammo(Ped ped, Hash weaponHash, int ammo)l
extern _native void set_ped_infinite_ammo(Ped ped, bool toggle, Hash weaponHash)l
extern _native void set_ped_infinite_ammo_clip(Ped ped, bool toggle)l
extern _native void give_weapon_to_ped(Ped ped, Hash weaponHash, int ammoCount, bool isHidden, bool equipNow)l
extern _native void give_delayed_weapon_to_ped(Ped ped, Hash weaponHash, int time, bool equipNow)l
extern _native void remove_all_ped_weapons(Ped ped, bool p1)l
extern _native void remove_weapon_from_ped(Ped ped, Hash weaponHash)l
extern _native void hide_ped_weapon_for_scripted_cutscene(Ped ped, bool toggle)l
extern _native void set_ped_current_weapon_visible(Ped ped, bool visible, bool deselectWeapon, bool p3, bool p4)l
extern _native void set_ped_drops_weapons_when_dead(Ped ped, bool toggle)l
extern _native bool has_ped_been_damaged_by_weapon(Ped ped, Hash weaponHash, int weaponType)l
extern _native void clear_ped_last_weapon_damage(Ped ped)l
extern _native bool has_entity_been_damaged_by_weapon(Entity entity, Hash weaponHash, int weaponType)l
extern _native void clear_entity_last_weapon_damage(Entity entity)l
extern _native void set_ped_drops_weapon(Ped ped)l
extern _native void set_ped_drops_inventory_weapon(Ped ped, Hash weaponHash, vector3 Offset, any p5)l
extern _native int get_max_ammo_in_clip(Ped ped, Hash weaponHash, bool p2)l
extern _native bool get_ammo_in_clip(Ped ped, Hash weaponHash, int* ammo)l
extern _native bool set_ammo_in_clip(Ped ped, Hash weaponHash, int ammo)l
extern _native bool get_max_ammo(Ped ped, Hash weaponHash, int* ammo)l
extern _native void set_ped_ammo_by_type(Ped ped, any ammoType, int ammo)l
extern _native int get_ped_ammo_by_type(Ped ped, any ammoType)l
extern _native void set_ped_ammo_to_drop(any p0, any p1)l
extern _native void unk_0xD6460EA2(float p0)l
extern _native Hash get_ped_ammo_type_from_weapon(Ped ped, Hash weaponHash)l
extern _native bool get_ped_last_weapon_impact_coord(Ped ped, vector3* coords)l
extern _native void set_ped_gadget(Ped ped, Hash gadgetHash, bool p2)l
extern _native bool get_is_ped_gadget_equipped(Ped ped, Hash gadgetHash)l
extern _native Hash get_selected_ped_weapon(Ped ped)l
extern _native void explode_projectiles(Ped ped, Hash weaponHash, bool p2)l
extern _native void remove_all_projectiles_of_type(Hash weaponHash, bool p1)l
extern _native32(0x3612110D) float _get_lockon_range_of_current_ped_weapon(Ped ped)l
extern _native float get_max_range_of_current_ped_weapon(Ped ped)l
extern _native bool has_vehicle_got_projectile_attached(Ped driver, Vehicle vehicle, Hash weaponHash, any p3)l
extern _native void give_weapon_component_to_ped(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native void remove_weapon_component_from_ped(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native bool has_ped_got_weapon_component(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native bool is_ped_weapon_component_active(Ped ped, Hash weaponHash, Hash componentHash)l
extern _native32(0x82EEAF0F) bool _ped_skip_next_reloading(Ped ped)l
extern _native bool make_ped_reload(Ped ped)l
extern _native void request_weapon_asset(Hash weaponHash, int p1, int p2)l
extern _native bool has_weapon_asset_loaded(Hash weaponHash)l
extern _native void remove_weapon_asset(Hash weaponHash)l
extern _native Object create_weapon_object(Hash weaponHash, int ammoCount, vector3 vec, bool showWorldModel, float heading, any p7)l
extern _native void give_weapon_component_to_weapon_object(Object weaponObject, Hash addonHash)l
extern _native void remove_weapon_component_from_weapon_object(any p0, any p1)l
extern _native bool has_weapon_got_weapon_component(Object weapon, Hash addonHash)l
extern _native void give_weapon_object_to_ped(Object weaponObject, Ped ped)l
extern _native bool does_weapon_take_weapon_component(Hash weaponHash, Hash componentHash)l
extern _native Object get_weapon_object_from_ped(Ped ped, bool p1)l
extern _native void set_ped_weapon_tint_index(Ped ped, Hash weaponHash, int tintIndex)l
extern _native int get_ped_weapon_tint_index(Ped ped, Hash weaponHash)l
extern _native void set_weapon_object_tint_index(Object weapon, int tintIndex)l
extern _native int get_weapon_object_tint_index(Object weapon)l
extern _native int get_weapon_tint_count(Hash weaponHash)l
extern _native bool get_weapon_hud_stats(Hash weaponHash, int* outData)l
extern _native bool get_weapon_component_hud_stats(Hash componentHash, int* outData)l
extern _native int get_weapon_clip_size(Hash weaponHash)l
extern _native void set_ped_chance_of_firing_blanks(Ped ped, vector2 Bias)l
extern _native Entity unk_0xEC2E5304(Ped ped, float p1)l
extern _native void request_weapon_high_detail_model(Entity weaponObject)l
extern _native bool is_ped_current_weapon_silenced(Ped ped)l
extern _native bool set_weapon_smokegrenade_assigned(Ped ped)l
extern _native any set_flash_light_fade_distance(float distance)l
extern _native void set_weapon_animation_override(Ped ped, Hash animStyle)l
extern _native int get_weapon_damage_type(Hash weaponHash)l
extern _native void unk_0x64646F1D(Ped ped)l
extern _native bool can_use_weapon_on_parachute(Hash weaponHash)l
#pragma endregion //}
#pragma region ITEMSET //{
extern _native any create_itemset(bool p0)l
extern _native void destroy_itemset(any p0)l
extern _native bool is_itemset_valid(any p0)l
extern _native bool add_to_itemset(any p0, any p1)l
extern _native void remove_from_itemset(any p0, any p1)l
extern _native any get_itemset_size(any p0)l
extern _native any get_indexed_item_in_itemset(any p0, any p1)l
extern _native bool is_in_itemset(any p0, any p1)l
extern _native void clean_itemset(any p0)l
#pragma endregion //}
#pragma region STREAMING //{
extern _native void load_all_objects_now()l
extern _native void load_scene(vector3 vec)l
extern _native any network_update_load_scene()l
extern _native void network_stop_load_scene()l
extern _native bool is_network_loading_scene()l
extern _native void set_interior_active(int interiorID, bool toggle)l
extern _native void request_model(Hash model)l
extern _native void request_menu_ped_model(Hash model)l
extern _native bool has_model_loaded(Hash model)l
extern _native void unk_0x939243FB(int interiorID, const char* roomName)l
extern _native void set_model_as_no_longer_needed(Hash model)l
extern _native bool is_model_in_cdimage(Hash model)l
extern _native bool is_model_valid(Hash model)l
extern _native bool is_model_a_vehicle(Hash model)l
extern _native any request_collision_at_coord(vector3 vec)l
extern _native void request_collision_for_model(Hash model)l
extern _native bool has_collision_for_model_loaded(Hash model)l
extern _native void request_additional_collision_at_coord(float p0, float p1, float p2)l
extern _native bool does_anim_dict_exist(const char* animDict)l
extern _native void request_anim_dict(const char* animDict)l
extern _native bool has_anim_dict_loaded(const char* animDict)l
extern _native void remove_anim_dict(const char* animDict)l
extern _native void request_anim_set(const char* animSet)l
extern _native bool has_anim_set_loaded(const char* animSet)l
extern _native void remove_anim_set(const char* animSet)l
extern _native void request_clip_set(const char* clipSet)l
extern _native bool has_clip_set_loaded(const char* clipSet)l
extern _native void remove_clip_set(const char* clipSet)l
extern _native void request_ipl(const char* iplName)l
extern _native void remove_ipl(const char* iplName)l
extern _native bool is_ipl_active(const char* iplName)l
extern _native void set_streaming(bool toggle)l
extern _native void set_game_pauses_for_streaming(bool toggle)l
extern _native void set_reduce_ped_model_budget(bool toggle)l
extern _native void set_reduce_vehicle_model_budget(bool toggle)l
extern _native void set_ditch_police_models(bool toggle)l
extern _native int get_number_of_streaming_requests()l
extern _native any request_ptfx_asset()l
extern _native bool has_ptfx_asset_loaded()l
extern _native void remove_ptfx_asset()l
extern _native void request_named_ptfx_asset(const char* fxName)l
extern _native bool has_named_ptfx_asset_loaded(const char* fxName)l
extern _native void set_vehicle_population_budget(int p0)l
extern _native void set_ped_population_budget(int p0)l
extern _native void clear_focus()l
extern _native32(0x14680A60) void _set_focus_area(vector3 vec, vector3 offset)l
extern _native void set_focus_entity(Entity entity)l
extern _native bool is_entity_focus(Entity entity)l
extern _native void unk_0x403CD434(const char* p0, bool p1)l
extern _native void unk_0xA07BAEB9(any p0)l
extern _native any format_focus_heading(vector3 vec, float rad, any p4, any p5)l
extern _native any unk_0x72344191(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7, any p8)l
extern _native any unk_0xC0157255(float p0, float p1, float p2, float p3, float p4, float p5, any p6)l
extern _native void unk_0xE80F8ABE(any p0)l
extern _native any unk_0x1B3521F4(any p0)l
extern _native any unk_0x42CFE9C0(any p0)l
extern _native any unk_0x56253356()l
extern _native bool new_load_scene_start(float p0, float p1, float p2, float p3, float p4, float p5, float p6, any p7)l
extern _native bool new_load_scene_start_sphere(float p0, float p1, float p2, float p3, any p4)l
extern _native void new_load_scene_stop()l
extern _native bool is_new_load_scene_active()l
extern _native bool is_new_load_scene_loaded()l
extern _native any unk_0xEAA51103()l
extern _native void start_player_switch(Ped from, Ped to, int flags, int switchType)l
extern _native void stop_player_switch()l
extern _native bool is_player_switch_in_progress()l
extern _native int get_player_switch_type()l
extern _native int get_ideal_player_switch_type(vector3 vec_1, vector3 vec_2)l
extern _native int get_player_switch_state()l
extern _native int get_player_short_switch_state()l
extern _native void unk_0xF0BD420D(int p0)l
extern _native any unk_0x02BA7AC2()l
extern _native void set_player_switch_outro(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8)l
extern _native void unk_0x279077B0(any* p0)l
extern _native void unk_0x55CB21F9()l
extern _native void unk_0x1084F2F4()l
extern _native void unk_0x5B1E995D()l
extern _native void unk_0x4B4B9A13()l
extern _native any unk_0x408F7148()l
extern _native32(0xFB4D062D) void _switch_out_player(Ped ped, int flags, int unknown)l
extern _native void unk_0x2349373B(any p0)l
extern _native any unk_0x74C16879()l
extern _native int set_player_inverted_up()l
extern _native any unk_0xC7A3D279()l
extern _native any destroy_player_in_pause_menu()l
extern _native any unk_0x7154B6FD()l
extern _native void unk_0xE5612C1A(float p0)l
extern _native void unk_0x9CD6A451(float p0, float p1, float p2, float p3)l
extern _native void unk_0x4267DA87()l
extern _native void unk_0x9FA4AF99(bool p0)l
extern _native void unk_0x9EF0A9CF(any* p0, any* p1)l
extern _native void unk_0xF2CDD6A8()l
extern _native any unk_0x17B0A1CD()l
extern _native void unk_0x3DA7AA5D()l
extern _native any unk_0xDAB4BAC0()l
extern _native void prefetch_srl(const char* srl)l
extern _native bool is_srl_loaded()l
extern _native void begin_srl()l
extern _native void end_srl()l
extern _native void set_srl_time(float p0)l
extern _native void unk_0x814D0752(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void unk_0x62F02485(any p0, any p1, any p2, any p3)l
extern _native void unk_0xA6459CAA(bool p0)l
extern _native void unk_0xF8F515E4(any p0)l
extern _native void set_hd_area(vector3 vec, float ground)l
extern _native void clear_hd_area()l
extern _native void unk_0xE243B2AF()l
extern _native void shutdown_creator_budget()l
extern _native bool unk_0xC0E83320(Hash modelHash)l
extern _native void unk_0x1C576388(any p0)l
extern _native any unk_0x3E9C4CBE()l
#pragma endregion //}
#pragma region SCRIPT //{
extern _native void request_script(const char* scriptName)l
extern _native void set_script_as_no_longer_needed(const char* scriptName)l
extern _native bool has_script_loaded(const char* scriptName)l
extern _native bool does_script_exist(const char* scriptName)l
extern _native void request_script_with_name_hash(Hash scriptHash)l
extern _native void set_script_with_name_hash_as_no_longer_needed(Hash scriptHash)l
extern _native bool has_script_with_name_hash_loaded(Hash scriptHash)l
extern _native void terminate_thread(int threadId)l
extern _native bool is_thread_active(int threadId)l
extern _native32(0xBE7ACD89) const char* _get_name_of_thread(int threadId)l
extern _native32(0xBB4E2F66) void _begin_enumerating_threads()l
extern _native32(0x1E28B28F) int _get_id_of_next_thread_in_enumeration()l
extern _native int get_id_of_this_thread()l
extern _native void terminate_this_thread()l
extern _native32(0x029D3841) int _get_number_of_instances_of_script_with_name_hash(Hash scriptHash)l
extern _native const char* get_this_script_name()l
extern _native Hash get_hash_of_this_script_name()l
extern _native int get_number_of_events(bool p0)l
extern _native bool get_event_exists(bool p0, int p1)l
extern _native int get_event_at_index(bool p0, int p1)l
extern _native bool get_event_data(bool p0, int p1, int* p2, int p3)l
extern _native void shutdown_loading_screen()l
extern _native void set_no_loading_screen(bool toggle)l
extern _native void unk_0xB03BCCDF()l
#pragma endregion //}
#pragma region UI //{
extern _native32(0xCB7C8994) void _set_loading_prompt_text_entry(const char* string)l
extern _native32(0x903F5EE4) void _show_loading_prompt(int busySpinnerType)l
extern _native32(0x94119534) void _remove_loading_prompt()l
extern _native void unk_0x71077FBD()l
extern _native32(0xB8B3A5D0) bool _is_loading_prompt_being_displayed()l
extern _native void unk_0xA7C8594B(bool p0)l
extern _native void unk_0x1DA7E41A(float p0)l
extern _native void unk_0x1E63088A()l
extern _native void unk_0x5205C6F5()l
extern _native32(0xECA8ACB9) void _remove_notification(int notificationId)l
extern _native void unk_0x520FCB6D()l
extern _native void unk_0xC8BAB2F2()l
extern _native void unk_0x4D0449C6()l
extern _native void unk_0xD3F40140()l
extern _native any unk_0xC5223796()l
extern _native void unk_0x709B4BCB()l
extern _native void unk_0x4A4A40A4()l
extern _native32(0x294405D4) int _get_current_notification()l
extern _native void unk_0xF881AB87()l
extern _native void unk_0x1D6859CA()l
extern _native32(0xCF14D7F2) void _set_notification_flash_color(RGBA colour)l
extern _native void unk_0x24A97AF8(any p0)l
extern _native void unk_0x44018EDB(bool p0)l
extern _native void unk_0xA4524B23()l
extern _native void unk_0xAFA1148B()l
extern _native void unk_0x3CD4307C()l
extern _native32(0x574EE85C) void _set_notification_text_entry(const char* type)l
extern _native32(0xED130FA1) int _set_notification_message_2(const char* p0, int p1, int p2, int p3, bool p4, const char* picName1, const char* picName2)l
extern _native32(0xE7E3C98B) int _set_notification_message(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject)l
extern _native32(0x0EB382B7) int _set_notification_message_4(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration)l
extern _native32(0x3E807FE3) int _set_notification_message_clan_tag(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration, const char* clanTag)l
extern _native32(0xDEB491C8) int _set_notification_message_clan_tag_2(const char* picName1, const char* picName2, bool flash, int iconType1, const char* sender, const char* subject, float duration, const char* clanTag, int iconType2, int p9)l
extern _native32(0x08F7AF78) int _draw_notification(bool blink, bool p1)l
extern _native32(0x57B8D0D4) int _draw_notification_2(bool blink, bool p1)l
extern _native32(0x02BCAF9B) int _draw_notification_3(bool blink, bool p1)l
extern _native32(0x02DED2B8) int _draw_notification_icon(const char* p0, const char* p1, int p2, int p3, const char* p4)l
extern _native32(0xA9CCEF66) int _notification_send_apartment_invite(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, RGB colour)l
extern _native32(0x88B9B909) int _notification_send_clan_invite(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, const char* playerName, RGB colour)l
extern _native any unk_0xE05E7052(any p0, any p1, any p2)l
extern _native any unk_0x4FA43BA4(any p0, any p1, any p2, any p3)l
extern _native any unk_0x8C90D22F(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native32(0x8E319AB8) int _draw_notification_4(bool blink, bool p1)l
extern _native any unk_0x5E93FBFA(any* p0, any* p1, any p2, any* p3, any* p4, any p5)l
extern _native void begin_text_command_print(const char* GxtEntry)l
extern _native void end_text_command_print(int duration, bool drawImmediately)l
extern _native void begin_text_command_is_message_displayed(const char* text)l
extern _native bool end_text_command_is_message_displayed()l
extern _native void begin_text_command_display_text(const char* text)l
extern _native void end_text_command_display_text(vector2 vector)l
extern _native32(0x51E7A037) void _begin_text_command_width(const char* text)l
extern _native32(0xD12A643A) float _end_text_command_get_width(int font)l
extern _native32(0x94B82066) void _begin_text_command_line_count(const char* entry)l
extern _native32(0xAA318785) int _end_text_command_get_line_count(vector2 vector)l
extern _native void begin_text_command_display_help(const char* inputType)l
extern _native void end_text_command_display_help(any p0, bool loop, bool beep, int shape)l
extern _native void begin_text_command_is_this_help_message_being_displayed(const char* labelName)l
extern _native bool end_text_command_is_this_help_message_being_displayed(int p0)l
extern _native void begin_text_command_set_blip_name(const char* gxtentry)l
extern _native void end_text_command_set_blip_name(Blip blip)l
extern _native32(0x0E103475) void _begin_text_command_objective(const char* p0)l
extern _native32(0x2944A6C5) void _end_text_command_objective(bool p0)l
extern _native void begin_text_command_clear_print(const char* text)l
extern _native void end_text_command_clear_print()l
extern _native32(0xBF855650) void _begin_text_command_timer(const char* p0)l
extern _native32(0x6E7FDA1C) void _end_text_command_timer(bool p0)l
extern _native void add_text_component_integer(int value)l
extern _native void add_text_component_float(float value, int decimalPlaces)l
extern _native void add_text_component_substring_text_label(const char* labelName)l
extern _native void add_text_component_substring_text_label_hash_key(Hash gxtEntryHash)l
extern _native void add_text_component_substring_blip_name(Blip blip)l
extern _native void add_text_component_substring_player_name(const char* text)l
extern _native void add_text_component_substring_time(int timestamp, int flags)l
extern _native void add_text_component_formatted_integer(int value, bool commaSeparated)l
extern _native32(0x65E1D404) void _add_text_component_app_title(const char* p0, int p1)l
extern _native void add_text_component_substring_website(const char* website)l
extern _native32(0x0829A799) void _add_text_component_scaleform(const char* p0)l
extern _native32(0x6F1A1901) void _set_notification_color_next(int p0)l
extern _native32(0x34A396EE) const char* _get_text_substring(const char* text, int position, int length)l
extern _native32(0x0183A66C) const char* _get_text_substring_safe(const char* text, int position, int length, int maxLength)l
extern _native32(0xFA6373BB) const char* _get_text_substring_slice(const char* text, int startPosition, int endPosition)l
extern _native32(0x95C4B5AD) const char* _get_label_text(const char* labelName)l
extern _native void clear_prints()l
extern _native void clear_brief()l
extern _native void clear_all_help_messages()l
extern _native void clear_this_print(const char* p0)l
extern _native void clear_small_prints()l
extern _native bool does_text_block_exist(const char* gxt)l
extern _native void request_additional_text(const char* gxt, int slot)l
extern _native32(0xF4D27EBE) void _request_additional_text_2(const char* gxt, int slot)l
extern _native bool has_additional_text_loaded(int slot)l
extern _native void clear_additional_text(int p0, bool p1)l
extern _native bool is_streaming_additional_text(int p0)l
extern _native bool has_this_additional_text_loaded(const char* gxt, int slot)l
extern _native bool is_message_being_displayed()l
extern _native bool does_text_label_exist(const char* gxt)l
extern _native int get_length_of_string_with_this_text_label(const char* gxt)l
extern _native int get_length_of_literal_string(const char* string)l
extern _native32(0x7DBC0764) int _get_length_of_string(const char* p0)l
extern _native const char* get_street_name_from_hash_key(Hash hash)l
extern _native bool is_hud_preference_switched_on()l
extern _native bool is_radar_preference_switched_on()l
extern _native bool is_subtitle_preference_switched_on()l
extern _native void display_hud(bool toggle)l
extern _native void unk_0xC380AC85()l
extern _native void unk_0xC47AB1B0()l
extern _native any display_radar(bool Toggle)l
extern _native bool is_hud_hidden()l
extern _native bool is_radar_hidden()l
extern _native void set_blip_route(Blip blip, bool enabled)l
extern _native void set_blip_route_colour(Blip blip, int colour)l
extern _native void add_next_message_to_previous_briefs(bool p0)l
extern _native void unk_0x9854485F(bool p0)l
extern _native void responding_as_temp(float p0)l
extern _native void set_radar_zoom(int zoomLevel)l
extern _native void unk_0x25EC28C0(any p0, float p1)l
extern _native32(0x09CF1CE5) void _set_radar_zoom_level_this_frame(float zoomLevel)l
extern _native void unk_0xE8D3A910()l
extern _native void get_hud_colour(int hudColorIndex, int* r, int* g, int* b, int* a)l
extern _native void unk_0x0E41E45C(RGBA colour)l
extern _native void unk_0x6BE3ACA8(RGBA colour)l
extern _native32(0x3B216749) void _set_hud_colours_switch(int hudColorIndex, int hudColorIndex2)l
extern _native32(0xF6E7E92B) void _set_hud_colour(int hudColorIndex, RGBA colour)l
extern _native void flash_ability_bar(bool toggle)l
extern _native void set_ability_bar_value(float p0, float p1)l
extern _native any flash_wanted_display(bool p0)l
extern _native32(0x3330175B) float _get_text_scale_height(float size, int font)l
extern _native void set_text_scale(float p0, float size)l
extern _native void set_text_colour(RGBA colour)l
extern _native void set_text_centre(bool align)l
extern _native void set_text_right_justify(bool toggle)l
extern _native void set_text_justification(int justifyType)l
extern _native void set_text_wrap(float start, float end)l
extern _native void set_text_leading(bool p0)l
extern _native void set_text_proportional(bool p0)l
extern _native void set_text_font(int fontType)l
extern _native void set_text_drop_shadow()l
extern _native void set_text_dropshadow(int distance, RGBA colour)l
extern _native void set_text_outline()l
extern _native void set_text_edge(int p0, RGBA colour)l
extern _native void set_text_render_id(int renderId)l
extern _native int get_default_script_rendertarget_render_id()l
extern _native bool register_named_rendertarget(const char* p0, bool p1)l
extern _native bool is_named_rendertarget_registered(const char* p0)l
extern _native bool release_named_rendertarget(any* p0)l
extern _native void link_named_rendertarget(Hash hash)l
extern _native any get_named_rendertarget_render_id(const char* p0)l
extern _native bool is_named_rendertarget_linked(Hash hash)l
extern _native void clear_help(bool toggle)l
extern _native bool is_help_message_on_screen()l
extern _native bool unk_0x812CBE0E()l
extern _native bool is_help_message_being_displayed()l
extern _native bool is_help_message_fading_out()l
extern _native bool unk_0x87871CE0()l
extern _native32(0xB9827942) int _get_blip_info_id_iterator()l
extern _native int get_number_of_active_blips()l
extern _native Blip get_next_blip_info_id(int blipSprite)l
extern _native Blip get_first_blip_info_id(int blipSprite)l
extern _native vector3 get_blip_info_id_coord(Blip blip)l
extern _native int get_blip_info_id_display(Blip blip)l
extern _native int get_blip_info_id_type(Blip blip)l
extern _native Entity get_blip_info_id_entity_index(Blip blip)l
extern _native Pickup get_blip_info_id_pickup_index(Blip blip)l
extern _native Blip get_blip_from_entity(Entity entity)l
extern _native Blip add_blip_for_radius(vector3 pos, float radius)l
extern _native Blip add_blip_for_entity(Entity entity)l
extern _native Blip add_blip_for_pickup(Pickup pickup)l
extern _native Blip add_blip_for_coord(vector3 vec)l
extern _native void unk_0xBF25E7B2(vector3 pos, float radius, int p4)l
extern _native void unk_0xE7E1E32B(bool p0)l
extern _native void set_blip_coords(Blip blip, vector3 pos)l
extern _native vector3 get_blip_coords(Blip blip)l
extern _native void set_blip_sprite(Blip blip, int spriteId)l
extern _native int get_blip_sprite(Blip blip)l
extern _native void set_blip_name_from_text_file(Blip blip, const char* gxtEntry)l
extern _native void set_blip_name_to_player_name(Blip blip, Player player)l
extern _native void set_blip_alpha(Blip blip, int alpha)l
extern _native int get_blip_alpha(Blip blip)l
extern _native void set_blip_fade(Blip blip, int opacity, int duration)l
extern _native void set_blip_rotation(Blip blip, int rotation)l
extern _native void set_blip_flash_timer(Blip blip, int duration)l
extern _native void set_blip_flash_interval(Blip blip, any p1)l
extern _native void set_blip_colour(Blip blip, int color)l
extern _native void set_blip_secondary_colour(Blip blip, FloatRGB colour)l
extern _native int get_blip_colour(Blip blip)l
extern _native int get_blip_hud_colour(Blip blip)l
extern _native bool is_blip_short_range(Blip blip)l
extern _native bool is_blip_on_minimap(Blip blip)l
extern _native bool unk_0x3E47F357(any p0)l
extern _native void unk_0x43996428(any p0, bool p1)l
extern _native void set_blip_high_detail(Blip blip, bool toggle)l
extern _native void set_blip_as_mission_creator_blip(Blip blip, bool toggle)l
extern _native bool is_mission_creator_blip(Blip blip)l
extern _native Blip disable_blip_name_for_var()l
extern _native bool unk_0xC5EB849A()l
extern _native void unk_0xA2CAAB4F(bool p0)l
extern _native void set_blip_flashes(Blip blip, bool toggle)l
extern _native void set_blip_flashes_alternate(Blip blip, bool toggle)l
extern _native bool is_blip_flashing(Blip blip)l
extern _native void set_blip_as_short_range(Blip blip, bool toggle)l
extern _native void set_blip_scale(Blip blip, float scale)l
extern _native void set_blip_priority(Blip blip, int priority)l
extern _native void set_blip_display(Blip blip, int displayId)l
extern _native void set_blip_category(Blip blip, int index)l
extern _native void remove_blip(Blip* blip)l
extern _native void set_blip_as_friendly(Blip blip, bool toggle)l
extern _native void pulse_blip(Blip blip)l
extern _native void show_number_on_blip(Blip blip, int number)l
extern _native void hide_number_on_blip(Blip blip)l
extern _native void unk_0x1D99F676(any p0, bool p1)l
extern _native32(0x3DCF0092) void _set_blip_checked(Blip blip, bool toggle)l
extern _native void show_heading_indicator_on_blip(Blip blip, bool toggle)l
extern _native32(0x8DE82C15) void _set_blip_friendly(Blip blip, bool toggle)l
extern _native32(0x4C8F02B4) void _set_blip_friend(Blip blip, bool toggle)l
extern _native void unk_0xABBE1E45(any p0, bool p1)l
extern _native void unk_0x6AA6A1CC(any p0, bool p1)l
extern _native32(0xC575F0BC) void _set_blip_shrink(Blip blip, bool toggle)l
extern _native void unk_0x40E25DB8(any p0, bool p1)l
extern _native bool does_blip_exist(Blip blip)l
extern _native void set_waypoint_off()l
extern _native void unk_0x62BABF2C()l
extern _native void refresh_waypoint()l
extern _native bool is_waypoint_active()l
extern _native void set_new_waypoint(vector2 vector)l
extern _native void set_blip_bright(Blip blip, bool toggle)l
extern _native void set_blip_show_cone(Blip blip, bool toggle)l
extern _native void unk_0x41B0D022(Ped ped)l
extern _native any set_minimap_component(int p0, bool p1, int p2)l
extern _native Blip get_main_player_blip_id()l
extern _native void hide_loading_on_fade_this_frame()l
extern _native void set_radar_as_interior_this_frame(Hash interior, vector2 vector, int z, int zoom)l
extern _native void set_radar_as_exterior_this_frame()l
extern _native32(0x54E75C7D) void _set_player_blip_position_this_frame(vector2 vector)l
extern _native any unk_0x199DED14()l
extern _native32(0x1A4318F7) void _disable_radar_this_frame()l
extern _native void unk_0xCE36E3FE()l
extern _native32(0x334EFD46) void _center_player_on_radar_this_frame()l
extern _native void set_widescreen_format(any p0)l
extern _native void display_area_name(bool toggle)l
extern _native void display_cash(bool toggle)l
extern _native void display_ammo_this_frame(bool display)l
extern _native void display_sniper_scope_this_frame()l
extern _native void hide_hud_and_radar_this_frame()l
extern _native void unk_0x5476B9FD(bool p0)l
extern _native void unk_0xF4F3C796()l
extern _native void unk_0x7BFFE82F()l
extern _native void set_multiplayer_bank_cash()l
extern _native void remove_multiplayer_bank_cash()l
extern _native void set_multiplayer_hud_cash(int p0, int p1)l
extern _native void remove_multiplayer_hud_cash()l
extern _native void hide_help_text_this_frame()l
extern _native void display_help_text_this_frame(const char* message, bool p1)l
extern _native32(0x1EFFB02A) void _show_weapon_wheel(bool forcedShow)l
extern _native void unk_0xB26FED2B()l
extern _native Hash unk_0x22E9F555()l
extern _native void unk_0x83B608A0(Hash weaponHash)l
extern _native void unk_0xE70D1F43(bool p0)l
extern _native void set_gps_flags(int p0, float p1)l
extern _native void clear_gps_flags()l
extern _native void unk_0xFB9BABF5(bool p0)l
extern _native void clear_gps_race_track()l
extern _native void unk_0x7F93799B(any p0, bool p1, bool p2)l
extern _native void unk_0xEEBDFE55(any p0, any p1, any p2)l
extern _native void unk_0xDA0AF00E(bool p0, any p1, any p2)l
extern _native void unk_0xCF2E3E24()l
extern _native void unk_0xC3DCBEDB(any p0, bool p1, bool p2)l
extern _native void unk_0xFE485135(vector3 vec)l
extern _native void unk_0xE87CBE4C(bool p0)l
extern _native void unk_0x0D9969E4()l
extern _native void clear_gps_player_waypoint()l
extern _native void set_gps_flashes(bool toggle)l
extern _native void flash_minimap_display()l
extern _native void unk_0x79A6CAF6(any p0)l
extern _native void toggle_stealth_radar(bool toggle)l
extern _native void key_hud_colour(bool p0, any p1)l
extern _native void set_mission_name(bool p0, const char* name)l
extern _native void unk_0x8D9A1734(bool p0, any* p1)l
extern _native void unk_0xD2161E77(bool p0, any* p1, any* p2, any* p3, any* p4, any* p5, any* p6, any* p7, any* p8)l
extern _native void set_minimap_block_waypoint(bool toggle)l
extern _native32(0x02F5F1D1) void _set_north_yankton_map(bool toggle)l
extern _native32(0xD8D77733) void _set_minimap_revealed(bool toggle)l
extern _native float unk_0xA4098ACC()l
extern _native32(0x65B705F6) bool _is_minimap_area_revealed(vector2 vector, float radius)l
extern _native void unk_0xE010F081(vector3 vec)l
extern _native void unk_0x5133A750(any p0)l
extern _native void unk_0x20FD3E87()l
extern _native void lock_minimap_angle(int angle)l
extern _native void unlock_minimap_angle()l
extern _native void lock_minimap_position(vector2 vector)l
extern _native void unlock_minimap_position()l
extern _native32(0x0308EDF6) void _set_minimap_attitude_indicator_level(float altitude, bool p1)l
extern _native void unk_0x7FB6FB2A(any p0, any p1, bool p2)l
extern _native void unk_0xF07D8CEF(any p0)l
extern _native void unk_0x827F14DE(any p0)l
extern _native32(0x08EB83D2) void _set_radar_bigmap_enabled(bool toggleBigMap, bool showFullMap)l
extern _native bool is_hud_component_active(int id)l
extern _native bool is_scripted_hud_component_active(int id)l
extern _native void hide_scripted_hud_component_this_frame(int id)l
extern _native bool unk_0xE8C8E535(any p0)l
extern _native void hide_hud_component_this_frame(int id)l
extern _native void show_hud_component_this_frame(int id)l
extern _native void unk_0x52746FE1()l
extern _native void reset_reticule_values()l
extern _native void reset_hud_component_values(int id)l
extern _native void set_hud_component_position(int id, vector2 vector)l
extern _native vector3 get_hud_component_position(int id)l
extern _native void clear_reminder_message()l
extern _native32(0xFE9A39F8) bool _get_screen_coord_from_world_coord(vector3 world, float* screenX, float* screenY)l
extern _native void unk_0x10DE5150()l
extern _native void unk_0x67649EE0()l
extern _native any unk_0x9D2C94FA()l
extern _native bool unk_0x45472FD5(any p0)l
extern _native void unk_0x198F32D7(any p0, float p1, float p2)l
extern _native void unk_0x93045157(any p0, vector3 vec)l
extern _native void unk_0x18B012B7(any p0, any p1, float p2, float p3)l
extern _native void unk_0x97852A82(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void clear_floating_help(any p0, bool p1)l
extern _native32(0xC969F2D0) void _create_mp_gamer_tag_color(int headDisplayId, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, any p5, RGB colour)l
extern _native bool unk_0xEFD2564A()l
extern _native32(0xF5CD2AA4) int _create_mp_gamer_tag(Ped ped, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, any p5)l
extern _native void remove_mp_gamer_tag(int gamerTagId)l
extern _native bool is_mp_gamer_tag_active(int gamerTagId)l
extern _native bool add_trevor_random_modifier(int gamerTagId)l
extern _native void set_mp_gamer_tag_visibility(int gamerTagId, int component, bool toggle)l
extern _native void unk_0x767DED29(int headDisplayId, bool p1)l
extern _native void unk_0xB01A5434(int headDisplayId, bool p1)l
extern _native void set_mp_gamer_tag_colour(int gamerTagId, int flag, int color)l
extern _native32(0x5777EC77) void _set_mp_gamer_tag_health_bar_color(int headDisplayId, int color)l
extern _native void set_mp_gamer_tag_alpha(int gamerTagId, int component, int alpha)l
extern _native void set_mp_gamer_tag_wanted_level(int gamerTagId, int wantedlvl)l
extern _native void set_mp_gamer_tag_name(int gamerTagId, const char* string)l
extern _native bool unk_0xF11414C4(int gamerTagId)l
extern _native void unk_0x939218AB(int gamerTagId, const char* string)l
extern _native any unk_0xAB5B7C18()l
extern _native int get_current_website_id()l
extern _native any unk_0xD217EE7E(any p0)l
extern _native void set_warning_message(const char* entryLine1, int instructionalKey, const char* entryLine2, bool p3, any p4, any* p5, any* p6, bool background)l
extern _native32(0x2DB9EAB5) void _set_warning_message_2(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, any p5, any* p6, any* p7, bool background)l
extern _native32(0x749929D3) void _set_warning_message_3(const char* entryHeader, const char* entryLine1, any instructionalKey, const char* entryLine2, bool p4, any p5, any p6, any* p7, any* p8, bool p9)l
extern _native bool is_warning_message_active()l
extern _native void unk_0x2F9A309C()l
extern _native32(0xE4FD20D8) void _set_map_full_screen(bool toggle)l
extern _native void unk_0x13E7A5A9(any p0)l
extern _native any unk_0x786CA0A2(float p0, float p1, float p2)l
extern _native void unk_0xCBEC9369()l
extern _native any unk_0x3F4AFB13()l
extern _native void unk_0x2F28F0A6(bool p0)l
extern _native void unk_0x801D0D86()l
extern _native void unk_0x317775DF()l
extern _native void activate_frontend_menu(Hash menuhash, bool Toggle_Pause, int component)l
extern _native void restart_frontend_menu(Hash menuHash, int p1)l
extern _native32(0x33D6868F) Hash _get_current_frontend_menu()l
extern _native void set_pause_menu_active(bool toggle)l
extern _native void disable_frontend_this_frame()l
extern _native void unk_0x7F349900()l
extern _native void unk_0x630CD8EE()l
extern _native void set_frontend_active(bool active)l
extern _native bool is_pause_menu_active()l
extern _native any unk_0xC85C4487()l
extern _native int get_pause_menu_state()l
extern _native bool is_pause_menu_restarting()l
extern _native32(0x2DFD35C7) void _log_debug_info(const char* p0)l
extern _native void unk_0x0A89336C(any p0)l
extern _native void unk_0xC84BE309()l
extern _native32(0x9FE8FD5E) void _add_frontend_menu_context(Hash hash)l
extern _native void object_decal_toggle(Hash hash)l
extern _native bool unk_0xC51BC42F(Hash hash)l
extern _native any unk_0x016D7AF9()l
extern _native void enable_deathblood_seethrough(bool p0)l
extern _native void unk_0x6C67131A(bool p0, any p1, any p2)l
extern _native void unk_0x11D09737(bool p0)l
extern _native any unk_0xD3BF3ABD()l
extern _native void unk_0xC06B763D()l
extern _native void unk_0xB9392CE7()l
extern _native any unk_0x92DAFA78()l
extern _native any unk_0x22CA9F2A()l
extern _native any unk_0xDA7951A2()l
extern _native any unk_0x7D95AFFF()l
extern _native any unk_0x96863460()l
extern _native void unk_0x8543AAC8(any* p0, any* p1)l
extern _native void unk_0x6025AA2F(any* p0, any* p1, any* p2)l
extern _native bool unk_0x46794EB2(int* p0, int* p1, int* p2)l
extern _native bool set_userids_uihidden(any p0, any* p1)l
extern _native bool unk_0xD6CC4766(any p0, any* p1, any p2, any p3)l
extern _native bool unk_0x51972B04(any p0, float* p1)l
extern _native bool unk_0xD43BB56D(Hash p0, any* p1)l
extern _native void clear_ped_in_pause_menu()l
extern _native void give_ped_to_pause_menu(Ped ped, int p1)l
extern _native void unk_0x127310EB(bool p0)l
extern _native void unk_0x8F45D327(bool p0)l
extern _native32(0x19FCBBB2) void _show_social_club_legal_screen()l
extern _native any unk_0x850690FF()l
extern _native int unk_0x9D4934F4()l
extern _native void unk_0x57218529()l
extern _native void unk_0x5F86AA39()l
extern _native void unk_0x7AD67C95(const char* p0)l
extern _native bool is_social_club_active()l
extern _native void unk_0xFF06772A(bool p0)l
extern _native32(0x96C4C4DD) void _set_ped_enemy_ai_blip(int pedHandle, bool showViewCones)l
extern _native bool does_ped_have_ai_blip(Ped ped)l
extern _native void unk_0xD8E31B1A(Ped ped, int unk)l
extern _native void hide_special_ability_lockon_operation(any p0, bool p1)l
extern _native void unk_0xFFDF46F0(Ped ped, bool p1)l
extern _native32(0xF9DC2AF7) void _set_ai_blip_max_distance(Ped ped, float p1)l
extern _native any* unk_0x06349065(Ped ped)l
extern _native Blip unk_0xCA52CF43(Ped ped)l
#pragma endregion //}
#pragma region GRAPHICS //{
extern _native void set_debug_lines_and_spheres_drawing_active(bool enabled)l
extern _native void draw_debug_line(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void draw_debug_line_with_two_colours(vector3 vec_1, vector3 vec_2, RGB colour_1, RGB colour_2, int alpha1, int alpha2)l
extern _native void draw_debug_sphere(vector3 vec, float radius, RGBA colour)l
extern _native void draw_debug_box(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void draw_debug_cross(vector3 vec, float size, RGBA colour)l
extern _native void draw_debug_text(const char* text, vector3 vec, RGBA colour)l
extern _native void draw_debug_text_2d(const char* text, vector3 vec, RGBA colour)l
extern _native void draw_line(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void draw_poly(vector3 vec_1, vector3 vec_2, vector3 vec_3, RGBA colour)l
extern _native void draw_box(vector3 vec_1, vector3 vec_2, RGBA colour)l
extern _native void unk_0xC44C2F44(bool p0)l
extern _native any unk_0xBA9AD458()l
extern _native any unk_0xADBBA287()l
extern _native void unk_0x9E553002()l
extern _native bool unk_0x56C1E488(any* p0, any p1, any p2, any p3)l
extern _native int unk_0x226B08EA(any* p0)l
extern _native any unk_0x1F3CADB0()l
extern _native any unk_0xA9DC8558()l
extern _native void unk_0x88EAF398()l
extern _native any unk_0x47B0C137()l
extern _native any unk_0x65376C9B()l
extern _native void unk_0x9CBA682A()l
extern _native any unk_0x3B15D33C(int p0)l
extern _native any unk_0xEC5D0317()l
extern _native bool unk_0x25D569EB(any p0)l
extern _native any unk_0xCFCDC518(any p0)l
extern _native void unk_0x108F36CC()l
extern _native void unk_0xE9F2B68F(bool p0, bool p1)l
extern _native int get_maximum_number_of_photos()l
extern _native any unk_0x239272BD()l
extern _native int unk_0x21DBF0C9()l
extern _native any unk_0x199FABF0(any p0)l
extern _native any unk_0x596B900D(any p0)l
extern _native void unk_0xC9EF81ED()l
extern _native any unk_0x9D84554C(any p0)l
extern _native any unk_0x9C106AD9(any p0)l
extern _native32(0x762E5C5F) int _return_two(any p0)l
extern _native void draw_light_with_range(vector3 pos, RGB color, float range, float intensity)l
extern _native void draw_spot_light(vector3 pos, vector3 dir, RGB color, float distance, float brightness, float roundness, float radius, float falloff)l
extern _native32(0x32BF9598) void _draw_spot_light_with_shadow(vector3 pos, vector3 dir, RGB color, float distance, float brightness, float roundness, float radius, float falloff, float shadow)l
extern _native void unk_0x93628786(float p0)l
extern _native void draw_marker(int type, vector3 pos, vector3 dir, vector3 rot, vector3 scale, RGBA colour, bool bobUpAndDown, bool faceCamera, int p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts)l
extern _native int create_checkpoint(int type, vector3 pos1, vector3 pos2, float radius, RGBA colour, int reserved)l
extern _native void unk_0x80151CCF(int checkpoint, float p0)l
extern _native void set_checkpoint_cylinder_height(int checkpoint, float nearHeight, float farHeight, float radius)l
extern _native void set_checkpoint_rgba(int checkpoint, RGBA colour)l
extern _native32(0xA5456DBB) void _set_checkpoint_icon_rgba(int checkpoint, RGBA colour)l
extern _native void unk_0x20EABD0F(int checkpoint, vector3 pos, vector3 unk)l
extern _native void unk_0x1E3A3126(int checkpoint)l
extern _native void delete_checkpoint(int checkpoint)l
extern _native void unk_0x932FDB81(bool p0)l
extern _native void unk_0x7E946E87(bool p0)l
extern _native void request_streamed_texture_dict(const char* textureDict, bool p1)l
extern _native bool has_streamed_texture_dict_loaded(const char* textureDict)l
extern _native void set_streamed_texture_dict_as_no_longer_needed(const char* textureDict)l
extern _native void draw_rect(vector2 vector, Size size, RGBA colour)l
extern _native void unk_0xF8FBCC25(bool p0)l
extern _native32(0xADF81D24) void _set_2d_layer(int layer)l
extern _native32(0x228A2598) void _set_screen_draw_position(int x, int y)l
extern _native32(0x3FE33BD6) void _screen_draw_position_end()l
extern _native32(0x76C641E4) void _screen_draw_position_ratio(vector2 vector, float p2, float p3)l
extern _native float get_safe_zone_size()l
extern _native void draw_sprite(const char* textureDict, const char* textureName, vector2 screen, Size size, float heading, RGBA colour)l
extern _native any add_entity_icon(Entity entity, const char* icon)l
extern _native void set_entity_icon_visibility(Entity entity, bool toggle)l
extern _native void set_entity_icon_color(Entity entity, RGBA colour)l
extern _native void set_draw_origin(vector3 vec, any p3)l
extern _native void clear_draw_origin()l
extern _native void attach_tv_audio_to_entity(Entity entity)l
extern _native void set_tv_audio_frontend(bool toggle)l
extern _native int load_movie_mesh_set(const char* movieMeshSetName)l
extern _native void release_movie_mesh_set(int movieMeshSet)l
extern _native any unk_0x9D5D9B38(any p0)l
extern _native void get_screen_resolution(int* x, int* y)l
extern _native bool get_is_widescreen()l
extern _native bool get_is_hidef()l
extern _native void set_nightvision(bool toggle)l
extern _native32(0x62619061) bool _is_nightvision_inactive()l
extern _native void set_noiseoveride(bool toggle)l
extern _native void set_noisinessoveride(float value)l
extern _native bool get_screen_coord_from_world_coord(vector3 world, float* screenX, float* screenY)l
extern _native vector3 get_texture_resolution(const char* textureDict, const char* textureName)l
extern _native void unk_0x455F1084(float p0)l
extern _native void set_flash(float p0, float p1, float fadeIn, float duration, float fadeOut)l
extern _native void unk_0x0DCC0B8B()l
extern _native32(0xAA2A0EAF) void _set_blackout(bool enable)l
extern _native Object create_tracked_point()l
extern _native any set_tracked_point_info(Object point, vector3 vec, float radius)l
extern _native bool is_tracked_point_visible(Object point)l
extern _native void destroy_tracked_point(Object point)l
extern _native void unk_0x48F16186()l
extern _native void unk_0x13D4ABC0(float p0)l
extern _native void unk_0xD2157428(float p0)l
extern _native void unk_0xC07C64C9(float p0)l
extern _native32(0xFE903D0F) void _set_far_shadows_suppressed(bool toggle)l
extern _native void unk_0xDE10BA1F(const char* p0)l
extern _native void unk_0x9F470BE3(bool p0)l
extern _native void unk_0x4A124267(bool p0)l
extern _native any unk_0xB19B2764(float p0)l
extern _native void unk_0x342FA2B4(bool p0)l
extern _native void unk_0x5D3BFFC9(bool p0)l
extern _native void unk_0xD9653728(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8)l
extern _native void unk_0x72BA8A14(float p0, float p1, float p2)l
extern _native void unk_0x804F444C(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)l
extern _native void unk_0xBB1A1294(any p0, any p1)l
extern _native void unk_0x1A1A72EF(bool p0)l
extern _native void unk_0x3BB12B75(int type, vector3 Pos, float p4, RGBA colour)l
extern _native void unk_0x4EA70FB4(float p0, float p1, float p2, float p3, float p4)l
extern _native void unk_0x0D830DC7(bool p0)l
extern _native any unk_0xA08B46AD()l
extern _native int unk_0xECD470F0(any p0)l
extern _native void set_seethrough(bool toggle)l
extern _native32(0x1FE547F2) bool _is_seethrough_active()l
extern _native void unk_0x654F0287(any p0, float p1)l
extern _native void unk_0xF6B837F0(float p0)l
extern _native any unk_0xD906A3A9()l
extern _native void unk_0xD34A6CBA(bool p0)l
extern _native void unk_0xD8CC7221(any p0)l
extern _native32(0x5604B890) bool _transition_to_blurred(float transitionTime)l
extern _native32(0x46617502) bool _transition_from_blurred(float transitionTime)l
extern _native void unk_0xDB7AECDA()l
extern _native float is_particle_fx_delayed_blink()l
extern _native any unk_0x926B8734()l
extern _native32(0x30ADE541) void _set_frozen_rendering_disabled(bool enabled)l
extern _native void unk_0x0113EAE4()l
extern _native void unk_0xDCBA251B()l
extern _native void unk_0x513D444B(bool p0, bool p1, float p2, float p3, float p4, float p5)l
extern _native bool unk_0xB2410EAB(bool p0)l
extern _native any unk_0x5AB94128()l
extern _native bool unk_0xD63FCB3E(const char* textureDict, bool p1)l
extern _native int start_particle_fx_non_looped_at_coord(const char* effectName, vector3 Pos, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native32(0x633F8C48) bool _start_particle_fx_non_looped_at_coord_2(const char* effectName, vector3 Pos, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native bool start_particle_fx_non_looped_on_ped_bone(const char* effectName, Ped ped, vector3 offset, vector3 rot, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native32(0x161780C1) bool _start_particle_fx_non_looped_on_ped_bone_2(const char* effectName, Ped ped, vector3 offset, vector3 rot, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native bool start_particle_fx_non_looped_on_entity(const char* effectName, Entity entity, vector3 offset, vector3 rot, float scale, bool axisX, bool axisY, bool axisZ)l
extern _native void set_particle_fx_non_looped_colour(FloatRGB colour)l
extern _native void set_particle_fx_non_looped_alpha(float alpha)l
extern _native int start_particle_fx_looped_at_coord(const char* effectName, vector3 vec, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11)l
extern _native int start_particle_fx_looped_on_ped_bone(const char* effectName, Ped ped, vector3 Offset, vector3 Rot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native int start_particle_fx_looped_on_entity(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native32(0x110752B2) int _start_particle_fx_looped_on_entity_2(const char* effectName, Entity entity, vector3 Offset, vector3 Rot, float scale, bool xAxis, bool yAxis, bool zAxis)l
extern _native void stop_particle_fx_looped(int ptfxHandle, bool p1)l
extern _native void remove_particle_fx(int ptfxHandle, bool p1)l
extern _native void remove_particle_fx_from_entity(Entity entity)l
extern _native void remove_particle_fx_in_range(vector3 vec, float radius)l
extern _native bool does_particle_fx_looped_exist(int ptfxHandle)l
extern _native void set_particle_fx_looped_offsets(int ptfxHandle, vector3 vec, vector3 rot)l
extern _native void set_particle_fx_looped_evolution(int ptfxHandle, const char* propertyName, float amount, bool Id)l
extern _native void set_particle_fx_looped_colour(int ptfxHandle, FloatRGB colour, bool p4)l
extern _native void set_particle_fx_looped_alpha(int ptfxHandle, float alpha)l
extern _native void set_particle_fx_looped_scale(int ptfxHandle, float scale)l
extern _native32(0x233DE879) void _set_particle_fx_looped_range(int ptfxHandle, float range)l
extern _native void set_particle_fx_cam_inside_vehicle(bool p0)l
extern _native void set_particle_fx_cam_inside_nonplayer_vehicle(any p0, bool p1)l
extern _native void set_particle_fx_shootout_boat(any p0)l
extern _native void set_particle_fx_blood_scale(bool p0)l
extern _native void enable_clown_blood_vfx(bool toggle)l
extern _native void enable_alien_blood_vfx(bool Toggle)l
extern _native32(0x9C720B61) void _use_particle_fx_asset_next_call(const char* name)l
extern _native void wash_decals_in_range(any p0, any p1, any p2, any p3, any p4)l
extern _native void wash_decals_from_vehicle(Vehicle vehicle, float p1)l
extern _native void fade_decals_in_range(any p0, any p1, any p2, any p3, any p4)l
extern _native void remove_decals_in_range(vector3 vec, float range)l
extern _native void remove_decals_from_object(Object obj)l
extern _native void remove_decals_from_object_facing(Object obj, vector3 vec)l
extern _native void remove_decals_from_vehicle(Vehicle vehicle)l
extern _native int add_decal(int decalType, vector3 pos, float p4, float p5, float p6, float p7, float p8, float p9, Size size, FloatRGB Coef, float opacity, float timeout, bool p17, bool p18, bool p19)l
extern _native any add_petrol_decal(vector3 vec, float groundLvl, float width, float transparency)l
extern _native void unk_0xE3938B0B(float p0)l
extern _native void unk_0xBAEC6ADD(any p0, any p1, any p2, any p3)l
extern _native void unk_0xCCCA6855()l
extern _native void remove_decal(int decal)l
extern _native bool is_decal_alive(int decal)l
extern _native float get_decal_wash_level(int decal)l
extern _native void unk_0xEAB6417C()l
extern _native void unk_0xC2703B88()l
extern _native void unk_0xA706E84D()l
extern _native bool unk_0x242C6A04(vector3 Coord, float p3)l
extern _native void unk_0x335695CF(any p0, any* p1, any* p2)l
extern _native void unk_0x7B786555(any p0)l
extern _native void move_vehicle_decals(any p0, any p1)l
extern _native32(0x12077738) bool _add_clan_decal_to_vehicle(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, any p13, int alpha)l
extern _native void unk_0x667046A8(Vehicle vehicle, any p1)l
extern _native int unk_0x4F4D76E8(Vehicle vehicle, any p1)l
extern _native32(0x6D58F73B) bool _does_vehicle_have_decal(Vehicle vehicle, any p1)l
extern _native void unk_0x9BABCBA4(bool p0)l
extern _native void unk_0xFDF6D8DA(bool p0)l
extern _native void unk_0x2056A015(float p0)l
extern _native void unk_0x0F486429(any* p0)l
extern _native void unk_0xD87CC710(float p0)l
extern _native void unk_0xE29EE145()l
extern _native void disable_vehicle_distantlights(bool toggle)l
extern _native void unk_0x60F72371(bool p0)l
extern _native void set_timecycle_modifier(const char* modifierName)l
extern _native void set_timecycle_modifier_strength(float strength)l
extern _native void set_transition_timecycle_modifier(const char* modifierName, float transition)l
extern _native void unk_0x56345F6B(float p0)l
extern _native void clear_timecycle_modifier()l
extern _native int get_timecycle_modifier_index()l
extern _native any unk_0x03C44E4B()l
extern _native void push_timecycle_modifier()l
extern _native void pop_timecycle_modifier()l
extern _native void unk_0x85BA15A4(const char* p0)l
extern _native void unk_0x9559BB38(float p0)l
extern _native void unk_0x554BA16E(const char* p0)l
extern _native void unk_0xE8F538B5(any* p0, any* p1)l
extern _native void unk_0x805BAB08(any p0)l
extern _native void unk_0x908A335E(any* p0)l
extern _native void unk_0x6776720A()l
extern _native int request_scaleform_movie(const char* scaleformName)l
extern _native int request_scaleform_movie_instance(const char* scaleformName)l
extern _native bool has_scaleform_movie_loaded(int scaleformHandle)l
extern _native bool has_scaleform_container_movie_loaded_into_parent(int scaleformHandle)l
extern _native void set_scaleform_movie_as_no_longer_needed(int* scaleformHandle)l
extern _native void set_scaleform_movie_to_use_system_time(int scaleform, bool toggle)l
extern _native void draw_scaleform_movie(int scaleformHandle, vector2 vector, Size size, RGBA colour, int unk)l
extern _native void draw_scaleform_movie_fullscreen(int scaleform, RGBA colour, int unk)l
extern _native void draw_scaleform_movie_fullscreen_masked(int scaleform1, int scaleform2, RGBA colour)l
extern _native void draw_scaleform_movie_3d(int scaleform, vector3 pos, vector3 rot, float p7, float p8, float p9, vector3 scale, any p13)l
extern _native32(0x899933C8) void _draw_scaleform_movie_3d_non_additive(int scaleform, vector3 pos, vector3 rot, float p7, float p8, float p9, vector3 scale, any p13)l
extern _native void call_scaleform_movie_method(int scaleform, const char* method)l
extern _native32(0x557EDA1D) void _call_scaleform_movie_function_float_params(int scaleform, const char* functionName, float param1, float param2, float param3, float param4, float param5)l
extern _native32(0x91A7FCEB) void _call_scaleform_movie_function_string_params(int scaleform, const char* functionName, const char* param1, const char* param2, const char* param3, const char* param4, const char* param5)l
extern _native32(0x6EAF56DE) void _call_scaleform_movie_function_mixed_params(int scaleform, const char* functionName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, const char* stringParam1, const char* stringParam2, const char* stringParam3, const char* stringParam4, const char* stringParam5)l
extern _native32(0x5D66CE1E) bool _push_scaleform_movie_function_from_hud_component(int hudComponent, const char* functionName)l
extern _native32(0x215ABBE8) bool _push_scaleform_movie_function(int scaleform, const char* functionName)l
extern _native32(0xF6015178) bool _push_scaleform_movie_function_n(const char* functionName)l
extern _native bool unk_0x5E219B67(const char* functionName)l
extern _native32(0x02DBF2D7) void _pop_scaleform_movie_function_void()l
extern _native32(0x2F38B526) any _pop_scaleform_movie_function()l
extern _native bool unk_0x5CD7C3C0(any funcData)l
extern _native int unk_0x2CFB0E6D(any funcData)l
extern _native const char* sitting_tv(int scaleform)l
extern _native32(0x716777CB) void _push_scaleform_movie_function_parameter_int(int value)l
extern _native32(0x9A01FFDA) void _push_scaleform_movie_function_parameter_float(float value)l
extern _native32(0x0D4AE8CB) void _push_scaleform_movie_function_parameter_bool(bool value)l
extern _native void begin_text_command_scaleform_string(const char* componentType)l
extern _native void end_text_command_scaleform_string()l
extern _native32(0x2E80DB52) void _end_text_command_scaleform_string_2()l
extern _native32(0x4DAAD55B) void _push_scaleform_movie_function_parameter_string(const char* value)l
extern _native void unk_0xCCBF0334(const char* p0)l
extern _native bool unk_0x91A081A1(any p0)l
extern _native void unk_0x83A9811D(any p0)l
extern _native32(0x7AF85862) void _request_hud_scaleform(int hudComponent)l
extern _native32(0x79B43255) bool _has_hud_scaleform_loaded(int hudComponent)l
extern _native void unk_0x03D87600(any p0)l
extern _native bool unk_0xE9183D3A(int scaleformHandle)l
extern _native void set_tv_channel(int channel)l
extern _native int get_tv_channel()l
extern _native void set_tv_volume(float volume)l
extern _native float get_tv_volume()l
extern _native void draw_tv_channel(vector2 Pos, Size Scale, float rotation, RGBA colour)l
extern _native void unk_0xB262DE67(int p0, const char* p1, bool p2)l
extern _native void unk_0x78C4DCBE(any p0, const char* p1, any p2)l
extern _native void unk_0xCBE7068F(any p0)l
extern _native32(0x4D1EB0FB) bool _load_tv_channel(Hash tvChannel)l
extern _native void unk_0x796DE696(bool p0)l
extern _native void unk_0xD99EC000(any p0)l
extern _native void enable_movie_subtitles(bool toggle)l
extern _native bool unk_0xE40A0F1A()l
extern _native bool unk_0x2E7D9B98(const char* p0)l
extern _native bool unk_0x9A0E3BFE(const char* p0, Ped ped, int p2, vector3 pos)l
extern _native void unk_0x431AA036()l
extern _native void unk_0x24A7A7F6(bool p0)l
extern _native void unk_0xA1CB6C94(bool p0)l
extern _native void unk_0x3B637AA7(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12)l
extern _native void unk_0xDF552973(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)l
extern _native32(0x1D980479) void _start_screen_effect(const char* effectName, int duration, bool looped)l
extern _native32(0x06BB5CDA) void _stop_screen_effect(const char* effectName)l
extern _native32(0x089D5921) bool _get_screen_effect_is_active(const char* effectName)l
extern _native32(0x4E6D875B) void _stop_all_screen_effects()l
#pragma endregion //}
#pragma region STATS //{
extern _native any stat_clear_slot_for_reload(int statSlot)l
extern _native bool stat_load(int p0)l
extern _native bool stat_save(int p0, bool p1, int p2)l
extern _native void unk_0xC62406A6(any p0)l
extern _native bool stat_load_pending(any p0)l
extern _native any stat_save_pending()l
extern _native any stat_save_pending_or_requested()l
extern _native any stat_delete_slot(any p0)l
extern _native bool stat_slot_is_loaded(any p0)l
extern _native bool unk_0x0BF0F4B2(any p0)l
extern _native any unk_0xCE6B62B5(any p0)l
extern _native void unk_0xCE7A2411(bool p0)l
extern _native bool unk_0x22804C20(any p0)l
extern _native void unk_0x395D18B1(any p0)l
extern _native any unk_0xED7000C8()l
extern _native any unk_0x099FCC86()l
extern _native bool stat_set_int(Hash statName, int value, bool save)l
extern _native bool stat_set_float(Hash statName, float value, bool save)l
extern _native bool stat_set_bool(Hash statName, bool value, bool save)l
extern _native bool stat_set_gxt_label(Hash statName, const char* value, bool save)l
extern _native bool stat_set_date(Hash statName, any* value, int numFields, bool save)l
extern _native bool stat_set_string(Hash statName, const char* value, bool save)l
extern _native bool stat_set_pos(Hash statName, vector3 vec, bool save)l
extern _native bool stat_set_masked_int(Hash statName, any p1, any p2, int p3, bool save)l
extern _native bool stat_set_user_id(Hash statName, const char* value, bool save)l
extern _native bool stat_set_current_posix_time(Hash statName, bool p1)l
extern _native bool stat_get_int(Hash statHash, int* outValue, int p2)l
extern _native bool stat_get_float(Hash statHash, float* outValue, any p2)l
extern _native bool stat_get_bool(Hash statHash, bool* outValue, any p2)l
extern _native bool stat_get_date(Hash statHash, any* p1, any p2, any p3)l
extern _native const char* stat_get_string(Hash statHash, int p1)l
extern _native bool stat_get_pos(any p0, any* p1, any* p2, any* p3, any p4)l
extern _native bool stat_get_masked_int(any p0, any* p1, any p2, any p3, any p4)l
extern _native const char* stat_get_user_id(any p0)l
extern _native const char* stat_get_license_plate(Hash statName)l
extern _native bool stat_set_license_plate(Hash statName, const char* str)l
extern _native void stat_increment(Hash statName, float value)l
extern _native bool unk_0x46F21343()l
extern _native bool unk_0x02F283CE()l
extern _native bool unk_0xC4110917(Hash statName, int p1, float* outValue)l
extern _native void unk_0x343B27E2(int p0)l
extern _native void unk_0xE3247582(int p0)l
extern _native int stat_get_number_of_days(Hash statName)l
extern _native int stat_get_number_of_hours(Hash statName)l
extern _native int stat_get_number_of_minutes(Hash statName)l
extern _native int stat_get_number_of_seconds(Hash statName)l
extern _native32(0x24DD4929) void _stat_set_profile_setting(int profileSetting, int value)l
extern _native int unk_0xDFC25D66(int p0)l
extern _native int unk_0xCA160BCC(int p0)l
extern _native32(0xB5BF87B2) Hash _get_pstat_bool_hash(int index, bool spStat, bool charStat, int character)l
extern _native32(0x1F938864) Hash _get_pstat_int_hash(int index, bool spStat, bool charStat, int character)l
extern _native32(0x3F8E893B) Hash _get_tupstat_bool_hash(int index, bool spStat, bool charStat, int character)l
extern _native32(0xFB93C5A2) Hash _get_tupstat_int_hash(int index, bool spStat, bool charStat, int character)l
extern _native bool stat_get_bool_masked(Hash statName, int mask, int p2)l
extern _native bool stat_set_bool_masked(Hash statName, bool value, int mask, bool save)l
extern _native void unk_0x61ECC465(const char* p0, any p1)l
extern _native void playstats_npc_invite(any* p0)l
extern _native void playstats_award_xp(any p0, any p1, any p2)l
extern _native void playstats_rank_up(any p0)l
extern _native void unk_0x896CDF8D()l
extern _native void unk_0x1A66945F(any p0, any p1)l
extern _native void unk_0xC960E161(any p0, any p1, any p2, any p3, any p4)l
extern _native void playstats_mission_started(any* p0, any p1, any p2, bool p3)l
extern _native void playstats_mission_over(any* p0, any p1, any p2, bool p3, bool p4, bool p5)l
extern _native void playstats_mission_checkpoint(any* p0, any p1, any p2, any p3)l
extern _native void unk_0xAC2C7C63(any* p0, any p1, any p2, any p3)l
extern _native void unk_0x413539BC(any p0, any p1, any p2, float p3)l
extern _native void playstats_race_checkpoint(any p0, any p1, any p2, any p3, any p4)l
extern _native bool unk_0x489E27E7(any* p0, any* p1)l
extern _native void playstats_match_started(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native void playstats_shop_item(any p0, any p1, any p2, any p3, any p4)l
extern _native void unk_0x6602CED6(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native void unk_0x759E0EC9(any p0, any p1, any p2, any p3)l
extern _native void unk_0x62073DF7(any p0, any p1, any p2, any p3)l
extern _native void unk_0x30558CFD(any p0, any p1, any p2)l
extern _native void unk_0x06CE3692(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9)l
extern _native void unk_0x8D5C7B37(any p0)l
extern _native void playstats_website_visited(Hash scaleformHash, int p1)l
extern _native void playstats_friend_activity(any p0, any p1)l
extern _native void playstats_oddjob_done(any p0, any p1, any p2)l
extern _native void playstats_prop_change(any p0, any p1, any p2, any p3)l
extern _native void playstats_cloth_change(any p0, any p1, any p2, any p3, any p4)l
extern _native void unk_0x79716890(any p0, any p1, any p2)l
extern _native void playstats_cheat_applied(const char* cheat)l
extern _native void unk_0x04181752(any* p0, any* p1, any* p2, any* p3)l
extern _native void unk_0x31002201(any* p0, any* p1, any* p2, any* p3)l
extern _native void unk_0xDDD1F1F3(any* p0, any* p1, any* p2, any* p3)l
extern _native void unk_0x66FEB701(int p0, const char* p1)l
extern _native void unk_0x9E2B9522(int time)l
extern _native any leaderboards_get_number_of_columns(any p0, any p1)l
extern _native any leaderboards_get_column_id(any p0, any p1, any p2)l
extern _native any leaderboards_get_column_type(any p0, any p1, any p2)l
extern _native any leaderboards_read_clear_all()l
extern _native any leaderboards_read_clear(any p0, any p1, any p2)l
extern _native bool leaderboards_read_pending(any p0, any p1, any p2)l
extern _native any unk_0x1789437B()l
extern _native bool leaderboards_read_successful(any p0, any p1, any p2)l
extern _native bool leaderboards2_read_friends_by_row(any* p0, any* p1, any p2, bool p3, any p4, any p5)l
extern _native bool leaderboards2_read_by_handle(any* p0, any* p1)l
extern _native bool leaderboards2_read_by_row(any* p0, any* p1, any p2, any* p3, any p4, any* p5, any p6)l
extern _native bool leaderboards2_read_by_rank(any* p0, any p1, any p2)l
extern _native bool leaderboards2_read_by_radius(any* p0, any p1, any* p2)l
extern _native bool leaderboards2_read_by_score_int(any* p0, any p1, any p2)l
extern _native bool leaderboards2_read_by_score_float(any* p0, float p1, any p2)l
extern _native bool unk_0x9BEC3401(any* p0, any* p1, any* p2)l
extern _native bool unk_0xC977D6E2(any* p0)l
extern _native void unk_0xF2DB6A82()l
extern _native bool unk_0x766A74FE(any p0, any* p1)l
extern _native any unk_0x6B90E730(any p0, any p1)l
extern _native float unk_0x509A286F(any p0, any p1)l
extern _native bool leaderboards2_write_data(any* p0)l
extern _native void unk_0x7524E27B(any p0, any p1, float p2)l
extern _native void unk_0x1C5CCC3A(any p0, any p1, any p2)l
extern _native bool leaderboards_cache_data_row(any* p0)l
extern _native void leaderboards_clear_cache_data()l
extern _native void unk_0x88AE9667(any p0)l
extern _native bool leaderboards_get_cache_exists(any p0)l
extern _native any leaderboards_get_cache_time(any p0)l
extern _native any unk_0xCE7CB520(any p0)l
extern _native bool leaderboards_get_cache_data_row(any p0, any p1, any* p2)l
extern _native void unk_0x4AC39C6C(any p0, any p1, any p2)l
extern _native void unk_0x3E69E7C3(any p0, float p1, any p2)l
extern _native void unk_0x2FFD2FA5(any p0, any p1, any p2, any* p3)l
extern _native bool unk_0x23D70C39()l
extern _native void unk_0x0AD43306()l
extern _native void unk_0xC7DE5C30()l
extern _native void unk_0xA3DAC790(int value)l
extern _native void unk_0x726FAE66(int value)l
extern _native void unk_0xF03895A4(int value)l
extern _native void unk_0x4C39CF10(any p0, any p1)l
extern _native void unk_0x2180AE13(any p0, any p1)l
extern _native void unk_0xEE292B91(any p0, float p1)l
extern _native void unk_0xA063CABD()l
extern _native bool unk_0x62C19A3D(any* p0, any* p1)l
extern _native void unk_0x3B4EF322()l
extern _native any unk_0x54E775E0()l
extern _native any unk_0xE3F0D62D(any* p0)l
#pragma endregion //}
#pragma region BRAIN //{
extern _native void add_script_to_random_ped(const char* name, Hash model, float p2, float p3)l
extern _native void register_object_script_brain(const char* scriptName, Hash objectName, int p2, float p3, int p4, int p5)l
extern _native bool is_object_within_brain_activation_range(Object object)l
extern _native void register_world_point_script_brain(any* p0, float p1, any p2)l
extern _native bool is_world_point_within_brain_activation_range()l
extern _native void enable_script_brain_set(int brainSet)l
extern _native void disable_script_brain_set(int brainSet)l
extern _native void unk_0x19B27825()l
extern _native void unk_0xF3A3AB08()l
extern _native void unk_0x949FE53E(const char* action)l
extern _native void unk_0x29CE8BAA(const char* action)l
#pragma endregion //}
#pragma region MOBILE //{
extern _native void create_mobile_phone(int phoneType)l
extern _native void destroy_mobile_phone()l
extern _native void set_mobile_phone_scale(float scale)l
extern _native void set_mobile_phone_rotation(vector3 rot, any p3)l
extern _native void get_mobile_phone_rotation(vector3* rotation, any p1)l
extern _native void set_mobile_phone_position(vector3 pos)l
extern _native void get_mobile_phone_position(vector3* position)l
extern _native void script_is_moving_mobile_phone_offscreen(bool toggle)l
extern _native bool can_phone_be_seen_on_screen()l
extern _native void cell_cam_activate(bool p0, bool p1)l
extern _native32(0x4479B304) void _disable_phone_this_frame(bool toggle)l
extern _native void unk_0xC273BB4D(int* toggle)l
extern _native void unk_0x66DCD9D2(float p0)l
extern _native bool cell_cam_is_char_visible_no_face_check(Entity entity)l
extern _native void get_mobile_phone_render_id(int* renderId)l
#pragma endregion //}
#pragma region APP //{
extern _native bool app_data_valid()l
extern _native int app_get_int(const char* property)l
extern _native float app_get_float(const char* property)l
extern _native const char* app_get_string(const char* property)l
extern _native void app_set_int(const char* property, int value)l
extern _native void app_set_float(const char* property, float value)l
extern _native void app_set_string(const char* property, const char* value)l
extern _native void app_set_app(const char* appName)l
extern _native void app_set_block(const char* blockName)l
extern _native void app_clear_block()l
extern _native void app_close_app()l
extern _native void app_close_block()l
extern _native bool app_has_linked_social_club_account()l
extern _native bool app_has_synced_data(const char* appName)l
extern _native void app_save_data()l
extern _native any app_get_deleted_file_status()l
extern _native bool app_delete_app_data(const char* appName)l
#pragma endregion //}
#pragma region TIME //{
extern _native void set_clock_time(int hour, int minute, int second)l
extern _native void pause_clock(bool toggle)l
extern _native void advance_clock_time_to(int hour, int minute, int second)l
extern _native void add_to_clock_time(int hours, int minutes, int seconds)l
extern _native int get_clock_hours()l
extern _native int get_clock_minutes()l
extern _native int get_clock_seconds()l
extern _native void set_clock_date(int day, int month, int year)l
extern _native int get_clock_day_of_week()l
extern _native int get_clock_day_of_month()l
extern _native int get_clock_month()l
extern _native int get_clock_year()l
extern _native int get_milliseconds_per_game_minute()l
extern _native void get_posix_time(int* year, int* month, int* day, int* hour, int* minute, int* second)l
extern _native void get_local_time(int* year, int* month, int* day, int* hour, int* minute, int* second)l
#pragma endregion //}
#pragma region PATHFIND //{
extern _native void set_roads_in_area(vector3 vec_1, vector3 vec_2, bool unknown1, bool unknown2)l
extern _native void set_roads_in_angled_area(vector3 vec_1, vector3 vec_2, float angle, bool unknown1, bool unknown2, bool unknown3)l
extern _native void set_ped_paths_in_area(vector3 vec_1, vector3 vec_2, bool unknown)l
extern _native bool get_safe_coord_for_ped(vector3 vec, bool onGround, vector3* outPosition, int flags)l
extern _native bool get_closest_vehicle_node(vector3 vec, vector3* outPosition, int nodeType, float p5, float p6)l
extern _native bool get_closest_major_vehicle_node(vector3 vec, vector3* outPosition, float unknown1, int unknown2)l
extern _native bool get_closest_vehicle_node_with_heading(vector3 vec, vector3* outPosition, float* outHeading, int nodeType, float p6, int p7)l
extern _native bool get_nth_closest_vehicle_node(vector3 vec, int nthClosest, vector3* outPosition, any unknown1, any unknown2, any unknown3)l
extern _native int get_nth_closest_vehicle_node_id(vector3 vec, int nth, int nodetype, float p5, float p6)l
extern _native bool get_nth_closest_vehicle_node_with_heading(vector3 vec, int nthClosest, vector3* outPosition, float* heading, any* unknown1, int unknown2, float unknown3, float unknown4)l
extern _native any get_nth_closest_vehicle_node_id_with_heading(vector3 vec, int nthClosest, vector3* outPosition, float outHeading, any p6, float p7, float p8)l
extern _native bool get_nth_closest_vehicle_node_favour_direction(vector3 vec, vector3 desired, int nthClosest, vector3* outPosition, float* outHeading, int nodetype, any p10, any p11)l
extern _native bool get_vehicle_node_properties(vector3 vec, int* density, int* flags)l
extern _native bool is_vehicle_node_id_valid(int vehicleNodeId)l
extern _native void get_vehicle_node_position(int nodeId, vector3* outPosition)l
extern _native32(0xEE4B1219) bool _get_supports_gps_route_flag(int nodeID)l
extern _native32(0x56737A3C) bool _get_is_slow_road_flag(int nodeID)l
extern _native any get_closest_road(vector3 vec, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10)l
extern _native bool load_all_path_nodes(bool keepInMemory)l
extern _native void unk_0xD6A3B458(bool p0)l
extern _native bool unk_0x86E80A17(float p0, float p1, float p2, float p3)l
extern _native bool unk_0x2CDA5012(float p0, float p1, float p2, float p3)l
extern _native void set_roads_back_to_original(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native void set_roads_back_to_original_in_angled_area(vector3 vec_1, vector3 vec_2, float p6)l
extern _native void unk_0x3C5085E4(float p0)l
extern _native void unk_0xD0F51299(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native void set_ped_paths_back_to_original(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native bool get_random_vehicle_node(vector3 vec, float radius, bool p4, bool p5, bool p6, vector3* outPosition, float* heading)l
extern _native void get_street_name_at_coord(vector3 vec, Hash* streetName, Hash* crossingRoad)l
extern _native int generate_directions_to_coord(vector3 vec, bool p3, float* direction, float* p5, float* distToNxJunction)l
extern _native void set_ignore_no_gps_flag(bool ignore)l
extern _native any unk_0x90DF7A4C(bool p0)l
extern _native void set_gps_disabled_zone(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native any unk_0x4B770634()l
extern _native any unk_0x286F82CC()l
extern _native any unk_0xF6422F9A(any p0, any p1, any p2, any p3, any p4)l
extern _native bool is_point_on_road(vector3 vec, Vehicle vehicle)l
extern _native void add_navmesh_required_region(vector2 vector, float radius)l
extern _native void remove_navmesh_required_regions()l
extern _native void disable_navmesh_in_area(any p0, any p1, any p2, any p3, any p4, any p5, any p6)l
extern _native bool are_all_navmesh_regions_loaded()l
extern _native bool is_navmesh_loaded_in_area(vector3 vec_1, vector3 vec_2)l
extern _native any add_navmesh_blocking_object(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, any p8)l
extern _native void update_navmesh_blocking_object(any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, any p8)l
extern _native void remove_navmesh_blocking_object(any p0)l
extern _native bool does_navmesh_blocking_object_exist(any p0)l
extern _native float unk_0x3FE8C5A0(float p0, float p1)l
extern _native float unk_0x3ED21C90(float p0, float p1, float p2, float p3)l
extern _native float unk_0xA07C5B7D(float left, float right)l
extern _native float unk_0x76751DD4(float p0, float p1, float p2, float p3)l
extern _native float calculate_travel_distance_between_points(vector3 vec_1, vector3 vec_2)l
#pragma endregion //}
#pragma region CONTROLS //{
extern _native bool is_control_enabled(int inputGroup, int control)l
extern _native bool is_control_pressed(int inputGroup, int control)l
extern _native bool is_control_released(int inputGroup, int control)l
extern _native bool is_control_just_pressed(int inputGroup, int control)l
extern _native bool is_control_just_released(int inputGroup, int control)l
extern _native int get_control_value(int inputGroup, int control)l
extern _native float get_control_normal(int inputGroup, int control)l
extern _native float unk_0xC49343BB(int inputGroup, int control)l
extern _native bool is_disabled_control_pressed(int inputGroup, int control)l
extern _native bool is_disabled_control_just_pressed(int inputGroup, int control)l
extern _native bool is_disabled_control_just_released(int inputGroup, int control)l
extern _native float get_disabled_control_normal(int inputGroup, int control)l
extern _native float unk_0xF2A65A4C(int inputGroup, int control)l
extern _native int unk_0x0E8EF929(int p0)l
extern _native const char* get_control_instructional_button(int inputGroup, int control, bool p2)l
extern _native const char* unk_0x3EE71F6A(int inputGroup, int control, bool p2)l
extern _native void set_pad_shake(int p0, int duration, int frequency)l
extern _native void stop_pad_shake(any p0)l
extern _native void unk_0x7D65EB6E(any p0, any p1)l
extern _native bool is_look_inverted()l
extern _native int get_local_player_aim_state()l
extern _native void set_playerpad_shakes_when_controller_disabled(bool toggle)l
extern _native void set_input_exclusive(int inputGroup, int control)l
extern _native void disable_control_action(int inputGroup, int control, bool disable)l
extern _native void enable_control_action(int inputGroup, int control, bool enable)l
extern _native void disable_all_control_actions(int inputGroup)l
extern _native void enable_all_control_actions(int inputGroup)l
extern _native bool unk_0xD2C80B2E(const char* p0)l
extern _native bool unk_0xBBFC9050(const char* p0)l
extern _native void unk_0x42140FF9()l
extern _native32(0x2CEDE6C5) void _disable_input_group(int inputGroup)l
#pragma endregion //}
#pragma region DATAFILE //{
extern _native void unk_0x621388FF(any p0)l
extern _native bool unk_0xB41064A4(any p0)l
extern _native bool unk_0x9DB63CFF(any p0)l
extern _native bool unk_0xF09157B0(const char* p0, bool p1, const char* p2, any* p3, any* p4, const char* type, bool p6)l
extern _native bool unk_0xD96860FC(const char* p0, const char* p1, const char* p2, const char* p3, bool p4)l
extern _native bool unk_0x459F2683(const char* p0, any* p1, bool p2, any* p3, any* p4, any* p5, const char* type)l
extern _native bool unk_0xDBB83E2B(const char* p0, const char* p1, const char* p2, const char* p3, const char* type)l
extern _native bool unk_0xBB6321BD(const char* p0, float p1, const char* type)l
extern _native bool unk_0xE8D56DA2(int p0)l
extern _native bool unk_0xCB6A351E(int p0, bool p1)l
extern _native bool unk_0xA4D1B30E(int p0)l
extern _native bool unk_0xB8515B2F(int p0)l
extern _native32(0x660C468E) bool _load_ugc_file(const char* filename)l
extern _native void datafile_create()l
extern _native void datafile_delete()l
extern _native void unk_0x4E03F632()l
extern _native void unk_0xF11F956F()l
extern _native const char* datafile_get_file_dict()l
extern _native bool unk_0x768CBB35(const char* filename)l
extern _native bool unk_0x0B4087F7(bool* p0)l
extern _native bool datafile_is_save_pending()l
extern _native32(0x9B29D99B) void _object_value_add_boolean(any* objectData, const char* key, bool value)l
extern _native32(0xEFCF554A) void _object_value_add_integer(any* objectData, const char* key, int value)l
extern _native32(0xE972CACF) void _object_value_add_float(any* objectData, const char* key, float value)l
extern _native32(0xD437615C) void _object_value_add_string(any* objectData, const char* key, const char* value)l
extern _native32(0x75FC6C3C) void _object_value_add_vector3(any* objectData, const char* key, vector3 value)l
extern _native32(0x96A8E05F) any* _object_value_add_object(any* objectData, const char* key)l
extern _native32(0x03939B8D) any* _object_value_add_array(any* objectData, const char* key)l
extern _native32(0x8876C872) bool _object_value_get_boolean(any* objectData, const char* key)l
extern _native32(0xA6C68693) int _object_value_get_integer(any* objectData, const char* key)l
extern _native32(0xA92C1AF4) float _object_value_get_float(any* objectData, const char* key)l
extern _native32(0x942160EC) const char* _object_value_get_string(any* objectData, const char* key)l
extern _native32(0xE84A127A) vector3 _object_value_get_vector3(any* objectData, const char* key)l
extern _native32(0xC9C13D8D) any* _object_value_get_object(any* objectData, const char* key)l
extern _native32(0x1F2F7D00) any* _object_value_get_array(any* objectData, const char* key)l
extern _native32(0x2678342A) int _object_value_get_type(any* objectData, const char* key)l
extern _native32(0x08174B90) void _array_value_add_boolean(any* arrayData, bool value)l
extern _native32(0xF29C0B36) void _array_value_add_integer(any* arrayData, int value)l
extern _native32(0xE4302123) void _array_value_add_float(any* arrayData, float value)l
extern _native32(0xF3C01350) void _array_value_add_string(any* arrayData, const char* value)l
extern _native32(0x16F464B6) void _array_value_add_vector3(any* arrayData, vector3 value)l
extern _native32(0xC174C71B) any* _array_value_add_object(any* arrayData)l
extern _native32(0xA2E5F921) bool _array_value_get_boolean(any* arrayData, int arrayIndex)l
extern _native32(0xBB120CFC) int _array_value_get_integer(any* arrayData, int arrayIndex)l
extern _native32(0x08AD2CC2) float _array_value_get_float(any* arrayData, int arrayIndex)l
extern _native32(0x93F985A6) const char* _array_value_get_string(any* arrayData, int arrayIndex)l
extern _native32(0x80E3DA55) vector3 _array_value_get_vector3(any* arrayData, int arrayIndex)l
extern _native32(0xECE81278) any* _array_value_get_object(any* arrayData, int arrayIndex)l
extern _native32(0xA8A21766) int _array_value_get_size(any* arrayData)l
extern _native32(0xFA2402C8) int _array_value_get_type(any* arrayData, int arrayIndex)l
#pragma endregion //}
#pragma region FIRE //{
extern _native int start_script_fire(vector3 vec, int maxChildren, bool isGasFire)l
extern _native void remove_script_fire(int fireHandle)l
extern _native any start_entity_fire(Entity entity)l
extern _native void stop_entity_fire(Entity entity)l
extern _native bool is_entity_on_fire(Entity entity)l
extern _native int get_number_of_fires_in_range(vector3 vec, float radius)l
extern _native void stop_fire_in_range(vector3 vec, float radius)l
extern _native bool get_closest_fire_pos(vector3* outPosition, vector3 vec)l
extern _native void add_owned_explosion(Ped ped, vector3 vec, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native void add_explosion_with_user_vfx(vector3 vec, int explosionType, Hash explosionFx, float damageScale, bool isAudible, bool isInvisible, float cameraShake)l
extern _native bool is_explosion_in_area(int explosionType, vector3 vec_1, vector3 vec_2)l
extern _native bool is_explosion_in_sphere(int explosionType, vector3 vec, float radius)l
extern _native bool is_explosion_in_angled_area(int explosionType, vector3 vec_1, vector3 vec_2, float angle)l
extern _native32(0xAEC0D176) Entity _get_ped_inside_explosion_area(int explosionType, vector3 vec_1, vector3 vec_2, float radius)l
#pragma endregion //}
#pragma region DECISIONEVENT //{
extern _native void set_decision_maker(Ped ped, Hash name)l
extern _native void clear_decision_maker_event_response(Hash name, int type)l
extern _native void block_decision_maker_event(Hash name, int type)l
extern _native void unblock_decision_maker_event(Hash name, int type)l
extern _native ScrHandle add_shocking_event_at_position(int type, vector3 vec, float duration)l
extern _native ScrHandle add_shocking_event_for_entity(int type, Entity entity, float duration)l
extern _native bool is_shocking_event_in_sphere(int type, vector3 vec, float radius)l
extern _native bool remove_shocking_event(ScrHandle event)l
extern _native void remove_all_shocking_events(bool p0)l
extern _native void remove_shocking_event_spawn_blocking_areas()l
extern _native void suppress_shocking_events_next_frame()l
extern _native void suppress_shocking_event_type_next_frame(int type)l
extern _native void suppress_agitation_events_next_frame()l
#pragma endregion //}
#pragma region ZONE //{
extern _native int get_zone_at_coords(vector3 vec)l
extern _native int get_zone_from_name_id(const char* zoneName)l
extern _native int get_zone_popschedule(int zoneId)l
extern _native const char* get_name_of_zone(vector3 vec)l
extern _native void set_zone_enabled(int zoneId, bool toggle)l
extern _native int get_zone_scumminess(int zoneId)l
extern _native void override_popschedule_vehicle_model(int scheduleId, Hash vehicleHash)l
extern _native void clear_popschedule_override_vehicle_model(int scheduleId)l
extern _native Hash get_hash_of_map_area_at_coords(vector3 vec)l
#pragma endregion //}
#pragma region ROPE //{
extern _native Object add_rope(vector3 vec, vector3 rot, float length, int ropeType, float maxLength, float minLength, float p10, bool p11, bool p12, bool rigid, float p14, bool breakWhenShot, any* unkPtr)l
extern _native void delete_rope(Object* rope)l
extern _native any delete_child_rope(Object rope)l
extern _native bool does_rope_exist(Object* rope)l
extern _native void rope_draw_shadow_enabled(Object* rope, bool toggle)l
extern _native any load_rope_data(Object rope, const char* rope_preset)l
extern _native void pin_rope_vertex(Object rope, int vertex, vector3 vec)l
extern _native any unpin_rope_vertex(Object rope, int vertex)l
extern _native int get_rope_vertex_count(Object rope)l
extern _native void attach_entities_to_rope(Object rope, Entity ent1, Entity ent2, vector3 ent1_, vector3 ent2_, float length, bool p10, bool p11, any* p12, any* p13)l
extern _native void attach_rope_to_entity(Object rope, Entity entity, vector3 vec, bool p5)l
extern _native void detach_rope_from_entity(Object rope, Entity entity)l
extern _native void rope_set_update_pinverts(Object rope)l
extern _native void unk_0x80DB77A7(any p0, any p1)l
extern _native void unk_0xC67D5CF6(any p0, bool p1)l
extern _native bool unk_0x7A18BB9C(any* p0)l
extern _native any get_rope_last_vertex_coord(Object rope)l
extern _native any get_rope_vertex_coord(Object rope, int vertex)l
extern _native void start_rope_winding(Object rope)l
extern _native void stop_rope_winding(Object rope)l
extern _native void start_rope_unwinding_front(Object rope)l
extern _native void stop_rope_unwinding_front(Object rope)l
extern _native void rope_convert_to_simple(Object rope)l
extern _native any rope_load_textures()l
extern _native bool rope_are_textures_loaded()l
extern _native any rope_unload_textures()l
extern _native void unk_0x106BA127(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8, any p9, any p10, any p11, any p12, any p13)l
extern _native void unk_0x7C6F7668(any p0, bool p1, bool p2)l
extern _native void unk_0x686672DD(any p0, any p1)l
extern _native32(0xFD309DC8) float _get_rope_length(Object rope)l
extern _native any rope_force_length(Object rope, float length)l
extern _native any rope_reset_length(Object rope, bool length)l
extern _native void apply_impulse_to_cloth(vector3 pos, vector3 vec, float impulse)l
extern _native void set_damping(Object rope, int vertex, float value)l
extern _native void activate_physics(Entity entity)l
extern _native void set_cgoffset(Object rope, vector3 vec)l
extern _native vector3 get_cgoffset(Object rope)l
extern _native void set_cg_at_boundcenter(Object rope)l
extern _native void break_entity_glass(any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, any p9, bool p10)l
extern _native any set_disable_breaking(Object rope, bool enabled)l
extern _native void set_disable_frag_damage(Object object, bool toggle)l
#pragma endregion //}
#pragma region WATER //{
extern _native bool get_water_height(vector3 vec, float* height)l
extern _native bool get_water_height_no_waves(vector3 vec, float* height)l
extern _native bool test_probe_against_water(vector3 vec_1, vector3 vec_2, vector3* result)l
extern _native bool test_probe_against_all_water(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native bool test_vertical_probe_against_all_water(vector3 vec, any p3, any* p4)l
extern _native void modify_water(vector2 vector, float radius, float height)l
#pragma endregion //}
#pragma region WORLDPROBE //{
extern _native int start_shape_test_los_probe(vector3 vec_1, vector3 vec_2, int flags, Entity entity, int p8)l
extern _native32(0x8251485D) int _start_shape_test_ray(vector3 vec_1, vector3 vec_2, int flags, Entity entity, int p8)l
extern _native int start_shape_test_bounding_box(Entity entity, int flags1, int flags2)l
extern _native int start_shape_test_box(vector3 vec, float x1, float y2, float z2, vector3 rot, any p9, any p10, any entity, any p12)l
extern _native int start_shape_test_bound(Entity entity, int flags1, int flags2)l
extern _native int start_shape_test_capsule(vector3 vec_1, vector3 vec_2, float radius, int flags, Entity entity, int p9)l
extern _native int unk_0x4559460A(vector3 vec_1, vector3 vec_2, float radius, int flags, Entity entity, any p9)l
extern _native int get_shape_test_result(int rayHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Entity* entityHit)l
extern _native32(0x4301E10C) int _get_shape_test_result_ex(int rayHandle, bool* hit, vector3* endCoords, vector3* surfaceNormal, Hash* materialHash, Entity* entityHit)l
extern _native void unk_0xEC2AAF06(Entity p0)l
#pragma endregion //}
#pragma region NETWORK //{
extern _native bool network_is_signed_in()l
extern _native bool network_is_signed_online()l
extern _native32(0x3FB40673) bool _network_are_ros_available()l
extern _native bool network_is_cloud_available()l
extern _native bool unk_0x66EC713F()l
extern _native any unk_0x358D1D77()l
extern _native bool network_is_host()l
extern _native bool network_have_online_privileges()l
extern _native bool unk_0x1F88819D(any p0)l
extern _native bool unk_0x2D817A5E(any p0, any p1)l
extern _native bool unk_0xBB54AA3D(any p0, any p1, bool p2)l
extern _native bool network_can_bail()l
extern _native void network_bail()l
extern _native void unk_0x96E28FE2()l
extern _native bool network_can_access_multiplayer(int* loadingState)l
extern _native bool network_is_multiplayer_disabled()l
extern _native bool network_can_enter_multiplayer()l
extern _native any network_session_enter(any p0, any p1, any p2, int maxPlayers, any p4, any p5)l
extern _native bool network_session_friend_matchmaking(int p0, int p1, int maxPlayers, bool p3)l
extern _native bool network_session_crew_matchmaking(int p0, int p1, int p2, int maxPlayers, bool p4)l
extern _native bool network_session_activity_quickmatch(any p0, any p1, any p2, any p3)l
extern _native bool network_session_host(int p0, int maxPlayers, bool p2)l
extern _native bool network_session_host_closed(int p0, int maxPlayers)l
extern _native bool network_session_host_friends_only(int p0, int maxPlayers)l
extern _native bool network_session_is_closed_friends()l
extern _native bool network_session_is_closed_crew()l
extern _native bool network_session_is_solo()l
extern _native bool network_session_is_private()l
extern _native bool network_session_end(bool p0, bool p1)l
extern _native void network_session_kick_player(Player player)l
extern _native32(0x8A559D26) bool _network_session_is_player_voted_to_kick(Player player)l
extern _native void unk_0x3C3E2AB6(int p0)l
extern _native32(0x5F29A7E0) void _network_session_set_max_players(int playerType, int playerCount)l
extern _native32(0x36EAD960) int _network_session_get_unk(int p0)l
extern _native void unk_0x5BE529F7(any p0)l
extern _native void unk_0x454C7B67(any p0)l
extern _native void unk_0xE5961511(any p0)l
extern _native void unk_0xAE396263(bool p0)l
extern _native void unk_0x913FD7D6(any p0)l
extern _native void unk_0xB3D9A67F(bool p0)l
extern _native void unk_0x6CC062FC(any p0)l
extern _native void unk_0x57F9BC83()l
extern _native32(0xF3768F90) void _network_session_hosted(bool p0)l
extern _native void network_add_followers(int* p0, int p1)l
extern _native void network_clear_followers()l
extern _native32(0x74E8C53E) void _network_get_server_time(int* hours, int* minutes, int* seconds)l
extern _native void unk_0x959E43A3(any p0)l
extern _native bool network_x_affects_gamers(any p0)l
extern _native bool network_find_matched_gamers(any p0, float p1, float p2, float p3)l
extern _native bool network_is_finding_gamers()l
extern _native any unk_0xBEDC4503()l
extern _native int network_get_num_found_gamers()l
extern _native bool network_get_found_gamer(any* p0, any p1)l
extern _native void network_clear_found_gamers()l
extern _native bool unk_0x42BD0780(any* p0)l
extern _native any unk_0xBEB98840()l
extern _native any unk_0x08029970()l
extern _native any unk_0xC871E745()l
extern _native bool unk_0xB5ABC4B4(any* p0, any p1)l
extern _native void unk_0x3F7EDBBD()l
extern _native void network_is_player_animation_drawing_synchronized()l
extern _native void network_session_cancel_invite()l
extern _native void network_session_force_cancel_invite()l
extern _native bool network_has_pending_invite()l
extern _native any unk_0xFBBAC350()l
extern _native any unk_0x0907A6BF()l
extern _native bool network_session_was_invited()l
extern _native void network_session_get_inviter(int* networkHandle)l
extern _native any unk_0x3EA9D44C()l
extern _native void network_suppress_invite(bool toggle)l
extern _native void network_block_invites(bool toggle)l
extern _native void unk_0x32B7A076()l
extern _native32(0x0FCE995D) void _network_block_kicked_players(bool p0)l
extern _native void unk_0xA639DCA2(bool p0)l
extern _native any unk_0x70ED476A()l
extern _native void unk_0x50507BED()l
extern _native void network_session_host_single_player(int p0)l
extern _native void network_session_leave_single_player()l
extern _native bool network_is_game_in_progress()l
extern _native bool network_is_session_active()l
extern _native bool network_is_in_session()l
extern _native bool network_is_session_started()l
extern _native bool network_is_session_busy()l
extern _native bool network_can_session_end()l
extern _native void network_session_mark_visible(bool p0)l
extern _native any network_session_is_visible()l
extern _native void network_session_block_join_requests(bool p0)l
extern _native void network_session_change_slots(int p0, bool p1)l
extern _native void network_session_voice_host()l
extern _native void network_session_voice_leave()l
extern _native void unk_0x9DFD89E6(any* globalPtr)l
extern _native void network_set_keep_focuspoint(bool p0, any p1)l
extern _native void unk_0x6EFC2FD0(any p0)l
extern _native bool unk_0x60AA4AA1()l
extern _native bool unk_0x132CA01E()l
extern _native void network_set_activity_spectator(bool toggle)l
extern _native any network_is_activity_spectator()l
extern _native void network_set_activity_spectator_max(int maxSpectators)l
extern _native int network_get_activity_player_num(bool p0)l
extern _native bool network_is_activity_spectator_from_handle(int* networkHandle)l
extern _native any network_host_transition(any p0, any p1, any p2, any p3, any p4, any p5)l
extern _native bool network_do_transition_quickmatch(any p0, any p1, any p2, any p3)l
extern _native bool network_do_transition_quickmatch_async(any p0, any p1, any p2, any p3)l
extern _native bool network_do_transition_quickmatch_with_group(any p0, any p1, any p2, any p3, any* p4, any p5)l
extern _native any network_join_group_activity()l
extern _native void unk_0x36A5F2DA()l
extern _native void unk_0x7EF353E1(bool p0)l
extern _native void unk_0xF60986FC(bool p0)l
extern _native void network_set_transition_creator_handle(any* p0)l
extern _native void network_clear_transition_creator_handle()l
extern _native bool network_invite_gamers_to_transition(any* p0, any p1)l
extern _native void network_set_gamer_invited_to_transition(int* networkHandle)l
extern _native any network_leave_transition()l
extern _native any network_launch_transition()l
extern _native void network_bail_transition()l
extern _native bool network_do_transition_to_game(bool p0, int maxPlayers)l
extern _native bool network_do_transition_to_new_game(bool p0, int maxPlayers, bool p2)l
extern _native bool network_do_transition_to_freemode(any* p0, any p1, bool p2, int players, bool p4)l
extern _native bool network_do_transition_to_new_freemode(any* p0, any* p1, int players, bool p3, bool p4, bool p5)l
extern _native any network_is_transition_to_game()l
extern _native any network_get_transition_members(any* p0, any p1)l
extern _native void network_apply_transition_parameter(any p0, any p1)l
extern _native void unk_0xE0C28DB5(any p0, const char* p1, bool p2)l
extern _native bool network_send_transition_gamer_instruction(int* networkHandle, const char* p1, int p2, int p3, bool p4)l
extern _native bool network_mark_transition_gamer_as_fully_joined(any* p0)l
extern _native any network_is_transition_host()l
extern _native bool network_is_transition_host_from_handle(int* networkHandle)l
extern _native bool network_get_transition_host(int* networkHandle)l
extern _native bool network_is_in_transition()l
extern _native bool network_is_transition_started()l
extern _native any network_is_transition_busy()l
extern _native any network_is_transition_matchmaking()l
extern _native void network_open_transition_matchmaking()l
extern _native void network_close_transition_matchmaking()l
extern _native any unk_0xC901AA9F()l
extern _native void network_set_transition_activity_id(any p0)l
extern _native void network_change_transition_slots(any p0, any p1)l
extern _native void unk_0x0532DDD2(bool p0)l
extern _native bool network_has_player_started_transition(Player player)l
extern _native bool network_are_transition_details_valid(any p0)l
extern _native bool network_join_transition(Player player)l
extern _native bool network_has_invited_gamer_to_transition(any* p0)l
extern _native bool network_is_activity_session()l
extern _native void unk_0x18F03AFD(any p0)l
extern _native32(0x8B99B72B) bool _network_send_presence_invite(int* networkHandle, any* p1, any p2, any p3)l
extern _native32(0x877C0E1C) bool _network_send_presence_transition_invite(any* p0, any* p1, any p2, any p3)l
extern _native any unk_0x5E832444(any p0)l
extern _native int network_get_num_presence_invites()l
extern _native bool network_accept_presence_invite(any p0)l
extern _native bool network_remove_presence_invite(any p0)l
extern _native any network_get_presence_invite_id(any p0)l
extern _native any network_get_presence_invite_inviter(any p0)l
extern _native bool network_get_presence_invite_handle(any p0, any* p1)l
extern _native any network_get_presence_invite_session_id(any p0)l
extern _native any unk_0xA4302183(any p0)l
extern _native any unk_0x51B2D848(any p0)l
extern _native any unk_0x4677C656(any p0)l
extern _native bool unk_0xF5E3401C(any p0)l
extern _native bool unk_0x7D593B4C(any p0)l
extern _native bool network_has_follow_invite()l
extern _native any network_action_follow_invite()l
extern _native any network_clear_follow_invite()l
extern _native void unk_0x9773F36A()l
extern _native void network_remove_transition_invite(any* p0)l
extern _native void network_remove_all_transition_invite()l
extern _native void unk_0xC47352E7()l
extern _native bool network_invite_gamers(any* p0, any p1, any* p2, any* p3)l
extern _native bool network_has_invited_gamer(any* p0)l
extern _native bool network_get_currently_selected_gamer_handle_from_invite_menu(any* p0)l
extern _native bool network_set_currently_selected_gamer_handle_from_invite_menu(any* p0)l
extern _native void unk_0x0808D4CC(any* p0, any* p1)l
extern _native bool fillout_pm_player_list(int* networkHandle, any p1, any p2)l
extern _native bool fillout_pm_player_list_with_names(any* p0, any* p1, any p2, any p3)l
extern _native bool using_network_weapontype(any p0)l
extern _native any unk_0xA812B6CB()l
extern _native any unk_0xF30E5814(any* p0, any p1)l
extern _native any unk_0xC6609191()l
extern _native bool network_is_chatting_in_platform_party(int* networkHandle)l
extern _native bool network_is_in_party()l
extern _native bool network_is_party_member(int* networkHandle)l
extern _native any unk_0x9156EFC0()l
extern _native any unk_0x8FA6EE0E()l
extern _native void unk_0x7F70C15A()l
extern _native void unk_0x8179C48A(any p0)l
extern _native void unk_0x41702C8A(any p0)l
extern _native int network_get_random_int()l
extern _native32(0xF9B6426D) int _network_get_random_int_in_range(int rangeStart, int rangeEnd)l
extern _native bool network_player_is_cheater()l
extern _native any unk_0x1720ABA6()l
extern _native bool network_player_is_badsport()l
extern _native bool unk_0xF9A51B92(any p0, any p1, any p2)l
extern _native bool bad_sport_player_left_detected(any* p0, any p1, any p2)l
extern _native void unk_0x4818ACD0(any p0, any p1)l
extern _native void network_set_this_script_is_network_script(int lobbySize, bool p1, int playerId)l
extern _native bool network_get_this_script_is_network_script()l
extern _native32(0xCCD8C02D) int _network_get_num_participants_host()l
extern _native int network_get_num_participants()l
extern _native int network_get_script_status()l
extern _native void network_register_host_broadcast_variables(int* vars, int numVars)l
extern _native void network_register_player_broadcast_variables(int* vars, int numVars)l
extern _native void unk_0xA71A1D2A()l
extern _native bool unk_0x0B739F53()l
extern _native int network_get_player_index(Player player)l
extern _native int network_get_participant_index(int index)l
extern _native Player network_get_player_index_from_ped(Ped ped)l
extern _native int network_get_num_connected_players()l
extern _native bool network_is_player_connected(Player player)l
extern _native int unk_0xF4F13B06()l
extern _native bool network_is_participant_active(any p0)l
extern _native bool network_is_player_active(Player player)l
extern _native bool network_is_player_a_participant(any p0)l
extern _native bool network_is_host_of_this_script()l
extern _native any network_get_host_of_this_script()l
extern _native int network_get_host_of_script(const char* scriptName, int p1, int p2)l
extern _native void network_set_mission_finished()l
extern _native bool network_is_script_active(const char* scriptName, any p1, bool p2, any p3)l
extern _native int network_get_num_script_participants(any* p0, any p1, any p2)l
extern _native any unk_0xDB8B5D71()l
extern _native bool unk_0xCEA55F4C(Player p0, any* p1, any p2)l
extern _native void unk_0x8DCFE77D()l
extern _native void unk_0x331D9A27()l
extern _native Player participant_id()l
extern _native int participant_id_to_int()l
extern _native int network_get_destroyer_of_network_id(int netId, Hash* weaponHash)l
extern _native32(0x28A45454) bool _network_get_desroyer_of_entity(any p0, any p1, Hash* p2)l
extern _native Entity network_get_entity_killer_of_player(Player player, Hash* weaponHash)l
extern _native void network_resurrect_local_player(vector3 vec, float heading, bool unk, bool changetime)l
extern _native void network_set_local_player_invincible_time(int time)l
extern _native bool network_is_local_player_invincible()l
extern _native void network_disable_invincible_flashing(int player, bool p1)l
extern _native void unk_0xB72F086D(any p0)l
extern _native bool unk_0xEDA68956(Entity p0)l
extern _native int network_get_network_id_from_entity(Entity entity)l
extern _native Entity network_get_entity_from_network_id(int netId)l
extern _native bool network_get_entity_is_networked(Entity entity)l
extern _native bool network_get_entity_is_local(Entity entity)l
extern _native void network_register_entity_as_networked(Entity entity)l
extern _native void network_unregister_networked_entity(Entity entity)l
extern _native bool network_does_network_id_exist(int netID)l
extern _native bool network_does_entity_exist_with_network_id(Entity entity)l
extern _native bool network_request_control_of_network_id(int netId)l
extern _native bool network_has_control_of_network_id(int netId)l
extern _native bool network_request_control_of_entity(Entity entity)l
extern _native bool network_request_control_of_door(int doorID)l
extern _native bool network_has_control_of_entity(Entity entity)l
extern _native bool network_has_control_of_pickup(Pickup pickup)l
extern _native bool network_has_control_of_door(int doorID)l
extern _native int veh_to_net(Vehicle vehicle)l
extern _native int ped_to_net(Ped ped)l
extern _native int obj_to_net(Object object)l
extern _native Vehicle net_to_veh(int netHandle)l
extern _native Ped net_to_ped(int netHandle)l
extern _native Object net_to_obj(int netHandle)l
extern _native Entity net_to_ent(int netHandle)l
extern _native bool network_gamertag_from_handle_pending()l
extern _native bool network_gamertag_from_handle_succeeded()l
extern _native void network_show_profile_ui(int* networkHandle)l
extern _native const char* network_player_get_name(Player player)l
extern _native const char* network_player_get_userid(Player player, int* userID)l
extern _native bool network_player_is_rockstar_dev(Player player)l
extern _native bool unk_0xD265B049(any p0)l
extern _native bool network_is_inactive_profile(any* p0)l
extern _native int network_get_max_friends()l
extern _native int network_get_friend_count()l
extern _native const char* network_get_friend_name(Player player)l
extern _native bool network_is_friend_online(const char* name)l
extern _native any network_is_pending_friend(any p0)l
extern _native any network_is_adding_friend()l
extern _native bool network_add_friend(any* p0, const char* p1)l
extern _native bool network_is_friend_index_online(int friendIndex)l
extern _native bool unk_0xB802B671(any p0)l
extern _native bool network_can_set_waypoint()l
extern _native any unk_0x5C0AB2A9(any p0)l
extern _native any unk_0x9A176B6E()l
extern _native bool network_has_headset()l
extern _native void unk_0x5C05B7E1(bool p0)l
extern _native bool network_gamer_has_headset(any* p0)l
extern _native bool network_is_gamer_talking(int* p0)l
extern _native bool network_can_communicate_with_gamer(int* player)l
extern _native bool network_is_gamer_muted_by_me(int* p0)l
extern _native bool network_am_i_muted_by_gamer(any* p0)l
extern _native bool network_is_gamer_blocked_by_me(any* p0)l
extern _native bool network_am_i_blocked_by_gamer(any* p0)l
extern _native bool network_is_player_talking(Player player)l
extern _native bool network_player_has_headset(Player player)l
extern _native bool network_is_player_muted_by_me(Player player)l
extern _native bool network_am_i_muted_by_player(Player player)l
extern _native bool network_is_player_blocked_by_me(Player player)l
extern _native bool network_am_i_blocked_by_player(Player player)l
extern _native float network_get_player_loudness(any p0)l
extern _native void network_set_talker_proximity(float p0)l
extern _native any network_get_talker_proximity()l
extern _native void network_set_voice_active(bool toggle)l
extern _native void unk_0x1A3EA6CD(bool p0)l
extern _native void network_override_transition_chat(bool p0)l
extern _native void network_set_team_only_chat(bool toggle)l
extern _native void unk_0xC8CC9E75(int team, bool toggle)l
extern _native void network_set_override_spectator_mode(bool toggle)l
extern _native void unk_0xC9DDA85B(bool p0)l
extern _native void unk_0xD33AFF79(bool p0)l
extern _native void unk_0x4FFEFE43(bool p0)l
extern _native void network_override_chat_restrictions(Player player, bool toggle)l
extern _native void unk_0x2F98B405(bool p0)l
extern _native void network_override_receive_restrictions(Player player, bool toggle)l
extern _native void unk_0x1BCD3DDF(bool p0)l
extern _native void network_set_voice_channel(any p0)l
extern _native void network_clear_voice_channel()l
extern _native bool is_network_vehicle_been_damaged_by_any_object(vector3 vec)l
extern _native void unk_0x7F9B9052()l
extern _native void unk_0x7BBEA8CF(any p0)l
extern _native void unk_0xE797A4B6(any p0)l
extern _native void unk_0x92268BB5(Player p0, float* p1, float* p2)l
extern _native void shutdown_and_launch_single_player_game()l
extern _native void network_set_friendly_fire_option(bool toggle)l
extern _native void network_set_rich_presence(any p0, any p1, any p2, any p3)l
extern _native void unk_0x017E6777(any p0, any p1)l
extern _native int network_get_timeout_time()l
extern _native void unk_0xBE6A30C3(Player player, vector3 vec, bool p4, bool p5)l
extern _native void unk_0x22E03AD0(Player player, bool p1)l
extern _native void unk_0xCEAE5AFC(Entity entity)l
extern _native32(0xF5F4BD95) bool _network_player_is_in_clan()l
extern _native bool unk_0x54E79E9C(int* clanDesc, int bufferSize)l
extern _native32(0x807B3450) int _get_num_membership_desc()l
extern _native bool network_clan_get_membership_desc(int* memberDesc, int p1)l
extern _native bool network_clan_download_membership_pending(any* p0)l
extern _native32(0x83ED8E08) bool _network_is_clan_membership_finished_downloading()l
extern _native bool network_clan_remote_memberships_are_in_cache(int* p0)l
extern _native int network_clan_get_membership_count(int* p0)l
extern _native bool network_clan_get_membership_valid(int* p0, any p1)l
extern _native bool network_clan_get_membership(int* p0, int* clanMembership, int p2)l
extern _native bool network_clan_join(int clanDesc)l
extern _native32(0xBDA90BAC) bool _network_clan_animation(const char* animDict, const char* animName)l
extern _native bool unk_0x8E952B12(int p0, const char* p1)l
extern _native any unk_0x966C90FD()l
extern _native bool unk_0xBA672146(any* p0, any* p1)l
extern _native bool unk_0x7963FA4D(any p0)l
extern _native bool unk_0x88B13CDC(any p0, any* p1)l
extern _native void unk_0xD6E3D5EA(any p0)l
extern _native any network_get_primary_clan_data_clear()l
extern _native void network_get_primary_clan_data_cancel()l
extern _native bool network_get_primary_clan_data_start(any* p0, any p1)l
extern _native any network_get_primary_clan_data_pending()l
extern _native any network_get_primary_clan_data_success()l
extern _native bool network_get_primary_clan_data_new(any* p0, any* p1)l
extern _native void set_network_id_can_migrate(int netId, bool toggle)l
extern _native void set_network_id_exists_on_all_machines(int netId, bool toggle)l
extern _native32(0x4D15FDB1) void _set_network_id_sync_to_player(int netId, Player player, bool toggle)l
extern _native void network_set_entity_can_blend(Entity entity, bool toggle)l
extern _native32(0x09CBC4B0) void _network_set_entity_visible_to_network(Entity entity, bool toggle)l
extern _native void set_network_id_visible_in_cutscene(int netId, bool p1, bool p2)l
extern _native void unk_0x00AE4E17(int netId, bool state)l
extern _native bool unk_0xEA5176C0(int netId)l
extern _native void set_local_player_visible_in_cutscene(bool p0, bool p1)l
extern _native void set_local_player_invisible_locally(bool p0)l
extern _native void set_local_player_visible_locally(bool p0)l
extern _native void set_player_invisible_locally(Player player, bool toggle)l
extern _native void set_player_visible_locally(Player player, bool toggle)l
extern _native void fade_out_local_player(bool p0)l
extern _native void network_fade_out_entity(Entity entity, bool normal, bool slow)l
extern _native bool is_player_in_cutscene(Player player)l
extern _native void set_entity_visible_in_cutscene(any p0, bool p1, bool p2)l
extern _native void set_entity_locally_invisible(Entity entity)l
extern _native void set_entity_locally_visible(Entity entity)l
extern _native bool is_damage_tracker_active_on_network_id(int netID)l
extern _native void activate_damage_tracker_on_network_id(int netID, bool p1)l
extern _native bool is_sphere_visible_to_another_machine(float p0, float p1, float p2, float p3)l
extern _native bool is_sphere_visible_to_player(any p0, float p1, float p2, float p3, float p4)l
extern _native void reserve_network_mission_objects(int p0)l
extern _native void reserve_network_mission_peds(int p0)l
extern _native void reserve_network_mission_vehicles(int p0)l
extern _native bool can_register_mission_objects(int p0)l
extern _native bool can_register_mission_peds(int p0)l
extern _native bool can_register_mission_vehicles(int p0)l
extern _native bool can_register_mission_entities(int p0, any p1, any p2, any p3)l
extern _native int get_num_reserved_mission_objects(bool p0)l
extern _native int get_num_reserved_mission_peds(bool p0)l
extern _native int get_num_reserved_mission_vehicles(bool p0)l
extern _native int unk_0x603FA104(bool p0)l
extern _native int unk_0xD8FEC4F8(bool p0)l
extern _native int unk_0x20527695(bool p0)l
extern _native any unk_0x8687E285()l
extern _native any unk_0x744AC008()l
extern _native any unk_0xC3A12135()l
extern _native any unk_0x6A036061()l
extern _native int get_network_time()l
extern _native int unk_0x98AA48E5()l
extern _native bool has_network_time_started()l
extern _native int get_time_offset(int timeA, int timeB)l
extern _native bool is_time_less_than(int timeA, int timeB)l
extern _native bool is_time_more_than(int timeA, int timeB)l
extern _native bool is_time_equal_to(int timeA, int timeB)l
extern _native int get_time_difference(int timeA, int timeB)l
extern _native const char* get_time_as_string(int time)l
extern _native32(0xF2FDF2E0) int _get_posix_time()l
extern _native32(0xBB7CCE49) void _get_date_and_time_from_unix_epoch(int unixEpoch, any* timeStructure)l
extern _native void network_set_in_spectator_mode(bool toggle, Ped playerPed)l
extern _native void unk_0x54058F5F(bool p0, any p1, bool p2)l
extern _native void unk_0xA7E36020(bool p0)l
extern _native void unk_0x64235620(bool p0, any p1)l
extern _native bool network_is_in_spectator_mode()l
extern _native void network_set_in_mp_cutscene(bool p0, bool p1)l
extern _native bool network_is_in_mp_cutscene()l
extern _native bool network_is_player_in_mp_cutscene(Player player)l
extern _native void set_network_vehicle_respot_timer(int netId, any p1)l
extern _native void unk_0xEA235081(Entity entity, bool p1)l
extern _native void use_player_colour_instead_of_team_colour(bool toggle)l
extern _native void network_add_entity_to_synchronised_scene(Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag)l
extern _native32(0xBFFE8B5C) void _network_force_local_use_of_synced_scene_camera(int netScene, const char* animDict, const char* animName)l
extern _native void network_attach_synchronised_scene_to_entity(int netScene, Entity entity, int bone)l
extern _native void network_start_synchronised_scene(int netScene)l
extern _native void network_stop_synchronised_scene(int netScene)l
extern _native32(0x16AED87B) int _network_unlink_networked_synchronised_scene(int netScene)l
extern _native any unk_0x0679CE71(int p0, any p1)l
extern _native bool unk_0xC62E77B3(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, int flags)l
extern _native bool unk_0x74D6B13C(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, int flags)l
extern _native any unk_0x90700C7D(any* p0)l
extern _native void unk_0x44BFB619()l
extern _native void network_get_respawn_result(int randomInt, vector3* coordinates, float* heading)l
extern _native any unk_0x03287FD2(any p0)l
extern _native void unk_0x408A9436()l
extern _native void unk_0xFFB2ADA1(any p0, any p1)l
extern _native void network_end_tutorial_session()l
extern _native any network_is_in_tutorial_session()l
extern _native any unk_0x755A2B3E()l
extern _native any unk_0xA003C40B()l
extern _native any unk_0x5E1020CC(any p0)l
extern _native32(0xE66A0B40) bool _network_is_player_equal_to_index(Player player, int index)l
extern _native void unk_0x72052DB3(any p0, bool p1)l
extern _native bool unk_0xB0313590(any p0)l
extern _native void network_override_clock_time(int Hours, int Minutes, int Seconds)l
extern _native void unk_0xC4AEAF49()l
extern _native any unk_0x2465296D()l
extern _native any network_add_entity_area(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native any unk_0x4C2C2B12(float p0, float p1, float p2, float p3, float p4, float p5)l
extern _native bool network_remove_entity_area(any p0)l
extern _native bool unk_0x69956127(any p0)l
extern _native bool unk_0xCB1CD6D3(any p0)l
extern _native bool unk_0xC6D53AA0(any p0)l
extern _native32(0x155465EE) void _network_set_network_id_dynamic(int netID, bool toggle)l
extern _native32(0x29532731) bool _network_request_cloud_background_scripts()l
extern _native void network_request_cloud_tunables()l
extern _native any unk_0x231CFD12()l
extern _native bool network_does_tunable_exist(const char* tunableContext, const char* tunableName)l
extern _native bool network_access_tunable_int(const char* tunableContext, const char* tunableName, int* value)l
extern _native bool network_access_tunable_float(const char* tunableContext, const char* tunableName, float* value)l
extern _native bool network_access_tunable_bool(const char* tunableContext, const char* tunableName)l
extern _native32(0xA78571CA) int _get_tunables_content_modifier_id(Hash contentHash)l
extern _native any unk_0x053BB329()l
extern _native void network_reset_body_tracker()l
extern _native any unk_0x17CBC608()l
extern _native bool unk_0xBFAA349B(any p0)l
extern _native bool unk_0xBEB7281A(Ped ped, Player player)l
extern _native any network_explode_vehicle(Vehicle vehicle, bool isAudible, bool isInvisible, bool p3)l
extern _native void unk_0xBC54371B(Entity entity)l
extern _native void unk_0x644141C5(Ped ped, vector3 vec, float p4)l
extern _native void network_set_property_id(any p0)l
extern _native void network_clear_property_id()l
extern _native void unk_0x53C9563C(int p0)l
extern _native void unk_0x6B97075B(bool p0)l
extern _native any unk_0x965EA007()l
extern _native any unk_0xEEFC8A55()l
extern _native void unk_0x866D1B67(any p0)l
extern _native any unk_0xED4A272F()l
extern _native any unk_0x4ACF110C(any p0)l
extern _native any unk_0x1AA3A0D5(any p0)l
extern _native any unk_0x37877757(any p0)l
extern _native any unk_0x1CF89DA5(any p0)l
extern _native any unk_0x16E53875(any p0, any p1)l
extern _native void unk_0x365C50EE(any p0, any p1)l
extern _native any unk_0x25E2DBA9()l
extern _native void set_store_enabled(bool toggle)l
extern _native bool unk_0x1FDC75DC(any p0)l
extern _native void unk_0xCA7A0A49()l
extern _native any unk_0x44A58B0A(any p0)l
extern _native any unk_0xD32FA11F()l
extern _native void unk_0xA7FA70AE()l
extern _native void unk_0xCC7DCE24()l
extern _native any unk_0x70F6D3AD()l
extern _native any unk_0x2B7B57B3(any* p0)l
extern _native bool unk_0xBAF52DD8(any p0)l
extern _native bool unk_0x9B9AFFF1(any p0)l
extern _native32(0xC38E9DB0) void _download_check()l
extern _native any unk_0x32A4EB22()l
extern _native any network_enable_motion_drugged()l
extern _native bool unk_0x08243B79(any* p0, any* p1)l
extern _native any unk_0x798D6C27()l
extern _native any unk_0xE69E8D0D()l
extern _native any unk_0x742075FE()l
extern _native any unk_0xCE569932()l
extern _native any unk_0x82146BE9()l
extern _native void unk_0x133FF2D5()l
extern _native bool unk_0xCBA7242F(any p0, any p1, any* p2, any p3, any p4, any p5)l
extern _native bool unk_0xDED82A6E(any* p0, bool p1, any* p2)l
extern _native bool unk_0x40CF0783(any p0, any p1, any* p2, any p3)l
extern _native bool unk_0x4609D596(any p0, any p1, any* p2, any* p3)l
extern _native bool unk_0x4C2C0D1F(any p0, any p1, any* p2, any* p3)l
extern _native bool unk_0x9EFBD5D1(any p0, any p1, any* p2, any* p3)l
extern _native bool unk_0xA6D8B798(any p0, any p1, any p2, any* p3, any* p4)l
extern _native bool unk_0x67E74842(any p0, any p1, any p2, any* p3, any* p4)l
extern _native bool set_balance_add_machine(any* p0, any* p1)l
extern _native bool set_balance_add_machines(any* p0, any p1, any* p2)l
extern _native bool unk_0x37F5BD93(any p0, any p1, any* p2, any* p3)l
extern _native bool network_get_background_loading_recipients(any p0, any p1, any* p2, any* p3)l
extern _native bool unk_0x87D1E6BD(any p0, any p1, any* p2, any* p3)l
extern _native void unk_0x021D5A94()l
extern _native any unk_0x4908A514()l
extern _native any unk_0x50296140()l
extern _native any unk_0x3970B0DA()l
extern _native any unk_0xC1487110()l
extern _native any unk_0xCC2356E3()l
extern _native any unk_0x2DE69817()l
extern _native any unk_0x81BD8D3B()l
extern _native any unk_0x8E1D8F78()l
extern _native void unk_0x0D35DD93()l
extern _native32(0x8F3137E6) const char* _get_content_user_id(int p0)l
extern _native any unk_0xB9137BA7(any p0)l
extern _native bool unk_0x9FEEAA9C(any p0)l
extern _native32(0x5E8A7559) int _get_content_category(int p0)l
extern _native32(0x331AEABF) const char* _get_content_id(any p0)l
extern _native32(0x0E5E8E5C) const char* _get_root_content_id(any p0)l
extern _native any unk_0xA5A0C695(any p0)l
extern _native32(0x91534C6E) int _get_content_description_hash(any p0)l
extern _native any unk_0x744A9EA5(any p0, any p1)l
extern _native void unk_0xA19A238D(any p0, any* p1)l
extern _native32(0xFF7D44E6) any _get_content_file_version(any p0, any p1)l
extern _native any unk_0xA2C5BD9D(any p0)l
extern _native bool unk_0xA850DDE1(any p0)l
extern _native bool unk_0x8F6754AE(any p0)l
extern _native any unk_0x1E34953F(any p0, any p1)l
extern _native any unk_0x771FE190(any p0, any p1)l
extern _native any unk_0x3276D9D3(any p0, any p1)l
extern _native any unk_0x41A0FB02(any p0, any p1)l
extern _native bool unk_0x11DC0F27(any p0)l
extern _native bool unk_0x0DEB3F5A(any p0)l
extern _native any unk_0x84315226(any p0, any p1)l
extern _native any unk_0x38FC2EEB(any* p0, any* p1, any p2, any p3, any p4)l
extern _native any unk_0x1C4F9FDB(any p0)l
extern _native bool unk_0xA69AE16C(any p0)l
extern _native bool unk_0xF50BC67A(any p0)l
extern _native bool unk_0xB3BBD241(any p0)l
extern _native any unk_0x70A2845C(any p0, any p1)l
extern _native bool unk_0x346B506C(any p0)l
extern _native void unk_0x0095DB71()l
extern _native bool unk_0xAD334B40(any* p0, any* p1, any* p2)l
extern _native bool unk_0x980D45D7(any* p0, bool p1, any* p2)l
extern _native bool unk_0x48CCC328(any* p0, bool p1, any* p2)l
extern _native any unk_0x8E664EFD()l
extern _native any unk_0x611E0BE2()l
extern _native any unk_0xF0211AC1()l
extern _native any unk_0x1F0DD8AF()l
extern _native void unk_0x405ECA16()l
extern _native bool unk_0x9567392B(any* p0, any* p1)l
extern _native any unk_0xF79FFF3C()l
extern _native any unk_0xA7F3F82B()l
extern _native any unk_0x410C61D1()l
extern _native bool unk_0x0D4F845D(any p0)l
extern _native void unk_0xE13C1F7F()l
extern _native void unk_0x213C6D36(bool p0)l
extern _native void unk_0x511E6F50(bool p0)l
extern _native bool unk_0xB4668B23(any p0)l
extern _native bool unk_0x30B51753(any* p0, any p1, any p2)l
extern _native any unk_0x02DAD93F()l
extern _native bool unk_0x2D947814(any p0)l
extern _native any unk_0x37A28C26()l
extern _native any unk_0x11E8B5CD()l
extern _native any unk_0x429AEAB3()l
extern _native int texture_download_request(int* PlayerHandle, const char* FilePath, const char* Name, bool p3)l
extern _native any unk_0x1856D008(any* p0, any* p1, bool p2)l
extern _native any unk_0x68C9AF69(any* p0, any p1, any p2, any p3, any* p4, bool p5)l
extern _native void texture_download_release(int p0)l
extern _native bool texture_download_has_failed(int p0)l
extern _native const char* texture_download_get_name(int p0)l
extern _native any unk_0x03225BA3(any p0)l
extern _native any unk_0x4DEBC227()l
extern _native bool network_is_cable_connected()l
extern _native any unk_0x0CA1167F()l
extern _native any unk_0x424C6E27()l
extern _native32(0xD3BBE42F) bool _is_rockstar_banned()l
extern _native32(0xBDBB5948) bool _is_socialclub_banned()l
extern _native32(0x97287D68) bool _can_play_online()l
extern _native any unk_0xC6EA802E()l
extern _native bool unk_0xFD261E30(any p0)l
extern _native bool unk_0x8570DD34(any p0, any* p1, any* p2)l
extern _native void unk_0x273C6180()l
extern _native void unk_0x371BBA08()l
extern _native void unk_0xA100CC97(bool p0)l
extern _native void unk_0xBB2D33D3(any p0, bool p1)l
#pragma endregion //}
#pragma region NETWORKCASH //{
extern _native void network_initialize_cash(int p0, int p1)l
extern _native void network_delete_character(int characterIndex, bool p1, bool p2)l
extern _native void network_clear_character_wallet(any p0)l
extern _native void network_give_player_jobshare_cash(int amount, int* networkHandle)l
extern _native void network_receive_player_jobshare_cash(int value, int* networkHandle)l
extern _native any unk_0xA27B9FE8()l
extern _native void network_refund_cash(int index, const char* context, const char* reason, bool unk)l
extern _native bool network_money_can_bet(any p0, bool p1, bool p2)l
extern _native bool network_can_bet(any p0)l
extern _native any network_earn_from_pickup(int amount)l
extern _native32(0x33C20BC4) void _network_earn_from_gang_pickup(int amount)l
extern _native32(0x30B3EC0A) void _network_earn_from_armour_truck(int amount)l
extern _native void network_earn_from_crate_drop(int amount)l
extern _native void network_earn_from_betting(int amount, const char* p1)l
extern _native void network_earn_from_job(int amount, const char* p1)l
extern _native void network_earn_from_mission_h(int amount, const char* heistHash)l
extern _native void network_earn_from_challenge_win(any p0, any* p1, bool p2)l
extern _native void network_earn_from_bounty(int amount, int* networkHandle, any* p2, any p3)l
extern _native void network_earn_from_import_export(any p0, any p1)l
extern _native void network_earn_from_holdups(int amount)l
extern _native void network_earn_from_property(int amount, Hash propertyName)l
extern _native void network_earn_from_ai_target_kill(any p0, any p1)l
extern _native void network_earn_from_not_badsport(int amount)l
extern _native void network_earn_from_rockstar(int amount)l
extern _native void network_earn_from_vehicle(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7)l
extern _native void network_earn_from_personal_vehicle(any p0, any p1, any p2, any p3, any p4, any p5, any p6, any p7, any p8)l
extern _native bool network_can_spend_money(any p0, bool p1, bool p2, bool p3, any p4)l
extern _native void network_buy_item(Ped player, Hash item, any p2, any p3, bool p4, const char* item_name, any p6, any p7, any p8, bool p9)l
extern _native void network_spent_taxi(int amount, bool p1, bool p2)l
extern _native void network_pay_employee_wage(any p0, bool p1, bool p2)l
extern _native void network_pay_utility_bill(any p0, bool p1, bool p2)l
extern _native void network_pay_match_entry_fee(int value, int* p1, bool p2, bool p3)l
extern _native void network_spent_betting(any p0, any p1, any* p2, bool p3, bool p4)l
extern _native void network_spent_in_stripclub(any p0, bool p1, any p2, bool p3)l
extern _native void network_buy_healthcare(int cost, bool p1, bool p2)l
extern _native void network_buy_airstrike(int cost, bool p1, bool p2)l
extern _native void network_buy_heli_strike(int cost, bool p1, bool p2)l
extern _native void network_spent_ammo_drop(any p0, bool p1, bool p2)l
extern _native void network_buy_bounty(int amount, Player victim, bool p2, bool p3)l
extern _native void network_buy_property(float propertyCost, Hash propertyName, bool p2, bool p3)l
extern _native void network_spent_heli_pickup(any p0, bool p1, bool p2)l
extern _native void network_spent_boat_pickup(any p0, bool p1, bool p2)l
extern _native void network_spent_bull_shark(any p0, bool p1, bool p2)l
extern _native void network_spent_cash_drop(any p0, bool p1, bool p2)l
extern _native void network_spent_hire_mugger(any p0, bool p1, bool p2)l
extern _native void network_spent_robbed_by_mugger(int amount, bool p1, bool p2)l
extern _native void network_spent_hire_mercenary(any p0, bool p1, bool p2)l
extern _native void network_spent_buy_wantedlevel(any p0, any* p1, bool p2, bool p3)l
extern _native void network_spent_buy_offtheradar(any p0, bool p1, bool p2)l
extern _native void network_spent_buy_reveal_players(any p0, bool p1, bool p2)l
extern _native void network_spent_carwash(any p0, any p1, any p2, bool p3, bool p4)l
extern _native void network_spent_cinema(any p0, any p1, bool p2, bool p3)l
extern _native void network_spent_telescope(any p0, bool p1, bool p2)l
extern _native void network_spent_holdups(any p0, bool p1, bool p2)l
extern _native void network_spent_buy_passive_mode(any p0, bool p1, bool p2)l
extern _native void network_spent_prostitutes(any p0, bool p1, bool p2)l
extern _native void network_spent_arrest_bail(any p0, bool p1, bool p2)l
extern _native void network_spent_pay_vehicle_insurance_premium(int amount, Hash vehicleModel, int* networkHandle, bool notBankrupt, bool hasTheMoney)l
extern _native void network_spent_call_player(any p0, any* p1, bool p2, bool p3)l
extern _native void network_spent_bounty(any p0, bool p1, bool p2)l
extern _native void network_spent_from_rockstar(int bank, bool p1, bool p2)l
extern _native const char* process_cash_gift(int* p0, int* p1, const char* p2)l
extern _native void network_spent_player_healthcare(any p0, any p1, bool p2, bool p3)l
extern _native void network_spent_no_cops(any p0, bool p1, bool p2)l
extern _native void network_spent_request_job(any p0, bool p1, bool p2)l
extern _native void network_buy_fairground_ride(int amountSpent, any p1, bool p2, bool p3)l
extern _native int network_get_vc_bank_balance()l
extern _native int network_get_vc_wallet_balance(int character)l
extern _native int network_get_vc_balance()l
extern _native bool network_can_receive_player_cash(any p0, any p1, any p2, any p3)l
extern _native any unk_0x8B755993(any p0)l
extern _native bool unk_0x8F266745(any p0)l
extern _native any unk_0x531E4892(any p0)l
extern _native any unk_0xB96C7ABE(any p0)l
#pragma endregion //}
#pragma region DLC1 //{
extern _native32(0x71D0CF3E) int _get_num_decorations(int character)l
extern _native bool unk_0x2E9D628C(int p0, int p1, int* outComponent)l
extern _native void init_shop_ped_component(int* outComponent)l
extern _native void init_shop_ped_prop(int* outProp)l
extern _native int unk_0xC937FF3D(int p0, int p1, int p2, int p3)l
extern _native32(0x594E862C) int _get_num_props_from_outfit(int character, int p1, int p2, bool p3, int p4, int componentId)l
extern _native void get_shop_ped_query_component(int componentId, int* outComponent)l
extern _native void get_shop_ped_component(Hash p0, any* p1)l
extern _native void get_shop_ped_query_prop(any p0, any* p1)l
extern _native Hash get_hash_name_for_component(Entity entity, int componentId, int drawableVariant, int textureVariant)l
extern _native Hash get_hash_name_for_prop(Entity entity, int componentId, int propIndex, int propTextureIndex)l
extern _native int unk_0x159751B4(Hash componentHash)l
extern _native void get_variant_component(Hash componentHash, int componentId, any* p2, any* p3, any* p4)l
extern _native32(0xCE70F183) int _get_num_forced_components(Hash componentHash)l
extern _native void get_forced_component(Hash componentHash, int componentId, any* p2, any* p3, any* p4)l
extern _native bool unk_0x8E2C7FD5(Hash componentHash, Hash drawableSlotHash, bool p2)l
extern _native int unk_0x1ECD23E7(int character, bool p1)l
extern _native void get_shop_ped_query_outfit(any p0, any* outfit)l
extern _native void get_shop_ped_outfit(any p0, any* p1)l
extern _native any get_shop_ped_outfit_locate(any p0)l
extern _native bool unk_0x6641A864(any p0, any p1, any* p2)l
extern _native32(0x818534AC) bool _get_prop_from_outfit(any outfit, int slot, any* item)l
extern _native int get_num_dlc_vehicles()l
extern _native Hash get_dlc_vehicle_model(int dlcVehicleIndex)l
extern _native bool get_dlc_vehicle_data(int dlcVehicleIndex, int* outData)l
extern _native int get_dlc_vehicle_flags(int dlcVehicleIndex)l
extern _native int get_num_dlc_weapons()l
extern _native bool get_dlc_weapon_data(int dlcWeaponIndex, int* outData)l
extern _native int get_num_dlc_weapon_components(int dlcWeaponIndex)l
extern _native bool get_dlc_weapon_component_data(int dlcWeaponIndex, int dlcWeapCompIndex, int* ComponentDataPtr)l
extern _native32(0x06396058) bool _is_dlc_data_empty(int dlcData)l
extern _native bool is_dlc_vehicle_mod(int modData)l
extern _native int unk_0x59352658(int modData)l
#pragma endregion //}
#pragma region DLC2 //{
extern _native bool is_dlc_present(Hash dlcHash)l
extern _native bool unk_0x881B1FDB()l
extern _native any unk_0xC2169164()l
extern _native any unk_0xF79A97F5()l
extern _native any unk_0xF69B729C()l
extern _native bool get_is_loading_screen_active()l
extern _native32(0x6087C10C) bool _nullify(any* variable, any unused)l
#pragma endregion //}
#pragma region SYSTEM //{
extern _native void wait(int ms)l
extern _native int start_new_script(const char* scriptName, int stackSize)l
extern _native int start_new_script_with_args(const char* scriptName, any* args, int argCount, int stackSize)l
extern _native int start_new_script_with_name_hash(Hash scriptHash, int stackSize)l
extern _native int start_new_script_with_name_hash_and_args(Hash scriptHash, any* args, int argCount, int stackSize)l
extern _native int timera()l
extern _native int timerb()l
extern _native void settimera(int value)l
extern _native void settimerb(int value)l
extern _native float timestep()l
extern _native float sin(float value)l
extern _native float cos(float value)l
extern _native float sqrt(float value)l
extern _native float pow(float base, float exponent)l
extern _native float vmag(vector3 vec)l
extern _native float vmag2(vector3 vec)l
extern _native float vdist(vector3 vec_1, vector3 vec_2)l
extern _native float vdist2(vector3 vec_1, vector3 vec_2)l
extern _native int shift_left(int value, int bitShift)l
extern _native int shift_right(int value, int bitShift)l
extern _native int floor(float value)l
extern _native int ceil(float value)l
extern _native int round(float value)l
extern _native float to_float(int value)l
#pragma endregion //}
#pragma region DECORATOR //{
extern _native bool decor_set_time(Entity entity, const char* propertyName, int value)l
extern _native bool decor_set_bool(Entity entity, const char* propertyName, bool value)l
extern _native bool decor_set_float(Entity entity, const char* propertyName, float value)l
extern _native bool decor_set_int(Entity entity, const char* propertyName, int value)l
extern _native bool decor_get_bool(Entity entity, const char* propertyName)l
extern _native float decor_get_float(Entity entity, const char* propertyName)l
extern _native int decor_get_int(Entity entity, const char* propertyName)l
extern _native bool decor_exist_on(Entity entity, const char* propertyName)l
extern _native bool decor_remove(Entity entity, const char* propertyName)l
extern _native void decor_register(const char* propertyName, int type)l
extern _native bool decor_is_registered_as_type(const char* propertyName, int type)l
extern _native void decor_register_lock()l
#pragma endregion //}
#pragma region SOCIALCLUB //{
extern _native32(0x6BE5DF29) int _get_total_sc_inbox_ids()l
extern _native32(0x5ECF955D) Hash _sc_inbox_message_init(int p0)l
extern _native32(0xD1ED1D48) bool _is_sc_inbox_valid(int p0)l
extern _native32(0x19EE0CCB) bool _sc_inbox_message_pop(int p0)l
extern _native bool sc_inbox_message_get_data_int(int p0, const char* context, int* out)l
extern _native bool sc_inbox_message_get_data_string(int p0, const char* context, const char* out)l
extern _native32(0xEBE420A4) bool _sc_inbox_message_push(int p0)l
extern _native32(0x2C959AF9) const char* _sc_inbox_message_get_string(int p0)l
extern _native void unk_0x0B9A3512(int* p0)l
extern _native void unk_0x75324674(const char* p0)l
extern _native bool sc_inbox_message_get_ugcdata(any p0, any* p1)l
extern _native bool unk_0x628F489B(const char* p0)l
extern _native bool unk_0xAB3346B5(any p0, int* p1)l
extern _native void sc_email_message_push_gamer_to_recip_list(Player* player)l
extern _native void sc_email_message_clear_recip_list()l
extern _native void unk_0xAF3C081B(const char* p0)l
extern _native void unk_0x2FB9F53C(bool p0)l
extern _native any unk_0x6C5738AB()l
extern _native any unk_0x468668F0()l
extern _native bool unk_0x90C74343(any p0, any p1)l
extern _native bool unk_0x3ACE6D6B(any p0, any* p1)l
extern _native bool unk_0x579B4510(any p0, float p1)l
extern _native bool unk_0xDF45B2A7(const char* p0)l
extern _native32(0xDF084A6B) bool _sc_start_check_string_task(const char* string, int* taskHandle)l
extern _native32(0xFFED3676) bool _sc_has_check_string_task_completed(int taskHandle)l
extern _native32(0xA796D7A7) int _sc_get_check_string_status(int taskHandle)l
extern _native any unk_0x09497F31(any p0)l
extern _native int unk_0x4D8A6521(any p0)l
extern _native bool unk_0x7AA36406(const char* p0, int* p1)l
extern _native bool unk_0xF379DCE4(any p0)l
extern _native any unk_0x65D84665(any p0)l
extern _native any unk_0xC96456BA()l
extern _native any unk_0x8E7AEEB7(any* p0)l
extern _native bool unk_0xE778B2A7(int p0, const char* p1, any* p2)l
extern _native bool unk_0xCE7D50A8(int p0, const char* p1, any* p2)l
extern _native bool unk_0xD26CCA46(any p0, any* p1)l
extern _native bool unk_0x24D84334(any p0)l
extern _native bool unk_0x8A023024(any p0, any p1)l
extern _native any unk_0x1C65B038()l
extern _native bool unk_0x4D4C37B3()l
extern _native bool unk_0xAED95A6F(const char* p0, int* p1)l
extern _native void unk_0x486867E6()l
#pragma endregion //}
#pragma region UNK //{
extern _native int unk_0x106C8317()l
extern _native bool unk_0xD87F3A9E()l
extern _native void unk_0xC0B971EA(bool p0)l
extern _native any unk_0x94BCAC7C()l
extern _native void unk_0x7D90EEE5(bool p0)l
extern _native32(0x734CFEDA) bool _is_ui_loading_multiplayer()l
extern _native void unk_0x8C227332(bool p0)l
extern _native void unk_0x5C350D78(bool p0)l
#pragma endregion //}
#pragma region UNK1 //{
#pragma endregion //}
#pragma region UNK2 //{
#pragma endregion //}
#pragma region UNK3 //{
#pragma endregion //}

/************ Console Only Natives ************/
extern _native bool network_is_local_talking();

/************ Undocumented Console Only Natives ************
sc_inbox_message_get_data_float
network_is_local_talking
get_number_of_vehicle_model_colours
play_stream_from_position
network_get_killer_of_player
waitunpaused
waitunwarped
get_vehicle_model_value
network_give_player_cash
network_invite_gamer
network_invite_gamer_to_transition
network_receive_player_cash
task_vehicle_follow
clear_text_label
get_current_language
network_set_player_muted
network_remove_all_invites
is_flash_light_on
set_entity_icon_id_color
set_entity_icon_id_visibility
add_entity_icon_by_vector
set_vehicle_brake
network_is_rockstar_dev
get_ped_head_overlay
network_check_give_player_cash
network_check_receive_player_cash
network_earn_from_bank_interest
network_spent_bank_interest
set_poi
set_control_shake
set_poi_special
network_get_game_region
get_shop_ped_prop
get_forced_prop
get_shop_ped_outfit_prop
get_shop_ped_outfit_component
is_cam_transitioning
does_entity_have_icon_id
network_is_unlocked
remove_vehicle_mod_kit
network_buy_smokes
network_remove_followers
network_has_follower
network_retain_followers
restore_script_values_for_network_game
store_script_values_for_network_game
get_anim_duration
get_cutscene_name
***********************************************************/


#undef _native
#undef _native32
