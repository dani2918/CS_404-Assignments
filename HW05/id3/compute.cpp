#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "mat.h"
// #include "ktree.h"
#include "compute.h"
using namespace std;



Compute::Compute(Matrix &x, vector<string> n, vector< map<int, string> > &mp)
{
    Matrix sub = x.subMatrixEq(0,0.0);
    names = n;
    strmap = mp;
    Tree t = Tree();
    numAns = x.maxCol(x.maxCols()-1) + 1;
    int * finishedCols;
    numFeatures = x.maxCols() - 1;
    finishedCols = new int[numFeatures];
    for(int i = 0; i < numFeatures; i++)
    {
        finishedCols[i] = 0;
    }

    Tree * finalt = constructTree(x, finishedCols, 0);
    finalt -> printEdge();

}

Tree * Compute::constructTree(Matrix &x,  int * &finishedCols, int depth)
{
    double * gain;
    int numFeatures = x.maxCols() - 1;
    gain = new double[numFeatures];
    for(int i = 0; i < numFeatures; i++)
    {
        gain[i] = 0.0;
    }
    getGain(x, gain, finishedCols);

    double bestGain = -99999999999;
    int bestFeature = -1;

    for (int i = 0; i < numFeatures; i++)
    {
        // cout << finishedCols[i] << " ";
        if(gain[i] > bestGain)
        {
            bestFeature = i;
            bestGain = gain[i];
        }
    }
    // cout << endl;

    // cout << "\nBest feature: " << names[bestFeature]  << endl;
    // printf("bestgain: %f\n", bestGain);

    Tree * t = new Tree(names[bestFeature]);
    int i = 0;
    Matrix subcpy;
    Matrix sub;
    Matrix subDownCol;

    // cout << endl;


    for (auto m : strmap[bestFeature])
    {
        subcpy = x.subMatrixEq(bestFeature, double(i));
        sub = Matrix(subcpy);
        // sub.print();
        // cout << "THE FEATURE: " << m.second << endl;
        i++;
        // cout << "DEPTH: " << depth << endl;
        string val;

        bool noFeatures = true;
        // for(int i = 0; i < x.maxCols() - 1; i++)
        // {
        //     // cout << finishedCols[i] << " ";
        //     if(finishedCols[i] != 1)
        //     {
        //         noFeatures = false;
        //     }
        //
        // }
        // finishedCols[bestFeature] = 1;
        // cout << "depth: " <<depth << " nf: " << numFeatures << endl;
        if(onlyOneAns(sub, val))
        {
            // printf("ONLY ONE ANSWER\n\n");
            t->addChild(m.second, new Tree(val));
        }
        else if(allSame (x, bestFeature))
        {
            // cout <<"BF IS: " << bestFeature << endl;
            if(depth >= numFeatures)
            {
                string s;
                s = getMostCommon(sub);
                // sub.print();
                // cout << s << endl;
                return new Tree(s);
            }
            // x.print();
            finishedCols[bestFeature] = 1;
            t = constructTree(x, finishedCols,++depth);
            return t;
        }
        else if(depth >= numFeatures)
        {
            string s;
            s = getMostCommon(sub);
            // sub.print();
            t->addChild(m.second, new Tree(s));
            // x.print();
            // cout <<"No features: " << s << " m.second: "<< m.second << endl;
        }

        else
        {
            t->addChild(m.second, constructTree(sub, finishedCols,++depth));
            finishedCols[bestFeature] = 0;
        }
    }
    finishedCols[bestFeature] = 1;
    return t;
}
void Compute::getGain(Matrix &x, double * &gain, int * &finishedCols)
{

    // printf("numans is: %d\n", numAns);
    int sum = 0;
    Matrix sub;
    Matrix subCts;
    int numFeatures;


    for(int i = 0; i < x.maxCols() - 1; i++)
    {
        if(finishedCols[i] == 1)
        {
            // printf("Ignoring col: %d\n", i);
            continue;
        }
        // printf("\nFeature: %s\n", names[i].c_str());
        numFeatures = x.maxCol(i) + 1;
        int ansCounts[numAns];
        int featCounts[numFeatures];


        // Initalize counts to 0
        for(int j = 0; j < numAns; j++)
        {
            ansCounts[j] = 0;
        }
        for(int j = 0; j < numFeatures; j++)
        {
            featCounts[j] = 0;
        }

        for (int j = 0; j < numFeatures; j++)
        {
            sub = x.subMatrixEq(i, double(j));
            // sub.print("Init Submat");
            featCounts[j] = sub.numRows();
            // printf("feat counts: %d\n", featCounts[j]);


            // Get answer counts
            for (int k = 0; k < numAns; k++)
            {
                subCts = sub.subMatrixEq(x.maxCols()-1, double(k));
                // subCts.print("Sub counts");
                // printf("max rows: %d\n", subCts.maxRows());
                ansCounts[k] += subCts.maxRows();
                // printf("number of %d: %d\n",k, p_i[k] );
                // printf("\n");
                // printf("anscounts[%d] is: %d\n",k, ansCounts[k] );
            }
            sum = 0;

            for (int k = 0; k < numAns; k++)
            {

                sum += ansCounts[k];
            }
            // printf("sum is: %d\n",sum );


            // counts[j] = sub.maxRows();
            // printf("%d ",counts[j] );
            // sum += counts[j];
        }
        double entropy = 0;
        for(int k = 0; k < numAns; k++)
        {
            double pi = double(ansCounts[k]) / sum;
            // printf("pi: %f\n", pi);
            entropy += calcEntropy(pi);
        }
        // printf("entropy: %f\n", entropy);
        double gainSum = 0;
        double newEntropy = 0;
        for(int k = 0; k < numFeatures; k++)
        {
            newEntropy = 0;
            sub = x.subMatrixEq(i, double(k));
            // sub.print();
            for(int l = 0; l < numAns; l++)
            {
                // Matrix with ans equal to l
                // printf("feature: %d, answer: %d\n", k , l);
                subCts = sub.subMatrixEq(x.maxCols()-1, double(l));
                // subCts.print();
                // printf("subsub rows: %d, sub rows: %d\n", subCts.maxRows(),sub.maxRows());
                double pi = 0;
                if(sub.numRows() == 0)
                {
                    pi = 0.0;
                }
                else{
                    pi = double(subCts.numRows()) / double(sub.numRows());
                }
                // printf("pi: %f\n", pi);
                newEntropy += calcEntropy(pi);
            }
            // printf("NEWENT: %f\n", newEntropy);
            gainSum += double(featCounts[k]) / sum * newEntropy;
            // printf("gainsum is %f\n", gainSum);
            // gainSum += double(featCounts[k]) / double(numFeatures) * entropy;
        }
        gain[i] = entropy - gainSum;
        // printf("gain is: %f, i: %d\n", gain[i], i);


        // printf("\n\n");
    }

}

