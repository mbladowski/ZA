#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include "Bignum.h"
#define BASE 256

using namespace std;

// Constructor
Bignum::Bignum(string x)
{
    vector<int> v;
    
    if(x[0] == '+')
    {
        s = true;
        for(unsigned int i = 1; i < x.length(); i++)
        {
            if(x[i] <= '9') v.push_back(x[i] - 48);
            else if(x[i] <= 'F') v.push_back(x[i] - 55);
            else v.push_back(x[i] - 87);
        }
    }
    else if(x[0] == '-')
    {
        s = false;
        for(unsigned int i = 1; i < x.length(); i++)
        {
            if(x[i] <= '9') v.push_back(x[i] - 48);
            else if(x[i] <= 'F') v.push_back(x[i] - 55);
            else v.push_back(x[i] - 87);
        }
    }
    else
    {
        s = true;
        for(unsigned int i = 0; i < x.length(); i++)
        {
            if(x[i] <= '9')
                v.push_back(x[i] - 48);
            else if(x[i] <= 'F')
                v.push_back(x[i] - 55);
            else
                v.push_back(x[i] - 87);
        }
    }
    
    for(int i = v.size() - 1; i >= 1; i -= 2)
    {
        l.push_back(v[i] + v[i - 1] * 16);
    }
    
    if(v.size() % 2) l.push_back(v[0]);
}

// Addition
Bignum Bignum::operator+(Bignum x)
{
    Bignum b;
    b.s = true;
    int size;
    int car = 0;
    
    if(x.l.size() > this->l.size())
    {
        for(unsigned int i = this->l.size() - 1; i < x.l.size() - 1;
i++) this->l.push_back(0);
        size = this->l.size() - 1;
    }
    else
    {
        for(unsigned int i = x.l.size() - 1; i < this->l.size() - 1;
i++) x.l.push_back(0);
        size = x.l.size() - 1;
    }
    
    if(this->s == true && x.s == true)
    {
        for(int i = 0; i <= size; i++)
        {
            int temp;
            temp = (x.l[i] + this->l[i] + car);
            if(temp > 255)
            {
                car = temp / BASE;
                temp %= BASE;
            }
            else car = 0;
            b.l.push_back(temp);
        }
        if(car != 0) b.l.push_back(car);
    }
    else if(this->s == true && x.s == false)
    {
        x.s = true;
        b = *this - x;
    }
    else if(this->s == false && x.s == true)
    {
        this->s = true;
        b = *this - x;
        if(compare(*this,x) == -1) b.s = true;
    }
    else
    {
        b.s = false;
        for(int i = 0; i <= size; i++)
        {
            int temp;
            temp = (x.l[i] + this->l[i] + car);
            if(temp > 255)
            {
                car = temp / BASE;
                temp %= BASE;
            }
            else car = 0;
            b.l.push_back(temp);
        }
        if(car != 0) b.l.push_back(car);
    }
    
    while(b.l.size() > 1 && b.l.back() == 0) b.l.pop_back();

    return b;
}

// Multiplication
Bignum Bignum::operator*(Bignum x)
{
    Bignum b;
    int m = this->l.size();
    int n = x.l.size();
    
    if(this->s == x.s) b.s = true;
    else b.s = false;
    
    for(int i = 0; i < m + n; i++) b.l.push_back(0);
    for(int j = 0; j < n; j++)
    {
        if(x.l[j] == 0) b.l[j + m] = 0;
        else
        {
            int c = 0;
            for(int i = 0; i < m; i++)
            {
                int r = this->l[i] * x.l[j] + c + b.l[i+j];
                b.l[i + j] = r % BASE;
                c = r / BASE;
            }
            b.l[j + m] = c;
        }
    }
    
    while(b.l.size() > 1 && b.l.back() == 0) b.l.pop_back();

    return b;
}

// Compare
int compare(Bignum x, Bignum y)
{
    if(x.s == y.s && x.s == true)
    {
        if(x.l.size() > y.l.size()) return 1;
        else if(x.l.size() < y.l.size()) return -1;
        else
        {
            for(int i = x.l.size() - 1; i >= 0; i--)
            {
                if(x.l[i] > y.l[i]) return 1;
                else if(x.l[i] < y.l[i]) return -1;
            }
        }
        return 0;
    }
    else if(x.s == true)
    {
        return 1;
    }
    else if(y.s == true)
    {
        return -1;
    }
    else
    {
        if(x.l.size() > y.l.size()) return -1;
        else if(x.l.size() < y.l.size()) return 1;
        else
        {
            for(int i = x.l.size() - 1; i >= 0; i--)
            {
                if(x.l[i] > y.l[i]) return -1;
                else if(x.l[i] < y.l[i]) return 1;
            }
        }
        return 0;
    }
}

