#include "RelevantTraversals.h"
#include "LSH.h"
#include "Cube.h"
#include <string.h>

using namespace std;

RelevantTraversals::RelevantTraversals(int length1, int length2, Projection* proj){
    this->length1 = length1;
    this->length2 = length2;
    this->projection = proj;
    createTraversalsMatrix();
    //printTraversalsMatrix();
    createRelevantTraversals();
    //printRelevantTraversals();
    deleteTraversalsMatrix();
}

// Traverse the diagonal and mark useful cells to true
void RelevantTraversals::createTraversalsMatrix(){
    traversalsMatrix = new bool*[length1];
    for (int i = 0; i < length1; ++i){
        traversalsMatrix[i] = new bool[length2];
        memset(traversalsMatrix[i], false, length2);
    }

    /**
     * Square Matrix
     */
    if (length1 == length2){
        traversalsMatrix[0][0] = true;
        if(length1 > 1){
            traversalsMatrix[0][1] = true;
            traversalsMatrix[1][0] = true;
        }
        for (int i = 1; i < length1 - 1; ++i) {
            // Diagonal squares
            traversalsMatrix[i][i] = true;
            // Relevant squares
            //traversalsMatrix[i-1][i+1] = true;
            //traversalsMatrix[i+1][i-1] = true;
            traversalsMatrix[i][i+1]   = true;
            traversalsMatrix[i+1][i]   = true;
        }
        traversalsMatrix[length1 - 1][length1 - 1] = true;
    }
    /**
     * Non-Square Matrix
     */
    else {
        traversalsMatrix[0][0] = true;
        if(length1 > 1) traversalsMatrix[1][0] = true;
        if(length2 > 1) traversalsMatrix[0][1] = true;
        int i = 0, j = 0;
        double diagonalFactor = double(length2) / double(length1);
        // Draw the diagonal, based on diagonalFactor
        while (i < length1 && j < length2){
            // Diagonal squares
            traversalsMatrix[i][j] = true;
            // Relevant squares
            //if((i-1 >= 0) && (j+1 < length2)) traversalsMatrix[i-1][j+1] = true;
            //if((i+1 < length1) && (j-1 >= 0)) traversalsMatrix[i+1][j-1] = true;
            if(j+1 < length2) traversalsMatrix[i][j+1] = true;
            if(i+1 < length1) traversalsMatrix[i+1][j] = true;
            double changeRowFactor = double(j + 1) / double(i + 1 + 1);
            double changeColFactor = double(j + 1 + 1) / double(i + 1);
            if(abs(changeRowFactor - diagonalFactor) < abs(changeColFactor - diagonalFactor)) // Change row
                i++;
            else // Change column
                j++;
        }
    }
}

void RelevantTraversals::deleteTraversalsMatrix() {
    for (int i = 0; i < length1; ++i)
        delete[] traversalsMatrix[i];
    delete[] traversalsMatrix;
}

