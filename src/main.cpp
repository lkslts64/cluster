#include "Cluster.h"
#include "ui.h"
#include "utils.h"
#include "parse_files.h"

using namespace std;

int main(int argc, char* argv[]) {

    auto cluster = new Cluster();

    readArguments(cluster, argc, argv);

    //put condition if the file is points or curves
    cluster->setData(parseFile(cluster->getGeneralParameters()->getInputFilename()));
    test_print_data(cluster->getDataset());

    //for 8 combinations
    {
        //Initialization

        //Assignment & Update in a loop until
    }

}