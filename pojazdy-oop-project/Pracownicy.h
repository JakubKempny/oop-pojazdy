#pragma once
#include <iostream>

class Pesel { // klasa sprawdzajaca poprawne wprowadzenie peselu
	string nr;
public:
	Pesel(string n);
};

class Stanowisko
{
	string nazwaStanowiska;
	double znizka{};
	//int iloscPracownikow;
public:
	Stanowisko() {}
	Stanowisko(string nazwaStanowiska);
};

class Pracownik: Stanowisko {
	string imie, nazwisko, vinPojazdu;
	Pesel pesel;
	double dystans{}; // jeszcze niemodyfikowalne
public:
	Pracownik(string i, string n, Pesel p, string poj, double dys) : imie(i), nazwisko(n), pesel(p), vinPojazdu(poj), dystans(dys) {}
	string formatDataToString();
};

