#pragma once
#include "LXST32GPIO.h"

class tGPO { // GP output
    GPIO_TypeDef *Port;
    uint8_t PinNo;
    bool State;
    void Init() {
        LXST32_GPIOQuickSetupPinOut(Port, PinNo, State);
    };
public:
    tGPO(GPIO_TypeDef *port, uint8_t pinNo, bool defState) : Port(port), PinNo(pinNo), State(defState) { // Assign and Init
        Init();
    };

    void SetState(bool state) {
        State = state;
        LXST32_SetGPIOPin(Port, PinNo, State);
    };
};
