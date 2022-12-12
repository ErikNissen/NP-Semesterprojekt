add_library(
        PersistentFileManagement
        PersistentFileManagement.hpp
)

target_include_directories(
        PersistentFileManagement PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)



target_link_libraries(
        PersistentFileManagement
)