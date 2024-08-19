#include "../headers/MPointer.h"

// Inicializar el recolector de basura
template <typename T>
MPointerGC<T>* MPointer<T>::gc = MPointerGC<T>::getInstance();

// Constructor
template <typename T>
MPointer<T>::MPointer() : pointer(nullptr), id(-1), refCount(nullptr) {
    gc->addPointer(this);
}

// Destructor
template <typename T>
MPointer<T>::~MPointer() {
    if (refCount) {
        (*refCount)--;  // Disminuir referencias
        if (*refCount == 0) {
            delete pointer;
            delete refCount;
            gc->removePointer(this);  // Informar al recolector de basura para que elimine la referencia
        }
    }
}

// Metodo estatico para crear un nuevo MPointer
template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    mp.pointer = new T(); // Reservar memoria para el tipo T
    mp.refCount = new int(1);
    return mp;
}

// Sobrecarga del operador de asignación entre MPointers
template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        if (refCount && --(*refCount) == 0) {  // Si no hay mas referencias, liberar memoria
            delete pointer;
            delete refCount;
            gc->removePointer(this);
        }
        this->pointer = other.pointer;  // Copiar la direccion de memoria
        this->id = other.id;
        this->refCount = other.refCount;
        (*refCount)++;  // Contador de referencias
    }
    return *this;
}

// Sobrecarga del operador de asignación para asignar un valor de tipo T
template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    if (!pointer) {
        pointer = new T();  // Reservar memoria si el puntero es nulo
        refCount = new int(1);
    }
    *pointer = value;  // Asignar el valor al espacio de memoria apuntado
    return *this;  // Devolver el valor actual
}

// Sobrecarga del operador * para acceder al valor almacenado
template <typename T>
T& MPointer<T>::operator*() {
    return *pointer;
}

// Sobrecarga del operador & para obtener la direccion de memoria
template <typename T>
T* MPointer<T>::operator&() {
    return pointer;
}

// Obtener el conteo de referencias
template <typename T>
int MPointer<T>::getRefCount() const {
    return *refCount;
}

template class MPointer<int>;
