cmake_minimum_required(VERSION 3.20)
project(Trees)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trees main.cpp)

add_subdirectory(benchmark-main)
target_link_libraries(Trees benchmark::benchmark)