//
// Created by alexn on 13.12.2022.
//

/*
 * This class handles the retrieving of Items from the Inventory.
 * It can receive tasks (TransferMessages) to retrieve a certain amount of a certain Item
 * and will try to fulfill them by requesting Containers from the Inventory and removing the Items from them.
 * When a Container is not empty after checking through all current tasks,
 * it is send to the IPoint for re-storing into the Inventory.
 * Empty Containers are discarded.
 */

#ifndef NP_SEMESTERPROJEKT_KPOINT_H
#define NP_SEMESTERPROJEKT_KPOINT_H

#include "Container.h"

class IPoint;

namespace inventoryLib {
    class Inventory;
}
namespace messagesLib {
    class TransferMessage;
}
namespace conveyorLib {
    class TransferPoint;
}

class KPoint {
public:
    explicit KPoint(inventoryLib::Inventory&, IPoint&);
    void addContainer(Container&);
    bool processNextContainerInQueue();
    void sendTaskForRetrievingItems(messagesLib::TransferMessage&);
private:
    auto sendTaskToInventory(messagesLib::TransferMessage&);
    void checkTransferPoints();
    std::queue<Container> containersToCheck;
    inventoryLib::Inventory& inv;
    std::vector<messagesLib::TransferMessage> tasks;
    std::vector<std::reference_wrapper<conveyorLib::TransferPoint>> transferPoints{};
    IPoint& iPoint;
};


#endif //NP_SEMESTERPROJEKT_KPOINT_H
