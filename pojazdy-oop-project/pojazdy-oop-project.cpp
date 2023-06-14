#include "Header.h"

using namespace std;

int main() {
    HWND console = GetConsoleWindow();    // maksymalizacja widoku konsli
    ShowWindow(console, SW_MAXIMIZE);
    KontenerCar konCar("Data/Pojazdy.txt");
    KontenerKierow konKier("Data/Pracownicy.txt");
    KontenerStacji konStacji("Data/Stacje.txt");
    KontenerStanow konStanow("Data/Stanowiska.txt");
    Menu menu1(konCar,konKier, konStacji, konStanow);
    menu1.showMenu();
}

