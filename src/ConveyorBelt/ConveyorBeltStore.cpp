#include "ConveyorBeltStore.h"
#include "../Item/Container.h"
#include "TransferPoint.h"

ConveyorBeltStore::ConveyorBeltStore() : ConveyorBelt() {}

// Transport a Container from the I-Point to a TransferPoint
void ConveyorBeltStore::transportContainer(Container &_container, TransferPoint &_transferPoint) {
    // Calculate the time it takes to transport the Container from I-Point to TransferPoint
    float timeOfTransport = _transferPoint.getDistance() / this->getSpeed();
    _container.timer.addSeconds(timeOfTransport);
    std::cout << "Transported Container \"" << _container.name << "\" via ConveyorBelt. Took " << timeOfTransport <<
              " seconds. Timer now at: " << _container.timer.timeInSeconds << std::endl;
    // Let the Container be picked up and stored by the TransferPoint
    _transferPoint.addContainer(_container);
}
