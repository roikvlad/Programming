#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int a, b;

	cout << "Введите число a=";
	cin >> a;
	cout << "Введите число b=";
	cin >> b;
	cout << "a+b=" << a + b << '\n' << "a-b=" << a - b << '\n' << "a*b=" << a * b << '\n' << "a/b=" << a / b << '\n';

	double c, d;

	cout << "Введите число c=";
	cin >> c;
	cout << "Введите число d=";
	cin >> d;
	cout << "c+d=" << c + d << '\n' << "c-d=" << c - d << '\n' << "c*d=" << c * d << '\n' << "c/d=" << c / d << '\n';

	int e;
	double g;

	cout << "Введите число e=";
	cin >> e;
	cout << "Введите число f=";
	cin >> g;
	cout << "e+g=" << e + g << '\n' << "e-g=" << e - g << '\n' << "e*g=" << e * g << '\n' << "e/g=" << e / g << '\n';

	double h;
	int i;

	cout << "Введите число h=";
	cin >> h;
	cout << "Введите число i=";
	cin >> i;
	cout << "h+d=" << h + i << '\n' << "h-i=" << h - i << '\n' << "h*i=" << h * d << '\n' << "h/i=" << h / i << '\n';

	//  system("pause");
	
}
