#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Budynek {
	string adres;

public:
	Budynek(string a) : adres(a) {}
	string getName() { return adres; }
};

class Ceny {
	double cenaBenzyny, cenaRopy, cenaGazu;
public:
	Ceny() = default;  // Konstruktor domyœlny
	Ceny(double b, double r, double g) : cenaBenzyny(b), cenaRopy(r), cenaGazu(g) {};
	string formatDataToString();
	double getBenz() { return cenaBenzyny; }
	double getRopa() { return cenaRopy; }
	double getGaz() { return cenaGazu; }
};

class StacjaPaliw : public Budynek, public Ceny {
	string firma, id;
	double znizka = 0;
public:
	StacjaPaliw(string i,string f, string a, double benzyna, double ropa, double gaz, double z) :id(i),  Budynek(a), firma(f), Ceny(benzyna, ropa, gaz), znizka(z) {}

	void setDiscount(double x) { znizka = x; }
	double getDiscount() { return znizka; }
	double getFuelCost(string fuelType);
	string formatDataToString();
	string getFirma() { return firma; };
};