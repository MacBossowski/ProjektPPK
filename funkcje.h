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

/** Funkcja "Czyt_Plik_Wej" odpowiada za odczyt linijek pliku wejœciowego ze wskazanej lokalizacji.
@param wej Ci¹g znaków okreœlaj¹cy lokalizacjê pliku tekstowego z informacjami o miastach.
@return wektor ci¹gów znaków w którym ka¿dy element jest linijk¹ z pliku wejœciowego. */
vSt Czyt_Plik_Wej(string wej);


/** Funkcja odpowiedzialna za przetworzenie wektora zwróconego przez funkcje "Czyt_Plik_Wej" w 3 listy.
 @param Plik_Tekstowy Wektor zawieraj¹cy informacje z pliku wejœciowego.
 @param Q Lista z nazwami wszystkich wymienionych miast.
 @param[out] P Lista przygotowywana do wype³nienia, w tej funkcji wype³niana nazwami miast.
 @return Funkcja zwraca graf zawieraj¹cy listy wszystkich po³¹czeñ danych miast wraz z odleg³oœciami. */
graf Dekoder(vSt Plik_Tekstowy, mStDb& Q, mStDbSt& P);


/** Funkcja sporz¹dzaj¹ca wykaz po³¹czen miêdzy miastami, sprawdzaj¹c ka¿dy wierzcho³ek grafu i wynajduj¹c najkrótsze jego po³¹czenia. 
Funkcja dzia³a iteracyjnie, dopóki wszystkie wierzcholki nie zostan¹ sprawdzone. 
@param Q Lista wierzcho³ków grafu, pêtla jest kontrolowana poprzez przenoszenie z niej elemetów do listy S.
@param S Lista sprawdzonych werzcho³ków przeniesionych z listy Q.
@param P Mapa przechowuj¹ca dla ka¿dego miasta jego najbli¿sze po³¹czenie.
@param Polaczenia Graf przechowuj¹cy informacje z pliku tekstowego.
@return W wyniku dzia³ania funkcji dostajemy wype³niony graf "P" który do ka¿dego miasta przypisuje 
jego najbli¿szego s¹siada. */
void Djikstra(mStDb& Q, mStDb& S, mStDbSt& P, graf& Polaczenia);


/** Rekurencyjna funkcja sk³adaj¹ca informacje z mapy P w odpowiednio sformatowane drogi do lokalizacji docelowych.
@param P Mapa przechowuj¹ca dla ka¿dego miasta jego najbli¿sze po³¹czenie
@param a Iterator s³u¿¹cy do odczytu odpowiedniego elementu z mapy P
@param cent Nazwa wybranej centrali
@param[out] odp WskaŸnik do zmiennej czekajacej na efekt koñcowy funkcji.
@return Funckja sk³ada w pojedynczy ciag znakow informacje z grafu "P" i wpisuje je do funkcji wyjscie.*/
void wypisanie(mStDbSt& P, string a, string cent, string& odp);


/** Funkcja wypisuj¹ca odpowiednio sformatowane trasy do pliku tekstowego.
@param wyj Lokalizacja i nazwa pliku wyjœciowego.
@param P Mapa przechowuj¹ca dla ka¿dego miasta jego najbli¿sze po³¹czenie.
@param cent Nazwa wybranej centrali.
@return Funkcja tworzy plik wyjœciowy w podanej lokalizacji i umieszcza tam ci¹gi znaków z najkrótszymi trasami do punktów grafu */
void wyjscie(string wyj, mStDbSt& P, string cent);
#endif