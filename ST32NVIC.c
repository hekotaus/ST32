#include "ST32NVIC.h"
//     LXST32_NVICInit();
void ST32_NVICInit(void) {
//void LXST32_NVICInit(void) {
  //HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1); HAL_NVIC_EnableIRQ(TIM2_IRQn);
  //HAL_NVIC_SetPriority(TIM7_IRQn, 0, 1); HAL_NVIC_EnableIRQ(TIM7_IRQn);
  //HAL_NVIC_SetPriority(ADC_IRQn, ADC_IRQ_PRIORITY, ADC_SUB_PRIORITY); HAL_NVIC_EnableIRQ(ADC_IRQn);

  /**
  * @brief  Sets the vector table location and Offset.
  * @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VectTab_RAM: Vector Table in internal SRAM.
  *     @arg NVIC_VectTab_FLASH: Vector Table in internal FLASH.
  * @param  Offset: Vector Table base offset field. This value must be a multiple of 0x200.
  * @retval None
  */

#ifdef STMSTD
#ifdef RUN_FROM_RAM
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0); // RAM
#else // FLASH
#ifdef BOOT_LOADER
  NVIC_SetVectorTable(NVIC_VectTab_FLASH + 0x20000, 0);  // For bootloader
#else
  NVIC_SetVectorTable(NVIC_VectTab_FLASH + 0x00000, 0);  // Non-bootloader
#endif

#endif
#endif
  __disable_irq();
};


void EnableInterrupts() {
  __enable_irq();
};

void DisableInterrupts() {
  __disable_irq();
};

