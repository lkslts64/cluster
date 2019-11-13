#include <random>
#include <assert.h>
#include "dba.h"
#include "distance.h"

using namespace std;

DBA::DBA(vector<Curve *> curves) {
    this->curves = curves;
    centroidLen = meanLength();
    currCentroid = pickRandomFilterShort();
}

Curve *DBA::run() {
    auto dtw = new DTW();
    vector<set<Point,point_compare>> psetVec;
    vector<Point> pvec;
    while (prevCentroid == nullptr ||
     dtw->dist(currCentroid,prevCentroid) > endDistThreshold) {
        prevCentroid = currCentroid;
        for (int i = 0; i < centroidLen; i++)
            psetVec.push_back(set<Point,point_compare>());
        auto ipairs = vector<struct IndexPairs>();
        for (auto c : curves) {
            dtw->distWithIndexPairs(c,prevCentroid,&ipairs);
            for (auto pair : ipairs) {
                psetVec.at(pair.p1).insert(c->getPoint(pair.p2));
            }
        }
        for (int i =0; i < centroidLen; i++) {
            pvec.push_back(mean(psetVec.at(i)));
        }
        currCentroid = new Curve(pvec);
        ipairs.clear();
        psetVec.clear();
        pvec.clear();
    }
    return currCentroid;
}

Point DBA::mean(set<Point,point_compare> pset) {
    double sumX = 0;
    double sumY = 0;
    for (auto point : pset) {
        auto coords = point.getCoordinates();
        assert(coords.size() == 2); 
        sumX += coords.at(0);
        sumY += coords.at(1);
    }
    auto meanX = sumX/double(pset.size());
    auto meanY = sumY/double(pset.size());
    return Point(vector<double> {meanX,meanY}); 
}

int DBA::meanLength() {
    int sum = 0;
    for (auto c: curves) {
        sum += c->getPoints().size();
    }
    return sum / curves.size();
}

//pick a random curve with length > centroidLen
//TODO:this is inneficient but works
Curve *DBA::pickRandomFilterShort() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<int> curveDist(0,curves.size()-1);
    while (true) {
        auto i = curveDist(rng);
        if (curves[i]->getPoints().size() >= centroidLen)
            return pickRandomSubsequence(curves[i]);
    }
}

Curve *DBA::pickRandomSubsequence(Curve *curve) {
    random_device dev;
    mt19937 rng(dev());
    int randMax = curve->getPoints().size()-centroidLen;
    if (randMax == 0)
        return curve;
    uniform_int_distribution<int> curveLenDist(0,randMax);
    auto start = curveLenDist(rng);
    auto pointBegin = curve->getPoints().begin()+start;
    return new Curve(vector<Point> (pointBegin,pointBegin+centroidLen));
}