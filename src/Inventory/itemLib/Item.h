//
// Created by Kim Simoski on 22.11.2022.
//

#ifndef NUPPROJECT_ITEM_H
#define NUPPROJECT_ITEM_H

#include<bits/stdc++.h>
#include "Priority.h"

namespace itemLib {
    class Item {
        // attributes
    private:
        unsigned int itemID{};
        Priority priority;
        unsigned int maxAmountPerContainer{};


        // constructors
    public:
        Item();
        explicit Item(const Priority& priority);
        Item(unsigned int itemId, Priority priority, unsigned int maxAmountPerContainer);

    public:

        // getters and setters
    public:
        [[nodiscard]] unsigned int getItemId() const;
        [[nodiscard]] Priority getPriority() const;
        [[nodiscard]] unsigned int getMaxAmountPerContainer() const;

        // methods
    public:
        void print();
    };
}


#endif //NUPPROJECT_ITEM_H
