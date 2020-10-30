#include <iostream>
using namespace std;
int main() 
{
	int v = 0, b = 0, k = 0, n;
	cout << "Введите количество билетов\n";
	cin >> n;
	
	char* arr = new char[n * 9];
	char a[9]{0};
	for (int i = 0; i < n * 9; i++)
	{
		cin >> arr[i];
	}


	for (int i = 0; i < (n * 9); i++) 
	{
		if ((i == 0 || i % 9 == 0) and int(arr[i]) == 97) 
		{
			a[0] = arr[i];
			b += 1;
			v = i; continue;
		}
		else if (i == 1 || i - v == 1) 
		{
			a[1] = arr[i];
			b += 1; continue;
		}
		else if (i == 2 || i - v == 2) 
		{
			a[2] = arr[i];
			b += 1; continue;
		}
		else if (i == 3 || i - v == 3) 
		{
			a[3] = arr[i];
			b += 1; continue;
		}
		else if (i == 4 || i - v == 4 and int(arr[i]) == 53) 
		{
			a[4] = arr[i];
			b += 1; continue;
		}
		else if (i == 5 || i - v == 5 and int(arr[i]) == 53) 
		{
			a[5] = arr[i];
			b += 1;continue;
		}
		else if (i == 6 || i - v == 6 and int(arr[i]) == 54) 
		{
			a[6] = arr[i];
			b += 1;continue;
		}
		else if (i == 7 || i - v == 7 and int(arr[i]) == 54) 
		{
			a[7] = arr[i];
			b += 1; continue;
		}
		else if (i == 8 || i - v == 8 and int(arr[i]) == 49) 
		{
			a[8] = arr[i];
			b +=  1;

			if (b == 9) 
			{
				for (int h = 0; h < 9; h++) 
				{
					cout << a[h];
					k = 1;
				}
			}
			else 
			{
				k = 0; continue;
			}
		}
	}
	if (k != 1)
	{
		cout << -1 ;
	}
}