#include "main.hpp"
#include "ConveyorBeltStore.h"
#include "ConveyorBeltRetrieve.h"

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
}