//
// Created by Kim Simoski on 19.11.2022.
//

#ifndef NUPPROJECT_SHELFPAIR_H
#define NUPPROJECT_SHELFPAIR_H


#include "Shelf.h"
#include "SegmentUse.h"
#include "../ConveyorBelt/TransferPoint.h"
#include <exception>
#include <iostream>

namespace inventoryLib {
    /*
    * The class ShelfPair is contained by the class Inventory. It represents one shelf pair of the inventory containing two shelves per pair.
    * The class provides methods to store or restore items. For reservations there are also methods to reserve for adding to and to reserve for getting from the inventory.
    * The class uses methods to calculate the fastest possible ways to shelf segments for storation processes.
    * The storage positions are based on three different levels of priority of items.
    */
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

        // TransferPoint to remove Containers from and put them into the Shelf
        TransferPoint inputTransferPoint;

        // TransferPoint to put Containers on to send them to KPoint
        TransferPoint outputTransferPoint;

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
        Shelf& getShelfByShelfNumber(unsigned int shelfNumber);
        [[nodiscard]] unsigned int getShelfPairNumber() const;
        [[nodiscard]] double getDistanceBetweenShelvesOfPair() const;
        double getShelfDepthInMeters();
        [[nodiscard]] TransferPoint& getInputTransferPoint();
        [[nodiscard]] TransferPoint& getOutputTransferPoint();

        void setSegmentsPriority(unsigned int shelfNumber, unsigned long long int row,
                                 unsigned long long int column, const Priority &priority);

        // methods
    public:
        //!!! Für folgende Methoden nochmal überprüfen, wie Zerstückelung stattfindet, wenn nicht ganze Ladung in einen Container passt
        //!!! Für folgende Methoden aktuelle Position der Bedienhilfen berücksichtigen, falls diese gerade frei sind. Dies aber eher mit Überladung der Methode machen, weil die generelle Regalzeilung ja schon vor dem Warten an der Warteschlange gemacht wird.
        //!!! -> Wenn die Berechnungen soweit implementiert sind, dass auch die Wartezeiten in der Schlange im Voraus bekannt sind, Methoden noch einmal ergänzen !!!

        void reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment);
        void reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment);

        void addContainer(const SegmentDataMessage& goalSegment, const Container& newContainer);
        Container takeContainer(const SegmentDataMessage& goalSegment);

        std::optional<TimeSegmentMessage> getFastestToReachSegmentBasedOnUse(const SegmentUse& containerUse, const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        void printAllShelfSegments();
    };
}




#endif //NUPPROJECT_SHELFPAIR_H
