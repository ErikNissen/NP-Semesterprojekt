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
Inventory::Inventory(unsigned int percentageOfPriorityA, unsigned int percentageOfPriorityB, unsigned int percentageOfPriorityC, const double conveyorBeltVelocity, const unsigned int numberOfShelfPairs, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow, const double verticalMaxVelocityInMetersPerSecond, const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond, const double horizontalAccelerationInMetersPerSquareSeconds, const double distanceBetweenShelfPairs, const double shelfWidthInMeters, const double shelfHeightInMeters, const double shelfDepthInMeters, const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters, const double distanceBetweenSegmentsInMeters, const double segmentWidthInMeters, const double segmentHeightInMeters, const double segmentDepthInMeters, const double containerWidthInMeters, const double containerHeightInMeters, const double containerDepthInMeters){
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


    this->rowsPerShelf = rowsPerShelf;
    this->segmentsPerRow = segmentsPerRow;

    this->percentageOfPriorityA = percentageOfPriorityA;
    this->percentageOfPriorityB = percentageOfPriorityB;
    this->percentageOfPriorityC = percentageOfPriorityC;

    /*
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

    //!!! Folgende Zeile wirft noch einen Speicherverwaltungsfehler aus (exit code -1073741819)
    setSegmentPrioritiesBasedOnFastestToReachSegmentsAndPrioPercentages();
}

// getters and setters
//!!! Besser auf Methode abstützen, die aus der ShelfNumber die ShelfPairNumber berechnet!!!
ShelfPair& Inventory::getShelfPairByShelfNumber(const unsigned int shelfNumber) {
    return shelfPairs.at(getShelfPairNumberByShelfNumber(shelfNumber)-1); // the list of shelf pairs starts at 0 but with the member shelfPairNumber = 1
}

unsigned int Inventory::getShelfPairNumberByShelfNumber(const unsigned int shelfNumber) {
    return std::ceil(static_cast<double>(shelfNumber)/2);
}


// methods
    void Inventory::setSegmentPrioritiesBasedOnFastestToReachSegmentsAndPrioPercentages(){
        unsigned int totalAmountOfShelfSegments{amountOfShelves * static_cast<unsigned int>(rowsPerShelf) * static_cast<unsigned int> (segmentsPerRow)};
        //!!! Prio-Handhabe ggf. komplett auf Maps oder Liste umstellen und durch Liste iterieren,anstatt alle Werte einzeln zu beziehen!!!
        unsigned int amountOfSegmentsReservedForPrioA{percentageOfPriorityA * totalAmountOfShelfSegments / 100};
        unsigned int amountOfSegmentsReservedForPrioB{percentageOfPriorityB * totalAmountOfShelfSegments / 100};
        unsigned int amountOfSegmentsReservedForPrioC{percentageOfPriorityC * totalAmountOfShelfSegments / 100};

        /*
        unsigned int amountOfSegmentsReservedForPrioA{static_cast<unsigned int> (std::round(static_cast<double>(percentageOfPriorityA)/100 * totalAmountOfShelfSegments))};
        unsigned int amountOfSegmentsReservedForPrioB{static_cast<unsigned int> (std::round(static_cast<double>(percentageOfPriorityB)/100 * totalAmountOfShelfSegments))};
        unsigned int amountOfSegmentsReservedForPrioC{static_cast<unsigned int> (std::round(static_cast<double>(percentageOfPriorityC)/100 * totalAmountOfShelfSegments))};
        */

        //!!! Stattdessen Liste aller Bestandteile machen und hier mithilfe von Mapping über alle iterieren. Alternativ Deklarationsschleife als Methode auslagern und da Parameter reinstecken !!!
        // priorityA
        initiateContainerPriorities(amountOfSegmentsReservedForPrioA, Priority::A);

        // priorityB
        initiateContainerPriorities(amountOfSegmentsReservedForPrioB, Priority::B);

        // priorityC
        initiateContainerPriorities(amountOfSegmentsReservedForPrioC, Priority::C);

        //!!! FOR DEBUGGING
        std::cout << "Prios have been reserved for Containers in Segments." << std::endl;
    }

