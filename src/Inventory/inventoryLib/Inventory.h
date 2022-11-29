//
// Created by Kim Simoski on 19.11.2022.
//

#ifndef NUPPROJECT_INVENTORY_H
#define NUPPROJECT_INVENTORY_H

# include "ShelfPair.h"

namespace inventoryLib {
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
        /*
        int rowsPerShelf;
        int segmentsPerRow;
        */

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

        Inventory(double conveyorBeltVelocity, unsigned int numberOfShelfPairs, unsigned long long int rowsPerShelf,
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
        static int getShelfPairNumberByShelfNumber(unsigned int shelfNumber);

        void setSegment(unsigned int shelfNumber, unsigned long long int row, unsigned long long int column, int value);

        // methods
        //!!! Dafür benötigte Zeiten für Fahrt zwischen den Regalpaaren zu den benötigten Zeiten innerhalb der Regalpaare addieren und dann den Weg mit kürzester benötigter Gesamtzeit wählen!!! Dabei Regaltiefen berücksichtigen!
        // getFastestToReachEmptyContainer() //!!! Rückgabewert: set/Tuple benötigte Zeit und Daten zum Segment (Regalpaar, Regal-Nummer, Segment-Nummer). Mit den Daten zum Segment übernimmt eine separate Methode den Weg Einlagerung
        // getNextContainerOfProductKindWithSpace()
        // getWayToNextMatchingContainer()
        // getNeededTimeForWayToNextMatchingContainer() // !!! Dafür Geschwindigkeiten und Beschleunigungen der Bediengeräte berücksichtigen !!!

    public:
        //addToInventory(ItemKind item);

        //!!! Methode und Zusammenhängende auf für Prioritäten reservierte Bereiche anpassen und das aktuelle Segment hier auslesen (Allerdings muss für die Einlagerung die Bedienhilfe am Ausgangspunkt sein. Dafür müssten dann auch die Dauern für Rückfahrten der Bedienhilfen vom vorherigen (Ziel)Segment bestimmt werden. Die Strecke des vorher wartenden Containers wird also immer doppelt gefahren. Dazu kommt noch, dass ggf. auf gleichem Weg noch eine Auslieferung getätigt wird.) !!!
        //!!! Wo wird das aktuelle Segment gespeichert und wo ist dessen Abfrage relevant ??? !!!
        TimeSegmentMessage getFastestToReachEmptyContainer(const SegmentDataMessage& currentSegment); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        //!!! For Debugging!!!
        std::vector<TimeSegmentMessage> getListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment);
        void printListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment);

        void printShelfSegments();

        //!!! Später für Füllen der Regale mit Containern bestimmter Prioritäten nutzen!!!
        void fillBasedOnFastestToReachSegments(int value);

    };
}

#endif //NUPPROJECT_INVENTORY_H
