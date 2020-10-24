#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	double s, l1, l2, r1, r2, x1, x2 ;

	cout<< "Введите s, промежуток l1--r1 и промежуток l2--r2" << '\n' ;
	cin>> s >> l1 >> r1 >> l2 >> r2 ;

	if(l1 <= r1 and l2 <= r2)
	{
		if(l1 + l2 <=s and r1 + r2 >= s)
		{
			x2 = s-l1;

			if( x2 - r2 > 0)
			{
				x1 = l1+x2-r2 ;
				x2 = s-x1 ;
			}
			else
			{
				x1 = l1 ;
			}
			cout<< x1 << ' ' << x2 ;
		}
		else 
		{
			cout<< -1 ;
		}

	}
	else
	{
		cout<< "Неправильно введён диапазон" ;
	}

}