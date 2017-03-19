#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "mat.h"
#include "readfile.h"

Readfile::Readfile()
{
	numInputs = 0;
	rows = 0;
	cols = 0;
	skipChars = 0;
}


void Readfile::readData(string passedFile, Matrix &x, int &k)
{
	numEigen = 1;
	string line;
	bool stdin = false;
	char * space = (char*)" ";

	// If reading from stdin
	if(passedFile =="")
	{
		stdin = true;
	}

	singleFile.open(passedFile);

	// First line: number of x
	if(singleFile.is_open() && !stdin)
	{
		getline(singleFile, line);
		// printf("%s\n", line.c_str());
	}
	else if (stdin)
	{
		getline(cin, line);
	}

	numEigen = atoi(line.c_str());
	// printf("num eign is: %d\n", numEigen);

	// Get each #rows, #cols pair
	if(!stdin)
	{
		getline(singleFile, line);
	}
	else
	{
		getline(cin, line);
	}

	istringstream irw(line);
	string tok;
	getline(irw, tok, ' ');
	rows = stoi(tok);
	getline(irw, tok, '\n');
	cols = stoi(tok);

	// printf("numx is: %d\n", numx);
	// printf("rows: %d\t", rows);
	// printf("cols: %d\n", cols);


	int xArrCount = 0;
	initArr();


	for(int i = 0; i < rows; i++)
	{
		//Get a line for each row
		if(!stdin)
		{
			getline(singleFile, line);
		}
		else
		{
			getline(cin, line);
		}

		istringstream irw(line);
		string tok;

		for(int j = 0; j < cols; j++)
		{
			getline(irw, tok, ' ');
			try
			{
				xArr[xArrCount] = stod(tok);
			}
			// Scrub extra leading space?
			catch(std::exception& e)
			{
				getline(irw, tok, ' ');
			}
			xArrCount++;
		}
	}

	x = new Matrix(rows, cols, xArr, "x");
	// x.print();
	k = numEigen;


	deleteArr();
}


void Readfile::initArr()
{
	xArr = new double[rows*cols];
}

void Readfile::deleteArr()
{
	delete[] xArr;
}
