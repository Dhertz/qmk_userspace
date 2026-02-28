// Copyright 2022 Dan Hertz (@dhertz)
// SPDX-License-Identifier: GPL-3.0

#include QMK_KEYBOARD_H
#include "dhertz.h"

static bool dip_switch_state[NUM_DIP_SWITCHES] = {0};

enum keyboard_keycodes {
    GRV_NUBS_DIP = NEW_SAFE_RANGE,
    NUBS_GRV_DIP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp|( )|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter|Del|
     * |------------------------------------------------------`    |---|
     * |SrCtl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |Hom|
     * |---------------------------------------------------------------|
     * |Shif|  #|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |   |
     * |---------------------------------------------------------------|
     * |NcCtl|  Alt| CTab|       LyrSpc        |CGv|Alt|CSa|Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
  [0] = LAYOUT_iso_68(
      KC_ESC, KC_1,  KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
      KC_TAB,  KC_Q,  KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_DEL,
      SRCH_CTL,   KC_A,  KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT, KC_HOME,
      KC_LSFT, HSH_TLD_1, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
      NC_CTL, KC_LALT, CMD_TAB_CMD, LYR_SPC, CMD_GRV_CMD, KC_RALT, CMD_SFT_ALT_A, KC_LEFT, KC_DOWN, KC_RIGHT
      ),
    /* Layer 1: Special
     * ,---------------------------------------------------------------.
     * |  §| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       |( )|
     * |---------------------------------------------------------------|
     * |ClTab|   |   |   |   |   |   |   |   |   |   |   |   |ScnSh|   |
     * |------------------------------------------------------`    |---|
     * |Mke/Fl|   |   |   |   |   |   |   |   |CSL|   |   |  `|    |End|
     * |---------------------------------------------------------------|
     * |    |  `|   |   |CAC|   |   |   |   |   |   |   |      |PgU|   |
     * |---------------------------------------------------------------|
     * | LCtl|     |  CS{|                     |CS}|   |   |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
  [1] = LAYOUT_iso_68(
      NUBS_GRV_DIP, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, SLEEP_OSX,
      CTL_TAB_CTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      QK_MAKE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CMD_SFT_L, KC_TRNS, KC_TRNS, KC_NUBS, SCRNSHT, KC_END,
      KC_TRNS, GRV_NUBS_DIP, KC_TRNS, KC_TRNS, CMD_ALT_C, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP,
      KC_LCTL, KC_TRNS, CMD_SFT_LBR_CMD, KC_TRNS, CMD_SFT_RBR_CMD, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
      ),
};

bool dip_switch_update_user(uint8_t index, bool active) {
    dip_switch_state[index] = active;
    // do not continue (set default layer to be 1)
    return false;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case GRV_NUBS_DIP:
            if (dip_switch_state[0]) {
                if (record->event.pressed) {
                    register_code(KC_GRV);
                } else {
                    unregister_code(KC_GRV);
                }
            } else {
                if (record->event.pressed) {
                    register_code(KC_NUBS);
                } else {
                    unregister_code(KC_NUBS);
                }
            }
            break;
        case NUBS_GRV_DIP:
            if (dip_switch_state[0]) {
                if (record->event.pressed) {
                    register_code(KC_NUBS);
                } else {
                    unregister_code(KC_NUBS);
                }
            } else {
                if (record->event.pressed) {
                    register_code(KC_GRV);
                } else {
                    unregister_code(KC_GRV);
                }
            }
            break;
        default:
            return true;
    }
    return false;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(ENC_CCW, ENC_CW) },
};
#endif

