//
// Created by alexn on 11.12.2022.
//

#ifndef NP_SEMESTERPROJEKT_IPOINT_H
#define NP_SEMESTERPROJEKT_IPOINT_H

#include "Item.h"
#include "Container.h"
#include "TransferPoint.h"
#include "Inventory.h"
#include "ConveyorBeltStore.h"

class IPoint {
public:
    explicit IPoint(inventoryLib::Inventory&);
    void storeItemsInInventory(itemLib::Item, unsigned int totalItemCount);
private:
    inventoryLib::Inventory& inv;
    ConveyorBeltStore conveyor;
    std::optional<TimeSegmentMessage> checkForNonFullContainersInInventory(const itemLib::Item& itemType);
    static std::vector<Container> generateContainersForItems(const itemLib::Item&, unsigned int itemCount);
    void dispatchContainer(Container&, TransferPoint&);
};


#endif //NP_SEMESTERPROJEKT_IPOINT_H
