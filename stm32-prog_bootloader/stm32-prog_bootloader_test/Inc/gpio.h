/**
 ******************************************************************************
 * @file           : gpio.h
 * @author         : Marek Gałeczka
 * @brief          : GPIO configuration header file
 ******************************************************************************
 */
#ifndef GPIO_H
#define GPIO_H
#include "stm32l4xx.h"
#include <stdint.h>

void GPIOx_Init(void);
void GPIO_TogglePin(GPIO_TypeDef *GPIO_Port, uint32_t GPIO_Pin);

#endif /*GPIO_H*/
