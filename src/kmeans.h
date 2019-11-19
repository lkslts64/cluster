#ifndef KMEANS_H
#define KMEANS_H
#include <vector>
#include <set>
#include "Curve.h"
#include "distance.h"
#include "Point.h"

class Kmeans {
    protected:
    set<Object *> objs;
    Object *currCentroid;
    Object *prevCentroid;
    DistanceMetric *metric;
    double stopThreshold;
    public:
    Kmeans(set<Object *> objs,double stopThreshold) {
        this->objs = objs;
        this->stopThreshold = stopThreshold;
        this->currCentroid = nullptr;
        this->prevCentroid = nullptr;
    }
    bool canStop() {
        if (prevCentroid == nullptr)
            return false;
        if (metric->dist(currCentroid,prevCentroid) < stopThreshold) 
            return true;
        return false;
    }
    virtual Object *centroid(bool *stop) = 0;

};

class KmeansPoints : public Kmeans {
    int numDimension;
    public:
        KmeansPoints(set<Object*> points,double stopThreshold,int numDimension) : 
        Kmeans(points,stopThreshold) {
            this->numDimension = numDimension;
            this->metric = new Manhattan();
        };
        Object * centroid(bool *stop) {
            double size = double(objs.size());
            vector<double> centro(numDimension,0.0);
            prevCentroid = currCentroid;
            for (auto obj : objs) {
                auto p = dynamic_cast<Point *>(obj);
                for (int i =0; i < p->getCoordinates().size();i++) {
                    centro.at(i) += p->getCoordinate(i)/size;
                }
            }
            currCentroid = new Point(centro);
            *stop = canStop();
            return currCentroid; 
        }

};


struct point_compare {
   bool operator() (const Point p1,const Point p2) {
       auto point1 = p1;
       auto point2 = p2;
    if (point1.getCoordinates().size() !=  point2.getCoordinates().size())
        return true;
    for (int i =0; i<point2.getCoordinates().size(); i++) 
        if (point1.getCoordinate(i) == point2.getCoordinate(i))
            continue;
        else if (point1.getCoordinate(i) <point2.getCoordinate(i))
            return true;
        else 
            return false;
    return false;
   }
};


class DBA : public Kmeans {
    //array of point sets
    int centroidLen;
    //algorithm ends if dist(nextCentroid,currCentroid) < endDistThreshold
    int meanLength();
    Point mean(set<Point,point_compare> pset) ;
    Curve *pickRandomFilterShort();
    Curve *pickRandomSubsequence(Curve *curve);
    public:
        DBA(set<Object *> curves,double stopThreshold);
        Object* centroid(bool *stop);
};

#endif