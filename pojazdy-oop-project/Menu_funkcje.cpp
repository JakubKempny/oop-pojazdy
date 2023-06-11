#include "Header.h"
#include <conio.h>

Menu::Menu(KontenerCar& konCar, KontenerKierow& konKier, KontenerStacji& konStacji, KontenerStanow& konStanow)
{
	this->konCar = konCar;
	this->konKier = konKier;
	this->konStacji = konStacji;
	this->konStanow = konStanow;
}

void Menu::showMenu()
{
	createMaps();
	showText();
	do
	{
		this->input = _getch();
	} while ((input != '1') && (input != '2') && (input != '3') && (input != '4') && (input != '5') && (input != '6'));

	switch ((int)input - 48)
	{
	case 1:
		cout << "Wybrales 1";
		break;
	case 2:
		baseDrivers();
		break;
	case 3:
		baseCars();
		break;
	case 4:
		cout << "Wybrales 4";
		break;
	case 5:
		baseLevels();
		break;
	case 6:
		exit(0);
		break;
	}
}

void Menu::showText()
{
	system("CLS");
	cout << "Witaj w kalkulatorze paliw v.2137! \n";
	cout << "1: Kalkulator paliwa" << endl;
	cout << "2: Baza pracownicy" << endl;
	cout << "3: Baza pojazdy" << endl;
	cout << "4: Baza stacje paliw" << endl;
	cout << "5: Baza stanowiska" << endl;
	cout << "6: Wyjdz z programu" << endl;
	cout << "Twoj wybor: ";
}

void Menu::addCar()
{
	cout << endl << "Dodawanie nowego samochodu: " << endl;
	konCar.addRecord();
	cout <<  "Czy chcesz zapisac zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konCar.saveChanges();
		cout << "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	} else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
}

void Menu::delCar()
{
	string vin{};
	cout << endl << "Usuwanie samochodu, podaj jego numer VIN: " << endl;
	cin >> vin;
	cout << "Czy napewno chcesz usunac pojazd o numerze VIN: " << vin << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		konCar.delRecord(vin);
		konCar.saveChanges();
		cout << "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	} else cout << "Pojazd nie zostal usuniety";
}

void Menu::addDriver()
{
	cout << endl << "Dodawanie nowego pracownika: " << endl;
	konKier.addRecord(konCar, konStanow);
	cout << "Czy chcesz zapisac zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konKier.saveChanges();
		cout << "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	} else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
}

void Menu::delDriver()
{
	string pesel{};
	cout << endl << "Usuwanie pracownika, podaj jego pesel: " << endl;
	cin >> pesel;
	cout << "Czy napewno chcesz usunac pracownika o numerze PESEL: " << pesel << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		konKier.delRecord(pesel);
		konKier.saveChanges();
		cout << "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	} else cout << "Uzytkownik nie zostal usuniety";
}

void Menu::addLevel()
{
	cout << endl << "Dodawanie nowego stanowiska: " << endl;
	konStanow.addRecord();
	cout << "Czy chcesz zapisac zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konStanow.saveChanges();
		cout << "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	else cout << "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
}

void Menu::delLevel()
{
	string nazwa{};
	string plik{};
	cout << endl << "Usuwanie stanowiska, podaj jego nazwe: " << endl;
	cin >> nazwa;
	cout << "Czy napewno chcesz usunac stanowisko o nazwie: " << nazwa << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		plik = konKier.getPathToFile();
		konStanow.delRecord(nazwa, plik);
		konStanow.saveChanges();
		cout << "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	else cout << "Stanowisko nie zostalo usuniete";
}

bool Menu::createMaps() 
{
	try {
		vector<string> lineCars = wczytajPlik(konCar.getPathToFile());
		konCar.createMapFromFile(lineCars);
		vector<string> lineDrivers = wczytajPlik(konKier.getPathToFile());
		konKier.createMapFromFile(lineDrivers);
		/*vector<string> lineGasStations = wczytajPlik(konStacji.getPathToFile()); //Na razie nie dzialaja te stacje paliw 
		konStacji.createMapFromFile(lineGasStations);*/ 
		vector<string> lineLevel = wczytajPlik(konStanow.getPathToFile());
		konStanow.createMapFromFile(lineLevel);
	}
	catch (CustomException& e) {
		cerr << e.what() << endl;
	}
	return true;
}

void Menu::baseCars()
{
	system("CLS");
	konCar.info();
	cout << "Dodaj/usun auto (a/d/q)";
	do
	{
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input)
	{
	case 'a':
		addCar();
		system("pause > nul"); // czeka na dowolny przycisk od uzytkownika zeby kontynuwac
		baseCars(); //uruchamia sie jeszcze raz zeby aktualizowac baze
		break;
	case 'd':
		delCar();
		system("pause > nul"); 
		baseCars();
		break;
	case 'q':
		showMenu();
		break;
	}
}

void Menu::baseDrivers()
{
	system("CLS");
	konKier.info();
	cout << "Dodaj/usun pracownika (a/d/q)";
	do
	{
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input)
	{
	case 'a':
		addDriver();
		system("pause > nul");
		baseDrivers(); 
		break;
	case 'd':
		delDriver();
		system("pause > nul");
		baseDrivers();
		break;
	case 'q':
		showMenu();
		break;
	}
}

void Menu::baseLevels()
{
	system("CLS");
	konStanow.info();
	cout << "Dodaj/usun stanowisko (a/d/q)";
	do
	{
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input)
	{
	case 'a':
		addLevel();
		system("pause > nul");
		baseLevels();
		break;
	case 'd':
		delLevel();
		system("pause > nul");
		baseLevels();
		break;
	case 'q':
		showMenu();
		break;
	}
}
//string Menu::addPetrol()
//{
//	cout << endl << "Dodawanie nowej stacji: " << endl;
//	konStacji.addRecord();
//	konStacji.saveChanges();
//
//	return "Zmiany zosta\210y zapisane!\n";
//}
//
//string Menu::delPetrol()
//{
//	string adres{};
//	cout << endl << "Usuwanie stacji, podaj adres: " << endl;
//	cin >> adres;
//	konKier.delRecord(adres);
//	konKier.saveChanges();
//
//	return "Zmiany zosta\210y zapisane!\n";
//}