//
// Created by alexn on 11.12.2022.
//

#include "IPoint.h"


IPoint::IPoint(inventoryLib::Inventory &inventory) : inv{inventory} {}

std::optional<TimeSegmentMessage> IPoint::checkForNonFullContainersInInventory(const Item &itemType) {
    auto answer{inv.reserveContainerOutputFromInventoryToAddItems(itemType)};
    return answer;
}

std::vector<Container> IPoint::generateContainersForItems(const Item &item, unsigned int itemCount) {
    std::vector<Container> newContainers;
    unsigned int amountOfContainers {itemCount / item.getMaxAmountPerContainer()};
    unsigned int amountOfItemsInLastContainer {itemCount % item.getMaxAmountPerContainer()};

    if(amountOfItemsInLastContainer > 0) {
        amountOfContainers++;
    } else {
        amountOfItemsInLastContainer = item.getMaxAmountPerContainer();
    }

    // Create as many full containers as needed and one last container with the rest of the items
    for(int i = 1; i <= amountOfContainers; i++){
        if(i != amountOfContainers) {
            newContainers.emplace_back(Container(item, item.getMaxAmountPerContainer()));
        } else {
            newContainers.emplace_back(Container(item, amountOfItemsInLastContainer));
        }
    }

    return newContainers;
}

void IPoint::dispatchContainer(Container &container, TransferPoint &tp) {

}

void IPoint::storeItemsInInventory(itemLib::Item item, const unsigned int totalItemCount) {
    std::vector<Container> containers {};
    int itemCount {static_cast<int>(totalItemCount)};
    // If the Items can fit perfectly into new >full< containers, there is no point in filling an existing one.
    if(!(itemCount % item.getMaxAmountPerContainer())) {
        // Check if there is a non-full Container in the Inventory with the same ItemType
        auto res {this->checkForNonFullContainersInInventory(item)};
        // If so, retrieve it and reduce the amount of Items to put in new Containers accordingly.
        if(res) {
            // itemCount -= res.freeSpaceInContainer
            // inv.takeContainer(res->getSegmentDataMessage());
        }
    }
    // If not all Items can fit into the existing Containers, or there are none, generate new Containers.
    if(itemCount > 0) {
        containers = generateContainersForItems(item, itemCount);
    }
    for(Container& c : containers) {
        auto answer {inv.reserveContainerToAddToInventory(c)};
        if(answer) {
            dispatchContainer(c, answer.get)
        }
    }
}
