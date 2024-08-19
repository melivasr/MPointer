#include "/home/mvasquezr/DatosII/MPointer/headers/MPointer.h"
#include <iostream>

int main() {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 10;
    std::cout << "Valor de ptr1: " << *ptr1 << std::endl;

    MPointer<int> ptr2 = ptr1; // Prueba de asignacion
    std::cout << "Valor de ptr2 (después de la asignación): " << *ptr2 << std::endl;

    ptr2 = 20; // Prueba de sobrecarga de operador =
    std::cout << "Nuevo valor de ptr1: " << *ptr1 << std::endl;
    std::cout << "Nuevo valor de ptr2: " << *ptr2 << std::endl;

    // Prueba de destruccion y recoleccion  de basura
    {
        MPointer<int> ptr3 = MPointer<int>::New();
        *ptr3 = 30;
        std::cout << "Valor de ptr3: " << *ptr3 << std::endl;
    } // Aqui ptr3 deberia ser recolectado por el GC

    // Prueba final
    std::cout << "Valor final de ptr1: " << *ptr1 << std::endl;

    return 0;
}

