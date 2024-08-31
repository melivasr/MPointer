cmake_minimum_required(VERSION 3.28)
project(MPointerProject)

set(CMAKE_CXX_STANDARD 17)

# Aplicación principal
add_executable(MPointer
        library/source/MPointer.cpp
        library/source/MPointerGC.cpp
        examples/main.cpp
        library/doublyLinkedList/DoublyLinkedList.cpp
        library/sortingAlgorithms/BubbleSort.cpp
        library/sortingAlgorithms/InsertionSort.cpp
)

# Encontrar y enlazar GTest para pruebas unitarias
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Ejecutable para las pruebas unitarias
add_executable(runTests
        tests/MPointerTest.cpp
        library/source/MPointer.cpp
        library/source/MPointerGC.cpp
        library/doublyLinkedList/DoublyLinkedList.cpp
        library/sortingAlgorithms/BubbleSort.cpp
        library/sortingAlgorithms/InsertionSort.cpp
        tests/MPointerGCTest.cpp
        tests/DoublyLinkedListTest.cpp
        tests/SortingAlgorithmsTest.cpp
)

# Enlazar con GTest y pthread
target_link_libraries(runTests GTest::gtest_main GTest::gtest pthread)

# Añadir las pruebas para que se ejecuten con `ctest`
add_test(NAME runTests COMMAND runTests)
