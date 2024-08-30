cmake_minimum_required(VERSION 3.28)
project(library/headers)

set(CMAKE_CXX_STANDARD 17)

add_executable(MPointer library/source/MPointer.cpp
        library/source/MPointerGC.cpp
        library/headers/MPointerGC.h
        library/headers/MPointer.h
        examples/main.cpp
        library/doublyLinkedList/DoublyLinkedList.cpp
        library/doublyLinkedList/DoublyLinkedList.h
        library/sortingAlgorithms/BubbleSort.cpp
        library/sortingAlgorithms/sortingAlgorithms.h)
