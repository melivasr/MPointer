#include "../headers/MPointerGC.h"
#include "../doublyLinkedList/DoublyLinkedList.h"

// Inicializar el recolector de basura
template <typename T>
MPointerGC<T>* MPointerGC<T>::instance = nullptr;

// Constructor
template <typename T>
MPointerGC<T>::MPointerGC() {}

// Obtener instancia del recolector de basura
template <typename T>
MPointerGC<T>* MPointerGC<T>::getInstance() {
    if (!instance) {
        instance = new MPointerGC<T>();
    }
    return instance;
}

// Agregar un nuevo MPointer
template <typename T>
void MPointerGC<T>::addPointer(MPointer<T>* mp) {
    std::lock_guard<std::mutex> lock(mtx);
    pointers.push_back(mp);
}

// Eliminar un MPointer
template <typename T>
void MPointerGC<T>::removePointer(MPointer<T>* mp) {
    std::lock_guard<std::mutex> lock(mtx);
    pointers.remove(mp);
}

// Ejecutar el recolector de basura de manera periódica para liberar memoria
template <typename T>
void MPointerGC<T>::runGC() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Esperar 5 segundos
        std::lock_guard<std::mutex> lock(mtx);
        for (auto it = pointers.begin(); it != pointers.end(); ) {
            if ((*it)->getRefCount() == 0) {
                delete *it;  // Liberar la memoria
                it = pointers.erase(it);  // Eliminar el puntero
            } else {
                ++it;  // Avanzar al siguiente elemento
            }
        }
    }
}

template class MPointerGC<int>;

template class MPointerGC<DoublyLinkedList<int>::Node>;
