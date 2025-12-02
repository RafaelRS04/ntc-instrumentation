#ifndef NTC_HEADER_INCLUDED
#define NTC_HEADER_INCLUDED

#include <Arduino.h>

namespace NTC {
    void begin(uint8_t analog_pin, float max_voltage);
    float read_temperature();
    float read_voltage();
};

#endif /* NTC.hpp */