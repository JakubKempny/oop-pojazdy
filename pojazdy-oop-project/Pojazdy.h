#pragma once

#include <iostream>
using namespace std;

class Silnik {
	double spalanie; // np 7,2 na 100 km
	string rodzajPaliwa; // benzyna,lpg,ropa,prad
	pair<double, double> paliwo;  // <akutalne,max>
public:
	Silnik(double s, string rpaliwa, double maxP) :spalanie(s) { // konstruktor
		paliwo.first = maxP;
		paliwo.second = maxP;
		if (rpaliwa == "benzyna") {
			rodzajPaliwa = rpaliwa;
		}
		else if (rpaliwa == "gaz") {
			rodzajPaliwa = rpaliwa;
		}
		else if (rpaliwa == "ropa") {
			rodzajPaliwa = rpaliwa;
		}
		else if (rpaliwa == "prad") {
			rodzajPaliwa = rpaliwa;
		}
		else {
			// wywal wyj¹tek
		}
	}
	Silnik() {}; // konstruktor do testów

	string formatDataToString();

	double oblZurzycie(double odl) {
		return (spalanie * odl) / 100;
	}
	void spalPaliwo(double odl) {
		double tmp = oblZurzycie(odl);
		if (paliwo.first - tmp >= 0) {
			paliwo.first -= tmp;
		}
		else {
			// wywal wyj¹tek !!! 
			// tutaj mo¿na zainicjowaæ tankowanie pojazdu
		}
	}
	
	
	void tankowanie(double p) {
		if (paliwo.first + p <= paliwo.second) {
			paliwo.first += p;
		}
		else {
			// wywal wyj¹tek !!!!! 
		}
	}
};

class Pojazd{
	string marka, model;
	unsigned int rocznik{};
	
public:
	Pojazd(string marka_, string model_, unsigned int rok): marka(marka_), model(model_), rocznik(rok){} 
	Pojazd() {}; // konstruktor do testu:
	// get'ery
	string formatDataToString();
	string getMarka() { return marka; }
	string getModel() { return model; }
	// set'ery
	
	
};

class Car: Pojazd, Silnik {
	int nrVin;
public:
	Car(string marka_, string model_, unsigned int rok_, double s, string rpaliwa, double maxP): Pojazd(marka_,model_,rok_),Silnik(s,rpaliwa,maxP){
	}
	Car() {}; // konstruktor do testów
	string formatDataToString();

};


