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

	// cout << "num features: " << numFeatures << endl;
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
		// cout << "feature: " << feature << endl;
		features.push_back(feature);
		rowcol >> tok;
		numValues = stoi(tok);
		// cout << "num Values: " << numValues << endl;

		map <string, int> tmp;
		for (int j = 0; j < numValues; j++)
		{
			rowcol >> tok;
			tmp[tok] = j;
		}
		strmap.push_back(tmp);
		// for (auto elem: tmp)
		// {
		// 	cout << elem.first << ": " << elem.second << "  ";
		// }
		// printf("\n");
	}

	cols = numFeatures + 1;
	if(!stdin)
	{
		getline(singleFile, line);
	}
	else
	{
		getline(cin, line);
	}
	istringstream rowcol(line);
	rowcol >> rows;

	printf("rows: %d, cols: %d\n",rows, cols );

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
			irw >> tok;
			// cout << tok << "";
			int code = strmap[j][tok];
			// cout << code << " ";
			xArr[xArrCount] = code;
			xArrCount++;
		}
		// cout << endl;
	}
	//
	x = new Matrix(rows, cols, xArr, "x");
	// x.print();
	deleteArr();
	// for (auto m : features)
	// {
	// 	cout << m << endl;
	// }
}


void Readfile::initArr()
{
	xArr = new double[rows*cols];
}

void Readfile::deleteArr()
{
	delete[] xArr;
}
