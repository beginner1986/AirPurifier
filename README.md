# AirPurifier

Components:
- Wemos D1 mini pro
- Nova Fitness SDS011 Dust Sensor
- BME280 temperature, pressure and humidity sensor

IDE:
- Visual Studio
- Visual Miocro Extension

Libraries:
- for BME280:
    - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
    - Adafruit BME280 Library: https://github.com/adafruit/Adafruit_BME280_Library
- for SDS011:
    - Nova Fitness SDS dust sensors Library: https://github.com/lewapek/sds-dust-sensors-arduino-library
- for file system:
    - SPIFFS (FS.h)
- for WiFi:
    - ESP8266WiFi: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
    - WiFiVlient.h
- for Web Server:
    - ESP8266WebServer: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer

Frontend:
- Bootstrap: https://getbootstrap.com/
- Modified Freelancer theme: https://startbootstrap.com/previews/freelancer/
- Pace - Automatic page load progress bar: https://github.hubspot.com/pace/docs/welcome/

Wiring:
- BME280 (I2C):
    - VCC -> 3V3
    - GND -> G
    - SCL -> D1
    - SDA -> D2

- SDS011 (UART):
    - 5V -> 5V
    - G -> G
    - TXD -> D7
    - RXD -> D8
   
- FAN:
	- +VCC -> 12V
	- GND -> G
	- PWM -> D3