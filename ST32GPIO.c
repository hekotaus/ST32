//#include "stm32h7xx_it.h"
//#include "stm32h7xx_hal_conf.h"
//#include "stm324xg_eval.h"
#include "ST32Tools.h"
//#include "..\Common\MGHW.h"
#include "hwversion.h"
#include "ST32GPIO.h"

const uint8_t GPIO_PORT_WIDTH = 16;

//typedef struct {
//  GPIO_TypeDef *gpio;
//  uint8 PinNo;
//} tHWRevGPIORecord, *pHWRevGPIORecord;

//tHWRevGPIORecord HWRevisionGPIO[7] = { // DIO 1..7
//  GPIOI8,
//  GPIOI9,
//  GPIOI11,
//  GPIOD7,
//  GPIOD6,
//  GPIOD5,
//  GPIOD4
//};

//#define HW_REV_NUM 1
//uint8 ST32_HWRevision = 0;
//char *ST32_HWRevisionS = NULL;
//char *ST32_HWRevisions[HW_REV_NUM] = {
//  "PrototypeA"
//};

//void ST32_DIOInit() {
//#ifndef EV_BOARD
//  for (uint8 i = DIO1; i < DIO_LAST; i++) {
//    Galvo_GPIOQuickSetupPinIn(DigIO[i].gpio, DigIO[i].PinNo, -1);
//  };
//  for (uint8 i = 0; i < 7; i++) {
//    Galvo_GPIOQuickSetupPinIn(HWRevisionGPIO[i].gpio, HWRevisionGPIO[i].PinNo, -1);
//  }
//#endif
//}

//void ST32_GetHWRevision() {
//  ST32_HWRevision = 0;
//#ifndef EV_BOARD
//  for (uint8 i = DIO1; i < 7; i++) {
//    ST32_HWRevision|=((GetGPIOPin(HWRevisionGPIO[i].gpio, HWRevisionGPIO[i].PinNo)?1:0) << i);
//  };
//#endif
//  if (ST32_HWRevision < HW_REV_NUM) {
//    ST32_HWRevisionS = ST32_HWRevisions[Galvo_HWRevision];
//  } else {
//    ST32_HWRevisionS = "ERROR";
//    ST32_HWRevision = 0xff;
//  }
//}

//tDigInRecord DigIO[DIO_LAST] = {
//  0, GPIONULL, // dummy
//#ifdef MS_REV
//#if MS_REV<REV_C
//  0, GPIOH4,
//  0, GPIOH5,
//  0, GPIOH8,
//  0, GPIOH9,
//  0, GPIOH13,
//  0, GPIOH14
//#else
//  0, GPIOH4,
//  0, GPIOH5,
//  0, GPIOH8,
//  0, GPIOH9,
//#endif
//#endif

//#ifdef IO_REV
//  0, GPIOG6, //1
//  0, GPIOG7, //2
//  0, GPIOG9, //3
//  0, GPIOG10,//4
//  0, GPIOG12,//5
//  0, GPIOG15,//6
//  0, GPIOH4, //7
//  0, GPIOH5, //8
//  0, GPIOH8, //9
//  0, GPIOH9, //10
//#endif
//}


//uint8 ST32_DINRead(uint8 Ch) {
//  DigIO[Ch].Value = GetGPIOPin(DigIO[Ch].gpio, DigIO[Ch].PinNo)?0:1;  // Inverted!
//  return DigIO[Ch].Value;
//}

bool ST32_PowerOnAllGPIOs() {
	static bool inited = false;
	if (!inited) {
#ifdef __HAL_RCC_GPIOA_CLK_ENABLE
    __HAL_RCC_GPIOA_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_GPIOB_CLK_ENABLE
    __HAL_RCC_GPIOB_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_GPIOC_CLK_ENABLE
    __HAL_RCC_GPIOC_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_GPIOD_CLK_ENABLE
    __HAL_RCC_GPIOD_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_GPIOE_CLK_ENABLE
    __HAL_RCC_GPIOE_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_GPIOF_CLK_ENABLE
    __HAL_RCC_GPIOF_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_GPIOH_CLK_ENABLE
    __HAL_RCC_GPIOH_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_GPIOI_CLK_ENABLE
    __HAL_RCC_GPIOI_CLK_ENABLE();
#endif
        inited = true;
	}
	return true;
}

