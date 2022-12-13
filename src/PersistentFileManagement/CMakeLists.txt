add_library(
        PersistentFileManagement
        PersistentFileManagement.cpp
        PersistentFileManagement.hpp
)



target_include_directories(
        PersistentFileManagement PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
