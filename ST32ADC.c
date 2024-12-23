//#include "stm32h7xx.h"
#include "string.h"
#include "ST32Tools.h"
#include "ST32ADC.h"
#include "ST32GPIO.h"
//#include "stm32h7xx_adc.h"



#if 0
float LXST32_ADCReadChannel(ADC_TypeDef *pADC, uint32 ch) { // returns Volts
  //  ADC_EOCOnEachRegularChannelCmd(pADC, ENABLE);
  ADC_RegularChannelConfig(pADC, ch, 1, ADC_SampleTime_15Cycles);
  pADC->CR2 |= (uint32_t)ADC_CR2_SWSTART; // Start conversion
  while (!(pADC->SR & ADC_FLAG_EOC)); // Wait end of conversion
  return ((float)(pADC->DR)); // Read value
}

float LXST32_AINReadi(uint32 ch, uint32 iter) { // returns Volts at CPU ADC pin
double res = 0.0, RAWres = 0.0;
uint32 i;
  if (iter>0) {
    for (i = 0; i<iter; i++) {
      LXST32_AINRead(ch);
      res += AIN[ch].Value;
      RAWres += AIN[ch].RAWValue;
    };
    res = res / iter;
    RAWres = RAWres / iter;
    AIN[ch].Value = res;
    AIN[ch].RAWValue = (uint32)RAWres;
  };
  return (float)res;
};

void LXST32_AINsInit() {
  uint32 i;
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
  ADC_StructInit(&ADC_InitStructure);

  /* Enable peripheral clocks *************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_ADC3, ENABLE);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADCs Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_Init(ADC2, &ADC_InitStructure);
  ADC_Init(ADC3, &ADC_InitStructure);

  for(i = 1; i < AIN_LAST; i++) { // "0" is for Evaluation Board potentiometer
    // Init MUX control GPIO pin
    if (AIN[i].DSgpio) SetGPIOPin(AIN[i].DSgpio, AIN[i].DSPinNo, 0);
    // Analogue input
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    if (AIN[i].gpio) {
      GPIO_InitStructure.GPIO_Pin = 0x1 << AIN[i].GPIOPinNo;
      GPIO_Init(AIN[i].gpio, &GPIO_InitStructure);
    };

  };
};

float LXST32_AINRead(uint32 ch) { // returns Volts at CPU ADC pin
  pAINRecord pAIN = &(AIN[ch]);
  if (pAIN->AINNo == AIN_TEMP) ADC_TempSensorVrefintCmd(ENABLE);
  pAIN->Value = 0.0;
  pAIN->RAWValue = 0;
  uint32 fltlen = 100;
  if (pAIN->gpio != NULL) {
    for (uint32 i = 0; i < fltlen; i++) {
      ADC_Cmd(pAIN->pADC, ENABLE);
      ADC_RegularChannelConfig(pAIN->pADC, pAIN->Chan, 1, ADC_SampleTime_15Cycles);
      pAIN->pADC->CR2 |= (uint32_t)ADC_CR2_SWSTART; // Start conversion
      while (!(pAIN->pADC->SR & ADC_FLAG_EOC)); // Wait end of conversion
      pAIN->RAWValue += pAIN->pADC->DR >> 0; // Read value
      ADC_Cmd(pAIN->pADC, DISABLE);
    };
    pAIN->RAWValue = pAIN->RAWValue / fltlen;
    pAIN->Value = (float)pAIN->RAWValue / 4095.0;
  };
  return pAIN->Value;
}
#endif
