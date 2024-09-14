#include "../headers/LinkedList.h"

#include "../../app/doublyLinkedList/DoublyLinkedList.h"

// Constructor
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;  // Elimina el nodo actual
        current = next;  // Avanza al siguiente nodo
    }
}

// Agrega un nodo al final de la lista
template <typename T>
void LinkedList<T>::add(T* data) {
    Node* newNode = new Node(data);  // Crea un nuevo nodo
    if (!head) {
        head = tail = newNode;  // Si la lista está vacía, el nuevo nodo es la cabeza y la cola
    } else {
        tail->next = newNode;  // Agrega el nuevo nodo al final de la lista
        newNode->prev = tail;
        tail = newNode;  // Actualiza la cola
    }
}

// Remueve un nodo específico de la lista
template <typename T>
void LinkedList<T>::remove(Node* node) {
    std::cout << "Eliminando nodo con datos: " << *(node->data) << std::endl;
    if (node == head) {
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
    } else if (node == tail) {
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    delete node;
}

// Busca un nodo que contenga el puntero 'data'
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::find(T* data) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            return current;  // Retorna el nodo si encuentra el dato
        }
        current = current->next;  // Avanza al siguiente nodo
    }
    return nullptr;  // Retorna nullptr si no encuentra el dato
}

// Obtiene la cabeza de la lista
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() const {
    return head;  // Retorna la cabeza de la lista
}

// Instanciación explícita de la plantilla
template class LinkedList<int>;
template class LinkedList<MPointer<int>>;
template class LinkedList<MPointer<typename LinkedList<int>::Node>>;
template class LinkedList<MPointer<double>>;
template class LinkedList<MPointer<std::string>>;
template class LinkedList<MPointer<typename DoublyLinkedList<int>::Node>>;
template class LinkedList<MPointer<long>>;
template class LinkedList<MPointer<bool>>;
template class LinkedList<MPointer<float>>;
template class LinkedList<MPointer<char>>;
