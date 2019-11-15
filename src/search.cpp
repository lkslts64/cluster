#include "search.h"
#include "distance.h"
#include <limits>
#include <bitset>
#include <set>
#include <fstream>

//void search_LSH_vs_BruteForce(LSH* lsh) {
//    ofstream out (lsh->getOutputFilename(), ofstream::out);
//    int querySize = lsh->getQueryData()->getSize();
//    auto queryData = lsh->getQueryData()->getData();
//    double queryRadius = lsh->getQueryData()->getRadius();
//
//    for (int i = 0; i < querySize; ++i) {
//        Object* queryObject = queryData.at(i);
//        out << "Query: " << queryObject->getId() << endl;
//        Object* nearestNeighbor = nullptr;
//        double distance;
//        set<Object *> radiusNeighbors;
//
//        //LSH
//        clock_t begin = clock();
//        search_LSH(&nearestNeighbor, &distance, queryObject, lsh, radiusNeighbors, queryRadius);
//        clock_t end = clock();
//
//        if(nearestNeighbor == nullptr){
//            out << "Nearest neighbor: Not Found" << endl;
//        } else {
//            out << "Nearest neighbor LSH: " << nearestNeighbor->getId() << endl;
//            out << "distance LSH: " << distance << endl;
//            out << "time LSH: " << end - begin << endl;
//        }
//
//        //Brute Force
//        begin = clock();
//        search_BruteForce(&nearestNeighbor, &distance, lsh->getDataset()->getData(), queryObject, lsh->getMetric());
//        end = clock();
//
//        out << "Nearest neighbor Brute Force: " << nearestNeighbor->getId() << endl;
//        out << "distance Brute Force: " << distance << endl;
//        out << "time Brute Force: " << end - begin << endl;
//        out << "R-near neighbors:" << endl;
//        for(auto n : radiusNeighbors){
//            out << n->getId() << endl;
//        }
//        out << endl << endl;
//    }
//}
//
//void search_BruteForce(Object **nnObj, double *distance, const vector<Object *>& data, Object *queryObj,DistanceMetric *dmetric) {
//    *nnObj = nullptr;
//    *distance = numeric_limits<double>::max();
//    for(auto candidate : data){
//        //Point* candidatePoint = dynamic_cast<Point*>(candidate);
//        double cur_dist;
//        if( (cur_dist = dmetric->dist(queryObj, candidate)) < *distance){
//            *distance = cur_dist;
//            *nnObj = candidate;
//        }
//    }
//}
//
//void search_LSH(Object **nearestNeighbor, double *distance, Object *queryObject, LSH* lsh, set<Object*>& radiusNeighbors, double radius) {
//    *nearestNeighbor = nullptr;
//    *distance = numeric_limits<double>::max();
//    bool found = false;
//    //int threshold = 50 * lsh->getNumOfHashTables();
//    int threshold = 10 * lsh->getNumOfHashTables();
//    int thresholdCount = 0;
//    auto hashers = lsh->getHashTableStruct()->getHashers();
//    auto hts = lsh->getHashTableStruct()->getAllHashTables();
//    for (int j = 0; j < lsh->getNumOfHashTables(); ++j) {
//        size_t hash = (*hashers.at(j))(queryObject);
//        if(hts[j].find(hash) == hts[j].end()) //empty bucket
//            continue;
//        //cout << "found in table " << j << endl;
//        auto points = hts[j].at(hash);
//        thresholdCount = 0;
//        for(auto candidate : points){
//            if (thresholdCount > threshold)
//                break;
//            double cur_dist = lsh->getMetric()->dist(queryObject, candidate);
//            if(cur_dist <= radius)
//                radiusNeighbors.insert(candidate);
//            if(cur_dist < *distance){
//                found = true;
//                *distance = cur_dist;
//                *nearestNeighbor = candidate;
//            }
//            thresholdCount++;
//        }
//    }
//    //if we fall in empty backet for all htables
//    //set dist to zero (otherwise AF calculation is useless)
//    if (!found)
//        *distance = 0.0;
//}
//
//void DoQueries(LSH *lsh) {
//    int querySize = lsh->getQueryData()->getSize();
//    auto queryData = lsh->getQueryData()->getData();
//    double queryRadius = lsh->getQueryData()->getRadius();
//
//    clock_t meanSearchLSH = 0;
//    clock_t meanSearchBF = 0;
//    double maxAF = numeric_limits<double>::min();
//    double averageAF = 0;
//    int averageAFCount = 0;
//    int notFound = 0;
//
//    for (int i = 0; i < querySize; ++i) {
//        Object* queryPoint = (Point*)queryData.at(i);
//        Object* nnPoint;
//        set<Object*> radiusNeighbors;
//        double distanceLSH;
//        double distanceBF;
//        clock_t begin = clock();
//        search_LSH(&nnPoint, &distanceLSH, queryPoint, lsh, radiusNeighbors, queryRadius);
//        clock_t end = clock();
//        meanSearchLSH += (end-begin);
//        begin = clock();
//        search_BruteForce(&nnPoint, &distanceBF, lsh->getDataset()->getData(), queryPoint, lsh->getMetric());
//        end = clock();
//        meanSearchBF += (end-begin);
//        double AF;
//        if ((AF = distanceLSH/distanceBF) > maxAF)
//            maxAF = AF;
//        if (distanceLSH > 0) {//compute only if > 0
//            averageAF += distanceLSH/distanceBF;
//            averageAFCount++;
//        } else
//            notFound++;
//        cout << " i : " << i << " AF " << AF << endl;
//    }
//    cout << "meanTimeSearchLSH " << meanSearchLSH/querySize << " meanTimeSearchBF " << meanSearchBF/querySize
//        << " and maxAF = " << maxAF << " and averageAF " << averageAF/averageAFCount << " and not found: " << notFound << endl;
//}