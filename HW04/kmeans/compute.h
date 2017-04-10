#ifndef COMPUTEH
#define COMPUTEH

class Compute
{
public:
    Compute(int x);
    Matrix kMeansTrain(Matrix &points, int depth);
    // void covariance(Matrix &x);
    // void eigen(Matrix &x);
    // void translate(Matrix &x);
    void component();
    // void initalize(Matrix &c, Matrix &oc, Matrix &d);

private:
    Matrix centers;
    // Matrix stddev;
    // Matrix m;
    // Matrix v;
    // Matrix origV;
    // Matrix w;
    int k;
};

#endif
