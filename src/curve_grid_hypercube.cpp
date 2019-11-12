#include <iostream>
#include <cmath>
#include "hasher.h"
#include "search.h"
#include "utils.h"
#include "Cube.h"
#include "ui.h"
#include "parse_files.h"

using namespace std;

int main(int argc, char* argv[]){
    auto cube = new Cube(new DTW());
    auto lsh = cube->getLsh();
    readArgumentsCubeCurves(cube, argc, argv);
    if(!lsh->isInputFileGiven())
        lsh->setInputFilename(askInputFile());
    if(!lsh->isQueryFileGiven())
        lsh->setQueryFilename(askQueryFile());
    if(!lsh->isOutputFileGiven())
        lsh->setOutputFilename(askOutputFile());
    lsh->setData(parseInputFileCurves(lsh->getInputFilename()));
    if(!cube->isDimensionGiven())
        cube->setDimension(log(lsh->getDataset()->getSize())/log(2));
    auto dataset = lsh->getDataset();
    lsh->setHashTableStruct(new CurveHashTableStruct(
        lsh->getNumOfHashTables(),lsh->getNumOfFunctions(),dataset->getDimension(),
        0.000002,dataset->getMax(),2));
    lsh->setQueryData(parseQueryFileCurves(lsh->getQueryFilename()));
    cube->createBinaryMaps();
    cube->createVertices();
    DoQueries(cube);
    return 0;
}
