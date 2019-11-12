#include <iostream>
#include <iomanip>
#include <limits>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "parse_files.h"
#include "utils.h"
#include "LSH.h"
#include "hasher.h"
#include "distance.h"
#include "search.h"


int main(int argc, char* argv[]){

    auto lsh = new LSH(new Manhattan());

    /**
     * read arguments
     */
    readArgumentsLSHPoints(lsh, argc, argv);
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
     * parse input file into memory
     */
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    cout << lsh->getDataset()->getMean() << endl;
    //test_print_data(lsh->getData());

    /**
     * insert data into hash tables
     */
    cout << "Constructing hash table..." << endl;
    lsh->setHashTableStruct(new PointHashTableStruct(lsh->getNumOfHashTables(),lsh->getNumOfFunctions(),lsh->getDataset()->getDimension(),4000));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
    lsh->getHashTableStruct()->test_print_hashtable();

    /**
     * parse query file into memory
     */
    lsh->setQueryData(parseQueryFilePoints(lsh->getQueryFilename()));
    //test_print_query_data(lsh->getQueryData());

    /**
     * search
     */
    search_LSH_vs_BruteForce(lsh);
    DoQueries(lsh);
    //ask user if he wants another one

    // +check memory leaks

    return 0;
}


