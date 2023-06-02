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

void KontenerCar::createMapFromFile(vector<string> wiersze) {
	string marka, model, rpaliwa, vim;
	unsigned int rok;
	double spalanie, maxP;
	mapCar.clear(); // tak na wypadek jabyœmy chcieli wywo³aæ t¹ funkcjê drugi raz
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, vim, ';');
		getline(ss, marka, ';');
		getline(ss, model, ';');
		ss >> rok;
		ss.ignore(); // Ignorowanie œrednika
		ss >> spalanie;
		ss.ignore(); // Ignorowanie œrednika
		getline(ss, rpaliwa, ';');
		ss >> maxP;
		if (!ss.eof()) {
			throw CustomException("Blad odczytu danych z pliku. Blad wystapil dla auta o numerze Vin: "+vim);
		}
		Car* wskCar = new Car(marka, model, rok, spalanie, rpaliwa, maxP);
		mapCar.insert(make_pair(vim, wskCar));
	}
}
void KontenerCar::addRecord() {
	string marka, model, rpaliwa, vim;
	unsigned int rok;
	double spalanie, maxP;
	cout << "Podaj Vim auta:";
	cin >> vim;
	for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
		if (vim == i->first) {
			// wywal wyj¹tek !!!!!
			// powtarza siê klucz unikalny
		}
	}
	cout << "Podaj marke auta:";
	cin >> marka;
	cout << "Podaj model auta:";
	cin.ignore();
	getline(cin,model);
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
	cout << "Dodano nowe auto. Aby zmiana byla trwala zapisz zmiany."<<endl;
}

void KontenerCar::delRecord(string vin) {
	bool exist = false;
	for (auto i : mapCar) {
		if (i.first == vin) exist = true;
	}
	if (exist) {
		mapCar.erase(vin);
		cout << "Auto o kodzie vin:" << vin << " zostalo usuniete" << endl;
	}
	else {
		// wywal wyj¹tek !!!
		// Nie ma takiego auta w mapCar
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
		cout << "Zapisano zmiany" << endl;
	}
	
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
	return to_string(spalanie) + ";" + rodzajPaliwa + ";" + to_string(paliwo.second);
}