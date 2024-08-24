#include "/home/mvasquezr/DatosII/MPointer/headers/MPointer.h"
#include <iostream>

/*
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
*/
#include "/home/mvasquezr/DatosII/MPointer/doublyLinkedList/DoublyLinkedList.h"
#include <iostream>

int main() {
    DoublyLinkedList<int> list;

    // Prueba de inserción al final
    list.append(10);
    list.append(20);
    list.append(30);
    std::cout << "Lista después de agregar al final: ";
    list.display();

    // Prueba de inserción al inicio
    list.prepend(5);
    std::cout << "Lista después de agregar al inicio: ";
    list.display();

    // Prueba de eliminación
    list.remove(20);
    std::cout << "Lista después de eliminar 20: ";
    list.display();

    // Verificación si la lista está vacía
    if (list.isEmpty()) {
        std::cout << "La lista está vacía." << std::endl;
    } else {
        std::cout << "La lista no está vacía." << std::endl;
    }

    return 0;
}

