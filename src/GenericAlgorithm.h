#ifndef ALGORITHMS_PROJECT_GENERICALGORITHM_H
#define ALGORITHMS_PROJECT_GENERICALGORITHM_H
#include "Dataset.h"
#include "HashTableStruct.h"
using namespace std;

class ANN_Structure {
public:

    virtual int getNumOfFunctions() const {}
    virtual int getNumOfHashTables() const {}
    virtual void setNumOfFunctions(int numOfFunctions){}
    virtual void setNumOfHashTables(int numOfHashTables){}
    virtual HashTableStruct * getHashTableStruct(){}
    virtual void setHashTableStruct(HashTableStruct *ht) {}

    virtual bool isDimensionGiven() const {}
    virtual int getDimension() const {}
    virtual int getMaxChecked() const {}
    virtual int getMaxProbes() const {}
    virtual void setDimension(int dimension) {}
    virtual void setMaxChecked(int maxChecked) {}
    virtual void setMaxProbes(int maxProbes) {}
    virtual void addToBinaryMap(Object* obj){}
    virtual void addToVertices(Object* obj){}
};

class GenericAlgorithm {
private:
    string inputFilename; bool inputFileGiven = false;
    string queryFilename; bool queryFileGiven = false;
    string outputFilename; bool outputFileGiven = false;

    Dataset* data;
    QueryDataset* queryData;

public:
    const string &getInputFilename() const {return inputFilename;}
    const string &getQueryFilename() const {return queryFilename;}
    const string &getOutputFilename() const {return outputFilename;}
    bool isInputFileGiven() const {return inputFileGiven;}
    bool isQueryFileGiven() const {return queryFileGiven;}
    bool isOutputFileGiven() const {return outputFileGiven;}
    Dataset *getDataset() const {return data;}
    QueryDataset *getQueryData() const {return queryData;}
    void setInputFilename(const string &inputFilename){
        inputFileGiven = true;
        this->inputFilename = inputFilename;
    }

    void setQueryFilename(const string &queryFilename){
        queryFileGiven = true;
        this->queryFilename = queryFilename;
    }

    void setOutputFilename(const string &outputFilename){
        outputFileGiven = true;
        this->outputFilename = outputFilename;
    }

    void setData(Dataset *data) {
        this->data = data;
    }

    void setQueryData(QueryDataset *queryData) {
        this->queryData = queryData;
    }

};


#endif //ALGORITHMS_PROJECT_GENERICALGORITHM_H
