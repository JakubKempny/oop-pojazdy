#include "Header.h"

void KontenerCar::createMapFromFile(vector<string> wiersze) {
	string marka, model, rpaliwa, vin;
	unsigned int rok;
	double spalanie;
	mapCar.clear(); // tak na wypadek jabyœmy chcieli wywo³aæ t¹ funkcjê drugi raz
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, vin, ';');
		getline(ss, marka, ';');
		getline(ss, model, ';');
		ss >> rok;
		ss.ignore(); // Ignorowanie œrednika
		ss >> setprecision(2) >> spalanie;
		ss.ignore(); // Ignorowanie œrednika
		getline(ss, rpaliwa, ';');
		if (!ss.eof()) {
			throw CustomException("Blad odczytu danych z pliku. Blad wystapil dla samochodu o numerze Vin: " + vin, 102);
		}
		Car* wskCar = new Car(marka, model, rok, spalanie, rpaliwa);
		mapCar.insert(make_pair(vin, wskCar));
	}
}
void KontenerCar::addRecord() {
	string marka, model, rpaliwa, vim, spalanieStr, rokStr;
	unsigned int rok;
	double spalanie;
	cout << endl << "Dodawanie nowego samochodu." << endl;
	cout << "Podaj Vim samochodu (1-17 znakow): ";
	getlineM(vim);
	try {
		if (is_digits(vim) == false || vim.length() > 17 || stod(vim) <= 0) throw CustomException("Vim zostal niepoprawnie wpisany!");
		for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
			if (vim == i->first) {

				throw CustomException("Powtarza sie numer Vin samochodu.", 200);
			}
		}
		cout << "Podaj marke samochodu (2-20 znakow): ";
		getlineM(marka);
		if (containsDigitsANDLetters(marka) == false || marka.length() > 20 || marka.length() < 2) throw CustomException("Marka zostala niepoprawnie wpisana!");
		cout << "Podaj model samochodu (2-20 znakow): ";
		getlineM(model);
		if (containsDigitsANDLetters(model) == false || model.length() > 20 || model.length() < 2) throw CustomException("Model zostal niepoprawnie wpisany!");
		cout << "Podaj rok produkcji samochodu: ";
		getlineM(rokStr);
		if (is_digits(rokStr) == false || rokStr.length() != 4 || stod(rokStr) < 1900 || stod(rokStr) > 2023) throw CustomException("Rocznik samochodu zostal niepoprawnie wpisany! ");
		rok = stod(rokStr);
		cout << "Podaj spalanie samochodu (l/100km): ";
		getlineM(spalanieStr);
		CommaWithDot(spalanieStr);
		if (is_digits2(spalanieStr) == false || stod(spalanieStr) <= 0 || spalanieStr.length() > 5 || checkMultipleDotsCommas(spalanieStr) == false) throw CustomException("Wysokosc spalanie samochodu zosta³a wpisana niepoprawnie!");
		spalanie = stod(spalanieStr);
		cout << "Podaj rodzaj paliwa samochodu:";
		getlineM(rpaliwa);
		Car* wskNewCar = new Car(marka, model, rok, spalanie, rpaliwa);
		cout << "Czy chcesz zapisac zmiany? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapCar.insert(make_pair(vim, wskNewCar));
			saveChanges();
			cout << "Dodano nowy samochod. Nacisnij dowolny klawisz, aby kontynuowac...";
		}
		else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerCar::delRecord(string plikKierowcy) {
	string vin{};
	try {
		bool exist = false;
		cout << endl << "Usuwanie samochodu, podaj jego numer VIN: ";
		cin >> vin;
		for (auto i : mapCar) {
			if (i.first == vin) exist = true;
		}
		if (!exist) throw CustomException("Smochod o takim numerze Vin nie istnieje w bazie.");
		if (czyPrzypCar(vin, plikKierowcy)) throw CustomException("Samochod o takim numerze Vin jest juz przypisany do pracownika. Usuc najpierw pracownika i sprobuj ponownie! ");
		cout << "Czy napewno chcesz usunac pojazd o numerze VIN: " << vin << "? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapCar.erase(vin);
			saveChanges();
			cout << "Smochod o numerze vin:" << vin << " zostal usuniety." << " Nacisnij dowolny klawisz, aby kontynuowac...";
		}
		else cout << "Pojazd nie zostal usuniety";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerCar::saveChanges() {
	ifstream f(this->getPathToFile());
	if (f.good()) { // trzeba sprawdzic czy taki plik istnieje, gdyby nie istnia³ to program bez tego if'a stworzy³by nowy plik, a tego nie chcemy
		fstream plik(this->getPathToFile(), ios::out | ios::trunc); // plik otwarty tak aby nadpisa³ dane zawarte w pliku
		stringstream ss;
		for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
			ss << i->first << ";" << i->second->formatDataToString() << "\n";
		}
		plik << ss.str();
		plik.close();
	}
}

void KontenerCar::info() {
	int spaceValue = 16;
	char z = '_';
	cout << "Dane z pliku: " << getPathToFile() << " :" << endl << endl;
	cout << setfill(z) << setw(spaceValue * 5 + 6 * 2 + spaceValue / 2 + 1) << z << endl;
	cout.fill(' ');
	// wstawianie nazw kategorii
	cout << "|" << setw(spaceValue / 2) << "nrVin" << setw(2) << "|" << setw(spaceValue) << "Marka" << setw(2) << "|" << setw(spaceValue) << "Model" << setw(2) << "|" << setw(spaceValue) << "Rocznik" << setw(2) << "|" << setw(spaceValue) << "Spalanie" << setw(2) << "|" << setw(spaceValue) << "Paliwo" << setw(2) << "|" << endl;
	// wstawianie lini
	cout << setfill(z) << setw(spaceValue * 5 + 6 * 2 + spaceValue / 2 + 1) << z << endl;
	cout.fill(' ');
	for (auto i : mapCar) {
		stringstream ss;
		ss << (i.second->formatDataToString());
		string tmp;
		cout << "|" << setw(spaceValue / 2) << i.first << setw(2);
		;
		while ((getline(ss, tmp, ';'))) {
			cout << "|" << setw(spaceValue) << tmp << setw(2);
			;
		}
		cout << "|" << endl;
		cout << setfill(z) << setw(spaceValue * 5 + 6 * 2 + spaceValue / 2 + 1) << z << endl;
		cout.fill(' ');
	}
}

bool KontenerCar::vinIstnieje(string vin) { //Sprawdza czy numer VIN istnieje w bazie pojazd{
	for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
		if (vin == i->first) {
			return true;
		}
	}
	return false;
}

bool KontenerCar::czyPrzypCar(string vin, string plikKierowcy) {
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

		if (kolumny[3] == vin && kolumny[3].size() == vin.size()) {
			plik.close();
			return true;
		}
	}
	plik.close();
	return false;
}