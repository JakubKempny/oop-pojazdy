#include "Header.h"

using namespace std;

int main() {
    KontenerCar konCar("Data/Pojazdy.txt");
    KontenerKierow konKier("Data/Pracownicy.txt");
    KontenerStacji konStacji("Data/Stacje.txt");
    KontenerStanow konStanow("Data/Stanowiska.txt");
    Menu menu1(konCar,konKier, konStacji, konStanow);
    menu1.showFullscreen();
    menu1.showMenu();
}