uint8_t ST32_GetGPIOPin(GPIO_TypeDef *gpio, uint8_t pinNo) {
	if ((gpio == NULL) || (pinNo >= GPIO_PORT_WIDTH)) return 0xff;
    return HAL_GPIO_ReadPin(gpio, 0x1 << pinNo);
}


// Modes: GPIO_MODE_IT_RISING, GPIO_MODE_IT_FALLING, GPIO_MODE_IT_RISING_FALLING, GPIO_MODE_EVT_RISING, GPIO_MODE_EVT_FALLING, GPIO_MODE_EVT_RISING_FALLING
// Pull: GPIO_NOPULL, GPIO_PULLUP,  GPIO_PULLDOWN
#ifdef STM32H
void ST32_GPIOEnableEXTI(uint8_t pinNo) {
	if (pinNo >= GPIO_PORT_WIDTH) return;
    HAL_NVIC_SetPriority(EXTI0_IRQn << pinNo, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn << pinNo);
}
#endif

void ST32_GPIOQuickSetupPinEXTI(GPIO_TypeDef *gpio, uint8_t pinNo, uint32_t pull, uint32_t mode) {
	if ((gpio == NULL) || (pinNo >= GPIO_PORT_WIDTH)) return;
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pin = 0x1 << pinNo;
    GPIO_InitStructure.Mode = mode;
    GPIO_InitStructure.Pull = pull;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Alternate = GPIO_MODE_INPUT;
    HAL_GPIO_Init(gpio, &GPIO_InitStructure);
    ST32_GPIOEnableEXTI(pinNo);
}

void ST32_GPIOQuickSetupPinIn(GPIO_TypeDef *gpio, uint8_t pinNo, uint32_t pull) {
	if ((gpio == NULL) || (pinNo >= GPIO_PORT_WIDTH)) return;
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pin = 0x1 << pinNo;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = pull;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Alternate = GPIO_MODE_INPUT;
    HAL_GPIO_Init(gpio, &GPIO_InitStructure);
}

void ST32_GPIOQuickSetupPinOut(GPIO_TypeDef *gpio, uint8_t pinNo, uint32_t State) {
	if ((gpio == NULL) || (pinNo >= GPIO_PORT_WIDTH)) return;
    // ST32_PowerOnAllGPIOs(); must be performed before settin up the pins
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = 0x1 << pinNo;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    //GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(gpio, &GPIO_InitStructure);
    ST32_SetGPIOPin(gpio, pinNo, !!State);
}

//uint8 ST32_GetGPIOPinFull(GPIO_TypeDef *gpio, uint8 PinNo) {
//  if ((gpio) && (PinNo!=0xff)) {
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Pin = 0x1 << PinNo;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//    GPIO_Init(gpio, &GPIO_InitStructure);
//    return GPIO_ReadInputDataBit(gpio, 0x1 << PinNo);
//  } else return 0xff;
//}

void ST32_SetGPIOPin(GPIO_TypeDef *gpio, uint8_t pinNo, bool State) {
	if ((gpio == NULL) || (pinNo >= GPIO_PORT_WIDTH)) return;
    if (State)
      gpio->BSRR |= (0x1 << pinNo);
    else
      gpio->BSRR |= (0x1 << (pinNo + GPIO_PORT_WIDTH));
}

//void ST32_SetGPIOPinFull(GPIO_TypeDef *gpio, uint8 PinNo, bool State) {
//  if ((gpio) && (PinNo!=0xff)) {
//   GPIO_InitTypeDef GPIO_InitStructure;
//   GPIO_InitStructure.GPIO_Pin = 0x1 << PinNo;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//   GPIO_Init(gpio, &GPIO_InitStructure);
//    if (State)
//      gpio->BSRRL = 0x1 << PinNo;
//    else
//      gpio->BSRRH = 0x1 << PinNo;
//  }
//}
