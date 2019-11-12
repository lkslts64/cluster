#include <random>
#include <vector>
#include  <string.h>
#include "hasher.h"
#include "Point.h"
#include "utils.h"

using namespace std;

//TODO: set window size based on dataset (for better point grouping).
//needs to be done inside lsh. We could set it based on some metrics e.g. 
//based on the highest coordinate of a point and minimum (generally based 
//on change-variation of points).

PointHasher::PointHasher(int ampSize,int numDimension,int window) {
    this->amplificationSize = ampSize;
    this->numDimension = numDimension;
    this->window = window;
    partialHashRange = pow(2,int(32/amplificationSize));
    generateGrids();
    powModuloMem = new int[numDimension];
    memset(powModuloMem, 0, numDimension);
}
PointHasher::~PointHasher() {
    delete[] powModuloMem;
}

void PointHasher::generateGrids() {
    random_device r;
    default_random_engine e1(r());
    uniform_real_distribution<double> uniform_dist(0, window);
    for(int i = 0; i < amplificationSize ; i++){
        vector<double> grid;
        for (int j = 0; j < numDimension; j++) {
            grid.push_back(uniform_dist(e1));
        }
        grids.push_back(grid);
    }
}

int PointHasher::hash(Point* point,int hashIndex) const {
    vector<double> coordinates = point->getCoordinates();
    int coefficient = 0xffffffff-5;
    int sum = 0,i = 0,j = numDimension - 1;
    for (auto c :coordinates) {
        int gridCell = floor( double(c - grids.at(hashIndex).at(i)) / double(window) );
        if (!powModuloMem[j])
            powModuloMem[j] = powModulo(coefficient,j,partialHashRange);
        sum += gridCell * powModuloMem[j];
        i++;
        j--;
    }
    return modulo(sum, partialHashRange);
}

int PointHasher::operator()(Object *obj, bool insert) const {
    Point *point = dynamic_cast<Point *>(obj);
    int numPartialHashBits = 32/amplificationSize;
    int res = 0;
    int partialHash;
    //calculate each partial hash and concatenate them in res
    for (int i =0; i < amplificationSize; i++) {
        partialHash = hash(point,i);
        res |= partialHash << i*numPartialHashBits;
    }

    return res;
}