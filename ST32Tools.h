#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "hwversion.h"

#ifdef STM32G0
#include <stm32g0xx_hal.h>
#include <stm32g0xx_hal_def.h>
#include <stm32g0xx_hal_gpio.h>
#include <stm32g0xx_hal_tim.h>
#endif

#ifdef STM32H5
#include <stm32h5xx_hal.h>
#include <stm32h5xx_hal_def.h>
#include <stm32h5xx_hal_gpio.h>
#include <stm32h5xx_hal_tim.h>
#endif

#ifdef STM32H7
#include <stm32h7xx_hal.h>
#include <stm32h7xx_hal_def.h>
#include <stm32h7xx_hal_gpio.h>
#include <stm32h7xx_hal_tim.h>
#endif

#ifdef STM32WB
#include <stm32wbxx_hal.h>
#include <stm32wbxx_hal_def.h>
#include <stm32wbxx_hal_gpio.h>
#include <stm32wbxx_hal_tim.h>
#endif


#include <stdint.h>
#include "assert.h"

// copied from core_cm4.h //////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
  #define   __I     volatile             /*!< defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< defines 'write only' permissions                */
#define     __IO    volatile             /*!< defines 'read / write' permissions              */
////////////////////////////////////////////////////////////////////////////////////////////////

#define FOREVER while(1)
#define NEVER while(0)
#define NOTHING {}

#ifndef __cplusplus
typedef unsigned char bool;
//static const bool False = 0;
//static const bool True = 1;
#endif

#define IO32 *(uint32_t *)
#define IO16 *(uint16_t *)
#define IO8  *(uint8_t *)

#define SWAP2(x) ( (((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8) )
#define SWAP4(x) ( (((x) & 0x000000ff) << 24) | (((x) & 0x0000ff00) << 8) | (((x) & 0x00ff0000) >> 8) | (((x) & 0xff000000) >> 24) )
#define SWAP8(x) ( (((x) & 0x00000000000000ff) << 56) | (((x) & 0x000000000000ff00) << 40) | (((x) & 0x0000000000ff0000) << 24) | (((x) & 0x00000000ff000000) <<  8) | (((x) & 0x000000ff00000000) >>  8) | (((x) & 0x0000ff0000000000) >> 24) | (((x) & 0x00ff000000000000) >> 40) | (((x) & 0xff00000000000000) >> 56) )

#define true 1
#define false 0

#ifndef NULL
#define NULL 0
#endif

#define kb *1024
#define mb *1024*1024

#define ABS(x) (((signed)(x))>=0)?(x):-(x)
#define CINC(x,y) {(x)++; if ((x) == (y)) (x) = 0; }
#define CDEC(x,y) {if ((x) == 0) (x) = (y); (x)--; }

float f_abs(float x);
uint32_t i_abs(int32_t x);

extern uint32_t SystemCoreClockMHz;
extern char HexAlphabet[];
void delay_stupid(__IO uint32_t nCount); // for stupid delays
void DelayCorrect();
//void SystemClock_Config_(void);

#if 0
void setupTimeOut(uint32_t ms);
void resetTimeOut();
bool isTimeOut();
#endif

//uint32_t millis();
void delayms(uint32_t ms); // delay, ms; max 1,118,481 ms == 1,118 s == 18.6 min
void delayus(uint32_t us); // delay, us; max 139,810us = 139.810 ms
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
void HAL_Delay(__IO uint32_t Delay);

bool IsDecDigit(char c);
bool IsAlphaLower(char c);
bool IsAlphaUpper(char c);
bool IsAlpha(char c);
bool IsAlphaDig(char c);
bool IsName1stSymbol(char c);
bool IsNameSymbol(char c);

uint8_t atomic_set_var_B (uint8_t *pVar, uint8_t newVal);

// Interrupts
extern volatile uint32_t IrqTrigger;
#define TRIG_TIM2 0x00000001
#define TRIG_TIM7 0x00000002

// Timer actions
#define TRIG_1MS     0x00000010
//#define TRIG_10MS    0x00000020
//#define TRIG_100MS   0x00000040
//#define TRIG_1000MS  0x00000080
//#define TRIG_ANYMS   0x000000F0

// CAN actions
#define TRIG_CAN_RX0 0x00000100
#define TRIG_CAN_RX1 0x00000200

#ifdef __cplusplus
}
#endif


