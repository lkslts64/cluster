#include <vector>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "LSH.h"
#include "ui.h"
#include "parse_files.h"
#include "search.h"
#include "curve_grid_lsh.h"

static FILE* temp_file = NULL;
using namespace std;

void test_DTW() {
   vector<Point> pointVec {(*new Point(vector<double> {-1,-1})),
   (*new Point(vector<double> {2,2}))};
   vector<Point> pointVec2 {(*new Point(vector<double> {3,3})),
   (*new Point(vector<double> {4,4}))};
   auto curv1 = new Curve(pointVec);
   auto curv2 = new Curve(pointVec2);
   auto dmetric = new DTW();
   auto ipairs = new vector<struct IndexPairs>();
   dmetric->distWithIndexPairs(curv1,curv2,ipairs);
   CU_ASSERT(ipairs->size() == 2);
   CU_ASSERT(ipairs->at(0).p1 == 0 && ipairs->at(0).p2 == 0);
   CU_ASSERT(ipairs->at(1).p1 == 1 && ipairs->at(1).p2 == 1);
   auto d =dmetric->dist(curv2,curv1); 
   CU_ASSERT(d > 7 && d < 8);
   vector<Point> pointVec3 {(*new Point(vector<double> {-5.42398,63.432432})),(*new Point(vector<double> {-533.43242,63.64324})),(*new Point(vector<double> {-5.55577,63.5678}))};
   vector<Point> pointVec4 {(*new Point(vector<double> {-5.14324,63.23132})),(*new Point(vector<double> {-5.778832,63.69978}))};
   auto curv3 = new Curve(pointVec3);
   auto curv4 = new Curve(pointVec4);
   dmetric = new DTW();
   ipairs = new vector<struct IndexPairs>();
   dmetric->distWithIndexPairs(curv3,curv4,ipairs);
   CU_ASSERT(ipairs->size() == 3)
   for (auto p : *ipairs) {
      cout << p.p1 << endl;
      cout << p.p2 << endl;
   }
   //cout << " dist is " << dmetric->dist(curv3,curv4) << endl;
}

void test_ReadArgsCurves() {
    auto lsh = new LSH(new DTW());
    char *argv[]= {
        "progName",
        "-d", "input_lol",
        "-q", "query_lol",
        "-o", "output_lol",
        "-k_vec ", "1",
        "-L_grid", "888",
    };
    int argc = sizeof(argv)/sizeof(char*);
    readArgumentsLSHCurves(lsh,argc,argv);
    CU_ASSERT(lsh->getInputFilename() == "input_lol");
    CU_ASSERT(lsh->getQueryFilename() == "query_lol");
    CU_ASSERT(lsh->getOutputFilename() == "output_lol");
    CU_ASSERT(lsh->getNumOfFunctions() == 1);
    CU_ASSERT(lsh->getNumOfHashTables() == 888);
}

void test_ParseTestFile(LSH *lsh) {
    auto dataset = lsh->getDataset();
    CU_ASSERT(dataset->getMax() == 3);
    CU_ASSERT(dataset->getMin() == 2);
    CU_ASSERT(dataset->getDimension() == 2);
    CU_ASSERT(dataset->getSize() == 2);
    auto data = dataset->getData();
    auto curve1 = dynamic_cast<Curve *>(data.at(0));
    CU_ASSERT(curve1->getId() == "curve_id1");
    auto point11 = curve1->getPoint(0);
    auto expected = new Point(vector<double> {-43242.423,849.438});
    CU_ASSERT(*expected == point11);
    auto point12 = curve1->getPoint(1);
    expected = new Point(vector<double> {33,32.43});
    CU_ASSERT(*expected == point12);
    auto point13 = curve1->getPoint(2);
    expected = new Point(vector<double> {-787.432,-888});
    CU_ASSERT(*expected == point13);
    auto curve2 = dynamic_cast<Curve *>(data.at(1));
    CU_ASSERT(curve2->getId() == "2");
    auto point21 = curve2->getPoint(0);
    expected = new Point(vector<double> {4324,43242});
    CU_ASSERT(*expected == point21);
    auto point22 = curve2->getPoint(1);
    expected = new Point(vector<double> {988.4328,-48778});
    CU_ASSERT(*expected == point22);
}

