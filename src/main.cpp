#include "Cluster.h"
#include "ui.h"
#include "utils.h"
#include "parse_files.h"
#include "strategy.h"
#include <sstream>
#include <chrono>

using namespace std;

enum InitAlgo {Random,SpreadOut};
enum AssignAlgo {Lloyd,Inverse};
enum UpdateAlgo {PAM,Centroid};
InitStrategy* init;
AssignmentStrategy* assign;
UpdateStrategy* update;

void executeAlgorithm(Cluster* cluster, InitAlgo init_selection, AssignAlgo assign_selection,
 UpdateAlgo update_selection);

int main(int argc, char* argv[]) {
    auto cluster = new Cluster();
    readArguments(cluster, argc, argv);
    cluster->setData(parseFile(cluster->getGeneralParameters()->getInputFilename()));
    //test_print_data(cluster->getDataset());

    executeAlgorithm(cluster,Random,Lloyd,PAM);
    executeAlgorithm(cluster,Random,Lloyd,Centroid);
    executeAlgorithm(cluster,Random,Inverse,PAM);
    executeAlgorithm(cluster,Random,Inverse,Centroid);
    executeAlgorithm(cluster,SpreadOut,Lloyd,PAM);
    executeAlgorithm(cluster,SpreadOut,Lloyd,Centroid);
    executeAlgorithm(cluster,SpreadOut,Inverse,PAM);
    executeAlgorithm(cluster,SpreadOut,Inverse,Centroid);
}

void executeAlgorithm(Cluster* cluster, InitAlgo init_selection, AssignAlgo assign_selection,
 UpdateAlgo update_selection){
     switch (init_selection) {
        case Random:    init = new RandomInit(cluster);break;
        case SpreadOut: init = new SpreadOutInit(cluster);break;
     }
     switch (assign_selection) {
        case Lloyd:   assign = new LloydAssignment(cluster);break;
        case Inverse: assign = new InverseAssignment(cluster);break;
     }
     switch (update_selection) {
        case PAM:      update = new PAMUpdate(cluster);break;
        case Centroid: update = new CentroidUpdate(cluster);break;
     }
    auto start = chrono::steady_clock::now();
    cout <<"============="<<endl<< "ALGORITHM " << init_selection+1 << assign_selection+1 << 
    update_selection+1 << endl<<"============="<<endl;
    cout << "initializing..." << endl;
    init->execute();
    cout<<"----------------"<<endl;
    cluster->testPrintCurrentCenters();
    cout<<"----------------"<<endl;
    int count = 0;
    do{
        cout << count << ". assigning..." << endl;
        assign->execute();
        cout << count << ". updating..." << endl;
        if (update->execute())  {
            cout << "update break!" << endl;
            break;
        }
    }while(count++ < 20);
    //a last assignment is mandatory.
    //otherwise clusters map has no values
    cout << count << ". assigning..." << endl;
    assign->execute();
    cout << "finished clustering!" << endl;
    auto end = chrono::steady_clock::now();
    auto time_span = static_cast<chrono::duration<double>>(end - start);
    cout<<"Operation took: "<< time_span.count() <<" seconds" << endl;
    stringstream firstLine;
    firstLine << "Algorithm I" << init_selection+1 << "A" << assign_selection+1 << "U" << update_selection+1;
    cluster->output(firstLine.str(), time_span.count());
    //clean
    cluster->clear();
    delete init;
    delete assign;
    delete update;
}