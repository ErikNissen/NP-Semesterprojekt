//
// Created by Kim Simoski on 27.11.2022.
//

#include "Segment.h"


using namespace inventoryLib;

// constructors
Segment::Segment(){
    priority = Priority::N;
    //item = Item();
}

Segment::Segment(const Priority& priority) {
    this->priority = priority;
    //item = Item(priority);
}


// getters and setters


//ToDO: Durch bessere Methode ersetzen z.B. mit Unique-Pointer, so dass wirklich kein Container vorhanden ist und nicht solange ein leerer, bis einer eingestellt wird
bool Segment::containsContainer() {
    return !container.isEmpty();
}



//ToDO: Hier überdenken, ob die Rückgabe es eine Referenz oder ein Nullpointer werden soll. Letzteres würde den Konstruktor komplizierter machen
const Container &Segment::getContainer() const {
    return container;
}

//ToDO: Tendenziell nur privat nutzen oder hinterher löschen und stattdessen eine addContainer-Methode erstellen
void Segment::setContainer(const Container &newContainer) {
    container = newContainer;
}



Priority Segment::getPriority() const {
    return priority;
}

void Segment::setPriority(const Priority& newPriority) {
    if(hasNoPriorityLevel()) {
        priority = newPriority;
    }
    else{
        throw std::invalid_argument("A container with a valid priority level has been tried to reset mistakenly. Something went wrong.");
    }
}

bool Segment::isSegmentReservedForContainerOutput() const {
    return segmentReservedForContainerOutput;
}

bool Segment::isSegmentReservedForContainerInput() const {
    return segmentReservedForContainerInput;
}

void Segment::setSegmentReservedForContainerInput(bool newSegmentReservedForContainerInputState) {
    Segment::segmentReservedForContainerInput = newSegmentReservedForContainerInputState;
}

void Segment::setSegmentMarkedForContainerOutput(bool newSegmentMarkedForContainerOutputState) {
    Segment::segmentReservedForContainerOutput = newSegmentMarkedForContainerOutputState;
}


// methods


void Segment::deleteReservationFromSegmentToAddContainer() {
    setSegmentReservedForContainerInput(false);
}

void Segment::deleteReservationFromSegmentToGetContainer() {
    setSegmentMarkedForContainerOutput(false);
}

void Segment::reserveSegmentToAddContainer() {
    setSegmentReservedForContainerInput(true);
}

void Segment::reserveSegmentToGetContainer() {
    setSegmentMarkedForContainerOutput(true);
}

//ToDO: !!! hier noch Abfrage ergänzen, ob Prioritäten zusammenpassen !!!
//ToDO: Evtl. mit else if oder switch case verzweigen , falls throws beibehalten werden sollen.
void Segment::addContainer(const Container &newContainer) {
    if(!containsContainer()){
        if(isSegmentReservedForContainerInput()) {
            setContainer(newContainer);
            deleteReservationFromSegmentToAddContainer();
        }
        else{
            throw std::invalid_argument("A container has been tried to be added in a not reserved segment. Something went wrong.");
        }
    }
    else{
        throw std::invalid_argument("A container has been tried to be added in an occupied segment. Something went wrong.");
    }
}

//ToDo: Ausgabe und Leeren eleganter lösen (tendenziell mit unique-Pointer)!
Container Segment::takeContainer() {
    if(containsContainer()){
        if(isSegmentReservedForContainerOutput()) {
            auto returnContainer{container};
            container = Container(Item());
            deleteReservationFromSegmentToGetContainer();
            return returnContainer;
        }
        else{
            throw std::invalid_argument("A container has been tried to be taken in a not reserved segment. Something went wrong.");
        }
    }
    else{
        throw std::invalid_argument("A container has been tried to be added in an occupied segment. Something went wrong.");
    }
}


bool Segment::hasNoPriorityLevel() {
    return (priority == Priority::N);
}

bool Segment::hasMatchingPriorityLevel(Container& externalContainer) {
    return (priority == externalContainer.getItemsPriority());
}


bool Segment::containsAtLeastOnePieceOfThisItemToGet(const Item &item) {
    return container.containsAtLeastOnePieceOfThisItemToGet(item);
}

bool Segment::containsPlaceForAtLeastOnePieceOfThisItemToAdd(const Item &item) {
    return container.containsPlaceForAtLeastOnePieceOfThisItemToAdd(item);
}

void Segment::print() {
    std::cout << "********************************"<< std::endl;
    container.print();
    printPriority();
    /*
    std::cout << "current amount of item: " << currentAmountOfItem << std::endl;
    std::cout << "reserved to add amount: " << reservedToAddAmount << std::endl;
    std::cout << "reserved to get amount: " << reservedToGetAmount << std::endl;
    std::cout << "********************************"<< std::endl;
    */
}

// https://stackoverflow.com/questions/66488850/how-to-print-the-enum-value-from-its-index
void Segment::printPriority() {
    switch (this->priority) {
        case Priority::A:
            std::cout << "Container-Priority: A" << std::endl;
            break;
        case Priority::B:
            std::cout << "Container-Priority: B" << std::endl;
            break;
        case Priority::C:
            std::cout << "Container-Priority: C" << std::endl;
            break;
        case Priority::N:
            std::cout << "Container-Priority not initialized" << std::endl;
            break;
        default:
            std::cout << "Container-Priority not available" << std::endl;
            //code to be executed, if the expression doesn't matched to  any constant_1(case 1)
            break;
    }
}














