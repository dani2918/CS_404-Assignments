#ifndef READFILEH
#define READFILEH


#include <fstream>
#include <vector>
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
		int numFeatures;
		int rows;
		int cols;
		double * xArr;
		vector< vector<string> > v;
};


#endif
