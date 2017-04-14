#ifndef COMPUTEH
#define COMPUTEH
#include "ktree.h"
using namespace std;
class Compute
{
public:
    Compute(Matrix &x, vector<string> n, vector< map<int, string> > &mp);


private:
    void getGain(Matrix &x, double * &gain, int * &finishedCols);
    Tree * constructTree(Matrix &x, int * &finishedCols, int depth);
    double calcEntropy(double p);
    vector<string> names;
    vector< map<int, string> > strmap;
    int numAns;
    bool onlyOneAns(Matrix x, string &val);
    int numFeatures;
    string getMostCommon(Matrix x);
    bool allSame(Matrix x, int col);
    // Matrix stddev;
    // Matrix m;
    // Matrix v;
    // Matrix origV;
    // Matrix w;
};

#endif