// Substraction
Bignum Bignum::operator-(Bignum x)
{
    Bignum b;
    Bignum temp;
    b.s = true;
    int size;
    
    if(compare(*this,x) == -1)
    {
        b.s = false;
        temp = *this;
        *this = x;
        x = temp;
    }
    else if(compare(*this,x) == 0)
    {
        b.l.push_back(0);
        return b;
    }
    if(x.l.size() > this->l.size())
    {
        for(unsigned int i=this->l.size()-1;i<x.l.size()-1;i++)
this->l.push_back(0);
        size = this->l.size();
    }
    else
    {
        for(unsigned int i = x.l.size() - 1; i < this->l.size() - 1;
i++) x.l.push_back(0);
        size = x.l.size();
    }
    if(this->s == true && x.s == true)
    {
        int k = 0;
        for(int i = 0; i < size; i++)
        {
            int temp = this->l[i] - x.l[i] + k;
            if(temp < 0)
            {
                temp = temp & 255;
                if(i + 1 < size) this->l[i+1]--;
            }
            
            b.l.push_back(temp % BASE);
            k = temp / BASE;
        }
    }
    else if(this->s == false && x.s == false)
    {
        x.s = true;
        int k = 0;
        for(int i = 0; i < size; i++)
        {
            int temp = this->l[i] - x.l[i] + k;
            if(temp < 0)
            {
                temp = temp & 255;
                if(i + 1 < size)
                    this->l[i + 1]--;
            }
            
            b.l.push_back(temp % BASE);
            k = temp / BASE;
        }
    }
    else if(this->s == false && x.s == true)
    {
        x.s = false;
        b = *this + x;
    }
    else if(this->s == true && x.s == false)
    {
        x.s = true;
        bool temp = b.s;
        b = *this + x;
        if(!temp)
            b.s = false;
    }
    
    while(b.l.size() > 1 && b.l.back() == 0) b.l.pop_back();

    if(temp.l.size() != 0)
    {
        temp = *this;
        *this = x;
        x = temp;
    }
    
    return b;
}

// Division
Bignum Bignum::operator/(Bignum x)
{
       
    Bignum a("1");
    Bignum b("0");
    Bignum c("0");
    Bignum zero("0");
    Bignum one("1");
    Bignum two("2");
    
    if(*this < x)
    {
        //zero.s = false;
        //x.s = true;
        return zero;
    }
    
    if(*this == x)
    {
        return one;
    }

    while(b + x <= *this && zero * x <= *this)
    {
        if(two * a * x + b > *this)
        {
            c = *this;
            b = a * x + b;
            zero = zero + a;
            a = one;
        }
        else a = two * a;
    }
    
    return zero;
}

// Modulo division
Bignum Bignum::operator%(Bignum x)
{
    return *this - x * (*this / x);
}

// Greatest common divisor
Bignum greatest_common_divisor(Bignum x, Bignum y)
{
    Bignum zero("0");
    Bignum z("0");
    
    if(x == zero) return y;

    while(y != zero)
    {
        //if(x > y) x = x - y;
        //else y = y - x;
        z = x % y;
        x = y;
        y = z;
    }
    
    return x;
}

// Stein's greatest common divisor
Bignum stein_greatest_common_divisor(Bignum x, Bignum y)
{
    Bignum zero("0");
    Bignum one("1");
    Bignum two("2");
    
    // trivial cases
    if(x == zero) return y;
    if(y == zero) return x;
    if(x == y) return x;

    // less trivial cases :P
    if((x % two) == zero)
    {
        if((y % two) == one) return greatest_common_divisor(x >> 1, y);
        else return greatest_common_divisor(x >> 1, y >> 1) << 1;
    }
    
    if((y % two) == zero) return greatest_common_divisor(x, y >> 1);
    
    if(x > y) return greatest_common_divisor((x - y) >> 1, y);
    
    return greatest_common_divisor((y - x) >> 1, x);
}

// Extended greatest common divisor
void extended_greatest_common_divisor(Bignum x, Bignum y, Bignum* pq)
{   
    Bignum k;
    Bignum r;
    Bignum temp;
    
    Bignum zero("0");
    
    Bignum a("0");
    Bignum b("1");
    
    Bignum p("1");
    Bignum q("0");
    
    bool s = false;
    
    if(x < y)
    {
        temp = x;
        x = y;
        y = temp;
        s = true;
    }   
    
    while(y != zero)
    {
        k = x / y;
        temp = x;
        x = y;
        y = temp % y;
        temp = a;
        a = p - k * a;
        p = temp;
        temp = b;
        b = q - k * temp;
        q = temp;
    }
    
    if(s == false)
    {
        pq[0] = p;
        pq[1] = q;
    }
    else
    {
        pq[0] = q;
        pq[1] = p;
    }
}

