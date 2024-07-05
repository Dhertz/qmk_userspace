RGB_MATRIX_EFFECT(off_after_x_seconds)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#define SLEEP_AFTER_SECONDS 90

static bool off_after_x_seconds(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (g_last_hit_tracker.tick[g_last_hit_tracker.count-1] < SLEEP_AFTER_SECONDS * 1000) {
        rgb_matrix_set_color_all(RGB_AZURE);
    } else {
        rgb_matrix_set_color_all(RGB_BLACK);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS


