/*
 * Manually track calculated times.
*/

#ifndef NP_SEMESTERPROJEKT_TIMER_H
#define NP_SEMESTERPROJEKT_TIMER_H

#include <iostream>


class Timer {
public:
    float timeInSeconds = 0;
    void addSeconds(float);
    void printSeconds() const;
};


#endif //NP_SEMESTERPROJEKT_TIMER_H
