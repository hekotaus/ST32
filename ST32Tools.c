#include "ST32Tools.h"

uint32_t delayCorr = 0; // used by delay functions to eliminate function related delay; Call DelayCorrect() after SystemCoreClockUpdate()
//uint32 SystemCoreClockMHz = 120;
uint32_t SystemCoreClockMHz = 32;
uint32_t MaxDelayMs = 525000; // for 120MHz
//uint32 MaxDelayMs = ???; // for 64MHz

uint32_t MaxDelayus = 139810; // for 120MHz
//uint32 MaxDelayus = ???; // for 64MHz

uint32_t t7_i_1ms = 0;
uint32_t t7_i_10ms = 0;
uint32_t t7_i_100ms = 0;
uint32_t t7_i_1000ms = 0;
uint32_t t7_i_1ms_10 = 0; // count from 0 to 9
uint32_t t7_i_10ms_10 = 0;
uint32_t t7_i_100ms_10 = 0;


char HexAlphabet[] = "0123456789ABCDEF";

float f_abs(float x) {
  if (x >= 0) return x; else return -x;
}

uint32_t i_abs(int32_t x) {
  if (x >= 0) return (uint32_t)x; else return (uint32_t)(-x);
}


void delay_stupid(__IO uint32_t nCount) {
  __IO uint32_t index = 0; 
  for(index = (100000 * nCount); index != 0; index--) NOTHING;
}

void DelayCorrect() {
  SystemCoreClockMHz = SystemCoreClock / 1000000;
  delayCorr = 119;//1.15 * SystemCoreClockMHz;
  
  MaxDelayMs = 0x00FFFFFF / 125 / SystemCoreClockMHz -1;
  uint32_t sysTickClkKHz = (SystemCoreClockMHz >> 3) * 1000; // SysClk = 64MHz => 8MHz == 8000 ticks/ms
  MaxDelayMs = 0x00FFFFFF / sysTickClkKHz -1; // Used Div8 for SysTick
  
  uint32_t sysTickClkMHz = SystemCoreClockMHz; // SysClk = 64MHz => 64MHz == 64 ticks/us
  MaxDelayus = 0x00FFFFFF / sysTickClkMHz -1; // Used Div1 for SysTick

}

void delaymms(volatile uint32_t ms) { // ms > 1118!!!
  do {
    ms = ms - MaxDelayMs;
    delayms(MaxDelayMs);
  } while (ms > MaxDelayMs);
  if (ms) delayms(ms);
}


void delayms(uint32_t ms) { // max 1,118 ms == 1.118 s
  if (ms > MaxDelayMs) {
    delaymms(ms);// = 1118 @ 120MHz;
  } else {
    if (ms == 0) ms = 1;
    SysTick->CTRL = 0; // Disable counter, interrupt and countflag
    SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK_DIV8; // slow counter

    uint32_t SystTickClkKHz = (SystemCoreClock >> 3) / 1000; // Div8 64,000,000Hz / Div8 / 1000 = 8,000 [ticks/ms]
    SysTick->LOAD = ms * SystTickClkKHz; // ticks per millisecond x ms value

    SysTick->VAL = 0;
    SysTick->CTRL |= 0x1; // Enable counter

    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
      NOTHING;
    SysTick->CTRL = 0; // Disable counter, interrupt and countflag
  }
}

void delayus(uint32_t us) {
  if (us > MaxDelayus) us = MaxDelayus; // max 139,810us = 139.810 ms
  if (us == 0) us = 1;
  SysTick->CTRL = 0; // Disable counter, interrupt and countflag
  SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK; // fast counter
//  SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8; // slow counter

  // init counter
  SysTick->LOAD = us * SystemCoreClockMHz - delayCorr;
  SysTick->VAL = 0;
  SysTick->CTRL |= 0x1; // Enable counter
  while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) NOTHING;
  SysTick->CTRL = 0; // Disable counter, interrupt and countflag
}

bool IsDecDigit(char c) {
  return ((c>='0') && (c<='9'));
}

bool IsAlphaLower(char c) {
  return ((c>='a') && (c<='z'));
}

bool IsAlphaUpper(char c) {
  return ((c>='A') && (c<='Z'));
}

bool IsAlpha(char c) {
  return (IsAlphaUpper(c) || IsAlphaLower(c));
}

bool IsAlphaDig(char c) {
  return (IsAlpha(c) || IsDecDigit(c)); 
}

bool IsName1stSymbol(char c) {
  return (IsAlpha(c) || (c=='_')); 
}

bool IsNameSymbol(char c) {
  return (IsAlpha(c) || IsDecDigit(c) || (c=='_')); 
}

uint8_t atomic_set_var_B (uint8_t *pVar, uint8_t newVal) {
  uint8_t var;
  uint32_t result;
  do {
    var = __LDREXB(pVar);
    var = newVal;
    result = __STREXB(var, pVar);
  } while (result != 0);

  return *pVar;
}
