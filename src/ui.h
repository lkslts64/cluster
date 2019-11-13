#ifndef ALGORITHMS_PROJECT_UI_H
#define ALGORITHMS_PROJECT_UI_H

void readArgumentsLSHPoints(LSH* lsh, int argc, char **argv);
void readArgumentsLSHCurves(LSH* lsh, int argc, char **argv);
string askInputFile();
string askQueryFile();
string askOutputFile();

#endif //ALGORITHMS_PROJECT_UI_H
