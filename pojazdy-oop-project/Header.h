#pragma once

#include "Pojazdy.h"
#include "Budynki.h"
#include "Pracownicy.h"
#include "Kontenery.h"
#include "Menu.h"
#include "Kalkulator.h"

#include <algorithm>
#include <conio.h>
#include <vector>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <Windows.h>
#include <cctype> // toupper

using namespace std;

vector<string> wczytajPlik(const string nazwaP);
// Funkcja sprawdzajace poprawnosc danych
bool is_digits(const string& str); 
bool containsOnlyLetters(string const& str);
bool containsDigitsANDLetters(string const& str);
bool is_digits2(const string& str);
void CommaWithDot(string& str);
string ignoreAfterSpace(const string& input);
bool checkMultipleDotsCommas(string& str);
void getlineM(string& str);
string nameToLower(string name);

class CustomException : public exception {
    string message;
    int errorCode;
public:
    CustomException(string msg, int err = 0) : message(msg), errorCode(err){}
    //get'ery
    const char* what() { return message.c_str(); }
    int getErrorCode() { return errorCode; };
};
