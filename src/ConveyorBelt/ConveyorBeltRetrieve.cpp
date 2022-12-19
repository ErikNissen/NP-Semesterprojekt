//
// Created by alexn on 21.11.2022.
//

#include "ConveyorBeltRetrieve.h"

ConveyorBeltRetrieve::ConveyorBeltRetrieve() : ConveyorBelt() {}

// Transport a Container from a TransferPoint to the K-Point
Container& ConveyorBeltRetrieve::transportContainer(TransferPoint &_transferPoint) {
    // Calculate the time it takes to transport the Container the TransferPoint to the K-Point
    float timeOfTransport = _transferPoint.getDistance() / this->getSpeed();
    // Retrieve the Container from the TransferPoint
    Container& container = _transferPoint.removeContainer();
    container.getTimer().addSeconds(timeOfTransport);
    std::cout << "Transported Container \"" << container.getId() << "\" via ConveyorBelt. Took " << timeOfTransport <<
              " seconds. Timer now at: " << container.getTimer().getTimeInSeconds() << std::endl;
    return container;
}
