#include "strategy.h"

void RandomInit::execute() {
    auto objs = cluster->getDataset()->getData();
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<int> dist(0,objs.size()-1);
    set<Object *> kMeans;
    for (int i = 0; i < cluster->getGeneralParameters()->getNumOfClusters(); ++i) {
        auto objectToInsert = objs.at(dist(rng));
        //if it already exists, find another
        while (kMeans.find(objectToInsert) != kMeans.end())
            objectToInsert = objs.at(dist(rng));
        kMeans.insert(objectToInsert);
    }
    cluster->setKMeans(kMeans);
}

void SpreadOutInit::execute() {

}

void LloydAssignment::execute() {

}

void InverseAssignment::execute() {

}

void PAMUpdate::execute() {

}

void CentroidUpdate::execute() {

}