#ifndef BIGNUM_hpp
#define BIGNUM_hpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Bignum 
{

public:
    vector<int> l;
    bool s;
    Bignum() {}
    Bignum(string a);
    
Bignum operator+(Bignum a);    
Bignum operator-(Bignum a);
Bignum operator*(Bignum a);

int operator<(Bignum a);
int operator>(Bignum a);
int operator==(Bignum a);

Bignum& operator=(int a);

friend ostream& operator<<(ostream& output, const Bignum& a);
};

int compare(Bignum a, Bignum b);
#endif
