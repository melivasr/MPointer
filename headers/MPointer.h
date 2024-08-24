#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* pointer;  // Puntero al tipo de dato almacenado
    int id;      // Identificador único para el MPointer
    int* refCount;  // Contador de referencias
    static MPointerGC<T>* gc;  // Instancia del recolector de basura para MPointers

public:
    MPointer();  // Constructor
    MPointer(const MPointer<T>& other);  // Constructor de copia
    MPointer(std::nullptr_t);  // Constructor que acepta nullptr
    ~MPointer();  // Destructor

    // Método para crear un nuevo MPointer
    static MPointer<T> New();

    // Sobrecarga de operadores
    MPointer<T>& operator=(const MPointer<T>& other);
    MPointer<T>& operator=(const T& value);
    MPointer<T>& operator=(std::nullptr_t);  // Sobrecarga para asignar nullptr

    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;

    T& operator*();
    T* operator&();

    // Sobrecarga del operador -> para acceder a los miembros del puntero
    T* operator->() const;

    // Sobrecarga a bool para evaluar si el puntero es válido
    operator bool() const;

    // Obtener el conteo de referencias del MPointer
    int getRefCount() const;
};

#endif // MPOINTER_H
