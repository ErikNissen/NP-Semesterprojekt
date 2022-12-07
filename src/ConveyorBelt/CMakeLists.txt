add_library(ConveyorBelt
        ConveyorBelt.cpp
        ConveyorBeltRetrieve.cpp
        ConveyorBeltStore.cpp
        TransferPoint.cpp
        Container.cpp)

target_include_directories(ConveyorBelt
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})