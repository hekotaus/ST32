#ifndef _LXST32SWITCH_H_
#define _LXST32SWITCH_H_

#include "ST32GPIO.h"

class tSwitch {
private:
    bool ActiveState = true; // Pushed state for buttons, "ON" state for switches
    GPIO_TypeDef *Gpio;
    uint8_t PinNo;
    uint32_t Mask = 0;
    int32_t Pull = 0;
public:
    tSwitch(GPIO_TypeDef *gpio, uint8_t pinNo, bool activeState, int32_t pull) {  // GPIO_NOPULL, GPIO_PULLUP,  GPIO_PULLDOWN
        Gpio = gpio;
        PinNo = pinNo;
        Mask = 0x1 << pinNo;
        Pull = pull;
        ActiveState = activeState; 
        ST32_GPIOQuickSetupPinIn(Gpio, PinNo, Pull);
    }
    bool IsActive() const {
        return ActiveState == GetState();
    };
    bool GetState() const { if (!Gpio) return false; else return !!(Gpio->IDR & Mask); }

    void EnableExtI(uint32_t mode) { // M1_INDEX, GPIO_NOPULL, GPIO_MODE_IT_RISING_FALLING);
    	ST32_GPIOQuickSetupPinEXTI(Gpio, PinNo, Pull, mode);
    }
};

class tDoubleSwitch {

public:
	// Individual conditions
	static const uint8_t NC_PUSHED = 0x01;  // Indicates NC matches Pushed condition
	static const uint8_t NO_PUSHED = 0x02; // Indicates NO matches Pushed condition
	// Normal conditions: both pushed or both unpushed
	static const uint8_t UNPUSHED = 0x00; // Indicates bothe NC and NO matches Unpushed condition. Normal work
	static const uint8_t PUSHED = 0x03; // Indicates, both NC and NO match "Pushed" condition. Normal when button pushed
	// Error conditions
	static const uint8_t IN_AIR = NC_PUSHED; // NC is already in air, NO not pushed yet
	static const uint8_t SHORT = NO_PUSHED; // NC is still closed, NO is already pushed
protected:
	tSwitch Switch_NC;
	tSwitch Switch_NO;
	uint8_t State = UNPUSHED;
public:
	uint8_t CheckState() {
        State = UNPUSHED;
        if (Switch_NC.IsActive()) State |= NC_PUSHED;
        if (Switch_NO.IsActive()) State |= NO_PUSHED;
        return State;
    }

public:
    tDoubleSwitch(GPIO_TypeDef *gpio_NC, uint8_t pinNo_NC, bool activeState_NC, int32_t pull_NC,
                  GPIO_TypeDef *gpio_NO, uint8_t pinNo_NO, bool activeState_NO, int32_t pull_NO)
        : Switch_NC(gpio_NC, pinNo_NC, activeState_NC, pull_NC)
        , Switch_NO(gpio_NO, pinNo_NO, activeState_NO, pull_NO)
    { };
//    bool IsContradictory() const { return (state == NC_PUSHED) || (state == NO_PUSHED); }
};

class tEndSwitchDouble : public tDoubleSwitch {
	bool Enabled = true;
	uint8_t contCnt = 0; // Contradictory states counter
	const uint8_t contThreshold = 20; // if contCnt > contThreshold => IsContradictory returns true

public:
    tEndSwitchDouble(GPIO_TypeDef *gpio_NC, uint8_t pinNo_NC, GPIO_TypeDef *gpio_NO, uint8_t pinNo_NO)
        : tDoubleSwitch(gpio_NC, pinNo_NC, true, 0, gpio_NO, pinNo_NO, false, 0)
    {
    }
    bool CheckPushed() {
        return Enabled && (CheckState() != UNPUSHED);
    }
    bool CheckContradictoryFault() { // We can have: (Both pushed) OR (both unpushed) OR temporary (NC pushed and NO unpushed)
    	bool res = false;
    	CheckState();
    	if (!Enabled) return false;
    	if (State == IN_AIR) { // This should not be a stable condition in a spring-loaded button
        	if (contCnt <= contThreshold)
        		contCnt++; // not yet
        	else
        		res = true;
    	} else if (State == SHORT) { // Both contacts connected to common. Faulty switch
        	contCnt = 0;
        	res = true;
    	} else { // Both Pushed and UNPUSHED states are good
    		contCnt = 0; // Good
        }
        return res;
    }
    bool IsEnabled() { return Enabled; };
    void SetEnabled(bool en) { Enabled = en; };
    void EnableExtI(uint32_t modeNC, uint32_t modeNO) {
    	Switch_NC.EnableExtI(modeNC);
    	Switch_NO.EnableExtI(modeNO);
    }
};

#endif
