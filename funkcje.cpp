#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include "funkcje.h"

using namespace std;

void Czyt_Parametry(int argc, vSt& Parameters, string& wej, string& wyj, string& cent)
{
    for (int y = 0; y < argc-1; y++)
    {
        if (string(Parameters[y]) == "-i")  //Nazwa pliku wejściowego
        {
            wej = string(Parameters[y + 1]);
        }
        if (string(Parameters[y]) == "-o") //Nazwa pliku wyjściowego
        {
            wyj = string(Parameters[y + 1]);
        }
        if (string(Parameters[y]) == "-s") //Nazwa centrali
        {
            cent = string(Parameters[y + 1]);
        }
    }
};

vSt Czyt_Plik_Wej(string wej) {

    vSt Plik_Tekstowy; //Wektor Przechowywujący linijki z pliku wejœciowego


    //odczytanie pliku wejœciowego i zapisanie treœci w zmiennej
    ifstream inFile;

    //Otwarcie pliku z trasami
    inFile.open(wej, ios::out);

    //Test otwarcia pliku 
    if (!inFile)
    {
        cout << "Nie mozna otworzyć pliku wejsciowego" << endl;
        exit(2);
    }

    string x;


    //Zapis linijek w wektorze
    while (getline(inFile, x))
    {
        Plik_Tekstowy.push_back(x);
    };

    //Zamkniêcie pliku z trasami
    inFile.close();

    return Plik_Tekstowy;
}




graf Dekoder(vSt Plik_Tekstowy, mStDb& Q, mStDbSt& P) {
    graf Wyj;
    for (auto a : Plik_Tekstowy)
    {
        //Licznik spacji w linijce tekstu
        int Spacje = 0; 

        //Miejsca na wyrazy z linijki tekstu
        string Miasto1, Miasto2, Dystans, Bufor;

        for (auto b : a)
        {

            if (isspace(b))     //Dodawanie wystąpień spacji do licznika spacji
            {
                Spacje += 1;
                continue;
            }
            else if (Spacje == 0) //Czytanie pierwszego miasta w linijce
            {
                Miasto1 += b;
            }
            else if (Spacje == 1) //Czytanie drugiego miasta w linijce
            {
                Miasto2 += b;
            }
            else if (Spacje == 2) //Czytanie odległości między miastami
            {
                Dystans += b;
            };
        };
        if (stoi(Dystans) < 0)
        {
            cerr << "W pliku wejsciowym znaleziono ujemny dystans";
            exit(4);
        };
       
        Wyj[Miasto1].push_back(make_pair(Miasto2, stoi(Dystans))); //Dodawanie do grafu informacji o 
        Wyj[Miasto2].push_back(make_pair(Miasto1, stoi(Dystans))); //wzajemnej odległości między miastami.
        Q[Miasto1] = numeric_limits<double>::max(); //Przygotowywanie listy Q, wypełnienie jest wszystkimi
        Q[Miasto2] = numeric_limits<double>::max(); //miastami i przypisanie im wartości max jako odległości.
        P[Miasto1].first = numeric_limits<double>::max(); //Przygotowywanie listy P, wypełnienie jest wszystkimi
        P[Miasto2].first = numeric_limits<double>::max(); //miastami i przypisanie im wartości max jako odległości.
        P[Miasto1].second = "Niedostepny"; //dopuszczamy możliwość że miasto może być niedostępne
        P[Miasto2].second = "Niedostepny";
    }
    Plik_Tekstowy.clear();
    return Wyj;
}



void Djikstra(mStDb& Q, mStDb& S, mStDbSt& P, graf& Polaczenia) {
    double Min;
    vSt Wyj;

    while (Q.size() > 0)
    {
        Min = numeric_limits<double>::max();

        for (auto a : Q)
        {
            if (a.second < Min)
            {
                Min = a.second;
                Wyj.clear();
                Wyj.push_back(a.first);
            }
            else if (a.second == Min)
            {
                Wyj.push_back(a.first);
            }

        }

        S[Wyj[0]] = 1;
        Q.erase(Wyj[0]);

        for (string b : Wyj)
        {
            for (auto c : Polaczenia[b])
            {
                if (S[c.first] == 1)
                {
                    continue;
                };
                if (P[c.first].first > P[Wyj[0]].first + c.second)
                {
                    Q[c.first] = c.second;
                    P[c.first].first = P[Wyj[0]].first + c.second;
                    P[c.first].second = Wyj[0];
                };

            }

        }


        Wyj.clear();

    }
    Polaczenia.clear();
    S.clear();
    Q.clear();

}


void wypisanie(mStDbSt& P, string a, string cent, string& odp)
{
    if (P[a].second != cent)
    {
        wypisanie(P, P[a].second, cent, odp);
    };
    odp += " -> " + a;
    return;
};





void wyjscie(string wyj, mStDbSt& P, string cent) {
    ofstream outfile(wyj);
    // Zapis tras z mapy lista w pliku wyjsciowym pod warunkiem ze odleglosc z 
   // mapy lista jest rowna najmniejszej dla danego miasta tj. tej z mapy miasta
    string odp;
    for (auto a : P)
    {
        if (a.second.second == "Niedostepny")
        {
            odp = cent + " -> " + a.first + ": " + "Nieosiagalny" + "\n";
        }
        else
        {
            odp = cent;
            wypisanie(P, a.first, cent, odp);
            odp += ": " + to_string(static_cast<int>(a.second.first)) + "\n";
        }
        
        outfile << odp;
    };

    //Zamkniêcie pliku
    outfile.close();
}