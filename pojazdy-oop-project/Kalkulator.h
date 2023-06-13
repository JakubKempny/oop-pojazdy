#pragma once

class Kalkulator
{
	char input{};
	string pesel{};
	vector<pair<double, string>> prices; //ten wektor przechowuje pod double - cene paliwa, pod stringiem id stacji benzynowej na ktorej tylko kosztuje
	KontenerCar car;
	KontenerKierow driver;
	KontenerStacji gasStation; 
	KontenerStanow level;
	vector<string> drivers; 
	vector<string> gasStations;
	Car* car1;
	Pracownik* prac1;
	StacjaPaliw* gas1;
	Stanowisko* pos1;
public:
	Kalkulator(KontenerCar& car, KontenerKierow& driver, KontenerStacji& gasStation, KontenerStanow& level);
	void computeEngine(); // glowna funkcja do liczenia tego wszystkiego i polaczenia w calosc 
	double fuelConsumption(string VIN, double dystans); // funkcja poboczna do obliczania spalania (20 dni) dla konkretnego pracownika (podajemy VIN jego samochodu jako argument)
	void bestStation(double consumption, string fuelType, string position);
	string fuelType(string VIN);
	double afterDiscount(string GasStationID, double price);
	string gasStationName(string GasStationID);
	double workerPositionContribution(string position);
	double companyCost(double price, double contribution);
	void discountCheck(double discountPrice, double fullPrice);
	void count(int i);
};