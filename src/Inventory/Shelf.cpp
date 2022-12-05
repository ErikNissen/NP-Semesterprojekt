//
// Created by Kim Simoski on 19.11.2022.
//

#include "Shelf.h"
#include "../Messages/TimeSegmentMessage.h"
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <optional>


using namespace inventoryLib;
// constructors
//!!! Konstruktor für Initialisierung aus Persistenten Daten mit komplettem Datensatz erstellen und von Inventar durch entsprechende Konstruktoren durchreichen, die aus einer JSON lesen !!!

/*Shelf::Shelf(const unsigned long long int rows, const unsigned long long int columns) {     // Constructor
    matrix = {rows, std::vector<int>(columns)};
}*/

Shelf::Shelf(const unsigned int shelfNumber, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow,
             const double verticalMaxVelocityInMetersPerSecond, const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond, const double horizontalAccelerationInMetersPerSquareSeconds,
             const double shelfWidthInMeters, const double shelfHeightInMeters, const double shelfDepthInMeters,
             const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters, const double distanceBetweenSegmentsInMeters,
             const double segmentWidthInMeters, const double segmentHeightInMeters, const double segmentDepthInMeters, const double containerWidthInMeters, const double containerHeightInMeters,
             const double containerDepthInMeters){

    this->shelfNumber = shelfNumber;

    // initiate shelf
    //!!! Bezeichner überdenken !!!

    //!!! Muss eigenen Vector erstellen. Die Üblichen können nur Standard-Datentypen beinhalten!!! Alternativ einen Vector of Pointer (unique oder shared. Eher unique)
    // https://www.geeksforgeeks.org/program-to-create-custom-vector-class-in-c/
    // https://www.programiz.com/cpp-programming/vectors
    matrix = {rowsPerShelf, std::vector<std::shared_ptr<ShelfContainer>>{segmentsPerRow, std::make_shared<ShelfContainer>(ShelfContainer{Priority::N})}}; // sets a matrix with a set size and Containers with default priority N which means no valid priority level

    // counts
    this->rowsPerShelf = rowsPerShelf;
    this->segmentsPerRow = segmentsPerRow;

    // measurements
    this->verticalMaxVelocityInMetersPerSecond = verticalMaxVelocityInMetersPerSecond;
    this->verticalAccelerationInMetersPerSquareSeconds = verticalAccelerationInMetersPerSquareSeconds;

    this->horizontalMaxVelocityInMetersPerSecond = horizontalMaxVelocityInMetersPerSecond ;
    this->horizontalAccelerationInMetersPerSquareSeconds = horizontalAccelerationInMetersPerSquareSeconds;

    //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!

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
}

// getters and setters
double Shelf::getShelfDepthInMeters() const{
    return shelfDepthInMeters;
}

unsigned int Shelf::getShelfNumber() const {
    return shelfNumber;
}


// methods
/*void Shelf::printShelfSegments() {
    std::cout << "Shelf number: " << shelfNumber << std::endl;
    for (auto &row: matrix) {
        for (auto &col: row) {
            //col.print();
            std::cout << col << " ";
        }
        std::cout<<std::endl;
    }
}*/

void Shelf::printShelfSegments() {
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "--[Shelf number: " << shelfNumber << "]--------------------------------------" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    for(unsigned long long i{0}; i < rowsPerShelf; ++i)
    {
        for(unsigned int j {0}; j < segmentsPerRow; ++j)
        {
            std::cout << "Row: " << i << "; " << "Segment: " << j << ":" << std::endl;
            matrix[i][j]->print();
        }
    }

}


//!!! Methoden zum Umrechnen mit physikalischen Größen evtl. in eine extra Klasse als Service auslagern !!!
// https://www.johannes-strommer.com/formeln/weg-geschwindigkeit-beschleunigung-zeit/
double Shelf::calculateTimeInSecondsFromWayInMeters(const double wayInMeters, const double maxVelocityInMetersPerSecond,
                                                   const double accelerationInMetersPerSquareSeconds) {
    double wayNeededForReachingMaxVelocityInMeters = maxVelocityInMetersPerSecond*maxVelocityInMetersPerSecond/(2 * accelerationInMetersPerSquareSeconds);

    // https://www.johannes-strommer.com/formeln/weg-geschwindigkeit-beschleunigung-zeit/
    // the reference is two times the way needed for accelerating up to the max velocity because the same way is needed for stopping the vehicle
    if(wayInMeters > 2 * wayNeededForReachingMaxVelocityInMeters){
        return maxVelocityInMetersPerSecond / accelerationInMetersPerSquareSeconds + wayInMeters / maxVelocityInMetersPerSecond;
    }
    else if(wayInMeters == 2 * wayNeededForReachingMaxVelocityInMeters){
        return 2 * maxVelocityInMetersPerSecond / accelerationInMetersPerSquareSeconds;
    }
    else{ //case: wayInMeters < wayNeededForReachingMaxVelocityInMeters
        return 2 * std::sqrt(wayInMeters/accelerationInMetersPerSquareSeconds);
    }
}

