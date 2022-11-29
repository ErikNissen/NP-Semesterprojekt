//
// Created by Kim Simoski on 19.11.2022.
//

#include <cmath>
#include "Inventory.h"

using namespace inventoryLib;
using namespace messagesLib;

// constructors
//!!! Bei Initialisierung zusätzlich die Aufteilung nach Prioritäten reservieren !!!

//!!! Anstatt alle Daten einzeln zu übergeben, vllt. Container-Object und Regal-Object usw. mit fertigen Maßen übergeben und anhanddessen Daten beziehen !!!
Inventory::Inventory(const double conveyorBeltVelocity, const unsigned int numberOfShelfPairs, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow, double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds, double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds, double distanceBetweenShelfPairs, double shelfWidthInMeters, double shelfHeightInMeters, double shelfDepthInMeters, double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters, double distanceBetweenSegmentsInMeters, double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters, double containerWidthInMeters, double containerHeightInMeters, double containerDepthInMeters){
    // initiate shelfs
    for(unsigned int shelfPairNumber{1}; shelfPairNumber <= numberOfShelfPairs; shelfPairNumber++){
        //shelfPairs.push_back({rowsPerShelf, segmentsPerRow});
        shelfPairs.emplace_back(shelfPairNumber, rowsPerShelf, segmentsPerRow, verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
                              distanceBetweenShelfPairs, shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters,
                              distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
                              segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters,
                              containerDepthInMeters);
    }

    //!!! Daten, die zum Regal gehören entweder nur hier deklarieren, als Parametern bei Methoden durchschleifen bis zu Shelf, oder nur in Shelf speichern und Attribute, da in einer Ebene höher sind, eine Ebene darüber, dafür Daten in den Konstruktoren durchschleifen und für die Log-Datei über Methode von jeder Klasse eigene Daten holen lassen, die dann über abgestützte Methoden durch Aufrufer weiter ergänzt werden. Letzteres ist eher objektorientiert.
    // save log data

    // counts
    this->amountOfShelves = numberOfShelfPairs * 2; //!!! Attribut kann wegrationalisiert werden, da die Anzahl aus den Regalen selbst beim Holen gezogen werden kann!!!

    /*
    this->rowsPerShelf = rowsPerShelf;
    this->segmentsPerRow = segmentsPerRow;

    // measurements
    this->verticalMaxVelocityInMetersPerSecond = verticalMaxVelocityInMetersPerSecond;
    this->verticalAccelerationInMetersPerSquareSeconds = verticalAccelerationInMetersPerSquareSeconds;

    this->horizontalMaxVelocityInMetersPerSecond = horizontalMaxVelocityInMetersPerSecond ;
    this->horizontalAccelerationInMetersPerSquareSeconds = horizontalAccelerationInMetersPerSquareSeconds;

    //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!
    */
    // inventory
    this->distanceBetweenShelves = distanceBetweenShelfPairs;
    this->conveyorBeltVelocity = conveyorBeltVelocity;

    /*
    // shelf
    this->shelfWidthInMeters = shelfWidthInMeters;
    this->shelfHeightInMeters = shelfHeightInMeters;
    this->shelfDepthInMeters = shelfDepthInMeters;

    this->distanceFromFloorToInputInMeters = distanceFromFloorToInputInMeters;
    this->distanceFromFloorToOutputInMeters = distanceFromFloorToOutputInMeters;

    // segment
    this->distanceBetweenSegmentsInMeters = distanceBetweenSegmentsInMeters;

    this->segmentWidthInMeters = segmentWidthInMeters;
    this->segmentHeightInMeters = segmentHeightInMeters;
    this->segmentDepthInMeters = segmentDepthInMeters;

    // container
    this->containerWidthInMeters = containerWidthInMeters;
    this->containerHeightInMeters = containerHeightInMeters;
    this->containerDepthInMeters = containerDepthInMeters;
     */
}

// getters and setters
//!!! Besser auf Methode abstützen, die aus der ShelfNumber die ShelfPairNumber berechnet!!!
ShelfPair& Inventory::getShelfPairByShelfNumber(const unsigned int shelfNumber) {
    return shelfPairs.at(getShelfPairNumberByShelfNumber(shelfNumber)-1); // the list of shelf pairs starts at 0 but with the member shelfPairNumber = 1
}

int Inventory::getShelfPairNumberByShelfNumber(const unsigned int shelfNumber) {
    return std::ceil(static_cast<double>(shelfNumber)/2);
}

//!!! For Debugging !!!
void Inventory::setSegment(const unsigned int shelfNumber, const unsigned long long int row, const unsigned long long int column, const int value) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(shelfNumber)};
    shelfPair.setSegment(shelfNumber, row, column, value);
}


// methods

