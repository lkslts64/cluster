#include "Cluster.h"
#include "ui.h"
#include "utils.h"
#include "parse_files.h"
#include "strategy.h"
#include <sstream>

using namespace std;

InitStrategy* init;
AssignmentStrategy* assign;
UpdateStrategy* update;

void executeAlgorithm(Cluster *,int,int,int);

int main(int argc, char* argv[]) {
    auto cluster = new Cluster();
    readArguments(cluster, argc, argv);
    cluster->setData(parseFile(cluster->getGeneralParameters()->getInputFilename()));
    //test_print_data(cluster->getDataset());

    executeAlgorithm(cluster,1,1,1);
    executeAlgorithm(cluster,1,1,2);
    executeAlgorithm(cluster,1,2,1);
    executeAlgorithm(cluster,1,2,2);
    executeAlgorithm(cluster,2,1,1);
    executeAlgorithm(cluster,2,1,2);
    executeAlgorithm(cluster,2,2,1);
    executeAlgorithm(cluster,2,2,2);
}


void executeAlgorithm(Cluster* cluster, int init_selection, int assign_selection, int update_selection){
    if(init_selection == 1)   init = new RandomInit(cluster);
    else                      init = new SpreadOutInit(cluster);
    if(assign_selection == 1) assign = new LloydAssignment(cluster);
    else                      assign = new InverseAssignment(cluster);
    if(update_selection == 1) update = new PAMUpdate(cluster);
    else                      update = new CentroidUpdate(cluster);

    init->execute();
    //cluster->testPrintClusterKeysAndSize();
    int count = 10;
    do{
        assign->execute();
        if (update->execute())  {
            cout << "update break!" << endl;
            break;
        }
    }while(count-- > 0);
    //a last assignment is mandatory.
    //otherwise clusters map has no values
    assign->execute();

    stringstream firstLine;
    firstLine << "Algorithm I" << init_selection << "A" << assign_selection << "U" << update_selection;
    cluster->output(firstLine.str());

    //clean
    cluster->clear();
    delete init;
    delete assign;
    delete update;
}