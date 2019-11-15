#include <ctime>
#include <limits>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "LSH.h"
#include "parse_files.h"
#include "search.h"

static FILE* temp_file = NULL;
using namespace std;

void setQueryData(LSH *lsh,string queryFilename) {
    lsh->setQueryFilename(queryFilename);
    lsh->setQueryData(parseQueryFilePoints(lsh->getQueryFilename()));
}

LSH *setInputData(string inputFilename) {
    auto lsh = new LSH(new Manhattan());
    lsh->setInputFilename(inputFilename);
    lsh->setData(parseFilePoints(lsh->getInputFilename()));
    lsh->setNumOfFunctions(4);
    lsh->setNumOfHashTables(5);
    //TODO: change this when we have a good formula for window.
    //change this value to experiment with performance of LSH.
    lsh->getDataset()->setMean(4000);
    lsh->setHashTableStruct(new PointHashTableStruct(lsh->getNumOfHashTables(),lsh->getNumOfFunctions(),lsh->getDataset()->getDimension(),lsh->getDataset()->getMean()));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
   return lsh;
}

void test_NumBuckets() {
   auto lsh = setInputData("../src/testdata/input_small_id");
   auto tables = lsh->getHashTableStruct()->getAllHashTables();
   auto numTables = lsh->getNumOfHashTables();
   int sum = 0;
   for (int i = 0; i < numTables; i++)
      sum += tables[i].bucket_count();
   cout << " bucket count in all tables: " << sum << endl;
}

LSH *LoadInput(string inputFilename,string queryFilename) {
   auto lsh = setInputData(inputFilename);
   setQueryData(lsh,queryFilename);
   return lsh;
}


void test_File(string inputFilename,string queryFilename) {
    auto lsh = LoadInput(inputFilename,queryFilename);
    DoQueries(lsh);
}

void test_LSHPoints() {
    test_File("../src/testdata/input_small_id","../src/testdata/query_small_id");
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
   if ((NULL == CU_add_test(pSuite, "test of PointHasher constructor",test_LSHPoints ))||
      (NULL == CU_add_test(pSuite, "test of PointHasher constructor", test_NumBuckets)))
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
