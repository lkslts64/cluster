#define private public
#include <vector>
#include <random>
#include "strategy.h"
#include "Dataset.h"
#include "utils.h"
#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"


//points have 3 coordinates each
vector<Object *> generateDatasetPoints(int numPoints,double lower,double upper,int numCoords) {
   vector<Object*> points;
   random_device dev;
   mt19937 rng(dev());
   uniform_real_distribution<double> dist(lower,upper);
   vector<double> coords;
   for (int i =0; i < numPoints; i++) {
      for (int i =0; i < numCoords;i++) 
        coords.push_back(dist(dev));
      points.push_back((new Point(coords)));
      coords.clear();
   }
   return points;
}

void test_search() {
    auto spreadOut = new SpreadOutInit(true);
    vector<double> dists {1.43,3,55.23,99.98,100.100};
    double x  = 66.55;
    auto i = spreadOut->search(dists,x);
    CU_ASSERT(i == 3);
    x = 0.66;
    i = spreadOut->search(dists,x);
    CU_ASSERT(i == 1);
    x = 99.98;
    i = spreadOut->search(dists,x);
    CU_ASSERT(i == 3);
}

void test_execute() {
    auto spreadOut = new SpreadOutInit(true);
    auto points = generateDatasetPoints(1000,0,1000000,1);
    spreadOut->_execute(points,20);
    CU_ASSERT(spreadOut->getCenters().size() == 20);
    //dificult to test this (its non deterministic)
    //just see the output - we want values to have 
    //big distance between them (high variance).
    for (auto c :spreadOut->getCenters()) {
        auto p = dynamic_cast<Point*>(c);
        for (auto coord : p->getCoordinates())
            cout << coord << ",";
    }
}

int init_suite1(void) { return 0; }

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) { return 0; }

int main(int argc,char *argv[]) {
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ((NULL == CU_add_test(pSuite, "test of spread out search",test_search)) || 
    (NULL == CU_add_test(pSuite, "test of spread out search",test_execute)))
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}