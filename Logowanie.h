#include <iostream>
#include <windows.h>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

class Logowanie
{
public:
    struct uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

vector <uzytkownik> uzytkownicy;

    char wybor;


    string sprawdzamNazweUzytkownika( int idUzytkownika );
    int sprawdzNumerPozycjiUzytkownika( int idUzytkownika );
    void zmienHaslo( int idUzytkownika );
    void zapiszUzytkownika( string, string, int);
    void nadpiszUzytkownikow();
    int rejestracja();
    int logowanie();
    int ekranLogowania();

    Logowanie();

};
