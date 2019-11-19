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

    InitStrategy* init = new RandomInit(cluster);
    AssignmentStrategy* assign = new InverseAssignment(cluster);
    UpdateStrategy* update = new CentroidUpdate(cluster);

    init->execute();
    cluster->testPrintClusterKeysAndSize();
    int i = 2;
    do{
        assign->execute();
        update->execute();
    }while(i--);
    cluster->output("Algorithm: Ι1A2U1");
    //TODO: clear cluster to use it again
    delete init; delete assign; delete update;

    init = new RandomInit(cluster);
    assign = new LloydAssignment(cluster);
    update = new PAMUpdate(cluster);

}