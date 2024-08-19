#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* pointer;  // Puntero al tipo de dato almacenado
    int id;      // Identificador unico para el MPointer
    int* refCount;  // Contador de referencias
    static MPointerGC<T>* gc;  // Instancia del recolector de basura para MPointers

public:
    MPointer();  // Constructor
    ~MPointer();  // Destructor

    // Metodo para crear un nuevo MPointer
    static MPointer<T> New();

    // Sobrecarga del operadores
    MPointer<T>& operator=(const MPointer<T>& other);
    MPointer<T>& operator=(const T& value);

    T& operator*();
    T* operator&();

    // Obtener el conteo de referencias del MPointer
    int getRefCount() const;
};

#endif
