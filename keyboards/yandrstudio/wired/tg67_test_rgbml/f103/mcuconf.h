// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

#undef  STM32_PLLXTPRE
#define STM32_PLLXTPRE STM32_PLLXTPRE_DIV2

// #undef STM32_USBPRE
// #define STM32_USBPRE STM32_USBPRE_DIV2

// #undef STM32_PLLMUL_VALUE
// #define STM32_PLLMUL_VALUE 12

// /*
// /*
//  * Clocks initialization for all sub-families except CL.
//  */
// void stm32_clock_init(void) {
// //   /* Set HSION bit */
//   RCC->CR |= (uint32_t)0x00000001;

// //   /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
//   RCC->CFGR &= (uint32_t)0xF8FF0000;

// //   /* Reset HSEON, CSSON and PLLON bits */
//   RCC->CR &= (uint32_t)0xFEF6FFFF;

// //   /* Reset HSEBYP bit */
//   RCC->CR &= (uint32_t)0xFFFBFFFF;

// //   /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
//   RCC->CFGR &= (uint32_t)0xFF80FFFF;

//   /* Disable all interrupts and clear pending bits  */
//   RCC->CIR = 0x009F0000;
// #if !STM32_NO_INIT
//   /* HSI setup, it enforces the reset situation in order to handle possible
//      problems with JTAG probes and re-initializations.*/
//   RCC->CR |= RCC_CR_HSION;                  /* Make sure HSI is ON.         */
//   while (!(RCC->CR & RCC_CR_HSIRDY))
//     ;                                       /* Wait until HSI is stable.    */
//   RCC->CR &= RCC_CR_HSITRIM | RCC_CR_HSION; /* CR Reset value.              */
//   RCC->CFGR = 0;                            /* CFGR reset value.            */
//   while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI)
//     ;                                       /* Waits until HSI is selected. */

// #if STM32_HSE_ENABLED
// #if defined(STM32_HSE_BYPASS)
//   /* HSE Bypass.*/
//   RCC->CR |= RCC_CR_HSEON | RCC_CR_HSEBYP;
// #endif
//   /* HSE activation.*/
//   RCC->CR |= RCC_CR_HSEON;
//   while (!(RCC->CR & RCC_CR_HSERDY))
//     ;                                       /* Waits until HSE is stable.   */
// #endif

// #if STM32_LSI_ENABLED
//   /* LSI activation.*/
//   RCC->CSR |= RCC_CSR_LSION;
//   while ((RCC->CSR & RCC_CSR_LSIRDY) == 0)
//     ;                                       /* Waits until LSI is stable.   */
// #endif

// #if STM32_ACTIVATE_PLL
//   /* PLL activation.*/
//   RCC->CFGR |= STM32_PLLMUL | STM32_PLLXTPRE | STM32_PLLSRC;
//   RCC->CR   |= RCC_CR_PLLON;
//   while (!(RCC->CR & RCC_CR_PLLRDY))
//     ;                                       /* Waits until PLL is stable.   */
// #endif

//   /* Clock settings.*/
// #if STM32_HAS_USB
//   RCC->CFGR = STM32_MCOSEL | STM32_USBPRE | STM32_PLLMUL | STM32_PLLXTPRE |
//               STM32_PLLSRC | STM32_ADCPRE | STM32_PPRE2  | STM32_PPRE1    |
//               STM32_HPRE;
// #else
//   RCC->CFGR = STM32_MCOSEL |                STM32_PLLMUL | STM32_PLLXTPRE |
//               STM32_PLLSRC | STM32_ADCPRE | STM32_PPRE2  | STM32_PPRE1    |
//               STM32_HPRE;
// #endif

//   /* Flash setup and final clock selection.   */
//   FLASH->ACR = FLASH_ACR_LATENCY_2;

//   /* Switching to the configured clock source if it is different from HSI.*/
// #if (STM32_SW != STM32_SW_HSI)
//   /* Switches clock source.*/
//   RCC->CFGR |= STM32_SW;
//   while ((RCC->CFGR & RCC_CFGR_SWS) != (STM32_SW << 2))
//     ;                                       /* Waits selection complete.    */
// #endif

// #if !STM32_HSI_ENABLED
//   RCC->CR &= ~RCC_CR_HSION;
// #endif
// #endif /* !STM32_NO_INIT */
// }
