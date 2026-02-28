#include QMK_KEYBOARD_H

enum {
    THE_BUTTON,
};

void finished(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(THE_BUTTON)
        ),
};

void tap_or_hold(tap_dance_state_t *state, char *tap_macro, char *hold_macro) {
        if (state->interrupted || !state->pressed) {
            send_string(tap_macro);
        } else {
            send_string(hold_macro);
        }
}

void finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_or_hold(state, SS_LALT("w"), SS_LALT("w"));
            break;
        case 3:
            tap_or_hold(state,
                        "qmk compile -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER),
                        "qmk flash -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER)
            );
            if (state->pressed) {
                wait_ms(30000);
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
