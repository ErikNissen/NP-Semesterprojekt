//
// Created by Kim Simoski on 22.11.2022.
//

#ifndef NUPPROJECT_TRANSFERMESSAGE_H
#define NUPPROJECT_TRANSFERMESSAGE_H

#include "../Item/Item.h"

namespace messagesLib {

    class TransferMessage {
        // attributes
    private:
        itemLib::Item item;
        unsigned int amountToTransfer;

        // getters and setters
    public:
        TransferMessage(const itemLib::Item &item, unsigned int amountToTransfer);

        const itemLib::Item &getItem() const;
        unsigned int getAmountToTransfer() const;

        // constructors
    public:

    }; // Inventory
}


#endif //NUPPROJECT_TRANSFERMESSAGE_H
