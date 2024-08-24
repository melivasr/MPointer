#include "../headers/MPointer.h"
#include "../doublyLinkedList/DoublyLinkedList.h"

// Inicializar el recolector de basura
template <typename T>
MPointerGC<T>* MPointer<T>::gc = MPointerGC<T>::getInstance();

// Constructor
template <typename T>
MPointer<T>::MPointer() : pointer(nullptr), id(-1), refCount(nullptr) {
    gc->addPointer(this);
}

// Constructor de copia
template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) {
    pointer = other.pointer;
    id = other.id;
    refCount = other.refCount;
    if (refCount) {
        (*refCount)++;
    }
    gc->addPointer(this);
}

// Constructor que acepta nullptr
template <typename T>
MPointer<T>::MPointer(std::nullptr_t) : pointer(nullptr), id(-1), refCount(nullptr) {}

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
        if (refCount) {
            (*refCount)++;
        }
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

// Sobrecarga del operador de asignación para nullptr
template <typename T>
MPointer<T>& MPointer<T>::operator=(std::nullptr_t) {
    if (refCount && --(*refCount) == 0) {  // Si no hay más referencias, liberar memoria
        delete pointer;
        delete refCount;
        gc->removePointer(this);
    }
    pointer = nullptr;
    refCount = nullptr;
    id = -1;
    return *this;
}

// Sobrecarga del operador == para nullptr
template <typename T>
bool MPointer<T>::operator==(std::nullptr_t) const {
    return pointer == nullptr;
}

// Sobrecarga del operador != para nullptr
template <typename T>
bool MPointer<T>::operator!=(std::nullptr_t) const {
    return pointer != nullptr;
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

// Sobrecarga del operador -> para acceder a los miembros del puntero
template <typename T>
T* MPointer<T>::operator->() const {
    return pointer;
}

// Sobrecarga de conversión a bool para evaluar si el puntero es válido
template <typename T>
MPointer<T>::operator bool() const {
    return pointer != nullptr;
}

// Obtener el conteo de referencias
template <typename T>
int MPointer<T>::getRefCount() const {
    return refCount ? *refCount : 0;
}

// Instanciación explícita de la plantilla para el tipo int
template class MPointer<int>;

// Instanciación para DoublyLinkedList
template class MPointer<DoublyLinkedList<int>::Node>;

