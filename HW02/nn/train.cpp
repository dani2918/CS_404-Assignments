#include "mat.h"
#include "util.h"
#include "train.h"

Train::Train(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	eta = 0.25;
	// numIterations = inputs.maxRows();
	numIterations = 200;
	transferThreshold = 0.5;

	normalizeAll(inputs, targets, testDat);


	// Matrix newInputs = new Matrix(inputs.maxRows(), inputs.maxCols()+1);
	// newInputs.insert(inputs, 0, 0);
	// // newInputs.print();

	// for(int i = 0; i < inputs.maxRows(); i++)
	// {
	// 	newInputs.set(i, inputs.maxCols(), -1.0);
	// }
	// newInputs.print();

	// inputs = new Matrix(newInputs, "inputs");

	appendBias(inputs, (char*)"inputs");
	setupWeights(inputs.maxCols(), targets.maxCols());

}
void Train::setupWeights(int inputCols, int targetCols)
{
	w = new Matrix(inputCols, targetCols, "w");
	v = new Matrix(inputCols, targetCols, "v");
	initRand();
	w.rand(-0.1,0.1);
	v.rand(-0.1,0.1);
	// w.print("w");
}

void Train::appendBias(Matrix &m, char * name)
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


void Train::normalizeAll(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	inputs.normalizeCols();
	// targets.normalize();
	// testDat.normalizeCols();
}


void Train::printAll(Matrix &inputs, Matrix &targets, Matrix &testDat)
{
	inputs.print("inputs");
	targets.print("targets");
	testDat.print("testDat");
	w.print("w");
	v.print("v");
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
	double mean;
	double beta = 20.0;
	int bestIter = 0;
	double lowestMean = 99999999999.0;
	setTransferThreshold(transferThreshold);
	setSlope(beta);
	Matrix xT = new Matrix(inputs.transpose());
	for(int i = 0; i < numIterations; i++)
	{
		// printf("\n\n\niteration: %d\n", i);

		/* ------------- Forward  ----------------*/
		Matrix activations = new Matrix; 
		activations = new Matrix(inputs.dot(v));
		// activations.print("activations0");

		activations.map(transferFunc);
		// activations.print("activations1");

		
		// xT.print("xT");
		Matrix differences = new Matrix(xT.dot(activations.sub(targets)));
		// differences.print("differences");

		differences = differences.scalarMult(eta);
		// differences.print("differences mul'd");

		Matrix differencesAbs = new Matrix(differences);
		differencesAbs.abs();
		mean = differencesAbs.mean();

		if(mean < lowestMean)
		{
			lowestMean = mean;
			bestW = new Matrix(w, "bestW");
			bestIter = i;
		}
		// w.print("w1");
		w = w.sub(differences);
		// w.print("w2");
		// printf("mean differences: %f\n", mean);

		if(mean < 0.05)
			break;
	}
	// printf("best iter is: %d\n value is: %f\n", bestIter, lowestMean);
}

Matrix &Train::getW()
{
	return bestW;
}

Matrix &Train::getV()
{
	return bestV;
}



