//
// Created by Kim Simoski on 22.11.2022.
//

#include "Item.h"

using namespace  itemLib;

// constructors


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

// methods
void Item::print() {

    std::cout << "item ID: " << itemID << std::endl;
    //!!! https://www.delftstack.com/howto/cpp/how-to-convert-enum-to-string-cpp/#:~:text=Use%20Custom%20Defined%20Function%20to%20Convert%20an%20Enum,char%2A%20value%20from%20enum_str%20array%20inside%20the%20function.

    printPriority();
    std::cout << "max. amount per container: " << maxAmountPerContainer << std::endl;
}

// https://stackoverflow.com/questions/66488850/how-to-print-the-enum-value-from-its-index
// !!! Methode am besten an die Klasse Priority koppelt (direkt oder als friend, falls das geht.)
void Item::printPriority() {
    switch (this->priority) {
        case Priority::A:
            std::cout << "Item-Priority: A" << std::endl;
            break;
        case Priority::B:
            std::cout << "Item-Priority: B" << std::endl;
            break;
        case Priority::C:
            std::cout << "Item-Priority: C" << std::endl;
            break;
        case Priority::N:
            std::cout << "Item-Priority not itialized" << std::endl;
            break;
        default:
            std::cout << "Item-Priority not available" << std::endl;
            //code to be executed, if the expression doesn't matched to  any constant_1(case 1)
            break;
    }
}




