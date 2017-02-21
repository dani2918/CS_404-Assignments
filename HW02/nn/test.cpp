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
	targets = new Matrix(tar);
	inputs = new Matrix(i,"x");
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
	inputs.print("input normalized");
	testDat.setName("out");
	testDat.print();
	testOutput.writeFormatted();

	double dist = sqrt(activations.dist2(targets));
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