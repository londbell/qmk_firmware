// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sonic170.h"


#ifdef RGBLIGHT_ENABLE

#   ifndef FACTORY_TEST

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_RED});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_capslock_layer);

bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

void keyboard_post_init_kb(void) {
      debug_enable=true;
  debug_matrix=true;
    rgblight_reload_from_eeprom();
    rgblight_layers = my_rgb_layers;
}

#   endif

#endif