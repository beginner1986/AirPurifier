#pragma once

struct SensorData {
	int pm1;
	int pm2_5;
	int pm10;
	int temperature;
	int pressure;
	int humidity;

	SensorData() 
		: pm1{ 0 }, pm2_5{ 0 }, pm10{ 0 }, temperature{ 0 }, pressure{ 0 }, humidity{ 0 } {
	}

	String getXML() {
		String XML = "";
		XML += "<response>";
		XML += "<pm1>" + (pm1 >= 0 ? String(pm1) : "-") + "</pm1>\n";
		XML += "<pm2_5>" + String(pm2_5) + "</pm2_5>\n";
		XML += "<pm10>" + String(pm10) + "</pm10>\n";
		XML += "<temperature>" + String(temperature) + "</temperature>\n";
		XML += "<pressure>" + String(pressure) + "</pressure>\n";
		XML += "<humidity>" + String(humidity) + "</humidity>\n";
		XML += "</response>";

		return XML;
	}
};
