#include "mat.h"
#include "compute.h"

Compute::Compute(int x)
{
    k = x;
}

void Compute::calcZ(Matrix &x)
{
    mean = new Matrix(1, x.maxCols(), "mean");
    stddev = new Matrix(1, x.maxCols(), "stddev");
    mean.constant(0.0); stddev.constant(0.0);

    // calculate mean, stdev foreach col
    for(int i = 0; i < x.maxCols(); i++)
    {
        double m = x.meanCol(i);
        mean.set(0, i, m);
        double s = x.stddevCol(i);
        stddev.set(0, i, s);
        // printf("mean: %f, stddev: %f\n", m, s);
    }

    // Translate to z score, return that matrix
    // x[row] = x[row] - mean/stddev()
    // mean.print();
    // stddev.print();
    // Matrix z = mean.div(stddev);

    // z.print();
    x = x.subRowVector(mean);
    x = x.divRowVector(stddev);
    // x.print();
}


void Compute::covariance(Matrix &x)
{
    m = new Matrix(x.cov());
    // m.print("Covariance");
    // x.print();
}

void Compute::eigen(Matrix &x)
{
    v = new Matrix(m);
    // v.print();
    // v.normalizeCols();

    w = v.eigenSystem();


    v.print("EigenVectors in rows");
    w.print("EigenValues");

    origV = new Matrix(v);
    // Select top k vectors
    v.shorten(k);
    // v.print("v");
}


void Compute::translate(Matrix &x)
{
    x = x.dotT(v);
    x.print("Compressed data");

    // Recover
    x = x.dot(v);


    x = x.multRowVector(stddev);
    x = x.addRowVector(mean);

    x.print("Decoded data");


}

void Compute::component()
{
    // w.print();
    for(int i = 0; i < w.maxCols(); i++)
    {
        double wroot = w.get(0,i);
        wroot = sqrt(wroot);
        w.set(0,i, wroot);
    }
    // origV.print();
    // w.print();

    w = w.transpose();
    origV.multColVector(w);
    origV.print("Component Matrix");

}
