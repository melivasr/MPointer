#include "../doublyLinkedList/DoublyLinkedList.h"
#include <iostream>

// Constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head) {
        MPointer<Node> temp = head;
        head = head->next;
        // El recolector de basura maneja la eliminación del nodo
    }
}

// Agregar al final de la lista
template <typename T>
void DoublyLinkedList<T>::append(T value) {
    MPointer<Node> newNode = MPointer<Node>::New();
    *newNode = Node(value);

    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
}

// Agregar al inicio de la lista
template <typename T>
void DoublyLinkedList<T>::prepend(T value) {
    MPointer<Node> newNode = MPointer<Node>::New();
    *newNode = Node(value);

    if (head) {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    } else {
        head = tail = newNode;
    }
}

// Eliminar un valor de la lista
template <typename T>
void DoublyLinkedList<T>::remove(T value) {
    MPointer<Node> current = head;
    while (current) {
        if (*current->data == value) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            return;
        }
        current = current->next;
    }
}

// Mostrar los elementos de la lista
template <typename T>
void DoublyLinkedList<T>::display() const {
    MPointer<Node> current = head;
    while (current) {
        std::cout << *current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Verificar si la lista está vacía
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

// Instanciación para el tipo int
template class DoublyLinkedList<int>;
