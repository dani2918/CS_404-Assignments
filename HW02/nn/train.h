#ifndef TRAINH
#define TRAINH

class Train
{
	public:
		Train(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void appendBias(Matrix &m, char * name);
		void normalizeAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void printAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void setNumIterations(int x);
		void setEta(double e);
		void setupWeights(int inputCols, int targetCols);
		void doTraining(Matrix &inputs, Matrix &targets);
		Matrix &getW();
		Matrix &getV();


	private:
		int numIterations;
		double eta;
		double transferThreshold;
		Matrix w = new Matrix;
		Matrix v = new Matrix;
		Matrix bestW = new Matrix;
		Matrix bestV = new Matrix;


};

#endif