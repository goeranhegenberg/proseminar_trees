cmake_minimum_required(VERSION 3.20)
project(Trees)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trees main.cpp UBTree.h Utils.cpp BTree.h)

add_subdirectory(benchmark-main)
include_directories(./include/interval-tree)
target_link_libraries(Trees benchmark::benchmark)