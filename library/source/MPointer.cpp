#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointer.h"
#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointerGC.h"
#include "/home/mvasquezr/DatosII/MPointer/library/doublyLinkedList/DoublyLinkedList.h"
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
        gc->decrementRefCount(id);
    }
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    mp.pointer = new T();
    return mp;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        if (id != -1) {
            gc->decrementRefCount(id);
        }
        pointer = other.pointer;
        id = other.id;
        gc->incrementRefCount(id);
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    if (!pointer) {
        pointer = new T();
        id = gc->generateId();
        gc->addPointer(this);
    }
    *pointer = value;
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(std::nullptr_t) {
    if (id != -1) {
        gc->decrementRefCount(id);
        pointer = nullptr;
        id = -1;
    }
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

// Instanciaciones explícitas
template class MPointer<int>;
template class MPointer<DoublyLinkedList<int>::Node>;
