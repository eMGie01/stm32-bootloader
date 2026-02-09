/**
 ******************************************************************************
 * @file           : clock.h
 * @author         : Marek Gałeczka
 * @brief          : Clock configuration header file
 ******************************************************************************
 */
#ifndef CLOCK_H
#define CLOCK_H
#include <stdint.h>

#define SYSTEM_CORE_CLOCK 24000000

extern uint32_t SystemCoreClock;

void SystemClock_Config_24MHz(void);

#endif /*CLOCK_H*/
