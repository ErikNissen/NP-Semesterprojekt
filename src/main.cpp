#include "main.hpp"
#include <algorithm>
//#include "Inventory.h"
#include "ConveyorBeltStore.h"
#include "ConveyorBeltRetrieve.h"

//using namespace Inventory;
//using namespace Messages;

int main (int argc, char *argv[]) {
    // Initialize objects
    Timer timer;
    TransferPoint transfer1(12);
    TransferPoint transfer2(14.2);
    ConveyorBeltStore conveyorStore;
    ConveyorBeltRetrieve conveyorRetrieve;
    Container container1("container1");
    Container container2("container2");
    Container container3("container3");

    // Store some containers at the TransferPoints
    timer.printSeconds();
    conveyorStore.transportContainer(container1, transfer1, timer);
    conveyorStore.transportContainer(container2, transfer1, timer);
    conveyorStore.transportContainer(container3, transfer2, timer);

    Sleep(100);

    // Retrieve the Containers from the TransferPoints
    conveyorRetrieve.transportContainer(transfer2, timer);
    conveyorRetrieve.transportContainer(transfer1, timer);
    conveyorRetrieve.transportContainer(transfer1, timer);

    // -------------------------------------------------------------------------------

    //!!! Für Debugging auf 5 * 5 Matrizen verändert. Projekt-Info ist 54*90
//    auto inventory{Inventory{2.6, 10, 5, 5,
//                             0.8, 0.5, 3.5, 0.4,
//                             1.2, 49.6, 28.0, 0.7,
//                             1.5, 0.0, 0.1,
//                             0.45, 0.45, 0.65, 0.4, 0.4,
//                             0.6}};

    //!!! For Debugging !!!
    //!!! Startpunkt mit aktuellem Punkt usw. später noch abgleichen und überarbeiten
//    SegmentDataMessage startPoint{1,0,0};
    //auto emptyContainer{inventory.getFastestToReachEmptyContainer(startPoint)};

    //!!!getFastestToReachEmptyContainer({1,0,0}) gibt noch ein anderes Ergebnis zurück, als wenn mit startPoint als Parameter direkt eine SegmentDataMessage in den entsprechenenden Konstruktor gegeben wird!!!
    /*auto emptyContainer{inventory.getFastestToReachEmptyContainer({1,0,0})};
    std::cout << "!!! Ausgabe mit fertiger Print-Methode: !!! \n";
    emptyContainer.print();
    */


    //inventory.printListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(startPoint);


    //inventory.printShelfSegments();

    /*
    auto timeSegmentMessageToFastestSegment{inventory.getFastestToReachEmptyContainer({1,0,0})};

    std::cout<< "[*GESAMTWEG OHNE QUEUES*]: " << std::endl;
    timeSegmentMessageToFastestSegment.print();
*/

    //!!! Für Debugging. Später in Main auf Basis der Methode Regale mit Containern füllen, die eine Priorität haben.!!!

    for(int i{1}; i < 50; i++) {
        //!!! Zugriff in folgender Zeile funktioniert nicht !!!
//        inventory.fillBasedOnFastestToReachSegments(i);
    }

//    inventory.printShelfSegments();



    /*
    //FOR DEBUGGING
    std::cout << "TESTOUTPUT VON DIREKTER SHELFPAIR-ANSTEUERUNG!" << std::endl;
    inventory.setSegment(1,0,0,10);

    inventory.printShelfSegments();
    */

    /*
    std::cout << "TESTOUTPUT VON DIREKTER SHELFPAIR-ANSTEUERUNG!" << std::endl;
    inventory.shelfPairs[0].setSegment(1,0,0,10);

    std::cout << "FOR DEBUGGING SEGMENTE von shelf pair 1:!" << std::endl;
    inventory.shelfPairs[0].printShelfSegments();
    */


    /*
    auto fastestToReachEmptyContainer{inventory.getFastestToReachEmptyContainer(startPoint)};
    std::cout << "REGAL, IN DEM INSGESAMT SCHNELLSTES ZU ERREICHENDES SEGMENT IST" << std::endl;
    std::cout << fastestToReachEmptyContainer.getShelfNumber() << std::endl;
    std::cout << fastestToReachEmptyContainer.getRow() << std::endl;
    std::cout << fastestToReachEmptyContainer.getColumn() << std::endl;
    std::cout << "time needed: " << fastestToReachEmptyContainer.getNeededTimeWithoutWaitingInQueueInSeconds() << std::endl;

    fastestToReachEmptyContainer.print();
*/


    //fastestToReachEmptyContainer.print();

/*
    auto fastestToReachEmptyContainer{inventory.getFastestToReachEmptyContainer(startPoint)};
    fastestToReachEmptyContainer.print();

    inventory.setSegment(1,0,0,10);
    inventory.printShelfSegments();
    fastestToReachEmptyContainer = inventory.getFastestToReachEmptyContainer(startPoint);
    fastestToReachEmptyContainer.print();

    inventory.setSegment(1,0,1,10);
    inventory.printShelfSegments();
    fastestToReachEmptyContainer = inventory.getFastestToReachEmptyContainer(startPoint);
    fastestToReachEmptyContainer.print();
*/




/*
    getFastestToReachEmptyContainer(startPoint).print();

    matrix[0][0]=10;

    getFastestToReachEmptyContainer(startPoint).print();

    matrix[1][0]=10;
    getFastestToReachEmptyContainer(startPoint).print();
    */


// !!! Mehrere Ausgaben hinterhereinanfer der jeweils gleichen Methode funktionieren. Diese Aufrufe funktionieren auch einzeln, aber nicht Nacheinander. Irgendein Problem mit Binding oder Freigeben der wenigen Pointer??? Oder Static-Methoden !!!

/*
    std::cout << "needed time for reaching shelf pair via conveyor belt in seconds: " << inventory.calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(1) << std::endl;
    std::cout << "needed time for reaching shelf pair via conveyor belt in seconds: " << inventory.calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(2) << std::endl;
    std::cout << "needed time for reaching shelf pair via conveyor belt in seconds: " << inventory.calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(3) << std::endl;
    std::cout << "needed time for reaching shelf pair via conveyor belt in seconds: " << inventory.calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(4) << std::endl;
    std::cout << "needed time for reaching shelf pair via conveyor belt in seconds: " << inventory.calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(5) << std::endl;
    std::cout << "needed time for reaching shelf pair via conveyor belt in seconds: " << inventory.calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(6) << std::endl;
*/

    //std::cout << "Hello, World!" << std::endl;

    /*
    inventory.getFastestToReachEmptyContainer(startPoint).print();
    inventory.getFastestToReachEmptyContainer(startPoint).print();
    inventory.getFastestToReachEmptyContainer(startPoint).print();
    */
    return 0;
}