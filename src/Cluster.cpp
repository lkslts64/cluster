#include "Cluster.h"
#include "distance.h"
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
    clusters.clear();
    for(auto center : centers)
        clusters[center];
}

void Cluster::addToCluster(Object *center, Object *obj) {
    clusters[center].insert(obj);
}

vector<double> Cluster::getSilhouette(){
    DistanceMetric* metric;
    if(getDataset()->getHasVectors())
        metric = new Manhattan;
    else
        metric = new DTW;
    vector<double> silhouette;
    double total = 0;
    for(const auto& cluster : clusters){
        double s = 0;
        for(auto obj : cluster.second){
            double a=0,b=0;
            //calculate averageDistance1
            for(auto obj2 : cluster.second)
                if(obj!=obj2)
                    a += metric->dist(obj,obj2) / double(cluster.second.size() - 1);
            //find second nearest cluster
            pair<Object *,set<Object *>> secondCluster;
            double minDist = numeric_limits<double>::max();
            for (const auto& cluster2 : clusters) {
                if(cluster.first != cluster2.first){
                    double dist = metric->dist(obj, cluster2.first);
                    if(dist < minDist){
                        minDist = dist;
                        secondCluster = cluster2;
                    }
                }
            }
            //calculate averageDistance2
            for(auto obj2 : secondCluster.second)
                b += metric->dist(obj, obj2) / double(secondCluster.second.size());
            if(a!=0 || b!=0)
                s += (b-a)/max(a,b);
        }
        if(!cluster.second.empty())
            s /= double(cluster.second.size());
        total += s;
        silhouette.push_back(s);
    }
    total = total / double(clusters.size());
    silhouette.push_back(total);
    return silhouette;
}

void Cluster::output(string firstLine, double time) {
    out << firstLine << endl;
    int i = 0;
    for(const auto& cluster : clusters){
        //TODO: centroid: <item_id> ή πίνακας με τις συντεταγμένες του centroid στην περίπτωση k-means Update}
        out << "CLUSTER-"<< i+1 <<" {size: " << cluster.second.size() << ", centroid: " << cluster.first->getId() << "}" << endl;
        i++;
    }
    out << "clustering_time: " << time << endl;
    cout<<"Calculating silhouette..."<<endl;
    out << "Silhouette: [";
    for(auto s : getSilhouette()){
        out << s << ", ";
    }
    out << "]" << endl;

    if(getGeneralParameters()->isComplete()){
        i = 0;
        for(const auto& cluster : clusters){
            out << "CLUSTER-"<< i+1 <<" {";
            for(auto obj : cluster.second){
                out << obj->getId() << ", ";
            }
            out << "}" << endl;
            i++;
        }
    }
    out << endl;
}

void Cluster::clear() {
    clusters.clear();
}

void Cluster::setOutputStream() {
    out.open(getGeneralParameters()->getOutputFilename(), ofstream::out);
}
