#include <stdio.h>
#include <string>
#include <sstream>
#include "mat.h"
#include "readfile.h"





//c++11 dependent
// Readfile::Readfile() : locNames {"/Users/MattDaniel/Desktop/CS_404/HW01/testDataA1/irisData.in", 
// 	"/Users/MattDaniel/Desktop/CS_404/HW01/testDataA1/majority.in",
// 	"/Users/MattDaniel/Desktop/CS_404/HW01/testDataA1/or.in",
// 	"/Users/MattDaniel/Desktop/CS_404/HW01/testDataA1/twologic.in",
// 	"/Users/MattDaniel/Desktop/CS_404/HW01/testDataA1/xor.in",
// 	"/Users/MattDaniel/Desktop/CS_404/HW01/testDataA1/xor2.in"}
// {

// }

Readfile::Readfile()
{
	numInputs = 0;
	rows = 0;
	cols = 0;
	skipChars = 0;
}


void Readfile::readData(string passedFile, Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	string line;
	char * space = (char*)" ";
	
	singleFile.open(passedFile);

	// First line: number of inputs
	if(singleFile.is_open())
	{
		getline(singleFile, line);
		// printf("%s\n", line.c_str());
	}
	numInputs = atoi(line.c_str());

	for(int i = 0; i < 2; i++)
	{
		// Get each #rows, #cols pair

		getline(singleFile, line);
		istringstream irw(line);
		string tok;
		getline(irw, tok, ' ');
		rows = stoi(tok);
		getline(irw, tok, '\n');
		cols = stoi(tok);

		// printf("numInputs is: %d\n", numInputs);
		// printf("rows: %d\t", rows);
		// printf("cols: %d\n", cols);


		int xArrCount = 0;
		int tArrCount = 0;
		initArr();


		for(int i = 0; i < rows; i++)
		{
			
			//Get a line for each row
			getline(singleFile, line);
			istringstream irw(line);
			string tok;
			for(int j = 0; j < cols; j++)
			{
				getline(irw, tok, ' ');

				// If we have an input not a target
				if(j < numInputs)
				{
					xArr[xArrCount] = stod(tok);
					xArrCount++;
				}
				else
				{
					tArr[tArrCount] = stod(tok);
					tArrCount++;
				}
			}
		}

		// Training Data - first pass
		if(i == 0)
		{
			inputs = new Matrix(rows, numInputs, xArr, "x");
			// inputs.print();

			targets = new Matrix(rows, cols - numInputs, tArr, "t");
			// targets.print();
		}

		// Test data = second pass
		if(i == 1)
		{
			testDat = new Matrix(rows, numInputs, xArr, "testDat"); 
			// testDat.print();
		}

		deleteArr();
		

	}


}

void Readfile::initArr()
{	

	xArr = new double[rows*numInputs];
	tArr = new double[rows*(cols-numInputs)];

}

void Readfile::deleteArr()
{
	
	delete[] xArr;
	delete[] tArr;
}


// char * Readfile::split(char * orig, char * token)
// {
// 	skipChars = 0;
// 	char * splitStr;
// 	while(orig != token)
// 	{
// 		skipChars++;
// 		orig++;
// 	}
// 	strcpy(splitStr, )
// 	return splitStr;
// }