add_library(PersistentFileManagement
        PersistentFileManagement.cpp
        )

target_include_directories(PersistentFileManagement
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(PersistentFileManagement
        nlohmann_json::nlohmann_json
        )