#include "mat.h"
#include "util.h"
#include "train.h"

Train::Train(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	eta = 0.25;
	numIterations = 5;
	transferThreshold = 0.5;

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
	inputs.normalizeCols();
	// targets.normalize();
	testDat.normalizeCols();
}


void Train::printAll(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	inputs.print("inputs");
	targets.print("targets");
	testDat.print("testDat");
	w.print("w");
}

void Train::setNumIterations(int x)
{
	numIterations = x;
}

void Train::setEta(double e)
{
	eta = e;
}

void Train::doTraining(Matrix &inputs, Matrix &targets)
{
	for(int i = 0; i < numIterations; i++)
	{
		printf("\n\n\niteration: %d\n", i);
		Matrix activations = new Matrix; //(inputs.maxRows(), targets.maxCols());
		activations = new Matrix(inputs.dot(w));
		activations.print("activations0");
		setTransferThreshold(transferThreshold);
		activations.map(transferFunc);
		activations.print("activations1");

		Matrix xT = new Matrix(inputs.transpose());
		xT.print("xT");
		Matrix differences = new Matrix(xT.dot(activations.sub(targets)));
		differences.print("differences");

		differences = differences.scalarMult(eta);
		differences.print("differences mul'd");
		w.print("w");

		w = w.sub(differences.scalarMult(eta));
	}
}



