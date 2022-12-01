add_library(Item
        Item.cpp
        Priority.cpp
        )

target_include_directories(Item
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})