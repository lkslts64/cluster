#include "Cluster.h"
using namespace std;

void Cluster::testPrintClusterKeysAndSize() {
    for(auto cluster : clusters) {
        cout << "CENTER: " << cluster.first->getId() << " SIZE: "<< cluster.second.size() << endl;
    }
}

set<Object *> Cluster::getCenters() {
    set<Object *> centers;
    for(const auto& cluster : clusters)
        centers.insert(cluster.first);
    return centers;
}

void Cluster::setCenters(const set<Object *>& centers) {
    for(auto center : centers)
        clusters[center];
}