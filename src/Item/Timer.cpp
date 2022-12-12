//
// Created by alexn on 26.11.2022.
//

#include "Timer.h"

void Timer::addSeconds(float _seconds) {
    timeInSeconds += _seconds;
}

void Timer::printSeconds() const {
    std::cout << "Timer at " << timeInSeconds << " seconds." << std::endl;
}
