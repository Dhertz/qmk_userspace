// Copyright 2022 Dan Hertz (@dhertz)
// SPDX-License-Identifier: GPL-3.0

#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define KC_OSX_EJECT 0x66
#define X_OSX_EJECT 66
#define SRCH_CTL CTL_T(KC_F19)
#define LYR_SPC LT(1, KC_SPC)
#define NC_CTL CTL_T(KC_F18)
#define SLEEP_OSX LALT(LGUI(KC_OSX_EJECT))
#define LOCK_OSX LSFT(LCTL(KC_OSX_EJECT))

enum custom_keycodes {
    HSH_TLD = SAFE_RANGE,
    HSH_TLD_1,
    CTRL_A,
    CMD_ALT_C,
    CMD_SFT_L,
    CMD_TAB_CMD,
    CMD_GRV_CMD,
    CMD_SFT_A,
    CMD_SFT_D,
    CMD_SFT_ALT_A,
    CMD_SFT_LBR_CMD,
    CMD_SFT_RBR_CMD,
    CTL_TAB_CTL,
    SCRNSHT,
    NEW_SAFE_RANGE,
};

void mod_or_mod_with_macro(keyrecord_t *record, uint16_t kc_mod, char* cmd_or_macro);

#endif
