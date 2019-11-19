#define private public
#include <set>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "hasher.h"
#include "parse_files.h"
#include "LSH.h"
#include "Point.h"
#include "ui.h"
#include "Dataset.h"
#include "parse_files.h"

LSH *lsh;
static FILE* temp_file = NULL;
using namespace std;

void test_meanOfMins() {
   vector<Point*> points {new Point(vector<double> {2.0,2.0,2.0}),new Point(vector<double> {3.0,3.0,3.0}),new Point(vector<double> {4.0,4.0,4.0})};
   vector<Object *> objs (points.begin(),points.end());
   //mean dist = (3 + 3 + 3)/3 = 3
   CU_ASSERT(meanOfMins(new Dataset(objs),3,new Manhattan()) == 3);
}

void test_PointHasher(void) {
    //check signleton and selectedGrids array size.
    auto phasher = new PointHasher(4,6,100);
    //ensure selected has 4 elements
    CU_ASSERT(phasher->grids[3][5] < 100);
    auto phasher2 = new PointHasher(6,9,100);
    //ensure selected has 6 elements
    CU_ASSERT(phasher2->grids[5][8] < 100);
}

//check that near points lie on the same bucket.
//This depends on the window size (currently 100).
void test_HashNonAmplified(void) {
    auto phasher = new PointHasher(5,2,100);
    int M = pow(2,int(32/5));
    Point *point = new Point("1");
    //
    //
    point->addCoordinateLast(-2000.1);
    point->addCoordinateLast(9000.1);
    int bucket = phasher->hash(point,1);
    CU_ASSERT(bucket < M && bucket > 0);
    Point *point2 = new Point("2");
    point2->addCoordinateLast(-2001.1);
    point2->addCoordinateLast(9001.1);
    int bucket2 = phasher->hash(point2,1);
    CU_ASSERT(bucket2 < M && bucket2 > 0);
    //ensure they lie on the same bucket. This can fail with small
    //propability because we the whole process is random.
    CU_ASSERT(bucket2 == bucket);
}

void test_Determinism(void) {
   auto point = new Point(vector<double> {44.432,85.984,34.439,989.890});
    auto phasher = new PointHasher(5,4,10);
    size_t bucket;
    size_t prevBucket = 0;
    for (int i =0; i < 20; i++)
      if (prevBucket!=0 && (bucket = (*phasher)(point)) != prevBucket) 
         CU_FAIL("test determinism failed!");
}

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("testPoinHasher.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

int main(int argc,char *argv[]) {
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ((NULL == CU_add_test(pSuite, "test of PointHasher constructor", test_PointHasher))||
       (NULL == CU_add_test(pSuite, "test of hash(obj,hashIndex) ", test_HashNonAmplified)) || 
       (NULL == CU_add_test(pSuite,"test determinism",test_Determinism)) ||
       (NULL == CU_add_test(pSuite,"test mean of mins",test_meanOfMins)))
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
