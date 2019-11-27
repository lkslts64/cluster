#include <vector>
#include <limits>
#include "strategy.h"
#include "utils.h"
#include "Dataset.h"

void SpreadOutInit::execute() {
    auto objs = cluster->getDataset()->getData();
    auto numClusters = cluster->getGeneralParameters()->getNumOfClusters();
    _execute(objs,numClusters);
    cluster->setCenters(this->centers);
}


void SpreadOutInit::_execute(vector<Object *> objs,int numClusters) {
    init(objs);
    random_device dev;
    mt19937 rng(dev());
    auto objsSize = objs.size();
    //index of distArr is a centroid candidate
    vector<double> distArr;
    //index i of indexArr stores index of distArr[i] at objs vector
    vector<int> indexArr;
    while (centers.size() < numClusters) {
        double max = numeric_limits<double>::min();
        for (int i = 0; i < objsSize; i++) {
            //skip centroids
            if (centers.find(objs.at(i)) != centers.end())
                continue;
            auto dist = minDist(metric,objs.at(i),centers);
            if (dist > max)
                max = dist;
            distArr.push_back(dist);
            indexArr.push_back(i);
        }
        //normalize with maximum of array 
        for (int i =0; i< distArr.size(); i++) 
            distArr.at(i) /= max;
        for (int i =1; i< distArr.size(); i++) 
            distArr.at(i) += distArr.at(i-1);
        uniform_int_distribution<int> uni(0,distArr.at(distArr.size()-1));
        auto ind = this->search(distArr,uni(rng));            
        centers.insert(objs.at(indexArr.at(ind)));
        distArr.clear();
        indexArr.clear();
        //
    } 
}

//distArr is sorted
//
//search is a binary search variation
int SpreadOutInit::search(vector<double> distArr,double x) {
    int start = 0;
    int end = distArr.size() -1;
    int half;
    while(end >= start) {
        half= start + (end-start)/2;
        if (x == distArr.at(half)) //very rare
            return half;
        else if (x > distArr.at(half)) 
            start = half+1;
        else 
            end = half-1;
    }
    //at the end we can have two cases:
    //1) half == end == start-1 , so start is the index we want
    //2) half == start == end+1, so start is the index we want
    //3) half == start == end+1 == 0 so start+1 is the index we want
    if (!start)
        return start+1;
    return start;
}

//set first centroid 
void SpreadOutInit::init(vector<Object *> objs) {
    auto objsSize = objs.size();
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<int> uni(0,objs.size()-1);
    auto index = uni(rng);
    auto firstCentroid = objs.at(index);
    centers.insert(firstCentroid);
}
