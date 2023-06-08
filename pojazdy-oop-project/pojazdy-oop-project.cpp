#include "Header.h"
#include <iostream>

using namespace std;

int main(){
    string odp;

    //Demonstracyjna zmian commita:

    KontenerCar konCar("Data/Pojazdy.txt");
    try {
        vector<string> wiersze = wczytajPlik(konCar.getPathToFile());
        konCar.createMapFromFile(wiersze);
    }catch(CustomException &e){
        //Przydało by się w takiej sytuacji rozróżnić wyjątki z bolku try
        // 1) Nie udało się otworzyć pliku
        // 2) Jeden z wierszy z pliku jest źle zapisany(jest za dużo danych)
        cerr<<e.what()<<endl;

    }
    konCar.info();

    cout << "Chcesz dodac nowe auto? (y/n)";
    cin >> odp;
    if(odp == "y") konCar.addRecord();

    konCar.delRecord("3");
    konCar.saveChanges();

}

