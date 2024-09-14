cmake_minimum_required(VERSION 3.28)
project(MPointerLibrary)

# Incluir los directorios de cabecera
include_directories(include)

# Crear la librería estática
add_library(MPointerLibrary STATIC
        source/MPointer.cpp
        source/MPointerGC.cpp
        source/LinkedList.cpp
        headers/MPointer.h
        headers/MPointerGC.h
        headers/LinkedList.h
)

# Encontrar GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Añadir los tests
set(TEST_SOURCES
        tests/MPointerTest.cpp
        tests/MPointerGCTest.cpp
)

# Ejecutable para los tests
add_executable(runTests ${TEST_SOURCES})

# Enlazar la librería con los tests
target_link_libraries(runTests PRIVATE MPointerLibrary GTest::GTest GTest::Main)

# Registrar tests
add_test(NAME runTests COMMAND runTests)
