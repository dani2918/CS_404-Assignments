class Train
{
	public:
		Train(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void normalizeAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void printAll(Matrix &inputs, Matrix &targets, Matrix &testDat);
		void setNumIterations(int x);
		void setEta(double e);
		void setupW(int inputCols, int targetCols);

	private:
		int numIterations;
		double eta;
		Matrix w = new Matrix;


};

