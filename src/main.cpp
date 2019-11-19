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
    int count = 6;
    do{
        assign->execute();
        //cout <<count<< endl;
        if (update->execute())  {
            cout << "update break!" << endl;
            break;
        }
    }while(count-- > 0);
    //a last assignment is mandatory.
    //otherwise clusters map has no values
    assign->execute();
    cluster->output("Algorithm: Ι1A2U1");
    //TODO: clear cluster to use it again
    delete init; delete assign; delete update;

    init = new RandomInit(cluster);
    assign = new LloydAssignment(cluster);
    update = new PAMUpdate(cluster);

}