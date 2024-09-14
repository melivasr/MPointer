#include "../../library/headers/MPointer.h"
#include "../../library/headers/MPointerGC.h"
#include "../headers/LinkedList.h"
#include "../../app/doublyLinkedList/DoublyLinkedList.h"

#include <iostream>

// Inicialización de la instancia de MPointerGC a nullptr
template <typename T>
MPointerGC<T>* MPointerGC<T>::instance = nullptr;

// Constructor que inicia el recolector de basura en un hilo separado
template <typename T>
MPointerGC<T>::MPointerGC() : running(true), nextId(0), gcThread(&MPointerGC<T>::runGC, this) {}

// Destructor que detiene el recolector de basura
template <typename T>
MPointerGC<T>::~MPointerGC() {
    running = false;
    if (gcThread.joinable()) {
        gcThread.join();  // Espera a que el hilo termine
    }
}

// Obtiene la instancia única de MPointerGC (patrón singleton)
template <typename T>
MPointerGC<T>* MPointerGC<T>::getInstance() {
    if (!instance) {
        instance = new MPointerGC<T>();
    }
    return instance;
}

// Genera un nuevo ID único
template <typename T>
int MPointerGC<T>::generateId() {
    std::lock_guard<std::mutex> lock(mtx);
    return nextId++;
}

// Agrega un MPointer a la lista de punteros a gestionar
template <typename T>
void MPointerGC<T>::addPointer(MPointer<T>* mp) {
    std::lock_guard<std::mutex> lock(mtx);  // Asegura acceso exclusivo
    pointersList.add(mp);
}

// Remueve un MPointer de la lista usando su ID
template <typename T>
void MPointerGC<T>::removePointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();
    while (node != nullptr) {
        if (node->data->getId() == id) {
            pointersList.remove(node);  // Elimina el nodo
            break;
        }
        node = node->next;
    }
}

// Incrementa el contador de referencias de un MPointer
template <typename T>
void MPointerGC<T>::incrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();
    while (node != nullptr) {
        if (node->data->getId() == id) {
            node->refCount++;
            break;
        }
        node = node->next;
    }
}

// Decrementa el contador de referencias y elimina si llega a 0
template <typename T>
void MPointerGC<T>::decrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();
    while (node != nullptr) {
        if (node->data->getId() == id) {
            node->refCount--;
            if (node->refCount == 0) {
                delete node->data;  // Libera la memoria
                pointersList.remove(node);  // Elimina el nodo
            }
            break;
        }
        node = node->next;
    }
}

// Muestra información de los MPointer gestionados
template <typename T>
void MPointerGC<T>::debug() {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();

    while (node != nullptr) {
        std::cout << "ID: " << node->data->getId()  // Muestra ID, valor y contador de referencias
                  << " Value: " << *node->data
                  << " RefCount: " << node->refCount
                  << " Address: " << &(*node->data)
                  << std::endl;
        node = node->next;
    }
}

// Hilo del recolector de basura que elimina MPointers con refCount 0
template <typename T>
void MPointerGC<T>::runGC(MPointerGC* mp){
    while (mp->running) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::lock_guard<std::mutex> lock(mp->mtx);
        auto node = mp->pointersList.getHead();
        while (node != nullptr) {
            if (node->refCount == 0) {
                delete node->data;  // Libera la memoria
                auto temp = node->next;
                mp->pointersList.remove(node);  // Elimina el nodo
                node = temp;
            } else {
                node = node->next;
            }
        }
    }
}

// Instanciaciones explícitas
template class MPointerGC<int>;
template class MPointerGC<LinkedList<int>::Node>;
template class MPointerGC<double>;
template class MPointerGC<std::string>;
template class MPointerGC<DoublyLinkedList<int>::Node>;
