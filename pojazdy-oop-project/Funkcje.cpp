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
	string marka, model, rpaliwa, vin;
	unsigned int rok;
	double spalanie, maxP;
	mapCar.clear(); // tak na wypadek jabyœmy chcieli wywo³aæ t¹ funkcjê drugi raz
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, vin, ';');
		getline(ss, marka, ';');
		getline(ss, model, ';');
		ss >> rok;
		ss.ignore(); // Ignorowanie œrednika
		ss >>setprecision(2)>> spalanie;
		ss.ignore(); // Ignorowanie œrednika
		getline(ss, rpaliwa, ';');
		ss >>setprecision(2) >> maxP;
		if (!ss.eof()) {
			throw CustomException("Blad odczytu danych z pliku. Blad wystapil dla auta o numerze Vin: "+vin,102);
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
				// wywal wyj¹tek !!!!!
				// powtarza siê klucz unikalny
				throw CustomException("Powtarza sie numer Vin auta.", 200);
			}
		}
	}
	catch(CustomException &e){
		cout << e.what() << endl; 
		addRecord(); // Ponownie uruchamiay funkcje
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
	try {
		bool exist = false;
		for (auto i : mapCar) {
			if (i.first == vin) exist = true;
		}
		if (!exist) throw CustomException("Auto o takim numerze Vin nie istnieje w bazie.");
		mapCar.erase(vin);
		cout << "Auto o numerze vin:" << vin << " zostalo usuniete" << endl;
	}
	catch (CustomException &e) {
		cout << e.what()<<endl;
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

void KontenerCar::info(){ 
	// tymczasowo
	cout << "Dane z pliku: " << getPathToFile() << " :" << endl;
	int spaceValue = 16;
	// wstawianie nazw kategorii
	cout << setw(spaceValue / 2) << "nrVin" << setw(2) << "|" << setw(spaceValue) << "Marka" << setw(2) << "|" << setw(spaceValue) << "Model" << setw(2) << "|" << setw(spaceValue) << "Rocznik" << setw(2) << "|" << setw(spaceValue) << "Spalanie" << setw(2) << "|" << setw(spaceValue) << "Paliwo" << setw(2) << "|" << setw(spaceValue) << "Pojemnosc paliwa" << setw(2) << "|" <<endl;
	
	// wstawianie lini
	char z = '-';
	cout << setfill(z) << setw(spaceValue * 6 + 7 * 2 + spaceValue / 2) << z << endl;
	cout.fill(' ');
	
	for (auto i : mapCar) {
		stringstream ss;
		ss << (i.second->formatDataToString());
		string tmp;
		cout << setw(spaceValue/2) << i.first << setw(2);
		;
		while ((getline(ss, tmp, ';'))) {
			cout << "|" << setw(spaceValue) << tmp << setw(2);
			;
		}
		cout <<"|" << endl;
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
	string sTmp, pTmp;
	stringstream ss;
	ss << fixed << setprecision(1);
	double s = spalanie,
		   p = paliwo.second;
	ss << s << " " << p;
	ss >> sTmp >> pTmp;
	return sTmp + ";" + rodzajPaliwa + ";" + pTmp;
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

Pesel::Pesel(string n) //Funkcja sprawdzajaca czy PESEL jest poprawny
{
	if ((is_digits(n)) && (n.length() == 11)) {
			nr = n;
	} else throw CustomException("PESEL jest niepoprawny! ");
}

string Pracownik::formatDataToString() {
	return  imie + ";" + nazwisko + ";" + vinPojazdu + ";";
}

bool KontenerKierow::vinWolny(string vin) //Sprawdza czy numer VIN nie jest juz przypadkie zajety przez innego kierowce
{
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
				cout << "Nieprawidlowy format linii." << endl;
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

void KontenerKierow::createMapFromFile(vector<string> wiersze) {
	string imie, nazwisko, pesel, vin;
	mapPrac.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, pesel, ';');
		getline(ss, imie, ';');
		getline(ss, nazwisko, ';');
		getline(ss, vin, ';');
		Pracownik* wskPrac = new Pracownik(imie, nazwisko, pesel, vin);
		mapPrac.insert(make_pair(pesel, wskPrac));
	}
}

void KontenerKierow::addRecord(KontenerCar& k) {
	string imie, nazwisko, pesel, vin;
	string e;
	cout << "Podaj Pesel pracownika:";
	try
	{
		cin >> pesel;
		for (auto i = mapPrac.begin(); i != mapPrac.end(); ++i) {
			if (pesel == i->first) throw CustomException("W bazie znajduje sie juz uzytkownik o podanym numerze Pesel! ");
		}
		cout << "Podaj imie pracownika:";
		cin >> imie;
		if (containsOnlyLetters(imie) == false) throw CustomException("Imie zawiera niedozwolone znaki! ");
		cout << "Podaj nazwisko pracownika:";
		cin >> nazwisko;
		if (containsOnlyLetters(nazwisko) == false) throw CustomException("Nazwisko zawiera niedozwolone znaki! ");
		cout << "Podaj vin pojazdu pracownika:";
		cin >> vin;
		if (!k.vinIstnieje(vin)) throw CustomException("Podany samochod nie istnieje! ");
		if (vinWolny(vin)) throw CustomException("Podany samochod jest juz przypisany do innego kierowcy! ");
		Pracownik* wskNewPrac = new Pracownik(imie, nazwisko, pesel, vin);
		mapPrac.insert(make_pair(pesel, wskNewPrac));
		cout << "Dodano nowego pracownika. Aby zmiana byla trwala zapisz zmiany." << endl;
	}
	catch (CustomException& e)
	{
		cout << e.what() << endl;
	}
}

void KontenerKierow::delRecord(string pesel) {
	bool exist = false;
	for (auto i : mapPrac) {
		if (i.first == pesel) exist = true;
	}
	try {
	if (!exist) throw CustomException("Pracownik o takim numerze PESEL nie istnieje w bazie.");
	mapPrac.erase(pesel);
	cout << "Pracownik o peselu:" << pesel << " zostal usuniety" << endl;
	string e = "Pracownik o podanym numerze PESEL nie istnieje! ";
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
		cout << "Zapisano zmiany" << endl;
	}
}