#include "Header.h"

Kalkulator::Kalkulator(KontenerCar& car, KontenerKierow& driver, KontenerStacji& gasStation, KontenerStanow& level) {
	this->car = car;
	this->driver = driver;
	this->gasStation = gasStation;
	this->level = level;
}

double Kalkulator::fuelConsumption(string VIN, double dystans) {
	car1 = car.getCar(VIN);
	return car1->oblZurzycie(dystans)*days;
}

string Kalkulator::fuelType(string VIN) {
	car1 = car.getCar(VIN);
	return car1->getRodzPaliwa();
}

double Kalkulator::workerPositionContribution(string position) {
	pos1 = level.getPosition(position);
	return pos1->getContribution();
}

double Kalkulator::afterDiscount(string GasStationID, double price) {
	gas1 = gasStation.getStation(GasStationID);
	double discount = gas1->getDiscount();
	double result = price - (discount * price);
	return result;
}

string Kalkulator::gasStationName(string GasStationID) {
	gas1 = gasStation.getStation(GasStationID);
	return gas1->getName();
}

double Kalkulator::companyCost(double price, double contribution) {
	return price * contribution;
}

void Kalkulator::discountCheck(double discountPrice, double fullPrice) {
	int spaceValue = 25;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6); 
	if (fullPrice == discountPrice) {
		cout << setw(spaceValue) << "BRAK RABATU" << setw(2) ;
		SetConsoleTextAttribute(hConsole, 7);
		cout << "|";
	}
	
	cout << setw(spaceValue) << discountPrice << setw(2) ;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "|";
}


void Kalkulator::bestStation(double consumption, string fuelType, string position) {
	char z = '_';
	int spaceValue = 25;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //bajery do zmiany kolorow 
	prices.clear(); // czyszcze wektor z danych poprzedniego pracownika
	map<string, StacjaPaliw*> map = gasStation.getMap();
	gasStations.reserve(map.size());
	for (auto const& keyMap : map) {
		gasStations.push_back(keyMap.first);
	}
	string idStacji{};
	for (int i = 0; i < map.size(); i++) {
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
	//TUTAJ WYSWIETLA CALA RESZTE
	SetConsoleTextAttribute(hConsole, 3);
	cout << setw(spaceValue) << gasStationName(station) << setw(2) ;
	
	SetConsoleTextAttribute(hConsole, 7);
	cout << "|";
	
	SetConsoleTextAttribute(hConsole, 4);
	cout << setw(spaceValue) << fullPrice << setw(2);
	SetConsoleTextAttribute(hConsole, 7);
	cout << "|";
	
	discountCheck(discountPrice, fullPrice);

	SetConsoleTextAttribute(hConsole, 2);
	cout << setw(spaceValue) << realPrice << setw(2);
	SetConsoleTextAttribute(hConsole, 7);
	cout << "|" << endl;

	cout << setfill(z) << setw(spaceValue * 7 + 7 * 2 + 1) << z << endl;
	cout.fill(' ');
}

void Kalkulator::compute(int workerID) {
	char z = '_';
	int spaceValue = 25;
	string idPrac{};
	string vin{};
	double dystans{};
	string surname{};
	string position{};
	idPrac = drivers.at(workerID);
	prac1 = driver.getWorker(idPrac);
	vin = prac1->getDriverVin();
	dystans = prac1->getDystans();
	surname = prac1->getNameSurname();
	position = prac1->getPosition();
	//TUTAJ WYSWIETLA IMIE, NAZWISKO, POZYCJE I SPALANIE
	cout << "\174" << setw(spaceValue ) << surname<< setw(2) << "|" << setw(spaceValue) << position << setw(2) << "|" << setw(spaceValue) << fuelConsumption(vin, dystans) << setw(2) << "|";
	

	//cout << surname << "   " << position << "   " << fuelConsumption(vin, dystans) << "   ";
	bestStation(fuelConsumption(vin, dystans), fuelType(vin), position);
}

void Kalkulator::computeEngine() {
	bool exist = false;
	char z = '_';
	int spaceValue = 25;
	string daysText;
	//wrzucam pesele pracownikow do wektora
	map<string, Pracownik*> map = driver.getMap();
	drivers.reserve(map.size()); //rezerwacja pamieci dla wektora
	for (auto const& keyMap : map) {
		drivers.push_back(keyMap.first);
	}
	try {
		cout << endl << "Dla ilu dni wykonac obliczenia: ";
		getlineM(daysText);
		if (is_digits(daysText) == false || stod(daysText) == 0 || daysText.length() > 5) throw CustomException("Podano nieprawidlowa wartosc. ");
		days = stod(daysText);
		cout << "Obliczyc dla wszystkich czy konkretnego pracownika? a/i: ";
		do {
			this->input = _getch();
		} while ((input != 'a') && (input != 'i'));
		switch (input) {
		case 'i':
			cout << endl << "Podaj pesel pracownika dla ktorego chcesz policzyc: ";
			getlineM(pesel);
			for (auto i : driver.getMap()) {
				if (i.first == pesel) exist = true;
			}
			if (!exist) throw CustomException("Pracownik o takim numerze PESEL nie istnieje w bazie.");
			cout << setfill(z) << setw(spaceValue * 7 + 7 * 2 + 1) << z << endl;
			cout.fill(' ');
			// wstawianie nazw kategorii
			cout << "\174" << setw(spaceValue) << "Imie i Nazwisko" << setw(2) << "|" << setw(spaceValue) << "Stanowisko" << setw(2) << "|" << setw(spaceValue) << "Spalanie (miesieczne)" << setw(2) << "|" << setw(spaceValue) << "Najtansza stacja" << setw(2) << "|" << setw(spaceValue) << "Calkowity koszt" << setw(2) << "|" << setw(spaceValue) << "Z rabatem stacji" << setw(2) << "|" << setw(spaceValue) << "Koszt dla firmy" << setw(2) << "|" << endl;
			cout << setfill(z) << setw(spaceValue * 7 + 7 * 2 + 1) << z << endl;
			cout.fill(' ');

			for (int i = 0; i < map.size(); i++)
			{
				if (drivers.at(i) == pesel) {
					compute(i);
				}
			}
			break;
		case 'a':
			//TUTAJ SA KOLUMNY
			cout << endl << setfill(z) << setw(spaceValue * 7 + 7 * 2 + 1) << z << endl;
			cout.fill(' ');
			// wstawianie nazw kategorii
			cout << "\174" << setw(spaceValue) << "Imie i Nazwisko" << setw(2) << "|" << setw(spaceValue) << "Stanowisko" << setw(2) << "|" << setw(spaceValue) << "Spalanie (miesieczne)" << setw(2) << "|" << setw(spaceValue) << "Najtansza stacja" << setw(2) << "|" << setw(spaceValue) << "Calkowity koszt" << setw(2) << "|" << setw(spaceValue) << "Z rabatem stacji" << setw(2) << "|" << setw(spaceValue) << "Koszt dla firmy" << setw(2) << "|" << endl;
			cout << setfill(z) << setw(spaceValue * 7 + 7 * 2 + 1) << z << endl;
			cout.fill(' ');
			for (int i = 0; i < map.size(); i++) {
				compute(i);
			}
		}
	}
	catch (CustomException& e) {
		cout << e.what() << endl;
	}
	delete car1;
	delete prac1;
	delete gas1;
	delete pos1;
}