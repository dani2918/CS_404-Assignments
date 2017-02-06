#include "mat.h"
#include "util.h"
#include "test.h"


Test::Test(Matrix &testDat, Matrix &passedW)
{
	Matrix newtestDat = new Matrix(testDat.maxRows(), testDat.maxCols()+1);
	newtestDat.insert(testDat, 0, 0);
	for(int i = 0; i < testDat.maxRows(); i++)
	{
		newtestDat.set(i, testDat.maxCols(), -1.0);
	}
	Matrix testDatWBias = new Matrix(newtestDat, "testDat");
	w = new Matrix(passedW, "w");
	// w.print();
	runTest(testDat, testDatWBias);
}

void Test::runTest(Matrix &testDat, Matrix &testDatWBias)
{
	Matrix activations = new Matrix;
	testDatWBias.normalizeCols();
	activations = new Matrix(testDatWBias.dot(w));
	// activations.print("test activations0");
	// setTransferThreshold(transferThreshold);
	activations.map(transferFunc);
	// activations.print("test activations1");

	// activations.print("activations");
	Matrix testOutput = new Matrix(testDat.maxRows(), testDat.maxCols() + activations.maxCols() );
	testOutput.insert(testDat, 0, 0);
	testOutput.insert(activations, 0, testDat.maxCols() );
	// testOutput.print("td");

	printf("BEGIN TESTING\n");
	testOutput.writeFormatted();


}