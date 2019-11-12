#include <iostream>
#include <getopt.h>
#include <algorithm>
#include "utils.h"
#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"
#include "ui.h"
#include "Projection.h"

using namespace std;

class InputParser{
    private:
        vector <string> tokens;
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(string(argv[i]));
        }
        const string& getCmdOption(const string &option) const{
            vector<string>::const_iterator itr;
            itr =  find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const string empty_string("");
            return empty_string;
        }
        bool cmdOptionExists(const string &option) const{
            return find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
};

void readArgumentsLSHPoints(LSH* lsh, int argc, char **argv) {
    auto parser = new InputParser(argc,argv);
    if (parser->cmdOptionExists("-d"))
        lsh->setInputFilename(parser->getCmdOption("-d"));
    if (parser->cmdOptionExists("-q"))
        lsh->setQueryFilename(parser->getCmdOption("-q"));
    if (parser->cmdOptionExists("-o"))
        lsh->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-k"))
        lsh->setNumOfFunctions(stoi(parser->getCmdOption("-k")));
    else
        lsh->setNumOfFunctions(4);
    if (parser->cmdOptionExists("-L"))
        lsh->setNumOfHashTables(stoi(parser->getCmdOption("-L")));
    else
        lsh->setNumOfHashTables(5);
}

void readArgumentsCubePoints(Cube* cube, int argc, char **argv) {
    auto parser = new InputParser(argc,argv);
    if (parser->cmdOptionExists("-d"))
        cube->getLsh()->setInputFilename(parser->getCmdOption("-d"));
    if (parser->cmdOptionExists("-q"))
        cube->getLsh()->setQueryFilename(parser->getCmdOption("-q"));
    if (parser->cmdOptionExists("-o"))
        cube->getLsh()->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-k"))
        cube->setDimension(stoi(parser->getCmdOption("-k")));
    if (parser->cmdOptionExists("-M"))
        cube->setMaxChecked(stoi(parser->getCmdOption("-M")));
    if (parser->cmdOptionExists("-probes"))
        cube->setMaxProbes(stoi(parser->getCmdOption("-probes")));
}   

void readArgumentsCubeCurves(Cube* cube, int argc, char **argv) {
    auto parser = new InputParser(argc,argv);
    if (parser->cmdOptionExists("-d"))
        cube->getLsh()->setInputFilename(parser->getCmdOption("-d"));
    if (parser->cmdOptionExists("-q"))
        cube->getLsh()->setQueryFilename(parser->getCmdOption("-q"));
    if (parser->cmdOptionExists("-o"))
        cube->getLsh()->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-k_hypercube"))
        cube->setDimension(stoi(parser->getCmdOption("-k")));
    if (parser->cmdOptionExists("-M"))
        cube->setMaxChecked(stoi(parser->getCmdOption("-M")));
    if (parser->cmdOptionExists("-probes"))
        cube->setMaxProbes(stoi(parser->getCmdOption("-probes")));
}   

void readArgumentsLSHCurves(LSH* lsh, int argc, char **argv) {
    auto parser = new InputParser(argc,argv);
    if (parser->cmdOptionExists("-d"))
        lsh->setInputFilename(parser->getCmdOption("-d"));
    if (parser->cmdOptionExists("-q"))
        lsh->setQueryFilename(parser->getCmdOption("-q"));
    if (parser->cmdOptionExists("-o"))
        lsh->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-k_vec"))
        lsh->setNumOfFunctions(stoi(parser->getCmdOption("-k_vec")));
    else 
        lsh->setNumOfFunctions(1);
    if (parser->cmdOptionExists("-L_grid"))
        lsh->setNumOfHashTables(stoi(parser->getCmdOption("-L_grid")));
    else 
        lsh->setNumOfHashTables(4);
}

void readArgumentsLSHProjectionCurves(Projection* projection, int argc, char **argv){
    auto parser = new InputParser(argc,argv);
    if (parser->cmdOptionExists("-d"))
        projection->setInputFilename(parser->getCmdOption("-d"));
    if (parser->cmdOptionExists("-q"))
        projection->setQueryFilename(parser->getCmdOption("-q"));
    if (parser->cmdOptionExists("-o"))
        projection->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-k_vec"))
        projection->getAnn()->setNumOfFunctions(stoi(parser->getCmdOption("-k_vec")));
    else
        projection->getAnn()->setNumOfFunctions(4);
    if (parser->cmdOptionExists("-L_vec"))
        projection->getAnn()->setNumOfHashTables(stoi(parser->getCmdOption("-L_vec")));
    else
        projection->getAnn()->setNumOfHashTables(5);
    if (parser->cmdOptionExists("-e"))
        projection->setNormalMatrix(stod(parser->getCmdOption("-e")));
    else
        projection->setNormalMatrix(0.5);
}

void readArgumentsCubeProjectionCurves(Projection* projection, int argc, char **argv) {
    auto parser = new InputParser(argc,argv);
    if (parser->cmdOptionExists("-d"))
        projection->setInputFilename(parser->getCmdOption("-d"));
    if (parser->cmdOptionExists("-q"))
        projection->setQueryFilename(parser->getCmdOption("-q"));
    if (parser->cmdOptionExists("-o"))
        projection->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-k_hypercube"))
        projection->getAnn()->setDimension(stoi(parser->getCmdOption("-k_hypercube")));
    if (parser->cmdOptionExists("-M"))
        projection->getAnn()->setMaxChecked(stoi(parser->getCmdOption("-M")));
    if (parser->cmdOptionExists("-probes"))
        projection->getAnn()->setMaxProbes(stoi(parser->getCmdOption("-probes")));
    if (parser->cmdOptionExists("-e"))
        projection->setNormalMatrix(stod(parser->getCmdOption("-e")));
    else
        projection->setNormalMatrix(0.5);
}

string askInputFile(){
    string filename;
    cout << "Please give input filename" << endl;
    cin >> filename;
    return filename;
}

string askQueryFile(){
    string filename;
    cout << "Please give query filename" << endl;
    cin >> filename;
    return filename;
}

string askOutputFile(){
    string filename;
    cout << "Please give output filename" << endl;
    cin >> filename;
    return filename;
}
