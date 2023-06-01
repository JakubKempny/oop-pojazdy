#pragma once

#include <iostream>
using namespace std;

enum class Rpaliwa {benzyna=1,lpg,ropa,prad}; // narazie jest enum class, jak czegoœ innego nie wymyœlimi to zostanie

class Silnik {
	double spalanie; // np 7,2 na 100 km
	Rpaliwa rodzajPaliwa; // benzyna,lpg,ropa,prad
	pair<double, double> paliwo;  // <akutalne,max>
public:
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
	Silnik(double s, string rpaliwa) :spalanie(s) { // konstruktor
		if (rpaliwa == "benzyna") {
			rodzajPaliwa = Rpaliwa::benzyna;
		}
		else if (rpaliwa == "gaz") {
			rodzajPaliwa = Rpaliwa::lpg;
		}
		else if (rpaliwa == "ropa") {
			rodzajPaliwa = Rpaliwa::ropa;
		}
		else if (rpaliwa == "prad") {
			rodzajPaliwa = Rpaliwa::prad;
		}
		else {
			// wywal wyj¹tek
		}
	}
	Silnik() {}; // konstruktor do testów
	
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
	Pojazd(string marka_, string model_, unsigned int rok, double maxP, double p): marka(marka_), model(model_), rocznik(rok){} 
	Pojazd() {}; // konstruktor do testu:
	// get'ery
	string getMarka() { return marka; }
	string getModel() { return model; }
	// set'ery
	
	
};

class Car: Pojazd, Silnik {
	int indeks;
public:
	Car(string marka_, string model_, unsigned int rok, double maxP, double p, double s, string rpaliwa): Pojazd(marka_,model_,rok,maxP,p),Silnik(s,rpaliwa){
	}
	Car() {}; // konstruktor do testów

};


