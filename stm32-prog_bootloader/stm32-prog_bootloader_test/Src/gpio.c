/**
 ******************************************************************************
 * @file           : gpio.c
 * @author         : Marek Gałeczka
 * @brief          : GPIO configuration file
 ******************************************************************************
 */
#include "gpio.h"

/**
 * @brief GPIO_Init() is used for initialization of GPIOs.
 *
 * @param void
 * @return None
 */
void GPIOx_Init(void) {

    /* GPIOA */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; /* Turn on peripherial clock (for GPIOA) */
    (void)RCC->AHB2ENR; /* Wait one cycle (by dummy reading the register value) after enabling peripherial clock */

    /* PA5 */
    GPIOA->BSRR = 1U << GPIO_BSRR_BR5_Pos; /* Turn on the Bit set/reset register to reset state */
    GPIOA->MODER &= ~GPIO_MODER_MODE5; /* Reset GPIOx Pin MODE Bit value */
    GPIOA->MODER |= 1U << GPIO_MODER_MODE5_Pos; /* Set GPIOx Pin as output (0b01) */
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT5; /* Set GPIOx Pin's output as push-pull (0b0) */
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5; /* Set GPIOx Pin's output speed to Low speed (0b00) */
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5; /* Set GPIOx Pin's output to no pull-up, no pull-down (0b00) */

    /* PA2 (TX) & PA3 (RX) (USART2) */
    GPIOA->MODER &= ~GPIO_MODER_MODE2;
    GPIOA->MODER |= 2U << GPIO_MODER_MODE2_Pos; /* Set PA2 as alternate function */
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_Msk; /* Reset value in PA2 AFSEL register */
    GPIOA->AFR[0] |=  7U  << GPIO_AFRL_AFSEL2_Pos; /* Set PA2 pin as UART type */
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT2; /* Set GPIOx Pin's output as push-pull (0b0) */
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2;
    GPIOA->OSPEEDR |= 2U << GPIO_OSPEEDR_OSPEED2_Pos; /* Set Gpiox Pin's output speed to high speed (0b10) */
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2; /* No pull-up no pull-down */

    GPIOA->MODER &= ~GPIO_MODER_MODE3;
    GPIOA->MODER |= 2U << GPIO_MODER_MODE3_Pos; /* Set PA3 as alternate function*/
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_Msk;
    GPIOA->AFR[0] |=  7U  << GPIO_AFRL_AFSEL3_Pos; /* Set PA3 pin as UART type */
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT3; /* Set GPIOx Pin's output as push-pull (0b0) */
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3;
    GPIOA->OSPEEDR |= 2U << GPIO_OSPEEDR_OSPEED3_Pos; /* Set Gpiox Pin's output speed to high speed (0b10) */
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3;
    GPIOA->PUPDR |= 1U << GPIO_PUPDR_PUPD3_Pos; /* Pull-up */

    /* ... */
    return;
}

/**
* @brief GPIO_TogglePin()
*
* @param 
* @return 
*/
void GPIO_TogglePin(GPIO_TypeDef *GPIO_Port, uint32_t GPIO_Pin) { 

    if (GPIO_Port->ODR & (1U << GPIO_Pin)) {
        GPIO_Port->BSRR = 1U << (GPIO_Pin + 16U);
    } else {
        GPIO_Port->BSRR = 1U << GPIO_Pin;
    }

    return;
}
