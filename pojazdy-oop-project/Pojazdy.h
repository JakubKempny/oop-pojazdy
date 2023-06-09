#pragma once
#include"Header.h"
#include <iostream>
using namespace std;

class Silnik {
	double spalanie; // np 7,2 na 100 km
	string rodzajPaliwa; // benzyna,lpg,ropa
public:
	Silnik(double s, string rpaliwa);
	string formatDataToString();
	double oblZurzycie(double odl) { return (spalanie * odl) / 100; }
	double getSpalanie() { return spalanie; }
	string getRodzPaliwa() { return rodzajPaliwa; }
};

class Pojazd {
	string marka, model;
	unsigned int rocznik{};
public:
	Pojazd(string marka_, string model_, unsigned int rok): marka(marka_), model(model_), rocznik(rok){} 
	// get'ery
	string formatDataToString();
	string getMarka() { return marka; }
	string getModel() { return model; }
	// set'ery
};

class Car: public Pojazd, public Silnik {
	int nrVin;
public:
	Car(string marka_, string model_, unsigned int rok_, double s, string rpaliwa): Pojazd(marka_,model_,rok_),Silnik(s,rpaliwa) {}
	string formatDataToString();
};


