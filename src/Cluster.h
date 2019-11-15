#ifndef ALGORITHMS_PROJECT_CLUSTER_H
#define ALGORITHMS_PROJECT_CLUSTER_H

#include "GeneralParameters.h"

using namespace std;

class Cluster {
private:
    GeneralParameters* gen_params;

    Dataset* data;
public:

    GeneralParameters *getGeneralParameters() const {
        return gen_params;
    }

    void setGeneralParameters(GeneralParameters *genParams) {
        gen_params = genParams;
    }

    Dataset *getDataset() const {
        return data;
    }

    void setData(Dataset *data) {
        this->data = data;
    }

};

#endif //ALGORITHMS_PROJECT_CLUSTER_H
