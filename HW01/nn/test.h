#ifndef TESTH
#define TESTH

class Test
{
	public:
		Test(Matrix &testDat, Matrix &passedW);
		void runTest(Matrix &testDat, Matrix &testDatWBias);
		// void normalizeAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
	private:
		Matrix w = new Matrix;



};


#endif