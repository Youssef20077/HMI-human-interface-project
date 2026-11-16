# Project Human-Machine Interface (HMI)

## Introduction

An HMI allows users to interact with a system that monitors the temperature, humidity and light intensity of a room through sensors connected to the Arduino. The objective of this project is to monitor the temperature, humidity and light intensity and display those values via an LCD and alert the users if the readings exceed limits set by the user. The reason why monitoring these conditions is so important is to ensure the user has a safe environment that prevents equipment damage or discomfort. This project relates to real-world applications such as monitoring the cabin temperature in vehicles.

## Scope

The hardware used for the human-machine interface project starts with the Arduino, which sends commands to the components that are connected to it. One of these components connected to the Arduino is the LCD, which is connected using the four- pin mode. The pins connected in four-pin mode are D4, D5, D6, and D7. The LCD is also connected to the potentiometer, which adjusts the contrast of the LCD. The sensors connected to the Arduino are the LM35 temperature sensor, which is connected to A0; the humidity sensor, which is connected to digital pin 3. In addition, the LDR, which is connected to A1 of the Arduino. The temperature sensor measures the temperature in degrees Celsius, and the humidity sensor detects the humidity. The LDR monitors the light of its surroundings. The final components connected to the Arduino are the two push buttons, which are connected to D8 and D9. The main purpose of these two buttons is to set limits for the measurements provided by the sensors and to check whether the limits set by the buttons are exceeded. If the limits are exceeded, the Arduino will send commands to the LED connected to digital pin 10, warning the user that the limits are exceeded.

## Software Architecture

![Software Architecture](Human interface design and architecture embedded systems 2026_figure_page_1_1.jpeg)

Arduino_HMI_Modular_final.ino: This is the main program responsible for controlling the overall HMI system. It initializes all hardware components, updates sensor readings, checks button inputs, controls the LED, and displays information on the LCD.

ADC.h: This header file declares the functions used for Analog-to-Digital Conversion (ADC). It allows other modules to access these functions.

ADC.ino: This file contains the functions responsible for initializing the ADC and converting analog signals into digital values. It is used to read the LM35 temperature sensor and LDR.

Buttons.h: This header file declares the functions used to initialize and monitor the push buttons. It allows the main program to access the button functions.

Buttons.ino: This file contains the code responsible for detecting button presses and adjusting sensor limits. Button 1 increases the selected limit, Button 2 decreases it, and pressing both buttons switches between LH and LL.

DHT11.h: This header file declares the functions used to communicate with the DHT11 humidity sensor. It allows other modules to access these functions.

DHT11.ino: This file contains the functions responsible for communicating with the DHT11 sensor and obtaining humidity readings. It processes the digital signals received from the sensor.

LCD.h: This header file declares the functions used to control the LCD, including displaying characters, strings, and numbers. It allows other modules to access these functions.

LCD.ino: This file contains the code responsible for initializing and controlling the 16×2 LCD in 4-bit mode. It displays sensor readings, upper and lower limits, and system status messages.

LED.h: This header file declares the functions responsible for initializing and updating the LED. It allows the main program to access the LED control functions.

LED.ino: This file contains the code responsible for controlling the LED based on sensor readings and their limits. The LED provides a visual indication when a sensor reading exceeds its acceptable range.

Sensors.h: This header file declares the functions and variables used to manage the sensors and their limits. It allows other modules to access sensor readings and limit values.

Sensors.ino: This file contains the functions responsible for updating temperature, humidity, and light readings. It also manages the upper and lower limits and checks whether sensor readings are within the acceptable range.

UART.h: This header file declares the functions used for UART serial communication. It allows other modules to transmit information through the serial interface.

UART.ino: This file contains the functions responsible for initializing UART communication and transmitting messages. It sends information such as button activity and limit adjustments to the Serial Monitor.

## System flowchart

![System flowchart](Human interface design and architecture embedded systems 2026_figure_page_3_1.jpeg)

## System communication

The ATmega328P microcontroller communicates with the connected components to control the overall system. The LM35 and LDR send analog signals, which are converted into digital values using the ADC module. The DHT11 sends digital humidity readings directly to the microcontroller. The processed measurements are then displayed on the LCD. The push buttons allow users to adjust the upper and lower limits. When sensor readings fall outside these limits, the microcontroller activates the LED to warn the user of abnormal conditions.
