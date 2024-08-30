#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H

#include "../doublyLinkedList/DoublyLinkedList.h"

// Clase abstracta base para los algoritmos de ordenamiento
template <typename T>
class SortingAlgorithm {
public:
    virtual void sort(DoublyLinkedList<T>& list) = 0;
    virtual ~SortingAlgorithm() = default;
};

//Bubble Sort
template <typename T>
class BubbleSort : public SortingAlgorithm<T> {
public:
    void sort(DoublyLinkedList<T>& list) override;
};

//Insertion Sort
template <typename T>
class InsertionSort : public SortingAlgorithm<T> {
public:
    void sort(DoublyLinkedList<T>& list) override;
};

#endif // SORTINGALGORITHM_H

