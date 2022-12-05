//
// Created by Kim Simoski on 27.11.2022.
//

#include "ShelfContainer.h"
#include "../Messages/TransferMessage.h"


// constructors
ShelfContainer::ShelfContainer(){
    priority = Priority::C;
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
void ShelfContainer::setPriority(const Priority& priority) {
    this->priority = priority;
}

void ShelfContainer::appendItemType(const Item& item) {
    this->item = item;
}

// methods
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
// checks for an amount to get in regards of already reserved amounts to get but not amounts to add. Cause latter ones are not yet added. But first ones are not allowed to be booked twice.
bool ShelfContainer::containsAmountToGet(const unsigned int amount) const {
    if((this->currentAmountOfItem - this->reservedToGetAmount) >= amount){
        return true;
    }
    else{
        return false;
    }
}
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool ShelfContainer::containsPlaceForAmountToAdd(const unsigned int amount) {
    //!!! folgend erst überprüfen, ob item schon vorhanden ist. Falls nicht, ist Platz da, weil der Container dann leer ist. !!! Analog bei allen Abfragen, die Daten von Item abfragen!!!
    if(currentAmountOfItem + reservedToAddAmount + amount <= item.getMaxAmountPerContainer()){
        return true;
    }
    else{
        return false;
    }
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool ShelfContainer::containsItemsOfSameItemKind(const Item& item) {
    if(this->item.getItemId() == item.getItemId()){
        return true;
    }
    else{
        return false;
    }
}

//!!! Darauf achten, dass die Art von Item (entspricht Attribut item von Klasse Item) gelöscht wird, wenn die tatsächliche Menge irgendwo auf Null reduziert wird und aktuell eine Einlagerung reserviert ist.!!!
bool ShelfContainer::isEmpty() {
    if (item.getItemId() == 0 || !hasPriorityLevel()) {
        return true;
    }
    else{
        return false;
    }
}

bool ShelfContainer::hasNoPriorityLevel(){
    return !hasPriorityLevel();
}

bool ShelfContainer::hasPriorityLevel() {
    return (priority != Priority::N);
}

//!!! Prüfen, ob der Konstruktoraufruf von Item so klappt. Ansonsten ggf. Werte manuell auf Null setzen !!!
void ShelfContainer::ifEmptyAndNotResToAddDeleteItemType() {
    if((currentAmountOfItem == 0) && (reservedToAddAmount == 0)){
        item = Item{};
        //!!! vermutlich gleichbedeutend mit: item.getItemId() == 0
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
void ShelfContainer::addAmount(unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)) {
        reservedToAddAmount -= amount;
        currentAmountOfItem += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

void ShelfContainer::takeAmount(messagesLib::TransferMessage &transferMessage) {
    if(item.getItemId() == transferMessage.getItem().getItemId()){
        takeAmount(transferMessage.getAmountToTransfer());
    }
}

void ShelfContainer::takeAmount(unsigned int amount) {
    if(containsAmountToGet(amount)) {
        reservedToGetAmount -= amount;
        currentAmountOfItem -= amount;
        ifEmptyAndNotResToAddDeleteItemType();
    }
    else {
        throw std::invalid_argument("The amount exceeds the available amount of the used container. Something went wrong.");
    }
}

/*
bool areItemIDsMatching(const messagesLib::TransferMessage &transferMessage){
    return (item.getItemId() == transferMessage.getItem().getItemId());
}
*/

void ShelfContainer::print() {
    item.print();
    std::cout << "current amount of item: " << currentAmountOfItem << std::endl;
    std::cout << "reserved to add amount: " << reservedToAddAmount << std::endl;
    std::cout << "reserved to get amount: " << reservedToGetAmount << std::endl;
}




