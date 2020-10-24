#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");

	double a, b, c;
	int n;
	cout << "Введите число, возводимое в степень" << '\n';
	cin >> a;
	b = a;
		cout << "Введите целую степень" << '\n';
	cin >> n;

	if (n > 0)
	{
		for (int i = 1; i <= n; i++)
		{
			a *= b;
			n -= 1;
		}
		cout << "Ответ=" << a << '\n';
	}

	else if(n<0)
	
		{
		for (int i = 0; i < -n; i++)
		{
			a *= b;
			n -= -1;

		}
		a = 1 / a;
			cout << "Ответ=" << a << '\n';
		}
	else
	{
		a = 1;
		cout << "Ответ=" << a;
	}

	
	
//return 0;
}
