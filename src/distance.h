#ifndef DISTANCE_H
#define DISTANCE_H
#include "Point.h"

class DistanceMetric {
    public:
    virtual double dist(Object* obj1,Object *obj2) = 0;
    virtual ~DistanceMetric(){};
};

class Manhattan : public DistanceMetric {
    public:
    double dist(Object *obj1,Object *obj2);
};

struct DTWTuple {
    int predecessor;
    double dist;
}; 

struct IndexPairs {
    int p1;
    int p2;
};


class DTW : public DistanceMetric {
    enum Predecessor {left,up,diagonal,start};
    struct DTWTuple **arr;
    int c1Len;
    int c2Len;
    //returns min of the first three values and sets predecessor 
    int min(double left,double up,double diagonal,int *predecessor);
    double _dist(Object *obj1,Object *obj2);
    void free();
    public:
    double distWithIndexPairs(Object *obj1,Object *obj2,vector<struct IndexPairs> *indexPairs);
    double dist(Object *obj1,Object *obj2);
    void backtrack(vector<struct IndexPairs> *ipairs);
};

#endif