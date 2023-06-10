#include "Header.h"

void KontenerCar::createMapFromFile(vector<string> wiersze) {
	string marka, model, rpaliwa, vin;
	unsigned int rok;
	double spalanie, maxP;
	mapCar.clear(); // tak na wypadek jaby�my chcieli wywo�a� t� funkcj� drugi raz
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, vin, ';');
		getline(ss, marka, ';');
		getline(ss, model, ';');
		ss >> rok;
		ss.ignore(); // Ignorowanie �rednika
		ss >> setprecision(2) >> spalanie;
		ss.ignore(); // Ignorowanie �rednika
		getline(ss, rpaliwa, ';');
		ss >> setprecision(2) >> maxP;
		if (!ss.eof()) {
			throw CustomException("Blad odczytu danych z pliku. Blad wystapil dla auta o numerze Vin: " + vin, 102);
		}
		Car* wskCar = new Car(marka, model, rok, spalanie, rpaliwa, maxP);
		mapCar.insert(make_pair(vin, wskCar));
	}
}
void KontenerCar::addRecord() {
	string marka, model, rpaliwa, vim;
	unsigned int rok;
	double spalanie, maxP;
	cout << "Podaj Vim auta:";
	cin >> vim;
	try {
		for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
			if (vim == i->first) {
				// wywal wyj�tek !!!!!
				// powtarza si� klucz unikalny
				throw CustomException("Powtarza sie numer Vin auta.", 200);
			}
		}
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
		addRecord(); // Ponownie uruchamiay funkcje
	}
	cout << "Podaj marke auta:";
	cin >> marka;
	cout << "Podaj model auta:";
	cin.ignore();
	getline(cin, model);
	cout << "Podaj rok produkcji auta:";
	cin >> rok;
	cout << "Podaj spalanie auta (l/100km):";
	cin >> spalanie;
	cout << "Podaj rodzaj paliwa auta:";
	cin >> rpaliwa;
	cout << "Podaj maksymalnosc ilosc paliwa w aucie:";
	cin >> maxP;
	Car* wskNewCar = new Car(marka, model, rok, spalanie, rpaliwa, maxP);
	mapCar.insert(make_pair(vim, wskNewCar));
	cout << "Dodano nowe auto. Aby zmiana byla trwala zapisz zmiany." << endl;
}

void KontenerCar::delRecord(string vin) {
	try {
		bool exist = false;
		for (auto i : mapCar) {
			if (i.first == vin) exist = true;
		}
		if (!exist) throw CustomException("Auto o takim numerze Vin nie istnieje w bazie.");
		mapCar.erase(vin);
		cout << "Auto o numerze vin:" << vin << " zostalo usuniete" << endl;
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerCar::saveChanges() {
	ifstream f(this->getPathToFile());
	if (f.good()) { // trzeba sprawdzic czy taki plik istnieje, gdyby nie istnia� to program bez tego if'a stworzy�by nowy plik, a tego nie chcemy
		fstream plik(this->getPathToFile(), ios::out | ios::trunc); // plik otwarty tak aby nadpisa� dane zawarte w pliku
		stringstream ss;
		for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
			ss << i->first << ";" << i->second->formatDataToString() << "\n";
		}
		plik << ss.str();
		plik.close();
		cout << "Zapisano zmiany" << endl;
	}
}

void KontenerCar::info() {
	// tymczasowo
	cout << "Dane z pliku: " << getPathToFile() << " :" << endl;
	int spaceValue = 16;
	// wstawianie nazw kategorii
	cout << setw(spaceValue / 2) << "nrVin" << setw(2) << "|" << setw(spaceValue) << "Marka" << setw(2) << "|" << setw(spaceValue) << "Model" << setw(2) << "|" << setw(spaceValue) << "Rocznik" << setw(2) << "|" << setw(spaceValue) << "Spalanie" << setw(2) << "|" << setw(spaceValue) << "Paliwo" << setw(2) << "|" << setw(spaceValue) << "Pojemnosc paliwa" << setw(2) << "|" << endl;

	// wstawianie lini
	char z = '-';
	cout << setfill(z) << setw(spaceValue * 6 + 7 * 2 + spaceValue / 2) << z << endl;
	cout.fill(' ');

	for (auto i : mapCar) {
		stringstream ss;
		ss << (i.second->formatDataToString());
		string tmp;
		cout << setw(spaceValue / 2) << i.first << setw(2);
		;
		while ((getline(ss, tmp, ';'))) {
			cout << "|" << setw(spaceValue) << tmp << setw(2);
			;
		}
		cout << "|" << endl;
	}
}

bool KontenerCar::vinIstnieje(string vin) //Sprawdza czy numer VIN istnieje w bazie pojazdy
{
	for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
		if (vin == i->first)
		{
			return true;
		}
	}
	return false;
}

string Car::formatDataToString() {
	string	pojazd = Pojazd::formatDataToString(),
		silnik = Silnik::formatDataToString();
	return	pojazd + ";" + silnik;

}
string Pojazd::formatDataToString() {
	return marka + ";" + model + ";" + to_string(rocznik);
}

string Silnik::formatDataToString() {
	string sTmp, pTmp;
	stringstream ss;
	ss << fixed << setprecision(1);
	double s = spalanie,
		p = paliwo.second;
	ss << s << " " << p;
	ss >> sTmp >> pTmp;
	return sTmp + ";" + rodzajPaliwa + ";" + pTmp;
}