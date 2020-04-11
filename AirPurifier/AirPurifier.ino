/*
----------- PINOUT ---------------
BME280:
    - VCC -> 3V3
    - GND -> G
    - SCL -> D1
    - SDA -> D2

SDS011:
    - 5V -> 5V
    - G -> G
    - TXD -> D7
    - RXD -> D8
----------- /PINOUT ---------------

------------- LIBS ----------------
BME280:
    - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
    - Adafruit BME280 Library: https://github.com/adafruit/Adafruit_BME280_Library
SDS011:
    - Nova Fitness SDS dust sensors Library: https://github.com/lewapek/sds-dust-sensors-arduino-library
------------- /LIBS ----------------
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SdsDustSensor.h>

#define BME280_ADDRESS 0x76
#define SDS011_RX_PIN D7
#define SDS011_TX_PIN D8

Adafruit_BME280 bme;
SdsDustSensor sds(SDS011_RX_PIN, SDS011_TX_PIN);

void setup() {
    initBme280();
    initSds011();
}

void loop() {
    printBme280Values();
    Serial.println();
    printSds011Values();
    Serial.println();
    delay(1000);
}

void initBme280()
{
    if (!bme.begin(BME280_ADDRESS))
    {
        Serial.println("Nie wykryto czujnika BME260!");
        while (1);
    }
}

void initSds011()
{
    Serial.begin(9600);
    sds.begin();

    Serial.println(sds.queryFirmwareVersion().toString());
    Serial.println(sds.setActiveReportingMode().toString());
    Serial.println(sds.setContinuousWorkingPeriod().toString());
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

void printSds011Values()
{
    PmResult pm = sds.readPm();
    if (pm.isOk()) {
        Serial.print("PM2.5 = ");
        Serial.println(pm.pm25);
        Serial.print("PM10 = ");
        Serial.println(pm.pm10);
    }
    else {
        Serial.println("B³¹d czujnika SDS011.");
        Serial.print("Could not read values from sensor, reason: ");
        Serial.println(pm.statusToString());
    }
}
