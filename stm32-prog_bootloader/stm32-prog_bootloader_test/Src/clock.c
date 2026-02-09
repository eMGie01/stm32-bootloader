/**
 ******************************************************************************
 * @file           : clock.c
 * @author         : Marek Gałeczka
 * @brief          : Clock configuration file
 ******************************************************************************
 */

#include "clock.h"
#include "stm32l4xx.h"

uint32_t SystemCoreClock = SYSTEM_CORE_CLOCK;

/**
 * @brief __systemClock_Config_24MHz() is used for initialization and configuration
 *        of main system clock (SYSCLK) to a value of 24 MHz using HSI nad PLL.
 *
 * @param void
 * @return None
 */
void SystemClock_Config_24MHz(void) {

    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN; 
    PWR->CR1 |= PWR_CR1_VOS_0; /* Set greater voltage value */

    RCC->CR |= RCC_CR_HSION; /* Turn on the Internal Oscilator */
    while(!(RCC->CR & RCC_CR_HSIRDY)); /* Wait for the HSIRDY bit to set */

    /* 1WS, because 24MHz, turn the prefetched on, turn the cache on for instructions, turn cache on for data */
    FLASH->ACR = FLASH_ACR_LATENCY_1WS |
                 FLASH_ACR_PRFTEN |
                 FLASH_ACR_ICEN |
                 FLASH_ACR_DCEN; /* Configure Flash */

    /* Configure PLL -> ((internal) 16MHz / 2) * 18) / 6 = 24MHz */
    /**
    * HSI = 16 MHz
    * PLLM = /2, PLLN = 18, PLLR = /6
    * f_VCO = 144 MHz, SYSCLK = 24 MHz
    */
    RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSI |
                   1U << RCC_PLLCFGR_PLLM_Pos |
                   18U << RCC_PLLCFGR_PLLN_Pos |
                   2U << RCC_PLLCFGR_PLLR_Pos |
                   RCC_PLLCFGR_PLLREN;
    /* HSI clock selected as PLL, ... , clock entry (11 to [Bit1 and Bit0]) */
    
    RCC->CR |= RCC_CR_PLLON; /* Turn on the PLL */
    while(!(RCC->CR & RCC_CR_PLLRDY)); /* Wait for the PLLRDY bit to set */

    RCC->CFGR &= ~(RCC_CFGR_HPRE |
                  RCC_CFGR_PPRE1 |
                  RCC_CFGR_PPRE2); /* Clear prescalers for clocks */

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1 |
                 RCC_CFGR_PPRE1_DIV1 |
                 RCC_CFGR_PPRE2_DIV1; /* Set prescalers for clocks to 1 */  

    RCC->CFGR |= RCC_CFGR_SW_PLL; /* Select PLL as system clock*/
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)); /* Wait for switch of systemclock to PLL*/

    SystemCoreClock = SYSTEM_CORE_CLOCK; /* Change SystemCoreClock variable to set value */

    return;
}
