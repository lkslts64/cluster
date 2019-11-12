#ifndef ALGORITHMS_PROJECT_CURVE_H
#define ALGORITHMS_PROJECT_CURVE_H
#include <vector>
#include "Object.h"
#include "Point.h"

using namespace std;

class Curve : public Object{

private:

    std::vector<Point> points;

public:

    Curve(string id);
    Curve(vector<Point> points);
    ~Curve();
    std::vector<Point> getPoints();
    void setPoints(vector<Point> pVec);
    Point getPoint(int i);
    void foo(){}
};


#endif //ALGORITHMS_PROJECT_CURVE_H
