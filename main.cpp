#include <fstream>
#include "nrmare.h"
#define LGMAX 1000

using namespace std;

ifstream fin("descfib.in");
ofstream fout("descfib.out");

NrMare n; ///numarul citit

NrMare fib[LGMAX]; ///sirul generat
int con;
bool rez[LGMAX]; ///Apare fib[i] in descompunere?
int nr;

void fibonacci(); ///generarea sirului lui Fibonacci

int main()
{
    int i;
    fin>>n;
    fibonacci();
    while (n[0]!=0||n.getlg()!=1) ///cat timp n nu este egal cu 0
        {
            for (i=con; i>=0; i--) ///parcurg sirul de la mai mare la mai mic
                {
                    if (n>=fib[i]) ///fib[i] incape in n
                        {
                            nr++; ///numarul de termeni din descompunere creste
                            rez[i]=1; ///fib[i] apare in descompunere
                            n-=fib[i];
                        }
                }
        }
    fout<<nr<<'\n'; ///nr de termeni din descompunere
    for (i=0; i<=con; i++) ///afisez termenii care apar in ordine crescatoare
        {
            if (rez[i])
                fout<<fib[i]<<'\n';
        }
    return 0;
}

void fibonacci()
{
    NrMare f1(1), f2(1), f3; ///termenii initiali
    fib[0]=f1;
    for (con=1; f3<=n; con++) ///generez cat timp f3<=n
    {
        f3=f1+f2;
        fib[con]=f3;
        f1=f2;
        f2=f3;
    }
    con--;
}
