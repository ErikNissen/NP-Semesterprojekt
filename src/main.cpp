#include "main.hpp"
#include <algorithm>
#include "Inventory.h"
#include "ConveyorBeltStore.h"
#include "ConveyorBeltRetrieve.h"
#include "Inventory.h"
#include "PersistentFileManagement/PersistentFileManagement.hpp"

int main (int argc, char *argv[]) {
    /*
    // Initialize objects
    TransferPoint transfer1(12);
    TransferPoint transfer2(14.2);
    ConveyorBeltStore conveyorStore;
    ConveyorBeltRetrieve conveyorRetrieve;
    Container container1(Priority::One, "Container 1");
    Container container2(Priority::Two, "Container 2");
    Container container3(Priority::Three, "Container 3");

    // Store some containers at the TransferPoints
    conveyorStore.transportContainer(container1, transfer1);
    conveyorStore.transportContainer(container2, transfer1);
    conveyorStore.transportContainer(container3, transfer2);

    Sleep(100);

    // Retrieve the Containers from the TransferPoints
    conveyorRetrieve.transportContainer(transfer2);
    conveyorRetrieve.transportContainer(transfer1);
    conveyorRetrieve.transportContainer(transfer1);
    conveyorRetrieve.transportContainer(transfer2, timer);
    conveyorRetrieve.transportContainer(transfer1, timer);
    conveyorRetrieve.transportContainer(transfer1, timer);


    // -------------------------------------------------------------------------------
*/
    //!!! Für Debugging auf 5 * 5 Matrizen verändert. Projekt-Info ist 54*90
    auto inventory{inventoryLib::Inventory(8, 90, 2, 2.6, 10, 5, 5,
                             0.8, 0.5, 3.5, 0.4,
                             1.2, 49.6, 28.0, 0.7,
                             1.5, 0.0, 0.1,
                             0.45, 0.45, 0.65, 0.4, 0.4,
                             0.6)};

    inventory.printShelfSegments();


    //!!! Startpunkt mit aktuellem Punkt usw. später noch abgleichen und überarbeiten
    SegmentDataMessage startPoint{1,0,0};

    startPoint.print();

    TimeSegmentMessage testMessage{1, startPoint};
    testMessage.print();


    inventory.reserveSegmentToAddContainer({1,0,0});

    // test adding containers
    Item item {1, Priority::A, 5};
    Container container {item};
    container.addAmount(container.getAmountOfPlacesForItem()-1);
    inventory.addContainer({1,0,0}, container);

    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> after adding container to shelf 1, row 1, segment 1: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    inventory.printShelfSegments();

    /*
    // test reserving segment for container output for adding item to fastest to reach container
    auto fastestToReachContainerToAddItems{inventory.reserveContainerOutputFromInventoryToAddItems(startPoint, item)};
    if(fastestToReachContainerToAddItems) {
        std::cout << "Der aktuell schnellste zu erreichende Container zum Hinzufügen von Items: " << std::endl;
        fastestToReachContainerToAddItems->print();
    }
    else{
        std::cout << "Aktuell steht kein Container zum Hinzufügen von Items zur Verfügung." << std::endl;
    }
    */

    // test reserving segment for container output for adding item to fastest to reach container
    auto fastestToReachContainerToGetItems{inventory.reserveContainerOutputFromInventoryToGetItems(startPoint, item)};
    if(fastestToReachContainerToGetItems) {
        std::cout << "Der aktuell schnellste zu erreichende Container zum Entnehmen von Items: " << std::endl;
        fastestToReachContainerToGetItems->print();
    }
    else{
        std::cout << "Aktuell steht kein Container zum Entnehmen von Items zur Verfügung." << std::endl;
    }

    //inventory.reserveSegmentToGetContainer({1,0,0});


     /*
     inventory.reserveSegmentToGetContainer(timeSegmentMessageFromFastestToReach->getSegmentDataMessage());

    //inventory.takeContainer({1,0,0});

    */





    return 0;
}