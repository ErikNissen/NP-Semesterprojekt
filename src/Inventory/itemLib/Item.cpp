//
// Created by Kim Simoski on 22.11.2022.
//

#include "Item.h"

using namespace  itemLib;

// constructors
Item::Item()
{}

Item::Item(const Priority& priority) { // used by container in inventory lib
    this->priority = priority;
}

Item::Item(unsigned int itemId, Priority priority, unsigned int maxAmountPerContainer) {
    this->itemID = itemId;
    this->priority = priority;
    this->maxAmountPerContainer = maxAmountPerContainer;
}


// getters and setters
unsigned int Item::getItemId() const {
    return itemID;
}

Priority Item::getPriority() const {
    return priority;
}

unsigned int Item::getMaxAmountPerContainer() const {
    return maxAmountPerContainer;
}

void Item::print() {

    std::cout << "item ID: " << itemID << std::endl;
    //!!! https://www.delftstack.com/howto/cpp/how-to-convert-enum-to-string-cpp/#:~:text=Use%20Custom%20Defined%20Function%20to%20Convert%20an%20Enum,char%2A%20value%20from%20enum_str%20array%20inside%20the%20function.
    //std::cout << "priority: " << std::static_cast<string>(Priority::priority) << std::endl;
    std::cout << "max. amount per container: " << maxAmountPerContainer << std::endl;
}




