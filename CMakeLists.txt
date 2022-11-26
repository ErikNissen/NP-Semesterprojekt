set(CPP_VERSION 20)

cmake_minimum_required(VERSION 3.21)
project(NP_Semesterprojekt)

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

include_directories(src src/ConveyorBelt)

add_executable(NP_Semesterprojekt
        src/main.cpp
        src/main.hpp
        src/ConveyorBelt/Container.cpp
        src/ConveyorBelt/ConveyorBelt.cpp
        src/ConveyorBelt/ConveyorBeltRetrieve.cpp
        src/ConveyorBelt/ConveyorBeltStore.cpp
        src/ConveyorBelt/TransferPoint.cpp
        src/ConveyorBelt/Timer.cpp)
