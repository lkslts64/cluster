#include <math.h>
#include <cfloat>
#include "distance.h"
#include "LSH.h"

double Manhattan::dist(Object *obj1,Object *obj2){
    auto p1 = dynamic_cast<Point *>(obj1);
    auto p2 = dynamic_cast<Point *>(obj2);
    if (p1->getCoordinates().size() != p2->getCoordinates().size())
        return -1;
    double sum = 0;
    int sz = p1->getCoordinates().size();
    for(int i =0; i < sz;i++)
        sum += fabs(p1->getCoordinate(i) - p2->getCoordinate(i));
    return sum;
}

double euclidean(Point p1,Point p2) {
    if (p1.getCoordinates().size() != p2.getCoordinates().size())
        return -1;
    double dist;
    double sum = 0.0;
    for (int i=0; i < p1.getCoordinates().size(); i++) {
        dist = p1.getCoordinate(i) - p2.getCoordinate(i);
        sum += dist*dist;
    }
    return sqrt(sum);
}


int DTW::min(double left,double up,double diagonal,int *predecessor) {
    if (left <= up && left <= diagonal) {
        *predecessor = this->left;
        return left;
    }
    else if (up <= left && up <= diagonal) {
        *predecessor = this->up;
        return up;
    }
    else {
        *predecessor = this->diagonal;
        return diagonal;
    }
}

void DTW::backtrack(vector<struct IndexPairs> *ipairs) {
    //auto ipairs = new vector<struct IndexPairs>();
    struct IndexPairs ipair;
    auto i = c1Len-1;
    auto j = c2Len-1;
    //push last pair
    ipair = {i,j};
    ipairs->push_back(ipair);
    while (arr[i][j].predecessor != this->start) {
        switch (arr[i][j].predecessor) {
        case this->left:
            j--;
            break;
        case this->up:
            i--;
            break;
        case this->diagonal:
            i--;
            j--;
            break;
        }
        ipair = {i,j};
        ipairs->insert(ipairs->begin(),ipair);
    }
}



double DTW::_dist(Object *obj1,Object *obj2){
    auto c1 = dynamic_cast<Curve *>(obj1);
    auto c2 = dynamic_cast<Curve *>(obj2);
    c1Len = c1->getPoints().size();
    c2Len = c2->getPoints().size();
    int predecessor;
    arr = new struct DTWTuple*[c1Len];
    for (int i =0; i < c1Len; i++)
        arr[i] = new struct DTWTuple[c2Len];
    for (int i =0; i < c1Len; i++) {
        for (int j =0; j < c2Len; j++) {
            if (!i && !j) {//both zero
                arr[i][j].dist = euclidean(c1->getPoint(i),c2->getPoint(j));
                arr[i][j].predecessor = this->start;
            }
            else if (!i) {
                arr[i][j].dist = arr[i][j-1].dist + euclidean(c1->getPoint(i),c2->getPoint(j));
                arr[i][j].predecessor = this->left;
            }
            else if (!j) {
                arr[i][j].dist = arr[i-1][j].dist + euclidean(c1->getPoint(i),c2->getPoint(j));
                arr[i][j].predecessor = this->up;
            }
            else {
                arr[i][j].dist = this->min(arr[i][j-1].dist,arr[i-1][j].dist,arr[i-1][j-1].dist,&predecessor) +
                euclidean(c1->getPoint(i),c2->getPoint(j));
                arr[i][j].predecessor = predecessor;
            }
        }
    }
    return arr[c1Len-1][c2Len-1].dist;
}

void DTW::free() {
    for (int i =0; i < c1Len; i++)
        delete arr[i];
    delete arr;
}

double DTW::dist(Object *obj1,Object *obj2){
    auto res = _dist(obj1,obj2);
    free();
    return res;
}

double DTW::distWithIndexPairs(Object *obj1,Object *obj2,vector<struct IndexPairs> *indexPairs) {
    double dist = this->_dist(obj1,obj2);
    backtrack(indexPairs);
    free();
    return dist;
}

DTW::~DTW() {
    delete []arr;
}
