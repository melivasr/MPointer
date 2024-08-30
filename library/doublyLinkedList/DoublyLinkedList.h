#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "../headers/MPointer.h"

#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        MPointer<T> data;
        MPointer<Node> next;
        MPointer<Node> prev;

        Node() : data(nullptr), next(nullptr), prev(nullptr) {}
        Node(T value) : data(MPointer<T>::New()), next(nullptr), prev(nullptr) {
            *data = value;
        }

        // Sobrecarga del operador << para Node
        friend std::ostream& operator<<(std::ostream& os, const Node& node) {
            os << *(node.data); // Imprimir el valor almacenado en el MPointer
            return os;
        }
    };

    MPointer<Node> head;
    MPointer<Node> tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void append(T value);
    void prepend(T value);
    void remove(T value);
    void display() const;
    bool isEmpty() const;
};

#endif // DOUBLYLINKEDLIST_H

