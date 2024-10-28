# Ultrasonic Distance and Temperature Sensor Alert System

This project combines an ultrasonic distance sensor and an LM35 temperature sensor with an ESP32 to monitor distance and temperature. If a specified threshold for either is crossed, an alert system with a buzzer and LED is activated.

## Table of Contents

- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Pin Configuration](#pin-configuration)
- [Code Explanation](#code-explanation)
- [Usage](#usage)
- [Notes](#notes)

## Project Overview

The project continuously measures:
1. **Distance**: Uses the HC-SR04 ultrasonic sensor to detect objects within a maximum distance (100 cm).
2. **Temperature**: Reads temperature from the LM35 sensor.

An alert system activates when:
- An object is detected within 20 cm.
- Temperature exceeds 40°C.

## Hardware Requirements

- ESP32 microcontroller
- HC-SR04 Ultrasonic Distance Sensor
- LM35 Temperature Sensor
- Buzzer
- LED

## Pin Configuration

| Component            | ESP32 Pin |
|----------------------|-----------|
| Buzzer               | GPIO 2    |
| Ultrasonic Trig Pin  | GPIO 5    |
| Ultrasonic Echo Pin  | GPIO 18   |
| LED                  | GPIO 4    |
| LM35 Temperature Pin | GPIO 33   |

## Code Explanation

### Key Constants

- **BUZZER_PIN**: Pin connected to the buzzer.
- **TRIG_PIN & ECHO_PIN**: Ultrasonic sensor pins.
- **LED_PIN**: Pin for the LED.
- **MAX_DISTANCE**: Maximum distance threshold for object detection (100 cm).
- **ADC_VREF_mV**: ADC reference voltage of the ESP32.
- **TEMP_THRESHOLD**: Temperature threshold (40°C).

### Functions

- **`readDistance()`**: Sends an ultrasonic pulse, measures the echo time, and calculates the distance.
- **`loop()`**: Measures distance and temperature and activates the alert if thresholds are met.

## Usage

1. **Upload the Code** to the ESP32.
2. **Monitor Serial Output** for real-time distance and temperature data.
3. **Alert System Activation**:
   - The buzzer and LED will turn on if an object is within 20 cm.
   - The buzzer and LED will also turn on if the temperature goes above 40°C.

## Notes

- **Power Requirements**: Ensure the ESP32 and sensors are powered adequately.
- **Serial Communication**: The Serial Monitor is used at a baud rate of 115200 for distance readings and 9600 for temperature readings.
- **Timeout**: The ultrasonic sensor includes a 6 ms timeout, limiting readings to a 100 cm max range.

