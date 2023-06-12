#pragma once

class Menu
{
private:
	char input{}; //zmienna do wybierania opcji w menu 1-5 i a/d/q
protected:
	KontenerCar konCar;
	KontenerKierow konKier;
	KontenerStacji konStacji;
	KontenerStanow konStanow;
public:
	Menu() {};
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
	//void addLevel();
	//void delLevel();
	void addPetrol();
	void delPetrol();

	void calc();
};

