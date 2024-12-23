#pragma once



#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32H5
#include <stm32h5xx_hal_fdcan.h>
#endif

#ifdef STM32H7
#include <stm32h7xx_hal_fdcan.h>
#endif

#include <string.h>

static const int CanFrameSize = 8;

#ifdef STM32H
struct tCanOutMessage {
    FDCAN_TxHeaderTypeDef TxHeader; // Can Header
    uint8_t Data[CanFrameSize];
    tCanOutMessage() {};
    tCanOutMessage(FDCAN_TxHeaderTypeDef txHeader, uint8_t *data) {
    	TxHeader = txHeader;
    	if (txHeader.DataLength <= CanFrameSize)
    		memcpy(Data, data, txHeader.DataLength);
    }
};

struct tCanInMessage {
    FDCAN_RxHeaderTypeDef RxHeader; // Can Header
    uint8_t Data[CanFrameSize];
    tCanInMessage() {};
    tCanInMessage(FDCAN_RxHeaderTypeDef rxHeader, uint8_t *data) {
    	RxHeader = rxHeader;
    	if (rxHeader.DataLength <= CanFrameSize)
    		memcpy(Data, data, rxHeader.DataLength);
    }
};
#endif

#ifdef __cplusplus
}
#endif
