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
		cout << "Nie mo\276na otworzy\206 pliku." << endl;
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
	string e;
	cout << "Podaj Pesel pracownika:";
	try
	{
		cin >> pesel;
		for (auto i = mapPrac.begin(); i != mapPrac.end(); ++i) {
			if (pesel == i->first) throw CustomException("W bazie znajduje si\251 ju\276 u\276ytkownik o podanym numerze Pesel! ");
		}
		cout << "Podaj imi\251 pracownika:";
		cin >> imie;
		if (containsOnlyLetters(imie) == false) throw CustomException("Imie zawiera niedozwolone znaki! ");
		cout << "Podaj nazwisko pracownika:";
		cin >> nazwisko;
		if (containsOnlyLetters(nazwisko) == false) throw CustomException("Nazwisko zawiera niedozwolone znaki! ");
		cout << "Podaj vin pojazdu pracownika:";
		cin >> vin;
		if (!k.vinIstnieje(vin)) throw CustomException("Podany samoch\242d nie istnieje! ");
		if (vinWolny(vin)) throw CustomException("Podany samoch\242d jest ju\276 przypisany do innego kierowcy! ");
		cout << "Podaj \230redni dystans jaki pokonuje pracownik km/dzie\344:";
		cin >> dystans;
		cout << "Podaj stanowisko pracownika:";
		cin >> stanowisko;
		if (!s.stanowIstnieje(stanowisko)) throw CustomException("Podane stanowisko nie istnieje! ");
		Pracownik* wskNewPrac = new Pracownik(imie, nazwisko, pesel, vin, dystans, stanowisko);
		mapPrac.insert(make_pair(pesel, wskNewPrac));
		cout << "Dodano nowego pracownika. Aby zmiana by\210a trwa\210a zapisz zmiany." << endl;
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
		cout << "Pracownik o peselu:" << pesel << " zosta\210 usuni\251ty" << endl;
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
	string e;
	cout << "Podaj nazw\251 stanowiska:";
	try
	{
		cin >> nazwa;
		//for (auto& c : nazwa){ //zmiana wszystkich znakow w stringu na male aby potem uniknac problemow typu: Menadzer vs menadzer
		//	nazwa = tolower(c);
		//}
		for (auto i = mapStan.begin(); i != mapStan.end(); ++i) {
			if (nazwa == i->first) throw CustomException("W bazie znajduje si\251 ju\276 stanowisko o podanej nazwie! ");
		}
		cout << "Podaj procent pokrycia koszt\242w paliwa(np. 0.40 to 40% koszt\242w kt\242re pokrywa firma):";
		cin >> proc_pokrycia;

		Stanowisko* wskNewStan = new Stanowisko(nazwa, proc_pokrycia);
		mapStan.insert(make_pair(nazwa, wskNewStan));
		cout << "Dodano nowe stanowisko. Aby zmiana byla trwa\210a zapisz zmiany." << endl;
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

		if (kolumny[5] == nazwaStanow && kolumny[5].size() == nazwaStanow.size())
		{
			plik.close();
			return true;
		}
	}
	plik.close();
	return false;
}

void KontenerStanow::delRecord(string nazwa, string plikKierowcy) {
	bool exist = false;
	for (auto i : mapStan) {
		if (i.first == nazwa) exist = true;
	}
	try {
		if (!exist) throw CustomException("Stanowisko o takiej nazwie nie istnieje w bazie.");
		if (czyPrzypStan(nazwa, plikKierowcy)) throw CustomException("Stanowisko o takiej nazwie jest ju\276 przypisane do pracownika. Nie mo\276na usun\245\206 stanowiska! "); // sprawdzi czy stanowisko przypadkiem nie jest juz przypisane do jakiegos pracownika
		mapStan.erase(nazwa);
		cout << "Stanowisko:" << nazwa << " zosta\210o usuni\251te" << endl;
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
