#include "Header.h"

void KontenerStanow::createMapFromFile(vector<string> wiersze) {
	string nazwa;
	double proc_pokrycia{};
	mapStan.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, nazwa, ';');
		ss >> proc_pokrycia;
		ss.ignore();
		Stanowisko* wskStan = new Stanowisko(nazwa, proc_pokrycia);
		mapStan.insert(make_pair(nazwa, wskStan));
	}
}

void KontenerStanow::addRecord() {
	string nazwa, proc;
	double proc_pokrycia;
	cout << endl << "Dodawanie nowego stanowiska." << endl;
	cout << "Podaj nazwe stanowiska (2-20 znakow): ";
	try {
		getlineM(nazwa);
		nazwa = nameToLower(nazwa);
		if (containsDigitsANDLetters(nazwa) == false || nazwa.length() > 20 || nazwa.length() < 2) throw CustomException("Nazwa zostala wpisana niepoprawnie!");
		for (auto i = mapStan.begin(); i != mapStan.end(); ++i) {
			if (nazwa == i->first) throw CustomException("W bazie znajduje sie juz stanowisko o podanej nazwie! ");
		}
		cout << "Podaj procent pokrycia kosztow paliwa(np. 0.40 to 40% kosztow ktore pokrywa firma):";
		getlineM(proc);
		CommaWithDot(proc);
		if (is_digits2(proc) == false || stod(proc) < 0 || stod(proc) > 1 || checkMultipleDotsCommas(proc) == false) throw CustomException("Wartosc wpisana niepoprawnie!");
		proc_pokrycia = stod(proc);
		Stanowisko* wskNewStan = new Stanowisko(nazwa, proc_pokrycia);
		cout << "Czy chcesz zapisac zmiany? y/n: ";
		cin >> input;
		if (input == 'y') {
			cout << "Pomyslnie utworzono nowe stanowisko. Nacisnij dowolny klawisz, aby kontynuowac...";
			mapStan.insert(make_pair(nazwa, wskNewStan));
			saveChanges();
		}
		else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

bool KontenerStanow::czyPrzypStan(string nazwaStanow, string plikKierowcy) {
	string linia;
	string nazwa = plikKierowcy;
	ifstream plik(nazwa);
	if (!plik) {
		cout << "Nie mozna otworzyc pliku." << endl;
		return false;
	}
	while (getline(plik, linia)) {
		istringstream iss(linia);
		string kolumny[6];
		string separator = ";";
		for (int i = 0; i < 6; ++i) {
			if (!getline(iss, kolumny[i], separator[0])) {
				plik.close();
				return false;
			}
		}
		if (kolumny[5] == nazwaStanow && kolumny[5].size() == nazwaStanow.size()) {
			plik.close();
			return true;
		}
	}
	plik.close();
	return false;
}

void KontenerStanow::delRecord(string plikKierowcy) {
	string nazwa{};
	string plik{};
	cout << endl << "Usuwanie stanowiska, podaj jego nazwe: ";
	cin >> nazwa;
	bool exist = false;
	for (auto i : mapStan) {
		if (i.first == nazwa) exist = true;
	}
	try {
		if (!exist) throw CustomException("Stanowisko o takiej nazwie nie istnieje w bazie.");
		if (czyPrzypStan(nazwa, plikKierowcy)) throw CustomException("Stanowisko o takiej nazwie jest juz przypisane do pracownika. Nie mozna usunac stanowiska! "); // sprawdzi czy stanowisko przypadkiem nie jest juz przypisane do jakiegos pracownika
		cout << "Czy napewno chcesz usunac stanowisko o nazwie: " << nazwa << "? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapStan.erase(nazwa);
			saveChanges();
			cout << "Stanowisko:" << nazwa << " zostalo usuniete. " << "Nacisnij dowolny klawisz, aby kontynuowac...";
		}
		else cout << "Nie zapisano zmian w bazie";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerStanow::saveChanges() {
	ifstream f(this->getPathToFile());
	if (f.good()) {
		fstream plik(this->getPathToFile(), ios::out | ios::trunc);
		stringstream ss;
		for (auto i = mapStan.begin(); i != mapStan.end(); ++i) {
			ss << i->first << ";" << i->second->formatDataToString() << "\n";
		}
		plik << ss.str();
		plik.close();
	}
}

void KontenerStanow::info() {
	char z = '_';
	int spaceValue = 25;
	cout << "Dane z pliku: " << getPathToFile() << " : \n\n";
	cout << setfill(z) << setw(2 * spaceValue + 2 * 2 + 1) << z << endl;
	cout.fill(' ');
	// wstawianie nazw kategorii
	cout << "\174" << setw(spaceValue) << "Stanowisko" << setw(2) << "|" << setw(spaceValue) << "Wysokosc znizki [*100%]" << setw(2) << "|" << endl;
	cout << setfill(z) << setw(2 * spaceValue + 2 * 2 + 1) << z << endl;
	cout.fill(' ');
	for (auto i : mapStan) {
		stringstream ss;
		ss << (i.second->formatDataToString());
		string tmp;
		cout << "|" << setw(spaceValue) << i.first << setw(2);
		;
		while ((getline(ss, tmp, ';'))) {
			cout << "|" << setw(spaceValue) << tmp << setw(2);
			;
		}
		cout << "|" << endl;
		cout << setfill(z) << setw(2 * spaceValue + 2 * 2 + 1) << z << endl;
		cout.fill(' ');
	}
}

bool KontenerStanow::stanowIstnieje(string nazwa) {
	for (auto i = mapStan.begin(); i != mapStan.end(); ++i) {
		if (nazwa == i->first)
		{
			return true;
		}
	}
	return false;
}
