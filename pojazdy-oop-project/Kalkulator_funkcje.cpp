#include "Header.h"
#include <algorithm>
Kalkulator::Kalkulator(KontenerCar& car, KontenerKierow& driver, KontenerStacji& gasStation, KontenerStanow& level)
{
	this->car = car;
	this->driver = driver;
	this->gasStation = gasStation;
	this->level = level;
}

double Kalkulator::fuelConsumption(string VIN, double dystans)
{
	car1 = car.getCar(VIN);
	return car1->oblZurzycie(dystans)*20;
}

string Kalkulator::fuelType(string VIN)
{
	car1 = car.getCar(VIN);
	return car1->getRodzPaliwa();
}

string Kalkulator::bestStation(double consumption, string fuelType)
{
	//wrzucenie stacji paliw do wektora
	map<string, StacjaPaliw*> map = gasStation.getMap();
	gasStations.reserve(map.size());
	for (auto const& keyMap : map)
	{
		gasStations.push_back(keyMap.first);
	}

	string idStacji{};
	for (int i = 0; i < map.size(); i++)
	{

		idStacji = gasStations.at(i);
		gas = gasStation.getWorker(idStacji);
		cout << gas->getFuelCost(fuelType);
		//cout << "ID STACIJ: " << idStacji << "; " << gas->getFuelCost(fuelType) * consumption << ": ";
		prices.push_back(make_pair((gas->getFuelCost(fuelType) * consumption), idStacji));
	}
	sort(prices.begin(), prices.end()); //sortuje wektor par
	double price = prices[0].first; //wybieramy sobie najmniejszy element (cena)
	string station = prices[0].second;  //wybieramy sobie najmniejszy element (ID stacji)
	gas = gasStation.getWorker(station);
	string name = gas->getName();
	return  "Calkowity koszt: " + to_string(price) + " dla stacji: " + name;
}

void Kalkulator::computeEngine()
{
	// potem nalezy tez sprawdzic czy plik z pracownikami lub stacjami nie jest pusty

	//wrzucam pesele pracownikow do wektora
	map<string, Pracownik*> map = driver.getMap();
	drivers.reserve(map.size()); //rezerwacja pamieci dla wektora
	for (auto const& keyMap : map)
	{
		drivers.push_back(keyMap.first);
	}
	string idPrac{};
	string vin{};
	double dystans{};
	string surname{};
	for (int i = 0; i < map.size(); i++)
	{

		idPrac = drivers.at(i);
		prac = driver.getWorker(idPrac);
		vin = prac->getDriverVin();
		dystans = prac->getDystans();
		surname = prac->getNameSurname();
		cout << "Miesiecznie dla pracownika : " << surname << " spalanie wynosi: " << fuelConsumption(vin, dystans) << "  ";
		cout << bestStation(fuelConsumption(vin, dystans), fuelType(vin)) << endl;
	}
}