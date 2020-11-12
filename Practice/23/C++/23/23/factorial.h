#pragma once
#include <iostream>

int factorial(int n)
{
	int a = 1 ;
	for (int i = 1; i <= n; i += 1) {
		a *= i ;
	}
	return a ;
}