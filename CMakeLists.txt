set(CPP_VERSION 20)

cmake_minimum_required(VERSION 3.21)
project(NP_Semesterprojekt)

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

include_directories(src)

add_executable(NP_Semesterprojekt
        src/main.cpp
        src/main.hpp)
