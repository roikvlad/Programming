#include <iostream>
#include <String.h>
#include <iomanip>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    int i, j, p=0, t=0, n, c, l = 0;;
    double a;
 
    string st;
    cout << "Введите стоп слово\n";
    cin >> st;

    char str[] = "hallo, klempner, das, ist, fantastisch, fluggegecheimen"; 

    int arr = sizeof(str) - 1;

     for (int i = 0; i < arr; i++)
    {
        if (str[i] == char(' ') or str[i] == char(','))
           l += 1;
    }

     a = arr - l;
   
    double s = 1 ;
    c = st.length();
    for (int i = 0; i < c ; i++)
    {
        int b = 0;
        for (int j = 0; j < arr ; j++)
        {
            if (st[i] == str[j])
            {
                b += 1;
            }
            if (j == a - 1);

        }
        s *= b / a;
        if (i == c - 1)
        {
            cout << setprecision(16) << s;
        }
    }
    return 0;
}

