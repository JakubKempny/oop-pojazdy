#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Budynek {
	string adres;
public:
	Budynek(string a) :adres(a) {}
};

class StacjaPaliw: Budynek {
	string firma;
	map<Rpaliwa, double> ceny;
	double discount=0; // - warto�� zni�ki, je�li = 0 to jej nie ma
public:
	StacjaPaliw(string a, string f) :Budynek(a), firma(f){} // niedoko�czony
	//set'ery
	void setDiscoiunt(double x) { discount = x; }
	//get'ery
	double getDiscount() { return discount; }

};