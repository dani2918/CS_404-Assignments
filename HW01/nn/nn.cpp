#include "nn.h"
#include "mat.h"
#include "readfile.h"
#include "train.h"
#include "test.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	Matrix targets = new Matrix;
	Matrix inputs = new Matrix;
	Matrix testDat = new Matrix;
	Readfile rf;
	

	if(argc == 2)
	{
		string argFile = argv[1];
		// printf("%s\n", argFile.c_str());
		rf.readData(argFile, inputs, targets, testDat);
	}
	else if(argc == 1)
	{
		rf.readData("", inputs, targets, testDat);
	}
	else
	{
		printf("Error - Usage: '$./nn filename'\n");
	}

	Train train(inputs,targets,testDat);

	// train.normalizeAll(inputs, targets, testDat);
	// train.printAll(inputs, targets, testDat);
	// printf("\n\n\n");

	train.doTraining(inputs, targets);
	// train.getW().print("TESTING");

	Test test(testDat, train.getW());

	// printf("inputs max rows: %d\n", inputs.maxRows());

	return 0;
}