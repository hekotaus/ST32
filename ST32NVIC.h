#ifndef _LXST32_NVIC_H_
#define _LXST32_NVIC_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "ST32Tools.h"

void ST32_NVICInit(void);
//void EnableEXTIs(uint32_t mask); // use bitmask 0x0000FFFF
void EnableInterrupts();
void DisableInterrupts();

#ifdef __cplusplus
}
#endif

#endif
