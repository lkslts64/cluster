#ifndef ALGORITHMS_PROJECT_CLUSTER_H
#define ALGORITHMS_PROJECT_CLUSTER_H

#include <set>
#include <map>
#include <fstream>
#include "GeneralParameters.h"

using namespace std;

class Cluster {
private:
    GeneralParameters* gen_params;

    Dataset* data;

    /**
     * Keys:    current centers
     * Value:   set of objects that belong to this center
     */
    map<Object *, set<Object *>> clusters;
    ofstream out;
public:

    GeneralParameters *getGeneralParameters() {return gen_params;}
    void setGeneralParameters(GeneralParameters *genParams) {gen_params = genParams;}
    Dataset *getDataset() {return data;}
    void setData(Dataset *data) {this->data = data;}
    map<Object *, set<Object *>> getClusters() {return clusters;}
    void addToCluster(Object * center, Object * obj);
    set<Object *> getCenters();
    void setCenters(const set<Object *>& centers);
    void testPrintClusterKeysAndSize();
    vector<double> getSilhouette();
    void output(string firstLine);

    void clear();

    void setOutputStream();
};

#endif //ALGORITHMS_PROJECT_CLUSTER_H
