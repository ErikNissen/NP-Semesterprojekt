//
// Created by Kim Simoski on 19.11.2022.
//

#include <iostream>
#include <vector>
#include <memory>
#include "../Messages/SegmentDataMessage.h"
#include "../Messages/TimeSegmentMessage.h"
#include "ShelfContainer.h"
#include "ContainerUse.h"

#ifndef NUPPROJECT_SHELF_H
#define NUPPROJECT_SHELF_H

using namespace messagesLib;
//using namespace Inventory;
//using namespace Item;

namespace inventoryLib {
    //!!! Im Fall von Pointer-Gebrauch diesen zu modernerem Pointer umändern!!!
    //!!! Funktioniert noch nicht mit Waren bzw. Containern mit Waren, fügt noch nichts hinzu, holt noch nichts und reserviert noch keine Bereiche anhand der Prioriäten !!!
class Shelf {

        // attributes
    private:
        // https://riptutorial.com/cplusplus/example/17463/matrices-using-vectors
        // https://iamsorush.com/posts/shared-pointer-cpp/
        //!!! Evtl. von shared_pointer zu unique_pointer wechseln und dafür Move-Konstruktor für Container-Klasse schreiben
        std::vector<std::vector<std::shared_ptr<ShelfContainer>>> matrix;
        //std::vector<std::vector<int>> matrix;

        //!!! Log-Data bzw. Daten zum Berechnen entweder nur hier initialisieren, oder in extra Klasse, die zum Verrechnen genutzt wird oder in Inventar oder zusammengesetzt jeweils ergänzend in umklammernder Klasse, mit jeweils objektorientierter Zuteilung !!!
        // log_data

        unsigned int shelfNumber; // beginning with 1

        // counts
        unsigned long long rowsPerShelf;
        unsigned long long segmentsPerRow;


        // measurements

        //!!! Wenn man Velocity und Acceleration als Regaleigentschaft deklariert, macht man die Bedienhilfen abstrahiert zu einer Regaleigenschaft. Da müsste man dann darauf achten, dass in einem Regalpaar immer nur ein Regal gleichzeitig diese Eigenschaft nutzen kann und der aktuelle Index für alle einzelnen "Methoden", welche die Bedienhilfen widerspiegeln identisch sein muss.
        //!!! Für letzteres könnte aber der aktuelle Index aus Shelfpair als Argument in die Methoden übergeben werden, wenn diese Klasse sie aufruft. Das wäre aber eher prozedural als objektorientiert. !!!
        // transport vehicle
        double verticalMaxVelocityInMetersPerSecond;
        double verticalAccelerationInMetersPerSquareSeconds;

        double horizontalMaxVelocityInMetersPerSecond;
        double horizontalAccelerationInMetersPerSquareSeconds;

        //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!

        // inventory

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

        //!!! Container-Handhabe habe ich bisher aber nicht praktisch umgesetzt, weder mit Warentypen mit Priorisierung, noch mit Anzahlen oder Nutzung in den Regalfächern !!!
        // container
        double containerWidthInMeters;
        double containerHeightInMeters;
        double containerDepthInMeters;



        // constructors
    public:
        //!!! Konstruktor ergänzen, der anhand einer JSON Rand-Werte und Inhalte der Tabellen setzt!!!
        Shelf() = default; //!!! Maybe delete later if possible. Needed for Constructor initialisation in ShelfPair !!!
        //Shelf(unsigned long long int rows, unsigned long long int columns);
        Shelf(unsigned int shelfNumber, unsigned long long int rowsPerShelf, unsigned long long int segmentsPerRow,
              double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds,
              double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds,
              double shelfWidthInMeters, double shelfHeightInMeters, double shelfDepthInMeters,
              double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters,
              double distanceBetweenSegmentsInMeters,
              double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters,
              double containerWidthInMeters, double containerHeightInMeters,
              double containerDepthInMeters);

        // getters and setters
    public:
        [[nodiscard]] double getShelfDepthInMeters() const;
        [[nodiscard]] unsigned int getShelfNumber() const;
        void setSegmentsPriority(const unsigned long long int row, const unsigned long long int column, const Priority& priority);



