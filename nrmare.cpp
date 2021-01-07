#include "nrmare.h"

///constructori
NrMare::NrMare(int x)
{for (lg=0; lg<LGMAX; lg++) c[lg]=0;
 //ctor
 if (x==0) {lg=1; c[0]=0;}
     else
     {lg=0;
      while (x) {c[lg++]=x%10; x/=10;}
     }
}

NrMare::NrMare(char *s)
{int i;
 for (lg=0; lg<LGMAX; lg++) c[lg]=0;
 for (lg=0; s[lg]; lg++);
 for (i=0; i<lg; i++) c[i]=s[lg-1-i]-'0';
}

///copiere
NrMare::NrMare(const NrMare& a)
{int i;
 //copy ctor
 lg=a.lg;
 for (i=0; i<lg; i++) c[i]=a.c[i];
}

///atribuire
NrMare& NrMare::operator=(const NrMare& a)
{int i;
    //if (this == &a) return *this; // handle self assignment
    //assignment operator
    lg=a.lg;
    for (i=0; i<lg; i++) c[i]=a.c[i];
    return *this;
}

///operatori de citire si scriere
istream& operator>> (istream& in, NrMare& a)
{
 char sir[LGMAX+1];
 in>>sir;
 a=NrMare(sir);
 return in;
}

ostream& operator<<(ostream& out, const NrMare& a)
{int i;
 for (i=a.lg-1; i>=0; i--) out<<a.c[i];
 return out;
}

///operatori unari
NrMare& NrMare::operator++()///forma prefixata
{int i;
 ///cat timp am 9 il fac 0
 for (i=0; i<lg && c[i]==9; i++) c[i]=0;
 if (i<lg) c[i]++;
    else
    {if (lg==LGMAX-1) throw("OVERFLOW");
     c[lg++]=1; }
 return *this;
}

NrMare& NrMare::operator--()///forma prefixata
{int i;
 if (lg==1 && c[0]==0) ///numarul este 0
    throw("UNDERFLOW");
 for (i=0; c[i]==0; i++) c[i]=9;
 c[i]--;
 if (lg>1 && c[lg-1]==0) lg--;
 return *this;
}

NrMare NrMare::operator++(int fictiv)///forma postfixata
{NrMare temp=*this;
 ++(*this);
 return temp;
}

NrMare NrMare::operator--(int fictiv)///forma postfixata
{
  NrMare temp=*this;
 --(*this);
 return temp;
}

int NrMare::operator[] (const int poz)
{ if (poz<0 || poz>=lg) throw("RANGE CHECK ERROR");
  return c[poz];
}

NrMare::operator int ()
{
 int i, rez=0, p10=1;
 for (i=0; i<lg; i++) {rez+=c[i]*p10; p10*=10;}
 return rez;
}

///operatori aritmetici
NrMare operator+ (const NrMare& a, const NrMare& b)
{ int i, t, val;
  NrMare s;
  if (a.lg<b.lg)
     s.lg=b.lg;
     else
     s.lg=a.lg;
  for (t=i=0; i<s.lg; i++)
      {
       val=a.c[i]+b.c[i]+t;
       s.c[i]=val%10;
       t=val/10;
      }
  if (t) s.c[s.lg++]=t;
  return s;
}

NrMare operator+ (const NrMare& a, int b)
{
 NrMare s, temp(b);
 s=a+temp;
 return s;
}

NrMare operator+ (int a, const NrMare& b)
{NrMare s, temp(a);
 s=b+temp;
 return s;
}

NrMare& NrMare::operator+=(const NrMare& a)
{NrMare temp=*this+a;
 *this=temp;
 return *this;
}

NrMare operator- (const NrMare& a, const NrMare& b)
{
    int i, t=0, val;
    NrMare d;
    d.lg=a.lg;
    for (i=0; i<d.lg; i++)
        {
            val=a.c[i]-b.c[i]+t;
            if (val<0)
                {
                    d.c[i]=val+10;
                    t=-1;
                }
                else
                {
                    d.c[i]=val;
                    t=0;
                }
        }
    while (d.lg>1&&d.c[d.lg-1]==0)
            d.lg--;
    return d;
}

NrMare operator- (const NrMare& a, int b)
{
    NrMare d, temp(b);
    d=a-temp;
    return d;
}

NrMare operator- (int a, const NrMare& b)
{
    NrMare d, temp(a);
    d=temp-b;
    return d;
}

NrMare& NrMare::operator-=(const NrMare& a)
{
NrMare temp=*this-a;
 *this=temp;
 return *this;
}


NrMare operator* (const NrMare& a, const NrMare& b)
{
    NrMare m;
    int t=0, i, j, val;
    if ((a.lg==1&&a.c[0]==0) || (b.lg==1&&b.c[0]==0))
        {
            m.lg=1;
            m.c[0]=0;
            return m;
        }
    for (i=0; i<=a.lg; i++)
        for (j=0; j<b.lg; j++)
            {
                m.c[i+j]+=a.c[i]*b.c[j];
            }
    m.lg=a.lg+b.lg-1;
    for (i=0; i<m.lg; i++)
        {
            val=m.c[i]+t;
            m.c[i]=val%10;
            t=val/10;
        }
    while (t)
        {
            m.c[m.lg++]=t%10;
            t=t/10;
        }
    return m;
}

