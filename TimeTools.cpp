#include "TimeTools.h"

tDecimalMsCounter g_system_time_ms;

bool operator != (const tDecimalMsCounter & A, const tDecimalMsCounter & B) {
    return A.i_1ms != B.i_1ms;
}

bool operator == (const tDecimalMsCounter & A, const tDecimalMsCounter & B) {
    return A.i_1ms == B.i_1ms;
}

timems_t operator - (const tDecimalMsCounter & A, const tDecimalMsCounter & B) {
    return A.i_1ms - B.i_1ms;
}

uint32_t millis32() {
    return uint32_t(g_system_time_ms.i_1ms);
}

