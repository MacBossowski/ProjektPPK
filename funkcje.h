/** @file */

#pragma once

#ifndef funkcje_h
#define funkcje_h

#include <set>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <unordered_map>

using namespace std;

typedef vector<string> vSt;
typedef unordered_map<string, double> mStDb;
typedef unordered_map<string, pair<double, string>> mStDbSt;
typedef map<string, vector<pair<string, int>>> graf;


void Czyt_Parametry(int argc, vSt& Parameters, string& wej, string& wyj, string& cent);

/** Funkcja "Czyt_Plik_Wej" odpowiada za odczyt linijek pliku wej�ciowego ze wskazanej lokalizacji.
@param wej Ci�g znak�w okre�laj�cy lokalizacj� pliku tekstowego z informacjami o miastach.
@return wektor ci�g�w znak�w w kt�rym ka�dy element jest linijk� z pliku wej�ciowego. */
vSt Czyt_Plik_Wej(string wej);


/** Funkcja odpowiedzialna za przetworzenie wektora zwr�conego przez funkcje "Czyt_Plik_Wej" w 3 listy.
 @param Plik_Tekstowy Wektor zawieraj�cy informacje z pliku wej�ciowego.
 @param Q Lista z nazwami wszystkich wymienionych miast.
 @param[out] P Lista przygotowywana do wype�nienia, w tej funkcji wype�niana nazwami miast.
 @return Funkcja zwraca graf zawieraj�cy listy wszystkich po��cze� danych miast wraz z odleg�o�ciami. */
graf Dekoder(vSt Plik_Tekstowy, mStDb& Q, mStDbSt& P);


/** Funkcja sporz�dzaj�ca wykaz po��czen mi�dzy miastami, sprawdzaj�c ka�dy wierzcho�ek grafu i wynajduj�c najkr�tsze jego po��czenia. 
Funkcja dzia�a iteracyjnie, dop�ki wszystkie wierzcholki nie zostan� sprawdzone. 
@param Q Lista wierzcho�k�w grafu, p�tla jest kontrolowana poprzez przenoszenie z niej elemet�w do listy S.
@param S Lista sprawdzonych werzcho�k�w przeniesionych z listy Q.
@param P Mapa przechowuj�ca dla ka�dego miasta jego najbli�sze po��czenie.
@param Polaczenia Graf przechowuj�cy informacje z pliku tekstowego.
@return W wyniku dzia�ania funkcji dostajemy wype�niony graf "P" kt�ry do ka�dego miasta przypisuje 
jego najbli�szego s�siada. */
void Djikstra(mStDb& Q, mStDb& S, mStDbSt& P, graf& Polaczenia);


/** Rekurencyjna funkcja sk�adaj�ca informacje z mapy P w odpowiednio sformatowane drogi do lokalizacji docelowych.
@param P Mapa przechowuj�ca dla ka�dego miasta jego najbli�sze po��czenie
@param a Iterator s�u��cy do odczytu odpowiedniego elementu z mapy P
@param cent Nazwa wybranej centrali
@param[out] odp Wska�nik do zmiennej czekajacej na efekt ko�cowy funkcji.
@return Funckja sk�ada w pojedynczy ciag znakow informacje z grafu "P" i wpisuje je do funkcji wyjscie.*/
void wypisanie(mStDbSt& P, string a, string cent, string& odp);


/** Funkcja wypisuj�ca odpowiednio sformatowane trasy do pliku tekstowego.
@param wyj Lokalizacja i nazwa pliku wyj�ciowego.
@param P Mapa przechowuj�ca dla ka�dego miasta jego najbli�sze po��czenie.
@param cent Nazwa wybranej centrali.
@return Funkcja tworzy plik wyj�ciowy w podanej lokalizacji i umieszcza tam ci�gi znak�w z najkr�tszymi trasami do punkt�w grafu */
void wyjscie(string wyj, mStDbSt& P, string cent);
#endif