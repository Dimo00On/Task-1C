cmake_minimum_required(VERSION 3.24)
project(Task1C)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(SolutionFinder SHARED
        Graph.cpp
        Graph.h
        SolutionFinder.cpp
        SolutionFinder.h
        )

add_executable(Task1C main.cpp)

target_link_libraries(Task1C
        SolutionFinder
        )