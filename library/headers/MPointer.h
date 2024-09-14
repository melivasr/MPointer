#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointerGC;

template <typename T>
class MPointer {
private:
    T* pointer;  // Puntero al tipo de dato almacenado
    int id;
    static MPointerGC<T>* gc;  // Instancia del recolector de basura

public:
    MPointer();  // Constructor por defecto
    MPointer(const MPointer<T>& other);  // Constructor de copia
    MPointer(std::nullptr_t);
    ~MPointer();  // Destructor para liberar recursos y

    // Metodo para crear un nuevo MPointer, gestionado por el recolector de basura
    static MPointer<T> New();

    // Sobrecarga de operadores
    MPointer<T>& operator=(const MPointer<T>& other);  // Asignación de otro MPointer
    MPointer<T>& operator=(const T& value);  // Asignación directa de valor
    MPointer<T>& operator=(std::nullptr_t);  // Asignación de nullptr

    // Operadores de comparación con nullptr
    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;

    // Operadores
    T* operator& ();  // Devuelve la dirección del objeto apuntado
    T& operator*() const;  // Desreferencia el puntero
    T* operator->() const;  // Acceso a los miembros del objeto apuntado

    operator bool() const;  // Convierte el MPointer a bool para verificar si es válido

    int getId() const;  // Obtiene el identificador único del MPointer
};

#endif // MPOINTER_H
