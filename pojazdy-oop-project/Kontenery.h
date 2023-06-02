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
	string getPathToFile() { return pathToFile; }
	void createMapFromFile(vector<string> wiersze);
	void info() override { // tymczasowo
		cout << "Dane z pliku: " << getPathToFile() << " :" << endl;
		for (auto i = mapCar.begin(); i != mapCar.end();++i) {
			cout << i->first <<";";
			cout << i->second->formatDataToString()<<endl;
		}
	}
	void addRecord();
	void delRecord(string vin);
	void saveChanges(); // nadpisuje dane z pliku
};

class KontenerKierow:Kontener {

};

class KontenerStacjiPaliw:Kontener {

};