#include "Header.h"
#include "Funkcje.cpp"

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

void KontenerStacji::addRecord()
{
	string adres, nazwa;
	string cenaBenzynyStr{}, cenaRopyStr{}, cenaGazuStr{}, znizkaStr;
	string e;
	cout << "Podaj adres stacji:";
	try
	{
		getline(cin, adres);
		for (auto i = mapStacji.begin(); i != mapStacji.end(); ++i) {
			if (adres == i->first) throw CustomException("W bazie znajduje si\251 ju\276 Stacja o podanym adresie! ");
		}
		cout << "Podaj nazw\251 stacji:";
		cin >> nazwa;
		if (containsDigitsANDLetters(nazwa) == false) throw CustomException("Nazwa zawiera niedozwolone znaki! ");

		cout << "Podaj wysoko\230\206 ceny benzyny:";
		cin >> cenaBenzynyStr;
		if (is_digits2(cenaBenzynyStr) == false) throw CustomException("Cena zawiera niedozwolone znaki! ");
		double cenaBenzyny = stod(cenaBenzynyStr);
		cout << "Podaj wysoko\230\206 ceny oleju nap\251dowego:";
		cin >> cenaRopyStr;
		if (is_digits2(cenaRopyStr) == false) throw CustomException("Cena zawiera niedozwolone znaki! ");
		double cenaRopy = stod(cenaRopyStr);
		cout << "Podaj wysoko\230\206 ceny gazu:";
		cin >> cenaGazuStr;
		if (is_digits2(cenaGazuStr) == false) throw CustomException("Cena zawiera niedozwolone znaki! ");
		double cenaGazu = stod(cenaGazuStr);
		cout << "Podaj wysoko\230\206 zni\276ki:";
		cin >> znizkaStr;
		if (is_digits2(znizkaStr) == false) throw CustomException("Zni\276ka zawiera niedozwolone znaki! ");
		double znizka = stod(znizkaStr);

		Ceny* newCeny = new Ceny(cenaBenzyny, cenaRopy, cenaGazu);
		StacjaPaliw* wskStacji = new StacjaPaliw(nazwa, adres, newCeny, znizka);
		mapStacji.insert(make_pair(adres, wskStacji));
		cout << "Dodano now\245 stacj\251. Aby zmiana byla trwala zapisz zmiany." << endl;
	}
	catch (CustomException& e)
	{
		cout << e.what() << endl;
	}
}

void KontenerStacji::createMapFromFile(vector<string> wiersze) {
	string nazwa, adres, cenaBenzynyStr, cenaGazuStr, cenaRopyStr, znizkaStr;


	mapStacji.clear();
	for (int i = 0; i < wiersze.size(); ++i) {
		stringstream ss(wiersze[i]);
		getline(ss, nazwa, ';');
		getline(ss, adres, ';');
		getline(ss, cenaBenzynyStr, ';');
		double cenaBenzyny = stod(znizkaStr);  //zmiana stringa na doubla
		getline(ss, cenaRopyStr, ';');
		double cenaRopy = stod(cenaRopyStr);
		getline(ss, cenaGazuStr, ';');
		double cenaGazu = stod(cenaGazuStr);
		getline(ss, znizkaStr, ';');
		double znizka = stod(znizkaStr);

		Ceny* cena1 = new Ceny(cenaBenzyny, cenaRopy, cenaGazu);
		// tu jescze ten wektor na pesel ale to nw jak siê tym ob³ugiwaæ

		StacjaPaliw* wskStacji = new StacjaPaliw(nazwa, adres, cena1, znizka);
		mapStacji.insert(make_pair(adres, wskStacji));
	}
}
