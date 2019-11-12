#ifndef ALGORITHMS_PROJECT_LSH_H
#define ALGORITHMS_PROJECT_LSH_H
#include "Dataset.h"
#include "HashTableStruct.h"
#include "distance.h"
#include "GenericAlgorithm.h"

class LSH : public GenericAlgorithm, public ANN_Structure {
private:

    HashTableStruct * tables;
    DistanceMetric *distMetric;

    //k_vec for Curves - k for Points
    int numOfFunctions = 0;

    //L_grid for Curves - L for Points
    int numOfHashTables = 0;

public:
    LSH(DistanceMetric *metric) {
        distMetric = metric;
    }
    DistanceMetric *getMetric() { return distMetric;}

    int getNumOfFunctions() const {return numOfFunctions;}
    int getNumOfHashTables() const {return numOfHashTables;}
    HashTableStruct * getHashTableStruct() {return tables;}

    void setNumOfFunctions(int numOfFunctions){
        this->numOfFunctions = numOfFunctions;
    }

    void setNumOfHashTables(int numOfHashTables){
        this->numOfHashTables = numOfHashTables;
    }

    void setHashTableStruct(HashTableStruct *ht) {
        tables = ht;
    }

};

#endif //ALGORITHMS_PROJECT_LSH_H
