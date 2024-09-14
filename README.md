# MPointer

Este proyecto consiste en el diseño e implementación de un nuevo tipo de dato en C++ denominado `MPointer`, que encapsula punteros tradicionales y gestiona automáticamente la memoria mediante un recolector de basura (`MPointerGC`). El objetivo principal es evitar problemas comunes en la gestión manual de memoria, como los `memory leaks` y punteros colgantes.

## Tabla de Contenidos
1. [Descripción del Proyecto](#descripción-del-proyecto)
2. [Funcionalidades](#funcionalidades)
3. [Instalación](#instalación)
4. [Uso](#uso)


## Descripción del Proyecto

`MPointer<T>` es una clase template que encapsula un puntero de tipo `T*` y gestiona su ciclo de vida mediante un recolector de basura llamado `MPointerGC`. El recolector de basura se ejecuta periódicamente en un hilo independiente, liberando la memoria de los punteros que ya no tienen referencias activas, eliminando así posibles fugas de memoria.

Además de la gestión de memoria, el proyecto incluye la implementación de algoritmos de ordenamiento como QuickSort, BubbleSort e InsertionSort utilizando listas doblemente enlazadas que emplean `MPointer` para manejar los nodos.

## Funcionalidades

- **Encapsulación de punteros**: `MPointer<T>` reemplaza el uso de punteros tradicionales (`int*`, `char*`, `bool*`, etc.) en C++ con `MPointer<int>`, `MPointer<char>`, `MPointer<bool>`, y otros tipos.
- **Gestión automática de memoria**: A través de `MPointerGC`, el sistema se encarga de liberar memoria cuando ya no es utilizada.
- **Recolector de basura**: `MPointerGC` gestiona las instancias de `MPointer` y monitorea el ciclo de vida de los objetos.
- **Algoritmos de ordenamiento**: Implementación de QuickSort, BubbleSort e InsertionSort, con listas doblemente enlazadas utilizando `MPointer`.
- **Pruebas unitarias**: El proyecto incluye pruebas unitarias Google Test (`GTest`).

## Instalación

> **Nota**: Este proyecto fue desarrollado y probado en un sistema Linux. Los pasos de instalación pueden variar ligeramente en Windows. Se recomienda usar `MinGW` o `Cygwin` para entornos de desarrollo C++ en Windows.

Para compilar y ejecutar este proyecto, sigue los siguientes pasos:

1. Clona este repositorio en tu máquina local:

    ```bash
    git clone https://github.com/melivasr/MPointer.git
    ```

2. Asegúrate de tener instalado CMake y un compilador compatible con C++.

    - En Linux, puedes instalar CMake y un compilador con los siguientes comandos:

    ```bash
    sudo apt-get install cmake g++
    ```

    - En Windows, puedes descargar CMake desde [su sitio oficial](https://cmake.org/download/) e instalarlo junto con un compilador como `MinGW` o utilizar herramientas como Visual Studio.

3. Genera los archivos de compilación con CMake

4. Compila el proyecto

5. Ejecuta las pruebas unitarias

## Uso

A continuación, se muestra un ejemplo básico de cómo utilizar `MPointer`:

```cpp
#include "MPointer.h"

int main() {
    // Crear un MPointer que encapsula un int
    MPointer<int> myPtr = MPointer<int>::New();
    
    // Asignar un valor al puntero
    *myPtr = 5;
    
    // Obtener el valor del puntero
    int valor = *myPtr;
    
    // Asignar una nueva referencia
    MPointer<int> myPtr2 = MPointer<int>::New();
    myPtr2 = myPtr;

    return 0;
}
