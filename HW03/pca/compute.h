#ifndef COMPUTEH
#define COMPUTEH

class Compute
{
public:
    Compute(int x);
    void calcZ(Matrix &x);
    void covariance(Matrix &x);
    void eigen(Matrix &x);
    void translate(Matrix &x);
    void component();

private:
    Matrix mean;
    Matrix stddev;
    Matrix m;
    Matrix v;
    Matrix origV;
    Matrix w;
    int k;
};

#endif
