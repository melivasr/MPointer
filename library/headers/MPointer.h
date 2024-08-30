#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* pointer;  // Puntero al tipo de dato almacenado
    int id;      // Identificador único para el MPointer
    static MPointerGC<T>* gc;  // Instancia del recolector de basura para MPointers

public:
    MPointer();  // Constructor
    MPointer(const MPointer<T>& other);  // Constructor de copia
    MPointer(std::nullptr_t);  // Constructor que acepta nullptr
    ~MPointer();  // Destructor

    // Metodo para crear un nuevo MPointer
    static MPointer<T> New();

    // Sobrecarga de operadores
    MPointer<T>& operator=(const MPointer<T>& other);
    MPointer<T>& operator=(const T& value);
    MPointer<T>& operator=(std::nullptr_t);  // Sobrecarga para asignar nullptr

    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;

    T* operator& ();
    T& operator*() const;

    T* operator->() const;

    operator bool() const;

    int getId() const;
};

#endif // MPOINTER_H
