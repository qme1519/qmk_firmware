/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#define TAPPING_TERM 200

#include "cat.h"

enum layer_names {
    _QWERTY,
    _SPECIAL,
    _SYSTEM
};

static uint16_t current_keycode = KC_NO;
static uint8_t current_mods = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /Tab (1)/       \Enter \  |Space(2)|      |      |      |
 *            |      |      |      |      |/       /         \      \ |        |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
    KC_ESC,     KC_1,               KC_2,               KC_3,               KC_4,               KC_5,                               KC_6,               KC_7,               KC_8,               KC_9,                 KC_0,        KC_MINS,
    KC_TAB,     KC_Q,               KC_W,               KC_E,               KC_R,               KC_T,                               KC_Y,               KC_U,               KC_I,               KC_O,                 KC_P,        KC_BACKSLASH,
    CW_TOGG,    MT(MOD_LGUI, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LSFT, KC_D), MT(MOD_LCTL, KC_F), KC_G,                               KC_H,               MT(MOD_RCTL, KC_J), MT(MOD_RSFT, KC_K), MT(MOD_RALT, KC_L),   MT(MOD_RGUI, KC_SCLN),   KC_QUOT,
    KC_NO,      KC_Z,               KC_X,               KC_C,               KC_V,               KC_B,      KC_MUTE,       KC_MPLY,  KC_N,               KC_M,               KC_COMM,            KC_DOT,               KC_SLSH,     KC_NO,
                                    KC_NO,              KC_NO,              KC_NO,              KC_BSPC,   LT(1, KC_TAB), KC_ENT,   LT(2, KC_SPC),      KC_NO,              KC_NO,              KC_NO    
),

