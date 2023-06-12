#include "Header.h"
#include<Windows.h>

void KontenerStacji::delRecord() {
	string id;
	char input{};
	cout << endl << "Usuwanie stacji, podaj ID: ";
	cin >> id;
	bool exist = false;
	try{
	for (auto i : mapStacji) {
		if (i.first == id) exist = true;
	}
	if (!exist) throw CustomException("Stacja o takim ID nie istnieje w bazie.");
	cout << "Czy napewno chcesz usun\245\206 stacje paliw z ID: " << id << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		mapStacji.erase(id);
		saveChanges();
		cout <<"Stacja benzynowa z id: " << id << " zosta\210a usuni\251ta\n." << "Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	} else cout << "Stacja nie zosta\210a usuni\251ta";
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
	string adres, nazwa,numer, miasto,ulica,numerUl;
	string cenaBenzyny{}, cenaRopy{}, cenaGazu{}, znizka;
	char input{};
	cout << endl << "\nDodawanie nowej stacji.\n" << endl;
	cout << "Podaj numer ID stacji: ";
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
		cout << "Podaj miasto, w kt\242rym znajduje si\251 stacja:";
		cin.ignore();
		getline(cin, miasto);
		if (containsOnlyLetters(miasto) == false || miasto.length() > 20 ||miasto.length()<2|| miasto.empty()) throw CustomException("Miasto zosta\210o niepoprawnie wpisane!");

		cout << "Podaj nazw\251 ulicy, na kt\242rej znajduje si\251 stacja: ";
		getline(cin, ulica);
		if (containsOnlyLetters(ulica) == false || 2>ulica.length() > 20 || ulica.empty()) throw CustomException("Ulica zosta\210 niepoprawnie wpisana!");

		cout << "Podaj numer lokalu: ";
		cin >> numerUl;
		if (is_digits(numerUl) == false|| numerUl.length()>3 || stod(numerUl)<=0) throw CustomException("Numer lokalu zosta\210 niepoprawnie wpisany! ");

		adres = miasto + ' ' + "ul." + ulica + ' ' + numerUl;

		cout << "Podaj nazw\251 stacji:";
		cin.ignore();
		getline(cin, nazwa);
		if (containsDigitsANDLetters(nazwa) == false||3>nazwa.length()>20||nazwa.empty()) throw CustomException("Nazwa zosta\210a niepoprawnie wpisana!");

		cout << "Podaj wysoko\230\206 ceny benzyny:";
		cin >> cenaBenzyny;
		CommaWithDot(cenaBenzyny);
		if (is_digits2(cenaBenzyny) == false||stod(cenaBenzyny)<=0||cenaBenzyny.length()>10) throw CustomException("Cena zosta\210a niepoprawnie wpisana!");
		
		cout << "Podaj wysoko\230\206 ceny oleju nap\251dowego:";
		cin >> cenaRopy;
		CommaWithDot(cenaRopy);
		if (is_digits2(cenaRopy) == false || stod(cenaRopy) <= 0 || cenaRopy.length() > 10) throw CustomException("Cena zosta\210a niepoprawnie wpisana!");

		
		cout << "Podaj wysoko\230\206 ceny gazu:";
		cin >> cenaGazu;
		CommaWithDot(cenaGazu);
		if (is_digits2(cenaGazu) == false || stod(cenaGazu) <= 0 || cenaGazu.length() > 10) throw CustomException("Cena zosta\210a niepoprawnie wpisana!");

		
		cout << "Podaj wysoko\230\206 zni\276ki:";
		cin >> znizka;
		CommaWithDot(znizka);
		if (is_digits2(znizka) == false || stod(znizka) < 0 || znizka.length() > 10||stod(znizka)>1) throw CustomException("Zni\276ka zosta\210a niepoprawnie wpisana!");

		

		StacjaPaliw* wskStacji = new StacjaPaliw(numer,nazwa, adres, stod(cenaBenzyny), stod(cenaRopy), stod(cenaGazu), stod(znizka));
		cout << "Czy chcesz zapisa\206 zmiany? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapStacji.insert(make_pair(numer, wskStacji));
			saveChanges();
			cout << "Dodano nowa stacje paliw. Naci\230nij dowolny klawisz, aby kontynuowa\206...";
		}
		else cout << "Nie zapisano zmian w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
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
	cout <<"\174"<< setw(spaceValue/3) << "Numer ID" << setw(2) << "|" << setw(spaceValue) << "Adres" << setw(2) << "|" << setw(spaceValue) << "Nazwa" << setw(2) << "|" << setw(spaceValue) << "Cena benzyny [z\210/l]" << setw(2) << "|" << setw(spaceValue) << "Cena diesla [z\210/l]" << setw(2) << "|" << setw(spaceValue) << "Cena gazu [z\210/l]" << setw(2) << "|" << setw(spaceValue) << "Wysoko\230\206 zni\276ki [*100%]" << setw(2) << "|" << endl;
	
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