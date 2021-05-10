cmake_minimum_required(VERSION 3.0.0)
project(MyRegex 
        VERSION 0.1.0
        DESCRIPTION "Just trying to parse regex."
        LANGUAGES CXX)


include(CTest)
enable_testing()

add_executable(MyRegex src/main.cpp)

include(CPack)
