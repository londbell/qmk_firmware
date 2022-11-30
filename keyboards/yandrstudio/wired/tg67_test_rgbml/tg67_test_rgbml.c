// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tg67_test_rgbml.h"
#include "rgb_matrix_layer.h"

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_update_pwm_buffers(void);

led_config_t g_led_config = {
    {
        {54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68},
        {53,  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39},
        {25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,   NO_LED,  37,  38},
        {24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14,   NO_LED,  13,  12,  11},
        {0,  1,  2,  NO_LED,   NO_LED,  4,   NO_LED,  NO_LED,   NO_LED,  6,  7,   NO_LED,  8,  9,  10}
    },
    {
        // LED Index to Physical Position
        {0,64},{16,64},{32,64},{48,64},       {80,64},       {112,64},       {144,64},{160,64},       {192,64},{208,64},{224,64},
        {224,48},{208,48},{192,48},       {160,48},{144,48},{128,48},{112,48},{96,48},{80,48},{64,48},{48,48},{32,48},{16,48},{0,48},
        {0,32},{16,32},{32,32},{48,32},{64,32},{80,32},{96,32},{112,32},{128,32},{144,32},{160,32},{176,32},       {208,32},{224,32},
        {224,16},{208,16},{192,16},{176,16},{160,16},{144,16},{128,16},{112,16},{96,16},{80,16},{64,16},{48,16},{32,16},{16,16},{0,16},
        {0,0},{16,0},{32,0},{48,0},{64,0},{80,0},{96,0},{112,0},{128,0},{144,0},{160,0},{176,0},{192,0},{208,0},{224,0}
    },
    {
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

const rgb_matrix_adv_layer_segment_t PROGMEM my_capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS(
    {25, 1, HSV_RED}
);
const rgb_matrix_adv_layer_segment_t PROGMEM my_z_layer[] = RGB_MATRIX_LAYER_SEGMENTS(
    {26, 6, HSV_RED},
    {1, 6, HSV_GREEN}
);

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(
    my_capslock_layer,
    my_z_layer
);

void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(0, host_keyboard_led_state().caps_lock);
    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_update_pwm_buffers();
    }
}

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch(keycode) {
        case KC_Z:
            if (record->event.pressed) {
                rgb_matrix_adv_blink_layer_repeat(1, 500, 6);
            }
            return true;
        case LOCK_GUI:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        default:
            return true;
    }
    return true;
}
