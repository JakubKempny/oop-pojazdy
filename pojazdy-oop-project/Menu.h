#pragma once

class Menu
{
	char input{}; //zmienna do wybierania opcji w menu 1-5 i a/d/q
	KontenerCar konCar;
	KontenerKierow konKier;
	KontenerStacji konStacji;
public:
	Menu(KontenerCar& konCar, KontenerKierow& konKier);
	void showText();
	void showMenu();
	void baseCars();
	void baseDrivers();
	string addCar();
	string delCar();
	string addDriver();
	string delDriver();
	string addPetrol();
	string delPetrol();
};
