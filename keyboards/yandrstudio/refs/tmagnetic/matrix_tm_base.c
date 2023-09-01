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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "quantum.h"
#include "gpio.h"
#include "analog.h"

const pin_t matrix_io_pins[PINS_NUM] = PINS_MAP;
const pin_t matrix_mux_pins[NUM_OF_MUX] = MUX_OUT_PIN2MCU;
const pin_t mux_en_pins[NUM_OF_MUX] = MUX_EN_PINS;
const uint8_t mask_of_each_4051[MATRIX_ROWS][MATRIX_COLS][3] = MATRIX_OF_4051;

// 都应该保存到eeprom或者flash
// 记录最大最小值
uint32_t adc_vals_low[MATRIX_ROWS][MATRIX_COLS] = {0};
uint32_t adc_vals_high[MATRIX_ROWS][MATRIX_COLS] = {0};
// 记录触发阈值
uint32_t adc_vals_th[MATRIX_ROWS][MATRIX_COLS] = {0};
// rt阈值
int32_t rt_th = -50;
// 记录上次扫描值
uint32_t adc_vals_last[MATRIX_ROWS][MATRIX_COLS] = {0};
// 记录当前值
uint32_t adc_vals_cur[MATRIX_ROWS][MATRIX_COLS] = {0};


// 校准标记, 应该要保存到eeprom
bool has_calibrate_th = false;
// rt开关，应该要保存到eeprom
bool rt_fun_sw = true;
// rt标记，全局变量
bool rt_toggle = true;


static inline void writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        writePinLow(pin);
    }
}
static inline void writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        writePinHigh(pin);
    }
}
static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}

static void set_mux_addr(uint8_t addr) {
    if (addr & 0x01) {
        writeHigh(MUX_ADD_PIN1);
    } else {
        writeLow(MUX_ADD_PIN1);
    }
    if (addr & 0x02) {
        writeHigh(MUX_ADD_PIN2);
    } else {
        writeLow(MUX_ADD_PIN2);
    }
    if (addr & 0x04) {
        writeHigh(MUX_ADD_PIN3);
    } else {
        writeLow(MUX_ADD_PIN3);
    }
}

static uint32_t get_curr_adc_val(uint8_t current_row, uint8_t current_col) {
    if (mask_of_each_4051[current_row][current_col][0] == 0xff) {
        return analogReadPin(matrix_io_pins[mask_of_each_4051[current_row][current_col][2]]);
    } else {
#if NUM_OF_MUX > 1
        writeLow(mux_en_pins[mask_of_each_4051[current_row][current_col][0]]);
#endif
        set_mux_addr(mask_of_each_4051[current_row][current_col][1]);
        wait_us(1);
        uint32_t adc_val = analogReadPin(matrix_mux_pins[mask_of_each_4051[current_row][current_col][0]]);
#if NUM_OF_MUX > 1
        writeHigh(mux_en_pins[mask_of_each_4051[current_row][current_col][0]]);
#endif
        return adc_val;
    }
}

static void init_pins(void) {
    for (uint8_t i = 0; i < NUM_OF_MUX; ++i) {
        setPinOutput(mux_en_pins[i]);
    }
    setPinOutput(MUX_ADD_PIN1);
    setPinOutput(MUX_ADD_PIN2);
    setPinOutput(MUX_ADD_PIN3);

#if NUM_OF_MUX > 1
//默认全部失能
    for (uint8_t i = 0; i < NUM_OF_MUX; ++i) {
        writeHigh(mux_en_pins[i]);
    }
#else
// 只有一个直接使能
        writeLow(mux_en_pins[0]);
#endif

    // 4051的读取脚
    for (uint8_t i = 0; i < NUM_OF_MUX; ++i) {
        palSetLineMode(matrix_mux_pins[i], PAL_MODE_INPUT_ANALOG);
    }
    // 直连IO的读取脚
    for (uint8_t i = 0; i < PINS_NUM; ++i) {
        palSetLineMode(matrix_io_pins[i], PAL_MODE_INPUT_ANALOG);
    }

// 需要启动校准
    // if (!has_calibrate_th) {
    //     star_calibrate_th();
    // }
}
static uint32_t adc_debug_timer = 0;
static void debug_for_adc(uint8_t current_row, uint8_t current_col, uint32_t adc) {
    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, adc_debug_timer) >= 500) {
        dprintf("R: %d, C: %d, ADC:%ld, TH:%ld\n", current_row, current_col, adc, adc_vals_th[current_row][current_col]);
        adc_debug_timer = timer_now;
    }
}


static bool read_matrix(matrix_row_t current_matrix[], uint8_t current_row, uint8_t current_col) {
    bool matrix_changed = false;

    matrix_row_t last_row_value = current_matrix[current_row];

    matrix_row_t current_row_value = last_row_value;

    // 多次采样取平均值
    uint32_t adc_val = 0;
    for (uint8_t i = 0; i < ADC_SAMPLE_TIMES; ++i) {
        adc_val += get_curr_adc_val(current_row, current_col);
    }
    adc_val /= 3;

    debug_for_adc(current_row, current_col, adc_val);

    // 记录上次的值，并更新
    // 逻辑上有问题，last val更新很快，不会触发rt
    // 需要更改last val的定义为一次下压过程中的最低点
    uint32_t last_val = adc_vals_last[current_row][current_col];
    adc_vals_last[current_row][current_col] = adc_val;

    // rt功能，先标记本地变量
    int32_t diff_val = adc_val - last_val;
    bool rt_toggle_local = false;
    if (rt_toggle && diff_val < rt_th) {
        // 如果目前矩阵是触发状态
        if (current_row_value & (MATRIX_ROW_SHIFTER << current_col)) {
            // 直接设置为抬起
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
            // 标记触发rt功能
            rt_toggle_local = true;
        }
    }

    if (!rt_toggle_local) {
        // rt没有触发才进行基础的扫描
        if (adc_val >= adc_vals_th[current_row][current_col]) {
            // 触发功能
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // 没触发
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
    }
    // Determine if the matrix changed state
    if ((last_row_value != current_row_value)) {
        matrix_changed |= true;
        current_matrix[current_row] = current_row_value;
    }
    return matrix_changed;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
    for (uint8_t i = 0; i < MATRIX_ROWS; ++i) {
        for (uint8_t j = 0; j < MATRIX_COLS; ++j) {
            adc_vals_low[i][j] = 760;
            adc_vals_high[i][j] = 980;
            adc_vals_th[i][j] = 820;

            adc_vals_last[i][j] = adc_vals_low[i][j];
        }
    }
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set col, read rows
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            changed |= read_matrix(current_matrix, current_row, current_col);
        }
    }
    return (uint8_t)changed;
}
