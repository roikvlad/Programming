#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	
	int n, y, b, c = 1 ;
	
	cout << "Угадай число от 0-100 у тебя 5 попыток." << '\n';

	while (c > 0)
	{
		y = rand() % 100;


		for (int i = 0; i < 5; i++)
		{
			cin >> n;
			if (n == y)
			{
				cout << "Поздравляю! Вы угадали" << '\n';
				break;
			}
			else if (n < y and i != 4)
			{
				cout << "Загаданное число больше" << '\n';
			}
			else if (n > y and i != 4)
			{
				cout << "Загаданное число меньше" << '\n';
			}
			else if (i == 4)
			{
				cout << "Вы проиграли. Было загадано: " << y << "\n";
			}


		}

		cout << "Хотите начать сначала?(1 - ДА )" << '\n';
		cin >> b;
		if (b != 1)
		{
			break;
		}
	}
}