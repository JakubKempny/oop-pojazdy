#pragma once

#include <iostream>
#include <vector>
#include <map>

class Kontener {
	virtual void info() = 0;
};

class KontenerCar:Kontener {
	map<string, Car*> mapCar; // <nr Vim, wskaŸnik na Car>
	string pathToFile = "";
	char input{};
public:
	KontenerCar() {};
	KontenerCar(string s):pathToFile(s) {};
	~KontenerCar() {
		for (auto i:mapCar) {
			delete i.second;
		}
	}
	void createMapFromFile(vector<string> wiersze);
	void info() override;
	void addRecord();
	void delRecord(string plikKierowcy);
	void saveChanges(); // nadpisuje dane z pliku
	bool vinIstnieje(string vin);
	bool czyPrzypCar(string vin, string plikKierowcy);
	//get'ery
	Car* getCar(string c) { return mapCar.at(c); };
	string getPathToFile() { return pathToFile; }
};


class KontenerStanow :Kontener {
	map<string, Stanowisko*> mapStan; // <nazwaStanowiska, wskaznik na Stanowisko>
	string pathToFile = "";
	char input;
public:
	KontenerStanow() {};
	KontenerStanow(string s) : pathToFile(s) {};
	~KontenerStanow() {
		for (auto i : mapStan) {
			delete i.second;
		}
	}
	string getPathToFile() { return pathToFile; }
	void createMapFromFile(vector<string> wiersze);
	void info() override;  
	void addRecord();
	void delRecord(string plikKierowcy);
	void saveChanges();
	bool stanowIstnieje(string nazwa);
	bool czyPrzypStan(string nazwaStanow, string plikKierowcy);
	Stanowisko* getPosition(string c) { return mapStan.at(c); };
};

class KontenerKierow:Kontener {
	map<string, Pracownik*> mapPrac; // <nr pesel, wskaznik na Pracownik>
	string pathToFile = "";
	char input;
public:
	KontenerKierow() {};
	KontenerKierow(string s) : pathToFile(s) {};
	~KontenerKierow() {
		for (auto i : mapPrac) {
			delete i.second;
		}
	}
	void createMapFromFile(vector<string> wiersze);
	void info() override; 
	void addRecord(KontenerCar& k, KontenerStanow& stan);
	void delRecord();
	void saveChanges();
	bool vinWolny(string vin);
	map<string, Pracownik*> getMap() { return mapPrac; }
	Pracownik* getWorker(string c) { return mapPrac.at(c); };
	string getPathToFile() { return pathToFile; }
};


class KontenerStacji :Kontener {

	map<string, StacjaPaliw*> mapStacji; // numer ID, wskaznik na Stacje
	string pathToFile = "";
	char input;
public:
	KontenerStacji() {};
	KontenerStacji(string s) : pathToFile(s) {};
	~KontenerStacji() {
		for (auto i : mapStacji) {
			delete i.second;
		}
	}
	void createMapFromFile(vector<string> wiersze);
	void info() override;
	void addRecord();
	void delRecord();
	void saveChanges();
	void changeRecord();
	map<string, StacjaPaliw*> getMap() { return mapStacji; }
	StacjaPaliw* getStation(string c) { return mapStacji.at(c); };
	string getPathToFile() { return pathToFile; }
};