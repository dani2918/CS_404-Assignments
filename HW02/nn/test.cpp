#include "mat.h"
#include "util.h"
#include "test.h"
#include <math.h>


Test::Test(Matrix &testDat, Matrix &passedV, Matrix &passedW, Matrix &tar, Matrix &i)
{
	Matrix newtestDat = new Matrix(testDat.maxRows(), testDat.maxCols()+1);
	newtestDat.insert(testDat, 0, 0);
	for(int i = 0; i < testDat.maxRows(); i++)
	{
		newtestDat.set(i, testDat.maxCols(), -1.0);
	}
	Matrix testDatWBias = new Matrix(newtestDat, "testDat");
	v = new Matrix(passedV, "v");
	w = new Matrix(passedW, "w");
	// w.print();
	inputs = new Matrix(i);
	targets = new Matrix(tar);
	runTest(testDat, testDatWBias);

}

void Test::runTest(Matrix &testDat, Matrix &testDatWBias)
{
	// v.print();
	Matrix activations = new Matrix;
	testDatWBias.normalizeCols();


	Matrix h = new Matrix(testDatWBias.dot(v));
	h.map(transferFunc);
	appendBias(h, (char*)"h");
	// h.print();

	
	Matrix y = new Matrix(h.dot(w));
	y.map(transferFunc);

	activations = new Matrix(y);
	// activations.print();

	
	// activations = new Matrix(testDatWBias.dot(w));
	// activations.print("test activations0");
	// setTransferThreshold(transferThreshold);
	// activations.map(transferFunc);
	// activations.print("test activations1");

	// activations.print("activations");
	Matrix testOutput = new Matrix(testDat.maxRows(), testDat.maxCols() + activations.maxCols() );
	testOutput.insert(testDat, 0, 0);
	testOutput.insert(activations, 0, testDat.maxCols() );
	// testOutput.print("td");

	printf("BEGIN TESTING\n");
	inputs.setName("x");
	inputs.print("input normalized");
	targets.setName("out");
	targets.print();

	int exp[targets.maxRows()];
	int max[targets.maxRows()];
	double maxTargetSoFar = 0;
	int maxTargetIndexSoFar = 0;
	double maxTestSoFar = 0;
	int maxTestIndexSoFar = 0;

	for(int r = 0; r < targets.maxRows(); r++)
	{
		for(int c = 0; c < targets.maxCols(); c++)
		{
			// printf("%f ", activations.get(r,c));
			if(activations.get(r,c) > maxTestSoFar)
			{
				maxTestSoFar = activations.get(r,c);
				maxTestIndexSoFar = c;
			}
			if(targets.get(r,c) > maxTargetSoFar)
			{
				maxTargetSoFar = targets.get(r,c);
				maxTargetIndexSoFar = c;
				
				// printf("exp[r]: %d\n", exp[r]);
			}
			
			// printf("%f\n", max[r]);
		}
		exp[r] = maxTargetIndexSoFar;
		max[r] = maxTestIndexSoFar;

			maxTargetSoFar = 0;
			maxTargetIndexSoFar = 0;
			maxTestSoFar = 0;
			maxTestIndexSoFar = 0;
		// printf("\n");
	}


	//Set up confusion matrix
	Matrix confusion = new Matrix(targets.maxCols(), targets.maxCols(), "Confusion");
	confusion.setName("Confusion");
	confusion.constant(0.0);
	for(int row = 0; row < targets.maxRows(); row++)
	{
		int r = exp[row]; int c = max[row];
		// printf("row: %d, col: %d", r, c);
		int val = (int)confusion.get(r,c);
		// printf(" val: %d\n", val);
		val += 1 ;
		confusion.set(r,c, val);
	}


	// testOutput.writeFormatted();
	for (int r=0; r<testOutput.maxRows(); r++) 
	{
        for (int c=0; c<testOutput.maxCols(); c++) 
        {
            printf("%.2f ", testOutput.get(r,c));
        }
        printf("EXP: %d MAX: %d",exp[r], max[r]);
        printf("\n");
    }

	double dist = sqrt(activations.dist2(targets));
	

	// Print confusion matrix
	confusion.print();
	printf("DIST: %f\n", dist);


}



void Test::appendBias(Matrix &m, char * name)
{
	Matrix newInputs = new Matrix(m.maxRows(), m.maxCols()+1);
	newInputs.insert(m, 0, 0);
	// newInputs.print();

	for(int i = 0; i < m.maxRows(); i++)
	{
		newInputs.set(i, m.maxCols(), -1.0);
	}
	m = new Matrix(newInputs, name);
}