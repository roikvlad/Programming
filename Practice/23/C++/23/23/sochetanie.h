#include "factorial.h"
#ifndef SOCHETANIE_H
#define SOCHETANIE_H

int sochetanie(int n, int k)
{
	return( factorial(n) ) / ( ( factorial(k) ) * ( factorial(10 - k) ) ) ;
}
#endif