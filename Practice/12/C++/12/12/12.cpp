#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	unsigned int n, a;
	
	cout << "Введите число для вычисления факториала" << '\n' ;
	cin >> n;
	
	a = 1;

	for (int i = 2; i <= n; i++)
	{
		a = a * i;
	}

	cout << "Ответ=" << a;

}