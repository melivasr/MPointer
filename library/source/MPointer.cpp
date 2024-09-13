#include "../../library/headers/MPointer.h"
#include "../../library/headers/MPointerGC.h"
#include "../headers/LinkedList.h"
template <typename T>
MPointerGC<T>* MPointer<T>::gc = MPointerGC<T>::getInstance();

template <typename T>
MPointer<T>::MPointer() : pointer(nullptr), id(-1) {
    id = gc->generateId();
    gc->addPointer(this);
}

template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) : pointer(other.pointer), id(other.id) {
    gc->incrementRefCount(id);
}

template <typename T>
MPointer<T>::MPointer(std::nullptr_t) : pointer(nullptr), id(-1) {}

template <typename T>
MPointer<T>::~MPointer() {
    if (id != -1) {
        gc->decrementRefCount(id);  // El recolector maneja la eliminación de memoria
    }
}


template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T>* mp = new MPointer<T>();  // Crea un objeto MPointer en el heap

    mp->pointer = new T();  // Reserva memoria para el objeto de tipo T

    mp->id = gc->generateId();  // Genera un nuevo ID para este MPointer

    gc->addPointer(mp);  // Añade el puntero de MPointer al recolector de basura

    return *mp;  // Devuelve el objeto MPointer por valor
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        // Si este puntero ya tiene una referencia asignada, decrementa su contador de referencias
        if (id != -1) {
            std::cout << "Decrementando referencia del ID: " << id << std::endl;
            gc->decrementRefCount(id);
        }
        // Copia el puntero y el ID del otro MPointer
        pointer = other.pointer;
        id = other.id;

        // Incrementa el contador de referencias del nuevo puntero
        if (id != -1) {
            std::cout << "Incrementando referencia del nuevo ID: " << id << std::endl;
            gc->incrementRefCount(id);
        }
    }
    return *this;
}


template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    if (!pointer) {
        pointer = new T(value);  // Usa el constructor que acepta un argumento
        id = gc->generateId();
        gc->addPointer(this);
    } else {
        *pointer = value;  // Si el puntero ya existe, simplemente asigna el valor
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(std::nullptr_t) {
    if (id != -1) {
        std::cout << "Decrementando referencia del ID: " << id << std::endl;
        gc->decrementRefCount(id);
    }
    pointer = nullptr;
    id = -1;  // Invalidamos el ID porque el puntero ya no apunta a ningún objeto válido
    return *this;
}


template <typename T>
bool MPointer<T>::operator==(std::nullptr_t) const {
    return pointer == nullptr;
}

template <typename T>
bool MPointer<T>::operator!=(std::nullptr_t) const {
    return pointer != nullptr;
}

template <typename T>
T& MPointer<T>::operator*() const {
    return *pointer;
}


template <typename T>
T* MPointer<T>::operator&() {
    return pointer;
}

template <typename T>
T* MPointer<T>::operator->() const {
    return pointer;
}

template <typename T>
MPointer<T>::operator bool() const {
    return pointer != nullptr;
}

template <typename T>
int MPointer<T>::getId() const {
    return id;
}

template class MPointer<int>;
template class MPointer<LinkedList<int>::Node>;
template class MPointer<double>;
template class MPointer<std::string>;