#include "../../library/headers/MPointer.h"
#include "../../library/headers/MPointerGC.h"
#include "../headers/LinkedList.h"
#include "../../app/doublyLinkedList/DoublyLinkedList.h"

// Inicialización del recolector de basura
template <typename T>
MPointerGC<T>* MPointer<T>::gc = MPointerGC<T>::getInstance();

// Constructor por defecto
template <typename T>
MPointer<T>::MPointer() : pointer(nullptr), id(-1) {
    id = gc->generateId();  // Genera un ID único
    gc->addPointer(this);   // Anade el MPointer al recolector de basura
}

// Constructor de copia
template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) : pointer(other.pointer), id(other.id) {
    gc->incrementRefCount(id);  // Incrementa el contador de referencias
}

// Constructor que acepta nullptr
template <typename T>
MPointer<T>::MPointer(std::nullptr_t) : pointer(nullptr), id(-1) {}

// Destructor
template <typename T>
MPointer<T>::~MPointer() {
    if (id != -1) {
        gc->decrementRefCount(id);  // Decrementa el contador de referencias
    }
}

// Metodo estatico New para crear un nuevo MPointer
template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T>* mp = new MPointer<T>();
    mp->pointer = new T();  // Asigna memoria para un objeto de tipo T
    mp->id = gc->generateId();
    gc->addPointer(mp);  // Añade el MPointer al recolector
    return *mp;
}

// Sobrecarga del operador de asignacion para otro MPointer
template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        if (id != -1) {
            gc->decrementRefCount(id);  // Decrementa el refCount actual
        }
        pointer = other.pointer;
        id = other.id;
        if (id != -1) {
            gc->incrementRefCount(id);  // Incrementa el refCount del nuevo ID
        }
    }
    return *this;
}

// Sobrecarga del operador de asignación para un valor
template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    if (!pointer) {
        pointer = new T(value);  // Asigna memoria para el valor
        id = gc->generateId();
        gc->addPointer(this);
    } else {
        *pointer = value;  // Asigna el valor al puntero existente
    }
    return *this;
}

// Sobrecarga del operador de asignación para nullptr
template <typename T>
MPointer<T>& MPointer<T>::operator=(std::nullptr_t) {
    if (id != -1) {
        gc->decrementRefCount(id);  // Decrementa el refCount
    }
    pointer = nullptr;
    id = -1;  // Invalida el ID
    return *this;
}

// Sobrecargas de operadores
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

// Conversión implicita a bool para verificar si el puntero es válido
template <typename T>
MPointer<T>::operator bool() const {
    return pointer != nullptr;
}

// Devuelve el ID unico del MPointer
template <typename T>
int MPointer<T>::getId() const {
    return id;
}

// Instanciaciones explicitas
template class MPointer<int>;
template class MPointer<LinkedList<int>::Node>;
template class MPointer<double>;
template class MPointer<std::string>;
template class MPointer<DoublyLinkedList<int>::Node>;
template class MPointer<long>;
template class MPointer<bool>;
template class MPointer<float>;
template class MPointer<char>;
