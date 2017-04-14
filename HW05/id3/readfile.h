#ifndef READFILEH
#define READFILEH


#include <fstream>
#include <vector>
#include <map>
using namespace std;
class Readfile
{
	public:
		fstream singleFile;
		Readfile();
		// ~readfile();

		void readData(string passedFile, Matrix &x, int &k,
			vector<string> &names, vector< map<int, string>> &mp);
		// void parseData();
		void initArr();
		void deleteArr();
		// char * split(char * orig, char * token);

	private:
		int numFeatures;
		int rows;
		int cols;
		double * xArr;
		vector< map<string, int>> strmap;
		string feature;
		vector<string> features;
		vector<map<int, string>> reverse;
		int numValues;
};


#endif
