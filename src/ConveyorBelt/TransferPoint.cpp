#include "TransferPoint.h"


TransferPoint::TransferPoint(float _distanceToPackaging) : distanceToPackaging{_distanceToPackaging} {}

// Put a Container onto the TransferPoint
void TransferPoint::addContainer(Container &_container, Timer &_timer) {
    // Put new Container onto the TransferPoint if there is still room
    if((1 + containers.size()) * Container::length < this->length) {
        containers.push(_container);
        _timer.addSeconds(2.5);
        std::cout << "Added Container \"" << _container.name << "\" to TransferPoint. Took 2.5 seconds. Timer now at: " << _timer.timeInSeconds << std::endl;
    }
}

// Remove a Container from the TransferPoint and return a reference to it
Container &TransferPoint::removeContainer(Timer &_timer) {
    // Wait until there is a Container (if there is none)
    while (containers.empty()) {
        _timer.addSeconds(0.5);
        Sleep(500);
    }
    // Store the first Container from the queue
    Container& container = containers.front();
    // Remove from queue
    containers.pop();
    _timer.addSeconds(2.5);
    std::cout << "Removed Container \"" << container.name << "\" from TransferPoint. Took 2.5 seconds. Timer now at: " << _timer.timeInSeconds << std::endl;
    return container;
}

float TransferPoint::getDistance() const {
    return distanceToPackaging;
}
