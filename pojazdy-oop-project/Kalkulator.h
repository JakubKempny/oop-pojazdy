#pragma once

class Kalkulator
{
	vector<pair<string, int>> assignedWorkers; //ten wektor bedzie przechowywal pracownikow przypisanych do konkretnej stacji: para to pesel pracownika(czyli string) i id stacji(czyli int)
	KontenerCar car;
	KontenerKierow driver;
	KontenerStacji gasStation; 
	KontenerStanow level;
	vector<string> drivers;
public:
	Kalkulator(KontenerCar car, KontenerKierow driver, KontenerStacji gasStation, KontenerStanow level);
	void computeEngine(); // glowna funkcja do liczenia tego wszystkiego i polaczenia w calosc 
	double fuelConsumption(string VIN); // funkcja poboczna do obliczania spalania (20 dni) dla konkretnego pracownika (podajemy VIN jego samochodu jako argument)
};