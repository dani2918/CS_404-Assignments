#include "mat.h"
#include "compute.h"

Compute::Compute(int x)
{
    k = x;
}

Matrix Compute::kMeansTrain(Matrix &data, int depth)
{
    Matrix oldCenters = Matrix();

    int cols = data.numCols();
    double mins[cols];
    double maxs[cols];
    for(int i = 0; i < cols; i++)
    {
        mins[i] = data.minCol(i);
        maxs[i] = data.maxCol(i);
    }
    Matrix minima = Matrix(1, cols, mins);
    Matrix maxima = Matrix(1, cols, maxs);

    // Pick the centre locations randomly
    centers = Matrix(k, cols, true, "centers");
    oldCenters = Matrix(centers, "oldCenters");
    for(int i = 0; i < cols; i++)
    {
        centers.randCol(i, mins[i], maxs[i]);
        oldCenters.randCol(i, mins[i], maxs[i]);
    }

    // initalize(centers, oldCenters, data);
    // centers.print();
    // oldCenters.print();

    // int count = 0;
    int maxDepth = 200;
    centers.setName("Pts");
    bool done = false;

    while((!centers.equal(oldCenters) || !done) && depth < maxDepth)//&& count < maxIterations)
    {
        printf("Try: %d\n", depth);
        // oldCenters.print("old");
        oldCenters = Matrix(centers);
        depth++;
        centers.print();
        done = true;

        Matrix distances = Matrix(data.numRows(), centers.numRows(), "distances");

        // data.print();
        // centers.print();

        // Compute distances, identify closest cluster
        for (int i = 0; i < distances.numRows(); i++)
        {
            for (int j = 0; j < centers.numRows(); j++)
            {
                distances.set(i,j, data.dist2(i, j, centers));
            }
        }
        // distances.print();

        Matrix minRows = Matrix(distances.argMinRow());
        Matrix augmented = Matrix(data.numRows(), data.numCols()+1, true);
        augmented.insert(minRows, 0, 0);
        augmented.insert(data, 0, 1);

        int num[k];
        Matrix slice = Matrix(augmented);
        // augmented.print();
        for (int i = 0; i < k; i++)
        {
            num[k] = 0;
            slice = Matrix(augmented.pickRows(double(i), augmented, num[k]));
            printf("Group %d size: %d\n", i, slice.numRows());
            if(num[k] != 0)
            {

                // slice.print();

                // Get means for each col of split array
                // Update cluster
                for(int j = 0; j < centers.numCols(); j++)
                {
                    double mean = slice.meanCol(j+1);
                    centers.set(i, j, mean);
                }
            }
            // A group has no values associated with the point
            else
            {
                // printf("here: %d\n",i);
                for(int j = 0; j < centers.numCols(); j++)
                {
                    // printf("got here\n");
                    double rm = randMod(maxs[j]-mins[j]) + mins[j];
                    // printf("did get here\n" );
                    // printf("%f   %f\n %f\n", mins[j], maxs[j], rm);
                    centers.set(i, j, rm);
                    done = false;
                }
            }
            // centers.print();
        }
    }
    // centers.print();

    // Matrix test = Matrix(augmented.pickRows(1.0, augmented, num));
    // augmented.print();
    // test.print();
    // augmented.print();

    return centers;

}

//void Compute::initalize(Matrix &c, Matrix &oc, Matrix &d)
//{
    // 	Find the minimum and maximum values for each feature

//}

//
// 	def kmeanstrain(self,data,maxIterations=10):
//
// 		# Find the minimum and maximum values for each feature
// 		minima = data.min(axis=0)
// 		maxima = data.max(axis=0)
//
// 		# Pick the centre locations randomly
// 		self.centres = np.random.rand(self.k,self.nDim)*(maxima-minima)+minima
// 		oldCentres = np.random.rand(self.k,self.nDim)*(maxima-minima)+minima
//
// 		count = 0
// 		#print centres
// 		while np.sum(np.sum(oldCentres-self.centres))!= 0 and count<maxIterations:
//
// 			oldCentres = self.centres.copy()
// 			count += 1
//
// 			# Compute distances
// 			distances = np.ones((1,self.nData))*np.sum((data-self.centres[0,:])**2,axis=1)
// 			for j in range(self.k-1):
// 				distances = np.append(distances,np.ones((1,self.nData))*np.sum((data-self.centres[j+1,:])**2,axis=1),axis=0)
//
// 			# Identify the closest cluster
// 			cluster = distances.argmin(axis=0)
// 			cluster = np.transpose(cluster*np.ones((1,self.nData)))
//
// 			# Update the cluster centres
// 			for j in range(self.k):
// 				thisCluster = np.where(cluster==j,1,0)
// 				if sum(thisCluster)>0:
// 					self.centres[j,:] = np.sum(data*thisCluster,axis=0)/np.sum(thisCluster)
// 			#plot(data[:,0],data[:,1],'kx')
// 			#plot(centres[:,0],centres[:,1],'ro')
// 		return self.centres
