/**
 ******************************************************************************
 * @file           : systick.h
 * @author         : Marek Gałeczka
 * @brief          : System Tick configuration header file
 ******************************************************************************
 */
#ifndef SYSTICK_H
#define SYSTICK_H
#include "stdint.h"

void SysTick_Init(void);
uint32_t get_SysTick(void);

#endif /*SYSTICK_H*/