/*
std::vector<SegmentDataMessage> Shelf::getListOfFreeContainers() { //!!! Hier noch später Reservierung für Warenprioritäten berücksichtigen!!!
    std::vector<SegmentDataMessage> listOfEmptyContainers;
    for(unsigned long long i{0} ; i < rowsPerShelf; i++)
    {
        for(unsigned long long j{0}; j < segmentsPerRow; j++)
        {
            //if(matrix.at(i).at(j).isEmpty()) {
            if(matrix.at(i).at(j)->isEmpty()) {
                listOfEmptyContainers.emplace_back(shelfNumber, i, j);
            }
        }
    }
    return listOfEmptyContainers;
}
*/

//!!! Hier TransferMessage als weiteres Argument einfügen und in entsprechenden Methoden von ShelfContainer, um direkt zu gucken, welcher Container aktuell zum Item und der Anzahl passt !!!
std::vector<SegmentDataMessage> Shelf::getListOfContainersBasedOnUse(const ContainerUse& containerUse, const TransferMessage &transferMessage) { //!!! Hier noch später Reservierung für Warenprioritäten berücksichtigen!!!
    std::vector<SegmentDataMessage> listOfEmptyContainers;
    for(unsigned long long i{0} ; i < rowsPerShelf; i++)
    {
        for(unsigned long long j{0}; j < segmentsPerRow; j++)
        {

            switch(containerUse)
            {
                case ContainerUse::InitPrio:
                    if(matrix.at(i).at(j)->hasNoPriorityLevel()) {
                        listOfEmptyContainers.emplace_back(shelfNumber, i, j);
                    }
                    break;

                case ContainerUse::Add:
                    if(matrix.at(i).at(j)->containsPlaceForAmountToAddOfThisItem(transferMessage)) {
                        listOfEmptyContainers.emplace_back(shelfNumber, i, j);
                    }
                    break;

                case ContainerUse::Get:
                    if(matrix.at(i).at(j)->containsAmountToGetOfThisItem(transferMessage)) {
                        listOfEmptyContainers.emplace_back(shelfNumber, i, j);
                    }
                    break;

                default:
                    break;
            }
        }
    }
    return listOfEmptyContainers;
}


double Shelf::calculateWayTimeToSegmentInSeconds(const SegmentDataMessage& currentSegment, const SegmentDataMessage& goalSegment) {

    int horizontalArrayIndicesDifference{calculateHorizontalArrayIndicesDifference(currentSegment, goalSegment)};
    int verticalArrayIndicesDifference{calculateVerticalArrayIndicesDifference(currentSegment, goalSegment)};

    double horizontalWayInMeters{calculateHorizontalWayFromArrayIndicesDifference(horizontalArrayIndicesDifference)};
    double verticalWayInMeters{calculateVerticalWayFromArrayIndicesDifference(verticalArrayIndicesDifference)};

    double timeNeededForHorizontalWayInSeconds{calculateTimeNeededForHorizontalWayInSeconds(horizontalWayInMeters)};
    double timeNeededForVerticalWayInSeconds{calculateTimeNeededForVerticalWayInSeconds(verticalWayInMeters)};

    return std::max(timeNeededForHorizontalWayInSeconds, timeNeededForVerticalWayInSeconds); // the whole waytime is determined by the slower direction if both happen to run parallel
}

double Shelf::calculateHorizontalWayFromArrayIndicesDifference(const int arrayIndicesDifference) const {
    return arrayIndicesDifference * (distanceBetweenSegmentsInMeters + segmentWidthInMeters);
}

double Shelf::calculateVerticalWayFromArrayIndicesDifference(const int arrayIndicesDifference) const {
    return arrayIndicesDifference * (segmentHeightInMeters); //!!! Hier muss ggf. noch die Bodenhöhe ergänzt werden !!!
}

