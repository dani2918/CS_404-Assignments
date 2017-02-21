#ifndef READFILEH
#define READFILEH


#include <fstream>
using namespace std;
class Readfile
{
	public:
		fstream singleFile;
		Readfile();
		// ~readfile();

		void readData(string passedFile, Matrix &inputs, Matrix &targets, Matrix &testDat);
		// void parseData();
		void initArr();
		void deleteArr();
		int getNumHiddenNodes();
		// char * split(char * orig, char * token);

	private:
		int numInputs;
		int numHiddenNodes;
		int rows;
		int cols;
		int skipChars;
		double * xArr;
		double * tArr;
};


#endif