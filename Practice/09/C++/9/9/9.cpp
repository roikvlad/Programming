#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int h1, h2, m1, m2;
	char a, b;
	cout << "Введите время первого человека(час, двоеточие, минуты)" << '\n';
	cin >>h1>>a>>m1 ;

	if (h1 >= 0 and h1 <= 23 and m1 >= 0 and m1 <= 59)

	{
		cout << "Введите время второго человека(час, двоеточие, минуты)" << '\n';
		cin >> h2 >> b >> m2;
		if (h2 >= 0 and h2 <= 23 and m2 >= 0 and m2 <= 59)
		{
			if (h1 == h2 and abs(m2 - m1) <= 15 and abs(m1 - m2) <= 15)
			{
				cout << "Встреча состоится";
			}
			else if ((h2 - h1 == 1 and ((60 - m1) + m2) <= 15 or h2 - h1 == -1 and ((60 - m2) + m1) <= 15 or h2 - h1 == 23 and ((60 - m2) + m1) <= 15 or h2 - h1 == -23 or ((60 - m1) + m2) <= 15))
				    {
					cout << "Встреча состоится";
				    }
			     else
				    {
				    cout << "Встреча не состоится";
				    }
			
		}
		else
		{
			cout << "Неправильно введено время второго человека" << '\n';
		}
	}
	else
	{
		cout << "Неправильно введено время первого человека" << '\n';
	}

}