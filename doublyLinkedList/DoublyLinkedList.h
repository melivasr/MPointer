#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "../headers/MPointer.h"

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        MPointer<T> data;
        MPointer<Node> next;
        MPointer<Node> prev;

        // Constructor por defecto
        Node() : data(nullptr), next(nullptr), prev(nullptr) {}

        // Constructor que inicializa con un valor
        Node(T value) : data(MPointer<T>::New()), next(nullptr), prev(nullptr) {
            *data = value;
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

