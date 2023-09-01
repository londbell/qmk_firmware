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

#undef  STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

#undef  STM32_PLLXTPRE
#define STM32_PLLXTPRE STM32_PLLXTPRE_DIV2

#undef STM32_PPRE1
#define STM32_PPRE1 STM32_PPRE1_DIV2

#undef STM32_PPRE2
#define STM32_PPRE2 STM32_PPRE2_DIV1

#undef STM32_ADCPRE
#define STM32_ADCPRE STM32_ADCPRE_DIV6
