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

		void readData(string passedFile, Matrix &x, int &k);
		// void parseData();
		void initArr();
		void deleteArr();
		// char * split(char * orig, char * token);

	private:
		int kExpGrps;
		int timesComputed;
		int rows;
		int cols;
		double * xArr;
};


#endif
