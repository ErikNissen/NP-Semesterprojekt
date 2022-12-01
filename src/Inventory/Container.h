//
// Created by Kim Simoski on 27.11.2022.
//

#ifndef NUPPROJECT_CONTAINER_H
#define NUPPROJECT_CONTAINER_H

#include "../Item/Priority.h"

#include "../Item/Item.h"


// container for containing items with amounts and priorities in a shelf segment per container

using namespace itemLib;

class Container {
    // attributes
    //!!! Werte von Items am besten direkt über Methoden beziehen, anstatt sie einzeln aus dem Item als Attribute zu speichern
    Priority priority;
    //!!! Die Art des Items muss inmittelbar beim ersten Reservieren des Hinzufügens eines Items gesetzt werden bzw. bei jedem ersten Reservieren des Hinzufügens von Items nachdem der Container im Regal ganz leer war. Das Checken muss mit einem Mutex beim Reservieren passieren und beim Leeren des Containers auf eine Anzahl von 0.
    Item item;
    unsigned int currentAmountOfItem{};
    unsigned int reservedToAddAmount{}; // reserved amounts to add are not yet added and therefore are not allowed to leave the inventory but the have to be reserved for not overbooking the space limited by a maximum amount
    unsigned int reservedToGetAmount{}; // reserved amounts to get have not left the inventory therefore are using limited space. Also they are not allowed to be booked twice

    // constructors
public: explicit Container(const Priority& priority);

    // getters and setters
public:
    // methods
    unsigned int getMaxAmountOfItem(); // gets max amount of contained item
    void setPriority(const Priority& priority);
    void appendItemType(const Item& item);
    void ifEmptyDeleteItemType();

private:
    [[nodiscard]] bool containsAmountToGet(unsigned int amount) const;
    bool containsPlaceForAmountToAdd(unsigned int amount);
public:
    bool containsItemsOfSameItemKind(const Item& item);
    bool isEmpty();

    //!!! Reservieren bei Wahl des Laufbands aufrufen. Hinzufügen und abziehen erst aufrufen, wenn die Bedienhilfe tatsächlich angekommen ist !!!
    //!!! bei folgenden Methoden vllt. als bool zurückgeben, ob es geklappt hat!!!
    void reserveAmountToAdd(unsigned int amount);
    void reserveAmountToTake(unsigned int amount);
    void addAmount(unsigned int amount);
    void takeAmount(unsigned int amount);
    void print();
};

#endif //NUPPROJECT_CONTAINER_H
