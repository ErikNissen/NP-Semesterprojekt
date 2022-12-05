//
// Created by Kim Simoski on 22.11.2022.
//

#include "TransferMessage.h"

using namespace messagesLib;

// getters and setters
const itemLib::Item &TransferMessage::getItem() const {
    return item;
}

unsigned int TransferMessage::getAmountToTransfer() const {
    return amountToTransfer;
}

// constructors
TransferMessage::TransferMessage(const itemLib::Item &item, unsigned int amountToTransfer) : item(item),
                                                                                             amountToTransfer(
                                                                                                     amountToTransfer) {}
