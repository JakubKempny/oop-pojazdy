#include "Header.h"

string Car::formatDataToString() {
	string	pojazd = Pojazd::formatDataToString(),
	silnik = Silnik::formatDataToString();
	return	pojazd + ";" + silnik;
}
string Pojazd::formatDataToString() {
	return marka + ";" + model + ";" + to_string(rocznik);
}

string Silnik::formatDataToString() { // gites
	string sTmp;
	stringstream ss;
	ss << fixed << setprecision(1);
	ss << spalanie;
	ss >> sTmp;
	return sTmp + ";" + rodzajPaliwa;
}

Silnik::Silnik(double s, string rpaliwa) :spalanie(s) { // konstruktor
	if (rpaliwa == "benzyna" || rpaliwa == "gaz" || rpaliwa == "ropa") {
		rodzajPaliwa = rpaliwa;
	}
	else {
		throw CustomException("Niepoprawny rodzaj paliwa.");
	}
}
