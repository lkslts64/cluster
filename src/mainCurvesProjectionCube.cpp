#include <iostream>
#include "Projection.h"
#include "ui.h"
#include "parse_files.h"
#include "search.h"

//WARNING! bigger size may crash your pc
#define MAX_LENGTH 5

using namespace std;

int main(int argc, char* argv[]){

    auto projection = new Projection(new Cube(new DTW), "cube");

    readArgumentsCubeProjectionCurves(projection, argc, argv);
    if(!projection->isInputFileGiven())
        projection->setInputFilename(askInputFile());
    if(!projection->isQueryFileGiven())
        projection->setQueryFilename(askQueryFile());
    if(!projection->isOutputFileGiven())
        projection->setOutputFilename(askOutputFile());

    projection->setData(parseInputFileCurvesMaxLength(projection->getInputFilename(), MAX_LENGTH));
    projection->setQueryData(parseQueryFileCurvesMaxLength(projection->getQueryFilename(), MAX_LENGTH));

    if(!projection->getAnn()->isDimensionGiven())
        projection->getAnn()->setDimension(log(projection->getDataset()->getSize())/log(2));

    cout << "Building traversals matrix..." << endl;
    projection->buildTraversalsMatrix(MAX_LENGTH);

    cout << "Putting data to cubes..." << endl;
    projection->putDataToCubes();

    cout << "Starting queries..." << endl;
    search_Cube_vs_BruteForce_Projection(projection);
    DoQueriesProjCube(projection);

    return 0;
}