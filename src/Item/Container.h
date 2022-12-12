//
// Created by Kim Simoski on 27.11.2022.
//

#ifndef NUPPROJECT_CONTAINER_H
#define NUPPROJECT_CONTAINER_H

#include "Priority.h"
#include "Item.h"
#include "Timer.h"


// container for containing items with amounts and priorities in a shelf segment per container

using namespace itemLib;

class Container {
    // attributes
private:
    Item item{};
    unsigned int currentAmountOfItem;

public:
    Timer timer; // Tracks the time a Container is getting transported
    constexpr static float length = 0.4;
    constexpr static float width = 0.6;
    constexpr static float height = 0.4;
    std::string name = "Container";

    // constructors
public:
    explicit Container(const Item& item);
    explicit Container(const Item& item, unsigned int currentAmount);

    // getters and setters
public:
    [[nodiscard]] const Item &getItem() const;
    [[nodiscard]] unsigned int getMaxAmountOfItem() const; // gets max amount of contained item
    [[nodiscard]] unsigned int getCurrentAmountOfItem() const;
    [[nodiscard]] unsigned int getAmountOfPlacesForItem() const;
    [[nodiscard]] Priority getItemsPriority() const;
    void appendItemType(const Item& item);


    // methods
private:
    [[nodiscard]] bool containsAmountToGet(unsigned int amount) const;
    bool containsPlaceForAmountToAdd(unsigned int amount);
public:
    bool containsItemsOfSameItemKind(const Item& item);
    [[nodiscard]] bool isEmpty() const;

    bool containsAtLeastOnePieceOfThisItemToGet(const Item& item);
    bool containsPlaceForAtLeastOnePieceOfThisItemToAdd(const Item& item);

    //bool containsAmountToGetOfThisItem(const TransferMessage& transferMessage);
    //bool containsPlaceForAmountToAddOfThisItem(const TransferMessage& transferMessage);

    void addAmount(unsigned int amount);
    void takeAmount(unsigned int amount);
    void print();
};

#endif //NUPPROJECT_CONTAINER_H
