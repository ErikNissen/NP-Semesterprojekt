//
// Created by Kim Simoski on 19.11.2022.
//

#include "ShelfPair.h"

using namespace inventoryLib;
using namespace messagesLib;

// constructors
ShelfPair::ShelfPair(const unsigned int shelfPairNumber, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow,
                     const double verticalMaxVelocityInMetersPerSecond, const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond, const double horizontalAccelerationInMetersPerSquareSeconds,
                     const double distanceBetweenShelvesOfPair, const double shelfWidthInMeters, const double shelfHeightInMeters, const double shelfDepthInMeters,
                     const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters, const double distanceBetweenSegmentsInMeters,
                     const double segmentWidthInMeters, const double segmentHeightInMeters, const double segmentDepthInMeters, const double containerWidthInMeters, const double containerHeightInMeters,
                     const double containerDepthInMeters){

    // log data
    this-> shelfPairNumber = shelfPairNumber;

    // measurement
    this-> distanceBetweenShelvesOfPair = distanceBetweenShelvesOfPair;

    // initiate amountOfShelves
    shelfLeft = Shelf{shelfPairNumber * 2 - 1, rowsPerShelf, segmentsPerRow, verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
    shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters, distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
    segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters, containerDepthInMeters};
    shelfRight = Shelf{shelfPairNumber * 2, rowsPerShelf, segmentsPerRow, verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
    shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters, distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
    segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters, containerDepthInMeters};
}

// getters and setters
unsigned int ShelfPair::getShelfPairNumber() const{
    return shelfPairNumber;
}

Shelf& ShelfPair::getShelfByShelfNumber(const unsigned int shelfNumber) {
    if(shelfLeft.getShelfNumber() == shelfNumber){
        return shelfLeft;
    }
    else if (shelfRight.getShelfNumber() == shelfNumber){
        return shelfRight;
    }
    else throw std::invalid_argument("Shelf number is not found in current shelf number. An argument has been set wrong.");
    //!!! https://cppbyexample.com/exceptions.html#:~:text=In%20C%2B%2B%20to%20raise%20or%20throw%20exceptions%20the,many%20basic%20exception%20types%20in%20the%20%3Cexception%3E%20header.
}

double ShelfPair::getDistanceBetweenShelvesOfPair() const {
    return distanceBetweenShelvesOfPair;
}

double ShelfPair::getShelfDepthInMeters(){
    return shelfLeft.getShelfDepthInMeters();
}

void ShelfPair::setSegmentsPriority(const unsigned int shelfNumber, const unsigned long long int row, const unsigned long long int column, const Priority& priority) {
    getShelfByShelfNumber(shelfNumber).setSegmentsPriority(row, column, priority);
}

// methods
//!!! Berücksichtigt noch nicht, dass Eingabe und Ausgabe unterschiedliche Höhen und damit unterschiedliche Strecken haben!!!
std::optional<TimeSegmentMessage> ShelfPair::getFastestToReachSegmentBasedOnUse(const SegmentUse& containerUse, const Item& item) {
    auto timeSegmentMessageOfFastestWayToSegmentShelfLeft{
            shelfLeft.getFastestToReachSegmentsBasedOnUse({1, 0, 0}, containerUse, item)};
    auto timeSegmentMessageOfFastestWayToSegmentShelfRight{
            shelfRight.getFastestToReachSegmentsBasedOnUse({1, 0, 0}, containerUse, item)};

    if(timeSegmentMessageOfFastestWayToSegmentShelfLeft && timeSegmentMessageOfFastestWayToSegmentShelfRight) {
        if (timeSegmentMessageOfFastestWayToSegmentShelfLeft->getNeededTimeWithoutWaitingInQueueInSeconds() <=
            timeSegmentMessageOfFastestWayToSegmentShelfRight->getNeededTimeWithoutWaitingInQueueInSeconds()) {
            return timeSegmentMessageOfFastestWayToSegmentShelfLeft;
        } else {
            return timeSegmentMessageOfFastestWayToSegmentShelfRight;
        }
    }
    else if(timeSegmentMessageOfFastestWayToSegmentShelfLeft){
        return (timeSegmentMessageOfFastestWayToSegmentShelfLeft);
    }
    else if(timeSegmentMessageOfFastestWayToSegmentShelfRight){
        return (timeSegmentMessageOfFastestWayToSegmentShelfRight);
    }
    else {
        return {};
    }
}


void ShelfPair::reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment) {
    getShelfByShelfNumber(goalSegment.getShelfNumber()).reserveSegmentToAddContainer(goalSegment);
}

void ShelfPair::reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment) {
    getShelfByShelfNumber(goalSegment.getShelfNumber()).reserveSegmentToGetContainer(goalSegment);
}

void ShelfPair::addContainer(const SegmentDataMessage &goalSegment, const Container &newContainer) {
    getShelfByShelfNumber(goalSegment.getShelfNumber()).addContainer(goalSegment, newContainer);
}

//ToDo: get und take einheitlich benennen
Container ShelfPair::takeContainer(const SegmentDataMessage &goalSegment) {
    return getShelfByShelfNumber(goalSegment.getShelfNumber()).takeContainer(goalSegment);
}

void ShelfPair::printAllShelfSegments() {
    shelfLeft.printShelfSegments();
    shelfRight.printShelfSegments();
}














