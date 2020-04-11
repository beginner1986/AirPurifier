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
#define SDS_SAMPLING_TIME 30000
#define MAIN_LOOP_DELAY_TIME 30000

Adafruit_BME280 bme;
SdsDustSensor sds(SDS011_RX_PIN, SDS011_TX_PIN);

void setup() {
    initBme280();
    initSds011();
}

void loop() {
    readBme280Values();
    readSds011Values();
    delay(MAIN_LOOP_DELAY_TIME);

    Serial.println();
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
    sds.setQueryReportingMode();
}

void readBme280Values()
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

void readSds011Values()
{
    WorkingStateResult state = sds.wakeup();
    if (!state.isWorking())
        Serial.println("Problem ze wzbudzeniem czujnika SDS011.");
    delay(SDS_SAMPLING_TIME);

    PmResult pm = sds.queryPm();
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

    state = sds.sleep();
    if (state.isWorking())
        Serial.println("Problem z uœpieniem czujnika SDS011.");
}
