#ifndef ALGORITHMS_PROJECT_CLUSTER_H
#define ALGORITHMS_PROJECT_CLUSTER_H

#include <set>
#include "GeneralParameters.h"

using namespace std;

class Cluster {
private:
    GeneralParameters* gen_params;

    Dataset* data;

    //current k-Means of Dataset
    set<Object *> k_means;

public:

    GeneralParameters *getGeneralParameters() {
        return gen_params;
    }

    void setGeneralParameters(GeneralParameters *genParams) {
        gen_params = genParams;
    }

    Dataset *getDataset() {
        return data;
    }

    void setData(Dataset *data) {
        this->data = data;
    }

    set<Object *> getKMeans() {
        return k_means;
    }

    void setKMeans(set<Object *> kMeans) {
        this->k_means = kMeans;
    }
};

#endif //ALGORITHMS_PROJECT_CLUSTER_H
