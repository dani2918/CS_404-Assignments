#ifndef TRAINH
#define TRAINH

class Train
{
	public:
		Train(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void normalizeAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void printAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void setNumIterations(int x);
		void setEta(double e);
		void setupW(int inputCols, int targetCols);
		void doTraining(Matrix &inputs, Matrix &targets);
		Matrix &getW();


	private:
		int numIterations;
		double eta;
		double transferThreshold;
		Matrix w = new Matrix;
		Matrix bestW = new Matrix;


};

#endif