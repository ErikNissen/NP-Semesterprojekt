/*
 * Transfer station between ConveyorBelts and Shelfs.
 * Can hold certain amount of Containers in a queue (FIFO) depending on their length and own length.
 * Is used for both Storing and Retrieving Containers.
*/

#ifndef NP_SEMESTERPROJEKT_TRANSFERPOINT_H
#define NP_SEMESTERPROJEKT_TRANSFERPOINT_H


#include <queue>
#include "../Inventory/Container.h"
#include "windows.h"

class TransferPoint {
public:
    explicit TransferPoint(float _distanceToPackaging);
    std::queue<Container> containers;
    void addContainer(Container&);
    Container& removeContainer();
    float getDistance() const;
private:
    float length = 2.3;
    float width = 0.7;
    float distanceToPackaging; // distance to the K/I -Point
};


#endif //NP_SEMESTERPROJEKT_TRANSFERPOINT_H
