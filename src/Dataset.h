#ifndef ALGORITHMS_PROJECT_DATASET_H
#define ALGORITHMS_PROJECT_DATASET_H
#include <vector>
#include "Point.h"
using namespace std;

class Dataset {
    private:
        bool hasVectors;
        //default to 2 for curves
        int dimension;
        size_t size;
        //minLength of Curve for Curves - minCoordinate for Points
        double min;
        //maxLength of Curve for Curves - maxCoordinate for Points
        double max;
        //unnecessary for Curves
        int mean;
        vector<Object *> data;
    public:
        Dataset(vector<Object *> data);
        Dataset(){};
        void setSize(size_t sz);
        void setMax(double max);
        void setMin(double min);
        void setMean(int mean);
        void setDimension(int d);
        void add(Object *obj);
        vector<Object *> getData();
        size_t getSize();
        int getDimension();
        //min coordinate for points 
        //min length for curves
        double getMin();
        //max coordinate for points 
        //max length for curves
        double getMax();
        int getMean();
        void setHasVectors(bool hasVectors);
        bool getHasVectors();
};

#endif //ALGORITHMS_PROJECT_DATASET_H
