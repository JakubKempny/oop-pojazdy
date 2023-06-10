#pragma once

#include <iostream>
using namespace std;

class Silnik {
	double spalanie; // np 7,2 na 100 km
	string rodzajPaliwa; // benzyna,lpg,ropa,prad
public:
	Silnik(double s, string rpaliwa) :spalanie(s) { // konstruktor
		if (rpaliwa == "benzyna") {
			rodzajPaliwa = rpaliwa;
		}
		else if (rpaliwa == "lpg") {
			rodzajPaliwa = rpaliwa;
		}
		else if (rpaliwa == "ropa") {
			rodzajPaliwa = rpaliwa;
		}
		else if (rpaliwa == "prad") {
			rodzajPaliwa = rpaliwa;
		}
		else {
			rodzajPaliwa = "#####";  // Jak siê poda z³¹ nazwe paliwa trzeba podaæ kolejny raz
		}
	}
	Silnik() {}; // konstruktor do testów

	string formatDataToString();

	double oblZurzycie(double odl) {
		return (spalanie * odl) / 100;
	}
};

class Pojazd{
	string marka, model;
	unsigned int rocznik{};
	
public:
	Pojazd(string marka_, string model_, unsigned int rok): marka(marka_), model(model_), rocznik(rok){} 
	Pojazd() {}; // konstruktor do testu:
	//virtual ~Pojazd();
	// get'ery
	string formatDataToString();
	string getMarka() { return marka; }
	string getModel() { return model; }
	// set'ery
	
};

class Car: Pojazd, Silnik {
	int nrVin;
public:
	Car(string marka_, string model_, unsigned int rok_, double s, string rpaliwa): Pojazd(marka_,model_,rok_),Silnik(s,rpaliwa){
	}
	Car() {}; // konstruktor do testów
	string formatDataToString();

};