// Less than
int Bignum::operator<(Bignum x)
{
    if(compare(*this,x) == -1) return 1;
    else return 0;
}

// Greater than
int Bignum::operator>(Bignum x)
{
    if(compare(*this,x) == 1) return 1;
    else return 0;
}

// Equal
int Bignum::operator==(Bignum x)
{
    if(!compare(*this,x)) return 1;
    else return 0;
}

// Make the Bignum
Bignum& Bignum::operator=(int x)
{
    ostringstream oss;
    oss << x;
    string value = oss.str();
    Bignum y(value);
    *this = y;
    return *this;
}

// Unequal
int Bignum::operator!=(Bignum x)
{
    if(compare(*this,x) != 0) return 1;
    else return 0;
}

// Less or equal
int Bignum::operator<=(Bignum x)
{
    if(compare(*this,x) == -1 || compare(*this,x) == 0) return 1;
    else return 0;
}

// Greater or equal
int Bignum::operator>=(Bignum x)
{
    if(compare(*this,x) == 1 || compare(*this,x) == 0) return 1;
    else return 0;
}

// Left shift
Bignum Bignum::operator<<(int x)
{
    Bignum bnum = (*this);
    
    int off = 0;
    
    int mk[] = {128, 192, 224, 240, 248, 252, 254, 255};
    
    bnum.l[bnum.l.size() - 1] <<= x;
    
    for(int i = bnum.l.size() - 2; i >= 0; i--)
    {
        off = bnum.l[i] & mk[x - 1];
        bnum.l[i + 1] |= off >> (8 - x);
        bnum.l[i + 1] &= 255;
        bnum.l[i] <<= x;
    }
    
    bnum.l[0] &= 255;
    
    return bnum;
}

// Right shift
Bignum Bignum::operator>>(int x)
{
    Bignum bnum = (*this);
    
    int off = 0;
    
    int mk[] = {1, 3, 7, 15, 31, 63, 127, 255};
    
    bnum.l[0] >>= x;
    
    for(unsigned int i = 1; i < bnum.l.size(); i++)
    {
        off = bnum.l[i] & mk[x - 1];
        bnum.l[i - 1] |= off << (8 - x);
        bnum.l[i] >>= x;
    }
    
    return bnum;
}

// Output
ostream& operator<<(ostream& output, const Bignum& x)
{
    int i;
    if(x.s == false) output << "-";
    output << hex << x.l[x.l.size() - 1];
    
    for(i = x.l.size() - 2; i >= 0; i--)
    {
        output << setw(2) << setfill('0') << hex << x.l[i];
    }
    
    return output;
}

// Main function
int main()
{
    string n1;
    string n2;
    char action;
    Bignum res[2];
    
    cout << "Obowiazujacy format to [liczba] [operator] [liczba]:" <<
endl;
    cin >> n1 >> action >> n2;

    Bignum x(n1);
    Bignum y(n2);

    switch(action)
    {
                   case '+':
                        cout << "Wynik to: " << uppercase << x + y <<
endl;
                        break;
                   case '-':
                        cout << "Wynik to: " << uppercase << x - y <<
endl;
                        break;
                   case '*':
                        cout << "Wynik to: " << uppercase << x * y <<
endl;
                        break;
                   case '?':
                        if(compare(x,y) == 1) cout << x << " > " << y <<
endl;
                        else if(compare(x,y) == -1) cout << x << " < "
<< y << endl;
                        else cout << x << " = " << y << endl;
                        break;
                   case '/':
                        cout << "Wynik to: " << uppercase << x / y <<
endl;
                        break;
                   case '%':
                        cout << "Wynik to: " << uppercase << x % y <<
endl;
                        break;
                   case 'g':
                        cout << "Wynik to: " << uppercase << 
greatest_common_divisor(x,y) <<
endl;
                        break;
                   case 's':
                        cout << "Wynik to: " << uppercase << 
stein_greatest_common_divisor(x,y) <<
endl;
                        break;
                   case 'e':
                        extended_greatest_common_divisor(x,y,res);
                        cout << "Wynik to: " << uppercase << res[0] << 
"," << res[1] << endl;
                        break;
                   default: cout << "Unrecognised operation!" << endl;
    }

    //system("PAUSE");
    return 0;
}

