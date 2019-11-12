#include "Projection.h"
#include "RelevantTraversals.h"

void Projection::buildTraversalsMatrix(int size){
    for (int i = 0; i < size; ++i) {
        vector<RelevantTraversals *> line;
        // Create traversals for two curves with lengths i + 1, j + 1 respectively.
        // Save memory by starting j from i, as i,j and j,i have the same traversals
        for (int j = 0; j < size; ++j)
            line.push_back(new RelevantTraversals(i + 1, j + 1, this));
        traversalsMatrix.push_back(line);
    }
}

void Projection::setNormalMatrix(double epsilon) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(0, 1);

    int dimension = 2;
    int k = round((-2.0 * (log(epsilon)/log(2))) / epsilon);

    if(k<0)
        k = 4;

    for (int i = 0; i < k; ++i) {
        vector<double> v;
        for (int j = 0; j < dimension; ++j)
            v.push_back(distribution(gen));
        normalMatrix.push_back(v);
    }
}

void Projection::printNormalMatrix(){
    for(auto v : normalMatrix){
        for(auto num : v){
            cout << num << " ";
        }
        cout << endl;
    }
}

const string &Projection::getAlgorithm() const {
    return algorithm;
}

void Projection::putDataToHashTables() {
    for(auto obj : getDataset()->getData()){
        cout << obj->getId() << endl;
        Curve *curve = dynamic_cast<Curve *>(obj);
        int index = curve->getPoints().size();
        for(auto traversals : traversalsMatrix.at(index-1)){
            traversals->addToHashTables(curve);
        }
    }
}

void Projection::putDataToCubes() {
    for(auto obj : getDataset()->getData()){
        cout << obj->getId() << endl;
        Curve *curve = dynamic_cast<Curve *>(obj);
        int index = curve->getPoints().size();
        for(auto traversals : traversalsMatrix.at(index-1)){
            traversals->addToCubes(curve);
        }
    }
}
