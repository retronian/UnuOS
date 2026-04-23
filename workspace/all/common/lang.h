// UnuUI - simple UI string localization
// To switch language: write "en", "ja", "zh_cn", "zh_tw", or "ko" to
// SHARED_USERDATA_PATH/lang.txt
//
// Per-language Noto Sans CJK font is selected automatically so the script
// renders with its native glyph forms (jp/sc/tc/kr).

#ifndef __LANG_H__
#define __LANG_H__

typedef struct {
	// font path for this language (full path under RES_PATH)
	const char* font_path;
	// libretro language id (enum retro_language), used to query localized core options
	int retro_lang;
	// button labels (api.c, minui.c) — upper case in upstream
	const char* resume;
	const char* brightness;
	const char* volume;
	const char* power;
	const char* sleep;
	const char* info;
	const char* back;
	const char* okay;
	const char* open;
	// status / messages (minui.c)
	const char* empty_folder;
	// root entries (minui.c)
	const char* recently_played;
	const char* collections;
	const char* tools;
	const char* settings;
	const char* language;
	// in-game menu (minarch.c top-level)
	const char* continue_;
	const char* save;
	const char* load;
	const char* options;
	const char* quit;
	const char* reset;
	// in-game options menu (minarch.c)
	const char* frontend;
	const char* emulator;
	const char* controls;
	const char* shortcuts;
	const char* save_changes;
	// shortcut names (minarch.c)
	const char* save_state;
	const char* load_state;
	const char* reset_game;
	const char* save_quit;
	const char* cycle_scale;
	const char* cycle_effect;
	const char* toggle_ff;
	const char* hold_ff;
	// messages (minarch.c, api.c)
	const char* no_core_options;       // "This core has no options."
	const char* empty_slot;            // "Empty Slot"
	const char* using_defaults;        // "Using defaults."
	const char* using_console_cfg;     // "Using console config."
	const char* using_game_cfg;        // "Using game config."
	// frontend option names (minarch.c)
	const char* fe_screen_scaling;
	const char* fe_screen_effect;
	const char* fe_screen_sharpness;
	const char* fe_prevent_tearing;
	const char* fe_cpu_speed;
	const char* fe_prioritize_audio;
	const char* fe_debug_hud;
	const char* fe_max_ff_speed;
	// frontend option descriptions (minarch.c). scaling has two variants
	// depending on whether cropped mode is available on the device.
	const char* fe_desc_scaling_short;
	const char* fe_desc_scaling_full;
	const char* fe_desc_effect;
	const char* fe_desc_sharpness;
	const char* fe_desc_tearing;
	const char* fe_desc_cpu;
	const char* fe_desc_audio;
	const char* fe_desc_debug;
	const char* fe_desc_maxff;
	const char* fe_desc_language;
	// controls/shortcuts menu hint (minarch.c)
	const char* press_a_to_set_x_to_clear;
	// save-changes submenu (minarch.c)
	const char* save_for_console;
	const char* save_for_game;
	const char* restore_defaults;
	const char* powering_off;          // "Powering off"
	const char* power_off_now;         // "Power off now"
	const char* quicksave_powering_off;// "Quicksave created,\npowering off"
	const char* quicksave_power_off_now; // "Quicksave created,\npower off now"
	// Tools menu entries (.pak directory names, minui.c)
	const char* tool_adbd;
	const char* tool_bootlogo;
	const char* tool_clock;
	const char* tool_files;
	const char* tool_input;
	const char* tool_ip;
	const char* tool_remove_loading;
	const char* tool_toggle_560p;
} Lang;

extern Lang lang;

void Lang_init(void);

#endif
