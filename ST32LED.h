#ifndef _LXST32_LED_H_
#define _LXST32_LED_H_

//#ifdef __cplusplus
//extern "C" {
//#endif

#include "ST32Tools.h"
#include "ST32GPIO.h"
#include "ST32IOConfig.h"
#include <string>


#ifdef LED1
#define LED1ON ST32_SetGPIOPin(LED1, LED_ON)
#define LED1OFF ST32_SetGPIOPin(LED1, LED_OFF)
#endif

//#ifdef LED2
//#define LED2ON LXST32_SetGPIOPin(LED2, LED_ON)
//#define LED2OFF LXST32_SetGPIOPin(LED2, LED_OFF)
//#endif

//#ifdef LED3
//#define LED3ON LXST32_SetGPIOPin(LED3, LED_ON)
//#define LED3OFF LXST32_SetGPIOPin(LED3, LED_OFF)
//#endif


class tLed {
private:
    GPIO_TypeDef *Gpio = nullptr;
    uint8_t PinNo;// = 0xff;
    bool Polarity = false; // false = active low, true = active high
    bool InitState = false; // false = passive, true = active
    bool FreeHand = true;
public:
    void Init() { // Setup hardware, when clock is running
        ST32_GPIOQuickSetupPinOut(Gpio, PinNo, (Polarity == InitState)); // == represents !XOR
    };
    tLed(GPIO_TypeDef *gpio, uint8_t pinNo, bool polarity, bool initState = false)
    : Gpio(gpio)
    , PinNo(pinNo)
    , Polarity(polarity)
    , InitState(initState)
    {
        Init();
    };
    bool SetState(bool st) {
        if (!FreeHand) return false;
        ST32_SetGPIOPin(Gpio, PinNo, Polarity == st);
        return true;
    };
    void Morse(const std::string &s) {
    	  const uint32_t dot_on = 200; // .
    	  const uint32_t dash_on = 3 * dot_on; // -

    	  const uint32_t symb_off = dot_on;
    	  const uint32_t let_off = 3 * dot_on;
    	  const uint32_t word_off = 7 * dot_on;

//        LedErrorOn(); delayms(d1on); LedErrorOff(); delayms(d1off); LedErrorOn(); delayms(d1on); LedErrorOff(); delayms(d1off); LedErrorOn(); delayms(d1on); LedErrorOff(); delayms(d2off);

        for(const auto c : s) {
        	switch (c) {
        	case '.': SetState(true); delayms(dot_on); SetState(false); delayms(symb_off); break;
        	case '-': SetState(true);; delayms(dash_on); SetState(false); delayms(symb_off); break;
        	case ' ': delayms(let_off - symb_off); break;
        	}
        }
        delayms(word_off - let_off);
    }
};

//#define GPIO_PORT(x,y) x
//#define GPIO_PIN(x,y) y
//LED_MISC_0

//#define LED1ON GPIOI->BSRR |= (0x1<<2)
//#define LED1OFF GPIOI->BSRR |= (0x1<<18)
//#define LED2ON GPIOI->BSRR |= (0x1<<3)
//#define LED2OFF GPIOI->BSRR |= (0x1<<19)

//typedef struct {
//  GPIO_TypeDef *gpio;
//  uint8 PinNo;
//} tESTLED, *pESTLED;

//extern tESTLED LEDs[];

//void LXST32_LEDFlash(GPIO_TypeDef *gpio, uint8 PinNo, uint32 Periodms, uint32 Count);
//void LXST32_LEDInit();

//#ifdef __cplusplus
//}
//#endif


#endif
