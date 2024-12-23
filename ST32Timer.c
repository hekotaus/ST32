#include "ST32Timer.h"
//#define KR_KEY_RELOAD    ((uint16_t)0xAAAA)

//void IWDG_ReloadCounter(void) {
//  IWDG->KR = KR_KEY_RELOAD;
//}

//uint32_t i_tim7 = 0;

//void testfunc() {
//  GPIOH->ODR = 0x1000;//0x1<<12;
//};
#ifdef TIM2
void TIM2_IRQHandler(void) {
  if (TIM2->SR) TIM2->SR = 0;
}
#endif

TIM_Base_InitTypeDef  TIM_TimeBaseStructure;

#if defined TIM7
void LXST32_Init1msTimer7() {
  __HAL_RCC_TIM7_CLK_ENABLE();
  //TIM_TimeBaseStructure.Period = 250; // ARR,
  TIM_TimeBaseStructure.Prescaler = SystemCoreClockMHz-1; // 1MHz
  TIM_TimeBaseStructure.Period = 1000; // ARR, // 1000us
  TIM_TimeBaseStructure.ClockDivision = 0;
  TIM_TimeBaseStructure.CounterMode = TIM_COUNTERMODE_UP;
  TIM_Base_SetConfig(TIM7, &TIM_TimeBaseStructure);
  TIM7->DIER = 0x1; // Update interrupt enabled
  TIM7->CR1 = 0x81; // Auto-reload preload enable | Counter enabled
#ifdef TIM7_IRQn
  NVIC_EnableIRQ(TIM7_IRQn);
#endif

#ifdef STM32G071 //TIM7_LPTIM2_IRQn
  NVIC_EnableIRQ(TIM7_LPTIM2_IRQn);
#endif

#ifdef STM32G070 //TIM7_LPTIM2_IRQn
  NVIC_EnableIRQ(TIM7_IRQn);
#endif

};
//#endif
#endif // TIM7


#if defined TIM17
void ST32_Init1msTimer17() {
  __HAL_RCC_TIM17_CLK_ENABLE();
  //TIM_TimeBaseStructure.Period = 250; // ARR,
  TIM_TimeBaseStructure.Prescaler = SystemCoreClockMHz-1; // 1MHz
  TIM_TimeBaseStructure.Period = 1000; // ARR, // 1000us
  TIM_TimeBaseStructure.ClockDivision = 0;
  TIM_TimeBaseStructure.CounterMode = TIM_COUNTERMODE_UP;
  TIM_Base_SetConfig(TIM17, &TIM_TimeBaseStructure);
  TIM17->DIER = 0x1; // Update interrupt enabled
  TIM17->CR1 = 0x81; // Auto-reload preload enable | Counter enabled



#ifdef STM32WB55
    NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);
#endif

#ifdef STM32G071 //TIM7_LPTIM2_IRQn
  NVIC_EnableIRQ(TIM7_LPTIM2_IRQn);
#endif

#ifdef STM32G070 //TIM7_LPTIM2_IRQn
  NVIC_EnableIRQ(TIM7_IRQn);
#endif

};
//#endif
#endif // TIM7

#if defined TIM5
void LXST32_Init1usTickTimer5() {
  __HAL_RCC_TIM5_CLK_ENABLE();
  //TIM_TimeBaseStructure.Period = 250; // ARR,
  TIM_TimeBaseStructure.Prescaler = SystemCoreClockMHz-1; // 1MHz
  TIM_TimeBaseStructure.Period = 0xffffffff; // ARR,
  TIM_TimeBaseStructure.ClockDivision = 0;
  TIM_TimeBaseStructure.CounterMode = TIM_COUNTERMODE_UP;
  TIM_Base_SetConfig(TIM5, &TIM_TimeBaseStructure);
  TIM5->DIER = 0x1; // Update interrupt enabled
  TIM5->CR1 = 0x81; // Auto-reload preload enable | Counter enabled
  //NVIC_EnableIRQ(TIM5_IRQn);
};
#endif

#ifdef TIM2
void LXST32_InitFastTimer() {
  TIM_HandleTypeDef    TimHandle;
  __HAL_RCC_TIM2_CLK_ENABLE();
  TimHandle.Instance = TIM2;
  if (FAST_TIMER_PERIOD_uS == 100)
    TimHandle.Init.Period            = 50; // 100uS
  if (FAST_TIMER_PERIOD_uS == 10)
    TimHandle.Init.Period            = 5; // 10uS
  TimHandle.Init.Prescaler         = SystemCoreClockMHz-4;
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TimHandle.Init.RepetitionCounter = 0;
  if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK);
  if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK) ;
};
#endif



