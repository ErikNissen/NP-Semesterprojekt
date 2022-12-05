//
// Created by Kim Simoski on 19.11.2022.
//

#ifndef NUPPROJECT_INVENTORY_H
#define NUPPROJECT_INVENTORY_H

# include "ShelfPair.h"
#include "ContainerUse.h"

namespace inventoryLib {
    /*
     * The class inventory represents the whole inventory containing several shelfpairs which contain two shelves per pair.
     * The class provides methods to store or restore items.
     * The class uses methods to calculate the fastest possible ways to shelf segments for storation processes.
     * The storage positions are based on three different levels of priority of items.
     */

    //!!! Segment und Container nicht synonym verwenden. Für Methoden Entscheidung für eins der beiden Treffen und Bezeichner überarbeiten !!!
    class Inventory {

        //attributes
    private:


        //!!! Public for Debugging. Hinterher wieder private machen !!!
    public:
        std::vector<ShelfPair> shelfPairs;

        double calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(unsigned int shelfPairNumber);

    private:
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
        ShelfPair& getShelfPairByShelfNumber(unsigned int shelfNumber);
        static unsigned int getShelfPairNumberByShelfNumber(unsigned int shelfNumber);

        //void setSegment(unsigned int shelfNumber, unsigned long long int row, unsigned long long int column, int value);
        void setSegmentsPriority(const SegmentDataMessage &segmentDataMessage, const Priority &priority);
        void setSegmentsPriority(unsigned int shelfNumber, unsigned long long int row, unsigned long long int column, const Priority& priority);


        // methods
        //!!! Dafür benötigte Zeiten für Fahrt zwischen den Regalpaaren zu den benötigten Zeiten innerhalb der Regalpaare addieren und dann den Weg mit kürzester benötigter Gesamtzeit wählen!!! Dabei Regaltiefen berücksichtigen!
        // getFastestToReachEmptyContainer() //!!! Rückgabewert: set/Tuple benötigte Zeit und Daten zum Segment (Regalpaar, Regal-Nummer, Segment-Nummer). Mit den Daten zum Segment übernimmt eine separate Methode den Weg Einlagerung
        // getNextContainerOfProductKindWithSpace()
        // getWayToNextMatchingContainer()
        // getNeededTimeForWayToNextMatchingContainer() // !!! Dafür Geschwindigkeiten und Beschleunigungen der Bediengeräte berücksichtigen !!!

    private:

       //void initiateContainerPriorities();

        void setSegmentPrioritiesBasedOnFastestToReachSegmentsAndPrioPercentages();

        void initiateContainerPriorities(const unsigned int amountOfSegmentsReservedForPrio, const Priority &priority);
    public:

        //addToInventory(ItemKind item);

        //!!! Methode und Zusammenhängende auf für Prioritäten reservierte Bereiche anpassen und das aktuelle Segment hier auslesen (Allerdings muss für die Einlagerung die Bedienhilfe am Ausgangspunkt sein. Dafür müssten dann auch die Dauern für Rückfahrten der Bedienhilfen vom vorherigen (Ziel)Segment bestimmt werden. Die Strecke des vorher wartenden Containers wird also immer doppelt gefahren. Dazu kommt noch, dass ggf. auf gleichem Weg noch eine Auslieferung getätigt wird.) !!!
        //!!! Wo wird das aktuelle Segment gespeichert und wo ist dessen Abfrage relevant ??? !!!
        // The method gets the TimeSegmentMessage which contain the Segments coordinates and the time needed for the way (waiting time in queues excluded)
        //TimeSegmentMessage getFastestToReachEmptyContainer(const SegmentDataMessage& currentSegment); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        //TimeSegmentMessage getFastestToReachContainerBasedOnUse(const SegmentDataMessage& currentSegment, const ContainerUse& containerUse, const TransferMessage& transferMessage); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        std::optional<TimeSegmentMessage> getFastestToReachContainerBasedOnUse(const SegmentDataMessage& currentSegment, const ContainerUse& containerUse, const TransferMessage& transferMessage); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference


        //!!! For Debugging!!!
        //std::vector<TimeSegmentMessage> getListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment);

        //void printListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment);

        void printShelfSegments();

        //!!! Später für Füllen der Regale mit Containern bestimmter Prioritäten nutzen!!!
        void fillBasedOnFastestToReachSegments(int value);
    };
}

#endif //NUPPROJECT_INVENTORY_H
