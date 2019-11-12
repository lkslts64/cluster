#include "Cube.h"

//creates random 0/1 mapping for every entry of hash tables
void Cube::createBinaryMaps() {
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_int_distribution<int> dist(0,1);

    binaryMaps = new unordered_map<size_t, bool>[dimension];
    auto hashers = lsh->getHashTableStruct()->getHashers();
    auto data = lsh->getDataset()->getData();
    //for every item
    for(auto obj : data){
        //insert it in every map
        for (int i = 0; i < dimension; ++i) {
            binaryMaps[i].insert(make_pair((*hashers.at(i))(obj), dist(mt)));
        }
    }
}

void Cube::createVertices() {
    numberOfVertices = pow(2,dimension);
    vertices = new vector<Object *>[numberOfVertices];
    auto data = lsh->getDataset()->getData();
    auto hashers = lsh->getHashTableStruct()->getHashers();
    //for every item, insert it in the right vertex
    for(auto obj : data){
        size_t index = 0;
        //construct index
        for (int i = 0; i < dimension; ++i) {
            index <<= 1u;
            index |= binaryMaps[i].at((*hashers.at(i))(obj));
        }
        vertices[index].push_back(obj);
    }
}

void Cube::test_print_binaryMaps(){
    for (int i = 0; i < dimension; i++) {
        cout << "\nBINARY TABLE " << i + 1 << endl;
        for(auto x : binaryMaps[i]){
            cout<<"bucket #"<< x.first << ", value: " << x.second << endl;
        }
    }
}

void Cube::test_print_vertices(){
    for (size_t i = 0; i < numberOfVertices; ++i) {
        cout << "VERTEX " << i << endl;
        for(auto obj : vertices[i]){
            cout << obj->getId() << endl;
        }
        cout << endl;
    }
}


void Cube::allocateBinaryMaps(){
    binaryMaps = new unordered_map<size_t, bool>[dimension];
}
void Cube::addToBinaryMap(Object* obj){
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_int_distribution<int> dist(0,1);
    auto hashers = lsh->getHashTableStruct()->getHashers();
    //insert it in every map
    for (int i = 0; i < dimension; ++i) {
        binaryMaps[i].insert(make_pair((*hashers.at(i))(obj, true), dist(mt)));
    }
}
void Cube::allocateVertices(){
    numberOfVertices = pow(2,dimension);
    vertices = new vector<Object *>[numberOfVertices];
}
void Cube::addToVertices(Object* obj){
    auto hashers = lsh->getHashTableStruct()->getHashers();
    size_t index = 0;
    //construct index
    for (int i = 0; i < dimension; ++i) {
        index <<= 1u;
        index |= binaryMaps[i].at((*hashers.at(i))(obj, true));
    }
    vertices[index].push_back(obj);
}

