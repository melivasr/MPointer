#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "../../library/headers/MPointer.h"
#include <iostream>

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T data;
        MPointer<Node> prev;
        MPointer<Node> next;

        // Constructor por defecto
        Node() : data(T()), prev(nullptr), next(nullptr) {}

        // Constructor con valor
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    MPointer<Node> head;
    MPointer<Node> tail;

    DoublyLinkedList();  // Constructor
    ~DoublyLinkedList();  // Destructor

    // Métodos de la lista
    void append(T value);
    void prepend(T value);
    void display() const;
    void remove(T value);
    bool isEmpty() const;
    T get(int index) const;
    void set(int index, T value);
    int size() const;

    // Métodos de acceso
    MPointer<Node> getHead() const;
    MPointer<Node> getTail() const;
};

// Definición del operador << como una plantilla global fuera de la clase
template <typename T>
std::ostream& operator<<(std::ostream& os, const typename DoublyLinkedList<T>::Node& node) {
    os << "Node data: " << node.data;
    return os;
}

#endif // DOUBLYLINKEDLIST_H
