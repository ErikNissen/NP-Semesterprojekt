add_library(Inventory
        Inventory.cpp
        ShelfPair.cpp
        Shelf.cpp
        ShelfContainer.cpp ContainerUse.cpp ContainerUse.h)

target_include_directories(Inventory
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})