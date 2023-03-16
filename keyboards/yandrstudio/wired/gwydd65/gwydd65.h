// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"
#if defined(KEYBOARD_yandrstudio_wired_point65_rev1)
    #include "rev1.h"
#else
    #include "rev2.h"
#endif

enum keyboard_keycodes {
    LOCK_GUI = QK_KB,
    TOG_MACOS_KEYMAP,
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD
};

#define KC_LG    LOCK_GUI
#define KC_MACOS TOG_MACOS_KEYMAP
#define KC_MCTL  KC_MISSION_CONTROL
#define KC_LPAD  KC_LAUNCHPAD
