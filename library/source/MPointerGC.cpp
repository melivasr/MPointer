#include "../../library/headers/MPointer.h"
#include "../../library/headers/MPointerGC.h"
#include "../headers/LinkedList.h"

#include <iostream>


template <typename T>
MPointerGC<T>* MPointerGC<T>::instance = nullptr;

template <typename T>
MPointerGC<T>::MPointerGC() : running(true), nextId(0), gcThread(&MPointerGC<T>::runGC, this) {
}

template <typename T>
MPointerGC<T>::~MPointerGC() {
    running = false;
    if (gcThread.joinable()) {
        gcThread.join();  // Espera a que el hilo termine
    }
}

template <typename T>
MPointerGC<T>* MPointerGC<T>::getInstance() {
    if (!instance) {
        instance = new MPointerGC<T>();
    }
    return instance;
}

template <typename T>
int MPointerGC<T>::generateId() {
    std::lock_guard<std::mutex> lock(mtx);
    return nextId++;
}

template <typename T>
void MPointerGC<T>::addPointer(MPointer<T>* mp) {
    std::lock_guard<std::mutex> lock(mtx);  // Asegura acceso exclusivo a la lista
    pointersList.add(mp);  // Agrega el puntero MPointer<T> a la lista doblemente enlazada
}


template <typename T>
void MPointerGC<T>::removePointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();
    while (node != nullptr) {
        if (node->data->getId() == id) {
            pointersList.remove(node);  // Elimina el nodo de la lista
            break;
        }
        node = node->next;
    }
}
template <typename T>
void MPointerGC<T>::incrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();
    while (node != nullptr) {
        if (node->data->getId() == id) {
            node->refCount++;
            std::cout << "Incrementando referencia del ID: " << id << ", nuevo refCount: " << node->refCount << std::endl;
            break;
        }
        node = node->next;
    }
}

template <typename T>
void MPointerGC<T>::decrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();
    while (node != nullptr) {
        if (node->data->getId() == id) {
            node->refCount--;  // Decrementa el contador de referencias
            if (node->refCount == 0) {  // Solo elimina si el contador llega a 0
                std::cout << "Referencia del ID: " << id << " llegó a 0, eliminando nodo" << std::endl;
                delete node->data;  // Libera la memoria del MPointer
                pointersList.remove(node);  // Elimina el nodo de la lista
            } else {
                std::cout << "Decrementando referencia del ID: " << id << ", refCount actual: " << node->refCount << std::endl;
            }
            break;
        }
        node = node->next;
    }
}

template <typename T>
void MPointerGC<T>::debug() {
    std::lock_guard<std::mutex> lock(mtx);
    auto node = pointersList.getHead();
    while (node != nullptr) {
        std::cout << "ID: " << node->data->getId()
                  << " Value: " << **node->data
                  << " RefCount: " << node->refCount
                  << " Address: " << node->data->operator&()
                  << std::endl;
        node = node->next;
    }
}

template <typename T>
void MPointerGC<T>::runGC(MPointerGC* mp){
    while (mp->running) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::lock_guard<std::mutex> lock(mp->mtx);
        auto node = mp->pointersList.getHead();
        while (node != nullptr) {
            if (node->refCount == 0) {
                delete node->data;
                auto temp = node->next;  // Guardar el siguiente nodo antes de eliminar
                mp->pointersList.remove(node);
                node = temp;  // Continuar con el siguiente nodo
            } else {
                node = node->next;
            }
        }
    }
}

template class MPointerGC<int>;
template class MPointerGC<LinkedList<int>::Node>;
template class MPointerGC<double>;
template class MPointerGC<std::string>;