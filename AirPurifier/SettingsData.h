#pragma once

struct SettingsData {
	//manual
	int manualslider;
	int lastmanualslider;
	//semiauto
	int pmstart;
	int lastpmstart;
	int pmend;
	int lastpmend;
	int semiautoslider;
	int lastsemiautoslider;
	int pmtype;
	int lastpmtype;
	//auto
	int pmtokeep;
	int lastpmtokeep;
	int pmtypetokeep;
	int lastpmtypetokeep;

	SettingsData()
		: manualslider{ 0 }, lastmanualslider{ -1 }, pmstart{ 60 }, lastpmstart{ -1 }, pmend{ 80 }, lastpmend{ -1 }, semiautoslider{ 0 }, lastsemiautoslider{ -1 }, pmtype{ 0 }, lastpmtype{ -1 }, pmtokeep{ 0 }, pmtypetokeep{ 0 }, lastpmtokeep{ -1 }, lastpmtypetokeep{ -1 } {
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