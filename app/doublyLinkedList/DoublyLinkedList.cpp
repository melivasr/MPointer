#include "DoublyLinkedList.h"
#include <iostream>

// Constructor: inicializa la cabeza y la cola en nullptr.
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Destructor: limpia todos los nodos de la lista.
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head) {
        MPointer<Node> temp = head;
        head = head->next;
        temp->next = nullptr;
        temp->prev = nullptr;
    }
    head = nullptr;
    tail = nullptr;
}

// Añade un valor al final de la lista.
template <typename T>
void DoublyLinkedList<T>::append(T value) {
    MPointer<Node> newNode = MPointer<Node>::New();
    newNode->data = value;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Añade un valor al inicio de la lista.
template <typename T>
void DoublyLinkedList<T>::prepend(T value) {
    MPointer<Node> newNode = MPointer<Node>::New();
    newNode->data = value;

    if (head) {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    } else {
        head = tail = newNode;
    }
}

// Elimina el primer nodo que contenga el valor dado.
template <typename T>
void DoublyLinkedList<T>::remove(T value) {
    MPointer<Node> currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data == value) {
            if (currentNode->prev != nullptr) {
                currentNode->prev->next = currentNode->next;
            } else {
                head = currentNode->next;
            }
            if (currentNode->next != nullptr) {
                currentNode->next->prev = currentNode->prev;
            } else {
                tail = currentNode->prev;
            }
            currentNode->next = nullptr;
            currentNode->prev = nullptr;
            return;
        }
        currentNode = currentNode->next;
    }
    std::cerr << "Valor no encontrado en la lista." << std::endl;
}
// Muestra los elementos de la lista en una sola línea, separados por comas
template <typename T>
void DoublyLinkedList<T>::display() const {
    MPointer<Node> current = head;
    bool first = true;  // Para controlar si es el primer elemento
    while (current != nullptr) {
        if (!first) {
            std::cout << ", ";  // Imprimir una coma antes de cada elemento, excepto el primero
        }
        std::cout << current->data;
        first = false;  // A partir del primer elemento, cambia el flag
        current = current->next;
    }
    std::cout << std::endl;  // Nueva línea al final
}

// Devuelve el valor en el índice especificado.
template <typename T>
T DoublyLinkedList<T>::get(int index) const {
    MPointer<Node> current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            return current->data;
        }
        current = current->next;
        count++;
    }
    std::cerr << "Índice no válido" << std::endl;
    return T();
}

// Modifica el valor en el índice especificado.
template <typename T>
void DoublyLinkedList<T>::set(int index, T value) {
    MPointer<Node> current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            current->data = value;
            return;
        }
        current = current->next;
        count++;
    }
    std::cerr << "Índice no válido" << std::endl;
}

// Retorna el tamaño de la lista.
template <typename T>
int DoublyLinkedList<T>::size() const {
    int count = 0;
    MPointer<Node> current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Instanciaciones explícitas
template class DoublyLinkedList<int>;
template class MPointer<DoublyLinkedList<int>::Node>;
