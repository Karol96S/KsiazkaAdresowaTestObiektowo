#include <iostream>
#include <windows.h>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Logowanie.h"

using namespace std;

 Logowanie::Logowanie()
{
    fstream plik;
    string linia;
    uzytkownik uzytkownikDoWczytania;

    if(plik.good() == true)
    {
        plik.open("Uzytkownicy.txt", ios::in);
        while(getline(plik,linia))
        {
            string nazwa = "", haslo = "", idUzytkownika = "";
            int pozycjaLitery = 0;

            while( linia[ pozycjaLitery ] != '|')
            {
                idUzytkownika = idUzytkownika + linia[ pozycjaLitery ];
                pozycjaLitery++;
            }
            pozycjaLitery++;

            while( linia[ pozycjaLitery ] != '|')
            {
                nazwa = nazwa + linia[ pozycjaLitery ];
                pozycjaLitery++;
            }
            pozycjaLitery++;

            while( linia[ pozycjaLitery ] != '|')
            {
                haslo = haslo + linia[ pozycjaLitery ];
                pozycjaLitery++;
            }

            uzytkownikDoWczytania.idUzytkownika = atoi(idUzytkownika.c_str());
            uzytkownikDoWczytania.nazwa = nazwa;
            uzytkownikDoWczytania.haslo = haslo;
            uzytkownicy.push_back( uzytkownikDoWczytania );
        }
        plik.close();
    }
}

string Logowanie::sprawdzamNazweUzytkownika( int idUzytkownika )
{
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if( uzytkownicy[i].idUzytkownika == idUzytkownika )
        {
            return uzytkownicy[i].nazwa;
            break;
        }
    }
}

int Logowanie::sprawdzNumerPozycjiUzytkownika( int idUzytkownika )
{
    for(int i = 0; i < uzytkownicy.size(); i++)
    {
        if( uzytkownicy[i].idUzytkownika == idUzytkownika )
        {
            return i;
            break;
        }
    }
}

void Logowanie::zmienHaslo( int idUzytkownika )
{
    int ktoryUzytkownik = 0;
    int sprawdzamHaslo = 1;
    string noweHaslo;

    while( sprawdzamHaslo == 1 )
    {
    for(int i = 0; i < uzytkownicy.size(); i++)
    {
        if( uzytkownicy[i].idUzytkownika == idUzytkownika)
        {
            ktoryUzytkownik = i;
        }
    }

    system("cls");
    cout << "Aby cofnac wcisnij '0'" << endl;
    cout << endl;
    cout << "Prosze podac nowe haslo: ";
    cin >> noweHaslo;

    if( noweHaslo == "0" )
    {
        break;
    }

    sprawdzamHaslo = 0;

    for(int i = 0; i < uzytkownicy.size(); i++)
    {
        if( uzytkownicy[i].haslo == noweHaslo )
        {
            system("cls");
            cout << "Podano bledne haslo!" << endl;
            system("pause");
            sprawdzamHaslo = 1;
            break;
        }
    }

    if ( sprawdzamHaslo == 0 )
    {
        uzytkownicy[ktoryUzytkownik].haslo = noweHaslo;
        system("cls");
        cout << "Haslo zostalo poprawnie zmienione!" << endl;
        nadpiszUzytkownikow ();
        system("pause");
    }

    }

}

void Logowanie::zapiszUzytkownika( string nazwa, string haslo, int id)
{
    uzytkownik nowyUzytkownik;
    nowyUzytkownik.nazwa = nazwa;
    nowyUzytkownik.haslo = haslo;
    nowyUzytkownik.idUzytkownika = id;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    plik<<nowyUzytkownik.idUzytkownika<< "|";                                                           //ZAPIS
    plik<<nowyUzytkownik.nazwa<< "|";
    plik<<nowyUzytkownik.haslo<< "|" << endl;
    plik.close();
}

void Logowanie::nadpiszUzytkownikow()
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    for(int i = 0; i < uzytkownicy.size(); i++)
    {
    plik<<uzytkownicy[i].idUzytkownika<< "|";
    plik<<uzytkownicy[i].nazwa<< "|";
    plik<<uzytkownicy[i].haslo<< "|" << endl;
    }
    plik.close();
}

