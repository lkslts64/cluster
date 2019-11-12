#include "Point.h"

Point::Point(string id) :Object(id) {}

Point::Point(vector<double> coordinates) {
    this->coordinates = coordinates;    
}
Point::~Point() { coordinates.clear();}

void Point::addCoordinateLast(double coordinate){
    this->coordinates.push_back(coordinate);
}

double Point::getCoordinate(int position){
    return this->coordinates.at(position);
}

std::vector<double> Point::getCoordinates() {
    return this->coordinates;
}

bool Point::operator== (Point const point) {
    //int min = point.coordinates.size() < coordinates.size() ? point.coordinates.size() : coordinates.size();
    if (point.coordinates.size() !=  coordinates.size())
        return 0;
    for (int i =0; i<coordinates.size(); i++) 
        if (point.coordinates.at(i) != coordinates.at(i))
            return 0;
    return 1;
}

bool Point::operator< (Point const point) {
    if (point.coordinates.size() !=  coordinates.size())
        return 1;
    for (int i =0; i<coordinates.size(); i++) 
        if (point.coordinates.at(i) == coordinates.at(i))
            continue;
        else if (point.coordinates.at(i) < coordinates.at(i))
            return true;
        else 
            return false;
    return false;

}
