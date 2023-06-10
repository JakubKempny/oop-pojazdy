#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;

//class Budynek {
//	string adres;
//public:
//	Budynek(string a) :adres(a) {}
//};
//
//class StacjaPaliw: Budynek {
//	string firma;
//	map<string, double> ceny;
//	double discount=0; // - wartoœæ zni¿ki, jeœli = 0 to jej nie ma
//public:
//	StacjaPaliw(string a, string f) :Budynek(a), firma(f){} // niedokoñczony
//	//set'ery
//	void setDiscoiunt(double x) { discount = x; }
//	//get'ery
//	double getDiscount() { return discount; }
//
//};

class Budynek {
	string adres;

public:
	Budynek(string a) : adres(a) {}
};

class Ceny {
	double cenaBenzyny, cenaRopy, cenaGazu;
public:
	Ceny(double b, double r, double g) : cenaBenzyny(b), cenaRopy(r), cenaGazu(g) {};
};

class StacjaPaliw : public Budynek, public Ceny {
	string firma;
	double znizka = 0;
	vector<int> pesel;

public:
	StacjaPaliw(string f, string a, Ceny c, double z) :firma(f), Budynek(a), Ceny(c), znizka(z) {}


	void setDiscount(double x) { znizka = x; }
	double getDiscount() { return znizka; }


};