#ifndef _LXST32_GPIO_H_
#define _LXST32_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif


extern uint8_t ST32_HWRevision;
extern char *ST32_HWRevisionS;
void ST32_GetHWRevision(); // Call once to read revision to the variable LXST32_HWRevision
// Get port name and pin number separately
#define GPIO_PORT(x,y) x
#define GPIO_PIN(x,y) y
// NULL
#define GPIONULL NULL, 0xFF
// PortA
#define GPIOA0  GPIOA,  0
#define GPIOA1  GPIOA,  1
#define GPIOA2  GPIOA,  2
#define GPIOA3  GPIOA,  3
#define GPIOA4  GPIOA,  4
#define GPIOA5  GPIOA,  5
#define GPIOA6  GPIOA,  6
#define GPIOA7  GPIOA,  7
#define GPIOA8  GPIOA,  8
#define GPIOA9  GPIOA,  9
#define GPIOA10 GPIOA, 10
#define GPIOA11 GPIOA, 11
#define GPIOA12 GPIOA, 12
#define GPIOA13 GPIOA, 13
#define GPIOA14 GPIOA, 14
#define GPIOA15 GPIOA, 15
// PortB
#define GPIOB0  GPIOB,  0
#define GPIOB1  GPIOB,  1
#define GPIOB2  GPIOB,  2
#define GPIOB3  GPIOB,  3
#define GPIOB4  GPIOB,  4
#define GPIOB5  GPIOB,  5
#define GPIOB6  GPIOB,  6
#define GPIOB7  GPIOB,  7
#define GPIOB8  GPIOB,  8
#define GPIOB9  GPIOB,  9
#define GPIOB10 GPIOB, 10
#define GPIOB11 GPIOB, 11
#define GPIOB12 GPIOB, 12
#define GPIOB13 GPIOB, 13
#define GPIOB14 GPIOB, 14
#define GPIOB15 GPIOB, 15
// PortC
#define GPIOC0  GPIOC,  0
#define GPIOC1  GPIOC,  1
#define GPIOC2  GPIOC,  2
#define GPIOC3  GPIOC,  3
#define GPIOC4  GPIOC,  4
#define GPIOC5  GPIOC,  5
#define GPIOC6  GPIOC,  6
#define GPIOC7  GPIOC,  7
#define GPIOC8  GPIOC,  8
#define GPIOC9  GPIOC,  9
#define GPIOC10 GPIOC, 10
#define GPIOC11 GPIOC, 11
#define GPIOC12 GPIOC, 12
#define GPIOC13 GPIOC, 13
#define GPIOC14 GPIOC, 14
#define GPIOC15 GPIOC, 15
// PortD
#define GPIOD0  GPIOD,  0
#define GPIOD1  GPIOD,  1
#define GPIOD2  GPIOD,  2
#define GPIOD3  GPIOD,  3
#define GPIOD4  GPIOD,  4
#define GPIOD5  GPIOD,  5
#define GPIOD6  GPIOD,  6
#define GPIOD7  GPIOD,  7
#define GPIOD8  GPIOD,  8
#define GPIOD9  GPIOD,  9
#define GPIOD10 GPIOD, 10
#define GPIOD11 GPIOD, 11
#define GPIOD12 GPIOD, 12
#define GPIOD13 GPIOD, 13
#define GPIOD14 GPIOD, 14
#define GPIOD15 GPIOD, 15
// PortE
#define GPIOE0  GPIOE,  0
#define GPIOE1  GPIOE,  1
#define GPIOE2  GPIOE,  2
#define GPIOE3  GPIOE,  3
#define GPIOE4  GPIOE,  4
#define GPIOE5  GPIOE,  5
#define GPIOE6  GPIOE,  6
#define GPIOE7  GPIOE,  7
#define GPIOE8  GPIOE,  8
#define GPIOE9  GPIOE,  9
#define GPIOE10 GPIOE, 10
#define GPIOE11 GPIOE, 11
#define GPIOE12 GPIOE, 12
#define GPIOE13 GPIOE, 13
#define GPIOE14 GPIOE, 14
#define GPIOE15 GPIOE, 15
// PortF
#define GPIOF0  GPIOF,  0
#define GPIOF1  GPIOF,  1
#define GPIOF2  GPIOF,  2
#define GPIOF3  GPIOF,  3
#define GPIOF4  GPIOF,  4
#define GPIOF5  GPIOF,  5
#define GPIOF6  GPIOF,  6
#define GPIOF7  GPIOF,  7
#define GPIOF8  GPIOF,  8
#define GPIOF9  GPIOF,  9
#define GPIOF10 GPIOF, 10
#define GPIOF11 GPIOF, 11
#define GPIOF12 GPIOF, 12
#define GPIOF13 GPIOF, 13
#define GPIOF14 GPIOF, 14
#define GPIOF15 GPIOF, 15
// PortH
#define GPIOH0  GPIOH,  0
#define GPIOH1  GPIOH,  1
#define GPIOH2  GPIOH,  2
#define GPIOH3  GPIOH,  3
#define GPIOH4  GPIOH,  4
#define GPIOH5  GPIOH,  5
#define GPIOH6  GPIOH,  6
#define GPIOH7  GPIOH,  7
#define GPIOH8  GPIOH,  8
#define GPIOH9  GPIOH,  9
#define GPIOH10 GPIOH, 10
#define GPIOH11 GPIOH, 11
#define GPIOH12 GPIOH, 12
#define GPIOH13 GPIOH, 13
#define GPIOH14 GPIOH, 14
#define GPIOH15 GPIOH, 15
// PortI
#define GPIOI0  GPIOI,  0
#define GPIOI1  GPIOI,  1
#define GPIOI2  GPIOI,  2
#define GPIOI3  GPIOI,  3
#define GPIOI4  GPIOI,  4
#define GPIOI5  GPIOI,  5
#define GPIOI6  GPIOI,  6
#define GPIOI7  GPIOI,  7
#define GPIOI8  GPIOI,  8
#define GPIOI9  GPIOI,  9
#define GPIOI10 GPIOI, 10
#define GPIOI11 GPIOI, 11
#define GPIOI12 GPIOI, 12
#define GPIOI13 GPIOI, 13
#define GPIOI14 GPIOI, 14
#define GPIOI15 GPIOI, 15

