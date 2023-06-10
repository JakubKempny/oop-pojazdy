#include "Header.h"
#include <conio.h>

Menu::Menu(KontenerCar &konCar, KontenerKierow &konKier)
{
	this->konCar = konCar;
	this->konKier = konKier;
}

void Menu::showMenu()
{
	createMaps();
	showText();
	do
	{
		this->input = _getch();
	} while ((input != '1') && (input != '2') && (input != '3') && (input != '4') && (input != '5'));

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
	cout << "5: Wyjdz z programu" << endl;
	cout << "Twoj wybor: ";
}

string Menu::addCar()
{
	cout << endl << "Dodawanie nowego samochodu: " << endl;
	konCar.addRecord();
	cout <<  "Czy chcesz zapisac zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konCar.saveChanges();
		return "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	return "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
}

string Menu::delCar()
{
	string vin{};
	cout << endl << "Usuwanie samochodu, podaj jego numer VIN: " << endl;
	cin >> vin;
	cout << "Czy napewno chcesz usunac pojazd o numerze VIN: " << vin << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		konCar.delRecord(vin);
		konCar.saveChanges();
		return "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	return "Uzytkownik nie zostal usuniety";
}

string Menu::addDriver()
{
	cout << endl << "Dodawanie nowego pracownika: " << endl;
	konKier.addRecord(konCar);
	cout << "Czy chcesz zapisac zmiany? y/n: ";
	cin >> input;
	if (input == 'y') {
		konKier.saveChanges();
		return "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	} 
	return "Nie zapisano zmian w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
}

string Menu::delDriver()
{
	string pesel{};
	cout << endl << "Usuwanie pracownika, podaj jego pesel: " << endl;
	cin >> pesel;
	cout << "Czy napewno chcesz usunac pracownika o numerze PESEL: " << pesel << "? y/n: ";
	cin >> input;
	if (input == 'y') {
		konKier.delRecord(pesel);
		konKier.saveChanges();
		return "Zapisano zmiany w bazie! Nacisnij dowolny klawisz, aby kontynuowac...";
	}
	return "Uzytkownik nie zostal usuniety";
}

bool Menu::createMaps() 
{
	try {
		vector<string> lineCars = wczytajPlik(konCar.getPathToFile());
		konCar.createMapFromFile(lineCars);
		vector<string> lineDrivers = wczytajPlik(konKier.getPathToFile());
		konKier.createMapFromFile(lineDrivers);
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
		cout << addCar();
		system("pause > nul"); // czeka na dowolny przycisk od uzytkownika zeby kontynuwac
		baseCars(); //uruchamia sie jeszcze raz zeby aktualizowac baze
		break;
	case 'd':
		cout << delCar();
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
		cout << addDriver();
		system("pause > nul");
		baseDrivers(); 
		break;
	case 'd':
		cout << delDriver();
		system("pause > nul");
		baseDrivers();
		break;
	case 'q':
		showMenu();
		break;
	}
}