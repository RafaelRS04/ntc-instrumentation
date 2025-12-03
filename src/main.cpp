#include <Wire.h>
#include <NTC.hpp>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

/* Oled reset pin is -1 */
#define OLED_RESET -1

/* Initial values definitions */
#define NO_VOLTAGE -1.0f
#define NO_TEMPERATURE -1.0f

/* Buffer lengths definitions */
#define TEXT_BUFFER_LENGTH 20
#define FLOAT_BUFFER_LENGTH 10

/* NTC model parameters */
#define INTERCEPT 37.92962f
#define SLOPE -2.89722f

/* Read calls period */
#define READ_TIME_MS 250

Adafruit_SH1106 display(OLED_RESET);
NTC ntc(A0, SLOPE, INTERCEPT);

unsigned long read_time = 0;

float voltage =  NO_VOLTAGE;
float temperature = NO_TEMPERATURE;
float new_temperature = NO_TEMPERATURE;

char text_buffer[TEXT_BUFFER_LENGTH];
char float_buffer[FLOAT_BUFFER_LENGTH];

void setup() {
    Wire.begin();
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    ntc.begin();
}

void loop() {
    if(millis() - read_time >= READ_TIME_MS) {
        new_temperature = ntc.read_temperature();
        read_time = millis();
    }

    if(new_temperature != temperature) {
        temperature = new_temperature;
        voltage = ntc.read_voltage();

        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setCursor(0, 0);

        display.setTextSize(1);
        display.print("\n\n");
        
        display.setTextSize(3);
        dtostrf(temperature, 2, 1, float_buffer);
        snprintf(text_buffer, TEXT_BUFFER_LENGTH, "%s\xa7""C", float_buffer);
        display.println(text_buffer);
        
        display.setTextSize(1);
        dtostrf(voltage, 2, 1, float_buffer);
        snprintf(text_buffer, TEXT_BUFFER_LENGTH, "Voltage: %sV", float_buffer);
        display.println(text_buffer);

        display.display();
    }
}