#include "Header.h"

string Ceny::formatDataToString() {
	string benz;
	string ropa;
	string gaz;
	stringstream ss;
	ss << fixed << setprecision(2);
	ss << cenaBenzyny << ";" << cenaRopy << ";" << cenaGazu;
	ss >> benz;
	return benz;
}

string StacjaPaliw::formatDataToString() {
	string ceny = Ceny::formatDataToString();
	string rabat{};
	stringstream ss;
	ss << znizka;
	ss >> rabat;
	string adres = Budynek::getName();
	return adres + ";" + firma + ";" + ceny + ";" + rabat + ";";  
}

double StacjaPaliw::getFuelCost(string fuelType) {
	if (fuelType == "benzyna") {
		return getBenz();
	} else if (fuelType == "ropa") {
		return getRopa();
	} else if (fuelType == "gaz") {
		return getGaz();
	}
}