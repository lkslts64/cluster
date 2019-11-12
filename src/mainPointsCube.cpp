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

    auto cube = new Cube(new Manhattan());
    auto lsh = cube->getLsh();
    /**
     * read arguments
     */
    readArgumentsCubePoints(cube, argc, argv);
    /**
     * ask files (if not given as arguments)
     */
    if(!lsh->isInputFileGiven())
        lsh->setInputFilename(askInputFile());
    if(!lsh->isQueryFileGiven())
        lsh->setQueryFilename(askQueryFile());
    if(!lsh->isOutputFileGiven())
        lsh->setOutputFilename(askOutputFile());

    /**
     * parse input file into memory, set dimension if not given
     */
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    //test_print_data(lsh->getDataset());
    if(!cube->isDimensionGiven())
        cube->setDimension(log(lsh->getDataset()->getSize())/log(2));

    /**
    * construct hash table struct
    */
    lsh->setHashTableStruct(new PointHashTableStruct(cube->getDimension(), lsh->getNumOfFunctions(),lsh->getDataset()->getDimension(), 4000));

    /**
    * parse query file into memory
    */
    lsh->setQueryData(parseQueryFilePoints(lsh->getQueryFilename()));
    //test_print_query_data(lsh->getQueryData());

    /**
     * Init Cube, based on LSH
     */
    cube->createBinaryMaps();
    //cube->test_print_binaryMaps();
    cube->createVertices();
    //cube->test_print_vertices();

    /**
     * Search Cube
     */
    search_Cube_vs_BruteForce(cube);
    DoQueries(cube);

    //ask user if he wants another one

    // +check memory leaks

    return 0;
}
