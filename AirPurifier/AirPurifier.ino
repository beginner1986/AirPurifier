/*
----------- PINOUT ---------------
BME280:
    - VCC -> 3V3
    - GND -> G
    - SCL -> D1
    - SDA -> D2
----------- /PINOUT ---------------

------------- LIBS ----------------
BME280:
    - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
    - Adafruit BME280 Library: https://github.com/adafruit/Adafruit_BME280_Library
------------- /LIBS ----------------
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
    initBme280();
}

void loop() {
    printBme280Values();
    Serial.println();
}

void initBme280()
{
    if (!bme.begin(0x76))
    {
        Serial.println("Nie wykryto czujnika BME260!");
        while (1);
    }
}

void printBme280Values()
{
    Serial.print("Temperatura: ");
    Serial.print(bme.readTemperature());
    Serial.println("*C)");

    Serial.print("Cisnienie: ");
    Serial.print(bme.readPressure() / 100.0f);
    Serial.println("hPa)");

    Serial.print("Wilgotnosc: ");
    Serial.print(bme.readHumidity());
    Serial.println("%)");
}