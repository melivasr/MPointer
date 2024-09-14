#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "MPointer.h"

// Declaración anticipada de MPointer para evitar dependencias
template <typename T>
class MPointer;

template <typename T>
class LinkedList {
public:
    struct Node {
        T* data;  // Puntero al dato
        int refCount;  // Conteo de referencias
        Node* prev;  // Puntero al nodo anterior
        Node* next;  // Puntero al siguiente nodo

        Node() : data(nullptr), refCount(1), prev(nullptr), next(nullptr) {}

        Node(T* data) : data(data), refCount(1), prev(nullptr), next(nullptr) {}

        // Sobrecarga del operador << para imprimir el contenido del nodo
        friend std::ostream& operator<<(std::ostream& os, const Node& node) {
            if (node.data) {
                os << *(node.data);
            } else {
                os << "null";
            }
            return os;
        }
    };

    LinkedList();  // Constructor
    ~LinkedList();  // Destructor

    void add(T* data);  // Agrega un nodo al final de la lista
    void remove(Node* node);  // Remueve un nodo específico
    Node* find(T* data);  // Busca un nodo que contenga el puntero 'data'
    Node* getHead() const;  // Obtiene la cabeza de la lista

private:
    Node* head;  // Puntero a la cabeza de la lista
    Node* tail;  // Puntero a la cola de la lista
};

#endif // LINKEDLIST_H
