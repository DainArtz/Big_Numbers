#ifndef NRMARE_H
#define NRMARE_H
#define LGMAX 1000
#include <iostream>

using namespace std;

class NrMare
{   private:
        ///nr naturale mari
        int lg;
        int c[LGMAX];

    public:

        ///constructori
        NrMare(int x=0);
        NrMare(char *s);

        ///copiere
        NrMare(const NrMare& other);

        ///atribuiri
        NrMare& operator=(const NrMare& a);
        NrMare& operator+=(const NrMare& a);
        NrMare& operator-=(const NrMare& a);
        NrMare& operator*=(const NrMare& a);

        ///operatori unari
        NrMare& operator++();///forma prefixata
        NrMare& operator--();///forma prefixata
        NrMare operator++(int fictiv);///forma postfixata
        NrMare operator--(int fictiv);///forma postfixata

        int operator[] (const int poz);

        operator int ();

        ///operatori binari aritmetici
        friend NrMare operator+ (const NrMare& a, const NrMare& b);
        friend NrMare operator+ (const NrMare& a, int b);
        friend NrMare operator+ (int a, const NrMare& b);
        friend NrMare operator- (const NrMare& a, const NrMare& b);
        friend NrMare operator- (const NrMare& a, int b);
        friend NrMare operator- (int a, const NrMare& b);
        friend NrMare operator* (const NrMare& a, const NrMare& b);
        friend NrMare operator* (const NrMare& a, int b);
        friend NrMare operator* (int a, const NrMare& b);
        friend NrMare operator/ (const NrMare& a, int b);
        friend NrMare operator% (const NrMare& a, int b);

        ///operatori binari de egalitate si relationali
        friend bool operator== (const NrMare& a, const NrMare& b);
        friend bool operator== (int a, const NrMare& b);
        friend bool operator== (const NrMare& a, int b);
        friend bool operator!= (const NrMare& a, const NrMare& b);
        friend bool operator!= (int a, const NrMare& b);
        friend bool operator!= (const NrMare& a, int b);
        friend bool operator< (const NrMare& a, const NrMare& b);
        friend bool operator< (int a, const NrMare& b);
        friend bool operator< (const NrMare& a, int b);
        friend bool operator> (const NrMare& a, const NrMare& b);
        friend bool operator> (int a, const NrMare& b);
        friend bool operator> (const NrMare& a, int b);
        friend bool operator<= (const NrMare& a, const NrMare& b);
        friend bool operator<= (int a, const NrMare& b);
        friend bool operator<= (const NrMare& a, int b);
        friend bool operator>= (const NrMare& a, const NrMare& b);
        friend bool operator>= (int a, const NrMare& b);
        friend bool operator>= (const NrMare& a, int b);

        ///operatori de citire si scriere
        friend istream& operator>> (istream& in, NrMare& a);
        friend ostream& operator<<(ostream& out, const NrMare& a);

        ///getteri
        int getlg();
};

#endif // NRMARE_H