//!!! Folgende beiden Methode in einer Aufrufen, die Start-und Ziel-Koordinaten kennt und jeweils die Differenz in y und in x-Richtung als Argument übergibt. Dabei ggf. Extraweg bis Ausgabestelle beachten und darauf, dass nicht zwingend immer vom Startpunkt gefahren wird!!!


//!!! Für Nutzung der Methode für Initialisierung ist es aber vom Startpunkt des Regals richtig !!!
int Shelf::calculateHorizontalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment){
    return std::abs(static_cast<int>(currentSegmentOfThisShelfPair.getColumn()) - static_cast<int>(goalSegment.getColumn()));
    //return std::abs(goalSegment.getColumn() - 0);
}

//!!! Später currentSegementOfThisShelf implementieren und berücksichtigen, um nicht jedes Mal vom Ausgangspunkt zu rechnen. Für Nutzung der Methode für Initialisierung ist es aber vom Startpunkt des Regals richtig!!!
int Shelf::calculateVerticalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment){
    //return std::abs(goalSegment.getRow() - 0);
    return std::abs(static_cast<int>(currentSegmentOfThisShelfPair.getRow()) - static_cast<int>(goalSegment.getRow()));
}

//!!! Methoden für Auslagerung und Einlagerung überlagern, um zusätzliche Strecke zu berücksichtigen!!!
double Shelf::calculateTimeNeededForHorizontalWayInSeconds(const double wayInMeters) {
       return calculateTimeInSecondsFromWayInMeters(wayInMeters, horizontalMaxVelocityInMetersPerSecond,
                                                    horizontalAccelerationInMetersPerSquareSeconds);
}

double Shelf::calculateTimeNeededForVerticalWayInSeconds(const double wayInMeters) {
    return calculateTimeInSecondsFromWayInMeters(wayInMeters, verticalMaxVelocityInMetersPerSecond,
                                                 verticalAccelerationInMetersPerSquareSeconds);
}

/*
    TimeSegmentMessage Shelf::getFastestToReachContainerBasedOnUse(const SegmentDataMessage &currentSegment,
                                                                   const ContainerUse &containerUse, const TransferMessage &transferMessage) {
        std::vector<SegmentDataMessage> listOfMatchingContainersForUse{getListOfContainersBasedOnUse(containerUse, transferMessage)};

        if(!listOfMatchingContainersForUse.empty()){
            std::vector<TimeSegmentMessage> listOfTimeSegmentMessages{};

            // add the needed way times to the segments and save new message in new list
            for(SegmentDataMessage goalsSegmentDataMessage:listOfMatchingContainersForUse){
                double timeNeededForWayInSeconds{calculateWayTimeToSegmentInSeconds(currentSegment, goalsSegmentDataMessage)};
                listOfTimeSegmentMessages.emplace_back(timeNeededForWayInSeconds, goalsSegmentDataMessage);
            }

            //if(!listOfTimeSegmentMessages.empty()){
            TimeSegmentMessage segmentWithFastestWay;
            segmentWithFastestWay = *std::min_element(listOfTimeSegmentMessages.begin(), listOfTimeSegmentMessages.end(),
                                                  compareTwoElements);
            return segmentWithFastestWay;
        }
        else
        { //!!!Hier Exception werfen oder mit optional artbbeiten, falls TimeSegmentMessage* ein leer ist???
            //!!! https://en.cppreference.com/w/cpp/utility/optional !!!
            //!!! Wenn kein Container zur Verfügung steht, würde über den Weg versucht werden, ein Container einfach zu überschreiben, der dann 10000 Sekunden als Anlaufzeit versuchen würde zu nehmen
            //!!! Wenn man hier aber eine Exception wirft, aber in einem anderen Regal noch Platz ist, wird das Programm fälschlicherweise abgebrochen !!!
            return {TimeSegmentMessage(10000, currentSegment)}; //!!! Seeeehr schlechter Workaroud, um nicht nichts zurückzugeben!!!
        }
    }
    */

