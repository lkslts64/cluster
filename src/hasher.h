#ifndef HASHER_H
#define HASHER_H 
#include <random>
#include "Object.h"
#include "Point.h"
#include "Curve.h"
#include <tuple>

#define WINDOW_SIZE 100

class Hasher {
    public:
        virtual int operator()(Object *obj, bool insert = true) const {};
};

//Create an instance per LSHHashtable.
//Call hash(Object*) and the return value will be
//the index of the bucket that Object should be stored.
class PointHasher : public Hasher {
    private:
        vector<vector<double>> grids ;
        //we can set window based on dataset range of values.
        int window = WINDOW_SIZE;
        int amplificationSize;
        int numDimension;
        int partialHashRange;
        //Memoization for powModulo func.
        int * powModuloMem;
        void generateGrids();
    public:
        PointHasher();
        PointHasher(int,int,int);
        ~PointHasher();
        //compute the ith hash of Object obj
        int hash(Point *point,int i) const;
        //compute the concatenation of all hash functions i=0,1,..amplificationSize
        int operator() (Object* obj, bool insert = true) const;
};

class CurveHasher : public Hasher {
    private:
        int numDimension;
        //delta in slides
        double gridSize;
        //vector t in slides
        double *shiftedGrid;
        //max length of curve (maybe all have the same length
        //- they are already padded-). 
        int max;
        PointHasher *phasher;
        Point *vectorize(double **snapedCurve);
        int isConsecutiveDuplicate(double **snapedCurve,int i);
        double *snap(Point *point);
        double **snap(Curve *curve);
        double snap(double coordinate,int i);
        Curve *pad(Curve *curve);
        //double roundCoordinateV2(Point *point,int i);
    public: 
        CurveHasher();
        CurveHasher(int,int,double,int,int);
        ~CurveHasher();
        int operator() (Object *obj, bool insert = true) const;
};

class CurveProjectionHasher : public PointHasher {
private:
    vector<vector<double>> normalMatrix;
    vector<tuple<int, int>> traversal;
public:
    CurveProjectionHasher(int ampSize,int numDimension,int window, const vector<vector<double>>& normalMatrix, vector<tuple<int, int>> traversal)
                        : PointHasher(ampSize, numDimension, window){
        this->normalMatrix = normalMatrix;
        this->traversal = traversal;
    }
    int operator() (Object* obj, bool insert) const{
        //construct point from curve
        Curve* curve = dynamic_cast<Curve *>(obj);
        Point* curvePoint = new Point("");
        auto points = curve->getPoints();
        for(auto tuple : traversal){
            for(auto normal1 : normalMatrix){
                double coordinate = 0;
                int i = 0;
                for(double normal2 : normal1){
                    if(insert)
                        coordinate += normal2 * points.at(get<0>(tuple)).getCoordinate(i++);
                    else
                        coordinate += normal2 * points.at(get<1>(tuple)).getCoordinate(i++);
                }
                curvePoint->addCoordinateLast(coordinate);
            }
        }
        //call super
        return PointHasher::operator()(curvePoint);
    }
};

#endif