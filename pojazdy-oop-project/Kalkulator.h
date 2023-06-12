#pragma once

class Kalkulator
{
	vector<pair<double, string>> prices; //ten wektor przechowuje pod double - cene paliwa, pod stringiem id stacji benzynowej na ktorej tylko kosztuje
	KontenerCar car;
	KontenerKierow driver;
	KontenerStacji gasStation; 
	KontenerStanow level;
	vector<string> drivers; 
	vector<string> gasStations;
	Car* car1;
	Pracownik* prac;
	StacjaPaliw* gas;
public:
	Kalkulator(KontenerCar& car, KontenerKierow& driver, KontenerStacji& gasStation, KontenerStanow& level);
	void computeEngine(); // glowna funkcja do liczenia tego wszystkiego i polaczenia w calosc 
	double fuelConsumption(string VIN, double dystans); // funkcja poboczna do obliczania spalania (20 dni) dla konkretnego pracownika (podajemy VIN jego samochodu jako argument)
	string bestStation(double consumption, string fuelType);
	string fuelType(string VIN);
};