//!!! Berücksichtigt noch nicht, dass Eingabe und Ausgabe unterschiedliche Höhen und damit unterschiedliche Strecken haben!!!
std::optional<TimeSegmentMessage> Shelf::getFastestToReachContainerBasedOnUse(const SegmentDataMessage &currentSegment,
                                                               const ContainerUse &containerUse, const TransferMessage &transferMessage) {
    std::vector<SegmentDataMessage> listOfMatchingContainersForUse{getListOfContainersBasedOnUse(containerUse, transferMessage)};

    if(!listOfMatchingContainersForUse.empty()){
        std::vector<TimeSegmentMessage> listOfTimeSegmentMessages{};

        // add the needed way times to the segments and save new message in new list
        for(SegmentDataMessage goalsSegmentDataMessage:listOfMatchingContainersForUse){
            double timeNeededForWayInSeconds{calculateWayTimeToSegmentInSeconds(currentSegment, goalsSegmentDataMessage)};
            listOfTimeSegmentMessages.emplace_back(timeNeededForWayInSeconds, goalsSegmentDataMessage);
        }

        TimeSegmentMessage segmentWithFastestWay;
        segmentWithFastestWay = *std::min_element(listOfTimeSegmentMessages.begin(), listOfTimeSegmentMessages.end(),
                                                  compareTwoElements);
        return segmentWithFastestWay;
    }
    else{//!!! https://en.cppreference.com/w/cpp/utility/optional !!! // if no value is returned, optional contains an empty value which tranlates to a false bool value
    return {};
    }
}


/*
TimeSegmentMessage Shelf::getFastestToReachEmptyContainer(const SegmentDataMessage& currentSegment) {
    std::vector<SegmentDataMessage> listOfFreeContainers{getListOfFreeContainers()};
    std::vector<TimeSegmentMessage> listOfTimeSegmentMessages{};

    // add the needed way times to the segments and save new message in new list
    for(SegmentDataMessage goalsSegmentDataMessage:listOfFreeContainers){
        double timeNeededForWayInSeconds{calculateWayTimeToSegmentInSeconds(currentSegment, goalsSegmentDataMessage)};
        listOfTimeSegmentMessages.emplace_back(timeNeededForWayInSeconds, goalsSegmentDataMessage);
    }

    //if(!listOfTimeSegmentMessages.empty()){
        TimeSegmentMessage segmentWithFastestWay;
        segmentWithFastestWay = *std::min_element(listOfTimeSegmentMessages.begin(), listOfTimeSegmentMessages.end(),
                                                  compareTwoElements);
        return segmentWithFastestWay; //!!!Hier Exception werfen, falls TimeSegmentMessage* ein leer ist???
 }
 */

bool Shelf::compareTwoElements(const TimeSegmentMessage& leftElement, const TimeSegmentMessage& rightElement){
    return (leftElement.getNeededTimeWithoutWaitingInQueueInSeconds() < rightElement.getNeededTimeWithoutWaitingInQueueInSeconds());
}




/*
//!!! Performances überprüfen und nur diese Methode oder die darüber nutzen!
TimeSegmentMessage Shelf::getFastestToReachEmptyContainerAlt(const SegmentDataMessage& currentSegment) {
    std::vector<SegmentDataMessage> listOfFreeContainers{getListOfFreeContainers()};

    double shortestTimeInSeconds {-1}; //!!! Workaround, brächte aber Fehler, wenn kein freies Segment gefunden wird!!!

    TimeSegmentMessage* segmentWithFastestWay; //!!! Pointer-Handhabe überarbeiten zu neueren Cpp-Standards !!!

    for(SegmentDataMessage segmentDataMessage:listOfFreeContainers){
        double timeNeededForWayInSeconds{calculateWayTimeToSegmentInSeconds(currentSegment, segmentDataMessage)};

        if(shortestTimeInSeconds < 0 || timeNeededForWayInSeconds < shortestTimeInSeconds){
            shortestTimeInSeconds = timeNeededForWayInSeconds;
            *segmentWithFastestWay  = {shortestTimeInSeconds, segmentDataMessage};
        }
    }
    return *segmentWithFastestWay; //!!! Fehler werfen oder null_ptr zurückgeben und an aufrufenden Stellen auf null_ptr abfragen, falls kein Element gefunden wird und die Liste ergo leer ist
}
 */

//!!! Setzt die Priorität irgendwie für die komplette Matrix auf einmal !!!
void Shelf::setSegmentsPriority(const unsigned long long int row, const unsigned long long int column, const Priority& priority) {
    matrix.at(row).at(column)->setPriority(priority); // Zuweisung wird irgendwie nicht umgesetzt, obwohl debugging bis hier kommt!
    //matrix[row][column]->setPriority(priority); // Zuweisung wird irgendwie nicht umgesetzt, obwohl debugging bis hier kommt!
}

/*
std::vector<SegmentDataMessage> Shelf::getListOfFreeContainersWithoutPriority() {

    return std::vector<SegmentDataMessage>();
}*/

















