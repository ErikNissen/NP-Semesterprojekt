//
// Created by Kim Simoski on 27.11.2022.
//

#include "ShelfContainer.h"
#include "../Messages/TransferMessage.h"

using namespace inventoryLib;

// constructors
ShelfContainer::ShelfContainer(){
    priority = Priority::N;
    item = Item();
}

ShelfContainer::ShelfContainer(const Priority& priority) {
    this->priority = priority;
    item = Item(priority);
}

// getters and setters
unsigned int ShelfContainer::getMaxAmountOfItem() {
    return item.getMaxAmountPerContainer();
}

//!!! Vor dem Setzen der Prio im Container selbst immer testen, ob der Container leer und auch nicht für das  Hinzufügen reserviert ist.
void ShelfContainer::setPriority(const Priority& newPriority) {
    if(hasNoPriorityLevel()) {
        priority = newPriority;
    }
    else{
        throw std::invalid_argument("A container with a valid priority level has been tried to reset mistakenly. Something went wrong.");
    }
}

//!!! vllt. stattdessen einfach Item ersetzen !!!
void ShelfContainer::appendItemType(const TransferMessage& transferMessage) {
    item = transferMessage.getItem();
}

// methods
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!

bool ShelfContainer::containsPlaceForAmountToAddOfThisItem(const TransferMessage& transferMessage) {
    return (hasMatchingPriorityLevel(transferMessage) && (containsItemsOfSameItemKind(transferMessage)||isEmpty()) && (containsPlaceForAmountToAdd(transferMessage.getAmountToTransfer())));
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool ShelfContainer::containsPlaceForAmountToAdd(const unsigned int amount) {
    //!!! folgend erst überprüfen, ob item schon vorhanden ist. Falls nicht, ist Platz da, weil der Container dann leer ist. !!! Analog bei allen Abfragen, die Daten von Item abfragen!!!
    return (currentAmountOfItem + reservedToAddAmount + amount <= item.getMaxAmountPerContainer());
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!

bool ShelfContainer::containsAmountToGetOfThisItem(const TransferMessage &transferMessage) {
    return (containsItemsOfSameItemKind(transferMessage) && containsAmountToGet(transferMessage.getAmountToTransfer()));
}

// checks for an amount to get in regards of already reserved amounts to get but not amounts to add. Cause latter ones are not yet added. But first ones are not allowed to be booked twice.
bool ShelfContainer::containsAmountToGet(const unsigned int amount) const {
    return ((this->currentAmountOfItem - this->reservedToGetAmount) >= amount);
}

//!!! Darauf achten, dass die Art von Item (entspricht Attribut item von Klasse Item) gelöscht wird, wenn die tatsächliche Menge irgendwo auf Null reduziert wird und aktuell eine Einlagerung reserviert ist.!!!
bool ShelfContainer::isEmpty() {
    return (item.getItemId() == 0);
}

bool ShelfContainer::hasNoPriorityLevel(){
    return (priority == Priority::N);
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool ShelfContainer::containsItemsOfSameItemKind(const TransferMessage& transferMessage) {
    return (this->item.getItemId() == transferMessage.getItem().getItemId());
}

bool ShelfContainer::hasMatchingPriorityLevel(const TransferMessage& transferMessage) {
    return (priority == transferMessage.getItem().getPriority());
}

//!!! Prüfen, ob der Konstruktoraufruf von Item so klappt. Ansonsten ggf. Werte manuell auf Null setzen !!!
void ShelfContainer::ifEmptyAndNotReservedToAddDeleteItemType() {
    if((currentAmountOfItem == 0) && (reservedToAddAmount == 0)){
        item = Item{};
        //!!! vermutlich gleichbedeutend mit: item.getItemId() == 0
    }
}


void ShelfContainer::reserveAmountToAddForItem(const TransferMessage &transferMessage) {
    if(containsPlaceForAmountToAddOfThisItem(transferMessage)){
        if(isEmpty()){ // if currently the container is empty there is no reference values for max limits therefore it needs to be appended first
            appendItemType(transferMessage);
        }
        reserveAmountToAdd(transferMessage.getAmountToTransfer());
    }

}

void ShelfContainer::reserveAmountToAdd(const unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container is exceeded. Something went wrong.");
    }
}

void ShelfContainer::reserveAmountToTakeForItem(const TransferMessage& transferMessage) {
    if(containsAmountToGetOfThisItem(transferMessage)){
        reserveAmountToTake(transferMessage.getAmountToTransfer());
    }
}

void ShelfContainer::reserveAmountToTake(const unsigned int amount) {
    if(containsAmountToGet(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this reservation to add. Something went wrong.");
    }
}

//!!! Zugriffe auf Mengen mit MUTEX regeln, da es sonst zu Unstimmigkeiten kommt. Es darf immer nur abgezogen oder hinzugefügt, zum Holen oder Hinzufügen reserviert werden!!!
//!!! Methode mit TransferMessage als Parameter erstellen!!!

void ShelfContainer::addAmount(const TransferMessage& transferMessage) { // amounts get only added if this amount is reserved to be added. The itemType gets appended by the reservation.
    if(containsItemsOfSameItemKind(transferMessage)){
        addAmount(transferMessage.getAmountToTransfer());
    }
}


void ShelfContainer::addAmount(unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)) {
        reservedToAddAmount -= amount;
        currentAmountOfItem += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

void ShelfContainer::takeAmount(const TransferMessage& transferMessage) {
    if(containsItemsOfSameItemKind(transferMessage)){
        takeAmount(transferMessage.getAmountToTransfer());
    }
}

void ShelfContainer::takeAmount(unsigned int amount) {
    if(containsAmountToGet(amount)) {
        reservedToGetAmount -= amount;
        currentAmountOfItem -= amount;
        ifEmptyAndNotReservedToAddDeleteItemType();
    }
    else {
        throw std::invalid_argument("The amount exceeds the available amount of the used container. Something went wrong.");
    }
}


void ShelfContainer::print() {
    std::cout << "********************************"<< std::endl;
    item.print();
    printPriority();
    std::cout << "current amount of item: " << currentAmountOfItem << std::endl;
    std::cout << "reserved to add amount: " << reservedToAddAmount << std::endl;
    std::cout << "reserved to get amount: " << reservedToGetAmount << std::endl;
    std::cout << "********************************"<< std::endl;
}

// https://stackoverflow.com/questions/66488850/how-to-print-the-enum-value-from-its-index
void ShelfContainer::printPriority() {
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










