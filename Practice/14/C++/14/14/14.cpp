#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int n, x, a, c, d;
	double b;
	cout << "Введите число" << '\n';
	cin >> n;
	b = pow(10, 15);
	x = 1;
	c = 0;

	if (n >= 0 and n <= b)
	{
		if (n == 0)
		{
			a = 0;
			cout << "Количество=" << a;
		}
		else
		{
			for (int i = 1; i <= n; i++)
			{
				x *= 2;
				c = c + 1;
				if (x > n)
				{
					d = c;
					cout << "Количество=" << d;
					break;
				}
			}

		}
	}
	else
	{
		cout << "Ваше число не попадает в диапозон.";
	}
}