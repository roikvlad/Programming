#include <iostream>
#include "factorial.h"
#include "sochetanie.h"
#include "sin.h"
#include <cstdlib>
#include <iomanip>


using namespace std;

int main()
{
	cout << "n\tn! \n";
	for (int n = 1; n <= 10; n += 1) 
	cout << n << "\t" << factorial(n) << "\n" ;

	cout << "\nx\tsin(x) \n";

	for (double x = 0; x <= 0.785399; x += 0.0174533)
	{
		cout<< fixed;
		cout<< setprecision(5) << x << "\t" << sin(x, 5) << "\n" ;
	}
	
	cout<< "\nk\tC(k, 10) \n";

	for (int k = 1; k <= 10; k += 1) 
		cout<< k << "\t" << sochetanie(10, k) << "\n" ;

	return 0;
}