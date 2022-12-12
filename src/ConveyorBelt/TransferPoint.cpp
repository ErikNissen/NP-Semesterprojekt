#include "TransferPoint.h"


TransferPoint::TransferPoint(float _distanceToPackaging) : distanceToPackaging{_distanceToPackaging} {}

// Put a Container onto the TransferPoint
void TransferPoint::addContainer(Container &_container) {
    // Put new Container onto the TransferPoint if there is still room
    if((1 + containers.size()) * Container::length < this->length) {
        _container.timer.addSeconds(2.5);
        containers.push(_container);
        std::cout << "Added Container \"" << _container.name << "\" to TransferPoint. Took 2.5 seconds. Timer now at: " << _container.timer.timeInSeconds << std::endl;
    }
}

// Remove a Container from the TransferPoint and return a reference to it
Container &TransferPoint::removeContainer() {
    // Wait until there is a Container (if there is none)
    while (containers.empty()) {
        Sleep(500);
    }
    // Store the first Container from the queue
    Container& container = containers.front();
    container.timer.addSeconds(2.5);
    // Remove from queue
    containers.pop();
    std::cout << "Removed Container \"" << container.name << "\" from TransferPoint. Took 2.5 seconds. Timer now at: " << container.timer.timeInSeconds << std::endl;
    return container;
}

float TransferPoint::getDistance() const {
    return distanceToPackaging;
}
