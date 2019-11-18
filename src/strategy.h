#ifndef STRATEGY_H
#define STRATEGY_H
#include <random>
#include <vector>
#include "Object.h"
#include "Cluster.h"
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
public:
    SpreadOutInit(Cluster* cluster){
        this->cluster = cluster;
    }
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
    virtual void execute() = 0;
};

class PAMUpdate : public UpdateStrategy{
public:
    PAMUpdate(Cluster* cluster){
        this->cluster = cluster;
    }
    void execute();
};

class CentroidUpdate : public UpdateStrategy{
public:
    CentroidUpdate(Cluster* cluster){
        this->cluster = cluster;
    }
    void execute();
};


#endif