        // methods
    private:
        // based on the vertical speed and vertical difference and horizontal speed and horizontal difference
        double calculateWayTimeToSegmentInSeconds(const SegmentDataMessage& currentSegment, const SegmentDataMessage& goalSegment);

        //double Shelf::calculateTimeInSecondsFromWayInMeters(const double wayInMetersHorizonzal, double wayInMetersVertical);
        //!!! Bezug der Parameter evtl. klassenintern gestalten, anstatt Parameter zu verwenden. Evtl. auch extra Klasse als Service erstellen, die sich um reale Werte und Berechnungen von Zeiten und Strecken kümmert, so dass die einzelnen Regale nur eine Liste an möglichen Positionen zurückgeben ergänzt um Infos zur Regalnummer/Ansteuerung !!!
        double calculateTimeInSecondsFromWayInMeters(double wayInMeters, double maxVelocityInMetersPerSecond,
                                                    double accelerationInMetersPerSquareSeconds);

        double calculateTimeNeededForHorizontalWayInSeconds(double wayInMeters);
        double calculateTimeNeededForVerticalWayInSeconds(double wayInMeters);




        //!!! Weg anhand des aktuellen Ortes der Bedienhilfe ermitteln, indem dieser Wert von ShelfPair übergeben wird
        [[nodiscard]] double calculateHorizontalWayFromArrayIndicesDifference(int arrayIndicesDifference) const;
        [[nodiscard]] double calculateVerticalWayFromArrayIndicesDifference(int arrayIndicesDifference) const;

        int calculateHorizontalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment);
        int calculateVerticalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment);

        bool static compareTwoElements(const TimeSegmentMessage& leftElement, const TimeSegmentMessage& rightElement);

    public:
        //!!! Später für Initialisierung mit leeren Containern drei verschiedener Prioritäten abändern!!!
        //void fillBasedOnFastestToReachSegments(int value);

        //!!! Für folgende Methoden nochmal überprüfen, wie Zerstückelung stattfindet, wenn nicht ganze Ladung in einen Container passt
        //!!! Für folgende Methoden aktuelle Position der Bedienhilfen berücksichtigen, falls diese gerade frei sind. Dies aber eher mit Überladung der Methode machen, weil die generelle Regalzeilung ja schon vor dem Warten an der Warteschlange gemacht wird.
        //!!! -> Wenn die Berechnungen soweit implementiert sind, dass auch die Wartezeiten in der Schlange im Voraus bekannt sind, Methoden noch einmal ergänzen !!!
        // getClosestContainerToAdd(ItemKind item, amount); //based on getNextContainerOfProductKindWithSpace(ItemKind item) and in case of no matching Container: getFastestToReachEmptyContainer()
        // getClosestContainerToRemove(ItemKind item, amount); //based on getNextContainerOfProductKindWithSpace(ItemKind item)

        // addToClosestContainer(ItemKind item);
        void printShelfSegments();

        //!!! Vernünftige Handhabe einführen, wenn das Regal keinen freien Container hat, ohne dass es den Aufruf von ShelfPair insgesamt blockiert, weil ja ein anderes Regal einen passenden Platz haben kann!!!
        std::vector<SegmentDataMessage> getListOfContainersBasedOnUse(const ContainerUse &containerUse, const TransferMessage &transferMessage);
        std::optional<TimeSegmentMessage> getFastestToReachContainerBasedOnUse(const SegmentDataMessage& currentSegment, const ContainerUse& containerUse, const TransferMessage &transferMessage);

        //TimeSegmentMessage getFastestToReachContainerBasedOnUse(const SegmentDataMessage& currentSegment, const ContainerUse& containerUse, const TransferMessage &transferMessage);
        //TimeSegmentMessage getFastestToReachEmptyContainer(const SegmentDataMessage& currentSegment);
        //TimeSegmentMessage getFastestToReachEmptyContainerAlt(const SegmentDataMessage& currentSegment);

        // getNextContainerOfProductKindWithSpace(const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference
        void setSegmentPrioritiesBasedOnFastestToReachSegments();


};
}

#endif //NUPPROJECT_SHELF_H
