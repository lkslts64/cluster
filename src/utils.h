#include <string>
#include <set>
#include "Dataset.h"
#include "distance.h"

using namespace std;

int powModulo(int base,int exp,int div);
bool file_exists(const char* filename);
double max(double,double);
double min(double,double);
int modulo(int a, int b);
void test_print_data(Dataset *data);
double minDist(DistanceMetric *metric,Object *target, set<Object*> objs, Object *closest = nullptr);
double minVec(vector<double> vec);
double minDistanceInSet(set<Object *>, DistanceMetric*);
void printProgress (double percentage);
