//
// Created by Kim Simoski on 27.11.2022.
//

#ifndef NUPPROJECT_CONTAINER_H
#define NUPPROJECT_CONTAINER_H

#include "../Item/Priority.h"

#include "../Item/Item.h"
#include "../Messages/TransferMessage.h"



// container for containing items with amounts and priorities in a shelf segment per container

using namespace itemLib;
using namespace messagesLib;

namespace inventoryLib {
    /*
    * The class ShelfContainer is contained by the class Shelf. It represents one container in a segment of the shelf containing an amount of items (Item).
    * The class provides methods to store or restore items. For reservations there are also methods to reserve for adding to and to reserve for getting from the inventory.
    * The items () can only be added to containers with matching priority levels (Priority) if the container has been empty until now or are already containing this item and has space left.
    */
    class ShelfContainer {
// attributes
        //!!! Werte von Items am besten direkt über Methoden beziehen, anstatt sie einzeln aus dem Item als Attribute zu speichern
        Priority priority{Priority::C};

        //!!! Die Art des Items muss unmittelbar beim ersten Reservieren des Hinzufügens eines Items gesetzt werden bzw. bei jedem ersten Reservieren des Hinzufügens von Items nachdem der Container im Regal ganz leer war. Das Checken muss mit einem Mutex beim Reservieren passieren und beim Leeren des Containers auf eine Anzahl von 0.
        Item item{};
        unsigned int currentAmountOfItem{};
        unsigned int reservedToAddAmount{}; // reserved amounts to add are not yet added and therefore are not allowed to leave the inventory but the have to be reserved for not overbooking the space limited by a maximum amount
        unsigned int reservedToGetAmount{}; // reserved amounts to get have not left the inventory therefore are using limited space. Also they are not allowed to be booked twice

        // constructors
    public:
        ShelfContainer();

        explicit ShelfContainer(const Priority &priority);

        // getters and setters
    public:

        unsigned int getMaxAmountOfItem(); // gets max amount of contained item
        void setPriority(const Priority &priority);

        void appendItemType(const TransferMessage &transferMessage);


        // methods
    private:
        void ifEmptyAndNotReservedToAddDeleteItemType(); // for getting used while taking the last items from a container if there are currently no reservations for adding to enable storing a new kind of item

        bool isEmpty();
        [[nodiscard]] bool containsAmountToGet(unsigned int amount) const;
        bool containsPlaceForAmountToAdd(unsigned int amount);
        bool containsItemsOfSameItemKind(const TransferMessage &transferMessage);
        bool hasMatchingPriorityLevel(const TransferMessage& transferMessage);

        void reserveAmountToAdd(unsigned int amount);
        void reserveAmountToTake(unsigned int amount);

        void addAmount(unsigned int amount);
        void takeAmount(unsigned int amount);

        void printPriority();

    public:
        bool hasNoPriorityLevel(); // for initializing the containers priority levels only once to reserve percentages of container amounts for different priority levels

        [[nodiscard]] bool containsAmountToGetOfThisItem(const TransferMessage& transferMessage);
        bool containsPlaceForAmountToAddOfThisItem(const TransferMessage& transferMessage);

        //!!! Reservieren bei Wahl des Laufbands aufrufen. Hinzufügen und abziehen erst aufrufen, wenn die Bedienhilfe tatsächlich angekommen ist !!!
        //!!! bei folgenden Methoden vllt. als bool zurückgeben, ob es geklappt hat!!!
        void reserveAmountToAddForItem(const TransferMessage &transferMessage);
        void reserveAmountToTakeForItem(const TransferMessage &transferMessage);

        void addAmount(const TransferMessage &transferMessage);
        void takeAmount(const TransferMessage &transferMessage);

        void print();
    };
}

#endif //NUPPROJECT_CONTAINER_H
