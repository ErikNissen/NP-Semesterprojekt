//
// Created by Kim Simoski on 19.11.2022.
//

#include "ShelfPair.h"

using namespace inventoryLib;
using namespace messagesLib;

// constructors
/*
ShelfPair::ShelfPair(const unsigned long long int rows, const unsigned long long int columns){
    shelfLeft = Shelf{rows, columns};
    shelfRight = Shelf{rows, columns};
}
*/

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

double ShelfPair::getDistanceBetweenShelvesOfPair() const {
    return distanceBetweenShelvesOfPair;
}

double ShelfPair::getShelfDepthInMeters(){
    return shelfLeft.getShelfDepthInMeters();
}

//!!! For Debugging!!!
/*
void ShelfPair::setSegment(const unsigned int shelfNumber, const unsigned long long int row, const unsigned long long int column, const int value) {
    //auto &shelf{getShelfByShelfNumber(shelfNumber)};

    //!!! FOR DEBUGGING !!!
    std::cout << "SETSEGMENT IN SHELFPAIR" << std::endl;

    //shelf.setSegment(row, column, value);
    getShelfByShelfNumber(shelfNumber).setSegment(row, column, value);
}
*/

// methods

//!!! Methode und Zusammenhängende auf für Prioritäten reservierte Bereiche anpassen und das aktuelle Segment hier auslesen (Allerdings muss für die Einlagerung die Bedienhilfe am Ausgangspunkt sein. Dafür müssten dann auch die Dauern für Rückfahrten der Bedienhilfen vom vorherigen (Ziel)Segment bestimmt werden. Die Strecke des vorher wartenden Containers wird also immer doppelt gefahren. Dazu kommt noch, dass ggf. auf gleichem Weg noch eine Auslieferung getätigt wird.) !!!
TimeSegmentMessage ShelfPair::getFastestToReachEmptyContainer(const SegmentDataMessage& currentSegment) {
    TimeSegmentMessage timeSegmentMessageOfFastestWayToSegmentShelfLeft{shelfLeft.getFastestToReachEmptyContainer(currentSegment)};

    //!!! For Debugging !!!
    //std::cout<< "! Daten vom linken Regal: " << std::endl;
    //timeSegmentMessageOfFastestWayToSegmentShelfLeft.print();



    TimeSegmentMessage timeSegmentMessageOfFastestWayToSegmentShelfRight{shelfRight.getFastestToReachEmptyContainer(currentSegment)};

    //!!! For Debugging !!!
    //std::cout<< "! Daten vom rechten Regal: " << std::endl;
    //timeSegmentMessageOfFastestWayToSegmentShelfRight.print();




    if(timeSegmentMessageOfFastestWayToSegmentShelfLeft.getNeededTimeWithoutWaitingInQueueInSeconds() <= timeSegmentMessageOfFastestWayToSegmentShelfRight.getNeededTimeWithoutWaitingInQueueInSeconds()){
        //!!! FOR DEBUGGING !!!
        //std::cout << "Shelf pair number " << shelfPairNumber << "'s fastest to reach segment is in: " << shelfLeft.getShelfNumber() << std::endl;
        //timeSegmentMessageOfFastestWayToSegmentShelfLeft.print();

        return timeSegmentMessageOfFastestWayToSegmentShelfLeft;
    }
    else{
        //!!! FOR DEBUGGING !!!
        //std::cout << " Shelf pair " << shelfPairNumber << "'s fastest to reach segment is in: " << shelfRight.getShelfNumber() << std::endl;
        //timeSegmentMessageOfFastestWayToSegmentShelfRight.print();

        return timeSegmentMessageOfFastestWayToSegmentShelfRight;
    }
}

void ShelfPair::printShelfSegments() {
    shelfLeft.printShelfSegments();
    shelfRight.printShelfSegments();
}

//!!! Implementierung von currentSegment als {0,0,0} überarbeiten !!!
/*
void ShelfPair::fillBasedOnFastestToReachSegments(const int value) {
    auto fastestToReachEmptyContainer{getFastestToReachEmptyContainer({1,0,0})};
    getShelfByShelfNumber(fastestToReachEmptyContainer.getShelfNumber()).setSegment(fastestToReachEmptyContainer.getRow(), fastestToReachEmptyContainer.getColumn(), value);
}*/

//!!! Methode so modifizieren, dass sie einen Fehler wirft, wenn beide Regalnummern nicht zutreffen !!!
Shelf& ShelfPair::getShelfByShelfNumber(const int shelfNumber) {
    if(shelfLeft.getShelfNumber() == shelfNumber){
        return shelfLeft;
    }
    else if (shelfRight.getShelfNumber() == shelfNumber){
        return shelfRight;
    }
    else throw std::invalid_argument("Shelf number is not found in current shelf number. An argument has been set wrong.");
    //return *(*Shelf ) nullptr; //!!! Hier besser mit try und Exception arbeiten!!! https://cppbyexample.com/exceptions.html#:~:text=In%20C%2B%2B%20to%20raise%20or%20throw%20exceptions%20the,many%20basic%20exception%20types%20in%20the%20%3Cexception%3E%20header.
}









