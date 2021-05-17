cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(hlib VERSION 0.0.1)

add_executable(src src/main.cpp)

target_compile_options(src PRIVATE -Wno-subobject-linkage -Wall -Wextra -pedantic)
