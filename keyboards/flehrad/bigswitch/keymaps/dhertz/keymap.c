/*
Copyright 2018 QMK Contributors

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

// Tap dance enums
enum {
    THE_BUTTON,
};

void finished(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(THE_BUTTON)
        ),
};

/*
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
void tap_or_hold(tap_dance_state_t *state, char *tap_macro, char *hold_macro) {
        if (state->interrupted || !state->pressed) {
            send_string(tap_macro);
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        } else {
            send_string(hold_macro);
        }
}

void finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            // Tap for F24 - zoom hangup, hold to sleep
            tap_or_hold(state, SS_TAP(X_F24), SS_LALT(SS_LGUI(SS_TAP(X_OSX_EJECT))));
            break;
        case 2:
            // Tap for N/A, hold for quit app
            tap_or_hold(state, "", SS_LGUI("q"));
            break;
        case 3:
            tap_or_hold(state,
                        "qmk compile -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER),
                        "qmk flash -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER)
            );
            if (state->pressed) {
                //wait for the compile to be done
                wait_ms(5000);
                reset_keyboard();
            }
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [THE_BUTTON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, finished, NULL)
};
