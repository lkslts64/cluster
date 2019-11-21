#include <random>
#include <assert.h>
#include "kmeans.h"
#include "distance.h"

using namespace std;

DBA::DBA(double stopThreshold) : Kmeans(stopThreshold) {
    this->metric = new DTW();
}

Object *DBA::centroid(bool *stop) {
    //auto _prevCentroid = currCentroid;
    centroidLen = meanLength();
    currCentroid = pickRandomFilterShort();
    while(true)  {
        vector<set<Point,point_compare>> psetVec;
        vector<Point> pvec;
        auto dtw = dynamic_cast<DTW *>(metric);
        auto _prevCentroid = currCentroid;
        auto centro = dynamic_cast<Curve*>(currCentroid);
        for (int i = 0; i < centroidLen; i++)
            psetVec.push_back(set<Point,point_compare>());
        auto ipairs = vector<struct IndexPairs>();
        for (auto obj : objs) {
            auto c = dynamic_cast<Curve *>(obj); 
            dtw->distWithIndexPairs(c,currCentroid,&ipairs);
            for (auto pair : ipairs) {
                psetVec.at(pair.p2).insert(c->getPoint(pair.p1));
            }
            ipairs.clear();
        }
        for (int i =0; i < centroidLen; i++) {
            pvec.push_back(mean(psetVec.at(i)));
        }
        currCentroid = new Curve(pvec);
        centro = dynamic_cast<Curve*>(currCentroid);
        //condition to stop current update 
        if (metric->dist(_prevCentroid,currCentroid) < stopThreshold)
            break;
        psetVec.clear();
        pvec.clear();
        //return currCentroid;
    }
    //condition to stop clusterizing
    if (prevCentroid != nullptr) {
        if (canStop()) {
            *stop = true;
        } else {
            *stop = false;
        }
    } else {
        *stop = false;
    }
    //set prev to be curren so we can compare at next 
    //invokation of centroid()
    prevCentroid = currCentroid;
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
    for (auto obj: objs) {
        auto c = dynamic_cast<Curve *>(obj); 
        sum += c->getPoints().size();
    }
    return sum / objs.size();
}

//pick a random curve with length > centroidLen
//TODO:this is inneficient but works
Curve *DBA::pickRandomFilterShort() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<int> curveDist(0,objs.size()-1);
    //TODO:transform set-> vector so we can index it.
    //this is very costly assuming the set will 
    //many curves.
    vector<Curve *> _curves (objs.begin(),objs.end());
    while (true) {
        auto i = curveDist(rng);
        if (_curves[i]->getPoints().size() >= centroidLen)
            return pickRandomSubsequence(_curves[i]);
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
    vector<Point> pvec;
    auto end = curve->getPoints().begin()+centroidLen-1;
    for (int i = start; i < start+centroidLen; i++) {
        pvec.push_back(curve->getPoint(i));
    }
    return new Curve(pvec);
}