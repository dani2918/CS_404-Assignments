

// Necessary so that mat.map can use a function pointer
// Instead of a method pointer

#include "util.h"
#include <stdio.h>

double utilTransferThreshold;

void setTransferThreshold(double x)
{
	utilTransferThreshold = x;
	// printf("Transfer thresh is: %f\n", utilTransferThreshold);
}



double transferFunc(double x)
{
	if(x > utilTransferThreshold)
	{
		return 1.0;
	}
	else
	{
		return 0.0;
	}
}