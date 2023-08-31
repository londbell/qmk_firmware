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
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "quantum.h"
#include "gpio.h"

const pin_t matrix_io_pins[PINS_NUM] = PINS_MAP;
const pin_t matrix_mux_pins[NUM_OF_MUX] = MUX_OUT_PIN2MCU;
const pin_t mux_en_pins[NUM_OF_MUX] = MUX_EN_PINS;
const uint8_t mask_of_each_4051[MATRIX_ROWS][MATRIX_COLS][3] = MATRIX_OF_4051;

// 都应该保存到eeprom或者flash
// 记录最大最小值
uint32_t adc_vals_low[MATRIX_ROWS][MATRIX_COLS] = {0};
uint32_t adc_vals_high[MATRIX_ROWS][MATRIX_COLS] = {0};
// 记录触发阈值
uint32_t adc_vals_th1[MATRIX_ROWS][MATRIX_COLS] = {0};
uint32_t adc_vals_th2[MATRIX_ROWS][MATRIX_COLS] = {0};
uint32_t adc_vals_th3[MATRIX_ROWS][MATRIX_COLS] = {0};
// rt阈值
int32_t rt_th = 0;
// 记录上次扫描值
uint32_t adc_vals_last[MATRIX_ROWS][MATRIX_COLS] = {0};
// 记录当前值
uint32_t adc_vals_cur[MATRIX_ROWS][MATRIX_COLS] = {0};


// 校准标记, 应该要保存到eeprom
bool has_calibrate_th = false;
// rt开关，应该要保存到eeprom
bool rt_fun_sw = true;
// rt标记，全局变量
bool rt_toggle = false;


static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        writePinLow(pin);
    }
}
static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        writePinHigh(pin);
    }
}
static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}

static void set_mux_addr(uint8_t addr) {
    if (addr & 0x01) {
        setPinOutput_writeHigh(MUX_ADD_PIN1);
    } else {
        setPinOutput_writeLow(MUX_ADD_PIN1);
    }
    if (addr & 0x02) {
        setPinOutput_writeHigh(MUX_ADD_PIN2);
    } else {
        setPinOutput_writeLow(MUX_ADD_PIN2);
    }
    if (addr & 0x04) {
        setPinOutput_writeHigh(MUX_ADD_PIN3);
    } else {
        setPinOutput_writeLow(MUX_ADD_PIN3);
    }
}

static uint32_t get_curr_adc_val(uint8_t current_row, uint8_t current_col) {
    if (mask_of_each_4051[current_row][current_col][0] == 0xff) {
        return analogReadPin(matrix_io_pins(mask_of_each_4051[current_row][current_col][2]));
    } else {
#if NUM_OF_MUX > 1
        setPinOutput_writeLow(mux_en_pins[mask_of_each_4051[current_row][current_col][0]]);
#endif
        set_mux_addr();
        wait_us(1);
        uint32_t adc_val = analogReadPin(matrix_mux_pins(mask_of_each_4051[current_row][current_col][0]));
#if NUM_OF_MUX > 1
        setPinOutput_writeHigh(mux_en_pins[mask_of_each_4051[current_row][current_col][0]]);
#endif
        return adc_val;
    }
}

static void init_pins(void) {
    setPinOutput(MUX1_EN_PIN);
    setPinOutput(MUX_ADD_PIN1);
    setPinOutput(MUX_ADD_PIN2);
    setPinOutput(MUX_ADD_PIN3);

#if NUM_OF_MUX > 1
//默认全部失能
    for (uint8_t i = 0; i < NUM_OF_MUX; ++i) {
        setPinOutput_writeHigh(mux_en_pins[i]);
    }
#else
// 只有一个直接使能
        setPinOutput_writeLow(mux_en_pins[0]);
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

static void debug_for_adc(uint32_t adc) {

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

    debug_for_adc(adc_val);

    // rt功能，先标记本地变量
    int32_t diff_val = adc_val - adc_vals_last[current_row][current_col];
    bool rt_toggle_local = false;
    if (diff_val < rt_th) {
        rt_toggle_local = true;
    }

    // 触发功能
    if (adc_val >= adc_vals_th3[current_row][current_col]) {

    } else if (adc_val >= adc_vals_th2[current_row][current_col]) {

    } else if (adc_val >= adc_vals_th1[current_row][current_col]) {

    } else {
    // 抬起阈值
    }

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;

        // Check row pin state
        if (readPin(row_pins[row_index]) == 1) {
            // Pin HI, set col bit
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin LO, clear col bit
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_row_value)) {
            matrix_changed |= true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_cols();
    matrix_output_unselect_delay(current_col, matrix_changed);  // wait for all Row signals to go HIGH


    return matrix_changed;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
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
