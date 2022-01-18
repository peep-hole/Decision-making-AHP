cmake_minimum_required(VERSION 3.0.0)
project(Decision-making-AHP VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCES
    "src/main.cpp"
    "src/AHP/PriorityMatrix.cpp"
    "src/AHP/PriorityMatrix.hpp"
    "src/AHP/AHPSolver.cpp"
    "src/AHP/AHPSolver.hpp"
    "src/AHP/JsonContainer.cpp"
    "src/AHP/JsonContainer.hpp"
    "src/tests/ahpTests.cpp"
    "src/tests/ahpTests.h"
)

add_executable(Decision-making-AHP ${SOURCES})

target_include_directories(Decision-making-AHP PUBLIC vendor)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
