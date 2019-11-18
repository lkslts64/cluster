#include "Dataset.h"

Dataset::Dataset(vector<Object *> data) {
    this->data = data;
}

void Dataset::setSize(size_t sz) {
    this->size = sz;
}

void Dataset::setDimension(int d) {
    this->dimension = d;
}

void Dataset::add(Object *obj) {
    this->data.push_back(obj);
}

vector<Object *> Dataset::getData() {
    return this->data;
}

int Dataset::getDimension() {
    return dimension;
}

size_t Dataset::getSize() {
    return size;
}

double Dataset::getMax() {
    return max;
}

double Dataset::getMin() {
    return min;
}

void Dataset::setMax(double max) {
    this->max = max;
}

void Dataset::setMin(double min) {
    this->min = min;
}

void Dataset::setMean(int mean) {
    this->mean = mean;
}

int Dataset::getMean() {
    return mean;
}

void Dataset::setHasVectors(bool hasVectors) {
    this->hasVectors = hasVectors;
}

bool Dataset::getHasVectors() {
    return hasVectors;
}