#include <iostream>
#include "Projection.h"
#include "ui.h"
#include "parse_files.h"
#include "search.h"

//WARNING! bigger size may crash your pc
#define MAX_LENGTH 6

using namespace std;

int main(int argc, char* argv[]){

    auto projection = new Projection(new LSH(new DTW), "lsh");

    readArgumentsLSHProjectionCurves(projection, argc, argv);
    if(!projection->isInputFileGiven())
        projection->setInputFilename(askInputFile());
    if(!projection->isQueryFileGiven())
        projection->setQueryFilename(askQueryFile());
    if(!projection->isOutputFileGiven())
        projection->setOutputFilename(askOutputFile());

    projection->setData(parseInputFileCurvesMaxLength(projection->getInputFilename(), MAX_LENGTH));
    projection->setQueryData(parseQueryFileCurvesMaxLength(projection->getQueryFilename(), MAX_LENGTH));

    cout << "Building traversals matrix..." << endl;
    projection->buildTraversalsMatrix(MAX_LENGTH);

    cout << "Putting data to hash tables..." << endl;
    projection->putDataToHashTables();

    cout << "Starting queries..." << endl;
    search_LSH_vs_BruteForce_Projection(projection);
    DoQueries(projection);

    return 0;
}