//!!! Diese Methode berechnet den Weg vom ersten Einlagerungseinstellplatz über das Laufband bis zum jeweiligen Einlagerungseinstellplatz mit ein, aber beachtet dessen Warteschlange mit den jeweiligen Wartezeiten noch nicht. !!!
//!!! Analoge Methode ergänzen, die separat die Zeiten für die Einlagerung kennt. Dann könnten die für das Log gleich mitgegeben und für den Countdown an den Wartestationen. Ggf. aber auch woanders implementieren. Aber jeweils nur für das Zielsegment des insgesamt kürzesten Weges!!!
//!!! Beachtet noch nicht die jeweils aktuelle Position oder die Interaktion mit Ausgabeprozessen !!!
std::optional<TimeSegmentMessage> Inventory::getFastestToReachContainerBasedOnUse(const SegmentUse& containerUse, const Item& item) {

    double shortestTimeInSeconds {-1};
    //TimeSegmentMessage* segmentWithFastestWay{nullptr}; //!!! Pointer-Workaround umgehen

    std::optional<TimeSegmentMessage> segmentWithFastestWay;

    for(ShelfPair shelfPair: shelfPairs){
        //!!! Bezeichner kürzen!!!
        auto fastestToReachSegmentOfShelfPair{shelfPair.getFastestToReachContainerBasedOnUse(containerUse, item)};

        if(fastestToReachSegmentOfShelfPair) {
            double neededTimeForReachingSegmentFromInputWaitingPlaceInSeconds{
                    fastestToReachSegmentOfShelfPair->getNeededTimeWithoutWaitingInQueueInSeconds()};
            double neededTimeForReachingPairFromFirstPairsViaConveyorBeltInSeconds{
                    calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(shelfPair.getShelfPairNumber())};
            double neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds{
                    neededTimeForReachingSegmentFromInputWaitingPlaceInSeconds +
                    neededTimeForReachingPairFromFirstPairsViaConveyorBeltInSeconds};

            if (shortestTimeInSeconds < 0 ||
                neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds < shortestTimeInSeconds) {
                shortestTimeInSeconds = neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds;
                segmentWithFastestWay = std::optional<TimeSegmentMessage>{{
                        neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds,
                        fastestToReachSegmentOfShelfPair->getSegmentDataMessage()}};
            }
        }
    }
    if (segmentWithFastestWay){
        return segmentWithFastestWay;
    }
    else{
        throw std::out_of_range("Cannot find empty space. All shelves are full.");
    }
}


//!!! Zugriffsweg auf distanceBetweenShelvesOfPair und shelfDepthInMeters überdenken!!!
//!!! Methodenbezeichner kürzen !!!
//!!! Für Debugging public gemacht. Hinterher wieder private machen !!!
double Inventory::calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(const int unsigned shelfPairNumber) {
    return static_cast<double>(shelfPairNumber - 1) * (shelfPairs.at(0).getDistanceBetweenShelvesOfPair() + 2 * shelfPairs[0].getShelfDepthInMeters())/conveyorBeltVelocity;
}

//!!! So abwandeln, dass die Liste aus dem jeweils besten Wert pro Regalpaar ohne Zeiten der Warteschlangen in einer Liste ausgegeben werden. Allerdings müssen Abfragen für Reservierungen und Umsetzung der Reservierung gleichzeitig passieren (MUTEX), damit es nicht zu Fehlverrechnungen kommt!!!
/*
std::vector<TimeSegmentMessage> Inventory::getListOfFastestToReachContainersByUseWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment) {
    std::vector<TimeSegmentMessage> listOfFastestToReachEmptyContainersForAllPairs{};
    for(ShelfPair& shelfPair: shelfPairs){
        listOfFastestToReachEmptyContainersForAllPairs.emplace_back(shelfPair.getFastestToReachEmptyContainer(currentSegment));
    }
    return listOfFastestToReachEmptyContainersForAllPairs;
}
*/


/*
void Inventory::printListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(const SegmentDataMessage& currentSegment) {
    auto listOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs{getListOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs(currentSegment)};
    for(auto fastestToReachEmptyContainersForShelfPair: listOfFastestToReachEmptyContainersWithoutConveyorBeltForAllShelfPairs){
        fastestToReachEmptyContainersForShelfPair.print();
    }
}*/

//!!! Methoden zum Setzen der Prioritäten private machen!!!
void Inventory::setSegmentsPriority(const SegmentDataMessage& segmentDataMessage,
                                    const itemLib::Priority &priority) {
    //!!! FOR DEBUGGING !!!
    auto num{segmentDataMessage.getShelfNumber()};
    auto row{segmentDataMessage.getRow()};
    auto seg{segmentDataMessage.getColumn()};
    setSegmentsPriority(num, row, seg, priority);

    //setSegmentsPriority(segmentDataMessage.getShelfNumber(), segmentDataMessage.getRow(), segmentDataMessage.getColumn(), priority);
    }

void Inventory::setSegmentsPriority(const unsigned int shelfNumber, const unsigned long long int row, const unsigned long long int column,
                                    const Priority& priority) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(shelfNumber)};
    shelfPair.setSegmentsPriority(shelfNumber, row, column, priority);
}


void Inventory::initiateContainerPriorities(const unsigned int amountOfSegmentsReservedForPrio, const Priority& priority) {
    for (unsigned int i{0}; i < amountOfSegmentsReservedForPrio; i++) {
        auto fastestToReachEmptyContainer{getFastestToReachContainerWithoutSetPriority()->getSegmentDataMessage()};
        setSegmentsPriority(fastestToReachEmptyContainer, priority);
    }
}


std::optional<TimeSegmentMessage>
Inventory::getFastestToReachContainerWithoutSetPriority() {
    return Inventory::getFastestToReachContainerBasedOnUse(SegmentUse::InitPrio, {});
}

std::optional<TimeSegmentMessage>
Inventory::getFastestToReachSegmentForContainerInput(const Container& container) {
    return Inventory::getFastestToReachContainerBasedOnUse(SegmentUse::AddContainerToSegment, container.getItem());
}


