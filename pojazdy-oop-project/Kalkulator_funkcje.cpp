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

double Kalkulator::workerPositionContribution(string position)
{
	pos1 = level.getPosition(position);
	return pos1->getContribution();
}

double Kalkulator::afterDiscount(string GasStationID, double price)
{
	gas1 = gasStation.getStation(GasStationID);
	double discount = gas1->getDiscount();
	double result = price - (discount * price);
	return result;
}

string Kalkulator::gasStationName(string GasStationID)
{
	gas1 = gasStation.getStation(GasStationID);
	return gas1->getName();
}

double Kalkulator::companyCost(double price, double contribution)
{
	return price * contribution;
}

void Kalkulator::discountCheck(double discountPrice, double fullPrice)
{
	if (fullPrice == discountPrice) {
		cout << "BRAK RABATU";
	}
	else cout << discountPrice;
}

void Kalkulator::bestStation(double consumption, string fuelType, string position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //bajery do zmiany kolorow 

	prices.clear(); // czyszcze wektor z danych poprzedniego pracownika
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
		gas1 = gasStation.getStation(idStacji);
		prices.push_back(make_pair((gas1->getFuelCost(fuelType) * consumption), idStacji));
	}
	sort(prices.begin(), prices.end()); //sortuje wektor par
	double fullPrice = prices[0].first; //wybieramy sobie najmniejszy element (cena bez obnizek)
	string station = prices[0].second;  //wybieramy sobie najmniejszy element (ID stacji)
	double discountPrice = afterDiscount(station, fullPrice);
	double realPrice = companyCost(discountPrice, workerPositionContribution(position));
	cout << fixed << setprecision(2);

	//TUTAJ WYSWIETLA CALA RESZTE XD
	cout << gasStationName(station) << "   ";
	SetConsoleTextAttribute(hConsole, 4);
	cout << fullPrice << "   ";
	SetConsoleTextAttribute(hConsole, 6);
	discountCheck(discountPrice, fullPrice);
	SetConsoleTextAttribute(hConsole, 2);
	cout << "   " << realPrice << endl;
	SetConsoleTextAttribute(hConsole, 7);
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
	string position{};
	//TUTAJ SA KOLUMNY
	cout << "Imie i Nazwisko |  Stanowisko  |  Spalanie (miesieczne)  |  Najtansza stacja  |  Calkowity Koszt  |  Z rabatem stacji  |  Koszt firmy  |" << endl;
	for (int i = 0; i < map.size(); i++)
	{
		idPrac = drivers.at(i);
		prac1 = driver.getWorker(idPrac);

		vin = prac1->getDriverVin();
		dystans = prac1->getDystans();
		surname = prac1->getNameSurname();
		position = prac1->getPosition();
		//TUTAJ WYSWIETLA IMIE, NAZWISKO, POZYCJE I SPALANIE
		cout << surname << "   " << position << "   " << fuelConsumption(vin, dystans) << "   ";
		bestStation(fuelConsumption(vin, dystans), fuelType(vin), position);
	}
}