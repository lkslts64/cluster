#ifndef ALGORITHMS_PROJECT_RELEVANTTRAVERSALS_H
#define ALGORITHMS_PROJECT_RELEVANTTRAVERSALS_H

#include <iostream>
#include <tuple>
#include <vector>
#include "GenericAlgorithm.h"
#include "Projection.h"

using namespace std;
class Projection;
class RelevantTraversals {
private:
    int length1, length2;

    vector<vector<tuple<int, int>>> traversals;

    vector<ANN_Structure *> ann_structs;

    Projection* projection;
    /**
     * This matrix is used as a helper to create
     * relevant traversals. The cells that are
     * close to the diagonal, are set to true.
     */
    bool **traversalsMatrix;

    void createTraversalsMatrix();
    void deleteTraversalsMatrix();

    void createRelevantTraversals();
    void constructTraversalsRecursively(vector<tuple<int, int>> traversal, int i, int j);

    void printTraversalsMatrix();
    void printRelevantTraversals();
public:

    RelevantTraversals(int length1, int length2, Projection* proj);

    void addToHashTables(Curve *curve);
    vector<vector<tuple<int, int>>> getTraversals(){return traversals;}
    vector<ANN_Structure *> getAnnStructs(){return ann_structs;}

    void addToCubes(Curve *curve);
};

#endif //ALGORITHMS_PROJECT_RELEVANTTRAVERSALS_H
