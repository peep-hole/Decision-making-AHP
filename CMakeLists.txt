cmake_minimum_required(VERSION 3.0.0)
project(Decision-making-AHP VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Decision-making-AHP src/main.cpp)

target_include_directories(Decision-making-AHP PUBLIC vendor)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