NrMare operator* (const NrMare& a, int b)
{
    NrMare m, temp(b);
    m=a*temp;
    return m;
}

NrMare operator* (int a, const NrMare& b)
{
   NrMare m, temp(a);
   m=temp*b;
   return m;
}

NrMare& NrMare::operator*=(const NrMare& a)
{
    NrMare temp=*this*a;
    *this=temp;
    return *this;
}

NrMare operator/ (const NrMare& a, int b)
{
    NrMare div;
    int i, rest;
    div.lg=a.lg;
    rest=0;
    for (i=a.lg-1; i>=0; i--)
        {
            rest=rest*10+a.c[i];
            div.c[i]=rest/b;
            rest=rest%b;
        }
    while (div.lg>1&&div.c[div.lg-1]==0)
        div.lg--;
    return div;
}

NrMare operator% (const NrMare& a, int b)
{
    NrMare div;
    int i, rest;
    div.lg=a.lg;
    rest=0;
    for (i=a.lg-1; i>=0; i--)
        {
            rest=rest*10+a.c[i];
            div.c[i]=rest/b;
            rest=rest%b;
        }
    while (div.lg>1&&div.c[div.lg-1]==0)
        div.lg--;
    NrMare aux(rest);
    return aux;
}

///operatori de egalitate si relationari
bool operator== (const NrMare& a, const NrMare& b)
{int i;
 if (a.lg!=b.lg) return 0;
 for (i=0; i<a.lg && a.c[i]==b.c[i]; i++);
 return i==a.lg;
}

bool operator== (int a, const NrMare& b)
{
  NrMare temp(a);
  return temp==b;
}

bool operator== (const NrMare& a, int b)
{
    NrMare temp(b);
    return temp==a;
}
bool operator!= (const NrMare& a, const NrMare& b)
{
    return !(a==b);
}

bool operator!= (int a, const NrMare& b)
{
    NrMare temp(a);
    return temp!=b;
}

bool operator!= (const NrMare& a, int b)
{
    NrMare temp(b);
    return a!=temp;
}

bool operator< (const NrMare& x, const NrMare& y)
{
   int i;
    if (x.lg>y.lg)
        return 0;
    if (y.lg>x.lg)
        return 1;
    if (x.lg==y.lg)
        {
            for (i=x.lg-1; i>=0; i--)
                {
                    if (x.c[i]>y.c[i])
                        return 0;
                    if (y.c[i]>x.c[i])
                        return 1;
                }
        }
    return 0;
}

bool operator< (int a, const NrMare& b)
{
    NrMare temp(a);
    return temp<b;
}

bool operator< (const NrMare& a, int b)
{
    NrMare temp(b);
    return a<temp;
}

bool operator> (const NrMare& x, const NrMare& y)
{
   int i;
    if (x.lg>y.lg)
        return 1;
    if (y.lg>x.lg)
        return 0;
    if (x.lg==y.lg)
        {
            for (i=x.lg-1; i>=0; i--)
                {
                    if (x.c[i]>y.c[i])
                        return 1;
                    if (y.c[i]>x.c[i])
                        return 0;
                }
        }
    return 0;
}


bool operator> (int a, const NrMare& b)
{
    NrMare temp(a);
    return temp>b;
}

bool operator> (const NrMare& a, int b)
{
    NrMare temp(b);
    return a>temp;
}

bool operator<= (const NrMare& x, const NrMare& y)
{
    int i;
    if (x.lg>y.lg)
        return 0;
    if (y.lg>x.lg)
        return 1;
    if (x.lg==y.lg)
        {
            for (i=x.lg-1; i>=0; i--)
                {
                    if (x.c[i]>y.c[i])
                        return 0;
                    if (y.c[i]>x.c[i])
                        return 1;
                }
        }
    return 1;
}

bool operator<= (int a, const NrMare& b)
{
    NrMare temp(a);
    return temp<=b;
}

bool operator<= (const NrMare& a, int b)
{
    NrMare temp(b);
    return a<=temp;
}

bool operator>= (const NrMare& x, const NrMare& y)
{
   int i;
    if (x.lg>y.lg)
        return 1;
    if (y.lg>x.lg)
        return 0;
    if (x.lg==y.lg)
        {
            for (i=x.lg-1; i>=0; i--)
                {
                    if (x.c[i]>y.c[i])
                        return 1;
                    if (y.c[i]>x.c[i])
                        return 0;
                }
        }
    return 1;
}

bool operator>= (int a, const NrMare& b)
{
    NrMare temp(a);
    return temp>=b;
}

bool operator>= (const NrMare& a, int b)
{
    NrMare temp(b);
    return a>=temp;
}

///getteri
int NrMare::getlg()
{
    return lg;
}
