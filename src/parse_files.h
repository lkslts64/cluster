#ifndef ALGORITHMS_PROJECT_PARSE_FILES_H
#define ALGORITHMS_PROJECT_PARSE_FILES_H
#include "Dataset.h"
#include "distance.h"

Dataset* parseFilePoints(string filename);
Dataset* parseFileCurves(string filename);
int meanOfMins(Dataset *dataset,int limit,  DistanceMetric* distanceMetric);
Dataset* parseInputFileCurvesMaxLength(string filename, int max);

#endif //ALGORITHMS_PROJECT_PARSE_FILES_H
