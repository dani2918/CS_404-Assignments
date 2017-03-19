#include "mat.h"
#include "readfile.h"
#include "compute.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	Matrix x = Matrix();
	int k = 0;
	Readfile rf;


	if(argc == 2)
	{
		string argFile = argv[1];
		// printf("%s\n", argFile.c_str());
		rf.readData(argFile, x, k);
	}
	else if(argc == 1)
	{
		rf.readData("", x, k);
	}
	else
	{
		printf("Error - Usage: '$./pca filename'\n");
	}
	Compute compute(k);
	compute.calcZ(x);
	compute.covariance(x);
	compute.eigen(x);
	compute.translate(x);
	compute.component();

	return 0;
}
