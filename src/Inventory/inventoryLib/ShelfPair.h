//
// Created by Kim Simoski on 19.11.2022.
//

#ifndef NUPPROJECT_SHELFPAIR_H
#define NUPPROJECT_SHELFPAIR_H


#include "Shelf.h"
#include <exception>
#include <iostream>

namespace inventoryLib {
    class ShelfPair {

        // attributes
    private:
        //!!! Bezeichnung der Regale für Speicherung des Logs evtl. überarbeiten, um absolute Nummerierung aller Regale zu erleichtern !!!
        Shelf shelfLeft, shelfRight;
        int currentRow{0}, currentColumn{0};

        // log data
        unsigned int shelfPairNumber; // beginning with 1

        // measurement
        double distanceBetweenShelvesOfPair;

        // constructors
    public:
        //ShelfPair(unsigned long long int rows, unsigned long long int columns);

        ShelfPair(unsigned int shelfPairNumber, unsigned long long int rowsPerShelf, unsigned long long int segmentsPerRow,
                  double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds,
                  double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds,
                  double distanceBetweenShelvesOfPair, double shelfWidthInMeters, double shelfHeightInMeters,
                  double shelfDepthInMeters,
                  double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters,
                  double distanceBetweenSegmentsInMeters,
                  double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters,
                  double containerWidthInMeters, double containerHeightInMeters,
                  double containerDepthInMeters);

        // getters and setters
    public:
        [[nodiscard]] unsigned int getShelfPairNumber() const;
        [[nodiscard]] double getDistanceBetweenShelvesOfPair() const;
        double getShelfDepthInMeters();

        //!!! For Debugging !!!
        void setSegment(unsigned int shelfNumber, unsigned long long int row, unsigned long long int column, int value);

        // methods
    public:
        // getFastestToReachEmptyContainer(double horizontalMaxVelocityInMetersPerSecond, double verticalMaxVelocityInMetersPerSecond, double )
        // getNextContainerOfProductKindWithSpace() // Als Rückgabewert muss die Regalbezeichnung mit übergeben werden. Evtl. Tuple oder Set zurückgeben
        // getClosestContainerToAdd(ItemKind item, amount); //based on getNextContainerOfProductKindWithSpace(ItemKind item) and in case of no matching Container: getFastestToReachEmptyContainer()
        // getClosestContainerToRemove(ItemKind item, amount); //based on getNextContainerOfProductKindWithSpace(ItemKind item)


        //!!! Vernünftige Handhabe einführen, wenn das Regalpaar keinen freien Container hat, ohne dass es den Aufruf von Inventory insgesamt blockiert, weil ja ein anderes Regalpaar einen passenden Platz haben kann!!!
        TimeSegmentMessage getFastestToReachEmptyContainer(const SegmentDataMessage& currentSegment); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference


        // getWayToNextMatchingContainer()
        // getNeededTimeForWayToNextMatchingContainer()

        //!!! Später auf ContainerInhalte abändern, sobald pro Segment ein Container vorliegt!!!
        void printShelfSegments();

        //!!! Später für Initialisierung mit leeren Containern drei verschiedener Prioritäten abändern!!!
        void fillBasedOnFastestToReachSegments(int value);

        Shelf& getShelfByShelfNumber(int shelfNumber);

    };
}




#endif //NUPPROJECT_SHELFPAIR_H
