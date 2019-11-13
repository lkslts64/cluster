#ifndef ALGORITHMS_PROJECT_SEARCH_H
#define ALGORITHMS_PROJECT_SEARCH_H

#include <set>
#include "Dataset.h"
#include "LSH.h"

void search_LSH_vs_BruteForce(LSH* lsh);

void search_LSH(Object **nearestNeighbor, double *distance, Object *queryObject, LSH* lsh, set<Object*>& radiusNeighbors, double radius);
void search_BruteForce(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryPoint,DistanceMetric *dmetric);

void DoQueries(LSH *lsh);

#endif //ALGORITHMS_PROJECT_SEARCH_H
