#include "Header.h"

void KontenerStacji::delRecord(string adres) {
	bool exist = false;
	for (auto i : mapStacji) {
		if (i.first == adres) exist = true;
	}
	if (exist) {
		mapStacji.erase(adres);
		cout << "Stacja benzynowa z adresem: " << adres << " zosta\210a usuni\251ta\n";
	}
	else {
		string e = "Stacja benzynowa o podanym adresie nie istnieje!\n";
		throw e;
	}
}

string Ceny::formatDataToString()
{
	string benz;
	string ropa;
	string gaz;
	stringstream ss;
	ss << fixed << setprecision(1);
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
	return firma + ";" + ceny + ";" + rabat + ";";
}

void KontenerStacji::addRecord()
{
	string adres, nazwa;
	double cenaBenzyny{}, cenaRopy{}, cenaGazu{}, znizka;
	cout << "Podaj adres stacji:";
	try
	{
		getline(cin, adres);
		for (auto i = mapStacji.begin(); i != mapStacji.end(); ++i) {
			if (adres == i->first) throw CustomException("W bazie znajduje si\251 ju\276 Stacja o podanym adresie! ");
		}
		cout << "Podaj nazw\251 stacji:";
		cin >> nazwa;
		

		cout << "Podaj wysoko\230\206 ceny benzyny:";
		cin >> cenaBenzyny;
		
		cout << "Podaj wysoko\230\206 ceny oleju nap\251dowego:";
		cin >> cenaRopy;
		
		cout << "Podaj wysoko\230\206 ceny gazu:";
		cin >> cenaGazu;
		
		cout << "Podaj wysoko\230\206 zni\276ki:";
		cin >> znizka;
		StacjaPaliw* wskStacji = new StacjaPaliw(nazwa, adres, cenaBenzyny, cenaRopy, cenaGazu, znizka);
		mapStacji.insert(make_pair(adres, wskStacji));
		cout << "Dodano now\245 stacj\251. Aby zmiana byla trwala zapisz zmiany." << endl;
	}
	catch (CustomException& e)
	{
		cout << e.what() << endl;
	}
}

void KontenerStacji::createMapFromFile(vector<string> wiersze) {
	string nazwa, adres;
	double cenaBenzyny, cenaGazu, cenaRopy, znizka;
	mapStacji.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
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
		StacjaPaliw* wskStacji = new StacjaPaliw(nazwa, adres, cenaBenzyny, cenaRopy, cenaGazu, znizka);
		mapStacji.insert(make_pair(adres, wskStacji));
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
