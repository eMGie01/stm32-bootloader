/**
 ******************************************************************************
 * @file           : systick.c
 * @author         : Marek Gałeczka
 * @brief          : System Tick configuration file
 ******************************************************************************
 */
#include "systick.h"
#include "clock.h"
#include "stm32l4xx.h"

/**
 * variables for handling SysTick timer
 */
static volatile uint32_t sys_ticks = 0;

/**
 * @brief SysTick_Init() 
 *
 * @param void
 * @return None
 */
void SysTick_Init(void) {

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; /* Turn off SysTick enable (bit to 0) */
    SysTick->CTRL |= 1U << SysTick_CTRL_CLKSOURCE_Pos; /* Set up HCLK as SysTick source */
    SysTick->LOAD = (SystemCoreClock / 1000U) - 1U; /* (24 MHz / 1000) - 1 */
    SysTick->VAL = 0U;
    SysTick->CTRL |= 1U << SysTick_CTRL_TICKINT_Pos;
    SysTick->CTRL |= 1U << SysTick_CTRL_ENABLE_Pos;

    return;
}

/**
 * @brief SysTick_Handler() 
 *
 * @param void
 * @return None
 */
void SysTick_Handler(void) {
    sys_ticks++;
}

/**
* @brief get_SysTick() 
*
* @param void
* @return uint32_t value of sys_ticks parameter
*/
uint32_t get_SysTick(void) {
    return sys_ticks;
}
