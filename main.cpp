

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "funkcje.h"

using namespace std;

int main(int argc, char **argv)
{

    string wej, wyj, cent;
   
    ///Test parametrów wejściowych
    if (argc !=7)
    {
        cerr << "Podano nieprawidlowe parametry wejsciowe:" << endl;
        cerr << argv[0] << " -i  -o  -s" << endl;
        cerr << "-i: plik wejsciowy z drogami," << endl << "-o: plik wyjsciowy z trasami spedycyjnymi," << endl << "-s: nazwa miasta startowego, gdzie znajduje sie centrala" << std::endl;
        exit(3); 
    }
    else {
        vSt Parameters;
        /// odczyt parametrów wejściowych
        for (int y = 1; y < argc; y++)
        {
            Parameters.push_back(argv[y]);
        };
        Czyt_Parametry(argc, Parameters, wej, wyj, cent);
        
    };



    ///Formatowanie parametru -s tak aby treść zaczynała się od dużej litery
    cent[0] = toupper(cent[0]);


    mStDb Q; ///Lista miast nie użytych w algorytmie
    mStDb S; ///Lista miast użytych w algorytmie
    mStDbSt P; ///Lista zawierająca miasto docelowe / najkrótszy poprzedzający odcinek / miasto poprzedzające docelowe

    ///Mapa zawierająca informacje o połączeniach między miastami oraz o odległościach je dzielących.
    ///Wypełniana jest przy pomocy funkcji "Czyt_Plik_Wej" która zczytuje ze wskazanego parametrem "wej" pliku wejściowego linijki z tekstem.
    ///Przekazane są one później w formie wektora do funkcji "Dekoder" która rozdziela wyrazy między spacjami, porządkuje je w grafie sporządzonym z mapy indeksowanej 
    ///nazwami miast i przypisująca im wektor zawierający pary miast z którymi są połączone oraz odległości między nimi. 
    ///Parametry Q i P przekazują do tej funkcji odnoścniki do wcześniej opisanych list Q i P, które funkcja wypełnia wszystkimi nazwami miast.
    graf Polaczenia = Dekoder((Czyt_Plik_Wej(wej)), Q, P);

    if (Q[cent] == 0)
    {
        cerr << "W pliku nie znaleziono miasta o nazwie " << cent << "." << endl;
        return 0;
    };


    ///Usunięcie niepotrzebnych informacji o odległości między wybranym miastem a nim samym;
    Q[cent] = 0;
    P[cent].first = 0;

    ///Wywołanie funkcji wypełniającej listę P na podstawie informacji zawartych w grafie "Polaczenia".
    ///Kontrolowana jest przez przenoszenie elementów z listy Q do listy S.
    Djikstra(Q, S, P, Polaczenia);

    ///Usunięcie niepotrzebnych informacji o odległości między wybranym miastem a nim samym;
    P.erase(cent);

    /// Wywołanie funkcji odpowiedzialnej za umieszczennie w pliku wyjściowym finałowych informacji o najkrótszych trasach
    wyjscie(wyj, P, cent);

    cerr << "Sukces!" << endl;
    return 0;

}