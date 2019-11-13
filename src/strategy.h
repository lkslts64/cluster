#ifndef STRAT_H
#define STRAT_H
#include <random>
#include <vector>
#include "Object.h"

using namespace std;

//functors for initialization strategy
class InitStrategy {
    public:
    virtual Object *operator() (vector<Object *> objs) = 0;
};

class RandStrategy : public InitStrategy {
    public:
    Object *operator() (vector<Object *> objs) {
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<int> dist(0,objs.size()-1);
        return objs.at(dist(rng));
    }
};

class SpreadOutStrategy : public InitStrategy {
    //Instructor didn't explain it well so cant implement it yet.
};


#endif