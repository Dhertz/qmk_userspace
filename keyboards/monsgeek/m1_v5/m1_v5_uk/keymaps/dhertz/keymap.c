#include QMK_KEYBOARD_H
#include "dhertz.h"

#define ______ KC_NO

static uint8_t custom_brightness = 64;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,   KC_MUTE,
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,  KC_DEL,
	    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,            KC_PGUP,
	    SRCH_CTL, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    KC_BSLS,  KC_ENT,   KC_END,
        KC_LSFT,  HSH_TLD_1,KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,    KC_RSFT,  KC_UP,    KC_PGDN,
        NC_CTL,   KC_LALT,  CMD_TAB_CMD,                      LYR_SPC,                         CMD_GRV_CMD, KC_RALT,CMD_SFT_ALT_A,KC_LEFT,  KC_DOWN,  KC_RGHT),

    [1] = LAYOUT( /* Function */
        NUBS_GRV, KC_BRID,  KC_BRIU,  KC_MCTL,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,  SLEEP_OSX,
        EE_CLR,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        CTL_TAB_CTL,  _______,  _______,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,            _______,
        QK_MAKE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_TOG,  _______,  _______, KC_NUBS,   SCRNSHT,  _______,
        _______,  KC_GRV,  _______,  _______,  KC_CALC,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_PGUP,  _______,
        KC_LCTL,  GU_TOGG,  _______,                      HS_BATQ,                                _______,  _______,  _______,  KC_HOME, KC_PGDN,  KC_END),
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgb_matrix_set_color_all(RGB_AZURE);
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
}

uint32_t cancel_cmd(uint32_t trigger_time, void *cb_arg) {
    if (get_highest_layer(layer_state|default_layer_state) > 0) {
        return 20;
    }
    unregister_code(KC_LCMD);
    return 0;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state|default_layer_state) == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else {
        // Check if shift is held on layer 1 for RGB brightness control
        if (get_highest_layer(layer_state|default_layer_state) == 1 &&
            (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) {
            if (clockwise) {
                if (custom_brightness < 240) {
                    custom_brightness += 15;
                } else {
                    custom_brightness = 255;
                }
            } else {
                if (custom_brightness > 15) {
                    custom_brightness -= 15;
                } else {
                    custom_brightness = 0;
                }
            }
        } else {
            // Default layer 1+ behavior: Cmd+Tab navigation
            if ((get_mods() & MOD_BIT(KC_LCMD)) != MOD_BIT(KC_LCMD)) {
                register_code(KC_LCMD);
                defer_exec(20, cancel_cmd, NULL);
            }
            if (clockwise) {
                tap_code(KC_TAB);
            } else {
                tap_code16(S(KC_TAB));
            }
        }
    }
    return false;
}
bool rgb_matrix_indicators_kb(void) {
    // Apply brightness scaling to colors
    uint8_t scaled_r, scaled_g, scaled_b;

    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 1:
            // Scale RGB_PURPLE (128, 0, 128) by custom brightness
            scaled_r = (128 * custom_brightness) / 255;
            scaled_g = 0;
            scaled_b = (128 * custom_brightness) / 255;
            rgb_matrix_set_color_all(scaled_r, scaled_g, scaled_b);
            break;
        default:
            // Scale RGB_AZURE (0, 127, 255) by custom brightness
            scaled_r = 0;
            scaled_g = (127 * custom_brightness) / 255;
            scaled_b = (255 * custom_brightness) / 255;
            rgb_matrix_set_color_all(scaled_r, scaled_g, scaled_b);
            break;
    }
    return false;
}
