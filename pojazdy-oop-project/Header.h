#pragma once

#include "Pojazdy.h"
#include "Budynki.h"
#include "Pracownicy.h"
#include "Kontenery.h"
#include "Menu.h"
#include "Kalkulator.h"

#include <vector>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

vector<string> wczytajPlik(const string nazwaP);
bool is_digits(const string& str); // Funkcja do sprawdzania czy string zawiera same cyfry
bool containsOnlyLetters(string const& str);
bool containsDigitsANDLetters(string const& str);
bool check(int zmienna);
bool check(double zmienna);
bool is_digits2(const string& str);

class CustomException : public exception {
    string message;
    int errorCode;
public:
    CustomException(string msg, int err = 0) : message(msg), errorCode(err){}

    //get'ery
    const char* what() { return message.c_str(); }
    int getErrorCode() { return errorCode; };
};