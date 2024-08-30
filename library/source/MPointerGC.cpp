#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointer.h"
#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointerGC.h"
#include "/home/mvasquezr/DatosII/MPointer/library/doublyLinkedList/DoublyLinkedList.h"
#include <iostream>

template <typename T>
MPointerGC<T>* MPointerGC<T>::instance = nullptr;

template <typename T>
MPointerGC<T>::MPointerGC() : running(true), nextId(0), gcThread(&MPointerGC::runGC, this) {}

template <typename T>
MPointerGC<T>::~MPointerGC() {
    running = false;
    if (gcThread.joinable()) {
        gcThread.join();
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
    std::lock_guard<std::mutex> lock(mtx);
    pointers[mp->getId()] = mp;
    refCounts[mp->getId()] = 1;
}

template <typename T>
void MPointerGC<T>::removePointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    pointers.erase(id);
    refCounts.erase(id);
}

template <typename T>
void MPointerGC<T>::incrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    refCounts[id]++;
}

template <typename T>
void MPointerGC<T>::decrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    if (--refCounts[id] == 0) {
        delete pointers[id];
        removePointer(id);
    }
}

template <typename T>
void MPointerGC<T>::debug() {
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& pair : pointers) {
        int id = pair.first;
        MPointer<T>* mp = pair.second;
        std::cout << "ID: " << id
                  << " Value: " << **mp  // Mostrar el valor almacenado en el nodo
                  << " RefCount: " << refCounts[id]
                  << " Address: " << mp->operator&()
                  << std::endl;
    }
}

template <typename T>
void MPointerGC<T>::runGC() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::lock_guard<std::mutex> lock(mtx);
        for (auto it = pointers.begin(); it != pointers.end(); ) {
            if (refCounts[it->first] == 0) {
                delete it->second;
                it = pointers.erase(it);
            } else {
                ++it;
            }
        }
    }
}

template class MPointerGC<int>;
// Instanciación de MPointerGC para el tipo Node de DoublyLinkedList<int>
template class MPointerGC<DoublyLinkedList<int>::Node>;
