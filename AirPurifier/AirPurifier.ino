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
File system:
    - SPIFFS: FS.h
WiFi:
    - ESP8266WiFi: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
    - WiFiVlient.h
Web Server:
    - ESP8266WebServer: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
------------- /LIBS ----------------
*/

//------------ INCLUDES ----------------
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SdsDustSensor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "FS.h"
#include <ESP8266WebServer.h>
//----------- /INCLUDES ----------------

// ------------ STRUCTS ----------------
typedef struct {
    float temperature;
    float humidity;
    float pressure;
    float voltage;
} node;

typedef struct {
    int nodeNum;
    int attribute;
    int sign;
    float val;
    int isActive;

} alert;
// ----------- /STRUCTS ----------------

// ------------ CONSTS ----------------
#define BME280_ADDRESS 0x76
#define SDS011_RX_PIN D7
#define SDS011_TX_PIN D8
#define SDS_WORKING_PERIOD 10000UL
// ----------- /CONSTS ----------------

// ------------ GLOBALS ----------------
const String ssid = "beginner";
const String password = "Anakonda11";
ESP8266WebServer server(80); //Server on port 80
String wholeAlertData[20];

unsigned long mainLoopTime = millis();
unsigned long deltaTime = 0;
unsigned long now = millis();
int PM_AE_UG_1_0, PM_AE_UG_2_5, PM_AE_UG_10_0 = 0;
int alertArrayIndex = 0;

node nodeArray[]{ { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0} };
alert alertArray[20];

Adafruit_BME280 bme;
SdsDustSensor sds(SDS011_RX_PIN, SDS011_TX_PIN);
// ----------- /GLOBALS ----------------

// ------------ SETUP -----------------
void setup() {
    Serial.begin(9600);
    initBme280();
    initSds011();
    initFileSystem();
    initWiFi();
    initServer();
}
// ----------- /SETUP -----------------

// ----------- LOOP -----------------
void loop() {
    server.handleClient();
    deltaTime = millis() - mainLoopTime;

    if (deltaTime < SDS_WORKING_PERIOD) {
        sdsTurnOff();
    }
    else if(deltaTime < 2 * SDS_WORKING_PERIOD) {
        sdsTurnOn();
    }
    else {
        readSds011Values();
        readBme280Values();
        Serial.println();
        mainLoopTime = millis();
    }
}

// ----------- /LOOP -----------------

// ----------- FUNCTIONS -----------------
void initBme280() {
    if (!bme.begin(BME280_ADDRESS)) {
        Serial.println("Nie wykryto czujnika BME260!");
        while (1);
    }
}

void initSds011() {
    sds.begin();
    sds.setQueryReportingMode();
}

void sdsTurnOn() {
    WorkingStateResult state = sds.wakeup();
    if (!state.isWorking()) {
        Serial.println("Problem ze wzbudzeniem czujnika SDS011.");
    }
}

void sdsTurnOff() {
    WorkingStateResult state = sds.sleep();
    if (state.isWorking())
        Serial.println("Problem z uœpieniem czujnika SDS011.");
}

void readBme280Values() {
    Serial.print("Temperatura: ");
    Serial.print(bme.readTemperature());
    Serial.println("*C");

    Serial.print("Cisnienie: ");
    Serial.print(bme.readPressure() / 100.0f);
    Serial.println("hPa");

    Serial.print("Wilgotnosc: ");
    Serial.print(bme.readHumidity());
    Serial.println("%");
}

void readSds011Values() {
    PmResult pm = sds.queryPm();
    if (pm.isOk()) {
        Serial.print("PM2.5 = ");
        Serial.println(pm.pm25);
        Serial.print("PM10 = ");
        Serial.println(pm.pm10);

        PM_AE_UG_1_0 = -1;  // not supported by SDS011
        PM_AE_UG_2_5 = pm.pm25;
        PM_AE_UG_10_0 = pm.pm10;
    }
    else {
        Serial.println("B³¹d odczytu z czujnika SDS011.");
        Serial.println(pm.statusToString());
    }
}

// WiFi stuff
void handleXML() {
    String k = "_" + String(PM_AE_UG_1_0);
    String e = "_" + String(PM_AE_UG_2_5);
    String u = "_" + String(PM_AE_UG_10_0);
    String XML = "<?xml version='1.0'?>";
    XML += "<response>";
    XML += k + e + u + "_";
    XML += "</response>";
    server.send(200, "text/xml", XML);
}

void handleAlertData() {
    String XML = "<?xml version='1.0'?>";
    XML += "<response>";
    for (int i = 0; i < 20; i++)
        XML += wholeAlertData[i];
    XML += "</response>";
    server.send(200, "text/xml", XML);
}

void handleSave() {
    if (server.arg("room") != "" && server.arg("attribute") != "" && server.arg("sign") != "" && server.arg("val") != "" && server.arg("alertNames") != "") {
        alertArray[alertArrayIndex].nodeNum = server.arg("room").toInt();
        alertArray[alertArrayIndex].attribute = server.arg("attribute").toInt();
        alertArray[alertArrayIndex].sign = server.arg("sign").toInt();
        alertArray[alertArrayIndex].val = server.arg("val").toFloat();
        alertArray[alertArrayIndex].isActive = 1;
        wholeAlertData[alertArrayIndex] = server.arg("alertNames");
        alertArrayIndex++;
        Serial.println("alert added");
        handleAlertData();
    }
}

void initFileSystem() {
    if (!SPIFFS.begin()) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
}

void initWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected to " + ssid);
    Serial.println("IP address: " + WiFi.localIP().toString() + "\n");
}

void initServer() {
    server.serveStatic("/", SPIFFS, "/index.html");
    server.serveStatic("/alerts.html", SPIFFS, "/alerts.html");
    server.on("/xml", handleXML);
    server.on("/xmla", handleAlertData);
    server.on("/save", handleSave);
    //Start server
    server.begin();
    Serial.println("HTTP server started");
}
// ----------- /FUNCTIONS -----------------
