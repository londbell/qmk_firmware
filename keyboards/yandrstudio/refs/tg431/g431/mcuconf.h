/* Copyright 2020 QMK
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

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

#undef STM32_HSE_ENABLED
#undef STM32_PLLSRC
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLQ_VALUE
#undef STM32_PLLR_VALUE


#define STM32_HSE_ENABLED                   TRUE
#define STM32_PLLSRC                        STM32_PLLSRC_HSE
#define STM32_PLLM_VALUE                    6
#define STM32_PLLN_VALUE                    85
#define STM32_PLLQ_VALUE                    2
#define STM32_PLLR_VALUE                    2
