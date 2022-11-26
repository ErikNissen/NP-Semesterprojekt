//
// Created by alexn on 21.11.2022.
//

#ifndef NP_SEMESTERPROJEKT_CONTAINER_H
#define NP_SEMESTERPROJEKT_CONTAINER_H


#include <string>

class Container {
public:
    Container() = default;
    explicit Container(std::string);
    constexpr static float length = 0.4;
    constexpr static float width = 0.6;
    constexpr static float height = 0.4;
    std::string name = "Container";
};


#endif //NP_SEMESTERPROJEKT_CONTAINER_H
