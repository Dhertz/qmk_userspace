// Copyright 2022 Dan Hertz (@dhertz)
// SPDX-License-Identifier: GPL-3.0

#include "dhertz.h"

uint32_t current_default_layer = (1 << 0);

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

__attribute__ ((weak))
void action_function_keymap(keyrecord_t *record, uint8_t id, uint8_t opt) {}

// Call user matrix init, then call the keymap's init function
void matrix_init_user(void) {
  matrix_init_keymap();
}

// No global matrix scan code, so just run keymap's matix
// scan function
void matrix_scan_user(void) {
  matrix_scan_keymap();
}

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
            break;
        case CMD_SFT_RBR_CMD:
            mod_or_mod_with_macro(record, KC_LGUI, SS_LSFT("]"));
            break;
        case CTL_TAB_CTL:
            mod_or_mod_with_macro(record, KC_RCTL, SS_TAP(X_TAB));
            break;
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
            case CTRL_A:
                SEND_STRING(SS_LCTL("a"));
                break;
            case CMD_ALT_C:
                SEND_STRING(SS_LGUI(SS_LALT("c")));
                break;
            case CMD_SFT_L:
                SEND_STRING(SS_LGUI("L"));
                break;
            case CMD_SFT_A:
                SEND_STRING(SS_LGUI("A"));
                break;
            case CMD_SFT_ALT_A:
                SEND_STRING(SS_LGUI(SS_LALT("A")));
                break;
            case SCRNSHT:
                SEND_STRING(SS_LGUI(SS_LSFT("4")));
                break;
            case NUBS_GRV:
                if (current_default_layer == (1 << 1)) {
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

void led_set_user(uint8_t usb_led) {
   led_set_keymap(usb_led);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    current_default_layer = state;
    return state;
}

