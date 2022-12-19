/*
 * This ConveyorBelt is used only for retrieving Containers from the TransferPoints.
*/

#ifndef NP_SEMESTERPROJEKT_CONVEYORBELTRETRIEVE_H
#define NP_SEMESTERPROJEKT_CONVEYORBELTRETRIEVE_H


#include "ConveyorBelt.h"
#include "Container.h"

class KPoint;

namespace conveyorLib{

    class ConveyorBeltRetrieve : public ConveyorBelt {
    public:
        explicit ConveyorBeltRetrieve(KPoint&);
        KPoint& kPoint;
        void transportContainer(Container&, float distance);
    };

}
#endif //NP_SEMESTERPROJEKT_CONVEYORBELTRETRIEVE_H