//!!! Diese Methode berechnet den Weg vom ersten Einlagerungseinstellplatz über das Laufband bis zum jeweiligen Einlagerungseinstellplatz mit ein, aber beachtet dessen Warteschlange mit den jeweiligen Wartezeiten noch nicht. !!!
//!!! Analoge Methode ergänzen, die separat die Zeiten für die Einlagerung kennt. Dann könnten die für das Log gleich mitgegeben und für den Countdown an den Wartestationen. Ggf. aber auch woanders implementieren. Aber jeweils nur für das Zielsegment des insgesamt kürzesten Weges!!!
//!!! Beachtet noch nicht die jeweils aktuelle Position oder die Interaktion mit Ausgabeprozessen !!!
TimeSegmentMessage Inventory::getFastestToReachEmptyContainer(const SegmentDataMessage& currentSegment) {

    //std::vector<SegmentDataMessage> {};

    double shortestTimeInSeconds {-1};
    TimeSegmentMessage* segmentWithFastestWay;

    for(ShelfPair shelfPair: shelfPairs){
        //!!! Bezeichner kürzen!!!
        TimeSegmentMessage fastestToReachSegmentOfShelfPair{shelfPair.getFastestToReachEmptyContainer(currentSegment)};
        double neededTimeForReachingSegmentFromInputWaitingPlaceInSeconds{fastestToReachSegmentOfShelfPair.getNeededTimeWithoutWaitingInQueueInSeconds()};
        double neededTimeForReachingPairFromFirstPairsViaConveyorBeltInSeconds{calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(shelfPair.getShelfPairNumber())};
        double neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds{neededTimeForReachingSegmentFromInputWaitingPlaceInSeconds + neededTimeForReachingPairFromFirstPairsViaConveyorBeltInSeconds};

        if(shortestTimeInSeconds < 0 || neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds < shortestTimeInSeconds) {
            shortestTimeInSeconds = neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds;
            segmentWithFastestWay = new TimeSegmentMessage(neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds, fastestToReachSegmentOfShelfPair.getSegmentDataMessage());
        }

    }
    if (segmentWithFastestWay == nullptr){
        throw std::out_of_range("Cannot find empty space. All shelves are full.");
    }
    TimeSegmentMessage message{*segmentWithFastestWay};
    delete segmentWithFastestWay;
    return message;
}

//!!! Zugriffsweg auf distanceBetweenShelvesOfPair und shelfDepthInMeters überdenken!!!
//!!! Methodenbezeichner kürzen !!!
//!!! Für Debugging public gemacht. Hinterher wieder private machen !!!
double Inventory::calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(const int unsigned shelfPairNumber) {
    return static_cast<double>(shelfPairNumber - 1) * (shelfPairs.at(0).getDistanceBetweenShelvesOfPair() + 2 * shelfPairs[0].getShelfDepthInMeters())/conveyorBeltVelocity;

}

std::vector<TimeSegmentMessage> Inventory::getListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment) {
    std::vector<TimeSegmentMessage> listOfFastestToReachEmptyContainersForAllPairs{};
    for(ShelfPair& shelfPair: shelfPairs){
        listOfFastestToReachEmptyContainersForAllPairs.emplace_back(shelfPair.getFastestToReachEmptyContainer(currentSegment));
    }
    return listOfFastestToReachEmptyContainersForAllPairs;
}

void Inventory::printListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment) {
    auto listOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs{getListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(currentSegment)};
    for(auto fastestToReachEmptyContainersForShelfPair: listOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs){
        fastestToReachEmptyContainersForShelfPair.print();
    }
}

void Inventory::printShelfSegments() {
    std::cout << "!! All shelf segments: " << std::endl;
    for(auto shelfPair:shelfPairs){
        shelfPair.printShelfSegments();
    }
}

//!!! Berücksichtigte mit auskommentierter Zeile nicht die Daten, die SegmentDaten FastestToReach im Detail hier zurückgibt, sondern nur das entsprechende Regal. Dieses guckt dann wieder, welches das am schnellsten zu erreichende Segment ist. Das ist eigentlich unnötiger Arbeitsaufwand. Eigentlich könnte im Regal dann auch direkt die allgemeine set-Methode für Segmente aufgerufen werden!!!
//!!! Implementierung von 1,0,0 als Default-Current-Container verbessern!!!
void Inventory::fillBasedOnFastestToReachSegments(const int value) {
        auto fastestToReachEmptyContainer{getFastestToReachEmptyContainer({1,0,0})};
        auto shelfNumberFromFastestToReachSegment{fastestToReachEmptyContainer.getShelfNumber()};
        ShelfPair& shelfPair{getShelfPairByShelfNumber(shelfNumberFromFastestToReachSegment)};
        //shelfPair.fillBasedOnFastestToReachSegments(value);  //!!! Änderung für Kommentar oben in dieser Zeile!!!
        shelfPair.getShelfByShelfNumber(fastestToReachEmptyContainer.getShelfNumber()).setSegment(fastestToReachEmptyContainer.getRow(), fastestToReachEmptyContainer.getColumn(), value); //!!! Methoden hier besser aufeinander abstützen. Z.B. eine SetSegmentValue-Methode in Shelfpair integrieren, die auf der von Shelf abgestützt ist.

        //!!! FOR DEBUGGING !!!
        fastestToReachEmptyContainer.print();

}