std::optional<TimeSegmentMessage>
Inventory::getFastestToReachContainerForItemInput(const Item& item) {
    return getFastestToReachContainerBasedOnUse(SegmentUse::AddItemToContainer, item);
}

std::optional<TimeSegmentMessage>
Inventory::getFastestToReachContainerForItemOutput(const Item& item) {
    return getFastestToReachContainerBasedOnUse(SegmentUse::GetItemFromContainer, item);
}


//ToDO: Segmente müssen reserviert werden für: Ausgabe des Containers zum Befüllen, Ausgabe des Containers zum Herausnehmen, Einfügen des Containers in ein Segment

std::optional<TimeSegmentMessage> Inventory::reserveContainerToAddToInventory(const Container& container) {
    auto fastestToReachContainer{getFastestToReachSegmentForContainerInput(container)};
    if(fastestToReachContainer) {
        reserveSegmentToAddContainer(fastestToReachContainer->getSegmentDataMessage());
    }
    return fastestToReachContainer;
}

//ToDO: Im besten Fall diese Methode erst beim Punkt aufrufen, der das Laufband mit ansteuert und dafür noch eine Ebene aufrufen, die das schnellste zu erreichende Segment unter Berücksichtung der Warteschlangen berechnet
//!!! Die Methoden zum Reservieren evtl. so anpassen, dass noch vor dem Aufruf die aktuellen Wartezeiten in den Schlangen berücksichtigt werden können, was so direkt nicht der Fall ist. Aber zwischen Abfrage der Liste und Reservierung darf keine Zeit liegen. Dann müsste ggf. das Laufband beides gleichzeitig in einer Methode machen, die ein Mutex ist !!!
std::optional<TimeSegmentMessage> Inventory::reserveContainerOutputFromInventoryToGetItems(const Item& item) {
    auto fastestToReachContainer{getFastestToReachContainerForItemOutput(item)};
    if(fastestToReachContainer) {
        reserveSegmentToGetContainer(fastestToReachContainer->getSegmentDataMessage());
    }
    return fastestToReachContainer;
}

//ToDO: Im besten Fall diese Methode erst beim Punkt aufrufen, der das Laufband mit ansteuert und dafür noch eine Ebene aufrufen, die das schnellste zu erreichende Segment unter Berücksichtung der Warteschlangen berechnet
//!!! Die Methoden zum Reservieren evtl. so anpassen, dass noch vor dem Aufruf die aktuellen Wartezeiten in den Schlangen berücksichtigt werden können, was so direkt nicht der Fall ist. Aber zwischen Abfrage der Liste und Reservierung darf keine Zeit liegen. Dann müsste ggf. das Laufband beides gleichzeitig in einer Methode machen, die ein Mutex ist !!!
std::optional<TimeSegmentMessage> Inventory::reserveContainerOutputFromInventoryToAddItems(const Item& item) {
    auto fastestToReachContainer{getFastestToReachContainerForItemInput(item)};
    if(fastestToReachContainer) {
        reserveSegmentToGetContainer(fastestToReachContainer->getSegmentDataMessage());
    }
    return fastestToReachContainer;
}

//!!! the selection process of the fastest to reach matching shelf segment and the reservation (this method) have to be called simultaneously
void Inventory::reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    shelfPair.reserveSegmentToAddContainer(goalSegment);
}

//!!! the selection process in of the fastest to reach matching shelf segment and the reservation (this method) have to be called simultaneously
void Inventory::reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    shelfPair.reserveSegmentToGetContainer(goalSegment);
}

//!!! for getting called after waiting at a shelfPairs input waiting point
void Inventory::addContainer(const SegmentDataMessage &goalSegment, const Container &newContainer) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    shelfPair.addContainer(goalSegment, newContainer);
}

//!!! for getting called after waiting at a shelfPairs input waiting point
Container Inventory::takeContainer(const SegmentDataMessage &goalSegment) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    return shelfPair.takeContainer(goalSegment);
}



void Inventory::printShelfSegments() {
    std::cout << "!! All shelf segments: " << std::endl;
    for(auto shelfPair:shelfPairs){
        shelfPair.printAllShelfSegments();
    }
}

/*
std::optional<TimeSegmentMessage> Inventory::getFastestToReachContainerWithoutSetPriority() {
    return getFastestToReachContainerWithoutSetPriority();
}*/


/*
std::optional<TimeSegmentMessage> Inventory::getFastestToReachSegmentForContainerInput(const Container& container) {
    return getFastestToReachSegmentForContainerInput(container);
}*/

/*
std::optional<TimeSegmentMessage> Inventory::getFastestToReachContainerForItemInput(const Item &item) {
    return getFastestToReachContainerForItemInput(item);
}
 */

/*
std::optional<TimeSegmentMessage> Inventory::getFastestToReachContainerForItemOutput(const Item &item) {
    return getFastestToReachContainerForItemOutput(item);
}
 */

/*
std::optional<TimeSegmentMessage>
Inventory::getFastestToReachContainerBasedOnUse(const SegmentUse &containerUse, const Item &item) {
    return getFastestToReachContainerBasedOnUse(containerUse, item);
}*/


















