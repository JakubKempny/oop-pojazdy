#include "Header.h"

void KontenerStacji::delRecord() {
	string id;
	cout << endl << "Usuwanie stacji, podaj ID: ";
	cin >> id;
	bool exist = false;
	try {
		for (auto i : mapStacji) {
			if (i.first == id) exist = true;
		}
		if (!exist) throw CustomException("Stacja o takim ID nie istnieje w bazie.");
		cout << "Czy napewno chcesz usunac stacje paliw z ID: " << id << "? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapStacji.erase(id);
			saveChanges();
			cout << "Stacja benzynowa z id: " << id << " zostala usunieta. " << "Nacisnij dowolny klawisz, aby kontynuowac...";
		}
		else cout << "Stacja nie zostala usunieta";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerStacji::addRecord() {
	string adres, nazwa, numer, miasto, ulica, numerUl, cenaBenzyny{}, cenaRopy{}, cenaGazu{}, znizka;
	cout << "\nDodawanie nowej stacji.\n";
	cout << "Podaj numer ID stacji: ";
	try {
		cin >> numer;
		for (auto i = mapStacji.begin(); i != mapStacji.end(); ++i) {
			if (is_digits(numer) == false)
			{
				throw CustomException("Numer zawiera niedozwolone znaki! ");
			}
			if (numer == i->first) throw CustomException("W bazie znajduje sie juz Stacja o podanym numerze! ");
		}
		cout << "Podaj miasto, w ktorym znajduje se stacja (2-20 znakow):";
		cin.ignore();
		getlineM(miasto);
		if (containsDigitsANDLetters(miasto) == false || miasto.length() > 20 || miasto.length() < 2) throw CustomException("Miasto zostalo niepoprawnie wpisane!");
		cout << "Podaj nazwe ulicy, na ktorej znajduje sie stacja (2-20 znakow): ";
		getlineM(ulica);
		if (containsDigitsANDLetters(ulica) == false || ulica.length() > 20 || ulica.length() < 2) throw CustomException("Ulica zostala niepoprawnie wpisana!");
		cout << "Podaj numer lokalu: ";
		getlineM(numerUl);
		if (is_digits(numerUl) == false || numerUl.length() > 3 || stod(numerUl) <= 0) throw CustomException("Numer lokalu zostal niepoprawnie wpisany! ");
		adres = miasto + ' ' + "ul." + ulica + ' ' + numerUl;
		cout << "Podaj nazwe stacji (3-20 znakow):";
		getlineM(nazwa);
		if (3 > nazwa.length() || nazwa.length() > 20) throw CustomException("Nazwa zostala niepoprawnie wpisana!");
		cout << "Podaj wysokosc ceny benzyny:";
		getlineM(cenaBenzyny);
		CommaWithDot(cenaBenzyny);
		if (is_digits2(cenaBenzyny) == false || stod(cenaBenzyny) <= 0 || cenaBenzyny.length() > 10 || checkMultipleDotsCommas(cenaBenzyny) == false) throw CustomException("Cena zostala niepoprawnie wpisana!");
		cout << "Podaj wysokosc ceny oleju napedowego:";
		getlineM(cenaRopy);
		CommaWithDot(cenaRopy);
		if (is_digits2(cenaRopy) == false || stod(cenaRopy) <= 0 || cenaRopy.length() > 10 || checkMultipleDotsCommas(cenaRopy) == false) throw CustomException("Cena zostala niepoprawnie wpisana!");
		cout << "Podaj wysokosc ceny gazu:";
		getlineM(cenaGazu);
		CommaWithDot(cenaGazu);
		if (is_digits2(cenaGazu) == false || stod(cenaGazu) <= 0 || cenaGazu.length() > 10 || checkMultipleDotsCommas(cenaGazu) == false) throw CustomException("Cena zostala niepoprawnie wpisana!");
		cout << "Podaj wysokosc znizki:";
		getlineM(znizka);
		CommaWithDot(znizka);
		if (is_digits2(znizka) == false || stod(znizka) > 1 || stod(znizka) < 0 || checkMultipleDotsCommas(znizka) == false) throw CustomException("Znizka zostala niepoprawnie wpisana!");
		StacjaPaliw* wskStacji = new StacjaPaliw(numer, nazwa, adres, stod(cenaBenzyny), stod(cenaRopy), stod(cenaGazu), stod(znizka));
		cout << "Czy chcesz zapisac zmiany? y/n: ";
		cin >> input;
		if (input == 'y') {
			mapStacji.insert(make_pair(numer, wskStacji));
			saveChanges();
			cout << "Dodano nowa stacje paliw. Nacisnij dowolny klawisz, aby kontynuowac...";
		}
		else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}

void KontenerStacji::createMapFromFile(vector<string> wiersze) {
	string nazwa, adres, numer;
	double cenaBenzyny, cenaGazu, cenaRopy, znizka;
	mapStacji.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, numer, ';');
		getline(ss, adres, ';');
		getline(ss, nazwa, ';');
		ss >> cenaBenzyny;
		ss.ignore();
		ss >> cenaRopy;
		ss.ignore();
		ss >> cenaGazu;
		ss.ignore();
		ss >> znizka;
		ss.ignore();
		StacjaPaliw* wskStacji = new StacjaPaliw(numer, nazwa, adres, cenaBenzyny, cenaRopy, cenaGazu, znizka);
		mapStacji.insert(make_pair(numer, wskStacji));
	}
}

