#include "Header.h"


void KontenerStacji::delRecord(string numer) {
	bool exist = false;
	try{
	for (auto i : mapStacji) {
		if (i.first == numer) exist = true;
	}
	if (!exist) throw CustomException("Stacja o takim ID nie istnieje w bazie.");
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
	return adres + ";" + firma + ";" + ceny + ";" + rabat + ";";  
}


void KontenerStacji::addRecord()
{
	string adres, nazwa,numer;
	string cenaBenzyny{}, cenaRopy{}, cenaGazu{}, znizka;
	
	cout << "Podaj numer stacji:";
	try
	{
		cin >> numer;
		for (auto i = mapStacji.begin(); i != mapStacji.end(); ++i) {
			if (is_digits(numer) == false)
			{
				throw CustomException("Numer zawiera niedozwolone znaki! ");
				

			}
			if (numer == i->first) throw CustomException("W bazie znajduje si\251 ju\276 Stacja o podanym numerze! ");
		}
		cout << "Podaj adres stacji:";
		cin.ignore();
		getline(cin, adres);
		if (containsDigitsANDLetters(adres) == false) throw CustomException("Adres zawiera niedozwolone znaki! ");
		

		cout << "Podaj nazw\251 stacji:";
		getline(cin, nazwa);
		if (containsDigitsANDLetters(nazwa) == false) throw CustomException("Nazwa zawiera niedozwolone znaki! ");

		cout << "Podaj wysoko\230\206 ceny benzyny:";
		cin >> cenaBenzyny;
		if (is_digits2(cenaBenzyny) == false || stod(cenaBenzyny) < 0 || cenaBenzyny.length() > 20) throw CustomException("Cena zosta\210a wpisana niepoprawnie! ");

		cout << "Podaj wysoko\230\206 ceny oleju nap\251dowego:";
		cin >> cenaRopy;
		if (is_digits2(cenaRopy) == false || stod(cenaRopy) < 0 || cenaRopy.length() > 20) throw CustomException("Cena zosta\210a wpisana niepoprawnie!");

		cout << "Podaj wysoko\230\206 ceny gazu:";
		cin >> cenaGazu;
		if (is_digits2(cenaGazu) == false || stod(cenaGazu) < 0||cenaGazu.length()>20) throw CustomException("Cena zosta\210a wpisana niepoprawnie!");
		
		cout << "Podaj wysoko\230\206 zni\276ki:";
		cin >> znizka;
		//CommaAndDot(znizka);
		if (is_digits2(znizka) == false||stod(znizka)<0||stod(znizka)>1||znizka.length()>20) throw CustomException("Zni\276ka zosta\210a wpisana niepoprawnie!");


		StacjaPaliw* wskStacji = new StacjaPaliw(numer,nazwa, adres, stod(cenaBenzyny), stod(cenaRopy), stod(cenaGazu), stod(znizka));
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

void KontenerStacji:: info() {
	char z = '_';
	int spaceValue = 25;

	cout << "Dane z pliku: " << getPathToFile() << " : \n\n";
	cout << setfill(z) << setw(spaceValue * 6 + 7 * 2 + spaceValue / 3 + 1) << z << endl;
	cout.fill(' ');
	// wstawianie nazw kategorii
	cout <<"\174"<< setw(spaceValue/3) << "Numer ID" << setw(2) << "|" << setw(spaceValue) << "Adres" << setw(2) << "|" << setw(spaceValue) << "Nazwa" << setw(2) << "|" << setw(spaceValue) << "Cena benzyny [z\210/l]" << setw(2) << "|" << setw(spaceValue) << "Cena diesla [z\210/l]" << setw(2) << "|" << setw(spaceValue) << "Cena gazu [z\210/l]" << setw(2) << "|" << setw(spaceValue) << "Wysoko\230\206 zni\276ki" << setw(2) << "|" << endl;
	
	cout << setfill(z) << setw(spaceValue * 6 + 7 * 2 + spaceValue/3+1) << z << endl;
	cout.fill(' ');
	
		for (auto i : mapStacji) {
			stringstream ss;
			ss << (i.second->formatDataToString());
			string tmp;
			cout <<"|"<< setw(spaceValue / 3) << i.first << setw(2);
			;
			while ((getline(ss, tmp, ';'))) {
				cout << "|" << setw(spaceValue) << tmp << setw(2);
				;
			}
			cout << "|" << endl;
			cout << setfill(z) << setw(spaceValue * 6 + 7 * 2 + spaceValue / 3 + 1) << z << endl;
			cout.fill(' ');
		}
}
