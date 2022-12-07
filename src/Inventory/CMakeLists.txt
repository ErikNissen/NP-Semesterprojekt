add_library(Inventory
        Inventory.cpp
        ShelfPair.cpp
        Shelf.cpp
        Container.cpp
        Timer.cpp)

target_include_directories(Inventory
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})