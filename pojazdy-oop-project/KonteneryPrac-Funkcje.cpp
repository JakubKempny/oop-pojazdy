#include "Header.h"

bool KontenerKierow::vinWolny(string vin) { //Sprawdza czy numer VIN nie jest juz przypadkie zajety przez innego kierowce
	string linia;
	string nazwa = this->getPathToFile();
	ifstream plik(nazwa);
	if (!plik) {
		cout << "Nie mozna otworzyc pliku." << endl;
		return false;
	}
	while (getline(plik, linia)) {
		istringstream iss(linia);
		string kolumny[4];
		string separator = ";";
		for (int i = 0; i < 4; ++i) {
			if (!getline(iss, kolumny[i], separator[0])) {
				plik.close();
				return false;
			}
		}
		if (kolumny[3] == vin && kolumny[3].size() == vin.size()) {
			plik.close();
			return true;
		}
	}
	plik.close();
	return false;
}

void KontenerKierow::createMapFromFile(vector<string> wiersze) {
	string imie, nazwisko, pesel, vin, stanowisko;
	double dystans;
	mapPrac.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, pesel, ';');
		getline(ss, imie, ';');
		getline(ss, nazwisko, ';');
		getline(ss, vin, ';');
		ss >> dystans;
		ss.ignore();
		getline(ss, stanowisko, ';');
		Pracownik* wskPrac = new Pracownik(imie, nazwisko, pesel, vin, dystans, stanowisko);
		mapPrac.insert(make_pair(pesel, wskPrac));
	}
}

void KontenerKierow::addRecord(KontenerCar& k, KontenerStanow& s) {
	string imie, nazwisko, pesel, vin, stanowisko, dystansStr;
	string komunikat = "Przerwano proces dodawania pracownika. ";
	double dystans;
	cout << endl << "Dodawanie nowego pracownika." << endl;
	cout << "Podaj Pesel pracownika: ";
	try {
		getlineM(pesel);
		if (is_digits(pesel) == false || pesel.length() != 11 || stod(pesel) <= 0) throw CustomException("Numer PESEL zostal niepoprawnie wpisany! ");
		for (auto i = mapPrac.begin(); i != mapPrac.end(); ++i) {
			if (pesel == i->first) throw CustomException(komunikat + "W bazie znajduje sie juz uzytkownik o podanym numerze Pesel! ");
		}
		cout << "Podaj imie pracownika (2-20 znakow): ";
		getlineM(imie);
		if (containsOnlyLetters(imie) == false || imie.length() > 20 || imie.length() < 2) throw CustomException(komunikat + "Imie zawiera niedozwolone znaki! ");
		cout << "Podaj nazwisko pracownika: (2-20 znakow): ";
		getlineM(nazwisko);
		if (containsOnlyLetters(nazwisko) == false || nazwisko.length() > 20 || nazwisko.length() < 2) throw CustomException(komunikat + "Nazwisko zawiera niedozwolone znaki! ");
		cout << "Podaj vin pojazdu pracownika: ";
		cin >> vin;
		if (!k.vinIstnieje(vin)) throw CustomException(komunikat + "Podany samochod nie istnieje! ");
		if (vinWolny(vin)) throw CustomException(komunikat + "Podany samochod jest juz przypisany do innego kierowcy! ");
		cout << "Podaj sredni dystans jaki pokonuje pracownik km/dzien: ";
		getlineM(dystansStr);
		CommaWithDot(dystansStr);
		if (is_digits2(dystansStr) == false || stod(dystansStr) < 0 || dystansStr.length() > 10 || checkMultipleDotsCommas(dystansStr) == false) throw CustomException(komunikat + "Dystans zostal niepoprawnie wpisany!");
		dystans = stod(dystansStr);
		cout << "Podaj stanowisko pracownika: ";
		getlineM(stanowisko);
		if (!s.stanowIstnieje(stanowisko)) throw CustomException(komunikat + "Podane stanowisko nie istnieje! ");
		Pracownik* wskNewPrac = new Pracownik(imie, nazwisko, pesel, vin, dystans, stanowisko);
		cout << "Czy chcesz zapisac zmiany? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapPrac.insert(make_pair(pesel, wskNewPrac));
			saveChanges();
			cout << "Dodano nowego pracownika. Nacisnij dowolny klawisz, aby kontynuowac...";
		}
		else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerKierow::delRecord() {

	string pesel{};
	bool exist = false;
	cout << endl << "Usuwanie pracownika, podaj jego pesel: " << endl;
	cin >> pesel;
	for (auto i : mapPrac) {
		if (i.first == pesel) exist = true;
	}
	try {
		if (!exist) throw CustomException("Pracownik o takim numerze PESEL nie istnieje w bazie.");

		cout << "Czy napewno chcesz usunac pracownika o numerze PESEL: " << pesel << "? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapPrac.erase(pesel);
			saveChanges();
			cout << "Pracownik o peselu:" << pesel << " zostal usuniety." << "Nacisnij dowolny klawisz, aby kontynuowac...";
		}
		else cout << "Pracownik nie zostal usuniety";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerKierow::saveChanges() {
	ifstream f(this->getPathToFile());
	if (f.good()) {
		fstream plik(this->getPathToFile(), ios::out | ios::trunc);
		stringstream ss;
		for (auto i = mapPrac.begin(); i != mapPrac.end(); ++i) {
			ss << i->first << ";" << i->second->formatDataToString() << "\n";
		}
		plik << ss.str();
		plik.close();
	}
}

void KontenerKierow::info() {
	char z = '_';
	int spaceValue = 25;
	cout << "Dane z pliku: " << getPathToFile() << " : \n\n";
	cout << setfill(z) << setw(6 * spaceValue + 6 * 2 + 1) << z << endl;
	cout.fill(' ');
	// wstawianie nazw kategorii
	cout << "\174" << setw(spaceValue) << "PESEL" << setw(2) << "|" << setw(spaceValue) << "Imie" << setw(2) << "|" << setw(spaceValue) << "Nazwisko" << setw(2) << "|" << setw(spaceValue) << "Vin pojazu" << setw(2) << "|" << setw(spaceValue) << "Pokonany dystans [km]" << setw(2) << "|" << setw(spaceValue) << "Stanowisko" << setw(2) << "|" << endl;
	cout << setfill(z) << setw(6 * spaceValue + 6 * 2 + 1) << z << endl;
	cout.fill(' ');
	for (auto i : mapPrac) {
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
		cout << setfill(z) << setw(6 * spaceValue + 2 * 6 + 1) << z << endl;
		cout.fill(' ');
	}
}