#include "Header.h"

// Przyjmuje nazwe pliku. Zwraca wektor stringów, gdzie kazdy string to jest jeden wiersz z pliku
vector<string> wczytajPlik(const string nazwaP) { 
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
	} else {
		throw CustomException("Nie udalo sie otworzyc pliku: "+nazwaP);
	}
}

// Funkcje sprawdzajace znaki w stringu
bool is_digits(const string& str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

bool containsOnlyLetters(string const& str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

bool containsDigitsANDLetters(string const& str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ") == std::string::npos;
}

bool is_digits2(const string& str) {

	char firstChar = str[0];
	if (firstChar == '.' || firstChar == ',' || firstChar == ' ')
		return false;

	return str.find_first_not_of("0123456789,.") == std::string::npos;
}

void CommaWithDot(string& str) { // zamiana przecinka na kropke
	for (char& c : str) {
		if (c == ',') {
			c = '.';
		}
	}
}

void getlineM(string& str) {
	do {
		std::getline(std::cin, str);
	} while (str.empty());
}

bool checkMultipleDotsCommas(string& str) {
	int Count = 0;
	for (char c : str) {
		if (c == '.' || c == ',')
			Count++;
	}
	if (Count > 1) {
		return false;
	} else return true;
}

string ignoreAfterSpace(const string& input) {
	std::stringstream ss(input);
	std::string result;
	ss >> result;
	return result;
}

string nameToLower(string name) {
	string newName;
	for (int i = 0; i < name.length(); i++) {
		newName += tolower(name[i]);
	}
	return newName;
}
