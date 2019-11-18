#include "Cluster.h"
using namespace std;

void Cluster::setCenters(const set<Object *>& centers) {
    for(auto center : centers)
        clusters[center];
}

void Cluster::testPrintClusterKeysAndSize() {
    for(auto cluster : clusters) {
        cout << "CENTER: " << cluster.first->getId() << " SIZE: "<< cluster.second.size() << endl;
    }
}

