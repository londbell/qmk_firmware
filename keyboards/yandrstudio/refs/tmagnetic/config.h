/* Copyright 2021 JasonRen(biu)
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
#define MANUFACTURER    "TEST_Y&R"
#define PRODUCT         "tmagnetic"

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

// #define DEBUG_MATRIX_SCAN_RATE

#define TAP_CODE_DELAY 15

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define MATRIX_ADC_PIN B0

#define NUM_OF_MUX   1
#define MUX_ADD_PIN1 A7
#define MUX_ADD_PIN2 A6
#define MUX_ADD_PIN3 A5
#define MUX_EN_PINS  {B2}
#define MUX_OUT_PIN2MCU {B0}

#define PINS_NUM 1
#define PINS_MAP {B1}

//                       {muxId, muxAim, io_pin}
#define MATRIX_OF_4051 { {{0,0,0},{0,2,0},{0,1,0}},\
                         {{0,3,0},{0,4,0},{0,6,0}},\
                         {{0,5,0},{0,7,0},{0xff,0,0}}\
                        }

#define ADC_SAMPLE_TIMES 3
