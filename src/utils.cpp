#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <limits>
#include "utils.h"
#include "Curve.h"

using namespace std;

// computes base^exp % div , without using pow().This
// func ensures no overflow will occur during the above
// computation.Optimized with a divided & conquer technique.
int powModulo(int base,int exp,int div) {
    if(exp == 0) {
        return 1;
    } else if (exp == 1) {
        return base % div;
    } else if (exp % 2 == 0) {
        return (powModulo(base,exp/2,div)*powModulo(base,exp/2,div)) % div;
    } else {
        return (powModulo(base,exp-1,div)*powModulo(base,1,div)) % div;
    }
}

// check if file exists
bool file_exists(const char* filename){
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}

void test_print_data_points(Dataset *data) {
    auto objs = data->getData();
    vector<Point *> points(objs.begin(),objs.end());
    cout.precision(numeric_limits<double>::max_digits10);
    for (int i = 0; i < points.size(); i++) {
        cout << "CHECKING ITEM ID: " << points[i]->getId() << endl;
        auto coords = points[i]->getCoordinates();
        for (int j = 0; j < coords.size(); ++j) {
            cout << coords[j] << " ";
        }
        cout << endl;
    }
    cout << data->getDimension() << " " << data->getSize() << endl;
}

void test_print_data_curves(Dataset *data){
    auto objs = data->getData();
    vector<Curve *> curves(objs.begin(),objs.end());
    cout.precision(numeric_limits<double>::max_digits10);
    for(auto curve: curves){
        cout << "CHECKING ITEM ID: " << curve->getId() << endl;
        for(auto point: curve->getPoints()){
            cout << "(" << point.getCoordinate(0) << "," << point.getCoordinate(1) << ") ";
        }
        cout << endl;
    }
    cout << data->getDimension() << " " << data->getSize() << endl;
}

void test_print_data(Dataset *data){
    if(data->getHasVectors())
        test_print_data_points(data);
    else
        test_print_data_curves(data);
}

double min(double coordinate,double min) {
    return coordinate < min ? coordinate : min;
}

double max(double coordinate,double max) {
    return coordinate > max ? coordinate : max;
}

int modulo(int a, int b){
    if(a>=0)
        return a%b;
    return a%b + b;
}

//returs min distance of target with objs and
//sets closest as the Object that was closer 
//to target.
double minDist(DistanceMetric *metric,Object *target,
    set<Object*> objs, Object *closest) {
        double min = numeric_limits<double>::max();
        double dist;
        for (auto obj: objs) {
            if ((dist = metric->dist(obj,target)) < min) {
                min = dist;
                closest = obj; 
            }
        }
        return min;
}

double minVec(vector<double> vec) {
    double min = numeric_limits<double>::max();
    for (auto v : vec) {
        if (v < min)
            min = v;
    }
    return min;
}
