//
// Created by Kim Simoski on 27.11.2022.
//

#include "Container.h"

#include <utility>


// constructors
Container::Container(const Priority& priority) {
    this->priority = priority;
    item = Item(priority);
    timer = Timer();
}

Container::Container(const Priority& priority, std::string name) {
    this->priority = priority;
    this->name = std::move(name);
    item = Item(priority);
    timer = Timer();
}

// getters and setters
unsigned int Container::getMaxAmountOfItem() {
    return item.getMaxAmountPerContainer();
}

void Container::setPriority(const Priority& priority) {
    this->priority = priority;
}

void Container::appendItemType(const Item& item) {
    this->item = item;
}

// methods
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
// checks for an amount to get in regards of already reserved amounts to get but not amounts to add. Cause latter ones are not yet added. But first ones are not allowed to be booked twice.
bool Container::containsAmountToGet(const unsigned int amount) const {
    if((this->currentAmountOfItem - this->reservedToGetAmount) >= amount){
        return true;
    }
    else{
        return false;
    }
}
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool Container::containsPlaceForAmountToAdd(const unsigned int amount) {
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
bool Container::containsItemsOfSameItemKind(const Item& item) {
    if(this->item.getItemId() == item.getItemId()){
        return true;
    }
    else{
        return false;
    }
}

//!!! Darauf achten, dass die Art von Item (entspricht Attribut item von Klasse Item) gelöscht wird, wenn die tatsächliche Menge irgendwo auf Null reduziert wird und aktuell eine Einlagerung reserviert ist.!!!
bool Container::isEmpty() {
    if (item.getItemId() == 0) {
        return true;
    }
    else{
        return false;
    }
}

void Container::ifEmptyDeleteItemType() {
    if((currentAmountOfItem == 0) && (reservedToAddAmount == 0)){
        item = Item{};
        //!!! vermutlich gleichbedeutend mit: item.getItemId() == 0
    }
}

void Container::reserveAmountToAdd(const unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container is exceeded. Something went wrong.");
    }
}

void Container::reserveAmountToTake(const unsigned int amount) {
    if(containsAmountToGet(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this reservation to add. Something went wrong.");
    }
}

//!!! Zugriffe auf Mengen mit MUTEX regeln, da es sonst zu Unstimmigkeiten kommt. Es darf immer nur abgezogen oder hinzugefügt, zum Holen oder Hinzufügen reserviert werden!!!
void Container::addAmount(unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)) {
        reservedToAddAmount -= amount;
        currentAmountOfItem += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

void Container::takeAmount(unsigned int amount) {

}

void Container::print() {
    item.print();
    std::cout << "current amount of item: " << currentAmountOfItem << std::endl;
    std::cout << "reserved to add amount: " << reservedToAddAmount << std::endl;
    std::cout << "reserved to get amount: " << reservedToGetAmount << std::endl;
}
