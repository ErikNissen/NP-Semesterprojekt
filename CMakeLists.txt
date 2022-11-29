set(CPP_VERSION 20)

cmake_minimum_required(VERSION 3.21)
project(NP_Semesterprojekt)

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

add_subdirectory(src/Inventory/inventoryLib)
add_subdirectory(src/Inventory/messagesLib)
add_subdirectory(src/Inventory/itemLib)

include_directories(src/Inventory/inventoryLib src/Inventory/messagesLib src/Inventory/itemLib)
link_libraries(src/Inventory/inventoryLib src/Inventory/messagesLib src/Inventory/itemLib)

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
