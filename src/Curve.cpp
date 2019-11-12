#include "Curve.h"

Curve::Curve(string id) : Object(id) {}

Curve::Curve(vector<Point> points) { this->points = points;}

Curve::~Curve() {}

std::vector<Point> Curve::getPoints() {
    return points;
}

Point Curve::getPoint(int i) {
    return points.at(i);
}

void Curve::setPoints(vector<Point> pVec) {
    points = pVec;
}