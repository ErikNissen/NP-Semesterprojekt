//
// Created by alexn on 13.12.2022.
//

#include "KPoint.h"

KPoint::KPoint(inventoryLib::Inventory &inventory, IPoint& _iPoint) : inv{inventory}, iPoint{_iPoint} {}



void KPoint::addContainer(Container &container) {
    containers.push(container);
}

bool KPoint::processNextContainerInQueue() {
    if(!containers.empty()) {
        // Store the first Container from the queue
        Container container = containers.front();
        // Remove from queue
        containers.pop();

        /// getAmountOfItemsToChange must be a value of Container which indicates how many Items to remove/add
        /*
        if(container.getAmountOfItemsToChange() < 0) {
            container.takeAmount(getAmountOfItemsToChange());
        } else {
            container.addAmount(getAmountOfItemsToChange());
        }*/
        if(!container.isEmpty()) {
            iPoint.storeContainerInInventory(container);
        }
        return true;
    } else {
        return false;
    }
}
