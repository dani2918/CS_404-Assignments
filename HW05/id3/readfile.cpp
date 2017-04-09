#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "mat.h"
#include "readfile.h"


Readfile::Readfile()
{
	numFeatures = 0;
	rows = 0;
	cols = 0;
}


void Readfile::readData(string passedFile, Matrix &x, int &k)
{
	string line;
	bool stdin = false;
	// If reading from stdin
	if(passedFile =="")
	{
		stdin = true;
	}
	singleFile.open(passedFile);
	if(singleFile.is_open() && !stdin)
	{
		getline(singleFile, line);
		// printf("%s\n", line.c_str());
	}
	else if (stdin)
	{
		getline(cin, line);
	}


	istringstream irw(line);
	string tok;
	getline(irw, tok, ' ');
	numFeatures = stoi(tok);

	cout << "num features: " << numFeatures << endl;
	for(int i = 0; i <= numFeatures; i++)
	{
		if(!stdin)
		{
			getline(singleFile, line);
		}
		else
		{
			getline(cin, line);
		}
		istringstream rowcol(line);
		rowcol >> tok;
		feature = tok;
		cout << "feature: " << feature << endl;
		rowcol >> tok;
		numValues = stoi(tok);
		cout << "num Values: " << numValues << endl;

		map <int, string> tmp;
		for (int j = 0; j < numValues; j++)
		{
			rowcol >> tok;
			tmp[j] = tok;
		}
		strmap.push_back(tmp);
		for (auto elem: tmp)
		{
			cout << elem.first << ": " << elem.second << "  ";
		}
		printf("\n");
	}


	// getline(irw, tok, '\n');
	// timesComputed = stoi(tok);

	//First & Second inputs, same line
	// printf("kgrps is: %d\n", kExpGrps);

	// Get each #rows, #cols pair
	// if(!stdin)
	// {
	// 	getline(singleFile, line);
	// }
	// else
	// {
	// 	getline(cin, line);
	// }
	//
	// istringstream rowcol(line);
	// getline(rowcol, tok, ' ');
	// rows = stoi(tok);
	// getline(rowcol, tok, '\n');
	// cols = stoi(tok);

	// printf("rows: %d\t", rows);
	// printf("cols: %d\n", cols);

	// int xArrCount = 0;
	// initArr();
	// for(int i = 0; i < rows; i++)
	// {
	// 	//Get a line for each row
	// 	if(!stdin)
	// 	{
	// 		getline(singleFile, line);
	// 	}
	// 	else
	// 	{
	// 		getline(cin, line);
	// 	}
	//
	// 	istringstream irw(line);
	// 	string tok;
	//
	// 	for(int j = 0; j < cols; j++)
	// 	{
	// 		getline(irw, tok, ' ');
	// 		while(strcmp(tok.c_str(), "") == 0)
	// 		{
	// 			getline(irw, tok, ' ');
	// 		}
	// 		xArr[xArrCount] = stod(tok);
	// 		xArrCount++;
	// 	}
	// }
	//
	// x = new Matrix(rows, cols, xArr, "x");
	// // x.print();
	// // k = kExpGrps;
	//
	//
	// deleteArr();
}


void Readfile::initArr()
{
	xArr = new double[rows*cols];
}

void Readfile::deleteArr()
{
	delete[] xArr;
}
