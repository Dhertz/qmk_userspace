// Copyright 2022 Dan Hertz (@dhertz)
// SPDX-License-Identifier: GPL-3.0

#include "dhertz.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {}

#ifdef RGB_MATRIX_ENABLE
static uint8_t custom_brightness = 64;
#endif

#ifdef DEFERRED_EXEC_ENABLE
uint32_t cancel_cmd(uint32_t trigger_time, void *cb_arg) {
    if (get_highest_layer(layer_state|default_layer_state) > 0) {
        return 20;
    }
    unregister_code(KC_LCMD);
    return 0;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CMD_TAB_CMD:
            mod_or_mod_with_macro(record, KC_LGUI, SS_TAP(X_TAB));
            return false;
        case CMD_GRV_CMD:
            mod_or_mod_with_macro(record, KC_RGUI, SS_TAP(X_GRAVE));
            return false;
        case CMD_SFT_LBR_CMD:
            mod_or_mod_with_macro(record, KC_LGUI, SS_LSFT("["));
            return false;
        case CMD_SFT_RBR_CMD:
            mod_or_mod_with_macro(record, KC_LGUI, SS_LSFT("]"));
            return false;
        case CTL_TAB_CTL:
            mod_or_mod_with_macro(record, KC_RCTL, SS_TAP(X_TAB));
            return false;
    }

    if (record->event.pressed) {
        switch(keycode) {
            case HSH_TLD:
                if (get_mods()&(MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))) {
                    SEND_STRING(SS_TAP(X_NONUS_BACKSLASH));
                } else {
                    SEND_STRING(SS_LALT("3"));
                }
                break;
            case HSH_TLD_1:
                if (get_mods()&(MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))) {
                    SEND_STRING(SS_TAP(X_GRV));
                } else {
                    SEND_STRING(SS_LALT("3"));
                }
                break;
            case CMD_ALT_C:
                SEND_STRING(SS_LGUI(SS_LALT("c")));
                break;
            case CMD_SFT_L:
                SEND_STRING(SS_LGUI("L"));
                break;
            case CMD_SFT_ALT_A:
                SEND_STRING(SS_LGUI(SS_LALT("A")));
                break;
            case SCRNSHT:
                SEND_STRING(SS_LGUI(SS_LSFT("4")));
                break;
            case ENC_CW:
                if (get_highest_layer(layer_state|default_layer_state) == 1 &&
                    (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) {
#ifdef RGB_MATRIX_ENABLE
                    if (custom_brightness < 240) {
                        custom_brightness += 15;
                    } else {
                        custom_brightness = 255;
                    }
#endif
                } else {
#ifdef DEFERRED_EXEC_ENABLE
                    if ((get_mods() & MOD_BIT(KC_LCMD)) != MOD_BIT(KC_LCMD)) {
                        register_code(KC_LCMD);
                        defer_exec(20, cancel_cmd, NULL);
                    }
#endif
                    tap_code(KC_TAB);
                }
                break;
            case ENC_CCW:
                if (get_highest_layer(layer_state|default_layer_state) == 1 &&
                    (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) {
#ifdef RGB_MATRIX_ENABLE
                    if (custom_brightness > 15) {
                        custom_brightness -= 15;
                    } else {
                        custom_brightness = 0;
                    }
#endif
                } else {
#ifdef DEFERRED_EXEC_ENABLE
                    if ((get_mods() & MOD_BIT(KC_LCMD)) != MOD_BIT(KC_LCMD)) {
                        register_code(KC_LCMD);
                        defer_exec(20, cancel_cmd, NULL);
                    }
#endif
                    tap_code16(S(KC_TAB));
                }
                break;
            case NUBS_GRV:
                if (default_layer_state == (1 << 1)) {
                    tap_code(KC_NUBS);
                } else {
                    tap_code(KC_GRV);
                }
                break;
            default:
                return process_record_keymap(keycode, record);
        }
        return false;
    }
    return process_record_keymap(keycode, record);
}

static uint16_t sunds_timer;

void mod_or_mod_with_macro(keyrecord_t *record, uint16_t kc_mod, char* macro) {
    if (record->event.pressed) {
        sunds_timer = timer_read();
        register_code(kc_mod);
    } else {
        if (timer_elapsed(sunds_timer) < TAPPING_TERM) {
            send_string(macro);
        }
        unregister_code(kc_mod);
    }
}

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(RGB_AZURE);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    keyboard_post_init_keymap();
}

bool rgb_matrix_indicators_user(void) {
    uint8_t scaled_r, scaled_g, scaled_b;

    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 1:
            scaled_r = (0x7A * custom_brightness) / 255;
            scaled_g =  0x00;
            scaled_b = (0x7F * custom_brightness) / 255;
            rgb_matrix_set_color_all(scaled_r, scaled_g, scaled_b);
            break;
        default:
            scaled_r = (0x99 * custom_brightness) / 255;
            scaled_g = (0xF5 * custom_brightness) / 255;
            scaled_b = (0xFF * custom_brightness) / 255;
            rgb_matrix_set_color_all(scaled_r, scaled_g, scaled_b);
            break;
    }
    return false;
}
#elif defined(RGBLIGHT_ENABLE)
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv(HSV_TEAL);
    keyboard_post_init_keymap();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
        default:
            rgblight_sethsv_noeeprom(HSV_TEAL);
            break;
    }
    return state;
}
#else
void keyboard_post_init_user(void) {
    keyboard_post_init_keymap();
}
#endif
