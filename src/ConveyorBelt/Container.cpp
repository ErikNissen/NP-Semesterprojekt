//
// Created by alexn on 21.11.2022.
//

#include "Container.h"

#include <utility>

Container::Container(std::string _name) : name{std::move(_name)} {}
