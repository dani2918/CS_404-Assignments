

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
	return (x > utilTransferThreshold ? 1.0 : 0.0);
}