void test_ParseCurves() {
    auto lsh = new LSH(new DTW());
    lsh->setInputFilename("../src/testdata/curves_loukas_small");
    lsh->setData(parseFileCurves(lsh->getInputFilename()));
    test_ParseTestFile(lsh);
    delete lsh;
    //----------------------
    lsh = new LSH(new DTW());
    lsh->setInputFilename("../src/testdata/trajectories_input");
    lsh->setData(parseFileCurves(lsh->getInputFilename()));
    CU_ASSERT(lsh->getDataset()->getSize() == 7401);
    delete lsh;
    //----------------------
    lsh = new LSH(new DTW());
    lsh->setQueryFilename("../src/testdata/trajectories_query");
    lsh->setData(parseQueryFileCurves(lsh->getQueryFilename()));
    CU_ASSERT(lsh->getDataset()->getSize() == 86);
    delete lsh;
    //----------------------
}

LSH *LoadInputLSHCurves(string inputFilename,string queryFilename) {
   auto lsh = new LSH(new DTW());
    lsh->setInputFilename(inputFilename);
    lsh->setData(parseFileCurves(lsh->getInputFilename()));
    lsh->setNumOfFunctions(4);
    lsh->setNumOfHashTables(5);
    auto dataset = lsh->getDataset();

    //TODO:set min appropirately - 
    lsh->setHashTableStruct(new CurveHashTableStruct(lsh->getNumOfHashTables(),lsh->getNumOfFunctions(),dataset->getDimension(),0.5,dataset->getMax(),4000));
    auto curves = dataset->getData();
    for (auto & curve : curves)
        lsh->getHashTableStruct()->addToAllHashTables(curve);
    lsh->setQueryFilename(queryFilename);
    lsh->setQueryData(parseQueryFileCurves(lsh->getQueryFilename()));
   return lsh;
}

void test_NumBuckets() {
   auto lsh = new LSH(new DTW());
    lsh->setInputFilename("../src/testdata/trajectories_input");
    lsh->setData(parseFileCurves(lsh->getInputFilename()));
    lsh->setNumOfFunctions(4);
    lsh->setNumOfHashTables(5);
    auto dataset = lsh->getDataset();
    //cout << dataset->getMax() << " " <<  dataset->getMin() << endl;
    lsh->setHashTableStruct(new CurveHashTableStruct(lsh->getNumOfHashTables(),lsh->getNumOfFunctions(),dataset->getDimension(),dataset->getMin(),dataset->getMax(),4000));
    auto curves = dataset->getData();
    for (auto & curve : curves)
        lsh->getHashTableStruct()->addToAllHashTables(curve);
   auto tables = lsh->getHashTableStruct()->getAllHashTables();
   auto numTables = lsh->getNumOfHashTables();
   int sum = 0;
   for (int i = 0; i < numTables; i++)
      sum += tables[i].bucket_count();
   cout << " bucket count in all tables: " << sum << endl;
}

void test_File(string inputFilename,string queryFilename) {
   auto lsh = LoadInputLSHCurves(inputFilename,queryFilename);
   DoQueries(lsh);
}

void test_Files() {
   test_File("../src/testdata/trajectories_input_small","../src/testdata/trajectories_query_small");
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
   if ((NULL == CU_add_test(pSuite, "test of read curve args",test_ReadArgsCurves)) ||
    (NULL == CU_add_test(pSuite, "test of DTW",test_DTW)) ||
    (NULL == CU_add_test(pSuite, "test of read curve args",test_ParseCurves)) ||
    (NULL == CU_add_test(pSuite, "test of read curve args",test_NumBuckets)) ||
    (NULL == CU_add_test(pSuite, "test of files - main test",test_Files)))
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
