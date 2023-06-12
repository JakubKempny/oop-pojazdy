#include "Header.h"

void KontenerStacji::delRecord(string numer) {
	bool exist = false;
	try{
	for (auto i : mapStacji) {
		if (i.first == numer) exist = true;
	}
	if (!exist) throw CustomException("Stacja o takim id nie istnieje w bazie.");
		mapStacji.erase(numer);
		cout << "Stacja benzynowa z adresem: " << numer << " zosta\210a usuni\251ta\n";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

string Ceny::formatDataToString()
{
	string benz;
	string ropa;
	string gaz;
	stringstream ss;
	ss << fixed << setprecision(2);
	ss << cenaBenzyny << ";" << cenaRopy << ";" << cenaGazu;
	ss >> benz;
	return benz;
}

string StacjaPaliw::formatDataToString()
{
	string ceny = Ceny::formatDataToString();
	string rabat{};
	stringstream ss;
	ss << znizka;
	ss >> rabat;
	string adres = Budynek::getName();
	return adres + ";" + firma + ";" + ceny + ";" + rabat + ";";  /// a adres?
}

void KontenerStacji::addRecord()
{
	string adres, nazwa,numer;
	double cenaBenzyny{}, cenaRopy{}, cenaGazu{}, znizka;
	cout << "Podaj numer stacji:";
	try
	{
		cin >> numer;
		for (auto i = mapStacji.begin(); i != mapStacji.end(); ++i) {
			if (numer == i->first) throw CustomException("W bazie znajduje si\251 ju\276 Stacja o podanym numerze! ");
		}
		/*cout << "Podaj adres stacji:";
		cin.ignore();
		getline(cin, adres);*/

		cout << "Podaj nazw\251 stacji:";
		cin.ignore();
		getline(cin, nazwa);
		

		cout << "Podaj wysoko\230\206 ceny benzyny:";
		cin >> cenaBenzyny;
		
		cout << "Podaj wysoko\230\206 ceny oleju nap\251dowego:";
		cin >> cenaRopy;
		
		cout << "Podaj wysoko\230\206 ceny gazu:";
		cin >> cenaGazu;
		
		cout << "Podaj wysoko\230\206 zni\276ki:";
		cin >> znizka;
		StacjaPaliw* wskStacji = new StacjaPaliw(numer,nazwa, adres, cenaBenzyny, cenaRopy, cenaGazu, znizka);
		mapStacji.insert(make_pair(numer, wskStacji));
		cout << "Dodano now\245 stacj\251. Aby zmiana by\210a trwa\210a zapisz zmiany." << endl;
	}
	catch (CustomException& e)
	{
		cout << e.what() << endl;
	}
}

void KontenerStacji::createMapFromFile(vector<string> wiersze) {
	string nazwa, adres,numer;
	double cenaBenzyny, cenaGazu, cenaRopy, znizka;
	mapStacji.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, numer, ';');
		getline(ss, adres, ';');
		getline(ss, nazwa, ';');
		ss >> cenaBenzyny;
		ss.ignore();
		ss >> cenaGazu;
		ss.ignore();
		ss >> cenaRopy;
		ss.ignore();
		ss >> znizka;
		ss.ignore();
		StacjaPaliw* wskStacji = new StacjaPaliw(numer ,nazwa, adres, cenaBenzyny, cenaRopy, cenaGazu, znizka);
		mapStacji.insert(make_pair(numer, wskStacji));
	}
}

void KontenerStacji::saveChanges()
{
	ifstream f(this->getPathToFile());
	if (f.good()) {
		fstream plik(this->getPathToFile(), ios::out | ios::trunc);
		stringstream ss;
		for (auto i = mapStacji.begin(); i != mapStacji.end(); ++i) {
			ss << i->first << ";" << i->second->formatDataToString() << "\n";
		}
		plik << ss.str();
		plik.close();
	}
}
