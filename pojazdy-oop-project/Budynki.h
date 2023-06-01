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
	double discount=0; // - wartoœæ zni¿ki, jeœli = 0 to jej nie ma
public:
	StacjaPaliw(string a, string f) :Budynek(a), firma(f){} // niedokoñczony
	//set'ery
	void setDiscoiunt(double x) { discount = x; }
	//get'ery
	double getDiscount() { return discount; }

};