cmake_minimum_required(VERSION 3.28)
project(MPointerProject)

set(CMAKE_CXX_STANDARD 17)

# Habilitar testing
enable_testing()

# Añadir subdirectorios
add_subdirectory(library)
add_subdirectory(app)
