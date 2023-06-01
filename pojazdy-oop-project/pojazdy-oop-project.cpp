#include "Header.h"
#include <iostream>

using namespace std;

int main(){
    //Demonstracyjna zmian commita:
    KontenerCar konCar("Data/Pojazdy.txt");
    konCar.createMapFromFile(wczytajPlik(konCar.getPathToFile()));
    konCar.info();
    konCar.addRecord();
    konCar.saveChanges();
}

