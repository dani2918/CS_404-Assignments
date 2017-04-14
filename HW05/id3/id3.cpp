#include "mat.h"
#include "readfile.h"
#include "compute.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include<map>

using namespace std;

int main(int argc, char *argv[])
{
	vector< map<int, string>> mp;
	initRand();
	Matrix x = Matrix();
	int k = 0;
	vector<string> names;

	Readfile rf;

	if(argc == 2)
	{
		string argFile = argv[1];
		// printf("%s\n", argFile.c_str());
		rf.readData(argFile, x, k, names, mp);
	}
	else if(argc == 1)
	{
		rf.readData("", x, k, names, mp);
	}
	else
	{
		printf("Error - Usage: '$./id3 < filename \n");
	}



	Compute compute(x, names, mp);


	return 0;
}
