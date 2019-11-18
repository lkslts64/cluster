#include "Cluster.h"
#include "ui.h"
#include "utils.h"
#include "parse_files.h"
#include "strategy.h"

using namespace std;

int main(int argc, char* argv[]) {

    auto cluster = new Cluster();

    readArguments(cluster, argc, argv);

    cluster->setData(parseFile(cluster->getGeneralParameters()->getInputFilename()));
    //test_print_data(cluster->getDataset());

    auto init = new RandomInit(cluster);
    auto assign = new InverseAssignment(cluster);
    auto update = new PAMUpdate(cluster);

    init->execute();
    cluster->testPrintClusterKeysAndSize();
    do{
        assign->execute();
        update->execute();
    }while(0);


}