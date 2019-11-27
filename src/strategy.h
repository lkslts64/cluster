#ifndef STRATEGY_H
#define STRATEGY_H
#include <random>
#include <vector>
#include "Object.h"
#include "Cluster.h"
#include "Dataset.h"
#include "LSH.h"
#include "kmeans.h"
#define DBA_THRESHOLD 1
#define KMEANS_THRESHOLD 0.5

using namespace std;

class Strategy {
protected:
    Cluster* cluster;
public:
    virtual ~Strategy(){}
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
private:
    DistanceMetric* metric;
public:
    LloydAssignment(Cluster* cluster);
    void execute();
};

class InverseAssignment : public AssignmentStrategy{
private:
    LSH* lsh;
    bool hasVectors;
public:
    InverseAssignment(Cluster* cluster);
    ~InverseAssignment();
    void execute();
};

class UpdateStrategy : public Strategy {
public:
    virtual bool execute() = 0;
};

class PAMUpdate : public UpdateStrategy{
private:
    DistanceMetric* metric;
public:
    PAMUpdate(Cluster* cluster);
    ~PAMUpdate();
    bool execute();
};

class CentroidUpdate : public UpdateStrategy{
    DistanceMetric* metric;
    vector<Kmeans *> algos;
public:
    CentroidUpdate(Cluster* cluster){
        this->cluster = cluster;
        auto dataset = cluster->getDataset();
        if (dataset->getHasVectors()) 
            for (int i = 0; i < cluster->getGeneralParameters()->getNumOfClusters(); i++) 
                algos.push_back(new KmeansPoints(KMEANS_THRESHOLD,dataset->getDimension()));
        else 
            for (int i = 0; i < cluster->getGeneralParameters()->getNumOfClusters(); i++) 
                algos.push_back(new DBA(DBA_THRESHOLD));

        if(cluster->getDataset()->getHasVectors())
            metric = new Manhattan;
        else
            metric = new DTW;
    }
    ~CentroidUpdate(){delete metric;}
    bool execute();
};


#endif