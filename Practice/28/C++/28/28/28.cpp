#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void print_factorization(unsigned int n) 
{
    if (n < 4) 
    {
        cout << n ; 
    }
    else
    {
        std::vector<int> b ;
        int a = 2 , k = 1 , k1 = 1 , n1 = n ;
        while (a) 
        {
            if (!(n1 % a)) 
            {
                n1 = n1 / a ;
                b.push_back(a) ;
                a = 2 ;
            }
            else 
            { 
                a++; 
            }
            if ((n1 / a) == 1) 
            {

                b.push_back(n1) ;
                a = 0; 
            }
        }
        while ((b.size()) > 0) 
        {
            if ((b.size()) == 1) 
            {
                cout << b[0] ;
                b.clear() ;
            }
            else 
            {
                for (int q = 0; q < (b.size() - 1); q++) 
                {
                    if (b.size() < 2) 
                    {
                        q = b.size() + 10;
                    }
                    else 
                    {
                        if (b[q] == b[q + 1]) 
                        {
                            if (q == (b.size() - 2)) 
                            {
                                cout << b[0] << "^" << b.size() ;
                                b.clear() ;
                            }
                        }
                        else 
                        {
                            k = b[0];
                            k1 = q + 1;
                            auto begin = b.cbegin() ;
                            b.erase(begin, begin + q + 1) ;
                            if (k1 > 1) 
                            {
                                cout << k << "^" << k1 << "*" ;
                            }
                            else cout << k << "*" ;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian") ;

    int a ;
    cin >> a ;

    print_factorization(a) ;

    cout << "\n" ;

    system("pause") ;
    return 0 ;
}