#include <iostream>
#include <sstream>
#include <fstream>
#include <cfloat>
#include <string.h>
#include <limits>
#include <assert.h>
#include "parse_files.h"
#include "utils.h"
#include "distance.h"
#include "Curve.h"

using namespace std;

Dataset* parseInputFilePoints(string filename) {
    if(!file_exists(filename.c_str())){
        cout << "input file does not exist" << endl;
        exit(-1);
    };
    auto data = new Dataset();
    cout << "Parsing input file: " << filename << ", please wait..." << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int current_dimension = -1;
    double minCoordinate = DBL_MAX;
    double maxCoordinate = -DBL_MAX;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find(' '));
        auto point = new Point(item_id);
        //keep only the coordinates
        line = line.substr(line.find(' ') + 1);
        string token;
        stringstream line_stream(line);
        int dimension = 0;
        //add every coordinate to point
        while(line_stream >> token){
            auto coordinate = atof(token.c_str());
            minCoordinate = min(coordinate,minCoordinate);
            maxCoordinate = max(coordinate,maxCoordinate);
            point->addCoordinateLast(coordinate);
            dimension++;
        }
        if(current_dimension != -1 && current_dimension != dimension){
            cout << "Error in input file, non stable dimension" << endl;
        }
        current_dimension = dimension;
        size++;
        data->add(point);
    }
    data->setSize(size);
    data->setDimension(current_dimension);
    data->setMax(maxCoordinate);
    data->setMin(minCoordinate);
    //remove this if we dont care about the PointHasher 
    //window value. This call costs to much in terms of
    //processing.
    //data->setMean(meanOfMins(data,1000));
    return data;
}

//Calculate the mean distance of every point with his NN.
//Complexity: numDimension * n^2 / 2 
//We can use a better algorithm instead of bruteforce 
//like kd-tree of octree but it needs some work.
//Use this func only with a Dataset of Points.
int meanOfMins(Dataset *dataset,int limit, DistanceMetric* distanceMetric) {
    double sum = 0;
    int size = dataset->getSize();
    int i=0;
    auto data = dataset->getData();
    for(auto obj : data){
        Point* queryPoint = dynamic_cast<Point*>(obj);
        double distance = numeric_limits<double>::max();
        for(auto candidate : data){
            Point* candidatePoint = dynamic_cast<Point*>(candidate);
            double cur_dist;
            if(candidatePoint != queryPoint
               && (cur_dist = distanceMetric->dist(queryPoint, candidatePoint)) < distance){
                distance = cur_dist;
            }
        }
        i++;
        sum += distance/limit;
        if(i == limit){
            break;
        }
    }
    return sum;
}

Dataset* parseInputFileCurves(string filename) {
    if(!file_exists(filename.c_str())){
        cout << "input file does not exist" << endl;
        exit(-1);
    };
    auto data = new Dataset();
    cout << "Parsing input file: " << filename << ", please wait..." << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int minCurveLen = INT32_MAX;
    int maxCurveLen = INT32_MIN;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find('\t'));
        vector<Point> curveVec;
        line = line.substr(line.find_first_of("\t ") + 1);
        string token;
        stringstream line_stream(line);
        int curveLen;
        line_stream >> curveLen;
        maxCurveLen = max(maxCurveLen,curveLen);
        minCurveLen = min(minCurveLen,curveLen);
        line = line.substr(line.find_first_of("\t ") + 1);
        while(line_stream >> token){
            //ensure the right format is given : (coordinate,coordinate)
            assert(token[0] == '(');
            token = token.substr(1);
            size_t coordinateSz;
            vector<double> pointVec;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ',');
            token = token.substr(1);
            //spec doesn't match with actual format so we make some workarounds
            line_stream >> token;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ')');
            token = token.substr(1);
            curveVec.push_back((*new Point(pointVec)));
        }
        if (curveLen != curveVec.size()) {
            cout << "expected curve length doesn't match with actual curve length." << endl;
            exit(-1);
        }
        auto curve = new Curve(curveVec); 
        curve->setId(item_id);
        data->add(curve);
        size++;
    }
    data->setSize(size);
    data->setDimension(2);
    data->setMax(maxCurveLen);
    data->setMin(minCurveLen);
    return data;
}

QueryDataset* parseQueryFilePoints(string filename){
    if(!file_exists(filename.c_str())){
        cout << "query file does not exist" << endl;
        exit(-1);
    };
    auto data = new QueryDataset();
    cout << "Parsing query file: " << filename << endl;
    ifstream queryFile(filename.c_str());
    //get radius (bonus)
    string radius_line;
    getline(queryFile, radius_line);
    radius_line = radius_line.substr(radius_line.find(' ') + 1);
    data->setRadius(atof(radius_line.c_str()));
    string line;
    int size = 0;
    int current_dimension = -1;
    while(getline(queryFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find(' '));
        auto point = new Point(item_id);
        //keep only the coordinates
        line = line.substr(line.find(' ') + 1);
        string token;
        stringstream line_stream(line);
        int dimension = 0;
        //add every coordinate to point
        while(line_stream >> token){
            point->addCoordinateLast(atof(token.c_str()));
            dimension++;
        }
        if(current_dimension != -1 && current_dimension != dimension){
            cout << "Error in query file, non stable dimension" << endl;
            exit(-1);
        }
        current_dimension = dimension;
        size++;
        data->add(point);
    } 
    data->setSize(size);
    data->setDimension(current_dimension);
    return data;
}

