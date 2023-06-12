#include "Header.h"

void KontenerCar::createMapFromFile(vector<string> wiersze) {
	string marka, model, rpaliwa, vin;
	unsigned int rok;
	double spalanie;
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
		if (!ss.eof()) {
			throw CustomException("B\210ad odczytu danych z pliku. B\201ad wystapi\210 dla auta o numerze Vin: " + vin, 102);
		}
		Car* wskCar = new Car(marka, model, rok, spalanie, rpaliwa);
		mapCar.insert(make_pair(vin, wskCar));
	}
}
void KontenerCar::addRecord() {
	string marka, model, rpaliwa, vim;
	unsigned int rok;
	double spalanie;
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
		cout << "Podaj marke samochodu:";
		cin >> marka;
		cout << "Podaj model samochodu:";
		cin.ignore();
		getline(cin, model);
		cout << "Podaj rok produkcji samochodu:";
		cin >> rok;
		cout << "Podaj spalanie samochodu (l/100km):";
		cin >> spalanie;
		cout << "Podaj rodzaj paliwa samochodu:";
		cin >> rpaliwa;
		Car* wskNewCar = new Car(marka, model, rok, spalanie, rpaliwa);
		mapCar.insert(make_pair(vim, wskNewCar));
		cout << "Dodano nowy samoch\242d. Aby zmiana by\210a trwa\210a zapisz zmiany." << endl;
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerCar::delRecord(string vin, string plikKierowcy) {
	try {
		bool exist = false;
		for (auto i : mapCar) {
			if (i.first == vin) exist = true;
		}
		if (!exist) throw CustomException("Smoch\242d o takim numerze Vin nie istnieje w bazie.");
		if (czyPrzypCar(vin, plikKierowcy)) throw CustomException("Samoch\242d o takim numerze Vin jest ju\276 przypisany do pracownika. Usu\241 najpierw pracownika i spr\242buj ponownie! ");
		mapCar.erase(vin);
		cout << "Smoch\242d o numerze vin:" << vin << " zosta\210 usuni\251ty" << endl;
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
	}
}

void KontenerCar::info() {
	// tymczasowo
	cout << "Dane z pliku: " << getPathToFile() << " :" << endl;
	int spaceValue = 16;
	// wstawianie nazw kategorii
	cout << setw(spaceValue / 2) << "nrVin" << setw(2) << "|" << setw(spaceValue) << "Marka" << setw(2) << "|" << setw(spaceValue) << "Model" << setw(2) << "|" << setw(spaceValue) << "Rocznik" << setw(2) << "|" << setw(spaceValue) << "Spalanie" << setw(2) << "|" << setw(spaceValue) << "Paliwo" << setw(2) << "|"<<endl;

	// wstawianie lini
	char z = '-';
	cout << setfill(z) << setw(spaceValue * 5 + 6 * 2 + spaceValue / 2) << z << endl;
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

bool KontenerCar::czyPrzypCar(string vin, string plikKierowcy)
{
	string linia;
	string nazwa = plikKierowcy;
	ifstream plik(nazwa);
	if (!plik) {
		cout << "Nie mo\276na otworzy\206 pliku." << endl;
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

		if (kolumny[3] == vin && kolumny[3].size() == vin.size())
		{
			plik.close();
			return true;
		}
	}
	plik.close();
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

string Silnik::formatDataToString() { // gites
	string sTmp;
	stringstream ss;
	ss << fixed << setprecision(1);
	ss << spalanie;
	ss >> sTmp;
	return sTmp + ";" + rodzajPaliwa;
}

Silnik::Silnik(double s, string rpaliwa) :spalanie(s) { // konstruktor
	if (rpaliwa == "benzyna" || rpaliwa == "gaz" || rpaliwa == "ropa" || rpaliwa == "pr\245d") {
		rodzajPaliwa = rpaliwa;
	}
	else {
		throw CustomException("Niepoprawny rodzaj paliwa.");
	}
}
