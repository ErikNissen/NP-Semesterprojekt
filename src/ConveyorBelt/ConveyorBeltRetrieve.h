/*
 * This ConveyorBelt is used only for retrieving Containers from the TransferPoints.
*/

#ifndef NP_SEMESTERPROJEKT_CONVEYORBELTRETRIEVE_H
#define NP_SEMESTERPROJEKT_CONVEYORBELTRETRIEVE_H


#include "ConveyorBelt.h"
#include "../Item/Container.h"
#include "TransferPoint.h"

class [[maybe_unused]] ConveyorBeltRetrieve : public ConveyorBelt {
public:
    ConveyorBeltRetrieve();

	[[maybe_unused]] Container& transportContainer(TransferPoint&);
};


#endif //NP_SEMESTERPROJEKT_CONVEYORBELTRETRIEVE_H
