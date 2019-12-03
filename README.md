# Clustering Algorithms for Vectors & Curves

Task 2, Algorithms Project, DI @ UoA 2019

* The goal of this task is to experiment with algorithms to find clusters for Vectors/Curves and evaluate the results using a Silhouette function.
* Clustering can be divided into: Initialization, Assignment, Update. We have implemented 2 variations for every one of these, so in total there are 8 (2 Init * 2 Assign * 2 Update) different ways of clustering.
* Some algorithms (LSH mainly) contain code from our previous [project](https://github.com/kostismich7/lsh-search-vectors-curves).
* All source/header files, sample input data files, and the config file are in src directory.
* Do NOT change the structure of cluster.conf file, only the values.
* Implemented on C++ 14
* Build with CMake

## Build & Execution

Run all the following commands in project's root directory.
* $ cmake .
* $ make cluster
* $ ./cluster -i [input file]  -c [config file] -ο [output file] -complete [optional]

## Algorithms
   
* Initialization:
    1. Random: Choose random initial centers of clusters from dataset.
    2. KMeans++: Spread out the initial centers.
* Assignment:
    1. Lloyd's: Assign every object to the currently closest center (brute-force). 
    2. Inverse/LSH: Insert data into an LSH structure and assign objects to centers of the same bucket. The remaining objects are inserted a la Lloyd's.
* Update:
    1. PAM: Choose a new center for every cluster by minimizing the objective function, which is the sum of distances to every object of the correspondent cluster.
    2. Centroid: Calculate a new center (Mean Vector/DTW Centroid Curve).
    
## Results

* ALGORITHM XYZ => X init, Y Assignment and Z Update. X,Y,Z ε {1,2}
* Silhouette Evaluation => -1 is bad clustering, 1 is good clustering.
* There are many combinations of data sets and number of clusters to be tested, we present some of them below.

### Vectors

* [Dataset 1](src/dataset/vectors/DataVectors_5_1000x500.csv), 5 clusters
    * ALGORITHM 111: Silhouette Evaluation = 0.492803, Time Elapsed = 3.06878
    * ALGORITHM 112: Silhouette Evaluation = 0.492059, Time Elapsed = 3.51274
    * ALGORITHM 121: Silhouette Evaluation = 0.981076, Time Elapsed = 2.95744
    * ALGORITHM 122: Silhouette Evaluation = 0.267091, Time Elapsed = 2.0841
    * ALGORITHM 211: Silhouette Evaluation = 0.981076, Time Elapsed = 1.99185
    * ALGORITHM 212: Silhouette Evaluation = 0.981076, Time Elapsed = 1.4421
    * ALGORITHM 221: Silhouette Evaluation = 0.981076, Time Elapsed = 1.6154
    * ALGORITHM 222: Silhouette Evaluation = 0.981076, Time Elapsed = 1.23574

* [Dataset 2](src/dataset/vectors/DataVectors_10_1000x500.csv), 10 clusters
    * ALGORITHM 111: Silhouette Evaluation = 0.523068, Time Elapsed = 2.02812
    * ALGORITHM 112: Silhouette Evaluation = 0.737392, Time Elapsed = 1.27863
    * ALGORITHM 121: Silhouette Evaluation = 0.492485, Time Elapsed = 1.90018
    * ALGORITHM 122: Silhouette Evaluation = 0.736186, Time Elapsed = 1.66065
    * ALGORITHM 211: Silhouette Evaluation = 0.736897, Time Elapsed = 1.02471
    * ALGORITHM 212: Silhouette Evaluation = 0.982139, Time Elapsed = 1.36607
    * ALGORITHM 221: Silhouette Evaluation = 0.982139, Time Elapsed = 1.12196
    * ALGORITHM 222: Silhouette Evaluation = 0.982139, Time Elapsed = 1.89894
    
* [Dataset 3](src/dataset/vectors/DataVectors_15_10000x100.csv), 15 clusters
    * ALGORITHM 111: Silhouette Evaluation = 0.518054, Time Elapsed = 71.5432
    * ALGORITHM 112: Silhouette Evaluation = 0.521806, Time Elapsed = 1.67196
    * ALGORITHM 121: Silhouette Evaluation = 0.323089, Time Elapsed = 67.1974
    * ALGORITHM 122: Silhouette Evaluation = 0.487596, Time Elapsed = 5.15969
    * ALGORITHM 211: Silhouette Evaluation = 0.752752, Time Elapsed = 42.3858
    * ALGORITHM 212: Silhouette Evaluation = 0.778737, Time Elapsed = 4.16277
    * ALGORITHM 221: Silhouette Evaluation = 0.605798, Time Elapsed = 30.5469
    * ALGORITHM 222: Silhouette Evaluation = 0.467371, Time Elapsed = 4.53498

### Curves

* [Dataset 1](src/dataset/curves/trajectories_dataset_very_small.csv), 7 clusters
    * ALGORITHM 111: Silhouette Evaluation = 0.560874, Time Elapsed = 124.128
    * ALGORITHM 112: Silhouette Evaluation = 0.593036, Time Elapsed = 105.733
    * ALGORITHM 121: Silhouette Evaluation = 0.465221, Time Elapsed = 148.514
    * ALGORITHM 122: Silhouette Evaluation = 0.764804, Time Elapsed = 235.677
    * ALGORITHM 211: Silhouette Evaluation = 0.535267, Time Elapsed = 198.893
    * ALGORITHM 212: Silhouette Evaluation = 0.824727, Time Elapsed = 135.249
    * ALGORITHM 221: Silhouette Evaluation = 0.457437, Time Elapsed = 204.199
    * ALGORITHM 222: Silhouette Evaluation = 0.583609, Time Elapsed = 190.295

* [Dataset 2](src/dataset/curves/input_projection6.csv), 6 clusters
    * ALGORITHM 111: Silhouette Evaluation = 0.354756, Time Elapsed = 32.7696
    * ALGORITHM 112: Silhouette Evaluation = 0.365942, Time Elapsed = 4.54283
    * ALGORITHM 121: Silhouette Evaluation = 0.375336, Time Elapsed = 39.7761
    * ALGORITHM 122: Silhouette Evaluation = 0.440976, Time Elapsed = 5.86232
    * ALGORITHM 211: Silhouette Evaluation = 0.404408, Time Elapsed = 38.7312
    * ALGORITHM 212: Silhouette Evaluation = 0.585789, Time Elapsed = 13.1666
    * ALGORITHM 221: Silhouette Evaluation = 0.458901, Time Elapsed = 39.0185
    * ALGORITHM 222: Silhouette Evaluation = 0.485789, Time Elapsed = 10.9606

* [Dataset 3](src/dataset/curves/input_projection10.csv), 10 clusters
    * ALGORITHM 111: Silhouette Evaluation = 0.377536, Time Elapsed = 25.3448
    * ALGORITHM 112: Silhouette Evaluation = 0.360237, Time Elapsed = 17.8947
    * ALGORITHM 121: Silhouette Evaluation = 0.303868, Time Elapsed = 37.0851
    * ALGORITHM 122: Silhouette Evaluation = 0.414426, Time Elapsed = 18.2446
    * ALGORITHM 211: Silhouette Evaluation = 0.357422, Time Elapsed = 32.19
    * ALGORITHM 212: Silhouette Evaluation = 0.432093, Time Elapsed = 17.6343
    * ALGORITHM 221: Silhouette Evaluation = 0.307241, Time Elapsed = 223.615
    * ALGORITHM 222: Silhouette Evaluation = 0.397739, Time Elapsed = 20.0385

## Conclusion

* Initialization: KMeans++ produces efficient initial centers opposed to Random which usually does bad initial assignments. 
* Assignment: Lloyd's brute-force solution seems to be a little more efficient than Inverse/LSH for the data sets that we are dealing with.
* Update: Centroid is faster than PAM strategy. The latter performs a brute-force solution to find a new center based on minimizing the overall distance between members and center of each cluster. The former updates the centers by creating new centroids based on each cluster's members' average.

## Authors

* [Loukas Litsos](https://github.com/lkslts64) (AM: 1115201500082)
* [Kostis Michailidis](https://github.com/kostismich7) (AM: 1115201500098)