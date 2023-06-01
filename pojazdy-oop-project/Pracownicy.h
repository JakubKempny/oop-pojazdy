#pragma once
#include <iostream>

class Pesel { // klasa która by by³a odpowiedzialna za poprawne wprowadzenie peselu
	int nr;
public:
	Pesel(int n) {
		if (n < 99999999999 && n>0) {
			nr = n;
		}
		else {
			throw "Nie poprawny pesel";
		}
	}
};

class Pracownik {
	string imie, nazwisko;
	Pesel pesel;
public:
	Pracownik(string i, string n, Pesel p) : imie(i), nazwisko(n), pesel(p) {}

};

class Kierowca: Pracownik {
	double dystans{};
public:
	Kierowca(string i, string n, int p, double d) :Pracownik(i, n, p),dystans(d){
	}
};