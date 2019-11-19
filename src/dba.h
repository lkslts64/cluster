#ifndef DBA_H
#define DBA_H
#include <vector>
#include <set>
#include "Curve.h"
#include "Point.h"

/*
class FilterFunc {
    virtual bool operator() (Curve *) = 0;
};

class FilterSmallLen {
    bool operator() (Curve *c,int threshold) { 
        if (c->getPoints().size() > threshold)
            return true;
        return false;
     }
};
*/


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


class DBA {
    set<Object *> curves;
    //array of point sets
    int centroidLen;
    Curve * currCentroid;
    Curve * prevCentroid;
    //algorithm ends if dist(nextCentroid,currCentroid) < endDistThreshold
    double endDistThreshold;
    int meanLength();
    Point mean(set<Point,point_compare> pset) ;
    Curve *pickRandomFilterShort();
    Curve *pickRandomSubsequence(Curve *curve);
    public:
        DBA(set<Object *> curves);
        Curve* run();
};
#endif