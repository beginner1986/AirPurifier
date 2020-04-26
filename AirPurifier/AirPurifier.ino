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

#include "SensorsData.h"
#include "SettingsData.h"

//----------- /INCLUDES ----------------

// ------------ CONSTS ----------------
#define SDS011_RX_PIN D7
#define SDS011_TX_PIN D8

const String SSID = "beginner";
const String WIFI_PASSWORD = "Anakonda11";
const unsigned long SDS_WORKING_PERIOD = 10000UL;   // short time for debugging
// ----------- /CONSTS ----------------

// ------------ GLOBALS ----------------
unsigned long mainLoopTime = millis();
unsigned long now = millis();
unsigned long deltaTime = 0;

int alertArrayIndex = 0;
String wholeAlertData[20];

Adafruit_BME280 bme;
SdsDustSensor sds(SDS011_RX_PIN, SDS011_TX_PIN);
ESP8266WebServer server(80);

SensorData sensorData;
SettingsData settingsData;
// ----------- /GLOBALS ----------------

// ------------ SETUP -----------------
void setup() {
    Serial.begin(9600);
	pinMode(0, OUTPUT);
    //initBme280();
    //initSds011();
    initFileSystem();
    initWiFi();
    initServer();
	sensorData.mode = 1;
}
// ----------- /SETUP -----------------

// ----------- LOOP -----------------
void loop() {
    server.handleClient();
	//measureData();
	switch (sensorData.mode)
	{
	case 1:
	{
		manualMode();
		break;
	}
	case 2:
	{
		semiAutoMode();
		break;
	}
	case 3:
	{
		autoMode();
		break;
	}
	case 4:
	{
		off();
		break;
	}
	}
}
// ----------- /LOOP -----------------

// ----------- FUNCTIONS -----------------
void manualMode() {
	if (settingsData.manualslider != settingsData.lastmanualslider) {
		analogWrite(0, map(settingsData.manualslider, 0, 100, 0, 1023));
		
	}
	settingsData.lastmanualslider = settingsData.manualslider;
	
}

void semiAutoMode() {

}

void autoMode() {

}

void off() {

}
void initBme280() {
    if (!bme.begin(BME280_ADDRESS_ALTERNATE)) {
        Serial.println("BME260 sensor not detected!");
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
        Serial.println("SDS011 wake up failed!");
    }
}

void sdsTurnOff() {
    WorkingStateResult state = sds.sleep();
    if (state.isWorking())
        Serial.println("SDS011 sllep failed!");
}

void readBme280Values() {
    sensorData.temperature = bme.readTemperature();
    sensorData.pressure = bme.readPressure() / 100.0f;
    sensorData.humidity = bme.readHumidity();

    Serial.println("Temperature: " + String(sensorData.temperature) + "*C");
    Serial.println("Pressure: " + String(sensorData.pressure) + "hPa");
    Serial.print("Humidity: " + String(sensorData.humidity) + "%");
}

void readSds011Values() {
    PmResult pm = sds.queryPm();
    if (pm.isOk()) {
        Serial.print("PM2.5 = ");
        Serial.println(pm.pm25);
        Serial.print("PM10 = ");
        Serial.println(pm.pm10);

        sensorData.pm1 = -1;  // not supported by SDS011
        sensorData.pm2_5 = pm.pm25;
        sensorData.pm10 = pm.pm10;
    }
    else {
        Serial.println("SDS011 sensor data read error: " + pm.statusToString());
    }
}
void measureData() {
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
		Serial.println("\n");
		mainLoopTime = millis();
	}
}
void handleXML() {
    String XML = sensorData.getXML();
    server.send(200, "text/xml", XML);
}
void handleSettingsXML() {
	String XML = settingsData.getSettingsXML();
	XML += "<mode>" + String(sensorData.mode) + "</mode>\n";
	XML += "</response>";
	server.send(200, "text/xml", XML);
}

void handleSave() {
	Serial.println("received something");

    if (server.arg("manualslider") != "") {
		settingsData.manualslider = server.arg("manualslider").toInt();
		server.send(200, "text/plain", "");
		Serial.println(settingsData.manualslider);
    }

	if (server.arg("pmstart") != "" && server.arg("pmend") != "" && server.arg("semiautoslider") != "" && server.arg("pmtype") != "") {
		settingsData.pmstart = server.arg("pmstart").toInt();
		settingsData.pmend = server.arg("pmend").toInt();
		settingsData.semiautoslider = server.arg("semiautoslider").toInt();
		settingsData.pmtype = server.arg("pmtype").toInt();
		server.send(200, "text/plain", "");
		Serial.println(settingsData.pmstart);
		Serial.println(settingsData.pmend);
		Serial.println(settingsData.semiautoslider);
		Serial.println(settingsData.pmtype);
	}

	if (server.arg("pmtokeep") != "" && server.arg("pmtypetokeep") != "") {
		settingsData.pmtokeep = server.arg("pmtokeep").toInt();
		settingsData.pmtypetokeep = server.arg("pmtypetokeep").toInt();
		server.send(200, "text/plain", "");
		Serial.println(settingsData.pmtokeep);
		Serial.println(settingsData.pmtypetokeep);
	}

	if (server.arg("mode") != "") {
		sensorData.mode = server.arg("mode").toInt();
		server.send(200, "text/plain", "");
		Serial.println(sensorData.mode);
	}
}


void initFileSystem() {
    if (!SPIFFS.begin()) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
}

void initWiFi() {
    WiFi.begin(SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected to " + SSID);
    Serial.println("IP address: " + WiFi.localIP().toString());
}

void initServer() {
    server.serveStatic("/", SPIFFS, "/index.html");
    server.serveStatic("/index.html", SPIFFS, "/index.html");

    server.serveStatic("/css/styles.css", SPIFFS, "/css/styles.css");
    server.serveStatic("/css/tile.css", SPIFFS, "/css/tile.css");
    server.serveStatic("/css/pace.css", SPIFFS, "/css/pace.css");
    server.serveStatic("/css/fonts.css", SPIFFS, "/css/fonts.css");
    server.serveStatic("/css/fonts-italic.css", SPIFFS, "/css/fonts-italic.css");

    server.serveStatic("/js/data.js", SPIFFS, "/js/data.js");
    server.serveStatic("/js/pace.min.js", SPIFFS, "/js/pace.min.js");
    server.serveStatic("/js/ui.js", SPIFFS, "/js/ui.js");
	server.serveStatic("/js/settings.js", SPIFFS, "/js/settings.js");
    server.serveStatic("/js/jquery.min.js", SPIFFS, "/js/jquery.min.js");
    server.serveStatic("/js/bootstrap.bundle.min.js", SPIFFS, "/js/bootstrap.bundle.min.js");
    server.serveStatic("/js/jquery.easing.min.js", SPIFFS, "/js/jquery.easing.min.js");

    server.serveStatic("/img/background.jpg", SPIFFS, "/img/background.jpg");
    server.serveStatic("/img/cloud.png", SPIFFS, "/img/cloud.png");
    server.serveStatic("/img/arrow.png", SPIFFS, "/img/arrow.png");
    server.serveStatic("/img/star.png", SPIFFS, "/img/star.png");
    server.serveStatic("/img/bars.svg", SPIFFS, "/img/bars.svg");

    server.on("/xml", handleXML);
	server.on("/settings", handleSettingsXML);
    server.on("/save", handleSave);

    server.begin();
    Serial.println("HTTP server started.\n");
}
// ----------- /FUNCTIONS -----------------
