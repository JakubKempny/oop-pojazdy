#include "Header.h"

//Ponizsze fukcje odnosza sie do Pracownika

Pesel::Pesel(string n) //Funkcja sprawdzajaca czy PESEL jest poprawny
{
	if ((is_digits(n)) && (n.length() == 11)) {
		nr = n;
	}
	else throw CustomException("PESEL jest niepoprawny! ");
}

string Pracownik::formatDataToString() {
	string dyst;
	stringstream ss;
	ss << fixed << setprecision(1);
	ss << dystans;
	ss >> dyst;
	string stan = Stanowisko::getName();
	return  imie + ";" + nazwisko + ";" + vinPojazdu + ";" + dyst + ";" + stan + ";";
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

bool KontenerStanow::stanowIstnieje(string nazwa)
{
	for (auto i = mapStan.begin(); i != mapStan.end(); ++i) {
		if (nazwa == i->first)
		{
			return true;
		}
	}
	return false;
}


void KontenerKierow::addRecord(KontenerCar& k, KontenerStanow& s) {
	string imie, nazwisko, pesel, vin, stanowisko;
	double dystans;
	char input{};	

	cout << endl << "Dodawanie nowego pracownika." << endl;
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
		cout << "Podaj sredni dystans jaki pokonuje pracownik km/dzien:";
		cin >> dystans;
		cout << "Podaj stanowisko pracownika:";
		cin >> stanowisko;
		if (!s.stanowIstnieje(stanowisko)) throw CustomException("Podane stanowisko nie istnieje! ");
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
	catch (CustomException& e)
	{
		cout << e.what() << endl;
	}
}

void KontenerKierow::delRecord() {

	string pesel{};
	bool exist = false;
	cout << endl << "Usuwanie pracownika, podaj jego pesel: " << endl;
	cin >> pesel;
	char input{};
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
	cout << "\174" << setw(spaceValue ) << "PESEL" << setw(2) << "|" << setw(spaceValue) << "Imie" << setw(2) << "|" << setw(spaceValue) << "Nazwisko" << setw(2) << "|" << setw(spaceValue) << "Vin pojazu" << setw(2) << "|" << setw(spaceValue) << "Pokonany dystans [km]" << setw(2) << "|" << setw(spaceValue) << "Stanowisko" << setw(2) << "|"<<endl;

	cout << setfill(z) << setw(6 *spaceValue+6*2+ 1) << z << endl;
	cout.fill(' ');

	for (auto i : mapPrac) {
		stringstream ss;
		ss << (i.second->formatDataToString());
		string tmp;
		cout << "|" << setw(spaceValue ) << i.first << setw(2);
		;
		while ((getline(ss, tmp, ';'))) {
			cout << "|" << setw(spaceValue) << tmp << setw(2);
			;
		}
		cout << "|" << endl;
		cout << setfill(z) << setw(6*spaceValue + 2 *6 + 1) << z << endl;
		cout.fill(' ');
	}
}


//Ponizsze funkcje odnosza sie do stanowiska


Stanowisko::Stanowisko(string nazwaStanowiska)
{
	this->nazwaStanowiska = nazwaStanowiska;
}

Stanowisko::Stanowisko(string nazwaStanowiska, double proc_pokrycia)
{
	this->nazwaStanowiska = nazwaStanowiska;
	this->proc_pokrycia = proc_pokrycia;
}

string Stanowisko::getName()
{
	return this->nazwaStanowiska;
}

string Stanowisko::formatDataToString() {
	string proc;
	stringstream ss;
	ss << fixed << setprecision(2);
	ss << proc_pokrycia;
	ss >> proc;
	return  proc + ";";
}

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
	string nazwa;
	double proc_pokrycia;
	char input;

	cout << endl << "Dodawanie nowego stanowiska." << endl;
	cout << "Podaj nazwe stanowiska: " << endl;
	try
	{
		cin >> nazwa; //trzeba dodac potem wyjatek i sprawdzic czy nazwa nie ma spacji
		for (auto& c : nazwa){ //zmiana wszystkich znakow w stringu na male aby potem uniknac problemow typu: Menadzer vs menadzer
			nazwa = tolower(c);
		}
		for (auto i = mapStan.begin(); i != mapStan.end(); ++i) {
			if (nazwa == i->first) throw CustomException("W bazie znajduje sie juz stanowisko o podanej nazwie! ");
		}
		cout << "Podaj procent pokrycia kosztow paliwa(np. 0.40 to 40% kosztow ktore pokrywa firma):";
		cin >> proc_pokrycia;

		Stanowisko* wskNewStan = new Stanowisko(nazwa, proc_pokrycia);
		cout << "Czy chcesz zapisac zmiany? y/n: ";
		cin >> input;
		if (input == 'y') {
			cout << "Pomyslnie utworzono nowe stanowisko. Nacisnij dowolny klawisz, aby kontynuowac...";
			mapStan.insert(make_pair(nazwa, wskNewStan));
			saveChanges();
		} else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	catch (CustomException& e)
	{
		cout << e.what() << endl;
	}
}

bool KontenerStanow::czyPrzypStan(string nazwaStanow, string plikKierowcy)
{
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

		if (kolumny[5] == nazwaStanow && kolumny[5].size() == nazwaStanow.size())
		{
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
	char input;
	cout << endl << "Usuwanie stanowiska, podaj jego nazwe: " << endl;
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
			cout << "Stanowisko:" << nazwa << " zostalo usuniete." << "Nacisnij dowolny klawisz, aby kontynuowac...";
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
	cout << "\174" << setw(spaceValue) << "Stanowisko" << setw(2) << "|" << setw(spaceValue) << "Wysokosc znizki [*100%]"<< setw(2)<<"|" << endl;
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
