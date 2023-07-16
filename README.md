# ESP8266 Sous Vide

## Overview
This project is a homemade Sous Vide cooker built with an ESP8266. A Sous Vide cooker is a device that allows you to cook food at precise temperatures for a set amount of time. This cooking method is popular with chefs for its precision and consistency. This project was born from a love of cooking and electronics, and the goal is to blend these two passions into a single project.


## How it Works
The ESP8266 is a low-cost Wi-Fi module that can be programmed using the Arduino IDE, making it a great choice for IoT projects. The code for this project utilizes several libraries to manage Wi-Fi connections, read temperature data, and control cooking time.


The main components of the code include:

1. **TemperatureSensor**: This class is responsible for interfacing with a temperature sensor to get the current temperature and using a circular buffer to make average temperature.

2. **CookingPot**: This class manages the cooking process. It checks if the current temperature has reached the maximum temperature, and if it has, it controls a relay to maintain the temperature. It also has a status LED.

3. **TimerCooker**: This class manages the cooking time. It can start a timer, check if the time is up, and print the remaining time.

4. **SousVideOrchestrator**: This class orchestrates the interaction between the TemperatureSensor, CookingPot and TimerCooker. It controls the flow of the program, managing when to start the timer, how to react when the time is up and updating the temperature measurements.


The `setup()` function initializes the Wi-Fi connection, starts the timer, and sets up the temperature sensor and the cooking pot.

The `loop()` function is the main program loop. It continually reads the temperature, checks if the cooking time has ended, and if not, checks if the maximum temperature has been reached and controls the relay accordingly.

## Motivation
Cooking and electronics are two areas that can seem very different, but when combined, can result in interesting and unique projects like this one. The goal of this project was to create a homemade Sous Vide cooker using an ESP8266 and to learn more about IoT and embedded systems in the process.

## How to Use
To use this project, you need an ESP8266, a temperature sensor (DS18B20 temperature probe), and a relay to control the heat source. Upload the code to the ESP8266 using the Arduino IDE. The ESP8266 will create a Wi-Fi access point that you can connect to. Once connected, the device will start cooking and maintain the temperature for the set amount of time.

## Future Work
There are many potential improvements and additions for this project. Some ideas include adding a user interface to set the cooking temperature and time, integrating with a mobile app for remote monitoring and control, and improving the temperature control algorithm for more precise cooking.
