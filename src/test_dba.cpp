#define private public
#include "dba.h"
#include <iostream>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

using namespace std;
static FILE* temp_file = nullptr;


void test_DBA() {
   vector<Point> pointVec {(*new Point(vector<double> {-1,-1})),
   (*new Point(vector<double> {2,2}))};
   vector<Point> pointVec2 {(*new Point(vector<double> {3,3})),
   (*new Point(vector<double> {4,4}))};
   vector<Point> pointVec3 {(*new Point(vector<double> {-15,63})),
   (*new Point(vector<double> {-5,5}))};
   vector<Point> pointVec4 {(*new Point(vector<double> {-20,83})),
   (*new Point(vector<double> {-6,9}))};
   auto curv1 = new Curve(pointVec);
   auto curv2 = new Curve(pointVec2);
   auto curv3 = new Curve(pointVec3);
   auto curv4 = new Curve(pointVec4);
   auto curves = vector<Curve *>();
   curves.push_back(curv1);
   curves.push_back(curv2);
   curves.push_back(curv3);
   curves.push_back(curv4);
   auto dba = new DBA(curves);
   auto res = dba->run();
   auto points = res->getPoints();
   CU_ASSERT(points.size() == 2);
   //check if we get the mean of values for every coordinate
   //e.g the centroid curve we will have point0-coordinate0 =
   //= (-1+2-15-10)/4
   CU_ASSERT(points.at(0).getCoordinate(0) == -8.25);
   CU_ASSERT(points.at(0).getCoordinate(1) == 37);
   CU_ASSERT(points.at(1).getCoordinate(0) == -1.25);
   CU_ASSERT(points.at(1).getCoordinate(1) == 5);
}

int init_suite1(void) { return 0; }

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
   if ((NULL == CU_add_test(pSuite, "test of DBA",test_DBA))) 
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
