#ifndef ALGORITHMS_PROJECT_SEARCH_H
#define ALGORITHMS_PROJECT_SEARCH_H

#include <set>
#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"
#include "Projection.h"

void search_Cube_vs_BruteForce(Cube* cube);
void search_LSH_vs_BruteForce(LSH* lsh);
void search_LSH_vs_BruteForce_Projection(Projection* projection);
void search_Cube_vs_BruteForce_Projection(Projection* projection);

void search_Cube(Object **nearestNeighbor, double *distance, Object* queryObject, Cube* cube, set<Object*>& radiusNeighbors, double radius);
void search_LSH(Object **nearestNeighbor, double *distance, Object *queryObject, LSH* lsh, set<Object*>& radiusNeighbors, double radius);
void search_BruteForce(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryPoint,DistanceMetric *dmetric);
void search_LSH_Projection(Object **nearestNeighbor, double *distance, Object *queryObject, Projection* projection);
void search_Cube_Projection(Object **nearestNeighbor, double *distance, Object* queryObject, Projection* projection);

void DoQueries(LSH *lsh);
void DoQueries(Cube *cube);
void DoQueries(Projection* projection);
void DoQueriesProjCube(Projection* projection);

#endif //ALGORITHMS_PROJECT_SEARCH_H
