#include <iostream>
#include "DoublyLinkedList.h"
#include "sortingAlgorithms.h"

int main() {
    // Crear una lista doblemente enlazada de enteros
    DoublyLinkedList<int> list;

    // Añadir algunos elementos a la lista
    list.append(5);
    list.append(3);
    list.append(9);
    list.append(1);
    list.append(7);

    // Mostrar la lista original
    std::cout << "Lista original:" << std::endl;
    list.display();

    // Crear instancias de los algoritmos de ordenamiento
    BubbleSort<int> bubbleSort;
    InsertionSort<int> insertionSort;
    QuickSort<int> quickSort;

    // Realizar Bubble Sort y mostrar el resultado
    bubbleSort.sort(list);
    std::cout << "Lista ordenada con Bubble Sort:" << std::endl;
    list.display();

    // Volver a insertar los elementos en la lista (en orden aleatorio)
    list.remove(5); list.append(5);
    list.remove(3); list.append(3);
    list.remove(9); list.append(9);
    list.remove(1); list.append(1);
    list.remove(7); list.append(7);

    // Realizar Insertion Sort y mostrar el resultado
    insertionSort.sort(list);
    std::cout << "Lista ordenada con Insertion Sort:" << std::endl;
    list.display();

    // Volver a insertar los elementos en la lista (en orden aleatorio)
    list.remove(5); list.append(5);
    list.remove(3); list.append(3);
    list.remove(9); list.append(9);
    list.remove(1); list.append(1);
    list.remove(7); list.append(7);

    // Realizar Quick Sort y mostrar el resultado
    quickSort.sort(list);
    std::cout << "Lista ordenada con Quick Sort:" << std::endl;
    list.display();

    // Pruebas adicionales para verificar el manejo de MPointer
    MPointer<int> testPointer = MPointer<int>::New();
    *testPointer = 42;
    std::cout << "Valor de testPointer: " << *testPointer << std::endl;

    // Simulación de uso de múltiples referencias a MPointer
    MPointer<int> testPointer2 = testPointer;
    std::cout << "Valor de testPointer2 (copia de testPointer): " << *testPointer2 << std::endl;

    return 0;
}
