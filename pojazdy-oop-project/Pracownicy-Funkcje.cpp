#include "Header.h"

Pesel::Pesel(string n) {//Funkcja sprawdzajaca czy PESEL jest poprawny

	if ((is_digits(n)) && (n.length() == 11)) {
		nr = n;
	}
	else throw CustomException("PESEL jest niepoprawny! ");
}

string Pracownik::formatDataToString() {
	string dyst;
	stringstream ss;
	ss << fixed << setprecision(1);
	ss << dystans;
	ss >> dyst;
	string stan = Stanowisko::getName();
	return  imie + ";" + nazwisko + ";" + vinPojazdu + ";" + dyst + ";" + stan + ";";
}
