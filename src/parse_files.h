#ifndef ALGORITHMS_PROJECT_PARSE_FILES_H
#define ALGORITHMS_PROJECT_PARSE_FILES_H
#include "Dataset.h"
#include "distance.h"

Dataset* parseInputFilePoints(string filename);
QueryDataset* parseQueryFilePoints(string filename);
Dataset* parseInputFileCurves(string filename);
QueryDataset* parseQueryFileCurves(string filename);
int meanOfMins(Dataset *dataset,int limit,  DistanceMetric* distanceMetric);
Dataset* parseInputFileCurvesMaxLength(string filename, int max);
QueryDataset* parseQueryFileCurvesMaxLength(string filename, int max);

#endif //ALGORITHMS_PROJECT_PARSE_FILES_H
