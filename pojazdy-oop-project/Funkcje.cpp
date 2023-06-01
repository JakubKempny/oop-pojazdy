#include "Header.h"

// Przyjmuje nazwe pliku. Zwraca wektor stringów, gdzie ka¿dy string to jest jeden wiersz z pliku
vector<string> wczytajPlik(const string nazwaP){ 
	fstream plik(nazwaP, ios::in);
	vector<string> wektor;
	string wiersz;
	while (getline(plik, wiersz)) {
		wektor.push_back(wiersz);
	}
	return wektor;
}

