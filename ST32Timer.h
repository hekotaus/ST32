#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ST32Tools.h"

// Period of the fast timer, uS. Currently can be 10 or 100
#define FAST_TIMER_PERIOD_uS 100

extern uint32_t i_tim7;
// fast timer period, uS
//extern uint32 i_tim_100uS;
//#define FAST_TIMER_TICK 100

void TIM7_IRQHandler_();

//void EST_Timer2_1msInit();
//void EST_Timer7_1msInit();
//void LXST32_Timer2_1msInit();
void ST32_Init1msTimer7();
void ST32_Init1msTimer17();
void ST32_Init1usTickTimer5();
//void LXST32_InitFastTimer();

#ifdef __cplusplus
}
#endif

