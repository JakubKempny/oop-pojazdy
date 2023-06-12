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
		calc();
		break;
	case 2:
		baseDrivers();
		break;
	case 3:
		baseCars();
		break;
	case 4:
		baseGasStations();
		break;
	case 5:
		baseLevels();
		break;
	case 6:
		exit(0);
		break;
	}
}

void Menu::calc()
{
	system("CLS");
	Kalkulator kalk1(konCar,konKier,konStacji,konStanow);
	kalk1.computeEngine();
	cout << endl << "Kliknij dowolny klawisz, aby wr\242ci\206 do menu... ";
	system("pause > nul");
	showMenu();
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
	cout << "6: Wyjd\253 z programu" << endl;
	cout << "Tw\242j wyb\242r: ";
}

void Menu::addCar()
{
	cout << endl << "Dodawanie nowego samoch\242du: " << endl;
	konCar.addRecord();
	cout <<  "Czy chcesz zapisa\206 zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konCar.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	} else cout << "Nie zapisano zmian w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
}

void Menu::delCar()
{
	string vin{};
	string plik{};
	cout << endl << "Usuwanie samochodu, podaj jego numer VIN: " << endl;
	cin >> vin;
	cout << "Czy napewno chcesz usun\245\206 pojazd o numerze VIN: " << vin << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		plik = konKier.getPathToFile();
		konCar.delRecord(vin,plik);
		konCar.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	} else cout << "Pojazd nie zosta\210 usuni\251ty";
}

void Menu::addDriver()
{
	cout << endl << "Dodawanie nowego pracownika: " << endl;
	konKier.addRecord(konCar, konStanow);
	cout << "Czy chcesz zapisa\206 zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konKier.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	} else cout << "Nie zapisano zmian w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
}

void Menu::delDriver()
{
	string pesel{};
	cout << endl << "Usuwanie pracownika, podaj jego pesel: " << endl;
	cin >> pesel;
	cout << "Czy napewno chcesz usun\245\206 pracownika o numerze PESEL: " << pesel << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		konKier.delRecord(pesel);
		konKier.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	} else cout << "Uzytkownik nie zosta\210 usuni\251ty";
}

void Menu::addLevel()
{
	cout << endl << "Dodawanie nowego stanowiska: " << endl;
	konStanow.addRecord();
	cout << "Czy chcesz zapisa\206 zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konStanow.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	}
	else cout << "Nie zapisano zmian w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
}

void Menu::delLevel()
{
	string nazwa{};
	string plik{};
	cout << endl << "Usuwanie stanowiska, podaj jego nazwe\251: " << endl;
	cin >> nazwa;
	cout << "Czy napewno chcesz usun\245\206 stanowisko o nazwie: " << nazwa << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		plik = konKier.getPathToFile();
		konStanow.delRecord(nazwa, plik);
		konStanow.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	}
	else cout << "Stanowisko nie zostalo usuni\251te";
}


void Menu::addPetrol()
{
	cout << endl << "Dodawanie nowej stacji: " << endl;
	konStacji.addRecord();
	cout << "Czy chcesz zapisa\206 zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konStacji.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	}
	else cout << "Nie zapisano zmian w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
}

void Menu::delPetrol()
{
	string id;
	cout << endl << "Usuwanie stacji, podaj ID: ";
	cin >> id;
	cout << "Czy napewno chcesz usun\245\206 stacje paliw z ID: " << id << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		konStacji.delRecord(id);
		konStacji.saveChanges();
		cout << "Zapisano zmiany w bazie! Naci\230nij dowolny klawisz, aby kontynuowa\206...";
	}
	else cout << "Stacja nie zosta\210a usuni\251ta";
}

bool Menu::createMaps() 
{
	try {
		vector<string> lineCars = wczytajPlik(konCar.getPathToFile());
		konCar.createMapFromFile(lineCars);
		vector<string> lineDrivers = wczytajPlik(konKier.getPathToFile());
		konKier.createMapFromFile(lineDrivers);
		vector<string> lineGasStations = wczytajPlik(konStacji.getPathToFile());
		konStacji.createMapFromFile(lineGasStations);
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
	cout << "Dodaj/usu\344 samoch\242d (a/d/q)";
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
	cout << "Dodaj/usu\344 pracownika (a/d/q)";
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
	cout << "Dodaj/usu\344 stanowisko (a/d/q)";
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

void Menu::baseGasStations()
{
	system("CLS");
	konStacji.info();
	cout << "Dodaj/usu\344 stacje paliw (a/d/q)";
	do
	{
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input)
	{
	case 'a':
		addPetrol();
		system("pause > nul");
		baseGasStations();
		break;
	case 'd':
		delPetrol();
		system("pause > nul");
		baseGasStations();
		break;
	case 'q':
		showMenu();
		break;
	}
}
