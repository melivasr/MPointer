#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "../headers/MPointer.h"
#include <iostream>

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        MPointer<T> data;
        MPointer<Node> next;
        MPointer<Node> prev;

        Node() : data(nullptr), next(nullptr), prev(nullptr) {}
        Node(T value) : data(MPointer<T>::New()), next(nullptr), prev(nullptr) {
            *data = value;
        }

        // Métodos de acceso para `next` y `prev`
        MPointer<Node> getNext() const { return next; }
        MPointer<Node> getPrev() const { return prev; }
        MPointer<T> getData() const { return data; }

        // Sobrecarga del operador << para Node
        friend std::ostream& operator<<(std::ostream& os, const Node& node) {
            os << *(node.data); // Imprimir el valor almacenado en el MPointer
            return os;
        }
    };

    MPointer<Node> head;
    MPointer<Node> tail;

    DoublyLinkedList();
    ~DoublyLinkedList();
    void append(T value);
    void prepend(T value);
    void remove(T value);
    void display() const;
    bool isEmpty() const;

    // Métodos de acceso para head y tail
    MPointer<Node> getHead() const { return head; }
    MPointer<Node> getTail() const { return tail; }
};

#endif // DOUBLYLINKEDLIST_H
