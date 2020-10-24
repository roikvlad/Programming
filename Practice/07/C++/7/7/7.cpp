#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	double z, a, b, c, d, e, k, x1, y1, x2, y2, x3, y3, p, s;
	cout << "Введите способ вычесления (1-через строны, 2-через векторы)" << '\n';
	cin >> z;

	if (z == 1)

	{
		cout << "Введите стророны a, b, c" << '\n';
		cin >> a;
		cin >> b;
		cin >> c;

		{
			if (((a + b) > c) and ((b + c) > a) and ((a + c) > b) and (a > 0) and (b > 0) and (c > 0))

			{
				p = (a + b + c) / 2;
				s = sqrt(p * (p - a) * (p - b) * (p - c));
				cout << "Площадь треугольника S=" << s << '\n';
			}

			else

			{
				cout << "Ошибка. Данного треугольника не существует" << '\n';
			}
		}
	}

	else if (z == 2)
	{

		cout << "Введите координаты в виде x1 y1 x2 y2 x3 y3" << '\n';
		cin >> x1 >> y1;
		cin >> x2 >> y2;
		cin >> x3 >> y3;
		d = sqrt( (x2 -x1)*(x2 - x1) +  (y2 - y1)*(y2 - y1) );
		e = sqrt( (x3 - x2)*(x3 - x2) + (y3 - y2)*(y3 - y2) );
		k = sqrt( (x1 - x3)*(x1 - x3) + (y1 - y3)*(y1 - y3) );
			
		{ if (((d + e) > k) and ((d + k) > e) and ((e + k) > d) and (k > 0) and (d > 0) and (e > 0))
			{
			p = (d + e + k) / 2;
			s = sqrt(p * (p - d) * (p - e) * (p - k));
			cout << "Площадь треугольника S=" << s << '\n';
			}


			else

				{
				cout << "Ошибка. Данного треугольника не существует" << '\n';
				}
		}
			 
	}
	
	else
		{
		cout << "Введите правильно способ подсчета (1 или 2)" << '\n';
	    }
   
}

	








	
	


