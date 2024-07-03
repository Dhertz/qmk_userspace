/*
Copyright 2015 Jun Wako <wakojun@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "dhertz.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp|Del|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter|Hom|
     * |------------------------------------------------------`    |---|
     * |SrCtl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |End|
     * |---------------------------------------------------------------|
     * |Shif|  #|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |NcCtl|  Alt| CTab|        LyrSpc       |CGv|Alt|CSa|Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [0] = LAYOUT_iso( \
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,    KC_DEL, \
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,             KC_HOME,\
        KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_BSLS,     KC_ENT, KC_END, \
        KC_LSFT,HSH_TLD,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,     KC_UP,  KC_PGDN,\
        NC_CTL, KC_LALT, CMD_TAB_CMD,              LYR_SPC,             CMD_GRV_CMD, KC_RALT, CMD_SFT_ALT_A, KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    /* Layer 1: HHKB mode (Space)
     * ,---------------------------------------------------------------.
     * |  §| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       |Sle|
     * |---------------------------------------------------------------|
     * |ClTab|   |   |   |   |   |   |   |Psc|Slk|Pus| Up|   |ScnSh|   |
     * |------------------------------------------------------`    |---|
     * |Mke/Fl|VoD|VoU|Mut|   |   |   |Bsp|Del|CSL|Lef|Rig|  `|    |   |
     * |---------------------------------------------------------------|
     * |    |  `|   |   |CAC|   |   |   |   |   |   |Dow|      |PgU|   |
     * |---------------------------------------------------------------|
     * | LCtl|     |  CS{|                     |CS}|   |   |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
    [1] = LAYOUT_iso( \
        KC_GRV,     KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12, KC_TRNS,  SLEEP_OSX,\
        CTL_TAB_CTL,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,BL_UP, KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCT,KC_TRNS,KC_PAUS,  KC_UP,              KC_TRNS,\
        QK_MAKE,    KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,BL_TOGG,KC_TRNS,KC_BSPC,KC_DEL, CMD_SFT_L,KC_LEFT,KC_RGHT,KC_NUBS,   SCRNSHT,KC_TRNS,\
        KC_TRNS,    KC_NUBS,KC_TRNS,KC_TRNS,CMD_ALT_C,BL_DOWN, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_DOWN,KC_TRNS,KC_TRNS,  KC_PGUP,KC_TRNS,\
        KC_LCTL,    KC_TRNS,CMD_SFT_LBR_CMD,             KC_TRNS,           CMD_SFT_RBR_CMD,KC_TRNS,KC_TRNS,     KC_HOME,KC_PGDN,KC_END  \
    ),
};

void keyboard_post_init_user(void) {
    led_matrix_set_value_all(0);
}

bool led_matrix_indicators_kb(void) {
    switch(get_highest_layer(layer_state)) {
        case 1:
            led_matrix_set_value_all(255);
            break;
        default:
            led_matrix_set_value_all(0);
            break;
    }
    return false;
}
