# ESP8266 Sous Vide

## Overview
This project is a homemade Sous Vide cooker built with an ESP8266. A Sous Vide cooker is a device that allows you to cook food at precise temperatures for a set amount of time. This cooking method is popular with chefs for its precision and consistency. The goal of this project is to blend the passions of cooking and electronics into one unified project.

## How it Works
The ESP8266 is a cost-effective Wi-Fi module programmable using the Arduino IDE, making it a top choice for IoT projects. This project's code leverages multiple libraries to handle Wi-Fi connectivity, fetch temperature data, and oversee the cooking duration.

The key components of the code comprise:

1. **TemperatureSensor**: This class manages the interface with a temperature sensor to acquire the present temperature. It also employs a circular buffer for average temperature computation.

2. **CookingPot**: This class supervises the cooking process. It determines if the current temperature has hit the maximum allowable temperature, and if so, it operates a relay to sustain this temperature. It also features a status LED.

3. **TimerCooker**: This class oversees the cooking duration. It has capabilities to initiate a timer, verify if the timer has concluded, and display the remaining time.

4. **SousVideOrchestrator**: This class arranges the interplay between the TemperatureSensor, CookingPot, and TimerCooker. It directs the program's flow, deciding when to start the timer, how to respond when the timer concludes, and updating temperature metrics.

5. **WarmupController**: This class manages the initial warm-up phase of the cooker. It ensures that the water reaches up to 90% of the desired cooking temperature before proceeding to the main cooking phase.

6. **PIDController**: Implements a PID control algorithm to precisely control the temperature, making sure it remains as close as possible to the desired temperature.

7. **MQTTManager**: Manages MQTT communications, allowing the device to receive cooking commands and publish metrics and updates.

The `setup()` function initializes the Wi-Fi connection, configures the temperature sensor, the cooking pot, and other essential components.

The `loop()` function acts as the central program loop. It consistently reads the temperature, checks if the cooking duration has elapsed, and controls the relay based on the current temperature and desired set point.

## Motivation
While cooking and electronics may initially seem like disparate fields, their fusion can lead to captivating and novel projects like this Sous Vide cooker. This endeavor aims to construct a homemade Sous Vide cooker with an ESP8266 while delving deeper into the realms of IoT and embedded systems.

## How to Use
To operationalize this project, you'll need an ESP8266, a DS18B20 temperature probe (or a similar temperature sensor), and a relay to govern the heating mechanism. Load the code onto the ESP8266 using the Arduino IDE. Subsequently, the ESP8266 will initiate a Wi-Fi access point to which you can connect. After establishing the connection, the device commences the cooking process, maintaining the desired temperature for the stipulated duration.

## Future Work
There's ample scope for refining and enhancing this project. Possible future improvements include:

- Developing a user interface for more intuitive temperature and time settings.
- Incorporating a mobile app for remote surveillance and control.
- Further optimizing the PID temperature control algorithm and exploring more advanced control strategies.
- Implementing security features, such as encrypted MQTT communications.
- Designing a printed circuit board (PCB) schematic to make the electronics assembly more accessible and professional.
- Creating a 3D-printable case (STL files) for the electronic components, ensuring the Sous Vide system is both visually appealing and safely contained.
- Making the entire project open-source, allowing enthusiasts and hobbyists to easily replicate, customize, and improve upon the existing design.
- Providing comprehensive documentation on setting up an MQTT server, making it seamless for users to get started with the project.

By encompassing the entire gamut of electronic design, software, and physical casing, this project aims to offer a holistic, end-to-end solution for DIY Sous Vide enthusiasts.
