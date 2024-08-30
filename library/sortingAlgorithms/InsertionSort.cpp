#include "sortingAlgorithms.h"
#include "../doublyLinkedList/DoublyLinkedList.h"

template <typename T>
void InsertionSort<T>::sort(DoublyLinkedList<T>& list) {
    if (list.isEmpty()) return;

    MPointer<typename DoublyLinkedList<T>::Node> current = list.getHead()->getNext();

    while (current != nullptr) {
        T key = *current->getData();
        MPointer<typename DoublyLinkedList<T>::Node> prev = current->getPrev();

        while (prev != nullptr && *prev->getData() > key) {
            *prev->getNext()->getData() = *prev->getData();
            prev = prev->getPrev();
        }

        if (prev == nullptr) {
            *list.getHead()->getData() = key;
        } else {
            *prev->getNext()->getData() = key;
        }

        current = current->getNext();
    }
}

// Instanciación explícita
template class InsertionSort<int>;
