#ifndef ALGORITHMS_PROJECT_CUBE_H
#define ALGORITHMS_PROJECT_CUBE_H
#include <cmath>
#include <random>
#include "LSH.h"

class Cube : public ANN_Structure {
private:

    int dimension = 3; bool dimension_given = false;
    int max_checked = 10;
    int max_probes = 2;

    LSH* lsh;

    unordered_map<size_t, bool> * binaryMaps;

    size_t numberOfVertices;
    vector<Object *> * vertices;

public:

    Cube(DistanceMetric * dmetric){
        lsh = new LSH(dmetric);
        lsh->setNumOfFunctions(4);
    }
    ~Cube(){delete lsh;}

    bool isDimensionGiven() const {return dimension_given;}
    int getDimension() const {return dimension;}
    int getMaxChecked() const {return max_checked;}
    int getMaxProbes() const {return max_probes;}
    auto getLsh() const {return lsh;}
    size_t getNumberOfVertices() const {return numberOfVertices;}
    auto getVertices() const {return vertices;}
    auto getBinaryMaps() const {return binaryMaps;}

    void setDimension(int dimension) {
        dimension_given = true;
        this->dimension = dimension;
        lsh->setNumOfHashTables(dimension);
    }
    void setMaxChecked(int maxChecked) {
        max_checked = maxChecked;
    }
    void setMaxProbes(int maxProbes) {
        max_probes = maxProbes;
    }

    void createBinaryMaps();
    void createVertices();
    void allocateBinaryMaps();
    void addToBinaryMap(Object *obj);
    void allocateVertices();
    void addToVertices(Object *obj);
    void test_print_binaryMaps();
    void test_print_vertices();
};

#endif //ALGORITHMS_PROJECT_CUBE_H
