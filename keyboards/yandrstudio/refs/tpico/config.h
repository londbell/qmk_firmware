/* Copyright 2023 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID  0xAA96
#define PRODUCT_ID 0xFFFF
#define DEVICE_VER 0x0001
#define MANUFACTURER TEST_Y&R
#define PRODUCT tjoystick

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

//                        0    1    2
#define MATRIX_COL_PINS { B0,  A8,  A9 }
#define MATRIX_ROW_PINS { B1,  A11, A10}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
