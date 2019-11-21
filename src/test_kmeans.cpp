#define private public
#include "kmeans.h"
#include "distance.h"
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
   vector<Point> pointVec5 {(*new Point(vector<double> {-1,-1})),
   (*new Point(vector<double> {2,2})),(*new Point(vector<double> {10,10}))};
   auto curv1 = new Curve(pointVec);
   auto curv5 = new Curve(pointVec5);
   auto dtw = new DTW();
   auto ipairs = vector<struct IndexPairs>();
   auto dist = dtw->distWithIndexPairs(curv1,curv5,&ipairs);
   CU_ASSERT(dist > 11 && dist < 12);
   auto curv2 = new Curve(pointVec2);
   auto curv3 = new Curve(pointVec3);
   auto curv4 = new Curve(pointVec4);
   auto curves = set<Object *>();
   curves.insert(curv1);
   curves.insert(curv2);
   curves.insert(curv3);
   curves.insert(curv4);
   auto dba = new DBA(1);
   dba->setObjs(curves);
   bool stop;
   auto obj = dba->centroid(&stop);
   auto res = dynamic_cast<Curve *>(obj);
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

void test_KmeansPoints() {
   auto p1 = new Point(vector<double> {2,1});
   auto p2 = new Point(vector<double> {-6,9});
   auto p3 = new Point(vector<double> {-5,5});
   set<Object *> pset {p1,p2,p3};
   auto kmeans = new KmeansPoints(1.0,2);
   kmeans->setObjs(pset);
   bool stop;
   auto obj = kmeans->centroid(&stop);
   auto res = dynamic_cast<Point *>(obj);
   CU_ASSERT(res->getCoordinates().size() == 2);
   CU_ASSERT(int(res->getCoordinate(0)) == -3);
   CU_ASSERT(res->getCoordinate(1) == 5);
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
   if ((NULL == CU_add_test(pSuite, "test of DBA",test_DBA)) ||  
      ((NULL == CU_add_test(pSuite, "test of kmeans points",test_KmeansPoints))))
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
