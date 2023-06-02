#pragma once

#include "Pojazdy.h"
#include "Budynki.h"
#include "Pracownicy.h"
#include "Kontenery.h"

#include <vector>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

vector<string> wczytajPlik(const string nazwaP);



class CustomException : public exception {
    string message;
public:
    CustomException(string msg) : message(msg) {}
    const char* what(){
        return message.c_str();
    }
};