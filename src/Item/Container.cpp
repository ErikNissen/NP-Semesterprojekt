//
// Created by Kim Simoski on 07.12.2022.
//

#include "Container.h"
//
// Created by Kim Simoski on 27.11.2022.
//


// constructors
Container::Container(const Item& item) {
    this->item = item;
    timer = Timer();
}

Container::Container(const Item& item, std::string name) {
    this->item = item;
    this->name = std::move(name);
    timer = Timer();
}

// getters and setters
unsigned int Container::getMaxAmountOfItem() {
    return item.getMaxAmountPerContainer();
}

unsigned int Container::getAmountOfPlacesForItem() {
    return item.getMaxAmountPerContainer() - currentAmountOfItem;
}

Priority Container::getItemsPriority() {
    return item.getPriority();
}

void Container::appendItemType(const Item& externalItem) {
    this->item = externalItem;
}

// methods
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
// checks for an amount to get in regards of already reserved amounts to get but not amounts to add. Cause latter ones are not yet added. But first ones are not allowed to be booked twice.
bool Container::containsAmountToGet(const unsigned int amount) const {
    return this->currentAmountOfItem >= amount;
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool Container::containsPlaceForAmountToAdd(const unsigned int amount) {
    //!!! folgend erst überprüfen, ob item schon vorhanden ist. Falls nicht, ist Platz da, weil der Container dann leer ist. !!! Analog bei allen Abfragen, die Daten von Item abfragen!!!
    return currentAmountOfItem + amount <= item.getMaxAmountPerContainer();
}

bool Container::containsItemsOfSameItemKind(const Item& externalItem) {
    return this->item.getItemId() == externalItem.getItemId();
}

void Container::addAmount(unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)) {
        currentAmountOfItem += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

void Container::takeAmount(unsigned int amount) {
    if(containsAmountToGet(amount)) {
        currentAmountOfItem -= amount;
    }
    else {
        throw std::invalid_argument("The minimum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

bool Container::containsAtLeastOnePieceOfThisItemToGet(const Item &externalItem) {
    return containsItemsOfSameItemKind(externalItem) && containsAmountToGet(1);
}

bool Container::containsPlaceForAtLeastOnePieceOfThisItemToAdd(const Item &externalItem) {
    return (containsItemsOfSameItemKind(externalItem) && containsPlaceForAmountToAdd(1)) || isEmpty();
}

bool Container::isEmpty() const {
    return (currentAmountOfItem == 0);
}

void Container::print() {
    item.print();
    std::cout << "current amount of item: " << currentAmountOfItem << std::endl;
}











