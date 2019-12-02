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
* ALGORITHM_XYZ => X init, Y Assignment and Z Update. X,Y,Z ε {1,2}
* Silhouette Evaluation => -1 is bad clustering, 1 is good clustering.
#### Vectors

* [Dataset 1](src/dataset/vectors/DataVectors_5_1000x500.csv), 5 clusters
    * ALGORITHM 111: Silhouette Evaluation = 0.492803, Time Elapsed = 3.06878
    * ALGORITHM 112: Silhouette Evaluation = 0.492059, Time Elapsed = 3.51274
    * ALGORITHM 121: Silhouette Evaluation = 0.981076, Time Elapsed = 2.95744
    * ALGORITHM 122: Silhouette Evaluation = 0.267091, Time Elapsed = 22.0841
    * ALGORITHM 211: Silhouette Evaluation = 0.981076, Time Elapsed = 1.89185
    * ALGORITHM 212: Silhouette Evaluation = 0.981076, Time Elapsed = 31.3421
    * ALGORITHM 221: Silhouette Evaluation = 0.981076, Time Elapsed = 1.6154
    * ALGORITHM 222: Silhouette Evaluation = 0.981076, Time Elapsed = 1.23574

* [Dataset 2](src/dataset/vectors/DataVectors_10_1000x500.csv), 10 clusters
        
#### Curves

## Conclusion

* Initialization: KMeans++ produces efficient initial centers opposed to Random which usually does bad assignments. 
* Assignment:
* Update:

## Authors
* [Loukas Litsos](https://github.com/lkslts64) (AM: 1115201500082)
* [Kostis Michailidis](https://github.com/kostismich7) (AM: 1115201500098)