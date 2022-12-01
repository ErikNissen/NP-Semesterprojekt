add_library(ConveyorBelt
        Container.cpp
        ConveyorBelt.cpp
        ConveyorBeltRetrieve.cpp
        ConveyorBeltStore.cpp
        Timer.cpp
        TransferPoint.cpp
        )

target_include_directories(ConveyorBelt
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})