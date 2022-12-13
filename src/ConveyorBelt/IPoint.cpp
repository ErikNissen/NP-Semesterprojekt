//
// Created by alexn on 11.12.2022.
//

#include "IPoint.h"


IPoint::IPoint(inventoryLib::Inventory &inventory) : inv{inventory}, conveyor{ConveyorBeltStore()} {}

// Check if there is a non-full Container with the same ItemType already in the Inventory and initiate its Output
std::optional<TimeSegmentMessage> IPoint::checkForNonFullContainersInInventory(const Item &itemType) {
    auto answer{inv.reserveContainerOutputFromInventoryToAddItems(itemType)};
    if(answer) {
        ///TODO: tell the thread of this ShelfPair to wait for answer->getNeededTimeWithoutWaitingInQueueInSeconds() and then call takeContainer() to put it onto outputTransferPoint
    }
    return answer;
}

// Generate new Containers and fill them with Items
std::vector<Container> IPoint::generateContainersForItems(const Item &item, unsigned int itemCount) {
    std::vector<Container> newContainers;
    unsigned int amountOfContainers {itemCount / item.getMaxAmountPerContainer()};
    unsigned int amountOfItemsInLastContainer {itemCount % item.getMaxAmountPerContainer()};

    if(amountOfItemsInLastContainer > 0) {
        amountOfContainers++;
    } else {
        amountOfItemsInLastContainer = item.getMaxAmountPerContainer();
    }

    // Create as many full containers as possible and one last container with the rest of the items
    for(int i = 1; i <= amountOfContainers; i++){
        if(i != amountOfContainers) {
            newContainers.emplace_back(Container(item, item.getMaxAmountPerContainer()));
        } else {
            newContainers.emplace_back(Container(item, amountOfItemsInLastContainer));
        }
    }

    return newContainers;
}

// Actually send a Container to a TransferPoint via the storing ConveyorBelt
void IPoint::dispatchContainer(Container &container, TransferPoint &tp) {
    conveyor.transportContainer(container, tp);
}

/// This is the main public method that gets called from outside the class. It is only allowed to run once at a time. TODO: If necessary (if multiple threads actually access this method), lock with Mutex.
// Initiate the storing of a certain amount of Items into the Inventory.
// If possible and useful, existing Containers in Inventory will be filled before new Containers are then generated for the rest of the items.
void IPoint::storeItemsInInventory(itemLib::Item item, const unsigned int totalItemCount) {
    std::vector<Container> containers {};
    int itemCount {static_cast<int>(totalItemCount)};
    // If the Items can fit perfectly into new >full< containers, there is no point in filling an existing one.
    if(!(itemCount % item.getMaxAmountPerContainer())) {
        // Check if there is a non-full Container in the Inventory with the same ItemType
        auto res {this->checkForNonFullContainersInInventory(item)};
        // If so, retrieve it and reduce the amount of Items to put in new Containers accordingly.
        if(res) {
            ///TODO: implement as method (in SegmentMessage) like the following to get amount of free space in the Container that gets retrieved
            /// (basically the same as takeContainer() but without functionality, just return a reference)
            // reduce the itemCount by the amount that can fit into the already existing Container
            // itemCount -= inv.getContainer(res->getSegmentDataMessage()).getFreeSpaceInContainer();

            ///TODO: If there was a non-full Container that can be filled, that filling can't be done right here but must later be initiated by the K-Point once the Container actually gets there.
            /// That means the K-Point must somehow know that the Container needs to be filled and with how many items, once it gets there (store this info within the Container?).
        }
    }
    // If not all Items can fit into the existing Containers, or there are none, generate new Containers.
    if(itemCount > 0) {
        containers = generateContainersForItems(item, itemCount);
    }
    for(Container& c : containers) {
        auto answer {inv.reserveContainerToAddToInventory(c)};
        if(answer) {
            // put Container onto ConveyorBelt and send it to the correct TransferPoint
            dispatchContainer(c, inv.getShelfPairByShelfNumber(answer->getShelfPairNumber()).getInputTransferPoint());
            // wait before putting the next Container onto the ConveyorBelt
            Sleep(250);
        }
    }
}
