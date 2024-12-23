#pragma once

#include <stdint.h>

using timems_t = int64_t;

class tDecimalMsCounter {
private:
    volatile timems_t _i_1ms = 0; // 2^32ms = 49days
    volatile timems_t _i_10ms = 0;
    volatile timems_t _i_100ms = 0;
    volatile timems_t _i_1000ms = 0;
    volatile uint8_t _i_1ms_10 = 0; // count from 0 to 9
    volatile uint8_t _i_10ms_10 = 0; // count from 0 to 9
    volatile uint8_t _i_100ms_10 = 0; // count from 0 to 9
    volatile bool _Trig_10ms = true;
    volatile bool _Trig_100ms = true;
    volatile bool _Trig_1000ms = true;

public:

    // This is for R/O access to variables
    volatile const timems_t& i_1ms = _i_1ms; // 2^32ms = 49days
    volatile const timems_t& i_10ms = _i_10ms;
    volatile const timems_t& i_100ms = _i_100ms;
    volatile const timems_t& i_1000ms = _i_1000ms;
    volatile const uint8_t& i_1ms_10 = _i_1ms_10; // count from 0 to 9
    volatile const uint8_t& i_10ms_10 = _i_10ms_10; // count from 0 to 9
    volatile const uint8_t& i_100ms_10 = _i_100ms_10; // count from 0 to 9
    volatile const bool& Trig_10ms = _Trig_10ms;
    volatile const bool& Trig_100ms = _Trig_100ms;
    volatile const bool& Trig_1000ms = _Trig_1000ms;


    void tick() {
        _Trig_10ms = false;
        _Trig_100ms = false;
        _Trig_1000ms = false;

        _i_1ms++; // Global
        _i_1ms_10++;
        if (_i_1ms_10 == 10) {
            _Trig_10ms = true;
            _i_1ms_10 = 0; // Reset
            _i_10ms++; // Global
            _i_10ms_10++; //
            if (_i_10ms_10 == 10) {
                _Trig_100ms = true;
            	_i_10ms_10 = 0; // Reset
            	_i_100ms++; //
            	_i_100ms_10++; // Local
                if (_i_100ms_10 == 10) {
                    _Trig_1000ms = true;
                    _i_100ms_10 = 0; // Reset
                    _i_1000ms++; //
                }
            }
        }
    }



};

bool operator == (const tDecimalMsCounter & A, const tDecimalMsCounter & B);
bool operator != (const tDecimalMsCounter & A, const tDecimalMsCounter & B);
timems_t operator - (const tDecimalMsCounter & A, const tDecimalMsCounter & B);


extern tDecimalMsCounter g_system_time_ms;

uint32_t millis32(); // For ESP
