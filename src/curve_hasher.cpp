#include <random>
#include <vector>
#include <cmath>
#include <cfloat>
#include "LSH.h"
#include "Curve.h"
#include "Point.h"
#include "hasher.h"




//assume ai = 1 i =1,2,..d (from slides)
CurveHasher::CurveHasher(int numDimension,int ampSize,double min,int max,int pointHasherWindow) {
    this->numDimension = numDimension;
    this->max = max;
    gridSize = 4.0 * double(numDimension) * min;
    //TODO:set variables properly
    phasher = new PointHasher(ampSize,max*numDimension,pointHasherWindow);
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_real_distribution<double> uniform_dist(0,numDimension);
    shiftedGrid = (double *)malloc(numDimension * sizeof(double));
    for (int i = 0; i < numDimension;i++) {
        shiftedGrid[i] = uniform_dist(e1);
    }
}

CurveHasher::~CurveHasher() {
    free(shiftedGrid);
    free(phasher);
}

int CurveHasher::operator() (Object *obj, bool insert) const {
    Curve *curve = dynamic_cast<Curve *>(obj);
    auto c = pad(curve);
    auto point = vectorize(snap(c));
    auto bucket =  (*phasher)(point);
    free(point);
    return bucket;
}

//TODO: pad more efficiently without using a temp vector (pointVec)
Curve *CurveHasher::pad(Curve *curve) {
    vector<Point> pointVec  = (curve->getPoints());
    auto sz = pointVec.size();
    for (int i=0; i < max-sz; i++)
        pointVec.push_back((*new Point(vector<double> (numDimension,0xffff))));
    //sz = pointVec.size();
    //curve->setPoints(pointVec);
    return new Curve(pointVec);
}

//transform grid curve (snapedCurve) to a vector which is 
//equivalent to a Point.
Point *CurveHasher::vectorize(double **snapedCurve) {
    vector<double> vec;
    double sumCoordinates = 0;
    int coefficient = 10;
    for (int i =0; i<max; i++) {
        if (i != 0 && isConsecutiveDuplicate(snapedCurve,i))
            continue;
        for (int j =0; j < numDimension; j++) 
            vec.push_back(snapedCurve[i][j]);
    }
    //free memory allocated in snap.
    for (int i =0; i < max; i++) 
        free(snapedCurve[i]);
    free(snapedCurve);
    return new Point(vec);
}

int CurveHasher::isConsecutiveDuplicate(double **snapedCurve,int i) {
    for (int j =0; j < numDimension; j++) {
        if (snapedCurve[i][j] != snapedCurve[i-1][j])
            return 0;
    }
    return 1;
}

double **CurveHasher::snap(Curve *curve) {
    double **snapedCurve = (double **)malloc(max * sizeof(double *));
    for (int i=0; i< max; i++)
        snapedCurve[i] = snap(&curve->getPoint(i));
    return snapedCurve;
}

double *CurveHasher::snap(Point *point) {
    double *snapedPoint = (double *)malloc(numDimension * sizeof(double));
    for (int i = 0; i< numDimension; i++) {
        snapedPoint[i] = snap(point->getCoordinate(i),i);
    }
    return snapedPoint;
}

//round coordinate i of point(obj) to the nearest multiple
//of gridSize (starting from shiftedGrid[i]) and return the nearest multiple.
//Simpler solution than V2.
//Based on https://stackoverflow.com/questions/29557459/round-to-nearest-multiple-of-a-number
double CurveHasher::snap(double coordinate,int i) {
    double _gridSize = double(gridSize);
    double round =  coordinate + _gridSize/2.0;
    round -= fmod(round,_gridSize);
    double shiftDown = round - fabs(_gridSize - shiftedGrid[i]);
    double shiftUp = round + shiftedGrid[i];
    if (fabs(coordinate - shiftUp) < fabs(coordinate - shiftDown)) {
        return shiftUp;
    }
    return shiftDown;
}