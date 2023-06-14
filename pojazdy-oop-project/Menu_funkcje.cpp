#include "Header.h"

void Menu::calc() {
	system("CLS");
	showHeader();
	Kalkulator kalk1(konCar, konKier, konStacji, konStanow);
	kalk1.computeEngine();
	cout << endl << "Kliknij dowolny klawisz, aby wrocic do menu... ";
	system("pause > nul");
	showMenu();
}

Menu::Menu(KontenerCar& konCar, KontenerKierow& konKier, KontenerStacji& konStacji, KontenerStanow& konStanow) {
	this->konCar = konCar;
	this->konKier = konKier;
	this->konStacji = konStacji;
	this->konStanow = konStanow;
}

void Menu::showMenu() {
	createMaps();
	showText();
	do {
		this->input = _getch();
	} while ((input != '1') && (input != '2') && (input != '3') && (input != '4') && (input != '5') && (input != '6'));

	switch ((int)input - 48) {
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

void Menu::showText() {
	system("CLS");
	showHeader();
	cout << " Witaj w kalkulatorze paliw! \n";
	cout << " 1: Kalkulator paliwa" << endl;
	cout << " 2: Baza pracownicy" << endl;
	cout << " 3: Baza pojazdy" << endl;
	cout << " 4: Baza stacje paliw" << endl;
	cout << " 5: Baza stanowiska" << endl;
	cout << " 6: Wyjdz z programu" << endl;
	cout << " Twoj wybor: ";
}

void Menu::showHeader() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);
	cout << endl;
	cout << "  PPPPPP      AAAA     LL         II   WW      WW    EEEEEEE   XX    XX " << endl;
	cout << " PP    PP    AA  AA    LL         II   WW  WW  WW   EE          XX  XX  " << endl;
	cout << " PPPPPPP    AAAAAAAA   LL         II   WW WWWW WW   EEEEEEEE      XX    " << endl;
	cout << " PP         AA    AA   LL         II   WWWW  WWWW   EE          XX  XX  " << endl;
	cout << " PP         AA    AA   LLLLLLLL   II   WW      WW    EEEEEEE   XX    XX " << endl << endl << endl;
	SetConsoleTextAttribute(h, 15);
}

bool Menu::createMaps() {
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

void Menu::baseCars() {
	system("CLS");
	konCar.info();
	cout << "\nDodaj/usun samochod (a/d/q)";
	do {
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input) {
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

void Menu::baseDrivers() {
	system("CLS");
	konKier.info();
	cout << "\nDodaj/usun pracownika (a/d/q)";
	do {
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input) {
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

void Menu::baseLevels() {
	system("CLS");
	konStanow.info();
	cout << "\nDodaj/usun stanowisko (a/d/q)";
	do {
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q'));
	switch (input) {
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

void Menu::baseGasStations() {
	system("CLS");
	konStacji.info();
	cout << "\nDodaj/usun/zmien_ceny/wyjdz (a/d/c/q)";
	do {
		this->input = _getch();
	} while ((input != 'a') && (input != 'd') && (input != 'q') && (input != 'c'));
	switch (input) {
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
	case 'c':
		konStacji.changeRecord();
		system("pause > nul");
		baseGasStations();
		break;
	case 'q':
		showMenu();
		break;
	}
}
