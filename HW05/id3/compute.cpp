#include "mat.h"
#include "compute.h"

Compute::Compute(int x)
{
    k = x;
}

Matrix Compute::kMeansTrain(Matrix &data, int depth)
{
    // Matrix oldCenters = Matrix();
    //
    // int cols = data.numCols();
    // double mins[cols];
    // double maxs[cols];
    // for(int i = 0; i < cols; i++)
    // {
    //     mins[i] = data.minCol(i);
    //     maxs[i] = data.maxCol(i);
    // }
    // Matrix minima = Matrix(1, cols, mins);
    // Matrix maxima = Matrix(1, cols, maxs);
    //
    // // Pick the centre locations randomly
    // centers = Matrix(k, cols, true, "centers");
    // oldCenters = Matrix(centers, "oldCenters");
    // for(int i = 0; i < cols; i++)
    // {
    //     centers.randCol(i, mins[i], maxs[i]);
    //     oldCenters.randCol(i, mins[i], maxs[i]);
    // }
    //
    // // initalize(centers, oldCenters, data);
    // // centers.print();
    // // oldCenters.print();
    //
    // // int count = 0;
    // int maxDepth = 200;
    // centers.setName("Pts");
    // bool done = false;
    //
    // while((!centers.equal(oldCenters) || !done) && depth < maxDepth)//&& count < maxIterations)
    // {
    //     printf("Try: %d\n", depth);
    //     // oldCenters.print("old");
    //     oldCenters = Matrix(centers);
    //     depth++;
    //     centers.print();
    //     done = true;
    //
    //     Matrix distances = Matrix(data.numRows(), centers.numRows(), "distances");
    //
    //     // data.print();
    //     // centers.print();
    //
    //     // Compute distances, identify closest cluster
    //     for (int i = 0; i < distances.numRows(); i++)
    //     {
    //         for (int j = 0; j < centers.numRows(); j++)
    //         {
    //             distances.set(i,j, data.dist2(i, j, centers));
    //         }
    //     }
    //     // distances.print();
    //
    //     Matrix minRows = Matrix(distances.argMinRow());
    //     Matrix augmented = Matrix(data.numRows(), data.numCols()+1, true);
    //     augmented.insert(minRows, 0, 0);
    //     augmented.insert(data, 0, 1);
    //
    //     int num[k];
    //     Matrix slice = Matrix(augmented);
    //     // augmented.print();
    //     for (int i = 0; i < k; i++)
    //     {
    //         num[k] = 0;
    //         slice = Matrix(augmented.pickRows(double(i), augmented, num[k]));
    //         printf("Group %d size: %d\n", i, slice.numRows());
    //         if(num[k] != 0)
    //         {
    //
    //             // slice.print();
    //
    //             // Get means for each col of split array
    //             // Update cluster
    //             for(int j = 0; j < centers.numCols(); j++)
    //             {
    //                 double mean = slice.meanCol(j+1);
    //                 centers.set(i, j, mean);
    //             }
    //         }
    //         // A group has no values associated with the point
    //         else
    //         {
    //             // printf("here: %d\n",i);
    //             for(int j = 0; j < centers.numCols(); j++)
    //             {
    //                 // printf("got here\n");
    //                 double rm = randMod(maxs[j]-mins[j]) + mins[j];
    //                 // printf("did get here\n" );
    //                 // printf("%f   %f\n %f\n", mins[j], maxs[j], rm);
    //                 centers.set(i, j, rm);
    //                 done = false;
    //             }
    //         }
    //         // centers.print();
    //     }
    // }
    // centers.print();

    // Matrix test = Matrix(augmented.pickRows(1.0, augmented, num));
    // augmented.print();
    // test.print();
    // augmented.print();

    // return centers;
    return Matrix();
}
