#include "Cluster.h"
#include <fstream>
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

void Cluster::addToCluster(Object *center, Object *obj) {
    clusters[center].insert(obj);
}

void Cluster::output(string firstLine) {
    ofstream out (getGeneralParameters()->getOutputFilename(), ofstream::out);
    out << firstLine << endl;
    int i = 0;
    for(const auto& cluster : clusters){
        //TODO: centroid: <item_id> ή πίνακας με τις συντεταγμένες του centroid στην περίπτωση k-means Update}
        out << "CLUSTER-"<< i <<" {size: " << cluster.second.size() << ", centroid: " << cluster.first->getId() << "}" << endl;
        i++;
    }
    //TODO: in seconds
    out << "clustering_time:" << endl;
    //TODO
    out << "Silhouette: " << endl;

    if(getGeneralParameters()->isComplete()){
        i = 0;
        for(const auto& cluster : clusters){
            //TODO: centroid: <item_id> ή πίνακας με τις συντεταγμένες του centroid στην περίπτωση k-means Update}
            out << "CLUSTER-"<< i <<" {";
            for(auto obj : cluster.second){
                out << obj->getId() << ",";
            }
            out << "}" << endl;
            i++;
        }
    }


}