//TODO: remove this func - same with parseInputFileCurves except return 
//types - avoid duplication.
QueryDataset* parseQueryFileCurves(string filename) {
    if(!file_exists(filename.c_str())){
        cout << "query file does not exist" << endl;
        exit(-1);
    };
    auto data = new QueryDataset();
    cout << "Parsing query file: " << filename << ", please wait..." << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int minCurveLen = INT32_MAX;
    int maxCurveLen = INT32_MIN;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find('\t'));
        vector<Point> curveVec;
        line = line.substr(line.find_first_of("\t ") + 1);
        string token;
        stringstream line_stream(line);
        int curveLen;
        line_stream >> curveLen;
        maxCurveLen = max(maxCurveLen,curveLen);
        minCurveLen = min(minCurveLen,curveLen);
        line = line.substr(line.find_first_of("\t ") + 1);
        while(line_stream >> token){
            //ensure the right format is given : (coordinate,coordinate)
            assert(token[0] == '(');
            token = token.substr(1);
            size_t coordinateSz;
            vector<double> pointVec;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ',');
            token = token.substr(1);
            //spec doesn't match with actual format so we make some workarounds
            line_stream >> token;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ')');
            token = token.substr(1);
            curveVec.push_back((*new Point(pointVec)));
        }
        if (curveLen != curveVec.size()) {
            cout << "expected curve length doesn't match with actual curve length." << endl;
            exit(-1);
        }
        auto curve = new Curve(curveVec); 
        curve->setId(item_id);
        data->add(curve);
        size++;
    }
    data->setSize(size);
    data->setDimension(2);
    data->setMax(maxCurveLen);
    data->setMin(minCurveLen);
    return data;
}

Dataset* parseInputFileCurvesMaxLength(string filename, int maxLength){
    if(!file_exists(filename.c_str())){
        cout << "input file does not exist" << endl;
        exit(-1);
    };
    auto data = new Dataset();
    cout << "Parsing input file: " << filename << ", please wait..." << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int minCurveLen = INT32_MAX;
    int maxCurveLen = INT32_MIN;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find('\t'));
        vector<Point> curveVec;
        line = line.substr(line.find_first_of("\t ") + 1);
        string token;
        stringstream line_stream(line);
        int curveLen;
        line_stream >> curveLen;
        if(curveLen > maxLength)
            continue;
        maxCurveLen = max(maxCurveLen,curveLen);
        minCurveLen = min(minCurveLen,curveLen);
        line = line.substr(line.find_first_of("\t ") + 1);
        while(line_stream >> token){
            //ensure the right format is given : (coordinate,coordinate)
            assert(token[0] == '(');
            token = token.substr(1);
            size_t coordinateSz;
            vector<double> pointVec;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ',');
            token = token.substr(1);
            //spec doesn't match with actual format so we make some workarounds
            line_stream >> token;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ')');
            token = token.substr(1);
            curveVec.push_back((*new Point(pointVec)));
        }
        if (curveLen != curveVec.size()) {
            cout << "expected curve length doesn't match with actual curve length." << endl;
            exit(-1);
        }
        auto curve = new Curve(curveVec);
        curve->setId(item_id);
        data->add(curve);
        size++;
    }
    data->setSize(size);
    data->setDimension(2);
    data->setMax(maxCurveLen);
    data->setMin(minCurveLen);
    return data;

}

QueryDataset* parseQueryFileCurvesMaxLength(string filename, int maxLength){
    if(!file_exists(filename.c_str())){
        cout << "query file does not exist" << endl;
        exit(-1);
    };
    auto data = new QueryDataset();
    cout << "Parsing query file: " << filename << ", please wait..." << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int minCurveLen = INT32_MAX;
    int maxCurveLen = INT32_MIN;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find('\t'));
        vector<Point> curveVec;
        line = line.substr(line.find_first_of("\t ") + 1);
        string token;
        stringstream line_stream(line);
        int curveLen;
        line_stream >> curveLen;
        if(curveLen > maxLength)
            continue;
        maxCurveLen = max(maxCurveLen,curveLen);
        minCurveLen = min(minCurveLen,curveLen);
        line = line.substr(line.find_first_of("\t ") + 1);
        while(line_stream >> token){
            //ensure the right format is given : (coordinate,coordinate)
            assert(token[0] == '(');
            token = token.substr(1);
            size_t coordinateSz;
            vector<double> pointVec;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ',');
            token = token.substr(1);
            //spec doesn't match with actual format so we make some workarounds
            line_stream >> token;
            pointVec.push_back(stod(token,&coordinateSz));
            token = token.substr(coordinateSz);
            assert(token[0] == ')');
            token = token.substr(1);
            curveVec.push_back((*new Point(pointVec)));
        }
        if (curveLen != curveVec.size()) {
            cout << "expected curve length doesn't match with actual curve length." << endl;
            exit(-1);
        }
        auto curve = new Curve(curveVec);
        curve->setId(item_id);
        data->add(curve);
        size++;
    }
    data->setSize(size);
    data->setDimension(2);
    data->setMax(maxCurveLen);
    data->setMin(minCurveLen);
    return data;
}