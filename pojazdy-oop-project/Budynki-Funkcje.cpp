#include "Header.h"

void KontenerStacji::delRecord(string adres){
	bool exist = false;
	for (auto i : mapStacji){
		if (i.first == adres) exist = true;
	}
	if (exist){
		mapStacji.erase(adres);
		cout << "Stacja benzynowa z adresem: " << adres << " zosta\210a usuni\251ta\n";
	}
	else{
		string e = "Stacja benzynowa o podanym adresie nie istnieje!\n";
		throw e;
	}
}

void KontenerStacji::addRecord()
{
	string nazwa, adres;

	double cenaRopy{}, cenaBenzyny{}, cenaGazu{}, znizka{};

	cout << "Podaj nazw\251 stacji: ";
	cin >> nazwa;
	cout << "Podaj adres stacji: ";
	cin >> adres;
}

void KontenerStacji::createMapFromFile(vector<string> wiersze) {
	string nazwa, adres, cenaBenzynyStr, cenaGazuStr, cenaRopyStr, znizkaStr;


	mapStacji.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, nazwa, ';');
		getline(ss, adres, ';');
		getline(ss, znizkaStr, ';');
		double znizka = stod(znizkaStr);
		getline(ss, cenaBenzynyStr, ';');
		double cenaBenzyny = stod(znizkaStr);  //zmiana stringa na doubla
		getline(ss, cenaRopyStr, ';');
		double cenaRopy = stod(cenaRopyStr);
		getline(ss, cenaGazuStr, ';');
		double cenaGazu = stod(cenaGazuStr);
		Ceny cena1(cenaBenzyny, cenaRopy, cenaGazu);
		// tu jescze ten wektor na pesel ale to nw jak siê tym ob³ugiwaæ

		StacjaPaliw* wskStacji = new StacjaPaliw(nazwa, adres, cena1, znizka);
		mapStacji.insert(make_pair(adres, wskStacji));
	}
}

void KontenerStacji::saveChanges() {
	ifstream f(this->getPathToFile());
	if (f.good()) {
		fstream plik(this->getPathToFile(), ios::out | ios::trunc);
		stringstream ss;
		for (auto i = mapStacji.begin(); i != mapStacji.end(); ++i) {
			//TO DO ODKOMENTOWANIA POTEM< BO NIE MA NAPISANEJ FUNKCJI ZWRACAJACEJ WIERSZE formatDataTostring()
			//ss << i->first << ";" << i->second->formatDataToString() << "\n";
		}
		plik << ss.str();
		plik.close();
		cout << "Zapisano zmiany" << endl;
	}
}
