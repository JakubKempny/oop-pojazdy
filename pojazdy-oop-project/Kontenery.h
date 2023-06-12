#pragma once

class Kontener {
	virtual void info() = 0;
};

class KontenerCar:Kontener {
	map<string, Car*> mapCar; // <nr Vim, wskaünik na Car>
	string pathToFile = "";
public:
	KontenerCar() {};
	KontenerCar(string s):pathToFile(s) {};
	~KontenerCar() {
		for (auto i:mapCar) {
			delete i.second;
		}
	}
	string getPathToFile() { return pathToFile; }
	void createMapFromFile(vector<string> wiersze);
	void info() override;
	void addRecord();
	void delRecord(string plikKierowcy);
	void saveChanges(); // nadpisuje dane z pliku
	//get'ery
	Car* getCar(string c) { return mapCar.at(c); };

	bool vinIstnieje(string vin);
	bool czyPrzypCar(string vin, string plikKierowcy);
};


class KontenerStanow :Kontener {
	map<string, Stanowisko*> mapStan; // <nazwaStanowiska, wskaznik na Stanowisko>
	string pathToFile = "";
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
	void info() override { // tymczasowo
		cout << "Dane z pliku: " << getPathToFile() << " :" << endl;
		for (auto i = mapStan.begin(); i != mapStan.end(); ++i) {
			cout << i->first << ";";
			cout << i->second->formatDataToString() << endl;
		}
	}
	void addRecord();
	void delRecord(string plikKierowcy);
	void saveChanges();
	bool stanowIstnieje(string nazwa);
	bool czyPrzypStan(string nazwaStanow, string plikKierowcy);
};

class KontenerKierow:Kontener {
	map<string, Pracownik*> mapPrac; // <nr pesel, wskaznik na Pracownik>
	string pathToFile = "";
public:
	KontenerKierow() {};
	KontenerKierow(string s) : pathToFile(s) {};
	~KontenerKierow() {
		for (auto i : mapPrac) {
			delete i.second;
		}
	}
	string getPathToFile() { return pathToFile; }
	void createMapFromFile(vector<string> wiersze);
	void info() override { // tymczasowo
		cout << "Dane z pliku: " << getPathToFile() << " :" << endl;
		for (auto i = mapPrac.begin(); i != mapPrac.end(); ++i) {
			cout << i->first << ";";
			cout << i->second->formatDataToString() << endl;
		}
	}
	void addRecord(KontenerCar& k, KontenerStanow& stan);
	void delRecord();
	void saveChanges();
	bool vinWolny(string vin);
	map<string, Pracownik*> getMap() { return mapPrac; }
	Pracownik* getWorker(string c) { return mapPrac.at(c); };
};


class KontenerStacji :Kontener {

	map<string, StacjaPaliw*> mapStacji; // adres, wskaünik na Stacje
	string pathToFile = "";
public:
	KontenerStacji() {};
	KontenerStacji(string s) : pathToFile(s) {};
	~KontenerStacji() {
		for (auto i : mapStacji) {
			delete i.second;
		}
	}
	string getPathToFile() { return pathToFile; }
	void createMapFromFile(vector<string> wiersze);

	void info() override;
	void addRecord();
	void delRecord();
	void saveChanges();
};