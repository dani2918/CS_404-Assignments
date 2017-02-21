#ifndef TESTH
#define TESTH

class Test
{
	public:
		Test(Matrix &testDat, Matrix &passedV, Matrix &passedW, Matrix &tar, Matrix &i);
		void runTest(Matrix &testDat, Matrix &testDatWBias);
		void appendBias(Matrix &m, char * name);
		// void normalizeAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
	private:
		Matrix w = new Matrix;
		Matrix v = new Matrix;
		Matrix inputs = new Matrix;
		Matrix targets = new Matrix;



};


#endif