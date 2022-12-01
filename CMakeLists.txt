set(CPP_VERSION 20)

cmake_minimum_required(VERSION 3.21)
project(NP_Semesterprojekt)

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

add_executable(NP_Semesterprojekt
        src/main.cpp
        )

add_subdirectory(src)

target_include_directories(NP_Semesterprojekt
        PUBLIC src)

target_link_libraries(NP_Semesterprojekt
        ConveyorBelt
        Inventory
        Messages
        Item)