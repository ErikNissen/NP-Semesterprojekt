set(CPP_VERSION 20)

cmake_minimum_required(VERSION 3.21)
project(NP_Semesterprojekt)

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

include_directories(src)

add_executable(NP_Semesterprojekt
        src/main.cpp
        src/main.hpp src/PersistentFileManagement/json.cpp src/PersistentFileManagement/json.hpp)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        GIT_TAG v3.11.2)

FetchContent_MakeAvailable(json)

target_link_libraries(NP_Semesterprojekt PRIVATE
        nlohmann_json::nlohmann_json)