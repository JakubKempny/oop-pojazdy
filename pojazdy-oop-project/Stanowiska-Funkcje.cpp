#include "Header.h"

Stanowisko::Stanowisko(string nazwaStanowiska) {
	this->nazwaStanowiska = nazwaStanowiska;
}

Stanowisko::Stanowisko(string nazwaStanowiska, double proc_pokrycia) {
	this->nazwaStanowiska = nazwaStanowiska;
	this->proc_pokrycia = proc_pokrycia;
}

string Stanowisko::getName() {
	return this->nazwaStanowiska;
}

string Stanowisko::formatDataToString() {
	string proc;
	stringstream ss;
	ss << fixed << setprecision(2);
	ss << proc_pokrycia;
	ss >> proc;
	return  proc + ";";
}