// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "point65.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch(keycode) {
        case KC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case KC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case KC_MCTL_MAC:
            if (record->event.pressed) {
                register_code16(KC_MCTL);
            } else {
                unregister_code16(KC_MCTL);
            }
            return false;
        case KC_LPAD_MAC:
            if (record->event.pressed) {
                register_code16(KC_LPAD);
            } else {
                unregister_code16(KC_LPAD);
            }
            return false;
        default:
            return true;
    }
    return true;
}
