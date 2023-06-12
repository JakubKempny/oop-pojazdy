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
		throw CustomException("Nie uda\210o si\251 otworzy\210 pliku: "+nazwaP);
	}
}

// Funkcje sprawdzajace znaki w stringu

bool is_digits(const string& str) 
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

bool containsOnlyLetters(string const& str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

bool containsDigitsANDLetters(string const& str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789., ") == std::string::npos;
}



bool is_digits2(const string& str) // Funkcja do sprawdzania czy string zawiera same cyfry
{
	return str.find_first_not_of("0123456789., ") == std::string::npos;
}

void CommaWithDot(string& str) // zamiana przecinka na kropke
{
	for (char& c : str) {
		if (c == ',') {
			c = '.';
		}
	}
	
}