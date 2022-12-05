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
        itemLib::Item item{};
        unsigned int amountToTransfer{};

        // getters and setters
    public:
        [[nodiscard]] const itemLib::Item &getItem() const;
        [[nodiscard]] unsigned int getAmountToTransfer() const;

        // constructors
        TransferMessage() = default;
        TransferMessage(const itemLib::Item &item, unsigned int amountToTransfer);

    public:

    }; // Inventory
}


#endif //NUPPROJECT_TRANSFERMESSAGE_H
