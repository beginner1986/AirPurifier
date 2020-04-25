#pragma once

struct SettingsData {
	//manual
	int manualslider;
	//semiauto
	int pmstart;
	int pmend;
	int semiautoslider;
	int pmtype;
	//auto
	int pmtokeep;
	int pmtypetokeep;

	SettingsData()
		: manualslider{ 0 }, pmstart{ 0 }, pmend{ 0 }, semiautoslider{ 0 }, pmtype{ 0 }, pmtokeep{ 0 }, pmtypetokeep{ 0 } {
	}
};