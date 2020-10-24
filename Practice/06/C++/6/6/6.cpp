#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	double a, b, c, d, x ;
	cout << "Введите a, b, c" << '\n';
	cin >> a ;
	cin >> b ;
	cin >> c ;

	if (a == 0)
	{
		cout << "x=" << -c / b << endl;
	}
	else
	{
		d = b * b - 4 * a * c;
		if (d < 0)
		{
			cout << "Уравнение не имеет решений";
		}
		else if (d == 0)
		{
			cout << "x=" << -b / (2 * a);
		}
		else
		{
			cout << "x1=" << (-b + sqrt(d)) / (2 * a) << '\n' << "x2=" << (-b - sqrt(d)) / (2 * a) << endl;
		}
	}

	



	//  system("pause");
}