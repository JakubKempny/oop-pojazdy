#include "Header.h"
#include <conio.h>

void Menu::calc()
{
	system("CLS");
	Kalkulator kalk1(konCar, konKier, konStacji, konStanow);
	kalk1.computeEngine();
	cout << endl << "Kliknij dowolny klawisz, aby wrocic do menu... ";
	system("pause > nul");
	showMenu();
}

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

void Menu::showText()
{
	system("CLS");
	cout << "Witaj w kalkulatorze paliw! \n";
	cout << "1: Kalkulator paliwa" << endl;
	cout << "2: Baza pracownicy" << endl;
	cout << "3: Baza pojazdy" << endl;
	cout << "4: Baza stacje paliw" << endl;
	cout << "5: Baza stanowiska" << endl;
	cout << "6: Wyjd\253 z programu" << endl;
	cout << "Twoj wybor: ";
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
	cout << "Dodaj/usun samochod (a/d/q)";
	do
	{
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input)
	{
	case 'a':
		konCar.addRecord();
		system("pause > nul"); // czeka na dowolny przycisk od uzytkownika zeby kontynuwac
		baseCars(); //uruchamia sie jeszcze raz zeby aktualizowac baze
		break;
	case 'd':
		konCar.delRecord(konKier.getPathToFile());
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
		konKier.addRecord(konCar, konStanow);
		system("pause > nul");
		baseDrivers(); 
		break;
	case 'd':
		konKier.delRecord();
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
		konStanow.addRecord();
		system("pause > nul");
		baseLevels();
		break;
	case 'd':
		konStanow.delRecord(konKier.getPathToFile());
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
	cout << "Dodaj/usun stacje paliw (a/d/q)";
	do
	{
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input)
	{
	case 'a':
		konStacji.addRecord();
		system("pause > nul");
		baseGasStations();
		break;
	case 'd':
		konStacji.delRecord();
		system("pause > nul");
		baseGasStations();
		break;
	case 'q':
		showMenu();
		break;
	}
}
