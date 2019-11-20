#include "strategy.h"
#include "utils.h"
#include "LSH.h"
#include "utils.h"
#include "kmeans.h"
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

LloydAssignment::LloydAssignment(Cluster* cluster){
    this->cluster = cluster;
    if(cluster->getDataset()->getHasVectors())
        metric = new Manhattan;
    else
        metric = new DTW;
}
void LloydAssignment::execute() {
    auto centers = cluster->getCenters();
    auto data = cluster->getDataset()->getData();
    //assign every object to the nearest center (brute-force)
    for(auto obj : data){
        Object * minCenter;
        double minDistance = numeric_limits<double>::max();
        for (auto center : centers) {
            double dist = metric->dist(obj, center);
            if(dist < minDistance){
                minDistance = dist;
                minCenter = center;
            }
        }
        cluster->addToCluster(minCenter, obj);
    }
}

InverseAssignment::InverseAssignment(Cluster* cluster) {
    this->cluster = cluster;
    this->hasVectors = cluster->getDataset()->getHasVectors();
    auto numOfGrids = cluster->getGeneralParameters()->getNumOfGrids();
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
        lsh->setHashTableStruct(new CurveHashTableStruct(numOfGrids, numOfHFs, dimension, 0.000002, cluster->getDataset()->getMax(),2));
    }
    auto data = cluster->getDataset()->getData();
    for (auto & obj : data)
        lsh->getHashTableStruct()->addToAllHashTables(obj);
    //lsh->getHashTableStruct()->test_print_hashtable();
}
InverseAssignment::~InverseAssignment(){
    delete lsh;
}
void InverseAssignment::execute() {
    //calculate initial radius = min(dist between centers)/2
    auto metric = lsh->getMetric();
    auto centers = cluster->getCenters();
    auto hashers = lsh->getHashTableStruct()->getHashers();
    auto hts = lsh->getHashTableStruct()->getAllHashTables();
    auto numOfHTs = lsh->getHashTableStruct()->getNumOfHTs();
    auto data = cluster->getDataset()->getData();
    //array that tells if a point/curve has been assigned to a center
    vector<bool> isAssigned;
    for(auto obj : data){
        isAssigned.push_back(false);
    }

    // Optimization before brute-force (use LSH):
    // For every center, assign to it every object that is on the same bucket
    // In case that there are over 1 centers for the same object, select the min distance
    for(auto center : centers){
        set<Object *> centersInSameBucket;
        //find centers that are in the same bucket
        for(auto center2 : centers){
            for(int i = 0; i < numOfHTs ; i++){
                if((*hashers.at(i))(center) == (*hashers.at(i))(center2)) {
                    centersInSameBucket.insert(center2);
                }
            }
        }

        for(int i = 0; i < numOfHTs ; i++){
            int hash = (*hashers.at(i))(center);
            if(hts[i].find(hash) == hts[i].end()) //empty bucket
                continue;
            auto points = hts[i].at(hash);
            for(auto point : points){
                Object * minCenter;
                double minDistance = numeric_limits<double>::max();
                for (auto candidateCenter : centersInSameBucket) {
                    double dist = metric->dist(point, candidateCenter);
                    if(dist < minDistance){
                        minDistance = dist;
                        minCenter = candidateCenter;
                    }
                }

                isAssigned.at(distance(data.begin(),find(data.begin(), data.end(), point))) = true;

                cluster->addToCluster(minCenter, point);
            }
        }
    }

    //assign every remaining object to the nearest center (brute-force)
    int i = 0;
    for(auto obj : data){
        if(isAssigned.at(i))
            continue;
        Object * minCenter;
        double minDistance = numeric_limits<double>::max();
        for (auto center : centers) {
            double dist = metric->dist(obj, center);
            if(dist < minDistance){
                minDistance = dist;
                minCenter = center;
            }
        }
        cluster->addToCluster(minCenter, obj);
        i++;
    }

}

//find the best centroid for each cluster
//based on minimizing the sum of distances to the center
bool PAMUpdate::execute() {
    DistanceMetric* metric;
    if(cluster->getDataset()->getHasVectors())
        metric = new Manhattan;
    else
        metric = new DTW;
    set<Object *> bestCenters;
    auto centers = cluster->getCenters();
    for(auto center : centers){
        auto members = cluster->getClusters()[center];
        Object *bestCenter;
        double min = numeric_limits<double>::max();
        for(auto candidateCenter : members){
            //calculate sum of distances to the candidateCenter
            double sum = 0;
            for(auto member : members){
                sum += metric->dist(candidateCenter, member) / double(members.size());
            }
            if(sum < min){
                min = sum;
                bestCenter = candidateCenter;
            }
        }
        bestCenters.insert(bestCenter);
    }
    cluster->setCenters(bestCenters);
    //TODO: put a stop
    return false;
}

bool CentroidUpdate::execute() {
    auto objs = cluster->getDataset();
    auto numClusters = cluster->getGeneralParameters()->getNumOfClusters();
    bool stop;
    int stopCount = 0;
    Object *centroid;
    set<Object *> centroids;
    int i = 0;
    for (auto clust : cluster->getClusters()) {
        algos[i]->setObjs(clust.second);
        centroid = algos[i]->centroid(&stop);
        if (stop) 
            stopCount++;
        centroids.insert(centroid);
        i++;
    }
    cluster->setCenters(centroids);
    //we should stop if all centroids didn't change too much from the
    //previous update
    return stopCount == numClusters;
}