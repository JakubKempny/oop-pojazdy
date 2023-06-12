#include "Header.h"

Kalkulator::Kalkulator(KontenerCar car, KontenerKierow driver, KontenerStacji gasStation, KontenerStanow level)
{
	this->car = car;
	this->driver = driver;
	this->gasStation = gasStation;
	this->level = level;
}

double Kalkulator::fuelConsumption(string idPrac)
{
	return 0;
}

void Kalkulator::computeEngine()
{
	// potem nalezy tez sprawdzic czy plik z pracownikami lub stacjami nie jest pusty


	//wrzucam pesele pracownikow do wektorka
	map<string, Pracownik*> map = driver.getMap();
	drivers.reserve(map.size()); //rezerwacja pamieci dla wektora
	for (auto const& keyMap : map)
	{
		drivers.push_back(keyMap.first);
	}
	string idPrac{};
	for (int i = 0; i < map.size(); i++)
	{
		idPrac = drivers.at(i);
		cout << "Dla pracownika: " << idPrac << " spalanie wynosi: " << fuelConsumption(idPrac) << endl;
	}
}