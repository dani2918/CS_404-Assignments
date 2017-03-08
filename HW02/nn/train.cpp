#include "mat.h"
#include "util.h"
#include "train.h"

Train::Train(Matrix &inputs, Matrix &targets, Matrix &testDat, int nhn)
{
	eta = 0.1;
	// numIterations = inputs.maxRows();
	numIterations = 30000;
	transferThreshold = 0.0;
	numHiddenNodes = nhn;

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
	v = new Matrix(inputCols, numHiddenNodes, "v");
	w = new Matrix(numHiddenNodes + 1, targetCols, "w");
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
	// targets.normalizeCols();
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
	double beta = 1;
	int bestIter = 0;
	double lowestMean = 99999999999.0;
	setTransferThreshold(transferThreshold);
	setSlope(beta);
	Matrix x = new Matrix(inputs);
	// x.print();
	Matrix xT = new Matrix(inputs.transpose());
	Matrix y = new Matrix();
	for(int i = 0; i < numIterations; i++)
	{
		// printf("\n\n\niteration: %d\n", i);

		/* ------------- Forward  ----------------*/
		// v.print();
		Matrix h = new Matrix(x.dot(v));
		h.map(transferFunc);
		appendBias(h, (char*)"h");
		// h.print("H");

		Matrix usableH = new Matrix(h);
		y = new Matrix(usableH.dot(w));
		y.map(transferFunc);
		// y.print("Y");


		/* ------------- Backward  ----------------*/

		// Save original y, h so we don't mutate below
		Matrix usableY = new Matrix(y);
		usableH = new Matrix(h);

		// resetting usabley just in case
		Matrix dy = new Matrix(usableY.sub(targets));
		usableY = new Matrix(y);
		dy.mult(usableY);
		usableY = new Matrix(y);
		dy.mult(usableY.scalarPreSub(1.0));
		// dy.print("DY");

		Matrix dh = new Matrix(usableH);
		usableH = new Matrix(h);
		dh.mult(usableH.scalarPreSub(1.0));

		Matrix usableW = new Matrix(w);
		Matrix wt = new Matrix(usableW.transpose());
		Matrix usableDy = new Matrix(dy);
		dh.mult(usableDy.dot(wt));

		// dh.print("DH");


		// Matrix differencesAbs = new Matrix(dy);
		// differencesAbs.abs();
		double dist = sqrt(y.dist2(targets));
		// mean = differencesAbs.mean();

		// if(i % 500 == 0)
		// {
		// 	printf("i is: %d   lowest dist is: %f\n",i,lowestMean);
		// }

		if(dist < lowestMean)
		{	
			lowestMean = dist;
			bestW = new Matrix(w, "bestW");
			bestV = new Matrix(v, "bestV");
			bestIter = i;
		}


		/* ------------- Update  ----------------*/
		Matrix ht = new Matrix(h.transpose());
		Matrix differences = new Matrix(ht.dot(dy));
		differences = differences.scalarMult(eta);
		w = w.sub(differences);

		dh.narrow(dh.maxCols()-1);

		xT = new Matrix(x.transpose());
		differences = new Matrix(xT.dot(dh));
		differences = differences.scalarMult(eta);
		v = v.sub(differences);


		// xT.print("xT");
		// Matrix differences = new Matrix(xT.dot(activations.sub(targets)));
		// // differences.print("differences");

		// differences = differences.scalarMult(eta);
		// // differences.print("differences mul'd");

		// Matrix differencesAbs = new Matrix(differences);
		// differencesAbs.abs();
		// mean = differencesAbs.mean();

		// if(mean < lowestMean)
		// {
		// 	lowestMean = mean;
		// 	bestW = new Matrix(w, "bestW");
		// 	bestV = new Matrix(v, "bestV");
		// 	bestIter = i;
		// }

		// printf(" iter is: %d\n value is: %f\n", bestIter, lowestMean);
		// // w.print("w1");
		// w = w.sub(differences);
		// // w.print("w2");
		// // printf("mean differences: %f\n", mean);

		// if(mean < 0.05)
		// 	break;
	}
	// printf("DONE\n");
	// printf("best iter is: %d\n value is: %f\n", bestIter, lowestMean);

	// bestV = new Matrix(v);
	// bestW = new Matrix(w);
		Matrix saveY = new Matrix(y);


		Matrix h = new Matrix(inputs.dot(bestV));
		h.map(transferFunc);
		appendBias(h, (char*)"h");
		// h.print();

		
		y = new Matrix(h.dot(bestW));
		y.map(transferFunc);
		// y.print("BEST Y");
		// saveY.print("FINAL Y");


		// targets.print("TARGETS");
}

Matrix &Train::getW()
{
	return bestW;
}

Matrix &Train::getV()
{
	return bestV;
}

void Train::setNumHiddenNodes(int n)
{
	numHiddenNodes = n;
}