/*
// getters and setters
unsigned int Segment::getMaxAmountOfItem() {
    return item.getMaxAmountPerContainer();
}

//!!! Vor dem Setzen der Prio im Container selbst immer testen, ob der Container leer und auch nicht für das  Hinzufügen reserviert ist.
void Segment::setPriority(const Priority& newPriority) {
    if(hasNoPriorityLevel()) {
        priority = newPriority;
    }
    else{
        throw std::invalid_argument("A container with a valid priority level has been tried to reset mistakenly. Something went wrong.");
    }
}

//!!! vllt. stattdessen einfach Item ersetzen !!!
void Segment::appendItemType(const TransferMessage& transferMessage) {
    item = transferMessage.getItem();
}

// methods
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!

bool Segment::containsPlaceForAmountToAddOfThisItem(const TransferMessage& transferMessage) {
    return (hasMatchingPriorityLevel(transferMessage) && (containsItemsOfSameItemKind(transferMessage)||isEmpty()) && (containsPlaceForAmountToAdd(transferMessage.getAmountToTransfer())));
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool Segment::containsPlaceForAmountToAdd(const unsigned int amount) {
    //!!! folgend erst überprüfen, ob item schon vorhanden ist. Falls nicht, ist Platz da, weil der Container dann leer ist. !!! Analog bei allen Abfragen, die Daten von Item abfragen!!!
    return (currentAmountOfItem + reservedToAddAmount + amount <= item.getMaxAmountPerContainer());
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!

bool Segment::containsAmountToGetOfThisItem(const TransferMessage &transferMessage) {
    return (containsItemsOfSameItemKind(transferMessage) && containsAmountToGet(transferMessage.getAmountToTransfer()));
}

// checks for an amount to get in regards of already reserved amounts to get but not amounts to add. Cause latter ones are not yet added. But first ones are not allowed to be booked twice.
bool Segment::containsAmountToGet(const unsigned int amount) const {
    return ((this->currentAmountOfItem - this->reservedToGetAmount) >= amount);
}

//!!! Darauf achten, dass die Art von Item (entspricht Attribut item von Klasse Item) gelöscht wird, wenn die tatsächliche Menge irgendwo auf Null reduziert wird und aktuell eine Einlagerung reserviert ist.!!!
bool Segment::isEmpty() {
    return (item.getItemId() == 0);
}

bool Segment::hasNoPriorityLevel(){
    return (priority == Priority::N);
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool Segment::containsItemsOfSameItemKind(const TransferMessage& transferMessage) {
    return (this->item.getItemId() == transferMessage.getItem().getItemId());
}

bool Segment::hasMatchingPriorityLevel(const TransferMessage& transferMessage) {
    return (priority == transferMessage.getItem().getPriority());
}

//!!! Prüfen, ob der Konstruktoraufruf von Item so klappt. Ansonsten ggf. Werte manuell auf Null setzen !!!
void Segment::ifEmptyAndNotReservedToAddDeleteItemType() {
    if((currentAmountOfItem == 0) && (reservedToAddAmount == 0)){
        item = Item{};
        //!!! vermutlich gleichbedeutend mit: item.getItemId() == 0
    }
}


void Segment::reserveAmountToAddForItem(const TransferMessage &transferMessage) {
    if(containsPlaceForAmountToAddOfThisItem(transferMessage)){
        if(isEmpty()){ // if currently the container is empty there is no reference values for max limits therefore it needs to be appended first
            appendItemType(transferMessage);
        }
        reserveAmountToAdd(transferMessage.getAmountToTransfer());
    }

}

void Segment::reserveAmountToAdd(const unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container is exceeded. Something went wrong.");
    }
}

void Segment::reserveAmountToTakeForItem(const TransferMessage& transferMessage) {
    if(containsAmountToGetOfThisItem(transferMessage)){
        reserveAmountToTake(transferMessage.getAmountToTransfer());
    }
}

void Segment::reserveAmountToTake(const unsigned int amount) {
    if(containsAmountToGet(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this reservation to add. Something went wrong.");
    }
}

//!!! Zugriffe auf Mengen mit MUTEX regeln, da es sonst zu Unstimmigkeiten kommt. Es darf immer nur abgezogen oder hinzugefügt, zum Holen oder Hinzufügen reserviert werden!!!
//!!! Methode mit TransferMessage als Parameter erstellen!!!

void Segment::addAmount(const TransferMessage& transferMessage) { // amounts get only added if this amount is reserved to be added. The itemType gets appended by the reservation.
    if(containsItemsOfSameItemKind(transferMessage)){
        addAmount(transferMessage.getAmountToTransfer());
    }
}


void Segment::addAmount(unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)) {
        reservedToAddAmount -= amount;
        currentAmountOfItem += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

void Segment::takeAmount(const TransferMessage& transferMessage) {
    if(containsItemsOfSameItemKind(transferMessage)){
        takeAmount(transferMessage.getAmountToTransfer());
    }
}

void Segment::takeAmount(unsigned int amount) {
    if(containsAmountToGet(amount)) {
        reservedToGetAmount -= amount;
        currentAmountOfItem -= amount;
        ifEmptyAndNotReservedToAddDeleteItemType();
    }
    else {
        throw std::invalid_argument("The amount exceeds the available amount of the used container. Something went wrong.");
    }
}
 */













