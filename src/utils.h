#include <string>
#include "Dataset.h"

using namespace std;

int powModulo(int base,int exp,int div);
bool file_exists(const char* filename);
bool is_number(string  str);
double max(double,double);
double min(double,double);
void test_print_data_points(Dataset *data);
void test_print_query_data(QueryDataset *data);
int modulo(int a, int b);
void test_print_data_curves(Dataset *data);