#pragma once

class Kontener {
	virtual void info() = 0;
};

class KontenerCar:Kontener {
	map<string, Car*> mapCar; // <nr Vim, wskaŸnik na Car>
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
	void delRecord(string vin);
	void saveChanges(); // nadpisuje dane z pliku
	//get'ery
	Car* getCar(string c) { return mapCar.at(c); };

	bool vinIstnieje(string vin);
};

class KontenerKierow:Kontener {
	map<string, Pracownik*> mapPrac; // <nr pesel, wskaznik na Pracownik>
	string pathToFile = "";
public:
	KontenerKierow() {};
	KontenerKierow(string s) : pathToFile(s) {};
	string getPathToFile() { return pathToFile; }
	void createMapFromFile(vector<string> wiersze);
	void info() override { // tymczasowo
		cout << "Dane z pliku: " << getPathToFile() << " :" << endl;
		for (auto i = mapPrac.begin(); i != mapPrac.end(); ++i) {
			cout << i->first << ";";
			cout << i->second->formatDataToString() << endl;
		}
	}
	void addRecord(KontenerCar& k);
	void delRecord(string pesel);
	void saveChanges();
	bool vinWolny(string vin);
};

class KontenerStacjiPaliw:Kontener {

};