//Alternative functions
//#define AFT1  GPIO_AF_TIM1
//#define AFT2  GPIO_AF_TIM2
//#define AFT3  GPIO_AF_TIM3
//#define AFT4  GPIO_AF_TIM4
//#define AFT5  GPIO_AF_TIM5
//#define AFT6  GPIO_AF_TIM6
//#define AFT7  GPIO_AF_TIM7
//#define AFT8  GPIO_AF_TIM8
//#define AFT9  GPIO_AF_TIM9
//#define AFT10 GPIO_AF_TIM10
//#define AFT11 GPIO_AF_TIM11
//#define AFT12 GPIO_AF_TIM12
//#define AFT13 GPIO_AF_TIM13
//#define AFT14 GPIO_AF_TIM14
//#define AFT15 GPIO_AF_TIM15


//#ifdef MG_IO
//#define SIG_IN1 GPIOG4
//#define SIG_IN2 GPIOG5
//#endif

extern const uint8_t GPIO_PORT_WIDTH;
bool ST32_PowerOnAllGPIOs();

uint8_t ST32_GetGPIOPin(GPIO_TypeDef *gpio, uint8_t PinNo);
void ST32_SetGPIOPin(GPIO_TypeDef *gpio, uint8_t PinNo, bool State);

void ST32_GPIOEnableEXTI(uint8_t pinNo);
void ST32_GPIOQuickSetupPinEXTI(GPIO_TypeDef *gpio, uint8_t pinNo, uint32_t pull, uint32_t mode);
void ST32_GPIOQuickSetupPinOut(GPIO_TypeDef *gpio, uint8_t pinNo, uint32_t State);
void ST32_GPIOQuickSetupPinIn(GPIO_TypeDef *gpio, uint8_t pinNo, uint32_t pull); // GPIO_NOPULL, GPIO_PULLUP,  GPIO_PULLDOWN


//typedef struct {
//  uint8 Value;
//  GPIO_TypeDef *gpio;
//  uint8 PinNo;
//} tDigInRecord, *pDigInRecord;
//extern tDigInRecord DigIO[];


#ifdef __cplusplus
}
#endif

#endif
