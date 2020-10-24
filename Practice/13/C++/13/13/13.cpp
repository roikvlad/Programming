#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int n, a, b;
	cout << "Введите число для проверки" << '\n';
	cin >> n;
	b = pow(10, 10);
	if (n >= 2 and n <= b)
	{
		a = 0;
		for (int i = 2; i < 10; i++)
		{
			if (n % i == 0)
			{
				a = 1;
			}
		}
		if (a and n!=2 and n!=3 and n!=5 and n!=7)
		{
			cout << "Составное число";
		}
		else
		{
			cout << "Простое число";
		}
	}
	else
	{
		cout << "Число n не соответствует условию";
	}

}