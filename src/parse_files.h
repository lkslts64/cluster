#ifndef ALGORITHMS_PROJECT_PARSE_FILES_H
#define ALGORITHMS_PROJECT_PARSE_FILES_H
#include "Dataset.h"
#include "distance.h"

Dataset* parseFile(string filename);
Dataset* parseFilePoints(string filename);
Dataset* parseFileCurves(string filename);
int meanOfMins(Dataset *dataset,int limit,  DistanceMetric* distanceMetric);

#endif //ALGORITHMS_PROJECT_PARSE_FILES_H