void KontenerStacji::saveChanges() {
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

void KontenerStacji::info() {
	char z = '_';
	int spaceValue = 30;
	cout << "Dane z pliku: " << getPathToFile() << " : \n\n";
	cout << setfill(z) << setw(spaceValue * 6 + 7 * 2 + spaceValue / 3 + 1) << z << endl;
	cout.fill(' ');
	// wstawianie nazw kategorii
	cout << "\174" << setw(spaceValue / 3) << "Numer ID" << setw(2) << "|" << setw(spaceValue) << "Adres" << setw(2) << "|" << setw(spaceValue) << "Nazwa" << setw(2) << "|" << setw(spaceValue) << "Cena benzyny [zl/l]" << setw(2) << "|" << setw(spaceValue) << "Cena ropy [zl/l]" << setw(2) << "|" << setw(spaceValue) << "Cena gazu [zl/l]" << setw(2) << "|" << setw(spaceValue) << "Wysokosc znizki [*100%]" << setw(2) << "|" << endl;
	cout << setfill(z) << setw(spaceValue * 6 + 7 * 2 + spaceValue / 3 + 1) << z << endl;
	cout.fill(' ');
	for (auto i : mapStacji) {
		stringstream ss;
		ss << (i.second->formatDataToString());
		string tmp;
		cout << "|" << setw(spaceValue / 3) << i.first << setw(2);
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

void KontenerStacji::changeRecord() {
	string id;
	string cenaBenzyny{}, cenaRopy{}, cenaGazu{};
	StacjaPaliw* newGas;
	cout << endl << "Zmiana cen stacji, podaj ID: ";
	cin >> id;
	bool exist = false;
	try {
		for (auto i : mapStacji) {
			if (i.first == id) exist = true;
		}
		if (!exist) throw CustomException("Stacja o takim ID nie istnieje w bazie.");
		newGas = getStation(id);
		cout << "Podaj wysokosc ceny benzyny:";
		getlineM(cenaBenzyny);
		CommaWithDot(cenaBenzyny);
		if (is_digits2(cenaBenzyny) == false || stod(cenaBenzyny) <= 0 || cenaBenzyny.length() > 10 || checkMultipleDotsCommas(cenaBenzyny) == false) throw CustomException("Cena zostala niepoprawnie wpisana!");
		cout << "Podaj wysokosc ceny oleju napedowego:";
		getlineM(cenaRopy);
		CommaWithDot(cenaRopy);
		if (is_digits2(cenaRopy) == false || stod(cenaRopy) <= 0 || cenaRopy.length() > 10 || checkMultipleDotsCommas(cenaRopy) == false) throw CustomException("Cena zostala niepoprawnie wpisana!");
		cout << "Podaj wysokosc ceny gazu:";
		getlineM(cenaGazu);
		CommaWithDot(cenaGazu);
		if (is_digits2(cenaGazu) == false || stod(cenaGazu) <= 0 || cenaGazu.length() > 10 || checkMultipleDotsCommas(cenaGazu) == false) throw CustomException("Cena zostala niepoprawnie wpisana!");
		cout << "Czy napewno chcesz dokonac zmian w stacji paliw o ID: " << id << "? y/n: ";
		cin >> input;
		if (input == 'y') {
			//TUTAJ SOBIE PODMIENIA OBIEKT
			newGas = new StacjaPaliw(id, newGas->getFirma(), newGas->getName(), stod(cenaBenzyny), stod(cenaRopy), stod(cenaGazu), newGas->getDiscount());

			for (auto i : mapStacji) {
				if (i.first == id) {
					*i.second = *newGas;
				}
			}
			saveChanges();
			cout << "Stacja benzynowa z id: " << id << " zaaktualizowala ceny. " << "Nacisnij dowolny klawisz, aby kontynuowac...";
			delete newGas;
		}
		else cout << "Nie dokonano zmian.";
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
}