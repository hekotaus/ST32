#ifndef _LXST32ADC_
#define _LXST32ADC_

//Interrup configuration:
#define ADC_IRQ_PRI_GROUP		NVIC_PriorityGroup_2
#define ADC_IRQ_PRIORITY		1 //Priority 1
#define ADC_EXT_PRIORITY		3 //Priority 1 sub-priority 3

typedef struct {
  float Value;
  uint32_t RAWValue;
  uint8_t AINNo;
  ADC_TypeDef *pADC;
  uint8_t Chan;
  GPIO_TypeDef *gpio;
  uint8_t GPIOPinNo;
  GPIO_TypeDef *DSgpio; // DifSel
  uint8_t DSPinNo; // DifSel
} tAINRecord, *pAINRecord;

//void LXST32_AINsInit();
float LXST32_ADCReadChannel(ADC_TypeDef *pADC, uint32_t ch); // obsolete
float LXST32_AINReadi(uint32_t ch, uint8_t mux, uint32_t iter); // returns Volts at CPU ADC pin, averages iter readings
float LXST32_AINRead(uint32_t ch, uint8_t mux); // returns Volts at CPU ADC pin

//internalADC void ADCHardwareInit(void);
//void LXST32_ADCExternalInit(void);

#endif
