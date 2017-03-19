

// Necessary so that mat.map can use a function pointer
// Instead of a method pointer

#include "util.h"
#include <stdio.h>
#include <math.h>

double utilTransferThreshold;
double slope; 

void setTransferThreshold(double x)
{
	utilTransferThreshold = x;
	// printf("Transfer thresh is: %f\n", utilTransferThreshold);
}

void setSlope(double x)
{
	slope = x;
}



double transferFunc(double x)
{
	return 1/(1+exp(-4 * slope * x));
}

// {
// 	if(x > utilTransferThreshold)
// 	{
// 		return 1.0;
// 	}
// 	else
// 	{
// 		return 0.0;
// 	}
// }