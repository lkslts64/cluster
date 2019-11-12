#ifndef ALGORITHMS_PROJECT_POINT_H
#define ALGORITHMS_PROJECT_POINT_H
#include <vector>
#include <string>
#include "Object.h"
using namespace std;
class Point : public Object{

private:

    vector<double> coordinates;

public:
    Point(string id);
    Point(vector<double> coordinates);
    ~Point();
    void foo(){}

    void addCoordinateLast(double coordinate);

    double getCoordinate(int position);
    std::vector<double> getCoordinates();
    bool operator== (Point const point);
    bool operator< (Point const point);
};


#endif //ALGORITHMS_PROJECT_POINT_H
