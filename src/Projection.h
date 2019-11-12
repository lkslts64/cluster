#ifndef ALGORITHMS_PROJECT_PROJECTION_H
#define ALGORITHMS_PROJECT_PROJECTION_H

#include <iostream>
#include <tuple>
#include <vector>
#include <string.h>
#include "RelevantTraversals.h"
#include "Dataset.h"
#include "GenericAlgorithm.h"
#include "LSH.h"

using namespace std;
class RelevantTraversals;
class Projection : public GenericAlgorithm{
private:
    vector<vector<RelevantTraversals *>> traversalsMatrix;

    //G Matrix
    vector<vector<double>> normalMatrix;

    //ANN to be used in traversals
    ANN_Structure* ann;
    string algorithm;
public:
    const string &getAlgorithm() const;

//public:

    Projection(ANN_Structure *ann, string alg){
        this->ann = ann;
        this->algorithm = alg;
    }

    auto getTraversalsMatrix(){ return traversalsMatrix;}
    auto getNormalMatrix() { return normalMatrix;}
    auto getAnn() { return ann;}

    void buildTraversalsMatrix(int size);

    void setNormalMatrix(double epsilon);

    void printNormalMatrix();

    void putDataToHashTables();

    void putDataToCubes();
};


#endif //ALGORITHMS_PROJECT_PROJECTION_H
