#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	double a, b;

	cout << "Введите число a=";
	cin >> a;
	cout << "Введите число b=";
	cin >> b;
	a = a + b;
	b = a - b;
	a = a - b;
	cout << "Теперь a=" << a << ' ' << "b=" << b <<'\n' ;


	double c, d, g;

	cout << "Введите число c=";
	cin >> c;
	cout << "Введите число d=";
	cin >> d;
	g = d;
	d = c;
	c = g;
	cout << "Теперь c=" << c << ' ' << "d=" << d;


	//  system("pause");

}
