// OneOS - simple UI string localization
//
// Switch language by writing one of:
//   en, ja, zh_cn, zh_tw, ko
// to <SHARED_USERDATA_PATH>/lang.txt

#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "lang.h"

Lang lang;

#define FONT_JP RES_PATH "/NotoSansCJKjp-Bold.otf"
#define FONT_SC RES_PATH "/NotoSansCJKsc-Bold.otf"
#define FONT_TC RES_PATH "/NotoSansCJKtc-Bold.otf"
#define FONT_KR RES_PATH "/NotoSansCJKkr-Bold.otf"

static const Lang lang_en = {
	.font_path    = FONT_JP, // jp variant has full Latin coverage
	.resume       = "RESUME",
	.brightness   = "BRIGHTNESS",
	.volume       = "VOLUME",
	.continue_    = "Continue",
	.save         = "Save",
	.load         = "Load",
	.options      = "Options",
	.quit         = "Quit",
	.reset        = "Reset",
	.frontend     = "Frontend",
	.emulator     = "Emulator",
	.controls     = "Controls",
	.shortcuts    = "Shortcuts",
	.save_changes = "Save Changes",
	.save_state   = "Save State",
	.load_state   = "Load State",
};

static const Lang lang_ja = {
	.font_path    = FONT_JP,
	.resume       = "再開",
	.brightness   = "明るさ",
	.volume       = "音量",
	.continue_    = "続ける",
	.save         = "セーブ",
	.load         = "ロード",
	.options      = "設定",
	.quit         = "終了",
	.reset        = "リセット",
	.frontend     = "本体",
	.emulator     = "エミュ",
	.controls     = "操作",
	.shortcuts    = "ショートカット",
	.save_changes = "保存",
	.save_state   = "状態保存",
	.load_state   = "状態読込",
};

// Simplified Chinese (中国大陆 / Mainland China, Singapore)
static const Lang lang_zh_cn = {
	.font_path    = FONT_SC,
	.resume       = "继续",
	.brightness   = "亮度",
	.volume       = "音量",
	.continue_    = "继续",
	.save         = "保存",
	.load         = "读取",
	.options      = "选项",
	.quit         = "退出",
	.reset        = "重置",
	.frontend     = "系统",
	.emulator     = "模拟器",
	.controls     = "控制",
	.shortcuts    = "快捷键",
	.save_changes = "保存",
	.save_state   = "存档",
	.load_state   = "读档",
};

// Traditional Chinese (台灣 / Taiwan, Hong Kong)
static const Lang lang_zh_tw = {
	.font_path    = FONT_TC,
	.resume       = "繼續",
	.brightness   = "亮度",
	.volume       = "音量",
	.continue_    = "繼續",
	.save         = "儲存",
	.load         = "載入",
	.options      = "選項",
	.quit         = "結束",
	.reset        = "重設",
	.frontend     = "系統",
	.emulator     = "模擬器",
	.controls     = "控制",
	.shortcuts    = "快捷鍵",
	.save_changes = "儲存",
	.save_state   = "存檔",
	.load_state   = "讀檔",
};

// Spanish (Español)
static const Lang lang_es = {
	.font_path    = FONT_JP, // jp variant has full Latin coverage
	.resume       = "REANUDAR",
	.brightness   = "BRILLO",
	.volume       = "VOLUMEN",
	.continue_    = "Continuar",
	.save         = "Guardar",
	.load         = "Cargar",
	.options      = "Opciones",
	.quit         = "Salir",
	.reset        = "Reiniciar",
	.frontend     = "Sistema",
	.emulator     = "Emulador",
	.controls     = "Controles",
	.shortcuts    = "Atajos",
	.save_changes = "Guardar",
	.save_state   = "Guardar est.",
	.load_state   = "Cargar est.",
};

// French (Français)
static const Lang lang_fr = {
	.font_path    = FONT_JP, // jp variant has full Latin coverage
	.resume       = "REPRENDRE",
	.brightness   = "LUMINOSITÉ",
	.volume       = "VOLUME",
	.continue_    = "Continuer",
	.save         = "Sauver",
	.load         = "Charger",
	.options      = "Options",
	.quit         = "Quitter",
	.reset        = "Reset",
	.frontend     = "Système",
	.emulator     = "Émulateur",
	.controls     = "Commandes",
	.shortcuts    = "Raccourcis",
	.save_changes = "Sauver",
	.save_state   = "Sauv. état",
	.load_state   = "Charg. état",
};

// Korean (한국어)
static const Lang lang_ko = {
	.font_path    = FONT_KR,
	.resume       = "재개",
	.brightness   = "밝기",
	.volume       = "음량",
	.continue_    = "계속",
	.save         = "저장",
	.load         = "로드",
	.options      = "설정",
	.quit         = "종료",
	.reset        = "재시작",
	.frontend     = "본체",
	.emulator     = "에뮬",
	.controls     = "조작",
	.shortcuts    = "단축키",
	.save_changes = "저장",
	.save_state   = "상태저장",
	.load_state   = "상태로드",
};

void Lang_init(void) {
	lang = lang_en; // default

	FILE* f = fopen(SHARED_USERDATA_PATH "/lang.txt", "r");
	if (!f) return;

	char code[16] = {0};
	if (fgets(code, sizeof(code), f)) {
		// strip trailing whitespace/newlines
		for (int i = (int)strlen(code) - 1; i >= 0; i--) {
			if (code[i] == '\n' || code[i] == '\r' || code[i] == ' ' || code[i] == '\t') code[i] = '\0';
			else break;
		}
		if (strcmp(code, "ja") == 0)         lang = lang_ja;
		else if (strcmp(code, "zh_cn") == 0) lang = lang_zh_cn;
		else if (strcmp(code, "zh_tw") == 0) lang = lang_zh_tw;
		else if (strcmp(code, "ko") == 0)    lang = lang_ko;
		else if (strcmp(code, "es") == 0)    lang = lang_es;
		else if (strcmp(code, "fr") == 0)    lang = lang_fr;
	}
	fclose(f);
}
