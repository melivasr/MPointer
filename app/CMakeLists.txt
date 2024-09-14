cmake_minimum_required(VERSION 3.28)
project(MPointerApp)

set(CMAKE_CXX_STANDARD 17)

# Incluir los directorios de encabezados
include_directories(${CMAKE_SOURCE_DIR}/library/headers)
include_directories(${CMAKE_SOURCE_DIR}/app/doublyLinkedList)
include_directories(${CMAKE_SOURCE_DIR}/app/sortingAlgorithms)

# Añadir todas las fuentes necesarias
add_executable(MPointerApp
        main.cpp
        doublyLinkedList/DoublyLinkedList.cpp
)

# Enlazar la librería estática
target_link_libraries(MPointerApp PRIVATE MPointerLibrary)
