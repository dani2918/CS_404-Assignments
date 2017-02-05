#include "mat.h"
#include "train.h"

Train::Train(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	eta = 0.25;
	numIterations = 5;

	normalizeAll(inputs, targets, testDat);

	Matrix newInputs = new Matrix(inputs.maxRows(), inputs.maxCols()+1);
	newInputs.insert(inputs, 0, 0);
	// newInputs.print();

	for(int i = 0; i < inputs.maxRows(); i++)
	{
		newInputs.set(i, inputs.maxCols(), -1.0);
	}
	// newInputs.print();

	inputs = new Matrix(newInputs, "inputs");
	setupW(inputs.maxCols(), targets.maxCols());
}
void Train::setupW(int inputCols, int targetCols)
{
	w = new Matrix(inputCols, targetCols, "w");
	initRand();
	w.rand(-0.1,0.1);
	// w.print("w");
}


void Train::normalizeAll(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	inputs.normalize();
	// targets.normalize();
	testDat.normalize();
}


void Train::printAll(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	inputs.print("inputs");
	targets.print("targets");
	testDat.print("testDat");
}

void Train::setNumIterations(int x)
{
	numIterations = x;
}

void Train::setEta(double e)
{
	eta = e;
}


