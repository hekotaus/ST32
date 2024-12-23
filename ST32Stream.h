#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "hwversion.h"

#ifdef STM32G0
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_uart.h"
#endif


#ifdef STM32H5
#include "stm32h5xx_hal.h"
#include "stm32h5xx_hal_uart.h"
#endif

#ifdef STM32H7
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_uart.h"
#endif

#ifdef STM32WB
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_uart.h"
#endif


#include <stdint.h>

typedef int64_t (*tTimeCallback)();
class Stream { // UART in Arduino style
private:
	tTimeCallback CbGetTime_us = nullptr;
	uint64_t TimeoutCh_us = 0;
	float BitTime_us = 0;
public:
	const UART_HandleTypeDef* Usart = nullptr;

	Stream(UART_HandleTypeDef* usart, tTimeCallback cbGetTime)
	: CbGetTime_us(cbGetTime)
	, Usart(usart)
	{};

	bool write_block(const char *pData, const uint16_t size, uint16_t *pbytes_sent = nullptr) {
        if (Usart->gState != HAL_UART_STATE_READY) return 0; // Check that a Tx process is not already ongoing
        if (pData == nullptr) return 0;
        if (size == 0) return 0;

        bool timeout = false;
        int64_t startTime = CbGetTime_us();
        int64_t toTime = startTime + size * TimeoutCh_us;
        uint16_t sent = 0;
        while ((sent != size) && !timeout) {
        	while( ((Usart->Instance->ISR & UART_FLAG_TXE) == 0) && !timeout) {
        		timeout = (CbGetTime_us() > toTime);
        	}
        	if (!timeout) { // Send byte
        		Usart->Instance->TDR = *pData++;
        		++sent;
        	}
        }
        if (pbytes_sent != nullptr) *pbytes_sent = sent;
        return (size == sent);
	}

    bool write_ch(uint8_t ch) {
        if (Usart->gState != HAL_UART_STATE_READY) return 0; // Check that a Tx process is not already ongoing
        uint64_t startTime = CbGetTime_us();
        bool timeout = false;
        while( ((Usart->Instance->ISR & UART_FLAG_TXE) == 0) && !timeout) {
        	timeout = (CbGetTime_us() - startTime) > TimeoutCh_us;
        };
        if (timeout)
            return false;
        Usart->Instance->TDR = ch;
        return true;
	}

    void resetErr() {
    	if (Usart->Instance->ISR & 0xF) // All errors
    		Usart->Instance->ISR |= 0xF;
    }

	bool available() {
	    return !!(Usart->Instance->ISR & (UART_FLAG_RXNE | UART_FLAG_RXFNE));
	} // have data to read

	bool read_block(uint8_t *pData, const uint16_t size, uint16_t *pbytes_received, uint32_t timeout_us) {
        if (Usart->gState != HAL_UART_STATE_READY) return 0; // Check that a Tx process is not already ongoing
        if (pData == nullptr) return 0;
        if (size == 0) return 0;

        bool timeout = false;
        int64_t startTime = CbGetTime_us();
        int64_t toTime = startTime + timeout_us;
        uint16_t received = 0;
        while ((received != size) && !timeout) {
        	while( !available() && !timeout) {
        		int64_t now = CbGetTime_us();
        		timeout = (now > toTime);
        	}
        	if (!timeout) { // Send byte
        		*pData++ = (uint8_t)(Usart->Instance->RDR & 0xFF);
        		++received;
        	}
        }
        if (pbytes_received != nullptr) *pbytes_received = received;
        return (size == received);
	}

	//uint16_t read() {
	//    uint8_t data = 0;
	//    HAL_StatusTypeDef res = HAL_UART_Receive(Usart, &data, 1, 1);
	//    if (res == HAL_OK)
	//        return data;
	//    else
	//        return -1;
	//}

    bool read_ch(uint8_t *data) {
        if (Usart->RxState != HAL_UART_STATE_READY) return false; // Check that a Rx process is not already ongoing
        if (data == nullptr) return false;
        //Usart->Instance->CR1 |= USART_CR1_RE;
        uint64_t startTime = CbGetTime_us();
        int64_t toTime = startTime + TimeoutCh_us;
        bool timeout = false;
        while( !available() && !timeout) {
        	timeout = (CbGetTime_us() > toTime);
        };
        //Usart->Instance->CR1 &= ~USART_CR1_RE;
        if (timeout)
        	return false;
//HAL_UART_Receive(huart, pData, Size, Timeout)
        *data = (uint8_t)(Usart->Instance->RDR & 0xFF);
        return true;
	};

//	void defaults() {
//	}; // ???

	void begin(uint32_t speed) {
		if (speed == 0) return;
		BitTime_us = 1'000'000.0f / speed;
		TimeoutCh_us = uint64_t(1'000'000.0f * 10.0f * 2.0f / speed);
		Usart->Instance->CR1 |= USART_CR1_RE;
	};

	float getBitTime_us() { return BitTime_us; }

	void flush() {
		uint8_t ch;
		while(available())
			read_ch(&ch);
	}

};
#ifdef __cplusplus
}
#endif

