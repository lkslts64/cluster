#ifndef ALGORITHMS_PROJECT_GENERALPARAMETERS_H
#define ALGORITHMS_PROJECT_GENERALPARAMETERS_H
#include "Dataset.h"
#include "HashTableStruct.h"
using namespace std;

class GeneralParameters {
private:
    string input_filename;
    string output_filename;
    bool is_complete = false;

    int num_of_clusters;
    int num_of_grids = 2;
    int num_of_vector_hash_tables = 3;
    int num_of_vector_hash_functions;

public:
    const string &getInputFilename() const {return input_filename;}
    const string &getOutputFilename() const {return output_filename;}

    void setInputFilename(const string &inputFilename){
        this->input_filename = inputFilename;
    }

    void setOutputFilename(const string &outputFilename){
        this->output_filename = outputFilename;
    }

    bool isComplete() const {
        return is_complete;
    }

    void setIsComplete(bool is_complete) {
        GeneralParameters::is_complete = is_complete;
    }

    int getNumOfClusters() const {
        return num_of_clusters;
    }

    void setNumOfClusters(int numOfClusters) {
        num_of_clusters = numOfClusters;
    }

    int getNumOfGrids() const {
        return num_of_grids;
    }

    void setNumOfGrids(int numOfGrids) {
        num_of_grids = numOfGrids;
    }

    int getNumOfVectorHashTables() const {
        return num_of_vector_hash_tables;
    }

    void setNumOfVectorHashTables(int numOfVectorHashTables) {
        num_of_vector_hash_tables = numOfVectorHashTables;
    }

    int getNumOfVectorHashFunctions() const {
        return num_of_vector_hash_functions;
    }

    void setNumOfVectorHashFunctions(int numOfVectorHashFunctions) {
        num_of_vector_hash_functions = numOfVectorHashFunctions;
    }
};


#endif //ALGORITHMS_PROJECT_GENERALPARAMETERS_H
