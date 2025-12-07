# NTC Thermistor Instrumentation Firmware

## About
Arduino Uno firmware for instrumentation of an NTC thermistor using a Wheatstone bridge and an OPA344PA amplifier. The system reads the amplified analog signal, converts it to temperature, and displays the result on an OLED LCD.

## Technical Results & Specifications

The system was calibrated using linear regression ($R^2 = 0.9976$) to map the conditioned voltage output ($V_O$) to temperature ($T$).

| Parameter | Specification |
| :--- | :--- |
| **Measurement Range** | 23.4°C to 37.9°C |
| **Transfer Function** | $T(V_O) = 37.92962 - 2.89722 \cdot V_O$ |
| **Analog Sensitivity** | $-2.89722 \text{ °C/V}$ |
| **Digital Resolution (10-bit)**| $\approx 0.01415 \text{ °C/bit}$ |
| **Max Linearity Error** | $0.293 \text{ °C}$ ($2.93\%$) |
| **Sampling Rate** | $1 \text{ Hz}$ (Timer1 Interrupt) |

## Firmware Implementation

### Dependencies
To compile this project, the following libraries are required:
* `Adafruit_GFX`
* `Adafruit_SH1106`

### Hardware Pinout
* **A0**: Analog Input (Output from OPA344PA)
* **A4 (SDA) / A5 (SCL)**: SH1106 OLED Display (I2C)

### Operational Logic
1.  **Sampling:** A hardware timer (Timer1) triggers an ISR every 1 second to perform the ADC reading, ensuring precise timing independent of the main loop.
2.  **Processing:** The main loop polls the `NTC` object every 250ms to check for updated values.
3.  **Display:** Updates the OLED screen only when a change in temperature is detected.