#include <Wire.h>
#include <NTC.hpp>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET -1
#define NO_VOLTAGE -1.0f
#define NO_TEMPERATURE -1.0f
#define TEXT_BUFFER_LENGTH 20
#define FLOAT_BUFFER_LENGTH 10
#define READ_TIME_MS 250

Adafruit_SH1106 display(OLED_RESET);

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
    NTC::begin(A0, 5.0);
}

void loop() {
    if(millis() - read_time >= READ_TIME_MS) {
        new_temperature = NTC::read_temperature();
        read_time = millis();
    }

    if(new_temperature != temperature) {
        temperature = new_temperature;
        voltage = NTC::read_voltage();

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