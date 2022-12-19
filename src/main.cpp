#include "main.hpp"
#include "Inventory.h"
#include <thread>

int main (int argc, char *argv[]) {
	Warehouse warehouse{};
//	warehouse.testing();

    endlessThread(warehouse);

    return 0;
}

void endlessThread(Warehouse& warehouse){
    std::jthread iHandler(endlesThreadHandlerIPoint, std::ref(warehouse));
    std::jthread kHandler(endlesThreadHandlerKPoint, std::ref(warehouse));
}

void endlesThreadHandlerIPoint(Warehouse& warehouse) {
    while (true) {
        warehouse.getIPoint().processNextContainerInQueue();
    }
}

void endlesThreadHandlerKPoint(Warehouse& warehouse) {
    while (true) {
        warehouse.getKPoint().processNextContainerInQueue();
    }
}