void RelevantTraversals::constructTraversalsRecursively(vector<tuple<int, int>> traversal, int i, int j){
    // Reached the bottom of the matrix so we are left with
    // only option to move right
    if (i == length1 - 1){
        for (int k = j; k < length2; k++)
            traversal.push_back(make_tuple(i,k));
        // New traversal & ANN
        traversals.push_back(traversal);
        if(!projection->getAlgorithm().compare("lsh")){
            auto lsh = new LSH(new DTW);
            lsh->setNumOfHashTables(projection->getAnn()->getNumOfHashTables());
            lsh->setNumOfFunctions(projection->getAnn()->getNumOfFunctions());
            lsh->setHashTableStruct(new CurveProjectionHashTableStruct(lsh->getNumOfHashTables(), lsh->getNumOfFunctions(),
                    projection->getNormalMatrix().size()*traversal.size(), 1, projection->getNormalMatrix(), traversal));
            ann_structs.push_back(lsh);
        } else if (!projection->getAlgorithm().compare("cube")){
            auto cube = new Cube(new DTW);
            auto lsh = cube->getLsh();
            cube->setDimension(projection->getAnn()->getDimension());
            cube->setMaxProbes(projection->getAnn()->getMaxProbes());
            cube->setMaxChecked(projection->getAnn()->getMaxChecked());
            lsh->setData(projection->getDataset());
            lsh->setHashTableStruct(new CurveProjectionHashTableStruct(cube->getDimension(), lsh->getNumOfFunctions(),
                    projection->getNormalMatrix().size()*traversal.size(), 1, projection->getNormalMatrix(), traversal));
            cube->allocateBinaryMaps();
            cube->allocateVertices();
            ann_structs.push_back(cube);
        }

        return;
    }

    // Reached the right corner of the matrix we are left with
    // only the downward movement.
    if (j == length2 - 1){
        for (int k = i; k < length1; k++)
            traversal.push_back(make_tuple(k,j));
        // New traversal & ANN
        traversals.push_back(traversal);
        if(!projection->getAlgorithm().compare("lsh")){
            auto lsh = new LSH(new DTW);
            lsh->setNumOfHashTables(projection->getAnn()->getNumOfHashTables());
            lsh->setNumOfFunctions(projection->getAnn()->getNumOfFunctions());
            lsh->setHashTableStruct(new CurveProjectionHashTableStruct(lsh->getNumOfHashTables(), lsh->getNumOfFunctions(),
                    projection->getNormalMatrix().size()*traversal.size(), 1, projection->getNormalMatrix(), traversal));
            ann_structs.push_back(lsh);
        } else if (!projection->getAlgorithm().compare("cube")){
            auto cube = new Cube(new DTW);
            auto lsh = cube->getLsh();
            cube->setDimension(projection->getAnn()->getDimension());
            cube->setMaxProbes(projection->getAnn()->getMaxProbes());
            cube->setMaxChecked(projection->getAnn()->getMaxChecked());
            lsh->setData(projection->getDataset());
            lsh->setHashTableStruct(new CurveProjectionHashTableStruct(cube->getDimension(), lsh->getNumOfFunctions(),
                    projection->getNormalMatrix().size()*traversal.size(), 1, projection->getNormalMatrix(), traversal));
            cube->allocateBinaryMaps();
            cube->allocateVertices();
            ann_structs.push_back(cube);
        }

        return;
    }

    // Add the current cell to the path being generated
    traversal.push_back(make_tuple(i,j));

    // Move down if it is a useful cell
    if(traversalsMatrix[i+1][j]) constructTraversalsRecursively(traversal, i + 1, j);

    // Move right if it is a useful cell
    if(traversalsMatrix[i][j+1]) constructTraversalsRecursively(traversal, i, j + 1);

    // Move diagonal if it is a useful cell
    if(traversalsMatrix[i+1][j+1]) constructTraversalsRecursively(traversal, i + 1, j + 1);
}

void RelevantTraversals::createRelevantTraversals(){
    vector<tuple<int, int>> traversal;
    constructTraversalsRecursively(traversal, 0, 0);
}

void RelevantTraversals::printTraversalsMatrix() {
    for (int i = 0; i < length1; ++i) {
        for (int j = 0; j < length2; ++j)
            if(traversalsMatrix[i][j])
                cout << "1";
            else
                cout << "0";
        cout << endl;
    }
    cout << endl << endl;
}

void RelevantTraversals::printRelevantTraversals() {
    for(auto traversal : traversals){
        for (auto & t : traversal)
            cout << "("<< get<0>(t) << ", " << get<1>(t)  << ") ";
        cout << endl;
    }
    cout << "There were " << traversals.size() << " different relevant traversals" << endl << endl;

    for(auto a : ann_structs){
        cout << a->getNumOfHashTables() << endl;
    }
}

void RelevantTraversals::addToHashTables(Curve *curve) {
    for(auto ann : ann_structs){
        ann->getHashTableStruct()->addToAllHashTables(curve);
    }
}

void RelevantTraversals::addToCubes(Curve *curve) {
    for(auto ann : ann_structs){
        ann->addToBinaryMap(curve);
        ann->addToVertices(curve);
    }
}
