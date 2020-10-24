#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b;
	char c;

    cout << "Вас приветствует калькулятор" << '\n';
	cout << "Введите первое число, знак действия, второе число " << '\n';
	cin >> a >> c >> b;

	{
		if (c == '+')
		cout << "a+b=" << a + b;
	else if (c == '-')
		cout << "a-b=" << a - b;
	else if (c == '*')
		cout << "a*b=" << a * b;
	else if (c == '/')
		cout << "a/b=" << a / b << endl;
	else
		cout << "ОШИБКА";
	}




    
	//  system("pause");
}