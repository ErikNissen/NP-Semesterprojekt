//
// Created by alexn on 13.12.2022.
//

#ifndef NP_SEMESTERPROJEKT_KPOINT_H
#define NP_SEMESTERPROJEKT_KPOINT_H

#include "Item.h"
#include "Container.h"
#include "Inventory.h"
#include "ConveyorBeltRetrieve.h"
#include "IPoint.h"


class KPoint {
public:
    explicit KPoint(inventoryLib::Inventory&, IPoint&);
    void addContainer(Container&);
private:
    bool processNextContainerInQueue();
    std::queue<Container> containers;
    inventoryLib::Inventory& inv;
    IPoint& iPoint;
};


#endif //NP_SEMESTERPROJEKT_KPOINT_H
