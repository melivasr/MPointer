#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointer.h"
#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointerGC.h"
#include "/home/mvasquezr/DatosII/MPointer/library/doublyLinkedList/DoublyLinkedList.h"
#include "/home/mvasquezr/DatosII/MPointer/library/sortingAlgorithms/sortingAlgorithms.h"
#include <iostream>


MPointer<int> foo() {
    MPointer<int> temp = MPointer<int>::New();
    *temp = 666;
    MPointerGC<int>::getInstance()->debug();
    return temp;
}

int main() {
    /*// Pruebas de MPointer
    MPointer<int> mp1 = MPointer<int>::New();
    MPointer<int> mp2 = MPointer<int>::New();
    *mp1 = 100;
    *mp2 = 200;

    foo();

    MPointerGC<int>::getInstance()->debug();

    mp2 = mp1;

    MPointerGC<int>::getInstance()->debug();*/

    // Pruebas de algoritmos de ordenamiento
    DoublyLinkedList<int> list;
    list.append(5);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);

    std::cout << "Lista original: ";
    list.display();

    // Prueba de BubbleSort
    BubbleSort<int> bubbleSort;
    bubbleSort.sort(list);
    std::cout << "Lista ordenada con BubbleSort: ";
    list.display();

    // Revertir la lista para la siguiente prueba
    list = DoublyLinkedList<int>();
    list.append(5);
    list.append(2);
    list.append(9);
    list.append(1);
    list.append(6);

    // Prueba de InsertionSort
    InsertionSort<int> insertionSort;
    insertionSort.sort(list);
    std::cout << "Lista ordenada con InsertionSort: ";
    list.display();

    return 0;

}


