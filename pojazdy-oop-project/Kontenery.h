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

};

class KontenerKierow:Kontener {

};

class KontenerStacjiPaliw:Kontener {

};