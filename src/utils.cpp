#include <sys/stat.h>
#include <vector>
#include <algorithm>
#include <iostream>
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

bool is_number(string s)
{
    return !s.empty() &&
            find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void test_print_data_points(Dataset *data) {
    auto objs = data->getData();
    vector<Point *> points(objs.begin(),objs.end());
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
    for(auto curve: curves){
        cout << "CHECKING ITEM ID: " << curve->getId() << endl;
        for(auto point: curve->getPoints()){
            cout << "(" << point.getCoordinate(0) << "," << point.getCoordinate(1) << ") ";
        }
        cout << endl;
    }
    cout << data->getDimension() << " " << data->getSize() << endl;
}

double min(double coordinate,double min) {
    return coordinate < min ? coordinate : min;
}

double max(double coordinate,double max) {
    return coordinate > max ? coordinate : max;
}

void test_print_query_data(QueryDataset *data) {
    auto objs = data->getData();
    vector<Point *> points(objs.begin(),objs.end());
    for (int i = 0; i < points.size(); i++) {
        cout << "CHECKING ITEM ID: " << points[i]->getId() << endl;
        auto coords = points[i]->getCoordinates();
        for (int j = 0; j < coords.size(); ++j) {
            cout << coords[j] << " ";
        }
        cout << endl;
    }
    cout << data->getDimension() << " " << data->getSize() << " " << data->getRadius() << endl;
}

int modulo(int a, int b){
    if(a>=0)
        return a%b;
    return a%b + b;
}