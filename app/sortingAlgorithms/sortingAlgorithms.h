// sortingAlgorithms.h
#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H

#include "../../app/doublyLinkedList/DoublyLinkedList.h"

template <typename T>
class SortingAlgorithm {
public:
    virtual void sort(DoublyLinkedList<T>& list) = 0;
    virtual ~SortingAlgorithm() = default;
};

// Bubble Sort
template <typename T>
class BubbleSort : public SortingAlgorithm<T> {
public:
    void sort(DoublyLinkedList<T>& list) override;
};

// Implementación de BubbleSort
template <typename T>
void BubbleSort<T>::sort(DoublyLinkedList<T>& list) {
    int n = list.size();  // Obtener el tamaño de la lista
    if (n <= 1) return;   // Si la lista está vacía o tiene un solo elemento, no necesita ordenarse

    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (list.get(i) > list.get(i + 1)) {
                T temp = list.get(i);
                list.set(i, list.get(i + 1));
                list.set(i + 1, temp);
                swapped = true;
            }
        }
        n--;  // Reduce el rango a ordenar
    } while (swapped);
}


// Insertion Sort
template <typename T>
class InsertionSort : public SortingAlgorithm<T> {
public:
    void sort(DoublyLinkedList<T>& list) override;
};

// Implementación de InsertionSort
template <typename T>
void InsertionSort<T>::sort(DoublyLinkedList<T>& list) {
    int n = list.size();
    if (n <= 1) return;  // No hay necesidad de ordenar una lista vacía o con un solo elemento

    for (int i = 1; i < n; ++i) {
        T key = list.get(i);
        int j = i - 1;

        // Mueve los elementos que son mayores que `key` una posición adelante
        while (j >= 0 && list.get(j) > key) {
            list.set(j + 1, list.get(j));
            j--;
        }
        list.set(j + 1, key);  // Inserta el elemento en su lugar
    }
}


// Quick Sort
template <typename T>
class QuickSort : public SortingAlgorithm<T> {
public:
    void sort(DoublyLinkedList<T>& list) override;
private:
    int partition(DoublyLinkedList<T>& list, int low, int high);
    void quickSort(DoublyLinkedList<T>& list, int low, int high);
};

// Implementación de QuickSort
template <typename T>
int QuickSort<T>::partition(DoublyLinkedList<T>& list, int low, int high) {
    T pivot = list.get(low);  // Usamos el elemento en la posición `low` como pivote
    int left = low + 1;
    int right = high;

    while (left <= right) {
        while (left <= right && list.get(left) <= pivot) {
            left++;
        }
        while (left <= right && list.get(right) > pivot) {
            right--;
        }
        if (left < right) {
            T temp = list.get(left);
            list.set(left, list.get(right));
            list.set(right, temp);
        }
    }
    T temp = list.get(low);
    list.set(low, list.get(right));
    list.set(right, temp);

    return right;  // Devuelve la nueva posición del pivote
}

template <typename T>
void QuickSort<T>::quickSort(DoublyLinkedList<T>& list, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(list, low, high);
        quickSort(list, low, pivotIndex - 1);
        quickSort(list, pivotIndex + 1, high);
    }
}

template <typename T>
void QuickSort<T>::sort(DoublyLinkedList<T>& list) {
    int n = list.size();  // Obtener el tamaño de la lista
    if (n > 1) {
        quickSort(list, 0, n - 1);  // Iniciar el QuickSort desde el primer hasta el último elemento
    }
}

#endif // SORTINGALGORITHM_H
