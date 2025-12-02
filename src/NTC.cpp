
#include <NTC.hpp>

/* Value for 1 Hz overflow interruptions */
#define COUNTER_INITIAL_VALUE (65536 - (F_CPU / 1024))

static volatile int16_t ntc_read; 
static uint8_t ntc_pin;

ISR(TIMER1_OVF_vect) {
    TCNT1 = COUNTER_INITIAL_VALUE;

    ntc_read = analogRead(ntc_pin);
    ntc_read = map(ntc_read, 0, 1023, 0, 100);
}

void NTC::begin(uint8_t analog_pin, float max_voltage) {
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

    float temperature = 100 - ntc_read + 260;
    temperature = temperature / 10.0f;

    sei();

    return temperature;
}

float NTC::read_voltage() {
    cli();

    float voltage = 5 * ntc_read / 100.0f;
    
    sei();

    return voltage;
}