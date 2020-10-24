#include <iostream>

using namespace std;

int main()
{
		setlocale (LC_ALL, "Russian");
	
	double x, x0, v0, t, a, g ;
	g=9.8 ;

	cout << "Введите x0, v0, t" << '\n';
	cin >> x0; cin >> v0; cin >> t;
	a = g;

	x = x0 + v0 * t - a * t * t / 2;
		cout << "Конечная координата х=" << x0-x ;
		

	//  system("pause");
}