#include "factorial.h"
#ifndef SIN_H
#define SIN_H

double sin(double x, double k)
{
	double tern = x ;
	double Sum = tern ;
	for (double i = 1; i <= k; i += 1) 
	{
		tern = -( (x * x) / ( (2 * i) * (2 * i + 1) ) ) * tern ;
		Sum += tern  ;
	}
	return Sum;
}
#endif