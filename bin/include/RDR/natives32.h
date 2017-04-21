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

#define sin sin_degree
#define cos cos_degree
#define tan tan_degree
#define atan atan_degree
#define atan2 atan2_degree

extern _native int floor(float x)l
extern _native float sin_degree(float x)l
extern _native float cos_degree(float x)l
extern _native float tan_degree(float x)l
extern _native float atan_degree(float x)l
extern _native float atan2_degree(float x, float y)l
extern _native void unk_0x0728B211()l
extern _native void unk_0xF037DCA2(int pram0)l
extern _native void unk_0x1F0CD262(int pram0)l
extern _native void retrieve_game_state(int pram0, int pram1, int pram2)l
extern _native void ui_disable(const char* uiLayer)l
extern _native void ui_exclude(const char* uiLayer)l
extern _native void ui_enable(const char* uiLayer)l
extern _native void ui_include(const char* uiLayer)l
extern _native int unk_0x3B004817()l
extern _native void set_rich_presence(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x7CE2C2E1()l
extern _native void unk_0x49E4EB10(int pram0)l
extern _native void toggle_cover_props(int pram0)l
extern _native void log_message(char* message)l
extern _native int unk_0x814D97E8()l
extern _native void unk_0x6CD7DCE1(int pram0, int pram1)l
extern _native int rand_int_range(int min, int max)l
extern _native int to_float(int pram0)l
extern _native bool ui_isactive(const char* UiLayer)l
extern _native void ui_activate(const char* UiLayer)l
extern _native void set_start_pos(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int request_asset(const char* AssetDir, eAssetType AssetType)l
extern _native void wait(int ms)l
extern _native int launch_new_script(const char* ScriptDir, int Unk0)l
extern _native bool is_script_valid(int ScriptID)l
extern _native Layout find_named_layout(const char* LayoutName)l
extern _native32(0xFC8E55ED) bool _is_layout_valid(Layout Layout)l
extern _native Actor find_actor_in_layout(Layout Layout, const char* ActorName)l
extern _native bool is_actor_valid(Actor Actor)l
extern _native Time make_time_of_day(int Hour, int Minute, int Second)l
extern _native void set_weather(eWeather WeatherType, Time Time)l
extern _native int streaming_is_world_loaded()l
extern _native void hud_fade_in(int pram0, int pram1)l
extern _native void camera_reset(int pram0)l
extern _native void streaming_set_cutscene_mode(int pram0)l
extern _native void terminate_this_script()l
extern _native Layout create_layout(const char* layoutName)l
extern _native void clear_regions()l
extern _native int is_ps3()l
extern _native void unk_0x7ABDE1F0(int pram0)l
extern _native void unk_0x7D7F9770(int pram0)l
extern _native void printnl()l
extern _native int ui_get_num_children(int pram0)l
extern _native void ui_add_child(int pram0, int pram1)l
extern _native void ui_set_data(int pram0, int pram1, int pram2)l
extern _native void unk_0xEC86DB0E()l
extern _native void unk_0x3B25299D(int pram0)l
extern _native void printint(int pram0)l
extern _native void printstring(int pram0)l
extern _native void unk_0x1C8CA53C(int pram0, int pram1)l
extern _native void unk_0xE8960298(int pram0)l
extern _native void unk_0xA8ADCAEB(int pram0)l
extern _native void store_game_state(int pram0, int pram1, int pram2)l
extern _native int unk_0x95CDCE7A()l
extern _native void ui_set_string(char* entry, char* string)l
extern _native Layout get_ambient_layout()l
extern _native void iterate_in_layout(int pram0, int pram1)l
extern _native void set_pause_script(int pram0)l
extern _native void set_time_acceleration(int pram0)l
extern _native void lights_set_on_time(int pram0, int pram1)l
extern _native void lights_set_off_time(int pram0, int pram1)l
extern _native int unk_0x8BA565F7(int pram0)l
extern _native int unk_0xB8E09389(int pram0)l
extern _native int unk_0x0E453CF0(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_time_of_day(Time UnixTime)l
extern _native int net_is_session_host()l
extern _native int net_is_in_session()l
extern _native int unk_0x5D934CCB(int pram0, int pram1)l
extern _native float rand_float_range(float Min, float Max)l
extern _native void unk_0xB35C0660(int pram0)l
extern _native int decor_get_int(int pram0, int pram1)l
extern _native void unk_0x0E4B7A33(int pram0, int pram1)l
extern _native void give_weapon_to_actor(Actor Actor, int WeaponID, int Unk0, int Unk1, int _Unk1)l
extern _native int add_item(const char* ItemName, Actor Actor, int Unk1)l
extern _native void set_player_deadeye_points(int pram0, int pram1, int pram2)l
extern _native void set_disable_deadeye(int pram0, int pram1)l
extern _native void set_deadeye_multilock_enable(int pram0, int pram1)l
extern _native void set_deadeye_targetpaint_enable(int pram0, int pram1)l
extern _native void unk_0xCB017277(int pram0, int pram1)l
extern _native void unk_0x98B3ABFA(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x3417766E(int pram0, int pram1, int pram2)l
extern _native32(0x5842B9D1) int _get_current_time()l
extern _native void unk_0x7D5C0C4D()l
extern _native void unk_0x7E4A92CF(int pram0, int pram1)l
extern _native void ui_set_money(int pram0, int pram1, int pram2)l
extern _native const char* unk_0x47EF426D(const char* pram0)l
extern _native int net_get_playmode()l
extern _native const char* ui_get_string(const char* GXTEntry)l
extern _native void save_soft_save(int pram0)l
extern _native int unk_0x82F63365(int pram0)l
extern _native void set_player_control_rumble(int pram0, int pram1)l
extern _native void script_done_loading()l
extern _native int is_exitflag_set()l
extern _native int get_profile_time()l
extern _native void unk_0xB9D95B4C()l
extern _native int unk_0x5C8DD257(int pram0)l
extern _native Time get_time_of_day()l
extern _native int get_hour(Time T)l
extern _native int hud_is_faded()l
extern _native int hud_is_fading()l
extern _native void unk_0x2E5F186B()l
extern _native int unk_0xEF6BF96E()l
extern _native int net_is_unlocked(int pram0)l
extern _native void printfloat(int pram0)l
extern _native void hud_fade_out(int pram0, int pram1, int pram2)l
extern _native void release_layout_ref(int pram0)l
extern _native void unk_0x86B0B004(int pram0, int pram1)l
extern _native int is_blip_valid(int pram0)l
extern _native void remove_blip(int pram0)l
extern _native void animal_species_gringo_clear_all()l
extern _native void streaming_evict_prop(int pram0)l
extern _native void streaming_evict_propset(int pram0)l
extern _native void streaming_evict_actor(int pram0, int pram1)l
extern _native int get_asset_name(int pram0, int pram1)l
extern _native void remove_anim_set(int pram0)l
extern _native void streaming_evict_gringo(int pram0)l
extern _native void remove_action_tree(int pram0)l
extern _native void remove_string_table(int pram0)l
extern _native void streaming_evict_script(int pram0)l
extern _native void streaming_unrequest_movable_nav_mesh(int pram0)l
extern _native void unk_0x32FCA813(int pram0)l
extern _native void log_error(char* message)l
extern _native int abs(int pram0)l
extern _native void remove_collectable(int pram0, int pram1)l
extern _native int round(int pram0)l
extern _native int unk_0xFA6BDD8E(int pram0, int pram1, int pram2)l
extern _native32(0x8ED1FF95) const char* _float_to_string(float Flt, int unk3, int Precision)l
extern _native const char* int_to_string(int i)l
extern _native void clear_stat_message()l
extern _native int string_to_hash(int pram0)l
extern _native void set_stat_message(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12)l
extern _native bool is_string_valid(const char* pram0)l
extern _native void log_warning(char* message)l
extern _native int add_collectable(int pram0, int pram1, int pram2)l
extern _native int shift_left(int pram0, int pram1)l
extern _native int unk_0x7AB722D8()l
extern _native int unk_0x84B0B5D6()l
extern _native int is_actor_alive(int pram0)l
extern _native void set_weapon_gold(Actor Actor, int Weapon, bool Gold)l
extern _native void unk_0x7D6A8D4A(int pram0, int pram1)l
extern _native int has_achievement_been_passed(int pram0)l
extern _native int award_achievement(int pram0)l
extern _native int award_avatar(int pram0)l
extern _native int decor_check_exist(int pram0, int pram1)l
extern _native bool is_dev_build()l
extern _native const char* ss_get_string(int pram0, int pram1)l
extern _native int save_game(int pram0)l
extern _native void unk_0x17F34613(int pram0)l
extern _native void unk_0xED40F27D(int pram0)l
extern _native int unk_0xBAB151CB()l
extern _native int unk_0x5545C218(int pram0)l
extern _native int unk_0xE623B382(int pram0)l
extern _native int get_player_deadeye_points(int pram0)l
extern _native int get_num_journal_entries_in_list(int pram0)l
extern _native int get_journal_entry_in_list(int pram0, int pram1)l
extern _native int get_journal_entry_type(int pram0)l
extern _native int get_journal_entry_misc_flag(int pram0)l
extern _native int is_journal_entry_updated(int pram0)l
extern _native int get_targeted_journal_entry()l
extern _native int unk_0x118D085E(int pram0)l
extern _native int unk_0xA4B2016D(int pram0)l
extern _native int unk_0x6262DC5E(int pram0, int pram1)l
extern _native int unk_0x0CDD6F94(int pram0)l
extern _native int unk_0x7BF75BCE(int pram0, int pram1)l
extern _native int unk_0x4BB2BC20(int pram0, int pram1)l
extern _native int unk_0x78A3CD3D(int pram0)l
extern _native int unk_0x7F4D5AE0(int pram0, int pram1)l
extern _native int is_frontend_death(int pram0, int pram1, int pram2)l
extern _native Weapon get_weapon_equipped(Actor Actor, int Index)l
extern _native int unk_0x0E0EFB13(int pram0)l
extern _native int unk_0x2C23CBE7(int pram0)l
extern _native int unk_0x608DCAEF(int pram0, int pram1)l
extern _native int unk_0xCC02BBD3(int pram0)l
extern _native int unk_0xA8040D70(int pram0)l
extern _native int unk_0xCCE4A339(int pram0)l
extern _native32(0x0ADC17E9) bool _is_actor_player(Actor actorId)l
extern _native Actor get_player_actor(int PlayerId)l
extern _native int get_day(Time T)l
extern _native int fabs(int pram0)l
extern _native int unk_0x6CC9CCE7()l
extern _native int get_item_count(int pram0, int pram1)l
extern _native void print_objective_format(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int decor_set_int(int pram0, int pram1, int pram2)l
extern _native bool is_object_valid(Object Object)l
extern _native int get_object_position(int pram0, int pram1)l
extern _native int get_object_type(int pram0)l
extern _native void get_volume_scale(int pram0, int pram1)l
extern _native int add_blip_for_coord(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_blip_scale(int pram0, int pram1)l
extern _native void set_blip_color(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_blip_priority(int pram0, int pram1)l
extern _native void set_blip_name(int pram0, int pram1)l
extern _native int is_journal_entry_in_list(int pram0, int pram1)l
extern _native int create_journal_entry(int pram0, int pram1, int pram2, int pram3)l
extern _native void append_journal_entry(int pram0, int pram1)l
extern _native void prepend_journal_entry_detail(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_journal_entry_detail_style(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_journal_entry_progress(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x2AA8E2FA(int pram0, int pram1, int pram2)l
extern _native int is_journal_entry_targeted(int pram0)l
extern _native void remove_journal_entry(int pram0, int pram1)l
extern _native void unk_0x87DC7F5B(int pram0, int pram1)l
extern _native void target_journal_entry(int pram0)l
extern _native void clear_journal_entry(int pram0)l
extern _native int unk_0x60135878()l
extern _native int unk_0x4B2FCAF6()l
extern _native int unk_0x2F0E7DE7()l
extern _native int unk_0x710B3A83()l
extern _native int unk_0x7AB368CF(int pram0, int pram1)l
extern _native void unk_0x08A655C5(int pram0, int pram1)l
extern _native void unk_0x1E98AFEC(int pram0, int pram1)l
extern _native void unk_0xFF3DB575(int pram0, int pram1)l
extern _native int shift_right(int pram0, int pram1)l
extern _native int vdist(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x115CD0CC(int pram0)l
extern _native void unk_0x4F52CB58(int pram0)l
extern _native void destroy_object(Object Object)l
extern _native int is_door_valid(int pram0)l
extern _native int decor_get_object(int pram0, int pram1)l
extern _native int is_door_locked(int pram0)l
extern _native int unk_0x502DAC62(int pram0)l
extern _native int is_actor_in_volume(int pram0, int pram1)l
extern _native int gateway_update(int pram0)l
extern _native int unk_0xD7591B0E(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int was_script_use_context_ever_pressed(int pram0)l
extern _native int unk_0x64BEDDEA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12, int pram13, int pram14, int pram15, int pram16, int pram17)l
extern _native int add_blip_for_object(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xE3E30992(int pram0)l
extern _native void unk_0xCE79F8E2(int pram0, int pram1)l
extern _native int get_gringo_from_object(int pram0)l
extern _native void gringo_allow_activation(int pram0, int pram1)l
extern _native int decor_remove(int pram0, int pram1)l
extern _native int unk_0xCB3F7DA5(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int decor_set_bool(Actor Actor, const char* DecorName, bool set)l
extern _native void print_money(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void set_door_lock(int pram0, int pram1)l
extern _native int get_latest_console_command()l
extern _native void reset_latest_console_command()l
extern _native int string_contains_string(int pram0, int pram1)l
extern _native int unk_0x8C37CA1A(int pram0, int pram1)l
extern _native int unk_0x39286DE5(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x6745191B(int pram0, int pram1, int pram2, int pram3)l
extern _native void terminate_script(int ScriptID)l
extern _native int unk_0x3B1B6407()l
extern _native void unk_0x4C02E1E5()l
extern _native void request_anim_set(int pram0, int pram1)l
extern _native int request_action_tree(int pram0)l
extern _native int has_anim_set_loaded(int pram0)l
extern _native int has_action_tree_loaded(int pram0)l
extern _native int set_anim_set_for_actor(int pram0, int pram1, int pram2)l
extern _native int set_action_node_for_actor(int pram0, int pram1)l
extern _native int set_react_node_for_actor(int pram0, int pram1)l
extern _native int get_num_console_command_tokens()l
extern _native int get_console_command_token(int pram0)l
extern _native int unk_0xAC830865(int pram0, int pram1)l
extern _native void get_volume_center(int pram0, int pram1)l
extern _native int find_ground_intersection(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x19B26C78(int pram0)l
extern _native void unk_0x272D756C(int pram0, int pram1, int pram2)l
extern _native void unk_0x76341F1A(int pram0)l
extern _native void unk_0x5A6418A2(int pram0, int pram1)l
extern _native void unk_0xBCD4979C(int pram0, int pram1, int pram2)l
extern _native void unk_0x30C67D05(int pram0)l
extern _native void unk_0x762192EB(int pram0)l
extern _native void unk_0x309D058C(int pram0)l
extern _native void unk_0x1900A97E(int pram0, int pram1)l
extern _native void unk_0xAA99E18E(int pram0)l
extern _native void unk_0x2CCE1115(int pram0)l
extern _native float string_to_float(const char* Str)l
extern _native Iterator create_object_iterator(Layout layout)l
extern _native void iterate_on_object_type(Iterator Iterator, int Type)l
extern _native Object start_object_iterator(Iterator Iterator)l
extern _native int unk_0x024B2FFC(int pram0)l
extern _native int unk_0x36CC24A4(int pram0)l
extern _native void unk_0x4028CE77(int pram0)l
extern _native int object_iterator_next(int pram0)l
extern _native void destroy_iterator(int pram0)l
extern _native int string_length(const char* pram0)l
extern _native int string_upper(int pram0)l
extern _native32(0x8218D693) bool _string_compare(const char* Str1, const char* Str2)l
extern _native int string_to_int(const char* pram0)l
extern _native void get_position(int pram0, vector3* outCoords)l
extern _native float get_heading(int pram0)l
extern _native int load_soft_save(int pram0)l
extern _native int does_file_exist(int pram0)l
extern _native int load_game(int pram0)l
extern _native int unk_0x8C710D3E(int pram0)l
extern _native void net_log(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native Camera get_game_camera()l
extern _native void get_camera_direction(Camera Cam, vector3* OutDirection)l
extern _native void get_camera_position(Camera Cam, vector3* OutPosition)l
extern _native void vscale(vector3* Vector, float Scale)l
extern _native int get_actorenum_from_string(const char* ActorName)l //case sensitive
extern _native void streaming_request_actor(int pram0, int pram1, int pram2)l
extern _native int streaming_is_actor_loaded(int pram0, int pram1)l
extern _native int unk_0x4A2063EC(int pram0)l
extern _native int get_object_orientation(int pram0, int pram1)l
extern _native Layout unk_0xADE13224()l//ambient object layout?
extern _native Actor create_actor_in_layout(Layout Layout, const char* ActorName, eActor ActorID, vector3 Position, vector3 Rotation)l
extern _native void task_stand_still(int pram0, int pram1, int pram2, int pram3)l
extern _native int string_lower(int pram0)l
extern _native void kill_actor(int pram0)l
extern _native void print_frame_time(int pram0)l
extern _native int launch_new_script_with_args(int pram0, int pram1, int pram2, int pram3)l
extern _native int get_actor_axis(int pram0, int pram1, int pram2)l
extern _native void script_breakpoint(int pram0)l
extern _native int unk_0x025C9845(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native Object create_prop_in_layout(Layout Layout, const char* PropName, const char* FragmentPath, vector3 Position, vector3 Rotation, bool Frozen)l
extern _native int find_object_in_object(int pram0, int pram1)l
extern _native int in_targetting_posse(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int snap_actor_to_gringo(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void audio_music_force_track(const char* SongName, const char* Mood, int pram2, int pram3, int pram4, float pram5, int pram6)l
extern _native int unk_0x6A9CFA2A(int pram0)l
extern _native int ai_ignore_actor(int pram0)l
extern _native void unk_0x4DF3C5D1()l
extern _native int unk_0xCCB57C38(int pram0)l
extern _native void unk_0x5AEB2E4F(int pram0)l
extern _native int unk_0x17883570(int pram0)l
extern _native void unk_0x10873616()l
extern _native int set_ownership_straggler(int pram0, int pram1)l
extern _native int string_num_tokens()l
extern _native int string_get_token(int pram0)l
extern _native int unk_0x990614C1(int pram0)l
extern _native int is_volume_valid(int pram0)l
extern _native void unk_0xC0C6245E(int pram0)l
extern _native int get_object_name(int pram0)l
extern _native int unk_0x2803BDA8(int pram0)l
extern _native void unk_0x1BD78730(int pram0, int pram1, int pram2)l
extern _native int unk_0xF437B3D9(int pram0, int pram1, int pram2, int pram3)l
extern _native int get_object_relative_position(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int get_object_relative_orientation(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xC07681C1(int pram0, int pram1, int pram2, int pram3)l
extern _native int get_asset_id(const char* AssetPath, eAssetType AssetType)l
extern _native void streaming_request_propset(int pram0)l
extern _native int streaming_is_propset_loaded(int pram0)l
extern _native void unk_0x836466F8(int pram0)l
extern _native int unk_0x779267C3(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int unk_0x51D6DA2C(int pram0)l
extern _native int unk_0x5219B7D0(int pram0)l
extern _native int decor_check_string(Object decor, const char* EventType, const char* EventName)l
extern _native void unk_0x3E509DF1(int pram0, int pram1)l
extern _native int unk_0xDB70DF0C(int pram0)l
extern _native void set_physinst_frozen(int pram0, int pram1)l
extern _native int unk_0x6B72661F(int pram0)l
extern _native int unk_0x3CD2C250(int pram0)l
extern _native int add_ai_coverset_for_propset(int pram0)l
extern _native int get_vehicle(int pram0)l
extern _native void printvector(int pram0, int pram1, int pram2)l
extern _native void unk_0xD695F857(int pram0)l
extern _native int unk_0x8F4B473D(int pram0, int pram1, int pram2)l
extern _native void task_kill_char(int pram0, int pram1)l
extern _native void task_melee_attack(int pram0, int pram1, int pram2)l
extern _native int actor_mount_actor(int pram0, int pram1)l
extern _native void reset_analog_positions(int pram0, int pram1)l
extern _native void iterate_in_sphere(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int get_num_iterator_matches(int pram0)l
extern _native int unk_0x960DB7A5()l
extern _native bool is_iterator_valid(Iterator iterator)l
extern _native void iterate_everywhere(int pram0)l
extern _native int unk_0xB578DB52(int pram0)l
extern _native int unk_0xE07C2D99(int pram0)l
extern _native void unk_0x6761D53A(int pram0, int pram1)l
extern _native int unk_0x85C58BE1(int pram0)l
extern _native void unk_0x2D6CD106(int pram0, int pram1)l
extern _native int unk_0xD60032F6(int pram0)l
extern _native Object find_object_in_layout(Layout Layout, const char* ObjectName)l
extern _native int is_crime_valid(int pram0)l
extern _native void set_crime_type(int pram0, int pram1)l
extern _native void set_crime_victim(int pram0, int pram1)l
extern _native void set_crime_criminal(int pram0, int pram1)l
extern _native void unk_0x2AE7D51F(int pram0, int pram1)l
extern _native void unk_0x898B00F4(int pram0, int pram1)l
extern _native int set_crime_position(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x921B5F2B(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_crime_objectset(int pram0, int pram1)l
extern _native void set_crime_faction(int pram0, int pram1)l
extern _native void unk_0x54E7F26B(int pram0, int pram1)l
extern _native void set_crime_counter(int pram0, int pram1)l
extern _native void unk_0x8521A685(int pram0, int pram1)l
extern _native int unk_0x831338D9(int pram0)l
extern _native int unk_0x2CB3B980(int pram0)l
extern _native int unk_0x43FBBDE1(int pram0, int pram1)l
extern _native int set_actor_time_of_last_crime(int pram0, int pram1)l
extern _native void iterate_in_set(Iterator Iterator, IterationSet IterationSet)l
extern _native int get_iterator_parent(int pram0)l
extern _native int unk_0x7C3D1193(int pram0)l
extern _native void add_time(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_rain_amount(float Amount)l
extern _native void unk_0xF0C9645A(float Amount)l
extern _native void unk_0xEB866555()l
extern _native void set_wind(int pram0, int pram1, int pram2)l
extern _native void set_auto_wind()l
extern _native void unk_0x063F900A(int pram0)l
extern _native bool does_script_exist(const char* ScriptPath)l
extern _native void file_start_path(int pram0)l
extern _native void unk_0x63CDBB01(int pram0)l
extern _native void file_end_path()l
extern _native int unk_0x6F323C5F()l
extern _native int unk_0x4417C9F2(int pram0)l
extern _native void unk_0x05719022(int pram0)l
extern _native int net_start_new_script(int pram0, int pram1)l
extern _native int unk_0xC739D1D2(int pram0)l
extern _native int unk_0xB50E95D7(int pram0)l
extern _native void unk_0x95FBA0B0(int pram0, int pram1)l
extern _native void set_player_control(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x243AF970(int pram0, int pram1, int pram2)l
extern _native void unk_0x598815BD(int pram0)l
extern _native32(0xE42A8278) void _print_help(char* txt, float time, bool isStringLiteral, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int unk_0x9C9529D8(int pram0, int pram1)l
extern _native int get_minute(Time T)l
extern _native int get_second(Time T)l
extern _native int is_objectset_valid(int pram0)l
extern _native int get_objectset_size(int pram0)l
extern _native void clean_objectset(int pram0)l
extern _native int unk_0x50D39153(int pram0, int pram1)l
extern _native void unk_0xA3E05BAE(int pram0, int pram1)l
extern _native int unk_0x49D0DF2E(int pram0)l
extern _native void release_curve(int pram0)l
extern _native int vmag(int pram0, int pram1, int pram2)l
extern _native int unk_0xD3FE15FB()l
extern _native int unk_0xD34F7B3A()l
extern _native int unk_0x913A5CB6()l
extern _native int unk_0x214AFB8C(int pram0)l
extern _native int unk_0x2AF84928(int pram0)l
extern _native int unk_0x87C5471F(int pram0)l
extern _native int ceil(int pram0)l
extern _native void unk_0x4D918005(int pram0, int pram1)l
extern _native int has_item(int pram0, int pram1)l
extern _native void delete_item(int pram0, int pram1, int pram2)l
extern _native void unk_0x40121E4F(int pram0, int pram1)l
extern _native void unk_0xDE84B637(int pram0, int pram1)l
extern _native void ai_speech_set_allow_context_global(int pram0, int pram1)l
extern _native void set_actor_should_taunt(int pram0, int pram1)l
extern _native void unk_0x4B0D6152(int pram0, int pram1)l
extern _native int unk_0x0CC3D8F6(int pram0, int pram1)l
extern _native int unk_0xFAC315B7(int pram0, int pram1, int pram2)l
extern _native int decor_set_float(int pram0, int pram1, int pram2)l
extern _native void update_profile_stat(int pram0, int pram1, int pram2)l
extern _native void set_journal_entry_trophy(int pram0, int pram1)l
extern _native int unk_0x5CAFCBD4(int pram0, int pram1, int pram2)l
extern _native int get_ammo_enum(int pram0)l
extern _native int unk_0xDB679ED9(int pram0)l
extern _native void unk_0x4372593E(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xA534CD14(int pram0, int pram1, int pram2)l
extern _native int is_point_in_volume(int pram0, int pram1, int pram2, int pram3)l
extern _native int is_actor_riding(int pram0)l
extern _native int is_any_speech_playing(int pram0)l
extern _native void unk_0x31BAF169(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int get_actor_velocity(int pram0, int pram1)l
extern _native int get_camera_channel_position(int pram0, int pram1)l
extern _native int get_actor_health(int pram0)l
extern _native int get_actor_max_health(int pram0)l
extern _native int is_actor_in_water(int pram0)l
extern _native void set_blip_blink(int pram0, int pram1, int pram2, int pram3)l
extern _native int is_actor_driving_vehicle(int pram0)l
extern _native int unk_0x5D41D423(int pram0)l
extern _native int unk_0xDF024C94(int pram0, int pram1, int pram2)l
extern _native void hud_clear_objective()l
extern _native32(0xE4DACF40) void _clear_prints()l
extern _native32(0x32394BB6) void _print_subtitle(const char* txt, float time, bool isStringLiteral, int printType, int pram4, int pram5, int pram6, int pram7)l
extern _native void set_deadeye_point_modifier(int pram0, int pram1)l
extern _native void set_max_deadeye_points(int pram0, int pram1)l
extern _native void unk_0x27A96719(int pram0, int pram1)l
extern _native void set_weather_complex(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12, int pram13, int pram14)l
extern _native void iterate_on_partial_name(int pram0, int pram1)l
extern _native void iterate_on_partial_model_name(int pram0, int pram1)l
extern _native void hud_clear_big_text()l
extern _native void hud_clear_counter()l
extern _native void hud_clear_help()l
extern _native void hud_clear_small_text()l
extern _native void unk_0x777A1CA2()l
extern _native void hud_clear_help_queue()l
extern _native void unk_0x02E1E708()l
extern _native void clear_gps_path(int pram0)l
extern _native int unk_0x5C51D43C(int pram0, int pram1)l
extern _native int unk_0xFDF42AAC(int pram0, int pram1)l
extern _native void unk_0xD923CD1B(int pram0, int pram1)l
extern _native int unk_0x0E2C4B68(int pram0, int pram1)l
extern _native int unk_0xFAD5A270(int pram0, int pram1)l
extern _native void unk_0xA9459BB6(int pram0, int pram1, int pram2)l
extern _native void unk_0x9D9784B8(int pram0, int pram1)l
extern _native void unk_0xE1124E00()l
extern _native void reset_game()l
extern _native void unk_0x9C80A3A4(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void equip_accessory(int pram0, int pram1, int pram2)l
extern _native int unk_0xA677B204(int pram0)l
extern _native int actor_has_weapon(int pram0, int pram1)l
extern _native int unk_0xFEEC4EE2(int pram0)l
extern _native void enable_weather_sphere(int pram0, int pram1)l
extern _native void unk_0xC0556FB8(int pram0, int pram1)l
extern _native int append_region(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0xA17311E4(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native int unk_0x177A3843(int pram0, int pram1)l
extern _native void unk_0xB104FF3E(int pram0, int pram1)l
extern _native int unk_0x31D76951(int pram0, int pram1)l
extern _native int unk_0x1FEECD4C(int pram0)l
extern _native int unk_0x24C18749(int pram0, int pram1, int pram2)l
extern _native void unk_0x08765C6B(int pram0, int pram1)l
extern _native void unk_0xFD0AA999()l
extern _native void unk_0xBFB65BE8()l
extern _native void unk_0x71BE51F4()l
extern _native int is_mission_script()l
extern _native int streaming_request_prop(int pram0, int pram1)l
extern _native void streaming_request_gringo(int pram0)l
extern _native void request_string_table(const char* StringTablePath)l
extern _native void streaming_request_script(int pram0)l
extern _native void streaming_request_movable_nav_mesh(int pram0)l
extern _native void unk_0x620649B4(int pram0)l
extern _native int streaming_is_prop_loaded(int pram0)l
extern _native int streaming_is_gringo_loaded(int pram0)l
extern _native bool has_string_table_loaded(const char* StringTablePath)l
extern _native int streaming_is_script_loaded(int pram0)l
extern _native int streaming_is_movable_nav_mesh_resident(int pram0)l
extern _native int unk_0x67994764(int pram0)l
extern _native32(0x9C424E0D) int _get_id_of_this_script()l
extern _native int unk_0x01309706(int pram0)l
extern _native void unk_0x90CD8795(int pram0, int pram1)l
extern _native void unk_0x9E88643A(int pram0, int pram1)l
extern _native void unk_0xDAD46FAB()l
extern _native32(0xB731EB45) void _cheat_infinite_horse_stamina(bool Activate)l
extern _native32(0x3F67DEDB) int _cheat_blazing_guns(bool Activate)l
extern _native void unk_0x7D0EFDD8(int pram0)l
extern _native void push_command_handle(int pram0, int pram1)l
extern _native void unk_0xF1A723D0(int pram0, int pram1)l
extern _native void create_stat(int pram0, int pram1, int pram2, int pram3)l
extern _native void disable_child_sector(int pram0)l
extern _native void enable_child_sector(int pram0)l
extern _native void set_curve_weight(int pram0, int pram1)l
extern _native void disable_world_sector(int pram0)l
extern _native void enable_world_sector(int pram0)l
extern _native int enable_curve(int pram0, int pram1)l
extern _native int unk_0xC7612A79(int pram0, int pram1)l
extern _native void unk_0xD44F7102(int pram0, int pram1, int pram2)l
extern _native const char* vector_to_string(vector3* Vec)l
extern _native void audio_music_set_state(int pram0)l
extern _native int unk_0x38771B89(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int unk_0xC426D16F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void load_audio_bank(const char* RefName, const char* BankPath)l
extern _native32(0x98CD7340) bool _is_audio_bank_loading(const char* RefName, const char* BankPath)l
extern _native void unk_0x176E921C(const char* pram0)l
extern _native int request_mission_audio_bank(const char* pram0)l
extern _native void unk_0xA82D893C(int pram0, int pram1)l
extern _native void destroy_volume(int pram0)l
extern _native void unk_0xBFD6D55F(int pram0, int pram1)l
extern _native void set_player_endless_readymode(int pram0, int pram1)l
extern _native void reset_anim_set_for_actor(int pram0, int pram1)l
extern _native void set_player_posture(int pram0, int pram1, int pram2)l
extern _native int unk_0xD86BFBD8(int pram0, int pram1)l
extern _native void unk_0x851F88F6(int pram0)l
extern _native void unk_0xF86010D1(int pram0, int pram1)l
extern _native void unk_0xBAEC56D1(int pram0)l
extern _native void append_journal_entry_detail(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int get_player_combatmode()l
extern _native int decor_get_float(int pram0, int pram1)l
extern _native void disband_objectset(int pram0)l
extern _native int unk_0xF5EE5874(int pram0)l
extern _native int unk_0x2F358B89(int pram0, int pram1)l
extern _native int unk_0x061A2A3C()l
extern _native void unk_0xCA840DBB(int pram0)l
extern _native int unk_0x0B1569C5(int pram0, int pram1, int pram2)l
extern _native int unk_0x9A73C2CD()l
extern _native int unk_0x8E0D7219(int pram0, int pram1)l
extern _native void ui_send_event(int pram0)l
extern _native int unk_0xD8E31D42()l
extern _native int unk_0x4BA92498()l
extern _native void set_camera_position(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_camera_orientation(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_camera_direction(Camera Cam, vector3 Direction, bool Unk1)l
extern _native void set_current_camera_on_channel(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void unk_0x2A3B1045(int pram0)l
extern _native void unk_0x8F82B7D4(int pram0, int pram1)l
extern _native void unk_0x9E6D7105(int pram0)l
extern _native void unk_0xBB2EABF9(int pram0)l
extern _native void unk_0x18346D88()l
extern _native void unk_0x0C197810()l
extern _native void remove_camera_from_channel(int pram0, int pram1)l
extern _native void destroy_layout(int pram0)l
extern _native void hud_enable(int pram0)l
extern _native void settimera(int pram0)l
extern _native int unk_0x82A290D4()l
extern _native int unk_0x111554E2(int pram0)l
extern _native int unk_0xC64DF45D()l
extern _native int ui_isfocused(const char* UiLayer)l
extern _native int net_is_online_available()l
extern _native int unk_0xCF02D1D6(int pram0)l
extern _native bool is_button_pressed(Controller Controller, eButton Button, int Unk1, int Unk0)l
extern _native void ui_exit(const char* uiLayer)l
extern _native int unk_0x03962973()l
extern _native void destroy_objectset(int pram0)l
extern _native int unk_0x2D160228(int pram0, int pram1)l
extern _native int squad_is_valid(int pram0)l
extern _native int squad_get_size(int pram0)l
extern _native int squad_get_actor_by_index(int pram0, int pram1)l
extern _native void unk_0xEA86A817(int pram0)l
extern _native void unk_0x1D4786CF(int pram0)l
extern _native void unk_0xED6D63FE(int pram0)l
extern _native int unk_0xE18028C1(int pram0)l
extern _native void unk_0x25690082(int pram0)l
extern _native void unk_0x57478561(int pram0)l
extern _native void squad_leave(int pram0)l
extern _native void destroy_actor(int pram0)l
extern _native void release_actor_as_ambient(int pram0)l
extern _native void release_actor(Actor Actor)l
extern _native int camera_is_visible_actor(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void release_object_ref(int pram0)l
extern _native32(0xF6207DF5) GUIWindow _gui_get_window(int GUIHandle, const char* WindowName)l
extern _native int gui_window_valid(int pram0)l
extern _native int gui_close_window(int pram0)l
extern _native void unk_0x5AC72FCC(int pram0)l
extern _native void unk_0x73BE57AF(int pram0)l
extern _native void unk_0xA094152A(int pram0)l
extern _native void set_actor_invulnerability(Actor Actor, bool Invulnerable)l
extern _native void unk_0xA737CCAC(int pram0)l
extern _native void ui_pop(const char* pram0)l
extern _native void streaming_unload_bounds()l
extern _native int unk_0xCE043618()l
extern _native void unk_0x0DFF578A(int pram0, int pram1, int pram2)l
extern _native int would_actor_be_visible(int pram0, int pram1, int pram2)l
extern _native int unk_0x44A34042(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void squad_make_empty(int pram0)l
extern _native int unk_0x1D69F321(int pram0, int pram1, int pram2)l
extern _native void task_bird_land_at_coord(int pram0, int pram1)l
extern _native int unk_0x5F7176D6()l
extern _native int get_weather()l
extern _native int find_named_population_set(int pram0)l
extern _native int is_popset_valid(int pram0)l
extern _native int object_iterator_current(int pram0)l
extern _native int is_gringo_valid(int pram0)l
extern _native int unk_0xE2DCFF34(int pram0, int pram1, int pram2)l
extern _native void unk_0x8EB5CE58(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x0DC149BD(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xD92BA5B6(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int unk_0xFF8CBD07(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int get_locator_offsets(int pram0, int pram1, int pram2, int pram3)l
extern _native int set_object_position(Object Obj, vector3 Position)l
extern _native void unk_0x47C5E353(int pram0, int pram1)l
extern _native void unk_0x3932B786(int pram0)l
extern _native int unk_0xF7277A0F(int pram0, int pram1)l
extern _native int unk_0xD0C471FB(int pram0)l
extern _native int get_actor_from_object(int pram0)l
extern _native bool is_actor_vehicle(Actor Actor)l
extern _native int unk_0x994F2BD1(int pram0, int pram1)l
extern _native void unk_0x43F59172(int pram0)l
extern _native void unk_0x52D984AF(int pram0)l
extern _native void ai_goal_look_clear(int pram0)l
extern _native void unk_0x031E983D(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void set_actor_allow_weapon_reactions(int pram0, int pram1)l
extern _native void ai_quick_exit_gringo(int pram0, int pram1)l
extern _native int get_last_attacker(int pram0)l
extern _native int get_rider(int pram0)l
extern _native void task_clear(int pram0)l
extern _native void task_wander(int pram0, int pram1)l
extern _native void memory_prefer_riding(int pram0, int pram1)l
extern _native void release_layout_objects(int pram0)l
extern _native bool is_actor_riding_vehicle(Actor Actor)l
extern _native int get_mount(int pram0)l
extern _native int unk_0xF68C926F(int pram0)l
extern _native int unk_0xD85CA776(int pram0)l
extern _native int get_draft_actor(int pram0, int pram1)l
extern _native bool is_actor_dead(Actor actor)l
extern _native int is_object_in_objectset(int pram0, int pram1)l
extern _native const char* get_actor_name(Actor actor)l
extern _native int unk_0x1449EE9E(int pram0)l
extern _native void ai_set_nav_material_usage(int pram0, int pram1, int pram2)l
extern _native void set_actor_exempt_from_ambient_restrictions(int pram0, int pram1)l
extern _native void set_actor_obey_ambient_move_restrictions(int pram0, int pram1)l
extern _native void ai_set_enable_dead_body_reactions(int pram0, int pram1)l
extern _native int decor_set_object(int pram0, int pram1, int pram2)l
extern _native int decor_get_bool(int pram0, int pram1)l
extern _native int camera_is_visible_point(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void memory_identify(int pram0, int pram1)l
extern _native void memory_consider_as(int pram0, int pram1, int pram2)l
extern _native int is_ai_actor_unalerted(int pram0)l
extern _native void ai_goal_look_at_actor(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void unk_0xFE5715A1(int pram0, int pram1, int pram2)l
extern _native void unk_0x15B7044B(int pram0, int pram1, int pram2, int pram3)l
extern _native bool is_actor_on_foot(int actor)l
extern _native void ai_set_player_projectile_impact_hear_range(int pram0, int pram1)l
extern _native int ai_has_player_projectile_impacted_within(int pram0, int pram1)l
extern _native int ai_has_player_projectile_near_missed_within(int pram0, int pram1, int pram2)l
extern _native int unk_0xA5A24484(int pram0)l
extern _native int unk_0x86BAAC6C(int pram0, int pram1)l
extern _native int is_player_weapon_zoomed(int pram0)l
extern _native int memory_get_is_visible(int pram0, int pram1)l
extern _native int unk_0x02365961(int pram0)l
extern _native int unk_0x7F454A92(int pram0)l
extern _native void cancel_currently_playing_ambient_speech(int pram0)l
extern _native void ai_speech_set_allow_for_actor(int pram0, int pram1)l
extern _native void unk_0x99AFD2D1(int pram0, int pram1, int pram2)l
extern _native int get_actor_enum(int pram0)l
extern _native void unk_0xC1F9A360(int pram0)l
extern _native void unk_0xAD42EABC(int pram0, int pram1)l
extern _native int unk_0x5C4262F9(int pram0)l
extern _native int unk_0x6C939AA7(int pram0, int pram1)l
extern _native void task_use_gringo(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_actor_stay_within_volume(int pram0, int pram1, int pram2, int pram3)l
extern _native void ai_goal_look_at_neutral(int pram0, int pram1)l
extern _native int unk_0xFA37C0FA(int pram0, int pram1, int pram2)l
extern _native void task_priority_set(int pram0, int pram1)l
extern _native void task_wander_in_volume(int pram0, int pram1, int pram2)l
extern _native void squad_join(int pram0, int pram1)l
extern _native int unk_0x7080E24A(int pram0, int pram1, int pram2)l
extern _native int unk_0x9A93E7CA(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x002B0698(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x9AA8A1B1(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x426828CB(int pram0)l
extern _native int gringo_enable_spawn(int pram0, int pram1)l
extern _native int attach_objects(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int is_attachment_valid(int pram0)l
extern _native int unk_0x000079CB(int pram0)l
extern _native int unk_0x1F003E6C(int pram0, int pram1, int pram2)l
extern _native int unk_0x35CD589C(int pram0)l
extern _native void create_object_glow(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void release_volume(int pram0)l
extern _native void add_ai_move_restriction_stay_outside_of_volume_set(int pram0, int pram1)l
extern _native void unk_0x0ACF7E75(int pram0)l
extern _native void remove_ai_move_restriction_stay_outside_of_volume_set(int pram0, int pram1)l
extern _native void unk_0x80FF115A(int pram0)l
extern _native int unk_0xD3503922(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int get_actorenum_species(int pram0)l
extern _native int is_population_set_ready(int pram0, int pram1, int pram2)l
extern _native int unk_0x8FD12F97(int pram0)l
extern _native int get_actorenum_in_population(int pram0, int pram1)l
extern _native int get_actorenum_in_population_weight(int pram0, int pram1)l
extern _native void task_flee_actor(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void memory_clear_all(int pram0)l
extern _native int get_current_gringo(int pram0)l
extern _native int unk_0x111501F7(int pram0)l
extern _native int create_corpse_in_layout(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int request_fixed_corpse(int pram0, int pram1)l
extern _native void unk_0x05D69EA6(int pram0, int pram1)l
extern _native int unk_0xCC277C0A(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int unk_0x3DD1DC3F(int pram0, int pram1)l
extern _native int unk_0x9C40E671(int pram0)l
extern _native int set_object_position_on_ground(Object Obj, vector3 Position)l
extern _native int unk_0x7A6146DB(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void set_camera_focus_prompt_text(int pram0, int pram1)l
extern _native void unk_0x601FC9F4(int pram0, int pram1)l
extern _native void unk_0x04A38C60(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native const char* get_script_name()l
extern _native int get_total_minutes(int pram0)l
extern _native int unk_0xA5FF6076(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x0E018669(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int unk_0x8E551A7C(int pram0)l
extern _native int unk_0xE531DCAE(int pram0, int pram1, int pram2)l
extern _native int unk_0xBD4E48A6(int pram0, int pram1)l
extern _native void unk_0xDF93BD7C(int pram0)l
extern _native int is_pers_char_alive(int pram0)l
extern _native int unk_0x2CA16327(int pram0)l
extern _native void ambient_set_search_center_player()l
extern _native void unk_0xA89B77A7(int pram0, int pram1)l
extern _native void unk_0x609514AE(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x45190938(int pram0, int pram1, int pram2)l
extern _native void unk_0x912EEC43(int pram0, int pram1, int pram2)l
extern _native void unk_0x9A35520B(int pram0)l
extern _native void unk_0xA337135A(int pram0)l
extern _native void unk_0x0AC99007(int pram0, int pram1)l
extern _native void unk_0x54BD1C65(int pram0, int pram1)l
extern _native void unk_0xC8B149B4(int pram0)l
extern _native int unk_0x0C6EF9E1(int pram0, int pram1)l
extern _native void unk_0xB1609063(int pram0)l
extern _native void unk_0x9CD2B55F(int pram0, int pram1, int pram2)l
extern _native void unk_0x391F3607(int pram0, int pram1, int pram2)l
extern _native int unk_0xBADCF1E9(int pram0)l
extern _native void unk_0x19D652F9(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x30A9FA0A(int pram0, int pram1)l
extern _native int get_x(int pram0)l
extern _native int get_z(int pram0)l
extern _native int create_population_set(int pram0)l
extern _native void unk_0x0C1B8DEA(int pram0, int pram1, int pram2)l
extern _native void unk_0x50ED77F1(int pram0, int pram1)l
extern _native void ai_set_enable_horse_charge_reactions(int pram0, int pram1)l
extern _native void unk_0xF4429710(int pram0, int pram1)l
extern _native void unk_0xB421AFCA(int pram0)l
extern _native void hogtie_actor(int pram0)l
extern _native void task_face_actor(int pram0, int pram1, int pram2, int pram3)l
extern _native void memory_set_weapon_draw_preference(int pram0, int pram1)l
extern _native void task_point_gun_at_object(int pram0, int pram1, int pram2, int pram3)l
extern _native int is_actor_hogtied(int pram0)l
extern _native int get_hogtied_master(int pram0)l
extern _native int unk_0xFF0B53EF()l
extern _native int ai_is_hostile_or_enemy(int pram0, int pram1)l
extern _native int unk_0xA936E73B(int pram0, int pram1)l
extern _native void mark_object_for_aggressive_cleanup(int pram0, int pram1)l
extern _native void unk_0xA8BD64D1(int pram0)l
extern _native void memory_report_position_auto(int pram0, int pram1, int pram2)l
extern _native int add_blip_for_actor(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0xA4F209D5(int pram0)l
extern _native int is_ambient_speech_playing(int pram0)l
extern _native int unk_0xD98CB6F6(int pram0)l
extern _native int task_sequence_open()l
extern _native void task_sequence_close()l
extern _native void task_sequence_perform(int pram0, int pram1)l
extern _native void task_sequence_release(int pram0, int pram1)l
extern _native void unk_0xA343FDBB()l
extern _native int unk_0x7957CA4F(int pram0, int pram1, int pram2)l
extern _native void task_mount(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void set_actor_one_shot_death(int pram0, int pram1)l
extern _native void unk_0x2EBE540D(int pram0, int pram1)l
extern _native void combat_class_ai_set_friendly_fire_consideration(int pram0, int pram1)l
extern _native void combat_class_ai_set_attrib_float(int pram0, int pram1, int pram2)l
extern _native int unk_0xF270EAC1(int pram0)l
extern _native int decor_set_vector(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xBF680846(int pram0)l
extern _native int unk_0x016C6801(int pram0, int pram1)l
extern _native int actors_in_range(int pram0, int pram1, int pram2)l
extern _native void print_help_format(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native32(0xB114332D) int _push_neg_one()l
extern _native void unk_0x45589499(int pram0)l
extern _native int gui_set_text(int TextHandle, const char* MenuName)l
extern _native32(0xCBC97619) bool _is_key_pressed(eKey KeyCode)l
extern _native int gui_make_text(int GUIHandle, SizedArray Position, const char* MenuTitle, const char* GXTText, float pram4)l
extern _native int gui_set_text_color(int TextHandle, float* ColorArea)l
extern _native32(0x524F6981) Controller _get_actor_controller(int ActorId)l
extern _native float get_stick_y(Controller Controller, bool IsRightStick, int unk1)l
extern _native float get_stick_x(Controller Controller, bool IsRightStick, int unk1)l
extern _native void unk_0x3C2D93C1(float x, float y, const char* Text, float r, float g, float b, float a)l
extern _native int gui_set_text_justify(int TextHandle, int JustifyType)l
extern _native int get_task_status(int pram0, int pram1)l
extern _native void memory_clear_events(int pram0, int pram1)l
extern _native int unk_0xAFB1CC55(int pram0)l
extern _native int ai_impairment_mask_matches(int pram0, int pram1)l
extern _native int squad_get(int pram0)l
extern _native int unk_0xAEDD7512(int pram0)l
extern _native int say_single_line_string_beat(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void unk_0xBA734A15(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native bool is_actor_human(int actor)l
extern _native void memory_allow_take_cover(int pram0, int pram1)l
extern _native int unk_0xEE0AB3DD(int pram0)l
extern _native int get_crime_criminal(int pram0)l
extern _native int get_crime_type(int pram0)l
extern _native int is_actor_on_train(int pram0, int pram1)l
extern _native int get_last_hit_time(int pram0)l
extern _native int unk_0xFF5F7D2C(int pram0, int pram1)l
extern _native int unk_0xCC04895F(int pram0, int pram1)l
extern _native int unk_0xB1FCFFDC(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x4685D538(int pram0, int pram1, int pram2, int pram3)l
extern _native int gringo_update_int(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_actor_update_priority(int pram0, int pram1)l
extern _native int unk_0xBE5D84BF(int pram0)l
extern _native void get_formation_location(int pram0, int pram1, int pram2)l
extern _native void set_draw_actor(Actor pram0, bool ToDraw)l
extern _native void clear_actor_max_speed(int pram0)l
extern _native bool is_actor_animal(Actor Actor)l
extern _native int animal_actor_get_species(int pram0)l
extern _native void animal_species_rel_set_can_attack(int pram0, int pram1, int pram2)l
extern _native void combat_class_ai_set_attrib_bool(int pram0, int pram1, int pram2)l
extern _native void memory_allow_shooting(int pram0, int pram1)l
extern _native void set_actor_max_speed(int pram0, int pram1)l
extern _native void unk_0xD1CF9793(int pram0)l
extern _native int add_script_use_context_in_volume(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int unk_0x758F993A(int pram0)l
extern _native void break_off_above(int pram0, int pram1)l
extern _native int set_prop_velocity(int pram0, int pram1)l
extern _native int unk_0xFADF0B96(int pram0)l
extern _native void set_volume_enabled(int pram0, int pram1)l
extern _native void unk_0xDC6DEE92(int pram0, int pram1)l
extern _native void ai_set_enable_stickup_override(int pram0, int pram1)l
extern _native void set_actor_cutscene_mode(int pram0, int pram1)l
extern _native void audio_music_one_shot(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x9398BE8F(int pram0)l
extern _native bool enable_vehicle_seat(Actor Vehicle, int SeatId, bool Enable)l
extern _native int decor_set_string(int pram0, int pram1, int pram2)l
extern _native int create_weapon_pickup(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void set_draw_object(int pram0, int pram1)l
extern _native int unk_0xDAB0D820(int pram0)l
extern _native int unk_0x3ACE659E(int pram0)l
extern _native Actor get_actor_in_vehicle_seat(Vehicle Veh, int SeatID)l
extern _native32(0xE7023D23) void _create_explosion(vector3* coords, const char* explosionName, bool pram2, vector3* damageVector, bool pram4)l
extern _native int unk_0xF04335A6(int pram0, int pram1)l
extern _native int unk_0x4FF36FA7(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int is_physinst_valid(int pram0)l
extern _native int unk_0x0550E178(int pram0)l
extern _native int unk_0x659532FB(int pram0, int pram1)l
extern _native void unk_0x9AC1CA75(int pram0, int pram1, int pram2)l
extern _native int unk_0xCBB2267A(int pram0, int pram1)l
extern _native int get_object_owner(int pram0)l
extern _native int unk_0x65C3D8F6()l
extern _native int attach_draft_to_vehicle(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xB12584C8(int pram0, int pram1)l
extern _native void unk_0x6F9C399B(int pram0)l
extern _native void unk_0xCB1E8485(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0x12325AE7(int pram0)l
extern _native void start_vehicle(Actor Vehicle)l
extern _native void streaming_unload_scene()l
extern _native int unk_0xE975BE40(int pram0)l
extern _native int is_actor_using_ledge(int pram0)l
extern _native int unk_0x231E7034(int pram0)l
extern _native int unk_0x8FFDCE5C(int pram0, int pram1)l
extern _native void enable_use_contexts(int pram0)l
extern _native void unk_0x15547025()l
extern _native void unk_0xF03CC7A7(int pram0)l
extern _native int unk_0x21C59F4C(int pram0)l
extern _native void remove_ambient_move_restriction_stay_outside_of_volume(int pram0)l
extern _native int does_ambient_spawn_restriction_volume_exist(int pram0)l
extern _native void remove_ambient_spawn_restriction_stay_outside_of_volume(int pram0)l
extern _native void ui_push(const char* pram0)l
extern _native void unk_0x5C94F6EC(int pram0, int pram1, int pram2, int pram3)l
extern _native void play_cutsceneobject(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void unk_0xDCC91F8C(int pram0, int pram1)l
extern _native void stop_vehicle(int pram0)l
extern _native int unk_0xA923A22D(int pram0, int pram1, int pram2, int pram3)l
extern _native int check_cutscene_collisions(int pram0)l
extern _native int get_camera_from_cutsceneobject(int pram0)l
extern _native int set_camera_lighting_scheme(int pram0, int pram1)l
extern _native void set_cutsceneobject_paused(int pram0, int pram1)l
extern _native int get_camerashot_from_cutsceneobject(int pram0, int pram1)l
extern _native void unk_0xDCD3A7DE(int pram0, int pram1)l
extern _native int cutsceneobject_add_transition_hold(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_camerashot_perspective(int pram0, int pram1)l
extern _native void set_camerashot_fov(int pram0, int pram1)l
extern _native void set_camerashot_near_clip_plane(int pram0, int pram1)l
extern _native void set_camerashot_collision_parameters(int pram0, int pram1, int pram2)l
extern _native void set_camerashot_collision_enabled(int pram0, int pram1)l
extern _native void set_camerashot_position(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_camerashot_orientation(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0x714D6F72(int pram0)l
extern _native void ui_clear_message_queue(int pram0)l
extern _native int abort_scripted_conversation(int pram0)l
extern _native void add_companion_permanent()l
extern _native void free_from_hogtie(int pram0)l
extern _native void task_override_set_posture(int pram0, int pram1)l
extern _native void set_actor_health(int pram0, int pram1)l
extern _native int is_player_deadeye(int pram0)l
extern _native void cancel_deadeye()l
extern _native void unk_0xAF50E8A1(int pram0)l
extern _native void unk_0x11A65FFB(int pram0)l
extern _native void unk_0x0F474297(int pram0)l
extern _native void unk_0x15001332()l
extern _native void unk_0xAF94B7D9()l
extern _native void clear_character_blood()l
extern _native void clear_tumbleweeds()l
extern _native int unk_0xD4048969(int pram0)l
extern _native void destroy_camera(int pram0)l
extern _native void unk_0xE6C1DBD9(int pram0)l
extern _native void show_physinst(int pram0)l
extern _native void unk_0xA5A6A3E3(int pram0, int pram1, int pram2)l
extern _native void audio_music_suspend(int pram0)l
extern _native void audio_music_release_control(int pram0, int pram1)l
extern _native int get_crime_position(int pram0, int pram1)l
extern _native void player_rumble(int pram0, int pram1, int pram2)l
extern _native int is_actor_crippled(int pram0, int pram1)l
extern _native void memory_prefer_walking(int pram0, int pram1)l
extern _native int get_actor_from_pers_char(int pram0)l
extern _native void reference_actor(int pram0)l
extern _native void set_pers_char_exempt_from_ambient_restrictions(int pram0, int pram1)l
extern _native void task_follow_object_at_distance(int pram0, int pram1, int pram2, int pram3)l
extern _native void task_go_near_coord(int pram0, int pram1, int pram2, int pram3)l
extern _native void task_vehicle_leave(int pram0)l
extern _native void task_search(int pram0, int pram1, int pram2)l
extern _native int create_nav_query(int pram0, int pram1)l
extern _native void nav_query_start_can_path_to_point(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int nav_query_is_done(int pram0)l
extern _native int nav_query_can_path_to_point(int pram0)l
extern _native int unk_0xBCC98808(int pram0)l
extern _native void unk_0x3ECD8FEE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x9613C2D0(int pram0)l
extern _native int find_nearest_door(int pram0, int pram1)l
extern _native int is_player_in_combat(int pram0)l
extern _native int is_actor_male(int pram0)l
extern _native void unk_0x91DE3A31(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int get_crime_victim(int pram0)l
extern _native void unk_0xAF6A3160(int pram0, int pram1)l
extern _native int actor_holster_weapon(int pram0, int pram1)l
extern _native int is_actor_ragdoll(int pram0)l
extern _native void teleport_actor(Actor Actor, vector3* Position, bool Unk1, bool _Unk1, bool __Unk1)l
extern _native void dereference_actor(int pram0)l
extern _native void nav_query_stop(int pram0)l
extern _native void ai_actor_set_match_walk_speed_enabled(int pram0, int pram1)l
extern _native void ai_combat_set_new_state_machine_enabled(int pram0, int pram1)l
extern _native int unk_0x35B5587D(int pram0)l
extern _native int gringo_update_bool(int pram0, int pram1, int pram2, int pram3)l
extern _native int get_crime_objectset(int pram0)l
extern _native int unk_0xD96DBABD(int pram0)l
extern _native void set_actor_heading(Actor Actor, float Heading, bool Unk1)l
extern _native int get_actor_faction(int pram0)l
extern _native void set_mover_frozen(int pram0, int pram1)l
extern _native int is_mover_frozen(int pram0)l
extern _native int get_crime_counter(int pram0)l
extern _native void task_override_clear_movetype(int pram0)l
extern _native int can_anyone_of_faction_see_object(int pram0, int pram1)l
extern _native int unk_0xA2DA4D24(int pram0)l
extern _native void iterate_in_volume(int pram0, int pram1)l
extern _native int is_faction_valid(int pram0)l
extern _native int ai_get_task_retreat_flag(int pram0)l
extern _native int get_actor_vehicle_state(int pram0, int pram1, int pram2)l
extern _native int cutsceneobject_add_transition_ease_in_out(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void unk_0x3DEB0933(int pram0, int pram1)l
extern _native void set_camerashot_far_clip_plane(int pram0, int pram1)l
extern _native void reset_camerashot_targetdof(int pram0)l
extern _native void unk_0x8BCB6B86(int pram0, int pram1)l
extern _native int get_pers_char_death_timestamp(int pram0)l
extern _native void unk_0x19C3CF93(int pram0)l
extern _native void unk_0x4C28B11E(int pram0, int pram1, int pram2)l
extern _native void init_camera_from_game_camera(int pram0)l
extern _native void set_camera_target_position(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_camera_fov(int pram0, int pram1)l
extern _native int squad_goal_add_general_task(int pram0, int pram1, int pram2, int pram3)l
extern _native void task_use_lasso(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ai_set_nav_actor_width(int pram0, int pram1)l
extern _native void memory_consider_as_enemy(int pram0, int pram1)l
extern _native void task_go_to_coord(int pram0, int pram1, int pram2)l
extern _native void task_follow_object(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void task_shoot_at_coord(int pram0, int pram1, int pram2)l
extern _native int unk_0x5402321A()l
extern _native int create_fire_in_volume(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void task_follow_actor(int pram0, int pram1)l
extern _native int is_actor_mounted(int pram0)l
extern _native void task_dismount(int pram0, int pram1)l
extern _native int find_intersection(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void task_shoot_at_coord_from_position(int pram0, int pram1, int pram2, int pram3)l
extern _native int is_actor_reloading(int pram0)l
extern _native void task_seek_cover_from_actor(int pram0, int pram1)l
extern _native void task_dive(int pram0, int pram1)l
extern _native void ambient_set_search_center_actor(int pram0)l
extern _native int memory_get_is_identified(int pram0, int pram1)l
extern _native int unk_0x69DA275F(int pram0)l
extern _native int revive_pers_char(int pram0, int pram1)l
extern _native int create_pers_char_in_layout(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0x80FB8BDE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int gringo_update_struct(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int get_blip_icon(int pram0)l
extern _native void unk_0xABD125F6(int pram0, int pram1)l
extern _native void unk_0xFBA76D7E(int pram0, int pram1)l
extern _native void set_blip_flag(int pram0, int pram1, int pram2)l
extern _native int unk_0xE78A0469(int pram0)l
extern _native void unk_0x02755628(int pram0, int pram1)l
extern _native void unk_0x5EA2E02D(int pram0)l
extern _native int unk_0xD76F1E9A(int pram0)l
extern _native void set_blip_impairment_mask(int pram0, int pram1)l
extern _native void task_draw_holster_weapon(int pram0, int pram1)l
extern _native void memory_attack_on_sight(int pram0, int pram1)l
extern _native void set_actor_faction(int pram0, int pram1)l
extern _native void unk_0x0B5E1904(int pram0, int pram1)l
extern _native int actor_reset_anims(int pram0, int pram1)l
extern _native void play_sound_frontend(const char* SoundName)l
extern _native void set_actor_can_bump(int pram0, int pram1)l
extern _native void unk_0xC52B5F18(int pram0, int pram1)l
extern _native void unk_0xEB7B0FAA(int pram0, int pram1)l
extern _native void print_big_format(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int unk_0xCE210220(int pram0, int pram1, int pram2)l
extern _native int get_object_heading(int pram0)l
extern _native int is_action_node_playing(int pram0, int pram1)l
extern _native int attach_slot_from_string(int pram0)l
extern _native int attach_prop_to_anim(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void add_ambient_move_restriction_stay_outside_of_volume(int pram0)l
extern _native void add_ambient_spawn_restriction_stay_outside_of_volume(int pram0)l
extern _native void unk_0xC9365FBC(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int cutsceneobject_add_transition_indefinite(int pram0, int pram1, int pram2)l
extern _native void reset_camerashot_target(int pram0, int pram1)l
extern _native void toggle_actor_action_signal_on(int pram0, int pram1, int pram2)l
extern _native int is_actor_in_hogtie(int pram0)l
extern _native void unk_0x33CE49C9()l
extern _native void toggle_actor_action_signal_off(int pram0)l
extern _native void destroy_population_set(int pram0)l
extern _native void unk_0x95D0FC79(int pram0)l
extern _native int is_actor_horse(int pram0)l
extern _native int set_actor_vision_xray(int pram0, int pram1)l
extern _native void task_flee_actorset(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void set_blip_pos(int pram0, int pram1)l
extern _native int unk_0x55DAC120(int pram0)l
extern _native void unk_0xBE39208A(int pram0, int pram1, int pram2)l
extern _native void task_override_set_movetype(int pram0, int pram1)l
extern _native void unk_0xCA950EF0(int pram0)l
extern _native void task_go_to_coord_nonstop(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x435A982F(int pram0, int pram1)l
extern _native int unk_0x4DD06256(int pram0, int pram1, int pram2, int pram3)l
extern _native int squad_goal_add_stay_within_volume(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void task_go_near_actor(int pram0, int pram1, int pram2, int pram3)l
extern _native void task_search_for_object(int pram0, int pram1, int pram2, int pram3)l
extern _native int squad_goal_link_modifier_to_other_goal(int pram0, int pram1, int pram2)l
extern _native void task_go_to_coord_and_stay(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x817AC6D6(int pram0, int pram1, int pram2)l
extern _native int squad_goal_add_meet_at_position(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int set_linked_anim_target(int pram0, int pram1)l
extern _native void task_action_perform(int pram0, int pram1)l
extern _native void audio_stop_pain(int pram0)l
extern _native void unk_0x12D077CA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void unk_0x31A55281(int pram0)l
extern _native void unk_0x651C1FC2(int pram0)l
extern _native void ui_set_style(int pram0, int pram1)l
extern _native int unk_0xB7CE8FCC(int pram0, int pram1, int pram2)l
extern _native int unk_0x430207A4(int pram0)l
extern _native int unk_0x55842354(int pram0)l
extern _native int unk_0x91C6AC0E(int pram0, int pram1, int pram2)l
extern _native int add_formation_location(int pram0, int pram1)l
extern _native int is_slot_valid(int SlotID)l
extern _native void memory_report_position(int pram0, int pram1, int pram2)l
extern _native int get_lasso_target(int pram0)l
extern _native int unk_0xEB40C2FC(int pram0)l
extern _native int unk_0x69FA5315(int pram0)l
extern _native int memory_get_position_last_known_time(int pram0, int pram1)l
extern _native void ai_clear_nav_material_usage(int pram0)l
extern _native int unk_0x7A207FFE(int pram0)l
extern _native void ai_clear_fire_delay(int pram0)l
extern _native void ai_clear_fire_delay_randomness(int pram0)l
extern _native void ai_clear_burst_duration(int pram0)l
extern _native void ai_clear_burst_duration_randomness(int pram0)l
extern _native void ai_clear_shots_per_burst(int pram0)l
extern _native void combat_class_ai_set_range_between_bursts_delay(int pram0, int pram1, int pram2)l
extern _native Object unk_0x184BD1BC(Object pram0)l
extern _native int unk_0xE2ED95CC(int pram0)l
extern _native int unk_0x2ECF04F3(int pram0, int pram1)l
extern _native void unk_0x52B2F3F0(int pram0)l
extern _native int is_actor_performing_linked_animation(int pram0)l
extern _native int unk_0xBEC2871A(int pram0)l
extern _native int unk_0xEF4F4F20(int pram0)l
extern _native int get_actor_vision_xray(int pram0)l
extern _native int timestep()l
extern _native int is_player_using_cover(int pram0)l
extern _native int unk_0x5B792331(int pram0, int pram1)l
extern _native int unk_0xF6BF4242(int pram0)l
extern _native int is_actor_drunk(int pram0)l
extern _native int unk_0x30C4CA99(int pram0)l
extern _native int get_lasso_user(int pram0)l
extern _native void unk_0xA6D794FE(int pram0, int pram1)l
extern _native void unk_0xC09B114B(int pram0, int pram1)l
extern _native void ai_behavior_set_allow(int pram0, int pram1, int pram2)l
extern _native void set_tough_actor(int pram0, int pram1)l
extern _native void ai_set_range_accuracy_modifier(int pram0, int pram1, int pram2)l
extern _native int set_actor_vision_max_range(int pram0, int pram1, int pram2)l
extern _native int set_actor_vision_field_of_view(int pram0, int pram1)l
extern _native void memory_prefer_melee(int pram0, int pram1)l
extern _native void ai_set_shots_per_burst(int pram0, int pram1)l
extern _native void ai_set_burst_duration(int pram0, int pram1)l
extern _native void ai_set_burst_duration_randomness(int pram0, int pram1)l
extern _native void ai_set_fire_delay(int pram0, int pram1)l
extern _native void ai_set_fire_delay_randomness(int pram0, int pram1)l
extern _native void actor_enable_variable_mesh(int pram0, int pram1, int pram2)l
extern _native void combat_class_ai_clear_all_attribs(int pram0)l
extern _native void combat_class_ai_set_fight_attack_distance(int pram0, int pram1, int pram2)l
extern _native void combat_class_ai_set_fight_desired_distance(int pram0, int pram1, int pram2)l
extern _native void combat_class_ai_set_fight_time_between_attacks(int pram0, int pram1)l
extern _native void combat_class_ai_set_range_accuracy(int pram0, int pram1)l
extern _native void tough_armour_set_tuning_regeneration_rate(int pram0, int pram1)l
extern _native void tough_armour_set_tuning_pad_armour(int pram0, int pram1)l
extern _native void ai_perception_set_visual_id_distance(int pram0, int pram1)l
extern _native void ai_perception_set_visual_id_time(int pram0, int pram1)l
extern _native void tough_armour_set_tuning_hit_deduction(int pram0, int pram1, int pram2)l
extern _native int is_actor_player(int pram0)l
extern _native void ai_predicate_override_clear_all(int pram0)l
extern _native void ai_predicate_override_set_bool(int pram0, int pram1, int pram2)l
extern _native void squad_set_not_eliminated_impairment_mask(int pram0, int pram1)l
extern _native void squad_set_faction(int pram0, int pram1)l
extern _native int net_is_object_local(int pram0)l
extern _native int unk_0x2B8C3258(int pram0)l
extern _native int get_local_slot()l
extern _native int unk_0xA2866F3B(int pram0)l
extern _native int unk_0xADB08F12(int pram0)l
extern _native int unk_0xB4D1D8A3(int pram0, int pram1)l
extern _native int get_curve_name(int pram0)l
extern _native void unk_0x7B07D449()l
extern _native int unk_0x0B40BBE3(int pram0, int pram1, int pram2)l
extern _native int get_slot_actor(int pram0)l
extern _native int unk_0x579C2014(int pram0)l
extern _native void unk_0xA6403262(int pram0, int pram1)l
extern _native void ui_enter(const char* uiLayer)l
extern _native void task_shoot_from_position(int pram0, int pram1, int pram2)l
extern _native void unk_0xEF270DC9()l
extern _native void unk_0xD1628C57()l
extern _native void unk_0xF7696B8B(int pram0, int pram1)l
extern _native int unk_0xE094DB31(int pram0, int pram1)l
extern _native void unk_0xBB77E597(int pram0, int pram1)l
extern _native void unk_0xF349D0B6(int pram0, int pram1)l
extern _native void close_door_fast(int pram0)l
extern _native void actor_disable_weapon_render(int pram0, int pram1, int pram2)l
extern _native void set_pers_char_enabled(int pram0, int pram1)l
extern _native void set_day(int pram0)l
extern _native void teleport_actor_with_heading(Actor Actor, vector3 Position, float Heading, bool Unk1, bool _Unk1, bool __Unk1)l
extern _native int set_object_orientation(int pram0, int pram1, int pram2, int pram3)l
extern _native void open_door_fast(int pram0, int pram1)l
extern _native int unk_0x76FBF412()l
extern _native void unk_0x6ADAAD87(int pram0, int pram1, int pram2)l
extern _native void unk_0xB3E331AC()l
extern _native void unk_0xB09D5B43()l
extern _native void unk_0x9028B082()l
extern _native void clear_decals()l
extern _native void unk_0x2CB5D7AF()l
extern _native int is_actorset_valid(int pram0)l
extern _native int get_actorset_size(int pram0)l
extern _native int unk_0xC5202810(int pram0, int pram1)l
extern _native int get_slot_position(int pram0, int pram1)l
extern _native int vdist2(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0xEE4E2461(int pram0)l
extern _native void unk_0xAA24E0CC(int pram0)l
extern _native void unk_0xDE9AA6E5(int pram0)l
extern _native int unk_0x54F8EAA4(int pram0)l
extern _native void unk_0x0D8BA78E(int pram0, int pram1)l
extern _native int unk_0x0B5431C9(int pram0)l
extern _native int is_actor_in_actorset(int pram0, int pram1)l
extern _native int add_actorset_member(int pram0, int pram1)l
extern _native int is_actor_rideable(int pram0)l
extern _native int new_scripted_conversation()l
extern _native void add_line_to_conversation(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void add_new_frontend_conversation_speaker(int pram0, int pram1)l
extern _native void start_script_conversation(int pram0, int pram1)l
extern _native int unk_0x5E985228(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void print_big(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xE2163ECC(int pram0, int pram1)l
extern _native int unk_0x4957E482(int pram0, int pram1)l
extern _native int unk_0xB13DD691(int pram0, int pram1, int pram2)l
extern _native int unk_0x009DFC82(int pram0, int pram1, int pram2)l
extern _native int unk_0x9253CC79(int pram0, int pram1)l
extern _native void unk_0xC73DAD2B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void is_horses_relative(int pram0, int pram1)l
extern _native void unk_0x1082715D()l
extern _native int unk_0x6226328F()l
extern _native void unk_0x59F98CA9(int pram0)l
extern _native void set_debug_draw(int pram0)l
extern _native int unk_0x943BE053(int pram0)l
extern _native int unk_0x2DB3AC0F(int pram0, int pram1)l
extern _native void streaming_load_bounds(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0x2CCEA76C(int pram0)l
extern _native void unk_0xE9C41DFE(int pram0)l
extern _native void reset_factions()l
extern _native void hud_counter_display(int pram0)l
extern _native void hud_timer_display(int pram0)l
extern _native void set_actor_min_speed(int pram0, int pram1)l
extern _native void set_actor_rideable(Actor Actor, bool Rideable)l
extern _native void task_follow_path(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void task_sequence_perform_repeatedly(int pram0, int pram1, int pram2)l
extern _native void animal_actor_set_domestication(Actor Actor, bool Domestication)l
extern _native void animal_tuning_set_attrib_bool(int pram0, int pram1, int pram2)l
extern _native int unk_0x9A4CD54B(int pram0)l
extern _native void audio_music_set_mood(const char* Mood, int pram1, int pram2, int pram3)l
extern _native int is_weapon_drawn(int pram0)l
extern _native int unk_0x09950C1B(int pram0, int pram1)l
extern _native void open_door_direction(int pram0, int pram1)l
extern _native int is_camera_active_on_channel(int pram0, int pram1)l
extern _native void task_face_coord(int pram0, int pram1, int pram2)l
extern _native int is_scripted_speech_playing(int pram0)l
extern _native int gateway_get_actor(int pram0)l
extern _native void simulate_player_input_gait(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xB89CC342(int pram0, int pram1, int pram2)l
extern _native int unk_0x4251BF6C(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int is_ai_actor_in_combat(int pram0)l
extern _native int unk_0x07B7AA6B(int pram0)l
extern _native int is_world_sector_loaded(int pram0)l
extern _native int unk_0xA5F229C9(int pram0, int pram1, int pram2)l
extern _native int get_door_from_object(int pram0)l
extern _native int unk_0xB6709FF4(int pram0, int pram1, int pram2)l
extern _native int unk_0x5831679F()l
extern _native void streaming_evict_all()l
extern _native void unk_0xF1607937(int pram0, int pram1)l
extern _native void set_actor_max_health(int pram0, int pram1)l
extern _native void set_allow_ride_by_player(Actor Actor, bool Ride)l
extern _native void unk_0x135EA21D(int pram0)l
extern _native void set_npc_to_actor_damage_scale_factor(int pram0, int pram1)l
extern _native void set_player_cause_weapon_reaction_combat(int pram0, int pram1)l
extern _native void deactivate_actors_for_pers_chars_in_volume(int pram0)l
extern _native void task_go_to_object(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x76876FEA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void set_camera_focus_prompt_enabled(int pram0, int pram1)l
extern _native void task_override_set_movespeed_absolute(int pram0, int pram1)l
extern _native void unk_0x7EDD316C(int pram0)l
extern _native int get_actors_horse(int pram0)l
extern _native void add_cameratransition_event_gamecamerareset(int pram0, int pram1, int pram2, int pram3)l
extern _native void play_sound_from_position(const char* SoundName, vector3 Position)l
extern _native void audio_play_vocal_effect(int pram0, int pram1, int pram2)l
extern _native int play_sound_from_actor(int pram0, int pram1, int pram2)l
extern _native void open_door_direction_fast(int pram0, int pram1)l
extern _native int get_object_axis(int pram0, int pram1, int pram2)l
extern _native int unk_0x9BCC06E2(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12, int pram13, int pram14)l
extern _native int unk_0x82A73B3D(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void task_animal_circle_aggressively(int pram0, int pram1)l
extern _native int unk_0x951B8DF7(int pram0, int pram1)l
extern _native int is_player_targetting_actor(int pram0, int pram1, int pram2)l
extern _native void task_flee_coord(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x98790639(int pram0)l
extern _native void task_crouch(int pram0, int pram1)l
extern _native int unk_0xEDA897FA(int pram0)l
extern _native void memory_consider_according_to_faction(int pram0, int pram1)l
extern _native int destroy_actorset(int pram0)l
extern _native void unk_0x1BED8493(int pram0, int pram1, int pram2)l
extern _native void set_actor_weapon_reaction_actor_type(int pram0, int pram1)l
extern _native void unk_0x4EEC6628(int pram0, int pram1)l
extern _native void unk_0x3A2D7759(int pram0, int pram1)l
extern _native void clear_last_hit(int pram0)l
extern _native int unk_0x08308EBA(int pram0)l
extern _native void clear_last_attack(int pram0)l
extern _native void set_allow_execute(int pram0, int pram1)l
extern _native void set_allow_cold_weather_breath(int pram0, int pram1)l
extern _native void animal_tuning_set_attrib_float(int pram0, int pram1, int pram2)l
extern _native void unk_0x900165CE(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0x63925367(int pram0, int pram1)l
extern _native void set_cripple_enable(int pram0, int pram1)l
extern _native int get_object_named_bone_position(int pram0, int pram1, int pram2)l
extern _native void task_go_to_coord_precisely(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void set_actor_drunk(int pram0, int pram1)l
extern _native int unk_0xA36ED4A6(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void make_next_rand_actorenums_unique(int pram0)l
extern _native void ai_set_nav_actor_avoidance_mode(int pram0, int pram1)l
extern _native int unk_0x4634B6BE(int pram0, int pram1, int pram2)l
extern _native void stop_sound(int pram0)l
extern _native void unk_0x44986367(int pram0, int pram1)l
extern _native void task_taunt_actor_in_place(int pram0, int pram1, int pram2)l
extern _native int unk_0x50AE988A(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x90AD2C2D(int pram0)l
extern _native void task_hide_at_cover(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int remove_actorset_member(int pram0, int pram1)l
extern _native void unk_0x6118212B(int pram0, int pram1, int pram2)l
extern _native void unk_0xF9C5DC76(int pram0, int pram1)l
extern _native bool is_button_down(Controller Controller, eButton Button, int Unk1, int Unk0)l
extern _native void feed_code_warp_dist(int pram0)l
extern _native void unk_0xD4FECCBC(int pram0)l
extern _native void clear_actors_horse(int pram0)l
extern _native void unk_0x96AC812B(int pram0)l
extern _native int is_actor_mule(int pram0)l
extern _native void set_actors_horse(int pram0, int pram1)l
extern _native void unk_0x327E4426(int pram0, int pram1)l
extern _native void unk_0x57055A7D(int pram0, int pram1)l
extern _native void unk_0x5CC16A49(int pram0, int pram1)l
extern _native void unk_0x6400E005(int pram0, int pram1)l
extern _native int find_traffic_path(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void get_curve_point(int pram0, int pram1, int pram2, int pram3)l
extern _native int pow(int pram0, int pram1)l
extern _native int unk_0x39DA0B3A(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xF48F8F09(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int unk_0xAE168124()l
extern _native void set_actor_move_conflict_allowed_to_run_over_small_animals(int pram0, int pram1)l
extern _native void set_actor_move_conflict_high_priority(int pram0, int pram1)l
extern _native void unk_0x9F1F8669(int pram0)l
extern _native void force_vehicle_cinematic_camera(int pram0)l
extern _native void unk_0x2692B771(int pram0)l
extern _native int unk_0x71A3F193(int pram0)l
extern _native int unk_0xFB252BA9(int pram0)l
extern _native void ai_set_nav_actor_avoidance_allow_turns(int pram0, int pram1)l
extern _native int unk_0x49D2C1DA(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xC6AF3662(int pram0, int pram1)l
extern _native void unk_0x4F8FAF8F(int pram0, int pram1)l
extern _native void unk_0x04D89A35(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int get_curve_type(int pram0)l
extern _native int unk_0xFAD7A113(int pram0)l
extern _native int squad_goal_add_follow_traffic_curve(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void squad_follow_traffic_curve_set_behavior_flag(int pram0, int pram1, int pram2, int pram3)l
extern _native void squad_follow_traffic_curve_set_task_priority(int pram0, int pram1, int pram2)l
extern _native int unk_0xA4BC2A1B(int pram0, int pram1, int pram2)l
extern _native int squad_follow_traffic_curve_is_curve_already_in_list(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void squad_follow_traffic_curve_enqueue_curve(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x8C221B4D(int pram0)l
extern _native int ai_get_is_retreating(int pram0)l
extern _native void pause_game(int pram0)l
extern _native void unpause_game()l
extern _native void remove_object_attachment(int pram0)l
extern _native void dereference_object(int pram0)l
extern _native int disband_actorset(int pram0)l
extern _native int unk_0x0F701FF7(int pram0, int pram1, int pram2, int pram3)l
extern _native int is_gringo_ready(int pram0)l
extern _native void unk_0xF635B9EA(int pram0)l
extern _native void clear_actor_min_speed(int pram0)l
extern _native void ai_set_nav_pathfinding_enabled(int pram0, int pram1)l
extern _native int is_cutsceneobject_paused(int pram0)l
extern _native void actor_dismount_now(int pram0)l
extern _native int unk_0x3C45D66A(int pram0, int pram1, int pram2)l
extern _native void unk_0x67FC68DB(int pram0)l
extern _native void delete_accessory(int pram0, int pram1)l
extern _native void unk_0x2E84E682(int pram0, int pram1)l
extern _native void ai_goal_aim_at_object(int pram0, int pram1, int pram2)l
extern _native void open_door(int pram0, int pram1, int pram2)l
extern _native int clear_linked_anim_target(int pram0)l
extern _native void set_cripple_flag(int pram0, int pram1)l
extern _native int get_most_recent_mount(int pram0)l
extern _native int get_y(int pram0)l
extern _native int unk_0xD14515A3(int pram0, int pram1)l
extern _native void task_vehicle_enter(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_vehicle_allowed_to_drive(Actor Vehicle, bool Allowed)l
extern _native bool set_actor_in_vehicle(Actor Source, Actor Destination, int SeatID)l
extern _native void set_actor_auto_transition_to_driver_seat(int pram0, int pram1)l
extern _native void reference_object(int pram0)l
extern _native int cutsceneobject_add_transition_decorator(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int attach_camerashot(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void set_camerashot_target_object(int pram0, int pram1, int pram2)l
extern _native void set_camerashot_target_object_offsets(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void set_camerashot_target_object_roll(int pram0, int pram1)l
extern _native int ai_is_aggroing(int pram0, int pram1)l
extern _native void detach_lasso(int pram0)l
extern _native int unk_0xAF2597E8(int pram0)l
extern _native int unk_0x16EB367C(int pram0)l
extern _native int find_water_intersection(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void add_actor_stay_outside_of_volume(int pram0, int pram1)l
extern _native int unk_0x9265B24B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void task_follow_and_attack_object(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void task_shoot_enemies_from_any_cover(int pram0, int pram1)l
extern _native int get_actor_vision_max_range(int pram0)l
extern _native int memory_get_was_visible_within_time(int pram0, int pram1, int pram2)l
extern _native int create_obstacle_in_layout(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native int combat_class_ai_get_range_accuracy(int pram0)l
extern _native void add_actor_stay_within_volume(int pram0, int pram1)l
extern _native void set_actor_volume_parameters(int pram0, int pram1, int pram2)l
extern _native void set_camera_aspect_ratio(int pram0, int pram1)l
extern _native void set_camera_near_clip_plane(int pram0, int pram1)l
extern _native void set_camera_far_clip_plane(int pram0, int pram1)l
extern _native void set_camera_collision_parameters(int pram0, int pram1, int pram2)l
extern _native void set_camera_collision_enabled(int pram0, int pram1)l
extern _native void reset_camera_target(int pram0, int pram1)l
extern _native void reset_camera_targetdof(int pram0)l
extern _native int gringo_deactivate(int pram0)l
extern _native int memory_get_must_identify(int pram0, int pram1)l
extern _native int is_camera_focus_enabled(int pram0)l
extern _native void set_camera_focus_enabled(int pram0, int pram1)l
extern _native int is_camera_focus_active(int pram0)l
extern _native void ai_predicate_override_clear(int pram0, int pram1)l
extern _native int is_script_use_context_pressed(int pram0)l
extern _native int unk_0x211DE185(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void unk_0x6077F3AE(int pram0, int pram1)l
extern _native int unk_0x52261CE0(int pram0)l
extern _native void set_actor_stay_outside_of_volume(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_camera_focus_player_invulnerable(int pram0, int pram1)l
extern _native void set_camera_focus_player_input_disabled(int pram0, int pram1)l
extern _native int set_prop_ai_obstacle_enabled(int pram0, int pram1)l
extern _native void unk_0x547166A7(int pram0)l
extern _native void fire_release_handle(int pram0, int pram1)l
extern _native void unk_0x983ED842(int pram0)l
extern _native void unk_0x902781BF(int pram0, int pram1)l
extern _native int unk_0x965A4652(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int create_corpse_in_layout_random(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void create_decal(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void unk_0x0E41A6AC(int pram0)l
extern _native int fire_create_handle()l
extern _native int unk_0xB65ADFAC(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x3D5D3B26(int pram0, int pram1)l
extern _native int unk_0xF1F8AFCA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int is_scripted_conversation_ongoing()l
extern _native int get_journal_entry(int pram0)l
extern _native void clear_journal_entry_detail_list(int pram0, int pram1)l
extern _native void add_new_conversation_speaker(int pram0, int pram1, int pram2)l
extern _native int squad_goal_add_battle_allies(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x74CA8E22(int pram0)l
extern _native void unk_0x80317230(int pram0, int pram1, int pram2)l
extern _native int unk_0x35C8FD4A(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x211DD9D2(int pram0)l
extern _native int unk_0x2CF0010F(int pram0)l
extern _native void set_actor_proof(int pram0, int pram1)l
extern _native void unk_0x76A72D9A(int pram0, int pram1)l
extern _native int create_cover_location_in_layout(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void ai_speech_set_allow_context_for_actor(int pram0, int pram1, int pram2)l
extern _native int unk_0xD4FBCCE0(int pram0)l
extern _native int sc_challenge_launch(int pram0)l
extern _native void task_shoot_enemies_from_cover(int pram0, int pram1, int pram2, int pram3)l
extern _native void task_go_near_object(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void attach_player_to_cover(int pram0, int pram1, int pram2)l
extern _native void actor_pop_next_gait(int pram0, int pram1, int pram2)l
extern _native void unk_0x6C194C1F(int pram0)l
extern _native void hud_timer_countdown(int pram0)l
extern _native void set_actor_face_style(int pram0, int pram1)l
extern _native void task_vehicle_enter_specific_location(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xB6E791F6(int pram0, int pram1)l
extern _native int get_vehicle_bump_count(int pram0)l
extern _native void unk_0x0E9BA223(int pram0)l
extern _native void ui_set_text(char* entry, char* text)l
extern _native void unk_0xE5D53722(int pram0, int pram1)l
extern _native void set_transition_collision_params(int pram0, int pram1, int pram2)l
extern _native void unk_0xF76F2BB3(int pram0, int pram1, int pram2, int pram3)l
extern _native void add_camerashot_collision_exclusion(int pram0, int pram1, int pram2)l
extern _native void ai_disable_perception(int pram0)l
extern _native void ai_enable_perception(int pram0)l
extern _native void task_shoot_enemies_from_position(int pram0, int pram1, int pram2, int pram3)l
extern _native int set_actor_anim_current_time(int pram0, int pram1)l
extern _native void set_allow_deadeye_locks(int pram0, int pram1)l
extern _native void unk_0xAC8D3A0C(int pram0, int pram1)l
extern _native void set_deadeye_locks_on_head_only(int pram0, int pram1)l
extern _native32(0x358F874F) bool _is_key_down(int keyCode)l
extern _native int unk_0x5E339E16(int pram0)l
extern _native int attach_objects_continuous(int pram0, int pram1, int pram2)l
extern _native void task_override_clear_posture(int pram0)l
extern _native int unk_0x0208A8E0(int pram0, int pram1)l
extern _native void unk_0x77402033(int pram0)l
extern _native void ai_reset_firing_fsm(int pram0)l
extern _native void stop_ped_speaking(int pram0, int pram1)l
extern _native int unk_0x77964B0C(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native bool is_actor_drafted(int actor)l
extern _native void set_actor_posture(int pram0, int pram1)l
extern _native bool is_actor_local_player(int actor)l
extern _native int unk_0x8A0D25F2(int pram0, int pram1)l
extern _native void ai_goal_look_at_coord(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int leash_constrain(int pram0)l
extern _native int leash_restart(int pram0)l
extern _native int unk_0x7F190CA3(int pram0, int pram1)l
extern _native int unk_0x14BEC6F5(int pram0, int pram1)l
extern _native int leash_break(int pram0, int pram1)l
extern _native void task_taunt_actor(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0xAFC96669(int pram0)l
extern _native void nav_query_receive_can_path_to_point(int pram0, int pram1)l
extern _native int unk_0x734CC17B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int leash_is_broken(int pram0)l
extern _native int leash_release_constraint(int pram0)l
extern _native void set_actor_hanging_from_noose(int pram0, int pram1)l
extern _native void remove_actor_stay_within_volume(int pram0, int pram1)l
extern _native int unk_0x5A72DD49(int pram0, int pram1)l
extern _native int leash_attach_to_world(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void unk_0x65DAA654(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x4B67B8BB(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11)l
extern _native void unk_0x1CD960B8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ui_refresh(const char* pram0)l
extern _native void unk_0x6B5DF46D(int pram0, int pram1)l
extern _native int gringo_get_target(int pram0)l
extern _native int unk_0x1FCC8FEF(int pram0)l
extern _native int unk_0x48588CCB(int pram0, int pram1, int pram2, int pram3)l
extern _native void squad_flock_add_external_alert(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void squad_flock_add_external_repulsion(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void squad_flock_player_proximity_boost_set_enabled(int pram0, int pram1, int pram2)l
extern _native int unk_0x66A8AF91(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void unk_0x731F2C21(int pram0)l
extern _native void unk_0xA90A13A5(int pram0, int pram1)l
extern _native void unk_0x7A759A53(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_actor_passed_out(int pram0, int pram1)l
extern _native void fire_projectile(Actor Actor, const char* WeapGroup, float pram2, vector3* Origin, vector3* Target)l
extern _native int animal_species_rel_get_can_attack(int pram0, int pram1)l
extern _native int get_actor_max_speed_absolute(int pram0)l
extern _native void ai_actor_force_speed(int pram0, int pram1)l
extern _native void set_actor_max_speed_absolute(int pram0, int pram1)l
extern _native int is_actor_on_ground(int actor)l
extern _native bool get_actor_most_recent_vehicle(int pram0)l
extern _native int get_actor_hogtie_state(int actor)l
extern _native int unk_0xF7400A47(int pram0, int pram1)l
extern _native void unk_0xBFC8EF7C(int pram0, int pram1)l
extern _native int unk_0xD02757C1(int pram0, int pram1)l
extern _native void unk_0x0871084C(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int unk_0xF0354E46(int pram0)l
extern _native void create_direction_decal(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void activate_physinst(int pram0)l
extern _native void ai_global_set_permanent_danger(int pram0, int pram1)l
extern _native void remove_actor_stay_outside_of_volume(int pram0, int pram1)l
extern _native void task_surround_actor(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ai_goal_aim_clear(int pram0)l
extern _native void memory_clear_weapon_draw_preference(int pram0)l
extern _native void ai_set_weapon_min_range(int pram0, int pram1)l
extern _native void ai_goal_shoot_clear(int pram0)l
extern _native void actor_force_weapon_render(int pram0, int pram1, int pram2)l
extern _native void ai_set_weapon_max_range(int pram0, int pram1)l
extern _native int hud_timer_get()l
extern _native int unk_0xAAC96EFF(int pram0, int pram1)l
extern _native void task_bird_soar_at_coord(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_actor_unkillable(int pram0, int pram1)l
extern _native void unk_0xF1A53C41(int pram0, int pram1, int pram2, int pram3)l
extern _native int leash_attach_to_object(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void unk_0x88943B5B(int pram0, int pram1)l
extern _native int unk_0x941FC468(int pram0)l
extern _native void get_gringo_activation_sphere(int pram0, int pram1, int pram2)l
extern _native int unk_0x8EB0B2AD()l
extern _native void set_camera_target_object(int pram0, int pram1, int pram2)l
extern _native int unk_0xBFD6AE3D(int pram0)l
extern _native int gringo_query_prop(int pram0, int pram1)l
extern _native int attach_objects_using_locator(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int get_prop_velocity(int pram0, int pram1)l
extern _native int unk_0x945F518F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void unk_0x338F85D9(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0xFF642652(int pram0)l
extern _native int unk_0xE27EBCBD(int pram0)l
extern _native int is_actor_playing_node_in_tree(int pram0, int pram1)l
extern _native int unk_0x80B8A1BE(int pram0, int pram1, int pram2)l
extern _native int unk_0xECC40138(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x43E2808B(int pram0)l
extern _native void unk_0x527CB774(int pram0, int pram1)l
extern _native int unk_0x0733E811(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int is_area_obstructed(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void unk_0x561C9A6D(int pram0)l
extern _native void unk_0x528C7F3D(int pram0)l
extern _native void unk_0xE9E8C31A(int pram0)l
extern _native void set_actor_action_signal(int pram0, int pram1, int pram2)l
extern _native void unk_0x5685A440(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void unk_0x761BA4BD(int pram0, int pram1)l
extern _native int unk_0x92FE8D74(int pram0, int pram1)l
extern _native int unk_0x08FD1D81(int pram0)l
extern _native void unk_0x3627F773(int pram0, int pram1)l
extern _native void ai_set_nav_failsafe_movement_enabled(int pram0, int pram1)l
extern _native void memory_clear_riding_preference(int pram0)l
extern _native void set_actor_is_companion(int pram0, int pram1)l
extern _native void set_actor_is_ambient(int pram0, int pram1)l
extern _native void unk_0xC28A5950(int pram0, int pram1)l
extern _native void set_allow_jack(int pram0, int pram1)l
extern _native void memory_should_always_pathfind_in_formation(int pram0, int pram1)l
extern _native void actor_draw_weapon(int pram0, int pram1, int pram2)l
extern _native int unk_0x8F8EDCCF(int pram0, int pram1, int pram2)l
extern _native int unk_0x6ADC74CE(int pram0, int pram1)l
extern _native void unk_0x8DFF31DF(int pram0, int pram1)l
extern _native int unk_0x620178B3(int pram0)l
extern _native void unk_0xB3E44649(int pram0)l
extern _native void toggle_coop_journal_ui(int pram0)l
extern _native void unk_0xE822010A(int pram0, int pram1)l
extern _native int unk_0x55C5BB93(int pram0)l
extern _native int unk_0xBFCF32D9(int pram0)l
extern _native int unk_0xE8FFE727(int pram0, int pram1, int pram2)l
extern _native void unk_0x57D9950B(int pram0)l
extern _native void unk_0xF4D0807E(int pram0, int pram1)l
extern _native void hud_set_fade_color(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x2148AC15(int pram0, int pram1)l
extern _native void stop_all_fires()l
extern _native void unk_0xA393AC4E(int pram0)l
extern _native int unk_0xFC52BD15(int pram0)l
extern _native void mission_audio_bank_no_longer_needed()l
extern _native void unk_0x87E40FB8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int get_cutsceneobject_sequence(int pram0)l
extern _native void end_current_transition_from_cutsceneobject(int pram0)l
extern _native void unk_0x2FB85996(int pram0)l
extern _native void unk_0xB226E8E3(int pram0)l
extern _native int get_camera_channel_direction(int pram0, int pram1)l
extern _native int cutsceneobject_add_transition_ease_in(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int cutsceneobject_add_transition_lerp(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void set_camerashot_target_position(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ui_restore(char* uiLayer)l
extern _native void unk_0x444C3C32(int pram0, int pram1, int pram2)l
extern _native void unregister_host_broadcast_variables()l
extern _native void unregister_client_broadcast_variables()l
extern _native void unk_0x4D0C8AA4(int pram0)l
extern _native void net_update_leaderboard(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x89277EA3()l
extern _native void unk_0x7154D15B()l
extern _native int unk_0xE5C5CE63()l
extern _native int unk_0xA684E813()l
extern _native void unk_0x88249424(int pram0, int pram1, int pram2)l
extern _native int unk_0x81F24788()l
extern _native int unk_0xA80C6DE6(int pram0)l
extern _native int get_time_acceleration()l
extern _native int get_num_players()l
extern _native int unk_0x49F96787()l
extern _native int net_get_net_time()l
extern _native void unk_0xB5DDEF68(int pram0, int pram1)l
extern _native void unk_0x7725001B(int pram0, int pram1, int pram2)l
extern _native void unk_0x437588E6(int pram0)l
extern _native void clear_actor_proof(int pram0, int pram1)l
extern _native int unk_0x6396ABB7(int pram0)l
extern _native void unk_0x7E0CDD87()l
extern _native void ui_focus(const char* uiLayer)l
extern _native int unk_0x8EFDFE89(int pram0)l
extern _native int unk_0x7609A328(int pram0)l
extern _native void unk_0x1105FB64(int pram0, int pram1)l
extern _native int unk_0x9D20BDC4(int pram0)l
extern _native int flash_get_int(const char* scaleformName, const char* scaleformVarName)l
extern _native void unk_0x8266C617(int pram0, int pram1, int pram2)l
extern _native int unk_0xAB2D8A68(int pram0, int pram1, int pram2)l
extern _native void unk_0x3E8E7D7B(int pram0)l
extern _native int unk_0x0B071844(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native32(0x637E446B) Actor _change_actor_model_in_layout(Layout Layout, Actor Actor, const char* ActorInLayout, eActor ActorID, vector3 Position, vector3 Rotation, int unk0)l
extern _native void unk_0x6F6D942B(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void set_ambient_voice_name(int pram0, int pram1)l
extern _native void unk_0xF2F77F44(int pram0, int pram1)l
extern _native void set_local_player_voice(int pram0)l
extern _native void set_local_player_pain_voice(int pram0)l
extern _native void unk_0x1E56BAFD(int pram0)l
extern _native void set_deadeye_invulnerability(int pram0, int pram1)l
extern _native void set_deadeye_damage_scaling(int UNK0, float Scaling)l
extern _native void set_deadeye_regeneration_rate(int pram0, int pram1, int pram2)l
extern _native void set_deadeye_timescale(int UNK0, float TimeScale)l
extern _native int decor_handles_relative(int pram0)l
extern _native void unk_0x9FC69F27(int pram0, int pram1)l
extern _native void detach_camerashot(int pram0)l
extern _native int get_actor_slot(int pram0)l
extern _native void get_camerashot_position(int pram0, int pram1)l
extern _native int unk_0x457A0510(int pram0, int pram1)l
extern _native void get_camerashot_direction(int pram0, int pram1)l
extern _native void set_camerashot_direction(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int get_camerashot_fov(int pram0)l
extern _native void init_camerashot_from_game_camera(int pram0)l
extern _native void streaming_enable_force_fragment_high_lod(int pram0)l
extern _native int cutsceneobject_add_transition_ease_out(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void add_camerashot_collision_boundflag(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_object(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_target_offset(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_focal_length(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_cutoff_distance(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_using_soft_dof(int pram0, int pram1, int pram2)l
extern _native void set_camerashot_targetdof_smoothing(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_filtertype(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_fstop(int pram0, int pram1)l
extern _native void camerashot_add_arc_behavior(int pram0, int pram1)l
extern _native void ui_set_string_format(const char* GXTName, const char* FormatString, const char* String1, const char* String2, const char* String3)l
extern _native int in_selected_pedpath(int pram0)l
extern _native int unk_0xF81E2097(int pram0, int pram1)l
extern _native int unk_0xA6AA7B9E(int pram0, int pram1)l
extern _native int unk_0xF83666A6()l
extern _native void unk_0xC78B7436()l
extern _native void unk_0x49053A94(int pram0, int pram1)l
extern _native void ui_unfocus(const char* uiLayer)l
extern _native int unk_0xBA89F5EA(int pram0)l
extern _native const char* get_slot_name(int SlotID)l
extern _native int unk_0xC0FC4B57()l
extern _native int net_is_host_of_this_script()l
extern _native void unk_0x2547029C(int pram0, int pram1)l
extern _native void unk_0x46C39437(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void object_iterator_reset(int pram0)l
extern _native void unk_0xEA2A40BC(int pram0, int pram1)l
extern _native void memory_allow_throwing_explosives(int pram0, int pram1)l
extern _native void task_use_turret_against_coord(int pram0, int pram1, int pram2, int pram3)l
extern _native int combat_class_ai_get_attrib_float(int pram0, int pram1)l
extern _native int unk_0xCDA6BB6C()l
extern _native int unk_0xFF1F1730()l
extern _native int unk_0x93050734()l
extern _native void unk_0xE7A1C191()l
extern _native void add_cameratransition_event_hudfadein(int pram0, int pram1, int pram2, int pram3)l
extern _native void add_cameratransition_event_hudfadeout(int pram0, int pram1, int pram2, int pram3)l
extern _native int get_volume_heading(int pram0)l
extern _native void task_use_turret(int pram0, int pram1, int pram2)l
extern _native void unk_0x03240324(int pram0, int pram1)l
extern _native void unk_0x6471D75C(int pram0, int pram1)l
extern _native void unk_0x53895856(int pram0, int pram1)l
extern _native void unk_0x9C471E7D(int pram0, int pram1)l
extern _native void unk_0x1A82B949(int pram0, int pram1)l
extern _native void unk_0xE5E04E83(int pram0, int pram1)l
extern _native void unk_0x6CEFA97A(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0x5E84F53E(int pram0)l
extern _native void unk_0x4FA19C01()l
extern _native int unk_0x5BD2295E()l
extern _native void unk_0x3AE77125(int pram0, int pram1, int pram2, int pram3)l
extern _native void ai_set_weapon_desired_range(int pram0, int pram1)l
extern _native void unk_0xA4E29C31(int pram0, int pram1)l
extern _native void register_host_broadcast_variables(int pram0, int pram1)l
extern _native void register_client_broadcast_variables(int pram0, int pram1)l
extern _native int unk_0x704DBAC9(int pram0)l
extern _native void destroy_object_glow(int pram0)l
extern _native void unk_0x77403213(int pram0, int pram1, int pram2)l
extern _native void unk_0x418A22D5(int pram0, int pram1)l
extern _native void unk_0xCEC355CE(int pram0, int pram1)l
extern _native int unk_0x650A7440(int pram0, int pram1)l
extern _native void unk_0xD771AF0B(int pram0, int pram1, int pram2)l
extern _native int unk_0x7AB65B0C()l
extern _native int unk_0xFB2B0CCF(int pram0)l
extern _native int unk_0x2ADA3DD4()l
extern _native void unk_0x7837890B(int pram0)l
extern _native void unregister_script_with_audio()l
extern _native int unk_0x78B73E47(int pram0)l
extern _native int unk_0x5908F7FE(int pram0)l
extern _native int unk_0x19BD222F(int pram0)l
extern _native void destroy_object_animator(int pram0)l
extern _native void train_set_engine_enabled(int pram0, int pram1)l
extern _native void unk_0xADE865AE(int pram0, int pram1)l
extern _native void vehicle_set_handbrake(Actor Vehicle, bool Handbreak)l
extern _native void train_set_target_speed(int pram0, int pram1)l
extern _native int unk_0x5B417C9C(int pram0)l
extern _native int unk_0x1A4C98C1(int pram0, int pram1)l
extern _native void gateway_disable(int pram0, int pram1)l
extern _native void add_player_deadeye_points(int pram0, int pram1, int pram2)l
extern _native void task_follow_path_from_nearest_point(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void train_set_position_direction(int pram0, int pram1, int pram2)l
extern _native int gateway_get_volume(int pram0)l
extern _native void unk_0x5FEA3E61(int pram0, int pram1)l
extern _native int unk_0x7D397CAA(int pram0)l
extern _native int get_object_attached_to(int pram0)l
extern _native int unk_0x97931B87(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xFE83A4FE(int pram0)l
extern _native void unk_0x1C147E14(int pram0, int pram1)l
extern _native void unk_0x1306549E(int pram0, int pram1)l
extern _native int unk_0xCA6231C1(int pram0)l
extern _native void remove_camera_collision_exclusion(int pram0, int pram1)l
extern _native int is_physinst_ready(int pram0)l
extern _native void set_prop_fixed(int pram0, int pram1)l
extern _native int is_actor_jumping(int pram0)l
extern _native int is_actor_using_cover(int pram0)l
extern _native int get_player_zoom_state(int pram0)l
extern _native int unk_0x8C7E41E2(int pram0, int pram1)l
extern _native int get_event_type(int pram0)l
extern _native int unk_0x7EB1ED99(int pram0)l
extern _native void ui_anim_setup(int pram0, int pram1, int pram2, int pram3)l
extern _native void ui_anim_restart(int pram0)l
extern _native int unk_0xFF65A07C()l
extern _native int squad_goal_add_battle_defend_volume(int pram0, int pram1, int pram2, int pram3)l
extern _native void scale_volume(int pram0, int pram1)l
extern _native int unk_0x860FCDBD()l
extern _native int unk_0x0D0A66B6(int pram0, int pram1, int pram2, int pram3)l
extern _native int link_object_animator_to_actor(int pram0, int pram1, int pram2)l
extern _native void add_camera_collision_exclusion(int pram0, int pram1, int pram2)l
extern _native void print_small_format(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native32(0x4FE2B586) void _set_actor_infinite_ammo(Actor Actor, int WeapId, bool Infinite)l
extern _native Layout get_event_layout()l
extern _native int is_event_valid(int pram0)l
extern _native int unk_0xB64DDA6F(int pram0)l
extern _native int train_create_new_train(int pram0, int pram1, int pram2)l
extern _native void unk_0xA7A672FA(int pram0, int pram1)l
extern _native int train_get_car(int pram0, int pram1)l
extern _native int create_world_sector(int pram0, int pram1)l
extern _native int unk_0xC5E372BC(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xD4A54348(int pram0, int pram1, int pram2, int pram3)l
extern _native int squad_goal_add_stay_outside_of_volume(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void task_go_near_actorset(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xA9F5CDCB(int pram0)l
extern _native void train_enable_visual_debug(int pram0)l
extern _native void destroy_layout_objects(int pram0)l
extern _native void ui_hide(const char* uiLayer)l
extern _native void ui_show(const char* uiLayer)l
extern _native void unk_0xB3FC8CB7(int pram0, int pram1)l
extern _native void unk_0x5AEA32D1(int pram0, int pram1)l
extern _native void unk_0x175BE678(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0xB4D9B233(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void squad_flock_add_external_velocity_match(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void squad_flock_add_external_attraction_path(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void squad_flock_player_whistle_boost_set_enabled(int pram0, int pram1, int pram2)l
extern _native int unk_0x142D9F3A(int pram0, int pram1)l
extern _native int unk_0xBD374C00(int pram0)l
extern _native void get_path_point(int pram0, int pram1, int pram2)l
extern _native void ai_set_nav_max_water_depth_level(int pram0, int pram1)l
extern _native void squad_flock_set_external_movement_tuning(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void gateway_set_actor(int pram0, int pram1)l
extern _native void gringo_enable_type(int pram0)l
extern _native void train_release_train(int pram0, int pram1)l
extern _native void train_destroy_train(int pram0)l
extern _native int train_get_num_cars(int pram0)l
extern _native int unk_0x138F38AC(int pram0)l
extern _native void task_point_gun_at_coord(int pram0, int pram1, int pram2)l
extern _native int actor_has_anim_set(int pram0, int pram1)l
extern _native void clear_faction_status_to_individual_actor(int pram0, int pram1)l
extern _native int get_actor_stuck_state(int pram0)l
extern _native void unk_0xD95C01D2(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xE79F6CD4(int pram0, int pram1)l
extern _native void set_player_control_config(int pram0, int pram1)l
extern _native void set_force_player_aim_mode(int pram0, int pram1)l
extern _native void unk_0xB6CA7EBF(int pram0)l
extern _native void unk_0x160E79C6(int pram0, int pram1)l
extern _native void unk_0x6E946AF8(int pram0)l
extern _native int unk_0xF9CC7F63(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void ui_suppress(char* uiLayer)l
extern _native int unk_0x42A4CCD5(int pram0)l
extern _native void gringo_disable_type(int pram0)l
extern _native void unk_0xFD759593(int pram0, int pram1)l
extern _native void set_boat_extra_steer(int pram0, int pram1)l
extern _native void unk_0x44930268(int pram0, int pram1)l
extern _native void unk_0x4FCE7B9D(int pram0)l
extern _native void unk_0xDD0320CB()l
extern _native void set_damage_scale_enable(int pram0, int pram1)l
extern _native void task_override_set_movespeed_normalized(int pram0, int pram1)l
extern _native void unk_0x0753A098(int pram0, int pram1)l
extern _native void set_faction_status_to_individual_actor(int pram0, int pram1, int pram2)l
extern _native void set_vehicle_ejection_enabled(int pram0, int pram1)l
extern _native void unk_0x2B8F86ED(int pram0)l
extern _native int unk_0x794F5C21(int pram0)l
extern _native int unk_0xC673362C(int pram0, int pram1)l
extern _native int unk_0xC09ACD5C(int pram0)l
extern _native int unk_0x95A543E2(int pram0)l
extern _native void unk_0xBD42097A(int pram0)l
extern _native int unk_0xFD355ED1(int pram0, int pram1)l
extern _native int unk_0x805AC16A(int pram0, int pram1)l
extern _native void unk_0x67031EDA()l
extern _native void unk_0xD6111569(int pram0)l
extern _native void unk_0x0AAE9E6B(int pram0)l
extern _native int unk_0x4F652A00()l
extern _native int unk_0xFC564903()l
extern _native void unk_0xD7572C68(int pram0)l
extern _native int unk_0x76F09F04()l
extern _native void unk_0x87A3A38D(int pram0)l
extern _native int unk_0xEC6F465F(int pram0, int pram1)l
extern _native void unk_0x98FC68AF(int pram0)l
extern _native32(0xA56B459C) void _ui_disable(bool disable)l
extern _native void unk_0x20B684AB(int pram0)l
extern _native void unk_0xFA382FCB(int pram0, int pram1)l
extern _native void unk_0x0547A660(int pram0)l
extern _native void unk_0xCF065186(int pram0)l
extern _native void unk_0xBE7965C8(int pram0)l
extern _native void unk_0xD4C7E0D5(int pram0)l
extern _native int unk_0x59466B4D()l
extern _native int play_sound_from_object(int pram0, int pram1)l
extern _native void release_sound_id(int pram0)l
extern _native int unk_0xADF7D54B(int pram0)l
extern _native Object create_mp_text(Object Prop, const char* UnkNullStr, const char* GXTTextToDisplay, vector3 Position, vector3 Rotation, bool MaybeIsStringLiteral)l
extern _native int unk_0xE8739A48(int pram0)l
extern _native void unk_0x1F9EE9E1(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x6AFF3122(int pram0)l
extern _native void unk_0x1904CC1D(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x08D06543(int pram0)l
extern _native void set_sector_props_super_locked(int pram0, int pram1)l
extern _native void unk_0x84CD0651(int pram0, int pram1, int pram2)l
extern _native int unk_0x0AFC0B99()l
extern _native int is_door_closing(int pram0)l
extern _native int is_door_closed(int pram0)l
extern _native int is_door_opening(int pram0)l
extern _native void close_door(int pram0, int pram1)l
extern _native void unk_0x7CFD539A(int pram0, int pram1, int pram2)l
extern _native int unk_0xE92C3435(int pram0)l
extern _native void unk_0x591339B9(int pram0, int pram1)l
extern _native void toggle_journal_ui(int pram0, int pram1)l
extern _native void unk_0xB1B643E0(int pram0)l
extern _native void unk_0xA0AE0C98(int pram0, int pram1)l
extern _native void unk_0x48123591(int pram0)l
extern _native void unk_0xC741F051(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void unk_0xD291A820(int pram0)l
extern _native void unk_0xCE5CCF2E(int pram0, int pram1)l
extern _native int unk_0xC589CD7D()l
extern _native void unk_0xB0B4296A()l
extern _native void unk_0x8A1D83F2()l
extern _native int unk_0x44C07DA5(int pram0)l
extern _native int unk_0x69BE2817(int pram0)l
extern _native int unk_0xD8C8BEA1(int pram0)l
extern _native int unk_0x679C5955(int pram0)l
extern _native int get_object_named_bone_orientation(int pram0, int pram1, int pram2)l
extern _native int unk_0x8BD88B43()l
extern _native int unk_0x1C7C0F86(int pram0, int pram1, int pram2)l
extern _native int unk_0x836F42DA(int pram0, int pram1, int pram2, int pram3)l
extern _native void init_camera_from_channel(int pram0, int pram1)l
extern _native int unk_0x85049505(int pram0, int pram1)l
extern _native void unk_0x9A56C3F3(int pram0, int pram1)l
extern _native int unk_0xD9965A9A()l
extern _native void unk_0x4585821E(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x4238C471()l
extern _native void set_blip_visible(int pram0, int pram1)l
extern _native bool is_button_released(Controller Controller, eButton Button, int Unk1, int Unk0)l
extern _native void unk_0x408E28E2(int pram0)l
extern _native int net_is_player_participant(int pram0)l
extern _native void set_faction_is_lawful_to_attack(int pram0, int pram1)l
extern _native void mark_region_ready(int pram0)l
extern _native void task_animal_patrol(int pram0, int pram1)l
extern _native void unk_0x27A00456(int pram0)l
extern _native void unk_0x5C4CAE3A(int pram0)l
extern _native int net_get_host_of_this_script()l
extern _native int unk_0xB6006EA9(int pram0)l
extern _native int net_get_script_status()l
extern _native void net_set_this_script_is_net_script(int pram0)l
extern _native void unk_0x4897DD37(int pram0)l
extern _native int unk_0xE1D265FA(int pram0)l
extern _native void remove_all_pickups()l
extern _native int get_sound_id()l
extern _native void unk_0xB157BBB4(int pram0, int pram1)l
extern _native void at_fired_last(int pram0, int pram1, int pram2)l
extern _native void unk_0x1182C34F(int pram0)l
extern _native void unk_0xD0FB6AF0(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xDF50D8DE(int pram0, int pram1)l
extern _native int flash_set_int(const char* scaleformName, const char* scaleformVarName, int value)l
extern _native int unk_0x554CF528(int pram0)l
extern _native int set_object_animator_node(int pram0, int pram1)l
extern _native void unk_0xC00F8181(int pram0)l
extern _native int cutsceneobject_get_current_transition_type(int pram0)l
extern _native int unk_0x28DAED2A(int pram0)l
extern _native int unk_0xD4DEBC08(int pram0)l
extern _native void unk_0x75DD203B(int pram0)l
extern _native void unk_0xB829A92D(int pram0)l
extern _native void end_scripted_request(int pram0)l
extern _native void unk_0xE783219A(int pram0)l
extern _native void unk_0x6AF07F86(int pram0)l
extern _native void unk_0xCE7CE46D(int pram0, int pram1)l
extern _native void unk_0xEA2B35DB()l
extern _native void ui_hide_prompt(int pram0)l
extern _native void unk_0x5C7F63E3(int pram0)l
extern _native void set_auto_conversation_look(int pram0, int pram1)l
extern _native int unk_0xECD4F604(int pram0, int pram1)l
extern _native int unk_0xDD807723(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xAD313D88(int pram0, int pram1)l
extern _native int unk_0x9AD6D5B1(int pram0, int pram1)l
extern _native int is_processing_camera_shot_transition(int pram0)l
extern _native void end_current_camera_shot_transition(int pram0)l
extern _native void unk_0x7D95325E()l
extern _native int create_object_locator(int pram0, int pram1)l
extern _native int unk_0xE25F407D(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void unk_0x8FB32562(int pram0)l
extern _native float get_analog_button_value(Controller Controller, eButton Analog, bool Unk1)l
extern _native void unk_0x77D6ABF5(int pram0, int pram1)l
extern _native int camera_get_current_transition_type(int pram0)l
extern _native void ui_set_prompt_string(int pram0, int pram1)l
extern _native int unk_0xE39B92B7(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void ui_set_prompt_icon(int pram0, int pram1)l
extern _native int unk_0x0627DDEC(int pram0, int pram1)l
extern _native int unk_0x9BC05C90(int pram0, int pram1)l
extern _native int set_panim_phase(int pram0, int pram1)l
extern _native int flash_set_string(const char* scaleformName, const char* scaleformVarName, int pram2, int pram3)l
extern _native int unk_0x54A417F3(int pram0, int pram1)l
extern _native void set_camerashot_targetdof_fixed_distance(int pram0, int pram1)l
extern _native int add_camera_shot_transition_ease_in_out(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int add_camera_shot_transition_indefinite(int pram0, int pram1, int pram2)l
extern _native int unk_0x31940E4C(int pram0, int pram1)l
extern _native void hide_physinst(int pram0)l
extern _native int unk_0xD12802AF(int pram0)l
extern _native void unk_0xB3C3FF5E()l
extern _native int unk_0x64C2DD40(int pram0, int pram1)l
extern _native int unk_0x0D914C89()l
extern _native int unk_0x9B903F45(int pram0)l
extern _native void unk_0xCF1B9B11(int pram0, int pram1)l
extern _native int net_is_posse_leader()l
extern _native int net_get_posse_count()l
extern _native void end_current_minigame()l
extern _native void start_minigame(int pram0)l
extern _native int is_local_player(int pram0)l
extern _native int unk_0x554FC5E0()l
extern _native void unk_0x1EEE7494(int pram0, int pram1)l
extern _native void set_actor_allow_dismount(int pram0, int pram1)l
extern _native void ui_deactivate(const char* pram0)l
extern _native int unk_0x1A59E608(int pram0)l
extern _native void unk_0xA3AE09EF()l
extern _native void unk_0x27D40FD1(int pram0, int pram1, int pram2)l
extern _native void unk_0xB4C867BD(int pram0, int pram1, int pram2, int pram3)l
extern _native bool is_actor_shooting(Actor Actor)l
extern _native int is_actor_throwing(int pram0)l
extern _native void set_equip_slot_enabled(int pram0, int pram1, int pram2)l
extern _native int copy_volume(int pram0, int pram1, int pram2, int pram3)l
extern _native int object_iterator_prev(int pram0)l
extern _native int unk_0x276EFF8E(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xD792B93B(int pram0, int pram1)l
extern _native void set_camera_targetdof_using_soft_dof(int pram0, int pram1, int pram2)l
extern _native void unk_0x0AA5D947(int pram0, int pram1)l
extern _native void unk_0xEEC81873(int pram0, int pram1)l
extern _native int unk_0x4A8066FB()l
extern _native void unk_0xBEDF7AA8()l
extern _native int ss_register(int pram0, int pram1, int pram2)l
extern _native void unk_0xEC1E8210()l
extern _native void unk_0x06B4A139(int pram0)l
extern _native void unk_0x22424394(int pram0, int pram1)l
extern _native void unk_0x83E043A6()l
extern _native void unk_0x03CD9C87(int pram0, int pram1)l
extern _native void unk_0x39F5EF0F(int pram0, int pram1)l
extern _native void unk_0xD6CC6907(int pram0, int pram1)l
extern _native void unk_0x9D886C2F(int pram0, int pram1)l
extern _native void unk_0x714D5D09(int pram0, int pram1)l
extern _native void unk_0xBF959948(int pram0)l
extern _native void unk_0x3C163FDD(int pram0)l
extern _native void unk_0x67770F4B(int pram0, int pram1, int pram2, int pram3)l
extern _native void animal_species_tuning_set_attrib_bool(int pram0, int pram1, int pram2, int pram3)l
extern _native void animal_species_tuning_set_attrib_float(int pram0, int pram1, int pram2, int pram3)l
extern _native void animal_species_flock_set_parameter(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void animal_species_rel_set_predator_and_prey(int pram0, int pram1)l
extern _native void animal_species_flock_set_boolean_parameter(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void animal_species_flock_set_enabled(int pram0, int pram1, int pram2, int pram3)l
extern _native void animal_species_tuning_move_set_attrib(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void animal_species_init_begin(int pram0)l
extern _native void animal_species_init_register(int pram0, int pram1)l
extern _native void animal_species_init_end()l
extern _native void animal_species_flock_and_tuning_clear_all()l
extern _native void animal_species_rel_clear_all()l
extern _native void animal_species_tuning_set_attachment_with_offset(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void animal_species_rel_set_eat_gringo(int pram0, int pram1, int pram2)l
extern _native void animal_species_rel_set_can_warn(int pram0, int pram1, int pram2)l
extern _native void animal_species_rel_set_threat(int pram0, int pram1, int pram2)l
extern _native void animal_species_add_external_influence_flock_reasoner(int pram0, int pram1)l
extern _native void animal_species_tuning_set_attrib_float_from_time(int pram0, int pram1, int pram2, int pram3)l
extern _native void animal_species_add_external_repulsion(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void animal_species_rel_set_avoid(int pram0, int pram1, int pram2)l
extern _native void animal_species_add_external_random_noise(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void animal_species_set_special_use_gringo(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void animal_species_tuning_set_hunting_prey_prop(int pram0, int pram1)l
extern _native void animal_species_rel_set_attack_grab_enabled(int pram0, int pram1, int pram2)l
extern _native void animal_species_rel_set_play_growl(int pram0, int pram1, int pram2)l
extern _native void animal_species_rel_set_play_sniff(int pram0, int pram1, int pram2)l
extern _native void animal_species_rel_set_play_hunt(int pram0, int pram1, int pram2)l
extern _native void animal_species_rel_set_play_chase(int pram0, int pram1, int pram2)l
extern _native void animal_species_rel_set_play_beg(int pram0, int pram1, int pram2)l
extern _native void animal_species_set_unalerted_behavior(int pram0, int pram1, int pram2, int pram3)l
extern _native void animal_species_tuning_set_attachment_with_childbone(int pram0, int pram1, int pram2, int pram3)l
extern _native void animal_species_needs_domestication_levels(int pram0)l
extern _native void unk_0x1957B498(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x88FD9623(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x192973A0(int pram0, int pram1, int pram2, int pram3)l
extern _native void set_faction_to_faction_accuracy_scale_factor(int pram0, int pram1, int pram2)l
extern _native void unk_0xAD3877AF(int pram0)l
extern _native void reload_factions(int pram0)l
extern _native void unk_0x0079FD0F()l
extern _native void set_vehicle_appointment_target()l
extern _native void unk_0xF4641CF4(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x4BCFADB1(int pram0, int pram1)l
extern _native void unk_0xF435CCDE(int pram0)l
extern _native void unk_0x39EF8DA7()l
extern _native void unk_0x8BE2D8B0(int pram0)l
extern _native void unk_0x724B4E9B(int pram0, int pram1)l
extern _native int remove_asset(int pram0, int pram1)l
extern _native void unk_0x10BD98C9(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x4D42E285(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xE694F53A(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x82609DC7(int pram0, int pram1, int pram2)l
extern _native void unk_0x628E3173(int pram0, int pram1, int pram2)l
extern _native void unk_0xA6C4E59F(int pram0, int pram1, int pram2)l
extern _native void unk_0xEA06907B(int pram0, int pram1, int pram2)l
extern _native void unk_0xA2597101(int pram0, int pram1, int pram2)l
extern _native int unk_0x629E2E88()l
extern _native int combat_class_request_get_actor()l
extern _native void combat_class_request_completed()l
extern _native void set_actor_allow_weapon_reaction_flee(int pram0, int pram1)l
extern _native void ai_set_nav_hazard_avoidance_enabled(int pram0, int pram1, int pram2)l
extern _native void set_actor_sex(int pram0, int pram1)l
extern _native void unk_0x4D53AC21(int pram0, int pram1)l
extern _native void unk_0x12A86E9D(int pram0, int pram1)l
extern _native void unk_0x91220723(int pram0, int pram1, int pram2)l
extern _native void unk_0x5613615B(int pram0, int pram1)l
extern _native int unk_0x76478D6E()l
extern _native int unk_0xA488E930(int pram0)l
extern _native void unk_0x9679CF84(int pram0, int pram1)l
extern _native void unk_0x39928706(int pram0, int pram1)l
extern _native int unk_0x1EE7153B(int pram0, int pram1, int pram2)l
extern _native int unk_0xA8F64D32(int pram0, int pram1)l
extern _native int actor_get_weapon_ammo(int pram0, int pram1)l
extern _native void ai_shoot_target_set_bone(int pram0, int pram1, int pram2)l
extern _native void task_use_turret_against_object(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x856C3A8A(int pram0, int pram1, int pram2)l
extern _native int animal_actor_get_domestication(int pram0)l
extern _native int unk_0x2A902148(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void ai_global_clear_danger(int pram0)l
extern _native void unk_0x468DDDB3(int pram0, int pram1)l
extern _native int unk_0x5DE07F18(int pram0)l
extern _native int set_current_map(int pram0)l
extern _native int unk_0xF62EE158()l
extern _native void unk_0x449D4A89(int pram0)l
extern _native int unk_0xAEC955F8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x28FCBDF2(int pram0)l
extern _native void allow_tumbleweeds(int pram0)l
extern _native void ui_set_icon(int pram0, int pram1)l
extern _native void unk_0xDF4627D1(int pram0, int pram1)l
extern _native void unk_0xDC330FB9(int pram0)l
extern _native int unk_0x9AC89564(int pram0, int pram1, int pram2)l
extern _native int unk_0xA61FA36B()l
extern _native int unk_0x1E81DB60(int pram0, int pram1, int pram2)l
extern _native void unk_0x2F7CB0E3(int pram0, int pram1)l
extern _native void unk_0x955E5EEB(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native void unk_0x59A7835E()l
extern _native int unk_0x57FC0E16(int pram0)l
extern _native int is_physinst_in_level(int pram0)l
extern _native int get_journal_entry_num_details(int pram0)l
extern _native int get_journal_entry_detail_hash_by_index(int pram0, int pram1)l
extern _native void unk_0x5209C0C0(int pram0, int pram1, int pram2, int pram3)l
extern _native void enable_mover(int pram0)l
extern _native int unk_0x7246F438(int pram0)l
extern _native int unk_0x6A0FE2A0(int pram0, int pram1)l
extern _native int unk_0xAC5043C5()l
extern _native void unk_0x9E6CAD1D(int pram0, int pram1)l
extern _native void suspend_mover(int pram0)l
extern _native void set_curve_active(int pram0, int pram1)l
extern _native void release_constraint(int pram0)l
extern _native void set_bridge_stiffness(int pram0, int pram1)l
extern _native int unk_0x4A05AA7D(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void set_sleep_tolerance(int pram0, int pram1)l
extern _native int unk_0xC039BBF1(int pram0, int pram1, int pram2)l
extern _native int unk_0x51CF9A54(int pram0, int pram1, int pram2)l
extern _native int get_object_relative_offset(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0xBE17EB88(int pram0)l
extern _native void unk_0xABC78721(int pram0)l
extern _native int gringo_query_struct(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xBBB2780E()l
extern _native int unk_0xF4015EFC()l
extern _native int is_gringo_active()l
extern _native int unk_0xF550F8E7()l
extern _native int unk_0xCA589BAB()l
extern _native int unk_0x2F096285()l
extern _native int unk_0x54745DB0()l
extern _native int unk_0xD62D413C(int pram0)l
extern _native void gringo_enable_player_control(int pram0, int pram1)l
extern _native int unk_0x926FD361()l
extern _native void gringo_set_message_return(int pram0)l
extern _native void gringo_wait(int pram0)l
extern _native void gringo_stop()l
extern _native int gringo_handles_movement(int pram0)l
extern _native int set_gringo_bool_attr(int pram0, int pram1, int pram2)l
extern _native int get_target_object()l
extern _native void unk_0x9A756A72(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0x0A0E660E()l
extern _native int get_gringo_bool_attr(int pram0, int pram1, int pram2)l
extern _native void unk_0x89DE8A75(int pram0, int pram1)l
extern _native int get_gringo_string_attr(int pram0, int pram1, int pram2)l
extern _native int get_gringo_float_attr(int pram0, int pram1, int pram2)l
extern _native void unk_0x7284A71B(int pram0, int pram1)l
extern _native int unk_0x5CFBF505(int pram0)l
extern _native int unk_0x3A31175A(int pram0)l
extern _native int unk_0x6426CCD6(int pram0)l
extern _native int is_gringo_component_valid(int pram0)l
extern _native int unk_0xE18BCD70(int pram0, int pram1, int pram2)l
extern _native int unk_0x4DB7C61C(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xA20141C0(int pram0)l
extern _native int gringo_get_attribute(int pram0, int pram1)l
extern _native int gringo_get_attribute_count(int pram0)l
extern _native int unk_0xBED45A9A(int pram0)l
extern _native int unk_0xBF322F5C(int pram0)l
extern _native int gringo_get_attribute_hash(int pram0)l
extern _native int unk_0xD7BB1792(int pram0, int pram1)l
extern _native int unk_0xD282013F(int pram0, int pram1)l
extern _native int is_prop_fixed(int pram0)l
extern _native int unk_0x663F1464(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x4A1D2E25(int pram0)l
extern _native int unk_0x817B6952(int pram0)l
extern _native void unk_0x53B9569C(int pram0, int pram1)l
extern _native int unk_0x0912622D(int pram0)l
extern _native int net_set_node_replication(int pram0, int pram1, int pram2)l
extern _native int unk_0xC17BAD12(int pram0)l
extern _native void set_animal_can_attack(int pram0, int pram1)l
extern _native int unk_0x35279C3F(int pram0, int pram1)l
extern _native int unk_0x5F516FC3(int pram0)l
extern _native void unk_0xB62FE25C(int pram0, int pram1)l
extern _native int ai_speech_get_allow_for_actor(int pram0)l
extern _native int unk_0xE4C686BA(int pram0, int pram1, int pram2)l
extern _native int unk_0xAE7B3880()l
extern _native int unk_0x600A0EE4(int pram0, int pram1)l
extern _native int unk_0xAFF7D382(int pram0, int pram1, int pram2)l
extern _native int gringo_return_actor_to_default_anims(int pram0)l
extern _native void report_gringo_use_phase(int pram0, int pram1)l
extern _native int unk_0xD3D8E8ED(int pram0, int pram1)l
extern _native void unk_0x29AEB2DB(int pram0, int pram1)l
extern _native void unk_0x6695E185(int pram0, int pram1)l
extern _native int unk_0x1D711058(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x87BA5FE9(int pram0, int pram1)l
extern _native int unk_0x721FC9A4(int pram0)l
extern _native int unk_0x6263F909(int pram0)l
extern _native int unk_0x3E8F94BE(int pram0, int pram1)l
extern _native int gringo_get_physinst(int pram0)l
extern _native int unk_0xB96874B4(int pram0)l
extern _native int unk_0x5B46757F(int pram0)l
extern _native int unk_0x15A0E28B(int pram0)l
extern _native int unk_0x5AF74E19(int pram0, int pram1)l
extern _native int unk_0x1F74EE6C(int pram0, int pram1, int pram2)l
extern _native int unk_0x405E3903(int pram0, int pram1)l
extern _native int unk_0xEEE9C799(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int get_gringo_vector_attr(int pram0, int pram1, int pram2)l
extern _native void unk_0x026F7060(int pram0, int pram1, int pram2, int pram3)l
extern _native int set_gringo_vector_attr(int pram0, int pram1, int pram2)l
extern _native int set_gringo_float_attr(int pram0, int pram1, int pram2)l
extern _native int gringo_actor_move_to_and_face(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int unk_0xFF1FC1EF()l
extern _native int unk_0x24BAABCA(int pram0)l
extern _native void reset_react_node_for_actor(int pram0)l
extern _native int unk_0x5C11B011(int pram0, int pram1)l
extern _native int unk_0xA7E9DA22(int pram0)l
extern _native void unk_0x61664EC0(int pram0, int pram1, int pram2)l
extern _native int unk_0x4F10FD5B(int pram0)l
extern _native void reset_prop(int pram0)l
extern _native void unk_0x90FBBB8B(int pram0)l
extern _native void unk_0x8C2914C4(int pram0, int pram1)l
extern _native void unk_0x22D573D2(int pram0)l
extern _native int unk_0x51581898(int pram0)l
extern _native int unk_0x7E81694C(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native void gringo_set_component_user(int pram0, int pram1)l
extern _native int unk_0x9CD3385E(int pram0)l
extern _native void gringo_set_request_string(int pram0)l
extern _native int unk_0xBC32DA9A(int pram0, int pram1, int pram2)l
extern _native int get_actor_gait_type(int pram0)l
extern _native void unk_0x8CAF5C5C(int pram0)l
extern _native int unk_0x65CA3037(int pram0)l
extern _native int unk_0x5388F37D()l
extern _native int unk_0x284DD17C(int pram0, int pram1)l
extern _native int unk_0x3FA5FC03(int pram0)l
extern _native int unk_0xD6EE9534(int pram0, int pram1, int pram2)l
extern _native void unk_0xC8C0C708(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x7BF01CCB()l
extern _native void unk_0x8EA46104(int pram0)l
extern _native int get_target_actor()l
extern _native void unk_0xBEF32D17(int pram0, int pram1)l
extern _native void unk_0x7D600F2F(int pram0, int pram1)l
extern _native int unk_0x2C57A529(int pram0, int pram1)l
extern _native void gringo_set_prop_collisions(int pram0, int pram1)l
extern _native void unk_0x175CD937(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x47D2DE08(int pram0, int pram1)l
extern _native int unk_0x48B7C279(int pram0, int pram1)l
extern _native void unk_0xEB046CD9(int pram0)l
extern _native void unk_0x1C462085(int pram0)l
extern _native void unk_0x58018D83(int pram0)l
extern _native int is_player_signed_in()l
extern _native int unk_0x1D177160()l
extern _native int unk_0x1ADA1769()l
extern _native void set_camerashot_from_lens(int pram0, int pram1)l
extern _native void force_camerashot_update(int pram0)l
extern _native int camerashot_is_visible_actor(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0xF52BA99F(int pram0)l
extern _native int is_object_attached(int pram0)l
extern _native int is_actor_on_boat(int pram0)l
extern _native int train_get_lod_level(int pram0)l
extern _native int train_get_velocity(int pram0)l
extern _native void unk_0x1344515B()l
extern _native void unk_0x364F41D6()l
extern _native int is_population_set_required_resident(int pram0)l
extern _native int create_zone_volume(int pram0)l
extern _native void set_zone_population_type(int pram0, int pram1)l
extern _native void unk_0x9381D459(int pram0, int pram1)l
extern _native void unk_0xE0FDD026(int pram0, int pram1)l
extern _native void unk_0x5996941F(int pram0, int pram1)l
extern _native void unk_0x84FB15FA(int pram0, int pram1)l
extern _native void unk_0x1B271D85(int pram0, int pram1)l
extern _native void set_zone_population_count_random(int pram0, int pram1, int pram2)l
extern _native void unk_0xD28A3706(int pram0)l
extern _native void unk_0x04EFC113(int pram0)l
extern _native void set_accessoryset_on_spawn(int pram0, int pram1, int pram2)l
extern _native int unk_0xB0882841(int pram0, int pram1)l
extern _native int unk_0x03B2D067(int pram0)l
extern _native void unk_0x93B6135B(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void ambient_spawn_prestream_set(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void unk_0x0B24CE10(int pram0, int pram1)l
extern _native void unk_0xE4A789D8(int pram0, int pram1)l
extern _native void unk_0x07FD0A76(int pram0, int pram1)l
extern _native int unk_0xC1195126(int pram0)l
extern _native void set_town_density(int pram0)l
extern _native void unk_0x6C526E7B(int pram0)l
extern _native int is_zone_valid(int pram0)l
extern _native void unk_0xD72DF5C6(int pram0, int pram1)l
extern _native void unk_0x7D4FB8C8(int pram0, int pram1)l
extern _native void set_zone_priority(int pram0, int pram1)l
extern _native void unk_0xE7F19909(int pram0, int pram1)l
extern _native void ai_goal_shoot_at_coord(int pram0, int pram1)l
extern _native void set_allow_ride_by_ai(int pram0, int pram1)l
extern _native void ai_set_allowed_mount_directions(int pram0, int pram1)l
extern _native int unk_0x3F226995(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12)l
extern _native void unk_0x261A4C0E(int pram0, int pram1, int pram2)l
extern _native void set_door_current_speed(int pram0, int pram1, int pram2)l
extern _native int camera_is_visible_volume(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void unk_0x15040CD2(int pram0)l
extern _native void reset_exclusive_journal_id()l
extern _native void unk_0x14ED45FB()l
extern _native void unk_0x1BB84187()l
extern _native void unk_0xAC72E757(int pram0)l
extern _native void audio_mission_release()l
extern _native void enable_journal_replay(int pram0)l
extern _native void unk_0xF1779E65()l
extern _native void unk_0x6C7A3CE6()l
extern _native void unk_0xBEF6031B(int pram0, int pram1)l
extern _native int unk_0xDB86F53B(int pram0)l
extern _native void disable_verify_ss(int pram0)l
extern _native void unk_0xB42EBC65(int pram0)l
extern _native void unk_0x374DE883(int pram0)l
extern _native void streaming_enable_bounds(int pram0)l
extern _native void clear_mission_info()l
extern _native void set_deadeye_regeneration_rate_multiplier(int pram0, int pram1)l
extern _native void unk_0x07EC142B(int pram0)l
extern _native void unk_0x7AB17813(int pram0, int pram1)l
extern _native int unk_0xDE339CE1()l
extern _native int unk_0xA6CFA220()l
extern _native int unk_0xEDF1D0B4()l
extern _native void unk_0xC175F2B5(int pram0, int pram1)l
extern _native int unk_0x8287F8B3(int pram0, int pram1, int pram2)l
extern _native int unk_0x3D014AB1(int pram0)l
extern _native int unk_0x24F97294()l
extern _native void unk_0x2B45FADE()l
extern _native int unk_0xA5691922()l
extern _native int unk_0xED0BA189(int pram0)l
extern _native int unk_0xD89902F1(int pram0)l
extern _native void unk_0xFD300D15(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0x0FE90DCB()l
extern _native void unk_0x98A9AC9E()l
extern _native void unk_0xE808BFFB(int pram0)l
extern _native int unk_0x7653788C()l
extern _native void unk_0x98D0F458()l
extern _native int actor_is_grabbed_by_cutscene(int pram0)l
extern _native void set_most_recent_mount(int pram0, int pram1)l
extern _native void unk_0x755382BC(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int cutscene_manager_get_initial_streaming_load_scene_ext(int pram0, int pram1)l
extern _native void unk_0x99D215B4(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void unk_0x7716B12B()l
extern _native int unk_0xB2F2A7F2(int pram0, int pram1, int pram2)l
extern _native int unk_0x9410D992(int pram0, int pram1, int pram2)l
extern _native int unk_0xC6557710(int pram0)l
extern _native int get_last_note_objective()l
extern _native int unk_0xD9E4A8DA()l
extern _native int unk_0xA56DCCF2(int pram0, int pram1, int pram2)l
extern _native int unk_0xEBAB5F62(int pram0)l
extern _native void unk_0x6287203C(int pram0)l
extern _native int ai_has_actor_bumped_into_me(int pram0, int pram1, int pram2)l
extern _native int unk_0x7263860F()l
extern _native void set_cutscene_streaming_load_scene(int pram0, int pram1)l
extern _native void unk_0x9E6A776F(int pram0, int pram1)l
extern _native int unk_0x2DB208A1()l
extern _native void ai_set_nav_pathfinding_enabled_when_driving(int pram0, int pram1)l
extern _native int unk_0x8020C45E(int pram0, int pram1, int pram2)l
extern _native void unk_0xF0DDF83D(int pram0)l
extern _native int audio_music_is_prepared()l
extern _native int audio_music_play_prepared()l
extern _native void unk_0xE613AE52(int pram0)l
extern _native void unk_0xF55B50ED(int pram0)l
extern _native void unk_0x6336182D(int pram0)l
extern _native void unk_0x84F3DD81(int pram0, int pram1)l
extern _native int unk_0xCE01609D(int pram0)l
extern _native void unk_0x3A6960B2(int pram0)l
extern _native void set_actor_speed(int pram0, int pram1)l
extern _native void audio_mission_init()l
extern _native void unk_0x66FCA3F7(int pram0)l
extern _native void set_exclusive_journal_id(int pram0)l
extern _native void set_mission_info(int pram0, int pram1)l
extern _native int unk_0xBDD4D4D5(int pram0)l
extern _native void train_set_max_accel(int pram0, int pram1)l
extern _native void train_set_target_pos(int pram0, int pram1)l
extern _native void unk_0x1440C806(int pram0, int pram1)l
extern _native void unk_0x0911BA31(int pram0, int pram1)l
extern _native void unk_0x47FAE768(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0xB0479CB8(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void train_force_high_lod(int pram0, int pram1)l
extern _native void train_set_max_decel(int pram0, int pram1)l
extern _native void unk_0x268D546D(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xE0BE8235(int pram0)l
extern _native void task_shoot_from_cover(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void actor_set_grabbed_by_cutscene(int pram0, int pram1)l
extern _native int unk_0x1F9F8C04(int pram0, int pram1, int pram2)l
extern _native int unk_0xF37E8A9E(int pram0, int pram1)l
extern _native void unk_0x7007019D(int pram0, int pram1)l
extern _native int unk_0x8C0E3E29(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int unk_0xB550D120(int pram0)l
extern _native void set_prop_targetable(int pram0, int pram1, int pram2)l
extern _native void ai_avoid_ignore_actor(int pram0, int pram1)l
extern _native void ai_set_nav_subgrid_cell_size(int pram0, int pram1)l
extern _native int unk_0x8ED2B0BC(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void task_follow_object_along_path(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void estimate_two_distances_along_path(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void task_horse_action(int pram0, int pram1)l
extern _native int unk_0x5DB05BBC(int pram0)l
extern _native void unk_0x8062BD74(int pram0, int pram1, int pram2)l
extern _native void destroy_point_light(int pram0)l
extern _native void unk_0x205E891C(int pram0, int pram1, int pram2)l
extern _native void set_deadeye_blink(int pram0)l
extern _native void unk_0x134AAF17(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x12558DBD(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x88863344()l
extern _native int unk_0xD062CBF6(int pram0, int pram1)l
extern _native void deactivate_journal_entry(int pram0, int pram1)l
extern _native void set_rcm_actor_call_over_enable(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int get_journal_entry_disallow_tracking(int pram0)l
extern _native int gateway_get_marker(int pram0)l
extern _native int get_actor_invulnerability(int pram0)l
extern _native int is_ai_actor_engaged_in_combat(int pram0)l
extern _native void unk_0xD15B53F8(int pram0)l
extern _native int unk_0xD89C14BA(int pram0)l
extern _native int get_layout_name(int pram0)l
extern _native void unk_0x50A2051C(int pram0)l
extern _native int unk_0x79C748BE(int pram0, int pram1, int pram2)l
extern _native int is_blip_visible(int pram0)l
extern _native void unk_0x2D40E85C(int pram0, int pram1, int pram2)l
extern _native int set_actor_hearing_max_range(int pram0, int pram1)l
extern _native int is_door_open_in_direction(int pram0, int pram1)l
extern _native void set_door_auto_close(int pram0, int pram1)l
extern _native int unk_0xD6F4FDAD(int pram0)l
extern _native bool get_draw_actor(Actor Actor)l
extern _native void set_player_deadeye_mode(int pram0, int pram1)l
extern _native void unk_0xCC69DCC1(int pram0, int pram1, int pram2)l
extern _native void task_guard_stand(int pram0, int pram1, int pram2)l
extern _native int unk_0x22558E3F(int pram0)l
extern _native int unk_0x26884138()l
extern _native int unk_0xE7371670()l
extern _native void set_infinite_deadeye(int UNK0, bool Infinite)l
extern _native int horse_unlock_freshness(int pram0)l
extern _native int horse_set_curr_freshness(int pram0, int pram1)l
extern _native int horse_lock_freshness(int pram0)l
extern _native int decor_get_vector(int pram0, int pram1, int pram2)l
extern _native void set_stamina_blink(int pram0)l
extern _native int set_actor_max_freshness(int pram0, int pram1)l
extern _native int unk_0x21BCC0A9(int pram0)l
extern _native int unk_0x75D4E33F(int pram0, int pram1)l
extern _native int unk_0x99356925(int pram0, int pram1, int pram2)l
extern _native int unk_0x35051831(int pram0, int pram1, int pram2)l
extern _native void unk_0x14585073(int pram0, int pram1)l
extern _native void set_rcm_was_john_now_jack(int pram0, int pram1)l
extern _native void ai_goal_look_at_player_when_within(int pram0, int pram1)l
extern _native int ai_was_pushed_over(int pram0, int pram1)l
extern _native int unk_0xEBC9C2FD(int pram0, int pram1)l
extern _native int ai_global_is_danger(int pram0, int pram1)l
extern _native int get_radar_radius()l
extern _native void unk_0xC6E36B1D(int pram0)l
extern _native void play_sound(int pram0)l
extern _native int unk_0x191658C0()l
extern _native int unk_0x32D1DEB0()l
extern _native void set_journal_entry_updated(int pram0, int pram1)l
extern _native void register_traffic_objectset(int pram0)l
extern _native void set_actor_weapon_reaction_no_flee_hack(int pram0, int pram1)l
extern _native void register_traffic_actor(int pram0, int pram1)l
extern _native int unk_0x1BA90C92(int pram0)l
extern _native int is_actor_whistling(int pram0)l
extern _native int unk_0x87C49DBD(int pram0, int pram1)l
extern _native int unk_0x72F6EED0()l
extern _native int get_event_time(int pram0)l
extern _native void set_gps_path(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native void register_gps_curve_objectset(int pram0)l
extern _native int unk_0xAA322DFC(int pram0)l
extern _native void set_journal_entry_disallow_tracking(int pram0, int pram1)l
extern _native int unk_0x427F4D58(int pram0, int pram1, int pram2)l
extern _native int unk_0x94F5E63F(int pram0)l
extern _native void unk_0xAB8A1C15(int pram0)l
extern _native void unk_0x8392855D(int pram0, int pram1)l
extern _native int unk_0x6B439149()l
extern _native int net_mailbox_is_challenge_valid(int pram0)l
extern _native int unk_0xE85942F0(int pram0)l
extern _native int unk_0xFD6197EB(int pram0, int pram1)l
extern _native int sc_challenge_get_var_int(int pram0, int pram1)l
extern _native int unk_0xA183D927()l
extern _native void ui_challenge_set_objective(int pram0, int pram1, int pram2)l
extern _native void unk_0x761A6750(int pram0, int pram1)l
extern _native void unk_0xAFC9071D(int pram0, int pram1, int pram2)l
extern _native void ui_button_set_text(int pram0, int pram1)l
extern _native void unk_0xC201524D(int pram0, int pram1, int pram2)l
extern _native void ui_challenge_set_description(int pram0, int pram1)l
extern _native void unk_0x3731AC9F(int pram0, int pram1)l
extern _native int sc_challenge_get_community_value(int pram0)l
extern _native int sc_challenge_get_community_total(int pram0)l
extern _native void unk_0x4A598723(int pram0, int pram1, int pram2)l
extern _native void unk_0x9272926C(int pram0, int pram1, int pram2)l
extern _native void ui_challenge_make_current(int pram0)l
extern _native int unk_0xA3E1EF71()l
extern _native int unk_0x34711B59()l
extern _native int unk_0x5725C84F()l
extern _native int unk_0x5FD52711()l
extern _native int unk_0x86BC0A55(int pram0, int pram1)l
extern _native void unk_0xEB4A6D85()l
extern _native int unk_0xD0808C42()l
extern _native int unk_0xE89C6E4F()l
extern _native int unk_0x49C2B05F(int pram0)l
extern _native int unk_0x0791F35A()l
extern _native int unk_0xC813DBEF()l
extern _native int unk_0x70AF0351(int pram0)l
extern _native int unk_0xE6B4F505()l
extern _native int unk_0x097BB984()l
extern _native int unk_0x3A8C77AD(int pram0)l
extern _native int unk_0xEA7ADF42()l
extern _native int unk_0x293C3288()l
extern _native int unk_0x984749B4(int pram0)l
extern _native int unk_0xA7F231B0()l
extern _native void unk_0x970AC1F7(int pram0, int pram1)l
extern _native void unk_0x0A87A573(int pram0, int pram1)l
extern _native int unk_0x25EF49AD(int pram0)l
extern _native void unk_0x23EB81F0(int pram0, int pram1)l
extern _native void update_stat(int pram0, int pram1, int pram2)l
extern _native void hide_stat(int pram0, int pram1)l
extern _native int unk_0x5B404EDA()l
extern _native int unk_0x6A307D5F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void unk_0x7FF20D84(int pram0)l
extern _native void unk_0x364450B1(int pram0)l
extern _native int can_player_die()l
extern _native void unk_0xCFE22435(int pram0)l
extern _native void reset_rumble()l
extern _native void unk_0x39B0CFE5()l
extern _native void set_faction_to_faction_damage_scale_factor(int pram0, int pram1, int pram2)l
extern _native int net_request_object(int pram0)l
extern _native void task_respond_to_horse_whistle(int pram0, int pram1)l
extern _native int unk_0x50A7E334(int pram0)l
extern _native void unk_0x48DB367D(int pram0)l
extern _native void unk_0xB4614D11(int pram0, int pram1)l
extern _native int unk_0x919142BE()l
extern _native int unk_0x3A899B0E(int pram0)l
extern _native int get_actor_ground_material(int pram0)l
extern _native int unk_0x3E758743(int pram0)l
extern _native void unk_0xE7F781B8()l
extern _native void ai_set_special_areas_time(int pram0, int pram1)l
extern _native int tough_armour_get_tuning_regeneration_rate(int pram0)l
extern _native void set_player_enable_mount_use_contexts(int pram0, int pram1)l
extern _native int gringo_query_bool(int pram0, int pram1, int pram2, int pram3)l
extern _native int get_game_state()l
extern _native int create_journal_entry_by_hash(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x50C0E83F(int pram0)l
extern _native int unk_0x2776B0F5(int pram0)l
extern _native void unk_0xB008EF49(int pram0, int pram1, int pram2)l
extern _native int unk_0xF750D150(int pram0, int pram1, int pram2)l
extern _native void unk_0x0E712FCB(int pram0, int pram1)l
extern _native void set_prop_targetable_acquisition_radius(int pram0, int pram1)l
extern _native void set_prop_targetable_score_bias(int pram0, int pram1)l
extern _native void set_prop_targetable_as_enemy(int pram0, int pram1)l
extern _native void set_prop_targetable_target_box_size(int pram0, int pram1, int pram2)l
extern _native void set_actor_death_drop_distance(int pram0, int pram1)l
extern _native void fire_set_owner(int pram0, int pram1)l
extern _native int unk_0x375A33F0(int pram0, int pram1)l
extern _native int actor_is_variable_mesh_enabled(int pram0, int pram1)l
extern _native int get_actor_proof(int pram0)l
extern _native void unk_0x49BC0219(int pram0)l
extern _native void unk_0x6085F7AC(int pram0, int pram1)l
extern _native void add_cameratransition_event_gamecameraresettilt(int pram0, int pram1, int pram2)l
extern _native int unk_0xE5645CB3()l
extern _native void unk_0xC9FCD3EC(int pram0)l
extern _native void unk_0xEC906A7A(int pram0)l
extern _native void unk_0xFA43DCC5(int pram0)l
extern _native int is_actor_flying(int pram0)l
extern _native int copy_event(int pram0, int pram1)l
extern _native int get_linked_anim_target(int pram0)l
extern _native int unk_0x19F62133()l
extern _native int unk_0x586714AE(int pram0)l
extern _native int unk_0xB573FF63(int pram0)l
extern _native void set_prop_health(int pram0, int pram1)l
extern _native int unk_0xFC718FC5(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void gringo_set_target_object(int pram0, int pram1, int pram2)l
extern _native int unk_0xB78BC233(int pram0, int pram1, int pram2)l
extern _native void add_cameratransition_event_cutgamecamerabehindplayer(int pram0, int pram1, int pram2)l
extern _native bool camera_probe(vector3* Result, vector3 Source, vector3 Target, Actor Owner, int Flag)l
extern _native void unk_0x8B011F5D()l
extern _native void unk_0xA8226DFF(int pram0)l
extern _native void unk_0x831FC466(int pram0)l
extern _native void unk_0xCC9E6F4C(int pram0, int pram1, int pram2, int pram3)l
extern _native void add_persistent_script(int pram0)l
extern _native void remove_persistent_script(int pram0)l
extern _native int is_game_paused()l
extern _native32(0xBC58F1EA) IterationSet _get_iteration_set(int SetId)l
extern _native int ui_get_selected_index(const char* MenuID, bool UNK0)l
extern _native void ui_transition_to(int pram0)l
extern _native void unk_0x7BD7A465(int pram0, int pram1)l
extern _native int unk_0xFD91BE0D(int pram0)l
extern _native void unk_0xCF674E31(int pram0, int pram1)l
extern _native void set_player_combatmode(int pram0)l
extern _native void ui_goto(int pram0)l
extern _native void unk_0x5F66B23E(int pram0, int pram1)l
extern _native void set_pers_char_allow_spawn_elsewhere(int pram0, int pram1)l
extern _native void unk_0x7614AEBA(int pram0, int pram1)l
extern _native int unk_0xD036DF91()l
extern _native void unk_0x69FC319E()l
extern _native int has_sound_finished(int pram0)l
extern _native void unk_0x5B05E3E0(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void make_bird_fly_from_point(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void squad_battle_allies_set_formation_density(int pram0, int pram1, int pram2)l
extern _native int play_simple_prop_animation(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0xA607D290()l
extern _native void set_indicator_draw(int pram0, int pram1)l
extern _native void unk_0x3375FB38(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0xE7A0A109(int pram0)l
extern _native void unk_0x0073024E(int pram0)l
extern _native void unk_0x82C54B8A(int pram0, int pram1)l
extern _native void unk_0x92CC441F(int pram0, int pram1)l
extern _native void snapshot_globals()l
extern _native void unk_0xFB227D11(int pram0)l
extern _native void unk_0x85D62384()l
extern _native int unk_0x8DF144C2(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x17CF885F(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x20CE8AA8(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0x6D59A25F(int pram0, int pram1)l
extern _native void unk_0x8E867DDD(int pram0)l
extern _native void unk_0x6E79F939(int pram0, int pram1)l
extern _native void unk_0xE8637D2B(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0x3E647734(int pram0, int pram1, int pram2)l
extern _native void unk_0xE0553D6B(int pram0, int pram1)l
extern _native void unk_0xD68E04BB(int pram0, int pram1)l
extern _native void unk_0x638EAF70(int pram0, int pram1)l
extern _native void unk_0xEA975A79(int pram0, int pram1)l
extern _native void unk_0x6BB42C21(int pram0)l
extern _native void unk_0x0E634931(int pram0)l
extern _native void unk_0x567712E5(int pram0)l
extern _native void unk_0xB888B369(int pram0)l
extern _native void unk_0x306D9FEE(int pram0)l
extern _native void unk_0xC3614E0A(int pram0)l
extern _native void unk_0xF962F2B8(int pram0)l
extern _native void unk_0x22D0DF9B(int pram0)l
extern _native void unk_0xA234C5D0(int pram0)l
extern _native void unk_0x733BA9F5(int pram0)l
extern _native void unk_0x79351E54(int pram0)l
extern _native void unk_0xCCBE7F0F(int pram0)l
extern _native void unk_0x5FCF3B85(int pram0)l
extern _native void unk_0xF07F5E41(int pram0)l
extern _native void unk_0xCB139D15(int pram0)l
extern _native void unk_0x886E06C2(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void unk_0xB6839756()l
extern _native void unk_0x6D0B8619(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x807B9519(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xCBA75200(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x0A23A69C()l
extern _native void unk_0x01C7193C(int pram0, int pram1)l
extern _native void unk_0xE0DF7B3B(int pram0, int pram1, int pram2)l
extern _native void unk_0x2AD5D078(int pram0, int pram1, int pram2)l
extern _native void unk_0xF82711CC(int pram0, int pram1, int pram2)l
extern _native void unk_0x92FE3677(int pram0, int pram1, int pram2)l
extern _native void unk_0xA72B6620(int pram0, int pram1, int pram2)l
extern _native void unk_0xBAC27559(int pram0, int pram1, int pram2)l
extern _native void ss_init(int pram0)l
extern _native int ss_set_table_size(int pram0, int pram1)l
extern _native void combat_class_name_register_int(int pram0, int pram1)l
extern _native void unk_0x0B396DFF(int pram0)l
extern _native void unk_0x24F3A0DB(int pram0)l
extern _native void unk_0x9FEFA743(int pram0)l
extern _native void ai_speech_register_event(int pram0, int pram1)l
extern _native void ai_speech_register_tags_begin(int pram0)l
extern _native void ai_speech_register_tag(int pram0, int pram1, int pram2, int pram3)l
extern _native void ai_speech_register_tags_end()l
extern _native int unk_0xE77F61B2(int pram0, int pram1)l
extern _native int ai_speech_add_phrase(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void ai_speech_add_tag_for_phrase(int pram0, int pram1, int pram2)l
extern _native void debug_player_log(int pram0)l
extern _native void unk_0x9953D4FC(int pram0)l
extern _native void unk_0x751809BB(int pram0)l
extern _native void unk_0x25A42C69(int pram0)l
extern _native void unk_0x86CB8CFB(int pram0)l
extern _native void unk_0xD6AD0016(int pram0)l
extern _native void unk_0x8C00C0BE(int pram0)l
extern _native void unk_0x7CC67B30(int pram0)l
extern _native void unk_0xD4ECD97D(int pram0)l
extern _native void unk_0x826BB889(int pram0)l
extern _native void unk_0x5473B93A(int pram0)l
extern _native void unk_0x1B1EFCCB(int pram0)l
extern _native void unk_0xD85BAFA8(int pram0)l
extern _native void unk_0xEB99D1A9(int pram0, int pram1, int pram2)l
extern _native void unk_0x3C6FE75D(int pram0, int pram1)l
extern _native void unk_0x7DA34015(int pram0, int pram1)l
extern _native void unk_0x79EFDF7E(int pram0, int pram1)l
extern _native void unk_0xCA669478(int pram0, int pram1)l
extern _native void unk_0x74E7F898(int pram0, int pram1)l
extern _native void get_lockon_mission(int pram0, int pram1)l
extern _native void unk_0xFCD2DE48(int pram0)l
extern _native void unk_0xB8F1D736(int pram0)l
extern _native void unk_0x30402375(int pram0)l
extern _native void unk_0x7922F870(int pram0)l
extern _native void unk_0x663723A0(int pram0)l
extern _native void unk_0x93CFB180(int pram0)l
extern _native void unk_0xA1FCBA24(int pram0)l
extern _native void unk_0x7ED8B78C()l
extern _native void unk_0xD4871BDB(int pram0)l
extern _native void unk_0xA88359B9(int pram0, int pram1)l
extern _native void unk_0xC65F6751(int pram0)l
extern _native void unk_0x83CBD612(int pram0)l
extern _native void unk_0x4AD2BC30(int pram0)l
extern _native void unk_0xA13D379B(int pram0, int pram1)l
extern _native void unk_0xC4C59CA4(int pram0)l
extern _native void unk_0xA915DC46(int pram0)l
extern _native void unk_0xBAD8B9A8(int pram0)l
extern _native void unk_0x6CBF76AB(int pram0)l
extern _native void unk_0x4F64116B(int pram0)l
extern _native void unk_0x0386C556(int pram0, int pram1, int pram2)l
extern _native void unk_0xE0DD373F(int pram0)l
extern _native void unk_0xF63FA0A1(int pram0)l
extern _native void unk_0x375BBD85(int pram0)l
extern _native void unk_0x4819FB7C(int pram0)l
extern _native void unk_0xC4F468AA(int pram0)l
extern _native void game_estimate_mount(int pram0)l
extern _native void unk_0xD6BBC8AA(int pram0)l
extern _native void unk_0x354DDFED(int pram0, int pram1)l
extern _native void unk_0x230AB95E(int pram0)l
extern _native void add_to_zone_allowed_gringo_type_list(int pram0, int pram1)l
extern _native void unk_0xC43C4D76(int pram0, int pram1)l
extern _native void unk_0xFCA83D15(int pram0, int pram1, int pram2)l
extern _native int unk_0x9189EB8B(int pram0)l
extern _native int unk_0x00CDD849(int pram0)l
extern _native int unk_0x6138B1B8(int pram0)l
extern _native void remove_glow_indicator(int pram0)l
extern _native int is_volume_enabled(int pram0)l
extern _native int count_flames_in_volume(int pram0)l
extern _native int unk_0x3B32AB84(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x3E30A514(int pram0, int pram1)l
extern _native int set_panim_params(int pram0, int pram1, int pram2)l
extern _native int get_current_duel_score(int pram0)l
extern _native int unk_0x26011C78(int pram0)l
extern _native int has_accessory_enum(int pram0, int pram1)l
extern _native void unk_0xD021B37F(int pram0)l
extern _native void unk_0x94A24A5C(int pram0)l
extern _native int begin_duel(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10, int pram11, int pram12)l
extern _native int unk_0x7FDDF876(int pram0, int pram1)l
extern _native int add_duel_hostage(int pram0, int pram1)l
extern _native void set_emotion(int pram0, int pram1, int pram2)l
extern _native int set_duel_difficulty(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xADCC16A2()l
extern _native int remove_event_response(int pram0, int pram1, int pram2)l
extern _native void clear_player_blood()l
extern _native void unk_0x9D9E093E(int pram0)l
extern _native void unk_0x338DF299()l
extern _native int is_actor_anim_phase_locked(int pram0)l
extern _native void release_actor_anim_phase_lock(int pram0)l
extern _native void unk_0xDE7C65CE()l
extern _native void unk_0x32F2D6F1(int pram0)l
extern _native void hud_timer_pause()l
extern _native void unk_0x7784BB85()l
extern _native int unk_0xD3A523FD(int pram0)l
extern _native void set_actor_anim_phase_lock(int pram0, int pram1)l
extern _native void unk_0x24AE7AFB()l
extern _native int unk_0xA091179F(int pram0, int pram1)l
extern _native void unk_0x0CCE435E(int pram0, int pram1, int pram2)l
extern _native void unk_0x87A2C1D5(int pram0)l
extern _native void ai_reset_nav_subgrid_cell_size(int pram0)l
extern _native int unk_0x544BCE48(int pram0, int pram1)l
extern _native void unk_0x4D629653(int pram0, int pram1, int pram2)l
extern _native int unk_0x9B083FD2()l
extern _native int get_physinst_velocity(int pram0, int pram1)l
extern _native float sqrt(float pram0)l
extern _native int get_actor_update_priority(int pram0)l
extern _native void hud_counter_set(int pram0)l
extern _native int exp(int pram0)l
extern _native int unk_0xD058BD70()l
extern _native int unk_0x4C48EA4D()l
extern _native int unk_0x35CDFDC5(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x8A2A1A51(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x581CAC89()l
extern _native int unk_0x79AFAB1F(int pram0, int pram1)l
extern _native int gui_make_overlay(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int unk_0xD019FF37(int pram0)l
extern _native int unk_0xA7FF2899(int pram0, int pram1, int pram2)l
extern _native GUIWindow gui_main_window()l
extern _native void unk_0x72168160(int pram0)l
extern _native int get_most_recent_rider(int pram0)l
extern _native void unk_0x8DEC3E03(int pram0)l
extern _native int unk_0x14708CB1()l
extern _native void unk_0x7A99E7DE()l
extern _native void unk_0x1D5E39A0()l
extern _native int gringo_query_float(int pram0, int pram1, int pram2, int pram3)l
extern _native int is_actor_inited(int pram0)l
extern _native void unk_0xA870B28E(int pram0, int pram1)l
extern _native int unk_0x9DDB29B1(int pram0)l
extern _native int unk_0x24A1B923()l
extern _native int decor_remove_all(int pram0)l
extern _native void unk_0x713B1D7F(int pram0, int pram1)l
extern _native int unk_0x34F03EC7(int pram0, int pram1, int pram2)l
extern _native void unk_0x573BEF3B(int pram0, int pram1)l
extern _native void ui_set_text_hash(int pram0, int pram1)l
extern _native void unk_0x50C18480(int pram0, int pram1)l
extern _native int unk_0x6A0A241A(int pram0)l
extern _native int net_get_nat_type()l
extern _native int unk_0xC1A30BB5()l
extern _native void unk_0x2C4CBC25(int pram0)l
extern _native int unk_0xF2140DEE(int pram0)l
extern _native void unk_0xBECB3EEC(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x98A5CDC5(int pram0)l
extern _native int unk_0x8808546E()l
extern _native int unk_0x1A47001B()l
extern _native int unk_0x0FF6B8F4()l
extern _native int net_session_leave_session()l
extern _native void unk_0xCE8F6304(int pram0)l
extern _native void unk_0x41921C98(int pram0)l
extern _native void unk_0xAB32D5D9(int pram0)l
extern _native int unk_0x75F27D60(int pram0)l
extern _native int unk_0x6A7B9FAD(int pram0)l
extern _native int unk_0x106CE441(int pram0)l
extern _native void unk_0xA64A451E(int pram0, int pram1)l
extern _native int unk_0xB514ECA7(int pram0, int pram1)l
extern _native int get_actor_combat_class(int pram0)l
extern _native void set_vehicle_passengers_allowed(int pram0, int pram1)l
extern _native void squads_merge(int pram0, int pram1)l
extern _native void unk_0x91BB8548(int pram0, int pram1)l
extern _native void set_volume_params(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native int unk_0x15D6F3C7(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x746897AB(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x0B24362F(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8)l
extern _native int get_player_control_config(int pram0)l
extern _native void unk_0x72B03551()l
extern _native void unk_0xE5FE0A6A(int pram0)l
extern _native void unk_0x08D84437(int pram0)l
extern _native void unk_0xAFFBBE78(int pram0)l
extern _native void unk_0xF34B8448(int pram0)l
extern _native void unk_0x796E66E7(int pram0)l
extern _native void unk_0x784F04DD(int pram0)l
extern _native void unk_0x3248D20E(int pram0)l
extern _native void unk_0xBC46E3E1(int pram0, int pram1, int pram2)l
extern _native void unk_0x2634F265(int pram0, int pram1)l
extern _native void unk_0xA0A5FF80(int pram0, int pram1)l
extern _native int unk_0x52C10147(int pram0)l
extern _native void unk_0x90008899(int pram0)l
extern _native int net_get_area_overload_state_for_slot(int pram0)l
extern _native int net_is_busy()l
extern _native int unk_0x63034F52(int pram0)l
extern _native int unk_0x2037A74F(int pram0)l
extern _native int unk_0x89D8FC30()l
extern _native int unk_0xE9EAC45C(int pram0)l
extern _native int unk_0xBDF22FCA(int pram0)l
extern _native int unk_0xA174152C(int pram0)l
extern _native int unk_0x0183A3F0(int pram0)l
extern _native int unk_0xF6E40FF3(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int net_is_faction_safe(int pram0)l
extern _native void unk_0x9EA132A3(int pram0)l
extern _native int gui_make_window(GUIWindow Parent, int pram1, const char* WindowName, const char* pram3)l
extern _native int unk_0x9180FF1C(int pram0)l
extern _native void unk_0x2F7B457B(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xC0849D70()l
extern _native int unk_0x8DF05A4F(int pram0)l
extern _native void unk_0x651F6299(int pram0)l
extern _native int unk_0x4A721118(int pram0)l
extern _native int unk_0x4500B98A(int pram0)l
extern _native int get_weapon_gold(Actor Actor, Weapon Weapon)l
extern _native int unk_0x3AE1062C()l
extern _native32(0xC666B987) bool _is_actor_ammo_infinite(Actor Actor, int pram1)l
extern _native void ready_item(const char* ItemName, Actor Actor)l
extern _native int unk_0x0B2D5E4B()l
extern _native int unk_0x2010ABE6()l
extern _native int unk_0xFA0E1F8B(int pram0)l
extern _native void unk_0xCB0BCAE2(int pram0)l
extern _native void disable_player_gringo_use(int pram0, int pram1)l
extern _native int unk_0x3A5C56E3(int pram0)l
extern _native void unk_0xCC7D0431(int pram0)l
extern _native void unk_0xF7B747CA()l
extern _native void unk_0x1184EC7B(int pram0)l
extern _native int unk_0x81FD9851()l
extern _native void unk_0x120E6123(int pram0)l
extern _native int unk_0x86FF3A9B()l
extern _native int unk_0xDC88B308()l
extern _native int unk_0xF5B7B208()l
extern _native int unk_0xBD269877(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0x43C5F320()l
extern _native void unk_0xAD85A378()l
extern _native void set_camera_focus_object(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void unk_0xEB214384(int pram0)l
extern _native int get_slot_facing(int pram0, int pram1)l
extern _native void unk_0x6E303287(int pram0, int pram1)l
extern _native32(0xB1A2028A) void _ui_enter_exclusive(char* scaleformLayer)l
extern _native void burn_actor(int pram0, int pram1, int pram2)l
extern _native int gringo_stay_active(int pram0, int pram1)l
extern _native int unk_0xD8218A5B()l
extern _native int unk_0x74EE96B8(int pram0)l
extern _native int unk_0x2374C1E0()l
extern _native void train_destroy_car(int pram0, int pram1)l
extern _native int train_get_nearest_poi_distance(int pram0)l
extern _native void unk_0x90DD37E7(int pram0, int pram1, int pram2)l
extern _native int ai_global_get_permanent_danger(int pram0)l
extern _native void destroy_crime(int pram0)l
extern _native int unk_0x72A048B7(int pram0)l
extern _native int get_crime_faction(int pram0)l
extern _native int unk_0x67F224B4(int pram0)l
extern _native int ai_self_defense_get_attacked_player_first(int pram0)l
extern _native int get_last_damage(int pram0)l
extern _native int get_journal_entry_progress(int pram0)l
extern _native int unk_0x91396EB7(int pram0)l
extern _native int fire_get_owner(int pram0)l
extern _native void unk_0x40C2576F(int pram0, int pram1)l
extern _native void unk_0xDF3DF05A(int pram0)l
extern _native int audio_is_scripted_music_playing()l
extern _native int get_actor_weapon_reaction_actor_type(int pram0)l
extern _native int unk_0xD19EFFC1(int pram0, int pram1)l
extern _native void hud_stamina_override(int pram0, int pram1, int pram2)l
extern _native int unk_0x6F513950(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int get_camera_shot_transition(int pram0)l
extern _native void set_fixed_transition_t(int pram0, int pram1)l
extern _native void animal_actor_set_docile(Actor Actor, bool Docile)l
extern _native void get_camera_up_vector(int pram0, int pram1)l
extern _native int cutsceneobject_add_transition_fixed(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native void unk_0xCA99D3B4()l
extern _native int sc_challenge_get_var_bool(int pram0, int pram1)l
extern _native int sc_challenge_get_var_float(int pram0, int pram1)l
extern _native void ui_challenge_create(int pram0, int pram1, int pram2)l
extern _native void ui_challenge_set_progress(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int sc_challenge_get_expiration_state(int pram0)l
extern _native void sc_challenge_process_expiration(int pram0)l
extern _native void sc_challenge_release(int pram0)l
extern _native int sc_challenge_get_leaderboard_id(int pram0, int pram1)l
extern _native void sc_challenge_clean_up(int pram0)l
extern _native void unk_0x9D9CDCE3(int pram0, int pram1)l
extern _native void unk_0xD5ED5FCB(int pram0, int pram1)l
extern _native void sc_challenge_reset_expiration_state(int pram0)l
extern _native int sc_challenge_is_active(int pram0)l
extern _native int sc_challenge_is_running(int pram0)l
extern _native int unk_0xBBF4F7E4()l
extern _native int unk_0xAFD53217(int pram0, int pram1, int pram2)l
extern _native int unk_0xB555A648(int pram0, int pram1, int pram2)l
extern _native int get_gringo_int_attr(int pram0, int pram1, int pram2)l
extern _native int set_gringo_int_attr(int pram0, int pram1, int pram2)l
extern _native int gringo_get_component_hash(int pram0)l
extern _native int unk_0xC15C3361(int pram0, int pram1)l
extern _native int unk_0xA766EA5C(int pram0, int pram1)l
extern _native int is_prop_streamed_in(int pram0)l
extern _native void grave_set_dug_up(int pram0, int pram1)l
extern _native int get_grave_from_object(int pram0)l
extern _native int unk_0x04507DBC(int pram0, int pram1)l
extern _native int unk_0x88F7432C(int pram0, int pram1)l
extern _native int get_actor_anim_current_time(int pram0, int pram1)l
extern _native int set_prop_velocity_on_axis(int pram0, int pram1, int pram2)l
extern _native int unk_0x3736FF43(int pram0)l
extern _native void unk_0xF95DDBF2(int pram0, int pram1)l
extern _native void unk_0x6BA667B5(int pram0)l
extern _native int unk_0xB8C419C3(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int is_actor_anim_playing(int pram0, int pram1)l
extern _native int unk_0x08D76BB0(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xA2DEC153(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native int is_vehicle_engine_running(int pram0)l
extern _native void set_vehicle_engine_running(Actor Vehicle, bool Running)l
extern _native int unk_0x6517FF1B(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int gringo_is_active(int pram0)l
extern _native void destroy_zone(int pram0)l
extern _native int unk_0x7E4681E8(int pram0, int pram1, int pram2)l
extern _native int gringo_actor_face(int pram0, int pram1, int pram2)l
extern _native int unk_0x217B4264(int pram0, int pram1, int pram2)l
extern _native int unk_0x3DEA631B(int pram0, int pram1)l
extern _native void push_minigame_input(int pram0, int pram1)l
extern _native void unk_0x8275FDD4(int pram0)l
extern _native int unk_0x6AAD0420(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0x655D350B(int pram0, int pram1, int pram2, int pram3)l
extern _native int set_object_animator_rate(int pram0, int pram1)l
extern _native int set_object_animator_phase(int pram0, int pram1)l
extern _native int is_minigame_running()l
extern _native int has_prop_been_damaged(int pram0)l
extern _native int create_object_animator(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x188B6431(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xB57D4110(int pram0, int pram1, int pram2)l
extern _native int unk_0x97951004(int pram0)l
extern _native int unk_0x325F7E50(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void unk_0x507BBD3A(int pram0, int pram1)l
extern _native void unk_0xC93116B1()l
extern _native int unk_0xEB33480A(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7)l
extern _native int unk_0xA9E00433(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5)l
extern _native void ai_set_disarmed(int pram0, int pram1)l
extern _native void lasso_event(int pram0, int pram1)l
extern _native void unk_0x96161235(int pram0)l
extern _native int unk_0x1AA3A0C0(int pram0, int pram1)l
extern _native void ai_global_report_danger(int pram0)l
extern _native int unk_0x6689F85C(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xEC28CA8E(int pram0, int pram1, int pram2)l
extern _native int unk_0xA332ACE3(int pram0, int pram1)l
extern _native void unk_0x3184B507()l
extern _native void unk_0x489B3078()l
extern _native void audio_play_pain(int pram0, int pram1)l
extern _native int gringo_actor_move_to(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0xC5205015(int pram0)l
extern _native int unk_0xADBF3ADF(int pram0)l
extern _native void unk_0x38636EBF(int pram0, int pram1)l
extern _native int unk_0x869D5D92(int pram0, int pram1, int pram2)l
extern _native int is_hogtie_cutfree_obstructed(int pram0, int pram1)l
extern _native void clear_hogtie_attach_victim(int pram0)l
extern _native int unk_0x60D10483(int pram0, int pram1)l
extern _native void set_hogtie_attach_victim(int pram0, int pram1)l
extern _native int get_faction_status_to_individual_actor(int pram0, int pram1)l
extern _native int unk_0xBCED635B(int pram0)l
extern _native int unk_0x9634D42E(int pram0, int pram1)l
extern _native int get_actor_posture(int pram0)l
extern _native void set_player_disable_targeting(int pram0, int pram1)l
extern _native void unk_0x6E86FCB5(int pram0, int pram1, int pram2)l
extern _native void unk_0x7BCE4845(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native void unk_0xD1C91A7F(int pram0, int pram1, int pram2, int pram3)l
extern _native void train_get_position(int pram0, int pram1)l
extern _native int unk_0x90B514B9(int pram0, int pram1, int pram2)l
extern _native void gringo_unload_animation(int pram0)l
extern _native void gringo_load_animation(int pram0)l
extern _native void camerashot_add_lookstick_rotation_behavior(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int unk_0xE782EB20(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9, int pram10)l
extern _native void unk_0x660DBDDD(int pram0)l
extern _native int gringo_query_int(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xDEE6523D(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x466C02BA(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xE9C74577(int pram0)l
extern _native int unk_0xF573B7DE(int pram0, int pram1)l
extern _native int get_gringo_struct_attr(int pram0, int pram1, int pram2, int pram3)l
extern _native int deactivate_actor_for_pers_char(int pram0)l
extern _native void task_wander_in_box(int pram0, int pram1, int pram2, int pram3)l
extern _native void task_guard_patrol_path(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native int gringo_query_string(int pram0, int pram1, int pram2, int pram3)l
extern _native int unk_0xF0991C9F(int pram0, int pram1)l
extern _native int unk_0x257C73C5(int pram0)l
extern _native int get_actor_height(int pram0)l
extern _native int unk_0xE9612679(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x67258116(int pram0, int pram1)l
extern _native void set_actor_is_shopkeeper(int pram0, int pram1, int pram2)l
extern _native int was_ai_actor_player_weapon_threatened_by(int pram0, int pram1, int pram2)l
extern _native int ai_has_actor_threatened_recently(int pram0)l
extern _native void unk_0x0B9AE52F(int pram0)l
extern _native void unk_0x5F4C08A2(int pram0)l
extern _native void dof_pop()l
extern _native void unk_0x3601E3E2(int pram0)l
extern _native int unk_0x5A12BB48()l
extern _native void unk_0xB84DE662(int pram0)l
extern _native void shop_refresh(int pram0)l
extern _native int unk_0x42CBA241(int pram0)l
extern _native int unk_0x1BF8FD6D(int pram0)l
extern _native int unk_0x94D8F49E(int pram0)l
extern _native void unk_0xB75FAD6A(int pram0)l
extern _native int unk_0xFAF37414(int pram0)l
extern _native void unk_0xA40EFFFF(int pram0, int pram1)l
extern _native int ss_get_string_id(int pram0, int pram1)l
extern _native int unk_0xB954DE78(int pram0)l
extern _native void unk_0x777CF9FA(int pram0, int pram1)l
extern _native void unk_0x7A34C33D(int pram0, int pram1)l
extern _native void shop_clear()l
extern _native int unk_0x2FCD8CCA(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6)l
extern _native void dof_push()l
extern _native int get_camerashot_far_clip_plane(int pram0)l
extern _native void dof_set(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0x47A8DDED(int pram0)l
extern _native int stringtable_length(int pram0)l
extern _native int train_is_valid(int pram0)l
extern _native void task_failure_mode_set(int pram0, int pram1)l
extern _native int horse_get_curr_freshness(int pram0)l
extern _native int get_actor_max_freshness(int pram0)l
extern _native void unk_0x9603D3B2(int pram0, int pram1)l
extern _native int unk_0x00EF33EF()l
extern _native int get_camera_fov(int pram0)l
extern _native void update_aimramp(int pram0, int pram1, int pram2, int pram3, int pram4)l
extern _native int unk_0x9BD37A3D(int pram0)l
extern _native int unk_0xDA50B18B(int pram0, int pram1)l
extern _native int unk_0x4062688A(int pram0)l
extern _native int unk_0xE13B49BD(int pram0)l
extern _native void unk_0x4486E8C7()l
extern _native int unk_0x55E6227E(int pram0, int pram1)l
extern _native void unk_0x02DB5C93(int pram0, int pram1, int pram2)l
extern _native void unk_0x8DD4BC60(int pram0)l
extern _native void unk_0xD5501B1B(int pram0, int pram1)l
extern _native void unk_0x1CB7C07D(int pram0)l
extern _native void unk_0x4C3F3C71(int pram0)l
extern _native void unk_0xAF7D851C()l
extern _native int unk_0x95132289()l
extern _native void unk_0x18D7E687(int pram0, int pram1, int pram2, int pram3)l
extern _native void unk_0xC3BE5695()l
extern _native void unk_0xF38E8BBE()l
extern _native void unk_0xBD829B6B()l
extern _native void unk_0x7306CC72(int pram0)l
extern _native void unk_0x9631DFD0(int pram0, int pram1, int pram2)l
extern _native void unk_0x3BED7D9F()l
extern _native void unk_0xEB8325B3(int pram0)l
extern _native void unk_0x77C8F279(int pram0)l
extern _native void unk_0x868E29C1(int pram0, int pram1)l
extern _native void unk_0xCEED74A5()l
extern _native void unk_0xE74C4851()l
extern _native void set_camerashot_control_sequence_vec3(int pram0, int pram1, int pram2, int pram3, int pram4, int pram5, int pram6, int pram7, int pram8, int pram9)l
extern _native void unk_0x382C47C5(int pram0)l
extern _native int get_task_next_point_on_path(int pram0, int pram1)l
extern _native int set_cutsceneinputs_target_guid(int pram0, int pram1, int pram2)l
extern _native int unk_0x8701F1F6()l
extern _native int unk_0xB5401D4A()l
extern _native int unk_0x80B30545()l
extern _native bool get_last_hit_zone(Actor Actor, int* out)l
extern _native const char* get_weapon_display_name(eWeapon WeaponID)l
extern _native Blip get_blip_on_object(Object Obj)l


/*---------------Undocumented Natives------------------
actor_has_anim_loaded
actor_is_hidden_by_cutscene
actor_set_max_gait
add_accessory
add_camera_shot_transition_ease_out
add_camera_shot_transition_hold
ai_action_is_active
ai_avoid_clear_ignore_actor
ai_dont_slow_down_to_walk_for_turns
ai_goal_aim_at_coord
ai_goal_shoot_at_object
ai_goal_stand_at_coord
ai_goal_stand_clear
ai_has_player_fired_gun_within
ai_reset_nav_actor_width
ai_riding_set_attribute
ai_set_enable_reaction_vo
ai_set_ignore_open_area_material
ai_set_nav_allow_tweak_desired_movement
ai_set_nav_max_slope
ai_shoot_target_clear_offset
ai_shoot_target_set_offset
animal_actor_get_docile
animal_species_add_external_path_attraction
animal_species_remove_external_path_attraction
append_journal_note
clear_actor_proof_all
clear_player_control_horse_follow
combat_class_ai_get_attrib_bool
combat_class_ai_set_fight_time_between_attacks_multiplier
create_corpse_variation_in_layout
detach_draft_from_vehicle_by_actor
estimate_distance_along_path
estimate_path_length
gateway_is_disabled
get_actor_max_speed
get_actor_min_speed
get_actor_vision_field_of_view
get_allow_ride
get_allow_ride_by_player
get_draw_object
get_max_speed
get_prop_health
grave_is_dug_up
gringo_force_update
gringo_set_money_presence
horse_auto_jump_enabled_for_ai_riders
horse_enable_auto_jump_for_ai_riders
is_actor_on_path
is_camera_focus_prompt_enabled
is_player_in_horse_follow
is_player_targetting_object
iterate_in_area
memory_allow_pickup_weapons
pause_scripted_conversation
remove_horse_accessory
restart_scripted_conversation
set_actor_frozen_after_corpsify
set_actor_min_speed_absolute
set_actor_movable_nav_mesh
set_actor_observed_targeted_reactions
set_actor_permanent
set_allow_lasso_mini_game
set_allow_melee_special_move
set_allow_ride
set_player_allow_pickup
set_player_cause_weapon_reactions
set_player_melee_mode_selected
set_player_vehicle_input
set_time_warp
squad_battle_allies_set_objective
squad_flock_event_boost_set_enabled
squad_flock_set_allow_stragglers
squad_flock_set_flocking_parameter
squad_follow_path_in_formation_set_behavior_flag
squad_follow_path_in_formation_set_desired_leader
squad_follow_path_in_formation_set_nonstop
squad_follow_path_in_formation_set_path
squad_follow_path_in_formation_set_speed
squad_follow_path_in_formation_set_speed_absolute
squad_follow_path_in_formation_set_speed_normalized
squad_goal_add_flock
squad_goal_add_follow_path_in_formation
streaming_set_custcene_mode
task_action_perform_at_position
task_animal_follow_aggressively
task_animal_hunt
task_bird_fly_near_coord
task_bird_soar
task_follow_and_attack_object_along_path
task_follow_path_from_point
task_go_to_coord_using_material
task_guard_patrol_auto
task_jump_over_obstruction
task_jump_to_object
task_shoot_enemies_from_preferred_cover
train_set_speed
set_corpse_permanent
set_radar_streaming
destroy_camera_shot
has_accessory
net_session_gamer_count
remove_physinst
is_prop_broken
is_using_turret
is_physinst_active
is_physinst_frozen
hud_timer_set
hud_timer_unpause
find_named_actorset
train_set_fx
leash_detatch_object
set_gringo_struct_attr
ui_disable_input
start_new_script
waitunwarped
waitunpaused
get_timestamp
task_divetoward
task_diveawayfrom
cancel_duel
get_actor_type
task_play_anim
start_new_script_with_args
set_camera_targetdof_focal_length
get_camerashot_up_vector
get_camerashot_x_vector
set_camerashot_target_object_bone
get_equip_slot_enabled
create_corpse_variation_in_layout_random
set_actor_react_to_lasso
task_be_dead
task_be_dead_random
task_bird_land
task_door_action
task_warn_char
task_action_perform_on_target
task_follow_object_in_formation
task_ledge_action
task_seek_cover_from_coord
task_simple_behavior
task_stealth_attack
task_tr_action
task_tr_action_on_actor
task_use_gringo_group
squad_flock_set_bool_flocking_parameter
squad_follow_traffic_curve_get_all_behavior_flags
squad_follow_traffic_curve_set_all_behavior_flags
squad_follow_traffic_curve_get_behavior_flag
squad_follow_traffic_curve_set_speed
squad_follow_traffic_curve_set_speed_absolute
squad_follow_traffic_curve_set_speed_normalized
squad_follow_traffic_curve_set_offset_x
squad_follow_traffic_curve_set_desired_leader
squad_follow_traffic_curve_clear_desired_leader
squad_follow_path_in_formation_get_all_behavior_flags
squad_follow_path_in_formation_set_all_behavior_flags
squad_follow_path_in_formation_get_behavior_flag
squad_follow_path_in_formation_set_task_priority
squad_follow_path_in_formation_set_offset_x
squad_follow_path_in_formation_clear_desired_leader
squad_follow_traffic_curve_set_curve
squad_goal_add_follow_object_in_formation
ai_get_nav_actor_avoidance_allow_turns
ai_get_nav_allow_tweak_desired_movement
ai_set_nav_unalerted_prefer_pedpath
ai_goal_look_at_player_when_within_clear
is_ai_actor_performing_task
ai_self_defense_get_player_attacked_first
ai_self_defense_set_player_attacked_first
ai_get_ignore_open_area_material
ai_was_pushed_over_by
memory_get_weapon_draw_preference
memory_set_unarmed_retreat
set_prop_no_fade
streaming_load_all_requests_now
set_deadeye_time_limit
set_wagon_to_wagon_jack_enable
toggle_cover_prop
detach_draft_from_vehicle_by_index
net_get_overload_state_for_slot
get_faction_is_lawful_to_attack
is_physinst_hide
set_actor_stamina
set_physinst_hide
debug_draw_line
debug_draw_string
debug_draw_vector
debug_draw_sphere
find_closest_door
create_named_population_set
create_event_trap
create_object_animator_on_object
create_gateway_type
create_leash_object
create_obstacle_on_object
create_fire_on_object
gringo_is_prop_ready
is_actor_on_ladder
is_actor_draft_vehicle
is_actor_hogtie_attached
is_actor_being_dragged
reset_vehicle_bump_count
reset_props_in_volume
leash_detach_object
decor_get_string_hash
is_object_animator_valid
is_object_animator_ready
is_vehicle_allowed_to_drive
is_local_player_valid
is_script_use_context_valid
is_pers_char_valid
is_door_opened
is_object_in_volume
is_actor_in_room
set_zone_population_count
set_zone_population_density
get_object_from_actor
get_object_from_crime
get_object_from_event
get_object_from_volume
get_object_from_gringo
get_object_from_objectset
get_object_from_pers_char
get_object_from_physinst
get_object_from_animator
get_object_from_squad
get_object_animator_on_object
get_object_animator_phase
get_object_model_name
destroy_pers_char
release_script_use_context
add_script_use_context
get_actor_from_actorset
get_actor_enum_string
get_actor_enum_faction
get_actor_drafted_to
release_pers_char
set_actor_to_seat
get_local_player_name
get_system_time
get_last_hit_flags
get_last_hit_weapon
get_camera_from_object
get_blip_on_object
get_camera_aspect_ratio
get_population_set_name
get_factions_status
get_weapon_max_ammo
get_weapon_in_hand
get_weapon_fragment_name
set_camera_follow_actor
net_is_session_client
cutscene_manager_load_cutscene
cutscene_manager_load_cutfile
cutscene_manager_hide_actor
cutscene_manager_unload_cutscene
cutscene_manager_play_cutscene
cutscene_manager_stop_cutscene
cutscene_manager_show_actor
hide_child_sector
show_child_sector
prepend_journal_entry
net_get_gamer_posse_size
net_get_gamer_posse_leader
net_get_session_gamer_count
enable_game_camera_focus
disable_game_camera_focus
shop_add_item
shop_get_item_quantity
shop_set_player_bank
shop_set_item_quantity
shop_is_sell_selected
create_fire_property
is_actor_crouching
is_actor_blindfiring
set_actor_stop_update
get_actor_stop_update
is_display_widescreen
is_player_teleporting
is_seat_occupied
net_session_set_invitable
net_session_start_gameplay
net_session_end_gameplay
get_game_edition
get_fire_property
get_event_perpetrator
get_actor_incapacitated
ui_label_set_text
get_last_frame_time
get_last_attack_time
get_last_attack_target
ui_label_set_value
get_corpse_actor_enum
get_blip_on_actor
fire_set_max_flames
flash_set_bool
flash_set_float
flash_get_bool
flash_get_float
flash_set_array_int
flash_set_array_string
net_posse_remove_gamer
flash_set_extent_bool
is_actor_inside_vehicle
can_actor_hogtie_target
set_game_camera_focus
create_actorset_in_layout
create_point_in_layout
create_volume_in_layout
create_gringo_in_layout
create_propset_in_layout
create_path_in_layout
create_squad_in_layout
create_formation_in_layout
create_crime_in_layout
create_objectset_in_layout
create_gateway_in_layout
create_camera_in_layout
create_camerashot_in_layout
create_aimramp_in_layout
create_cutsceneobject_in_layout
get_prop_from_object
get_crime_from_object
get_event_from_object
get_physinst_from_actor
get_physinst_from_object
get_iterator_from_object
get_curve_from_object
get_volume_from_object
get_squad_from_object
get_objectset_from_object
set_prop_cause_arm_up
ai_get_nav_failsafe_movement_enabled
ai_set_tr_program_for_actor
animal_species_tuning_get_attrib_float
get_journal_entry_detail_style_by_hash
set_actor_low_drop_damage
set_actor_medium_drop_damage
set_actor_high_drop_damage
set_actor_fly_fx
turn_actor_into_zombie
set_door_lock_visible
set_actor_base_score
set_actor_allow_disarm



*/

#undef _native
#undef _native32
#undef l