double Compute::calcEntropy(double p)
{
    if(p != 0)
    {
        return -1 * p * log2(p);
    }
    else{
        return 0.0;
    }
}

bool Compute::onlyOneAns(Matrix x,  string &val)
{
    double tst;

    // printf("init x is: %f\n", tst);
    if(x.numRows() < 1)
    {
        val = "NONE";
        return true;
    }
    else
    {
        tst = x.get(0, x.numCols()-1);
    }
    for (int i = 1; i < x.numRows(); i++)
    {
        // printf("x is: %f\n", x.get(i, x.numCols()-1));
        if(x.get(i, x.numCols()-1) != tst)
        {
            return false;
        }
    }
    int tstVal = int(tst);
    // cout << strmap[numFeatures][tstVal] << endl;
    val = strmap[numFeatures][tstVal];
    return true;
}

string Compute::getMostCommon(Matrix x)
{
    // x.print();
    if(x.numRows() < 1)
    {
        return "NONE";
    }
    int counts[numAns];
    for(int i = 0; i < numAns; i++)
    {
        counts[i] = 0;
    }
    int ans;
    for(int i = 0; i < x.numRows(); i++)
    {
        ans = int(x.get(i, x.numCols()-1));
        counts[ans]++;
    }
    int best = 0;
    int bestCount = counts[0];
    for(int i = 1; i < numAns; i++)
    {
        // cout << "counts is: " << counts[i] <<  " i is: " << i << endl;
        if(counts[i] > bestCount)
        {
            best = i;
            bestCount = counts[i];
        }
    }
    // cout << "best is: " << best <<endl;
    return  strmap[numFeatures][best];
}

bool Compute::allSame(Matrix x, int col)
{
    double first = x.get(0, col);
    for (int i = 0; i < x.numRows(); i++)
    {
        // cout << x.get(i,col) << endl;
        if (first != x.get(i,col))
        {
            return false;
        }
    }
    return true;
}
