
#include <NTC.hpp>

/* Value for 1 Hz overflow interruptions */
#define COUNTER_INITIAL_VALUE (65536 - (F_CPU / 1024))

/* Voltage estimative calculation via analog readed values */
#define CALCULATE_VOLTAGE(ntc_read) (5 * ntc_read / 1023.0f)

static volatile int16_t ntc_read; 
static uint8_t ntc_pin;

ISR(TIMER1_OVF_vect) {
    TCNT1 = COUNTER_INITIAL_VALUE;

    ntc_read = analogRead(ntc_pin);
}

NTC::NTC(uint8_t analog_pin, float slope, float intercept) {
    this->analog_pin = analog_pin;
    this->slope = slope;
    this->intercept = intercept;
}

void NTC::begin() {
    pinMode(analog_pin, INPUT);

    cli();

    ntc_pin = analog_pin;

    /* Setup Timer/Counter 1 */
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << CS12 | 1 << CS10);
    TCNT1 = COUNTER_INITIAL_VALUE;

    /* Unmask Timer/Counter interrupts */
    TIMSK1 |= (1 << TOIE1);

    sei();
}

float NTC::read_temperature() {
    cli();

    float temperature = CALCULATE_VOLTAGE(ntc_read) * slope + intercept;

    sei();

    return temperature;
}

float NTC::read_voltage() {
    cli();

    float voltage = CALCULATE_VOLTAGE(ntc_read);
    
    sei();

    return voltage;
}