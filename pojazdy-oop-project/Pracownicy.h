#pragma once
#include <iostream>

class Pesel { // klasa sprawdzajaca poprawne wprowadzenie peselu
	string nr;
public:
	Pesel() {};
	Pesel(string n);
};

class Stanowisko
{
	string nazwaStanowiska;
	double proc_pokrycia{}; //czyli 0.40 to 40% tyle pokrywa firma pieniedzy pracownikowi
	//int iloscPracownikow;
public:
	Stanowisko() {}
	Stanowisko(string nazwaStanowiska);
	Stanowisko(string nazwaStanowiska, double proc_pokrycia);
	string formatDataToString();
};

class Pracownik: Stanowisko,Pesel {
	string imie, nazwisko, vinPojazdu;
	Pesel pesel;
	double dystans{};
public:
	Pracownik(string i, string n, Pesel p, string poj, double dys) : imie(i), nazwisko(n), Pesel(p), vinPojazdu(poj), dystans(dys) {}
	//Pracownik(string i, string n, Pesel p, string poj, double dys, string stan) : imie(i), nazwisko(n), Pesel(p), vinPojazdu(poj), dystans(dys), Stanowisko(stan) {}
	string formatDataToString();
};

