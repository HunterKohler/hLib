cmake_minimum_required(VERSION 3.19.7)

project(Wargames-Library VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Catch2 2.13.4 REQUIRED)

add_executable(test src/des/test.cpp)

target_link_libraries(test PRIVATE Catch2::Catch2)
