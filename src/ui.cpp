#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include "utils.h"
#include "Dataset.h"
#include "Cluster.h"
#include "ui.h"

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

void parseConfigFile(GeneralParameters *gen_params, const string &config_filename) {
    if(!file_exists(config_filename.c_str())){
        cout << "configuration file does not exist" << endl;
        exit(-1);
    };
    ifstream infile(config_filename);
    string line;
    map<string, int> params_map;
    //construct params_map
    while(getline(infile, line)){
        string param_name = line.substr(0, line.find(':'));
        string param_value = line.substr(line.find(':') + 1);
        params_map[param_name] = stoi(param_value);
    }

    if(params_map.find("number_of_clusters") != params_map.end())
        gen_params->setNumOfClusters(params_map["number_of_clusters"]);
    else{
        cout << "configuration file error: number_of_clusters does not exist" << endl;
        exit(-1);
    }
    if(params_map.find("number_of_grids") != params_map.end())
        gen_params->setNumOfGrids(params_map["number_of_grids"]);
    else{
        cout << "configuration file error: number_of_grids does not exist" << endl;
        exit(-1);
    }
    if(params_map.find("number_of_vector_hash_tables") != params_map.end())
        gen_params->setNumOfVectorHashTables(params_map["number_of_vector_hash_tables"]);
    else{
        cout << "configuration file error: number_of_vector_hash_tables does not exist" << endl;
        exit(-1);
    }
    if(params_map.find("number_of_vector_hash_functions") != params_map.end())
        gen_params->setNumOfVectorHashFunctions(params_map["number_of_vector_hash_functions"]);
    else{
        cout << "configuration file error: number_of_vector_hash_functions does not exist" << endl;
        exit(-1);
    }
}

void readArguments(Cluster* cluster, int argc, char **argv){
    auto parser = new InputParser(argc,argv);
    auto gen_params = new GeneralParameters;
    if (parser->cmdOptionExists("-i"))
        gen_params->setInputFilename(parser->getCmdOption("-i"));
    if (parser->cmdOptionExists("-o"))
        gen_params->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-complete"))
        gen_params->setIsComplete(true);
    if (parser->cmdOptionExists("-c"))
        parseConfigFile(gen_params, parser->getCmdOption("-c"));
    cluster->setGeneralParameters(gen_params);
}


