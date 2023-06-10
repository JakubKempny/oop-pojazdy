#include "Header.h"

// Przyjmuje nazwe pliku. Zwraca wektor stringów, gdzie ka¿dy string to jest jeden wiersz z pliku
vector<string> wczytajPlik(const string nazwaP){ 
	fstream plik(nazwaP, ios::in);
	if (plik.is_open()) {
		vector<string> wektor;
		string wiersz;
		while (getline(plik, wiersz)) {
			//cout << wiersz << endl;
			wektor.push_back(wiersz);
		}
		plik.close();
		return wektor;
	}
	else {
		throw CustomException("Nie udalo sie otworzyc pliku: "+nazwaP);
	}
}

//Imo chyba lepiej bedzie to rozdzielic na osobne pliki typu: funkcje_glowne, funkcje_pracownik, funkcje_pojazdy, funkcje_budynki
//ale na razie wrzuce wszystko dla pracownika tutaj ponizej

bool is_digits(const string& str) // Funkcja do sprawdzania czy string zawiera same cyfry
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

bool containsOnlyLetters(string const& str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

bool containsDigitsANDLetters(string const& str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") == std::string::npos;
}
bool check(int zmienna)
{
	if (zmienna < 0)
		return false;
	else
		return true;
}

bool check(double zmienna)
{
	if (zmienna < 0)
		return false;
	else
		return true;
}


