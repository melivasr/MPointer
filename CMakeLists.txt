cmake_minimum_required(VERSION 3.28)
project(headers)

set(CMAKE_CXX_STANDARD 17)

add_executable(MPointer source/MPointer.cpp
        source/MPointerGC.cpp
        headers/MPointerGC.h
        headers/MPointer.h
        examples/main.cpp)
