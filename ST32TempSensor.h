#pragma once
#include "hwversion.h"

extern ADC_HandleTypeDef hadc1;

class tTempSensor {


// Internal temperature sensor
	const double Vref;
#ifdef STM32H563
    const double VrefCalib = 3.3; //
#endif
#ifdef STM32H743
    const double VrefCalib = 3.3; //
#endif
#ifdef STM32WB55
    const double VrefCalib = 3.0; //
#endif
	const double Kref;
#ifdef STM32H563
    const double TS_CAL1_TEMP = 30; // degC
    const double TS_CAL2_TEMP = 130; // degC
    const uint16_t *pTS_CAL1 = (uint16_t *) 0x08FFF814;
    const uint16_t *pTS_CAL2 = (uint16_t *) 0x08FFF818;
#endif

#ifdef STM32H743
    const double TS_CAL1_TEMP = 30; // degC
    const double TS_CAL2_TEMP = 110; // degC
    const uint16_t *pTS_CAL1 = (uint16_t *) 0x1FF1E820;
    const uint16_t *pTS_CAL2 = (uint16_t *) 0x1FF1E840;
#endif


#ifdef STM32WB55
    const double TS_CAL1_TEMP = 30; // degC
    const double TS_CAL2_TEMP = 130; // degC
    const uint16_t *pTS_CAL1 = (uint16_t *) 0x1FFF75A8;
    const uint16_t *pTS_CAL2 = (uint16_t *) 0x1FFF75CA;
#endif


    const double TS_CAL1_ADC; // degC
    const double TS_CAL2_ADC; // degC

    const double K; // Linear slope
    const double B; // Linear offset

    int16_t Temp = 0;
    uint32_t AdcValue = 0x0000;

public:

    explicit tTempSensor(double vref)
    : Vref(vref)
    , Kref(Vref / VrefCalib)
    , TS_CAL1_ADC(*pTS_CAL1)
    , TS_CAL2_ADC(*pTS_CAL2)
    , K((TS_CAL2_TEMP - TS_CAL1_TEMP) / (TS_CAL2_ADC - TS_CAL1_ADC))
    , B(- K * TS_CAL1_ADC + TS_CAL1_TEMP)

    {

    }

    bool RequestTemp() {
    	return (HAL_OK == HAL_ADC_Start(&hadc1));

    }

    int16_t ConvertTemp(uint32_t adcValue) {
    	AdcValue = adcValue;
        double dRes = AdcValue;
        dRes = dRes * Kref;
        dRes = K * dRes + B;
        Temp = int16_t(dRes);
        return Temp;
    }

    int16_t ReadTemp() {
    	if (HAL_ADC_PollForConversion(&hadc1, 20) != HAL_OK)
    		return -273;
        AdcValue = HAL_ADC_GetValue(&hadc1);
        return ConvertTemp(AdcValue);
    }

    int16_t GetTemp() const {
        return Temp;
    }

    uint32_t GetAdcValue() const {
        return AdcValue;
    }
};
