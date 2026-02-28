#include QMK_KEYBOARD_H
#include "dhertz.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,   KC_MUTE,
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,  KC_DEL,
	    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,            KC_PGUP,
	    SRCH_CTL, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    KC_BSLS,  KC_ENT,   KC_PGDN,
        KC_LSFT,  HSH_TLD_1,KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,    KC_RSFT,  KC_UP,    KC_END,
        NC_CTL,   KC_LALT,  CMD_TAB_CMD,                      LYR_SPC,                         CMD_GRV_CMD, KC_RALT,CMD_SFT_ALT_A,KC_LEFT,  KC_DOWN,  KC_RGHT),

    [1] = LAYOUT( /* Function */
        NUBS_GRV, KC_BRID,  KC_BRIU,  KC_MCTL,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RM_NEXT,  SLEEP_OSX,
        EE_CLR,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        CTL_TAB_CTL,  _______,  _______,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,            _______,
        QK_MAKE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  CMD_SFT_L,  _______,  _______, KC_NUBS,   SCRNSHT,  _______,
        _______,  KC_GRV,  _______,  _______,  CMD_ALT_C,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_PGUP,  _______,
        KC_LCTL,  GU_TOGG,  CMD_SFT_LBR_CMD,                      HS_BATQ,                                CMD_SFT_RBR_CMD,  _______,  _______,  KC_HOME, KC_PGDN,  KC_END),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(ENC_CCW, ENC_CW) },
};
#endif
