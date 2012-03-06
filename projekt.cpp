// Autor: Michal Bladowski, 2012

#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <cstdlib>

using namespace std;

void dodawanie();
int zamien(char c);

string pierwsza = "";
string pierwsza_signed = "";  
string druga = "";
string druga_signed = "";

vector<int> pierwsza_wektor;
vector<int> druga_wektor;
vector<int> wynik_wektor;

int pierwsza_dlugosc;
int druga_dlugosc;
int pomocnicza = 0;

char signum;

bool pierwsza_ujemna = false; 
bool druga_ujemna = false; 
bool wynik_ujemny = false;

/* Main */
int main()
{
    cout << "Podaj dwie liczby szesnastkowe:" << endl;
    cout << "Pierwsza_liczba Operator Druga_liczba:";
    
    cin >> pierwsza >> signum >> druga;

    if(!isdigit(pierwsza[0]))
    {
        if(pierwsza[0] == '-') pierwsza_ujemna = true;
        pierwsza.erase(0, 1);
    }

    if(!isdigit(druga[0]))
    {
        if(druga[0] == '-') druga_ujemna = true;
        druga.erase(0, 1);
    }

    unsigned int i;
    bool res = false;
    
    for(i = 0; i < pierwsza.length(); i++)
    {
        if(!((pierwsza[i] >= (char)48 && pierwsza[i] <= (char)57) || (pierwsza[i] >= 
(char)65 && pierwsza[i] <= (char)70)))
        {
            res = true;
        }
    }

    for(i = 0; i < druga.length(); i++)
    {
        if(!((druga[i] >= 48 && druga[i] <= 57) || (druga[i] >= 65 && druga[i] <= 70)))
        {
            res = true;
        }
    }
    
    if(res)
    {
        cout << "Podane liczby maja niepoprawny format" << endl;
        return 0;
    }

    pierwsza_wektor.clear();
    druga_wektor.clear();
    wynik_wektor.clear();

    for(int i = pierwsza.length() - 1; i >= 0; i -= 2)
    {
        pierwsza_wektor.push_back(zamien(pierwsza[i - 1]) * 16 + zamien(pierwsza[i]));
        if(i == 2)
        {
            pierwsza_wektor.push_back(zamien(pierwsza[i - 2]));
        }    
    }

    for(int i = druga.length() - 1; i >= 0; i -= 2)
    {
        druga_wektor.push_back(zamien(druga[i - 1]) * 16 + zamien(druga[i]));
        if(i == 2)
        {
            druga_wektor.push_back(zamien(druga[i - 2]));
        }
    }

    pierwsza_dlugosc = pierwsza_wektor.size();
    druga_dlugosc = druga_wektor.size();
    
    if(signum == '+')
    {
        dodawanie();
    } 
    else
    {
        cout << "Niepoprawny symbol" << endl;
    }

    if(wynik_ujemny)
    {
        cout << "-";
    }

    for(int i = wynik_wektor.size() - 1; i >= 0; i--)
    {
        cout << hex << uppercase << wynik_wektor[i] << endl;
        system("PAUSE");
    }

    return 0;
}

/* Dodawanie */
void dodawanie()
{
    if(pierwsza_dlugosc == druga_dlugosc)
    {
        unsigned int i;
        for(i = 0; i < pierwsza_wektor.size(); i++)
        {
                pomocnicza = pierwsza_wektor[i] + druga_wektor[i] + pomocnicza;
                wynik_wektor.push_back(pomocnicza % 256);
                pomocnicza = pomocnicza / 256;
        }
            if(pomocnicza != 0) wynik_wektor.push_back(pomocnicza);
            pomocnicza = 0;
    }
    else
    {
        int i;
        if(pierwsza_dlugosc > druga_dlugosc)
        {
            for(i = 0; i < pierwsza_dlugosc; i++)
            {
                if(i < druga_dlugosc)
                {
                    pomocnicza = pierwsza_wektor[i] + druga_wektor[i] + pomocnicza;
                    wynik_wektor.push_back(pomocnicza % 256);
                    pomocnicza = pomocnicza / 256;
                } 
                else 
                {
                    pomocnicza = pierwsza_wektor[i] + pomocnicza;
                    wynik_wektor.push_back(pomocnicza % 256);
                    pomocnicza = pomocnicza / 256;
                }
            }
        } 
        else 
        {
            for(i = 0; i < druga_dlugosc; i++)
            {
                if(i < pierwsza_dlugosc)
                {
                    pomocnicza = pierwsza_wektor[i] + druga_wektor[i] + pomocnicza;
                    wynik_wektor.push_back(pomocnicza % 256);
                    pomocnicza = pomocnicza / 256;
                } 
                else 
                {
                    pomocnicza = druga_wektor[i] + pomocnicza;
                    wynik_wektor.push_back(pomocnicza % 256);
                    pomocnicza = pomocnicza / 256;
                }
            }
        }
    }
}

/* Zamiana */
int zamien(char c){
    if((int)c >= 48 && (int)c <= 57)
    {
        return (int)c-48;
    }

    if((int)c >= 65 && (int)c <= 70)
    {
        if(c == 65) return 10;
        if(c == 66) return 11;
        if(c == 67) return 12;
        if(c == 68) return 13;
        if(c == 69) return 14;
        if(c == 70) return 15;
    }
    return -1;
}