/*
 * Special chars
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   +  |   =  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   `  |   {  |   [  |   (  |   -  |-------.    ,-------|   _  |   )  |   ]  |   }  |   ~  |  \   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |-------|    |-------|   6  |   7  |   8  |   9  |   0  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_SPECIAL] = LAYOUT(
    KC_NO,      KC_F1,              KC_F2,                 KC_F3,              KC_F4,              KC_F5,                            KC_F6,                 KC_F7,              KC_F8,              KC_F9,                 KC_F10,                 KC_NO,
    KC_NO,      KC_EXLM,            KC_AT,                 KC_HASH,            KC_DLR,             KC_PERC,                          KC_CIRC,               KC_AMPR,            KC_ASTR,            KC_PLUS,               KC_EQL,                 KC_NO,
    KC_NO,      KC_GRV,             S(KC_LBRC),            KC_LBRC,            S(KC_9),            KC_MINS,                          S(KC_MINS),            S(KC_0),            KC_RBRC,            S(KC_RBRC),            S(KC_GRV),              KC_BACKSLASH,
    KC_NO,      KC_1,               KC_2,                  KC_3,               KC_4,               KC_5,      KC_NO,         KC_NO,  KC_6,                  KC_7,               KC_8,               KC_9,                  KC_0,                   KC_NO,
                                    KC_NO,                 KC_NO,              KC_NO,              KC_NO,     KC_NO,         KC_NO,  KC_NO,                 KC_NO,              KC_NO,              KC_NO    
),

/*
 * System keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Reset|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | PgUp | Home |  Up  | End  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |  Del |      |-------.    ,-------| Pgdn | Left | Down | Right|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | Prev | Next |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_SYSTEM] = LAYOUT(
    QK_BOOT,    KC_NO,    KC_NO,     KC_NO,    KC_NO,        KC_NO,                            KC_NO,            KC_NO,                                     KC_NO,                         KC_NO,          KC_NO,     KC_NO,
    KC_NO,      KC_NO,    KC_NO,     KC_NO,    KC_NO,        KC_NO,                            KC_PAGE_UP,       KC_HOME,                                   KC_UP,                         KC_END,         KC_NO,     KC_NO,
    KC_NO,      KC_NO,    KC_NO,     KC_NO,    KC_DEL,       KC_NO,                            KC_PAGE_DOWN,     KC_LEFT,                                   KC_DOWN,                       KC_RIGHT,       KC_NO,     KC_NO,
    KC_NO,      KC_NO,    KC_NO,     KC_NO,    KC_NO,        KC_NO,     KC_NO,         KC_NO,  KC_NO,            C(S(KC_TAB)),                              C(KC_TAB),                     KC_NO,          KC_NO,     KC_NO,
                          KC_NO,     KC_NO,    KC_NO,        KC_NO,     KC_NO,         KC_NO,  KC_NO,            KC_NO,                                     KC_NO,                         KC_NO    
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
};
#endif

#ifdef OLED_ENABLE

const char *keycode_to_string(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            static char name[2];
            name[0] = 'A' + (keycode - KC_A);
            name[1] = '\0';
            return name;

        case KC_1 ... KC_9:
            static char num[2];
            num[0] = '1' + (keycode - KC_1);
            num[1] = '\0';
            return num;

        case KC_0:
            return "0";
        case KC_ENTER:
            return "ENTER";
        case KC_ESC:
            return "ESC";
        case KC_SPACE:
            return "SPACE";
        case KC_TAB:
            return "TAB";
        case KC_BSPC:
            return "BSPC";
        case KC_LSFT:
        case KC_RSFT:
            return "SHIFT";
        case KC_LCTL:
        case KC_RCTL:
            return "CTRL";
        default:
            return "----";
    }
}

// Helper: map Mod-Tap keycode to its modifier
uint8_t keycode_to_mods(uint16_t keycode) {
    switch (keycode) {
        case MT(MOD_LCTL, KC_F): return MOD_BIT(KC_LCTL);
        case MT(MOD_LSFT, KC_D): return MOD_BIT(KC_LSFT);
        case MT(MOD_LALT, KC_S): return MOD_BIT(KC_LALT);
        case MT(MOD_LGUI, KC_A): return MOD_BIT(KC_LGUI);
        case MT(MOD_RCTL, KC_J): return MOD_BIT(KC_RCTL);
        case MT(MOD_RSFT, KC_K): return MOD_BIT(KC_RSFT);
        case MT(MOD_RALT, KC_L): return MOD_BIT(KC_RALT);
        case MT(MOD_RGUI, KC_SEMICOLON): return MOD_BIT(KC_RGUI);
        default: return 0;
    }
}


static void print_status_narrow(void) {
         // Print current mode
     oled_write_P(PSTR("\n"), false);

     oled_write_ln_P(PSTR("Jakub"), false);
     oled_write_ln_P(PSTR("-----"), false);

    //  switch (get_highest_layer(default_layer_state)) {
    //      case _QWERTY:
    //          oled_write_ln_P(PSTR("Qwrt"), false);
    //          break;
    //      default:
    //          oled_write_ln_P(PSTR("Undef"), false);
    //  }

     oled_write_P(PSTR("\n"), false);
     // Print current layer
     oled_write_ln_P(PSTR("LAYER"), false);

     switch (get_highest_layer(layer_state)) {
         case _QWERTY:
             oled_write_ln_P(PSTR("Base"), false);
             break;
         case _SPECIAL:
             oled_write_ln_P(PSTR("Spec"), false);
             break;
         case _SYSTEM:
             oled_write_ln_P(PSTR("Sys"), false);
             break;
         default:
             oled_write_ln_P(PSTR("Undf"), false);
     }

     // Host Keyboard LED Status
     led_t led_state = host_keyboard_led_state();
     oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
     oled_write_ln_P(PSTR("Key:"), false);
    if (current_mods) {
        if (current_mods & MOD_MASK_SHIFT) oled_write_ln_P(PSTR("Shift"), false);
        else if (current_mods & MOD_MASK_CTRL) oled_write_ln_P(PSTR("Ctrl"), false);
        else if (current_mods & MOD_MASK_ALT) oled_write_ln_P(PSTR("Alt"), false);
        else if (current_mods & MOD_MASK_GUI) oled_write_ln_P(PSTR("Gui"), false);
    } else if (current_keycode != KC_NO) {
        oled_write_ln(keycode_to_string(current_keycode), false);
    }
 }

 // === QMK OLED API function ===
 // Called at the start of oled_init, weak function overridable by the user
 oled_rotation_t oled_init_user(oled_rotation_t rotation) {
     if (is_keyboard_master()) {
         return OLED_ROTATION_270; // vertical for master
        }
    else {
        return OLED_ROTATION_180;   // horizontal for slave
    }
    }
    

    // === QMK OLED API function ===
    // Called at the start of oled_task, weak function overridable by the user
 bool oled_task_user(void) {
     if (is_keyboard_master()) {
         print_status_narrow();
     } else {
         oled_render_anim();
     }
     return false;
 }

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        current_keycode = keycode; // store the key that was just pressed
    } else {
        current_keycode = KC_NO; // clear when released
    }
    current_mods = get_mods(); // always track actual active modifiers
    return true;
}
