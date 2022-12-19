/*
 * Transfer station between ConveyorBelts and Shelfs.
 * Can hold certain amount of Containers in a queue (FIFO) depending on their length and own length.
 * Is used for both Storing and Retrieving Containers.
*/

#ifndef NP_SEMESTERPROJEKT_TRANSFERPOINT_H
#define NP_SEMESTERPROJEKT_TRANSFERPOINT_H


#include <queue>

#include "windows.h"
#include "../Item/Container.h"


class TransferPoint {
public:
    explicit TransferPoint(float _distanceToPackaging);
    std::queue<Container> containers;
    void addContainer(const Container&);

	[[maybe_unused]] Container& removeContainer();
    [[nodiscard]] float getDistance() const;
private:
    float length = 2.3f;
    float width = 0.7f;
	[[maybe_unused]] float distanceToPackaging; // distance to the K/I -Point
};


#endif //NP_SEMESTERPROJEKT_TRANSFERPOINT_H
