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
		//wywal wyj¹tek 
		cout << "Nie udalo sie otowrzyc pliku" << endl;
	}
	
}

void KontenerCar::createMapFromFile(vector<string> wiersze) {
	
	string marka, model, rpaliwa, vim;
	unsigned int rok;
	double spalanie, maxP;
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
			// wywal wyjatek !!!!!
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

void KontenerCar::saveChanges() {
	fstream plik(this->getPathToFile(),ios::out | ios::trunc); // plik otwarty tak aby nadpisa³ dane zawarte w pliku
	stringstream ss;
	for (auto i = mapCar.begin(); i != mapCar.end(); ++i) {
		ss << i->first << ";"<<i->second->formatDataToString()<<"\n";
	}
	plik << ss.str();
	plik.close();
	cout << "Zapisano zmiany" << endl;
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