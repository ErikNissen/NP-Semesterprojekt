set(CPP_VERSION 20)

cmake_minimum_required(VERSION 3.21)
project(NP_Semesterprojekt)

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

add_executable(NP_Semesterprojekt
        src/main.cpp
        )

add_subdirectory(src)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        GIT_TAG v3.11.2)

FetchContent_MakeAvailable(json)

target_include_directories(NP_Semesterprojekt
        PUBLIC src)

target_link_libraries(NP_Semesterprojekt
        ConveyorBelt
        Inventory
        Messages
        Item
        nlohmann_json::nlohmann_json
        src/PersistentFileManagement/json.hpp)
