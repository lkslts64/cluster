#ifndef STRATEGY_H
#define STRATEGY_H
#include <random>
#include <vector>
#include "Object.h"
#include "Cluster.h"
#include "Dataset.h"
#include "LSH.h"

using namespace std;

class Strategy {
protected:
    Cluster* cluster;
};

//functors for initialization strategy
class InitStrategy : public Strategy{
public:
    virtual void execute() = 0;
};

/**
 * Randomly select k objects as centers
 */
class RandomInit : public InitStrategy {
public:
    RandomInit(Cluster* cluster){
        this->cluster = cluster;
    }
    void execute();
};

class SpreadOutInit : public InitStrategy {
    set<Object *> centers;
    //index of each center is dataset vector
    set<int> centersIndex;
    DistanceMetric *metric;
public:
    SpreadOutInit(Cluster* cluster){
        this->cluster = cluster;
        if(cluster->getDataset()->getHasVectors()) 
            this->metric = new Manhattan();
        else 
            this->metric = new DTW();
    }
    SpreadOutInit(bool hasVectors) {
        if(hasVectors) 
            this->metric = new Manhattan();
        else 
            this->metric = new DTW();

    }
    set<Object *> getCenters() { return centers; }
    void init(vector<Object *> objs);
    int search(vector<double> distArr,double x);
    void _execute(vector<Object *> objs,int numClusters);
    void execute();
};

class AssignmentStrategy : public Strategy{
public:
    virtual void execute() = 0;
};

class LloydAssignment : public AssignmentStrategy{
public:
    LloydAssignment(Cluster* cluster){
        this->cluster = cluster;
    }
    void execute();
};

class InverseAssignment : public AssignmentStrategy{
private:
    LSH* lsh;
    bool hasVectors;
public:
    InverseAssignment(Cluster* cluster);
    void execute();
};

class UpdateStrategy : public Strategy {
public:
    virtual bool execute() = 0;
};

class PAMUpdate : public UpdateStrategy{
public:
    PAMUpdate(Cluster* cluster){
        this->cluster = cluster;
    }
    bool execute();
};

class CentroidUpdate : public UpdateStrategy{
public:
    CentroidUpdate(Cluster* cluster){
        this->cluster = cluster;
    }
    bool execute();
};


#endif