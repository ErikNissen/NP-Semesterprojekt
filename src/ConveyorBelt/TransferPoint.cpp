#include "TransferPoint.h"

using namespace conveyorLib;

TransferPoint::TransferPoint(float _distanceToPackaging) : distanceToPackaging{_distanceToPackaging} {}

/// Put a Container onto the TransferPoint
void TransferPoint::addContainer(Container &_container) {
    // Put new Container onto the TransferPoint if there is still room
    if(static_cast<float>((1 + containers.size())) * Container::getLength() <
	this->length) {
        _container.getTimer().addSeconds(2.5);
        containers.push(_container);
        std::cout << "Added Container \"" << _container.getId() << "\" to TransferPoint. Took 2.5 seconds. Timer now at: " << _container.getTimer().getTimeInSeconds() << std::endl;
    }
}

/// Remove a Container from the TransferPoint and return a reference to it
Container &TransferPoint::removeContainer() {
    // Store the first Container from the queue
    Container& container = containers.front();
    container.getTimer().addSeconds(2.5);
    // Remove from queue
    containers.pop();
    std::cout << "Removed Container \"" << container.getId() << "\" from TransferPoint. Took 2.5 seconds. Timer now at: " << container.getTimer().getTimeInSeconds() << std::endl;
    return container;
}

float TransferPoint::getDistance() const {
    return distanceToPackaging;
}

bool TransferPoint::checkForContainer() const {
    if(containers.empty()) {
        return false;
    } else {
        return true;
    };
}
