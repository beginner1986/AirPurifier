#pragma once

struct SettingsData {
	//manual
	int manualslider;
	int lastmanualslider;
	//semiauto
	int pmstart;
	int pmend;
	int semiautoslider;
	int pmtype;
	//auto
	int pmtokeep;
	int pmtypetokeep;

	SettingsData()
		: manualslider{ 0 }, lastmanualslider{ -1 }, pmstart{ 60 }, pmend{ 80 }, semiautoslider{ 0 }, pmtype{ 0 }, pmtokeep{ 0 }, pmtypetokeep{ 0 } {
	}

	String getSettingsXML() {
		String XML = "";
		XML += "<response>";
		XML += "<manualslider>" + String(manualslider) + "</manualslider>\n";
		XML += "<pmstart>" + String(pmstart) + "</pmstart>\n";
		XML += "<pmend>" + String(pmend) + "</pmend>\n";
		XML += "<semiautoslider>" + String(semiautoslider) + "</semiautoslider>\n";
		XML += "<pmtype>" + String(pmtype) + "</pmtype>\n";
		XML += "<pmtokeep>" + String(pmtokeep) + "</pmtokeep>\n";
		XML += "<pmtypetokeep>" + String(pmtypetokeep) + "</pmtypetokeep>\n";


		return XML;
	}
};