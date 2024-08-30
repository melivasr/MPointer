#include "sortingAlgorithms.h"
#include "../doublyLinkedList/DoublyLinkedList.h"


template <typename T>
void BubbleSort<T>::sort(DoublyLinkedList<T>& list) {
    if (list.isEmpty()) return;

    bool swapped;
    do {
        swapped = false;
        MPointer<typename DoublyLinkedList<T>::Node> current = list.getHead();
        while (current->getNext()) {
            if (*current->data > *current->getNext()->data) {
                T temp = *current->data;
                *current->data = *current->getNext()->data;
                *current->getNext()->data = temp;
                swapped = true;
            }
            current = current->getNext();
        }
    } while (swapped);
}

// Instanciación explícita
template class BubbleSort<int>;
