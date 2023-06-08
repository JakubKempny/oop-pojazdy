#pragma once
#include <iostream>

class Pesel { // klasa sprawdzajaca poprawne wprowadzenie peselu
	string nr;
public:
	Pesel(string n);
};

class Pracownik {
	string imie, nazwisko, vinPojazdu;
	Pesel pesel;
	double dystans{}; // jeszcze niemodyfikowalne
public:
	Pracownik(string i, string n, Pesel p, string poj) : imie(i), nazwisko(n), pesel(p), vinPojazdu(poj) {}
	string formatDataToString();
};

class Stanowisko
{
	string nazwa;
	double znizka; // chyba w procentach? w sensie 0.15 to bedzie 15%
	int iloscPracownikow;
};