//
// Created by Kim Simoski on 19.11.2022.
//

#ifndef NUPPROJECT_INVENTORY_H
#define NUPPROJECT_INVENTORY_H

#include "ShelfPair.h"
#include "SegmentUse.h"

namespace inventoryLib {
    /*
     * The class Inventory represents the whole inventory containing several shelfpairs (ShelfPair) which contain two shelves (Shelf) per pair. Each shelf has rows with coloumns as segments containting containers (Segment) for containing items (Item)
     * The class provides methods to store or restore items. For reservations there are also methods to reserve for adding to and to reserve for getting from the inventory.
     * The class uses methods to calculate the fastest possible ways to shelf segments for storation processes.
     * The storage positions are based on three different levels of priority of items.
     */
    //!!! Segment und Container nicht synonym verwenden. Für Methoden Entscheidung für eins der beiden Treffen und Bezeichner überarbeiten !!!
    class Inventory {

        //attributes
    private:
        std::vector<ShelfPair> shelfPairs;

        // log_data


        // counts
        unsigned int amountOfShelves;

        unsigned long long int rowsPerShelf;
        unsigned long long int segmentsPerRow;


        // measurements

        // conveyor belt
        double conveyorBeltVelocity; // needed for finding the matching segment with the shortest way by regarding the way between shelf pairs

        /*
        // transport vehicle
        double verticalMaxVelocityInMetersPerSecond;
        double verticalAccelerationInMetersPerSquareSeconds;

        double horizontalMaxVelocityInMetersPerSecond;
        double horizontalAccelerationInMetersPerSquareSeconds;

        //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!
        */
        // inventory
        double distanceBetweenShelves;

        unsigned int percentageOfPriorityA;
        unsigned int percentageOfPriorityB;
        unsigned int percentageOfPriorityC;

        /*
        // shelf
        double shelfWidthInMeters;
        double shelfHeightInMeters;
        double shelfDepthInMeters;

        double distanceFromFloorToInputInMeters;
        double distanceFromFloorToOutputInMeters;

        // segment
        double distanceBetweenSegmentsInMeters;

        double segmentWidthInMeters;
        double segmentHeightInMeters;
        double segmentDepthInMeters;

        // container
        double containerWidthInMeters;
        double containerHeightInMeters;
        double containerDepthInMeters;
        */

        // constructors
    public:
        //Inventory() = default;

        Inventory(unsigned int percentageOfPriorityA, unsigned int percentageOfPriorityB, unsigned int percentageOfPriorityC, double conveyorBeltVelocity, unsigned int numberOfShelfPairs, unsigned long long int rowsPerShelf,
                  unsigned long long int segmentsPerRow,
                  double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds,
                  double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds,
                  double distanceBetweenShelfPairs, double shelfWidthInMeters, double shelfHeightInMeters,
                  double shelfDepthInMeters,
                  double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters,
                  double distanceBetweenSegmentsInMeters,
                  double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters,
                  double containerWidthInMeters, double containerHeightInMeters,
                  double containerDepthInMeters);

        // getters and setters
        //!!! Für Debugging public gemacht -> Später private machen !!!
    public:
        ShelfPair& getShelfPairByShelfNumber(unsigned int shelfNumber);
        static unsigned int getShelfPairNumberByShelfNumber(unsigned int shelfNumber);

        void setSegmentsPriority(const SegmentDataMessage &segmentDataMessage, const Priority &priority);
        void setSegmentsPriority(unsigned int shelfNumber, unsigned long long int row, unsigned long long int column, const Priority& priority);


        // methods
    private:

       //void initiateContainerPriorities();
        void setSegmentPrioritiesBasedOnFastestToReachSegmentsAndPrioPercentages();
        void initiateContainerPriorities(unsigned int amountOfSegmentsReservedForPrio, const Priority &priority);

        //!!! Aktuellen Punkt der Bedienhilfen berücksichtigen (Allerdings muss für die Einlagerung die Bedienhilfe am Ausgangspunkt sein. Dafür müssten dann auch die Dauern für Rückfahrten der Bedienhilfen vom vorherigen (Ziel)Segment bestimmt werden. Die Strecke des vorher wartenden Containers wird also immer doppelt gefahren. Dazu kommt noch, dass ggf. auf gleichem Weg noch eine Auslieferung getätigt wird.) !!!
        //!!! Wo wird das aktuelle Segment gespeichert und wo ist dessen Abfrage relevant ??? !!!
        // The method gets the TimeSegmentMessage which contain the Segments coordinates and the time needed for the way (waiting time in queues excluded)
        std::optional<TimeSegmentMessage> getFastestToReachContainerWithoutSetPriority(const SegmentDataMessage& currentSegment); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference
        std::optional<TimeSegmentMessage> getFastestToReachContainerForItemInput(const SegmentDataMessage& currentSegment, const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference
        std::optional<TimeSegmentMessage> getFastestToReachContainerForItemOutput(const SegmentDataMessage& currentSegment, const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        std::optional<TimeSegmentMessage> getFastestToReachContainerBasedOnUse(const SegmentDataMessage& currentSegment, const SegmentUse& containerUse, const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        double calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(unsigned int shelfPairNumber);

    public:
        //!!! Für die folgenden beiden Methoden aktuelle Position der Bedienhilfen berücksichtigen, falls diese gerade frei sind. Dies aber eher mit Überladung der Methode machen, weil die generelle Regalzeilung ja schon vor dem Warten an der Warteschlange gemacht wird.
        //!!! -> Wenn die Berechnungen soweit implementiert sind, dass auch die Wartezeiten in der Schlange im Voraus bekannt sind, Methoden noch einmal ergänzen !!!
        std::optional<TimeSegmentMessage> reserveContainerOutputFromInventoryToGetItems(const SegmentDataMessage& currentSegment, const Item& item);
        std::optional<TimeSegmentMessage> reserveContainerToAddToInventory(const SegmentDataMessage& currentSegment, const Item& item);

        void reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment);
        void reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment);

        void addContainer(const SegmentDataMessage& goalSegment, const Container& newContainer);
        Container takeContainer(const SegmentDataMessage& goalSegment);

        //!!! Die Methode noch so ausbessern, dass dem ConveyorBelt eine Liste der jeweils besten Plätze pro Regalpaar übergeben werden kann (, damit dieser anhand der Warteschlangen nochmal berechnen kann, welches Segment insgesamt inklusive der Warteschlangen zum Zeitpunkt des ankommens am optimalsten ist)!!!
        //std::vector<TimeSegmentMessage> getListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment);

        void printShelfSegments();

        std::optional<TimeSegmentMessage>
        reserveContainerOutputFromInventoryToAddItems(const SegmentDataMessage &currentSegment, const Item &item);
    };
}

#endif //NUPPROJECT_INVENTORY_H
