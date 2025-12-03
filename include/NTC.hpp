#ifndef NTC_HEADER_INCLUDED
#define NTC_HEADER_INCLUDED

#include <Arduino.h>

class NTC {
public:
    NTC(uint8_t analog_pin, float slope, float intercept);

    void begin();
    float read_temperature();
    float read_voltage();

private:
    uint8_t analog_pin;
    float slope;
    float intercept;
};

#endif /* NTC.hpp */