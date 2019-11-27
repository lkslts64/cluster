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

## Results


##### Authors
* [Loukas Litsos](https://github.com/lkslts64) (AM: 1115201500082)
* [Kostis Michailidis](https://github.com/kostismich7) (AM: 1115201500098)