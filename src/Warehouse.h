//
// Created by alexn on 19.12.2022.
//

#ifndef NP_SEMESTERPROJEKT_WAREHOUSE_H
#define NP_SEMESTERPROJEKT_WAREHOUSE_H


#include "Inventory.h"
#include "IPoint.h"
#include "KPoint.h"
#include "ConveyorBeltRetrieve.h"
#include <unistd.h>
//#include <ntgdi.h>

class Warehouse {
public:
    Warehouse();
    [[nodiscard]] IPoint getIPoint() const;
    [[nodiscard]] KPoint getKPoint() const;
    void testing();
private:
    inventoryLib::Inventory inventory;
    IPoint iPoint;
    KPoint kPoint;
    ConveyorBeltStore conveyorStore;
    ConveyorBeltRetrieve conveyorRetrieve;
};


#endif //NP_SEMESTERPROJEKT_WAREHOUSE_H
