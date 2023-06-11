#pragma once

class Menu
{
	char input{}; //zmienna do wybierania opcji w menu 1-5 i a/d/q
	KontenerCar konCar;
	KontenerKierow konKier;
	KontenerStacji konStacji;
	KontenerStanow konStanow;
public:
	Menu(KontenerCar& konCar, KontenerKierow& konKier, KontenerStacji &konStacji, KontenerStanow &konStanow);
	void showText();
	void showMenu();
	void baseCars();
	void baseDrivers();
	void baseLevels();
	void baseGasStations();
	bool createMaps();
	void addCar();
	void delCar();
	void addDriver();
	void delDriver();
	void addLevel();
	void delLevel();
	void addPetrol();
	void delPetrol();
};
