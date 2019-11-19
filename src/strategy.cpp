#include "strategy.h"
#include "utils.h"
#include "LSH.h"
#include "utils.h"
#include "dba.h"
#include <limits>
#include <algorithm>

void RandomInit::execute() {
    auto objs = cluster->getDataset()->getData();
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<int> dist(0,objs.size()-1);
    set<Object *> centers;
    for (int i = 0; i < cluster->getGeneralParameters()->getNumOfClusters(); ++i) {
        auto objectToInsert = objs.at(dist(rng));
        //if it already exists, find another
        while (centers.find(objectToInsert) != centers.end())
            objectToInsert = objs.at(dist(rng));
        centers.insert(objectToInsert);
    }
    cluster->setCenters(centers);
}

void LloydAssignment::execute() {

}

InverseAssignment::InverseAssignment(Cluster* cluster) {
    this->cluster = cluster;
    this->hasVectors = cluster->getDataset()->getHasVectors();
    auto numOfHTs = cluster->getGeneralParameters()->getNumOfVectorHashTables();
    auto numOfHFs = cluster->getGeneralParameters()->getNumOfVectorHashFunctions();
    auto dimension = cluster->getDataset()->getDimension();
    if(hasVectors) {
        lsh = new LSH(new Manhattan);
        //TODO: window...
        lsh->setHashTableStruct(new PointHashTableStruct(numOfHTs, numOfHFs, dimension, 10000));
    } else {
        lsh = new LSH(new DTW);
        //TODO: window... and min
        lsh->setHashTableStruct(new CurveHashTableStruct(numOfHTs, numOfHFs, dimension, 0.000002, cluster->getDataset()->getMax(),2));
    }
    auto data = cluster->getDataset()->getData();
    for (auto & obj : data)
        lsh->getHashTableStruct()->addToAllHashTables(obj);
    //lsh->getHashTableStruct()->test_print_hashtable();
}

void InverseAssignment::execute() {
    //calculate initial radius = min(dist between centers)/2
    auto metric = lsh->getMetric();
    auto centers = cluster->getCenters();
    double minDistance = minDistanceInSet(centers, metric);
    double radius = minDistance / 2.0;

    //keep hashes of centers

//    while(something){
//        //for every center
//            //for every hash table
//                //keep the object if dist < radius
//                //mark the already picked ones
//
//
//        radius *= 2;
//    }

}

void PAMUpdate::execute() {

}

void CentroidUpdate::execute() {
    auto objs = cluster->getDataset();
    auto numClusters = cluster->getGeneralParameters()->getNumOfClusters();

    set<Object *> centroids;
    if (objs->getHasVectors()) {
        for (auto clust : cluster->getClusters()) {
            double clusterSize = double(clust.second.size());
            vector<double> centroid(objs->getDimension(),0.0);
            for (auto obj : clust.second) {
                auto p = dynamic_cast<Point *>(obj);
                for (int i =0; i < p->getCoordinates().size();i++) {
                    centroid.at(i) += p->getCoordinate(i)/clusterSize;
                }
            }
            centroids.insert(new Point(centroid));
            centroid.clear();
        }
    } else {
        for (auto clust : cluster->getClusters()) {
            auto dba = new DBA(clust.second);
            auto centroid = dba->run();
            centroids.insert(centroid);
        }
    }
}