// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, \
    K200, K206, K205, K204, K203, K202, K201, K207, K208, K209, K210, K211, K212,       \
    K300, K306, K305, K301, K302, K303, K304, K309, K310, K308, K307, K311, K312, K313, \
    K400, K401, K402, K403, K404,                   K410, K408, K407, K411, K412, K413  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013}, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113}, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO}, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313}, \
    { K400,  K401,  K402,  K403,  K404,  KC_NO, KC_NO, K407,  K408,  KC_NO, K410,  K411,  K412,  K413}  \
}

enum keyboard_keycodes {
#ifdef VIA_ENABLE
    LOCK_GUI = USER00,
#else
    LOCK_GUI = SAFE_RANGE,
#endif

#ifdef RGB_MATRIX_ENABLE
    KC_KEY_UNDER_RGBSW,
    BAT_SHOW,
#endif
    TOG_MACOS_KEYMAP,
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD,
#ifdef VIA_ENABLE
    NEW_SAFE_RANGE = SAFE_RANGE  // Important!
#else
    NEW_SAFE_RANGE   // Important!
#endif
};

#define KC_LG     LOCK_GUI
#define KC_MACOS  TOG_MACOS_KEYMAP
#define KC_MCTL   KC_MISSION_CONTROL
#define KC_LPAD   KC_LAUNCHPAD

#ifdef RGB_MATRIX_ENABLE
#   define RGB_KG_T  KC_KEY_UNDER_RGBSW
#   define KC_BTSH BAT_SHOW
#endif
