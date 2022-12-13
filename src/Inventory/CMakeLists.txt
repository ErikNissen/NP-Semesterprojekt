add_library(Inventory
        Inventory.cpp
        ShelfPair.cpp
        Shelf.cpp
        Segment.cpp
        )

target_include_directories(Inventory
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Inventory
        Item
        PersistentFileManagement
        )