int Logowanie::rejestracja()
{
    string nazwa, haslo;
    uzytkownik nowyUzytkownik;
    int iloscUzytkownikow = uzytkownicy.size();
    int id = 0;
    int sprawdzamCzyNazwaJestZajeta = 0;
    while ( id == 0 )
    {
        while ( sprawdzamCzyNazwaJestZajeta == 0 )
        {
            system("cls");
            cout << "Prosze podac nazwe uzytkownika: ";
            cin >> nazwa;
            sprawdzamCzyNazwaJestZajeta = 1;

            if( iloscUzytkownikow > 0 )
            {
                for (int i = 0; i < iloscUzytkownikow; i++)
                {
                    if( uzytkownicy[i].nazwa == nazwa )
                    {
                        cout << endl;
                        cout << "Podana nazwa jest juz zajeta!" << endl;
                        sprawdzamCzyNazwaJestZajeta = 0;
                        system("pause");
                        break;
                    }
                }
            }

        }

            system("cls");
            cout << "Prosze podac haslo: ";
            cin >> haslo;

        nowyUzytkownik.nazwa = nazwa;
        nowyUzytkownik.haslo = haslo;
        if ( uzytkownicy.size() == 0 )
        {
            nowyUzytkownik.idUzytkownika = 1;
        }
        else if( uzytkownicy.size() > 0 )
        {
            nowyUzytkownik.idUzytkownika = uzytkownicy[ iloscUzytkownikow - 1 ].idUzytkownika + 1;
        }

        id = nowyUzytkownik.idUzytkownika;
    }

    if( id!= 0) Logowanie::zapiszUzytkownika ( nazwa, haslo, id );
    uzytkownicy.push_back( nowyUzytkownik );

    return id;

    system ("cls");
    cout << "Pomyslnie zarejestrowano nowego uzytkownika!" << endl;
    cout << endl;
    system("pause");
}

int Logowanie::logowanie()
{
    string nazwa, haslo;
    int id = 0;
    int sprawdzamCzyNazwaIstnieje = 0;
    int sprawdzamCzyHasloIstnieje = 0;
    int numerUzytkownika = 0;

    while ( id == 0 )
    {
        while ( sprawdzamCzyNazwaIstnieje == 0 )
        {
            system("cls");
            cout << "Aby wrocic wpisz '0'"<< endl;
            cout << endl;
            cout << "Podaj login(nazwe): ";
            cin >> nazwa;

            if ( nazwa == "0")
            {
                return 0;
            }

            else
            {
                if( uzytkownicy.size() > 0)
                {
                    for (int i = 0; i < uzytkownicy.size(); i++)
                    {
                        if( uzytkownicy[i].nazwa == nazwa)
                        {
                            sprawdzamCzyNazwaIstnieje = 1;
                            break;
                        }
                    }
                    if( sprawdzamCzyNazwaIstnieje == 0 )
                    {
                        cout << endl;
                        cout << "Podano bledna nazwe uzytkownika!" << endl;
                        system("pause");
                    }

                }

                else
                {
                    cout << "Ta baza danych nie ma jeszcze zapisanych uzytkownikow!" << endl;
                    system("pause");
                    return 0;
                }

            }
        }


        while ( sprawdzamCzyHasloIstnieje == 0 )
        {
            system ("cls");
            cout << "Aby wrocic wpisz '0'"<< endl;
            cout << endl;
            cout << "Podaj haslo: ";
            cin >> haslo;

            if ( haslo == "0")
            {
                return 0;
            }

            else
            {
                for (int i = 0; i < uzytkownicy.size(); i++)
                {
                    if( uzytkownicy[i].haslo == haslo && uzytkownicy[i].nazwa == nazwa )
                    {
                        sprawdzamCzyHasloIstnieje = 1;
                        numerUzytkownika = i;
                        system("cls");
                        cout << "Zalogowano poprawnie! Witaj." << endl;
                        cout << endl;
                        system("pause");
                    }
                }

                if( sprawdzamCzyHasloIstnieje == 0 )
                {
                    cout << endl;
                    cout << "Podano bledne haslo!" << endl;
                    system("pause");
                }
                id = uzytkownicy[ numerUzytkownika ].idUzytkownika;
            }
        }
    }
    return id;
}

int Logowanie::ekranLogowania()
{
    int idUzytkownika = -1;
    char wybor;
    while (1)
    {
        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        if(wybor == '1')
        {
            idUzytkownika = logowanie();
            break;
        }
        else if (wybor == '2')
        {
            idUzytkownika = rejestracja();
        }
        else if (wybor == '3')
        {
            break;
        }
        else
        {
            cout << endl;
            cout << "Niewlasciwy klawisz, prosze wybrac opcje z zakresu 1 do 3" << endl;
            system("pause");
        }

    }
    return idUzytkownika;
}


